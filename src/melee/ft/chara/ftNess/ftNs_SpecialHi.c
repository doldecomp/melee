#include "ftNs_SpecialHi.h"

#include "ftNs_Init.h"

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
#include "ftCommon/ftCo_DownBound.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftNess/types.h"
#include "it/items/itnesspkthunderball.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

// SpecialHi/SpecialAirHi (PK Thunder)
#define FTNESS_SPECIALHI_COLL_FLAG                                            \
    Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |                 \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

// SpecialHi Jibaku (PK Thunder 2 Self-Hit)
#define FTNESS_JIBAKU_COLL_FLAG                                               \
    Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |   \
        Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |                   \
        Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27

// Setup float order
static float return_float1(void) // -25264
{
    return 5.0f;
}

static float return_float2(void) // -25260
{
    return 0.0f;
}

static float return_float3(void) // -25256
{
    return 8.333333015441895f;
}

static float return_float4(void) // -25252
{
    return 12.333333015441895f;
}

static float return_float5(void) // -25248
{
    return M_PI / 2;
}

static f64 return_float6(void) // -25236
{
    return 2 * M_PI;
}

static f64 return_float7(void) // -25228
{
    return M_PI;
}

static f64 return_float8(void) // -25220
{
    return M_PI / 2;
}

static float return_float9(void) // -25216
{
    return 1.0f;
}

static f64 return_float10(void) // -25208
{
    return 0.0;
}

static float return_float12(void) // -25200
{
    return M_PI / 180;
}

static float return_float13(void)
{
    return 90.0f;
}

static float return_float14(void)
{
    return -1.0f;
}

static float return_float15(void)
{
    return 0.5f;
}

static f64 return_float16(void)
{
    return 0.5;
}

static f64 return_float17(void)
{
    return 3.0;
}

static float return_float18(void)
{
    return 1e-4F;
}

static float return_float19(void)
{
    return -1e-4F;
}

static f64 return_float20(void)
{
    return -M_PI / 2;
}

#pragma push
#pragma dont_inline on
// 0x80117B70
// https://decomp.me/scratch/242L6
void ftNs_SpecialHiStopGFX(HSD_GObj* gobj) // Removes GFX
{
    s32 msid;
    Fighter* fp;

    fp = gobj->user_data;
    msid = fp->motion_id;
    switch (msid) {
    case ftNs_MS_SpecialHiStart:
    case ftNs_MS_SpecialHiHold:
    case ftNs_MS_SpecialHiEnd:
    case ftNs_MS_SpecialHi:
    case ftNs_MS_SpecialAirHiStart:
    case ftNs_MS_SpecialAirHiHold:
    case ftNs_MS_SpecialAirHiEnd:
    case ftNs_MS_SpecialAirHi:
    case ftNs_MS_SpecialAirHiRebound:
        efLib_DestroyAll(gobj);
        fp->fv.ns.pkthunder_gfx = false;
    default:
        return;
    }
}
#pragma pop

inline bool check_distance(Vec3* pos, Vec2* pair)
{
    if ((ABS(pos->x - pair->x) < 8.333333015441895f) &&
        (ABS(pos->y - pair->y) < 12.333333015441895f))
    {
        return true;
    }
    return false;
}

// 0x80117BBC
// https://decomp.me/scratch/xTtbs // Very confusing and fabricated match based
// on auto-decomp // https://decomp.me/scratch/hwphL // Proper match
bool ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj)
{
    u8 unused0[8];

    Vec2 pair;
    Vec3 pos;

    u8 unused1[12];

    Vec2 pair2;
    Vec3 pos2;

    u8 unused2[36];

    Fighter* fp = GET_FIGHTER(gobj);
    s32 ret = false;

    if (!fp->fv.ns.pkthunder_gobj) {
        return false;
    }

    switch (fp->mv.ns.specialhi.thunderColl) {
    case 0:
        pos = fp->cur_pos;
        pos.y += 5.0f * fp->x34_scale.y;
        it_802AB3F0(fp->fv.ns.pkthunder_gobj, &pair, 0);
        if (check_distance(&pos, &pair) == true) {
            fp->mv.ns.specialhi.thunderColl = 2;
            it_802AB3F0(fp->fv.ns.pkthunder_gobj,
                        &fp->mv.ns.specialhi.collPos1, 0);
            it_802AB3F0(fp->fv.ns.pkthunder_gobj,
                        &fp->mv.ns.specialhi.collPos2, 1);
            ret = true;
        }
        break;

    case 1:
        pos2 = fp->cur_pos;
        pos2.y += 5.0f * fp->x34_scale.y;
        it_802AB3F0(fp->fv.ns.pkthunder_gobj, &pair2, 0);
        if (!check_distance(&pos2, &pair2)) {
            fp->mv.ns.specialhi.thunderColl = 0;
        }
    }
    return ret;
}

/// Checks if Ness is in SpecialHiHold/SpecialAirHiHold
/// (PK Thunder control loop)
bool ftNs_SpecialHi_CheckSpecialHiHold(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    return fp->motion_id == ftNs_MS_SpecialHiHold ||
                   fp->motion_id == ftNs_MS_SpecialAirHiHold
               ? true
               : false;
}

// 0x80117DD4
// https://decomp.me/scratch/e00Cp
void ftNs_SpecialHi_ItemPKThunderRemove(HSD_GObj* gobj) // OnTakeDamage?
{
    Fighter* fp;
    Fighter* temp_fp;
    s32 msid;

    temp_fp = gobj->user_data;
    if (temp_fp->fv.ns.pkthunder_gobj != NULL) {
        temp_fp->fv.ns.pkthunder_gobj = NULL;
    }
    fp = GET_FIGHTER(gobj);
    msid = fp->motion_id;
    switch (msid) {
    case ftNs_MS_SpecialHiStart:
    case ftNs_MS_SpecialHiHold:
    case ftNs_MS_SpecialHiEnd:
    case ftNs_MS_SpecialHi:
    case ftNs_MS_SpecialAirHiStart:
    case ftNs_MS_SpecialAirHiHold:
    case ftNs_MS_SpecialAirHiEnd:
    case ftNs_MS_SpecialAirHi:
    case ftNs_MS_SpecialAirHiRebound:
        efLib_DestroyAll(gobj);
        fp->fv.ns.pkthunder_gfx = false;

    default:
        temp_fp->death2_cb = NULL;
        temp_fp->take_dmg_cb = NULL;
        ftParts_8007592C(temp_fp, 0, 0.0f);
    }
}

// 0x80117E60
// https://decomp.me/scratch/MTTJq
void ftNs_SpecialHi_TakeDamage(HSD_GObj* gobj) // OnTakeDamage again?
{
    s32 msid;
    Fighter* fp;
    Fighter* fighter_data2;
    Fighter* temp_fp;

    temp_fp = gobj->user_data;
    fp = temp_fp;
    if (temp_fp->fv.ns.pkthunder_gobj != NULL) {
        it_802AB9C0(temp_fp->fv.ns.pkthunder_gobj);
        fp->fv.ns.pkthunder_gobj = NULL;
    }
    fighter_data2 = GET_FIGHTER(gobj);
    msid = fighter_data2->motion_id;
    switch (msid) {
    case ftNs_MS_SpecialHiStart:
    case ftNs_MS_SpecialHiHold:
    case ftNs_MS_SpecialHiEnd:
    case ftNs_MS_SpecialHi:
    case ftNs_MS_SpecialAirHiStart:
    case ftNs_MS_SpecialAirHiHold:
    case ftNs_MS_SpecialAirHiEnd:
    case ftNs_MS_SpecialAirHi:
    case ftNs_MS_SpecialAirHiRebound:
        efLib_DestroyAll(gobj);
        fighter_data2->fv.ns.pkthunder_gfx = false;
    default:
        temp_fp->death2_cb = NULL;
        temp_fp->take_dmg_cb = NULL;
        ftParts_8007592C(temp_fp, 0, 0.0f);
    }
}

