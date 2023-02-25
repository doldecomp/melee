#ifndef _gmmain_lib_h_
#define _gmmain_lib_h_

#include <common_structs.h>
#include <Runtime/platform.h>

struct gmm_x1CB0 {
    u8 padding_x0[0x16 - 0x0];
    /* 0x1CC6 0x16 */ u8 saved_language;
    u8 padding_x16[0x20 - 0x16 - 1];
};

typedef union _UnkFlagStruct2 {
    struct {
        u16 b0 : 1;
        u16 b1 : 1;
        u16 b2 : 1;
        u16 b3 : 1;
        u16 b4 : 1;
        u16 b5 : 1;
        u16 b6 : 1;
        u16 b789 : 3;
        u16 b10_to_12 : 3;
        u16 b13_to_15 : 3;
    } bits;
    u16 flags;
} UnkFlagStruct2;

struct gmm_x1F2C {
    u8 padding_x0[0x78];
    s8 x78;
    s8 x79;
    UnkFlagStruct x7A;
    s8 x7B;
    UnkFlagStruct2 x7C;
    s16 x7E;
    s8 x80;
    s8 x81;
    s8 x82;
    s8 x83;
    s32 x84;
    s32 x88;
    s32 x8C;
    s32 x90;
    s32 x94;
    s32 x98;
    s32 x9C;
    s16 xA0;
    s16 xA2;
    s32 xA4;
    s32 xA8;
};

struct gmm_x2FF8_inner {
    u8 padding[0x1A2];
    s8 x1A2;
    u8 padding_x1A2;
};

struct gmm_x2FF8 {
    struct gmm_x2FF8_inner inner[19];
};

typedef struct _GameRules {
    /*0x00*/ u8 unk_x0;
    /*0x01*/ u8 unk_x1;
    /*0x02*/ u8 mode;
    /*0x03*/ u8 time_limit;
    /*0x04*/ u8 stock_count;
    /*0x05*/ u8 handicap;
    /*0x06*/ u8 damage_ratio;
    /*0x07*/ u8 unk_x7;
    /*0x08*/ u8 stock_time_limit;
    /*0x09*/ u8 friendly_fire;
    /*0x0A*/ u8 pause;
    /*0x0B*/ u8 score_display;
    /*0x0C*/ u8 unk_xc;
    /*0x0D*/ u8 unk_xd[3];
    /*0x10*/ u8 unk_x10;
    /*0x11*/ u8 unk_x11[7];
} GameRules;

struct gmm_x1868 {
    /* 0x1868 */ s32 x1868;
    u8 padding_x1868[0x1A18 - 0x1868 - 4];
    /* 0x1A18 */ s32 x1A18;
    /* 0x1A1C */ s32 x1A1C;
    /* 0x1A20 */ s32 x1A20;
    /* 0x1A24 */ s32 x1A24;
    /* 0x1A28 */ s32 x1A28;
    /* 0x1A2C */ s32 x1A2C;
    /* 0x1A30 */ s32 x1A30;
    /* 0x1A34 */ s32 x1A34;
    /* 0x1A38 */ s32 x1A38;
    /* 0x1A3C */ s32 x1A3C;
    /* 0x1A40 */ s32 x1A40;
    /* 0x1A44 */ s32 x1A44;
    /* 0x1A48 */ s32 x1A48;
    /* 0x1A4C */ s32 x1A4C;
    /* 0x1A50 */ s32 x1A50;
    /* 0x1A54 */ s32 x1A54;
    /* 0x1A58 */ s32 x1A58;
    /* 0x1A5C */ s32 x1A5C;
    /* 0x1A60 */ s32 x1A60;
    /* 0x1A64 */ s32 x1A64;
    /* 0x1A68 */ s64 x1A68;
    /* 0x1A70 */ s32 x1A70[4];
    u8 padding_x1A70[0x1B3C - 0x1A70 - 16];
    /* 0x1B3C */ u8 x1B3C;
    /* 0x1B40 */ u32 x1B40[3];
    /* 0x1B4C */ u32 x1B4C[3];
    /* 0x1B58 */ u32 x1B58[3];
    u8 padding_x1B58[0x1B80 - 0x1B58 - 3 * 4];
    /* 0x1B80 */ u32 x1B80[4];
    u8 padding_x1B80[0x1C88 - 0x1B80 - 4 * 4];
    /* 0x1C88 */ u32 x1C88[3];
    u8 padding_x1C88[0x1CB0 - 0x1C88 - 3 * 4];
    /* 0x1CB0 */ struct gmm_x1CB0 x1CB0;
    /* 0x1CD0 */ s16 x1CD0;
    /* 0x1CD2 */ s16 x1CD2;
    /* 0x1CD4 */ s32 x1CD4;
    u8 padding_x1CD4[0x1F2C - 0x1CD4 - 4];
    /* 0x1F2C */ struct gmm_x1F2C x1F2C[25];
    /* 0x2FF8 */ struct gmm_x2FF8 x2FF8[2];
    //  u8 padding_x2FF8[0x7000 - 0x2FF8 - 0x1A4*19*2];
};

