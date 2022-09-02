#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>

extern HSD_GObj* func_802C7D60(HSD_GObj*, Vec3*, s32, f32);

// 0x8014CBF4
// https://decomp.me/scratch/c9uUz // Create Oil Panic Item //
void ftGameWatch_ItemPanicSetup(HSD_GObj* fighter_gobj)
{
    Vec3 sp1C;
    void (*cb_OnDeath2)(HSD_GObj*);
    void (*cb_OnTakeDamage)(HSD_GObj*);
    void (*cb_EnterHitlag)(HSD_GObj*);
    void (*cb_ExitHitlag)(HSD_GObj*);

    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2268_panicGObj == NULL)
    {
        func_8000B1CC(fp->x5E8_fighterBones[0].x0_jobj, NULL, &sp1C);
        fp->sa.gaw.x2268_panicGObj = func_802C7D60(fighter_gobj, &sp1C, 0, fp->x2C_facing_direction);
    }
    if (fp->sa.gaw.x2268_panicGObj != NULL)
    {
        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
    }
    fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemPanicEnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemPanicExitHitlag;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014CC9C
// https://decomp.me/scratch/Cdp6X // Set Oil Panic flags + clear pointers
void ftGameWatch_ItemPanicSetFlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    ftGameWatch_ItemPanicExitHitlag(fighter_gobj);
    fp->sa.gaw.x2268_panicGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

extern void func_802C7E94(HSD_GObj*);

// 0x8014CCD8
// https://decomp.me/scratch/UDMIR // Remove Oil Panic item
void ftGameWatch_ItemPanicRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* panicGObj;
    HSD_GObj* panicGObj2;

    if (fp->sa.gaw.x2268_panicGObj != NULL)
    {
        func_802C7E94(fp->sa.gaw.x2268_panicGObj);
        ftGameWatch_ItemPanicSetFlag(fighter_gobj);
    }
}

extern void func_802C7EE0(HSD_GObj*);
extern void func_802C7F00(HSD_GObj*);

// 0x8014CD38 - Apply hitlag to Oil Panic item
void ftGameWatch_ItemPanicEnterHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.gaw.x2268_panicGObj != NULL)
    {
        func_802C7EE0(fp->sa.gaw.x2268_panicGObj);
    }
}

// 0x8014CD68 - Remove hitlag for Oil Panic item
void ftGameWatch_ItemPanicExitHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.gaw.x2268_panicGObj != NULL)
    {
        func_802C7F00(fp->sa.gaw.x2268_panicGObj);
    }
}

// 0x8014CD98
// https://decomp.me/scratch/QwezP // Check if Mr. Game & Watch is in any of his Oil Panic Action States
BOOL ftGameWatch_ItemCheckPanicRemove(HSD_GObj* fighter_gobj)
{
    s32 ASID = ((Fighter*)fighter_gobj->user_data)->x10_action_state_index;

    if ((ASID >= AS_GAMEWATCH_SPECIALLW_SHOOT) && (ASID <= AS_GAMEWATCH_SPECIALAIRLW_SHOOT))
    {
        return FALSE;
    }
    return TRUE;
}

extern void func_80074B0C(HSD_GObj*, s32, s32);

// 0x8014CDC0
// https://decomp.me/scratch/bF0RR // Update Oil Panic charge level indicator models
void ftGameWatch_SpecialLw_UpdateBucketModel(HSD_GObj* fighter_gobj)
{
    s32 modelState;
    Fighter* fp = fighter_gobj->user_data;

    func_80074B0C(fighter_gobj, 5, 2);
    modelState = fp->sa.gaw.x2238_panicCharge;
    switch (modelState)
    {
    case GAMEWATCH_PANIC_EMPTY:
        func_80074B0C(fighter_gobj, 6, -1);
        func_80074B0C(fighter_gobj, 7, -1);
        func_80074B0C(fighter_gobj, 8, -1);
        return;
    case GAMEWATCH_PANIC_LOW:
        func_80074B0C(fighter_gobj, 6, 0);
        func_80074B0C(fighter_gobj, 7, -1);
        func_80074B0C(fighter_gobj, 8, -1);
        return;
    case GAMEWATCH_PANIC_MID:
        func_80074B0C(fighter_gobj, 6, 0);
        func_80074B0C(fighter_gobj, 7, 0);
        func_80074B0C(fighter_gobj, 8, -1);
        return;
    case GAMEWATCH_PANIC_FULL:
    default:
        func_80074B0C(fighter_gobj, 6, 0);
        func_80074B0C(fighter_gobj, 7, 0);
        func_80074B0C(fighter_gobj, 8, 0);
        return;
    }
}

