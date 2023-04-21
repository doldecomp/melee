#include "forward.h"

#include "ftMt_SpecialN.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ftMewtwo/ftMt_Init.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

// SpecialN/SpecialAirN

#define FTMEWTWO_SPECIALN_ACTION_FLAG                                         \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_PreserveSfx |             \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |           \
        FtStateChange_Unk_19

#define FTMEWTWO_SPECIALN_COLL_FLAG                                           \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |       \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |           \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// 0x80146CCC
// https://decomp.me/scratch/qxdYd
s32 ftMt_SpecialN_GetChargeLevel(HSD_GObj* gobj, s32* chargeLevel,
                                 s32* chargeCycles)
{
    Fighter* fp;
    ftMewtwoAttributes* mewtwoAttrs;

    if (gobj != NULL) {
        fp = getFighter(gobj);
        mewtwoAttrs = getFtSpecialAttrsD(fp);

        if (fp->fv.mt.x2230_shadowHeldGObj == NULL) {
            return -1;
        }

        *chargeLevel = fp->fv.mt.x2234_shadowBallCharge;
        *chargeCycles = mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
        return 0;
    }
    return -1;
}

// 0x80146D24
// https://decomp.me/scratch/EKheK // Check to remove Shadow Ball
bool ftMt_SpecialN_CheckShadowBallRemove(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = getFighter(gobj);
        s32 msid = fp->motion_id;

        switch (msid) {
        case ftMt_MS_SpecialNStart:
        case ftMt_MS_SpecialNLoop:
        case ftMt_MS_SpecialNFull:
        case ftMt_MS_SpecialNCancel:
        case ftMt_MS_SpecialNEnd:
        case ftMt_MS_SpecialAirNStart:
        case ftMt_MS_SpecialAirNLoop:
        case ftMt_MS_SpecialAirNFull:
        case ftMt_MS_SpecialAirNCancel:
        case ftMt_MS_SpecialAirNEnd:

            if (fp->x2070.x2071_b6 != false) {
                return true;
            }
            return false;
        }
        return true;
    }
    return true;
}

// 0x80146D74
// https://decomp.me/scratch/s3eQH // Check to stash Shadow Ball?
bool ftMt_SpecialN_CheckShadowBallCancel(HSD_GObj* gobj)
{
    s32 msid;

    if (gobj != NULL) {
        msid = getFighter(gobj)->motion_id;
        switch (msid) {
        case ftMt_MS_SpecialNStart:
        case ftMt_MS_SpecialNLoop:
        case ftMt_MS_SpecialNFull:
        case ftMt_MS_SpecialNEnd:
        case ftMt_MS_SpecialAirNStart:
        case ftMt_MS_SpecialAirNLoop:
        case ftMt_MS_SpecialAirNFull:
        case ftMt_MS_SpecialAirNEnd:
            return false;

        default:
        case ftMt_MS_SpecialNCancel:
        case ftMt_MS_SpecialAirNCancel:
            return true;
        }
    } else {
        return true;
    }
}

static inline void ftMewtwo_SpecialN_ClearGObj(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = getFighter(gobj);
        if (fp->fv.mt.x2238_shadowBallGObj != NULL) {
            efLib_DestroyAll(gobj);
            fp->fv.mt.x2238_shadowBallGObj = NULL;
        }
    }
}

// 0x80146DC8
// https://decomp.me/scratch/gzSFm // Clear Shadow Ball GObj pointer and reset
// flag
void ftMt_SpecialN_SetNULL(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = getFighter(gobj);
        if (fp->fv.mt.x2230_shadowHeldGObj != NULL) {
            fp->fv.mt.x2230_shadowHeldGObj = NULL;
        }
        ftMewtwo_SpecialN_ClearGObj(gobj);
    }
}

static inline void ftMewtwo_SpecialN_RemoveHeldShadowBall(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    Fighter* fp2 = fp = getFighter(gobj);

    if (gobj != NULL) {
        if (fp->fv.mt.x2230_shadowHeldGObj != NULL) {
            it_802C573C(fp->fv.mt.x2230_shadowHeldGObj);
            fp->fv.mt.x2230_shadowHeldGObj = NULL;
        }
        if (gobj != NULL) {
            Fighter* fp2 = fp2 = getFighter(gobj);
            if (fp2->fv.mt.x2238_shadowBallGObj != NULL) {
                efLib_DestroyAll(gobj);
                fp2->fv.mt.x2238_shadowBallGObj = NULL;
            }
        }
    }
    fp2->fv.mt.x2234_shadowBallCharge = 0;
    ft_800BFFAC(fp2);
    efLib_DestroyAll(gobj);
}

