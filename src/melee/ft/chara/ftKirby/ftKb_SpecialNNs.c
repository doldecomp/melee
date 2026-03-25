#include "ftKb_Init.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Escape.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Landing.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "it/items/itnesspkflash.h"
#include "lb/lb_00B0.h"
#include "mp/mplib.h"
#include "MSL/trigf.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

#define SIGNF(x) ((x) > 0.0f ? 1.0f : -1.0f)

extern float ftKb_Init_803CB710[4];
extern float ftKb_Init_803CB720[4];
extern char ftKb_Init_804D3DD0[7];
extern char ftKb_Init_804D3DD8[5];
extern char ftKb_Init_804D3DE0[6];

// fake HSD_JObj helpers

static inline void ftKb_JObjGetScale(HSD_JObj* jobj, Vec3* scale)
{
    (jobj) ? ((void) 0)
           : __assert(ftKb_Init_804D3DD0, 0x337, ftKb_Init_804D3DD8);
    (scale) ? ((void) 0)
            : __assert(ftKb_Init_804D3DD0, 0x338, ftKb_Init_804D3DE0);
    *scale = jobj->scale;
}

static inline bool ftKb_JObjMtxIsDirty(HSD_JObj* jobj)
{
    bool result;
    (jobj) ? ((void) 0)
           : __assert(ftKb_Init_804D3DD0, 0x234, ftKb_Init_804D3DD8);
    result = false;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY)) {
        result = true;
    }
    return result;
}

static inline void ftKb_JObjSetScale(HSD_JObj* jobj, Vec3* scale)
{
    (jobj) ? ((void) 0)
           : __assert(ftKb_Init_804D3DD0, 0x2F8, ftKb_Init_804D3DD8);
    (scale) ? ((void) 0)
            : __assert(ftKb_Init_804D3DD0, 0x2F9, ftKb_Init_804D3DE0);
    jobj->scale = *scale;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        if (jobj != NULL && !ftKb_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void ftKb_JObjSetRotationY(HSD_JObj* jobj, f32 y, f32* base)
{
    (jobj) ? ((void) 0)
           : __assert(ftKb_Init_804D3DD0, 0x294, ftKb_Init_804D3DD8);
    (!(jobj->flags & JOBJ_USE_QUATERNION))
        ? ((void) 0)
        : __assert(ftKb_Init_804D3DD0, 0x295, (char*) &base[8]);
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        if (jobj != NULL && !ftKb_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void ftKb_AirScaleAnimStep(Fighter_GObj* gobj, Vec3* scale,
                                         f32* scale_base)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int frame = fp->mv.pr.specialn.x8;
    if (frame >= 0 && frame < 4) {
        scale->x = fp->fv.kb.x8C.x;
        scale->y = fp->fv.kb.x8C.y * scale_base[frame];
        scale->z = fp->fv.kb.x8C.z * scale_base[frame + 4];
        ftKb_JObjSetScale(jobj, scale);
        fp->mv.pr.specialn.x8 += 1;
    } else {
        ftKb_JObjSetScale(jobj, &fp->fv.kb.x8C);
    }
}

/* 105A34 */ static void fn_80105A34(Fighter_GObj* gobj);

extern ftCollisionBox ftKb_Init_803CB758;
extern f32 ftKb_Init_804D94F0;
extern f32 ftKb_Init_804D94F4;

static inline void ftKb_SetNsFlashAttr(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    fp->mv.kb.specialn_ns.frames_to_loop_charge_ground =
        da->specialn_ns_frames_to_loop_charge_ground;
    fp->mv.kb.specialn_ns.frames_to_loop_charge_air =
        da->specialn_ns_frames_to_loop_charge_air;
    fp->mv.kb.specialn_ns.falling_acceleration_delay =
        da->specialn_ns_falling_acceleration_delay;
    fp->fv.kb.ns_flash_gobj = NULL;
    fp->mv.kb.specialn_ns.charge_release_delay =
        da->specialn_ns_charge_release_delay;
}

void ftKb_SpecialNNs_800FEDD0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNStart, 0, 0, 1, 0, 0);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->self_vel.y = 0;
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4 * 4);
        da = fp->dat_attrs;
        fp->mv.kb.specialn_ns.frames_to_loop_charge_ground =
            da->specialn_ns_frames_to_loop_charge_ground;
        fp->mv.kb.specialn_ns.frames_to_loop_charge_air =
            da->specialn_ns_frames_to_loop_charge_air;
        fp->mv.kb.specialn_ns.falling_acceleration_delay =
            da->specialn_ns_falling_acceleration_delay;
        fp->fv.kb.ns_flash_gobj = NULL;
        fp->mv.kb.specialn_ns.charge_release_delay =
            da->specialn_ns_charge_release_delay;
        ftAnim_8006EBA4(gobj);
    }
}

static inline void ftKb_NsSpecialNStart_Anim_inline(HSD_GObj* gobj,
                                                    Vec3* flash_pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.ns_flash_gobj == NULL) {
        lb_8000B1CC(fp->parts[FtPart_WaistN].joint, NULL, flash_pos);
        flash_pos->z = 0;
        flash_pos->y += fp->x34_scale.y * 3;
        {
            HSD_GObj* flash_gobj =
                it_802AA8C0(gobj, flash_pos, 145, fp->facing_dir);
            fp->fv.kb.ns_flash_gobj = flash_gobj;
            if (flash_gobj != NULL) {
                fp->death2_cb = ftKb_Init_800EE74C;
                fp->take_dmg_cb = ftKb_Init_800EE7B8;
            }
        }
    }
}

void ftKb_NsSpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 flash_pos;
    PAD_STACK(20);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 436, 0, 0, 1, 0, NULL);
        ftKb_NsSpecialNStart_Anim_inline(gobj, &flash_pos);
        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    }
}

void ftKb_NsSpecialNHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int flash_timer_min = fp->mv.kb.specialn_ns.frames_to_loop_charge_ground;
    if (flash_timer_min != 0) {
        fp->mv.kb.specialn_ns.frames_to_loop_charge_ground =
            flash_timer_min - 1;
    }
    if (fp->fv.kb.ns_flash_gobj == NULL) {
        int flash_timer_delay =
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air;
        if (flash_timer_delay != 0) {
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air =
                flash_timer_delay - 1;
        }
    }
    if (fp->fv.kb.ns_flash_gobj == NULL) {
        if (fp->mv.kb.specialn_ns.frames_to_loop_charge_ground <= 0 &&
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air <= 0)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNEnd, 0, 0, 1, 0,
                                      NULL);
            return;
        }
        if (fp->motion_id != ftKb_MS_NsSpecialNHold1) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNHold1, 0,
                                      fp->cur_anim_frame, 1, 0, NULL);
        }
    } else {
        if (it_802AA7E4(fp->fv.kb.ns_flash_gobj) != gobj) {
            fp->fv.kb.ns_flash_gobj = NULL;
            return;
        }
        if (it_802AA7F0(fp->fv.kb.ns_flash_gobj) == 1 &&
            fp->motion_id != ftKb_MS_NsSpecialNHold1)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNHold1, 0,
                                      fp->cur_anim_frame, 1, 0, NULL);
        }
    }
}

void ftKb_NsSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    ftKb_SetNsFlashAttr(gobj);
    ftPartSetRotX(fp, 0, 0.0f);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_NsSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 flash_pos;
    PAD_STACK(20);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNHold0, 0, 0, 1, 0,
                                  NULL);
        ftKb_NsSpecialNStart_Anim_inline(gobj, &flash_pos);
        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    }
}