inline void ftGameWatch_SpecialLw_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->gameWatchVars[0].SpecialLw.isRelease = FALSE;
    fp->gameWatchVars[0].SpecialLw.turnFrames = 0;
}

// 0x8014CEF0
// https://decomp.me/scratch/P6t9i // Mr. Game & Watch's Oil Panic Start Action State handler
void ftGameWatch_SpecialLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL)
    {
        ftGameWatch_SpecialLwShoot_ReleaseOil(fighter_gobj);
        return;
    }
    fp->x80_self_vel.y = 0.0f;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALLW, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_SetVars(fighter_gobj);
}

// 0x8014CF78
// https://decomp.me/scratch/NxM32
void ftGameWatch_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = fp->x2D4_specialAttributes;

    if (fp->sa.gaw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL)
    {
        ftGameWatch_SpecialAirLwShoot_ReleaseOil(fighter_gobj);
        return;
    }
    fp->x80_self_vel.x /= gawAttrs->x64_GAMEWATCH_PANIC_MOMENTUM_PRESERVE;
    fp->x80_self_vel.y = 0.0f;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_SetVars(fighter_gobj);
}

extern void ftColl_CreateAbsorbHit(HSD_GObj*, AbsorbDesc*);

inline void ftGameWatch_SpecialLw_UpdateVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    u32 ftcmd_var = fp->x2200_ftcmd_var0;
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);
    if (ftcmd_var == 1U)
    {
        fp->x2200_ftcmd_var0 = 2U;
        ftColl_CreateAbsorbHit(fighter_gobj, &gawAttrs->x80_GAMEWATCH_PANIC_ABSORPTION);
    }
    else if (ftcmd_var == 0U)
    {
        fp->x2218_flag.bits.b6 = 0;
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    }
}

// 0x8014D014
// https://decomp.me/scratch/UxcJl // Mr. Game & Watch's grounded Oil Panic Loop Animation callback
void ftGameWatch_SpecialLw_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((38.0f == fp->x894_currentAnimFrame) && ((s32)fp->gameWatchVars[0].SpecialLw.isRelease == FALSE))
    {
        ftGameWatch_SpecialLw_UpdateAction(fighter_gobj, 5.0f);
    }
    ftGameWatch_SpecialLw_UpdateVars(fighter_gobj);
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x8014D014
// https://decomp.me/scratch/u5lmv // Mr. Game & Watch's aerial Oil Panic Loop Animation callback
void ftGameWatch_SpecialAirLw_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((38.0f == fp->x894_currentAnimFrame) && ((s32)fp->gameWatchVars[0].SpecialLw.isRelease == FALSE))
    {
        ftGameWatch_SpecialAirLw_UpdateAction(fighter_gobj, 5.0f);
    }
    ftGameWatch_SpecialLw_UpdateVars(fighter_gobj);
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x8014D1AC
// https://decomp.me/scratch/U5Cl2 // Mr. Game & Watch's grounded Oil Panic Loop IASA callback
void ftGameWatch_SpecialLw_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 facingDir;
    f32 stick_range;
    s32 turnFrames;
    ftGameWatchAttributes* gawAttrs;

    fp = fighter_gobj->user_data;
    turnFrames = fp->gameWatchVars[0].SpecialLw.turnFrames;
    gawAttrs = getFtSpecialAttrs(fp);
    if (turnFrames > 0)
    {
        fp->gameWatchVars[0].SpecialLw.turnFrames = turnFrames - 1;
    }
    else
    {
        stick_range = fp->input.x620_lstick_x;
        if (stick_range < 0.0f)
        {
            stick_range = -stick_range;
        }
        if (stick_range > p_ftCommonData->x0) 
        {
            facingDir = fp->x2C_facing_direction;
            func_8007D9FC(fp);
            if (facingDir != fp->x2C_facing_direction)
            {
                fp->gameWatchVars[0].SpecialLw.turnFrames = (s32)gawAttrs->x7C_GAMEWATCH_PANIC_TURN_FRAMES;
            }
        }
    }
    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->gameWatchVars[0].SpecialLw.isRelease = TRUE;
    }
}

