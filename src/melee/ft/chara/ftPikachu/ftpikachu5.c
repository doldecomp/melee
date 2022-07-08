#include "ftpikachu.h"

s32 ftPikachu_CheckProperty_801275CC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    s32 value = fighter->x2071_b0_3;

    switch (value) {
        case 1: 
        case 2: 
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            return 1;
        default:
            return 0;

    }

}

void ftPikachu_80127608(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80030E44(2, &fighter->xB0_pos);
    func_8007EBAC(fighter, 0xB, 0);
}

void ftPikachu_SetState_8012764C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->x2344_stateVar2 = 3;
}


inline f32 nested_sum_fabs(f32 fighter_pos_y, f32 pika_attr_xBC, f32 pika_attr_xBC_abs, f32 vec_y) {
    if (fighter_pos_y + pika_attr_xBC_abs - vec_y < 0.0f) {
        return -(fighter_pos_y + fabs_inline(pika_attr_xBC) - vec_y);
    } else {
        return fighter_pos_y + fabs_inline(pika_attr_xBC) - vec_y;
    }
}

s32 ftPikachu_8012765C(HSD_GObj* fighterObj) {
    Vec vec;
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    u32 state_var = fighter->x2340_stateVar1_u32;

    if (!fighter->x2344_stateVar2_s32) {
        return 0;
    }

    if (state_var) {
        func_802B1FE8(state_var, &vec);
    } else {
        return 0;
    }
    

    if (fabs_inline(fighter->xB0_pos.x - vec.x) < fabs_inline(pika_attr->xC4)) {

        f32 final_y_pos = nested_sum_fabs(fighter->xB0_pos.y, pika_attr->xBC, fabs_inline(pika_attr->xBC), vec.y);

        if (
            (final_y_pos < pika_attr->xC8) 
            && 
            fighter->x2340_stateVar1_u32 
            && 
            !func_802B1DEC(fighter->x2340_stateVar1_u32)
        )
        {
            func_802B1FC8(fighter->x2340_stateVar1_u32);
            return 1;
        }
    }
    

    return 0;
}

void ftPikachu_SetState_8012779C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->x2344_stateVar2 = 0;
}

void ftPikachu_EfSpawn_801277AC(HSD_GObj* fighterObj) {
    s32 unused;
    Vec vec1;
    Vec vec2;
    Vec vec3;
    s32 unused2[2];
    
    Fighter* fighter;
    ftPikachuAttributes* pika_attr;
    BOOL flag_check;

    fighter = fighterObj->user_data;
    pika_attr = fighter->x2D4_specialAttributes;
    
    if (fighter->x2210_ThrowFlags.b0) {
        fighter->x2210_ThrowFlags.b0 = 0;
        flag_check = 1;
    } else {
        flag_check = 0;
    }
    if (flag_check && !fighter->x2340_stateVar1_u32) {
        vec1 = fighter->xB0_pos;

        vec1.y += pika_attr->xD0;
        vec2 = vec1;
        vec2.y += pika_attr->xCC;
        ef_Spawn(0x4C3, fighterObj, &vec2);
        {
            vec3.z = 0.0f;
            vec3.x = 0.0f;
            vec3.y = pika_attr->xC0;
            fighter->x2340_stateVar1 = func_802B1DF8(fighterObj, &vec1, &vec3, pika_attr->xD4, pika_attr->xD8, pika_attr->xDC);
        }
    }
}

void ftPikachu_SpecialLw_StartAction(HSD_GObj* fighterObj) {

    Fighter* fighter = fighterObj->user_data;
    fighter->x2200_ftcmd_var0 = 0;
    *((u32*)(&fighter->x2210_ThrowFlags)) = 0;
    fighter->x2344_stateVar2 = 1;
    fighter->x2340_stateVar1 = 0;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x167, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void ftPikachu_SpecialLwAir_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->x2200_ftcmd_var0 = 0;
    *((u32*)(&fighter->x2210_ThrowFlags)) = 0;
    fighter->x2344_stateVar2 = 1;
    fighter->x2340_stateVar1 = 0;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x16B, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void ftPikachu_ActionChange_8012798C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x167, 0xC4C5086, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_801279EC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x16B, 0xC4C5086, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fighter);
}

void ftPikachu_ActionChange_80127A54(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x168, 0xC4C588E, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    fighter->cb.x21DC_callback_OnTakeDamage = &ftPikachu_SetState_8012779C;
    fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_801277AC;
}

void ftPikachu_ActionChange_80127ACC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x16C, 0xC4C588E, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    fighter->cb.x21DC_callback_OnTakeDamage = &ftPikachu_SetState_8012779C;
    fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_801277AC;
    func_8007D468(fighter);
}

void ftPikachu_ActionChange_80127B4C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x169, 0xC4C508E, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80127BAC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x16D, 0xC4C508E, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fighter);
}

void ftPikachu_ActionChange_80127C14(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x16A, 0xC4C5086, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80127C74(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x16E, 0xC4C5086, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fighter);
}

void ftPikachu_ActionChange_80127CDC(HSD_GObj* fighterObj) {
    s32 unused[4];

    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        Fighter *fighter_copy;
        Fighter *fighter = fighterObj->user_data;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x168, 0x800, 0, 0.0f, 1.0f, 0.0f);
        fighter_copy = fighterObj->user_data;
        *((u32*)(&fighter_copy->x2210_ThrowFlags)) = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage = &ftPikachu_SetState_8012779C;
        fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_801277AC;

    }
}

