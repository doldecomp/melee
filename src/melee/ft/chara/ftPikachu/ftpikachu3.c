#include "ftpikachu.h"

void ftPikachu_SpecialS_StartAction(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    fighter->cb.x21EC_callback = ftPikachu_80124DC8;

    fighter->xEC_ground_vel /= pika_attr->x30;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x157, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void ftPikachu_SpecialSAir_StartAction(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    fighter->cb.x21EC_callback = ftPikachu_80124DC8;

    fighter->x80_self_vel.x /= pika_attr->x30;
    fighter->x80_self_vel.y = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15C, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void ftPikachu_ZeroVelocity_80124F24(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->x80_self_vel.x = 0.0f;
    if (fighter->x80_self_vel.y >= 0.0f) {
        fighter->x80_self_vel.y = 0.0f;
    }
    ftPikachu_ActionChange_80125D28(fighterObj);
}

void ftPikachu_80124F64(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftPikachu_ActionChange_801254D4(fighterObj);
    }
}

void ftPikachu_80124FA0(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftPikachu_ActionChange_80125528(fighterObj);
    }
}

void ftPikachu_Stub_80124FDC() {}

void ftPikachu_Stub_80124FE0() {}

void ftPikachu_80124FE4(HSD_GObj* fighterObj) {
    s32 unused;
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    f32 pika_attr_x34 = pika_attr->x34;
    func_8007C930(fighter, pika_attr_x34);
    func_8007CB74(fighterObj);
}

void ftPikachu_80125024(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    struct attr* attr = &fighter->x110_attr;
    
    if (fighter->x2200_ftcmd_var0) {
        func_8007D494(fighter, pika_attr->x38, attr->x170_TerminalVelocity);
    }
    func_8007CE94(fighter, pika_attr->x34);
}

void ftPikachu_80125084(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        ftPikachu_ActionChange_801250FC(fighterObj);
    }
}

void ftPikachu_801250C0(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj)) {
        ftPikachu_ActionChange_8012515C(fighterObj);
    }
}

void ftPikachu_ActionChange_801250FC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15C, 0xc4c5284, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_8012515C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x157, 0xc4c5284, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_801251BC(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8007DB24(fighterObj);
        fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
    }
    fighter->x2340_stateVar1++;
    if (fighter->x2340_stateVar1 > pika_attr->x24) {
        ftPikachu_ActionChange_80125834(fighterObj);
    }
}

void ftPikachu_8012525C(HSD_GObj* fighterObj) {

    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8007DB24(fighterObj);
        fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
    }

    fighter->x2340_stateVar1++;

    if (fighter->x2340_stateVar1 > pika_attr->x24) {
        ftPikachu_ActionChange_801258A0(fighterObj);
    }
    
}

void ftPikachu_801252FC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (!(fighter->input.x65C & 0x200)) {
        ftPikachu_ActionChange_80125834(fighterObj);
    }
}

void ftPikachu_8012532C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (!(fighter->input.x65C & 0x200)) {
        ftPikachu_ActionChange_801258A0(fighterObj);
    }
}

void ftPikachu_8012535C(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftPikachu_8012537C(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftPikachu_8012539C(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        ftPikachu_ActionChange_80125414(fighterObj);
    }
}

void ftPikachu_801253D8(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj) ) {
        ftPikachu_ActionChange_80125474(fighterObj);
    }
}

void ftPikachu_ActionChange_80125414(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0xC4C5286, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80125474(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x158, 0xC4C5286, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_801254D4(HSD_GObj* fighterObj) {
    s32 unused[3];
    Fighter* fighter;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x158, 0x200, 0, 0.0f, 1.0f, 0.0f);
    fighter = fighterObj->user_data;
    fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
}

void ftPikachu_ActionChange_80125528(HSD_GObj* fighterObj) {
    s32 unused[3];
    Fighter* fighter;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0x200, 0, 0.0f, 1.0f, 0.0f);
    fighter = fighterObj->user_data;
    fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
}

void ftPikachu_8012557C(HSD_GObj* fighterObj) {
    s32 unused[4];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    if (fighter->x914[0].x0 == 1) {
        f32 float_result = (fighter->x2340_stateVar1 * pika_attr->x2C) + pika_attr->x28;
        func_8007ABD0(&fighter->x914[0], float_result, fighterObj);
    }

    if (fighter->x2200_ftcmd_var0) {
        func_8007D5D4(fighter);
        ftPikachu_ActionChange_80125A54(fighterObj);
    }
}

