#include "ftCh_Init.h"

#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/chara/ftCommon/ftCo_CaptureCut.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCrazyHand/forward.h"

#include "ftMasterHand/types.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 156310 */ static void ftCh_Init_80156310(HSD_GObj* gobj);
/* 157080 */ static void fn_80157080(Fighter_GObj* gobj);
/* 15746C */ static void fn_8015746C(HSD_GObj* gobj);
/* 15755C */ static void fn_8015755C(HSD_GObj* gobj);
/* 1578E8 */ static void fn_801578E8(HSD_GObj* gobj);
/* 159288 */ static void fn_80159288(HSD_GObj* gobj);
/* 15B174 */ void ftCh_GrabUnk1_8015B174(HSD_GObj* gobj);
/* 15B548 */ static void fn_8015B548(HSD_GObj* gobj, HSD_GObj* gobj2);

extern f32 ftCh_Init_804DA070;
extern f32 ftCh_Init_804DA074;
extern f32 ftCh_Init_804DA080;
extern f32 ftCh_Init_804DA084;
extern f32 ftCh_Init_804DA178;
extern f32 ftCh_Init_804DA17C;

/* static */ void ftCh_Init_801566B4(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156688(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_801566E0(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156710(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156740(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156770(void);
/* static */ void ftCh_Init_801567A0(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_801567AC(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_801567DC(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_8015683C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_8015686C(void);
/* static */ void ftCh_Init_80156878(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156884(void);
/* static */ void ftCh_Init_80156898(void);
/* static */ void ftCh_Init_801568AC(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_801568B8(void);
/* static */ void ftCh_Init_801568E8(void);
/* static */ void ftCh_Init_80156918(void);
/* static */ void ftCh_Init_80156948(void);

MotionState ftCh_Init_MotionStateTable[ftCh_MS_SelfCount] = {
    {
        // ftMh_MS_Wait1_0 = 341
        ftMh_SM_Wait1_0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Wait1_0_Anim,
        ftCh_Wait1_0_IASA,
        ftCh_Wait1_0_Phys,
        ftCh_Wait1_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait2_0 = 342
        ftMh_SM_Wait2_0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Wait1_0_Anim,
        ftCh_Wait1_0_IASA,
        ftCh_Wait1_0_Phys,
        ftCh_Wait1_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Entry = 343
        ftMh_SM_Entry,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Entry_Anim,
        ftCh_Entry_IASA,
        ftCh_Entry_Phys,
        ftCh_Entry_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Damage = 344
        ftMh_SM_Damage,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Damage_Anim,
        ftCh_Damage_IASA,
        ftCh_Damage_Phys,
        ftCh_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Damage2 = 345
        ftMh_SM_Damage2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Damage2_Anim,
        ftCh_Damage2_IASA,
        ftCh_Damage2_Phys,
        ftCh_Damage2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WaitSweep = 346
        ftMh_SM_WaitSweep,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_WaitSweep_Anim,
        ftCh_WaitSweep_IASA,
        ftCh_WaitSweep_Phys,
        ftCh_WaitSweep_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_SweepLoop = 347
        ftMh_SM_SweepLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_SweepLoop_Anim,
        ftCh_SweepLoop_IASA,
        ftCh_SweepLoop_Phys,
        ftCh_SweepLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_SweepWait = 348
        ftMh_SM_SweepWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_SweepWait_Anim,
        ftCh_SweepWait_IASA,
        ftCh_SweepWait_Phys,
        ftCh_SweepWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Slap = 349
        ftMh_SM_Slap,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Slap_Anim,
        ftCh_Slap_IASA,
        ftCh_Slap_Phys,
        ftCh_Slap_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Walk2 = 350
        ftMh_SM_Walk2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Walk2_Anim,
        ftCh_Walk2_IASA,
        ftCh_Walk2_Phys,
        ftCh_Slap_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkLoop = 351
        ftMh_SM_WalkLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_WalkLoop_Anim,
        ftCh_WalkLoop_IASA,
        ftCh_WalkLoop_Phys,
        ftCh_WalkLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkWait = 352
        ftMh_SM_WalkWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_WalkWait_Anim,
        ftCh_WalkWait_IASA,
        ftCh_WalkWait_Phys,
        ftCh_WalkWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_WalkShoot = 353
        ftMh_SM_WalkShoot,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_WalkShoot_Anim,
        ftCh_WalkShoot_IASA,
        ftCh_WalkShoot_Phys,
        ftCh_WalkShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Drill = 354
        ftMh_SM_Drill,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Drill_Anim,
        ftCh_Drill_IASA,
        ftCh_Drill_Phys,
        ftCh_Drill_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushUp = 355
        ftMh_SM_RockCrushUp,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_RockCrushUp_Anim,
        ftCh_RockCrushUp_IASA,
        ftCh_RockCrushUp_Phys,
        ftCh_RockCrushUp_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushWait = 356
        ftMh_SM_RockCrushWait,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_RockCrushWait_Anim,
        ftCh_RockCrushUp_IASA,
        ftCh_RockCrushUp_Phys,
        ftCh_RockCrushUp_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_RockCrushDown = 357
        ftMh_SM_RockCrushDown,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_RockCrushDown_Anim,
        ftCh_RockCrushDown_IASA,
        ftCh_RockCrushDown_Phys,
        ftCh_RockCrushDown_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_PaperCrush = 358
        ftMh_SM_PaperCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_PaperCrush_Anim,
        ftCh_PaperCrush_IASA,
        ftCh_PaperCrush_Phys,
        ftCh_PaperCrush_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Poke1 = 359
        ftMh_SM_Poke1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Poke1_Anim,
        ftCh_Poke1_IASA,
        ftCh_Poke1_Phys,
        ftCh_Poke1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Poke2 = 360
        ftMh_SM_Poke2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Poke2_Anim,
        ftCh_Poke2_IASA,
        ftCh_Poke2_Phys,
        ftCh_Poke2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamStart = 361
        ftMh_SM_FingerBeamStart,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_FingerBeamStart_Anim,
        ftCh_FingerBeamStart_IASA,
        ftCh_FingerBeamStart_Phys,
        ftCh_FingerBeamStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamLoop = 362
        ftMh_SM_FingerBeamLoop,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_FingerBeamLoop_Anim,
        ftCh_FingerBeamLoop_IASA,
        ftCh_FingerBeamLoop_Phys,
        ftCh_FingerBeamLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerBeamEnd = 363
        ftMh_SM_FingerBeamEnd,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_FingerBeamEnd_Anim,
        ftCh_FingerBeamEnd_IASA,
        ftCh_FingerBeamEnd_Phys,
        ftCh_FingerBeamEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun1 = 364
        ftMh_SM_FingerGun1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_FingerGun1_Anim,
        ftCh_FingerGun1_IASA,
        ftCh_FingerGun1_Phys,
        ftCh_FingerGun1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun2 = 365
        ftMh_SM_FingerGun2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_FingerGun2_Anim,
        ftCh_FingerGun2_IASA,
        ftCh_FingerGun2_Phys,
        ftCh_FingerGun2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_FingerGun3 = 366
        ftMh_SM_FingerGun3,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_FingerGun2_Anim,
        ftCh_FingerGun2_IASA,
        ftCh_FingerGun2_Phys,
        ftCh_FingerGun2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane1 = 367
        ftMh_SM_BackAirplane1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_BackAirplane1_Anim,
        ftCh_BackAirplane1_IASA,
        ftCh_BackAirplane1_Phys,
        ftCh_BackAirplane1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane2 = 368
        ftMh_SM_BackAirplane2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_BackAirplane2_Anim,
        ftCh_BackAirplane2_IASA,
        ftCh_BackAirplane2_Phys,
        ftCh_BackAirplane2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackAirplane3 = 369
        ftMh_SM_BackAirplane3,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_BackAirplane3_Anim,
        ftCh_BackAirplane3_IASA,
        ftCh_BackAirplane3_Phys,
        ftCh_BackAirplane3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackPunch = 370
        ftMh_SM_BackPunch,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_BackPunch_Anim,
        ftCh_BackPunch_IASA,
        ftCh_BackPunch_Phys,
        ftCh_BackPunch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackCrush = 371
        ftMh_SM_BackCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_BackCrush_Anim,
        ftCh_BackCrush_IASA,
        ftCh_BackCrush_Phys,
        ftCh_BackCrush_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_BackDisappear = 372
        ftMh_SM_BackDisappear,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_BackDisappear_Anim,
        ftCh_BackDisappear_IASA,
        ftCh_BackDisappear_Phys,
        ftCh_BackDisappear_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait1_1 = 373
        ftMh_SM_Wait1_1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Wait1_1_Anim,
        ftCh_Wait1_1_IASA,
        ftCh_Wait1_1_Phys,
        ftCh_Wait1_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Grab = 374
        ftMh_SM_Grab,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Grab_Anim,
        ftCh_Grab_IASA,
        ftCh_Grab_Phys,
        ftCh_Grab_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Cancel = 375
        ftMh_SM_Cancel,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Cancel_Anim,
        ftCh_Cancel_IASA,
        ftCh_Cancel_Phys,
        ftCh_Cancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeezing0 = 376
        ftMh_SM_Squeezing0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Squeezing0_Anim,
        ftCh_Squeezing0_IASA,
        ftCh_Squeezing0_Phys,
        ftCh_Squeezing0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeezing1 = 377
        ftMh_SM_Squeezing1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Squeezing1_Anim,
        ftCh_Squeezing1_IASA,
        ftCh_Squeezing1_Phys,
        ftCh_Squeezing1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Squeeze = 378
        ftMh_SM_Squeeze,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Squeeze_Anim,
        ftCh_Squeeze_IASA,
        ftCh_Squeeze_Phys,
        ftCh_Squeeze_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Throw = 379
        ftMh_SM_Throw,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Throw_Anim,
        ftCh_Throw_IASA,
        ftCh_Throw_Phys,
        ftCh_Throw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Slam = 380
        ftMh_SM_Slam,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Slam_Anim,
        ftCh_Slam_IASA,
        ftCh_Slam_Phys,
        ftCh_Slam_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Fail = 381
        ftMh_SM_Fail,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_Fail_Anim,
        ftCh_Fail_IASA,
        ftCh_Fail_Phys,
        ftCh_Fail_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagCrush = 382
        ftMh_SM_TagCrush,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_TagCrush_Anim,
        ftCh_TagCrush_IASA,
        ftCh_TagCrush_Phys,
        ftCh_TagCrush_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagApplaud = 383
        ftMh_SM_TagApplaud,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_TagApplaud_Anim,
        ftCh_TagApplaud_IASA,
        ftCh_TagApplaud_Phys,
        ftCh_TagApplaud_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagRockPaper = 384
        ftMh_SM_TagRockPaper,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_TagRockPaper_Anim,
        ftCh_TagRockPaper_IASA,
        ftCh_TagRockPaper_Phys,
        ftCh_TagRockPaper_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagGrab = 385
        ftMh_SM_TagGrab,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_TagGrab_Anim,
        ftCh_TagGrab_IASA,
        ftCh_TagGrab_Phys,
        ftCh_TagGrab_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagSqueeze = 386
        ftMh_SM_TagSqueeze,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_TagSqueeze_Anim,
        ftCh_TagGrab_IASA,
        ftCh_TagGrab_Phys,
        ftCh_TagGrab_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagFail = 387
        ftMh_SM_TagFail,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_TagFail_Anim,
        ftCh_TagFail_IASA,
        ftCh_TagFail_Phys,
        ftCh_TagFail_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_TagCancel = 388
        ftMh_SM_TagCancel,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_TagCancel_Anim,
        NULL,
        ftCh_TagCancel_Phys,
        ftCh_TagCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMh_MS_Wait1_2 = 389
        ftMh_SM_Wait1_2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCh_TagCancel_Anim,
        NULL,
        ftCh_TagCancel_Phys,
        ftCh_TagCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftCh_Init_DatFilename[] = "PlCh.dat";
char ftCh_Init_DataName[] = "ftDataCrazyhand";
char ftCh_Init_803D4834[] = "PlChNr.dat";
char ftCh_Init_803D4840[] = "PlyCrazyhand_Share_joint";
char ftCh_Init_AnimDatFilename[] = "PlChAJ.dat";

Fighter_CostumeStrings ftCh_Init_CostumeStrings[] = {
    { ftCh_Init_803D4834, ftCh_Init_803D4840, NULL },
};

jtbl_t ftCh_Init_803D4900 = {
    ftCh_Init_801566B4, ftCh_Init_80156A5C, ftCh_Init_80156688,
    ftCh_Init_80156A5C, ftCh_Init_801566E0, ftCh_Init_80156A5C,
    ftCh_Init_80156710, ftCh_Init_80156A5C, ftCh_Init_80156740,
    ftCh_Init_80156A5C, ftCh_Init_80156A5C, ftCh_Init_80156770,
    ftCh_Init_801567A0, ftCh_Init_80156A5C, ftCh_Init_801567AC,
    ftCh_Init_80156A5C, ftCh_Init_801567DC, ftCh_Init_80156A5C,
    ftCh_Init_8015683C, ftCh_Init_80156A5C, ftCh_Init_80156A5C,
    ftCh_Init_80156A5C, ftCh_Init_80156A5C, ftCh_Init_80156A5C,
    ftCh_Init_80156A5C, ftCh_Init_8015686C, ftCh_Init_80156878,
    ftCh_Init_80156A5C, ftCh_Init_80156A5C, ftCh_Init_80156884,
    ftCh_Init_80156898, ftCh_Init_801568AC, ftCh_Init_80156A5C,
    ftCh_Init_80156A5C, ftCh_Init_801568B8, ftCh_Init_801568E8,
    ftCh_Init_80156918, ftCh_Init_80156948,
};

/* static */ void ftCh_GrabUnk1_8015B2FC(void);
/* static */ void ftCh_GrabUnk1_8015B35C(void);
/* static */ void ftCh_GrabUnk1_8015B390(void);
/* static */ void ftCh_GrabUnk1_8015B3B8(void);
/* static */ void ftCh_GrabUnk1_8015B3EC(void);
/* static */ void ftCh_GrabUnk1_8015B404(void);
/* static */ void ftCh_GrabUnk1_8015B43C(void);
/* static */ void ftCh_GrabUnk1_8015B46C(void);
/* static */ void ftCh_GrabUnk1_8015B4AC(void);
/* static */ void ftCh_GrabUnk1_8015B4BC(void);

jtbl_t ftCh_Init_803D4998 = {
    ftCh_GrabUnk1_8015B2FC, ftCh_GrabUnk1_8015B35C, ftCh_GrabUnk1_8015B390,
    ftCh_GrabUnk1_8015B3B8, ftCh_GrabUnk1_8015B3EC, ftCh_GrabUnk1_8015B404,
    ftCh_GrabUnk1_8015B43C, ftCh_GrabUnk1_8015B46C, ftCh_GrabUnk1_8015B4AC,
    ftCh_GrabUnk1_8015B4BC,
};

void ftCh_Init_OnDeath(HSD_GObj* gobj) {}

void ftCh_Init_OnLoad(HSD_GObj* gobj)
{
    ftData* ftdata;
    ftCrazyHand_DatAttrs* ftData_attr;
    void** items;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftdata = fp->ft_data;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(fp, ftCrazyHand_DatAttrs);

    ftBossLib_8015BDB4(gobj);
    it_8026B3F8(items[0], 127);
    it_8026B3F8(items[1], 128);
    it_8026B3F8(items[2], 129);
    fp->no_normal_motion = 1;
    fp->x2229_b6 = 1;
    fp->no_kb = 1;
    fp->x222A_b0 = 1;
    fp->x222A_b1 = 1;
    fp->x2229_b3 = 1;
    fp->cur_pos.x = ftData_attr->x18;
    fp->cur_pos.y = ftData_attr->x1C;
    fp->cur_pos.z = 0.0f;
    fp->mv.ch.unk0.x28 = 0;
    fp->mv.ch.unk0.x2C = 0;
    fp->mv.ch.unk0.x30 = 0;
    fp->mv.ch.unk0.x34 = 0;
    fp->mv.ch.unk0.x38 = -1;
    fp->mv.ch.unk0.x3C = -1;
    fp->mv.ch.unk0.x40 = -1;
    fp->mv.ch.unk0.x1C = 0.0f;
    fp->mv.ch.unk0.x20 = 0;
    fp->fv.ch.x222C = ftBossLib_8015C244(gobj, &fp->cur_pos);
    fp->fv.ch.x2238 = 1.0f;
    fp->fv.ch.x224C = 0;
    fp->fv.ch.x2250 = ftMh_MS_Damage2;
    fp->fv.ch.x2254 = 0;
    fp->x1A88.level = 1;
    ftBossLib_8015BD24(fp->x1A88.level, &fp->fv.mh.x223C, fp->fv.ch.x2238,
                       ftData_attr->x0, ftData_attr->x8, ftData_attr->x4);
}

void ftCh_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCrazyHand_DatAttrs);
}

void ftCh_Init_80155FCC(HSD_GObj* gobj)
{
    if (Stage_80225194() == 0xFB) {
        ftCh_Init_80156310(gobj);
    } else {
        ftCh_GrabUnk1_8015B174(gobj);
    }
}

void ftCh_Init_80156014(HSD_GObj* gobj) {}

/// #ftCh_Init_80156018

/// #ftCh_Init_801560D8

/// #ftCh_Init_80156198

/// #ftCh_Init_80156310

/// #ftCh_Wait1_0_Anim

void ftCh_Wait1_0_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Wait1_0_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Wait1_0_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_80156AD8

/// #fn_80156F6C

void ftCh_Entry_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Entry_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Entry_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Entry_Coll(HSD_GObj* gobj) {}

void fn_80157080(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x158, 0, ftCh_Init_804DA070,
                              ftCh_Init_804DA074, ftCh_Init_804DA070, NULL);
    ftAnim_8006EBA4(gobj);
}
void ftCh_Damage_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_80157170(gobj);
    }
}

void ftCh_Damage_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Damage_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Damage_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_80157170

/// #ftCh_Damage2_Anim

void ftCh_Damage2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Damage2_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* attrs = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18,
                       attrs->x14, attrs->x10);
}

void ftCh_Damage2_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015737C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WaitSweep, 0, ftCh_Init_804DA070,
                              ftCh_Init_804DA074, ftCh_Init_804DA070, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WaitSweep_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_WaitSweep_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WaitSweep_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WaitSweep_Coll(HSD_GObj* gobj) {}

static void fn_8015746C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_SweepLoop, 0, ftCh_Init_804DA070,
                              ftCh_Init_804DA074, ftCh_Init_804DA070, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_SweepLoop_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_SweepLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_SweepLoop_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_SweepLoop_Coll(HSD_GObj* gobj) {}

static void fn_8015755C(HSD_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftMh_MS_SweepWait, 0, ftCh_Init_804DA080,
                              ftCh_Init_804DA084, ftCh_Init_804DA080, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_SweepWait_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_8015764C(gobj);
    }
}

void ftCh_SweepWait_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_SweepWait_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_SweepWait_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_8015764C

/// #ftCh_Slap_Anim

void ftCh_Slap_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_Slap_Phys

/// #fn_801577B4

void ftCh_Init_801577F8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Walk2, 0, ftCh_Init_804DA070,
                              ftCh_Init_804DA074, ftCh_Init_804DA070, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Walk2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Walk2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Walk2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Slap_Coll(HSD_GObj* gobj) {}

static void fn_801578E8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkLoop, 0, ftCh_Init_804DA070,
                              ftCh_Init_804DA074, ftCh_Init_804DA070, NULL);
    ftAnim_8006EBA4(gobj);
}

/// #ftCh_WalkLoop_Anim

void ftCh_WalkLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WalkLoop_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WalkLoop_Coll(HSD_GObj* gobj) {}

void ftCh_Init_801579F4(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkWait, 0, ftCh_Init_804DA070,
                              ftCh_Init_804DA074, ftCh_Init_804DA070, NULL);
    ftAnim_8006EBA4(gobj);
}

/// #ftCh_WalkWait_Anim

void ftCh_WalkWait_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_WalkWait_Phys

void ftCh_WalkWait_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80157B58(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = 0;
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkShoot, 0, 0, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WalkShoot_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_WalkShoot_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WalkShoot_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WalkShoot_Coll(HSD_GObj* gobj) {}

/// #fn_80157C50

void ftCh_Drill_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Drill_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_Drill_Phys

void ftCh_Drill_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_80157DF8

/// #ftCh_RockCrushUp_Anim

void ftCh_RockCrushWait_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_RockCrushUp_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_RockCrushUp_Phys

void ftCh_RockCrushUp_Coll(HSD_GObj* gobj) {}

/// #fn_80158144

void ftCh_RockCrushDown_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_RockCrushDown_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_RockCrushDown_Phys

void ftCh_RockCrushDown_Coll(HSD_GObj* gobj) {}

/// #fn_801582D8

void ftCh_PaperCrush_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_801583E4(gobj);
    }
}

