#include "it/forward.h"

#include "ftCLink_Init.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftLink/ftlink.h"
#include "lb/lbmthp.h"

MotionState ftCl_Init_MotionStateTable[] = {
    { 295, 0x00240009, 0x0A000000, ftLk_0877_800CEDE0, ftLk_0877_800CEE00,
      ftLk_0877_800CEE30, ftLk_0877_800CEE50, ftCamera_UpdateCameraBox },
    { 239, 0x00000071, 0x01000000, ftCl_Unk2_80149354, ftCl_Unk2_8014943C,
      ftCl_Unk2_8014945C, ftCl_Unk2_8014947C, ftCamera_UpdateCameraBox },
    { 240, 0x00000071, 0x01000000, ftCl_Unk2_80149354, ftCl_Unk2_8014943C,
      ftCl_Unk2_8014945C, ftCl_Unk2_8014947C, ftCamera_UpdateCameraBox },
    { 296, 0x00340111, 0x12000000, ftLk_800ED15C, ftLk_800EDD88, ftLk_800EDFD8,
      ftLk_800EE098, ftCamera_UpdateCameraBox },
    { 297, 0x003C0111, 0x12000000, ftLk_800ED480, ftLk_800EDE30, ftLk_800EDFF8,
      ftLk_800EE120, ftCamera_UpdateCameraBox },
    { 298, 0x00340111, 0x12000000, ftLk_800ED5B4, ftLk_800EDEAC, ftLk_800EE018,
      ftLk_800EE1A8, ftCamera_UpdateCameraBox },
    { 299, 0x00340511, 0x12000000, ftLk_800ED72C, ftLk_800EDEB0, ftLk_800EE038,
      ftLk_800EE2E0, ftCamera_UpdateCameraBox },
    { 300, 0x003C0511, 0x12000000, ftLk_800EDA58, ftLk_800EDF58, ftLk_800EE058,
      ftLk_800EE368, ftCamera_UpdateCameraBox },
    { 301, 0x00340511, 0x12000000, ftLk_800EDB8C, ftLk_800EDFD4, ftLk_800EE078,
      ftLk_800EE3F0, ftCamera_UpdateCameraBox },
    { 302, 0x00340112, 0x13000000, ftLk_800EC54C, NULL, ftLk_800EC88C,
      ftLk_800EC94C, ftCamera_UpdateCameraBox },
    { 303, 0x00340112, 0x13000000, ftLk_800EC588, ftLk_800EC71C, ftLk_800EC8AC,
      ftLk_800EC9C4, ftCamera_UpdateCameraBox },
    { 304, 0x00340112, 0x13000000, ftLk_800EC5F8, NULL, ftLk_800EC8CC,
      ftLk_800ECA1C, ftCamera_UpdateCameraBox },
    { 305, 0x00340512, 0x13000000, ftLk_800EC634, NULL, ftLk_800EC8EC,
      ftLk_800ECA88, ftCamera_UpdateCameraBox },
    { 306, 0x00340512, 0x13000000, ftLk_800EC670, ftLk_800EC810, ftLk_800EC90C,
      ftLk_800ECB00, ftCamera_UpdateCameraBox },
    { 307, 0x00340512, 0x13000000, ftLk_800EC6E0, NULL, ftLk_800EC92C,
      ftLk_800ECB58, ftCamera_UpdateCameraBox },
    { 308, 0x00340213, 0x14000000, ftLk_800EBC10, ftLk_800EBCAC, ftLk_800EBD30,
      ftLk_800EBDC0, ftCamera_UpdateCameraBox },
    { 309, 0x00340213, 0x14000000, ftLk_800EBC4C, ftLk_800EBCB0, ftLk_800EBCB4,
      ftLk_800EBDFC, ftCamera_UpdateCameraBox },
    { 310, 0x00340014, 0x15000000, ftLk_800EB8A4, NULL, ftLk_800EB91C,
      ftLk_800EB95C, ftCamera_UpdateCameraBox },
    { 311, 0x00340414, 0x15000000, ftLk_800EB8E0, NULL, ftLk_800EB93C,
      ftLk_800EB9D4, ftCamera_UpdateCameraBox },
    { 312, 0x00200000, 0x01000000, ftLk_0877_800C3D6C, ftLk_0877_800C4384,
      ftLk_0877_800C438C, ftLk_0877_800C447C, ftCamera_UpdateCameraBox },
    { 313, 0x00C00000, 0x01000000, ftLk_0877_800C4380, ftLk_0877_800C4388,
      ftLk_0877_800C4438, ftLk_80082B78, ftCamera_UpdateCameraBox },
};