// 0x80146E30
// https://decomp.me/scratch/kHPon
/// Remove Shadow Ball when taking damage
void ftMt_SpecialN_OnTakeDamage(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj != NULL) {
        ftMewtwo_SpecialN_RemoveHeldShadowBall(gobj);
    }
}

/// Remove Shadow Ball OnDeath2?
void ftMt_SpecialN_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj != NULL) {
        Fighter* fp = fp = GET_FIGHTER(gobj);
        Fighter* fp2 = GET_FIGHTER(gobj);
        ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
        fp2 = fp = getFighter(gobj);

        if (gobj != NULL) {
            if (fp->fv.mt.x2230_shadowHeldGObj != NULL) {
                it_802C573C(fp->fv.mt.x2230_shadowHeldGObj);
                fp->fv.mt.x2230_shadowHeldGObj = NULL;
            }
            if (gobj != NULL) {
                Fighter* fp2 = fp2 = getFighter(gobj);
                if (fp2->fv.mt.x2238_shadowBallGObj != NULL) {
                    efLib_DestroyAll(gobj);
                    fp2->fv.mt.x2238_shadowBallGObj = NULL;
                }
            }
        }
        if ((f32) fp2->fv.mt.x2234_shadowBallCharge !=
            mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES)
        {
            fp2->fv.mt.x2234_shadowBallCharge = 0;
            ft_800BFFAC(fp2);
            efLib_DestroyAll(gobj);
        }
    }
}

static void ftMewtwo_SpecialN_GetPos(Fighter* fp, Vec3* sp38)
{
    Vec3 sp2C;
    sp2C.z = 2.0f;
    sp2C.y = 0.0f;
    sp2C.x = 0.0f;
    lb_8000B1CC(fp->parts[0x23].x0_jobj, &sp2C, sp38);
    sp38->z = 0.0f;
}

static void ftMewtwo_SpecialN_SetRecoil(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    if (((s32) fp->motion_id == ftMt_MS_SpecialAirNEnd) ||
        ((s32) fp->ground_or_air == GA_Air))
    {
        fp->x80_self_vel.x =
            fp->facing_dir * (mewtwoAttrs->x8_MEWTWO_SHADOWBALL_AIR_RECOIL_X *
                              (f32) fp->fv.mt.x2234_shadowBallCharge);
    }
    if (((s32) fp->motion_id == ftMt_MS_SpecialNEnd) ||
        ((s32) fp->ground_or_air == GA_Ground))
    {
        fp->gr_vel = fp->facing_dir *
                     (mewtwoAttrs->x4_MEWTWO_SHADOWBALL_GROUND_RECOIL_X *
                      (f32) fp->fv.mt.x2234_shadowBallCharge);
    }
}

// 0x80146FA8
// https://decomp.me/scratch/6f5xe // Shoot Shadow Ball
void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj)
{
    Fighter* fp2;
    Fighter* fp;
    Fighter* temp_fp;
    ftMewtwoAttributes* mewtwoAttrs;
    HSD_GObj* shadowBallGObj;
    f64 facingDir;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

/// @todo Missing @c inline function(s).
#ifdef MUST_MATCH
    fp = fp = getFighter(gobj);
    mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
#else
    fp = getFighter(gobj);
    mewtwoAttrs = getFtSpecialAttrsD(fp);
#endif

    if (((u32) fp->x2204_ftcmd_var1 == 1U) &&
        (fp->fv.mt.x2230_shadowHeldGObj != NULL))
    {
        Vec3 sp38;
        fp->x2204_ftcmd_var1 = 2;
        ftMewtwo_SpecialN_GetPos(fp, &sp38);
        shadowBallGObj = fp->x1974_heldItem;
        if (1.0f == fp->facing_dir) {
            facingDir = (f64) 0.0;
        } else {
            facingDir = M_PI;
        }
        it_802C53F0(fp->fv.mt.x2230_shadowHeldGObj, &sp38, (f32) facingDir,
                    (f32) (u32) fp->fv.mt.x2234_shadowBallCharge,
                    mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES);
        ftMewtwo_SpecialN_SetRecoil(gobj);
        fp->fv.mt.x2234_shadowBallCharge = 0;
        if (gobj != NULL) {
/// @todo Missing @c inline function(s).
#ifdef MUST_MATCH
            temp_fp = temp_fp = getFighter(gobj);
#else
            temp_fp = getFighter(gobj);
#endif

            if (temp_fp->fv.mt.x2230_shadowHeldGObj != NULL) {
                temp_fp->fv.mt.x2230_shadowHeldGObj = NULL;
            }
            if (gobj != NULL) {
/// @todo Missing @c inline function(s).
#ifdef MUST_MATCH
                fp2 = fp2 = getFighter(gobj);
#else
                fp2 = getFighter(gobj);
#endif

                if (fp2->fv.mt.x2238_shadowBallGObj != NULL) {
                    efLib_DestroyAll(gobj);
                    fp2->fv.mt.x2238_shadowBallGObj = NULL;
                }
            }
        }
        fp->x1974_heldItem = shadowBallGObj;
        if ((f32) fp->fv.mt.x2234_shadowBallCharge ==
            mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES)
        {
            ft_80088148(fp, 0x30DB6U, SFX_VOLUME_MAX, SFX_PAN_MID);
            return;
        }
        ft_80088148(fp, 0x30DB3U, SFX_VOLUME_MAX, SFX_PAN_MID);
    }
}