void ftCh_PaperCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_PaperCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_PaperCrush_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_801583E4

/// #ftCh_Poke1_Anim

void ftCh_Poke1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Poke1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Poke1_Coll(HSD_GObj* gobj) {}

/// #fn_80158534

/// #ftCh_Init_8015868C

void ftCh_Poke2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Poke2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Poke2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Poke2_Coll(HSD_GObj* gobj) {}

/// #fn_801587B0

void ftCh_FingerBeamStart_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_FingerBeamStart_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerBeamStart_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_FingerBeamStart_Coll(HSD_GObj* gobj) {}

/// #fn_801588B8

void ftCh_Init_80158B3C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x16A, 0, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
    ftAnim_SetAnimRate(gobj, da->xCC_pos.x);
    fp->mv.mh.unk0.x8 = da->xC4_pos.y;
}

/// #ftCh_FingerBeamLoop_Anim

void ftCh_FingerBeamLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_FingerBeamLoop_Phys

void ftCh_FingerBeamLoop_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80158DFC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x16B, 0, 0, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2D0(fp, 0x100, fn_80159288, NULL, fn_8015B548);
    fp->mv.mh.unk0.x20 = 0;
}

/// #ftCh_FingerBeamEnd_Anim

void ftCh_FingerBeamEnd_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerBeamEnd_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_FingerBeamEnd_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_80158F34

