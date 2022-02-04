#include "melee/gr/stage.h"

extern struct _StageInfo stage_info;

struct StructNumberAndVecp { s32 number; S32Vec* vec; };
struct StructPairWithStageID { s32 stage_id; s32 regular_number; };

extern f32 degrees_2_radians; // 0.017453f
extern f32 unk_one_half_const_804DBCD8; // 0.5
extern f32 unk_zero_const_804DBCD8; //0.0
extern Vec lbl_803B84C8; 

extern char lbl_804D4A00[1];

extern struct StructPairWithStageID unk_struct_804D49F0;
extern struct StructNumberAndVecp unk_struct_804D49E8;
extern S32Vec unk_arr_of_vectors_803E9960[];

extern f32 lbl_804DBCDC; //-10
extern f32 lbl_804DBCE0; //10
extern f32 lbl_804DBCE4; //100
extern f32 lbl_804DBCE8;

extern s32 func_801C2D24(s32, Vec*);
extern s32 func_80051EC8(Vec*, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32);
extern void func_801C5A84();
extern void func_801C5AA4();
extern void func_80023F28();
extern s32 func_801C28AC(s32, s32, s32*);
extern s32 func_8016B3A0();
extern s32 func_8016B238();


f32 get_cam_bounds_left_offset()
{
    return stage_info.cam_info.cam_bounds_left + stage_info.cam_info.cam_x_offset;
}

f32 get_cam_bounds_right_offset()
{
    return stage_info.cam_info.cam_bounds_right + stage_info.cam_info.cam_x_offset;
}

f32 get_cam_bounds_top_offset()
{
    return stage_info.cam_info.cam_bounds_top + stage_info.cam_info.cam_y_offset;
}

f32 get_cam_bounds_bottom_offset()
{
    return stage_info.cam_info.cam_bounds_bottom + stage_info.cam_info.cam_y_offset;
}

f32 get_cam_pan_angle_radians()
{
    return degrees_2_radians * stage_info.cam_info.cam_pan_degrees;
}

f32 get_cam_max_depth()
{
    return stage_info.cam_info.cam_max_depth;
}

f32 get_cam_zoom_rate()
{
    return stage_info.cam_info.cam_zoom_rate;
}

f32 get_cam_info_x20() {
    return stage_info.cam_info.x20;
}

f32 get_cam_info_x24() {
    return stage_info.cam_info.x24;
}

f32 get_cam_fixed_zoom() {
    return stage_info.cam_info.cam_fixed_zoom;
}

f32 get_cam_track_ratio() {
    return stage_info.cam_info.cam_track_ratio;
}

f32 get_cam_track_smooth() {
    return stage_info.cam_info.cam_track_smooth;
}

f32 get_blast_zone_right_offset() {
    return stage_info.blast_zone.right + stage_info.cam_info.cam_x_offset;
}

f32 get_blast_zone_left_offset() {
    return stage_info.blast_zone.left + stage_info.cam_info.cam_x_offset;
}

f32 get_blast_zone_top_offset() {
    return stage_info.blast_zone.top + stage_info.cam_info.cam_y_offset;
}

f32 get_blast_zone_bottom_offset() {
   return stage_info.blast_zone.bottom + stage_info.cam_info.cam_y_offset;
}

f32 calc_unk_cam_y_80224B98() {
    f32 cam_y_offset = stage_info.cam_info.cam_y_offset;
    f32 y_pos = stage_info.cam_info.cam_bounds_bottom + cam_y_offset + (stage_info.blast_zone.bottom + cam_y_offset);
    return unk_one_half_const_804DBCD8 * y_pos;
}

f32 calc_unk_cam_y_bounds_80224BC4() {

    f32 cam_y_offset = stage_info.cam_info.cam_y_offset;
    f32 cam_bounds_bottom_offset = stage_info.cam_info.cam_bounds_bottom + cam_y_offset;

    f32 y_pos = stage_info.blast_zone.bottom + cam_y_offset + cam_bounds_bottom_offset;
    f32 y_pos_product = unk_one_half_const_804DBCD8 * y_pos;

    return unk_one_half_const_804DBCD8 * (cam_bounds_bottom_offset + y_pos_product);
}

