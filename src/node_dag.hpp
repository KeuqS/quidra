#pragma once
#include "ready_work.hpp"
#include "node_failure.hpp"
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <thread>
#include <vector>

namespace quidra::runtime_parallel::detail {
struct NodeSpec {
    std::uint8_t (*body)(void*){};
    void* frame{};
    const std::uint32_t* predecessors{};
    std::uint32_t predecessor_count{};
    bool worker_safe{};
    quidra::runtime::ModuleState module_state{};
    std::uint8_t (*join)(void*,std::uint8_t){};
    const char* display_name{};
    unsigned long long line{},column{};
    const void* trace_body{};
};
struct NodeResult {
    std::uint32_t index{std::numeric_limits<std::uint32_t>::max()};
    std::uint8_t status{};
    std::shared_ptr<quidra::runtime::OwnedNodeReport> report;
    std::optional<int> exit_status;
};
NodeResult run_shared_nodes(const NodeSpec* specs, std::uint32_t count);
class NodeDag {
    enum class State {pending, ready, running, finishing, succeeded, failed, skipped};
    struct Node {
        ReadyWork work;
        NodeDag* owner{};
        std::uint32_t index{};
        std::uint32_t remaining{};
        bool blocked{};
        State state{State::pending};
        std::uint8_t pending_status{};
        std::vector<std::uint32_t> successors;
    };
public:
    NodeDag(ReadyQueue& queue, const NodeSpec* specs, std::uint32_t count,
            std::uint64_t helpers)
        : queue_(queue), specs_(specs), nodes_(count), helpers_(helpers) {
        for (std::uint32_t i=0; i<count; ++i) {
            const auto& spec = specs[i];
            if (!spec.body || (spec.predecessor_count && !spec.predecessors))
                throw std::invalid_argument("invalid parallel node table");
            auto& node = nodes_[i];
            node.owner = this; node.index = i;
            node.remaining = spec.predecessor_count;
            node.work.invoke = invoke; node.work.context = &node;
            node.work.helper_bound = helpers;
            for (std::uint32_t j=0; j<spec.predecessor_count; ++j) {
                const auto predecessor = spec.predecessors[j];
                if (predecessor >= i)
                    throw std::invalid_argument("invalid parallel predecessor");
                nodes_[predecessor].successors.push_back(i);
            }
        }
        // Prepare every node and allocate inverse adjacency before publishing
        // any work. A construction failure therefore cannot leave callbacks
        // pointing into a partly constructed block.
    }
    NodeResult run() noexcept {
        if (nodes_.empty()) return {};
        {
            std::lock_guard<std::mutex> guard(mutex_);
            for (auto& node : nodes_) if (!node.remaining) ready(node);
            refresh_local();
        }
        while (!done_.load(std::memory_order_acquire)) {
            Node* local = nullptr;
            Node* joining = nullptr;
            {
                std::lock_guard<std::mutex> guard(mutex_);
                for(auto& node:nodes_) if(node.state==State::finishing){
                    node.state=State::running;joining=&node;break;
                }
                for (auto& node : nodes_) {
                    if (joining || worker(node) || terminal(node.state)) continue;
                    if (node.state == State::ready) {
                        node.state = State::running;
                        local = &node;
                    }
                    break;
                }
                refresh_local();
            }
            if(joining){
                const auto& spec=specs_[joining->index];
                finish(joining->index,spec.join(spec.frame,joining->pending_status));
            }else if (local) invoke(local);
            else if (!queue_.help(0, true))
                queue_.wait_for_progress(done_, local_ready_);
        }
        return result_;
    }
private:
    static bool terminal(State state) noexcept {
        return state == State::succeeded || state == State::failed || state == State::skipped;
    }
    bool worker(const Node& node) const noexcept {
        return helpers_ != 0 && specs_[node.index].worker_safe;
    }
    void ready(Node& node) noexcept {
        node.state = State::ready;
        if (worker(node)) queue_.push(node.work);
    }
    void refresh_local() noexcept {
        bool ready = false;
        for(const auto& node:nodes_) if(node.state==State::finishing){
            local_ready_.store(true,std::memory_order_release);return;
        }
        for (const auto& node : nodes_) {
            if (worker(node) || terminal(node.state)) continue;
            ready = node.state == State::ready;
            break;
        }
        local_ready_.store(ready, std::memory_order_release);
    }
    static void invoke(void* raw) noexcept {
        auto& node = *static_cast<Node*>(raw);
        auto* owner = node.owner;
        {
            std::lock_guard<std::mutex> guard(owner->mutex_);
            node.state = State::running;
        }
        const auto& spec = owner->specs_[node.index];
        auto status = spec.body(spec.frame);
        if(spec.join && std::this_thread::get_id()!=owner->caller_){
            auto* queue=&owner->queue_;
            {
                std::lock_guard<std::mutex> guard(owner->mutex_);
                node.pending_status=status;node.state=State::finishing;
                owner->refresh_local();
            }
            queue->changed();
            return;
        }
        if(spec.join)status=spec.join(spec.frame,status);
        owner->finish(node.index, status);
    }
    void finish(std::uint32_t index, std::uint8_t status) noexcept {
        auto* queue = &queue_;
        bool completed = false;
        {
            std::lock_guard<std::mutex> guard(mutex_);
            auto& node = nodes_[index];
            node.state = status == 0 ? State::succeeded : State::failed;
            ++terminal_count_;
            if (status && index < result_.index) result_ = {index, status, {}, {}};
            // Predecessors precede successors. A single forward traversal
            // propagates skipped descendants without allocating on failure.
            propagate(node, status != 0);
            for (std::uint32_t i=index+1; i<nodes_.size(); ++i) {
                auto& successor = nodes_[i];
                if (successor.state != State::pending || successor.remaining) continue;
                if (successor.blocked) {
                    successor.state = State::skipped;
                    ++terminal_count_;
                    propagate(successor, true);
                } else ready(successor);
            }
            refresh_local();
            completed = terminal_count_ == nodes_.size();
        }
        // No block lock survives publication. After complete() the block
        // itself may already have been destroyed by its joining thread.
        if (completed) queue->complete(done_);
        else queue->changed();
    }
    void propagate(const Node& predecessor, bool blocked) noexcept {
        for (const auto index : predecessor.successors) {
            auto& successor = nodes_[index];
            --successor.remaining;
            successor.blocked = successor.blocked || blocked;
        }
    }
    ReadyQueue& queue_;
    const NodeSpec* specs_;
    std::vector<Node> nodes_;
    std::uint64_t helpers_;
    const std::thread::id caller_{std::this_thread::get_id()};
    std::mutex mutex_;
    std::atomic<bool> done_{false};
    std::atomic<bool> local_ready_{false};
    std::size_t terminal_count_{};
    NodeResult result_;
};
inline NodeResult run_nodes(ReadyQueue& queue, const NodeSpec* specs,
                             std::uint32_t count, std::uint64_t helpers) {
    NodeDag dag(queue, specs, count, helpers);
    return dag.run();
}
} // namespace quidra::runtime_parallel::detail
