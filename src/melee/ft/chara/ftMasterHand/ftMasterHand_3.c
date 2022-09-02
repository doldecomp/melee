#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

#pragma dont_inline on

// 80150C8C 0014D86C
// https://decomp.me/scratch/Nhsvo
void func_80150C8C(HSD_GObj* gobj) {
    Fighter* r31_fp;

    r31_fp = gobj->user_data;
    if ((r31_fp->sa.masterhand.x2258 == 0x155) || (r31_fp->sa.masterhand.x2258 == 0x185)) {
        Fighter_ActionStateChange_800693AC(gobj, 0x185, 0, 0, r31_fp->x894_currentAnimFrame, 1.0f, 0.0f);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 0x185, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
    r31_fp->sa.masterhand.x2258 = 0x185;
}



// 80150D28 0014D908
// https://decomp.me/scratch/ntaE2
void func_80150D28(HSD_GObj* gobj) {
    Fighter* r31_fp;

    r31_fp = gobj->user_data;
    if ((r31_fp->sa.masterhand.x2258 == 0x156) || (r31_fp->sa.masterhand.x2258 == 0x186)) {
        Fighter_ActionStateChange_800693AC(gobj, 0x186, 0, 0, r31_fp->x894_currentAnimFrame, 1.0f, 0.0f);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 0x186, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
    r31_fp->sa.masterhand.x2258 = 0x186;
}



// 80150DC4 0014D9A4
// https://decomp.me/scratch/vZOBB
void func_80150DC4(HSD_GObj* gobj, void* arg1_stateVar2, Vec3* arg2_pos) {
    f32 temp_f1;
    Fighter* r32_fp;
    s32 unk_filler[4];

    r32_fp = gobj->user_data;
    if (r32_fp->sa.masterhand.x2258 == 0x156) {
        if ((r32_fp->sa.masterhand.x2258 == 0x156) || (r32_fp->sa.masterhand.x2258 == 0x186)) {
            Fighter_ActionStateChange_800693AC(gobj, 0x186, 0, 0, r32_fp->x894_currentAnimFrame, 1.0f, 0.0f);
        } else {
            temp_f1 = 0.0f;
            Fighter_ActionStateChange_800693AC(gobj, 0x186, 0, 0, temp_f1, 1.0f, temp_f1);
            func_8006EBA4(gobj);
        }
        r32_fp->sa.masterhand.x2258 = 0x186;
    } else {
        if ((r32_fp->sa.masterhand.x2258 == 0x155) || (r32_fp->sa.masterhand.x2258 == 0x185)) {
            Fighter_ActionStateChange_800693AC(gobj, 0x185, 0, 0, r32_fp->x894_currentAnimFrame, 1.0f, 0.0f);
        } else {
            Fighter_ActionStateChange_800693AC(gobj, 0x185, 0, 0, 0.0f, 1.0f, 0.0f);
            func_8006EBA4(gobj);
        }
        r32_fp->sa.masterhand.x2258 = 0x185;
    }
    r32_fp->x2344_callback = arg1_stateVar2;
    r32_fp->x234C_pos = *arg2_pos;
}



// 80150F00 0014DAE0
// https://decomp.me/scratch/tAkIF
void lbl_80150F00(HSD_GObj* gobj) {
    u32 unk[1];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        fp->sa.masterhand.x2258 = 0x185;
        Fighter_ActionStateChange_800693AC(gobj, 0x185, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
}



// 80150F68 0014DB48
// https://decomp.me/scratch/kHlJR
void lbl_80150F68(HSD_GObj* gobj) {
    Fighter* r31_fp;
    MasterHandAttributes* r30_ft_attributes;
    ftData* r4_ftdata;

    r31_fp = gobj->user_data;
    r4_ftdata = r31_fp->x10C_ftData;
    r30_ft_attributes = r4_ftdata->ext_attr;

    func_80085134(gobj);
    func_8015BE40(gobj, &r31_fp->x234C_pos, &r31_fp->x2358_stateVar7, r30_ft_attributes->x2C, r30_ft_attributes->x28);
}



// 80150FC8 0014DBA8
// https://decomp.me/scratch/8qlZ7
void lbl_80150FC8(HSD_GObj* gobj) {
    Fighter* r4_fp;

    r4_fp = gobj->user_data;
    if (0.0f == r4_fp->x2358_stateVar7) {
        r4_fp->x80_self_vel.z = 0.0f;
        r4_fp->x80_self_vel.y = 0.0f;
        r4_fp->x80_self_vel.x = 0.0f;

        if (r4_fp->x2344_stateVar2) {
            ((void(*)(HSD_GObj*))r4_fp->x2344_stateVar2)(gobj);
        }
    }
}



// 80151018 0014DBF8
// https://decomp.me/scratch/rjK44
void func_80151018(HSD_GObj* gobj) {
    Vec3 sp1C_pos;
    MasterHandAttributes* r5_attributes;
    Fighter* r6_fp;
    Fighter* r31_fp;
    u32 unk[4];

    r6_fp = gobj->user_data;
    r5_attributes = r6_fp->x10C_ftData->ext_attr;
    r6_fp->x2360 = 0;
    sp1C_pos.x = r5_attributes->x30_pos2.x;
    sp1C_pos.y = r5_attributes->x30_pos2.y;
    sp1C_pos.z = 0.0f;
    r6_fp->sa.masterhand.x2258 = 0x186;
    r31_fp = gobj->user_data;
    if (r31_fp->sa.masterhand.x2258 == 0x156) {
        func_80150D28(gobj);
    } else {
        func_80150C8C(gobj);
    }
    r31_fp->x2344_callback = lbl_8014FFDC;
    r31_fp->x234C_pos = sp1C_pos;
}
