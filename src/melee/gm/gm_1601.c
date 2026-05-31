#include "gm_1601.h"

#include "gm_1601.static.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmstamina.h"
#include "placeholder.h"
#include "stddef.h"

#include "baselib/gobjplink.h"
#include "baselib/jobj.h"
#include "baselib/particle.h"
#include "cm/camera.h"

#include "gm/forward.h"

#include "gm/types.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "if/ifnametag.h"
#include "if/ifstatus.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbtime.h"
#include "mn/mnstagesel.h"
#include "pl/player.h"
#include "pl/plbonus.h"
#include "sc/types.h"
#include "ty/toy.h"

#include <m2c_macros.h>
#include <baselib/video.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/random.h>
#include <melee/gm/gm_1A45.h>
#include <melee/pl/player.h>

/// JP character names
char* lbl_803D4D74[] = {
    "Ｃ．ファルコン",
    "ドンキ－コング",
    "フォックス",
    "Ｍｒ．ゲ－ム＆ウォッチ",
    "カ－ビィ",
    "クッパ",
    "リンク",
    "ルイ－ジ",
    "マリオ",
    "マルス",
    "ミュウツ－",
    "ネス",
    "ピ－チ",
    "ピカチュウ",
    "アイスクライマー",
    "プリン",
    "サムス",
    "ヨッシ－",
    "ゼルダ",
    "シーク",
    "ファルコ",
    "こどもリンク",
    "ドクタ－マリオ",
    "ロイ",
    "ピチュ－",
    "ガノンドロフ",
    "マスターハンド",
    "謎のザコ敵：男",
    "謎のザコ敵：女",
    "ギガクッパ",
    "クレイジーハンド",
    "サンドバッグ君",
    NULL,
};

/// US character names
char* lbl_803D4FDC[] = {
    "Ｃ． Ｆａｌｃｏｎ",
    "ＤＫ",
    "Ｆｏｘ",
    "Ｍｒ． Ｇａｍｅ ＆ Ｗａｔｃｈ",
    "Ｋｉｒｂｙ",
    "Ｂｏｗｓｅｒ",
    "Ｌｉｎｋ",
    "Ｌｕｉｇｉ",
    "Ｍａｒｉｏ",
    "Ｍａｒｔｈ",
    "Ｍｅｗｔｗｏ",
    "Ｎｅｓｓ",
    "Ｐｅａｃｈ",
    "Ｐｉｋａｃｈｕ",
    "Ｉｃｅ Ｃｌｉｍｂｅｒｓ",
    "Ｊｉｇｇｌｙｐｕｆｆ",
    "Ｓａｍｕｓ",
    "Ｙｏｓｈｉ",
    "Ｚｅｌｄａ",
    "Ｓｈｅｉｋ",
    "Ｆａｌｃｏ",
    "Ｙｏｕｎｇ Ｌｉｎｋ",
    "Ｄｒ． Ｍａｒｉｏ",
    "Ｒｏｙ",
    "Ｐｉｃｈｕ",
    "Ｇａｎｏｎｄｏｒｆ",
    "Ｍａｓｔｅｒｈａｎｄ",
    "ＺＡＫＯ ｏｔｏｋｏ",
    "ＺＡＫＯ ｏｎｎａ",
    "Ｇ－Ｂｏｗｓｅｒ",
    "Ｃｒａｚｙｈａｎｄ",
    "Ｓａｎｄｂａｇ",
    NULL,
};

char* lbl_803D5060[] = {
    NULL, NULL, "フォックス", NULL, NULL, NULL, NULL, NULL,     NULL,
    NULL, NULL, NULL,         NULL, NULL, NULL, NULL, "サムス", NULL,
    NULL, NULL, NULL,         NULL, NULL, NULL, NULL, NULL,     NULL,
    NULL, NULL, NULL,         NULL, NULL, NULL,
};

char* lbl_803D50E4[] = {
    NULL, NULL, "Ｆｏｘ", NULL, NULL, NULL, NULL, NULL,         NULL,
    NULL, NULL, NULL,     NULL, NULL, NULL, NULL, "Ｓａｍｕｓ", NULL,
    NULL, NULL, NULL,     NULL, NULL, NULL, NULL, NULL,         NULL,
    NULL, NULL, NULL,     NULL, NULL, NULL,
};

static struct lbl_803D5168_t {
    u8 x0;
    u8 x1;
} lbl_803D5168[] = {
    { 0x22, 0x00 }, { 0x24, 0x01 }, { 0x27, 0x02 }, { 0x38, 0x03 },
    { 0x29, 0x04 }, { 0x2A, 0x05 }, { 0x2B, 0x06 }, { 0x2C, 0x07 },
    { 0x21, 0x08 }, { 0x2D, 0x09 }, { 0x2E, 0x0A }, { 0x2F, 0x0B },
    { 0x30, 0x0C }, { 0x32, 0x0D }, { 0x28, 0x0E }, { 0x33, 0x0F },
    { 0x34, 0x10 }, { 0x36, 0x11 }, { 0x37, 0x12 }, { 0x35, 0x13 },
    { 0x26, 0x14 }, { 0x23, 0x15 }, { 0x25, 0x16 }, { 0x39, 0x17 },
    { 0x31, 0x18 }, { 0x3A, 0x19 }, { 0x48, 0x00 }, { 0 },
};

static struct {
    /* 0 */ u8 ncolors;
    /* 1 */ u8 x1;
    /* 2 */ u8 x2;
    /* 3 */ u8 x3;
} lbl_803D51A0[CKIND_PLAYABLE_COUNT] = {
    { 0x06, 0x02, 0x05, 0x04 }, { 0x05, 0x02, 0x03, 0x04 },
    { 0x04, 0x01, 0x02, 0x03 }, { 0x04, 0x01, 0x02, 0x03 },
    { 0x06, 0x03, 0x02, 0x04 }, { 0x04, 0x01, 0x02, 0x00 },
    { 0x05, 0x01, 0x02, 0x00 }, { 0x04, 0x03, 0x02, 0x00 },
    { 0x05, 0x00, 0x03, 0x04 }, { 0x05, 0x01, 0x00, 0x02 },
    { 0x04, 0x01, 0x02, 0x03 }, { 0x04, 0x00, 0x02, 0x03 },
    { 0x05, 0x00, 0x03, 0x04 }, { 0x04, 0x01, 0x02, 0x03 },
    { 0x04, 0x03, 0x00, 0x01 }, { 0x05, 0x01, 0x02, 0x03 },
    { 0x05, 0x00, 0x04, 0x03 }, { 0x06, 0x01, 0x02, 0x00 },
    { 0x05, 0x01, 0x02, 0x03 }, { 0x05, 0x01, 0x02, 0x03 },
    { 0x04, 0x01, 0x02, 0x03 }, { 0x05, 0x01, 0x02, 0x00 },
    { 0x05, 0x01, 0x02, 0x03 }, { 0x05, 0x01, 0x02, 0x03 },
    { 0x04, 0x01, 0x02, 0x03 }, { 0x05, 0x01, 0x02, 0x03 },
};

static struct ResultAnimEntry lbl_803D53A8[0x1B] = {
    {
        CKIND_CAPTAIN,
        "GmRstMCa.dat",
    },
    {
        CKIND_CLINK,
        "GmRstMCl.dat",
    },
    {
        CKIND_DONKEY,
        "GmRstMDk.dat",
    },
    {
        CKIND_DRMARIO,
        "GmRstMDr.dat",
    },
    {
        CKIND_FALCO,
        "GmRstMFc.dat",
    },
    {
        CKIND_FOX,
        "GmRstMFx.dat",
    },
    {
        CKIND_GAMEWATCH,
        "GmRstMGw.dat",
    },
    {
        CKIND_GANON,
        "GmRstMGn.dat",
    },
    {
        CKIND_KIRBY,
        "GmRstMKb.dat",
    },
    {
        CKIND_KOOPA,
        "GmRstMKp.dat",
    },
    {
        CKIND_LINK,
        "GmRstMLk.dat",
    },
    {
        CKIND_LUIGI,
        "GmRstMLg.dat",
    },
    {
        CKIND_MARS,
        "GmRstMMs.dat",
    },
    {
        CKIND_MARIO,
        "GmRstMMr.dat",
    },
    {
        CKIND_MEWTWO,
        "GmRstMMt.dat",
    },
    {
        CKIND_NESS,
        "GmRstMNs.dat",
    },
    {
        CKIND_POPONANA,
        "GmRstMPn.dat",
    },
    {
        CKIND_PEACH,
        "GmRstMPe.dat",
    },
    {
        CKIND_PIKACHU,
        "GmRstMPk.dat",
    },
    {
        CKIND_PICHU,
        "GmRstMPc.dat",
    },
    {
        CKIND_PURIN,
        "GmRstMPr.dat",
    },
    {
        CKIND_SAMUS,
        "GmRstMSs.dat",
    },
    {
        CKIND_SEAK,
        "GmRstMSk.dat",
    },
    {
        CKIND_YOSHI,
        "GmRstMYs.dat",
    },
    {
        CKIND_ZELDA,
        "GmRstMZd.dat",
    },
    {
        CKIND_EMBLEM,
        "GmRstMFe.dat",
    },
    {
        CHKIND_NONE,
        NULL,
    },
};

static struct VictoryTheme lbl_803D5480[0x1B] = {
    {
        0x0,
        0x11,
    },
    {
        0x1,
        0xD,
    },
    {
        0x2,
        0x10,
    },
    {
        0x3,
        0xF,
    },
    {
        0x4,
        0x14,
    },
    {
        0x5,
        0x16,
    },
    {
        0x6,
        0x15,
    },
    {
        0x7,
        0x16,
    },
    {
        0x8,
        0x16,
    },
    {
        0x9,
        0xE,
    },
    {
        0xA,
        0x18,
    },
    {
        0xB,
        0x17,
    },
    {
        0xC,
        0x16,
    },
    {
        0xD,
        0x18,
    },
    {
        0xE,
        0x13,
    },
    {
        0xF,
        0x18,
    },
    {
        0x10,
        0x19,
    },
    {
        0x11,
        0x1D,
    },
    {
        0x12,
        0x15,
    },
    {
        0x13,
        0x15,
    },
    {
        0x14,
        0x10,
    },
    {
        0x15,
        0x15,
    },
    {
        0x16,
        0x16,
    },
    {
        0x17,
        0xE,
    },
    {
        0x18,
        0x18,
    },
    {
        0x19,
        0x15,
    },
    {
        0x21,
        -1,
    },
};

int gm_801601C4(s8 arg0)
{
    f32 temp_f1;

    temp_f1 = (arg0 + 100) / 200.0F;
    temp_f1 *= 100.0F;
    if (temp_f1 == 50.0f) {
        return 0x7F;
    }
    if (temp_f1 > 50.0f) {
        return 127.0f * ((100.0f - temp_f1) / 50.0f);
    }
    return 0x7F;
}

int gm_80160244(s8 arg0)
{
    f32 temp_f2;

    temp_f2 = (arg0 + 100) / 200.0F;
    temp_f2 *= 100.0F;
    if (temp_f2 == 50.0f) {
        return 0x7F;
    }
    if (temp_f2 > 50.0f) {
        return 0x7F;
    }
    return (127.0f * (temp_f2 / 50.0f));
}

static inline int gm_801601C4_inner(s8 arg0)
{
    return gm_801601C4(arg0);
}

static inline int gm_801601C4_noinline(s8 arg0)
{
    return gm_801601C4_inner(arg0);
}

static inline int gm_80160244_inner(s8 arg0)
{
    return gm_80160244(arg0);
}

static inline int gm_80160244_noinline(s8 arg0)
{
    return gm_80160244_inner(arg0);
}

void gm_801602C0(s8 arg0)
{
    int a = gm_80160244(arg0);
    int b = gm_801601C4(arg0);

    PAD_STACK(8);

    lbAudioAx_80024614(b);
    lbAudioAx_800245F4(a);
}

void gm_801603B0(void)
{
    int temp_r31;
    s8 temp_r3;

    temp_r3 = gmMainLib_8015ED74();
    temp_r31 = gm_80160244_noinline(temp_r3);

    lbAudioAx_80024614(gm_801601C4_noinline(temp_r3));
    lbAudioAx_800245F4(temp_r31);
}

u32 fn_80160400(CharacterKind ckind)
{
    struct VictoryTheme* theme = lbl_803D5480;

    while (true) {
        if (theme->ckind == ckind) {
            return theme->theme_id;
        }

        {
            CharacterKind ckind;
            ckind = theme[1].ckind;
            theme++;

            if (ckind == CHKIND_NONE) {
                return -1;
            }
        }
    }
}

char* gm_80160438(s32 ckind)
{
    struct ResultAnimEntry* entry = lbl_803D53A8;
    s32 id;

    while (true) {
        id = entry->ckind;
        if (id == ckind || id == CHKIND_NONE) {
            return entry->path;
        }
        id = entry[1].ckind;
        entry++;
        if (id == CHKIND_NONE) {
            return NULL;
        }
    }
}

bool gm_80160474(CharacterKind ckind, GameModeKind scene)
{
    switch (scene) {
    case GM_CLASSIC_GOVER:
    case GM_CLASSIC:
        return lbl_803B7978[ckind];
    case GM_ADVENTURE_GOVER:
    case GM_ADVENTURE:
        return lbl_803B79BC[ckind];
    default:
        return lbl_803B7A00[ckind];
    }
}

char* gm_801604DC(CharacterKind ckind, GameModeKind scene)
{
    s32 var_r3;

    switch (scene) {
    case GM_CLASSIC_GOVER:
    case GM_CLASSIC:
        var_r3 = lbl_803B7978[ckind];
        break;
    case GM_ADVENTURE_GOVER:
    case GM_ADVENTURE:
        var_r3 = lbl_803B79BC[ckind];
        break;
    default:
        var_r3 = lbl_803B7A00[ckind];
        break;
    }
    return un_8030813C(var_r3, scene) + 4;
}

char* gm_80160564(CharacterKind ckind, GameModeKind scene)
{
    s32 var_r3;

    switch (scene) {
    case GM_CLASSIC_GOVER:
    case GM_CLASSIC:
        var_r3 = lbl_803B7978[ckind];
        break;
    case GM_ADVENTURE_GOVER:
    case GM_ADVENTURE:
        var_r3 = lbl_803B79BC[ckind];
        break;
    default:
        var_r3 = lbl_803B7A00[ckind];
        break;
    }
    return un_8030813C(var_r3, scene) + 0x24;
}

u8 fn_801605EC(s32 arg0)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (arg0 == lbl_803B78C8[i].ckind) {
            return lbl_803B78C8[i].idx;
        }
    }
    return NUM_UNLOCKABLE_CHARACTERS;
}

s8 gm_80160638(s32 arg0)
{
    return fn_801605EC(gm_80164024(arg0));
}

static inline u8 fn_801606A8_inline(int arg0)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (arg0 == lbl_803B78C8[i].idx) {
            return lbl_803B78C8[i].ckind;
        }
    }
    return CKIND_GANON;
}

u8 fn_801606A8(int arg0)
{
    return gm_8016400C(fn_801606A8_inline(arg0));
}

u8 fn_80160710(int arg0)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (arg0 == lbl_803B78C8[i].idx) {
            return lbl_803B78C8[i].x2;
        }
    }
    return 0x42;
}

int gm_8016075C(CharacterKind ckind)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (ckind == lbl_803B78C8[i].ckind) {
            return lbl_803B78C8[i].x4;
        }
    }
    return 0x148;
}

u8 fn_801607A8(int arg0)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (arg0 == lbl_803B790C[i][0]) {
            return lbl_803B790C[i][1];
        }
    }
    return 0x6F;
}

u8 fn_801607F4(int arg0)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (arg0 == lbl_803B790C[i][1]) {
            return lbl_803B790C[i][2];
        }
    }
    return 0x42U;
}

u8 fn_80160840(u8 arg0)
{
    if (arg0 >= 4) {
        return 4;
    }
    return arg0;
}

u32 gm_80160854(u8 slot, u8 team, u8 is_teams, u8 slot_type)
{
    u8 color_idx;

    if (is_teams != 0) {
        switch (team) { /* switch 1; irregular */
        case 0:         /* switch 1 */
            if (slot_type == Gm_PKind_Human) {
                color_idx = 0;
            } else {
                color_idx = 5;
            }
            return color_idx;
        case 1: /* switch 1 */
            if (slot_type == Gm_PKind_Human) {
                color_idx = 1;
            } else {
                color_idx = 6;
            }
            return color_idx;
        case 2: /* switch 1 */
            if (slot_type == Gm_PKind_Human) {
                color_idx = 3;
            } else {
                color_idx = 8;
            }
            return color_idx;
        case 3: /* switch 1 */
            if (slot_type == Gm_PKind_Human) {
                color_idx = 2;
            } else {
                color_idx = 7;
            }
            return color_idx;
        case 4: /* switch 1 */
            return 4U;
        }
    } else {
        if (slot_type != Gm_PKind_Human) {
            return 4U;
        }
        switch (slot) { /* irregular */
        case 0:
            return 0U;
        case 1:
            return 1U;
        case 2:
            return 2U;
        case 3:
            return 3U;
        }
    }
    return 0;
}

GXColor gm_80160968(u8 arg0)
{
    return lbl_803B7864[arg0];
}

const char* gm_80160980_noinline(u8 ckind);
const char* gm_80160980_noinline(u8 ckind)
{
    return gm_80160980(ckind);
}

const char* gm_80160980_noinline2(u8 ckind);
const char* gm_80160980_noinline2(u8 ckind)
{
    return gm_80160980_noinline(ckind);
}

const char* gm_80160980_noinline3(u8 ckind);
const char* gm_80160980_noinline3(u8 ckind)
{
    return gm_80160980_noinline2(ckind);
}

/// Get SJIS character name for a given CharacterKind
const char* gm_80160980(u8 ckind)
{
    if (lbLang_IsSavedLanguageUS()) {
        return lbl_803D4FDC[ckind];
    } else {
        return lbl_803D4D74[ckind];
    }
}

const char* fn_801609E0_noinline(u8 ckind);
const char* fn_801609E0_noinline(u8 ckind)
{
    return fn_801609E0(ckind);
}

const char* fn_801609E0_noinline2(u8 ckind);
const char* fn_801609E0_noinline2(u8 ckind)
{
    return fn_801609E0_noinline(ckind);
}

const char* fn_801609E0_noinline3(u8 ckind);
const char* fn_801609E0_noinline3(u8 ckind)
{
    return fn_801609E0_noinline2(ckind);
}

const char* fn_801609E0(u8 ckind)
{
    if (lbLang_IsSavedLanguageUS()) {
        if (lbl_803D50E4[ckind] != NULL) {
            return lbl_803D50E4[ckind];
        }
        return lbl_803D4FDC[ckind];
    } else {
        if (lbl_803D5060[ckind] != NULL) {
            return lbl_803D5060[ckind];
        }
        return lbl_803D4D74[ckind];
    }
}

