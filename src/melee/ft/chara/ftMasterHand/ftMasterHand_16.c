#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 8015377C 15035C
// https://decomp.me/scratch/003fu
void lbl_8015377C(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80151018(arg0);
    }
}



// 801537B8 150398
void lbl_801537B8(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 801537FC 1503DC
void lbl_801537FC(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 8015381C 1503FC
void lbl_8015381C(HSD_GObj* gobj) {
    return;
}



// 80153820 150400
// https://decomp.me/scratch/d4xeU
void func_80153820(HSD_GObj* arg0) {
    Fighter_ActionStateChange_800693AC(arg0, 0x16F, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
}