// 0x8014D264
// https://decomp.me/scratch/XVThc // Mr. Game & Watch's aerial Oil Panic Loop IASA callback
void ftGameWatch_SpecialAirLw_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 facingDir;
    f32 stick_range;
    s32 turnFrames;
    ftGameWatchAttributes* gawAttrs;

    fp = fighter_gobj->user_data;
    turnFrames = fp->gameWatchVars[0].SpecialLw.turnFrames;
    gawAttrs = getFtSpecialAttrs(fp);
    if (turnFrames > 0)
    {
        fp->gameWatchVars[0].SpecialLw.turnFrames = turnFrames - 1;
    }
    else
    {
        stick_range = fp->input.x620_lstick_x;
        if (stick_range < 0.0f)
        {
            stick_range = -stick_range;
        }
        if (stick_range > p_ftCommonData->x0) 
        {
            facingDir = fp->x2C_facing_direction;
            func_8007D9FC(fp);
            if (facingDir != fp->x2C_facing_direction)
            {
                fp->gameWatchVars[0].SpecialLw.turnFrames = (s32)gawAttrs->x7C_GAMEWATCH_PANIC_TURN_FRAMES;
            }
        }
    }
    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->gameWatchVars[0].SpecialLw.isRelease = TRUE;
    }
}

extern void func_8007AF10(HSD_GObj*);

// 0x8014D31C
// https://decomp.me/scratch/aC057 // Mr. Game & Watch's grounded Oil Panic Loop Physics callback
void ftGameWatch_SpecialLw_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AF10(fighter_gobj);
}

void func_8007AF10(HSD_GObj*);

// 0x8014D350
// https://decomp.me/scratch/3eki5 // Mr. Game & Watch's aerial Oil Panic Loop Physics callback
void ftGameWatch_SpecialAirLw_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftGameWatchAttributes* gawAttrs = fp->x2D4_specialAttributes;
    f32 fall_accel;
    f32 momentum_mul;
    f32 termnial_velocity;
    f32 unk;

    func_8007D494(fp, gawAttrs->x6C_GAMEWATCH_PANIC_FALL_ACCEL, gawAttrs->x70_GAMEWATCH_PANIC_VEL_Y_MAX);
    func_8007CE94(fp, gawAttrs->x68_GAMEWATCH_PANIC_MOMENTUM_MUL);
    func_8007AF10(fighter_gobj);
}

// 0x8014D3B4
// https://decomp.me/scratch/yrY9J // Mr. Game & Watch's grounded Oil Panic Loop Collision callback
void ftGameWatch_SpecialLw_Coll(HSD_GObj* fighter_gobj)
{
    if (func_800827A0(fighter_gobj) == FALSE)
    {
        ftGameWatch_SpecialLw_GroundToAir(fighter_gobj);
    }
}

// 0x8014D3F0 - Mr. Game & Watch's aerial Oil Panic Loop Collision callback
void ftGameWatch_SpecialAirLw_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftGameWatch_SpecialAirLw_AirToGround(fighter_gobj);
    }
}

inline void ftGameWatch_SpecialLw_UpdateVarsColl(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    u32 ftcmd_var = fp->x2200_ftcmd_var0;
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);
    if (ftcmd_var == 2U)
    {
        ftColl_CreateAbsorbHit(fighter_gobj, &gawAttrs->x80_GAMEWATCH_PANIC_ABSORPTION);
    }
    else if (ftcmd_var == 0U)
    {
        fp->x2218_flag.bits.b6 = 0;
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    }
}

// 0x8014D42C
// https://decomp.me/scratch/I9dd1
void ftGameWatch_SpecialLw_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW, FTGAMEWATCH_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftGameWatch_SpecialLw_UpdateVarsColl(fighter_gobj);
}

// 0x8014D4DC
// https://decomp.me/scratch/xk6So
void ftGameWatch_SpecialAirLw_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALLW, FTGAMEWATCH_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftGameWatch_SpecialLw_UpdateVarsColl(fighter_gobj);
}

inline void ftGameWatch_SpecialLw_UpdateVarsAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);
    if ((u32)fp->x2200_ftcmd_var0 >= 1U)
    {
        fp->x2200_ftcmd_var0 = 2U;
        ftColl_CreateAbsorbHit(fighter_gobj, &gawAttrs->x80_GAMEWATCH_PANIC_ABSORPTION);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    }
}