f32 unk_set_vec3_to_cam_offset_80224BF8(Vec *vec3, f32 arg8) {
    vec3->x = stage_info.cam_info.cam_x_offset;
    vec3->y = stage_info.cam_info.cam_y_offset;
    vec3->z = unk_zero_const_804DBCD8;
    return arg8;
}

f32 get_pausecam_zpos_min() { 
    return stage_info.cam_info.pausecam_zpos_min;
}

f32 get_pausecam_zpos_init() {
    return stage_info.cam_info.pausecam_zpos_init;
}

f32 get_pausecam_zpos_max() { 
    return stage_info.cam_info.pausecam_zpos_max;
}

f32 get_cam_angle_radians_up() {
    return degrees_2_radians * stage_info.cam_info.cam_angle_up;
}

f32 get_cam_angle_radians_down() {
    return degrees_2_radians * stage_info.cam_info.cam_angle_down;
}

f32 get_cam_angle_radians_left() {
    return degrees_2_radians * stage_info.cam_info.cam_angle_left;
}

f32 get_cam_angle_radians_right() {
    return degrees_2_radians * stage_info.cam_info.cam_angle_right;
}

void func_80224CAC(Vec *arg0) {

    Vec another_vec = lbl_803B84C8;
    Vec rot_vec;
    
    *arg0 = stage_info.cam_info.fixed_cam_pos;

    rot_vec.x = degrees_2_radians * stage_info.cam_info.fixed_cam_vert_angle;
    rot_vec.y = degrees_2_radians * stage_info.cam_info.fixed_cam_horz_angle;
    rot_vec.z = unk_zero_const_804DBCD8;

    lbvector_ApplyEulerRotation(&another_vec, &rot_vec);

    {
        Vec last_vec;
        f32 temp_f4 = (arg0->z / -another_vec.z);

        last_vec.x = (another_vec.x * temp_f4) + arg0->x;
        last_vec.y = (another_vec.y * temp_f4) + arg0->y;
        last_vec.z = unk_zero_const_804DBCD8;
        *arg0 = last_vec;
    }

}

void set_vec_to_fixed_cam_pos(Vec *arg0) {
    *arg0 = stage_info.cam_info.fixed_cam_pos;
}

f32 get_cam_fixed_fov() {
    return stage_info.cam_info.fixed_cam_fov;
}

BOOL func_80224DC8(s32 arg) {
    return (arg == 0x3b || arg == 0x3f || arg == 0x42 || arg == 0x49 || arg == 0x4c) != 0;
}


void func_80224E38(Vec* arg0, s32 arg1) {   //https://decomp.me/scratch/DCquW  
    func_801C2D24(arg1 + 4, arg0);
}

extern char lbl_803E9940[26];
extern char lbl_804D49F8[8];

