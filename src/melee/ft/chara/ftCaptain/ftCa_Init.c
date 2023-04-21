#include "ftCa_Init.h"

#include "ftCa_SpecialHi.h"
#include "ftCa_SpecialLw.h"
#include "ftCa_SpecialN.h"
#include "ftCa_SpecialS.h"
#include "types.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

static u32 const swing_flags_x4 =
    FtStateChange_PreserveGfx | FtStateChange_Unk_6 |
    FtStateChange_SkipUpdateRumble | FtStateChange_SkipUpdateItemVis |
    FtStateChange_SkipUpdateModelPartVis;

static u32 const swing_flags_x8 = FtStateChange_Unk_24 | FtStateChange_Unk_30;

static u32 const bat_swing_flags_x4 =
    swing_flags_x4 | FtStateChange_PreserveColAnimHitStatus;

static u32 const bat_swing_flags_x8 =
    swing_flags_x8 | FtStateChange_SkipUpdateModelFlag;

static u32 const parasol_swing_flags_x4 =
    swing_flags_x4 | FtStateChange_SkipUpdateHit;

static u32 const parasol_swing_flags_x8 =
    swing_flags_x8 | FtStateChange_Unk_27;

static u32 const harisen_swing_flags_x4 =
    bat_swing_flags_x4 | FtStateChange_SkipUpdateHit;

static u32 const harisen_swing_flags_x8 =
    swing_flags_x8 | FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

static u32 const star_rod_swing_flags_x4 =
    swing_flags_x4 | FtStateChange_SkipUpdateModel;

static u32 const star_rod_swing_flags_x8 =
    swing_flags_x8 | FtStateChange_SkipUpdateHitStunFlag;

static u32 const lipstick_swing_flags_x4 =
    bat_swing_flags_x4 | FtStateChange_SkipUpdateModel;

static u32 const lipstick_swing_flags_x8 =
    bat_swing_flags_x8 | FtStateChange_SkipUpdateHitStunFlag;

static u32 const specialn_base0_flags_x4 =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static u32 const specialn_base1_flags_x4 =
    specialn_base0_flags_x4 | FtStateChange_PreserveSfx;

static u32 const specialn_flags_x4 =
    specialn_base1_flags_x4 | FtStateChange_PreserveFastFall;

static u32 const specialn_flags_x8 =
    FtStateChange_SkipUpdateAttackCount | FtStateChange_SkipUpdateHitStunFlag;

static u32 const specialairn_flags_x4 =
    specialn_flags_x4 | FtStateChange_SkipUpdateParasol;

static u32 const specials_flags_x4 =
    specialn_base1_flags_x4 | FtStateChange_PreserveGfx;

static u32 const specials_flags_x8 = specialn_flags_x8 | FtStateChange_Unk_24;

static u32 const specialairsstart_flags_x4 =
    specials_flags_x4 | FtStateChange_SkipUpdateParasol;

static u32 const specialairs_flags_x4 =
    specials_flags_x4 | FtStateChange_SkipUpdateParasol;

static u32 const specialhi_flags_x4 = specialn_base0_flags_x4 |
                                      FtStateChange_PreserveFastFall |
                                      FtStateChange_PreserveGfx;

static u32 const specialhi_flags_x8 =
    FtStateChange_SkipUpdateModelFlag | FtStateChange_SkipUpdateHitStunFlag;

static u32 const specialairhi_flags_x4 =
    specialhi_flags_x4 | FtStateChange_SkipUpdateParasol;

static u32 const speciallw_flags_x4 =
    specialn_base1_flags_x4 | FtStateChange_PreserveColAnimHitStatus;

static u32 const speciallw_flags_x8 =
    specialhi_flags_x8 | FtStateChange_Unk_24;

static u32 const speciallwrebound_flags_x4 =
    speciallw_flags_x4 | FtStateChange_SkipUpdateParasol;

