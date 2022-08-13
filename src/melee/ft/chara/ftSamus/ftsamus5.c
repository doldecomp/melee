#include <ftsamus.h>

void ftSamus_SpecialHi_StartAction(HSD_GObj* fighterObj) {
    Fighter* fp = getFighterPlus(fighterObj);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x161, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftSamus_updateDamageDeathCBs(fighterObj);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8007D7FC(fp);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2340_stateVar1 = 0;
    func_8006EBA4(fighterObj);
    ef_Spawn(0x482, fighterObj, fp->x5E8_fighterBones[3].x0_jobj);
    fp->sa.samus.x2244 = 1;
}

void ftSamus_SpecialAirHi_StartAction(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes; 
    Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftSamus_updateDamageDeathCBs(fighterObj);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8007D60C(fp);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2340_stateVar1 = 0;
    fp->x80_self_vel.y = samus_attr->x44;
    func_8007D440(fp, samus_attr->x40);
    func_8006EBA4(fighterObj);
    ef_Spawn(0x482, fighterObj, fp->x5E8_fighterBones[3].x0_jobj);
    fp->sa.samus.x2244 = 1;
}


void ftSamus_DestroyAllUnsetx2444(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    efLib_DestroyAll(fighterObj);
    fp->sa.samus.x2244 = 0;
}

void ftSamus_8012A81C(HSD_GObj *fighterObj)
{
    Fighter *fp = fighterObj->user_data;
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;
    samus_attr = samus_attr2 = getFtSpecialAttrs(fp); 
    if (!ftAnim_IsFramesRemaining(fighterObj))
    {
        Fighter *fighter2 = fp;
        ftSamus_DestroyAllUnsetx2444(fighterObj);
        func_8007D60C(fighter2);
        if (samus_attr->x50 == 0.0f)
        {
            func_800CC730(fighterObj);
            return;
        }
        func_80096900(fighterObj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}


void ftSamus_8012A8C4(HSD_GObj* fighterObj) {
 
    Fighter *fp = fighterObj->user_data;
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;
    samus_attr = samus_attr2 = getFtSpecialAttrs(fp); 
 
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        Fighter* fighter2 = fp;
        ftSamus_DestroyAllUnsetx2444(fighterObj);
        func_8007D60C(fighter2);
        if (samus_attr->x50 == 0.0f) {
            func_800CC730(fighterObj);
            return;
        }
        func_80096900(fighterObj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}

void ftSamus_8012A96C(HSD_GObj* fighterObj) {
    f32 mag;
    f32 lstick_x;
    Fighter* fp = fighterObj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    if ((!fp->x2204_ftcmd_var1) && (!fp->x2340_stateVar1)) {
        if ((lstick_x = fp->input.x620_lstick_x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        if (mag > samus_attr->x4C) {
            if (((fp->x2C_facing_direction == 1.0f ) && (lstick_x < 0.0f)) 
                || ((fp->x2C_facing_direction == -1.0f) && (lstick_x > 0.0f))) {
                fp->x2204_ftcmd_var1 = 1;
                fp->x2340_stateVar1 = 1;
                func_8007D9FC(fp);
                func_80075AF0(fp, 0, M_PI_2 * fp->x2C_facing_direction);
            }
        }
    }
}

void ftSamus_8012AA3C(HSD_GObj* fighterObj) {
    f32 mag;
    f32 lstick_x;
    Fighter* fp = fighterObj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    if ((!fp->x2204_ftcmd_var1) && (!fp->x2340_stateVar1)) {
        if ((lstick_x = fp->input.x620_lstick_x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        if (mag > samus_attr->x4C) {
            if (((fp->x2C_facing_direction == 1.0f ) && (lstick_x < 0.0f)) 
                || ((fp->x2C_facing_direction == -1.0f) && (lstick_x > 0.0f))) {
                fp->x2204_ftcmd_var1 = 1;
                fp->x2340_stateVar1 = 1;
                func_8007D9FC(fp);
                func_80075AF0(fp, 0, M_PI_2 * fp->x2C_facing_direction);
            }
        }
    }
}

void ftSamus_8012AB0C(HSD_GObj* fighterObj) {
    Fighter *fp = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    
    if (fp->x2200_ftcmd_var0) {
        func_8007D60C(fp);
        fp->x2200_ftcmd_var0 = 0;
        fp->x80_self_vel.x = samus_attr->x38 * fp->x2C_facing_direction;
    }
    if (fp->xE0_ground_or_air == 1) {
        func_800851C0(fighterObj);
        func_8007D344(fp, 0.0f, samus_attr->x3C, samus_attr->x40);
        func_8007D268(fp);
        return;
    }
    func_80084F3C(fighterObj);
}

void ftSamus_8012ABB4(HSD_GObj* fighterObj) {
    Fighter *fp = fighterObj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    func_80084DB0(fighterObj);
    func_8007D344(fp, 0.0f, samus_attr->x3C, samus_attr->x40);
}

void ftSamus_8012AC00(HSD_GObj* fighterObj) {
    Fighter *fp = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    
    if (fp->xE0_ground_or_air == GA_Air) {
        s32 direction;

        if (fp->x80_self_vel.y >= 0.0f) {
            func_80081D0C(fighterObj);
            return;
        }
        if (fp->x2C_facing_direction == 1.0f) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (EnvColl_CheckGroundAndLedge(fighterObj, direction)) {
            ftSamus_DestroyAllUnsetx2444(fighterObj);
            func_800D5CB0(fighterObj, 0, samus_attr->x50);
            return;
        }
        if (func_80081298(fighterObj)) {
            ftSamus_DestroyAllUnsetx2444(fighterObj);
            func_80081370(fighterObj);
        }
    } else {
        func_80084104(fighterObj);
    }
}

void ftSamus_8012ACF8(HSD_GObj* fighterObj) {
    Fighter *fp = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    
    if (fp->xE0_ground_or_air == GA_Air) {
        s32 direction;

        if (fp->x80_self_vel.y >= 0.0f) {
            func_80081D0C(fighterObj);
            return;
        }
        if (fp->x2C_facing_direction == 1.0f) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (EnvColl_CheckGroundAndLedge(fighterObj, direction)) {
            ftSamus_DestroyAllUnsetx2444(fighterObj);
            func_800D5CB0(fighterObj, 0, samus_attr->x50);
            return;
        }
        if (func_80081298(fighterObj)) {
            ftSamus_DestroyAllUnsetx2444(fighterObj);
            func_80081370(fighterObj);
        }
    } else {
        func_80084104(fighterObj);
    }
}