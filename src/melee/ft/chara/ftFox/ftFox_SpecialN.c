#include <melee/ft/chara/ftFox/ftfox.h>

// 0x800E5CB0
// https://decomp.me/scratch/aumQK // Get Fox/Falco's Item Hold Bone Position for Blaster GFX - used in Fox's fp code
void ftFox_FtGetHoldJoint(HSD_GObj* fighter_gobj, Vec3* pos)
{
    Vec3 sp14;
    Fighter* fp = fp = getFighter(fighter_gobj); // Double fp init otherwise this will not match when inlined O_O

    sp14.x = 0.0f;
    sp14.y = 1.2325000762939453f;
    sp14.z = 4.263599872589111f;
    func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 0x31)].x0_jobj, &sp14, pos);
}

// 0x800E5D20
// https://decomp.me/scratch/x2JfZ // Get Fox/Falco's Item Hold Bone Position for Blaster GFX again? - used in Blaster's item code
void ftFox_ItGetHoldJoint(HSD_GObj* fighter_gobj, Vec3* pos)
{
    Vec3 sp14;
    Fighter* fp = fp = getFighter(fighter_gobj);

    sp14.x = 0.0f;
    sp14.y = 1.2325000762939453f;
    sp14.z = 0.013600001111626625f;
    func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 0x31)].x0_jobj, &sp14, pos);
}

// 0x800E5D90
// https://decomp.me/scratch/DRgo9 // Fox & Falco's Blaster OnActionStateChange function
void ftFox_SpecialN_OnChangeAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_800892A0(fighter_gobj);
    func_80089824(fighter_gobj);
}

// 0x800E5DC4
// https://decomp.me/scratch/A0n4M // Check if Fox/Falco has a Blaster GOBj pointer
BOOL ftFox_CheckRemoveBlaster(HSD_GObj* fighter_gobj)
{
    if (getFighter(fighter_gobj)->sa.fox.x222C_blasterGObj == NULL)
    {
        return TRUE;
    }
    return FALSE;
}

// 0x800E5DE4 - shoutouts to Olifr� for figuring this one out!
// https://decomp.me/scratch/aatYF // Get ASID for Fox/Falco moves that require the Blaster item
s32 ftFox_GetBlasterAction(HSD_GObj* fighter_gobj)
{
    s32 ASID = 9;

    if (fighter_gobj != NULL)
    {
        Fighter* fp = fighter_gobj->user_data;
        if (fp != NULL)
        {
            s32 currASID = fp->x10_action_state_index;
            switch (currASID)
            {
            case AS_FOX_SPECIALN_START:
            case AS_FOX_SPECIALN_LOOP:
            case AS_FOX_SPECIALN_END:
            case AS_FOX_SPECIALAIRN_START:
            case AS_FOX_SPECIALAIRN_LOOP:
            case AS_FOX_SPECIALAIRN_END:
                ASID = currASID - AS_FOX_SPECIALN_START;
                break;

            case ASID_THROWB:
            case ASID_THROWHI:
            case ASID_THROWLW:
                ASID = currASID - ASID_CATCHDASH;
            }
        }
    }
    return ASID;
}

// 0x800E5E38
// https://decomp.me/scratch/f6oIX // Check if Fox/Falco is performing a move that requires the Blaster item
BOOL ftFox_CheckBlasterAction(HSD_GObj* fighter_gobj)
{
    if (fighter_gobj != NULL)
    {
        Fighter* fp = fighter_gobj->user_data;
        s32 ASID = fp->x10_action_state_index;
        switch (ASID)
        {
            case AS_FOX_SPECIALN_START:
            case AS_FOX_SPECIALN_LOOP:
            case AS_FOX_SPECIALN_END:
            case AS_FOX_SPECIALAIRN_START:
            case AS_FOX_SPECIALAIRN_LOOP:
            case AS_FOX_SPECIALAIRN_END:
            case ASID_THROWB:
            case ASID_THROWHI:
            case ASID_THROWLW:

            if (fp->x2071_b6 != FALSE)
            {
                return TRUE;
            }
            return FALSE;
        }
    }
    return TRUE;
}