// 0x80117F00
// https://decomp.me/scratch/1nlBY
// Run from PK Thunder's OnReflect callback. Sets Ness's reference to PK
// Thunder to NULL if he is reflecting his own PK Thunder.
void ftNs_SpecialHi_ItemPKThunderCheckOwn(HSD_GObj* gobj,
                                          HSD_GObj* thunder_gobj)
{
    HSD_GObj* temp_thunder;
    Fighter* temp_fp = GET_FIGHTER(gobj);

    temp_thunder = temp_fp->fv.ns.pkthunder_gobj;
    if ((temp_thunder != NULL) && (temp_thunder == thunder_gobj)) {
        temp_fp->fv.ns.pkthunder_gobj = NULL;
    }
}

// 0x80117F24
// https://decomp.me/scratch/3URl3
static void ftNs_SpecialAirHi_CollisionModVel(
    HSD_GObj* gobj,
    CollData* coll_data) // Adjusts Ness's velocity upon interacting with
                         // collisions during SpecialAirHi
{
    Vec3 sp14;
    Fighter* fp;
    float phi_f1;
    float phi_f3;

    fp = GET_FIGHTER(gobj);
    while (fp->mv.ns.specialhi.aerialVel < 0.0f) {
        fp->mv.ns.specialhi.aerialVel += 2 * M_PI;
    }
    while (fp->mv.ns.specialhi.aerialVel > 2 * M_PI) {
        fp->mv.ns.specialhi.aerialVel -= 2 * M_PI;
    }
    if (coll_data->env_flags & Collide_LeftWallMask) {
        phi_f1 = atan2f(coll_data->left_facing_wall.normal.y,
                        coll_data->left_facing_wall.normal.x);
        while (phi_f1 < 0.0f) {
            phi_f1 += 2 * M_PI;
        }

        while (phi_f1 > 2 * M_PI) {
            phi_f1 -= 2 * M_PI;
        }
        phi_f3 = M_PI + fp->mv.ns.specialhi.aerialVel;

        while (phi_f3 < 0.0f) {
            phi_f3 += 2 * M_PI;
        }

        while (phi_f3 > 2 * M_PI) {
            phi_f3 -= 2 * M_PI;
        }
        if ((phi_f3 - phi_f1) < 0.0f) {
            phi_f1 += M_PI / 2;
        } else {
            phi_f1 -= M_PI / 2;
        }
    }
    if (coll_data->env_flags & Collide_RightWallMask) {
        phi_f1 = atan2f(coll_data->right_facing_wall.normal.y,
                        coll_data->right_facing_wall.normal.x);
        phi_f3 = M_PI + phi_f1;

        while (phi_f3 < 0.0f) {
            phi_f3 += 2 * M_PI;
        }

        while (phi_f3 > 2 * M_PI) {
            phi_f3 -= 2 * M_PI;
        }
        if ((fp->mv.ns.specialhi.aerialVel - phi_f3) < 0.0f) {
            phi_f1 += M_PI / 2;
        } else {
            phi_f1 -= M_PI / 2;
        }
    }
    sp14.y = 0.0f;
    sp14.x = 0.0f;
    sp14.z = 1.0f;
    lbVector_RotateAboutUnitAxis(&fp->self_vel, &sp14,
                                 phi_f1 - fp->mv.ns.specialhi.aerialVel);
    fp->mv.ns.specialhi.aerialVel = atan2f(fp->self_vel.y, fp->self_vel.x);
}

// 0x80118120
// https://decomp.me/scratch/ARLRd
void ftNs_SpecialHiStart_Enter(HSD_GObj* gobj) // Ness's grounded PK Thunder
                                               // Start Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr = fp->dat_attrs;

    u8 _[4];

    ftNessAttributes* temp_attr;
    f64 phi_f0;

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiStart, 0, 0.0f, 1.0f,
                              0.0f, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;

    {
        Fighter* temp_fp;
        temp_fp = gobj->user_data;
        temp_attr = getFtSpecialAttrs(temp_fp);
        temp_fp->mv.ns.specialhi.thunderTimerLoop1 =
            (s32) temp_attr->x40_PK_THUNDER_LOOP1;
        temp_fp->mv.ns.specialhi.thunderTimerLoop2 =
            (s32) temp_attr->x44_PK_THUNDER_LOOP2;
        temp_fp->mv.ns.specialhi.gravityDelay =
            (s32) temp_attr->x48_PK_THUNDER_GRAVITY_DELAY;
        {
            float temp_f1_2 = 0.0f;
        }
        temp_fp->mv.ns.specialhi.fallAccel = 0.0f;
        temp_fp->mv.ns.specialhi.unkVector1.z = 0.0f;
        temp_fp->mv.ns.specialhi.unkVector1.y = 0.0f;
        temp_fp->mv.ns.specialhi.unkVector1.x = 0.0f;
        temp_fp->mv.ns.specialhi.unkVar4 = 0.0f;
        temp_fp->mv.ns.specialhi.unkVar3 = 0.0f;
        temp_fp->death2_cb = NULL;
        temp_fp->take_dmg_cb = NULL;
        ftParts_8007592C(temp_fp, 0, 0.0f);
        fp->mv.ns.specialhi.thunderColl = 1;
        fp->mv.ns.specialhi.gravityDelay =
            (s32) ness_attr->x48_PK_THUNDER_GRAVITY_DELAY;
        fp->mv.ns.specialhi.jibakuGFX = 0;
        fp->mv.ns.specialhi.collPos1.x = 0.0f;
        fp->mv.ns.specialhi.collPos1.x = 0.0f;
        fp->mv.ns.specialhi.collPos1.x = 0.0f;
        fp->mv.ns.specialhi.collPos2.x = 0.0f;
        fp->mv.ns.specialhi.collPos2.x = 0.0f;
        fp->mv.ns.specialhi.collPos2.x = 0.0f;
        if (1.0f == fp->facing_dir) {
            phi_f0 = (f64) 0.0;
        } else {
            phi_f0 = M_PI;
        }
        fp->mv.ns.specialhi.aerialVel = (float) phi_f0;
        fp->mv.ns.specialhi.facingDir = (float) 1.0f;
        fp->mv.ns.specialhi.unkVar = (float) 0.0f;
        ftAnim_8006EBA4(gobj);
    }
}

