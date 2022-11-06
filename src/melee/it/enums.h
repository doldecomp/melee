#ifndef MELEE_IT_ENUMS_H
#define MELEE_IT_ENUMS_H

#include <ctypes.h>

#pragma region "Item state change flags"

#define ITEM_STATE_CHANGE_NONE 0

#define ITEM_STATE_CHANGE_UNK_0x1 (1 << 0)

/**
 * Updates item model with target item state's AnimJoint, MatAnimJoint
 * and extra HSD archive node, if available.
 */
#define ITEM_ANIM_UPDATE (1 << 1)

// Copies 0xC44 to 0xC40 if toggled ON.
#define ITEM_DROP_UPDATE (1 << 2)

// Runs some JObj function.
#define ITEM_MODEL_UPDATE (1 << 3)

// Keep current hitboxes.
#define ITEM_HIT_PRESERVE (1 << 4)

// Keep current SFX.
#define ITEM_SFX_PRESERVE (1 << 5)

// Keep current color overlay.
#define ITEM_COLANIM_PRESERVE (1 << 6)

// Effect unknown.
#define ITEM_UNK_UPDATE (1 << 7)

// Run item's subaction events up to its current animation frame.
#define ITEM_CMD_UPDATE (1 << 8)

#pragma endregion

/**
 * These are used in 0x8026C258 to determine whether Samus' homing missile
 * should lock on its target.
 */
#pragma region "Unknown item kinds"

// Target (mato)
#define ITEM_UNK_MATO 4

#define ITEM_UNK_LOCKON 5

// Stage enemy (Goomba, Koopa Troopa, etc.)
#define ITEM_UNK_ENEMY 6

#pragma endregion

/* Based on "ID Lists" from the SSBM datasheet, in-game references,
 * and further research by VetriTheRetri.
 * @see https://docs.google.com/spreadsheets/d/1JX2w-r2fuvWuNgGb6D3Cs4wHQKLFegZe2jhbBuIhCG8
 */
