#include "ftKb_Init.static.h"

#include "types.h"

#include <placeholder.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Jump.h"
#include "ft/chara/ftCommon/ftCo_KneeBend.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ftcamera.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureKirby.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"

#include "ftKirby/forward.h"

#include "it/it_26B1.h"
#include "it/items/it_2F28.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itkirby_2F23.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itkirbyhammer.h"
#include "it/items/itnesspkflush.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "lb/lb_00B0.h"
#include "lb/lbanim.h"
#include "lb/lbvector.h"
#include "melee/lb/lbrefract.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

void ftAnim_80070458_proto(Fighter* fp, CostumeTObjList*, int);

MotionState ftKb_Init_MotionStateTable[ftKb_MS_SelfCount] = {
    {
        // ftKb_MS_JumpAerialF1 = 341
        ftKb_SM_JumpAerialF1,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF2 = 342
        ftKb_SM_JumpAerialF2,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF3 = 343
        ftKb_SM_JumpAerialF3,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF4 = 344
        ftKb_SM_JumpAerialF4,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF5 = 345
        ftKb_SM_JumpAerialF5,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF1Met = 346
        ftKb_SM_JumpAerialF1Met,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF2Met = 347
        ftKb_SM_JumpAerialF2Met,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF3Met = 348
        ftKb_SM_JumpAerialF3Met,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF4Met = 349
        ftKb_SM_JumpAerialF4Met,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_JumpAerialF5Met = 350
        ftKb_SM_JumpAerialF5Met,
        ftKb_MF_MultiJump,
        FtMoveId_Default << 24,
        ftCo_JumpAerialF1_Anim,
        ftCo_JumpAerialF1_IASA,
        ftCo_JumpAerialF1_Phys,
        ftCo_JumpAerialF1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_AttackDash = 351
        ftCo_SM_AttackDash,
        ftKb_MF_AttackDash,
        FtMoveId_AttackDash << 24,
        ftKb_AttackDash_Anim,
        ftKb_AttackDash_IASA,
        ftKb_AttackDash_Phys,
        ftKb_AttackDash_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_AttackDashAir = 352
        ftCo_SM_AttackDash,
        ftKb_MF_AttackDashAir,
        FtMoveId_AttackDash << 24,
        ftKb_AttackDashAir_Anim,
        ftKb_AttackDashAir_IASA,
        ftKb_AttackDashAir_Phys,
        ftKb_AttackDashAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialN = 353
        ftKb_SM_SpecialN,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialN_Anim,
        NULL,
        ftKb_SpecialN_Phys,
        ftKb_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialNLoop = 354
        ftKb_SM_SpecialNLoop,
        ftKb_MF_SpecialNLoop,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNLoop_Anim,
        ftKb_SpecialNLoop_IASA,
        ftKb_SpecialNLoop_Phys,
        ftKb_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialNEnd = 355
        ftKb_SM_SpecialNEnd,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNEnd_Anim,
        NULL,
        ftKb_SpecialNEnd_Phys,
        ftKb_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialNCapture0 = 356
        ftKb_SM_SpecialNCapture,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNCapture_Anim,
        NULL,
        ftKb_SpecialNCapture_Phys,
        ftKb_SpecialNCapture_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialNCapture1 = 357
        ftKb_SM_SpecialNCapture,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNCapture0_Anim,
        NULL,
        ftKb_SpecialNCapture0_Phys,
        ftKb_SpecialNCapture0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_Eat = 358
        ftKb_SM_Eat,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_Eat_Anim,
        NULL,
        ftKb_Eat_Phys,
        ftKb_Eat_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatWait = 359
        ftKb_SM_EatWait,
        ftKb_MF_SpecialN,
        0x12400000,
        ftKb_EatWait_Anim,
        ftKb_EatWait_IASA,
        ftKb_EatWait_Phys,
        ftKb_EatWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatWalkSlow = 360
        ftKb_SM_EatWalkSlow,
        ftKb_MF_SpecialNCaptureWalk,
        FtMoveId_SpecialN << 24,
        ftKb_EatWalk_Anim,
        ftKb_EatWalk_IASA,
        ftKb_EatWalk_Phys,
        ftKb_EatWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatWalkMiddle = 361
        ftKb_SM_EatWalkMiddle,
        ftKb_MF_SpecialNCaptureWalk,
        FtMoveId_SpecialN << 24,
        ftKb_EatWalk_Anim,
        ftKb_EatWalk_IASA,
        ftKb_EatWalk_Phys,
        ftKb_EatWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatWalkFast = 362
        ftKb_SM_EatWalkFast,
        ftKb_MF_SpecialNCaptureWalk,
        FtMoveId_SpecialN << 24,
        ftKb_EatWalk_Anim,
        ftKb_EatWalk_IASA,
        ftKb_EatWalk_Phys,
        ftKb_EatWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatTurn = 363
        ftKb_SM_EatTurn,
        ftKb_MF_SpecialNCaptureTurn,
        FtMoveId_SpecialN << 24,
        ftKb_EatTurn_Anim,
        NULL,
        ftKb_EatTurn_Phys,
        ftKb_EatTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatJump1 = 364
        ftKb_SM_EatJump1,
        ftKb_MF_SpecialNCaptureJumpSquat,
        FtMoveId_SpecialN << 24,
        ftKb_EatJump1_Anim,
        ftKb_EatJump1_IASA,
        ftKb_EatJump1_Phys,
        ftKb_EatJump1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatJump2 = 365
        ftKb_SM_EatJump2,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_EatJump2_Anim,
        NULL,
        ftKb_EatJump2_Phys,
        ftKb_EatJump2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatLanding = 366
        ftKb_SM_EatLanding,
        ftKb_MF_SpecialN,
        0x12400000,
        ftKb_EatLanding_Anim,
        NULL,
        ftKb_EatLanding_Phys,
        ftKb_EatLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialNDrink0 = 367
        ftKb_SM_SpecialNDrink,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNDrink_Anim,
        NULL,
        ftKb_SpecialNDrink_Phys,
        ftKb_SpecialNDrink_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialNDrink1 = 368
        ftKb_SM_SpecialNDrink,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNDrink0_Anim,
        NULL,
        ftKb_SpecialNDrink0_Phys,
        ftKb_SpecialNDrink0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialNSpit0 = 369
        ftKb_SM_SpecialNSpit,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNSpit_Anim,
        NULL,
        ftKb_SpecialNSpit_Phys,
        ftKb_SpecialNSpit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialNSpit1 = 370
        ftKb_SM_SpecialNSpit,
        ftKb_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNSpit0_Anim,
        NULL,
        ftKb_SpecialNSpit0_Phys,
        ftKb_SpecialNSpit0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirN = 371
        ftKb_SM_SpecialAirN,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirN_Anim,
        NULL,
        ftKb_SpecialAirN_Phys,
        ftKb_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirNLoop = 372
        ftKb_SM_SpecialAirNLoop,
        ftKb_MF_SpecialAirNLoop,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirNLoop_Anim,
        ftKb_SpecialAirNLoop_IASA,
        ftKb_SpecialAirNLoop_Phys,
        ftKb_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirNEnd = 373
        ftKb_SM_SpecialNEnd,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirNEnd_Anim,
        NULL,
        ftKb_SpecialAirNEnd_Phys,
        ftKb_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirNCapture0 = 374
        ftKb_SM_SpecialNCapture,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirNCapture_Anim,
        NULL,
        ftKb_SpecialAirNCapture_Phys,
        ftKb_SpecialAirNCapture_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirNCapture1 = 375
        ftKb_SM_SpecialNCapture,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNCapture1_Anim,
        NULL,
        ftKb_SpecialNCapture1_Phys,
        ftKb_SpecialNCapture1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatAir = 376
        ftKb_SM_Eat,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirNCaptured_Anim,
        NULL,
        ftKb_SpecialAirNCaptured_Phys,
        ftKb_SpecialAirNCaptured_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatFall = 377
        ftKb_SM_EatWait,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirNCaptureWait_Anim,
        ftKb_SpecialAirNCaptureWait_IASA,
        ftKb_SpecialAirNCaptureWait_Phys,
        ftKb_SpecialAirNCaptureWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirNDrink0 = 378
        ftKb_SM_SpecialNDrink,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirNDrink_Anim,
        NULL,
        ftKb_SpecialAirNDrink_Phys,
        ftKb_SpecialAirNDrink_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirNDrink1 = 379
        ftKb_SM_SpecialNDrink,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNDrink1_Anim,
        NULL,
        ftKb_SpecialNDrink1_Phys,
        ftKb_SpecialNDrink1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirNSpit0 = 380
        ftKb_SM_SpecialNSpit,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirNSpit_Anim,
        NULL,
        ftKb_SpecialAirNSpit_Phys,
        ftKb_SpecialAirNSpit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirNSpit1 = 381
        ftKb_SM_SpecialNSpit,
        ftKb_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialNSpit1_Anim,
        NULL,
        ftKb_SpecialNSpit1_Phys,
        ftKb_SpecialNSpit1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_EatTurnAir = 382
        ftKb_SM_EatTurn,
        ftKb_MF_SpecialAirNCaptureTurn,
        FtMoveId_SpecialN << 24,
        ftKb_SpecialAirNCaptureTurn_Anim,
        NULL,
        ftKb_SpecialAirNCaptureTurn_Phys,
        ftKb_SpecialAirNCaptureTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialS = 383
        ftKb_SM_SpecialS,
        ftKb_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftKb_SpecialS_Anim,
        NULL,
        ftKb_SpecialS_Phys,
        ftKb_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirS = 384
        ftKb_SM_SpecialAirS,
        ftKb_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftKb_SpecialAirS_Anim,
        NULL,
        ftKb_SpecialAirS_Phys,
        ftKb_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialHi1 = 385
        ftKb_SM_SpecialHi1,
        ftKb_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftKb_SpecialHi1_Anim,
        ftKb_SpecialHi1_IASA,
        ftKb_SpecialHi1_Phys,
        ftKb_SpecialHi1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialHi2 = 386
        ftKb_SM_SpecialHi2,
        ftKb_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftKb_SpecialHi2_Anim,
        ftKb_SpecialHi2_IASA,
        ftKb_SpecialHi2_Phys,
        ftKb_SpecialHi2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialHi3 = 387
        ftKb_SM_SpecialHi3,
        ftKb_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftKb_SpecialHi3_Anim,
        ftKb_SpecialHi3_IASA,
        ftKb_SpecialHi3_Phys,
        ftKb_SpecialHi3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialHi4 = 388
        ftKb_SM_SpecialHi4,
        ftKb_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftKb_SpecialHi4_Anim,
        ftKb_SpecialHi4_IASA,
        ftKb_SpecialHi4_Phys,
        ftKb_SpecialHi4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirHi1 = 389
        ftKb_SM_SpecialAirHi1,
        ftKb_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftKb_SpecialAirHi1_Anim,
        ftKb_SpecialAirHi1_IASA,
        ftKb_SpecialAirHi1_Phys,
        ftKb_SpecialAirHi1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirHi2 = 390
        ftKb_SM_SpecialAirHi2,
        ftKb_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftKb_SpecialAirHi2_Anim,
        ftKb_SpecialAirHi2_IASA,
        ftKb_SpecialAirHi2_Phys,
        ftKb_SpecialAirHi2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirHi3 = 391
        ftKb_SM_SpecialAirHi3,
        ftKb_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftKb_SpecialAirHi3_Anim,
        ftKb_SpecialAirHi3_IASA,
        ftKb_SpecialAirHi3_Phys,
        ftKb_SpecialAirHi3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirHi4 = 392
        ftKb_SM_SpecialAirHiEnd,
        ftKb_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftKb_SpecialAirHiEnd_Anim,
        ftKb_SpecialAirHiEnd_IASA,
        ftKb_SpecialAirHiEnd_Phys,
        ftKb_SpecialAirHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialLw1 = 393
        ftKb_SM_SpecialLw1,
        ftKb_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftKb_SpecialLw1_Anim,
        ftKb_SpecialLw1_IASA,
        ftKb_SpecialLw1_Phys,
        ftKb_SpecialLw1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialLw = 394
        ftKb_SM_SpecialLw,
        ftKb_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftKb_SpecialLw_Anim,
        ftKb_SpecialLw_IASA,
        ftKb_SpecialLw_Phys,
        ftKb_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialLwEnd = 395
        ftKb_SM_SpecialLwEnd,
        ftKb_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftKb_SpecialLwEnd_Anim,
        ftKb_SpecialLwEnd_IASA,
        ftKb_SpecialLwEnd_Phys,
        ftKb_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirLwStart = 396
        ftKb_SM_SpecialAirLwStart,
        ftKb_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftKb_SpecialAirLwStart_Anim,
        ftKb_SpecialAirLwStart_IASA,
        ftKb_SpecialAirLwStart_Phys,
        ftKb_SpecialAirLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirLw = 397
        ftKb_SM_SpecialAirLw,
        ftKb_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftKb_SpecialAirLw_Anim,
        ftKb_SpecialAirLw_IASA,
        ftKb_SpecialAirLw_Phys,
        ftKb_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SpecialAirLwEnd = 398
        ftKb_SM_SpecialAirLwEnd,
        ftKb_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftKb_SpecialAirLwEnd_Anim,
        ftKb_SpecialAirLwEnd_IASA,
        ftKb_SpecialAirLwEnd_Phys,
        ftKb_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MrSpecialN = 399
        ftKb_SM_MrSpecialN,
        ftKb_MF_SpecialNMr,
        FtMoveId_KbSpecialNMr << 24,
        ftKb_MrSpecialN_Anim,
        ftKb_MrSpecialN_IASA,
        ftKb_MrSpecialN_Phys,
        ftKb_MrSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MrSpecialAirN = 400
        ftKb_SM_MrSpecialAirN,
        ftKb_MF_SpecialAirNMr,
        FtMoveId_KbSpecialNMr << 24,
        ftKb_MrSpecialAirN_Anim,
        ftKb_MrSpecialAirN_IASA,
        ftKb_MrSpecialAirN_Phys,
        ftKb_MrSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_LkSpecialNStart = 401
        ftKb_SM_LkSpecialNStart,
        ftKb_MF_SpecialNLk,
        FtMoveId_KbSpecialNLk << 24,
        ftKb_LkSpecialNStart_Anim,
        ftKb_LkSpecialNStart_IASA,
        ftKb_LkSpecialNStart_Phys,
        ftKb_LkSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_LkSpecialNLoop = 402
        ftKb_SM_LkSpecialNLoop,
        ftKb_MF_SpecialNLkCharged,
        FtMoveId_KbSpecialNLk << 24,
        ftKb_LkSpecialNLoop_Anim,
        ftKb_LkSpecialNLoop_IASA,
        ftKb_LkSpecialNLoop_Phys,
        ftKb_LkSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_LkSpecialNEnd = 403
        ftKb_SM_LkSpecialNEnd,
        ftKb_MF_SpecialNLk,
        FtMoveId_KbSpecialNLk << 24,
        ftKb_LkSpecialNEnd_Anim,
        ftKb_LkSpecialNEnd_IASA,
        ftKb_LkSpecialNEnd_Phys,
        ftKb_LkSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_LkSpecialAirNStart = 404
        ftKb_SM_LkSpecialAirNStart,
        ftKb_MF_SpecialAirNLk,
        FtMoveId_KbSpecialNLk << 24,
        ftKb_LkSpecialAirNStart_Anim,
        ftKb_LkSpecialAirNStart_IASA,
        ftKb_LkSpecialAirNStart_Phys,
        ftKb_LkSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_LkSpecialAirNLoop = 405
        ftKb_SM_LkSpecialAirNLoop,
        ftKb_MF_SpecialAirNLkCharged,
        FtMoveId_KbSpecialNLk << 24,
        ftKb_LkSpecialAirNLoop_Anim,
        ftKb_LkSpecialAirNLoop_IASA,
        ftKb_LkSpecialAirNLoop_Phys,
        ftKb_LkSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_LkSpecialAirNEnd = 406
        ftKb_SM_LkSpecialAirNEnd,
        ftKb_MF_SpecialAirNLk,
        FtMoveId_KbSpecialNLk << 24,
        ftKb_LkSpecialAirNEnd_Anim,
        ftKb_LkSpecialAirNEnd_IASA,
        ftKb_LkSpecialAirNEnd_Phys,
        ftKb_LkSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SsSpecialNStart = 407
        ftKb_SM_SsSpecialNStart,
        ftKb_MF_SpecialNSs,
        FtMoveId_KbSpecialNSs << 24,
        ftKb_SsSpecialNStart_Anim,
        ftKb_SsSpecialNStart_IASA,
        ftKb_SsSpecialNStart_Phys,
        ftKb_SsSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SsSpecialNHold = 408
        ftKb_SM_SsSpecialNHold,
        ftKb_MF_SpecialNSs,
        FtMoveId_KbSpecialNSs << 24,
        ftKb_SsSpecialNHold_Anim,
        ftKb_SsSpecialNHold_IASA,
        ftKb_SsSpecialNHold_Phys,
        ftKb_SsSpecialNHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SsSpecialNCancel = 409
        ftKb_SM_SsSpecialNCancel,
        ftKb_MF_SpecialNSs,
        FtMoveId_KbSpecialNSs << 24,
        ftKb_SsSpecialNCancel_Anim,
        ftKb_SsSpecialNCancel_IASA,
        ftKb_SsSpecialNCancel_Phys,
        ftKb_SsSpecialNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SsSpecialN = 410
        ftKb_SM_SsSpecialN,
        ftKb_MF_SpecialNSs,
        FtMoveId_KbSpecialNSs << 24,
        ftKb_SsSpecialN_Anim,
        ftKb_SsSpecialN_IASA,
        ftKb_SsSpecialN_Phys,
        ftKb_SsSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SsSpecialAirNStart = 411
        ftKb_SM_SsSpecialAirNStart,
        ftKb_MF_SpecialAirNSs,
        FtMoveId_KbSpecialNSs << 24,
        ftKb_SsSpecialAirNStart_Anim,
        ftKb_SsSpecialAirNStart_IASA,
        ftKb_SsSpecialAirNStart_Phys,
        ftKb_SsSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SsSpecialAirN = 412
        ftKb_SM_SsSpecialAirN,
        ftKb_MF_SpecialAirNSs,
        FtMoveId_KbSpecialNSs << 24,
        ftKb_SsSpecialAirN_Anim,
        ftKb_SsSpecialAirN_IASA,
        ftKb_SsSpecialAirN_Phys,
        ftKb_SsSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialN1 = 413
        ftKb_SM_YsSpecialN1,
        ftKb_MF_SpecialNYs,
        FtMoveId_KbSpecialNYs << 24,
        ftKb_YsSpecialN1_Anim,
        NULL,
        ftKb_YsSpecialN1_Phys,
        ftKb_YsSpecialN1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialNCapture1_0 = 414
        ftKb_SM_YsSpecialNCapture1,
        ftKb_MF_SpecialNYs,
        FtMoveId_KbSpecialNYs << 24,
        ftKb_YsSpecialNCapture1_Anim,
        NULL,
        ftKb_YsSpecialNCapture1_Phys,
        ftKb_YsSpecialNCapture1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialNCapture1_1 = 415
        ftKb_SM_YsSpecialNCapture1,
        ftKb_MF_SpecialNYs,
        FtMoveId_KbSpecialNYs << 24,
        ftKb_YsSpecialAirNCapture1_Anim,
        NULL,
        ftKb_YsSpecialAirNCapture1_Phys,
        ftKb_YsSpecialAirNCapture1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialNCapture2_0 = 416
        ftKb_SM_YsSpecialNCapture2,
        ftKb_MF_SpecialNYs,
        FtMoveId_SpecialN << 24,
        ftKb_YsSpecialNCapture2_1_Anim,
        NULL,
        ftKb_YsSpecialNCapture2_1_Phys,
        ftKb_YsSpecialNCapture2_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialNCapture2_1 = 417
        ftKb_SM_YsSpecialNCapture2,
        ftKb_MF_SpecialNYs,
        FtMoveId_SpecialN << 24,
        ftKb_YsSpecialNCapture2_0_Anim,
        NULL,
        ftKb_YsSpecialNCapture2_0_Phys,
        ftKb_YsSpecialNCapture2_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialAirNCapture2 = 418
        ftKb_SM_YsSpecialAirNCapture2,
        ftKb_MF_SpecialAirNYs,
        FtMoveId_KbSpecialNYs << 24,
        ftKb_YsSpecialAirNCapture2_Anim,
        NULL,
        ftKb_YsSpecialAirNCapture2_Phys,
        ftKb_YsSpecialAirNCapture2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialAirNCapture1_0 = 419
        ftKb_SM_YsSpecialAirCapture1,
        ftKb_MF_SpecialAirNYs,
        FtMoveId_KbSpecialNYs << 24,
        ftKb_YsSpecialAirCapture1_Anim,
        NULL,
        ftKb_YsSpecialAirCapture1_Phys,
        ftKb_YsSpecialAirCapture1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialAirNCapture1_1 = 420
        ftKb_SM_YsSpecialAirCapture1,
        ftKb_MF_SpecialAirNYs,
        FtMoveId_KbSpecialNYs << 24,
        ftKb_YsSpecialAirCapture2_Anim,
        NULL,
        ftKb_YsSpecialAirCapture2_Phys,
        ftKb_YsSpecialAirCapture2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialAirN2_0 = 421
        ftKb_SM_YsSpecialAirN2,
        ftKb_MF_SpecialAirNYs,
        FtMoveId_KbSpecialNYs << 24,
        ftKb_YsSpecialAirN2_0_Anim,
        NULL,
        ftKb_YsSpecialAirN2_0_Phys,
        ftKb_YsSpecialAirN2_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_YsSpecialAirN2_1 = 422
        ftKb_SM_YsSpecialAirN2,
        ftKb_MF_SpecialAirNYs,
        FtMoveId_KbSpecialNYs << 24,
        ftKb_YsSpecialAirN2_1_Anim,
        NULL,
        ftKb_YsSpecialAirN2_1_Phys,
        ftKb_YsSpecialAirN2_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FxSpecialNStart = 423
        ftKb_SM_FxSpecialNStart,
        ftKb_MF_SpecialNFx,
        FtMoveId_KbSpecialNFx << 24,
        ftKb_FxSpecialNStart_Anim,
        ftKb_FxSpecialNStart_IASA,
        ftKb_FxSpecialNStart_Phys,
        ftKb_FxSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FxSpecialNLoop = 424
        ftKb_SM_FxSpecialNLoop,
        ftKb_MF_SpecialNFxLoop,
        FtMoveId_KbSpecialNFx << 24,
        ftKb_FxSpecialNLoop_Anim,
        ftKb_FxSpecialNLoop_IASA,
        ftKb_FxSpecialNLoop_Phys,
        ftKb_FxSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FxSpecialNEnd = 425
        ftKb_SM_FxSpecialNEnd,
        ftKb_MF_SpecialNFx,
        FtMoveId_KbSpecialNFx << 24,
        ftKb_FxSpecialNEnd_Anim,
        ftKb_FxSpecialNEnd_IASA,
        ftKb_FxSpecialNEnd_Phys,
        ftKb_FxSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FxSpecialAirNStart = 426
        ftKb_SM_FxSpecialAirNStart,
        ftKb_MF_SpecialAirNFx,
        FtMoveId_KbSpecialNFx << 24,
        ftKb_FxSpecialAirNStart_Anim,
        ftKb_FxSpecialAirNStart_IASA,
        ftKb_FxSpecialAirNStart_Phys,
        ftKb_FxSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FxSpecialAirNLoop = 427
        ftKb_SM_FxSpecialAirNLoop,
        ftKb_MF_SpecialAirNFxLoop,
        FtMoveId_KbSpecialNFx << 24,
        ftKb_FxSpecialAirNLoop_Anim,
        ftKb_FxSpecialAirNLoop_IASA,
        ftKb_FxSpecialAirNLoop_Phys,
        ftKb_FxSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FxSpecialAirNEnd = 428
        ftKb_SM_FxSpecialAirNEnd,
        ftKb_MF_SpecialAirNFx,
        FtMoveId_KbSpecialNFx << 24,
        ftKb_FxSpecialAirNEnd_Anim,
        ftKb_FxSpecialAirNEnd_IASA,
        ftKb_FxSpecialAirNEnd_Phys,
        ftKb_FxSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PkSpecialN = 429
        ftKb_SM_PkSpecialN,
        ftKb_MF_SpecialNPk,
        FtMoveId_KbSpecialNPk << 24,
        ftKb_PkSpecialN_Anim,
        ftKb_PkSpecialN_IASA,
        ftKb_PkSpecialN_Phys,
        ftKb_PkSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PkSpecialAirN = 430
        ftKb_SM_PkSpecialAirN,
        ftKb_MF_SpecialAirNPk,
        FtMoveId_KbSpecialNPk << 24,
        ftKb_PkSpecialAirN_Anim,
        ftKb_PkSpecialAirN_IASA,
        ftKb_PkSpecialAirN_Phys,
        ftKb_PkSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_LgSpecialN = 431
        ftKb_SM_LgSpecialN,
        ftKb_MF_SpecialNLg,
        FtMoveId_KbSpecialNLg << 24,
        ftKb_LgSpecialN_Anim,
        ftKb_LgSpecialN_IASA,
        ftKb_LgSpecialN_Phys,
        ftKb_LgSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_LgSpecialAirN = 432
        ftKb_SM_LgSpecialAirN,
        ftKb_MF_SpecialAirNLg,
        FtMoveId_KbSpecialNLg << 24,
        ftKb_LgSpecialAirN_Anim,
        ftKb_LgSpecialAirN_IASA,
        ftKb_LgSpecialAirN_Phys,
        ftKb_LgSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_CaSpecialN = 433
        ftKb_SM_CaSpecialN,
        ftKb_MF_SpecialNCa,
        FtMoveId_KbSpecialNCa << 24,
        ftKb_CaSpecialN_Anim,
        ftKb_CaSpecialN_IASA,
        ftKb_CaSpecialN_Phys,
        ftKb_CaSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_CaSpecialAirN = 434
        ftKb_SM_CaSpecialAirN,
        ftKb_MF_SpecialAirNCa,
        FtMoveId_KbSpecialNCa << 24,
        ftKb_CaSpecialAirN_Anim,
        ftKb_CaSpecialAirN_IASA,
        ftKb_CaSpecialAirN_Phys,
        ftKb_CaSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_NsSpecialNStart = 435
        ftKb_SM_NsSpecialNStart,
        ftKb_MF_SpecialNNs,
        FtMoveId_KbSpecialNNs << 24,
        ftKb_NsSpecialNStart_Anim,
        ftKb_NsSpecialNStart_IASA,
        ftKb_NsSpecialNStart_Phys,
        ftKb_NsSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_NsSpecialNHold0 = 436
        ftKb_SM_NsSpecialNHold0,
        ftKb_MF_SpecialNNs,
        FtMoveId_KbSpecialNNs << 24,
        ftKb_NsSpecialNHold_Anim,
        ftKb_NsSpecialNHold_IASA,
        ftKb_NsSpecialNHold_Phys,
        ftKb_NsSpecialNHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_NsSpecialNHold1 = 437
        ftKb_SM_NsSpecialNHold1,
        ftKb_MF_SpecialNNs,
        FtMoveId_KbSpecialNNs << 24,
        ftKb_NsSpecialNHold_Anim,
        ftKb_NsSpecialNHold_IASA,
        ftKb_NsSpecialNHold_Phys,
        ftKb_NsSpecialNHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_NsSpecialNEnd = 438
        ftKb_SM_NsSpecialNEnd,
        ftKb_MF_SpecialNNs,
        FtMoveId_KbSpecialNNs << 24,
        ftKb_NsSpecialNEnd_Anim,
        ftKb_NsSpecialNEnd_IASA,
        ftKb_NsSpecialNEnd_Phys,
        ftKb_NsSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_NsSpecialAirNStart = 439
        ftKb_SM_NsSpecialAirNStart,
        ftKb_MF_SpecialAirNNs,
        FtMoveId_KbSpecialNNs << 24,
        ftKb_NsSpecialAirNStart_Anim,
        ftKb_NsSpecialAirNStart_IASA,
        ftKb_NsSpecialAirNStart_Phys,
        ftKb_NsSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_NsSpecialAirNHold0 = 440
        ftKb_SM_NsSpecialAirNHold0,
        ftKb_MF_SpecialAirNNs,
        FtMoveId_KbSpecialNNs << 24,
        ftKb_NsSpecialAirNHold_Anim,
        ftKb_NsSpecialAirNHold_IASA,
        ftKb_NsSpecialAirNHold_Phys,
        ftKb_NsSpecialAirNHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_NsSpecialAirNHold1 = 441
        ftKb_SM_NsSpecialAirNHold1,
        ftKb_MF_SpecialAirNNs,
        FtMoveId_KbSpecialNNs << 24,
        ftKb_NsSpecialAirNHold_Anim,
        ftKb_NsSpecialAirNHold_IASA,
        ftKb_NsSpecialAirNHold_Phys,
        ftKb_NsSpecialAirNHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_NsSpecialAirNEnd = 442
        ftKb_SM_NsSpecialAirNEnd,
        ftKb_MF_SpecialAirNNs,
        FtMoveId_KbSpecialNNs << 24,
        ftKb_NsSpecialAirNEnd_Anim,
        ftKb_NsSpecialAirNEnd_IASA,
        ftKb_NsSpecialAirNEnd_Phys,
        ftKb_NsSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_KpSpecialNStart = 443
        ftKb_SM_KpSpecialNStart,
        ftKb_MF_SpecialNKp,
        FtMoveId_KbSpecialNKp << 24,
        ftKb_KpSpecialNStart_Anim,
        ftKb_KpSpecialNStart_IASA,
        ftKb_KpSpecialNStart_Phys,
        ftKb_KpSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_KpSpecialN = 444
        ftKb_SM_KpSpecialN,
        ftKb_MF_SpecialNKpLoop,
        FtMoveId_KbSpecialNKp << 24,
        ftKb_KpSpecialN_Anim,
        ftKb_KpSpecialN_IASA,
        ftKb_KpSpecialN_Phys,
        ftKb_KpSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_KpSpecialNEnd = 445
        ftKb_SM_KpSpecialNEnd,
        ftKb_MF_SpecialNKp,
        FtMoveId_KbSpecialNKp << 24,
        ftKb_KpSpecialNEnd_Anim,
        ftKb_KpSpecialNEnd_IASA,
        ftKb_KpSpecialNEnd_Phys,
        ftKb_KpSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_KpSpecialAirNStart = 446
        ftKb_SM_KpSpecialAirNStart,
        ftKb_MF_SpecialAirNKp,
        FtMoveId_KbSpecialNKp << 24,
        ftKb_KpSpecialAirNStart_Anim,
        ftKb_KpSpecialAirNStart_IASA,
        ftKb_KpSpecialAirNStart_Phys,
        ftKb_KpSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_KpSpecialAirN = 447
        ftKb_SM_KpSpecialAirN,
        ftKb_MF_SpecialAirNKpLoop,
        FtMoveId_KbSpecialNKp << 24,
        ftKb_KpSpecialAirN_Anim,
        ftKb_KpSpecialAirN_IASA,
        ftKb_KpSpecialAirN_Phys,
        ftKb_KpSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_KpSpecialAirNEnd = 448
        ftKb_SM_KpSpecialAirNEnd,
        ftKb_MF_SpecialAirNKp,
        FtMoveId_KbSpecialNKp << 24,
        ftKb_KpSpecialAirNEnd_Anim,
        ftKb_KpSpecialAirNEnd_IASA,
        ftKb_KpSpecialAirNEnd_Phys,
        ftKb_KpSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PeSpecialLw = 449
        ftKb_SM_PeSpecialLw,
        ftKb_MF_SpecialNPe,
        FtMoveId_KbSpecialNPe << 24,
        ftKb_PeSpecialLw_Anim,
        ftKb_PeSpecialLw_IASA,
        ftKb_PeSpecialLw_Phys,
        ftKb_PeSpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PeSpecialLwHit = 450
        ftKb_SM_PeSpecialLwHit,
        ftKb_MF_SpecialNPe,
        FtMoveId_KbSpecialNPe << 24,
        ftKb_PeSpecialLwHit_Anim,
        ftKb_PeSpecialLwHit_IASA,
        ftKb_PeSpecialLwHit_Phys,
        ftKb_PeSpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PeSpecialAirLw = 451
        ftKb_SM_PeSpecialAirLw,
        ftKb_MF_SpecialAirNPe,
        FtMoveId_KbSpecialNPe << 24,
        ftKb_PeSpecialAirLw_Anim,
        ftKb_PeSpecialAirLw_IASA,
        ftKb_PeSpecialAirLw_Phys,
        ftKb_PeSpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PeSpecialAirLwHit = 452
        ftKb_SM_PeSpecialAirLwHit,
        ftKb_MF_SpecialAirNPe,
        FtMoveId_KbSpecialNPe << 24,
        ftKb_PeSpecialAirLwHit_Anim,
        ftKb_PeSpecialAirLwHit_IASA,
        ftKb_PeSpecialAirLwHit_Phys,
        ftKb_PeSpecialAirLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PpSpecialN = 453
        ftKb_SM_PpSpecialN,
        ftKb_MF_SpecialNPp,
        FtMoveId_KbSpecialNPp << 24,
        ftKb_PpSpecialN_Anim,
        ftKb_PpSpecialN_IASA,
        ftKb_PpSpecialN_Phys,
        ftKb_PpSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PpSpecialAirN = 454
        ftKb_SM_PpSpecialAirN,
        ftKb_MF_SpecialAirNPp,
        FtMoveId_KbSpecialNPp << 24,
        ftKb_PpSpecialAirN_Anim,
        ftKb_PpSpecialAirN_IASA,
        ftKb_PpSpecialAirN_Phys,
        ftKb_PpSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialNStart = 455
        ftKb_SM_DkSpecialNStart,
        ftKb_MF_SpecialNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialNStart_Anim,
        ftKb_DkSpecialNStart_IASA,
        ftKb_DkSpecialNStart_Phys,
        ftKb_DkSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialNLoop = 456
        ftKb_SM_DkSpecialNLoop,
        ftKb_MF_SpecialNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialNLoop_Anim,
        ftKb_DkSpecialNLoop_IASA,
        ftKb_DkSpecialNLoop_Phys,
        ftKb_DkSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialNCancel = 457
        ftKb_SM_DkSpecialNCancel,
        ftKb_MF_SpecialNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialNCancel_Anim,
        ftKb_DkSpecialNCancel_IASA,
        ftKb_DkSpecialNCancel_Phys,
        ftKb_DkSpecialNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialN = 458
        ftKb_SM_DkSpecialN,
        ftKb_MF_SpecialNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialN_Anim,
        ftKb_DkSpecialN_IASA,
        ftKb_DkSpecialN_Phys,
        ftKb_DkSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialNFull = 459
        ftKb_SM_DkSpecialNFull,
        ftKb_MF_SpecialNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialNFull_Anim,
        ftKb_DkSpecialNFull_IASA,
        ftKb_DkSpecialNFull_Phys,
        ftKb_DkSpecialNFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialAirNStart = 460
        ftKb_SM_DkSpecialAirNStart,
        ftKb_MF_SpecialAirNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialAirNStart_Anim,
        ftKb_DkSpecialAirNStart_IASA,
        ftKb_DkSpecialAirNStart_Phys,
        ftKb_DkSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialAirNLoop = 461
        ftKb_SM_DkSpecialAirNLoop,
        ftKb_MF_SpecialAirNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialAirNLoop_Anim,
        ftKb_DkSpecialAirNLoop_IASA,
        ftKb_DkSpecialAirNLoop_Phys,
        ftKb_DkSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialAirNCancel = 462
        ftKb_SM_DkSpecialAirNCancel,
        ftKb_MF_SpecialAirNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialAirNCancel_Anim,
        ftKb_DkSpecialAirNCancel_IASA,
        ftKb_DkSpecialAirNCancel_Phys,
        ftKb_DkSpecialAirNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialAirN = 463
        ftKb_SM_DkSpecialAirN,
        ftKb_MF_SpecialAirNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialAirN_Anim,
        ftKb_DkSpecialAirN_IASA,
        ftKb_DkSpecialAirN_Phys,
        ftKb_DkSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DkSpecialAirNFull = 464
        ftKb_SM_DkSpecialAirNFull,
        ftKb_MF_SpecialAirNDk,
        FtMoveId_KbSpecialNDk << 24,
        ftKb_DkSpecialAirNFull_Anim,
        ftKb_DkSpecialAirNFull_IASA,
        ftKb_DkSpecialAirNFull_Phys,
        ftKb_DkSpecialAirNFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_ZdSpecialN = 465
        ftKb_SM_ZdSpecialN,
        ftKb_MF_SpecialNZd,
        FtMoveId_KbSpecialNZd << 24,
        ftKb_ZdSpecialN_Anim,
        ftKb_ZdSpecialN_IASA,
        ftKb_ZdSpecialN_Phys,
        ftKb_ZdSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_ZdSpecialAirN = 466
        ftKb_SM_ZdSpecialAirN,
        ftKb_MF_SpecialAirNZd,
        FtMoveId_KbSpecialNZd << 24,
        ftKb_ZdSpecialAirN_Anim,
        ftKb_ZdSpecialAirN_IASA,
        ftKb_ZdSpecialAirN_Phys,
        ftKb_ZdSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SkSpecialNStart = 467
        ftKb_SM_SkSpecialNStart,
        ftKb_MF_SpecialNSk,
        FtMoveId_KbSpecialNSk << 24,
        ftKb_SkSpecialNStart_Anim,
        ftKb_SkSpecialNStart_IASA,
        ftKb_SkSpecialNStart_Phys,
        ftKb_SkSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SkSpecialNLoop = 468
        ftKb_SM_SkSpecialNLoop,
        ftKb_MF_SpecialNSkLoop,
        FtMoveId_KbSpecialNSk << 24,
        ftKb_SkSpecialNLoop_Anim,
        ftKb_SkSpecialNLoop_IASA,
        ftKb_SkSpecialNLoop_Phys,
        ftKb_SkSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SkSpecialNCancel = 469
        ftKb_SM_SkSpecialNCancel,
        ftKb_MF_SpecialNSk,
        FtMoveId_KbSpecialNSk << 24,
        ftKb_SkSpecialNCancel_Anim,
        ftKb_SkSpecialNCancel_IASA,
        ftKb_SkSpecialNCancel_Phys,
        ftKb_SkSpecialNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SkSpecialNEnd = 470
        ftKb_SM_SkSpecialNEnd,
        ftKb_MF_SpecialNSk,
        FtMoveId_KbSpecialNSk << 24,
        ftKb_SkSpecialNEnd_Anim,
        ftKb_SkSpecialNEnd_IASA,
        ftKb_SkSpecialNEnd_Phys,
        ftKb_SkSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SkSpecialAirNStart = 471
        ftKb_SM_SkSpecialAirNStart,
        ftKb_MF_SpecialAirNSk,
        FtMoveId_KbSpecialNSk << 24,
        ftKb_SkSpecialAirNStart_Anim,
        ftKb_SkSpecialAirNStart_IASA,
        ftKb_SkSpecialAirNStart_Phys,
        ftKb_SkSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SkSpecialAirNLoop = 472
        ftKb_SM_SkSpecialAirNLoop,
        ftKb_MF_SpecialAirNSkLoop,
        FtMoveId_KbSpecialNSk << 24,
        ftKb_SkSpecialAirNLoop_Anim,
        ftKb_SkSpecialAirNLoop_IASA,
        ftKb_SkSpecialAirNLoop_Phys,
        ftKb_SkSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SkSpecialAirNCancel = 473
        ftKb_SM_SkSpecialAirNCancel,
        ftKb_MF_SpecialAirNSk,
        FtMoveId_KbSpecialNSk << 24,
        ftKb_SkSpecialAirNCancel_Anim,
        ftKb_SkSpecialAirNCancel_IASA,
        ftKb_SkSpecialAirNCancel_Phys,
        ftKb_SkSpecialAirNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_SkSpecialAirNEnd = 474
        ftKb_SM_SkSpecialAirNEnd,
        ftKb_MF_SpecialAirNSk,
        FtMoveId_KbSpecialNSk << 24,
        ftKb_SkSpecialAirNEnd_Anim,
        ftKb_SkSpecialAirNEnd_IASA,
        ftKb_SkSpecialAirNEnd_Phys,
        ftKb_SkSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialNStartR = 475
        ftKb_SM_PrSpecialNStartR,
        ftKb_MF_SpecialNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialNStart_Anim,
        ftKb_PrSpecialNStart_IASA,
        ftKb_PrSpecialNStart_Phys,
        ftKb_PrSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialNStartL = 476
        ftKb_SM_PrSpecialNStartL,
        ftKb_MF_SpecialNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialNStart_Anim,
        ftKb_PrSpecialNStart_IASA,
        ftKb_PrSpecialNStart_Phys,
        ftKb_PrSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialNLoop = 477
        ftKb_SM_PrSpecialNLoop,
        ftKb_MF_SpecialNPrLoop,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialNLoop_Anim,
        ftKb_PrSpecialNLoop_IASA,
        ftKb_PrSpecialNLoop_Phys,
        ftKb_PrSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialNFull = 478
        ftKb_SM_PrSpecialNFull,
        ftKb_MF_SpecialNPrLoop,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialNFull_Anim,
        ftKb_PrSpecialNFull_IASA,
        ftKb_PrSpecialNFull_Phys,
        ftKb_PrSpecialNFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialN1 = 479
        ftKb_SM_PrSpecialN1,
        ftKb_MF_SpecialNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialN1_Anim,
        ftKb_PrSpecialN1_IASA,
        ftKb_PrSpecialN1_Phys,
        ftKb_PrSpecialN1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialNTurn = 480
        ftKb_SM_PrSpecialNTurn,
        ftKb_MF_SpecialNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialNTurn_Anim,
        ftKb_PrSpecialNTurn_IASA,
        ftKb_PrSpecialNTurn_Phys,
        ftKb_PrSpecialNTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialNEndR = 481
        ftKb_SM_PrSpecialNEndR,
        ftKb_MF_SpecialNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialNEnd_Anim,
        ftKb_PrSpecialNEnd_IASA,
        ftKb_PrSpecialNEnd_Phys,
        ftKb_PrSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialNEndL = 482
        ftKb_SM_PrSpecialNEndL,
        ftKb_MF_SpecialNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialNEnd_Anim,
        ftKb_PrSpecialNEnd_IASA,
        ftKb_PrSpecialNEnd_Phys,
        ftKb_PrSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialAirNStartR = 483
        ftKb_SM_PrSpecialAirNStartR,
        ftKb_MF_SpecialAirNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialAirNStart_Anim,
        ftKb_PrSpecialAirNStart_IASA,
        ftKb_PrSpecialAirNStart_Phys,
        ftKb_PrSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialAirNStartL = 484
        ftKb_SM_PrSpecialAirNStartL,
        ftKb_MF_SpecialAirNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialAirNStart_Anim,
        ftKb_PrSpecialAirNStart_IASA,
        ftKb_PrSpecialAirNStart_Phys,
        ftKb_PrSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialAirNLoop = 485
        ftKb_SM_PrSpecialAirNLoop,
        ftKb_MF_SpecialAirNPrLoop,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialAirNLoop_Anim,
        ftKb_PrSpecialAirNLoop_IASA,
        ftKb_PrSpecialAirNLoop_Phys,
        ftKb_PrSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialAirNFull = 486
        ftKb_SM_PrSpecialAirNFull,
        ftKb_MF_SpecialAirNPrLoop,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialAirNFull_Anim,
        ftKb_PrSpecialAirNFull_IASA,
        ftKb_PrSpecialAirNFull_Phys,
        ftKb_PrSpecialAirNFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialAirN = 487
        ftKb_SM_PrSpecialAirN,
        ftKb_MF_SpecialAirNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialAirN_Anim,
        ftKb_PrSpecialAirN_IASA,
        ftKb_PrSpecialAirN_Phys,
        ftKb_PrSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialN0 = 488
        ftKb_SM_PrSpecialN0,
        ftKb_MF_SpecialNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialN_Anim,
        ftKb_PrSpecialN_IASA,
        ftKb_PrSpecialN_Phys,
        ftKb_PrSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialAirNEndR0 = 489
        ftKb_SM_PrSpecialAirNEndR0,
        ftKb_MF_SpecialAirNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialAirNEndR_Anim,
        ftKb_PrSpecialAirNEndR_IASA,
        ftKb_PrSpecialAirNEndR_Phys,
        ftKb_PrSpecialAirNEndR_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialAirNEndR1 = 490
        ftKb_SM_PrSpecialAirNEndR1,
        ftKb_MF_SpecialAirNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialAirNEndR_Anim,
        ftKb_PrSpecialAirNEndR_IASA,
        ftKb_PrSpecialAirNEndR_Phys,
        ftKb_PrSpecialAirNEndR_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PrSpecialNHit = 491
        ftKb_SM_PrSpecialNHit,
        ftKb_MF_SpecialAirNPr,
        FtMoveId_KbSpecialNPr << 24,
        ftKb_PrSpecialNHit_Anim,
        ftKb_PrSpecialNHit_IASA,
        ftKb_PrSpecialNHit_Phys,
        ftKb_PrSpecialNHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MsSpecialNStart = 492
        ftKb_SM_MsSpecialNStart,
        ftKb_MF_SpecialNMs,
        FtMoveId_KbSpecialNMs << 24,
        ftKb_MsSpecialNStart_Anim,
        ftKb_MsSpecialNStart_IASA,
        ftKb_MsSpecialNStart_Phys,
        ftKb_MsSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MsSpecialNLoop = 493
        ftKb_SM_MsSpecialNLoop,
        ftKb_MF_SpecialNMs,
        FtMoveId_KbSpecialNMs << 24,
        ftKb_MsSpecialNLoop_Anim,
        ftKb_MsSpecialNLoop_IASA,
        ftKb_MsSpecialNLoop_Phys,
        ftKb_MsSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MsSpecialNEnd0 = 494
        ftKb_SM_MsSpecialNEnd0,
        ftKb_MF_SpecialNMs,
        FtMoveId_KbSpecialNMs << 24,
        ftKb_MsSpecialNEnd_Anim,
        ftKb_MsSpecialNEnd_IASA,
        ftKb_MsSpecialNEnd_Phys,
        ftKb_MsSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MsSpecialNEnd1 = 495
        ftKb_SM_MsSpecialNEnd1,
        ftKb_MF_SpecialNMs,
        FtMoveId_KbSpecialNMs << 24,
        ftKb_MsSpecialNEnd_Anim,
        ftKb_MsSpecialNEnd_IASA,
        ftKb_MsSpecialNEnd_Phys,
        ftKb_MsSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MsSpecialAirNStart = 496
        ftKb_SM_MsSpecialAirNStart,
        ftKb_MF_SpecialAirNMs,
        FtMoveId_KbSpecialNMs << 24,
        ftKb_MsSpecialAirNStart_Anim,
        ftKb_MsSpecialAirNStart_IASA,
        ftKb_MsSpecialAirNStart_Phys,
        ftKb_MsSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MsSpecialAirNLoop = 497
        ftKb_SM_MsSpecialAirNLoop,
        ftKb_MF_SpecialAirNMs,
        FtMoveId_KbSpecialNMs << 24,
        ftKb_MsSpecialAirNLoop_Anim,
        ftKb_MsSpecialAirNLoop_IASA,
        ftKb_MsSpecialAirNLoop_Phys,
        ftKb_MsSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MsSpecialAirNEnd0 = 498
        ftKb_SM_MsSpecialAirNEnd0,
        ftKb_MF_SpecialAirNMs,
        FtMoveId_KbSpecialNMs << 24,
        ftKb_MsSpecialAirNEnd_Anim,
        ftKb_MsSpecialAirNEnd_IASA,
        ftKb_MsSpecialAirNEnd_Phys,
        ftKb_MsSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MsSpecialAirNEnd1 = 499
        ftKb_SM_MsSpecialAirNEnd1,
        ftKb_MF_SpecialAirNMs,
        FtMoveId_KbSpecialNMs << 24,
        ftKb_MsSpecialAirNEnd_Anim,
        ftKb_MsSpecialAirNEnd_IASA,
        ftKb_MsSpecialAirNEnd_Phys,
        ftKb_MsSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialNStart = 500
        ftKb_SM_MtSpecialNStart,
        ftKb_MF_SpecialNMt,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialNStart_Anim,
        ftKb_MtSpecialNStart_IASA,
        ftKb_MtSpecialNStart_Phys,
        ftKb_MtSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialNLoop = 501
        ftKb_SM_MtSpecialNLoop,
        ftKb_MF_SpecialNMtLoop,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialNLoop_Anim,
        ftKb_MtSpecialNLoop_IASA,
        ftKb_MtSpecialNLoop_Phys,
        ftKb_MtSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialNLoopFull = 502
        ftKb_SM_MtSpecialNLoopFull,
        ftKb_MF_SpecialNMtLoop,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialNLoopFull_Anim,
        ftKb_MtSpecialNLoopFull_IASA,
        ftKb_MtSpecialNLoopFull_Phys,
        ftKb_MtSpecialNLoopFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialNCancel = 503
        ftKb_SM_MtSpecialNCancel,
        ftKb_MF_SpecialNMt,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialNCancel_Anim,
        ftKb_MtSpecialNCancel_IASA,
        ftKb_MtSpecialNCancel_Phys,
        ftKb_MtSpecialNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialNEnd = 504
        ftKb_SM_MtSpecialNEnd,
        ftKb_MF_SpecialNMt,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialNEnd_Anim,
        ftKb_MtSpecialNEnd_IASA,
        ftKb_MtSpecialNEnd_Phys,
        ftKb_MtSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialAirNStart = 505
        ftKb_SM_MtSpecialAirNStart,
        ftKb_MF_SpecialAirNMt,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialAirNStart_Anim,
        ftKb_MtSpecialAirNStart_IASA,
        ftKb_MtSpecialAirNStart_Phys,
        ftKb_MtSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialAirNLoop = 506
        ftKb_SM_MtSpecialAirNLoop,
        ftKb_MF_SpecialAirNMtLoop,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialAirNLoop_Anim,
        ftKb_MtSpecialAirNLoop_IASA,
        ftKb_MtSpecialAirNLoop_Phys,
        ftKb_MtSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialAirNLoopFull = 507
        ftKb_SM_MtSpecialAirNLoopFull,
        ftKb_MF_SpecialAirNMtLoop,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialAirNLoopFull_Anim,
        ftKb_MtSpecialAirNLoopFull_IASA,
        ftKb_MtSpecialAirNLoopFull_Phys,
        ftKb_MtSpecialAirNLoopFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialAirNCancel = 508
        ftKb_SM_MtSpecialAirNCancel,
        ftKb_MF_SpecialAirNMt,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialAirNCancel_Anim,
        ftKb_MtSpecialAirNCancel_IASA,
        ftKb_MtSpecialAirNCancel_Phys,
        ftKb_MtSpecialAirNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_MtSpecialAirNEnd = 509
        ftKb_SM_MtSpecialAirNEnd,
        ftKb_MF_SpecialAirNMt,
        FtMoveId_KbSpecialNMt << 24,
        ftKb_MtSpecialAirNEnd_Anim,
        ftKb_MtSpecialAirNEnd_IASA,
        ftKb_MtSpecialAirNEnd_Phys,
        ftKb_MtSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GwSpecialN = 510
        ftKb_SM_GwSpecialN,
        ftKb_MF_SpecialNGw,
        FtMoveId_KbSpecialNGw << 24,
        ftKb_GwSpecialN_Anim,
        ftKb_GwSpecialN_IASA,
        ftKb_GwSpecialN_Phys,
        ftKb_GwSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GwSpecialAirN = 511
        ftKb_SM_GwSpecialAirN,
        ftKb_MF_SpecialAirNGw,
        FtMoveId_KbSpecialNGw << 24,
        ftKb_GwSpecialAirN_Anim,
        ftKb_GwSpecialAirN_IASA,
        ftKb_GwSpecialAirN_Phys,
        ftKb_GwSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DrSpecialN = 512
        ftKb_SM_DrSpecialN,
        ftKb_MF_SpecialNDr,
        FtMoveId_KbSpecialNDr << 24,
        ftKb_MrSpecialN_Anim,
        ftKb_MrSpecialN_IASA,
        ftKb_MrSpecialN_Phys,
        ftKb_MrSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_DrSpecialAirN = 513
        ftKb_SM_DrSpecialAirN,
        ftKb_MF_SpecialAirNDr,
        FtMoveId_KbSpecialNDr << 24,
        ftKb_MrSpecialAirN_Anim,
        ftKb_MrSpecialAirN_IASA,
        ftKb_MrSpecialAirN_Phys,
        ftKb_MrSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_ClSpecialNStart = 514
        ftKb_SM_ClSpecialNStart,
        ftKb_MF_SpecialNCl,
        FtMoveId_KbSpecialNCl << 24,
        ftKb_LkSpecialNStart_Anim,
        ftKb_LkSpecialNStart_IASA,
        ftKb_LkSpecialNStart_Phys,
        ftKb_LkSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_ClSpecialNLoop = 515
        ftKb_SM_ClSpecialNLoop,
        ftKb_MF_SpecialNClCharged,
        FtMoveId_KbSpecialNCl << 24,
        ftKb_LkSpecialNLoop_Anim,
        ftKb_LkSpecialNLoop_IASA,
        ftKb_LkSpecialNLoop_Phys,
        ftKb_LkSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_ClSpecialNEnd = 516
        ftKb_SM_ClSpecialNEnd,
        ftKb_MF_SpecialNCl,
        FtMoveId_KbSpecialNCl << 24,
        ftKb_LkSpecialNEnd_Anim,
        ftKb_LkSpecialNEnd_IASA,
        ftKb_LkSpecialNEnd_Phys,
        ftKb_LkSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_ClSpecialAirNStart = 517
        ftKb_SM_ClSpecialAirNStart,
        ftKb_MF_SpecialAirNCl,
        FtMoveId_KbSpecialNCl << 24,
        ftKb_LkSpecialAirNStart_Anim,
        ftKb_LkSpecialAirNStart_IASA,
        ftKb_LkSpecialAirNStart_Phys,
        ftKb_LkSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_ClSpecialAirNLoop = 518
        ftKb_SM_ClSpecialAirNLoop,
        ftKb_MF_SpecialAirNClCharged,
        FtMoveId_KbSpecialNCl << 24,
        ftKb_LkSpecialAirNLoop_Anim,
        ftKb_LkSpecialAirNLoop_IASA,
        ftKb_LkSpecialAirNLoop_Phys,
        ftKb_LkSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_ClSpecialAirNEnd = 519
        ftKb_SM_ClSpecialAirNEnd,
        ftKb_MF_SpecialAirNCl,
        FtMoveId_KbSpecialNCl << 24,
        ftKb_LkSpecialAirNEnd_Anim,
        ftKb_LkSpecialAirNEnd_IASA,
        ftKb_LkSpecialAirNEnd_Phys,
        ftKb_LkSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FcSpecialNStart = 520
        ftKb_SM_FcSpecialNStart,
        ftKb_MF_SpecialNFc,
        FtMoveId_KbSpecialNFc << 24,
        ftKb_FxSpecialNStart_Anim,
        ftKb_FxSpecialNStart_IASA,
        ftKb_FxSpecialNStart_Phys,
        ftKb_FxSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FcSpecialNLoop = 521
        ftKb_SM_FcSpecialNLoop,
        ftKb_MF_SpecialNFcLoop,
        FtMoveId_KbSpecialNFc << 24,
        ftKb_FxSpecialNLoop_Anim,
        ftKb_FxSpecialNLoop_IASA,
        ftKb_FxSpecialNLoop_Phys,
        ftKb_FxSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FcSpecialNEnd = 522
        ftKb_SM_FcSpecialNEnd,
        ftKb_MF_SpecialNFc,
        FtMoveId_KbSpecialNFc << 24,
        ftKb_FxSpecialNEnd_Anim,
        ftKb_FxSpecialNEnd_IASA,
        ftKb_FxSpecialNEnd_Phys,
        ftKb_FxSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FcSpecialAirNStart = 523
        ftKb_SM_FcSpecialAirNStart,
        ftKb_MF_SpecialAirNFc,
        FtMoveId_KbSpecialNFc << 24,
        ftKb_FxSpecialAirNStart_Anim,
        ftKb_FxSpecialAirNStart_IASA,
        ftKb_FxSpecialAirNStart_Phys,
        ftKb_FxSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FcSpecialAirNLoop = 524
        ftKb_SM_FcSpecialAirNLoop,
        ftKb_MF_SpecialAirNFcLoop,
        FtMoveId_KbSpecialNFc << 24,
        ftKb_FxSpecialAirNLoop_Anim,
        ftKb_FxSpecialAirNLoop_IASA,
        ftKb_FxSpecialAirNLoop_Phys,
        ftKb_FxSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FcSpecialAirNEnd = 525
        ftKb_SM_FcSpecialAirNEnd,
        ftKb_MF_SpecialAirNFc,
        FtMoveId_KbSpecialNFc << 24,
        ftKb_FxSpecialAirNEnd_Anim,
        ftKb_FxSpecialAirNEnd_IASA,
        ftKb_FxSpecialAirNEnd_Phys,
        ftKb_FxSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PcSpecialN = 526
        ftKb_SM_PcSpecialN,
        ftKb_MF_SpecialNPc,
        FtMoveId_KbSpecialNPc << 24,
        ftKb_PkSpecialN_Anim,
        ftKb_PkSpecialN_IASA,
        ftKb_PkSpecialN_Phys,
        ftKb_PkSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_PcSpecialAirN = 527
        ftKb_SM_PcSpecialAirN,
        ftKb_MF_SpecialAirNPc,
        FtMoveId_KbSpecialNPc << 24,
        ftKb_PkSpecialAirN_Anim,
        ftKb_PkSpecialAirN_IASA,
        ftKb_PkSpecialAirN_Phys,
        ftKb_PkSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GnSpecialN = 528
        ftKb_SM_GnSpecialN,
        ftKb_MF_SpecialNGn,
        FtMoveId_KbSpecialNGn << 24,
        ftKb_CaSpecialN_Anim,
        ftKb_CaSpecialN_IASA,
        ftKb_CaSpecialN_Phys,
        ftKb_CaSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GnSpecialAirN = 529
        ftKb_SM_GnSpecialAirN,
        ftKb_MF_SpecialAirNGn,
        FtMoveId_KbSpecialNGn << 24,
        ftKb_CaSpecialAirN_Anim,
        ftKb_CaSpecialAirN_IASA,
        ftKb_CaSpecialAirN_Phys,
        ftKb_CaSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FeSpecialNStart = 530
        ftKb_SM_FeSpecialNStart,
        ftKb_MF_SpecialNFeStart,
        FtMoveId_KbSpecialNFe << 24,
        ftKb_MsSpecialNStart_Anim,
        ftKb_MsSpecialNStart_IASA,
        ftKb_MsSpecialNStart_Phys,
        ftKb_MsSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FeSpecialNLoop = 531
        ftKb_SM_FeSpecialNLoop,
        ftKb_MF_SpecialNFeStart,
        FtMoveId_KbSpecialNFe << 24,
        ftKb_MsSpecialNLoop_Anim,
        ftKb_MsSpecialNLoop_IASA,
        ftKb_MsSpecialNLoop_Phys,
        ftKb_MsSpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FeSpecialNEnd0 = 532
        ftKb_SM_FeSpecialNEnd0,
        ftKb_MF_SpecialNFeStart,
        FtMoveId_KbSpecialNFe << 24,
        ftKb_MsSpecialNEnd_Anim,
        ftKb_MsSpecialNEnd_IASA,
        ftKb_MsSpecialNEnd_Phys,
        ftKb_MsSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FeSpecialNEnd1 = 533
        ftKb_SM_FeSpecialNEnd1,
        ftKb_MF_SpecialNFeStart,
        FtMoveId_KbSpecialNFe << 24,
        ftKb_MsSpecialNEnd_Anim,
        ftKb_MsSpecialNEnd_IASA,
        ftKb_MsSpecialNEnd_Phys,
        ftKb_MsSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FeSpecialAirNStart = 534
        ftKb_SM_FeSpecialAirNStart,
        ftKb_MF_SpecialNFe,
        FtMoveId_KbSpecialNFe << 24,
        ftKb_MsSpecialAirNStart_Anim,
        ftKb_MsSpecialAirNStart_IASA,
        ftKb_MsSpecialAirNStart_Phys,
        ftKb_MsSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FeSpecialAirNLoop = 535
        ftKb_SM_FeSpecialAirNLoop,
        ftKb_MF_SpecialNFe,
        FtMoveId_KbSpecialNFe << 24,
        ftKb_MsSpecialAirNLoop_Anim,
        ftKb_MsSpecialAirNLoop_IASA,
        ftKb_MsSpecialAirNLoop_Phys,
        ftKb_MsSpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FeSpecialAirNEnd0 = 536
        ftKb_SM_FeSpecialAirNEnd0,
        ftKb_MF_SpecialNFe,
        FtMoveId_KbSpecialNFe << 24,
        ftKb_MsSpecialAirNEnd_Anim,
        ftKb_MsSpecialAirNEnd_IASA,
        ftKb_MsSpecialAirNEnd_Phys,
        ftKb_MsSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_FeSpecialAirNEnd1 = 537
        ftKb_SM_FeSpecialAirNEnd1,
        ftKb_MF_SpecialNFe,
        FtMoveId_KbSpecialNFe << 24,
        ftKb_MsSpecialAirNEnd_Anim,
        ftKb_MsSpecialAirNEnd_IASA,
        ftKb_MsSpecialAirNEnd_Phys,
        ftKb_MsSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GkSpecialNStart = 538
        ftKb_SM_GkSpecialNStart,
        ftKb_MF_SpecialNGk,
        FtMoveId_KbSpecialNGk << 24,
        ftKb_KpSpecialNStart_Anim,
        ftKb_KpSpecialNStart_IASA,
        ftKb_KpSpecialNStart_Phys,
        ftKb_KpSpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GkSpecialN = 539
        ftKb_SM_GkSpecialN,
        ftKb_MF_SpecialNGkLoop,
        FtMoveId_KbSpecialNGk << 24,
        ftKb_KpSpecialN_Anim,
        ftKb_KpSpecialN_IASA,
        ftKb_KpSpecialN_Phys,
        ftKb_KpSpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GkSpecialNEnd = 540
        ftKb_SM_GkSpecialNEnd,
        ftKb_MF_SpecialNGk,
        FtMoveId_KbSpecialNGk << 24,
        ftKb_KpSpecialNEnd_Anim,
        ftKb_KpSpecialNEnd_IASA,
        ftKb_KpSpecialNEnd_Phys,
        ftKb_KpSpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GkSpecialAirNStart = 541
        ftKb_SM_GkSpecialAirNStart,
        ftKb_MF_SpecialAirNGk,
        FtMoveId_KbSpecialNGk << 24,
        ftKb_KpSpecialAirNStart_Anim,
        ftKb_KpSpecialAirNStart_IASA,
        ftKb_KpSpecialAirNStart_Phys,
        ftKb_KpSpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GkSpecialAirN = 542
        ftKb_SM_GkSpecialAirN,
        ftKb_MF_SpecialAirNGkLoop,
        FtMoveId_KbSpecialNGk << 24,
        ftKb_KpSpecialAirN_Anim,
        ftKb_KpSpecialAirN_IASA,
        ftKb_KpSpecialAirN_Phys,
        ftKb_KpSpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftKb_MS_GkSpecialAirNEnd = 543
        ftKb_SM_GkSpecialAirNEnd,
        ftKb_MF_SpecialAirNGk,
        FtMoveId_KbSpecialNGk << 24,
        ftKb_KpSpecialAirNEnd_Anim,
        ftKb_KpSpecialAirNEnd_IASA,
        ftKb_KpSpecialAirNEnd_Phys,
        ftKb_KpSpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
};

HSD_GObjEvent ftKb_Init_803C9CC8[] = {
    ftKb_SpecialN_800EFA40,
    ftKb_SpecialN_800EFAF0,
    ftKb_SpecialN_800EFB4C,
    ftKb_SpecialN_800EFBFC,
    ftKb_SpecialN_800EFC58,
    ftKb_SpecialN_800EFD08,
    ftKb_SpecialN_800F0FC0,
    ftKb_SpecialN_800F10A4,
    NULL,
    NULL,
    ftKb_SpecialN_800EFD64,
    ftKb_SpecialN_800EFE1C,
    ftKb_SpecialN_800EFE80,
    ftKb_SpecialN_800EFF38,
    ftKb_SpecialN_800EFF9C,
    ftKb_SpecialN_800F0054,
    ftKb_SpecialN_800F00B8,
    ftKb_SpecialN_800F0168,
    ftKb_SpecialN_800F01C4,
    ftKb_SpecialN_800F0274,
    ftKb_SpecialN_800F02D0,
    ftKb_SpecialN_800F0380,
    NULL,
    NULL,
    ftKb_SpecialN_800F03DC,
    ftKb_SpecialN_800F0494,
    ftKb_SpecialN_800F04F8,
    ftKb_SpecialN_800F05A8,
    ftKb_SpecialN_800F0604,
    ftKb_SpecialN_800F06B4,
    ftKb_SpecialN_800F10D4,
    ftKb_SpecialN_800F11AC,
    ftKb_SpecialN_800F11F0,
    ftKb_SpecialN_800F12C8,
    ftKb_SpecialN_800F0710,
    ftKb_SpecialN_800F07C0,
    ftKb_SpecialN_800F081C,
    ftKb_SpecialN_800F08D4,
    ftKb_SpecialN_800F0938,
    ftKb_SpecialN_800F09F0,
    ftKb_SpecialN_800F0A54,
    ftKb_SpecialN_800F0B0C,
    ftKb_SpecialN_800F0B70,
    ftKb_SpecialN_800F0C20,
    ftKb_SpecialN_800F130C,
    ftKb_SpecialN_800F13F0,
    ftKb_SpecialN_800F0C7C,
    ftKb_SpecialN_800F0D34,
    ftKb_SpecialN_800F14B4,
    ftKb_SpecialN_800F15D8,
    ftKb_SpecialN_800F0D98,
    ftKb_SpecialN_800F0E48,
    ftKb_SpecialN_800F0EA4,
    ftKb_SpecialN_800F0F5C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_SpecialN_800EFD64,
    ftKb_SpecialN_800EFE1C,
    NULL,
    NULL,
};

HSD_GObjEvent ftKb_Init_803C9DD0[] = {
    ftKb_SpecialN_800F9110,
    ftKb_SpecialNFx_800FE100,
    ftKb_SpecialNCa_800F99BC,
    ftKb_SpecialNDk_800FF8EC,
    ftKb_SpecialN_800F5F68,
    ftKb_SpecialNKp_800FA8B4,
    ftKb_SpecialNLk800FB880,
    ftKb_SpecialNSk_8010612C,
    ftKb_SpecialNNs_800FED38,
    ftKb_SpecialNPe_8010C4D4,
    ftKb_SpecialNIc_80108D64,
    NULL,
    ftKb_SpecialNPk_800F9FD4,
    ftKb_SpecialNSs_800FCF74,
    ftKb_SpecialNYs_8010941C,
    ftKb_SpecialNPr_80101560,
    ftKb_SpecialNMt_80107568,
    ftKb_SpecialNLg_800F9614,
    ftKb_SpecialNMs_8010B2FC,
    ftKb_SpecialNZd_80105B2C,
    ftKb_SpecialNLk800FB880,
    ftKb_SpecialN_800F9110,
    ftKb_SpecialNFx_800FE100,
    ftKb_SpecialNPk_800F9FD4,
    ftKb_SpecialNGw_8010D188,
    ftKb_SpecialNCa_800F99BC,
    ftKb_SpecialNMs_8010B2FC,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_SpecialNKp_800FA8B4,
    NULL,
};

HSD_GObjEvent ftKb_Init_803C9E54[] = {
    ftKb_SpecialNMr_800F93CC,
    ftKb_SpecialNFx_800FE240,
    ftKb_SpecialNCa_800F9A54,
    ftKb_SpecialNDk_800FFA10,
    ftKb_SpecialN_800F6070,
    ftKb_SpecialNKp_800FA958,
    ftKb_SpecialNLk800FBA00,
    ftKb_SpecialNSk_801061E4,
    ftKb_SpecialNNs_800FEDD0,
    ftKb_SpecialNPe_8010C560,
    ftKb_SpecialNIc_80108E14,
    NULL,
    ftKb_SpecialNPk_800FA064,
    ftKb_SpecialNSs_800FD020,
    ftKb_SpecialNYs_801094FC,
    ftKb_SpecialNPr_80101618,
    ftKb_SpecialNMt_80107638,
    ftKb_SpecialNLg_800F9684,
    ftKb_SpecialNMs_8010B4A0,
    ftKb_SpecialNZd_80105BA8,
    ftKb_SpecialNLk800FBA00,
    ftKb_SpecialNMr_800F93CC,
    ftKb_SpecialNFx_800FE240,
    ftKb_SpecialNPk_800FA064,
    ftKb_SpecialNGw_8010D204,
    ftKb_SpecialNCa_800F9A54,
    ftKb_SpecialNMs_8010B4A0,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_SpecialNKp_800FA958,
    NULL,
};

typedef struct ftKirby_UnkArrayThing {
    /*  +0 */ int x0;
    /*  +4 */ int x4;
    /*  +8 */ int x8;
    /*  +C */ int xC;
    /* +10 */ int x10;
    /* +14 */ int x14;
    /* +18 */ int x18;
    /* +1C */ int x1C;
    /* +20 */ int x20;
    /* +24 */ int x24;
    /* +28 */ int x28;
    /* +2C */ int x2C;
} ftKirby_UnkArrayThing;

ftKirby_UnkArrayThing ftKb_Init_803C9ED8 = { 0 };
ftKirby_UnkArrayThing ftKb_Init_803C9F08 = { 0 };
ftKirby_UnkArrayThing ftKb_Init_803C9F38 = { 0 };
ftKirby_UnkArrayThing ftKb_Init_803C9F68 = { 0 };
ftKirby_UnkArrayThing ftKb_Init_803C9F98 = { 0 };

ftKirby_UnkArrayThing* ftKb_Init_803C9FC8[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    &ftKb_Init_803C9ED8,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &ftKb_Init_803C9F08,
    &ftKb_Init_803C9F38,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &ftKb_Init_803C9F68,
    NULL,
    &ftKb_Init_803C9F98,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

MotionState ftKb_Init_UnkMotionStates0[] = {
    {
        ftCo_SM_RunBrake,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C737C,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Kneebend,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C737C,
        NULL,
        NULL,
    },
    {
        ftCo_SM_JumpF,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C737C,
        NULL,
        NULL,
    },
    {
        ftCo_SM_JumpB,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C7414,
        NULL,
        NULL,
    },
};

/* 0EE854 */ static void ftKb_Init_800EE854(void);
/* 0EE874 */ static void ftKb_Init_800EE874(void);
/* 0EE8B0 */ static void ftKb_Init_800EE8B0(void);
/* 0EE8EC */ static void ftKb_Init_800EE8EC(void);
/* 0EE904 */ static void ftKb_Init_800EE904(void);
/* 0F1CA0 */ static bool fn_800F1CA0(HSD_GObj* gobj);
/* 105FEC */ static void fn_800F6AC8(HSD_GObj* gobj);
/* 105FEC */ static void fn_80105FEC(void);
/* 10C288 */ static void fn_8010C288(HSD_GObj* gobj);

jtbl_t ftKb_Init_803CA0CC = {
    ftKb_Init_800EE854, ftKb_Init_800EE904, ftKb_Init_800EE904,
    ftKb_Init_800EE904, ftKb_Init_800EE8EC, ftKb_Init_800EE904,
    ftKb_Init_800EE904, ftKb_Init_800EE904, ftKb_Init_800EE904,
    ftKb_Init_800EE904, ftKb_Init_800EE874, ftKb_Init_800EE904,
    ftKb_Init_800EE904, ftKb_Init_800EE8B0,
};

char ftKb_Init_assert_msg_0[] = "fighter parts model dobj num over!\n";
char ftKb_Init_assert_msg_1[] = "ftkirby.c";
char ftKb_Init_assert_msg_2[] = "fighter dobj num over!\n";

/* static */ void ftKb_SpecialN_800F1708(void);
/* static */ void ftKb_SpecialN_800F171C(void);
/* static */ void ftKb_SpecialN_800F1730(void);
/* static */ void ftKb_SpecialN_800F1744(void);
/* static */ void ftKb_SpecialN_800F1764(void);
/* static */ void ftKb_SpecialN_800F1784(void);
/* static */ void ftKb_SpecialN_800F17A4(void);
/* static */ void ftKb_SpecialN_800F17C4(void);
/* static */ void ftKb_SpecialN_800F17E4(void);
/* static */ void ftKb_SpecialN_800F17F8(void);
/* static */ void ftKb_SpecialN_800F1818(void);
/* static */ void ftKb_SpecialN_800F1838(void);
/* static */ void ftKb_SpecialN_800F1858(void);
/* static */ void ftKb_SpecialN_800F186C(void);
/* static */ void ftKb_SpecialN_800F1880(void);
/* static */ void ftKb_SpecialN_800F1894(void);
/* static */ void ftKb_SpecialN_800F18B4(void);
/* static */ void ftKb_SpecialN_800F18C8(void);
/* static */ void ftKb_SpecialN_800F18E8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);

jtbl_t ftKb_Init_803CA14C = {
    ftKb_SpecialN_800F1708, ftKb_SpecialN_800F1764, ftKb_SpecialN_800F18F8,
    ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F186C,
    ftKb_SpecialN_800F17A4, ftKb_SpecialN_800F1894, ftKb_SpecialN_800F17F8,
    ftKb_SpecialN_800F1744, ftKb_SpecialN_800F1730, ftKb_SpecialN_800F18F8,
    ftKb_SpecialN_800F1818, ftKb_SpecialN_800F1858, ftKb_SpecialN_800F18E8,
    ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F17E4, ftKb_SpecialN_800F171C,
    ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F17C4,
    ftKb_SpecialN_800F18B4, ftKb_SpecialN_800F1784, ftKb_SpecialN_800F1838,
    ftKb_SpecialN_800F18C8, ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F18F8,
    ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F18F8,
    ftKb_SpecialN_800F18F8, ftKb_SpecialN_800F1880,
};

/* static */ void ftKb_SpecialN_800F19E8(void);
/* static */ void ftKb_SpecialN_800F19F4(void);
/* static */ void ftKb_SpecialN_800F1A00(void);
/* static */ void ftKb_SpecialN_800F1A0C(void);
/* static */ void ftKb_SpecialN_800F1A20(void);
/* static */ void ftKb_SpecialN_800F1A2C(void);
/* static */ void ftKb_SpecialN_800F1A38(void);
/* static */ void ftKb_SpecialN_800F1A44(void);
/* static */ void ftKb_SpecialN_800F1A50(void);
/* static */ void ftKb_SpecialN_800F1A64(void);
/* static */ void ftKb_SpecialN_800F1A70(void);
/* static */ void ftKb_SpecialN_800F1A78(void);

jtbl_t ftKb_Init_803CA1CC = {
    ftKb_SpecialN_800F1A78, ftKb_SpecialN_800F1A00, ftKb_SpecialN_800F1A78,
    ftKb_SpecialN_800F1A64, ftKb_SpecialN_800F1A78, ftKb_SpecialN_800F1A78,
    ftKb_SpecialN_800F1A0C, ftKb_SpecialN_800F1A44, ftKb_SpecialN_800F1A2C,
    ftKb_SpecialN_800F19F4, ftKb_SpecialN_800F19E8, ftKb_SpecialN_800F1A78,
    ftKb_SpecialN_800F1A78, ftKb_SpecialN_800F1A38, ftKb_SpecialN_800F1A50,
    ftKb_SpecialN_800F1A78, ftKb_SpecialN_800F1A20, ftKb_SpecialN_800F1A78,
    ftKb_SpecialN_800F1A78, ftKb_SpecialN_800F1A78, ftKb_SpecialN_800F1A0C,
    ftKb_SpecialN_800F1A78, ftKb_SpecialN_800F1A00, ftKb_SpecialN_800F1A78,
    ftKb_SpecialN_800F1A70,
};

/* static */ void ftKb_SpecialN_800F1AC8(void);
/* static */ void ftKb_SpecialN_800F1AD4(void);
/* static */ void ftKb_SpecialN_800F1AE0(void);
/* static */ void ftKb_SpecialN_800F1AEC(void);
/* static */ void ftKb_SpecialN_800F1B00(void);
/* static */ void ftKb_SpecialN_800F1B0C(void);
/* static */ void ftKb_SpecialN_800F1B18(void);
/* static */ void ftKb_SpecialN_800F1B24(void);
/* static */ void ftKb_SpecialN_800F1B30(void);
/* static */ void ftKb_SpecialN_800F1B44(void);
/* static */ void ftKb_SpecialN_800F1B50(void);
/* static */ void ftKb_SpecialN_800F1B58(void);

jtbl_t ftKb_Init_803CA230 = {
    ftKb_SpecialN_800F1B58, ftKb_SpecialN_800F1AE0, ftKb_SpecialN_800F1B58,
    ftKb_SpecialN_800F1B44, ftKb_SpecialN_800F1B58, ftKb_SpecialN_800F1B58,
    ftKb_SpecialN_800F1AEC, ftKb_SpecialN_800F1B24, ftKb_SpecialN_800F1B0C,
    ftKb_SpecialN_800F1AD4, ftKb_SpecialN_800F1AC8, ftKb_SpecialN_800F1B58,
    ftKb_SpecialN_800F1B58, ftKb_SpecialN_800F1B18, ftKb_SpecialN_800F1B30,
    ftKb_SpecialN_800F1B58, ftKb_SpecialN_800F1B00, ftKb_SpecialN_800F1B58,
    ftKb_SpecialN_800F1B58, ftKb_SpecialN_800F1B58, ftKb_SpecialN_800F1AEC,
    ftKb_SpecialN_800F1B58, ftKb_SpecialN_800F1AE0, ftKb_SpecialN_800F1B58,
    ftKb_SpecialN_800F1B50,
};

/* static */ void ftKb_SpecialN_800F1CC8(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);

jtbl_t ftKb_Init_803CA294 = {
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CC8,
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CD0,
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CC8, ftKb_SpecialN_800F1CD0,
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CC8, ftKb_SpecialN_800F1CC8,
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CC8,
};

/* static */ void ftKb_SpecialN_800F1D00(void);
/* static */ void ftKb_SpecialN_800F1D08(void);

jtbl_t ftKb_Init_803CA2CC = {
    ftKb_SpecialN_800F1D08, ftKb_SpecialN_800F1D08, ftKb_SpecialN_800F1D00,
    ftKb_SpecialN_800F1D08, ftKb_SpecialN_800F1D08, ftKb_SpecialN_800F1D08,
    ftKb_SpecialN_800F1D08, ftKb_SpecialN_800F1D00, ftKb_SpecialN_800F1D08,
    ftKb_SpecialN_800F1D08, ftKb_SpecialN_800F1D00, ftKb_SpecialN_800F1D00,
    ftKb_SpecialN_800F1D08, ftKb_SpecialN_800F1D00, NULL
};

char ftKb_Init_DatFilename[] = "PlKb.dat";
char ftKb_Init_DataName[] = "ftDataKirby";
char ftKb_Init_803CA320[] = "PlKbNr.dat";
char ftKb_Init_803CA32C[] = "PlyKirby5K_Share_joint";
char ftKb_Init_803CA344[] = "PlyKirby5K_Share_matanim_joint";
char ftKb_Init_803CA364[] = "PlKbYe.dat";
char ftKb_Init_803CA370[] = "PlyKirby5KYe_Share_joint";
char ftKb_Init_803CA38C[] = "PlyKirby5KYe_Share_matanim_joint";
char ftKb_Init_803CA3B0[] = "PlKbBu.dat";
char ftKb_Init_803CA3BC[] = "PlyKirby5KBu_Share_joint";
char ftKb_Init_803CA3D8[] = "PlyKirby5KBu_Share_matanim_joint";
char ftKb_Init_803CA3FC[] = "PlKbRe.dat";
char ftKb_Init_803CA408[] = "PlyKirby5KRe_Share_joint";
char ftKb_Init_803CA424[] = "PlyKirby5KRe_Share_matanim_joint";
char ftKb_Init_803CA448[] = "PlKbGr.dat";
char ftKb_Init_803CA454[] = "PlyKirby5KGr_Share_joint";
char ftKb_Init_803CA470[] = "PlyKirby5KGr_Share_matanim_joint";
char ftKb_Init_803CA494[] = "PlKbWh.dat";
char ftKb_Init_803CA4A0[] = "PlyKirby5KWh_Share_joint";
char ftKb_Init_803CA4BC[] = "PlyKirby5KWh_Share_matanim_joint";
char ftKb_Init_AnimDatFilename[] = "PlKbAJ.dat";

Fighter_DemoStrings ftKb_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileKirby",
    "ftDemoIntroMotionFileKirby",
    "ftDemoEndingMotionFileKirby",
    "ftDemoViWaitMotionFileKirby",
};

