#ifndef MELEE_MN_MNDIAGRAM2_H
#define MELEE_MN_MNDIAGRAM2_H

#include <placeholder.h>

#include <baselib/gobj.h>
#include <melee/mn/types.h>

/* 243A3C */ bool mnDiagram2_IsTimeStat(u8 stat_type);
/* 243A5C */ bool mnDiagram2_IsDistanceStat(u8 stat_type);
/* 243A84 */ bool mnDiagram2_IsPercentageStat(u8 stat_type);
/* 243AB4 */ bool mnDiagram2_IsIconOnlyStat(u8 stat_type);
/* 243ADC */ void mnDiagram2_ClearStatRows(HSD_GObj* gobj);
/* 243BBC */ void mnDiagram2_UpdateHeader(HSD_GObj* gobj, u8 is_name_mode,
                                          u8 entity_idx);
/* 243D40 */ void mnDiagram2_HandleInput(HSD_GObj* gobj);
/* 244330 */ int mnDiagram2_GetStatValue(int is_name_mode, u8 stat_type,
                                         u8 entity_idx);
/* 24469C */ void mnDiagram2_CreateStatRow(HSD_GObj* gobj, u8 is_name_mode,
                                           u8 stat_type, u8 row_idx,
                                           u8 entity_idx);
/* 244C74 */ void mnDiagram2_PopulateStatRows(HSD_GObj* gobj, u8 scroll_offset,
                                              u8 is_name_mode, u8 entity_idx);
/* 244D20 */ void mnDiagram2_OnAnimComplete(HSD_GObj* gobj);
/* 244D80 */ void mnDiagram2_UpdateScrollArrows(HSD_GObj* gobj);
/* 244F68 */ void mnDiagram2_Think(HSD_GObj* gobj);
/* 245028 */ void mnDiagram2_FreeUserData(Diagram2* data);
/* 245068 */ void mnDiagram2_InitUserData(void* arg);
/* 245178 */ void mnDiagram2_Create(int arg0);
/* 2453B0 */ void mnDiagram2_Init(void);
/* 24541C */ u8 mnDiagram2_GetRankedFighter(u8 stat_type, u8 rank);
/* 245684 */ u8 mnDiagram2_GetRankedName(u8 stat_type, u8 rank);
/* 24589C */ void mnDiagram2_GetAggregatedFighterRank(u8* out, u8 type,
                                                      u8 idx);
/* 245AE4 */ void mnDiagram2_ClearDetailView(HSD_GObj* gobj);

#endif
