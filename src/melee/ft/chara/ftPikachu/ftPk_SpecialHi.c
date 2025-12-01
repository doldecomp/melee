#include "ftPk_SpecialHi.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftPikachu/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <dolphin/mtx.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

/// @todo Move elsewhere.
#define MAX_STICK_MAG 0.999f

// points velocity toward facing direction
void ftPk_SpecialHi_UpdateVel(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = fp->facing_dir * ABS(fp->gr_vel);
    fp->self_vel.x = fp->facing_dir * ABS(fp->self_vel.x);
    fp->mv.pk.specialhi.x10.x =
        fp->facing_dir * ABS(fp->mv.pk.specialhi.x10.x);
}

void ftPk_SpecialHi_Enter(HSD_GObj* gobj)
{
    u8 _[8];

    /// @todo Can't move below @c fp.
    ftPikachuAttributes* sa;

    Fighter* fp = GET_FIGHTER(gobj);

    {
        sa = fp->dat_attrs;
        fp->cmd_vars[0] = 0;
        fp->mv.pk.specialhi.x0 = sa->x5C;
    }

    fp->mv.pk.specialhi.x8 = 0;
    fp->mv.pk.specialhi.x18 = 0;
    fp->gr_vel = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    Fighter_ChangeMotionState(gobj, 353, 0, 0.0f, 1.0f, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    u8 _[8];

    /// @todo Can't move below @c fp.
    ftPikachuAttributes* sa;

    Fighter* fp = GET_FIGHTER(gobj);

    {
        sa = fp->dat_attrs;
        fp->cmd_vars[0] = 0;
        fp->mv.pk.specialhi.x0 = sa->x5C;
    }

    fp->mv.pk.specialhi.x8 = 0;
    fp->mv.pk.specialhi.x18 = 0;
    fp->gr_vel = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    Fighter_ChangeMotionState(gobj, 356, 0, 0.0f, 1.0f, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialHiStart0_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPk_SpecialHi_80126C0C(gobj);
    }
}

void ftPk_SpecialAirHiStart0_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPk_SpecialHi_80126E1C(gobj);
    }
}

void ftPk_SpecialHiStart0_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialAirHiStart0_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialHiStart0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirHiStart0_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);

    {
        ftPikachuAttributes* sa = fp->dat_attrs;
        ftCo_DatAttrs* da = &fp->co_attrs;

        if ((signed) fp->mv.pk.specialhi.x0 != 0) {
            fp->mv.pk.specialhi.x0--;
        } else {
            ftCommon_Fall(fp, sa->x64, da->terminal_vel);
        }
    }

    ftCommon_8007CF58(fp);
}

void ftPk_SpecialHiStart0_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftPk_SpecialHi_ChangeMotion_Unk00(gobj);
    }
}

void ftPk_SpecialAirHiStart0_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_CheckGroundAndLedge(gobj, fp->facing_dir < 0 ? -1 : +1)) {
        ftPk_SpecialHi_ChangeMotion_Unk01(gobj);
    } else if (!ftCliffCommon_80081298(gobj)) {
        /// @todo Fix weird control flow.
        return;
    }
}

void ftPk_SpecialHi_ChangeMotion_Unk00(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 356, 206327940, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
}

void ftPk_SpecialHi_ChangeMotion_Unk01(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 353, 206327940, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
}

void ftPk_SpecialHiStart1_Anim(HSD_GObj* gobj)
{
    Vec3 vec;
    Vec3 vec2;

    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    fp->mv.pk.specialhi.x4--;
    if (fp->mv.pk.specialhi.x4 <= 0) {
        ftPk_SpecialHi_MotionChangeUpdateVel_Unk0(gobj);
        fp = GET_FIGHTER(gobj);
        if (fp->kind != FTKIND_PICHU) {
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, 0,
                &vec);
            efSync_Spawn(1012, gobj, &vec);
            fp->x2219_b0 = true;
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
        }
    } else {
        fp = GET_FIGHTER(gobj);
        if (fp->kind != FTKIND_PICHU) {
            float tempf;
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, 0,
                &vec2);
            tempf = HSD_Randf();
            vec2.x += 6 * tempf - 3;
            tempf = HSD_Randf();
            vec2.y += 6 * tempf - 3;
            efSync_Spawn(1012, gobj, &vec2);
            fp->x2219_b0 = true;
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
        }
    }
}

