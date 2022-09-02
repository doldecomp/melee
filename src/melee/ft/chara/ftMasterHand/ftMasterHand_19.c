#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80153AEC 1506CC
void lbl_80153AEC(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_80151018(gobj);
    }
}



// 80153B28 150708
void lbl_80153B28(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 80153B6C 15074C
void lbl_80153B6C(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 80153B8C 15076C
void lbl_80153B8C(HSD_GObj* gobj) {
    return;
}



// 80153B90 150770
// https://decomp.me/scratch/vgHNv
void lbl_80153B90(HSD_GObj* arg0) {
    Fighter* temp_r31;
    MasterHandAttributes* temp_r30;
    Vec3 sp10;
    s32 unk;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(arg0, 0x172, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    temp_r31->x2340_f32 = temp_r30->x6C;
    func_8015C208(arg0, &sp10);
    temp_r31->xB0_pos.x = sp10.x;
    temp_r31->xB0_pos.y = temp_r30->x68;
    temp_r31->x80_self_vel.z = 0.0f;
    temp_r31->x80_self_vel.y = 0.0f;
    temp_r31->x80_self_vel.x = 0.0f;
}



// 80153C48 150828
// https://decomp.me/scratch/NrDG9
void lbl_80153C48(HSD_GObj* arg0) {
    s32 unk[2];
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        ((Fighter*)arg0->user_data)->x80_self_vel.x = 0.0f;
        func_80151018(arg0);
    }
}



// 80153C90 150870
// https://decomp.me/scratch/ijnCv
void lbl_80153C90(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80153CD4 1508B4
// https://decomp.me/scratch/qCZ0G
void lbl_80153CD4(HSD_GObj* gobj) {
    Fighter* r4_fp;

    r4_fp = gobj->user_data;
    if (--r4_fp->x2340_f32 > 0.0f) {
        func_8015BF74(gobj, ((MasterHandAttributes*)r4_fp->x10C_ftData->ext_attr)->x58);
    } else {
        r4_fp->x80_self_vel.x = 0.0f;
    }
}
