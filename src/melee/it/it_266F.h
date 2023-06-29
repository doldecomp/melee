/// @file
/// @attention Symbols in this file are placed correctly.
#ifndef MELEE_IT_CODE_80266F3C_H
#define MELEE_IT_CODE_80266F3C_H

#include "it/types.h"

#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

extern HSD_ObjAllocUnk4 it_804A0E30;
extern HSD_ObjAllocUnk5 it_804A0E50;
extern HSD_ObjAllocUnk6 it_804A0E60;
extern ItemCommonData* it_804D6D28;
extern s8 it_804D6D00;
extern s32 it_804D6D08;
extern s32 it_804D6D0C;
extern u32 it_804D6D10;

/// @todo Probably #size_t but that needs to be changed to
///       <tt>unsigned int</tt> first.
extern uint it_804D6D14;

extern CommonItemArticles* it_804D6D24;

void it_8027B4A4(HSD_GObj*, u32);
void* it_8027B5B0(s32, s32, HSD_JObj*, s32, s32);
void it_80274EE8(u32);

/// Load ItCo.dat/usd
void it_8027870C(s32);

bool it_8026D324(bool);
s32 it_8026D604(HSD_GObj* gobj);
void it_8026F9A0(void);
void it_802701BC(HSD_GObj* gobj);
void it_802703E8(HSD_GObj* gobj);

void it_802706D0(HSD_GObj* gobj);
void it_80270E30(HSD_GObj* gobj);
void it_8027137C(HSD_GObj* gobj);
void it_8027146C(HSD_GObj* gobj);
void it_802714C0(HSD_GObj* gobj);
void it_80271508(HSD_GObj* gobj, s32 arg1);
void it_8027163C(HSD_GObj* gobj);
void it_80271A58(HSD_GObj* gobj);
void it_802721B8(HSD_GObj* gobj);
void it_80272280(HSD_GObj* gobj);
void it_80272298(HSD_GObj* gobj);
void it_802722B0(HSD_GObj* gobj);
void it_80272304(HSD_GObj* gobj);
void it_80272460(itHit* hitbox, s32 damage, HSD_GObj* gobj);
void it_802725D4(HSD_GObj*);
void it_80272784(HSD_GObj* gobj);
void it_80272A18(HSD_JObj* item_jobj);
void it_80272A3C(HSD_JObj* item_jobj);

/// Check if GObj is Item class
bool it_80272D1C(HSD_GObj* gobj);

/// Check GObj entity class
s32 it_80272D40(HSD_GObj* gobj);

void it_802728C8(HSD_GObj* gobj);
void it_80272F7C(HSD_JObj*, f32);
void it_80273168(HSD_GObj* gobj);
void it_802731A4(HSD_GObj*);
void it_802731E0(HSD_GObj*);
void it_8027327C(HSD_GObj* gobj, s32 ID1, s32 ID2);
void it_8027346C(HSD_GObj* gobj);
void it_80273484(HSD_GObj* gobj);
void it_80273500(HSD_GObj*, Vec3*);
void it_80273748(HSD_GObj*, Vec3*, Vec3*);

void it_80273B50(HSD_GObj*, Vec3*);
void it_80274198(HSD_GObj*, s32);
void it_802741F4(HSD_GObj*, s32);
void it_8027429C(HSD_GObj*, Vec3*);
void it_802742F4(HSD_GObj*, HSD_GObj*, u8);
void it_80274658(HSD_GObj*, f32);
void it_80274740(HSD_GObj* gobj);
void it_80274A64(HSD_GObj* gobj);
bool it_80274C78(HSD_GObj* gobj);
void it_80274DAC(HSD_GObj*);
void it_8027737C(HSD_GObj* gobj, Vec3* pos);

/// Toggle flag in 0xDC8 off
void it_80274EF8(HSD_GObj* gobj);

void it_80274F10(HSD_GObj* gobj);

/// Set item lifetime
void it_80275158(HSD_GObj* gobj, f32 lifetime);

void it_80275390(HSD_GObj*);
void it_802753BC(HSD_GObj*, s16);
void it_802753DC(HSD_GObj*);

/// Toggle several flags in 0xDCD off
void it_80275474(HSD_GObj* gobj);

void it_802754D4(HSD_GObj*);

/// Toggle several flags in 0xDCE off
void it_80275504(HSD_GObj* gobj);

void it_802756D0(HSD_GObj* gobj);
void it_802756E0(HSD_GObj* gobj);
void it_8027574C(HSD_GObj* gobj);
void it_80275870(HSD_GObj* gobj);
void it_80275E98(HSD_GObj*, SpawnItem*);
void it_802762B0(Item*);
void it_802762BC(Item*);

/// Advance Item Script
void it_802799E4(HSD_GObj* gobj);

void it_80279B64(Item*);

void it_80279B88(Item* item_data, s32 arg1, s32 arg2);
void it_80279BBC(Item* item_data);
void it_80279BE0(HSD_GObj* gobj);
void it_8027B0C4(HSD_GObj*, SpawnItem*);
UNK_RET it_8026FAC4(UNK_PARAMS);
UNK_RET ftColl_80077688(UNK_PARAMS);
UNK_RET it_8026FC00(UNK_PARAMS);
UNK_RET it_80272818(UNK_PARAMS);
HSD_JObj* it_80272C90(Item_GObj* gobj);

bool it_8026E9A4(Item_GObj*, Vec3*, Vec3*, int);
bool it_80273130(Item_GObj*);
void it_802750F8(Item_GObj*);
void it_80274594(Item_GObj*);
void it_8026EECC(Item_GObj*, int);
bool it_8026DA08(Item_GObj*);
bool it_80276308(Item_GObj*);
bool it_802763E0(Item_GObj*);
void it_80272860(Item_GObj*, f32, f32);

#endif
