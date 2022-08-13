#pragma once

#include <melee/ft/ftcommon.h>
#include <melee/lb/lbvector.h>
#include <melee/it/item.h>

typedef struct _ftSamusAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    s32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    f32 x6C;
    f32 x70;
    Vec x74_vec;
    f32 x80;
    f32 height_attributes[6];
    u8 data_filler_4[0xD4 - 0x9C];
} ftSamusAttributes;

/// maybe Samus grapple?
struct UNK_SAMUS_S1 {
    HSD_Joint* x0_joint;
    HSD_AnimJoint** x4_anim_joints;
    HSD_AnimJoint* x8_anim_joint;
    HSD_MatAnimJoint* xC_matanim_joint;
};

struct UNK_SAMUS_S2 {
    S32Vec intvec;
    Vec vec1;
    Vec vec2;
    f32 single_float;
};

void ftSamus_80128428(HSD_GObj* fighterObj);
void ftSamus_80129048(HSD_GObj* fighterObj);
void ftSamus_801290A4(HSD_GObj* fighterObj);
void ftSamus_801291F0(HSD_GObj* fighterObj);
void ftSamus_8012A168(HSD_GObj* fighterObj, Vec* spawnlocation);
void ftSamus_8012A074(HSD_GObj* fighterObj);
void ftSamus_8012B570(HSD_GObj* fighterObj);
void ftSamus_8012B5F0(HSD_GObj* fighterObj);
void ftSamus_8012B668(HSD_GObj* fighterObj);

inline void ftSamus_updateDamageDeathCBs(HSD_GObj* fighterObj) {
    Fighter* fp = getFighterPlus(fighterObj);
    fp->cb.x21DC_callback_OnTakeDamage = &ftSamus_80128428;
    fp->cb.x21E4_callback_OnDeath2 = &ftSamus_80128428;
}

//// only used in ftsamus3 so far (maybe move to there)
inline void ftSamus_SetAttrx2334(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    fp->sa.samus.x2234 = 0;
}

inline void ftSamus_destroyAllEF(HSD_GObj* fighterObj) {
    if (fighterObj) {
        Fighter* fp = getFighterPlus(fighterObj);
        if (fp->sa.samus.x2234) {
            efLib_DestroyAll(fighterObj);
            fp->sa.samus.x2234 = 0;
        }
    }
}

inline void ftSamus_UnkAndDestroyAllEF(HSD_GObj* fighterObj) {

    if (fighterObj) {
        Fighter* fp = fighterObj->user_data;
        u32 x222C = fp->sa.samus.x222C;
        if (x222C) {
            func_802B5974(x222C);
            fp->sa.samus.x222C = 0;
        }
        ftSamus_destroyAllEF(fighterObj);
    } 
}
