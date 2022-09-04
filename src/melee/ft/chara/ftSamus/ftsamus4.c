#include <melee/ft/chara/ftSamus/ftsamus.h>

void ftSamus_ClearThrowFlagsUnk(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    fp->x2210_ThrowFlags.flags = 0;
    fp->cb.x21BC_callback_Accessory4 = &ftSamus_8012A074;
}

void ftSamus_SpecialS_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->xEC_ground_vel /= samus_attr->x2C; 
    fp->x80_self_vel.y = 0.0f;
    if (fp->x673 < samus_attr->x28) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15E, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighter_gobj);
    } else {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15D, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighter_gobj);
    }
    ftSamus_ClearThrowFlagsUnk(fighter_gobj);
}

void ftSamus_SpecialAirS_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->x80_self_vel.x /= samus_attr->x2C; 
    if (fp->x673 < samus_attr->x28) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x160, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighter_gobj);
    } else {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15F, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighter_gobj);
    }
    ftSamus_ClearThrowFlagsUnk(fighter_gobj);
}

void ftSamus_8012A380(HSD_GObj* fighter_gobj) {
    s32 unsued[2]; /// don't know how to remove this filler without unused data
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftSamus_8012A3BC(HSD_GObj* fighter_gobj) {
    s32 unsued[2]; /// don't know how to remove this filler without unused data
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftSamus_8012A3F8(HSD_GObj* fighter_gobj) {}

void ftSamus_8012A3FC(HSD_GObj* fighter_gobj) {}

void ftSamus_8012A400(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftSamus_8012A420(HSD_GObj *fighter_gobj)
{
    s32 unused[5];
    Fighter *fp = getFighterPlus(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    Fighter *fighter2;
    func_8007D4B8(fp);
    fighter2 = fp;
    func_8007CE94(fighter2, samus_attr->x30);
}

void ftSamus_8012A468(HSD_GObj* fighter_gobj) {
    if (!func_800827A0(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftSamus_8012A4A4(HSD_GObj* fighter_gobj) {
    if (func_80081D0C(fighter_gobj)) {
        func_80082B1C(fighter_gobj);
    }
}

void ftSamus_8012A4E0(HSD_GObj* fighter_gobj) {
    s32 unused[2];
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftSamus_8012A51C(HSD_GObj* fighter_gobj) {
    s32 unused[2];
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftSamus_8012A558(HSD_GObj* fighter_gobj) {}

void ftSamus_8012A55C(HSD_GObj* fighter_gobj) {}

void ftSamus_8012A560(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftSamus_8012A580(HSD_GObj *fighter_gobj)
{
    s32 unused[8];  /// this func is so strange
    Fighter *fighter2;
    Fighter *fp;
    ftSamusAttributes *samus_attr;
    ftSamusAttributes *samus_attr2;
    fp = fighter2 = getFighterPlus(fighter_gobj);
    samus_attr = getFtSpecialAttrs(fp);
    func_8007D4B8(fp);
    samus_attr2 = samus_attr; 
    func_8007CE94(fp, samus_attr2->x30);
}

void ftSamus_8012A5C8(HSD_GObj* fighter_gobj) {
    if (!func_80082708(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftSamus_8012A604(HSD_GObj* fighter_gobj) {
    if (func_80081D0C(fighter_gobj)) {
        func_80082B1C(fighter_gobj);
    }
}

void ftSamus_8012A640(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    efLib_DestroyAll(fighter_gobj);
    fp->sa.samus.x2244 = 0; 
}