void ftPk_SpecialAirHiStart1_Anim(HSD_GObj* gobj)
{
    Vec3 vec;
    Vec3 vec2;

    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    fp->mv.pk.specialhi.x4--;
    if (fp->mv.pk.specialhi.x4 <= 0) {
        ftPk_SpecialHi_MotionChangeUpdateVel_Unk1(gobj);
        fp = GET_FIGHTER(gobj);
        if (fp->kind != FTKIND_PICHU) {
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, 0,
                &vec);
            efSync_Spawn(1012, gobj, &vec);
            fp->x2219_b0 = true;
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
        }
    } else {
        fp = GET_FIGHTER(gobj);
        if (fp->kind != FTKIND_PICHU) {
            float tempf;
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, 0,
                &vec2);
            tempf = HSD_Randf();
            vec2.x += (10 * tempf) - 5;
            tempf = HSD_Randf();
            vec2.y += (10 * tempf) - 5;
            efSync_Spawn(1012, gobj, &vec2);
            fp->x2219_b0 = true;
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
        }
    }
}

void ftPk_SpecialHiStart1_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialAirHiStart1_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialHi_8012642C(HSD_GObj* gobj)
{
    Vec3 scl;
    Vec3 velocity_vec;

    HSD_JObj* jobj;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    float half_pi = (float) M_PI_2;
    float tempf = (fp->facing_dir * atan2f(fp->self_vel.x, fp->self_vel.y)) +
                  (pika_attr->x78 - half_pi);

    ftParts_8007592C(fp, ftParts_GetBoneIndex(fp, FtPart_XRotN), tempf);
    scl.x = pika_attr->x7C_scale.x;
    scl.y = pika_attr->x7C_scale.y;
    scl.z = pika_attr->x7C_scale.z;
    jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
    HSD_JObjSetScale(jobj, &scl);

    velocity_vec = fp->self_vel;
    ftCommon_8007E2FC(gobj);
    fp->self_vel = velocity_vec;

    fp->x6D8.x = fp->x6D8.y = fp->x6D8.z = fp->x6C0.x = fp->x6C0.y =
        fp->x6C0.z = fp->lstick_angle = fp->x6A4_transNOffset.x =
            fp->x6A4_transNOffset.y = fp->x6A4_transNOffset.z =
                fp->x68C_transNPos.x = fp->x68C_transNPos.y =
                    fp->x68C_transNPos.z = 0.0f;
}

void ftPk_SpecialHiStart1_Phys(HSD_GObj* gobj)
{
    ftCommon_ApplyGroundMovement(gobj);
}

#pragma push
#pragma dont_inline on
void ftPk_SpecialAirHiStart1_Phys(HSD_GObj* gobj)
{
    ftPk_SpecialHi_8012642C(gobj);
}
#pragma pop

void ftPk_SpecialHiStart1_Coll(HSD_GObj* gobj)
{
    Vec3 scl;

    Fighter* fighter2;

    HSD_JObj* jobj;

    Fighter* fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->coll_data;

    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    u8 _[20];

    /// @todo Eliminate cast (by changing type of field)
    if (!ft_80082888(gobj, (ftCollisionBox*) &pika_attr->height_attributes)) {
        if (collData->env_flags & Collide_LeftWallMask ||
            collData->env_flags & Collide_RightWallMask)
        {
            ftCommon_8007D60C(fp);
            ftPk_SpecialHi_MotionChangeUpdateVel_Unk1(gobj);
            return;
        }
        ftPk_SpecialHi_ChangeMotion_Unk02(gobj);
        return;
    }

    { /// could be an inline?
        CollData* collData;
        fighter2 = GET_FIGHTER(gobj);
        collData = &fighter2->coll_data;
        pika_attr = fighter2->dat_attrs;
        if (collData->env_flags & Collide_FloorMask) {
            float angle =
                atan2f(collData->floor.normal.x, collData->floor.normal.y);
            float angle2 = (fighter2->facing_dir * angle) + pika_attr->x68;
            ftParts_8007592C(fighter2,
                             ftParts_GetBoneIndex(fighter2, FtPart_XRotN),
                             angle2);
        }
        scl.x = pika_attr->x6C_scale.x;
        scl.y = pika_attr->x6C_scale.y;
        scl.z = pika_attr->x6C_scale.z;
        jobj = fighter2->parts[ftParts_GetBoneIndex(fighter2, FtPart_XRotN)]
                   .joint;
        HSD_JObjSetScale(jobj, &scl);
    }

    if (collData->env_flags & Collide_LeftWallMask ||
        collData->env_flags & Collide_RightWallMask)
    {
        ftPk_SpecialHi_MotionChangeUpdateVel_Unk0(gobj);
    }
}

