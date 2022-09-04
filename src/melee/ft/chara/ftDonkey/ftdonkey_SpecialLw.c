#include <melee/ft/chara/ftDonkey/ftdonkey.h>

void ftDonkey_SpecialLw_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2340_stateVar1 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17F, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}

void ftDonkey_8010DCD8(HSD_GObj* fighter_gobj) {
    s32 unused[2]; // needs either unused filler, or arg params
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftDonkey_8010DE88(fighter_gobj);
    }
}

void ftDonkey_8010DD14(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010DD18(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_8010DD38(HSD_GObj* fighter_gobj) {
    if (!func_80082708(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftDonkey_8010DD74(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if (fp->x2340_stateVar1) {
            fp->x2340_stateVar1 = 0;
            ftDonkey_8010DE88(fighter_gobj);
        } else {
            ftDonkey_8010DFF8(fighter_gobj);
        }
    }
}

void ftDonkey_8010DDDC(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (fp->input.x668 & 0x200) {
        fp->x2340_stateVar1 = 1;
    }
}

void ftDonkey_8010DDF8(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_8010DE18(HSD_GObj* fighter_gobj) {
    if (!func_80082708(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftDonkey_8010DE54(HSD_GObj* fighter_gobj) {
    func_80089824(fighter_gobj);
    func_800892A0(fighter_gobj);
}

void ftDonkey_8010DE88_inner(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (!fp->x2219_flag.bits.b0) {
        efAsync_Spawn(fighter_gobj, &fp->x60C, 1, 0x4CC, fp->x5E8_fighterBones[0].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_8010DE88(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    fp->cb.x21EC_callback = &ftDonkey_8010DE54;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x180, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_8010DE88_inner(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftDonkey_8010DB3C;
}

void ftDonkey_8010DF5C(HSD_GObj* fighter_gobj) {
    s32 unused[2];
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftDonkey_8010DF98(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010DF9C(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_8010DFBC(HSD_GObj* fighter_gobj) {
    if (!func_80082708(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftDonkey_8010DFF8(HSD_GObj* fighter_gobj) {
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x181, 0, NULL, 0.0f, 1.0f, 0.0f);
}

void ftDonkey_8010E030(HSD_GObj* fighter_gobj) {
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftDonkey_8010E06C(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010E070(HSD_GObj* fighter_gobj) {
    func_80084DB0(fighter_gobj);
} 

void ftDonkey_8010E090(HSD_GObj* fighter_gobj) {
    if (func_80081D0C(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftDonkey_8010E0CC(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    if (!fp->x2219_flag.bits.b0) {
        ef_Spawn(0x4C6, fighter_gobj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftDonkey_8010E148(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    if (!fp->x2219_flag.bits.b0) {
        ef_Spawn(0x4C7, fighter_gobj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}