char* ftKb_Init_803CA5A4[] = {
    "ftDemoVi0501MotionFileKirby",
    NULL,
    NULL,
    "ftDemoVi0502MotionFileKirby",
};

Fighter_CostumeStrings ftKb_Init_CostumeStrings[] = {
    { ftKb_Init_803CA320, ftKb_Init_803CA32C, ftKb_Init_803CA344 },
    { ftKb_Init_803CA364, ftKb_Init_803CA370, ftKb_Init_803CA38C },
    { ftKb_Init_803CA3B0, ftKb_Init_803CA3BC, ftKb_Init_803CA3D8 },
    { ftKb_Init_803CA3FC, ftKb_Init_803CA408, ftKb_Init_803CA424 },
    { ftKb_Init_803CA448, ftKb_Init_803CA454, ftKb_Init_803CA470 },
    { ftKb_Init_803CA494, ftKb_Init_803CA4A0, ftKb_Init_803CA4BC },
};

typedef struct ftKirby_CopyName {
    char* filename;
    char* name;
} ftKirby_CopyName;

ftKirby_CopyName ftKb_Init_803CA9D0[FTKIND_MAX] = {
    { "PlKbCpMr.dat", "ftDataKirbyCopyMario" },
    { "PlKbCpFx.dat", "ftDataKirbyCopyFox" },
    { "PlKbCpCa.dat", "ftDataKirbyCopyCaptain" },
    { "PlKbCpDk.dat", "ftDataKirbyCopyDonkey" },
    { NULL, NULL },
    { "PlKbCpKp.dat", "ftDataKirbyCopyKoopa" },
    { "PlKbCpLk.dat", "ftDataKirbyCopyLink" },
    { "PlKbCpSk.dat", "ftDataKirbyCopySeak" },
    { "PlKbCpNs.dat", "ftDataKirbyCopyNess" },
    { "PlKbCpPe.dat", "ftDataKirbyCopyPeach" },
    { "PlKbCpPp.dat", "ftDataKirbyCopyPopo" },
    { NULL, NULL },
    { "PlKbCpPk.dat", "ftDataKirbyCopyPikachu" },
    { "PlKbCpSs.dat", "ftDataKirbyCopySamus" },
    { "PlKbCpYs.dat", "ftDataKirbyCopyYoshi" },
    { "PlKbCpPr.dat", "ftDataKirbyCopyPurin" },
    { "PlKbCpMt.dat", "ftDataKirbyCopyMewtwo" },
    { "PlKbCpLg.dat", "ftDataKirbyCopyLuigi" },
    { "PlKbCpMs.dat", "ftDataKirbyCopyMars" },
    { "PlKbCpZd.dat", "ftDataKirbyCopyZelda" },
    { "PlKbCpCl.dat", "ftDataKirbyCopyClink" },
    { "PlKbCpDr.dat", "ftDataKirbyCopyDrmario" },
    { "PlKbCpFc.dat", "ftDataKirbyCopyFalco" },
    { "PlKbCpPc.dat", "ftDataKirbyCopyPichu" },
    { "PlKbCpGw.dat", "ftDataKirbyCopyGamewatch" },
    { "PlKbCpGn.dat", "ftDataKirbyCopyGanon" },
    { "PlKbCpFe.dat", "ftDataKirbyCopyEmblem" },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
};