const char* gm_80160A60(int arg0)
{
    u8 ckind;

    if (Player_GetPlayerSlotType(arg0) != Gm_PKind_NA) {
        ckind = Player_GetPlayerCharacter(arg0);
        if (ckind == CKIND_ZELDA || ckind == CKIND_SEAK) {
            if (Player_80036394(arg0) == FTKIND_SEAK) {
                if (lbLang_IsSavedLanguageUS()) {
                    return lbl_803D4FDC[CKIND_SEAK];
                } else {
                    return lbl_803D4D74[CKIND_SEAK];
                }
            } else {
                if (lbLang_IsSavedLanguageUS()) {
                    return lbl_803D4FDC[CKIND_ZELDA];
                } else {
                    return lbl_803D4D74[CKIND_ZELDA];
                }
            }
        }
        if (lbLang_IsSavedLanguageUS()) {
            return lbl_803D4FDC[ckind];
        } else {
            return lbl_803D4D74[ckind];
        }
    }
    return NULL;
}

void gm_80160B40(HSD_Text* text, u8 ckind, u8 arg2)
{
    HSD_Text* tmp_text = text;
    u8 tmp_ckind = ckind;
    f32 var_f31;
    const char* str;

    if (lbLang_IsSavedLanguageUS()) {
        tmp_text->default_kerning = 1;
    }
    str = arg2 ? fn_801609E0(tmp_ckind) : gm_80160980(tmp_ckind);
    if (lbLang_IsSavedLanguageUS()) {
        bool tmp = arg2 && lbl_803D50E4[tmp_ckind] != NULL;
        var_f31 = tmp ? lbl_803B7784[tmp_ckind] : lbl_803B767C[tmp_ckind];
    } else {
        bool tmp = arg2 && lbl_803D5060[tmp_ckind] != NULL;
        var_f31 = tmp ? lbl_803B7700[tmp_ckind] : lbl_803B75F8[tmp_ckind];
    }
    HSD_SisLib_803A6B98(tmp_text, 0.0F, 0.0F, str);
    tmp_text->font_size.x *= var_f31;
}

void gm_80160C90(HSD_Text* text, u8 fighter_id, bool arg2)
{
    // Some sort of text rendering based on the fighter ID and a second bool
    f32 var_f31;
    s32 var_r5;
    const char* var_r29;

    if (lbLang_IsSavedLanguageUS() != 0) {
        text->default_kerning = 1;
    }

    var_r29 = ((u8) arg2) ? fn_801609E0_noinline3(fighter_id)
                          : gm_80160980_noinline3(fighter_id);

    if (lbLang_IsSavedLanguageUS() != 0) {
        var_r5 = 0;
        if ((u8) arg2 != 0 && lbl_803D50E4[fighter_id] != 0) {
            var_r5 = 1;
        }

        if (var_r5 != 0) {
            var_f31 = lbl_803B7784[fighter_id];
        } else {
            var_f31 = lbl_803B767C[fighter_id];
        }
    } else {
        var_r5 = 0;
        if ((u8) arg2 != 0 && lbl_803D5060[fighter_id] != 0) {
            var_r5 = 1;
        }

        if (var_r5 != 0) {
            var_f31 = lbl_803B7700[fighter_id];
        } else {
            var_f31 = lbl_803B75F8[fighter_id];
        }
    }

    HSD_SisLib_803A7548(text,
                        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, var_r29, var_r5),
                        var_f31, 1.0f);
}

void fn_80160DE8(HSD_JObj* arg0, u8 arg1, s32 arg2, u8 arg3, f32 farg0,
                 f32 farg1)
{
    const char* str;
    f32 size;
    s32 is_us = lbLang_IsSavedLanguageUS();

    if (is_us != 0) {
        ((u8*) arg0)[0x49] = 1;
    }
    str = ((u8) arg2) ? fn_801609E0_noinline3(arg3)
                      : gm_80160980_noinline3(arg3);

    if (is_us != 0) {
        if (arg3 != 0 && lbl_803D50E4[arg1] != NULL) {
            size = lbl_803B75F8[arg1 + 0x63];
        } else {
            size = lbl_803B75F8[arg1 + 0x21];
        }
    } else {
        if (arg3 != 0 && lbl_803D5060[arg1] != NULL) {
            size = lbl_803B75F8[arg1 + 0x42];
        } else {
            size = lbl_803B75F8[arg1];
        }
    }
    HSD_SisLib_803A70A0((HSD_Text*) arg0, arg2, (char*) str);
    HSD_SisLib_803A7548((HSD_Text*) arg0, arg2, size * farg0, farg1);
}

f32 fn_80160F58(u8 ckind)
{
    f32 result;
    if (lbLang_IsSavedLanguageUS()) {
        result = lbl_803D50E4[ckind] != NULL ? lbl_803B7784[ckind]
                                             : lbl_803B767C[ckind];
    } else {
        result = lbl_803D5060[ckind] != NULL ? lbl_803B7700[ckind]
                                             : lbl_803B75F8[ckind];
    }
    return result;
}

