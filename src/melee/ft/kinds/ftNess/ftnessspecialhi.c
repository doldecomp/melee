#include "ftnessspecialhi.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <melee/mp/forward.h>

#include <math.h>
#include <placeholder.h>

#include "ftness.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_DownBound.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itnesspkthunderball.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbvector.h>

/// SpecialHi/SpecialAirHi (PK Thunder)
#define FTNESS_SPECIALHI_COLL_FLAG                                            \
    Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |                 \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

/// SpecialHi Jibaku (PK Thunder 2 Self-Hit)
#define FTNESS_JIBAKU_COLL_FLAG                                               \
    Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |   \
        Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |                   \
        Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27

#ifdef MUST_MATCH
static void order_sdata2(void)
{
    (void) 5.0f;
    (void) 0.0f;
    (void) 8.333333015441895f;
    (void) 12.333333015441895f;
    (void) M_PI_2_F;
    (void) M_TAU;
    (void) M_PI;
    (void) M_PI_2;
    (void) 1.0f;
    (void) 0.0;
    (void) MTXDegToRad(1);
    (void) 90.0f;
    (void) -1.0f;
    (void) 0.5f;
    (void) 0.5;
    (void) 3.0;
    (void) 1e-4f;
    (void) -1e-4f;
    (void) -M_PI_2;
}
#endif

/// 0x80117B70
/// https://decomp.me/scratch/242L6
void ftNs_SpecialHiStopGFX(HSD_GObj* gobj) // Removes GFX
{
    Fighter* fp = GET_FIGHTER(gobj);

    switch (fp->motion_id) {
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
        fp->u.ns.pkthunder_gfx = false;
    }
}

static inline void startGFX(HSD_GObj* gobj, int id)
{
    Fighter* fp = gobj->user_data;
    ftNs_SpecialHiStopGFX(gobj);
    efSync_Spawn(id, gobj, fp->parts[FtPart_HipN].joint);
    fp->u.ns.pkthunder_gfx = true;
}

static inline bool check_distance(Vec3* pos, Vec3* pair)
{
    if ((ABS(pos->x - pair->x) < 8.333333015441895f) &&
        (ABS(pos->y - pair->y) < 12.333333015441895f))
    {
        return true;
    }
    return false;
}

/// 0x80117BBC
/// https://decomp.me/scratch/xTtbs // Very confusing and fabricated match
/// based on auto-decomp // https://decomp.me/scratch/hwphL // Proper match
bool ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj)
{
    u8 unused0[4];

    Vec3 pair;
    Vec3 pos;

    u8 unused1[8];

    Vec3 pair2;
    Vec3 pos2;

    u8 unused2[36];

    Fighter* fp = GET_FIGHTER(gobj);
    s32 ret = false;

    if (!fp->u.ns.pkthunder_gobj) {
        return false;
    }

    switch (fp->mv.ns.specialhi.thunderColl) {
    case 0:
        pos = fp->cur_pos;
        pos.y += 5.0f * fp->x34_scale.y;
        it_802AB3F0(fp->u.ns.pkthunder_gobj, &pair, 0);
        if (check_distance(&pos, &pair) == true) {
            fp->mv.ns.specialhi.thunderColl = 2;
            it_802AB3F0(fp->u.ns.pkthunder_gobj, &fp->mv.ns.specialhi.collPos1,
                        0);
            it_802AB3F0(fp->u.ns.pkthunder_gobj, &fp->mv.ns.specialhi.collPos2,
                        1);
            ret = true;
        }
        break;

    case 1:
        pos2 = fp->cur_pos;
        pos2.y += 5.0f * fp->x34_scale.y;
        it_802AB3F0(fp->u.ns.pkthunder_gobj, &pair2, 0);
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

/// 0x80117DD4
/// https://decomp.me/scratch/e00Cp
void ftNs_SpecialHi_ItemPKThunderRemove(HSD_GObj* gobj) // OnTakeDamage?
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.ns.pkthunder_gobj != NULL) {
        fp->u.ns.pkthunder_gobj = NULL;
    }
    ftNs_SpecialHiStopGFX(gobj);
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
    ftPartSetRotX(fp, 0, 0.0F);
}

