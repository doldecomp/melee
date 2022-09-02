#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80155388 151F68
// https://decomp.me/scratch/6nLDB
void lbl_80155388(HSD_GObj* gobj) {
    Fighter* fp;
    Fighter* ft_2;
    s32 unused[2];

    fp = gobj->user_data;
    if (fp->x2204_ftcmd_var1 != 0) {
        func_8015C5F8(gobj);
        fp->x2204_ftcmd_var1 = 0;
    }
    // inlined? possibly shared with lbl_8015521C
    if ((func_8015C31C() != 0) || (func_8015C3A0() != 0) || (ftAnim_IsFramesRemaining(gobj) == 0)) {
        ft_2 = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        ft_2->x1A5C = 0;
        func_80151018(gobj);
    }
}



// 8015541C 151FFC
void lbl_8015541C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 80155460 152040
void lbl_80155460(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 80155480 152060
void lbl_80155480(HSD_GObj* gobj) {
    return;
}



// 80155484 152064
// https://decomp.me/scratch/jsnxb
void lbl_80155484(HSD_GObj* gobj) {
    Fighter* fp;
    HSD_GObj* gobj_2;

    fp = gobj->user_data;
    gobj_2 = func_8015C3E8(0x1CU);
    if (func_8015C31C() == 0) {
        func_8015A560(gobj_2);
    }
    fp->x1A5C = gobj_2;
    Fighter_ActionStateChange_800693AC(gobj, 0x180, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}
