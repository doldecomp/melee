#ifndef GALE01_1601C4
#define GALE01_1601C4

#include <placeholder.h>
#include <platform.h>

#include "dolphin/gx/GXStruct.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

#include "ft/forward.h"
#include "gm/forward.h"
#include "mn/forward.h"
#include "sc/forward.h"

#include <printf.h>
#include <melee/gm/gm_17C0.h>

struct lbl_8046B488_t;

#include <melee/gm/gm_17C0.h>

/* 1601C4 */ int gm_801601C4(s8);
/* 160244 */ int gm_80160244(s8);
/* 1602C0 */ void gm_801602C0(s8);
/* 1603B0 */ void gm_801603B0(void);
/* 160400 */ u32
    fn_80160400(CharacterKind);      ///< gets character victory theme id
/* 160438 */ char* gm_80160438(s32); ///< gets character result anim path
/* 160474 */ bool gm_80160474(CharacterKind, MajorSceneKind);
/* 1604DC */ char*
    gm_801604DC(CharacterKind,
                MajorSceneKind); ///< gets characters trophy model
/* 160564 */ char* gm_80160564(CharacterKind, MajorSceneKind);
/* 1605EC */ u8 fn_801605EC(s32);
/* 160638 */ s8 gm_80160638(s32);
/* 1606A8 */ u8 fn_801606A8(int);
/* 160710 */ u8 fn_80160710(int);
/* 16075C */ int gm_8016075C(CharacterKind);
/* 1607A8 */ u8 fn_801607A8(int);
/* 1607F4 */ u8 fn_801607F4(int);
/* 160840 */ u8 fn_80160840(u8);
/* 160854 */ u32 gm_80160854(u8, u8, u8,
                             u8);     ///< gets the player hud color index