char ftKb_Init_803CAAD8[] = "PlKbNrCpDk.dat";
char ftKb_Init_803CAAE8[] = "PlyKirbyDk_Share_joint";
char ftKb_Init_803CAB00[] = "PlyKirbyDk_Share_matanim_joint";
char ftKb_Init_803CAB20[] = "PlKbYeCpDk.dat";
char ftKb_Init_803CAB30[] = "PlyKirbyDkYe_Share_joint";
char ftKb_Init_803CAB4C[] = "PlyKirbyDkYe_Share_matanim_joint";
char ftKb_Init_803CAB70[] = "PlKbBuCpDk.dat";
char ftKb_Init_803CAB80[] = "PlyKirbyDkBu_Share_joint";
char ftKb_Init_803CAB9C[] = "PlyKirbyDkBu_Share_matanim_joint";
char ftKb_Init_803CABC0[] = "PlKbReCpDk.dat";
char ftKb_Init_803CABD0[] = "PlyKirbyDkRe_Share_joint";
char ftKb_Init_803CABEC[] = "PlyKirbyDkRe_Share_matanim_joint";
char ftKb_Init_803CAC10[] = "PlKbGrCpDk.dat";
char ftKb_Init_803CAC20[] = "PlyKirbyDkGr_Share_joint";
char ftKb_Init_803CAC3C[] = "PlyKirbyDkGr_Share_matanim_joint";
char ftKb_Init_803CAC60[] = "PlKbWhCpDk.dat";
char ftKb_Init_803CAC70[] = "PlyKirbyDkWh_Share_joint";
char ftKb_Init_803CAC8C[] = "PlyKirbyDkWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CACB0[] = {
    { ftKb_Init_803CAAD8, ftKb_Init_803CAAE8, ftKb_Init_803CAB00 },
    { ftKb_Init_803CAB20, ftKb_Init_803CAB30, ftKb_Init_803CAB4C },
    { ftKb_Init_803CAB70, ftKb_Init_803CAB80, ftKb_Init_803CAB9C },
    { ftKb_Init_803CABC0, ftKb_Init_803CABD0, ftKb_Init_803CABEC },
    { ftKb_Init_803CAC10, ftKb_Init_803CAC20, ftKb_Init_803CAC3C },
    { ftKb_Init_803CAC60, ftKb_Init_803CAC70, ftKb_Init_803CAC8C },
};

