#include "soundtest.h"

#include <melee/gm/forward.h>

#include "textlib.h"
#include "types.h"
#include <melee/gm/gm_unsplit.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/mn/inlines.h>

/* 2FF88C */ static bool un_802FF88C(enum soundtest_callback_arg0);
/* 2FF934 */ static bool un_802FF934(enum soundtest_callback_arg0);
/* 2FF958 */ static bool un_802FF958(enum soundtest_callback_arg0);
/* 2FF99C */ static bool un_802FF99C(enum soundtest_callback_arg0);
/* 2FF9DC */ static bool un_802FF9DC(enum soundtest_callback_arg0);
/* 2FFB58 */ static bool un_802FFB58(enum soundtest_callback_arg0);
/* 2FFBAC */ static bool un_802FFBAC(enum soundtest_callback_arg0);
/* 2FFC30 */ static bool un_802FFC30(enum soundtest_callback_arg0);
/* 2FFC6C */ static bool un_802FFC6C(enum soundtest_callback_arg0);
/* 2FFCC8 */ static bool fn_802FFCC8(enum soundtest_callback_arg0);

/// Symbol table loaded from SmSt.dat
struct SoundTestLoadData {
    /* 0x00 */ int x0;
    /* 0x04 */ char** x4;
    /* 0x08 */ char** x8;
    /* 0x0C */ char** xC;
    /* 0x10 */ int x10;
    /* 0x14 */ int* x14;
    /* 0x18 */ int* x18;
    /* 0x1C */ char** x1C;
};

/// .sdata
/* 804D5850 */ static int un_804D5850 = 127;
/* 804D5854 */ static int un_804D5854 = 127;
/* 804D5858 */ static int un_804D5858 = 127;
/* 804D585C */ static int un_804D585C = -1;

/// .sbss
/* 4D6DA8 */ static struct SoundTestLoadData* un_804D6DA8;
/* 4D6DAC */ static int un_804D6DAC;
/* 4D6DB0 */ static int un_804D6DB0;
/* 4D6DB4 */ static int un_804D6DB4;
/* 4D6DB8 */ static int un_804D6DB8;
/* 4D6DBC */ static int un_804D6DBC;
/* 4D6DC0 */ static int un_804D6DC0;

/// .data
/* 803F9F28 */ char un_803F9F28[] = "Sound Test Menu";
/* 803F9F38 */ char un_803F9F38[] = "Sound Mode ";
/* 803F9F44 */ char un_803F9F44[] = "Mas Volume";
/* 803F9F50 */ char un_803F9F50[] = "FGM Volume";
/* 803F9F5C */ char un_803F9F5C[] = "BGM Volume";
/* 803F9F68 */ char un_803F9F68[] = "DSP Level";
/* 803F9F74 */ char un_803F9F74[] = "FGM Group";
/* 803F9F80 */ char un_803F9F80[] = "FGM Name";
/* 803F9F8C */ char un_803F9F8C[] = "BGM Name";
/* 803F9F98 */ char un_803F9F98[] = "-- EXIT --";