void ftCh_BackPunch_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_BackPunch_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackPunch_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_BackPunch_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_80159098

/// #ftCh_FingerGun1_Anim

void ftCh_FingerGun1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerGun1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_FingerGun1_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    }
}

/// #fn_80159288

/// #ftCh_Init_801592D4

/// #ftCh_BackAirplane1_Anim

void ftCh_BackAirplane1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackAirplane1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_BackAirplane1_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    }
}

/// #ftCh_Init_801594D4

/// #ftCh_BackAirplane2_Anim

void ftCh_BackAirplane2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackAirplane2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_BackAirplane2_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_80159670

/// #ftCh_BackAirplane3_Anim

void ftCh_BackAirplane3_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackAirplane3_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_BackAirplane3_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_801597F0

void ftCh_BackCrush_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.ch.unk0.x4(gobj);
    }
}
void ftCh_BackCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_BackCrush_Coll(HSD_GObj* gobj) {}

/// #fn_80159908

void ftCh_BackDisappear_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0.0f;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}
void ftCh_BackDisappear_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_BackDisappear_Phys

void ftCh_BackDisappear_Coll(HSD_GObj* gobj) {}

/// #fn_80159AA4

/// #ftCh_Wait1_1_Anim

void ftCh_Wait1_1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_Wait1_1_Phys