// 0x80118250
// https://decomp.me/scratch/D08nX
void ftNs_SpecialAirHiStart_Enter(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Start Motion State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;
    Fighter* temp_fp;
    ftNessAttributes* temp_attr;
    f64 phi_f0;

    u8 _[12];
    {
        float _ = 0.0f;
    }
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiStart, 0, 0.0f, 1.0f,
                              0.0f, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    temp_fp = gobj->user_data;
    temp_attr = temp_fp->dat_attrs;
    temp_fp->mv.ns.specialhi.thunderTimerLoop1 =
        (s32) temp_attr->x40_PK_THUNDER_LOOP1;
    temp_fp->mv.ns.specialhi.thunderTimerLoop2 =
        (s32) temp_attr->x44_PK_THUNDER_LOOP2;
    temp_fp->mv.ns.specialhi.gravityDelay =
        (s32) temp_attr->x48_PK_THUNDER_GRAVITY_DELAY;
    {
        float _ = 0.0f;
    }
    temp_fp->mv.ns.specialhi.fallAccel = 0.0f;
    temp_fp->mv.ns.specialhi.unkVector1.z = 0.0f;
    temp_fp->mv.ns.specialhi.unkVector1.y = 0.0f;
    temp_fp->mv.ns.specialhi.unkVector1.x = 0.0f;
    temp_fp->mv.ns.specialhi.unkVar4 = 0.0f;
    temp_fp->mv.ns.specialhi.unkVar3 = 0.0f;
    temp_fp->death2_cb = NULL;
    temp_fp->take_dmg_cb = NULL;
    ftParts_8007592C(temp_fp, 0, 0.0f);
    fp->mv.ns.specialhi.thunderColl = 1;
    fp->mv.ns.specialhi.gravityDelay =
        (s32) ness_attr->x48_PK_THUNDER_GRAVITY_DELAY;
    fp->mv.ns.specialhi.jibakuGFX = false;
    fp->mv.ns.specialhi.collPos1.x = 0.0f;
    fp->mv.ns.specialhi.collPos1.x = 0.0f;
    fp->mv.ns.specialhi.collPos1.x = 0.0f;
    fp->mv.ns.specialhi.collPos2.x = 0.0f;
    fp->mv.ns.specialhi.collPos2.x = 0.0f;
    fp->mv.ns.specialhi.collPos2.x = 0.0f;
    if (1.0f == fp->facing_dir) {
        phi_f0 = (f64) 0.0;
    } else {
        phi_f0 = M_PI;
    }
    fp->mv.ns.specialhi.aerialVel = (float) phi_f0;
    fp->mv.ns.specialhi.facingDir = (float) 1.0f;
    fp->mv.ns.specialhi.unkVar = (float) 0.0f;
    fp->self_vel.y = 0.0f;
    ftAnim_8006EBA4(gobj);
}

/// @todo Rewrite this.
void ftNs_SpecialHi_Enter(
    HSD_GObj* gobj) // Ness's grounded PK Thunder 2 Motion State handler
{
    /// @todo Try to move these close to usage
    Vec3 sp40;
    ftNessAttributes* ness_attr2;
    Fighter* fighter_data2;

    u8 _[8];
    Fighter* fighter_data3;

    Fighter* fp = getFighter(gobj);
    ftNessAttributes* ness_attr = fp->dat_attrs;
    if ((fp->coll_data.floor.flags & LINE_FLAG_PLATFORM) == 0) {
        float temp_f3 = 5.0f;
        float temp_f1;
        float temp_f2;

        sp40.x = fp->cur_pos.x - fp->mv.ns.specialhi.collPos1.x;
        temp_f2 = fp->x34_scale.y;
        temp_f1 = (temp_f3 * temp_f2) + fp->cur_pos.y;
        sp40.y = temp_f1 - fp->mv.ns.specialhi.collPos1.y;
        sp40.z = 0.0f;

        {
            float temp_f1_2 =
                lbVector_Angle(&fp->coll_data.floor.normal, &sp40);

            if (!(temp_f1_2 < (float) M_PI_2)) {
                if (!(temp_f1_2 >
                      deg_to_rad *
                          (90.0f +
                           ness_attr->x60_PK_THUNDER_2_KNOCKDOWN_ANGLE)))
                {
                    {
                        float facing_dir;
                        if (sp40.x >= 0) {
                            facing_dir = +1;
                        } else {
                            facing_dir = -1;
                        }
                        fp->facing_dir = facing_dir;
                    }

                    {
                        float facing_dir;
                        if (sp40.y >= 0) {
                            facing_dir = +1;
                        } else {
                            facing_dir = -1;
                        }
                        fp->mv.ns.specialhi.facingDir = facing_dir;
                    }

                    fp->mv.ns.specialhi.aerialVel = atan2f(sp40.y, sp40.x);
                    {
                        u8 _[4];

                        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHi, 0,
                                                  0.0f, 1.0f, 0.0f, NULL);
                        fp->gr_vel =
                            (float) (ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                                     fp->facing_dir);
                        fp = getFighter(gobj);
                        ness_attr2 = getFtSpecialAttrs(fp);
                        fp->mv.ns.specialhi.unkVar =
                            (float) ness_attr2->x58_PK_THUNDER_2_UNK1;
                        fighter_data2 = GET_FIGHTER(gobj);
                        ftParts_8007592C(fighter_data2, 0,
                                         (fighter_data2->facing_dir *
                                          atan2f(fighter_data2->self_vel.x,
                                                 fighter_data2->self_vel.y)) -
                                             1.5707963705062866f);
                        fighter_data2 = fp;
                        fighter_data2->death2_cb = NULL;
                        fighter_data2->take_dmg_cb = NULL;
                        fighter_data2->x1968_jumpsUsed =
                            fighter_data2->co_attrs.max_jumps;
                        return;
                    }
                }
                goto block_stuff;
            }
        }
    }
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    ftCommon_8007D60C(fp);
    ftNs_SpecialAirHi_Enter(gobj);
    return;

block_stuff: {
    fighter_data3 = fighter_data3 = GET_FIGHTER(gobj);
    {
        enum_t msid = fighter_data3->motion_id;
        switch (msid) {
        case ftNs_MS_SpecialHiStart:
        case ftNs_MS_SpecialHiHold:
        case ftNs_MS_SpecialHiEnd:
        case ftNs_MS_SpecialHi:
        case ftNs_MS_SpecialAirHiStart:
        case ftNs_MS_SpecialAirHiHold:
        case ftNs_MS_SpecialAirHiEnd:
        case ftNs_MS_SpecialAirHi:
        case ftNs_MS_SpecialAirHiRebound:
            efLib_DestroyAll(gobj);
            fighter_data3->fv.ns.pkthunder_gfx = false;
        default:
            ftParts_8007592C(fp, 0, 0.0f);
            ftCo_80097D40(gobj);
            return;
        }
    }
}
}

inline void
NessFloatMath_PKThunder2(HSD_GObj* gobj) // Required for 0x80118570 to match
{
    Fighter* fp;
    ftNessAttributes* ness_attr;
    float temp_f2;
    float temp_f1;
    float phi_f0;

    fp = getFighter(gobj);
    temp_f2 = fp->cur_pos.x - fp->mv.ns.specialhi.collPos1.x;
    ness_attr = getFtSpecialAttrs(fp);
    temp_f1 = ((5.0f * fp->x34_scale.y) + fp->cur_pos.y) -
              fp->mv.ns.specialhi.collPos1.y;
    if (temp_f2 >= 0.0f) {
        phi_f0 = 1.0f;
    } else {
        phi_f0 = -1.0f;
    }
    fp->facing_dir = phi_f0;
    if (temp_f1 >= 0.0f) {
        phi_f0 = 1.0f;
    } else {
        phi_f0 = -1.0f;
    }
    fp->mv.ns.specialhi.facingDir = phi_f0;
    fp->mv.ns.specialhi.aerialVel = atan2f(temp_f1, temp_f2);
    fp->self_vel.x = (float) (ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                              cosf(fp->mv.ns.specialhi.aerialVel));
    fp->self_vel.y = (float) (ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                              sinf(fp->mv.ns.specialhi.aerialVel));
}

/// Ness's PK Thunder 2 Motion State handler if Ness is launching into
/// SpecialAirHi from SpecialHiHold
void ftNs_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    ftNessAttributes* temp_attr;
    Fighter* fighter_data3;
    Fighter* fighter_data2;

    u8 _[20];

    NessFloatMath_PKThunder2(gobj);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHi, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    fighter_data2 = GET_FIGHTER(gobj);
    temp_attr = getFtSpecialAttrs(fighter_data2);
    fighter_data2->mv.ns.specialhi.unkVar = temp_attr->x58_PK_THUNDER_2_UNK1;
    fighter_data3 = GET_FIGHTER(gobj);
    ftParts_8007592C(
        fighter_data3, 0,
        (fighter_data3->facing_dir *
         atan2f(fighter_data3->self_vel.x, fighter_data3->self_vel.y)) -
            (float) M_PI_2);
    fighter_data2->death2_cb = NULL;
    fighter_data2->take_dmg_cb = NULL;
    fighter_data2->x1968_jumpsUsed = fighter_data2->co_attrs.max_jumps;
}

