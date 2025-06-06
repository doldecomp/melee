#ifndef _shadow_h_
#define _shadow_h_

#include <platform.h>

#include "baselib/forward.h"

#include "baselib/cobj.h"
#include "baselib/list.h"
#include "baselib/objalloc.h"
#include "baselib/tobj.h"

#include <dolphin/mtx.h>

struct HSD_Shadow {
    HSD_SList* objects; // 0x0
    HSD_CObj* camera;   // 0x4
    HSD_TObj* texture;  // 0x8
    f32 scaleS;         // 0xC
    f32 scaleT;         // 0x10
    f32 transS;         // 0x14
    f32 transT;         // 0x18
    bool active;        // 0x1C
    u8 intensity;       // 0x20
    void* user_data;    // 0x24
};

struct HSD_ViewingRect {
    Vec3 origin;
    Vec3 up_v;
    Vec3 right_v;
    Vec3 eye_v;
    Vec3 eye_vn;
    f32 distance;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
    int perspective;
};

HSD_ObjAllocData* HSD_ShadowGetAllocData(void);
void HSD_ShadowInitAllocData(void);
HSD_Shadow* HSD_ShadowAlloc(void);
void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj);
void HSD_ShadowDeleteObject(HSD_Shadow* shadow, HSD_JObj* jobj);

void HSD_ShadowStartRender(HSD_Shadow* shadow);
void HSD_ShadowEndRender(HSD_Shadow* shadow);
void HSD_ShadowSetActive(HSD_Shadow* shadow, int active);

HSD_TObj* makeShadowTObj(void);
void HSD_ShadowRemove(HSD_Shadow* shadow);
void HSD_ShadowInit(HSD_Shadow* shadow);
void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height);

void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, float top, float bottom,
                              float left, float right);
void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec3* position, Vec3* interest,
                         Vec3* upvector, int perspective);
int HSD_ViewingRectCheck(HSD_ViewingRect* rect);
void HSD_ViewingRectAddRect(HSD_ViewingRect* rect, Vec3* position, float top,
                            float bottom, float left, float right);

#endif
