#include "soundtest.h"

#include "gm/forward.h"

#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "if/types.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbcardnew.h"
#include "lb/lblanguage.h"
#include "lb/lbsnap.h"
#include "ty/toy.h"
#include "ty/tylist.h"

#include <printf.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <baselib/sislib.h>
#include <baselib/sobjlib.h>
#include <MSL/stdio.h>
#include <MSL/string.h>

// .data
/* 3F9FD0 */ static int un_803F9FD0;
/* 3F9FDC */ static float un_803F9FDC;
/* 3FA070 */ static int un_803FA070;
/* 3FA090 */ static int un_803FA090;
/* 3FA09C */ static float un_803FA09C;
/* 3FA0B0 */ static int un_803FA0B0;
/* 3FA128 */ static struct {
    u8 _pad0[0x220];
    u16 x220;
    u8 _pad222[0x2];
    u8 x224;
    u8 x225;
    u8 x226;
    u8 x227;
} un_803FA128;
/* 3FA258 */ static struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    u8 _pad14[0x14];
    int x28;
    int x2C;
    int x30;
    u8 _pad34[0xC4];
    int xF8;
    int xFC;
    int x100;
    int x104;
    int x108;
    int x10C;
    int x110;
    int x114;
    int x118;
    int x11C;
    int x120;
    int x124;
    int x128;
    int x12C;
    int x130;
    u8 _pad134[0x4];
    void* x138;
    u8 _pad13C[0x8];
    u8 x144[0x44];
    s32 x188;
} un_803FA258;
/* 3FA348 */ static u16 un_803FA348;
/* 3FA34C */ static u8 un_803FA34C;
/* 3FA658 */ static int un_803FA658;
/* 3FA8E8 */ static int un_803FA8E8;
/* 3FAA44 */ static u8 un_803FAA44[0xC0];
/* 3FB168 */ static int un_803FB168;
/* 3FB60C */ static u8 un_803FB60C[0xE0];
/* 3FB728 */ static u8 un_803FB728[0xC0];
/* 3FB870 */ static u8 un_803FB870[0xE0];
/* 3FB98C */ static u8 un_803FB98C[0xC0];
/* 3FBA9C */ static u8 un_803FBA9C[0xC0];
/* 3FBB98 */ static u8 un_803FBB98[0xC0];
/* 3FBCAC */ static u8 un_803FBCAC[0xC0];
/* 3FBDC0 */ static u8 un_803FBDC0[0xC0];
/* 3FBFFC */ static u8 un_803FBFFC[0xC0];
/* 3FC0FC */ static u8 un_803FC0FC[0xC0];
/* 3FC22C */ static u8 un_803FC22C[0x1F4];
/* 3FC63C */ static u8 un_803FC63C[0x80];
/* 3FC70C */ static u8 un_803FC70C[0x11C];
/* 3FC828 */ static u8 un_803FC828[0xA0];
/* 3FC8C8 */ static u8 un_803FC8C8[0x168];
/* 3FCA40 */ static u8 un_803FCA40[0x1A0];
/* 3FCC38 */ static u8 un_803FCC38[0xFC];
/* 3FCD34 */ static u8 un_803FCD34[0x118];
/* 3FCE4C */ static u8 un_803FCE4C[0xE0];
/* 3FD064 */ static u8 un_803FD064[0x1C0];
/* 3FD310 */ static u8 un_803FD310[0x27C];
/* 3FD58C */ static u8 un_803FD58C[0x2D8];
/* 3FD864 */ static u8 un_803FD864[0x294];
/* 3FDAF8 */ static u8 un_803FDAF8[0x80];
/* 3FDB9C */ static u8 un_803FDB9C[0x84];
/* 3FD224 */ extern char un_803FD224[];
/* 3FD230 */ extern char un_803FD230[];
/* 3FD23C */ extern char un_803FD23C[];
/* 3FD24C */ extern char un_803FD24C[];
/* 3FD258 */ extern char un_803FD258[];
/* 3FD264 */ extern char un_803FD264[];
/* 3FD274 */ extern void* un_803FD274;
/* 3FD28C */ extern char un_803FD28C[];
/* 3FD29C */ extern char un_803FD29C[];
/* 3FD2AC */ extern char un_803FD2AC[];

