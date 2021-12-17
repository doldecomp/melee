#include "melee/gr/stage.h"

extern struct _StageInfo stage_info;

extern f32 degrees_2_radians; // 0.017453f
extern f32 unk_one_half_const_804DBCD8; // 0.5
extern f32 unk_zero_const_804DBCD8; //0.0
extern Vec lbl_803B84C8; 
extern void func_801C2D24(s32 arg0, s32 arg1);

// char *lbl_803E9940 = "no!=St_Player_InitPos_None";
// extern char *lbl_803E9940[];
extern s32 lbl_804D49F8;
extern f32 lbl_804DBCDC;
extern f32 lbl_804DBCE0;
extern f32 lbl_804DBCE4;
extern f32 lbl_804DBCE8;
extern void func_80051EC8();

extern s32 lbl_804D49E8;

extern S32Vec lbl_803E9960[];


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

    func_8000E138(&another_vec, &rot_vec);

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

asm s32 func_80224DC8(s32 arg0) {
    nofralloc
    /* 80224DC8 002219A8  2C 03 00 3B */	cmpwi r3, 0x3b
    /* 80224DCC 002219AC  38 00 00 01 */	li r0, 1
    /* 80224DD0 002219B0  7C 04 03 78 */	mr r4, r0
    /* 80224DD4 002219B4  7C 05 03 78 */	mr r5, r0
    /* 80224DD8 002219B8  7C 06 03 78 */	mr r6, r0
    /* 80224DDC 002219BC  41 82 00 10 */	beq lbl_80224DEC
    /* 80224DE0 002219C0  2C 03 00 3F */	cmpwi r3, 0x3f
    /* 80224DE4 002219C4  41 82 00 08 */	beq lbl_80224DEC
    /* 80224DE8 002219C8  38 C0 00 00 */	li r6, 0
    lbl_80224DEC:
    /* 80224DEC 002219CC  2C 06 00 00 */	cmpwi r6, 0
    /* 80224DF0 002219D0  40 82 00 10 */	bne lbl_80224E00
    /* 80224DF4 002219D4  2C 03 00 42 */	cmpwi r3, 0x42
    /* 80224DF8 002219D8  41 82 00 08 */	beq lbl_80224E00
    /* 80224DFC 002219DC  38 A0 00 00 */	li r5, 0
    lbl_80224E00:
    /* 80224E00 002219E0  2C 05 00 00 */	cmpwi r5, 0
    /* 80224E04 002219E4  40 82 00 10 */	bne lbl_80224E14
    /* 80224E08 002219E8  2C 03 00 49 */	cmpwi r3, 0x49
    /* 80224E0C 002219EC  41 82 00 08 */	beq lbl_80224E14
    /* 80224E10 002219F0  38 80 00 00 */	li r4, 0
    lbl_80224E14:
    /* 80224E14 002219F4  2C 04 00 00 */	cmpwi r4, 0
    /* 80224E18 002219F8  40 82 00 10 */	bne lbl_80224E28
    /* 80224E1C 002219FC  2C 03 00 4C */	cmpwi r3, 0x4c
    /* 80224E20 00221A00  41 82 00 08 */	beq lbl_80224E28
    /* 80224E24 00221A04  38 00 00 00 */	li r0, 0
    lbl_80224E28:
    /* 80224E28 00221A08  7C 60 00 D0 */	neg r3, r0
    /* 80224E2C 00221A0C  30 03 FF FF */	addic r0, r3, -1
    /* 80224E30 00221A10  7C 60 19 10 */	subfe r3, r0, r3
    /* 80224E34 00221A14  4E 80 00 20 */	blr 
}