void ftCh_Wait1_1_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80159F40(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Grab, 0, ftCh_Init_804DA070,
                              ftCh_Init_804DA074, ftCh_Init_804DA070, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Grab_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_8015A030(gobj);
    }
}

void ftCh_Grab_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Grab_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Grab_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_8015A030

void ftCh_Cancel_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0.0f;
        ftCh_Init_8015A184(gobj);
    }
}
void ftCh_Cancel_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Cancel_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ftBossLib_8015BF74(gobj, da->xDC);
}

void ftCh_Cancel_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_8015A184

void ftCh_Squeezing0_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Squeezing0_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Squeezing0_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Squeezing0_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_8015A2B0

void ftCh_Squeezing1_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C2E0() || ftBossLib_8015C358() ||
        !ftAnim_IsFramesRemaining(gobj))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Squeezing1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Squeezing1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Squeezing1_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_8015A3F4

void ftCh_Squeeze_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }

    if ((ftBossLib_8015C2E0() != 0) || (ftBossLib_8015C358() != 0) ||
        (!ftAnim_IsFramesRemaining(gobj)))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Squeeze_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Squeeze_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Squeeze_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_8015A560

void ftCh_Throw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }

    if ((ftBossLib_8015C2E0() != 0) || (ftBossLib_8015C358() != 0) ||
        (!ftAnim_IsFramesRemaining(gobj)))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Throw_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Throw_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Throw_Coll(HSD_GObj* gobj) {}