s32 fn_80161004(MatchEnd* match_end)
{
    s32 max = 0;
    s32 i;

    if (match_end->is_teams == 1) {
        for (i = 0; i < 5; i++) {
            struct MatchTeamData* t = &match_end->team_standings[i];
            if (match_end->team_standings[i].active != 0 &&
                (s32) t->is_big_loser > max)
            {
                max = t->is_big_loser;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            struct MatchPlayerData* p = &match_end->player_standings[i];
            if (match_end->player_standings[i].slot_type != 3 &&
                (s32) p->is_big_loser > max)
            {
                max = p->is_big_loser;
            }
        }
    }
    return max;
}

s32 fn_80161154(MatchEnd* arg0)
{
    u8 spC[4];
    MatchPlayerData* var_r31;
    s32 idx;
    s32 cnt;
    s32 var_r3 = fn_80161004(arg0);

    idx = 4;
    cnt = 0;
    if (arg0->is_teams == 1) {
        if (arg0->player_standings[0].slot_type != 3 &&
            arg0->team_standings[arg0->player_standings[0].team].is_big_loser ==
                var_r3) {
            spC[0] = 1;
            cnt = 1;
            idx = 0;
        } else {
            spC[0] = 0;
        }
        if (arg0->player_standings[1].slot_type != 3 &&
            arg0->team_standings[arg0->player_standings[1].team].is_big_loser ==
                var_r3) {
            spC[1] = 1;
            cnt = 1;
            idx = 1;
        } else {
            spC[1] = 0;
        }
        if (arg0->player_standings[2].slot_type != 3 &&
            arg0->team_standings[arg0->player_standings[2].team].is_big_loser ==
                var_r3) {
            spC[2] = 1;
            cnt = 1;
            idx = 2;
        } else {
            spC[2] = 0;
        }
        if (arg0->player_standings[3].slot_type != 3 &&
            arg0->team_standings[arg0->player_standings[3].team].is_big_loser ==
                var_r3) {
            spC[3] = 1;
            cnt = 1;
            idx = 3;
        } else {
            spC[3] = 0;
        }
    } else {
        if (arg0->player_standings[0].slot_type != 3 &&
            arg0->player_standings[0].is_big_loser == var_r3) {
            if (idx != 4) {
                cnt = 1;
            } else {
                idx = 0;
            }
            spC[0] = 1;
        } else {
            spC[0] = 0;
        }
        if (arg0->player_standings[1].slot_type != 3 &&
            arg0->player_standings[1].is_big_loser == var_r3) {
            if (idx != 4) {
                cnt = 1;
            } else {
                idx = 1;
            }
            spC[1] = 1;
        } else {
            spC[1] = 0;
        }
        if (arg0->player_standings[2].slot_type != 3 &&
            arg0->player_standings[2].is_big_loser == var_r3) {
            if (idx != 4) {
                cnt = 1;
            } else {
                idx = 2;
            }
            spC[2] = 1;
        } else {
            spC[2] = 0;
        }
        if (arg0->player_standings[3].slot_type != 3 &&
            arg0->player_standings[3].is_big_loser == var_r3) {
            if (idx != 4) {
                cnt = 1;
            } else {
                idx = 3;
            }
            spC[3] = 1;
        } else {
            spC[3] = 0;
        }
    }
    if (cnt == 0) {
        return idx;
    }

    idx = 4;
    if (spC[0]) {
        if (idx == 4) {
            idx = 0;
        } else if (arg0->player_standings[idx].x20 >
                   arg0->player_standings[0].x20) {
            idx = 0;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[1]) {
        if (idx == 4) {
            idx = 1;
        } else if (arg0->player_standings[idx].x20 >
                   arg0->player_standings[1].x20) {
            idx = 1;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[2]) {
        if (idx == 4) {
            idx = 2;
        } else if (arg0->player_standings[idx].x20 >
                   arg0->player_standings[2].x20) {
            idx = 2;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[3]) {
        if (idx == 4) {
            idx = 3;
        } else if (arg0->player_standings[idx].x20 >
                   arg0->player_standings[3].x20) {
            idx = 3;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    cnt = 0;
    if (spC[0] && idx != 0) {
        if (arg0->player_standings[0].x20 == var_r31->x20) {
            cnt = 1;
        } else {
            spC[0] = 0;
        }
    }
    if (spC[1] && idx != 1) {
        if (arg0->player_standings[1].x20 == var_r31->x20) {
            cnt += 1;
        } else {
            spC[1] = 0;
        }
    }
    if (spC[2] && idx != 2) {
        if (arg0->player_standings[2].x20 == var_r31->x20) {
            cnt += 1;
        } else {
            spC[2] = 0;
        }
    }
    if (spC[3] && idx != 3) {
        if (arg0->player_standings[3].x20 == var_r31->x20) {
            cnt += 1;
        } else {
            spC[3] = 0;
        }
    }
    if (cnt == 0) {
        return idx;
    }

    idx = 4;
    if (spC[0]) {
        if (idx == 4) {
            idx = 0;
        } else if (arg0->player_standings[idx].x24 <
                   arg0->player_standings[0].x24) {
            idx = 0;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[1]) {
        if (idx == 4) {
            idx = 1;
        } else if (arg0->player_standings[idx].x24 <
                   arg0->player_standings[1].x24) {
            idx = 1;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[2]) {
        if (idx == 4) {
            idx = 2;
        } else if (arg0->player_standings[idx].x24 <
                   arg0->player_standings[2].x24) {
            idx = 2;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[3]) {
        if (idx == 4) {
            idx = 3;
        } else if (arg0->player_standings[idx].x24 <
                   arg0->player_standings[3].x24) {
            idx = 3;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    cnt = 0;
    if (spC[0] && idx != 0) {
        if (arg0->player_standings[0].x24 == var_r31->x24) {
            cnt = 1;
        } else {
            spC[0] = 0;
        }
    }
    if (spC[1] && idx != 1) {
        if (arg0->player_standings[1].x24 == var_r31->x24) {
            cnt += 1;
        } else {
            spC[1] = 0;
        }
    }
    if (spC[2] && idx != 2) {
        if (arg0->player_standings[2].x24 == var_r31->x24) {
            cnt += 1;
        } else {
            spC[2] = 0;
        }
    }
    if (spC[3] && idx != 3) {
        if (arg0->player_standings[3].x24 == var_r31->x24) {
            cnt += 1;
        } else {
            spC[3] = 0;
        }
    }
    if (cnt == 0) {
        return idx;
    }

    idx = 4;
    if (spC[0]) {
        if (idx == 4) {
            idx = 0;
        } else if (arg0->player_standings[idx].x44 >
                   arg0->player_standings[0].x44) {
            idx = 0;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[1]) {
        if (idx == 4) {
            idx = 1;
        } else if (arg0->player_standings[idx].x44 >
                   arg0->player_standings[1].x44) {
            idx = 1;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[2]) {
        if (idx == 4) {
            idx = 2;
        } else if (arg0->player_standings[idx].x44 >
                   arg0->player_standings[2].x44) {
            idx = 2;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[3]) {
        if (idx == 4) {
            idx = 3;
        } else if (arg0->player_standings[idx].x44 >
                   arg0->player_standings[3].x44) {
            idx = 3;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    cnt = 0;
    if (spC[0] && idx != 0) {
        if (arg0->player_standings[0].x44 == var_r31->x44) {
            cnt = 1;
        } else {
            spC[0] = 0;
        }
    }
    if (spC[1] && idx != 1) {
        if (arg0->player_standings[1].x44 == var_r31->x44) {
            cnt += 1;
        } else {
            spC[1] = 0;
        }
    }
    if (spC[2] && idx != 2) {
        if (arg0->player_standings[2].x44 == var_r31->x44) {
            cnt += 1;
        } else {
            spC[2] = 0;
        }
    }
    if (spC[3] && idx != 3) {
        if (arg0->player_standings[3].x44 == var_r31->x44) {
            cnt += 1;
        } else {
            spC[3] = 0;
        }
    }
    if (cnt == 0) {
        return idx;
    }

    idx = 4;
    if (spC[0]) {
        if (idx == 4) {
            idx = 0;
        } else if (arg0->player_standings[idx].x50 <
                   arg0->player_standings[0].x50) {
            idx = 0;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[1]) {
        if (idx == 4) {
            idx = 1;
        } else if (arg0->player_standings[idx].x50 <
                   arg0->player_standings[1].x50) {
            idx = 1;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[2]) {
        if (idx == 4) {
            idx = 2;
        } else if (arg0->player_standings[idx].x50 <
                   arg0->player_standings[2].x50) {
            idx = 2;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    if (spC[3]) {
        if (idx == 4) {
            idx = 3;
        } else if (arg0->player_standings[idx].x50 <
                   arg0->player_standings[3].x50) {
            idx = 3;
        }
        var_r31 = &arg0->player_standings[idx];
    }
    cnt = 0;
    if (spC[0] && idx != 0) {
        if (arg0->player_standings[0].x50 == var_r31->x50) {
            cnt = 1;
        } else {
            spC[0] = 0;
        }
    }
    if (spC[1] && idx != 1) {
        if (arg0->player_standings[1].x50 == var_r31->x50) {
            cnt += 1;
        } else {
            spC[1] = 0;
        }
    }
    if (spC[2] && idx != 2) {
        if (arg0->player_standings[2].x50 == var_r31->x50) {
            cnt += 1;
        } else {
            spC[2] = 0;
        }
    }
    if (spC[3] && idx != 3) {
        if (arg0->player_standings[3].x50 == var_r31->x50) {
            cnt += 1;
        } else {
            spC[3] = 0;
        }
    }
    if (cnt == 0) {
        return idx;
    }
    if (spC[0]) {
        return 0;
    }
    if (spC[1]) {
        return 1;
    }
    if (spC[2]) {
        return 2;
    }
    if (spC[3]) {
        var_r3 = 3;
    }
    return var_r3;
}

struct gm_stats {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ u32 unk20;
    /* 0x24 */ u32 unk24;
    /* 0x28 */ u32 unk28;
    /* 0x2C */ u32 unk2C;
    /* 0x30 */ u32 unk30;
    /* 0x34 */ u32 unk34;
    /* 0x38 */ u32 unk38;
    /* 0x3C */ u32 unk3C;
    /* 0x40 */ u32 unk40;
};

void fn_80161C90(MatchEnd* arg0, int arg1, u16* arg2)
{
    struct gm_stats* s = (struct gm_stats*) arg2;
    MatchPlayerData* p = &arg0->player_standings[arg1];
    u32 count;

    s->unk0 = MIN(s->unk0 + p->self_destructs, 0xFFFF);
    s->unk4 = MIN(s->unk4 + p->x38, 0xFFFFFFFFU);
    s->unk8 = MIN(s->unk8 + p->x3C, 0xFFFFFFFFU);
    s->unkC = MIN(s->unkC + p->x40, 0xFFFFFFFFU);
    s->unk10 = MIN(s->unk10 + p->x44, 0xFFFFFFFFU);
    s->unk14 = MIN(s->unk14 + p->x48, 0xFFFFFFFFU);
    if (s->unk18 < p->x4C) {
        s->unk18 = p->x4C;
    }
    s->unk1A = MIN(s->unk1A + 1, 0xFFFF);
    if (arg1 == fn_80165548(arg0, fn_80165418(arg0), fn_801654A0(arg0))) {
        s->unk1C = MIN(s->unk1C + 1, 0xFFFF);
    }
    if (arg1 == fn_80161154(arg0)) {
        s->unk1E = MIN(s->unk1E + 1, 0xFFFF);
    }
    s->unk20 = MIN(s->unk20 + arg0->frame_count / 60, 0xFFFFFFFFU);
    count = 0;
    if (arg0->player_standings[0].slot_type != 3) {
        count = 1;
    }
    if (arg0->player_standings[1].slot_type != 3) {
        count += 1;
    }
    if (arg0->player_standings[2].slot_type != 3) {
        count += 1;
    }
    if (arg0->player_standings[3].slot_type != 3) {
        count += 1;
    }
    count = s->unk24 + count;
    if (count > 0xFFFFFFFFU) {
        count = 0xFFFF;
    }
    s->unk24 = count;
    s->unk28 = MIN(s->unk28 + p->x50, 0xFFFFFFFFU);
    gmMainLib_8015EDBC()->x10 =
        MIN(p->x50 + gmMainLib_8015EDBC()->x10, 0xFFFFFFFFU);
    s->unk2C = MIN(s->unk2C + p->x54, 0xFFFFFFFFU);
    s->unk30 = MIN(s->unk30 + p->x58, 0xFFFFFFFFU);
    s->unk34 = MIN(s->unk34 + p->x5C, 0xFFFFFFFFU);
    if (arg0->x5 == 2) {
        s->unk38 = MIN(s->unk38 + p->x60, 0xFFFFFFFFU);
        s->unk3C = MIN(s->unk3C + p->x64, 0xFFFFFFFFU);
        s->unk40 = MIN(s->unk40 + p->x68, 0xFFFFFFFFU);
    }
}

void fn_80162068(MatchEnd* match_end)
{
    s32 i;
    s32 j;
    struct MatchPlayerData* pdata_i;
    struct MatchPlayerData* pdata_j;
    struct FighterData* fd;
    s32 sum;

    for (i = 0; i < 4; i++) {
        pdata_i = &match_end->player_standings[i];
        if (pdata_i->slot_type == 3) {
            continue;
        }
        fd = GetPersistentFighterData(gm_80164024(pdata_i->character_kind));
        for (j = 0; j < 4; j++) {
            pdata_j = &match_end->player_standings[j];
            if (i == j || pdata_j->slot_type == 3) {
                continue;
            }
            if (pdata_i->kills[j] +
                    fd->fighter_kos[gm_80164024(pdata_j->character_kind)] >
                0xFFFF)
            {
                sum = 0xFFFF;
            } else {
                sum = pdata_i->kills[j] +
                      fd->fighter_kos[gm_80164024(pdata_j->character_kind)];
            }
            fd->fighter_kos[gm_80164024(pdata_j->character_kind)] = (u16) sum;
        }
        fn_80161C90(match_end, i, &fd->sd_count);
    }
}

s32 fn_80162170(MatchEnd* arg0)
{
    s32 i;
    s32 j;
    MatchPlayerData* p;

    for (i = 0; i < 4; i++) {
        p = &arg0->player_standings[i];
        if (p->slot_type != 3) {
            u8 ck = p->x4;
            if (ck != 0x78) {
                struct NameTagData* nt = GetPersistentNameData(ck);
                for (j = 0; j < 4; j++) {
                    if (j != i && arg0->player_standings[j].slot_type != 3) {
                        u8 ock = arg0->player_standings[j].x4;
                        if (ock != 0x78) {
                            s32 v = p->kills[j] + nt->vs_kos[ock];
                            if (v > 0xFFFF) {
                                v = 0xFFFF;
                            }
                            nt->vs_kos[ock] = v;
                        }
                    }
                }
                {
                    u32* pt = &nt->play_time_by_fighter[gm_80164024(
                        p->character_kind)];
                    *pt = MIN(*pt + arg0->frame_count / 60, 0xFFFFFFFFU);
                }
                fn_80161C90(arg0, i, &nt->sd_count);
            }
        }
    }
}

s32 gm_801623A4(MatchEnd* arg0)
{
    fn_80162068(arg0);
    return fn_80162170(arg0);
}

int gm_801623D8(void)
{
    return *(s32*) gmMainLib_8015CCF0();
}

void gm_801623FC(int arg0)
{
    u32* temp_r30;
    u32 var_r29;
    u32* temp_r31;
    u32* temp_r3;

    var_r29 = arg0;
    temp_r30 = gmMainLib_8015CCF0();
    temp_r31 = gmMainLib_8015CCFC();
    temp_r3 = &gmMainLib_8015EDBC()->x14;
    if (var_r29 > *temp_r31) {
        *temp_r31 = var_r29;
    }
    if (var_r29 > *temp_r3) {
        *temp_r3 = var_r29;
    }
    if (var_r29 > 0x270F) {
        var_r29 = 0x270F;
    }
    *temp_r30 = (s32) var_r29;
}

s32 gm_8016247C(s32 arg0)
{
    u32 var_r4;
    u32 var_r3;
    u32 var_r28;
    u32 var_r29;
    u32* temp_r31;
    u32* temp_r5;
    u32* temp_r30_2;
    u32* temp_r3;
    u32 temp_r0;
    u32 temp_r0_2;
    s32 temp_r29 = *gmMainLib_8015CCF0();
    u32* temp_r30 = gmMainLib_8015CCFC();
    s32 ret;

    temp_r5 = &gmMainLib_8015EDBC()->x14;

    var_r4 = MAX(-1U, *temp_r30 + arg0);
    *temp_r30 = var_r4;

    var_r3 = MAX(-1U, *temp_r5 + arg0);
    *temp_r5 = var_r3;

    var_r28 = MIN(0x270FU, temp_r29 + arg0);
    ret = (s32) var_r28;
    var_r29 = var_r28;

    temp_r30_2 = gmMainLib_8015CCF0();
    temp_r31 = gmMainLib_8015CCFC();
    temp_r3 = &gmMainLib_8015EDBC()->x14;

    if (var_r28 > (u32) *temp_r31) {
        *temp_r31 = var_r28;
    }
    if (var_r28 > (u32) *temp_r3) {
        *temp_r3 = var_r28;
    }
    if (var_r28 > 0x270FU) {
        var_r29 = 0x270FU;
    }
    *temp_r30_2 = var_r29;
    return (s32) ret;
}

void gm_80162574(u8 arg0, u8 arg1)
{
    u16* ptr;
    u32 val;

    if (arg1 == 7) {
        return;
    }
    if (arg1 == 8) {
        return;
    }

    // First counter
    ptr = (u16*) gmMainLib_8015CFB4(gm_80164024(arg0));
    val = *ptr + 1;
    if (val > 0xFFFF) {
        val = 0xFFFF;
    }
    *ptr = val;

    // Second counter
    ptr = &gmMainLib_8015EDBC()->x18[gm_80164024(arg0)];
    val = *ptr + 1;
    if (val > 0xFFFF) {
        val = 0xFFFF;
    }
    *ptr = val;
}

void gm_8016260C(u8 arg0, u8 arg1)
{
    u32* counter = NULL;

    if ((u8) (arg1 - 7) <= 1) {
        u32* p = gmMainLib_GetMatchResetCounter();
        *p = MIN(*p + 1, 0xFFFFFFFFU);
        return;
    }
    if (gm_801A4310() == 0x1F) {
        counter = gmMainLib_8015CD5C();
    } else {
        switch ((s32) arg0) {
        case 0:
            counter = gmMainLib_GetTimeMatchTotal();
            break;
        case 1:
            counter = gmMainLib_GetStockMatchTotal();
            break;
        case 2:
            counter = gmMainLib_GetCoinMatchTotal();
            {
                struct gmm_retval_EDBC* q = gmMainLib_8015EDBC();
                q->x4 = MIN(q->x4 + 1, 0xFFFFFFFFU);
            }
            break;
        case 3:
            counter = gmMainLib_GetBonusMatchTotal();
            break;
        }
    }
    *counter = MIN(*counter + 1, 0xFFFFFFFFU);
    {
        struct gmm_retval_ED98* a = gmMainLib_8015ED98();
        a->x0 = MIN(a->x0 + 1, 0xFFFFFFFFU);
    }
    {
        struct gmm_retval_EDB0* b = gmMainLib_8015EDB0();
        b->x0 = MIN((u32) b->x0 + 1, 0xFFFFFFFFU);
    }
    {
        struct gmm_retval_EDBC* c = gmMainLib_8015EDBC();
        c->x0 = MIN((u32) c->x0 + 1, 0xFFFFFFFFU);
    }
}

u32 gm_GetVsPlayMatchTotal(void)
{
    u32 tmp = *(u32*) gmMainLib_GetTimeMatchTotal() +
              *(u32*) gmMainLib_GetStockMatchTotal() +
              *(u32*) gmMainLib_GetCoinMatchTotal() +
              *(u32*) gmMainLib_GetBonusMatchTotal() +
              *(u32*) gmMainLib_8015CD5C();
    return tmp;
}

u32 gm_80162800(MatchEnd* arg0)
{
    u32 count;
    u32* temp_r3;
    u32 sum;
    u32 i;

    temp_r3 = gmMainLib_GetVsPlayContestants();
    count = 0;
    for (i = 0; i < 6; i++) {
        if (arg0->player_standings[i].slot_type == 0) {
            count++;
        }
    }
    sum = *temp_r3 + count;
    *temp_r3 = (sum > -1) ? -1 : sum;
    return count;
}

void gm_801628C4(u32 arg0, u32 arg1)
{
    u32* temp_r3;
    u32 var_r4;
    struct gmm_retval_ED98* temp_r3_3;

    temp_r3 = gmMainLib_GetVsPlayTime();
    var_r4 = *temp_r3 + arg0;
    *temp_r3 = (var_r4 > (u32) -1) ? (u32) -1 : var_r4;

    temp_r3 = gmMainLib_GetCombinedVSPlayTime();
    var_r4 = (0, *temp_r3 + (arg0 * arg1));
    *temp_r3 = (var_r4 > (u32) -1) ? (u32) -1 : var_r4;

    temp_r3_3 = gmMainLib_8015ED98();
    var_r4 = temp_r3_3->x4 + (arg0 * arg1);
    temp_r3_3->x4 = (var_r4 > (u32) -1) ? (u32) -1 : var_r4;
}

long gm_80162968(u32 seconds)
{
    u32* ptr = gmMainLib_GetSingleplayerTime();

    *ptr = ((*ptr + seconds) > -1) ? -1 : (*ptr + seconds);
}

long gm_801629B4(s32 amount)
{
    u32* ptr = gmMainLib_8015CD80();

    *ptr = ((*ptr + amount) > -1) ? -1 : (*ptr + amount);
}

long gm_GetPlayTime(void)
{
    u32 a;
    u32 b;

    a = *(u32*) gmMainLib_GetVsPlayTime();
    b = *(u32*) gmMainLib_GetSingleplayerTime();
    return a + b > -1 ? -1 : a + b;
}

long gm_80162A4C(s32 amount)
{
    u32* ptr;

    ptr = gmMainLib_GetTotalDamage();
    *ptr = ((*ptr + amount) > -1) ? -1 : (*ptr + amount);
}

struct gmm_x1868_1A8_t* gm_80162A98(s32 arg0)
{
    struct gmm_x1868_1A8_t* temp_r3;
    u32 var_r31;
    s32* temp_r3_2 = gmMainLib_GetKOTotal();

    *temp_r3_2 = MAX(*temp_r3_2 + arg0, -1U);

    var_r31 = MAX((u32) (arg0 + gmMainLib_8015EDBC()->xC), -1U);

    gmMainLib_8015EDBC()->xC = var_r31;

    var_r31 = MAX((u32) (arg0 + gmMainLib_8015EDC8()->x0), -1U);

    temp_r3 = gmMainLib_8015EDC8();
    temp_r3->x0 = var_r31;
    return temp_r3;
}

void gm_80162B4C(s32 amount)
{
    u32* ptr;
    u32 sum;

    ptr = gmMainLib_GetSelfDestructTotal();
    sum = *ptr + amount;
    *ptr = (sum > (u32) -1) ? (u32) -1 : sum;
}

void gm_IncrementPowerCount(void)
{
    u32 result;
    u32 val;
    u32* ptr;

    ptr = gmMainLib_GetPowerCount();
    val = *ptr;
    result = (val + 1 > (u32) -1) ? (u32) -1 : val + 1;
    *ptr = result;
}

int gm_80162BD8(u8 arg0)
{
    return *gmMainLib_8015D0C0(arg0);
}

bool fn_80162BFC(s8 ckind, int arg1)
{
    int* temp_r3;

    temp_r3 = (int*) gmMainLib_8015D0C0(gm_80164024((u8) ckind));
    if ((u32) *temp_r3 < (u32) arg1) {
        *temp_r3 = arg1;
        return true;
    }
    return false;
}

s32 gm_80162C48(void)
{
    s32 var_r0;
    s32 i;
    s32 var_r29;

    var_r29 = 0;
    for (i = 0; i < 0x19; i++) {
        if ((u32) (var_r29 + *gmMainLib_8015D0C0(i)) > -1U) {
            var_r0 = -1;
        } else {
            var_r0 = var_r29 + *gmMainLib_8015D0C0(i);
        }
        var_r29 = var_r0;
    };
    return var_r29;
}

bool fn_80162CCC(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D0D8(i)) {
            return true;
        }
    }
    return false;
}

bool gm_80162D1C(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (!gmMainLib_8015D0D8(i)) {
            return false;
        }
    }
    return true;
}

u8 gm_80162D6C(void)
{
    s32 i;
    u8 min;

    i = 0;
    min = 4;
    do {
        if (min > (u8) *gmMainLib_8015D194((u8) i)) {
            min = *gmMainLib_8015D194((u8) i);
        }
        i += 1;
    } while (i < 0x19);

    return min;
}

int gm_80162DD4(u8 i)
{
    return *gmMainLib_8015D1E8(i);
}

s32 fn_80162DF8(u8 ckind, u32 arg1)
{
    s32* temp_r3;

    temp_r3 = gmMainLib_8015D1E8(gm_80164024(ckind));
    if (*temp_r3 < arg1) {
        *temp_r3 = arg1;
        return 1;
    }
    return 0;
}

s32 gm_80162E44(void)
{
    s32 var_r0;
    int i;
    s32 var_r29;

    var_r29 = 0;
    for (i = 0; i < 0x19; i++) {
        // Could maybe be replaced by
        // MIN((u32) (var_r29 + *gmMainLib_8015D1E8((u8) i)), (u32)-1)?
        // Doing so breaks 100% match tho, so eh
        if ((u32) (var_r29 + *gmMainLib_8015D1E8((u8) i)) > (u32) -1) {
            var_r0 = -1;
        } else {
            var_r0 = var_r29 + *gmMainLib_8015D1E8((u8) i);
        }
        var_r29 = var_r0;
    };
    return var_r29;
}

bool gm_80162EC8(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D200(i)) {
            return true;
        }
    }
    return false;
}

bool gm_80162F18(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (!gmMainLib_8015D200(i)) {
            return false;
        }
    }
    return true;
}

u8 gm_80162F68(void)
{
    s32 i;
    u8 min;

    i = 0;
    min = 4;
    do {
        if (min > (u8) *gmMainLib_8015D2BC((u8) i)) {
            min = *gmMainLib_8015D2BC((u8) i);
        }
        i += 1;
    } while (i < 0x19);

    return min;
}

int gm_80162FD0(u8 i)
{
    return *gmMainLib_8015D310(i);
}

bool fn_80162FF4(u8 ckind, u32 arg1)
{
    s32* temp_r3;

    temp_r3 = gmMainLib_8015D310(gm_80164024(ckind));
    if (*temp_r3 < arg1) {
        *temp_r3 = arg1;
        return true;
    }
    return false;
}

s32 gm_80163040(void)
{
    s32 var_r0;
    int i;
    s32 var_r29;

    var_r29 = 0;
    for (i = 0; i < 0x19; i++) {
        if ((u32) (var_r29 + *gmMainLib_8015D310((u8) i)) > (u32) -1) {
            var_r0 = -1;
        } else {
            var_r0 = var_r29 + *gmMainLib_8015D310((u8) i);
        }
        var_r29 = var_r0;
    };
    return var_r29;
}

bool fn_801630C4(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D328(i)) {
            return true;
        }
    }
    return false;
}

bool gm_80163114(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (!gmMainLib_8015D328(i)) {
            return false;
        }
    }
    return true;
}

u8 gm_80163164(void)
{
    s32 i;
    u8 min;

    i = 0;
    min = 4;
    do {
        if (min > (u8) *gmMainLib_8015D3E4((u8) i)) {
            min = *gmMainLib_8015D3E4((u8) i);
        }
        i += 1;
    } while (i < 0x19);

    return min;
}

u32 gm_801631CC(u8 i)
{
    return *gmMainLib_8015D06C(i);
}

u32 gm_801631F0(void)
{
    s32 i = 0;
    u32 sum = 0;
    u32 tmp;

    for (; i < 0x19; i++) {
        tmp = sum + *gmMainLib_8015D06C((u8) i);

        if (tmp > (u32) -1) {
            tmp = (u32) -1;
        } else {
            tmp = sum + *gmMainLib_8015D06C((u8) i);
        }
        sum = tmp;
    }

    return sum;
}

u16 gm_80163274(u8 i)
{
    return *gmMainLib_8015D7EC(i);
}

bool gm_80163298(s8 c_kind, u16 arg1)
{
    u8 index;
    u16* record;
    u16 score;

    index = gm_80164024(c_kind);
    record = gmMainLib_8015D7EC(index);
    score = arg1;

    if ((u32) gmMainLib_8015EDBC()->x114[index] < (u32) score) {
        gmMainLib_8015EDBC()->x114[index] = (int) score;
    }

    if (*record < arg1) {
        *record = arg1;
        return true;
    }
    return false;
}

s32 gm_8016332C(u8 arg0)
{
    if (!gmMainLib_8015D48C(arg0)) {
        return *gmMainLib_8015D438(arg0);
    }
    return -1;
}

void gm_80163374(u8 arg0, u8* arg1, u8* arg2, u8* arg3, u8* arg4)
{
    s32 temp_r0;
    u32 val;

    if (gmMainLib_8015D48C(arg0) != 0) {
        val = *gmMainLib_8015D438(arg0);
        temp_r0 = val / 60;
        if (arg1 != NULL) {
            *arg1 = (u8) ((temp_r0 / 60) / 60);
        }
        if (arg2 != NULL) {
            *arg2 = (u8) ((temp_r0 / 60) % 60);
        }
        if (arg3 != NULL) {
            *arg3 = (u8) (temp_r0 % 60);
        }
        if (arg4 != NULL) {
            *arg4 = (u8) ((99.0f * (f32) (val % 60)) / 59.0f);
        }
    }
}

bool gm_801634D4(u8* arg0, u8* arg1, u8* arg2, u8* arg3)
{
    u32 total_frames = 0;
    s32 i;
    s32 frames;

    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D48C(i) != 0) {
            total_frames += *gmMainLib_8015D438((u8) i);
        } else {
            return false;
        }
    }

    frames = total_frames / 60;

    if (arg0 != NULL) {
        *arg0 = (u8) ((frames / 60) / 60);
    }
    if (arg1 != NULL) {
        *arg1 = (u8) ((frames / 60) % 60);
    }
    if (arg2 != NULL) {
        *arg2 = (u8) (frames % 60);
    }
    if (arg3 != NULL) {
        *arg3 = (u8) ((99.0f * (f32) (total_frames % 60)) / 59.0f);
    }

    return true;
}

bool gm_8016365C(u8 arg0)
{
    if (!gmMainLib_8015D6BC(arg0)) {
        return true;
    }
    return false;
}

s32 gm_80163690(u8 arg0)
{
    if (!gmMainLib_8015D6BC(arg0)) {
        return *gmMainLib_8015D6A4(arg0);
    }
    return -1;
}

void gm_801636D8(u8 arg0, u8* arg1, u8* arg2, u8* arg3, u8* arg4)
{
    s32 temp_r0;
    u32 val;

    if (gmMainLib_8015D6BC(arg0) != 0) {
        val = *gmMainLib_8015D6A4(arg0);
        temp_r0 = val / 60;
        if (arg1 != NULL) {
            *arg1 = (u8) ((temp_r0 / 60) / 60);
        }
        if (arg2 != NULL) {
            *arg2 = (u8) ((temp_r0 / 60) % 60);
        }
        if (arg3 != NULL) {
            *arg3 = (u8) (temp_r0 % 60);
        }
        if (arg4 != NULL) {
            *arg4 = (u8) ((99.0f * (f32) (val % 60)) / 59.0f);
        }
    }
}

bool gm_80163838(u8* arg0, u8* arg1, u8* arg2, u8* arg3)
{
    u32 total_frames = 0;
    s32 i;
    s32 frames;

    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D6BC(i) != 0) {
            total_frames += *gmMainLib_8015D6A4((u8) i);
        } else {
            return false;
        }
    }

    frames = total_frames / 60;

    if (arg0 != NULL) {
        *arg0 = (u8) ((frames / 60) / 60);
    }
    if (arg1 != NULL) {
        *arg1 = (u8) ((frames / 60) % 60);
    }
    if (arg2 != NULL) {
        *arg2 = (u8) (frames % 60);
    }
    if (arg3 != NULL) {
        *arg3 = (u8) ((99.0f * (f32) (total_frames % 60)) / 59.0f);
    }

    return true;
}

bool gm_801639C0(u8 arg0)
{
    if (!gmMainLib_8015D710(arg0)) {
        return true;
    }
    return false;
}

int gm_801639F4(u8 arg0)
{
    if (!gmMainLib_8015D710(arg0)) {
        return *gmMainLib_8015D6F8(arg0);
    }
    return -1;
}

void gm_80163A3C(u8 arg0, u8* arg1, u8* arg2, u8* arg3, u8* arg4)
{
    s32 temp_r0;
    u32 val;

    if (gmMainLib_8015D710(arg0) != 0) {
        val = *gmMainLib_8015D6F8(arg0);
        temp_r0 = val / 60;
        if (arg1 != NULL) {
            *arg1 = (u8) ((temp_r0 / 60) / 60);
        }
        if (arg2 != NULL) {
            *arg2 = (u8) ((temp_r0 / 60) % 60);
        }
        if (arg3 != NULL) {
            *arg3 = (u8) (temp_r0 % 60);
        }
        if (arg4 != NULL) {
            *arg4 = (u8) ((99.0f * (f32) (val % 60)) / 59.0f);
        }
    }
}

bool gm_80163B9C(u8* arg0, u8* arg1, u8* arg2, u8* arg3)
{
    s32 i;
    u32 total_frames;
    s32 frames;
    total_frames = 0;
    for (i = 0; i < 25; i++) {
        if (gmMainLib_8015D710((u8) i) != 0) {
            total_frames = *gmMainLib_8015D6F8((u8) i);

            frames = total_frames / 60;
            if (arg0 != NULL) {
                *arg0 = (u8) ((frames / 60) / 60);
            }
            if (arg1 != NULL) {
                *arg1 = (u8) ((frames / 60) % 60);
            }
            if (arg2 != NULL) {
                *arg2 = (u8) (frames % 60);
            }
            if (arg3 != NULL) {
                *arg3 = (u8) ((99.0f * (f32) (total_frames % 60)) / 59.0f);
            }
            return true;
        }
    }
    return false;
}

bool fn_80163D24(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D710(i)) {
            return true;
        }
    }
    return false;
}

bool fn_80163D74(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D764(i)) {
            return true;
        }
    }
    return false;
}

u16 gm_Get3MinMultimanHighscore(u8 i)
{
    return *gmMainLib_8015D74C(i);
}

/// Get total number of KOs
int gm_Get3MinMultimanTotalHighscore(void)
{
    int i;
    int total = 0;
    for (i = 0; i < 0x19; i++) {
        total += *gmMainLib_8015D74C(i);
    }
    return total;
}

u16 gm_Get15MinMultimanHighscore(u8 i)
{
    return *gmMainLib_8015D7A4(i);
}

int gm_Get15MinMultimanTotalHighscore(void)
{
    int i;
    int total = 0;
    for (i = 0; i < 0x19; i++) {
        total += *gmMainLib_8015D7A4(i);
    }
    return total;
}

int gm_GetEndlessHighscore(u8 i)
{
    return *gmMainLib_8015D7BC(i);
}

int gm_GetEndlessTotalHighscore(void)
{
    int i;
    int total = 0;
    for (i = 0; i < 0x19; i++) {
        total += *gmMainLib_8015D7BC(i);
    }
    return total;
}

int gm_GetCruelHighscore(u8 i)
{
    return *gmMainLib_8015D7D4(i);
}

int gm_GetCruelTotalHighscore(void)
{
    int i;
    int total = 0;
    for (i = 0; i < 0x19; i++) {
        total += *gmMainLib_8015D7D4(i);
    }
    return total;
}

int fn_80163FA4(u8 arg0)
{
    int i;
    int count = 0;
    for (i = 0; i < arg0; i++) {
        if (gmMainLib_8015CEFC(i)) {
            count++;
        }
    }
    return count;
}

u8 gm_8016400C(u8 ckind)
{
    return lbl_803B7888[ckind];
}

u8 gm_80164024(u8 arg0)
{
    return lbl_803B78A4[arg0];
}

bool gm_8016403C(u8 item)
{
    u64 item_mask = gmMainLib_8015CC58()->item_mask;
    if ((1LL << item) & item_mask) {
        return true;
    }
    return false;
}

void fn_801640B0(u64* item_mask)
{
    int i;
    struct gmm_x1CB0* temp_r30 = gmMainLib_8015CC58();

    for (i = 0; i < 0x20; i++) {
        int shift;
        if ((shift = lbl_803B7844[(u8) i]) != 0x23) {
            if (temp_r30->item_mask & (1LL << i)) {
                *item_mask |= 1LL << shift;
            } else {
                *item_mask &= ~(1LL << shift);
            }
        }
    }
}

float fn_8016419C(u8 arg0)
{
    return lbl_803B7930[arg0 - 1].x;
}

float fn_801641B4(u8 arg0)
{
    return lbl_803B7930[arg0 - 1].y;
}

u16 gm_801641CC(u8 arg0)
{
    return lbl_803B7808[arg0];
}

void gm_801641E4(u8 stage, u8 enable)
{
    if (enable) {
        gmMainLib_8015CC58()->stage_mask |= 1 << stage;
    } else {
        gmMainLib_8015CC58()->stage_mask &= ~(1 << stage);
    }
}

s32 gm_80164250(u16 mask)
{
    bool tmp = (1 << mask) & gmMainLib_8015CC58()->stage_mask;
    if (tmp) {
        return 1;
    }
    return 0;
}

bool fn_801642A0(void)
{
    s32 var_r30;
    s32 var_r29;
    u8 var_r0;

    var_r30 = 0;
    var_r29 = 0;
    do {
        if ((1 << (u16) var_r29) & gmMainLib_8015CC58()->stage_mask) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            var_r30 += 1;
        }
        var_r29 += 1;
    } while (var_r29 < 0x1D);

    if (var_r30 > 1) {
        return false;
    }
    return true;
}

// RandomStageSwitch
bool gm_80164330(s32 arg0)
{
    s32 total_stages_on;
    struct gmm_x1CB0* temp_ret;
    s32 i;
    u8 var_r0;

    if (gm_80164430(lbl_803B7808[(u8) arg0]) == 0) {
        return false;
    }
    if (gmMainLib_8015EE44() == 0) {
        return true;
    }

    total_stages_on = 0;
    i = 0;
    for (i = 0; i < 0x1D; i++) {
        temp_ret = gmMainLib_8015CC58();
        if (temp_ret->stage_mask & (1 << (u16) i)) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            total_stages_on = 1;
        }
    }
    if (total_stages_on == 0) {
        OSReport("RandomStageSwitch All-Off!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    }
    if ((1 << (u16) arg0) & gmMainLib_8015CC58()->stage_mask) {
        return true;
    }
    return false;
}

bool gm_80164430(u16 arg0)
{
    u16* temp_r31;
    s32 i;
    u8 stage_idx;
    u8 unlock_bit;

    temp_r31 = gmMainLib_8015EDA4();
    stage_idx = Stage_8022519C(arg0);

    for (i = 0; i < NUM_UNLOCKABLE_STAGES; i++) {
        if ((s32) stage_idx == (s32) lbl_803B790C[i][1]) {
            unlock_bit = lbl_803B790C[i][0];
            goto found;
        }
    }
    unlock_bit = NUM_UNLOCKABLE_STAGES;

found:
    if (unlock_bit == NUM_UNLOCKABLE_STAGES ||
        (*temp_r31 & (1LL << unlock_bit)))
    {
        return true;
    }
    return false;
}

int gm_80164504(u16 stage_id)
{
    u16* stage_unlock_mask;
    u8 internal_id;
    s32 i;
    u8 unlock_idx;
    u8 notify_val;

    stage_unlock_mask = gmMainLib_8015EDA4();
    internal_id = Stage_8022519C(stage_id);

    for (i = 0; i < NUM_UNLOCKABLE_STAGES; i++) {
        if ((s32) internal_id == (s32) lbl_803B790C[i][1]) {
            unlock_idx = lbl_803B790C[i][0];
            goto found_stage;
        }
    }
    unlock_idx = NUM_UNLOCKABLE_STAGES;

found_stage:
    if (unlock_idx != NUM_UNLOCKABLE_STAGES) {
        for (i = 0; i < NUM_UNLOCKABLE_STAGES; i++) {
            if ((s32) unlock_idx == (s32) lbl_803B790C[i][0]) {
                notify_val = lbl_803B790C[i][2];
                goto found_notify;
            }
        }
        notify_val = 0x42;

    found_notify:
        gmMainLib_8015D818(notify_val);
        *stage_unlock_mask |= (1LL << (s32) unlock_idx);
    }
}

/// Are all stages unlocked?
bool gm_80164600(void)
{
    u16* stage_unlock_mask = gmMainLib_8015EDA4();
    int i;

    for (i = 0; i < NUM_UNLOCKABLE_STAGES; i++) {
        if (!(*stage_unlock_mask & (1LL << i))) {
            return false;
        }
    }
    return true;
}

void gm_8016468C(void)
{
    int i;
    u16* ptr = gmMainLib_8015EDA4();

    for (i = 0; i < 11; i++) {
        *ptr |= 1LL << i;
    }
}

void gm_801647D0(void)
{
    u16* stage_unlock_mask = gmMainLib_8015EDA4();
    *stage_unlock_mask = 0;
}

int gm_801647F8(u8 arg0)
{
    struct lbl_803D5168_t* var_r5 = lbl_803D5168;
    if (arg0 == 0x20) {
        arg0 = 0xE;
    }
    while (var_r5->x0 != 0x148) {
        if (var_r5->x1 == arg0) {
            return var_r5->x0;
        }
        var_r5++;
    }
    return 0x148;
}

/// Is a specific character unlocked?
bool gm_80164840(u8 ckind)
{
    u16* temp_r31 = gmMainLib_8015ED8C();
    u8 var = lbl_803B78A4[ckind];
    u8 var_r0 = fn_801605EC(var);

    if (var_r0 == NUM_UNLOCKABLE_CHARACTERS || (*temp_r31 & (1LL << var_r0))) {
        return true;
    }
    return false;
}

static inline bool gm_80164840_inner(u8 ckind)
{
    return gm_80164840(ckind);
}

static inline bool gm_80164840_noinline(u8 ckind)
{
    return gm_80164840_inner(ckind);
}

void gm_80164910(int arg0)
{
    u16* char_unlock_mask;
    u8 internal_id;
    s32 i;
    u8 unlock_idx;
    u8 notify_val;

    char_unlock_mask = gmMainLib_8015ED8C();
    internal_id = lbl_803B78A4[(u8) arg0];

    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if ((s32) internal_id == (s32) lbl_803B78C8[i].ckind) {
            unlock_idx = lbl_803B78C8[i].idx;
            goto found_char;
        }
    }
    unlock_idx = NUM_UNLOCKABLE_CHARACTERS;

found_char:
    if (unlock_idx != NUM_UNLOCKABLE_CHARACTERS) {
        for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
            if ((s32) unlock_idx == (s32) lbl_803B78C8[i].idx) {
                notify_val = lbl_803B78C8[i].x2;
                goto found_notify;
            }
        }
        notify_val = 0x42;

    found_notify:
        gmMainLib_8015D818(notify_val);
        *char_unlock_mask |= (1LL << (s32) unlock_idx);
    }
}

s32 gm_80164A0C(u8 arg0)
{
    s32 var_ctr;
    s32 var_r3;
    u16* temp_r31 = gmMainLib_8015ED8C();
    u8 var_r0;

    // Selected character
    u8 key = lbl_803B78C8[arg0].idx;

    // These are 6 big, should the loop be over that somehow with var_r4 as i?
    const struct lbl_803B78C8_0x6* var_r4 = lbl_803B78C8;
    var_r3 = 0;
    for (var_ctr = 0xB; var_ctr != 0; var_ctr -= 1) {
        if (key == var_r4[1].idx) {
            var_r3 = (s32) ((const u8*) lbl_803B75F8 + (var_r3 * 6));
            var_r0 = *(u8*) (var_r3 + 0x2D0);
            goto done;
        }
        var_r4 += 6;
        var_r3 += 1;
    }

    var_r0 = 0xB;

done:
    if (var_r0 != 0xB) {
        *temp_r31 &= (u16) ~(1ULL << var_r0);
    }
    return var_r3;
}

/// Are all unlockable characters unlocked?
bool gm_80164ABC(void)
{
    u16* unlockable_character_bitfield = gmMainLib_8015ED8C();
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (!(*unlockable_character_bitfield & (1LL << i))) {
            /// @remarks Gekko codes which unlock all characters change this to
            ///          return @c true.
            return false;
        }
    }
    return true;
}

