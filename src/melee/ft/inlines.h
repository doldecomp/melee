#ifndef MELEE_FT_INLINES_H
#define MELEE_FT_INLINES_H

#include <platform.h>

#include "ft/forward.h"

#include "ft/ftanim.h"
#include "ft/types.h"
#include "it/it_26B1.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
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
        void* backup = (fp)->dat_attrs_backup;                                \
        attributeName* src = (attributeName*) (fp)->ft_data->ext_attr;        \
        void** da = &(fp)->dat_attrs;                                         \
        *(attributeName*) (fp)->dat_attrs_backup = *src;                      \
        *da = backup;                                                         \
    } while (0)

/// @todo Remove declarations. Doesn't really need to be a macro.
#define COPY_ATTRS(gobj, attributeName)                                       \
    Fighter* fp = GET_FIGHTER(gobj);                                          \
    attributeName* sA2 = (attributeName*) fp->dat_attrs;                      \
    attributeName* ext_attr = (attributeName*) fp->ft_data->ext_attr;         \
    *sA2 = *ext_attr;

#ifdef M2CTX
#define GET_FIGHTER(gobj) ((Fighter*) HSD_GObjGetUserData((HSD_GObj*) gobj))
#else
#define GET_FIGHTER(gobj) ((Fighter*) HSD_GObjGetUserData(gobj))
#endif

/// @deprecated Use #GET_FIGHTER instead.
static inline Fighter* getFighter(Fighter_GObj* gobj)
{
    return gobj->user_data;
}

/// @deprecated use #GET_FIGHTER instead.
static inline Fighter* getFighterPlus(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp;
}

static inline void* getFtSpecialAttrs(Fighter* fp)
{
    void* fighter_attr = fp->dat_attrs;
    return fighter_attr;
}

static inline void* getFtSpecialAttrsD(Fighter* fp) // Direct
{
    return fp->dat_attrs;
}

static inline s32 ftGetKind(Fighter* fp)
{
    return fp->kind;
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

static inline ftCo_DatAttrs* getFtAttrs(Fighter* fp)
{
    return &fp->co_attrs;
}

static inline CollData* getFtColl(Fighter* fp)
{
    return &fp->coll_data;
}

static inline Fighter_GObj* getFtVictim(Fighter* fp)
{
    return fp->victim_gobj;
}

static inline HSD_GObj* getFtTargetItem(Fighter* fp)
{
    return fp->target_item_gobj;
}

static inline bool ftGetGroundAir(Fighter* fp)
{
    return fp->ground_or_air;
}

static inline float stickGetDir(float x1, float x2)
{
    if (x1 < x2) {
        return -x1;
    } else {
        return x1;
    }
}

static inline void getAccelAndTarget(Fighter* fp, float* accel,
                                     float* target_vel)
{
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    *accel = fp->input.lstick.x * fp->co_attrs.dash_run_acceleration_a;
    *accel += fp->input.lstick.x > 0 ? +co_attrs->dash_run_acceleration_b
                                     : -co_attrs->dash_run_acceleration_b;
    *target_vel = fp->input.lstick.x * co_attrs->dash_run_terminal_velocity;
}

/// used for all fighters except Kirby and Purin
static inline void Fighter_OnItemPickup(Fighter_GObj* gobj, bool catchItemFlag,
                                        bool bool2, bool bool3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!it_8026B2B4(fp->item_gobj)) {
        switch (it_8026B320(fp->item_gobj)) {
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

static inline void Fighter_OnItemInvisible(Fighter_GObj* gobj, bool flag)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!it_8026B2B4(fp->item_gobj)) {
        ftAnim_80070CC4(gobj, flag);
    }
}

static inline void Fighter_OnItemVisible(Fighter_GObj* gobj, bool flag)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!it_8026B2B4(fp->item_gobj)) {
        ftAnim_80070C48(gobj, flag);
    }
}

static inline void Fighter_OnItemDrop(Fighter_GObj* gobj, bool dropItemFlag,
                                      bool bool2, bool bool3)
{
    ftAnim_80070FB4(gobj, bool2, -1);
    if (dropItemFlag) {
        ftAnim_80070CC4(gobj, bool3);
    }
}

static inline void Fighter_OnKnockbackEnter(Fighter_GObj* gobj, s32 arg1)
{
    ftAnim_800704F0(gobj, arg1, 3.0f);
    ftAnim_800704F0(gobj, 0, 3.0f);
}

static inline void Fighter_OnKnockbackExit(Fighter_GObj* gobj, s32 arg1)
{
    ftAnim_800704F0(gobj, arg1, 0.0f);
    ftAnim_800704F0(gobj, 0, 0.0f);
}

static inline void Fighter_UnsetCmdVar0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
}

static inline CollData* Fighter_GetCollData(Fighter* fp)
{
    return &fp->coll_data;
}

/// @todo This and #ftCheckThrowB3, etc. are probably one macro or something.
static inline bool ftCheckThrowB0(Fighter* fp)
{
    if (fp->throw_flags_b0) {
        fp->throw_flags_b0 = false;
        return true;
    } else {
        return false;
    }
}

static inline bool ftCheckThrowB3(Fighter* fp)
{
    if (fp->throw_flags_b3) {
        fp->throw_flags_b3 = false;
        return true;
    } else {
        return false;
    }
}

static inline bool ftCheckThrowB4(Fighter* fp)
{
    if (fp->throw_flags_b4) {
        fp->throw_flags_b4 = false;
        return true;
    } else {
        return false;
    }
}

static inline float ftGetFacingDir(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->facing_dir;
}

/// Ternary macro for fcmpo-based facing direction check
#define CLIFFCATCH_O(fp)                                                      \
    ((fp)->facing_dir < 0.0f) ? CLIFFCATCH_LEFT : CLIFFCATCH_RIGHT

/// Ternary macro for fcmpu-based facing direction check
#define CLIFFCATCH_U(fp)                                                      \
    ((fp)->facing_dir != 1.0f) ? CLIFFCATCH_LEFT : CLIFFCATCH_RIGHT

/// @todo Fix naming.
#define gmScriptEventCast(p_event, type) ((type*) p_event)
#define gmScriptEventUpdatePtr(event, type)                                   \
    (event = (void*) ((uintptr_t) event + (sizeof(type))))

inline ftCmdScript* getCmdScript(Fighter* fp)
{
    return &fp->x3E4_fighterCmdScript;
}

#endif
