#ifndef GALE01_0860C4
#define GALE01_0860C4

#include <melee/cm/forward.h>
#include <melee/ft/forward.h>
#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>

/* 0860C4 */ s32 ftLib_CountFighters(void);
/* 0860E8 */ bool ftLib_IsMasterHandPresent(void);
/* 086140 */ bool ftLib_IsCrazyHandPresent(void);
/* 086198 */ HSD_GObj* ftLib_FindLowestPercentOpponent(HSD_GObj*);
/* 08627C */ HSD_GObj* ftLib_FindNearestOpponent(Vec3* pos, HSD_GObj*);
/* 086368 */ Fighter_GObj* ftLib_FindNearestOpponentInDir(Vec3*, Fighter_GObj*,
                                                          float);
/* 0864A8 */ float ftLib_GetOpponentsDir(Vec3*, HSD_GObj*);
/* 0865C0 */ float ftLib_GetFacingDir(HSD_GObj*);
/* 0865CC */ s32 ftLib_GetGroundAir(HSD_GObj*);
/* 0865D8 */ void ftLib_GetLStick(HSD_GObj*, float*, float*);
/* 0865F0 */ HSD_JObj* ftLib_GetHipJObj(HSD_GObj*);
/* 086630 */ HSD_JObj* ftLib_GetPartJObj(Fighter_GObj*, Fighter_Part part);
/* 086644 */ void ftLib_GetPos(Fighter_GObj*, Vec3*);
/* 086664 */ void ftLib_SetPos(HSD_GObj*, Vec3*);
/* 086684 */ void ftLib_GetPrevPos(HSD_GObj*, Vec3*);
/* 0866A4 */ void ftLib_SetScale(HSD_GObj*, float);
/* 0866DC */ void ftLib_GetCameraBonePos(HSD_GObj*, Vec3*);
/* 086724 */ void ftLib_ReleaseItem(HSD_GObj*, HSD_GObj*);
/* 086764 */ void ftLib_ClearHeldSpecialItem(HSD_GObj*);
/* 086794 */ HSD_GObj* ftLib_GetItem(HSD_GObj*);
/* 0867A0 */ bool ftLib_IsHoldingItem(HSD_GObj*, HSD_GObj*);
/* 0867CC */ HSD_GObj* ftLib_GetHeldSpecialItem(HSD_GObj*);
/* 0867D8 */ bool ftLib_IsInputDisabled(HSD_GObj*);
/* 0867E8 */ void ftLib_DisableInput(HSD_GObj*);
/* 086824 */ void ftLib_DisableAllInput(void);
/* 08688C */ void ftLib_EnableInput(HSD_GObj*);
/* 0868A4 */ void ftLib_EnableAllInput(void);
/* 0868D4 */ bool ftLib_IsItemVisible(HSD_GObj*, HSD_GObj*);

/// @returns @c true if @p gobj is a #Fighter, otherwise @c false.
/* 086960 */ bool ftLib_IsFighter(HSD_GObj* gobj);

/* 086984 */ CollData* ftLib_GetCollData(HSD_GObj*);
/* 086990 */ void ftLib_GetECBCenter(HSD_GObj*, Vec3*);
/* 0869D4 */ float ftLib_GetModelScale(HSD_GObj*);
/* 0869F8 */ float ftLib_800869F8(HSD_GObj*);
/* 086A0C */ float ftLib_GetScale(HSD_GObj*);
/* 086A18 */ bool ftLib_IsShielding(HSD_GObj*);
/* 086A4C */ void ftLib_80086A4C(HSD_GObj*, float);
/* 086A58 */ bool ftLib_GetScreenPos(HSD_GObj*, S32Vec2*);
/* 086A8C */ bool ftLib_UpdateScreenVisibility(HSD_GObj*);
/* 086B64 */ bool ftLib_IsOffscreen(HSD_GObj*);
/* 086B74 */ CmSubject* ftLib_GetCameraSubject(HSD_GObj*);
/* 086B80 */ float ftLib_80086B80(HSD_GObj*);
/* 086B90 */ void ftLib_GetCameraSubjectBonePos(HSD_GObj*, Vec3* v);
/* 086BB4 */ bool ftLib_IsCameraSubjectInBounds(HSD_GObj*);
/* 086BE0 */ u8 ftLib_GetPlayerIndex(HSD_GObj*);
/* 086BEC */ void ftLib_GetPosDelta(HSD_GObj*, Vec3*);

/// @returns A fighter action state ID.
/* 086C0C */ enum_t ftLib_GetMotionId(HSD_GObj*);

