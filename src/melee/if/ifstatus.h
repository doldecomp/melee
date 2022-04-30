#ifndef _ifstatus_h_
#define _ifstatus_h_

#include <global.h>
#include <dolphin/types.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct _HudFlags {
  u8 explode_animation: 1;
  u8 unk40: 1;
  u8 force_digit_shake: 1;
  u8 unk10: 1;
  u8 hide_all_digits: 1;
  u8 animation_status_id: 2;
  u8 unk1: 1;
} HudFlags;

typedef struct _HudValue {
    // pointer to "unknown class type E"
    void* HUD_parent_entity;
    // probably a pointer to "unknown class type E"
    void* next;
    // represents players 1-6
    // TODO: list if this 0 indexed, or what
    u8 player_slot;
    // damage as int
    u16 damage_percent;
    u16 old_damage;
    u8 damage_from_last_attack;
    u8 frames_of_shake_remaining;
    HudFlags flags; 
    f32 hundreds_digit_x_translation;
    f32 tens_digit_x_translation;
    f32 ones_digit_x_translation;
    f32 percent_sign_x_translation;
    f32 hundreds_digit_y_translation;
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
    void* hundreds_jobj;
    void* tens_jobj;
    void* ones_jobj;
    void* percent_sign_jobj;
} HudValue;

typedef struct _HudIndex {
  HudValue players[6];
  // 258 unk
  void* unk258;
  // 0x25c
  void* jobj_desc_parent;
  // 0x260
  void* janim_selection_joints;
  // 0x264
  void* janim_selection_textures;
  // 0x268 null?
  void* unk268;
  void* unk26C;
  void* unk270;
  void* unk274;
} HudIndex;

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
    u32 unk14;
    // 0x18
    u32 unk18;
    // 0x1C
    u32 unk1C;
    // 0x20
    u32 unk20;
    // 0x24
    u32 unk24;
    // 0x28
    //u32 unk40;
} Element_803F9628;

typedef struct _Thing_803F9628 {
    Element_803F9628 things[8];
    u32 extra[6];
} Thing_803F9628;

// external functions we need
// takes HSD obj* ?
//extern void func_80391CAC(void*);
extern void func_802FB6AC(s32);


// functions defined in this file

HudIndex* func_802F4910(void);
asm void /*?*/ func_802F491C(void /*?*/);
asm void /*?*/ func_802F4B84(void /*?*/);
// Huge function, likely last to reverse
asm void /*?*/ func_802F4EDC(void /*?*/);
asm void /*?*/ func_802F5B48(void /*?*/);
asm void /*?*/ func_802F5EC0(void /*?*/);
asm void /*?*/ func_802F6194(void /*?*/);
asm void /*?*/ func_802F61FC(void /*?*/);
asm void func_802F6508(s32);
void func_802F665C(s8);
asm void /*?*/ func_802F66A4(void /*?*/);
asm void /*?*/ func_802F6788(void /*?*/);
asm void /*?*/ func_802F6804(void /*?*/);
void func_802F6898(void);
// https://decomp.me/scratch/mbZj9 
// slight mismatch in global, 99.55%
void func_802F68F0(void);
asm void /*?*/ func_802F6948(void /*?*/);
asm void /*?*/ func_802F69C0(void /*?*/);
asm void /*?*/ func_802F6AF8(void /*?*/);
asm void /*?*/ func_802F6C04(void /*?*/);
asm void /*?*/ func_802F6D10(void /*?*/);
void func_802F6E1C(void);
void func_802F6E3C(s32);
asm void /*?*/ func_802F6EA4(void /*?*/);
// https://decomp.me/scratch/8CIfp
asm void /*?*/ func_802F7034(void /*?*/);
// in progress
// https://decomp.me/scratch/XzfAH
asm void /*?*/ func_802F7134(void /*?*/);
void func_802F7220(void);

#endif