void ftKb_NsSpecialAirNHold_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int flash_timer_min = fp->mv.kb.specialn_ns.frames_to_loop_charge_ground;
    if (flash_timer_min != 0) {
        fp->mv.kb.specialn_ns.frames_to_loop_charge_ground =
            flash_timer_min - 1;
    }
    if (fp->fv.kb.ns_flash_gobj == NULL) {
        int flash_timer_delay =
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air;
        if (flash_timer_delay != 0) {
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air =
                flash_timer_delay - 1;
        }
    }
    if (fp->fv.kb.ns_flash_gobj == NULL) {
        if (fp->mv.kb.specialn_ns.frames_to_loop_charge_ground <= 0 &&
            fp->mv.kb.specialn_ns.frames_to_loop_charge_air <= 0)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNEnd, 0, 0, 1,
                                      0, NULL);
            return;
        }
        if (fp->motion_id != ftKb_MS_NsSpecialAirNHold1) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNHold1, 0,
                                      fp->cur_anim_frame, 1, 0, NULL);
        }
    } else {
        if (it_802AA7E4(fp->fv.kb.ns_flash_gobj) != gobj) {
            fp->fv.kb.ns_flash_gobj = NULL;
            return;
        }
        if (it_802AA7F0(fp->fv.kb.ns_flash_gobj) == 1 &&
            fp->motion_id != ftKb_MS_NsSpecialAirNHold1)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNHold1, 0,
                                      fp->cur_anim_frame, 1, 0, NULL);
        }
    }
}

void ftKb_NsSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    u8 _[16];
    ftKb_SetNsFlashAttr(gobj);
    ftPartSetRotX(fp, 0, 0.0f);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->specialn_ns_freefall_toggle == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0f,
                          da->specialn_ns_freefall_toggle);
        }
    }
}

void ftKb_NsSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialNHold_IASA(Fighter_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.kb.specialn_ns.charge_release_delay--;
        {
            bool result;
            if (fp->mv.kb.specialn_ns.charge_release_delay <= 0) {
                fp->mv.kb.specialn_ns.charge_release_delay = 0;
                result = true;
            } else {
                result = false;
            }
            if (result != true) {
                return;
            }
        }
        if (fp->input.held_inputs & HSD_PAD_B) {
            return;
        }
    }
    if (gobj == NULL) {
        return;
    }
    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp == NULL) {
            return;
        }
        if (fp->fv.kb.ns_flash_gobj != NULL) {
            fp->fv.kb.ns_flash_gobj = NULL;
        }
    }
}

void ftKb_NsSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialAirNHold_IASA(Fighter_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.kb.specialn_ns.charge_release_delay--;
        {
            bool result;
            if (fp->mv.kb.specialn_ns.charge_release_delay <= 0) {
                fp->mv.kb.specialn_ns.charge_release_delay = 0;
                result = true;
            } else {
                result = false;
            }
            if (result != true) {
                return;
            }
        }
        if (fp->input.held_inputs & HSD_PAD_B) {
            return;
        }
    }
    if (gobj == NULL) {
        return;
    }
    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp == NULL) {
            return;
        }
        if (fp->fv.kb.ns_flash_gobj != NULL) {
            fp->fv.kb.ns_flash_gobj = NULL;
        }
    }
}

void ftKb_NsSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.kb.specialn_ns.falling_acceleration_delay != 0) {
        fp->mv.kb.specialn_ns.falling_acceleration_delay--;
    }
    ft_80084F3C(gobj);
}

void ftKb_NsSpecialNHold_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_NsSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_NsSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 airFriction;
    PAD_STACK(4);
    if (fp->mv.kb.specialn_ns.falling_acceleration_delay != 0) {
        fp->mv.kb.specialn_ns.falling_acceleration_delay--;
    } else {
        ftCommon_Fall(fp, da->specialn_ns_gravity, fp->co_attrs.terminal_vel);
    }
    airFriction = fp->co_attrs.aerial_friction;
    ftCommon_ApplyFrictionAir(fp, airFriction);
}

void ftKb_NsSpecialAirNHold_Phys(Fighter_GObj* gobj)
{
    PAD_STACK(4);
    ftKb_NsSpecialAirNStart_Phys(gobj);
}

void ftKb_NsSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    PAD_STACK(4);
    ftKb_NsSpecialAirNStart_Phys(gobj);
}

void ftKb_NsSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNStart,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
    }
}

void ftKb_NsSpecialNHold_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNHold0,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
    }
}

void ftKb_NsSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNEnd, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

void ftKb_NsSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

void ftKb_NsSpecialAirNHold_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNHold0, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

void ftKb_NsSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNEnd, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

void ftKb_SpecialNDk_800FF8EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->fv.kb.xBC == da->specialn_dk_swings_to_full_charge) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNFull, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 1;
        fp->mv.dk.specialn.xC = fp->fv.kb.xBC;
        fp->fv.kb.xBC = 0;
    } else {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNStart, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 0;
        fp->mv.dk.specialn.xC = 0;
    }
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.dk.specialn.x0 = 0;
    fp->mv.dk.specialn.x4 = 0;
    fp->mv.dk.specialn.x14 = -1;
    fp->mv.dk.specialn.x10 = -1;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0;
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        fp2->pre_hitlag_cb = efLib_PauseAll;
        fp2->post_hitlag_cb = efLib_ResumeAll;
    }
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNDk_800FFA10(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->fv.kb.xBC == da->specialn_dk_swings_to_full_charge) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNFull, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 1;
        fp->mv.dk.specialn.xC = fp->fv.kb.xBC;
        fp->fv.kb.xBC = 0;
    } else {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNStart, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 0;
        fp->mv.dk.specialn.xC = 0;
    }
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.dk.specialn.x0 = 0;
    fp->mv.dk.specialn.x4 = 0;
    fp->mv.dk.specialn.x14 = -1;
    fp->mv.dk.specialn.x10 = -1;
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        fp2->pre_hitlag_cb = efLib_PauseAll;
        fp2->post_hitlag_cb = efLib_ResumeAll;
    }
    ftAnim_8006EBA4(gobj);
}

static inline void ftKb_DkSpecialNStart_Coll_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftKb_DkSpecialNStart_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNLoop, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    volatile unsigned short pad;
    if (fp->cur_anim_frame == 0.0F) {
        fp->fv.kb.xBC += 1;
        if (fp->fv.kb.xBC >= da->specialn_dk_swings_to_full_charge) {
            Fighter* fighter2 = fp;
            ftCo_800BFFD0(fighter2, 58, 0);
            fp->fv.kb.xBC = da->specialn_dk_swings_to_full_charge;
            {
                Fighter* fp2 = gobj->user_data;
                fp2->pre_hitlag_cb = NULL;
                fp2->post_hitlag_cb = NULL;
            }
            ft_8008A2BC(gobj);
        }
    }
}

void ftKb_DkSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
        ft_8008A2BC(gobj);
    }
}

void ftKb_DkSpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(24);
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1194, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1193, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->mv.dk.specialn.x4 == 0) {
            fp->mv.dk.specialn.x4 = 1;
        }
        if (fp->mv.dk.specialn.x10 == -1) {
            fp->mv.dk.specialn.x10 = (s32) fp->x914[0].damage;
        }
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.dk.specialn.x10 +
                            (fp->mv.dk.specialn.xC *
                             da->specialn_dk_damage_increase_per_swing),
                        gobj);
        if (fp->mv.dk.specialn.x14 == -1) {
            fp->mv.dk.specialn.x14 = (s32) fp->x914[1].damage;
        }
        ftColl_8007ABD0(&fp->x914[1],
                        fp->mv.dk.specialn.x14 +
                            (fp->mv.dk.specialn.xC *
                             da->specialn_dk_damage_increase_per_swing),
                        gobj);
    }
    if (fp->mv.dk.specialn.x4 == 1) {
        fp->mv.dk.specialn.x4 = 2;
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            ftKb_DatAttrs* da2 = fp2->dat_attrs;
            fp2->gr_vel =
                fp2->facing_dir *
                (da2->specialn_dk_grounded_punch_horizontal_velocity *
                 fp2->mv.dk.specialn.xC);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        {
            Fighter* fp2 = gobj->user_data;
            fp2->pre_hitlag_cb = NULL;
            fp2->post_hitlag_cb = NULL;
        }
        ft_8008A2BC(gobj);
    }
}

