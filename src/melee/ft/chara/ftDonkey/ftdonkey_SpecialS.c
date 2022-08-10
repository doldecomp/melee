#include "ftdonkey.h"

void ftDonkey_SpecialS_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17B, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
    Fighter_UnsetCmdVar0(fighterObj);
    fighter->cb.x21BC_callback_Accessory4 = &ftDonkey_8010E0CC;
}

void ftDonkey_SpecialAirS_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = fighter->x2D4_specialAttributes;
    fighter->x80_self_vel.x /= donkey_attr->SpecialS.x3C_MIN_STICK_X_MOMENTUM;
    fighter->x80_self_vel.y = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17C, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
    Fighter_UnsetCmdVar0(fighterObj);
    fighter->cb.x21BC_callback_Accessory4 = &ftDonkey_8010E148;
}

void ftDonkey_8010E2BC(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftDonkey_8010E2F8(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftDonkey_8010E334(HSD_GObj* fighterObj) {}

void ftDonkey_8010E338(HSD_GObj* fighterObj) {}

void ftDonkey_8010E33C(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010E35C(HSD_GObj* fighterObj)
{
    Fighter *fighter = getFighter(fighterObj);
    attr *ft_attr = &fighter->x110_attr;
    ftDonkeyAttributes *donkey_attr = getFtSpecialAttrs(fighter);
    if (fighter->x2200_ftcmd_var0) {
        func_8007D494(fighter, donkey_attr->SpecialS.x44_AERIAL_GRAVITY, ft_attr->x170_TerminalVelocity);
    }
    func_8007CE94(fighter, donkey_attr->SpecialS.x40_MOMENTUM_TRANSITION_MODIFIER);
    if (fighter->x2200_ftcmd_var0 != 0){
        /// unused or removed code here
    }
}

void ftDonkey_8010E3BC(HSD_GObj* fighterObj) {
    Fighter *fighter = getFighter(fighterObj);
    if (fighter->x2200_ftcmd_var0) {
        if (!func_800827A0(fighterObj)) {
            ftDonkey_8010E464(fighterObj);
        }
    } else if (!func_80082708(fighterObj)) {
        ftDonkey_8010E464(fighterObj);
    }
}

void ftDonkey_8010E428(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj)) {
        ftDonkey_8010E4EC(fighterObj);
    }
}

void ftDonkey_8010E464(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17C, 0x0C4C508A, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    if (fighter->x2219_flag.bits.b0 == 1) {
        fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}

void ftDonkey_8010E4EC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17B, 0x0C4C508A, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    if (fighter->x2219_flag.bits.b0 == 1) {
        fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}
