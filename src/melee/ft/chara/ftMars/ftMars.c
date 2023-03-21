#include "ftMars.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include <common_structs.h>

ActionState as_table_mars[] = {
    { 295, 0x00340211, 0x12000000, lbl_80136844, lbl_80136914, lbl_8013691C,
      lbl_801369A4, func_800761C8 },
    { 296, 0x00340211, 0x12000000, lbl_80136ADC, lbl_80136C8C, lbl_80136CFC,
      lbl_80136D3C, func_800761C8 },
    { 297, 0x00340211, 0x12000000, lbl_80136EE4, lbl_8013713C, lbl_80137144,
      lbl_80137184, func_800761C8 },
    { 298, 0x00340211, 0x12000000, lbl_80136EE4, lbl_8013713C, lbl_80137144,
      lbl_80137184, func_800761C8 },
    { 299, 0x00340611, 0x12000000, lbl_801368AC, lbl_80136918, lbl_8013695C,
      lbl_801369E0, func_800761C8 },
    { 300, 0x00340611, 0x12000000, lbl_80136BB4, lbl_80136CC4, lbl_80136D1C,
      lbl_80136D78, func_800761C8 },
    { 301, 0x00340611, 0x12000000, lbl_80137010, lbl_80137140, lbl_80137164,
      lbl_801371C0, func_800761C8 },
    { 302, 0x00340611, 0x12000000, lbl_80137010, lbl_80137140, lbl_80137164,
      lbl_801371C0, func_800761C8 },
    { 303, 0x00340212, 0x13000000, ftMars_80137558, ftMars_801375B8,
      ftMars_80137618, ftMars_8013767C, func_800761C8 },
    { 304, 0x00340212, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, func_800761C8 },
    { 305, 0x00340212, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, func_800761C8 },
    { 306, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, func_800761C8 },
    { 307, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, func_800761C8 },
    { 308, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, func_800761C8 },
    { 309, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, func_800761C8 },
    { 310, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, func_800761C8 },
    { 311, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, func_800761C8 },
    { 312, 0x00340612, 0x13000000, ftMars_80137558, ftMars_801375B8,
      ftMars_80137618, ftMars_8013767C, func_800761C8 },
    { 313, 0x00340612, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, func_800761C8 },
    { 314, 0x00340612, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, func_800761C8 },
    { 315, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, func_800761C8 },
    { 316, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, func_800761C8 },
    { 317, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, func_800761C8 },
    { 318, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, func_800761C8 },
    { 319, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, func_800761C8 },
    { 320, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, func_800761C8 },
    { 321, 0x00340213, 0x14000000, lbl_801382E8, lbl_801383A8, lbl_80138638,
      lbl_801388B4, func_800761C8 },
    { 322, 0x00340613, 0x14000000, lbl_80138348, lbl_801384F0, lbl_8013873C,
      lbl_80138940, func_800761C8 },
    { 323, 0x00340214, 0x15000000, lbl_80138AA8, lbl_80138C20, lbl_80138C28,
      lbl_80138CC0, func_800761C8 },
    { 324, 0x00340214, 0x15000000, lbl_80138E68, lbl_80138FC0, lbl_80138FC8,
      lbl_80139008, func_800761C8 },
    { 325, 0x00340614, 0x15000000, lbl_80138B64, lbl_80138C24, lbl_80138C5C,
      lbl_80138CFC, func_800761C8 },
    { 326, 0x00340614, 0x15000000, lbl_80138F14, lbl_80138FC4, lbl_80138FE8,
      lbl_80139044, func_800761C8 },
};

