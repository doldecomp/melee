#include "ftCo_Thrown.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0D14.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Damage.h"
#include "lb/lb_00B0.h"

#include <baselib/gobj.h>
#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

/* 0DE5A4 */ static void ftCo_800DE5A4(Fighter_GObj*);

void ftCo_800DE3FC(Fighter_GObj* gobj, FtMotionId msid, float anim_speed)
{
    Fighter* fp;
    Fighter* thrower_fp;

    fp = GET_FIGHTER(gobj);
    thrower_fp = GET_FIGHTER(fp->victim_gobj);
    ftCo_800DB368(thrower_fp, fp);
    fp->facing_dir = thrower_fp->facing_dir;
    fp->mv.co.thrown.unk_bool = false;
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, anim_speed, 0.0f,
                              fp->victim_gobj);
    if (thrower_fp->kind == FTKIND_YOSHI) {
        ftColl_8007B62C(gobj, 2);
    }
    if (thrower_fp->kind != FTKIND_KIRBY || msid - ftCo_MS_ThrownF > 1U) {
        pl_80040614(thrower_fp->player_id, thrower_fp->x221F_b4,
                    fp->grab_timer);
        fp->grab_timer = 0.0f;
    }
    fp->accessory1_cb = ftCo_800DE508;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E358(gobj);
    ftAnim_8006EBA4(gobj);
}

/// Assigned to #Fighter::accessory1_cb
void ftCo_800DE508(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;

    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &pos);
    pos.x = (fp->facing_dir * (fp->x1A70.z * fp->x34_scale.y)) + pos.x;
    pos.y += fp->x1A70.y * fp->x34_scale.y;
    pos.z = 0.0f;
    fp->cur_pos = pos;
}

void ftCo_800DE5A4(Fighter_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (fp->mv.co.thrown.unk_bool) {
        if (fp->mv.co.thrown.anim_timer) {
            if (fp->mv.co.thrown.anim_timer == fp->cur_anim_frame) {
                ftAnim_SetAnimRate(arg0, 0.0f);
                fp->mv.co.thrown.anim_timer = 0.0f;
                ftCommon_8007E3EC(arg0);
            }
        }
    } else {
        ftCommon_8007E3EC(arg0);
    }
    if (fp->grab_timer) {
        fp->grab_timer -= p_ftCommonData->grab_timer_decrement;
        ftCommon_8007DC08(fp, p_ftCommonData->x3C8);
        if (fp->grab_timer <= 0.0f) {
            if (fp->mv.co.thrown.xC || fn_800DC044(arg0)) {
                fn_800DC070(arg0);
            } else {
                ftCo_CaptureCut_Enter(arg0);
            }
        }
    }
}

void ftCo_ThrownF_Anim(Fighter_GObj* gobj)
{
    ftCo_800DE5A4(gobj);
}

void ftCo_ThrownF_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownF_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownF_Coll(Fighter_GObj* gobj) {}

void ftCo_ThrownB_Anim(Fighter_GObj* gobj)
{
    ftCo_800DE5A4(gobj);
}

void ftCo_ThrownB_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownB_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownB_Coll(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Anim(Fighter_GObj* gobj)
{
    ftCo_800DE5A4(gobj);
}

void ftCo_ThrownHi_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Coll(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Cam(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim = GET_FIGHTER(fp->victim_gobj);
    if (victim->kind == FTKIND_KIRBY && victim->motion_id == ftCo_MS_ThrowHi) {
        ftCamera_800762F4(gobj);

    } else {
        ftCamera_UpdateCameraBox(gobj);
    }
}

void ftCo_ThrownLw_Anim(Fighter_GObj* gobj)
{
    ftCo_800DE5A4(gobj);
}

void ftCo_ThrownLw_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownLw_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownLw_Coll(Fighter_GObj* gobj) {}

void fn_800DE798(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftColl_8007B8CC(fp, fp->mv.co.fighterthrow.victim);
}

static inline int calcKnockbackAngle(bool is_upward)
{
    int kb_angle;
    if (is_upward != 0) {
        kb_angle = 90;
    } else {
        kb_angle = -1;
    }
    return kb_angle;
}

static inline float calcFacingDir(Fighter* fp)
{
    bool flip_facing_dir = false;
    if (fp->dmg.x1848_kb_angle > 90 && fp->dmg.x1848_kb_angle < 270) {
        flip_facing_dir = true;
    }
    if (flip_facing_dir) {
        return -fp->dmg.facing_dir_1;
    } else {
        return +0.0f;
    }
}

void ftCo_800DE7C0(Fighter_GObj* gobj, Fighter_GObj* victim, bool is_upward)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (victim != 0) {
        fp->x21EC = fn_800DE798;
        fp->mv.co.fighterthrow.victim = victim;
    }

    ftCo_8008DCE0(gobj, calcKnockbackAngle(is_upward), calcFacingDir(fp));
    ftCo_8008E5A4(fp);
}

void ftCo_800DE854(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* thrower_gobj = fp->victim_gobj;
    Fighter* thrower_fp = GET_FIGHTER(thrower_gobj);
    HitCapsule* hit = &thrower_fp->xDF4[1];
    Vec3 collpos;
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &collpos);
    fp->dmg.kb_applied = ftColl_80079C70(fp, thrower_fp, hit, hit->unk_count);
    fp->dmg.x1848_kb_angle = hit->kb_angle;
    fp->dmg.facing_dir_1 = -thrower_fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 1;
    fp->dmg.x1854_collpos = collpos;
    fp->dmg.x1860_element = hit->element;
    Fighter_UnkTakeDamage_8006CC30(fp, hit->damage);
    ftColl_8007891C(thrower_gobj, gobj, hit->damage);
}

void ftCo_800DE920(Fighter_GObj* gobj, f32 anim_timer)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.thrown.unk_bool = true;
    if (fp->cur_anim_frame == anim_timer) {
        ftAnim_SetAnimRate(gobj, 0.0f);
        fp->mv.co.thrown.anim_timer = 0.0f;
    } else {
        fp->mv.co.thrown.anim_timer = anim_timer;
    }
}

void ftCo_800DE974(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.thrown.unk_bool = false;
    ftAnim_SetAnimRate(gobj, 1.0f);
    ftAnim_8006EBA4(gobj);
}