/// PK Thunder Grounded Startup Animation
void ftNs_SpecialHiStart_Anim(HSD_GObj* gobj)
{
    Vec3 pkt_pos;

    u8 _[32];

    Fighter* fp = gobj->user_data;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiHold, 0, 0.0f, 1.0f,
                                  0.0f, NULL);

        {
            Fighter* fighter_data2 = gobj->user_data;
            HSD_GObj* pkt_ptr = fighter_data2->fv.ns.pkthunder_gobj;
            if (pkt_ptr == NULL) {
                lb_8000B1CC(fighter_data2->parts[FtPart_L2ndNa].joint, NULL,
                            &pkt_pos);

                pkt_pos.z = 0.0f;

                pkt_ptr =
                    it_802AB58C(gobj, &pkt_pos, fighter_data2->facing_dir);

                fighter_data2->fv.ns.pkthunder_gobj = pkt_ptr;

                if (pkt_ptr != NULL) {
                    fighter_data2->death2_cb = ftNs_Init_OnDamage;
                    fighter_data2->take_dmg_cb = ftNs_Init_OnDamage;
                }
            }
        }

        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;

        fp = gobj->user_data;

        ftNs_SpecialHiStopGFX(gobj);

        efSync_Spawn(1262, gobj, fp->parts[FtPart_HipN].joint);

        fp->fv.ns.pkthunder_gfx = true;
    }
}

// 0x801187A4
// https://decomp.me/scratch/Xm3tt
void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj) // Ness's grounded PK Thunder
                                             // Control Loop Animation callback
{
    s32 msid;
    s32 ASID2;
    s32 thunderTimer;
    s32 thunderTimer2;
    Fighter* fp;
    Fighter* fighter_data2;
    Fighter* fighter_data3;

    fp = gobj->user_data;
    thunderTimer = fp->mv.ns.specialhi.thunderTimerLoop1;
    if (thunderTimer > 0) {
        fp->mv.ns.specialhi.thunderTimerLoop1 = (s32) (thunderTimer - 1);
    }
    if (fp->fv.ns.pkthunder_gobj == NULL) {
        thunderTimer2 = fp->mv.ns.specialhi.thunderTimerLoop2;
        if (thunderTimer2 > 0) {
            fp->mv.ns.specialhi.thunderTimerLoop2 = (s32) (thunderTimer2 - 1);
        }
    }
    if (fp->fv.ns.pkthunder_gobj == NULL) {
        if (((s32) fp->mv.ns.specialhi.thunderTimerLoop1 <= 0) &&
            ((s32) fp->mv.ns.specialhi.thunderTimerLoop2 <= 0))
        {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiEnd, 0, 0.0f,
                                      1.0f, 0.0f, NULL);
            fighter_data2 = gobj->user_data;
            msid = fighter_data2->motion_id;
            switch (msid) {
            case ftNs_MS_SpecialHiStart:
            case ftNs_MS_SpecialHiHold:
            case ftNs_MS_SpecialHiEnd:
            case ftNs_MS_SpecialHi:
            case ftNs_MS_SpecialAirHiStart:
            case ftNs_MS_SpecialAirHiHold:
            case ftNs_MS_SpecialAirHiEnd:
            case ftNs_MS_SpecialAirHi:
            case ftNs_MS_SpecialAirHiRebound:
                efLib_DestroyAll(gobj);
                fighter_data2->fv.ns.pkthunder_gfx = false;
            }
        }
    } else if (it_802AB568(fp->fv.ns.pkthunder_gobj) == gobj) {
        if (ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(gobj) == true) {
            ftNs_SpecialHi_Enter(gobj);
        }
    } else {
        fp->fv.ns.pkthunder_gobj = NULL;
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiEnd, 0, 0.0f, 1.0f,
                                  0.0f, NULL);
        fighter_data3 = gobj->user_data;
        ASID2 = fighter_data3->motion_id;
        switch (ASID2) {
        case ftNs_MS_SpecialHiStart:
        case ftNs_MS_SpecialHiHold:
        case ftNs_MS_SpecialHiEnd:
        case ftNs_MS_SpecialHi:
        case ftNs_MS_SpecialAirHiStart:
        case ftNs_MS_SpecialAirHiHold:
        case ftNs_MS_SpecialAirHiEnd:
        case ftNs_MS_SpecialAirHi:
        case ftNs_MS_SpecialAirHiRebound:
            efLib_DestroyAll(gobj);
            fighter_data3->fv.ns.pkthunder_gfx = false;
        }
    }
}

/// Ness's grounded PK Thunder End Animation callback
void ftNs_SpecialHiEnd_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// Ness's grounded PK Thunder 2 Animation callback
void ftNs_SpecialHi_Anim(HSD_GObj* gobj)
{
    u8 _[4];

    {
        Fighter* temp_fp = gobj->user_data;
        temp_fp->mv.ns.specialhi.jibakuGFX =
            temp_fp->mv.ns.specialhi.jibakuGFX + 1;

        if (temp_fp->mv.ns.specialhi.jibakuGFX == 1) {
            Fighter* fp = gobj->user_data;
            ftNs_SpecialHiStopGFX(gobj);
            efSync_Spawn(1263, gobj, fp->parts[FtPart_HipN].joint);
            fp->fv.ns.pkthunder_gfx = true;
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiEnd, 0, 0.0f, 1.0f,
                                  0.0f, NULL);
        {
            Fighter* fp = gobj->user_data;
            enum_t msid = fp->motion_id;

            switch (msid) {
            case ftNs_MS_SpecialHiStart:
            case ftNs_MS_SpecialHiHold:
            case ftNs_MS_SpecialHiEnd:
            case ftNs_MS_SpecialHi:
            case ftNs_MS_SpecialAirHiStart:
            case ftNs_MS_SpecialAirHiHold:
            case ftNs_MS_SpecialAirHiEnd:
            case ftNs_MS_SpecialAirHi:
            case ftNs_MS_SpecialAirHiRebound:
                efLib_DestroyAll(gobj);
                fp->fv.ns.pkthunder_gfx = false;
            }
        }
    }
}

/// Ness's aerial PK Thunder Start Animation callback
void ftNs_SpecialAirHiStart_Anim(HSD_GObj* gobj)
{
    Vec3 pkt_pos;

    u8 _[32];

    HSD_GObj* pkt_ptr;
    Fighter* fp = gobj->user_data;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiHold, 0, 0.0f,
                                  1.0f, 0.0f, NULL);

        {
            Fighter* fp2 = gobj->user_data;
            pkt_ptr = fp2->fv.ns.pkthunder_gobj;

            if (pkt_ptr == 0) {
                lb_8000B1CC(fp2->parts[FtPart_L2ndNa].joint, NULL, &pkt_pos);

                pkt_pos.z = 0.0f;

                pkt_ptr = it_802AB58C(gobj, &pkt_pos, fp2->facing_dir);

                fp2->fv.ns.pkthunder_gobj = pkt_ptr;

                if (pkt_ptr != NULL) {
                    fp2->death2_cb = ftNs_Init_OnDamage;
                    fp2->take_dmg_cb = ftNs_Init_OnDamage;
                }
            }
        }

        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;

        fp = gobj->user_data;

        ftNs_SpecialHiStopGFX(gobj);

        efSync_Spawn(1262, gobj, fp->parts[FtPart_HipN].joint);

        fp->fv.ns.pkthunder_gfx = true;
    }
}

