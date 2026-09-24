#include <melee/if/soundtest.h>

#include <melee/gm/forward.h>

#include <melee/if/if_3004.h>
#include <melee/if/textlib.h>
#include <melee/if/types.h>
#include <melee/db/db.h>
#include <melee/db/dbsound.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
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
/* 3001DC */ static bool un_803001DC(enum soundtest_callback_arg0);
/* 300218 */ static bool un_80300218(enum soundtest_callback_arg0);
/* 300248 */ static bool un_80300248(enum soundtest_callback_arg0);
/* 300290 */ static bool un_80300290(enum soundtest_callback_arg0);
/* 3002FC */ static bool un_803002FC(enum soundtest_callback_arg0);
/* 300338 */ static bool un_80300338(enum soundtest_callback_arg0);
/* 300378 */ static bool un_80300378(enum soundtest_callback_arg0);
/* 3003C4 */ static bool un_803003C4(enum soundtest_callback_arg0);
/* 300410 */ static bool un_80300410(enum soundtest_callback_arg0);
/* 2FFCC8 */ static bool fn_802FFCC8(enum soundtest_callback_arg0);

/// .bss (extern)
/* 45A6C0 */ extern u8 gmMainLib_8045A6C0[];
/* 4D6B88 */ extern int db_804D6B88;

/// Overlay used to reach the menu data through the label block that precedes
/// it, the way the original code addresses it.
struct un_803F9F28_t {
    u8 _pad0[0xA8];
    int xA8;
    u8 _padAC[0x8];
    f32 xB4;
    u8 _padB8[0x90];
    int x148;
    u8 _pad14C[0x1C];
    int x168;
    u8 _pad16C[0x8];
    f32 x174;
    u8 _pad178[0x10];
    int x188;
    u8 _pad18C[0x50];
    char x1DC[0xC];
    char x1E8[0x18];
};

struct un_803FA128_x130_t {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10[4];
    int x20_pad;
    int x24[4];
    int x34_pad;
    int x38[4];
    int x48[4];
    int x58[4];
    int x68[4];
    f32 x78[4];
    f32 x88[4];
    f32 x98[4];
    int xA8[4];
    int xB8[4];
    int xC8;
    int xCC[4];
    int xDC[4];
    f32 xEC;
};

/// Overlay reaching past the end of #un_803FA128 into #un_803FA258, matching
/// how the original code addresses both blocks from a single base.
struct un_803FA128_t {
    u8 _pad0[0x130];
    struct un_803FA128_x130_t x130;
    u16 x220;
    u8 _pad222[0x2];
    u8 x224;
    u8 x225;
    u8 x226;
    u8 x227;
};

/// .data (defined at the end of this file, so that the functions above
/// address each block through its own symbol).
/* 803F9EF0 */ extern char lbl_803F9EF0[];
/* 803F9F10 */ extern char lbl_803F9F10[];
/* 803F9F28 */ extern char un_803F9F28[];
/* 803F9F38 */ extern char un_803F9F38[];
/* 803F9F44 */ extern char un_803F9F44[];
/* 803F9F50 */ extern char un_803F9F50[];
/* 803F9F5C */ extern char un_803F9F5C[];
/* 803F9F68 */ extern char un_803F9F68[];
/* 803F9F74 */ extern char un_803F9F74[];
/* 803F9F80 */ extern char un_803F9F80[];
/* 803F9F8C */ extern char un_803F9F8C[];
/* 803F9F98 */ extern char un_803F9F98[];
/* 803F9FA4 */
/* 803FA128 */ extern int un_803FA128[76];
/* 803FA258 */ extern struct un_803FA258_t un_803FA258;
/* 803FA3E8 */ extern char* un_803FA3E8[3];
/* 803FA3F4 */ extern char un_803FA3F4[];
/* 803FA404 */ extern char un_803FA404[];
/* 803FA414 */ extern char un_803FA414[];
/* 803FA424 */ extern char un_803FA424[];
/* 803FA434 */ extern char un_803FA434[];
/* 803FA440 */ extern char* un_803FA440[5];
/* 803FA454 */ extern char un_803FA454[];
/* 803FA468 */ extern char un_803FA468[];
/* 803FA474 */ extern char un_803FA474[];
/* 803FA480 */ extern char un_803FA480[];
/* 803FA48C */ extern char un_803FA48C[];
/* 803FA498 */ extern char un_803FA498[];
/* 803FA4A8 */ extern char un_803FA4A8[];
/* 803FA4B8 */ extern char un_803FA4B8[];
/* 803FA4CC */ extern char un_803FA4CC[];
/* 803FA640 */ extern char un_803FA640[];
/* 803FA658 */ extern struct un_80304138_objalloc_t_x8 un_803FA658[8];

