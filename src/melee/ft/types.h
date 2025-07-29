#ifndef MELEE_FT_TYPES_H
#define MELEE_FT_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h" // IWYU pragma: export
#include "it/forward.h"
#include <baselib/forward.h>

#include "cm/types.h"
#include "ftCaptain/types.h"
#include "ftCommon/types.h"
#include "ftDonkey/types.h"
#include "ftFox/types.h"
#include "ftGameWatch/types.h"
#include "ftKirby/types.h"
#include "ftKoopa/types.h"
#include "ftLink/types.h"
#include "ftLuigi/types.h"
#include "ftMario/types.h"
#include "ftMars/types.h"
#include "ftMasterHand/types.h"
#include "ftMewtwo/types.h"
#include "ftNess/types.h"
#include "ftPeach/types.h"
#include "ftPikachu/types.h"
#include "ftPopo/types.h"
#include "ftPurin/types.h"
#include "ftSamus/types.h"
#include "ftSandbag/types.h"
#include "ftSeak/types.h"
#include "ftYoshi/types.h"
#include "ftZakoBoy/types.h"
#include "ftZelda/types.h"
#include "gr/types.h"
#include "lb/lbanim.h"
#include "lb/types.h"

#include <common_structs.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#define FTPART_INVALID 0xFF

// Table in PlCo.dat
typedef struct _FighterPartsTable {
    u8* joint_to_part;
    u8* part_to_joint;
    u32 parts_num;
} FighterPartsTable;