/// 0x80117E60
/// https://decomp.me/scratch/MTTJq
void ftNs_SpecialHi_TakeDamage(HSD_GObj* gobj) // OnTakeDamage again?
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.ns.pkthunder_gobj != NULL) {
        it_802AB9C0(fp->u.ns.pkthunder_gobj);
        fp->u.ns.pkthunder_gobj = NULL;
    }
    ftNs_SpecialHiStopGFX(gobj);
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
    ftPartSetRotX(fp, 0, 0.0F);
}

/// 0x80117F00
/// https://decomp.me/scratch/1nlBY
/// Run from PK Thunder's OnReflect callback. Sets Ness's reference to PK
/// Thunder to NULL if he is reflecting his own PK Thunder.
void ftNs_SpecialHi_ItemPKThunderCheckOwn(HSD_GObj* gobj,
                                          HSD_GObj* thunder_gobj)
{
    HSD_GObj* temp_thunder;
    Fighter* temp_fp = GET_FIGHTER(gobj);

    temp_thunder = temp_fp->u.ns.pkthunder_gobj;
    if ((temp_thunder != NULL) && (temp_thunder == thunder_gobj)) {
        temp_fp->u.ns.pkthunder_gobj = NULL;
    }
}

/// 0x80117F24
/// https://decomp.me/scratch/3URl3
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
        fp->mv.ns.specialhi.aerialVel += M_TAU;
    }
    while (fp->mv.ns.specialhi.aerialVel > M_TAU) {
        fp->mv.ns.specialhi.aerialVel -= M_TAU;
    }
    if (coll_data->env_flags & Collide_LeftWallMask) {
        phi_f1 = atan2f(coll_data->left_facing_wall.normal.y,
                        coll_data->left_facing_wall.normal.x);
        while (phi_f1 < 0.0f) {
            phi_f1 += M_TAU;
        }

        while (phi_f1 > M_TAU) {
            phi_f1 -= M_TAU;
        }
        phi_f3 = M_PI + fp->mv.ns.specialhi.aerialVel;

        while (phi_f3 < 0.0f) {
            phi_f3 += M_TAU;
        }

        while (phi_f3 > M_TAU) {
            phi_f3 -= M_TAU;
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
            phi_f3 += M_TAU;
        }

        while (phi_f3 > M_TAU) {
            phi_f3 -= M_TAU;
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

/// 0x80118120
/// https://decomp.me/scratch/ARLRd
void ftNs_SpecialHiStart_Enter(HSD_GObj* gobj) // Ness's grounded PK Thunder
                                               // Start Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr = fp->dat_attrs;

    u8 _[4];

    ftNessAttributes* temp_attr;
    f64 phi_f0;

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiStart, Ft_MF_None, 0.0f, 1.0f,
                              0.0f, NULL);
    Fighter_ClearCmdVars(fp);

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
        ftPartSetRotX(temp_fp, 0, 0.0F);
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
        fp->mv.ns.specialhi.facingDir = 1.0f;
        fp->mv.ns.specialhi.unkVar = 0.0f;
        ftAnim_8006EBA4(gobj);
    }
}

/// 0x80118250
/// https://decomp.me/scratch/D08nX
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
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiStart, Ft_MF_None, 0.0f, 1.0f,
                              0.0f, NULL);
    Fighter_ClearCmdVars(fp);
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
    ftPartSetRotX(temp_fp, 0, 0.0F);
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
    fp->mv.ns.specialhi.facingDir = 1.0f;
    fp->mv.ns.specialhi.unkVar = 0.0f;
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
                      MTXDegToRad(
                          90.0f +
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

                        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHi, Ft_MF_None,
                                                  0.0f, 1.0f, 0.0f, NULL);
                        fp->gr_vel = (ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                                      fp->facing_dir);
                        fp = getFighter(gobj);
                        ness_attr2 = getFtSpecialAttrs(fp);
                        fp->mv.ns.specialhi.unkVar =
                            ness_attr2->x58_PK_THUNDER_2_UNK1;
                        fighter_data2 = GET_FIGHTER(gobj);
                        ftPartSetRotX(fighter_data2, 0,
                                      (fighter_data2->facing_dir *
                                       atan2f(fighter_data2->self_vel.x,
                                              fighter_data2->self_vel.y)) -
                                          (float) M_PI_2);
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
    fighter_data3 =
