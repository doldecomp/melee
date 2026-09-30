/**
 * @file objalloc.h
 * @brief Memory pool allocator
 * @details Manages fixed-size memory pools for efficient allocation of engine objects like JObj, DObj, and Fighter.
 */
#ifndef _objalloc_h_
#define _objalloc_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/debug.h>

typedef struct _objheap {
    uintptr_t top;
    uintptr_t curr;
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
ASSERT_SIZE(struct _HSD_ObjAllocData, 0x2C);

/**
 * @brief Gets the number of currently used blocks in the pool.
 */
static inline u32 HSD_ObjAllocGetUsing(HSD_ObjAllocData* data)
{
    HSD_ASSERT(205, data);
    return data->used;
}

/**
 * @brief Gets the number of free blocks in the pool.
 */
static inline u32 HSD_ObjAllocGetFreed(HSD_ObjAllocData* data)
{
    HSD_ASSERT(221, data);
    return data->free;
}

/**
 * @brief Gets the peak number of blocks used in the pool.
 */
static inline u32 HSD_ObjAllocGetPeak(HSD_ObjAllocData* data)
{
    HSD_ASSERT(237, data);
    return data->peak;
}

/**
 * @brief Sets the maximum number of blocks that can be allocated from the pool.
 */
static inline void HSD_ObjAllocSetNumLimit(HSD_ObjAllocData* data,
                                           u32 num_limit)
{
    HSD_ASSERT(251, data);
    data->num_limit = num_limit;
}

/**
 * @brief Enables the numerical block limit for the pool.
 */
static inline void HSD_ObjAllocEnableNumLimit(HSD_ObjAllocData* data)
{
    HSD_ASSERT(278, data);
    data->num_limit_flag = 1;
}

/**
 * @brief Disables the numerical block limit for the pool.
 */
static inline void HSD_ObjAllocDisableNumLimit(HSD_ObjAllocData* data)
{
    HSD_ASSERT(291, data);
    data->num_limit_flag = 0;
}

/// A NULL pool uses HSD_MemAlloc for backing storage.
/**
 * @brief Sets the global heap used for block allocations.
 */
void HSD_ObjSetHeap(u32 size, void* ptr);
/**
 * @brief Adds new free blocks to the allocator pool.
 * @param data The allocator data
 * @param num Number of blocks to add
 * @return Number of blocks successfully added
 */
s32 HSD_ObjAllocAddFree(HSD_ObjAllocData* data, u32 num);
/**
 * @brief Allocates a block from the object pool.
 * @param data The allocator data
 * @return Pointer to the allocated block
 */
void* HSD_ObjAlloc(HSD_ObjAllocData* data);
/**
 * @brief Frees a block back into the object pool.
 * @param data The allocator data
 * @param obj The block to free
 */
void HSD_ObjFree(HSD_ObjAllocData* data, void* obj);
/**
 * @brief Forgets memory allocations within a specific range.
 */
void _HSD_ObjAllocForgetMemory(void* low, void* high);
/**
 * @brief Initializes an object pool allocator.
 * @param data The allocator data
 * @param size The size of each block
 * @param align Alignment requirement for blocks
 */
void HSD_ObjAllocInit(HSD_ObjAllocData* data, size_t size, u32 align);

#endif