// .sdata
/* 4D5850 */ static int un_804D5850 = 0x7F;
/* 4D5854 */ static int un_804D5854 = 0x7F;
/* 4D5858 */ static int un_804D5858 = 0x7F;
/* 4D585C */ static int un_804D585C = -1;

// .sbss
/* 4D6DA8 */ static int* un_804D6DA8;
/* 4D6DAC */ static int un_804D6DAC;
/* 4D6DB0 */ static int un_804D6DB0;
/* 4D6DB4 */ static int un_804D6DB4;
/* 4D6DB8 */ static int un_804D6DB8;
/* 4D6DBC */ static int un_804D6DBC;
/* 4D6DC0 */ static int un_804D6DC0;

// .sbss (extern)
/* 4D6DC8 */ extern s32 un_804D6DC8;
/* 4D6DCC */ extern s32 un_804D6DCC;
/* 4D6DD0 */ extern float un_804D6DD0;
/* 4D6DD8 */ extern s32 un_804D6DD8;
/* 4D6DDC */ extern s32 un_804D6DDC;
/* 4D6DE0 */ extern s32 un_804D6DE0;
/* 4D6DE4 */ extern s32 un_804D6DE4;
/* 4D6DE8 */ extern s32 un_804D6DE8;
/* 4D6DEC */ extern s32 un_804D6DEC;
/* 4D6DF0 */ extern s32 un_804D6DF0;
/* 4D6DF4 */ extern s32 un_804D6DF4;
/* 4D6DF8 */ extern s32 un_804D6DF8;
/* 4D6DFC */ extern s32 un_804D6DFC;
/* 4D6E00 */ extern s32 un_804D6E00;
/* 4D6E04 */ extern void* un_804D6E04;
/* 4D6E08 */ extern HSD_GObj* un_804D6E08;
/* 4D6E0C */ extern s32 un_804D6E0C;
/* 4D6E10 */ extern s32 un_804D6E10;
/* 4D6E14 */ extern s32 un_804D6E14;

// .sdata (extern)
/* 4D5908 */ extern s32 un_804D5908;
/* 4D590C */ extern s32 un_804D590C;
/* 4D5910 */ extern s32 un_804D5910;
/* 4D5978 */ extern char un_804D5978[];
/* 4D5980 */ extern char un_804D5980[];
/* 4D5988 */ extern char un_804D5988[];
/* 4D5990 */ extern char un_804D5990[];

// .bss (extern)
/* 45A6C0 */ extern u8 gmMainLib_8045A6C0[];

// .sdata2 (extern)
/* 4DDC48 */ extern float un_804DDC48;
/* 4DDC4C */ extern float un_804DDC4C;
/* 4DDC50 */ extern float un_804DDC50;

void un_802FF7DC(void)
{
    lbArchive_LoadSymbols("SmSt.dat", &un_804D6DA8, "smSoundTestLoadData", 0);
    un_803F9FDC = un_804D6DA8[0];
    un_803F9FD0 = un_804D6DA8[1];
    un_803FA070 = un_804D6DA8[2];
    un_803FA090 = un_804D6DA8[3];
    un_803FA09C = un_804D6DA8[4];
    un_803FA0B0 = un_804D6DA8[5];
}

bool un_802FF884(char* unused)
{
    return false;
}

int un_802FF88C(void)
{
    un_804D6DB8 = 0;
    un_804D5858 = 0x7F;
    un_804D5854 = 0x7F;
    un_804D5850 = 0x7F;
    un_804D6DB4 = 0;
    un_804D6DB0 = 0;
    un_804D6DC0 = 0;
    un_804D585C = -1;
    un_804D6DBC = lbAudioAx_80024BD0();
    lbAudioAx_800236DC();
    lbAudioAx_800245D4(0x7F);
    lbAudioAx_800245F4(0x7F);
    lbAudioAx_80024614(0x7F);
    if (un_80302DF0()) {
        un_80302DF8(un_80302DF0(), fn_802FFCC8);
    }
    {
        un_80304138_objalloc_t* x = un_80302DF0();
        x->x4->scale_x = 16.0f;
        x->x4->scale_y = 32.0f;
    }
    return 1;
}

