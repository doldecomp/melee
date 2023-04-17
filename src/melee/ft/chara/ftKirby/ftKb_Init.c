#include "ft/forward.h"

#include "ftKirby/ftKb_Init.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <dolphin/mtx/types.h>

MotionState ftKb_Init_MotionStateTable[] = {
    { 295, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 296, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 298, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 300, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 302, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 303, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x0000006A, 0x01000000, ftCo_MultiJump_Anim, ftCo_MultiJump_IASA,
      ftCo_MultiJump_Phys, ftCo_MultiJump_Coll, ftCamera_UpdateCameraBox },
    { 52, 0x00240005, 0x06000000, ftKb_AttackDash_Anim, ftKb_AttackDash_IASA,
      ftKb_AttackDash_Phys, ftKb_AttackDash_Coll, ftCamera_UpdateCameraBox },
    { 52, 0x00240405, 0x06000000, ftKb_AttackDashAir_Anim,
      ftKb_AttackDashAir_IASA, ftKb_AttackDashAir_Phys,
      ftKb_AttackDashAir_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340011, 0x12000000, ftKb_SpecialNStart_Anim, NULL,
      ftKb_SpecialNStart_Phys, ftKb_SpecialNStart_Coll,
      ftCamera_UpdateCameraBox },
    { 306, 0x003C0011, 0x12000000, ftKb_SpecialNLoop_Anim,
      ftKb_SpecialNLoop_IASA, ftKb_SpecialNLoop_Phys, ftKb_SpecialNLoop_Coll,
      ftCamera_UpdateCameraBox },
    { 307, 0x00340011, 0x12000000, ftKb_SpecialNEnd_Anim, NULL,
      ftKb_SpecialNEnd_Phys, ftKb_SpecialNEnd_Coll, ftCamera_UpdateCameraBox },
    { 308, 0x00340011, 0x12000000, ftKb_SpecialNCapture_Anim, NULL,
      ftKb_SpecialNCapture_Phys, ftKb_SpecialNCapture_Coll,
      ftCamera_UpdateCameraBox },
    { 308, 0x00340011, 0x12000000, ftKb_MS_357_Anim, NULL, ftKb_MS_357_Phys,
      ftKb_MS_357_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340011, 0x12000000, ftKb_SpecialNCaptured_Anim, NULL,
      ftKb_SpecialNCaptured_Phys, ftKb_SpecialNCaptured_Coll,
      ftCamera_UpdateCameraBox },
    { 310, 0x00340011, 0x12400000, ftKb_SpecialNCaptureWait_Anim,
      ftKb_SpecialNCaptureWait_IASA, ftKb_SpecialNCaptureWait_Phys,
      ftKb_SpecialNCaptureWait_Coll, ftCamera_UpdateCameraBox },
    { 311, 0x00344011, 0x12000000, ftKb_SpecialNCaptureWalk_Anim,
      ftKb_SpecialNCaptureWalk_IASA, ftKb_SpecialNCaptureWalk_Phys,
      ftKb_SpecialNCaptureWalk_Coll, ftCamera_UpdateCameraBox },
    { 312, 0x00344011, 0x12000000, ftKb_SpecialNCaptureWalk_Anim,
      ftKb_SpecialNCaptureWalk_IASA, ftKb_SpecialNCaptureWalk_Phys,
      ftKb_SpecialNCaptureWalk_Coll, ftCamera_UpdateCameraBox },
    { 313, 0x00344011, 0x12000000, ftKb_SpecialNCaptureWalk_Anim,
      ftKb_SpecialNCaptureWalk_IASA, ftKb_SpecialNCaptureWalk_Phys,
      ftKb_SpecialNCaptureWalk_Coll, ftCamera_UpdateCameraBox },
    { 317, 0x00342011, 0x12000000, ftKb_SpecialNCaptureTurn_Anim, NULL,
      ftKb_SpecialNCaptureTurn_Phys, ftKb_SpecialNCaptureTurn_Coll,
      ftCamera_UpdateCameraBox },
    { 314, 0x00348011, 0x12000000, ftKb_SpecialNCaptureJumpSquat_Anim,
      ftKb_SpecialNCaptureJumpSquat_IASA, ftKb_SpecialNCaptureJumpSquat_Phys,
      ftKb_SpecialNCaptureJumpSquat_Coll, ftCamera_UpdateCameraBox },
    { 315, 0x00340011, 0x12000000, ftKb_SpecialNCaptureJump_Anim, NULL,
      ftKb_SpecialNCaptureJump_Phys, ftKb_SpecialNCaptureJump_Coll,
      ftCamera_UpdateCameraBox },
    { 316, 0x00340011, 0x12400000, ftKb_SpecialNCaptureLanding_Anim, NULL,
      ftKb_SpecialNCaptureLanding_Phys, ftKb_SpecialNCaptureLanding_Coll,
      ftCamera_UpdateCameraBox },
    { 318, 0x00340011, 0x12000000, ftKb_SpecialNDigest_Anim, NULL,
      ftKb_SpecialNDigest_Phys, ftKb_SpecialNDigest_Coll,
      ftCamera_UpdateCameraBox },
    { 318, 0x00340011, 0x12000000, ftKb_MS_368_Anim, NULL, ftKb_MS_368_Phys,
      ftKb_MS_368_Coll, ftCamera_UpdateCameraBox },
    { 319, 0x00340011, 0x12000000, ftKb_SpecialNSpit_Anim, NULL,
      ftKb_SpecialNSpit_Phys, ftKb_SpecialNSpit_Coll,
      ftCamera_UpdateCameraBox },
    { 319, 0x00340011, 0x12000000, ftKb_MS_370_Anim, NULL, ftKb_MS_370_Phys,
      ftKb_MS_370_Coll, ftCamera_UpdateCameraBox },
    { 320, 0x00340411, 0x12000000, ftKb_SpecialAirNStart_Anim, NULL,
      ftKb_SpecialAirNStart_Phys, ftKb_SpecialAirNStart_Coll,
      ftCamera_UpdateCameraBox },
    { 321, 0x003C0411, 0x12000000, ftKb_SpecialAirNLoop_Anim,
      ftKb_SpecialAirNLoop_IASA, ftKb_SpecialAirNLoop_Phys,
      ftKb_SpecialAirNLoop_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340411, 0x12000000, ftKb_SpecialAirNEnd_Anim, NULL,
      ftKb_SpecialAirNEnd_Phys, ftKb_SpecialAirNEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 308, 0x00340411, 0x12000000, ftKb_SpecialAirNCapture_Anim, NULL,
      ftKb_SpecialAirNCapture_Phys, ftKb_SpecialAirNCapture_Coll,
      ftCamera_UpdateCameraBox },
    { 308, 0x00340411, 0x12000000, ftKb_MS_375_Anim, NULL, ftKb_MS_375_Phys,
      ftKb_MS_375_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340411, 0x12000000, ftKb_SpecialAirNCaptured_Anim, NULL,
      ftKb_SpecialAirNCaptured_Phys, ftKb_SpecialAirNCaptured_Coll,
      ftCamera_UpdateCameraBox },
    { 310, 0x00340411, 0x12000000, ftKb_SpecialAirNCaptureWait_Anim,
      ftKb_SpecialAirNCaptureWait_IASA, ftKb_SpecialAirNCaptureWait_Phys,
      ftKb_SpecialAirNCaptureWait_Coll, ftCamera_UpdateCameraBox },
    { 318, 0x00340411, 0x12000000, ftKb_SpecialAirNDigest_Anim, NULL,
      ftKb_SpecialAirNDigest_Phys, ftKb_SpecialAirNDigest_Coll,
      ftCamera_UpdateCameraBox },
    { 318, 0x00340411, 0x12000000, ftKb_MS_379_Anim, NULL, ftKb_MS_379_Phys,
      ftKb_MS_379_Coll, ftCamera_UpdateCameraBox },
    { 319, 0x00340411, 0x12000000, ftKb_SpecialAirNSpit_Anim, NULL,
      ftKb_SpecialAirNSpit_Phys, ftKb_SpecialAirNSpit_Coll,
      ftCamera_UpdateCameraBox },
    { 319, 0x00340411, 0x12000000, ftKb_MS_381_Anim, NULL, ftKb_MS_381_Phys,
      ftKb_MS_381_Coll, ftCamera_UpdateCameraBox },
    { 317, 0x00342411, 0x12000000, ftKb_SpecialAirNCaptureTurn_Anim, NULL,
      ftKb_SpecialAirNCaptureTurn_Phys, ftKb_SpecialAirNCaptureTurn_Coll,
      ftCamera_UpdateCameraBox },
    { 322, 0x00340012, 0x13000000, ftKb_SpecialS_Anim, NULL,
      ftKb_SpecialS_Phys, ftKb_SpecialS_Coll, ftCamera_UpdateCameraBox },
    { 323, 0x00340412, 0x13000000, ftKb_SpecialAirS_Anim, NULL,
      ftKb_SpecialAirS_Phys, ftKb_SpecialAirS_Coll, ftCamera_UpdateCameraBox },
    { 324, 0x00340013, 0x14000000, ftKb_SpecialHiStart_Anim,
      ftKb_SpecialHiStart_IASA, ftKb_SpecialHiStart_Phys,
      ftKb_SpecialHiStart_Coll, ftCamera_UpdateCameraBox },
    { 325, 0x00340013, 0x14000000, ftKb_MS_386_Anim, ftKb_MS_386_IASA,
      ftKb_MS_386_Phys, ftKb_MS_386_Coll, ftCamera_UpdateCameraBox },
    { 326, 0x00340013, 0x14000000, ftKb_MS_387_Anim, ftKb_MS_387_IASA,
      ftKb_MS_387_Phys, ftKb_MS_387_Coll, ftCamera_UpdateCameraBox },
    { 327, 0x00340013, 0x14000000, ftKb_SpecialHiEnd_Anim,
      ftKb_SpecialHiEnd_IASA, ftKb_SpecialHiEnd_Phys, ftKb_SpecialHiEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 328, 0x00340413, 0x14000000, ftKb_SpecialAirHiStart_Anim,
      ftKb_SpecialAirHiStart_IASA, ftKb_SpecialAirHiStart_Phys,
      ftKb_SpecialAirHiStart_Coll, ftCamera_UpdateCameraBox },
    { 329, 0x00340413, 0x14000000, ftKb_SpecialAirHiApex_Anim,
      ftKb_SpecialAirHiApex_IASA, ftKb_SpecialAirHiApex_Phys,
      ftKb_SpecialAirHiApex_Coll, ftCamera_UpdateCameraBox },
    { 330, 0x00340413, 0x14000000, ftKb_SpecialHiSwordDescent_Anim,
      ftKb_SpecialHiSwordDescent_IASA, ftKb_SpecialHiSwordDescent_Phys,
      ftKb_SpecialHiSwordDescent_Coll, ftCamera_UpdateCameraBox },
    { 331, 0x00340413, 0x14000000, ftKb_SpecialAirHiEnd_Anim,
      ftKb_SpecialAirHiEnd_IASA, ftKb_SpecialAirHiEnd_Phys,
      ftKb_SpecialAirHiEnd_Coll, ftCamera_UpdateCameraBox },
    { 332, 0x00340214, 0x15000000, ftKb_SpecialLwStart_Anim,
      ftKb_SpecialLwStart_IASA, ftKb_SpecialLwStart_Phys,
      ftKb_SpecialLwStart_Coll, ftCamera_UpdateCameraBox },
    { 333, 0x00340214, 0x15000000, ftKb_SpecialLw_Anim, ftKb_SpecialLw_IASA,
      ftKb_SpecialLw_Phys, ftKb_SpecialLw_Coll, ftCamera_UpdateCameraBox },
    { 334, 0x00340214, 0x15000000, ftKb_SpecialLwEnd_Anim,
      ftKb_SpecialLwEnd_IASA, ftKb_SpecialLwEnd_Phys, ftKb_SpecialLwEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 335, 0x00340614, 0x15000000, ftKb_SpecialAirLwStart_Anim,
      ftKb_SpecialAirLwStart_IASA, ftKb_SpecialAirLwStart_Phys,
      ftKb_SpecialAirLwStart_Coll, ftCamera_UpdateCameraBox },
    { 336, 0x00340614, 0x15000000, ftKb_SpecialAirLw_Anim,
      ftKb_SpecialAirLw_IASA, ftKb_SpecialAirLw_Phys, ftKb_SpecialAirLw_Coll,
      ftCamera_UpdateCameraBox },
    { 337, 0x00340614, 0x15000000, ftKb_SpecialAirLwEnd_Anim,
      ftKb_SpecialAirLwEnd_IASA, ftKb_SpecialAirLwEnd_Phys,
      ftKb_SpecialAirLwEnd_Coll, ftCamera_UpdateCameraBox },
    { 338, 0x00340015, 0x16000000, ftKb_SpecialNMr_Anim, ftKb_SpecialNMr_IASA,
      ftKb_SpecialNMr_Phys, ftKb_SpecialNMr_Coll, ftCamera_UpdateCameraBox },
    { 339, 0x00340415, 0x16000000, ftKb_SpecialAirNMr_Anim,
      ftKb_SpecialAirNMr_IASA, ftKb_SpecialAirNMr_Phys,
      ftKb_SpecialAirNMr_Coll, ftCamera_UpdateCameraBox },
    { 340, 0x0034011A, 0x1B000000, ftKb_SpecialNLkCharge_Anim,
      ftKb_SpecialNLkCharge_IASA, ftKb_SpecialNLkCharge_Phys,
      ftKb_SpecialNLkCharge_Coll, ftCamera_UpdateCameraBox },
    { 341, 0x003C011A, 0x1B000000, ftKb_SpecialNLkFullyCharged_Anim,
      ftKb_SpecialNLkFullyCharged_IASA, ftKb_SpecialNLkFullyCharged_Phys,
      ftKb_SpecialNLkFullyCharged_Coll, ftCamera_UpdateCameraBox },
    { 342, 0x0034011A, 0x1B000000, ftKb_SpecialNLkFire_Anim,
      ftKb_SpecialNLkFire_IASA, ftKb_SpecialNLkFire_Phys,
      ftKb_SpecialNLkFire_Coll, ftCamera_UpdateCameraBox },
    { 343, 0x0034051A, 0x1B000000, ftKb_SpecialAirNLkCharge_Anim,
      ftKb_SpecialAirNLkCharge_IASA, ftKb_SpecialAirNLkCharge_Phys,
      ftKb_SpecialAirNLkCharge_Coll, ftCamera_UpdateCameraBox },
    { 344, 0x003C051A, 0x1B000000, ftKb_SpecialAirNLkFullyCharged_Anim,
      ftKb_SpecialAirNLkFullyCharged_IASA, ftKb_SpecialAirNLkFullyCharged_Phys,
      ftKb_SpecialAirNLkFullyCharged_Coll, ftCamera_UpdateCameraBox },
    { 345, 0x0034051A, 0x1B000000, ftKb_SpecialAirNLkFire_Anim,
      ftKb_SpecialAirNLkFire_IASA, ftKb_SpecialAirNLkFire_Phys,
      ftKb_SpecialAirNLkFire_Coll, ftCamera_UpdateCameraBox },
    { 346, 0x00340120, 0x21000000, ftKb_SpecialNSsStart_Anim,
      ftKb_SpecialNSsStart_IASA, ftKb_SpecialNSsStart_Phys,
      ftKb_SpecialNSsStart_Coll, ftCamera_UpdateCameraBox },
    { 347, 0x00340120, 0x21000000, ftKb_SpecialNSsLoop_Anim,
      ftKb_SpecialNSsLoop_IASA, ftKb_SpecialNSsLoop_Phys,
      ftKb_SpecialNSsLoop_Coll, ftCamera_UpdateCameraBox },
    { 348, 0x00340120, 0x21000000, ftKb_SpecialNSsEnd_Anim,
      ftKb_SpecialNSsEnd_IASA, ftKb_SpecialNSsEnd_Phys,
      ftKb_SpecialNSsEnd_Coll, ftCamera_UpdateCameraBox },
    { 349, 0x00340120, 0x21000000, ftKb_SpecialNSsFire_Anim,
      ftKb_SpecialNSsFire_IASA, ftKb_SpecialNSsFire_Phys,
      ftKb_SpecialNSsFire_Coll, ftCamera_UpdateCameraBox },
    { 350, 0x00340520, 0x21000000, ftKb_SpecialAirNSsStart_Anim,
      ftKb_SpecialAirNSsStart_IASA, ftKb_SpecialAirNSsStart_Phys,
      ftKb_SpecialAirNSsStart_Coll, ftCamera_UpdateCameraBox },
    { 351, 0x00340520, 0x21000000, ftKb_SpecialAirNSsFire_Anim,
      ftKb_SpecialAirNSsFire_IASA, ftKb_SpecialAirNSsFire_Phys,
      ftKb_SpecialAirNSsFire_Coll, ftCamera_UpdateCameraBox },
    { 352, 0x00340021, 0x22000000, ftKb_SpecialNYs_Anim, NULL,
      ftKb_SpecialNYs_Phys, ftKb_SpecialNYs_Coll, ftCamera_UpdateCameraBox },
    { 353, 0x00340021, 0x22000000, ftKb_SpecialNYsCaptureStart_Anim, NULL,
      ftKb_SpecialNYsCaptureStart_Phys, ftKb_SpecialNYsCaptureStart_Coll,
      ftCamera_UpdateCameraBox },
    { 353, 0x00340021, 0x22000000, ftKb_MS_415_Anim, NULL, ftKb_MS_415_Phys,
      ftKb_MS_415_Coll, ftCamera_UpdateCameraBox },
    { 354, 0x00340021, 0x12000000, ftKb_SpecialNYsCapture_Anim, NULL,
      ftKb_SpecialNYsCapture_Phys, ftKb_SpecialNYsCapture_Coll,
      ftCamera_UpdateCameraBox },
    { 354, 0x00340021, 0x12000000, ftKb_MS_417_Anim, NULL, ftKb_MS_417_Phys,
      ftKb_MS_417_Coll, ftCamera_UpdateCameraBox },
    { 355, 0x00340421, 0x22000000, ftKb_SpecialAirNYs_Anim, NULL,
      ftKb_SpecialAirNYs_Phys, ftKb_SpecialAirNYs_Coll,
      ftCamera_UpdateCameraBox },
    { 356, 0x00340421, 0x22000000, ftKb_SpecialAirNYsCaptureStart_Anim, NULL,
      ftKb_SpecialAirNYsCaptureStart_Phys, ftKb_SpecialAirNYsCaptureStart_Coll,
      ftCamera_UpdateCameraBox },
    { 356, 0x00340421, 0x22000000, ftKb_MS_420_Anim, NULL, ftKb_MS_420_Phys,
      ftKb_MS_420_Coll, ftCamera_UpdateCameraBox },
    { 357, 0x00340421, 0x22000000, ftKb_SpecialAirNYsCapture_Anim, NULL,
      ftKb_SpecialAirNYsCapture_Phys, ftKb_SpecialAirNYsCapture_Coll,
      ftCamera_UpdateCameraBox },
    { 357, 0x00340421, 0x22000000, ftKb_MS_422_Anim, NULL, ftKb_MS_422_Phys,
      ftKb_MS_422_Coll, ftCamera_UpdateCameraBox },
    { 358, 0x00340116, 0x17000000, ftKb_SpecialNFxStart_Anim,
      ftKb_SpecialNFxStart_IASA, ftKb_SpecialNFxStart_Phys,
      ftKb_SpecialNFxStart_Coll, ftCamera_UpdateCameraBox },
    { 359, 0x003C0116, 0x17000000, ftKb_SpecialNFxLoop_Anim,
      ftKb_SpecialNFxLoop_IASA, ftKb_SpecialNFxLoop_Phys,
      ftKb_SpecialNFxLoop_Coll, ftCamera_UpdateCameraBox },
    { 360, 0x00340116, 0x17000000, ftKb_SpecialNFxEnd_Anim,
      ftKb_SpecialNFxEnd_IASA, ftKb_SpecialNFxEnd_Phys,
      ftKb_SpecialNFxEnd_Coll, ftCamera_UpdateCameraBox },
    { 361, 0x00340516, 0x17000000, ftKb_SpecialAirNFxStart_Anim,
      ftKb_SpecialAirNFxStart_IASA, ftKb_SpecialAirNFxStart_Phys,
      ftKb_SpecialAirNFxStart_Coll, ftCamera_UpdateCameraBox },
    { 362, 0x003C0516, 0x17000000, ftKb_SpecialAirNFxLoop_Anim,
      ftKb_SpecialAirNFxLoop_IASA, ftKb_SpecialAirNFxLoop_Phys,
      ftKb_SpecialAirNFxLoop_Coll, ftCamera_UpdateCameraBox },
    { 363, 0x00340516, 0x17000000, ftKb_SpecialAirNFxEnd_Anim,
      ftKb_SpecialAirNFxEnd_IASA, ftKb_SpecialAirNFxEnd_Phys,
      ftKb_SpecialAirNFxEnd_Coll, ftCamera_UpdateCameraBox },
    { 364, 0x0034011F, 0x20000000, ftKb_SpecialNPk_Anim, ftKb_SpecialNPk_IASA,
      ftKb_SpecialNPk_Phys, ftKb_SpecialNPk_Coll, ftCamera_UpdateCameraBox },
    { 365, 0x0034051F, 0x20000000, ftKb_SpecialAirNPk_Anim,
      ftKb_SpecialAirNPk_IASA, ftKb_SpecialAirNPk_Phys,
      ftKb_SpecialAirNPk_Coll, ftCamera_UpdateCameraBox },
    { 366, 0x00340024, 0x25000000, ftKb_SpecialNLg_Anim, ftKb_SpecialNLg_IASA,
      ftKb_SpecialNLg_Phys, ftKb_SpecialNLg_Coll, ftCamera_UpdateCameraBox },
    { 367, 0x00340424, 0x25000000, ftKb_SpecialAirNLg_Anim,
      ftKb_SpecialAirNLg_IASA, ftKb_SpecialAirNLg_Phys,
      ftKb_SpecialAirNLg_Coll, ftCamera_UpdateCameraBox },
    { 368, 0x00340217, 0x18000000, ftKb_SpecialNCa_Anim, ftKb_SpecialNCa_IASA,
      ftKb_SpecialNCa_Phys, ftKb_SpecialNCa_Coll, ftCamera_UpdateCameraBox },
    { 369, 0x00340617, 0x18000000, ftKb_SpecialAirNCa_Anim,
      ftKb_SpecialAirNCa_IASA, ftKb_SpecialAirNCa_Phys,
      ftKb_SpecialAirNCa_Coll, ftCamera_UpdateCameraBox },
    { 370, 0x0034011C, 0x1D000000, ftKb_SpecialNNsStart_Anim,
      ftKb_SpecialNNsStart_IASA, ftKb_SpecialNNsStart_Phys,
      ftKb_SpecialNNsStart_Coll, ftCamera_UpdateCameraBox },
    { 371, 0x0034011C, 0x1D000000, ftKb_SpecialNNsCharge_Anim,
      ftKb_SpecialNNsCharge_IASA, ftKb_SpecialNNsCharge_Phys,
      ftKb_SpecialNNsCharge_Coll, ftCamera_UpdateCameraBox },
    { 372, 0x0034011C, 0x1D000000, ftKb_SpecialNNsCharge_Anim,
      ftKb_SpecialNNsCharge_IASA, ftKb_SpecialNNsCharge_Phys,
      ftKb_SpecialNNsCharge_Coll, ftCamera_UpdateCameraBox },
    { 373, 0x0034011C, 0x1D000000, ftKb_SpecialNNsEnd_Anim,
      ftKb_SpecialNNsEnd_IASA, ftKb_SpecialNNsEnd_Phys,
      ftKb_SpecialNNsEnd_Coll, ftCamera_UpdateCameraBox },
    { 374, 0x0034051C, 0x1D000000, ftKb_SpecialAirNNsStart_Anim,
      ftKb_SpecialAirNNsStart_IASA, ftKb_SpecialAirNNsStart_Phys,
      ftKb_SpecialAirNNsStart_Coll, ftCamera_UpdateCameraBox },
    { 375, 0x0034051C, 0x1D000000, ftKb_SpecialAirNNsCharge_Anim,
      ftKb_SpecialAirNNsCharge_IASA, ftKb_SpecialAirNNsCharge_Phys,
      ftKb_SpecialAirNNsCharge_Coll, ftCamera_UpdateCameraBox },
    { 376, 0x0034051C, 0x1D000000, ftKb_SpecialAirNNsCharge_Anim,
      ftKb_SpecialAirNNsCharge_IASA, ftKb_SpecialAirNNsCharge_Phys,
      ftKb_SpecialAirNNsCharge_Coll, ftCamera_UpdateCameraBox },
    { 377, 0x0034051C, 0x1D000000, ftKb_SpecialAirNNsEnd_Anim,
      ftKb_SpecialAirNNsEnd_IASA, ftKb_SpecialAirNNsEnd_Phys,
      ftKb_SpecialAirNNsEnd_Coll, ftCamera_UpdateCameraBox },
    { 378, 0x00340019, 0x1A000000, ftKb_SpecialNKpStart_Anim,
      ftKb_SpecialNKpStart_IASA, ftKb_SpecialNKpStart_Phys,
      ftKb_SpecialNKpStart_Coll, ftCamera_UpdateCameraBox },
    { 379, 0x003C0019, 0x1A000000, ftKb_SpecialNKpLoop_Anim,
      ftKb_SpecialNKpLoop_IASA, ftKb_SpecialNKpLoop_Phys,
      ftKb_SpecialNKpLoop_Coll, ftCamera_UpdateCameraBox },
    { 380, 0x00340019, 0x1A000000, ftKb_SpecialNKpEnd_Anim,
      ftKb_SpecialNKpEnd_IASA, ftKb_SpecialNKpEnd_Phys,
      ftKb_SpecialNKpEnd_Coll, ftCamera_UpdateCameraBox },
    { 381, 0x00340419, 0x1A000000, ftKb_SpecialAirNKpStart_Anim,
      ftKb_SpecialAirNKpStart_IASA, ftKb_SpecialAirNKpStart_Phys,
      ftKb_SpecialAirNKpStart_Coll, ftCamera_UpdateCameraBox },
    { 382, 0x003C0419, 0x1A000000, ftKb_SpecialAirNKpLoop_Anim,
      ftKb_SpecialAirNKpLoop_IASA, ftKb_SpecialAirNKpLoop_Phys,
      ftKb_SpecialAirNKpLoop_Coll, ftCamera_UpdateCameraBox },
    { 383, 0x00340419, 0x1A000000, ftKb_SpecialAirNKpEnd_Anim,
      ftKb_SpecialAirNKpEnd_IASA, ftKb_SpecialAirNKpEnd_Phys,
      ftKb_SpecialAirNKpEnd_Coll, ftCamera_UpdateCameraBox },
    { 384, 0x0034001D, 0x1E000000, ftKb_SpecialNPe_Anim, ftKb_SpecialNPe_IASA,
      ftKb_SpecialNPe_Phys, ftKb_SpecialNPe_Coll, ftCamera_UpdateCameraBox },
    { 385, 0x0034001D, 0x1E000000, ftKb_SpecialNPeAttack_Anim,
      ftKb_SpecialNPeAttack_IASA, ftKb_SpecialNPeAttack_Phys,
      ftKb_SpecialNPeAttack_Coll, ftCamera_UpdateCameraBox },
    { 386, 0x0034041D, 0x1E000000, ftKb_SpecialAirNPe_Anim,
      ftKb_SpecialAirNPe_IASA, ftKb_SpecialAirNPe_Phys,
      ftKb_SpecialAirNPe_Coll, ftCamera_UpdateCameraBox },
    { 387, 0x0034041D, 0x1E000000, ftKb_SpecialAirNPeAttack_Anim,
      ftKb_SpecialAirNPeAttack_IASA, ftKb_SpecialAirNPeAttack_Phys,
      ftKb_SpecialAirNPeAttack_Coll, ftCamera_UpdateCameraBox },
    { 388, 0x0034011E, 0x1F000000, ftKb_SpecialNIc_Anim, ftKb_SpecialNIc_IASA,
      ftKb_SpecialNIc_Phys, ftKb_SpecialNIc_Coll, ftCamera_UpdateCameraBox },
    { 389, 0x0034051E, 0x1F000000, ftKb_SpecialAirNIc_Anim,
      ftKb_SpecialAirNIc_IASA, ftKb_SpecialAirNIc_Phys,
      ftKb_SpecialAirNIc_Coll, ftCamera_UpdateCameraBox },
    { 390, 0x00340218, 0x19000000, ftKb_SpecialNDkChargeStart_Anim,
      ftKb_SpecialNDkChargeStart_IASA, ftKb_SpecialNDkChargeStart_Phys,
      ftKb_SpecialNDkChargeStart_Coll, ftCamera_UpdateCameraBox },
    { 391, 0x00340218, 0x19000000, ftKb_SpecialNDkChargeLoop_Anim,
      ftKb_SpecialNDkChargeLoop_IASA, ftKb_SpecialNDkChargeLoop_Phys,
      ftKb_SpecialNDkChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 392, 0x00340218, 0x19000000, ftKb_SpecialNDkChargeStop_Anim,
      ftKb_SpecialNDkChargeStop_IASA, ftKb_SpecialNDkChargeStop_Phys,
      ftKb_SpecialNDkChargeStop_Coll, ftCamera_UpdateCameraBox },
    { 393, 0x00340218, 0x19000000, ftKb_SpecialNDkEarlyPunch_Anim,
      ftKb_SpecialNDkEarlyPunch_IASA, ftKb_SpecialNDkEarlyPunch_Phys,
      ftKb_SpecialNDkEarlyPunch_Coll, ftCamera_UpdateCameraBox },
    { 394, 0x00340218, 0x19000000, ftKb_SpecialNDkFullChargePunch_Anim,
      ftKb_SpecialNDkFullChargePunch_IASA, ftKb_SpecialNDkFullChargePunch_Phys,
      ftKb_SpecialNDkFullChargePunch_Coll, ftCamera_UpdateCameraBox },
    { 395, 0x00340618, 0x19000000, ftKb_SpecialAirNDkChargeStart_Anim,
      ftKb_SpecialAirNDkChargeStart_IASA, ftKb_SpecialAirNDkChargeStart_Phys,
      ftKb_SpecialAirNDkChargeStart_Coll, ftCamera_UpdateCameraBox },
    { 396, 0x00340618, 0x19000000, ftKb_SpecialAirNDkChargeLoop_Anim,
      ftKb_SpecialAirNDkChargeLoop_IASA, ftKb_SpecialAirNDkChargeLoop_Phys,
      ftKb_SpecialAirNDkChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 397, 0x00340618, 0x19000000, ftKb_SpecialAirNDkChargeStop_Anim,
      ftKb_SpecialAirNDkChargeStop_IASA, ftKb_SpecialAirNDkChargeStop_Phys,
      ftKb_SpecialAirNDkChargeStop_Coll, ftCamera_UpdateCameraBox },
    { 398, 0x00340618, 0x19000000, ftKb_SpecialAirNDkEarlyPunch_Anim,
      ftKb_SpecialAirNDkEarlyPunch_IASA, ftKb_SpecialAirNDkEarlyPunch_Phys,
      ftKb_SpecialAirNDkEarlyPunch_Coll, ftCamera_UpdateCameraBox },
    { 399, 0x00340618, 0x19000000, ftKb_SpecialAirNDkFullChargePunch_Anim,
      ftKb_SpecialAirNDkFullChargePunch_IASA,
      ftKb_SpecialAirNDkFullChargePunch_Phys,
      ftKb_SpecialAirNDkFullChargePunch_Coll, ftCamera_UpdateCameraBox },
    { 400, 0x00340026, 0x27000000, ftKb_SpecialNZd_Anim, ftKb_SpecialNZd_IASA,
      ftKb_SpecialNZd_Phys, ftKb_SpecialNZd_Coll, ftCamera_UpdateCameraBox },
    { 401, 0x00340426, 0x27000000, ftKb_SpecialAirNZd_Anim,
      ftKb_SpecialAirNZd_IASA, ftKb_SpecialAirNZd_Phys,
      ftKb_SpecialAirNZd_Coll, ftCamera_UpdateCameraBox },
    { 402, 0x0034011B, 0x1C000000, ftKb_SpecialNSkStartCharge_Anim,
      ftKb_SpecialNSkStartCharge_IASA, ftKb_SpecialNSkStartCharge_Phys,
      ftKb_SpecialNSkStartCharge_Coll, ftCamera_UpdateCameraBox },
    { 403, 0x003C011B, 0x1C000000, ftKb_SpecialNSkChargeLoop_Anim,
      ftKb_SpecialNSkChargeLoop_IASA, ftKb_SpecialNSkChargeLoop_Phys,
      ftKb_SpecialNSkChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 404, 0x0034011B, 0x1C000000, ftKb_SpecialNSkEndCharge_Anim,
      ftKb_SpecialNSkEndCharge_IASA, ftKb_SpecialNSkEndCharge_Phys,
      ftKb_SpecialNSkEndCharge_Coll, ftCamera_UpdateCameraBox },
    { 405, 0x0034011B, 0x1C000000, ftKb_SpecialNSkFire_Anim,
      ftKb_SpecialNSkFire_IASA, ftKb_SpecialNSkFire_Phys,
      ftKb_SpecialNSkFire_Coll, ftCamera_UpdateCameraBox },
    { 406, 0x0034051B, 0x1C000000, ftKb_SpecialAirNSkStartCharge_Anim,
      ftKb_SpecialAirNSkStartCharge_IASA, ftKb_SpecialAirNSkStartCharge_Phys,
      ftKb_SpecialAirNSkStartCharge_Coll, ftCamera_UpdateCameraBox },
    { 407, 0x003C051B, 0x1C000000, ftKb_SpecialAirNSkChargeLoop_Anim,
      ftKb_SpecialAirNSkChargeLoop_IASA, ftKb_SpecialAirNSkChargeLoop_Phys,
      ftKb_SpecialAirNSkChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 408, 0x0034051B, 0x1C000000, ftKb_SpecialAirNSkEndCharge_Anim,
      ftKb_SpecialAirNSkEndCharge_IASA, ftKb_SpecialAirNSkEndCharge_Phys,
      ftKb_SpecialAirNSkEndCharge_Coll, ftCamera_UpdateCameraBox },
    { 409, 0x0034051B, 0x1C000000, ftKb_SpecialAirNSkFire_Anim,
      ftKb_SpecialAirNSkFire_IASA, ftKb_SpecialAirNSkFire_Phys,
      ftKb_SpecialAirNSkFire_Coll, ftCamera_UpdateCameraBox },
    { 410, 0x00340222, 0x23000000, ftKb_SpecialNPrChargeStart_Anim,
      ftKb_SpecialNPrChargeStart_IASA, ftKb_SpecialNPrChargeStart_Phys,
      ftKb_SpecialNPrChargeStart_Coll, ftCamera_UpdateCameraBox },
    { 411, 0x00340222, 0x23000000, ftKb_SpecialNPrChargeStart_Anim,
      ftKb_SpecialNPrChargeStart_IASA, ftKb_SpecialNPrChargeStart_Phys,
      ftKb_SpecialNPrChargeStart_Coll, ftCamera_UpdateCameraBox },
    { 412, 0x003C0222, 0x23000000, ftKb_SpecialNPrChargeLoop_Anim,
      ftKb_SpecialNPrChargeLoop_IASA, ftKb_SpecialNPrChargeLoop_Phys,
      ftKb_SpecialNPrChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 413, 0x003C0222, 0x23000000, ftKb_SpecialNPrFullyCharged_Anim,
      ftKb_SpecialNPrFullyCharged_IASA, ftKb_SpecialNPrFullyCharged_Phys,
      ftKb_SpecialNPrFullyCharged_Coll, ftCamera_UpdateCameraBox },
    { 414, 0x00340222, 0x23000000, ftKb_SpecialNPrChargeRelease_Anim,
      ftKb_SpecialNPrChargeRelease_IASA, ftKb_SpecialNPrChargeRelease_Phys,
      ftKb_SpecialNPrChargeRelease_Coll, ftCamera_UpdateCameraBox },
    { 415, 0x00340222, 0x23000000, ftKb_SpecialNPrTurnStart_Anim,
      ftKb_SpecialNPrTurnStart_IASA, ftKb_SpecialNPrTurnStart_Phys,
      ftKb_SpecialNPrTurnStart_Coll, ftCamera_UpdateCameraBox },
    { 416, 0x00340222, 0x23000000, ftKb_SpecialNPrEnd_Anim,
      ftKb_SpecialNPrEnd_IASA, ftKb_SpecialNPrEnd_Phys,
      ftKb_SpecialNPrEnd_Coll, ftCamera_UpdateCameraBox },
    { 417, 0x00340222, 0x23000000, ftKb_SpecialNPrEnd_Anim,
      ftKb_SpecialNPrEnd_IASA, ftKb_SpecialNPrEnd_Phys,
      ftKb_SpecialNPrEnd_Coll, ftCamera_UpdateCameraBox },
    { 418, 0x00340622, 0x23000000, ftKb_SpecialAirNPrChargeStart_Anim,
      ftKb_SpecialAirNPrChargeStart_IASA, ftKb_SpecialAirNPrChargeStart_Phys,
      ftKb_SpecialAirNPrChargeStartL_Coll, ftCamera_UpdateCameraBox },
    { 419, 0x00340622, 0x23000000, ftKb_SpecialAirNPrChargeStart_Anim,
      ftKb_SpecialAirNPrChargeStart_IASA, ftKb_SpecialAirNPrChargeStart_Phys,
      ftKb_SpecialAirNPrChargeStartL_Coll, ftCamera_UpdateCameraBox },
    { 420, 0x003C0622, 0x23000000, ftKb_SpecialAirNPrChargeLoop_Anim,
      ftKb_SpecialAirNPrChargeLoop_IASA, ftKb_SpecialAirNPrChargeLoop_Phys,
      ftKb_SpecialAirNPrChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 421, 0x003C0622, 0x23000000, ftKb_SpecialAirNPrFullyCharged_Anim,
      ftKb_SpecialAirNPrFullyCharged_IASA, ftKb_SpecialAirNPrFullyCharged_Phys,
      ftKb_SpecialAirNPrFullyCharged_Coll, ftCamera_UpdateCameraBox },
    { 422, 0x00340622, 0x23000000, ftKb_SpecialAirNPrChargeRelease_Anim,
      ftKb_SpecialAirNPrChargeRelease_IASA,
      ftKb_SpecialAirNPrChargeRelease_Phys,
      ftKb_SpecialAirNPrChargeRelease_Coll, ftCamera_UpdateCameraBox },
    { 423, 0x00340222, 0x23000000, ftKb_MS_488_Anim, ftKb_MS_488_IASA,
      ftKb_MS_488_Phys, ftKb_MS_488_Coll, ftCamera_UpdateCameraBox },
    { 424, 0x00340622, 0x23000000, ftKb_SpecialAirNPrEnd_Anim,
      ftKb_SpecialAirNPrEnd_IASA, ftKb_SpecialAirNPrEnd_Phys,
      ftKb_SpecialAirNPrEndL_Coll, ftCamera_UpdateCameraBox },
    { 425, 0x00340622, 0x23000000, ftKb_SpecialAirNPrEnd_Anim,
      ftKb_SpecialAirNPrEnd_IASA, ftKb_SpecialAirNPrEnd_Phys,
      ftKb_SpecialAirNPrEndL_Coll, ftCamera_UpdateCameraBox },
    { 426, 0x00340622, 0x23000000, ftKb_SpecialNPrHit_Anim,
      ftKb_SpecialNPrHit_IASA, ftKb_SpecialNPrHit_Phys,
      ftKb_SpecialNPrHit_Coll, ftCamera_UpdateCameraBox },
    { 427, 0x00340225, 0x26000000, ftKb_SpecialNMsStartCharge_Anim,
      ftKb_SpecialNMsStartCharge_IASA, ftKb_SpecialNMsStartCharge_Phys,
      ftKb_SpecialNMsStartCharge_Coll, ftCamera_UpdateCameraBox },
    { 428, 0x00340225, 0x26000000, ftKb_SpecialNMsChargeLoop_Anim,
      ftKb_SpecialNMsChargeLoop_IASA, ftKb_SpecialNMsChargeLoop_Phys,
      ftKb_SpecialNMsChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 429, 0x00340225, 0x26000000, ftKb_SpecialNMs_Anim, ftKb_SpecialNMs_IASA,
      ftKb_SpecialNMs_Phys, ftKb_SpecialNMs_Coll, ftCamera_UpdateCameraBox },
    { 430, 0x00340225, 0x26000000, ftKb_SpecialNMs_Anim, ftKb_SpecialNMs_IASA,
      ftKb_SpecialNMs_Phys, ftKb_SpecialNMs_Coll, ftCamera_UpdateCameraBox },
    { 431, 0x00340625, 0x26000000, ftKb_SpecialAirNMsStartCharge_Anim,
      ftKb_SpecialAirNMsStartCharge_IASA, ftKb_SpecialAirNMsStartCharge_Phys,
      ftKb_SpecialAirNMsStartCharge_Coll, ftCamera_UpdateCameraBox },
    { 432, 0x00340625, 0x26000000, ftKb_SpecialAirNMsChargeLoop_Anim,
      ftKb_SpecialAirNMsChargeLoop_IASA, ftKb_SpecialAirNMsChargeLoop_Phys,
      ftKb_SpecialAirNMsChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 433, 0x00340625, 0x26000000, ftKb_SpecialAirNFeMs_Anim,
      ftKb_SpecialAirNMs_IASA, ftKb_SpecialAirNMs_Phys,
      ftKb_SpecialAirNMs_Coll, ftCamera_UpdateCameraBox },
    { 434, 0x00340625, 0x26000000, ftKb_SpecialAirNFeMs_Anim,
      ftKb_SpecialAirNMs_IASA, ftKb_SpecialAirNMs_Phys,
      ftKb_SpecialAirNMs_Coll, ftCamera_UpdateCameraBox },
    { 435, 0x00340123, 0x24000000, ftKb_SpecialNMtStartCharge_Anim,
      ftKb_SpecialNMtStartCharge_IASA, ftKb_SpecialNMtStartCharge_Phys,
      ftKb_SpecialNMtStartCharge_Coll, ftCamera_UpdateCameraBox },
    { 436, 0x003C0123, 0x24000000, ftKb_SpecialNMtChargeLoop_Anim,
      ftKb_SpecialNMtChargeLoop_IASA, ftKb_SpecialNMtChargeLoop_Phys,
      ftKb_SpecialNMtChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 437, 0x003C0123, 0x24000000, ftKb_SpecialNMtFullyCharged_Anim,
      ftKb_SpecialNMtFullyCharged_IASA, ftKb_SpecialNMtFullyCharged_Phys,
      ftKb_SpecialNMtFullyCharged_Coll, ftCamera_UpdateCameraBox },
    { 438, 0x00340123, 0x24000000, ftKb_SpecialNMtEndCharge_Anim,
      ftKb_SpecialNMtEndCharge_IASA, ftKb_SpecialNMtEndCharge_Phys,
      ftKb_SpecialNMtEndCharge_Coll, ftCamera_UpdateCameraBox },
    { 439, 0x00340123, 0x24000000, ftKb_SpecialNMtFire_Anim,
      ftKb_SpecialNMtFire_IASA, ftKb_SpecialNMtFire_Phys,
      ftKb_SpecialNMtFire_Coll, ftCamera_UpdateCameraBox },
    { 440, 0x00340523, 0x24000000, ftKb_SpecialAirNMtStartCharge_Anim,
      ftKb_SpecialAirNMtStartCharge_IASA, ftKb_SpecialAirNMtStartCharge_Phys,
      ftKb_SpecialAirNMtStartCharge_Coll, ftCamera_UpdateCameraBox },
    { 441, 0x003C0523, 0x24000000, ftKb_SpecialAirNMtChargeLoop_Anim,
      ftKb_SpecialAirNMtChargeLoop_IASA, ftKb_SpecialAirNMtChargeLoop_Phys,
      ftKb_SpecialAirNMtChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 442, 0x003C0523, 0x24000000, ftKb_SpecialAirNMtFullyCharged_Anim,
      ftKb_SpecialAirNMtFullyCharged_IASA, ftKb_SpecialAirNMtFullyCharged_Phys,
      ftKb_SpecialAirNMtFullyCharged_Coll, ftCamera_UpdateCameraBox },
    { 443, 0x00340523, 0x24000000, ftKb_SpecialAirNMtEndCharge_Anim,
      ftKb_SpecialAirNMtEndCharge_IASA, ftKb_SpecialAirNMtEndCharge_Phys,
      ftKb_SpecialAirNMtEndCharge_Coll, ftCamera_UpdateCameraBox },
    { 444, 0x00340523, 0x24000000, ftKb_SpecialAirNMtFire_Anim,
      ftKb_SpecialAirNMtFire_IASA, ftKb_SpecialAirNMtFire_Phys,
      ftKb_SpecialAirNMtFire_Coll, ftCamera_UpdateCameraBox },
    { 445, 0x0034012B, 0x2C000000, ftKb_SpecialNGw_Anim, ftKb_SpecialNGw_IASA,
      ftKb_SpecialNGw_Phys, ftKb_SpecialNGw_Coll, ftCamera_UpdateCameraBox },
    { 446, 0x0034052B, 0x2C000000, ftKb_SpecialAirNGw_Anim,
      ftKb_SpecialAirNGw_IASA, ftKb_SpecialAirNGw_Phys,
      ftKb_SpecialAirNGw_Coll, ftCamera_UpdateCameraBox },
    { 447, 0x00340028, 0x29000000, ftKb_SpecialNMr_Anim, ftKb_SpecialNMr_IASA,
      ftKb_SpecialNMr_Phys, ftKb_SpecialNMr_Coll, ftCamera_UpdateCameraBox },
    { 448, 0x00340428, 0x29000000, ftKb_SpecialAirNMr_Anim,
      ftKb_SpecialAirNMr_IASA, ftKb_SpecialAirNMr_Phys,
      ftKb_SpecialAirNMr_Coll, ftCamera_UpdateCameraBox },
    { 449, 0x00340127, 0x28000000, ftKb_SpecialNLkCharge_Anim,
      ftKb_SpecialNLkCharge_IASA, ftKb_SpecialNLkCharge_Phys,
      ftKb_SpecialNLkCharge_Coll, ftCamera_UpdateCameraBox },
    { 450, 0x003C0127, 0x28000000, ftKb_SpecialNLkFullyCharged_Anim,
      ftKb_SpecialNLkFullyCharged_IASA, ftKb_SpecialNLkFullyCharged_Phys,
      ftKb_SpecialNLkFullyCharged_Coll, ftCamera_UpdateCameraBox },
    { 451, 0x00340127, 0x28000000, ftKb_SpecialNLkFire_Anim,
      ftKb_SpecialNLkFire_IASA, ftKb_SpecialNLkFire_Phys,
      ftKb_SpecialNLkFire_Coll, ftCamera_UpdateCameraBox },
    { 452, 0x00340527, 0x28000000, ftKb_SpecialAirNLkCharge_Anim,
      ftKb_SpecialAirNLkCharge_IASA, ftKb_SpecialAirNLkCharge_Phys,
      ftKb_SpecialAirNLkCharge_Coll, ftCamera_UpdateCameraBox },
    { 453, 0x003C0527, 0x28000000, ftKb_SpecialAirNLkFullyCharged_Anim,
      ftKb_SpecialAirNLkFullyCharged_IASA, ftKb_SpecialAirNLkFullyCharged_Phys,
      ftKb_SpecialAirNLkFullyCharged_Coll, ftCamera_UpdateCameraBox },
    { 454, 0x00340527, 0x28000000, ftKb_SpecialAirNLkFire_Anim,
      ftKb_SpecialAirNLkFire_IASA, ftKb_SpecialAirNLkFire_Phys,
      ftKb_SpecialAirNLkFire_Coll, ftCamera_UpdateCameraBox },
    { 455, 0x00340129, 0x2A000000, ftKb_SpecialNFxStart_Anim,
      ftKb_SpecialNFxStart_IASA, ftKb_SpecialNFxStart_Phys,
      ftKb_SpecialNFxStart_Coll, ftCamera_UpdateCameraBox },
    { 456, 0x003C0129, 0x2A000000, ftKb_SpecialNFxLoop_Anim,
      ftKb_SpecialNFxLoop_IASA, ftKb_SpecialNFxLoop_Phys,
      ftKb_SpecialNFxLoop_Coll, ftCamera_UpdateCameraBox },
    { 457, 0x00340129, 0x2A000000, ftKb_SpecialNFxEnd_Anim,
      ftKb_SpecialNFxEnd_IASA, ftKb_SpecialNFxEnd_Phys,
      ftKb_SpecialNFxEnd_Coll, ftCamera_UpdateCameraBox },
    { 458, 0x00340529, 0x2A000000, ftKb_SpecialAirNFxStart_Anim,
      ftKb_SpecialAirNFxStart_IASA, ftKb_SpecialAirNFxStart_Phys,
      ftKb_SpecialAirNFxStart_Coll, ftCamera_UpdateCameraBox },
    { 459, 0x003C0529, 0x2A000000, ftKb_SpecialAirNFxLoop_Anim,
      ftKb_SpecialAirNFxLoop_IASA, ftKb_SpecialAirNFxLoop_Phys,
      ftKb_SpecialAirNFxLoop_Coll, ftCamera_UpdateCameraBox },
    { 460, 0x00340529, 0x2A000000, ftKb_SpecialAirNFxEnd_Anim,
      ftKb_SpecialAirNFxEnd_IASA, ftKb_SpecialAirNFxEnd_Phys,
      ftKb_SpecialAirNFxEnd_Coll, ftCamera_UpdateCameraBox },
    { 461, 0x0034012A, 0x2B000000, ftKb_SpecialNPk_Anim, ftKb_SpecialNPk_IASA,
      ftKb_SpecialNPk_Phys, ftKb_SpecialNPk_Coll, ftCamera_UpdateCameraBox },
    { 462, 0x0034052A, 0x2B000000, ftKb_SpecialAirNPk_Anim,
      ftKb_SpecialAirNPk_IASA, ftKb_SpecialAirNPk_Phys,
      ftKb_SpecialAirNPk_Coll, ftCamera_UpdateCameraBox },
    { 463, 0x0034022C, 0x2D000000, ftKb_SpecialNCa_Anim, ftKb_SpecialNCa_IASA,
      ftKb_SpecialNCa_Phys, ftKb_SpecialNCa_Coll, ftCamera_UpdateCameraBox },
    { 464, 0x0034062C, 0x2D000000, ftKb_SpecialAirNCa_Anim,
      ftKb_SpecialAirNCa_IASA, ftKb_SpecialAirNCa_Phys,
      ftKb_SpecialAirNCa_Coll, ftCamera_UpdateCameraBox },
    { 465, 0x0034022D, 0x2E000000, ftKb_SpecialNMsStartCharge_Anim,
      ftKb_SpecialNMsStartCharge_IASA, ftKb_SpecialNMsStartCharge_Phys,
      ftKb_SpecialNMsStartCharge_Coll, ftCamera_UpdateCameraBox },
    { 466, 0x0034022D, 0x2E000000, ftKb_SpecialNMsChargeLoop_Anim,
      ftKb_SpecialNMsChargeLoop_IASA, ftKb_SpecialNMsChargeLoop_Phys,
      ftKb_SpecialNMsChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 467, 0x0034022D, 0x2E000000, ftKb_SpecialNMs_Anim, ftKb_SpecialNMs_IASA,
      ftKb_SpecialNMs_Phys, ftKb_SpecialNMs_Coll, ftCamera_UpdateCameraBox },
    { 468, 0x0034022D, 0x2E000000, ftKb_SpecialNMs_Anim, ftKb_SpecialNMs_IASA,
      ftKb_SpecialNMs_Phys, ftKb_SpecialNMs_Coll, ftCamera_UpdateCameraBox },
    { 469, 0x0034062D, 0x2E000000, ftKb_SpecialAirNMsStartCharge_Anim,
      ftKb_SpecialAirNMsStartCharge_IASA, ftKb_SpecialAirNMsStartCharge_Phys,
      ftKb_SpecialAirNMsStartCharge_Coll, ftCamera_UpdateCameraBox },
    { 470, 0x0034062D, 0x2E000000, ftKb_SpecialAirNMsChargeLoop_Anim,
      ftKb_SpecialAirNMsChargeLoop_IASA, ftKb_SpecialAirNMsChargeLoop_Phys,
      ftKb_SpecialAirNMsChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 471, 0x0034062D, 0x2E000000, ftKb_SpecialAirNFeMs_Anim,
      ftKb_SpecialAirNMs_IASA, ftKb_SpecialAirNMs_Phys,
      ftKb_SpecialAirNMs_Coll, ftCamera_UpdateCameraBox },
    { 472, 0x0034062D, 0x2E000000, ftKb_SpecialAirNFeMs_Anim,
      ftKb_SpecialAirNMs_IASA, ftKb_SpecialAirNMs_Phys,
      ftKb_SpecialAirNMs_Coll, ftCamera_UpdateCameraBox },
    { 473, 0x0034002E, 0x2F000000, ftKb_SpecialNKpStart_Anim,
      ftKb_SpecialNKpStart_IASA, ftKb_SpecialNKpStart_Phys,
      ftKb_SpecialNKpStart_Coll, ftCamera_UpdateCameraBox },
    { 474, 0x003C002E, 0x2F000000, ftKb_SpecialNKpLoop_Anim,
      ftKb_SpecialNKpLoop_IASA, ftKb_SpecialNKpLoop_Phys,
      ftKb_SpecialNKpLoop_Coll, ftCamera_UpdateCameraBox },
    { 475, 0x0034002E, 0x2F000000, ftKb_SpecialNKpEnd_Anim,
      ftKb_SpecialNKpEnd_IASA, ftKb_SpecialNKpEnd_Phys,
      ftKb_SpecialNKpEnd_Coll, ftCamera_UpdateCameraBox },
    { 476, 0x0034042E, 0x2F000000, ftKb_SpecialAirNKpStart_Anim,
      ftKb_SpecialAirNKpStart_IASA, ftKb_SpecialAirNKpStart_Phys,
      ftKb_SpecialAirNKpStart_Coll, ftCamera_UpdateCameraBox },
    { 477, 0x003C042E, 0x2F000000, ftKb_SpecialAirNKpLoop_Anim,
      ftKb_SpecialAirNKpLoop_IASA, ftKb_SpecialAirNKpLoop_Phys,
      ftKb_SpecialAirNKpLoop_Coll, ftCamera_UpdateCameraBox },
    { 478, 0x0034042E, 0x2F000000, ftKb_SpecialAirNKpEnd_Anim,
      ftKb_SpecialAirNKpEnd_IASA, ftKb_SpecialAirNKpEnd_Phys,
      ftKb_SpecialAirNKpEnd_Coll, ftCamera_UpdateCameraBox },
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

typedef unk_t ftKirby_UnkArrayThing[12];

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
    { 14, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 15, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 16, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 17, 0, 0x01000000, NULL, NULL, ft_800C7414, NULL, NULL },
};

