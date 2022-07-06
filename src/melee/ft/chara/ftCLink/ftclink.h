#ifndef _ftclink_h_
#define _ftclink_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

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

void ftCLink_OnItemPickup(HSD_GObj*, BOOL);
void ftCLink_OnItemDrop(HSD_GObj*, BOOL);

inline void checkFighter2244(HSD_GObj* gobj)
{
    Fighter* ft;

    if (gobj == NULL) {
        return;
    }

    ft = gobj->user_data;
    if (ft != NULL && ft->sa.clink.x2244 != 0) {
        func_802C8C34(ft->sa.clink.x2244);
        ft->sa.clink.x2244 = 0;
    }

    if (gobj == NULL) {
        gobj == NULL;
    }
}

#endif
