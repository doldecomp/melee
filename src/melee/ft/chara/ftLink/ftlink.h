#ifndef MELEE_FT_CHARA_FTLINK_FTLINK_H
#define MELEE_FT_CHARA_FTLINK_FTLINK_H

#include <ctypes.h>

typedef struct _HSD_GObj HSD_GObj;


void ftLink_OnItemDrop(HSD_GObj* fighter_gobj, BOOL arg1);
void ftLink_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool);
void func_800EC06C(void);

#endif
