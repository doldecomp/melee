#ifndef MELEE_FT_INLINES_H
#define MELEE_FT_INLINES_H

#include <platform.h>
#include "ftCommon/forward.h"

#include "ft/ftanim.h"
#include "ft/types.h"
#include "gr/stage.h"
#include "it/item2.h"
#include "lb/lbcollision.h"
#include "lb/lbrefract.h"
#include "pl/player.h"

#include <common_structs.h>
#include <math.h>
#include <dolphin/mtx/types.h>
#include <baselib/archive.h>
#include <baselib/controller.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/random.h>

#define PUSH_ATTRS(fp, attributeName)                                         \
    do {                                                                      \
        void* backup = (fp)->x2D8_specialAttributes2;                         \
        attributeName* src = (attributeName*) (fp)->ft_data->ext_attr;        \
        void** attr = &(fp)->x2D4_specialAttributes;                          \
        *(attributeName*) (fp)->x2D8_specialAttributes2 = *src;               \
        *attr = backup;                                                       \
    } while (0)

#define COPY_ATTRS(gobj, attributeName)                                       \
    Fighter* fp = GET_FIGHTER(gobj);                                          \
    attributeName* sA2 = (attributeName*) fp->x2D4_specialAttributes;         \
    attributeName* ext_attr = (attributeName*) fp->ft_data->ext_attr;         \
    *sA2 = *ext_attr;

#define SCALE_HEIGHT_ATTRS(num_attrs)                                         \
    {                                                                         \
        int i;                                                                \
        for (i = 0; i < num_attrs; i++) {                                     \
            sA2->height_attributes[i] *= fp->x34_scale.y;                     \
        }                                                                     \
    }

#define GET_FIGHTER(gobj) ((Fighter*) HSD_GObjGetUserData(gobj))

/// @deprecated Use #GET_FIGHTER instead.
static inline Fighter* getFighter(HSD_GObj* gobj)
{
    return gobj->user_data;
}

/// @deprecated use #GET_FIGHTER instead.
static inline Fighter* getFighterPlus(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp;
}

static inline void* getFtSpecialAttrs(Fighter* fp)
{
    void* fighter_attr = fp->x2D4_specialAttributes;
    return fighter_attr;
}

static inline void* getFtSpecialAttrsD(Fighter* fp) // Direct
{
    return fp->x2D4_specialAttributes;
}

static inline s32 ftGetKind(Fighter* fp)
{
    return fp->x4_fighterKind;
}

static inline s32 ftGetAction(Fighter* fp)
{
    return fp->motion_id;
}

static inline void* getFtSpecialAttrs2CC(Fighter* fp)
{
    void* fighter_attr = fp->x2CC;
    return fighter_attr;
}

static inline attr* getFtAttrs(Fighter* fp)
{
    return &fp->x110_attr;
}

static inline CollData* getFtColl(Fighter* fp)
{
    return &fp->x6F0_collData;
}

static inline bool ftGetGroundAir(Fighter* fp)
{
    return fp->ground_or_air;
}

static inline f32 stickGetDir(f32 x1, f32 x2)
{
    if (x1 < x2) {
        return -x1;
    } else {
        return x1;
    }
}
/// used for all fighters except Kirby and Purin
static inline void Fighter_OnItemPickup(HSD_GObj* gobj, bool catchItemFlag,
                                        bool bool2, bool bool3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        switch (func_8026B320(fp->x1974_heldItem)) {
        case 1:
            ftAnim_80070FB4(gobj, bool2, 1);
            break;
        case 2:
            ftAnim_80070FB4(gobj, bool2, 0);
            break;
        case 3:
            ftAnim_80070FB4(gobj, bool2, 2);
            break;
        case 4:
            ftAnim_80070FB4(gobj, bool2, 3);
            break;
        }
        if (catchItemFlag) {
            ftAnim_80070C48(gobj, bool3);
        }
    }
}

static inline void Fighter_OnItemInvisible(HSD_GObj* gobj, bool bool)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        ftAnim_80070CC4(gobj, bool);
    }
}

static inline void Fighter_OnItemVisible(HSD_GObj* gobj, bool bool)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        ftAnim_80070C48(gobj, bool);
    }
}

static inline void Fighter_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag,
                                      bool bool2, bool bool3)
{
    ftAnim_80070FB4(gobj, bool2, -1);
    if (dropItemFlag) {
        ftAnim_80070CC4(gobj, bool3);
    }
}

static inline void Fighter_OnKnockbackEnter(HSD_GObj* gobj, s32 arg1)
{
    ftAnim_800704F0(gobj, arg1, 3.0f);
    ftAnim_800704F0(gobj, 0, 3.0f);
}

static inline void Fighter_OnKnockbackExit(HSD_GObj* gobj, s32 arg1)
{
    ftAnim_800704F0(gobj, arg1, 0.0f);
    ftAnim_800704F0(gobj, 0, 0.0f);
}

static inline void Fighter_UnsetCmdVar0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
}

static inline CollData* Fighter_GetCollData(Fighter* fp)
{
    return &fp->x6F0_collData;
}

// Ternary macro for fcmpo-based facing direction check

#define CLIFFCATCH_O(fp)                                                      \
    ((fp)->facing_dir < 0.0f) ? CLIFFCATCH_LEFT : CLIFFCATCH_RIGHT

// Ternary macro for fcmpu-based facing direction check

#define CLIFFCATCH_U(fp)                                                      \
    ((fp)->facing_dir != 1.0f) ? CLIFFCATCH_LEFT : CLIFFCATCH_RIGHT

#endif
