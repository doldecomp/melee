#include "ftMars.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <common_structs.h>

MotionState ftMs_Init_MotionStateTable[] = {
    { 295, 0x00340211, 0x12000000, ftMs_SpecialN_80136844,
      ftMs_SpecialN_80136914, ftMs_SpecialN_8013691C, ftMs_SpecialN_801369A4,
      ftCamera_UpdateCameraBox },
    { 296, 0x00340211, 0x12000000, ftMs_SpecialN_80136ADC,
      ftMs_SpecialN_80136C8C, ftMs_SpecialN_80136CFC, ftMs_SpecialN_80136D3C,
      ftCamera_UpdateCameraBox },
    { 297, 0x00340211, 0x12000000, ftMs_SpecialN_80136EE4,
      ftMs_SpecialN_8013713C, ftMs_SpecialN_80137144, ftMs_SpecialN_80137184,
      ftCamera_UpdateCameraBox },
    { 298, 0x00340211, 0x12000000, ftMs_SpecialN_80136EE4,
      ftMs_SpecialN_8013713C, ftMs_SpecialN_80137144, ftMs_SpecialN_80137184,
      ftCamera_UpdateCameraBox },
    { 299, 0x00340611, 0x12000000, ftMs_SpecialN_801368AC,
      ftMs_SpecialN_80136918, ftMs_SpecialN_8013695C, ftMs_SpecialN_801369E0,
      ftCamera_UpdateCameraBox },
    { 300, 0x00340611, 0x12000000, ftMs_SpecialN_80136BB4,
      ftMs_SpecialN_80136CC4, ftMs_SpecialN_80136D1C, ftMs_SpecialN_80136D78,
      ftCamera_UpdateCameraBox },
    { 301, 0x00340611, 0x12000000, ftMs_SpecialN_80137010,
      ftMs_SpecialN_80137140, ftMs_SpecialN_80137164, ftMs_SpecialN_801371C0,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftMs_SpecialN_80137010,
      ftMs_SpecialN_80137140, ftMs_SpecialN_80137164, ftMs_SpecialN_801371C0,
      ftCamera_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftMs_SpecialS_80137558,
      ftMs_SpecialS_801375B8, ftMs_SpecialS_80137618, ftMs_SpecialS_8013767C,
      ftCamera_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftMs_SpecialS_801377B0,
      ftMs_SpecialS_80137810, ftMs_SpecialS_80137870, ftMs_SpecialS_801378D4,
      ftCamera_UpdateCameraBox },
    { 305, 0x00340212, 0x13000000, ftMs_SpecialS_801377B0,
      ftMs_SpecialS_80137810, ftMs_SpecialS_80137870, ftMs_SpecialS_801378D4,
      ftCamera_UpdateCameraBox },
    { 306, 0x00340212, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 307, 0x00340212, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 308, 0x00340212, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 309, 0x00340212, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 310, 0x00340212, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 311, 0x00340212, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 312, 0x00340612, 0x13000000, ftMs_SpecialS_80137558,
      ftMs_SpecialS_801375B8, ftMs_SpecialS_80137618, ftMs_SpecialS_8013767C,
      ftCamera_UpdateCameraBox },
    { 313, 0x00340612, 0x13000000, ftMs_SpecialS_801377B0,
      ftMs_SpecialS_80137810, ftMs_SpecialS_80137870, ftMs_SpecialS_801378D4,
      ftCamera_UpdateCameraBox },
    { 314, 0x00340612, 0x13000000, ftMs_SpecialS_801377B0,
      ftMs_SpecialS_80137810, ftMs_SpecialS_80137870, ftMs_SpecialS_801378D4,
      ftCamera_UpdateCameraBox },
    { 315, 0x00340612, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 316, 0x00340612, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 317, 0x00340612, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 318, 0x00340612, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 319, 0x00340612, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 320, 0x00340612, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 321, 0x00340213, 0x14000000, ftMs_SpecialHi_801382E8,
      ftMs_SpecialHi_801383A8, ftMs_SpecialHi_80138638,
      ftMs_SpecialHi_801388B4, ftCamera_UpdateCameraBox },
    { 322, 0x00340613, 0x14000000, ftMs_SpecialHi_80138348,
      ftMs_SpecialHi_801384F0, ftMs_SpecialHi_8013873C,
      ftMs_SpecialHi_80138940, ftCamera_UpdateCameraBox },
    { 323, 0x00340214, 0x15000000, ftMs_SpecialLw_80138AA8,
      ftMs_SpecialLw_80138C20, ftMs_SpecialLw_80138C28,
      ftMs_SpecialLw_80138CC0, ftCamera_UpdateCameraBox },
    { 324, 0x00340214, 0x15000000, ftMs_SpecialLw_80138E68,
      ftMs_SpecialLw_80138FC0, ftMs_SpecialLw_80138FC8,
      ftMs_SpecialLw_80139008, ftCamera_UpdateCameraBox },
    { 325, 0x00340614, 0x15000000, ftMs_SpecialLw_80138B64,
      ftMs_SpecialLw_80138C24, ftMs_SpecialLw_80138C5C,
      ftMs_SpecialLw_80138CFC, ftCamera_UpdateCameraBox },
    { 326, 0x00340614, 0x15000000, ftMs_SpecialLw_80138F14,
      ftMs_SpecialLw_80138FC4, ftMs_SpecialLw_80138FE8,
      ftMs_SpecialLw_80139044, ftCamera_UpdateCameraBox },
};

