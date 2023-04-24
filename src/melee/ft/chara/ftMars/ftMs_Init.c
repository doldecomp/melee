#include "forward.h"
#include "ft/forward.h"

#include "ftMs_Init.h"

#include "ftMs_SpecialHi.h"
#include "ftMs_SpecialLw.h"
#include "ftMs_SpecialN.h"
#include "ftMs_SpecialS.h"

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
    {
        295,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNChargeStart_Anim,
        ftMs_SpecialNChargeStart_IASA,
        ftMs_SpecialNChargeStart_Phys,
        ftMs_SpecialNChargeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNChargeLoop_Anim,
        ftMs_SpecialNChargeLoop_IASA,
        ftMs_SpecialNChargeLoop_Phys,
        ftMs_SpecialNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNChargeEnd_Anim,
        ftMs_SpecialNChargeEnd_IASA,
        ftMs_SpecialNChargeEnd_Phys,
        ftMs_SpecialNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNChargeEnd_Anim,
        ftMs_SpecialNChargeEnd_IASA,
        ftMs_SpecialNChargeEnd_Phys,
        ftMs_SpecialNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNChargeStart_Anim,
        ftMs_SpecialAirNChargeStart_IASA,
        ftMs_SpecialAirNChargeStart_Phys,
        ftMs_SpecialAirNChargeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNChargeLoop_Anim,
        ftMs_SpecialAirNChargeLoop_IASA,
        ftMs_SpecialAirNChargeLoop_Phys,
        ftMs_SpecialAirNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNChargeEnd_Anim,
        ftMs_SpecialAirNChargeEnd_IASA,
        ftMs_SpecialAirNChargeEnd_Phys,
        ftMs_SpecialAirNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNChargeEnd_Anim,
        ftMs_SpecialAirNChargeEnd_IASA,
        ftMs_SpecialAirNChargeEnd_Phys,
        ftMs_SpecialAirNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS1_Anim,
        ftMs_SpecialS1_IASA,
        ftMs_SpecialS1_Phys,
        ftMs_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        311,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        312,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS1_Anim,
        ftMs_SpecialS1_IASA,
        ftMs_SpecialS1_Phys,
        ftMs_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        313,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        315,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        316,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        317,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        318,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        319,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        320,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        321,
        ftMs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftMs_SpecialHi_Anim,
        ftMs_SpecialHi_IASA,
        ftMs_SpecialHi_Phys,
        ftMs_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        322,
        ftMs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftMs_SpecialAirHi_Anim,
        ftMs_SpecialAirHi_IASA,
        ftMs_SpecialAirHi_Phys,
        ftMs_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        323,
        ftMs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialLw_Anim,
        ftMs_SpecialLw_IASA,
        ftMs_SpecialLw_Phys,
        ftMs_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        324,
        ftMs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialLwHit_Anim,
        ftMs_SpecialLwHit_IASA,
        ftMs_SpecialLwHit_Phys,
        ftMs_SpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        325,
        ftMs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialAirLw_Anim,
        ftMs_SpecialAirLw_IASA,
        ftMs_SpecialAirLw_Phys,
        ftMs_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        326,
        ftMs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialAirLwHit_Anim,
        ftMs_SpecialAirLwHit_IASA,
        ftMs_SpecialAirLwHit_Phys,
        ftMs_SpecialAirLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
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
void ftMs_Init_OnLoadForRoy(Fighter* fp)
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
void ftMs_SpecialN_801365A8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = ftLib_800872A4(gobj);
        switch (result) {
        case 18:
            efSync_Spawn(1266, gobj, fp->parts->x0_jobj);
            break;
        case 26:
            efSync_Spawn(1297, gobj, fp->parts->x0_jobj);
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
void ftMs_SpecialN_8013666C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = ftLib_800872A4(gobj);
        switch (result) {
        case 18:
            efSync_Spawn(1267, gobj, fp->parts->x0_jobj);
            break;
        case 26:
            efSync_Spawn(1298, gobj, fp->parts->x0_jobj);
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
void ftMs_SpecialN_80136730(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.ms.specialn.x0 = 0;
}
