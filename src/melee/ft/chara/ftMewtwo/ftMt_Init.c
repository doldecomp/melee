#include <platform.h>

#include "forward.h"
#include "it/forward.h"

#include "ftMt_Init.h"

#include "ftMt_SpecialHi.h"
#include "ftMt_SpecialLw.h"
#include "ftMt_SpecialN.h"
#include "ftMt_SpecialS.h"

#include "ft/ftcamera.h"
#include "ft/ftcolanim.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftMewtwo/types.h"
#include "it/it_26B1.h"

#include <dolphin/mtx.h>

MotionState ftMt_Init_MotionStateTable[ftMt_MS_SelfCount] = {
    {
        // ftMt_MS_SpecialNStart = 341
        ftMt_SM_SpecialNStart,
        ftMt_MF_SpecialNStart,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialNStart_Anim,
        ftMt_SpecialNStart_IASA,
        ftMt_SpecialNStart_Phys,
        ftMt_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialNLoop = 342
        ftMt_SM_SpecialNLoop,
        ftMt_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialNLoop_Anim,
        ftMt_SpecialNLoop_IASA,
        ftMt_SpecialNLoop_Phys,
        ftMt_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialNLoopFull = 343
        ftMt_SM_SpecialNLoopFull,
        ftMt_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialNLoopFull_Anim,
        ftMt_SpecialNLoopFull_IASA,
        ftMt_SpecialNLoopFull_Phys,
        ftMt_SpecialNLoopFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialNCancel = 344
        ftMt_SM_SpecialNCancel,
        ftMt_MF_SpecialNStart,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialNCancel_Anim,
        ftMt_SpecialNCancel_IASA,
        ftMt_SpecialNCancel_Phys,
        ftMt_SpecialNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialNEnd = 345
        ftMt_SM_SpecialNEnd,
        ftMt_MF_SpecialNStart,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialNEnd_Anim,
        ftMt_SpecialNEnd_IASA,
        ftMt_SpecialNEnd_Phys,
        ftMt_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirNStart = 346
        ftMt_SM_SpecialAirNStart,
        ftMt_MF_SpecialAirNStart,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialAirNStart_Anim,
        ftMt_SpecialAirNStart_IASA,
        ftMt_SpecialAirNStart_Phys,
        ftMt_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirNLoop = 347
        ftMt_SM_SpecialAirNLoop,
        ftMt_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialAirNLoop_Anim,
        ftMt_SpecialAirNLoop_IASA,
        ftMt_SpecialAirNLoop_Phys,
        ftMt_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirNLoopFull = 348
        ftMt_SM_SpecialAirNLoopFull,
        ftMt_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialAirNLoopFull_Anim,
        ftMt_SpecialAirNLoopFull_IASA,
        ftMt_SpecialAirNLoopFull_Phys,
        ftMt_SpecialAirNLoopFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirNCancel = 349
        ftMt_SM_SpecialAirNCancel,
        ftMt_MF_SpecialAirNStart,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialAirNCancel_Anim,
        ftMt_SpecialAirNCancel_IASA,
        ftMt_SpecialAirNCancel_Phys,
        ftMt_SpecialAirNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirNEnd = 350
        ftMt_SM_SpecialAirNEnd,
        ftMt_MF_SpecialAirNStart,
        FtMoveId_SpecialN << 24,
        ftMt_SpecialAirNEnd_Anim,
        ftMt_SpecialAirNEnd_IASA,
        ftMt_SpecialAirNEnd_Phys,
        ftMt_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialS = 351
        ftMt_SM_SpecialS,
        ftMt_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMt_SpecialS_Anim,
        ftMt_SpecialS_IASA,
        ftMt_SpecialS_Phys,
        ftMt_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirS = 352
        ftMt_SM_SpecialAirS,
        ftMt_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftMt_SpecialAirS_Anim,
        ftMt_SpecialAirS_IASA,
        ftMt_SpecialAirS_Phys,
        ftMt_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialHiStart = 353
        ftMt_SM_SpecialHiStart,
        ftMt_MF_SpecialHiStart,
        FtMoveId_SpecialHi << 24,
        ftMt_SpecialHiStart_Anim,
        ftMt_SpecialHiStart_IASA,
        ftMt_SpecialHiStart_Phys,
        ftMt_SpecialHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialHiLost = 354
        ftMt_SM_SpecialHiLost,
        ftMt_MF_SpecialHiStart,
        FtMoveId_SpecialHi << 24,
        ftMt_SpecialHiLost_Anim,
        ftMt_SpecialHiLost_IASA,
        ftMt_SpecialHiLost_Phys,
        ftMt_SpecialHiLost_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialHi = 355
        ftMt_SM_SpecialHi,
        ftMt_MF_SpecialHiStart,
        FtMoveId_SpecialHi << 24,
        ftMt_SpecialHi_Anim,
        ftMt_SpecialHi_IASA,
        ftMt_SpecialHi_Phys,
        ftMt_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirHiStart = 356
        ftMt_SM_SpecialAirHiStart,
        ftMt_MF_SpecialAirHiStart,
        FtMoveId_SpecialHi << 24,
        ftMt_SpecialAirHiStart_Anim,
        ftMt_SpecialAirHiStart_IASA,
        ftMt_SpecialAirHiStart_Phys,
        ftMt_SpecialAirHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirHiLost = 357
        ftMt_SM_SpecialHiLost,
        ftMt_MF_SpecialAirHiStart,
        FtMoveId_SpecialHi << 24,
        ftMt_SpecialAirHiLost_Anim,
        ftMt_SpecialAirHiLost_IASA,
        ftMt_SpecialAirHiLost_Phys,
        ftMt_SpecialAirHiLost_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirHi = 358
        ftMt_SM_SpecialAirHi,
        ftMt_MF_SpecialAirHiStart,
        FtMoveId_SpecialHi << 24,
        ftMt_SpecialAirHi_Anim,
        ftMt_SpecialAirHi_IASA,
        ftMt_SpecialAirHi_Phys,
        ftMt_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialLw = 359
        ftMt_SM_SpecialLw,
        ftMt_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMt_SpecialLw_Anim,
        ftMt_SpecialLw_IASA,
        ftMt_SpecialLw_Phys,
        ftMt_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMt_MS_SpecialAirLw = 360
        ftMt_SM_SpecialAirLw,
        ftMt_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftMt_SpecialAirLw_Anim,
        ftMt_SpecialAirLw_IASA,
        ftMt_SpecialAirLw_Phys,
        ftMt_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftMt_Init_DatFilename[] = "PlMt.dat";
char ftMt_Init_DataName[] = "ftDataMewtwo";
char ftMt_Init_803D0D9C[] = "PlMtNr.dat";
char ftMt_Init_803D0DA8[] = "PlyMewtwo5K_Share_joint";
char ftMt_Init_803D0DC0[] = "PlyMewtwo5K_Share_matanim_joint";
char ftMt_Init_803D0DE0[] = "PlMtRe.dat";
char ftMt_Init_803D0DEC[] = "PlyMewtwo5KRe_Share_joint";
char ftMt_Init_803D0E08[] = "PlyMewtwo5KRe_Share_matanim_joint";
char ftMt_Init_803D0E2C[] = "PlMtBu.dat";
char ftMt_Init_803D0E38[] = "PlyMewtwo5KBu_Share_joint";
char ftMt_Init_803D0E54[] = "PlyMewtwo5KBu_Share_matanim_joint";
char ftMt_Init_803D0E78[] = "PlMtGr.dat";
char ftMt_Init_803D0E84[] = "PlyMewtwo5KGr_Share_joint";
char ftMt_Init_803D0EA0[] = "PlyMewtwo5KGr_Share_matanim_joint";
char ftMt_Init_AnimDatFilename[] = "PlMtAJ.dat";

Fighter_DemoStrings ftMt_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileMewtwo",
    "ftDemoIntroMotionFileMewtwo",
    "ftDemoEndingMotionFileMewtwo",
    "ftDemoViWaitMotionFileMewtwo",
};

Fighter_CostumeStrings ftMt_Init_CostumeStrings[] = {
    { ftMt_Init_803D0D9C, ftMt_Init_803D0DA8, ftMt_Init_803D0DC0 },
    { ftMt_Init_803D0DE0, ftMt_Init_803D0DEC, ftMt_Init_803D0E08 },
    { ftMt_Init_803D0E2C, ftMt_Init_803D0E38, ftMt_Init_803D0E54 },
    { ftMt_Init_803D0E78, ftMt_Init_803D0E84, ftMt_Init_803D0EA0 },
};

void ftMt_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.mt.x222C_disableGObj = NULL;
    fp->fv.mt.x2230_shadowHeldGObj = NULL;
    fp->fv.mt.x2234_shadowBallCharge = 0;
    fp->fv.mt.x2238_shadowBallGObj = NULL;
    fp->fv.mt.x223C_isConfusionBoost = false;
}

