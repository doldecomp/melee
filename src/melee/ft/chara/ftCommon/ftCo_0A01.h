#ifndef GALE01_0A0148
#define GALE01_0A0148

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "gr/forward.h"

#include <common_structs.h>
#include <placeholder.h>

/* 09D4F0 */ UNK_RET ftCo_800A05F4(UNK_PARAMS);
/* 09D694 */ UNK_RET ftCo_800A0798(UNK_PARAMS);
/* 09DB88 */ void ftCo_800A0C8C(ftCo_Fighter* fp);
/* 09DCA0 */ void ftCo_800A0DA4(Fighter* fp);
/* 09DEAC */ bool ftCo_800A0FB0(Vec3* arg0, int* arg1, int arg2, int arg3,
                                int arg4, int arg5, int arg6, float arg7,
                                float arg8, float arg9, float arg10,
                                float arg11);
/* 09DF18 */ void ftCo_800A101C(Fighter*, s8, s8, s32);
/* 09E6E0 */ float ftCo_800A17E4(Fighter* fp);
/* 09E770 */ float ftCo_800A1874(Fighter* fp);
/* 09E800 */ float ftCo_800A1904(Fighter* fp);
/* 09E844 */ float ftCo_800A1948(Fighter* fp);
/* 09E888 */ HSD_Pad ftCo_800A198C(Fighter* fp);
/* 09E890 */ float ftCo_800A1994(Fighter* fp);
/* 09E920 */ float ftCo_800A1A24(Fighter* fp);
/* 09F06C */ bool ftCo_800A2170(ftCo_Fighter* fp0, ftCo_Fighter* fp1);
/* 09F7CC */ UNK_RET ftCo_800A28D0(UNK_PARAMS);
/* 09F894 */ UNK_RET ftCo_800A2998(UNK_PARAMS);
/* 09F96C */ UNK_RET ftCo_800A2A70(UNK_PARAMS);
/* 09FAD0 */ bool ftCo_800A2BD4(ftCo_Fighter* fp);
/* 09FB04 */ bool ftCo_800A2C08(ftCo_Fighter* fp);
/* 0A0030 */ bool ftCo_800A3134(ftCo_Fighter* fp);
/* 0A007C */ bool ftCo_IsGrabbing(ftCo_Fighter* fp);
/* 0A00FC */ bool ftCo_800A3200(ftCo_Fighter* fp);
/* 0A0740 */ UNK_RET ftCo_800A3844(UNK_PARAMS);
/* 0A193C */ UNK_RET ftCo_800A4A40(UNK_PARAMS);
/* 0A1AB4 */ float ftCo_800A1AB4(ftCo_Fighter* fp0, ftCo_Fighter* fp1);
/* 0A1BA8 */ bool ftCo_800A1BA8(ftCo_Fighter* fp);
/* 0A1C44 */ bool ftCo_800A1C44(ftCo_Fighter* fp);
/* 0A1CA8 */ bool ftCo_800A1CA8(ftCo_Fighter* fp);
/* 0A1D88 */ UNK_RET ftCo_800A4E8C(UNK_PARAMS);
/* 0A2040 */ bool ftCo_800A2040(Fighter* fp);
/* 0A2804 */ bool ftCo_800A5908(Fighter* fp);
/* 0A287C */ bool ftCo_800A5980(Fighter* fp);
/* 0A28BC */ bool ftCo_800A59C0(UNK_T);
/* 0A28E0 */ enum_t ftCo_800A59E4(ftCo_Fighter* fp);
/* 0A2924 */ bool ftCo_800A5A28(ftCo_Fighter* fp);
/* 0A41F4 */ bool ftCo_800B395C(ftCo_GObj* gobj, int);
/* 0A5A5C */ bool ftCo_800A5A5C(ftCo_Fighter*);
/* 0A5A90 */ bool ftCo_800A5A90(ftCo_Fighter* fp);
/* 0B07FC */ void ftCo_800B3900(Fighter_GObj* gobj);
/* 0B0858 */ UNK_RET ftCo_800B3958(UNK_PARAMS);

