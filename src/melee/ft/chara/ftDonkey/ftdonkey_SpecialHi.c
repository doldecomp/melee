#include <melee/ft/chara/ftDonkey/ftdonkey.h>

void ftDonkey_SetCallbacks_SpecialHi(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    fp->cb.x21DC_callback_OnTakeDamage = &ftDonkey_8010D774;
    fp->cb.x21E4_callback_OnDeath2 = &ftDonkey_8010D774;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_SpecialHi_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17D, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_SetCallbacks_SpecialHi(fighter_gobj);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    func_8007CC78(fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fp->x80_self_vel.x = fp->xEC_ground_vel;
    fp->x80_self_vel.y = 0.0f;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    func_8006EBA4(fighter_gobj);
    ef_Spawn(0x4CA, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj);
}

void ftDonkey_SpecialAirHi_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17E, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_SetCallbacks_SpecialHi(fighter_gobj);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    func_8007D440(fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fp->x80_self_vel.y = donkey_attr->SpecialHi.x4C_AERIAL_VERTICAL_VELOCITY;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    func_8006EBA4(fighter_gobj);
    ef_Spawn(0x4CA, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj);
}

void ftDonkey_8010FCD4(HSD_GObj* fighter_gobj) {
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftDonkey_8010FD10(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8007D60C(fp);
        if (donkey_attr->SpecialHi.x64_LANDING_LAG == 0.0f) {
            func_800CC730(fighter_gobj); 
        } else {
            func_80096900(fighter_gobj, 1, 0, 1, 1.0f, donkey_attr->SpecialHi.x64_LANDING_LAG);
        }
    }
}

void ftDonkey_8010FD9C(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010FDA0(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010FDA4(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    func_8007CADC(fp, 0.0f, donkey_attr->SpecialHi.x5C_GROUNDED_MOBILITY, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    func_8007CB74(fighter_gobj);
}

void ftDonkey_8010FDEC(HSD_GObj* fighter_gobj) {
    s32 unused[2];  /// get inline break the regalloc, this seems cleanest
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    f32 gravity_scalar;

    if (fp->x2200_ftcmd_var0) {
        gravity_scalar = 1.0f;
    } else {
        gravity_scalar = donkey_attr->SpecialHi.x50_AERIAL_GRAVITY;
    }
    func_8007D494(fp, gravity_scalar * fp->x110_attr.x16C_Gravity, fp->x110_attr.x170_TerminalVelocity);
    func_8007D344(fp, 0.0f, donkey_attr->SpecialHi.x60_AERIAL_MOBILITY, donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
}

void ftDonkey_8010FE60(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    if (!func_80082708(fighter_gobj)) {
        func_8007D60C(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17E, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialHi(fighter_gobj);
        func_8007D440(fp, donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
    } 
}

void ftDonkey_8010FF14(HSD_GObj* fighter_gobj) {
    s32 unused[2]; /// get inline break the regalloc, this seems cleanest
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    
    if (fp->x80_self_vel.y >= 0.0f) {
        if (func_80081D0C(fighter_gobj)) {
            func_8007D7FC(fp);
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17D, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
            ftDonkey_SetCallbacks_SpecialHi(fighter_gobj);
            func_8007CC78(fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        }
    } else {
        if (EnvColl_CheckGroundAndLedge(fighter_gobj, 0)) {
            func_8007D7FC(fp);
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17D, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
            ftDonkey_SetCallbacks_SpecialHi(fighter_gobj);
            func_8007CC78(fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        } else if (func_80081298(fighter_gobj)) {
            func_80081370(fighter_gobj);
        }
    }
}

void ftDonkey_DestroyAllEffects_SpecialHi(HSD_GObj* fighter_gobj) {
    efLib_DestroyAll(fighter_gobj);
}