/* 160968 */ GXColor gm_80160968(u8); ///< gets the player hud color
/* 160980 */ const char* gm_80160980(u8 ckind);
/* 1609E0 */ const char* fn_801609E0(u8 ckind);
/* 160A60 */ const char* gm_80160A60(int);
/* 160B40 */ UNK_RET gm_80160B40(HSD_Text*, u8, u8);
/* 160C90 */ UNK_RET gm_80160C90(UNK_PARAMS);
/* 160DE8 */ UNK_RET fn_80160DE8(UNK_PARAMS);
/* 160F58 */ float fn_80160F58(u8 ckind);
/* 161004 */ UNK_RET fn_80161004(UNK_PARAMS);
/* 161154 */ UNK_RET fn_80161154(UNK_PARAMS);
/* 161C90 */ UNK_RET fn_80161C90(UNK_PARAMS);
/* 162068 */ void fn_80162068(void);
/* 162170 */ s32 fn_80162170(MatchEnd*);
/* 1623A4 */ s32 gm_801623A4(MatchEnd*);
/* 1623D8 */ int gm_801623D8(void);
/* 1623FC */ UNK_RET gm_801623FC(int);
/* 16247C */ UNK_RET gm_8016247C(int);
/* 162574 */ void gm_80162574(u8, u8);
/* 16260C */ void gm_8016260C(u8, u8);
/* 16279C */ u32 gm_8016279C(void);
/* 162800 */ u32 gm_80162800(struct MatchEnd*);
/* 1628C4 */ void gm_801628C4(u32, u32);
/* 162968 */ long gm_80162968(u32 seconds);
/* 1629B4 */ long gm_801629B4(s32 amount);
/* 162A00 */ long gm_80162A00(void);
/* 162A4C */ long gm_80162A4C(s32 amount);
/* 162A98 */ UNK_RET gm_80162A98(s32);
/* 162B4C */ UNK_RET gm_80162B4C(s32);
/* 162B98 */ void gm_80162B98(void);
/* 162BD8 */ int gm_80162BD8(u8);
/* 162BFC */ UNK_RET fn_80162BFC(s8 ckind, int);
/* 162C48 */ int gm_80162C48(void);
/* 162CCC */ bool fn_80162CCC(void);
/* 162D1C */ bool gm_80162D1C(void);
/* 162D6C */ u8 gm_80162D6C(void);
/* 162DD4 */ int gm_80162DD4(u8);
/* 162DF8 */ UNK_RET fn_80162DF8(s8 ckind, int);
/* 162E44 */ int gm_80162E44(void);
/* 162EC8 */ bool gm_80162EC8(void);
/* 162F18 */ bool gm_80162F18(void);
/* 162F68 */ u8 gm_80162F68(void);
/* 162FD0 */ int gm_80162FD0(u8);
/* 162FF4 */ UNK_RET fn_80162FF4(s8 ckind, int);
/* 163040 */ int gm_80163040(void);
/* 1630C4 */ bool fn_801630C4(void);
/* 163114 */ bool gm_80163114(void);
/* 163164 */ u8 gm_80163164(void);
/* 1631CC */ u32 gm_801631CC(u8);
/* 1631F0 */ u32 gm_801631F0(void);
/* 163274 */ u16 gm_80163274(u8);
/* 163298 */ UNK_RET gm_80163298(s8 c_kind, int);
/* 16332C */ int gm_8016332C(int);
/* 163374 */ void gm_80163374(int, void*, void*, void*, void*);
/* 1634D4 */ int gm_801634D4(void*, void*, void*, void*);
/* 16365C */ bool gm_8016365C(u8);
/* 163690 */ int gm_80163690(int);
/* 1636D8 */ void gm_801636D8(int, void*, void*, void*, void*);
/* 163838 */ int gm_80163838(void*, void*, void*, void*);
/* 1639C0 */ bool gm_801639C0(u8);
/* 1639F4 */ int gm_801639F4(int);
/* 163A3C */ void gm_80163A3C(int, void*, void*, void*, void*);
/* 163B9C */ int gm_80163B9C(void*, void*, void*, void*);
/* 163D24 */ bool fn_80163D24(void);
/* 163D74 */ bool fn_80163D74(void);
/* 163DC4 */ u16 gm_Get3MinMultimanHighscore(u8);
/* 163DE8 */ int gm_Get3MinMultimanTotalHighscore(void);
/* 163E3C */ u16 gm_Get15MinMultimanHighscore(u8);
/* 163E60 */ int gm_Get15MinMultimanTotalHighscore(void);
/* 163EB4 */ int gm_GetEndlessHighscore(u8);
/* 163ED8 */ int gm_GetEndlessTotalHighscore(void);
/* 163F2C */ int gm_GetCruelHighscore(u8);
/* 163F50 */ int gm_GetCruelTotalHighscore(void);
/* 163FA4 */ int fn_80163FA4(u8);
/* 16400C */ u8 gm_8016400C(u8 ckind);
/* 164024 */ u8 gm_80164024(u8 ckind);
/* 16403C */ bool gm_8016403C(u8 item);
/* 1640B0 */ void fn_801640B0(u64* item_mask);
/* 16419C */ float fn_8016419C(u8);
/* 1641B4 */ float fn_801641B4(u8);
/* 1641CC */ u16 gm_801641CC(u8);
/* 1641E4 */ void gm_801641E4(u8 stage, u8 enable);
/* 164250 */ UNK_RET gm_80164250(UNK_PARAMS);
/* 1642A0 */ UNK_RET fn_801642A0(UNK_PARAMS);
/* 164330 */ u8 gm_80164330(u8);
/* 164430 */ bool gm_80164430(u16);
/* 164504 */ int gm_80164504(u16);
/* 164600 */ bool gm_80164600(void);
/* 16468C */ UNK_RET gm_8016468C(UNK_PARAMS);
/* 1647D0 */ void gm_801647D0(void);
/* 1647F8 */ int gm_801647F8(u8);
/* 164840 */ bool gm_80164840(u8 ckind); ///< character unlocked check
/* 164910 */ void gm_80164910(int);
/* 164A0C */ UNK_RET gm_80164A0C(int);
/* 164ABC */ bool gm_80164ABC(void);
/* 164B48 */ bool fn_80164B48(void);
/* 164F18 */ void gm_80164F18(void);
/* 16505C */ void gm_8016505C(void);
/* 165084 */ bool gm_80165084(void);
/* 1650E8 */ void fn_801650E8(void);
/* 165108 */ void fn_80165108(int, int);
/* 165190 */ void fn_80165190(s32, s32);
/* 1651FC */ void fn_801651FC(s32, s32);
/* 165268 */ void gm_80165268(int);
/* 165290 */ void gm_80165290(int);
/* 1652B0 */ void fn_801652B0(s32, s32);
/* 1652D8 */ void* fn_801652D8(void);
/* 165388 */ HSD_GObj* gm_80165388(u16, u8, u8, s32);
/* 1653C8 */ void gm_801653C8(HSD_GObj*);
/* 1653E8 */ float fn_801653E8(u8);
/* 165418 */ u8 fn_80165418(MatchEnd*);
/* 1654A0 */ u8 fn_801654A0(MatchEnd*);
/* 165548 */ u8 fn_80165548(MatchEnd*, s8, u8);
/* 1656A8 */ u8 fn_801656A8(MatchEnd*, s8);
/* 16588C */ UNK_RET fn_8016588C(UNK_PARAMS);
/* 165AC0 */ UNK_RET fn_80165AC0(UNK_PARAMS);
/* 165D60 */ UNK_RET fn_80165D60(UNK_PARAMS);
/* 165E7C */ UNK_RET fn_80165E7C(UNK_PARAMS);
/* 165FA4 */ UNK_RET fn_80165FA4(UNK_PARAMS);
/* 1661E0 */ UNK_RET fn_801661E0(UNK_PARAMS);
/* 166378 */ void gm_80166378(UNK_T);
/* 166A98 */ UNK_RET gm_80166A98(UNK_PARAMS);
/* 166CBC */ s32 gmCamera_801A2640(void);
/* 166CCC */ void gm_80166CCC(MatchEnd*, MatchEnd*);
/* 167140 */ bool gm_80167140(MatchEnd*);
/* 167194 */ int fn_80167194(MatchEnd*);
/* 16719C */ void fn_8016719C(s32, s32);
/* 167320 */ void gm_80167320(int slot, bool);
/* 167470 */ void gm_80167470(int, bool);
/* 1674C4 */ UNK_RET gm_801674C4(UNK_PARAMS);
/* 16758C */ void fn_8016758C(void);
/* 167638 */ s32 fn_80167638(s32, Vec3*, Vec3*);
/* 1677C0 */ void gm_801677C0(struct gm_801677C0_s* arg0);
/* 1677E8 */ void gm_801677E8(s8 arg0);
/* 1677F0 */ u8 gm_801677F0(void);
/* 1677F8 */ bool gm_801677F8(int port, int);
/* 167858 */ void gm_80167858(int port, int, int, int);
/* 1678F8 */ void gm_801678F8(int port, int, int);
/* 16795C */ void gm_8016795C(struct PlayerInitData*);
/* 167A14 */ void gm_80167A14(struct PlayerInitData*);
/* 167A64 */ void gm_80167A64(struct StartMeleeRules*);
/* 167B50 */ void gm_80167B50(struct VsModeData*);
/* 167BC8 */ void
gm_80167BC8(struct VsModeData*); // inits VsModeData from game rules
/* 167FC4 */ void gm_80167FC4(struct SSSData*);
/* 1685D4 */ s8 gm_801685D4(u8, u8);
/* 168638 */ void gm_80168638(MatchEnd*);
/* 168710 */ void gm_80168710(MatchEnd*, VsModeData*);
/* 1688AC */ int gm_801688AC(MatchEnd*);
/* 168940 */ int gm_80168940(MatchEnd*);
/* 16895C */ void gm_8016895C(HSD_JObj*, DynamicModelDesc*, int idx);
/* 1689E4 */ void fn_801689E4(HSD_JObj*, DynamicModelDesc*, int);
/* 168A6C */ UNK_RET fn_80168A6C(UNK_PARAMS);
/* 168B34 */ float gm_80168B34(CharacterKind, int, int);
/* 168BF8 */ float gm_80168BF8(int);
/* 168C5C */ void gm_80168C5C(u32);
/* 168E54 */ UNK_RET fn_80168E54(s8, s8, u8, u8);
/* 168F2C */ void fn_80168F2C(void);
/* 168F7C */ UNK_RET fn_80168F7C(UNK_PARAMS);
/* 168F88 */ void gm_80168F88(void);
/* 168FC4 */ void gm_80168FC4(void);
/* 169000 */ UNK_RET fn_80169000(UNK_PARAMS);
/* 169238 */ u8 gm_80169238(u8);
/* 169264 */ u8 gm_80169264(u8);
/* 169290 */ u8 gm_80169290(u8);
/* 1692BC */ u8 gm_801692BC(u8);
/* 1692E8 */ void gm_801692E8(u32 secs, datetime* datetime);
/* 169364 */ struct lbl_8046B488_t* fn_80169364(void);
/* 169370 */ u8 gm_80169370(s32);
/* 169384 */ int gm_80169384(void);
/* 169394 */ s32 gm_80169394(void);
/* 1693BC */ bool gm_801693BC(int);
/* 169434 */ void fn_80169434(s32 arg0);
/* 169444 */ bool fn_80169444(int);
/* 1694A0 */ int gm_801694A0(HSD_GObj*);
/* 169520 */ void* gm_80169520(void);
/* 169530 */ void* gm_80169530(void);
/* 169540 */ void* gm_80169540(void);
/* 169550 */ UNK_RET fn_80169550(int slot);
/* 169574 */ UNK_RET fn_80169574(UNK_PARAMS);
/* 1695BC */ UNK_RET fn_801695BC(UNK_PARAMS);
/* 1697FC */ UNK_RET fn_801697FC(UNK_PARAMS);
/* 16989C */ UNK_RET fn_8016989C(UNK_PARAMS);
/* 169900 */ UNK_RET fn_80169900(UNK_PARAMS);
/* 169A84 */ UNK_RET fn_80169A84(UNK_PARAMS);
/* 169C54 */ UNK_RET fn_80169C54(s8, s8);
/* 169F50 */ UNK_RET fn_80169F50(s8, s8);
/* 16A09C */ UNK_RET fn_8016A09C(UNK_PARAMS);
/* 16A164 */ UNK_RET gm_8016A164(UNK_PARAMS);
/* 16A1F8 */ bool gm_8016A1F8(void);
/* 16A21C */ void gm_8016A21C(StartMeleeRules*);
/* 16A22C */ UNK_RET gm_8016A22C(s8 ckind0, s8 ckind1, s8 ckind2, int, int,
                                 int, int, int, int, s8 ckind, int color, int,
                                 int, int opp_count, int, int, int, f32, f32);
/* 16A404 */ void gm_8016A404(s32 arg0);
/* 16A414 */ void gm_8016A414(f32 arg8);
/* 16A424 */ void gm_8016A424(s8 arg0);
/* 16A434 */ void gm_8016A434(void);
/* 16A450 */ void fn_8016A450(void);
/* 16A46C */ void fn_8016A46C(void);
/* 16A488 */ UNK_RET fn_8016A488(UNK_PARAMS);
/* 16A4C8 */ UNK_RET fn_8016A4C8(UNK_PARAMS);
/* 16A92C */ void gm_8016A92C(StartMeleeRules*);
/* 16A944 */ bool gm_8016A944(UNK_PARAMS);
/* 16A97C */ void* gm_8016A97C(void);
/* 16A98C */ UNK_T gm_8016A98C(void);
/* 16A998 */ UNK_RET gm_8016A998(UNK_PARAMS);
/* 16A9E8 */ UNK_RET gm_8016A9E8(UNK_PARAMS);
/* 16AC44 */ UNK_RET gm_8016AC44(s8 ckind, s8 costume_id);

#endif
