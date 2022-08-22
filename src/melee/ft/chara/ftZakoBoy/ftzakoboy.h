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
void ftZakoBoy_OnItemInvisible(HSD_GObj*);
void ftZakoBoy_OnItemVisible(HSD_GObj*);
void ftZakoBoy_OnItemDrop(HSD_GObj*, BOOL);
void ftZakoBoy_OnLoad(HSD_GObj*);
void ftZakoBoy_LoadSpecialAttrs(HSD_GObj*);

#endif