/* 803F9FA4 */ struct SoundTestMenuData un_803F9FA4 = {
    {
        { 0, un_802FF88C, un_803F9F28, NULL, NULL, 0.0f, 0.0f, 0.0f },
        { 2, un_802FF934, un_803F9F38, NULL, &un_804D6DBC, 0.0f, 0.0f, 0.0f },
        { 3, un_802FF958, un_803F9F44, NULL, &un_804D5850, 0.0f, 127.0f,
          1.0f },
        { 3, un_802FF958, un_803F9F50, NULL, &un_804D5854, 0.0f, 127.0f,
          1.0f },
        { 3, un_802FF958, un_803F9F5C, NULL, &un_804D5858, 0.0f, 127.0f,
          1.0f },
        { 3, un_802FF99C, un_803F9F68, NULL, &un_804D6DAC, 0.0f, 127.0f,
          1.0f },
        { 2, un_802FF9DC, un_803F9F74, NULL, &un_804D6DB0, 0.0f, 55.0f, 1.0f },
        { 2, un_802FFB58, un_803F9F80, NULL, &un_804D6DB4, 0.0f, 0.0f, 0.0f },
        { 2, un_802FFBAC, un_803F9F8C, NULL, &un_804D6DB8, 0.0f, 98.0f, 1.0f },
        { 1, un_802FFC6C, un_803F9F98, NULL, NULL, 0.0f, 0.0f, 0.0f },
        { 9, un_802FFC30, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
    },
    "SmSt.dat",
    "smSoundTestLoadData",
};

void un_802FF7DC(void)
{
    lbArchive_LoadSymbols(un_803F9FA4.x160, &un_804D6DA8, un_803F9FA4.x16C, 0);
    un_803F9FA4.entries[1].x18 = un_804D6DA8->x0;
    un_803F9FA4.entries[1].xC = un_804D6DA8->x4;
    un_803F9FA4.entries[6].xC = un_804D6DA8->x8;
    un_803F9FA4.entries[7].xC = un_804D6DA8->xC;
    un_803F9FA4.entries[7].x18 = un_804D6DA8->x10;
    un_803F9FA4.entries[8].xC = un_804D6DA8->x1C;
}

bool un_802FF884(char* arg0)
{
    return false;
}

bool un_802FF88C(enum soundtest_callback_arg0 arg0)
{
    un_804D5858 = 0x7F;
    un_804D6DB8 = 0;
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

bool un_802FF934(enum soundtest_callback_arg0 arg0)
{
    lbAudioAx_80024C08(un_804D6DBC);
}

bool un_802FF958(enum soundtest_callback_arg0 arg0)
{
    u8 tmp = un_804D5854;
    lbAudioAx_800245F4(tmp);
    tmp = un_804D5858;
    lbAudioAx_80024614(tmp);
    tmp = un_804D5850;
    lbAudioAx_800245D4(tmp);
    return 0;
}

bool un_802FF99C(enum soundtest_callback_arg0 arg0)
{
    u8 tmp = un_804D6DAC;
    lbAudioAx_80024634(tmp);
    un_802FFB58(arg0);
    return 0;
}

bool un_802FF9DC(enum soundtest_callback_arg0 arg0)
{
    s32 i;
    s32 total;

    i = un_804D6DB4 = 0;
    for (; i < un_804D6DB0; i++) {
        un_804D6DB4 += un_804D6DA8->x18[i];
    }
    un_803F9FA4.entries[7].x14 = (f32) un_804D6DB4;
    total = un_804D6DB4 + un_804D6DA8->x18[un_804D6DB0];
    un_803F9FA4.entries[7].x18 = (f32) total;
    return 0;
}

bool un_802FFB58(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80023694();
        lbAudioAx_80023B24(un_804D6DA8->x14[un_804D6DB4]);
    } else if (arg0 == 0) {
        lbAudioAx_80023694();
    }
    return 0;
}

bool un_802FFBAC(enum soundtest_callback_arg0 arg0)
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

bool un_802FFC30(enum soundtest_callback_arg0 arg0)
{
    lbAudioAx_800236DC();
    lbAudioAx_800245D4(0x7F);
    lbAudioAx_800245F4(0x7F);
    lbAudioAx_80024614(0x7F);
    return true;
}

bool un_802FFC6C(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80023694();
        sfxBack();
        lbAudioAx_800236DC();
        lbAudioAx_800245D4(0x7F);
        lbAudioAx_800245F4(0x7F);
        lbAudioAx_80024614(0x7F);
        gm_ChangeGameModeAfterCurrentScene(GM_TITLE);
        gm_801A4B60();
    }
    return true;
}

bool fn_802FFCC8(enum soundtest_callback_arg0 arg0)
{
    return false;
}
