#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include <functions.h>
#include <melee/pl/player.h>
#include <melee/gr/stage.h>
#include <math.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/controller.h>
#include <melee/lb/lbrefract.h>
#include <sysdolphin/baselib/archive.h>
#include <common_structs.h>
#include <melee/ft/ftstatevars.h>

BOOL func_80081298(HSD_GObj* gobj);

typedef enum FighterKind
{
    FTKIND_MARIO,
    FTKIND_FOX,
    FTKIND_CAPTAIN,
    FTKIND_DONKEY,
    FTKIND_KIRBY,
    FTKIND_KOOPA,
    FTKIND_LINK,
    FTKIND_SEAK,
    FTKIND_NESS,
    FTKIND_PEACH,
    FTKIND_POPO,
    FTKIND_NANA,
    FTKIND_PIKACHU,
    FTKIND_SAMUS,
    FTKIND_YOSHI,
    FTKIND_PURIN,
    FTKIND_MEWTWO,
    FTKIND_LUIGI,
    FTKIND_MARS,
    FTKIND_ZELDA,
    FTKIND_CLINK,
    FTKIND_DRMARIO,
    FTKIND_FALCO,
    FTKIND_PICHU,
    FTKIND_GAMEWATCH,
    FTKIND_GANON,
    FTKIND_EMBLEM,
    FTKIND_MASTERH,
    FTKIND_CREZYH,
    FTKIND_BOY,
    FTKIND_GIRL,
    FTKIND_GKOOPS,
    FTKIND_SANDBAG,
    FTKIND_NONE

} FighterKind;

typedef enum CharacterKind
{
    CKIND_CAPTAIN, // Captain Falcon (Captain) //
    CKIND_DONKEY, // Donkey Kong (Donkey) //
    CKIND_FOX, // Fox //
    CKIND_GAMEWATCH, // Mr. Game & Watch (GameWatch) //
    CKIND_KIRBY, // Kirby //
    CKIND_KOOPA, // Bowser (Koopa) //
    CKIND_LINK, // Link //
    CKIND_LUIGI, // Luigi // 
    CKIND_MARIO, // Mario //
    CKIND_MARS, // Marth (Mars) //
    CKIND_MEWTWO, // Mewtwo //
    CKIND_NESS, // Ness// 
    CKIND_PEACH, // Peach //
    CKIND_PIKACHU, // Pikachu //
    CKIND_POPONANA, // Ice Climbers (Popo & Nana) //
    CKIND_PURIN, // Jigglypuff (Purin) //
    CKIND_SAMUS, // Samus //
    CKIND_YOSHI, // Yoshi //
    CKIND_ZELDA, // Zelda (ZE->SE) //
    CKIND_SEAK, // Sheik (SE->ZE) //
    CKIND_FALCO, // Falco //
    CKIND_CLINK, // Young Link (CLink) //
    CKIND_DRMARIO, // Dr. Mario //
    CKIND_EMBLEM, // Roy (Emblem) //
    CKIND_PICHU, // Pichu //
    CKIND_GANON, // Ganondorf (Ganon) //
    CKIND_MASTERH, // Master Hand (MasterH) //
    CKIND_BOY, // Male Wireframe (Boy) //
    CKIND_GIRL, // Female Wireframe (Girl) //
    CKIND_GKOOPS, // Giga Bowser (GKoops) //
    CKIND_CREZYH, // Crazy Hand (CrezyH) //
    CHKIND_SANDBAG, // Sandbag //
    CHKIND_POPO, // Popo //
    CHKIND_NONE // None //

} CharacterKind;

// Action State Change flags

#define FIGHTER_FASTFALL_PRESERVE 0x1
#define FIGHTER_GFX_PRESERVE 0x2
#define FIGHTER_HITSTATUS_COLANIM_PRESERVE 0x4 // Preserve full body collision state //
#define FIGHTER_HIT_NOUPDATE 0x8 // Keep hitboxes
#define FIGHTER_MODEL_NOUPDATE 0x10 // Ignore model state change (?) 
#define FIGHTER_ANIMVEL_NOUPDATE 0x20
#define FIGHTER_UNK_0x40 0x40
#define FIGHTER_MATANIM_NOUPDATE 0x80 // Ignore switching to character's "hurt" textures (?) //
#define FIGHTER_THROW_EXCEPTION_NOUPDATE 0x100 // Resets thrower GObj pointer to NULL if false? //
#define FIGHTER_SFX_PRESERVE 0x200
#define FIGHTER_PARASOL_NOUPDATE 0x400 // Ignore Parasol state change //
#define FIGHTER_RUMBLE_NOUPDATE 0x800 // Ignore rumble update? //
#define FIGHTER_COLANIM_NOUPDATE 0x1000
#define FIGHTER_ACCESSORY_PRESERVE 0x2000 // Keep respawn platform? //
#define FIGHTER_CMD_UPDATE 0x4000 // Run all Subaction Events up to the current animation frame //
#define FIGHTER_NAMETAGVIS_NOUPDATE 0x8000
#define FIGHTER_PART_HITSTATUS_COLANIM_PRESERVE 0x10000 // Assume this is for individual bones? //
#define FIGHTER_SWORDTRAIL_PRESERVE 0x20000
#define FIGHTER_ITEMVIS_NOUPDATE 0x40000 // Used by Ness during Up/Down Smash, I suppose this is what the flag does //
#define FIGHTER_SKIP_UNK_0x2222 0x80000 // Skips updating bit 0x20 of 0x2222? //
#define FIGHTER_PHYS_UNKUPDATE 0x100000
#define FIGHTER_FREEZESTATE 0x200000 // Sets anim rate to 0x and some other stuff
#define FIGHTER_MODELPART_VIS_NOUPDATE 0x400000
#define FIGHTER_METALB_NOUPDATE 0x800000
#define FIGHTER_UNK_0x1000000 0x1000000
#define FIGHTER_ATTACKCOUNT_NOUPDATE 0x2000000
#define FIGHTER_MODEL_FLAG_NOUPDATE 0x4000000
#define FIGHTER_UNK_0x2227 0x8000000
#define FIGHTER_HITSTUN_FLAG_NOUPDATE 0x10000000
#define FIGHTER_ANIM_NOUPDATE 0x20000000 // Keeps current fp animation?
#define FIGHTER_UNK_0x40000000 0x40000000 // Unused?
#define FIGHTER_UNK_0x80000000 0x80000000 // Unused?


// LandingFallSpecial flags //

#define IS_INTERRUPTIBLE 1

// Ledge Grab Macros //

#define CLIFFCATCH_BOTH 0
#define CLIFFCATCH_LEFT -1
#define CLIFFCATCH_RIGHT 1

// Ternary macro for fcmpo-based facing direction check 

#define CLIFFCATCH_O(fp) \
((fp)->x2C_facing_direction < 0.0f) ? CLIFFCATCH_LEFT : CLIFFCATCH_RIGHT \

// Ternary macro for fcmpu-based facing direction check

#define CLIFFCATCH_U(fp) \
((fp)->x2C_facing_direction != 1.0f) ? CLIFFCATCH_LEFT : CLIFFCATCH_RIGHT \

