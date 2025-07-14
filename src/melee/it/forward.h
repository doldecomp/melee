#ifndef MELEE_IT_FORWARD_H
#define MELEE_IT_FORWARD_H

#include "ft/forward.h"
#include <baselib/forward.h>

typedef struct Article Article;
typedef struct BobOmbRain BobOmbRain;
typedef struct BoneDynamicsDesc BoneDynamicsDesc;
typedef struct CameraBoxFlags CameraBoxFlags;
typedef struct DynamicBoneTable DynamicBoneTable;
typedef struct ECB ECB;
typedef struct flag32 flag32;
typedef struct HSD_ObjAllocUnk HSD_ObjAllocUnk;
typedef struct HSD_ObjAllocUnk2 HSD_ObjAllocUnk2;
typedef struct HSD_ObjAllocUnk4 HSD_ObjAllocUnk4;
typedef struct HSD_ObjAllocUnk5 HSD_ObjAllocUnk5;
typedef struct HSD_ObjAllocUnk6 HSD_ObjAllocUnk6;
typedef struct it_2F28_DatAttrs it_2F28_DatAttrs;
typedef struct Item Item;
typedef struct Item_DynamicBones Item_DynamicBones;
typedef struct ItemAttr ItemAttr;
typedef struct ItemCommonData ItemCommonData;
typedef struct ItemDynamics ItemDynamics;
typedef struct ItemModelDesc ItemModelDesc;
typedef struct ItemModStruct ItemModStruct;
typedef struct ItemStateArray ItemStateArray;
typedef struct ItemStateDesc ItemStateDesc;
typedef struct itSword_ItemVars itSword_ItemVars;
typedef struct SpawnItem SpawnItem;
typedef struct UnkItemArticles3 UnkItemArticles3;

#ifdef M2CTX
typedef struct Item_GObj Item_GObj;
struct Item_GObj {
    /*  +0 */ u16 classifier;
    /*  +2 */ u8 p_link;
    /*  +3 */ u8 gx_link;
    /*  +4 */ u8 p_priority;
    /*  +5 */ u8 render_priority;
    /*  +6 */ u8 obj_kind;
    /*  +7 */ u8 user_data_kind;
    /*  +8 */ Item_GObj* next;
    /*  +C */ Item_GObj* prev;
    /* +10 */ Item_GObj* next_gx;
    /* +14 */ Item_GObj* prev_gx;
    /* +18 */ HSD_GObjProc* proc;
    /* +1C */ void (*rendered)(Item_GObj* gobj, s32 code);
    /* +20 */ u64 gxlink_prios;
    /* +28 */ HSD_JObj* hsd_obj;
    /* +2C */ Item* user_data;
    /* +30 */ void (*user_data_remove_func)(Item* data);
    /* +34 */ void* x34_unk;
};
#else
typedef HSD_GObj Item_GObj;
#endif

typedef void (*ItCmd)(Item_GObj* gobj, FtCmdState* cmd);

typedef enum Item_StateChangeFlags {
    ITEM_UNK_0x1 = (1 << 0),
    ITEM_ANIM_UPDATE = (1 << 1),
    ITEM_DROP_UPDATE = (1 << 2),
    ITEM_MODEL_UPDATE = (1 << 3),
    ITEM_HIT_PRESERVE = (1 << 4),
    ITEM_SFX_PRESERVE = (1 << 5),
    ITEM_COLANIM_PRESERVE = (1 << 6),
    ITEM_UNK_UPDATE = (1 << 7),
    ITEM_CMD_UPDATE = (1 << 8),
} Item_StateChangeFlags;

typedef enum Item_UnkKinds {
    ITEM_UNK_MATO = 4,
    ITEM_UNK_LOCKON,
    ITEM_UNK_ENEMY,
    ITEM_UNK_7
} Item_UnkKinds;