void ftKb_DkSpecialNFull_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[32];
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1194, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1193, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled &&
        (fp->mv.dk.specialn.x4 == 0))
    {
        fp->mv.dk.specialn.x4 = 1;
    }
    if (fp->mv.dk.specialn.x4 == 1) {
        fp->mv.dk.specialn.x4 = 2;
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            ftKb_DatAttrs* da2 = fp2->dat_attrs;
            fp2->gr_vel =
                fp2->facing_dir *
                (da2->specialn_dk_grounded_punch_horizontal_velocity *
                 fp2->mv.dk.specialn.xC);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        {
            Fighter* fp2 = gobj->user_data;
            fp2->pre_hitlag_cb = NULL;
            fp2->post_hitlag_cb = NULL;
        }
        ft_8008A2BC(gobj);
    }
}

void ftKb_DkSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNLoop, 0, 0.0F,
                                  1.0F, 0.0F, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->cur_anim_frame == 0.0F) {
        new_var = da;
        fp->fv.kb.xBC += 1;
        if (fp->fv.kb.xBC >= new_var->specialn_dk_swings_to_full_charge) {
            Fighter* fighter2 = fp;
            ftCo_800BFFD0(fighter2, 58, 0);
            fp->fv.kb.xBC = new_var->specialn_dk_swings_to_full_charge;
            {
                Fighter* fp2 = gobj->user_data;
                fp2->pre_hitlag_cb = NULL;
                fp2->post_hitlag_cb = NULL;
            }
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftKb_DkSpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    u8 _[16];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_DkSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1194, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1193, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->mv.dk.specialn.x10 == -1) {
            fp->mv.dk.specialn.x10 = (s32) fp->x914[0].damage;
        }
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.dk.specialn.x10 +
                            (fp->mv.dk.specialn.xC *
                             da->specialn_dk_damage_increase_per_swing),
                        gobj);
        if (fp->mv.dk.specialn.x14 == -1) {
            fp->mv.dk.specialn.x14 = (s32) fp->x914[1].damage;
        }
        ftColl_8007ABD0(&fp->x914[1],
                        fp->mv.dk.specialn.x14 +
                            (fp->mv.dk.specialn.xC *
                             da->specialn_dk_damage_increase_per_swing),
                        gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        {
            Fighter* fp2 = gobj->user_data;
            fp2->pre_hitlag_cb = NULL;
            fp2->post_hitlag_cb = NULL;
        }
        if (da->specialn_dk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_dk_freefall_toggle);
        }
    }
}

void ftKb_DkSpecialAirNFull_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1194, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1193, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        {
            Fighter* fp2 = gobj->user_data;
            fp2->pre_hitlag_cb = NULL;
            fp2->post_hitlag_cb = NULL;
        }
        if (da->specialn_dk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_dk_freefall_toggle);
        }
    }
}

void ftKb_DkSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftCo_8009917C(gobj)) {
        if (fp->input.x668 & HSD_PAD_B) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialN, 0, 0.0F, 1.0F,
                                      0.0F, NULL);
            new_var = fp;
            new_var->mv.dk.specialn.xC = fp->fv.kb.xBC;
            fp->fv.kb.xBC = 0;
            ftKb_DkSpecialNStart_Coll_inline(gobj);
            ftAnim_8006EBA4(gobj);
        }
        if (fp->input.x668 & HSD_PAD_LR) {
            fp->mv.dk.specialn.x0 = 1;
        }
        if (fp->cur_anim_frame == 0.0F && fp->mv.dk.specialn.x0) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNCancel, 0, 0.0F,
                                      1.0F, 0.0F, NULL);
            ftKb_DkSpecialNStart_Coll_inline(gobj);
        }
    }
}

void ftKb_DkSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNFull_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    new_var = fp;
    if (fp->input.x668 & HSD_PAD_B) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirN, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
        fp->mv.dk.specialn.xC = fp->fv.kb.xBC;
        fp->fv.kb.xBC = 0;
        ftKb_DkSpecialNStart_Coll_inline(gobj);
        ftAnim_8006EBA4(gobj);
    }
    if (fp->input.x668 & HSD_PAD_LR) {
        fp->mv.dk.specialn.x0 = 1;
    }
    if (new_var->cur_anim_frame == 0.0F && fp->mv.dk.specialn.x0) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNCancel, 0, 0.0F,
                                  1.0F, 0.0F, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNFull_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNStart_Phys(Fighter_GObj* gobj)

{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNFull_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNFull_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNStart,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNLoop, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNCancel,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_800827A0(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirN, 0x0C4D508EU,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_800827A0(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNFull, 0x0C4D508EU,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNLoop, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNCancel, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialN, 0x0C4D508EU,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNFull, 0x0C4D508EU,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_SpecialNPr_80100DE0(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->fv.kb.xBC = 0;
    efLib_DestroyAll(gobj);
}

static inline void ftKb_PrScaleAnimStep(Fighter_GObj* gobj, Vec3* scale)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int frame = fp->mv.pr.specialn.x8;
    if (frame >= 0 && frame < 4) {
        scale->x = fp->fv.kb.x8C.x;
        scale->y = fp->fv.kb.x8C.y * ftKb_Init_803CB710[frame];
        scale->z = fp->fv.kb.x8C.z * ftKb_Init_803CB720[frame];
        ftKb_JObjSetScale(jobj, scale);
        fp->mv.pr.specialn.x8 += 1;
    } else {
        ftKb_JObjSetScale(jobj, &fp->fv.kb.x8C);
    }
}

static inline void ftKb_PrRestoreScale(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    ftKb_JObjSetScale(jobj, &fp->fv.kb.x8C);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
    if (fp->mv.pr.specialn.facing_dir != 0) {
        fp->facing_dir = fp->mv.pr.specialn.facing_dir;
    }
    fp->mv.pr.specialn.facing_dir = 0;
}

static inline void ftKb_PrSetCallbacks(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
    fp->deal_dmg_cb = fn_80100E0C;
    fp->x21F8 = fn_80105978;
}

void fn_80100E0C(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 9) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4);

    fp->mv.pr.specialn.xC = 0;
    switch (fp->motion_id) {
    case ftKb_MS_PrSpecialN1:
    case ftKb_MS_PrSpecialNTurn:
    case ftKb_MS_PrSpecialAirN:
    case ftKb_MS_PrSpecialN0:
        fp->mv.pr.specialn.x0 -= da->specialn_pr_unk;
        fp->facing_dir = fp->mv.pr.specialn.x34.x;
        ftColl_8007AFF8(gobj);
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialNHit, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        fp->death2_cb = ftKb_Init_800EE74C;
        fp->take_dmg_cb = ftKb_Init_800EE7B8;
        fp->deal_dmg_cb = NULL;
        if (fp->ground_or_air == GA_Ground) {
            fp->self_vel.x =
                fp->gr_vel * da->specialn_pr_horizontal_bounce_momentum_on_hit;
            ftCommon_8007D5D4(fp);
        } else {
            fp->self_vel.x *=
                da->specialn_pr_horizontal_bounce_momentum_on_hit;
        }
        fp->self_vel.y = da->specialn_pr_vertical_bounce_momentum_on_hit;
        fp->x74_anim_vel.y = 0;
        fp->x74_anim_vel.x = 0;
        fp->xE4_ground_accel_1 = 0;
        fp->gr_vel = 0;
        fp->mv.pr.specialn.facing_dir = 0;
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        ft_PlaySFX(fp, 0x3D0D6, 127, 64);
    }
}

