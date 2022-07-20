#include "ftdonkey.h"

//// TODO remove these when moved over enough functions and floats in this file
extern f32 lbl_804D95E8;
extern f32 lbl_804D95EC;

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
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17D, 0, NULL, lbl_804D95E8, lbl_804D95EC, lbl_804D95E8);
    ftDonkey_SetCallbacks_SpecialHi(fighterObj);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    func_8007CC78(fighter, donkey_attr->x54);
    fighter->x80_self_vel.x = fighter->xEC_ground_vel;
    fighter->x80_self_vel.y = lbl_804D95E8;
    fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    func_8006EBA4(fighterObj);
    ef_Spawn(0x4CA, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj);
}

void ftDonkey_SpecialAirHi_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17E, 0, NULL, lbl_804D95E8, lbl_804D95EC, lbl_804D95E8);
    ftDonkey_SetCallbacks_SpecialHi(fighterObj);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    func_8007D440(fighter, donkey_attr->x54);
    fighter->x80_self_vel.y = donkey_attr->x4C;
    fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    func_8006EBA4(fighterObj);
    ef_Spawn(0x4CA, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj);
}
