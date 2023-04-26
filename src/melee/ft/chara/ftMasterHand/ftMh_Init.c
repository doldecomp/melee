#include "ftCommon/forward.h"

#include "ftMh_Init.h"

#include "ftMh_MS_341.h"
#include "ftMh_MS_343.h"
#include "ftMh_MS_344.h"
#include "ftMh_MS_346.h"
#include "ftMh_MS_348.h"
#include "ftMh_MS_349.h"
#include "ftMh_MS_352.h"
#include "ftMh_MS_353.h"
#include "ftMh_MS_355.h"
#include "ftMh_MS_357.h"
#include "ftMh_MS_359.h"
#include "ftMh_MS_361.h"
#include "ftMh_MS_363.h"
#include "ftMh_MS_366.h"
#include "ftMh_MS_367.h"
#include "ftMh_MS_368.h"
#include "ftMh_MS_369.h"
#include "ftMh_MS_371_0.h"
#include "ftMh_MS_371_1.h"
#include "ftMh_MS_372.h"
#include "ftMh_MS_376.h"
#include "ftMh_MS_378.h"
#include "ftMh_MS_379.h"
#include "ftMh_MS_380.h"
#include "ftMh_MS_382.h"
#include "ftMh_MS_383.h"
#include "ftMh_MS_384.h"
#include "ftMh_MS_389.h"
#include "types.h"

