#ifndef _item_h_
#define _item_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>
#include <functions.h>
#include <melee/pl/player.h>
#include <melee/gr/stage.h>
#include <melee/ft/fighter.h>
#include <math.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/controller.h>
#include <common_structs.h>

#include <melee/it/itkind.h>
#include <melee/it/itCommonItems.h>
#include <melee/it/itPKFlash.h>
#include <melee/it/itPKThunder.h>
#include <melee/it/itYoyo.h>

// Item State Change Flags //

// Apparently there's no 0x1 flag //
#define ITEM_ANIM_UPDATE 0x2 // Updates item model with target Item State's AnimJoint, MatAnimJoint and extra HSD archive node if available //
#define ITEM_DROP_UPDATE 0x4 // Copies 0xC44 to 0xC40 if toggled ON //
#define ITEM_MODEL_UPDATE 0x8 // Runs some JObj function //
#define ITEM_HIT_PRESERVE 0x10 // Keep current hitboxes //
#define ITEM_SFX_PRESERVE 0x20 // Keep current SFX //
#define ITEM_COLANIM_PRESERVE 0x40 // Keep current Color Overlay //
#define ITEM_UNK_UPDATE 0x80 // ??? //
#define ITEM_CMD_UPDATE 0x100 // Run item's Subaction Events up to its current animation frame //

// Item Unk Kinds //

// These are used in 0x8026C258 to determine whether Samus' Homing Missile should lock on its target.
#define ITEM_UNK_MATO 4 // Item type: Target (Mato)
#define ITEM_UNK_LOCKON 5
#define ITEM_UNK_ENEMY 6 // Item type: Stage Enemy (Goomba, Koopa Troopa, etc.)



struct ItemStateTable
{
    s32 x0_state_id;
    void* x4_callback_anim;
    void* x8_callback_phys;
    void* xC_callback_coll;
};

struct ItemStateContainer
{
    struct ItemStateTable stateTable[];
};

struct ItemLogicTable
{
    struct ItemStateContainer* x0_itemStatePtr;
    void (*x4_callback_OnSpawn)(HSD_GObj* item);
    void (*x8_callback_OnDestroy)(HSD_GObj* item);
    void (*xC_callback_OnPickup)(HSD_GObj* item);
    void (*x10_callback_OnDrop)(HSD_GObj* item);
    void (*x14_callback_OnThrow)(HSD_GObj* item);
    s32 (*x18_callback_OnGiveDamage)(HSD_GObj* item);
    s32 (*x1C_callback_OnTakeDamage)(HSD_GObj* item);
    void (*x20_callback_EnterAir)(HSD_GObj* item);
    s32 (*x24_callback_OnReflect)(HSD_GObj* item);
    s32 (*x28_callback_OnClank)(HSD_GObj* item);
    s32 (*x2C_callback_OnAbsorb)(HSD_GObj* item);
    s32 (*x30_callback_OnShieldBounce)(HSD_GObj* item);
    s32 (*x34_callback_OnHitShield)(HSD_GObj* item);
    void (*x38_callback_OnUnknown)(HSD_GObj* item, HSD_GObj* fighter);
};

typedef struct _CameraBoxFlags
{
    struct {
        u8 b01 : 2;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } bits;
} CameraBoxFlags;

typedef struct flag32
{
    union {
        struct {
            u32 x0 : 1;
            u32 x1 : 1;
            u32 x2 : 1;
            u32 x3 : 1;
            u32 x4 : 1;
            u32 x5 : 1;
            u32 x6 : 1;
            u32 x7 : 1;
            u32 x8 : 1;
            u32 x9 : 1;
            u32 xA : 1;
            u32 xB : 1;
            u32 xC : 1;
            u32 xD : 1;
            u32 xE : 1;
            u32 xF : 4;
            u32 x13 : 1;
            u32 x14 : 1;
            u32 x15 : 1;
            u32 x16 : 1;
            u32 x17 : 2;
            u32 x19 : 1;
            u32 x1A : 1;
            u32 x1B : 1;
            u32 x1C : 1;
            u32 x1D : 1;
            u32 x1E : 1;
            u32 x1F : 1;
        }flags;
        u32 word;
    };
}flag32;

typedef struct DynamicBoneTable
{
    HSD_JObj* x0_jobj[33]; // Rough estimate //
}DynamicBoneTable;

typedef struct DynamicBones
{
    void* x0_ptr;     // is stored @ 8000fdd4, comes from a nonstandard heap @ -0x52fc(r13)
    s32 x4_jobj_num;  // number of bones in this boneset
    f32 x8;           // stored @ 80011718, 0x8 of dynamicdesc
    f32 xc;           // stored @ 80011720, 0xC of dynamicdesc
    f32 x10;          // stored @ 80011728, 0x10 of dynamicdesc
} DynamicBones;

typedef struct ItemDynamicBones
{
    s32 x0_apply_phys_num;     // If this is 256, dyanmics are not processed
    HSD_JObj* x4_root_jobj;
    DynamicBones x8_dynamicBones; // This will be a dynamic bone struct once they're defined //

} ItemDynamicBones;

typedef struct {
    f32 x0_ecbTop;
    f32 x4_ecbBottom;
    f32 x8_ecbRight;
    f32 xC_ecbLeft;
} ECB;

