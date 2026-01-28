#include "ftKb_Init.h"
#include "types.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_CaptureWaitKirby.h"
#include "ft/chara/ftCommon/ftCo_Damage.h"
#include "ft/chara/ftCommon/ftCo_Escape.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Jump.h"
#include "ft/chara/ftCommon/ftCo_KneeBend.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/chara/ftCommon/ftpickupitem.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ftcamera.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureKirby.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"

#include "ftKirby/forward.h"

#include "ftLink/types.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/items/it_27CF.h"
#include "it/items/it_2ADA.h"
#include "it/items/it_2F28.h"
#include "it/items/itclimbersice.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itkirby_2F23.h"
#include "it/items/itkirbycutterbeam.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itkirbyhammer.h"
#include "it/items/itkirbyyoshispecialn.h"
#include "it/items/itlinkarrow.h"
#include "it/items/itlinkbow.h"
#include "it/items/itmewtwoshadowball.h"
#include "it/items/itnesspkflush.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "it/items/itpikachutjoltground.h"
#include "it/items/itsamuschargeshot.h"
#include "it/items/itseakneedleheld.h"
#include "lb/lb_00B0.h"
#include "lb/lbanim.h"
#include "lb/lbvector.h"
#include "melee/lb/lbrefract.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

// Forward declaration for function in ftKb_SpecialNZd.c
void fn_80105A34(Fighter_GObj*);

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

void ftKb_NsSpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 436, 0, 0, 1, 0, NULL);
        {
            Fighter* fp = GET_FIGHTER(gobj);
            Vec3 flash_pos;
            PAD_STACK(4 * 5);
            if (fp->fv.kb.ns_flash_gobj == NULL) {
                lb_8000B1CC(fp->parts[FtPart_WaistN].joint, NULL, &flash_pos);
                flash_pos.z = 0;
                flash_pos.y += fp->x34_scale.y * 3;
                {
                    HSD_GObj* flash_gobj =
                        it_802AA8C0(gobj, &flash_pos, 145, fp->facing_dir);
                    fp->fv.kb.ns_flash_gobj = flash_gobj;
                    if (flash_gobj != NULL) {
                        fp->death2_cb = ftKb_Init_800EE74C;
                        fp->take_dmg_cb = ftKb_Init_800EE7B8;
                    }
                }
            }
        }
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

/// #ftKb_NsSpecialNEnd_Anim

/// #ftKb_NsSpecialAirNStart_Anim

/// #ftKb_NsSpecialAirNHold_Anim

/// #ftKb_NsSpecialAirNEnd_Anim

void ftKb_NsSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_NsSpecialNHold_IASA(Fighter_GObj* gobj)
{
    {
        Fighter* fp = gobj->user_data;
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
        Fighter* fp = gobj->user_data;
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
        Fighter* fp = gobj->user_data;
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
        Fighter* fp = gobj->user_data;
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
    /// FAKE MATCH: comma operator required for regalloc
    if (((0, fp->mv.kb.specialn_ns)).falling_acceleration_delay != 0) {
        fp->mv.kb.specialn_ns.falling_acceleration_delay--;
    } else {
        ftCommon_Fall(fp, da->specialn_ns_gravity, fp->co_attrs.terminal_vel);
    }
    {
        float airFriction = fp->co_attrs.aerial_friction;
        ftCommon_ApplyFrictionAir(fp, airFriction);
    }
}

void ftKb_NsSpecialAirNHold_Phys(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    new_var = da;
    if (fp->mv.kb.specialn_ns.falling_acceleration_delay != 0) {
        fp->mv.kb.specialn_ns.falling_acceleration_delay--;
    } else {
        ftCommon_Fall(fp, new_var->specialn_ns_gravity,
                      fp->co_attrs.terminal_vel);
    }
    {
        float airFriction = fp->co_attrs.aerial_friction;
        ftCommon_ApplyFrictionAir(fp, airFriction);
    }
}

void ftKb_NsSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// FAKE MATCH: comma operator required for regalloc
    ftKb_DatAttrs* da = (0, fp->dat_attrs);
    if (fp->mv.kb.specialn_ns.falling_acceleration_delay != 0) {
        fp->mv.kb.specialn_ns.falling_acceleration_delay--;
    } else {
        ftCommon_Fall(fp, da->specialn_ns_gravity, fp->co_attrs.terminal_vel);
    }
    {
        float airFriction = fp->co_attrs.aerial_friction;
        ftCommon_ApplyFrictionAir(fp, airFriction);
    }
}

void ftKb_NsSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1B7, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKb_NsSpecialNHold_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1B8, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKb_NsSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1BA, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKb_NsSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x1B3, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKb_NsSpecialAirNHold_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x1B4, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKb_NsSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x1B6, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

/// #ftKb_SpecialNDk_800FF8EC

/// #ftKb_SpecialNDk_800FFA10

