#!/usr/bin/env bash
# A call path retained by one host thread survives another thread's walk.
set -euo pipefail
QUIDRA=$1
SOURCE=$2
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
export QUIDRA_CACHE_DIR="$TMP/cache"
cat > "$TMP/trace.qui" <<'QUI'
extern int32 sample_path(int32 tag) = "sample_path"
int32 path_a(int32 depth)
    if depth == 0
        return sample_path(1)
    return path_a(depth - 1) + 1
int32 path_b(int32 depth)
    if depth == 0
        return sample_path(2)
    return path_b(depth - 1) + 1
export "C" int32 from_a()
    return path_a(3) + 1
export "C" int32 from_b()
    return path_b(3) + 1
QUI
cat > "$TMP/host.cpp" <<'CPP'
#include "runtime_trace.hpp"
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

extern "C" int32_t from_a();
extern "C" int32_t from_b();
std::mutex mutex;
std::condition_variable ready;
bool a_ready = false, b_done = false;
bool valid = false;

std::string names(quidra::runtime::CallPath path) {
    std::string out;
    for (size_t i=0; i<path.count; ++i) {
        out += std::string(path.items[i].function);
        out += '|';
    }
    return out;
}
extern "C" int32_t sample_path(int32_t tag) {
    if (tag == 2) {
        auto other = quidra::runtime::walk_call_path();
        std::cout << "B=" << names(other) << '\n';
        {
            std::lock_guard<std::mutex> guard(mutex);
            b_done = true;
        }
        ready.notify_all();
        return 0;
    }
    auto own = quidra::runtime::walk_call_path();
    const auto before = names(own);
    {
        std::unique_lock<std::mutex> guard(mutex);
        a_ready = true;
        ready.notify_all();
        ready.wait(guard, [] {return b_done;});
    }
    const auto after = names(own);
    std::cout << "A-before=" << before << "\nA-after=" << after << '\n';
    valid = before.find("path_a") != std::string::npos && before == after;
    return 0;
}
int main() {
    std::thread first([] {from_a();});
    std::thread second([] {
        {std::unique_lock<std::mutex> guard(mutex);
         ready.wait(guard, [] {return a_ready;});}
        from_b();
    });
    first.join(); second.join();
    return valid ? 0 : 1;
}
CPP
"$QUIDRA" build "$TMP/trace.qui" --lib -o "$TMP/libtrace.a" --print-link-flags > "$TMP/flags"
read -r -a link_flags < "$TMP/flags"
"${CXX:-c++}" -std=c++17 -O1 -I "$SOURCE/src" "$TMP/host.cpp" "$TMP/libtrace.a" "${link_flags[@]}" -pthread -o "$TMP/host"
perl -e 'alarm shift; exec @ARGV' 60 "$TMP/host"
echo 'runtime trace concurrency: ok'