char ftKb_Init_803CACF8[] = "PlKbNrCpPr.dat";
char ftKb_Init_803CAD08[] = "PlyKirbyPr_Share_joint";
char ftKb_Init_803CAD20[] = "PlyKirbyPr_Share_matanim_joint";
char ftKb_Init_803CAD40[] = "PlKbYeCpPr.dat";
char ftKb_Init_803CAD50[] = "PlyKirbyPrYe_Share_joint";
char ftKb_Init_803CAD6C[] = "PlyKirbyPrYe_Share_matanim_joint";
char ftKb_Init_803CAD90[] = "PlKbBuCpPr.dat";
char ftKb_Init_803CADA0[] = "PlyKirbyPrBu_Share_joint";
char ftKb_Init_803CADBC[] = "PlyKirbyPrBu_Share_matanim_joint";
char ftKb_Init_803CADE0[] = "PlKbReCpPr.dat";
char ftKb_Init_803CADF0[] = "PlyKirbyPrRe_Share_joint";
char ftKb_Init_803CAE0C[] = "PlyKirbyPrRe_Share_matanim_joint";
char ftKb_Init_803CAE30[] = "PlKbGrCpPr.dat";
char ftKb_Init_803CAE40[] = "PlyKirbyPrGr_Share_joint";
char ftKb_Init_803CAE5C[] = "PlyKirbyPrGr_Share_matanim_joint";
char ftKb_Init_803CAE80[] = "PlKbWhCpPr.dat";
char ftKb_Init_803CAE90[] = "PlyKirbyPrWh_Share_joint";
char ftKb_Init_803CAEAC[] = "PlyKirbyPrWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CAED0[] = {
    { ftKb_Init_803CACF8, ftKb_Init_803CAD08, ftKb_Init_803CAD20 },
    { ftKb_Init_803CAD40, ftKb_Init_803CAD50, ftKb_Init_803CAD6C },
    { ftKb_Init_803CAD90, ftKb_Init_803CADA0, ftKb_Init_803CADBC },
    { ftKb_Init_803CADE0, ftKb_Init_803CADF0, ftKb_Init_803CAE0C },
    { ftKb_Init_803CAE30, ftKb_Init_803CAE40, ftKb_Init_803CAE5C },
    { ftKb_Init_803CAE80, ftKb_Init_803CAE90, ftKb_Init_803CAEAC },
};

char ftKb_Init_803CAF18[] = "PlKbNrCpMt.dat";
char ftKb_Init_803CAF28[] = "PlyKirbyMt_Share_joint";
char ftKb_Init_803CAF40[] = "PlyKirbyMt_Share_matanim_joint";
char ftKb_Init_803CAF60[] = "PlKbYeCpMt.dat";
char ftKb_Init_803CAF70[] = "PlyKirbyMtYe_Share_joint";
char ftKb_Init_803CAF8C[] = "PlyKirbyMtYe_Share_matanim_joint";
char ftKb_Init_803CAFB0[] = "PlKbBuCpMt.dat";
char ftKb_Init_803CAFC0[] = "PlyKirbyMtBu_Share_joint";
char ftKb_Init_803CAFDC[] = "PlyKirbyMtBu_Share_matanim_joint";
char ftKb_Init_803CB000[] = "PlKbReCpMt.dat";
char ftKb_Init_803CB010[] = "PlyKirbyMtRe_Share_joint";
char ftKb_Init_803CB02C[] = "PlyKirbyMtRe_Share_matanim_joint";
char ftKb_Init_803CB050[] = "PlKbGrCpMt.dat";
char ftKb_Init_803CB060[] = "PlyKirbyMtGr_Share_joint";
char ftKb_Init_803CB07C[] = "PlyKirbyMtGr_Share_matanim_joint";
char ftKb_Init_803CB0A0[] = "PlKbWhCpMt.dat";
char ftKb_Init_803CB0B0[] = "PlyKirbyMtWh_Share_joint";
char ftKb_Init_803CB0CC[] = "PlyKirbyMtWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CB0F0[] = {
    { ftKb_Init_803CAF18, ftKb_Init_803CAF28, ftKb_Init_803CAF40 },
    { ftKb_Init_803CAF60, ftKb_Init_803CAF70, ftKb_Init_803CAF8C },
    { ftKb_Init_803CAFB0, ftKb_Init_803CAFC0, ftKb_Init_803CAFDC },
    { ftKb_Init_803CB000, ftKb_Init_803CB010, ftKb_Init_803CB02C },
    { ftKb_Init_803CB050, ftKb_Init_803CB060, ftKb_Init_803CB07C },
    { ftKb_Init_803CB0A0, ftKb_Init_803CB0B0, ftKb_Init_803CB0CC },
};

char ftKb_Init_803CB138[] = "PlKbNrCpFc.dat";
char ftKb_Init_803CB148[] = "PlyKirbyFc_Share_joint";
char ftKb_Init_803CB160[] = "PlyKirbyFc_Share_matanim_joint";
char ftKb_Init_803CB180[] = "PlKbYeCpFc.dat";
char ftKb_Init_803CB190[] = "PlyKirbyFcYe_Share_joint";
char ftKb_Init_803CB1AC[] = "PlyKirbyFcYe_Share_matanim_joint";
char ftKb_Init_803CB1D0[] = "PlKbBuCpFc.dat";
char ftKb_Init_803CB1E0[] = "PlyKirbyFcBu_Share_joint";
char ftKb_Init_803CB1FC[] = "PlyKirbyFcBu_Share_matanim_joint";
char ftKb_Init_803CB220[] = "PlKbReCpFc.dat";
char ftKb_Init_803CB230[] = "PlyKirbyFcRe_Share_joint";
char ftKb_Init_803CB24C[] = "PlyKirbyFcRe_Share_matanim_joint";
char ftKb_Init_803CB270[] = "PlKbGrCpFc.dat";
char ftKb_Init_803CB280[] = "PlyKirbyFcGr_Share_joint";
char ftKb_Init_803CB29C[] = "PlyKirbyFcGr_Share_matanim_joint";
char ftKb_Init_803CB2C0[] = "PlKbWhCpFc.dat";
char ftKb_Init_803CB2D0[] = "PlyKirbyFcWh_Share_joint";
char ftKb_Init_803CB2EC[] = "PlyKirbyFcWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CB310[] = {
    { ftKb_Init_803CB138, ftKb_Init_803CB148, ftKb_Init_803CB160 },
    { ftKb_Init_803CB180, ftKb_Init_803CB190, ftKb_Init_803CB1AC },
    { ftKb_Init_803CB1D0, ftKb_Init_803CB1E0, ftKb_Init_803CB1FC },
    { ftKb_Init_803CB220, ftKb_Init_803CB230, ftKb_Init_803CB24C },
    { ftKb_Init_803CB270, ftKb_Init_803CB280, ftKb_Init_803CB29C },
    { ftKb_Init_803CB2C0, ftKb_Init_803CB2D0, ftKb_Init_803CB2EC },
};

char ftKb_Init_803CB358[] = "PlKbNrCpGw.dat";
char ftKb_Init_803CB368[] = "PlyKirbyGw_Share_joint";
char ftKb_Init_803CB380[] = "PlyKirbyGw_Share_matanim_joint";

Fighter_CostumeStrings ftKb_Init_803CB3A0[] = {
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
    { ftKb_Init_803CB358, ftKb_Init_803CB368, ftKb_Init_803CB380 },
};

Fighter_CostumeStrings* ftKb_Init_803CB3E8[] = {
    NULL,
    NULL,
    NULL,
    ftKb_Init_803CACB0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_Init_803CAED0,
    ftKb_Init_803CB0F0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_Init_803CB310,
    NULL,
    ftKb_Init_803CB3A0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

s8 ftKb_Init_803CB46C[FTKIND_MAX] = {
    32, 33, 38, 39, -1, 41, 35, 21, 42, 45, 46, 46, 36, 34, 40, 43, 44,
    37, 20, 21, 35, 32, 33, 36, -1, 47, 48, -1, -1, -1, -1, -1, -1,
};

bool ftKb_Init_803CB490[] = {
    false, true,  false, false, false, false, true,  true,
    false, false, false, true,  true,  true,  false, false,
    true,  true,  true,  true,  false, true,  true,
};

struct ftKb_Init_803CB4EC {
    int ints[6];
    Vec3 vec;
} ftKb_Init_803CB4EC = {
    { 0, 2, 3, 4, 5, 6 },
    { 0.0F, 1.0F, 0.0F },
};

char ftKb_Init_803CB510[] = "Other Dead_Proc Existence";
char ftKb_Init_803CB52C[] = "ftkirbyspecials.c";

enum_t ftKb_Init_803CB540[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
};

u32 ftKb_Init_803CB6C0[] = { 260006, 260009, 260012, 260015, 260018, 0 };

char ftKb_Init_803CB6D8[] = "ftToSpecialNFox::Caution!!!\n";
char ftKb_Init_803CB6F8[] = "ftkirbyspecialfox.c\0\0\0\0";

Vec4 ftKb_Init_803CB710 = { 0.65F, 0.7F, 0.8F, 1.0F };
Vec4 ftKb_Init_803CB720 = { 1.1F, 1.35F, 1.3F, 1.2F };

char ftKb_Init_assert_msg_3[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 ftKb_Init_803CB758[] = {
    { +8, +0, -4 },
    { +4, +4, +4 },
};

float ftKb_Init_803CB770[] = {
    -1, -0.75, -0.5, -0.25, 0, +0.25, +0.5, +0.75, +1,
};

/* static */ void ftKb_SpecialNSk_80106464(void);
/* static */ void ftKb_SpecialNSk_80106474(void);

jtbl_t ftKb_Init_803CB794 = {
    ftKb_SpecialNSk_80106474, ftKb_SpecialNSk_80106474,
    ftKb_SpecialNSk_80106464, ftKb_SpecialNSk_80106474,
    ftKb_SpecialNSk_80106474, ftKb_SpecialNSk_80106464,
    ftKb_SpecialNSk_80106474, ftKb_SpecialNSk_80106474,
    ftKb_SpecialNSk_80106464, ftKb_SpecialNSk_80106474,
    ftKb_SpecialNSk_80106474, ftKb_SpecialNSk_80106464,
    ftKb_SpecialNSk_80106474, ftKb_SpecialNSk_80106474,
    ftKb_SpecialNSk_80106464, ftKb_SpecialNSk_80106474,
    ftKb_SpecialNSk_80106474, ftKb_SpecialNSk_80106464,
};

/* static */ void ftKb_SpecialNSk_801066B4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);

jtbl_t ftKb_Init_803CB7DC = {
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066B4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066B4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066B4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066B4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066B4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066C4,
    ftKb_SpecialNSk_801066B4,
    NULL,
};

u32 ftKb_Init_803CB828[] = { 0x00030DB9, 0x00030DBC, 0x00030DBF, 0x00030DC2 };

float const ftKb_Init_803B7548[10] = { 0 };
Vec3 const ftKb_Init_803B7570 = { 0, 4, 0 };
Vec3 const ftKb_Init_803B757C = { 0, 4, 0 };

void ftKb_Init_800EE528(void)
{
    /// @todo Bad cast.
    s32* number_list = (s32*) &ft_80459B88.x0;
    ftKirby_UnkArrayThing** struct_list = ftKb_Init_803C9FC8;

    s32 i;
    for (i = 0; i < FTKIND_MAX; i++) {
        ftKirby_UnkArrayThing* unk_struct;
        number_list[i] = 0;
        unk_struct = struct_list[i];
        if (unk_struct) {
            unk_struct->x0 = 0;
            unk_struct = struct_list[i];
            unk_struct->x4 = 0;
            unk_struct = struct_list[i];
            unk_struct->x8 = 0;
            unk_struct = struct_list[i];
            unk_struct->xC = 0;
            unk_struct = struct_list[i];
            unk_struct->x10 = 0;
            unk_struct = struct_list[i];
            unk_struct->x14 = 0;
            unk_struct = struct_list[i];
            unk_struct->x18 = 0;
            unk_struct = struct_list[i];
            unk_struct->x1C = 0;
            unk_struct = struct_list[i];
            unk_struct->x20 = 0;
            unk_struct = struct_list[i];
            unk_struct->x24 = 0;
            unk_struct = struct_list[i];
            unk_struct->x28 = 0;
            unk_struct = struct_list[i];
            unk_struct->x2C = 0;
        }
    }
}

void ftKb_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    fp->fv.kb.hat.x0 = 0;
    fp->fv.kb.hat.x4 = HSD_Randi(5) + 1;
    fp->fv.kb.hat.jobj = NULL;
    fp->fv.kb.hat.kind = 4;
    fp->fv.kb.hat.x14.data = 0;
    fp->fv.kb.x60 = 0;
    fp->fv.kb.x64 = 0;
    if (Player_GetFlagsBit1(fp->player_id) &&
        Player_GetUnk4D(fp->player_id) != 4)
    {
        ftKb_SpecialN_800F1BAC(gobj, Player_GetUnk4D(fp->player_id), 0);
    }
}

