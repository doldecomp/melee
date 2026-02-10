#include "ftCo_ThrownKirby.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/types.h"
#include "ftKirby/ftKb_Init.h"
#include "ftKirby/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <common_structs.h>
#include <math_ppc.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

typedef float (*KirbyVelocityFunc)(Fighter_GObj* gobj, Vec3* victim_self_vel,
                                   float victim_facing_dir);
typedef float (*GetFloatFunc)(Fighter_GObj* gobj);

/* literal */ float const ftCo_804D8BD0 = 0;
/* literal */ double const ftCo_804D8BD8 = S32_TO_F32;
/* literal */ double const ftCo_804D8BE0 = 0.5;
/* literal */ double const ftCo_804D8BE8 = 3;
/* literal */ float const ftCo_804D8BF0 = -1;
/* literal */ float const ftCo_804D8BF4 = +1;
/* literal */ extern char* ftCo_804D3BE0;
/* literal */ extern char* ftCo_804D3BE8;
/* literal */ extern char* ftCo_804D3BF0;

FighterKind ftCo_800BD9E0(Fighter_GObj* gobj, Fighter_GObj* victim_gobj)
{
    ftKb_Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(victim_gobj);
    FighterKind victim_kind = victim_fp->kind;
    if (victim_kind == FTKIND_KIRBY) {
        ftCo_800BDA50(victim_gobj);
        return victim_fp->fv.kb.hat.kind;
    }
    if ((unsigned) (victim_kind - FTKIND_BOY) <= 1 ||
        victim_kind == FTKIND_SANDBAG)
    {
        return fp->fv.kb.hat.kind;
    }
    if (victim_kind == FTKIND_NANA) {
        victim_kind = FTKIND_POPO;
    }
    return victim_kind;
}

void ftCo_800BDA50(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.kind != FTKIND_KIRBY) {
        /// @todo Which @c mv is this?
        fp->mv.co.thrownkirby.x18_b1 = true;
    }
}

void ftCo_800BDA74(Fighter_GObj* gobj, Vec3* normal)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if (ft_800824A0(gobj, &fp->mv.co.thrownkirby.coll_box)) {
        *normal = coll->floor.normal;
    } else if (coll->env_flags & Collide_RightWallMask) {
        *normal = coll->right_facing_wall.normal;
    } else if (coll->env_flags & Collide_LeftWallMask) {
        *normal = coll->left_facing_wall.normal;
    } else if (coll->env_flags & Collide_CeilingMask) {
        *normal = coll->ceiling.normal;
    } else {
        normal->x = normal->y = normal->z = 0;
    }
}

static inline float inlineB0(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->co_attrs.xDC;
}

static inline float inlineB1(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->co_attrs.kirby_b_star_damage;
}

static inline void inlineB2(Fighter_GObj* gobj, Fighter_GObj* thrower_gobj,
                            Vec3* scale, ftCommon_MotionState msid,
                            KirbyVelocityFunc vel_func, GetFloatFunc get_float)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    fp->facing_dir = -GET_FIGHTER(thrower_gobj)->facing_dir;
    fp->mv.co.thrownkirby.thrower_gobj = thrower_gobj;
    fp->mv.co.thrownkirby.x8 = 0;
    fp->mv.co.thrownkirby.x4 =
        vel_func(thrower_gobj, &fp->self_vel, fp->facing_dir);
    Fighter_UpdateModelScale(gobj);
    HSD_JObjGetScale(jobj, &fp->mv.co.thrownkirby.scale);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_SkipThrowException, 0, 1, 0,
                              thrower_gobj);
    fp->take_dmg_2_cb = ftCo_800BE7C0;
    fp->take_dmg_cb = ftCo_800BE7C0;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->invisible = true;
    ftColl_8007B62C(gobj, 2);
    ftCommon_8007EFC0(fp, 1);
    ftCommon_InitGrab(fp, 0, get_float(thrower_gobj));
    ftAnim_8006EBA4(gobj);
    ftCommon_8007D5D4(fp);
    fp->mv.co.thrownkirby.x18_b0 = false;
    fp->mv.co.thrownkirby.x18_b1 = false;
    ftCommon_SetAccessory(fp, ftKb_SpecialN_800F5898(thrower_gobj, 0));
    scale->x = scale->y = scale->z = inlineB0(gobj);
    HSD_JObjSetScale(fp->x20A0_accessory, scale);
    lb_8000C2F8(fp->x20A0_accessory,
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_YRotN)].joint);
}

