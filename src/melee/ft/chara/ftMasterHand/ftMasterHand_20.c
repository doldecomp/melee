#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

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
    Fighter* fp;
    MasterHandAttributes* attr;
    Vec3 sp1C;
    Vec3 scale;
    s32 unk;

    fp = gobj->user_data;
    jobj = get_jobj(gobj);
    attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(gobj, 0x173, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    func_8015C208(gobj, &sp1C);
    fp->xB0_pos.x = sp1C.x;
    fp->xB0_pos.y = attr->x70;

    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;

    fp->x2340_f32 = attr->x74;
    fp->x23B0 = attr->x7C;

    HSD_JObjGetScale(jobj, &scale);
    fp->x23A4.x = scale.x;
    fp->x23A4.y = scale.y;
    fp->x23A4.z = scale.z;

    fp->x2398.x = scale.x - attr->x78;
    fp->x2398.y = scale.y - attr->x78;
    fp->x2398.z = scale.z - attr->x78;

    fp->x2398.x /= attr->x7C;
    fp->x2398.y /= attr->x7C;
    fp->x2398.z /= attr->x7C;

    scale.x = attr->x78;
    scale.y = attr->x78;
    scale.z = attr->x78;
    HSD_JObjSetScale(jobj, &scale);

    fp->x2200_ftcmd_var0 = 1;
}



// 80153F8C 150B6C
// https://decomp.me/scratch/w6kte
void lbl_80153F8C(HSD_GObj* gobj_arg) {
    HSD_GObj* gobj = gobj_arg;
    Fighter* fp;
    s32 unk;
    Vec3 scale;
    s32 unk2[3];

    fp = gobj->user_data;
    if (fp->x2200_ftcmd_var0 != 0) {
        HSD_JObj* jobj = get_jobj(gobj);
        if (--fp->x23B0 < 0) {
            fp->x2200_ftcmd_var0 = 0;
            scale.x = fp->x23A4.x;
            scale.y = fp->x23A4.y;
            scale.z = fp->x23A4.z;
        } else {
            HSD_JObjGetScale(jobj, &scale);
            scale.x += fp->x2398.x;
            scale.y += fp->x2398.y;
            scale.z += fp->x2398.z;
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
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80154158 150D38
// https://decomp.me/scratch/rgPDD
void lbl_80154158(HSD_GObj* gobj) {
    Fighter* r3_fp;
    MasterHandAttributes* r4_attributes;
    u32 unk[2];

    r3_fp = gobj->user_data;
    if (--r3_fp->x2340_f32 > 0.0f) {
        r4_attributes = r3_fp->x10C_ftData->ext_attr;
        func_8015BF74(gobj, r4_attributes->x58);
    } else {
        r3_fp->x80_self_vel.x = 0.0f;
    }
    func_8015C190(gobj);
}
