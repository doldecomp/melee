#ifndef MELEE_IT_ITEM2_H
#define MELEE_IT_ITEM2_H

#include <ctypes.h>
#include <sysdolphin/baselib/gobj.h>

BOOL func_8026B594(HSD_GObj* item_gobj); // Check if item can fire projectiles

// Return item hold kind
s32 func_8026B320(HSD_GObj* item_gobj);

// Identical to 0x8026B54C but likely using a different itAttributes struct
f32 func_8026B560(HSD_GObj* item_gobj);

BOOL func_8026B2B4(HSD_GObj*);
s32 func_8026B30C(HSD_GObj*);
f32 func_8026B54C(HSD_GObj*);
f32 func_8026B574(HSD_GObj*);
s32 func_8026B588();
void func_8026B7F8();

#endif