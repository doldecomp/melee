#include "forward.h"
#include "ftCommon/forward.h"

#include "ftSs_Init.h"

#include "ftSs_SpecialHi.h"
#include "ftSs_SpecialLw_0.h"
#include "ftSs_SpecialLw_1.h"
#include "ftSs_SpecialN.h"
#include "ftSs_SpecialS.h"
#include "types.h"

#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftcamera.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_AirCatch.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/aobj.h>
#include <baselib/jobj.h>
#include <baselib/object.h>

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
        ftSs_SpecialNHold_Anim,
        ftSs_SpecialNHold_IASA,
        ftSs_SpecialNHold_Phys,
        ftSs_SpecialNHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialNCancel = 345
        ftSs_SM_SpecialNCancel,
        ftSs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSs_SpecialNCancel_Anim,
        ftSs_SpecialNCancel_IASA,
        ftSs_SpecialNCancel_Phys,
        ftSs_SpecialNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_SpecialN = 346
        ftSs_SM_SpecialN,
        ftSs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSs_SpecialN_Anim,
        ftSs_SpecialN_IASA,
        ftSs_SpecialN_Phys,
        ftSs_SpecialN_Coll,
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
        ftSs_SpecialAirN_Anim,
        ftSs_SpecialAirN_IASA,
        ftSs_SpecialAirN_Phys,
        ftSs_SpecialAirN_Coll,
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
        ftSs_SpecialAirSSmash_Anim,
        ftSs_SpecialAirSSmash_IASA,
        ftSs_SpecialAirSSmash_Phys,
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
        ftSs_SpecialLwBomb_Anim,
        ftSs_SpecialLwBomb_IASA,
        ftSs_SpecialLwBomb_Phys,
        ftSs_SpecialLwBomb_Coll,
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
        ftCo_AirCatch_Anim,
        ftCo_AirCatch_IASA,
        ftCo_AirCatch_Phys,
        ftCo_AirCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSs_MS_AirCatchHit = 358
        ftSs_SM_AirCatchHit,
        ftSs_MF_ZairCatch,
        FtMoveId_Default << 24,
        ftCo_AirCatchHit_Anim,
        ftCo_AirCatchHit_IASA,
        ftCo_AirCatchHit_Phys,
        ftCo_AirCatchHit_Coll,
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

    fp->x2224_b7 = 1;

    PUSH_ATTRS(fp, ftSs_DatAttrs);

    it_8026B3F8(item_list[0], 93);
    it_8026B3F8(item_list[1], 94);
    it_8026B3F8(item_list[2], 95);
    it_8026B3F8(item_list[3], 96);
}

void ftSs_Init_80128428(HSD_GObj* gobj)
{
    ftSs_SpecialN_80129258(gobj);
    ftSs_SpecialS_8012A640(gobj);
    ftCo_800D9C98(gobj);
}

void ftSs_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 0, 0);
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
    ftSs_DatAttrs* da = fp->dat_attrs;
    s32 samus_x2230 = fp->fv.ss.x2230;
    if (samus_x2230 == da->x18) {
        ftCo_800BFFD0(fp, 53, 0);
    }
}

void ftSs_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSs_DatAttrs);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x8 *= fp->x34_scale.y;
        sA2->x74_vec.y *= fp->x34_scale.y;
        sA2->x54 *= fp->x34_scale.y;
        sA2->x58 *= fp->x34_scale.y;
        {
            /// @todo Shared code wit #ftPk_Init_LoadSpecialAttrs
            int i;
            for (i = 0;
                 i < (signed) (sizeof(sA2->height_attributes) / sizeof(float));
                 i++)
            {
                ((float*) &sA2->height_attributes)[i] *= fp->x34_scale.y;
            }
        }
    }
}

void ftSs_Init_80128770(HSD_AObj* gobj, float rate)
{
    if (gobj && !(HSD_AObjGetFlags(gobj) & 0x20000000)) {
        HSD_AObjSetRate(gobj, rate);
    }
}

void ftSs_Init_CreateThrowGrappleBeam(HSD_GObj* gobj, s32 motion_state,
                                      float anim_speed)
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
                fighter_copy->parts[FtPart_ThrowN].joint);
}