/* static */ void ftKb_Init_800EE854(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE8EC(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE874(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE904(void);
/* static */ void ftKb_Init_800EE8B0(void);

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
/* static */ void ftKb_SpecialN_800F1764(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F186C(void);
/* static */ void ftKb_SpecialN_800F17A4(void);
/* static */ void ftKb_SpecialN_800F1894(void);
/* static */ void ftKb_SpecialN_800F17F8(void);
/* static */ void ftKb_SpecialN_800F1744(void);
/* static */ void ftKb_SpecialN_800F1730(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F1818(void);
/* static */ void ftKb_SpecialN_800F1858(void);
/* static */ void ftKb_SpecialN_800F18E8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F17E4(void);
/* static */ void ftKb_SpecialN_800F171C(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F17C4(void);
/* static */ void ftKb_SpecialN_800F18B4(void);
/* static */ void ftKb_SpecialN_800F1784(void);
/* static */ void ftKb_SpecialN_800F1838(void);
/* static */ void ftKb_SpecialN_800F18C8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F18F8(void);
/* static */ void ftKb_SpecialN_800F1880(void);

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

/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A00(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A64(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A0C(void);
/* static */ void ftKb_SpecialN_800F1A44(void);
/* static */ void ftKb_SpecialN_800F1A2C(void);
/* static */ void ftKb_SpecialN_800F19F4(void);
/* static */ void ftKb_SpecialN_800F19E8(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A38(void);
/* static */ void ftKb_SpecialN_800F1A50(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A20(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A0C(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A00(void);
/* static */ void ftKb_SpecialN_800F1A78(void);
/* static */ void ftKb_SpecialN_800F1A70(void);

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

/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1AE0(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1B44(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1AEC(void);
/* static */ void ftKb_SpecialN_800F1B24(void);
/* static */ void ftKb_SpecialN_800F1B0C(void);
/* static */ void ftKb_SpecialN_800F1AD4(void);
/* static */ void ftKb_SpecialN_800F1AC8(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1B18(void);
/* static */ void ftKb_SpecialN_800F1B30(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1B00(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1AEC(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1AE0(void);
/* static */ void ftKb_SpecialN_800F1B58(void);
/* static */ void ftKb_SpecialN_800F1B50(void);

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

/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CC8(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CC8(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CC8(void);
/* static */ void ftKb_SpecialN_800F1CC8(void);
/* static */ void ftKb_SpecialN_800F1CD0(void);
/* static */ void ftKb_SpecialN_800F1CC8(void);

jtbl_t ftKb_Init_803CA294 = {
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CC8,
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CD0,
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CC8, ftKb_SpecialN_800F1CD0,
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CC8, ftKb_SpecialN_800F1CC8,
    ftKb_SpecialN_800F1CD0, ftKb_SpecialN_800F1CC8,
};

/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D00(void);
/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D00(void);
/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D00(void);
/* static */ void ftKb_SpecialN_800F1D00(void);
/* static */ void ftKb_SpecialN_800F1D08(void);
/* static */ void ftKb_SpecialN_800F1D00(void);

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

struct lbl_803CB4EC_t {
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

uint ftKb_Init_803CB6C0[] = { 260006, 260009, 260012, 260015, 260018, 0 };

char ftKb_Init_803CB6D8[] = "ftToSpecialNFox::Caution!!!\n";
char ftKb_Init_803CB6F8[] = "ftkirbyspecialfox.c\0\0\0\0";

Vec4 ftKb_Init_803CB710 = { 0.65F, 0.7F, 0.8F, 1.0F };
Vec4 ftKb_Init_803CB720 = { 1.1F, 1.35F, 1.3F, 1.2F };

char ftKb_Init_assert_msg_3[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 ftKb_Init_803CB758[] = {
    { +8, +0, -4 },
    { +4, +4, +4 },
};

f32 ftKb_Init_803CB770[] = {
    -1, -0.75, -0.5, -0.25, 0, +0.25, +0.5, +0.75, +1,
};
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106464(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106464(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106464(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106464(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106464(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106474(void);
/* static */ void ftKb_SpecialNSk_80106464(void);

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
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066B4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066B4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066B4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066B4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066B4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066C4(void);
/* static */ void ftKb_SpecialNSk_801066B4(void);

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

uint ftKb_Init_803CB828[] = { 0x00030DB9, 0x00030DBC, 0x00030DBF, 0x00030DC2 };

f32 const ftKb_Init_803B7548[10] = { 0 };
Vec3 const ftKb_Init_803B7570 = { 0, 4, 0 };
Vec3 const ftKb_Init_803B757C = { 0, 4, 0 };

#ifdef MWERKS_GEKKO
#pragma push
asm void ftKb_Init_800EE528(void)
{ // clang-format off
    nofralloc
/* 800EE528 00000000  38 00 00 21 */	li r0, 0x21
/* 800EE52C 00000004  3C 80 80 46 */	lis r4, ft_80459B88@ha
/* 800EE530 00000008  7C 09 03 A6 */	mtctr r0
/* 800EE534 0000000C  3C 60 80 3D */	lis r3, ftKb_Init_803C9FC8@ha
/* 800EE538 00000010  38 84 9B 88 */	addi r4, r4, ft_80459B88@l
/* 800EE53C 00000014  38 A3 9F C8 */	addi r5, r3, ftKb_Init_803C9FC8@l
lbl_800EE540:
/* 800EE540 00000018  38 00 00 00 */	li r0, 0x0
/* 800EE544 0000001C  90 04 00 00 */	stw r0, 0x0(r4)
/* 800EE548 00000020  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE54C 00000024  28 03 00 00 */	cmplwi r3, 0x0
/* 800EE550 00000028  41 82 00 60 */	beq lbl_800EE5B0
/* 800EE554 0000002C  90 03 00 00 */	stw r0, 0x0(r3)
/* 800EE558 00000030  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE55C 00000034  90 03 00 04 */	stw r0, 0x4(r3)
/* 800EE560 00000038  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE564 0000003C  90 03 00 08 */	stw r0, 0x8(r3)
/* 800EE568 00000040  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE56C 00000044  90 03 00 0C */	stw r0, 0xc(r3)
/* 800EE570 00000048  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE574 0000004C  90 03 00 10 */	stw r0, 0x10(r3)
/* 800EE578 00000050  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE57C 00000054  90 03 00 14 */	stw r0, 0x14(r3)
/* 800EE580 00000058  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE584 0000005C  90 03 00 18 */	stw r0, 0x18(r3)
/* 800EE588 00000060  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE58C 00000064  90 03 00 1C */	stw r0, 0x1c(r3)
/* 800EE590 00000068  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE594 0000006C  90 03 00 20 */	stw r0, 0x20(r3)
/* 800EE598 00000070  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE59C 00000074  90 03 00 24 */	stw r0, 0x24(r3)
/* 800EE5A0 00000078  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE5A4 0000007C  90 03 00 28 */	stw r0, 0x28(r3)
/* 800EE5A8 00000080  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE5AC 00000084  90 03 00 2C */	stw r0, 0x2c(r3)
lbl_800EE5B0:
/* 800EE5B0 00000088  38 84 00 04 */	addi r4, r4, 0x4
/* 800EE5B4 0000008C  38 A5 00 04 */	addi r5, r5, 0x4
/* 800EE5B8 00000090  42 00 FF 88 */	bdnz lbl_800EE540
/* 800EE5BC 00000094  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#elif false

// https://decomp.me/scratch/6dL9q
void ftKb_Init_800EE528(void)
{
    s32* number_list = ft_80459B88;
    ftKirby_UnkArrayThing** struct_list = ftKb_Init_803C9FC8;

    s32 i;
    for (i = 0; i < FTKIND_MAX; i++) {
        struct S_KIRBY1* unk_struct;
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

#endif

void ftKb_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    fp->fv.kb.x222C = 0;
    fp->fv.kb.x2230 = (s32) (HSD_Randi(5) + 1);
    fp->fv.kb.x223C = 0;
    fp->fv.kb.x2238 = 4;
    fp->fv.kb.x2244 = 0;
    fp->fv.kb.x228C = 0;
    fp->fv.kb.x2290 = 0;
    if (Player_GetFlagsBit1(fp->xC_playerID) &&
        Player_GetUnk4D(fp->xC_playerID) != 4)
    {
        ftKb_SpecialN_800F1BAC(gobj, Player_GetUnk4D(fp->xC_playerID), 0);
    }
}

void ftKb_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftKirbyAttributes);

    fp->x2222_flag.bits.b1 = 1;
    fp->x2D0 = fp->x2D4_specialAttributes;
    fp->fv.kb.x2234.bits.b0 = Player_GetFlagsAEBit1(fp->xC_playerID);
    it_8026B3F8(item_list[0], 0x32);
    it_8026B3F8(item_list[1], 0x33);
    it_8026B3F8(item_list[2], 0x34);
    it_8026B3F8(item_list[3], 0x35);
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
    fp->cb.x21E8_callback_OnDeath3 = NULL;
}

void ftKb_Init_800EE7B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialAirLw_800F5524(gobj);
    ftKb_AttackDashAir_800F22D4(gobj);
    ftKb_SpecialAirLw_800F5318(gobj);
    ftKb_SpecialN_800F9090(gobj);
    ftKb_SpecialN_800F1A8C(gobj);
    fp->cb.x21E0_callback_OnDeath = NULL;
}

/// @file
/// @todo Matching, but needs more data moved over for DOL match

#if false

void ftKb_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    s32 _[2];
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirbyAttributes* attr = fp->x2D4_specialAttributes;
    switch (fp->fv.kb.x2238) {
    case 3:
        if (fp->fv.kb.x22E8 == attr->x190) {
            ft_800BFFD0(fp, 0x3A, 0);
        }
        break;
    case 13:
        if (fp->fv.kb.x22D4 == attr->x168) {
            ft_800BFFD0(fp, 0x36, 0);
        }
        break;
    case 16:
        if (fp->fv.kb.x22C8 == attr->x384) {
            ft_800BFFD0(fp, 0x5D, 0);
            return;
        }
        break;
    case 7:
        if (fp->fv.kb.x22E0 == 6) {
            ft_800BFFD0(fp, 0x57, 0);
        }
        break;
    }
}

void ftKb_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
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
    COPY_ATTRS(gobj, ftKirbyAttributes);
}

void ftKb_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftKb_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

#endif