inline void ftFox_SpecialN_SetNULL(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
}

// 0x800E5E90
// https://decomp.me/scratch/4v8j4 // Clear Blaster GObj pointer and callbacks
void ftFox_ClearBlaster(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.fox.x222C_blasterGObj != NULL)
    {
        fp->sa.fox.x222C_blasterGObj = NULL;
    }
    ftFox_SpecialN_SetNULL(fighter_gobj);
}

extern void func_802AEAB4(HSD_GObj*);

// 0x800E5EBC
// https://decomp.me/scratch/WglAb // Remove Blaster item
void ftFox_RemoveBlaster(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* blasterGObj;

    if (fp->sa.fox.x222C_blasterGObj != NULL)
    {
        func_802AEAB4(fp->sa.fox.x222C_blasterGObj);
        fp->sa.fox.x222C_blasterGObj = NULL;
    }
    if (func_800E5534(fighter_gobj) == FALSE)
    {
        ftFox_SpecialN_SetNULL(fighter_gobj);
    }
}

extern void func_8029C6A4(f32, f32, HSD_GObj*, Vec3*, s32);
extern void func_802AE1D0(HSD_GObj*);

u32 foxSFX[2] = { 0x1AE17, 0x1AE1A };
u32 falcoSFX[2] = { 0x18703, 0x18706 };

// 0x800E5F28
// https://decomp.me/scratch/iPgDc // Create Blaster Shot Item
void ftFox_CreateBlasterShot(HSD_GObj* fighter_gobj)
{
    Vec3 sp2C;
    s32 unused;
    ftFoxAttributes* foxAttrs;
    Fighter* fp;
    f64 launchAngle;
    s32 ftKind;

    fp = fp = getFighter(fighter_gobj);
    foxAttrs = getFtSpecialAttrs(fp);
    if ((u32)fp->x2208_ftcmd_var2 != 0U)
    {
        fp->x2208_ftcmd_var2 = 0U;
        ftFox_FtGetHoldJoint(fighter_gobj, &sp2C);
        sp2C.z = 0.0f;

        if (1.0f == fp->x2C_facing_direction)
        {
            launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
        }
        else
        {
            launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;
        }

        func_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, fighter_gobj, &sp2C, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
        func_802AE1D0(fp->sa.fox.x222C_blasterGObj);
        ftKind = func_800872A4(fighter_gobj);
        switch (ftKind)
        {
        case FTKIND_FOX:
            func_80088148(fp, foxSFX[-1.0f == fp->x2C_facing_direction], SFX_VOLUME_MAX, SFX_PAN_MID);
            return;

        case FTKIND_FALCO:
            func_80088148(fp, falcoSFX[-1.0f == fp->x2C_facing_direction], SFX_VOLUME_MAX, SFX_PAN_MID);
            return;
        }
    }
}

extern void func_8026BAE8(HSD_GObj*, f32);
extern HSD_GObj* func_802AE8A8(f32, HSD_GObj*, Vec3*, s32, s32);
extern void func_800E5588(HSD_GObj*);

inline void ftFox_SpecialN_SetCall(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    fp->cb.x21DC_callback_OnTakeDamage = func_800E5588;
    fp->cb.x21E4_callback_OnDeath2 = func_800E5588;
}

