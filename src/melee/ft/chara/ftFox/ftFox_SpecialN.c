#include "ftfox.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "it/code_8027CF30.h"
#include "it/item.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>
#include <dolphin/os/os.h>

void ftFox_FtGetHoldJoint(HSD_GObj* gobj, Vec3* pos)
{
    /// @todo Shared @c inline with #ftFox_ItGetHoldJoint.
    Vec3 sp14;

    // Double fp init otherwise this will not match when inlined
    Fighter* fp = fp = GET_FIGHTER(gobj);

    sp14.x = 0.0f;
    sp14.y = 1.2325000762939453f;
    sp14.z = 4.263599872589111f;

    func_8000B1CC(fp->ft_bones[func_8007500C(fp, 0x31)].x0_jobj, &sp14, pos);
}

void ftFox_ItGetHoldJoint(HSD_GObj* gobj, Vec3* pos)
{
    Vec3 sp14;
    Fighter* fp = fp = GET_FIGHTER(gobj);

    sp14.x = 0.0f;
    sp14.y = 1.2325000762939453f;
    sp14.z = 0.013600001111626625f;

    func_8000B1CC(fp->ft_bones[func_8007500C(fp, 0x31)].x0_jobj, &sp14, pos);
}

// 0x800E5D90
// https://decomp.me/scratch/DRgo9 // Fox & Falco's Blaster OnMotionStateChange
// function
void ftFox_SpecialN_OnChangeAction(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_800892A0(gobj);
    func_80089824(gobj);
}

// 0x800E5DC4
// https://decomp.me/scratch/A0n4M // Check if Fox/Falco has a Blaster GOBj
// pointer
bool ftFox_CheckRemoveBlaster(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.fx.x222C_blasterGObj == NULL) {
        return true;
    }
    return false;
}

