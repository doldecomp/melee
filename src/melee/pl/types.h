#ifndef MELEE_PL_TYPES_H
#define MELEE_PL_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include <melee/pl/forward.h>

#include <melee/ft/types.h>

struct plAllocInfo {
    FighterKind internal_id;
    u8 slot;
    s8 x5;
    struct {
        u8 b0 : 1;
        u8 has_transformation : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
};

/// @todo Probably the same struct as #plAllocInfo, figure out how to make them
///       work as one.
struct plAllocInfo2 {
    FighterKind internal_id;
    u8 slot;
    enum_t unk8;
    struct {
        u8 b0 : 1;
        u8 has_transformation : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
};

struct plAttackStats {
    /*   +0 */ u32 total;
    /*   +4 */ u32 by_attack_counts[StatsAttack_Count];
    /* +194 */ u32 thrown_item_count;
    /* +198 */ u32 aerials_count;
    /* +19C */ u32 specials_count;
    /* +1A0 */ u32 x1A0_count; ///< increments on most attacks, but not down special?
    /* +1A4 */ u32 x1A4_count; ///< increments on down specials?
    /* +1A8 */ u32 x1A8;
};

struct plActionStats {
    /*   +0 */ struct plAttackStats attacks;
    /* +1AC */ struct plAttackStats hits;
    /// @todo i dont think this is a union but in-game, x358 follows
    // the pattern for plAttackStats... but pl_800386D8 directly references
    // x3E8. it doesnt really make sense that it would split the enum at
    // StatsAttack_KbSpecialNMt
    /* +358 */ union {
        struct plAttackStats x358_hits;
        struct {
            u32 total;
            u32 by_attack_lo[35];
            u32 by_attack_hi[65];
            u32 thrown_item_count;
            u32 aerials_count;
            u32 specials_count;
            u32 x4F8_count;
            u32 x4FC_count;
            u32 x500;
        };
    };
    /* +504 */ u8 x504[StatsAttack_Count]; ///< related to UnkPlBonusBits
    /* +568 */ u32 x568;
    /* +56C */ u32 x56C;
    /* +570 */ u32 x570;
    /* +574 */ u32 x574;
    /* +578 */ u32 x578;
    /* +57C */ u32 x57C;
    /* +580 */ u32 x580;
    /* +584 */ u32 x584;
    /* +588 */ u32 x588;
    /* +58C */ u32 x58C;
    /* +590 */ u32 x590;
    /* +594 */ u32 x594;
    /* +598 */ u32 x598[8];
    /* +5B8 */ u8 x5B8[4];
    /* +5BC */ u8 x5BC_b0 : 1;
    /* +5BC */ u8 x5BC_b1 : 1;
    /* +5BC */ u8 x5BC_b2 : 1;
    /* +5BC */ u8 x5BC_b3 : 1;
};

struct StaleMoveTable {
    /*   +0 */ int current_index;
    /*   +4 */ struct {
        u16 move_id;
        u16 attack_instance;
    } StaleMoves[10];
    /*  +2C */ plActionStats total_attack_count_struct;
    /* +5EC */ struct pl_x5EC_t {
        u8 x0; ///< player slot
        f32 x4;
        u32 x8;
        u32 xC;
        struct {
            float x0; ///< combo damage?
            s16 x4;
            u16 x6;
            s16 x8;
            int xC;
            s16 x10;
            u16 x12_b0 : 1;
        } x10[6];
    } x5EC;
    /* +674 */ u32 x674[39];
    /* +710 */ int x710[39];
    /* +7AC */ int x7AC[39];
    /* +848 */ int x848[30];
    /* +8C0 */ struct pl_x8C0_t {
        int x0;
        struct {
            u16 x0;
            u8 x2;
            u8 x3_b0 : 1;
        } x4[5];
    } x8C0;
    /* +8D8 */ struct pl_x8D8_t {
        int x0;
        struct {
            u32 x0;
            u8 x4_b0 : 1;
            u8 x4_b1 : 1;
        } x4[5];
    } x8D8;
    /* +904 */ unsigned int x904[215];
    /* +C60 */ float xC60;
    /* +C64 */ float xC64;
    /* +C68 */ int xC68;
    /* +C6C */ float xC6C;
    /* +C70 */ float xC70;
    /* +C74 */ float xC74;
    /* +C78 */ float xC78[6];
    /* +C90 */ unsigned int xC90;
    /* +C94 */ int xC94;
    /* +C98 */ float xC98;
    /* +C9C */ float xC9C;
    /* +CA0 */ float xCA0;
    /* +CA4 */ int xCA4;
    /* +CA8 */ unsigned int xCA8;
    /* +CAC */ unsigned int xCAC;
    /* +CB0 */ int xCB0;
    /* +CB4 */ int xCB4;
    /* +CB8 */ int xCB8;
    /* +CBC */ UnkPlBonusBits xCBC;
    /* +CC0 */ ft_800898B4_t xCC0;
    /* +CD4 */ u16 xCD4;
    /* +CD8 */ int xCD8;
    /* +CDC */ float xCDC;
    /* +CE0 */ float xCE0;
    /* +CE4 */ u32 xCE4;
    /* +CE8 */ u32 xCE8;
    /* +CEC */ int xCEC;
    /* +CF0 */ int xCF0;
};
STATIC_ASSERT(sizeof(struct StaleMoveTable) == 0xCF4);

struct pl_StaleMoveTableExt_t {
    /*   +0 */ StaleMoveTable x0_staleMoveTable;
    /* +CF4 */ int xCF4;
    /* +CF8 */ float xCF8;
    /* +CFC */ int xCFC;
    /* +D00 */ int xD00;
    /* +D04 */ unsigned int xD04;
    /* +D08 */ unsigned int xD08;
    /* +D0C */ unsigned int xD0C;
    /* +D10 */ int xD10;
    /* +D14 */ u32 xD14;
    /* +D18 */ unsigned int xD18;
    /* +D1C */ u32 xD1C;
    /* +D20 */ u32 xD20;
    /* +D24 */ u32 xD24;
    /* +D28 */ u32 xD28;
    /* +D2C */ u32 xD2C;
    /* +D30 */ u32 xD30;
    /* +D34 */ int xD34;
    /* +D38 */ u32 xD38;
    /* +D3C */ u32 xD3C;
    /* +D40 */ unsigned int xD40;
    /* +D44 */ unsigned int xD44;
    /* +D48 */ unsigned int xD48;
    /* +D4C */ unsigned int xD4C;
    /* +D50 */ unsigned int xD50;
    /* +D54 */ unsigned int xD54;
    /* +D58 */ unsigned int xD58;
    /* +D5C */ unsigned int xD5C;
    /* +D60 */ unsigned long xD60;
    /* +D64 */ int xD64;
    /* +D68 */ int xD68;
    /* +D6C */ int xD6C;
    /* +D70 */ int xD70;
    /* +D74 */ float xD74;
    /* +D78 */ float xD78;
    /* +D7C */ float xD7C;
    /* +D80 */ float xD80;
    /* +D84 */ float xD84;
    /* +D88 */ float xD88;
    /* +D8C */ float xD8C;
    /* +D90 */ int xD90;
    /* +D94 */ float xD94;
    /* +D98 */ int xD98;
    /* +D9C */ int xD9C;
    /* +DA0 */ int xDA0;
    /* +DA4 */ int xDA4;
    /* +DA8 */ int xDA8;
    /* +DAC */ int xDAC;
    /* +DB0 */ int xDB0;
    /* +DB4 */ int xDB4;
    /* +DB8 */ int xDB8;
    /* +DBC */ int xDBC;
    /* +DC0 */ float xDC0;
    /* +DC4 */ int xDC4;
    /* +DC8 */ int xDC8;
    /* +DCC */ int xDCC;
    /* +DD0 */ union {
        u8 xDD0_value;
        struct {
            u8 bit0 : 1;
            u8 bit1 : 1;
            u8 bit2 : 1;
            u8 bit3 : 1;
            u8 bit4 : 1;
            u8 bit5 : 1;
            u8 bit6 : 1;
            u8 bit7 : 1;
        };
    } xDD0;
    /* +DD1 */ union {
        u8 xDD1_value;
        struct {
            u8 bit0 : 1;
            u8 bit1 : 1;
            u8 bit2 : 1;
            u8 bit3 : 1;
            u8 bit4 : 1;
            u8 bit5 : 1;
            u8 bit6 : 1;
            u8 bit7 : 1;
        };
    } xDD1;
}; // UNKNOWN SIZE

struct pl_800386E8_arg0_t {
    /* 0x000 */ char pad_0[0x190];
    /* 0x190 */ int unk_190;         /* inferred */
    /* 0x194 */ char pad_194[0x418]; /* maybe part of unk_190[0x107]? */
    /* 0x5AC */ int unk_5AC;         /* inferred */
    /* 0x5B0 */ int unk_5B0;         /* inferred */
}; /* size = 0x5B4 */

struct pl_804D6470_t {
    /*   +0 */ u8 x0[0x4];
    /*   +4 */ int x4;
    /*   +8 */ u8 x8[0x10];
    /*  +18 */ unsigned int x18;
    /*  +1C */ unsigned int x1C;
    /*  +20 */ u8 x20[0x24 - 0x20];
    /*  +24 */ int x24;
    /*  +28 */ float x28;
    /*  +2C */ unsigned int x2C;
    /*  +30 */ unsigned int x30;
    /*  +34 */ float x34;
    /*  +38 */ float x38;
    /*  +3C */ u32 x3C;
    /*  +40 */ u32 x40;
    /*  +44 */ float x44;
    /*  +48 */ float x48;
    /*  +4C */ float x4C;
    /*  +50 */ u8 x50[0x58 - 0x50];
    /*  +58 */ float x58;
    /*  +5C */ float x5C;
    /*  +60 */ float x60;
    /*  +64 */ float x64;
    /*  +68 */ float x68;
    /*  +6C */ float x6C;
    /*  +70 */ unsigned int x70;
    /*  +74 */ unsigned int x74;
    /*  +78 */ float x78;
    /*  +7C */ unsigned int x7C;
    /*  +80 */ unsigned int x80;
    /*  +84 */ float x84;
    /*  +88 */ unsigned int x88;
    /*  +8C */ unsigned int x8C;
    /*  +90 */ unsigned int x90;
    /*  +94 */ unsigned int x94;
    /*  +98 */ float x98;
    /*  +9C */ float x9C;
    /*  +A0 */ float xA0;
    /*  +A4 */ unsigned int xA4;
    /*  +A8 */ unsigned int xA8;
    /*  +AC */ unsigned int xAC;
    /*  +B0 */ unsigned int xB0;
    /*  +B4 */ unsigned int xB4;
    /*  +B8 */ unsigned int xB8;
    /*  +BC */ unsigned int xBC;
    /*  +C0 */ u8 xC0[0xC4 - 0xC0];
    /*  +C4 */ unsigned int xC4;
    /*  +C8 */ unsigned int xC8;
    /*  +CC */ float xCC;
    /*  +D0 */ float xD0;
    /*  +D4 */ float xD4;
    /*  +D8 */ float xD8;
    /*  +DC */ u32 xDC;
    /*  +E0 */ unsigned int xE0;
    /*  +E4 */ UNK_T xE4;
    /*  +E8 */ float xE8;
    /*  +EC */ int xEC;
    /*  +E8 */ u8 xF0[0xF4 - 0xF0];
    /*  +F4 */ float xF4;
    /*  +F8 */ float xF8;
    /*  +FC */ float xFC;
    /* +100 */ float x100;
    /* +104 */ float x104;
    /* +108 */ int x108;
    /* +10C */ float x10C;
    /* +110 */ int x110;
    /* +114 */ float x114;
    /* +118 */ unsigned int x118;
    /* +11C */ float x11C;
    /* +120 */ int x120;
    /* +124 */ unsigned int x124;
    /* +128 */ int x128;
    /* +12C */ int x12C;
    /* +130 */ unsigned int x130;
    /* +134 */ unsigned int x134;
    /* +138 */ u8 x138[0x144 - 0x138];
    /* +144 */ unsigned int x144;
    /* +148 */ unsigned int x148;
    /* +14C */ unsigned int x14C;
    /* +150 */ unsigned int x150;
    /* +154 */ unsigned int x154;
    /* +158 */ unsigned int x158;
    /* +15C */ unsigned int x15C;
    /* +160 */ u8 x160[0x164 - 0x160];
    /* +164 */ unsigned int x164;
    /* +168 */ unsigned int x168;
    /* +16C */ unsigned int x16C;
    /* +170 */ unsigned int x170;
    /* +174 */ unsigned int x174;
    /* +178 */ unsigned int x178;
    /* +17C */ int x17C;
    /* +180 */ float x180;
}; // UNKNOWN SIZE

#endif
