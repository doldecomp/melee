#ifndef MELEE_IF_IFSTATUS_H
#define MELEE_IF_IFSTATUS_H

#include <platform.h>

#include "pl/player.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/jobj.h>
#include <baselib/tobj.h>

typedef struct _HudFlags {
    u8 explode_animation : 1;
    u8 unk40 : 1;
    u8 force_digit_shake : 1;
    u8 unk10 : 1;
    u8 hide_all_digits : 1;
    u8 animation_status_id : 2;
    u8 unk1 : 1;
} HudFlags;

typedef struct _UnknownClassTypeE {
    s32 padding[0x24];
    HSD_JObj* unk28;
} UnknownClassTypeE;

typedef struct _HudValue {
    // pointer to "unknown class type E"
    // 0x00
    HSD_GObj* HUD_parent_entity;
    // probably a pointer to "unknown class type E"
    // 0x04
    HSD_GObj* next;
    // represents players 1-6
    // TODO: list if this 0 indexed, or what
    // 0x08
    u8 player_slot;
    // 0x09
    u8 unk9;
    // damage as int
    // 0x0A
    u16 damage_percent;
    // 0x0C
    u16 old_damage;
    // 0x0E
    u8 damage_from_last_attack;
    // 0x0F
    u8 frames_of_shake_remaining;
    // 0x10
    HudFlags flags;
    // 0x14
    f32 hundreds_digit_x_translation;
    // 0x18
    f32 tens_digit_x_translation;
    // 0x1C
    f32 ones_digit_x_translation;
    // 0x20
    f32 percent_sign_x_translation;
    // 0x24
    f32 hundreds_digit_y_translation;
    // 0x28
    f32 tens_digit_y_translation;
    f32 ones_digit_y_translation;
    f32 percent_sign_y_translation;
    f32 hundreds_x_velocity;
    f32 hundreds_y_velocity;
    f32 tens_x_velocity;
    f32 tens_y_velocity;
    f32 ones_x_velocity;
    f32 ones_y_velocity;
    f32 percent_sign_x_velocity;
    f32 percent_sign_y_velocity;
    HSD_JObj* hundreds_jobj;
    HSD_JObj* tens_jobj;
    HSD_JObj* ones_jobj;
    HSD_JObj* percent_sign_jobj;
} HudValue;

typedef struct _HudIndex {
    HudValue players[6];
    // 258 unk
    HSD_Joint* unk258;
    // 0x25c
    void* jobj_desc_parent;
    // 0x260
    HSD_AnimJoint* janim_selection_joints;
    // 0x264
    void* janim_selection_textures;
    // 0x268 null?
    void* unk268;
    void* unk26C;
    void* unk270;
    void* unk274;
    // 8 elements of size 0x28, what is this?
} HudIndex;

typedef struct _Element_803F9628_Obj_14 {
    s32 padding[6];
    s32 unk1C;
} Element_803F9628_Obj_14;

typedef struct _Element_803F9628 {
    // 0x00
    // maybe?
    HSD_GObj* unk0;
    // 0x04
    u32 unk4;
    // 0x08
    void* unk8;
    // 0x0C
    // flags?
    u32 unkC;
    // 0x10
    // flags?
    u32 unk10;
    // 0x14
    s32 unk14;
    // 0x18
    u32 unk18;
    // 0x1C
    u32 unk1C;
    // 0x20
    u32 unk20;
    // 0x24
    u32 unk24;
    // 0x28
    // u32 unk40;
} Element_803F9628;

typedef struct _Thing_803F9628 {
    Element_803F9628 things[8];
    u32 extra[6];
} Thing_803F9628;

typedef struct _Coordinate3D {
    f32 x;
    f32 y;
    f32 z;
} Coordinate3D;

typedef struct _Placeholder_8016AE38_flags {
    u8 unk80 : 1;
    u8 unk40 : 1;
    u8 unk20 : 1;
    u8 unk10 : 1;
    u8 unk8 : 1;
    u8 unk4 : 1;
    u8 unk2 : 1;
    u8 unk1 : 1;
} Placeholder_8016AE38_flags;

typedef struct _Placeholder_8016AE38_flags_2 {
    u8 top3 : 3;
    u8 bot5 : 5;
} Placeholder_8016AE38_flags_2;

// When we figure out what that function is, replace this type with an actual
// type
typedef struct _Placeholder_8016AE38_ret_val {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u32 padding[0x931 - 3];
    Placeholder_8016AE38_flags_2 unk24C8;
    u8 unk24C9;
    Placeholder_8016AE38_flags unk24CA;
} Placeholder_8016AE38_ret_val;

typedef struct _Placeholder_8016AE50_flags {
    u8 unk80 : 1;
    u8 unk40 : 1;
    u8 unk20 : 1;
    u8 unk10 : 1;
    u8 unk8 : 1;
    u8 unk4 : 1;
    u8 unk2 : 1;
    u8 unk1 : 1;
} Placeholder_8016AE50_flags;

// When we figure out what that function is, replace this type with an actual
// type
typedef struct _Placeholder_8016AE50_ret_val {
    u8 unk0;
    u8 unk1;
    Placeholder_8016AE50_flags flags;
} Placeholder_8016AE50_ret_val;

// external functions we need
// takes HSD obj* ?
// extern void func_80391CAC(void*);
extern void func_802FB6AC(s32);
extern Placeholder_8016AE38_ret_val* func_8016AE38(void);
extern Placeholder_8016AE50_ret_val* func_8016AE50(void);
extern void func_8016B8D4(s32, s32);
extern void func_802F7C30(s32);
extern void func_802F7AF8(s32);
extern void func_802F7D08(s32);
extern void func_802F7BB4(s32);
extern void func_802FB650(s32);

// functions defined in this file

HudIndex* func_802F4910(void);
HSD_GObj* func_802F6194(HSD_GObj*, s32);
void func_802F6508(s32);
void func_802F665C(s8);
void func_802F6788(s32);
void func_802F6804(void);
void func_802F6898(void);
void func_802F68F0(void);
void func_802F6948(s32);
void func_802F69C0(s32, s32);
void func_802F6AF8(s32);
void func_802F6C04(s32);
void func_802F6D10(s32);
void func_802F6E1C(int slot);
void func_802F6E3C(s32);
void func_802F7220(void);

extern HudIndex lbl_804A10C8; // global array of HUD info

void func_802F5B48(void);
void lbl_802F5DE0(HSD_GObj* player, s32 arg1);
void lbl_802F5E50(void);
void func_802F5EC0(void);
void func_802F61FC(void);
void func_802F66A4(void);
void func_802F4B84(void);
void func_802F6EA4(void);
void func_802F7034(void);
void func_802F7134(void);
void func_802F4EDC(void);
void func_802F491C(void);

#endif
