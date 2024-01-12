#include "forward.h"
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "it/forward.h"

#include "ftYs_Init.h"

#include "ftYs_Guard.h"
#include "ftYs_SpecialN.h"
#include "types.h"

#include "ef/efasync.h"
#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Guard.h"

#include <placeholder.h>
#include <dolphin/os.h>

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
        /// @todo Fix names, this is SpecialN
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
        /// @todo Fix names, this is SpecialS
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
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    struct S_UNK_YOSHI1* unk_struct1;
    s32* ptr2EndIndex;
    ftYoshiAttributes* attr_r26;
    u8* index;
    s32 i;
    f32 zero_float;

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
                __assert("ftyoshi.c", 97, "0");
            }
        }
    }
}

void ftYs_Init_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg,
                        f32 start_frame)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

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
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    f32 tempf =
        da->xC *
        (1.0f - (fp->shield_health / p_ftCommonData->x260_startShieldHealth));
    ftYs_Init_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5B8, tempf);
    ftYs_Init_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5BC, tempf);
}

void ftYs_Init_8012B918(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftYs_Init_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5B8, 0.0f);
    ftYs_Init_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5BC, 0.0f);
}

void ftYs_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.ys.x2238 = 0;
}

// https://decomp.me/scratch/5TPxg
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
    temp = temp_r27 = (struct S_UNK_YOSHI1*) fp->x5B8;
    ft = fp->ft_data;
    temp_r28 = (struct S_UNK_YOSHI1*) fp->x5BC;
    item_list = ft->x48_items;
    other_attr = ft->ext_attr;

    if (!temp) {
        OSReport("yoshi parts_model NULL!!\n");
        __assert("ftyoshi.c", 113, "0");
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

/* static */ void ftYs_SpecialS_8012E270(HSD_GObj* gobj);
/* static */ void ftYs_SpecialS_8012DF18(HSD_GObj* gobj);

void ftYs_Init_8012BA8C(HSD_GObj* gobj)
{
    ftYs_SpecialS_8012E270(gobj);
    ftYs_SpecialS_8012DF18(gobj);
}

f32 ftYs_Init_8012BAC0(Fighter* fp)
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

/* static */ extern f32 const ftYs_Init_804D9A28;
/* static */ extern u8 ftYs_Unk1_803B75C0[];

#ifdef MWERKS_GEKKO

#pragma push
asm /* 12BDA0 */ void ftYs_Init_8012BDA0(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8012BDA0 00128980  7C 08 02 A6 */	mflr r0
/* 8012BDA4 00128984  38 80 00 02 */	li r4, 2
/* 8012BDA8 00128988  90 01 00 04 */	stw r0, 4(r1)
/* 8012BDAC 0012898C  94 21 FF A8 */	stwu r1, -88(r1)
/* 8012BDB0 00128990  93 E1 00 54 */	stw r31, 84(r1)
/* 8012BDB4 00128994  83 E3 00 2C */	lwz r31, 44(r3)
/* 8012BDB8 00128998  4B F4 F3 09 */	bl ftColl_8007B0C0
/* 8012BDBC 0012899C  80 9F 01 0C */	lwz r4, 268(r31)
/* 8012BDC0 001289A0  3C 60 80 3B */	lis r3, ftYs_Unk1_803B75C0@ha
/* 8012BDC4 001289A4  38 00 00 01 */	li r0, 1
/* 8012BDC8 001289A8  C0 02 A0 48 */	lfs f0, ftYs_Init_804D9A28
/* 8012BDCC 001289AC  80 84 00 08 */	lwz r4, 8(r4)
/* 8012BDD0 001289B0  38 E3 75 C0 */	addi r7, r3, ftYs_Unk1_803B75C0@l
/* 8012BDD4 001289B4  88 A4 00 11 */	lbz r5, 17(r4)
/* 8012BDD8 001289B8  38 7F 00 00 */	addi r3, r31, 0
/* 8012BDDC 001289BC  38 9F 11 A0 */	addi r4, r31, 4512
/* 8012BDE0 001289C0  90 A1 00 20 */	stw r5, 32(r1)
/* 8012BDE4 001289C4  38 A1 00 20 */	addi r5, r1, 32
/* 8012BDE8 001289C8  90 01 00 24 */	stw r0, 36(r1)
/* 8012BDEC 001289CC  90 01 00 28 */	stw r0, 40(r1)
/* 8012BDF0 001289D0  80 C7 00 00 */	lwz r6, 0(r7)
/* 8012BDF4 001289D4  80 07 00 04 */	lwz r0, 4(r7)
/* 8012BDF8 001289D8  90 C1 00 38 */	stw r6, 56(r1)
/* 8012BDFC 001289DC  90 01 00 3C */	stw r0, 60(r1)
/* 8012BE00 001289E0  80 07 00 08 */	lwz r0, 8(r7)
/* 8012BE04 001289E4  90 01 00 40 */	stw r0, 64(r1)
/* 8012BE08 001289E8  80 C1 00 38 */	lwz r6, 56(r1)
/* 8012BE0C 001289EC  80 01 00 3C */	lwz r0, 60(r1)
/* 8012BE10 001289F0  90 C1 00 2C */	stw r6, 44(r1)
/* 8012BE14 001289F4  90 01 00 30 */	stw r0, 48(r1)
/* 8012BE18 001289F8  80 01 00 40 */	lwz r0, 64(r1)
/* 8012BE1C 001289FC  90 01 00 34 */	stw r0, 52(r1)
/* 8012BE20 00128A00  D0 01 00 44 */	stfs f0, 68(r1)
/* 8012BE24 00128A04  4B F4 F7 89 */	bl ftColl_8007B5AC
/* 8012BE28 00128A08  80 01 00 5C */	lwz r0, 92(r1)
/* 8012BE2C 00128A0C  83 E1 00 54 */	lwz r31, 84(r1)
/* 8012BE30 00128A10  38 21 00 58 */	addi r1, r1, 88
/* 8012BE34 00128A14  7C 08 03 A6 */	mtlr r0
/* 8012BE38 00128A18  4E 80 00 20 */	blr
}
#pragma pop

#endif

void ftYs_Init_8012BE3C(HSD_GObj* gobj) {
    ftCo_DatAttrs_xBC_t* co_xBC;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_Part part;
    Fighter* fp2;
    HSD_JObj* jobj;
    ftParts_80074B0C(gobj, 0, 0);
    ftColl_8007B0C0(gobj, 0);

    co_xBC = &fp->co_attrs.xBC;
    part = ftParts_8007500C(fp, FtPart_HipN);
    fp2 = GET_FIGHTER(gobj);
    jobj = fp->parts[part].joint;
    efAsync_Spawn(gobj, &fp2->x60C, FtPart_HipN, 1231, jobj, co_xBC);
}

#ifdef MWERKS_GEKKO

/* static */ extern f32 const ftYs_Init_804D9A2C;
/* static */ extern f32 const ftYs_Init_804D9A28;

#pragma push
asm void ftYs_Init_8012BECC(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
ftYs_Init_8012BECC:
/* 8012BECC 00128AAC  7C 08 02 A6 */	mflr r0
/* 8012BED0 00128AB0  38 80 01 55 */	li r4, 341
/* 8012BED4 00128AB4  90 01 00 04 */	stw r0, 4(r1)
/* 8012BED8 00128AB8  38 A0 00 00 */	li r5, 0
/* 8012BEDC 00128ABC  38 C0 00 00 */	li r6, 0
/* 8012BEE0 00128AC0  94 21 FF C8 */	stwu r1, -56(r1)
/* 8012BEE4 00128AC4  93 E1 00 34 */	stw r31, 52(r1)
/* 8012BEE8 00128AC8  7C 7F 1B 78 */	mr r31, r3
/* 8012BEEC 00128ACC  93 C1 00 30 */	stw r30, 48(r1)
/* 8012BEF0 00128AD0  93 A1 00 2C */	stw r29, 44(r1)
/* 8012BEF4 00128AD4  C0 22 A0 4C */	lfs f1, ftYs_Init_804D9A2C(r2)
/* 8012BEF8 00128AD8  C0 42 A0 48 */	lfs f2, ftYs_Init_804D9A28(r2)
/* 8012BEFC 00128ADC  FC 60 08 90 */	fmr f3, f1
/* 8012BF00 00128AE0  4B F3 D4 AD */	bl Fighter_ChangeMotionState
/* 8012BF04 00128AE4  7F E3 FB 78 */	mr r3, r31
/* 8012BF08 00128AE8  4B F4 2C 9D */	bl ftAnim_8006EBA4
/* 8012BF0C 00128AEC  7F E3 FB 78 */	mr r3, r31
/* 8012BF10 00128AF0  4B F6 65 41 */	bl ftCo_80092450
/* 8012BF14 00128AF4  83 DF 00 2C */	lwz r30, 44(r31)
/* 8012BF18 00128AF8  38 7F 00 00 */	addi r3, r31, 0
/* 8012BF1C 00128AFC  38 80 00 01 */	li r4, 1
/* 8012BF20 00128B00  4B F4 F1 A1 */	bl ftColl_8007B0C0
/* 8012BF24 00128B04  38 00 00 00 */	li r0, 0
/* 8012BF28 00128B08  90 1E 23 4C */	stw r0, 9036(r30)
/* 8012BF2C 00128B0C  C0 22 A0 4C */	lfs f1, ftYs_Init_804D9A2C(r2)
/* 8012BF30 00128B10  D0 3E 23 40 */	stfs f1, 9024(r30)
/* 8012BF34 00128B14  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8012BF38 00128B18  C0 03 02 68 */	lfs f0, 616(r3)
/* 8012BF3C 00128B1C  D0 1E 23 50 */	stfs f0, 9040(r30)
/* 8012BF40 00128B20  90 1E 23 64 */	stw r0, 9060(r30)
/* 8012BF44 00128B24  90 1E 23 60 */	stw r0, 9056(r30)
/* 8012BF48 00128B28  D0 21 00 1C */	stfs f1, 28(r1)
/* 8012BF4C 00128B2C  D0 21 00 18 */	stfs f1, 24(r1)
/* 8012BF50 00128B30  D0 21 00 14 */	stfs f1, 20(r1)
/* 8012BF54 00128B34  80 7E 01 0C */	lwz r3, 268(r30)
/* 8012BF58 00128B38  80 9E 05 E8 */	lwz r4, 1512(r30)
/* 8012BF5C 00128B3C  80 63 00 08 */	lwz r3, 8(r3)
/* 8012BF60 00128B40  88 03 00 11 */	lbz r0, 17(r3)
/* 8012BF64 00128B44  54 00 20 36 */	slwi r0, r0, 4
/* 8012BF68 00128B48  7F A4 00 2E */	lwzx r29, r4, r0
/* 8012BF6C 00128B4C  28 1D 00 00 */	cmplwi r29, 0
/* 8012BF70 00128B50  40 82 00 14 */	bne lbl_8012BF84
/* 8012BF74 00128B54  38 6D 87 B8 */	addi r3, r13, ftYs_Unk2_804D3E58
/* 8012BF78 00128B58  38 80 03 94 */	li r4, 916
/* 8012BF7C 00128B5C  38 AD 87 C0 */	addi r5, r13, ftYs_Unk2_804D3E60
/* 8012BF80 00128B60  48 25 C2 A1 */	bl __assert
lbl_8012BF84:
/* 8012BF84 00128B64  80 61 00 14 */	lwz r3, 20(r1)
/* 8012BF88 00128B68  80 01 00 18 */	lwz r0, 24(r1)
/* 8012BF8C 00128B6C  90 7D 00 38 */	stw r3, 56(r29)
/* 8012BF90 00128B70  90 1D 00 3C */	stw r0, 60(r29)
/* 8012BF94 00128B74  80 01 00 1C */	lwz r0, 28(r1)
/* 8012BF98 00128B78  90 1D 00 40 */	stw r0, 64(r29)
/* 8012BF9C 00128B7C  80 1D 00 14 */	lwz r0, 20(r29)
/* 8012BFA0 00128B80  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8012BFA4 00128B84  40 82 00 4C */	bne lbl_8012BFF0
/* 8012BFA8 00128B88  28 1D 00 00 */	cmplwi r29, 0
/* 8012BFAC 00128B8C  41 82 00 44 */	beq lbl_8012BFF0
/* 8012BFB0 00128B90  40 82 00 14 */	bne lbl_8012BFC4
/* 8012BFB4 00128B94  38 6D 87 B8 */	addi r3, r13, ftYs_Unk2_804D3E58
/* 8012BFB8 00128B98  38 80 02 34 */	li r4, 564
/* 8012BFBC 00128B9C  38 AD 87 C0 */	addi r5, r13, ftYs_Unk2_804D3E60
/* 8012BFC0 00128BA0  48 25 C2 61 */	bl __assert
lbl_8012BFC4:
/* 8012BFC4 00128BA4  80 9D 00 14 */	lwz r4, 20(r29)
/* 8012BFC8 00128BA8  38 60 00 00 */	li r3, 0
/* 8012BFCC 00128BAC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8012BFD0 00128BB0  40 82 00 10 */	bne lbl_8012BFE0
/* 8012BFD4 00128BB4  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 8012BFD8 00128BB8  41 82 00 08 */	beq lbl_8012BFE0
/* 8012BFDC 00128BBC  38 60 00 01 */	li r3, 1
lbl_8012BFE0:
/* 8012BFE0 00128BC0  2C 03 00 00 */	cmpwi r3, 0
/* 8012BFE4 00128BC4  40 82 00 0C */	bne lbl_8012BFF0
/* 8012BFE8 00128BC8  7F A3 EB 78 */	mr r3, r29
/* 8012BFEC 00128BCC  48 24 72 FD */	bl HSD_JObjSetMtxDirtySub
lbl_8012BFF0:
/* 8012BFF0 00128BD0  7F E3 FB 78 */	mr r3, r31
/* 8012BFF4 00128BD4  4B FF F8 B1 */	bl ftYs_Init_8012B8A4
/* 8012BFF8 00128BD8  7F C3 F3 78 */	mr r3, r30
/* 8012BFFC 00128BDC  4B F6 5D 5D */	bl ftCo_80091D58
/* 8012C000 00128BE0  38 7E 00 00 */	addi r3, r30, 0
/* 8012C004 00128BE4  38 80 00 6E */	li r4, 110
/* 8012C008 00128BE8  38 A0 00 7F */	li r5, 127
/* 8012C00C 00128BEC  38 C0 00 40 */	li r6, 64
/* 8012C010 00128BF0  4B F5 C1 39 */	bl ft_80088148
/* 8012C014 00128BF4  80 01 00 3C */	lwz r0, 60(r1)
/* 8012C018 00128BF8  83 E1 00 34 */	lwz r31, 52(r1)
/* 8012C01C 00128BFC  83 C1 00 30 */	lwz r30, 48(r1)
/* 8012C020 00128C00  83 A1 00 2C */	lwz r29, 44(r1)
/* 8012C024 00128C04  38 21 00 38 */	addi r1, r1, 56
/* 8012C028 00128C08  7C 08 03 A6 */	mtlr r0
/* 8012C02C 00128C0C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