#ifdef MUST_MATCH
        fighter_data3 =
#endif
            GET_FIGHTER(gobj);
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
            fighter_data3->u.ns.pkthunder_gfx = false;
        default:
            ftPartSetRotX(fp, 0, 0.0F);
            ftCo_80097D40(gobj);
            return;
        }
    }
}
}

static inline float sign(float x)
{
    float r;
    if (x >= 0.0f) {
        r = 1.0f;
    } else {
        r = -1.0f;
    }
    return r;
}

static inline void
NessFloatMath_PKThunder2(HSD_GObj* gobj) // Required for 0x80118570 to match
{
    Fighter* fp = getFighter(gobj);
    float dx = fp->cur_pos.x - fp->mv.ns.specialhi.collPos1.x;
    ftNessAttributes* ness_attr = getFtSpecialAttrs(fp);
    float dy = 5.0f * fp->x34_scale.y + fp->cur_pos.y -
               fp->mv.ns.specialhi.collPos1.y;

    fp->facing_dir = sign(dx);
    fp->mv.ns.specialhi.facingDir = sign(dy);
    fp->mv.ns.specialhi.aerialVel = atan2f(dy, dx);
    fp->self_vel.x = ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                     cosf(fp->mv.ns.specialhi.aerialVel);
    fp->self_vel.y = ness_attr->x54_PK_THUNDER_2_MOMENTUM *
                     sinf(fp->mv.ns.specialhi.aerialVel);
}

/// Ness's PK Thunder 2 Motion State handler if Ness is launching into
/// SpecialAirHi from SpecialHiHold
void ftNs_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    ftNessAttributes* ness_attr;
    Fighter* fp2;
    Fighter* fp;

    NessFloatMath_PKThunder2(gobj);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHi, Ft_MF_None, 0.0f, 1.0f, 0.0f,
                              NULL);
    fp = GET_FIGHTER(gobj);
    ness_attr = getFtSpecialAttrs(fp);
    fp->mv.ns.specialhi.unkVar = ness_attr->x58_PK_THUNDER_2_UNK1;
    fp2 = GET_FIGHTER(gobj);
    ftPartSetRotX(fp2, 0,
                  fp2->facing_dir * atan2f(fp2->self_vel.x, fp2->self_vel.y) -
                      (float) M_PI_2);
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
}

/// PK Thunder Grounded Startup Animation
void ftNs_SpecialHiStart_Anim(HSD_GObj* gobj)
{
    Vec3 pkt_pos;

    u8 _[32];

    Fighter* fp = gobj->user_data;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiHold, Ft_MF_None, 0.0f, 1.0f,
                                  0.0f, NULL);

        {
            Fighter* fighter_data2 = gobj->user_data;
            HSD_GObj* pkt_ptr = fighter_data2->u.ns.pkthunder_gobj;
            if (pkt_ptr == NULL) {
                lb_8000B1CC(fighter_data2->parts[FtPart_L2ndNa].joint, NULL,
                            &pkt_pos);

                pkt_pos.z = 0.0f;

                pkt_ptr =
                    it_802AB58C(gobj, &pkt_pos, fighter_data2->facing_dir);

                fighter_data2->u.ns.pkthunder_gobj = pkt_ptr;

                if (pkt_ptr != NULL) {
                    fighter_data2->death2_cb = ftNs_Init_OnDamage;
                    fighter_data2->take_dmg_cb = ftNs_Init_OnDamage;
                }
            }
        }

        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;

        startGFX(gobj, 1262);
    }
}

