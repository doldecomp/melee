/// @file
/// Side Special - Green Missile (SpecialS)
#ifndef GALE01_142A24
#define GALE01_142A24

#include <baselib/forward.h>

/* 142A24 */ void ftLg_SpecialS_SetGFX(HSD_GObj* gobj);
/* 142A5C */ void ftLg_SpecialS_SetVars(HSD_GObj* gobj);
/* 142B14 */ void ftLg_SpecialS_Enter(HSD_GObj* gobj);
/* 142B88 */ void ftLg_SpecialAirS_Enter(HSD_GObj* gobj);
/* 142C00 */ void ftLg_SpecialS_OnGiveDamage(HSD_GObj* gobj);
/* 142C40 */ void ftLg_SpecialSStart_Anim(HSD_GObj* gobj);
/* 142C7C */ void ftLg_SpecialAirSStart_Anim(HSD_GObj* gobj);
/* 142CB8 */ void ftLg_SpecialSStart_IASA(HSD_GObj* gobj);
/* 142CBC */ void ftLg_SpecialAirSStart_IASA(HSD_GObj* gobj);
/* 142CC0 */ void ftLg_SpecialSStart_Phys(HSD_GObj* gobj);
/* 142D00 */ void ftLg_SpecialAirSStart_Phys(HSD_GObj* gobj);
/* 142D60 */ void ftLg_SpecialSStart_Coll(HSD_GObj* gobj);
/* 142D9C */ void ftLg_SpecialAirSStart_Coll(HSD_GObj* gobj);
/* 142DD8 */ void ftLg_SpecialSStart_GroundToAir(HSD_GObj* gobj);
/* 142E38 */ void ftLg_SpecialAirSStart_AirToGround(HSD_GObj* gobj);
/* 142E98 */ void ftLg_SpecialSHold_Anim(HSD_GObj* gobj);
/* 142F38 */ void ftLg_SpecialAirSHold_Anim(HSD_GObj* gobj);
/* 142FD8 */ void ftLg_SpecialSHold_IASA(HSD_GObj* gobj);
/* 143008 */ void ftLg_SpecialAirSHold_IASA(HSD_GObj* gobj);
/* 143038 */ void ftLg_SpecialSHold_Phys(HSD_GObj* gobj);
/* 143058 */ void ftLg_SpecialAirSHold_Phys(HSD_GObj* gobj);
/* 143078 */ void ftLg_SpecialSHold_Coll(HSD_GObj* gobj);
/* 1430B4 */ void ftLg_SpecialAirSHold_Coll(HSD_GObj* gobj);
/* 1430F0 */ void ftLg_SpecialSHold_GroundToAir(HSD_GObj* gobj);
/* 143150 */ void ftLg_SpecialAirSHold_AirToGround(HSD_GObj* gobj);
/* 1431B0 */ void ftLg_SpecialSHold_Enter(HSD_GObj* gobj);
/* 143204 */ void ftLg_SpecialAirSHold_Enter(HSD_GObj* gobj);
/* 143258 */ void ftLg_SpecialSLaunch_Anim(HSD_GObj* gobj);
/* 143304 */ void ftLg_SpecialAirSLaunch_Anim(HSD_GObj* gobj);
/* 1433A8 */ void ftLg_SpecialSLaunch_IASA(HSD_GObj* gobj);
/* 1433AC */ void ftLg_SpecialAirSLaunch_IASA(HSD_GObj* gobj);
/* 1433B0 */ void ftLg_SpecialSLaunch_Phys(HSD_GObj* gobj);
/* 1433D0 */ void ftLg_SpecialAirSLaunch_Phys(HSD_GObj* gobj);
/* 1433F0 */ void ftLg_SpecialSLaunch_Coll(HSD_GObj* gobj);
/* 14342C */ void ftLg_SpecialAirSLaunch_Coll(HSD_GObj* gobj);
/* 143468 */ void ftLg_SpecialSLaunch_GroundToAir(HSD_GObj* gobj);
/* 1434C8 */ void ftLg_SpecialAirSLaunch_AirToGround(HSD_GObj* gobj);
/* 143528 */ void ftLg_SpecialSLaunch_Enter(HSD_GObj* gobj);
/* 143600 */ void ftLg_SpecialAirSLaunch_Enter(HSD_GObj* gobj);
/* 1436D8 */ void ftLg_SpecialSMisfire_Anim(HSD_GObj* gobj);
/* 143784 */ void ftLg_SpecialAirSMisfire_Anim(HSD_GObj* gobj);
/* 143828 */ void ftLg_SpecialSMisfire_IASA(HSD_GObj* gobj);
/* 14382C */ void ftLg_SpecialAirSMisfire_IASA(HSD_GObj* gobj);
/* 143830 */ void ftLg_SpecialSMisfire_Phys(HSD_GObj* gobj);
/* 143850 */ void ftLg_SpecialAirSMisfire_Phys(HSD_GObj* gobj);
/* 143870 */ void ftLg_SpecialSMisfire_Coll(HSD_GObj* gobj);
/* 1438AC */ void ftLg_SpecialAirSMisfire_Coll(HSD_GObj* gobj);
/* 1438E8 */ void ftLg_SpecialSMisfire_GroundToAir(HSD_GObj* gobj);
/* 143948 */ void ftLg_SpecialAirSMisfire_AirToGround(HSD_GObj* gobj);
/* 1439A8 */ void ftLg_SpecialSMisfire_Enter(HSD_GObj* gobj);
/* 143A60 */ void ftLg_SpecialAirSMisfire_Enter(HSD_GObj* gobj);
/* 143B18 */ void ftLg_SpecialSFly_Anim(HSD_GObj* gobj);
/* 143B1C */ void ftLg_SpecialAirSFly_Anim(HSD_GObj* gobj);
/* 143B58 */ void ftLg_SpecialSFly_IASA(HSD_GObj* gobj);
/* 143B5C */ void ftLg_SpecialAirSFly_IASA(HSD_GObj* gobj);
/* 143B60 */ void ftLg_SpecialSFly_Phys(HSD_GObj* gobj);
/* 143B64 */ void ftLg_SpecialAirSFly_Phys(HSD_GObj* gobj);
/* 143BE0 */ void ftLg_SpecialSFly_Coll(HSD_GObj* gobj);
/* 143BE4 */ void ftLg_SpecialAirSFly_Coll(HSD_GObj* gobj);
/* 143C60 */ void ftLg_SpecialSFly_Enter(HSD_GObj* gobj);
/* 143D7C */ void ftLg_SpecialSEnd_Anim(HSD_GObj* gobj);
/* 143DB8 */ void ftLg_SpecialAirSEnd_Anim(HSD_GObj* gobj);
/* 143DF4 */ void ftLg_SpecialSEnd_IASA(HSD_GObj* gobj);
/* 143DF8 */ void ftLg_SpecialAirSEnd_IASA(HSD_GObj* gobj);
/* 143DFC */ void ftLg_SpecialSEnd_Phys(HSD_GObj* gobj);
/* 143E3C */ void ftLg_SpecialAirSEnd_Phys(HSD_GObj* gobj);
/* 143E8C */ void ftLg_SpecialSEnd_Coll(HSD_GObj* gobj);
/* 143EC8 */ void ftLg_SpecialAirSEnd_Coll(HSD_GObj* gobj);
/* 143F18 */ void ftLg_SpecialSEnd_Enter(HSD_GObj* gobj);
/* 143F70 */ void ftLg_SpecialAirSEnd_Enter(HSD_GObj* gobj);

#endif
