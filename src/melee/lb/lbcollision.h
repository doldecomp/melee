#ifndef GALE01_005BB0
#define GALE01_005BB0

#include <placeholder.h>
#include <platform.h>

#include "ft/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <baselib/jobj.h>

struct lbColl_8000A10C_arg0_t;

struct Fighter_x1614_t;

/* 005BB0 */ int lbColl_80005BB0(HitCapsule*, int);
/* 005C44 */ bool lbColl_80005C44(const Vec3*, const Vec3*, const Vec3*, Vec3*,
                                  float, float);
/* 005EBC */ float lbColl_80005EBC(const Vec3*, const Vec3*, const Vec3*,
                                   float*);
/* 005FC0 */ float lbColl_80005FC0(Vec3*, Vec3*, Vec3*, float*);
/* 006094 */ bool lbColl_80006094(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*,
                                  float, float);
/* 0067F8 */ bool lbColl_800067F8(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*,
                                  float, float, float);
/* 0077A0 */ void lbColl_800077A0(Vec3*, Mtx, Vec3*, Vec3*, Vec3*, Vec3*,
                                  float* angle, float, float);
/* 007AFC */ bool lbColl_80007AFC(HitCapsule*, HitCapsule*, float, float);
/* 007B78 */ bool lbColl_80007B78(Mtx, struct Fighter_x1614_t*, float, float);
/* 007BCC */ bool lbColl_80007BCC(HitCapsule*, HitResult* shield_hit, UNK_T,
                                  s32, float, float, float);
/* 007D68 */ void lbColl_JObjSetupMatrix(HSD_JObj*);
/* 007DD8 */ void lbColl_80007DD8(HitCapsule*, HitResult*, Mtx, Vec3*, float*,
                                  float);
/* 007ECC */ bool lbColl_80007ECC(HitCapsule*, HurtCapsule*, Mtx,
                                  float hit_scl_y, float hurt_scl_y,
                                  float hurt_pos_z);
/* 00805C */ bool lbColl_8000805C(HitCapsule* arg0, HurtCapsule* arg1,
                                  Mtx arg2, s32 arg3, float arg4, float arg5,
                                  float arg6);
/* 008248 */ bool lbColl_80008248(HitCapsule*, HurtCapsule*, Mtx, float, float,
                                  float);
/* 0083C4 */ void lbColl_800083C4(HurtCapsule*);
/* 008428 */ void lbColl_80008428(HitCapsule*);
/* 008434 */ void lbColl_80008434(HitCapsule*);
/* 008440 */ void lbColl_80008440(HitCapsule*);
/* 0084FC */ void lbColl_CopyHitCapsule(HitCapsule* src, HitCapsule* dst);
/* 008688 */ bool lbColl_80008688(HitCapsule*, int type, void* victim);
/* 008820 */ bool lbColl_80008820(HitCapsule*, int type, void* victim);
/* 0089B8 */ void lbColl_800089B8(HitCapsule* hit, UNK_T arg1);
/* 008A5C */ void lbColl_80008A5C(HitCapsule* hit);
/* 008D30 */ void lbColl_80008D30(HitCapsule*, lbColl_80008D30_arg1*);
/* 008DA4 */ UNK_RET lbColl_80008DA4(GXColor*, GXColor*);
/* 008FC8 */ void lbColl_80008FC8(Vec3, Vec3, GXColor*, GXColor*, float);
/* 0096B4 */ void lbColl_800096B4(MtxPtr, Vec3, Vec3, GXColor*, GXColor*, float);
/* 009DD4 */ UNK_RET lbColl_80009DD4(Vec3*, Vec3*, GXColor*);
/* 009F54 */ bool lbColl_80009F54(HitCapsule* hit, u32 arg1, float arg8);
/* 00A044 */ bool lbColl_8000A044(HitCapsule* hit, u32 arg1, float arg8);
/* 00A10C */ bool lbColl_8000A10C(struct lbColl_8000A10C_arg0_t*, u32, f32);
/* 00A1A8 */ bool lbColl_8000A1A8(struct Fighter_x1614_t*, int, float scale_y);
/* 00A244 */ bool lbColl_8000A244(HurtCapsule* hurt, u32 arg1, Mtx arg2,
                                  float arg3);
/* 00A460 */ bool lbColl_8000A460(Fighter_x1670_t* hurt, u32 arg1);
/* 00A584 */ bool lbColl_8000A584(HurtCapsule* hurt, u32 arg1, u32 arg2,
                                  MtxPtr arg3, float arg8);
/* 00A78C */ bool lbColl_8000A78C(HitResult* hit, u32 arg1, Mtx arg2,
                                  float pos_z);
/* 00A95C */ bool lbColl_8000A95C(HitResult* hit, u32 arg1, Mtx arg2,
                                  float pos_z);
/* 00AB2C */ bool lbColl_8000AB2C(HitResult* hit, u32 arg1, Mtx arg2,
                                  float pos_z);
/* 00ACFC */ bool lbColl_8000ACFC(void*, HitCapsule*);

static inline bool approximatelyZero(float x)
{
    bool result;

    if ((x < 0.00001f) && (x > -0.00001f)) {
        result = true;
    } else {
        result = false;
    }

    return result;
}

static inline bool testPlusX(Vec3* a, Vec3* b, Vec3* c, float offset)
{
    float x = a->x + offset;
    if (x < b->x && x < c->x) {
        return false;
    }

    return true;
}

static inline bool testPlus(float a, float b, float c, float offset)
{
    float x = a + offset;
    if (x < b && x < c) {
        return false;
    }

    return true;
}

static inline bool testMinusX(Vec3* a, Vec3* b, Vec3* c, float offset)
{
    float x = a->x - offset;
    if (x > b->x && x > c->x) {
        return false;
    }

    return true;
}

#endif