/// 0x801187A4
/// https://decomp.me/scratch/Xm3tt
void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int timer;

    timer = fp->mv.ns.specialhi.thunderTimerLoop1;
    if (timer > 0) {
        fp->mv.ns.specialhi.thunderTimerLoop1 = timer - 1;
    }
    if (fp->u.ns.pkthunder_gobj == NULL) {
        timer = fp->mv.ns.specialhi.thunderTimerLoop2;
        if (timer > 0) {
            fp->mv.ns.specialhi.thunderTimerLoop2 = timer - 1;
        }
    }

    if (fp->u.ns.pkthunder_gobj == NULL) {
        if (fp->mv.ns.specialhi.thunderTimerLoop1 <= 0 &&
            fp->mv.ns.specialhi.thunderTimerLoop2 <= 0)
        {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiEnd, Ft_MF_None, 0.0f,
                                      1.0f, 0.0f, NULL);
            ftNs_SpecialHiStopGFX(gobj);
        }
    } else if (it_802AB568(fp->u.ns.pkthunder_gobj) == gobj) {
        if (ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(gobj) == true) {
            ftNs_SpecialHi_Enter(gobj);
        }
    } else {
        fp->u.ns.pkthunder_gobj = NULL;
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiEnd, Ft_MF_None, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftNs_SpecialHiStopGFX(gobj);
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
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.ns.specialhi.jibakuGFX += 1;
    if (fp->mv.ns.specialhi.jibakuGFX == 1) {
        startGFX(gobj, 1263);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialHiEnd, Ft_MF_None, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftNs_SpecialHiStopGFX(gobj);
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
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiHold, Ft_MF_None, 0.0f,
                                  1.0f, 0.0f, NULL);

        {
            Fighter* fp2 = gobj->user_data;
            pkt_ptr = fp2->u.ns.pkthunder_gobj;

            if (pkt_ptr == 0) {
                lb_8000B1CC(fp2->parts[FtPart_L2ndNa].joint, NULL, &pkt_pos);

                pkt_pos.z = 0.0f;

                pkt_ptr = it_802AB58C(gobj, &pkt_pos, fp2->facing_dir);

                fp2->u.ns.pkthunder_gobj = pkt_ptr;

                if (pkt_ptr != NULL) {
                    fp2->death2_cb = ftNs_Init_OnDamage;
                    fp2->take_dmg_cb = ftNs_Init_OnDamage;
                }
            }
        }

        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;

        startGFX(gobj, 1262);
    }
}

/// Ness's aerial PK Thunder Control Loop Animation callback
void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int timer;

    timer = fp->mv.ns.specialhi.thunderTimerLoop1;
    if (timer > 0) {
        fp->mv.ns.specialhi.thunderTimerLoop1 = timer - 1;
    }
    if (fp->u.ns.pkthunder_gobj == NULL) {
        timer = fp->mv.ns.specialhi.thunderTimerLoop2;
        if (timer > 0) {
            fp->mv.ns.specialhi.thunderTimerLoop2 = timer - 1;
        }
    }

    if (fp->u.ns.pkthunder_gobj == NULL) {
        if (fp->mv.ns.specialhi.thunderTimerLoop1 <= 0 &&
            fp->mv.ns.specialhi.thunderTimerLoop2 <= 0)
        {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiEnd, Ft_MF_None, 0.0f,
                                      1.0f, 0.0f, NULL);
            ftNs_SpecialHiStopGFX(gobj);
        }
    } else if (it_802AB568(fp->u.ns.pkthunder_gobj) == gobj) {
        if (ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(gobj) == true) {
            NessFloatMath_PKThunder2(gobj);
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHi, Ft_MF_None, 0.0f,
                                      1.0f, 0.0f, NULL);
            {
                Fighter* fp1 = GET_FIGHTER(gobj);
                ftNessAttributes* ness_attr = getFtSpecialAttrs(fp1);
                Fighter* fp2;

                fp1->mv.ns.specialhi.unkVar = ness_attr->x58_PK_THUNDER_2_UNK1;
                fp2 = GET_FIGHTER(gobj);
                ftPartSetRotX(fp2, 0,
                              fp2->facing_dir * atan2f(fp2->self_vel.x,
                                                       fp2->self_vel.y) -
                                  (float) M_PI_2);
                fp1->death2_cb = NULL;
                fp1->take_dmg_cb = NULL;
                fp1->x1968_jumpsUsed = fp1->co_attrs.max_jumps;
            }
        }
    } else {
        fp->u.ns.pkthunder_gobj = NULL;
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiEnd, Ft_MF_None, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftNs_SpecialHiStopGFX(gobj);
    }
    PAD_STACK(8);
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
        startGFX(gobj, 1263);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        float temp_f1 = fp1->mv.ns.specialhi.fallAccel;
        float phi_f1 = temp_f1;

        if (temp_f1 < 0) {
            phi_f1 = -temp_f1;
        }

        fp1->self_vel.y = (-phi_f1);
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

