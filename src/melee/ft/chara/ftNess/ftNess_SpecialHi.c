#include "ftNess.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

#include <trigf.h>
#include <dolphin/mtx/types.h>
#include <MetroTRK/intrinsics.h>

// Setup float order
static f32 return_float1(void) // -0x62B0
{
    return 5.0f;
}

static f32 return_float2(void) // -0x62AC
{
    return 0.0f;
}

static f32 return_float3(void) // -0x62A8
{
    return 8.333333015441895f;
}

static f32 return_float4(void) // -0x62A4
{
    return 12.333333015441895f;
}

static f32 return_float5(void) // -0x62A0
{
    return M_PI / 2;
}

static f64 return_float6(void) // -0x6294
{
    return 2 * M_PI;
}

static f64 return_float7(void) // -0x628C
{
    return M_PI;
}

static f64 return_float8(void) // -0x6284
{
    return M_PI / 2;
}

static f32 return_float9(void) // -0x6280
{
    return 1.0f;
}

static f64 return_float10(void) // -0x6278
{
    return 0.0;
}

static f32 return_float12(void) // -0x6270
{
    return M_PI / 180;
}

static f32 return_float13(void)
{
    return 90.0f;
}

static f32 return_float14(void)
{
    return -1.0f;
}

static f32 return_float15(void)
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

static f32 return_float18(void)
{
    return 1e-4F;
}

static f32 return_float19(void)
{
    return -1e-4F;
}

static f64 return_float20(void)
{
    return -M_PI / 2;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif

// 0x80117B70
// https://decomp.me/scratch/242L6
void ftNess_SpecialHiStopGFX(HSD_GObj* gobj) // Removes GFX
{
    s32 msid;
    Fighter* fp;

    fp = gobj->user_data;
    msid = fp->motion_id;
    switch (msid) {
    case MS_NESS_SPECIALHI_START:
    case MS_NESS_SPECIALHI_HOLD:
    case MS_NESS_SPECIALHI_END:
    case MS_NESS_SPECIALHI:
    case MS_NESS_SPECIALAIRHI_START:
    case MS_NESS_SPECIALAIRHI_HOLD:
    case MS_NESS_SPECIALAIRHI_END:
    case MS_NESS_SPECIALAIRHI:
    case MS_NESS_SPECIALAIRHI_HITWALL:
        efLib_DestroyAll(gobj);
        fp->fv.ns.pkthunder_gfx = false;
    default:
        return;
    }
}

#ifdef MUST_MATCH
#pragma pop
#endif

static inline f32 fabs_inline_ness(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

inline bool check_distance(Vec3* pos, Vec2* pair)
{
    if ((fabs_inline_ness(pos->x - pair->x) < 8.333333015441895f) &&
        (fabs_inline_ness(pos->y - pair->y) < 12.333333015441895f))
    {
        return true;
    }
    return false;
}

// 0x80117BBC
// https://decomp.me/scratch/xTtbs // Very confusing and fabricated match based
// on auto-decomp // https://decomp.me/scratch/hwphL // Proper match
bool ftNess_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[8];
#endif

    Vec2 pair;
    Vec3 pos;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[12];
#endif

    Vec2 pair2;
    Vec3 pos2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused2[36];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    s32 ret = false;

    if (!fp->fv.ns.pkthunder_gobj)
        return false;

    switch (fp->mv.ns.specialhi.thunderColl) {
    case 0:
        pos = fp->cur_pos;
        pos.y += 5.0f * fp->x34_scale.y;
        func_802AB3F0(fp->fv.ns.pkthunder_gobj, &pair, 0);
        if (check_distance(&pos, &pair) == true) {
            fp->mv.ns.specialhi.thunderColl = 2;
            func_802AB3F0(fp->fv.ns.pkthunder_gobj,
                          &fp->mv.ns.specialhi.collPos1, 0);
            func_802AB3F0(fp->fv.ns.pkthunder_gobj,
                          &fp->mv.ns.specialhi.collPos2, 1);
            ret = true;
        }
        break;

    case 1:
        pos2 = fp->cur_pos;
        pos2.y += 5.0f * fp->x34_scale.y;
        func_802AB3F0(fp->fv.ns.pkthunder_gobj, &pair2, 0);
        if (!check_distance(&pos2, &pair2)) {
            fp->mv.ns.specialhi.thunderColl = 0;
        }
    }
    return ret;
}

/// Checks if Ness is in SpecialHiHold/SpecialAirHiHold
/// (PK Thunder control loop)
bool ftNess_CheckSpecialHiHold(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    return fp->motion_id == MS_NESS_SPECIALHI_HOLD ||
                   fp->motion_id == MS_NESS_SPECIALAIRHI_HOLD
               ? true
               : false;
}

// 0x80117DD4
// https://decomp.me/scratch/e00Cp
void ftNess_ItemPKThunderRemove(HSD_GObj* gobj) // OnTakeDamage?
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
    case MS_NESS_SPECIALHI_START:
    case MS_NESS_SPECIALHI_HOLD:
    case MS_NESS_SPECIALHI_END:
    case MS_NESS_SPECIALHI:
    case MS_NESS_SPECIALAIRHI_START:
    case MS_NESS_SPECIALAIRHI_HOLD:
    case MS_NESS_SPECIALAIRHI_END:
    case MS_NESS_SPECIALAIRHI:
    case MS_NESS_SPECIALAIRHI_HITWALL:
        efLib_DestroyAll(gobj);
        fp->fv.ns.pkthunder_gfx = false;

    default:
        temp_fp->cb.x21E4_callback_OnDeath2 = NULL;
        temp_fp->cb.x21DC_callback_OnTakeDamage = NULL;
        func_8007592C(temp_fp, 0, 0.0f);
    }
}

// 0x80117E60
// https://decomp.me/scratch/MTTJq
void ftNess_SpecialHiTakeDamage(HSD_GObj* gobj) // OnTakeDamage again?
{
    s32 msid;
    Fighter* fp;
    Fighter* fighter_data2;
    Fighter* temp_fp;

    temp_fp = gobj->user_data;
    fp = temp_fp;
    if (temp_fp->fv.ns.pkthunder_gobj != NULL) {
        func_802AB9C0(temp_fp->fv.ns.pkthunder_gobj);
        fp->fv.ns.pkthunder_gobj = NULL;
    }
    fighter_data2 = GET_FIGHTER(gobj);
    msid = fighter_data2->motion_id;
    switch (msid) {
    case MS_NESS_SPECIALHI_START:
    case MS_NESS_SPECIALHI_HOLD:
    case MS_NESS_SPECIALHI_END:
    case MS_NESS_SPECIALHI:
    case MS_NESS_SPECIALAIRHI_START:
    case MS_NESS_SPECIALAIRHI_HOLD:
    case MS_NESS_SPECIALAIRHI_END:
    case MS_NESS_SPECIALAIRHI:
    case MS_NESS_SPECIALAIRHI_HITWALL:
        efLib_DestroyAll(gobj);
        fighter_data2->fv.ns.pkthunder_gfx = false;
    default:
        temp_fp->cb.x21E4_callback_OnDeath2 = NULL;
        temp_fp->cb.x21DC_callback_OnTakeDamage = NULL;
        func_8007592C(temp_fp, 0, 0.0f);
    }
}

