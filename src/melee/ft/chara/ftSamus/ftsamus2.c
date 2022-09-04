#include <melee/ft/chara/ftSamus/ftsamus.h>

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

void ftSamus_80128944(HSD_GObj* fighter_gobj, f32 farg1, f32 farg2) {
    Fighter* fp = fighter_gobj->user_data; 
    ftSamusAttributes* attr = getFtSpecialAttrs(fp);
    f32 float_result = ftSamus_80128AC8(fighter_gobj, farg1, farg2);
    if (!func_8007B868(fighter_gobj)) {
        switch(fp->x2071_b0_3) {
            case 0:
            case 2:
            case 3:
            case 4:
                if ((fp->x2073 == 0x14) || ((fp->x2071_b5) == 0)) {
                    if (fp->x5F5 == 2) {
                        ftSamus_80128B1C(fighter_gobj, float_result, attr->x0, 1.0f);
                    } else {
                        ftSamus_80128B1C(fighter_gobj, float_result, 0.0f, 1.0f);
                    }
                }
        }
            
    }

}

s32 ftSamus_80128A1C(HSD_GObj* fighter_gobj, s32 arg1, f32 farg1) {
    Fighter* fp = getFighter(fighter_gobj); 
    s32 i; 

    for (i = 0; i < fp->x119E_hurtboxNum; i++) {
        if (func_80008248(arg1, &fp->x11A0_fighterHurtbox[i], func_8007F804(fp), farg1, fp->x34_scale.y, fp->xB0_pos.z)) {
            return 1;
        }
    }
    return 0;
}

f32 ftSamus_80128AC8(HSD_GObj* fighter_gobj, f32 farg1, f32 farg2) {
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* attr = getFtSpecialAttrs(fp);
    f32 value = (fp->xB0_pos.x - farg1) / farg2;
    if (value >= 1.0f) {  
        value = 1.0f; 
    }
    if (value <= -1.0f) {
        value = -1.0f;
    }
    return (-attr->x4 * value) + 1.5707963705062866f;
}

inline void ftSamus_80128B1C_inner(HSD_GObj *fighter_gobj, f32 angle) {
    
    Fighter *fp = getFighter(fighter_gobj);
    struct attr* ftAttr = &fp->x110_attr;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);

    fp = getFighter(fighter_gobj);
    fp->x80_self_vel.x = samus_attr->x8 * cosf(angle);
    fp->x80_self_vel.y = samus_attr->x8 * sinf(angle);
    func_8007D440(fp, ftAttr->x17C_AerialDriftMax * samus_attr->x10);
}

void ftSamus_80128B1C(HSD_GObj *fighter_gobj, f32 angle, f32 arg9, f32 argA)
{
    Fighter *fp;
    Fighter *fighter2;
    fp = fighter2 = getFighterPlus(fighter_gobj);
    func_8007DB58(fighter_gobj);
    ftSamus_80128B1C_inner(fighter_gobj, angle);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2340_stateVar1 = 0;
    if (fp->xE0_ground_or_air == GA_Ground)
    {
        func_8007D5D4(fighter2);
    }
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0, 0, arg9, argA, 0.0f);
    func_8006EBA4(fighter_gobj);
}