#ifdef NON_MATCHING
void func_80224E64(s32 arg0, Vec* arg_vec) {  ///Matched here just can't do strings -- https://decomp.me/scratch/ijCpa
    BOOL bool1;

    f32 counter_f;
    Vec internal_vec;
    f32 zero;

    if (arg0 == -1) {
        __assert(lbl_804D49F8, 360, lbl_803E9940);
    }

    if (arg0 == 4) {
        bool1 = 0;
        for (counter_f = lbl_804DBCDC; counter_f < 100.0f; counter_f += 10.0f) {
            s32 temp_ret = func_80051EC8(&internal_vec, 0, 0, 0, 1, -1, -1, unk_zero_const_804DBCD8, 10.0f + counter_f, unk_zero_const_804DBCD8, counter_f);
            if (temp_ret != 0) {
                bool1 = 1;
                break;
            }
        }

        if (bool1 == 0) {
            for (counter_f = lbl_804DBCDC; counter_f > -100.0f; counter_f -= 10.0f) {
                s32 temp_ret = func_80051EC8(&internal_vec, 0, 0, 0, 1, -1, -1, unk_zero_const_804DBCD8, counter_f, unk_zero_const_804DBCD8, counter_f - 10.0f);

                if (temp_ret != 0) {
                    bool1 = 1;
                    break;
                }
            }
        }

        if (bool1) {
            *arg_vec = internal_vec;
            return;
        }
        zero = unk_zero_const_804DBCD8;
        arg_vec->z = zero;
        arg_vec->y = zero;
        arg_vec->x = zero;
        return;

    }
    func_801C2D24(arg0, arg_vec);

}
#else
asm void func_80224E64(s32 arg0, Vec* arg_vec)   //// matched here: https://decomp.me/scratch/ijCpa
{
    nofralloc
/* 80224E64 00221A44  7C 08 02 A6 */	mflr r0
/* 80224E68 00221A48  90 01 00 04 */	stw r0, 4(r1)
/* 80224E6C 00221A4C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80224E70 00221A50  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 80224E74 00221A54  DB C1 00 30 */	stfd f30, 0x30(r1)
/* 80224E78 00221A58  DB A1 00 28 */	stfd f29, 0x28(r1)
/* 80224E7C 00221A5C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80224E80 00221A60  3B E3 00 00 */	addi r31, r3, 0
/* 80224E84 00221A64  2C 1F FF FF */	cmpwi r31, -1
/* 80224E88 00221A68  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80224E8C 00221A6C  3B C4 00 00 */	addi r30, r4, 0
/* 80224E90 00221A70  40 82 00 18 */	bne lbl_80224EA8
/* 80224E94 00221A74  3C 60 80 3F */	lis r3, lbl_803E9940@ha
/* 80224E98 00221A78  38 A3 99 40 */	addi r5, r3, lbl_803E9940@l
/* 80224E9C 00221A7C  38 6D 93 58 */	addi r3, r13, lbl_804D49F8
/* 80224EA0 00221A80  38 80 01 68 */	li r4, 0x168
/* 80224EA4 00221A84  48 16 33 7D */	bl __assert
lbl_80224EA8:
/* 80224EA8 00221A88  2C 1F 00 04 */	cmpwi r31, 4
/* 80224EAC 00221A8C  40 82 01 00 */	bne lbl_80224FAC
/* 80224EB0 00221A90  C3 A2 C2 FC */	lfs f29, lbl_804DBCDC
/* 80224EB4 00221A94  3B E0 00 00 */	li r31, 0
/* 80224EB8 00221A98  C3 E2 C3 00 */	lfs f31, lbl_804DBCE0
/* 80224EBC 00221A9C  C3 C2 C3 04 */	lfs f30, lbl_804DBCE4
/* 80224EC0 00221AA0  48 00 00 48 */	b lbl_80224F08
lbl_80224EC4:
/* 80224EC4 00221AA4  C0 22 C2 F8 */	lfs f1, unk_zero_const_804DBCD8
/* 80224EC8 00221AA8  FC 80 E8 90 */	fmr f4, f29
/* 80224ECC 00221AAC  EC 5F E8 2A */	fadds f2, f31, f29
/* 80224ED0 00221AB0  38 61 00 10 */	addi r3, r1, 0x10
/* 80224ED4 00221AB4  FC 60 08 90 */	fmr f3, f1
/* 80224ED8 00221AB8  38 80 00 00 */	li r4, 0
/* 80224EDC 00221ABC  38 A0 00 00 */	li r5, 0
/* 80224EE0 00221AC0  38 C0 00 00 */	li r6, 0
/* 80224EE4 00221AC4  38 E0 00 01 */	li r7, 1
/* 80224EE8 00221AC8  39 00 FF FF */	li r8, -1
/* 80224EEC 00221ACC  39 20 FF FF */	li r9, -1
/* 80224EF0 00221AD0  4B E2 CF D9 */	bl func_80051EC8
/* 80224EF4 00221AD4  2C 03 00 00 */	cmpwi r3, 0
/* 80224EF8 00221AD8  41 82 00 0C */	beq lbl_80224F04
/* 80224EFC 00221ADC  3B E0 00 01 */	li r31, 1
/* 80224F00 00221AE0  48 00 00 10 */	b lbl_80224F10
lbl_80224F04:
/* 80224F04 00221AE4  EF BD F8 2A */	fadds f29, f29, f31
lbl_80224F08:
/* 80224F08 00221AE8  FC 1D F0 40 */	fcmpo cr0, f29, f30
/* 80224F0C 00221AEC  41 80 FF B8 */	blt lbl_80224EC4
lbl_80224F10:
/* 80224F10 00221AF0  2C 1F 00 00 */	cmpwi r31, 0
/* 80224F14 00221AF4  40 82 00 60 */	bne lbl_80224F74
/* 80224F18 00221AF8  C3 A2 C2 FC */	lfs f29, lbl_804DBCDC
/* 80224F1C 00221AFC  C3 C2 C3 00 */	lfs f30, lbl_804DBCE0
/* 80224F20 00221B00  C3 E2 C3 08 */	lfs f31, lbl_804DBCE8
/* 80224F24 00221B04  48 00 00 48 */	b lbl_80224F6C
lbl_80224F28:
/* 80224F28 00221B08  C0 22 C2 F8 */	lfs f1, unk_zero_const_804DBCD8
/* 80224F2C 00221B0C  FC 40 E8 90 */	fmr f2, f29
/* 80224F30 00221B10  EC 9D F0 28 */	fsubs f4, f29, f30
/* 80224F34 00221B14  38 61 00 10 */	addi r3, r1, 0x10
/* 80224F38 00221B18  FC 60 08 90 */	fmr f3, f1
/* 80224F3C 00221B1C  38 80 00 00 */	li r4, 0
/* 80224F40 00221B20  38 A0 00 00 */	li r5, 0
/* 80224F44 00221B24  38 C0 00 00 */	li r6, 0
/* 80224F48 00221B28  38 E0 00 01 */	li r7, 1
/* 80224F4C 00221B2C  39 00 FF FF */	li r8, -1
/* 80224F50 00221B30  39 20 FF FF */	li r9, -1
/* 80224F54 00221B34  4B E2 CF 75 */	bl func_80051EC8
/* 80224F58 00221B38  2C 03 00 00 */	cmpwi r3, 0
/* 80224F5C 00221B3C  41 82 00 0C */	beq lbl_80224F68
/* 80224F60 00221B40  3B E0 00 01 */	li r31, 1
/* 80224F64 00221B44  48 00 00 10 */	b lbl_80224F74
lbl_80224F68:
/* 80224F68 00221B48  EF BD F0 28 */	fsubs f29, f29, f30
lbl_80224F6C:
/* 80224F6C 00221B4C  FC 1D F8 40 */	fcmpo cr0, f29, f31
/* 80224F70 00221B50  41 81 FF B8 */	bgt lbl_80224F28
lbl_80224F74:
/* 80224F74 00221B54  2C 1F 00 00 */	cmpwi r31, 0
/* 80224F78 00221B58  41 82 00 20 */	beq lbl_80224F98
/* 80224F7C 00221B5C  80 61 00 10 */	lwz r3, 0x10(r1)
/* 80224F80 00221B60  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80224F84 00221B64  90 7E 00 00 */	stw r3, 0(r30)
/* 80224F88 00221B68  90 1E 00 04 */	stw r0, 4(r30)
/* 80224F8C 00221B6C  80 01 00 18 */	lwz r0, 0x18(r1)
/* 80224F90 00221B70  90 1E 00 08 */	stw r0, 8(r30)
/* 80224F94 00221B74  48 00 00 24 */	b lbl_80224FB8
lbl_80224F98:
/* 80224F98 00221B78  C0 02 C2 F8 */	lfs f0, unk_zero_const_804DBCD8
/* 80224F9C 00221B7C  D0 1E 00 08 */	stfs f0, 8(r30)
/* 80224FA0 00221B80  D0 1E 00 04 */	stfs f0, 4(r30)
/* 80224FA4 00221B84  D0 1E 00 00 */	stfs f0, 0(r30)
/* 80224FA8 00221B88  48 00 00 10 */	b lbl_80224FB8
lbl_80224FAC:
/* 80224FAC 00221B8C  38 7F 00 00 */	addi r3, r31, 0
/* 80224FB0 00221B90  38 9E 00 00 */	addi r4, r30, 0
/* 80224FB4 00221B94  4B F9 DD 71 */	bl func_801C2D24
lbl_80224FB8:
/* 80224FB8 00221B98  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80224FBC 00221B9C  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 80224FC0 00221BA0  CB C1 00 30 */	lfd f30, 0x30(r1)
/* 80224FC4 00221BA4  CB A1 00 28 */	lfd f29, 0x28(r1)
/* 80224FC8 00221BA8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80224FCC 00221BAC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80224FD0 00221BB0  38 21 00 40 */	addi r1, r1, 0x40
/* 80224FD4 00221BB4  7C 08 03 A6 */	mtlr r0
/* 80224FD8 00221BB8  4E 80 00 20 */	blr 
}
#endif

