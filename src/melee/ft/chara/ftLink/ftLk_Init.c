#include "forward.h"
#include "ft/forward.h"

#include "ftLk_Init.h"

#include "ftLk_SpecialHi.h"
#include "ftLk_SpecialLw.h"
#include "ftLk_SpecialN.h"
#include "ftLk_SpecialS.h"
#include "types.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCLink/ftCl_Init.h"
#include "lb/lbmthp.h"

#include <dolphin/mtx/types.h>

MotionState ftLk_Init_MotionStateTable[] = {
    {
        295,
        ftLk_MF_AttackS42,
        FtMoveId_AttackS4 << 24,
        ftCo_AttackS42_Anim,
        ftCo_AttackS42_IASA,
        ftCo_AttackS42_Phys,
        ftCo_AttackS42_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        -1,
        0,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        -1,
        0,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        296,
        ftLk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialNCharge_Anim,
        ftLk_SpecialNCharge_IASA,
        ftLk_SpecialNCharge_Phys,
        ftLk_SpecialNCharge_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        ftLk_MF_SpecialNFullyCharged,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialNFullyCharged_Anim,
        ftLk_SpecialNFullyCharged_IASA,
        ftLk_SpecialNFullyCharged_Phys,
        ftLk_SpecialNFullyCharged_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        ftLk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialNFire_Anim,
        ftLk_SpecialNFire_IASA,
        ftLk_SpecialNFire_Phys,
        ftLk_SpecialNFire_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        ftLk_MF_SpecialAirNCharge,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialAirNCharge_Anim,
        ftLk_SpecialAirNCharge_IASA,
        ftLk_SpecialAirNCharge_Phys,
        ftLk_SpecialAirNCharge_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        ftLk_MF_SpecialAirNFullyCharged,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialAirNFullyCharged_Anim,
        ftLk_SpecialAirNFullyCharged_IASA,
        ftLk_SpecialAirNFullyCharged_Phys,
        ftLk_SpecialAirNFullyCharged_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        ftLk_MF_SpecialAirNFire,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialAirNFire_Anim,
        ftLk_SpecialAirNFire_IASA,
        ftLk_SpecialAirNFire_Phys,
        ftLk_SpecialAirNFire_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        ftLk_MF_SpecialSThrow,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialSThrow_Anim,
        NULL,
        ftLk_SpecialSThrow_Phys,
        ftLk_SpecialSThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        ftLk_MF_SpecialSCatch,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialSCatch_Anim,
        ftLk_SpecialSCatch_IASA,
        ftLk_SpecialSCatch_Phys,
        ftLk_SpecialSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        ftLk_MF_SpecialSCatch,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialSThrowEmpty_Anim,
        NULL,
        ftLk_SpecialSThrowEmpty_Phys,
        ftLk_SpecialSThrowEmpty_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        ftLk_MF_SpecialAirSThrow,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialAirSThrow_Anim,
        NULL,
        ftLk_SpecialAirSThrow_Phys,
        ftLk_SpecialAirSThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        ftLk_MF_SpecialAirSThrow,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialAirSCatch_Anim,
        ftLk_SpecialAirSCatch_IASA,
        ftLk_SpecialAirSCatch_Phys,
        ftLk_SpecialAirSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        ftLk_MF_SpecialAirSThrowEmpty,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialAirSThrowEmpty_Anim,
        NULL,
        ftLk_SpecialAirSThrowEmpty_Phys,
        ftLk_SpecialAirSThrowEmpty_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        ftLk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftLk_SpecialHi_Anim,
        ftLk_SpecialHi_IASA,
        ftLk_SpecialHi_Phys,
        ftLk_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        ftLk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftLk_SpecialAirHi_Anim,
        ftLk_SpecialAirHi_IASA,
        ftLk_SpecialAirHi_Phys,
        ftLk_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        ftLk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftLk_SpecialLw_Anim,
        NULL,
        ftLk_SpecialLw_Phys,
        ftLk_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        311,
        ftLk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftLk_SpecialAirLw_Anim,
        NULL,
        ftLk_SpecialAirLw_Phys,
        ftLk_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        312,
        FtStateChange_FreezeState,
        FtMoveId_Default << 24,
        ftCo_Zair_Anim,
        ftCo_Zair_IASA,
        ftCo_Zair_Phys,
        ftCo_Zair_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        313,
        ftLk_MF_ZairCatch,
        FtMoveId_Default << 24,
        ftCo_ZairCatch_Anim,
        ftCo_ZairCatch_IASA,
        ftCo_ZairCatch_Phys,
        ftCo_ZairCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftLk_Init_DatFilename[] = "PlLk.dat";
char ftLk_Init_DataName[] = "ftDataLink";
char ftLk_Init_803C80D0[] = "PlLkNr.dat";
char ftLk_Init_803C80DC[] = "PlyLink5K_Share_joint";
char ftLk_Init_803C80F4[] = "PlyLink5K_Share_matanim_joint";
char ftLk_Init_803C8114[] = "PlLkRe.dat";
char ftLk_Init_803C8120[] = "PlyLink5KRe_Share_joint";
char ftLk_Init_803C8138[] = "PlyLink5KRe_Share_matanim_joint";
char ftLk_Init_803C8158[] = "PlLkBu.dat";
char ftLk_Init_803C8164[] = "PlyLink5KBu_Share_joint";
char ftLk_Init_803C817C[] = "PlyLink5KBu_Share_matanim_joint";
char ftLk_Init_803C819C[] = "PlLkBk.dat";
char ftLk_Init_803C81A8[] = "PlyLink5KBk_Share_joint";
char ftLk_Init_803C81C0[] = "PlyLink5KBk_Share_matanim_joint";
char ftLk_Init_803C81E0[] = "PlLkWh.dat";
char ftLk_Init_803C81EC[] = "PlyLink5KWh_Share_joint";
char ftLk_Init_803C8204[] = "PlyLink5KWh_Share_matanim_joint";
char ftLk_Init_AnimDatFilename[] = "PlLkAJ.dat";

Fighter_DemoStrings ftLk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileLink",
    "ftDemoIntroMotionFileLink",
    "ftDemoEndingMotionFileLink",
    "ftDemoViWaitMotionFileLink",
};

Fighter_CostumeStrings ftLk_Init_CostumeStrings[] = {
    { ftLk_Init_803C80D0, ftLk_Init_803C80DC, ftLk_Init_803C80F4 },
    { ftLk_Init_803C8114, ftLk_Init_803C8120, ftLk_Init_803C8138 },
    { ftLk_Init_803C8158, ftLk_Init_803C8164, ftLk_Init_803C817C },
    { ftLk_Init_803C819C, ftLk_Init_803C81A8, ftLk_Init_803C81C0 },
    { ftLk_Init_803C81E0, ftLk_Init_803C81EC, ftLk_Init_803C8204 },
};

int ftLk_Init_803C82EC[31] = { 0 };

Vec3 const ftLk_Init_803B7520[3] = { 0 };

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

void ftLk_Init_OnLoadForCLink(Fighter* fp)
{
    PUSH_ATTRS(fp, ftLinkAttributes);
}

void ftLk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLinkAttributes* link_attr = fp->ft_data->ext_attr;
    void** item_list = fp->ft_data->x48_items;
    link_attr->x54 = lbMthp_8001E8F8(ftData_80085E50(fp, 72));
    PUSH_ATTRS(fp, ftLinkAttributes);

    link_attr = fp->x2D4_specialAttributes;
    it_8026B3F8(item_list[0], link_attr->x48);
    it_8026B3F8(item_list[1], link_attr->x2C);
    it_8026B3F8(item_list[2], link_attr->xBC);
    it_8026B3F8(item_list[3], link_attr->xC);
    it_8026B3F8(item_list[4], link_attr->x10);
    ftParts_800753D4(fp, *Fighter_804D6540[fp->x4_fighterKind], item_list[6]);
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
    ft_80088148(fp, 160106, 127, 64);
}
