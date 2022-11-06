#include <melee/ft/chara/ftSamus/ftsamus.h>

#include <melee/ef/ef.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/lb/lbunknown_001.h>

void ftSamus_801293BC_inner(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    s32 x2230 = fp->sa.samus.x2230;
    fp->x80_self_vel.x = (fp->facing_direction * (samus_attr->x1C * x2230));
}

void ftSamus_801291F0(HSD_GObj* fighter_gobj){
    if (fighter_gobj) {
        Fighter* fp = getFighter(fighter_gobj);
        if (fp->sa.samus.x222C) {
            fp->sa.samus.x222C = 0;
        }
        ftSamus_destroyAllEF(fighter_gobj);
    } 
}


void ftSamus_80129258(HSD_GObj* fighter_gobj) {
    
    if (fighter_gobj) {
        Fighter* fp = getFighter(fighter_gobj);
        ftSamus_UnkAndDestroyAllEF(fighter_gobj);
        fp->sa.samus.x2230 = 0;
    }
}


s32 ftSamus_801292E4(HSD_GObj* fighter_gobj) {
    Vec vec1;
    Vec vec2;
    
    u32 result;
    Fighter* fp = getFighter(fighter_gobj);
    
    if ((fp->x2200_ftcmd_var0 == 1U) && (!fp->sa.samus.x222C)) {
        fp->x2200_ftcmd_var0 = 0U;
        vec2.z = 4.0f;
        vec2.y = 0.0f;
        vec2.x = 0.0f;
        func_8000B1CC(fp->x5E8_fighterBones[50].x0_jobj, &vec2, &vec1);
        vec1.z = 0.0f;
        result = func_802B55C8(fighter_gobj, &vec1, 0x32, 0x5E, fp->facing_direction);
        fp->sa.samus.x222C = result;
        if (result) {
            ftSamus_updateDamageDeathCBs(fighter_gobj);
        } else {
            fp->sa.samus.x222C = 0U;
            return 1;
        }
    }
    return 0;
}

#include <math.h>
#include <melee/pl/player.h>
#include <melee/it/code_8027CF30.h>

void ftSamus_801293BC(HSD_GObj* fighter_gobj) {
    ftSamusAttributes* samus_attr;
    HSD_GObj* held_item;
    Fighter* fp;
    f64 var_f0;
    s32 unused[5]; // could not match all the stack without this

    fp = getFighterPlus(fighter_gobj);
    samus_attr = getFtSpecialAttrs(fp);

    if ((fp->x2204_ftcmd_var1 == 1) && (fp->sa.samus.x222C)) {
        Vec vec1;
        u32 x2230; 

        fp->x2204_ftcmd_var1 = 2;
        func_8000B1CC(fp->x5E8_fighterBones[51].x0_jobj, NULL, &vec1);
        vec1.z = 0.0f;
        held_item = fp->x1974_heldItem;
        if (1.0f == fp->facing_direction) {
            var_f0 = 0.0;
        } else {
            var_f0 = M_PI;
        }
        x2230 = fp->sa.samus.x2230; 
        func_802B56E4(fp->sa.samus.x222C, &vec1, var_f0, x2230, samus_attr->x18);
        if ((fp->x10_action_state_index == 0x15C) ||  (fp->xE0_ground_or_air == GA_Air)) {
            ftSamus_801293BC_inner(fighter_gobj);
        }
        fp->sa.samus.x2230 = 0U;
        
        ftSamus_801291F0(fighter_gobj);
        ef_Spawn(0x486, fighter_gobj, &vec1, &fp->facing_direction);
        fp->x1974_heldItem = held_item;
    }
}

#include <melee/ft/ftanim.h>

void ftSamus_SpecialN_StartAction(HSD_GObj* fighter_gobj) {
    Vec* self_vel;
    Fighter* fp = getFighter(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x157, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    func_8007D7FC(fp);
    self_vel = &fp->x80_self_vel;
    self_vel->y = 0.0f;
    ftSamus_updateDamageDeathCBs(fighter_gobj);
    fp->x2340_stateVar1 = 0;
    fp->x2344_stateVar2 = 0;
    fp->x2348_stateVar3_f32 = 0.0f;
    func_8006EBA4(fighter_gobj);
}  

void ftSamus_SpecialAirN_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15B, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftSamus_updateDamageDeathCBs(fighter_gobj);
    fp->x2340_stateVar1 = 1;
    fp->x2344_stateVar2 = 0;
    fp->x2348_stateVar3_f32 = 0.0f;
    func_8006EBA4(fighter_gobj);
}

#include <melee/ft/ftanim.h>

void ftSamus_80129684(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    ftSamus_801292E4(fighter_gobj);
    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        if ((fp->x2340_stateVar1 == 1) || (fp->sa.samus.x2230 == samus_attr->x18)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15A, 0, NULL, 0.0f, 1.0f, 0.0f);
        } else {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x158, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftSamus_SetAttrx2334(fighter_gobj);
        }
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}


extern s32 lbl_803CE6B8[]; // TODO