typedef struct ItemAttr
{
    u8 x0_is_heavy : 1;          // 0x0, bit 0x80, is heavy item (crate)
    u8 x0_78 : 4;                // unk, might be lock-on behavior? (Samus Missile)
    u8 x0_hold_kind : 3;         // defines hand hold behavior
    u8 x1_1 : 2;     // 0x1 0xB0
    u8 x1_3 : 1;     // 0x1 0x20
    u8 x1_4 : 1;     // 0x1 0x10
    u8 x1_5 : 1;     // 0x1 0x08
    u8 x1_67_cam_kind : 2; // 0x1 0x06, is stored to 0xdcd
    u8 x1_8 : 1;     // 0x1 0x01    char flags3; //0x2
    u8 x3;                //0x3
    f32 x4_throw_speed_mul;     // 0x4, speed multiplier at which this item is thrown at
    s32 x8;                     //
    f32 xC_spin_speed;           //
    f32 x10_fall_speed;           // 0x10
    f32 x14_fall_speed_max;       // 0x14
    f32 x18;                  //
    f32 x1C_damage_mul;             // collision related? referenced on taking damage @ 80270f90
    ECB x20;
    Vec2 x30_unk;                // 0x34
    Vec2 x38_grab_range;            // 0x38
    ECB x40;
    s32 x50;                    // 0x50
    s32 x54;                    // 0x54
    s32 x58;                    // 0x58
    s32 x5c;                    // 0x5c
    f32 x60_scale;                // 0x60, does not affect hitboxes
    s32 x64_destroy_gfx;            // 0x64, ID of a gfx to play on destroy
    s32 x68;                    // 0x68
    s32 x6C;                    // 0x6c
    s32 x70;                    // 0x70
    s32 x74;                    // 0x74
    s32 x78_destroySFX;            // 0x78
    s32 x7C;                    // 0x7c
    s32 x80;                    // 0x80
    s32 x84;                    // 0x84
    s32 x88;                    // 0x88
    s32 x8C;                    // 0x8c
    s32 x90;                    // 0x90
    s32 x94;                    // 0x94
    s32 x98;                    // 0x98
    s32 x9C;                    // 0x9c
} ItemAttr;

typedef struct ItemDynamicsDesc
{
    s32 x0_boneID; // bone index;
    void* x4_params;  // dynamics params;
    s32 x8_num;       // number of children bones to make dynamic
    f32 xC;
    f32 x10;
    f32 x14;
}ItemDynamicsDesc;

typedef struct ItemDynamics
{
    s32 x0_dynamics_num;            // 0x8 number of dynamic bonesets for this fighter
    ItemDynamicsDesc* x4_dynamicsDesc; // 0x4 boneset data array (one for each boneset)
}ItemDynamics;

typedef struct ItemState_ParamStruct
{
    void* x0_unk;
    void* x4_unk;
    void* x8_unk;
}ItemState_ParamStruct;

struct ItemStateDesc
{
    void* x0_anim_joint;
    void* x4_matanim_joint;
    void* x8_parameters;
    void* xC_script;
};

typedef struct ItemStateArray
{
    struct ItemStateDesc x0_itemStateDesc[8];
}ItemStateArray;

typedef struct ItemModelDesc
{
    HSD_Joint* x0_joint;
    s32 x4_bone_count;
    s32 x8_bone_attach_id;
    s32 xC_bit_field;
} ItemModelDesc;

typedef struct _Article
{
    ItemAttr* x0_common_attr;
    void* x4_specialAttributes;
    void* x8_hurtbox;
    ItemStateArray* xC_itemStates;
    ItemModelDesc* x10_modelDesc;
    ItemDynamics* x14_dynamics;
} Article;

typedef struct itHurt
{
    s32 x0_bone_state;            // 0x0 = normral; 0x1 = invincible; 0x2 = intangible;
    Vec3 x4_hurt1_offset;
    Vec3 x10_hurt2_offset;
    f32 x1C_scale;
    HSD_JObj* x20_jobj;
    UnkFlagStruct x24_flags;      // 0x80 = hurtbox position update toggle; doesn't update position if toggled ON
    UnkFlagStruct x25_flags;
    UnkFlagStruct x26_flags;
    UnkFlagStruct x27_flags;
    Vec3 x28_hurt1_pos;
    Vec3 x34_hurt2_pos;
    s32 x40_bone_index;

} itHurt;

typedef struct itHitVictim
{
    void* x0_victim;    // m-ex header says this is a user_data pointer but proceeds to call it a GObj in the comment below it //
    s32 x4_timedRehit;  // number of frames needed to pass before this entity can be hit again; 0 = can't rehit //
} itHitVictim;

typedef struct itHit
{
    s32 x0_toggle;                            // Toggles hitbox on/off.
    s32 x4_unk;
    s32 x8_damage;                            // Projected damage
    f32 xC_damage_staled;                     // Staled damage, actually applied
    Vec3 x10_offset;
    f32 x1C_hitbox_size;
    s32 x20_angle;
    s32 x24_knockback_growth;
    s32 x28_wdsk;                             // Weight-Dependent Set Knockback
    s32 x2C_base_knockback;
    s32 x30_element;                          // Normal, fire, electric, etc.
    s32 x34_shield_damage;                    // If hitbox damage + shield damage is less than 0 (negative), this will effectively restore shield health
    s32 x38_SFX_severity;                     // 0x38. hurtbox interaction. 0 = none, 1 = grounded, 2 = aerial, 3 = both // What //
    s32 x3C_SFX_kind;
    UnkFlagStruct x40_flags;                  // 0x20 -> check against aerial fighters; 0x10 -> check against grounded fighters
    UnkFlagStruct x41_flags;                  // 0x8/0x4/0x2 = timed rehit on item/fighter/shield; 0x1 = can reflect
    UnkFlagStruct x42_flags;                  // 0x80 = can absorb; 0x20 = hit only fighters facing the item; 0x10 = can shield; 0x8 = ignore reflect/absorb bubbles(?); 0x4 = ignore hurtboxes; 0x2 = ignore ungrabbable hurtboxes 
    UnkFlagStruct x43_flags;                  // 0x80 = interact with items only; 0x20 = interact with all?
    s32 x44;
    HSD_JObj* x48_jobj;
    Vec3 x4C_pos;
    Vec3 x58_posPrev;
    Vec3 x64_posColl;                         // 0x64   position of hurt collision
    f32 x70_coll_distance;                    // 0x70   Distance From Collding Hurtbox (Used for phantom hit collision calculation)
    itHitVictim x74_tipLog[12];
    itHitVictim xD4_damageLog[12];
    s32 x134;
    s32 x138;
} itHit;

