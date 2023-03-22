#include "ftpikachu4.h"

#include "ftpikachu.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_81B.h"
#include "ft/ft_877.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "lb/lbunknown_001.h"

#include <trigf.h>
#include <dolphin/mtx/types.h>

/// @todo Move elsewhere.
#define MAX_STICK_MAG 0.999f

// points velocity toward facing direction
void ftPikachu_UpdateVel_80125D80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = fp->facing_dir * fabs_inline(fp->gr_vel);
    fp->x80_self_vel.x = fp->facing_dir * fabs_inline(fp->x80_self_vel.x);
    fp->mv.pk.unk4.x10.x = fp->facing_dir * fabs_inline(fp->mv.pk.unk4.x10.x);
}

void ftPikachu_SpecialHi_StartMotion(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Can't move below @c fp.
    ftPikachuAttributes* sa;

    Fighter* fp = GET_FIGHTER(gobj);

    {
        sa = fp->x2D4_specialAttributes;
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.pk.unk4.x0 = sa->x5C;
    }

    fp->mv.pk.unk4.x8 = 0;
    fp->mv.pk.unk4.x18 = 0;
    fp->gr_vel = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
    Fighter_ChangeMotionState(gobj, 0x161, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftPikachu_SpecialAirHi_StartMotion(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Can't move below @c fp.
    ftPikachuAttributes* sa;

    Fighter* fp = GET_FIGHTER(gobj);

    {
        sa = fp->x2D4_specialAttributes;
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.pk.unk4.x0 = sa->x5C;
    }

    fp->mv.pk.unk4.x8 = 0;
    fp->mv.pk.unk4.x18 = 0;
    fp->gr_vel = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
    Fighter_ChangeMotionState(gobj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftPikachu_80125ED8(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPikachu_80126C0C(gobj);
    }
}

void ftPikachu_80125F14(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPikachu_80126E1C(gobj);
    }
}

void ftPikachu_Stub_80125F50(HSD_GObj* arg0) {}

void ftPikachu_Stub_80125F54(HSD_GObj* arg0) {}

void ftPikachu_80125F58(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftPikachu_80125F78(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);

    {
        ftPikachuAttributes* sa = fp->x2D4_specialAttributes;
        attr* attr = &fp->x110_attr;

        if ((signed) fp->mv.pk.unk4.x0 != 0)
            fp->mv.pk.unk4.x0--;
        else
            ftCommon_8007D494(fp, sa->x64, attr->x170_TerminalVelocity);
    }

    ftCommon_8007CF58(fp);
}

void ftPikachu_80125FD8(HSD_GObj* gobj)
{
    if (!func_80082708(gobj))
        ftPikachu_ActionChange_80126084(gobj);
}

void ftPikachu_80126014(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (EnvColl_CheckGroundAndLedge(gobj, fp->facing_dir < 0 ? -1 : +1)) {
        ftPikachu_ActionChange_801260E4(gobj);
    } else if (!ftCliffCommon_80081298(gobj)) {
        /// @todo Fix weird control flow.
        return;
    }
}

void ftPikachu_ActionChange_80126084(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x164, 0xC4C5084, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_801260E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x161, 0xC4C5084, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_80126144(HSD_GObj* gobj)
{
    Vec3 vec;
    Vec3 vec2;

    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->mv.pk.unk4.x4--;
    if (fp->mv.pk.unk4.x4 <= 0) {
        ftPikachu_ActionChangeUpdateVel_801274AC(gobj);
        fp = GET_FIGHTER(gobj);
        if (fp->x4_fighterKind != FTKIND_PICHU) {
            func_8000B1CC(fp->ft_bones[ftParts_8007500C(fp, 2)].x0_jobj, 0,
                          &vec);
            ef_Spawn(0x3F4, gobj, &vec);
            fp->x2219_flag.bits.b0 = 1;
            fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        }
    } else {
        fp = GET_FIGHTER(gobj);
        if (fp->x4_fighterKind != FTKIND_PICHU) {
            f32 tempf;
            func_8000B1CC(fp->ft_bones[ftParts_8007500C(fp, 2)].x0_jobj, 0,
                          &vec2);
            tempf = HSD_Randf();
            vec2.x += (6.0f * tempf) - 3.0f;
            tempf = HSD_Randf();
            vec2.y += (6.0f * tempf) - 3.0f;
            ef_Spawn(0x3F4, gobj, &vec2);
            fp->x2219_flag.bits.b0 = 1;
            fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        }
    }
}

void ftPikachu_801262B4(HSD_GObj* gobj)
{
    Vec3 vec;
    Vec3 vec2;

    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->mv.pk.unk4.x4--;
    if (fp->mv.pk.unk4.x4 <= 0) {
        ftPikachu_ActionChangeUpdateVel_80127534(gobj);
        fp = GET_FIGHTER(gobj);
        if (fp->x4_fighterKind != FTKIND_PICHU) {
            func_8000B1CC(fp->ft_bones[ftParts_8007500C(fp, 2)].x0_jobj, 0,
                          &vec);
            ef_Spawn(0x3F4, gobj, &vec);
            fp->x2219_flag.bits.b0 = 1;
            fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        }
    } else {
        fp = GET_FIGHTER(gobj);
        if (fp->x4_fighterKind != FTKIND_PICHU) {
            f32 tempf;
            func_8000B1CC(fp->ft_bones[ftParts_8007500C(fp, 2)].x0_jobj, 0,
                          &vec2);
            tempf = HSD_Randf();
            vec2.x += (10.0f * tempf) - 5.0f;
            tempf = HSD_Randf();
            vec2.y += (10.0f * tempf) - 5.0f;
            ef_Spawn(0x3F4, gobj, &vec2);
            fp->x2219_flag.bits.b0 = 1;
            fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        }
    }
}

void ftPikachu_Stub_80126424(HSD_GObj* arg0) {}

void ftPikachu_Stub_80126428(HSD_GObj* arg0) {}

void ftPikachu_8012642C(HSD_GObj* gobj)
{
    Vec3 scale;
    Vec3 velocity_vec;

    HSD_JObj* jobj;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    f32 half_pi = (f32) M_PI_2;
    f32 tempf =
        (fp->facing_dir * atan2f(fp->x80_self_vel.x, fp->x80_self_vel.y)) +
        (pika_attr->x78 - half_pi);

    ftParts_8007592C(fp, ftParts_8007500C(fp, 2), tempf);
    scale.x = pika_attr->x7C_scale.x;
    scale.y = pika_attr->x7C_scale.y;
    scale.z = pika_attr->x7C_scale.z;
    jobj = fp->ft_bones[ftParts_8007500C(fp, 2)].x0_jobj;
    HSD_JObjSetScale(jobj, &scale);

    velocity_vec = fp->x80_self_vel;
    ftCommon_8007E2FC(gobj);
    fp->x80_self_vel = velocity_vec;

    fp->x6D8.x = fp->x6D8.y = fp->x6D8.z = fp->x6C0.x = fp->x6C0.y =
        fp->x6C0.z = fp->x6BC_inputStickangle = fp->x6A4_transNOffset.x =
            fp->x6A4_transNOffset.y = fp->x6A4_transNOffset.z =
                fp->x68C_transNPos.x = fp->x68C_transNPos.y =
                    fp->x68C_transNPos.z = 0.0f;
}

void ftPikachu_801265D4(HSD_GObj* gobj)
{
    ftCommon_8007CB74(gobj);
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif

void ftPikachu_801265F4(HSD_GObj* gobj)
{
    ftPikachu_8012642C(gobj);
}

#ifdef MUST_MATCH
#pragma pop
#endif

void ftPikachu_80126614(HSD_GObj* gobj)
{
    Vec3 scale;

    Fighter* fighter2;

    HSD_JObj* jobj;

    Fighter* fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->x6F0_collData;

    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    /// @todo Eliminate cast (by changing type of field)
    if (!func_80082888(gobj, (ftCollisionBox*) &pika_attr->height_attributes))
    {
        if ((collData->x134_envFlags & 0x3F) ||
            (collData->x134_envFlags & 0xFC0))
        {
            ftCommon_8007D60C(fp);
            ftPikachu_ActionChangeUpdateVel_80127534(gobj);
            return;
        }
        ftPikachu_ActionChange_80126A2C(gobj);
        return;
    }

    { /// could be an inline?
        CollData* collData;
        fighter2 = GET_FIGHTER(gobj);
        collData = &fighter2->x6F0_collData;
        pika_attr = fighter2->x2D4_specialAttributes;
        if (collData->x134_envFlags & 0x18000) {
            f32 angle = atan2f(collData->x14C_ground.normal.x,
                               collData->x14C_ground.normal.y);
            f32 angle2 = (fighter2->facing_dir * angle) + pika_attr->x68;
            ftParts_8007592C(fighter2, ftParts_8007500C(fighter2, 2), angle2);
        }
        scale.x = pika_attr->x6C_scale.x;
        scale.y = pika_attr->x6C_scale.y;
        scale.z = pika_attr->x6C_scale.z;
        jobj = fighter2->ft_bones[ftParts_8007500C(fighter2, 2)].x0_jobj;
        HSD_JObjSetScale(jobj, &scale);
    }

    if ((collData->x134_envFlags & 0x3F) || (collData->x134_envFlags & 0xFC0))
    {
        ftPikachu_ActionChangeUpdateVel_801274AC(gobj);
    }
}

bool ftPikachu_GetBool(HSD_GObj* gobj)
{
    Fighter* fighter2 = gobj->user_data;
    ftPikachuAttributes* pika_attr2 = fighter2->x2D4_specialAttributes;
    if (fighter2->mv.pk.unk4.x18 >= pika_attr2->x88) {
        return 1;
    } else if (func_8009A134(gobj)) {
        return 0;
    } else {
        return 1;
    }
}

void ftPikachu_801267C8(HSD_GObj* gobj)
{
    bool bool0;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    CollData* collData = &fp->x6F0_collData;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    fp->mv.pk.unk4.x18++;
    if (EnvColl_CheckGroundAndLedge(gobj, fp->facing_dir < 0.0f ? -1 : 1)) {
        bool0 = ftPikachu_GetBool(gobj);

        if (bool0) {
            f32 tempf = lbvector_AngleXY(&collData->x14C_ground.normal,
                                         &fp->x80_self_vel);
            if (tempf > (0.017453292f * (90.0f + pika_attr->xA0))) {
                ftCommon_8007D7FC(fp);
                ftPikachu_ActionChangeUpdateVel_801274AC(gobj);
                return;
            }
            ftPikachu_ActionChange_80126AA4(gobj);
            return;
        }
    }

    if (!ftCliffCommon_80081298(gobj)) {
        if (collData->x134_envFlags & 0x6000) {
            f32 angle = lbvector_AngleXY(&collData->x188_ceiling.normal,
                                         &fp->x80_self_vel);
            if (angle > (0.017453292f * (90.0f + pika_attr->xA0))) {
                ftPikachu_ActionChangeUpdateVel_80127534(gobj);
            }
        }

        if (collData->x134_envFlags & 0x3F) {
            f32 angle = lbvector_AngleXY(&collData->x160_rightwall.normal,
                                         &fp->x80_self_vel);
            if (angle > (0.017453292f * (90.0f + pika_attr->xA0))) {
                ftPikachu_ActionChangeUpdateVel_80127534(gobj);
            }
        }

        if (collData->x134_envFlags & 0xFC0) {
            f32 angle = lbvector_AngleXY(&collData->x174_leftwall.normal,
                                         &fp->x80_self_vel);
            if (angle > (0.017453292f * (90.0f + pika_attr->xA0))) {
                ftPikachu_ActionChangeUpdateVel_80127534(gobj);
            }
        }
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif

void ftPikachu_ActionChange_80126A2C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x165, 0xC4C508A, 0,
                              fp->x894_currentAnimFrame, 0.0f, 0.0f);
    fp->x2223_flag.bits.b4 = true;
    ftPikachu_8012642C(gobj);
}

#ifdef MUST_MATCH
#pragma pop
#endif

void ftPikachu_ActionChange_80126AA4(HSD_GObj* gobj)
{
    Vec3 scale;

    CollData* collData;
    ftPikachuAttributes* pika_attr;

    Fighter* fp;
    Fighter* fighter2;

    HSD_JObj* jobj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fighter2 = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fighter2);
    Fighter_ChangeMotionState(gobj, 0x162, 0xC4C508A, 0,
                              fighter2->x894_currentAnimFrame, 0.0f, 0.0f);

    fp = GET_FIGHTER(gobj);
    collData = &fp->x6F0_collData;
    pika_attr = fp->x2D4_specialAttributes;
    if (fp->x6F0_collData.x134_envFlags & 0x18000) {
        f32 angle = (fp->facing_dir * atan2f(collData->x14C_ground.normal.x,
                                             collData->x14C_ground.normal.y)) +
                    pika_attr->x68;
        ftParts_8007592C(fp, ftParts_8007500C(fp, 2), angle);
    }

    scale.x = pika_attr->x6C_scale.x;
    scale.y = pika_attr->x6C_scale.y;
    scale.z = pika_attr->x6C_scale.z;
    jobj = fp->ft_bones[ftParts_8007500C(fp, 2)].x0_jobj;
    HSD_JObjSetScale(jobj, &scale);
}

/// @todo What.
static inline float get_max_and_fill_stack(void)
{
    float stack[7];
    stack[0] = MAX_STICK_MAG;
    return MAX_STICK_MAG;
}

// grounded up b zip
void ftPikachu_80126C0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    CollData* collData = &fp->x6F0_collData;
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    // distance formula
    f32 stick_mag = sqrtf(fp->input.x620_lstick_x * fp->input.x620_lstick_x +
                          fp->input.x624_lstick_y * fp->input.x624_lstick_y);

    // cap stick magnitude to MAX_STICK_MAG
    if (stick_mag > MAX_STICK_MAG)
        stick_mag = get_max_and_fill_stack();

    if (!(stick_mag < pika_attr->x8C)) {
        Vec3 lstick_direction;

        lstick_direction.x = fp->input.x620_lstick_x;
        lstick_direction.y = fp->input.x624_lstick_y;
        lstick_direction.z = 0.0f;

        if (!(lbvector_AngleXY(&collData->x14C_ground.normal,
                               &lstick_direction) < (f32) M_PI_2) &&
            (!func_8009A134(gobj)))
        {
            Fighter* fighter2;
            ftCommon_8007D9FC(fp);

            // store stick angle to compare during zip2 check
            fp->mv.pk.unk4.x10.x = lstick_direction.x;
            fp->mv.pk.unk4.x10.y = lstick_direction.y;

            fighter2 = GET_FIGHTER(gobj);

            // set zip duration
            fighter2->mv.pk.unk4.x4 =
                ((ftPikachuAttributes*) fighter2->x2D4_specialAttributes)->x60;

            // lose double jump(s)
            fighter2->x1968_jumpsUsed = fighter2->x110_attr.x168_MaxJumps;

            // set ground velocity to (zip_slope * stick_mag) + zip_intercept
            // and then flip based on facing direction
            fp->gr_vel = (pika_attr->x90 * stick_mag) + pika_attr->x94;
            fp->gr_vel *= fp->facing_dir;

            // if second zip
            if (fp->mv.pk.unk4.x8) {
                // multiply ground velocity by second_zip_decay
                fp->gr_vel *= pika_attr->x98;

                Fighter_ChangeMotionState(gobj, 0x162, 2, 0, 12.0f, 1.0f,
                                          0.0f);
                ftAnim_8006EBA4(gobj);
            }
            Fighter_ChangeMotionState(gobj, 0x162, 0xA, 0, 13.0f, 1.0f, 0.0f);
            ftAnim_8006EBA4(gobj);
            ftAnim_SetAnimRate(gobj, 0.0f);
            fp->x2223_flag.bits.b4 = 1;
            fp->cb.x21F8_callback = &ftPikachu_UpdateVel_80125D80;
            return;
        }
    }
    ftCommon_8007D60C(fp);
    ftPikachu_80126E1C(gobj);
}

// aerial up b zip
void ftPikachu_80126E1C(HSD_GObj* gobj)
{
    f32 temp_f2_2;
    f32 some_angle;
    f32 final_stick_mag;

    Fighter* fighter2;
    Fighter* fp = GET_FIGHTER(gobj);

    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    // distance formula
    f32 temp_stick_mag =
        sqrtf((fp->input.x620_lstick_x * fp->input.x620_lstick_x) +
              (fp->input.x624_lstick_y * fp->input.x624_lstick_y));

    final_stick_mag = temp_stick_mag;

    // cap stick magnitude to MAX_STICK_MAG
    if (temp_stick_mag > MAX_STICK_MAG)
        final_stick_mag = get_max_and_fill_stack();

    if ((final_stick_mag > pika_attr->x8C)) {
        if (fabs_inline(fp->input.x620_lstick_x) > 0.001f) {
            ftCommon_8007D9FC(fp);
        }

        // zip angle = atan2(stick_y, stick_x * facing_direction)
        some_angle = atan2f(fp->input.x624_lstick_y,
                            fp->input.x620_lstick_x * fp->facing_dir);

        // store stick angle to compare during zip2 check
        fp->mv.pk.unk4.x10.x = fp->input.x620_lstick_x;
        fp->mv.pk.unk4.x10.y = fp->input.x624_lstick_y;
    } else {
        // set facing direction if stick x meets a threshold
        ftCommon_8007DA24(fp);

        // use max stick_mag and 90°
        final_stick_mag = MAX_STICK_MAG;
        some_angle = (f32) M_PI_2;

        // store inputs as if x=0 and y=max
        fp->mv.pk.unk4.x10.x = 0.0f;
        fp->mv.pk.unk4.x10.y = MAX_STICK_MAG;
    }

    fighter2 = GET_FIGHTER(gobj);

    // set zip duration
    fighter2->mv.pk.unk4.x4 =
        ((ftPikachuAttributes*) fighter2->x2D4_specialAttributes)->x60;

    // lose double jump(s)
    fighter2->x1968_jumpsUsed = fighter2->x110_attr.x168_MaxJumps;

    // compute velocity as (zip slope * stick_mag) + zip intercept
    // x velocity is the same but flips based on facing direction
    temp_f2_2 = ((pika_attr->x90 * final_stick_mag) + pika_attr->x94) *
                cosf(some_angle);
    fp->x80_self_vel.x = fp->facing_dir * temp_f2_2;
    fp->x80_self_vel.y =
        ((pika_attr->x90 * final_stick_mag) + pika_attr->x94) *
        sinf(some_angle);

    // if second zip
    if (fp->mv.pk.unk4.x8) {
        // multiply velocity by second-zip decay
        fp->x80_self_vel.x *= pika_attr->x98;
        fp->x80_self_vel.y *= pika_attr->x98;

        Fighter_ChangeMotionState(gobj, 0x165, 2, 0, 12.0f, 1.0f, 0.0f);
        ftAnim_8006EBA4(gobj);
    }
    Fighter_ChangeMotionState(gobj, 0x165, 0xA, 0, 13.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0.0f);
    fp->x2223_flag.bits.b4 = 1;

    // set velocity to move toward facing direction
    fp->cb.x21F8_callback = &ftPikachu_UpdateVel_80125D80;
}

static inline bool return_and_fill_stack(void)
{
    float stack[1];
    stack[0] = MAX_STICK_MAG;
    return 0;
}

// seems to check whether to perform a second up b zip
bool ftPikachu_80127064(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    // distance formula
    f32 stick_mag = sqrtf((fp->input.x620_lstick_x * fp->input.x620_lstick_x) +
                          (fp->input.x624_lstick_y * fp->input.x624_lstick_y));

    // if stick_mag is less than the threshold, push the max stick magnitude
    // onto the stack and return 0
    if (stick_mag < pika_attr->x8C)
        return return_and_fill_stack();

    if (!fp->mv.pk.unk4.x8) {
        Vec3 vec1, vec2;
        f32 tempf;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4];
#endif

        // push current stick to temporary vector
        vec1.x = fp->input.x620_lstick_x;
        vec1.y = fp->input.x624_lstick_y;
        vec1.z = 0.0f;

        // push stick from zip1 to temporary vector
        vec2.x = fp->mv.pk.unk4.x10.x;
        vec2.y = fp->mv.pk.unk4.x10.y;
        vec2.z = 0.0f;

        // get the angular difference between them
        tempf = lbvector_AngleXY(&vec2, &vec1);

        // if the angular difference > the minimum difference, return 1
        if (tempf > (DEG_TO_RAD * (pika_attr->xA8)))
            return true;

        return false;
    }

    return false;
}

void ftPikachu_80127198(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((u32) fp->x2200_ftcmd_var0 == 1U) {
        if (ftPikachu_80127064(gobj)) {
            fp->x2200_ftcmd_var0 = 0;
            fp->mv.pk.unk4.x8 = 1;
            ftPikachu_80126C0C(gobj);
            return;
        }
        fp->x2200_ftcmd_var0 = 2;
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8008A2BC(gobj);
    }
}

void ftPikachu_80127228(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1) {
        if (ftPikachu_80127064(gobj)) {
            fp->x2200_ftcmd_var0 = 0;
            fp->mv.pk.unk4.x8 = 1;
            ftPikachu_80126E1C(gobj);
        } else {
            fp->x2200_ftcmd_var0 = 2;
        }
    } else if (!ftAnim_IsFramesRemaining(gobj)) {
        func_80096900(gobj, 1, 0, 1, sa->xAC, sa->xB0);
    }
}