// 0x801471C8
// https://decomp.me/scratch/QGj1l // Play Shadow Ball Charge SFX
void ftMt_SpecialN_PlayChargeSFX(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMewtwoAttributes* mewtwoAttrs = fp->x2D4_specialAttributes;
    static u32 shadowBallSFX[4] = { 0x30DB9, 0x30DBC, 0x30DBF, 0x30DC2 };
    f32 chargeLevel;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if ((u32) fp->x2208_ftcmd_var2 != 0U) {
        if (fp->fv.mt.x2234_shadowBallCharge != 0) {
            chargeLevel = (f32) fp->fv.mt.x2234_shadowBallCharge /
                          mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
        } else {
            chargeLevel = 0.0f;
        }
        if (fp->mv.mt.SpecialN.chargeLevel > 0.0f) {
            if ((chargeLevel > 0.75f) &&
                (fp->mv.mt.SpecialN.chargeLevel <= 0.75f))
            {
                fp->mv.mt.SpecialN.chargeLevel = chargeLevel;
                ft_80088510(fp, shadowBallSFX[3], SFX_VOLUME_MAX, SFX_PAN_MID);
                return;
            }
            if ((chargeLevel > 0.5f) &&
                (fp->mv.mt.SpecialN.chargeLevel <= 0.5f))
            {
                fp->mv.mt.SpecialN.chargeLevel = chargeLevel;
                ft_80088510(fp, shadowBallSFX[2], SFX_VOLUME_MAX, SFX_PAN_MID);
                return;
            }
            if ((chargeLevel > 0.25f) &&
                (fp->mv.mt.SpecialN.chargeLevel <= 0.25f))
            {
                fp->mv.mt.SpecialN.chargeLevel = chargeLevel;
                ft_80088510(fp, shadowBallSFX[1], SFX_VOLUME_MAX, SFX_PAN_MID);
                return;
            }
            if ((chargeLevel > 0.0f) &&
                (fp->mv.mt.SpecialN.chargeLevel <= 0.0f))
            {
                fp->mv.mt.SpecialN.chargeLevel = chargeLevel;
                ft_80088510(fp, shadowBallSFX[0], SFX_VOLUME_MAX, SFX_PAN_MID);
            }
        } else {
            fp->mv.mt.SpecialN.chargeLevel = (f32) 9.999999747378752e-5f;
            ft_80088510(fp, shadowBallSFX[0], SFX_VOLUME_MAX, SFX_PAN_MID);
        }
    }
}

inline void ftMewtwo_SpecialN_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->cb.x21E4_callback_OnDeath2 = ftMt_Init_OnDeath2;
    fp->cb.x21DC_callback_OnTakeDamage = ftMt_Init_OnTakeDamage;
    fp->cb.x21E8_callback_OnDeath3 = ftMt_Init_OnDeath2;
}

inline void ftMewtwo_SpecialN_ChangeAction(HSD_GObj* gobj)

{
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    s32 releaseLag;

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNStart, 0, NULL, 0.0f, 1.0f,
                              0.0f);

    releaseLag = 0;
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    ftCommon_8007D7FC(fp);

    fp->x80_self_vel.y = 0.0f;

    ftMewtwo_SpecialN_SetCall(gobj);

    fp->mv.mt.SpecialN.isFull = false;
    fp->mv.mt.SpecialN.x2344 = (u32) 0;

    if ((s32) fp->fv.mt.x2234_shadowBallCharge == 0) {
        releaseLag = mewtwoAttrs->x10_MEWTWO_SHADOWBALL_RELEASE_LAG;
    }
    fp->mv.mt.SpecialN.releaseLag = releaseLag;
    fp->mv.mt.SpecialN.chargeLevel = 0.0f;

    ftAnim_8006EBA4(gobj);
}