// Points to data in PlCo.dat
struct ftCommonData {
    /* +0 */ float x0;
    /* +4 */ float x4;
    /* +8 */ float x8_someStickThreshold;
    /* +C */ float xC;
    /* +10 */ float x10;
    /* +14 */ float x14;
    /* +18 */ float x18;
    /* +1C */ int x1C;
    /* +20 */ float x20;
    /* +24 */ float x24;
    /* +28 */ float x28;
    /* +2C */ float x2C;
    /* +30 */ float x30;
    /* +34 */ float x34;
    /* +38 */ float x38_someLStickXThreshold;
    /* +3C */ float x3C;
    /* +40 */ int x40;
    /* +44 */ float x44;
    /* +48 */ float x48;
    /* +4C */ float x4C;
    /* +50 */ float x50;
    /* +54 */ float x54;
    /* +58 */ float x58_someLStickXThreshold;
    /* +5C */ float x5C;
    /* +60 */ float x60_someFrictionMul;
    /* +64 */ UNK_T x64;
    /* +68 */ float x68;
    /* +6C */ float x6C;
    /* +70 */ float tap_jump_threshold;
    /* +6C */ int x74;
    /* +78 */ float x78;
    /* +7C */ float tap_jump_release_threshold;
    /* +80 */ float x80;
    /* +84 */ u8 x84[4];
    /* +88 */ float x88;
    /* +8C */ int x8C;
    /* +90 */ u8 x90[0x98 - 0x90];
    /* +98 */ float x98;
    /* +9C */ float x9C;
    /* +A0 */ float xA0;
    /* +A4 */ float xA4;
    /* +A8 */ float xA8;
    /* +AC */ float attackhi3_stick_threshold_y;
    /* +B0 */ float xB0;
    /* +B4 */ float xB4;
    /* +B8 */ float xB8;
    /* +BC */ float xBC;
    /* +C0 */ float xC0;
    /* +C4 */ float xC4;
    /* +C8 */ float xC8;
    /* +CC */ float xCC;
    /* +D0 */ float xD0;
    /* +D4 */ float xD4;
    /* +D8 */ float xD8;
    /* +DC */ float xDC;
    /* +E0 */ float xE0;
    /* +E4 */ int xE4;
    /* +E8 */ float xE8;
    /* +EC */ float xEC;
    /* +F0 */ float xF0;
    /* +F4 */ float xF4;
    /* +F8 */ float xF8;
    /* +FC */ int xFC;
    /* +100 */ float x100;
    /* +104 */ float kb_min;
    /* +108 */ UNK_T x108;
    /* +10C */ UNK_T x10C;
    /* +110 */ UNK_T x110;
    /* +114 */ UNK_T x114;
    /* +118 */ UNK_T x118;
    /* +11C */ UNK_T x11C;
    /* +120 */ UNK_T x120;
    /* +124 */ float kb_squat_mul;
    /* +128 */ float x128;
    /* +12C */ float x12C;
    /* +130 */ int x130;
    /* +134 */ int x134;
    /* +138 */ float x138;
    /* +13C */ float x13C;
    /* +140 */ float x140;
    /* +144 */ float x144;
    /* +148 */ float x148;
    /* +14C */ float x14C;
    /* +150 */ float x150;
    /* +154 */ float x154;
    /* +158 */ float x158;
    /* +15C */ float x15C;
    /* +160 */ float x160;
    /* +164 */ float x164;
    /* +168 */ float x168;
    /* +16C */ float x16C;
    /* +170 */ float x170;
    /* +174 */ float x174;
    /* +178 */ float x178;
    /* +17C */ float x17C;
    /* +180 */ float x180;
    /* +184 */ float x184;
    /* +188 */ float x188;
    /* +18C */ int x18C;
    /* +190 */ float x190;
    /* +194 */ float x194_unkHitLagFrames;
    /* +198 */ float x198;
    /* +19C */ float x19C;
    /* +1A0 */ float x1A0;
    /* +1A4 */ UNK_T x1A4;
    /* +1A8 */ float x1A8;
    /* +1AC */ float x1AC;
    /* +1B0 */ float x1B0;
    /* +1B4 */ UNK_T x1B4;
    /* +1B8 */ int x1B8;
    /* +1BC */ float x1BC;
    /* +1C0 */ float x1C0;
    /* +1C4 */ UNK_T x1C4;
    /* +1C8 */ float x1C8;
    /* +1CC */ float x1CC;
    /* +1D0 */ float x1D0;
    /* +1D4 */ UNK_T x1D4;
    /* +1D8 */ UNK_T x1D8;
    /* +1DC */ UNK_T x1DC;
    /* +1E0 */ float x1E0;
    /* +1E4 */ float x1E4;
    /* +1E8 */ UNK_T x1E8;
    /* +1EC */ float x1EC;
    /* +1F0 */ float x1F0;
    /* +1F4 */ float x1F4;
    /* +1F8 */ UNK_T x1F8;
    /* +1FC */ float x1FC;
    /* +200 */ float x200;
    /* +204 */ float x204_knockbackFrameDecay;
    /* +208 */ u8 x208[0x210 - 0x208];
    /* +210 */ float x210;
    /* +214 */ int x214;
    /* +218 */ float x218;
    /* +21C */ float x21C;
    /* +220 */ float x220;
    /* +224 */ int x224;
    /* +228 */ float x228;
    /* +22C */ float x22C;
    /* +230 */ float x230;
    /* +234 */ UNK_T x234;
    /* +238 */ UNK_T x238;
    /* +23C */ UNK_T x23C;
    /* +240 */ UNK_T x240;
    /* +244 */ float x244;
    /* +248 */ float x248;
    /* +24C */ float x24C;
    /* +250 */ float x250;
    /* +254 */ float x254;
    /* +258 */ float x258;
    /* +25C */ float x25C;
    /* +260 */ float x260_startShieldHealth;
    /* +264 */ float x264;
    /* +268 */ float x268;
    /* +26C */ UNK_T x26C;
    /* +270 */ UNK_T x270;
    /* +274 */ UNK_T x274;
    /* +278 */ float x278;
    /* +27C */ float x27C;
    /* +280 */ float x280_unkShieldHealth;
    /* +284 */ float x284;
    /* +288 */ float x288;
    /* +28C */ float x28C;
    /* +290 */ float x290;
    /* +294 */ float x294;
    /* +298 */ float x298;
    /* +29C */ UNK_T x29C;
    /* +2A0 */ int x2A0;
    /* +2A4 */ float x2A4;
    /* +2A8 */ float x2A8;
    /* +2AC */ float x2AC;
    /* +2B0 */ float x2B0;
    /* +2B4 */ float x2B4;
    /* +2B8 */ int x2B8;
    /* +2BC */ float x2BC;
    /* +2C0 */ UNK_T x2C0;
    /* +2C4 */ UNK_T x2C4;
    /* +2C8 */ UNK_T x2C8;
    /* +2CC */ UNK_T x2CC;
    /* +2D0 */ UNK_T x2D0;
    /* +2D4 */ float x2D4;
    /* +2D8 */ float x2D8;
    /* +2DC */ float x2DC;
    /* +2E0 */ float x2E0;
    /* +2E4 */ float x2E4;
    /* +2E8 */ float x2E8;
    /* +2EC */ float x2EC;
    /* +2F0 */ float x2F0;
    /* +2F4 */ UNK_T x2F4;
    /* +2F8 */ float x2F8;
    /* +2FC */ float x2FC;
    /* +300 */ float x300;
    /* +304 */ float x304;
    /* +308 */ float x308;
    /* +30C */ UNK_T x30C;
    /* +310 */ UNK_T x310;
    /* +314 */ float x314;
    /* +318 */ int x318;
    /* +31C */ float x31C;
    /* +320 */ int x320;
    /* +324 */ int x324;
    /* +328 */ UNK_T x328;
    /* +32C */ Vec2 escapeair_deadzone;
    /* +334 */ int x334;
    /* +338 */ float escapeair_force;
    /* +33C */ float escapeair_decay;
    /* +340 */ float x340;
    /* +344 */ float x344;
    /* +348 */ UNK_T x348;
    /* +34C */ UNK_T x34C;
    /* +350 */ UNK_T x350;
    /* +354 */ UNK_T x354;
    /* +358 */ UNK_T x358;
    /* +35C */ UNK_T x35C;
    /* +360 */ UNK_T x360;
    /* +364 */ UNK_T x364;
    /* +368 */ UNK_T x368;
    /* +36C */ UNK_T x36C;
    /* +370 */ UNK_T x370;
    /* +374 */ UNK_T x374;
    /* +378 */ UNK_T x378;
    /* +37C */ UNK_T x37C;
    /* +380 */ UNK_T x380;
    /* +384 */ UNK_T x384;
    /* +388 */ UNK_T x388;
    /* +38C */ UNK_T x38C;
    /* +390 */ UNK_T x390;
    /* +394 */ UNK_T x394;
    /* +398 */ UNK_T x398;
    /* +39C */ UNK_T x39C;
    /* +3A0 */ UNK_T x3A0;
    /* +3A4 */ UNK_T x3A4;
    /* +3A8 */ float x3A8;
    /* +3AC */ UNK_T x3AC;
    /* +3B0 */ float x3B0;
    /* +3B4 */ float shouldered_anim_rate;
    /* +3B8 */ UNK_T x3B8;
    /* +3BC */ UNK_T x3BC;
    /* +3C0 */ int x3C0;
    /* +3C4 */ UNK_T x3C4;
    /* +3C8 */ UNK_T x3C8;
    /* +3CC */ int x3CC;
    /* +3D0 */ float x3D0;
    /* +3D4 */ float x3D4;
    /* +3D8 */ float x3D8;
    /* +3DC */ float x3DC;
    /* +3E0 */ float x3E0;
    /* +3E4 */ float x3E4;
    /* +3E8 */ float x3E8_shieldKnockbackFrameDecay;
    /* +3EC */ float x3EC_shieldGroundFrictionMultiplier;
    /* +3F0 */ u8 x3F0[0x3FC - 0x3F0];
    /* +3FC */ int x3FC;
    /* +400 */ float x400;
    /* +404 */ float x404;
    /* +408 */ float x408;
    /* +40C */ float x40C;
    /* +410 */ int x410;
    /* +414 */ UNK_T x414;
    /* +418 */ int x418;
    /* +41C */ int x41C;
    /* +420 */ UNK_T x420;
    /* +424 */ float x424;
    /* +428 */ int x428;
    /* +42C */ float x42C;
    /* +430 */ float x430;
    /* +434 */ UNK_T x434;
    /* +438 */ float x438;
    /* +43C */ UNK_T x43C;
    /* +440 */ float x440;
    /* +444 */ float x444;
    /* +448 */ float x448;
    /* +44C */ float x44C;
    /* +450 */ float x450;
    /* +454 */ float x454;
    /* +458 */ float x458;
    /* +45C */ float x45C;
    /* +460 */ float x460;
    /* +464 */ float x464;
    /* +468 */ float x468;
    /* +46C */ float x46C;
    /* +470 */ float x470;
    /* +474 */ float x474;
    /* +478 */ float x478;
    /* +47C */ float x47C;
    /* +480 */ float x480;
    /* +484 */ UNK_T x484;
    /* +488 */ int x488;
    /* +48C */ float x48C;
    /* +490 */ float x490;
    /* +494 */ float x494;
    /* +498 */ int ledge_cooldown;
    /* +49C */ int x49C;
    /* +4A0 */ float x4A0;
    /* +4A4 */ float x4A4;
    /* +4A8 */ float x4A8;
    /* +4AC */ float x4AC;
    /* +4B0 */ float x4B0;
    /* +4B4 */ int x4B4;
    /* +4B8 */ float x4B8;
    /* +4BC */ float x4BC;
    /* +4C0 */ float x4C0;
    /* +4C4 */ int x4C4;
    /* +4C8 */ int x4C8;
    /* +4CC */ int x4CC;
    /* +4D0 */ float x4D0;
    /* +4D4 */ float x4D4;
    /* +4D8 */ u32 x4D8;
    /* +4DC */ Vec2 x4DC;
    /* +4E4 */ Vec3 x4E4;
    /* +4F0 */ float x4F0;
    /* +4F4 */ UNK_T x4F4;
    /* +4F8 */ u32 x4F8;
    /* +4FC */ u32 x4FC;
    /* +500 */ UNK_T x500;
    /* +504 */ int x504;
    /* +508 */ UNK_T x508;
    /* +50C */ UNK_T x50C;
    /* +510 */ UNK_T x510;
    /* +514 */ UNK_T x514;
    /* +518 */ UNK_T x518;
    /* +51C */ UNK_T x51C;
    /* +520 */ int x520;
    /* +524 */ UNK_T x524;
    /* +528 */ UNK_T x528;
    /* +52C */ UNK_T x52C;
    /* +530 */ UNK_T x530;
    /* +534 */ UNK_T x534;
    /* +538 */ UNK_T x538;
    /* +53C */ UNK_T x53C;
    /* +540 */ UNK_T x540;
    /* +544 */ UNK_T x544;
    /* +548 */ UNK_T x548;
    /* +54C */ UNK_T x54C;
    /* +550 */ UNK_T x550;
    /* +554 */ UNK_T x554;
    /* +558 */ UNK_T x558;
    /* +55C */ UNK_T x55C;
    /* +560 */ UNK_T x560;
    /* +564 */ UNK_T x564;
    /* +568 */ float x568;
    /* +56C */ float x56C;
    /* +570 */ float x570;
    /* +574 */ float x574;
    /* +578 */ float x578;
    /* +57C */ int x57C;
    /* +580 */ int x580;
    /* +584 */ int x584;
    /* +588 */ int x588;
    /* +58C */ UNK_T x58C;
    /* +590 */ UNK_T x590;
    /* +594 */ UNK_T x594;
    /* +598 */ UNK_T x598;
    /* +59C */ float x59C;
    /* +5A0 */ float x5A0;
    /* +5A4 */ int x5A4;
    /* +5A8 */ float x5A8;
    /* +5AC */ float x5AC;
    /* +5B0 */ float x5B0;
    /* +5B4 */ int x5B4;
    /* +5B8 */ u8 x5B8[0x5C0 - 0x5B8];
    /* +5C0 */ float x5C0;
    /* +5C4 */ UNK_T x5C4;
    /* +5C8 */ int x5C8;
    /* +5CC */ float x5CC;
    /* +5D0 */ UNK_T x5D0;
    /* +5D4 */ UNK_T x5D4;
    /* +5D8 */ UNK_T x5D8;
    /* +5DC */ u32 bury_timer_unk1;
    /* +5E0 */ u32 bury_timer_unk2;
    /* +5E4 */ u32 bury_timer_unk3;
    /* +5E8 */ UNK_T x5E8;
    /* +5EC */ UNK_T x5EC;
    /* +5F0 */ u32 x5F0;
    /* +5F4 */ int x5F4;
    /* +5F8 */ float x5F8;
    /* +5FC */ float x5FC;
    /* +600 */ float x600;
    /* +604 */ float x604;
    /* +608 */ float x608;
    /* +60C */ float x60C;
    /* +610 */ float x610;
    /* +614 */ float x614;
    /* +618 */ float x618;
    /* +61C */ float x61C;
    /* +620 */ int x620;
    /* +624 */ float x624;
    /* +628 */ float x628;
    /* +62C */ float x62C;
    /* +630 */ float x630;
    /* +634 */ float x634;
    /* +638 */ float x638;
    /* +63C */ float x63C;
    /* +640 */ float x640;
    /* +644 */ float x644;
    /* +648 */ int x648;
    /* +64C */ float x64C;
    /* +650 */ float x650;
    /* +654 */ float x654;
    /* +658 */ float x658;
    /* +65C */ float x65C;
    /* +660 */ float x660;
    /* +664 */ float x664;
    /* +668 */ float x668;
    /* +66C */ float x66C;
    /* +670 */ float x670;
    /* +674 */ float x674;
    /* +678 */ float x678;
    /* +67C */ float x67C;
    /* +680 */ float x680;
    /* +684 */ float x684;
    /* +688 */ int x688;
    /* +68C */ int x68C;
    /* +690 */ int x690;
    /* +694 */ float x694;
    /* +698 */ float x698;
    /* +69C */ float x69C;
    /* +6A0 */ float x6A0;
    /* +6A4 */ float x6A4;
    /* +6A8 */ float x6A8;
    /* +6AC */ int x6AC;
    /* +6B0 */ int x6B0;
    /* +6B4 */ int x6B4;
    /* +6B8 */ int x6B8;
    /* +6BC */ UNK_T x6BC;
    /* +6C0 */ UNK_T x6C0;
    /* +6C4 */ UNK_T x6C4;
    /* +6C8 */ int x6C8;
    /* +6CC */ int x6CC;
    /* +6D0 */ float x6D0;
    /* +6D4 */ UNK_T x6D4;
    /// @todo expand to actual size
    /* +6D8 */ void* x6D8[1];
    /* +6DC */ GXColor x6DC_colorsByPlayer[4];
    /* +6EC */ u8 x6EC[0x6F0 - 0x6EC];
    /* +6F0 */ float unk_armor;
    /* +6F4 */ int x6F4_unkDamage;
    /* +6F8 */ int x6F8;
    /* +6FC */ int x6FC;
    /* +700 */ int x700;
    /* +704 */ float x704;
    /* +708 */ float x708;
    /* +70C */ float x70C;
    /* +710 */ float x710;
    /* +714 */ float x714;
    /* +718 */ float kb_ice_mul;
    /* +71C */ u8 x71C[0x760 - 0x71C];
    /* +760 */ int x760;
    /* +764 */ int x764;
    /* +768 */ float x768;
    /* +76C */ float x76C;
    /* +770 */ float x770;
    /* +774 */ int x774;
    /* +778 */ float passive_wall_vel_y_base;
    /* +77C */ float x77C;
    /* +780 */ UNK_T x780;
    /* +784 */ UNK_T x784;
    /* +788 */ float x788;
    /* +78C */ float x78C;
    /* +790 */ UNK_T x790;
    /* +794 */ float x794;
    /* +798 */ float x798;
    /* +79C */ float x79C;
    /* +7A0 */ float x7A0;
    /* +7A4 */ float x7A4;
    /* +7A8 */ float x7A8;
    /* +7AC */ int x7AC;
    /* +7B0 */ int x7B0;
    /* +7B4 */ int x7B4_unkDamage;
    /* +7B8 */ float x7B8;
    /* +7BC */ float x7BC;
    /* +7C0 */ float x7C0;
    /* +7C4 */ float kb_smashcharge_mul;
    /* +7C8 */ int x7C8;
    /* +7CC */ int x7CC;
    /* +7D0 */ int x7D0;
    /* +7D4 */ float hit_weight_mul;
    /* +7D8 */ GXColor x7D8;
    /* +7DC */ int x7DC;
    /* +7E0 */ int x7E0;
    /* +7E4 */ float x7E4_scaleZ;
    /* +7E8 */ u32 unk_kb_angle_min;
    /* +7EC */ u32 unk_kb_angle_max;
    /* +7F0 */ int x7F0;
    /* +7F4 */ u8 x7F4[0x800 - 0x7F4];
    /* +800 */ float x800;
    /* +804 */ u8 x804[4];
    /* +804 */ Vec3 x808;
    /* +814 */ int x814;
    // lots of more data following, exact size to be determined
};

typedef struct _FtSFXArr {
    int num;
    int* sfx_ids;
} FtSFXArr;

struct FtSFX {
    FtSFXArr* smash;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
    int x18;
    int x1C;
    int x20;
    int x24;
    int x28;
    int x2C;
    int x30;
    int x34;
};

struct DObjList {
    usize_t count;
    HSD_DObj** data;
};

typedef struct {
    u32 unk0;
    f32 unk4;
} ftData_x34;

typedef struct ftData_x44_t {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    float unkC;
    float unk10;
    float unk14;
    float unk18;
} ftData_x44_t;

