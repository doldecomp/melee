#include "ftkirby.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "it/items/itnesspkflash.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

static void ftKb_NsSpecialNStart_Anim_inline(HSD_GObj* gobj, Vec3* flash_pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.ns_flash_gobj == NULL) {
        lb_8000B1CC(fp->parts[FtPart_WaistN].joint, NULL, flash_pos);
        flash_pos->z = 0;
        flash_pos->y += fp->x34_scale.y * 3.0f;
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

void ftKb_SpecialNNs_800FED38(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNStart, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
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
    Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialAirNStart, Ft_MF_None,
                              0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->self_vel.y = 0.0f;
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