char lbl_803CF820[] = "PlMs.dat";
char lbl_803CF82C[] = "ftDataMars";
char lbl_803CF838[] = "PlMsNr.dat";
char lbl_803CF844[] = "PlyMars5K_Share_joint";
char lbl_803CF85C[] = "PlyMars5K_Share_matanim_joint";
char lbl_803CF87C[] = "PlMsRe.dat";
char lbl_803CF888[] = "PlyMars5KRe_Share_joint";
char lbl_803CF8A0[] = "PlyMars5KRe_Share_matanim_joint";
char lbl_803CF8C0[] = "PlMsGr.dat";
char lbl_803CF8CC[] = "PlyMars5KGr_Share_joint";
char lbl_803CF8E4[] = "PlyMars5KGr_Share_matanim_joint";
char lbl_803CF904[] = "PlMsBk.dat";
char lbl_803CF910[] = "PlyMars5KBk_Share_joint";
char lbl_803CF928[] = "PlyMars5KBk_Share_matanim_joint";
char lbl_803CF948[] = "PlMsWh.dat";
char lbl_803CF954[] = "PlyMars5KWh_Share_joint";
char lbl_803CF96C[] = "PlyMars5KWh_Share_matanim_joint";
char lbl_803CF98C[] = "PlMsAJ.dat";

Fighter_DemoStrings lbl_803CFA08 = {
    "ftDemoResultMotionFileMars",
    "ftDemoIntroMotionFileMars",
    "ftDemoEndingMotionFileMars",
    "ftDemoViWaitMotionFileMars",
};

Fighter_CostumeStrings lbl_803CFA18[] = {
    { lbl_803CF838, lbl_803CF844, lbl_803CF85C },
    { lbl_803CF87C, lbl_803CF888, lbl_803CF8A0 },
    { lbl_803CF8C0, lbl_803CF8CC, lbl_803CF8E4 },
    { lbl_803CF904, lbl_803CF910, lbl_803CF928 },
    { lbl_803CF948, lbl_803CF954, lbl_803CF96C },
};

// 80136258 00132E38
// https://decomp.me/scratch/6RQ5w
void ftMars_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    fp->ev.ms.x222C = 0;
}

// 801362B0 00132E90
// ftMars_OnItemPickup
void ftMars_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 1);
}

// 80136390 00132F70
// ftMars_OnItemInvisible
// https://decomp.me/scratch/BksNr
void ftMars_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

// 801363D8 00132FB8
// ftMars_OnItemVisible
// https://decomp.me/scratch/9zuEy
void ftMars_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

// 80136420 00133000
// ftMars_OnItemDrop
// https://decomp.me/scratch/Ws8ow
void ftMars_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 1);
}

// 80136474 00133054
// https://decomp.me/scratch/2TlGi
void ftMars_OnLoadForRoy(Fighter* fp)
{
    PUSH_ATTRS(fp, MarsAttributes);
}

// 801364AC 0013308C
// https://decomp.me/scratch/9UJHY
void ftMars_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PUSH_ATTRS(fp, MarsAttributes);
}

// 801364E8 001330C8
// https://decomp.me/scratch/tfzFL
void ftMars_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, MarsAttributes);
}

// 80136520 00133100
// ftMars_OnKnockbackEnter
// https://decomp.me/scratch/rgfFA
void ftMars_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

// 80136564 00133144
// https://decomp.me/scratch/Jqd2A
void ftMars_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

// 801365A8 00133188
// https://decomp.me/scratch/Jqd2A
void lbl_801365A8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = func_800872A4(gobj);
        switch (result) {
        case 0x12:
            ef_Spawn(0x4F2, gobj, fp->x5E8_fighterBones->x0_jobj);
            break;
        case 0x1A:
            ef_Spawn(0x511, gobj, fp->x5E8_fighterBones->x0_jobj);
            break;
        }
        fp->x2219_flag.bits.b0 = 1;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
    return;
}

// 8013666C 0013324C
// https://decomp.me/scratch/Jqd2A
void lbl_8013666C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = func_800872A4(gobj);
        switch (result) {
        case 0x12:
            ef_Spawn(0x4F3, gobj, fp->x5E8_fighterBones->x0_jobj);
            break;
        case 0x1A:
            ef_Spawn(0x512, gobj, fp->x5E8_fighterBones->x0_jobj);
            break;
        }
        fp->x2219_flag.bits.b0 = 1;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
    return;
}

// 80136730 00133310
// https://decomp.me/scratch/Jqd2A
void lbl_80136730(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.ms.specialn.x0 = 0;
}
