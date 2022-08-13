#ifndef _shadow_h_
#define _shadow_h_

#include <global.h>

#include <dolphin/types.h>

#include <sysdolphin/baselib/objalloc.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/list.h>

typedef struct _HSD_Shadow {
    struct _HSD_SList* objects; // 0x0
    struct _HSD_CObj* camera; // 0x4
    struct _HSD_TObj* texture; //0x8
    f32 scaleS; // 0xC
    f32 scaleT; // 0x10
    f32 transS; // 0x14
    f32 transT; // 0x18
    BOOL active; // 0x1C
    u8 intensity; // 0x20
    void* user_data; // 0x24
} HSD_Shadow;

typedef struct _HSD_ViewingRect {
    Vec origin;
    Vec up_v;
    Vec right_v;
    Vec eye_v;
    Vec eye_vn;
    f32 distance;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
    f32 perspective;
} HSD_ViewingRect;

HSD_ObjAllocData* HSD_ShadowGetAllocData(void);
void HSD_ShadowInitAllocData(void);
HSD_Shadow* HSD_ShadowAlloc(void);

#endif