// 0x80117F00
// https://decomp.me/scratch/1nlBY
void ftNess_ItemPKThunderCheckOwn(
    HSD_GObj* gobj,
    HSD_GObj* thunder_gobj) // Run from PK Thunder's OnReflect callback. Sets
                            // Ness's reference to PK Thunder to NULL if he is
                            // reflecting his own PK Thunder.
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
void ftNess_SpecialAirHi_CollisionModVel(
    HSD_GObj* gobj,
    CollData* coll_data) // Adjusts Ness's velocity upon interacting with
                         // collisions during SpecialAirHi
{
    Vec3 sp14;
    Fighter* fp;
    f32 phi_f1;
    f32 phi_f3;

    fp = GET_FIGHTER(gobj);
    while (fp->mv.ns.specialhi.aerialVel < 0.0f) {
        fp->mv.ns.specialhi.aerialVel += 2 * M_PI;
    }
    while (fp->mv.ns.specialhi.aerialVel > 2 * M_PI) {
        fp->mv.ns.specialhi.aerialVel -= 2 * M_PI;
    }
    if ((coll_data->x134_envFlags & 0x3F) != 0) {
        phi_f1 = atan2f(coll_data->x160_rightwall.normal.y,
                        coll_data->x160_rightwall.normal.x);
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
    if ((coll_data->x134_envFlags & 0xFC0) != 0) {
        phi_f1 = atan2f(coll_data->x174_leftwall.normal.y,
                        coll_data->x174_leftwall.normal.x);
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
    lbvector_RotateAboutUnitAxis(&fp->x80_self_vel, &sp14,
                                 phi_f1 - fp->mv.ns.specialhi.aerialVel);
    fp->mv.ns.specialhi.aerialVel =
        atan2f(fp->x80_self_vel.y, fp->x80_self_vel.x);
}

// 0x80118120
// https://decomp.me/scratch/ARLRd
void ftNess_SpecialHi_StartMotion(HSD_GObj* gobj) // Ness's grounded PK Thunder
                                                  // Start Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ftNessAttributes* temp_attr;
    f64 phi_f0;

    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI_START, 0, NULL, 0.0f,
                              1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

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

/// @todo Unused assignment.
#ifdef MUST_MATCH
        {
            f32 temp_f1_2 = 0.0f;
        }
#endif

        temp_fp->mv.ns.specialhi.fallAccel = 0.0f;
        temp_fp->mv.ns.specialhi.unkVector1.z = 0.0f;
        temp_fp->mv.ns.specialhi.unkVector1.y = 0.0f;
        temp_fp->mv.ns.specialhi.unkVector1.x = 0.0f;
        temp_fp->mv.ns.specialhi.unkVar4 = 0.0f;
        temp_fp->mv.ns.specialhi.unkVar3 = 0.0f;
        temp_fp->cb.x21E4_callback_OnDeath2 = NULL;
        temp_fp->cb.x21DC_callback_OnTakeDamage = NULL;
        func_8007592C(temp_fp, 0, 0.0f);
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
        fp->mv.ns.specialhi.aerialVel = (f32) phi_f0;
        fp->mv.ns.specialhi.facingDir = (f32) 1.0f;
        fp->mv.ns.specialhi.unkVar = (f32) 0.0f;
        func_8006EBA4(gobj);
    }
}

// 0x80118250
// https://decomp.me/scratch/D08nX
void ftNess_SpecialAirHiStart_Action(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Start Motion State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;
    Fighter* temp_fp;
    ftNessAttributes* temp_attr;
    f64 phi_f0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

/// @todo Unused assignment.
#ifdef MUST_MATCH
    {
        f32 _ = 0.0f;
    }
#endif

    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_START, 0, NULL, 0.0f,
                              1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    temp_fp = gobj->user_data;
    temp_attr = temp_fp->x2D4_specialAttributes;
    temp_fp->mv.ns.specialhi.thunderTimerLoop1 =
        (s32) temp_attr->x40_PK_THUNDER_LOOP1;
    temp_fp->mv.ns.specialhi.thunderTimerLoop2 =
        (s32) temp_attr->x44_PK_THUNDER_LOOP2;
    temp_fp->mv.ns.specialhi.gravityDelay =
        (s32) temp_attr->x48_PK_THUNDER_GRAVITY_DELAY;

/// @todo Unused assignment.
#ifdef MUST_MATCH
    {
        f32 _ = 0.0f;
    }
#endif

    temp_fp->mv.ns.specialhi.fallAccel = 0.0f;
    temp_fp->mv.ns.specialhi.unkVector1.z = 0.0f;
    temp_fp->mv.ns.specialhi.unkVector1.y = 0.0f;
    temp_fp->mv.ns.specialhi.unkVector1.x = 0.0f;
    temp_fp->mv.ns.specialhi.unkVar4 = 0.0f;
    temp_fp->mv.ns.specialhi.unkVar3 = 0.0f;
    temp_fp->cb.x21E4_callback_OnDeath2 = NULL;
    temp_fp->cb.x21DC_callback_OnTakeDamage = NULL;
    func_8007592C(temp_fp, 0, 0.0f);
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
    fp->mv.ns.specialhi.aerialVel = (f32) phi_f0;
    fp->mv.ns.specialhi.facingDir = (f32) 1.0f;
    fp->mv.ns.specialhi.unkVar = (f32) 0.0f;
    fp->x80_self_vel.y = 0.0f;
    func_8006EBA4(gobj);
}