void ftKb_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftKb_DatAttrs);

    fp->can_multijump = true;
    fp->x2D0 = fp->dat_attrs;
    fp->fv.kb.hat.x8_b0 = Player_GetFlagsAEBit1(fp->player_id);
    it_8026B3F8(item_list[0], 50);
    it_8026B3F8(item_list[1], 51);
    it_8026B3F8(item_list[2], 52);
    it_8026B3F8(item_list[3], 53);
}

void ftKb_Init_800EE74C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialAirLw_800F5524(gobj);
    ftKb_AttackDashAir_800F22D4(gobj);
    ftKb_SpecialAirLw_800F5318(gobj);
    ftKb_SpecialN_800F9090(gobj);
    ftKb_SpecialN_800F19AC(gobj);
    ftKb_SpecialN_800F5D04(gobj, false);
    fp->death3_cb = NULL;
}

void ftKb_Init_800EE7B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialAirLw_800F5524(gobj);
    ftKb_AttackDashAir_800F22D4(gobj);
    ftKb_SpecialAirLw_800F5318(gobj);
    ftKb_SpecialN_800F9090(gobj);
    ftKb_SpecialN_800F1A8C(gobj);
    fp->death1_cb = NULL;
}

void ftKb_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    s32 _[2];
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_DONKEY:
        if (fp->fv.kb.xBC == da->specialn_dk_swings_to_full_charge) {
            ftCo_800BFFD0(fp, 58, 0);
        }
        break;
    case FTKIND_SAMUS:
        if (fp->fv.kb.xA8 == da->specialn_ss_charge_time) {
            ftCo_800BFFD0(fp, 54, 0);
        }
        break;
    case FTKIND_MEWTWO:
        if (fp->fv.kb.x9C == da->specialn_mt_charge_time) {
            ftCo_800BFFD0(fp, 93, 0);
            return;
        }
        break;
    case FTKIND_SEAK:
        if (fp->fv.kb.xB4 == 6) {
            ftCo_800BFFD0(fp, 87, 0);
        }
        break;
    default:
        break;
    }
}

void ftKb_Init_OnItemPickup(HSD_GObj* gobj, bool arg1)
{
    Fighter* fp = getFighter(gobj);
    if (!it_8026B2B4(fp->item_gobj)) {
        switch (it_8026B320(fp->item_gobj)) {
        case 1:
            ftAnim_80070FB4(gobj, 1, 0);
            break;
        case 3:
            ftAnim_80070FB4(gobj, 1, 1);
            break;
        case 4:
            ftAnim_80070FB4(gobj, 1, 2);
            break;
        }
        if (arg1) {
            ftAnim_80070C48(gobj, 1);
        }
    }
}

void ftKb_Init_OnItemInvisible(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (it_8026B2B4(fp->item_gobj) == 0) {
        ftAnim_80070CC4(gobj, 1);
    }
}

void ftKb_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftKb_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftKb_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftKb_DatAttrs);
}

void ftKb_Init_800EEB00(Fighter_GObj* gobj, ArticleDynamicBones** arg1)
{
    *arg1 = ft_80459B88.hats[FTKIND_PICHU]->hat_dynamics[4]->ftDynamicBones;
}

void ftKb_Init_800EEB1C(Fighter_GObj* gobj, s32* arg1)
{
    *arg1 = ft_80459B88.hats[FTKIND_PICHU]->hat_dynamics[4]->x4;
}

void ftKb_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftKb_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftKb_Init_UnkDemoCallbacks0(int kind, int* out1, int* out2)
{
    if (kind == 14) {
        goto case14;
    }
    if (kind >= 14) {
        return;
    }
    if (kind < 11) {
        return;
    }
    *out1 = 14;
    *out2 = 16;
    return;
case14:
    *out2 = 17;
    *out1 = 17;
}

char* ftKb_Init_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 11:
        offset = 14;
        break;
    case 14:
        offset = 17;
    }

    return ftKb_Init_803CA5A4[offset - 14];
}
/// #ftKb_SpecialN_800EEC34

/// #ftKb_SpecialN_800EED50

void ftKb_Init_UnkMotionStates5(void)
{
    Player_80031DC8(ftKb_SpecialN_800EED50);
}

/// #ftKb_SpecialN_800EEEC4

/// #ftKb_UnkMtxFunc0

HSD_JObj* ftKb_Init_UnkMotionStates6(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.kb.hat.jobj) {
        return fp->fv.kb.hat.jobj;
    }

    /// @todo What???
    return (HSD_JObj*) gobj;
}

/// #ftKb_SpecialN_800EF040

/// #ftKb_SpecialN_800EF0E4

/// #ftKb_SpecialN_800EF35C

/// #ftKb_SpecialN_800EF438

/// #ftKb_SpecialN_800EF69C

/// #ftKb_UnkIntBoolFunc0

void ftKb_Init_UnkCallbackPairs0_0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.x14.data != NULL && fp->fv.kb.hat.jobj == NULL) {
        ftAnim_800705E0(&fp->fv.kb.x44);
    }
}

void ftKb_Init_UnkCallbackPairs0_1(Fighter_GObj* gobj, int arg1, float arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.x14.data != NULL && fp->fv.kb.hat.jobj == NULL) {
        ftAnim_80070458_proto(fp, &fp->fv.kb.x44, arg1);
    }
}
void ftKb_SpecialN_800EFA40(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4);
    if (fp->fv.kb.hat.jobj == NULL) {
        Kirby_Unk* unk = ft_80459B88.x0;
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(unk->x0);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&unk->x4, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

static void ftKb_SpecialN_800EFAF0_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj != NULL) {
        HSD_JObjRemoveAll(fp->fv.kb.hat.jobj);
        fp->fv.kb.hat.jobj = NULL;
        HSD_ObjFree(&fighter_x2040_alloc_data, fp->fv.kb.hat.x14.data);
        fp->fv.kb.hat.x14.data = NULL;
    }
}

void ftKb_SpecialN_800EFAF0(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800EFB4C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_MARIO];

        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);

        // Fighter_InitPObj
        ftPartsPObjSetDefaultClass();

        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);

        fp->x2225_b2 = true;

        // Fighter_InitPObj2
        ftPartsPObjClearDefaultClass();

        // Fighter_IndexFtPartsDObjs
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        {
            // Fighter_InitFtPartsModel(FtPartsDesc *ftpartsdesc, FtPartsVis
            // *unk, int index, FtParts *ftparts, FtParts *ftparts2);
            ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0,
                             &fp->fv.kb.hat.x14, &fp->fv.kb.hat.x14);
        }
    }
}

void ftKb_SpecialN_800EFBFC(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800EFC58(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_FOX];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800EFD08(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

/// #ftKb_SpecialN_800EFD64

void ftKb_SpecialN_800EFE1C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800EFE80(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.kb.hat.jobj == NULL) {
        Fighter* fp = gobj->user_data;
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_KOOPA];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800EFF38(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800EFF9C(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.kb.hat.jobj == NULL) {
        Fighter* fp = gobj->user_data;
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_LINK];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800F0054(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F00B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_SEAK];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800F0168(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F01C4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_NESS];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800F0274(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F02D0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_PEACH];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800F0380(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F03DC(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.kb.hat.jobj == NULL) {
        Fighter* fp = gobj->user_data;
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_NANA];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800F0494(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F04F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_PIKACHU];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800F05A8(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F0604(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_SAMUS];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800F06B4(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F0710(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_MEWTWO];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800F07C0(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F081C(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.kb.hat.jobj == NULL) {
        Fighter* fp = gobj->user_data;
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_LUIGI];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800F08D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0938(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.kb.hat.jobj == NULL) {
        Fighter* fp = gobj->user_data;
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_MARS];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800F09F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0A54(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.kb.hat.jobj == NULL) {
        Fighter* fp = gobj->user_data;
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_ZELDA];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800F0B0C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0B70(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_CLINK];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800F0C20(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F0C7C(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.kb.hat.jobj == NULL) {
        Fighter* fp = gobj->user_data;
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_FALCO];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800F0D34(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0D98(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_GAMEWATCH];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
    }
}

void ftKb_SpecialN_800F0E48(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F0EA4(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.kb.hat.jobj == NULL) {
        Fighter* fp = gobj->user_data;
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_GANON];
        fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->fv.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->fv.kb.hat.jobj, &fp->fv.kb.hat.x14);
        ftParts_8007487C(&hat->desc, &fp->fv.kb.hat.x24, 0, &fp->fv.kb.hat.x14,
                         &fp->fv.kb.hat.x14);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800F0F5C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0FC0(Fighter_GObj* gobj)
{
    u8 sp14[0x90];

    Fighter* fp = fp = GET_FIGHTER(gobj);
    KirbyHatStruct* temp_r29;

    PAD_STACK(4);

    if (fp->fv.kb.hat.x14.data != NULL) {
        return;
    }

    temp_r29 = ft_80459B88.hats[FTKIND_CAPTAIN];
    ftKb_SpecialN_800EF040(gobj, 3, temp_r29);
    fp->fv.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
    fp->fv.kb.hat.x1C.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
    ftKb_SpecialN_800EF0E4(gobj, 3, sp14);
    ftKb_SpecialN_800EF35C(gobj, 3, sp14);
    ftKb_SpecialN_800EF438(gobj, temp_r29);
    ftParts_8007487C((FtPartsDesc*) temp_r29, &fp->fv.kb.hat.x24,
                     fp->x619_costume_id, &fp->fv.kb.hat.x14,
                     &fp->fv.kb.hat.x1C);
    ftAnim_80070200(fp, (ftData_x8_x8*) &temp_r29->desc.vis_table,
                    &fp->fv.kb.x44, &fp->fv.kb.hat.x14);
}

void ftKb_SpecialN_800F10A4(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EF69C(gobj, 3, ft_80459B88.hats[FTKIND_CAPTAIN]);
}

/// #ftKb_SpecialN_800F10D4

void ftKb_SpecialN_800F11AC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftKb_SpecialN_800EF69C(gobj, 0xF, ft_80459B88.hats[14]);
    ftCo_UnloadDynamicBones(fp);
}
/// #ftKb_SpecialN_800F11F0

void ftKb_SpecialN_800F12C8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EF69C(gobj, 0x10, ft_80459B88.hats[FTKIND_PURIN]);
    ftCo_UnloadDynamicBones(fp);
}
/// #ftKb_SpecialN_800F130C

void ftKb_SpecialN_800F13F0(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EF69C(gobj, 0x16, ft_80459B88.hats[FTKIND_DRMARIO]);
}

/// #ftKb_SpecialN_800F1420

/// #ftKb_SpecialN_800F14B4

/// #ftKb_SpecialN_800F15D8

/// #ftKb_SpecialN_Enter

/// #ftKb_SpecialAirN_Enter

/// #ftKb_SpecialN_800F16D0

/// #ftKb_SpecialN_800F190C

/// #ftKb_SpecialN_800F19AC

/// #ftKb_SpecialN_800F1A8C

void ftKb_Init_UnkMotionStates3(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->fv.kb.hat.kind;

    switch (kind) {
    case FTKIND_KOOPA:
    case FTKIND_GKOOPS:
        ftKb_SpecialNKp_800FA7D4(gobj);
        break;
    }
}
/// #ftKb_SpecialN_800F1BAC

static bool fn_800F1CA0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    u32 val = M2C_FIELD(fp, u32*, 0x2238);
    switch (val) {
    case 2:
    case 7:
    case 10:
    case 11:
    case 13:
        return true;
    default:
        return false;
    }
}

s32 ftKb_SpecialN_800F1CD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->fv.kb.hat.kind;
    bool result;

    switch (kind) {
    case FTKIND_CAPTAIN:
    case FTKIND_SEAK:
    case FTKIND_POPO:
    case FTKIND_NANA:
    case FTKIND_SAMUS:
        result = true;
        break;
    default:
        result = false;
        break;
    }

    if (result) {
        return true;
    }
    return false;
}
/// #ftKb_SpecialN_800F1D24

/// #ftKb_SpecialN_800F1DAC

/// #ftKb_SpecialN_800F1F1C

/// #ftKb_SpecialN_800F1F68

void fn_800F1FDC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15F, 0x0C4C5082U, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0, NULL);
}

void ftKb_AttackDash_Anim(Fighter_GObj* gobj)
{
    ftCo_AttackDash_Anim(gobj);
}

void ftKb_AttackDash_IASA(Fighter_GObj* gobj)
{
    ftCo_AttackDash_IASA(gobj);
}

void ftKb_AttackDash_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftKb_AttackDash_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F20C4);
}

/// #fn_800F20C4

/// #ftKb_AttackDashAir_Anim

void ftKb_AttackDashAir_IASA(Fighter_GObj* gobj) {}

void ftKb_AttackDashAir_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80085204(gobj);
    ftCommon_FallBasic(fp);
}

void ftKb_AttackDashAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F1FDC);
}

void ftKb_AttackDashAir_800F21C0(Fighter_GObj* gobj)
{
    ftPartGetRotX(gobj->user_data, 0);
}

/// #fn_800F21E8

void ftKb_AttackDashAir_800F22D4(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftPartSetRotX(ft, 0, 0.0F);
}

/// #ftKb_SpecialHi_Enter

/// #ftKb_SpecialAirHi_Enter

/// #ftKb_SpecialHi1_Anim

/// #ftKb_SpecialHi2_Anim

void ftKb_SpecialHi3_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirHiEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialLw1_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialLwEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirLwStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirLwEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialNLoop_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirNLoop_Anim(Fighter_GObj* gobj) {}

void ftKb_EatWait_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirNCaptureWait_Anim(Fighter_GObj* gobj) {}

void ftKb_EatJump2_Anim(Fighter_GObj* gobj) {}

void ftKb_CaSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PkSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PkSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_KpSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_KpSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_KpSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_KpSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_LkSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_LkSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_FxSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_FxSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNFull_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNFull_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNTurn_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialAirNEndR_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNHit_IASA(Fighter_GObj* gobj) {}

void ftKb_ZdSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_ZdSpecialAirN_IASA(Fighter_GObj* gobj) {}

void fn_80105FEC(void) {}

void ftKb_SkSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

/// #ftKb_SpecialHi4_Anim

/// #ftKb_SpecialAirHi1_Anim

/// #ftKb_SpecialAirHi2_Anim

void ftKb_SpecialAirHi3_Anim(Fighter_GObj* gobj) {}

/// #ftKb_SpecialAirHiEnd_Anim

/// #ftKb_SpecialHi1_IASA

void ftKb_SpecialHi2_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialHi3_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialHi4_IASA(Fighter_GObj* gobj) {}

/// #ftKb_SpecialAirHi1_IASA

void ftKb_SpecialAirHi2_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirHi3_IASA(Fighter_GObj* gobj) {}

/// #ftKb_SpecialAirHiEnd_IASA

void ftKb_SpecialHi1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(4); // Todo: Remove This
    ft_80084FA8(gobj);
    ftCommon_8007CADC(fp, 0.0f,
                      temp_r30->air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      temp_r30->air_drift_max);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_SpecialHi2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(4); // Todo: Remove This
    ft_80085134(gobj);
    ftCommon_8007CADC(fp, 0.0f,
                      temp_r30->air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      temp_r30->air_drift_max);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_SpecialHi3_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    ftCommon_8007CADC(fp, 0.0f,
                      fp->co_attrs.air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      fp->co_attrs.air_drift_max);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_SpecialHi4_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftKb_SpecialAirHi1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 stack; // Needed For Stack?
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ft_80085134(gobj);
    if (fp->self_vel.y > 0.0f) {
        fp->self_vel.y *= dat_attr->specialhi_vertical_momentum;
    }
    ftCommon_8007D3A8(fp, 0.0f,
                      temp_r30->air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      temp_r30->air_drift_max);
}

void ftKb_SpecialAirHi2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 stack; // Needed For Stack?
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ft_80085134(gobj);
    if (fp->self_vel.y > 0.0f) {
        fp->self_vel.y *= dat_attr->specialhi_vertical_momentum;
    }
    ftCommon_8007D3A8(fp, 0.0f,
                      temp_r30->air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      temp_r30->air_drift_max);
}

void ftKb_SpecialAirHi3_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ftCommon_8007D3A8(fp, 0.0f,
                      fp->co_attrs.air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      fp->co_attrs.air_drift_max);
}

void ftKb_SpecialAirHiEnd_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

inline void ftKirbyDmgInline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
}

inline void ftKirbyDmgInline2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
}

void ftKb_SpecialHi1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x185, 0xC1082U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

void ftKb_SpecialHi2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 var_r4;
    PAD_STACK(5); // Fake
    if (fp->mv.kb.specialn_pe.facing_dir > 0x14) {
        if (1 == fp->facing_dir) {
            var_r4 = 1;
        } else {
            var_r4 = -1;
        }
        if (ft_CheckGroundAndLedge(gobj, var_r4)) {
            fp->mv.kb.specialn_pe.facing_dir++;
            ftCommon_8007D5D4(fp);
            Fighter_ChangeMotionState(gobj, 0x188, 0xC1082U, 0.0f, 1.0f, 0.0f,
                                      NULL);
            ftKirbyDmgInline(gobj);
            fp->accessory4_cb = fn_800F21E8;
            fp->self_vel.z = 0.0f;
            fp->self_vel.y = 0.0f;
            fp->self_vel.x = 0.0f;
            fp->gr_vel = 0.0f;
            ftPartSetRotX(fp, 0,
                          fp->facing_dir *
                              atan2f(fp->coll_data.floor.normal.x,
                                     fp->coll_data.floor.normal.y));
            return;
        }
        if (ftCliffCommon_80081298(gobj)) {
            ftCliffCommon_80081370(gobj);
        }
    } else {
        fp->mv.kb.specialn_pe.facing_dir++;
        ftCommon_8007D60C(fp);
        ft_80082578(gobj);
    }
}

void ftKb_SpecialHi3_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 var_r4;

    if (1.0f == fp->facing_dir) {
        var_r4 = 1;
    } else {
        var_r4 = -1;
    }
    if (ft_CheckGroundAndLedge(gobj, var_r4)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x188, 0xC1082U, 0.0f, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
        fp->accessory4_cb = fn_800F21E8;
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        fp->gr_vel = 0.0f;
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftKb_SpecialHi4_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x188, 0xC1082U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
        fp->accessory4_cb = fn_800F21E8;
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        ftPartSetRotX(fp, 0, 0.0F);
        return;
    }
    ftPartSetRotX(fp, 0,
                  fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                          fp->coll_data.floor.normal.y));
}

void ftKb_SpecialAirHi1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x181, 0xC1082U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
    }
}

void ftKb_SpecialAirHi2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 var_r4;
    PAD_STACK(6); // Fix
    if (fp->mv.kb.specialn_pe.facing_dir > 0x14) {
        if (1.0f == fp->facing_dir) {
            var_r4 = 1;
        } else {
            var_r4 = -1;
        }
        if (ft_CheckGroundAndLedge(gobj, var_r4)) {
            fp->mv.kb.specialn_pe.facing_dir++;
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, 0x184, 0xC1082U, 0.0f, 1.0f, 0.0f,
                                      NULL);
            ftKirbyDmgInline(gobj);
            fp->accessory4_cb = fn_800F21E8;
            fp->self_vel.z = 0.0f;
            fp->self_vel.y = 0.0f;
            fp->self_vel.x = 0.0f;
            fp->gr_vel = 0.0f;
            ftPartSetRotX(fp, 0,
                          fp->facing_dir *
                              atan2f(fp->coll_data.floor.normal.x,
                                     fp->coll_data.floor.normal.y));
            return;
        }
        if (ftCliffCommon_80081298(gobj)) {
            ftCliffCommon_80081370(gobj);
        }
    } else {
        fp->mv.kb.specialn_pe.facing_dir++;
        ftCommon_8007D60C(fp);
        ft_80082578(gobj);
    }
}

void ftKb_SpecialAirHi3_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 var_r4;
    if (fp->facing_dir == 1.0f) {
        var_r4 = 1;
    } else {
        var_r4 = -1;
    }
    if (ft_CheckGroundAndLedge(gobj, var_r4)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x184, 0xC1082U, 0.0f, 1.0f, 0.0f,
                                  NULL);
        ftKirbyDmgInline(gobj);
        fp->accessory4_cb = fn_800F21E8;
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        fp->gr_vel = 0.0f;
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftKb_SpecialAirHiEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x184, 0xC1082U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
        fp->accessory4_cb = fn_800F21E8;
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
        return;
    }
    ftPartSetRotX(fp, 0, 0.0F);
}

void ftKb_SpecialHi_800F331C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    switch (fp->mv.kb.specialhi.x8) {
    case 1:
        fp->mv.kb.specialhi.x14++;
        break;
    case 2:
        fp->mv.kb.specialhi.x14--;
        break;
    }

    if ((fp->mv.kb.specialhi.x14 >= 0) && (fp->mv.kb.specialhi.x14 < 0x16)) {
        if (ftKb_Init_803CB490[fp->mv.kb.specialhi.x14] == 0) {
            ftParts_80074B0C(gobj, 0, 0);
            ftParts_80074B0C(gobj, 1, 0);
            ftCommon_8007F5CC(gobj, 1);
            fp->x221E_b4 = TRUE;
            fp->x2225_b2 = TRUE;
        } else {
            ftParts_80074B0C(gobj, 0,
                             ftKb_Init_803CB4EC.ints[fp->mv.kb.specialhi.x10]);
            ftParts_80074B0C(gobj, 1, -1);
            ftCommon_8007F5CC(gobj, 0);
            fp->x221E_b4 = FALSE;
            fp->x2225_b2 = FALSE;
        }
    } else {
        fp->mv.kb.specialhi.x8 = 0;
    }
}

void ftKb_SpecialHi_800F346C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    switch (fp->cmd_vars[0]) {
    case 1:
        if (!fp->mv.kb.specialhi.x8 && !fp->mv.kb.specialhi.xC) {
            fp->mv.kb.specialhi.x8 = fp->cmd_vars[0];
            fp->dmg.x1834 = dat_attr->speciallw_hp;
            fp->fv.kb.hat.x4 = fp->mv.kb.specialhi.x10 =
                ((fp->fv.kb.hat.x4 + HSD_Randi(4)) % 5) + 1; // Trouble Here
            fp->mv.kb.specialhi.x14 = 0;
            fp->mv.kb.specialhi.xC = 1;
        }
        break;
    case 2:
        if (!fp->mv.kb.specialhi.x8 && !fp->mv.kb.specialhi.xC) {
            fp->mv.kb.specialhi.x8 = fp->cmd_vars[0];
            fp->mv.kb.specialhi.x14 = 0x16;
        }
        break;
    }
    fp->cmd_vars[0] = 0;
}

