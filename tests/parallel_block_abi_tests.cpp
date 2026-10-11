#ifdef NDEBUG
#undef NDEBUG
#endif
#include "quidra/abi/parallel_block.h"
#include "runtime_parallel.hpp"
#include "node_failure.hpp"
#include <array>
#include <atomic>
#include <cassert>
#include <cstdint>
#include <thread>
#include <vector>
using Entry=std::uint8_t(*)(void*);
struct Table {
    std::array<const void*,20> pointers{};
    std::array<std::uint64_t,16> numbers{};
    std::array<void*,4> frames{};
    void add(unsigned i,Entry entry,void** frame,const std::uint32_t* pred,unsigned count,bool safe,void(*drop)(void*)=nullptr){
        pointers[i*5]=reinterpret_cast<const void*>(entry);
        pointers[i*5+1]=reinterpret_cast<const void*>(entry);
        pointers[i*5+2]=pred;pointers[i*5+3]=reinterpret_cast<const void*>(drop);pointers[i*5+4]="<node body>()";
        numbers[i*4]=count;numbers[i*4+1]=safe;numbers[i*4+2]=10+i;numbers[i*4+3]=1;frames[i]=frame;
    }
    void* run(unsigned count){return quidra_parallel_block(pointers.data(),numbers.data(),frames.data(),count,nullptr,1,1);}
};
std::uint8_t assign(void* raw){auto** f=static_cast<void**>(raw);*static_cast<int*>(f[1])=40;return 0;}
std::uint8_t plus_one(void* raw){auto** f=static_cast<void**>(raw);*static_cast<int*>(f[2])=*static_cast<int*>(f[1])+1;return 0;}
std::uint8_t sum(void* raw){auto** f=static_cast<void**>(raw);*static_cast<int*>(f[3])=*static_cast<int*>(f[1])+*static_cast<int*>(f[2]);return 0;}
struct Receipt{int value;std::atomic<unsigned> dropped{0};};
std::uint8_t fail(void* raw){auto** f=static_cast<void**>(raw);f[0]=f[1];return 1;}
void drop(void* raw){auto** f=static_cast<void**>(raw);auto* receipt=static_cast<Receipt*>(f[0]);f[0]=nullptr;if(receipt)++receipt->dropped;}
std::uint8_t mark(void* raw){auto** f=static_cast<void**>(raw);++*static_cast<std::atomic<unsigned>*>(f[1]);return 0;}
std::uint8_t verify_caller(void* raw){auto** f=static_cast<void**>(raw);assert(std::this_thread::get_id()==*static_cast<std::thread::id*>(f[1]));return 0;}
std::uint8_t nested(void*){int x=0;void* frame[]{nullptr,&x};Table table;table.add(0,assign,frame,nullptr,0,true);assert(table.run(1)==nullptr);assert(x==40);return 0;}
struct Iterations {
    std::thread::id caller;
    bool caller_only{};
    bool fail{};
    std::vector<std::atomic<unsigned>> visits;
    explicit Iterations(unsigned count,bool owner):caller(std::this_thread::get_id()),caller_only(owner),visits(count) {}
};
std::uint8_t iteration(void* raw) {
    auto** frame=static_cast<void**>(raw);
    auto& context=*static_cast<Iterations*>(frame[1]);
    const auto ordinal=*static_cast<std::uint64_t*>(frame[2]);
    assert(ordinal<context.visits.size());
    if(context.caller_only)assert(std::this_thread::get_id()==context.caller);
    ++context.visits[ordinal];
    if(context.fail && (ordinal==1||ordinal==3))
        quidra::runtime::report_failure(quidra::abi::FailureReason::parallel_start_failed,
            quidra::abi::FailureArgs{.message=ordinal==1?"logical one":"logical three"},1,1);
    return 0;
}
void check_iterations(bool worker_safe) {
    Iterations context(257,!worker_safe);
    void* captures[]{&context};
    const void* pointers[]{reinterpret_cast<const void*>(iteration),reinterpret_cast<const void*>(iteration),nullptr,nullptr,"<parallel iteration>()"};
    const std::uint64_t numbers[]{0,0,1,1};
    assert(quidra_parallel_iterations(pointers,numbers,captures,1,0,worker_safe,nullptr,1,1)==nullptr);
    for(const auto& visit:context.visits)assert(visit==0);
    assert(quidra_parallel_iterations(pointers,numbers,captures,1,context.visits.size(),worker_safe,nullptr,1,1)==nullptr);
    for(const auto& visit:context.visits)assert(visit==1);
}
void check_iteration_failures() {
    Iterations context(257,false);context.fail=true;
    void* captures[]{&context};
    const void* pointers[]{reinterpret_cast<const void*>(iteration),reinterpret_cast<const void*>(iteration),nullptr,nullptr,"<parallel iteration>()"};
    const std::uint64_t numbers[]{0,0,1,1};
    struct Call {const void* const* pointers;const std::uint64_t* numbers;void** captures;std::uint64_t count;} call{pointers,numbers,captures,context.visits.size()};
    quidra::runtime::NodeFailureScope scope(nullptr);
    const bool okay=quidra::runtime::invoke_node_body(&scope,[](void* raw) {
        const auto& call=*static_cast<Call*>(raw);
        quidra_parallel_iterations(call.pointers,call.numbers,call.captures,1,call.count,true,nullptr,1,1);
    },&call);
    assert(!okay && scope.report);
    assert(scope.report->message().find("logical one")!=std::string_view::npos);
    for(const auto& visit:context.visits)assert(visit==1);
}
int main(){
    for(auto threads:{1U,2U,3U,8U}){
        quidra::runtime_parallel::set_thread_count_for_testing(threads);
        check_iterations(true);check_iterations(false);check_iteration_failures();
        int x=0,a=0,b=0,total=0;void* f0[]{nullptr,&x};void* f1[]{nullptr,&x,&a};void* f2[]{nullptr,&x,&b};void* f3[]{nullptr,&a,&b,&total};
        const std::uint32_t first[]{0},both[]{1,2};Table diamond;
        diamond.add(0,assign,f0,nullptr,0,true);diamond.add(1,plus_one,f1,first,1,true);diamond.add(2,plus_one,f2,first,1,true);diamond.add(3,sum,f3,both,2,true);
        assert(diamond.run(4)==nullptr);assert(total==82);
        Receipt early{0},late{1};std::atomic<unsigned> skipped{0},independent{0};
        void* e[]{nullptr,&early};void* l[]{nullptr,&late};void* s[]{nullptr,&skipped};void* n[]{nullptr,&independent};Table failure;
        failure.add(0,fail,e,nullptr,0,false,drop);failure.add(1,fail,l,nullptr,0,false,drop);failure.add(2,mark,s,first,1,true);failure.add(3,mark,n,nullptr,0,true);
        assert(failure.run(4)==&early);assert(e[0]==nullptr);assert(l[0]==nullptr);assert(early.dropped==0);assert(late.dropped==1);assert(skipped==0);assert(independent==1);
        std::thread::id caller=std::this_thread::get_id();void* caller_frame[]{nullptr,&caller};void* nested_frame[]{nullptr};Table fallback;
        fallback.add(0,verify_caller,caller_frame,nullptr,0,false);fallback.add(1,nested,nested_frame,nullptr,0,true);assert(fallback.run(2)==nullptr);
    }
}
