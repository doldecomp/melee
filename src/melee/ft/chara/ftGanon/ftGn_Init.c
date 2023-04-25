#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftGn_Init.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCaptain/ftCa_Init.h"
#include "ftCaptain/ftCa_SpecialHi.h"
#include "ftCaptain/ftCa_SpecialLw.h"
#include "ftCaptain/ftCa_SpecialN.h"
#include "ftCaptain/ftCa_SpecialS.h"

MotionState ftGn_Init_MotionStateTable[] = {
    {
        ftCo_AnimId_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_AnimId_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_AnimId_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_AnimId_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_AnimId_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_AnimId_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCa_AnimId_SpecialN,
        ftCa_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftCa_SpecialN_Anim,
        ftCa_SpecialN_IASA,
        ftCa_SpecialN_Phys,
        ftCa_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialAirN,
        ftCa_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftCa_SpecialAirN_Anim,
        ftCa_SpecialAirN_IASA,
        ftCa_SpecialAirN_Phys,
        ftCa_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialSStart,
        ftCa_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftCa_SpecialSStart_Anim,
        ftCa_SpecialSStart_IASA,
        ftCa_SpecialSStart_Phys,
        ftCa_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialS,
        ftCa_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftCa_SpecialS_Anim,
        ftCa_SpecialS_IASA,
        ftCa_SpecialS_Phys,
        ftCa_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialAirSStart,
        ftCa_MF_SpecialAirSStart,
        FtMoveId_SpecialS << 24,
        ftCa_SpecialAirSStart_Anim,
        ftCa_SpecialAirSStart_IASA,
        ftCa_SpecialAirSStart_Phys,
        ftCa_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialAirS,
        ftCa_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftCa_SpecialAirS_Anim,
        ftCa_SpecialAirS_IASA,
        ftCa_SpecialAirS_Phys,
        ftCa_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialHi,
        ftCa_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftCa_SpecialHi_Anim,
        ftCa_SpecialHi_IASA,
        ftCa_SpecialHi_Phys,
        ftCa_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialAirHi,
        ftCa_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftCa_SpecialAirHi_Anim,
        ftCa_SpecialAirHi_IASA,
        ftCa_SpecialAirHi_Phys,
        ftCa_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialHiCatch,
        ftCa_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftCa_SpecialHiCatch_Anim,
        ftCa_SpecialHiCatch_IASA,
        ftCa_SpecialHiCatch_Phys,
        ftCa_SpecialHiCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialHiThrow,
        ftCa_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftCa_SpecialHiThrow_Anim,
        ftCa_SpecialHiThrow_IASA,
        ftCa_SpecialHiThrow_Phys,
        ftCa_SpecialHiThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialLw,
        ftCa_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialLw_Anim,
        NULL,
        ftCa_SpecialLw_Phys,
        ftCa_SpecialLwColl,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialLwGroundEnd,
        ftCa_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialLwGroundEnd_Anim,
        NULL,
        ftCa_SpecialLwGroundEnd_Phys,
        ftCa_SpecialLwGroundEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialAirLwRebound,
        ftCa_MF_SpecialLwRebound,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialAirLw_Anim,
        NULL,
        ftCa_SpecialAirLw_Phys,
        ftCa_SpecialAirLwColl,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialAirLwGroundEnd,
        ftCa_MF_SpecialLwRebound,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialAirLwGroundEnd_Anim,
        NULL,
        ftCa_SpecialAirLwGroundEnd_Phys,
        ftCa_SpecialAirLwGroundEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialAirLwAirEnd,
        ftCa_MF_SpecialLwRebound,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialAirLwAirEnd_Anim,
        NULL,
        ftCa_SpecialAirLwAirEnd_Phys,
        ftCa_SpecialAirLwAirEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialAirLwEnd,
        ftCa_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialLwAirEnd_Anim,
        NULL,
        ftCa_SpecialLwAirEnd_Phys,
        ftCa_SpecialLwAirEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftCa_AnimId_SpecialLwRebound,
        ftCa_MF_SpecialLwRebound,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialLwRebound_Anim,
        NULL,
        ftCa_SpecialLwRebound_Phys,
        ftCa_SpecialLwRebound_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftGn_Init_DatFilename[] = "PlGn.dat";
char ftGn_Init_DataName[] = "ftDataGanon";
char ftGn_Init_803D2CF0[] = "PlGnNr.dat";
char ftGn_Init_803D2CFC[] = "PlyGanon5K_Share_joint";
char ftGn_Init_803D2D14[] = "PlGnRe.dat";
char ftGn_Init_803D2D20[] = "PlyGanon5KRe_Share_joint";
char ftGn_Init_803D2D3C[] = "PlGnBu.dat";
char ftGn_Init_803D2D48[] = "PlyGanon5KBu_Share_joint";
char ftGn_Init_803D2D64[] = "PlGnGr.dat";
char ftGn_Init_803D2D70[] = "PlyGanon5KGr_Share_joint";
char ftGn_Init_803D2D8C[] = "PlGnLa.dat";
char ftGn_Init_803D2D98[] = "PlyGanon5KLa_Share_joint";
char ftGn_Init_AnimDatFilename[] = "PlGnAJ.dat";

Fighter_DemoStrings ftGn_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileGanon",
    "ftDemoIntroMotionFileGanon",
    "ftDemoEndingMotionFileGanon",
    "ftDemoViWaitMotionFileGanon",
};

Fighter_CostumeStrings ftGn_Init_CostumeStrings[] = {
    { ftGn_Init_803D2CF0, ftGn_Init_803D2CFC, NULL },
    { ftGn_Init_803D2D14, ftGn_Init_803D2D20, NULL },
    { ftGn_Init_803D2D3C, ftGn_Init_803D2D48, NULL },
    { ftGn_Init_803D2D64, ftGn_Init_803D2D70, NULL },
    { ftGn_Init_803D2D8C, ftGn_Init_803D2D98, NULL },
};

void ftGn_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, -1);
    fp->fv.gn.during_specials = false;
    fp->fv.gn.during_specials_start = false;
}

void ftGn_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
}

void ftGn_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftGn_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftGn_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftGn_Init_OnLoad(HSD_GObj* gobj)
{
    ftCa_Init_OnLoadForGanon(gobj->user_data);
}

void ftGn_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftCa_Init_LoadSpecialAttrs(gobj);
}

void ftGn_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0);
}

void ftGn_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0);
}
