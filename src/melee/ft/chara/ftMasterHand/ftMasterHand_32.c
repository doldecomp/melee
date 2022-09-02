#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80155B70 152750
void func_80155B70(HSD_GObj* gobj) {
    return;
}



// 80155B74 152754
void func_80155B74(HSD_GObj* gobj) {
    return;
}



// 80155B78 152758
void func_80155B78(HSD_GObj* gobj) {
    return;
}



// 80155B7C 15275C
void func_80155B7C(HSD_GObj* gobj) {
    return;
}



// 80155B80 152760
// https://decomp.me/scratch/BFD9X
void func_80155B80(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    Fighter_ActionStateChange_800693AC(gobj, 0x148, 0, 0, 0.0f, 1.0f, 0.0f);
    fp->x221E_flag.bits.b0 = 1;
    fp->x2220_flag.bits.b3 = 1;
    fp->cb.x21B0_callback_Accessory1 = &func_800DB464;
    func_8007E2F4(fp, 0x1FF);
    fp->x2220_flag.bits.b3 = 1;
    func_8006EBA4(gobj);
}



// 80155C20 152800
// https://decomp.me/scratch/LZjJ4
void func_8007DC08(Fighter*, f32);
void func_8015483C(HSD_GObj*);
void func_80155C94(HSD_GObj*);

void func_80155C20(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    func_8007DC08(fp, p_ftCommonData->x3A8);
    if (fp->x1A4C <= 0.0f) {
        func_80155C94(gobj);
        func_8015483C(fp->x1A58_interactedFighter);
    }
}