bool fn_80164B48(void)
{
    const u8* base = (const u8*) lbl_803B75F8;
    const u8* es;
    u16* ptr;
    s32 i;
    u8 idx;
    u8 t;
    s32 ok;

    ptr = gmMainLib_8015ED8C();
    t = base[0x2C2];
    idx = 0xB;
    es = base + 0x2D0;
    for (i = 0; i < 0xB; i++) {
        if (t == es[1]) {
            idx = (base + i * 6)[0x2D0];
            break;
        }
        es += 6;
    }
    ok = 0;
    if (idx == 0xB || (*ptr & (1LL << idx))) {
        ok = 1;
    }
    if (ok == 0) {
        return 0;
    }

    ptr = gmMainLib_8015ED8C();
    t = base[0x2C5];
    idx = 0xB;
    es = base + 0x2D0;
    for (i = 0; i < 0xB; i++) {
        if (t == es[1]) {
            idx = (base + i * 6)[0x2D0];
            break;
        }
        es += 6;
    }
    ok = 0;
    if (idx == 0xB || (*ptr & (1LL << idx))) {
        ok = 1;
    }
    if (ok == 0) {
        return 0;
    }

    ptr = gmMainLib_8015ED8C();
    t = base[0x2C1];
    idx = 0xB;
    es = base + 0x2D0;
    for (i = 0; i < 0xB; i++) {
        if (t == es[1]) {
            idx = (base + i * 6)[0x2D0];
            break;
        }
        es += 6;
    }
    ok = 0;
    if (idx == 0xB || (*ptr & (1LL << idx))) {
        ok = 1;
    }
    if (ok == 0) {
        return 0;
    }

    ptr = gmMainLib_8015ED8C();
    t = base[0x2C0];
    idx = 0xB;
    es = base + 0x2D0;
    for (i = 0; i < 0xB; i++) {
        if (t == es[1]) {
            idx = (base + i * 6)[0x2D0];
            break;
        }
        es += 6;
    }
    ok = 0;
    if (idx == 0xB || (*ptr & (1LL << idx))) {
        ok = 1;
    }
    if (ok == 0) {
        return 0;
    }

    ptr = gmMainLib_8015ED8C();
    t = base[0x2C4];
    idx = 0xB;
    es = base + 0x2D0;
    for (i = 0; i < 0xB; i++) {
        if (t == es[1]) {
            idx = (base + i * 6)[0x2D0];
            break;
        }
        es += 6;
    }
    ok = 0;
    if (idx == 0xB || (*ptr & (1LL << idx))) {
        ok = 1;
    }
    if (ok == 0) {
        return 0;
    }

    ptr = gmMainLib_8015ED8C();
    t = base[0x2C3];
    idx = 0xB;
    es = base + 0x2D0;
    for (i = 0; i < 0xB; i++) {
        if (t == es[1]) {
            idx = (base + i * 6)[0x2D0];
            break;
        }
        es += 6;
    }
    ok = 0;
    if (idx == 0xB || (*ptr & (1LL << idx))) {
        ok = 1;
    }
    if (ok == 0) {
        return 0;
    }

    return 1;
}

void gm_80164F18(void)
{
    u16* ptr;
    int i;

    ptr = gmMainLib_8015ED8C();

    for (i = 0; i < 11; i++) {
        *ptr |= (u16) (1LL << i);
    }
}

void gm_8016505C(void)
{
    u16* temp_r3 = gmMainLib_8015ED8C();
    *temp_r3 = 0;
}

bool gm_80165084(void)
{
    s32 i;
    bool result = true;

    for (i = 0; i <= 0x1B; i++) {
        if (i != 0x1A && gmMainLib_8015D94C(i) == 0) {
            result = false;
            break;
        }
    }

    return result;
}

void fn_801650E8(void)
{
    Ground_801C5800();
}

void fn_80165108(int slot, int arg1)
{
    if (slot == -1) {
        Camera_8002F73C(0xB, 5);
        return;
    }
    if (((Player_GetPlayerSlotType(slot) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(slot) == Gm_PKind_Cpu)) &&
        (Player_GetEntity(slot) != NULL))
    {
        Camera_8002F73C(slot, arg1);
    }
}

void fn_80165190(s32 slot, s32 arg1)
{
    if (((Player_GetPlayerSlotType(slot) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(slot) == Gm_PKind_Cpu)) &&
        (Player_GetEntity(slot) != NULL))
    {
        Camera_8002F760(slot, arg1);
    }
}

void fn_801651FC(s32 slot, s32 arg1)
{
    if (((Player_GetPlayerSlotType(slot) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(slot) == Gm_PKind_Cpu)) &&
        (Player_GetEntity(slot) != NULL))
    {
        Camera_8002F784(slot, arg1);
    }
}

void gm_80165268(int unused)
{
    Camera_8002FC7C(4, 3);
}

void gm_80165290(int x)
{
    Camera_8002F8F4();
}

void fn_801652B0(s32 arg0, s32 arg1)
{
    Camera_8002F9E4(arg0, arg1);
}

void* fn_801652D8(void)
{
    u32 val;
    s32 idx;
    HSD_VIInfo* vi = &HSD_VIData;
    PerfLabelLine* lines = &lbl_8046B378.line0;

    lines[0].unk_04 = 0;

    idx = 0;
    sprintf(lines[idx].text, "\\cffff00%2d", (int) vi->perf.frame_renew);

    lines[0].next = &lines[1];

    val = gm_801A4BB8();

    idx = 1;
    sprintf(lines[idx].text, "\\ce0e0ff%5d", (int) val);

    lines[1].next = &lines[2];
    lines[1].next = NULL;

    return &lbl_8046B378;
}

/// creates the develop mode stress test
HSD_GObj* gm_80165388(u16 arg0, u8 arg1, u8 arg2, s32 arg3)
{
    HSD_GObj* temp_r3;

    temp_r3 = hsd_80398310(arg0, arg1, arg2, arg3);
    if (temp_r3 != NULL) {
        hsd_80392528((Event) fn_801652D8);
    }
    return temp_r3;
}

/// frees the develop mode stress test
void gm_801653C8(HSD_GObj* gobj)
{
    HSD_GObjPLink_80390228(gobj);
}

f32 fn_801653E8(u8 arg0)
{
    return (0.1f * arg0);
}

u8 fn_80165418(MatchEnd* match_end)
{
    u8 winner = 0;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (match_end->player_standings[i].slot_type != Gm_PKind_NA &&
            match_end->player_standings[i].is_small_loser == 0)
        {
            winner = i;
        }
    }
    return winner;
}

u8 fn_801654A0(MatchEnd* match_end)
{
    u8 winner = 0;
    s32 i;
    for (i = 0; i < 5; i++) {
        if (match_end->team_standings[i].active != 0 &&
            match_end->team_standings[i].is_small_loser == 0)
        {
            winner = i;
        }
    }
    return winner;
}

