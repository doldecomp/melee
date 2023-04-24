#include "forward.h"

#include "ftFx_SpecialN.h"

#include "ftFx_Init.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx/types.h>
#include <dolphin/os/os.h>

void ftFx_SpecialN_FtGetHoldJoint(HSD_GObj* gobj, Vec3* pos)
{
    /// @todo Shared @c inline with #ftFx_SpecialN_ItGetHoldJoint.
    Vec3 sp14;

    // Double fp init otherwise this will not match when inlined
    Fighter* fp = fp = GET_FIGHTER(gobj);

    sp14.x = 0;
    sp14.y = 1.2325000762939453f;
    sp14.z = 4.263599872589111f;

    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].x0_jobj,
                &sp14, pos);
}

void ftFx_SpecialN_ItGetHoldJoint(HSD_GObj* gobj, Vec3* pos)
{
    Vec3 sp14;
    Fighter* fp = fp = GET_FIGHTER(gobj);

    sp14.x = 0;
    sp14.y = 1.2325000762939453f;
    sp14.z = 0.013600001111626625f;

    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].x0_jobj,
                &sp14, pos);
}

// 0x800E5D90
// https://decomp.me/scratch/DRgo9 // Fox & Falco's Blaster OnMotionStateChange
// function
void ftFx_SpecialN_OnChangeAction(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ft_800892A0(gobj);
    ft_80089824(gobj);
}

// 0x800E5DC4
// https://decomp.me/scratch/A0n4M // Check if Fox/Falco has a Blaster GOBj
// pointer
bool ftFx_SpecialN_CheckRemoveBlaster(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.fx.x222C_blasterGObj == NULL) {
        return true;
    }
    return false;
}

// 0x800E5DE4 - shoutouts to Olifr� for figuring this one out!
// https://decomp.me/scratch/aatYF // Get msid for Fox/Falco moves that require
// the Blaster item
s32 ftFx_SpecialN_GetBlasterAction(HSD_GObj* gobj)
{
    s32 msid = 9;

    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            s32 currASID = fp->motion_id;
            switch (currASID) {
            case ftFx_MS_SpecialNStart:
            case ftFx_MS_SpecialNLoop:
            case ftFx_MS_SpecialNEnd:
            case ftFx_MS_SpecialAirNStart:
            case ftFx_MS_SpecialAirNLoop:
            case ftFx_MS_SpecialAirNEnd:
                msid = currASID - ftFx_MS_SpecialNStart;
                break;

            case ftCo_MS_ThrowB:
            case ftCo_MS_ThrowHi:
            case ftCo_MS_ThrowLw:
                msid = currASID - ftCo_MS_CatchDash;
            }
        }
    }
    return msid;
}

// 0x800E5E38
// https://decomp.me/scratch/f6oIX // Check if Fox/Falco is performing a move
// that requires the Blaster item
bool ftFx_SpecialN_CheckBlasterAction(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        s32 msid = fp->motion_id;
        switch (msid) {
        case ftFx_MS_SpecialNStart:
        case ftFx_MS_SpecialNLoop:
        case ftFx_MS_SpecialNEnd:
        case ftFx_MS_SpecialAirNStart:
        case ftFx_MS_SpecialAirNLoop:
        case ftFx_MS_SpecialAirNEnd:
        case ftCo_MS_ThrowB:
        case ftCo_MS_ThrowHi:
        case ftCo_MS_ThrowLw:

            if (fp->x2070.x2071_b6 != false) {
                return true;
            }
            return false;
        }
    }
    return true;
}

inline void ftFox_SpecialN_SetNULL(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
}

// 0x800E5E90
// https://decomp.me/scratch/4v8j4 // Clear Blaster GObj pointer and callbacks
void ftFx_SpecialN_ClearBlaster(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.fx.x222C_blasterGObj != NULL) {
        fp->fv.fx.x222C_blasterGObj = NULL;
    }
    ftFox_SpecialN_SetNULL(gobj);
}