/// Ness's aerial PK Thunder Control Loop Animation callback
void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj)
{
    u8 _[44];

    Fighter* fp0 = gobj->user_data;

    {
        int pkt_timer0 = fp0->mv.ns.specialhi.thunderTimerLoop1;
        if (pkt_timer0 > 0) {
            fp0->mv.ns.specialhi.thunderTimerLoop1 = (s32) (pkt_timer0 - 1);
        }
    }

    if (fp0->fv.ns.pkthunder_gobj == NULL) {
        int pkt_timer1 = fp0->mv.ns.specialhi.thunderTimerLoop2;

        if (pkt_timer1 > 0) {
            fp0->mv.ns.specialhi.thunderTimerLoop2 = (s32) (pkt_timer1 - 1);
        }
    }

    if (fp0->fv.ns.pkthunder_gobj == NULL) {
        if (fp0->mv.ns.specialhi.thunderTimerLoop1 <= 0 &&
            fp0->mv.ns.specialhi.thunderTimerLoop2 <= 0)
        {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiEnd, 0, 0, 1,
                                      0, NULL);
            {
                Fighter* fp1 = gobj->user_data;
                enum_t msid = fp1->motion_id;
                switch (msid) {
                case ftNs_MS_SpecialHiStart:
                case ftNs_MS_SpecialHiHold:
                case ftNs_MS_SpecialHiEnd:
                case ftNs_MS_SpecialHi:
                case ftNs_MS_SpecialAirHiStart:
                case ftNs_MS_SpecialAirHiHold:
                case ftNs_MS_SpecialAirHiEnd:
                case ftNs_MS_SpecialAirHi:
                case ftNs_MS_SpecialAirHiRebound:
                    efLib_DestroyAll(gobj);
                    fp1->fv.ns.pkthunder_gfx = false;
                }
            }
        }
    } else if (it_802AB568(fp0->fv.ns.pkthunder_gobj) == gobj) {
        if (ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(gobj) == true) {
            NessFloatMath_PKThunder2(gobj);
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHi, 0, 0.0f,
                                      1.0f, 0.0f, NULL);

            {
                Fighter* fp1 = gobj->user_data;

                {
                    ftNessAttributes* temp_attr = fp1->dat_attrs;
                    fp1->mv.ns.specialhi.unkVar =
                        temp_attr->x58_PK_THUNDER_2_UNK1;
                }

                {
                    Fighter* fp4 = gobj->user_data;
                    ftParts_8007592C(
                        fp4, 0,
                        fp4->facing_dir *
                                atan2f(fp4->self_vel.x, fp4->self_vel.y) -
                            (float) M_PI_2);
                }

                fp1->death2_cb = NULL;
                fp1->take_dmg_cb = NULL;
                fp1->x1968_jumpsUsed = fp1->co_attrs.max_jumps;
            }
        }
    } else {
        fp0->fv.ns.pkthunder_gobj = NULL;
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiEnd, 0, 0.0f, 1.0f,
                                  0.0f, NULL);
        {
            Fighter* fp1 = gobj->user_data;
            enum_t msid = fp1->motion_id;
            switch (msid) {
            case ftNs_MS_SpecialHiStart:
            case ftNs_MS_SpecialHiHold:
            case ftNs_MS_SpecialHiEnd:
            case ftNs_MS_SpecialHi:
            case ftNs_MS_SpecialAirHiStart:
            case ftNs_MS_SpecialAirHiHold:
            case ftNs_MS_SpecialAirHiEnd:
            case ftNs_MS_SpecialAirHi:
            case ftNs_MS_SpecialAirHiRebound:
                efLib_DestroyAll(gobj);
                fp1->fv.ns.pkthunder_gfx = false;
            }
        }
    }
}

/// Ness's aerial PK Thunder End Animation callback
void ftNs_SpecialAirHiEnd_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = gobj->user_data;
    ftNessAttributes* ness_attr = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
        ftCommon_8007D60C(fp);

        if (ness_attr->x70_PK_THUNDER_2_LANDING_LAG == 0) {
            ftCo_Fall_Enter(gobj);
            return;
        }

        ftCo_800969D8(gobj, 1, 0, 1, 1,
                      ness_attr->x70_PK_THUNDER_2_LANDING_LAG,
                      ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
    }
}

/// Ness's aerial PK Thunder 2 Animation callback
void ftNs_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp0;
    Fighter* fp1 = gobj->user_data;
    ftNessAttributes* ness_attr = fp1->dat_attrs;

    fp1->mv.ns.specialhi.jibakuGFX = fp1->mv.ns.specialhi.jibakuGFX + 1;
    if (fp1->mv.ns.specialhi.jibakuGFX == 1) {
        fp0 = gobj->user_data;
        ftNs_SpecialHiStopGFX(gobj);
        efSync_Spawn(1263, gobj, fp0->parts[FtPart_HipN].joint);
        fp0->fv.ns.pkthunder_gfx = true;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        float temp_f1 = fp1->mv.ns.specialhi.fallAccel;
        float phi_f1 = temp_f1;

        if (temp_f1 < 0) {
            phi_f1 = -temp_f1;
        }

        fp1->self_vel.y = (float) -phi_f1;
        ftCommon_8007D60C(fp1);

        if (ness_attr->x70_PK_THUNDER_2_LANDING_LAG == 0) {
            ftCo_Fall_Enter(gobj);
            return;
        }

        ftCo_800969D8(gobj, 1, 0, 1, 1,
                      ness_attr->x70_PK_THUNDER_2_LANDING_LAG,
                      ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
    }
}

/// Ness's PK Thunder 2 Wall Rebound Animation callback
void ftNs_SpecialAirHiRebound_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp0 = gobj->user_data;

    {
        Fighter* fp1 = fp0;
        ftNessAttributes* ness_attr = fp0->dat_attrs;

        if (!ftAnim_IsFramesRemaining(gobj)) {
            ftCommon_8007D60C(fp1);

            if (ness_attr->x70_PK_THUNDER_2_LANDING_LAG == 0) {
                ftCo_Fall_Enter(gobj);
                return;
            }

            ftCo_800969D8(gobj, 1, 0, 1, 1.0f,
                          ness_attr->x70_PK_THUNDER_2_LANDING_LAG,
                          ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
        }
    }
}

// 0x80118F80
void ftNs_SpecialHiStart_IASA(
    HSD_GObj* gobj) // Ness's PK Thunder IASA callbacks
{
    return;
}

// 0x80118F84
void ftNs_SpecialHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F88
void ftNs_SpecialHiEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F8C
void ftNs_SpecialHi_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F90
void ftNs_SpecialAirHiStart_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F94
void ftNs_SpecialAirHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F98
void ftNs_SpecialAirHiEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F9C
void ftNs_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118FA0
void ftNs_SpecialAirHiRebound_IASA(HSD_GObj* gobj)
{
    return;
}

inline void ThunderPhysTimer(HSD_GObj* gobj)
{
    Fighter* temp_fp;
    s32 thunderPhysTimer;

    temp_fp = gobj->user_data;
    thunderPhysTimer = temp_fp->mv.ns.specialhi.gravityDelay;
    if (thunderPhysTimer != 0) {
        temp_fp->mv.ns.specialhi.gravityDelay = (s32) (thunderPhysTimer - 1);
    }
}

// 0x80118FA4
// https://decomp.me/scratch/5RSqi
void ftNs_SpecialHiStart_Phys(
    HSD_GObj* gobj) // Ness's grounded PK Thunder Start Physics callback
{
    ThunderPhysTimer(gobj);
    ft_80084F3C(gobj);
}

