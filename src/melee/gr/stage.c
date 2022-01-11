#include "melee/gr/stage.h"

extern struct _StageInfo stage_info;

extern f32 degrees_2_radians; // 0.017453f
extern f32 unk_one_half_const_804DBCD8; // 0.5
extern f32 unk_zero_const_804DBCD8; //0.0
extern Vec lbl_803B84C8; 
extern void func_801C2D24(s32 arg0, s32 arg1);

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

