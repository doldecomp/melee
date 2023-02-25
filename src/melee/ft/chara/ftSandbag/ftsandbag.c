#include <melee/ft/chara/ftSandbag/ftsandbag.h>

#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/types.h>
#include <melee/lb/lbunknown_001.h>

ActionState as_table_sandbag[] = {
    { 295, FLAGS_ZERO, 0x01400000, func_8014FC20, func_8014FC24, func_8014FC28,
      func_8014FC48, func_800761C8 },
};

char lbl_803D39B8[] = "PlSb.dat";
char lbl_803D39C4[] = "ftDataSandbag";
char lbl_803D39D4[] = "PlSbNr.dat";
char lbl_803D39E0[] = "PlySandbag_Share_joint";
char lbl_803D39F8[] = "PlySandbag_Share_matanim_joint";
char lbl_803D3A18[] = "PlSbAJ.dat";

Fighter_CostumeStrings lbl_803D3A24[] = {
    { lbl_803D39D4, lbl_803D39E0, lbl_803D39F8 },
};

typedef struct _ftSandbagAttributes {
    u32 x0_pair[2];
} ftSandbagAttributes;

void ftSandbag_OnDeath(HSD_GObj* arg0) {}

void ftSandbag_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PUSH_ATTRS(fp, ftSandbagAttributes);

    fp->x2228_flag.bits.b2 = 1;
    fp->x2226_flag.bits.b0 = 1;

    func_8014FA30(fp);
}

void func_8014FA30(Fighter* fp)
{
    FighterBone* bones = fp->x5E8_fighterBones;
    func_8000C1C0(bones[5].x0_jobj, bones[12].x0_jobj);
    bones = fp->x5E8_fighterBones;
    func_8000C1C0(bones[5].x4_jobj2, bones[12].x4_jobj2);
    bones = fp->x5E8_fighterBones;
    func_8000C1C0(bones[5].x0_jobj, bones[17].x0_jobj);
    bones = fp->x5E8_fighterBones;
    func_8000C1C0(bones[5].x4_jobj2, bones[17].x4_jobj2);
    bones = fp->x5E8_fighterBones;
    func_8000C228(bones[7].x0_jobj, bones[37].x0_jobj);
    bones = fp->x5E8_fighterBones;
    func_8000C228(bones[7].x4_jobj2, bones[37].x4_jobj2);

    func_8000C420(fp->x5E8_fighterBones[7].x0_jobj, 1, -1.57079637f);
    func_8000C420(fp->x5E8_fighterBones[7].x0_jobj, 2, -1.57079637f);
    func_8000C420(fp->x5E8_fighterBones[7].x4_jobj2, 1, -1.57079637f);
    func_8000C420(fp->x5E8_fighterBones[7].x4_jobj2, 2, -1.57079637f);

    bones = fp->x5E8_fighterBones;
    func_8000C228(bones[6].x0_jobj, bones[5].x0_jobj);
    bones = fp->x5E8_fighterBones;
    func_8000C228(bones[6].x4_jobj2, bones[5].x4_jobj2);

    func_8000C420(fp->x5E8_fighterBones[6].x0_jobj, 1, -1.50098311f);
    func_8000C420(fp->x5E8_fighterBones[6].x0_jobj, 2, -1.50098311f);
    func_8000C420(fp->x5E8_fighterBones[6].x4_jobj2, 1, -1.50098311f);
    func_8000C420(fp->x5E8_fighterBones[6].x4_jobj2, 2, -1.50098311f);
}

void ftSandbag_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSandbagAttributes);
}

void ftSandbag_OnKnockbackEnter(HSD_GObj* arg0) {}

void ftSandbag_OnKnockbackExit(HSD_GObj* arg0) {}

void func_8014FBA4(HSD_GObj* gobj)
{
    f32 temp_f1;

    Fighter* fp = gobj->user_data;
    if ((s32) fp->xE0_ground_or_air == GA_Air) {
        func_8007D7FC(fp);
    }

    Fighter_ActionStateChange_800693AC(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8007EFC0(fp, p_ftCommonData->x5F0);
}

void func_8014FC20(HSD_GObj* arg0) {}

void func_8014FC24(HSD_GObj* arg0) {}

void func_8014FC28(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void func_8014FC48(HSD_GObj* gobj)
{
    func_80083F88(gobj);
}
