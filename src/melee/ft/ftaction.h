#ifndef GALE01_071028
#define GALE01_071028

#include "ft/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include <placeholder.h>
#include <dolphin/mtx/types.h>

struct FtCmdState {
    float x0;      // timer
    float x4;      // frame
    char* x8;      // script
    int xC;        // stack_depth
    void*(x10[5]); // stack
};

#ifdef M2CTX
extern u8 ftAction_803C0870[];

struct _m2c_stack_ftAction_80072CD8 {
    /* 0x00 */ char pad_0[0x14];
    /* 0x14 */ Vec3 vec0;
    /* 0x20 */ Vec3 vec1;
    /* 0x2C */ IntVec3 ivec0;
    /* 0x38 */ M2C_UNK sp38;      /* inferred */
    /* 0x3C */ M2C_UNK sp3C;      /* inferred */
    /* 0x40 */ int* sp40;         /* inferred */
    /* 0x44 */ char pad_44[0x18]; /* maybe part of sp40[7]? */
    /* 0x5C */ IntVec3 ivec1;     /* inferred */
    /* 0x68 */ char pad_68[0x10];
}; /* size = 0x78 */

struct _m2c_stack_ftAction_80072E4C {
    /* 0x00 */ char pad_0[0x14];
    /* 0x14 */ Vec3 vec0;
    /* 0x20 */ Vec3 vec1;
    /* 0x2C */ IntVec3 ivec0;
    /* 0x38 */ M2C_UNK sp38;      /* inferred */
    /* 0x3C */ M2C_UNK sp3C;      /* inferred */
    /* 0x40 */ int* sp40;         /* inferred */
    /* 0x44 */ char pad_44[0x18]; /* maybe part of sp40[7]? */
    /* 0x5C */ IntVec3 ivec1;
    /* 0x68 */ char pad_68[0x10];
}; /* size = 0x78 */

struct _m2c_stack_ftAction_80072320 {
    /* 0x00 */ char pad_0[8];
    /* 0x08 */ int sp8; /* inferred */
    /* 0x0C */ int spC; /* inferred */
    /* 0x10 */ char pad_10[0x30];
}; /* size = 0x40 */
#endif

