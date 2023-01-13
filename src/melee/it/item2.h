#ifndef MELEE_IT_ITEM2_H
#define MELEE_IT_ITEM2_H

#include <sysdolphin/baselib/gobj.h>

/// Transfer item on character swap - used for Zelda <-> Sheik
void func_8026B9A8(HSD_GObj* item_gobj, HSD_GObj* arg1, u8 arg2);

bool func_8026B2B4(struct _HSD_GObj*);
s32 itGetKind(struct _HSD_GObj*);
s32 func_8026B30C(struct _HSD_GObj*);

/// Return item hold kind
s32 func_8026B320(struct _HSD_GObj*);

void func_8026B3F8(struct _Article*, s32);
f32 func_8026B54C(struct _HSD_GObj*);
f32 func_8026B560(struct _HSD_GObj*);
f32 func_8026B574(struct _HSD_GObj*);
s32 func_8026B588();
bool func_8026B594(struct _HSD_GObj*);
void func_8026B7F8();

#endif
