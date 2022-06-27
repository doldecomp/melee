#include "ftMasterHand.h"

// 80153D28 150908
void lbl_80153D28(HSD_GObj* gobj) {
    return;
}



// 80153D2C 15090C
// https://decomp.me/scratch/RXqaJ
inline HSD_JObj* get_jobj(HSD_GObj* gobj) {
    return gobj->hsd_obj;
}

void lbl_80153D2C(HSD_GObj* gobj) {
    HSD_JObj* jobj;
    Fighter* ft;
    MasterHandAttributes* attr;
    Vec3 sp1C;
    Vec3 scale;
    s32 unk;

    ft = gobj->user_data;
    jobj = get_jobj(gobj);
    attr = ft->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(gobj, 0x173, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    func_8015C208(gobj, &sp1C);
    ft->xB0_pos.x = sp1C.x;
    ft->xB0_pos.y = attr->x70;

    ft->x80_self_vel.z = 0.0f;
    ft->x80_self_vel.y = 0.0f;
    ft->x80_self_vel.x = 0.0f;

    ft->x2340_f32 = attr->x74;
    ft->x23B0 = attr->x7C;

    HSD_JObjGetScale(jobj, &scale);
    ft->x23A4.x = scale.x;
    ft->x23A4.y = scale.y;
    ft->x23A4.z = scale.z;

    ft->x2398.x = scale.x - attr->x78;
    ft->x2398.y = scale.y - attr->x78;
    ft->x2398.z = scale.z - attr->x78;

    ft->x2398.x /= attr->x7C;
    ft->x2398.y /= attr->x7C;
    ft->x2398.z /= attr->x7C;

    scale.x = attr->x78;
    scale.y = attr->x78;
    scale.z = attr->x78;
    HSD_JObjSetScale(jobj, &scale);

    ft->x2200_ftcmd_var0 = 1;
}



// 80153F8C 150B6C
// https://decomp.me/scratch/w6kte
void lbl_80153F8C(HSD_GObj* gobj_arg) {
    HSD_GObj* gobj = gobj_arg;
    Fighter* ft;
    s32 unk;
    Vec3 scale;
    s32 unk2[3];

    ft = gobj->user_data;
    if (ft->x2200_ftcmd_var0 != 0) {
        HSD_JObj* jobj = get_jobj(gobj);
        if (--ft->x23B0 < 0) {
            ft->x2200_ftcmd_var0 = 0;
            scale.x = ft->x23A4.x;
            scale.y = ft->x23A4.y;
            scale.z = ft->x23A4.z;
        } else {
            HSD_JObjGetScale(jobj, &scale);
            scale.x += ft->x2398.x;
            scale.y += ft->x2398.y;
            scale.z += ft->x2398.z;
        }
        HSD_JObjSetScale(jobj, &scale);
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ((Fighter*)gobj->user_data)->x80_self_vel.x = 0.0f;
        func_80151018(gobj);
    }
}



// 80154114 150CF4
void lbl_80154114(HSD_GObj* arg0) {
    Fighter* ft = arg0->user_data;
    if (Player_GetPlayerSlotType(ft->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80154158 150D38
// https://decomp.me/scratch/rgPDD
void lbl_80154158(HSD_GObj* gobj) {
    Fighter* r3_ft_userdata;
    MasterHandAttributes* r4_attributes;
    u32 unk[2];

    r3_ft_userdata = gobj->user_data;
    if (--r3_ft_userdata->x2340_f32 > 0.0f) {
        r4_attributes = r3_ft_userdata->x10C_ftData->ext_attr;
        func_8015BF74(gobj, r4_attributes->x58);
    } else {
        r3_ft_userdata->x80_self_vel.x = 0.0f;
    }
    func_8015C190(gobj);
}