static inline void ftKb_DkSpecialNStart_Coll_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp = gobj->user_data;
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
            fp->pre_hitlag_cb = NULL;
            fp->post_hitlag_cb = NULL;
            ft_8008A2BC(gobj);
        }
    }
}

void ftKb_DkSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
        ft_8008A2BC(gobj);
    }
}

void ftKb_DkSpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
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
            Fighter* fp2 = gobj->user_data;
            ftKb_DatAttrs* da2 = fp2->dat_attrs;
            fp2->gr_vel =
                fp2->facing_dir *
                (da2->specialn_dk_grounded_punch_horizontal_velocity *
                 fp2->mv.dk.specialn.xC);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
        ft_8008A2BC(gobj);
    }
}

void ftKb_DkSpecialNFull_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
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
            Fighter* fp2 = gobj->user_data;
            ftKb_DatAttrs* da2 = fp2->dat_attrs;
            fp2->gr_vel =
                fp2->facing_dir *
                (da2->specialn_dk_grounded_punch_horizontal_velocity *
                 fp2->mv.dk.specialn.xC);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
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
            fp->pre_hitlag_cb = NULL;
            fp->post_hitlag_cb = NULL;
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftKb_DkSpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    u8 _[16];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_DkSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
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
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
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
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
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
        Fighter_ChangeMotionState(gobj, 0x1CC, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1CD, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1CE, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1CF, 0x0C4D508EU, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1D0, 0x0C4D508EU, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1C7, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x1C8, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x1C9, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x1CA, 0x0C4D508EU, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x1CB, 0x0C4D508EU, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_SpecialNPr_80100DE0(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->fv.kb.xBC = 0;
    efLib_DestroyAll(gobj);
}

/// #fn_80100E0C

void fn_80100F60(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

/// #ftKb_SpecialNPr_80100F94

/// #ftKb_SpecialNPr_801010D4

/// #ftKb_SpecialNPr_8010131C

/// #ftKb_SpecialNPr_8010140C

/// #ftKb_SpecialNPr_80101560

/// #ftKb_SpecialNPr_80101618

/// #ftKb_PrSpecialNStart_Anim

/// #ftKb_PrSpecialNLoop_Anim

/// #ftKb_PrSpecialNFull_Anim

/// #ftKb_PrSpecialN1_Anim

/// #ftKb_PrSpecialNTurn_Anim

/// #ftKb_PrSpecialNEnd_Anim

/// #ftKb_PrSpecialAirNStart_Anim

/// #ftKb_PrSpecialAirNLoop_Anim

/// #ftKb_PrSpecialAirNFull_Anim

/// #ftKb_PrSpecialAirN_Anim

/// #ftKb_PrSpecialN_Anim

/// #ftKb_PrSpecialAirNEndR_Anim

/// #ftKb_PrSpecialNHit_Anim

void ftKb_PrSpecialNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_PrSpecialNLoop_IASA

/// #ftKb_PrSpecialNFull_IASA

/// #ftKb_PrSpecialN1_IASA

void ftKb_PrSpecialNTurn_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_PrSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_PrSpecialAirNLoop_IASA

/// #ftKb_PrSpecialAirNFull_IASA

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
    Fighter* ft = GET_FIGHTER(gobj);
    ft->xE4_ground_accel_1 = 0.0f;
    ft->gr_vel = 0.0f;
    ft->self_vel.x = 0.0001f * ft->facing_dir;
    ft->self_vel.y = 0.0f;
    ft->x74_anim_vel.y = 0.0f;
    ft->x74_anim_vel.x = 0.0f;
}

void ftKb_PrSpecialNFull_Phys(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->xE4_ground_accel_1 = 0.0f;
    ft->gr_vel = 0.0f;
    ft->self_vel.x = 0.0001f * ft->facing_dir;
    ft->self_vel.y = 0.0f;
    ft->x74_anim_vel.y = 0.0f;
    ft->x74_anim_vel.x = 0.0f;
}

/// #ftKb_PrSpecialN1_Phys

/// #ftKb_PrSpecialNTurn_Phys

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

/// #ftKb_PrSpecialAirN_Phys

/// #ftKb_PrSpecialN_Phys

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

/// #ftKb_PrSpecialNStart_Coll

/// #ftKb_PrSpecialNLoop_Coll

/// #ftKb_PrSpecialNFull_Coll

/// #ftKb_PrSpecialN1_Coll

/// #ftKb_PrSpecialNTurn_Coll

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

/// #ftKb_PrSpecialAirNStart_Coll

/// #ftKb_PrSpecialAirNLoop_Coll

/// #ftKb_PrSpecialAirNFull_Coll

/// #ftKb_PrSpecialAirN_Coll

/// #ftKb_PrSpecialN_Coll

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

/// #ftKb_PrSpecialNHit_Coll

/// #fn_80105978

void fn_80105AB0(Fighter_GObj*);

void fn_80105AB0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
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
    Fighter_ChangeMotionState(gobj, ftKb_MS_ZdSpecialN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftKb_SpecialNZd_Helper(gobj);
    fp->accessory4_cb = fn_80105A34;
}