static bool ftPikachu_GetBool(HSD_GObj* gobj)
{
    Fighter* fighter2 = gobj->user_data;
    ftPikachuAttributes* pika_attr2 = fighter2->dat_attrs;
    if (fighter2->mv.pk.specialhi.x18 >= pika_attr2->x88) {
        return 1;
    } else if (ftCo_8009A134(gobj)) {
        return 0;
    } else {
        return 1;
    }
}

void ftPk_SpecialAirHiStart1_Coll(HSD_GObj* gobj)
{
    bool bool0;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;
    CollData* collData = &fp->coll_data;

    u8 _[12];

    fp->mv.pk.specialhi.x18++;
    if (ft_CheckGroundAndLedge(gobj, fp->facing_dir < 0.0f ? -1 : 1)) {
        bool0 = ftPikachu_GetBool(gobj);

        if (bool0) {
            float tempf =
                lbVector_AngleXY(&collData->floor.normal, &fp->self_vel);
            if (tempf > (0.017453292f * (90.0f + pika_attr->xA0))) {
                ftCommon_8007D7FC(fp);
                ftPk_SpecialHi_MotionChangeUpdateVel_Unk0(gobj);
                return;
            }
            ftPk_SpecialHi_ChangeMotion_Unk03(gobj);
            return;
        }
    }

    if (!ftCliffCommon_80081298(gobj)) {
        if (collData->env_flags & Collide_CeilingMask) {
            float angle =
                lbVector_AngleXY(&collData->ceiling.normal, &fp->self_vel);
            if (angle > (0.017453292f * (90.0f + pika_attr->xA0))) {
                ftPk_SpecialHi_MotionChangeUpdateVel_Unk1(gobj);
            }
        }

        if (collData->env_flags & Collide_LeftWallMask) {
            float angle = lbVector_AngleXY(&collData->left_facing_wall.normal,
                                           &fp->self_vel);
            if (angle > (0.017453292f * (90.0f + pika_attr->xA0))) {
                ftPk_SpecialHi_MotionChangeUpdateVel_Unk1(gobj);
            }
        }

        if (collData->env_flags & Collide_RightWallMask) {
            float angle = lbVector_AngleXY(&collData->right_facing_wall.normal,
                                           &fp->self_vel);
            if (angle > (0.017453292f * (90.0f + pika_attr->xA0))) {
                ftPk_SpecialHi_MotionChangeUpdateVel_Unk1(gobj);
            }
        }
    }
}

#pragma push
#pragma dont_inline on
void ftPk_SpecialHi_ChangeMotion_Unk02(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    u8 _[8];

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 357, 206327946, fp->cur_anim_frame, 0.0f,
                              0.0f, 0);
    fp->x2223_b4 = true;
    ftPk_SpecialHi_8012642C(gobj);
}
#pragma pop

