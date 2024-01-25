#ifndef MELEE_LB_LBCOLLISION_H
#define MELEE_LB_LBCOLLISION_H

#include <platform.h>
#include "ft/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <placeholder.h>
#include <dolphin/mtx/types.h>
#include <baselib/jobj.h>

void lbColl_JObjSetupMatrix(HSD_JObj*);
bool lbColl_80008248(HitCapsule*, HurtCapsule*, Mtx, f32, f32, f32);
void lbColl_80008440(HitCapsule*);
void lbColl_80008434(HitCapsule*);
bool lbColl_8000ACFC(UNK_T, HitCapsule*);
bool lbColl_80008688(HitCapsule*, enum_t, Fighter*);
void lbColl_CopyHitCapsule(HitCapsule* src, HitCapsule* dst);
UNK_RET lbColl_80008820(UNK_PARAMS);
int lbColl_80005BB0(HitCapsule*, int);
bool lbColl_80007ECC(HitCapsule*, HurtCapsule*, Mtx, f32 hit_scl_y,
                     f32 hurt_scl_y, f32 hurt_pos_z);
bool lbColl_8000805C(HitCapsule*, HurtCapsule*, UNK_T, s32, f32, f32, f32);
bool lbColl_80007BCC(HitCapsule*, HitResult* shield_hit, unk_t, s32, f32, f32,
                     f32);
bool lbColl_80007AFC(HitCapsule*, HitCapsule*, f32, f32);
void lbColl_80007DD8(HitCapsule*, HitResult*, Mtx, unk_t, unk_t, f32);
void lbColl_80008D30(HitCapsule*, UNK_T);
void lbColl_80008428(HitCapsule*);
bool lbColl_80005C44(Vec3*, Vec3*, Vec3*, Vec3*, f32, f32);
f32 lbColl_80005EBC(Vec3*, Vec3*, Vec3*, f32*);
f32 lbColl_80005FC0(Vec3*, Vec3*, Vec3*, f32*);
bool lbColl_80006094(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, f32, f32);
bool lbColl_800067F8(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, f32, f32, f32);
bool lbColl_80006E58(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Mtx, Vec3*, f32,
                     f32 scl, f32);

/// @param[out] angle
void lbColl_800077A0(Vec3*, Mtx, Vec3*, Vec3*, Vec3*, Vec3*, f32* angle, f32,
                     f32);

UNK_RET lbColl_80007B78(Mtx, Mtx, f32, f32);
void lbColl_800083C4(HurtCapsule*);
UNK_RET lbColl_800089B8(UNK_PARAMS);
UNK_RET lbColl_80008A5C(UNK_PARAMS);
UNK_RET lbColl_80008DA4(UNK_PARAMS);
UNK_RET lbColl_80008FC8(UNK_PARAMS);
void lbColl_800096B4(MtxPtr, UNK_T, UNK_T, UNK_T, UNK_T, f32);
UNK_RET lbColl_80009DD4(UNK_PARAMS);
UNK_RET lbColl_80009F54(UNK_PARAMS);
UNK_RET lbColl_8000A044(UNK_PARAMS);
UNK_RET lbColl_8000A10C(UNK_PARAMS);
UNK_RET lbColl_8000A1A8(UNK_PARAMS);
void lbColl_8000A244(HurtCapsule*, u32, Mtx, f32);
UNK_RET lbColl_8000A460(UNK_PARAMS);
UNK_RET lbColl_8000A584(UNK_PARAMS);
UNK_RET lbColl_8000A78C(UNK_PARAMS);
bool lbColl_8000A95C(HitResult*, unk_t, Mtx*, f32 pos_z);
UNK_RET lbColl_8000AB2C(UNK_PARAMS);

static inline bool approximatelyZero(f32 x)
{
    bool result;

    if ((x < 0.00001f) && (x > -0.00001f)) {
        result = true;
    } else {
        result = false;
    }

    return result;
}

static inline bool testPlusX(Vec3* a, Vec3* b, Vec3* c, f32 offset)
{
    f32 x = a->x + offset;
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

static inline bool testMinusX(Vec3* a, Vec3* b, Vec3* c, f32 offset)
{
    f32 x = a->x - offset;
    if (x > b->x && x > c->x) {
        return false;
    }

    return true;
}

#endif