// 0x800E608C
// https://decomp.me/scratch/B3aTL // Fox & Falco's grounded Blaster Action State handler
void ftFox_SpecialN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    HSD_GObj* blasterGObj;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALN_START, 0, NULL, 0.0f, 1.0f, 0.0f);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    func_8006EBA4(fighter_gobj);

    fp->xEC_ground_vel = 0.0f;
    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;

    fp->foxVars[0].SpecialN.isBlasterLoop = FALSE;

    blasterGObj = func_802AE8A8(fp->x2C_facing_direction, fighter_gobj, &fp->xB0_pos, func_8007500C(fp, 0x31), foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);
    fp->sa.fox.x222C_blasterGObj = blasterGObj;

    if (blasterGObj != NULL)
    {
        func_8026BAE8(fp->sa.fox.x222C_blasterGObj, 0.8500000238418579f);
        ftFox_SpecialN_SetCall(fighter_gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    __assert("ftfoxspecialn.c", 305, "0");
}

// 0x800E61A8
// https://decomp.me/scratch/TUDhU
void ftFox_SpecialAirN_StartAction(HSD_GObj* fighter_gobj) // Fox & Falco's aerial Blaster Action State handler
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    HSD_GObj* blasterGObj;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRN_START, 0, NULL, 0.0f, 1.0f, 0.0f);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    func_8006EBA4(fighter_gobj);

    fp->foxVars[0].SpecialN.isBlasterLoop = FALSE;
    blasterGObj = func_802AE8A8(fp->x2C_facing_direction, fighter_gobj, &fp->xB0_pos, func_8007500C(fp, 0x31), foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);
    fp->sa.fox.x222C_blasterGObj = blasterGObj;

    if (blasterGObj != NULL)
    {
        func_8026BAE8(fp->sa.fox.x222C_blasterGObj, 0.8500000238418579f);
        ftFox_SpecialN_SetCall(fighter_gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    __assert("ftfoxspecialn.c", 333, "0");
}

extern void func_802ADDD0(HSD_GObj*, s32);
extern void func_802AE538(HSD_GObj*);

// 0x800E62A4
// https://decomp.me/scratch/ZOB3l // Fox & Falco's grounded Blaster Start Animation callback
void ftFox_SpecialNStart_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* blasterGObj;

    func_802ADDD0(fp->sa.fox.x222C_blasterGObj, 1);
    if ((fp->x220C_ftcmd_var3 == 1U) && (fp->sa.fox.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE538(fp->sa.fox.x222C_blasterGObj);
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALN_LOOP, (FIGHTER_MODEL_NOUPDATE | FIGHTER_GFX_PRESERVE), NULL, 0.0f, 1.0f, 0.0f);
        ftFox_SpecialN_SetCall(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFox_CreateBlasterShot;
        func_802ADDD0(fp->sa.fox.x222C_blasterGObj, 1);
    }
}

// 0x800E6368
// https://decomp.me/scratch/J7zwX // Fox & Falco's grounded Blaster Loop Animation callback
void ftFox_SpecialNLoop_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* temp_r28 = fighter_gobj->user_data;

    func_802ADDD0(temp_r28->sa.fox.x222C_blasterGObj, 1);
    if (((u32)temp_r28->x220C_ftcmd_var3 == 1U) && (temp_r28->sa.fox.x222C_blasterGObj != NULL))
    {
        temp_r28->x220C_ftcmd_var3 = 0U;
        func_802AE538(temp_r28->sa.fox.x222C_blasterGObj);
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if ((s32)temp_r28->foxVars[0].SpecialN.isBlasterLoop == TRUE)
        {
            temp_r28->cb.x21EC_callback = ftFox_SpecialN_OnChangeAction;
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALN_LOOP, (FIGHTER_ATTACKCOUNT_NOUPDATE | FIGHTER_MODEL_NOUPDATE | FIGHTER_GFX_PRESERVE), NULL, 0.0f, 1.0f, 0.0f);
            temp_r28->cb.x21BC_callback_Accessory4 = ftFox_CreateBlasterShot;
            temp_r28->foxVars[0].SpecialN.isBlasterLoop = FALSE;
            func_802ADDD0(temp_r28->sa.fox.x222C_blasterGObj, 1);
        }
        else
        {
            HSD_GObj* temp;
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALN_END, (FIGHTER_MODEL_NOUPDATE | FIGHTER_GFX_PRESERVE), NULL, 0.0f, 1.0f, 0.0f);
            temp = temp_r28->sa.fox.x222C_blasterGObj;
            temp_r28->x2204_ftcmd_var1 = 1;
            func_802ADDD0(temp, 1);
        }
        ftFox_SpecialN_SetCall(fighter_gobj);
    }
    {
        Vec3 sp2C;
        Fighter* unused;
        ftFoxAttributes* foxAttrs;
        Fighter* fp;
        f64 launchAngle;
        s32 ftKind;

        fp = fp = getFighter(fighter_gobj);
        foxAttrs = getFtSpecialAttrs(fp);
        unused = getFighter(fighter_gobj);

        if ((u32)fp->x2208_ftcmd_var2 != 0U)
        {
            fp->x2208_ftcmd_var2 = 0U;
            ftFox_FtGetHoldJoint(fighter_gobj, &sp2C);
            sp2C.z = 0.0f;

            if (1.0f == fp->x2C_facing_direction)
            {
                launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
            }
            else
            {
                launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            func_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, fighter_gobj, &sp2C, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
            func_802AE1D0(fp->sa.fox.x222C_blasterGObj);
            ftKind = func_800872A4(fighter_gobj);
            switch (ftKind)
            {
            case FTKIND_FOX:
                func_80088148(fp, foxSFX[-1.0f == fp->x2C_facing_direction], SFX_VOLUME_MAX, SFX_PAN_MID);
                return;

            case FTKIND_FALCO:
                func_80088148(fp, falcoSFX[-1.0f == fp->x2C_facing_direction], SFX_VOLUME_MAX, SFX_PAN_MID);
                return;
            }
        }
    }
}

