#include "ftLk_Init.h"

#include "ftLk_SpecialHi.h"
#include "ftLk_SpecialLw.h"
#include "ftLk_SpecialN.h"
#include "ftLk_SpecialS.h"
#include "types.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0D14.h"
#include "ft/ftattacks4combo.h"
#include "ft/ftcamera.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCLink/ftCl_Init.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_Guard.h"
#include "it/it_26B1.h"
#include "lb/lbanim.h"

#include <dolphin/mtx.h>

MotionState ftLk_Init_MotionStateTable[ftLk_MS_SelfCount] = {
    {
        // ftLk_MS_AttackS42 = 341
        ftLk_SM_AttackS42,
        ftLk_MF_AttackS42,
        FtMoveId_AttackS4 << 24,
        ftCo_AttackS42_Anim,
        ftCo_AttackS42_IASA,
        ftCo_AttackS42_Phys,
        ftCo_AttackS42_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_AppealSR = 342
        ftCo_SM_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // ftLk_MS_AppealSL = 343
        ftCo_SM_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // ftLk_MS_SpecialNStart = 344
        ftLk_SM_SpecialNStart,
        ftLk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialNStart_Anim,
        ftLk_SpecialNStart_IASA,
        ftLk_SpecialNStart_Phys,
        ftLk_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialNLoop = 345
        ftLk_SM_SpecialNLoop,
        ftLk_MF_SpecialNFullyCharged,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialNLoop_Anim,
        ftLk_SpecialNLoop_IASA,
        ftLk_SpecialNLoop_Phys,
        ftLk_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialNEnd = 346
        ftLk_SM_SpecialNEnd,
        ftLk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialNEnd_Anim,
        ftLk_SpecialNEnd_IASA,
        ftLk_SpecialNEnd_Phys,
        ftLk_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialAirNStart = 347
        ftLk_SM_SpecialAirNStart,
        ftLk_MF_SpecialAirNCharge,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialAirNStart_Anim,
        ftLk_SpecialAirNStart_IASA,
        ftLk_SpecialAirNStart_Phys,
        ftLk_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialAirNLoop = 348
        ftLk_SM_SpecialAirNLoop,
        ftLk_MF_SpecialAirNFullyCharged,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialAirNLoop_Anim,
        ftLk_SpecialAirNLoop_IASA,
        ftLk_SpecialAirNLoop_Phys,
        ftLk_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialAirNEnd = 349
        ftLk_SM_SpecialAirNEnd,
        ftLk_MF_SpecialAirNFire,
        FtMoveId_SpecialN << 24,
        ftLk_SpecialAirNEnd_Anim,
        ftLk_SpecialAirNEnd_IASA,
        ftLk_SpecialAirNEnd_Phys,
        ftLk_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialS1 = 350
        ftLk_SM_SpecialS1,
        ftLk_MF_SpecialSThrow,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialS1_Anim,
        NULL,
        ftLk_SpecialS1_Phys,
        ftLk_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialS2 = 351
        ftLk_SM_SpecialS2,
        ftLk_MF_SpecialSCatch,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialS2_Anim,
        ftLk_SpecialS2_IASA,
        ftLk_SpecialS2_Phys,
        ftLk_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialS1Empty = 352
        ftLk_SM_SpecialS1Empty,
        ftLk_MF_SpecialSCatch,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialS1Empty_Anim,
        NULL,
        ftLk_SpecialS1Empty_Phys,
        ftLk_SpecialS1Empty_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialAirS1 = 353
        ftLk_SM_SpecialAirS1,
        ftLk_MF_SpecialAirSThrow,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialAirS1_Anim,
        NULL,
        ftLk_SpecialAirS1_Phys,
        ftLk_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialAirS2 = 354
        ftLk_SM_SpecialAirS2,
        ftLk_MF_SpecialAirSThrow,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialAirS2_Anim,
        ftLk_SpecialAirS2_IASA,
        ftLk_SpecialAirS2_Phys,
        ftLk_SpecialAirS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialAirS1Empty = 355
        ftLk_SM_SpecialAirS1Empty,
        ftLk_MF_SpecialAirSThrowEmpty,
        FtMoveId_SpecialS << 24,
        ftLk_SpecialAirS1Empty_Anim,
        NULL,
        ftLk_SpecialAirS1Empty_Phys,
        ftLk_SpecialAirS1Empty_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialHi = 356
        ftLk_SM_SpecialHi,
        ftLk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftLk_SpecialHi_Anim,
        ftLk_SpecialHi_IASA,
        ftLk_SpecialHi_Phys,
        ftLk_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialAirHi = 357
        ftLk_SM_SpecialAirHi,
        ftLk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftLk_SpecialAirHi_Anim,
        ftLk_SpecialAirHi_IASA,
        ftLk_SpecialAirHi_Phys,
        ftLk_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialLw = 358
        ftLk_SM_SpecialLw,
        ftLk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftLk_SpecialLw_Anim,
        NULL,
        ftLk_SpecialLw_Phys,
        ftLk_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_SpecialAirLw = 359
        ftLk_SM_SpecialAirLw,
        ftLk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftLk_SpecialAirLw_Anim,
        NULL,
        ftLk_SpecialAirLw_Phys,
        ftLk_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_AirCatch = 360
        ftLk_SM_AirCatch,
        Ft_MF_FreezeState,
        FtMoveId_Default << 24,
        ftCo_AirCatch_Anim,
        ftCo_AirCatch_IASA,
        ftCo_AirCatch_Phys,
        ftCo_AirCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_AirCatchHit = 361
        ftLk_SM_AirCatchHit,
        ftLk_MF_ZairCatch,
        FtMoveId_Default << 24,
        ftCo_AirCatchHit_Anim,
        ftCo_AirCatchHit_IASA,
        ftCo_AirCatchHit_Phys,
        ftCo_AirCatchHit_Coll,
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

ftLk_SpecialN_Vec3Group const ftLk_Init_Vec3Group = { 0 };

bool ftLk_Init_BoomerangExists(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.lk.boomerang_gobj != NULL) {
        return true;
    } else {
        return false;
    }
}

void ftLk_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    ftParts_80074A4C(gobj, 2, 0);

    fp->fv.lk.used_boomerang = false;
    fp->fv.lk.boomerang_gobj = NULL;
    fp->fv.lk.xC = 0;
    fp->fv.lk.arrow_gobj = NULL;
    fp->fv.lk.x14 = 0;
    fp->fv.lk.xC = 0;
    fp->fv.lk.x18 = 0;
}