typedef enum ftCommonAction
{
    ASID_DEADDOWN,
    ASID_DEADLEFT,
    ASID_DEADRIGHT,
    ASID_DEADUP,
    ASID_DEADUPSTAR,
    ASID_DEADUPSTARICE,
    ASID_DEADUPFALL,
    ASID_DEADUPFALLHITCAMERA,
    ASID_DEADUPFALLHITCAMERAFLAT,
    ASID_DEADUPFALLICE,
    ASID_DEADUPFALLHITCAMERAICE,
    ASID_SLEEP,
    ASID_REBIRTH,
    ASID_REBIRTHWAIT,
    ASID_WAIT,
    ASID_WALKSLOW,
    ASID_WALKMIDDLE,
    ASID_WALKFAST,
    ASID_TURN,
    ASID_TURNRUN,
    ASID_DASH,
    ASID_RUN,
    ASID_RUNDIRECT,
    ASID_RUNBRAKE,
    ASID_KNEEBEND,
    ASID_JUMPF,
    ASID_JUMPB,
    ASID_JUMPAERIALF,
    ASID_JUMPAERIALB,
    ASID_FALL,
    ASID_FALLF,
    ASID_FALLB,
    ASID_FALLAERIAL,
    ASID_FALLAERIALF,
    ASID_FALLAERIALB,
    ASID_FALLSPECIAL,
    ASID_FALLSPECIALF,
    ASID_FALLSPECIALB,
    ASID_DAMAGEFALL,
    ASID_SQUAT,
    ASID_SQUATWAIT,
    ASID_SQUATRV,
    ASID_LANDING,
    ASID_LANDINGFALLSPECIAL,
    ASID_ATTACK11,
    ASID_ATTACK12,
    ASID_ATTACK13,
    ASID_ATTACK100START,
    ASID_ATTACK100LOOP,
    ASID_ATTACK100END,
    ASID_ATTACKDASH,
    ASID_ATTACKS3HI,
    ASID_ATTACKS3HIS,
    ASID_ATTACKS3S,
    ASID_ATTACKS3LWS,
    ASID_ATTACKS3LW,
    ASID_ATTACKHI3,
    ASID_ATTACKLW3,
    ASID_ATTACKS4HI,
    ASID_ATTACKS4HIS,
    ASID_ATTACKS4S,
    ASID_ATTACKS4LWS,
    ASID_ATTACKS4LW,
    ASID_ATTACKHI4,
    ASID_ATTACKLW4,
    ASID_ATTACKAIRN,
    ASID_ATTACKAIRF,
    ASID_ATTACKAIRB,
    ASID_ATTACKAIRHI,
    ASID_ATTACKAIRLW,
    ASID_LANDINGAIRN,
    ASID_LANDINGAIRF,
    ASID_LANDINGAIRB,
    ASID_LANDINGAIRHI,
    ASID_LANDINGAIRLW,
    ASID_DAMAGEHI1,
    ASID_DAMAGEHI2,
    ASID_DAMAGEHI3,
    ASID_DAMAGEN1,
    ASID_DAMAGEN2,
    ASID_DAMAGEN3,
    ASID_DAMAGELW1,
    ASID_DAMAGELW2,
    ASID_DAMAGELW3,
    ASID_DAMAGEAIR1,
    ASID_DAMAGEAIR2,
    ASID_DAMAGEAIR3,
    ASID_DAMAGEFLYHI,
    ASID_DAMAGEFLYN,
    ASID_DAMAGEFLYLW,
    ASID_DAMAGEFLYTOP,
    ASID_DAMAGEFLYROLL,
    ASID_LIGHTGET,
    ASID_HEAVYGET,
    ASID_LIGHTTHROWF,
    ASID_LIGHTTHROWB,
    ASID_LIGHTTHROWHI,
    ASID_LIGHTTHROWLW,
    ASID_LIGHTTHROWDASH,
    ASID_LIGHTTHROWDROP,
    ASID_LIGHTTHROWAIRF,
    ASID_LIGHTTHROWAIRB,
    ASID_LIGHTTHROWAIRHI,
    ASID_LIGHTTHROWAIRLW,
    ASID_HEAVYTHROWF,
    ASID_HEAVYTHROWB,
    ASID_HEAVYTHROWHI,
    ASID_HEAVYTHROWLW,
    ASID_LIGHTTHROWF4,
    ASID_LIGHTTHROWB4,
    ASID_LIGHTTHROWHI4,
    ASID_LIGHTTHROWLW4,
    ASID_LIGHTTHROWAIRF4,
    ASID_LIGHTTHROWAIRB4,
    ASID_LIGHTTHROWAIRHI4,
    ASID_LIGHTTHROWAIRLW4,
    ASID_HEAVYTHROWF4,
    ASID_HEAVYTHROWB4,
    ASID_HEAVYTHROWHI4,
    ASID_HEAVYTHROWLW4,
    ASID_SWORDSWING1,
    ASID_SWORDSWING3,
    ASID_SWORDSWING4,
    ASID_SWORDSWINGDASH,
    ASID_BATSWING1,
    ASID_BATSWING3,
    ASID_BATSWING4,
    ASID_BATSWINGDASH,
    ASID_PARASOLSWING1,
    ASID_PARASOLSWING3,
    ASID_PARASOLSWING4,
    ASID_PARASOLSWINGDASH,
    ASID_HARISENSWING1,
    ASID_HARISENSWING3,
    ASID_HARISENSWING4,
    ASID_HARISENSWINGDASH,
    ASID_STARRODSWING1,
    ASID_STARRODSWING3,
    ASID_STARRODSWING4,
    ASID_STARRODSWINGDASH,
    ASID_LIPSTICKSWING1,
    ASID_LIPSTICKSWING3,
    ASID_LIPSTICKSWING4,
    ASID_LIPSTICKSWINGDASH,
    ASID_ITEMPARASOLOPEN,
    ASID_ITEMPARASOLFALL,
    ASID_ITEMPARASOLFALLSPECIAL,
    ASID_ITEMPARASOLDAMAGEFALL,
    ASID_LGUNSHOOT,
    ASID_LGUNSHOOTAIR,
    ASID_LGUNSHOOTEMPTY,
    ASID_LGUNSHOOTAIREMPTY,
    ASID_FIREFLOWERSHOOT,
    ASID_FIREFLOWERSHOOTAIR,
    ASID_ITEMSCREW,
    ASID_ITEMSCREWAIR,
    ASID_DAMAGESCREW,
    ASID_DAMAGESCREWAIR,
    ASID_ITEMSCOPESTART,
    ASID_ITEMSCOPERAPID,
    ASID_ITEMSCOPEFIRE,
    ASID_ITEMSCOPEEND,
    ASID_ITEMSCOPEAIRSTART,
    ASID_ITEMSCOPEAIRRAPID,
    ASID_ITEMSCOPEAIRFIRE,
    ASID_ITEMSCOPEAIREND,
    ASID_ITEMSCOPESTARTEMPTY,
    ASID_ITEMSCOPERAPIDEMPTY,
    ASID_ITEMSCOPEFIREEMPTY,
    ASID_ITEMSCOPEENDEMPTY,
    ASID_ITEMSCOPEAIRSTARTEMPTY,
    ASID_ITEMSCOPEAIRRAPIDEMPTY,
    ASID_ITEMSCOPEAIRFIREEMPTY,
    ASID_ITEMSCOPEAIRENDEMPTY,
    ASID_LIFTWAIT,
    ASID_LIFTWALK1,
    ASID_LIFTWALK2,
    ASID_LIFTTURN,
    ASID_GUARDON,
    ASID_GUARD,
    ASID_GUARDOFF,
    ASID_GUARDSETOFF,
    ASID_GUARDREFLECT,
    ASID_DOWNBOUNDU,
    ASID_DOWNWAITU,
    ASID_DOWNDAMAGEU,
    ASID_DOWNSTANDU,
    ASID_DOWNATTACKU,
    ASID_DOWNFOWARDU,
    ASID_DOWNBACKU,
    ASID_DOWNSPOTU,
    ASID_DOWNBOUNDD,
    ASID_DOWNWAITD,
    ASID_DOWNDAMAGED,
    ASID_DOWNSTANDD,
    ASID_DOWNATTACKD,
    ASID_DOWNFOWARDD,
    ASID_DOWNBACKD,
    ASID_DOWNSPOTD,
    ASID_PASSIVE,
    ASID_PASSIVESTANDF,
    ASID_PASSIVESTANDB,
    ASID_PASSIVEWALL,
    ASID_PASSIVEWALLJUMP,
    ASID_PASSIVECEIL,
    ASID_SHIELDBREAKFLY,
    ASID_SHIELDBREAKFALL,
    ASID_SHIELDBREAKDOWNU,
    ASID_SHIELDBREAKDOWND,
    ASID_SHIELDBREAKSTANDU,
    ASID_SHIELDBREAKSTANDD,
    ASID_FURAFURA,
    ASID_CATCH,
    ASID_CATCHPULL,
    ASID_CATCHDASH,
    ASID_CATCHDASHPULL,
    ASID_CATCHWAIT,
    ASID_CATCHATTACK,
    ASID_CATCHCUT,
    ASID_THROWF,
    ASID_THROWB,
    ASID_THROWHI,
    ASID_THROWLW,
    ASID_CAPTUREPULLEDHI,
    ASID_CAPTUREWAITHI,
    ASID_CAPTUREDAMAGEHI,
    ASID_CAPTUREPULLEDLW,
    ASID_CAPTUREWAITLW,
    ASID_CAPTUREDAMAGELW,
    ASID_CAPTURECUT,
    ASID_CAPTUREJUMP,
    ASID_CAPTURENECK,
    ASID_CAPTUREFOOT,
    ASID_ESCAPEF,
    ASID_ESCAPEB,
    ASID_ESCAPE,
    ASID_ESCAPEAIR,
    ASID_REBOUNDSTOP,
    ASID_REBOUND,
    ASID_THROWNF,
    ASID_THROWNB,
    ASID_THROWNHI,
    ASID_THROWNLW,
    ASID_THROWNLWWOMEN,
    ASID_PASS,
    ASID_OTTOTTO,
    ASID_OTTOTTOWAIT,
    ASID_FLYREFLECTWALL,
    ASID_FLYREFLECTCEIL,
    ASID_STOPWALL,
    ASID_STOPCEIL,
    ASID_MISSFOOT,
    ASID_CLIFFCATCH,
    ASID_CLIFFWAIT,
    ASID_CLIFFCLIMBSLOW,
    ASID_CLIFFCLIMBQUICK,
    ASID_CLIFFATTACKSLOW,
    ASID_CLIFFATTACKQUICK,
    ASID_CLIFFESCAPESLOW,
    ASID_CLIFFESCAPEQUICK,
    ASID_CLIFFJUMPSLOW1,
    ASID_CLIFFJUMPSLOW2,
    ASID_CLIFFJUMPQUICK1,
    ASID_CLIFFJUMPQUICK2,
    ASID_APPEALR,
    ASID_APPEALL,
    ASID_SHOULDEREDWAIT,
    ASID_SHOULDEREDWALKSLOW,
    ASID_SHOULDEREDWALKMIDDLE,
    ASID_SHOULDEREDWALKFAST,
    ASID_SHOULDEREDTURN,
    ASID_THROWNFF,
    ASID_THROWNFB,
    ASID_THROWNFHI,
    ASID_THROWNFLW,
    ASID_CAPTURECAPTAIN,
    ASID_CAPTUREYOSHI,
    ASID_YOSHIEGG,
    ASID_CAPTUREKOOPA,
    ASID_CAPTUREDAMAGEKOOPA,
    ASID_CAPTUREWAITKOOPA,
    ASID_THROWNKOOPAF,
    ASID_THROWNKOOPAB,
    ASID_CAPTUREKOOPAAIR,
    ASID_CAPTUREDAMAGEKOOPAAIR,
    ASID_CAPTUREWAITKOOPAAIR,
    ASID_THROWNKOOPAAIRF,
    ASID_THROWNKOOPAAIRB,
    ASID_CAPTUREKIRBY,
    ASID_CAPTUREWAITKIRBY,
    ASID_THROWNKIRBYSTAR,
    ASID_THROWNCOPYSTAR,
    ASID_THROWNKIRBY,
    ASID_BARRELWAIT,
    ASID_BURY,
    ASID_BURYWAIT,
    ASID_BURYJUMP,
    ASID_DAMAGESONG,
    ASID_DAMAGESONGWAIT,
    ASID_DAMAGESONGRV,
    ASID_DAMAGEBIND,
    ASID_CAPTUREMEWTWO,
    ASID_CAPTUREMEWTWOAIR,
    ASID_THROWNMEWTWO,
    ASID_THROWNMEWTWOAIR,
    ASID_WARPSTARJUMP,
    ASID_WARPSTARFALL,
    ASID_HAMMERWAIT,
    ASID_HAMMERWALK,
    ASID_HAMMERTURN,
    ASID_HAMMERKNEEBEND,
    ASID_HAMMERFALL,
    ASID_HAMMERJUMP,
    ASID_HAMMERLANDING,
    ASID_KINOKOGIANTSTART,
    ASID_KINOKOGIANTSTARTAIR,
    ASID_KINOKOGIANTEND,
    ASID_KINOKOGIANTENDAIR,
    ASID_KINOKOSMALLSTART,
    ASID_KINOKOSMALLSTARTAIR,
    ASID_KINOKOSMALLEND,
    ASID_KINOKOSMALLENDAIR,
    ASID_ENTRY,
    ASID_ENTRYSTART,
    ASID_ENTRYEND,
    ASID_DAMAGEICE,
    ASID_DAMAGEICEJUMP,
    ASID_CAPTUREMASTERHAND,
    ASID_CAPTUREDAMAGEMASTERHAND,
    ASID_CAPTUREWAITMASTERHAND,
    ASID_THROWNMASTERHAND,
    ASID_CAPTUREKIRBYYOSHI,
    ASID_KIRBYYOSHIEGG,
    ASID_CAPTURELEADEAD,
    ASID_CAPTURELIKELIKE,
    ASID_DOWNREFLECT,
    ASID_CAPTURECRAZYHAND,
    ASID_CAPTUREDAMAGECRAZYHAND,
    ASID_CAPTUREWAITCRAZYHAND,
    ASID_THROWNCRAZYHAND,
    ASID_BARREL
} ftCommonAction;