/// @todo Rewrite this.
void ftNess_SpecialHi_Action(
    HSD_GObj* gobj) // Ness's grounded PK Thunder 2 Motion State handler
{
    /// @todo Try to move these close to usage
    Vec3 sp40;
    ftNessAttributes* ness_attr2;
    Fighter* fighter_data2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fighter_data3;

    Fighter* fp = getFighter(gobj);
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    if ((fp->x6F0_collData.x14C_ground.unk & 0x100) == 0) {
        f32 temp_f3 = 5.0f;
        f32 temp_f1;
        f32 temp_f2;

        sp40.x = fp->cur_pos.x - fp->mv.ns.specialhi.collPos1.x;
        temp_f2 = fp->x34_scale.y;
        temp_f1 = (temp_f3 * temp_f2) + fp->cur_pos.y;
        sp40.y = temp_f1 - fp->mv.ns.specialhi.collPos1.y;
        sp40.z = 0.0f;

        {
            f32 temp_f1_2 =
                lbvector_Angle(&fp->x6F0_collData.x14C_ground.normal, &sp40);

            if (!(temp_f1_2 < (f32) M_PI_2)) {
                if (!(temp_f1_2 >
                      DEG_TO_RAD *
                          (90.0f +
                           ness_attr->x60_PK_THUNDER_2_KNOCKDOWN_ANGLE)))
                {
                    {
                        f32 facing_dir;
                        if (sp40.x >= 0) {
                            facing_dir = +1;
                        } else {
                            facing_dir = -1;
                        }
                        fp->facing_dir = facing_dir;
                    }

                    {
                        f32 facing_dir;
                        if (sp40.y >= 0) {
                            facing_dir = +1;
                        } else {
                            facing_dir = -1;
                        }
                        fp->mv.ns.specialhi.facingDir = facing_dir;
                    }

                    fp->mv.ns.specialhi.aerialVel = atan2f(sp40.y, sp40.x);
                    {
                        /// @todo Unused stack.
#ifdef MUST_MATCH
                        u8 _[4];
#endif

                        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI, 0,
                                                  NULL, 0.0f, 1.0f, 0.0f);
                        fp->gr_vel =
                            (f32) (ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                                   fp->facing_dir);
                        fp = getFighter(gobj);
                        ness_attr2 = getFtSpecialAttrs(fp);
                        fp->mv.ns.specialhi.unkVar =
                            (f32) ness_attr2->x58_PK_THUNDER_2_UNK1;
                        fighter_data2 = GET_FIGHTER(gobj);
                        func_8007592C(fighter_data2, 0,
                                      (fighter_data2->facing_dir *
                                       atan2f(fighter_data2->x80_self_vel.x,
                                              fighter_data2->x80_self_vel.y)) -
                                          1.5707963705062866f);
                        fighter_data2 = fp;
                        fighter_data2->cb.x21E4_callback_OnDeath2 = NULL;
                        fighter_data2->cb.x21DC_callback_OnTakeDamage = NULL;
                        fighter_data2->x1968_jumpsUsed =
                            fighter_data2->x110_attr.x168_MaxJumps;
                        return;
                    }
                }
                goto block_stuff;
            }
        }
    }
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    func_8007D60C(fp);
    ftNess_SpecialAirHi_Action(gobj);
    return;

block_stuff : {
#ifdef MUST_MATCH
    fighter_data3 = fighter_data3 = GET_FIGHTER(gobj);
#else
    fighter_data3 = GET_FIGHTER(gobj);
#endif

    {
        enum_t msid = fighter_data3->motion_id;
        switch (msid) {
        case MS_NESS_SPECIALHI_START:
        case MS_NESS_SPECIALHI_HOLD:
        case MS_NESS_SPECIALHI_END:
        case MS_NESS_SPECIALHI:
        case MS_NESS_SPECIALAIRHI_START:
        case MS_NESS_SPECIALAIRHI_HOLD:
        case MS_NESS_SPECIALAIRHI_END:
        case MS_NESS_SPECIALAIRHI:
        case MS_NESS_SPECIALAIRHI_HITWALL:
            efLib_DestroyAll(gobj);
            fighter_data3->fv.ns.pkthunder_gfx = false;
        default:
            func_8007592C(fp, 0, 0.0f);
            func_80097D40(gobj);
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
    f32 temp_f2;
    f32 temp_f1;
    f32 phi_f0;

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
    fp->x80_self_vel.x = (f32) (ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                                cosf(fp->mv.ns.specialhi.aerialVel));
    fp->x80_self_vel.y = (f32) (ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                                sinf(fp->mv.ns.specialhi.aerialVel));
}

/// Ness's PK Thunder 2 Motion State handler if Ness is launching into
/// SpecialAirHi from SpecialHiHold
void ftNess_SpecialAirHi_Action(HSD_GObj* gobj)
{
    ftNessAttributes* temp_attr;
    Fighter* fighter_data3;
    Fighter* fighter_data2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    NessFloatMath_PKThunder2(gobj);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    fighter_data2 = GET_FIGHTER(gobj);
    temp_attr = getFtSpecialAttrs(fighter_data2);
    fighter_data2->mv.ns.specialhi.unkVar = temp_attr->x58_PK_THUNDER_2_UNK1;
    fighter_data3 = GET_FIGHTER(gobj);
    func_8007592C(
        fighter_data3, 0,
        (fighter_data3->facing_dir * atan2f(fighter_data3->x80_self_vel.x,
                                            fighter_data3->x80_self_vel.y)) -
            (f32) M_PI_2);
    fighter_data2->cb.x21E4_callback_OnDeath2 = NULL;
    fighter_data2->cb.x21DC_callback_OnTakeDamage = NULL;
    fighter_data2->x1968_jumpsUsed = fighter_data2->x110_attr.x168_MaxJumps;
}

/// PK Thunder Grounded Startup Animation
void ftNess_SpecialHiStart_Anim(HSD_GObj* gobj)
{
    Vec3 pkt_pos;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[32];
#endif

    Fighter* fp = gobj->user_data;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI_HOLD, 0, NULL, 0.0f,
                                  1.0f, 0.0f);

        {
            Fighter* fighter_data2 = gobj->user_data;
            HSD_GObj* pkt_ptr = fighter_data2->fv.ns.pkthunder_gobj;
            if (pkt_ptr == NULL) {
                func_8000B1CC(fighter_data2->ft_bones[24].x0_jobj, NULL,
                              &pkt_pos);

                pkt_pos.z = 0.0f;

                pkt_ptr =
                    func_802AB58C(gobj, &pkt_pos, fighter_data2->facing_dir);

                fighter_data2->fv.ns.pkthunder_gobj = pkt_ptr;

                if (pkt_ptr != NULL) {
                    fighter_data2->cb.x21E4_callback_OnDeath2 =
                        ftNess_OnDamage;
                    fighter_data2->cb.x21DC_callback_OnTakeDamage =
                        ftNess_OnDamage;
                }
            }
        }

        fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;

        fp = gobj->user_data;

        ftNess_SpecialHiStopGFX(gobj);

        ef_Spawn(0x4EE, gobj, fp->ft_bones[4].x0_jobj);

        fp->fv.ns.pkthunder_gfx = true;
    }
}

