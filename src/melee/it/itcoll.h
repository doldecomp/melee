#ifndef _itcoll_h_
#define _itcoll_h_

#include <platform.h>

#include "it/item.h"

/* 26F9AC */ void it_8026F9AC(s32, void*, HitCapsule*, HurtCapsule*);
/* 26FA2C */ void it_8026FA2C(Item*, HitCapsule*, s32, Item*, bool);
/* 26FAC4 */ void it_8026FAC4(Item*, HitCapsule*, s32, void*, bool);
/* 26FC00 */ void it_8026FC00(Item*, HitCapsule*, s32, Fighter*);
/* 26FCF8 */ void it_8026FCF8(Item*, HitCapsule*);
/* 26FE68 */ void it_8026FE68(Item*, HitCapsule*, Item*, HitCapsule*);
/* 2701BC */ void it_802701BC(Item_GObj*);
/* 2703E8 */ void it_802703E8(Item_GObj*);
/* 2706D0 */ void it_802706D0(Item_GObj*);
/* 270CD8 */ f32 it_80270CD8(Item*, HitCapsule*);
/* 270E30 */ void it_80270E30(Item_GObj*);
/* 27129C */ void it_8027129C(Item_GObj*, s32);
/* 27137C */ void it_8027137C(Item_GObj*);
/* 27146C */ void it_8027146C(Item_GObj*);
/* 2714C0 */ void it_802714C0(Item_GObj*);
/* 271508 */ void it_80271508(Item_GObj*, HurtCapsuleState);
/* 271534 */ void it_80271534(Item_GObj*, s32, HurtCapsule*);
/* 271590 */ void it_80271590(Item_GObj*, s32, HurtCapsule*);
/* 27163C */ void it_8027163C(Item_GObj*);
/* 271A58 */ void it_80271A58(Item_GObj*);
/* 2721B8 */ void it_802721B8(Item_GObj*);
/* 272280 */ void it_80272280(Item_GObj*);
/* 272298 */ void it_80272298(Item_GObj*);
/* 2722B0 */ void it_802722B0(Item_GObj*);
/* 272304 */ void it_80272304(Item_GObj*);
/* 27236C */ HSD_GObj* it_8027236C(Item_GObj*);
/* 2723FC */ HSD_GObj* it_802723FC(Item_GObj*);
/* 272460 */ void it_80272460(HitCapsule*, u32, Item_GObj*);

#endif