char ftMs_Init_DatFilename[] = "PlMs.dat";
char ftMs_Init_DataName[] = "ftDataMars";
char ftMs_Init_803CF838[] = "PlMsNr.dat";
char ftMs_Init_803CF844[] = "PlyMars5K_Share_joint";
char ftMs_Init_803CF85C[] = "PlyMars5K_Share_matanim_joint";
char ftMs_Init_803CF87C[] = "PlMsRe.dat";
char ftMs_Init_803CF888[] = "PlyMars5KRe_Share_joint";
char ftMs_Init_803CF8A0[] = "PlyMars5KRe_Share_matanim_joint";
char ftMs_Init_803CF8C0[] = "PlMsGr.dat";
char ftMs_Init_803CF8CC[] = "PlyMars5KGr_Share_joint";
char ftMs_Init_803CF8E4[] = "PlyMars5KGr_Share_matanim_joint";
char ftMs_Init_803CF904[] = "PlMsBk.dat";
char ftMs_Init_803CF910[] = "PlyMars5KBk_Share_joint";
char ftMs_Init_803CF928[] = "PlyMars5KBk_Share_matanim_joint";
char ftMs_Init_803CF948[] = "PlMsWh.dat";
char ftMs_Init_803CF954[] = "PlyMars5KWh_Share_joint";
char ftMs_Init_803CF96C[] = "PlyMars5KWh_Share_matanim_joint";
char ftMs_Init_AnimDatFilename[] = "PlMsAJ.dat";

Fighter_DemoStrings ftMs_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileMars",
    "ftDemoIntroMotionFileMars",
    "ftDemoEndingMotionFileMars",
    "ftDemoViWaitMotionFileMars",
};

Fighter_CostumeStrings ftMs_Init_CostumeStrings[] = {
    { ftMs_Init_803CF838, ftMs_Init_803CF844, ftMs_Init_803CF85C },
    { ftMs_Init_803CF87C, ftMs_Init_803CF888, ftMs_Init_803CF8A0 },
    { ftMs_Init_803CF8C0, ftMs_Init_803CF8CC, ftMs_Init_803CF8E4 },
    { ftMs_Init_803CF904, ftMs_Init_803CF910, ftMs_Init_803CF928 },
    { ftMs_Init_803CF948, ftMs_Init_803CF954, ftMs_Init_803CF96C },
};

// 80136258 00132E38
// https://decomp.me/scratch/6RQ5w
void ftMs_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    fp->fv.ms.x222C = 0;
}

// 801362B0 00132E90
// ftMs_Init_OnItemPickup
void ftMs_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 1);
}

// 80136390 00132F70
// ftMs_Init_OnItemInvisible
// https://decomp.me/scratch/BksNr
void ftMs_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

// 801363D8 00132FB8
// ftMs_Init_OnItemVisible
// https://decomp.me/scratch/9zuEy
void ftMs_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

// 80136420 00133000
// ftMs_Init_OnItemDrop
// https://decomp.me/scratch/Ws8ow
void ftMs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 1);
}

// 80136474 00133054
// https://decomp.me/scratch/2TlGi
void ftMs_OnLoadForRoy(Fighter* fp)
{
    PUSH_ATTRS(fp, MarsAttributes);
}

// 801364AC 0013308C
// https://decomp.me/scratch/9UJHY
void ftMs_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PUSH_ATTRS(fp, MarsAttributes);
}

// 801364E8 001330C8
// https://decomp.me/scratch/tfzFL
void ftMs_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, MarsAttributes);
}

// 80136520 00133100
// ftMs_Init_OnKnockbackEnter
// https://decomp.me/scratch/rgfFA
void ftMs_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

// 80136564 00133144
// https://decomp.me/scratch/Jqd2A
void ftMs_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

// 801365A8 00133188
// https://decomp.me/scratch/Jqd2A
void ftMs_Init_801365A8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = ftLib_800872A4(gobj);
        switch (result) {
        case 0x12:
            efSync_Spawn(0x4F2, gobj, fp->ft_bones->x0_jobj);
            break;
        case 0x1A:
            efSync_Spawn(0x511, gobj, fp->ft_bones->x0_jobj);
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
void ftMs_Init_8013666C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = ftLib_800872A4(gobj);
        switch (result) {
        case 0x12:
            efSync_Spawn(0x4F3, gobj, fp->ft_bones->x0_jobj);
            break;
        case 0x1A:
            efSync_Spawn(0x512, gobj, fp->ft_bones->x0_jobj);
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
void ftMs_Init_80136730(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.ms.specialn.x0 = 0;
}
