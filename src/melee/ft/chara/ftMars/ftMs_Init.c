#include "ftMs_Init.h"

#include "ftMs_SpecialHi.h"
#include "ftMs_SpecialLw.h"
#include "ftMs_SpecialN.h"
#include "ftMs_SpecialS.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"

#include "forward.h"

#include "ft/ftcamera.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftMars/types.h"

MotionState ftMs_Init_MotionStateTable[ftMs_MS_SelfCount] = {
    {
        // ftMs_MS_SpecialNStart = 341
        ftMs_SM_SpecialNStart,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNStart_Anim,
        ftMs_SpecialNStart_IASA,
        ftMs_SpecialNStart_Phys,
        ftMs_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialNLoop = 342
        ftMs_SM_SpecialNLoop,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNLoop_Anim,
        ftMs_SpecialNLoop_IASA,
        ftMs_SpecialNLoop_Phys,
        ftMs_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialNEnd0 = 343
        ftMs_SM_SpecialNEnd0,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNEnd_Anim,
        ftMs_SpecialNEnd_IASA,
        ftMs_SpecialNEnd_Phys,
        ftMs_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialNEnd1 = 344
        ftMs_SM_SpecialNEnd1,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNEnd_Anim,
        ftMs_SpecialNEnd_IASA,
        ftMs_SpecialNEnd_Phys,
        ftMs_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirNStart = 345
        ftMs_SM_SpecialAirNStart,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNStart_Anim,
        ftMs_SpecialAirNStart_IASA,
        ftMs_SpecialAirNStart_Phys,
        ftMs_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirNLoop = 346
        ftMs_SM_SpecialAirNLoop,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNLoop_Anim,
        ftMs_SpecialAirNLoop_IASA,
        ftMs_SpecialAirNLoop_Phys,
        ftMs_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirNEnd0 = 347
        ftMs_SM_SpecialAirNEnd0,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNEnd_Anim,
        ftMs_SpecialAirNEnd_IASA,
        ftMs_SpecialAirNEnd_Phys,
        ftMs_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirNEnd1 = 348
        ftMs_SM_SpecialAirNEnd1,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNEnd_Anim,
        ftMs_SpecialAirNEnd_IASA,
        ftMs_SpecialAirNEnd_Phys,
        ftMs_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS1 = 349
        ftMs_SM_SpecialS1,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialAirS1_Anim,
        ftMs_SpecialAirS1_IASA,
        ftMs_SpecialAirS1_Phys,
        ftMs_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS2Hi = 350
        ftMs_SM_SpecialS2Hi,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS2Lw = 351
        ftMs_SM_SpecialS2Lw,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS3Hi = 352
        ftMs_SM_SpecialS3Hi,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS3S = 353
        ftMs_SM_SpecialS3S,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS3Lw = 354
        ftMs_SM_SpecialS3Lw,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS4Hi = 355
        ftMs_SM_SpecialS4Hi,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS4S = 356
        ftMs_SM_SpecialS4S,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS4Lw = 357
        ftMs_SM_SpecialS4Lw,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS1 = 358
        ftMs_SM_SpecialAirS1,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialAirS1_Anim,
        ftMs_SpecialAirS1_IASA,
        ftMs_SpecialAirS1_Phys,
        ftMs_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS2Hi = 359
        ftMs_SM_SpecialAirS2Hi,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS2Lw = 360
        ftMs_SM_SpecialAirS2Lw,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS3Hi = 361
        ftMs_SM_SpecialAirS3Hi,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS3S = 362
        ftMs_SM_SpecialAirS3S,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS3Lw = 363
        ftMs_SM_SpecialAirS3Lw,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS4Hi = 364
        ftMs_SM_SpecialAirS4Hi,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS4S = 365
        ftMs_SM_SpecialAirS4S,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS4Lw = 366
        ftMs_SM_SpecialAirS4Lw,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialHi = 367
        ftMs_SM_SpecialHi,
        ftMs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftMs_SpecialHi_Anim,
        ftMs_SpecialHi_IASA,
        ftMs_SpecialHi_Phys,
        ftMs_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirHi = 368
        ftMs_SM_SpecialAirHi,
        ftMs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftMs_SpecialAirHi_Anim,
        ftMs_SpecialAirHi_IASA,
        ftMs_SpecialAirHi_Phys,
        ftMs_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialLw = 369
        ftMs_SM_SpecialLw,
        ftMs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialLw_Anim,
        ftMs_SpecialLw_IASA,
        ftMs_SpecialLw_Phys,
        ftMs_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialLwHit = 370
        ftMs_SM_SpecialLwHit,
        ftMs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialLwHit_Anim,
        ftMs_SpecialLwHit_IASA,
        ftMs_SpecialLwHit_Phys,
        ftMs_SpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirLw = 371
        ftMs_SM_SpecialAirLw,
        ftMs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialAirLw_Anim,
        ftMs_SpecialAirLw_IASA,
        ftMs_SpecialAirLw_Phys,
        ftMs_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirLwHit = 372
        ftMs_SM_SpecialAirLwHit,
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

/// 80136258 00132E38
/// https://decomp.me/scratch/6RQ5w
void ftMs_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    fp->fv.ms.x222C = 0;
}

/// 801362B0 00132E90
/// ftMs_Init_OnItemPickup
void ftMs_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 0, 1);
}

