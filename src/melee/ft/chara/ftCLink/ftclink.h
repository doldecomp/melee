#ifndef _ftclink_h_
#define _ftclink_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

void func_8014919C(HSD_GObj* fighter_gobj);

void ftCLink_OnItemPickup(HSD_GObj*, BOOL);
void ftCLink_OnItemDrop(HSD_GObj*, BOOL);

inline void checkFighter2244(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL) {
        return;
    }

    fp = gobj->user_data;
    if (fp != NULL && fp->sa.clink.x2244 != 0) {
        func_802C8C34(fp->sa.clink.x2244);
        fp->sa.clink.x2244 = 0;
    }

    if (gobj == NULL) {
        gobj == NULL;
    }
}

#endif
