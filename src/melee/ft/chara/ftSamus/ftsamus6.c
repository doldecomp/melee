#include <melee/ft/chara/ftSamus/ftsamus.h>

void ftSamus_8012ADF0(HSD_GObj* fighter_gobj) {
    Vec vec;
    BOOL bool1;
    Fighter *fp = getFighterPlus(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    
    if (fp->x2210_ThrowFlags.b0) {
        fp->x2210_ThrowFlags.b0 = 0;
        bool1 = 1;
    } else {
        bool1 = 0;
    }
    if (bool1) {
        f32 vec_x; 
        func_8000B1CC(fp->x5E8_fighterBones[0].x0_jobj, NULL, &vec);
        vec_x = samus_attr->x74_vec.x;
        vec.x += (vec_x * fp->x2C_facing_direction);
        vec.y += samus_attr->x74_vec.y;
        vec.z += samus_attr->x74_vec.z;
        func_802B4AC8(fighter_gobj, &vec, fp->x2C_facing_direction, vec_x);
        fp->cb.x21BC_callback_Accessory4 = 0;
    }
}


void ftSamus_8012AEBC(HSD_GObj* fighter_gobj) {
    struct UNK_SAMUS_S2 unk_struct;
    Fighter* fp = getFighter(fighter_gobj);
    func_8007B0C0(fighter_gobj, 2);
    
    
    unk_struct.intvec.x = 2;
    unk_struct.intvec.y = 1;
    unk_struct.intvec.z = 0;
    unk_struct.vec1.x = unk_struct.vec1.y = unk_struct.vec1.z = 0.0f; 
    unk_struct.vec2.x = unk_struct.vec2.y = unk_struct.vec2.z = 0.0f;
    unk_struct.single_float = 3.0f; 
    func_8007B5AC(fp, &fp->x11A0_fighterHurtbox[0], &unk_struct); 
}

void ftSamus_8012AF38(HSD_GObj* fighter_gobj) {
    func_8007B0C0(fighter_gobj, 0);
}

void ftSamus_SpecialLw_StartAction_inner(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.b0 = 0;
    fp->x2340_stateVar1 = 0;
    if (fp->x894_currentAnimFrame == 3.0f) {
        fp->x2204_ftcmd_var1 = 1;
    }
    fp->cb.x21BC_callback_Accessory4 = &ftSamus_8012ADF0;
}

void ftSamus_SpecialLw_StartAction(HSD_GObj* fighter_gobj) {
    Fighter *fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    
    fp->xEC_ground_vel *= samus_attr->x6C;
    if (fp->x10_action_state_index == 0x28) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0, NULL, 3.0f, 1.0f, 0.0f);
        ftSamus_SpecialLw_StartAction_inner(fighter_gobj);
        fp->x2204_ftcmd_var1 = 2;
        ftSamus_8012B5F0(fighter_gobj);
        return;
    }
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftSamus_SpecialLw_StartAction_inner(fighter_gobj);
}

void ftSamus_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj) {
    Fighter *fp = getFighterPlus(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    
    fp->x80_self_vel.x *= samus_attr->x70;
    fp->x80_self_vel.y = samus_attr->x58;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftSamus_SpecialLw_StartAction_inner(fighter_gobj);
}

///// what the heck is up with the stack in this function... can't get rid of unused params
void ftSamus_8012B150(HSD_GObj* fighter_gobj, s32 a, s32 b, s32 c, s32 d) {

    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2204_ftcmd_var1 == 1) {
        fp->x2204_ftcmd_var1 = 2;
        ftSamus_8012B5F0(fighter_gobj);
        return; 
    }
    if ((fp->x2200_ftcmd_var0) && (!fp->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighter_gobj);
        fp->x2340_stateVar1 = 1;
    }
    if ((!fp->x2200_ftcmd_var0) && ( fp->x2340_stateVar1)) {
        func_8007B0C0(fighter_gobj, 0);
        fp->x2340_stateVar1 = 0;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftSamus_8012B264(HSD_GObj* fighter_gobj, s32 a, s32 b) {

    Fighter* fp = getFighterPlus(fighter_gobj);

    if ((fp->x2200_ftcmd_var0) && (!fp->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighter_gobj);
        fp->x2340_stateVar1 = 1;
    }
    if ((!fp->x2200_ftcmd_var0) && ( fp->x2340_stateVar1)) {
        func_8007B0C0(fighter_gobj, 0);
        fp->x2340_stateVar1 = 0;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftSamus_8012B358(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    if ((fp->x2208_ftcmd_var2) && (fp->input.x624_lstick_y < samus_attr->x80)) {
        fp->x2208_ftcmd_var2 = 0;
        func_800D638C(fighter_gobj);
    }
}

void ftSamus_8012B3A4(HSD_GObj* fighter_gobj) {}

void ftSamus_8012B3A8(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    attr* ft_attr = &fp->x110_attr;
 
    if (fp->x2200_ftcmd_var0) {
        func_8007CADC(
            fp, 
            0.0f, 
            ft_attr->x110_WalkInitialVelocity * samus_attr->x64, 
            ft_attr->x118_WalkMaximumVelocity * samus_attr->x5C
        );
        func_8007CB74(fighter_gobj);
    } else {
        func_80084F3C(fighter_gobj);
    }
}

void ftSamus_8012B41C(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    attr* ft_attr = &fp->x110_attr;
 
    func_8007D4B8(fp);
    func_8007D3A8(
        fp, 
        0.0f, 
        ft_attr->x174_AerialDriftStickMult * samus_attr->x68, 
        ft_attr->x17C_AerialDriftMax * samus_attr->x60
    );
}

void ftSamus_8012B488(HSD_GObj* fighter_gobj) {
    Fighter *fp = fighter_gobj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    
    if (fp->x2200_ftcmd_var0) {
        if (!func_80082888(fighter_gobj, &samus_attr->height_attributes)) {
            ftSamus_8012B570(fighter_gobj);
        }
    } else if (!func_800827A0(fighter_gobj)) {
        ftSamus_8012B570(fighter_gobj);
    }
}

void ftSamus_8012B4FC(HSD_GObj* fighter_gobj) {
    Fighter *fp = fighter_gobj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    
    if (fp->x2200_ftcmd_var0) {
        if (func_800824A0(fighter_gobj, &samus_attr->height_attributes)) {
            ftSamus_8012B668(fighter_gobj);
        }
    } else if (func_80081D0C(fighter_gobj)) {
        ftSamus_8012B668(fighter_gobj);
    }
}

void ftSamus_UnkSetStateAndCb(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2204_ftcmd_var1 = 2;
    fp->x2340_stateVar1 = 0;
    fp->cb.x21BC_callback_Accessory4 = &ftSamus_8012ADF0;
}

void ftSamus_8012B570(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0x0C4C509C, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftSamus_UnkSetStateAndCb(fighter_gobj);
}

void ftSamus_8012B5F0(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->x80_self_vel.y = samus_attr->x54;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0x0C4C509C, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = ftSamus_8012ADF0;
}

void ftSamus_8012B668(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0x0C4C509C, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftSamus_UnkSetStateAndCb(fighter_gobj);
}
