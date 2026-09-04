#ifndef GALE01_0E9DF8
#define GALE01_0E9DF8

#include <platform.h>

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 0E9DF8 */ void ftFx_SpecialS_CreateGFX(HSD_GObj* gobj);
/* 0E9E78 */ bool ftFx_SpecialS_CheckGhostRemove(HSD_GObj* gobj);
/* 0E9EA0 */ s32 ftFx_SpecialS_GetCmdVar2(HSD_GObj* gobj);
/* 0E9EAC */ void ftFx_SpecialS_CopyGhostPosIndexed(HSD_GObj* gobj, s32 index,
                                                    Vec3* ghostPos);
/* 0E9ED4 */ float ftFx_SpecialS_ReturnFloatVarIndexed(HSD_GObj* gobj,
                                                       s32 index);
/* 0E9EE8 */ void ftFx_SpecialSStart_Enter(HSD_GObj* gobj);
/* 0E9F6C */ void ftFx_SpecialAirSStart_Enter(HSD_GObj* gobj);
/* 0EA004 */ void ftFx_SpecialSStart_Anim(HSD_GObj* gobj);
/* 0EA040 */ void ftFx_SpecialAirSStart_Anim(HSD_GObj* gobj);
/* 0EA07C */ void ftFx_SpecialSStart_IASA(HSD_GObj* gobj);
/* 0EA080 */ void ftFx_SpecialAirSStart_IASA(HSD_GObj* gobj);
/* 0EA084 */ void ftFx_SpecialSStart_Phys(HSD_GObj* gobj);
/* 0EA0BC */ void ftFx_SpecialAirSStart_Phys(HSD_GObj* gobj);
/* 0EA128 */ void ftFx_SpecialSStart_Coll(HSD_GObj* gobj);
/* 0EA164 */ void ftFx_SpecialAirSStart_Coll(HSD_GObj* gobj);
/* 0EA1D4 */ void ftFx_SpecialSStart_GroundToAir(HSD_GObj* gobj);
/* 0EA234 */ void ftFx_SpecialAirSStart_AirToGround(HSD_GObj* gobj);
/* 0EA294 */ void ftFx_SpecialS_Anim(HSD_GObj* gobj);
/* 0EA344 */ void ftFx_SpecialAirS_Anim(HSD_GObj* gobj);
/* 0EA3F4 */ void ftFx_SpecialS_IASA(HSD_GObj* gobj);
/* 0EA438 */ void ftFx_SpecialAirS_IASA(HSD_GObj* gobj);
/* 0EA47C */ void ftFx_SpecialS_Phys(HSD_GObj* gobj);
/* 0EA534 */ void ftFx_SpecialAirS_Phys(HSD_GObj* gobj);
/* 0EA5EC */ void ftFx_SpecialS_Coll(HSD_GObj* gobj);
/* 0EA628 */ void ftFx_SpecialAirS_Coll(HSD_GObj* gobj);
/* 0EA698 */ void ftFx_SpecialS_GroundToAir(HSD_GObj* gobj);
/* 0EA700 */ void ftFx_SpecialAirS_AirToGround(HSD_GObj* gobj);
/* 0EA768 */ void ftFx_SpecialS_Enter(HSD_GObj* gobj);
/* 0EA838 */ void ftFx_SpecialAirS_Enter(HSD_GObj* gobj);
/* 0EA908 */ void ftFx_SpecialSEnd_Anim(HSD_GObj* gobj);
/* 0EA944 */ void ftFx_SpecialAirSEnd_Anim(HSD_GObj* gobj);
/* 0EA9A4 */ void ftFx_SpecialSEnd_IASA(HSD_GObj* gobj);
/* 0EA9A8 */ void ftFx_SpecialAirSEnd_IASA(HSD_GObj* gobj);
/* 0EA9AC */ void ftFx_SpecialSEnd_Phys(HSD_GObj* gobj);
/* 0EAA8C */ void ftFx_SpecialAirSEnd_Phys(HSD_GObj* gobj);
/* 0EAB90 */ void ftFx_SpecialSEnd_Coll(HSD_GObj* gobj);
/* 0EABCC */ void ftFx_SpecialAirSEnd_Coll(HSD_GObj* gobj);
/* 0EAC50 */ void ftFx_SpecialSEnd_Enter(HSD_GObj* gobj);
/* 0EACD8 */ void ftFx_SpecialAirSEnd_Enter(HSD_GObj* gobj);

#endif
