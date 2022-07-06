#ifndef _ftzakoboy_h_
#define _ftzakoboy_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

typedef struct _ftZakoboyAttributes
{
    s32 x0;
} ftZakoboyAttributes;

void ftZakoBoy_OnDeath(HSD_GObj*);
void ftZakoBoy_OnItemPickup(HSD_GObj*, BOOL);
void ftZakoBoy_StoreHeldItem(HSD_GObj*);
void ftZakoBoy_RestoreHeldItem(HSD_GObj*);
void ftZakoBoy_OnItemDrop(HSD_GObj*, BOOL);
void ftZakoBoy_OnLoad(HSD_GObj*);
void func_8014F3FC(HSD_GObj*);

#endif
