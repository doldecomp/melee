#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80155074 151C54
// https://decomp.me/scratch/GL82m
void lbl_80155074(HSD_GObj* gobj) {
    s32 unused[2];
    Fighter* fp;
    HSD_GObj* gobj_2;

    fp = gobj->user_data;
    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        func_80155D6C(fp->x1A58_interactedFighter, 0x14A);
        if (fp->x1A58_interactedFighter != 0) {
            gobj_2 = fp->x1A58_interactedFighter;
            func_8007E2F4(fp, 0);
            func_800DE2A8(gobj, gobj_2);
            func_800DE7C0(gobj_2, 0, 0);
        }
        fp->x2360 = 0;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_80151018(gobj);
    }
}




// 8015512C 151D0C
void lbl_8015512C(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80155170 151D50
void lbl_80155170(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 80155190 151D70
void lbl_80155190(HSD_GObj* gobj) {
    return;
}



// 80155194 151D74
// https://decomp.me/scratch/3ppDy
void lbl_80155194(HSD_GObj* gobj) {
    Fighter* fp;
    HSD_GObj* gobj_2;

    fp = gobj->user_data;
    gobj_2 = func_8015C3E8(0x1C);
    if (func_8015C31C() == 0) {
        func_8015A2B0(gobj_2);
    }
    fp->x1A5C = gobj_2;
    Fighter_ActionStateChange_800693AC(gobj, 0x17E, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}