// 0x80147320
// https://decomp.me/scratch/zcZ5Y // Mewtwo's grounded Shadow Ball Start
// Motion State handler
void ftMt_SpecialN_Enter(HSD_GObj* gobj)
{
    ftMewtwo_SpecialN_ChangeAction(gobj);
}

inline void ftMewtwo_SpecialAirN_ChangeAction(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    u32 releaseLag;

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNStart, 0, NULL, 0.0f,
                              1.0f, 0.0f);

    releaseLag = 0;

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    ftMewtwo_SpecialN_SetCall(gobj);

    fp->mv.mt.SpecialN.isFull = false;
    fp->mv.mt.SpecialN.x2344 = (u32) 0;

    if ((s32) fp->fv.mt.x2234_shadowBallCharge == 0) {
        releaseLag = mewtwoAttrs->x10_MEWTWO_SHADOWBALL_RELEASE_LAG;
    }

    fp->mv.mt.SpecialN.releaseLag = releaseLag;
    fp->mv.mt.SpecialN.chargeLevel = 0.0f;

    fp->x80_self_vel.y *= 0.5f;

    ftAnim_8006EBA4(gobj);
}

// 0x801473F4
// https://decomp.me/scratch/okSqF // Mewtwo's aerial Shadow Ball Start Action
// State handler
void ftMt_SpecialAirN_Enter(HSD_GObj* gobj)
{
    ftMewtwo_SpecialAirN_ChangeAction(gobj);
}

// 0x801474C0
// https://decomp.me/scratch/KY0xt // Mewtwo's grounded Shadow Ball Start
// Animation callback
void ftMt_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Vec3 sp2C;
    Vec3 sp20;
    Fighter* fp = fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    HSD_GObj* shadowHeldGObj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    if (((u32) fp->x220C_ftcmd_var3 == 1U) &&
        (fp->fv.mt.x2230_shadowHeldGObj == NULL))
    {
        sp2C.z = 2.0f;
        sp2C.y = 0.0f;
        sp2C.x = 0.0f;
        lb_8000B1CC(fp->parts[0x23].x0_jobj, &sp2C, &sp20);
        sp20.z = 0.0f;
        shadowHeldGObj = it_802C5000(
            gobj, &sp20, 0x23, It_Kind_Mewtwo_ShadowBall, fp->facing_dir);
        fp->fv.mt.x2230_shadowHeldGObj = shadowHeldGObj;
        if (shadowHeldGObj != NULL) {
            ftMewtwo_SpecialN_SetCall(gobj);
        } else {
            fp->fv.mt.x2230_shadowHeldGObj = NULL;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (((s32) fp->mv.mt.SpecialN.isFull == true) ||
            ((f32) fp->fv.mt.x2234_shadowBallCharge ==
             mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES))
        {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNEnd, 0, NULL, 0.0f,
                                      1.0f, 0.0f);
        } else {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNLoop, 0, NULL,
                                      0.0f, 1.0f, 0.0f);
            fp->mv.mt.SpecialN.x2348 = false;
        }
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

inline void ftMewtwo_SpecialN_CreateHeldShadow(HSD_GObj* gobj, Vec3* pos1,
                                               Vec3* pos2)
{
    Fighter* fp = getFighter(gobj);

    if (((u32) fp->x220C_ftcmd_var3 == 1U) &&
        (fp->fv.mt.x2230_shadowHeldGObj == NULL))
    {
        HSD_GObj* shadowHeldGObj;

        pos1->z = 2.0f;
        pos1->y = 0.0f;
        pos1->x = 0.0f;
        lb_8000B1CC(fp->parts[0x23].x0_jobj, pos1, pos2);
        pos2->z = 0.0f;
        shadowHeldGObj = it_802C5000(
            gobj, pos2, 0x23, It_Kind_Mewtwo_ShadowBall, fp->facing_dir);
        fp->fv.mt.x2230_shadowHeldGObj = shadowHeldGObj;
        if (shadowHeldGObj != NULL) {
            ftMewtwo_SpecialN_SetCall(gobj);
        } else {
            fp->fv.mt.x2230_shadowHeldGObj = NULL;
        }
    }
}

