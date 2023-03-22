#include "ftZelda_Init.h"

#include "ftZelda_SpecialHi.h"
#include "ftZelda_SpecialLw.h"
#include "ftZelda_SpecialN.h"
#include "ftZelda_SpecialS.h"

#include "ft/fighter.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftZelda_MotionStateTable[] = {
    { 295, 0x00341011, 0x12000000, ftZelda_8013AA38, ftZelda_8013AB60,
      ftZelda_8013AB68, ftZelda_8013AC10, ftCamera_UpdateCameraBox },
    { 296, 0x00341411, 0x12000000, ftZelda_8013AACC, ftZelda_8013AB64,
      ftZelda_8013AB9C, ftZelda_8013AC4C, ftCamera_UpdateCameraBox },
    { 297, 0x00340112, 0x13000000, ftZelda_8013B780, ftZelda_8013BDD0,
      ftZelda_8013BED8, ftZelda_8013C070, ftCamera_UpdateCameraBox },
    { 298, 0x00340112, 0x13000000, ftZelda_8013B89C, ftZelda_8013BDD4,
      ftZelda_8013BF10, ftZelda_8013C0DC, ftCamera_UpdateCameraBox },
    { 299, 0x00340112, 0x13000000, ftZelda_8013BA04, ftZelda_8013BE50,
      ftZelda_8013BF30, ftZelda_8013C148, ftCamera_UpdateCameraBox },
    { 300, 0x00340512, 0x13000000, ftZelda_8013BA8C, ftZelda_8013BE54,
      ftZelda_8013BF50, ftZelda_8013C1B4, ftCamera_UpdateCameraBox },
    { 301, 0x00340512, 0x13000000, ftZelda_8013BBA8, ftZelda_8013BE58,
      ftZelda_8013BFB0, ftZelda_8013C220, ftCamera_UpdateCameraBox },
    { 302, 0x00340512, 0x13000000, ftZelda_8013BD10, ftZelda_8013BED4,
      ftZelda_8013C010, ftZelda_8013C28C, ftCamera_UpdateCameraBox },
    { 303, 0x00340013, 0x14000000, ftZelda_801399B4, ftZelda_80139A2C,
      ftZelda_80139A34, ftZelda_80139A98, ftCamera_UpdateCameraBox },
    { 303, 0x00340013, 0x14000000, ftZelda_80139C1C, ftZelda_80139C94,
      ftZelda_80139C9C, ftZelda_80139CC0, ftCamera_UpdateCameraBox },
    { 304, 0x00340013, 0x14000000, ftZelda_8013A448, ftZelda_8013A4E4,
      ftZelda_8013A4EC, ftZelda_8013A588, ftCamera_UpdateCameraBox },
    { 305, 0x00340413, 0x14000000, ftZelda_801399F0, ftZelda_80139A30,
      ftZelda_80139A54, ftZelda_80139AD4, ftCamera_UpdateCameraBox },
    { 305, 0x00340413, 0x14000000, ftZelda_80139C58, ftZelda_80139C98,
      ftZelda_80139CBC, ftZelda_80139D60, ftCamera_UpdateCameraBox },
    { 306, 0x00340413, 0x14000000, ftZelda_8013A484, ftZelda_8013A4E8,
      ftZelda_8013A50C, ftZelda_8013A5C4, ftCamera_UpdateCameraBox },
    { 307, 0x00340014, 0x15000000, ftZelda_8013B068, ftZelda_8013B0E8,
      ftZelda_8013B0F0, ftZelda_8013B154, ftCamera_UpdateCameraBox },
    { 308, 0x00340014, 0x15000000, ftZelda_8013B2A4, ftZelda_8013B31C,
      ftZelda_8013B324, ftZelda_8013B388, ftCamera_UpdateCameraBox },
    { 309, 0x00340414, 0x15000000, ftZelda_8013B0A8, ftZelda_8013B0EC,
      ftZelda_8013B110, ftZelda_8013B190, ftCamera_UpdateCameraBox },
    { 310, 0x00340414, 0x15000000, ftZelda_8013B2E0, ftZelda_8013B320,
      ftZelda_8013B344, ftZelda_8013B3C4, ftCamera_UpdateCameraBox },
};

char lbl_803CFC98[] = "PlZd.dat";
char lbl_803CFCA4[] = "ftDataZelda";
char lbl_803CFCB0[] = "PlZdNr.dat";
char lbl_803CFCBC[] = "PlyZelda5K_Share_joint";
char lbl_803CFCD4[] = "PlyZelda5K_Share_matanim_joint";
char lbl_803CFCF4[] = "PlZdRe.dat";
char lbl_803CFD00[] = "PlyZelda5KRe_Share_joint";
char lbl_803CFD1C[] = "PlyZelda5KRe_Share_matanim_joint";
char lbl_803CFD40[] = "PlZdBu.dat";
char lbl_803CFD4C[] = "PlyZelda5KBu_Share_joint";
char lbl_803CFD68[] = "PlyZelda5KBu_Share_matanim_joint";
char lbl_803CFD8C[] = "PlZdGr.dat";
char lbl_803CFD98[] = "PlyZelda5KGr_Share_joint";
char lbl_803CFDB4[] = "PlyZelda5KGr_Share_matanim_joint";
char lbl_803CFDD8[] = "PlZdWh.dat";
char lbl_803CFDE4[] = "PlyZelda5KWh_Share_joint";
char lbl_803CFE00[] = "PlyZelda5KWh_Share_matanim_joint";
char lbl_803CFE24[] = "PlZdAJ.dat";

Fighter_DemoStrings lbl_803CFEA0 = {
    "ftDemoResultMotionFileZelda",
    "ftDemoIntroMotionFileZelda",
    "ftDemoEndingMotionFileZelda",
    "ftDemoViWaitMotionFileZelda",
};

Fighter_CostumeStrings lbl_803CFEB0[] = {
    { lbl_803CFCB0, lbl_803CFCBC, lbl_803CFCD4 },
    { lbl_803CFCF4, lbl_803CFD00, lbl_803CFD1C },
    { lbl_803CFD40, lbl_803CFD4C, lbl_803CFD68 },
    { lbl_803CFD8C, lbl_803CFD98, lbl_803CFDB4 },
    { lbl_803CFDD8, lbl_803CFDE4, lbl_803CFE00 },
};

void ftZelda_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    fp->fv.zd.x222C = 0;
}

void ftZelda_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftZelda_DatAttrs);

    func_8026B3F8(item_list[0], 0x6CU);
    func_8026B3F8(item_list[1], 0x6DU);
}

void ftZelda_801393AC(HSD_GObj* gobj)
{
    ftZelda_8013B5EC(gobj);
}

void ftZelda_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftZelda_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftZelda_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftZelda_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftZelda_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftZelda_DatAttrs);
}

/// Zelda_RemoveDress
void ftZelda_801395C8(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    int result = func_80074A74(gobj, 1);
    if (result == -1) {
        func_80074A4C(gobj, 1, 0);
    } else {
        func_80074A4C(gobj, 1, -1);
    }
}

void ftZelda_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftZelda_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
