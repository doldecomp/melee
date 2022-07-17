#include "ftdonkey.h"

/// TODO remove these externs
extern void ftDonkey_8010FAD0(HSD_GObj* fighterObj);  /// exists later on in ftdonkey, not yet matched
extern f32 lbl_804D95E0;
extern f32 lbl_804D95E4;

inline void ftDonkey_SpecialN_StartAction_inner(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->cb.x21DC_callback_OnTakeDamage = &ftDonkey_8010D774;
    fighter->cb.x21E4_callback_OnDeath2 = &ftDonkey_8010D774;
    fighter->cb.x21F0_callback = &ftDonkey_8010FAD0;
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_SpecialN_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    if ( fighter->sa.dk.x222C == donkey_attr->x2C) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x175, 0, NULL, lbl_804D95E0, lbl_804D95E4, lbl_804D95E0);
        fighter->x2348_stateVar3 = 1;
        fighter->x234C_stateVar4 = fighter->sa.dk.x222C;
        fighter->sa.dk.x222C = 0;
    } else {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x171, 0, NULL, lbl_804D95E0, lbl_804D95E4, lbl_804D95E0);
        fighter->x2348_stateVar3 = 0;
        fighter->x234C_stateVar4 = 0;
    }
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = 0;
    fighter->x2344_stateVar2 = 0;
    fighter->x2354_stateVar6 = -1; 
    fighter->x2350_stateVar5_s32 = -1;
    func_8007D7FC(fighter);
    fighter->x80_self_vel.y = lbl_804D95E0;
    ftDonkey_SpecialN_StartAction_inner(fighterObj);
    func_8006EBA4(fighterObj);
}

void ftDonkey_SpecialAirN_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    if ( fighter->sa.dk.x222C == donkey_attr->x2C) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x17A, 0, NULL, lbl_804D95E0, lbl_804D95E4, lbl_804D95E0);
        fighter->x2348_stateVar3 = 1;
        fighter->x234C_stateVar4 = fighter->sa.dk.x222C;
        fighter->sa.dk.x222C = 0;
    } else {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x176, 0, NULL, lbl_804D95E0, lbl_804D95E4, lbl_804D95E0);
        fighter->x2348_stateVar3 = 0;
        fighter->x234C_stateVar4 = 0;
    }
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = 0;
    fighter->x2344_stateVar2 = 0;
    fighter->x2354_stateVar6 = -1; 
    fighter->x2350_stateVar5_s32 = -1;

    ftDonkey_SpecialN_StartAction_inner(fighterObj);
    func_8006EBA4(fighterObj);
}