// 0x80118FDC
// https://decomp.me/scratch/3o65K
void ftNs_SpecialHiHold_Phys(HSD_GObj* gobj) // Ness's grounded PK Thunder
                                             // Control Loop Physics callback
{
    ft_80084F3C(gobj);
}

// 0x80118FFC
// This is identical to 0x80118FDC so there's no link bruh
void ftNs_SpecialHiEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

static const float vel_epsilon = 0.0001f;

/// Ness's grounded PK Thunder 2 Physics callback
void ftNs_SpecialHi_Phys(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp0 = gobj->user_data;
    float ground_vel = fp0->gr_vel;
    float vel_y = fp0->self_vel.y;
    ftNessAttributes* ness_attr = fp0->dat_attrs;

    fp0->gr_vel =
        -(ness_attr->x5C_PK_THUNDER_2_DECELERATION_RATE * fp0->facing_dir -
          ground_vel);

    if (fp0->facing_dir == +1) {
        if (fp0->gr_vel <= vel_epsilon) {
            fp0->gr_vel = ground_vel;
        }
    } else if (fp0->gr_vel >= -vel_epsilon) {
        fp0->gr_vel = ground_vel;
    }

    if (fp0->mv.ns.specialhi.facingDir == +1) {
        if (fp0->self_vel.y <= vel_epsilon) {
            fp0->self_vel.y = vel_y;
        }
    } else if (fp0->self_vel.y >= -vel_epsilon) {
        fp0->self_vel.y = vel_y;
    }

    fp0->mv.ns.specialhi.unkVector1 = fp0->self_vel;
    ftCommon_ApplyGroundMovement(gobj);

    {
        Fighter* fp = gobj->user_data;
        ftParts_8007592C(fp, 0,
                         fp->facing_dir *
                                 atan2f(fp->self_vel.x, fp->self_vel.y) -
                             (float) M_PI_2);
    }
}

/// Ness's aerial PK Thunder Start Physics callback
void ftNs_SpecialAirHiStart_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = gobj->user_data;
    int gravity_timer = fp->mv.ns.specialhi.gravityDelay;
    ftNessAttributes* ness_attr = fp->dat_attrs;

    if (gravity_timer != 0) {
        fp->mv.ns.specialhi.gravityDelay = gravity_timer - 1;
    } else {
        ftCommon_Fall(fp, ness_attr->x50_PK_THUNDER_FALL_ACCEL,
                      fp->co_attrs.terminal_vel);
    }

    {
        float friction = fp->co_attrs.aerial_friction;
        ftCommon_ApplyFrictionAir(fp, friction);
    }
}

// 0x80119194
// https://decomp.me/scratch/nvI07
void ftNs_SpecialAirHiHold_Phys(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Control Loop Physics
                    // callback
{
    u8 _[8];

    Fighter* fp = gobj->user_data;
    int gravity_timer = fp->mv.ns.specialhi.gravityDelay;
    ftNessAttributes* ness_attr = fp->dat_attrs;

    if (gravity_timer != 0) {
        fp->mv.ns.specialhi.gravityDelay = gravity_timer - 1;
    } else {
        ftCommon_Fall(fp, ness_attr->x50_PK_THUNDER_FALL_ACCEL,
                      fp->co_attrs.terminal_vel);
    }

    {
        float friction = fp->co_attrs.aerial_friction;
        ftCommon_ApplyFrictionAir(fp, friction);
    }
}

/// Ness's aerial PK Thunder End Physics callback
void ftNs_SpecialAirHiEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = gobj->user_data;
    int gravity_timer = fp->mv.ns.specialhi.gravityDelay;
    ftNessAttributes* ness_attr = fp->dat_attrs;

    if (gravity_timer != 0) {
        fp->mv.ns.specialhi.gravityDelay = gravity_timer - 1;
    } else {
        ftCommon_Fall(fp, ness_attr->x50_PK_THUNDER_FALL_ACCEL,
                      fp->co_attrs.terminal_vel);
    }

    {
        float friction = fp->co_attrs.aerial_friction;
        ftCommon_ApplyFrictionAir(fp, friction);
    }
}

inline void ftNess_atan2(HSD_GObj* gobj)
{
    Fighter* fighter_data2 = GET_FIGHTER(gobj);

    u8 _[4] = { 0 };

    ftParts_8007592C(
        fighter_data2, 0,
        (fighter_data2->facing_dir *
         atan2f(fighter_data2->self_vel.x, fighter_data2->self_vel.y)) -
            (float) M_PI_2);
}

inline void* getFtSpecialAttrs2(Fighter* fp)
{
    u8 _[4] = { 0 };

    return fp->dat_attrs;
}

// Ness's aerial PK Thunder 2 Physics callback
void ftNs_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    float temp_sqrt;
    ftNessAttributes* ness_attr;
    Fighter* fp;
    float temp_f0;
    float temp_f0_2;
    float temp_f1;
    float temp_f1_5;
    float temp_f1_6;
    float temp_f2;

    u8 _[4];

    float phi_f1;
    float phi_f31;
    float temp_fmuls;
    float temp_fmuls2;
    float temp_add;

    fp = getFighter(gobj);
    temp_f2 = fp->self_vel.x;
    temp_f1 = fp->self_vel.y;
    ness_attr = getFtSpecialAttrs2(fp);
    temp_fmuls = temp_f2 * temp_f2;
    temp_fmuls2 = temp_f1 * temp_f1;

    temp_sqrt = sqrtf(temp_fmuls + temp_fmuls2);
    if (temp_sqrt < 0.0f) {
        temp_f1_5 = fp->self_vel.x;
        temp_f0 = fp->self_vel.y;
        temp_fmuls = temp_f1_5 * temp_f1_5;
        temp_fmuls2 = temp_f0 * temp_f0;
        temp_add = temp_fmuls + temp_fmuls2;
        phi_f1 = -sqrtf__Ff(temp_add);
    } else {
        temp_f1_6 = fp->self_vel.x;
        temp_f0_2 = fp->self_vel.y;
        temp_fmuls = temp_f1_6 * temp_f1_6;
        temp_fmuls2 = temp_f0_2 * temp_f0_2;
        temp_add = temp_fmuls + temp_fmuls2;
        phi_f1 = sqrtf__Ff(temp_add);
    }
    temp_f2 = phi_f1 - ness_attr->x5C_PK_THUNDER_2_DECELERATION_RATE;
    phi_f31 = temp_f2;

    if (temp_f2 <= vel_epsilon) {
        phi_f31 = phi_f1;
    }

    fp->self_vel.x = phi_f31 * cosf(fp->mv.ns.specialhi.aerialVel);
    fp->self_vel.y = phi_f31 * sinf(fp->mv.ns.specialhi.aerialVel);
    ftNess_atan2(gobj);
    fp->mv.ns.specialhi.unkVector1 = fp->self_vel;
    if ((u32) fp->cmd_vars[0] == 1U) {
        fp->mv.ns.specialhi.fallAccel = (float) fp->mv.ns.specialhi.fallAccel -
                                        ness_attr->x50_PK_THUNDER_FALL_ACCEL;
        if ((float) fp->mv.ns.specialhi.fallAccel <
            -ness_attr->x54_PK_THUNDER_2_MOMENTUM)
        {
            fp->mv.ns.specialhi.fallAccel =
                -ness_attr->x54_PK_THUNDER_2_MOMENTUM;
        }
        fp->cur_pos.y += (float) fp->mv.ns.specialhi.fallAccel;
    }
}

// 0x80119410
// https://decomp.me/scratch/HLUCz
void ftNs_SpecialAirHiRebound_Phys(
    HSD_GObj* gobj) // Ness's PK Thunder 2 Wall Rebound Physics callback
{
    ftCo_DatAttrs* fighter_attr;
    Fighter* fp = gobj->user_data;

    fighter_attr = &fp->co_attrs;
    fighter_attr == NULL;
    ftCommon_Fall(fp, fp->co_attrs.grav, fp->co_attrs.terminal_vel);
    ftCommon_ApplyFrictionAir(fp, fighter_attr->aerial_friction);
}

