#include <melee/ft/chara/ftLuigi/ftluigi.h>

// 0x801445C4
// https://decomp.me/scratch/TTyNT // Luigi Cyclone Rotation Update
void ftLuigi_SpecialLw_UpdateRot(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    func_8007592C(fp, 0, 0.0f);
}

extern void func_8007D440(Fighter*, f32);

inline void ftLuigi_SpecialLw_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->luigiVars[0].SpecialLw.groundVelX = (f32)0.0f;
    fp->luigiVars[0].SpecialLw.unk = (s32)luigiAttrs->x88_LUIGI_CYCLONE_UNK + 1;
    fp->luigiVars[0].SpecialLw.isUnkColl = FALSE;
}

inline void ftLuigi_SpecialLw_SetCall(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    fp->cb.x21DC_callback_OnTakeDamage = ftLuigi_SpecialLw_UpdateRot;
    fp->cb.x21E4_callback_OnDeath2 = ftLuigi_SpecialLw_UpdateRot;
}

inline void ftLuigi_SpecialLw_SetGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_JObj* hsd_obj = fighter_gobj->hsd_obj;
    ef_Spawn(0x509, fighter_gobj, hsd_obj);
    fp->x2219_flag.bits.b0 = 1;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x801445F0
// https://decomp.me/scratch/ // Luigi's grounded Cyclone Action State handler
void ftLuigi_SpecialLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    Fighter* temp_fp;
    Fighter* var[7];
    Fighter* fp2;

    temp_fp = (fp = getFighter(fighter_gobj));
    luigiAttrs = temp_fp->x2D4_specialAttributes;
    fp2 = temp_fp;
    getFighter(fighter_gobj)->x2208_ftcmd_var2 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRLW, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp2->x80_self_vel.y = (f32)(luigiAttrs->x70_LUIGI_CYCLONE_TAP_MOMENTUM - luigiAttrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX);
    func_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    ftLuigi_SpecialLw_SetVars(fighter_gobj);
    ftLuigi_SpecialLw_SetCall(fighter_gobj);
    ftLuigi_SpecialLw_SetGFX(fighter_gobj);
    fp2->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp2->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x80144708
// https://decomp.me/scratch/egaIB // Luigi's aerial Cyclone Action State handler
void ftLuigi_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    Fighter* temp_fp;
    Fighter* var[7];
    Fighter* fp2;
    f32 cycloneVar;

    temp_fp = (fp = getFighter(fighter_gobj));
    luigiAttrs = temp_fp->x2D4_specialAttributes;
    fp2 = temp_fp;
    getFighter(fighter_gobj)->x2208_ftcmd_var2 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRLW, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    if (fp2->sa.luigi.x222C_cycloneCharge != 0)
    {
        cycloneVar = 0.0f;
    }
    else cycloneVar = luigiAttrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
    fp2->x80_self_vel.y = (f32)(luigiAttrs->x70_LUIGI_CYCLONE_TAP_MOMENTUM - cycloneVar);
    func_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    ftLuigi_SpecialLw_SetVars(fighter_gobj);
    ftLuigi_SpecialLw_SetCall(fighter_gobj);
    ftLuigi_SpecialLw_SetGFX(fighter_gobj);
    fp2->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp2->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

inline void ftLuigi_SpecialLw_SetNULL(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
}

// 0x80144830
// https://decomp.me/scratch/ye3Hd // Luigi's grounded Cyclone Animation callback
void ftLuigi_SpecialLw_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialLw_SetNULL(fighter_gobj);
        func_8008A2BC(fighter_gobj);
    }
}

// 0x8014487C
// https://decomp.me/scratch/gssxH // Luigi's aerial Cyclone Animation callback
void ftLuigi_SpecialAirLw_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    Fighter* temp_fp;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    s32 cycloneLanding;

    if ((u32)fp->x2204_ftcmd_var1 != 0U)
    {
        fp->x2204_ftcmd_var1 = 0U;
        fp->sa.luigi.x222C_cycloneCharge = TRUE;
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialLw_SetNULL(fighter_gobj);
        cycloneLanding = luigiAttrs->x94_LUIGI_CYCLONE_LANDING_LAG;
        if ((f32)0.0f == (f64)cycloneLanding)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 0, 1, 1.0f, (f32)cycloneLanding);
    }
}

// 0x80144950 - Luigi's grounded Cyclone IASA callback
void ftLuigi_SpecialLw_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80144954 - Luigi's aerial Cyclone IASA callback
void ftLuigi_SpecialAirLw_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

extern void ftComm_ClampFalllSpeed(Fighter*, f32);
extern void func_8007CADC(Fighter*, f32, f32, f32);
extern void func_8007D440(Fighter*, f32);

inline void ftLuigi_SpecialLw_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);
    fp->x2208_ftcmd_var2 = 0;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x166, 0x0C4C508A, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftComm_ClampFalllSpeed(fp, luigiAttrs->x90_LUIGI_CYCLONE_TAP_GRAVITY);
    func_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x80144958