struct ftData {
    /*  +0 */ struct {
        /*   +0 */ u8 x0[0x8C];
        /*  +8C */ float x8C;
        /*  +90 */ u8 x90[0xFC - 0x90];
        /*  +FC */ float xFC;
        /* +100 */ u8 x100[0x168 - 0x100];
        /* +168 */ float x168;
        /* +16C */ int x16C_idx;
    }* x0;
    /*  +4 */ void* ext_attr;
    /*  +8 */ struct ftData_x8 {
        /*  +0 */ u8 x0[0x8];
        /*  +8 */ struct ftData_x8_x8 {
            /*  +8 */ u32 x8;
            /*  +C */ u16** xC;
        } x8;
        /* +10 */ u8 x10;
        /* +11 */ u8 x11;
        /* +12 */ u8 x12;
        /* +13 */ u8 x13;
        /* +14 */ u8 x14;
    }* x8;
    /*  +C */ struct S_TEMP4* xC;
    /* +10 */ u8* x10;
    /* +14 */ struct S_TEMP4* x14;
    /* +18 */ u8* x18;
    /* +1C */ UNK_T x1C;
    /* +20 */ struct {
        /* +0 */ UNK_T x0;
        /* +4 */ HSD_Joint* x8;
    }* x20;
    /* +24 */ UNK_T x24;
    /* +28 */ UNK_T x28;
    /* +2C */ struct ftDynamics* x2C;
    /* +30 */ UNK_T x30;
    /* +34 */ struct ftData_x34 {
        /* +0 */ Fighter_Part x0;
        /* +4 */ float scale;
    }* x34;
    /* +38 */ UNK_T x38;
    /* +3C */ struct UnkFloat6_Camera* x3C;
    /* +40 */ UNK_T _40;
    /* +44 */ ftData_x44_t* x44;
    /* +48 */ UNK_T* x48_items;
    /* +4C */ FtSFX* x4C_sfx;
    /* +50 */ u8 x50[0x54 - 0x50];
    /* +54 */ int x54;
    /* +58 */ void* x58;
};