asm void func_80224E38(s32 arg0, s32 arg1) {
    nofralloc
    /* 80224E38 00221A18  7C 08 02 A6 */	mflr r0
    /* 80224E3C 00221A1C  90 01 00 04 */	stw r0, 4(r1)
    /* 80224E40 00221A20  38 03 00 00 */	addi r0, r3, 0
    /* 80224E44 00221A24  38 64 00 04 */	addi r3, r4, 4
    /* 80224E48 00221A28  94 21 FF F8 */	stwu r1, -8(r1)
    /* 80224E4C 00221A2C  7C 04 03 78 */	mr r4, r0
    /* 80224E50 00221A30  4B F9 DE D5 */	bl func_801C2D24
    /* 80224E54 00221A34  80 01 00 0C */	lwz r0, 0xc(r1)
    /* 80224E58 00221A38  38 21 00 08 */	addi r1, r1, 8
    /* 80224E5C 00221A3C  7C 08 03 A6 */	mtlr r0
    /* 80224E60 00221A40  4E 80 00 20 */	blr 
}

// asm void func_80224E64() {
//     nofralloc
// /* 80224E64 00221A44  7C 08 02 A6 */	mflr r0
// /* 80224E68 00221A48  90 01 00 04 */	stw r0, 4(r1)
// /* 80224E6C 00221A4C  94 21 FF C0 */	stwu r1, -0x40(r1)
// /* 80224E70 00221A50  DB E1 00 38 */	stfd f31, 0x38(r1)
// /* 80224E74 00221A54  DB C1 00 30 */	stfd f30, 0x30(r1)
// /* 80224E78 00221A58  DB A1 00 28 */	stfd f29, 0x28(r1)
// /* 80224E7C 00221A5C  93 E1 00 24 */	stw r31, 0x24(r1)
// /* 80224E80 00221A60  3B E3 00 00 */	addi r31, r3, 0
// /* 80224E84 00221A64  2C 1F FF FF */	cmpwi r31, -1
// /* 80224E88 00221A68  93 C1 00 20 */	stw r30, 0x20(r1)
// /* 80224E8C 00221A6C  3B C4 00 00 */	addi r30, r4, 0
// /* 80224E90 00221A70  40 82 00 18 */	bne lbl_80224EA8
// /* 80224E94 00221A74  3C 60 80 3F */	lis r3, lbl_803E9940
// /* 80224E98 00221A78  38 A3 99 40 */	addi r5, r3, lbl_803E9940
// /* 80224E9C 00221A7C  38 6D 93 58 */	addi r3, r13, lbl_804D49F8
// /* 80224EA0 00221A80  38 80 01 68 */	li r4, 0x168
// /* 80224EA4 00221A84  48 16 33 7D */	bl __assert
// lbl_80224EA8:
// /* 80224EA8 00221A88  2C 1F 00 04 */	cmpwi r31, 4
// /* 80224EAC 00221A8C  40 82 01 00 */	bne lbl_80224FAC
// /* 80224EB0 00221A90  C3 A2 C2 FC */	lfs f29, lbl_804DBCDC
// /* 80224EB4 00221A94  3B E0 00 00 */	li r31, 0
// /* 80224EB8 00221A98  C3 E2 C3 00 */	lfs f31, lbl_804DBCE0
// /* 80224EBC 00221A9C  C3 C2 C3 04 */	lfs f30, lbl_804DBCE4
// /* 80224EC0 00221AA0  48 00 00 48 */	b lbl_80224F08
// lbl_80224EC4:
// /* 80224EC4 00221AA4  C0 22 C2 F8 */	lfs f1, unk_zero_const_804DBCD8
// /* 80224EC8 00221AA8  FC 80 E8 90 */	fmr f4, f29
// /* 80224ECC 00221AAC  EC 5F E8 2A */	fadds f2, f31, f29
// /* 80224ED0 00221AB0  38 61 00 10 */	addi r3, r1, 0x10
// /* 80224ED4 00221AB4  FC 60 08 90 */	fmr f3, f1
// /* 80224ED8 00221AB8  38 80 00 00 */	li r4, 0
// /* 80224EDC 00221ABC  38 A0 00 00 */	li r5, 0
// /* 80224EE0 00221AC0  38 C0 00 00 */	li r6, 0
// /* 80224EE4 00221AC4  38 E0 00 01 */	li r7, 1
// /* 80224EE8 00221AC8  39 00 FF FF */	li r8, -1
// /* 80224EEC 00221ACC  39 20 FF FF */	li r9, -1
// /* 80224EF0 00221AD0  4B E2 CF D9 */	bl func_80051EC8
// /* 80224EF4 00221AD4  2C 03 00 00 */	cmpwi r3, 0
// /* 80224EF8 00221AD8  41 82 00 0C */	beq lbl_80224F04
// /* 80224EFC 00221ADC  3B E0 00 01 */	li r31, 1
// /* 80224F00 00221AE0  48 00 00 10 */	b lbl_80224F10
// lbl_80224F04:
// /* 80224F04 00221AE4  EF BD F8 2A */	fadds f29, f29, f31
// lbl_80224F08:
// /* 80224F08 00221AE8  FC 1D F0 40 */	fcmpo cr0, f29, f30
// /* 80224F0C 00221AEC  41 80 FF B8 */	blt lbl_80224EC4
// lbl_80224F10:
// /* 80224F10 00221AF0  2C 1F 00 00 */	cmpwi r31, 0
// /* 80224F14 00221AF4  40 82 00 60 */	bne lbl_80224F74
// /* 80224F18 00221AF8  C3 A2 C2 FC */	lfs f29, lbl_804DBCDC
// /* 80224F1C 00221AFC  C3 C2 C3 00 */	lfs f30, lbl_804DBCE0
// /* 80224F20 00221B00  C3 E2 C3 08 */	lfs f31, lbl_804DBCE8
// /* 80224F24 00221B04  48 00 00 48 */	b lbl_80224F6C
// lbl_80224F28:
// /* 80224F28 00221B08  C0 22 C2 F8 */	lfs f1, unk_zero_const_804DBCD8
// /* 80224F2C 00221B0C  FC 40 E8 90 */	fmr f2, f29
// /* 80224F30 00221B10  EC 9D F0 28 */	fsubs f4, f29, f30
// /* 80224F34 00221B14  38 61 00 10 */	addi r3, r1, 0x10
// /* 80224F38 00221B18  FC 60 08 90 */	fmr f3, f1
// /* 80224F3C 00221B1C  38 80 00 00 */	li r4, 0
// /* 80224F40 00221B20  38 A0 00 00 */	li r5, 0
// /* 80224F44 00221B24  38 C0 00 00 */	li r6, 0
// /* 80224F48 00221B28  38 E0 00 01 */	li r7, 1
// /* 80224F4C 00221B2C  39 00 FF FF */	li r8, -1
// /* 80224F50 00221B30  39 20 FF FF */	li r9, -1
// /* 80224F54 00221B34  4B E2 CF 75 */	bl func_80051EC8
// /* 80224F58 00221B38  2C 03 00 00 */	cmpwi r3, 0
// /* 80224F5C 00221B3C  41 82 00 0C */	beq lbl_80224F68
// /* 80224F60 00221B40  3B E0 00 01 */	li r31, 1
// /* 80224F64 00221B44  48 00 00 10 */	b lbl_80224F74
// lbl_80224F68:
// /* 80224F68 00221B48  EF BD F0 28 */	fsubs f29, f29, f30
// lbl_80224F6C:
// /* 80224F6C 00221B4C  FC 1D F8 40 */	fcmpo cr0, f29, f31
// /* 80224F70 00221B50  41 81 FF B8 */	bgt lbl_80224F28
// lbl_80224F74:
// /* 80224F74 00221B54  2C 1F 00 00 */	cmpwi r31, 0
// /* 80224F78 00221B58  41 82 00 20 */	beq lbl_80224F98
// /* 80224F7C 00221B5C  80 61 00 10 */	lwz r3, 0x10(r1)
// /* 80224F80 00221B60  80 01 00 14 */	lwz r0, 0x14(r1)
// /* 80224F84 00221B64  90 7E 00 00 */	stw r3, 0(r30)
// /* 80224F88 00221B68  90 1E 00 04 */	stw r0, 4(r30)
// /* 80224F8C 00221B6C  80 01 00 18 */	lwz r0, 0x18(r1)
// /* 80224F90 00221B70  90 1E 00 08 */	stw r0, 8(r30)
// /* 80224F94 00221B74  48 00 00 24 */	b lbl_80224FB8
// lbl_80224F98:
// /* 80224F98 00221B78  C0 02 C2 F8 */	lfs f0, unk_zero_const_804DBCD8
// /* 80224F9C 00221B7C  D0 1E 00 08 */	stfs f0, 8(r30)
// /* 80224FA0 00221B80  D0 1E 00 04 */	stfs f0, 4(r30)
// /* 80224FA4 00221B84  D0 1E 00 00 */	stfs f0, 0(r30)
// /* 80224FA8 00221B88  48 00 00 10 */	b lbl_80224FB8
// lbl_80224FAC:
// /* 80224FAC 00221B8C  38 7F 00 00 */	addi r3, r31, 0
// /* 80224FB0 00221B90  38 9E 00 00 */	addi r4, r30, 0
// /* 80224FB4 00221B94  4B F9 DD 71 */	bl func_801C2D24
// lbl_80224FB8:
// /* 80224FB8 00221B98  80 01 00 44 */	lwz r0, 0x44(r1)
// /* 80224FBC 00221B9C  CB E1 00 38 */	lfd f31, 0x38(r1)
// /* 80224FC0 00221BA0  CB C1 00 30 */	lfd f30, 0x30(r1)
// /* 80224FC4 00221BA4  CB A1 00 28 */	lfd f29, 0x28(r1)
// /* 80224FC8 00221BA8  83 E1 00 24 */	lwz r31, 0x24(r1)
// /* 80224FCC 00221BAC  83 C1 00 20 */	lwz r30, 0x20(r1)
// /* 80224FD0 00221BB0  38 21 00 40 */	addi r1, r1, 0x40
// /* 80224FD4 00221BB4  7C 08 03 A6 */	mtlr r0
// /* 80224FD8 00221BB8  4E 80 00 20 */	blr 
// }