void ftSamus_80128C04(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (( fp->x2200_ftcmd_var0) && (!fp->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighter_gobj);
        fp->x2340_stateVar1 = 1;
    }
    if ((!fp->x2200_ftcmd_var0) && (fp->x2340_stateVar1)) {
        ftSamus_8012AF38(fighter_gobj);
        fp->x2340_stateVar1 = 0;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftSamus_80128CA0(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (( fp->x2200_ftcmd_var0) && (!fp->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighter_gobj);
        fp->x2340_stateVar1 = 1;
    }
    if ((!fp->x2200_ftcmd_var0) && (fp->x2340_stateVar1)) {
        ftSamus_8012AF38(fighter_gobj);
        fp->x2340_stateVar1 = 0;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftSamus_80128D3C(HSD_GObj* fighter_gobj) { 
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    if ((fp->x2204_ftcmd_var1) && (fp->input.x624_lstick_y < samus_attr->x14)) {
        fp->x2204_ftcmd_var1 = 0;
        func_800D638C(fighter_gobj);
        return;
    }
    
    if (func_80096540(fighter_gobj)) return; 
    if (func_800D695C(fighter_gobj)) return; 
    if (func_800D6824(fighter_gobj)) return; 
    if (func_800D68C0(fighter_gobj)) return; 
    if (func_800D8990(fighter_gobj)) return; 
    if (func_8008BFC4(fighter_gobj)) return; 
    if (func_8008C830(fighter_gobj)) return; 
    if (func_8008CB44(fighter_gobj)) return; 
    if (func_8008B658(fighter_gobj)) return; 
    if (func_8008B980(fighter_gobj)) return; 
    if (func_8008BB44(fighter_gobj)) return;
    if (func_8008A9F8(fighter_gobj)) return;  
    if (func_80099794(fighter_gobj)) return;  

}

void ftSamus_80128E68(HSD_GObj* fighter_gobj) {
    func_800CCAAC(fighter_gobj);
}

void ftSamus_80128E88(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    struct attr* ftAttr = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0) {
        f32 samus_attr_xC = samus_attr->xC;
        func_8007CADC(
            fp, 
            0.0f, 
            ftAttr->x110_WalkInitialVelocity * samus_attr_xC, 
            ftAttr->x118_WalkMaximumVelocity * samus_attr_xC
        );
        func_8007CB74(fighter_gobj);
    } else {
        func_80084F3C(fighter_gobj);
    }
}

void ftSamus_80128EF8(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    struct attr* ftAttr = &fp->x110_attr;
    func_8007D4B8(fp);
    func_8007D344(
        fp, 
        0.0f, 
        ftAttr->x154_GroundToAirJumpMomentumMultiplier  * samus_attr->x10, 
        ftAttr->x158_JumpHMaxVelocity * samus_attr->x10
    );
}

void ftSamus_80128F60(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    if (fp->x2200_ftcmd_var0) {
        if (!func_80082888(fighter_gobj, &samus_attr->height_attributes)) {
            ftSamus_80129048(fighter_gobj);
        }
    } else if (!func_800827A0(fighter_gobj)) {
        ftSamus_80129048(fighter_gobj);
    }
}

void ftSamus_80128FD4(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    if (fp->x2200_ftcmd_var0) {
        if (func_800824A0(fighter_gobj, &samus_attr->height_attributes)) {
            ftSamus_801290A4(fighter_gobj);
        }
    } else if (func_80081D0C(fighter_gobj)) {
        ftSamus_801290A4(fighter_gobj);
    }
}

void ftSamus_80129048(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0x10, 0, fp->x894_currentAnimFrame, fp->x89C_frameSpeedMul, 0.0f);
}

void ftSamus_801290A4(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x155, 0x10, 0, fp->x894_currentAnimFrame, fp->x89C_frameSpeedMul, 0.0f);
}

s32 ftSamus_80129100(HSD_GObj* fighter_gobj, s32* arg1, s32* arg2) {

    if (fighter_gobj) {
        Fighter* fp = fighter_gobj->user_data;
        ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
        if (!fp->sa.samus.x222C) return -1;
        
        *arg1 = fp->sa.samus.x2230;
        *arg2 = samus_attr->x18;
        return 0;
    }
    return -1;
}

s32 ftSamus_80129158(HSD_GObj* fighter_gobj) {
    
    if (fighter_gobj) {
        Fighter* fp = getFighter(fighter_gobj);
        s32 action_state_index = fp->x10_action_state_index;
        switch (action_state_index) {
            case 0x157:
            case 0x158:
            case 0x159:
            case 0x15A:
            case 0x15B:
            case 0x15C:
                if (fp->x2071_b6) {
                    return 1;
                }
            return 0;
        }
        
        return 1;
    }
    return 1;
}

s32 ftSamus_801291A8(HSD_GObj* fighter_gobj) {
    if (fighter_gobj) {
        Fighter* fp = getFighter(fighter_gobj);
        s32 action_state_index = fp->x10_action_state_index;

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