typedef struct _ThrowFlags {
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

struct ftCo_DatAttrs_xBC_t {
    float size;
    Vec3 x4;
    Vec3 x10;
    float x1C;
};

typedef struct ftCo_DatAttrs {
    /* +000 fp+110 */ float walk_init_vel;
    /* +004 fp+114 */ float walk_accel;
    /* +008 fp+118 */ float walk_max_vel;
    /* +00C fp+11C */ float slow_walk_max;
    /* +010 fp+120 */ float mid_walk_point;
    /* +014 fp+124 */ float fast_walk_min;
    /* +018 fp+128 */ float gr_friction;
    /* +01C fp+12C */ float dash_initial_velocity;
    /* +020 fp+130 */ float dash_run_acceleration_a;
    /* +024 fp+134 */ float dash_run_acceleration_b;
    /* +028 fp+138 */ float dash_run_terminal_velocity;
    /* +02C fp+13C */ float run_animation_scaling;
    /* +030 fp+140 */ float max_run_brake_frames;
    /* +034 fp+144 */ float grounded_max_horizontal_velocity;
    /* +038 fp+148 */ float jump_startup_time;
    /* +03C fp+14C */ float jump_h_initial_velocity;
    /* +040 fp+150 */ float jump_v_initial_velocity;
    /* +044 fp+154 */ float ground_to_air_jump_momentum_multiplier;
    /* +048 fp+158 */ float jump_h_max_velocity;
    /* +04C fp+15C */ float hop_v_initial_velocity;
    /* +050 fp+160 */ float air_jump_v_multiplier;
    /* +054 fp+164 */ float air_jump_h_multiplier;
    /* +058 fp+168 */ int max_jumps;
    /* +05C fp+16C */ float grav;
    /* +060 fp+170 */ float terminal_vel;
    /* +064 fp+174 */ float air_drift_stick_mul;
    /* +068 fp+178 */ float aerial_drift_base;
    /* +06C fp+17C */ float air_drift_max;
    /* +070 fp+180 */ float aerial_friction;
    /* +074 fp+184 */ float fast_fall_velocity;
    /* +078 fp+188 */ float horizontal_air_mobility_constant;
    /* +07C fp+18C */ float jab_2_input_window;
    /* +080 fp+190 */ float jab_3_input_window;
    /* +084 fp+194 */ float frames_to_change_direction_on_standing_turn;
    /* +088 fp+198 */ float weight;
    /* +08C fp+19C */ float model_scaling;
    /* +090 fp+1A0 */ float initial_shield_size;
    /* +094 fp+1A4 */ float shield_break_initial_velocity;
    /* +098 fp+1A8 */ int rapid_jab_window;
    /* +09C fp+1AC */ float x9C;
    /* +0A0 fp+1B0 */ int xA0;
    /* +0A4 fp+1B4 */ int xA4;
    /* +0A8 fp+1B8 */ float ledge_jump_horizontal_velocity;
    /* +0AC fp+1BC */ float ledge_jump_vertical_velocity;
    /* +0B0 fp+1C0 */ float item_throw_velocity_multiplier;
    /* +0B4 fp+1C4 */ int xB4;
    /* +0B8 fp+1C8 */ float xB8;
    /* +0BC fp+1CC */ ftCo_DatAttrs_xBC_t xBC;
    /* +0DC fp+1EC */ float xDC;
    /* +0E0 fp+1F0 */ float kirby_b_star_damage;
    /* +0E4 fp+1F4 */ float normal_landing_lag;
    /* +0E8 fp+1F8 */ float landingairn_lag;
    /* +0EC fp+1FC */ float landingairf_lag;
    /* +0F0 fp+200 */ float landingairb_lag;
    /* +0F4 fp+204 */ float landingairhi_lag;
    /* +0F8 fp+208 */ float landingairlw_lag;
    /* +0FC fp+20C */ float name_tag_height;
    /* +100 fp+210 */ float passivewall_vel_x;
    /* +104 fp+214 */ float wall_jump_horizontal_velocity;
    /* +108 fp+218 */ float wall_jump_vertical_velocity;
    /* +10C fp+21C */ float passiveceil_vel_x;
    /* +110 fp+220 */ float trophy_scale;
    /* +114 fp+224 */ Vec3 x114;
    /* +118 fp+230 */ Vec3 x118;
    /* +11C fp+23C */ float x11C;
    /* +120 fp+240 */ Vec3 x120;
    /* +124 fp+24C */ float x124;
    /* +128 fp+250 */ float x128;
    /* +12C fp+254 */ int x12C;
    /* +130 fp+258 */ float x130;
    /* +134 fp+25C */ float bubble_ratio;
    /* +138 fp+260 */ int x138;
    /* +13C fp+264 */ int x13C;
    /* +140 fp+268 */ float x140;
    /* +144 fp+26C */ int x144;
    /* +148 fp+270 */ float respawn_platform_scale;
    /* +14C fp+274 */ float x14C;
    /* +150 fp+278 */ int x150;
    /* +154 fp+27C */ int camera_zoom_target_bone;
    /* +158 fp+280 */ Vec3 x158;
    /* +15C fp+28C */ float x15C;
    /* +160 fp+290 */ int weight_dependent_throw_speed_flags;
} ftCo_DatAttrs;

struct FighterBone {
    /* +0 */ HSD_JObj* joint;
    /* +4 */ HSD_JObj* x4_jobj2; // used for interpolation
    /* +8:0 */ u8 flags_b0 : 1;
    /* +8:1 */ u8 flags_b1 : 1;
    /* +8:2 */ u8 flags_b2 : 1;
    /* +8:3 */ u8 flags_b3 : 1;
    /* +8:4 */ u8 flags_b4 : 1;
    /* +8:5 */ u8 flags_b5 : 1;
    /* +8:6 */ u8 flags_b6 : 1;
    /* +8:7 */ u8 flags_b7 : 1;
    /* +9 */ u8 x9_pad[3];
    /* +C */ u8 xC;
};
STATIC_ASSERT(sizeof(struct FighterBone) == 0x10);

/* fp+2114 */ typedef struct _SmashAttr {
    /* fp+2114 */ SmashState state;
    /// number of frames fp has charged for
    /* fp+2118 */ float x2118_frames;
    /// frame that charge begins/ends
    /* fp+211C */ float x211C_holdFrame;
    /// damage multiplier
    /* fp+2120 */ float x2120_damageMul;
    /// speed multiplier?
    /* fp+2124 */ float x2124_frameSpeedMul;
    /* fp+2128 */ s32 x2128;
    /* fp+212C */ s8 x212C;
    /* fp+212D */ s8 x212D;
    /* fp+212E */ s8 x212E;
    /* fp+212F */ s8 x212F;
    /// bool for smash sfx?
    /* fp+2130 */ s32 x2130_sfxBool;
    /* fp+2134 */ s8 x2134_vibrateFrame;
    /* fp+2135 */ s8 x2135;
    /* fp+2136 */ s8 x2136;
    /* fp+2137 */ s8 x2137;
    /* fp+2138 */ float x2138_smashSinceHitbox;
} SmashAttr;

typedef struct itPickup {
    /*  +0 */ Vec4 gr_light_offset;
    /* +10 */ Vec4 gr_heavy_offset;
    /* +20 */ Vec4 air_light_offset;
} itPickup;

typedef struct {
    HSD_Joint* joint;
    HSD_MatAnimJoint* x4;
    u8 padding[0x0C];
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
    /* +6:0 */ u8 flags_b0 : 1;
    /* +6:1 */ u8 flags_b1 : 1;
};

struct MotionState {
    enum_t anim_id;

    enum_t x4_flags;

    union {
        /// @todo Try to match without this being a @c union.
        u32 _;
        struct {
            u8 move_id : 8;
            struct {
                u8 x9_b0 : 1;
                u8 x9_b1 : 1;
                u8 x9_b2 : 1;
                u8 x9_b3 : 1;
                u8 x9_b4 : 1;
                u8 x9_b5 : 1;
                u8 x9_b6 : 1;
                u8 x9_b7 : 1;
            };
            u8 xA;
            u8 xB;
        };
    };

    HSD_GObjEvent anim_cb;
    HSD_GObjEvent input_cb;
    HSD_GObjEvent phys_cb;
    HSD_GObjEvent coll_cb;
    HSD_GObjEvent cam_cb;
};

struct S_TEMP4 {
    s32 x0;
    s32 x4;
    s32 x8;
    ftSubactionList* xC;
    s32 x10_animCurrFlags;
    s32 x14;
};

struct Fighter_CostumeStrings {
    char* dat_filename;
    char* joint_name;
    char* matanim_joint_name;
};

struct Fighter_DemoStrings {
    char* result_filename;
    char* intro_filename;
    char* ending_filename;
    char* vi_wait_filename;
};

/// @todo Rename this and its members; investigate using it elsewhere.
/* fp+2070 */ union Struct2070 {
    /* fp+2070 */ struct {
        /* fp+2070 */ s8 x2070;
        /* fp+2071:0 */ u8 x2071_b0_3 : 4;
        /* fp+2071:4 */ u8 x2071_b4 : 1;
        /* fp+2071:5 */ u8 x2071_b5 : 1;
        /* fp+2071:6 */ u8 x2071_b6 : 1;
        /* fp+2071:7 */ u8 x2071_b7 : 1;
        /* fp+2072:0 */ u8 x2072_b0 : 1;
        /* fp+2072:1 */ u8 x2072_b1 : 1;
        /* fp+2072:2 */ u8 x2072_b2 : 1;
        /* fp+2072:3 */ u8 x2072_b3 : 1;
        /* fp+2072:4 */ u8 x2072_b4 : 1;
        /* fp+2072:5 */ u8 x2072_b5 : 1;
        /* fp+2072:6 */ u8 x2072_b6 : 1;
        /* fp+2072:7 */ u8 x2072_b7 : 1;
        /* fp+2073 */ u8 x2073;
    };
    /* fp+2070 */ s32 x2070_int;
};

/// @todo See if this should likewise be instituted for item->xD94 thru
/// xDA4_word/xDA8_short
/* fp+2074 */ struct Struct2074 {
    /* fp+2074 */ Vec2 x2074_vec;
    /* fp+207C */ S32Vec2 x207C;
    /* fp+2084 */ u32 x2084;
    /* fp+2088 */ u16 x2088;
};

struct ftSubactionList {
    u8 x0_opcode;
};

struct ftCmdScript {
    float x3E4_scriptEventTimer;         // 0x3E4
    float x3E8_scriptFrameTimer;         // 0x3E8
    ftSubactionList* x3EC_scriptCurrent; // 0x3EC
    s32 x3F0_scriptLoopNum;              // 0x3F0
    void* x3F4_scriptReturn;             // 0x3F4
};

struct ftDeviceUnk1 {
    /*  +0 */ u8 x0[0x7B - 0x00];
    /* +7B */ u8 x7B;
};

struct ftDeviceUnk2 {
    /*  +0 */ UNK_T x0;
    /*  +4 */ UNK_T x4;
    /*  +8 */ UNK_T x8;
    /*  +C */ UNK_T xC;
    /* +10 */ UNK_T x10;
    /* +14 */ UNK_T x14;
    /* +18 */ UNK_T x18;
    /* +1C */ UNK_T x1C;
    /* +20 */ UNK_T x20;
    /* +24 */ UNK_T x24;
    /* +28 */ ftDeviceUnk1* x28;
    /* +2C */ UNK_T x2C;
    /* +30 */ UNK_T x30;
    /* +34 */ UNK_T x34;
    /* +38 */ UNK_T x38;
    /* +3C */ UNK_T x3C;
    /* +40 */ UNK_T x40;
    /* +44 */ UNK_T x44;
    /* +48 */ UNK_T x48;
    /* +4C */ UNK_T x4C;
    /* +50 */ GXColor lobj_color;
    /* +54 */ UNK_T x54;
    /* +58 */ UNK_T x58;
    /* +5C */ UNK_T x5C;
    /* +60 */ UNK_T x60;
    /* +64 */ UNK_T x64;
    /* +68 */ UNK_T x68;
    /* +6C */ UNK_T x6C;
    /* +70 */ UNK_T x70;
    /* +74 */ float lobj_rot_x;
    /* +74 */ float lobj_rot_yz;
    /* +7C:0 */ u8 x7C_b0 : 1;
    /* +7C:1 */ u8 x7C_b1 : 1;
    /* +7C:2 */ u8 x7C_b2 : 1;
    /* +7C:3 */ u8 x7C_b3 : 1;
    /* +7C:4 */ u8 x7C_b4 : 1;
    /* +7C:5 */ u8 x7C_b5 : 1;
    /* +7C:6 */ u8 x7C_b6 : 1;
    /* +7C:7 */ u8 x7C_b7 : 1;
};

struct ftDeviceUnk3 {
    UNK_T x0;
    u32 x4;
    ftDevice_Callback0 active_cb;
};

struct ftDeviceUnk4 {
    int x0;
    UNK_T x4;
};
STATIC_ASSERT(sizeof(struct ftDeviceUnk4) == 0x8);

struct ftDeviceUnk5 {
    UNK_T x0;
    ftCommon_BuryType x4;
    bool (*cb)(UNK_T, Fighter_GObj*);
};
STATIC_ASSERT(sizeof(struct ftDeviceUnk5) == 0xC);

struct Fighter_x1A88_xFC_t {
    /*  +0 */ HSD_Pad x0;
    /*  +4 */ u8 x4;
    /*  +5 */ u8 x5;
    /*  +6 */ u8 x6;
    /*  +7 */ u8 x7;
    /*  +8 */ u8 x8;
    /*  +9 */ u8 x9;
    /*  +A */ u8 xA;
    /*  +B */ u8 xB;
    /*  +C */ Vec3 cur_pos;
    /* +18 */ float facing_dir;
    /* +1C */ struct Fighter_x1A88_xFC_t* x1C;
    /* +20 */ u8 x20[0x348 - 0x20];
};
STATIC_ASSERT(sizeof(struct Fighter_x1A88_xFC_t) == 0x348);

struct Fighter_x1A88_t {
    /*   +0 */ HSD_Pad x0;
    /*   +4 */ s8 x4;
    /*   +5 */ u8 x5;
    /*   +6 */ u8 x6;
    /*   +7 */ u8 x7;
    /*   +8 */ u8 x8;
    /*   +9 */ u8 x9;
    /*   +A */ u8 xA;
    /*   +B */ u8 xB;
    /*   +C */ enum_t xC;
    /*  +10 */ int x10;
    /*  +14 */ int x14;
    /*  +18 */ int x18;
    /*  +1C */ int x1C;
    /*  +20 */ int x20;
    /*  +24 */ u8 x24[0x34 - 0x24];
    /*  +34 */ float x34;
    /*  +38 */ float x38;
    /*  +3C */ UNK_T x3C;
    /*  +40 */ UNK_T x40;
    /*  +44 */ Fighter* x44;
    /*  +48 */ UNK_T x48;
    /*  +4C */ void* x4C;
    /*  +50 */ int x50;
    /*  +54 */ Vec2 x54;
    /*  +5C */ float x5C;
    /*  +60 */ int x60;
    /*  +64 */ Vec2 x64;
    /*  +64 */ u8 x6C[0x7C - 0x6C];
    /*  +7C */ int x7C;
    /*  +80 */ u8 x80[0xF8 - 0x80];
    /*  +F8:0 */ u8 xF8_b0 : 1;
    /*  +F8:1 */ u8 xF8_b1 : 1;
    /*  +F8:2 */ u8 xF8_b2 : 1;
    /*  +F8:3 */ u8 xF8_b3 : 1;
    /*  +F8:4 */ u8 xF8_b4 : 1;
    /*  +F8:5 */ u8 xF8_b5 : 1;
    /*  +F8:6 */ u8 xF8_b6 : 1;
    /*  +F8:7 */ u8 xF8_b7 : 1;
    /*  +F9:0 */ u8 xF9_b0 : 1;
    /*  +F9:1 */ u8 xF9_b1 : 1;
    /*  +F9:2 */ u8 xF9_b2 : 1;
    /*  +F9:3 */ u8 xF9_b3 : 1;
    /*  +F9:4 */ u8 xF9_b4 : 1;
    /*  +F9:5 */ u8 xF9_b5 : 1;
    /*  +F9:6 */ u8 xF9_b6 : 1;
    /*  +F9:7 */ u8 xF9_b7 : 1;
    /*  +FA:0 */ u8 xFA_b0 : 1;
    /*  +FA:1 */ u8 xFA_b1 : 1;
    /*  +FA:2 */ u8 xFA_b2 : 1;
    /*  +FA:3 */ u8 xFA_b3 : 1;
    /*  +FA:4 */ u8 xFA_b4 : 1;
    /*  +FA:5 */ u8 xFA_b5 : 1;
    /*  +FA:6 */ u8 xFA_b6 : 1;
    /*  +FA:7 */ u8 xFA_b7 : 1;
    /*  +FB:0 */ u8 xFB_b0 : 1;
    /*  +FB:1 */ u8 xFB_b1 : 1;
    /*  +FB:2 */ u8 xFB_b2 : 1;
    /*  +FB:3 */ u8 xFB_b3 : 1;
    /*  +FB:4 */ u8 xFB_b4 : 1;
    /*  +FB:5 */ u8 xFB_b5 : 1;
    /*  +FB:6 */ u8 xFB_b6 : 1;
    /*  +FB:7 */ u8 xFB_b7 : 1;
    /*  +FC */ struct Fighter_x1A88_xFC_t xFC;
    /* +444 */ struct Fighter_x1A88_xFC_t* x444;
    /* +448 */ struct Fighter_x1A88_xFC_t* x448;
    /* +44C */ UNK_T x44C;
    /* +450 */ UNK_T x450;
    /* +454 */ u32 x454;
    /* +458 */ u8 x458[0x554 - 0x458];
    /* +554 */ union Fighter_x1A88_x544_t {
        struct {
            u8 x0_u8;
        };
        u32 x0_u32;
        void* x0_p;
    } x554;
    /* +558 */ float x558;
    /* +558 */ u8 x55C[0x568 - 0x55C];
    /* +568 */ float x568;
    /* +56C */ float x56C;
    /* +570 */ UNK_T x570;
    /* +574 */ float half_width;
    /* +578 */ float half_height;
};
STATIC_ASSERT(sizeof(struct Fighter_x1A88_t) == 0x57C);

struct Fighter_x59C_t {
    char pad_0[0x8000];
};
STATIC_ASSERT(sizeof(struct Fighter_x59C_t) == 0x8000);

struct UnkPlBonusBits {
    u8 x0, x1;
    u8 x2_b0 : 1;
    u8 x2_b1 : 1;
    u8 x2_b2 : 1;
    u8 x2_b3 : 1;
    u8 x2_b4 : 1;
    u8 x2_b5 : 1;
    u8 x2_b6 : 1;
    u8 x2_b7 : 1;
    u8 x3;
};

struct ft_800898B4_t {
    /*  +0  */ int x0;
    /*  +4  */ int x4;
    /*  +8  */ float kb_applied1;
    /*  +C  */ int xC;
    /*  +10 */ u32 x10_b0 : 1;
    /*  +10 */ u32 x10_b1 : 1;
    /*  +10 */ u32 x10_b2 : 1;
    /*  +10 */ u32 x10_b3 : 1;
    /*  +10 */ u32 x10_b4 : 1;
    /*  +10 */ u32 x10_b5 : 1;
    /*  +10 */ u32 x10_b6 : 1;
    /*  +10 */ u32 x10_b7 : 1;
    /*  +11 */ u32 x11_b0 : 1;
    /*  +11 */ u32 x11_b1 : 1;
    /*  +11 */ u32 x11_b2 : 1;
    /*  +11 */ u32 x11_b3 : 1;
    /*  +11 */ u32 x11_b4 : 1;
};

struct Fighter {
    /*    fp+0 */ HSD_GObj* gobj;
    /*    fp+4 */ FighterKind kind;
    /*    fp+8 */ s32 x8_spawnNum;
    /*    fp+C */ u8 player_id;
    /*   fp+10 */ FtMotionId motion_id;
    /*   fp+14 */ enum_t anim_id;
    /*   fp+18 */ s32 x18;
    /*   fp+1C */ MotionState* x1C_actionStateList;
    /*   fp+20 */ MotionState* x20_actionStateList;
    /*   fp+24 */ struct S_TEMP4* x24;
    /*   fp+28 */ u8* x28;
    /*   fp+2C */ float facing_dir;
    /*   fp+30 */ float facing_dir1;
    /*   fp+34 */ Vec3 x34_scale;
    /*   fp+40 */ float x40;
    /*   fp+44 */ Mtx x44_mtx;
    /*   fp+74 */ Vec3 x74_anim_vel;
    /*   fp+80 */ Vec3 self_vel;
    /*   fp+8C */ Vec3 x8c_kb_vel;
    /*   fp+98 */ Vec3 x98_atk_shield_kb;
    /*   fp+A4 */ Vec3 xA4_unk_vel;
    /*   fp+B0 */ Vec3 cur_pos;
    /*   fp+BC */ Vec3 prev_pos;
    /*   fp+C8 */ Vec3 pos_delta;
    /*   fp+D4 */ Vec3 xD4_unk_vel;
    /*   fp+E0 */ GroundOrAir ground_or_air;
    /*   fp+E4 */ float xE4_ground_accel_1;
    /*   fp+E8 */ float xE8_ground_accel_2;
    /*   fp+EC */ float gr_vel;
    /*   fp+F0 */ float xF0_ground_kb_vel;
    /*   fp+F4 */ float xF4_ground_attacker_shield_kb_vel;
    /*   fp+F8 */ Vec2 xF8_playerNudgeVel;
    /*  fp+100 */ float x100;
    /*  fp+104 */ u8 x104;
    /*  fp+105 */ s8 x105;
    /*  fp+106 */ s8 x106;
    /*  fp+107 */ s8 x107;
    /*  fp+108 */ HSD_Joint* x108_costume_joint;
    /*  fp+10C */ ftData* ft_data;
    /*  fp+110 */ ftCo_DatAttrs co_attrs;
    /*  fp+294 */ itPickup x294_itPickup;
    /*  fp+2C4 */ Vec2 x2C4;
    /*  fp+2CC */ ftDonkeyAttributes* x2CC;
    /*  fp+2D0 */ void* x2D0;
    /*  fp+2D4 */ void* dat_attrs;
    /*  fp+2D8 */ void* dat_attrs_backup;
    /*  fp+2DC */ float x2DC;
    /*  fp+2E0 */ float x2E0;
    /*  fp+2E4 */ float x2E4;
    /*  fp+2E8 */ float x2E8;
    /*  fp+2EC */ float x2EC;
    /*  fp+2F0 */ BoneDynamicsDesc dynamic_bone_sets[Ft_Dynamics_NumMax];
    /*  fp+3E0 */ int dynamics_num;
    /*  fp+3E4 */ ftCmdScript x3E4_fighterCmdScript;
    /*  fp+3F8 */ UNK_T x3F8;
    /*  fp+3FC */ UNK_T x3FC;
    /*  fp+400 */ UNK_T x400;
    /*  fp+404 */ UNK_T x404;
    /*  fp+408 */ ftDeviceUnk2 x408;
    /*  fp+488 */ ftDeviceUnk2 x488;
    /*  fp+508 */ ftDeviceUnk2 x508;
    /*  fp+588 */ HSD_LObj* x588;
    /*  fp+58C */ s32 x58C;
    /*  fp+590 */ FigaTree* x590;
    /*  fp+594 */ union {
        struct {
            /* fp+594:0 */ u8 x594_b0 : 1;
            /* fp+594:1 */ u8 x594_b1 : 1;
            /* fp+594:2 */ u8 x594_b2 : 1;
            /* fp+594:3 */ u8 x594_b3 : 1;
            /* fp+594:4 */ u8 x594_b4 : 1;
            /* fp+594:5 */ u8 x594_b5 : 1;
            /* fp+594:6 */ u8 x594_b6 : 1;
            /* fp+594:7 */ u8 x594_b7 : 1;
            /* fp+596 */ struct {
                /* fp+596:0 */ u8 x0 : 7;
                /* fp+596:7 */ u16 x7 : 3;
            } x596_bits;
        };
        struct {
            u32 x594_pad : 10;
            u32 x594_bits : 13;
            u32 x594_pad2 : 3;
            u32 x597_bits : 6; // FighterKind of this fighter's x590 FigaTree
        };
        /* fp+594 */ s32 x594_s32;
    };
    /*  fp+598 */ s32 x598;
    /*  fp+59C */ struct Fighter_x59C_t* x59C;
    /*  fp+5A0 */ struct Fighter_x59C_t* x5A0;
    /*  fp+5A4 */ UNK_T x5A4;
    /*  fp+5A8 */ UNK_T x5A8;
    /*  fp+5AC */ u8 _5AC[0x5B8 - 0x5AC];
    /*  fp+5B8 */ s32 x5B8;
    /*  fp+5BC */ UNK_T x5BC;
    /*  fp+598 */ u8 filler_x598[0x5C8 - 0x5C0];
    /*  fp+5A0 */ void* x5C8;
    /*  fp+5CC */ u32 n_costume_tobjs;
    /*  fp+5D0 */ u16* x5D0;
    /*  fp+5D4 */ HSD_TObj* costume_tobjs[5];
    /*  fp+5E8 */ FighterBone* parts;
    /*  fp+5EC */ DObjList dobj_list;
    union {
        struct {
            s8 x0, x1;
        }
        /// @todo This is nonsense. Used by #ftParts_80074A74.
        x5F4_arr[2];
        struct {
            /*  fp+5F4 */ s8 x5F4;
            /*  fp+5F5 */ s8 x5F5;
            /*  fp+5F6 */ s8 x5F6;
            /*  fp+5F7 */ s8 x5F7;
        };
    };
    /*  fp+5F8 */ s8 x5F8;
    /*  fp+5FC */ u8 filler_x5FC[0x60C - 0x5F9];
    /*  fp+60C */ void* x60C;
    /*  fp+610 */ GXColor x610_color_rgba[2];
    /*  fp+618 */ u8 x618_player_id;
    /*  fp+619 */ u8 x619_costume_id;
    /*  fp+61A */ u8 x61A_controller_index;
    /*  fp+61B */ u8 team;
    /*  fp+61C */ u8 x61C;
    /*  fp+61D */ u8 x61D;
    /*  fp+61E */ u8 filler_x61E[0x620 - 0x61E];
    /*  fp+620 */ struct {
        /*  fp+620 */ Vec2 lstick;
        /*  fp+628 */ Vec2 lstick1;
        /*  fp+630 */ float x630;
        /*  fp+634 */ float x634;
        /*  fp+638 */ Vec2 cstick;
        /*  fp+640 */ Vec2 cstick1;
        /*  fp+648 */ float x648;
        /*  fp+64C */ float x64C;
        /*  fp+650 */ float x650;
        /*  fp+654 */ float x654;
        /*  fp+658 */ float x658;
        /*  fp+65C */ HSD_Pad held_inputs;
        /*  fp+660 */ s32 x660;
        /*  fp+664 */ s32 x664;
        /*  fp+668 */ HSD_Pad x668;
        /*  fp+66C */ s32 x66C;
    } input;
    /*  fp+670 */ u8 x670_timer_lstick_tilt_x;
    /*  fp+671 */ u8 x671_timer_lstick_tilt_y;
    /*  fp+672 */ u8 x672_input_timer_counter;
    /*  fp+673 */ u8 x673;
    /*  fp+674 */ u8 x674;
    /*  fp+674 */ u8 x675;
    /*  fp+676 */ u8 x676_x;
    /*  fp+677 */ u8 x677_y;
    /*  fp+678 */ u8 x678;
    /*  fp+679 */ u8 x679_x;
    /*  fp+67A */ u8 x67A_y;
    /*  fp+67B */ u8 x67B;
    /*  fp+67C */ u8 x67C;
    /*  fp+67D */ u8 x67D;
    /*  fp+67E */ u8 x67E;
    /*  fp+67F */ u8 x67F;
    /*  fp+680 */ u8 x680;
    /*  fp+681 */ u8 x681;
    /*  fp+682 */ u8 x682;
    /*  fp+683 */ u8 x683;
    /*  fp+684 */ u8 x684;
    /*  fp+685 */ u8 x685;
    /*  fp+686 */ u8 x686;
    /*  fp+687 */ u8 x687;
    /*  fp+688 */ u8 x688;
    /*  fp+689 */ u8 x689;
    /*  fp+68A */ u8 x68A;
    /*  fp+68B */ u8 x68B;
    /*  fp+68C */ Vec3 x68C_transNPos;
    /*  fp+698 */ Vec3 x698;
    /*  fp+6A4 */ Vec3 x6A4_transNOffset;
    /*  fp+6B0 */ Vec3 x6B0;
    /*  fp+6BC */ float lstick_angle;
    /*  fp+6C0 */ Vec3 x6C0;
    /*  fp+6CC */ Vec3 x6CC;
    /*  fp+6D8 */ Vec3 x6D8;
    /*  fp+6E4 */ Vec3 x6E4;
    /*  fp+6F0 */ CollData coll_data;
    /*  fp+88C */ s32 ecb_lock;
    /*  fp+890 */ CameraBox* x890_cameraBox;
    /*  fp+894 */ float cur_anim_frame;
    /*  fp+898 */ float x898_unk;
    /*  fp+89C */ float frame_speed_mul;
    /*  fp+8A0 */ float x8A0_unk;
    /*  fp+8A4 */ float x8A4_animBlendFrames;
    /*  fp+8A8 */ float x8A8_unk;
    /*  fp+8AC */ HSD_JObj* x8AC_animSkeleton;
    /*  fp+8AC */ u8 filler_x8AC[0x914 - 0x8B0];
    /*  fp+914 */ HitCapsule x914[4];
    /*  fp+DF4 */ HitCapsule xDF4[2];
    /* fp+1064 */ HitCapsule x1064_thrownHitbox;
    /* fp+119C */ u8 x119C_teamUnk;
    /* fp+119D */ u8 grabber_unk1;
    /* fp+119E */ u8 hurt_capsules_len;
    /* fp+119F */ u8 x119F;
    /* fp+11A0 */ HurtCapsule hurt_capsules[15];
    /* fp+1614 */ UNK_T x1614;
    /* fp+1618 */ u8 filler_x1618[0x166C - 0x1618];
    /* fp+166C */ u8 x166C;
    /* fp+1670 */ UNK_T x1670;
    /* fp+1674 */ u8 filler_x1674[0x1828 - 0x1674];
    /* fp+1828 */ enum_t x1828;
    /* fp+182C */ struct dmg {
        /* fp+182C */ float x182c_behavior;
        /* fp+1830 */ float x1830_percent;
        /* fp+1834 */ float x1834;
        /* fp+1838 */ float x1838_percentTemp;
        /* fp+183C */ int x183C_applied;
        /* fp+1840 */ int x1840;
        /* fp+1844 */ float facing_dir_1;
        /* fp+1848 */ int x1848_kb_angle;
        /* fp+184C */ int x184c_damaged_hurtbox;
        /* fp+1850 */ float kb_applied;
        /* fp+1854 */ Vec3 x1854_collpos;
        /* fp+1860 */ u32 x1860_element;
        /* fp+1864 */ int x1864;
        /* fp+1868 */ HSD_GObj* x1868_source;
        /* fp+186C */ int x186c;
        /* fp+1870 */ int x1870;
        /* fp+1874 */ int x1874;
        /* fp+1878 */ int x1878;
        /* fp+187C */ int x187c;
        /* fp+1880 */ int x1880;
        /* fp+1884 */ int x1884;
        /* fp+1888 */ int x1888;
        /* fp+188C */ int x188c;
        /* fp+1890 */ int x1890;
        /* fp+1894 */ int x1894;
        /* fp+1898 */ int x1898;
        /* fp+189C */ float x189C_unk_num_frames;
        /* fp+18A0 */ float x18a0;
        /// kb magnitude
        /* fp+18A4 */ float x18A4_knockbackMagnitude;
        /* fp+18A8 */ float x18A8;
        /// in frames
        /* fp+18AC */ int x18ac_time_since_hit;
        /* fp+18B0 */ float armor0;
        /* fp+18B4 */ float armor1;
        /* fp+18B8 */ float x18B8;
        /* fp+18BC */ float x18BC;
        /* fp+18C0 */ int x18C0;
        /// damage source ply number
        /* fp+18C4 */ int x18c4_source_ply;
        /* fp+18C8 */ int x18C8;
        /* fp+18CC */ int x18CC;
        /* fp+18D0 */ int x18D0;
        /* fp+18D4 */ UnkPlBonusBits x18d4;
        /* fp+18D8 */ ft_800898B4_t x18d8;
        /// Last Move Instance This Player Was Hit by
        /* fp+18EC */ u16 x18ec_instancehitby;
        /* fp+18F0 */ int x18F0;
        /* fp+18F4 */ int x18F4;
        /* fp+18F8 */ u8 x18F8;
        /* fp+18F9 */ u8 x18f9;
        /* fp+18FA */ u16 x18fa_model_shift_frames;
        /* fp+18FC */ u8 x18FC;
        /* fp+18FD */ u8 x18FD;
        /* fp+1900 */ float x1900;
        /* fp+1904 */ float x1904;
        /* fp+1908 */ enum_t x1908;
        /* fp+190C */ UNK_T x190C;
        /* fp+1910 */ int x1910;
        /* fp+1914 */ int x1914;
        /* fp+1918 */ int int_value;
        /* fp+191C */ float x191C;
        /* fp+1920 */ float facing_dir;
        /* fp+1924 */ int x1924;
        /* fp+1928 */ float x1928;
        /* fp+192C */ float x192c;
        /* fp+1930 */ Vec3 x1930;
        /* fp+193C */ Vec3 x193c;
        /* fp+1948 */ int x1948;
        /* fp+194C */ int x194C;
        /* fp+1950 */ bool x1950;
        /* fp+1954 */ float x1954;
        /* fp+1958 */ float x1958;
        /* fp+195C */ float x195c_hitlag_frames;
    } dmg;
    /* fp+1960 */ float x1960_vibrateMult;
    /* fp+1964 */ float x1964;
    /* fp+1968 */ u8 x1968_jumpsUsed;
    /* fp+1969 */ u8 x1969_walljumpUsed;
    /* fp+196C */ float hitlag_mul;
    /* fp+1970 */ enum_t unk_msid;
    /* fp+1974 */ Item_GObj* item_gobj;
    /* fp+1978 */ Item_GObj* x1978; // held item
    /* fp+197C */ HSD_GObj* x197C;
    /* fp+1980 */ HSD_GObj* x1980;
    /* fp+1984 */ Item_GObj* x1984_heldItemSpec;
    /* fp+1988 */ enum_t x1988;
    /* fp+198C */ s32 x198C;
    /* fp+1990 */ s32 x1990;
    /* fp+1994 */ bool x1994;
    /* fp+1998 */ float shield_health;
    /* fp+199C */ float lightshield_amount;
    /* fp+19A0 */ s32 x19A0_shieldDamageTaken;
    /* fp+19A4 */ int x19A4;
    /* fp+19A8 */ HSD_GObj* x19A8;
    /* fp+19AC */ float specialn_facing_dir;
    /* fp+19B0 */ enum_t x19B0;
    /* fp+19B4 */ float shield_unk0;
    /* fp+19B8 */ float shield_unk1;
    /* fp+19BC */ s32 x19BC_shieldDamageTaken3;
    /* fp+19C0 */ HitResult shield_hit;
    /* fp+19E4 */ HitResult reflect_hit;
    /* fp+1A08 */ HitResult absorb_hit;
    /* fp+1A2C */ struct {
        /* fp+1A2C */ float x1A2C_reflectHitDirection;
        /* fp+1A30 */ s32 x1A30_maxDamage;
        /* fp+1A34 */ float x1A34_damageMul;
        /* fp+1A38 */ float x1A38_speedMul;
        /// % damage over the maximum reflectable damage threshold
        /* fp+1A3C */ s32 x1A3C_damageOver;
    } ReflectAttr;
    /* fp+1A40 */ struct {
        /* fp+1A40 */ float x1A40_absorbHitDirection;
        /// unconfirmed?
        /* fp+1A44 */ s32 x1A44_damageTaken;
        /// unconfirmed?
        /* fp+1A48 */ s32 x1A48_hitsTaken;
    } AbsorbAttr;
    /* fp+1A4C */ float x1A4C;
    /* fp+1A50 */ s8 x1A50;
    /* fp+1A51 */ s8 x1A51;
    /* fp+1A52 */ u8 x1A52;
    /* fp+1A53 */ u8 x1A53;
    /* fp+1A54 */ s32 x1A54;
    /* fp+1A58 */ Fighter_GObj* victim_gobj;
    /* fp+1A5C */ Fighter_GObj* x1A5C;
    /* fp+1A60 */ Item_GObj* x1A60;
    /* fp+1A64 */ UNK_T x1A64;
    /* fp+1A68 */ u16 x1A68;
    /* fp+1A6A */ u16 x1A6A;
    /* fp+1A6C */ float x1A6C;
    /* fp+1A70 */ Vec3 x1A70;
    /* fp+1A7C */ Vec3 x1A7C;
    /* fp+x1A88 */ struct Fighter_x1A88_t x1A88;
    /* fp+2004 */ int x2004;
    /* fp+2008 */ s32 x2008;
    /* fp+200C */ s32 x200C;
    /* fp+2010 */ s32 x2010;
    /* fp+2014 */ s32 x2014;
    /* fp+2018 */ s32 x2018;
    /* fp+201C */ s32 x201C;
    /* fp+2020 */ s8 x2020;
    /* fp+2021 */ s8 x2021;
    /* fp+2022 */ s8 x2022;
    /* fp+2024 */ s32 x2024;
    /* fp+2028 */ s32 x2028;
    /* fp+202C */ s32 x202C;
    /* fp+2030 */ s32 x2030;
    /* fp+2034 */ s32 x2034;
    /* fp+2038 */ s32 x2038;
    /* fp+203C */ s32 x203C;
    /* fp+2040 */ void* x2040;
    /* fp+203C */ u8 filler_x203C[0x2064 - 0x2044];
    /* fp+2064 */ int x2064_ledgeCooldown;
    /* fp+2068 */ s32 x2068_attackID;
    /* fp+206C */ u16 x206C_attack_instance;
    /* fp+206E */ short x206E;
    /* fp+2070 */ union Struct2070 x2070;
    /* fp+2074 */ struct Struct2074 x2074;
    /* fp+208C */ s32 x208C;
    /* fp+2090 */ u16 x2090;
    /* fp+2092 */ u16 x2092;
    /// GObj pointer of combo victim?
    /* fp+2094 */ Fighter_GObj* x2094;
    /* fp+2098 */ u16 x2098;
    /* fp+209A */ u16 x209A;
    /* fp+209C */ s16 x209C;
    /* fp+20A0 */ HSD_JObj* x20A0_accessory;
    /* fp+20A4 */ UnkFlagStruct x20A4;
    /* fp+20A8 */ u32 x20A8;
    /* fp+20AC */ HSD_GObj* unk_gobj;
    /* fp+20B0 */ UNK_T x20B0;
    /* fp+20B4 */ UNK_T x20B4;
    /* fp+20B8 */ UNK_T x20B8;
    /* fp+20BC */ UNK_T x20BC;
    /* fp+20C0 */ UNK_T x20C0;
    /* fp+20C4 */ UNK_T x20C4;
    /* fp+20C8 */ UNK_T x20C8;
    /* fp+20CC */ UNK_T x20CC;
    /* fp+20D0 */ UNK_T x20D0;
    /* fp+20D4 */ UNK_T x20D4;
    /* fp+20D8 */ UNK_T x20D8;
    /* fp+20DC */ UNK_T x20DC;
    /* fp+20E0 */ UNK_T x20E0;
    /* fp+20E4 */ UNK_T x20E4;
    /* fp+20E8 */ UNK_T x20E8;
    /* fp+20EC */ UNK_T x20EC;
    /* fp+20F0 */ UNK_T x20F0;
    /* fp+20F4 */ UNK_T x20F4;
    /* fp+20F8 */ float x20F8;
    /* fp+20FC */ float x20FC;
    /* fp+2100 */ s8 x2100;
    /* fp+2101:0 */ u8 x2101_bits_0to6 : 7;
    /* fp+2101:7 */ u8 x2101_bits_8 : 1;
    /* fp+2102 */ s8 x2102;
    /* fp+2103 */ s8 x2103;
    /* fp+2104 */ s32 x2104;
    /* fp+2108 */ int capture_timer;
    /* fp+210C */ u8 wall_jump_input_timer;
    /* fp+210C */ u8 filler_x210C[3];
    /* fp+2110 */ float x2110_walljumpWallSide;
    /* fp+2114 */ SmashAttr smash_attrs;
    /* fp+213C */ s32 x213C;
    /* fp+2140 */ float x2140;
    /* fp+2144 */ int x2144;
    /* fp+2148 */ s32 x2148;
    /* fp+214C */ s32 x214C;
    /* fp+2150 */ s32 x2150;
    /* fp+2154 */ s32 x2154;
    /* fp+2158 */ s32 x2158;
    /* fp+215C */ s32 x215C;
    /* fp+2160 */ s32 x2160;
    /* fp+2164 */ int x2164;
    /* fp+2168 */ int x2168;
    /* fp+216C */ float unk_grab_val;
    /* fp+2170 */ float x2170;
    /* fp+2174 */ u8 filler_x2174[0x2180 - 0x2174];
    /* fp+2180 */ s32 x2180;
    /* fp+2184 */ HSD_JObj* x2184;
    /* fp+2188 */ S32Vec2 x2188;
    /// callback struct. Not all of them used by fighter.c.
    /* fp+2190 */ HSD_GObjEvent grab_cb;
    /* fp+2194 */ HSD_GObjEvent x2194;
    /* fp+2198 */ HSD_GObjInteraction grabbed_cb;
    /* fp+219C */ HSD_GObjEvent input_cb;
    /* fp+21A0 */ HSD_GObjEvent anim_cb;
    /* fp+21A4 */ HSD_GObjEvent phys_cb;
    /* fp+21A8 */ HSD_GObjEvent coll_cb;
    /* fp+21AC */ HSD_GObjEvent cam_cb;
    /* fp+21B0 */ HSD_GObjEvent accessory1_cb;
    /* fp+21B4 */ HSD_GObjEvent accessory2_cb;
    /* fp+21B8 */ HSD_GObjEvent accessory3_cb;
    /* fp+21BC */ HSD_GObjEvent accessory4_cb;
    /* fp+21C0 */ HSD_GObjEvent deal_dmg_cb;
    /* fp+21C4 */ HSD_GObjEvent shield_hit_cb;
    /* fp+21C8 */ HSD_GObjEvent reflect_hit_cb;
    /* fp+21CC */ HSD_GObjEvent x21CC;
    /* fp+21D0 */ HSD_GObjEvent hitlag_cb;
    /* fp+21D4 */ HSD_GObjEvent pre_hitlag_cb;
    /* fp+21D8 */ HSD_GObjEvent post_hitlag_cb;
    /* fp+21DC */ HSD_GObjEvent take_dmg_cb;
    /* fp+21E0 */ HSD_GObjEvent death1_cb;
    /// @remarks Used. Internally Dead_Proc as evidenced by 800F5430.
    /* fp+21E4 */ HSD_GObjEvent death2_cb;
    /* fp+21E8 */ HSD_GObjEvent death3_cb;
    /* fp+21EC */ HSD_GObjEvent x21EC;
    /* fp+21F0 */ HSD_GObjEvent x21F0;
    /* fp+21F4 */ HSD_GObjEvent x21F4;
    /* fp+21F8 */ HSD_GObjEvent x21F8;
    /* fp+21FC */ UnkFlagStruct x21FC_flag;
    /* fp+21FC */ u8 filler_x21FC[0x2200 - 0x21FD];
    /* fp+2200 */ u32 cmd_vars[4];
    /* fp+2210 */ union {
        u32 throw_flags;
        struct {
            u8 throw_flags_b0 : 1;
            u8 throw_flags_b1 : 1;
            u8 throw_flags_b2 : 1;
            u8 throw_flags_b3 : 1;
            u8 throw_flags_b4 : 1;
            u8 throw_flags_b5 : 1;
            u8 throw_flags_b6 : 1;
            u8 throw_flags_b7 : 1;
        };
    };
    /* fp+2214 */ float x2214;

    /* fp+2218:0 */ u8 allow_interrupt : 1;
    /* fp+2218:1 */ u8 x2218_b1 : 1;
    /* fp+2218:2 */ u8 x2218_b2 : 1;
    /* fp+2218:3 */ u8 x2218_b3 : 1;
    /* fp+2218:4 */ u8 x2218_b4 : 1;
    /* fp+2218:5 */ u8 x2218_b5 : 1;
    /* fp+2218:6 */ u8 x2218_b6 : 1;
    /* fp+2218:7 */ u8 x2218_b7 : 1;

    /* fp+2219:0 */ u8 x2219_b0 : 1;
    /* fp+2219:1 */ u8 x2219_b1 : 1;
    /* fp+2219:2 */ u8 x2219_b2 : 1;
    /* fp+2219:3 */ u8 x2219_b3 : 1;
    /* fp+2219:4 */ u8 x2219_b4 : 1;
    /* fp+2219:5 */ u8 x2219_b5 : 1;
    /* fp+2219:6 */ u8 x2219_b6 : 1;
    /* fp+2219:7 */ u8 x2219_b7 : 1;

    /* fp+221A:0 */ u8 x221A_b0 : 1;
    /* fp+221A:1 */ u8 x221A_b1 : 1;
    /* fp+221A:2 */ u8 x221A_b2 : 1;
    /* fp+221A:3 */ u8 x221A_b3 : 1;
    /* fp+221A:4 */ u8 x221A_b4 : 1;
    /* fp+221A:5 */ u8 x221A_b5 : 1;
    /* fp+221A:6 */ u8 x221A_b6 : 1;
    /* fp+221A:7 */ u8 x221A_b7 : 1;

    /* fp+221B */ struct {
        /* fp+221B:0 */ u8 x221B_b0 : 1;
        /* fp+221B:1 */ u8 x221B_b1 : 1;
        /* fp+221B:2 */ u8 x221B_b2 : 1;
        /* fp+221B:3 */ u8 x221B_b3 : 1;
        /* fp+221B:4 */ u8 x221B_b4 : 1;
        /* fp+221B:5 */ u8 x221B_b5 : 1;
        /* fp+221B:6 */ u8 x221B_b6 : 1;
        /* fp+221B:7 */ u8 x221B_b7 : 1;
    };

    /* fp+221C:0 */ u16 x221C_b0 : 1;
    /* fp+221C:1 */ u16 x221C_b1 : 1;
    /* fp+221C:2 */ u16 x221C_b2 : 1;
    /* fp+221C:3 */ u16 x221C_b3 : 1;
    /* fp+221C:4 */ u16 x221C_b4 : 1;
    /* fp+221C:5 */ u16 x221C_b5 : 1;
    /* fp+221C:6 */ u16 x221C_b6 : 1;
    /* fp+221C:7 */ u16 x221C_u16_y : 3;
    /* fp+221D:2 */ u16 x221D_b2 : 1;
    /* fp+221D:3 */ u16 x221D_b3 : 1;
    /* fp+221D:4 */ u16 x221D_b4 : 1;
    /* fp+221D:5 */ u16 x221D_b5 : 1;
    /* fp+221D:6 */ u16 x221D_b6 : 1;
    /* fp+221D:7 */ u16 x221D_b7 : 1;

    /* fp+221E:0 */ u8 x221E_b0 : 1;
    /* fp+221E:1 */ u8 x221E_b1 : 1;
    /* fp+221E:2 */ u8 x221E_b2 : 1;
    /* fp+221E:3 */ u8 x221E_b3 : 1;
    /* fp+221E:4 */ u8 x221E_b4 : 1;
    /* fp+221E:5 */ u8 x221E_b5 : 1;
    /* fp+221E:6 */ u8 x221E_b6 : 1;
    /* fp+221E:7 */ u8 x221E_b7 : 1;

    /* fp+221F:0 */ u8 x221F_b0 : 1;
    /* fp+221F:1 */ u8 x221F_b1 : 1;
    /* fp+221F:2 */ u8 x221F_b2 : 1;
    /* fp+221F:3 */ u8 x221F_b3 : 1;
    /* fp+221F:4 */ u8 x221F_b4 : 1;
    /* fp+221F:5 */ u8 x221F_b5 : 1;
    /* fp+221F:6 */ u8 x221F_b6 : 1;
    /* fp+221F:7 */ u8 x221F_b7 : 1;

    /* fp+2220 */ struct {
        /* fp+2220:0 */ u8 b0 : 3;
        /* fp+2220:3 */ u8 b3 : 1;
        /* fp+2220:4 */ u8 b4 : 1;
        /* fp+2220:5 */ u8 b5 : 1;
        /* fp+2220:6 */ u8 b6 : 1;
        /* fp+2220:7 */ u8 b7 : 1;
    } x2220_flag;

    /* fp+2221:0 */ u8 x2221_b0 : 1;
    /* fp+2221:1 */ u8 x2221_b1 : 1;
    /* fp+2221:2 */ u8 x2221_b2 : 1;
    /* fp+2221:3 */ u8 x2221_b3 : 1;
    /* fp+2221:4 */ u8 x2221_b4 : 1;
    /* fp+2221:5 */ u8 x2221_b5 : 1;
    /* fp+2221:6 */ u8 x2221_b6 : 1;
    /* fp+2221:7 */ u8 x2221_b7 : 1;

    /* fp+2222:0 */ u8 x2222_b0 : 1;
    /* fp+2222:1 */ u8 x2222_b1 : 1;
    /* fp+2222:2 */ u8 x2222_b2 : 1;
    /* fp+2222:3 */ u8 x2222_b3 : 1;
    /* fp+2222:4 */ u8 x2222_b4 : 1;
    /* fp+2222:5 */ u8 x2222_b5 : 1;
    /* fp+2222:6 */ u8 x2222_b6 : 1;
    /* fp+2222:7 */ u8 x2222_b7 : 1;

    /* fp+2223:0 */ u8 x2223_b0 : 1;
    /* fp+2223:1 */ u8 x2223_b1 : 1;
    /* fp+2223:2 */ u8 x2223_b2 : 1;
    /* fp+2223:3 */ u8 x2223_b3 : 1;
    /* fp+2223:4 */ u8 x2223_b4 : 1;
    /* fp+2223:5 */ u8 x2223_b5 : 1;
    /* fp+2223:6 */ u8 x2223_b6 : 1;
    /* fp+2223:7 */ u8 x2223_b7 : 1;

    /* fp+2224:0 */ u8 x2224_b0 : 1;
    /* fp+2224:1 */ u8 x2224_b1 : 1;
    /* fp+2224:2 */ u8 x2224_b2 : 1;
    /* fp+2224:3 */ u8 x2224_b3 : 1;
    /* fp+2224:4 */ u8 x2224_b4 : 1;
    /* fp+2224:5 */ u8 x2224_b5 : 1;
    /* fp+2224:6 */ u8 x2224_b6 : 1;
    /* fp+2224:7 */ u8 x2224_b7 : 1;

    /* fp+2225:0 */ u8 x2225_b0 : 1;
    /* fp+2225:1 */ u8 x2225_b1 : 1;
    /* fp+2225:2 */ u8 x2225_b2 : 1;
    /* fp+2225:3 */ u8 x2225_b3 : 1;
    /* fp+2225:4 */ u8 x2225_b4 : 1;
    /* fp+2225:5 */ u8 x2225_b5 : 1;
    /* fp+2225:6 */ u8 x2225_b6 : 1;
    /* fp+2225:7 */ u8 x2225_b7 : 1;

    /* fp+2226:0 */ u8 x2226_b0 : 1;
    /* fp+2226:1 */ u8 x2226_b1 : 1;
    /* fp+2226:2 */ u8 x2226_b2 : 1;
    /* fp+2226:3 */ u8 x2226_b3 : 1;
    /* fp+2226:4 */ u8 x2226_b4 : 1;
    /* fp+2226:5 */ u8 x2226_b5 : 1;
    /* fp+2226:6 */ u8 x2226_b6 : 1;
    /* fp+2226:7 */ u8 x2226_b7 : 1;

    /* fp+2227:0 */ u8 x2227_b0 : 1;
    /* fp+2227:1 */ u8 x2227_b1 : 1;
    /* fp+2227:2 */ u8 x2227_b2 : 1;
    /* fp+2227:3 */ u8 x2227_b3 : 1;
    /* fp+2227:4 */ u8 x2227_b4 : 1;
    /* fp+2227:5 */ u8 x2227_b5 : 1;
    /* fp+2227:6 */ u8 x2227_b6 : 1;
    /* fp+2227:7 */ u8 x2227_b7 : 1;

    /* fp+2228:0 */ u8 x2228_b0 : 1;
    /* fp+2228:1 */ u8 x2228_b1 : 1;
    /* fp+2228:2 */ u8 x2228_b2 : 1;
    /* fp+2228:3 */ u8 x2228_b3 : 2;
    /* fp+2228:5 */ u8 x2228_b5 : 1;
    /* fp+2228:6 */ u8 x2228_b6 : 1;
    /* fp+2228:7 */ u8 x2228_b7 : 1;

    /* fp+2229:0 */ u8 x2229_b0 : 1;
    /* fp+2229:1 */ u8 x2229_b1 : 1;
    /* fp+2229:2 */ u8 x2229_b2 : 1;
    /* fp+2229:3 */ u8 x2229_b3 : 1;
    /* fp+2229:4 */ u8 x2229_b4 : 1;
    /* fp+2229:5 */ u8 x2229_b5_no_normal_motion : 1;
    /* fp+2229:6 */ u8 x2229_b6 : 1;
    /* fp+2229:7 */ u8 x2229_b7 : 1;

    /* fp+222A */ UnkFlagStruct x222A_flag;

    /* fp+222C */ union Fighter_FighterVars {
        /* fp+222C */ struct ftCaptain_FighterVars ca, gn;
        /* fp+222C */ struct ftDonkey_FighterVars dk;
        /* fp+222C */ struct ftFox_FighterVars fx, fc;
        /* fp+222C */ struct ftGameWatch_FighterVars gw;
        /* fp+222C */ struct ftKb_FighterVars kb;
        /* fp+222C */ struct ftKoopa_FighterVars kp, gk;
        /* fp+222C */ struct ftLk_FighterVars lk;
        /* fp+222C */ struct ftLuigi_FighterVars lg;
        /* fp+222C */ struct ftMario_FighterVars mr;
        /* fp+222C */ struct ftMars_FighterVars ms;
        /* fp+222C */ struct ftMasterhand_FighterVars mh, ch;
        /* fp+222C */ struct ftMewtwo_FighterVars mt;
        /* fp+222C */ struct ftNess_FighterVars ns;
        /* fp+222C */ struct ftPeach_FighterVars pe;
        /* fp+222C */ struct ftPikachu_FighterVars pk, pc;
        /* fp+222C */ struct ftPopo_FighterVars pp, nn;
        /* fp+222C */ struct ftPurin_FighterVars pr;
        /* fp+222C */ struct ftSamus_FighterVars ss;
        /* fp+222C */ struct ftSandbag_FighterVars sb;
        /* fp+222C */ struct ftSeak_FighterVars sk;
        /* fp+222C */ struct ftYoshi_FighterVars ys;
        /* fp+222C */ struct ftZakoBoy_FighterVars bo, gl;
        /* fp+222C */ struct ftZelda_FighterVars zd;
    } fv;
    /* fp+2324 */ InternalStageId bury_stage_kind;
    /* fp+2328 */ u32 bury_timer_1;
    /* fp+232C */ u32 bury_timer_2;
    /* fp+2330 */ IntVec2 x2330;
    /* fp+2338 */ IntVec2 x2338;
    /// @at{2340} @sz{AC}
    /* fp+2340 */ union Fighter_MotionVars {
        /* fp+2340 */ u8 _[0x23EC - 0x2340];
        /* fp+2340 */ union ftCaptain_MotionVars ca, gn;
        /* fp+2340 */ union ftCommon_MotionVars co;
        /* fp+2340 */ union ftDonkey_MotionVars dk;
        /* fp+2340 */ union ftFox_MotionVars fx, fc;
        /* fp+2340 */ union ftGameWatch_MotionVars gw;
        /* fp+2340 */ union ftKb_MotionVars kb;
        /* fp+2340 */ union ftKoopa_MotionVars kp;
        /* fp+2340 */ union ftLk_MotionVars lk;
        /* fp+2340 */ union ftLuigi_MotionVars lg;
        /* fp+2340 */ union ftMario_MotionVars mr, dr;
        /* fp+2340 */ union ftMars_MotionVars ms, fe;
        /* fp+2340 */ union ftMasterHand_MotionVars mh, ch;
        /* fp+2340 */ union ftMewtwo_MotionVars mt;
        /* fp+2340 */ union ftNess_MotionVars ns;
        /* fp+2340 */ union ftPe_MotionVars pe;
        /* fp+2340 */ union ftPikachu_MotionVars pk, pc;
        /* fp+2340 */ union ftPp_MotionVars pp;
        /* fp+2340 */ union ftPurin_MotionVars pr;
        /* fp+2340 */ union ftSamus_MotionVars ss;
        /* fp+2340 */ union ftSeak_MotionVars sk;
        /* fp+2340 */ union ftYoshi_MotionVars ys;
        /* fp+2340 */ union ftZelda_MotionVars zd;
    } mv;
};
STATIC_ASSERT(sizeof(Fighter) == 0x23EC);

struct gmScriptEventDefault {
    u32 opcode : 6;
    u32 value1 : 26;
};

struct ftData_UnkCountStruct {
    void* data;
    int count;
};

struct UnkFloat6_Camera {
    Vec3 x0;
    Vec3 xC;
};

struct FtCmdState {
    float x0; // timer
    float x4; // frame
    union {
        char* x8; // script
        struct {
            union {
                s16 x0;
                struct {
                    u8 x0_b0 : 1;
                    u8 x0_b1 : 1;
                    u8 x0_b2 : 1;
                    u8 x0_b3 : 1;
                    u8 x0_b4 : 1;
                    u8 x0_b5 : 1;
                    u8 x0_b6 : 1;
                    u8 x0_b7 : 1;
                    u8 x1_b0 : 1;
                    u8 x1_b1 : 1;
                    u8 x1_b2 : 1;
                    u8 x1_b3 : 1;
                    u8 x1_b4 : 1;
                    u8 x1_b5 : 1;
                    u8 x1_b6 : 1;
                    u8 x1_b7 : 1;
                };
                struct {
                    u8 x0_b0_8 : 6;
                    u16 x0_b0_2 : 8;
                    u32 x0_b0_3 : 18;
                };
                struct {
                    u32 x0_6_26_1 : 6;
                    u32 x0_6_26_2 : 26;
                };
            };
            union {
                s16 x2;
                struct {
                    u8 x2_b0 : 1;
                    u8 x2_b1 : 1;
                    u8 x2_b2 : 1;
                    u8 x2_b3 : 1;
                    u8 x2_b4 : 1;
                    u8 x2_b5 : 1;
                    u8 x2_b6 : 1;
                    u8 x2_b7 : 1;
                    u8 x3_b0 : 1;
                    u8 x3_b1 : 1;
                    u8 x3_b2 : 1;
                    u8 x3_b3 : 1;
                    u8 x3_b4 : 1;
                    u8 x3_b5 : 1;
                    u8 x3_b6 : 1;
                    u8 x3_b7 : 1;
                };
            };
        }* x8_bits;
    };
    int xC;        // stack_depth
    void*(x10[5]); // stack
};

typedef struct ftData_UnkModelStruct {
    Fighter_ModelEvent model_events[FTKIND_MAX];
    HSD_JObj* (*getter[FTKIND_MAX])(HSD_GObj*);
} ftData_UnkModelStruct;

struct ftData_80085FD4_ret {
    /* +0 */ UNK_T x0;
    /* +4 */ UNK_T x4;
    /* +8 */ UNK_T x8;
    /* +C */ UNK_T xC;
    /* +10:0 */ u8 x10_b0 : 1;
    /* +10:1 */ u8 x10_b1 : 1;
    /* +14 */ u32 x14;
};

typedef struct ArticleDynamicBones {
    BoneDynamicsDesc array[Ft_Dynamics_NumMax];
} ArticleDynamicBones;

typedef struct ftDynamics {
    /// @todo Very similar to #ItemDynamics.
    struct {
        /*  +0 */ int dynamicsNum;
        /*  +4 */ ArticleDynamicBones* ftDynamicBones;
    };
    /*  +8 */ int x4;
    /*  +C */ void* x8;
    /* +10 */ FigaTree*** x10;
} ftDynamics;

typedef struct KirbyHatStruct {
    /*  +0 */ HSD_Joint* hat_joint;
    /*  +4 */ s32 joint_num;
    /*  +8 */ void* hat_vis_table;
    /*  +C */ ftDynamics* hat_dynamics[5];
} KirbyHatStruct;

typedef struct Kirby_Unk {
    /*  +0 */ HSD_Joint* x0;
    /*  +4 */ HSD_Joint** x4;
    /*  +8 */ UNK_T x8;
    /*  +C */ UNK_T xC;
    /* +10 */ ftDynamics* x10;
    /* +14 */ UNK_T x14;
    /* +18 */ ftDynamics* x18;
    /* +1C */ ftDynamics* x1C;
} Kirby_Unk;

struct ft_80459B88_t {
    /* +0 */ Kirby_Unk* x0;
    /* +4 */ KirbyHatStruct* hats[FTKIND_MAX];
};
STATIC_ASSERT(sizeof(struct ft_80459B88_t) == 0x88);

struct Fighter_804D653C_t {
    u32 unk;
    u8 unk4;
    u8 unk5;
};

#endif