// 0x8014D58C
// https://decomp.me/scratch/qFKjA
void ftGameWatch_SpecialLw_UpdateAction(HSD_GObj* fighter_gobj, f32 animFrame)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALLW, FTGAMEWATCH_SPECIALLW_UPDATE_FLAG, NULL, animFrame - 1.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(fighter_gobj);
}

// 0x8014D620
// https://decomp.me/scratch/N583p
void ftGameWatch_SpecialAirLw_UpdateAction(HSD_GObj* fighter_gobj, f32 animFrame)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW, FTGAMEWATCH_SPECIALLW_UPDATE_FLAG, NULL, animFrame - 1.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(fighter_gobj);
}

// 0x8014D6B4
// https://decomp.me/scratch/WEwao // Mr. Game & Watch's grounded Oil Panic Fill Action State handler
void ftGameWatch_SpecialLwCatch_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if ((s32)fp->sa.gaw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL)
        {
            func_8008A2BC(fighter_gobj);
            return;
        }
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALLW, FTGAMEWATCH_SPECIALLW_UPDATE_FLAG, NULL, 4.0f, 1.0f, 0.0f);
        func_8006EBA4(fighter_gobj);
        ftGameWatch_SpecialLw_UpdateVarsAction(fighter_gobj);
    }
}

// 0x8014D774 - Mr. Game & Watch's aerial Oil Panic Fill Animation callback
void ftGameWatch_SpecialAirLwCatch_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if ((s32)fp->sa.gaw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW, FTGAMEWATCH_SPECIALLW_UPDATE_FLAG, NULL, 4.0f, 1.0f, 0.0f);
        func_8006EBA4(fighter_gobj);
        ftGameWatch_SpecialLw_UpdateVarsAction(fighter_gobj);
    }
}

// 0x8014D834 - Mr. Game & Watch's grounded Oil Panic Fill IASA callback
void ftGameWatch_SpecialLwCatch_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014D838 - Mr. Game & Watch's aerial Oil Panic Fill IASA callback
void ftGameWatch_SpecialAirLwCatch_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014D83C - Mr. Game & Watch's grounded Oil Panic Fill Physics callback
void ftGameWatch_SpecialLwCatch_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x8014D85C - Mr. Game & Watch's aerial Oil Panic Fill Physics callback
void ftGameWatch_SpecialAirLwCatch_Phys(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

// 0x8014D87C
// https://decomp.me/scratch/Me11F // Mr. Game & Watch's grounded Oil Panic Fill Collision callback
void ftGameWatch_SpecialLwCatch_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftGameWatch_SpecialLwCatch_GroundToAir(fighter_gobj);
    }
}

// 0x8014D8B8 - Mr. Game & Watch's aerial Oil Panic Fill Collision callback
void ftGameWatch_SpecialAirLwCatch_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftGameWatch_SpecialAirLwCatch_AirToGround(fighter_gobj);
    }
}

// 0x8014D8F4
// https://decomp.me/scratch/zwOYe // Mr. Game & Watch's ground -> air Oil Panic Fill Action State handler
void ftGameWatch_SpecialLwCatch_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW_CATCH, FTGAMEWATCH_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x8014D954 - Mr. Game & Watch's air -> ground Oil Panic Fill Action State handler
void ftGameWatch_SpecialAirLwCatch_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALLW_CATCH, FTGAMEWATCH_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x8014D9B4
// https://decomp.me/scratch/iEZQY // Check to enter grounded or aerial Oil Panic Fill
void ftGameWatch_AbsorbThink_DecideAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 ASID;

    fp->sa.gaw.x2238_panicCharge += fp->AbsorbAttr.x1A48_hitsTaken;
    fp->sa.gaw.x223C_panicDamage += fp->AbsorbAttr.x1A44_damageTaken;
    if ((s32)fp->sa.gaw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL)
    {
        func_800BFFD0(fp, 5, 0);
    }
    if ((s32)fp->xE0_ground_or_air == GA_Ground)
    {
        ASID = AS_GAMEWATCH_SPECIALLW_CATCH;
    }
    else ASID = AS_GAMEWATCH_SPECIALAIRLW_CATCH;
    Fighter_ActionStateChange_800693AC(fighter_gobj, ASID, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
}

inline void ftGameWatch_SpecialLwShoot_ApplyDamage(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 i;

    for (i = 0; i < 4; i++)
    {
        if (fp->x914[i].x0 == 1)
        {
            func_8007ABD0(&fp->x914[i], fp->x2204_ftcmd_var1, fighter_gobj);
        }
    }
}

