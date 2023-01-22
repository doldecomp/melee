#ifndef _ftzakoboy_h_
#define _ftzakoboy_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct _ftZakoboyAttributes {
    s32 x0;
} ftZakoboyAttributes;

extern char lbl_803D34E8[];
extern char lbl_803D34F4[];

void ftZakoBoy_OnDeath(HSD_GObj*);
void ftZakoBoy_OnItemPickup(HSD_GObj*, bool);
void ftZakoBoy_OnItemInvisible(HSD_GObj*);
void ftZakoBoy_OnItemVisible(HSD_GObj*);
void ftZakoBoy_OnItemDrop(HSD_GObj*, bool);
void ftZakoBoy_OnLoad(HSD_GObj*);
void ftZakoBoy_LoadSpecialAttrs(HSD_GObj*);

#endif
