#ifndef QUIDRA_ABI_PARALLEL_BLOCK_H
#define QUIDRA_ABI_PARALLEL_BLOCK_H
#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif
/* Per-node pointer table: entry, trace body, uint32 predecessors, frame drop,
   display name. Number table: predecessor count, worker-safe, line, column.
   Each frame starts with a nullable owned void|error cell; captures follow.
   All work and native fences finish before this call returns or propagates. */
typedef void (*quidra_parallel_module_state)(uint64_t*,bool);
void* quidra_parallel_block(const void* const* pointers,const uint64_t* numbers,
                           void* const* frames,uint32_t count,
                           quidra_parallel_module_state state,
                           unsigned long long line,unsigned long long column);
/* One nonfallible, independent void node table. Captures are borrowed until
   join; the runtime appends a pointer to the uint64 logical ordinal to each
   bounded worker frame. Count must fit INT64_MAX. All iterations drain, and
   the lowest failing ordinal determines the joined outcome. */
void* quidra_parallel_iterations(const void* const* pointers,const uint64_t* numbers,
    void* const* captures,uint32_t capture_count,uint64_t count,bool worker_safe,
    quidra_parallel_module_state state,unsigned long long line,unsigned long long column);
/* Receipts borrow stable tracker/storage until the enclosing join. */
void* quidra_parallel_array_prepare(void* array,bool read_only,bool bare_integer,
    unsigned long long line,unsigned long long column);
bool quidra_parallel_array_inline(void* receipt);
void quidra_parallel_array_mark(void* receipt,void* address,unsigned long long bytes);
#ifdef __cplusplus
}
#endif
#endif