void ftLk_Init_OnLoadForCLink(Fighter* fp)
{
    PUSH_ATTRS(fp, ftLk_DatAttrs);
}

void ftLk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->ft_data->ext_attr;
    void** item_list = fp->ft_data->x48_items;
    da->attackairlw_hit_anim_frame_end =
        lbAnim_8001E8F8(ftData_80085E50(fp, 72));
    PUSH_ATTRS(fp, ftLk_DatAttrs);
    da = fp->dat_attrs;
    it_8026B3F8(item_list[0], da->x48);
    it_8026B3F8(item_list[1], da->x2C);
    it_8026B3F8(item_list[2], da->xBC);
    it_8026B3F8(item_list[3], da->xC);
    it_8026B3F8(item_list[4], da->x10);
    ftParts_800753D4(fp, *Fighter_804D6540[fp->kind], item_list[6]);
}

void ftLk_800EAF38(HSD_GObj* gobj)
{
    ftLk_SpecialS_RemoveBoomerang1(gobj);
}

void ftLk_800EAF58(HSD_GObj* gobj)
{
    ftLk_SpecialS_RemoveBoomerang1(gobj);
    ftCo_800D94D8(gobj);
    ftLk_SpecialN_ProcessFv10(gobj);
    ftLk_SpecialN_ProcessFv14(gobj);
    ftCl_Init_80149268(gobj);
}

void ftLk_Init_OnItemPickupExt(HSD_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (it_8026B2B4(fp->item_gobj) == 1) {
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
    if (it_8026B2B4(fp->item_gobj) == 1) {
        ftParts_80074A4C(gobj, 1, 0);
    }
    ftParts_80074A4C(gobj, 2, 0);
    ftLk_Init_OnItemDrop(gobj, arg1);
}

void ftLk_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftLk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    u8 _[8];

    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftLk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftLk_DatAttrs);
    if (fp->x34_scale.y != 1.0f) {
        sA2->specialhi_pos_y_offset *= fp->x34_scale.y;
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
    float new_ground_vel;

    Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* link_attr = fp->ft_data->ext_attr;

    float resultf = ftCo_80092ED8(fp->x19A4, link_attr->xD8);
    fp->gr_vel = resultf * p_ftCommonData->x294;
    if (fp->specialn_facing_dir < 0) {
        new_ground_vel = fp->gr_vel;
    } else {
        new_ground_vel = -fp->gr_vel;
    }
    fp->gr_vel = new_ground_vel;
    ft_PlaySFX(fp, 160106, 127, 64);
}
