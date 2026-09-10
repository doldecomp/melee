#ifndef GALE01_23EA2C
#define GALE01_23EA2C

#include <sysdolphin/baselib/forward.h>

#include <melee/mn/types.h>
#include <melee/sc/types.h>

/* 23EA2C */ u8 mnDiagram_GetFighterByIndex(int idx);
/* 23EA40 */ u8 mnDiagram_GetNameByIndex(int idx);

/**
 * @brief Tests whether a distance is at or above the large-unit threshold.
 *
 * The threshold is 160934 when #lbLang_IsSavedLanguageUS is true and 100000
 * otherwise. Callers use a true result to select SIS entry @c 0x7F instead of
 * their per-stat unit entry. Despite the name, this is not an arithmetic
 * overflow check.
 *
 * @param[in] distance Accumulated distance, before conversion.
 */
/* 23EA54 */ bool mnDiagram_IsDistanceOverflow(u32 distance);

/**
 * @brief Scales a distance for display with a language-dependent divisor.
 *
 * US: @c distance/30.4788 (f64, truncated) below 160934, else
 * @c distance/160934. Otherwise: @c distance/100 below 100000, else
 * @c distance/100000. The result is not capped at the threshold: 160933 gives
 * 5280, 160934 gives 1, and 321868 gives 2. The unit is chosen by the caller.
 *
 * @param[in] distance Accumulated distance, before conversion.
 */
/* 23EAC4 */ u32 mnDiagram_ConvertDistanceForDisplay(u32 distance);

/* 23EB84 */ s32 mnDiagram_GetHitPercentage(u8 is_name_mode, u8 player_index);
/* 23ECC4 */ s32 mnDiagram_GetPlayPercentage(u8 is_name_mode, u8 player_index);
/* 23EE38 */ s32 mnDiagram_GetAveragePlayerCount(u8 is_name_mode,
                                                 u8 player_index);
/* 23EF70 */ int mnDiagram_GetNameTotalKOs(u8 field_index);
/* 23EFE4 */ int mnDiagram_GetNameTotalFalls(u8 field_index);
/* 23F068 */ int mnDiagram_GetFighterTotalKOs(u8 field_index);
/* 23F0DC */ int mnDiagram_GetFighterTotalFalls(u8 field_index);

/**
 * @brief Writes @p val as NUL-terminated decimal text with its low
 * @p decimal_places digits after a decimal point.
 *
 * Callers pass 0 or 2. With 2, 5 gives "0.05" and 12345 gives "123.45"; with
 * 0, no decimal point is written. No thousands separators.
 *
 * @param[out] buf Must hold the whole result and its NUL.
 * @param[in] val Value scaled by 10^@p decimal_places.
 * @param[in] decimal_places Digits after the decimal point.
 */
/* 23F14C */ void mnDiagram_FormatDecimalNumber(char* buf, u32 val,
                                                int decimal_places);

/**
 * @brief Writes nonnegative @p seconds as "M:SS" with unpadded minutes.
 *
 * 59 gives "0:59", 60 gives "1:00", and 600000 gives "10000:00"; minutes are
 * neither capped nor split into hours. Callers apply their own limits.
 *
 * @param[out] buf Must hold the whole result and its NUL.
 * @param[in] seconds Nonnegative elapsed seconds.
 */
/* 23F238 */ void mnDiagram_FormatTime(char* buf, s32 seconds);

/**
 * @brief Writes @p val as NUL-terminated decimal digits.
 *
 * No padding or separators; 0 gives "0". Both callers cap @p val first. This
 * and #mnDiagram_FormatDecimalNumber use the signed #mn_GetDigitCount and
 * #mn_GetDigitAt, so the full @c u32 range is not established.
 *
 * @param[out] buf Must hold the whole result and its NUL.
 * @param[in] val Value to format.
 */
/* 23F334 */ void mnDiagram_IntToStr(char* buf, u32 val);

/* 23F3A8 */ u8 mnDiagram_GetPrevNameIndex(s32 idx);
/* 23F400 */ u8 mnDiagram_GetNextNameIndex(s32 idx);
/* 23F45C */ u8 mnDiagram_GetPrevFighterIndex(s32 idx);
/* 23F4CC */ u8 mnDiagram_GetNextFighterIndex(s32 idx);
/* 23F540 */ u32
mnDiagram_GetNamePlayTimeByFighter(int name_idx,
                                   SelectableCharacterKind fighter_idx);
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
/* 240D94 */ void mnDiagram_CreatePopupTexts(void* arg0, s32 arg1, s32 arg2,
                                             s32 arg3);
/* 241310 */ void mnDiagram_CreatePopup(s32 arg0, s32 arg1, s32 arg2);
/* 241668 */ void mnDiagram_ClearGrid(void* arg0);
/* 241730 */ void mnDiagram_RefreshGrid(HSD_GObj* arg0, int arg1, int arg2);
/* 2417D0 */ void mnDiagram_UpdateScrollArrows(HSD_GObj* gobj);
/* 241AE8 */ void mnDiagram_ExitAnimProc(HSD_GObj* gobj);
/* 241B4C */ void mnDiagram_UpdateScrollArrowVisibility(void* gobj, int count);
/* 241BF8 */ void mnDiagram_OnFrame(HSD_GObj* gobj);
/* 241E78 */ void mnDiagram_DrawCellValue(void* arg0, u8 arg1, u8 arg2,
                                          int arg3);
/* 24227C */ void mnDiagram_DrawGridValues(void* arg0, s32 arg1, s32 arg2,
                                           u8 arg3);
/* 2427B4 */ void mnDiagram_DrawNameHeaders(void* arg0, s32 arg1, s32 arg2);
/* 242B38 */ HSD_JObj* mnDiagram_CreateFighterIcon(int idx, int arg1);
/* 242C0C */ void mnDiagram_DrawFighterHeaders(void* arg0, int arg1, int arg2);
/* 243038 */ void mnDiagram_CursorProc(HSD_GObj* gobj);
/* 2433AC */ void mnDiagram_CreateCursor(void);
/* 243434 */ void mnDiagram_CreateScreen(u8 arg0);
/* 2437E8 */ void mnDiagram_Init(u8 arg0, u8 arg1);

/* 4A0834 */ extern StaticModelDesc MenMainConB2_Top;
/* 4A0844 */ extern StaticModelDesc MenMainConB3_Top;
/* 4A0854 */ extern StaticModelDesc MenMainCursorB3_Top;

#endif