void fn_80100F60(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

void ftKb_SpecialNPr_80100F94(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    HitCapsuleState state = fp->x914[0].state;
    f32 abs_vel =
        (fp->ground_or_air == GA_Air) ? ABS(fp->self_vel.x) : ABS(fp->gr_vel);
    s32 damage;
    if (abs_vel < da->specialn_pr_unk10) {
        fp->x914[0].state = HitCapsule_Disabled;
        ftCo_800BFFAC(fp);
    } else if (state == HitCapsule_Disabled) {
        fp->x914[0].state = HitCapsule_Enabled;
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->ground_or_air == GA_Air) {
            damage = da->specialn_pr_damage_multiplier *
                     (da->specialn_pr_base_damage + ABS(fp->self_vel.x));
        } else {
            damage = da->specialn_pr_damage_multiplier *
                     (da->specialn_pr_base_damage + ABS(fp->gr_vel));
        }
        if (damage < 1) {
            damage = 1;
        }
        ftColl_8007ABD0(&fp->x914[0], damage, gobj);
    }
}

void ftKb_SpecialNPr_801010D4(Fighter_GObj* gobj, bool unk, MotionFlags flags,
                              f32 anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    fp->facing_dir = fp->mv.pr.specialn.x34.x;
    ftColl_8007AFF8(gobj);
    if (unk == false) {
        FtMotionId msid;
        if (fp->facing_dir == 1.0f) {
            msid = ftKb_MS_PrSpecialNEndR;
        } else {
            msid = ftKb_MS_PrSpecialNEndL;
        }
        Fighter_ChangeMotionState(gobj, msid, flags, anim_start, 1, 0, NULL);
        fp->gr_vel *= da->specialn_pr_forward_momentum_from_stick;
        fp->x74_anim_vel.y = 0;
        fp->self_vel.y = 0;
    } else {
        FtMotionId msid;
        if (fp->facing_dir == 1.0f) {
            msid = ftKb_MS_PrSpecialAirNEndR0;
        } else {
            msid = ftKb_MS_PrSpecialAirNEndR1;
        }
        Fighter_ChangeMotionState(gobj, msid, flags, anim_start, 1, 0, NULL);
        fp->self_vel.x *= da->specialn_pr_forward_momentum_from_stick;
        fp->self_vel.y *= da->specialn_pr_unk4;
        fp->xE4_ground_accel_1 = 0;
        fp->gr_vel = 0;
    }
    ftKb_PrSetCallbacks(gobj);
    ftKb_PrRestoreScale(gobj);
    fp->mv.pr.specialn.facing_dir = 0;
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
}

void ftKb_SpecialNPr_8010131C(Fighter_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKb_JObjGetScale(jobj, &fp->fv.kb.x8C);
    fp->gr_vel = 0;
    fp->mv.pr.specialn.x0 = da->specialn_pr_duration;
    fp->mv.pr.specialn.x4 = -1;
    fp->mv.pr.specialn.x8 = -1;
    fp->mv.pr.specialn.xC = 0;
    fp->mv.pr.specialn.x14 = 0;
    fp->mv.pr.specialn.x34.y = 0;
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x24 = 0;
    fp->mv.pr.specialn.x28 = 0;
    fp->mv.pr.specialn.x2C = da->specialn_pr_charge_rate1;
    fp->mv.pr.specialn.x30 = 0;
    fp->deal_dmg_cb = fn_80100E0C;
    fp->x21F8 = fn_80105978;
}

static inline void ftKb_PrPlayRollSFX(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int sfx_id;
    if (fp->ground_or_air == GA_Air) {
        sfx_id = 0x3D0D3;
    } else {
        sfx_id = 0x3D0D0;
    }
    ft_80088510(fp, sfx_id, 127, 64);
}

void ftKb_SpecialNPr_8010140C(Fighter_GObj* gobj, bool arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    while (fp->mv.pr.specialn.x14 < 0.0f) {
        fp->mv.pr.specialn.x14 += M_PI * 2;
    }
    while (fp->mv.pr.specialn.x14 > M_PI * 2) {
        fp->mv.pr.specialn.x14 -= M_PI * 2;
    }
    if (fp->mv.pr.specialn.x34.y == 0.0f) {
        ftKb_PrPlayRollSFX(gobj);
    } else {
        if (fp->mv.pr.specialn.x34.x == (arg1 ? -1.0f : 1.0f)) {
            if (fp->mv.pr.specialn.x14 < fp->mv.pr.specialn.x34.y) {
                ftKb_PrPlayRollSFX(gobj);
            }
        } else if (fp->mv.pr.specialn.x14 > fp->mv.pr.specialn.x34.y) {
            ftKb_PrPlayRollSFX(gobj);
        }
    }
    fp->mv.pr.specialn.x34.y = fp->mv.pr.specialn.x14;
}

void ftKb_SpecialNPr_80101560(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    FtMotionId msid;
    u8 _[16];
    fp->mv.pr.specialn.x34.x = fp->facing_dir;
    if (1.0f == fp->mv.pr.specialn.x34.x) {
        msid = ftKb_MS_PrSpecialNStartR;
    } else {
        msid = ftKb_MS_PrSpecialNStartL;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftAnim_8006EBA4(gobj);
    ftKb_SpecialNPr_8010131C(gobj);
    fp->x74_anim_vel.y = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->mv.pr.specialn.x1C = da->specialn_pr_unk1;
}

void ftKb_SpecialNPr_80101618(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    FtMotionId msid;
    u8 _[16];
    fp->mv.pr.specialn.x34.x = fp->facing_dir;
    if (1.0f == fp->mv.pr.specialn.x34.x) {
        msid = ftKb_MS_PrSpecialAirNStartR;
    } else {
        msid = ftKb_MS_PrSpecialAirNStartL;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftAnim_8006EBA4(gobj);
    ftKb_SpecialNPr_8010131C(gobj);
    fp->x74_anim_vel.y = da->specialn_pr_air_height_offset_at_start;
    fp->mv.pr.specialn.x1C = da->specialn_pr_unk2;
}

void ftKb_PrSpecialNStart_Anim(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(12);
    fp->mv.pr.specialn.facing_dir = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialNLoop, mf, 0, 0, 0,
                                  NULL);
        ftKb_PrSetCallbacks(gobj);
        fp->cur_anim_frame = 0;
        ftAnim_SetAnimRate(gobj, 0);
        fp->gr_vel = fp->self_vel.x = fp->facing_dir * 0.0001f;
        fp->xE4_ground_accel_1 = fp->x74_anim_vel.x = 0;
        ftPartSetRotY(fp, 0, M_PI_2);
    }
}

static inline void ftKb_PrNormalizeAndSetRollAngle(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    while (fp->mv.pr.specialn.x14 < 0.0f) {
        fp->mv.pr.specialn.x14 += M_PI * 2;
    }
    while (fp->mv.pr.specialn.x14 > M_PI * 2) {
        fp->mv.pr.specialn.x14 -= M_PI * 2;
    }
    ftPartSetRotX(fp, FtPart_YRotN, fp->mv.pr.specialn.x14);
}