// 0x8014764C
// https://decomp.me/scratch/fZA6w // Mewtwo's grounded Shadow Ball Loop
// Animation callback
void ftMt_SpecialNLoop_Anim(HSD_GObj* gobj)
{
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Vec3 sp1C;
    const Vec3 shadowBallPos = { 0.0f, 7.0f, 0.0f };

    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = fp->x2D4_specialAttributes;

    sp34 = shadowBallPos;

    fp->mv.mt.SpecialN.releaseLag--;
    if (fp->mv.mt.SpecialN.releaseLag <= 0) {
        fp->mv.mt.SpecialN.releaseLag = 0;
        ftMewtwo_SpecialN_CreateHeldShadow(gobj, &sp28, &sp1C);
        ftMt_SpecialN_PlayChargeSFX(gobj);
        if ((s32) fp->mv.mt.SpecialN.x2348 == false) {
            fp->mv.mt.SpecialN.x2344++;
            if ((s32) fp->mv.mt.SpecialN.x2344 >
                (s32) mewtwoAttrs->xC_MEWTWO_SHADOWBALL_CHARGE_ITERATIONS)
            {
                fp->mv.mt.SpecialN.x2344 = 0;
                fp->fv.mt.x2234_shadowBallCharge++;
                if ((f32) fp->fv.mt.x2234_shadowBallCharge >=
                    mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES)
                {
                    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNFull,
                                              FTMEWTWO_SPECIALN_ACTION_FLAG,
                                              NULL, fp->x894_currentAnimFrame,
                                              1.0f, 0.0f);
                    fp->fv.mt.x2234_shadowBallCharge =
                        (s32) mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
                    fp->mv.mt.SpecialN.x2348 = true;
                    ftCommon_8007EBAC(fp, 0xCU, 0U);
                    lb_8000B1CC(fp->parts[0].x0_jobj, &sp34, &sp40);
                    efSync_Spawn(0x1B, gobj, &sp40);
                    ft_800BFFD0(fp, 0x5C, 0);
                }
            }
        }
    }
}

// 0x80147850
// https://decomp.me/scratch/Fn7lE // Set Shadow Ball vars to full charge?
void ftMt_SpecialNFull_Anim(HSD_GObj* gobj)
{
    Fighter* fp = fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);

    fp->mv.mt.SpecialN.x2348 = true;
    fp->fv.mt.x2234_shadowBallCharge =
        mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
}

inline void ftMewtwo_SpecialN_RemoveShadowBall2(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = getFighter(gobj);

        if (fp->fv.mt.x2230_shadowHeldGObj != NULL) {
            it_802C573C(fp->fv.mt.x2230_shadowHeldGObj);
            fp->fv.mt.x2230_shadowHeldGObj = NULL;
        }
        ftMewtwo_SpecialN_ClearGObj(gobj);
    }
}