// 0x801187A4
// https://decomp.me/scratch/Xm3tt
void ftNess_SpecialHiHold_Anim(
    HSD_GObj* gobj) // Ness's grounded PK Thunder Control Loop
                    // Animation callback
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
            Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI_END, 0, NULL,
                                      0.0f, 1.0f, 0.0f);
            fighter_data2 = gobj->user_data;
            msid = fighter_data2->motion_id;
            switch (msid) {
            case MS_NESS_SPECIALHI_START:
            case MS_NESS_SPECIALHI_HOLD:
            case MS_NESS_SPECIALHI_END:
            case MS_NESS_SPECIALHI:
            case MS_NESS_SPECIALAIRHI_START:
            case MS_NESS_SPECIALAIRHI_HOLD:
            case MS_NESS_SPECIALAIRHI_END:
            case MS_NESS_SPECIALAIRHI:
            case MS_NESS_SPECIALAIRHI_HITWALL:
                efLib_DestroyAll(gobj);
                fighter_data2->fv.ns.pkthunder_gfx = false;
            }
        }
    } else if (func_802AB568(fp->fv.ns.pkthunder_gobj) == gobj) {
        if (ftNess_ItemPKThunder_CheckNessCollide(gobj) == true) {
            ftNess_SpecialHi_Action(gobj);
        }
    } else {
        fp->fv.ns.pkthunder_gobj = NULL;
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI_END, 0, NULL, 0.0f,
                                  1.0f, 0.0f);
        fighter_data3 = gobj->user_data;
        ASID2 = fighter_data3->motion_id;
        switch (ASID2) {
        case MS_NESS_SPECIALHI_START:
        case MS_NESS_SPECIALHI_HOLD:
        case MS_NESS_SPECIALHI_END:
        case MS_NESS_SPECIALHI:
        case MS_NESS_SPECIALAIRHI_START:
        case MS_NESS_SPECIALAIRHI_HOLD:
        case MS_NESS_SPECIALAIRHI_END:
        case MS_NESS_SPECIALAIRHI:
        case MS_NESS_SPECIALAIRHI_HITWALL:
            efLib_DestroyAll(gobj);
            fighter_data3->fv.ns.pkthunder_gfx = false;
        }
    }
}

/// Ness's grounded PK Thunder End Animation callback
void ftNess_SpecialHiEnd_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

/// Ness's grounded PK Thunder 2 Animation callback
void ftNess_SpecialHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    {
        Fighter* temp_fp = gobj->user_data;
        temp_fp->mv.ns.specialhi.jibakuGFX =
            temp_fp->mv.ns.specialhi.jibakuGFX + 1;

        if (temp_fp->mv.ns.specialhi.jibakuGFX == 1) {
            Fighter* fp = gobj->user_data;
            ftNess_SpecialHiStopGFX(gobj);
            ef_Spawn(0x4EF, gobj, fp->ft_bones[4].x0_jobj);
            fp->fv.ns.pkthunder_gfx = true;
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI_END, 0, NULL, 0.0f,
                                  1.0f, 0.0f);
        {
            Fighter* fp = gobj->user_data;
            enum_t msid = fp->motion_id;

            switch (msid) {
            case MS_NESS_SPECIALHI_START:
            case MS_NESS_SPECIALHI_HOLD:
            case MS_NESS_SPECIALHI_END:
            case MS_NESS_SPECIALHI:
            case MS_NESS_SPECIALAIRHI_START:
            case MS_NESS_SPECIALAIRHI_HOLD:
            case MS_NESS_SPECIALAIRHI_END:
            case MS_NESS_SPECIALAIRHI:
            case MS_NESS_SPECIALAIRHI_HITWALL:
                efLib_DestroyAll(gobj);
                fp->fv.ns.pkthunder_gfx = false;
            }
        }
    }
}

/// Ness's aerial PK Thunder Start Animation callback
void ftNess_SpecialAirHiStart_Anim(HSD_GObj* gobj)
{
    Vec3 pkt_pos;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[32];
#endif

    HSD_GObj* pkt_ptr;
    Fighter* fp = gobj->user_data;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_HOLD, 0, NULL,
                                  0.0f, 1.0f, 0.0f);

        {
            Fighter* fp2 = gobj->user_data;
            pkt_ptr = fp2->fv.ns.pkthunder_gobj;

            if (pkt_ptr == 0) {
                func_8000B1CC(fp2->ft_bones[24].x0_jobj, NULL, &pkt_pos);

                pkt_pos.z = 0.0f;

                pkt_ptr = func_802AB58C(gobj, &pkt_pos, fp2->facing_dir);

                fp2->fv.ns.pkthunder_gobj = pkt_ptr;

                if (pkt_ptr != NULL) {
                    fp2->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
                    fp2->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
                }
            }
        }

        fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;

        fp = gobj->user_data;

        ftNess_SpecialHiStopGFX(gobj);

        ef_Spawn(0x4EE, gobj, fp->ft_bones[4].x0_jobj);

        fp->fv.ns.pkthunder_gfx = true;
    }
}

/// Ness's aerial PK Thunder Control Loop Animation callback
void ftNess_SpecialAirHiHold_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[44];
#endif

    Fighter* fp0 = gobj->user_data;

    {
        int pkt_timer0 = fp0->mv.ns.specialhi.thunderTimerLoop1;
        if (pkt_timer0 > 0)
            fp0->mv.ns.specialhi.thunderTimerLoop1 = (s32) (pkt_timer0 - 1);
    }

    if (fp0->fv.ns.pkthunder_gobj == NULL) {
        int pkt_timer1 = fp0->mv.ns.specialhi.thunderTimerLoop2;

        if (pkt_timer1 > 0)
            fp0->mv.ns.specialhi.thunderTimerLoop2 = (s32) (pkt_timer1 - 1);
    }

    if (fp0->fv.ns.pkthunder_gobj == NULL) {
        if (fp0->mv.ns.specialhi.thunderTimerLoop1 <= 0 &&
            fp0->mv.ns.specialhi.thunderTimerLoop2 <= 0)
        {
            Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_END, 0, NULL,
                                      0, 1, 0);
            {
                Fighter* fp1 = gobj->user_data;
                enum_t msid = fp1->motion_id;
                switch (msid) {
                case MS_NESS_SPECIALHI_START:
                case MS_NESS_SPECIALHI_HOLD:
                case MS_NESS_SPECIALHI_END:
                case MS_NESS_SPECIALHI:
                case MS_NESS_SPECIALAIRHI_START:
                case MS_NESS_SPECIALAIRHI_HOLD:
                case MS_NESS_SPECIALAIRHI_END:
                case MS_NESS_SPECIALAIRHI:
                case MS_NESS_SPECIALAIRHI_HITWALL:
                    efLib_DestroyAll(gobj);
                    fp1->fv.ns.pkthunder_gfx = false;
                }
            }
        }
    } else if (func_802AB568(fp0->fv.ns.pkthunder_gobj) == gobj) {
        if (ftNess_ItemPKThunder_CheckNessCollide(gobj) == true) {
            NessFloatMath_PKThunder2(gobj);
            Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI, 0, NULL,
                                      0.0f, 1.0f, 0.0f);

            {
                Fighter* fp1 = gobj->user_data;

                {
                    ftNessAttributes* temp_attr = fp1->x2D4_specialAttributes;
                    fp1->mv.ns.specialhi.unkVar =
                        temp_attr->x58_PK_THUNDER_2_UNK1;
                }

                {
                    Fighter* fp4 = gobj->user_data;
                    func_8007592C(fp4, 0,
                                  fp4->facing_dir *
                                          atan2f(fp4->x80_self_vel.x,
                                                 fp4->x80_self_vel.y) -
                                      (f32) M_PI_2);
                }

                fp1->cb.x21E4_callback_OnDeath2 = NULL;
                fp1->cb.x21DC_callback_OnTakeDamage = NULL;
                fp1->x1968_jumpsUsed = fp1->x110_attr.x168_MaxJumps;
            }
        }
    } else {
        fp0->fv.ns.pkthunder_gobj = NULL;
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_END, 0, NULL,
                                  0.0f, 1.0f, 0.0f);
        {
            Fighter* fp1 = gobj->user_data;
            enum_t msid = fp1->motion_id;
            switch (msid) {
            case MS_NESS_SPECIALHI_START:
            case MS_NESS_SPECIALHI_HOLD:
            case MS_NESS_SPECIALHI_END:
            case MS_NESS_SPECIALHI:
            case MS_NESS_SPECIALAIRHI_START:
            case MS_NESS_SPECIALAIRHI_HOLD:
            case MS_NESS_SPECIALAIRHI_END:
            case MS_NESS_SPECIALAIRHI:
            case MS_NESS_SPECIALAIRHI_HITWALL:
                efLib_DestroyAll(gobj);
                fp1->fv.ns.pkthunder_gfx = false;
            }
        }
    }
}