// Combine with Item_UnkKinds?
typedef enum Item_HoldKinds {
    ITEM_HOLD_0,  // Common items, besides It_Kind_Foods
    ITEM_HOLD_1,  // Item-related items
    ITEM_HOLD_2,  // It_Kind_Foods
    ITEM_HOLD_3,  // Pokemon_Random
    ITEM_HOLD_4,  // Monsters 2 and Stage-specific items, besides
                  // It_Kind_Arwing_Laser, It_Kind_GreatFox_Laser, and
                  // It_Kind_Kyasarin_Egg
    ITEM_HOLD_5,  // (Stage-specific projectile items) It_Kind_Arwing_Laser,
                  // It_Kind_GreatFox_Laser, and It_Kind_Kyasarin_Egg
    ITEM_HOLD_6,  // Monster items, besides It_Kind_Octarock_Stone
    ITEM_HOLD_7,  // It_Kind_Octarock_Stone
    ITEM_HOLD_8,  // Character-related items, besides It_Kind_Unk4 and
                  // It_Kind_Coin
    ITEM_HOLD_9,  // Pokemon items
    ITEM_HOLD_10, // Pokemon-related items
    ITEM_HOLD_11, // It_Kind_Coin
    ITEM_HOLD_12, // It_Kind_Unk4
    // More?
} Item_HoldKinds;

// Based on "ID Lists" from the SSBM datasheet, in-game references, and further
// research by VetriTheRetri
// https://docs.google.com/spreadsheets/d/1JX2w-r2fuvWuNgGb6D3Cs4wHQKLFegZe2jhbBuIhCG8
// Development JP name strings are listed starting at data address 0x803EA7A8

#define It_Common_Start It_Kind_Capsule
#define It_Common_End It_Kind_L_Gun_Ray