void ftPikachu_Stub_801272D8(HSD_GObj* arg0) {}

void ftPikachu_Stub_801272DC(HSD_GObj* arg0) {}

void ftPikachu_801272E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0)
        func_80084F3C(gobj);
}

void ftPikachu_80127310(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0) {
        ftCommon_8007D4B8(fp);
        ftCommon_8007D440(fp, sa->x9C * fp->x110_attr.x17C_AerialDriftMax);
    } else {
        fp->x80_self_vel.y -= (fp->x80_self_vel.y / 9.0f);
        ftCommon_8007CEF4(fp);
    }
}

void ftPikachu_8012738C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    /// @todo Eliminate cast (by changing type of
    ///       #ftPikachuAttributes::height_attributes)
    ftCollisionBox* box = (ftCollisionBox*) &pika_attr->height_attributes;

    if (!func_80082888(gobj, box))
        ftPikachu_ActionChange_8012744C(gobj);
}

void ftPikachu_801273D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    /// @todo Eliminate cast (by changing type of
    ///       #ftPikachuAttributes::height_attributes)
    ftCollisionBox* box = (ftCollisionBox*) &pika_attr->height_attributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (func_8008239C(gobj, fp->facing_dir, (f32*) box)) {
        func_800D5CB0(gobj, 0, pika_attr->xB0);
    } else if (!ftCliffCommon_80081298(gobj)) {
        /// @todo Fix weird control flow.
        return;
    };
}