struct RGBA {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

// Points to data in PlCo.dat
typedef struct _ftCommonData {
    /* 0x0 */ f32 x0;
    /* 0x4 */ f32 x4;
    /* 0x8 */ f32 x8_someStickThreshold;
    /* 0xC */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
    /* 0x18 */ f32 x18;
    /* 0x1C */ f32 x1C;
    /* 0x20 */ f32 x20;
    /* 0x24 */ f32 x24;
    /* 0x28 */ f32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ f32 x30;
    u8 filler_x34[0x70 - 0x34];
    /* 0x70 */ f32 x70_someLStickYMax;
    u8 filler_x74[0x88 - 0x74];
    /* 0x88 */ f32 x88;
    /* 0x8C */ s32 x8C;
    u8 filler_x90[0x98 - 0x90];
    /* 0x98 */ f32 x98_shieldHealthInit;
    u8 filler_x9C[0xEC-0x9C];
    /* 0xEC */ f32 xEC;
    /* 0xF0 */ f32 xF0;
    u8 filler_xF4[0x128-0xF4];
    /* 0x128 */ f32 x128;
    /* 0x12C */ f32 x12C;
    /* 0x130 */ f32 x130;
    /* 0x134 */ s32 x134;
    /* 0x138 */ f32 x138;
    /* 0x13C */ f32 x13C;
    u8 filler_x140[0x164-0x140];
    /* 0x164 */ f32 x164;
    u8 filler_x168[0x194-0x168];
    /* 0x194 */ f32 x194_unkHitLagFrames;
    /* 0x198 */ f32 x198;
    /* 0x19C */ f32 x19C;
    /* 0x1A0 */ f32 x1A0;
    u8 filler_x1A4[0x1FC-0x1A4];
    /* 0x1FC */ f32 x1FC;
    /* 0x200 */ f32 x200;
    /* 0x204 */ f32 x204_knockbackFrameDecay;
    u8 filler_x208[0x21C-0x208];
    /* 0x21C */ f32 x21C;
    u8 filler_x220[0x260-0x220];
    /* 0x260 */ f32 x260_startShieldHealth;
    u8 filler_x264[0x27C-0x264];
    /* 0x27C */ f32 x27C;
    /* 0x280 */ f32 x280_unkShieldHealth;
    /* 0x284 */ f32 x284;
    /* 0x288 */ f32 x288;
    u8 filler_x28C[0x294-0x28C];
    /* 0x294 */ f32 x294;
    u8 filler_x298[0x2DC-0x298];
    /* 0x2DC */ f32 x2DC;
    /* 0x2E0 */ f32 x2E0;
    u8 filler_x2E4[0x308-0x2E4];
    /* 0x308 */ f32 x308;
    u8 filler_x30C[0x3A8-0x30C];
    /* 0x3A8 */ f32 x3A8;
    u8 filler_x3AC[0x3E0-0x3AC];
    /* 0x3E0 */ f32 x3E0;
    /* 0x3E4 */ f32 x3E4;
    /* 0x3E8 */ f32 x3E8_shieldKnockbackFrameDecay;
    /* 0x3EC */ f32 x3EC_shieldGroundFrictionMultiplier;
    u8 filler_x3F0[0x418-0x3F0];
    /* 0x418 */ s32 x418;
    /* 0x41C */ s32 x41C;
    u8 filler_x420[0x440-0x420];
    /* 0x440 */ f32 x440;
    /* 0x444 */ f32 x444;
    /* 0x448 */ f32 x448;
    /* 0x44C */ f32 x44C;
    /* 0x450 */ f32 x450;
    /* 0x454 */ f32 x454;
    /* 0x458 */ f32 x458;
    /* 0x45C */ f32 x45C;
    /* 0x460 */ f32 x460;
    u8 filler_x464[0x480-0x464];
    /* 0x480 */ f32 x480;
    u8 filler_x484[0x498-0x484];
    /* 0x498 */ u32 x498_ledgeCooldownTime;
    u8 filler_x49C[0x4C4-0x49C];
    s32 x4C4;
    s32 x4C8;
    s32 x4CC;
    f32 x4D0;
    f32 x4D4;
    u32 x4D8;
    u8 filler_x4D0[0x5C0-0x4DC];
    /* 0x5F0 */ f32 x5C0;
    u8 filler_x5C4[0x5F0-0x5C4];
    /* 0x5F0 */  u32 x5F0;
    u8 filler_x5F4[0x6D8-0x5F4];
   /* 0x6D8 */ void* x6D8[1]; // TODO expand to actual size
    struct RGBA x6DC_colorsByPlayer[4];
    u8 filler_x6EC[0x6F4 - 0x6EC];
    /* 0x6F4 */ s32 x6F4_unkDamage;
    /* 0x6F8 */ s32 x6F8;
    /* 0x6FC */ s32 x6FC;
    /* 0x700 */ s32 x700;
    /* 0x704 */ f32 x704;
    /* 0x708 */ f32 x708;
    /* 0x70C */ f32 x70C;
    /* 0x710 */ f32 x710;
    /* 0x714 */ f32 x714;
    u8 filler_x718[0x768-0x718];
    /* 0x768 */ f32 x768;
    /* 0x76C */ f32 x76C;
    /* 0x770 */ f32 x770;
    /* 0x774 */ s32 x774;
    u8 x7A0_filler[0x7A0 - 0x778];
    /* 0x7A0 */ s32 x7A0;
    /* 0x7A4 */ s32 x7A4;
    /* 0x7A8 */ s32 x7A8;
    /* 0x7AC */ s32 x7AC;
    /* 0x7B0 */ s32 x7B0;
    /* 0x7B4 */ s32 x7B4_unkDamage;
    /* 0x7B8 */ f32 x7B8;
    /* 0x7BC */ f32 x7BC;
    /* 0x7C0 */ f32 x7C0;
    /* 0x7C4 */ s32 x7C4;
    /* 0x7C8 */ s32 x7C8;
    /* 0x7CC */ s32 x7CC;
    /* 0x7D0 */ s32 x7D0;
    /* 0x7D4 */ s32 x7D4;
    /* 0x7D8 */ s32 x7D8;
    /* 0x7DC */ s32 x7DC;
    /* 0x7E0 */ s32 x7E0;
    /* 0x7E4 */ f32 x7E4_scaleZ;
    u8 x7E8_filler[0x814 - 0x7E8];
    /* 0x814 */ s32 x814;
    // lots of more data following, exact size to be determined
} ftCommonData;

typedef struct _FtCollisionData
{
    u8 data_filler_0[0x28];
    u32 x28;
    u8 data_filler_2C[0x30 - 0x2C];
    s32 x30;
    s32 x34;
} FtCollisionData;

struct UnkFloat6_Camera;

typedef struct _ftData
{
    struct {
        u8 x0_fill[0x8C];
        f32 x8C;
        u8 x90_fill[0xFC - 0x90];
        f32 xFC;
        u8 x100_fill[0x16C - 0x100];
        s32 x16C_idx;
    }* x0;
    /* 0x04 */ void* ext_attr;
    struct {
        u8 x0_fill[0x10];
        u8 unk10, unk11, unk12;
    }* x8;
    struct S_TEMP4* xC;
    u8* x10;
    s32 filler_x14[10];
    struct UnkFloat6_Camera *x3C;
    s32 filler_x40[2];
    /* 0x48 */ void** x48_items;
    FtCollisionData* x4C_collisionData;
    s32 filler_x50[2];
    void* x58;
} ftData;

typedef struct _ThrowFlags
{
  union {
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
    u32 flags;
  };
} ThrowFlags;

typedef struct attr
{
    /* 0x110 */ f32 x110_WalkInitialVelocity;
    /* 0x114 */ f32 x114_WalkAcceleration;
    /* 0x118 */ f32 x118_WalkMaximumVelocity;
    /* 0x11C */ f32 x11C_SlowWalkMax;
    /* 0x120 */ f32 x120_MidWalkPoint;
    /* 0x124 */ f32 x124_FastWalkMin;
    /* 0x128 */ f32 x128_GroundFriction; // used
    /* 0x12C */ f32 x12C_DashInitialVelocity;
    /* 0x130 */ f32 x130_DashrunAccelerationA;
    /* 0x134 */ f32 x134_DashrunAccelerationB;
    /* 0x138 */ f32 x138_DashrunTerminalVelocity;
    /* 0x13C */ f32 x13C_RunAnimationScaling;
    /* 0x140 */ f32 x140_MaxRunbrakeFrames;
    /* 0x144 */ f32 x144_GroundedMaxHorizontalVelocity;
    /* 0x148 */ f32 x148_JumpStartupTime;
    /* 0x14C */ f32 x14C_JumpHInitialVelocity;
    /* 0x150 */ f32 x150_JumpVInitialVelocity;
    /* 0x154 */ f32 x154_GroundToAirJumpMomentumMultiplier;
    /* 0x158 */ f32 x158_JumpHMaxVelocity;
    /* 0x15C */ f32 x15C_HopVInitialVelocity;
    /* 0x160 */ f32 x160_AirJumpVMultiplier;
    /* 0x164 */ f32 x164_AirJumpHMultiplier;
    /* 0x168 */ s32 x168_MaxJumps;
    /* 0x16C */ f32 x16C_Gravity;
    /* 0x170 */ f32 x170_TerminalVelocity;
    /* 0x174 */ f32 x174_AerialDriftStickMult;
    /* 0x178 */ f32 x178_AerialDriftBase;
    /* 0x17C */ f32 x17C_AerialDriftMax;
    /* 0x180 */ f32 x180_AerialFriction;
    /* 0x184 */ f32 x184_FastfallVelocity;
    /* 0x188 */ f32 x188_HorizontalAirMobilityConstant;
    /* 0x18C */ f32 x18C_Jab_2InputWindow;
    /* 0x190 */ s32 x190_Jab_3InputWindow;
    /* 0x194 */ s32 x194_FramesToChangeDirectionOnStandingTurn;
    /* 0x198 */ f32 x198_Weight;
    /* 0x19C */ f32 x19C_ModelScaling;
    /* 0x1A0 */ f32 x1A0_InitialShieldSize;
    /* 0x1A4 */ f32 x1A4_ShieldBreakInitialVelocity;
    /* 0x1A8 */ s32 x1A8_RapidJabWindow;
    /* 0x1AC */ s32 x1AC;
    /* 0x1B0 */ s32 x1B0;
    /* 0x1B4 */ s32 x1B4;
    /* 0x1B8 */ f32 x1B8_LedgeJumpHorizontalVelocity;
    /* 0x1BC */ f32 x1BC_LedgeJumpVerticalVelocity;
    /* 0x1C0 */ f32 x1C0_ItemThrowVelocityMultiplier;
    /* 0x1C4 */ s32 x1C4;
    /* 0x1C8 */ s32 x1C8;
    /* 0x1CC */ s32 x1CC;
    /* 0x1D0 */ s32 x1D0;
    /* 0x1D4 */ s32 x1D4;
    /* 0x1D8 */ s32 x1D8;
    /* 0x1DC */ s32 x1DC;
    /* 0x1E0 */ s32 x1E0;
    /* 0x1E4 */ s32 x1E4;
    /* 0x1E8 */ s32 x1E8;
    /* 0x1EC */ s32 x1EC;
    /* 0x1F0 */ f32 x1F0_KirbyBStarDamage;
    /* 0x1F4 */ f32 x1F4_NormalLandingLag;
    /* 0x1F8 */ f32 x1F8_NAirLandingLag;
    /* 0x1FC */ f32 x1FC_FAirLandingLag;
    /* 0x200 */ f32 x200_BAirLandingLag;
    /* 0x204 */ f32 x204_UAirLandingLag;
    /* 0x208 */ f32 x208_DAirLandingLag;
    /* 0x20C */ f32 x20C_NametagHeight;
    /* 0x210 */ s32 x210;
    /* 0x214 */ f32 x214_WallJumpHorizontalVelocity;
    /* 0x218 */ f32 x218_WallJumpVerticalVelocity;
    /* 0x21C */ s32 x21C;
    /* 0x220 */ f32 x220_TrophyScale;
    /* 0x224 */ Vec3 x224;
    /* 0x230 */ Vec3 x230;
    /* 0x23C */ f32 x23C;
    /* 0x240 */ Vec3 x240;
    /* 0x24C */ f32 x24C;
    /* 0x250 */ s32 x250;
    /* 0x254 */ s32 x254;
    /* 0x258 */ f32 x258; // used
    /* 0x25C */ f32 x25C_BubbleRatio;
    /* 0x260 */ s32 x260;
    /* 0x264 */ s32 x264;
    /* 0x268 */ s32 x268;
    /* 0x26C */ s32 x26C;
    /* 0x270 */ f32 x270_RespawnPlatformScale;
    /* 0x274 */ s32 x274;
    /* 0x278 */ s32 x278;
    /* 0x27C */ s32 x27C_CameraZoomTargetBone;
    /* 0x280 */ Vec3 x280;
    /* 0x28C */ s32 x28C;
    /* 0x290 */ s32 x290_WeightDependentThrowSpeedFlags;
}attr;

typedef struct _FighterBone
{
  /* 0x0 */ HSD_JObj* x0_jobj;
  /* 0x4 */ HSD_JObj* x4_jobj2; // used for interpolation
  /* 0x5 */ UnkFlagStruct flags;
  /* 0x6 */ u8 filler_x6[7];
} FighterBone;


typedef struct _Hitbox {
    s32 x0;
    s32 x4;
    s32 x8;
    f32 xC;
    u8 filler[0x128]; // slightly more detail, f32 needed for 'manual' mods to hitbox damage //
} Hitbox;

typedef struct _CameraBox
{
  u32 data_filler[2];
  s32 x8;
  UnkFlagStruct xC_flag;
  u8 xD_fill[0x10 - 0xD];
  Vec3 x10; // might be Vec2?
  Vec3 x1C;
  f32 x28;
  Vec2 x2C;
  Vec3 x34;
  Vec2 x40;
  Vec3 x48;
} CameraBox;

typedef struct _ftECB
{
    Vec2 top;
    Vec2 bottom;
    Vec2 right;
    Vec2 left;
} ftECB;

typedef struct _ECBFlagStruct {
    union { 
        struct {
        u8 b0 : 1;
        u8 b1234 : 4;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } bits;
    u8 raw;
    };
} ECBFlagStruct;

typedef struct SurfaceData {
    s32 index;
    u32 unk;
    Vec3 normal;
} SurfaceData;

typedef struct _CollData
{
    HSD_GObj* x0_gobj;
    Vec3 x4_vec;
    Vec3 x10_vec;
    Vec3 x1C_vec;
    Vec3 x28_vec;
    ECBFlagStruct x34_flags;
    ECBFlagStruct x35_flags;
    s16 x36;
    s32 x38;
    s32 x3C;
    s32 x40;
    u32 x44;
    u32 x48;
    u32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    s32 x60;
    ftECB x64_ecb;
    ftECB x84_ecb;
    ftECB xA4_ecbCurrCorrect;
    ftECB xC4_ecb;
    ftECB xE4_ecb;
    s32 x104; // TODO: this is the start of a substruct with size 0x2C
    union {
        struct {
            HSD_JObj* x108_joint;
            HSD_JObj* x10C_joint[6];
        };
        struct {
            f32 x108_f32;
            f32 x10C_f32;
            f32 x110_f32;
            f32 x114_f32;
            f32 x118_f32;
            f32 x11C_f32;
            f32 x120_f32;
        };
    };
    f32 x124;
    f32 x128;
    f32 x12C;
    u32 x130_flags;
    s32 x134_envFlags;
    s32 filler138;
    s32 filler13C;
    Vec3 x140;
    SurfaceData x14C_ground;
    SurfaceData x160_rightwall;
    SurfaceData x174_leftwall;
    SurfaceData x188_ceiling;
    /* 0x19C */ s32 x19C;
} CollData;

typedef struct ftHurt
{
    u32 x0_bone_state;                    // 0x0, whether or not this hurtbox can be hit
    Vec3 x4_hurt1_offset;                 // 0x4
    Vec3 x10_hurt2_offset;                // 0x10
    f32 x1C_scale;                        // 0x1c
    HSD_JObj* x20_jobj;                   // 0x20
    unsigned char x24_1_is_updated : 1;   // 0x24, 0x80, if enabled, wont update position
    unsigned char x24_2 : 1;              // 0x24 0x40
    unsigned char x24_3 : 1;              // 0x24 0x20
    unsigned char x24_4 : 1;              // 0x24 0x10
    unsigned char x24_5 : 1;              // 0x24 0x08
    unsigned char x24_6 : 1;              // 0x24 0x04
    unsigned char x24_7 : 1;              // 0x24 0x02
    unsigned char x24_8 : 1;              // 0x24 0x01
    Vec3 x28_hurt1_pos;                   // 0x28
    Vec3 x34_hurt2_pos;                   // 0x34
    u32 x40_bone_index;                   // 0x40
    u32 x44_hurt_kind;                    // 0x44. 0 = low, 1 = mid, 2 = high
    u32 x48_is_grabbable;                 // 0x48
}ftHurt;

typedef struct _SmashAttr {
    s32 x2114_state;                        // 0x2114 0 = none, 1 = pre-charge, 2 = charging, 3 = release
    f32 x2118_frames;                       // 0x2118 number of frames fp has charged for
    f32 x211C_holdFrame;                    // 0x211c frame that charge begins/ends
    f32 x2120_damageMul;                    // 0x2120 damage multiplier
    f32 x2124_frameSpeedMul;                // 0x2124 speed multiplier?
    s32 x2128;                              // 0x2128
    s8 x212C;                               // 0x212C
    s8 x212D;                               // 0x212D
    s8 x212E;                               // 0x212E
    s8 x212F;                               // 0x212F
    s32 x2130_sfxBool;                      // 0x2130 bool for smash sfx?
    s8 x2134_vibrateFrame;                  // 0x2134
    s8 x2135;                               // 0x2135
    s8 x2136;                               // 0x2136
    s8 x2137;                               // 0x2137
    f32 x2138_smashSinceHitbox;             // 0x2138
} SmashAttr;

typedef struct _ftHit
{
    u8 filler_x0[0x134];
    s32 x134;
} ftHit;

typedef struct _itPickup // 0x294
{
    Vec2 x0_ground_light_offset;  // 0x294
    Vec2 x8;                      // 0x29C
    Vec2 x10_ground_heavy_offset; // 0x2A4
    Vec2 x18;                     // 0x2AC
    Vec2 x20_air_light_offset;    // 0x2B4
    Vec2 x28;                     // 0x2BC
} itPickup;

typedef struct _S32Pair {
    s32 x, y;
} S32Pair;

typedef struct {
    HSD_Joint* joint;
    u8 padding[0x10];
    HSD_Archive* x14_archive;
} UnkCostumeStruct;

struct UnkCostumeList {
    UnkCostumeStruct* costume_list;
    u8 numCostumes;
};


struct S_TEMP1 {
    FighterKind fighterKind;
    u8 playerID;
    u8 unk5;
    UnkFlagStruct flags;
};

struct ActionState {
    s32 action_id; 