/// Mewtwo's grounded Shadow Ball Cancel Animation callback
void ftMt_SpecialNCancel_Anim(HSD_GObj* gobj)
{
#ifdef MUST_MATCH
    u8 _[24];
#endif

    ftMewtwo_SpecialN_RemoveShadowBall2(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// Mewtwo's grounded Shadow Ball End Animation callback
void ftMt_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    ftMt_SpecialN_ReleaseShadowBall(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x80147954
// https://decomp.me/scratch/sgOTM // Mewtwo's aerial Shadow Ball Start
// Animation callback
void ftMt_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    Vec3 sp2C;
    Vec3 sp20;
    Fighter* fp = fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    HSD_GObj* shadowHeldGObj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    if (((u32) fp->x220C_ftcmd_var3 == 1U) &&
        (fp->fv.mt.x2230_shadowHeldGObj == NULL))
    {
        sp2C.z = 2.0f;
        sp2C.y = 0.0f;
        sp2C.x = 0.0f;
        lb_8000B1CC(fp->parts[0x23].x0_jobj, &sp2C, &sp20);
        sp20.z = 0.0f;
        shadowHeldGObj = it_802C5000(
            gobj, &sp20, 0x23, It_Kind_Mewtwo_ShadowBall, fp->facing_dir);
        fp->fv.mt.x2230_shadowHeldGObj = shadowHeldGObj;
        if (shadowHeldGObj != NULL) {
            ftMewtwo_SpecialN_SetCall(gobj);
        } else {
            fp->fv.mt.x2230_shadowHeldGObj = NULL;
        }
    }
    fp->mv.mt.SpecialN.isFull = false;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (((s32) fp->mv.mt.SpecialN.isFull == true) ||
            ((f32) fp->fv.mt.x2234_shadowBallCharge ==
             mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES))
        {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNEnd, 0, NULL,
                                      0.0f, 1.0f, 0.0f);
        } else {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNLoop, 0, NULL,
                                      0.0f, 1.0f, 0.0f);
            fp->mv.mt.SpecialN.x2348 = false;
        }
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

// 0x80147AEC
// https://decomp.me/scratch/Ngg62 // Mewtwo's aerial Shadow Ball Loop
// Animation callback
void ftMt_SpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Vec3 sp1C;
    const Vec3 shadowBallPos = { 0.0f, 7.0f, 0.0f };

    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = fp->x2D4_specialAttributes;

    sp34 = shadowBallPos;

    fp->mv.mt.SpecialN.releaseLag--;
    if (fp->mv.mt.SpecialN.releaseLag <= 0) {
        fp->mv.mt.SpecialN.releaseLag = 0;
        ftMewtwo_SpecialN_CreateHeldShadow(gobj, &sp28, &sp1C);
        ftMt_SpecialN_PlayChargeSFX(gobj);
        if ((s32) fp->mv.mt.SpecialN.x2348 == false) {
            fp->mv.mt.SpecialN.x2344++;
            if ((s32) fp->mv.mt.SpecialN.x2344 >
                (s32) mewtwoAttrs->xC_MEWTWO_SHADOWBALL_CHARGE_ITERATIONS)
            {
                fp->mv.mt.SpecialN.x2344 = 0;
                fp->fv.mt.x2234_shadowBallCharge++;
                if ((f32) fp->fv.mt.x2234_shadowBallCharge >=
                    mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES)
                {
                    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNFull,
                                              FTMEWTWO_SPECIALN_ACTION_FLAG,
                                              NULL, fp->x894_currentAnimFrame,
                                              1.0f, 0.0f);
                    fp->fv.mt.x2234_shadowBallCharge =
                        (s32) mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
                    fp->mv.mt.SpecialN.x2348 = 1;
                    ftCommon_8007EBAC(fp, 0xCU, 0U);

                    lb_8000B1CC(fp->parts[0].x0_jobj, &sp34, &sp40);
                    efSync_Spawn(0x1B, gobj, &sp40);
                    ft_800BFFD0(fp, 0x5C, 0);
                }
            }
        }
    }
}

// 0x8014CF0
// https://decomp.me/scratch/Fn7lE // Set Shadow Ball vars to full charge?
void ftMt_SpecialAirNFull_Anim(HSD_GObj* gobj)
{
    Fighter* fp = fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);

    fp->mv.mt.SpecialN.x2348 = false;
    fp->fv.mt.x2234_shadowBallCharge =
        mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
}

// 0x80147D20
// https://decomp.me/scratch/7U2EJ // Mewtwo's aerial Shadow Ball Cancel
// Animation callback
void ftMt_SpecialAirNCancel_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    ftMewtwo_SpecialN_RemoveShadowBall2(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

// Mewtwo's aerial Shadow Ball End Animation callback
void ftMt_SpecialAirNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftMt_SpecialN_ReleaseShadowBall(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (0.0f == mewtwoAttrs->x14_MEWTWO_SHADOWBALL_LANDING_LAG) {
            ft_800CC730(gobj);
            return;
        }
        ft_80096900(gobj, 1, 0, true, 1.0f,
                    mewtwoAttrs->x14_MEWTWO_SHADOWBALL_LANDING_LAG);
    }
}

// 0x80147E30 - Mewtwo's grounded Shadow Ball Start IASA callback
void ftMt_SpecialNStart_IASA(HSD_GObj* gobj)
{
    return;
}

/// Mewtwo's grounded Shadow Ball Loop IASA callback
void ftMt_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    u32 recentInput;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[48];
#endif

    if (ft_8009917C(gobj) != false) {
        ftMewtwo_SpecialN_RemoveShadowBall2(gobj);
    } else {
        recentInput = fp->input.x668;
        if ((recentInput & HSD_BUTTON_A) &&
            (fp->mv.mt.SpecialN.releaseLag <= 0))
        {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNEnd, 0, NULL, 0.0f,
                                      1.0f, 0.0f);
            ftMewtwo_SpecialN_SetCall(gobj);
            return;
        }
        if ((recentInput & HSD_BUTTON_B) != false) {
            if (fp->mv.mt.SpecialN.releaseLag <= 0) {
                Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNEnd, 0, NULL,
                                          0.0f, 1.0f, 0.0f);
                ftMewtwo_SpecialN_SetCall(gobj);
            }
        } else if ((recentInput & HSD_BUTTON_LR) != false) {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNCancel, 0, NULL,
                                      0.0f, 1.0f, 0.0f);
            ftMewtwo_SpecialN_RemoveShadowBall2(gobj);
            ftMewtwo_SpecialN_SetCall(gobj);
        }
    }
}