void ftPk_SpecialHi_ChangeMotion_Unk03(HSD_GObj* gobj)
{
    Vec3 scl;

    CollData* collData;
    ftPikachuAttributes* pika_attr;

    Fighter* fp;
    Fighter* fighter2;

    HSD_JObj* jobj;

    u8 _[16];

    fighter2 = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fighter2);
    Fighter_ChangeMotionState(gobj, 354, 206327946, fighter2->cur_anim_frame,
                              0.0f, 0.0f, 0);

    fp = GET_FIGHTER(gobj);
    collData = &fp->coll_data;
    pika_attr = fp->dat_attrs;
    if (fp->coll_data.env_flags & Collide_FloorMask) {
        float angle = (fp->facing_dir * atan2f(collData->floor.normal.x,
                                               collData->floor.normal.y)) +
                      pika_attr->x68;
        ftParts_8007592C(fp, ftParts_GetBoneIndex(fp, FtPart_XRotN), angle);
    }

    scl.x = pika_attr->x6C_scale.x;
    scl.y = pika_attr->x6C_scale.y;
    scl.z = pika_attr->x6C_scale.z;
    jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
    HSD_JObjSetScale(jobj, &scl);
}

/// @todo What.
static inline float get_max_and_fill_stack(void)
{
    float stack[7];
    stack[0] = MAX_STICK_MAG;
    return MAX_STICK_MAG;
}

// grounded up b zip
void ftPk_SpecialHi_80126C0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    CollData* collData = &fp->coll_data;
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    // distance formula
    float stick_mag = sqrtf(fp->input.lstick.x * fp->input.lstick.x +
                            fp->input.lstick.y * fp->input.lstick.y);

    // cap stick magnitude to MAX_STICK_MAG
    if (stick_mag > MAX_STICK_MAG) {
        stick_mag = get_max_and_fill_stack();
    }

    if (!(stick_mag < pika_attr->x8C)) {
        Vec3 lstick_direction;

        lstick_direction.x = fp->input.lstick.x;
        lstick_direction.y = fp->input.lstick.y;
        lstick_direction.z = 0.0f;

        if (!(lbVector_AngleXY(&collData->floor.normal, &lstick_direction) <
              (float) M_PI_2) &&
            (!ftCo_8009A134(gobj)))
        {
            Fighter* fighter2;
            ftCommon_UpdateFacing(fp);

            // store stick angle to compare during zip2 check
            fp->mv.pk.specialhi.x10.x = lstick_direction.x;
            fp->mv.pk.specialhi.x10.y = lstick_direction.y;

            fighter2 = GET_FIGHTER(gobj);

            // set zip duration
            fighter2->mv.pk.specialhi.x4 =
                ((ftPikachuAttributes*) fighter2->dat_attrs)->x60;

            // lose double jump(s)
            fighter2->x1968_jumpsUsed = fighter2->co_attrs.max_jumps;

            // set ground velocity to (zip_slope * stick_mag) + zip_intercept
            // and then flip based on facing direction
            fp->gr_vel = (pika_attr->x90 * stick_mag) + pika_attr->x94;
            fp->gr_vel *= fp->facing_dir;

            // if second zip
            if (fp->mv.pk.specialhi.x8) {
                // multiply ground velocity by second_zip_decay
                fp->gr_vel *= pika_attr->x98;

                Fighter_ChangeMotionState(gobj, 354, 2, 12.0f, 1.0f, 0.0f, 0);
                ftAnim_8006EBA4(gobj);
            }
            Fighter_ChangeMotionState(gobj, 354, 10, 13.0f, 1.0f, 0.0f, 0);
            ftAnim_8006EBA4(gobj);
            ftAnim_SetAnimRate(gobj, 0.0f);
            fp->x2223_b4 = 1;
            fp->x21F8 = &ftPk_SpecialHi_UpdateVel;
            return;
        }
    }
    ftCommon_8007D60C(fp);
    ftPk_SpecialHi_80126E1C(gobj);
}