    s32 x4_flags;

    u8 move_id;
    UnkFlagStruct x9_flags;
    UnkFlagStruct flagsA;
    UnkFlagStruct flagsB;

    void* cb_Anim;
    void* cb_Input;
    void* cb_Physics;
    void* cb_Collision;
    void* cb_Camera;
};

struct S_TEMP4 {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10_animCurrFlags;
    s32 x14;
};

// --------------------------------------------------------------------------------
// UNION DEFS FOR FIGHTER STRUCTS. TODO: Maybe move these to per-fp
// header includes or something.
// --------------------------------------------------------------------------------
struct SpecialAttrs_Mario {
    /* 0x222C */ s32 x222C_vitaminCurr; // Current Megavitamin color combo //
    /* 0x2230 */ s32 x2230_vitaminPrev; // Previous Megavitamin color combo //
    /* 0x2234 */ BOOL x2234_tornadoCharge;
    /* 0x2238 */ BOOL x2238_isCapeBoost;
    /* 0x223C */ HSD_GObj* x223C_capeGObj;
    /* 0x2240 */ u32 x2240;
};

struct SpecialAttrs_Fox {
    /* 0x222C */ HSD_GObj* x222C_blasterGObj;
};

struct SpecialAttrs_Captain {
    /* 0x222C */ BOOL x222C_isSpecialSStartGFX;
    /* 0x2230 */ BOOL x2230_isSpecialSGFX;
};

struct SpecialAttrs_DK {
    /* 0x222C */ s32 x222C;
    /* 0x2230 */ s32 x2230;
};

struct SpecialAttrs_Kirby {
    /* 0x222C */ s32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ UnkFlagStruct x2234;
    /* 0x2235 */ u8 filler_x2235[3];
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
    /* 0x224C */ u8 filler1[0x228C - 0x224C];
    /* 0x228C */ u32 x228C;
    /* 0x2290 */ u32 x2290;
    /* 0x2294 */ u8 filler2[0x22C8 - 0x2294];
    /* 0x22C8 */ s32 x22C8;
    /* 0x22CC */ s32 x22CC;
    /* 0x22D0 */ s32 x22D0;
    /* 0x22D4 */ s32 x22D4;
    /* 0x22D8 */ s32 x22D8;
    /* 0x22DC */ s32 x22DC;
    /* 0x22E0 */ s32 x22E0;
    /* 0x22E4 */ s32 x22E4;
    /* 0x22E8 */ s32 x22E8;
};

struct SpecialAttrs_Koopa {
    /* 0x222C */ u32 x222C;
};

struct SpecialAttrs_Link {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
};

struct SpecialAttrs_Seak {
    /* 0x222C */ s32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
};

struct SpecialAttrs_Ness {
    /* 0x222C */ HSD_GObj* x222C_yoyoGObj;
    /* 0x2230 */ Vec3 x2230_yoyoHitboxPos;
    /* 0x223C */ f32 x223C;
    /* 0x2240 */ HSD_GObj* x2240_flashGObj;
    /* 0x2244 */ HSD_GObj* x2244_pkThunderGObj;
    /* 0x2248 */ HSD_GObj* x2248_baseballBatGObj;
    /* 0x224C */ u32 x224C_thunderGFX; // bool for PK Thunder GFX? //
};

struct SpecialAttrs_Peach {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
};

struct SpecialAttrs_Popo {
    char filler0[0x100];
};

struct SpecialAttrs_Nana {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ UnkFlagStruct x2230;
    /* 0x2231 */ u8 filler_x2231[3];
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
    /* 0x224C */ u32 x224C;
    /* 0x2250 */ f32 x2250;
};

struct SpecialAttrs_Pikachu {
    char filler0[0x100];
};

struct SpecialAttrs_Samus {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ s32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;