typedef struct _Item
{
    void* x0;
    HSD_GObj* x4_GObj;
    s32 x8;
    s32 xC_spawn_kind;
    s32 x10_item_kind;
    s32 x14_hold_kind;
    s32 x18;
    s32 x1C;
    u8 x20_team_id;
    u8 x21;
    u8 x22;
    u8 x23;
    s32 x24_item_state_index;
    s32 x28_item_anim_index;
    f32 x2C_facing_direction;
    f32 x30_initial_facing_dir;
    f32 x34_spin_speed;
    f32 x38_scale;
    f32 x3C;
    Vec3 x40_vel;
    Vec3 x4C_pos;
    Vec3 x58_vec_unk;
    Vec3 x64_vec_unk2;
    Vec3 x70_nudge;
    u8 padding_x7C[0xB8 - 0x7C];
    struct ItemLogicTable* xB8_itemLogicTable; // Global item callbacks //
    struct ItemStateContainer* xBC_itemStateContainer;
    s32 xC0_unk_state; // Air state? //
    Article* xC4_article_data;
    union                       // Might be exclusively HSD_Joint* //
    {                      
        HSD_JObj* xC8_jobj; 
        HSD_Joint* xC8_joint;
    };
    ItemAttr* xCC_item_attr;
    struct ItemStateDesc* xD0_itemStateDesc;
    ItemDynamicBones xD4_dynamicBones[24];
    s32 x374_dynamicBonesNum;
    CollData x378_itemColl;
    HSD_GObj* x518_ownerGObj; // Item's current owner //
    s32 x51C;
    CameraBox* x520_cameraBox; // CameraBox //
    f32 x524;
    s32 x528;
    void* x52C_item_script; // Script parse? //
    u32 x530;
    u32 x534;
    u32 x538;
    u32 x53C;
    u32 x540;
    u32 x544;
    ColorOverlay x548_colorOverlay;
    u8 x5C8;
    u8 x5C9;
    u8 x5CA;
    u8 x5CB;
    f32 x5CC_currentAnimFrame;
    f32 x5D0_animFrameSpeed;
    itHit x5D4_hitboxes[4];
    s32 xAC4_ignoreItemID; // Cannot hit items with this index? //
    s32 xAC8_hurtboxNum; // Number of hurtboxes this item has //
    itHurt xACC_itemHurtbox[2];
    u32 xB54;
    u32 xB58;
    u32 xB5C;
    u32 xB60;
    u32 xB64;
    u8 xB68;
    u8 xB69;
    u8 xB6A;
    u8 xB6B;
    u32 xB6C;
    u32 xB70;
    u32 xB74;
    u32 xB78;
    u32 xB7C;
    u32 xB80;
    u32 xB84;
    u32 xB88;
    u32 xB8C;
    u32 xB90;
    u32 xB94;
    u32 xB98;
    u32 xB9C;
    u32 xBA0;
    u32 xBA4;
    u32 xBA8;
    u32 xBAC;
    u32 xBB0;
    u32 xBB4;
    u32 xBB8;
    DynamicBoneTable* xBBC_dynamicBoneTable;
    u32 xBC0;
    u8 xBC4;
    u8 xBC5;
    u8 xBC6;
    u8 xBC7;
    u32 xBC8;
    Vec2 xBCC_unk;
    Vec2 xBD4_grabRange;
    ECB xBDC;
    ECB xBEC;
    ECB xBFC;
    ECB xC0C;
    ECB xC1C;
    u32 xC2C;
    u32 xC30;
    struct itdmg
    {
        s32 xC34_damageDealt;                           // Rounded down
        s32 xC38;                                       // 0xc38
        f32 xC3C;                                       // 0xc3c
        f32 xC40;                                       // 0xc40
        f32 xC44;                                       // 0xc44
        s32 xC48;                                       // 0xc48
        s32 xC4C;                                       // Something to do with damage. 0x80077464 checks this against reflectors' maximum damage threshold
        s32 xC50;                                       // 0xc50
        f32 xC54;                                       // 0xc54
        f32 xC58;                                       // 0xc58
        s32 xC5C;                                       // 0xc5c
        s32 xC60;                                       // 0xc60
        HSD_GObj* xC64_reflectGObj;                     // GObj that reflected this item?
        f32 xC68;                                       // 0xc68
        f32 xC6C;                                       // 0xc6c
        f32 xC70;                                       // 0xc70
        s32 xC74;
        Vec2 xC78;                                       // 0xc74
        Vec2 xC80;                                       // 0xc7c
        s32 xC88;                                       // 0xc88
        s16 xC8C;                                       // 0xc8c
        HSD_GObj* xC90_absorbGObj;                      // 0xc90
        s32 xC94;                                       // 0xc94
        s32 xC98;                                       // 0xc98
        s32 xC9C;                                       // Total damage taken?
        s32 xCA0;                                       // Last amount of damage taken?
        s32 xCA4;                                       // 0xca4
        s32 xCA8;                                       // 0xca8, hitlag related
        s32 xCAC_angle;                                 // 0xcac
        s32 xCB0_source_ply;                            // 0xcb0, damage source ply number
        s32 xCB4;                                       // 0xcb4
        f32 xCB8_outDamageDirection;                    // 0xcb8, updated @ 80078184
        f32 xCBC_hitlagFrames;                          // 0xcbc, hitlag frames remaining
        f32 xCC0;                                       // 0xcc0
        s32 xCC4;                                       // 0xcc4
        f32 xCC8_knockback;                             // 0xcc8
        f32 xCCC_incDamageDirection;                    // Direction from which damage was applied?
        f32 xCD0;                                       // 0xcd0
        f32 xCD4;                                       // 0xcd4
        f32 xCD8;                                       // 0xcd8
        f32 xCDC;                                       // 0xcdc
        f32 xCE0;                                       // 0xce0
        f32 xCE4;                                       // 0xce4
        f32 xCE8;                                       // 0xce8
        HSD_GObj* xCEC_fighterGObj;                     // 0xcec
        HSD_GObj* xCF0_itemGObj;                        // 0xcf0, is a fighter GObj, but is the owner of the fighter that hit the item (?)
    } itdmg;
    HSD_GObj* xCF4_fighterGObjUnk;
    HSD_GObj* xCF8_detectGObj; // GObj that was detected by this item's inert hitbox
    s32 xCFC;
    HSD_GObj* xD00_grabGObj; // GObj that got grabbed by this item
    HSD_GObj* xD04_atkCollItem; // GObj that collided with this item's hitbox?
    u8 xD08;
    u8 xD09;
    u8 xD0A;
    u8 xD0B;
    u32 xD0C;
    s32 xD10;
    struct itcb
    {
        s32 (*xD14_callback_Anim)(HSD_GObj* item);                                      // 0xd14
        void (*xD18_callback_Phys)(HSD_GObj* item);                                     // 0xd18
        s32 (*xD1C_callback_Coll)(HSD_GObj* item);                                      // 0xd1c
        void (*xD20_callback_Accessory)(HSD_GObj* item);                                // 0xd20
        s32 (*xD24_callback_Inert)(HSD_GObj* item);                                    // 0xd24, runs when a GObj is detected by this item's inert hibox
        void (*xD28_callback_EnterHitlag)(HSD_GObj* item);                              // 0xd28, runs after applying hitlag in damage apply proc 8026a62c
        void (*xD2C_callback_ExitHitlag)(HSD_GObj* item);                               // 0xd2c, runs after exiting hitlag in hitlag update proc 8026a200
        s32 (*xD30_callback_JumpedOn)(HSD_GObj* item);                                 // 0xd30, runs when the item is "jumped on", 80269bac
        void (*xD34_callback_Grab_ItemCB)(HSD_GObj* item);                       // 0xd34, when grabbing a fighter, run this function on self
        void (*xD38_callback_Grab_VictimCB)(HSD_GObj* victim, HSD_GObj* item); // 0xd38, when grabbing a fighter, run this function on fighter
    } itcb;
    f32 xD3C_spinSpeed;
    f32 xD40;
    f32 xD44_lifeTimer;
    f32 xD48_halfLifeTimer; // Not radioactive, just the item's original lifetime halved
    s32 xD4C;
    s32 xD50_landNum; // Number of times this item has landed
    s32 xD54_throwNum; // Number of times this item has been thrown
    s32 xD58;
    s32 xD5C;
    s32 xD60; // Something to do with OnDestroy GFX? //
    s32 xD64;
    s32 xD68;
    s32 xD6C;
    s32 xD70;
    s32 xD74;
    s32 xD78;
    s32 xD7C_destroySFX; // SFX that plays when this item is destroyed
    s32 xD80;
    s32 xD84;
    s32 xD88_attackID; // ???
    s16 xD8C_attackInstance;
    s16 xD8E;
    s32 xD90;
    Vec2 xD94;
    Vec2 xD9C;
    union {
        UnkFlagStruct xDA4_flag;
        u32 xDA4_word;
    };
    union {
        UnkFlagStruct xDA8_flag;
        u16 xDA8_short;
    };
    union {
        UnkFlagStruct xDAA_flag; // Develop mode stuff?
        u8 xDAA_byte;
    };
    u32 xDAC_itcmd_var0;
    u32 xDB0_itcmd_var1;
    u32 xDB4_itcmd_var2;
    u32 xDB8_itcmd_var3;
    u32 xDBC_itcmd_var4;
    u32 xDC0;
    u32 xDC4;
    flag32 xDC8_word;
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4567 : 4;
    } xDCC_flag;
    CameraBoxFlags xDCD_flag;
    UnkFlagStruct xDCE_flag;
    UnkFlagStruct xDCF_flag;
    UnkFlagStruct xDD0_flag;
    UnkFlagStruct xDD1_flag;
    UnkFlagStruct xDD2_flag;
    UnkFlagStruct xDD3_flag;
    union {
        BobOmbVars BobOmb;
        HeartContainerVars HeartContainer;
        MaximTomatoVars MaximTomato;
        FoodVars Food;
        EggVars Egg;
        WhispyAppleVars WhispyApple;
        PKFlashVars PKFlash;
        PKFlashExplVars PKFlashExpl;
        PKThunderVars PKThunderVars;
        u8 padding[0xFCC - 0xDD4];
    } xDD4_itemVar;
} Item;