void ftPikachu_ActionChange_80127D60(HSD_GObj* fighterObj) {
    s32 unused[4];

    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        Fighter *fighter_copy;
        Fighter *fighter = fighterObj->user_data;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x16C, 0x800, 0, 0.0f, 1.0f, 0.0f);
        fighter_copy = fighterObj->user_data;
        *((u32*)(&fighter_copy->x2210_ThrowFlags)) = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage = &ftPikachu_SetState_8012779C;
        fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_801277AC;

    }
}

void ftPikachu_ActionChange_80127DE4(HSD_GObj* fighterObj) {
    s32 unused[4];
    Fighter* fighter = fighterObj->user_data;
    if ((fighter->x2344_stateVar2_s32 == 3) || fighter->x2200_ftcmd_var0) {
        fighter->cb.x21DC_callback_OnTakeDamage= 0;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x16A, 0, 0, 0.0f, 1.0f, 0.0f);
        return;
    }
    if (ftPikachu_8012765C(fighterObj)) {
        Fighter* fighter_copy = fighterObj->user_data;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x169, 0, 0, 0.0f, 1.0f, 0.0f);
        fighter_copy->x2200_ftcmd_var0 = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage = 0;
        fighter = fighterObj->user_data;
        efAsync_Spawn(fighterObj, &fighter->x60C, 0, 0x4C0, fighter_copy->x5E8_fighterBones[0].x0_jobj);
    }
}

void ftPikachu_ActionChange_80127EC0(HSD_GObj* fighterObj) {
    s32 unused[8];
    Fighter* fighter = fighterObj->user_data;
    if ((fighter->x2344_stateVar2_s32 == 3) || fighter->x2200_ftcmd_var0) {
        fighter->cb.x21DC_callback_OnTakeDamage= 0;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x16E, 0, 0, 0.0f, 1.0f, 0.0f);
        return;
    }
    if (ftPikachu_8012765C(fighterObj)) {
        Fighter* fighter_copy = fighterObj->user_data;
        ftPikachuAttributes* pika_attr = fighter_copy->x2D4_specialAttributes;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x16D, 0, 0, 0.0f, 1.0f, 0.0f);
        fighter_copy->x2200_ftcmd_var0 = 0;
        fighter_copy->cb.x21DC_callback_OnTakeDamage = 0;
        fighter_copy->x80_self_vel.y = (f32) pika_attr->xB4;
        fighter = fighterObj->user_data;
        efAsync_Spawn(fighterObj, &fighter->x60C, 0, 0x4C0, fighter_copy->x5E8_fighterBones[0].x0_jobj);
    }
} 

void ftPikachu_ActionChange_80127FB0(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (fighter->x2200_ftcmd_var0) {
        fighter->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x16A, 0, 0, 0.0f, 1.0f, 0.0f);
    }
}

void ftPikachu_ActionChange_80128000(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (fighter->x2200_ftcmd_var0) {
        fighter->cb.x21DC_callback_OnTakeDamage = 0;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x16E, 0, 0, 0.0f, 1.0f, 0.0f);
    }
}

void ftPikachu_80128050(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftPikachu_8012808C(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftPikachu_801280C8(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftPikachu_801280E8(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftPikachu_80128108(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftPikachu_80128128(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftPikachu_80128148(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftPikachu_80128168(HSD_GObj* fighterObj) {
    s32 unused;
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    f32 pika_B8 = pika_attr->xB8;
    f32 terminal_velocity = fighter->x110_attr.x170_TerminalVelocity;
    func_8007D494(fighter, pika_B8, terminal_velocity);
    func_8007CF58(fighter);
}

void ftPikachu_801281AC(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftPikachu_801281CC(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftPikachu_PrepCallActionChange_801281EC(HSD_GObj* fighterObj) {
    func_8008403C(fighterObj, &ftPikachu_ActionChange_801279EC);
}

void ftPikachu_PrepCallActionChange_80128214(HSD_GObj* fighterObj) {
    func_80082C74(fighterObj, &ftPikachu_ActionChange_8012798C);
}

void ftPikachu_PrepCallActionChange_8012823C(HSD_GObj* fighterObj) {
    func_8008403C(fighterObj, &ftPikachu_ActionChange_80127ACC);
}

void ftPikachu_PrepCallActionChange_80128264(HSD_GObj* fighterObj) {
    func_80082C74(fighterObj, &ftPikachu_ActionChange_80127A54);
}

void ftPikachu_PrepCallActionChange_8012828C(HSD_GObj* fighterObj) {
    func_8008403C(fighterObj, &ftPikachu_ActionChange_80127BAC);
}

void ftPikachu_PrepCallActionChange_801282B4(HSD_GObj* fighterObj) {
    func_80082C74(fighterObj, &ftPikachu_ActionChange_80127B4C);
}

void ftPikachu_PrepCallActionChange_801282DC(HSD_GObj* fighterObj) {
    func_8008403C(fighterObj, &ftPikachu_ActionChange_80127C74);
}

void ftPikachu_PrepCallActionChange_80128304(HSD_GObj* fighterObj) {
    func_80082C74(fighterObj, &ftPikachu_ActionChange_80127C14);
}