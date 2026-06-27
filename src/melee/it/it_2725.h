#ifndef GALE01_IT_2725
#define GALE01_IT_2725

#include <platform.h>

#include "ft/forward.h"
#include "it/forward.h"

#include "it/itCharItems.h"
#include "it/items/types.h"
#include "it/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

struct lb_80014638_arg1_t;

/* 272560 */ void it_80272560(Item_GObj*, s32);
/* 2725D4 */ void it_802725D4(Item_GObj*);
/* 272674 */ void it_80272674(Item_GObj*, s32);
/* 272784 */ void it_80272784(Item_GObj*);
/* 272818 */ Fighter* it_80272818(Item*);
/* 272828 */ Item_GObj* it_80272828(ItemKind);
/* 272860 */ void it_80272860(Item_GObj*, f32, f32);
/* 2728C8 */ void it_802728C8(Item_GObj*);
/* 272940 */ void it_80272940(Item_GObj*);
/* 272980 */ void it_80272980(Item_GObj*);
/* 272A18 */ void it_80272A18(HSD_JObj* item_jobj);
/* 272A3C */ void it_80272A3C(HSD_JObj* item_jobj);
/* 272A60 */ void it_80272A60(Item_GObj*);
/* 272AC4 */ void it_80272AC4(Item_GObj*, Vec3*);
/* 272B40 */ void it_80272B40(Item_GObj*);
/* 272BA4 */ void it_80272BA4(Item_GObj*);
/* 272C08 */ void it_80272C08(Item_GObj*);
/* 272C6C */ bool it_80272C6C(Item_GObj*);
/* 272C90 */ HSD_JObj* it_80272C90(Item_GObj*);
/* 272CC0 */ HSD_JObj* it_80272CC0(Item_GObj*, enum_t);
/* 272D1C */ bool it_80272D1C(Item_GObj*);
/* 272D40 */ s32 it_80272D40(Item_GObj*);
/* 272DB0 */ void itColl_BounceOffVictim(Item_GObj*);
/* 272DE4 */ void it_80272DE4(HSD_JObj*, f32);
/* 272F7C */ void it_80272F7C(HSD_JObj*, f32);
/* 273030 */ bool it_80273030(Item_GObj*);
/* 273078 */ bool itColl_BounceOffShield(Item_GObj*);
/* 273130 */ bool it_80273130(Item_GObj*);
/* 273168 */ void it_80273168(Item_GObj*);
/* 2731A4 */ void it_802731A4(Item_GObj*);
/* 2731E0 */ void it_802731E0(Item_GObj*);
/* 27321C */ void it_8027321C(Item_GObj*);
/* 27327C */ void it_8027327C(Item_GObj*, enum_t ID1, enum_t ID2);
/* 2732E4 */ void it_802732E4(Item*, s32);
/* 273318 */ void it_80273318(Item_GObj*, HSD_Joint*);
/* 273408 */ void it_80273408(Item_GObj*);
/* 273454 */ void it_80273454(Item_GObj*);
/* 27346C */ void it_8027346C(Item_GObj*);
/* 273484 */ void it_80273484(Item_GObj*);
/* 27349C */ void it_8027349C(Item_GObj*);
/* 2734B4 */ void it_802734B4(Item_GObj*);
/* 273500 */ void it_80273500(Item_GObj*, Vec3*);
/* 273598 */ void it_80273598(Item_GObj*, s32, s32);
/* 273600 */ void it_80273600(Item_GObj*);
/* 273648 */ void it_80273648(Item_GObj*, s32, s32);
/* 273670 */ void it_80273670(Item_GObj*, int, float);
/* 273748 */ void it_80273748(Item_GObj*, Vec3*, Vec3*);
/* 273B50 */ void it_80273B50(Item_GObj*, Vec3*);
/* 273F34 */ void it_80273F34(Item_GObj*, HSD_GObj*);
/* 274198 */ void it_80274198(Item_GObj*, bool);
/* 2741F4 */ void it_802741F4(Item_GObj*, bool);
/* 274250 */ void it_80274250(Item_GObj*, Vec3*);
/* 27429C */ void it_8027429C(Item_GObj*, Vec3*);
/* 2742F4 */ void it_802742F4(Item_GObj*, HSD_GObj*, Fighter_Part);
/* 274484 */ void it_80274484(Item_GObj*, HSD_JObj*, f32);
/* 274574 */ void it_80274574(Item_GObj*);
/* 274594 */ void it_80274594(Item_GObj*);
/* 274658 */ int it_80274658(Item_GObj*, f32);
/* 2746F8 */ HSD_JObj* it_802746F8(Item_GObj*);
/* 274740 */ void it_80274740(Item_GObj*);
/* 274990 */ f32 it_80274990(Item_GObj*);
/* 274A64 */ void it_80274A64(Item_GObj*);
/* 274C60 */ void it_80274C60(Item_GObj*);
/* 274C78 */ bool it_80274C78(Item_GObj*);
/* 274C88 */ void it_80274C88(Item_GObj*);
/* 274CAC */ void it_80274CAC(Item_GObj*);
/* 274D04 */ void it_80274D04(Item_GObj*, struct lb_80014638_arg1_t*);
/* 274D6C */ void it_80274D6C(Item_GObj*);
/* 274DAC */ void it_80274DAC(Item_GObj*);
/* 274DFC */ void it_80274DFC(Item_GObj*);
/* 274E44 */ void it_80274E44(Item_GObj*);
/* 274ECC */ void it_80274ECC(Item_GObj*, bool);
/* 274ED8 */ void it_80274ED8(void);
/* 274EE8 */ void it_80274EE8(void);
/* 274EF8 */ void it_80274EF8(Item_GObj*);
/* 274F10 */ void it_80274F10(Item_GObj*);
/* 274F28 */ void it_80274F28(Item*, s8, HSD_GObjEvent, HSD_GObjInteraction);
/* 274F48 */ void it_80274F48(Item_GObj*, s32, HSD_GObj*, Fighter_Part);
/* 274FDC */ void it_80274FDC(Item_GObj*, s32, Fighter_GObj*, Fighter_Part);
/* 275070 */ void it_80275070(Item_GObj*, s32);
/* 2750E8 */ bool it_802750E8(Item_GObj*, s32);
/* 2750F8 */ void it_802750F8(Item_GObj*);
/* 275158 */ void it_80275158(Item_GObj*, f32);
/* 275174 */ void it_80275174(Item_GObj*, f32);
/* 27518C */ void it_8027518C(Item_GObj*);
/* 2751D8 */ bool it_802751D8(Item_GObj*);
/* 275210 */ void it_80275210(Item_GObj*);
/* 275228 */ void it_80275228(Item_GObj*);
/* 275240 */ void it_80275240(Item_GObj*);
/* 275258 */ void it_80275258(Item_GObj*);
/* 275270 */ void it_80275270(Item_GObj*);
/* 275288 */ void it_80275288(Item_GObj*, s32, s32);
/* 2752D8 */ void it_802752D8(Item_GObj*, s32, s32);
/* 275328 */ void it_80275328(HSD_GObj*, ItemLink*);
/* 275390 */ void it_80275390(Item_GObj*);
/* 2753BC */ void it_802753BC(Item_GObj*, s16);
#endif
