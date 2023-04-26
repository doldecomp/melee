#include "forward.h"
#include "ft/forward.h"

#include "ftSs_Init.h"

#include "ftSs_SpecialHi.h"
#include "ftSs_SpecialLw_0.h"
#include "ftSs_SpecialLw_1.h"
#include "ftSs_SpecialN.h"
#include "ftSs_SpecialS.h"
#include "types.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx/types.h>

MotionState ftSs_Init_MotionStateTable[ftSs_MS_SelfCount] = {
    {
        // ftSs_MS_SpecialLw = 341
        ftSs_SM_SpecialLw,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftSs_SpecialLw_Anim,
        ftSs_SpecialLw_IASA,
        ftSs_SpecialLw_Phys,
        ftSs_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialAirLw = 342
        ftSs_SM_SpecialAirLw,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftSs_SpecialAirLw_Anim,
        ftSs_SpecialAirLw_IASA,
        ftSs_SpecialAirLw_Phys,
        ftSs_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialNStart = 343
        ftSs_SM_SpecialNStart,
        ftSs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSs_SpecialNStart_Anim,
        ftSs_SpecialNStart_IASA,
        ftSs_SpecialNStart_Phys,
        ftSs_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialNHold = 344
        ftSs_SM_SpecialNHold,
        ftSs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSs_SpecialNLoop_Anim,
        ftSs_SpecialNLoop_IASA,
        ftSs_SpecialNLoop_Phys,
        ftSs_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialNCancel = 345
        ftSs_SM_SpecialNCancel,
        ftSs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSs_SpecialNEnd_Anim,
        ftSs_SpecialNEnd_IASA,
        ftSs_SpecialNEnd_Phys,
        ftSs_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialN = 346
        ftSs_SM_SpecialN,
        ftSs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSs_SpecialNShoot_Anim,
        ftSs_SpecialNShoot_IASA,
        ftSs_SpecialNShoot_Phys,
        ftSs_SpecialNShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialAirNStart = 347
        ftSs_SM_SpecialAirNStart,
        ftSs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftSs_SpecialAirNStart_Anim,
        ftSs_SpecialAirNStart_IASA,
        ftSs_SpecialAirNStart_Phys,
        ftSs_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialAirN = 348
        ftSs_SM_SpecialAirN,
        ftSs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftSs_SpecialAirNShoot_Anim,
        ftSs_SpecialAirNShoot_IASA,
        ftSs_SpecialAirNShoot_Phys,
        ftSs_SpecialAirNShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialS = 349
        ftSs_SM_SpecialS,
        ftSs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftSs_SpecialS_Anim,
        ftSs_SpecialS_IASA,
        ftSs_SpecialS_Phys,
        ftSs_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialSSmash = 350
        ftSs_SM_SpecialSSmash,
        ftSs_MF_SpecialSSmash,
        FtMoveId_SpecialS << 24,
        ftSs_SpecialSSmash_Anim,
        ftSs_SpecialSSmash_IASA,
        ftSs_SpecialSSmash_Phys,
        ftSs_SpecialSSmash_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialAirS = 351
        ftSs_SM_SpecialAirS,
        ftSs_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftSs_SpecialAirS_Anim,
        ftSs_SpecialAirS_IASA,
        ftSs_SpecialAirS_Phys,
        ftSs_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialAirSSmash = 352
        ftSs_SM_SpecialAirSSmash,
        ftSs_MF_SpecialAirSSmash,
        FtMoveId_SpecialS << 24,
        ftSs_SpecialAirSmash_Anim,
        ftSs_SpecialAirSmash_IASA,
        ftSs_SpecialAirSmash_Phys,
        ftSs_SpecialAirSSmash_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialHi = 353
        ftSs_SM_SpecialHi,
        ftSs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftSs_SpecialHi_Anim,
        ftSs_SpecialHi_IASA,
        ftSs_SpecialHi_Phys,
        ftSs_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialAirHi = 354
        ftSs_SM_SpecialAirHi,
        ftSs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftSs_SpecialAirHi_Anim,
        ftSs_SpecialAirHi_IASA,
        ftSs_SpecialAirHi_Phys,
        ftSs_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialLwBomb = 355
        ftSs_SM_SpecialLwBomb,
        ftSs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftSs_SpecialLwBombEnd_Anim,
        ftSs_SpecialLwBombEnd_IASA,
        ftSs_SpecialLwBombEnd_Phys,
        ftSs_SpecialLwBombEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialAirLwBomb = 356
        ftSs_SM_SpecialAirLwBomb,
        ftSs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftSs_SpecialAirLwBomb_Anim,
        ftSs_SpecialAirLwBomb_IASA,
        ftSs_SpecialAirLwBomb_Phys,
        ftSs_SpecialAirLwBomb_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_AirCatch = 357
        ftSs_SM_AirCatch,
        Ft_MF_FreezeState,
        FtMoveId_Default << 24,
        ftCo_Zair_Anim,
        ftCo_Zair_IASA,
        ftCo_Zair_Phys,
        ftCo_Zair_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_AirCatchHit = 358
        ftSs_SM_AirCatchHit,
        ftSs_MF_ZairCatch,
        FtMoveId_Default << 24,
        ftCo_ZairCatch_Anim,
        ftCo_ZairCatch_IASA,
        ftCo_ZairCatch_Phys,
        ftCo_ZairCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftSs_Init_DatFilename[] = "PlSs.dat";
char ftSs_Init_DataName[] = "ftDataSamus";
char ftSs_Init_803CE528[] = "PlSsNr.dat";
char ftSs_Init_803CE534[] = "PlySamus5K_Share_joint";
char ftSs_Init_803CE54C[] = "PlSsPi.dat";
char ftSs_Init_803CE558[] = "PlySamus5KPi_Share_joint";
char ftSs_Init_803CE574[] = "PlSsBk.dat";
char ftSs_Init_803CE580[] = "PlySamus5KBk_Share_joint";
char ftSs_Init_803CE59C[] = "PlSsGr.dat";
char ftSs_Init_803CE5A8[] = "PlySamus5KGr_Share_joint";
char ftSs_Init_803CE5C4[] = "PlSsLa.dat";
char ftSs_Init_803CE5D0[] = "PlySamus5KLa_Share_joint";
char ftSs_Init_AnimDatFilename[] = "PlSsAJ.dat";

Fighter_DemoStrings ftSs_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileSamus",
    "ftDemoIntroMotionFileSamus",
    "ftDemoEndingMotionFileSamus",
    "ftDemoViWaitMotionFileSamus",
};

Fighter_CostumeStrings ftSs_Init_CostumeStrings[] = {
    { ftSs_Init_803CE528, ftSs_Init_803CE534, NULL },
    { ftSs_Init_803CE54C, ftSs_Init_803CE558, NULL },
    { ftSs_Init_803CE574, ftSs_Init_803CE580, NULL },
    { ftSs_Init_803CE59C, ftSs_Init_803CE5A8, NULL },
    { ftSs_Init_803CE5C4, ftSs_Init_803CE5D0, NULL },
};

void ftSs_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.ss.x222C = 0;
    fp->fv.ss.x2230 = 0;
    fp->fv.ss.x2238 = 0;
    fp->fv.ss.x2244 = 0;
    fp->fv.ss.x223C = 0;
    fp->fv.ss.x2240 = 0;
}