/// @todo Static functions belong in #ftCo_0A01.c
/* 09D044 */ static UNK_RET ftCo_800A0148(UNK_PARAMS);
/* 09D06C */ static UNK_RET ftCo_800AC7D4(UNK_PARAMS);
/* 09D280 */ static UNK_RET ftCo_800A0384(UNK_PARAMS);
/* 09D3DC */ static UNK_RET ftCo_800ACB44(UNK_PARAMS);
/* 09D404 */ static UNK_RET ftCo_800A0508(UNK_PARAMS);
/* 09D5F4 */ static UNK_RET ftCo_800ACD5C(UNK_PARAMS);
/* 09D7EC */ static UNK_RET ftCo_800A08F0(UNK_PARAMS);
/* 09D9F0 */ static UNK_RET ftCo_800A0AF4(UNK_PARAMS);
/* 09DBAC */ static UNK_RET ftCo_800A0CB0(UNK_PARAMS);
/* 09DCC4 */ static UNK_RET ftCo_800AD42C(UNK_PARAMS);
/* 09DDE4 */ static UNK_RET ftCo_800AD54C(UNK_PARAMS);
/* 09DDFC */ static UNK_RET ftCo_800A0F00(UNK_PARAMS);
/* 09E094 */ static UNK_RET ftCo_800AD7FC(UNK_PARAMS);
/* 09E4C0 */ static UNK_RET ftCo_800ADC28(UNK_PARAMS);
/* 09E6E0 */ static UNK_RET ftCo_800ADE48(UNK_PARAMS);
/* 09EBC0 */ static void ftCo_800A1CC4(UNK_T, UNK_T, UNK_T);
/* 09EE38 */ static void ftCo_800A1F3C(ftCo_Fighter* fp, float arg1,
                                       float arg2, float arg3);