// aerial up b zip
void ftPk_SpecialHi_80126E1C(HSD_GObj* gobj)
{
    float temp_f2_2;
    float some_angle;
    float final_stick_mag;

    Fighter* fighter2;
    Fighter* fp = GET_FIGHTER(gobj);

    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    // distance formula
    float temp_stick_mag = sqrtf((fp->input.lstick.x * fp->input.lstick.x) +
                                 (fp->input.lstick.y * fp->input.lstick.y));

    final_stick_mag = temp_stick_mag;

    // cap stick magnitude to MAX_STICK_MAG
    if (temp_stick_mag > MAX_STICK_MAG) {
        final_stick_mag = get_max_and_fill_stack();
    }

    if ((final_stick_mag > pika_attr->x8C)) {
        if (ABS(fp->input.lstick.x) > 0.001f) {
            ftCommon_UpdateFacing(fp);
        }

        // zip angle = atan2(stick_y, stick_x * facing_direction)
        some_angle =
            atan2f(fp->input.lstick.y, fp->input.lstick.x * fp->facing_dir);

        // store stick angle to compare during zip2 check
        fp->mv.pk.specialhi.x10.x = fp->input.lstick.x;
        fp->mv.pk.specialhi.x10.y = fp->input.lstick.y;
    } else {
        // set facing direction if stick x meets a threshold
        ftCommon_8007DA24(fp);

        // use max stick_mag and 90°
        final_stick_mag = MAX_STICK_MAG;
        some_angle = (float) M_PI_2;

        // store inputs as if x=0 and y=max
        fp->mv.pk.specialhi.x10.x = 0.0f;
        fp->mv.pk.specialhi.x10.y = MAX_STICK_MAG;
    }

    fighter2 = GET_FIGHTER(gobj);

    // set zip duration
    fighter2->mv.pk.specialhi.x4 =
        ((ftPikachuAttributes*) fighter2->dat_attrs)->x60;

    // lose double jump(s)
    fighter2->x1968_jumpsUsed = fighter2->co_attrs.max_jumps;

    // compute velocity as (zip slope * stick_mag) + zip intercept
    // x velocity is the same but flips based on facing direction
    temp_f2_2 = ((pika_attr->x90 * final_stick_mag) + pika_attr->x94) *
                cosf(some_angle);
    fp->self_vel.x = fp->facing_dir * temp_f2_2;
    fp->self_vel.y = ((pika_attr->x90 * final_stick_mag) + pika_attr->x94) *
                     sinf(some_angle);

    // if second zip
    if (fp->mv.pk.specialhi.x8) {
        // multiply velocity by second-zip decay
        fp->self_vel.x *= pika_attr->x98;
        fp->self_vel.y *= pika_attr->x98;

        Fighter_ChangeMotionState(gobj, 357, 2, 12.0f, 1.0f, 0.0f, 0);
        ftAnim_8006EBA4(gobj);
    }
    Fighter_ChangeMotionState(gobj, 357, 10, 13.0f, 1.0f, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0.0f);
    fp->x2223_b4 = 1;

    // set velocity to move toward facing direction
    fp->x21F8 = &ftPk_SpecialHi_UpdateVel;
}

static inline bool return_and_fill_stack(void)
{
    float stack[1];
    stack[0] = MAX_STICK_MAG;
    return 0;
}

// seems to check whether to perform a second up b zip
bool ftPk_SpecialHi_80127064(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    // distance formula
    float stick_mag = sqrtf((fp->input.lstick.x * fp->input.lstick.x) +
                            (fp->input.lstick.y * fp->input.lstick.y));

    // if stick_mag is less than the threshold, push the max stick magnitude
    // onto the stack and return 0
    if (stick_mag < pika_attr->x8C) {
        return return_and_fill_stack();
    }

    if (!fp->mv.pk.specialhi.x8) {
        Vec3 vec1, vec2;
        float tempf;

        u8 _[4];

        // push current stick to temporary vector
        vec1.x = fp->input.lstick.x;
        vec1.y = fp->input.lstick.y;
        vec1.z = 0.0f;

        // push stick from zip1 to temporary vector
        vec2.x = fp->mv.pk.specialhi.x10.x;
        vec2.y = fp->mv.pk.specialhi.x10.y;
        vec2.z = 0.0f;

        // get the angular difference between them
        tempf = lbVector_AngleXY(&vec2, &vec1);

        // if the angular difference > the minimum difference, return 1
        if (tempf > (deg_to_rad * (pika_attr->xA8))) {
            return true;
        }

        return false;
    }

    return false;
}

