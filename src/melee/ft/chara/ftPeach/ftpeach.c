#include "ftpeach.h"

#include "ft/forward.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "it/forward.h"
#include "lb/lbmthp.h"

MotionState as_table_peach[] = {
    { 295, 0, 0x01000000, ftPeach_8011BC38, ftPeach_8011BC8C, ftPeach_8011BD18,
      ftPeach_8011BD3C, func_800761C8 },
    { 296, 0, 0x01000000, ftPeach_8011BDF0, ftPeach_8011BE2C, ftPeach_8011BE30,
      ftPeach_8011BE50, func_800761C8 },
    { 297, 0, 0x01000000, ftPeach_8011BDF0, ftPeach_8011BE2C, ftPeach_8011BE30,
      ftPeach_8011BE50, func_800761C8 },
    { 68, 0x0024040C, 0x0D000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 69, 0x0024040D, 0x0E000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 70, 0x0024040E, 0x0F000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 71, 0x0024040F, 0x10000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 72, 0x00240410, 0x11000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 298, 0x00240A09, 0x0A000000, ftPeach_8011C248, ftPeach_8011C284,
      ftPeach_8011C2B4, ftPeach_8011C2D4, func_800761C8 },
    { 299, 0x00240A09, 0x0A000000, ftPeach_8011C248, ftPeach_8011C284,
      ftPeach_8011C2B4, ftPeach_8011C2D4, func_800761C8 },
    { 300, 0x00240A09, 0x0A000000, ftPeach_8011C248, ftPeach_8011C284,
      ftPeach_8011C2B4, ftPeach_8011C2D4, func_800761C8 },
    { 301, 0x00340014, 0x15000000, ftPeach_8011D2EC, NULL, ftPeach_8011D394,
      ftPeach_8011D3D4, func_800761C8 },
    { 301, 0x00340014, 0x15000000, ftPeach_8011D340, NULL, ftPeach_8011D3B4,
      ftPeach_8011D3FC, func_800761C8 },
    { 302, 0x00340212, 0x13000000, ftPeach_8011C4F0, ftPeach_8011C5E8,
      ftPeach_8011C5F0, ftPeach_8011C664, func_800761C8 },
    { 303, 0x00340212, 0x13000000, ftPeach_8011CA84, ftPeach_8011CAFC,
      ftPeach_8011CB04, ftPeach_8011CB44, func_800761C8 },
    { 304, 0x00340212, 0x13000000, NULL, NULL, NULL, NULL, func_800761C8 },
    { 305, 0x00340612, 0x13000000, ftPeach_8011C588, ftPeach_8011C5EC,
      ftPeach_8011C644, ftPeach_8011C6FC, func_800761C8 },
    { 306, 0x00340612, 0x13000000, ftPeach_8011CAC0, ftPeach_8011CB00,
      ftPeach_8011CB24, ftPeach_8011CB80, func_800761C8 },
    { 307, 0x00340612, 0x13000000, ftPeach_8011CAC0, ftPeach_8011CB00,
      ftPeach_8011CB24, ftPeach_8011CB80, func_800761C8 },
    { 304, 0x00340612, 0x13000000, ftPeach_8011C878, ftPeach_8011C8C8,
      ftPeach_8011C8CC, ftPeach_8011C93C, func_800761C8 },
    { 308, 0x00340013, 0x14000000, ftPeach_8011D8D0, ftPeach_8011DA30,
      ftPeach_8011DCC0, ftPeach_8011DDBC, func_800761C8 },
    { 309, 0x00340013, 0x14000000, ftPeach_8011DE9C, ftPeach_8011DF5C,
      ftPeach_8011DF64, ftPeach_8011E094, func_800761C8 },
    { 310, 0x00340413, 0x14000000, ftPeach_8011D980, ftPeach_8011DB78,
      ftPeach_8011DCF8, ftPeach_8011DE2C, func_800761C8 },
    { 311, 0x00340413, 0x14000000, ftPeach_8011DEFC, ftPeach_8011DF60,
      ftPeach_8011DFD0, ftPeach_8011E104, func_800761C8 },
    { 312, 0x00340011, 0x12000000, ftPeach_8011E4F8, ftPeach_8011E670,
      ftPeach_8011E678, ftPeach_8011E75C, func_800761C8 },
    { 313, 0x00340011, 0x12000000, ftPeach_8011E9A0, ftPeach_8011EA68,
      ftPeach_8011EA70, ftPeach_8011EAE0, func_800761C8 },
    { 314, 0x00340411, 0x12000000, ftPeach_8011E5B4, ftPeach_8011E674,
      ftPeach_8011E6AC, ftPeach_8011E798, func_800761C8 },
    { 315, 0x00340411, 0x12000000, ftPeach_8011EA04, ftPeach_8011EA6C,
      ftPeach_8011EA90, ftPeach_8011EB1C, func_800761C8 },
    { 316, 0x00440058, 0x57800000, func_800CF0B8, func_800CF118, func_800CF1A0,
      func_800CF258, func_800761C8 },
    { 317, 0x004C0058, 0x57800000, func_800CF424, func_800CF428, func_800CF494,
      func_800CF4B4, func_800761C8 },
};

