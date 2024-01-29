#ifndef MELEE_IF_TYPES_H
#define MELEE_IF_TYPES_H

#include <platform.h>
#include "if/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

struct HudFlags {
    u8 explode_animation : 1;
    u8 unk40 : 1;
    u8 force_digit_shake : 1;
    u8 unk10 : 1;
    u8 hide_all_digits : 1;
    u8 animation_status_id : 2;
    u8 unk1 : 1;
};

struct UnknownClassTypeE {
    s32 padding[0x24];
    HSD_JObj* unk28;
};

struct HudValue {
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
};

struct HudIndex {
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
};

struct Element_803F9628_Obj_14 {
    s32 padding[6];
    s32 unk1C;
};

struct Element_803F9628 {
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
};

struct Thing_803F9628 {
    Element_803F9628 things[8];
    u32 extra[6];
};

struct Placeholder_8016AE50_flags {
    u8 unk80 : 1;
    u8 unk40 : 1;
    u8 unk20 : 1;
    u8 unk10 : 1;
    u8 unk8 : 1;
    u8 unk4 : 1;
    u8 unk2 : 1;
    u8 unk1 : 1;
};

struct Placeholder_8016AE50_ret_val {
    u8 unk0;
    u8 unk1;
    Placeholder_8016AE50_flags flags;
};

struct ifMagnify {
    HSD_Joint* joint; // // ifMagnify_802fc3c0 accesses 0x804A1DE0 for a Joint
    int x4;
    int x8;
    int xC;
    int x10;
    struct {
        HSD_GObj* gobj; // ifMagnify_802fc750 accesses 0x804A1DF4 + slot * 0x10
                        // for a GObj
        HSD_TObj* tobj; // ifMagnify_802fc3c0 accesses 0x804A1DF8 + slot * 0x10
                        // for a TObj
        HSD_ImageDesc*
            idesc; // ifMagnify_802FBBDC access 0x804A1DFC for an ImageDesc
        struct {
            u8 is_offscreen : 1;
            u8 ignore_offscreen : 1;
            u8 unk : 6;
        } state;
    } player[6];
    u8 unk[0xF0 - 0x74];
};

#endif