// 0x8014DA60
// https://decomp.me/scratch/LhPOm // Mr. Game & Watch's grounded Oil Panic Release Animation callback
void ftGameWatch_SpecialLwShoot_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    ftGameWatch_SpecialLwShoot_ApplyDamage(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x8014DAF0 - Mr. Game & Watch's aerial Oil Panic Release Animation callback
void ftGameWatch_SpecialAirLwShoot_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    ftGameWatch_SpecialLwShoot_ApplyDamage(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x8014DB80 - Mr. Game & Watch's grounded Oil Panic Release IASA callback
void ftGameWatch_SpecialLwShoot_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014DB84 - Mr. Game & Watch's aerial Oil Panic Release IASA callback
void ftGameWatch_SpecialAirLwShoot_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014DB88 - Mr. Game & Watch's grounded Oil Panic Release Physics callback
void ftGameWatch_SpecialLwShoot_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x8014DBA8 - Mr. Game & Watch's aerial Oil Panic Release Physics callback
void ftGameWatch_SpecialAirLwShoot_Phys(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

// 0x8014DBC8
// https://decomp.me/scratch/SvQLD // Mr. Game & Watch's grounded Oil Panic Release Collision callback
void ftGameWatch_SpecialLwShoot_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftGameWatch_SpecialLwShoot_GroundToAir(fighter_gobj);
    }
}

// 0x8014DC04 - Mr. Game & Watch's aerial Oil Panic Release Collision callback
void ftGameWatch_SpecialAirLwShoot_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftGameWatch_SpecialAirLwShoot_AirToGround(fighter_gobj);
    }
}

// 0x8014DC40
// https://decomp.me/scratch/f6Yx0 // Mr. Game & Watch's ground -> air Oil Panic Release Action State handler
void ftGameWatch_SpecialLwShoot_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW_SHOOT, FTGAMEWATCH_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
}

// 0x8014DCB4 - Mr. Game & Watch's air -> ground Oil Panic Release Action State handler
void ftGameWatch_SpecialAirLwShoot_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALLW_SHOOT, FTGAMEWATCH_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
}

// 0x8014DD28
// https://decomp.me/scratch/ZWXFH // Enter SpecialLwShoot and calculate damage
void ftGameWatch_SpecialLwShoot_ReleaseOil(HSD_GObj* fighter_gobj)
{
    ftGameWatchAttributes* gawAttrs;
    Fighter* fp;
    void(*cb_Accessory4)(HSD_GObj*);
    f32 panicDamage;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALLW_SHOOT, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    fp = getFighter(fighter_gobj);
    gawAttrs = getFtSpecialAttrs(fp);

    fp->x2204_ftcmd_var1 = (u32)((f32)fp->sa.gaw.x223C_panicDamage * gawAttrs->x78_GAMEWATCH_PANIC_DAMAGE_MUL);
    panicDamage = (f32)fp->x2204_ftcmd_var1 + gawAttrs->x74_GAMEWATCH_PANIC_DAMAGE_ADD;
    fp->x2204_ftcmd_var1 = (u32)panicDamage;
    fp->sa.gaw.x2238_panicCharge = GAMEWATCH_PANIC_EMPTY;
    fp->sa.gaw.x223C_panicDamage = 0;

    ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
}

// 0x8014DE0C - Enter SpecialAirLwShoot and calculate damage
void ftGameWatch_SpecialAirLwShoot_ReleaseOil(HSD_GObj* fighter_gobj)
{
    ftGameWatchAttributes* gawAttrs;
    Fighter* fp;
    void(*cb_Accessory4)(HSD_GObj*);
    f32 panicDamage;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW_SHOOT, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    fp = getFighter(fighter_gobj);
    gawAttrs = getFtSpecialAttrs(fp);

    fp->x2204_ftcmd_var1 = (u32)((f32)fp->sa.gaw.x223C_panicDamage * gawAttrs->x78_GAMEWATCH_PANIC_DAMAGE_MUL);
    panicDamage = (f32)fp->x2204_ftcmd_var1 + gawAttrs->x74_GAMEWATCH_PANIC_DAMAGE_ADD;
    fp->x2204_ftcmd_var1 = (u32)panicDamage;
    fp->sa.gaw.x2238_panicCharge = 0;
    fp->sa.gaw.x223C_panicDamage = 0;

    ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
}