void ftKb_SpecialHi_800F3570(Fighter_GObj* gobj)
{
    Vec3 sp1C;
    Vec3 vec;
    f32 var_f3;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    fp->mv.kb.specialhi.x18 = fp->coll_data.floor.normal;
    fp->mv.kb.specialhi.xC4 =
        fp->facing_dir *
        atan2f(fp->mv.kb.specialhi.x18.x, fp->mv.kb.specialhi.x18.y);
    if (0.0f != fp->mv.kb.specialhi.x18.x) {
        vec.x = fp->cur_pos.y;
        vec.y = dat_attr->speciallw_slide_max_speed;
        vec.z = fp->cur_pos.x;
        if (fp->mv.kb.specialhi.x18.x > 0.0f) {
            var_f3 = 1.0f;
        } else {
            var_f3 = -1.0f;
        }
        if (mpCheckAllRemap(
                NULL, 0, NULL, &sp1C, -1, -1, vec.z, vec.x + vec.y,
                (fp->mv.kb.specialhi.x18.y * vec.y *
                 ((fp->mv.kb.specialhi.x18.x > 0.0f) ? 1.0f : -1.0f)) +
                    vec.z,
                vec.x - vec.y) == 0)
        {
            sp1C = ftKb_Init_803CB4EC.vec;
        }
        if (fp->mv.kb.specialhi.x18.x > 0.0f) {
            if (sp1C.x < 0.0f) {
                fp->mv.kb.specialhi.x18 = ftKb_Init_803CB4EC.vec;
                fp->mv.kb.specialhi.xC4 = 0.0f;
                fp->xE4_ground_accel_1 = 0.0f;
                fp->gr_vel = 0.0f;
            }
        } else if (sp1C.x > 0.0f) {
            fp->mv.kb.specialhi.x18 = ftKb_Init_803CB4EC.vec;
            fp->mv.kb.specialhi.xC4 = 0.0f;
            fp->xE4_ground_accel_1 = 0.0f;
            fp->gr_vel = 0.0f;
        }
    }
}

void ftKb_SpecialHi_800F36DC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.kb.speciallw.x24 = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x54 = fp->mv.kb.speciallw.x24;
    fp->mv.kb.speciallw.x88[0] = 0.0f;
    fp->mv.kb.speciallw.x88[4] = 0.0f;
    fp->mv.kb.speciallw.x30 = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x60 = fp->mv.kb.speciallw.x30;
    fp->mv.kb.speciallw.x88[1] = 0.0f;
    fp->mv.kb.speciallw.x88[5] = 0.0f;
    fp->mv.kb.speciallw.x3C = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x6C = fp->mv.kb.speciallw.x3C;
    fp->mv.kb.speciallw.x88[2] = 0.0f;
    fp->mv.kb.speciallw.x88[6] = 0.0f;
    fp->mv.kb.speciallw.x48 = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x78 = fp->mv.kb.speciallw.x48;
    fp->mv.kb.speciallw.x88[3] = 0.0f;
    fp->mv.kb.speciallw.x88[7] = 0.0f;
    fp->mv.kb.speciallw.x18 = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x84 = 0.0f;
}

void ftKb_SpecialHi_800F37EC(Fighter_GObj* gobj)
{
    f32 temp_f5 = 0;
    s32 var_r4;
    s32 var_r5;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    fp->mv.kb.speciallw.x48 = fp->mv.kb.speciallw.x3C;
    fp->mv.kb.speciallw.x78 = fp->mv.kb.speciallw.x6C;
    fp->mv.kb.speciallw.x88[3] = fp->mv.kb.speciallw.x88[2];
    fp->mv.kb.speciallw.x88[7] = fp->mv.kb.speciallw.x88[6];
    fp->mv.kb.speciallw.x3C = fp->mv.kb.speciallw.x30;
    fp->mv.kb.speciallw.x6C = fp->mv.kb.speciallw.x60;
    fp->mv.kb.speciallw.x88[2] = fp->mv.kb.speciallw.x88[1];
    fp->mv.kb.speciallw.x88[6] = fp->mv.kb.speciallw.x88[5];
    fp->mv.kb.speciallw.x30 = fp->mv.kb.speciallw.x24;
    fp->mv.kb.speciallw.x60 = fp->mv.kb.speciallw.x54;
    fp->mv.kb.speciallw.x88[1] = fp->mv.kb.speciallw.x88[0];
    fp->mv.kb.speciallw.x88[5] = fp->mv.kb.speciallw.x88[4];
    fp->mv.kb.speciallw.x24 = fp->mv.kb.speciallw.x18;
    fp->mv.kb.speciallw.x88[0] = fp->mv.kb.speciallw.x84;
    fp->mv.kb.speciallw.x54.z = 0.0f;
    fp->mv.kb.speciallw.x54.y = 0.0f;
    fp->mv.kb.speciallw.x54.x = 0.0f;
    fp->mv.kb.speciallw.x88[4] = 0.0f;
    fp->mv.kb.speciallw.x54.x += fp->mv.kb.speciallw.x24.x;
    fp->mv.kb.speciallw.x54.y += fp->mv.kb.speciallw.x24.y;
    fp->mv.kb.speciallw.x54.z += fp->mv.kb.speciallw.x24.z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[0];
    fp->mv.kb.speciallw.x54.x += fp->mv.kb.speciallw.x30.x;
    fp->mv.kb.speciallw.x54.y += fp->mv.kb.speciallw.x30.y;
    fp->mv.kb.speciallw.x54.z += fp->mv.kb.speciallw.x30.z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[1];
    fp->mv.kb.speciallw.x54.x += fp->mv.kb.speciallw.x3C.x;
    fp->mv.kb.speciallw.x54.y += fp->mv.kb.speciallw.x3C.y;
    fp->mv.kb.speciallw.x54.z += fp->mv.kb.speciallw.x3C.z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[2];
    fp->mv.kb.speciallw.x54.x += fp->mv.kb.speciallw.x48.x;
    fp->mv.kb.speciallw.x54.y += fp->mv.kb.speciallw.x48.y;
    fp->mv.kb.speciallw.x54.z += fp->mv.kb.speciallw.x48.z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[3];
    lbVector_Normalize(&fp->mv.kb.speciallw.x54);
    var_r4 = 3;
    fp->mv.kb.speciallw.x88[4] *= 0.25f;
    fp->mv.kb.speciallw.x88[8] = 1.0f;
    for (var_r4 = 3; var_r4 > 0; var_r4--) {
        if (ABS(fp->mv.kb.speciallw.x88[var_r4]) >
            dat_attr->speciallw_min_slant_angle_slide)
        {
            for (var_r5 = var_r4; var_r5 >= 0; var_r5--) {
                if (ABS(fp->mv.kb.speciallw.x88[var_r5]) <=
                    dat_attr->speciallw_min_slant_angle_slide)
                {
                    fp->mv.kb.speciallw.x88[8] = 0.9f;
                    var_r5 = -1;
                    var_r4 = -1;
                } else if (fp->mv.kb.speciallw.x88[var_r5] > 0.0f) {
                    if (temp_f5 < 0.0f) {
                        fp->mv.kb.speciallw.x88[8] -= 0.25f;
                        if (fp->mv.kb.speciallw.x88[8] < 0.0f) {
                            fp->mv.kb.speciallw.x88[8] = 0.0f;
                        }
                    } else if (fp->mv.kb.speciallw.x88[var_r5] > 0.0f) {
                        fp->mv.kb.speciallw.x88[8] -= 0.25f;
                        if (fp->mv.kb.speciallw.x88[8] < 0.0f) {
                            fp->mv.kb.speciallw.x88[8] = 0.0f;
                        }
                    }
                }
            }
        }
    }
}

void ftKb_SpecialHi_800F3B28(Fighter_GObj* gobj)
{
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    f32 var_f1_2;
    f32 var_f31;
    f32 var_f4;
    f32 var_f5;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    var_f31 = fp->mv.kb.speciallw.x88[4];
    ftPartSetRotX(fp, 0, var_f31);
    if (ABS(var_f31) < dat_attr->speciallw_min_slant_angle_slide) {
        var_f31 = 0.0f;
    }
    if (var_f31 > dat_attr->speciallw_max_slant_angle_slide) {
        var_f31 = dat_attr->speciallw_max_slant_angle_slide;
    }
    if (var_f31 < -dat_attr->speciallw_max_slant_angle_slide) {
        var_f31 = -dat_attr->speciallw_max_slant_angle_slide;
    }
    temp_f1 = ft_GetGroundFrictionMultiplier(fp);
    if (ABS(var_f31) < 0.017453292f) {
        var_f5 = 0.0f;
        temp_f3 = fp->gr_vel;
        temp_f2 =
            temp_f1 * (fp->mv.co.common.x58.x * fp->co_attrs.gr_friction);
        var_f1_2 = ABS(fp->gr_vel);
        if (ABS(temp_f2) > var_f1_2) {
            var_f4 = -fp->gr_vel;
        } else {
            if (temp_f3 > 0.0f) {
                var_f4 = -temp_f2;
            } else {
                var_f4 = temp_f2;
            }
        }
    } else {
        var_f4 = 0.0f;
        var_f5 =
            (1.0f + (1.0f - temp_f1)) *
            (fp->mv.co.common.x4C.z * dat_attr->speciallw_slide_acceleration);
    }
    fp->xE4_ground_accel_1 = fp->mv.kb.speciallw.x88[8] * (var_f5 + var_f4);
    fp->gr_vel *= fp->mv.kb.speciallw.x88[8];
    if (fp->gr_vel < -dat_attr->speciallw_slide_max_speed) {
        fp->gr_vel = -dat_attr->speciallw_slide_max_speed;
    } else if (fp->gr_vel > dat_attr->speciallw_slide_max_speed) {
        fp->gr_vel = dat_attr->speciallw_slide_max_speed;
    }
    if (fp->gr_vel + fp->xE4_ground_accel_1 <
        -dat_attr->speciallw_slide_max_speed)
    {
        fp->xE4_ground_accel_1 =
            -dat_attr->speciallw_slide_max_speed - fp->gr_vel;
    } else if (fp->gr_vel + fp->xE4_ground_accel_1 >
               dat_attr->speciallw_slide_max_speed)
    {
        fp->xE4_ground_accel_1 =
            dat_attr->speciallw_slide_max_speed - fp->gr_vel;
    }
    fp->x74_anim_vel.x = fp->mv.co.common.x58.x * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.y = -fp->mv.co.common.x4C.z * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.z = 0.0f;
    fp->self_vel.x = fp->mv.co.common.x58.x * fp->gr_vel;
    fp->self_vel.y = -fp->mv.co.common.x4C.z * fp->gr_vel;
    fp->self_vel.z = 0.0f;
}

void ftKb_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* temp_r28;
    s32 temp_r30;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(0x18);

    temp_r28 = fp->parts[FtPart_YRotN].joint;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.kb.speciallw.x0 = dat_attr->speciallw_max_time_in_stone;
    fp->mv.kb.speciallw.x2 = dat_attr->speciallw_min_time_in_stone;
    fp->mv.kb.speciallw.x4 = 0;
    fp->mv.kb.speciallw.x6 = 0;
    fp->mv.kb.speciallw.x8 = 0;
    fp->mv.kb.speciallw.xC = 0;
    fp->mv.kb.speciallw.x10 = -1;
    fp->mv.kb.speciallw.x14 = -1;
    ftKb_SpecialHi_800F36DC(gobj);
    fp->dmg.x1834 = 0.0f;
    fp->x221C_b4 = 0;
    temp_r30 = fp->x221C_b4;
    Fighter_ChangeMotionState(gobj, 0x189, 0U, 0.0f, 1.0f, 0.0f, NULL);
    fp->x221C_b4 = temp_r30;
    ftKirbyDmgInline2(gobj);
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(0x49B, (HSD_GObj*) gobj, temp_r28);
}

void ftKb_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* temp_r28;
    s32 temp_r30;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(0x18);

    temp_r28 = fp->parts[FtPart_YRotN].joint;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.kb.speciallw.x0 = dat_attr->speciallw_max_time_in_stone;
    fp->mv.kb.speciallw.x2 = dat_attr->speciallw_min_time_in_stone;
    fp->mv.kb.speciallw.x4 = 0;
    fp->mv.kb.speciallw.x6 = 0;
    fp->mv.kb.speciallw.x8 = 0;
    fp->mv.kb.speciallw.xC = 0;
    fp->mv.kb.speciallw.x10 = -1;
    fp->mv.kb.speciallw.x14 = -1;
    ftKb_SpecialHi_800F36DC(gobj);
    fp->dmg.x1834 = 0.0f;
    fp->x221C_b4 = 0;
    temp_r30 = fp->x221C_b4;
    Fighter_ChangeMotionState(gobj, 0x18c, 0U, 0.0f, 1.0f, 0.0f, NULL);
    fp->x221C_b4 = temp_r30;
    ftKirbyDmgInline2(gobj);
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(0x49B, (HSD_GObj*) gobj, temp_r28);
}

void ftKb_SpecialLw1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 temp_r30;

    fp->x221C_b4 = 0;
    ftKb_SpecialHi_800F346C(gobj);
    ftKb_SpecialHi_800F331C(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_r30 = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, 0x18A, 0x04440012U, 0.0f, 0.0f, 0.0f,
                                  NULL);
        fp->x221C_b4 = temp_r30;
        ftAnim_SetAnimRate(gobj, 0.0f);
    }
}

inline void ftKbUnkInline(Fighter_GObj* gobj, int val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221C_b4 = val;
    ftKb_SpecialHi_800F346C(gobj);
    ftKb_SpecialHi_800F331C(gobj);
}

void ftKb_SpecialLw_Anim(Fighter_GObj* gobj)
{
    ftKbUnkInline(gobj, 1);
}

void ftKb_SpecialLwEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ftKbUnkInline(gobj, 0);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->dmg.x1834 = 0.0f;
        fp->x221C_b4 = 0;
        if (dat_attr->speciallw_freefall_toggle == 0.0f) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0f,
                      dat_attr->speciallw_freefall_toggle);
    }
}

void ftKb_SpecialAirLwStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 temp_r30;
    fp->x221C_b4 = 0;
    ftKb_SpecialHi_800F346C(gobj);
    ftKb_SpecialHi_800F331C(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_r30 = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, 0x18D, 0x04440012U, 0.0f, 0.0f, 0.0f,
                                  NULL);
        fp->x221C_b4 = temp_r30;
        ftAnim_SetAnimRate(gobj, 0.0f);
    }
}

void ftKb_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    ftKbUnkInline(gobj, 1);
}

void ftKb_SpecialAirLwEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ftKbUnkInline(gobj, 0);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->dmg.x1834 = 0.0f;
        fp->x221C_b4 = 0;
        if (dat_attr->speciallw_freefall_toggle == 0.0f) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0f,
                      dat_attr->speciallw_freefall_toggle);
    }
}

inline static bool fbKb_SpecialLw_IASA_Inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool var_r0;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    if (fp->mv.kb.speciallw.x0 <= 0) {
        var_r0 = 1;
    } else if ((fp->mv.kb.speciallw.x0 <=
                (s32) (dat_attr->speciallw_max_time_in_stone -
                       dat_attr->speciallw_min_time_in_stone)) &&
               (fp->input.x668 & 0x200))
    {
        var_r0 = 1;
    } else {
        if (fp->mv.kb.speciallw.x0 > 0) {
            fp->mv.kb.speciallw.x0--;
        }
        var_r0 = 0;
    }

    return var_r0;
}

void ftKb_SpecialLw_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 temp_r28;
    HSD_JObj* temp_r30 = fp->parts[FtPart_YRotN].joint;
    PAD_STACK(16);

    if (fbKb_SpecialLw_IASA_Inline(gobj)) {
        ftCommon_8007D5D4(fp);
        temp_r28 = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, 0x18B, 0x04440012U, 0.0f, 1.0f, 0.0f,
                                  NULL);
        fp->x221C_b4 = temp_r28;
        ftKirbyDmgInline(gobj);
        efSync_Spawn(0x49C, gobj, temp_r30);
    }
}

void ftKb_SpecialLw1_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

/// #ftKb_SpecialLw_Phys

void ftKb_SpecialLwEnd_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftKb_SpecialAirLwStart_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

/// #ftKb_SpecialAirLw_Phys

void ftKb_SpecialAirLwEnd_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

/// #ftKb_SpecialLw1_Coll

/// #ftKb_SpecialLw_Coll

/// #ftKb_SpecialLwEnd_Coll

/// #ftKb_SpecialAirLwStart_Coll

/// #ftKb_SpecialAirLw_Coll

/// #ftKb_SpecialAirLwEnd_Coll

/// #ftKb_SpecialAirLw_800F5318

void ftKb_SpecialAirLw_800F539C(Fighter_GObj* gobj)
{
    M2C_FIELD(gobj->user_data, s32*, 0x222C) = 0;
}

/// #fn_800F53AC

void ftKb_SpecialAirLw_800F5524(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->fv.kb.hat.x0 != NULL) {
        it_802ADC34(gobj);
        fp->fv.kb.hat.x0 = NULL;
    }
}

void ftKb_SpecialS_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, 0x17F, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &fn_800F53AC;
}

/// #ftKb_SpecialAirS_Enter

void ftKb_SpecialS_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialAirS_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(0x08);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialS_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirS_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// #ftKb_SpecialS_Coll

/// #ftKb_SpecialAirS_Coll

void ftKb_SpecialN_800F5800(HSD_GObj* gobj, Vec3* vec)
{
    Fighter* ft = GET_FIGHTER(gobj);
    *vec = ft->cur_pos;
}

/// #ftKb_SpecialN_800F5820

void ftKb_SpecialN_800F5874(Vec2* arg0)
{
    ftCommonData* cd = gFtDataList[FTKIND_KIRBY]->ext_attr;
    arg0->x = cd->x9C_radians;
    arg0->y = cd->xA0_radians;
}

HSD_Joint* ftKb_SpecialN_800F5898(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* ca = fp->ft_data;
    return M2C_FIELD(&ca->x48_items[0], HSD_Joint**, 0x10);
}

float ftKb_SpecialN_800F58AC(Fighter_GObj* gobj, Vec3* victim_self_vel,
                             float victim_facing_dir)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    victim_self_vel->x = -victim_facing_dir *
                         da->specialn_ground_spit_initial_horizontal_velocity;
    victim_self_vel->z = 0.0f;
    victim_self_vel->y = 0.0f;
    return da->specialn_spit_deceleration_rate;
}

/// #ftKb_SpecialN_800F58D8

void ftKb_SpecialN_800F5954(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    mpUpdateFloorSkip(&ft->coll_data);
}

bool ftKb_SpecialN_800F597C(Fighter_GObj* gobj)
{
    return M2C_FIELD(gobj->user_data, s32*, 0x840) & 0x100;
}

/// #ftKb_SpecialN_800F598C

void ftKb_SpecialN_800F5A04(Fighter_GObj* gobj, f32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    if (!fp->ground_or_air) {
        fp->gr_vel = arg1 * dat_attr->specialn_stop_momentum;
        return;
    }
    fp->self_vel.x = arg1 * dat_attr->specialn_stop_momentum;
}

bool ftKb_SpecialN_800F5A38(Fighter_GObj* gobj, Fighter* victim_fp)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId id = fp->motion_id;
    if (id == ftKb_MS_EatWait || id == ftKb_MS_EatFall) {
        return 1;
    }
    return 0;
}

float ftKb_SpecialN_800F5A60(Fighter_GObj* gobj)
{
    return -GET_FIGHTER(gobj)->facing_dir;
}

float ftKb_SpecialN_800F5A70(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_gravity_of_inhaled;
}

f32 ftKb_SpecialN_800F5A88(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->specialn_star_base_duration;
}

f32 ftKb_SpecialN_800F5A98(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_spit_spin;
}

f32 ftKb_SpecialN_800F5AB0(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->specialn_frames_in_swallow_star;
}

f32 ftKb_SpecialN_800F5AC0(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_star_duration_divisor;
}

f32 ftKb_SpecialN_800F5AD8(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_star_deceleration_rate;
}

f32 ftKb_SpecialN_800F5AF0(Fighter_GObj* gobj)
{
    return M2C_FIELD(M2C_FIELD(gobj->user_data, void**, 0x2D4), f32*, 0x5C);
}

f32 ftKb_SpecialN_800F5B00(Fighter_GObj* gobj)
{
    return M2C_FIELD(M2C_FIELD(gobj->user_data, void**, 0x2D4), f32*, 0x58);
}

f32 ftKb_SpecialN_800F5B10(Fighter_GObj* gobj)
{
    return M2C_FIELD(M2C_FIELD(gobj->user_data, void**, 0x2D4), f32*, 0x54);
}

void ftKb_SpecialN_800F5B20(Fighter_GObj* gobj, Vec2* out)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    out->x = da->specialn_velocity_outer_grab_box;
    out->y = da->specialn_velocity_inner_grab_box;
}

float ftKb_SpecialN_800F5B3C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_gravity_of_inhaled;
}

f32 ftKb_SpecialN_800F5B4C(Fighter_GObj* gobj)
{
    return M2C_FIELD(M2C_FIELD(gobj->user_data, void**, 0x2D4), f32*, 0x40);
}

/// #ftKb_SpecialN_800F5B5C

/// #ftKb_SpecialN_800F5BA4

/// #ftKb_SpecialN_800F5C34

/// #ftKb_SpecialN_800F5D04

/// #ftKb_SpecialN_800F5DE8

/// #ftKb_SpecialN_800F5EA8

void ftKb_SpecialN_800F5F68(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 14);

    fp->throw_flags = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = 0;
    fp->fv.kb.xE0 = 4;

    // Ends up being 00 28 according to data sheet
    fp->fv.kb.xE4 = da->jumpaerial_unk;

    fp->fv.kb.xE8 = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerFall));
    fp->fv.kb.xEC = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerJump));
    fp->fv.kb.xF0 =
        lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerLanding));

    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialN, 0, 0, 1, 0, NULL);
    fp->x2222_b2 = true;
    ftAnim_8006EBA4(gobj);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 16, fn_800F6210, fn_800F6178, ftCo_800BD1DC);
        fp->x2225_b1 = true;
    }
}

/// #ftKb_SpecialN_800F6070

void fn_800F6178(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F23EC(fp->target_item_gobj, gobj, -fp->facing_dir);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNCapture1,
                              Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_KeepSfx,
                              0, 1, 0, NULL);
    fp->x2222_b2 = true;
    fp->fv.kb.xF4_b0 = true;
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

/// #fn_800F6210

/// #fn_800F6280

/// #fn_800F6318

/// #ftKb_SpecialN_800F6388

/// #ftKb_SpecialN_800F63EC

/// #fn_800F6450

/// #fn_800F64C8

/// #fn_800F6528

/// #fn_800F6588

/// #fn_800F6638

/// #fn_800F66E8

/// #fn_800F6798

/// #fn_800F6848

/// #fn_800F68A8

/// #fn_800F6908

/// #fn_800F697C

/// #fn_800F69E8

/// #fn_800F6A5C

/// Fighter_CollGround_PassLedgeCB
void fn_800F6AC8(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatAir, mf, fp->cur_anim_frame, 1,
                              0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

/// #fn_800F6B3C

/// #ftKb_SpecialS_800F6BB0

/// #fn_800F6C24

/// #fn_800F6C98

/// #fn_800F6D0C

/// #fn_800F6D80

/// #fn_800F6DF4

/// #fn_800F6E68

/// #fn_800F6EDC

/// #fn_800F6F50

/// #fn_800F6FC4

/// #fn_800F702C

/// #ftKb_SpecialN_Anim

/// #ftKb_SpecialAirN_Anim

/// #ftKb_SpecialNLoop_Anim

/// #ftKb_SpecialAirNLoop_Anim

/// #ftKb_SpecialNEnd_Anim

/// #ftKb_SpecialAirNEnd_Anim

/// #ftKb_SpecialNCapture0_Anim

/// #ftKb_SpecialNCapture_Anim

void ftKb_SpecialNCapture1_Anim(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800F5DE8(gobj);
}

void ftKb_SpecialAirNCapture_Anim(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800F5EA8(gobj);
}

void ftKb_Eat_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel, 0, 1,
                                  0, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

/// #ftKb_SpecialAirNCaptured_Anim

/// #ftKb_EatWait_Anim

/// #ftKb_SpecialAirNCaptureWait_Anim

/// #ftKb_SpecialNSpit0_Anim

/// #ftKb_SpecialNSpit_Anim

/// #ftKb_SpecialNSpit1_Anim

/// #ftKb_SpecialAirNSpit_Anim

/// #ftKb_SpecialNDrink0_Anim

/// #ftKb_SpecialNDrink_Anim

/// #ftKb_SpecialNDrink1_Anim

/// #ftKb_SpecialAirNDrink_Anim

/// #ftKb_EatTurn_Anim

/// #ftKb_SpecialAirNCaptureTurn_Anim

void ftKb_EatWalk_Anim(Fighter_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

/// #ftKb_EatJump1_Anim

/// #ftKb_EatJump2_Anim

/// #ftKb_EatLanding_Anim

/// #ftKb_SpecialNLoop_IASA

/// #ftKb_SpecialAirNLoop_IASA

/// #ftKb_EatWait_IASA

/// #ftKb_SpecialAirNCaptureWait_IASA

/// #ftKb_EatWalk_IASA

void ftKb_EatJump1_IASA(Fighter_GObj* gobj)
{
    ftCo_KneeBend_Check_ShortHop(gobj);
}

void ftKb_SpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNCapture0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNCapture_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNCapture_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_Eat_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptured_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptureWait_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNSpit0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNSpit_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNSpit1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNSpit_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNDrink0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNDrink_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNDrink1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNDrink_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatTurn_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptureTurn_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatWalk_Phys(Fighter_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftKb_EatJump1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_EatJump2_Phys(Fighter_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftKb_EatLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialN_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6588);
}

void ftKb_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6638);
}