void ftMt_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftMewtwoAttributes);

    {
        fp->parts[FtPart_TransN].flags_b4 = true;
        fp->x2221_b2 = true;
    }
    it_8026B3F8(item_list[0], It_Kind_Mewtwo_Disable);
    it_8026B3F8(item_list[1], It_Kind_Mewtwo_ShadowBall);
}

void ftMt_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    return;
}

void ftMt_Init_OnDeath2(HSD_GObj* gobj)
{
    ftMt_SpecialLw_RemoveDisable(gobj);
    ftMt_SpecialN_OnTakeDamage(gobj);
}

void ftMt_Init_OnTakeDamage(HSD_GObj* gobj)
{
    ftMt_SpecialLw_RemoveDisable(gobj);
    ftMt_SpecialN_OnDeath(gobj);
}

void ftMt_Init_OnItemDrop(HSD_GObj* gobj, bool flag) {}

void ftMt_Init_OnItemInvisible(HSD_GObj* gobj)
{
    return;
}

void ftMt_Init_OnItemVisible(HSD_GObj* gobj)
{
    return;
}

void ftMt_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* da = fp->dat_attrs;
    float attr_value = da->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;

    if (fp->fv.mt.x2234_shadowBallCharge == attr_value) {
        ftCo_800BFFD0(fp, 92, 0);
    }
}

void ftMt_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftMewtwoAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x80_MEWTWO_DISABLE_OFFSET_X *= fp->x34_scale.y;
        sA2->x84_MEWTWO_DISABLE_OFFSET_Y *= fp->x34_scale.y;
    }
}

void ftMt_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 2);
}

void ftMt_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 2);
}
