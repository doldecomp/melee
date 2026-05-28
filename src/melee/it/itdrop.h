#ifndef GALE01_ITDROP_H
#define GALE01_ITDROP_H

#include <platform.h>

#include "it/types.h"

/* 26F3AC */ ItemKind it_8026F3AC(void);
/* 26F3D4 */ bool it_8026F3D4(Item_GObj*, struct it_8026F3D4_arg1_t*, s32,
                              s32);
/* 26F53C */ void it_8026F53C(Item_GObj*, Vec3*, bool);
/* 26F5C8 */ Item_GObj* it_8026F5C8(Item_GObj*, ItemKind, Vec3*);
/* 26F6BC */ Item_GObj* it_8026F6BC(Item_GObj*, Vec3*, Vec3*, bool);
/* 26F7C8 */ Item_GObj* it_8026F7C8(Vec3*, Vec3*, bool);
/* 26F8B4 */ bool it_8026F8B4(Item_GObj*, Vec3*, Vec3*, bool);

#endif
