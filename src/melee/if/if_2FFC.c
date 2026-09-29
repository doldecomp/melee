#include "if_2FFC.h"

#include "if_3004.h"
#include "textlib.h"
#include "types.h"
#include <melee/db/db.h>
#include <melee/db/dbsound.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/inlines.h>

/* 3001DC */ static bool un_803001DC(enum soundtest_callback_arg0);
/* 300218 */ static bool un_80300218(enum soundtest_callback_arg0);
/* 300248 */ static bool un_80300248(enum soundtest_callback_arg0);
/* 300290 */ static bool un_80300290(enum soundtest_callback_arg0);
/* 3002FC */ static bool un_803002FC(enum soundtest_callback_arg0);
/* 300338 */ static bool un_80300338(enum soundtest_callback_arg0);
/* 300378 */ static bool un_80300378(enum soundtest_callback_arg0);
/* 3003C4 */ static bool un_803003C4(enum soundtest_callback_arg0);
/* 300410 */ static bool un_80300410(enum soundtest_callback_arg0);

/// .bss (extern)
/* 45A6C0 */ extern u8 gmMainLib_8045A6C0[];
/* 4D6B88 */ extern int db_804D6B88;

/* 803FA3F4 */ extern char un_803FA3F4[];
/* 803FA404 */ extern char un_803FA404[];

/// .sdata
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

/// .data
/* 803FA128 */ int un_803FA128[76] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 3, 2, 2, 5, 5, 4, 6, 6, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 6, 6, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5,
};
/* 803FA258 */ struct un_803FA258_t un_803FA258 = {
    /* 0x000 */ 0,
    /* 0x004 */ 0,
    /* 0x008 */ 32,
    /* 0x00C */ 0,
    /* 0x010 */ { 6, 8, 6, 6, 8 },
    /* 0x024 */ { 0, 0, 3, 3, 0 },
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
    { 2, un_80300248, un_803FA480, un_804D5880, &un_803FA258.x4, 0.0f, 2.0f,
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

void un_802FFCD0(int count, int* values)
{
    int i;
    for (i = 0; i < count; i++) {
        values[i] = values[count];
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
    struct un_803FA258_t* sp;
    s32 i;
    u16 timer;

    gm_SetupRulesDefaults(r);
    r->x2_2 = 0;
    r->is_teams = un_803FA258.xC;
    switch (un_803FA258.xC8) {
    case 0:
        r->match_kind = 0;
        timer = un_803FA258.xCC[1] + un_803FA258.xCC[0] * 0x3C;
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
        timer = un_803FA258.xCC[1] + un_803FA258.xCC[0] * 0x3C;
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
    r->stkind = un_803FA258.x8;
    r->x20 = -1;
    r->item_freq = un_803FA258.xCC[3] - 1;
    r->sd_penalty = -1;
    r->x30 = un_803FA258.xEC;
    gm_SetupAllPlayerDefaults(arg0->players);
    sp = &un_803FA258;
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
        arg0->players[i].stocks = un_803FA258.xCC[2];
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
    if (un_803FA258.x4 && arg0 == 1) {
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
    u8* src;

    src = gmMainLib_8045A6C0;
    src = src + un_803FA258.xF0;

    un_803FA258.xF4 = src[0x1868];
    un_803FA258.xF5 = src[0x1869];
    un_803FA258.xF6 = src[0x186A];
    un_803FA258.xF7 = src[0x186B];
    return 0;
}

bool un_80300378(enum soundtest_callback_arg0 arg0)
{
    u8* ptr;

    un_803FA258.xF0 &= 0xFFFE;

    ptr = gmMainLib_8045A6C0;
    ptr = ptr + un_803FA258.xF0;

    un_803FA258.xF4 = ptr[0x1868];
    un_803FA258.xF5 = ptr[0x1869];
    un_803FA258.xF6 = ptr[0x186A];
    un_803FA258.xF7 = ptr[0x186B];

    return 0;
}

bool un_803003C4(enum soundtest_callback_arg0 arg0)
{
    u8* ptr;

    un_803FA258.xF0 &= 0xFFFC;

    ptr = gmMainLib_8045A6C0;
    ptr = ptr + un_803FA258.xF0;

    un_803FA258.xF4 = ptr[0x1868];
    un_803FA258.xF5 = ptr[0x1869];
    un_803FA258.xF6 = ptr[0x186A];
    un_803FA258.xF7 = ptr[0x186B];

    return 0;
}

bool un_80300410(enum soundtest_callback_arg0 arg0)
{
    if (arg0 == 1) {
        u8* dst;
        sfxForward();
        dst = gmMainLib_8045A6C0;
        dst += un_803FA258.xF0;
        dst[0x1868] = un_803FA258.xF4;
        dst[0x1869] = un_803FA258.xF5;
        dst[0x186A] = un_803FA258.xF6;
        dst[0x186B] = un_803FA258.xF7;
    }
    return 0;
}