// https://decomp.me/scratch/pXs3o // Luigi's grounded Cyclone Physics callback
void ftLuigi_SpecialLw_Phys(HSD_GObj* fighter_gobj)
{
    ftLuigiAttributes* luigiAttrs;
    Fighter* fp;
    f32 var;
    f32 var2;
    f32 var3;

    fp = fighter_gobj->user_data;
    luigiAttrs = getFtSpecialAttrs(fp);
    var2 = luigiAttrs->x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND;
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        fp->luigiVars[0].SpecialLw.groundVelX -= luigiAttrs->x84_LUIGI_CYCLONE_FRICTION_END;
        var2 += fp->luigiVars[0].SpecialLw.groundVelX;
        if (var2 < 0.0f)
        {
            var2 = 0.0f;
        }
    }
    func_8007CADC(fp, 0.0f, luigiAttrs->x7C_LUIGI_CYCLONE_MOMENTUM_X_MUL_GROUND, var2);
    func_8007CB74(fighter_gobj);
    if (((u32)fp->x2208_ftcmd_var2 != 0U) && ((fp->input.x668 & HSD_BUTTON_B) != FALSE))
    {
        fp->x80_self_vel.y += luigiAttrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
        ftLuigi_SpecialLw_GroundToAir(fighter_gobj);
    }
}

extern void func_8007D3A8(Fighter*, f32, f32, f32);
extern void func_8007D508(Fighter*, f32, f32);

// 0x80144A74C
// https://decomp.me/scratch/85hbq // Luigi's aerial Cyclone Physics callback
void ftLuigi_SpecialAirLw_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    ftLuigiAttributes* luigiAttrs2;
    f32 var;
    f32 unused;
    f32 vel;

    fp = fighter_gobj->user_data;
    luigiAttrs = fp->x2D4_specialAttributes;
    if (((s32)fp->sa.luigi.x222C_cycloneCharge == FALSE) && ((u32)fp->x2208_ftcmd_var2 != 0U) && ((fp->input.x668 & HSD_BUTTON_B) != FALSE))
    {
        func_8007D508(fp, luigiAttrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX, luigiAttrs->x90_LUIGI_CYCLONE_TAP_GRAVITY);
    }
    func_8007D4B8(fp);
    var = luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR;
    luigiAttrs2 = fp->x2D4_specialAttributes;
    if ((u32)fp->x2200_ftcmd_var0 != 0)
    {
        fp->luigiVars[0].SpecialLw.groundVelX -= luigiAttrs2->x84_LUIGI_CYCLONE_FRICTION_END;
        var += fp->luigiVars[0].SpecialLw.groundVelX;
        if (var < 0.0f)
        {
            var = 0.0f;
        }
    }
    func_8007D3A8(fp, 0.0f, luigiAttrs->x80_LUIGI_CYCLONE_MOMENTUM_X_MUL_AIR, var);
}

extern BOOL func_800824A0(HSD_GObj*, struct UnkEnvCollBox*);
extern BOOL func_80082888(HSD_GObj*, struct UnkEnvCollBox*);

struct UnkEnvCollBox
{
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
};

extern struct UnkEnvCollBox lbl_803D0AE8;

inline void ftLuigi_SpecialLw_UnkAngle(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (((u32)fp->x220C_ftcmd_var3 != 0U) && ((s32)fp->luigiVars[0].SpecialLw.isUnkColl != FALSE))
    {
        func_8007592C(fp, 0, fp->x2C_facing_direction * atan2f(fp->x6F0_collData.x14C_ground.normal.x, fp->x6F0_collData.x14C_ground.normal.y));
        return;
    }
    func_8007592C(fp, 0, 0.0f);
}

// 0x80144B38
// https://decomp.me/scratch/Yaesq // Luigi's grounded Cyclone Collision callback
void ftLuigi_SpecialLw_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 var[5];

    if ((s32)fp->xE0_ground_or_air == GA_Ground)
    {
        if (func_80082888(fighter_gobj, &lbl_803D0AE8) == FALSE)
        {
            ftLuigi_SpecialLw_GroundToAir(fighter_gobj);
            fp->luigiVars[0].SpecialLw.isUnkColl = FALSE;
        }
        else
        {
            fp->luigiVars[0].SpecialLw.isUnkColl = TRUE;
        }
    }
    else if (func_800824A0(fighter_gobj, &lbl_803D0AE8) == FALSE)
    {
        ftLuigi_SpecialLw_GroundToAir(fighter_gobj);
        fp->luigiVars[0].SpecialLw.isUnkColl = FALSE;
    }
    else
    {
        fp->luigiVars[0].SpecialLw.isUnkColl = TRUE;
    }
    ftLuigi_SpecialLw_UnkAngle(fighter_gobj);
}

inline void ftLuigi_SpecialAirLw_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    fp->x2208_ftcmd_var2 = 0;
    func_8007D7FC(fp);
    fp->x80_self_vel.y = 0.0f;
    fp->sa.luigi.x222C_cycloneCharge = FALSE;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALLW, FTLUIGI_SPECIALLW_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007CC78(fp, luigiAttrs->x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x80144CEC
// https://decomp.me/scratch/fdQ4f // Luigi's aerial Cyclone Collision callback
void ftLuigi_SpecialAirLw_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 var[8];

    if (func_800824A0(fighter_gobj, &lbl_803D0AE8) != FALSE)
    {
        ftLuigi_SpecialAirLw_AirToGround(fighter_gobj);
        fp->luigiVars[0].SpecialLw.isUnkColl = TRUE;
    }
    else
    {
        fp->luigiVars[0].SpecialLw.isUnkColl = FALSE;
    }
    ftLuigi_SpecialLw_UnkAngle(fighter_gobj);
}