extern void func_80094818(HSD_GObj*, s32);
extern void func_802AE608(HSD_GObj*);

inline void ftFox_SpecialN_RemoveBlasterNULL(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.fox.x222C_blasterGObj != NULL)
    {
        fp->sa.fox.x222C_blasterGObj = NULL;
    }
    ftFox_SpecialN_SetNULL(fighter_gobj);
}

// 0x800E65BC
// https://decomp.me/scratch/aIEIA // Fox & Falco's grounded Blaster End Animation callback
void ftFox_SpecialNEnd_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* blasterGObj;

    func_802ADDD0(fp->sa.fox.x222C_blasterGObj, fp->x2204_ftcmd_var1);
    if ((u32)fp->x2204_ftcmd_var1 == 2U)
    {
        func_80094818(fighter_gobj, 0);
    }
    if (((u32)fp->x220C_ftcmd_var3 == 2U) && (fp->sa.fox.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE608(fp->sa.fox.x222C_blasterGObj);
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftFox_SpecialN_RemoveBlasterNULL(fighter_gobj);
        func_8008A2BC(fighter_gobj);
    }
}

// 0x800E667C
// https://decomp.me/scratch/Os6Ik // Fox & Falco's aerial Blaster Start Animation callback
void ftFox_SpecialAirNStart_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* blasterGObj;

    func_802ADDD0(fp->sa.fox.x222C_blasterGObj, 1);
    if ((fp->x220C_ftcmd_var3 == 1U) && (fp->sa.fox.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE538(fp->sa.fox.x222C_blasterGObj);
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRN_LOOP, (FIGHTER_MODEL_NOUPDATE | FIGHTER_GFX_PRESERVE), NULL, 0.0f, 1.0f, 0.0f);
        ftFox_SpecialN_SetCall(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFox_CreateBlasterShot;
        func_802ADDD0(fp->sa.fox.x222C_blasterGObj, 1);
    }
}