char ftCl_Init_DatFilename[] = "PlCl.dat";
char ftCl_Init_DataName[] = "ftDataClink";
char ftCl_Init_803D1258[] = "PlClNr.dat";
char ftCl_Init_803D1264[] = "PlyClink5K_Share_joint";
char ftCl_Init_803D127C[] = "PlyClink5K_Share_matanim_joint";
char ftCl_Init_803D129C[] = "PlClRe.dat";
char ftCl_Init_803D12A8[] = "PlyClink5KRe_Share_joint";
char ftCl_Init_803D12C4[] = "PlyClink5KRe_Share_matanim_joint";
char ftCl_Init_803D12E8[] = "PlClBu.dat";
char ftCl_Init_803D12F4[] = "PlyClink5KBu_Share_joint";
char ftCl_Init_803D1310[] = "PlyClink5KBu_Share_matanim_joint";
char ftCl_Init_803D1334[] = "PlClWh.dat";
char ftCl_Init_803D1340[] = "PlyClink5KWh_Share_joint";
char ftCl_Init_803D135C[] = "PlyClink5KWh_Share_matanim_joint";
char ftCl_Init_803D1380[] = "PlClBk.dat";
char ftCl_Init_803D138C[] = "PlyClink5KBk_Share_joint";
char ftCl_Init_803D13A8[] = "PlyClink5KBk_Share_matanim_joint";
char ftCl_Init_AnimDatFilename[] = "PlClAJ.dat";

Fighter_DemoStrings ftCl_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileClink",
    "ftDemoIntroMotionFileClink",
    "ftDemoEndingMotionFileClink",
    "ftDemoViWaitMotionFileClink",
};

Fighter_CostumeStrings ftCl_Init_CostumeStrings[] = {
    { ftCl_Init_803D1258, ftCl_Init_803D1264, ftCl_Init_803D127C },
    { ftCl_Init_803D129C, ftCl_Init_803D12A8, ftCl_Init_803D12C4 },
    { ftCl_Init_803D12E8, ftCl_Init_803D12F4, ftCl_Init_803D1310 },
    { ftCl_Init_803D1334, ftCl_Init_803D1340, ftCl_Init_803D135C },
    { ftCl_Init_803D1380, ftCl_Init_803D138C, ftCl_Init_803D13A8 },
};

void ftCl_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    ftParts_80074A4C(gobj, 2, 0);
    fp->fv.cl.x222C = 0;
    fp->fv.cl.x2234 = 0;
    fp->fv.cl.x2238 = 0;
    fp->fv.cl.x223C = 0;
    fp->fv.cl.x2240 = 0;
    fp->fv.cl.x2238 = 0;
    fp->fv.cl.x2244 = 0;
}

void ftCl_Init_OnLoad(HSD_GObj* gobj)
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
    attrs->x54 = lbMthp_8001E8F8(ftData_80085E50(fp, 0x48));
    ftLk_OnLoadForCLink(fp);
    attrs = fp->x2D4_specialAttributes;
    it_8026B3F8(items[0], attrs->x48);
    it_8026B3F8(items[1], attrs->x2C);
    it_8026B3F8(items[2], attrs->xBC);
    it_8026B3F8(items[3], attrs->xC);
    it_8026B3F8(items[4], attrs->x10);
    it_8026B3F8(items[5], It_Kind_CLink_Milk);
    ftParts_800753D4(fp, *lbl_804D6540[fp->x4_fighterKind], items[6]);
}

void ftCl_Init_OnItemPickupExt(HSD_GObj* gobj, bool arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = gobj->user_data;

    if (it_8026B2B4(fp->x1974_heldItem) == true) {
        ftParts_80074A4C(gobj, 1, 1);
    }

    ftParts_80074A4C(gobj, 2, 1);
    ftCl_Init_OnItemPickup(gobj, arg1);
}

void ftCl_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftCl_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftCl_Init_OnItemDropExt(HSD_GObj* gobj, bool arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = gobj->user_data;

    if (it_8026B2B4(fp->x1974_heldItem) == true) {
        ftParts_80074A4C(gobj, 1, 0);
    }

    ftParts_80074A4C(gobj, 2, 0);
    ftCl_Init_OnItemDrop(gobj, arg1);
}

void ftCl_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftCl_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftCl_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftLk_Init_LoadSpecialAttrs(gobj);
}

void ftCl_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftCl_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftCl_Init_80149114(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CLinkAttributes* temp_r4 = (void*) fp->ft_data->ext_attr;
    f32 ftmp = ft_80092ED8(fp->x19A4, temp_r4, temp_r4->xD8);
    fp->gr_vel = ftmp * p_ftCommonData->x294;
    if (fp->x19AC < 0.0f) {
        ftmp = fp->gr_vel;
    } else {
        ftmp = -fp->gr_vel;
    }
    fp->gr_vel = ftmp;
    ft_80088148(fp, 0x111DA, 0x7F, 0x40);
}

void ftCl_Init_8014919C(HSD_GObj* gobj)
{
    CLinkAttributes* attrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    if (fp->x5F8 == 0) {
        attrs = (void*) fp->x2D4_specialAttributes;
        ftColl_8007B1B8(gobj, &attrs->xC4, ftCl_Init_80149114);
        fp->x221B_b3 = true;
        fp->x221B_b4 = true;
        fp->x221B_b2 = true;
    }
}

bool ftCl_Init_8014920C(HSD_GObj* gobj)
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

void ftCl_Init_80149268(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    checkFighter2244(gobj);
}

void ftCl_Init_801492C4(HSD_GObj* gobj)
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

u32 ftCl_Init_801492F4(HSD_GObj* gobj)
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

void ftCl_Init_80149318(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ft_800DEAE8(gobj, 0x156, 0x157);
    fp->x2204_ftcmd_var1 = 0;
}