void ftKb_PrSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 9) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKb_SpecialNPr_8010140C(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x2C += da->specialn_pr_charge_rate2;
    if (fp->mv.pr.specialn.x2C >= da->specialn_pr_charge_time) {
        fp->mv.pr.specialn.x2C = da->specialn_pr_charge_time;
        if (fp->mv.pr.specialn.x30 == 0) {
            ftCo_800BFFD0(fp, 5, 0);
        }
        fp->mv.pr.specialn.x30 = 1;
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialNFull, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
    }
    fp->mv.pr.specialn.x14 +=
        fp->mv.pr.specialn.x34.x *
        (fp->mv.pr.specialn.x2C *
         (deg_to_rad * da->specialn_pr_charge_spin_animation));
    ftKb_PrNormalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftKb_PrSpecialNFull_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKb_SpecialNPr_8010140C(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x2C += da->specialn_pr_charge_rate2;
    if (fp->mv.pr.specialn.x2C >= da->specialn_pr_charge_time) {
        fp->mv.pr.specialn.x2C = da->specialn_pr_charge_time;
        fp->mv.pr.specialn.x30 = 1;
    }
    fp->mv.pr.specialn.x14 +=
        fp->mv.pr.specialn.x34.x *
        (fp->mv.pr.specialn.x2C *
         (deg_to_rad * da->specialn_pr_charge_spin_animation));
    ftKb_PrNormalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

static inline void ftKb_PrHitCapsuleToggle(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* da;
    Fighter* fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    fp->mv.pr.specialn.xC += 1;
    if (fp->mv.pr.specialn.xC >= (s32) da->specialn_pr_unk6 &&
        fp->x914[0].state != HitCapsule_Disabled)
    {
        fp->x914[0].x4 = (fp->x914[0].x4 + 1) & 1;
        fp->mv.pr.specialn.xC = 0;
    }
}

void ftKb_PrSpecialN1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 scale;
    PAD_STACK(16);
    ftKb_SpecialNPr_8010140C(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    ftKb_PrScaleAnimStep(gobj, &scale);
    ftKb_PrHitCapsuleToggle(gobj);
    ftKb_SpecialNPr_80100F94(gobj);
    {
        f32 old_angle = fp->mv.pr.specialn.x14;
        f32 delta =
            deg_to_rad * fp->mv.pr.specialn.x2C *
            (f32) (0.2 * da->specialn_pr_unk5 * fp->mv.pr.specialn.x34.x);
        fp->mv.pr.specialn.x14 = old_angle + delta;
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        fp->mv.pr.specialn.x0 -= 1;
        if (fp->mv.pr.specialn.x0 <= 0) {
            if (M_PI_2 < fp->mv.pr.specialn.x14 &&
                fp->mv.pr.specialn.x14 < M_PI_2 * 3)
            {
                if (delta > 0.0f) {
                    if (fp->mv.pr.specialn.x14 > M_PI && old_angle < M_PI) {
                        fp->mv.pr.specialn.x0 = 0;
                        ftKb_SpecialNPr_801010D4(gobj, false, 0x40012, 0);
                        return;
                    }
                    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
                    return;
                }
                if (fp->mv.pr.specialn.x14 < M_PI && old_angle > M_PI) {
                    fp->mv.pr.specialn.x0 = 0;
                    ftKb_SpecialNPr_801010D4(gobj, false, 0x40012, 0);
                    return;
                }
                ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
                return;
            }
            ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
            return;
        }
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }
}

void ftKb_PrSpecialNTurn_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 angle;
    Vec3 scale;
    PAD_STACK(8);
    ftKb_SpecialNPr_8010140C(gobj, true);
    ftKb_PrScaleAnimStep(gobj, &scale);
    fp->mv.pr.specialn.x14 +=
        0.2 * da->specialn_pr_spinning_speed_turn * -fp->mv.pr.specialn.x34.x;
    ftKb_PrNormalizeAndSetRollAngle(gobj);
    fp->mv.pr.specialn.x0 -= 1;
    if (fp->mv.pr.specialn.x0 <= 0) {
        fp->mv.pr.specialn.x0 = 0;
        fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
        ftKb_SpecialNPr_801010D4(gobj, false, 0x40012, 0);
        return;
    }
    if ((fp->mv.pr.specialn.x24 % (s32) da->specialn_pr_delay_per_smoke) == 0)
    {
        angle = atan2f(-fp->coll_data.floor.normal.x,
                       fp->coll_data.floor.normal.y);
        efSync_Spawn(0x3FF, gobj, &fp->cur_pos, &fp->facing_dir, &angle);
    }
    fp->mv.pr.specialn.x24 += 1;
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftKb_PrSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 scale;
    fp->mv.pr.specialn.facing_dir = 0;
    ftKb_PrScaleAnimStep(gobj, &scale);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_PrRestoreScale(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftKb_PrSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    fp->mv.pr.specialn.facing_dir = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialAirNLoop, mf, 0, 0, 0,
                                  NULL);
        ftKb_PrSetCallbacks(gobj);
        fp->cur_anim_frame = 0;
        ftAnim_SetAnimRate(gobj, 0);
        fp->self_vel.x = fp->facing_dir * 0.0001f;
        fp->x74_anim_vel.x = 0;
        ftPartSetRotY(fp, 0, M_PI_2);
    }
}

void ftKb_PrSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 9) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKb_SpecialNPr_8010140C(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x2C += da->specialn_pr_charge_rate2;
    if (fp->mv.pr.specialn.x2C >= da->specialn_pr_charge_time) {
        fp->mv.pr.specialn.x2C = da->specialn_pr_charge_time;
        if (fp->mv.pr.specialn.x30 == 0) {
            ftCo_800BFFD0(fp, 5, 0);
        }
        fp->mv.pr.specialn.x30 = 1;
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialAirNFull, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
    }
    fp->mv.pr.specialn.x14 +=
        fp->mv.pr.specialn.x34.x *
        (fp->mv.pr.specialn.x2C *
         (deg_to_rad * da->specialn_pr_charge_spin_animation));
    ftKb_PrNormalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftKb_PrSpecialAirNFull_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKb_SpecialNPr_8010140C(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    fp->mv.pr.specialn.x2C += da->specialn_pr_charge_rate2;
    if (fp->mv.pr.specialn.x2C >= da->specialn_pr_charge_time) {
        fp->mv.pr.specialn.x2C = da->specialn_pr_charge_time;
        fp->mv.pr.specialn.x30 = 1;
    }
    fp->mv.pr.specialn.x14 +=
        fp->mv.pr.specialn.x34.x *
        (fp->mv.pr.specialn.x2C *
         (deg_to_rad * da->specialn_pr_charge_spin_animation));
    ftKb_PrNormalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftKb_PrSpecialAirN_Anim(Fighter_GObj* gobj)
{
    f32* scale_base = ftKb_Init_803CB710;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 scale;
    PAD_STACK(16);
    ftKb_SpecialNPr_8010140C(gobj, false);
    fp->mv.pr.specialn.facing_dir = 0;
    ftKb_AirScaleAnimStep(gobj, &scale, scale_base);
    ftKb_PrHitCapsuleToggle(gobj);
    ftKb_SpecialNPr_80100F94(gobj);
    {
        f32 old_angle = fp->mv.pr.specialn.x14;
        f32 delta =
            (f32) (0.2 * da->specialn_pr_unk5 * fp->mv.pr.specialn.x34.x) *
            (0.017453292f * fp->mv.pr.specialn.x2C *
             da->specialn_pr_spin_anim_speed_after_collision);
        fp->mv.pr.specialn.x14 = old_angle + delta;
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        fp->mv.pr.specialn.x0--;
        if (fp->mv.pr.specialn.x0 <= 0) {
            if (M_PI_2 < fp->mv.pr.specialn.x14 &&
                fp->mv.pr.specialn.x14 < M_PI_2 * 3)
            {
                if (delta > 0.0f) {
                    if (fp->mv.pr.specialn.x14 > M_PI && old_angle < M_PI) {
                        fp->mv.pr.specialn.x0 = 0;
                        ftKb_SpecialNPr_801010D4(gobj, true, 0x40012, 0);
                        return;
                    }
                    ftKb_JObjSetRotationY(fp->parts[FtPart_TopN].joint, M_PI_2,
                                          scale_base);
                    return;
                }
                if (fp->mv.pr.specialn.x14 < M_PI && old_angle > M_PI) {
                    fp->mv.pr.specialn.x0 = 0;
                    ftKb_SpecialNPr_801010D4(gobj, true, 0x40012, 0);
                    return;
                }
                ftKb_JObjSetRotationY(fp->parts[FtPart_TopN].joint, M_PI_2,
                                      scale_base);
                return;
            }
            ftKb_JObjSetRotationY(fp->parts[FtPart_TopN].joint, M_PI_2,
                                  scale_base);
            return;
        }
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }
}

void ftKb_PrSpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 scale;
    PAD_STACK(4);
    ftKb_SpecialNPr_8010140C(gobj, true);
    ftKb_PrScaleAnimStep(gobj, &scale);
    fp->mv.pr.specialn.x14 +=
        da->specialn_pr_spin_anim_speed_after_collision *
        (f32) (0.2 * da->specialn_pr_spinning_speed_turn *
               -fp->mv.pr.specialn.x34.x);
    ftKb_PrNormalizeAndSetRollAngle(gobj);
    fp->mv.pr.specialn.x0 -= 1;
    if (fp->mv.pr.specialn.x0 <= 0) {
        fp->mv.pr.specialn.x0 = 0;
        fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
        ftKb_SpecialNPr_801010D4(gobj, false, 0x40012, 0);
        return;
    }
    fp->mv.pr.specialn.x24 += 1;
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftKb_PrSpecialAirNEndR_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    u8 _[16];
    Vec3 scale;
    PAD_STACK(4);
    fp->mv.pr.specialn.facing_dir = 0;
    ftKb_PrScaleAnimStep(gobj, &scale);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_PrRestoreScale(gobj);
        if (da->specialn_pr_freefall_toggle == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0f,
                          da->specialn_pr_freefall_toggle);
        }
    }
}

