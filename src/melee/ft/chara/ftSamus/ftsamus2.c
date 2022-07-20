#include "ftsamus.h"

extern s32 func_8008A9F8(HSD_GObj*); 
extern s32 func_8008B658(HSD_GObj*); 
extern s32 func_8008B980(HSD_GObj*); 
extern s32 func_8008BB44(HSD_GObj*); 
extern s32 func_8008BFC4(HSD_GObj*); 
extern s32 func_8008C830(HSD_GObj*); 
extern s32 func_8008CB44(HSD_GObj*); 
extern s32 func_80096540(HSD_GObj*); 
extern s32 func_80099794(HSD_GObj*);
extern void func_800D638C(HSD_GObj*);
extern s32 func_800D6824(HSD_GObj*); 
extern s32 func_800D68C0(HSD_GObj*); 
extern s32 func_800D695C(HSD_GObj*); 
extern s32 func_800D8990(HSD_GObj*); 

void ftSamus_80128944(HSD_GObj* fighterObj, f32 farg1, f32 farg2) {
    Fighter* fighter = fighterObj->user_data; 
    ftSamusAttributes* attr = getFtSpecialAttrs(fighter);
    f32 float_result = ftSamus_80128AC8(fighterObj, farg1, farg2);
    if (!func_8007B868(fighterObj)) {
        switch(fighter->x2071_b0_3) {
            case 0:
            case 2:
            case 3:
            case 4:
                if ((fighter->x2073 == 0x14) || ((fighter->x2071_b5) == 0)) {
                    if (fighter->x5F5 == 2) {
                        ftSamus_80128B1C(fighterObj, float_result, attr->x0, 1.0f);
                    } else {
                        ftSamus_80128B1C(fighterObj, float_result, 0.0f, 1.0f);
                    }
                }
        }
            
    }

}

s32 ftSamus_80128A1C(HSD_GObj* fighterObj, s32 arg1, f32 farg1) {
    Fighter* fighter = getFighter(fighterObj); 
    s32 i; 

    for (i = 0; i < fighter->x119E_hurtboxNum; i++) {
        if (func_80008248(arg1, &fighter->x11A0_fighterHurtbox[i], func_8007F804(fighter), farg1, fighter->x34_scale.y, fighter->xB0_pos.z)) {
            return 1;
        }
    }
    return 0;
}

f32 ftSamus_80128AC8(HSD_GObj* fighterObj, f32 farg1, f32 farg2) {
    Fighter* fighter = getFighter(fighterObj);
    ftSamusAttributes* attr = getFtSpecialAttrs(fighter);
    f32 value = (fighter->xB0_pos.x - farg1) / farg2;
    if (value >= 1.0f) {  
        value = 1.0f; 
    }
    if (value <= -1.0f) {
        value = -1.0f;
    }
    return (-attr->x4 * value) + 1.5707963705062866f;
}

inline void ftSamus_80128B1C_inner(HSD_GObj *fighterObj, f32 angle) {
    
    Fighter *fighter = getFighter(fighterObj);
    struct attr* ftAttr = &fighter->x110_attr;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);

    fighter = getFighter(fighterObj);
    fighter->x80_self_vel.x = samus_attr->x8 * cosf(angle);
    fighter->x80_self_vel.y = samus_attr->x8 * sinf(angle);
    func_8007D440(fighter, ftAttr->x17C_AerialDriftMax * samus_attr->x10);
}

void ftSamus_80128B1C(HSD_GObj *fighterObj, f32 angle, f32 arg9, f32 argA)
{
    Fighter *fighter;
    Fighter *fighter2;
    fighter = fighter2 = getFighterPlus(fighterObj);
    func_8007DB58(fighterObj);
    ftSamus_80128B1C_inner(fighterObj, angle);
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2340_stateVar1 = 0;
    if (fighter->xE0_ground_or_air == GA_Ground)
    {
        func_8007D5D4(fighter2);
    }
    Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0, 0, arg9, argA, 0.0f);
    func_8006EBA4(fighterObj);
}

