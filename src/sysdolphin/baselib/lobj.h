#ifndef _lobj_h_
#define _lobj_h_

#include <global.h>

#include <dolphin/types.h>
#include <dolphin/gx/GXLight.h>

#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/fobj.h>
#include <sysdolphin/baselib/wobj.h>

#define HSD_A_L_LITC_R 9
#define HSD_A_L_LITC_G 10
#define HSD_A_L_LITC_B 11
#define HSD_A_L_VIS 12
#define HSD_A_L_A0 13
#define HSD_A_L_A1 14
#define HSD_A_L_A2 15
#define HSD_A_L_K0 16
#define HSD_A_L_K1 17
#define HSD_A_L_K2 18
#define HSD_A_L_CUTOFF 19
#define HSD_A_L_REFDIST 20
#define HSD_A_L_REFBRIGHT 21
#define HSD_A_L_LITC_A 22

#define LOBJ_AMBIENT (0 << 0)
#define LOBJ_INFINITE (1 << 0)
#define LOBJ_POINT (2 << 0)
#define LOBJ_SPOT (3 << 0)
#define LOBJ_DIFFUSE (1 << 2)
#define LOBJ_SPECULAR (1 << 3)
#define LOBJ_ALPHA (1 << 4)
#define LOBJ_HIDDEN (1 << 5)
#define LOBJ_RAW_PARAM (1 << 6)
#define LOBJ_DIFF_DIRTY (1 << 7)
#define LOBJ_SPEC_DIRTY (1 << 8)

#define LOBJ_TYPE_MASK 3

#define LOBJ_LIGHT_ATTN_NONE 0
#define LOBJ_LIGHT_ATTN 1

#define HSD_LObjGetType(o) (o->flags & 0x3)

typedef struct _HSD_LightPoint {
    f32 cutoff;
    u32 point_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
} HSD_LightPoint;

typedef struct _HSD_LightPointDesc {
    f32 cutoff;
    u32 point_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
} HSD_LightPointDesc;

typedef struct _HSD_LightSpot {
    f32 cutoff;
    u32 spot_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
} HSD_LightSpot;

typedef struct _HSD_LightSpotDesc {
    f32 cutoff;
    u32 spot_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
} HSD_LightSpotDesc;

typedef struct _HSD_LightAttn {
    f32 a0;
    f32 a1;
    f32 a2;
    f32 k0;
    f32 k1;
    f32 k2;
} HSD_LightAttn;

typedef struct _HSD_LObj {
    /* 0x00 - 0x04 */ HSD_Obj parent;
    /* 0x08 */ u16 flags;
    /* 0x0A */ u16 priority;
    /* 0x0C */ struct _HSD_LObj* next;
    /* 0x10 */ GXColor color;
    /* 0x14 */ GXColor hw_color;
    /* 0x18 */ struct _HSD_WObj* position;
    /* 0x1C */ struct _HSD_WObj* interest;
    /* 0x20 - 0x34 */ union {
        HSD_LightPoint point;
        HSD_LightSpot spot;
        HSD_LightAttn attn;
    } u;
    /* 0x38 */ f32 shininess;
    /* 0x3C - 0x44 */ Vec lvec;
    /* 0x48 */ struct _HSD_AObj* aobj;
    /* 0x4C */ GXLightID id;
    /* 0x50 */ GXLightObj lightobj;
    /* 0x90 */ GXLightID spec_id;
    /* 0x94 */ GXLightObj spec_lightobj;
} HSD_LObj;

typedef struct _HSD_LightDesc {
    /* 0x00 */ char* class_name;
    /* 0x04 */ struct _HSD_LightDesc* next;
    /* 0x08 */ u16 flags;
    /* 0x0A */ u16 attnflags;
    /* 0x0C */ GXColor color;
    /* 0x10 */ struct _HSD_WObjDesc* position;
    /* 0x14 */ struct _HSD_WObjDesc* interest;
    union {
        void* p;
        f32* shininess;
        HSD_LightPointDesc* point;
        HSD_LightSpotDesc* spot;
        HSD_LightAttn* attn;
    } u;
} HSD_LightDesc;

typedef struct _HSD_LightAnim {
    struct _HSD_LightAnim* next;
    struct _HSD_AObjDesc* aobjdesc;
    struct _HSD_WObjAnim* position_anim;
    struct _HSD_WObjAnim* interest_anim;
} HSD_LightAnim;

typedef struct _HSD_LObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_LObj* lobj, HSD_LightDesc* ldesc);
} HSD_LObjInfo;

#define HSD_LOBJ(o) ((HSD_LObj*)(o))
#define HSD_LOBJ_INFO(i) ((HSD_LObjInfo*)(i))
#define HSD_LOBJ_METHOD(o) HSD_LOBJ_INFO(HSD_OBJECT_METHOD(o))

extern HSD_LObjInfo hsdLobj;

u32 HSD_LObjGetFlags(HSD_LObj* lobj);
void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags);
void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags);
s32 HSD_LObjGetLightMaskDiffuse(void);
s32 HSD_LObjGetLightMaskAttnFunc(void);
s32 HSD_LObjGetLightMaskAlpha(void);
s32 HSD_LObjGetLightMaskSpecular(void);
s32 HSD_LObjGetNbActive(void);
HSD_LObj* HSD_LObjGetActiveByID(GXLightID id);
HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx);

void LObjUpdateFunc(void* obj, u32 type, FObjData* val);

void HSD_LObjAnim(HSD_LObj* lobj);
void HSD_LObjAnimAll(HSD_LObj *lobj);
void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe);
void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe);
void HSD_LObjGetLightVector(HSD_LObj *lobj, VecPtr dir);
void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess, u32 unused);

BOOL HSD_LObjGetPosition(HSD_LObj*, Vec*);
BOOL HSD_LObjGetInterest(HSD_LObj*, Vec*);

HSD_WObj* HSD_LObjGetPositionWObj(HSD_LObj* lobj);
HSD_WObj* HSD_LObjGetInterestWObj(HSD_LObj* lobj);
void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe);
void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe);

s32 HSD_LightID2Index(GXLightID);
void HSD_LObjDeleteCurrent(HSD_LObj* lobj);
s32 HSD_Index2LightID(u32);

#endif