/// .sdata
/* 804D5850 */ static int un_804D5850 = 127;
/* 804D5854 */ static int un_804D5854 = 127;
/* 804D5858 */ static int un_804D5858 = 127;
/* 804D585C */ static int un_804D585C = -1;
/* 804D5860 */ static char un_804D5860[] = "NONE";
/* 804D5868 */ static char un_804D5868[] = "ACTIVED";
/* 804D5870 */ static char un_804D5870[] = "AUTO";
/* 804D5878 */ static char un_804D5878[] = "OFF";
/* 804D587C */ static char un_804D587C[] = "ON";
/* 804D5880 */ char* un_804D5880[2] = { un_804D5878, un_804D587C };
/* 804D5888 */ static char* un_804D5888[2] = { un_803FA3F4, un_803FA404 };
/* 804D5890 */ static char un_804D5890[] = "Master";
/* 804D5898 */ static char un_804D5898[] = "Develop";
/* 804D58A0 */ static char un_804D58A0[] = "Addr4 :";
/* 804D58A8 */ static char un_804D58A8[] = "u32   :";
/* 804D58B0 */ static char un_804D58B0[] = "Addr2 :";
/* 804D58B8 */ static char un_804D58B8[] = "u16   :";
/* 804D58C0 */ static char un_804D58C0[] = "Addr  :";
/* 804D58C8 */ static char un_804D58C8[] = "u8    :";

/// .sbss
/* 4D6DA8 */ static int* un_804D6DA8;
/* 4D6DAC */ static int un_804D6DAC;
/* 4D6DB0 */ static int un_804D6DB0;
/* 4D6DB4 */ static int un_804D6DB4;
/* 4D6DB8 */ static int un_804D6DB8;
/* 4D6DBC */ static int un_804D6DBC;
/* 4D6DC0 */ static int un_804D6DC0;

void un_802FF7DC(void)
{
    struct un_803F9F28_t* data = (struct un_803F9F28_t*) un_803F9F28;
    int* syms;
    lbArchive_LoadSymbols(data->x1DC, &un_804D6DA8, data->x1E8, 0);
    syms = un_804D6DA8;
    data->xB4 = syms[0];
    data->xA8 = syms[1];
    data->x148 = syms[2];
    data->x168 = syms[3];
    data->x174 = syms[4];
    data->x188 = syms[7];
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
        un_804D6DB4 += ((int**) un_804D6DA8)[6][i];
    }
    un_803F9FA4.entries[7].x14 = (f32) un_804D6DB4;
    total = un_804D6DB4 + ((int**) un_804D6DA8)[6][un_804D6DB0];
    un_803F9FA4.entries[7].x18 = (f32) total;
    return 0;
}

bool un_802FFB58(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80023694();
        lbAudioAx_80023B24(((int**) un_804D6DA8)[5][un_804D6DB4]);
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

void un_802FFCD0(int count, void* data)
{
    int* arr = data;
    int i;
    for (i = 0; i < count; i++) {
        arr[i] = arr[count];
    }
}

void un_802FFD94(int arg0, void* arg1, soundtest_callback arg2)
{
    struct un_80304138_objalloc_t* d;
    if (arg0 == 1) {
        d = un_80302DF0();
        sfxForward();
        un_80304210(d, arg1, 0, -60, 0);
        un_80302DF8(un_80302DF0(), arg2);
    }
}

bool fn_802FFE0C(enum soundtest_callback_arg0 arg0)
{
    switch (arg0) {
    case 0:
        sfxBack();
        un_80304334(un_80302DF0());
        break;
    case 6:
        sfxForward();
        gm_SetNextGameModeStateId(4);
        gm_801A4B60();
        break;
    default:
        break;
    }
    return 0;
}

bool fn_802FFE6C(enum soundtest_callback_arg0 update_scene)
{
    bool res = update_scene;
    if (update_scene == false) {
        sfxBack();
        un_80304334(un_80302DF0());
        res = false;
    }

    return res;
}

bool un_802FFEA4(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetNextGameModeStateId(0x4);
        gm_801A4B60();
    }

    return false;
}