/// 0x80118F80
void ftNs_SpecialHiStart_IASA(
    HSD_GObj* gobj) // Ness's PK Thunder IASA callbacks
{
    return;
}

/// 0x80118F84
void ftNs_SpecialHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x80118F88
void ftNs_SpecialHiEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x80118F8C
void ftNs_SpecialHi_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x80118F90
void ftNs_SpecialAirHiStart_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x80118F94
void ftNs_SpecialAirHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x80118F98
void ftNs_SpecialAirHiEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x80118F9C
void ftNs_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x80118FA0
void ftNs_SpecialAirHiRebound_IASA(HSD_GObj* gobj)
{
    return;
}

static inline void ThunderPhysTimer(HSD_GObj* gobj)
{
    Fighter* temp_fp;
    s32 thunderPhysTimer;

    temp_fp = gobj->user_data;
    thunderPhysTimer = temp_fp->mv.ns.specialhi.gravityDelay;
    if (thunderPhysTimer != 0) {
        temp_fp->mv.ns.specialhi.gravityDelay = (s32) (thunderPhysTimer - 1);
    }
}

/// 0x80118FA4
/// https://decomp.me/scratch/5RSqi
void ftNs_SpecialHiStart_Phys(
    HSD_GObj* gobj) // Ness's grounded PK Thunder Start Physics callback
{
    ThunderPhysTimer(gobj);
    ft_80084F3C(gobj);
}

/// 0x80118FDC
/// https://decomp.me/scratch/3o65K
void ftNs_SpecialHiHold_Phys(HSD_GObj* gobj) // Ness's grounded PK Thunder
                                             // Control Loop Physics callback
{
    ft_80084F3C(gobj);
}

/// 0x80118FFC
/// This is identical to 0x80118FDC so there's no link bruh
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
    ftCommon_SetSelfMovementFromGroundedMovement(gobj);

    {
        Fighter* fp = gobj->user_data;
        ftPartSetRotX(
            fp, 0,
            (fp->facing_dir * atan2f(fp->self_vel.x, fp->self_vel.y)) -
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
                      fp->co_attrs.terminal_velocity);
    }

    {
        float friction = fp->co_attrs.aerial_friction;
        ftCommon_CalcSelfAccel_Deaccel(fp, friction);
    }
}

/// 0x80119194
/// https://decomp.me/scratch/nvI07
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
                      fp->co_attrs.terminal_velocity);
    }

    {
        float friction = fp->co_attrs.aerial_friction;
        ftCommon_CalcSelfAccel_Deaccel(fp, friction);
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
                      fp->co_attrs.terminal_velocity);
    }

    {
        float friction = fp->co_attrs.aerial_friction;
        ftCommon_CalcSelfAccel_Deaccel(fp, friction);
    }
}

static inline void ftNess_atan2(HSD_GObj* gobj)
{
    Fighter* fighter_data2 = GET_FIGHTER(gobj);
    FORCE_PAD_STACK_4;

    ftPartSetRotX(
        fighter_data2, 0,
        (fighter_data2->facing_dir *
         atan2f(fighter_data2->self_vel.x, fighter_data2->self_vel.y)) -
            (float) M_PI_2);
}

static inline void* getFtSpecialAttrs2(Fighter* fp)
{
    FORCE_PAD_STACK_4;
    return fp->dat_attrs;
}