extern struct sdata_ItemGXLink
{
    void (*x0_renderFunc)(HSD_GObj*, s32);
};

struct r13_ItemTable
{
    s32 filler;
    Article* x0_article[0x9F];
};

typedef struct UnkCommonArticlePtr
{
    u32 x0;
}UnkCommonArticlePtr;

typedef struct UnkCommonArticleStruct
{
    s32 x0;
    UnkCommonArticlePtr* x4;
}UnkCommonArticleStruct;

typedef struct CommonItemArticles
{
    void* article_ptr[0x10];
    UnkCommonArticleStruct* x40;
}CommonItemArticles;

typedef struct UnkItemArticles
{
    void* unkptr[];
}UnkItemArticles;

typedef struct UnkItemArticles2
{
    void* unkptr[];
}UnkItemArticles2;

typedef struct UnkItemArticles3
{
    void* unkptr[1];
}UnkItemArticles3;

typedef struct BobOmbRain
{
    s32 x0;
    s32 x4;
    Vec3 x8_vec;
    s32 x14;
    s32 x18;
    UnkFlagStruct x1C;
}BobOmbRain;

typedef struct SpawnItem
{
    HSD_GObj* x0_parent_gobj;  // Primary owner of the item; usually a fighter GObj
    HSD_GObj* x4_parent_gobj2; // Secondary owner GObj of the item; e.g. Ness' PK Fire Pillar has this set to PK Fire Spark's item GObj
    s32 x8_item_id;            // 0x8, ID of the item to spawn
    s32 xC_hold_kind;          // Defines the behavior of the item, such as thrown and pickup. 0 = capsule
    s32 x10;
    Vec3 x14_pos;
    Vec3 x20_pos_prev;
    Vec3 x2C_vel;
    f32 x38_facing_direction;
    s16 x3C_damage;
    s16 x3E;
    s32 x40;                   // 0x1 = correct initial position
    UnkFlagStruct x44_flag;    // 0x80 = perform initial collision check
    UnkFlagStruct x45_flag;
    UnkFlagStruct x46_flag;
    UnkFlagStruct x47_flag;
    s32 x48_ground_or_air;          // 0x0 = stationary, 0x1 = air (?)

} SpawnItem;