// 0x800E5EBC
// https://decomp.me/scratch/WglAb // Remove Blaster item
void ftFx_SpecialN_RemoveBlaster(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->fv.fx.x222C_blasterGObj != NULL) {
        it_802AEAB4(fp->fv.fx.x222C_blasterGObj);
        fp->fv.fx.x222C_blasterGObj = NULL;
    }
    if (ftFx_Init_800E5534(gobj) == false) {
        ftFox_SpecialN_SetNULL(gobj);
    }
}

u32 foxSFX[2] = { 110103, 110106 };
u32 falcoSFX[2] = { 100099, 100102 };

// 0x800E5F28
// https://decomp.me/scratch/iPgDc // Create Blaster Shot Item
void ftFx_SpecialN_CreateBlasterShot(HSD_GObj* gobj)
{
    /** @todo Shared @c inline with #ftFx_SpecialNLoop_Anim and
     * #ftFx_SpecialAirNLoop_Anim.
     */
    Vec3 sp2C;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ftFoxAttributes* foxAttrs;
    Fighter* fp;
    f64 launchAngle;
    s32 ftKind;

#ifdef MUST_MATCH
    /// @todo Seems fake, probably one or more missing @c inline functions.
    fp = fp = GET_FIGHTER(gobj);
#else
    fp = GET_FIGHTER(gobj);
#endif

    foxAttrs = getFtSpecialAttrs(fp);

    if ((u32) fp->x2208_ftcmd_var2 != 0U) {
        fp->x2208_ftcmd_var2 = 0U;
        ftFx_SpecialN_FtGetHoldJoint(gobj, &sp2C);
        sp2C.z = 0;

        if (1 == fp->facing_dir) {
            launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
        } else {
            launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;
        }

        it_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, gobj, &sp2C,
                    foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);

        it_802AE1D0(fp->fv.fx.x222C_blasterGObj);
        ftKind = ftLib_800872A4(gobj);

        switch (ftKind) {
        case FTKIND_FOX:
            ft_80088148(fp, foxSFX[-1 == fp->facing_dir], SFX_VOLUME_MAX,
                        SFX_PAN_MID);
            return;

        case FTKIND_FALCO:
            ft_80088148(fp, falcoSFX[-1 == fp->facing_dir], SFX_VOLUME_MAX,
                        SFX_PAN_MID);
            return;
        }
    }
}

inline void ftFox_SpecialN_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = ftFx_Init_800E5588;
    fp->cb.x21E4_callback_OnDeath2 = ftFx_Init_800E5588;
}