// 0x800E6740
// https://decomp.me/scratch/FyW7c // Fox & Falco's aerial Blaster Loop Animation callback
void ftFox_SpecialAirNLoop_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_802ADDD0(fp->sa.fox.x222C_blasterGObj, 1);
    if (((u32)fp->x220C_ftcmd_var3 == 1U) && (fp->sa.fox.x222C_blasterGObj != NULL))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE538(fp->sa.fox.x222C_blasterGObj);
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if ((s32)fp->foxVars[0].SpecialN.isBlasterLoop == TRUE)
        {
            fp->cb.x21EC_callback = ftFox_SpecialN_OnChangeAction;
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRN_LOOP, (FIGHTER_ATTACKCOUNT_NOUPDATE | FIGHTER_MODEL_NOUPDATE | FIGHTER_GFX_PRESERVE), NULL, 0.0f, 1.0f, 0.0f);
            ftFox_SpecialN_SetCall(fighter_gobj);
            fp->cb.x21BC_callback_Accessory4 = ftFox_CreateBlasterShot;
            fp->foxVars[0].SpecialN.isBlasterLoop = FALSE;
            func_802ADDD0(fp->sa.fox.x222C_blasterGObj, 1);
        }
        else
        {
            HSD_GObj* temp;

            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRN_END, (FIGHTER_MODEL_NOUPDATE | FIGHTER_GFX_PRESERVE), NULL, 0.0f, 1.0f, 0.0f);
            ftFox_SpecialN_SetCall(fighter_gobj);

            temp = fp->sa.fox.x222C_blasterGObj;
            fp->x2204_ftcmd_var1 = 1;
            func_802ADDD0(temp, 1);
        }
        ftFox_SpecialN_SetCall(fighter_gobj);
    }
    {
        Vec3 sp2C;
        Fighter* unused;
        ftFoxAttributes* foxAttrs;
        Fighter* fp;

        fp = fp = getFighter(fighter_gobj);
        foxAttrs = getFtSpecialAttrs(fp);
        unused = getFighter(fighter_gobj);

        if ((u32)fp->x2208_ftcmd_var2 != 0U)
        {
            f64 launchAngle;
            s32 ftKind;

            fp->x2208_ftcmd_var2 = 0U;
            ftFox_FtGetHoldJoint(fighter_gobj, &sp2C);
            sp2C.z = 0.0f;

            if (1.0f == fp->x2C_facing_direction)
            {
                launchAngle = foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            else
            {
                launchAngle = M_PI - foxAttrs->x10_FOX_BLASTER_ANGLE;
            }

            func_8029C6A4(launchAngle, foxAttrs->x14_FOX_BLASTER_VEL, fighter_gobj, &sp2C, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
            func_802AE1D0(fp->sa.fox.x222C_blasterGObj);

            ftKind = func_800872A4(fighter_gobj);
            switch (ftKind)
            {
            case FTKIND_FOX:
                func_80088148(fp, foxSFX[-1.0f == fp->x2C_facing_direction], SFX_VOLUME_MAX, SFX_PAN_MID);
                return;

            case FTKIND_FALCO:
                func_80088148(fp, falcoSFX[-1.0f == fp->x2C_facing_direction], SFX_VOLUME_MAX, SFX_PAN_MID);
                return;
            }
        }
    }
}

// 0x800E69BC
// https://decomp.me/scratch/OAWla // Fox & Falco's aerial Blaster End Animation callback
void ftFox_SpecialAirNEnd_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    func_802ADDD0(fp->sa.fox.x222C_blasterGObj, fp->x2204_ftcmd_var1);
    if ((u32)fp->x2204_ftcmd_var1 == 2U)
    {
        func_80094818(fighter_gobj, 0);
    }
    if (((u32)fp->x220C_ftcmd_var3 == 2U) && ((u32)fp->sa.fox.x222C_blasterGObj != 0U))
    {
        fp->x220C_ftcmd_var3 = 0U;
        func_802AE608(fp->sa.fox.x222C_blasterGObj);
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftFox_SpecialN_RemoveBlasterNULL(fighter_gobj);
        if (0.0f == foxAttrs->x18_FOX_BLASTER_LANDING_LAG)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 0, IS_INTERRUPTIBLE, 1.0f, foxAttrs->x18_FOX_BLASTER_LANDING_LAG);
    }
}

// 0x800E6AB4
// https://decomp.me/scratch/7JCEh // Fox & Falco's grounded Blaster Start IASA callback
void ftFox_SpecialNStart_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (((u32)fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->foxVars[0].SpecialN.isBlasterLoop = TRUE;
    }
}

// 0x800E6ADC
// https://decomp.me/scratch/7JCEh // Fox & Falco's grounded Blaster Loop IASA callback
void ftFox_SpecialNLoop_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (((u32)fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->foxVars[0].SpecialN.isBlasterLoop = TRUE;
    }
}

// 0x800E6B04 - Fox & Falco's grounded Blaster End IASA callback
void ftFox_SpecialNEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E6B08
// https://decomp.me/scratch/7JCEh // Fox & Falco's aerial Blaster Start IASA callback
void ftFox_SpecialAirNStart_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (((u32)fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->foxVars[0].SpecialN.isBlasterLoop = TRUE;
    }
}