void ftPikachu_ActionChange_8012744C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x166, 0xC4C508A, 0,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChangeUpdateVel_801274AC(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftPikachuAttributes* pika_attr;
    Fighter* fp = GET_FIGHTER(gobj);
    pika_attr = fp->x2D4_specialAttributes;
    fp->mv.pk.unk4.x1C.x = fp->x80_self_vel.x;
    fp->mv.pk.unk4.x1C.y = fp->x80_self_vel.y;
    fp->mv.pk.unk4.x24 = fp->gr_vel;

    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
    fp->gr_vel = 0.0f;
    fp->gr_vel = fp->mv.pk.unk4.x24 * pika_attr->xA4;
    Fighter_ChangeMotionState(gobj, 0x163, 2, 0, 0.0f, 1.0f, 0.0f);
    fp->cb.x21F8_callback = &ftPikachu_UpdateVel_80125D80;
}

void ftPikachu_ActionChangeUpdateVel_80127534(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftPikachuAttributes* pika_attr;
    Fighter* fp = GET_FIGHTER(gobj);
    pika_attr = fp->x2D4_specialAttributes;
    fp->mv.pk.unk4.x1C.x = fp->x80_self_vel.x;
    fp->mv.pk.unk4.x1C.y = fp->x80_self_vel.y;
    fp->mv.pk.unk4.x24 = fp->gr_vel;

    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
    fp->gr_vel = 0.0f;
    fp->x80_self_vel.x = fp->mv.pk.unk4.x1C.x * pika_attr->xA4;
    fp->x80_self_vel.y = fp->mv.pk.unk4.x1C.y * pika_attr->xA4;
    Fighter_ChangeMotionState(gobj, 0x166, 2, 0, 0.0f, 1.0f, 0.0f);
    fp->cb.x21F8_callback = &ftPikachu_UpdateVel_80125D80;
}
