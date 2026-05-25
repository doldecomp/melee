#include "ft_0C31.h"

#include "ftcommon.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/types.h"
#include "ftCommon/forward.h"
#include "ftKirby/ftKb_Init.h"
#include "lb/lbaudio_ax.h"

#include <trigf.h>
#include <baselib/dobj.h>
#include <baselib/jobj.h>

HSD_MObj* ft_804D6580;
HSD_MObj* ft_804D6588;

bool ftCo_800C7CA0(Fighter_GObj* gobj)
{
    Vec3 ef_offset;
    Fighter* fp = GET_FIGHTER(gobj);
    f32 threshold = p_ftCommonData->x1B0;
    f32 vel_x = fp->x8c_kb_vel.x;
    CollData* coll = &fp->coll_data;
    PAD_STACK(8);
    if (vel_x < -threshold && (coll->env_flags & Collide_RightWallHug) &&
        fp->mv.co.downreflect.x4 != 1)
    {
        Vec3* normal;
        ef_offset.x = coll->ecb.left.x;
        ef_offset.y = coll->ecb.left.y;
        ef_offset.z = 0.0F;
        ftKb_SpecialN_800F1F1C(gobj, &ef_offset);
        normal = &coll->right_facing_wall.normal;
        fn_800C7DC4(gobj, ftCo_MS_DownReflect, normal, &ef_offset);
        fp->mv.co.downreflect.x4 = 1;
        return true;
    }
    if (vel_x > threshold && (coll->env_flags & Collide_LeftWallHug) &&
        fp->mv.co.downreflect.x4 != 2)
    {
        Vec3* normal;
        ef_offset.x = coll->ecb.right.x;
        ef_offset.y = coll->ecb.right.y;
        ef_offset.z = 0.0F;
        ftKb_SpecialN_800F1F1C(gobj, &ef_offset);
        normal = &coll->left_facing_wall.normal;
        fn_800C7DC4(gobj, ftCo_MS_DownReflect, normal, &ef_offset);
        fp->mv.co.downreflect.x4 = 2;
        return true;
    }
    return false;
}

void fn_800C7DC4(HSD_GObj* gobj, s32 motion_state, Vec3* normal, Vec3* offset)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    Vec3 vel;
    Vec3 spawn_pos;
    f32 angle;
    f32 mag;

    ftCommon_8007D5D4(fp);
    spawn_pos.x = fp->cur_pos.x + offset->x;
    spawn_pos.y = fp->cur_pos.y + offset->y;
    spawn_pos.z = fp->cur_pos.z + offset->z;
    angle = atan2f(-normal->x, normal->y);
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, 0x406, NULL, &spawn_pos,
                  &angle);
    Camera_80030E44(2, &spawn_pos);
    mag = fp->xF0_ground_kb_vel;
    vel = *normal;
    vel.x *= mag;
    vel.y *= mag;
    vel.z *= mag;
    {
        f32 mul = p_ftCommonData->x1BC;
        vel.x *= mul;
        vel.y *= mul;
    }
    fp->x8c_kb_vel = vel;
    fp->self_vel.z = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    {
        f32 fdir;
        if (fp->x8c_kb_vel.x < 0.0f) {
            fdir = -1.0f;
        } else {
            fdir = 1.0f;
        }
        fp->facing_dir = fdir;
    }
    Fighter_ChangeMotionState(gobj, motion_state, 0x18040, 0.0f, 1.0f, 0.0f,
                              NULL);

    // @todo fix branch structure
    if (coll->env_flags & Collide_RightWallHug) {
        goto t1;
    }
    if (!(coll->env_flags & Collide_RightWallHug)) {
        goto t2;
    }
t1:
    fp->cur_pos.x = -(fp->x68C_transNPos.z * -fp->facing_dir -
                      (fp->cur_pos.x + offset->x));
    goto end;
t2:
    fp->cur_pos.y = fp->x68C_transNPos.y + (fp->cur_pos.y + offset->y);
end:

    ftCo_80090574(gobj);
    fp->dmg.x18A8 = mag;
    ftCommon_8007EBAC(fp, 7, 0);
    ftColl_8007B760(gobj, p_ftCommonData->x1B8);
    PAD_STACK(4);
}

void ftCo_DownReflect_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80090780(gobj);
    }
}

void ftCo_DownReflect_IASA(Fighter_GObj* gobj) {}

void ftCo_DownReflect_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_DownReflect_Coll(Fighter_GObj* gobj)
{
    if (ft_80081DD4(gobj)) {
        ftCo_80097D88(gobj);
    }
}

void ftCo_800C8064(void)
{
    HSD_DObj* temp_r3;
    HSD_MObj* var_r0;

    temp_r3 = HSD_JObjGetDObj(HSD_JObjLoadJoint(Fighter_804D6504));
    if (temp_r3 != NULL) {
        var_r0 = temp_r3->mobj;
    } else {
        var_r0 = NULL;
    }
    ft_804D6580 = var_r0;
}

/// @todo maybe uses a shared inline with ftmetal functions?
void ft_800C80A4(Fighter* fp)
{
    size_t i;
    int idx;

    for (i = idx = 0; i < ftPartsTable[fp->kind]->parts_num; idx++, i++) {
        FighterBone* bone = &fp->parts[idx];
        if (bone->flags_b1) {
            HSD_JObj* jobj = bone->joint;
            HSD_DObj* dobj = HSD_JObjGetDObj(jobj);
            HSD_JObjSetFlags(jobj, JOBJ_LIGHTING | JOBJ_TEXGEN |
                                       JOBJ_SPECULAR | JOBJ_UNK_B18);
            HSD_JObjClearFlags(jobj, JOBJ_UNK_B19 | JOBJ_UNK_B20);
            while (dobj != NULL) {
                HSD_DObj* cur;
                HSD_DObjModifyFlags(dobj, 2, 0xE);
                if (dobj != NULL) {
                    cur = dobj->next;
                } else {
                    cur = NULL;
                }
                dobj = cur;
            }
        }
    }
}
