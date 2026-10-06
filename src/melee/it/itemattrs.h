#ifndef MELEE_IT_ITEMATTRS_H
#define MELEE_IT_ITEMATTRS_H

#include <Runtime/platform.h>

#include <melee/it/forward.h>

#include <dat_macros.h>

#include <dolphin/mtx.h>
#include <melee/ft/kinds/ftCommon/types.h>
#include <melee/ft/kinds/ftSeak/types.h>
#include <melee/it/itCharItems.h>
#include <melee/it/itCommonItems.h>
#include <melee/it/itPKFlash.h>
#include <melee/it/itPKThunder.h>
#include <melee/it/itYoyo.h>

typedef struct ArwingLaserAttr {
    /* +0 */ ItemAttr* x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
} ArwingLaserAttr;

typedef struct itCerebiAttributes {
    /* +0 */ f32 scale;
    /* +4 */ Vec2 velocity;
    /* +C */ f32 vertical_acceleration;
} itCerebiAttributes;

typedef struct itFFlowerFlameAttributes {
    /* +0 */ f32 lifetime;
} itFFlowerFlameAttributes;

typedef struct itMarioFireballAttributes {
    /*  +0 */ f32 x0;
    /*  +4 */ f32 x4;
    /*  +8 */ f32 x8;
    /*  +C */ f32 xC;
    /* +10 */ f32 x10;
} itMarioFireballAttributes;

typedef struct itLuigiFireballAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
} itLuigiFireballAttributes;

typedef struct itHeihoAttributes {
    /*  +0 */ s32* x0;
    /*  +4 */ f32 speed[3];
    /* +10 */ u8 x10[4];
    /* +14 */ f32 x14;
} itHeihoAttributes;

typedef struct itLugiaAeroblastAttributes {
    /* +0 */ f32 lifetime;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
} itLugiaAeroblastAttributes;

typedef struct itParasolAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
} itParasolAttributes;

typedef struct itRabbitCAttributes {
    /* +0 */ f32 x0;
} itRabbitCAttributes;

typedef struct itMetalBAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
} itMetalBAttributes;

typedef struct {
    f32 x0;
} ItMetamonVars;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
} ItZeldaDinFire_ItemVars;

typedef struct KinokoAttrs {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ HSD_AnimJoint* x8[2];
} KinokoAttrs;

typedef struct {
    f32 speed;
    f32 accel;
} StarAttrs;

typedef struct StarRodAttributes {
    s32 x0;
    Vec x4;
} StarRodAttributes;

typedef struct StarRodStarAttrs {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    s32 x18;
    f32 x1C;
} StarRodStarAttrs;

typedef struct itDoseiAttributes {
    f32 unk0;
    s32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} itDoseiAttributes;

typedef struct itGShell_Attrs {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    char pad18[0x1C - 0x18];
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    f32 x30;
    Vec x34;
} itGShell_Attrs;

typedef struct itHammerData {
    u32 x0;
    u32 x4;
    f32 x8;
} itHammerData;

typedef struct itKirbyCutterBeamAttributes {
    f32 x0_speed;
    f32 x4_vel;
    f32 x8_lifetime;
    f32 xC_decel;
} itKirbyCutterBeamAttributes;

typedef struct itKoopaFlame_Attributes {
    f32 x0_lifetime;        // 28.0
    f32 x4_hitbox_lifetime; // 20.0
    f32 x8_min_speed;       // 1.9
    f32 xC_max_speed;       // 2.2
    f32 x10_min_angle;      // 2.1816616
    f32 x14_max_angle;      // 2.5307274
} itKoopaFlame_Attributes;

typedef struct itLipstickSporeAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    s32 x18;
} itLipstickSporeAttributes;

typedef struct {
    f32 x0;
    f32 x4;
    itECB x8;
} itMsBomb_Attrs;

typedef struct itRShell_Attrs {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    Vec3 x14;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    char pad30[0x38 - 0x30];
    f32 x38; // rotation multiplier (gshell x20)
    f32 x3C;
    f32 x40;
    f32 x44;
    Vec x48;
    s32 x54;
} itRShell_Attrs;

typedef struct itSeakNeedleThrownAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
} itSeakNeedleThrownAttributes;

typedef struct itZGShell_Attrs {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    Vec x3C;
} itZGShell_Attrs;