// 0x800E608C
// https://decomp.me/scratch/B3aTL // Fox & Falco's grounded Blaster Action
// State handler
void ftFx_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    HSD_GObj* blasterGObj;

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialNStart, 0, NULL, 0, 1, 0);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    ftAnim_8006EBA4(gobj);

    fp->gr_vel = 0;
    fp->x80_self_vel.z = 0;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = 0;

    fp->mv.fx.SpecialN.isBlasterLoop = false;

    blasterGObj = it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                              ftParts_8007500C(fp, FtPart_RThumbNb),
                              foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);
    fp->fv.fx.x222C_blasterGObj = blasterGObj;

    if (blasterGObj != NULL) {
        it_8026BAE8(fp->fv.fx.x222C_blasterGObj, 0.85);
        ftFox_SpecialN_SetCall(gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    __assert("ftfoxspecialn.c", 305, "0");
}

// 0x800E61A8
// https://decomp.me/scratch/TUDhU
void ftFx_SpecialAirN_Enter(
    HSD_GObj* gobj) // Fox & Falco's aerial Blaster Motion State handler
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    HSD_GObj* blasterGObj;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirNStart, 0, NULL, 0, 1,
                              0);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    ftAnim_8006EBA4(gobj);

    fp->mv.fx.SpecialN.isBlasterLoop = false;
    blasterGObj = it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                              ftParts_8007500C(fp, FtPart_RThumbNb),
                              foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);
    fp->fv.fx.x222C_blasterGObj = blasterGObj;

    if (blasterGObj != NULL) {
        it_8026BAE8(fp->fv.fx.x222C_blasterGObj, 0.85);
        ftFox_SpecialN_SetCall(gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    __assert("ftfoxspecialn.c", 333, "0");
}

// 0x800E62A4
// https://decomp.me/scratch/ZOB3l // Fox & Falco's grounded Blaster Start
// Animation callback
void ftFx_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    if ((fp->x220C_ftcmd_var3 == 1U) && (fp->fv.fx.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        it_802AE538(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialNLoop,
                                  (Ft_MF_SkipModel | Ft_MF_KeepGfx), NULL, 0,
                                  1, 0);
        ftFox_SpecialN_SetCall(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFx_SpecialN_CreateBlasterShot;
        it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    }
}

// 0x800E6368
// https://decomp.me/scratch/J7zwX // Fox & Falco's grounded Blaster Loop
// Animation callback
void ftFx_SpecialNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* temp_r28 = gobj->user_data;

    it_802ADDD0(temp_r28->fv.fx.x222C_blasterGObj, 1);
    if (((u32) temp_r28->x220C_ftcmd_var3 == 1U) &&
        (temp_r28->fv.fx.x222C_blasterGObj != NULL))
    {
        temp_r28->x220C_ftcmd_var3 = 0U;
        it_802AE538(temp_r28->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((s32) temp_r28->mv.fx.SpecialN.isBlasterLoop == true) {
            temp_r28->cb.x21EC_callback = ftFx_SpecialN_OnChangeAction;
            Fighter_ChangeMotionState(
                gobj, ftFx_MS_SpecialNLoop,
                (Ft_MF_SkipAttackCount | Ft_MF_SkipModel | Ft_MF_KeepGfx),
                NULL, 0, 1, 0);
            temp_r28->cb.x21BC_callback_Accessory4 =
                ftFx_SpecialN_CreateBlasterShot;
            temp_r28->mv.fx.SpecialN.isBlasterLoop = false;
            it_802ADDD0(temp_r28->fv.fx.x222C_blasterGObj, 1);
        } else {
            HSD_GObj* temp;
            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialNEnd,
                                      (Ft_MF_SkipModel | Ft_MF_KeepGfx), NULL,
                                      0, 1, 0);
            temp = temp_r28->fv.fx.x222C_blasterGObj;
            temp_r28->x2204_ftcmd_var1 = 1;
            it_802ADDD0(temp, 1);
        }
        ftFox_SpecialN_SetCall(gobj);
    }
    {
        Vec3 sp2C;
        ftFoxAttributes* foxAttrs;
        Fighter* fp;
        f64 launchAngle;
        FighterKind ftKind;

        /// @todo Fake assignment.
#ifdef MUST_MATCH
        fp = fp = GET_FIGHTER(gobj);
#else
        fp = GET_FIGHTER(gobj);
#endif

        foxAttrs = getFtSpecialAttrs(fp);

/// @todo Unused assignment.
#ifdef MUST_MATCH
        {
            Fighter* _ = GET_FIGHTER(gobj);
        }
#endif

        if (fp->x2208_ftcmd_var2 != 0) {
            fp->x2208_ftcmd_var2 = 0;
            ftFx_SpecialN_FtGetHoldJoint(gobj, &sp2C);
            sp2C.z = 0;

            if (1 == fp->facing_dir) {
                launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
            } else {
                launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            it_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, gobj,
                        &sp2C, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
            it_802AE1D0(fp->fv.fx.x222C_blasterGObj);
            ftKind = ftLib_800872A4(gobj);
            switch (ftKind) {
            case FTKIND_FOX:
                ft_80088148(fp, foxSFX[-1 == fp->facing_dir], SFX_VOLUME_MAX,
                            SFX_PAN_MID);
                return;

            case FTKIND_FALCO:
                ft_80088148(fp, falcoSFX[-1 == fp->facing_dir], SFX_VOLUME_MAX,
                            SFX_PAN_MID);
                return;
            }
        }
    }
}

static inline void ftFox_SpecialN_RemoveBlasterNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.fx.x222C_blasterGObj != NULL) {
        fp->fv.fx.x222C_blasterGObj = NULL;
    }
    ftFox_SpecialN_SetNULL(gobj);
}