MotionState ftCa_Init_MotionStateTable[] = {
    {
        295,
        swing_flags_x4,
        swing_flags_x8,
        ftCo_SwordSwing_Anim,
        ftCo_SwordSwing_IASA,
        ftCo_SwordSwing_Phys,
        ftCo_SwordSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        bat_swing_flags_x4,
        bat_swing_flags_x8,
        ftCo_BatSwing_Anim,
        ftCo_BatSwing_IASA,
        ftCo_BatSwing_Phys,
        ftCo_BatSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        parasol_swing_flags_x4,
        parasol_swing_flags_x8,
        ftCo_ParasolSwing_Anim,
        ftCo_ParasolSwing_IASA,
        ftCo_ParasolSwing_Phys,
        ftCo_ParasolSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        harisen_swing_flags_x4,
        harisen_swing_flags_x8,
        ftCo_HarisenSwing_Anim,
        ftCo_HarisenSwing_IASA,
        ftCo_HarisenSwing_Phys,
        ftCo_HarisenSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        star_rod_swing_flags_x4,
        star_rod_swing_flags_x8,
        ftCo_StarRodSwing_Anim,
        ftCo_StarRodSwing_IASA,
        ftCo_StarRodSwing_Phys,
        ftCo_StarRodSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        lipstick_swing_flags_x4,
        lipstick_swing_flags_x8,
        ftCo_LipstickSwing_Anim,
        ftCo_LipstickSwing_IASA,
        ftCo_LipstickSwing_Phys,
        ftCo_LipstickSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        specialn_flags_x4,
        specialn_flags_x8,
        ftCa_SpecialN_Anim,
        ftCa_SpecialN_IASA,
        ftCa_SpecialN_Phys,
        ftCa_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        specialairn_flags_x4,
        specialn_flags_x8,
        ftCa_SpecialAirN_Anim,
        ftCa_SpecialAirN_IASA,
        ftCa_SpecialAirN_Phys,
        ftCa_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        specials_flags_x4,
        specials_flags_x8,
        ftCa_SpecialSStart_Anim,
        ftCa_SpecialSStart_IASA,
        ftCa_SpecialSStart_Phys,
        ftCa_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        specials_flags_x4,
        specials_flags_x8,
        ftCa_SpecialS_Anim,
        ftCa_SpecialS_IASA,
        ftCa_SpecialS_Phys,
        ftCa_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        specialairsstart_flags_x4,
        specials_flags_x8,
        ftCa_SpecialAirSStart_Anim,
        ftCa_SpecialAirSStart_IASA,
        ftCa_SpecialAirSStart_Phys,
        ftCa_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        specialairs_flags_x4,
        specials_flags_x8,
        ftCa_SpecialAirS_Anim,
        ftCa_SpecialAirS_IASA,
        ftCa_SpecialAirS_Phys,
        ftCa_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        specialhi_flags_x4,
        specialhi_flags_x8,
        ftCa_SpecialHi_Anim,
        ftCa_SpecialHi_IASA,
        ftCa_SpecialHi_Phys,
        ftCa_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        specialairhi_flags_x4,
        specialhi_flags_x8,
        ftCa_SpecialAirHi_Anim,
        ftCa_SpecialAirHi_IASA,
        ftCa_SpecialAirHi_Phys,
        ftCa_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        specialhi_flags_x4,
        specialhi_flags_x8,
        ftCa_SpecialHiCatch_Anim,
        ftCa_SpecialHiCatch_IASA,
        ftCa_SpecialHiCatch_Phys,
        ftCa_SpecialHiCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        specialhi_flags_x4,
        specialhi_flags_x8,
        ftCa_SpecialHiThrow_Anim,
        ftCa_SpecialHiThrow_IASA,
        ftCa_SpecialHiThrow_Phys,
        ftCa_SpecialHiThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        311,
        speciallw_flags_x4,
        speciallw_flags_x8,
        ftCa_SpecialLw_Anim,
        NULL,
        ftCa_SpecialLw_Phys,
        ftCa_SpecialLwColl,
        ftCamera_UpdateCameraBox,
    },
    {
        312,
        speciallw_flags_x4,
        speciallw_flags_x8,
        ftCa_SpecialLwGroundEnd_Anim,
        NULL,
        ftCa_SpecialLwGroundEnd_Phys,
        ftCa_SpecialLwGroundEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        313,
        speciallwrebound_flags_x4,
        speciallw_flags_x8,
        ftCa_SpecialAirLw_Anim,
        NULL,
        ftCa_SpecialAirLw_Phys,
        ftCa_SpecialAirLwColl,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        speciallwrebound_flags_x4,
        speciallw_flags_x8,
        ftCa_SpecialAirLwGroundEnd_Anim,
        NULL,
        ftCa_SpecialAirLwGroundEnd_Phys,
        ftCa_SpecialAirLwGroundEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        316,
        speciallwrebound_flags_x4,
        speciallw_flags_x8,
        ftCa_SpecialAirLwAirEnd_Anim,
        NULL,
        ftCa_SpecialAirLwAirEnd_Phys,
        ftCa_SpecialAirLwAirEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        315,
        speciallw_flags_x4,
        speciallw_flags_x8,
        ftCa_SpecialLwAirEnd_Anim,
        NULL,
        ftCa_SpecialLwAirEnd_Phys,
        ftCa_SpecialLwAirEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        317,
        speciallwrebound_flags_x4,
        speciallw_flags_x8,
        ftCa_SpecialLwRebound_Anim,
        NULL,
        ftCa_SpecialLwRebound_Phys,
        ftCa_SpecialLwRebound_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftCa_Init_DatFilename[] = "PlCa.dat";
char ftCa_Init_DataName[] = "ftDataCaptain";
static char nr_dat[] = "PlCaNr.dat";
static char nr_joint[] = "PlyCaptain5K_Share_joint";
static char gy_dat[] = "PlCaGy.dat";
static char gy_joint[] = "PlyCaptain5KGy_Share_joint";

#ifdef MUST_MATCH
char re_dat[] = "PlCaRe.";
#else
/// @todo What.
char re_dat[] = "PlCaRe.dat";
#endif

static char re_joint[] = "PlyCaptain5KRe_Share_joint";
static char wh_dat[] = "PlCaWh.dat";
static char wh_joint[] = "PlyCaptain5KWh_Share_joint";
static char gr_dat[] = "PlCaGr.dat";
static char gr_joint[] = "PlyCaptain5KGr_Share_joint";
static char bu_dat[] = "PlCaBu.dat";
static char bu_joint[] = "PlyCaptain5KBu_Share_joint";
char ftCa_Init_AnimDatFilename[] = "PlCaAJ.dat";

Fighter_DemoStrings ftCa_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileCaptain",
    "ftDemoIntroMotionFileCaptain",
    "ftDemoEndingMotionFileCaptain",
    "ftDemoViWaitMotionFileCaptain",
};

Fighter_CostumeStrings ftCa_Init_CostumeStrings[] = {
    { nr_dat, nr_joint, NULL }, { gy_dat, gy_joint, NULL },
    { re_dat, re_joint, NULL }, { wh_dat, wh_joint, NULL },
    { gr_dat, gr_joint, NULL }, { bu_dat, bu_joint, NULL },
};

void ftCa_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.ca.during_specials = 0;
    fp->fv.ca.during_specials_start = false;
}

void ftCa_Init_800E28C8(HSD_GObj* gobj)
{
    ftCa_SpecialS_RemoveGFX(gobj);
}

void ftCa_Init_OnItemPickup(HSD_GObj* gobj, bool arg1)
{
    Fighter_OnItemPickup(gobj, arg1, true, true);
}

void ftCa_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftCa_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

/// @remarks Used for both OnItemRelease and OnUnknownItemRelated
void ftCa_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftCa_Init_OnLoadForGanon(Fighter* fp)
{
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

void ftCa_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2224_flag.bits.b7 = true;
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

void ftCa_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCaptain_DatAttrs);
}