void ftCo_800BDB58(Fighter_GObj* gobj, Fighter_GObj* thrower_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 scale;
    inlineB2(gobj, thrower_gobj, &scale, ftCo_MS_ThrownKirbyStar,
             ftKb_SpecialN_800F58AC, ftKb_SpecialN_800F5A88);

    /// @todo Possibly another callback in #inlineB2
    ftColl_8007ABD0(fp->x914, inlineB1(gobj), gobj);

    ftKb_SpecialN_800F5820(thrower_gobj, &fp->mv.co.thrownkirby.coll_box,
                           scale.x);
}

void ftCo_ThrownKirbyStar_Anim(Fighter_GObj* gobj) {}

void ftCo_ThrownKirbyStar_IASA(Fighter_GObj* gobj) {}

static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float vel_mag = sqrtf(SQ(fp->self_vel.x) + SQ(fp->self_vel.y));
    if (vel_mag > fp->mv.co.thrownkirby.x4) {
        fp->self_vel.x =
            (fp->self_vel.x * (vel_mag - fp->mv.co.thrownkirby.x4)) / vel_mag;
        fp->self_vel.y =
            (fp->self_vel.y * (vel_mag - fp->mv.ca.specialhi.vel.x)) / vel_mag;
        if (fp->self_vel.y < 0) {
            fp->facing_dir = -1;
        } else {
            fp->facing_dir = +1;
        }
    } else {
        fp->self_vel.x = 0;
    }
    fp->grab_timer -= ftKb_SpecialN_800F5AC0();
}

void ftCo_ThrownKirbyStar_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    inlineA0(gobj);
    fp->mv.co.thrownkirby.x14 =
        ftCommon_GrabMash(fp, ftKb_SpecialN_800F5AD8());
    if (fp->grab_timer <= 0) {
        ftCo_800BE494(gobj);
    }
}

/// @todo Shared code with #ftCo_ThrownCopyStar_Coll but an inline uses too
///       much stack.
void ftCo_ThrownKirbyStar_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 self_vel;
    Vec3 normal;
    ftCo_800BDA74(gobj, &normal);
    if (normal.x || normal.y || normal.z) {
        self_vel = fp->self_vel;
        lbVector_Mirror(&fp->self_vel, &normal);
        if (self_vel.x * fp->self_vel.x + self_vel.y * fp->self_vel.y < 0) {
            ftCo_800BE494(gobj);
            fp->mv.co.thrownkirby.x8 = normal.x < 0 ? -1 : +1;
        }
    }
}

void ftCo_800BE000(Fighter_GObj* gobj, Fighter_GObj* thrower_gobj)
{
    Vec3 scale;
    Fighter* fp = GET_FIGHTER(gobj);
    inlineB2(gobj, thrower_gobj, &scale, ftCo_MS_ThrownCopyStar,
             ftKb_SpecialN_800F58D8, ftKb_SpecialN_800F5AB0);

    /// @todo Possibly another callback in #inlineB2
    ftColl_8007AFF8(gobj);

    ftKb_SpecialN_800F5820(thrower_gobj, &fp->mv.co.thrownkirby.coll_box,
                           scale.x);
}

void ftCo_ThrownCopyStar_Anim(Fighter_GObj* gobj) {}

void ftCo_ThrownCopyStar_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownCopyStar_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    inlineA0(gobj);
    fp->mv.co.thrownkirby.x14 =
        ftCommon_GrabMash(fp, ftKb_SpecialN_800F5AD8());
    if (fp->grab_timer <= 0) {
        ftCo_800BE494(gobj);
    }
}

