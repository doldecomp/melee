#ifndef MELEE_IF_TYPES_H
#define MELEE_IF_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include "if/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

struct IfDamageFlags {
    u8 explode_animation : 1;
    u8 randomize_velocity : 1;
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

struct IfDamageState {
    /* +00 */ HSD_GObj* HUD_parent_entity;
    /* +04 */ HSD_GObj* next;
    /* +08 */ u8 player_slot;
    /* +09 */ u8 unk9;
    /* +0A */ u16 damage_percent;
    /* +0C */ u16 old_damage;
    /* +0E */ u8 damage_from_last_attack;
    /* +0F */ u8 frames_of_shake_remaining;
    /* +10 */ IfDamageFlags flags;
    /* +14 */ float translation_x[HUD_PLACE_MAX];
    /* +24 */ float translation_y[HUD_PLACE_MAX];
    /* +34 */ float velocity_x[HUD_PLACE_MAX];
    /* +44 */ float velocity_y[HUD_PLACE_MAX];
    /* +54 */ HSD_JObj* jobjs[HUD_PLACE_MAX];
};

struct HudIndex {
    IfDamageState players[6];
    /* +258 */ HSD_Joint* unk258;
    /* +25C */ void* jobj_desc_parent;
    /* +260 */ HSD_AnimJoint* janim_selection_joints;
    /* +264 */ void* janim_selection_textures;
    /* +268 */ void* unk268;
    /* +26C */ void* unk26C;
    /* +270 */ void* unk270;
    /* +274 */ void* unk274;
    // 8 elements of size 0x28, what is this?
};

struct Element_803F9628_Obj_14 {
    s32 padding[6];
    s32 unk1C;
};

struct Element_803F9628 {
    /* +00 */ HSD_GObj* x0;
    /* +04 */ u32 x4;
    /* +08 */ UNK_T x8;
    /* +0C */ u32 xC;  // flags?
    /* +10 */ u32 x10; // flags?
    /* +14 */ s32 x14;
    /* +18 */ u32 x18;
    /* +1C */ u32 x1C;
    /* +20 */ u32 x20;
    /* +24 */ u32 x24;
    /* +28 */ u32 x28;
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
