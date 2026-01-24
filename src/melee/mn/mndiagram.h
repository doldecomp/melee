#ifndef GALE01_23EA2C
#define GALE01_23EA2C

#include <placeholder.h>

#include <baselib/forward.h>

/* 23EA2C */ u8 mnDiagram_GetFighterByIndex(int idx);
/* 23EA40 */ u8 mnDiagram_GetNameByIndex(int idx);
/* 23EA54 */ bool mnDiagram_IsDistanceOverflow(u32 distance);
/* 23EAC4 */ u32 mnDiagram_ConvertDistanceForDisplay(u32 distance);
/* 23EB84 */ s32 mnDiagram_GetHitPercentage(u8 is_name_mode, u8 player_index);
/* 23ECC4 */ s32 mnDiagram_GetPlayPercentage(u8 is_name_mode, u8 player_index);
/* 23EE38 */ s32 mnDiagram_GetAveragePlayerCount(u8 is_name_mode, u8 player_index);
/* 23EF70 */ int mnDiagram_GetNameTotalKOs(u8 field_index);
/* 23EFE4 */ int mnDiagram_GetNameTotalFalls(u8 field_index);
/* 23F068 */ int mnDiagram_GetFighterTotalKOs(u8 field_index);
/* 23F0DC */ int mnDiagram_GetFighterTotalFalls(u8 field_index);
/* 23F14C */ void mnDiagram_FormatDecimalNumber(char* buf, u32 val, int mode);
/* 23F238 */ void mnDiagram_FormatTime(char* buf, u32 val);
/* 23F334 */ void mnDiagram_IntToStr(char* buf, u32 val);
/* 23F3A8 */ u8 mnDiagram_GetPrevNameIndex(u8 idx);
/* 23F400 */ u8 mnDiagram_GetNextNameIndex(u8 idx);
/* 23F45C */ u8 mnDiagram_GetPrevFighterIndex(u8 idx);
/* 23F4CC */ u8 mnDiagram_GetNextFighterIndex(u8 idx);
/* 23F540 */ u32 mnDiagram_GetNamePlayTimeByFighter(int name_idx,
                                                    int fighter_idx);
/* 23F578 */ int mnDiagram_GetRankedFighterForName(int rank, int name_idx,
                                                   u32 (*func)(int, int));
/* 23F8CC */ u8 mnDiagram_GetLeastPlayedFighter(u8 name_idx);
/* 23FA6C */ void mnDiagram_8023FA6C(void);
/* 23FC28 */ void mnDiagram_8023FC28(void);
/* 23FDD8 */ int mnDiagram_CountUnlockedFighters(void);
/* 23FE30 */ void mnDiagram_PopupInputProc(HSD_GObj*);
/* 23FED4 */ void mnDiagram_InputProc(HSD_GObj*);
/* 240B18 */ void mnDiagram_PopupCleanup(void* arg0);
/* 240B98 */ void mnDiagram_PopupAnimProc(void* arg0);
/* 240D94 */ void mnDiagram_80240D94(void* arg0, s32 arg1, s32 arg2, s32 arg3);
/* 241310 */ void mnDiagram_80241310(s32 arg0, s32 arg1, s32 arg2);
/* 241668 */ void mnDiagram_80241668(void* arg0);
/* 241730 */ void mnDiagram_80241730(void* arg0, int arg1, int arg2);
/* 2417D0 */ void mnDiagram_802417D0(HSD_GObj* gobj);
/* 241AE8 */ void mnDiagram_ExitAnimProc(HSD_GObj* gobj);
/* 241B4C */ void mnDiagram_UpdateScrollArrowVisibility(void* gobj, int count);
/* 241BF8 */ void mnDiagram_OnFrame(HSD_GObj* gobj);
/* 241E78 */ void mnDiagram_80241E78(void* arg0, u8 arg1, u8 arg2, s32 arg3);
/* 24227C */ void mnDiagram_8024227C(void* arg0, s32 arg1, s32 arg2, u8 arg3);
/* 2427B4 */ void mnDiagram_802427B4(void* arg0, s32 arg1, s32 arg2);
/* 242B38 */ HSD_JObj* mnDiagram_80242B38(int idx, int arg1);
/* 242C0C */ void mnDiagram_80242C0C(void* arg0, int arg1, int arg2);
/* 243038 */ void mnDiagram_CursorProc(HSD_GObj* gobj);
/* 2433AC */ void mnDiagram_802433AC(void);
/* 243434 */ void mnDiagram_80243434(u8 arg0);
/* 2437E8 */ void mnDiagram_802437E8(s32 arg0, s32 arg1);

#endif