void ftPk_SpecialHiEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((u32) fp->cmd_vars[0] == 1U) {
        if (ftPk_SpecialHi_80127064(gobj)) {
            fp->cmd_vars[0] = 0;
            fp->mv.pk.specialhi.x8 = 1;
            ftPk_SpecialHi_80126C0C(gobj);
            return;
        }
        fp->cmd_vars[0] = 2;
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPk_SpecialAirHiEnd_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    if (fp->cmd_vars[0] == 1) {
        if (ftPk_SpecialHi_80127064(gobj)) {
            fp->cmd_vars[0] = 0;
            fp->mv.pk.specialhi.x8 = 1;
            ftPk_SpecialHi_80126E1C(gobj);
        } else {
            fp->cmd_vars[0] = 2;
        }
    } else if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 0, 1, sa->xAC, sa->xB0);
    }
}

void ftPk_SpecialHiEnd_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialAirHiEnd_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialHiEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        ft_80084F3C(gobj);
    }
}

void ftPk_SpecialAirHiEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    if (fp->cmd_vars[0]) {
        ftCommon_FallBasic(fp);
        ftCommon_ClampSelfVelX(fp, sa->x9C * fp->co_attrs.air_drift_max);
    } else {
        fp->self_vel.y -= (fp->self_vel.y / 9.0f);
        ftCommon_8007CEF4(fp);
    }
}

void ftPk_SpecialHiEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    /// @todo Eliminate cast (by changing type of
    ///       #ftPikachuAttributes::height_attributes)
    ftCollisionBox* box = (ftCollisionBox*) &pika_attr->height_attributes;

    if (!ft_80082888(gobj, box)) {
        ftPk_SpecialHi_ChangeMotion_Unk04(gobj);
    }
}

void ftPk_SpecialAirHiEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    /// @todo Eliminate cast (by changing type of
    ///       #ftPikachuAttributes::height_attributes)
    ftCollisionBox* box = (ftCollisionBox*) &pika_attr->height_attributes;

    u8 _[8];

    if (ft_8008239C(gobj, fp->facing_dir, box)) {
        ftCo_LandingFallSpecial_Enter(gobj, false, pika_attr->xB0);
    } else if (!ftCliffCommon_80081298(gobj)) {
        /// @todo Fix weird control flow.
        return;
    };
}

void ftPk_SpecialHi_ChangeMotion_Unk04(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 358, 206327946, fp->cur_anim_frame, 1.0f,
                              0.0f, 0);
}

void ftPk_SpecialHi_MotionChangeUpdateVel_Unk0(HSD_GObj* gobj)
{
    u8 _[8];

    ftPikachuAttributes* pika_attr;
    Fighter* fp = GET_FIGHTER(gobj);
    pika_attr = fp->dat_attrs;
    fp->mv.pk.specialhi.x1C.x = fp->self_vel.x;
    fp->mv.pk.specialhi.x1C.y = fp->self_vel.y;
    fp->mv.pk.specialhi.x24 = fp->gr_vel;

    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    fp->gr_vel = 0.0f;
    fp->gr_vel = fp->mv.pk.specialhi.x24 * pika_attr->xA4;
    Fighter_ChangeMotionState(gobj, 355, 2, 0.0f, 1.0f, 0.0f, 0);
    fp->x21F8 = &ftPk_SpecialHi_UpdateVel;
}

void ftPk_SpecialHi_MotionChangeUpdateVel_Unk1(HSD_GObj* gobj)
{
    u8 _[8];

    ftPikachuAttributes* pika_attr;
    Fighter* fp = GET_FIGHTER(gobj);
    pika_attr = fp->dat_attrs;
    fp->mv.pk.specialhi.x1C.x = fp->self_vel.x;
    fp->mv.pk.specialhi.x1C.y = fp->self_vel.y;
    fp->mv.pk.specialhi.x24 = fp->gr_vel;

    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    fp->gr_vel = 0.0f;
    fp->self_vel.x = fp->mv.pk.specialhi.x1C.x * pika_attr->xA4;
    fp->self_vel.y = fp->mv.pk.specialhi.x1C.y * pika_attr->xA4;
    Fighter_ChangeMotionState(gobj, 358, 2, 0.0f, 1.0f, 0.0f, 0);
    fp->x21F8 = &ftPk_SpecialHi_UpdateVel;
}