char ftPeach_str_PlPe_dat[] = "PlPe.dat";
char ftPeach_str_ftDataPeach[] = "ftDataPeach";
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
char str_PlPeAJ_dat[] = "PlPeAJ.dat";

Fighter_DemoStrings ftPeach_str_arr_ftDemo = {
    "ftDemoResultMotionFilePeach",
    "ftDemoIntroMotionFilePeach",
    "ftDemoEndingMotionFilePeach",
    "ftDemoViWaitMotionFilePeach",
};

Fighter_CostumeStrings ftPeach_str_arr_Costumes[] = {
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

void ftPeach_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    fp->fv.pe.x222C = 1;
    fp->fv.pe.x2234 = -1;
    fp->fv.pe.x2240 = 0;
    fp->fv.pe.x223C = 0;
    fp->fv.pe.x2238 = 0;
    fp->fv.pe.x2244 = 0;
    fp->fv.pe.x2248 = 0;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 2, 0);
    func_80074A4C(gobj, 3, -1);
    func_80074A4C(gobj, 4, 0);

    switch (fp->x619_costume_id) {
    case 1:
        func_80074A4C(gobj, 1, -1);
        func_80074A4C(gobj, 5, 0);
        func_80074A4C(gobj, 6, -1);
        break;

    default:
        func_80074A4C(gobj, 1, 0);
        func_80074A4C(gobj, 5, -1);
        func_80074A4C(gobj, 6, 0);
        break;
    }
}

void ftPeach_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftPeachAttributes* extAtrrs = fp->x10C_ftData->ext_attr;
    void** items = fp->x10C_ftData->x48_items;

    extAtrrs->unk0 = func_8001E8F8(func_80085E50(fp, 18));
    extAtrrs->unk4 = func_8001E8F8(func_80085E50(fp, 19));

    PUSH_ATTRS(fp, ftPeachAttributes);

    func_8026B3F8(items[0], It_Kind_Peach_Explode);
    func_8026B3F8(items[1], It_Kind_Peach_Turnip);
    func_8026B3F8(items[2], It_Kind_Peach_Parasol);
    func_8026B3F8(items[3], It_Kind_Peach_Toad);
    func_8026B3F8(items[4], It_Kind_Peach_ToadSpore);
}

/* static */ void ftPeach_8011D598(HSD_GObj* gobj);
/* static */ void ftPeach_8011E2E8(HSD_GObj* gobj);
/* static */ void ftPeach_8011CFA0(HSD_GObj* gobj);

void ftPeach_8011B704(HSD_GObj* gobj)
{
    ftPeach_8011D598(gobj);
    ftPeach_8011E2E8(gobj);
    ftPeach_8011CFA0(gobj);
}

void ftPeach_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftPeach_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftPeach_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftPeach_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftPeach_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftPeachAttributes);
}

void ftPeach_8011B93C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    s32 result = func_80074A74(gobj, 2);

    if (result == -1)
        func_80074A4C(gobj, 2, 0);
    else
        func_80074A4C(gobj, 2, -1);
}

void ftPeach_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftPeach_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

s32 ftPeach_8011BA20(Fighter* fp)
{
    s32 result = 1;

    if (!(fp->input.x624_lstick_y >= p_ftCommonData->x70_someLStickYMax) &&
        !(fp->input.x65C_heldInputs & 0xC00))
        result = 0;

    return result;
}
