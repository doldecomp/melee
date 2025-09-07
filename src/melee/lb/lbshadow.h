#ifndef MELEE_LB_SHADOW_H
#define MELEE_LB_SHADOW_H

#include <placeholder.h>
#include <platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 00E9F0 */ void lbShadow_8000E9F0(Vec3*, s32, f32);
/* 00ED54 */ void lbShadow_8000ED54(LbShadow*, HSD_JObj*);
/* 00EE8C */ void lbShadow_8000EE8C(LbShadow*);
/* 00EEE0 */ void lbShadow_8000EEE0(HSD_GObj*);
/* 00EFEC */ void lbShadow_8000EFEC(void);
/* 00F214 */ void lbShadow_8000F214(HSD_Shadow*);
/* 00F38C */ void lbShadow_8000F38C(s32);

#endif
