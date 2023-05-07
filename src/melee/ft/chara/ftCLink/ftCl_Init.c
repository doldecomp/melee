#include "forward.h"
#include "ftLink/forward.h"
#include "it/forward.h"

#include "ftCl_Init.h"

#include "ftCl_AppealS.h"
#include "inlines.h"
#include "types.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftLink/ftLk_Init.h"
#include "ftLink/ftLk_SpecialHi.h"
#include "ftLink/ftLk_SpecialLw.h"
#include "ftLink/ftLk_SpecialN.h"
#include "ftLink/ftLk_SpecialS.h"
#include "lb/lbmthp.h"

MotionState ftCl_Init_MotionStateTable[ftLk_MS_SelfCount] = {
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
        ftCo_SM_AppealSR,
        ftCl_MF_Zair,
        FtMoveId_Default << 24,
        ftCl_AppealS_Anim,
        ftCl_AppealS_IASA,
        ftCl_AppealS_Phys,
        ftCl_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftLk_MS_AppealSL = 343
        ftCo_SM_AppealSL,
        ftCl_MF_Zair,
        FtMoveId_Default << 24,
        ftCl_AppealS_Anim,
        ftCl_AppealS_IASA,
        ftCl_AppealS_Phys,
        ftCl_AppealS_Coll,
        ftCamera_UpdateCameraBox,
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
        ftLk_MF_SpecialSThrow,
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
        ftLk_MF_SpecialAirSThrow,
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
    attrs->x54 = lbMthp_8001E8F8(ftData_80085E50(fp, 72));
    ftLk_Init_OnLoadForCLink(fp);
    attrs = fp->dat_attrs;
    it_8026B3F8(items[0], attrs->x48);
    it_8026B3F8(items[1], attrs->x2C);
    it_8026B3F8(items[2], attrs->xBC);
    it_8026B3F8(items[3], attrs->xC);
    it_8026B3F8(items[4], attrs->x10);
    it_8026B3F8(items[5], It_Kind_CLink_Milk);
    ftParts_800753D4(fp, *Fighter_804D6540[fp->kind], items[6]);
}

void ftCl_Init_OnItemPickupExt(HSD_GObj* gobj, bool arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = gobj->user_data;

    if (it_8026B2B4(fp->item_gobj) == true) {
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

    if (it_8026B2B4(fp->item_gobj) == true) {
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
    if (fp->specialn_facing_dir < 0.0f) {
        ftmp = fp->gr_vel;
    } else {
        ftmp = -fp->gr_vel;
    }
    fp->gr_vel = ftmp;
    ft_80088148(fp, 70106, 127, 64);
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
        attrs = (void*) fp->dat_attrs;
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
    if (temp_r0 != 342 && temp_r0 != 343) {
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
            return fp->cmd_vars[1];
        }
    }
    return 0;
}

void ftCl_Init_80149318(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ft_800DEAE8(gobj, 342, 343);
    fp->cmd_vars[1] = 0;
}