/// #ftCh_Slam_Anim

void ftCh_Slam_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Slam_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Slam_Coll(HSD_GObj* gobj) {}

/// #ftCh_Fail_Anim

void ftCh_Fail_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Fail_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Fail_Coll(HSD_GObj* gobj) {}

void ftCh_GrabUnk1_8015A888(HSD_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x17E, 0, ftCh_Init_804DA178,
                              ftCh_Init_804DA17C, ftCh_Init_804DA178, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_TagCrush_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_TagCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_TagCrush_Coll(HSD_GObj* gobj) {}

/// #ftCh_TagApplaud_Anim

void ftCh_TagApplaud_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagApplaud_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_TagApplaud_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    }
}

void fn_8015AAC8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x180, 0, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
}

/// #ftCh_TagRockPaper_Anim

void ftCh_TagRockPaper_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagRockPaper_Phys(HSD_GObj* gobj) {}

void ftCh_TagRockPaper_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015ABD0

/// #ftCh_GrabUnk1_8015AC50

void ftCh_FingerGun2_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp->mv.mh.unk0.x20 == 1) {
            ftCh_Init_801592D4(gobj);
        } else {
            ftCh_Init_80158F34(gobj);
        }
    }
}

void ftCh_FingerGun2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerGun2_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_FingerGun2_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015ADD0

