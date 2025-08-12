#include "ftNess/ftNs_Init.h"

#include "ftNs_AttackHi4.h"
#include "ftNs_AttackLw4.h"
#include "ftNs_AttackS4.h"
#include "ftNs_SpecialHi.h"
#include "ftNs_SpecialN.h"
#include "ftNs_SpecialS.h"

#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftNess/ftNs_SpecialLw.h"
#include "ftNess/types.h"

#include "it/forward.h"

#include "it/it_26B1.h"

MotionState ftNs_Init_MotionStateTable[ftNs_MS_SelfCount] = {
    {
        // ftNs_MS_AttackS4 = 341
        ftCo_SM_AttackS4,
        ftNs_MF_AttackS4,
        FtMoveId_AttackS4 << 24,
        ftNs_AttackS4_Anim,
        ftNs_AttackS4_IASA,
        ftNs_AttackS4_Phys,
        ftNs_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_AttackHi4 = 342
        ftCo_SM_AttackHi4,
        ftNs_MF_AttackHi4Start,
        (FtMoveId_AttackHi4 << 24) | (1 << 23),
        ftNs_AttackHi4_Anim,
        ftNs_AttackHi4_IASA,
        ftNs_AttackHi4_Phys,
        ftNs_AttackHi4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_AttackHi4Charge = 343
        ftNs_SM_AttackHi4Charge,
        ftNs_MF_AttackHi4,
        FtMoveId_AttackHi4 << 24,
        ftNs_AttackHi4Charge_Anim,
        ftNs_AttackHi4Charge_IASA,
        ftNs_AttackHi4Charge_Phys,
        ftNs_AttackHi4Charge_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_AttackHi4Release = 344
        ftNs_SM_AttackHi4Release,
        ftNs_MF_AttackHi4,
        FtMoveId_AttackHi4 << 24,
        ftNs_AttackHi4Release_Anim,
        ftNs_AttackHi4Release_IASA,
        ftNs_AttackHi4Release_Phys,
        ftNs_AttackHi4Release_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_AttackLw4 = 345
        ftCo_SM_AttackLw4,
        ftNs_MF_AttackLw4Start,
        (FtMoveId_AttackLw4 << 24) | (1 << 23),
        ftNs_AttackLw4_Anim,
        ftNs_AttackLw4_IASA,
        ftNs_AttackLw4_Phys,
        ftNs_AttackLw4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_AttackLw4Charge = 346
        ftNs_SM_AttackLw4Charge,
        ftNs_MF_AttackLw4,
        FtMoveId_AttackLw4 << 24,
        ftNs_AttackLw4Charge_Anim,
        ftNs_AttackLw4Charge_IASA,
        ftNs_AttackLw4Charge_Phys,
        ftNs_AttackLw4Charge_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_AttackLw4Release = 347
        ftNs_SM_AttackLw4Release,
        ftNs_MF_AttackLw4,
        FtMoveId_AttackLw4 << 24,
        ftNs_AttackLw4Release_Anim,
        ftNs_AttackLw4Release_IASA,
        ftNs_AttackLw4Release_Phys,
        ftNs_AttackLw4Release_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialNStart = 348
        ftNs_SM_SpecialNStart,
        ftNs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftNs_SpecialNStart_Anim,
        ftNs_SpecialNStart_IASA,
        ftNs_SpecialNStart_Phys,
        ftNs_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialNHold = 349
        ftNs_SM_SpecialNHold0,
        ftNs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftNs_SpecialNRelease_Anim,
        ftNs_SpecialNRelease_IASA,
        ftNs_SpecialNRelease_Phys,
        ftNs_SpecialNRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialNRelease = 350
        ftNs_SM_SpecialNHold1,
        ftNs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftNs_SpecialNRelease_Anim,
        ftNs_SpecialNRelease_IASA,
        ftNs_SpecialNRelease_Phys,
        ftNs_SpecialNRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialNEnd = 351
        ftNs_SM_SpecialNEnd,
        ftNs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftNs_SpecialNEnd_Anim,
        ftNs_SpecialNEnd_IASA,
        ftNs_SpecialNEnd_Phys,
        ftNs_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirNStart = 352
        ftNs_SM_SpecialAirNStart,
        ftNs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftNs_SpecialAirNStart_Anim,
        ftNs_SpecialAirNStart_IASA,
        ftNs_SpecialAirNStart_Phys,
        ftNs_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirNHold = 353
        ftNs_SM_SpecialAirNHold0,
        ftNs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftNs_SpecialAirNRelease_Anim,
        ftNs_SpecialAirNRelease_IASA,
        ftNs_SpecialAirNRelease_Phys,
        ftNs_SpecialAirNRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirNRelease = 354
        ftNs_SM_SpecialAirNHold1,
        ftNs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftNs_SpecialAirNRelease_Anim,
        ftNs_SpecialAirNRelease_IASA,
        ftNs_SpecialAirNRelease_Phys,
        ftNs_SpecialAirNRelease_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirNEnd = 355
        ftNs_SM_SpecialAirNEnd,
        ftNs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftNs_SpecialAirNEnd_Anim,
        ftNs_SpecialAirNEnd_IASA,
        ftNs_SpecialAirNEnd_Phys,
        ftNs_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialS = 356
        ftNs_SM_SpecialS,
        ftNs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftNs_SpecialS_Anim,
        NULL,
        ftNs_SpecialS_Phys,
        ftNs_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirS = 357
        ftNs_SM_SpecialAirS,
        ftNs_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftNs_SpecialAirS_Anim,
        NULL,
        ftNs_SpecialAirS_Phys,
        ftNs_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialHiStart = 358
        ftNs_SM_SpecialHiStart,
        ftNs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialHiStart_Anim,
        ftNs_SpecialHiStart_IASA,
        ftNs_SpecialHiStart_Phys,
        ftNs_SpecialHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialHiHold = 359
        ftNs_SM_SpecialHiHold,
        ftNs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialHiHold_Anim,
        ftNs_SpecialHiHold_IASA,
        ftNs_SpecialHiHold_Phys,
        ftNs_SpecialHiHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialHiEnd = 360
        ftNs_SM_SpecialHiEnd,
        ftNs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialHiEnd_Anim,
        ftNs_SpecialHiEnd_IASA,
        ftNs_SpecialHiEnd_Phys,
        ftNs_SpecialHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialHi = 361
        ftNs_SM_SpecialHi,
        ftNs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialHi_Anim,
        ftNs_SpecialHi_IASA,
        ftNs_SpecialHi_Phys,
        ftNs_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirHiStart = 362
        ftNs_SM_SpecialAirHiStart,
        ftNs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialAirHiStart_Anim,
        ftNs_SpecialAirHiStart_IASA,
        ftNs_SpecialAirHiStart_Phys,
        ftNs_SpecialAirHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirHiHold = 363
        ftNs_SM_SpecialAirHiHold,
        ftNs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialAirHiHold_Anim,
        ftNs_SpecialAirHiHold_IASA,
        ftNs_SpecialAirHiHold_Phys,
        ftNs_SpecialAirHiHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirHiEnd = 364
        ftNs_SM_SpecialAirHiEnd,
        ftNs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialAirHiEnd_Anim,
        ftNs_SpecialAirHiEnd_IASA,
        ftNs_SpecialAirHiEnd_Phys,
        ftNs_SpecialAirHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirHi = 365
        ftNs_SM_SpecialAirHi,
        ftNs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialAirHi_Anim,
        ftNs_SpecialAirHi_IASA,
        ftNs_SpecialAirHi_Phys,
        ftNs_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirHiRebound = 366
        ftNs_SM_SpecialAirHiRebound,
        ftNs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftNs_SpecialAirHiRebound_Anim,
        ftNs_SpecialAirHiRebound_IASA,
        ftNs_SpecialAirHiRebound_Phys,
        ftNs_SpecialAirHiRebound_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialLwStart = 367
        ftNs_SM_SpecialLwStart,
        ftNs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialLwStart_Anim,
        ftNs_SpecialLwStart_IASA,
        ftNs_SpecialLwStart_Phys,
        ftNs_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialLwHold = 368
        ftNs_SM_SpecialLwHold,
        ftNs_MF_SpecialLwLoop,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialLwHold_Anim,
        ftNs_SpecialLwHold_IASA,
        ftNs_SpecialLwHold_Phys,
        ftNs_SpecialLwHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialLwHit = 369
        ftNs_SM_SpecialLwHit,
        ftNs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialLwHit_Anim,
        ftNs_SpecialLwHit_IASA,
        ftNs_SpecialLwHit_Phys,
        ftNs_SpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialLwEnd = 370
        ftNs_SM_SpecialLwEnd,
        ftNs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialLwEnd_Anim,
        ftNs_SpecialLwEnd_IASA,
        ftNs_SpecialLwEnd_Phys,
        ftNs_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialLwTurn = 371
        ftNs_SM_SpecialLwHold,
        ftNs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialLwTurn_Anim,
        ftNs_SpecialLwTurn_IASA,
        ftNs_SpecialLwTurn_Phys,
        ftNs_SpecialLwTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirLwStart = 372
        ftNs_SM_SpecialAirLwStart,
        ftNs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialAirLwStart_Anim,
        ftNs_SpecialAirLwStart_IASA,
        ftNs_SpecialAirLwStart_Phys,
        ftNs_SpecialAirLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirLwHold = 373
        ftNs_SM_SpecialAirLwHold,
        ftNs_MF_SpecialAirLwLoop,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialAirLwHold_Anim,
        ftNs_SpecialAirLwHold_IASA,
        ftNs_SpecialAirLwHold_Phys,
        ftNs_SpecialAirLwHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirLwHit = 374
        ftNs_SM_SpecialAirLwHit,
        ftNs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialAirLwHit_Anim,
        ftNs_SpecialAirLwHit_IASA,
        ftNs_SpecialAirLwHit_Phys,
        ftNs_SpecialAirLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirLwEnd = 375
        ftNs_SM_SpecialAirLwEnd,
        ftNs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialAirLwEnd_Anim,
        ftNs_SpecialAirLwEnd_IASA,
        ftNs_SpecialAirLwEnd_Phys,
        ftNs_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftNs_MS_SpecialAirLwTurn = 376
        ftNs_SM_SpecialAirLwHold,
        ftNs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftNs_SpecialAirLwTurn_Anim,
        ftNs_SpecialAirLwTurn_IASA,
        ftNs_SpecialAirLwTurn_Phys,
        ftNs_SpecialAirLwTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftNs_Init_DatFilename[] = "PlNs.dat";
char ftNs_Init_DataName[] = "ftDataNess";
char ftNs_Init_803CCAE8[] = "PlNsNr.dat";
char ftNs_Init_803CCAF4[] = "PlyNess5K_Share_joint";
char ftNs_Init_803CCB0C[] = "PlyNess5K_Share_matanim_joint";
char ftNs_Init_803CCB2C[] = "PlNsYe.dat";
char ftNs_Init_803CCB38[] = "PlyNess5KYe_Share_joint";
char ftNs_Init_803CCB50[] = "PlyNess5KYe_Share_matanim_joint";
char ftNs_Init_803CCB70[] = "PlNsBu.dat";
char ftNs_Init_803CCB7C[] = "PlyNess5KBu_Share_joint";
char ftNs_Init_803CCB94[] = "PlyNess5KBu_Share_matanim_joint";
char ftNs_Init_803CCBB4[] = "PlNsGr.dat";
char ftNs_Init_803CCBC0[] = "PlyNess5KGr_Share_joint";
char ftNs_Init_803CCBD8[] = "PlyNess5KGr_Share_matanim_joint";
char ftNs_Init_AnimDatFilename[] = "PlNsAJ.dat";

Fighter_DemoStrings ftNs_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileNess",
    "ftDemoIntroMotionFileNess",
    "ftDemoEndingMotionFileNess",
    "ftDemoViWaitMotionFileNess",
};

Fighter_CostumeStrings ftNs_Init_CostumeStrings[] = {
    { ftNs_Init_803CCAE8, ftNs_Init_803CCAF4, ftNs_Init_803CCB0C },
    { ftNs_Init_803CCB2C, ftNs_Init_803CCB38, ftNs_Init_803CCB50 },
    { ftNs_Init_803CCB70, ftNs_Init_803CCB7C, ftNs_Init_803CCB94 },
    { ftNs_Init_803CCBB4, ftNs_Init_803CCBC0, ftNs_Init_803CCBD8 },
};

void ftNs_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.ns.pkflash_gobj = NULL;
    fp->fv.ns.pkthunder_gobj = NULL;
    fp->fv.ns.bat_gobj = NULL;
    fp->fv.ns.yoyo_gobj = NULL;
    fp->fv.ns.pkthunder_gfx = false;
}