#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftMh_Init_MotionStateTable[ftMh_MS_SelfCount] = {
    {
        // ftMh_MS_Wait1_0 = 341
        ftMh_SM_Wait1_0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_341_Anim,
        ftMh_MS_341_IASA,
        ftMh_MS_341_Phys,
        ftMh_MS_341_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait2_0 = 342
        ftMh_SM_Wait2_0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_341_Anim,
        ftMh_MS_341_IASA,
        ftMh_MS_341_Phys,
        ftMh_MS_341_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Entry = 343
        ftMh_SM_Entry,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_343_Anim,
        ftMh_MS_343_IASA,
        ftMh_MS_343_Phys,
        ftMh_MS_343_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Damage = 344
        ftMh_SM_Damage,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_344_Anim,
        ftMh_MS_344_IASA,
        ftMh_MS_344_Phys,
        ftMh_MS_344_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Damage2 = 345
        ftMh_SM_Damage2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_345_Anim,
        ftMh_MS_344_IASA,
        ftMh_MS_344_Phys,
        ftMh_MS_344_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WaitSweep = 346
        ftMh_SM_WaitSweep,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_346_Anim,
        ftMh_MS_346_IASA,
        ftMh_MS_346_Phys,
        ftMh_MS_346_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_SweepLoop = 347
        ftMh_SM_SweepLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_347_Anim,
        ftMh_MS_347_IASA,
        ftMh_MS_347_Phys,
        ftMh_MS_347_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_SweepWait = 348
        ftMh_SM_SweepWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_348_Anim,
        ftMh_MS_348_IASA,
        ftMh_MS_348_Phys,
        ftMh_MS_348_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Slap = 349
        ftMh_SM_Slap,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_349_Anim,
        ftMh_MS_349_IASA,
        ftMh_MS_349_Phys,
        ftMh_MS_349_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Walk2 = 350
        ftMh_SM_Walk2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_350_Anim,
        ftMh_MS_350_IASA,
        ftMh_MS_350_Phys,
        ftMh_MS_350_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkLoop = 351
        ftMh_SM_WalkLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_351_Anim,
        ftMh_MS_351_IASA,
        ftMh_MS_351_Phys,
        ftMh_MS_351_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkWait = 352
        ftMh_SM_WalkWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_352_Anim,
        ftMh_MS_352_IASA,
        ftMh_MS_352_Phys,
        ftMh_MS_352_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkShoot = 353
        ftMh_SM_WalkShoot,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_353_Anim,
        ftMh_MS_353_IASA,
        ftMh_MS_353_Phys,
        ftMh_MS_353_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Drill = 354
        ftMh_SM_Drill,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_354_Anim,
        ftMh_MS_354_IASA,
        ftMh_MS_354_Phys,
        ftMh_MS_354_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushUp = 355
        ftMh_SM_RockCrushUp,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_355_Anim,
        ftMh_MS_355_IASA,
        ftMh_MS_355_Phys,
        ftMh_MS_355_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushWait = 356
        ftMh_SM_RockCrushWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_356_Anim,
        ftMh_MS_356_IASA,
        ftMh_MS_356_Phys,
        ftMh_MS_356_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushDown = 357
        ftMh_SM_RockCrushDown,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_357_Anim,
        ftMh_MS_357_IASA,
        ftMh_MS_357_Phys,
        ftMh_MS_357_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_PaperCrush = 358
        ftMh_SM_PaperCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_358_Anim,
        ftMh_MS_358_IASA,
        ftMh_MS_358_Phys,
        ftMh_MS_358_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Poke1 = 359
        ftMh_SM_Poke1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_359_Anim,
        ftMh_MS_359_IASA,
        ftMh_MS_359_Phys,
        ftMh_MS_359_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Poke2 = 360
        ftMh_SM_Poke2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_360_Anim,
        ftMh_MS_359_IASA,
        ftMh_MS_359_Phys,
        ftMh_MS_359_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamStart = 361
        ftMh_SM_FingerBeamStart,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_361_Anim,
        ftMh_MS_361_IASA,
        ftMh_MS_361_Phys,
        ftMh_MS_361_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamLoop = 362
        ftMh_SM_FingerBeamLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_362_Anim,
        ftMh_MS_362_IASA,
        ftMh_MS_362_Phys,
        ftMh_MS_362_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamEnd = 363
        ftMh_SM_FingerBeamEnd,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_363_Anim,
        ftMh_MS_363_IASA,
        ftMh_MS_363_Phys,
        ftMh_MS_363_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun1 = 364
        ftMh_SM_FingerGun1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_364_Anim,
        ftMh_MS_364_IASA,
        ftMh_MS_364_Phys,
        ftMh_MS_364_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun2 = 365
        ftMh_SM_FingerGun2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_365_Anim,
        ftMh_MS_365_IASA,
        ftMh_MS_365_Phys,
        ftMh_MS_365_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun3 = 366
        ftMh_SM_FingerGun3,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_366_Anim,
        ftMh_MS_366_IASA,
        ftMh_MS_366_Phys,
        ftMh_MS_366_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane1 = 367
        ftMh_SM_BackAirplane1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_367_Anim,
        ftMh_MS_367_IASA,
        ftMh_MS_367_Phys,
        ftMh_MS_367_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane2 = 368
        ftMh_SM_BackAirplane2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_368_Anim,
        ftMh_MS_368_IASA,
        ftMh_MS_368_Phys,
        ftMh_MS_368_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane3 = 369
        ftMh_SM_BackAirplane3,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_369_Anim,
        ftMh_MS_369_IASA,
        ftMh_MS_369_Phys,
        ftMh_MS_369_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackPunch = 370
        ftMh_SM_BackPunch,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_370_Anim,
        ftMh_MS_370_IASA,
        ftMh_MS_370_Phys,
        ftMh_MS_370_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackCrush = 371
        ftMh_SM_BackCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_371_Anim,
        ftMh_MS_371_IASA,
        ftMh_MS_371_Phys,
        ftMh_MS_371_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackDisappear = 372
        ftMh_SM_BackDisappear,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_372_Anim,
        ftMh_MS_372_IASA,
        ftMh_MS_372_Phys,
        ftMh_MS_372_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait1_1 = 373
        ftMh_SM_Wait1_1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_373_Anim,
        ftMh_MS_373_IASA,
        ftMh_MS_373_Phys,
        ftMh_MS_373_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Grab = 374
        ftMh_SM_Grab,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_374_Anim,
        ftMh_MS_374_IASA,
        ftMh_MS_374_Phys,
        ftMh_MS_374_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Cancel = 375
        ftMh_SM_Cancel,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_375_Anim,
        ftMh_MS_375_IASA,
        ftMh_MS_375_Phys,
        ftMh_MS_375_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeezing0 = 376
        ftMh_SM_Squeezing0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_376_Anim,
        ftMh_MS_376_IASA,
        ftMh_MS_376_Phys,
        ftMh_MS_376_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeezing1 = 377
        ftMh_SM_Squeezing1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_376_Anim,
        ftMh_MS_376_IASA,
        ftMh_MS_376_Phys,
        ftMh_MS_376_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeeze = 378
        ftMh_SM_Squeeze,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_378_Anim,
        ftMh_MS_378_IASA,
        ftMh_MS_378_Phys,
        ftMh_MS_378_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Throw = 379
        ftMh_SM_Throw,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_379_Anim,
        ftMh_MS_379_IASA,
        ftMh_MS_379_Phys,
        ftMh_MS_379_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Slam = 380
        ftMh_SM_Slam,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_380_Anim,
        ftMh_MS_380_IASA,
        ftMh_MS_380_Phys,
        ftMh_MS_380_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Fail = 381
        ftMh_SM_Fail,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_381_Anim,
        ftMh_MS_381_IASA,
        ftMh_MS_381_Phys,
        ftMh_MS_381_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagCrush = 382
        ftMh_SM_TagCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_382_Anim,
        ftMh_MS_382_IASA,
        ftMh_MS_382_Phys,
        ftMh_MS_382_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagApplaud = 383
        ftMh_SM_TagApplaud,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_383_Anim,
        ftMh_MS_383_IASA,
        ftMh_MS_383_Phys,
        ftMh_MS_383_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagRockPaper = 384
        ftMh_SM_TagRockPaper,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_384_Anim,
        ftMh_MS_384_IASA,
        ftMh_MS_384_Phys,
        ftMh_MS_384_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagGrab = 385
        ftMh_SM_TagGrab,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_385_Anim,
        ftMh_MS_385_IASA,
        ftMh_MS_385_Phys,
        ftMh_MS_385_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagSqueeze = 386
        ftMh_SM_TagSqueeze,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_386_Anim,
        ftMh_MS_386_IASA,
        ftMh_MS_386_Phys,
        ftMh_MS_386_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagFail = 387
        ftMh_SM_TagFail,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_387_Anim,
        ftMh_MS_387_IASA,
        ftMh_MS_387_Phys,
        ftMh_MS_387_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagCancel = 388
        ftMh_SM_TagCancel,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_388_Anim,
        ftMh_MS_388_IASA,
        ftMh_MS_388_Phys,
        ftMh_MS_388_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait1_2 = 389
        ftMh_SM_Wait1_2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_389_Anim,
        NULL,
        ftMh_MS_389_Phys,
        ftMh_MS_389_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait2_1 = 390
        ftMh_SM_Wait2_1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_389_Anim,
        NULL,
        ftMh_MS_389_Phys,
        ftMh_MS_389_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftMh_Init_DatFilename[] = "PlMh.dat";
char ftMh_Init_DataName[] = "ftDataMasterhand";
char ftMh_Init_803D4090[] = "PlMhNr.dat";
char ftMh_Init_803D409C[] = "PlyMasterhand_Share_joint";
char ftMh_Init_AnimDatFilename[] = "PlMhAJ.dat";

Fighter_CostumeStrings ftMh_Init_CostumeStrings[] = {
    { ftMh_Init_803D4090, ftMh_Init_803D409C, NULL },
};

void ftMh_Init_OnDeath(HSD_GObj* gobj) {}

void ftMh_Init_OnLoad(HSD_GObj* gobj)
{
    ftMasterHand_SpecialAttrs* ftData_attr;
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->ft_data;
    ftData_attr = ftdata->ext_attr;
    {
        UNK_T* items = ftdata->x48_items;
        PUSH_ATTRS(fp, ftMasterHand_SpecialAttrs);
        ftBossLib_8015BDB4(gobj);
        it_8026B3F8(items[0], 125);
        it_8026B3F8(items[1], 126);
        fp->x2229_b5_no_normal_motion = true;
        fp->x2229_b6 = true;
        fp->x2229_b7 = true;
        fp->x222A_flag.bits.b0 = true;
        fp->x222A_flag.bits.b1 = true;
        fp->x2229_b3 = true;
        fp->cur_pos.x = ftData_attr->x30_pos2.x;
        fp->cur_pos.y = ftData_attr->x30_pos2.y;
        fp->cur_pos.z = 0;
        fp->mv.mh.unk0.x34 = 0;
        fp->mv.mh.unk0.x38 = 0;
        fp->mv.mh.unk0.x3C = 0;
        fp->mv.mh.unk0.x40 = 0;
        fp->mv.mh.unk0.x28 = -1;
        fp->mv.mh.unk0.x2C = -1;
        fp->mv.mh.unk0.x30 = -1;
        fp->mv.mh.unk0.x1C = 0;
        fp->mv.mh.unk0.x20 = 0;
        fp->fv.mh.x222C = ftBossLib_8015C244(gobj, &fp->cur_pos);
        fp->fv.mh.x2238 = 1;
        fp->fv.mh.x224C = 0;
        fp->fv.mh.x2250 = ftMh_MS_SweepLoop;
        fp->fv.mh.x2254 = 0;
        fp->x1A98 = 1;
        ftBossLib_8015BD24(fp->x1A98, &fp->fv.mh.x223C, fp->fv.mh.x2238,
                           ftData_attr->x18, ftData_attr->x20,
                           ftData_attr->x1C);
    }
}

void ftMh_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftMasterHand_SpecialAttrs);
}