extern struct gmm_x0 {
    /* 0x0000 */ u8 language;
    /* 0x0001 */ u8 x1;
    u8 padding_x1[0x39 - 0x1 - 1];
    /* 0x0039 */ u8 x39[11];
    /* 0x0044 */ s32 x44;
    u8 padding_x44[0x6C - 0x44 - 4];
    /* 0x006C */ s32 x6C[4];
    u8 padding_x6C[0x51C - 0x6C - 4 * 4];
    /* 0x051C */ s32 x51C;
    /* 0x0520 */ s16 x520;
    /* 0x0522 */ s16 x522;
    /* 0x0524 */ s16 x524;
    /* 0x0526 */ s16 x526;
    /* 0x0528 */ s32 x528;
    /* 0x052C */ s32 x52C;
    u8 padding_x52C[0x57C - 0x52C - 4];
    /* 0x057C */ s32 x57C;
    u8 padding_x57C[0x586 - 0x57C - 4];
    /* 0x0586 */ s16 x586;
    /* 0x0588 */ s8 x588[4];
    u8 padding_x588[0x1850 - 0x588 - 4];
    /* 0x1850 */ GameRules x1850;
    struct gmm_x1868 thing;
}* lbl_804D3EE0;

struct gmm_retval_ED98 {
    u8 padding[0xC];
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
};

struct gmm_retval_EDBC {
    s32 x0;
    s32 x4;
    s32 x8;
    u8 padding[0x4C - 0x8 - 4];
    s32 x4C[4];
    u8 padding_x4C[0xB0 - 0x4C - 4 * 4];
    s32 xB0[4];
};

struct gmm_retval_EDB0 {
    s32 x0;
    s32 x4;
};

struct gmm_retval_EDBC* func_8015EDBC(void);
struct gmm_x1CB0* func_8015CC58(void);
struct gmm_retval_ED98* func_8015ED98(void);
struct gmm_retval_EDB0* func_8015EDB0(void);

s8* func_8015CE44(s32, s32);

/// @todo static
void func_8015D888(u32);

void func_8015D8FC(u32);
s32 func_8015D94C(u32);
void func_8015FCC0(void);
void func_8015FBA4(void);
GameRules* func_8015CC34(void);