typedef enum ItemKind {
    // COMMON ITEMS

    It_Kind_Capsule,  // Capsule
    It_Kind_Box,      // Crate
    It_Kind_Taru,     // Barrel
    It_Kind_Egg,      // Egg
    It_Kind_Kusudama, // Party Ball (Kusudama)
    It_Kind_TaruCann, // Barrel Cannon (TaruCann)
    It_Kind_BombHei,  // Bob-omb (BombHei)
    It_Kind_Dosei,    // Mr. Saturn (Dosei)
    It_Kind_Heart,    // Heart Container
    It_Kind_Tomato,   // Maxim Tomato
    It_Kind_Star,     // Starman (Super Star)
    It_Kind_Bat,      // Home-Run Bat
    It_Kind_Sword,    // Beam Sword
    It_Kind_Parasol,  // Parasol
    It_Kind_G_Shell,  // Green Shell (G Shell)
    It_Kind_R_Shell,  // Red Shell (R Shell)
    It_Kind_L_Gun,    // Ray Gun (L Gun)
    It_Kind_Freeze,   // Freezie (Freeze)
    It_Kind_Foods,    // Food
    It_Kind_MSBomb,   // Proximity Mine (MSBomb)
    It_Kind_Flipper,  // Flipper
    It_Kind_S_Scope,  // Super Scope (S Scope)
    It_Kind_StarRod,  // Star Rod
    It_Kind_LipStick, // Lip's Stick
    It_Kind_Harisen,  // Fan (Harisen)
    It_Kind_F_Flower, // Fire Flower (F Flower)
    It_Kind_Kinoko,   // Super Mushroom (Kinoko)
    It_Kind_DKinoko,  // Poison Mushroom (DKinoko)
    It_Kind_Hammer,   // Hammer
    It_Kind_WStar,    // Warp Star (WStar)
    It_Kind_ScBall,   // Screw Attack (ScBall)
    It_Kind_RabbitC,  // Bunny Hood (RabbitC)
    It_Kind_MetalB,   // Metal Box
    It_Kind_Spycloak, // Cloaking Device (Spycloak)
    It_Kind_M_Ball,   // Poke Ball (M Ball)

    // ITEM-RELATED

    It_Kind_L_Gun_Ray,      // Ray Gun recoil effect (?)
    It_Kind_StarRod_Star,   // Star Rod Star
    It_Kind_LipStick_Spore, // Lips Stick Dust
    It_Kind_S_Scope_Beam,   // Super Scope Beam
    It_Kind_L_Gun_Beam,     // Ray Gun Beam
    It_Kind_Hammer_Head,    // Hammer Head
    It_Kind_F_Flower_Flame, // Flower
    It_Kind_EvYoshiEgg,     // Yoshi's Egg (Event)

    // MONSTERS

    It_Kind_Kuriboh,        // Goomba (Kuriboh)
    It_Kind_Leadead,        // Redead (Leadead)
    It_Kind_Octarock,       // Octarok (Octarock)
    It_Kind_Ottosea,        // Ottosea
    It_Kind_Octarock_Stone, // Stone (Octarok Projectile)

    // CHARACTER-RELATED

    It_Kind_Mario_Fire,      // Mario's fireball
    It_Kind_DrMario_Vitamin, // Dr. Mario's pill
    It_Kind_Kirby_CBeam,     // Kirby's Cutter beam
    It_Kind_Kirby_Hammer,    // Kirby's Hammer
    It_Kind_Unk1,            // Maybe Kirby copy star?
    It_Kind_Unk2,
    It_Kind_Fox_Laser,                 // Fox's Laser
    It_Kind_Falco_Laser,               // Falco's Laser
    It_Kind_Fox_Illusion,              // Fox's Illusion
    It_Kind_Falco_Phantasm,            // Falco's Phantasm
    It_Kind_Link_Bomb,                 // Link's bomb
    It_Kind_CLink_Bomb,                // Young Link's bomb
    It_Kind_Link_Boomerang,            // Link's boomerang
    It_Kind_CLink_Boomerang,           // Young Link's boomerang
    It_Kind_Link_HShot,                // Link's Hookshot
    It_Kind_CLink_HShot,               // Young Link's Hookshot
    It_Kind_Link_Arrow,                // Link's Arrow
    It_Kind_CLink_Arrow,               // Young Link's Fire Arrow
    It_Kind_Ness_PKFire,               // PK Fire
    It_Kind_Ness_PKFire_Flame,         // PK Fire Pillar
    It_Kind_Ness_PKFlush,              // PK Flash (charging state)
    It_Kind_Ness_PKThunder,            // PK Thunder (Ball)
    It_Kind_Ness_PKThunder1,           // PK Thunder (Trail 1)
    It_Kind_Ness_PKThunder2,           // PK Thunder (Trail 2)
    It_Kind_Ness_PKThunder3,           // PK Thunder (Trail 3)
    It_Kind_Ness_PKThunder4,           // PK Thunder (Trail 4)
    It_Kind_Fox_Blaster,               // Fox's Blaster
    It_Kind_Falco_Blaster,             // Falco's Blaster
    It_Kind_Link_Bow,                  // Link's Bow
    It_Kind_CLink_Bow,                 // Young Link's Bow
    It_Kind_Ness_PKFlush_Explode,      // PK Flash (explosion)
    It_Kind_Seak_NeedleThrow,          // Needle (thrown)
    It_Kind_Seak_NeedleHeld,           // Needle (held)
    It_Kind_Pikachu_Thunder,           // Pikachu's Thunder
    It_Kind_Pichu_Thunder,             // Pichu's Thunder
    It_Kind_Mario_Cape,                // Mario's cape
    It_Kind_DrMario_Sheet,             // Dr. Mario's cape
    It_Kind_Seak_Vanish,               // Smoke (Sheik)
    It_Kind_Yoshi_EggThrow,            // Yoshi's Egg (thrown)
    It_Kind_Yoshi_EggLay,              // Yoshi's Egg Lay???
    It_Kind_Yoshi_Star,                // Yoshi's Star
    It_Kind_Pikachu_TJolt_Ground,      // Pikachu's thunder (B)
    It_Kind_Pikachu_TJolt_Air,         // Pikachu's thunder (B)
    It_Kind_Pichu_TJolt_Ground,        // Pichu's thunder (B)
    It_Kind_Pichu_TJolt_Air,           // Pichu's thunder (B)
    It_Kind_Samus_Bomb,                // Samus's bomb
    It_Kind_Samus_Charge,              // Samus's chargeshot
    It_Kind_Samus_Missile,             // Missile
    It_Kind_Samus_GBeam,               // Grapple beam
    It_Kind_Seak_Chain,                // Sheik's chain
    It_Kind_Peach_Explode,             // Peach Bomber explosion?
    It_Kind_Peach_Turnip,              // Peach's turnip
    It_Kind_Koopa_Flame,               // Bowser's flame
    It_Kind_Ness_Bat,                  // Ness's baseball bat
    It_Kind_Ness_Yoyo,                 // Ness's Yo-Yo
    It_Kind_Peach_Parasol,             // Peach's parasol
    It_Kind_Peach_Toad,                // Peach's Toad special
    It_Kind_Luigi_Fire,                // Luigi's fireball
    It_Kind_IceClimber_Ice,            // Ice (Ice Climbers)
    It_Kind_IceClimber_Blizzard,       // Blizzard
    It_Kind_Zelda_DinFire,             // Din's Fire (charging state)
    It_Kind_Zelda_DinFire_Explode,     // Din's Fire (explosion)
    It_Kind_Mewtwo_Disable,            // Mewtwo's Disable Projectile
    It_Kind_Peach_ToadSpore,           // Peach Toad's spore effect
    It_Kind_Mewtwo_ShadowBall,         // Mewtwo's Shadowball
    It_Kind_IceClimber_GumStrings,     // Ice Climbers Belay (Up B)
    It_Kind_GameWatch_Greenhouse,      // Mr. Game & Watch's Insecticide Spray
    It_Kind_GameWatch_Manhole,         // Mr. Game & Watch's Manhole
    It_Kind_GameWatch_Fire,            // Mr. Game & Watch's Fire (?)
    It_Kind_GameWatch_Parachute,       // Mr. Game & Watch's Parachute
    It_Kind_GameWatch_Turtle,          // Mr. Game & Watch's Turtle
    It_Kind_GameWatch_Breath,          // Mr. Game & Watch's Sparky
    It_Kind_GameWatch_Judge,           // Mr. Game & Watch's Judge
    It_Kind_GameWatch_Panic,           // Mr. Game & Watch's Oil Panic (?)
    It_Kind_GameWatch_Chef,            // Sausage
    It_Kind_CLink_Milk,                // Milk (Young Link)
    It_Kind_GameWatch_Rescue,          // Mr. Game & Watch's Firefighter
    It_Kind_MasterHand_Laser,          // Master Hand's Laser
    It_Kind_MasterHand_Bullet,         // Master Hand's Bullet
    It_Kind_CrazyHand_Laser,           // Crazy Hand's Laser
    It_Kind_CrazyHand_Bullet,          // Crazy Hand's Bullet
    It_Kind_CrazyHand_Bomb,            // Crazy Hand's Bomb
    It_Kind_Kirby_MarioFire,           // Kirby copy Mario's Fire (B)
    It_Kind_Kirby_DrMarioVitamin,      // Kirby copy Dr. Mario's Capsule (B)
    It_Kind_Kirby_LuigiFire,           // Kirby copy Luigi's Fire (B)
    It_Kind_Kirby_IceClimberIce,       // Kirby copy Ice Climbers' Ice Shot (B)
    It_Kind_Kirby_PeachToad,           // Kirby copy Peach's Toad (B)
    It_Kind_Kirby_PeachToadSpore,      // Kirby copy Toad's Spore (B)
    It_Kind_Kirby_FoxLaser,            // Kirby copy Fox's Laser (B)
    It_Kind_Kirby_FalcoLaser,          // Kirby copy Falco's Laser (B)
    It_Kind_Kirby_FoxBlaster,          // Kirby copy Fox's Blaster (B)
    It_Kind_Kirby_FalcoBlaster,        // Kirby copy Falco's Blaster (B)
    It_Kind_Kirby_LinkArrow,           // Kirby copy Link's Arrow (B)
    It_Kind_Kirby_CLinkArrow,          // Kirby copy Young Link's Arrow (B)
    It_Kind_Kirby_LinkBow,             // Kirby copy Link's Arrow (B)
    It_Kind_Kirby_CLinkBow,            // Kirby copy Young Link's Arrow (B)
    It_Kind_Kirby_MewtwoShadowBall,    // Kirby copy Mewtwo's Shadowball (B)
    It_Kind_Kirby_NessPKFlush,         // Kirby copy PK Flash (B)
    It_Kind_Kirby_NessPKFlush_Explode, // Kirby copy PK Flash Explosion (B)
    It_Kind_Kirby_PikachuTJolt_Ground, // Kirby copy Pikachu's Thunder (B)
    It_Kind_Kirby_PikachuTJolt_Air,    // Kirby copy Pikachu's Thunder (B)
    It_Kind_Kirby_PichuTJolt_Ground,   // Kirby copy Pichu's Thunder (B)
    It_Kind_Kirby_PichuTJolt_Air,      // Kirby copy Pichu's Thunder (B)
    It_Kind_Kirby_SamusCharge,         // Kirby copy Samus' Chargeshot (B)
    It_Kind_Kirby_SeakNeedleThrow, // Kirby copy Sheik's Needle (thrown) (B)
    It_Kind_Kirby_SeakNeedleHeld,  // Kirby copy Sheik's Needle (ground) (B)
    It_Kind_Kirby_KoopaFlame,      // Kirby copy Bowser's Flame (B)
    It_Kind_Kirby_GameWatchChef,   // Kirby copy Mr. Game & Watch's Sausage (B)
    It_Kind_Kirby_GameWatchChefPan, // Kirby copy Mr. Game & Watch's Chef Pan
                                    // (B)
    It_Kind_Kirby_YoshiEggLay,      // Kirby's Yoshi Egg Lay??? (B)
    It_Kind_Unk4,                   // (unique)
    It_Kind_Coin,                   // Coin (?)

    // POKEMON

    Pokemon_Random,      // Used for Random Pokemon value
    Pokemon_Tosakinto,   // Goldeen (Tosakinto)
    Pokemon_Chicorita,   // Chikorita (Chicorita)
    Pokemon_Kabigon,     // Snorlax (Kabigon)
    Pokemon_Kamex,       // Blastoise (Kamex)
    Pokemon_Matadogas,   // Weezing (Matadogas)
    Pokemon_Lizardon,    // Charizard (Lizardon)
    Pokemon_Fire,        // Moltres (Fire)
    Pokemon_Thunder,     // Zapdos (Thunder)
    Pokemon_Freezer,     // Articuno (Freezer)
    Pokemon_Sonans,      // Wobbuffet (Sonans)
    Pokemon_Hassam,      // Scizor (Hassam)
    Pokemon_Unknown,     // Unown (Unknown)
    Pokemon_Entei,       // Entei
    Pokemon_Raikou,      // Raikou
    Pokemon_Suikun,      // Suicune (Suikun)
    Pokemon_Kireihana,   // Bellossom (Kireihana)
    Pokemon_Marumine,    // Electrode (Marumine)
    Pokemon_Lugia,       // Lugia
    Pokemon_Houou,       // Ho-oh (Houou)
    Pokemon_Metamon,     // Ditto (Metamon)
    Pokemon_Pippi,       // Clefairy (Pippi)
    Pokemon_Togepy,      // Togepi (Togepy)
    Pokemon_Mew,         // Mew
    Pokemon_Cerebi,      // Celebi (Cerebi)
    Pokemon_Hitodeman,   // Staryu (Hitodeman)
    Pokemon_Lucky,       // Chansey (Lucky)
    Pokemon_Porygon2,    // Porygon2
    Pokemon_Hinoarashi,  // Cyndaquil (Hinoarashi)
    Pokemon_Maril,       // Marill (Maril)
    Pokemon_Fushigibana, // Venusaur (Fushigibana)

    // POKEMON-RELATED
    Pokemon_Chicorita_Leaf,   // Chikorita's Leaf
    Pokemon_Kamex_HydroPump,  // Blastoise's Water
    Pokemon_Matadogas_Gas1,   // Weezing's Gas
    Pokemon_Matadogas_Gas2,   // Weezing's Gas
    Pokemon_Lizardon_Flame1,  // Charizard's Breath
    Pokemon_Lizardon_Flame2,  // Charizard's Breath
    Pokemon_Lizardon_Flame3,  // Charizard's Breath
    Pokemon_Lizardon_Flame4,  // Charizard's Breath
    Pokemon_Unknown_Swarm,    // Mini-Unowns
    Pokemon_Lugia_Aeroblast,  // Lugia's Aeroblast
    Pokemon_Lugia_Aeroblast2, // Lugia's Aeroblast
    Pokemon_Lugia_Aeroblast3, // Lugia's Aeroblast
    Pokemon_Houou_SacredFire, // Ho-Oh's Flame
    Pokemon_Hitodeman_Star,   // Staryu's Star
    Pokemon_Lucky_Egg,        // Chansey's Healing Egg
    Pokemon_Hinoarashi_Flame, // Cyndaquil's Fire
    Pokemon_Unk,              // ???

    // MONSTERS 2

    It_Kind_Old_Kuri, // Old Goomba (old-Kuri)
    It_Kind_Mato,     // Target (Mato)
    It_Kind_Heiho,    // Yoshi's Story Shy Guy (Heiho)
    It_Kind_Nokonoko, // Koopa Troopa (Green) (Nokonoko)
    It_Kind_Patapata, // Koopa Troopa (Red) (Patapata)
    It_Kind_Likelike, // Like-Like (likelike)
    It_Kind_Old_Lead, // Old Redead (old-lead) [invalid]
    It_Kind_Old_Octa, // Old Octorok (old-octa) [invalid]
    It_Kind_Old_Otto, // Old Ottosea (old-otto)
    It_Kind_Whitebea, // Polar Bear (whitebea)
    It_Kind_Klap,     // Klaptrap (klap)
    It_Kind_ZGShell,  // Green Shell (zgshell)
    It_Kind_ZRShell,  // Red Shell (green act) (zrshell)

    // STAGE-SPECIFIC

    It_Kind_Tincle,          // Tingle (Tincle) (on balloon)
    It_Kind_Invalid1,        // [Invalid]
    It_Kind_Invalid2,        // [Invalid]
    It_Kind_Invalid3,        // [Invalid]
    It_Kind_WhispyApple,     // Whispy Apple
    It_Kind_WhispyHealApple, // Whispy's Healing Apple
    It_Kind_Invalid4,        // [Invalid]
    It_Kind_Invalid5,        // [Invalid]
    It_Kind_Invalid6,        // [Invalid]
    It_Kind_Tools,           // Tool (Flatzone)
    It_Kind_Invalid7,        // [Invalid]
    It_Kind_Invalid8,        // [Invalid]
    It_Kind_Kyasarin,        // Birdo (Kyasarin)
    It_Kind_Arwing_Laser,    // Arwing Laser
    It_Kind_GreatFox_Laser,  // Great Fox's Laser
    It_Kind_Kyasarin_Egg,    // Birdo's Egg
} ItemKind;

#endif