// 0x800E65BC
// https://decomp.me/scratch/aIEIA // Fox & Falco's grounded Blaster End
// Animation callback
void ftFx_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    it_802ADDD0(fp->fv.fx.x222C_blasterGObj, fp->x2204_ftcmd_var1);

    if ((u32) fp->x2204_ftcmd_var1 == 2U) {
        ft_80094818(gobj, 0);
    }

    if (((u32) fp->x220C_ftcmd_var3 == 2U) &&
        (fp->fv.fx.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        it_802AE608(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFox_SpecialN_RemoveBlasterNULL(gobj);
        ft_8008A2BC(gobj);
    }
}

// 0x800E667C
// https://decomp.me/scratch/Os6Ik // Fox & Falco's aerial Blaster Start
// Animation callback
void ftFx_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    if ((fp->x220C_ftcmd_var3 == 1U) && (fp->fv.fx.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        it_802AE538(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirNLoop,
                                  (Ft_MF_SkipModel | Ft_MF_KeepGfx), NULL, 0,
                                  1, 0);
        ftFox_SpecialN_SetCall(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFx_SpecialN_CreateBlasterShot;
        it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    }
}

// 0x800E6740
// https://decomp.me/scratch/FyW7c // Fox & Falco's aerial Blaster Loop
// Animation callback
void ftFx_SpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    if (((u32) fp->x220C_ftcmd_var3 == 1U) &&
        (fp->fv.fx.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        it_802AE538(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((s32) fp->mv.fx.SpecialN.isBlasterLoop == true) {
            fp->cb.x21EC_callback = ftFx_SpecialN_OnChangeAction;
            Fighter_ChangeMotionState(
                gobj, ftFx_MS_SpecialAirNLoop,
                (Ft_MF_SkipAttackCount | Ft_MF_SkipModel | Ft_MF_KeepGfx),
                NULL, 0, 1, 0);
            ftFox_SpecialN_SetCall(gobj);
            fp->cb.x21BC_callback_Accessory4 = ftFx_SpecialN_CreateBlasterShot;
            fp->mv.fx.SpecialN.isBlasterLoop = false;
            it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
        } else {
            HSD_GObj* temp;

            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirNEnd,
                                      (Ft_MF_SkipModel | Ft_MF_KeepGfx), NULL,
                                      0, 1, 0);
            ftFox_SpecialN_SetCall(gobj);

            temp = fp->fv.fx.x222C_blasterGObj;
            fp->x2204_ftcmd_var1 = 1;
            it_802ADDD0(temp, 1);
        }
        ftFox_SpecialN_SetCall(gobj);
    }
    {
        Vec3 sp2C;
        ftFoxAttributes* foxAttrs;
        Fighter* fp;

        /// @todo Fake assignment.
#ifdef MUST_MATCH
        fp = fp = GET_FIGHTER(gobj);
#else
        fp = GET_FIGHTER(gobj);
#endif

        foxAttrs = getFtSpecialAttrs(fp);

/// @todo Unused assignment.
#ifdef MUST_MATCH
        {
            Fighter* _ = GET_FIGHTER(gobj);
        }
#endif

        if ((u32) fp->x2208_ftcmd_var2 != 0U) {
            f64 launchAngle;
            s32 ftKind;

            fp->x2208_ftcmd_var2 = 0U;
            ftFx_SpecialN_FtGetHoldJoint(gobj, &sp2C);
            sp2C.z = 0;

            if (1 == fp->facing_dir) {
                launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            else
            {
                launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            it_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, gobj,
                        &sp2C, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
            it_802AE1D0(fp->fv.fx.x222C_blasterGObj);

            ftKind = ftLib_800872A4(gobj);
            switch (ftKind) {
            case FTKIND_FOX:
                ft_80088148(fp, foxSFX[-1 == fp->facing_dir], SFX_VOLUME_MAX,
                            SFX_PAN_MID);
                return;

            case FTKIND_FALCO:
                ft_80088148(fp, falcoSFX[-1 == fp->facing_dir], SFX_VOLUME_MAX,
                            SFX_PAN_MID);
                return;
            }
        }
    }
}

// 0x800E69BC
// https://decomp.me/scratch/OAWla // Fox & Falco's aerial Blaster End
// Animation callback
void ftFx_SpecialAirNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    it_802ADDD0(fp->fv.fx.x222C_blasterGObj, fp->x2204_ftcmd_var1);
    if ((u32) fp->x2204_ftcmd_var1 == 2U) {
        ft_80094818(gobj, 0);
    }
    if (((u32) fp->x220C_ftcmd_var3 == 2U) &&
        ((u32) fp->fv.fx.x222C_blasterGObj != 0U))
    {
        fp->x220C_ftcmd_var3 = 0U;
        it_802AE608(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFox_SpecialN_RemoveBlasterNULL(gobj);
        if (0 == foxAttrs->x18_FOX_BLASTER_LANDING_LAG) {
            ft_800CC730(gobj);
            return;
        }
        ft_80096900(gobj, 1, 0, true, 1,
                    foxAttrs->x18_FOX_BLASTER_LANDING_LAG);
    }
}

// 0x800E6AB4
// https://decomp.me/scratch/7JCEh // Fox & Falco's grounded Blaster Start IASA
// callback
void ftFx_SpecialNStart_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (((u32) fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->mv.fx.SpecialN.isBlasterLoop = true;
    }
}

// 0x800E6ADC
// https://decomp.me/scratch/7JCEh // Fox & Falco's grounded Blaster Loop IASA
// callback
void ftFx_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (((u32) fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->mv.fx.SpecialN.isBlasterLoop = true;
    }
}

// 0x800E6B04 - Fox & Falco's grounded Blaster End IASA callback
void ftFx_SpecialNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E6B08
// https://decomp.me/scratch/7JCEh // Fox & Falco's aerial Blaster Start IASA
// callback
void ftFx_SpecialAirNStart_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (((u32) fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->mv.fx.SpecialN.isBlasterLoop = true;
    }
}

// 0x800E6B30
// https://decomp.me/scratch/7JCEh // Fox & Falco's aerial Blaster Loop IASA
// callback
void ftFx_SpecialAirNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (((u32) fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->mv.fx.SpecialN.isBlasterLoop = true;
    }
}

// 0x800E6B58 - Fox & Falco's aerial Blaster End IASA callback
void ftFx_SpecialAirNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E6B5C - Fox & Falco's grounded Blaster Start Physics callback
void ftFx_SpecialNStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x800E6B7C - Fox & Falco's grounded Blaster Loop Physics callback
void ftFx_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x800E6B9C - Fox & Falco's grounded Blaster End Physics callback
void ftFx_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x800E6BBC - Fox & Falco's aerial Blaster Start Physics callback
void ftFx_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

// 0x800E6BDC - Fox & Falco's aerial Blaster Loop Physics callback
void ftFx_SpecialAirNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

// 0x800E6BFC - Fox & Falco's aerial Blaster End Physics callback
void ftFx_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

// 0x800E6C1C - Fox & Falco's grounded Blaster Start Collision callback
void ftFx_SpecialNStart_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

// 0x800E6C3C - Fox & Falco's grounded Blaster Loop Collision callback
void ftFx_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

// 0x800E6C1C - Fox & Falco's grounded Blaster End Collision callback
void ftFx_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

// 0x800E6C7C - Fox & Falco's aerial Blaster Start Collision callback
void ftFx_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    ftCo_ZairCatch_Coll(gobj);
}

// 0x800E6C9C - Fox & Falco's aerial Blaster Loop Collision callback
void ftFx_SpecialAirNLoop_Coll(HSD_GObj* gobj)
{
    ftCo_ZairCatch_Coll(gobj);
}

// 0x800E6CBC - Fox & Falco's aerial Blaster End Collision callback
void ftFx_SpecialAirNEnd_Coll(HSD_GObj* gobj)
{
    ftCo_ZairCatch_Coll(gobj);
}

// 0x800E6CDC
// https://decomp.me/scratch/G1jsj // Fox & Falco's Throw Animation callback -
// spawn Blaster
void ftFx_Throw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    s32 ftKind = ftGetKind(fp);

    if ((ftKind == FTKIND_FOX) || (ftKind == FTKIND_FALCO)) {
        if (!ftAnim_IsFramesRemaining(gobj)) {
            fp->fv.fx.x222C_blasterGObj = NULL;
            ftFox_SpecialN_SetNULL(gobj);
            return;
        }
        switch (fp->x2204_ftcmd_var1) {
        case 1:
            if (fp->fv.fx.x222C_blasterGObj == NULL) {
                HSD_GObj* blasterGObj =
                    it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                                ftParts_8007500C(fp, FtPart_RThumbNb),
                                foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);

                fp->fv.fx.x222C_blasterGObj = blasterGObj;
                if (blasterGObj != NULL) {
                    it_8026BAE8(fp->fv.fx.x222C_blasterGObj,
                                (0.85f * (fp->x34_scale.y *
                                          fp->x110_attr.x19C_ModelScaling)));
                    ftFox_SpecialN_SetCall(gobj);
                }
                return;
            } else {
                s32 flag;

                it_802ADDD0(fp->fv.fx.x222C_blasterGObj, fp->x2204_ftcmd_var1);
                switch (fp->x220C_ftcmd_var3) {
                case 1:
                    fp->x220C_ftcmd_var3 = 0;
                    it_802AE538(fp->fv.fx.x222C_blasterGObj);
                    break;
                case 2:
                    fp->x220C_ftcmd_var3 = 0;
                    it_802AE608(fp->fv.fx.x222C_blasterGObj);
                    break;
                }
                if (fp->x2210_ThrowFlags.b0 != 0) {
                    fp->x2210_ThrowFlags.b0 = 0;
                    flag = true;
                } else {
                    flag = false;
                }
                if (flag != false) {
                    Vec3 sp50;
                    Vec3 sp44;

                    ftFx_SpecialN_FtGetHoldJoint(gobj, &sp50);
                    ftFx_SpecialN_ItGetHoldJoint(gobj, &sp44);

                    sp44.z = 0;
                    sp50.z = 0;
                    switch (ftGetAction(fp)) {
                    case ftCo_MS_ThrowB:
                    case ftCo_MS_ThrowHi:
                    case ftCo_MS_ThrowLw:

                        it_8029C6CC(atan2f(sp50.y - sp44.y, sp50.x - sp44.x),
                                    foxAttrs->x14_FOX_BLASTER_VEL, gobj, &sp50,
                                    foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;

                    default:
                        it_8029C6A4(atan2f(sp50.y - sp44.y, sp50.x - sp44.x),
                                    foxAttrs->x14_FOX_BLASTER_VEL, gobj, &sp50,
                                    foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;
                    }
                    it_802AE1D0(fp->fv.fx.x222C_blasterGObj);
                    switch (ftGetAction(fp)) {
                    case ftCo_MS_ThrowHi:
                    case ftCo_MS_ThrowLw: {
                        switch (ftLib_800872A4(gobj)) {
                        case FTKIND_FOX:
                            ft_80088148(fp, 110109, SFX_VOLUME_MAX,
                                        SFX_PAN_MID);
                            return;
                        case FTKIND_FALCO:
                            ft_80088148(fp, 100105, SFX_VOLUME_MAX,
                                        SFX_PAN_MID);
                            return;
                        }
                    default:
                        break;
                    }
                    case ftCo_MS_ThrowB:
                        switch (ftLib_800872A4(gobj)) {
                        case FTKIND_FOX:
                            ft_80088148(fp, foxSFX[1 == fp->facing_dir],
                                        SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;

                        case FTKIND_FALCO:
                            ft_80088148(fp, falcoSFX[1 == fp->facing_dir],
                                        SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
        case 2:
            if (fp->fv.fx.x222C_blasterGObj != NULL) {
                fp->fv.fx.x222C_blasterGObj = NULL;
                ftFox_SpecialN_SetNULL(gobj);
                switch (ftLib_800872A4(gobj)) {
                case FTKIND_FOX:
                    ft_80088148(fp, 110100, SFX_VOLUME_MAX, SFX_PAN_MID);
                    return;
                case FTKIND_FALCO:
                    ft_80088148(fp, 100096, SFX_VOLUME_MAX, SFX_PAN_MID);
                    return;
                }
            }
            break;
        case 0:
            fp->fv.fx.x222C_blasterGObj = NULL;
            ftFox_SpecialN_SetNULL(gobj);
            ft_80094818(gobj, 0);
            break;
        }
    }
}