/// @todo Shared code with #ftCo_ThrownKirbyStar_Coll but an inline uses too
///       much stack.
void ftCo_ThrownCopyStar_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 self_vel;
    Vec3 normal;
    ftCo_800BDA74(gobj, &normal);
    if (normal.x || normal.y || normal.z) {
        self_vel = fp->self_vel;
        lbVector_Mirror(&fp->self_vel, &normal);
        if (self_vel.x * fp->self_vel.x + self_vel.y * fp->self_vel.y < 0) {
            ftCo_800BE494(gobj);
            fp->mv.co.thrownkirby.x8 = normal.x < 0 ? -1 : +1;
        }
    }
}

void ftCo_800BE494(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_ThrownKirby, Ft_MF_Unk06, 0, 1, 0,
                              NULL);
    fp->take_dmg_2_cb = ftCo_800BE7C0;
    fp->take_dmg_cb = ftCo_800BE7C0;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->invisible = false;
    ftColl_8007B62C(gobj, 0);
    if (!fp->mv.co.thrownkirby.x18_b0) {
        Vec2 self_vel;
        ftKb_SpecialN_800F5874(&self_vel);
        fp->self_vel.y = self_vel.y;
        if (fp->mv.ca.specialhi.vel.y) {
            fp->self_vel.x = fp->mv.ca.specialhi.vel.y * self_vel.x;
        } else {
            fp->self_vel.x = self_vel.x * (fp->self_vel.x < 0 ? -1 : +1);
        }
    } else if (fp->kind == FTKIND_KIRBY && fp->mv.co.thrownkirby.x18_b1 &&
               !fp->fv.kb.hat.x8_b0)
    {
        ftKb_SpecialN_800F190C(gobj, fp->fv.kb.hat.kind);
        ftKb_SpecialN_800EEEC4(gobj, fp->fv.kb.hat.kind);
        fp->fv.kb.hat.kind = FTKIND_KIRBY;
    }
    fp->mv.co.thrownkirby.x10 = ftKb_SpecialN_800F5A98();
    ftCommon_InitGrab(fp, 0, fp->mv.co.thrownkirby.x10);
    fp->mv.co.thrownkirby.xC = ftKb_SpecialN_800F5A70();
    ftAnim_8006EBA4(gobj);
    ftCommon_8007D5D4(fp);
    fp->accessory4_cb = ftCo_800BE6AC;
}

void ftCo_ThrownKirby_Anim(Fighter_GObj* gobj) {}

void ftCo_ThrownKirby_IASA(Fighter_GObj* gobj) {}

static inline void inlineC0(Fighter_GObj* gobj)
{
    Fighter_UpdateModelScale(gobj);
    ftCo_Fall_Enter(gobj);
}

void ftCo_ThrownKirby_Phys(Fighter_GObj* gobj)
{
    u8 _[28] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= ftKb_SpecialN_800F5AC0();
    if (!fp->mv.co.thrownkirby.x18_b0) {
        if (fp->grab_timer <= 0) {
            inlineC0(gobj);
        }
    } else {
        inlineC0(gobj);
    }
}

void ftCo_ThrownKirby_Coll(Fighter_GObj* gobj) {}

void ftCo_800BE6AC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 scale;
    scale.x = scale.y = scale.z =
        (1 - fp->mv.co.thrownkirby.xC) +
        (((fp->mv.co.thrownkirby.x10 - fp->grab_timer) /
          fp->mv.co.thrownkirby.x10) *
         fp->mv.co.thrownkirby.xC);
    scale.x *= fp->mv.co.thrownkirby.scale.x;
    scale.y *= fp->mv.co.thrownkirby.scale.y;
    scale.z *= fp->mv.co.thrownkirby.scale.z;
    HSD_JObjSetScale(jobj, &scale);
}

void ftCo_800BE7C0(Fighter_GObj* gobj)
{
    Fighter_UpdateModelScale(gobj);
}
