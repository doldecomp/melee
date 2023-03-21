#include "ftCLink/ftclink.h"

#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftLink/ftlink.h"
#include "it/forward.h"
#include "lb/lbmthp.h"

MotionState as_table_clink[] = {
    { 295, 0x00240009, 0x0A000000, func_800CEDE0, func_800CEE00, func_800CEE30,
      func_800CEE50, func_800761C8 },
    { 239, 0x00000071, 0x01000000, func_80149354, func_8014943C, func_8014945C,
      func_8014947C, func_800761C8 },
    { 240, 0x00000071, 0x01000000, func_80149354, func_8014943C, func_8014945C,
      func_8014947C, func_800761C8 },
    { 296, 0x00340111, 0x12000000, func_800ED15C, func_800EDD88, func_800EDFD8,
      func_800EE098, func_800761C8 },
    { 297, 0x003C0111, 0x12000000, func_800ED480, func_800EDE30, func_800EDFF8,
      func_800EE120, func_800761C8 },
    { 298, 0x00340111, 0x12000000, func_800ED5B4, func_800EDEAC, func_800EE018,
      func_800EE1A8, func_800761C8 },
    { 299, 0x00340511, 0x12000000, func_800ED72C, func_800EDEB0, func_800EE038,
      func_800EE2E0, func_800761C8 },
    { 300, 0x003C0511, 0x12000000, func_800EDA58, func_800EDF58, func_800EE058,
      func_800EE368, func_800761C8 },
    { 301, 0x00340511, 0x12000000, func_800EDB8C, func_800EDFD4, func_800EE078,
      func_800EE3F0, func_800761C8 },
    { 302, 0x00340112, 0x13000000, func_800EC54C, NULL, func_800EC88C,
      func_800EC94C, func_800761C8 },
    { 303, 0x00340112, 0x13000000, func_800EC588, func_800EC71C, func_800EC8AC,
      func_800EC9C4, func_800761C8 },
    { 304, 0x00340112, 0x13000000, func_800EC5F8, NULL, func_800EC8CC,
      func_800ECA1C, func_800761C8 },
    { 305, 0x00340512, 0x13000000, func_800EC634, NULL, func_800EC8EC,
      func_800ECA88, func_800761C8 },
    { 306, 0x00340512, 0x13000000, func_800EC670, func_800EC810, func_800EC90C,
      func_800ECB00, func_800761C8 },
    { 307, 0x00340512, 0x13000000, func_800EC6E0, NULL, func_800EC92C,
      func_800ECB58, func_800761C8 },
    { 308, 0x00340213, 0x14000000, func_800EBC10, func_800EBCAC, func_800EBD30,
      func_800EBDC0, func_800761C8 },
    { 309, 0x00340213, 0x14000000, func_800EBC4C, func_800EBCB0, func_800EBCB4,
      func_800EBDFC, func_800761C8 },
    { 310, 0x00340014, 0x15000000, func_800EB8A4, NULL, func_800EB91C,
      func_800EB95C, func_800761C8 },
    { 311, 0x00340414, 0x15000000, func_800EB8E0, NULL, func_800EB93C,
      func_800EB9D4, func_800761C8 },
    { 312, 0x00200000, 0x01000000, func_800C3D6C, func_800C4384, func_800C438C,
      func_800C447C, func_800761C8 },
    { 313, 0x00C00000, 0x01000000, func_800C4380, func_800C4388, func_800C4438,
      func_80082B78, func_800761C8 },
};

char lbl_803D1240[] = "PlCl.dat";
char lbl_803D124C[] = "ftDataClink";
char lbl_803D1258[] = "PlClNr.dat";
char lbl_803D1264[] = "PlyClink5K_Share_joint";
char lbl_803D127C[] = "PlyClink5K_Share_matanim_joint";
char lbl_803D129C[] = "PlClRe.dat";
char lbl_803D12A8[] = "PlyClink5KRe_Share_joint";
char lbl_803D12C4[] = "PlyClink5KRe_Share_matanim_joint";
char lbl_803D12E8[] = "PlClBu.dat";
char lbl_803D12F4[] = "PlyClink5KBu_Share_joint";
char lbl_803D1310[] = "PlyClink5KBu_Share_matanim_joint";
char lbl_803D1334[] = "PlClWh.dat";
char lbl_803D1340[] = "PlyClink5KWh_Share_joint";
char lbl_803D135C[] = "PlyClink5KWh_Share_matanim_joint";
char lbl_803D1380[] = "PlClBk.dat";
char lbl_803D138C[] = "PlyClink5KBk_Share_joint";
char lbl_803D13A8[] = "PlyClink5KBk_Share_matanim_joint";
char lbl_803D13CC[] = "PlClAJ.dat";