void ftSs_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftSamusAttributes);

    it_8026B3F8(item_list[0], 93);
    it_8026B3F8(item_list[1], 94);
    it_8026B3F8(item_list[2], 95);
    it_8026B3F8(item_list[3], 96);
}

void ftSs_Init_80128428(HSD_GObj* gobj)
{
    ftSs_SpecialN_80129258(gobj);
    ftSs_SpecialS_8012A640(gobj);
    ft_800D9C98(gobj);
}

void ftSs_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 0);
}

void ftSs_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftSs_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftSs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftSs_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* attr = fp->x2D4_specialAttributes;
    s32 samus_x2230 = fp->fv.ss.x2230;
    if (samus_x2230 == attr->x18) {
        ft_800BFFD0(fp, 53, 0);
    }
}

void ftSs_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSamusAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x8 *= fp->x34_scale.y;
        sA2->x74_vec.y *= fp->x34_scale.y;
        sA2->x54 *= fp->x34_scale.y;
        sA2->x58 *= fp->x34_scale.y;
        SCALE_HEIGHT_ATTRS(6);
    }
}

void ftSs_Init_80128770(HSD_AObj* gobj, f32 rate)
{
    if (gobj && !(HSD_AObjGetFlags(gobj) & 0x20000000)) {
        HSD_AObjSetRate(gobj, rate);
    }
}

void ftSs_Init_CreateThrowGrappleBeam(HSD_GObj* gobj, s32 motion_state,
                                      f32 anim_speed)
{
    Fighter* fighter_copy;
    Vec3 scale;

    Fighter* fp = getFighter(gobj);
    void** item_list = fp->ft_data->x48_items;
    struct UNK_SAMUS_S1* beam = item_list[4];
    ftCommon_SetAccessory(fp, beam->x0_joint);

    scale.x = scale.y = scale.z = fp->x34_scale.y;
    HSD_JObjSetScale((fighter_copy = fp)->x20A0_accessory, &scale);

    HSD_JObjAddAnimAll(fighter_copy->x20A0_accessory, beam->x8_anim_joint,
                       beam->xC_matanim_joint, 0);
    HSD_JObjAddAnimAll(fighter_copy->x20A0_accessory,
                       beam->x4_anim_joints[motion_state - ftCo_MS_ThrowF], 0,
                       0);
    HSD_ForeachAnim(fighter_copy->x20A0_accessory, JOBJ_TYPE,
                    ALL_TYPE_MASK & ~TOBJ_MASK & ~MOBJ_MASK,
                    &ftSs_Init_80128770, AOBJ_ARG_AF, anim_speed);
    HSD_JObjReqAnimAll(fighter_copy->x20A0_accessory, 0.0f);
    HSD_JObjAnimAll(fighter_copy->x20A0_accessory);
    lb_8000C2F8(fighter_copy->x20A0_accessory,
                fighter_copy->parts[FtPart_ThrowN].x0_jobj);
}
