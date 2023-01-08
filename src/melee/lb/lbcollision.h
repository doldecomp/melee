#ifndef MELEE_LB_LBCOLLISION_H
#define MELEE_LB_LBCOLLISION_H

#include <dolphin/types.h>

/// @todo Does not belong here.
typedef struct _Hitbox {
    s32 x0;
    s32 x4;
    s32 x8;
    f32 xC;
    /// @remarks @c f32 needed for 'manual' mods to hitbox damage.
    u8 filler[0x128];
} Hitbox;

void* HSD_JObjUnkMtxPtr(struct _HSD_JObj*);
s32 func_80008248(s32, struct ftHurt*, void*, f32, f32, f32);
void func_80008440(struct _Hitbox*);
void func_80008434(struct _Hitbox*);

#endif
