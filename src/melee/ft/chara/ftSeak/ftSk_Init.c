#include "forward.h"
#include "ft/forward.h"

#include "ftSeak/ftSk_Init.h"

#include "ftSk_SpecialHi.h"
#include "ftSk_SpecialLw.h"
#include "ftSk_SpecialN.h"
#include "ftSk_SpecialS.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftSeak/types.h"

MotionState ftSk_Init_MotionStateTable[] = {
    {
        ftSk_AnimId_SpecialNChargeStart,
        ftSk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialNChargeStart_Anim,
        ftSk_SpecialNChargeStart_IASA,
        ftSk_SpecialNChargeStart_Phys,
        ftSk_SpecialNChargeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialNChargeLoop,
        ftSk_MF_SpecialNLoop,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialNChargeLoop_Anim,
        ftSk_SpecialNChargeLoop_IASA,
        ftSk_SpecialNChargeLoop_Phys,
        ftSk_SpecialNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialNChargeEnd,
        ftSk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialNChargeEnd_Anim,
        ftSk_SpecialNChargeEnd_IASA,
        ftSk_SpecialNChargeEnd_Phys,
        ftSk_SpecialNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialNShoot,
        ftSk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialNShoot_Anim,
        ftSk_SpecialNShoot_IASA,
        ftSk_SpecialNShoot_Phys,
        ftSk_SpecialNShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirNChargeStart,
        ftSk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialAirNChargeStart_Anim,
        ftSk_SpecialAirNChargeStart_IASA,
        ftSk_SpecialAirNChargeStart_Phys,
        ftSk_SpecialAirNChargeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirNChargeLoop,
        ftSk_MF_SpecialAirNLoop,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialAirNChargeLoop_Anim,
        ftSk_SpecialAirNChargeLoop_IASA,
        ftSk_SpecialAirNChargeLoop_Phys,
        ftSk_SpecialAirNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirNChargeEnd,
        ftSk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialAirNChargeEnd_Anim,
        ftSk_SpecialAirNChargeEnd_IASA,
        ftSk_SpecialAirNChargeEnd_Phys,
        ftSk_SpecialAirNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirNShoot,
        ftSk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialAirNShoot_Anim,
        ftSk_SpecialAirNShoot_IASA,
        ftSk_SpecialAirNShoot_Phys,
        ftSk_SpecialAirNShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialSStart,
        ftSk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialSStart_Anim,
        ftSk_SpecialSStart_IASA,
        ftSk_SpecialSStart_Phys,
        ftSk_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialSLoop,
        ftSk_MF_SpecialSLoop,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialSLoop_Anim,
        ftSk_SpecialSLoop_IASA,
        ftSk_SpecialSLoop_Phys,
        ftSk_SpecialSLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialSEnd,
        ftSk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialSEnd_Anim,
        ftSk_SpecialSEnd_IASA,
        ftSk_SpecialSEnd_Phys,
        ftSk_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirSStart,
        ftSk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialAirSStart_Anim,
        ftSk_SpecialAirSStart_IASA,
        ftSk_SpecialAirSStart_Phys,
        ftSk_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirSLoop,
        ftSk_MF_SpecialAirSLoop,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialAirSLoop_Anim,
        ftSk_SpecialAirSLoop_IASA,
        ftSk_SpecialAirSLoop_Phys,
        ftSk_SpecialAirSLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirSEnd,
        ftSk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialAirSEnd_Anim,
        ftSk_SpecialAirSEnd_IASA,
        ftSk_SpecialAirSEnd_Phys,
        ftSk_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialHi,
        ftSk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialHiStart_Anim,
        ftSk_SpecialHiStart_IASA,
        ftSk_SpecialHiStart_Phys,
        ftSk_SpecialHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialHi,
        ftSk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialHi_Anim,
        ftSk_SpecialHi_IASA,
        ftSk_SpecialHi_Phys,
        ftSk_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialHiEnd,
        ftSk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialHiEnd_Anim,
        ftSk_SpecialHiEnd_IASA,
        ftSk_SpecialHiEnd_Phys,
        ftSk_SpecialHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirHi,
        ftSk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialAirHiStart_Anim,
        ftSk_SpecialAirHiStart_IASA,
        ftSk_SpecialAirHiStart_Phys,
        ftSk_SpecialAirHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirHi,
        ftSk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialAirHi_Anim,
        ftSk_SpecialAirHi_IASA,
        ftSk_SpecialAirHi_Phys,
        ftSk_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirHiEnd,
        ftSk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialAirHiEnd_Anim,
        ftSk_SpecialAirHiEnd_IASA,
        ftSk_SpecialAirHiEnd_Phys,
        ftSk_SpecialAirHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialLw,
        ftSk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftSk_SpecialLw_Anim,
        ftSk_SpecialLw_IASA,
        ftSk_SpecialLw_Phys,
        ftSk_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialLwEnd,
        ftSk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftSk_SpecialLwEnd_Anim,
        ftSk_SpecialLwEnd_IASA,
        ftSk_SpecialLwEnd_Phys,
        ftSk_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirLw,
        ftSk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftSk_SpecialAirLw_Anim,
        ftSk_SpecialAirLw_IASA,
        ftSk_SpecialAirLw_Phys,
        ftSk_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftSk_AnimId_SpecialAirLwEnd,
        ftSk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftSk_SpecialAirLwEnd_Anim,
        ftSk_SpecialAirLwEnd_IASA,
        ftSk_SpecialAirLwEnd_Phys,
        ftSk_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftSk_Init_DatFilename[] = "PlSk.dat";
char ftSk_Init_DataName[] = "ftDataSeak";
char ftSk_Init_803CC378[] = "PlSkNr.dat";
char ftSk_Init_803CC384[] = "PlySeak5K_Share_joint";
char ftSk_Init_803CC39C[] = "PlySeak5K_Share_matanim_joint";
char ftSk_Init_803CC3BC[] = "PlSkRe.dat";
char ftSk_Init_803CC3C8[] = "PlySeak5KRe_Share_joint";
char ftSk_Init_803CC3E0[] = "PlySeak5KRe_Share_matanim_joint";
char ftSk_Init_803CC400[] = "PlSkBu.dat";
char ftSk_Init_803CC40C[] = "PlySeak5KBu_Share_joint";
char ftSk_Init_803CC424[] = "PlySeak5KBu_Share_matanim_joint";
char ftSk_Init_803CC444[] = "PlSkGr.dat";
char ftSk_Init_803CC450[] = "PlySeak5KGr_Share_joint";
char ftSk_Init_803CC468[] = "PlySeak5KGr_Share_matanim_joint";
char ftSk_Init_803CC488[] = "PlSkWh.dat";
char ftSk_Init_803CC494[] = "PlySeak5KWh_Share_joint";
char ftSk_Init_803CC4AC[] = "PlySeak5KWh_Share_matanim_joint";
char ftSk_Init_AnimDatFilename[] = "PlSkAJ.dat";

Fighter_DemoStrings ftSk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileSeak",
    "ftDemoIntroMotionFileSeak",
    "ftDemoEndingMotionFileSeak",
    "ftDemoViWaitMotionFileSeak",
};

Fighter_CostumeStrings ftSk_Init_CostumeStrings[] = {
    { ftSk_Init_803CC378, ftSk_Init_803CC384, ftSk_Init_803CC39C },
    { ftSk_Init_803CC3BC, ftSk_Init_803CC3C8, ftSk_Init_803CC3E0 },
    { ftSk_Init_803CC400, ftSk_Init_803CC40C, ftSk_Init_803CC424 },
    { ftSk_Init_803CC444, ftSk_Init_803CC450, ftSk_Init_803CC468 },
    { ftSk_Init_803CC488, ftSk_Init_803CC494, ftSk_Init_803CC4AC },
};

void ftSk_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.sk.x222C = 0;
    fp->fv.sk.x2230 = 0;
    fp->fv.sk.x2234 = 0;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, -1);
}

void ftSk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftSeakAttributes);

    it_8026B3F8(item_list[0], 79);
    it_8026B3F8(item_list[1], 80);
    it_8026B3F8(item_list[2], 85);
    it_8026B3F8(item_list[3], 97);
}

/* static */ void ftSk_SpecialN_80111FBC(HSD_GObj* gobj);
/* static */ void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj);

void ftSk_Init_80110198(HSD_GObj* gobj)
{
    ftSk_SpecialN_80111FBC(gobj);
    ftSk_SpecialS_CheckAndDestroyChain(gobj);
}

void ftSk_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.sk.x222C == 6) {
        ft_800BFFD0(fp, 86, 0);
    }
}

void ftSk_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftSk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftSk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftSk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftSk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSeakAttributes);
}

void ftSk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftSk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