u8 fn_80165548(MatchEnd* me, s8 arg1, s32 team)
{
    s8 ret;
    MatchPlayerData* p;
    MatchPlayerData* q;
    s32 i;
    s32 j;

    ret = 0;
    if (me->is_teams == 1) {
        for (i = 0; i < 4; i++) {
            p = &me->player_standings[i];
            if (p->slot_type != 3 && (s32) p->team == (s32) team) {
                s8 result = i;
                q = me->player_standings;
                for (j = 0; j < 4; j++, q++) {
                    if (q->slot_type != 3 && (s32) q->team == (s32) team &&
                        i != j && p->is_small_loser > q->is_small_loser)
                    {
                        result = -1;
                        break;
                    }
                }
                if (result >= 0) {
                    ret = result;
                }
            }
        }
    } else {
        ret = arg1;
    }
    return ret;
}

u32 fn_801656A8(MatchEnd* arg0, u32 arg1)
{
    u32 ret = 0;

    if (arg0->player_standings[arg1].slot_type != 3) {
        s32 cnt_gt = 0;
        s32 j;
        for (j = 0; j < 6; j++) {
            if (arg0->player_standings[j].slot_type != 3 &&
                (u32) arg0->player_standings[arg1].x20 >
                    (u32) arg0->player_standings[j].x20) {
                cnt_gt += 1;
            }
        }
        {
            s32 cnt_lt = 0;
            for (j = 0; j < 6; j++) {
                if (arg0->player_standings[j].slot_type != 3 &&
                    (u32) arg0->player_standings[arg1].x24 <
                        (u32) arg0->player_standings[j].x24)
                {
                    cnt_lt += 1;
                }
            }
            ret = cnt_gt * 0x10;
            ret = ((ret + cnt_lt) * 0x10) & 0xFFFFFFFFFFFFFFFFu;
            j = 6 - arg1;
            ret += j;
        }
    }
    return ret;
}

s32 fn_8016588C(lbl_8046B6A0_24C_t* arg0, s32 arg1)
{
    s32 v;
    s32 lim;

    if (gm_801A4310() == 0x1F) {
        if (arg0->x58[arg1].x28 != 0) {
            v = (u8) (arg0->x58[arg1].x28 / 60 +
                      0xFF000001);
        } else {
            v = arg0->x58[arg1].x9;
        }
    } else {
        switch (arg0->x5) {
        case 2:
            v = arg0->x58[arg1].x1C;
            lim = (1 << 24) - 1;
            if (lim < 0) {
                lim = -lim;
            }
            if (v > lim) {
                return lim;
            }
            if (v < -lim) {
                return -lim;
            }
            break;
        case 1:
            if ((s8) arg0->x58[arg1].x8 != 0) {
                v = (u8) (s8) arg0->x58[arg1].x8;
            } else {
                v = (u8) (arg0->x58[arg1].x28 / 60 +
                          0xFF000001);
            }
            lim = (1 << 24) - 1;
            if (lim < 0) {
                lim = -lim;
            }
            if (v > lim) {
                return lim;
            }
            if (v < -lim) {
                return -lim;
            }
            break;
        case 3:
            pl_80039450(arg1);
            v = (u8) fn_8016FFD4(arg0, 2, (u8) arg1);
            lim = (1 << 24) - 1;
            if (lim < 0) {
                lim = -lim;
            }
            if (v > lim) {
                return lim;
            }
            if (v < -lim) {
                return -lim;
            }
            break;
        default: {
            u16 a = arg0->x58[arg1].xA;
            v = (u8) ((arg0->x58[arg1].x20 - (arg0->x58[arg1].x24 - a)) +
                      a * (s8) arg0->xC);
            break;
            lim = (1 << 24) - 1;
            if (lim < 0) {
                lim = -lim;
            }
            if (v > lim) {
                return lim;
            }
            if (v < -lim) {
                return -lim;
            }
        }
        }
    }
    lim = (1 << 24) - 1;
    if (lim < 0) {
        lim = -lim;
    }
    if (v > lim) {
        return lim;
    }
    if (v < -lim) {
        return -lim;
    }
    return v;
}

s32 fn_80165AC0(MatchEnd* arg0)
{
    s32 max_loser;
    s32 count;
    s32 i;
    s32 j;
    MatchPlayerData* p;

    max_loser = 0;
    for (i = 0; i < 6; i++) {
        p = &arg0->player_standings[i];
        if (p->slot_type != 3) {
            for (j = 0; j < 6; j++) {
                if (arg0->player_standings[j].slot_type != 3 && j != i &&
                    (s32) p->score < (s32) arg0->player_standings[j].score) {
                    p->is_big_loser += 1;
                }
            }
            if (max_loser < (s32) p->is_big_loser) {
                max_loser = p->is_big_loser;
            }
        }
    }
    arg0->loser = (arg0->loser & ~0xF0) | ((max_loser << 4) & 0xF0);
    count = 0;
    for (j = 0; j < 6; j++) {
        if (arg0->player_standings[j].slot_type != 3 &&
            arg0->player_standings[j].is_big_loser == 0) {
            arg0->winners[count] = j;
            count += 1;
        }
    }
    arg0->n_winners = count;
    return (s32) arg0;
}

MatchEnd* fn_80165D60(MatchEnd* arg0)
{
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        if ((u8) arg0->player_standings[i].slot_type != 3) {
            arg0->player_standings[i].is_small_loser =
                arg0->player_standings[i].is_big_loser;
            for (j = 0; j < 6; j++) {
                if ((u8) arg0->player_standings[j].slot_type != 3 && i != j &&
                    (u8) arg0->player_standings[i].is_big_loser ==
                        (u8) arg0->player_standings[j].is_big_loser &&
                    arg0->player_standings[i].x30 <
                        arg0->player_standings[j].x30)
                {
                    arg0->player_standings[i].is_small_loser++;
                }
            }
        }
    }

    return arg0;
}
void fn_80165E7C(MatchEnd* arg0)
{
    s32 i;
    int new_var;

    for (i = 0; i < 6; i++) {
        if ((u8) arg0->player_standings[i].slot_type != 3) {
            u8 team = arg0->player_standings[i].team;

            if (gm_801A4310() == GM_STAMINA_VS || arg0->x5 == 1) {
                int player_score = new_var = arg0->player_standings[i].score;

                if (player_score < 0) {
                    int team_score = arg0->team_standings[team].score;
                    if (team_score == 0) {
                        arg0->team_standings[team].score = player_score;
                    } else if (team_score < 0 && team_score < player_score) {
                        arg0->team_standings[team].score = player_score;
                    }
                } else {
                    int team_score = arg0->team_standings[team].score;
                    if (team_score < 0) {
                        arg0->team_standings[team].score = player_score;
                    } else {
                        arg0->team_standings[team].score =
                            team_score + player_score;
                    }
                }
            } else {
                arg0->team_standings[team].score +=
                    arg0->player_standings[i].score;
            }

            arg0->team_standings[team].subscore +=
                arg0->player_standings[i].x30;
            arg0->team_standings[team].active = 1;
        }
    }
}

s32 fn_80165FA4(MatchEnd* arg0)
{
    s32 max_loser;
    s32 count;
    s32 i;
    s32 j;
    struct MatchTeamData* t;

    max_loser = 0;
    for (i = 0; i < 5; i++) {
        t = &arg0->team_standings[i];
        if (t->active != 0) {
            for (j = 0; j < 5; j++) {
                if (j != i && arg0->team_standings[j].active != 0 &&
                    (s32) t->score < (s32) arg0->team_standings[j].score) {
                    t->is_big_loser += 1;
                }
            }
            if (max_loser < (s32) t->is_big_loser) {
                max_loser = t->is_big_loser;
            }
        }
    }
    arg0->loser = (arg0->loser & ~0xF) | (max_loser & 0xF);
    count = 0;
    for (j = 0; j < 5; j++) {
        if (arg0->team_standings[j].active != 0 &&
            arg0->team_standings[j].is_big_loser == 0) {
            arg0->team_winners[count] = j;
            count += 1;
        }
    }
    arg0->n_team_winners = count;
    return (s32) arg0;
}

s32 fn_801661E0(MatchEnd* arg0)
{
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        if ((u8) arg0->team_standings[i].active != 0) {
            arg0->team_standings[i].is_small_loser =
                arg0->team_standings[i].is_big_loser;
            for (j = 0; j < 5; j++) {
                if ((u8) arg0->team_standings[j].active != 0 && i != j &&
                    (u8) arg0->team_standings[i].is_big_loser ==
                        (u8) arg0->team_standings[j].is_big_loser &&
                    (u32) arg0->team_standings[i].subscore <
                        (u32) arg0->team_standings[j].subscore)
                {
                    arg0->team_standings[i].is_small_loser++;
                }
            }
        }
    }

    return (s32) arg0;
}

void gm_80166378(lbl_8046B6A0_24C_t* arg0_raw)
{
    MatchEnd* arg0 = (MatchEnd*) arg0_raw;
    Vec3 sp48;
    s32 i;
    s32 j;
    s32 cnt;
    MatchPlayerData* p;
    MatchPlayerData* q;
    u16* kw;

    memzero(arg0->player_standings, 0x3F0);
    memzero(arg0->team_standings, 0x3C);
    memzero(arg0->_x448, 4);
    arg0->frame_count = gm_8016AEDC();
    arg0->x7 = fn_8016B728();
    p = arg0->player_standings;
    for (i = 0; i < 6; i++, p++) {
        p->slot_type = Player_GetPlayerSlotType(i);
        if (p->slot_type != 3) {
            p->character_kind = Player_GetPlayerCharacter(i);
            p->character_id = Player_80036394(i);
            p->stocks = Player_GetStocks(i);
            p->x3 = Player_GetCostumeId(i);
            p->x4 = Player_GetNametagSlotID(i);
            p->x1C = Player_GetCoins(i);
            p->x28 = Player_GetMatchFrameCount(i);
            if ((u32) (p->x28 + 0x10000) == -1U) {
                p->x28 = gm_8016AEDC();
            }
            p->self_destructs = Player_GetSuicideCount(i);
            p->x24 = Player_GetFalls(i);
            p->team = Player_GetTeam(i);
            p->percent = Player_GetDamage(i);
            p->x3_6 = Player_800353BC(i);
            p->x3_7 = Player_GetMoreFlagsBit2(i);
            p->x9 = Player_GetRemainingHP(i);
            cnt = Player_GetJoystickCountByIndex(i, 0);
            sp48.y = 0.031f * ((f32) cnt * fn_8016B5B0());
            fn_80166A8C((Vec3*) &sp48.y, &sp48);
            p->xE = (u16) sp48.x;
            p->x34 = (s8) (100.0f * pl_80040948(i));
            p->x38 = pl_80040900(i);
            p->x3C = pl_80040924(i);
            p->x40 = pl_80040B3C(i);
            p->x44 = pl_80040B64(i);
            p->x48 = pl_80040BD8(i);
            p->x4C = pl_80040BFC(i);
            p->x50 = (u32) pl_80040C24(i) * 0xA;
            p->x54 = (u32) pl_80040C48(i) * 0xA;
            p->x58 = (u32) pl_80040C6C(i) * 0xA;
            p->x5C = (u32) pl_80040C90(i) * 0xA;
            p->x60 = Player_GetTotalCoins(i);
            p->x64 = Player_GetUnk98(i);
            p->x68 = Player_GetUnk9C(i);
            p->x6C = pl_80040CB4(i) / 60;
            p->x70 = pl_80040CD8(i) / 60;
            p->x74 = pl_80040A04(i);
            p->x78 = pl_80040A30(i);
            p->x7C = pl_80040A54(i);
            p->x80 = pl_80040B18(i);
            p->x84 = pl_80040A78(i);
            p->x88 = pl_80040A9C(i);
            p->x8C = pl_80040AF0(i);
            p->x90 = pl_8003E39C(i);
            p->x94 = (u32) (60.0f * (10.0f * pl_80040D44(i)));
            p->x98 = (u32) (60.0f * (10.0f * pl_80040D68(i)));
            p->x9C = pl_80040CFC(i) / 60;
            p->xA0 = pl_80040D20(i) / 60;
            p->xA4 = pl_80040DB8(i);
            q = arg0->player_standings;
            kw = p->kills;
            for (j = 0; j < 6; j++, q++) {
                if (q->slot_type != 3) {
                    kw[j] = Player_GetKOsByPlayerIndex(i, j);
                }
            }
        }
    }
    if (arg0->is_teams == 1) {
        p = arg0->player_standings;
        for (i = 0; i < 6; i++, p++) {
            if (p->slot_type != 3) {
                u8 team_i = p->team;
                q = arg0->player_standings;
                kw = p->kills;
                for (j = 0; j < 6; j++, q++) {
                    if (q->slot_type != 3) {
                        if (q->team != team_i) {
                            if (i != j) {
                                p->x20 += kw[j];
                            }
                        } else {
                            p->self_destructs += kw[j];
                            p->x24 += kw[j];
                        }
                    }
                }
            }
        }
    } else {
        p = arg0->player_standings;
        for (i = 0; i < 6; i++, p++) {
            if (p->slot_type != 3) {
                q = arg0->player_standings;
                kw = p->kills;
                for (j = 0; j < 6; j++, q++) {
                    if (q->slot_type != 3) {
                        if (i != j) {
                            p->x20 += kw[j];
                        } else {
                            p->self_destructs += kw[j];
                            p->x24 += kw[j];
                        }
                    }
                }
            }
        }
    }
    p = arg0->player_standings;
    for (i = 0; i < 6; i++, p++) {
        if (p->slot_type != 3) {
            p->score = fn_8016588C(arg0_raw, i);
            p->x30 = fn_801656A8(arg0, i);
        }
    }
    fn_80165AC0(arg0);
    fn_80165D60(arg0);
    fn_80165E7C(arg0);
    fn_80165FA4(arg0);
    fn_801661E0(arg0);
}

#ifdef MWERKS_GEKKO
float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
    register float x = src->x;
    asm { psq_st x, Vec3.x(dst), 1, qr3 }
    return x;
}
#else
float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
    NOT_IMPLEMENTED;
}
#endif

// Probably some code to setup or end a 4 player match?
s32 gm_80166A98(MatchEnd* arg0, s32 arg1, s8 arg2, u8 arg3, s8 arg4, u8 arg5,
                s8 arg6, u8 arg7, u8 arg_sp8, u8 arg_spC)
{
    struct HSD_PadStatus* pad_status;
    u32 i;

    memzero(arg0, 0x227C);
    pad_status = &HSD_PadMasterStatus[0];

    arg0->result = 1;
    arg0->x5 = 0;
    arg0->is_teams = 0;

    arg0->player_standings[0].character_kind = arg2;
    arg0->player_standings[1].character_kind = arg4;
    arg0->player_standings[2].character_kind = arg6;
    arg0->player_standings[3].character_kind = arg_sp8;

    // Apply player color to all 4 players?
    for (i = 0; i < 4; i++) {
        arg0->player_standings[i].character_kind |= (arg1 << 2) & 0xFC;
    }

    arg0->player_standings[0].score = 0xA - arg3;
    arg0->player_standings[1].score = 0xA - arg5;
    arg0->player_standings[2].score = 0xA - arg7;
    arg0->player_standings[3].score = 0xA - arg_spC;
    arg0->player_standings[0].x30 = 0xA - arg3;
    arg0->player_standings[1].x30 = 0xA - arg5;
    arg0->player_standings[2].x30 = 0xA - arg7;
    arg0->player_standings[3].x30 = 0xA - arg_spC;

    for (i = 0; i < 4; i++) {
        arg0->player_standings[i].x30 += 6 - i;
        if (arg0->player_standings[i].character_kind == 0x21) {
            arg0->player_standings[i].slot_type = 3;
        } else if (pad_status[i].err != 0) {
            arg0->player_standings[i].slot_type = 1;
        } else {
            arg0->player_standings[i].slot_type = 0;
        }

        if (arg0->player_standings[i].character_kind == 0x13) {
            arg0->player_standings[i].character_kind = 0x12;
            arg0->player_standings[i].character_id = 7;
        }
    }

    arg0->player_standings[4].slot_type = 3;
    arg0->player_standings[5].slot_type = 3;
    fn_80165AC0(arg0);
    fn_80165D60(arg0);
    fn_80165E7C(arg0);
    fn_80165FA4(arg0);
    return fn_801661E0(arg0);
}

u8 fn_80166CBC(struct fn_80166CBC_arg0_t* arg0, ssize_t index)
{
    return arg0[index].x5E;
}

void gm_80166CCC(MatchEnd* arg0, MatchEnd* arg1)
{
    s32 i;
    s32 player_count;
    s32 team_count;
    u8 result;

    result = arg1->result;
    player_count = 0;
    team_count = 0;
    if (result == 7 || result == 8) {
        arg0->result = result;
    }
    if (arg1->n_winners > 1) {
        for (i = 0; i < 6; i++) {
            if (arg1->player_standings[i].slot_type != 3) {
                arg1->player_standings[i].is_big_loser =
                    arg0->player_standings[i].is_big_loser +
                    arg1->player_standings[i].is_small_loser;
            }
        }
    }
    if (arg1->n_team_winners > 1) {
        for (i = 0; i < 5; i++) {
            if (arg1->team_standings[i].active != 0) {
                arg1->team_standings[i].is_big_loser =
                    arg0->team_standings[i].is_big_loser +
                    arg1->team_standings[i].is_small_loser;
            }
        }
    }
    for (i = 0; i < 6; i++) {
        if (arg1->player_standings[i].slot_type != 3) {
            player_count += 1;
        }
    }
    if (arg0->n_winners > 1) {
        for (i = 0; i < 6; i++) {
            if (arg0->player_standings[i].slot_type != 3) {
                arg0->player_standings[i].character_id =
                    arg1->player_standings[i].character_id;
                arg0->player_standings[i].xE += arg1->player_standings[i].xE;
                if (arg0->player_standings[i].is_big_loser == 0) {
                    if (arg1->player_standings[i].slot_type == 3) {
                        arg0->player_standings[i].is_big_loser += player_count;
                        arg0->player_standings[i].is_small_loser += player_count;
                    } else {
                        arg0->player_standings[i].is_big_loser =
                            arg1->player_standings[i].is_big_loser;
                        arg0->player_standings[i].is_small_loser =
                            arg1->player_standings[i].is_big_loser;
                    }
                }
            }
        }
    }

    for (i = 0; i < 6; i++) {
        if (arg1->team_standings[i].active != 0) {
            team_count += 1;
        }
    }
    if (arg0->n_team_winners > 1) {
        for (i = 0; i < 5; i++) {
            if (arg0->team_standings[i].active != 0) {
                if (arg0->team_standings[i].is_big_loser == 0) {
                    if (arg1->team_standings[i].active != 0) {
                        arg0->team_standings[i].is_big_loser =
                            arg1->team_standings[i].is_big_loser;
                        arg0->team_standings[i].is_small_loser =
                            arg1->team_standings[i].is_big_loser;
                    } else {
                        arg0->team_standings[i].is_big_loser += team_count;
                        arg0->team_standings[i].is_small_loser += team_count;
                    }
                }
            }
        }
    }
}

bool gm_80167140(MatchEnd* me)
{
    s32 winners;

    if (me->result != 7) {
        if (me->is_teams == 1) {
            winners = me->n_team_winners;
        } else {
            winners = fn_80167194(me);
        }
        if (winners > 1) {
            return true;
        }
    }

    return false;
}