void ftSamus_80128C04(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (( fighter->x2200_ftcmd_var0) && (!fighter->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighterObj);
        fighter->x2340_stateVar1 = 1;
    }
    if ((!fighter->x2200_ftcmd_var0) && (fighter->x2340_stateVar1)) {
        ftSamus_8012AF38(fighterObj);
        fighter->x2340_stateVar1 = 0;
    }
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftSamus_80128CA0(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (( fighter->x2200_ftcmd_var0) && (!fighter->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighterObj);
        fighter->x2340_stateVar1 = 1;
    }
    if ((!fighter->x2200_ftcmd_var0) && (fighter->x2340_stateVar1)) {
        ftSamus_8012AF38(fighterObj);
        fighter->x2340_stateVar1 = 0;
    }
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftSamus_80128D3C(HSD_GObj* fighterObj) { 
    Fighter* fighter = getFighterPlus(fighterObj);
    ftSamusAttributes* samus_attr = fighter->x2D4_specialAttributes;
    if ((fighter->x2204_ftcmd_var1) && (fighter->input.x624_lstick_y < samus_attr->x14)) {
        fighter->x2204_ftcmd_var1 = 0;
        func_800D638C(fighterObj);
        return;
    }
    
    if (func_80096540(fighterObj)) return; 
    if (func_800D695C(fighterObj)) return; 
    if (func_800D6824(fighterObj)) return; 
    if (func_800D68C0(fighterObj)) return; 
    if (func_800D8990(fighterObj)) return; 
    if (func_8008BFC4(fighterObj)) return; 
    if (func_8008C830(fighterObj)) return; 
    if (func_8008CB44(fighterObj)) return; 
    if (func_8008B658(fighterObj)) return; 
    if (func_8008B980(fighterObj)) return; 
    if (func_8008BB44(fighterObj)) return;
    if (func_8008A9F8(fighterObj)) return;  
    if (func_80099794(fighterObj)) return;  

}

void ftSamus_80128E68(HSD_GObj* fighterObj) {
    func_800CCAAC(fighterObj);
}

void ftSamus_80128E88(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);
    struct attr* ftAttr = &fighter->x110_attr;

    if (fighter->x2200_ftcmd_var0) {
        f32 samus_attr_xC = samus_attr->xC;
        func_8007CADC(
            fighter, 
            0.0f, 
            ftAttr->x110_WalkInitialVelocity * samus_attr_xC, 
            ftAttr->x118_WalkMaximumVelocity * samus_attr_xC
        );
        func_8007CB74(fighterObj);
    } else {
        func_80084F3C(fighterObj);
    }
}

void ftSamus_80128EF8(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);
    struct attr* ftAttr = &fighter->x110_attr;
    func_8007D4B8(fighter);
    func_8007D344(
        fighter, 
        0.0f, 
        ftAttr->x154_GroundToAirJumpMomentumMultiplier  * samus_attr->x10, 
        ftAttr->x158_JumpHMaxVelocity * samus_attr->x10
    );
}

void ftSamus_80128F60(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    ftSamusAttributes* samus_attr = fighter->x2D4_specialAttributes;
    if (fighter->x2200_ftcmd_var0) {
        if (!func_80082888(fighterObj, &samus_attr->height_attributes)) {
            ftSamus_80129048(fighterObj);
        }
    } else if (!func_800827A0(fighterObj)) {
        ftSamus_80129048(fighterObj);
    }
}

void ftSamus_80128FD4(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    ftSamusAttributes* samus_attr = fighter->x2D4_specialAttributes;
    if (fighter->x2200_ftcmd_var0) {
        if (func_800824A0(fighterObj, &samus_attr->height_attributes)) {
            ftSamus_801290A4(fighterObj);
        }
    } else if (func_80081D0C(fighterObj)) {
        ftSamus_801290A4(fighterObj);
    }
}

void ftSamus_80129048(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0x10, 0, fighter->x894_currentAnimFrame, fighter->x89C_frameSpeedMul, 0.0f);
}

void ftSamus_801290A4(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0x10, 0, fighter->x894_currentAnimFrame, fighter->x89C_frameSpeedMul, 0.0f);
}

s32 ftSamus_80129100(HSD_GObj* fighterObj, s32* arg1, s32* arg2) {

    if (fighterObj) {
        Fighter* fighter = fighterObj->user_data;
        ftSamusAttributes* samus_attr = getFtSpecialAttrs(fighter);
        if (!fighter->sa.samus.x222C) return -1;
        
        *arg1 = fighter->sa.samus.x2230;
        *arg2 = samus_attr->x18;
        return 0;
    }
    return -1;
}

s32 ftSamus_80129158(HSD_GObj* fighterObj) {
    
    if (fighterObj) {
        Fighter* fighter = getFighter(fighterObj);
        s32 action_state_index = fighter->x10_action_state_index;
        switch (action_state_index) {
            case 0x157:
            case 0x158:
            case 0x159:
            case 0x15A:
            case 0x15B:
            case 0x15C:
                if (fighter->x2071_b6) {
                    return 1;
                }
            return 0;
        }
        
        return 1;
    }
    return 1;
}

s32 ftSamus_801291A8(HSD_GObj* fighterObj) {
    if (fighterObj) {
        Fighter* fighter = getFighter(fighterObj);
        s32 action_state_index = fighter->x10_action_state_index;

        switch (action_state_index) {
            case 0x157:
            case 0x158:
            case 0x15A:
            case 0x15B:
            case 0x15C:
                return 0;
        }
        
        return 1;
    }
    return 1;
}