void un_802FFEE0(struct UnkSoundTestData0* arg0)
{
    u16 val = MIN((u16) un_803FA258.x12C, 0x3E);
    arg0->x0 = val;
    arg0->x2 = un_803FA258.x130;
    arg0->x4 = 0x98967F;
    arg0->x8 = 0;
}

void un_802FFF2C(StartMeleeData* arg0)
{
    StartMeleeRules* r = &arg0->rules;
    struct un_803FA128_t* s = (struct un_803FA128_t*) un_803FA128;
    struct un_803FA128_x130_t* sp;
    s32 i;
    u16 timer;

    gm_SetupRulesDefaults(r);
    r->x2_2 = 0;
    r->is_teams = s->x130.xC;
    switch (s->x130.xC8) {
    case 0:
        r->match_kind = 0;
        timer = s->x130.xCC[1] + s->x130.xCC[0] * 0x3C;
        if (timer != 0) {
            r->time_limit = timer;
            r->timer_enabled = 1;
        } else {
            r->timer_enabled = 0;
        }
        break;
    case 1:
        r->match_kind = 1;
        r->timer_enabled = 0;
        break;
    case 2:
        r->match_kind = 2;
        timer = s->x130.xCC[1] + s->x130.xCC[0] * 0x3C;
        if (timer != 0) {
            r->time_limit = timer;
            r->timer_enabled = 1;
        } else {
            r->timer_enabled = 0;
        }
        break;
    default:
        r->match_kind = 0;
        r->timer_enabled = 0;
        break;
    }
    r->stkind = s->x130.x8;
    r->x20 = -1;
    r->item_freq = s->x130.xCC[3] - 1;
    r->sd_penalty = -1;
    r->x30 = s->x130.xEC;
    gm_SetupAllPlayerDefaults(arg0->players);
    sp = &s->x130;
    for (i = 0; i < 4; i++) {
        arg0->players[i].ckind = sp->x10[i];
        arg0->players[i].slot_type = sp->x24[i];
        arg0->players[i].color = sp->x38[i];
        arg0->players[i].sub_color = sp->x48[i];
        arg0->players[i].team = sp->x58[i];
        arg0->players[i].rumble_enabled = sp->xDC[i];
        arg0->players[i].damage1 = sp->x68[i];
        arg0->players[i].attack_ratio = sp->x78[i];
        arg0->players[i].defense_ratio = sp->x88[i];
        arg0->players[i].cpu_kind = sp->xA8[i];
        arg0->players[i].cpu_level = sp->xB8[i];
        arg0->players[i].stocks = s->x130.xCC[2];
        arg0->players[i].xC_b1 = 0;
        arg0->players[i].model_scale = sp->x98[i];
    }
}

bool un_803001DC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetNextGameModeStateId(0x1);
        gm_801A4B60();
    }

    return false;
}

bool un_80300218(enum soundtest_callback_arg0 arg0)
{
    lbLang_SetSavedLanguage(un_803FA258.x0);
    return 0;
}

bool un_80300248(enum soundtest_callback_arg0 arg0)
{
    if (un_803FA258.x4[0] && arg0 == 1) {
        sfxForward();
        gmMainLib_8015FB68();
    }
    return 0;
}

bool un_80300290(enum soundtest_callback_arg0 arg0)
{
    un_802FFD94(arg0, &un_803FA658, fn_802FFE6C);
    return 0;
}

bool un_803002FC(enum soundtest_callback_arg0 update_scene)
{
    if (update_scene == true) {
        sfxForward();
        gm_SetNextGameModeStateId(0x2);
        gm_801A4B60();
    }

    return false;
}