void un_802FF934(void)
{
    lbAudioAx_80024C08(un_804D6DBC);
}

int un_802FF958(void)
{
    u8 tmp = un_804D5854;
    lbAudioAx_800245F4(tmp);
    tmp = un_804D5858;
    lbAudioAx_80024614(tmp);
    tmp = un_804D5850;
    lbAudioAx_800245D4(tmp);
    return 0;
}

int un_802FF99C(int arg0)
{
    u8 tmp = un_804D6DAC;
    lbAudioAx_80024634(tmp);
    un_802FFB58(arg0);
    return 0;
}

/// #un_802FF9DC

int un_802FFB58(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80023694();
        lbAudioAx_80023B24(((int**) un_804D6DA8)[5][un_804D6DB4]);
    } else if (arg0 == 0) {
        lbAudioAx_80023694();
    }
    return 0;
}

int un_802FFBAC(int arg0)
{
    if (arg0 == 1) {
        if (un_804D585C == un_804D6DB8) {
            int x = (un_804D6DC0 + 1) & 1;
            un_804D6DC0 = x;
            lbAudioAx_80024E50(x);
        } else {
            lbAudioAx_80023F28(un_804D6DB8);
            un_804D585C = un_804D6DB8;
            un_804D6DC0 = 0;
        }
    } else if (arg0 == 0) {
        lbAudioAx_800236DC();
        un_804D585C = -1;
        un_804D6DC0 = 0;
    }
    return 0;
}

bool un_802FFC30(void)
{
    lbAudioAx_800236DC();
    lbAudioAx_800245D4(0x7F);
    lbAudioAx_800245F4(0x7F);
    lbAudioAx_80024614(0x7F);
    return true;
}

bool un_802FFC6C(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80023694();
        lbAudioAx_80024030(0);
        lbAudioAx_800236DC();
        lbAudioAx_800245D4(0x7F);
        lbAudioAx_800245F4(0x7F);
        lbAudioAx_80024614(0x7F);
        gm_801A42F8(MJ_TITLE);
        gm_801A4B60();
    }
    return true;
}

bool fn_802FFCC8(void)
{
    return false;
}

/// #un_802FFCD0

void un_802FFD94(int arg0, void* arg1, void* arg2)
{
    struct un_80304138_objalloc_t* d;
    if (arg0 == 1) {
        d = un_80302DF0();
        lbAudioAx_80024030(1);
        un_80304210(d, arg1, 0, -60, 0);
        un_80302DF8(un_80302DF0(), arg2);
    }
}

int fn_802FFE0C(int arg0)
{
    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(4);
        gm_801A4B60();
        break;
    }
    return 0;
}

bool fn_802FFE6C(bool update_scene)
{
    bool res = update_scene;
    if (update_scene == false) {
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        res = false;
    }

    return res;
}

bool un_802FFEA4(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x4);
        gm_801A4B60();
    }

    return false;
}

void un_802FFEE0(s32* arg0)
{
#define ST_MIN(a, b) ((a) < (b) ? (a) : (b))
    u16 val = ST_MIN((u16) un_803FA258.x12C, 0x3E);
#undef ST_MIN

    ((u16*) arg0)[0] = val;
    ((u16*) arg0)[1] = (u16) un_803FA258.x130;
    arg0[1] = 0x98967F;
    arg0[2] = 0;
}

/// #un_802FFF2C

bool un_803001DC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x1);
        gm_801A4B60();
    }

    return false;
}

int un_80300218(void)
{
    lbLang_SetSavedLanguage(un_803FA258.x0);
    return 0;
}

int un_80300248(int arg0)
{
    if (un_803FA258.x4 && arg0 == 1) {
        lbAudioAx_80024030(1);
        gmMainLib_8015FB68();
    }
    return 0;
}

int un_80300290(int arg0)
{
    if (arg0 == 1) {
        struct un_80304138_objalloc_t* x = un_80302DF0();
        lbAudioAx_80024030(1);
        un_80304210(x, &un_803FA658, 0, -60, 0);
        un_80302DF8(un_80302DF0(), fn_802FFE6C);
    }
    return 0;
}