void ftKb_SpecialNLoop_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F66E8);
}

void ftKb_SpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6798);
}

void ftKb_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6848);
}

void ftKb_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F68A8);
}

void ftKb_SpecialNCapture0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6908);
}

void ftKb_SpecialNCapture_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F697C);
}

void ftKb_SpecialNCapture1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F69E8);
}

void ftKb_SpecialAirNCapture_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6A5C);
}

void ftKb_Eat_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6AC8);
}

void ftKb_SpecialAirNCaptured_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6B3C);
}

void ftKb_EatWait_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftKb_SpecialS_800F6BB0);
}

void ftKb_SpecialAirNCaptureWait_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6528);
}

void ftKb_SpecialNSpit0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6C24);
}

void ftKb_SpecialNSpit_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6C98);
}

void ftKb_SpecialNSpit1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6D0C);
}

void ftKb_SpecialAirNSpit_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6D80);
}

void ftKb_SpecialNDrink0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6DF4);
}

void ftKb_SpecialNDrink_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6E68);
}

void ftKb_SpecialNDrink1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6EDC);
}

void ftKb_SpecialAirNDrink_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6F50);
}

void ftKb_EatTurn_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6FC4);
}

void ftKb_SpecialAirNCaptureTurn_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F702C);
}

void ftKb_EatWalk_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_EatJump1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_EatJump2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6528);
}

void ftKb_EatLanding_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_SpecialN_800F9070(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death3_cb = ftKb_Init_800EE74C;
    fp->death1_cb = ftKb_Init_800EE7B8;
}

void ftKb_SpecialN_800F9090(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->target_item_gobj != NULL && fp->kind == FTKIND_KIRBY &&
        fp->fv.kb.hat.kind == FTKIND_KIRBY)
    {
        bool capturing = false;
        if (fp->motion_id == ftKb_MS_SpecialNCapture1 ||
            fp->motion_id == ftKb_MS_SpecialAirNCapture1)
        {
            capturing = true;
        }
        it_802F28C8(fp->target_item_gobj, capturing, 0);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
    }
}

/// #ftKb_SpecialN_800F9110

/// #ftKb_MrSpecialN_Anim

void ftKb_MrSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftKb_MrSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// #ftKb_MrSpecialN_Coll

/// #fn_800F9260

/// #ftKb_SpecialNMr_800F93CC

/// #ftKb_MrSpecialAirN_Anim

void ftKb_MrSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Fall_IASA_Inner(gobj);
    }
}

void ftKb_MrSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// #ftKb_MrSpecialAirN_Coll

/// #ftKb_SpecialNLg_800F951C

/// #ftKb_SpecialNLg_800F9598

/// #ftKb_SpecialNLg_800F9614

/// #ftKb_SpecialNLg_800F9684

/// #ftKb_LgSpecialN_Anim

/// #ftKb_LgSpecialAirN_Anim

void ftKb_LgSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftKb_LgSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Fall_IASA_Inner(gobj);
    }
}

void ftKb_LgSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LgSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// #ftKb_LgSpecialN_Coll

/// #ftKb_LgSpecialAirN_Coll

/// #fn_800F98F4

/// #ftKb_SpecialNCa_800F99BC

/// #ftKb_SpecialNCa_800F9A54

void ftKb_CaSpecialN_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

/// #ftKb_CaSpecialAirN_Anim

/// #ftKb_CaSpecialN_IASA

/// #ftKb_CaSpecialAirN_IASA

/// #ftKb_CaSpecialN_Phys

/// #ftKb_CaSpecialAirN_Phys

/// #ftKb_CaSpecialN_Coll

/// #ftKb_CaSpecialAirN_Coll

/// #ftKb_SpecialNPk_800F9FD4

/// #ftKb_SpecialNPk_800FA064

/// #ftKb_PkSpecialN_Anim

/// #ftKb_PkSpecialAirN_Anim

/// #ftKb_PkSpecialN_IASA

/// #ftKb_PkSpecialAirN_IASA

void ftKb_PkSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PkSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// #ftKb_PkSpecialN_Coll

/// #ftKb_PkSpecialAirN_Coll

/// #ftKb_SpecialNKp_800FA588

/// #ftKb_SpecialNKp_800FA7D4

/// #ftKb_SpecialNKp_800FA83C

/// #ftKb_SpecialNKp_800FA878

/// #ftKb_SpecialNKp_800FA8B4

/// #ftKb_SpecialNKp_800FA958

/// #ftKb_KpSpecialNStart_Anim

/// #ftKb_KpSpecialN_Anim

/// #ftKb_KpSpecialNEnd_Anim

/// #ftKb_KpSpecialAirNStart_Anim

/// #ftKb_KpSpecialAirN_Anim

/// #ftKb_KpSpecialAirNEnd_Anim

/// #ftKb_KpSpecialNStart_IASA

/// #ftKb_KpSpecialN_IASA

/// #ftKb_KpSpecialNEnd_IASA

/// #ftKb_KpSpecialAirNStart_IASA

/// #ftKb_KpSpecialAirN_IASA

/// #ftKb_KpSpecialAirNEnd_IASA

void ftKb_KpSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_KpSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_KpSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_KpSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_KpSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_KpSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// #ftKb_KpSpecialNStart_Coll

/// #ftKb_KpSpecialN_Coll

/// #ftKb_KpSpecialNEnd_Coll

/// #ftKb_KpSpecialAirNStart_Coll

/// #ftKb_KpSpecialAirN_Coll

/// #ftKb_KpSpecialAirNEnd_Coll

/// #ftKb_SpecialNLk800FB394

void ftKb_SpecialNLk800FB418(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = gobj->user_data;
        if ((ft != NULL) && (ft->fv.kb.x74 != 0)) {
            ft->fv.kb.x74 = 0;
        }
    }
}

void ftKb_SpecialNLk800FB444(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = gobj->user_data;
        if ((ft != NULL) && (ft->fv.kb.x78 != 0)) {
            ft->fv.kb.x78 = 0;
        }
    }
}

/// #ftKb_SpecialNLk800FB470

/// #ftKb_SpecialNLk800FB500

/// #ftKb_SpecialNLk800FB5F4

/// #ftKb_SpecialNLk800FB6DC

/// #ftKb_SpecialNLk800FB800

/// #ftKb_SpecialNLk800FB840

/// #ftKb_SpecialNLk800FB880

/// #ftKb_SpecialNLk800FBA00

/// #ftKb_LkSpecialNStart_Anim

/// #ftKb_LkSpecialNLoop_Anim

/// #ftKb_LkSpecialNEnd_Anim

/// #ftKb_LkSpecialAirNStart_Anim

/// #ftKb_LkSpecialAirNLoop_Anim

/// #ftKb_LkSpecialAirNEnd_Anim

/// #ftKb_LkSpecialNStart_IASA

/// #ftKb_LkSpecialNLoop_IASA

/// #ftKb_LkSpecialNEnd_IASA

/// #ftKb_LkSpecialAirNStart_IASA

/// #ftKb_LkSpecialAirNLoop_IASA

/// #ftKb_LkSpecialAirNEnd_IASA

void ftKb_LkSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_LkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_LkSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// #ftKb_LkSpecialNStart_Coll

/// #ftKb_LkSpecialNLoop_Coll

/// #ftKb_LkSpecialNEnd_Coll

/// #ftKb_LkSpecialAirNStart_Coll

/// #ftKb_LkSpecialAirNLoop_Coll

/// #ftKb_LkSpecialAirNEnd_Coll

/// #ftKb_SpecialNSs_800FCC14

/// #ftKb_SpecialNSs_800FCC6C

/// #ftKb_SpecialNSs_800FCCBC

/// #ftKb_SpecialNSs_800FCD04

/// #ftKb_SpecialNSs_800FCD60

/// #ftKb_SpecialNSs_800FCDE0

/// #ftKb_SpecialNSs_800FCF74

/// #ftKb_SpecialNSs_800FD020

/// #ftKb_SsSpecialNStart_Anim

/// #ftKb_SsSpecialNHold_Anim

/// #ftKb_SsSpecialNCancel_Anim

/// #ftKb_SsSpecialN_Anim

/// #ftKb_SsSpecialAirNStart_Anim

/// #ftKb_SsSpecialAirN_Anim

/// #ftKb_SsSpecialNStart_IASA

/// #ftKb_SsSpecialNHold_IASA

/// #ftKb_SsSpecialNCancel_IASA

/// #ftKb_SsSpecialN_IASA

/// #ftKb_SsSpecialAirNStart_IASA

/// #ftKb_SsSpecialAirN_IASA

void ftKb_SsSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialNHold_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SsSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SsSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x19B, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

/// #ftKb_SsSpecialNHold_Coll

void ftKb_SsSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x19c, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x19c, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x197, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SsSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x19a, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

/// #ftKb_SpecialNFx_800FDC00

/// #ftKb_SpecialNFx_800FDC70

void fn_800FDCE0(Fighter_GObj* gobj)
{
    FORCE_PAD_STACK_8;

    ft_800892A0(gobj);
    ft_80089824(gobj);
}

bool ftKb_SpecialNFx_800FDD14(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = gobj->user_data;
        if (ft != NULL) {
            if (!ft->fv.kb.xB0) {
                return true;
            }
            return false;
        }
    }
    return true;
}

/// #ftKb_SpecialNFx_800FDD4C

/// #ftKb_SpecialNFx_800FDDF4

void ftKb_SpecialNFx_800FDEB4(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = gobj->user_data;
        if ((ft != NULL) && (ft->fv.kb.xB0 != 0)) {
            ft->fv.kb.xB0 = 0;
        }
    }
}

/// #ftKb_SpecialNFx_800FDEE0

/// #ftKb_SpecialNFx_800FDF30

void fn_800FE0E0(Fighter_GObj* gobj)
{
    ftKb_SpecialNFx_800FDF30(gobj);
}

/// #ftKb_SpecialNFx_800FE100

/// #ftKb_SpecialNFx_800FE240

/// #ftKb_FxSpecialNStart_Anim

/// #ftKb_FxSpecialNLoop_Anim

/// #ftKb_FxSpecialNEnd_Anim

/// #ftKb_FxSpecialAirNStart_Anim

/// #ftKb_FxSpecialAirNLoop_Anim

/// #ftKb_FxSpecialAirNEnd_Anim

void ftKb_FxSpecialNStart_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->cmd_vars[0] != 0) && (ft->input.x668 & HSD_PAD_B)) {
        ft->mv.kb.specialhi.x0 = 1;
    }
}

void ftKb_FxSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->cmd_vars[0] != 0) && (ft->input.x668 & HSD_PAD_B)) {
        ft->mv.kb.specialhi.x0 = 1;
    }
}

/// #ftKb_FxSpecialNEnd_IASA

void ftKb_FxSpecialAirNStart_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->cmd_vars[0] != 0) && (ft->input.x668 & HSD_PAD_B)) {
        ft->mv.kb.specialhi.x0 = 1;
    }
}

void ftKb_FxSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->cmd_vars[0] != 0) && (ft->input.x668 & HSD_PAD_B)) {
        ft->mv.kb.specialhi.x0 = 1;
    }
}

/// #ftKb_FxSpecialAirNEnd_IASA

void ftKb_FxSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_FxSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_FxSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_FxSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_FxSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_FxSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_FxSpecialNStart_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

void ftKb_FxSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

void ftKb_FxSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

void ftKb_FxSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

void ftKb_FxSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

void ftKb_FxSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

bool ftKb_SpecialNNs_800FEC78(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.ns_flash_gobj != NULL &&
            (fp->motion_id == ftKb_MS_NsSpecialNHold0 ||
             fp->motion_id == ftKb_MS_NsSpecialAirNHold0))
        {
            return true;
        }
    }
    return false;
}

void ftKb_SpecialNNs_800FECBC(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.ns_flash_gobj != NULL) {
            fp->fv.kb.ns_flash_gobj = NULL;
        }
    }
}

/// #ftKb_SpecialNNs_800FECE8

void ftKb_SpecialNNs_800FED38(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNStart, Ft_MF_None, 0, 1,
                              0, NULL);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4 * 4);
        da = fp->dat_attrs;
        fp->mv.kb.specialn_ns.frames_to_loop_charge_ground =
            da->specialn_ns_frames_to_loop_charge_ground;
        fp->mv.kb.specialn_ns.frames_to_loop_charge_air =
            da->specialn_ns_frames_to_loop_charge_air;
        fp->mv.kb.specialn_ns.falling_acceleration_delay =
            da->specialn_ns_falling_acceleration_delay;
        fp->fv.kb.ns_flash_gobj = NULL;
        fp->mv.kb.specialn_ns.charge_release_delay =
            da->specialn_ns_charge_release_delay;
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_SpecialNNs_800FEDD0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNStart, 0, 0, 1, 0, 0);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->self_vel.y = 0;
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4 * 4);
        da = fp->dat_attrs;
        fp->mv.kb.specialn_ns.frames_to_loop_charge_ground =
            da->specialn_ns_frames_to_loop_charge_ground;
        fp->mv.kb.specialn_ns.frames_to_loop_charge_air =
            da->specialn_ns_frames_to_loop_charge_air;
        fp->mv.kb.specialn_ns.falling_acceleration_delay =
            da->specialn_ns_falling_acceleration_delay;
        fp->fv.kb.ns_flash_gobj = NULL;
        fp->mv.kb.specialn_ns.charge_release_delay =
            da->specialn_ns_charge_release_delay;
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_NsSpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 436, 0, 0, 1, 0, NULL);
        {
            Fighter* fp = GET_FIGHTER(gobj);
            Vec3 flash_pos;
            PAD_STACK(4 * 5);
            if (fp->fv.kb.ns_flash_gobj == NULL) {
                lb_8000B1CC(fp->parts[FtPart_WaistN].joint, NULL, &flash_pos);
                flash_pos.z = 0;
                flash_pos.y += fp->x34_scale.y * 3;
                {
                    HSD_GObj* flash_gobj =
                        it_802AA8C0(gobj, &flash_pos, 145, fp->facing_dir);
                    fp->fv.kb.ns_flash_gobj = flash_gobj;
                    if (flash_gobj != NULL) {
                        fp->death2_cb = ftKb_Init_800EE74C;
                        fp->take_dmg_cb = ftKb_Init_800EE7B8;
                    }
                }
            }
        }
        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    }
}

void ftKb_NsSpecialNHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int flash_timer_min = fp->mv.kb.specialn_ns.frames_to_loop_charge_ground;
    if (flash_timer_min != 0) {
        fp->mv.kb.specialn_ns.frames_to_loop_charge_ground =
            flash_timer_min - 1;
    }
    if (fp->fv.kb.ns_flash_gobj == NULL) {
        int flash_timer_delay =
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air;
        if (flash_timer_delay != 0) {
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air =
                flash_timer_delay - 1;
        }
    }
    if (fp->fv.kb.ns_flash_gobj == NULL) {
        if (fp->mv.kb.specialn_ns.frames_to_loop_charge_ground <= 0 &&
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air <= 0)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNEnd, 0, 0, 1, 0,
                                      NULL);
            return;
        }
        if (fp->motion_id != ftKb_MS_NsSpecialNHold1) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNHold1, 0,
                                      fp->cur_anim_frame, 1, 0, NULL);
        }
    } else {
        if (it_802AA7E4(fp->fv.kb.ns_flash_gobj) != gobj) {
            fp->fv.kb.ns_flash_gobj = NULL;
            return;
        }
        if (it_802AA7F0(fp->fv.kb.ns_flash_gobj) == 1 &&
            fp->motion_id != ftKb_MS_NsSpecialNHold1)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNHold1, 0,
                                      fp->cur_anim_frame, 1, 0, NULL);
        }
    }
}

/// #ftKb_NsSpecialNEnd_Anim

/// #ftKb_NsSpecialAirNStart_Anim

/// #ftKb_NsSpecialAirNHold_Anim

/// #ftKb_NsSpecialAirNEnd_Anim

/// #ftKb_NsSpecialNStart_IASA

/// #ftKb_NsSpecialNHold_IASA

/// #ftKb_NsSpecialNEnd_IASA

/// #ftKb_NsSpecialAirNStart_IASA

/// #ftKb_NsSpecialAirNHold_IASA

/// #ftKb_NsSpecialAirNEnd_IASA

void ftKb_NsSpecialNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.kb.specialn_ns.falling_acceleration_delay != 0) {
        fp->mv.kb.specialn_ns.falling_acceleration_delay--;
    }
    ft_80084F3C(gobj);
}

void ftKb_NsSpecialNHold_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_NsSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// #ftKb_NsSpecialAirNStart_Phys

/// #ftKb_NsSpecialAirNHold_Phys

/// #ftKb_NsSpecialAirNEnd_Phys

/// #ftKb_NsSpecialNStart_Coll

/// #ftKb_NsSpecialNHold_Coll

/// #ftKb_NsSpecialNEnd_Coll

/// #ftKb_NsSpecialAirNStart_Coll

/// #ftKb_NsSpecialAirNHold_Coll

/// #ftKb_NsSpecialAirNEnd_Coll

/// #ftKb_SpecialNDk_800FF8EC

/// #ftKb_SpecialNDk_800FFA10

/// #ftKb_DkSpecialNStart_Anim

/// #ftKb_DkSpecialNLoop_Anim

/// #ftKb_DkSpecialNCancel_Anim

/// #ftKb_DkSpecialN_Anim

/// #ftKb_DkSpecialNFull_Anim

/// #ftKb_DkSpecialAirNStart_Anim

/// #ftKb_DkSpecialAirNLoop_Anim

/// #ftKb_DkSpecialAirNCancel_Anim

/// #ftKb_DkSpecialAirN_Anim

/// #ftKb_DkSpecialAirNFull_Anim

/// #ftKb_DkSpecialNStart_IASA

/// #ftKb_DkSpecialNLoop_IASA

/// #ftKb_DkSpecialNCancel_IASA

/// #ftKb_DkSpecialN_IASA

/// #ftKb_DkSpecialNFull_IASA

/// #ftKb_DkSpecialAirNStart_IASA

/// #ftKb_DkSpecialAirNLoop_IASA

/// #ftKb_DkSpecialAirNCancel_IASA

/// #ftKb_DkSpecialAirN_IASA

/// #ftKb_DkSpecialAirNFull_IASA

void ftKb_DkSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNFull_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNFull_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

static void ftKb_DkSpecialNStart_Coll_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp = gobj->user_data;
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftKb_DkSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1CC, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1CD, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1CE, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1CF, 0x0C4D508EU, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1D0, 0x0C4D508EU, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1C7, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1C8, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

/// #ftKb_DkSpecialAirNCancel_Coll

/// #ftKb_DkSpecialAirN_Coll

/// #ftKb_DkSpecialAirNFull_Coll

void ftKb_SpecialNPr_80100DE0(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->fv.kb.xBC = 0;
    efLib_DestroyAll(gobj);
}

/// #fn_80100E0C

void fn_80100F60(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

/// #ftKb_SpecialNPr_80100F94

/// #ftKb_SpecialNPr_801010D4

/// #ftKb_SpecialNPr_8010131C

/// #ftKb_SpecialNPr_8010140C

/// #ftKb_SpecialNPr_80101560

/// #ftKb_SpecialNPr_80101618

/// #ftKb_PrSpecialNStart_Anim

/// #ftKb_PrSpecialNLoop_Anim

/// #ftKb_PrSpecialNFull_Anim

/// #ftKb_PrSpecialN1_Anim

/// #ftKb_PrSpecialNTurn_Anim

/// #ftKb_PrSpecialNEnd_Anim

/// #ftKb_PrSpecialAirNStart_Anim

/// #ftKb_PrSpecialAirNLoop_Anim

/// #ftKb_PrSpecialAirNFull_Anim

/// #ftKb_PrSpecialAirN_Anim

/// #ftKb_PrSpecialN_Anim

/// #ftKb_PrSpecialAirNEndR_Anim

/// #ftKb_PrSpecialNHit_Anim

/// #ftKb_PrSpecialNStart_IASA

/// #ftKb_PrSpecialNLoop_IASA

/// #ftKb_PrSpecialNFull_IASA

/// #ftKb_PrSpecialN1_IASA

/// #ftKb_PrSpecialNTurn_IASA

/// #ftKb_PrSpecialNEnd_IASA

/// #ftKb_PrSpecialAirNStart_IASA

/// #ftKb_PrSpecialAirNLoop_IASA

/// #ftKb_PrSpecialAirNFull_IASA

/// #ftKb_PrSpecialAirN_IASA

/// #ftKb_PrSpecialN_IASA

/// #ftKb_PrSpecialAirNEndR_IASA

/// #ftKb_PrSpecialNHit_IASA

void ftKb_PrSpecialNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->xE4_ground_accel_1 = 0.0f;
    ft->gr_vel = 0.0f;
    ft->self_vel.x = 0.0001f * ft->facing_dir;
    ft->self_vel.y = 0.0f;
    ft->x74_anim_vel.y = 0.0f;
    ft->x74_anim_vel.x = 0.0f;
}

void ftKb_PrSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->xE4_ground_accel_1 = 0.0f;
    ft->gr_vel = 0.0f;
    ft->self_vel.x = 0.0001f * ft->facing_dir;
    ft->self_vel.y = 0.0f;
    ft->x74_anim_vel.y = 0.0f;
    ft->x74_anim_vel.x = 0.0f;
}

void ftKb_PrSpecialNFull_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->xE4_ground_accel_1 = 0.0f;
    ft->gr_vel = 0.0f;
    ft->self_vel.x = 0.0001f * ft->facing_dir;
    ft->self_vel.y = 0.0f;
    ft->x74_anim_vel.y = 0.0f;
    ft->x74_anim_vel.x = 0.0f;
}

/// #ftKb_PrSpecialN1_Phys

/// #ftKb_PrSpecialNTurn_Phys

/// #ftKb_PrSpecialNEnd_Phys

void ftKb_PrSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftCommonData* cd = ft->dat_attrs;
    ftCommon_Fall(ft, cd->x2BC, cd->x2C0);
}

void ftKb_PrSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftCommonData* cd = ft->dat_attrs;
    ftCommon_Fall(ft, cd->x2BC, cd->x2C0);
}

void ftKb_PrSpecialAirNFull_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftCommonData* cd = ft->dat_attrs;
    ftCommon_Fall(ft, cd->x2BC, cd->x2C0);
}

/// #ftKb_PrSpecialAirN_Phys

/// #ftKb_PrSpecialN_Phys

void ftKb_PrSpecialAirNEndR_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftCommonData* cd = ft->dat_attrs;
    ftCommon_Fall(ft, cd->x2BC, cd->x2C0);
}

/// #ftKb_PrSpecialNHit_Phys

/// #ftKb_PrSpecialNStart_Coll

/// #ftKb_PrSpecialNLoop_Coll

/// #ftKb_PrSpecialNFull_Coll

/// #ftKb_PrSpecialN1_Coll

/// #ftKb_PrSpecialNTurn_Coll

/// #ftKb_PrSpecialNEnd_Coll

/// #ftKb_PrSpecialAirNStart_Coll

/// #ftKb_PrSpecialAirNLoop_Coll

/// #ftKb_PrSpecialAirNFull_Coll

/// #ftKb_PrSpecialAirN_Coll

/// #ftKb_PrSpecialN_Coll

/// #ftKb_PrSpecialAirNEndR_Coll

/// #ftKb_PrSpecialNHit_Coll

/// #fn_80105978

/// #fn_80105A34

/// #fn_80105AB0

/// #ftKb_SpecialNZd_80105B2C

/// #ftKb_SpecialNZd_80105BA8

/// #ftKb_ZdSpecialN_Anim

/// #ftKb_ZdSpecialAirN_Anim

/// #ftKb_ZdSpecialN_IASA

/// #ftKb_ZdSpecialAirN_IASA

void ftKb_ZdSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEF8(gobj);
}

/// #ftKb_ZdSpecialAirN_Phys

void ftKb_ZdSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNSk_80105E8C(gobj);
    }
}

void ftKb_ZdSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNSk_80105F3C(gobj);
    }
}

/// #ftKb_SpecialNSk_80105E8C

/// #ftKb_SpecialNSk_80105F3C

/// #fn_80105FEC

