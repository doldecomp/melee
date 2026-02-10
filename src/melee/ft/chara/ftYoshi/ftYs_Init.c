#include "ftYs_Init.h"

#include "ftYs_Guard.h"
#include "ftYs_SpecialN.h"
#include "types.h"

#include <placeholder.h>

#include "ef/efasync.h"

#include "forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Guard.h"
#include "ftYoshi/ftYs_SpecialHi.h"
#include "ftYoshi/ftYs_SpecialS.h"

#include "it/forward.h"

#include "it/it_26B1.h"

#include <baselib/forward.h>

#include <dolphin/os/OSError.h>
#include <baselib/aobj.h>
#include <baselib/debug.h>
#include <baselib/mobj.h>

/// @@todo Belongs in #ftYs_Guard.c?
/* 3B75C0 */ Vec3 const ftYs_Unk1_803B75C0 = { 0 };

#undef __FILE__
#define __FILE__ "ftyoshi.c"

MotionState ftYs_Init_MotionStateTable[ftYs_MS_SelfCount] = {
    {
        // ftYs_MS_GuardOn_0 = 341
        ftCo_SM_GuardOn,
        ftYs_MF_MS_341,
        FtMoveId_Default << 24,
        ftYs_GuardOn_0_Anim,
        ftYs_GuardOn_0_IASA,
        ftYs_GuardOn_0_Phys,
        ftYs_GuardOn_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_GuardHold = 342
        ftCo_SM_None,
        ftYs_MF_ShieldHold,
        FtMoveId_Default << 24,
        ftYs_GuardHold_Anim,
        ftYs_GuardHold_IASA,
        ftYs_GuardHold_Phys,
        ftYs_GuardHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_GuardOff = 343
        ftCo_SM_GuardOff,
        ftYs_MF_MS_341,
        FtMoveId_Default << 24,
        ftYs_GuardOff_Anim,
        ftYs_GuardOff_IASA,
        ftYs_GuardOff_Phys,
        ftYs_GuardOff_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_GuardDamage = 344
        ftCo_SM_GuardDamage,
        ftYs_MF_MS_341,
        FtMoveId_Default << 24,
        ftYs_GuardDamage_Anim,
        ftYs_GuardDamage_IASA,
        ftYs_GuardDamage_Phys,
        ftYs_GuardDamage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_GuardOn_1 = 345
        ftCo_SM_GuardOn,
        ftYs_MF_ShieldStart,
        FtMoveId_Default << 24,
        ftYs_GuardOn_1_Anim,
        ftYs_GuardOn_1_IASA,
        ftYs_GuardOn_1_Phys,
        ftYs_GuardOn_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialN1 = 346
        ftYs_SM_SpecialN1,
        ftYs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialN1_Anim,
        NULL,
        ftYs_SpecialN1_Phys,
        ftYs_SpecialN1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialN1_0 = 347
        ftYs_SM_SpecialN1_0,
        ftYs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialN1_0_Anim,
        NULL,
        ftYs_SpecialN1_0_Phys,
        ftYs_SpecialN1_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialN1_1 = 348
        ftYs_SM_SpecialN1_0,
        ftYs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialN1_1_Anim,
        NULL,
        ftYs_SpecialN1_1_Phys,
        ftYs_SpecialN1_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialN2_0 = 349
        ftYs_SM_SpecialN2_1,
        ftYs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialN2_0_Anim,
        NULL,
        ftYs_SpecialN2_0_Phys,
        ftYs_SpecialN2_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialN2_1 = 350
        ftYs_SM_SpecialN2_1,
        ftYs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialN2_1_Anim,
        NULL,
        ftYs_SpecialN2_1_Phys,
        ftYs_SpecialN2_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirN1_0 = 351
        ftYs_SM_SpecialAirN1_0,
        ftYs_MF_SpecialS,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialAirN1_0_Anim,
        NULL,
        ftYs_SpecialAirN1_0_Phys,
        ftYs_SpecialAirN1_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirN1_1 = 352
        /// @@todo Fix names, this is SpecialN
        ftYs_SM_SpecialAirN1_1,
        ftYs_MF_SpecialS,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialAirN1_1_Anim,
        NULL,
        ftYs_SpecialAirN1_1_Phys,
        ftYs_SpecialAirN1_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirN1_2 = 353
        ftYs_SM_SpecialAirN1_1,
        ftYs_MF_SpecialS,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialAirN1_2_Anim,
        NULL,
        ftYs_SpecialAirN1_2_Phys,
        ftYs_SpecialAirN1_2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirN2_0 = 354
        ftYs_SM_SpecialAirN2,
        ftYs_MF_SpecialS,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialAirN2_0_Anim,
        NULL,
        ftYs_SpecialAirN2_0_Phys,
        ftYs_SpecialAirN2_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirN2_1 = 355
        ftYs_SM_SpecialAirN2,
        ftYs_MF_SpecialS,
        FtMoveId_SpecialN << 24,
        ftYs_SpecialAirN2_1_Anim,
        NULL,
        ftYs_SpecialAirN2_1_Phys,
        ftYs_SpecialAirN2_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirSStart_0 = 356
        ftYs_SM_SpecialSStart,
        ftYs_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftYs_SpecialAirSStart_0_Anim,
        ftYs_SpecialAirSStart_0_IASA,
        ftYs_SpecialAirSStart_0_Phys,
        ftYs_SpecialAirSStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirSLoop_0 = 357
        ftYs_SM_SpecialSLoop_0,
        ftYs_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftYs_SpecialAirSLoop_0_Anim,
        ftYs_SpecialAirSLoop_0_IASA,
        ftYs_SpecialAirSLoop_0_Phys,
        ftYs_SpecialAirSLoop_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirSLoop_1 = 358
        ftYs_SM_SpecialSLoop_1,
        ftYs_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftYs_SpecialAirSLoop_1_Anim,
        ftYs_SpecialAirSLoop_1_IASA,
        ftYs_SpecialAirSLoop_1_Phys,
        ftYs_SpecialAirSLoop_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirSEnd = 359
        ftYs_SM_SpecialSEnd,
        ftYs_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftYs_SpecialAirSEnd_Anim,
        ftYs_SpecialAirSEnd_IASA,
        ftYs_SpecialAirSEnd_Phys,
        ftYs_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirSStart_1 = 360
        /// @@todo Fix names, this is SpecialS
        ftYs_SM_SpecialAirSStart,
        ftYs_MF_SpecialHi,
        FtMoveId_SpecialS << 24,
        ftYs_SpecialAirSStart_1_Anim,
        ftYs_SpecialAirSStart_1_IASA,
        ftYs_SpecialAirSStart_1_Phys,
        ftYs_SpecialAirSStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirSLoop_2 = 361
        ftYs_SM_SpecialAirSLoop_0,
        ftYs_MF_SpecialHi,
        FtMoveId_SpecialS << 24,
        ftYs_SpecialAirSLoop_2_Anim,
        ftYs_SpecialAirSLoop_2_IASA,
        ftYs_SpecialAirSLoop_2_Phys,
        ftYs_SpecialAirSLoop_2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirSLoop_3 = 362
        ftYs_SM_SpecialAirSLoop_1,
        ftYs_MF_SpecialHi,
        FtMoveId_SpecialS << 24,
        ftYs_SpecialAirSLoop_3_Anim,
        ftYs_SpecialAirSLoop_3_IASA,
        ftYs_SpecialAirSLoop_3_Phys,
        ftYs_SpecialAirSLoop_3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirSLanding = 363
        ftYs_SM_SpecialAirSEnd,
        ftYs_MF_SpecialHi,
        FtMoveId_SpecialS << 24,
        ftYs_SpecialAirSLanding_Anim,
        ftYs_SpecialAirSLanding_IASA,
        ftYs_SpecialAirSLanding_Phys,
        ftYs_SpecialAirSLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialHi = 364
        ftYs_SM_SpecialHi,
        ftYs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftYs_SpecialHi_Anim,
        NULL,
        ftYs_SpecialHi_Phys,
        ftYs_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirHi = 365
        ftYs_SM_SpecialAirHi,
        ftYs_MF_MS_365,
        FtMoveId_SpecialHi << 24,
        ftYs_SpecialAirHi_Anim,
        NULL,
        ftYs_SpecialAirHi_Phys,
        ftYs_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialLw = 366
        ftYs_SM_SpecialLw,
        ftYs_MF_MS_366,
        FtMoveId_SpecialLw << 24,
        ftYs_SpecialLw_Anim,
        NULL,
        ftYs_SpecialLw_Phys,
        ftYs_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialLwLanding = 367
        ftYs_SM_SpecialLwLanding,
        ftYs_MF_MS_366,
        FtMoveId_SpecialLw << 24,
        ftYs_SpecialLwLanding_Anim,
        NULL,
        ftYs_SpecialLwLanding_Phys,
        ftYs_SpecialLwLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftYs_MS_SpecialAirLw = 368
        ftYs_SM_SpecialAirLw,
        ftYs_MF_MS_368,
        FtMoveId_SpecialLw << 24,
        ftYs_SpecialAirLw_Anim,
        NULL,
        ftYs_SpecialAirLw_Phys,
        ftYs_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
};

extern char* ftYs_Unk2_804D3E58;
extern char* ftYs_Unk2_804D3E60;
extern char* ftYs_Unk2_804D3E68;
extern char* ftYs_Unk2_804D3E70;
extern char* ftYs_Unk2_804D3E78;

/// https://decomp.me/scratch/ufrFK
void ftYs_Init_8012B6E8(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg)
{
    u8 _[12];

    struct S_UNK_YOSHI1* unk_struct1;
    s32* ptr2EndIndex;
    ftYoshiAttributes* attr_r26;
    u8* index;
    s32 i;
    float zero_float;

    attr_r26 = fp->ft_data->ext_attr;
    index = (unk_struct1 = unk_struct_arg)->unk_struct->xC_start_index;
    ptr2EndIndex = (s32*) (&unk_struct1->unk_struct->x8_end_index);
    zero_float = 0.0f;

    for (i = 0; i < *ptr2EndIndex; i++) {
        HSD_DObj* dobj_r3 = fp->dobj_list.data[index[i]];
        HSD_MObj* mobj_r3;
        HSD_AObj* aobj_r24;

        if (dobj_r3) {
            mobj_r3 = dobj_r3->mobj;
        } else {
            mobj_r3 = 0;
        }

        aobj_r24 = mobj_r3->aobj;
        HSD_AObjSetRate(aobj_r24, 0.0f);

        if (zero_float == attr_r26->xC) {
            attr_r26->xC = HSD_AObjGetEndFrame(aobj_r24);
        } else {
            if (attr_r26->xC != HSD_AObjGetEndFrame(aobj_r24)) {
                OSReport("yoshi matanim frame not same\n");
                __assert(__FILE__, 97, "0");
            }
        }
    }
}

void ftYs_Init_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg,
                        float start_frame)
{
    u8 _[8];

    if (unk_struct_arg) {
        struct S_UNK_YOSHI2* unk_struct = unk_struct_arg->unk_struct;
        s32* ptr2EndIndex;
        u8* index;
        s32 i;

        index = unk_struct->xC_start_index;
        ptr2EndIndex = (s32*) &unk_struct->x8_end_index;

        for (i = 0; i < *ptr2EndIndex; i++) {
            HSD_DObj* dobj_r3 = fp->dobj_list.data[index[i]];
            HSD_MObj* mobj_r3;
            HSD_MObj* mobj;

            if (dobj_r3) {
                mobj_r3 = dobj_r3->mobj;
            } else {
                mobj_r3 = 0;
            }

            mobj = mobj_r3;
            HSD_MObjReqAnim(mobj, start_frame);
            HSD_MObjAnim(mobj);
        }
    }
}