/// Ness's aerial PK Thunder 2 Physics callback
void ftNs_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    ftNessAttributes* ness_attr;
    Fighter* fp;
    float temp_f2;

    float phi_f1;
    float phi_f31;
    float temp_add;

    fp = getFighter(gobj);
    ness_attr = getFtSpecialAttrs2(fp);

    phi_f1 = ABS(lbVector_Len_xy(&fp->self_vel));
    temp_f2 = phi_f1 - ness_attr->x5C_PK_THUNDER_2_DECELERATION_RATE;
    phi_f31 = temp_f2;

    if (temp_f2 <= vel_epsilon) {
        phi_f31 = phi_f1;
    }

    fp->self_vel.x = phi_f31 * cosf(fp->mv.ns.specialhi.aerialVel);
    fp->self_vel.y = phi_f31 * sinf(fp->mv.ns.specialhi.aerialVel);
    ftNess_atan2(gobj);
    fp->mv.ns.specialhi.unkVector1 = fp->self_vel;
    if (fp->cmd_vars[0] == 1U) {
        fp->mv.ns.specialhi.fallAccel = fp->mv.ns.specialhi.fallAccel -
                                        ness_attr->x50_PK_THUNDER_FALL_ACCEL;
        if (fp->mv.ns.specialhi.fallAccel <
            -ness_attr->x54_PK_THUNDER_2_MOMENTUM)
        {
            fp->mv.ns.specialhi.fallAccel =
                -ness_attr->x54_PK_THUNDER_2_MOMENTUM;
        }
        fp->cur_pos.y += fp->mv.ns.specialhi.fallAccel;
    }
}

/// 0x80119410
/// https://decomp.me/scratch/HLUCz
void ftNs_SpecialAirHiRebound_Phys(
    HSD_GObj* gobj) // Ness's PK Thunder 2 Wall Rebound Physics callback
{
    ftCo_DatAttrs* fighter_attr;
    Fighter* fp = gobj->user_data;

    fighter_attr = &fp->co_attrs;
    fighter_attr == NULL;
    ftCommon_Fall(fp, fp->co_attrs.gravity, fp->co_attrs.terminal_velocity);
    ftCommon_CalcSelfAccel_Deaccel(fp, fighter_attr->aerial_friction);
}

/// 0x80119460
/// https://decomp.me/scratch/YDYwL
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

/// 0x801194CC
/// https://decomp.me/scratch/oOw2I
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

/// 0x80119538
/// https://decomp.me/scratch/3bhjz
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
                ftPartSetRotX(fp1, 0, 0);
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
                ftNs_SpecialHiStopGFX(gobj);
                ftPartSetRotX(fp0, 0, 0);
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

/// 0x80119798
/// https://decomp.me/scratch/zd3TZ
void ftNs_SpecialAirHiStart_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Start Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80081D0C(gobj) != false) {
        ftCommon_AirToGroundStateChange(gobj, fp, ftNs_MS_SpecialHiStart,
                                        FTNESS_SPECIALHI_COLL_FLAG);
    }
}

/// 0x80119804
/// https://decomp.me/scratch/mu2vM
void ftNs_SpecialAirHiHold_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder Control Loop Collision
                    // callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80081D0C(gobj) != false) {
        ftCommon_AirToGroundStateChange(gobj, fp, ftNs_MS_SpecialHiHold,
                                        FTNESS_SPECIALHI_COLL_FLAG);
    }
}

/// 0x80119870
/// https://decomp.me/scratch/ELLSL
void ftNs_SpecialAirHiEnd_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Thunder End Collision callback
{
    Fighter* fp;

    fp = gobj->user_data;
    if (ft_80081D0C(gobj) != false) {
        ftCommon_AirToGroundStateChange(gobj, fp, ftNs_MS_SpecialHiEnd,
                                        FTNESS_SPECIALHI_COLL_FLAG);
    }
}

/// Ness's aerial PK Thunder 2 Collision callback
static inline void scaleXY(Vec3* v, float s)
{
    v->x *= s;
    v->y *= s;
}

/// Reflects Ness off a surface and enters the rebound state.
static inline Fighter* rebound(HSD_GObj* gobj, Vec3* normal)
{
    Fighter* fp = gobj->user_data;
    float x;
    float y;
    float xx;
    float yy;
    float dir;
    float max;

    lbVector_Mirror(&fp->self_vel, normal);
    scaleXY(&fp->self_vel, 0.5f);
    x = fp->self_vel.x;
    y = fp->self_vel.y;
    xx = x * x;
    yy = y * y;
    lbVector_sqrtf_accurate(xx + yy);
    max = fp->co_attrs.air_drift_max;
    ftCommon_ClampSelfVelX(fp, max);
    if (fp->self_vel.x >= 0.0f) {
        dir = 1.0f;
    } else {
        dir = -1.0f;
    }
    fp->facing_dir = dir;
    ftNs_SpecialHiStopGFX(gobj);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirHiRebound, Ft_MF_KeepGfx,
                              0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    return fp;
}

