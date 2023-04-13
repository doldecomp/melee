#include "ft/forward.h"

#include "ftlink.h"

#include "ft/code_80081B38.h"
#include "ft/fighter.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCLink/ftclink.h"
#include "lb/lbmthp.h"

ActionState ftLink_MotionStateTable[] = {
    { 295, 0x00240009, 0x0A000000, ftLink_800CEDE0, ftLink_800CEE00,
      ftLink_800CEE30, ftLink_800CEE50, ftCamera_UpdateCameraBox },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
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

char lbl_803C80B8[] = "PlLk.dat";
char lbl_803C80C4[] = "ftDataLink";
char lbl_803C80D0[] = "PlLkNr.dat";
char lbl_803C80DC[] = "PlyLink5K_Share_joint";
char lbl_803C80F4[] = "PlyLink5K_Share_matanim_joint";
char lbl_803C8114[] = "PlLkRe.dat";
char lbl_803C8120[] = "PlyLink5KRe_Share_joint";
char lbl_803C8138[] = "PlyLink5KRe_Share_matanim_joint";
char lbl_803C8158[] = "PlLkBu.dat";
char lbl_803C8164[] = "PlyLink5KBu_Share_joint";
char lbl_803C817C[] = "PlyLink5KBu_Share_matanim_joint";
char lbl_803C819C[] = "PlLkBk.dat";
char lbl_803C81A8[] = "PlyLink5KBk_Share_joint";
char lbl_803C81C0[] = "PlyLink5KBk_Share_matanim_joint";
char lbl_803C81E0[] = "PlLkWh.dat";
char lbl_803C81EC[] = "PlyLink5KWh_Share_joint";
char lbl_803C8204[] = "PlyLink5KWh_Share_matanim_joint";
char lbl_803C8224[] = "PlLkAJ.dat";

Fighter_DemoStrings lbl_803C82A0 = {
    "ftDemoResultMotionFileLink",
    "ftDemoIntroMotionFileLink",
    "ftDemoEndingMotionFileLink",
    "ftDemoViWaitMotionFileLink",
};

Fighter_CostumeStrings lbl_803C82B0[] = {
    { lbl_803C80D0, lbl_803C80DC, lbl_803C80F4 },
    { lbl_803C8114, lbl_803C8120, lbl_803C8138 },
    { lbl_803C8158, lbl_803C8164, lbl_803C817C },
    { lbl_803C819C, lbl_803C81A8, lbl_803C81C0 },
    { lbl_803C81E0, lbl_803C81EC, lbl_803C8204 },
};

int lbl_803C82EC[31] = { 0 };

Vec3 const lbl_803B7520[3] = { 0 };

bool ftLink_800EAD64(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->ev.lk.x2234) {
        return true;
    }

    return false;
}

void ftLink_OnDeath(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftParts_80074A4C(fighter_gobj, 0, 0);
    ftParts_80074A4C(fighter_gobj, 1, 0);
    ftParts_80074A4C(fighter_gobj, 2, 0);

    fp->ev.lk.x222C = 0;
    fp->ev.lk.x2234 = 0;
    fp->ev.lk.x2238 = 0;
    fp->ev.lk.x223C = 0;
    fp->ev.lk.x2240 = 0;
    fp->ev.lk.x2238 = 0;
    fp->ev.lk.x2244 = 0;
}

void ftLink_OnLoadForCLink(Fighter* fp)
{
    PUSH_ATTRS(fp, ftLinkAttributes);
}

void ftLink_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLinkAttributes* link_attr = fp->x10C_ftData->ext_attr;
    void** item_list = fp->x10C_ftData->x48_items;
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

void ftLink_800EAF38(void)
{
    ftLink_800EC06C();
}

void ftLink_800EAF58(HSD_GObj* fighter_gobj)
{
    ftLink_800EC06C();
    ft_800D94D8(fighter_gobj);
    ftLink_800ECD04(fighter_gobj);
    ftLink_800ECD58(fighter_gobj);
    ftCLink_80149268(fighter_gobj);
}

void ftLink_OnItemPickupExt(HSD_GObj* fighter_gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (it_8026B2B4(fp->x1974_heldItem) == 1) {
        ftParts_80074A4C(fighter_gobj, 1, 1);
    }
    ftParts_80074A4C(fighter_gobj, 2, 1);
    ftLink_OnItemPickup(fighter_gobj, arg1);
}

void ftLink_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftLink_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftLink_OnItemDropExt(HSD_GObj* fighter_gobj, bool arg1)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (it_8026B2B4(fp->x1974_heldItem) == 1) {
        ftParts_80074A4C(fighter_gobj, 1, 0);
    }
    ftParts_80074A4C(fighter_gobj, 2, 0);
    ftLink_OnItemDrop(fighter_gobj, arg1);
}

void ftLink_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftLink_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftLink_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftLinkAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x28 *= fp->x34_scale.y;
    }
}

void ftLink_OnKnockbackEnter(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftLink_OnKnockbackExit(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}

void ftLink_800EB334(HSD_GObj* fighter_gobj)
{
    f32 new_ground_vel;

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLinkAttributes* link_attr = fp->x10C_ftData->ext_attr;

    f32 resultf = ft_80092ED8(fp->x19A4, link_attr, link_attr->xD8);
    fp->xEC_ground_vel = resultf * p_ftCommonData->x294;
    if (fp->x19AC < 0.0f) {
        new_ground_vel = fp->xEC_ground_vel;
    } else {
        new_ground_vel = -fp->xEC_ground_vel;
    }
    fp->xEC_ground_vel = new_ground_vel;
    ft_80088148(fp, 0x2716AU, 0x7FU, 0x40U);
}