/* 09EE94 */ static UNK_RET ftCo_800A1F98(UNK_PARAMS);
/* 09EF9C */ static UNK_RET ftCo_800A20A0(UNK_PARAMS);
/* 09F044 */ static UNK_RET ftCo_800AE7AC(UNK_PARAMS);
/* 09F0F8 */ static bool ftCo_800A21FC(ftCo_Fighter* fp);
/* 09F198 */ static UNK_RET ftCo_800A229C(UNK_PARAMS);
/* 09F324 */ static UNK_RET ftCo_800AEA8C(UNK_PARAMS);
/* 09F588 */ static UNK_RET ftCo_800AECF0(UNK_PARAMS);
/* 09F614 */ static UNK_RET ftCo_800A2718(UNK_PARAMS);
/* 09F850 */ static UNK_RET ftCo_800AEFB8(UNK_PARAMS);
/* 09FB28 */ static UNK_RET ftCo_800AF290(UNK_PARAMS);
/* 09FB7C */ static UNK_RET ftCo_800A2C80(UNK_PARAMS);
/* 0A0024 */ static UNK_RET ftCo_800AF78C(UNK_PARAMS);
/* 0A0130 */ static UNK_RET ftCo_800A3234(UNK_PARAMS);
/* 0A0394 */ static UNK_RET ftCo_800A3498(UNK_PARAMS);
/* 0A0450 */ static UNK_RET ftCo_800A3554(UNK_PARAMS);
/* 0A04D8 */ static UNK_RET ftCo_800AFC40(UNK_PARAMS);
/* 0A060C */ static UNK_RET ftCo_800A3710(UNK_PARAMS);
/* 0A06D4 */ static UNK_RET ftCo_800AFE3C(UNK_PARAMS);
/* 0A0804 */ static UNK_RET ftCo_800A3908(UNK_PARAMS);
/* 0A0990 */ static UNK_RET ftCo_800B00F8(UNK_PARAMS);
/* 0A0D74 */ static UNK_RET ftCo_800B04DC(UNK_PARAMS);
/* 0A0F34 */ static UNK_RET ftCo_800A4038(UNK_PARAMS);
/* 0A0FF8 */ static UNK_RET ftCo_800B0760(UNK_PARAMS);
/* 0A11B0 */ static UNK_RET ftCo_800B0918(UNK_PARAMS);
/* 0A138C */ static void ftCo_800B0AF4(ftCo_Fighter* fp);
/* 0A1540 */ static UNK_RET ftCo_800B0CA8(UNK_PARAMS);
/* 0A1664 */ static UNK_RET ftCo_800A4768(UNK_PARAMS);
/* 0A1730 */ static UNK_RET ftCo_800B0E98(UNK_PARAMS);
/* 0A18B0 */ static void ftCo_800A49B4(ftCo_Fighter* fp);
/* 0A18B4 */ static UNK_RET ftCo_800B101C(UNK_PARAMS);
/* 0A1AE8 */ static UNK_RET ftCo_800A4BEC(UNK_PARAMS);
/* 0A1B04 */ static UNK_RET ftCo_800B126C(UNK_PARAMS);
/* 0A1B38 */ static bool ftCo_800A1B38(enum_t);
/* 0A1D10 */ static UNK_RET ftCo_800B1478(UNK_PARAMS);
/* 0A1FD0 */ static UNK_RET ftCo_800A50D4(UNK_PARAMS);
/* 0A2068 */ static UNK_RET ftCo_800B17D0(UNK_PARAMS);
/* 0A2190 */ static UNK_RET ftCo_800A5294(UNK_PARAMS);
/* 0A22D8 */ static UNK_RET ftCo_800A53DC(UNK_PARAMS);
/* 0A2350 */ static UNK_RET ftCo_800B1AB8(UNK_PARAMS);
/* 0A2638 */ static UNK_RET ftCo_800B1DA0(UNK_PARAMS);
/* 0A2788 */ static UNK_RET ftCo_800B1EF0(UNK_PARAMS);
/* 0A2798 */ static ftCo_Fighter* ftCo_800A589C(ftCo_Fighter* fp);
/* 0A2840 */ static bool ftCo_800A5944(ftCo_Fighter* fp);
/* 0A2A60 */ static UNK_RET ftCo_800B21C8(UNK_PARAMS);
/* 0A2D50 */ static UNK_RET ftCo_800B24B8(UNK_PARAMS);
/* 0A3028 */ static void ftCo_800B2790(ftCo_Fighter* fp);
/* 0A3C48 */ static void ftCo_800B33B0(ftCo_Fighter* fp);
/* 0A5ACC */ static UNK_RET ftCo_800A5ACC(UNK_PARAMS);
/* 0A5CE0 */ static UNK_RET ftCo_800A5CE0(UNK_PARAMS);
/* 0A5F4C */ static UNK_RET ftCo_800A5F4C(UNK_PARAMS);
/* 0A61D8 */ static UNK_RET ftCo_800A61D8(UNK_PARAMS);
/* 0A648C */ static UNK_RET ftCo_800A648C(UNK_PARAMS);
/* 0A6700 */ static UNK_RET ftCo_800A6700(UNK_PARAMS);
/* 0A6A98 */ static UNK_RET ftCo_800A6A98(UNK_PARAMS);
/* 0A6D2C */ static UNK_RET ftCo_800A6D2C(UNK_PARAMS);
/* 0A6FC4 */ static UNK_RET ftCo_800A6FC4(UNK_PARAMS);
/* 0A75DC */ static UNK_RET ftCo_800A75DC(UNK_PARAMS);
/* 0A7AAC */ static UNK_RET ftCo_800A7AAC(UNK_PARAMS);
/* 0A80E4 */ static UNK_RET ftCo_800A80E4(UNK_PARAMS);
/* 0A8210 */ static UNK_RET ftCo_800A8210(UNK_PARAMS);
/* 0A866C */ static UNK_RET ftCo_800A866C(UNK_PARAMS);
/* 0A8940 */ static UNK_RET ftCo_800A8940(UNK_PARAMS);
/* 0A8DE4 */ static UNK_RET ftCo_800A8DE4(UNK_PARAMS);
/* 0A8EB0 */ static UNK_RET ftCo_800A8EB0(UNK_PARAMS);
/* 0A92CC */ static UNK_RET ftCo_800A92CC(UNK_PARAMS);
/* 0A949C */ static UNK_RET ftCo_800A949C(UNK_PARAMS);
/* 0A963C */ static void ftCo_800A963C(ftCo_Fighter* fp);
/* 0A96B8 */ static UNK_RET ftCo_800A96B8(UNK_PARAMS);
/* 0A9904 */ static UNK_RET ftCo_800A9904(UNK_PARAMS);
/* 0A9CB4 */ static UNK_RET ftCo_800A9CB4(UNK_PARAMS);
/* 0AA320 */ static UNK_RET ftCo_800AA320(UNK_PARAMS);
/* 0AA42C */ static UNK_RET ftCo_800AA42C(UNK_PARAMS);
/* 0AA844 */ static UNK_RET ftCo_800AA844(UNK_PARAMS);
/* 0AABC8 */ static UNK_RET ftCo_800AABC8(UNK_PARAMS);
/* 0AACD0 */ static UNK_RET ftCo_800AACD0(UNK_PARAMS);
/* 0AAF48 */ static UNK_RET ftCo_800AAF48(UNK_PARAMS);
/* 0AB224 */ static UNK_RET ftCo_800AB224(UNK_PARAMS);
/* 0ABA34 */ static UNK_RET ftCo_800ABA34(UNK_PARAMS);
/* 0ABBA8 */ static UNK_RET ftCo_800ABBA8(UNK_PARAMS);
/* 0AC30C */ static UNK_RET ftCo_800AC30C(UNK_PARAMS);
/* 0AC434 */ static UNK_RET ftCo_800AC434(UNK_PARAMS);
/* 0AC5A0 */ static UNK_RET ftCo_800AC5A0(UNK_PARAMS);
/* 0B2AFC */ static void ftCo_800B2AFC(ftCo_Fighter* fp);

#endif