bool ftKb_SpecialNSk_80105FF0(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (gobj != NULL) {
        if (ft->fv.kb.xB8 != 0) {
            return false;
        }
        return true;
    }
    return true;
}

s32 ftKb_SpecialNSk_80106020(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (gobj != NULL) {
        return ft->fv.kb.xB4;
    }
    return 0;
}

/// #ftKb_SpecialNSk_8010603C

/// #ftKb_SpecialNSk_8010612C

/// #ftKb_SpecialNSk_801061E4

/// #ftKb_SkSpecialNStart_Anim

/// #ftKb_SkSpecialNLoop_Anim

void ftKb_SkSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xB8 = 0;
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

/// #ftKb_SkSpecialNEnd_Anim

/// #ftKb_SkSpecialAirNStart_Anim

/// #ftKb_SkSpecialAirNLoop_Anim

/// #ftKb_SkSpecialAirNCancel_Anim

/// #ftKb_SkSpecialAirNEnd_Anim

/// #ftKb_SkSpecialNStart_IASA

/// #ftKb_SkSpecialNLoop_IASA

/// #ftKb_SkSpecialNCancel_IASA

/// #ftKb_SkSpecialNEnd_IASA

/// #ftKb_SkSpecialAirNStart_IASA

/// #ftKb_SkSpecialAirNLoop_IASA

/// #ftKb_SkSpecialAirNCancel_IASA

/// #ftKb_SkSpecialAirNEnd_IASA

void ftKb_SkSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1d7, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1d8, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

/// #ftKb_SkSpecialNCancel_Coll

/// #ftKb_SkSpecialNEnd_Coll

void ftKb_SkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) != GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1d3, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) != GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1d4, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SkSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    FORCE_PAD_STACK_16;

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCo_Landing_Enter_Basic(gobj);
    }
}

/// #ftKb_SkSpecialAirNEnd_Coll

/// #fn_80106DB0

/// #ftKb_SpecialNMt_80106F44

/// #ftKb_SpecialNMt_80106F9C

/// #ftKb_SpecialNMt_80106FEC

/// #ftKb_SpecialNMt_80107040

/// #ftKb_SpecialNMt_8010709C

/// #ftKb_SpecialNMt_80107130

/// #ftKb_SpecialNMt_801071FC

/// #ftKb_SpecialNMt_80107410

/// #ftKb_SpecialNMt_80107568

/// #ftKb_SpecialNMt_80107638

/// #ftKb_MtSpecialNStart_Anim

/// #ftKb_MtSpecialNLoop_Anim

void ftKb_MtSpecialNLoopFull_Anim(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    PAD_STACK(4);
    ft->mv.kb.specialhi.x8 = 1;
    ft->fv.kb.x9C = da->specialn_mt_charge_time;
}

/// #ftKb_MtSpecialNCancel_Anim

/// #ftKb_MtSpecialNEnd_Anim

/// #ftKb_MtSpecialAirNStart_Anim

/// #ftKb_MtSpecialAirNLoop_Anim

void ftKb_MtSpecialAirNLoopFull_Anim(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    PAD_STACK(4);
    ft->mv.kb.specialhi.x8 = 0;
    ft->fv.kb.x9C = da->specialn_mt_charge_time;
}

/// #ftKb_MtSpecialAirNCancel_Anim

/// #ftKb_MtSpecialAirNEnd_Anim

void ftKb_MtSpecialNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_MtSpecialNLoop_IASA

/// #ftKb_MtSpecialNLoopFull_IASA

void ftKb_MtSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_MtSpecialAirNLoop_IASA

/// #ftKb_MtSpecialAirNLoopFull_IASA

void ftKb_MtSpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MtSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialNLoopFull_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MtSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialAirNLoopFull_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MtSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1f9, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1fa, 0x0C4C5280U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialNLoopFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1fb, 0x0C4C5280U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1fc, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1fd, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1f4, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1f5, 0x0C4C5280U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNLoopFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1f6, 0x0C4C5280U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1f7, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_MtSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1f8, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
    }
}

void ftKb_SpecialNIc_80108CE8(Fighter_GObj* gobj, Item_GObj* it_gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (it_gobj == ft->fv.kb.xC0) {
        ft->fv.kb.xC0 = NULL;
    }
}

/// #ftKb_SpecialNIc_80108D04

/// #ftKb_SpecialNIc_80108D64

/// #ftKb_SpecialNIc_80108E14

/// #ftKb_PpSpecialN_Anim

/// #ftKb_PpSpecialAirN_Anim

void ftKb_PpSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PpSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_PpSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PpSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// #ftKb_PpSpecialN_Coll

/// #ftKb_PpSpecialAirN_Coll

/// #fn_801090D4

Fighter_Part ftKb_SpecialNYs_80109238(Fighter_GObj* gobj)
{
    return ftParts_GetBoneIndex(GET_FIGHTER(gobj), FtPart_TransN2);
}

void ftKb_SpecialNYs_80109260(Fighter_GObj* gobj, Vec3* vec)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    vec->x = -ft->facing_dir * da->specialn_ys_initial_horizontal_momentum;
    vec->y = da->specialn_ys_initial_vertical_momentum;
    vec->z = 0.0f;
}

float ftKb_SpecialNYs_80109290(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->facing_dir;
}

f32 ftKb_SpecialNYs_8010929C(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    return da->specialn_ys_damage_multiplier;
}

f32 ftKb_SpecialNYs_801092AC(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    return da->specialn_ys_unk;
}

f32 ftKb_SpecialNYs_801092BC(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    return da->specialn_ys_growth_time;
}

f32 ftKb_SpecialNYs_801092CC(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    return da->specialn_ys_base_duration;
}

f32 ftKb_SpecialNYs_801092DC(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_egg_breakout_resistance;
}

f32 ftKb_SpecialNYs_801092F4(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_frames_reduced_per_input;
}

f32 ftKb_SpecialNYs_8010930C(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_unk1;
}

f32 ftKb_SpecialNYs_80109324(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_unk2;
}

int ftKb_SpecialNYs_8010933C(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_iframes_on_release;
}

void ftKb_SpecialNYs_80109354(Vec3* v)
{
    ftKb_DatAttrs* cd = gFtDataList[FTKIND_KIRBY]->ext_attr;
    v->x = cd->specialn_ys_horizontal_velocity_on_breakout;
    v->y = cd->specialn_ys_vertical_velocity_on_breakout;
    v->z = 0.0f;
}

float ftKb_SpecialNYs_80109380(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* cd = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return cd->specialn_ys_unk3 / cd->specialn_ys_damage_multiplier;
}

ftDynamics* ftKb_SpecialNYs_801093A0(Fighter_GObj* gobj)
{
    return ft_80459B88.hats[FTKIND_SAMUS]->hat_dynamics[0];
}

/// #ftKb_SpecialNYs_801093B4

/// #ftKb_SpecialNYs_8010941C

/// #ftKb_SpecialNYs_801094FC

/// #fn_801095DC

/// #fn_80109680

/// #fn_80109714

/// #fn_801097B8

/// #fn_8010984C

/// #fn_801098EC

/// #fn_8010998C

/// #fn_80109A08

/// #fn_80109A84

/// #fn_80109B00

/// #fn_80109B7C

/// #fn_80109BF8

/// #fn_80109C74

/// #fn_80109CF0

void ftKb_YsSpecialN1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_YsSpecialAirNCapture2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

/// #ftKb_YsSpecialAirNCapture1_Anim

/// #ftKb_YsSpecialNCapture1_Anim

/// #ftKb_YsSpecialAirCapture2_Anim

/// #ftKb_YsSpecialAirCapture1_Anim

/// #ftKb_YsSpecialNCapture2_0_Anim

/// #ftKb_YsSpecialNCapture2_1_Anim

/// #ftKb_YsSpecialAirN2_1_Anim

/// #ftKb_YsSpecialAirN2_0_Anim

void ftKb_YsSpecialN1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialAirNCapture2_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialAirNCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialNCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialAirCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialAirCapture2_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialNCapture2_0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialNCapture2_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialAirN2_1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialAirN2_0_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialN1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8010984C);
}

void ftKb_YsSpecialAirNCapture2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_801098EC);
}

void ftKb_YsSpecialAirNCapture1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8010998C);
}

void ftKb_YsSpecialNCapture1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_80109A08);
}

void ftKb_YsSpecialAirCapture2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80109A84);
}

void ftKb_YsSpecialAirCapture1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80109B00);
}

void ftKb_YsSpecialNCapture2_0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_80109B7C);
}

void ftKb_YsSpecialNCapture2_1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_80109BF8);
}

void ftKb_YsSpecialAirN2_1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80109C74);
}

void ftKb_YsSpecialAirN2_0_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80109CF0);
}

/// #ftKb_SpecialNYs_8010A8BC

/// #fn_8010A930

void ftCo_CaptureKirbyYoshi_Anim(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_Coll(Fighter_GObj* gobj) {}

void ftKb_SpecialNYs_8010AA2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->invisible = true;
    ftColl_8007B62C(gobj, 2);
}

/// #fn_8010AA64

/// #ftKb_SpecialNYs_8010AC78

/// #ftCo_KirbyYoshiEgg_Anim

void ftCo_KirbyYoshiEgg_IASA(Fighter_GObj* gobj) {}

void ftCo_KirbyYoshiEgg_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((enum GroundOrAir) fp->ground_or_air == GA_Ground) {
        ft_80084F3C(gobj);
        return;
    }
    ft_80084DB0(gobj);
}

void ftCo_KirbyYoshiEgg_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((enum GroundOrAir) fp->ground_or_air == GA_Ground) {
        ft_8008403C(gobj, fn_8010B148);
        return;
    }
    ft_80082C74(gobj, fn_8010B124);
}

void fn_8010B124(Fighter_GObj* gobj)
{
    ftCommon_8007D7FC(gobj->user_data);
}

void fn_8010B148(Fighter_GObj* gobj)
{
    ftCommon_8007D5D4(gobj->user_data);
}

/// #fn_8010B16C

void fn_8010B1D4(Fighter_GObj* gobj)
{
    Fighter_UpdateModelScale(gobj);
}

/// #fn_8010B1F4

void fn_8010B2E8(Fighter_GObj* gobj)
{
    ftKb_Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->mv.kb.specialn_ms.cur_frame = 0;
}

void ftKb_SpecialNMs_8010B2FC(HSD_GObj* gobj)
{
    PAD_STACK(4 * 6);
    {
        ftKb_DatAttrs* da;
        struct ftKb_SpecialNMs_DatAttrs* ms_da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ms_da = &da->ms;
        } else {
            ms_da = &da->fe;
        }

        // InStateChange callback
        fp->x21EC = fn_8010B2E8;

        fp->gr_vel = fp->gr_vel / ms_da->air_horizontal_momentum_preservation;
    }

    {
        ftKirby_MotionState msid;
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                msid = ftKb_MS_MsSpecialNStart;
            } else {
                msid = ftKb_MS_FeSpecialNStart;
            }
        }
        Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    }

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        Vec3 scale;

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ftCommon_SetAccessory(fp, ft_80459B88.x0->x0[FTKIND_MARS].next);
        } else {
            ftCommon_SetAccessory(fp, ft_80459B88.x0->x0[FTKIND_EMBLEM].next);
        }

        scale.x = scale.y = scale.z = ftCommon_GetModelScale(fp);
        HSD_JObjSetScale(fp->x20A0_accessory, &scale);
        lb_8000C2F8(
            fp->x20A0_accessory,
            fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint);
    }
}

/// #ftKb_SpecialNMs_8010B4A0

/// #ftKb_MsSpecialNStart_Anim

void ftKb_MsSpecialAirNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNMs_8010BC90(gobj);
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                ftCo_800BFFD0(fp, 99, 0);
            } else {
                ftCo_800BFFD0(fp, 100, 0);
            }
        }
    }
}

void ftKb_MsSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_MsSpecialNStart_Phys

/// #ftKb_MsSpecialAirNStart_Phys

void ftKb_MsSpecialNStart_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNMs_8010B868(gobj);
    }
}

/// #ftKb_MsSpecialAirNStart_Coll

/// #ftKb_SpecialNMs_8010B868

/// #ftKb_SpecialNMs_8010B8E0

/// #ftKb_MsSpecialNLoop_Anim

/// #ftKb_MsSpecialAirNLoop_Anim

void ftKb_MsSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->cmd_vars[0] = 0;
        ftKb_SpecialNPe_8010C148(gobj);
    }
}

void ftKb_MsSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->cmd_vars[0] = 0;
        ftKb_SpecialNPe_8010C1E8(gobj);
    }
}

void ftKb_MsSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MsSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// #ftKb_MsSpecialNLoop_Coll

/// #ftKb_MsSpecialAirNLoop_Coll

/// #ftKb_SpecialNMs_8010BB50

/// #ftKb_SpecialNMs_8010BBC8

/// #ftKb_SpecialNMs_8010BC40

void ftKb_SpecialNMs_8010BC90(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 var_r4;

    if ((s32) fp->fv.gw.x2238_panicCharge == 0x12) {
        var_r4 = 0x1F1;
    } else {
        var_r4 = 0x217;
    }

    Fighter_ChangeMotionState(gobj, var_r4, 0x3200U, ftKb_Init_804D9570, 0,
                              ftKb_Init_804D9570, NULL);
}

/// #ftKb_MsSpecialNEnd_Anim

/// #ftKb_MsSpecialAirNEnd_Anim

void ftKb_MsSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MsSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MsSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNPe_8010BF90(gobj);
    }
}

/// #ftKb_MsSpecialAirNEnd_Coll

/// #ftKb_SpecialNPe_8010BF90

/// #ftKb_SpecialNPe_8010C06C

/// #ftKb_SpecialNPe_8010C148

/// #ftKb_SpecialNPe_8010C1E8

void fn_8010C288(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->cmd_vars[2]) {
        Vec3 pos;
        fp->cmd_vars[2] = true;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, 0, &pos);
        fp->fv.kb.xD0 =
            it_802BDE18(gobj, &pos, FtPart_R3rdNa, 134, fp->facing_dir);
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = &ftKb_Init_800EE74C;
            fp->take_dmg_cb = &ftKb_Init_800EE7B8;
        }
        fp->accessory4_cb = NULL;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;
    }
}

void fn_8010C344(HSD_GObj* arg0)
{
    PAD_STACK(4);
    {
        Fighter* fp = arg0->user_data;
        Vec3 pos;
        PAD_STACK(4 * 2);
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, 0, &pos);
        pos.y += 2.5f;
        pos.z = 0;
        it_802BE214(arg0, &pos, 135, fp->facing_dir);
        fp->accessory4_cb = NULL;
    }
}

void ftKb_SpecialNPe_8010C3C0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialNPe_8010C47C(gobj);
    fp->fv.kb.xD0 = NULL;
}

void ftKb_SpecialNPe_8010C3F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDF40(fp->fv.kb.xD0);
        ftKb_SpecialNPe_8010C3C0(gobj);
    }
}

void fn_8010C44C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDFA0(fp->fv.kb.xD0);
    }
}

void ftKb_SpecialNPe_8010C47C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDFC0(fp->fv.kb.xD0);
    }
}

bool ftKb_SpecialNPe_8010C4AC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id >= ftKb_MS_PeSpecialLw &&
        fp->motion_id <= ftKb_MS_PeSpecialAirLwHit)
    {
        return false;
    }
    return true;
}

static void inlineA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.kb.specialn_pe.facing_dir = fp->facing_dir;
    fp->accessory4_cb = fn_8010C288;
}

static void inlineA1(HSD_GObj* gobj, ftKirby_MotionState msid)
{
    Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    inlineA0(gobj);
}

void ftKb_SpecialNPe_8010C4D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    fp->self_vel.y = 0;
    inlineA1(gobj, ftKb_MS_PeSpecialLw);
}

void ftKb_SpecialNPe_8010C560(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    fp->self_vel.x /= da->specialn_pe_friction;
    inlineA1(gobj, ftKb_MS_PeSpecialAirLw);
}

static inline void doPeAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd_var1 = fp->cmd_vars[1];
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    u8 _[4 * 4] = { 0 };

    if (cmd_var1 == 1) {
        fp->cmd_vars[1] = 2;
        ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                        fn_8010CD88);
        fp->x221B_b3 = true;
        fp->shield_unk0 = da->specialn_pe_unk3;
        fp->shield_unk1 = da->specialn_pe_unk3;
    } else if (cmd_var1 == 0) {
        fp->x221B_b0 = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKb_PeSpecialLw_Anim(HSD_GObj* gobj)
{
    doPeAnim(gobj, ft_8008A2BC);
}

void ftKb_PeSpecialAirLw_Anim(HSD_GObj* gobj)
{
    doPeAnim(gobj, ftCo_Fall_Enter);
}

void ftKb_PeSpecialLw_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialAirLw_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

void ftKb_PeSpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd_var0 = fp->cmd_vars[0];
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    if (cmd_var0 >= 1) {
        if (cmd_var0 == 1) {
            fp->cmd_vars[0] = 2;
            if (!fp->fv.kb.xCC) {
                fp->fv.kb.xCC = true;
                fp->self_vel.y = da->specialn_pe_air_initial_vertical_momentum;
            } else {
                fp->self_vel.y = 0;
            }
        }
        ftCommon_Fall(fp, da->specialn_pe_fall_acceleration,
                      da->specialn_pe_unk2);
    } else {
        ftCommon_FallBasic(fp);
    }
    ftCommon_ApplyFrictionAir(
        fp, da->specialn_pe_air_horizontal_momentum_preservation);
    ftColl_8007AEE0(gobj);
}

void ftKb_PeSpecialLw_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNPe_8010C8D8(gobj);
    }
}

void ftKb_PeSpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftKb_SpecialNPe_8010C9CC(gobj);
    }
}

void ftKb_SpecialNPe_8010C8D8(HSD_GObj* gobj)
{
    /// @todo Flag names.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialAirLw, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 2;
    }
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = ftKb_Init_800EE74C;
            fp->take_dmg_cb = ftKb_Init_800EE7B8;
        }

        fp->accessory4_cb = fn_8010C288;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;

        if (fp->cmd_vars[1] == 2) {
            ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                            fn_8010CD88);
            fp->x221B_b3 = true;
        }
    }
}

void ftKb_SpecialNPe_8010C9CC(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xCC = false;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialLw, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4 * 2);
        da = fp->dat_attrs;
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = ftKb_Init_800EE74C;
            fp->take_dmg_cb = ftKb_Init_800EE7B8;
        }
        fp->accessory4_cb = fn_8010C288;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;

        if (fp->cmd_vars[1] == 2) {
            ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                            fn_8010CD88);
            fp->x221B_b3 = true;
        }
    }
}

static inline void doPeHitAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[3]) {
        fp->cmd_vars[3] = false;
        fp->accessory4_cb = fn_8010C344;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKb_PeSpecialLwHit_Anim(HSD_GObj* gobj)
{
    doPeHitAnim(gobj, ft_8008A2BC);
}

void ftKb_PeSpecialAirLwHit_Anim(HSD_GObj* gobj)
{
    doPeHitAnim(gobj, ftCo_Fall_Enter);
}

void ftKb_PeSpecialLwHit_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialAirLwHit_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialLwHit_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PeSpecialAirLwHit_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    ftCommon_Fall(fp, da->specialn_pe_fall_acceleration, da->specialn_pe_unk2);
    ftCommon_ApplyFrictionAir(
        fp, da->specialn_pe_air_horizontal_momentum_preservation);
}

void ftKb_PeSpecialLwHit_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNGw_8010CC6C(gobj);
    }
}

void ftKb_PeSpecialAirLwHit_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftKb_SpecialNGw_8010CCD4(gobj);
    }
}

void ftKb_SpecialNGw_8010CC6C(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialAirLwHit, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialNGw_8010CD44(gobj);
}

void ftKb_SpecialNGw_8010CCD4(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xCC = false;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialLwHit, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialNGw_8010CD44(gobj);
}

void ftKb_SpecialNGw_8010CD44(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        fp->death2_cb = ftKb_Init_800EE74C;
        fp->take_dmg_cb = ftKb_Init_800EE7B8;
    }
    fp->pre_hitlag_cb = fn_8010C44C;
    fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;
}

void fn_8010CD88(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.kb.specialn_pe.facing_dir = fp->specialn_facing_dir;
    {
        ftKirby_MotionState msid;
        if (fp->ground_or_air == GA_Ground) {
            msid = ftKb_MS_PeSpecialLwHit;
        } else {
            msid = ftKb_MS_PeSpecialAirLwHit;
        }
        Fighter_ChangeMotionState(gobj, msid, 0, 9, 1, 0, 0);
    }
    ftAnim_8006EBA4(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BE100(fp->fv.kb.xD0);
    }
    ftKb_SpecialNGw_8010CD44(gobj);
}

void fn_8010CE5C(Fighter_GObj* gobj);

void fn_8010CFB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_LThumbNb)].joint,
                NULL, &pos);
    fp->fv.kb.xDC = it_802C74D8(
        gobj, &pos, ftParts_GetBoneIndex(fp, FtPart_LThumbNb), fp->facing_dir);
    if (fp->fv.kb.xDC != NULL) {
        fp->death2_cb = ftKb_Init_800EE74C;
        fp->take_dmg_cb = ftKb_Init_800EE7B8;
    }
    fp->pre_hitlag_cb = fn_8010D100;
    fp->post_hitlag_cb = ftKb_SpecialNGw_8010D130;
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D074(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialNGw_8010D130(gobj);
    fp->fv.kb.xDC = NULL;
}

void ftKb_SpecialNGw_8010D0A8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C760C(fp->fv.kb.xDC);
        ftKb_SpecialNGw_8010D074(gobj);
    }
}

void fn_8010D100(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C7658(fp->fv.kb.xDC);
    }
}

void ftKb_SpecialNGw_8010D130(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C7678(fp->fv.kb.xDC);
    }
}

bool ftKb_SpecialNGw_8010D160(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id >= ftKb_MS_GwSpecialN &&
        fp->motion_id <= ftKb_MS_GwSpecialAirN)
    {
        return false;
    }
    return true;
}

/// #ftGameWatch_SpecialN_SetVars with callback arg
inline void setGwVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.kb.specialn_gw.isChefLoopDisable = false;
    fp->mv.kb.specialn_gw.maxSausage = 0;
    fp->accessory4_cb = fn_8010CFB0;
}

void ftKb_SpecialNGw_8010D188(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0.0F;
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    setGwVars(gobj);
}

void ftKb_SpecialNGw_8010D204(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    setGwVars(gobj);
}

void ftKb_GwSpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x20);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (fp->mv.kb.specialn_gw.maxSausage <
                da->specialn_gw_max_sausages_per_use &&
            !fp->mv.kb.specialn_gw.isChefLoopDisable)
        {
            ftKb_SpecialNGw_8010D660(gobj, da->specialn_gw_frame_on_repeat);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_GwSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x20);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (!fp->mv.kb.specialn_gw.isChefLoopDisable &&
            fp->mv.kb.specialn_gw.maxSausage <
                da->specialn_gw_max_sausages_per_use)
        {
            ftKb_SpecialNGw_8010D6D0(gobj, da->specialn_gw_frame_on_repeat);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_GwSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialn_gw.isChefLoopDisable = true;
    }
    if (fp->cmd_vars[1] != 0 && (fp->input.x668 & HSD_PAD_B) &&
        fp->mv.kb.specialn_gw.maxSausage <
            da->specialn_gw_max_sausages_per_use)
    {
        ftKb_SpecialNGw_8010D660(gobj, da->specialn_gw_frame_on_repeat);
    }
}

void ftKb_GwSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialn_gw.isChefLoopDisable = true;
    }
    if (fp->cmd_vars[1] != 0 && (fp->input.x668 & HSD_PAD_B) &&
        fp->mv.kb.specialn_gw.maxSausage <
            da->specialn_gw_max_sausages_per_use)
    {
        ftKb_SpecialNGw_8010D6D0(gobj, da->specialn_gw_frame_on_repeat);
    }
}

void ftKb_GwSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_GwSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_GwSpecialN_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNGw_8010D580(gobj);
    }
}

void ftKb_GwSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNGw_8010D5F0(gobj);
    }
}

void ftKb_SpecialNGw_8010D580(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0x0C4C508C,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);

    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D5F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0x0C4C508C,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);

    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8010CE5C;
}

static inline void inline1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.kb.specialn_gw.isChefLoopDisable = false;
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D660(Fighter_GObj* gobj, f32 arg1)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0x0C4C508C,
                              arg1 - 1.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    inline1(gobj);
}

void ftKb_SpecialNGw_8010D6D0(Fighter_GObj* gobj, f32 arg1)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0x0C4C508C,
                              arg1 - 1.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    inline1(gobj);
}