    /* 0x2240 */ u8 x2240;
    /* 0x2241 */ u8 x2241;
    /* 0x2242 */ u8 x2242;
    /* 0x2243 */ u8 x2243;

    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
};

struct SpecialAttrs_Yoshi {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
};

struct SpecialAttrs_Purin {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ HSD_JObj* x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ void* x2244;
    /* 0x2248 */ u32 x2248;
};

struct SpecialAttrs_Mewtwo {
    /* 0x222C */ HSD_GObj* x222C_disableGObj;
    /* 0x2230 */ HSD_GObj* x2230_shadowHeldGObj; // GObj of Shadow Ball while in Mewtwo's hands?
    /* 0x2234 */ s32 x2234_shadowBallCharge;     // Number of cycles Shadow Ball has been charged
    /* 0x2238 */ HSD_GObj* x2238_shadowBallGObj;
    /* 0x223C */ BOOL x223C_isConfusionBoost;
};

struct SpecialAttrs_Luigi {
    /* 0x222C */ BOOL x222C_cycloneCharge;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
};

struct SpecialAttrs_Mars {
    /* 0x222C */ u32 x222C;
};

struct SpecialAttrs_Zelda {
    /* 0x222C */ u32 x222C;
};

struct SpecialAttrs_CLink {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
};

struct SpecialAttrs_Pichu {
    char filler0[0x100];
};

struct SpecialAttrs_GameWatch {
    /* 0x222C */ s32 x222C_judgeVar1;
    /* 0x2230 */ s32 x2230_judgeVar2;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ s32 x2238_panicCharge;
    /* 0x223C */ s32 x223C_panicDamage;
    /* 0x2240 */ s32 x2240_chefVar1;
    /* 0x2244 */ s32 x2244_chefVar2;
    /* 0x2248 */ HSD_GObj* x2248_manholeGObj;
    /* 0x224C */ HSD_GObj* x224C_greenhouseGObj;
    /* 0x2250 */ HSD_GObj* x2250_manholeGObj2;
    /* 0x2254 */ HSD_GObj* x2254_fireGObj;
    /* 0x2258 */ HSD_GObj* x2258_parachuteGObj;
    /* 0x225C */ HSD_GObj* x225C_turtleGObj;
    /* 0x2260 */ HSD_GObj* x2260_sparkyGObj;
    /* 0x2264 */ HSD_GObj* x2264_judgementGObj;
    /* 0x2268 */ HSD_GObj* x2268_panicGObj;
    /* 0x226C */ HSD_GObj* x226C_rescueGObj;
};

struct SpecialAttrs_Masterhand {
    /* 0x222C */ HSD_GObj* x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ f32 x2238;
    /* 0x223C */ f32 x223C;
    /* 0x2240 */ Vec3 x2240_pos;
    /* 0x224C */ u32 x224C;
    /* 0x2250 */ s32 x2250;
    /* 0x2254 */ s32 x2254;
    /* 0x2258 */ s32 x2258;
};

struct SpecialAttrs_Crazyhand {
    /* 0x222C */ HSD_GObj* x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ f32 x2238;
    /* 0x223C */ f32 x223C;
    /* 0x2240 */ Vec3 x2240_pos;
    /* 0x224C */ u32 x224C;
    /* 0x2250 */ s32 x2250;
    /* 0x2254 */ s32 x2254;
    /* 0x2258 */ s32 x2258;
};

struct SpecialAttrs_Boy {
    char filler0[0x100];
};

struct SpecialAttrs_Girl {
    char filler0[0x100];
};

struct SpecialAttrs_GKoopa {
    /* 0x222C */ f32 x222C;
    /* 0x2230 */ f32 x2230;
};

struct SpecialAttrs_Sandbag {
    char filler0[0x100];
};

typedef struct _Fighter {
    /* 0x0 */ HSD_GObj *x0_fighter;
    /* 0x4 */ FighterKind x4_fighterKind;
    /* 0x8 */ s32 x8_spawnNum;
    /* 0xC */ u8 xC_playerID;
    /* 0x10 */ s32 x10_action_state_index;
    /* 0x14 */ s32 x14_action_id;
    /* 0x18 */ s32 x18;
    /* 0x1C */ struct ActionState* x1C_actionStateList;
    /* 0x20 */ struct ActionState* x20_actionStateList;
    /* 0x24 */ struct S_TEMP4* x24;
    /* 0x28 */ u8* x28;
    /* 0x2C */ f32 x2C_facing_direction;
    /* 0x30 */ f32 x30_facingDirectionRepeated;
    /* 0x34 */ Vec3 x34_scale;
    /* 0x40 */ f32 x40;
    /* 0x44 */ Mtx x44_mtx;
    Vec3 x74_anim_vel;                                         // 0x74
    Vec3 x80_self_vel;                                         // 0x80
    Vec3 x8c_kb_vel;                                           // 0x8C
    Vec3 x98_atk_shield_kb;                                // 0x98
    Vec3 xA4_unk_vel;                                      // 0xA4
    Vec3 xB0_pos;                                          // 0xb0
    Vec3 xBC_prevPos;                                     // 0xBC
    Vec3 xC8_pos_delta;                                        // 0xC8
    Vec3 xD4_unk_vel;                                        // 0xD4
    GroundOrAir xE0_ground_or_air;                                         // 0xE0
    f32 xE4_ground_accel_1; // 0xE4
    f32 xE8_ground_accel_2;   // 0xE8
    f32 xEC_ground_vel;                                    // 0xEC
    f32 xF0_ground_kb_vel;
    f32 xF4_ground_attacker_shield_kb_vel;
    Vec2 xF8_playerNudgeVel;
    /* 0x100 */ f32 x100;
    /* 0x104 */ u8 x104;
    /* 0x105 */ s8 x105;
    /* 0x106 */ s8 x106;
    /* 0x107 */ s8 x107;
    /* 0x108 */ HSD_Joint* x108_costume_joint;
    /* 0x10C */ ftData* x10C_ftData;
    // TODO: Ask Psi how many of those are confirmed, only a fraction of them is used right now
    attr x110_attr;
    /* 0x294 */ itPickup x294_itPickup;
    /* 0x2C4 */ Vec2 x2C4;
    /* 0x2CC */ void* x2CC;
    /* 0x2D0 */ void* x2D0;
    /* 0x2D4 */ void* x2D4_specialAttributes;
    /* 0x2D8 */ void* x2D8_specialAttributes2;
    /* 0x2DC */ f32 x2DC;
    /* 0x2E0 */ f32 x2E0;
    /* 0x2E4 */ f32 x2E4;
    /* 0x2E8 */ f32 x2E8;
    /* 0x2EC */ f32 x2EC;
    /* 0x2F0 */ u32 x2F0;
    /* 0x2F4 */ unk_t x2F4;
    u8 filler_x2F0[0x3E0 - 0x2F8];
    /* 0x3E0 */ u32 x3E0;
    /* 0x3E4 */ f32 x3E4;
    /* 0x3E8 */ f32 x3E8;
    /* 0x3EC */ s32 x3EC;
    /* 0x3F0 */ s32 x3F0;
    u8 filler_x3F4[0x588 - 0x3F4];
    /* 0x588 */ s32 x588;
    /* 0x58C */ s32 x58C;
    /* 0x590 */ s32 x590;
    /* 0x594 */ union {
                    struct {
                        UnkFlagStruct x594_animCurrFlags1;
                        struct {
                            u8 x0: 7;
                            u16 x7: 3;
                        } x596_bits;
                    };
                    s32 x594_s32;
                };
    /* 0x598 */ s32 x598;
    /* 0x59C */ void* x59C;
    /* 0x5A0 */ void* x5A0;
    u8 filler_x5A4[0x5B8 - 0x5A4];
    /* 0x5B8 */ s32 x5B8;
    /* 0x5BC */ s32 x5BC;
    u8 filler_x598[0x5C8 - 0x5C0];
    /* 0x5A0 */ void* x5C8;
    u8 filler_x5CC[0x5E8 - 0x5CC];
    /* 0x5E8 */ FighterBone* x5E8_fighterBones;
    u8 filler_x5EC[0x5F0 - 0x5EC];
    /* 0x5F0 */ HSD_DObj** x5F0;
    /* 0x5F4 */ s8 x5F4;
    /* 0x5F5 */ s8 x5F5;
    /* 0x5F6 */ s8 x5F6;
    /* 0x5F7 */ s8 x5F7;
    /* 0x5F8 */ s8 x5F8;
    u8 filler_x5FC[0x60C - 0x5F9];
    /* 0x60C */ void* x60C;
    union {
        /* 0x610 */ struct RGBA x610_color_rgba[2];
        struct {
            /* 0x610 */ s32 x610;
            /* 0x614 */ s32 x614;
        };
    };
    /* 0x618 */ u8 x618_player_id;
    /* 0x619 */ u8 x619_costume_id;
    /* 0x61A */ u8 x61A_controller_index;
    /* 0x61B */ u8 x61B_team;
    /* 0x61C */ u8 x61C;
    /* 0x61D */ u8 x61D;
    u8 filler_x61E[0x620 - 0x61E];

    struct {
        /* 0x620 */ f32 x620_lstick_x;
        /* 0x624 */ f32 x624_lstick_y;
        /* 0x628 */ f32 x628_lstick_x2;
        /* 0x62C */ f32 x62C_lstick_y2;

        /* 0x630 */ f32 x630;
        /* 0x634 */ f32 x634;

        /* 0x638 */ f32 x638_lsubStick_x;
        /* 0x63C */ f32 x63C_lsubStick_y;
        /* 0x640 */ f32 x640_lsubStick_x2;
        /* 0x644 */ f32 x644_lsubStick_y2;
                    
        /* 0x648 */ f32 x648;
        /* 0x64C */ f32 x64C;
                    
        /* 0x650 */ f32 x650;
        /* 0x654 */ f32 x654;

        /* 0x658 */ f32 x658;

        /* 0x65C */ u32 x65C_heldInputs;
        /* 0x660 */ s32 x660;
        /* 0x664 */ s32 x664;
        /* 0x668 */ s32 x668;
        /* 0x66C */ s32 x66C;
    } input; // 0x620 to 0x670

    /* 0x670 */ u8 x670_timer_lstick_tilt_x;
    /* 0x671 */ u8 x671_timer_lstick_tilt_y;
    /* 0x672 */ u8 x672_input_timer_counter;

    /* 0x673 */ u8 x673;
    /* 0x674 */ u8 x674;
    /* 0x674 */ u8 x675;

    /* 0x676 */ u8 x676_x;
    /* 0x677 */ u8 x677_y;
    /* 0x678 */ u8 x678;

    /* 0x679 */ u8 x679_x;
    /* 0x67A */ u8 x67A_y;
    /* 0x67B */ u8 x67B;

    /* 0x67C */ u8 x67C;
    /* 0x67D */ u8 x67D;
    /* 0x67E */ u8 x67E;
    /* 0x67F */ u8 x67F;
    /* 0x680 */ u8 x680;
    /* 0x681 */ u8 x681;
    /* 0x682 */ u8 x682;
    /* 0x683 */ u8 x683;
    /* 0x684 */ u8 x684;
    /* 0x685 */ u8 x685;
    /* 0x686 */ u8 x686;
    /* 0x687 */ u8 x687;
    /* 0x688 */ u8 x688;
    /* 0x689 */ u8 x689;
    /* 0x68A */ u8 x68A;
    /* 0x68B */ u8 x68B;

    /* 0x68C */ Vec x68C_transNPos;
    /* 0x698 */  Vec x698;
    /* 0x6A4 */  Vec3 x6A4_transNOffset;
    /* 0x6B0 */  Vec3 x6B0;
    /* 0x6BC */  f32 x6BC_inputStickangle;
    /* 0x6C0 */  Vec x6C0;
    /* 0x6CC */  Vec x6CC;
    /* 0x6D8 */  Vec3 x6D8;
    /* 0x6E4 */  Vec3 x6E4;
    /* 0x6F0 */ CollData x6F0_collData;
    /* 0x890 */ CameraBox* x890_cameraBox;
    /* 0x894 */ f32 x894_currentAnimFrame;
    /* 0x898 */ f32 x898_unk;
    /* 0x89C */ f32 x89C_frameSpeedMul;
    /* 0x8A0 */ f32 x8A0_unk;
    /* 0x8A4 */ f32 x8A4_animBlendFrames;
    /* 0x8A8 */ f32 x8A8_unk;
    /* 0x8AC */ HSD_JObj* x8AC_animSkeleton;
    u8 filler_x8AC[0x914 - 0x8B0];
    /* 0x914 */ Hitbox x914[4];
    u8 filler_xDF4[0x1064 - 0xDF4];
    /* 0x1064 */ ftHit x1064_thrownHitbox;
    /* 0x119C */ u8 x119C_teamUnk;
    /* 0x119D */ u8 x119D;
    /* 0x119E */ u8 x119E_hurtboxNum;
    /* 0x119F */ u8 x119F;
    /* 0x11A0 */ ftHurt x11A0_fighterHurtbox[15];
    /* 0x1614 */ unk_t x1614;
    /* 0x1618 */ u8 filler_x1618[0x166C - 0x1618];
    /* 0x166C */ u32 x166C;
    /* 0x1670 */ unk_t x1670;
    /* 0x1674 */ u8 filler_x1674[0x1828 - 0x1674];
    /* 0x1828 */ s32 x1828;
    struct dmg                                                 // 0x182c
    {                                                          //
        f32 x182c_behavior;                                    // 0x182c
        f32 x1830_percent;                                     // 0x1830
        f32 x1834;                                             // 0x1834
        f32 x1838_percentTemp;                                 // 0x1838
        s32 x183C_applied;                                     // 0x183c
        s32 x1840;                                             // 0x1840
        f32 x1844_direction;                                   // 0x1844
        s32 x1848_kb_angle;                                    // 0x1848
        s32 x184c_damaged_hurtbox;                             // 0x184c
        f32 x1850_forceApplied;                                // 0x1850
        Vec3 x1854_collpos;                                    // 0x1854
        s32 x1860_dealt;                                       // 0x1860
        s32 x1864;                                             // 0x1864
        HSD_GObj *x1868_source;                                // 0x1868
        s32 x186c;                                             // 0x186c
        s32 x1870;                                             // 0x1870
        s32 x1874;                                             // 0x1874
        s32 x1878;                                             // 0x1878
        s32 x187c;                                             // 0x187c
        s32 x1880;                                             // 0x1880
        s32 x1884;                                             // 0x1884
        s32 x1888;                                             // 0x1888
        s32 x188c;                                             // 0x188c
        s32 x1890;                                             // 0x1890
        s32 x1894;                                             // 0x1894
        s32 x1898;                                             // 0x1898
        f32 x189C_unk_num_frames;                                             // 0x189c
        f32 x18a0;                                             // 0x18a0
        f32 x18A4_knockbackMagnitude;                          // 0x18a4  kb magnitude
        f32 x18A8;                                             // 0x18a8
        s32 x18ac_time_since_hit;                              // 0x18ac   in frames
        f32 x18B0;                                             // 0x18b0
        f32 x18B4_armor;                                       // 0x18b4
        f32 x18B8;                                             // 0x18b8
        f32 x18BC;                                             // 0x18bc
        s32 x18C0;                                             // 0x18c0
        s32 x18c4_source_ply;                                  // 0x18c4   damage source ply number
        s32 x18C8;                                             // 0x18c8
        s32 x18CC;                                             // 0x18cc
        s32 x18D0;                                             // 0x18d0
        s32 x18d4;                                             // 0x18d4
        s32 x18d8;                                             // 0x18d8
        s32 x18dc;                                             // 0x18dc
        s32 x18e0;                                             // 0x18e0
        s32 x18e4;                                             // 0x18e4
        s32 x18e8;                                             // 0x18e8
        u16 x18ec_instancehitby;                               // 0x18ec. Last Move Instance This Player Was Hit by
        s32 x18F0;                                             // 0x18f0
        s32 x18F4;                                             // 0x18f4
        u8 x18F8;                                              // 0x18f8
        u8 x18f9;                                              // 0x18f9
        u16 x18fa_model_shift_frames;                          // 0x18fa
        u8 x18FC;                                              // 0x18fc
        u8 x18FD;                                              // 0x18fd
        s32 x1900;                                             // 0x1900
        s32 x1904;                                             // 0x1904
        s32 x1908;                                             // 0x1908
        s32 x190C;                                             // 0x190c
        s32 x1910;                                             // 0x1910
        s32 x1914;                                             // 0x1914
        s32 x1918;                                             // 0x1918
        f32 x191C;                                             // 0x191c
        s32 x1920;                                             // 0x1920
        s32 x1924;                                             // 0x1924
        f32 x1928;                                             // 0x1928
        f32 x192c;                                             // 0x192c
        s32 x1930;                                             // 0x1930
        s32 x1934;                                             // 0x1934
        s32 x1938;                                             // 0x1938
        s32 x193c;                                             // 0x193c
        s32 x1940;                                             // 0x1940
        s32 x1944;                                             // 0x1944
        s32 x1948;                                             // 0x1948
        s32 x194C;                                             // 0x194c
        s32 x1950;                                             // 0x1950
        f32 x1954;                                             // 0x1954
        f32 x1958;                                             // 0x1958
        f32 x195c_hitlag_frames;                               // 0x195c
    } dmg;    
    /* 0x1960 */ f32 x1960_vibrateMult;
    /* 0x1964 */ f32 x1964;
    /* 0x1968 */ u8 x1968_jumpsUsed;
    /* 0x1969 */ u8 x1969_walljumpUsed;
    /* 0x196C */ f32 x196C_hitlag_mult;
    /* 0x1970 */ s32 x1970;
    /* 0x1974 */ HSD_GObj* x1974_heldItem;
    /* 0x1978 */ HSD_GObj* x1978;
    /* 0x197C */ HSD_GObj* x197C;
    /* 0x1980 */ HSD_GObj* x1980;
    /* 0x1984 */ HSD_GObj* x1984_heldItemSpec;
    /* 0x1988 */ s32 x1988;
    /* 0x198C */ s32 x198C;
    /* 0x1990 */ s32 x1990;
    /* 0x1994 */ s32 x1994;
    /* 0x1998 */ f32 x1998_shieldHealth;
    /* 0x199C */ f32 x199C_shieldLightshieldAmt;
    /* 0x19A0 */ s32 x19A0_shieldDamageTaken;
    /* 0x19A4 */ s32 x19A4;
    /* 0x19A8 */ void* x19A8;
    /* 0x19AC */ f32 x19AC;
    s32 filler_x19B0;
    /* 0x19B4 */ f32 x19B4_shieldUnk;
    /* 0x19B8 */ f32 x19B8_shieldUnk;
    /* 0x19BC */ s32 x19BC_shieldDamageTaken3;
    struct {
        HSD_JObj* x19C0_boneAttach;
        u8 x19C4_updatePos : 1;
        Vec3 x19C8_pos;
        Vec3 x19D4_offset;
        f32 x19E0_size;
    } ShieldHit;
    struct {
        HSD_JObj* x19E4_boneAttach;
        u8 x19E8_updatePos : 1; // Follows attach bone position if toggled OFF //
        Vec3 x19EC_pos;
        Vec3 x19F8_offset;
        f32 x1A04_size;
    } ReflectHit;
    struct {
        HSD_JObj* x1A08_boneAttach;
        u8 x1A0C_updatePos : 1; // Follows attach bone position if toggled OFF //
        Vec3 x1A10_pos;
        Vec3 x1A1C_offset;
        f32 x1A28_size;
    } AbsorbHit;
    struct {
        f32 x1A2C_reflectHitDirection;
        s32 x1A30_maxDamage;
        f32 x1A34_damageMul;
        f32 x1A38_speedMul;
        s32 x1A3C_damageOver; // % damage over the maximum reflectable damage threshold //
    } ReflectAttr;
    struct {
        f32 x1A40_absorbHitDirection;
        s32 x1A44_damageTaken; // unconfirmred? //
        s32 x1A48_hitsTaken; // unconfirmed? //
    } AbsorbAttr;
    /* 0x1A4C */ f32 x1A4C;
    /* 0x1A50 */ s8 x1A50;
    /* 0x1A51 */ s8 x1A51;
    /* 0x1A52 */ u8 x1A52;
    /* 0x1A53 */ u8 x1A53;
    /* 0x1A54 */ s32 x1A54;
    /* 0x1A58 */ HSD_GObj* x1A58_interactedFighter;
    /* 0x1A5C */ HSD_GObj* x1A5C;
    /* 0x1A60 */ u32 x1A60;
    /* 0x1A64 */ s32 x1A64;
    /* 0x1A68 */ s16 x1A68;
    /* 0x1A6A */ s16 x1A6A;
    /* 0x1A6C */ f32 x1A6C;
    /* 0x1A70 */ Vec x1A70;
    /* 0x1A7C */ Vec x1A7C;
    u8 filler_x1A7C[0x1A94-0x1A88];
    /* 0x1A94 */ u32 x1A94;
    /* 0x1A98 */ u32 x1A98;
    /* 0x1A9C */ s32 x1A9C;
    u8 filler_x1A9C[0x2004-0x1AA0];
    /* 0x2008 */ s32 x2004;
    /* 0x2008 */ s32 x2008;
    /* 0x200C */ s32 x200C;
    /* 0x2010 */ s32 x2010;
    /* 0x2014 */ s32 x2014;
    /* 0x2018 */ s32 x2018;
    /* 0x201C */ s32 x201C;
    /* 0x2020 */ s8 x2020;
    /* 0x2021 */ s8 x2021;
    /* 0x2022 */ s8 x2022;
    /* 0x2024 */ s32 x2024;
    /* 0x2028 */ s32 x2028;
    /* 0x202C */ s32 x202C;
    /* 0x2030 */ s32 x2030;
    /* 0x2034 */ s32 x2034;
    /* 0x2038 */ s32 x2038;
    /* 0x203C */ s32 x203C;
    /* 0x2040 */ void* x2040;
    u8 filler_x203C[0x2064 - 0x2044];
    /* 0x2064 */ s32 x2064_ledgeCooldown;
    /* 0x2068 */s32 x2068_attackID;
    u8 filler_x206C[0x2070 - 0x206C];
    /* 0x2070 */ union {
                    struct {
                        s8 x2070;

                        u8 x2071_b0_3: 4;
                        u8 x2071_b4: 1;
                        u8 x2071_b5: 1;
                        u8 x2071_b6: 1;
                        u8 x2071_b7: 1;
                        
                        u8 x2072_b0_3: 4;
                        u8 x2072_b4: 1;
                        u8 x2072_b5: 1;
                        u8 x2072_b6: 1;
                        u8 x2072_b7: 1;

                        u8 x2073;
                    };
                    s32 x2070_int;
                };
    u8 filler_x2074[0x208C - 0x2074];
    /* 0x208C */ s32 x208C;
    /* 0x2090 */ u16 x2090;
    /* 0x2092 */ u16 x2092;
    /* 0x2094 */ HSD_GObj* x2094; // GObj pointer of combo victim? //
    /* 0x2098 */ u16 x2098;
    /* 0x209A */ u16 x209A;
    /* 0x209C */ s16 x209C;
    /* 0x20A0 */ struct _HSD_JObj* x20A0_accessory;
    /* 0x20A4 */ s32 x20A4;
    /* 0x20A8 */ s32 x20A8;
    /* 0x20AC */ HSD_GObj* x20AC;
    u8 filler_x20B0[0x2100 - 0x20B0];
    /* 0x2100 */ s8 x2100;
    /* 0x2101 */ u8 x2101_bits_0to6 : 7;
    /* 0x2101 */ u8 x2101_bits_8 : 1;
    /* 0x2102 */ s8 x2102;
    /* 0x2103 */ s8 x2103;
    /* 0x2104 */ s32 x2104;
    /* 0x2108 */ s32 x2108;
    /* 0x210C */ u8 x210C_walljumpInputTimer;
    u8 filler_x210C[3];
    /* 0x2110 */ f32 x2110_walljumpWallSide;
    /* 0x2114 */ SmashAttr x2114_SmashAttr;
    /* 0x213C */ s32 x213C;
    /* 0x2140 */ f32 x2140;
    /* 0x2144 */ s32 x2144;
    /* 0x2148 */ s32 x2148;
    /* 0x214C */ s32 x214C;
    /* 0x2150 */ s32 x2150;
    /* 0x2154 */ s32 x2154;
    /* 0x2158 */ s32 x2158;
    /* 0x215C */ s32 x215C;
    /* 0x2160 */ s32 x2160;
    /* 0x2164 */ s32 x2164;
    /* 0x2168 */ s32 x2168;
    s32 filler_x216C;
    /* 0x2170 */ f32 x2170;
    u8 filler_x2174[0x2180 - 0x2174];
    /* 0x2180 */ s32 x2180;
    /* 0x2184 */ HSD_JObj* x2184;
    /* 0x2188 */ S32Pair x2188;
    // callback struct. Not all of them used by fighter.c, but I'm leaving them in for now.
    struct cb {
        void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj *fp); // used
        void (*x2194_callback)(HSD_GObj *fp); // used
        void (*x2198_callback_OnGrabFighter_Victim)(HSD_GObj*, HSD_GObj*); // used
        void (*x219C_callback_IASA)(HSD_GObj *fp); // used
        void (*x21A0_callback_Anim)(HSD_GObj *fp);
        void (*x21A4_callback_Phys)(HSD_GObj *fp); // xused
        void (*x21A8_callback_Coll)(HSD_GObj *fp);
        void (*x21AC_callback_Cam)(HSD_GObj *fp);
        void (*x21B0_callback_Accessory1)(HSD_GObj *fp);
        void (*x21B4_callback_Accessory2)(HSD_GObj *fp); // used
        void (*x21B8_callback_Accessory3)(HSD_GObj *fp); // used
        void (*x21BC_callback_Accessory4)(HSD_GObj *fp);
        void (*x21C0_callback_OnGiveDamage)(HSD_GObj *fp);
        void (*x21C4_callback_OnShieldHit)(HSD_GObj *fp);
        void (*x21C8_callback_OnReflectHit)(HSD_GObj *fp);
        void (*x21CC_callback)(HSD_GObj *fp);
        void (*x21D0_callback_EveryHitlag)(HSD_GObj *fp); // xused
        void (*x21D4_callback_EnterHitlag)(HSD_GObj *fp);
        void (*x21D8_callback_ExitHitlag)(HSD_GObj *fp);
        void (*x21DC_callback_OnTakeDamage)(HSD_GObj *fp);
        void (*x21E0_callback_OnDeath)(HSD_GObj *fp); // used
        void (*x21E4_callback_OnDeath2)(HSD_GObj *fp); // used. internally Dead_Proc as evidenced by 800f5430
        void (*x21E8_callback_OnDeath3)(HSD_GObj *fp); // used
        void (*x21EC_callback)(HSD_GObj *fp);
        void (*x21F0_callback)(HSD_GObj *fp);
        void (*x21F4_callback)(HSD_GObj *fp);
        void (*x21F8_callback)(HSD_GObj *fp);
    } cb;
    /* 0x21FC */ UnkFlagStruct x21FC_flag;
    u8 filler_x21FC[0x2200 - 0x21FD];
    /* 0x2200 */ u32 x2200_ftcmd_var0;
    /* 0x2204 */ u32 x2204_ftcmd_var1;
    /* 0x2208 */ u32 x2208_ftcmd_var2;
    /* 0x220C */ u32 x220C_ftcmd_var3;
    /* 0x2210 */ ThrowFlags x2210_ThrowFlags;
    /* 0x2214 */ f32 x2214;
    /* 0x2218 */ UnkFlagStruct x2218_flag;
    /* 0x2219 */ UnkFlagStruct x2219_flag;
    /* 0x221A */ UnkFlagStruct x221A_flag;
    /* 0x221B */ UnkFlagStruct x221B_flag;
    /* 0x221C */
    union
    {
        struct
        {
            UnkFlagStruct x221C_flag;
            UnkFlagStruct x221D_flag;
        };
        struct
        {
            u16 x221C_u16_x : 7;
            u16 x221C_u16_y : 3;
            u16 x221C_u16_z : 6;
        };
    };
    /* 0x221E */ UnkFlagStruct x221E_flag;
    /* 0x221F */ UnkFlagStruct x221F_flag;
                struct {
                    union {
                        struct {
                            u8 b0 : 3;
                            u8 b3 : 1;
                            u8 b4 : 1;
                            u8 b5 : 1;
                            u8 b6 : 1;
                            u8 b7 : 1;
                        } bits;
                        u8 flags;
                    };
                } x2220_flag;
    /* 0x2221 */ UnkFlagStruct x2221_flag;
    /* 0x2222 */ UnkFlagStruct x2222_flag;
    /* 0x2224 */ UnkFlagStruct x2223_flag;
    /* 0x2224 */ UnkFlagStruct x2224_flag;
    /* 0x2224 */ UnkFlagStruct x2225_flag;
    /* 0x2226 */ UnkFlagStruct x2226_flag;
    /* 0x2227 */ UnkFlagStruct x2227_flag;
    /* 0x2228 */ struct {  ///UnkFlagStruct does not quite work
                    struct {
                        u8 b0 : 1;
                        u8 b1 : 1;
                        u8 b2 : 1;
                        u8 b3 : 2;
                        u8 b5 : 1;
                        u8 b6 : 1;
                        u8 b7 : 1;
                    } bits;
                } x2228_flag;
                