void ftNs_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftNessAttributes* ness_attr = fp->dat_attrs;
    u8 _[4];
    s32 ledge_dir;
    s32 env_flags;

    fp->self_vel = fp->mv.ns.specialhi.unkVector1;

    if (1.0f == fp->facing_dir) {
        ledge_dir = 1;
    } else {
        ledge_dir = -1;
    }
    if (ft_CheckGroundAndLedge(gobj, ledge_dir) != false) {
        if (lbVector_Angle(&fp->coll_data.floor.normal, &fp->self_vel) >
            (0.01745329238474369f *
             (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
        {
            fp->self_vel.z = 0.0f;
            fp->self_vel.y = 0.0f;
            fp->self_vel.x = 0.0f;
            ftNs_SpecialHiStopGFX(gobj);
            ftPartSetRotX(fp, 0, 0);
            ftCo_80097D40(gobj);
            return;
        }

        ftCommon_AirToGroundStateChange(gobj, fp, ftNs_MS_SpecialHi,
                                        FTNESS_JIBAKU_COLL_FLAG);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
        return;
    }

    env_flags = fp->coll_data.env_flags;
    if (env_flags & Collide_CeilingMask) {
        if (lbVector_Angle(&fp->coll_data.ceiling.normal, &fp->self_vel) >
            (0.01745329238474369f *
             (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
        {
            Vec3 rot;
            Fighter* fp1 = rebound(gobj, &fp->coll_data.ceiling.normal);
            rot.x = atan2f(-fp->coll_data.ceiling.normal.x,
                           fp->coll_data.ceiling.normal.y);
            efSync_Spawn(1030, gobj, &fp1->cur_pos, &rot);
        }
    } else {
        if (env_flags & Collide_LeftWallMask) {
            if (lbVector_Angle(&fp->coll_data.left_facing_wall.normal,
                               &fp->self_vel) >
                (0.01745329238474369f *
                 (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
            {
                Vec3 rot;
                Fighter* fp1 =
                    rebound(gobj, &fp->coll_data.left_facing_wall.normal);
                rot.x = atan2f(-fp->coll_data.left_facing_wall.normal.x,
                               fp->coll_data.left_facing_wall.normal.y);
                efSync_Spawn(1030, gobj, &fp1->cur_pos, &rot);
                return;
            }
            ftNs_SpecialAirHi_CollisionModVel(gobj, &fp->coll_data);
            return;
        }
        if (env_flags & Collide_RightWallMask) {
            if (lbVector_Angle(&fp->coll_data.right_facing_wall.normal,
                               &fp->self_vel) >
                (0.01745329238474369f *
                 (90.0f + ness_attr->x64_PK_THUNDER_2_WALLHUG_ANGLE)))
            {
                Vec3 rot;
                Fighter* fp1 =
                    rebound(gobj, &fp->coll_data.right_facing_wall.normal);
                rot.x = atan2f(-fp->coll_data.right_facing_wall.normal.x,
                               fp->coll_data.right_facing_wall.normal.y);
                efSync_Spawn(1030, gobj, &fp1->cur_pos, &rot);
                return;
            }
            ftNs_SpecialAirHi_CollisionModVel(gobj, &fp->coll_data);
        }
    }
    PAD_STACK(144);
}

/// Ness's PK Thunder 2 Wall Rebound Collision callback
void ftNs_SpecialAirHiRebound_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_CheckGroundAndLedge(gobj, 0) == true) {
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        ftNs_SpecialHiStopGFX(gobj);
        ftPartSetRotX(fp, 0, 0.0F);
        ftCo_80097D40(gobj);
        return;
    }
    if (ftCliffCommon_80081298(gobj) != false) {
        ftCliffCommon_80081370(gobj);
    }
}
