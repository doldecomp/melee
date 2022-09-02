#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80151428 14E008
// https://decomp.me/scratch/mNdcr
// probably isCrazyHandLoaded func
u32 lbl_80151428(Vec* vec) {
    HSD_GObj* fetched_gobj;
    // Fighter* ft_userdata;

    fetched_gobj = func_8015C3E8(0x1B); // probably attempt to find crazy hand func.
    // ft_userdata = ((Fighter*) temp_r3->user_data);
    if (fetched_gobj) {
        func_8000B1CC(((Fighter*) fetched_gobj->user_data)->x5E8_fighterBones[5].x0_jobj, 0, vec);
        return 1;
    }
    return 0;
}



// 80151484 14E064
// https://decomp.me/scratch/0vIXi
inline void func_80151484_inline1(HSD_GObj* gobj) {
    Fighter* r29_fp = gobj->user_data;
    MasterHandAttributes* temp_r30 = r29_fp->x10C_ftData->ext_attr;
    r29_fp->x80_self_vel.z = 0.0f;
    r29_fp->x80_self_vel.y = 0.0f;
    r29_fp->x80_self_vel.x = 0.0f;
    func_802F046C(r29_fp->x2374);
    func_802F046C(r29_fp->x2378);
    func_802F046C(r29_fp->x237C);
    func_802F046C(r29_fp->x2380);
    r29_fp->x2374 = 0;
    r29_fp->x2378 = 0;
    r29_fp->x237C = 0;
    r29_fp->x2380 = 0;
    func_800236B8(r29_fp->x2368);
    func_800236B8(r29_fp->x236C);
    func_800236B8(r29_fp->x2370);
    if (r29_fp->x2360) {
        func_80155D1C(r29_fp->x1A58_interactedFighter);
    }
    r29_fp->x80_self_vel.y = temp_r30->x14C;
    r29_fp->x80_self_vel.z = temp_r30->x154;
    r29_fp->x2348_stateVar3 = (s32) temp_r30->x15C;
}

void func_80151484(HSD_GObj* gobj) {
    s32 unused[2];
    Fighter* r3_fp;

    r3_fp = gobj->user_data;
    r3_fp->x2200_ftcmd_var0 = 0;

    func_80151484_inline1(gobj);

    Fighter_ActionStateChange_800693AC(gobj, 0x158, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);

    // r3_fp now stored in r28
    func_800881D8(r3_fp, 0x4E217, 0x7F, 0x40);
    func_80088148(r3_fp, 0x4E218, 0x7F, 0x40);
    r3_fp->x23B4 = 0;
    r3_fp->x23B8 = 0;
}



// 801515B8 14E198
// https://decomp.me/scratch/I5KfO
void lbl_801515B8(HSD_GObj* gobj) {
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;
    Fighter* r31_fp;
    MasterHandAttributes* r4_attributes;

    r31_fp = gobj->user_data;
    if (r31_fp->x2200_ftcmd_var0) {
        r4_attributes = r31_fp->x10C_ftData->ext_attr;
        temp_r3 = r31_fp->x23B4 + 1;
        r31_fp->x23B4 = temp_r3;
        if (temp_r3 <= r4_attributes->x144) {
            func_8002438C(0x81652);
        } else {
            temp_r3_2 = r31_fp->x23B8 + 1;
            r31_fp->x23B8 = temp_r3_2;
            if (temp_r3_2 <= r4_attributes->x148) {
                func_8002438C(0x81653);
            }
        }
        r31_fp->x2200_ftcmd_var0 = 0U;
    }

    // x2348_stateVar3 does that make sense if its u32?
    if ((s32)r31_fp->x2348_stateVar3 > 0 && !ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ActionStateChange_800693AC(gobj, 0x159, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
    temp_r0 = r31_fp->x2348_stateVar3 - 1;

    r31_fp->x2348_stateVar3 = temp_r0;
    if (temp_r0) {
        return;
    }
    func_800D4F24(gobj, 0);
}



// 801516B4 14E294
// https://decomp.me/scratch/AmIVW
void lbl_801516B4(HSD_GObj* gobj) {
    f32 temp_f1;
    s32 temp_cr0_eq;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;
    Fighter* r31_fp;
    MasterHandAttributes* r4_attributes;

    r31_fp = gobj->user_data;
    if ((u32) r31_fp->x2200_ftcmd_var0 != 0U) {
        r4_attributes = r31_fp->x10C_ftData->ext_attr;
        temp_r3 = r31_fp->x23B4 + 1;
        r31_fp->x23B4 = temp_r3;
        if (temp_r3 <= (s32) r4_attributes->x144) {
            func_8002438C(0x81652);
        } else {
            temp_r3_2 = r31_fp->x23B8 + 1;
            r31_fp->x23B8 = temp_r3_2;
            if (temp_r3_2 <= (s32) r4_attributes->x148) {
                func_8002438C(0x81653);
            }
        }
        r31_fp->x2200_ftcmd_var0 = 0U;
    }
    if (((s32) r31_fp->x2348_stateVar3 > 0) && !ftAnim_IsFramesRemaining(gobj)) {
        temp_f1 = 0.0f;
        Fighter_ActionStateChange_800693AC(gobj, 0x159, 0, 0, temp_f1, 1.0f, temp_f1);
        func_8006EBA4(gobj);
    }
    temp_r0 = r31_fp->x2348_stateVar3 - 1;
    // temp_cr0_eq = ;
    r31_fp->x2348_stateVar3 = temp_r0;
    if (temp_r0 == 0) {
        func_800D4F24(gobj, 0);
    }
}
