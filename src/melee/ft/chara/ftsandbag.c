#include "ftsandbag.h"

typedef struct _PairStruct {
    u32 x0_first;
    u32 x4_second;
    u8 padding[0xB8];
} PairStruct;

struct UnkFighterStruct
{
    u32 data_filler_0[(0x5f0) / 4];
    u32 x5F0;                   // 0x5f0
    u32 data_filler_1[(0x810 - 0x5f4) / 4];
};

extern struct UnkFighterStruct* lbl_804D6554;

void ftSandbag_OnLoad(HSD_GObj* gobj) {
    Fighter* fighter = gobj->user_data;
    ftData* fighterDataInfo = fighter->x10C_ftData;

    PairStruct* extAttrs = (PairStruct *) fighterDataInfo->ext_attr;

    u32 ext_attr_first = extAttrs->x0_first;
    u32 ext_attr_second = extAttrs->x4_second;

    PairStruct* special_attr_2 = fighter->x2D8_specialAttributes2;

    special_attr_2->x0_first = ext_attr_first;
    special_attr_2->x4_second = ext_attr_second;

    fighter->x2D4_specialAttributes = special_attr_2;

    fighter->x2228_flag.bits.b2 = 1;
    fighter->x2226_flag.bits.b0 = 1;

    func_8014FA30(fighter);
}

u32 func_8014FB78(HSD_GObj* gobj) {
    Fighter* fighter = gobj->user_data;
    ftData* fighter_data = fighter->x10C_ftData;

    PairStruct *special_attr = (PairStruct *)fighter->x2D4_specialAttributes;

    PairStruct* ext_attr = (PairStruct *)fighter_data->ext_attr;

    s32 ext_attr_first = ext_attr->x0_first;
    s32 ext_attr_second = ext_attr->x4_second;

    special_attr->x0_first = ext_attr_first;
    special_attr->x4_second = ext_attr_second;

    return ext_attr_first;
}

void func_8014FBA4(HSD_GObj* gobj) {
    f32 temp_f1;

    Fighter* fighter = gobj->user_data;
    if ((s32) fighter->xE0_airState == 1) {
        func_8007D7FC(fighter);
    }

    func_800693AC(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8007EFC0(fighter, lbl_804D6554->x5F0);
}