void ftSamus_80129774(HSD_GObj *fighter_gobj)
{
  s32 unused;
  Fighter *fp;
  Fighter *fighter2;
  ftSamusAttributes *samus_attr;
  ftSamusAttributes *samus_attr2;

  fp = fighter2 = getFighterPlus(fighter_gobj);
  samus_attr = samus_attr2 = getFtSpecialAttrs(fp);
  if (fighter2->x2208_ftcmd_var2) {
    /// this block might be an inline, but couldn't get the regalloc to behave
    f32 var_f1;
    s32 index;
    fighter2->x2208_ftcmd_var2 = 0;
    if (fighter2->sa.samus.x2230){
      var_f1 = fighter2->sa.samus.x2230 / samus_attr->x18;
    }
    else {
      var_f1 = 0.f;
    }
    index = 5.0f * var_f1;
    func_80088510(fighter2, lbl_803CE6B8[index], 0x7F, 0x40);
  }
    
  fp->x2344_stateVar2 += 1;
  if (fp->x2344_stateVar2_s32 > samus_attr->x20)
  {
    fp->x2344_stateVar2 = 0;
    fp->sa.samus.x2230 += 1;
    if (fp->sa.samus.x2230 >= samus_attr->x18)
    {
      func_800BFFD0(fp, 0x35, 0);
      fp->sa.samus.x2230 = samus_attr->x18;
      Fighter_ActionStateChange_800693AC(fighter_gobj, 0x159, 0, 0, 0.0f, 1.0f, 0.0f);
      ftSamus_UnkAndDestroyAllEF(fighter_gobj);
      ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
  }
}

void ftSamus_80129940(HSD_GObj* fighter_gobj) {
    /// the filler here matches the following function where it is unavoidable
    /// It's possible to adjust the stack usage of the inline function, but that adjusts the stack usage 
    /// in the other functions that use it, this seems to be the best fit across all functions in this file
    s32 unused[4];
    ftSamus_UnkAndDestroyAllEF(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftSamus_801299D0(HSD_GObj* fighter_gobj) {
    s32 unused[6];  /// can't get rid of this, must have been something left over from removed code
    ftSamus_801293BC(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftSamus_80129A14(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftSamus_801292E4(fighter_gobj);
    fp->x2340_stateVar1 = 1;
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15C, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129A98(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    ftSamus_801293BC(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if (samus_attr->x24 == 0.0f) {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 0, 1, 1.0f, samus_attr->x24);
    }
}

void ftSamus_80129B18(HSD_GObj* fighter_gobj) {}

void ftSamus_80129B1C(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj *fighterObj2;
    if (func_8009917C(fighter_gobj)) {
        fighterObj2 = fighter_gobj;
        ftSamus_UnkAndDestroyAllEF(fighterObj2);
    } else {
        if ((fp->input.x668 & 0x200)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15A, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftSamus_updateDamageDeathCBs(fighter_gobj);
            return;
        }
        if ((fp->input.x668 & 0x80000000)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x159, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftSamus_UnkAndDestroyAllEF(fighter_gobj);
            ftSamus_updateDamageDeathCBs(fighter_gobj);
        }
    }
}

void ftSamus_80129C78(HSD_GObj* fighter_gobj) {}

void ftSamus_80129C7C(HSD_GObj* fighter_gobj) {}

void ftSamus_80129C80(HSD_GObj* fighter_gobj) {}

void ftSamus_80129C84(HSD_GObj* fighter_gobj) {}

void ftSamus_80129C88(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftSamus_80129CA8(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftSamus_80129CC8(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftSamus_80129CE8(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftSamus_80129D08(HSD_GObj* fighter_gobj) {
    func_80084EEC(fighter_gobj);
}

void ftSamus_80129D28(HSD_GObj* fighter_gobj) {
    func_80084EEC(fighter_gobj);
}

void ftSamus_80129D48(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (!func_80082708(fighter_gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15B, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129DC8(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (!func_80082708(fighter_gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15C, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
        func_80088148(fp, 0x3F7B5U, 0x7FU, 0x40U);
        fp->x2204_ftcmd_var1 = 1;
    }
}

void ftSamus_80129E68(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (!func_80082708(fighter_gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15C, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129EE8(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (!func_80082708(fighter_gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15C, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129F68(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (func_80081D0C(fighter_gobj) == 1) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x157, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129FE8(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (func_80081D0C(fighter_gobj) == 1) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15A, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}


s32 ftSamus_8012A068(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    return fp->sa.samus.x2238;
}

void ftSamus_8012A074(HSD_GObj* fighter_gobj) {
    BOOL bool1;
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    if (fp->x2210_ThrowFlags.b0) {
        fp->x2210_ThrowFlags.b0 = 0;
        bool1 = 1;
    } else {
        bool1 = 0;
    }
    if (bool1) {
        Vec position;
        fp->sa.samus.x2238++;
        func_8000B1CC(fp->x5E8_fighterBones[56].x0_jobj, NULL, &position);
        position.x += (samus_attr->x34 * fp->facing_direction);
        if ((fp->x10_action_state_index == 0x15D) || (fp->x10_action_state_index == 0x15F)) {
            func_802B62D0(fighter_gobj, &position, 0, fp->facing_direction);
        } else {
            func_802B62D0(fighter_gobj, &position, 1, fp->facing_direction);
        }
        ftSamus_8012A168(fighter_gobj, &position);
        fp->cb.x21BC_callback_Accessory4 = 0;
    }
}

void ftSamus_8012A168(HSD_GObj* fighter_gobj, Vec* spawnlocation) {
    Fighter* fp = getFighter(fighter_gobj);
    if (!fp->x2219_flag.bits.b0) {
        ef_Spawn(0x483, fighter_gobj, spawnlocation);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}
