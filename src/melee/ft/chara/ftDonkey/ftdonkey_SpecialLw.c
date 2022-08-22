#include <ftdonkey.h>

void ftDonkey_SpecialLw_StartAction(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    fp->x2340_stateVar1 = 0;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x17F, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void ftDonkey_8010DCD8(HSD_GObj* fighterObj) {
    s32 unused[2]; // needs either unused filler, or arg params
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftDonkey_8010DE88(fighterObj);
    }
}

void ftDonkey_8010DD14(HSD_GObj* fighterObj) {}

void ftDonkey_8010DD18(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010DD38(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftDonkey_8010DD74(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        if (fp->x2340_stateVar1) {
            fp->x2340_stateVar1 = 0;
            ftDonkey_8010DE88(fighterObj);
        } else {
            ftDonkey_8010DFF8(fighterObj);
        }
    }
}

void ftDonkey_8010DDDC(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    if (fp->input.x668 & 0x200) {
        fp->x2340_stateVar1 = 1;
    }
}

void ftDonkey_8010DDF8(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010DE18(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftDonkey_8010DE54(HSD_GObj* fighterObj) {
    func_80089824(fighterObj);
    func_800892A0(fighterObj);
}

void ftDonkey_8010DE88_inner(HSD_GObj* fighterObj) {
    Fighter* fp = getFighterPlus(fighterObj);
    if (!fp->x2219_flag.bits.b0) {
        efAsync_Spawn(fighterObj, &fp->x60C, 1, 0x4CC, fp->x5E8_fighterBones[0].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_8010DE88(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    fp->cb.x21EC_callback = &ftDonkey_8010DE54;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x180, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_8010DE88_inner(fighterObj);
    fp->cb.x21BC_callback_Accessory4 = &ftDonkey_8010DB3C;
}

void ftDonkey_8010DF5C(HSD_GObj* fighterObj) {
    s32 unused[2];
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftDonkey_8010DF98(HSD_GObj* fighterObj) {}

void ftDonkey_8010DF9C(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010DFBC(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftDonkey_8010DFF8(HSD_GObj* fighterObj) {
    Fighter_ActionStateChange_800693AC(fighterObj, 0x181, 0, NULL, 0.0f, 1.0f, 0.0f);
}

void ftDonkey_8010E030(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftDonkey_8010E06C(HSD_GObj* fighterObj) {}

void ftDonkey_8010E070(HSD_GObj* fighterObj) {
    func_80084DB0(fighterObj);
} 

void ftDonkey_8010E090(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftDonkey_8010E0CC(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    if (!fp->x2219_flag.bits.b0) {
        ef_Spawn(0x4C6, fighterObj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftDonkey_8010E148(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    if (!fp->x2219_flag.bits.b0) {
        ef_Spawn(0x4C7, fighterObj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}
