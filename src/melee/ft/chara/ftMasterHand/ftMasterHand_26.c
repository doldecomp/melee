#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80154FAC 151B8C
void lbl_80154FAC(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80154FF0 151BD0
void lbl_80154FF0(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 80155010 151BF0
void lbl_80155010(HSD_GObj* gobj) {
    return;
}



// 80155014 151BF4
// https://decomp.me/scratch/ZAwzc
void func_80155014(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    Fighter_ActionStateChange_800693AC(gobj, 0x17C, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp->x2200_ftcmd_var0 = 0;
}