/// Layouts and shared views of #Article::x4_specialAttributes.
/// The annotated variants use @c Article::kind (see #it_804D6D20_t and
/// #GroundItemData).
/// @todo Bind and annotate the remaining variants for the DAT walk.
union ItemSpecialAttributes {
    ItCapsuleAttr capsule DAT_IF(Article::kind == It_Kind_Capsule);
    itBoxAttributes box DAT_IF(Article::kind == It_Kind_Box);
    itTaruAttributes taru DAT_IF(Article::kind == It_Kind_Taru);
    itEgg_ItemVars egg DAT_IF(Article::kind == It_Kind_Egg);
    itKusudamaAttributes kusudama DAT_IF(Article::kind == It_Kind_Kusudama);
    itTaruCann_DatAttrs tarucann DAT_IF(Article::kind == It_Kind_TaruCann);
    itBombHeiAttributes bombhei DAT_IF(Article::kind == It_Kind_BombHei);
    itDoseiAttributes dosei DAT_IF(Article::kind == It_Kind_Dosei);
    HeartContainerAttr heart DAT_IF(Article::kind == It_Kind_Heart);
    MaximTomatoSpecialAttr tomato DAT_IF(Article::kind == It_Kind_Tomato);
    itStar_ItemVars star DAT_IF(Article::kind == It_Kind_Star);
    itBatAttributes bat DAT_IF(Article::kind == It_Kind_Bat);
    itParasolAttributes parasol DAT_IF(Article::kind == It_Kind_Parasol);
    itGShell_Attrs g_shell DAT_IF(Article::kind == It_Kind_G_Shell);
    itRShell_Attrs r_shell DAT_IF(Article::kind == It_Kind_R_Shell);
    ItLGunAttr l_gun DAT_IF(Article::kind == It_Kind_L_Gun);
    itFreezeAttributes freeze DAT_IF(Article::kind == It_Kind_Freeze);
    itFoodsAttributes foods DAT_IF(Article::kind == It_Kind_Foods);
    itMsBomb_Attrs ms_bomb DAT_IF(Article::kind == It_Kind_MSBomb);
    itFlipper_DatAttrs flipper DAT_IF(Article::kind == It_Kind_Flipper);
    itSScopeAttributes s_scope DAT_IF(Article::kind == It_Kind_S_Scope);
    StarRodAttributes star_rod DAT_IF(Article::kind == It_Kind_StarRod);
    itLipstickAttributes lipstick DAT_IF(Article::kind == It_Kind_LipStick);
    itHarisen_DatAttrs harisen DAT_IF(Article::kind == It_Kind_Harisen);
    FFlowerAttr f_flower DAT_IF(Article::kind == It_Kind_F_Flower);
    KinokoAttrs kinoko DAT_IF(Article::kind == It_Kind_Kinoko ||
                              Article::kind == It_Kind_DKinoko);
    itHammerData hammer_data DAT_IF(Article::kind == It_Kind_Hammer);
    itWstarAttributes wstar DAT_IF(Article::kind == It_Kind_WStar);
    itRabbitCAttributes rabbit_c DAT_IF(Article::kind == It_Kind_RabbitC);
    itMetalBAttributes metal_b DAT_IF(Article::kind == It_Kind_MetalB);
    itMBallAttributes m_ball DAT_IF(Article::kind == It_Kind_M_Ball);
    ItLGunRayAttr l_gun_ray DAT_IF(Article::kind == It_Kind_L_Gun_Ray);
    StarRodStarAttrs star_rod_star DAT_IF(Article::kind ==
                                          It_Kind_StarRod_Star);
    itLipstickSporeAttributes lipstick_spore DAT_IF(Article::kind ==
                                                    It_Kind_LipStick_Spore);
    ScopeBeamAttrs s_scope_beam DAT_IF(Article::kind == It_Kind_S_Scope_Beam);
    ItLGunBeamAttr l_gun_beam DAT_IF(Article::kind == It_Kind_L_Gun_Beam);
    itHammerheadAttributes hammer_head DAT_IF(Article::kind ==
                                              It_Kind_Hammer_Head);
    itFFlowerFlameAttributes f_flower_flame DAT_IF(Article::kind ==
                                                   It_Kind_F_Flower_Flame);
    itEvYoshiEgg_DatAttrs evyoshiegg DAT_IF(Article::kind ==
                                            It_Kind_EvYoshiEgg);

