#include "ftPe_Init.h"

#include "ftPe_AttackS4.h"
#include "ftPe_Float.h"
#include "ftPe_FloatAttack.h"
#include "ftPe_FloatFall.h"
#include "ftPe_SpecialHi.h"
#include "ftPe_SpecialLw.h"
#include "ftPe_SpecialN.h"
#include "ftPe_SpecialS.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/ft_0CEE.h"
#include "ft/ftcamera.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"
#include "it/forward.h"

#include "it/it_26B1.h"
#include "lb/lbanim.h"

MotionState ftPe_Init_MotionStateTable[ftPe_MS_SelfCount] = {
    {
        // ftPe_MS_Float = 341
        ftPe_SM_Float,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftPe_Float_Anim,
        ftPe_Float_IASA,
        ftPe_Float_Phys,
        ftPe_Float_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_FloatFallF = 342
        ftPe_SM_FloatFallF,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftPe_FloatFall_Anim,
        ftPe_FloatFall_IASA,
        ftPe_FloatFall_Phys,
        ftPe_FloatFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_FloatFallB = 343
        ftPe_SM_FloatFallB,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftPe_FloatFall_Anim,
        ftPe_FloatFall_IASA,
        ftPe_FloatFall_Phys,
        ftPe_FloatFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_FloatAttackAirN = 344
        ftCo_SM_AttackAirN,
        ftPe_MF_FloatAttackAirN,
        FtMoveId_AttackAirN << 24,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_FloatAttackAirF = 345
        ftCo_SM_AttackAirF,
        ftPe_MF_Move_14,
        FtMoveId_AttackAirF << 24,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_FloatAttackAirB = 346
        ftCo_SM_AttackAirB,
        ftPe_MF_FloatAttackAirB,
        FtMoveId_AttackAirB << 24,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_FloatAttackAirHi = 347
        ftCo_SM_AttackAirHi,
        ftPe_MF_FloatAttackAirHi,
        FtMoveId_AttackAirHi << 24,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_FloatAttackAirLw = 348
        ftCo_SM_AttackAirLw,
        ftPe_MF_Move_17,
        FtMoveId_AttackAirLw << 24,
        ftPe_FloatAttackAir_Anim,
        ftPe_FloatAttackAir_IASA,
        ftPe_FloatAttackAir_Phys,
        ftPe_FloatAttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_AttackS4Club = 349
        ftPe_SM_AttackS4_0,
        ftPe_MF_AttackS4,
        FtMoveId_AttackS4 << 24,
        ftPe_AttackS4_Anim,
        ftPe_AttackS4_IASA,
        ftPe_AttackS4_Phys,
        ftPe_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_AttackS4Pan = 350
        ftPe_SM_AttackS4_1,
        ftPe_MF_AttackS4,
        FtMoveId_AttackS4 << 24,
        ftPe_AttackS4_Anim,
        ftPe_AttackS4_IASA,
        ftPe_AttackS4_Phys,
        ftPe_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_AttackS4Racket = 351
        ftPe_SM_AttackS4_2,
        ftPe_MF_AttackS4,
        FtMoveId_AttackS4 << 24,
        ftPe_AttackS4_Anim,
        ftPe_AttackS4_IASA,
        ftPe_AttackS4_Phys,
        ftPe_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialLw = 352
        ftPe_SM_SpecialLw,
        ftPe_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftPe_SpecialLw_Anim,
        NULL,
        ftPe_SpecialLw_Phys,
        ftPe_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirLw = 353
        ftPe_SM_SpecialLw,
        ftPe_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftPe_SpecialAirLw_Anim,
        NULL,
        ftPe_SpecialAirLw_Phys,
        ftPe_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialSStart = 354
        ftPe_SM_SpecialSStart,
        ftPe_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftPe_SpecialSStart_Anim,
        ftPe_SpecialSStart_IASA,
        ftPe_SpecialSStart_Phys,
        ftPe_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialSEnd = 355
        ftPe_SM_SpecialSEnd,
        ftPe_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftPe_SpecialSEnd_Anim,
        ftPe_SpecialSEnd_IASA,
        ftPe_SpecialSEnd_Phys,
        ftPe_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialSJump = 356
        ftPe_SM_SpecialSJump,
        ftPe_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirSStart = 357
        ftPe_SM_SpecialAirSStart,
        ftPe_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPe_SpecialAirSStart_Anim,
        ftPe_SpecialAirSStart_IASA,
        ftPe_SpecialAirSStart_Phys,
        ftPe_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirSEnd_0 = 358
        ftPe_SM_SpecialAirSEnd_0,
        ftPe_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPe_SpecialAirSEnd_Anim,
        ftPe_SpecialAirSEnd_IASA,
        ftPe_SpecialAirSEnd_Phys,
        ftPe_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirSEnd_1 = 359
        ftPe_SM_SpecialAirSEnd_1,
        ftPe_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPe_SpecialAirSEnd_Anim,
        ftPe_SpecialAirSEnd_IASA,
        ftPe_SpecialAirSEnd_Phys,
        ftPe_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirSJump = 360
        ftPe_SM_SpecialSJump,
        ftPe_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftPe_SpecialAirSJump_Anim,
        ftPe_SpecialAirSJump_IASA,
        ftPe_SpecialAirSJump_Phys,
        ftPe_SpecialAirSJump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialHiStart = 361
        ftPe_SM_SpecialHiStart,
        ftPe_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPe_SpecialHiStart_Anim,
        ftPe_SpecialHiStart_IASA,
        ftPe_SpecialHiStart_Phys,
        ftPe_SpecialHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialHiEnd = 362
        ftPe_SM_SpecialHiEnd,
        ftPe_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPe_SpecialHiEnd_Anim,
        ftPe_SpecialHiEnd_IASA,
        ftPe_SpecialHiEnd_Phys,
        ftPe_SpecialHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirHiStart = 363
        ftPe_SM_SpecialAirHiStart,
        ftPe_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPe_SpecialAirHiStart_Anim,
        ftPe_SpecialAirHiStart_IASA,
        ftPe_SpecialAirHiStart_Phys,
        ftPe_SpecialAirHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirHiEnd = 364
        ftPe_SM_SpecialAirHiEnd,
        ftPe_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPe_SpecialAirHiEnd_Anim,
        ftPe_SpecialAirHiEnd_IASA,
        ftPe_SpecialAirHiEnd_Phys,
        ftPe_SpecialAirHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialN = 365
        ftPe_SM_SpecialN,
        ftPe_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPe_SpecialN_Anim,
        ftPe_SpecialN_IASA,
        ftPe_SpecialN_Phys,
        ftPe_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialNHit = 366
        ftPe_SM_SpecialNHit,
        ftPe_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftPe_SpecialNHit_Anim,
        ftPe_SpecialNHit_IASA,
        ftPe_SpecialNHit_Phys,
        ftPe_SpecialNHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirN = 367
        ftPe_SM_SpecialAirN,
        ftPe_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPe_SpecialAirN_Anim,
        ftPe_SpecialAirN_IASA,
        ftPe_SpecialAirN_Phys,
        ftPe_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_SpecialAirNHit = 368
        ftPe_SM_SpecialAirNHit,
        ftPe_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftPe_SpecialAirNHit_Anim,
        ftPe_SpecialAirNHit_IASA,
        ftPe_SpecialAirNHit_Phys,
        ftPe_SpecialAirNHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_ItemParasolOpen = 369
        ftPe_SM_ItemParasolOpen,
        ftPe_MF_ParasolOpen,
        (FtMoveId_Parasol << 24) | (1 << 23),
        ftCo_ItemParasolOpen_Anim,
        ftCo_ItemParasolOpen_IASA,
        ftCo_ItemParasolOpen_Phys,
        ftCo_ItemParasolOpen_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPe_MS_ItemParasolFall = 370
        ftPe_SM_ItemParasolFall,
        ftPe_MF_ParasolFallSpecial,
        (FtMoveId_Parasol << 24) | (1 << 23),
        ftCo_ItemParasolFallSpecial_Anim,
        ftCo_ItemParasolFallSpecial_IASA,
        ftCo_ItemParasolFallSpecial_Phys,
        ftCo_ItemParasolFallSpecial_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftPe_Init_DatFilename[] = "PlPe.dat";
char ftPe_Init_DataName[] = "ftDataPeach";
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
char ftPe_Init_AnimDatFilename[] = "PlPeAJ.dat";

Fighter_DemoStrings ftPe_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFilePeach",
    "ftDemoIntroMotionFilePeach",
    "ftDemoEndingMotionFilePeach",
    "ftDemoViWaitMotionFilePeach",
};

Fighter_CostumeStrings ftPe_Init_CostumeStrings[] = {
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

void ftPe_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.pe.has_float = true;
    fp->fv.pe.attacks4_motion_id = ftCo_MS_None;
    fp->fv.pe.specialairn_used = false;
    fp->fv.pe.parasol_gobj = NULL;
    fp->fv.pe.unk_item_gobj = NULL;
    fp->fv.pe.toad_gobj = NULL;
    fp->fv.pe.veg_gobj = NULL;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 2, 0);
    ftParts_80074A4C(gobj, 3, -1);
    ftParts_80074A4C(gobj, 4, 0);

    switch (fp->x619_costume_id) {
    case 1: {
        ftParts_80074A4C(gobj, 1, -1);
        ftParts_80074A4C(gobj, 5, 0);
        ftParts_80074A4C(gobj, 6, -1);
        break;
    }
    default: {
        ftParts_80074A4C(gobj, 1, 0);
        ftParts_80074A4C(gobj, 5, -1);
        ftParts_80074A4C(gobj, 6, 0);
        break;
    }
    }
}