typedef enum _It_Kind {

#pragma region "Common items"

    // Capsule
    It_Kind_Capsule,

    // Crate
    It_Kind_Box,

    // Barrel
    It_Kind_Taru,

    // Egg
    It_Kind_Egg,

    // Party Ball (Kusudama)
    It_Kind_Kusudama,

    // Barrel Cannon (TaruCann)
    It_Kind_TaruCann,

    // Bob-omb (BombHei)
    It_Kind_BombHei,

    // Mr. Saturn (Dosei)
    It_Kind_Dosei,

    // Heart Container
    It_Kind_Heart,

    // Maxim Tomato
    It_Kind_Tomato,

    // Starman (Super Star)
    It_Kind_Star,

    // Home-Run Bat
    It_Kind_Bat,

    // Beam Sword
    It_Kind_Sword,

    // Parasol
    It_Kind_Parasol,

    // Green Shell (G Shell)
    It_Kind_G_Shell,

    // Red Shell (R Shell)
    It_Kind_R_Shell,

    // Ray Gun (L Gun)
    It_Kind_L_Gun,

    // Freezie (Freeze)
    It_Kind_Freeze,

    // Food
    It_Kind_Foods,

    // Proximity Mine (MSBomb)
    It_Kind_MSBomb,

    // Flipper
    It_Kind_Flipper,

    // Super Scope (S Scope)
    It_Kind_S_Scope,

    // Star Rod
    It_Kind_StarRod,

    // Lip's Stick
    It_Kind_LipStick,

    // Fan (Harisen)
    It_Kind_Harisen,

    // Fire Flower (F Flower)
    It_Kind_F_Flower,

    // Super Mushroom (Kinoko)
    It_Kind_Kinoko,

    // Poison Mushroom (DKinoko)
    It_Kind_DKinoko,

    // Hammer
    It_Kind_Hammer,

    // Warp Star (WStar)
    It_Kind_WStar,

    // Screw Attack (ScBall)
    It_Kind_ScBall,

    // Bunny Hood (RabbitC)
    It_Kind_RabbitC,

    // Metal Box
    It_Kind_MetalB,

    // Cloaking Device (Spycloak)
    It_Kind_Spycloak,

    // Poké Ball (M Ball)
    It_Kind_M_Ball,

    // ITEM-RELATED

    // Ray Gun recoil effect (?)
    It_Kind_L_Gun_Ray,

    // Star Rod Star
    It_Kind_StarRod_Star,

    // Lips Stick Dust
    It_Kind_LipStick_Spore,

    // Super Scope Beam
    It_Kind_S_Scope_Beam,

    // Ray Gun Beam
    It_Kind_L_Gun_Beam,

    // Hammer Head
    It_Kind_Hammer_Head,

    // Flower
    It_Kind_F_Flower_Flame,

    // Yoshi's Egg (Event)
    It_Kind_EvYoshiEgg,

#pragma endregion

#pragma region "Monsters"

    // Goomba (Kuriboh)
    It_Kind_Kuriboh,

    // Redead (Leadead)
    It_Kind_Leadead,

    // Octarok (Octarock)
    It_Kind_Octarock,

    // Ottosea
    It_Kind_Ottosea,

    // Stone (Octarok Projectile)
    It_Kind_Octarock_Stone,

#pragma endregion

#pragma region "Character-related"

    // Mario's fireball
    It_Kind_Mario_Fire,

    // Dr. Mario's pill
    It_Kind_DrMario_Vitamin,

    // Kirby's Cutter beam
    It_Kind_Kirby_CBeam,

    // Kirby's Hammer
    It_Kind_Kirby_Hammer,
    It_Kind_Unk1,
    It_Kind_Unk2,

    // Fox's Laser
    It_Kind_Fox_Laser,

    // Falco's Laser
    It_Kind_Falco_Laser,

    // Fox's Illusion
    It_Kind_Fox_Illusion,

    // Falco's Phantasm
    It_Kind_Falco_Phantasm,

    // Link's bomb
    It_Kind_Link_Bomb,

    // Young Link's bomb
    It_Kind_CLink_Bomb,

    // Link's boomerang
    It_Kind_Link_Boomerang,

    // Young Link's boomerang
    It_Kind_CLink_Boomerang,

    // Link's Hookshot
    It_Kind_Link_HShot,

    // Young Link's Hookshot
    It_Kind_CLink_HShot,

    // Link's Arrow
    It_Kind_Link_Arrow,

    // Young Link's Fire Arrow
    It_Kind_CLink_Arrow,

    // PK Fire
    It_Kind_Ness_PKFire,

    // PK Fire Pillar
    It_Kind_Ness_PKFire_Flame,

    // PK Flash (charging state)
    It_Kind_Ness_PKFlush,

    // PK Thunder (Ball)
    It_Kind_Ness_PKThunder,

    // PK Thunder (Trail 1)
    It_Kind_Ness_PKThunder1,

    // PK Thunder (Trail 2)
    It_Kind_Ness_PKThunder2,

    // PK Thunder (Trail 3)
    It_Kind_Ness_PKThunder3,

    // PK Thunder (Trail 4)
    It_Kind_Ness_PKThunder4,

    // Fox's Blaster
    It_Kind_Fox_Blaster,

    // Falco's Blaster
    It_Kind_Falco_Blaster,

    // Link's Bow
    It_Kind_Link_Bow,

    // Young Link's Bow
    It_Kind_CLink_Bow,

    // PK Flash (explosion)
    It_Kind_Ness_PKFlush_Explode,

    // Needle (thrown)
    It_Kind_Seak_NeedleThrow,

    // Needle (held)
    It_Kind_Seak_NeedleHeld,

    // Pikachu's Thunder
    It_Kind_Pikachu_Thunder,

    // Pichu's Thunder
    It_Kind_Pichu_Thunder,

    // Mario's cape
    It_Kind_Mario_Cape,

    // Dr. Mario's cape
    It_Kind_DrMario_Sheet,

    // Smoke (Sheik)
    It_Kind_Seak_Vanish,

    // Yoshi's Egg (thrown)
    It_Kind_Yoshi_EggThrow,

    // Yoshi's Egg Lay???
    It_Kind_Yoshi_EggLay,

    // Yoshi's Star
    It_Kind_Yoshi_Star,

    // Pikachu's thunder (B)
    It_Kind_Pikachu_TJolt_Ground,

    // Pikachu's thunder (B)
    It_Kind_Pikachu_TJolt_Air,

    // Pichu's thunder (B)
    It_Kind_Pichu_TJolt_Ground,

    // Pichu's thunder (B)
    It_Kind_Pichu_TJolt_Air,

    // Samus's bomb
    It_Kind_Samus_Bomb,

    // Samus's chargeshot
    It_Kind_Samus_Charge,

    // Missile
    It_Kind_Samus_Missile,

    // Grapple beam
    It_Kind_Samus_GBeam,

    // Sheik's chain
    It_Kind_Seak_Chain,

    // Peach Bomber explosion?
    It_Kind_Peach_Explode,

    // Peach's turnip
    It_Kind_Peach_Turnip,

    // Bowser's flame
    It_Kind_Koopa_Flame,

    // Ness' baseball bat
    It_Kind_Ness_Bat,

    // Ness' Yo-Yo
    It_Kind_Ness_Yoyo,

    // Peach's parasol
    It_Kind_Peach_Parasol,

    // Peach's Toad special
    It_Kind_Peach_Toad,

    // Luigi's fireball
    It_Kind_Luigi_Fire,

    // Ice (Ice Climbers)
    It_Kind_IceClimber_Ice,

    // Blizzard
    It_Kind_IceClimber_Blizzard,

    // Din's Fire (charging state)
    It_Kind_Zelda_DinFire,

    // Din's Fire (explosion)
    It_Kind_Zelda_DinFire_Explode,

    // Mewtwo's Disable Projectile
    It_Kind_Mewtwo_Disable,

    // Peach Toad's spore effect
    It_Kind_Peach_ToadSpore,

    // Mewtwo's Shadowball
    It_Kind_Mewtwo_ShadowBall,

    // Ice Climbers Belay (Up B)
    It_Kind_IceClimber_GumStrings,

    // Mr. Game & Watch's Insecticide Spray
    It_Kind_GameWatch_Greenhouse,

    // Mr. Game & Watch's Manhole
    It_Kind_GameWatch_Manhole,

    // Mr. Game & Watch's Fire (?)
    It_Kind_GameWatch_Fire,

    // Mr. Game & Watch's Parachute
    It_Kind_GameWatch_Parachute,

    // Mr. Game & Watch's Turtle
    It_Kind_GameWatch_Turtle,

    // Mr. Game & Watch's Sparky
    It_Kind_GameWatch_Breath,

    // Mr. Game & Watch's Judge
    It_Kind_GameWatch_Judge,

    // Mr. Game & Watch's Oil Panic (?)
    It_Kind_GameWatch_Panic,

    // Sausage
    It_Kind_GameWatch_Chef,

    // Milk (Young Link)
    It_Kind_CLink_Milk,

    // Mr. Game & Watch's Firefighter
    It_Kind_GameWatch_Rescue,

    // Master Hand's Laser
    It_Kind_MasterHand_Laser,

    // Master Hand's Bullet
    It_Kind_MasterHand_Bullet,

    // Crazy Hand's Laser
    It_Kind_CrazyHand_Laser,

    // Crazy Hand's Bullet
    It_Kind_CrazyHand_Bullet,

    // Crazy Hand's Bomb
    It_Kind_CrazyHand_Bomb,

    // Kirby copy Mario's Fire (B)
    It_Kind_Kirby_MarioFire,

    // Kirby copy Dr. Mario's Capsule (B)
    It_Kind_Kirby_DrMarioVitamin,

    // Kirby copy Luigi's Fire (B)
    It_Kind_Kirby_LuigiFire,

    // Kirby copy Ice Climbers' Ice Shot (B)
    It_Kind_Kirby_IceClimberIce,

    // Kirby copy Peach's Toad (B)
    It_Kind_Kirby_PeachToad,

    // Kirby copy Toad's Spore (B)
    It_Kind_Kirby_PeachToadSpore,

    // Kirby copy Fox's Laser (B)
    It_Kind_Kirby_FoxLaser,

    // Kirby copy Falco's Laser (B)
    It_Kind_Kirby_FalcoLaser,

    // Kirby copy Fox's Blaster (B)
    It_Kind_Kirby_FoxBlaster,

    // Kirby copy Falco's Blaster (B)
    It_Kind_Kirby_FalcoBlaster,

    // Kirby copy Link's Arrow (B)
    It_Kind_Kirby_LinkArrow,

    // Kirby copy Young Link's Arrow (B)
    It_Kind_Kirby_CLinkArrow,

    // Kirby copy Link's Arrow (B)
    It_Kind_Kirby_LinkBow,

    // Kirby copy Young Link's Arrow (B)
    It_Kind_Kirby_CLinkBow,

    // Kirby copy Mewtwo's Shadowball (B)
    It_Kind_Kirby_MewtwoShadowBall,

    // Kirby copy PK Flash (B)
    It_Kind_Kirby_NessPKFlush,

    // Kirby copy PK Flash Explosion (B)
    It_Kind_Kirby_NessPKFlush_Explode,

    // Kirby copy Pikachu's Thunder (B)
    It_Kind_Kirby_PikachuTJolt_Ground,

    // Kirby copy Pikachu's Thunder (B)
    It_Kind_Kirby_PikachuTJolt_Air,

    // Kirby copy Pichu's Thunder (B)
    It_Kind_Kirby_PichuTJolt_Ground,

    // Kirby copy Pichu's Thunder (B)
    It_Kind_Kirby_PichuTJolt_Air,

    // Kirby copy Samus' Chargeshot (B)
    It_Kind_Kirby_SamusCharge,

    // Kirby copy Sheik's Needle (thrown) (B)
    It_Kind_Kirby_SeakNeedleThrow,

    // Kirby copy Sheik's Needle (ground) (B)
    It_Kind_Kirby_SeakNeedleHeld,

    // Kirby copy Bowser's Flame (B)
    It_Kind_Kirby_KoopaFlame,

    // Kirby copy Mr. Game & Watch's Sausage (B)
    It_Kind_Kirby_GameWatchChef,

    // Kirby copy Mr. Game & Watch's Chef Pan (B)
    It_Kind_Kirby_GameWatchChefPan,

    // Kirby's Yoshi Egg Lay??? (B)
    It_Kind_Kirby_YoshiEggLay,

    // (unique)
    It_Kind_Unk4,

    // Coin (?)
    It_Kind_Coin,
#pragma endregion

#pragma region "Pokémon"

    // Used for Random Pokémon value
    Pokemon_Random,

    // Goldeen (Tosakinto)
    Pokemon_Tosakinto,

    // Chikorita (Chicorita)
    Pokemon_Chicorita,

    // Snorlax (Kabigon)
    Pokemon_Kabigon,

    // Blastoise (Kamex)
    Pokemon_Kamex,

    // Weezing (Matadogas)
    Pokemon_Matadogas,

    // Charizard (Lizardon)
    Pokemon_Lizardon,

    // Moltres (Fire)
    Pokemon_Fire,

    // Zapdos (Thunder)
    Pokemon_Thunder,

    // Articuno (Freezer)
    Pokemon_Freezer,

    // Wobbuffet (Sonans)
    Pokemon_Sonans,

    // Scizor (Hassam)
    Pokemon_Hassam,

    // Unown (Unknown)
    Pokemon_Unknown,

    // Entei
    Pokemon_Entei,

    // Raikou
    Pokemon_Raikou,

    // Suicune (Suikun)
    Pokemon_Suikun,

    // Bellossom (Kireihana)
    Pokemon_Kireihana,

    // Electrode (Marumine)
    Pokemon_Marumine,

    // Lugia
    Pokemon_Lugia,

    // Ho-oh (Houou)
    Pokemon_Houou,

    // Ditto (Metamon)
    Pokemon_Metamon,

    // Clefairy (Pippi)
    Pokemon_Pippi,

    // Togepi (Togepy)
    Pokemon_Togepy,

    // Mew
    Pokemon_Mew,

    // Celebi (Cerebi)
    Pokemon_Cerebi,

    // Staryu (Hitodeman)
    Pokemon_Hitodeman,

    // Chansey (Lucky)
    Pokemon_Lucky,

    // Porygon2
    Pokemon_Porygon2,

    // Cyndaquil (Hinoarashi)
    Pokemon_Hinoarashi,

    // Marill (Maril)
    Pokemon_Maril,

    // Venusaur (Fushigibana)
    Pokemon_Fushigibana,
#pragma endregion

#pragma region "Pokémon-related"

    // Chikorita's Leaf
    Pokemon_Chicorita_Leaf,

    // Blastoise's Water
    Pokemon_Kamex_HydroPump,

    // Weezing's Gas
    Pokemon_Matadogas_Gas1,

    // Weezing's Gas
    Pokemon_Matadogas_Gas2,

    // Charizard's Breath
    Pokemon_Lizardon_Flame1,

    // Charizard's Breath
    Pokemon_Lizardon_Flame2,

    // Charizard's Breath
    Pokemon_Lizardon_Flame3,

    // Charizard's Breath
    Pokemon_Lizardon_Flame4,

    // Mini-Unowns
    Pokemon_Unknown_Swarm,

    // Lugia's Aeroblast
    Pokemon_Lugia_Aeroblast,

    // Lugia's Aeroblast
    Pokemon_Lugia_Aeroblast2,

    // Lugia's Aeroblast
    Pokemon_Lugia_Aeroblast3,

    // Ho-Oh's Flame
    Pokemon_Houou_SacredFire,

    // Staryu's Star
    Pokemon_Hitodeman_Star,

    // Chansey's Healing Egg
    Pokemon_Lucky_Egg,

    // Cyndaquil's Fire
    Pokemon_Hinoarashi_Flame,

    // ???
    Pokemon_Unk,

#pragma endregion

#pragma region "Monsters 2"

    // Old Goomba (old-Kuri)
    It_Kind_Old_Kuri,

    // Target (Mato)
    It_Kind_Mato,

    // Yoshi's Story Shy Guy (Heiho)
    It_Kind_Heiho,

    // Koopa Troopa (Green) (Nokonoko)
    It_Kind_Nokonoko,

    // Koopa Troopa (Red) (Patapata)
    It_Kind_Patapata,

    // Like-Like (likelike)
    It_Kind_Likelike,

    // Old Redead (old-lead) [invalid]
    It_Kind_Old_Lead,

    // Old Octorok (old-octa) [invalid]
    It_Kind_Old_Octa,

    // Old Ottosea (old-otto)
    It_Kind_Old_Otto,

    // Polar Bear (whitebea)
    It_Kind_Whitebea,

    // Klaptrap (klap)
    It_Kind_Klap,

    // Green Shell (zgshell)
    It_Kind_ZGShell,

    // Red Shell (green act) (zrshell)
    It_Kind_ZRShell,

#pragma endregion

#pragma region "Stage-specific"

    // Tingle (Tincle) (on balloon)
    It_Kind_Tincle,

    // [Invalid]
    It_Kind_Invalid1,

    // [Invalid]
    It_Kind_Invalid2,

    // [Invalid]
    It_Kind_Invalid3,

    // Whispy Apple
    It_Kind_WhispyApple,

    // Whispy's Healing Apple
    It_Kind_WhispyHealApple,

    // [Invalid]
    It_Kind_Invalid4,

    // [Invalid]
    It_Kind_Invalid5,

    // [Invalid]
    It_Kind_Invalid6,

    // Tool (Flatzone)
    It_Kind_Tools,

    // [Invalid]
    It_Kind_Invalid7,

    // [Invalid]
    It_Kind_Invalid8,

    // Birdo (Kyasarin)
    It_Kind_Kyasarin,

    // Arwing Laser
    It_Kind_Arwing_Laser,

    // Great Fox's Laser
    It_Kind_GreatFox_Laser,

    // Birdo's Egg
    It_Kind_Kyasarin_Egg,
#pragma endregion

} It_Kind;

#endif