#pragma push
#pragma peephole on
s32 func_80224FDC(Vec *arg0) {   ///https://decomp.me/scratch/hSlaQ
    s32 rand_output;
    s32 counter = 0x15;
    s32 counter2;

    while (counter != 0) {
        if (func_801C2D24(HSD_Randi(counter) + 0x7F, arg0)) { return 1; }
        counter += -1;
    }
    
    counter2 = 4;
    while (counter2 != 0) {
        rand_output = HSD_Randi(counter2);
        counter2 = func_801C2D24(rand_output, arg0);
        
        if (counter2 != 0) { return 1; }
        counter2 = rand_output;
    }
        
    return 0;
}
#pragma pop


#ifdef NON_MATCHING
s32 func_80225074(s32 arg0) {    ////https://decomp.me/scratch/ysONg

    s32 r31;
    s32 spC;

    if (func_8016B238() != 0) { 
        if (((stage_info.unk8C >> 7) & 0x1) || (arg0 == 2)) {
            r31 = 0x12;
        } else {
            r31 = 0x11;
        }
    }
    else if (func_8016B3A0() != 0) {
        if (arg0 == 2) {
            r31 = 0x22;
        }
        else if (arg0 == 1) {
            r31 = 0x64;
        } 
        else {
            r31 = 0x24;
        }
    }
    else if (arg0 == 0) { r31 = 4; }
    else if (arg0 == 3) { r31 = 1; }
    else if (arg0 == 2) { r31 = 2; }
    else if (arg0 == 1) { r31 = 0x44; }
    else {
        __assert(lbl_804D49F8, 0x20E, lbl_804D4A00);
    }

    r31 = func_801C28AC(unk_struct_804D49E8.number, r31, &spC);
    func_80023F28(spC);
    func_801C5A84(spC);
    func_801C5AA4(r31);
    return arg0;
}
#else
asm s32 func_80225074(s32 arg0, s32 arg1)
{
    nofralloc 
    /* 80225074 00221C54  7C 08 02 A6 */	mflr r0
    /* 80225078 00221C58  90 01 00 04 */	stw r0, 4(r1)
    /* 8022507C 00221C5C  94 21 FF E8 */	stwu r1, -0x18(r1)
    /* 80225080 00221C60  93 E1 00 14 */	stw r31, 0x14(r1)
    /* 80225084 00221C64  93 C1 00 10 */	stw r30, 0x10(r1)
    /* 80225088 00221C68  7C 7E 1B 78 */	mr r30, r3
    /* 8022508C 00221C6C  4B F4 61 AD */	bl func_8016B238
    /* 80225090 00221C70  2C 03 00 00 */	cmpwi r3, 0
    /* 80225094 00221C74  41 82 00 30 */	beq lbl_802250C4
    /* 80225098 00221C78  3C 60 80 4A */	lis r3, stage_info@ha
    /* 8022509C 00221C7C  38 63 E6 C8 */	addi r3, r3, stage_info@l
    /* 802250A0 00221C80  88 03 00 8C */	lbz r0, 0x8c(r3)
    /* 802250A4 00221C84  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
    /* 802250A8 00221C88  40 82 00 0C */	bne lbl_802250B4
    /* 802250AC 00221C8C  2C 1E 00 02 */	cmpwi r30, 2
    /* 802250B0 00221C90  40 82 00 0C */	bne lbl_802250BC
    lbl_802250B4:
    /* 802250B4 00221C94  3B E0 00 12 */	li r31, 0x12
    /* 802250B8 00221C98  48 00 00 90 */	b lbl_80225148
    lbl_802250BC:
    /* 802250BC 00221C9C  3B E0 00 11 */	li r31, 0x11
    /* 802250C0 00221CA0  48 00 00 88 */	b lbl_80225148
    lbl_802250C4:
    /* 802250C4 00221CA4  4B F4 62 DD */	bl func_8016B3A0
    /* 802250C8 00221CA8  2C 03 00 00 */	cmpwi r3, 0
    /* 802250CC 00221CAC  41 82 00 2C */	beq lbl_802250F8
    /* 802250D0 00221CB0  2C 1E 00 02 */	cmpwi r30, 2
    /* 802250D4 00221CB4  40 82 00 0C */	bne lbl_802250E0
    /* 802250D8 00221CB8  3B E0 00 22 */	li r31, 0x22
    /* 802250DC 00221CBC  48 00 00 6C */	b lbl_80225148
    lbl_802250E0:
    /* 802250E0 00221CC0  2C 1E 00 01 */	cmpwi r30, 1
    /* 802250E4 00221CC4  40 82 00 0C */	bne lbl_802250F0
    /* 802250E8 00221CC8  3B E0 00 64 */	li r31, 0x64
    /* 802250EC 00221CCC  48 00 00 5C */	b lbl_80225148
    lbl_802250F0:
    /* 802250F0 00221CD0  3B E0 00 24 */	li r31, 0x24
    /* 802250F4 00221CD4  48 00 00 54 */	b lbl_80225148
    lbl_802250F8:
    /* 802250F8 00221CD8  2C 1E 00 00 */	cmpwi r30, 0
    /* 802250FC 00221CDC  40 82 00 0C */	bne lbl_80225108
    /* 80225100 00221CE0  3B E0 00 04 */	li r31, 4
    /* 80225104 00221CE4  48 00 00 44 */	b lbl_80225148
    lbl_80225108:
    /* 80225108 00221CE8  2C 1E 00 03 */	cmpwi r30, 3
    /* 8022510C 00221CEC  40 82 00 0C */	bne lbl_80225118
    /* 80225110 00221CF0  3B E0 00 01 */	li r31, 1
    /* 80225114 00221CF4  48 00 00 34 */	b lbl_80225148
    lbl_80225118:
    /* 80225118 00221CF8  2C 1E 00 02 */	cmpwi r30, 2
    /* 8022511C 00221CFC  40 82 00 0C */	bne lbl_80225128
    /* 80225120 00221D00  3B E0 00 02 */	li r31, 2
    /* 80225124 00221D04  48 00 00 24 */	b lbl_80225148
    lbl_80225128:
    /* 80225128 00221D08  2C 1E 00 01 */	cmpwi r30, 1
    /* 8022512C 00221D0C  40 82 00 0C */	bne lbl_80225138
    /* 80225130 00221D10  3B E0 00 44 */	li r31, 0x44
    /* 80225134 00221D14  48 00 00 14 */	b lbl_80225148
    lbl_80225138:
    /* 80225138 00221D18  38 6D 93 58 */	addi r3, r13, lbl_804D49F8
    /* 8022513C 00221D1C  38 80 02 0E */	li r4, 0x20e
    /* 80225140 00221D20  38 AD 93 60 */	addi r5, r13, lbl_804D4A00
    /* 80225144 00221D24  48 16 30 DD */	bl __assert
    lbl_80225148:
    /* 80225148 00221D28  80 6D 93 48 */	lwz r3, unk_struct_804D49E8
    /* 8022514C 00221D2C  38 9F 00 00 */	addi r4, r31, 0
    /* 80225150 00221D30  38 A1 00 0C */	addi r5, r1, 0xc
    /* 80225154 00221D34  4B F9 D7 59 */	bl func_801C28AC
    /* 80225158 00221D38  7C 60 1B 78 */	mr r0, r3
    /* 8022515C 00221D3C  80 61 00 0C */	lwz r3, 0xc(r1)
    /* 80225160 00221D40  7C 1F 03 78 */	mr r31, r0
    /* 80225164 00221D44  4B DF ED C5 */	bl func_80023F28
    /* 80225168 00221D48  80 61 00 0C */	lwz r3, 0xc(r1)
    /* 8022516C 00221D4C  4B FA 09 19 */	bl func_801C5A84
    /* 80225170 00221D50  7F E3 FB 78 */	mr r3, r31
    /* 80225174 00221D54  4B FA 09 31 */	bl func_801C5AA4
    /* 80225178 00221D58  7F C3 F3 78 */	mr r3, r30
    /* 8022517C 00221D5C  80 01 00 1C */	lwz r0, 0x1c(r1)
    /* 80225180 00221D60  83 E1 00 14 */	lwz r31, 0x14(r1)
    /* 80225184 00221D64  83 C1 00 10 */	lwz r30, 0x10(r1)
    /* 80225188 00221D68  38 21 00 18 */	addi r1, r1, 0x18
    /* 8022518C 00221D6C  7C 08 03 A6 */	mtlr r0
    /* 80225190 00221D70  4E 80 00 20 */	blr 
}
#endif