int fn_80167194(MatchEnd* me)
{
    return me->n_winners;
}

void fn_8016719C(s32 slot, s32 subchar)
{
    Vec3 respawn_pos;
    Vec3 offset;
    f32 var_f1;
    lbl_8046B6A0_t* match_info;
    s32 var_r30;
    s32 stage_id;
    u8* temp_r4;
    u8 temp_r3;

    match_info = gm_8016AE44();
    stage_id = gm_8016B004();
    if (Stage_80224DC8(stage_id) != 0) {
        var_r30 = Ground_801C5774();
        Stage_80224E38(&respawn_pos, var_r30);
        offset.z = 0.0f;
        offset.y = 0.0f;
        offset.x = 0.0f;
        if ((stage_id != 0x4C) && (subchar == 0)) {
            Ground_801C38BC(respawn_pos.x, respawn_pos.y);
            Camera_8002F3AC();
        }
    } else {
        var_r30 = fn_80167638(slot, &respawn_pos, &offset);
    }
    respawn_pos.x += offset.x;
    Player_SetSpawnPlatformPos(slot, &respawn_pos);

    if (!(((u8) stage_info.unk8C.b0 >> 2U) & 1)) {
        Player_80032FA4(slot, var_r30);
        Player_SetSomePos(slot, &offset);
    }

    respawn_pos.y = Stage_GetCamBoundsTopOffset();
    Player_80032768(slot, &respawn_pos);
    if (respawn_pos.x >= 0.0f) {
        var_f1 = -1.0f;
    } else {
        var_f1 = 1.0f;
    }
    Player_SetFacingDirection(slot, var_f1);
    Player_SetHPByIndex(slot, subchar, match_info->FighterMatchInfo[slot].x6);
    Player_80032070(slot, subchar);
    if (subchar != 1) {
        ifStatus_802F6508(slot);
        temp_r4 = (u8*) &match_info->FighterMatchInfo[slot].xC;
        temp_r3 = *temp_r4;
        if ((temp_r3 >> 7U) & 1) {
            *temp_r4 &= 0x80;
            Camera_800310E8();
        }
    }
}

void gm_80167320(int slot, bool arg1)
{
    if (Player_GetFlagsBit1(slot) == 0) {
        if (gm_8016A1F8() && slot == 0 && fn_80169444(2)) {
            int i;
            for (i = 1; i < 6; i++) {
                if (Player_GetFlagsBit1(i)) {
                    ifStatus_802F6788(i);
                    Player_80031EBC(i);
                }
                Player_SetSlottype(i, Gm_PKind_NA);
            }
            gm_8016A164();
        }
        if ((gm_8016B094() || gm_8016B0E8()) && Player_GetStocks(slot) == 0) {
            gm_8016AC44(Player_GetPlayerCharacter(slot),
                        Player_GetCostumeId(slot));
        } else if (Stage_80224DC8(gm_8016B004())) {
            fn_8016719C(slot, arg1);
        } else {
            fn_8016719C(slot, arg1);
        }
    } else if (!arg1) {
        Player_80031EBC(slot);
        Player_SetSlottype(slot, Gm_PKind_NA);
        fn_80169550(slot);
    }
}

void gm_80167470(s32 arg0, s32 arg1)
{
    switch ((s32) gm_801A4310()) {
    case 0x1F:
        gm_801B97C4(arg0, arg1);
        break;
    }
}

void gm_801674C4(s8 arg0, u8 arg1, s8 arg2, s8 arg3, GmRouteCallback arg4)
{
    s8 temp_r31;
    struct lbl_8046B488_t* new_var;
    struct lbl_8046B488_t* temp_ptr;

    temp_ptr = fn_80169364();
    temp_ptr->x0 = arg0;
    temp_ptr->x1 = 0x21;
    temp_ptr->x2 = 0x21;
    temp_ptr->x7 = arg1;
    temp_ptr->x8 = arg1;
    temp_ptr->x9 = arg2;
    temp_ptr->xA = arg3;
    PAD_STACK(10);
    new_var = temp_ptr;
    new_var->unk_10_b2 = 1;
    fn_80169574((s32) new_var->x7, new_var->x20);
    fn_80169900(new_var->xD, new_var, temp_ptr->xA2, new_var->x20);
    temp_r31 = Player_GetCostumeId(0);
    fn_8016989C((u8*) new_var, (s8) Player_GetPlayerCharacter(0), temp_r31,
                (u8*) new_var->xA2, (u8*) temp_ptr->x20);
    fn_8016A09C();
    fn_80169434(arg4);
}

void fn_8016758C(void)
{
    lbl_8046B6A0_t* mi = gm_8016AE44();
    int i;

    for (i = 0; i < ARRAY_SIZE(mi->FighterMatchInfo); i++) {
        if (mi->FighterMatchInfo[i].x8 != 0) {
            mi->FighterMatchInfo[i].x8--;
        }
    }
}

struct lbl_803B7A44_t {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
};

extern struct lbl_803B7A44_t lbl_803B7A44;

s32 fn_80167638(s32 arg0, Vec3* arg1, Vec3* arg2)
{
    struct lbl_803B7A44_t sp;
    lbl_8046B6A0_t* info;
    s32 idx;
    s8 chr;

    info = gm_8016AE44();
    if (info->FighterMatchInfo[0].x8 == 0) {
        idx = 0;
    } else if (info->FighterMatchInfo[1].x8 == 0) {
        idx = 1;
    } else if (info->FighterMatchInfo[2].x8 == 0) {
        idx = 2;
    } else if (info->FighterMatchInfo[3].x8 == 0) {
        idx = 3;
    } else if (info->FighterMatchInfo[4].x8 == 0) {
        idx = 4;
    } else if (info->FighterMatchInfo[5].x8 == 0) {
        idx = 5;
    } else {
        idx = 0;
    }
    chr = Player_GetPlayerCharacter(arg0);
    if (stage_info.unk8C.b4) {
        Stage_80224E38(arg1, arg0);
        arg2->z = 0.0f;
        arg2->y = 0.0f;
        arg2->x = 0.0f;
        return arg0;
    }
    Stage_80224E38(arg1, 0);
    sp = lbl_803B7A44;
    arg2->x = 16.0f * (&sp.x0)[idx];
    arg2->z = 0.0f;
    arg2->y = 0.0f;
    info = gm_8016AE44();
    info->FighterMatchInfo[idx].x8 = 0x90;
    info->FighterMatchInfo[idx].x9 = chr;
    return 0;
}

void gm_801677C0(struct gm_801677C0_s* arg0)
{
    arg0->x0 = 0;
    arg0->x1 = 0;
    arg0->x2 = 0;
    arg0->x3 = 0;
    arg0->unk_20 = arg0->unk_28 = 0;
}

void gm_801677E8(s8 arg0)
{
    lbl_804D6598 = arg0;
}

u8 gm_801677F0(void)
{
    return lbl_804D6598;
}

bool gm_801677F8(int port, int arg1)
{
    bool result = false;
    if (arg1 == 0x78) {
        if (GetRumbleSettingOfPort(port) != 0) {
            result = true;
        }
    } else if (GetPersistentNameData(arg1)->x1A1 != 0) {
        result = true;
    }
    return result;
}

void gm_80167858(int port, int arg1, int arg2, int arg3)
{
    if (gm_801677F8(port, arg1)) {
        lb_80014574(port, 3, arg2, arg3);
    }
}

void gm_801678F8(int port, int arg1, int arg2)
{
    gm_80167858(port, 0x78, arg1, arg2);
}

void gm_8016795C(struct PlayerInitData* arg0)
{
    memzero(arg0, sizeof(*arg0));
    arg0->c_kind = CHKIND_NONE;
    arg0->slot_type = Gm_PKind_NA;
    arg0->stocks = 0;
    arg0->color = 0;
    arg0->slot = 0;
    arg0->x5 = -1;
    arg0->spawn_dir = 0;
    arg0->xB = 0;
    arg0->sub_color = 0;
    arg0->handicap = 9;
    arg0->team = 0;
    arg0->xC_b0 = false;
    arg0->xA = 0x78;
    arg0->xC_b1 = true;
    arg0->xE = 4;
    arg0->cpu_level = 0;
    arg0->x12 = 0;
    arg0->hp = 0;
    arg0->x18 = 1.0F;
    arg0->x1C = 1.0F;
    arg0->x20 = 1.0F;
}

void gm_80167A14(struct PlayerInitData* arg0)
{
    int i;
    for (i = 0; i < 6; i++) {
        gm_8016795C(&arg0[i]);
    }
}

void gm_80167A64(struct StartMeleeRules* arg0)
{
    memzero(arg0, sizeof(*arg0));
    arg0->x0_3 = 4;

    arg0->xC = 0;
    arg0->xB = 2;

    arg0->x20 = -1;
    arg0->x28 = 0;

    arg0->x3_1 = 1;

    arg0->x3_5 = 1;
    arg0->x3_4 = 1;
    arg0->x4_0 = 1;

    arg0->timer_shows_hours = 0;
    arg0->x2_5 = 1;
    arg0->x2_6 = 1;

    arg0->x2C = 1.0f;
    arg0->x30 = 1.0f;
    arg0->x34 = 1.0f;

    arg0->x4_6 = 1;
    arg0->x4_7 = 1;
    arg0->xD = 0x6E;
    arg0->xA = 0;
}

void gm_80167B50(VsModeData* arg0)
{
    gm_80167A64(&arg0->data.rules);
    gm_80167A14(arg0->data.players);
    arg0->loser = -1;
    arg0->ordered_stage_index = -1;
    arg0->winner = -1;
}

void gm_80167BC8(VsModeData* vs_data)
{
    GameRules* rules;
    struct gmm_x1CB0* prefs;
    s32 i;
    s8* handicap;
    PAD_STACK(56);

    rules = gmMainLib_8015CC34();
    prefs = gmMainLib_8015CC58();
    vs_data->data.rules.x0_6 = 0;

    switch (rules->mode) {
    case 0:
        vs_data->data.rules.x0_0 = 0;
        if (rules->time_limit != 0) {
            vs_data->data.rules.x0_6 = 1;
            vs_data->data.rules.x10 = rules->time_limit * 60;
        }
        break;
    case 1:
        vs_data->data.rules.x0_0 = 1;
        if (rules->stock_time_limit != 0) {
            vs_data->data.rules.x0_6 = 1;
            vs_data->data.rules.x10 = rules->stock_time_limit * 60;
            break;
        }
        break;
    case 2:
        vs_data->data.rules.x0_0 = 2;
        if (rules->time_limit != 0) {
            vs_data->data.rules.x0_6 = 1;
            vs_data->data.rules.x10 = rules->time_limit * 60;
        }
        break;
    case 3:
        vs_data->data.rules.x0_0 = 3;
        if (rules->time_limit != 0) {
            vs_data->data.rules.x0_6 = 1;
            vs_data->data.rules.x10 = rules->time_limit * 60;
        }
        break;
    }

    i = 0;
    for (i = 0; i < 6; i++) {
        vs_data->data.players[i].stocks = (s8) rules->stock_count;
        switch (rules->handicap) {
        case 0:
            vs_data->data.players[i].x18 = 1.0f;
            vs_data->data.players[i].x1C = 1.0f;
            break;
        case 1:
            handicap =
                gmMainLib_8015CE44(i, (s32) vs_data->data.players[i].xA);
            if (handicap != NULL) {
                vs_data->data.players[i].handicap =
                    *handicap; ///< @todo :: fix these to actually get the
                               ///< offensive and
                // defensive ratios just not sure how to setup the structs
                vs_data->data.players[i].x18 = lbl_803B7930[(u8) *handicap].x;
                vs_data->data.players[i].x1C = lbl_803B7930[(u8) *handicap].y;
            } else {
                vs_data->data.players[i].handicap = 5;
                vs_data->data.players[i].x18 = 0.61f;
                vs_data->data.players[i].x1C = 1.6393442f;
            }
            break;
        case 2:
            vs_data->data.players[i].x18 =
                lbl_803B7930[(u8) vs_data->data.players[i].handicap].x;
            vs_data->data.players[i].x1C =
                lbl_803B7930[(u8) vs_data->data.players[i].handicap].y;
            break;
        }
    }

    vs_data->data.rules.x1_7 = (rules->friendly_fire & 1);
    vs_data->data.rules.x30 = 0.1f * rules->damage_ratio;
    vs_data->data.rules.xB = (s8) prefs->item_freq;
    prefs = gmMainLib_8015CC58(); ///< @todo :: some weird item copy thing that
                                  ///< needs to be fixed
    i = 0;
    do {
        if ((s32) lbl_803B7844[i] != 0x23) {
            // prefs->item_mask = vs_data->data.rules.x20;
            if ((prefs->item_mask & (1LL << i))) {
                vs_data->data.rules.x20 |= (1LL << prefs->item_mask);
            } else {
                vs_data->data.rules.x20 &= ~(1LL << prefs->item_mask);
            }
        }
    } while (i < 0x20);
    // this is what decomp.py spits out
    // temp_r31 = gmMainLib_8015CC58();
    // var_r28_2 = 0;
    // do {
    //     if ((s32) lbl_803B75F8.pad_x24C[var_r28_2] != 0x23) {
    //         __shl2i();
    //         if ((((temp_r31->unkC & M2C_ERROR(/* Read from unset register
    //         $r4 */)) ^ 0) | ((temp_r31->unk8 & M2C_ERROR(/* Read from unset
    //         register $r3 */)) ^ 0)) != 0) {
    //             __shl2i();
    //             arg0->unk2C = (s32) (arg0->unk2C | M2C_ERROR(/* Read from
    //             unset register $r4 */)); arg0->unk28 = (s32) (arg0->unk28 |
    //             M2C_ERROR(/* Read from unset register $r3 */));
    //         } else {
    //             __shl2i();
    //             arg0->unk2C = (s32) (arg0->unk2C & ~(M2C_ERROR(/* Read from
    //             unset register $r4 */) | M2C_ERROR(/* Read from unset
    //             register $r4 */))); arg0->unk28 = (s32) (arg0->unk28 &
    //             ~(M2C_ERROR(/* Read from unset register $r3 */) |
    //             M2C_ERROR(/* Read from unset register $r3 */)));
    //         }
    //     }
    //     var_r28_2 += 1;
    // } while (var_r28_2 < 0x20);

    switch (gmMainLib_8015ED30()) {
    case 1:
        vs_data->data.rules.xC = 0;
        break;
    case 0:
        vs_data->data.rules.xC = -1;
        break;
    case 2:
        vs_data->data.rules.xC = -2;
        break;
    }

    if (rules->pause != 0) {
        vs_data->data.rules.x2_4 = 0;
    } else {
        vs_data->data.rules.x2_4 = 1;
    }
    if ((rules->score_display != 0) && (rules->mode == 0)) {
        vs_data->data.rules.x3_0 = 1;
        return;
    }
    vs_data->data.rules.x3_0 = 0;
}

static inline int pad_inline(SSSData* arg0, int base)
{
    int i;
    for (i = 0; i < 5; i++) {
        int j = (base + i) % 4;
        if (HSD_PadMasterStatus[(u8) j].err == 0 &&
            arg0->data.data.players[j].slot_type == Gm_PKind_Human)
        {
            return j;
        }
    }
    return -1;
}

static inline int get_flag_unk(u16 temp_r30)
{
    int temp_r3_2 = (u8) Stage_8022519C(temp_r30);
    int i;
    for (i = 0; i != ARRAY_SIZE(lbl_803B790C); i++) {
        if (temp_r3_2 == lbl_803B790C[i][1]) {
            return lbl_803B790C[i][0];
        }
    }
    return ARRAY_SIZE(lbl_803B790C);
}

static inline bool check_bit(u8 n, u16* mask)
{
    if ((n == 0xB) || (*mask & 1LL << n)) {
        return true;
    }
    return false;
}

void gm_80167FC4(SSSData* arg0)
{
    int temp_r30;
    GameRules* temp_r3;
    int i;

    u16* temp_r25;
    s32 temp_r28;
    u8 temp_r3_2;

    PAD_STACK(8);

    temp_r3 = gmMainLib_8015CC34();
    if (temp_r3->unk_x7 == 1) {
        arg0->force_stage_id = mnStageSel_8025BBD4();
        return;
    }
    arg0->force_stage_id = -1;
    switch (temp_r3->unk_x7) {
    case 0:
        arg0->unk_stage = 0;
        return;
    case 2:
        for (i = 0; i < 0x1D; i++) {
            temp_r28 = arg0->data.ordered_stage_index + i;
            temp_r28 = (temp_r28 + 1) % 29;
            temp_r30 = mnStageSel_8025BC08(temp_r28);
            temp_r25 = gmMainLib_8015EDA4();

            if (check_bit(get_flag_unk(temp_r30), temp_r25)) {
                arg0->force_stage_id = temp_r30;
                arg0->data.ordered_stage_index = temp_r28;
                return;
            }
        }
        break;
    case 3:
        arg0->data.loser = pad_inline(arg0, arg0->data.loser + 1);
        if (arg0->data.loser < 0) {
            arg0->data.loser = 0;
            arg0->unk_stage = 0;
        } else {
            arg0->unk_stage = arg0->data.loser + 1;
        }
        break;
    case 4:
        if (arg0->data.winner == -1) {
            arg0->unk_stage = pad_inline(arg0, HSD_Randi(4)) + 1;
        } else {
            arg0->unk_stage = pad_inline(arg0, arg0->data.winner) + 1;
        }
        break;
    }
}

s8 gm_801685D4(u8 arg0, u8 arg1)
{
    s8* temp_r3;

    if (gmMainLib_8015CC34()->handicap == 1) {
        temp_r3 = gmMainLib_8015CE44(arg0, arg1);
        if (temp_r3 != NULL) {
            return *temp_r3;
        }
    }
    return 0;
}

void gm_80168638(MatchEnd* arg0)
{
    u8 spC[4];
    s32 i;
    s8* temp_r3;
    if ((u8) gmMainLib_8015CC34()->handicap == 1) {
        for (i = 0; i < 4; i++) {
            temp_r3 = gmMainLib_8015CE44(i, arg0->player_standings[i].x4);
            if (temp_r3 != NULL) {
                spC[i] = (u8) *temp_r3;
            } else {
                spC[i] = 5;
            }
        }
        fn_80169000(arg0, spC);
        for (i = 0; i < 4; i++) {
            if ((u8) arg0->player_standings[i].slot_type != 3) {
                temp_r3 = gmMainLib_8015CE44(i, arg0->player_standings[i].x4);
                if (temp_r3 != NULL) {
                    *temp_r3 = (s8) spC[i];
                }
            }
        }
    }
}

void gm_80168710(MatchEnd* arg0, VsModeData* arg1)
{
    u8 buf[4];
    s32 count;
    s32 best;
    s32 j;

    best = -1;
    memzero(buf, 4);
    for (j = 0; j < 4; j++) {
        if (arg0->player_standings[j].slot_type == 0) {
            if ((s32) arg0->player_standings[j].is_big_loser > best) {
                best = arg0->player_standings[j].is_big_loser;
            }
        }
    }
    count = 0;
    for (j = 0; j < 4; j++) {
        if (arg0->player_standings[j].slot_type == 0 &&
            (s32) arg0->player_standings[j].is_big_loser == best) {
            buf[count] = j;
            count++;
        }
    }
    if (count != 0) {
        arg1->winner = (s8) buf[HSD_Randi(count)];
        return;
    }
    arg1->winner = -1;
}

