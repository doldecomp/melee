#include "ft/forward.h"

#include "ftPe_Init.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "lb/lbmthp.h"

MotionState ftPe_Init_MotionStateTable[] = {
    {
        295,
        0,
        0x01000000,
        ftPe_Float_Anim,
        ftPe_Float_IASA,
        ftPe_Float_Phys,
        ftPe_Float_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        0,
        0x01000000,
        ftPe_FloatEnd_Anim,
        ftPe_FloatEnd_IASA,
        ftPe_FloatEnd_Phys,
        ftPe_FloatEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        0,
        0x01000000,
        ftPe_FloatEnd_Anim,
        ftPe_FloatEnd_IASA,
        ftPe_FloatEnd_Phys,
        ftPe_FloatEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        68,
        0x0024040C,
        0x0D000000,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        69,
        0x0024040D,
        0x0E000000,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        70,
        0x0024040E,
        0x0F000000,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        71,
        0x0024040F,
        0x10000000,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        72,
        0x00240410,
        0x11000000,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        0x00240A09,
        0x0A000000,
        ftPe_AttackS4_Anim,
        ftPe_AttackS4_IASA,
        ftPe_AttackS4_Phys,
        ftPe_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        0x00240A09,
        0x0A000000,
        ftPe_AttackS4_Anim,
        ftPe_AttackS4_IASA,
        ftPe_AttackS4_Phys,
        ftPe_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        0x00240A09,
        0x0A000000,
        ftPe_AttackS4_Anim,
        ftPe_AttackS4_IASA,
        ftPe_AttackS4_Phys,
        ftPe_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        0x00340014,
        0x15000000,
        ftPe_SpecialLw_Anim,
        NULL,
        ftPe_SpecialLw_Phys,
        ftPe_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        0x00340014,
        0x15000000,
        ftPe_SpecialAirLw_Anim,
        NULL,
        ftPe_SpecialAirLw_Phys,
        ftPe_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        0x00340212,
        0x13000000,
        ftPe_SpecialSStart_Anim,
        ftPe_SpecialSStart_IASA,
        ftPe_SpecialSStart_Phys,
        ftPe_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        0x00340212,
        0x13000000,
        ftPe_SpecialSEnd_Anim,
        ftPe_SpecialSEnd_IASA,
        ftPe_SpecialSEnd_Phys,
        ftPe_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        0x00340212,
        0x13000000,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        0x00340612,
        0x13000000,
        ftPe_SpecialAirSStart_Anim,
        ftPe_SpecialAirSStart_IASA,
        ftPe_SpecialAirSStart_Phys,
        ftPe_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        0x00340612,
        0x13000000,
        ftPe_SpecialAirSEnd_Anim,
        ftPe_SpecialAirSEnd_IASA,
        ftPe_SpecialAirSEnd_Phys,
        ftPe_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        0x00340612,
        0x13000000,
        ftPe_SpecialAirSEnd_Anim,
        ftPe_SpecialAirSEnd_IASA,
        ftPe_SpecialAirSEnd_Phys,
        ftPe_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        0x00340612,
        0x13000000,
        ftPe_SpecialAirS_Anim,
        ftPe_SpecialAirS_IASA,
        ftPe_SpecialAirS_Phys,
        ftPe_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        0x00340013,
        0x14000000,
        ftPe_SpecialHiStart_Anim,
        ftPe_SpecialHiStart_IASA,
        ftPe_SpecialHiStart_Phys,
        ftPe_SpecialHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        0x00340013,
        0x14000000,
        ftPe_MS_362_Anim,
        ftPe_MS_362_IASA,
        ftPe_MS_362_Phys,
        ftPe_MS_362_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        0x00340413,
        0x14000000,
        ftPe_SpecialAirHiStart_Anim,
        ftPe_SpecialAirHiStart_IASA,
        ftPe_SpecialAirHiStart_Phys,
        ftPe_SpecialAirHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        311,
        0x00340413,
        0x14000000,
        ftPe_MS_364_Anim,
        ftPe_MS_364_IASA,
        ftPe_MS_364_Phys,
        ftPe_MS_364_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        312,
        0x00340011,
        0x12000000,
        ftPe_SpecialN_Anim,
        ftPe_SpecialN_IASA,
        ftPe_SpecialN_Phys,
        ftPe_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        313,
        0x00340011,
        0x12000000,
        ftPe_SpecialNAttack_Anim,
        ftPe_SpecialNAttack_IASA,
        ftPe_SpecialNAttack_Phys,
        ftPe_SpecialNAttack_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        0x00340411,
        0x12000000,
        ftPe_SpecialAirN_Anim,
        ftPe_SpecialAirN_IASA,
        ftPe_SpecialAirN_Phys,
        ftPe_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        315,
        0x00340411,
        0x12000000,
        ftPe_SpecialAirNAttack_Anim,
        ftPe_SpecialAirNAttack_IASA,
        ftPe_SpecialAirNAttack_Phys,
        ftPe_SpecialAirNAttack_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        316,
        0x00440058,
        0x57800000,
        ftCo_ItemParasolOpen_Anim,
        ftCo_ItemParasolOpen_IASA,
        ftCo_ItemParasolOpen_Phys,
        ftCo_ItemParasolOpen_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        317,
        0x004C0058,
        0x57800000,
        ftCo_ItemParasolFallSpecial_Anim,
        ftCo_ItemParasolFallSpecial_IASA,
        ftCo_ItemParasolFallSpecial_Phys,
        ftCo_ItemParasolFallSpecial_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftPe_Init_DatFilename[] = "PlPe.dat";
char ftPe_Init_DataName[] = "ftDataPeach";
char str_PlPeNr_dat[] = "PlPeNr.dat";
char str_PlyPeach5K_Share_joint[] = "PlyPeach5K_Share_joint";
char str_PlyPeach5K_Share_matanim_joint[] = "PlyPeach5K_Share_matanim_joint";
char str_PlPeYe_dat[] = "PlPeYe.dat";
char str_PlyPeach5KYe_Share_joint[] = "PlyPeach5KYe_Share_joint";
char str_PlyPeach5KYe_Share_matanim_joint[] =
    "PlyPeach5KYe_Share_matanim_joint";
char str_PlPeWh_dat[] = "PlPeWh.dat";
char str_PlyPeach5KWh_Share_joint[] = "PlyPeach5KWh_Share_joint";
char str_PlyPeach5KWh_Share_matanim_joint[] =
    "PlyPeach5KWh_Share_matanim_joint";
char str_PlPeBu_dat[] = "PlPeBu.dat";
char str_PlyPeach5KBu_Share_joint[] = "PlyPeach5KBu_Share_joint";
char str_PlyPeach5KBu_Share_matanim_joint[] =
    "PlyPeach5KBu_Share_matanim_joint";
char str_PlPeGr_dat[] = "PlPeGr.dat";
char str_PlyPeach5KGr_Share_joint[] = "PlyPeach5KGr_Share_joint";
char str_PlyPeach5KGr_Share_matanim_joint[] =
    "PlyPeach5KGr_Share_matanim_joint";
char ftPe_Init_AnimDatFilename[] = "PlPeAJ.dat";

Fighter_DemoStrings ftPe_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFilePeach",
    "ftDemoIntroMotionFilePeach",
    "ftDemoEndingMotionFilePeach",
    "ftDemoViWaitMotionFilePeach",
};

Fighter_CostumeStrings ftPe_Init_CostumeStrings[] = {
    { str_PlPeNr_dat, str_PlyPeach5K_Share_joint,
      str_PlyPeach5K_Share_matanim_joint },
    { str_PlPeYe_dat, str_PlyPeach5KYe_Share_joint,
      str_PlyPeach5KYe_Share_matanim_joint },
    { str_PlPeWh_dat, str_PlyPeach5KWh_Share_joint,
      str_PlyPeach5KWh_Share_matanim_joint },
    { str_PlPeBu_dat, str_PlyPeach5KBu_Share_joint,
      str_PlyPeach5KBu_Share_matanim_joint },
    { str_PlPeGr_dat, str_PlyPeach5KGr_Share_joint,
      str_PlyPeach5KGr_Share_matanim_joint },
};

void ftPe_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    fp->ev.pe.x222C = 1;
    fp->ev.pe.x2234 = -1;
    fp->ev.pe.x2240 = 0;
    fp->ev.pe.x223C = 0;
    fp->ev.pe.x2238 = 0;
    fp->ev.pe.x2244 = 0;
    fp->ev.pe.x2248 = 0;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 2, 0);
    ftParts_80074A4C(gobj, 3, -1);
    ftParts_80074A4C(gobj, 4, 0);

    switch (fp->x619_costume_id) {
    case 1:
        ftParts_80074A4C(gobj, 1, -1);
        ftParts_80074A4C(gobj, 5, 0);
        ftParts_80074A4C(gobj, 6, -1);
        break;

    default:
        ftParts_80074A4C(gobj, 1, 0);
        ftParts_80074A4C(gobj, 5, -1);
        ftParts_80074A4C(gobj, 6, 0);
        break;
    }
}

