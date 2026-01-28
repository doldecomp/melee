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
/* 23EE38 */ s32 mnDiagram_GetAveragePlayerCount(u8 is_name_mode,
                                                 u8 player_index);
/* 23EF70 */ int mnDiagram_GetNameTotalKOs(u8 field_index);
/* 23EFE4 */ int mnDiagram_GetNameTotalFalls(u8 field_index);
/* 23F068 */ int mnDiagram_GetFighterTotalKOs(u8 field_index);
/* 23F0DC */ int mnDiagram_GetFighterTotalFalls(u8 field_index);
/* 23F14C */ void mnDiagram_FormatDecimalNumber(char* buf, u32 val, int mode);
/* 23F238 */ void mnDiagram_FormatTime(char* buf, s32 seconds);
/* 23F334 */ void mnDiagram_IntToStr(char* buf, u32 val);
/* 23F3A8 */ u8 mnDiagram_GetPrevNameIndex(s32 idx);
/* 23F400 */ u8 mnDiagram_GetNextNameIndex(s32 idx);
/* 23F45C */ u8 mnDiagram_GetPrevFighterIndex(s32 idx);
/* 23F4CC */ u8 mnDiagram_GetNextFighterIndex(s32 idx);
/* 23F540 */ u32 mnDiagram_GetNamePlayTimeByFighter(int name_idx,
                                                    int fighter_idx);
/* 23F578 */ int mnDiagram_GetRankedFighterForName(int rank, int name_idx,
                                                   u32 (*func)(int, int));
/* 23F8CC */ u8 mnDiagram_GetLeastPlayedFighter(u8 name_idx);
/* 23FA6C */ void mnDiagram_SortFightersByKOs(void);
/* 23FC28 */ void mnDiagram_SortNamesByKOs(void);
/* 23FDD8 */ int mnDiagram_CountUnlockedFighters(void);
/* 23FE30 */ void mnDiagram_PopupInputProc(HSD_GObj*);
/* 23FED4 */ void mnDiagram_InputProc(HSD_GObj*);
/* 240B18 */ void mnDiagram_PopupCleanup(void* arg0);
/* 240B98 */ void mnDiagram_PopupAnimProc(void* arg0);
/* 240D94 */ void mnDiagram_PopupSetupText(void* gobj, s32 col_idx,
                                           s32 row_idx, s32 is_name_mode);
/* 241310 */ void mnDiagram_CreatePopup(s32 col_idx, s32 row_idx,
                                        s32 is_name_mode);
/* 241668 */ void mnDiagram_ClearGridContent(void* gobj);
/* 241730 */ void mnDiagram_UpdateGridDisplay(void* gobj, int col_idx,
                                              int row_idx);
/* 2417D0 */ void mnDiagram_UpdateScrollArrows(HSD_GObj* gobj);
/* 241AE8 */ void mnDiagram_ExitAnimProc(HSD_GObj* gobj);
/* 241B4C */ void mnDiagram_UpdateScrollArrowVisibility(void* gobj, int count);
/* 241BF8 */ void mnDiagram_OnFrame(HSD_GObj* gobj);
/* 241E78 */ void mnDiagram_DrawCellNumber(void* gobj, u8 col, u8 row,
                                           s32 value);
/* 24227C */ void mnDiagram_DrawGridCells(void* gobj, s32 col_offset,
                                          s32 row_offset, u8 is_name_mode);
/* 2427B4 */ void mnDiagram_DrawNameHeaders(void* gobj, s32 col_offset,
                                            s32 row_offset);
/* 242B38 */ HSD_JObj* mnDiagram_CreateFighterIcon(int fighter_idx, int mode);
/* 242C0C */ void mnDiagram_DrawFighterHeaders(void* gobj, int col_offset,
                                               int row_offset);
/* 243038 */ void mnDiagram_CursorProc(HSD_GObj* gobj);
/* 2433AC */ void mnDiagram_CreateCursor(void);
/* 243434 */ void mnDiagram_Setup(u8 anim_state);
/* 2437E8 */ void mnDiagram_Init(s32 load_dat, s32 anim_state);

#endif