s32 gm_801688AC(MatchEnd* arg0)
{
    u32 i;
    u32 sum = 0;
    struct MatchPlayerData* p = arg0->player_standings;
    for (i = 0; i < 6; i++) {
        if (arg0->player_standings[i].slot_type == 0) {
            sum += arg0->player_standings[i].xE;
        }
    }

    return sum;
}
int gm_80168940(MatchEnd* match_end)
{
    if (match_end->player_standings[0].slot_type == 0) {
        return match_end->player_standings[0].xE;
    }
    return 0;
}

void gm_8016895C(HSD_JObj* arg0, DynamicModelDesc* arg1, int idx)
{
    HSD_AnimJoint* anim = arg1->anims != NULL ? arg1->anims[idx] : NULL;
    HSD_MatAnimJoint* matanim =
        arg1->matanims != NULL ? arg1->matanims[idx] : NULL;
    HSD_ShapeAnimJoint* shapeanim =
        arg1->shapeanims != NULL ? arg1->shapeanims[idx] : NULL;
    HSD_JObjAddAnimAll(arg0, anim, matanim, shapeanim);
}

void fn_801689E4(HSD_JObj* arg0, DynamicModelDesc* arg1, int idx)
{
    HSD_AnimJoint* anim = arg1->anims != NULL ? arg1->anims[idx] : NULL;
    HSD_MatAnimJoint* matanim =
        arg1->matanims != NULL ? arg1->matanims[idx] : NULL;
    HSD_ShapeAnimJoint* shapeanim =
        arg1->shapeanims != NULL ? arg1->shapeanims[idx] : NULL;
    HSD_JObjAddAnimAll(arg0, anim, matanim, shapeanim);
}

void fn_80168A6C(void* arg0, void* arg1, s32 idx)
{
    struct {
        /* 0x00 */ s32** x0;
        /* 0x04 */ s32* x4;
        /* 0x08 */ s32 x8;
        /* 0x0C */ s32 xC;
    }* src = arg0;

    memzero(arg1, 0x20);

    if (src->x0[idx] != NULL) {
        ((s32*) arg1)[0] = src->x0[idx][0];
        ((s32*) arg1)[1] = src->x0[idx][1];
        ((s32*) arg1)[2] = src->x0[idx][2];
        ((s32*) arg1)[3] = src->x0[idx][3];
    }

    if (src->x4 != NULL) {
        ((s32*) arg1)[5] = src->x4[0];
        ((s32*) arg1)[6] = src->x4[1];
    }

    ((s32*) arg1)[4] = src->x8;
    ((s32*) arg1)[7] = src->xC;
}

f32 gm_80168B34(CharacterKind ckind, int arg1, int arg2)
{
    int base;
    if (ckind == CKIND_GKOOPS) {
        return 58.0F;
    }
    if (ckind == CKIND_BOY || ckind == CKIND_GIRL) {
        return 26.0F;
    }
    if (ckind == CKIND_MASTERH) {
        return 28.0F;
    }
    if (ckind == CKIND_CREZYH) {
        return 27.0F;
    }
    if (ckind == CKIND_ZELDA || ckind == CKIND_SEAK) {
        if (arg1 == 7) {
            base = 0x19;
        } else {
            base = 0x12;
        }
    } else if (ckind == CHKIND_SANDBAG) {
        return 59.0F;
    } else if (ckind == CHKIND_POPO) {
        base = 0xE;
    } else if (ckind > CKIND_SEAK) {
        base = ckind - 1;
    }
    return base + arg2 * 30;
}

float gm_80168BF8(int arg0)
{
    CharacterKind ckind = Player_GetPlayerCharacter(arg0);
    u32 costume = Player_GetCostumeId(arg0);
    gm_80168B34(ckind, Player_80036394(arg0), costume);
}

void gm_80168C5C(u32 arg0)
{
    switch (arg0) {
    case 0:
        lbAudioAx_800243F4(0x7C830);
        break;
    case 1:
        lbAudioAx_800243F4(0x7C831);
        break;
    case 2:
        lbAudioAx_800243F4(0x7C835);
        break;
    case 3:
        lbAudioAx_800243F4(0x7C83A);
        break;
    case 4:
        lbAudioAx_800243F4(0x7C83F);
        break;
    case 5:
        lbAudioAx_800243F4(0x7C840);
        break;
    case 6:
        lbAudioAx_800243F4(0x7C842);
        break;
    case 7:
        lbAudioAx_800243F4(0x7C844);
        break;
    case 8:
        lbAudioAx_800243F4(0x7C845);
        break;
    case 9:
        lbAudioAx_800243F4(0x7C846);
        break;
    case 10:
        lbAudioAx_800243F4(0x7C848);
        break;
    case 11:
        lbAudioAx_800243F4(0x7C84A);
        break;
    case 12:
        lbAudioAx_800243F4(0x7C84B);
        break;
    case 13:
        lbAudioAx_800243F4(0x7C84D);
        break;
    case 14:
        lbAudioAx_800243F4(0x7C83B);
        break;
    case 15:
        lbAudioAx_800243F4(0x7C83D);
        break;
    case 16:
        lbAudioAx_800243F4(0x7C84E);
        break;
    case 17:
        lbAudioAx_800243F4(0x7C84F);
        break;
    case 19:
        lbAudioAx_800243F4(0x7C850);
        break;
    case 18:
        lbAudioAx_800243F4(0x7C851);
        break;
    case 20:
        lbAudioAx_800243F4(0x7C834);
        break;
    case 21:
        lbAudioAx_800243F4(0x7C843);
        break;
    case 22:
        lbAudioAx_800243F4(0x7C832);
        break;
    case 23:
        lbAudioAx_800243F4(0x7C83C);
        break;
    case 24:
        lbAudioAx_800243F4(0x7C84C);
        break;
    case 25:
        lbAudioAx_800243F4(0x7C836);
        break;
    case 26:
        lbAudioAx_800243F4(0x7C849);
        break;
    case 29:
        lbAudioAx_800243F4(0x7C838);
        break;
    }
}

void fn_80168E54(s8 arg0, s8 arg1, u8 arg2, u8 arg3)
{
    if (arg3 != 0) {
        switch (arg2) {
        case 0:
            lbAudioAx_800237A8(0xC354, 0x7F, 0x40);
            break;
        case 1:
            lbAudioAx_800237A8(0xC352, 0x7F, 0x40);
            break;
        case 2:
            lbAudioAx_800237A8(0xC353, 0x7F, 0x40);
            break;
        }
    } else {
        if (arg0 == 0x12 && arg1 == 7) {
            arg0 = 0x13;
        } else if (arg0 == 0x13 && arg1 == 0x13) {
            arg0 = 0x12;
        }
        gm_80168C5C(arg0);
    }
}

void fn_80168F2C(s8 ignored)
{
    if (lbl_804D659A == 0) {
        lbl_804D659A = 3;
        lbAudioAx_80023870(0x7E, 0x7F, 0x40, 1);
    } else {
        lbl_804D659A--;
    }
}

void fn_80168F7C(void)
{
    lbl_804D659A = 0;
}

void gm_80168F88(void)
{
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x10);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

/// UnclePunch: Audio_LoadAnnouncer
void gm_80168FC4(void)
{
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

s32 fn_80169000(void* arg0, void* arg1)
{
    u8 handicaps[4];
    u8 positions[4];
    u8* p = (u8*) arg0;
    u8* hp = handicaps;
    u8* sp = (u8*) arg1;
    u8* hb = (u8*) arg1;
    s32 count;
    s32 i;
    u8* cur;
    u8 v;
    u8 t;

    count = 0;
    for (i = 0; i < 4; i++) {
        if (p[0x58] != 3) {
            count += 1;
            positions[p[0x5E]] = i;
        }
        *hp = *sp;
        hp += 1;
        sp += 1;
        p += 0xA8;
    }

    cur = &handicaps[positions[0]];
    v = *cur;
    t = 0;
    if (v >= 2 && handicaps[positions[count - 1]] <= 8) {
        *cur = v - 1;
        t = handicaps[positions[count - 1]];
        handicaps[positions[count - 1]] = t + 1;
    } else if (v == 1 && handicaps[positions[count - 1]] <= 7) {
        handicaps[positions[count - 1]] += 2;
    } else if (v >= 3 && handicaps[positions[count - 1]] == 9) {
        *cur -= 2;
    } else if (count >= 3) {
        if (v == 1 && handicaps[positions[count - 1]] == 8) {
            handicaps[positions[count - 1]] += 1;
            t = handicaps[positions[1]];
            if (t >= 2) {
                handicaps[positions[1]] = t - 1;
            }
        } else if (v == 2 && handicaps[positions[count - 1]] == 9) {
            *cur -= 1;
            t = handicaps[positions[1]];
            if (t >= 2) {
                handicaps[positions[1]] = t - 1;
            }
        }
    }
    hb[0] = handicaps[0];
    hb[1] = handicaps[1];
    hb[2] = handicaps[2];
    hb[3] = handicaps[3];
    return (s32) t;
}

/// #fn_80169000 done
u8 gm_80169238(u8 ckind)
{
    if (ckind >= ARRAY_SIZE(lbl_803D51A0)) {
        return 0;
    }
    return lbl_803D51A0[ckind].ncolors;
}

static inline u8 gm_80169238_inner2(u8 ckind)
{
    return gm_80169238(ckind);
}

static inline u8 gm_80169238_inner(u8 ckind)
{
    return gm_80169238_inner2(ckind);
}

static inline u8 gm_80169238_noinline(u8 ckind)
{
    return gm_80169238_inner(ckind);
}

u8 gm_80169264(u8 ckind)
{
    if (ckind >= ARRAY_SIZE(lbl_803D51A0)) {
        return 0;
    }
    return lbl_803D51A0[ckind].x1;
}

u8 gm_80169290(u8 ckind)
{
    if (ckind >= ARRAY_SIZE(lbl_803D51A0)) {
        return 0;
    }
    return lbl_803D51A0[ckind].x3;
}

u8 gm_801692BC(u8 ckind)
{
    if (ckind >= ARRAY_SIZE(lbl_803D51A0)) {
        return 0;
    }
    return lbl_803D51A0[ckind].x2;
}

void gm_801692E8(u32 secs, datetime* datetime)
{
    OSCalendarTime tm;

    lbTime_8000B028(&tm, secs);
    datetime->year = tm.year;
    datetime->month = tm.mon + 1;
    datetime->day = tm.mday;
    datetime->hour = tm.hour;
    datetime->minute = tm.min;
    if (tm.sec > 59) {
        datetime->second = 59;
    } else {
        datetime->second = tm.sec;
    }
}

struct lbl_8046B488_t* fn_80169364(void)
{
    return &lbl_8046B488;
}

u8 gm_80169370(s32 arg0)
{
    return ((u8*) &lbl_8046B488)[arg0];
}

int gm_80169384(void)
{
    return lbl_8046B488.x7;
}

s32 gm_80169394(void)
{
    return lbl_8046B488.unk_10_b3;
}

s32 fn_801693A8(void)
{
    return lbl_8046B488.unk_10_b2;
}

static inline bool gm_801693BC_inline(u8 ckind)
{
    if (ckind - 0x1B <= 1) {
        return true;
    }
    return false;
}

/// Player is Fighting Wireframe
bool gm_801693BC(int arg0)
{
    u8 ckind;
    PAD_STACK(8);
    if (Player_GetFlagsBit1(arg0) && (int) lbl_8046B488.x8 > 1) {
        return true;
    }
    ckind = Player_GetPlayerCharacter(arg0);
    ckind -= CKIND_BOY;
    if (ckind <= CKIND_GIRL - CKIND_BOY) {
        return true;
    }
    return false;
}

void fn_80169434(GmRouteCallback fn)
{
    lbl_8046B488.x1B8 = fn;
}

bool fn_80169444(bool arg0)
{
    struct lbl_8046B488_t* gp = &lbl_8046B488;

    if (gp->x1B8 != NULL) {
        if (gp->x1B8(arg0) == 1) {
            gp->x1B8 = NULL;
            return true;
        }
    }
    return false;
}
int gm_801694A0(HSD_GObj* arg0)
{
    int i;
    int count = lbl_8046B488.x7;
    PAD_STACK(8);
    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != Gm_PKind_NA &&
            Player_GetFlagsBit1(i) && Player_GetPlayerState(i) == 2)
        {
            count++;
        }
    }
    return count;
}

UNK_T gm_80169520(void)
{
    return lbl_8046B488.x20;
}

UNK_T gm_80169530(void)
{
    return lbl_8046B488.xA2;
}

UNK_T gm_80169540(void)
{
    return lbl_8046B488.x124;
}

void fn_80169550(int slot)
{
    s8 idx = lbl_8046B488.x1A6[slot];
    lbl_8046B488.x20[idx] = -1;
}

void fn_80169574(ssize_t size, s8* buf)
{
    memzero(buf, size);
    buf[size] = -2;
}