    /* 0x2229 */ u8 x2229_b0 : 1;
                 u8 x2229_b1 : 1;
                 u8 x2229_b2 : 1;
                 u8 x2229_b3 : 1;
                 u8 x2229_b4 : 1;
                 u8 x2229_b5_no_normal_motion : 1;
                 u8 x2229_b6 : 1;
                 u8 x2229_b7 : 1;

                 
    /* 0x222A */ UnkFlagStruct x222A_flag;
    u8 filler_x222B;
    // Some of these are clones of each other (they just use another struct)
    // and some of them dont have specials so dont exist in the union. TODO: Clean-up
    union {
        struct SpecialAttrs_Mario mario;
        struct SpecialAttrs_Fox fox;
        struct SpecialAttrs_Captain captain;
        struct SpecialAttrs_DK dk;
        struct SpecialAttrs_Kirby kirby;
        struct SpecialAttrs_Koopa koopa;
        struct SpecialAttrs_Link link;
        struct SpecialAttrs_Seak seak;
        struct SpecialAttrs_Ness ness;
        struct SpecialAttrs_Peach peach;
        struct SpecialAttrs_Popo popo;
        struct SpecialAttrs_Nana nana;
        struct SpecialAttrs_Pikachu pikachu;
        struct SpecialAttrs_Samus samus;
        struct SpecialAttrs_Yoshi yoshi;
        struct SpecialAttrs_Purin purin;
        struct SpecialAttrs_Mewtwo mewtwo;
        struct SpecialAttrs_Luigi luigi;
        struct SpecialAttrs_Mars mars;
        struct SpecialAttrs_Zelda zelda;
        struct SpecialAttrs_CLink clink;