void ftPe_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftPeachAttributes* extAtrrs = fp->x10C_ftData->ext_attr;
    void** items = fp->x10C_ftData->x48_items;

    extAtrrs->unk0 = lbMthp_8001E8F8(ftData_80085E50(fp, 18));
    extAtrrs->unk4 = lbMthp_8001E8F8(ftData_80085E50(fp, 19));

    PUSH_ATTRS(fp, ftPeachAttributes);

    it_8026B3F8(items[0], It_Kind_Peach_Explode);
    it_8026B3F8(items[1], It_Kind_Peach_Turnip);
    it_8026B3F8(items[2], It_Kind_Peach_Parasol);
    it_8026B3F8(items[3], It_Kind_Peach_Toad);
    it_8026B3F8(items[4], It_Kind_Peach_ToadSpore);
}

/* static */ void ftPe_8011D598(HSD_GObj* gobj);
/* static */ void ftPe_8011E2E8(HSD_GObj* gobj);
/* static */ void ftPe_8011CFA0(HSD_GObj* gobj);

void ftPe_Init_8011B704(HSD_GObj* gobj)
{
    ftPe_8011D598(gobj);
    ftPe_8011E2E8(gobj);
    ftPe_8011CFA0(gobj);
}

void ftPe_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftPe_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftPe_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftPe_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftPe_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftPeachAttributes);
}

void ftPe_Init_8011B93C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    s32 result = ftParts_80074A74(gobj, 2);

    if (result == -1) {
        ftParts_80074A4C(gobj, 2, 0);
    } else {
        ftParts_80074A4C(gobj, 2, -1);
    }
}

void ftPe_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftPe_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

s32 ftPe_8011BA20(Fighter* fp)
{
    s32 result = 1;

    if (!(fp->input.x624_lstick_y >= p_ftCommonData->x70_someLStickYMax) &&
        !(fp->input.x65C_heldInputs & 0xC00))
    {
        result = 0;
    }

    return result;
}
