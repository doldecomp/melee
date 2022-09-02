#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

extern const f32 neg1;

// 8015550C 1520EC
// https://decomp.me/scratch/wrO5N
void lbl_8015550C(HSD_GObj* gobj) {
    Fighter* fp;

    if ((func_8015C31C() != 0) || (func_8015C3A0() != 0) || (ftAnim_IsFramesRemaining(gobj) == 0)) {
        fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        func_80151018(gobj);
    }
}



// 80155580 152160
void lbl_80155580(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 801555C4 1521A4
void lbl_801555C4(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 801555E4 1521C4
void lbl_801555E4(HSD_GObj* gobj) {
    return;
}



// 801555E8 1521C8
// https://decomp.me/scratch/mvCUe
void lbl_801555E8(HSD_GObj* gobj) {
    Fighter* fp;

    if ((func_8015C31C() != 0) || (func_8015C3A0() != 0) || (ftAnim_IsFramesRemaining(gobj) == 0)) {
        fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        func_80155818(gobj);
    }
}



// 8015565C 15223C
void lbl_8015565C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 801556A0 152280
void lbl_801556A0(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 801556C0 1522A0
void lbl_801556C0(HSD_GObj* gobj) {
    return;
}



// 801556C4 1522A4
// https://decomp.me/scratch/Uuy48
void lbl_801556C4(HSD_GObj* gobj) {
    Fighter* fp;
    HSD_GObj* gobj_2;
    Fighter* ft_2;
    Fighter* ft_3;
    s32 unused[4];

    fp = gobj->user_data;
    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        func_80155D6C(fp->x1A58_interactedFighter, 0x14A);
        if (fp->x1A58_interactedFighter != 0) {
            gobj_2 = fp->x1A58_interactedFighter;
            ft_2 = gobj_2->user_data;
            func_8007E2F4(fp, 0);
            func_800DE2A8(gobj, gobj_2);
            ft_2->dmg.x1844_direction *= neg1;
            func_800DE7C0(gobj_2, 0, 0);
        }
    }
    if ((func_8015C31C() != 0) || (ftAnim_IsFramesRemaining(gobj) == 0)) {
        ft_3 = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        ft_3->x1A5C = 0;
        func_80151018(gobj);
    }
}



// 801557B0 152390
void lbl_801557B0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 801557F4 1523D4
void lbl_801557F4(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 80155814 1523F4
void lbl_80155814(HSD_GObj* gobj) {
    return;
}



// 80155818 1523F8
// https://decomp.me/scratch/qSDro
void func_80155818(HSD_GObj* gobj) {
    Fighter_ActionStateChange_800693AC(gobj, 0x183, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}



// 80155864 152444
// https://decomp.me/scratch/ln57J
void lbl_80155864(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_80151018(gobj);
    }
}



// 801558A0 152480
void lbl_801558A0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 801558E4 1524C4
void lbl_801558E4(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 80155904 1524E4
void lbl_80155904(HSD_GObj* gobj) {
    return;
}



// 80155908 1524E8
// https://decomp.me/scratch/jo0OK
void lbl_80155908(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    if ((--fp->x2364 <= 0.0f) && (fp->x2200_ftcmd_var0 != 0)) {
        func_80155D1C(fp->x1A58_interactedFighter);
        fp->x2200_ftcmd_var0 = 0;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_80151018(gobj);
    }
}



// 80155990 152570
void lbl_80155990(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 801559D4 1525B4
// https://decomp.me/scratch/cRlBe
void lbl_801559D4(HSD_GObj* gobj) {
    Fighter* fp;
    MasterHandAttributes* attr;

    fp = gobj->user_data;
    attr = fp->x10C_ftData->ext_attr;
    func_80085134(gobj);
    func_8015BE40(gobj, &fp->x234C_pos, &fp->x2358_stateVar7, attr->x2C, attr->x28);
}



// 80155A34 152614
// https://decomp.me/scratch/OedGK
void lbl_80155A34(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    if (fp->x2358_stateVar7 == 0.0f) {
        fp->x80_self_vel.z = 0.0f;
        fp->x80_self_vel.y = 0.0f;
        fp->x80_self_vel.x = 0.0f;
    }
}

const f32 neg1 = -1.0f;
