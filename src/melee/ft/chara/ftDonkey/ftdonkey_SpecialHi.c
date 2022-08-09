#include "ftdonkey.h"

void ftDonkey_SetCallbacks_SpecialHi(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->cb.x21DC_callback_OnTakeDamage = &ftDonkey_8010D774;
    fighter->cb.x21E4_callback_OnDeath2 = &ftDonkey_8010D774;
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_SpecialHi_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17D, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_SetCallbacks_SpecialHi(fighterObj);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    func_8007CC78(fighter, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fighter->x80_self_vel.x = fighter->xEC_ground_vel;
    fighter->x80_self_vel.y = 0.0f;
    fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    func_8006EBA4(fighterObj);
    ef_Spawn(0x4CA, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj);
}

void ftDonkey_SpecialAirHi_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17E, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_SetCallbacks_SpecialHi(fighterObj);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    func_8007D440(fighter, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fighter->x80_self_vel.y = donkey_attr->SpecialHi.x4C_AERIAL_VERTICAL_VELOCITY;
    fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    func_8006EBA4(fighterObj);
    ef_Spawn(0x4CA, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj);
}

void ftDonkey_8010FCD4(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftDonkey_8010FD10(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr = fighter->x2D4_specialAttributes;
    
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8007D60C(fighter);
        if (donkey_attr->SpecialHi.x64_LANDING_LAG == 0.0f) {
            func_800CC730(fighterObj); 
        } else {
            func_80096900(fighterObj, 1, 0, 1, 1.0f, donkey_attr->SpecialHi.x64_LANDING_LAG);
        }
    }
}

void ftDonkey_8010FD9C(HSD_GObj* fighterObj) {}

void ftDonkey_8010FDA0(HSD_GObj* fighterObj) {}

void ftDonkey_8010FDA4(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    func_8007CADC(fighter, 0.0f, donkey_attr->SpecialHi.x5C_GROUNDED_MOBILITY, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    func_8007CB74(fighterObj);
}

void ftDonkey_8010FDEC(HSD_GObj* fighterObj) {
    s32 unused[2];  /// get inline break the regalloc, this seems cleanest
    Fighter* fighter = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr = fighter->x2D4_specialAttributes;
    f32 gravity_scalar;

    if (fighter->x2200_ftcmd_var0) {
        gravity_scalar = 1.0f;
    } else {
        gravity_scalar = donkey_attr->SpecialHi.x50_AERIAL_GRAVITY;
    }
    func_8007D494(fighter, gravity_scalar * fighter->x110_attr.x16C_Gravity, fighter->x110_attr.x170_TerminalVelocity);
    func_8007D344(fighter, 0.0f, donkey_attr->SpecialHi.x60_AERIAL_MOBILITY, donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
}

void ftDonkey_8010FE60(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    if (!func_80082708(fighterObj)) {
        func_8007D60C(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x17E, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialHi(fighterObj);
        func_8007D440(fighter, donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
    } 
}

void ftDonkey_8010FF14(HSD_GObj* fighterObj) {
    s32 unused[2]; /// get inline break the regalloc, this seems cleanest
    Fighter* fighter = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    
    if (fighter->x80_self_vel.y >= 0.0f) {
        if (func_80081D0C(fighterObj)) {
            func_8007D7FC(fighter);
            Fighter_ActionStateChange_800693AC(fighterObj, 0x17D, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
            ftDonkey_SetCallbacks_SpecialHi(fighterObj);
            func_8007CC78(fighter, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        }
    } else {
        if (EnvColl_CheckGroundAndLedge(fighterObj, 0)) {
            func_8007D7FC(fighter);
            Fighter_ActionStateChange_800693AC(fighterObj, 0x17D, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
            ftDonkey_SetCallbacks_SpecialHi(fighterObj);
            func_8007CC78(fighter, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        } else if (func_80081298(fighterObj)) {
            func_80081370(fighterObj);
        }
    }
}

void ftDonkey_DestroyAllEffects_SpecialHi(HSD_GObj* fighterObj) {
    efLib_DestroyAll(fighterObj);
}