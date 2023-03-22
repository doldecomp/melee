#include "ftMars.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <common_structs.h>

MotionState ftMars_MotionStateTable[] = {
    { 295, 0x00340211, 0x12000000, ftMars_80136844, ftMars_80136914,
      ftMars_8013691C, ftMars_801369A4, Fighter_UpdateCameraBox },
    { 296, 0x00340211, 0x12000000, ftMars_80136ADC, ftMars_80136C8C,
      ftMars_80136CFC, ftMars_80136D3C, Fighter_UpdateCameraBox },
    { 297, 0x00340211, 0x12000000, ftMars_80136EE4, ftMars_8013713C,
      ftMars_80137144, ftMars_80137184, Fighter_UpdateCameraBox },
    { 298, 0x00340211, 0x12000000, ftMars_80136EE4, ftMars_8013713C,
      ftMars_80137144, ftMars_80137184, Fighter_UpdateCameraBox },
    { 299, 0x00340611, 0x12000000, ftMars_801368AC, ftMars_80136918,
      ftMars_8013695C, ftMars_801369E0, Fighter_UpdateCameraBox },
    { 300, 0x00340611, 0x12000000, ftMars_80136BB4, ftMars_80136CC4,
      ftMars_80136D1C, ftMars_80136D78, Fighter_UpdateCameraBox },
    { 301, 0x00340611, 0x12000000, ftMars_80137010, ftMars_80137140,
      ftMars_80137164, ftMars_801371C0, Fighter_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftMars_80137010, ftMars_80137140,
      ftMars_80137164, ftMars_801371C0, Fighter_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftMars_80137558, ftMars_801375B8,
      ftMars_80137618, ftMars_8013767C, Fighter_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, Fighter_UpdateCameraBox },
    { 305, 0x00340212, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, Fighter_UpdateCameraBox },
    { 306, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, Fighter_UpdateCameraBox },
    { 307, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, Fighter_UpdateCameraBox },
    { 308, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, Fighter_UpdateCameraBox },
    { 309, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, Fighter_UpdateCameraBox },
    { 310, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, Fighter_UpdateCameraBox },
    { 311, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, Fighter_UpdateCameraBox },
    { 312, 0x00340612, 0x13000000, ftMars_80137558, ftMars_801375B8,
      ftMars_80137618, ftMars_8013767C, Fighter_UpdateCameraBox },
    { 313, 0x00340612, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, Fighter_UpdateCameraBox },
    { 314, 0x00340612, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, Fighter_UpdateCameraBox },
    { 315, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, Fighter_UpdateCameraBox },
    { 316, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, Fighter_UpdateCameraBox },
    { 317, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, Fighter_UpdateCameraBox },
    { 318, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, Fighter_UpdateCameraBox },
    { 319, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, Fighter_UpdateCameraBox },
    { 320, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, Fighter_UpdateCameraBox },
    { 321, 0x00340213, 0x14000000, ftMars_801382E8, ftMars_801383A8,
      ftMars_80138638, ftMars_801388B4, Fighter_UpdateCameraBox },
    { 322, 0x00340613, 0x14000000, ftMars_80138348, ftMars_801384F0,
      ftMars_8013873C, ftMars_80138940, Fighter_UpdateCameraBox },
    { 323, 0x00340214, 0x15000000, ftMars_80138AA8, ftMars_80138C20,
      ftMars_80138C28, ftMars_80138CC0, Fighter_UpdateCameraBox },
    { 324, 0x00340214, 0x15000000, ftMars_80138E68, ftMars_80138FC0,
      ftMars_80138FC8, ftMars_80139008, Fighter_UpdateCameraBox },
    { 325, 0x00340614, 0x15000000, ftMars_80138B64, ftMars_80138C24,
      ftMars_80138C5C, ftMars_80138CFC, Fighter_UpdateCameraBox },
    { 326, 0x00340614, 0x15000000, ftMars_80138F14, ftMars_80138FC4,
      ftMars_80138FE8, ftMars_80139044, Fighter_UpdateCameraBox },
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
    fp->fv.ms.x222C = 0;
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
void ftMars_801365A8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = func_800872A4(gobj);
        switch (result) {
        case 0x12:
            ef_Spawn(0x4F2, gobj, fp->ft_bones->x0_jobj);
            break;
        case 0x1A:
            ef_Spawn(0x511, gobj, fp->ft_bones->x0_jobj);
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
void ftMars_8013666C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = func_800872A4(gobj);
        switch (result) {
        case 0x12:
            ef_Spawn(0x4F3, gobj, fp->ft_bones->x0_jobj);
            break;
        case 0x1A:
            ef_Spawn(0x512, gobj, fp->ft_bones->x0_jobj);
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
void ftMars_80136730(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.ms.specialn.x0 = 0;
}