void ftKb_PrSpecialNHit_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    u8 _[12];
    Vec3 scale;
    PAD_STACK(4);
    ftKb_PrScaleAnimStep(gobj, &scale);
    fp->mv.pr.specialn.x14 +=
        da->specialn_pr_spin_anim_speed_after_collision *
        (f32) (0.2 * da->specialn_pr_spinning_speed_turn *
               -fp->mv.pr.specialn.x34.x);
    ftKb_PrNormalizeAndSetRollAngle(gobj);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
}

void ftKb_PrSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialN1, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
        fp->gr_vel = fp->mv.pr.specialn.x34.x *
                     ((fp->mv.pr.specialn.x2C - da->specialn_pr_charge_rate1) *
                      da->specialn_pr_air_speed);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ft_PlaySFX(fp, 0x3D0D9, 127, 64);
    }
}

void ftKb_PrSpecialNFull_IASA(Fighter_GObj* gobj)
{
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialN1, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
        fp->gr_vel = fp->mv.pr.specialn.x34.x *
                     ((fp->mv.pr.specialn.x2C - da->specialn_pr_charge_rate1) *
                      da->specialn_pr_air_speed);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ft_PlaySFX(fp, 0x3D0D9, 127, 64);
    }
}

void ftKb_PrSpecialN1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (ABS(fp->input.lstick.x) > da->specialn_pr_spinning_speed) {
        f32 sign = SIGNF(fp->input.lstick.x);
        if (fp->mv.pr.specialn.x34.x != sign) {
            ftColl_8007AFF8(gobj);
            fp->mv.pr.specialn.facing_dir = sign;
            fp->mv.pr.specialn.x34.x = -sign;
            Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialNTurn,
                                      0x0C4C0292U, fp->cur_anim_frame, 0, 0,
                                      NULL);
            ftKb_PrSetCallbacks(gobj);
            fp->mv.pr.specialn.x10 = fp->gr_vel;
            fp->mv.pr.specialn.x1C = -0.05f * fp->gr_vel;
            fp->mv.pr.specialn.x24 = 0;
            ftKb_PrNormalizeAndSetRollAngle(gobj);
            ft_PlaySFX(fp, 0x3D0D9, 127, 64);
        }
    }
}

void ftKb_PrSpecialNTurn_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialAirN, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
        fp->self_vel.x =
            fp->mv.pr.specialn.x34.x *
            ((fp->mv.pr.specialn.x2C - da->specialn_pr_charge_rate1) *
             da->specialn_pr_air_speed);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ft_PlaySFX(fp, 0x3D0D9, 127, 64);
    }
}

void ftKb_PrSpecialAirNFull_IASA(Fighter_GObj* gobj)
{
    static u32 const mf =
        (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialAirN, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
        fp->self_vel.x =
            fp->mv.pr.specialn.x34.x *
            ((fp->mv.pr.specialn.x2C - da->specialn_pr_charge_rate1) *
             da->specialn_pr_air_speed);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ft_PlaySFX(fp, 0x3D0D9, 127, 64);
    }
}

void ftKb_PrSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialAirNEndR_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNHit_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->xE4_ground_accel_1 = 0.0f;
    ft->gr_vel = 0.0f;
    ft->self_vel.x = 0.0001f * ft->facing_dir;
    ft->self_vel.y = 0.0f;
    ft->x74_anim_vel.y = 0.0f;
    ft->x74_anim_vel.x = 0.0f;
}

void ftKb_PrSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ftKb_PrSpecialNStart_Phys(gobj);
}

void ftKb_PrSpecialNFull_Phys(Fighter_GObj* gobj)
{
    ftKb_PrSpecialNStart_Phys(gobj);
}

void ftKb_PrSpecialN1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 slope = fp->coll_data.floor.normal.x;
    u8 pad[8];
    f32 base_vel = fp->mv.pr.specialn.x34.x *
                   (da->specialn_pr_air_speed *
                    (fp->mv.pr.specialn.x2C - da->specialn_pr_some_speed_var));
    {
        f32 influence = da->specialn_pr_unk9 * (base_vel * ABS(slope));
        if (fp->coll_data.floor.normal.x > 0.0f) {
            if (fp->mv.pr.specialn.x1C > 0.0f) {
                fp->gr_vel = base_vel + influence;
            } else {
                fp->gr_vel = base_vel + influence;
            }
        } else if (fp->mv.pr.specialn.x1C > 0.0f) {
            fp->gr_vel = base_vel - influence;
        } else {
            fp->gr_vel = base_vel - influence;
        }
    }
    {
        f32 max_vel;
        if (ABS(fp->gr_vel) > (max_vel = da->specialn_pr_base_speed)) {
            if (fp->gr_vel < 0.0f) {
                max_vel = -max_vel;
            }
            fp->gr_vel = max_vel;
        }
    }
    {
        f32 max_vel;
        if (ABS(fp->gr_vel) > (max_vel = da->specialn_pr_max_speed)) {
            if (fp->gr_vel < 0.0f) {
                max_vel = -max_vel;
            }
            fp->gr_vel = max_vel;
        }
    }
    fp->mv.pr.specialn.x18 = ABS(fp->gr_vel);
    fp->x74_anim_vel.y = 0;
    fp->self_vel.y = 0;
    ftCommon_ApplyGroundMovement(gobj);
    fp->mv.pr.specialn.x2C -= da->specialn_pr_unk8;
    if (fp->mv.pr.specialn.x2C < da->specialn_pr_some_speed_var) {
        ftKb_SpecialNPr_801010D4(gobj, false, 0x40012, 0.0f);
    }
}

static inline void ftKb_PrSetFacingDir(Fighter* fp)
{
    if (fp->mv.pr.specialn.facing_dir != 0.0f) {
        fp->mv.pr.specialn.x34.x = fp->facing_dir =
            fp->mv.pr.specialn.facing_dir;
    }
    fp->mv.pr.specialn.facing_dir = 0.0f;
    fp->mv.pr.specialn.xC = 0;
}

