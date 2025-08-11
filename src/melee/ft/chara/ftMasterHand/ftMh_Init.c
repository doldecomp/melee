#include <platform.h>
#include <placeholder.h>

#include "ftMh_Init.h"

#include "ftMh_BackAirplane1.h"
#include "ftMh_BackAirplane2.h"
#include "ftMh_BackAirplane3.h"
#include "ftMh_BackCrush_0.h"
#include "ftMh_BackCrush_1.h"
#include "ftMh_BackDisappear.h"
#include "ftMh_Damage_0.h"
#include "ftMh_Drill.h"
#include "ftMh_Entry.h"
#include "ftMh_FingerBeam.h"
#include "ftMh_FingerGun.h"
#include "ftMh_FingerGun3.h"
#include "ftMh_PaperCrush.h"
#include "ftMh_Poke.h"
#include "ftMh_RockCrush.h"
#include "ftMh_Slam.h"
#include "ftMh_Slap.h"
#include "ftMh_Squeeze.h"
#include "ftMh_Squeezing.h"
#include "ftMh_Sweep.h"
#include "ftMh_SweepWait.h"
#include "ftMh_TagApplaud.h"
#include "ftMh_TagCrush.h"
#include "ftMh_TagRockPaper.h"
#include "ftMh_Throw.h"
#include "ftMh_Wait1_0.h"
#include "ftMh_Wait1_2.h"
#include "ftMh_Walk.h"
#include "types.h"

#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "it/it_26B1.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

