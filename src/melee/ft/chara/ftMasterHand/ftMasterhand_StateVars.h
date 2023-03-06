#ifndef FTMASTERHAND_STATEVARS_H
#define FTMASTERHAND_STATEVARS_H

#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftMasterhandStateVars {
    f32 x2340_unk;
    void (*x2344_callback)(HSD_GObj*);
    int x2348;
    Vec3 x234C_pos;
    f32 x2358;
    f32 x235C;
    int x2360;
    f32 x2364;
    int x2368;
    int x236C;
    int x2370;
    int x2374;
    int x2378;
    int x237C;
    int x2380;
} ftMasterhandStateVars;

#endif