// 0x8014800C
// https://decomp.me/scratch/w0g66 // Mewtwo's grounded Shadow Ball Full Charge
// IASA callback
void ftMt_SpecialNFull_IASA(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    u32 recentInput;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[48];
#endif

    if (ft_8009917C(gobj) != false) {
        ftMewtwo_SpecialN_RemoveShadowBall2(gobj);
    } else {
        recentInput = fp->input.x668;
        if ((recentInput & HSD_BUTTON_A) != false) {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNEnd, 0, NULL, 0.0f,
                                      1.0f, 0.0f);
            ftMewtwo_SpecialN_SetCall(gobj);
            return;
        }
        if ((recentInput & HSD_BUTTON_B) != false) {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNEnd, 0, NULL, 0.0f,
                                      1.0f, 0.0f);
            ftMewtwo_SpecialN_SetCall(gobj);
        } else if ((recentInput & HSD_BUTTON_LR) != false) {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNCancel, 0, NULL,
                                      0.0f, 1.0f, 0.0f);
            ftMewtwo_SpecialN_RemoveShadowBall2(gobj);
            ftMewtwo_SpecialN_SetCall(gobj);
        }
    }
}

// 0x801481CC - Mewtwo's grounded Shadow Ball Cancel IASA callback
void ftMt_SpecialNCancel_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x801481D0 - Mewtwo's grounded Shadow Ball End IASA callback
void ftMt_SpecialNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x801481D4 - Mewtwo's aerial Shadow Ball Start IASA callback
void ftMt_SpecialAirNStart_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x801481D8
// https://decomp.me/scratch/FYwNg // Mewtwo's aerial Shadow Ball Loop IASA
// callback
void ftMt_SpecialAirNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    u32 recentInput;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[32];
#endif

    recentInput = fp->input.x668;
    if (((recentInput & HSD_BUTTON_A) != false) &&
        (fp->mv.mt.SpecialN.releaseLag <= 0))
    {
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNEnd, 0, NULL, 0.0f,
                                  1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
        return;
    }
    if ((recentInput & HSD_BUTTON_B) != false) {
        if (fp->mv.mt.SpecialN.releaseLag <= 0) {
            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNEnd, 0, NULL,
                                      0.0f, 1.0f, 0.0f);
            ftMewtwo_SpecialN_SetCall(gobj);
        }
    } else if ((recentInput & HSD_BUTTON_LR) != false) {
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNCancel, 0, NULL,
                                  0.0f, 1.0f, 0.0f);
        ftMewtwo_SpecialN_RemoveShadowBall2(gobj);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

/// Mewtwo's aerial Shadow Ball Full Charge IASA callback
void ftMt_SpecialAirNFull_IASA(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    u32 recentInput;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[32];
#endif

    recentInput = fp->input.x668;
    if ((recentInput & HSD_BUTTON_A) != false) {
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNEnd, 0, NULL, 0.0f,
                                  1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
        return;
    }
    if ((recentInput & HSD_BUTTON_B) != false) {
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNEnd, 0, NULL, 0.0f,
                                  1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    } else if ((recentInput & HSD_BUTTON_LR) != false) {
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNCancel, 0, NULL,
                                  0.0f, 1.0f, 0.0f);
        ftMewtwo_SpecialN_RemoveShadowBall2(gobj);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

// 0x801484B8 - Mewtwo's aerial Shadow Ball Cancel IASA callback
void ftMt_SpecialAirNCancel_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x801484BC - Mewtwo's aerial Shadow Ball End IASA callback
void ftMt_SpecialAirNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x801484C0 - Mewtwo's grounded Shadow Ball Start Physics callback
void ftMt_SpecialNStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x801484E0 - Mewtwo's grounded Shadow Ball Loop Physics callback
void ftMt_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x80148500 - Mewtwo's grounded Shadow Ball Full Charge Physics callback
void ftMt_SpecialNFull_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x80148520 - Mewtwo's grounded Shadow Ball Cancel Physics callback
void ftMt_SpecialNCancel_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x80148540 - Mewtwo's grounded Shadow Ball End Physics callback
void ftMt_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x80148560 - Mewtwo's aerial Shadow Ball Start Physics callback
void ftMt_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 0x80148580 - Mewtwo's aerial Shadow Ball Loop Physics callback
void ftMt_SpecialAirNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 0x801485A0 - Mewtwo's aerial Shadow Ball Full Charge Physics callback
void ftMt_SpecialAirNFull_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 0x801485C0 - Mewtwo's aerial Shadow Ball Cancel Physics callback
void ftMt_SpecialAirNCancel_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 0x801485E0 - Mewtwo's aerial Shadow Ball End Physics callback
void ftMt_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 0x80148600
// https://decomp.me/scratch/2J4uh // Mewtwo's grounded Shadow Ball Start
// Collision callback
void ftMt_SpecialNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80082708(gobj) == false) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNStart,
                                  FTMEWTWO_SPECIALN_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