        // Mario SpecialAttrs struct is used for DrMario
        // Fox SpecialAttrs struct is used for Falco
        struct SpecialAttrs_Pichu pichu;
        struct SpecialAttrs_GameWatch gaw;
        // Cpt Falcon SpecialAttrs struct is used for Ganondorf
        // Mars (Marth) struct is used for Emblem (Roy)
        struct SpecialAttrs_Masterhand masterhand;
        struct SpecialAttrs_Crazyhand crazyhand;
        struct SpecialAttrs_Boy boy;
        struct SpecialAttrs_Girl girl;
        struct SpecialAttrs_GKoopa gkoopa;
        struct SpecialAttrs_Sandbag sandbag;

    } sa;
    /* 0x232C */ s32 x232C;
    /* 0x2330 */ Vec2 x2330;
    /* 0x2338 */ Vec2 x2338;

    /* The following series of individual unions with array size 0 is a temporary hack to bypass compiler errors and size shifts for this mess of a struct.
    These StateVar structs should be one big union once the rest is cleaned up. */

    union {
        union {
            ftCommonStateVars commonVars[0]; // 0x2340
        };
        union {
            ftMarioStateVars marioVars[0]; // 0x2340
        };
        union {
            ftCaptainStateVars captainVars[0]; // 0x2340
        };
        union {
            ftFoxStateVars foxVars[0]; // 0x2340
        };
        union {
            ftNessStateVars nessVars[0]; // 0x2340
        };
        union {
            ftLuigiStateVars luigiVars[0]; // 0x2340
        };
        union {
            ftMewtwoStateVars mewtwoVars[0]; // 0x2340
        };
        union {
            ftGameWatchStateVars gameWatchVars[0]; // 0x2340
        };
    /* 0x2340 */ s32 x2340_stateVar1;
    /* 0x2340 */ u32 x2340_stateVar1_u32;
    /* 0x2340 */ f32 x2340_f32;
    };
    union {
        u32 x2344_stateVar2;
        s32 x2344_stateVar2_s32;
        void (*x2344_callback)(HSD_GObj*);
        f32 x2344_f32;
        struct
        {
            union
            {
                Vec3 x2344_foxSpecialS[0];
            };
        };
    };
    union {
        /* 0x2348 */ u32 x2348_stateVar3;
        /* 0x2348 */ s32 x2348_stateVar3_s32;
        /* 0x2348 */ f32 x2348_stateVar3_f32;
    };
    union {
        struct {
            union {
                /* 0x234C */ u32 x234C_stateVar4;
                /* 0x234C */ s32 x234C_stateVar4_s32;
                /* 0x234C */ f32 x234C_stateVar4_f32;
            };
            union {
                /* 0x2350 */ u32 x2350_stateVar5;
                /* 0x2350 */ s32 x2350_stateVar5_s32;
                /* 0x2350 */ f32 x2350_stateVar5_f32;
            };
            union {
                /* 0x2354 */ u32 x2354_stateVar6;
                /* 0x2354 */ s32 x2354_stateVar6_s32;
                /* 0x2354 */ f32 x2354_stateVar6_f32;
            };
        };
        /* 0x234C */ Vec3 x234C_pos;
    };
    union {
        /* 0x2358 */ f32 x2358_stateVar7;
        /* 0x2358 */ s32 x2358_stateVar7_s32;

    };
    union {
        /* 0x235C */ f32 x235C;
        /* 0x235C */ u32 x235C_u32;
        /* 0x235C */ s32 x235C_s32;
        /* 0x235C */ f32 x235C_f32;
    };
    union {
        /* 0x2360 */ u32 x2360_u32;
        /* 0x2360 */ s32 x2360;
        /* 0x2360 */ f32 x2360_f32;
    };
    union {
        /* 0x2364 */ u32 x2364_u32;
        /* 0x2364 */ f32 x2364;
        /* 0x2364 */ f32 x2364_f32;
    };
    union {
        /* 0x2368 */ u32 x2368;
        /* 0x2368 */ f32 x2368_f32;
    };
    union {
        /* 0x236C */ u32 x236C;
        /* 0x236C */ f32 x236C_f32;
    };
    union {
        /* 0x2370 */ u32 x2370;
        /* 0x2370 */ f32 x2370_f32;
    };
    union {
    struct {
    union {
    /* 0x2374 */ u32 x2374;
    /* 0x2374 */ f32 x2374_f32;
    /* 0x2374 */ f32 x2374_foxArray[0];
    };
    union {
    /* 0x2378 */ u32 x2378;
    /* 0x2378 */ f32 x2378_f32;
    };
    union {
    /* 0x237C */ u32 x237C;
    /* 0x237C */ f32 x237C_f32;
    };
    };
    /* 0x2374 */ Vec3 x2374_Vec3;
    };
    union {
        /* 0x2380 */ u32 x2380;
        /* 0x2380 */ f32 x2380_f32;
    };
    union {
        /* 0x2384 */ u32 x2384_u32;
        /* 0x2384 */ s32 x2384_s32;
        /* 0x2384 */ f32 x2384_f32;
        /* 0x2384 */ HSD_GObj* x2384_GObj;
    };
    union {
        /* 0x2388 */ u32 x2388_u32;
        /* 0x2388 */ s32 x2388_s32;
        /* 0x2388 */ f32 x2388_f32;
    };
    union {
        /* 0x238C */ u32 x238C_u32;
        /* 0x238C */ f32 x238C;
        /* 0x238C */ f32 x238C_f32;
    };
    /* 0x2390 */ f32 x2390;
    /* 0x2394 */ s32 x2394;
    /* 0x2394 */ Vec3 x2398;
    /* 0x2394 */ Vec3 x23A4;
    /* 0x23B0 */ s32 x23B0;
    /* 0x23B4 */ s32 x23B4;
    /* 0x23B8 */ s32 x23B8;
} Fighter;

