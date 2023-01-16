#ifndef MELEE_FT_CHARA_FTCLINK_FTCLINK_H
#define MELEE_FT_CHARA_FTCLINK_FTCLINK_H

#include <melee/ft/fighter.h>
#include <melee/it/code_8027CF30.h>
#include <sysdolphin/baselib/gobj.h>

/// @todo this is #ftLinkAttributes.
typedef struct _CLinkAttributes {
    s32 x0_pad[(0xC - 0x0) / 4];
    s32 xC;
    s32 x10;
    s32 x14_pad[(0x2C - 0x14) / 4];
    s32 x2C;
    s32 x30_pad[(0x48 - 0x30) / 4];
    s32 x48;
    s32 x4C;
    s32 x50;
    f32 x54;
    s32 x58_pad[(0xBC - 0x58) / 4];
    s32 xBC;
    s32 xC0;
    f32 xC4;
    s32 xC8_pad[(0xD8 - 0xC8) / 4];
    f32 xD8;
} CLinkAttributes;

void ftCLink_OnItemPickup(HSD_GObj*, bool);
void ftCLink_OnItemDrop(HSD_GObj*, bool);
void func_80149268(HSD_GObj*);
void ftCLink_OnKnockbackExit(HSD_GObj* gobj);
void func_80149114(HSD_GObj* gobj);
void func_8014919C(HSD_GObj* gobj);
void ftCLink_OnDeath(HSD_GObj* gobj);
bool func_8014920C(HSD_GObj* gobj);
void func_801492C4(HSD_GObj* gobj);
u32 func_801492F4(HSD_GObj* gobj);
void func_80149318(HSD_GObj* gobj);
void ftCLink_OnLoad(HSD_GObj* gobj);
void ftCLink_OnItemPickupExt(HSD_GObj* gobj, s32 arg1);
void ftCLink_OnItemInvisible(HSD_GObj* gobj);
void ftCLink_OnItemVisible(HSD_GObj* gobj);
void ftCLink_OnItemDropExt(HSD_GObj* gobj, s32 arg1);
void ftCLink_LoadSpecialAttrs(HSD_GObj* gobj);
void ftCLink_OnKnockbackEnter(HSD_GObj* gobj);

static inline void checkFighter2244(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL)
        return;

    fp = gobj->user_data;
    if (fp != NULL && fp->sa.clink.x2244 != 0) {
        func_802C8C34(fp->sa.clink.x2244);
        fp->sa.clink.x2244 = 0;
    }

    if (gobj == NULL)
        gobj == NULL;
}

#endif
