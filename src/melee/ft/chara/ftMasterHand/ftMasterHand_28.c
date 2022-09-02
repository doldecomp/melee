#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 8015521C 151DFC
// https://decomp.me/scratch/veN50
void lbl_8015521C(HSD_GObj* gobj) {
    Fighter* fp;

    if ((func_8015C31C() != 0) || (func_8015C3A0() != 0) || (ftAnim_IsFramesRemaining(gobj) == 0)) {
        fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        func_80151018(gobj);
    }
}




// 80155290 151E70
void lbl_80155290(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 801552D4 151EB4
void lbl_801552D4(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 801552F4 151ED4
void lbl_801552F4(HSD_GObj* gobj) {
    return;
}



// 801552F8 151ED8
// https://decomp.me/scratch/x0WJ4
void lbl_801552F8(HSD_GObj* gobj) {
    Fighter* fp;
    HSD_GObj* gobj_2;

    fp = gobj->user_data;
    fp->x2204_ftcmd_var1 = 0;
    gobj_2 = func_8015C3E8(0x1CU);
    if (func_8015C31C() == 0) {
        func_8015A3F4(gobj_2);
    }
    fp->x1A5C = gobj_2;
    Fighter_ActionStateChange_800693AC(gobj, 0x17F, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}
