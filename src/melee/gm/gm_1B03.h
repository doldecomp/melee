#ifndef MELEE_GM_1B03_H
#define MELEE_GM_1B03_H

#include <placeholder.h>
#include <sysdolphin/baselib/forward.h>
#include <melee/mn/forward.h>
#include <melee/gm/forward.h>

struct gm_801B0FF8_arg0_x10_t {
    /* +0 */ s8 x0;
    /* +1 */ s8 x1;
    /* +2 */ s8 x2;
};

struct gm_801B0FF8_arg0_t {
    /* +0 */ char pad_0[0x10];
    /* +10 */ struct gm_801B0FF8_arg0_x10_t* x10;
};

struct gm_8049E548_t {
    /* 0x00 */ char pad_0[8];
    /* 0x08 */ s8 unk_8;
    /* 0x09 */ u8 unk_9;
    /* 0x0A */ s8 unk_A;
    /* 0x0B */ char pad_B[1];
    /* 0x0C */ u16 unk_C;
    /* 0x0E */ s8 unk_E; /* inferred */
    /* 0x0F */ char pad_F[1];
}; /* size = 0x10 */
STATIC_ASSERT(sizeof(struct gm_8049E548_t) == 0x10);

/* 1B0348 */ void gm_801B0348(StartMeleeData*); /// Character tints?
/* 1B0474 */ void gm_801B0474(StartMeleeData*, MatchEnd*);
/* 1B05F4 */ void gm_801B05F4(PlayerInitData*, int);
/* 1B0620 */ void gm_801B0620(PlayerInitData*, u8 c_kind, u8 color, u8 stocks, u8);
/* 1B0664 */ void gm_801B0664(PlayerInitData*, u8 c_kind, u8 color, u8 stocks, u8);
/* 1B06B0 */ void gm_801B06B0(CSSData*, u8, s8, s8, s8, u8, u8, u8);
/* 1B0730 */ void gm_801B0730(CSSData*, s8*, s8*, u8*, s8*, u8*);
/* 1B07B4 */ void gm_801B07B4(CSSData*, s8, s8, s8, u8, u8, u8);
/* 1B07E8 */ void gm_801B07E8(CSSData*, s8*, s8*, s8*, s8*, u8*);
/* 1B087C */ void gm_801B087C(MinorScene*);
/* 1B089C */ void gm_801B089C(MinorScene*);
/* 1B099C */ void gm_801B099C(MinorScene*);
/* 1B09C0 */ void gm_801B09C0(MinorScene*);
/* 1B09F8 */ int fn_801B09F8(int);
/* 1B0A34 */ void gm_801B0A34(MinorScene*);
/* 1B0A8C */ int fn_801B0A8C(int);
/* 1B0AC8 */ void gm_801B0AC8(MinorScene*);
/* 1B0B00 */ void gm_801B0B00(MinorScene*);
/* 1B0B24 */ void gm_801B0B24(MinorScene*);
/* 1B0B48 */ void gm_801B0B48(MinorScene*);
/* 1B0B8C */ void gm_801B0B8C(MinorScene*);
/* 1B0BF0 */ void gm_801B0BF0(MinorScene*);
/* 1B0C18 */ void gm_801B0C18(MinorScene*);
/* 1B0C50 */ void gm_801B0C50(MinorScene*);
/* 1B0C74 */ void gm_801B0C74(MinorScene*);
/* 1B0CF0 */ void gm_801B0CF0(MinorScene*);
/* 1B0DD0 */ void gm_801B0DD0(MinorScene*);
/* 1B0F1C */ void gm_801B0F1C(MinorScene*);
/* 1B0F60 */ void gm_801B0F60(MinorScene*);
/* 1B0F90 */ void gm_801B0F90(MinorScene*);
/* 1B0FB8 */ void gm_801B0FB8(MinorScene*);
/* 1B0FF8 */ void gm_801B0FF8(MinorScene*);
/* 1B138C */ void gm_801B138C(MinorScene*);
/* 1B13B8 */ void gm_801B13B8(MinorScene*);
/* 1B14A0 */ void gm_801B14A0(MinorScene*);
/* 1B14DC */ void gm_801B14DC(MinorScene*);
/* 1B1514 */ void gm_801B1514(MinorScene*);
/* 1B154C */ void gm_801B154C(MinorScene*);
/* 1B1588 */ void gm_801B1588(MinorScene*);
/* 1B15C8 */ void gm_801B15C8(MinorScene*);
/* 1B1648 */ void gm_801B1648(MinorScene*);
/* 1B1688 */ void gm_801B1688(MinorScene*);
/* 1B16A8 */ void gm_801B16A8(MinorScene*);
/* 1B16C8 */ void gm_801B16C8(MinorScene*);
/* 1B1724 */ void gm_801B1724(MinorScene*);
/* 1B174C */ void gm_801B174C(MinorScene*);
/* 1B1788 */ void gm_801B1788(MinorScene*);
/* 1B1810 */ void gm_801B1810(MinorScene*);
/* 1B1834 */ void gm_801B1834(MinorScene*);
/* 1B18D4 */ void gm_801B18D4(MinorScene*);
/* 1B1A2C */ void gm_801B1A2C(MinorScene*);
/* 1B1A84 */ void gm_801B1A84(MinorScene*);
/* 1B1AD4 */ void gm_801B1AD4(MinorScene*);
/* 1B1B74 */ void gm_801B1B74(MinorScene*);
/* 1B1C24 */ void gm_801B1C24(MinorScene*);
/* 1B1EB8 */ void gm_801B1EB8(MinorScene*);
/* 1B1EEC */ void gm_801B1EEC(MinorScene*);
/* 1B1F6C */ void fn_801B1F6C(int);
/* 1B1F70 */ void gm_801B1F70(MinorScene*);
/* 1B2204 */ void gm_801B2204(MinorScene*);
/* 1B2298 */ void gm_801B2298_OnInit(void);
/* 1B23C4 */ void gm_801B23C4_OnLoad(void);
/* 1B23F0 */ UNK_T gm_801B23F0(void);
/* 1B24B4 */ void gm_801B24B4(MinorScene*);
/* 1B2510 */ void gm_801B2510(MinorScene*);
/* 1B254C */ void gm_801B254C(MinorScene*);
/* 1B25D4 */ void gm_801B25D4(MinorScene*);
/* 1B26AC */ void gm_801B26AC(MinorScene*);
/* 1B2704 */ void gm_801B2704(MinorScene*);
/* 1B2790 */ void gm_801B2790(MinorScene*);
/* 1B2AF8 */ void gm_801B2AF8(MinorScene*);
/* 1B2B7C */ void gm_801B2B7C_OnInit(void);
/* 1B2BA4 */ UNK_RET gm_801B2BA4(UNK_PARAMS);
/* 1B2D54 */ UNK_RET gm_801B2D54(UNK_PARAMS);
/* 1B2F78 */ void gm_801B2F78_OnLoad(void);
/* 1B34B8 */ void gm_801B34B8_OnInit(void);
/* 1B3500 */ void gm_801B3500(MinorScene*);
/* 1B3A34 */ void gm_801B3A34(MinorScene*);
/* 1B3B40 */ void gm_801B3B40(MinorScene*);
/* 1B3D44 */ void gm_801B3D44(MinorScene*);
/* 1B3D84 */ void gm_801B3D84(MinorScene*);
/* 1B3DD8 */ void gm_801B3DD8(MinorScene*);
/* 1B3E44 */ void gm_801B3E44(MinorScene*);
/* 1B3F18 */ void gm_801B3F18(MinorScene*);
/* 1B3F40 */ UNK_RET gm_801B3F40(UNK_PARAMS);
/* 1B4064 */ UNK_RET gm_801B4064(UNK_PARAMS);
/* 1B4170 */ UNK_RET gm_801B4170(UNK_PARAMS);
/* 1B4254 */ UNK_RET gm_801B4254(UNK_PARAMS);
/* 1B4294 */ UNK_RET gm_801B4294(UNK_PARAMS);
/* 1B42E8 */ UNK_RET gm_801B42E8(UNK_PARAMS);
/* 1B4350 */ UNK_RET gm_801B4350(UNK_PARAMS);
/* 1B4408 */ UNK_RET gm_801B4408(UNK_PARAMS);
/* 1B4430 */ UNK_RET gm_801B4430(UNK_PARAMS);
/* 1B44A0 */ UNK_RET gm_801B44A0(UNK_PARAMS);
/* 1B45A4 */ UNK_RET gm_801B45A4(UNK_PARAMS);
/* 1B461C */ UNK_RET gm_801B461C(UNK_PARAMS);
/* 1B4684 */ UNK_RET gm_801B4684(UNK_PARAMS);
/* 1B4768 */ UNK_RET gm_801B4768(UNK_PARAMS);
/* 1B47FC */ UNK_RET gm_801B47FC(UNK_PARAMS);
/* 1B4860 */ UNK_RET gm_801B4860(UNK_PARAMS);
/* 1B4974 */ UNK_RET gm_801B4974(UNK_PARAMS);
/* 1B4B28 */ UNK_RET gm_801B4B28(UNK_PARAMS);
/* 1B4C5C */ UNK_RET gm_801B4C5C(UNK_PARAMS);
/* 1B4D34 */ UNK_RET gm_801B4D34(UNK_PARAMS);
/* 1B4DAC */ UNK_RET gm_801B4DAC(UNK_PARAMS);
/* 1B4E58 */ UNK_RET gm_801B4E58(UNK_PARAMS);
/* 1B4EB8 */ UNK_RET gm_801B4EB8(UNK_PARAMS);
/* 1B4F44 */ UNK_RET gm_801B4F44(UNK_PARAMS);
/* 1B4FCC */ UNK_RET gm_801B4FCC(UNK_PARAMS);
/* 1B5078 */ UNK_RET gm_801B5078(UNK_PARAMS);
/* 1B50C4 */ UNK_RET gm_801B50C4(UNK_PARAMS);
/* 1B518C */ UNK_RET gm_801B518C(UNK_PARAMS);
/* 1B51CC */ void gm_801B51CC_OnInit(void);
/* 1B5214 */ void gm_801B5214_OnLoad(void);
/* 1B5324 */ UNK_RET gm_801B5324(UNK_PARAMS);
/* 1B5624 */ UNK_RET gm_801B5624(UNK_PARAMS);
/* 1B59AC */ UNK_RET gm_801B59AC(UNK_PARAMS);
/* 1B5AA8 */ void fn_801B5AA8(int);
/* 1B5ACC */ UNK_RET gm_801B5ACC(UNK_PARAMS);
/* 1B5E7C */ UNK_RET gm_801B5E7C(UNK_PARAMS);
/* 1B5EB4 */ UNK_RET gm_801B5EB4(UNK_PARAMS);
/* 1B5EE4 */ UNK_RET gm_801B5EE4(UNK_PARAMS);
/* 1B5F50 */ UNK_RET gm_801B5F50(UNK_PARAMS);
/* 1B5FB4 */ UNK_RET gm_801B5FB4(UNK_PARAMS);
/* 1B607C */ void gm_801B607C(void);
/* 1B60A4 */ void gm_801B60A4_OnLoad(void);
/* 1B62D8 */ void gm_801B62D8_OnInit(void);
/* 1B6320 */ UNK_T gm_801B6320(void);
/* 1B632C */ UNK_RET gm_801B632C(UNK_PARAMS);
/* 1B63C4 */ UNK_RET gm_801B63C4(UNK_PARAMS);
/* 1B6428 */ UNK_RET gm_801B6428(UNK_PARAMS);
/* 1B65D4 */ UNK_RET gm_801B65D4(UNK_PARAMS);
/* 1B67E8 */ void gm_801B67E8_OnInit(void);
/* 1B6808 */ void gm_801B6808_OnLoad(void);
/* 1B6834 */ UNK_RET gm_801B6834(UNK_PARAMS);
/* 1B685C */ UNK_RET gm_801B685C(UNK_PARAMS);
/* 1B688C */ UNK_RET gm_801B688C(UNK_PARAMS);
/* 1B69C0 */ void gm_801B69C0(StartMeleeData*);
/* 1B6AD8 */ UNK_RET gm_801B6AD8(UNK_PARAMS);
/* 1B6B70 */ UNK_RET gm_801B6B70(UNK_PARAMS);
/* 1B6BE8 */ UNK_RET gm_801B6BE8(UNK_PARAMS);
/* 1B6F44 */ UNK_RET gm_801B6F44(UNK_PARAMS);
/* 1B7044 */ UNK_RET gm_801B7044(UNK_PARAMS);
/* 1B70DC */ UNK_RET gm_801B70DC(UNK_PARAMS);
/* 1B7154 */ UNK_RET gm_801B7154(UNK_PARAMS);
/* 1B74F0 */ UNK_RET gm_801B74F0(UNK_PARAMS);
/* 1B75F0 */ UNK_RET gm_801B75F0(UNK_PARAMS);
/* 1B7688 */ UNK_RET gm_801B7688(UNK_PARAMS);
/* 1B7700 */ UNK_RET gm_801B7700(UNK_PARAMS);
/* 1B7AA0 */ UNK_RET gm_801B7AA0(UNK_PARAMS);
/* 1B7B74 */ UNK_RET gm_801B7B74(UNK_PARAMS);
/* 1B7C0C */ UNK_RET gm_801B7C0C(UNK_PARAMS);
/* 1B7C84 */ UNK_RET gm_801B7C84(UNK_PARAMS);
/* 1B8024 */ UNK_RET gm_801B8024(UNK_PARAMS);
/* 1B8110 */ UNK_RET gm_801B8110(UNK_PARAMS);
/* 1B81A8 */ UNK_RET gm_801B81A8(UNK_PARAMS);
/* 1B8220 */ UNK_RET gm_801B8220(UNK_PARAMS);
/* 1B8580 */ UNK_RET gm_801B8580(UNK_PARAMS);
/* 1B863C */ UNK_RET gm_801B863C(UNK_PARAMS);
/* 1B86D4 */ UNK_RET gm_801B86D4(UNK_PARAMS);
/* 1B874C */ UNK_RET gm_801B874C(UNK_PARAMS);
/* 1B8AF8 */ UNK_RET gm_801B8AF8(UNK_PARAMS);

#endif