void ftKb_PrSpecialNTurn_Phys(Fighter_GObj* gobj)
{
    static u32 const mf1 = (1 << 4) | (1 << 18) | (1 << 25);
    static u32 const mf2 = (1 << 1) | (1 << 4) | (1 << 18) | (1 << 25);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 scale = da->specialn_pr_turn_rate_related *
                mpLib_800569EC(fp->coll_data.floor.flags);
    f32 slope = ABS(fp->coll_data.floor.normal.x);
    f32 x1C = fp->mv.pr.specialn.x1C;
    f32 influence = da->specialn_pr_unk9 * (x1C * slope);
    if (fp->coll_data.floor.normal.x > 0.0f) {
        if (x1C > 0.0f) {
            fp->gr_vel += scale * (x1C + influence);
        } else {
            fp->gr_vel += scale * (x1C + influence);
        }
    } else {
        if (x1C > 0.0f) {
            fp->gr_vel += scale * (x1C - influence);
        } else {
            fp->gr_vel += scale * (x1C - influence);
        }
    }
    fp->x74_anim_vel.y = 0;
    fp->self_vel.y = 0;
    ftCommon_ApplyGroundMovement(gobj);
    if (fp->mv.pr.specialn.x10 > 0.0f) {
        if (fp->gr_vel < 0.0f) {
            if (ABS(fp->gr_vel) >=
                ABS(fp->mv.pr.specialn.x10 * da->specialn_pr_unk11))
            {
                fp->x21EC = fn_80100F60;
                Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialN1, mf1,
                                          fp->cur_anim_frame, 0, 0, NULL);
                ftKb_PrSetCallbacks(gobj);
                ftKb_PrSetFacingDir(fp);
            }
        }
    } else {
        if (fp->gr_vel > 0.0f) {
            if (ABS(fp->gr_vel) >=
                ABS(fp->mv.pr.specialn.x10 * da->specialn_pr_unk11))
            {
                fp->x21EC = fn_80100F60;
                Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialN1, mf2,
                                          fp->cur_anim_frame, 0, 0, NULL);
                ftKb_PrSetCallbacks(gobj);
                ftKb_PrSetFacingDir(fp);
            }
        }
    }
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    ftKb_PrNormalizeAndSetRollAngle(gobj);
}

void ftKb_PrSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_ApplyFrictionGround(fp, fp->co_attrs.gr_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_PrSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftCommonData* cd = ft->dat_attrs;
    ftCommon_Fall(ft, cd->x2BC, cd->x2C0);
}

void ftKb_PrSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftCommonData* cd = ft->dat_attrs;
    ftCommon_Fall(ft, cd->x2BC, cd->x2C0);
}

void ftKb_PrSpecialAirNFull_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftCommonData* cd = ft->dat_attrs;
    ftCommon_Fall(ft, cd->x2BC, cd->x2C0);
}

void ftKb_PrSpecialAirN_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 new_var;
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 decel;
    PAD_STACK(16);
    fp->self_vel.x =
        fp->mv.pr.specialn.x34.x *
        (da->specialn_pr_air_speed *
         (fp->mv.pr.specialn.x2C - da->specialn_pr_some_speed_var));
    if (fp->self_vel.x > 0.0f) {
        decel = da->specialn_pr_air_x_axis_momentum;
    } else {
        decel = -da->specialn_pr_air_x_axis_momentum;
    }
    fp->self_vel.x -= decel;
    {
        f32 abs_vel;
        f32 min_vel;
        if (fp->self_vel.x < 0.0f) {
            abs_vel = -fp->self_vel.x;
        } else {
            abs_vel = fp->self_vel.x;
        }
        new_var = da->specialn_pr_air_y_axis_momentum;
        min_vel = new_var;
        if (abs_vel < min_vel) {
            if (fp->self_vel.x < 0.0f) {
                min_vel = -min_vel;
            }
            fp->self_vel.x = min_vel;
        }
    }
    {
        f32 abs_x = fp->self_vel.x;
        if (abs_x < 0.0f) {
            abs_x = -abs_x;
        }
        fp->mv.pr.specialn.x18 = abs_x;
    }
    ftCommon_Fall(fp, da->specialn_pr_air_height_offset_at_start,
                  da->specialn_pr_bounciness);
    fp->mv.pr.specialn.x2C -= da->specialn_pr_unk8;
    if (fp->mv.pr.specialn.x2C < da->specialn_pr_some_speed_var) {
        ftKb_SpecialNPr_801010D4(gobj, true, 0x40012, 0.0f);
    }
}

void ftKb_PrSpecialN_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 decel;
    if (fp->self_vel.x > 0.0f) {
        decel = da->specialn_pr_air_x_axis_momentum;
    } else {
        decel = -da->specialn_pr_air_x_axis_momentum;
    }
    fp->self_vel.x -= decel;
    {
        f32 abs_vel = ABS(fp->self_vel.x);
        f32 min_vel = da->specialn_pr_air_y_axis_momentum;
        if (abs_vel < min_vel) {
            if (fp->self_vel.x < 0.0f) {
                min_vel = -min_vel;
            }
            fp->self_vel.x = min_vel;
        }
    }
    ftCommon_Fall(fp, da->specialn_pr_air_height_offset_at_start,
                  da->specialn_pr_bounciness);
    ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    ftKb_PrNormalizeAndSetRollAngle(gobj);
}

void ftKb_PrSpecialAirNEndR_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftCommonData* cd = ft->dat_attrs;
    ftCommon_Fall(ft, cd->x2BC, cd->x2C0);
}

void ftKb_PrSpecialNHit_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    u8 _[8];

    if (fp->self_vel.y <= -da->specialn_pr_bounciness) {
        ftCommon_8007D268(fp);
    }
    ftCommon_Fall(fp, da->specialn_pr_air_height_offset_at_start,
                  da->specialn_pr_bounciness);
}

void ftKb_PrSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        FtMotionId msid;
        ftCommon_8007D5D4(fp);
        if (1.0f == fp->mv.pr.specialn.x34.x) {
            msid = ftKb_MS_PrSpecialAirNStartR;
        } else {
            msid = ftKb_MS_PrSpecialAirNStartL;
        }
        Fighter_ChangeMotionState(gobj, msid, 0x0C4C5092U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_PrSetCallbacks(gobj);
    }
}

void ftKb_PrSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialAirNLoop, 0x41092U,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }
}

void ftKb_PrSpecialNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialAirNFull, 0x41092U,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }
}

static inline void ftKb_PrWallBounceEffect(Fighter_GObj* gobj, Fighter* fp,
                                           f32 dir, Vec3* pos, f32* angle)
{
    Fighter* fp2 = GET_FIGHTER(gobj);
    *pos = fp2->cur_pos;
    *angle = atan2f(-fp->coll_data.left_facing_wall.normal.x * dir,
                    fp->coll_data.left_facing_wall.normal.y);
    if (dir > 0.0f) {
        pos->x += ABS(fp2->coll_data.ecb.right.x);
    } else {
        pos->x -= ABS(fp2->coll_data.ecb.left.x);
    }
    pos->y +=
        0.5f * ABS(fp2->coll_data.ecb.top.y + fp2->coll_data.ecb.bottom.y);
    efSync_Spawn(0x406, gobj, pos, angle);
    Camera_80030E44(3, pos);
    ftCommon_8007EBAC(fp2, 0xC, 0xA);
    ft_PlaySFX(fp2, 0x3D0D6, 127, 64);
}

void ftKb_PrSpecialN1_Coll(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 7) |
                          (1 << 12) | (1 << 14) | (1 << 18) | (1 << 19) |
                          (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    bool coll = ft_80082888(gobj, &ftKb_Init_803CB758);
    bool wall_hit;

    if (fp->mv.pr.specialn.x34.x == 1.0f) {
        wall_hit = fp->coll_data.env_flags & 0x3F;
        if (wall_hit) {
            Vec3 pos;
            f32 angle;
            ftKb_PrWallBounceEffect(gobj, fp, 1.0f, &pos, &angle);
        }
    } else {
        wall_hit = fp->coll_data.env_flags & 0xFC0;
        if (wall_hit) {
            Vec3 pos;
            f32 angle;
            ftKb_PrWallBounceEffect(gobj, fp, -1.0f, &pos, &angle);
        }
    }

    if (wall_hit) {
        PAD_STACK(4);
        fp->mv.pr.specialn.x2C *= da->specialn_pr_unk12;
        if (fp->mv.pr.specialn.x2C < 0) {
            fp->mv.pr.specialn.x2C = 0;
        }
        fp->mv.pr.specialn.x18 *= da->specialn_pr_unk12;
        fp->gr_vel = -fp->gr_vel * da->specialn_pr_unk12;
        fp->self_vel.x = -fp->self_vel.x * da->specialn_pr_unk12;
        fp->mv.pr.specialn.x34.x = (fp->gr_vel > 0.0f) ? 1.0f : -1.0f;
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }

    if (!coll) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialAirN, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
        fp->mv.pr.specialn.x1C = da->specialn_pr_unk2;
    }
}