// 0x80119460
// https://decomp.me/scratch/YDYwL
void ftNs_SpecialHiStart_Coll(
    HSD_GObj* gobj) // Ness's grounded PK Thunder Start Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80082708(gobj) == false) {
        ftCommon_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiStart,
                                  FTNESS_SPECIALHI_COLL_FLAG,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

// 0x801194CC
// https://decomp.me/scratch/oOw2I
void ftNs_SpecialHiHold_Coll(HSD_GObj* gobj) // Ness's grounded PK Thunder
                                             // Control Loop Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80082708(gobj) == false) {
        ftCommon_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiHold,
                                  FTNESS_SPECIALHI_COLL_FLAG,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

// 0x80119538
// https://decomp.me/scratch/3bhjz
void ftNs_SpecialHiEnd_Coll(
    HSD_GObj* gobj) // Ness's grounded PK Thunder End Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80082708(gobj) == false) {
        ftCommon_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiEnd,
                                  FTNESS_SPECIALHI_COLL_FLAG,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

/// Ness's grounded PK Thunder 2 Collision callback
void ftNs_SpecialHi_Coll(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp0;

    fp0 = gobj->user_data;
    if (ft_80082708(gobj) == false) {
        u32 env_flags = fp0->coll_data.env_flags;

        if (env_flags & Collide_LeftWallMask ||
            env_flags & Collide_RightWallMask)
        {
            ftCommon_8007D60C(fp0);
            {
                Fighter* fp1 = gobj->user_data;
                ftNessAttributes* temp_attr = fp1->dat_attrs;

                fp1->mv.ns.specialhi.thunderTimerLoop1 =
                    temp_attr->x40_PK_THUNDER_LOOP1;
                fp1->mv.ns.specialhi.thunderTimerLoop2 =
                    temp_attr->x44_PK_THUNDER_LOOP2;
                fp1->mv.ns.specialhi.gravityDelay =
                    temp_attr->x48_PK_THUNDER_GRAVITY_DELAY;
                fp1->mv.ns.specialhi.fallAccel = 0;
                fp1->mv.ns.specialhi.unkVector1.z = 0;
                fp1->mv.ns.specialhi.unkVector1.y = 0;
                fp1->mv.ns.specialhi.unkVector1.x = 0;
                fp1->mv.ns.specialhi.unkVar4 = 0;
                fp1->mv.ns.specialhi.unkVar3 = 0;
                fp1->death2_cb = NULL;
                fp1->take_dmg_cb = NULL;
                ftParts_8007592C(fp1, 0, 0);
            }

            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiEnd,
                                      FTNESS_SPECIALHI_COLL_FLAG,
                                      fp0->cur_anim_frame, 1, 0, NULL);
            return;
        }

        ftCommon_8007D60C(fp0);
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHi,
                                  FTNESS_JIBAKU_COLL_FLAG, fp0->cur_anim_frame,
                                  1, 0, NULL);
        return;
    }

    {
        u32 env_flags = fp0->coll_data.env_flags;

        if (env_flags & Collide_CeilingMask ||
            env_flags & Collide_LeftWallMask ||
            env_flags & Collide_RightWallMask)
        {
            fp0->gr_vel = 0;
            {
                Fighter* fighter_data2 = gobj->user_data;
                s32 msid = fighter_data2->motion_id;

                switch (msid) {
                case ftNs_MS_SpecialHiStart:
                case ftNs_MS_SpecialHiHold:
                case ftNs_MS_SpecialHiEnd:
                case ftNs_MS_SpecialHi:
                case ftNs_MS_SpecialAirHiStart:
                case ftNs_MS_SpecialAirHiHold:
                case ftNs_MS_SpecialAirHiEnd:
                case ftNs_MS_SpecialAirHi:
                case ftNs_MS_SpecialAirHiRebound:
                    efLib_DestroyAll(gobj);
                    fighter_data2->fv.ns.pkthunder_gfx = false;
                }
                ftParts_8007592C(fp0, 0, 0);
                ftCo_80097D40(gobj);
                return;
            }
        }
    }

    {
        u8 _[4];

        if (fp0->coll_data.floor.normal.y > 0.0f) {
            f64 angle;
            if (fp0->facing_dir == +1) {
                angle = -M_PI_2;
            } else {
                angle = M_PI_2;
            }
            fp0->mv.ns.specialhi.aerialVel =
                angle + atan2f(fp0->coll_data.floor.normal.y,
                               fp0->coll_data.floor.normal.x);
            return;
        }
    }

    {
        f64 angle;
        if (fp0->facing_dir == +1) {
            angle = M_PI_2;
        } else {
            angle = -M_PI_2;
        }

        fp0->mv.ns.specialhi.aerialVel =
            angle + atan2f(fp0->coll_data.floor.normal.y,
                           fp0->coll_data.floor.normal.x);
    }
}

// 0x80119798
// https://decomp.me/scratch/zd3TZ
void ftNs_SpecialAirHiStart_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Start Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80081D0C(gobj) != false) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiStart,
                                  FTNESS_SPECIALHI_COLL_FLAG,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

// 0x80119804
// https://decomp.me/scratch/mu2vM
void ftNs_SpecialAirHiHold_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Control Loop Collision
                    // callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80081D0C(gobj) != false) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiHold,
                                  FTNESS_SPECIALHI_COLL_FLAG,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

// 0x80119870
// https://decomp.me/scratch/ELLSL
void ftNs_SpecialAirHiEnd_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder End Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80081D0C(gobj) != false) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiEnd,
                                  FTNESS_SPECIALHI_COLL_FLAG,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