/* 086C18 */ void ftLib_StartRumble(HSD_GObj*, s32, s32);
/* 086C9C */ void ftLib_StartRumbleAll(s32, s32);
/* 086D40 */ void ftLib_StartItemRumble(HSD_GObj*, s32, s32);
/* 086DC4 */ void ftLib_StartItemRumbleAll(s32, s32);
/* 086E68 */ void ftLib_StopItemRumble(HSD_GObj*);
/* 086EB4 */ s32 ftLib_GetTeam(HSD_GObj*);
/* 086EC0 */ bool ftLib_IsInHitstun(HSD_GObj*);
/* 086ED0 */ bool ftLib_CanBeMagnified(HSD_GObj*);
/* 086F4C */ bool ftLib_80086F4C(HSD_GObj*);
/* 086F80 */ float ftLib_GetNameTagHeight(HSD_GObj*);
/* 086FA8 */ bool ftLib_IsSwordSwing(HSD_GObj*);
/* 086FD4 */ bool ftLib_IsSamePlayer(HSD_GObj*, HSD_GObj*);
/* 08701C */ bool ftLib_IsSleeping(HSD_GObj*);
/* 08702C */ void ftLib_IncFighterRefCount(s32);
/* 087050 */ void ftLib_DecFighterRefCount(s32);
/* 087074 */ bool ftLib_GetShakeOffset(HSD_GObj*, Vec3*);
/* 0870BC */ bool ftLib_GetSubColor(HSD_GObj*, GXColor*);
/* 0870F0 */ void ftLib_SetPercent(HSD_GObj*, s32);
/* 087120 */ s32 ftLib_GetPercent(HSD_GObj*);
/* 087140 */ void ftLib_80087140(HSD_GObj*);
/* 0871A8 */ void ftLib_ApplyMetalBox(Fighter_GObj*, Item_GObj*);
/* 087284 */ bool ftLib_IsSmashThrow(HSD_GObj*);
/* 0872A4 */ FighterKind ftLib_GetKind(HSD_GObj*);
/* 0872B0 */ LbShadow* ftLib_GetShadow(HSD_GObj*);
/* 0872BC */ bool ftLib_CastsShadow(HSD_GObj*);
/* 087300 */ s32 ftLib_GetLastAttackerSlot(HSD_GObj*);
/* 08730C */ s32 ftLib_IsLastAttackerSubFighter(HSD_GObj*);
/* 08731C */ s32 ftLib_IsSleeping_8008731C(HSD_GObj*);
/* 08732C */ bool ftLib_IsDead(HSD_GObj*);
/* 087354 */ bool ftLib_IsDeadUp(HSD_GObj*);
/* 08737C */ bool ftLib_IsDeadUpStar(HSD_GObj*);
/* 0873A4 */ bool ftLib_IsDeadUpFall(HSD_GObj*);
/* 0873CC */ bool ftLib_IsRebirth(HSD_GObj*);
/* 0873F4 */ bool ftLib_IsEntry(HSD_GObj*);
/* 08741C */ HSD_GObj* ftLib_FindBySpawnNum(u32);
/* 087454 */ float ftLib_GetKnockbackMagnitude(HSD_GObj*);
/* 087460 */ u32 ftLib_GetSpawnNum(HSD_GObj*);
/* 08746C */ s32 ftLib_8008746C(HSD_GObj*);
/* 0874BC */ s32 ftLib_IsSubFighter(HSD_GObj*);
/* 0874CC */ void ftLib_800874CC(HSD_GObj*, void*, s32);
/* 087508 */ void ftLib_LoadFighterCostume(s8, u8);
/// /* 087508 */ void ftLib_LoadFighterCostume(FighterKind, u8);
/* 087574 */ void ftLib_LoadFighterAllCostumes(s8);
/// /* 087574 */ void ftLib_LoadFighterAllCostumes(FighterKind);
/* 087610 */ void ftLib_LoadKirbyHats(u8);
/* 0876B4 */ void ftLib_IsFramesRemaining(HSD_GObj*);
/* 0876D4 */ bool ftLib_IsChargingSmash(HSD_GObj*);
/* 0876F4 */ s32 ftLib_GetLastHitSourceType(HSD_GObj*);
/* 087700 */ s32 ftLib_GetLastHitSourceKind(HSD_GObj*);
/* 08770C */ void ftLib_GetGameWatchColor(HSD_GObj*, void* dst);
/* 087744 */ void ftLib_GetGameWatchOutlineColor(HSD_GObj*, void* dst);
/* 08777C */ float ftLib_GetGroundSlopeAngle(HSD_GObj*);
/* 0877D4 */ bool ftLib_IsBeingNudged(HSD_GObj*);

#endif