void ftPikachu_8012561C(HSD_GObj* fighterObj) {
    s32 unused[4];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    if (fighter->x914[0].x0 == 1) {
        f32 float_result = (fighter->x2340_stateVar1 * pika_attr->x2C) + pika_attr->x28;
        func_8007ABD0(&fighter->x914[0], float_result, fighterObj);
    }

    if (fighter->x2200_ftcmd_var0) {
        ftPikachu_ActionChange_80125A54(fighterObj);
    }
}

void ftPikachu_Stub_801256B4() {}

void ftPikachu_Stub_801256B8() {}

void ftPikachu_801256BC(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftPikachu_801256DC(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftPikachu_801256FC(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        ftPikachu_ActionChange_80125774(fighterObj);
    }
}

void ftPikachu_80125738(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj)) {
        ftPikachu_ActionChange_801257D4(fighterObj);
    }
}

void ftPikachu_ActionChange_80125774(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0xC4C5086, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_801257D4(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15B, 0xC4C5086, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80125834(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15B, 0, 0, 0.0f, 1.0f, 0.0f);
    fighter = fighterObj->user_data;
    fighter->x2200_ftcmd_var0 = 0;
    func_8007DB24(fighterObj);
    fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124D2C;
}

void ftPikachu_ActionChange_801258A0(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0, 0, 0.0f, 1.0f, 0.0f);
    fighter = fighterObj->user_data;
    fighter->x2200_ftcmd_var0 = 0;
    func_8007DB24(fighterObj);
    fighter->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124D2C;
}

void ftPikachu_Stub_8012590C() {}

void ftPikachu_80125910(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftPikachu_ActionChange_80125D28(fighterObj);
    }
}

void ftPikachu_Stub_8012594C() {}

void ftPikachu_Stub_80125950() {}

void ftPikachu_Stub_80125954() {}


void ftPikachu_80125958(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    if (fighter->x2200_ftcmd_var0) {
        func_8007D494(fighter, pika_attr->x58, pika_attr->x4C);
    } else {
        func_8007D494(fighter, pika_attr->x48, pika_attr->x4C);
    }

    if (fighter->x2200_ftcmd_var0) {
        func_8007CE94(fighter, pika_attr->x54);
    }
}

void ftPikachu_Stub_801259D4() {}

void ftPikachu_801259D8(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    CollData* collData = &fighter->x6F0_collData;

    if (func_80081D0C(fighterObj)) {
        func_8007D7FC(fighter);
        ftPikachu_ActionChange_80125CD0(fighterObj);
    }

    if (collData->x134_envFlags & 0x3F || collData->x134_envFlags & 0xFC0) {
        ftPikachu_ActionChange_80125D28(fighterObj);
    }
}

void ftPikachu_ActionChange_80125A54(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    fighter->x2200_ftcmd_var0 = 0;

    fighter->x80_self_vel.x = (pika_attr->x40 * fighter->x2340_stateVar1) + pika_attr->x3C;
    fighter->x80_self_vel.x *= fighter->x2C_facing_direction;

    fighter->x80_self_vel.y = (0.5f * pika_attr->x44) + (pika_attr->x44 * (0.5f * fighter->x2340_stateVar1 / pika_attr->x24));
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15E, 0xA, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    fighter->cb.x21F8_callback = &func_8007F76C;
    fighter->cb.x21C0_callback_OnGiveDamage = &ftPikachu_ZeroVelocity_80124F24;
    
}

void ftPikachu_80125B34(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftPikachu_80125B70(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftPikachu_Stub_80125BAC() {}

void ftPikachu_Stub_80125BB0() {}

void ftPikachu_80125BB4(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    func_8007C930(fighter, pika_attr->x54);
    func_8007CB74(fighterObj);
}

void ftPikachu_80125BF4(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    func_8007D494(fighter, pika_attr->x58, fighter->x110_attr.x170_TerminalVelocity);
    func_8007CE94(fighter, pika_attr->x54);
}

void ftPikachu_80125C44(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftPikachu_80125C80(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (func_80081D0C(fighterObj)) {
        func_8007D7FC(fighter);
        ftPikachu_ActionChange_80125CD0(fighterObj);
    }
}

void ftPikachu_ActionChange_80125CD0(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    fighter->x2200_ftcmd_var0 = 0;
    fighter->xEC_ground_vel /= pika_attr->x50;

    Fighter_ActionStateChange_800693AC(fighterObj, 0x15A, 0, 0, 0.0f, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80125D28(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    fighter->x2200_ftcmd_var0 = 0;
    fighter->x80_self_vel.x /= pika_attr->x50;

    Fighter_ActionStateChange_800693AC(fighterObj, 0x15F, 0, 0, 0.0f, 1.0f, 0.0f);
}