// 0x800E5DE4 - shoutouts to Olifr� for figuring this one out!
// https://decomp.me/scratch/aatYF // Get msid for Fox/Falco moves that require
// the Blaster item
s32 ftFox_GetBlasterAction(HSD_GObj* gobj)
{
    s32 msid = 9;

    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            s32 currASID = fp->motion_id;
            switch (currASID) {
            case MS_FOX_SPECIALN_START:
            case MS_FOX_SPECIALN_LOOP:
            case MS_FOX_SPECIALN_END:
            case MS_FOX_SPECIALAIRN_START:
            case MS_FOX_SPECIALAIRN_LOOP:
            case MS_FOX_SPECIALAIRN_END:
                msid = currASID - MS_FOX_SPECIALN_START;
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
bool ftFox_CheckBlasterAction(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        s32 msid = fp->motion_id;
        switch (msid) {
        case MS_FOX_SPECIALN_START:
        case MS_FOX_SPECIALN_LOOP:
        case MS_FOX_SPECIALN_END:
        case MS_FOX_SPECIALAIRN_START:
        case MS_FOX_SPECIALAIRN_LOOP:
        case MS_FOX_SPECIALAIRN_END:
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
void ftFox_ClearBlaster(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.fx.x222C_blasterGObj != NULL) {
        fp->fv.fx.x222C_blasterGObj = NULL;
    }
    ftFox_SpecialN_SetNULL(gobj);
}

// 0x800E5EBC
// https://decomp.me/scratch/WglAb // Remove Blaster item
void ftFox_RemoveBlaster(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->fv.fx.x222C_blasterGObj != NULL) {
        func_802AEAB4(fp->fv.fx.x222C_blasterGObj);
        fp->fv.fx.x222C_blasterGObj = NULL;
    }
    if (func_800E5534(gobj) == false) {
        ftFox_SpecialN_SetNULL(gobj);
    }
}

u32 foxSFX[2] = { 0x1AE17, 0x1AE1A };
u32 falcoSFX[2] = { 0x18703, 0x18706 };

// 0x800E5F28
// https://decomp.me/scratch/iPgDc // Create Blaster Shot Item
void ftFox_CreateBlasterShot(HSD_GObj* gobj)
{
    /** @todo Shared @c inline with #ftFox_SpecialNLoop_Anim and
     * #ftFox_SpecialAirNLoop_Anim.
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
        ftFox_FtGetHoldJoint(gobj, &sp2C);
        sp2C.z = 0.0f;

        if (1.0f == fp->facing_dir)
            launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
        else
            launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;

        func_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, gobj, &sp2C,
                      foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);

        func_802AE1D0(fp->fv.fx.x222C_blasterGObj);
        ftKind = func_800872A4(gobj);

        switch (ftKind) {
        case FTKIND_FOX:
            func_80088148(fp, foxSFX[-1.0f == fp->facing_dir], SFX_VOLUME_MAX,
                          SFX_PAN_MID);
            return;

        case FTKIND_FALCO:
            func_80088148(fp, falcoSFX[-1.0f == fp->facing_dir],
                          SFX_VOLUME_MAX, SFX_PAN_MID);
            return;
        }
    }
}

inline void ftFox_SpecialN_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = func_800E5588;
    fp->cb.x21E4_callback_OnDeath2 = func_800E5588;
}

// 0x800E608C
// https://decomp.me/scratch/B3aTL // Fox & Falco's grounded Blaster Action
// State handler
void ftFox_SpecialN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    HSD_GObj* blasterGObj;

    func_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, MS_FOX_SPECIALN_START, 0, NULL, 0.0f, 1.0f,
                              0.0f);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    func_8006EBA4(gobj);

    fp->xEC_ground_vel = 0.0f;
    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;

    fp->mv.fx.SpecialN.isBlasterLoop = false;

    blasterGObj = func_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                                func_8007500C(fp, 0x31),
                                foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);
    fp->fv.fx.x222C_blasterGObj = blasterGObj;

    if (blasterGObj != NULL) {
        func_8026BAE8(fp->fv.fx.x222C_blasterGObj, 0.8500000238418579f);
        ftFox_SpecialN_SetCall(gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    __assert("ftfoxspecialn.c", 305, "0");
}

// 0x800E61A8
// https://decomp.me/scratch/TUDhU
void ftFox_SpecialAirN_StartMotion(
    HSD_GObj* gobj) // Fox & Falco's aerial Blaster Motion State handler
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    HSD_GObj* blasterGObj;

    Fighter_ChangeMotionState(gobj, MS_FOX_SPECIALAIRN_START, 0, NULL, 0.0f,
                              1.0f, 0.0f);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    func_8006EBA4(gobj);

    fp->mv.fx.SpecialN.isBlasterLoop = false;
    blasterGObj = func_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                                func_8007500C(fp, 0x31),
                                foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);
    fp->fv.fx.x222C_blasterGObj = blasterGObj;

    if (blasterGObj != NULL) {
        func_8026BAE8(fp->fv.fx.x222C_blasterGObj, 0.8500000238418579f);
        ftFox_SpecialN_SetCall(gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    __assert("ftfoxspecialn.c", 333, "0");
}

// 0x800E62A4
// https://decomp.me/scratch/ZOB3l // Fox & Falco's grounded Blaster Start
// Animation callback
void ftFox_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    func_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    if ((fp->x220C_ftcmd_var3 == 1U) && (fp->fv.fx.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE538(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(
            gobj, MS_FOX_SPECIALN_LOOP,
            (FtStateChange_SkipUpdateModel | FtStateChange_PreserveGfx), NULL,
            0.0f, 1.0f, 0.0f);
        ftFox_SpecialN_SetCall(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFox_CreateBlasterShot;
        func_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    }
}

// 0x800E6368
// https://decomp.me/scratch/J7zwX // Fox & Falco's grounded Blaster Loop
// Animation callback
void ftFox_SpecialNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* temp_r28 = gobj->user_data;

    func_802ADDD0(temp_r28->fv.fx.x222C_blasterGObj, 1);
    if (((u32) temp_r28->x220C_ftcmd_var3 == 1U) &&
        (temp_r28->fv.fx.x222C_blasterGObj != NULL))
    {
        temp_r28->x220C_ftcmd_var3 = 0U;
        func_802AE538(temp_r28->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((s32) temp_r28->mv.fx.SpecialN.isBlasterLoop == true) {
            temp_r28->cb.x21EC_callback = ftFox_SpecialN_OnChangeAction;
            Fighter_ChangeMotionState(gobj, MS_FOX_SPECIALN_LOOP,
                                      (FtStateChange_SkipUpdateAttackCount |
                                       FtStateChange_SkipUpdateModel |
                                       FtStateChange_PreserveGfx),
                                      NULL, 0.0f, 1.0f, 0.0f);
            temp_r28->cb.x21BC_callback_Accessory4 = ftFox_CreateBlasterShot;
            temp_r28->mv.fx.SpecialN.isBlasterLoop = false;
            func_802ADDD0(temp_r28->fv.fx.x222C_blasterGObj, 1);
        } else {
            HSD_GObj* temp;
            Fighter_ChangeMotionState(
                gobj, MS_FOX_SPECIALN_END,
                (FtStateChange_SkipUpdateModel | FtStateChange_PreserveGfx),
                NULL, 0.0f, 1.0f, 0.0f);
            temp = temp_r28->fv.fx.x222C_blasterGObj;
            temp_r28->x2204_ftcmd_var1 = 1;
            func_802ADDD0(temp, 1);
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
            ftFox_FtGetHoldJoint(gobj, &sp2C);
            sp2C.z = 0.0f;

            if (1.0f == fp->facing_dir) {
                launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
            } else {
                launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            func_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, gobj,
                          &sp2C, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
            func_802AE1D0(fp->fv.fx.x222C_blasterGObj);
            ftKind = func_800872A4(gobj);
            switch (ftKind) {
            case FTKIND_FOX:
                func_80088148(fp, foxSFX[-1.0f == fp->facing_dir],
                              SFX_VOLUME_MAX, SFX_PAN_MID);
                return;

            case FTKIND_FALCO:
                func_80088148(fp, falcoSFX[-1.0f == fp->facing_dir],
                              SFX_VOLUME_MAX, SFX_PAN_MID);
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
void ftFox_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    func_802ADDD0(fp->fv.fx.x222C_blasterGObj, fp->x2204_ftcmd_var1);

    if ((u32) fp->x2204_ftcmd_var1 == 2U)
        func_80094818(gobj, 0);

    if (((u32) fp->x220C_ftcmd_var3 == 2U) &&
        (fp->fv.fx.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE608(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFox_SpecialN_RemoveBlasterNULL(gobj);
        func_8008A2BC(gobj);
    }
}

// 0x800E667C
// https://decomp.me/scratch/Os6Ik // Fox & Falco's aerial Blaster Start
// Animation callback
void ftFox_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    func_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    if ((fp->x220C_ftcmd_var3 == 1U) && (fp->fv.fx.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE538(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(
            gobj, MS_FOX_SPECIALAIRN_LOOP,
            (FtStateChange_SkipUpdateModel | FtStateChange_PreserveGfx), NULL,
            0.0f, 1.0f, 0.0f);
        ftFox_SpecialN_SetCall(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFox_CreateBlasterShot;
        func_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    }
}

// 0x800E6740
// https://decomp.me/scratch/FyW7c // Fox & Falco's aerial Blaster Loop
// Animation callback
void ftFox_SpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    func_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    if (((u32) fp->x220C_ftcmd_var3 == 1U) &&
        (fp->fv.fx.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE538(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((s32) fp->mv.fx.SpecialN.isBlasterLoop == true) {
            fp->cb.x21EC_callback = ftFox_SpecialN_OnChangeAction;
            Fighter_ChangeMotionState(gobj, MS_FOX_SPECIALAIRN_LOOP,
                                      (FtStateChange_SkipUpdateAttackCount |
                                       FtStateChange_SkipUpdateModel |
                                       FtStateChange_PreserveGfx),
                                      NULL, 0.0f, 1.0f, 0.0f);
            ftFox_SpecialN_SetCall(gobj);
            fp->cb.x21BC_callback_Accessory4 = ftFox_CreateBlasterShot;
            fp->mv.fx.SpecialN.isBlasterLoop = false;
            func_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
        } else {
            HSD_GObj* temp;

            Fighter_ChangeMotionState(
                gobj, MS_FOX_SPECIALAIRN_END,
                (FtStateChange_SkipUpdateModel | FtStateChange_PreserveGfx),
                NULL, 0.0f, 1.0f, 0.0f);
            ftFox_SpecialN_SetCall(gobj);

            temp = fp->fv.fx.x222C_blasterGObj;
            fp->x2204_ftcmd_var1 = 1;
            func_802ADDD0(temp, 1);
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
            ftFox_FtGetHoldJoint(gobj, &sp2C);
            sp2C.z = 0.0f;

            if (1.0f == fp->facing_dir) {
                launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            else
            {
                launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            func_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, gobj,
                          &sp2C, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
            func_802AE1D0(fp->fv.fx.x222C_blasterGObj);

            ftKind = func_800872A4(gobj);
            switch (ftKind) {
            case FTKIND_FOX:
                func_80088148(fp, foxSFX[-1.0f == fp->facing_dir],
                              SFX_VOLUME_MAX, SFX_PAN_MID);
                return;

            case FTKIND_FALCO:
                func_80088148(fp, falcoSFX[-1.0f == fp->facing_dir],
                              SFX_VOLUME_MAX, SFX_PAN_MID);
                return;
            }
        }
    }
}

// 0x800E69BC
// https://decomp.me/scratch/OAWla // Fox & Falco's aerial Blaster End
// Animation callback
void ftFox_SpecialAirNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    func_802ADDD0(fp->fv.fx.x222C_blasterGObj, fp->x2204_ftcmd_var1);
    if ((u32) fp->x2204_ftcmd_var1 == 2U) {
        func_80094818(gobj, 0);
    }
    if (((u32) fp->x220C_ftcmd_var3 == 2U) &&
        ((u32) fp->fv.fx.x222C_blasterGObj != 0U))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE608(fp->fv.fx.x222C_blasterGObj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFox_SpecialN_RemoveBlasterNULL(gobj);
        if (0.0f == foxAttrs->x18_FOX_BLASTER_LANDING_LAG) {
            func_800CC730(gobj);
            return;
        }
        func_80096900(gobj, 1, 0, true, 1.0f,
                      foxAttrs->x18_FOX_BLASTER_LANDING_LAG);
    }
}

// 0x800E6AB4
// https://decomp.me/scratch/7JCEh // Fox & Falco's grounded Blaster Start IASA
// callback
void ftFox_SpecialNStart_IASA(HSD_GObj* gobj)
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
void ftFox_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (((u32) fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->mv.fx.SpecialN.isBlasterLoop = true;
    }
}

// 0x800E6B04 - Fox & Falco's grounded Blaster End IASA callback
void ftFox_SpecialNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E6B08
// https://decomp.me/scratch/7JCEh // Fox & Falco's aerial Blaster Start IASA
// callback
void ftFox_SpecialAirNStart_IASA(HSD_GObj* gobj)
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
void ftFox_SpecialAirNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (((u32) fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->mv.fx.SpecialN.isBlasterLoop = true;
    }
}

// 0x800E6B58 - Fox & Falco's aerial Blaster End IASA callback
void ftFox_SpecialAirNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E6B5C - Fox & Falco's grounded Blaster Start Physics callback
void ftFox_SpecialNStart_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

// 0x800E6B7C - Fox & Falco's grounded Blaster Loop Physics callback
void ftFox_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

// 0x800E6B9C - Fox & Falco's grounded Blaster End Physics callback
void ftFox_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

// 0x800E6BBC - Fox & Falco's aerial Blaster Start Physics callback
void ftFox_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

// 0x800E6BDC - Fox & Falco's aerial Blaster Loop Physics callback
void ftFox_SpecialAirNLoop_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

// 0x800E6BFC - Fox & Falco's aerial Blaster End Physics callback
void ftFox_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

// 0x800E6C1C - Fox & Falco's grounded Blaster Start Collision callback
void ftFox_SpecialNStart_Coll(HSD_GObj* gobj)
{
    func_80083F88(gobj);
}

// 0x800E6C3C - Fox & Falco's grounded Blaster Loop Collision callback
void ftFox_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    func_80083F88(gobj);
}

// 0x800E6C1C - Fox & Falco's grounded Blaster End Collision callback
void ftFox_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    func_80083F88(gobj);
}

// 0x800E6C7C - Fox & Falco's aerial Blaster Start Collision callback
void ftFox_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    func_80082B78(gobj);
}

// 0x800E6C9C - Fox & Falco's aerial Blaster Loop Collision callback
void ftFox_SpecialAirNLoop_Coll(HSD_GObj* gobj)
{
    func_80082B78(gobj);
}

// 0x800E6CBC - Fox & Falco's aerial Blaster End Collision callback
void ftFox_SpecialAirNEnd_Coll(HSD_GObj* gobj)
{
    func_80082B78(gobj);
}

// 0x800E6CDC
// https://decomp.me/scratch/G1jsj // Fox & Falco's Throw Animation callback -
// spawn Blaster
void ftFox_Throw_Anim(HSD_GObj* gobj)
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
                    func_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                                  func_8007500C(fp, 0x31),
                                  foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);

                fp->fv.fx.x222C_blasterGObj = blasterGObj;
                if (blasterGObj != NULL) {
                    func_8026BAE8(
                        fp->fv.fx.x222C_blasterGObj,
                        (0.8500000238418579f *
                         (fp->x34_scale.y * fp->x110_attr.x19C_ModelScaling)));
                    ftFox_SpecialN_SetCall(gobj);
                }
                return;
            } else {
                s32 flag;

                func_802ADDD0(fp->fv.fx.x222C_blasterGObj,
                              fp->x2204_ftcmd_var1);
                switch (fp->x220C_ftcmd_var3) {
                case 1:
                    fp->x220C_ftcmd_var3 = 0;
                    func_802AE538(fp->fv.fx.x222C_blasterGObj);
                    break;
                case 2:
                    fp->x220C_ftcmd_var3 = 0;
                    func_802AE608(fp->fv.fx.x222C_blasterGObj);
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

                    ftFox_FtGetHoldJoint(gobj, &sp50);
                    ftFox_ItGetHoldJoint(gobj, &sp44);

                    sp44.z = 0.0f;
                    sp50.z = 0.0f;
                    switch (ftGetAction(fp)) {
                    case ftCo_MS_ThrowB:
                    case ftCo_MS_ThrowHi:
                    case ftCo_MS_ThrowLw:

                        func_8029C6CC(atan2f(sp50.y - sp44.y, sp50.x - sp44.x),
                                      foxAttrs->x14_FOX_BLASTER_VEL, gobj,
                                      &sp50,
                                      foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;

                    default:
                        func_8029C6A4(atan2f(sp50.y - sp44.y, sp50.x - sp44.x),
                                      foxAttrs->x14_FOX_BLASTER_VEL, gobj,
                                      &sp50,
                                      foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;
                    }
                    func_802AE1D0(fp->fv.fx.x222C_blasterGObj);
                    switch (ftGetAction(fp)) {
                    case ftCo_MS_ThrowHi:
                    case ftCo_MS_ThrowLw: {
                        switch (func_800872A4(gobj)) {
                        case FTKIND_FOX:
                            func_80088148(fp, 0x1AE1DU, SFX_VOLUME_MAX,
                                          SFX_PAN_MID);
                            return;
                        case FTKIND_FALCO:
                            func_80088148(fp, 0x18709U, SFX_VOLUME_MAX,
                                          SFX_PAN_MID);
                            return;
                        }
                    default:
                        break;
                    }
                    case ftCo_MS_ThrowB:
                        switch (func_800872A4(gobj)) {
                        case FTKIND_FOX:
                            func_80088148(fp, foxSFX[1.0f == fp->facing_dir],
                                          SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;

                        case FTKIND_FALCO:
                            func_80088148(fp, falcoSFX[1.0f == fp->facing_dir],
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
                switch (func_800872A4(gobj)) {
                case FTKIND_FOX:
                    func_80088148(fp, 0x1AE14U, SFX_VOLUME_MAX, SFX_PAN_MID);
                    return;
                case FTKIND_FALCO:
                    func_80088148(fp, 0x18700U, SFX_VOLUME_MAX, SFX_PAN_MID);
                    return;
                }
            }
            break;
        case 0:
            fp->fv.fx.x222C_blasterGObj = NULL;
            ftFox_SpecialN_SetNULL(gobj);
            func_80094818(gobj, 0);
            break;
        }
    }
}