bool un_803002FC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x2);
        gm_801A4B60();
    }

    return false;
}

s32 un_80300338(void)
{
    u8* src = &gmMainLib_8045A6C0[un_803FA128.x220 + 0x1868];
    un_803FA128.x224 = src[0];
    un_803FA128.x225 = src[1];
    un_803FA128.x226 = src[2];
    un_803FA128.x227 = src[3];
    return 0;
}

s32 un_80300378(void)
{
    u8* src;
    un_803FA128.x220 &= 0xFFFE;
    src = &gmMainLib_8045A6C0[un_803FA128.x220 + 0x1868];
    un_803FA128.x224 = src[0];
    un_803FA128.x225 = src[1];
    un_803FA128.x226 = src[2];
    un_803FA128.x227 = src[3];
    return 0;
}

s32 un_803003C4(void)
{
    u8* src;
    un_803FA128.x220 &= 0xFFFC;
    src = &gmMainLib_8045A6C0[un_803FA128.x220 + 0x1868];
    un_803FA128.x224 = src[0];
    un_803FA128.x225 = src[1];
    un_803FA128.x226 = src[2];
    un_803FA128.x227 = src[3];
    return 0;
}

s32 un_80300410(s32 arg0)
{
    if (arg0 == 1) {
        u8* dst;
        lbAudioAx_80024030(1);
        dst = &gmMainLib_8045A6C0[un_803FA128.x220 + 0x1868];
        dst[0] = un_803FA128.x224;
        dst[1] = un_803FA128.x225;
        dst[2] = un_803FA128.x226;
        dst[3] = un_803FA128.x227;
    }
    return 0;
}

// these will try to inline un_802FFD94 otherwise
#pragma push
#pragma dont_inline on
int un_80300480(int arg0)
{
    un_802FFD94(arg0, &un_803FB168, fn_802FFE0C);
    return 0;
}

int un_803004B4(int arg0)
{
    un_802FFD94(arg0, &un_803FA8E8, fn_802FFE6C);
    return 0;
}
#pragma pop

#pragma dont_inline on
int un_803004E8(int arg0)
{
    un_802FFD94(arg0, &un_803FAA44, fn_802FFE6C);
    return 0;
}

int un_8030051C(int arg0)
{
    un_802FFD94(arg0, &un_803FB60C, fn_802FFE6C);
    return 0;
}

int un_80300550(int arg0)
{
    un_802FFD94(arg0, &un_803FB728, fn_802FFE6C);
    return 0;
}

int un_80300584(int arg0)
{
    un_802FFD94(arg0, &un_803FB870, fn_802FFE6C);
    return 0;
}

int un_803005B8(int arg0)
{
    un_802FFD94(arg0, &un_803FB98C, fn_802FFE6C);
    return 0;
}

int un_803005EC(int arg0)
{
    un_802FFD94(arg0, &un_803FBA9C, fn_802FFE6C);
    return 0;
}

int un_80300620(int arg0)
{
    un_802FFD94(arg0, &un_803FBB98, fn_802FFE6C);
    return 0;
}

int un_80300654(int arg0)
{
    un_802FFD94(arg0, &un_803FBCAC, fn_802FFE6C);
    return 0;
}

int un_80300688(int arg0)
{
    un_802FFD94(arg0, &un_803FBDC0, fn_802FFE6C);
    return 0;
}

int un_803006BC(int arg0)
{
    un_802FFD94(arg0, &un_803FBFFC, fn_802FFE6C);
    return 0;
}

int un_803006F0(int arg0)
{
    un_802FFD94(arg0, &un_803FC0FC, fn_802FFE6C);
    return 0;
}

int un_80300724(int arg0)
{
    un_802FFD94(arg0, &un_803FC22C, fn_802FFE6C);
    return 0;
}
#pragma dont_inline reset

void un_80300758(int arg0)
{
    if (arg0 == 1) {
        un_802FFCD0(4, (u8*)&un_803FA258 + 0x10);
    }
}

void un_80300790(int arg0)
{
    if (arg0 == 1) {
        un_802FFCD0(4, (u8*)&un_803FA258 + 0x24);
    }
}

#pragma dont_inline on
int un_803007C8(int arg0)
{
    un_802FFD94(arg0, &un_803FC63C, fn_802FFE6C);
    return 0;
}