/// Ness's aerial PK Thunder End Animation callback
void ftNess_SpecialAirHiEnd_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
        func_8007D60C(fp);

        if (ness_attr->x70_PK_THUNDER_2_LANDING_LAG == 0) {
            func_800CC730(gobj);
            return;
        }

        func_800969D8(gobj, 1, 0, 1, 1,
                      ness_attr->x70_PK_THUNDER_2_LANDING_LAG,
                      ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
    }
}

/// Ness's aerial PK Thunder 2 Animation callback
void ftNess_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp0;
    Fighter* fp1 = gobj->user_data;
    ftNessAttributes* ness_attr = fp1->x2D4_specialAttributes;

    fp1->mv.ns.specialhi.jibakuGFX = fp1->mv.ns.specialhi.jibakuGFX + 1;
    if (fp1->mv.ns.specialhi.jibakuGFX == 1) {
        fp0 = gobj->user_data;
        ftNess_SpecialHiStopGFX(gobj);
        ef_Spawn(0x4EF, gobj, fp0->ft_bones[4].x0_jobj);
        fp0->fv.ns.pkthunder_gfx = true;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        f32 temp_f1 = fp1->mv.ns.specialhi.fallAccel;
        f32 phi_f1 = temp_f1;

        if (temp_f1 < 0)
            phi_f1 = -temp_f1;

        fp1->x80_self_vel.y = (f32) -phi_f1;
        func_8007D60C(fp1);

        if (ness_attr->x70_PK_THUNDER_2_LANDING_LAG == 0) {
            func_800CC730(gobj);
            return;
        }

        func_800969D8(gobj, 1, 0, 1, 1,
                      ness_attr->x70_PK_THUNDER_2_LANDING_LAG,
                      ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
    }
}

/// Ness's PK Thunder 2 Wall Rebound Animation callback
void ftNess_SpecialAirHiRebound_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp0 = gobj->user_data;

    {
        Fighter* fp1 = fp0;
        ftNessAttributes* ness_attr = fp0->x2D4_specialAttributes;

        if (!ftAnim_IsFramesRemaining(gobj)) {
            func_8007D60C(fp1);

            if (ness_attr->x70_PK_THUNDER_2_LANDING_LAG == 0) {
                func_800CC730(gobj);
                return;
            }

            func_800969D8(gobj, 1, 0, 1, 1.0f,
                          ness_attr->x70_PK_THUNDER_2_LANDING_LAG,
                          ness_attr->x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND);
        }
    }
}

// 0x80118F80
void ftNess_SpecialHiStart_IASA(
    HSD_GObj* gobj) // Ness's PK Thunder IASA callbacks
{
    return;
}

// 0x80118F84
void ftNess_SpecialHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F88
void ftNess_SpecialHiEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F8C
void ftNess_SpecialHi_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F90
void ftNess_SpecialAirHiStart_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F94
void ftNess_SpecialAirHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F98
void ftNess_SpecialAirHiEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118F9C
void ftNess_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80118FA0
void ftNess_SpecialAirHiRebound_IASA(HSD_GObj* gobj)
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
void ftNess_SpecialHiStart_Phys(
    HSD_GObj* gobj) // Ness's grounded PK Thunder Start Physics callback
{
    ThunderPhysTimer(gobj);
    func_80084F3C(gobj);
}

// 0x80118FDC
// https://decomp.me/scratch/3o65K
void ftNess_SpecialHiHold_Phys(HSD_GObj* gobj) // Ness's grounded PK Thunder
                                               // Control Loop Physics callback
{
    func_80084F3C(gobj);
}

// 0x80118FFC
// This is identical to 0x80118FDC so there's no link bruh
void ftNess_SpecialHiEnd_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

static const f32 vel_epsilon = 0.0001f;

/// Ness's grounded PK Thunder 2 Physics callback
void ftNess_SpecialHi_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp0 = gobj->user_data;
    f32 ground_vel = fp0->gr_vel;
    f32 vel_y = fp0->x80_self_vel.y;
    ftNessAttributes* ness_attr = fp0->x2D4_specialAttributes;

    fp0->gr_vel =
        -(ness_attr->x5C_PK_THUNDER_2_DECELERATION_RATE * fp0->facing_dir -
          ground_vel);

    if (fp0->facing_dir == +1) {
        if (fp0->gr_vel <= vel_epsilon)
            fp0->gr_vel = ground_vel;
    } else if (fp0->gr_vel >= -vel_epsilon) {
        fp0->gr_vel = ground_vel;
    }

    if (fp0->mv.ns.specialhi.facingDir == +1) {
        if (fp0->x80_self_vel.y <= vel_epsilon)
            fp0->x80_self_vel.y = vel_y;
    } else if (fp0->x80_self_vel.y >= -vel_epsilon) {
        fp0->x80_self_vel.y = vel_y;
    }

    fp0->mv.ns.specialhi.unkVector1 = fp0->x80_self_vel;
    func_8007CB74(gobj);

    {
        Fighter* fp = gobj->user_data;
        func_8007592C(fp, 0,
                      fp->facing_dir *
                              atan2f(fp->x80_self_vel.x, fp->x80_self_vel.y) -
                          (f32) M_PI_2);
    }
}