bool un_80300338(enum soundtest_callback_arg0 arg0)
{
    struct un_803FA128_t* data = (struct un_803FA128_t*) un_803FA128;
    u8* src;

    src = gmMainLib_8045A6C0;
    src = src + data->x220;

    data->x224 = src[0x1868];
    data->x225 = src[0x1869];
    data->x226 = src[0x186A];
    data->x227 = src[0x186B];
    return 0;
}

bool un_80300378(enum soundtest_callback_arg0 arg0)
{
    struct un_803FA128_t* data = (struct un_803FA128_t*) un_803FA128;
    u8* ptr;

    data->x220 &= 0xFFFE;

    ptr = gmMainLib_8045A6C0;
    ptr = ptr + data->x220;

    data->x224 = ptr[0x1868];
    data->x225 = ptr[0x1869];
    data->x226 = ptr[0x186A];
    data->x227 = ptr[0x186B];

    return 0;
}

bool un_803003C4(enum soundtest_callback_arg0 arg0)
{
    struct un_803FA128_t* data = (struct un_803FA128_t*) un_803FA128;
    u8* ptr;

    data->x220 &= 0xFFFC;

    ptr = gmMainLib_8045A6C0;
    ptr = ptr + data->x220;

    data->x224 = ptr[0x1868];
    data->x225 = ptr[0x1869];
    data->x226 = ptr[0x186A];
    data->x227 = ptr[0x186B];

    return 0;
}

bool un_80300410(enum soundtest_callback_arg0 arg0)
{
    struct un_803FA128_t* data = (struct un_803FA128_t*) un_803FA128;

    if (arg0 == 1) {
        u8* dst;
        sfxForward();
        dst = gmMainLib_8045A6C0;
        dst += data->x220;
        dst[0x1868] = data->x224;
        dst[0x1869] = data->x225;
        dst[0x186A] = data->x226;
        dst[0x186B] = data->x227;
    }
    return 0;
}

/// .data
/* 803F9EF0 */ char lbl_803F9EF0[0x20] = "Remove Target %x (n %x) Id %d\n";
/* 803F9F10 */ char lbl_803F9F10[0x18] = "Remove All Over\n";
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
/* 803FA128 */ int un_803FA128[76] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 3, 2, 2, 5, 5, 4, 6, 6, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 6, 6, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5,
};
/* 803FA258 */ struct un_803FA258_t un_803FA258 = {
    /* 0x000 */ 0,
    /* 0x004 */ { 0, 32, 0, 6 },
    /* 0x014 */ { 8, 6, 6, 8 },
    /* 0x024 */ { 0, 0, 3, 3 },
    /* 0x034 */ 0,
    /* 0x038 */ { 0, 0, 0, 0 },
    /* 0x048 */ { 0, 0, 0, 0 },
    /* 0x058 */ { 0, 0, 0, 0 },
    /* 0x068 */ { 0, 0, 0, 0 },
    /* 0x078 */ { 1.0f, 1.0f, 1.0f, 1.0f },
    /* 0x088 */ { 1.0f, 1.0f, 1.0f, 1.0f },
    /* 0x098 */ { 1.0f, 1.0f, 1.0f, 1.0f },
    /* 0x0A8 */ { 4, 4, 4, 4 },
    /* 0x0B8 */ { 5, 5, 5, 5 },
    /* 0x0C8 */ 0,
    /* 0x0CC */ { 0, 0, 0, 0 },
    /* 0x0DC */ { 0, 0, 0, 0 },
    /* 0x0EC */ 1.0f,
    /* 0x0F0 */ 0x0,
    /* 0x0F2 */ { 0, 0 },
    /* 0x0F4 */ 0x0,
    /* 0x0F5 */ 0x0,
    /* 0x0F6 */ 0x0,
    /* 0x0F7 */ 0x0,
    /* 0x0F8 */ 0,
    /* 0x0FC */ 1,
    /* 0x100 */ 1,
    /* 0x104 */ 0,
    /* 0x108 */ 0,
    /* 0x10C */ 1,
    /* 0x110 */ 0,
    /* 0x114 */ 0,
    /* 0x118 */ 0,
    /* 0x11C */ 1,
    /* 0x120 */ 0,
    /* 0x124 */ 0,
    /* 0x128 */ 0,
    /* 0x12C */ 0,
    /* 0x130 */ 0,
    /* 0x134 */ 0,
    /* 0x138 */ NULL,
    /* 0x13C */ 0,
    /* 0x140 */ 0,
    /* 0x144 */ { 0, 0, 0, 0, 0, 1, 1, 1, 3, 1, 2, 3, 3, 0, 0, 0, 0 },
    /* 0x188 */ 1,
    /* 0x18C */ 0,
};
/* 803FA3E8 */ char* un_803FA3E8[3] = { un_804D5860, un_804D5868,
                                        un_804D5870 };
