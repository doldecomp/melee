#include "it/forward.h"

#include "ftCLink/ftCLink_Init.h"

#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftLink/ftlink.h"
#include "lb/lbmthp.h"

MotionState ftCLink_MotionStateTable[] = {
    { 295, 0x00240009, 0x0A000000, ftLink_800CEDE0, ftLink_800CEE00,
      ftLink_800CEE30, ftLink_800CEE50, ftCamera_UpdateCameraBox },
    { 239, 0x00000071, 0x01000000, ftCLink_80149354, ftCLink_8014943C,
      ftCLink_8014945C, ftCLink_8014947C, ftCamera_UpdateCameraBox },
    { 240, 0x00000071, 0x01000000, ftCLink_80149354, ftCLink_8014943C,
      ftCLink_8014945C, ftCLink_8014947C, ftCamera_UpdateCameraBox },
    { 296, 0x00340111, 0x12000000, ftLink_800ED15C, ftLink_800EDD88,
      ftLink_800EDFD8, ftLink_800EE098, ftCamera_UpdateCameraBox },
    { 297, 0x003C0111, 0x12000000, ftLink_800ED480, ftLink_800EDE30,
      ftLink_800EDFF8, ftLink_800EE120, ftCamera_UpdateCameraBox },
    { 298, 0x00340111, 0x12000000, ftLink_800ED5B4, ftLink_800EDEAC,
      ftLink_800EE018, ftLink_800EE1A8, ftCamera_UpdateCameraBox },
    { 299, 0x00340511, 0x12000000, ftLink_800ED72C, ftLink_800EDEB0,
      ftLink_800EE038, ftLink_800EE2E0, ftCamera_UpdateCameraBox },
    { 300, 0x003C0511, 0x12000000, ftLink_800EDA58, ftLink_800EDF58,
      ftLink_800EE058, ftLink_800EE368, ftCamera_UpdateCameraBox },
    { 301, 0x00340511, 0x12000000, ftLink_800EDB8C, ftLink_800EDFD4,
      ftLink_800EE078, ftLink_800EE3F0, ftCamera_UpdateCameraBox },
    { 302, 0x00340112, 0x13000000, ftLink_800EC54C, NULL, ftLink_800EC88C,
      ftLink_800EC94C, ftCamera_UpdateCameraBox },
    { 303, 0x00340112, 0x13000000, ftLink_800EC588, ftLink_800EC71C,
      ftLink_800EC8AC, ftLink_800EC9C4, ftCamera_UpdateCameraBox },
    { 304, 0x00340112, 0x13000000, ftLink_800EC5F8, NULL, ftLink_800EC8CC,
      ftLink_800ECA1C, ftCamera_UpdateCameraBox },
    { 305, 0x00340512, 0x13000000, ftLink_800EC634, NULL, ftLink_800EC8EC,
      ftLink_800ECA88, ftCamera_UpdateCameraBox },
    { 306, 0x00340512, 0x13000000, ftLink_800EC670, ftLink_800EC810,
      ftLink_800EC90C, ftLink_800ECB00, ftCamera_UpdateCameraBox },
    { 307, 0x00340512, 0x13000000, ftLink_800EC6E0, NULL, ftLink_800EC92C,
      ftLink_800ECB58, ftCamera_UpdateCameraBox },
    { 308, 0x00340213, 0x14000000, ftLink_800EBC10, ftLink_800EBCAC,
      ftLink_800EBD30, ftLink_800EBDC0, ftCamera_UpdateCameraBox },
    { 309, 0x00340213, 0x14000000, ftLink_800EBC4C, ftLink_800EBCB0,
      ftLink_800EBCB4, ftLink_800EBDFC, ftCamera_UpdateCameraBox },
    { 310, 0x00340014, 0x15000000, ftLink_800EB8A4, NULL, ftLink_800EB91C,
      ftLink_800EB95C, ftCamera_UpdateCameraBox },
    { 311, 0x00340414, 0x15000000, ftLink_800EB8E0, NULL, ftLink_800EB93C,
      ftLink_800EB9D4, ftCamera_UpdateCameraBox },
    { 312, 0x00200000, 0x01000000, ftLink_800C3D6C, ftLink_800C4384,
      ftLink_800C438C, ftLink_800C447C, ftCamera_UpdateCameraBox },
    { 313, 0x00C00000, 0x01000000, ftLink_800C4380, ftLink_800C4388,
      ftLink_800C4438, ftLink_80082B78, ftCamera_UpdateCameraBox },
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
    ftData* ftdata = fp->ft_data;
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

void ftCLink_80149114(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CLinkAttributes* temp_r4 = (void*) fp->ft_data->ext_attr;
    f32 ftmp = func_80092ED8(fp->x19A4, temp_r4, temp_r4->xD8);
    fp->gr_vel = ftmp * p_ftCommonData->x294;
    if (fp->x19AC < 0.0f) {
        ftmp = fp->gr_vel;
    } else {
        ftmp = -fp->gr_vel;
    }
    fp->gr_vel = ftmp;
    func_80088148(fp, 0x111DA, 0x7F, 0x40);
}

void ftCLink_8014919C(HSD_GObj* gobj)
{
    CLinkAttributes* attrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    if (fp->x5F8 == 0) {
        attrs = (void*) fp->x2D4_specialAttributes;
        func_8007B1B8(gobj, &attrs->xC4, ftCLink_80149114);
        fp->x221B_b3 = true;
        fp->x221B_b4 = true;
        fp->x221B_b2 = true;
    }
}

bool ftCLink_8014920C(HSD_GObj* gobj)
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

void ftCLink_80149268(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    checkFighter2244(gobj);
}

void ftCLink_801492C4(HSD_GObj* gobj)
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

u32 ftCLink_801492F4(HSD_GObj* gobj)
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

void ftCLink_80149318(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_800DEAE8(gobj, 0x156, 0x157);
    fp->x2204_ftcmd_var1 = 0;
}