MotionState ftMh_Init_MotionStateTable[ftMh_MS_SelfCount] = {
    {
        // ftMh_MS_Wait1_0 = 341
        ftMh_SM_Wait1_0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Wait1_0_Anim,
        ftMh_Wait1_0_IASA,
        ftMh_Wait1_0_Phys,
        ftMh_Wait1_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait2_0 = 342
        ftMh_SM_Wait2_0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Wait1_0_Anim,
        ftMh_Wait1_0_IASA,
        ftMh_Wait1_0_Phys,
        ftMh_Wait1_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Entry = 343
        ftMh_SM_Entry,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Entry_Anim,
        ftMh_Entry_IASA,
        ftMh_Entry_Phys,
        ftMh_Entry_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Damage = 344
        ftMh_SM_Damage,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Damage_Anim,
        ftMh_Damage_IASA,
        ftMh_Damage_Phys,
        ftMh_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Damage2 = 345
        ftMh_SM_Damage2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_MS_345_Anim,
        ftMh_Damage_IASA,
        ftMh_Damage_Phys,
        ftMh_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WaitSweep = 346
        ftMh_SM_WaitSweep,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_WaitSweep_Anim,
        ftMh_WaitSweep_IASA,
        ftMh_WaitSweep_Phys,
        ftMh_WaitSweep_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_SweepLoop = 347
        ftMh_SM_SweepLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_SweepLoop_Anim,
        ftMh_SweepLoop_IASA,
        ftMh_SweepLoop_Phys,
        ftMh_SweepLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_SweepWait = 348
        ftMh_SM_SweepWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_SweepWait_Anim,
        ftMh_SweepWait_IASA,
        ftMh_SweepWait_Phys,
        ftMh_SweepWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Slap = 349
        ftMh_SM_Slap,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Slap_Anim,
        ftMh_Slap_IASA,
        ftMh_Slap_Phys,
        ftMh_Slap_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Walk2 = 350
        ftMh_SM_Walk2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Walk2_Anim,
        ftMh_Walk2_IASA,
        ftMh_Walk2_Phys,
        ftMh_Walk2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkLoop = 351
        ftMh_SM_WalkLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_WalkLoop_Anim,
        ftMh_WalkLoop_IASA,
        ftMh_WalkLoop_Phys,
        ftMh_WalkLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkWait = 352
        ftMh_SM_WalkWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_WalkWait_Anim,
        ftMh_WalkWait_IASA,
        ftMh_WalkWait_Phys,
        ftMh_WalkWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkShoot = 353
        ftMh_SM_WalkShoot,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_WalkShoot_Anim,
        ftMh_WalkShoot_IASA,
        ftMh_WalkShoot_Phys,
        ftMh_WalkShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Drill = 354
        ftMh_SM_Drill,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Drill_Anim,
        ftMh_Drill_IASA,
        ftMh_Drill_Phys,
        ftMh_Drill_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushUp = 355
        ftMh_SM_RockCrushUp,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_RockCrushUp_Anim,
        ftMh_RockCrushUp_IASA,
        ftMh_RockCrushUp_Phys,
        ftMh_RockCrushUp_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushWait = 356
        ftMh_SM_RockCrushWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_RockCrushWait_Anim,
        ftMh_RockCrushWait_IASA,
        ftMh_RockCrushWait_Phys,
        ftMh_RockCrushWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushDown = 357
        ftMh_SM_RockCrushDown,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_RockCrushDown_Anim,
        ftMh_RockCrushDown_IASA,
        ftMh_RockCrushDown_Phys,
        ftMh_RockCrushDown_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_PaperCrush = 358
        ftMh_SM_PaperCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_PaperCrush_Anim,
        ftMh_PaperCrush_IASA,
        ftMh_PaperCrush_Phys,
        ftMh_PaperCrush_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Poke1 = 359
        ftMh_SM_Poke1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Poke1_Anim,
        ftMh_Poke1_IASA,
        ftMh_Poke1_Phys,
        ftMh_Poke1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Poke2 = 360
        ftMh_SM_Poke2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Poke2_Anim,
        ftMh_Poke1_IASA,
        ftMh_Poke1_Phys,
        ftMh_Poke1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamStart = 361
        ftMh_SM_FingerBeamStart,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_FingerBeamStart_Anim,
        ftMh_FingerBeamStart_IASA,
        ftMh_FingerBeamStart_Phys,
        ftMh_FingerBeamStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamLoop = 362
        ftMh_SM_FingerBeamLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_FingerBeamLoop_Anim,
        ftMh_FingerBeamLoop_IASA,
        ftMh_FingerBeamLoop_Phys,
        ftMh_FingerBeamLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamEnd = 363
        ftMh_SM_FingerBeamEnd,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_FingerBeamEnd_Anim,
        ftMh_FingerBeamEnd_IASA,
        ftMh_FingerBeamEnd_Phys,
        ftMh_FingerBeamEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun1 = 364
        ftMh_SM_FingerGun1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_FingerGun1_Anim,
        ftMh_FingerGun1_IASA,
        ftMh_FingerGun1_Phys,
        ftMh_FingerGun1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun2 = 365
        ftMh_SM_FingerGun2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_FingerGun2_Anim,
        ftMh_FingerGun2_IASA,
        ftMh_FingerGun2_Phys,
        ftMh_FingerGun2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun3 = 366
        ftMh_SM_FingerGun3,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_FingerGun3_Anim,
        ftMh_FingerGun3_IASA,
        ftMh_FingerGun3_Phys,
        ftMh_FingerGun3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane1 = 367
        ftMh_SM_BackAirplane1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_BackAirplane1_Anim,
        ftMh_BackAirplane1_IASA,
        ftMh_BackAirplane1_Phys,
        ftMh_BackAirplane1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane2 = 368
        ftMh_SM_BackAirplane2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_BackAirplane2_Anim,
        ftMh_BackAirplane2_IASA,
        ftMh_BackAirplane2_Phys,
        ftMh_BackAirplane2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane3 = 369
        ftMh_SM_BackAirplane3,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_BackAirplane3_Anim,
        ftMh_BackAirplane3_IASA,
        ftMh_BackAirplane3_Phys,
        ftMh_BackAirplane3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackPunch = 370
        ftMh_SM_BackPunch,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_BackPunch_Anim,
        ftMh_BackPunch_IASA,
        ftMh_BackPunch_Phys,
        ftMh_BackPunch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackCrush = 371
        ftMh_SM_BackCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_BackCrush_Anim,
        ftMh_BackCrush_IASA,
        ftMh_BackCrush_Phys,
        ftMh_BackCrush_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackDisappear = 372
        ftMh_SM_BackDisappear,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_BackDisappear_Anim,
        ftMh_BackDisappear_IASA,
        ftMh_BackDisappear_Phys,
        ftMh_BackDisappear_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait1_1 = 373
        ftMh_SM_Wait1_1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Wait1_1_Anim,
        ftMh_Wait1_1_IASA,
        ftMh_Wait1_1_Phys,
        ftMh_Wait1_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Grab = 374
        ftMh_SM_Grab,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Grab_Anim,
        ftMh_Grab_IASA,
        ftMh_Grab_Phys,
        ftMh_Grab_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Cancel = 375
        ftMh_SM_Cancel,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Cancel_Anim,
        ftMh_Cancel_IASA,
        ftMh_Cancel_Phys,
        ftMh_Cancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeezing0 = 376
        ftMh_SM_Squeezing0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Squeezing_Anim,
        ftMh_Squeezing_IASA,
        ftMh_Squeezing_Phys,
        ftMh_Squeezing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeezing1 = 377
        ftMh_SM_Squeezing1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Squeezing_Anim,
        ftMh_Squeezing_IASA,
        ftMh_Squeezing_Phys,
        ftMh_Squeezing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeeze = 378
        ftMh_SM_Squeeze,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Squeeze_Anim,
        ftMh_Squeeze_IASA,
        ftMh_Squeeze_Phys,
        ftMh_Squeeze_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Throw = 379
        ftMh_SM_Throw,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Throw_Anim,
        ftMh_Throw_IASA,
        ftMh_Throw_Phys,
        ftMh_Throw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Slam = 380
        ftMh_SM_Slam,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Slam_Anim,
        ftMh_Slam_IASA,
        ftMh_Slam_Phys,
        ftMh_Slam_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Fail = 381
        ftMh_SM_Fail,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Fail_Anim,
        ftMh_Fail_IASA,
        ftMh_Fail_Phys,
        ftMh_Fail_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagCrush = 382
        ftMh_SM_TagCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_TagCrush_Anim,
        ftMh_TagCrush_IASA,
        ftMh_TagCrush_Phys,
        ftMh_TagCrush_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagApplaud = 383
        ftMh_SM_TagApplaud,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_TagApplaud_Anim,
        ftMh_TagApplaud_IASA,
        ftMh_TagApplaud_Phys,
        ftMh_TagApplaud_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagRockPaper = 384
        ftMh_SM_TagRockPaper,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_TagRockPaper_Anim,
        ftMh_TagRockPaper_IASA,
        ftMh_TagRockPaper_Phys,
        ftMh_TagRockPaper_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagGrab = 385
        ftMh_SM_TagGrab,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_TagGrab_Anim,
        ftMh_TagGrab_IASA,
        ftMh_TagGrab_Phys,
        ftMh_TagGrab_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagSqueeze = 386
        ftMh_SM_TagSqueeze,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_TagSqueeze_Anim,
        ftMh_TagSqueeze_IASA,
        ftMh_TagSqueeze_Phys,
        ftMh_TagSqueeze_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagFail = 387
        ftMh_SM_TagFail,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_TagFail_Anim,
        ftMh_TagFail_IASA,
        ftMh_TagFail_Phys,
        ftMh_TagFail_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagCancel = 388
        ftMh_SM_TagCancel,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_TagCancel_Anim,
        ftMh_TagCancel_IASA,
        ftMh_TagCancel_Phys,
        ftMh_TagCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait1_2 = 389
        ftMh_SM_Wait1_2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Wait1_2_Anim,
        NULL,
        ftMh_Wait1_2_Phys,
        ftMh_Wait1_2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait2_1 = 390
        ftMh_SM_Wait2_1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftMh_Wait1_2_Anim,
        NULL,
        ftMh_Wait1_2_Phys,
        ftMh_Wait1_2_Coll,
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
        fp->no_normal_motion = true;
        fp->x2229_b6 = true;
        fp->no_kb = true;
        fp->x222A_b0 = true;
        fp->x222A_b1 = true;
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
        fp->x1A88.x10 = 1;
        ftBossLib_8015BD24(fp->x1A88.x10, &fp->fv.mh.x223C, fp->fv.mh.x2238,
                           ftData_attr->x18, ftData_attr->x20,
                           ftData_attr->x1C);
    }
}

void ftMh_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftMasterHand_SpecialAttrs);
}
