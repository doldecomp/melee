#include <melee/ft/chara/ftPikachu/ftpikachu.h>

void ftPikachu_SpecialN_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    func_8006EBA4(fighter_gobj);
}

void ftPikachu_SpecialAirN_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0, 0, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    func_8006EBA4(fighter_gobj);
}

void ftPikachu_80124908(HSD_GObj* fighter_gobj) {

    Vec sp14;
    s32 stack_buffer[2];
    Fighter* fp = fighter_gobj->user_data;
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1) {
        fp->x2200_ftcmd_var0 = 0;

        if (!fp->x2204_ftcmd_var1) {
            fp->x2204_ftcmd_var1 = 1;
            sp14.x = (fp->x34_scale.y * (pika_attr->x0 * fp->x2C_facing_direction)) + fp->xB0_pos.x;
            sp14.y = (pika_attr->x4 * fp->x34_scale.y) + fp->xB0_pos.y;
            sp14.z = 0.0f;
            func_802B338C(fighter_gobj, &sp14, fp->x2C_facing_direction, pika_attr->x14);
            switch (func_800872A4(fighter_gobj)) {
                case 12:
                    func_80088148(fp, 0x3a9cc, 0x7F, 0x40);
                    break;
                case 23:
                    func_80088148(fp, 0x382b3, 0x7F, 0x40);
                    break;
            }
        }
    }
    
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }    
}

void ftPikachu_80124A20(HSD_GObj* fighter_gobj) {
    Vec sp14;
    s32 stack_buffer[2];
    Fighter* fp = fighter_gobj->user_data;
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1) {
        fp->x2200_ftcmd_var0 = 0;

        if (!fp->x2204_ftcmd_var1) {
            fp->x2204_ftcmd_var1 = 1;
            sp14.x = (fp->x34_scale.y * (pika_attr->x8 * fp->x2C_facing_direction)) + fp->xB0_pos.x;
            sp14.y = (pika_attr->xC * fp->x34_scale.y) + fp->xB0_pos.y;
            sp14.z = 0.0f;
            func_802B338C(fighter_gobj, &sp14, fp->x2C_facing_direction, pika_attr->x14);
            switch (func_800872A4(fighter_gobj)) {
                case 12:
                    func_80088148(fp, 0x3a9cc, 0x7F, 0x40);
                    break;
                case 23:
                    func_80088148(fp, 0x382b3, 0x7F, 0x40);
                    break;
            }
        }
    }
    
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if (0.0f == pika_attr->x10) {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 0, 1, 1.0f, pika_attr->x10);
    }  
}

void ftPikachu_Stub_80124B6C() {}

void ftPikachu_Stub_80124B70() {}

void ftPikachu_80124B74(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftPikachu_80124B94(HSD_GObj* fighter_gobj) {
    func_80084DB0(fighter_gobj);
}

void ftPikachu_ActionChange_80124BB4(HSD_GObj* fighter_gobj) {
    Fighter* fp;
    if (!func_80082708(fighter_gobj)) {
        fp = fighter_gobj->user_data;
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0xc4c5082, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}


void ftPikachu_ActionChange_80124C20(HSD_GObj* fighter_gobj) {
    Fighter* fp;
    if (func_80081D0C(fighter_gobj) == 1) {
        fp = fighter_gobj->user_data;
        func_8007D7FC(fp);
        fp->x80_self_vel.y = 0.0f;
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x155, 0xc4c5082, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

void ftPikachu_EfSpawn_80124C90(HSD_GObj* fighter_gobj) {
    Fighter *fp = fighter_gobj->user_data;
    
    HSD_GObj *tempObj;
    HSD_GObj *tempObj2;
    
    if (!fp->x2219_flag.bits.b0)
    {
        s32 index = func_8007500C(fp, 4);
        tempObj = fighter_gobj;
        ef_Spawn(0x4BE, tempObj2 = tempObj, fp->x5E8_fighterBones[index].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftPikachu_EfSpawn_80124D2C(HSD_GObj* fighter_gobj) {
    Fighter *fp = fighter_gobj->user_data;
    
    HSD_GObj *tempObj;
    HSD_GObj *tempObj2;
    
    if (!fp->x2219_flag.bits.b0)
    {
        s32 index = func_8007500C(fp, 4);
        tempObj = fighter_gobj;
        ef_Spawn(0x4BF, tempObj2 = tempObj, fp->x5E8_fighterBones[index].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftPikachu_80124DC8(HSD_GObj* fighter_gobj) {
    u8 fighter_x673_byte;
    Fighter *fp = fighter_gobj->user_data;
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    f32 pika_attr_1C;
    
    fp->x2200_ftcmd_var0 = 0;
    fighter_x673_byte = fp->x673;

    pika_attr_1C = pika_attr->x1C;
    if (fighter_x673_byte < pika_attr_1C) {
        fp->x2340_stateVar1 = pika_attr->x20;
        fp->x2072_b4 = 1;
    } else {
        fp->x2340_stateVar1 = 0;
    }    
}
