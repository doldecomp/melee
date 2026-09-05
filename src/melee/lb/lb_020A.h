/**
 * @file lb_020A.h
 * @brief Skeletal transform and two-joint IK utilities.
 */

#ifndef GALE01_020AEC
#define GALE01_020AEC

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <Runtime/platform.h>

/* 020AEC */ void fn_80020AEC(HSD_JObj*, Mtx);
/* 020E38 */ void lbBgFlash_80020E38(HSD_JObj*, Vec3*, f32, f32, f32);
/* 02113C */ void fn_8002113C(HSD_JObj*, Vec3*, f32);
/* 021410 */ void lbBgFlash_80021410(IKState*);

#endif