/// Ness's aerial PK Thunder Start Physics callback
void ftNess_SpecialAirHiStart_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    int gravity_timer = fp->mv.ns.specialhi.gravityDelay;
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;

    if (gravity_timer != 0) {
        fp->mv.ns.specialhi.gravityDelay = gravity_timer - 1;
    } else {
        func_8007D494(fp, ness_attr->x50_PK_THUNDER_FALL_ACCEL,
                      fp->x110_attr.x170_TerminalVelocity);
    }

    {
        f32 friction = fp->x110_attr.x180_AerialFriction;
        func_8007CE94(fp, friction);
    }
}

// 0x80119194
// https://decomp.me/scratch/nvI07
void ftNess_SpecialAirHiHold_Phys(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Control Loop Physics
                    // callback
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    int gravity_timer = fp->mv.ns.specialhi.gravityDelay;
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;

    if (gravity_timer != 0) {
        fp->mv.ns.specialhi.gravityDelay = gravity_timer - 1;
    } else {
        func_8007D494(fp, ness_attr->x50_PK_THUNDER_FALL_ACCEL,
                      fp->x110_attr.x170_TerminalVelocity);
    }

    {
        f32 friction = fp->x110_attr.x180_AerialFriction;
        func_8007CE94(fp, friction);
    }
}

/// Ness's aerial PK Thunder End Physics callback
void ftNess_SpecialAirHiEnd_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    int gravity_timer = fp->mv.ns.specialhi.gravityDelay;
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;

    if (gravity_timer != 0) {
        fp->mv.ns.specialhi.gravityDelay = gravity_timer - 1;
    } else {
        func_8007D494(fp, ness_attr->x50_PK_THUNDER_FALL_ACCEL,
                      fp->x110_attr.x170_TerminalVelocity);
    }

    {
        f32 friction = fp->x110_attr.x180_AerialFriction;
        func_8007CE94(fp, friction);
    }
}

inline void ftNess_atan2(HSD_GObj* gobj)
{
    Fighter* fighter_data2 = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif

    func_8007592C(
        fighter_data2, 0,
        (fighter_data2->facing_dir * atan2f(fighter_data2->x80_self_vel.x,
                                            fighter_data2->x80_self_vel.y)) -
            (f32) M_PI_2);
}

inline void* getFtSpecialAttrs2(Fighter* fp)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif

    return fp->x2D4_specialAttributes;
}

// Ness's aerial PK Thunder 2 Physics callback
void ftNess_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    f32 temp_sqrt;
    ftNessAttributes* ness_attr;
    Fighter* fp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    f32 phi_f1;
    f32 phi_f31;
    f32 temp_fmuls;
    f32 temp_fmuls2;
    f32 temp_add;

    fp = getFighter(gobj);
    temp_f2 = fp->x80_self_vel.x;
    temp_f1 = fp->x80_self_vel.y;
    ness_attr = getFtSpecialAttrs2(fp);
    temp_fmuls = temp_f2 * temp_f2;
    temp_fmuls2 = temp_f1 * temp_f1;

    temp_sqrt = sqrtf(temp_fmuls + temp_fmuls2);
    if (temp_sqrt < 0.0f) {
        temp_f1_5 = fp->x80_self_vel.x;
        temp_f0 = fp->x80_self_vel.y;
        temp_fmuls = temp_f1_5 * temp_f1_5;
        temp_fmuls2 = temp_f0 * temp_f0;
        temp_add = temp_fmuls + temp_fmuls2;
        phi_f1 = -sqrtf__Ff(temp_add);
    } else {
        temp_f1_6 = fp->x80_self_vel.x;
        temp_f0_2 = fp->x80_self_vel.y;
        temp_fmuls = temp_f1_6 * temp_f1_6;
        temp_fmuls2 = temp_f0_2 * temp_f0_2;
        temp_add = temp_fmuls + temp_fmuls2;
        phi_f1 = sqrtf__Ff(temp_add);
    }
    temp_f2 = phi_f1 - ness_attr->x5C_PK_THUNDER_2_DECELERATION_RATE;
    phi_f31 = temp_f2;

    if (temp_f2 <= vel_epsilon)
        phi_f31 = phi_f1;

    fp->x80_self_vel.x = phi_f31 * cosf(fp->mv.ns.specialhi.aerialVel);
    fp->x80_self_vel.y = phi_f31 * sinf(fp->mv.ns.specialhi.aerialVel);
    ftNess_atan2(gobj);
    fp->mv.ns.specialhi.unkVector1 = fp->x80_self_vel;
    if ((u32) fp->x2200_ftcmd_var0 == 1U) {
        fp->mv.ns.specialhi.fallAccel = (f32) fp->mv.ns.specialhi.fallAccel -
                                        ness_attr->x50_PK_THUNDER_FALL_ACCEL;
        if ((f32) fp->mv.ns.specialhi.fallAccel <
            -ness_attr->x54_PK_THUNDER_2_MOMENTUM)
        {
            fp->mv.ns.specialhi.fallAccel =
                -ness_attr->x54_PK_THUNDER_2_MOMENTUM;
        }
        fp->cur_pos.y += (f32) fp->mv.ns.specialhi.fallAccel;
    }
}

// 0x80119410
// https://decomp.me/scratch/HLUCz
void ftNess_SpecialAirHiRebound_Phys(
    HSD_GObj* gobj) // Ness's PK Thunder 2 Wall Rebound Physics callback
{
    attr* fighter_attr;
    Fighter* fp = gobj->user_data;

    fighter_attr = &fp->x110_attr;
    fighter_attr == NULL;
    func_8007D494(fp, fp->x110_attr.x16C_Gravity,
                  fp->x110_attr.x170_TerminalVelocity);
    func_8007CE94(fp, fighter_attr->x180_AerialFriction);
}

// 0x80119460
// https://decomp.me/scratch/YDYwL
void ftNess_SpecialHiStart_Coll(
    HSD_GObj* gobj) // Ness's grounded PK Thunder Start Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (func_80082708(gobj) == false) {
        func_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_START,
                                  FTNESS_SPECIALHI_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x801194CC
// https://decomp.me/scratch/oOw2I
void ftNess_SpecialHiHold_Coll(
    HSD_GObj* gobj) // Ness's grounded PK Thunder Control Loop
                    // Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (func_80082708(gobj) == false) {
        func_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_HOLD,
                                  FTNESS_SPECIALHI_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80119538
// https://decomp.me/scratch/3bhjz
void ftNess_SpecialHiEnd_Coll(
    HSD_GObj* gobj) // Ness's grounded PK Thunder End Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (func_80082708(gobj) == false) {
        func_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_END,
                                  FTNESS_SPECIALHI_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

