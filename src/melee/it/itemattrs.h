#ifndef MELEE_IT_ITEMATTRS_H
#define MELEE_IT_ITEMATTRS_H

#include <Runtime/platform.h>

#include <dat_macros.h>

#include <dolphin/mtx.h>
#include <melee/ft/kinds/ftCommon/types.h>
#include <melee/ft/kinds/ftSeak/types.h>
#include <melee/it/itCharItems.h>
#include <melee/it/itCommonItems.h>
#include <melee/it/itPKFlash.h>
#include <melee/it/itPKThunder.h>
#include <melee/it/itYoyo.h>

/// Charizard flame attributes (#It_Kind_Lizardon_Flame1 through 4).
/// Their code reads these fields through #itLizardonAttributes.
struct itLizardonFlameAttributes {
    /* +0 */ f32 x0; ///< Lifetime, for #it_80275158
    /* +4 */ f32 x4; ///< Velocity multiplier
};

/// Unused attributes stored as words up to the next object.
struct itUnreadAttributes {
    /* +0 */ s32 x0[1] DAT_EXTENT;
};

typedef struct ArwingLaserAttr {
    /* +0 */ itSpecialAttrsHead* x0;
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

typedef struct itHassamAttributes {
    /* +00 */ f32 x0;
    /* +04 */ f32 x4;
    /* +08 */ f32 x8;
    /* +0C */ f32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ s32 x18;
    /* +1C */ s32 x1C;
    /* +20 */ s32 x20;
    /* +24 */ f32 x24;
    /* +28 */ f32 x28;
    /* +2C */ f32 x2C;
    /* +30 */ f32 x30;
    /* +34 */ f32 x34;
    /* +38 */ f32 x38;
    /* +3C */ s32 x3C;
    /* +40 */ s32 x40;
    /* +44 */ s32 x44;
} itHassamAttributes;

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
    itSpecialAttrsHead* x0;
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
    itSwordAttributes sword DAT_IF(Article::kind == It_Kind_Sword);
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
    itLeadeadAttributes leadead DAT_IF(Article::kind == It_Kind_Leadead);
    itOctarockAttributes octarock DAT_IF(Article::kind == It_Kind_Octarock);
    itMarioFireballAttributes
        mario_fireball DAT_IF(Article::kind == It_Kind_Mario_Fire ||
                              Article::kind == It_Kind_Kirby_MarioFire);
    itDrMarioPillAttributes
        dr_mario_pill DAT_IF(Article::kind == It_Kind_DrMario_Vitamin ||
                             Article::kind == It_Kind_Kirby_DrMarioVitamin);
    itKirbyCutterBeamAttributes kirby_cutter_beam DAT_IF(Article::kind ==
                                                         It_Kind_Kirby_CBeam);
    FoxLaserAttr fox_laser DAT_IF(Article::kind == It_Kind_Fox_Laser ||
                                  Article::kind == It_Kind_Falco_Laser ||
                                  Article::kind == It_Kind_Kirby_FoxLaser ||
                                  Article::kind == It_Kind_Kirby_FalcoLaser);
    FoxIllusionAttr
        fox_illusion DAT_IF(Article::kind == It_Kind_Fox_Illusion ||
                            Article::kind == It_Kind_Falco_Phantasm);
    itLinkBombAttributes link_bomb DAT_IF(Article::kind == It_Kind_Link_Bomb ||
                                          Article::kind == It_Kind_CLink_Bomb);
    itLinkBoomerangAttributes
        link_boomerang DAT_IF(Article::kind == It_Kind_Link_Boomerang ||
                              Article::kind == It_Kind_CLink_Boomerang);
    itLinkHookshotAttributes
        link_hookshot DAT_IF(Article::kind == It_Kind_Link_HShot ||
                             Article::kind == It_Kind_CLink_HShot);
    itLinkArrowAttributes
        link_arrow DAT_IF(Article::kind == It_Kind_Link_Arrow ||
                          Article::kind == It_Kind_CLink_Arrow ||
                          Article::kind == It_Kind_Kirby_LinkArrow ||
                          Article::kind == It_Kind_Kirby_CLinkArrow);
    itNessPKFirepillarAttributes
        ness_pk_firepillar DAT_IF(Article::kind == It_Kind_Ness_PKFire ||
                                  Article::kind == It_Kind_Ness_PKFire_Flame);
    itFlashAttributes flash DAT_IF(Article::kind == It_Kind_Ness_PKFlush ||
                                   Article::kind == It_Kind_Kirby_NessPKFlush);
    itPKThunderAttributes pk_thunder DAT_IF(Article::kind ==
                                            It_Kind_Ness_PKThunder);
    itFlashExplAttributes
        flash_expl DAT_IF(Article::kind == It_Kind_Ness_PKFlush_Explode ||
                          Article::kind == It_Kind_Kirby_NessPKFlush_Explode);
    itSeakNeedleThrownAttributes seak_needle_thrown
        DAT_IF(Article::kind == It_Kind_Seak_NeedleThrow ||
               Article::kind == It_Kind_Kirby_SeakNeedleThrow);
    itPikachuthunderAttributes
        pikachuthunder DAT_IF(Article::kind == It_Kind_Pikachu_Thunder ||
                              Article::kind == It_Kind_Pichu_Thunder);
    itYoshiEggThrowAttributes yoshi_egg_throw DAT_IF(Article::kind ==
                                                     It_Kind_Yoshi_EggThrow);
    StarAttrs yoshi_star DAT_IF(Article::kind == It_Kind_Yoshi_Star);
    itPikachutJoltGroundAttributes pikachut_jolt_ground
        DAT_IF(Article::kind == It_Kind_Pikachu_TJolt_Ground ||
               Article::kind == It_Kind_Pichu_TJolt_Ground ||
               Article::kind == It_Kind_Kirby_PikachuTJolt_Ground ||
               Article::kind == It_Kind_Kirby_PichuTJolt_Ground);
    itSamusBombAttributes samus_bomb DAT_IF(Article::kind ==
                                            It_Kind_Samus_Bomb);
    itSamusChargeShot_Attributes
        samus_charge_shot DAT_IF(Article::kind == It_Kind_Samus_Charge ||
                                 Article::kind == It_Kind_Kirby_SamusCharge);
    itSamusMissileAttributes samus_missile DAT_IF(Article::kind ==
                                                  It_Kind_Samus_Missile);
    itSamusGrappleAttributes samus_grapple DAT_IF(Article::kind ==
                                                  It_Kind_Samus_GBeam);
    itSeakChain_Attrs seak_chain DAT_IF(Article::kind == It_Kind_Seak_Chain);
    itPeachTurnipAttributes peach_turnip DAT_IF(Article::kind ==
                                                It_Kind_Peach_Turnip);
    itKoopaFlame_Attributes
        koopa_flame DAT_IF(Article::kind == It_Kind_Koopa_Flame ||
                           Article::kind == It_Kind_Kirby_KoopaFlame);
    itYoyoAttributes yoyo DAT_IF(Article::kind == It_Kind_Ness_Yoyo);
    itLuigiFireballAttributes
        luigi_fireball DAT_IF(Article::kind == It_Kind_Luigi_Fire ||
                              Article::kind == It_Kind_Kirby_LuigiFire);
    itClimbersIceAttributes
        climbers_ice DAT_IF(Article::kind == It_Kind_IceClimber_Ice ||
                            Article::kind == It_Kind_Kirby_IceClimberIce);
    itClimbersBlizzardAttributes
        climbers_blizzard DAT_IF(Article::kind == It_Kind_IceClimber_Blizzard);
    ItZeldaDinFire_ItemVars zelda_din_fire DAT_IF(Article::kind ==
                                                  It_Kind_Zelda_DinFire);
    itZeldaDinFireExplodeAttributes zelda_din_fire_explode
        DAT_IF(Article::kind == It_Kind_Zelda_DinFire_Explode);
    itMDisableAttributes m_disable DAT_IF(Article::kind ==
                                          It_Kind_Mewtwo_Disable);
    itPeachToadSporeAttributes
        peach_toad_spore DAT_IF(Article::kind == It_Kind_Peach_ToadSpore ||
                                Article::kind == It_Kind_Kirby_PeachToadSpore);
    itMewtwoShadowball_DatAttrs mewtwo_shadowball
        DAT_IF(Article::kind == It_Kind_Mewtwo_ShadowBall ||
               Article::kind == It_Kind_Kirby_MewtwoShadowBall);
    itClimbersStringAttributes
        climbers_string DAT_IF(Article::kind == It_Kind_IceClimber_GumStrings);
    itGamewatchAttributes
        gamewatch DAT_IF(Article::kind == It_Kind_GameWatch_Greenhouse ||
                         Article::kind == It_Kind_GameWatch_Manhole ||
                         Article::kind == It_Kind_GameWatch_Fire ||
                         Article::kind == It_Kind_GameWatch_Parachute ||
                         Article::kind == It_Kind_GameWatch_Turtle ||
                         Article::kind == It_Kind_GameWatch_Breath ||
                         Article::kind == It_Kind_GameWatch_Judge ||
                         Article::kind == It_Kind_GameWatch_Panic ||
                         Article::kind == It_Kind_GameWatch_Rescue ||
                         Article::kind == It_Kind_Kirby_GameWatchChefPan);
    itGamewatchchefAttributes
        gamewatchchef DAT_IF(Article::kind == It_Kind_GameWatch_Chef ||
                             Article::kind == It_Kind_Kirby_GameWatchChef);
    itMasterHandLaserAttributes
        master_hand_laser DAT_IF(Article::kind == It_Kind_MasterHand_Laser ||
                                 Article::kind == It_Kind_CrazyHand_Laser);
    itMasterHandBulletAttributes
        master_hand_bullet DAT_IF(Article::kind == It_Kind_MasterHand_Bullet ||
                                  Article::kind == It_Kind_CrazyHand_Bullet);
    itCrazyHandBombAttributes crazy_hand_bomb DAT_IF(Article::kind ==
                                                     It_Kind_CrazyHand_Bomb);
    itCoinAttributes coin DAT_IF(Article::kind == It_Kind_Coin);
    itTosakinto_Attrs tosakinto DAT_IF(Article::kind == It_PKind_Tosakinto);
    itChicoritaAttr chicorita DAT_IF(Article::kind == It_PKind_Chicorita);
    itKabigonAttributes kabigon DAT_IF(Article::kind == It_PKind_Kabigon);
    itKamexAttributes kamex DAT_IF(Article::kind == It_PKind_Kamex);
    itMatadogasAttributes
        matadogas DAT_IF(Article::kind == It_PKind_Matadogas ||
                         Article::kind == It_Kind_Matadogas_Gas1 ||
                         Article::kind == It_Kind_Matadogas_Gas2);
    itLizardonAttributes lizardon DAT_IF(Article::kind == It_PKind_Lizardon);
    itLizardonFlameAttributes
        lizardon_flame DAT_IF(Article::kind == It_Kind_Lizardon_Flame1 ||
                              Article::kind == It_Kind_Lizardon_Flame2 ||
                              Article::kind == It_Kind_Lizardon_Flame3 ||
                              Article::kind == It_Kind_Lizardon_Flame4);
    itFireAttributes fire DAT_IF(Article::kind == It_PKind_Fire);
    itThunderPokemonAttributes thunder_pokemon DAT_IF(Article::kind ==
                                                      It_PKind_Thunder);
    itFreezerAttributes freezer DAT_IF(Article::kind == It_PKind_Freezer);
    itsonansAttributes sonans DAT_IF(Article::kind == It_PKind_Sonans);
    itHassamAttributes hassam DAT_IF(Article::kind == It_PKind_Hassam);
    itUnknownAttributes unknown DAT_IF(Article::kind == It_PKind_Unknown ||
                                       Article::kind == It_Kind_Unknown_Swarm);
    itSanseijuuAttributes sanseijuu DAT_IF(Article::kind == It_PKind_Entei ||
                                           Article::kind == It_PKind_Raikou ||
                                           Article::kind == It_PKind_Suikun);
    itkireihanaAttributes kireihana DAT_IF(Article::kind ==
                                           It_PKind_Kireihana);
    itMarumineAttributes marumine DAT_IF(Article::kind == It_PKind_Marumine);
    itLugiaAttributes lugia DAT_IF(Article::kind == It_PKind_Lugia);
    itHououAttr houou DAT_IF(Article::kind == It_PKind_Houou ||
                             Article::kind == It_Kind_Houou_SacredFire);
    ItMetamonVars metamon DAT_IF(Article::kind == It_PKind_Metamon);
    itPippiAttributes pippi DAT_IF(Article::kind == It_PKind_Pippi);
    itTogepyAttributes togepy DAT_IF(Article::kind == It_PKind_Togepy);
    MewVars mew DAT_IF(Article::kind == It_PKind_Mew);
    itCerebiAttributes cerebi DAT_IF(Article::kind == It_PKind_Cerebi);
    itHitodemanAttributes
        hitodeman DAT_IF(Article::kind == It_PKind_Hitodeman ||
                         Article::kind == It_Kind_Hitodeman_Star);
    itLuckyAttributes lucky DAT_IF(Article::kind == It_PKind_Lucky);
    itHinoarashiAttributes
        hinoarashi DAT_IF(Article::kind == It_PKind_Hinoarashi ||
                          Article::kind == It_Kind_Hinoarashi_Flame);
    itMarilAttributes maril DAT_IF(Article::kind == It_PKind_Maril);
    itFushigibanaAttributes fushigibana DAT_IF(Article::kind ==
                                               It_PKind_Fushigibana);
    itChicoritaLeafAttr chicorita_leaf DAT_IF(Article::kind ==
                                              It_Kind_Chicorita_Leaf);
    itKamexHydroPumpAttributes
        kamex_hydro_pump DAT_IF(Article::kind == It_Kind_Kamex_HydroPump);
    itLugiaAeroblastAttributes
        lugia_aeroblast DAT_IF(Article::kind == It_Kind_Lugia_Aeroblast ||
                               Article::kind == It_Kind_Lugia_Aeroblast2 ||
                               Article::kind == It_Kind_Lugia_Aeroblast3);
    itLuckyEggAttributes lucky_egg DAT_IF(Article::kind == It_Kind_Lucky_Egg);

    itOldkuriAttributes oldkuri DAT_IF(Article::kind == It_Kind_Old_Kuri);
    itHeihoAttributes heiho DAT_IF(Article::kind == It_Kind_Heiho);
    itNokoNoko_DatAttrs noko_noko DAT_IF(Article::kind == It_Kind_Nokonoko);
    itPatapataAttributes patapata DAT_IF(Article::kind == It_Kind_Patapata);
    itLikelikeAttributes likelike DAT_IF(Article::kind == It_Kind_Likelike);
    itOldottoseaAttributes oldottosea DAT_IF(Article::kind ==
                                             It_Kind_Old_Otto);
    itWhiteBeaAttributes white_bea DAT_IF(Article::kind == It_Kind_Whitebea);
    itZGShell_Attrs zg_shell DAT_IF(Article::kind == It_Kind_ZGShell);
    itTincleAttributes tincle DAT_IF(Article::kind == It_Kind_Tincle);
    itWhispyAppleAttributes
        whispy_apple DAT_IF(Article::kind == It_Kind_WhispyApple ||
                            Article::kind == It_Kind_WhispyHealApple);
    itToolsAttributes tools DAT_IF(Article::kind == It_Kind_Tools);
    itKyasarinAttributes kyasarin DAT_IF(Article::kind == It_Kind_Kyasarin);
    ArwingLaserAttr arwing_laser DAT_IF(Article::kind == It_Kind_Arwing_Laser);
    itGreatFoxLaser_Attrs great_fox_laser DAT_IF(Article::kind ==
                                                 It_Kind_GreatFox_Laser);
    itKyasarinEggAttributes kyasarin_egg DAT_IF(Article::kind ==
                                                It_Kind_Kyasarin_Egg);
    /// Monsters and stage items whose code reads none of their attributes:
    /// only the record they start with is known.
    itSpecialAttrsHead* head DAT_IF(Article::kind == It_Kind_Kuriboh ||
                                    Article::kind == It_Kind_Ottosea ||
                                    Article::kind == It_Kind_Mato ||
                                    Article::kind == It_Kind_Klap ||
                                    Article::kind == It_Kind_ZRShell);
    it_2E5A_Attrs unk_2e5a DAT_IF(Article::kind == It_Kind_Unk4);
    /// Unused item attributes, including fighter item slots registered with
    /// no kind.
    itUnreadAttributes unread DAT_IF(
        Article::kind == It_Kind_ScBall || Article::kind == It_Kind_Spycloak ||
        Article::kind == It_Kind_Mario_Cape ||
        Article::kind == It_Kind_DrMario_Sheet ||
        Article::kind == It_Kind_Fox_Blaster ||
        Article::kind == It_Kind_Falco_Blaster ||
        Article::kind == It_Kind_Link_Bow ||
        Article::kind == It_Kind_CLink_Bow || Article::kind == It_Kind_Unk1 ||
        Article::kind == It_Kind_Ness_PKThunder4 ||
        Article::kind == It_Kind_Ness_Bat ||
        Article::kind == It_Kind_Pikachu_TJolt_Air ||
        Article::kind == It_Kind_Pichu_TJolt_Air ||
        Article::kind == It_Kind_Peach_Parasol ||
        Article::kind == It_Kind_Peach_Toad ||
        Article::kind == It_Kind_Seak_NeedleHeld ||
        Article::kind == It_Kind_Kirby_FoxBlaster ||
        Article::kind == It_Kind_Kirby_FalcoBlaster ||
        Article::kind == It_Kind_Kirby_LinkBow ||
        Article::kind == It_Kind_Kirby_CLinkBow ||
        Article::kind == It_Kind_Kirby_SeakNeedleHeld ||
        Article::kind == It_Kind_Kirby_PeachToad ||
        Article::kind == It_Kind_Kirby_PikachuTJolt_Air ||
        Article::kind == It_Kind_Kirby_PichuTJolt_Air ||
        Article::kind == It_Kind_Pokemon_Unk || Article::kind == It_Kind_None);
    // Other layouts and shared views used by item callers.
    struct itChainSegment chain_segment;
    itPokemonSpawn_DatAttrs pokemon_spawn;
    struct TetherAttributes tether;
    itUnkAttributes unk1;
    it_2728_DatAttrs unk_2728;
};

#endif
