#ifndef GALE01_ITGROUNDCOLL_H
#define GALE01_ITGROUNDCOLL_H

#include <platform.h>

#include "it/types.h"

#include <baselib/forward.h>
#include <dolphin/mtx.h>

/* 26D564 */ bool it_8026D564(Item_GObj*);
/* 26D5CC */ bool it_8026D5CC(Item_GObj*);
/* 26D604 */ bool it_8026D604(Item_GObj*);
/* 26D62C */ void it_8026D62C(Item_GObj*, HSD_GObjEvent);
/* 26D6F4 */ void it_8026D6F4(Item_GObj*, HSD_GObjEvent);
/* 26D78C */ void it_8026D78C(Item_GObj*, HSD_GObjEvent);
/* 26D82C */ void it_8026D82C(Item_GObj*);
/* 26D8A4 */ bool it_8026D8A4(Item_GObj*, HSD_GObjEvent);
/* 26D938 */ void it_8026D938(Item_GObj*, HSD_GObjEvent);
/* 26D9A0 */ bool it_8026D9A0(Item_GObj*);
/* 26DA08 */ bool it_8026DA08(Item_GObj*);
/* 26DA70 */ bool it_8026DA70(Item_GObj*);
/* 26DAA8 */ s32 it_8026DAA8(Item_GObj*);
/* 26DB40 */ bool it_8026DB40(Item_GObj*);
/* 26DBC8 */ bool it_8026DBC8(Item_GObj*);
/* 26DC24 */ bool it_8026DC24(Item_GObj*);
/* 26DD5C */ bool it_8026DD5C(Item_GObj*);
/* 26DDFC */ bool it_8026DDFC(Item_GObj*);
/* 26DE98 */ bool it_8026DE98(Item_GObj*);
/* 26DF34 */ bool it_8026DF34(Item_GObj*);
/* 26DFB0 */ bool it_8026DFB0(Item_GObj*);
/* 26E058 */ bool it_8026E058(Item_GObj*);
/* 26E0F4 */ void it_8026E0F4(Item_GObj*);
/* 26E15C */ void it_8026E15C(Item_GObj*, HSD_GObjEvent);
/* 26E248 */ void it_8026E248(Item_GObj*, HSD_GObjEvent);
/* 26E32C */ s32 it_8026E32C(Item_GObj*, HSD_GObjEvent);
/* 26E414 */ void it_8026E414(Item_GObj*, HSD_GObjEvent);
/* 26E4D0 */ void it_8026E4D0(Item_GObj*, HSD_GObjEvent);
/* 26E5A0 */ void it_8026E5A0(Item_GObj*, HSD_GObjEvent);
/* 26E664 */ void it_8026E664(Item_GObj*, HSD_GObjEvent);
/* 26E71C */ void it_8026E71C(Item_GObj*, HSD_GObjEvent);
/* 26E7E0 */ void it_8026E7E0(Item_GObj*, HSD_GObjEvent);
/* 26E8C4 */ void it_8026E8C4(Item_GObj*, HSD_GObjEvent, HSD_GObjEvent);
/* 26E9A4 */ bool it_8026E9A4(HSD_GObj*, Vec3*, Vec3*, Vec3*);
/* 26EA20 */ bool it_8026EA20(HSD_GObj*, Vec3*, Vec3*, Vec3*, int*,
                              u32* flags_out);
/* 26EA9C */ bool it_8026EA9C(HSD_GObj*, Vec3*, Vec3*, Vec3*, int*,
                              u32* flags_out, s32);

bool it_8026E15C_inline1(Item_GObj* gobj);
bool it_8026E15C_inline2(Item_GObj* gobj);
bool it_8026E248_inline(Item_GObj* gobj);
bool it_8026E32C_inline(Item_GObj* gobj);

#endif