inline Fighter* getFighter(HSD_GObj* fighter_gobj) 
{
    return fighter_gobj->user_data;
}

inline Fighter* getFighterPlus(HSD_GObj* fighter_gobj) // Uses more stack space //
{
    Fighter* fp = fighter_gobj->user_data;
    return fp;
}

inline void* getFtSpecialAttrs(Fighter* fp)
{
    void* fighter_attr = fp->x2D4_specialAttributes;
    return fighter_attr;
}

inline void* getFtSpecialAttrsD(Fighter* fp) // Direct
{
    return fp->x2D4_specialAttributes;
}

inline s32 ftGetKind(Fighter* fp)
{
    return fp->x4_fighterKind;
}

inline s32 ftGetAction(Fighter* fp)
{
    return fp->x10_action_state_index;
}

inline void* getFtSpecialAttrs2CC(Fighter* fp)
{
    void* fighter_attr = fp->x2CC;
    return fighter_attr;
}

inline attr* getFtAttrs(Fighter* fp)
{
    return &fp->x110_attr;
}

inline CollData* getFtColl(Fighter* fp)
{
    return &fp->x6F0_collData;
}

inline BOOL ftGetGroundAir(Fighter* fp)
{
    return fp->xE0_ground_or_air;
}

inline f32 stickGetDir(f32 x1, f32 x2)
{
    if (x1 < x2)
    {
        return -x1;
    }
    else return x1;
}

// functions in fighter.c
void Fighter_800679B0();
void Fighter_FirstInitialize_80067A84();
void Fighter_LoadCommonData();
void Fighter_UpdateModelScale(HSD_GObj* fighter_gobj);
void Fighter_UnkInitReset_80067C98(Fighter*);
void Fighter_UnkProcessDeath_80068354(HSD_GObj* fighter_gobj);
void Fighter_UnkUpdateCostumeJoint_800686E4(HSD_GObj* fighter_gobj);
void Fighter_UnkUpdateVecFromBones_8006876C(Fighter* fp);
void Fighter_ResetInputData_80068854(HSD_GObj* fighter_gobj);
void Fighter_UnkInitLoad_80068914(HSD_GObj* fighter_gobj, struct S_TEMP1* argdata);
u32 Fighter_NewSpawn_80068E40();
void Fighter_80068E64(HSD_GObj* fighter_gobj);
HSD_GObj* Fighter_80068E98(struct S_TEMP1* input);
void Fighter_ActionStateChange_800693AC(HSD_GObj* fighter_gobj, s32 new_action_state_index, s32 flags, HSD_GObj* otherObj, f32 animStart, f32 animSpeed, f32 animBlend);
void Fighter_8006A1BC(HSD_GObj* fighter_gobj);
void Fighter_8006A360(HSD_GObj* fighter_gobj);
void Fighter_8006ABA0(HSD_GObj* fighter_gobj);
void Fighter_UnkIncrementCounters_8006ABEC(HSD_GObj* fighter_gobj);
void Fighter_Spaghetti_8006AD10(HSD_GObj* fighter_gobj);
void Fighter_procUpdate(HSD_GObj* fighter_gobj, s32 dummy);
void Fighter_UnkApplyTransformation_8006C0F0(HSD_GObj* fighter_gobj);
void Fighter_8006C27C(HSD_GObj* fighter_gobj, s32 unused, s32 unused2, s32 unused3);
void Fighter_8006C5F4(HSD_GObj* fighter_gobj);
void Fighter_CallAcessoryCallbacks_8006C624(HSD_GObj* fighter_gobj);
void Fighter_8006C80C(HSD_GObj* fighter_gobj);
void Fighter_UnkProcessGrab_8006CA5C(HSD_GObj* fighter_gobj);
void Fighter_8006CB94(HSD_GObj* fighter_gobj);
void Fighter_UnkTakeDamage_8006CC30(Fighter* fp, f32 damage_amount);
void Fighter_TakeDamage_8006CC7C(Fighter*, f32);
void Fighter_8006CDA4(Fighter* fp, s32 arg1, s32 arg2, s32 arg3);
void Fighter_8006CF5C(Fighter* fp, s32 arg1);
void Fighter_UnkSetFlag_8006CFBC(HSD_GObj* fighter_gobj);
void Fighter_8006CFE0(HSD_GObj* fighter_gobj);
void Fighter_UnkRecursiveFunc_8006D044(HSD_GObj* fighter_gobj);
void Fighter_8006D10C(HSD_GObj* fighter_gobj);
void Fighter_UnkProcessShieldHit_8006D1EC(HSD_GObj* fighter_gobj);
void Fighter_8006D9AC(HSD_GObj* fighter_gobj);
void Fighter_UnkCallCameraCallback_8006D9EC(HSD_GObj* fighter_gobj);
void Fighter_8006DA4C(HSD_GObj* fighter_gobj);
void Fighter_Unload_8006DABC(Fighter* fp);


///// Shared Fighter Code

#define PUSH_ATTRS(fp, attributeName)                                           \
    do {                                                                    \
        void* backup = (fp)->x2D8_specialAttributes2;                      \
        attributeName *src = (attributeName*)(fp)->x10C_ftData->ext_attr;  \
        void* *attr = &(fp)->x2D4_specialAttributes;                       \
        *(attributeName *)(fp)->x2D8_specialAttributes2 = *src;            \
        *attr = backup;                                                      \
    } while(0)

#define COPY_ATTRS(gobj, attributeName)                                          \
    Fighter* fp = gobj->user_data;                                               \
    attributeName* sA2 = (attributeName*)fp->x2D4_specialAttributes;             \
    attributeName* ext_attr = (attributeName*)fp->x10C_ftData->ext_attr;         \
    *sA2 = *ext_attr;                                                            \

#define SCALE_HEIGHT_ATTRS(num_attrs)                     \
    {                                                     \
        int i;                                            \
        for (i = 0; i < num_attrs; i++) {                 \
            sA2->height_attributes[i] *= fp->x34_scale.y; \
        }                                                 \
    }  \


// Works but unused decided to go with inline instead 
#define MACRO_ft_OnItemPickup(FTNAME, param1, param2)                             \
    void FTNAME##_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {                 \
        Fighter *fp = getFighter(fighter_gobj);                                \
        if (!func_8026B2B4(fp->x1974_heldItem)) {                            \
            switch (func_8026B320(fp->x1974_heldItem)) {                     \
                case 1:                                                           \
                    func_80070FB4(fighter_gobj, param1, 1);                         \
                    break;                                                        \
                case 2:                                                           \
                    func_80070FB4(fighter_gobj, param1, 0);                         \
                    break;                                                        \
                case 3:                                                           \
                    func_80070FB4(fighter_gobj, param1, 2);                         \
                    break;                                                        \
                case 4:                                                           \
                    func_80070FB4(fighter_gobj, param1, 3);                         \
                    break;                                                        \
            }                                                                     \
            if (bool) {                                                           \
                func_80070C48(fighter_gobj, param2);                                \
            }                                                                     \
        }                                                                         \
    }                                                                             \

/// used for all fighters except Kirby and Purin
inline void Fighter_OnItemPickup(HSD_GObj* fighter_gobj, BOOL catchItemFlag, BOOL bool2, BOOL bool3) {
    Fighter *fp = getFighter(fighter_gobj);            
    if (!func_8026B2B4(fp->x1974_heldItem)) {        
        switch (func_8026B320(fp->x1974_heldItem)) { 
            case 1:                                       
                func_80070FB4(fighter_gobj, bool2, 1);     
                break;                                    
            case 2:                                       
                func_80070FB4(fighter_gobj, bool2, 0);     
                break;                                    
            case 3:                                       
                func_80070FB4(fighter_gobj, bool2, 2);     
                break;                                    
            case 4:                                       
                func_80070FB4(fighter_gobj, bool2, 3);     
                break;                                    
        }                                                 
        if (catchItemFlag) {                                       
            func_80070C48(fighter_gobj, bool3);            
        }                                                 
    }                                                     
}

inline void Fighter_OnItemInvisible(HSD_GObj* gobj, BOOL bool)
{
    Fighter* fp = getFighter(gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        func_80070CC4(gobj, bool);
    }
}

inline void Fighter_OnItemVisible(HSD_GObj* gobj, BOOL bool)
{
    Fighter* fp = getFighter(gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        func_80070C48(gobj, bool);
    }
}

inline void Fighter_OnItemDrop(HSD_GObj* gobj, BOOL dropItemFlag, BOOL bool2, BOOL bool3)
{
    func_80070FB4(gobj, bool2, -1);
    if (dropItemFlag) {
        func_80070CC4(gobj, bool3);
    }
}

inline void Fighter_OnKnockbackEnter(HSD_GObj* gobj, s32 arg1) {
    func_800704F0(gobj, arg1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

inline void Fighter_OnKnockbackExit(HSD_GObj* gobj, s32 arg1) {
    func_800704F0(gobj, arg1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

inline void Fighter_UnsetCmdVar0(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
}

extern unk_t lbl_804D6520;
extern ftCommonData* p_ftCommonData;

#endif
