#ifndef QUIDRA_PARALLEL_CALL_OWNERSHIP_H
#define QUIDRA_PARALLEL_CALL_OWNERSHIP_H
#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif
/* Owners are pointer pairs: stable typed mirror cell, empty-store callback.
   Scalar-only calls pass no owners and need no ticket. */
void* quidra_parallel_call_begin(const void* target,const void* const* owners,uint32_t count);
bool quidra_parallel_call_accept(const void* target);
bool quidra_parallel_call_end(void* ticket);
/* Internal invariant: never resume typed cleanup after an unaccepted call. */
void quidra_parallel_call_require_accept(bool accepted);
#ifdef __cplusplus
}
#endif
#endif