s32 fn_801695BC(u8 arg0, u8 arg1, u8 arg2, u8* arg3, u8* arg4)
{
    u8 sp1C[0x0C];
    s32 temp_r3_2;
    s32 var_ctr_2;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r7_2;
    s32 var_r8;
    s8 temp_r0;
    s8 temp_r3_3;
    s8 temp_r4;
    s8 temp_r4_3;
    s8 temp_r5;
    s8 var_r7;
    u32 var_ctr;
    u8 temp_r0_2;
    u8 temp_r3;
    u8 temp_r3_4;
    u8* temp_r4_2;
    u8* temp_r6;
    u8* var_r27;
    u8* var_r3;
    u8* var_r3_2;
    u8* var_r6;
    u8* temp_r27;

    temp_r3 = gm_80169238_noinline(arg0);
    if ((s8) arg0 != 0x21) {
        var_r7 = 0;
        if (temp_r3 > 0) {
            temp_r3_2 = (s32) temp_r3 - 8;
            if ((s32) temp_r3 > 8) {
                var_ctr = (u32) (temp_r3_2 + 7) >> 3;
                var_r6 = &sp1C[0];
                if (temp_r3_2 > 0) {
                    do {
                        var_r6[0] = (u8) var_r7;
                        var_r6[1] = (u8) (var_r7 + 1);
                        temp_r5 = var_r7 + 4;
                        var_r6[2] = (u8) (var_r7 + 2);
                        temp_r4 = var_r7 + 5;
                        temp_r3_3 = var_r7 + 6;
                        var_r6[3] = (u8) (var_r7 + 3);
                        temp_r0 = var_r7 + 7;
                        var_r7 += 8;
                        var_r6[4] = (u8) temp_r5;
                        var_r6[5] = (u8) temp_r4;
                        var_r6[6] = (u8) temp_r3_3;
                        var_r6[7] = (u8) temp_r0;
                        var_r6 += 8;
                        var_ctr -= 1;
                    } while (var_ctr != 0);
                }
            }
            var_r3_2 = &sp1C[var_r7];
            var_ctr_2 = (s32) temp_r3 - (s32) var_r7;
            if ((s32) var_r7 < (s32) temp_r3) {
                do {
                    *var_r3_2 = (u8) var_r7;
                    var_r3_2 += 1;
                    var_r7 += 1;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
        }

        if (arg1 == (s8) arg0) {
            sp1C[(s8) arg2] = 0xFF;
        }

        var_r27 = &sp1C[0];
        var_r28 = 0;
    loop_12:
        if (var_r28 < (s32) temp_r3) {
            temp_r4_2 = &sp1C[HSD_Randi((s32) temp_r3)];
            temp_r3_4 = *temp_r4_2;
            var_r28 += 1;
            *temp_r4_2 = *var_r27;
            *var_r27 = temp_r3_4;
            var_r27 += 1;
            goto loop_12;
        }

        var_r3 = arg3;
        var_r8 = 0;
        var_r7_2 = 0;
    loop_19:
        temp_r6 = &arg4[var_r7_2];
        if ((s8) *temp_r6 != -2) {
            if ((s8) arg0 == (s8) *var_r3) {
                if ((s8) sp1C[var_r8 % temp_r3] == -1) {
                    var_r8 += 1;
                }
                temp_r0_2 = sp1C[var_r8 % temp_r3];
                var_r8 += 1;
                *temp_r6 = temp_r0_2;
            }
            var_r7_2 += 1;
            var_r3 += 1;
            goto loop_19;
        }

        var_r28_2 = 1;
    loop_26:
        temp_r27 = &arg4[var_r28_2];
        if ((s8) temp_r27[0] != -2) {
            var_r3 = &arg3[var_r28_2];
            if (((s8) arg0 == (s8) var_r3[0]) &&
                ((s8) arg0 == (s8) var_r3[-1]))
            {
                var_r3 = (u8*) HSD_Randi(2);
                if (var_r3 != NULL) {
                    temp_r4_3 = (s8) temp_r27[0];
                    temp_r27[0] = temp_r27[-1];
                    temp_r27[-1] = (u8) temp_r4_3;
                }
            }
            var_r28_2 += 1;
            goto loop_26;
        }
        return (s32) var_r3;
    }
    return (s32) temp_r3;
}

#pragma push
#pragma dont_inline on
void fn_801697FC(s8 character, s8 costume, s8 new_character, s8 new_costume,
                 s8* buf)
{
    u8 ncolors = gm_80169238(character);
    int i;

    if (character == 0x21) {
        return;
    }
    if (new_character == character && costume == new_costume) {
        costume = (s8) ((costume + 1) % ncolors);
    }
    for (i = 0; (s8) buf[i] != -2; i++) {
        buf[i] = costume;
    }
}
#pragma pop

void fn_8016989C(u8* arg0, u8 arg1, u8 arg2, u8* arg3, u8* arg4)
{
    s32 i;
    for (i = 0; i < 3; i++) {
        fn_801695BC(arg0[i], arg1, arg2, arg3, arg4);
    };
}

#pragma push
#pragma dont_inline on
void fn_80169900(u8 arg0, struct lbl_8046B488_t* arg1, s8* arg2, s8* arg3)
{
    s32 var_r28 = 0;

    switch ((s32) arg0) {
    case 0: {
        s8* src = arg3;
        s8* dst = arg2;
        while (*src != -2) {
            *dst = (s8) arg1->x0;
            src += 1;
            dst += 1;
        }
        break;
    }
    case 1: {
        s8* dst = arg2;
        s8* src = arg3;
        while (*src != -2) {
            if (HSD_Randi(2) != 0) {
                *dst = arg1->x0;
            } else {
                *dst = arg1->x1;
            }
            src += 1;
            dst += 1;
        }
        break;
    }
    case 2: {
        s32 var_r27 = HSD_Randi(5);
        while (arg3[var_r28] != -2) {
            if (var_r27 != 0) {
                var_r27 -= 1;
                arg2[var_r28] = arg1->x0;
            } else {
                var_r27 = 5;
                if (HSD_Randi(2) != 0) {
                    if ((s32) arg1->x1 != 0x21 && gm_80164840(arg1->x1)) {
                        arg2[var_r28] = arg1->x1;
                    } else {
                        arg2[var_r28] = arg1->x0;
                    }
                } else {
                    if ((s32) arg1->x2 != 0x21 && gm_80164840(arg1->x2)) {
                        arg2[var_r28] = arg1->x2;
                    } else {
                        arg2[var_r28] = arg1->x0;
                    }
                }
            }
            var_r28 += 1;
        }
        break;
    }
    }
}
#pragma pop

long fn_80169A84(u8 arg0, s8* arg1, s8* arg2)
{
    s32 i;
    s32 count;
    s8* base;
    s8* p;
    s8* q;
    s8* dst;
    s8* src;
    u8 tmp;
    s8 result;

    base = (s8*) &lbl_8046B488;
    if ((s32) arg0 == 1) {
        i = 0;
        p = base + 0x1C0;
        do {
            if (i != 4 && gm_80164840_noinline((u8) i) != 0) {
                *p = i;
            } else {
                *p = -1;
            }
            i += 1;
            p += 1;
        } while (i < 0x1A);

        i = 0;
        p = base + 0x1C0;
        do {
            q = base + HSD_Randi(0x1B);
            tmp = q[0x1C0];
            i += 1;
            q[0x1C0] = (u8) *p;
            *p = tmp;
            p += 1;
        } while (i < 0x1A);

        count = 0;
        p = base + 0x1C0;
        i = 0xD;
        do {
            if ((s8) p[0] != -1) {
                count += 1;
                if (count > 0x10) {
                    p[0] = -1;
                }
            }
            if ((s8) p[1] != -1) {
                count += 1;
                if (count > 0x10) {
                    p[1] = -1;
                }
            }
            p += 2;
            i -= 1;
        } while (i != 0);

        dst = arg1;
        src = arg2;
        i = 0;
        while ((s8) *src != -2) {
            while ((s8) base[i + 0x1C0] == -1) {
                i = (i + 1) % 27;
            }
            result = Player_800325C8((CharacterKind) (s8) base[i + 0x1C0], 0);
            *dst = result;
            i += 1;
            src += 1;
            dst += 1;
        }
        return (s32) result;
    } else if ((s8) arg0 >= 1) {
        return (s32) base;
    } else if ((s8) arg0 >= 0) {
        dst = arg1;
        src = arg2;
        while ((s8) *src != -2) {
            *dst = -1;
            src += 1;
            dst += 1;
        }
        return (s32) src;
    } else {
        return (s32) base;
    }
}

void fn_80169C54(s8 arg0, s8 arg1)
{
    s32 buf[7];
    struct lbl_8046B488_t* st;
    s8* pc;
    s8* cp;
    s32 n;
    s32 count;
    s32 j;
    s32 k;
    s8 p;
    u8 ch;

    n = 0;
    st = fn_8016AE60();
    pc = (s8*) st;
    buf[0] = -1;
    buf[1] = -1;
    buf[2] = -1;
    buf[3] = -1;
    buf[4] = -1;
    buf[5] = -1;
    buf[6] = -1;
    j = 3;
    do {
        if ((s32) *pc == 4) {
            if (st->xB == 0) {
                count = gm_80169238_noinline(4U);
                for (k = 0; k < count; k++) {
                    buf[k] = k;
                    n += 1;
                }
            } else {
                n = 1;
                buf[0] = st->xC;
            }
            break;
        }
        pc += 1;
        j -= 1;
    } while (j != 0);

    if (arg0 == 4) {
        buf[n] = arg1;
        n += 1;
    }
    if (n > 0) {
        cp = (s8*) st;
        j = 0;
        do {
            ch = *cp;
            if (((s8) ch != 0x21) && ((s8) ch != 4)) {
                p = Player_800325C8((CharacterKind) (s8) ch, 0);
                if ((p != -1) && (p != 4)) {
                    for (k = 0; k < n; k++) {
                        Player_80031DA8((s32) p, buf[k]);
                    }
                }
                p = Player_800325C8((CharacterKind) (s8) ch, 1);
                if ((p != -1) && (p != 4)) {
                    for (k = 0; k < n; k++) {
                        Player_80031DA8((s32) p, buf[k]);
                    }
                }
            }
            j += 1;
            cp += 1;
        } while (j < 3);
        if (arg0 != 4) {
            p = Player_800325C8((CharacterKind) arg0, 0);
            if ((p != -1) && (p != 4)) {
                for (k = 0; k < n; k++) {
                    Player_80031DA8((s32) p, buf[k]);
                }
            }
            p = Player_800325C8((CharacterKind) arg0, 1);
            if ((p != -1) && (p != 4)) {
                for (k = 0; k < n; k++) {
                    Player_80031DA8((s32) p, buf[k]);
                }
            }
        }
    }
}

void fn_80169F50(s8 arg0, s8 arg1)
{
    struct lbl_8046B488_t* gp = &lbl_8046B488;
    s32 i;
    s32 flag;
    s8 v;
    s8* p;

    flag = 0;
    if (gp->x0 == 4) {
        flag = 1;
    } else {
        p = &gp->x1;
        if (gp->x1 == 4) {
            flag = 1;
        } else if (p[1] == 4) {
            flag = 1;
        }
    }

    if (flag == 1 && gp->xE != 0) {
        for (i = 0; gp->x20[i] != -2; i++) {
            v = gp->x20[i];
            if (v == -1) {
                continue;
            }
            if (gp->xA2[i] != 4) {
                continue;
            }
            if (gp->x124[i] == -1) {
                continue;
            }
            Player_80031DA8(gp->x124[i], v);
        }
    }

    if (arg0 == 4 && gp->xE != 0) {
        for (i = 0; gp->x20[i] != -2; i++) {
            if (gp->x20[i] == -1) {
                continue;
            }
            if (gp->x124[i] == -1) {
                continue;
            }
            Player_80031DA8(gp->x124[i], arg1);
        }
    }
}

void fn_8016A09C(void)
{
    s32 i;
    s32 var_r29;
    s32 j;
    PAD_STACK(4);
    var_r29 = 0;

    gm_8016AE44();
    lbl_8046B488.unk_10_b1 = 1;
    lbl_8046B488.unk_10_b0 = 0;

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_NA) {
            if (var_r29 >= (j = (s32) lbl_8046B488.x9)) {
                break;
            }
            Player_SetFlagsBit1(i);
            var_r29++;
        }
    }

    for (j = 0; j < 6; j++) {
        if (Player_GetFlagsBit1(j) != 0) {
            Player_SetTeam(j, 4);
        }
    }
}

/// @todo Offset mismatch indicates a TU split between #lbl_8046B378 and
///       #lbl_8046B488
void gm_8016A164(void)
{
    int i;
    lbl_8046B6A0_t* match_info = gm_8016AE44();
    PAD_STACK(4);

    match_info->is_singleplayer = false;
    lbl_8046B488.x8 = 0;
    lbl_8046B488.x7 = 0;
    lbl_8046B488.unk_10_b1 = false;
    lbl_8046B488.unk_10_b0 = false;
    fn_8016B138();

    for (i = 1; i < 6; i++) {
        Player_SetSlottype(i, Gm_PKind_NA);
        Player_UnsetFlagsBit1(i);
    }
}

s32 fn_8016A1E4(void)
{
    return lbl_8046B488.unk_10_b0;
}

bool gm_8016A1F8(void)
{
    if (lbl_8046B488.unk_10_b1) {
        return true;
    }
    return false;
}

void gm_8016A21C(StartMeleeRules* arg0)
{
    arg0->x54 = (void*) &lbl_8046B488;
}

static inline s32 fn_801695BC_noinline(u8 arg0, u8 arg1, u8 arg2, u8* arg3,
                                       u8* arg4)
{
    return fn_801695BC(arg0, arg1, arg2, arg3, arg4);
}

static inline void fn_801697FC_noinline(s8 character, s8 costume,
                                        s8 new_character, s8 new_costume,
                                        s8* buf)
{
    fn_801697FC(character, costume, new_character, new_costume, buf);
}

static inline void fn_80169900_noinline(u8 arg0, struct lbl_8046B488_t* arg1,
                                        s8* arg2, s8* arg3)
{
    fn_80169900(arg0, arg1, arg2, arg3);
}

s32 gm_8016A22C(s8 k0, s8 k1, s8 k2, u8 a3, u8 a4, int a5, int mode, int a7,
                u8 color, u8 p87, u8 p8b, int x6, int x7, int x9, int xA,
                int flag2, int flag1, f32 f1, f32 f2)
{
    u8* kinds;
    int i;

    memzero(&lbl_8046B488, 0x1C0);

    lbl_8046B488.x0 = k0;
    lbl_8046B488.x1 = k1;
    lbl_8046B488.x2 = k2;

    lbl_8046B488.x3 = a3;
    lbl_8046B488.x4 = a4;
    lbl_8046B488.x5 = (u8) a5;

    lbl_8046B488.x6 = (u8) x6;
    lbl_8046B488.x7 = (u8) x7;
    lbl_8046B488.x8 = (u8) x7;

    if (x9 > 5) {
        x9 = 5;
    }
    lbl_8046B488.x9 = (u8) x9;

    lbl_8046B488.xA = (u8) xA;

    lbl_8046B488.x14 = f1;
    lbl_8046B488.x18 = f2;

    lbl_8046B488.unk_10_b2 = flag2;
    lbl_8046B488.unk_10_b1 = flag1;

    lbl_8046B488.x1C = 1.0f;

    lbl_8046B488.xB = (u8) mode;
    lbl_8046B488.xD = (u8) a7;
    lbl_8046B488.xE = color;

    lbl_8046B488.xC = a3;

    lbl_8046B488.x1AC = p87;
    lbl_8046B488.x1AD = 0x21;
    lbl_8046B488.x1B2 = p8b;

    memzero(lbl_8046B488.x20, lbl_8046B488.x7);
    lbl_8046B488.x20[lbl_8046B488.x7] = (s8) -2;

    fn_80169900_noinline(lbl_8046B488.xD, &lbl_8046B488, lbl_8046B488.xA2,
                lbl_8046B488.x20);

    kinds = (u8*) &lbl_8046B488.x0;

    switch (lbl_8046B488.xB) {
    case 0:
        for (i = 0; i < 3; i++) {
            fn_801695BC_noinline(kinds[i], p87, p8b, (u8*) lbl_8046B488.xA2,
                        (u8*) lbl_8046B488.x20);
        }
        break;

    case 1:
        for (i = 0; i < 3; i++) {
            fn_801697FC_noinline(
                kinds[i], lbl_8046B488.xC, p87, p8b,
                lbl_8046B488
                    .x20); // This was being inlined, hence the no-inline
        }
        break;
    }

    return fn_80169A84(lbl_8046B488.xE, lbl_8046B488.x124, lbl_8046B488.x20);
}

void gm_8016A404(s32 arg0)
{
    M2C_FIELD(&lbl_8046B488, s32*, 0x1BC) = arg0;
}

void gm_8016A414(f32 arg8)
{
    M2C_FIELD(&lbl_8046B488, f32*, 0x1C) = arg8;
}

void gm_8016A424(s8 arg0)
{
    lbl_8046B488.xF = arg0;
}

void gm_8016A434(void)
{
    lbl_8046B488.unk_10_b3 = 1;
}

void fn_8016A450(void)
{
    lbl_8046B488.unk_10_b4 = 1;
}

void fn_8016A46C(void)
{
    lbl_8046B488.unk_10_b6 = 1;
}

void fn_8016A488(s32 arg0)
{
    if (gm_8016AE44()->hud_enabled == true) {
        Player_80031848(arg0);
    }
}

void fn_8016A4C8(void)
{
    Vec3 spDC;
    f32 var_f1;
    s32 var_r27;
    s32 i;
    s32 j;
    s32 var_r4;
    s32 var_r23;
    s32 r;
    s8 chr;
    u8 cos;
    s32 var_r0;
    void (*fp)(s32, u8);

    var_r27 = 0;
    if (lbl_8046B488.unk_10_b1) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 == 0) {
        return;
    }
    for (i = 0; i < 6; i++) {
        if (Player_GetFlagsBit1(i) != 0 && Player_GetPlayerState(i) == 0 &&
            (s32) lbl_8046B488.x7 > 0) {
            if (lbl_8046B488.x7 != 0) {
                lbl_8046B488.x7 -= 1;
            }
            fn_8016B738(1);
            Player_80036D24(i);
            lbl_8046B488.x1A6[i] = lbl_8046B488.x7;
            Player_SetFlagsBit1(i);
            Player_SetTeam(i, 4);
            Ground_801C2D24(i + (lbl_8046B488.xA - 1), &spDC);
            spDC.y = Stage_GetCamBoundsTopOffset();
            Player_80032768(i, &spDC);
            Player_SetSlottype(i, Gm_PKind_Cpu);
            Player_SetPlayerCharacter(
                i, (CharacterKind) (s8) (u8) lbl_8046B488.xA2[lbl_8046B488.x7]);
            Player_SetStocks(i, 1);
            cos = lbl_8046B488.x20[lbl_8046B488.x7];
            Player_SetCostumeId(i, (s8) cos);
            chr = Player_GetPlayerCharacter(i);
            var_r4 = 0;
            for (j = 0; j < 6; j++) {
                if (Player_GetPlayerSlotType(j) != Gm_PKind_NA &&
                    Player_GetFlagsBit1(j) == 0 &&
                    chr == Player_GetPlayerCharacter(j) &&
                    (s8) cos == Player_GetCostumeId(j)) {
                    var_r4 = 1;
                    break;
                }
            }
            Player_SetControllerIndex(i, var_r4);
            Player_SetMoreFlagsBit6(i, lbl_8046B488.xF);
            Player_SetMoreFlagsBit1(i, 0U);
            if (spDC.x >= 0.0f) {
                var_f1 = -1.0f;
            } else {
                var_f1 = 1.0f;
            }
            Player_SetFacingDirection(i, var_f1);
            Player_SetHUDDamage(i, 0);
            Player_SetPlayerId(i, i);
            Player_SetFlagsBit0(i, 0);
            Player_SetNametagSlotID(i, 0x78);
            Player_SetPlayerAndEntityCpuLevel(i, (s32) lbl_8046B488.x6);
            var_r23 = 0x17;
            if ((s32) lbl_8046B488.x7 != 1) {
                r = HSD_Randi(4);
                if (r != 3) {
                    if (r < 3) {
                        if (r < 0) {
                            var_r23 = 0x17;
                        }
                    } else {
                        var_r23 = 0x17;
                    }
                } else {
                    var_r23 = 0x18;
                }
            }
            Player_SetPlayerAndEntityCpuType(i, var_r23);
            if (lbl_8046B488.unk_10_b4) {
                Player_SetFlagsBit5(i, 1U);
                Player_SetPlayerAndEntityCpuType(i, 0x1B);
            }
            if (lbl_8046B488.unk_10_b6) {
                Player_SetFlagsAEBit0(i, 1U);
            } else {
                Player_SetFlagsAEBit0(i, 0U);
            }
            Player_SetFlagsBit6(i, lbl_8046B488.unk_10_b5);
            Player_SetModelScale(i, lbl_8046B488.x1C);
            Player_SetAttackRatio(i, lbl_8046B488.x14);
            Player_SetDefenseRatio(i, lbl_8046B488.x18);
            if ((s32) lbl_8046B488.x8 > 1) {
                Player_SetMoreFlagsBit5(i, 1U);
            } else {
                Player_SetMoreFlagsBit5(i, 0U);
            }
            if (Player_GetPlayerCharacter(i) == CKIND_KIRBY &&
                lbl_8046B488.xE != 0) {
                Player_SetUnk4D(i, (s8) (u8) lbl_8046B488.x124[lbl_8046B488.x7]);
                Player_SetFlagsAEBit1(i, 1U);
            }
            fp = *(void (**)(s32, u8)) ((u8*) &lbl_8046B488 + 0x1BC);
            if (fp != NULL) {
                fp(i, lbl_8046B488.x7);
            }
            Player_SetStructFunc(i, fn_8016A488);
            Player_80031AD0(i);
            ifStatus_802F6508(i);
            un_802FD28C(i);
        }
    }
    if ((s32) lbl_8046B488.x7 == 0) {
        for (j = 0; j < 6; j++) {
            if (Player_GetPlayerSlotType(j) != Gm_PKind_NA &&
                Player_GetFlagsBit1(j) != 0 && Player_GetStocks(j) != 0) {
                var_r27 = 1;
                break;
            }
        }
        if (var_r27 == 0) {
            lbl_8046B488.unk_10_b0 = 1;
            lbl_8046B488.unk_10_b1 = 0;
            if (lbl_8046B488.x1B8 != NULL && lbl_8046B488.x1B8(1) == 1) {
                lbl_8046B488.x1B8 = NULL;
            }
        }
    }
}

void gm_8016A92C(StartMeleeRules* arg0)
{
    lbl_8046B668.arr2[0] = -2;
    arg0->x58 = &lbl_8046B668;
}

bool gm_8016A944(void)
{
    if (gm_8016AE50()->x58 != NULL) {
        return true;
    }
    return false;
}

UNK_T gm_8016A97C(void)
{
    return &M2C_FIELD(&lbl_8046B668, UNK_T*, 0x1C);
}

struct lbl_8046B668_t* gm_8016A98C(void)
{
    return &lbl_8046B668;
}

int gm_8016A998(s8 arg0, s8 arg1)
{
    int i;
    struct lbl_8046B668_t* ptr = &lbl_8046B668;
    for (i = 0; i < 27; i++) {
        if (ptr->arr2[i] == -2) {
            ptr->arr2[i + 1] = -2;
            ptr->arr2[i] = arg1;
            ptr->arr1[i] = (u8) arg0;
            return i;
        }
    }
    return -1;
}

int gm_8016A9E8(u8 arg0, s8 arg1)
{
    int i;
    int found;
    struct lbl_8046B668_t* ptr = &lbl_8046B668;

    found = -1;
    for (i = 0; i < 27; i++) {
        if (ptr->arr2[i] == -2) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        for (i = found; i >= 0; i--) {
            ptr->arr2[i + 1] = ptr->arr2[i];
            ptr->arr1[i + 1] = ptr->arr1[i];
        }
        ptr->arr2[0] = arg1;
        ptr->arr1[0] = (u8) arg0;
        found++;
    }
    return found;
}

bool gm_8016AC44(s8 ckind, s8 costume_id)
{
    s32 idx;
    s32 i;
    bool found;

    found = false;
    if (gm_8016AE50()->x58 != NULL) {
        found = true;
    }
    if (found == 1) {
        idx = -1;
        for (i = 0; i < 27; i++) {
            if (lbl_8046B668.arr2[i] == -2) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            for (i = idx; i >= 0; i--) {
                if (lbl_8046B668.arr2[i] == costume_id &&
                    ckind == lbl_8046B668.arr1[i])
                {
                    return true;
                }
            }
        }
    }
    return false;
}