/// Ness's aerial PK Thunder 2 Collision callback
void ftNs_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* new_var;

    u8 unused0[4];

    Vec3 spC4;
    Vec3 spB8;
    Vec3 spAC;

    u8 unused1[140];

    s32 ledgeGrabDir;
    float temp_f0_2;
    float temp_f0_3;
    float temp_f0_4;
    float fmuls1;
    float fmuls2;
    float fmuls3;
    float fmuls4;
    float fmuls5;
    float fmuls6;
    float temp_f1_2;
    float temp_f1_5;
    float temp_f1_8;

    u8 unused2[4];

    float DriftMax;
    s32 msid;
    s32 ecbFlag;
    ftNessAttributes* ness_attr;
    Fighter* fighter_data2;
    Fighter* fighter_data3;
    Fighter* fighter_data4;
    Fighter* fighter_data5;
    Fighter* fighter_r31;
    float phi_f0;

    u8 unused3[8];

    fighter_r31 = gobj->user_data;
    ness_attr = fighter_r31->dat_attrs;
    fighter_r31->self_vel = fighter_r31->mv.ns.specialhi.unkVector1;

    if (1.0f == fighter_r31->facing_dir) {
        ledgeGrabDir = 1;
    } else {
        ledgeGrabDir = -1;
    }
    if (ft_CheckGroundAndLedge(gobj, ledgeGrabDir) != false) {
        if (lbVector_Angle(&fighter_r31->coll_data.floor.normal,
                           &fighter_r31->self_vel) >
            (0.01745329238474369f *
             (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
        {
            fighter_r31->self_vel.z = 0.0f;
            fighter_r31->self_vel.y = 0.0f;
            fighter_r31->self_vel.x = 0.0f;
            fighter_data2 = gobj->user_data;
            msid = fighter_data2->motion_id;
            switch (msid) {
            case ftNs_MS_SpecialHiStart:
            case ftNs_MS_SpecialHiHold:
            case ftNs_MS_SpecialHiEnd:
            case ftNs_MS_SpecialHi:
            case ftNs_MS_SpecialAirHiStart:
            case ftNs_MS_SpecialAirHiHold:
            case ftNs_MS_SpecialAirHiEnd:
            case ftNs_MS_SpecialAirHi:
            case ftNs_MS_SpecialAirHiRebound:
                efLib_DestroyAll(gobj);
                fighter_data2->fv.ns.pkthunder_gfx = false;
            }

            ftParts_8007592C(fighter_r31, 0, 0);
            ftCo_80097D40(gobj);
            return;
        }

        ftCommon_8007D7FC(fighter_r31);
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHi,
                                  FTNESS_JIBAKU_COLL_FLAG,
                                  fighter_r31->cur_anim_frame, 1, 0, NULL);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
        return;
    }

    ecbFlag = fighter_r31->coll_data.env_flags;
    if (ecbFlag & Collide_CeilingMask) {
        if (lbVector_Angle(&fighter_r31->coll_data.ceiling.normal,
                           &fighter_r31->self_vel) >
            (0.01745329238474369f *
             (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
        {
            fighter_data3 = gobj->user_data;
            lbVector_Mirror(&fighter_data3->self_vel,
                            &fighter_r31->coll_data.ceiling.normal);
            (new_var = fighter_data3)->self_vel.x *= 0.5f;
            new_var->self_vel.y *= 0.5f;
            temp_f1_2 = new_var->self_vel.x;
            temp_f0_2 = new_var->self_vel.y;
            fmuls1 = temp_f1_2 * temp_f1_2;
            fmuls2 = temp_f0_2 * temp_f0_2;
            lbVector_sqrtf_accurate(fmuls1 + fmuls2);
            DriftMax = new_var->co_attrs.air_drift_max;
            DriftMax == 0.0f;
            ftCommon_ClampSelfVelX(new_var, new_var->co_attrs.air_drift_max);
            if (new_var->self_vel.x >= 0.0f) {
                phi_f0 = 1.0f;
            } else {
                phi_f0 = -1.0f;
            }
            new_var->facing_dir = phi_f0;
            ftNs_SpecialHiStopGFX(gobj);
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiRebound,
                                      Ft_MF_KeepGfx, 0.0f, 1.0f, 0.0f, NULL);
            ftAnim_8006EBA4(gobj);
            spC4.x = atan2f(-fighter_r31->coll_data.ceiling.normal.x,
                            fighter_r31->coll_data.ceiling.normal.y);
            efSync_Spawn(1030, gobj, &new_var->cur_pos, &spC4);
        }

    } else {
        if (ecbFlag & Collide_LeftWallMask) {
            if (lbVector_Angle(&fighter_r31->coll_data.left_facing_wall.normal,
                               &fighter_r31->self_vel) >
                (0.01745329238474369f *
                 (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
            {
                fighter_data4 = gobj->user_data;
                lbVector_Mirror(
                    &fighter_data4->self_vel,
                    &fighter_r31->coll_data.left_facing_wall.normal);
                (new_var = fighter_data4)->self_vel.x *= 0.5f;
                new_var->self_vel.y *= 0.5f;
                temp_f1_5 = new_var->self_vel.x;
                temp_f0_3 = new_var->self_vel.y;
                fmuls3 = temp_f1_5 * temp_f1_5;
                fmuls4 = temp_f0_3 * temp_f0_3;
                lbVector_sqrtf_accurate(fmuls3 + fmuls4);
                DriftMax = new_var->co_attrs.air_drift_max;
                DriftMax == 0.0f;
                ftCommon_ClampSelfVelX(new_var,
                                       new_var->co_attrs.air_drift_max);
                if (fighter_data4->self_vel.x >= 0.0f) {
                    phi_f0 = 1.0f;
                } else {
                    phi_f0 = -1.0f;
                }
                fighter_data4->facing_dir = phi_f0;
                ftNs_SpecialHiStopGFX(gobj);
                Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiRebound,
                                          Ft_MF_KeepGfx, 0.0f, 1.0f, 0.0f,
                                          NULL);
                ftAnim_8006EBA4(gobj);
                spB8.x =
                    atan2f(-fighter_r31->coll_data.left_facing_wall.normal.x,
                           fighter_r31->coll_data.left_facing_wall.normal.y);
                efSync_Spawn(1030, gobj, &fighter_data4->cur_pos, &spB8);
                return;
            }
            ftNs_SpecialAirHi_CollisionModVel(gobj, &fighter_r31->coll_data);
            return;
        }
        if (ecbFlag & Collide_RightWallMask) {
            if (lbVector_Angle(
                    &fighter_r31->coll_data.right_facing_wall.normal,
                    &fighter_r31->self_vel) >
                (0.01745329238474369f *
                 (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
            {
                fighter_data5 = gobj->user_data;
                lbVector_Mirror(
                    &fighter_data5->self_vel,
                    &fighter_r31->coll_data.right_facing_wall.normal);
                (new_var = fighter_data5)->self_vel.x *= 0.5f;
                new_var->self_vel.y *= 0.5f;
                temp_f1_8 = new_var->self_vel.x;
                temp_f0_4 = new_var->self_vel.y;
                fmuls5 = temp_f1_8 * temp_f1_8;
                fmuls6 = temp_f0_4 * temp_f0_4;
                lbVector_sqrtf_accurate(fmuls5 + fmuls6);
                DriftMax = new_var->co_attrs.air_drift_max;
                DriftMax == 0.0f;
                ftCommon_ClampSelfVelX(new_var,
                                       new_var->co_attrs.air_drift_max);
                if (fighter_data5->self_vel.x >= 0.0f) {
                    phi_f0 = 1.0f;
                } else {
                    phi_f0 = -1.0f;
                }
                fighter_data5->facing_dir = phi_f0;
                ftNs_SpecialHiStopGFX(gobj);
                Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiRebound,
                                          Ft_MF_KeepGfx, 0.0f, 1.0f, 0.0f,
                                          NULL);
                ftAnim_8006EBA4(gobj);
                spAC.x =
                    atan2f(-fighter_r31->coll_data.right_facing_wall.normal.x,
                           fighter_r31->coll_data.right_facing_wall.normal.y);
                efSync_Spawn(1030, gobj, &fighter_data5->cur_pos, &spAC);
                return;
            }
            ftNs_SpecialAirHi_CollisionModVel(gobj, &fighter_r31->coll_data);
        }
    }
}

/// Ness's PK Thunder 2 Wall Rebound Collision callback
void ftNs_SpecialAirHiRebound_Coll(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp;
    Fighter* fighter_data2;
    enum_t msid;

    fp = gobj->user_data;
    if (ft_CheckGroundAndLedge(gobj, 0) == true) {
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        fighter_data2 = gobj->user_data;
        msid = fighter_data2->motion_id;
        switch (msid) {
        case ftNs_MS_SpecialHiStart:
        case ftNs_MS_SpecialHiHold:
        case ftNs_MS_SpecialHiEnd:
        case ftNs_MS_SpecialHi:
        case ftNs_MS_SpecialAirHiStart:
        case ftNs_MS_SpecialAirHiHold:
        case ftNs_MS_SpecialAirHiEnd:
        case ftNs_MS_SpecialAirHi:
        case ftNs_MS_SpecialAirHiRebound:
            efLib_DestroyAll(gobj);
            fighter_data2->fv.ns.pkthunder_gfx = false;
        }
        ftParts_8007592C(fp, 0, 0.0f);
        ftCo_80097D40(gobj);
        return;
    }
    if (ftCliffCommon_80081298(gobj) != false) {
        ftCliffCommon_80081370(gobj);
    }
}