// 0x800E6B30
// https://decomp.me/scratch/7JCEh // Fox & Falco's aerial Blaster Loop IASA callback
void ftFox_SpecialAirNLoop_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (((u32)fp->x2200_ftcmd_var0 != 0U) && (fp->input.x668 & HSD_BUTTON_B))
    {
        fp->foxVars[0].SpecialN.isBlasterLoop = TRUE;
    }
}

// 0x800E6B58 - Fox & Falco's aerial Blaster End IASA callback
void ftFox_SpecialAirNEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E6B5C - Fox & Falco's grounded Blaster Start Physics callback
void ftFox_SpecialNStart_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x800E6B7C - Fox & Falco's grounded Blaster Loop Physics callback
void ftFox_SpecialNLoop_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x800E6B9C - Fox & Falco's grounded Blaster End Physics callback
void ftFox_SpecialNEnd_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

extern void func_80084DB0(HSD_GObj*);

// 0x800E6BBC - Fox & Falco's aerial Blaster Start Physics callback
void ftFox_SpecialAirNStart_Phys(HSD_GObj* fighter_gobj)
{
    func_80084DB0(fighter_gobj);
}

// 0x800E6BDC - Fox & Falco's aerial Blaster Loop Physics callback
void ftFox_SpecialAirNLoop_Phys(HSD_GObj* fighter_gobj)
{
    func_80084DB0(fighter_gobj);
}

// 0x800E6BFC - Fox & Falco's aerial Blaster End Physics callback
void ftFox_SpecialAirNEnd_Phys(HSD_GObj* fighter_gobj)
{
    func_80084DB0(fighter_gobj);
}

// 0x800E6C1C - Fox & Falco's grounded Blaster Start Collision callback
void ftFox_SpecialNStart_Coll(HSD_GObj* fighter_gobj)
{
    func_80083F88(fighter_gobj);
}

// 0x800E6C3C - Fox & Falco's grounded Blaster Loop Collision callback
void ftFox_SpecialNLoop_Coll(HSD_GObj* fighter_gobj)
{
    func_80083F88(fighter_gobj);
}

// 0x800E6C1C - Fox & Falco's grounded Blaster End Collision callback
void ftFox_SpecialNEnd_Coll(HSD_GObj* fighter_gobj)
{
    func_80083F88(fighter_gobj);
}

extern void func_80082B78(HSD_GObj*);

// 0x800E6C7C - Fox & Falco's aerial Blaster Start Collision callback
void ftFox_SpecialAirNStart_Coll(HSD_GObj* fighter_gobj)
{
    func_80082B78(fighter_gobj);
}

// 0x800E6C9C - Fox & Falco's aerial Blaster Loop Collision callback
void ftFox_SpecialAirNLoop_Coll(HSD_GObj* fighter_gobj)
{
    func_80082B78(fighter_gobj);
}

// 0x800E6CBC - Fox & Falco's aerial Blaster End Collision callback
void ftFox_SpecialAirNEnd_Coll(HSD_GObj* fighter_gobj)
{
    func_80082B78(fighter_gobj);
}

extern void func_80094818(HSD_GObj*, s32);
extern void func_8026BAE8(HSD_GObj*, f32);
extern void func_8029C6A4(f32, f32, HSD_GObj*, Vec3*, s32);
extern void func_8029C6CC(f32, f32, HSD_GObj*, Vec3*, s32);
extern void func_802ADDD0(HSD_GObj*, s32);                    
extern void func_802AE1D0(HSD_GObj*);       
extern void func_802AE538(HSD_GObj*); 
extern void func_802AE608(HSD_GObj*);
extern HSD_GObj* func_802AE8A8(f32, HSD_GObj*, Vec3*, s32, s32);
extern void func_800E5588(HSD_GObj*);

