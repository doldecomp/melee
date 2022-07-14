#include "ftsamus.h"

void ftSamus_8012ADF0(HSD_GObj* fighterObj) {
    Vec vec;
    BOOL bool1;
    Fighter *fighter = getFighterPlus(fighterObj);
    ftSamusAttributes* samus_attr = fighter->x2D4_specialAttributes;
    
    if (fighter->x2210_ThrowFlags.b0) {
        fighter->x2210_ThrowFlags.b0 = 0;
        bool1 = 1;
    } else {
        bool1 = 0;
    }
    if (bool1) {
        f32 vec_x; 
        func_8000B1CC(fighter->x5E8_fighterBones[0].x0_jobj, NULL, &vec);
        vec_x = samus_attr->x74_vec.x;
        vec.x += (vec_x * fighter->x2C_facing_direction);
        vec.y += samus_attr->x74_vec.y;
        vec.z += samus_attr->x74_vec.z;
        func_802B4AC8(fighterObj, &vec, fighter->x2C_facing_direction, vec_x);
        fighter->cb.x21BC_callback_Accessory4 = 0;
    }
}


void ftSamus_8012AEBC(HSD_GObj* fighterObj) {
    struct UNK_SAMUS_S2 unk_struct;
    Fighter* fighter = getFighter(fighterObj);
    func_8007B0C0(fighterObj, 2);
    
    
    unk_struct.intvec.x = 2;
    unk_struct.intvec.y = 1;
    unk_struct.intvec.z = 0;
    unk_struct.vec1.x = unk_struct.vec1.y = unk_struct.vec1.z = 0.0f; 
    unk_struct.vec2.x = unk_struct.vec2.y = unk_struct.vec2.z = 0.0f;
    unk_struct.single_float = 3.0f; 
    func_8007B5AC(fighter, &fighter->x11A0_fighterHurtbox[0], &unk_struct); 
}

void ftSamus_8012AF38(HSD_GObj* fighterObj) {
    func_8007B0C0(fighterObj, 0);
}

void ftSamus_SpecialLw_StartAction_inner(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2210_ThrowFlags.b0 = 0;
    fighter->x2340_stateVar1 = 0;
    if (fighter->x894_currentAnimFrame == 3.0f) {
        fighter->x2204_ftcmd_var1 = 1;
    }
    fighter->cb.x21BC_callback_Accessory4 = &ftSamus_8012ADF0;
}

void ftSamus_SpecialLw_StartAction(HSD_GObj* fighterObj) {
    Fighter *fighter = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = fighter->x2D4_specialAttributes;
    
    fighter->xEC_ground_vel *= samus_attr->x6C;
    if (fighter->x10_action_state_index == 0x28) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x163, 0, NULL, 3.0f, 1.0f, 0.0f);
        ftSamus_SpecialLw_StartAction_inner(fighterObj);
        fighter->x2204_ftcmd_var1 = 2;
        ftSamus_8012B5F0(fighterObj);
        return;
    }
    Fighter_ActionStateChange_800693AC(fighterObj, 0x163, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
    ftSamus_SpecialLw_StartAction_inner(fighterObj);
}

void ftSamus_SpecialAirLw_StartAction(HSD_GObj* fighterObj) {
    Fighter *fighter = getFighterPlus(fighterObj);
    ftSamusAttributes* samus_attr = fighter->x2D4_specialAttributes;
    
    fighter->x80_self_vel.x *= samus_attr->x70;
    fighter->x80_self_vel.y = samus_attr->x58;

    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
    ftSamus_SpecialLw_StartAction_inner(fighterObj);
}