void ftNs_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftNessAttributes);

    it_8026B3F8(item_list[0], It_Kind_Ness_PKFire);
    it_8026B3F8(item_list[1], It_Kind_Ness_PKFire_Flame);
    it_8026B3F8(item_list[2], It_Kind_Ness_PKFlush);
    it_8026B3F8(item_list[8], It_Kind_Ness_PKFlush_Explode);
    it_8026B3F8(item_list[3], It_Kind_Ness_PKThunder);
    it_8026B3F8(item_list[4], It_Kind_Ness_PKThunder1);
    it_8026B3F8(item_list[5], It_Kind_Ness_PKThunder2);
    it_8026B3F8(item_list[6], It_Kind_Ness_PKThunder3);
    it_8026B3F8(item_list[7], It_Kind_Ness_PKThunder4);
    it_8026B3F8(item_list[9], It_Kind_Ness_Bat);
    it_8026B3F8(item_list[10], It_Kind_Ness_Yoyo);
}

void ftNs_Init_OnDamage(HSD_GObj* gobj)
{
    ftNs_AttackHi4_YoyoItemDespawn(gobj);
    ftNs_SpecialN_ItemPKFlushSetNULL(gobj);
    ftNs_SpecialHi_TakeDamage(gobj);
    ftNs_AttackS4_ItemNessBatRemove(gobj);
}

void ftNs_Init_OnAbsorb(HSD_GObj* gobj)
{
    ftNs_AbsorbThink_DecideAction(gobj);
}

float ftNs_Init_GetAbsorbHeal(Fighter* fp)
{
    return ((ftNessAttributes*) fp->dat_attrs)->x94_PSI_MAGNET_HEAL_MUL;
}

void ftNs_Init_OnItemPickup(HSD_GObj* gobj, bool catchItemFlag)
{
    Fighter_OnItemPickup(gobj, catchItemFlag, 1, 1);
}

void ftNs_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftNs_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftNs_Init_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag)
{
    Fighter_OnItemDrop(gobj, dropItemFlag, 1, 1);
}

void ftNs_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftNessAttributes);
}

void ftNs_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftNs_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