int un_803007FC(int arg0)
{
    un_802FFD94(arg0, &un_803FCA40, fn_802FFE6C);
    return 0;
}

int un_80300830(int arg0)
{
    un_802FFD94(arg0, &un_803FCC38, fn_802FFE6C);
    return 0;
}

int un_80300864(int arg0)
{
    un_802FFD94(arg0, &un_803FCE4C, fn_802FFE6C);
    return 0;
}

int un_80300898(int arg0)
{
    un_802FFD94(arg0, &un_803FD064, fn_802FFE6C);
    return 0;
}

int un_803008CC(int arg0)
{
    un_802FFD94(arg0, &un_803FDAF8, fn_802FFE6C);
    return 0;
}

int un_80300900(int arg0)
{
    un_802FFD94(arg0, &un_803FDB9C, fn_802FFE6C);
    return 0;
}

int un_80300934(int arg0)
{
    un_802FFD94(arg0, &un_803FD310, fn_802FFE6C);
    return 0;
}
#pragma dont_inline reset

bool un_80300968(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_HANYU_CSS);
        gm_801A4B60();
    }

    return false;
}

bool un_803009A4(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_HANYU_SSS);
        gm_801A4B60();
    }

    return false;
}

s32 un_803009E0(void)
{
    switch (un_804D6DD8) {
    case 2: {
        u32 val = (u32) *gmMainLib_8015D06C((u8) un_804D6DC8);
        un_804D6DD0 = (float) (val / 100U);
        break;
    }
    case 3: {
        s32 result = gmMainLib_8015D48C((u8) un_804D6DC8);
        gmMainLib_8015D4E8((u8) un_804D6DC8, result);
        un_804D6DCC = result;
        break;
    }
    }
    return 0;
}

int un_80300A88(void)
{
    switch (un_804D6DD8) {
    case 3:
        if (un_804D6DCC >= 1) {
            un_804D6DCC = 1;
        }
        break;
    }
    return 0;
}

bool un_80300AB8(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x4);
        gm_801A4B60();
    }

    return false;
}

bool un_80300AF4(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_803FA258.x8 = 0x3F;
        un_803FA258.x10 = 0xE;
        un_803FA258.x28 = 3;
        un_803FA258.x2C = 3;
        un_803FA258.x30 = 3;
        gm_SetScenePendingMinor(4);
        gm_801A4B60();
    }
    return false;
}

bool un_80300B58(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_803FA258.x8 = 0x3B;
        un_803FA258.x10 = 0x2;
        un_803FA258.x28 = 3;
        un_803FA258.x2C = 3;
        un_803FA258.x30 = 3;
        gm_SetScenePendingMinor(4);
        gm_801A4B60();
    }
    return false;
}

bool un_80300BBC(bool update_scene)
{
    if (update_scene == true) {
        un_803124BC();
        un_80311680();
        gm_801A42F8(MJ_TOY_GALLERY);
        gm_801A4B60();
    }

    return false;
}

bool un_80300BF8(bool update_scene)
{
    if (update_scene == true) {
        un_803124BC();
        Trophy_SetUnlockState(0xE6, true);
        gm_801A42F8(MJ_MENU);
        gm_801A4B60();
    }

    return false;
}

bool un_80300C3C(bool update_scene)
{
    if (update_scene == true) {
        un_803124BC();
        Trophy_SetUnlockState(0xC9, true);
        gm_801A42F8(MJ_MENU);
        gm_801A4B60();
    }

    return false;
}

bool un_80300C80(int arg0)
{
    if (arg0 == 1) {
        int* ptr = gmMainLib_8015CCF0();
        *ptr = un_804D6DDC * 10;
        un_803124BC();
        gm_801A42F8(1);
        gm_801A4B60();
    }
    return false;
}

void fn_80300CC8(int arg0)
{
    int* r29;
    int* r30;
    int* r31;

    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        r29 = gmMainLib_8015CD2C();
        r30 = gmMainLib_8015CD38();
        r31 = gmMainLib_8015CD44();
        {
            int* ptr = gmMainLib_8015CD50();
            *r29 = un_804D6DE0;
            *r30 = un_804D6DE4;
            *r31 = un_804D6DE8;
            *ptr = un_804D6DEC;
        }
        gm_801A42F8(1);
        gm_801A4B60();
        break;
    }
}