void* func_8015CD5C(void);
void* func_8015CD68(void);
void* func_8015CC40(void);
void* func_8015CD74(void);
void* func_8015CD80(void);
void* func_8015CD8C(void);
void* func_8015CD98(void);
void* func_8015CDA4(void);
void* func_8015CDB0(void);
void* func_8015CDBC(void);
void* func_8015CDC8(void);
void* func_8015CDD4(void);
void* func_8015CDE0(void);
void* func_8015CC4C(void);
void func_8015CDEC(void);
void func_8015CEB4(s32 arg0);
s32 func_8015CEFC(s32 arg0);
s32 func_8015CF5C(s32 arg0);
void func_8015CF70(s32 arg0, s32 arg1);
void func_8015CF84(void);
s32 func_8015CF94(void);
s32 func_8015CFAC(void);
s8* func_8015CFB4(u8 arg0);
s32 func_8015CFCC(u8 arg0);
void func_8015D00C(u8 arg0);
s32* func_8015D06C(u8 arg0);
s32* func_8015D084(s32 arg0);
void* func_8015CC64(s32 arg0);
s32* func_8015D0C0(u8 arg0);
s32 func_8015D0D8(u8 arg0);
s32 func_8015D0F4(u8 arg0);
void func_8015D134(u8 arg0);
s8* func_8015D194(u8 arg0);
void* func_8015CC78(void);
s32 func_8015D1AC(u8 arg0);
void func_8015D1C8(u8 arg0, s32 arg1);
s32* func_8015D1E8(u8 arg0);
s32 func_8015D200(u8 arg0);
s32 func_8015D21C(u8 arg0);
void func_8015D25C(u8 arg0);
s8* func_8015D2BC(u8 arg0);
s32 func_8015D2D4(u8 arg0);
void* func_8015CC84(void);
void func_8015D2F0(u8 arg0, s32 arg1);
s32* func_8015D310(u8 arg0);
s32 func_8015D328(u8 arg0);
s32 func_8015D344(u8 arg0);
void func_8015D384(u8 arg0);
s8* func_8015D3E4(u8 arg0);
s32 func_8015D3FC(u8 arg0);
void func_8015D418(u8 arg0, s32 arg1);
void* func_8015CC90(void);
s32* func_8015D438(u8 arg0);
s32* func_8015D450(s32 arg0);
s32 func_8015D48C(u8 arg0);
s32 func_8015D4A8(u8 arg0);
void* func_8015CC9C(s32 arg0);
void func_8015D4E8(u8 arg0, s32 arg1);
s32 lbl_8015D508(void);
s32 func_8015D5DC(void);
s32 func_8015D640(void);
s32* func_8015D6A4(u8 arg0);
s32 func_8015D6BC(u8 arg0);
void func_8015D6D8(u8 arg0, s32 arg1);
s32* func_8015D6F8(u8 arg0);
void* func_8015CCE4(void);
s32 func_8015D710(u8 arg0);
void func_8015D72C(u8 arg0, s32 arg1);
s16* func_8015D74C(u8 arg0);
s32 func_8015D764(u8 arg0);
void func_8015D780(u8 arg0);
s16* func_8015D7A4(u8 arg0);
s32* func_8015D7BC(u8 arg0);
s32* func_8015D7D4(u8 arg0);
void* func_8015CCF0(void);
s16* func_8015D7EC(u8 arg0);
void* func_8015D804(s32 arg0);
s32 func_8015D818(u32 arg0);
void func_8015D8B0(u32 arg0);
s32 func_8015D8D8(u32 arg0);
void* func_8015CCFC(void);
void func_8015D924(u32 arg0);
s32* func_8015D970(s32 arg0);
s32 func_8015D984(s32 arg0);
void* func_8015CD08(void);
s32 func_8015DA1C(u32 arg0);
void* func_8015CD14(void);
void func_8015DA68(u32 arg0);
void func_8015DAB4(u32 arg0);
s32 func_8015DADC(u32 arg0);
u8 func_8015DB00(void);
void func_8015DB0C(u8 arg0);
void func_8015DB18(void);
void func_8015DB2C(u8 arg0, s32 arg2);
void* func_8015CD20(void);
u8 func_8015DB6C(u8 arg0);
void func_8015DB80(void);
void* func_8015CD2C(void);
void* func_8015CD38(void);
void* func_8015CD44(void);
void* func_8015CD50(void);

#endif
