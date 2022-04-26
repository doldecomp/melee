#include "ftMasterHand.h"

// 801541C4 150DA4
void lbl_801541C4(HSD_GObj* gobj) {
    return;
}


// 801541C8 150DA8
// https://decomp.me/scratch/WhlXG
void func_801541C8(HSD_GObj* gobj, void* arg1) {
    Fighter* r31_ft_userdata;
    u32 unk[2];

    r31_ft_userdata = gobj->user_data;
    Fighter_ActionStateChange_800693AC(gobj, 0x174, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    r31_ft_userdata->x2344_callback = arg1;
}