#pragma dont_inline on
int un_80300D78(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_804D6DE0 = un_804D6DF0;
        un_804D6DE4 = un_804D6DF0;
        un_804D6DE8 = un_804D6DF0;
        un_804D6DEC = un_804D6DF0;
        un_802FFD94(arg0, &un_803FC70C, fn_80300CC8);
    }
    return 0;
}
#pragma dont_inline reset

void fn_80300DE0(int arg0)
{
    s32* ptr;

    ptr = gmMainLib_8015D06C(un_804D6DC8);
    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        *ptr = (u32) (un_804DDC48 * un_804D6DD0);
        gm_801A42F8(1);
        gm_801A4B60();
        break;
    }
}

#pragma dont_inline on
int un_80300E74(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_804D6DD8 = 2;
        un_802FFD94(arg0, &un_803FC8C8, fn_80300DE0);
    }
    return 0;
}
#pragma dont_inline reset

void fn_80300ED0(int arg0)
{
    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        gmMainLib_8015D4E8(un_804D6DC8, un_804D6DCC);
        gm_801A42F8(1);
        gm_801A4B60();
        break;
    }
}

#pragma dont_inline on
int un_80300F3C(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_804D6DD8 = 3;
        un_802FFD94(arg0, &un_803FC828, fn_80300ED0);
    }
    return 0;
}
#pragma dont_inline reset

s32 un_80300F98(s32 arg0)
{
    s32* temp_r31;

    if (arg0 == 1) {
        temp_r31 = gmMainLib_8015CDB0();
        lbAudioAx_80024030(1);
        *temp_r31 = un_804D6DF4;
        gm_801A42F8(1);
        gm_801A4B60();
    }
    return 0;
}

bool un_80300FEC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x4);
        gm_801A4B60();
    }

    return false;
}

int un_80301028(int arg0)
{
    if (arg0 == 1) {
        struct gmm_x0_528_t* ptr = gmMainLib_8015CDD4();
        ptr->x5 = un_804D5908 - 1;
        lbAudioAx_80024030(1);
        gm_801A42F8(4);
        gm_801A4B60();
    }
    return 0;
}

int un_80301074(int arg0)
{
    if (arg0 == 1) {
        struct gmm_x0_528_t* ptr = gmMainLib_8015CDC8();
        ptr->x5 = un_804D590C - 1;
        lbAudioAx_80024030(1);
        gm_801A42F8(3);
        gm_801A4B60();
    }
    return 0;
}

int un_803010C0(int arg0)
{
    if (arg0 == 1) {
        struct gmm_x0_528_t* ptr = gmMainLib_8015CDE0();
        ptr->x5 = un_804D5910 - 1;
        lbAudioAx_80024030(1);
        gm_801A42F8(5);
        gm_801A4B60();
    }
    return 0;
}

int fn_8030110C(int arg0)
{
    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        gm_801BEFA4(un_804D6DF8);
        gm_801BEFC0(un_804D6DFC);
        {
            struct gmm_x0_528_t* ptr = gmMainLib_8015CDC8();
            ptr->c_kind = (s8) un_804D6DF8;
            ptr->color = (u8) un_804D6DFC;
        }
        switch (un_804D6E00) {
        case 0:
            gm_801A42F8(0x1A);
            gm_801BF040(0x15);
            break;
        case 1:
            gm_801A42F8(0x1A);
            gm_801BF040(0x16);
            break;
        case 2:
            gm_801A42F8(0x1A);
            gm_801BF040(0x17);
            break;
        }
        gm_801A4B60();
        break;
    }
    return 0;
}

void fn_803011EC(int arg0)
{
    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        gm_801BEFA4(un_804D6DF8);
        gm_801BEFC0(un_804D6DFC);
        {
            s8 c_kind = (s8) un_804D6DF8;
            gm_8017EB30()->x0.ckind = c_kind;
        }
        {
            u8 color = (u8) un_804D6DFC;
            gm_8017EB30()->x0.color = color;
        }
        gm_801A42F8(0x15);
        gm_801A4B60();
        break;
    }
}