Fighter_DemoStrings lbl_803D1448 = {
    "ftDemoResultMotionFileClink",
    "ftDemoIntroMotionFileClink",
    "ftDemoEndingMotionFileClink",
    "ftDemoViWaitMotionFileClink",
};

Fighter_CostumeStrings lbl_803D1458[] = {
    { lbl_803D1258, lbl_803D1264, lbl_803D127C },
    { lbl_803D129C, lbl_803D12A8, lbl_803D12C4 },
    { lbl_803D12E8, lbl_803D12F4, lbl_803D1310 },
    { lbl_803D1334, lbl_803D1340, lbl_803D135C },
    { lbl_803D1380, lbl_803D138C, lbl_803D13A8 },
};

void ftCLink_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    func_80074A4C(gobj, 2, 0);
    fp->fv.cl.x222C = 0;
    fp->fv.cl.x2234 = 0;
    fp->fv.cl.x2238 = 0;
    fp->fv.cl.x223C = 0;
    fp->fv.cl.x2240 = 0;
    fp->fv.cl.x2238 = 0;
    fp->fv.cl.x2244 = 0;
}

void ftCLink_OnLoad(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    CLinkAttributes* attrs = (void*) ftdata->ext_attr;
    void** items = ftdata->x48_items;

    fp->x2224_flag.bits.b7 = true;
    attrs->x54 = func_8001E8F8(func_80085E50(fp, 0x48));
    ftLink_OnLoadForCLink(fp);
    attrs = fp->x2D4_specialAttributes;
    func_8026B3F8(items[0], attrs->x48);
    func_8026B3F8(items[1], attrs->x2C);
    func_8026B3F8(items[2], attrs->xBC);
    func_8026B3F8(items[3], attrs->xC);
    func_8026B3F8(items[4], attrs->x10);
    func_8026B3F8(items[5], It_Kind_CLink_Milk);
    func_800753D4(fp, *lbl_804D6540[fp->x4_fighterKind], items[6]);
}

void ftCLink_OnItemPickupExt(HSD_GObj* gobj, bool arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = gobj->user_data;

    if (func_8026B2B4(fp->x1974_heldItem) == true)
        func_80074A4C(gobj, 1, 1);

    func_80074A4C(gobj, 2, 1);
    ftCLink_OnItemPickup(gobj, arg1);
}

void ftCLink_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftCLink_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftCLink_OnItemDropExt(HSD_GObj* gobj, bool arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = gobj->user_data;

    if (func_8026B2B4(fp->x1974_heldItem) == true)
        func_80074A4C(gobj, 1, 0);

    func_80074A4C(gobj, 2, 0);
    ftCLink_OnItemDrop(gobj, arg1);
}

void ftCLink_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftCLink_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftCLink_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftLink_LoadSpecialAttrs(gobj);
}

void ftCLink_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftCLink_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void func_80149114(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CLinkAttributes* temp_r4 = (void*) fp->x10C_ftData->ext_attr;
    f32 ftmp = func_80092ED8(fp->x19A4, temp_r4, temp_r4->xD8);
    fp->xEC_ground_vel = ftmp * p_ftCommonData->x294;
    if (fp->x19AC < 0.0f) {
        ftmp = fp->xEC_ground_vel;
    } else {
        ftmp = -fp->xEC_ground_vel;
    }
    fp->xEC_ground_vel = ftmp;
    func_80088148(fp, 0x111DA, 0x7F, 0x40);
}

void func_8014919C(HSD_GObj* gobj)
{
    CLinkAttributes* attrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    if (fp->x5F8 == 0) {
        attrs = (void*) fp->x2D4_specialAttributes;
        func_8007B1B8(gobj, &attrs->xC4, func_80149114);
        fp->x221B_b3 = true;
        fp->x221B_b4 = true;
        fp->x221B_b2 = true;
    }
}

bool func_8014920C(HSD_GObj* gobj)
{
    s32 temp_r0;
    Fighter* fp;

    if (gobj == NULL) {
        return true;
    }
    fp = gobj->user_data;
    if (fp == NULL) {
        return true;
    }
    temp_r0 = fp->motion_id;
    if (temp_r0 != 0x156 && temp_r0 != 0x157) {
        return true;
    }
    if (fp->fv.cl.x2244 == 0) {
        return true;
    }
    return false;
}

void func_80149268(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    checkFighter2244(gobj);
}

void func_801492C4(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL) {
        return;
    }

    fp = gobj->user_data;
    if (fp != NULL && fp->fv.cl.x2244 != 0) {
        fp->fv.cl.x2244 = 0;
    };

    if (gobj == NULL) {
        return;
    }
}

u32 func_801492F4(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            return fp->x2204_ftcmd_var1;
        }
    }
    return 0;
}

void func_80149318(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_800DEAE8(gobj, 0x156, 0x157);
    fp->x2204_ftcmd_var1 = 0;
}