void ftKb_PrSpecialNTurn_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 abs_vel = fp->gr_vel;
    s32 result;
    PAD_STACK(12);
    if (abs_vel < 0.0f) {
        abs_vel = -abs_vel;
    }
    if (abs_vel > da->specialn_pr_unk3) {
        result = ft_80082888(gobj, &ftKb_Init_803CB758);
    } else {
        result = ft_80082978(gobj, &ftKb_Init_803CB758);
    }
    if (result == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialN0, 0x0C4C5092U,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
    }
}

void ftKb_PrSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        ftKb_SpecialNPr_801010D4(gobj, true, mf, fp->cur_anim_frame);
    }
}

void ftKb_PrSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        FtMotionId msid;
        ftCommon_8007D7FC(fp);
        if (fp->mv.pr.specialn.x34.x == 1.0F) {
            msid = ftKb_MS_PrSpecialNStartR;
        } else {
            msid = ftKb_MS_PrSpecialNStartL;
        }
        Fighter_ChangeMotionState(gobj, msid, 0x0C4C5092U, fp->cur_anim_frame,
                                  1.0F, 0.0F, NULL);
        ftKb_PrSetCallbacks(gobj);
    }
}

void ftKb_PrSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialNLoop, 0x41092U,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }
}

void ftKb_PrSpecialAirNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialNFull, 0x41092U,
                                  fp->cur_anim_frame, 0, 0, NULL);
        ftKb_PrSetCallbacks(gobj);
        ftKb_PrNormalizeAndSetRollAngle(gobj);
        ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
    }
}

void ftKb_PrSpecialAirN_Coll(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 7) |
                          (1 << 12) | (1 << 14) | (1 << 18) | (1 << 19) |
                          (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    bool coll;
    int wall_hit;

    if (fp->mv.pr.specialn.x34.x == 1.0f) {
        coll = ft_8008239C(gobj, 1, &ftKb_Init_803CB758);
    } else {
        coll = ft_8008239C(gobj, -1, &ftKb_Init_803CB758);
    }

    if (fp->mv.pr.specialn.x34.x == 1.0f) {
        wall_hit = fp->coll_data.env_flags & 0x3F;
        if (wall_hit) {
            Vec3 pos;
            f32 angle;
            ftKb_PrWallBounceEffect(gobj, fp, 1.0f, &pos, &angle);
        }
    } else {
        wall_hit = fp->coll_data.env_flags & 0xFC0;
        if (wall_hit) {
            Vec3 pos;
            f32 angle;
            ftKb_PrWallBounceEffect(gobj, fp, -1.0f, &pos, &angle);
        }
    }

    if (wall_hit) {
        fp->mv.pr.specialn.x2C *= da->specialn_pr_unk12;
        if (fp->mv.pr.specialn.x2C < 0) {
            fp->mv.pr.specialn.x2C = 0;
        }
        fp->mv.pr.specialn.x18 *= da->specialn_pr_unk12;
        fp->self_vel.x = -fp->self_vel.x * da->specialn_pr_unk12;
        fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
    }

    if (coll) {
        f32 vel_y = ABS(fp->self_vel.y * da->specialn_pr_bounce1);
        fp->self_vel.y = vel_y;
        if (vel_y < da->specialn_pr_bounce2) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialN1, mf,
                                      fp->cur_anim_frame, 0, 0, NULL);
            ftKb_PrSetCallbacks(gobj);
            {
                f32 vel = fp->mv.pr.specialn.x18 * fp->mv.pr.specialn.x34.x;
                fp->gr_vel = vel;
                fp->self_vel.x = vel;
            }
            fp->self_vel.z = 0;
            fp->self_vel.y = 0;
            ftKb_PrNormalizeAndSetRollAngle(gobj);
            ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
            atan2f(-fp->coll_data.floor.normal.x,
                   fp->coll_data.floor.normal.y);
            efSync_Spawn(0x3FF, gobj, &fp->cur_pos, &fp->mv.pr.specialn.x34,
                         &fp->mv.pr.specialn.x14);
            fp->mv.pr.specialn.x1C = da->specialn_pr_unk1;
        } else {
            if (ABS(fp->input.lstick.x) > da->specialn_pr_spinning_speed) {
                f32 dir = SIGNF(fp->input.lstick.x);
                fp->mv.pr.specialn.x34.x = dir;
                fp->self_vel.x = fp->gr_vel =
                    fp->mv.pr.specialn.x18 * fp->mv.pr.specialn.x34.x;
                ftPartSetRotY(fp, FtPart_TopN, M_PI_2);
            }
            ftKb_PrNormalizeAndSetRollAngle(gobj);
        }
        fp->mv.pr.specialn.x8 = 0;
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        ftKb_PrRestoreScale(gobj);
        ftCliffCommon_80081370(gobj);
    }
}

void ftKb_PrSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(12);
    if (ft_800824A0(gobj, &ftKb_Init_803CB758)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_PrSpecialNTurn, 0x0C4C5092U,
                                  fp->cur_anim_frame, 0.0F, 0.0F, NULL);
        ftKb_PrSetCallbacks(gobj);
        fp->gr_vel = fp->self_vel.x;
        fp->self_vel.z = 0;
        fp->self_vel.y = 0;
    }
}

void ftKb_PrSpecialAirNEndR_Coll(Fighter_GObj* gobj)
{
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        ftKb_SpecialNPr_801010D4(gobj, false, mf, fp->cur_anim_frame);
    }
}

void ftKb_PrSpecialNHit_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (ft_800824A0(gobj, &ftKb_Init_803CB758)) {
        ftKb_PrRestoreScale(gobj);
        ftCommon_8007D7FC(fp);
        if (da->specialn_pr_freefall_toggle == 0.0f) {
            ft_8008A2BC(gobj);
        } else {
            ftCo_LandingFallSpecial_Enter(gobj, 0,
                                          da->specialn_pr_freefall_toggle);
        }
    }
}

void fn_80105978(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
    fp->self_vel.x = -fp->self_vel.x;
    fp->gr_vel = -fp->gr_vel;
    fp->xE4_ground_accel_1 = -fp->xE4_ground_accel_1;
    fp->mv.pr.specialn.x10 = -fp->mv.pr.specialn.x10;
    fp->mv.pr.specialn.x14 = -fp->mv.pr.specialn.x14;
    fp->mv.pr.specialn.x18 = -fp->mv.pr.specialn.x18;
    fp->mv.pr.specialn.x1C = -fp->mv.pr.specialn.x1C;
    fp->mv.pr.specialn.facing_dir = -fp->mv.pr.specialn.facing_dir;
    fp->mv.pr.specialn.x34.x = -fp->mv.pr.specialn.x34.x;
    fp->mv.pr.specialn.x34.y = -fp->mv.pr.specialn.x34.y;
}

void fn_80105A34(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        FighterBone* bone = fp->parts;
        efSync_Spawn(0x4B6, gobj, bone[1].joint);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void fn_80105AB0(Fighter_GObj*);

void fn_80105AB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4B7, gobj, fp->parts[1].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

static inline void ftKb_SpecialNZd_Helper(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* attributes;
    Fighter* fighter2; // r5
    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->dat_attrs;
    fighter2->cmd_vars[0] = 0;
    fighter2->mv.zd.specialn.x0 =
        attributes->specialn_zd_frames_before_gravity;
}

void ftKb_SpecialNZd_80105B2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_ZdSpecialN, 0, ftKb_Init_804D94F0,
                              ftKb_Init_804D94F4, ftKb_Init_804D94F0, NULL);
    ftAnim_8006EBA4(gobj);
    ftKb_SpecialNZd_Helper(gobj);
    fp->accessory4_cb = fn_80105A34;
}
