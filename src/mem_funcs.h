#ifndef __MEM_FUNCS_H__
#define __MEM_FUNCS_H__

#include <Runtime/platform.h>
#include <stddef.h>

void __copy_longs_aligned(void* dst, const void* src, size_t len);
void __copy_longs_rev_aligned(void* dst, const void* src, size_t len);
void __copy_longs_unaligned(void* dst, const void* src, size_t len);
void __copy_longs_rev_unaligned(void* dst, const void* src, size_t len);

#endif
