#include "ftsamus.h"


///// TODO remove these
extern f32 lbl_804D99F0;
extern f32 lbl_804D99F4;

void ftSamus_SpecialHi_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x161, 0, NULL, lbl_804D99F0, lbl_804D99F4, lbl_804D99F0);
    ftSamus_updateDamageDeathCBs(fighterObj);
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8007D7FC(fighter);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = 0;
    func_8006EBA4(fighterObj);
    ef_Spawn(0x482, fighterObj, fighter->x5E8_fighterBones[3].x0_jobj);
    fighter->sa.samus.x2244 = 1;
}

void ftSamus_SpecialAirHi_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = fighter->x2D4_specialAttributes; 
    Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 0, NULL, lbl_804D99F0, lbl_804D99F4, lbl_804D99F0);
    ftSamus_updateDamageDeathCBs(fighterObj);
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8007D60C(fighter);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = 0;
    fighter->x80_self_vel.y = samus_attr->x44;
    func_8007D440(fighter, samus_attr->x40);
    func_8006EBA4(fighterObj);
    ef_Spawn(0x482, fighterObj, fighter->x5E8_fighterBones[3].x0_jobj);
    fighter->sa.samus.x2244 = 1;
}


void ftSamus_DestroyAllUnsetx2444(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    efLib_DestroyAll(fighterObj);
    fighter->sa.samus.x2244 = 0;
}

void ftSamus_8012A81C(HSD_GObj *fighterObj)
{
    Fighter *fighter = fighterObj->user_data;
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;
    samus_attr = samus_attr2 = getFtSpecialAttrs(fighter); 
    if (!ftAnim_IsFramesRemaining(fighterObj))
    {
        Fighter *fighter2 = fighter;
        ftSamus_DestroyAllUnsetx2444(fighterObj);
        func_8007D60C(fighter2);
        if (lbl_804D99F0 == samus_attr->x50)
        {
            func_800CC730(fighterObj);
            return;
        }
        func_80096900(fighterObj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}


void ftSamus_8012A8C4(HSD_GObj* fighterObj) {
 
    Fighter *fighter = fighterObj->user_data;
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;
    samus_attr = samus_attr2 = getFtSpecialAttrs(fighter); 
 
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        Fighter* fighter2 = fighter;
        ftSamus_DestroyAllUnsetx2444(fighterObj);
        func_8007D60C(fighter2);
        if (lbl_804D99F0 == samus_attr->x50) {
            func_800CC730(fighterObj);
            return;
        }
        func_80096900(fighterObj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}