/* 803FA3F4 */ char un_803FA3F4[] = "GmLangTypeJP";
/* 803FA404 */ char un_803FA404[] = "GmLangTypeUS";
/* 803FA414 */ char un_803FA414[] = "No-Debug-Rom";
/* 803FA424 */ char un_803FA424[] = "Debug-Develop";
/* 803FA434 */ char un_803FA434[] = "Debug-Rom";
/* 803FA440 */ char* un_803FA440[5] = { un_804D5890, un_803FA414, un_803FA424,
                                        un_803FA434, un_804D5898 };
/* 803FA454 */ char un_803FA454[] = "Versus Mode    >";
/* 803FA468 */ char un_803FA468[] = "Result Test";
/* 803FA474 */ char un_803FA474[] = "Language : ";
/* 803FA480 */ char un_803FA480[] = "Publicity: ";
/* 803FA48C */ char un_803FA48C[] = "DbLevel : ";
/* 803FA498 */ char un_803FA498[] = "Ik Debug Flag :";
/* 803FA4A8 */ char un_803FA4A8[] = "New DefCalc :";
/* 803FA4B8 */ char un_803FA4B8[] = "Global Data Edit >";
/* 803FA4CC */ char un_803FA4CC[] = "Mode Team Test >";
/* 803FA4E0 */ struct un_80304138_objalloc_t_x8 un_803FA4E0[11] = {
    { 0, NULL, db_build_timestamp, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803001DC, un_803FA454, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_80301420, un_803FA468, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 2, un_80300218, un_803FA474, un_804D5888, &un_803FA258.x0, 0.0f, 2.0f,
      0.0f },
    { 2, un_80300248, un_803FA480, un_804D5880, &un_803FA258.x4[0], 0.0f, 2.0f,
      0.0f },
    { 2, NULL, un_803FA48C, un_803FA440, &DbLevel, 0.0f, 5.0f, 0.0f },
    { 3, NULL, un_803FA498, NULL, &db_804D4AF8, 0.0f, 1.0f, 1.0f },
    { 3, NULL, un_803FA4A8, NULL, &db_804D6B88, 0.0f, 1.0f, 1.0f },
    { 1, un_80300290, un_803FA4B8, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 1, un_803002FC, un_803FA4CC, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
/* 803FA640 */ char un_803FA640[] = "< Global Data Edit >";
/* 803FA658 */ struct un_80304138_objalloc_t_x8 un_803FA658[8] = {
    { 0, NULL, un_803FA640, NULL, NULL, 0.0f, 0.0f, 0.0f },
    { 6, un_803003C4, un_804D58A0, NULL, &un_803FA258.xF0, 0.0f, 0.0f, 4.0f },
    { 7, un_80300410, un_804D58A8, NULL, &un_803FA258.xF4, 0.0f, 0.0f, 1.0f },
    { 6, un_80300378, un_804D58B0, NULL, &un_803FA258.xF0, 0.0f, 0.0f, 2.0f },
    { 6, un_80300410, un_804D58B8, NULL, &un_803FA258.xF4, 0.0f, 0.0f, 1.0f },
    { 6, un_80300338, un_804D58C0, NULL, &un_803FA258.xF0, 0.0f, 0.0f, 1.0f },
    { 5, un_80300410, un_804D58C8, NULL, &un_803FA258.xF4, 0.0f, 0.0f, 1.0f },
    { 9, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f },
};
