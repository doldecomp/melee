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
void func_8014F2F8(HSD_GObj*);
void func_8014F340(HSD_GObj*);
void func_8014F388(HSD_GObj*, s32);
void ftZakoBoy_OnLoad(HSD_GObj*);
void func_8014F3FC(HSD_GObj*);

#endif
