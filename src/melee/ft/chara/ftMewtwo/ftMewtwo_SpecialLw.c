#include <melee/ft/chara/ftMewtwo/ftmewtwo.h>

// 0x80146198
// https://decomp.me/scratch/QML6g // Reset Disable Stall flag
void ftMewtwo_SpecialLw_ClearDisableGObj(HSD_GObj* fighter_gobj)
{
    getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj = NULL;
}

extern void func_802C49E0(HSD_GObj*);

// 0x801461A8
// https://decomp.me/scratch/d5gF6 // Remove Disable projectile
void ftMewtwo_SpecialLw_RemoveDisable(HSD_GObj* fighter_gobj)
{
    if (getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj != NULL)
    {
        func_802C49E0(getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj);
        getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj = NULL;
    }
}

// 0x801461F0
// https://decomp.me/scratch/WnODY // Mewtwo's grounded Disable Action State handler
void ftMewtwo_SpecialLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 var;

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->sa.mewtwo.x222C_disableGObj = NULL;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALLW, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialLw_CreateDisable;
}

// 0x80146264
// https://decomp.me/scratch/fX4aP // Mewtwo's aerial Disable Action State handler
void ftMewtwo_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 var;

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->sa.mewtwo.x222C_disableGObj = NULL;
    fp->x80_self_vel.y = 0.0f;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALAIRLW, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialLw_CreateDisable;
}

//0x801462DC
// https://decomp.me/scratch/2no6L // Mewtwo's grounded Disable Animation callback
void ftMewtwo_SpecialLw_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if (getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj != NULL)
        {
            func_802C49E0(getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj);
            getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj = NULL;
        }
        func_8008A2BC(fighter_gobj);
    }
}

// 0x80146338 - Mewtwo's aerial Disable Animation callback
void ftMewtwo_SpecialAirLw_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if (getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj != NULL)
        {
            func_802C49E0(getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj);
            getFighter(fighter_gobj)->sa.mewtwo.x222C_disableGObj = NULL;
        }
        func_800CC730(fighter_gobj);
    }
}

// 0x80146394 - Mewtwo's grounded Disable IASA callback
void ftMewtwo_SpecialLw_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80146398 - Mewtwo's aerial Disable IASA callback
void ftMewtwo_SpecialAirLw_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014639C - Mewtwo's grounded Disable Physics callback
void ftMewtwo_SpecialLw_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x801463BC
// https://decomp.me/scratch/haV3L // Mewtwo's aerial Disable Physics callback
void ftMewtwo_SpecialAirLw_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    attr* ftAttrs = getFtAttrs(fp);

    func_8007D494(fp, mewtwoAttrs->x78_MEWTWO_DISABLE_GRAVITY, mewtwoAttrs->x7C_MEWTWO_DISABLE_TERMINAL_VELOCITY);
    func_8007CE94(fp, ftAttrs->x180_AerialFriction);
}

inline void ftMewtwo_SpecialLw_SetCall(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->sa.mewtwo.x222C_disableGObj != NULL)
    {
        fp->cb.x21E4_callback_OnDeath2 = ftMewtwo_OnDeath2;
        fp->cb.x21DC_callback_OnTakeDamage = ftMewtwo_OnTakeDamage;
    }
}

extern void func_8007D468(Fighter* fp);

// 0x80146410
// https://decomp.me/scratch/ktqvT // Mewtwo's ground -> air Disable Action State handler
void ftMewtwo_SpecialLw_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 var;

    func_8007D5D4(fp);

    fp->x80_self_vel.y = 0.0f;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALAIRLW, FTMEWTWO_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialLw_CreateDisable;

    ftMewtwo_SpecialLw_SetCall(fighter_gobj);

    func_8007D468(fp);
}

// 0x801464B0
// https://decomp.me/scratch/xNFhq // Mewtwo's air -> ground Disable Action State handler
void ftMewtwo_SpecialAirLw_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 var;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALLW, FTMEWTWO_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialLw_CreateDisable;

    ftMewtwo_SpecialLw_SetCall(fighter_gobj);
}

extern void func_8008403C(HSD_GObj*, void(*cb_Coll)(HSD_GObj*));
extern void func_80082C74(HSD_GObj*, void(*cb_Coll)(HSD_GObj*));

// 0x80146544 - Mewtwo's grounded Disable Collision callback
void ftMewtwo_SpecialLw_Coll(HSD_GObj* fighter_gobj)
{
    func_8008403C(fighter_gobj, ftMewtwo_SpecialLw_GroundToAir);
}

// 0x8014656C - Mewtwo's aerial Disable Collision callback
void ftMewtwo_SpecialAirLw_Coll(HSD_GObj* fighter_gobj)
{
    func_80082C74(fighter_gobj, ftMewtwo_SpecialAirLw_AirToGround);
}

extern HSD_GObj* func_802C4A40(HSD_GObj*, Vec3*, f32);

// 0x80146594
// https://decomp.me/scratch/rAoIe // Create Disable projectile
void ftMewtwo_SpecialLw_CreateDisable(HSD_GObj* fighter_gobj)
{
    Vec3 sp18;
    Fighter* fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs;
    HSD_GObj* disableGObj;

    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        mewtwoAttrs = getFtSpecialAttrsD(fp);

        func_8000B1CC(fp->x5E8_fighterBones[0x1B].x0_jobj, NULL, &sp18);

        sp18.x += (mewtwoAttrs->x80_MEWTWO_DISABLE_OFFSET_X * fp->x2C_facing_direction);
        sp18.y += mewtwoAttrs->x84_MEWTWO_DISABLE_OFFSET_Y;

        fp->sa.mewtwo.x222C_disableGObj = func_802C4A40(fighter_gobj, &sp18, fp->x2C_facing_direction);

        ftMewtwo_SpecialLw_SetCall(fighter_gobj);

        fp->x2200_ftcmd_var0 = 0U;
    }
}
