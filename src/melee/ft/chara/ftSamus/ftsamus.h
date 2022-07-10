#include "melee/ft/ftcommon.h"
#include "melee/lb/lbvector.h"
#include <melee/it/item.h>

typedef struct _ftSamusAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    u8 data_filler_1[0x54 - 0x24];
    f32 x54;
    f32 x58;
    u8 data_filler_2[0x78 - 0x5C];
    f32 x78;
    f32 data_filler_3[2]; 
    f32 height_attributes[6];  //x84 - x98
    u8 data_filler_4[0xD4 - 0x9C];
} ftSamusAttributes;

/// maybe Samus grapple?
struct UNK_SAMUS_S1 {
    HSD_Joint* x0_joint;
    HSD_AnimJoint** x4_anim_joints;
    HSD_AnimJoint* x8_anim_joint;
    HSD_MatAnimJoint* xC_matanim_joint;
};

void ftSamus_80129048(HSD_GObj* fighterObj);
void ftSamus_801290A4(HSD_GObj* fighterObj);