void ftPe_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* extAtrrs = fp->ft_data->ext_attr;
    UNK_T* items = fp->ft_data->x48_items;
    extAtrrs->floatfallf_anim_start = lbAnim_8001E8F8(ftData_80085E50(fp, 18));
    extAtrrs->floatfallb_anim_start = lbAnim_8001E8F8(ftData_80085E50(fp, 19));
    PUSH_ATTRS(fp, ftPe_DatAttrs);
    it_8026B3F8(items[0], It_Kind_Peach_Explode);
    it_8026B3F8(items[1], It_Kind_Peach_Turnip);
    it_8026B3F8(items[2], It_Kind_Peach_Parasol);
    it_8026B3F8(items[3], It_Kind_Peach_Toad);
    it_8026B3F8(items[4], It_Kind_Peach_ToadSpore);
}

void ftPe_Init_OnDeath2(HSD_GObj* gobj)
{
    ftPe_8011D598(gobj);
    ftPe_SpecialN_OnDeath2(gobj);
    ftPe_SpecialLw_8011CFA0(gobj);
}

void ftPe_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftPe_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftPe_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftPe_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 1, 1);
}

void ftPe_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftPe_DatAttrs);
}

void ftPe_Init_8011B93C(HSD_GObj* gobj)
{
    u8 _[8];

    s32 result = ftParts_80074A74(gobj, 2);

    if (result == -1) {
        ftParts_80074A4C(gobj, 2, 0);
    } else {
        ftParts_80074A4C(gobj, 2, -1);
    }
}

void ftPe_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftPe_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