void ftYs_Init_8012B8A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* da = fp->dat_attrs;
    u8 _[8];
    float tempf =
        da->xC *
        (1.0f - (fp->shield_health / p_ftCommonData->x260_startShieldHealth));
    ftYs_Init_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5AC.xC[0], tempf);
    ftYs_Init_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5AC.xC[1], tempf);
}

void ftYs_Init_8012B918(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftYs_Init_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5AC.xC[0], 0.0F);
    ftYs_Init_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5AC.xC[1], 0.0F);
}

void ftYs_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.ys.x2238 = 0;
}

/// https://decomp.me/scratch/5TPxg
void ftYs_Init_OnLoad(HSD_GObj* gobj)
{
    void** item_list;
    ftYoshiAttributes* other_attr;
    struct S_UNK_YOSHI1* temp_r28;
    struct S_UNK_YOSHI1* temp;
    ftData* ft;
    struct S_UNK_YOSHI1* temp_r27;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    temp = temp_r27 = (struct S_UNK_YOSHI1*) fp->x5AC.xC[0];
    ft = fp->ft_data;
    temp_r28 = (struct S_UNK_YOSHI1*) fp->x5AC.xC[1];
    item_list = ft->x48_items;
    other_attr = ft->ext_attr;

    if (!temp) {
        OSReport("yoshi parts_model NULL!!\n");
        __assert(__FILE__, 113, "0");
    }

    other_attr->xC = 0.0f;
    ftYs_Init_8012B6E8(fp, temp_r27);
    ftYs_Init_8012B6E8(fp, temp_r28);
    PUSH_ATTRS(fp, ftYoshiAttributes);
    it_8026B3F8(item_list[0], It_Kind_Yoshi_EggThrow);
    it_8026B3F8(item_list[1], It_Kind_Yoshi_Star);
    it_8026B3F8(item_list[2], It_Kind_Yoshi_EggLay);
    fp->x2226_b1 = 1;
}

void ftYs_Init_8012BA8C(HSD_GObj* gobj)
{
    ftYs_SpecialS_8012E270(gobj);
    ftYs_SpecialS_8012DF18(gobj);
}

float ftYs_Init_8012BAC0(Fighter* fp)
{
    ftYoshiAttributes* da = fp->dat_attrs;
    return da->x120;
}

void ftYs_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftYs_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftYs_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftYs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftYs_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftYoshiAttributes);
}

void ftYs_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftYs_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}