/// #ftCh_TagGrab_Anim

/// #ftCh_TagSqueeze_Anim

void ftCh_TagGrab_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagGrab_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    fp->self_vel.y += da->x12C_pos.y;
    fp->self_vel.z += da->x134_pos.y;
}

void ftCh_TagGrab_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015B174

void ftCh_TagFail_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_TagFail_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagFail_Phys(HSD_GObj* gobj) {}

void ftCh_TagFail_Coll(HSD_GObj* gobj) {}

/// #fn_8015B2C0

/// #fn_8015B4EC

/// #fn_8015B548

void ftCo_CaptureCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015B670

/// #ftCo_CaptureDamageCrazyHand_Anim

void ftCo_CaptureDamageCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureDamageCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureDamageCrazyHand_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015B778

void ftCh_GrabUnk1_8015B800(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->invisible = false;
    fp->facing_dir = -fp->facing_dir;
    ftCo_CaptureCut_Enter(gobj);
}

void ftCo_CaptureWaitCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015B850

void ftCo_ThrownCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015B8FC

/// #ftCh_GrabUnk1_8015B998

/// #ftCh_GrabUnk1_8015BA34

void ftCh_TagCancel_Anim(HSD_GObj* gobj)
{
    u8 _[4];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->fv.mh.x2258 = ftMh_MS_TagCancel;
        Fighter_ChangeMotionState(gobj, ftMh_MS_TagCancel, 0, 0, 1.0f, 0.0f,
                                  NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_TagCancel_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_TagCancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
        if (fp->mv.mh.unk0.x4) {
            fp->mv.mh.unk0.x4(gobj);
        }
    }
}

/// #ftCh_GrabUnk1_8015BC88

struct {
    enum_t asids[18];
    s8 bytes[64];
} ftCh_Init_803D4878 = {
    { ftMh_MS_Entry, ftMh_MS_Damage2, ftMh_MS_SweepLoop, ftMh_MS_Slap,
      ftMh_MS_WalkLoop, ftMh_MS_Drill, ftMh_MS_RockCrushUp,
      ftMh_MS_RockCrushDown, ftMh_MS_BackDisappear, ftMh_MS_Wait1_1,
      ftMh_MS_Grab, ftMh_MS_Poke1, ftMh_MS_FingerBeamStart,
      ftMh_MS_BackAirplane2, ftMh_MS_BackAirplane3, ftMh_MS_Squeezing1,
      ftMh_MS_Squeeze, ftMh_MS_Throw },
    { 0,  1,  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
      16, 17, 0, 0, 0, 4, 4, 4, 8, 3, 11, 2,  13, 2,  15, 3,
      1,  2,  3, 4, 5, 0, 2, 3, 4, 5, 0,  1,  3,  4,  5,  0,
      1,  2,  4, 5, 0, 1, 2, 3, 5, 0, 1,  2,  3,  4,  0,  0 },
};