/* 071028 */ void ftAction_80071028(Fighter_GObj* gobj, FtCmdState* cmd);
/* 0711DC */ void ftAction_800711DC(Fighter_GObj* gobj, FtCmdState* cmd);
/* 07121C */ /* static */ void ftAction_8007121C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0715EC */ /* static */ void ftAction_800715EC(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07162C */ /* static */ void ftAction_8007162C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07168C */ /* static */ void ftAction_8007168C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07169C */ /* static */ void ftAction_8007169C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0716F8 */ /* static */ void ftAction_800716F8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071708 */ /* static */ void ftAction_80071708(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071774 */ /* static */ void ftAction_80071774(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071784 */ /* static */ void ftAction_80071784(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0717C8 */ /* static */ void ftAction_800717C8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0717D8 */ /* static */ void ftAction_800717D8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071810 */ /* static */ void ftAction_80071810(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071820 */ /* static */ void ftAction_80071820(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0718A4 */ /* static */ void ftAction_800718A4(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071908 */ /* static */ void ftAction_80071908(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07192C */ /* static */ void ftAction_8007192C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071950 */ /* static */ void ftAction_80071950(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071974 */ /* static */ void ftAction_80071974(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071998 */ /* static */ void ftAction_80071998(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071A14 */ /* static */ void ftAction_80071A14(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071A58 */ /* static */ void ftAction_80071A58(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071A9C */ /* static */ void ftAction_80071A9C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071AE8 */ /* static */ void ftAction_80071AE8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071B28 */ /* static */ void ftAction_80071B28(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071B50 */ /* static */ void ftAction_80071B50(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071BE0 */ /* static */ UNK_RET lbl_80071BE0(UNK_PARAMS);
/* 071BE8 */ /* static */ UNK_RET lbl_80071BE8(UNK_PARAMS);
/* 071BF0 */ /* static */ UNK_RET lbl_80071BF0(UNK_PARAMS);
/* 071BF8 */ /* static */ UNK_RET lbl_80071BF8(UNK_PARAMS);
/* 071C00 */ /* static */ UNK_RET lbl_80071C00(UNK_PARAMS);
/* 071C08 */ /* static */ UNK_RET lbl_80071C08(UNK_PARAMS);
/* 071C10 */ /* static */ UNK_RET lbl_80071C10(UNK_PARAMS);
/* 071CA4 */ /* static */ void ftAction_80071CA4(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071CCC */ /* static */ void ftAction_80071CCC(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071D30 */ /* static */ void ftAction_80071D30(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071D40 */ /* static */ void ftAction_80071D40(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071D94 */ /* static */ void ftAction_80071D94(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071DCC */ /* static */ void ftAction_80071DCC(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071E04 */ /* static */ void ftAction_80071E04(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071F0C */ /* static */ void ftAction_80071F0C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071F34 */ /* static */ void ftAction_80071F34(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071F78 */ /* static */ void ftAction_80071F78(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071FA0 */ /* static */ void ftAction_80071FA0(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 071FC8 */ /* static */ void ftAction_80071FC8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072210 */ /* static */ UNK_RET lbl_80072210(UNK_PARAMS);
/* 072228 */ /* static */ UNK_RET lbl_80072228(UNK_PARAMS);
/* 072240 */ /* static */ UNK_RET lbl_80072240(UNK_PARAMS);
/* 072258 */ /* static */ UNK_RET lbl_80072258(UNK_PARAMS);
/* 072270 */ /* static */ UNK_RET lbl_80072270(UNK_PARAMS);
/* 072288 */ /* static */ UNK_RET lbl_80072288(UNK_PARAMS);
/* 0722A0 */ /* static */ UNK_RET lbl_800722A0(UNK_PARAMS);
/* 0722C8 */ /* static */ void ftAction_800722C8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072320 */ /* static */ void ftAction_80072320(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072408 */ /* static */ UNK_RET lbl_80072408(UNK_PARAMS);
/* 07243C */ /* static */ UNK_RET lbl_8007243C(UNK_PARAMS);
/* 072480 */ /* static */ UNK_RET lbl_80072480(UNK_PARAMS);
/* 072530 */ /* static */ UNK_RET lbl_80072530(UNK_PARAMS);
/* 072574 */ /* static */ UNK_RET lbl_80072574(UNK_PARAMS);
/* 0725B8 */ /* static */ UNK_RET lbl_800725B8(UNK_PARAMS);
/* 0725FC */ /* static */ UNK_RET lbl_800725FC(UNK_PARAMS);
/* 0726C0 */ /* static */ void ftAction_800726C0(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0726F4 */ /* static */ void ftAction_800726F4(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0727C8 */ /* static */ void ftAction_800727C8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07283C */ /* static */ void ftAction_8007283C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072894 */ /* static */ void ftAction_80072894(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0728F8 */ /* static */ void ftAction_800728F8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07296C */ /* static */ void ftAction_8007296C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07297C */ /* static */ void ftAction_8007297C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0729C4 */ /* static */ void ftAction_800729C4(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0729D4 */ /* static */ void ftAction_800729D4(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072A4C */ /* static */ void ftAction_80072A4C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072A5C */ /* static */ void ftAction_80072A5C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072AAC */ /* static */ void ftAction_80072AAC(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072ABC */ /* static */ void ftAction_80072ABC(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072B04 */ /* static */ void ftAction_80072B04(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072B14 */ /* static */ void ftAction_80072B14(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072B3C */ /* static */ void ftAction_80072B3C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072B84 */ /* static */ void ftAction_80072B84(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072B94 */ /* static */ void ftAction_80072B94(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072BE4 */ /* static */ void ftAction_80072BE4(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072BF4 */ /* static */ void ftAction_80072BF4(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072C5C */ /* static */ void ftAction_80072C5C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072C6C */ /* static */ void ftAction_80072C6C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072CB0 */ /* static */ void ftAction_80072CB0(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072CD8 */ /* static */ void ftAction_80072CD8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072E24 */ /* static */ void ftAction_80072E24(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072E4C */ /* static */ void ftAction_80072E4C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 072FE0 */ /* static */ void ftAction_80072FE0(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 073008 */ /* static */ void ftAction_80073008(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07309C */ /* static */ void ftAction_8007309C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 0730B8 */ /* static */ void ftAction_800730B8(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 073108 */ /* static */ void ftAction_80073108(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 073118 */ /* static */ void ftAction_80073118(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 07320C */ /* static */ void ftAction_8007320C(Fighter_GObj* gobj,
                                                 FtCmdState* cmd);
/* 073240 */ /* static */ void ftAction_80073240(Fighter_GObj* gobj);
/* 073354 */ /* static */ void ftAction_80073354(Fighter_GObj* gobj);
/* 07349C */ /* static */ void ftAction_8007349C(Fighter_GObj* gobj);

#endif
