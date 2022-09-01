#ifndef _objalloc_h_
#define _objalloc_h_

#include <global.h>

#include <dolphin/types.h>
#include <sysdolphin/baselib/debug.h>

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

typedef struct ItemCommonData
{
    u32 x0;
    u32 x4;
    u32 x8;
    u32 xC;
    u32 x10;
    u32 x14;
    u32 x18;
    u32 x1C;
    u32 x20;
    u32 x24;
    u32 x28;
    u32 x2C;
    s32 x30;
    u32 x34;
    s32 x38_float;
    s32 x3C_float;
    s32 x40_float;
    s32 x44_float;
    s32 x48_float;
    s32 x4C_float;
    s32 x50_float;
    s32 x54_float;
    s32 x58_float;
    s32 x5C_float;
    s32 x60_float;
    s32 x64_float;
    s32 x68_float;
    f32 x6C_float;
    f32 x70_float;
    f32 x74_float;
    f32 x78_float;
    f32 x7C_float;
    f32 x80_float[13];
    s32 xB4;
    f32 xB8;
    f32 xBC;
    f32 xC0;
    f32 xC4;
    f32 xC8;
    f32 xCC;
    f32 xD0;
    f32 xD4;
    s32 xD8;
    s32 xDC;
    u8 filler[0x148 - 0xE0];
    s32 x148;
    f32 x14C;
    f32 x150;
    f32 x154;
    f32 x158;
    f32 x15C;
} ItemCommonData;

extern s8 lbl_804D6D00;
extern s32 lbl_804D6D08;
extern s32 lbl_804D6D0C;
extern s32 lbl_804D6D10;
extern s32 lbl_804D6D14;
extern ItemCommonData* lbl_804D6D28;

typedef struct HSD_ObjAllocUnk2
{
    u8 x0_filler[0x144];
    u32 x144;
    u32 x148;
    u32 x14C;
    UnkFlagStruct x150;
    u32 x154;
    u32 x158;
    u32 x15C;
}HSD_ObjAllocUnk2;

typedef struct x1C_struct
{
    u32 x1C;
}x1C_struct;

typedef struct HSD_ObjAllocUnk
{
    u32 x0;
    u32 x4;
    u32 x8;
    u32 xC;
    u32 x10;
    u32 x14;
    u32 x18;
    x1C_struct x1C_struct;
    u32 x20;
    u32 x24;
    u32 x28;
    u32 x2C;
    u32 x30;
    u32 x34;
    u32 x38;
    u32 x3C;
    u32 x40;
    u32 x44;
    u32 x48;
    u32 x4C;
    u32 x50;
    u32 x54;
    u32 x58;
    u32 x5C;
    u32 x60;
    u32 x64;
    u32 x68;
} HSD_ObjAllocUnk;

typedef struct HSD_ObjAllocUnkStruct
{
    HSD_ObjAllocData x0;
    HSD_ObjAllocData x2C;
    HSD_ObjAllocData x58;
    HSD_ObjAllocUnk x84;
    HSD_ObjAllocUnk2 xEC;
}HSD_ObjAllocUnkStruct;

typedef struct HSD_ObjAllocUnk3
{
    u32 x0;
    u32 x4;
    u32 x8;
    u32 xC;
}HSD_ObjAllocUnk3;

typedef struct HSD_ObjAllocUnk4
{
    u8 x0;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 x4;
    u16 x6;
    u16 x8;
    u16 xA;
    u16 xC;
    u32 x10;
}HSD_ObjAllocUnk4;

typedef struct HSD_ObjAllocUnk5
{
    u8 x0;
    u32 x4;
    u16 x8;
    u16 xA;
    u16 xC;
}HSD_ObjAllocUnk5;

typedef struct HSD_ObjAllocUnk6
{
    u8 x0;
    u32 x4;
    u16 x8;
    u16 xA;
    u16 xC;
}HSD_ObjAllocUnk6;

typedef struct Item_r13_Data
{
    ItemCommonData* item_common;
    void** common_items;
    void** adventure_items;
    void** pokeball_items;
    s32 x10;
    s32 x14;
}Item_r13_Data;

typedef struct _HSD_ObjAllocInfo {
    struct _HSD_ObjAllocData* (*getData)(void);
    char* name;
} HSD_ObjAllocInfo;

inline u32 HSD_ObjAllocUsed(HSD_ObjAllocInfo* info)
{
    HSD_ObjAllocData* data = info->getData();
    assert_line(205, data);
    return data->used;
}

inline u32 HSD_ObjAllocFree(HSD_ObjAllocInfo* info)
{
    HSD_ObjAllocData* data = info->getData();
    assert_line(221, data);
    return data->free;
}

inline u32 HSD_ObjAllocPeak(HSD_ObjAllocInfo* info)
{
    HSD_ObjAllocData* data = info->getData();
    assert_line(237, data);
    return data->peak;
}

void HSD_ObjSetHeap(u32 size, void* ptr);
s32	HSD_ObjAllocAddFree(HSD_ObjAllocData* data, u32 num);
void* HSD_ObjAlloc(HSD_ObjAllocData* data);
void HSD_ObjFree(HSD_ObjAllocData* data, void* obj);
void _HSD_ObjAllocForgetMemory(void);
void HSD_ObjAllocInit(HSD_ObjAllocData *data, u32 size, u32 align);

#endif
