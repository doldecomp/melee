#ifndef _plstale_h_
#define _plstale_h_

#include <platform.h>

#include <baselib/gobj.h>

void plStale_InitAttackInstance(void);
void plStale_ResetStaleMoveTableForPlayer(s32 slot);
u16 plStale_IncrementAttackInstance(void);
void plStale_UpdateStaleMovesFromFighter(HSD_GObj* gobj, HSD_GObj* gobj_2);
void plStale_UpdateStaleMovesFromItem(HSD_GObj* gobj, HSD_GObj* gobj_2);

#endif
