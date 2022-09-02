#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80154D78 151958
// https://decomp.me/scratch/DzZiN
void lbl_80154D78(HSD_GObj* gobj) {
    Fighter* fp;
    s32 unused[2];
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp = gobj->user_data;
        if (fp->x2360 == 1) {
            func_80154A78(gobj);
        } else {
            func_801546D8(gobj);
        }
    }
}




// 80154DD0 1519B0
// https://decomp.me/scratch/5olg2
void lbl_80154DD0(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}




// 80154E14 1519F4
// https://decomp.me/scratch/2yMnG
void lbl_80154E14(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MasterHandAttributes* attr = fp->x10C_ftData->ext_attr;

    func_80085134(gobj);
    func_8015BE40(gobj, &fp->x234C_pos, &fp->x2358_stateVar7, attr->x2C, attr->x28);
}




// 80154E74 151A54
// https://decomp.me/scratch/0wwnm
void lbl_80154E74(HSD_GObj* gobj) {
    return;
}




// 80154E78 151A58
// https://decomp.me/scratch/lmtfb
void func_80154E78(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    Fighter_ActionStateChange_800693AC(gobj, 0x17B, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp->x2200_ftcmd_var0 = 0;
}




// 80154ED8 151AB8
// https://decomp.me/scratch/6H8xW
void lbl_80154ED8(HSD_GObj* gobj) {
    Fighter* fp;
    HSD_GObj* gobj_2;
    Fighter* ft_2;
    s32 unused[2];

    fp = gobj->user_data;
    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        func_80155D6C(fp->x1A58_interactedFighter, 0x14A);
        if (fp->x1A58_interactedFighter != 0) {
            gobj_2 = fp->x1A58_interactedFighter;
            ft_2 = gobj_2->user_data;
            func_8007E2F4(fp, 0);
            func_800DE2A8(gobj, gobj_2);
            ft_2->dmg.x1844_direction *= -1.0f;
            func_800DE7C0(gobj_2, 0, 0);
        }
        fp->x2360 = 0;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_80151018(gobj);
    }
}


