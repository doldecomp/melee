#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 8015386C 15044C
// https://decomp.me/scratch/dCvLa
void lbl_8015386C(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80153910(arg0);
    }
}



// 801538A8 150488
void lbl_801538A8(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 801538EC 1504CC
void lbl_801538EC(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 8015390C 1504EC
void lbl_8015390C(HSD_GObj* gobj) {
    return;
}



// 80153910 1504F0
// https://decomp.me/scratch/AYDbj
void func_80153910(HSD_GObj* arg0) {
    Fighter* fp;
    MasterHandAttributes* attr;
    Vec3 sp10;
    s32 unk;

    fp = arg0->user_data;
    attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(arg0, 0x170, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    func_8015C208(arg0, &sp10);
    fp->xB0_pos.x = sp10.x;
    fp->xB0_pos.y = attr->x5C;
    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
}



// 801539A4 150584
// https://decomp.me/scratch/DVyVs
void lbl_801539A4(HSD_GObj* arg0) {
    Fighter* temp_r4;
    s32 unk;

    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        temp_r4 = arg0->user_data;
        temp_r4->x80_self_vel.x = 0.0f;
        func_80153A64(arg0);
    }
}