#pragma dont_inline on
int un_80301280(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_802FFD94(arg0, &un_803FCD34, fn_803011EC);
    }
    return 0;
}

int un_803012D4(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        un_802FFD94(arg0, &un_803FCD34, fn_8030110C);
    }
    return 0;
}
#pragma dont_inline reset

bool un_80301328(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801BF708(0x0);
        gm_801A42F8(MJ_OPENING_MV);
        gm_801A4B60();
    }

    return false;
}

bool un_8030136C(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801BF708(0x5);
        gm_801A42F8(MJ_OPENING_MV);
        gm_801A4B60();
    }

    return false;
}

bool un_803013B0(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_DEBUG_CUTSCENE);
        gm_801A4B60();
    }

    return false;
}

#pragma dont_inline on
int un_803013EC(int arg0)
{
    un_802FFD94(arg0, &un_803FD58C, un_80301B48);
    return 0;
}

int un_80301420(int arg0)
{
    un_802FFD94(arg0, &un_803FD864, un_80301C80);
    return 0;
}
#pragma dont_inline reset

bool un_80301454(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_BOOT);
        gm_801A4B60();
    }

    return false;
}

bool un_80301490(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xD);
        gm_801A4B60();
    }

    return false;
}

bool un_803014CC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x7);
        gm_801A4B60();
    }

    return false;
}

bool un_80301508(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x3);
        gm_801A4B60();
    }

    return false;
}

bool un_80301544(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x9);
        gm_801A4B60();
    }

    return false;
}

bool un_80301580(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xC);
        gm_801A4B60();
    }

    return false;
}

bool un_803015BC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_PROGRESSIVE_SCAN);
        gm_801A4B60();
    }

    return false;
}

bool un_803015F8(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xA);
        gm_801A4B60();
    }

    return false;
}

int un_80301634(void)
{
    HSD_GObj* gobj;
    void* r31;
    void* r3;

    OSReport(un_804D5978);
    lb_8001C550();
    lb_8001D164(0);
    r31 = HSD_MemAlloc(lbSnap_8001E210());
    r3 = HSD_MemAlloc(lbSnap_8001E204());
    lbSnap_8001E218(r3, r31);
    un_804D6E04 = HSD_MemAlloc(0x96000);
    gobj = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(gobj, 0x280, 0x1E0, 0xC);
    gobj->gxlink_prios = 0x40000;
    gobj->user_data = NULL;
    un_804D6E08 = 0;
    return 0;
}

int un_803016D8(int arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD224);
    {
        s32 result = lb_8001B8C8(0);
        OSReport(un_803FD230, result);
    }
    return 0;
}

int un_80301734(int arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD23C);
    {
        s32 result = lb_8001C87C();
        OSReport(un_803FD230, result);
    }
    return 0;
}

int un_8030178C(int arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD24C);
    {
        s32 result = lb_8001C8BC();
        OSReport(un_803FD230, result);
        if (result == 0) {
            lb_8001CBAC(0);
        }
    }
    return 0;
}

int un_80301800(int arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_804D5980);
    lb_8001CE00();
    return 0;
}

int un_80301840(int arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_804D5988);
    {
        s32 result = lb_8001CBBC();
        gmMainLib_8015FA34(result);
        if (result == 0 || result == 2) {
            lb_8001CBAC(0);
        }
        OSReport(un_803FD230, result);
    }
    return 0;
}

int un_803018BC(int arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD258);
    {
        s32 result = lb_8001CC4C();
        OSReport(un_803FD230, result);
    }
    lb_8001CBAC(4);
    return 0;
}

int un_8030191C(int arg0)
{
    if (arg0 != 1) {
        return 0;
    }
    OSReport(un_803FD264);
    lbSnap_8001D40C(0);
    return 0;
}