// 0x8014868C - Mewtwo's grounded Shadow Ball Loop Collision callback
void ftMt_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80082708(gobj) == false) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(
            gobj, ftMt_MS_SpecialAirNLoop,
            (FtStateChange_PreserveSfx | FTMEWTWO_SPECIALN_COLL_FLAG), NULL,
            fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

/// Mewtwo's grounded Shadow Ball Full Charge Collision callback
void ftMt_SpecialNFull_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80082708(gobj) == false) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(
            gobj, ftMt_MS_SpecialAirNFull,
            (FtStateChange_PreserveSfx | FTMEWTWO_SPECIALN_COLL_FLAG), NULL,
            fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

/// Mewtwo's grounded Shadow Ball Cancel Collision callback
void ftMt_SpecialNCancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80082708(gobj) == false) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNCancel,
                                  FTMEWTWO_SPECIALN_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

// 0x80148830 - Mewtwo's grounded Shadow Ball Cancel Collision callback
void ftMt_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80082708(gobj) == false) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirNEnd,
                                  FTMEWTWO_SPECIALN_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

/// Mewtwo's aerial Shadow Ball Start Collision callback
void ftMt_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80081D0C(gobj) == true) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNStart,
                                  FTMEWTWO_SPECIALN_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

/// Mewtwo's aerial Shadow Ball Loop Collision callback
void ftMt_SpecialAirNLoop_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80081D0C(gobj) == true) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(
            gobj, ftMt_MS_SpecialNLoop,
            (FtStateChange_PreserveSfx | FTMEWTWO_SPECIALN_COLL_FLAG), NULL,
            fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

// Mewtwo's aerial Shadow Ball Full Charge Collision callback
void ftMt_SpecialAirNFull_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80081D0C(gobj) == true) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(
            gobj, ftMt_MS_SpecialNFull,
            (FtStateChange_PreserveSfx | FTMEWTWO_SPECIALN_COLL_FLAG), NULL,
            fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

/// Mewtwo's aerial Shadow Ball Cancel Collision callback
void ftMt_SpecialAirNCancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80081D0C(gobj) == true) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNCancel,
                                  FTMEWTWO_SPECIALN_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

/// Mewtwo's aerial Shadow Ball End Collision callback
void ftMt_SpecialAirNEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ft_80081D0C(gobj) == true) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialNEnd,
                                  FTMEWTWO_SPECIALN_COLL_FLAG, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftMewtwo_SpecialN_SetCall(gobj);
    }
}

static inline void ftMewtwo_SpecialN_LaunchShadowBall(HSD_GObj* gobj)
{
    Vec3 sp20;
    Vec3 sp2C;

    Fighter* fp = getFighter(gobj);

    if (ftGetKind(fp) == FTKIND_MEWTWO) {
        ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
        if ((u32) fp->x220C_ftcmd_var3 == 1U) {
            fp->x220C_ftcmd_var3 = 0;
            lb_8000B1CC(fp->parts[0x23].x0_jobj, NULL, &sp20);
            lb_8000B1CC(fp->parts[0x20].x0_jobj, NULL, &sp2C);
            sp2C.z = 0.0f;
            sp20.z = 0.0f;
            it_802C519C(gobj, &sp20, It_Kind_Mewtwo_ShadowBall,
                        mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES,
                        atan2f(sp20.y - sp2C.y, sp20.x - sp2C.x),
                        fp->facing_dir);
            ft_80088148(fp, 0x30DB3U, SFX_VOLUME_MAX, SFX_PAN_MID);
        }
    }
}

/// Create F-Throw Shadow Ball
void ftMt_SpecialN_Shoot(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ftMewtwo_SpecialN_LaunchShadowBall(gobj);
}
