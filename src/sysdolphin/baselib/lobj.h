#ifndef SYSDOLPHIN_BASELIB_LOBJ_H
#define SYSDOLPHIN_BASELIB_LOBJ_H

#include "baselib/forward.h"

#include "baselib/cobj.h"
#include "baselib/fobj.h"
#include "baselib/object.h"
#include "baselib/wobj.h"

#include <dolphin/gx/GXLight.h>

struct HSD_LightPoint {
    f32 cutoff;
    u32 point_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightPointDesc {
    f32 cutoff;
    u32 point_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightSpot {
    f32 cutoff;
    u32 spot_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightSpotDesc {
    f32 cutoff;
    u32 spot_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightAttn {
    f32 a0;
    f32 a1;
    f32 a2;
    f32 k0;
    f32 k1;
    f32 k2;
};

struct HSD_LObj {
    /* 0x00 - 0x04 */ HSD_Obj parent;
    /* 0x08 */ u16 flags;
    /* 0x0A */ u16 priority;
    /* 0x0C */ HSD_LObj* next;
    /* 0x10 */ GXColor color;
    /* 0x14 */ GXColor hw_color;
    /* 0x18 */ HSD_WObj* position;
    /* 0x1C */ HSD_WObj* interest;
    /* 0x20 - 0x34 */ union {
        HSD_LightPoint point;
        HSD_LightSpot spot;
        HSD_LightAttn attn;
    } u;
    /* 0x38 */ f32 shininess;
    /* 0x3C - 0x44 */ Vec3 lvec;
    /* 0x48 */ HSD_AObj* aobj;
    /* 0x4C */ GXLightID id;
    /* 0x50 */ GXLightObj lightobj;
    /* 0x90 */ GXLightID spec_id;
    /* 0x94 */ GXLightObj spec_lightobj;
};

struct HSD_LightDesc {
    /* 0x00 */ char* class_name;
    /* 0x04 */ HSD_LightDesc* next;
    /* 0x08 */ u16 flags;
    /* 0x0A */ u16 attnflags;
    /* 0x0C */ GXColor color;
    /* 0x10 */ HSD_WObjDesc* position;
    /* 0x14 */ HSD_WObjDesc* interest;
    union {
        void* p;
        f32* shininess;
        HSD_LightPointDesc* point;
        HSD_LightSpotDesc* spot;
        HSD_LightAttn* attn;
    } u;
};

struct HSD_LightAnim {
    struct _HSD_LightAnim* next;
    HSD_AObjDesc* aobjdesc;
    struct _HSD_WObjAnim* position_anim;
    struct _HSD_WObjAnim* interest_anim;
};

struct HSD_LObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_LObj* lobj, HSD_LightDesc* ldesc);
};

#define HSD_LOBJ(o) ((HSD_LObj*) (o))
#define HSD_LOBJ_INFO(i) ((HSD_LObjInfo*) (i))
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

void LObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val);

void HSD_LObjAnim(HSD_LObj* lobj);
void HSD_LObjAnimAll(HSD_LObj* lobj);
void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe);
void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe);
void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir);
void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess);

bool HSD_LObjGetPosition(HSD_LObj*, Vec3*);
bool HSD_LObjGetInterest(HSD_LObj*, Vec3*);

HSD_WObj* HSD_LObjGetPositionWObj(HSD_LObj* lobj);
HSD_WObj* HSD_LObjGetInterestWObj(HSD_LObj* lobj);
void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe);
void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe);

s32 HSD_LightID2Index(GXLightID);
void HSD_LObjDeleteCurrent(HSD_LObj* lobj);
s32 HSD_Index2LightID(u32);
void HSD_LObjRemoveAll(HSD_LObj* lobj);
void HSD_LObjSetPosition(HSD_LObj* lobj, Vec3* position);
void HSD_LObjSetInterest(HSD_LObj* lobj, Vec3* interest);
void func_803668EC(HSD_LObj* lobj);
void HSD_LObjSetupInit(HSD_CObj* arg0);

void func_80366CA4(HSD_LObj* lobj, GXColor* color);
void func_80366CB0(HSD_LObj* lobj, GXColor* color);
void func_80366CBC(HSD_LObj* lobj, f32 cutoff, s32 point_func);
void func_80366CD0(HSD_LObj* lobj, f32 ref_dist, f32 ref_br, s32 dist_func);
void HSD_LObjSetupSpecularInit(Mtx pmtx);
void setup_spec_lightobj(HSD_LObj* lobj, Mtx mtx, s32 spec_id);
void setup_point_lightobj(HSD_LObj* lobj, Mtx mtx);
void setup_spot_lightobj(HSD_LObj* lobj, Mtx mtx);
u32 HSD_LObjGetType(HSD_LObj* lobj);
void HSD_LObjAddCurrent(HSD_LObj* lobj);
void HSD_LObjUnrefThis(HSD_LObj* lobj);
void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj);
void HSD_LObjSetCurrentAll(HSD_LObj* lobj);
HSD_LObj* HSD_LObjGetCurrentByType(u16 type);

#endif