/// 80136390 00132F70
/// ftMs_Init_OnItemInvisible
/// https://decomp.me/scratch/BksNr
void ftMs_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

/// 801363D8 00132FB8
/// ftMs_Init_OnItemVisible
/// https://decomp.me/scratch/9zuEy
void ftMs_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

/// 80136420 00133000
/// ftMs_Init_OnItemDrop
/// https://decomp.me/scratch/Ws8ow
void ftMs_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 0, 1);
}

/// 80136474 00133054
/// https://decomp.me/scratch/2TlGi
void ftMs_Init_OnLoadForRoy(Fighter* fp)
{
    PUSH_ATTRS(fp, MarsAttributes);
}

/// 801364AC 0013308C
/// https://decomp.me/scratch/9UJHY
void ftMs_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PUSH_ATTRS(fp, MarsAttributes);
}

/// 801364E8 001330C8
/// https://decomp.me/scratch/tfzFL
void ftMs_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, MarsAttributes);
}

/// 80136520 00133100
/// ftMs_Init_OnKnockbackEnter
/// https://decomp.me/scratch/rgfFA
void ftMs_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

/// 80136564 00133144
/// https://decomp.me/scratch/Jqd2A
void ftMs_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

/// 801365A8 00133188
/// https://decomp.me/scratch/Jqd2A
void ftMs_SpecialN_801365A8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_b0) {
        result = ftLib_800872A4(gobj);
        switch (result) {
        case 18:
            efSync_Spawn(1266, gobj, fp->parts->joint);
            break;
        case 26:
            efSync_Spawn(1297, gobj, fp->parts->joint);
            break;
        }
        fp->x2219_b0 = 1;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = 0;
    return;
}

/// 8013666C 0013324C
/// https://decomp.me/scratch/Jqd2A
void ftMs_SpecialN_8013666C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_b0) {
        result = ftLib_800872A4(gobj);
        switch (result) {
        case 18:
            efSync_Spawn(1267, gobj, fp->parts->joint);
            break;
        case 26:
            efSync_Spawn(1298, gobj, fp->parts->joint);
            break;
        }
        fp->x2219_b0 = 1;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = 0;
    return;
}

/// 80136730 00133310
/// https://decomp.me/scratch/Jqd2A
void ftMs_SpecialN_80136730(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->cmd_vars[0] = 0;
    fp->mv.ms.specialn.cur_frame = 0;
}