int un_80301964(int arg0)
{
    if (arg0 != 1) {
        return 0;
    }

    OSReport(un_803FD28C);

    if (lbSnap_8001E058(0, un_804D6E0C) == 0xB) {
        s32 result;
        do {
            result = lb_8001B6F8();
        } while (result == 0xB);

        if (result == 0 && lbSnap_8001DE8C(un_804D6E04) != 0) {
            HSD_GObj* gobj;
            HSD_SObj_803A477C_t* sobj;

            if (un_804D6E08 != NULL) {
                HSD_GObjPLink_80390228(un_804D6E08);
            }

            gobj = GObj_Create(0xE, 0xF, 0);
            GObj_SetupGXLink(gobj, HSD_SObjLib_803A49E0, 0x12, 0);
            un_803FD274 = un_804D6E04;
            sobj =
                HSD_SObjLib_803A477C(gobj, (s32) un_804D5990, 0, 0, 0x80, 0);
            sobj->x10 = un_804DDC4C;
            sobj->x14 = un_804DDC50;
            sobj->x40 |= 2;
            un_804D6E08 = gobj;
        }
    }

    return 0;
}

int un_80301A64(int arg0)
{
    s32 result;

    if (arg0 != 1) {
        return 0;
    }

    OSReport(un_803FD29C);
    result = lbSnap_8001D5FC(0, un_804D6E10);
    if (result != 0xB) {
        return 0;
    }

    do {
        result = lb_8001B6F8();
    } while (result == 0xB);

    if (result == 0) {
        lbSnap_8001D40C(0);
    }
    return 0;
}

int un_80301AD4(int arg0)
{
    s32 result;

    if (arg0 != 1) {
        return 0;
    }

    OSReport(un_803FD2AC);
    result = lbSnap_8001D7B0(0, un_804D6E14, un_804D6E10);
    if (result != 0xB) {
        return 0;
    }

    do {
        result = lb_8001B6F8();
    } while (result == 0xB);

    if (result == 0) {
        lbSnap_8001D40C(0);
    }
    return 0;
}

int un_80301B48(int arg0)
{
    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(6);
        gm_801A4B60();
        break;
    }
    return 0;
}

void un_80301BA8(void* arg0)
{
    u8* out = arg0;
    *(s32*) (out + 0x0) = un_803FA258.x104;
    *(s32*) (out + 0x4) = un_803FA258.x108;
    out[0xA] = (u8) un_803FA258.x100;
    out[0xB] = (u8) un_803FA258.x10C;
    out[0xC] = (u8) un_803FA258.x11C;
    out[0x8] = 0;
    out[0x9] = 0x78;
    out[0xD] = (u8) un_803FA258.x110;
    out[0x19] = (u8) un_803FA258.xF8;
    out[0xE] = (u8) un_803FA258.x114;
    out[0x1A] = (u8) un_803FA258.xF8;
    out[0xF] = (u8) un_803FA258.x118;
    out[0x1B] = (u8) un_803FA258.xF8;
    out[0x10] = (u8) un_803FA258.x120;
    out[0x1C] = (u8) un_803FA258.xFC;
    out[0x11] = (u8) un_803FA258.x124;
    out[0x1D] = (u8) un_803FA258.xFC;
    out[0x12] = (u8) un_803FA258.x128;
    out[0x1E] = (u8) un_803FA258.xFC;
    out[0x13] = 0;
    out[0x14] = 0;
    out[0x15] = 0;
    out[0x16] = 0;
    out[0x17] = 0;
    out[0x18] = 0;
}

void un_80301C64(un_80301C64_t* arg0)
{
    arg0->x0 = un_803FA258.x138;
    arg0->x4 = 0;
}

int un_80301C80(int arg0)
{
    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xB);
        gm_801A4B60();
        break;
    }
    return 0;
}

void un_80301CE0(int arg0)
{
    switch (arg0) {
    case 6:
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xB);
        gm_801A4B60();
        break;
    case 1:
        un_802FFCD0(4, un_803FA258.x144);
        break;
    }
}

bool un_80301D40(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_FIXED_CAMERA_VS);
        gm_801A4B60();
    }

    return false;
}

int un_80301D7C(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80024030(1);
        gm_801BEB74(un_803FA258.x188 - 1);
        gm_801A42F8(0x2B);
        gm_801A4B60();
    }
    return 0;
}

bool un_80301DCC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x4);
        gm_801A4B60();
    }

    return false;
}

bool un_80301E08(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xE);
        gm_801A4B60();
    }

    return false;
}