    // Other layouts and shared views used by item callers.
    ArwingLaserAttr arwing_laser;
    itCerebiAttributes cerebi;
    struct itChainSegment chain_segment;
    itChicoritaAttr chicorita;
    itChicoritaLeafAttr chicorita_leaf;
    itClimbersBlizzardAttributes climbers_blizzard;
    itClimbersIceAttributes climbers_ice;
    itClimbersStringAttributes climbers_string;
    itCoinAttributes coin;
    itCrazyHandBombAttributes crazy_hand_bomb;
    itDrMarioPillAttributes dr_mario_pill;
    itFireAttributes fire;
    itFlashAttributes flash;
    itFlashExplAttributes flash_expl;
    FoxIllusionAttr fox_illusion;
    FoxLaserAttr fox_laser;
    itFreezerAttributes freezer;
    itFushigibanaAttributes fushigibana;
    itGamewatchAttributes gamewatch;
    itGamewatchchefAttributes gamewatchchef;
    itGreatFoxLaser_Attrs great_fox_laser;
    itHassam_ItemVars hassam;
    itHeihoAttributes heiho;
    itHinoarashiAttributes hinoarashi;
    itHitodemanAttributes hitodeman;
    itHououAttr houou;
    itKabigonAttributes kabigon;
    itKamexAttributes kamex;
    itKamexHydroPumpAttributes kamex_hydro_pump;
    itKirbyCutterBeamAttributes kirby_cutter_beam;
    itkireihanaAttributes kireihana;
    itKoopaFlame_Attributes koopa_flame;
    itKyasarinAttributes kyasarin;
    itKyasarinEggAttributes kyasarin_egg;
    itLeadeadAttributes leadead;
    itLikelikeAttributes likelike;
    itLinkArrowAttributes link_arrow;
    itLinkBombAttributes link_bomb;
    itLinkBoomerangAttributes link_boomerang;
    itLinkHookshotAttributes link_hookshot;
    itLizardonAttributes lizardon;
    itLuckyAttributes lucky;
    itLuckyEggAttributes lucky_egg;
    itLugiaAttributes lugia;
    itLugiaAeroblastAttributes lugia_aeroblast;
    itLuigiFireballAttributes luigi_fireball;
    itMDisableAttributes m_disable;
    itMarilAttributes maril;
    itMarumineAttributes marumine;
    itMarioFireballAttributes mario_fireball;
    itMasterHandBulletAttributes master_hand_bullet;
    itMasterHandLaserAttributes master_hand_laser;
    itMatadogasAttributes matadogas;
    ItMetamonVars metamon;
    MewVars mew;
    itMewtwoShadowball_DatAttrs mewtwo_shadowball;
    itNessPKFirepillarAttributes ness_pk_firepillar;
    itNokoNoko_DatAttrs noko_noko;
    itOctarockAttributes octarock;
    itOldkuriAttributes oldkuri;
    itOldottoseaAttributes oldottosea;
    itPatapataAttributes patapata;
    itPeachToadSporeAttributes peach_toad_spore;
    itPeachTurnipAttributes peach_turnip;
    itPikachutJoltGroundAttributes pikachut_jolt_ground;
    itPikachuthunderAttributes pikachuthunder;
    itPKThunderAttributes pk_thunder;
    itPippiAttributes pippi;
    itPokemonSpawn_DatAttrs pokemon_spawn;
    itSamusBombAttributes samus_bomb;
    itSamusChargeShot_Attributes samus_charge_shot;
    itSamusGrappleAttributes samus_grapple;
    itSamusMissileAttributes samus_missile;
    itSanseijuuAttributes sanseijuu;
    itSeakChain_Attrs seak_chain;
    itSeakNeedleThrownAttributes seak_needle_thrown;
    itsonansAttributes sonans;
    itSwordAttributes sword;
    struct TetherAttributes tether;
    itThunderPokemonAttributes thunder_pokemon;
    itTincleAttributes tincle;
    itTogepyAttributes togepy;
    itToolsAttributes tools;
    itTosakinto_Attrs tosakinto;
    itUnkAttributes unk1;
    it_2728_DatAttrs unk_2728;
    it_2E5A_Attrs unk_2e5a;
    itUnknownAttributes unknown;
    itWhispyAppleAttributes whispy_apple;
    itWhiteBeaAttributes white_bea;
    itYoshiEggThrowAttributes yoshi_egg_throw;
    StarAttrs yoshi_star;
    itYoyoAttributes yoyo;
    ItZeldaDinFire_ItemVars zelda_din_fire;
    itZeldaDinFireExplodeAttributes zelda_din_fire_explode;
    itZGShell_Attrs zg_shell;
};

#endif