/// Ness's grounded PK Thunder 2 Collision callback
void ftNess_SpecialHi_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp0;

    fp0 = gobj->user_data;
    if (func_80082708(gobj) == false) {
        u32 env_flags = fp0->x6F0_collData.x134_envFlags;

        if ((env_flags & 0b111111) || (env_flags & 0b111111 << 6)) {
            func_8007D60C(fp0);
            {
                Fighter* fp1 = gobj->user_data;
                ftNessAttributes* temp_attr = fp1->x2D4_specialAttributes;

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
                fp1->cb.x21E4_callback_OnDeath2 = NULL;
                fp1->cb.x21DC_callback_OnTakeDamage = NULL;
                func_8007592C(fp1, 0, 0);
            }

            Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_END,
                                      FTNESS_SPECIALHI_COLL_FLAG, NULL,
                                      fp0->x894_currentAnimFrame, 1, 0);
            return;
        }

        func_8007D60C(fp0);
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI,
                                  FTNESS_JIBAKU_COLL_FLAG, NULL,
                                  fp0->x894_currentAnimFrame, 1, 0);
        return;
    }

    {
        u32 env_flags = fp0->x6F0_collData.x134_envFlags;

        if ((env_flags & 0b11 << 13) || (env_flags & 0b111111) ||
            (env_flags & 0b111111 << 6))
        {
            fp0->gr_vel = 0;
            {
                Fighter* fighter_data2 = gobj->user_data;
                s32 msid = fighter_data2->motion_id;

                switch (msid) {
                case MS_NESS_SPECIALHI_START:
                case MS_NESS_SPECIALHI_HOLD:
                case MS_NESS_SPECIALHI_END:
                case MS_NESS_SPECIALHI:
                case MS_NESS_SPECIALAIRHI_START:
                case MS_NESS_SPECIALAIRHI_HOLD:
                case MS_NESS_SPECIALAIRHI_END:
                case MS_NESS_SPECIALAIRHI:
                case MS_NESS_SPECIALAIRHI_HITWALL:
                    efLib_DestroyAll(gobj);
                    fighter_data2->fv.ns.pkthunder_gfx = false;
                }
                func_8007592C(fp0, 0, 0);
                func_80097D40(gobj);
                return;
            }
        }
    }

    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4];
#endif

        if (fp0->x6F0_collData.x14C_ground.normal.y > 0.0f) {
            f64 angle;
            if (fp0->facing_dir == +1) {
                angle = -M_PI_2;
            } else {
                angle = M_PI_2;
            }
            fp0->mv.ns.specialhi.aerialVel =
                angle + atan2f(fp0->x6F0_collData.x14C_ground.normal.y,
                               fp0->x6F0_collData.x14C_ground.normal.x);
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
            angle + atan2f(fp0->x6F0_collData.x14C_ground.normal.y,
                           fp0->x6F0_collData.x14C_ground.normal.x);
    }
}

