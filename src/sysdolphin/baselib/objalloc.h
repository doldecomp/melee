#ifndef _objalloc_h_
#define _objalloc_h_

#include <platform.h>

#include <common_structs.h>
#include <sysdolphin/baselib/debug.h>

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

typedef struct _HSD_ObjAllocInfo {
    struct _HSD_ObjAllocData* (*getData)(void);
    char* name;
} HSD_ObjAllocInfo;

static inline u32 HSD_ObjAllocUsed(HSD_ObjAllocInfo* info)
{
    HSD_ObjAllocData* data = info->getData();
    HSD_ASSERT(205, data);
    return data->used;
}

static inline u32 HSD_ObjAllocFree(HSD_ObjAllocInfo* info)
{
    HSD_ObjAllocData* data = info->getData();
    HSD_ASSERT(221, data);
    return data->free;
}

static inline u32 HSD_ObjAllocPeak(HSD_ObjAllocInfo* info)
{
    HSD_ObjAllocData* data = info->getData();
    HSD_ASSERT(237, data);
    return data->peak;
}

void HSD_ObjSetHeap(u32 size, void* ptr);
s32 HSD_ObjAllocAddFree(HSD_ObjAllocData* data, u32 num);
void* HSD_ObjAlloc(HSD_ObjAllocData* data);
void HSD_ObjFree(HSD_ObjAllocData* data, void* obj);
void _HSD_ObjAllocForgetMemory(any_t low, any_t high);
void HSD_ObjAllocInit(HSD_ObjAllocData* data, size_t size, u32 align);

#endif