typedef struct ItemModStruct
{
    s32 x0_unk;

}ItemModStruct;

inline Item* GetItemData(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    return item_data;
}

inline Item* GetItemDirect(HSD_GObj* item_gobj)
{
    return item_gobj->user_data;
}

// FUNCTIONS //
s32 func_80266F3C(void);                                       // Check if items are enabled
void func_80266F70(void);                                      // Check to load ItCo.dat/usd
void func_80266FA8(void);                                      // ItCo prefunction with 0 
void func_8027870C(s32);                                       // Load ItCo.dat/usd
void func_80266FCC(void);                                      // Init item struct? 
void func_80267130(HSD_GObj* item_gobj, SpawnItem* spawnItem); // Initialize item coordinates? //
void func_80267454(HSD_GObj* item_gobj);                       // Remove Camera Box //
void func_802674AC(SpawnItem* spawnItem);                      // Set Item Hold kind //
void func_802675A8(HSD_GObj* item_gobj);
void func_802676F4(HSD_GObj* item_gobj);
s32 func_8026784C(s32 dropItem, s32 unused);                   // Decide drop item; 0x8026862C loads two integers into this, but the second one goes unused? //
void func_80267978(HSD_GObj* item_gobj);                       // Store Item Pointers //
void func_80267AA8(HSD_GObj* item_gobj, SpawnItem* spawnItem); // Initialize item variables //
void func_802680CC(HSD_GObj* item_gobj);                       // Setup Item JObj //
void func_8026814C(HSD_GObj* item_gobj);                       // Setup item render objects? //
s32 func_802682F0(HSD_GObj* item_gobj);                        // Initialize item bones //
void func_8026849C(HSD_GObj* item_gobj);                       // Set item model scale //
void func_80268560(HSD_GObj* item_gobj);                       // Setup item dynamics //
HSD_GObj* func_8026862C(SpawnItem* spawnItem);                 // Create Item //
void func_80268B18(SpawnItem* spawnItem);                      // Item spawn prefunction - spawn airborne //
void func_80268B5C(SpawnItem* spawnItem);                      // Item spawn prefunction - spawn grounded //
void func_80268B9C(SpawnItem* spawnItem);                      // Item spawn prefunction - spawn grounded and toggle unknown true //
void func_80268BE0(HSD_JObj* item_jobj, HSD_AnimJoint* anim_joint, HSD_MatAnimJoint* matanim_joint, ItemState_ParamStruct* arg3, Item* item_data); // Adds AObjs to item model //
void func_80268D34(HSD_GObj* item_gobj, struct ItemStateDesc* itemStateDesc); // Unk Item AObj-related function //
void func_80268DD4(HSD_GObj* item_gobj, f32 arg8);             // Advance item animation? //
void func_80268E40(Item* item_data, struct ItemStateDesc* itemStateDesc); // Copy item script //
void func_80268E5C(HSD_GObj* item_gobj, s32 itemStateID, s32 itemStateFlags); // Item State Change //
void lbl_802693E4(HSD_GObj* item_gobj);                        // Item Think - Hitlag //
void func_802694CC(HSD_GObj* item_gobj);                       // Advance item animation + script? //
void lbl_80269528(HSD_GObj* item_gobj);                        // Item Think - Animation //
s32 func_802696CC(HSD_GObj* item_gobj);                        // Item Think - Check for Blast Zones //
void func_802697D4(HSD_GObj* item_gobj);                       // Item Think - Physics //
void func_80269978(HSD_GObj* item_gobj);                       // Item Think - Collision //
void lbl_80269A9C(HSD_GObj* item_gobj);                        // Item Think - Accessory + Camera Box //
void lbl_80269B60(HSD_GObj* item_gobj);                        // Item Think - Yellow Bar Collision (cb_JumpedOn) //
void lbl_80269BE4(HSD_GObj* item_gobj);                        // Item Think - Grab //
void lbl_80269C5C(HSD_GObj* item_gobj);                        // Item Think - Hit Collision Logic //
void func_80269CA0(Item* item_data, s32 damage);               // Set damage taken //
void func_80269CC4(HSD_GObj* item_gobj);                       // Set damage struct //
s32 func_80269DC8(HSD_GObj* item_gobj);                        // Item Think - Shield Collision //
s32 func_80269F14(HSD_GObj* item_gobj);                        // Item Think - On Reflect //
void func_8026A0A0(HSD_GObj* item_gobj);                       // Item Think - Exit Hitlag Check //
void func_8026A0FC(HSD_GObj* item_gobj);                       // Item Think - Exit Hitlag Check 2 //
void func_8026A158(HSD_GObj* item_gobj);                       // Item Think - Enter Hitlag //
void func_8026A1E8(HSD_GObj* item_gobj);                       // Item Think - Exit Hitlag //    
void lbl_8026A294(HSD_GObj* item_gobj);                        // Item Think - Hit Collision //
void lbl_8026A788(HSD_GObj* item_gobj);                        // Item Think - Process Dynamic Bones //
void func_8026A810(HSD_GObj* item_gobj);                       // Run Item's OnSpawn Callback //
void func_8026A848(HSD_GObj* item_gobj, HSD_GObj* fighter_gobj);// Remove Item from Player //
void func_8026A8EC(HSD_GObj* item_gobj);                       // Destroy Item //
void func_8026AB54(HSD_GObj* item_gobj, s32 pickupGFX, s32 pickupSFX); // Make Item Held //
void func_8026ABD8(HSD_GObj* item_gobj, Vec3* pos, f32 arg2);  // Drop Item //
void func_8026AC74(HSD_GObj* item_gobj, s32 dropGFX, s32 dropSFX, f32 arg8); // This is actually another Item Drop function //
void func_8026AD20(HSD_GObj* item_gobj, s32 dropGFX, s32 dropSFX, f32 arg8); // Throw Item //
void func_8026ADC0(HSD_GObj* item_gobj);                       // Make Item Airborne //
void lbl_8026AE10(Item* item_data);                            // Clear Item Struct ? //
u32 func_8026AE60(void);                                       // Increment something //
void func_8026AE84(Item* item_data, s32 sfxID, u8 pan, u8 volume); // Play Item SFX //
void func_8026AF0C(Item* item_data, s32 sfxID, u8 pan, u8 volume); // Play Item SFX 2 //
void func_8026AFA0(Item* item_data, s32 sfxID, u8 pan, u8 volume); // Play Item SFX 3 //
void func_8026B034(Item* item_data);                               // Stop Item SFX //
void func_8026B074(Item* item_data);                               // Stop Item SFX 2 //
void func_8026B0B4(HSD_GObj* item_gobj);                           // Stop All Item SFX // 
s32 func_8026B1A4(HSD_GObj* item_gobj);                            // Check if item is grabbable //
f32 func_8026B1D4(HSD_GObj* item_gobj, itHit* itemHitboxUnk);      // Apply Item Damage -  may not be itHit* ??? //
void func_8026B294(HSD_GObj* item_gobj, Vec3* pos);                // Copy Item position vector //
BOOL func_8026B2B4(HSD_GObj* item_gobj);                            // Check if item is heavy //
BOOL func_8026B2D8(HSD_GObj* item_gobj);                            // Check if item is heavy again? //
s32 itGetKind(HSD_GObj* item_gobj);                                // Get Item ID //
s32 func_8026B30C(HSD_GObj* item_gobj);                            // Return flag from Item Attributes //
s32 func_8026B320(HSD_GObj* item_gobj);                            // Return item hold kind //
f32 func_8026B334(HSD_GObj* item_gobj);                            // Return item damage multiplier //
void func_8026B344(HSD_GObj* item_gobj, Vec3* pos);                // Unknown item position math, related to velocity? //
f32 func_8026B378(HSD_GObj* item_gobj);                            // Return item's X-Axis grab range? //
f32 func_8026B384(HSD_GObj* item_gobj);                            // Return item's Y-Axis grab range? //
void func_8026B390(HSD_GObj* item_gobj);                           // Toggle item flag 0x15 in 0xDC8 word ON // 
void func_8026B3A8(HSD_GObj* item_gobj);                           // Toggle item flag 0x15 in 0xDC8 word OFF // 
u32 func_8026B3C0(s32 itemID);                                     // Count item entities of identical kind? //
void func_8026B3F8(Article* article, s32 itemID);                  // Store Item article pointer to table //
void func_8026B40C(Article* article, s32 itemID);                  // Store Stage Item article pointer to table //
f32 func_8026B424(s32 damage);                                     // Item Damage Math //
s32 func_8026B47C(HSD_GObj* item_gobj);                            // Get heal value of healing items //
BOOL func_8026B4F0(HSD_GObj* item_gobj);                           // Check if item is a healing item //
f32 func_8026B54C(HSD_GObj* item_gobj);                            // Get unknown float from 0x0 of item's special attributes //
f32 func_8026B560(HSD_GObj* item_gobj);                            // Identical to 0x8026B54C but likely using a different itAttributes struct //
f32 func_8026B574(HSD_GObj* item_gobj);                            // Get unknown float from 0x4 of item's special attributes //
s32 func_8026B588(void);                                           // Get unknown integer from itCommonData //
BOOL func_8026B594(HSD_GObj* item_gobj);                           // Check if item can fire projectiles //
HSD_GObj* func_8026B5E4(Vec3* vector, Vec3* vector2, HSD_GObj* item_gobj); // Unknown item camera check? //
HSD_GObj* func_8026B634(Vec3* vector, Vec3* vector2, HSD_GObj* item_gobj); // Unknown item camera check 2? //
f32 func_8026B684(Vec3* pos);                                      // Get facing direction of fighter (?) with argument 0 //
f32 func_8026B6A8(Vec3* pos, s32 arg);                             // Get facing direction of fighter (?) with variable argument //
BOOL func_8026B6C8(HSD_GObj* item_gobj);                           // Check if item is a stage item? //
void func_8026B718(HSD_GObj* item_gobj, f32 hitlagFrames);         // Set item's hitlag frames //
void func_8026B724(HSD_GObj* item_gobj);                           // Toggle bit 3 of 0xDC8 word ON //
void func_8026B73C(HSD_GObj* item_gobj);                           // Toggle bits in 0xDC8 word //
BOOL func_8026B774(HSD_GObj* item_gobj, u8 arg1);                  // Bitwise operations in 0xDC8 word //
s32 func_8026B7A4(HSD_GObj* item_gobj);                            // Get Item State ID //
u8 func_8026B7B0(HSD_GObj* item_gobj);                             // Get Item Team ID //
s32 func_8026B7BC(HSD_GObj* item_gobj);                            // Get flag 0x14 of 0xDC8 word //
s32 func_8026B7CC(HSD_GObj* item_gobj);                            // Get 0x1C of Item - something to do with stale moves? //
s32 func_8026B7D8(void);                                           // Get unknown var from global data //
s32 func_8026B7E0(void);                                           // Get unknown var from global data //
s32 func_8026B7E8(HSD_GObj* item_gobj);                            // Get bit 1 of 0xDC8 word //
void func_8026B7F8(HSD_GObj* fighter_gobj);                        // Remove item from player on death? //
BOOL func_8026B894(HSD_GObj* item_gobj, HSD_GObj* referenced_gobj);// Remove all GObj interaction references from item //
s32 func_8026B924(HSD_GObj* item_gobj);                            // Return result of unk item check - requires -g compiler flag / Frank modifications to match //
f32 func_8026B960(HSD_GObj* item_gobj);                            // Return float result of item kind and state checks - requires -g compiler flag / Frank modifications to match //
void func_8026B9A8(HSD_GObj* item_gobj, s32 arg1, s32 arg2);       // Transfer item on character swap - used for Zelda <-> Sheik //
void func_8026BAE8(HSD_GObj* item_gobj, f32 scale_mul);            // Multiply item's scale //
void func_8026BB20(HSD_GObj* item_gobj);                           // Clear JObj flags on item model //
void func_8026BB44(HSD_GObj* item_gobj);                           // Set JObj flags on item model //
void func_8026BB68(HSD_GObj* fighter_gobj, Vec3* pos);             // Adjust item's position to fighter bone //
void func_8026BB88(HSD_GObj* item_gobj, Vec3* pos);                // Adjust item's position based on ECB? //
void func_8026BBCC(HSD_GObj* item_gobj, Vec3* pos);                // Adjust item's ECB position? //
void func_8026BC14(HSD_GObj* item_gobj);                           // Check if item owner is a fighter + decrement hitlag //
s32 func_8026BC68(HSD_GObj* item_gobj);                            // Return bit 0 of 0xDD0 //
HSD_GObj* func_8026BC78(HSD_GObj* item_gobj);                      // Get item owner //
BOOL func_8026BC84(HSD_GObj* item_gobj);                            // Get item attack kind //
void func_8026BC90(HSD_GObj* item_gobj, Vec3* pos);                // Unknown item ECB / position update //
void func_8026BCF4(HSD_GObj* item_gobj);                           // Toggle bit 2 of 0xDCD OFF //
void func_8026BD0C(HSD_GObj* item_gobj);                           // Toggle bit 2 of 0xDCD ON //
void func_8026BD24(HSD_GObj* item_gobj);                           // Toggle bit 3 of 0xDD0 ON //
void func_8026BD3C(HSD_GObj* item_gobj);                           // Toggle bit 3 of 0xDCC ON //
void func_8026BD54(HSD_GObj* item_gobj);                           // Toggle bit 3 of 0xDCC OFF //
void func_8026BD6C(HSD_GObj* item_gobj);                           // Toggle bit 3 of 0xDCD ON //
void func_8026BD84(HSD_GObj* item_gobj);                           // Toggle bit 4 of 0xDCD ON //
void func_8026BD9C(HSD_GObj* item_gobj);                           // Toggle 0x1A of 0xDC8 word ON //
void func_8026BDB4(HSD_GObj* item_gobj);                           // Toggle 0x1A of 0xDC8 word OFF //
void func_8026BDCC(HSD_GObj* item_gobj);                           // Toggle several item flags //
void func_8026BE28(HSD_GObj* item_gobj);                           // Toggle several item flags, inverted //
void* func_8026BE84(BobOmbRain* bobOmbRain);                       // Bob-Omb Rain Switch //
CollData* func_8026C100(HSD_GObj* item_gobj);                      // Get item's CollData pointer //
void func_8026C16C(HSD_GObj* item_gobj, BOOL isHeadless);          // Check if Hammer item's head should break off //
void func_8026C1B4(HSD_GObj* item_gobj);                           // Check if item has a hitbox //
u32 func_8026C1D4(void);                                           // Get unknown var from r13 pointer //
BOOL func_8026C1E8(HSD_GObj* item_gobj);                           // Check if item has grabbed a GObj? //
void func_8026C220(HSD_GObj* item_gobj, HSD_GObj* fighter_gobj);   // Get item owner's port number //
HSD_GObj* func_8026C258(Vec3* vector, f32 facingDir);              // Find the closest item to the given position? //
void func_8026C334(HSD_GObj* item_gobj, Vec3* pos);                // Unknown item position / ECB update //
void func_8026C368(HSD_GObj* item_gobj);                           // Run bomb item explosion callbacks //
void func_8026C3FC(void);                                          // Toggle bit 3 of 0xDC8 ON for all active item GObjs? //
void func_8026C42C(void);                                          // Toggle bits in 0xDC8 for all active item GObjs? //
f32 func_8026B424(s32 damage);                                /* extern */
u8 func_8026B7B0(HSD_GObj* item_gobj);                         // Get Team ID //
void func_8026BDCC(HSD_GObj* item_gobj);                         /* extern */
void func_8026C368(HSD_GObj* item_gobj);                         /* extern */
void func_8026D324(s32);
s32 func_8026D604(HSD_GObj* item_gobj);
void func_8026F9A0();
void func_802701BC(HSD_GObj* item_gobj);
void func_802703E8(HSD_GObj* item_gobj);
void func_802706D0(HSD_GObj* item_gobj);
void func_80270E30(HSD_GObj* item_gobj);
void func_8027137C(HSD_GObj* item_gobj);
void func_8027146C(HSD_GObj* item_gobj);
void func_802714C0(HSD_GObj* item_gobj);                         /* extern */
void func_80271508(HSD_GObj* item_gobj, s32 arg1);
void func_8027163C(HSD_GObj* item_gobj);
void func_80271A58(HSD_GObj* item_gobj);                         /* extern */
void func_802721B8(HSD_GObj* item_gobj);                         /* extern */
void func_80272280(HSD_GObj* item_gobj);
void func_8027163C(HSD_GObj* item_gobj);
void func_80271A58(HSD_GObj* item_gobj);                         /* extern */
void func_802721B8(HSD_GObj* item_gobj);                         /* extern */
void func_80272298(HSD_GObj* item_gobj);
void func_802722B0(HSD_GObj* item_gobj);
void func_80272304(HSD_GObj* item_gobj);
void func_80272460(itHit* hitbox, s32 damage, HSD_GObj* item_gobj);
void func_802725D4(HSD_GObj*);
void func_80272784(HSD_GObj* item_gobj);
void func_802728C8(HSD_GObj* item_gobj);
void func_80272A18(HSD_JObj* item_jobj);
void func_80272A3C(HSD_JObj* item_jobj);
s32 func_80272D1C(HSD_GObj* item_gobj);                        // Check if GObj entity class = 0x6 (item) //
s32 func_80272D40(HSD_GObj* item_gobj);                        // Check GObj entity class //
void func_80272F7C(HSD_JObj*, f32);
void func_802728C8(HSD_GObj* item_gobj);
s32 func_80272D1C(HSD_GObj* item_gobj);                        // Check if GObj entity class = 0x6 (item) //
void func_80273168(HSD_GObj* item_gobj);
void func_802731A4(HSD_GObj*);
void func_802731E0(HSD_GObj*);
void func_8027327C(HSD_GObj* item_gobj, s32 ID1, s32 ID2);
void func_8027346C(HSD_GObj* item_gobj);                         /* extern */
void func_80273484(HSD_GObj* item_gobj);
void func_80273500(HSD_GObj*, Vec3*);
void func_80273748(HSD_GObj*, s32, s32);
void func_80273B50(HSD_GObj*, Vec3*);
void func_80274198(HSD_GObj*, s32);
void func_802741F4(HSD_GObj*, s32);
void func_8027429C(HSD_GObj*, Vec3*);
void func_802742F4(HSD_GObj*, s32, s32);
void func_80274658(HSD_GObj*, f32);
void func_80274740(HSD_GObj* item_gobj);                         /* extern */
void func_80274A64(HSD_GObj* item_gobj);                             /* extern */
s32 func_80274C78(HSD_GObj* item_gobj);                /* extern */
void func_80274DAC(HSD_GObj*);
void func_8027737C(HSD_GObj* item_gobj, Vec3* pos);                  /* extern */
void func_80274EF8(HSD_GObj* item_gobj);                       // Toggle flag in 0xDC8 off //
void func_80274F10(HSD_GObj* item_gobj);
void func_80275158(HSD_GObj* item_gobj, f32 lifetime);         // Set item lifetime //
void func_80275390(HSD_GObj*);
void func_802753BC(HSD_GObj*, s16);
void func_802753DC(HSD_GObj*);
void func_802742F4(HSD_GObj*, s32, s32);
void func_80274740(HSD_GObj* item_gobj);                         /* extern */
void func_80274A64(HSD_GObj* item_gobj);                             /* extern */
s32 func_80274C78(HSD_GObj* item_gobj);                /* extern */
void func_8027737C(HSD_GObj* item_gobj, Vec3* pos);                  /* extern */
void func_80274EF8(HSD_GObj* item_gobj);                       // Toggle flag in 0xDC8 off //
void func_80275158(HSD_GObj* item_gobj, f32 lifetime);         // Set item lifetime //
void func_80275390(HSD_GObj*);
void func_80275474(HSD_GObj* item_gobj);                       // Toggle several flags in 0xDCD off //
void func_802754D4(HSD_GObj*);
void func_80275504(HSD_GObj* item_gobj);                       // Toggle several flags in 0xDCE off //
void func_802756D0(HSD_GObj* item_gobj);
void func_802756E0(HSD_GObj* item_gobj);
void func_8027574C(HSD_GObj* item_gobj);
void func_80275870(HSD_GObj* item_gobj);
void func_80275E98(HSD_GObj*, SpawnItem*);
void func_802762B0(Item*);
void func_802762BC(Item*);
void func_802799E4(HSD_GObj* item_gobj);                       // Advance Item Script //
void func_80279B64(Item*);
void func_80279B88(Item* item_data, s32 arg1, s32 arg2);
void func_80279BBC(Item* item_data);                             /* extern */
void func_80279BE0(HSD_GObj* item_gobj);                         /* extern */
void func_8027B0C4(HSD_GObj*, SpawnItem*);
void func_8027D670(Vec3*);
void func_8027D730(HSD_GObj*);
HSD_GObj* func_80283AE4(s32, Vec3*, s32);
void func_80283BD4(HSD_GObj*);
HSD_GObj* func_802841B4(s32, Vec3*, s32);
void func_8028428C(HSD_GObj*);
HSD_GObj* func_80284854(Vec3*);
HSD_GObj* func_80284D54(Vec3*);
HSD_GObj* func_80286088(s32);
HSD_GObj* func_802896CC(Vec3*);
void func_8028FE90(HSD_GObj*);
HSD_GObj* func_80290938(s32);
HSD_GObj* func_80291BE0(Vec3*);
HSD_GObj* func_80292D48(Vec3*);
HSD_GObj* func_80294DC0(Vec3*);
void func_8029D968(HSD_GObj*);
void func_802D09D0(HSD_GObj*);
void func_802799E4(HSD_GObj* item_gobj);                       // Advance Item Script //
void func_80279B88(Item* item_data, s32 arg1, s32 arg2);
void func_80279BBC(Item* item_data);                             /* extern */
void func_80279BE0(HSD_GObj* item_gobj);                         /* extern */

#endif