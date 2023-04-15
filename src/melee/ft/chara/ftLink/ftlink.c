#include "ft/forward.h"

#include "ftlink.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCLink/ftCLink_Init.h"
#include "lb/lbmthp.h"

#include <dolphin/mtx/types.h>

MotionState ftLk_Init_MotionStateTable[] = {
    { 295, 0x00240009, 0x0A000000, ftLk_0877_800CEDE0, ftLk_0877_800CEE00,
      ftLk_0877_800CEE30, ftLk_0877_800CEE50, ftCamera_UpdateCameraBox },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
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

char ftLk_Init_DatFilename[] = "PlLk.dat";
char ftLk_Init_DataName[] = "ftDataLink";
char ftLk_803C80D0[] = "PlLkNr.dat";
char ftLk_803C80DC[] = "PlyLink5K_Share_joint";
char ftLk_803C80F4[] = "PlyLink5K_Share_matanim_joint";
char ftLk_803C8114[] = "PlLkRe.dat";
char ftLk_803C8120[] = "PlyLink5KRe_Share_joint";
char ftLk_803C8138[] = "PlyLink5KRe_Share_matanim_joint";
char ftLk_803C8158[] = "PlLkBu.dat";
char ftLk_803C8164[] = "PlyLink5KBu_Share_joint";
char ftLk_803C817C[] = "PlyLink5KBu_Share_matanim_joint";
char ftLk_803C819C[] = "PlLkBk.dat";
char ftLk_803C81A8[] = "PlyLink5KBk_Share_joint";
char ftLk_803C81C0[] = "PlyLink5KBk_Share_matanim_joint";
char ftLk_803C81E0[] = "PlLkWh.dat";
char ftLk_803C81EC[] = "PlyLink5KWh_Share_joint";
char ftLk_803C8204[] = "PlyLink5KWh_Share_matanim_joint";
char ftLk_Init_AnimDatFilename[] = "PlLkAJ.dat";

Fighter_DemoStrings ftLk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileLink",
    "ftDemoIntroMotionFileLink",
    "ftDemoEndingMotionFileLink",
    "ftDemoViWaitMotionFileLink",
};

Fighter_CostumeStrings ftLk_Init_CostumeStrings[] = {
    { ftLk_803C80D0, ftLk_803C80DC, ftLk_803C80F4 },
    { ftLk_803C8114, ftLk_803C8120, ftLk_803C8138 },
    { ftLk_803C8158, ftLk_803C8164, ftLk_803C817C },
    { ftLk_803C819C, ftLk_803C81A8, ftLk_803C81C0 },
    { ftLk_803C81E0, ftLk_803C81EC, ftLk_803C8204 },
};

int ftLk_803C82EC[31] = { 0 };

Vec3 const lbl_803B7520[3] = { 0 };

bool ftLk_800EAD64(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.lk.x2234) {
        return true;
    }

    return false;
}

void ftLk_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    ftParts_80074A4C(gobj, 2, 0);

    fp->fv.lk.x222C = 0;
    fp->fv.lk.x2234 = 0;
    fp->fv.lk.x2238 = 0;
    fp->fv.lk.x223C = 0;
    fp->fv.lk.x2240 = 0;
    fp->fv.lk.x2238 = 0;
    fp->fv.lk.x2244 = 0;
}

void ftLk_OnLoadForCLink(Fighter* fp)
{
    PUSH_ATTRS(fp, ftLinkAttributes);
}

void ftLk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLinkAttributes* link_attr = fp->ft_data->ext_attr;
    void** item_list = fp->ft_data->x48_items;
    link_attr->x54 = lbMthp_8001E8F8(ftData_80085E50(fp, 0x48U));
    PUSH_ATTRS(fp, ftLinkAttributes);

    link_attr = fp->x2D4_specialAttributes;
    it_8026B3F8(item_list[0], link_attr->x48);
    it_8026B3F8(item_list[1], link_attr->x2C);
    it_8026B3F8(item_list[2], link_attr->xBC);
    it_8026B3F8(item_list[3], link_attr->xC);
    it_8026B3F8(item_list[4], link_attr->x10);
    ftParts_800753D4(fp, *lbl_804D6540[fp->x4_fighterKind], item_list[6]);
}

void ftLk_800EAF38(void)
{
    ftLk_800EC06C();
}

void ftLk_800EAF58(HSD_GObj* gobj)
{
    ftLk_800EC06C();
    ft_800D94D8(gobj);
    ftLk_800ECD04(gobj);
    ftLk_800ECD58(gobj);
    ftCl_Init_80149268(gobj);
}

void ftLk_Init_OnItemPickupExt(HSD_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (it_8026B2B4(fp->x1974_heldItem) == 1) {
        ftParts_80074A4C(gobj, 1, 1);
    }
    ftParts_80074A4C(gobj, 2, 1);
    ftLk_Init_OnItemPickup(gobj, arg1);
}

void ftLk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftLk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftLk_Init_OnItemDropExt(HSD_GObj* gobj, bool arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (it_8026B2B4(fp->x1974_heldItem) == 1) {
        ftParts_80074A4C(gobj, 1, 0);
    }
    ftParts_80074A4C(gobj, 2, 0);
    ftLk_Init_OnItemDrop(gobj, arg1);
}

void ftLk_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftLk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftLk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftLinkAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x28 *= fp->x34_scale.y;
    }
}

void ftLk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftLk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftLk_800EB334(HSD_GObj* gobj)
{
    f32 new_ground_vel;

    Fighter* fp = GET_FIGHTER(gobj);
    ftLinkAttributes* link_attr = fp->ft_data->ext_attr;

    f32 resultf = ft_80092ED8(fp->x19A4, link_attr, link_attr->xD8);
    fp->gr_vel = resultf * p_ftCommonData->x294;
    if (fp->x19AC < 0.0f) {
        new_ground_vel = fp->gr_vel;
    } else {
        new_ground_vel = -fp->gr_vel;
    }
    fp->gr_vel = new_ground_vel;
    ft_80088148(fp, 0x2716AU, 0x7FU, 0x40U);
}
