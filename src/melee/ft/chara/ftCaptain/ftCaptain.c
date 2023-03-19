#include "ftCaptain.h"

#include "ftCaptain_SpecialHi.h"
#include "ftCaptain_SpecialLw.h"
#include "ftCaptain_SpecialN.h"
#include "ftCaptain_SpecialS.h"
#include "types.h"

#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"

ActionState as_table_captain[] = {
    { 295, 0x00440842, 0x41000000, func_800CD390, func_800CD3B0, func_800CD3D0,
      func_800CD3F0, func_800761C8 },
    { 296, 0x00440846, 0x45000000, func_800CD458, func_800CD478, func_800CD498,
      func_800CD4B8, func_800761C8 },
    { 297, 0x0044084A, 0x49000000, func_800CD520, func_800CD540, func_800CD560,
      func_800CD580, func_800761C8 },
    { 298, 0x0044084E, 0x4D000000, func_800CD6A0, func_800CD7C4, func_800CD7E4,
      func_800CD804, func_800761C8 },
    { 299, 0x00440852, 0x51000000, func_800CD88C, func_800CD8AC, func_800CD8CC,
      func_800CD8EC, func_800761C8 },
    { 300, 0x00440856, 0x55000000, func_800CDB14, func_800CDB34, func_800CDB54,
      func_800CDB74, func_800761C8 },
    { 301, 0x00340211, 0x12000000, ftCaptain_SpecialN_Anim,
      ftCaptain_SpecialN_IASA, ftCaptain_SpecialN_Phys, ftCaptain_SpecialN_Coll,
      func_800761C8 },
    { 302, 0x00340611, 0x12000000, ftCaptain_SpecialAirN_Anim,
      ftCaptain_SpecialAirN_IASA, ftCaptain_SpecialAirN_Phys,
      ftCaptain_SpecialAirN_Coll, func_800761C8 },
    { 303, 0x00340212, 0x13000000, ftCaptain_SpecialSStart_Anim,
      ftCaptain_SpecialSStart_IASA, ftCaptain_SpecialSStart_Phys,
      ftCaptain_SpecialSStart_Coll, func_800761C8 },
    { 304, 0x00340212, 0x13000000, ftCaptain_SpecialS_Anim,
      ftCaptain_SpecialS_IASA, ftCaptain_SpecialS_Phys, ftCaptain_SpecialS_Coll,
      func_800761C8 },
    { 305, 0x00340612, 0x13000000, ftCaptain_SpecialAirSStart_Anim,
      ftCaptain_SpecialAirSStart_IASA, ftCaptain_SpecialAirSStart_Phys,
      ftCaptain_SpecialAirSStart_Coll, func_800761C8 },
    { 306, 0x00340612, 0x13000000, ftCaptain_SpecialAirS_Anim,
      ftCaptain_SpecialAirS_IASA, ftCaptain_SpecialAirS_Phys,
      ftCaptain_SpecialAirS_Coll, func_800761C8 },
    { 307, 0x00340013, 0x14000000, func_800E4B00, func_800E4B60, func_800E4BF8,
      func_800E4E1C, func_800761C8 },
    { 308, 0x00340413, 0x14000000, func_800E4EE8, func_800E4F48, func_800E4FDC,
      func_800E50D8, func_800761C8 },
    { 309, 0x00340013, 0x14000000, func_800E51F8, func_800E5234, func_800E5238,
      func_800E523C, func_800761C8 },
    { 310, 0x00340013, 0x14000000, func_800E5310, func_800E5384, func_800E5388,
      func_800E54B8, func_800761C8 },
    { 311, 0x00340214, 0x15000000, func_800E415C, NULL, func_800E4408,
      func_800E46B8, func_800761C8 },
    { 312, 0x00340214, 0x15000000, func_800E4268, NULL, func_800E449C,
      func_800E47B0, func_800761C8 },
    { 313, 0x00340614, 0x15000000, func_800E42E0, NULL, func_800E45E4,
      func_800E48BC, func_800761C8 },
    { 314, 0x00340614, 0x15000000, func_800E4354, NULL, func_800E4618,
      func_800E493C, func_800761C8 },
    { 316, 0x00340614, 0x15000000, func_800E4390, NULL, func_800E4678,
      func_800E495C, func_800761C8 },
    { 315, 0x00340214, 0x15000000, func_800E42A4, NULL, func_800E455C,
      func_800E4838, func_800761C8 },
    { 317, 0x00340614, 0x15000000, func_800E43CC, NULL, func_800E4698,
      func_800E49DC, func_800761C8 },
};

char lbl_803C7598[] = "PlCa.dat";
char lbl_803C75A4[] = "ftDataCaptain";
char lbl_803C75B4[] = "PlCaNr.dat";
char lbl_803C75C0[] = "PlyCaptain5K_Share_joint";
char lbl_803C75DC[] = "PlCaGy.dat";
char lbl_803C75E8[] = "PlyCaptain5KGy_Share_joint";
char lbl_803C7604[] = "PlCaRe.";
char lbl_803C760C[] = "PlyCaptain5KRe_Share_joint";
char lbl_803C7628[] = "PlCaWh.dat";
char lbl_803C7634[] = "PlyCaptain5KWh_Share_joint";
char lbl_803C7650[] = "PlCaGr.dat";
char lbl_803C765C[] = "PlyCaptain5KGr_Share_joint";
char lbl_803C7678[] = "PlCaBu.dat";
char lbl_803C7684[] = "PlyCaptain5KBu_Share_joint";
char lbl_803C76A0[] = "PlCaAJ.dat";

Fighter_DemoStrings lbl_803C772C = {
    "ftDemoResultMotionFileCaptain",
    "ftDemoIntroMotionFileCaptain",
    "ftDemoEndingMotionFileCaptain",
    "ftDemoViWaitMotionFileCaptain",
};

Fighter_CostumeStrings lbl_803C773C[] = {
    { lbl_803C75B4, lbl_803C75C0, NULL }, { lbl_803C75DC, lbl_803C75E8, NULL },
    { lbl_803C7604, lbl_803C760C, NULL }, { lbl_803C7628, lbl_803C7634, NULL },
    { lbl_803C7650, lbl_803C765C, NULL }, { lbl_803C7678, lbl_803C7684, NULL },
};

void ftCaptain_OnDeath(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_80074A4C(fighter_gobj, 0, 0);
    fp->sa.captain.during_specials = 0;
    fp->sa.captain.during_specials_start = false;
}

void ftCaptain_800E28C8(HSD_GObj* fighter_gobj)
{
    ftCaptain_SpecialS_RemoveGFX(fighter_gobj);
}

void ftCaptain_OnItemPickup(HSD_GObj* fighter_gobj, bool arg1)
{
    Fighter_OnItemPickup(fighter_gobj, arg1, 1, 1);
}

void ftCaptain_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftCaptain_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 1);
}

/// @remarks Used for both OnItemRelease and OnUnknownItemRelated
void ftCaptain_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftCaptain_OnLoadForGanon(Fighter* fp)
{
    PUSH_ATTRS(fp, ftCaptainAttributes);
}

void ftCaptain_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2224_flag.bits.b7 = true;
    PUSH_ATTRS(fp, ftCaptainAttributes);
}

void ftCaptain_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftCaptainAttributes);
}