// 0x800E6CDC
// https://decomp.me/scratch/G1jsj // Fox & Falco's Throw Animation callback - spawn Blaster
void ftFox_Throw_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    s32 ftKind = ftGetKind(fp);

    if ((ftKind == FTKIND_FOX) || (ftKind == FTKIND_FALCO))
    {
        if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
        {
            fp->sa.fox.x222C_blasterGObj = NULL;
            ftFox_SpecialN_SetNULL(fighter_gobj);
            return;
        }
        switch (fp->x2204_ftcmd_var1)
        {
        case 1:
            if (fp->sa.fox.x222C_blasterGObj == NULL)
            {
                HSD_GObj* blasterGObj = func_802AE8A8(fp->x2C_facing_direction, fighter_gobj, &fp->xB0_pos, func_8007500C(fp, 0x31), foxAttrs->x20_FOX_BLASTER_GUN_ITKIND);

                fp->sa.fox.x222C_blasterGObj = blasterGObj;
                if (blasterGObj != NULL)
                {
                    func_8026BAE8(fp->sa.fox.x222C_blasterGObj, (0.8500000238418579f * (fp->x34_scale.y * fp->x110_attr.x19C_ModelScaling)));
                    ftFox_SpecialN_SetCall(fighter_gobj);
                }
                return;
            }
            else
            {
                s32 flag;

                func_802ADDD0(fp->sa.fox.x222C_blasterGObj, fp->x2204_ftcmd_var1);
                switch (fp->x220C_ftcmd_var3)
                {
                case 1:
                    fp->x220C_ftcmd_var3 = 0;
                    func_802AE538(fp->sa.fox.x222C_blasterGObj);
                    break;
                case 2:
                    fp->x220C_ftcmd_var3 = 0;
                    func_802AE608(fp->sa.fox.x222C_blasterGObj);
                    break;
                }
                if (fp->x2210_ThrowFlags.b0 != 0)
                {
                    fp->x2210_ThrowFlags.b0 = 0;
                    flag = TRUE;
                }
                else
                {
                    flag = FALSE;
                }
                if (flag != FALSE)
                {
                    Vec3 sp50;
                    Vec3 sp44;

                    ftFox_FtGetHoldJoint(fighter_gobj, &sp50);
                    ftFox_ItGetHoldJoint(fighter_gobj, &sp44);

                    sp44.z = 0.0f;
                    sp50.z = 0.0f;
                    switch (ftGetAction(fp))
                    {
                    case ASID_THROWB:
                    case ASID_THROWHI:
                    case ASID_THROWLW:

                        func_8029C6CC(atan2f(sp50.y - sp44.y, sp50.x - sp44.x), foxAttrs->x14_FOX_BLASTER_VEL, fighter_gobj, &sp50, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;

                    default:
                        func_8029C6A4(atan2f(sp50.y - sp44.y, sp50.x - sp44.x), foxAttrs->x14_FOX_BLASTER_VEL, fighter_gobj, &sp50, foxAttrs->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;
                    }
                    func_802AE1D0(fp->sa.fox.x222C_blasterGObj);
                    switch (ftGetAction(fp))
                    {
                    case ASID_THROWHI:
                    case ASID_THROWLW:
                    {
                        switch (func_800872A4(fighter_gobj))
                        {
                        case FTKIND_FOX:
                            func_80088148(fp, 0x1AE1DU, SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;
                        case FTKIND_FALCO:
                            func_80088148(fp, 0x18709U, SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;
                        }
                    default: break;
                    }
                    case ASID_THROWB:
                        switch (func_800872A4(fighter_gobj))
                        {

                        case FTKIND_FOX:
                            func_80088148(fp, foxSFX[1.0f == fp->x2C_facing_direction], SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;

                        case FTKIND_FALCO:
                            func_80088148(fp, falcoSFX[1.0f == fp->x2C_facing_direction], SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
        case 2:
            if (fp->sa.fox.x222C_blasterGObj != NULL)
            {
                fp->sa.fox.x222C_blasterGObj = NULL;
                ftFox_SpecialN_SetNULL(fighter_gobj);
                switch (func_800872A4(fighter_gobj))
                {
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
            fp->sa.fox.x222C_blasterGObj = NULL;
            ftFox_SpecialN_SetNULL(fighter_gobj);
            func_80094818(fighter_gobj, 0);
            break;
        }
    }
}
