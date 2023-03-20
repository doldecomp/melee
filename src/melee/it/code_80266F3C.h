/// @file
/// @attention Symbols in this file are placed correctly.
#ifndef MELEE_IT_CODE_80266F3C_H
#define MELEE_IT_CODE_80266F3C_H

#include <placeholder.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <melee/it/types.h>

extern HSD_ObjAllocUnk4 lbl_804A0E30;
extern HSD_ObjAllocUnk5 lbl_804A0E50;
extern HSD_ObjAllocUnk6 lbl_804A0E60;
extern ItemCommonData* lbl_804D6D28;
extern s8 lbl_804D6D00;
extern s32 lbl_804D6D08;
extern s32 lbl_804D6D0C;
extern u32 lbl_804D6D10;

/// @todo Probably #size_t but that needs to be changed to
///       <tt>unsigned int</tt> first.
extern uint lbl_804D6D14;

extern ItemCommonData* lbl_804D6D28;
extern CommonItemArticles* lbl_804D6D24;

void func_8027B4A4(HSD_GObj*, u32);
void* func_8027B5B0(s32, s32, HSD_JObj*, s32, s32);
void func_80274EE8(u32);

/// Load ItCo.dat/usd
void func_8027870C(s32);

bool func_8026D324(bool);
s32 func_8026D604(HSD_GObj* item_gobj);
void func_8026F9A0(void);
void func_802701BC(HSD_GObj* item_gobj);
void func_802703E8(HSD_GObj* item_gobj);

void func_802706D0(HSD_GObj* item_gobj);
void func_80270E30(HSD_GObj* item_gobj);
void func_8027137C(HSD_GObj* item_gobj);
void func_8027146C(HSD_GObj* item_gobj);
void func_802714C0(HSD_GObj* item_gobj);
void func_80271508(HSD_GObj* item_gobj, s32 arg1);
void func_8027163C(HSD_GObj* item_gobj);
void func_80271A58(HSD_GObj* item_gobj);
void func_802721B8(HSD_GObj* item_gobj);
void func_80272280(HSD_GObj* item_gobj);
void func_8027163C(HSD_GObj* item_gobj);
void func_80271A58(HSD_GObj* item_gobj);
void func_802721B8(HSD_GObj* item_gobj);
void func_80272298(HSD_GObj* item_gobj);
void func_802722B0(HSD_GObj* item_gobj);
void func_80272304(HSD_GObj* item_gobj);
void func_80272460(itHit* hitbox, s32 damage, HSD_GObj* item_gobj);
void func_802725D4(HSD_GObj*);
void func_80272784(HSD_GObj* item_gobj);
void func_802728C8(HSD_GObj* item_gobj);
void func_80272A18(HSD_JObj* item_jobj);
void func_80272A3C(HSD_JObj* item_jobj);

/// Check if GObj is Item class
bool func_80272D1C(HSD_GObj* item_gobj);

/// Check GObj entity class
s32 func_80272D40(HSD_GObj* item_gobj);

void func_80272F7C(HSD_JObj*, f32);
void func_802728C8(HSD_GObj* item_gobj);
void func_80273168(HSD_GObj* item_gobj);
void func_802731A4(HSD_GObj*);
void func_802731E0(HSD_GObj*);
void func_8027327C(HSD_GObj* item_gobj, s32 ID1, s32 ID2);
void func_8027346C(HSD_GObj* item_gobj);
void func_80273484(HSD_GObj* item_gobj);
void func_80272F7C(HSD_JObj*, f32);
void func_802728C8(HSD_GObj* item_gobj);
void func_80273168(HSD_GObj* item_gobj);
void func_802731A4(HSD_GObj*);
void func_802731E0(HSD_GObj*);
void func_8027327C(HSD_GObj* item_gobj, s32 ID1, s32 ID2);
void func_8027346C(HSD_GObj* item_gobj);
void func_80273484(HSD_GObj* item_gobj);
void func_80273500(HSD_GObj*, Vec3*);
void func_80273748(HSD_GObj*, s32, s32);

void func_80273B50(HSD_GObj*, Vec3*);
void func_80274198(HSD_GObj*, s32);
void func_802741F4(HSD_GObj*, s32);
void func_8027429C(HSD_GObj*, Vec3*);
void func_802742F4(HSD_GObj*, HSD_GObj*, u8);
void func_80274658(HSD_GObj*, f32);
void func_80274740(HSD_GObj* item_gobj);
void func_80274A64(HSD_GObj* item_gobj);
bool func_80274C78(HSD_GObj* item_gobj);
void func_80274DAC(HSD_GObj*);
void func_8027737C(HSD_GObj* item_gobj, Vec3* pos);

/// Toggle flag in 0xDC8 off
void func_80274EF8(HSD_GObj* item_gobj);

void func_80274F10(HSD_GObj* item_gobj);

/// Set item lifetime
void func_80275158(HSD_GObj* item_gobj, f32 lifetime);

void func_80275390(HSD_GObj*);
void func_802753BC(HSD_GObj*, s16);
void func_802753DC(HSD_GObj*);
void func_80274740(HSD_GObj* item_gobj);
void func_80274A64(HSD_GObj* item_gobj);

/// Toggle several flags in 0xDCD off
void func_80275474(HSD_GObj* item_gobj);

void func_802754D4(HSD_GObj*);

/// Toggle several flags in 0xDCE off
void func_80275504(HSD_GObj* item_gobj);

void func_802756D0(HSD_GObj* item_gobj);
void func_802756E0(HSD_GObj* item_gobj);
void func_8027574C(HSD_GObj* item_gobj);
void func_80275870(HSD_GObj* item_gobj);
void func_80275E98(HSD_GObj*, SpawnItem*);
void func_802762B0(Item*);
void func_802762BC(Item*);

/// Advance Item Script
void func_802799E4(HSD_GObj* item_gobj);

void func_80279B64(Item*);

void func_80279B88(Item* item_data, s32 arg1, s32 arg2);
void func_80279BBC(Item* item_data);
void func_80279BE0(HSD_GObj* item_gobj);
void func_8027B0C4(HSD_GObj*, SpawnItem*);
UNK_RET func_8026FAC4(UNK_PARAMS);
UNK_RET func_80077688(UNK_PARAMS);
UNK_RET func_8026FC00(UNK_PARAMS);
UNK_RET func_80272818(UNK_PARAMS);

#endif
