#ifndef _objalloc_h_
#define _objalloc_h_

#include <platform.h>

#include "baselib/debug.h"

#include <common_structs.h>

typedef struct _objheap {
    u32 top;
    u32 curr;
    u32 size;
    u32 remain;
} objheap;

typedef struct _HSD_ObjAllocLink {
    struct _HSD_ObjAllocLink* next;
} HSD_ObjAllocLink;

typedef struct _HSD_ObjAllocData {
    u32 num_limit_flag : 1;
    u32 heap_limit_flag : 1;
    HSD_ObjAllocLink* freehead;
    u32 used;
    u32 free;
    u32 peak;
    u32 num_limit;
    u32 heap_limit_size;
    u32 heap_limit_num;
    u32 size;
    u32 align;
    struct _HSD_ObjAllocData* next;
} HSD_ObjAllocData;

static inline u32 HSD_ObjAllocGetUsing(HSD_ObjAllocData* data)
{
    HSD_ASSERT(205, data);
    return data->used;
}

static inline u32 HSD_ObjAllocGetFreed(HSD_ObjAllocData* data)
{
    HSD_ASSERT(221, data);
    return data->free;
}

static inline u32 HSD_ObjAllocGetPeak(HSD_ObjAllocData* data)
{
    HSD_ASSERT(237, data);
    return data->peak;
}

static inline void HSD_ObjAllocSetNumLimit(HSD_ObjAllocData* data,
                                           u32 num_limit)
{
    HSD_ASSERT(251, data);
    data->num_limit = num_limit;
}

static inline void HSD_ObjAllocEnableNumLimit(HSD_ObjAllocData* data)
{
    HSD_ASSERT(278, data);
    data->num_limit_flag = 1;
}

static inline void HSD_ObjAllocDisableNumLimit(HSD_ObjAllocData* data)
{
    HSD_ASSERT(291, data);
    data->num_limit_flag = 0;
}

void HSD_ObjSetHeap(u32 size, void* ptr);
s32 HSD_ObjAllocAddFree(HSD_ObjAllocData* data, u32 num);
void* HSD_ObjAlloc(HSD_ObjAllocData* data);
void HSD_ObjFree(HSD_ObjAllocData* data, void* obj);
void _HSD_ObjAllocForgetMemory(void* low, void* high);
void HSD_ObjAllocInit(HSD_ObjAllocData* data, size_t size, u32 align);

#endif
