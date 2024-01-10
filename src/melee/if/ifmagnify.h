#ifndef MELEE_IF_IFMAGNIFY_H
#define MELEE_IF_IFMAGNIFY_H

#include <platform.h>

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/tobj.h>

typedef struct ifMagnify { // base: 0x804A1DE0
    HSD_Joint* joint; // // ifMagnify_802fc3c0 accesses 0x804A1DE0 for a Joint
    int x4;
    int x8;
    int xC;
    int x10;

    struct {
        HSD_GObj* gobj; // ifMagnify_802fc750 accesses 0x804A1DF4 + slot * 0x10
                        // for a GObj
        HSD_TObj* tobj; // ifMagnify_802fc3c0 accesses 0x804A1DF8 + slot * 0x10
                        // for a TObj
        HSD_ImageDesc*
            idesc; // ifMagnify_802FBBDC access 0x804A1DFC for an ImageDesc
        struct {
            u8 is_offscreen : 1;
            u8 ignore_offscreen : 1;
            u8 unk : 6;
        } state;
    } player[6];
} ifMagnify;

s32 ifMagnify_802FB6E8(s32);
bool ifMagnify_802FC998(s32 ply_slot);

#endif