// s32 func_80224FDC(Vec *arg0) {
//     s32 rand_output;
//     s32 counter = 0x15;
//     s32 counter2;

//     while (counter != 0) {
//         if (func_801C2D24(HSD_Randi(counter) + 0x7F, arg0)) { return 1; }
//         counter += -1;
//     }
    
//     counter2 = 4;
//     while (counter2 != 0) {
//         rand_output = HSD_Randi(counter2);
//         counter2 = func_801C2D24(rand_output, arg0);
        
//         if (counter2 != 0) { return 1; }
//         counter2 = rand_output;
//     }
        
//     return 0;
    
// }

///func_80225074 HERE


///func_80225194 HERE
// s32 func_80225194() {   /// matching but can't compile a match because other functions above
//     return lbl_804D49E8;
// }


// s32 func_8022519C(s32 arg0) {
//     return lbl_803E9960[arg0].x;
// }

// s32 func_802251B4(s32 arg0, s32 arg1) {
//     return func_801C06B8(lbl_803E9960[arg0].x);
// }

///////////////func_802251E8 HERE//////////////////

// struct S32Vec { s32 x; s32 y; s32 z;  };
// struct Pair { s32 stage_id; s32 regular_number; };


// struct SpecialStruct { s32 number; struct S32Vec* vec; };  // 2nd var is pointer to 12 bytes probably vec

// extern func_801C0754(struct Pair*);                    /* extern */
// extern struct SpecialStruct lbl_804D49E8;
// extern s32 lbl_804D49F0;
// extern s32 lbl_804D49F4;

// extern struct S32Vec lbl_803E9960[];  /// 12 bytes for sure

// void func_802251E8(s32 arg0) {
//     struct Pair  sp10;

//     struct SpecialStruct *rawr;


//     lbl_804D49E8.number = arg0;
//     lbl_804D49E8.vec = &lbl_803E9960[arg0];
//     sp10.stage_id = lbl_804D49F0;
//     sp10.regular_number = lbl_804D49F4;

//     sp10.stage_id = lbl_804D49E8.vec->x;

//     sp10.regular_number = lbl_804D49E8.number;

    
//     func_801C0754(&sp10);
// }


//////////////////  These last 4 functions are all similar to the above function, 
///////////////// should be able to get them to match after compiling
///func_8022524C HERE

///func_80225298 HERE

///func_802252E4 HERE

///func_8022532C HERE