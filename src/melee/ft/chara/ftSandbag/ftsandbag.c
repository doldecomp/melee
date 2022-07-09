#include "ftsandbag.h"

typedef struct _ftSandbagAttributes
{
    u32 x0_pair[2];
} ftSandbagAttributes;

void ftSandbag_OnDeath(void) {
    return;
}

void ftSandbag_OnLoad(HSD_GObj* gobj) {
    Fighter* fighter = gobj->user_data;


    PUSH_ATTRS(fighter, ftSandbagAttributes);

    fighter->x2228_flag.bits.b2 = 1;
    fighter->x2226_flag.bits.b0 = 1;

    func_8014FA30(fighter);
}

void func_8014FA30(Fighter* fighter)
{
    FighterBone* bones = fighter->x5E8_fighterBones;
    func_8000C1C0(bones[5].x0_jobj, bones[12].x0_jobj);
    bones = fighter->x5E8_fighterBones;
    func_8000C1C0(bones[5].x4_jobj2, bones[12].x4_jobj2);
    bones = fighter->x5E8_fighterBones;
    func_8000C1C0(bones[5].x0_jobj, bones[17].x0_jobj);
    bones = fighter->x5E8_fighterBones;
    func_8000C1C0(bones[5].x4_jobj2, bones[17].x4_jobj2);
    bones = fighter->x5E8_fighterBones;
    func_8000C228(bones[7].x0_jobj, bones[37].x0_jobj);
    bones = fighter->x5E8_fighterBones;
    func_8000C228(bones[7].x4_jobj2, bones[37].x4_jobj2);

    func_8000C420(fighter->x5E8_fighterBones[7].x0_jobj, 1, -1.57079637f);
    func_8000C420(fighter->x5E8_fighterBones[7].x0_jobj, 2, -1.57079637f);
    func_8000C420(fighter->x5E8_fighterBones[7].x4_jobj2, 1, -1.57079637f);
    func_8000C420(fighter->x5E8_fighterBones[7].x4_jobj2, 2, -1.57079637f);

    bones = fighter->x5E8_fighterBones;
    func_8000C228(bones[6].x0_jobj, bones[5].x0_jobj);
    bones = fighter->x5E8_fighterBones;
    func_8000C228(bones[6].x4_jobj2, bones[5].x4_jobj2);

    func_8000C420(fighter->x5E8_fighterBones[6].x0_jobj, 1, -1.50098311f);
    func_8000C420(fighter->x5E8_fighterBones[6].x0_jobj, 2, -1.50098311f);
    func_8000C420(fighter->x5E8_fighterBones[6].x4_jobj2, 1, -1.50098311f);
    func_8000C420(fighter->x5E8_fighterBones[6].x4_jobj2, 2, -1.50098311f);
}

u32 func_8014FB78(HSD_GObj* gobj)
{
    Fighter* fighter = gobj->user_data;
    ftData* fighter_data = fighter->x10C_ftData;

    ftSandbagAttributes *special_attr = (ftSandbagAttributes *)fighter->x2D4_specialAttributes;

    ftSandbagAttributes* ext_attr = (ftSandbagAttributes *)fighter_data->ext_attr;

    s32 ext_attr_first = ext_attr->x0_pair[0];
    s32 ext_attr_second = ext_attr->x0_pair[1];

    special_attr->x0_pair[0] = ext_attr_first;
    special_attr->x0_pair[1] = ext_attr_second;

    return ext_attr_first;
}

void ftSandbag_OnKnockbackEnter(void) {
    return;
}

void ftSandbag_OnKnockbackExit(void) {
    return;
}

void func_8014FBA4(HSD_GObj* gobj)
{
    f32 temp_f1;

    Fighter* fighter = gobj->user_data;
    if ((s32) fighter->xE0_ground_or_air == GA_Air) {
        func_8007D7FC(fighter);
    }

    Fighter_ActionStateChange_800693AC(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8007EFC0(fighter, p_ftCommonData->x5F0);
}

void func_8014FC20(void) {
    return;
}

void func_8014FC24(void) {
    return;
}

void func_8014FC28(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void func_8014FC48(HSD_GObj* gobj)
{
    func_80083F88(gobj);
}
