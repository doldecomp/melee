#ifndef MELEE_FT_CHARA_FTYOSHI_FTYOSHI1_H
#define MELEE_FT_CHARA_FTYOSHI_FTYOSHI1_H

#include <platform.h>

#include "ft/forward.h"

#include "ft/types.h"

#include "ftCommon/forward.h"
#include "ftYoshi/forward.h"
#include <baselib/forward.h>

/* 12B6E8 */ void ftYs_Init_8012B6E8(Fighter* fp,
                                     struct S_UNK_YOSHI1* unk_struct_arg);
/* 12B804 */ void ftYs_Init_8012B804(Fighter* fp,
                                     struct S_UNK_YOSHI1* unk_struct_arg,
                                     float start_frame);
/* 12B8A4 */ void ftYs_Init_8012B8A4(HSD_GObj* gobj);
/* 12B918 */ void ftYs_Init_8012B918(HSD_GObj* gobj);
/* 12B960 */ void ftYs_Init_OnDeath(HSD_GObj* gobj);
/* 12B99C */ void ftYs_Init_OnLoad(HSD_GObj* gobj);
/* 12BA8C */ void ftYs_Init_8012BA8C(HSD_GObj* gobj);
/* 12BAC0 */ float ftYs_Init_8012BAC0(Fighter* fp);
/* 12BACC */ void ftYs_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 12BBAC */ void ftYs_Init_OnItemInvisible(HSD_GObj* gobj);
/* 12BBF4 */ void ftYs_Init_OnItemVisible(HSD_GObj* gobj);
/* 12BC3C */ void ftYs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
/* 12BC90 */ void ftYs_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 12BCC8 */ void ftYs_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 12BD34 */ void ftYs_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3CE6D0 */ extern MotionState ftYs_Init_MotionStateTable[ftYs_MS_SelfCount];

#endif