#pragma push
#pragma peephole on
s32 func_80225194() {  
    return unk_struct_804D49E8.number;
}

s32 func_8022519C(s32 arg0) {
    return unk_arr_of_vectors_803E9960[arg0].x;
}

s32 func_802251B4(s32 arg0, s32 arg1) {
    return func_801C06B8(unk_arr_of_vectors_803E9960[arg0].x);
}

void func_802251E8(s32 arg0, s32* unused) {
    struct StructPairWithStageID local_data;

    unk_struct_804D49E8.number = arg0;
    unk_struct_804D49E8.vec = &unk_arr_of_vectors_803E9960[arg0];

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.vec->x;
    local_data.regular_number = unk_struct_804D49E8.number;
    
    func_801C0754(&local_data); 
}



void func_8022524C() {
    struct StructPairWithStageID local_data;

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.vec->x;
    local_data.regular_number = unk_struct_804D49E8.number;
    
    func_801C0800(&local_data); 
}

void func_80225298() {
    struct StructPairWithStageID local_data;

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.vec->x;
    local_data.regular_number = unk_struct_804D49E8.number;
    
    func_801C0F78(&local_data); 
}

void func_802252E4(s32 arg0, s32 unused) {
    struct StructPairWithStageID local_data;

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.vec->x;
    local_data.regular_number = arg0;
    
    func_801C0FB8(&local_data); 
}

void func_8022532C(s32 arg0, s32 arg1) {
    struct StructPairWithStageID local_data;

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.vec->x;
    local_data.regular_number = arg0;
    
    func_801C1074(&local_data, arg1); 
}

