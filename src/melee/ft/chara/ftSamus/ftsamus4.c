#include <ftsamus.h>

void ftSamus_ClearThrowFlagsUnk(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    fp->x2210_ThrowFlags.flags = 0;
    fp->cb.x21BC_callback_Accessory4 = &ftSamus_8012A074;
}

void ftSamus_SpecialS_StartAction(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->xEC_ground_vel /= samus_attr->x2C; 
    fp->x80_self_vel.y = 0.0f;
    if (fp->x673 < samus_attr->x28) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x15E, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighterObj);
    } else {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighterObj);
    }
    ftSamus_ClearThrowFlagsUnk(fighterObj);
}

void ftSamus_SpecialAirS_StartAction(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->x80_self_vel.x /= samus_attr->x2C; 
    if (fp->x673 < samus_attr->x28) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighterObj);
    } else {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x15F, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighterObj);
    }
    ftSamus_ClearThrowFlagsUnk(fighterObj);
}

void ftSamus_8012A380(HSD_GObj* fighterObj) {
    s32 unsued[2]; /// don't know how to remove this filler without unused data
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftSamus_8012A3BC(HSD_GObj* fighterObj) {
    s32 unsued[2]; /// don't know how to remove this filler without unused data
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftSamus_8012A3F8(HSD_GObj* fighterObj) {}

void ftSamus_8012A3FC(HSD_GObj* fighterObj) {}

void ftSamus_8012A400(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftSamus_8012A420(HSD_GObj *fighterObj)
{
    s32 unused[5];
    Fighter *fp = getFighterPlus(fighterObj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    Fighter *fighter2;
    func_8007D4B8(fp);
    fighter2 = fp;
    func_8007CE94(fighter2, samus_attr->x30);
}

void ftSamus_8012A468(HSD_GObj* fighterObj) {
    if (!func_800827A0(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftSamus_8012A4A4(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj)) {
        func_80082B1C(fighterObj);
    }
}

void ftSamus_8012A4E0(HSD_GObj* fighterObj) {
    s32 unused[2];
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftSamus_8012A51C(HSD_GObj* fighterObj) {
    s32 unused[2];
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftSamus_8012A558(HSD_GObj* fighterObj) {}

void ftSamus_8012A55C(HSD_GObj* fighterObj) {}

void ftSamus_8012A560(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftSamus_8012A580(HSD_GObj *fighterObj)
{
    s32 unused[8];  /// this func is so strange
    Fighter *fighter2;
    Fighter *fp;
    ftSamusAttributes *samus_attr;
    ftSamusAttributes *samus_attr2;
    fp = fighter2 = getFighterPlus(fighterObj);
    samus_attr = getFtSpecialAttrs(fp);
    func_8007D4B8(fp);
    samus_attr2 = samus_attr; 
    func_8007CE94(fp, samus_attr2->x30);
}

void ftSamus_8012A5C8(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        func_800CC730(fighterObj);
    }
}

void ftSamus_8012A604(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj)) {
        func_80082B1C(fighterObj);
    }
}

void ftSamus_8012A640(HSD_GObj* fighterObj) {
    Fighter* fp = getFighterPlus(fighterObj);
    efLib_DestroyAll(fighterObj);
    fp->sa.samus.x2244 = 0; 
}