// 0x80119798
// https://decomp.me/scratch/zd3TZ
void ftNess_SpecialAirHiStart_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Start Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (func_80081D0C(gobj) != false) {
        func_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI_START,
                                  FTNESS_SPECIALHI_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80119804
// https://decomp.me/scratch/mu2vM
void ftNess_SpecialAirHiHold_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Control Loop Collision
                    // callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (func_80081D0C(gobj) != false) {
        func_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI_HOLD,
                                  FTNESS_SPECIALHI_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80119870
// https://decomp.me/scratch/ELLSL
void ftNess_SpecialAirHiEnd_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder End Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (func_80081D0C(gobj) != false) {
        func_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI_END,
                                  FTNESS_SPECIALHI_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

/// Ness's aerial PK Thunder 2 Collision callback
void ftNess_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* new_var;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif

    Vec3 spC4;
    Vec3 spB8;
    Vec3 spAC;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[140];
#endif

    s32 ledgeGrabDir;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 fmuls1;
    f32 fmuls2;
    f32 fmuls3;
    f32 fmuls4;
    f32 fmuls5;
    f32 fmuls6;
    f32 temp_f1_2;
    f32 temp_f1_5;
    f32 temp_f1_8;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused2[4];
#endif

    f32 DriftMax;
    s32 msid;
    s32 ecbFlag;
    ftNessAttributes* ness_attr;
    Fighter* fighter_data2;
    Fighter* fighter_data3;
    Fighter* fighter_data4;
    Fighter* fighter_data5;
    Fighter* fighter_r31;
    f32 phi_f0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused3[8];
#endif

    fighter_r31 = gobj->user_data;
    ness_attr = fighter_r31->x2D4_specialAttributes;
    fighter_r31->x80_self_vel = fighter_r31->mv.ns.specialhi.unkVector1;

    if (1.0f == fighter_r31->facing_dir) {
        ledgeGrabDir = 1;
    } else {
        ledgeGrabDir = -1;
    }
    if (EnvColl_CheckGroundAndLedge(gobj, ledgeGrabDir) != false) {
        if (lbvector_Angle(&fighter_r31->x6F0_collData.x14C_ground.normal,
                           &fighter_r31->x80_self_vel) >
            (0.01745329238474369f *
             (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
        {
            fighter_r31->x80_self_vel.z = 0.0f;
            fighter_r31->x80_self_vel.y = 0.0f;
            fighter_r31->x80_self_vel.x = 0.0f;
            fighter_data2 = gobj->user_data;
            msid = fighter_data2->motion_id;
            switch (msid) {
            case MS_NESS_SPECIALHI_START:
            case MS_NESS_SPECIALHI_HOLD:
            case MS_NESS_SPECIALHI_END:
            case MS_NESS_SPECIALHI:
            case MS_NESS_SPECIALAIRHI_START:
            case MS_NESS_SPECIALAIRHI_HOLD:
            case MS_NESS_SPECIALAIRHI_END:
            case MS_NESS_SPECIALAIRHI:
            case MS_NESS_SPECIALAIRHI_HITWALL:
                efLib_DestroyAll(gobj);
                fighter_data2->fv.ns.pkthunder_gfx = false;
            }

            func_8007592C(fighter_r31, 0, 0);
            func_80097D40(gobj);
            return;
        }

        func_8007D7FC(fighter_r31);
        Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALHI,
                                  FTNESS_JIBAKU_COLL_FLAG, NULL,
                                  fighter_r31->x894_currentAnimFrame, 1, 0);
        return;
    }

    if (func_80081298(gobj)) {
        func_80081370(gobj);
        return;
    }

    ecbFlag = fighter_r31->x6F0_collData.x134_envFlags;
    if ((ecbFlag & 0x6000) != 0) {
        if (lbvector_Angle(&fighter_r31->x6F0_collData.x188_ceiling.normal,
                           &fighter_r31->x80_self_vel) >
            (0.01745329238474369f *
             (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
        {
            fighter_data3 = gobj->user_data;
            lbvector_Mirror(&fighter_data3->x80_self_vel,
                            &fighter_r31->x6F0_collData.x188_ceiling.normal);
            (new_var = fighter_data3)->x80_self_vel.x *= 0.5f;
            new_var->x80_self_vel.y *= 0.5f;
            temp_f1_2 = new_var->x80_self_vel.x;
            temp_f0_2 = new_var->x80_self_vel.y;
            fmuls1 = temp_f1_2 * temp_f1_2;
            fmuls2 = temp_f0_2 * temp_f0_2;
            lbvector_sqrtf_accurate(fmuls1 + fmuls2);
            DriftMax = new_var->x110_attr.x17C_AerialDriftMax;
            DriftMax == 0.0f;
            func_8007D440(new_var, new_var->x110_attr.x17C_AerialDriftMax);
            if (new_var->x80_self_vel.x >= 0.0f) {
                phi_f0 = 1.0f;
            } else {
                phi_f0 = -1.0f;
            }
            new_var->facing_dir = phi_f0;
            ftNess_SpecialHiStopGFX(gobj);
            Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_HITWALL,
                                      FtStateChange_PreserveGfx, NULL, 0.0f,
                                      1.0f, 0.0f);
            func_8006EBA4(gobj);
            spC4.x = atan2f(-fighter_r31->x6F0_collData.x188_ceiling.normal.x,
                            fighter_r31->x6F0_collData.x188_ceiling.normal.y);
            ef_Spawn(0x406, gobj, &new_var->cur_pos, &spC4);
        }

    } else {
        if ((ecbFlag & 0x3F) != 0) {
            if (lbvector_Angle(
                    &fighter_r31->x6F0_collData.x160_rightwall.normal,
                    &fighter_r31->x80_self_vel) >
                (0.01745329238474369f *
                 (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
            {
                fighter_data4 = gobj->user_data;
                lbvector_Mirror(
                    &fighter_data4->x80_self_vel,
                    &fighter_r31->x6F0_collData.x160_rightwall.normal);
                (new_var = fighter_data4)->x80_self_vel.x *= 0.5f;
                new_var->x80_self_vel.y *= 0.5f;
                temp_f1_5 = new_var->x80_self_vel.x;
                temp_f0_3 = new_var->x80_self_vel.y;
                fmuls3 = temp_f1_5 * temp_f1_5;
                fmuls4 = temp_f0_3 * temp_f0_3;
                lbvector_sqrtf_accurate(fmuls3 + fmuls4);
                DriftMax = new_var->x110_attr.x17C_AerialDriftMax;
                DriftMax == 0.0f;
                func_8007D440(new_var, new_var->x110_attr.x17C_AerialDriftMax);
                if (fighter_data4->x80_self_vel.x >= 0.0f) {
                    phi_f0 = 1.0f;
                } else {
                    phi_f0 = -1.0f;
                }
                fighter_data4->facing_dir = phi_f0;
                ftNess_SpecialHiStopGFX(gobj);
                Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_HITWALL,
                                          FtStateChange_PreserveGfx, NULL,
                                          0.0f, 1.0f, 0.0f);
                func_8006EBA4(gobj);
                spB8.x =
                    atan2f(-fighter_r31->x6F0_collData.x160_rightwall.normal.x,
                           fighter_r31->x6F0_collData.x160_rightwall.normal.y);
                ef_Spawn(0x406, gobj, &fighter_data4->cur_pos, &spB8);
                return;
            }
            ftNess_SpecialAirHi_CollisionModVel(gobj,
                                                &fighter_r31->x6F0_collData);
            return;
        }
        if ((ecbFlag & 0xFC0) != 0) {
            if (lbvector_Angle(
                    &fighter_r31->x6F0_collData.x174_leftwall.normal,
                    &fighter_r31->x80_self_vel) >
                (0.01745329238474369f *
                 (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
            {
                fighter_data5 = gobj->user_data;
                lbvector_Mirror(
                    &fighter_data5->x80_self_vel,
                    &fighter_r31->x6F0_collData.x174_leftwall.normal);
                (new_var = fighter_data5)->x80_self_vel.x *= 0.5f;
                new_var->x80_self_vel.y *= 0.5f;
                temp_f1_8 = new_var->x80_self_vel.x;
                temp_f0_4 = new_var->x80_self_vel.y;
                fmuls5 = temp_f1_8 * temp_f1_8;
                fmuls6 = temp_f0_4 * temp_f0_4;
                lbvector_sqrtf_accurate(fmuls5 + fmuls6);
                DriftMax = new_var->x110_attr.x17C_AerialDriftMax;
                DriftMax == 0.0f;
                func_8007D440(new_var, new_var->x110_attr.x17C_AerialDriftMax);
                if (fighter_data5->x80_self_vel.x >= 0.0f) {
                    phi_f0 = 1.0f;
                } else {
                    phi_f0 = -1.0f;
                }
                fighter_data5->facing_dir = phi_f0;
                ftNess_SpecialHiStopGFX(gobj);
                Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRHI_HITWALL,
                                          FtStateChange_PreserveGfx, NULL,
                                          0.0f, 1.0f, 0.0f);
                func_8006EBA4(gobj);
                spAC.x =
                    atan2f(-fighter_r31->x6F0_collData.x174_leftwall.normal.x,
                           fighter_r31->x6F0_collData.x174_leftwall.normal.y);
                ef_Spawn(0x406, gobj, &fighter_data5->cur_pos, &spAC);
                return;
            }
            ftNess_SpecialAirHi_CollisionModVel(gobj,
                                                &fighter_r31->x6F0_collData);
        }
    }
}

/// Ness's PK Thunder 2 Wall Rebound Collision callback
void ftNess_SpecialAirHiRebound_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp;
    Fighter* fighter_data2;
    enum_t msid;

    fp = gobj->user_data;
    if (EnvColl_CheckGroundAndLedge(gobj, 0) == true) {
        fp->x80_self_vel.z = 0.0f;
        fp->x80_self_vel.y = 0.0f;
        fp->x80_self_vel.x = 0.0f;
        fighter_data2 = gobj->user_data;
        msid = fighter_data2->motion_id;
        switch (msid) {
        case MS_NESS_SPECIALHI_START:
        case MS_NESS_SPECIALHI_HOLD:
        case MS_NESS_SPECIALHI_END:
        case MS_NESS_SPECIALHI:
        case MS_NESS_SPECIALAIRHI_START:
        case MS_NESS_SPECIALAIRHI_HOLD:
        case MS_NESS_SPECIALAIRHI_END:
        case MS_NESS_SPECIALAIRHI:
        case MS_NESS_SPECIALAIRHI_HITWALL:
            efLib_DestroyAll(gobj);
            fighter_data2->fv.ns.pkthunder_gfx = false;
        }
        func_8007592C(fp, 0, 0.0f);
        func_80097D40(gobj);
        return;
    }
    if (func_80081298(gobj) != false) {
        func_80081370(gobj);
    }
}