///// what the heck is up with the stack in this function... can't get rid of unused params
void ftSamus_8012B150(HSD_GObj* fighterObj, s32 a, s32 b, s32 c, s32 d) {

    Fighter* fighter = fighterObj->user_data;

    if (fighter->x2204_ftcmd_var1 == 1) {
        fighter->x2204_ftcmd_var1 = 2;
        ftSamus_8012B5F0(fighterObj);
        return; 
    }
    if ((fighter->x2200_ftcmd_var0) && (!fighter->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighterObj);
        fighter->x2340_stateVar1 = 1;
    }
    if ((!fighter->x2200_ftcmd_var0) && ( fighter->x2340_stateVar1)) {
        func_8007B0C0(fighterObj, 0);
        fighter->x2340_stateVar1 = 0;
    }
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftSamus_8012B264(HSD_GObj* fighterObj, s32 a, s32 b) {

    Fighter* fighter = getFighterPlus(fighterObj);

    if ((fighter->x2200_ftcmd_var0) && (!fighter->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighterObj);
        fighter->x2340_stateVar1 = 1;
    }
    if ((!fighter->x2200_ftcmd_var0) && ( fighter->x2340_stateVar1)) {
        func_8007B0C0(fighterObj, 0);
        fighter->x2340_stateVar1 = 0;
    }
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftSamus_8012B358(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftSamusAttributes* samus_attr = fighter->x2D4_specialAttributes;
    if ((fighter->x2208_ftcmd_var2) && (fighter->input.x624_lstick_y < samus_attr->x80)) {
        fighter->x2208_ftcmd_var2 = 0;
        func_800D638C(fighterObj);
    }
}

void ftSamus_8012B3A4(HSD_GObj* fighterObj) {}

void ftSamus_8012B3A8(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);
    attr* ft_attr = &fighter->x110_attr;
 
    if (fighter->x2200_ftcmd_var0) {
        func_8007CADC(
            fighter, 
            0.0f, 
            ft_attr->x110_WalkInitialVelocity * samus_attr->x64, 
            ft_attr->x118_WalkMaximumVelocity * samus_attr->x5C
        );
        func_8007CB74(fighterObj);
    } else {
        func_80084F3C(fighterObj);
    }
}

void ftSamus_8012B41C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);
    attr* ft_attr = &fighter->x110_attr;
 
    func_8007D4B8(fighter);
    func_8007D3A8(
        fighter, 
        0.0f, 
        ft_attr->x174_AerialDriftStickMult * samus_attr->x68, 
        ft_attr->x17C_AerialDriftMax * samus_attr->x60
    );
}

void ftSamus_8012B488(HSD_GObj* fighterObj) {
    Fighter *fighter = fighterObj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);
    
    if (fighter->x2200_ftcmd_var0) {
        if (!func_80082888(fighterObj, &samus_attr->height_attributes)) {
            ftSamus_8012B570(fighterObj);
        }
    } else if (!func_800827A0(fighterObj)) {
        ftSamus_8012B570(fighterObj);
    }
}

void ftSamus_8012B4FC(HSD_GObj* fighterObj) {
    Fighter *fighter = fighterObj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);
    
    if (fighter->x2200_ftcmd_var0) {
        if (func_800824A0(fighterObj, &samus_attr->height_attributes)) {
            ftSamus_8012B668(fighterObj);
        }
    } else if (func_80081D0C(fighterObj)) {
        ftSamus_8012B668(fighterObj);
    }
}

void ftSamus_UnkSetStateAndCb(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    fighter->x2204_ftcmd_var1 = 2;
    fighter->x2340_stateVar1 = 0;
    fighter->cb.x21BC_callback_Accessory4 = &ftSamus_8012ADF0;
}

void ftSamus_8012B570(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0x0C4C509C, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    ftSamus_UnkSetStateAndCb(fighterObj);
}

void ftSamus_8012B5F0(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);
    fighter->x80_self_vel.y = samus_attr->x54;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0x0C4C509C, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    fighter->cb.x21BC_callback_Accessory4 = ftSamus_8012ADF0;
}

void ftSamus_8012B668(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x163, 0x0C4C509C, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    ftSamus_UnkSetStateAndCb(fighterObj);
}