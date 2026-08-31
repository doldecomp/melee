#include "gm_1601.h"

#include "gm_1601.static.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmstamina.h"
#include "placeholder.h"
#include "stddef.h"

#include <platform.h>

#include "baselib/gobjplink.h"
#include "baselib/jobj.h"
#include "cm/camera.h"

#include "ft/forward.h"
#include "gm/forward.h"

#include "gm/types.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "if/ifstatus.h"
#include "lb/lb_00B0.h"
#include "lb/lb_013B.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbtime.h"
#include "mn/mnstagesel.h"
#include "mn/types.h"

#include "pl/forward.h"

#include "pl/player.h"
#include "pl/plbonus.h"
#include "pl/plbonuslib.h"
#include "sc/types.h"
#include "ty/toy.h"

#include <dolphin/pad.h>
#include <baselib/sislib.h>
#include <baselib/video.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/debugconsole_main.h>
#include <sysdolphin/baselib/hsd_3915.h>
#include <sysdolphin/baselib/random.h>
#include <melee/gm/gm_1A45.h>
#include <melee/pl/player.h>

/* 166A8C */ static f32 fn_80166A8C(Vec3*, Vec3*);

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
#ifdef MUST_MATCH
    u8 x0;
    u8 x1;
#else
    unsigned int x0;
    unsigned int x1;
#endif

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

static struct VictoryTheme ckind_victory_themes[0x1B] = {
    {
        CKIND_CAPTAIN,
        0x11,
    },
    {
        CKIND_DONKEY,
        0xD,
    },
    {
        CKIND_FOX,
        0x10,
    },
    {
        CKIND_GAMEWATCH,
        0xF,
    },
    {
        CKIND_KIRBY,
        0x14,
    },
    {
        CKIND_KOOPA,
        0x16,
    },
    {
        CKIND_LINK,
        0x15,
    },
    {
        CKIND_LUIGI,
        0x16,
    },
    {
        CKIND_MARIO,
        0x16,
    },
    {
        CKIND_MARS,
        0xE,
    },
    {
        CKIND_MEWTWO,
        0x18,
    },
    {
        CKIND_NESS,
        0x17,
    },
    {
        CKIND_PEACH,
        0x16,
    },
    {
        CKIND_PIKACHU,
        0x18,
    },
    {
        CKIND_POPONANA,
        0x13,
    },
    {
        CKIND_PURIN,
        0x18,
    },
    {
        CKIND_SAMUS,
        0x19,
    },
    {
        CKIND_YOSHI,
        0x1D,
    },
    {
        CKIND_ZELDA,
        0x15,
    },
    {
        CKIND_SEAK,
        0x15,
    },
    {
        CKIND_FALCO,
        0x10,
    },
    {
        CKIND_CLINK,
        0x15,
    },
    {
        CKIND_DRMARIO,
        0x16,
    },
    {
        CKIND_EMBLEM,
        0xE,
    },
    {
        CKIND_PICHU,
        0x18,
    },
    {
        CKIND_GANON,
        0x15,
    },
    {
        CHKIND_NONE,
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
    struct VictoryTheme* theme = ckind_victory_themes;

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

bool gm_80160474(CharacterKind ckind, GameModeKind mode)
{
    switch (mode) {
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

char* gm_801604DC(CharacterKind ckind, GameModeKind mode)
{
    int var_r3;

    switch (mode) {
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
    return Toy_8030813C(var_r3) + 4;
}

char* gm_80160564(CharacterKind ckind, GameModeKind mode)
{
    int var_r3;

    switch (mode) {
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
    return Toy_8030813C(var_r3) + 0x24;
}

u8 gm_SelKindToUnlockIndex(SelectableCharacterKind selkind)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (selkind == lbl_803B78C8[i].selkind) {
            return lbl_803B78C8[i].idx;
        }
    }
    return NUM_UNLOCKABLE_CHARACTERS;
}

s8 gm_CKindToUnlockIndex(CharacterKind ckind)
{
    return gm_SelKindToUnlockIndex(gm_CKindToSelKind(ckind));
}

static inline u8 get_unlockable_selkind_by_bit_index(int unlock_bit_index)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (unlock_bit_index == lbl_803B78C8[i].idx) {
            return lbl_803B78C8[i].selkind;
        }
    }
    return SELKIND_COUNT;
}

u8 gm_GetCKindByUnlockIndex(int unlockable_character_bit_index)
{
    return gm_SelKindToCKind(
        get_unlockable_selkind_by_bit_index(unlockable_character_bit_index));
}

u8 fn_80160710(int arg0)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (arg0 == lbl_803B78C8[i].idx) {
            return lbl_803B78C8[i].notification_id;
        }
    }
    return 0x42;
}

int gm_8016075C(SelectableCharacterKind selkind)
{
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (selkind == lbl_803B78C8[i].selkind) {
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

GXColor gm_80160968(u32 arg0)
{
    return lbl_803B7864[(u8) arg0];
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

static inline void gm_80160B40_init_text(HSD_Text* text, HSD_Text** tmp_text)
{
    *tmp_text = text;
    if (lbLang_IsSavedLanguageUS()) {
        text->default_kerning = 1;
    }
}

void gm_80160B40(HSD_Text* text, u8 ckind, u8 arg2)
{
    u8 tmp_ckind = ckind;
    HSD_Text* tmp_text;
    f32 var_f31;
    const char* str;

    gm_80160B40_init_text(text, &tmp_text);
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

void gm_80160C90(HSD_Text* text, u8 fighter_id, u8 arg2)
{
    HSD_Text* tmp_text = text;
    u8 tmp_ckind = fighter_id;
    const char* str;
    f32 size;
    bool use_alt_name;

    if (lbLang_IsSavedLanguageUS() != 0) {
        text->default_kerning = 1;
    }
    str = arg2 ? fn_801609E0(tmp_ckind) : gm_80160980(tmp_ckind);

    if (lbLang_IsSavedLanguageUS() != 0) {
        f32 temp;
        use_alt_name = false;
        if (arg2 && lbl_803D50E4[tmp_ckind] != NULL) {
            use_alt_name = true;
        }
        if (use_alt_name) {
            temp = lbl_803B7784[tmp_ckind];
        } else {
            temp = lbl_803B767C[tmp_ckind];
        }
        size = temp;
    } else {
        f32 temp;
        use_alt_name = false;
        if (arg2 && lbl_803D5060[tmp_ckind] != NULL) {
            use_alt_name = true;
        }
        if (use_alt_name) {
            temp = lbl_803B7700[tmp_ckind];
        } else {
            temp = lbl_803B75F8[tmp_ckind];
        }
        size = temp;
    }
    HSD_SisLib_803A7548(
        tmp_text, HSD_SisLib_803A6B98(tmp_text, 0.0F, 0.0F, str, use_alt_name),
        size, 1.0F);
}

void fn_80160DE8(HSD_JObj* arg0, u8 arg1, s32 arg2, u8 arg3, f32 farg0,
                 f32 farg1)
{
    HSD_Text* tmp_text = (HSD_Text*) arg0;
    u8 tmp_ckind = arg1;
    const char* str;
    f32 size;
    bool use_alt_name;

    if (lbLang_IsSavedLanguageUS() != 0) {
        ((HSD_Text*) arg0)->default_kerning = 1;
    }
    str = arg3 ? fn_801609E0(tmp_ckind) : gm_80160980(tmp_ckind);

    if (lbLang_IsSavedLanguageUS() != 0) {
        f32 temp;
        use_alt_name = false;
        if (arg3 && lbl_803D50E4[tmp_ckind] != NULL) {
            use_alt_name = true;
        }
        if (use_alt_name) {
            temp = lbl_803B75F8[tmp_ckind + 0x63];
        } else {
            temp = lbl_803B75F8[tmp_ckind + 0x21];
        }
        size = temp;
    } else {
        f32 temp;
        use_alt_name = false;
        if (arg3 && lbl_803D5060[tmp_ckind] != NULL) {
            use_alt_name = true;
        }
        if (use_alt_name) {
            temp = lbl_803B75F8[tmp_ckind + 0x42];
        } else {
            temp = lbl_803B75F8[tmp_ckind];
        }
        size = temp;
    }
    HSD_SisLib_803A70A0(tmp_text, arg2, (char*) str);
    HSD_SisLib_803A7548(tmp_text, arg2, size * farg0, farg1);
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
    u8 spC[12];
    MatchPlayerData* best_player;
    s32 idx;
    s32 cnt;
    MatchPlayerData* player;
    s32 i;
    s32 result = fn_80161004(arg0);

    idx = 4;
    cnt = 0;
    if (arg0->is_teams == 1) {
        for (i = 0; i < 4; i++) {
            player = &arg0->player_standings[i];
            if (player->slot_type != 3 &&
                arg0->team_standings[player->team].is_big_loser == result)
            {
                spC[i] = 1;
                cnt = 1;
                idx = i;
            } else {
                spC[i] = 0;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            player = &arg0->player_standings[i];
            if (player->slot_type != 3 && player->is_big_loser == result) {
                if (idx != 4) {
                    cnt = 1;
                } else {
                    idx = i;
                }
                spC[i] = 1;
            } else {
                spC[i] = 0;
            }
        }
    }
    if (cnt == 0) {
        return idx;
    }

    idx = 4;
    for (i = 0; i < 4; i++) {
        if (spC[i]) {
            if (idx == 4) {
                idx = i;
            } else if ((u32) arg0->player_standings[idx].x20 >
                       (u32) arg0->player_standings[i].x20)
            {
                idx = i;
            }
            best_player = &arg0->player_standings[idx];
        }
    }
    cnt = 0;
    for (i = 0; i < 4; i++) {
        if (spC[i] && idx != i) {
            player = &arg0->player_standings[i];
            if ((u32) player->x20 == (u32) best_player->x20) {
                cnt += 1;
            } else {
                spC[i] = 0;
            }
        }
    }
    if (cnt == 0) {
        return idx;
    }

    idx = 4;
    for (i = 0; i < 4; i++) {
        if (spC[i]) {
            if (idx == 4) {
                idx = i;
            } else if ((u32) arg0->player_standings[idx].x24 <
                       (u32) arg0->player_standings[i].x24)
            {
                idx = i;
            }
            best_player = &arg0->player_standings[idx];
        }
    }
    cnt = 0;
    for (i = 0; i < 4; i++) {
        if (spC[i] && idx != i) {
            player = &arg0->player_standings[i];
            if ((u32) player->x24 == (u32) best_player->x24) {
                cnt += 1;
            } else {
                spC[i] = 0;
            }
        }
    }
    if (cnt == 0) {
        return idx;
    }

    idx = 4;
    for (i = 0; i < 4; i++) {
        if (spC[i]) {
            if (idx == 4) {
                idx = i;
            } else if (arg0->player_standings[idx].x44 >
                       arg0->player_standings[i].x44)
            {
                idx = i;
            }
            best_player = &arg0->player_standings[idx];
        }
    }
    cnt = 0;
    for (i = 0; i < 4; i++) {
        if (spC[i] && idx != i) {
            player = &arg0->player_standings[i];
            if (player->x44 == best_player->x44) {
                cnt += 1;
            } else {
                spC[i] = 0;
            }
        }
    }
    if (cnt == 0) {
        return idx;
    }

    idx = 4;
    for (i = 0; i < 4; i++) {
        if (spC[i]) {
            if (idx == 4) {
                idx = i;
            } else if (arg0->player_standings[idx].x50 <
                       arg0->player_standings[i].x50)
            {
                idx = i;
            }
            best_player = &arg0->player_standings[idx];
        }
    }
    cnt = 0;
    for (i = 0; i < 4; i++) {
        if (spC[i] && idx != i) {
            player = &arg0->player_standings[i];
            if (player->x50 == best_player->x50) {
                cnt += 1;
            } else {
                spC[i] = 0;
            }
        }
    }
    if (cnt == 0) {
        return idx;
    }
    {
        s32 j;
        for (j = 0; j < 4; j++) {
            if (spC[j]) {
                return j;
            }
        }
        return result;
    }
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

static inline u32 fn_80161C90_count_players(MatchEnd* match_end)
{
    u32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (match_end->player_standings[i].slot_type != 3) {
            count += 1;
        }
    }
    return count;
}

void fn_80161C90(MatchEnd* arg0, int arg1, u16* arg2)
{
    MatchPlayerData* p = &arg0->player_standings[arg1];
    struct gm_stats* s = (struct gm_stats*) arg2;
    u32 count;
    s32 flag;
    s32 i;

    s->unk0 = (s->unk0 + p->self_destructs > 0xFFFF)
                  ? 0xFFFF
                  : s->unk0 + p->self_destructs;
    s->unk4 =
        (s->unk4 + p->x38 > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unk4 + p->x38;
    s->unk8 =
        (s->unk8 + p->x3C > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unk8 + p->x3C;
    s->unkC =
        (s->unkC + p->x40 > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unkC + p->x40;
    s->unk10 =
        (s->unk10 + p->x44 > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unk10 + p->x44;
    s->unk14 =
        (s->unk14 + p->x48 > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unk14 + p->x48;
    if (s->unk18 < p->x4C) {
        s->unk18 = p->x4C;
    }
    s->unk1A = (s->unk1A + 1 > 0xFFFF) ? 0xFFFF : s->unk1A + 1;
    {
        if (arg1 == fn_80165548(arg0, fn_80165418(arg0), fn_801654A0(arg0))) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag != 0) {
            s->unk1C = (s->unk1C + 1 > 0xFFFF) ? 0xFFFF : s->unk1C + 1;
        }
    }
    if (arg1 == fn_80161154(arg0)) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag != 0) {
        s->unk1E = (s->unk1E + 1 > 0xFFFF) ? 0xFFFF : s->unk1E + 1;
    }
    s->unk20 = (s->unk20 + arg0->frame_count / 60 > 0xFFFFFFFFU)
                   ? 0xFFFFFFFFU
                   : s->unk20 + arg0->frame_count / 60;
    count = fn_80161C90_count_players(arg0);
    count = s->unk24 + count;
    if (count > 0xFFFF) {
        count = 0xFFFF;
    }
    s->unk24 = count;
    s->unk28 =
        (s->unk28 + p->x50 > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unk28 + p->x50;
    gmMainLib_8015EDBC()->x10 =
        (p->x50 + gmMainLib_8015EDBC()->x10 > 0xFFFFFFFFU)
            ? 0xFFFFFFFFU
            : p->x50 + gmMainLib_8015EDBC()->x10;
    s->unk2C =
        (s->unk2C + p->x54 > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unk2C + p->x54;
    s->unk30 =
        (s->unk30 + p->x58 > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unk30 + p->x58;
    s->unk34 =
        (s->unk34 + p->x5C > 0xFFFFFFFFU) ? 0xFFFFFFFFU : s->unk34 + p->x5C;
    if (arg0->match_kind == 2) {
        s->unk38 = (s->unk38 + p->x60 > 0xFFFFFFFFU) ? 0xFFFFFFFFU
                                                     : s->unk38 + p->x60;
        s->unk3C = (s->unk3C + p->x64 > 0xFFFFFFFFU) ? 0xFFFFFFFFU
                                                     : s->unk3C + p->x64;
        s->unk40 = (s->unk40 + p->x68 > 0xFFFFFFFFU) ? 0xFFFFFFFFU
                                                     : s->unk40 + p->x68;
    }
}

void fn_80162068(MatchEnd* match_end)
{
    ssize_t i;
    ssize_t j;
    struct MatchPlayerData* pdata_i;
    struct MatchPlayerData* pdata_j;
    struct FighterData* fd;
    s32 sum;

    for (i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        pdata_i = &match_end->player_standings[i];
        if (pdata_i->slot_type == 3) {
            continue;
        }
        fd = GetPersistentFighterData(gm_CKindToSelKind(pdata_i->ckind));
        for (j = 0; j < PAD_MAX_CONTROLLERS; j++) {
            pdata_j = &match_end->player_standings[j];
            if (i == j || pdata_j->slot_type == Gm_PKind_NA) {
                continue;
            }
            if (pdata_i->kills[j] +
                    fd->fighter_kos[gm_CKindToSelKind(pdata_j->ckind)] >
                U16_MAX)
            {
                sum = U16_MAX;
            } else {
                sum = pdata_i->kills[j] +
                      fd->fighter_kos[gm_CKindToSelKind(pdata_j->ckind)];
            }
            fd->fighter_kos[gm_CKindToSelKind(pdata_j->ckind)] = (u16) sum;
        }
        fn_80161C90(match_end, i, &fd->sd_count);
    }
}
void fn_80162170(MatchEnd* arg0)
{
    MatchEnd* cur;
    s32 i;
    MatchPlayerData* p;
    s32 j;
    MatchPlayerData* q;
    s32 play_time;

    for (i = 0, cur = arg0; i < 4;
         i++, cur = (MatchEnd*) ((MatchPlayerData*) cur + 1))
    {
        p = cur->player_standings;
        if (p->slot_type == 3) {
            continue;
        }
        if (p->x4 == 0x78) {
            continue;
        }
        {
            struct NameTagData* nt = GetPersistentNameData(p->x4);
            for (j = 0; j < 4; j++) {
                q = &arg0->player_standings[j];
                if (i != j && q->slot_type != 3) {
                    u8 ock = q->x4;
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
                u32 sum =
                    nt->play_time_by_fighter[gm_CKindToSelKind(p->ckind)] +
                    arg0->frame_count / 60;
                play_time = (sum > (u32) -1)
                                ? -1
                                : nt->play_time_by_fighter[gm_CKindToSelKind(
                                      p->ckind)] +
                                      arg0->frame_count / 60;
                nt->play_time_by_fighter[gm_CKindToSelKind(p->ckind)] =
                    play_time;
            }
            fn_80161C90(arg0, i, &nt->sd_count);
        }
    }
}

s32 gm_801623A4(MatchEnd* arg0)
{
    fn_80162068(arg0);
    fn_80162170(arg0);
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
    u32 total;
    u32 session_total;
    u32 capped_total;
    u32* high_score_ptr;
    u32* session_high_score_ptr;
    u32* current_score_ptr;
    u32* session_high_score_ptr2;
    s32 current_score = *gmMainLib_8015CCF0();
    u32* high_score_ptr2 = gmMainLib_8015CCFC();

    session_high_score_ptr = &gmMainLib_8015EDBC()->x14;

    total = ((*high_score_ptr2 + arg0) > (u32) -1) ? (u32) -1
                                                   : *high_score_ptr2 + arg0;
    *high_score_ptr2 = total;

    session_total = ((*session_high_score_ptr + arg0) > (u32) -1)
                        ? (u32) -1
                        : *session_high_score_ptr + arg0;
    *session_high_score_ptr = session_total;

    arg0 = current_score + arg0;
    if ((u32) arg0 > 0x270FU) {
        arg0 = 0x270FU;
    }
    capped_total = arg0;

    current_score_ptr = gmMainLib_8015CCF0();
    high_score_ptr = gmMainLib_8015CCFC();
    session_high_score_ptr2 = &gmMainLib_8015EDBC()->x14;

    if ((u32) arg0 > (*high_score_ptr)) {
        *high_score_ptr = arg0;
    }
    if ((u32) arg0 > (*session_high_score_ptr2)) {
        *session_high_score_ptr2 = arg0;
    }
    if ((u32) arg0 > 0x270FU) {
        capped_total = 0x270FU;
    }
    *current_score_ptr = capped_total;
    return arg0;
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
    ptr = (u16*) gmMainLib_8015CFB4(gm_CKindToSelKind(arg0));
    val = *ptr + 1;
    if (val > 0xFFFF) {
        val = 0xFFFF;
    }
    *ptr = val;

    // Second counter
    ptr = &gmMainLib_8015EDBC()->x18[gm_CKindToSelKind(arg0)];
    val = *ptr + 1;
    if (val > 0xFFFF) {
        val = 0xFFFF;
    }
    *ptr = val;
}

void gm_SetupHumanResultsScreen(u8 arg0, u8 arg1)
{
    u32* counter = NULL;

    if ((u8) (arg1 - 7) <= 1) {
        u32* p = gmMainLib_GetMatchResetCounter();
        *p = (*p + 1 > U32_MAX) ? U32_MAX : *p + 1;
        return;
    }
    if (gm_GetCurrentGameMode() == GM_STAMINA_VS) {
        counter = gmMainLib_GetStaminaMatchTotal();
    } else {
        switch ((MatchKind) arg0) {
        case MatchKind_Time:
            counter = gmMainLib_GetTimeMatchTotal();
            break;
        case MatchKind_Stock:
            counter = gmMainLib_GetStockMatchTotal();
            break;
        case MatchKind_Coin:
            counter = gmMainLib_GetCoinMatchTotal();
            {
                struct gmm_retval_EDBC* q = gmMainLib_8015EDBC();
                q->x4 = (q->x4 + 1 > U32_MAX) ? U32_MAX : q->x4 + 1;
            }
            break;
        case MatchKind_Bonus:
            counter = gmMainLib_GetBonusMatchTotal();
            break;
        }
    }
    *counter = (*counter + 1 > U32_MAX) ? U32_MAX : *counter + 1;
    {
        struct gmm_retval_ED98* a = gmMainLib_8015ED98();
        a->x0 = (a->x0 + 1 > U32_MAX) ? U32_MAX : a->x0 + 1;
    }
    {
        struct gmm_retval_EDB0* b = gmMainLib_8015EDB0();
        b->x0 = ((u32) b->x0 + 1 > U32_MAX) ? U32_MAX : (u32) b->x0 + 1;
    }
    {
        struct gmm_retval_EDBC* c = gmMainLib_8015EDBC();
        c->x0 = ((u32) c->x0 + 1 > U32_MAX) ? U32_MAX : (u32) c->x0 + 1;
    }
}

u32 gm_GetVsPlayMatchTotal(void)
{
    u32 total =
        *gmMainLib_GetTimeMatchTotal() + *gmMainLib_GetStockMatchTotal() +
        *gmMainLib_GetCoinMatchTotal() + *gmMainLib_GetBonusMatchTotal() +
        *gmMainLib_GetStaminaMatchTotal();
    return total;
}

u32 gm_80162800(MatchEnd* end)
{
    u32 count;
    u32* temp_r3;
    u32 sum;
    ssize_t i;

    temp_r3 = gmMainLib_GetVsPlayContestants();
    count = 0;
    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        if (end->player_standings[i].slot_type == Gm_PKind_Human) {
            count++;
        }
    }
    sum = *temp_r3 + count;
    *temp_r3 = (sum > -1) ? -1 : sum;
    return count;
}

void gm_SetupResultsScreenPlayTime(u32 arg0, u32 arg1)
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

s32 gm_80162968(u32 seconds)
{
    u32* ptr = gmMainLib_GetSingleplayerTime();

    *ptr = ((*ptr + seconds) > -1) ? -1 : (*ptr + seconds);
}

s32 gm_801629B4(s32 amount)
{
    u32* ptr = gmMainLib_8015CD80();

    *ptr = ((*ptr + amount) > -1) ? -1 : (*ptr + amount);
}

s32 gm_GetPlayTime(void)
{
    u32 a;
    u32 b;

    a = *(u32*) gmMainLib_GetVsPlayTime();
    b = *(u32*) gmMainLib_GetSingleplayerTime();
    return a + b > -1 ? -1 : a + b;
}

s32 gm_80162A4C(s32 amount)
{
    u32* ptr;

    ptr = gmMainLib_GetTotalDamage();
    *ptr = ((*ptr + amount) > -1) ? -1 : (*ptr + amount);
}

struct gmm_x1868_1A8_t* gm_80162A98(s32 arg0)
{
    struct gmm_x1868_1A8_t* ko_stats;
    u32 capped_total;
    s32* ko_total = gmMainLib_GetKOTotal();

    *ko_total = (*ko_total + arg0 > -1U) ? -1U : *ko_total + arg0;

    capped_total = (arg0 + gmMainLib_8015EDBC()->xC > -1U)
                       ? -1U
                       : arg0 + gmMainLib_8015EDBC()->xC;

    gmMainLib_8015EDBC()->xC = capped_total;

    capped_total = (arg0 + gmMainLib_8015EDC8()->x0 > -1U)
                       ? -1U
                       : arg0 + gmMainLib_8015EDC8()->x0;

    ko_stats = gmMainLib_8015EDC8();
    ko_stats->x0 = capped_total;
    return ko_stats;
}

void gm_RecordSelfDestructs(s32 amount)
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
    s32 val;
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

    temp_r3 = (int*) gmMainLib_8015D0C0(gm_CKindToSelKind((u8) ckind));
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
        if (min > (*gmMainLib_8015D194((u8) i))) {
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

    temp_r3 = gmMainLib_8015D1E8(gm_CKindToSelKind(ckind));
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
        if (min > (*gmMainLib_8015D2BC((u8) i))) {
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

    temp_r3 = gmMainLib_8015D310(gm_CKindToSelKind(ckind));
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
        if (min > (*gmMainLib_8015D3E4((u8) i))) {
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

    index = gm_CKindToSelKind(c_kind);
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
    u32 total_frames = 0;
    s32 frames;
    s32 i;

    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D710(i) != 0) {
            total_frames += *gmMainLib_8015D6F8((u8) i);
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

u8 gm_SelKindToCKind(u8 selkind)
{
    return selkind_to_ckind_map[selkind];
}

u8 gm_CKindToSelKind(u8 ckind)
{
    return ckind_to_selkind_map[ckind];
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
        if ((1 << (u16) i) & gmMainLib_8015CC58()->stage_mask) {
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
    return ((1 << (u16) arg0) & gmMainLib_8015CC58()->stage_mask) ? true
                                                                  : false;
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

void gm_80164504(u16 stkind)
{
    u16* stage_unlock_mask;
    s32 i;
    u8 grkind;
    u8 unlock_idx;
    u8 notify_val;

    stage_unlock_mask = gmMainLib_8015EDA4();
    grkind = Stage_8022519C(stkind);

    for (i = 0; i < NUM_UNLOCKABLE_STAGES; i++) {
        if ((s32) grkind == (s32) lbl_803B790C[i][1]) {
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
bool gm_IsCKindUnlocked(u8 ckind)
{
    u16* unlocked_chars_bitmask = gmMainLib_GetUnlockedCharactersBitmaskPtr();
    u8 selkind = ckind_to_selkind_map[ckind];
    u8 unlock_bit = gm_SelKindToUnlockIndex(selkind);

    if (unlock_bit == NUM_UNLOCKABLE_CHARACTERS ||
        (*unlocked_chars_bitmask & (1LL << unlock_bit)))
    {
        return true;
    }
    return false;
}

void gm_UnlockCKind(CharacterKind ckind)
{
    u16* char_unlock_mask;
    u8 selkind;
    int i;
    u8 unlock_idx;
    u8 notify_val;

    char_unlock_mask = gmMainLib_GetUnlockedCharactersBitmaskPtr();
    selkind = ckind_to_selkind_map[(u8) ckind];

    unlock_idx = gm_SelKindToUnlockIndex(selkind);

    if (unlock_idx != NUM_UNLOCKABLE_CHARACTERS) {
        for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
            if ((s32) unlock_idx == (s32) lbl_803B78C8[i].idx) {
                notify_val = lbl_803B78C8[i].notification_id;
                goto found_notify;
            }
        }
        notify_val = 0x42;

    found_notify:
        gmMainLib_8015D818(notify_val);
        *char_unlock_mask |= (1LL << (s32) unlock_idx);
    }
}

/// Lock character?
void gm_80164A0C(u8 ckind)
{
    u16* unlockable_character_bitfield =
        gmMainLib_GetUnlockedCharactersBitmaskPtr();
    s32 selkind = ckind_to_selkind_map[ckind];
    u8 idx = gm_SelKindToUnlockIndex(selkind);
    if (idx != NUM_UNLOCKABLE_CHARACTERS) {
        *unlockable_character_bitfield &= ~(1ULL << idx);
    }
}

/// Are all unlockable characters unlocked?
bool gm_80164ABC(void)
{
    u16* unlockable_character_bitfield =
        gmMainLib_GetUnlockedCharactersBitmaskPtr();
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

static inline bool is_character_unlocked(u8 n, const u16* mask)
{
    if (n == 0xB || (*mask & 1LL << n)) {
        return true;
    }
    return false;
}

bool fn_80164B48(void)
{
    u16* ptr;
    PAD_STACK(0xC);

    ptr = gmMainLib_GetUnlockedCharactersBitmaskPtr();
    if (!is_character_unlocked(
            gm_SelKindToUnlockIndex(ckind_to_selkind_map[CKIND_DRMARIO]), ptr))
    {
        return false;
    }

    ptr = gmMainLib_GetUnlockedCharactersBitmaskPtr();
    if (!is_character_unlocked(
            gm_SelKindToUnlockIndex(ckind_to_selkind_map[CKIND_GANON]), ptr))
    {
        return false;
    }

    ptr = gmMainLib_GetUnlockedCharactersBitmaskPtr();
    if (!is_character_unlocked(
            gm_SelKindToUnlockIndex(ckind_to_selkind_map[CKIND_CLINK]), ptr))
    {
        return false;
    }

    ptr = gmMainLib_GetUnlockedCharactersBitmaskPtr();
    if (!is_character_unlocked(
            gm_SelKindToUnlockIndex(ckind_to_selkind_map[CKIND_FALCO]), ptr))
    {
        return false;
    }

    ptr = gmMainLib_GetUnlockedCharactersBitmaskPtr();
    if (!is_character_unlocked(
            gm_SelKindToUnlockIndex(ckind_to_selkind_map[CKIND_PICHU]), ptr))
    {
        return false;
    }

    ptr = gmMainLib_GetUnlockedCharactersBitmaskPtr();
    if (!is_character_unlocked(
            gm_SelKindToUnlockIndex(ckind_to_selkind_map[CKIND_EMBLEM]), ptr))
    {
        return false;
    }

    return true;
}

void gm_80164F18(void) //< Unlock all characters?
{
    u16* ptr;
    int i;

    ptr = gmMainLib_GetUnlockedCharactersBitmaskPtr();

    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        *ptr |= 1LL << i;
    }
}

void gm_8016505C(void)
{
    u16* temp_r3 = gmMainLib_GetUnlockedCharactersBitmaskPtr();
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
    Ground_EnableMatchCamera();
}

void gm_EnablePlayerPauseCamera(int playerSlot, int playerId)
{
    if (playerSlot == -1) {
        Camera_SetUpPauseCameraWithDefaultZoom(NUM_UNLOCKABLE_CHARACTERS, 5);
        return;
    }
    if (((Player_GetPlayerSlotType(playerSlot) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(playerSlot) == Gm_PKind_Cpu)) &&
        (Player_GetEntity(playerSlot) != NULL))
    {
        Camera_SetUpPauseCameraWithDefaultZoom(playerSlot, playerId);
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
    Camera_SetModeToFixed();
}

void fn_801652B0(s32 arg0, s32 arg1)
{
    Camera_8002F9E4(arg0, arg1);
}

void* fn_801652D8(void)
{
    s32 idx;
    HSD_VIInfo* vi = &HSD_VIData;
    PerfLabelLine* lines = &lbl_8046B378.line0;

    lines[0].unk_04 = 0;

    idx = 0;
    sprintf(lines[idx].text, "\\cffff00%2d", (int) vi->perf.frame_renew);

    lines[0].next = &lines[1];

    sprintf(lines[idx = 1].text, "\\ce0e0ff%5d", (int) gm_801A4BB8());

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

s32 fn_80165418(MatchEnd* match_end)
{
    s32 winner = 0;
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

s32 fn_801654A0(MatchEnd* match_end)
{
    s32 winner = 0;
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

s32 fn_80165548(MatchEnd* me, s32 arg1, s32 team)
{
    s32 i;
    s32 ret;
    s32 result;
    s32 j;

    ret = 0;
    if (me->is_teams == 1) {
        for (i = 0; i < 4; i++) {
            if (me->player_standings[i].slot_type != 3 &&
                (s32) me->player_standings[i].team == team)
            {
                result = i;
                for (j = 0; j < 4; j++) {
                    if (me->player_standings[j].slot_type != 3 &&
                        (s32) me->player_standings[j].team == team && i != j &&
                        me->player_standings[i].is_small_loser >
                            me->player_standings[j].is_small_loser)
                    {
                        result = -1;
                        break;
                    }
                }
                if (result >= 0) {
                    ret += result;
                    break;
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
                    (u32) arg0->player_standings[j].x20)
            {
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

static inline s32 fn_8016588C_clamp(s32 v)
{
    s32 lim = (1 << 24) - 1;
    s32 result = v;

    if (lim < 0) {
        lim = -lim;
    }
    if (v > lim) {
        result = lim;
    } else if (v < -lim) {
        result = -lim;
    }
    return result;
}

s32 fn_8016588C(lbl_8046B6A0_24C_t* arg0, s32 arg1)
{
    s32 v;

    PAD_STACK(0x18);

    if (gm_GetCurrentGameMode() == GM_STAMINA_VS) {
        if (arg0->x58[arg1].x28 != 0) {
            v = arg0->x58[arg1].x28 / 60 + 0xFF000001;
        } else {
            v = arg0->x58[arg1].x9;
        }
        return fn_8016588C_clamp(v);
    } else if (arg0->x5 == 2) {
        return fn_8016588C_clamp(((MatchPlayerData*) arg0->x58)[arg1].x1C);
    } else if (arg0->x5 == 1) {
        if ((s8) arg0->x58[arg1].x8 != 0) {
            v = (s8) arg0->x58[arg1].x8;
        } else {
            v = arg0->x58[arg1].x28 / 60 + 0xFF000001;
        }
        return fn_8016588C_clamp(v);
    } else if (arg0->x5 == 3) {
        pl_80039450(arg1);
        return fn_8016588C_clamp(fn_8016FFD4(arg0, 2, (u8) arg1));
    } else {
        u16 a = arg0->x58[arg1].xA;
        return fn_8016588C_clamp(arg0->x58[arg1].x20 -
                                 (arg0->x58[arg1].x24 - a) +
                                 a * (s8) arg0->xC);
    }
}

struct fn_80165AC0_loser_bits {
    u8 hi : 4;
    u8 lo : 4;
};

s32 fn_80165AC0(MatchEnd* arg0)
{
    s32 i;
    s32 j;
    s32 max_loser;
    s32 count;

    max_loser = 0;
    for (i = 0; i < 6; i++) {
        if (arg0->player_standings[i].slot_type != 3) {
            for (j = 0; j < 6; j++) {
                if (arg0->player_standings[j].slot_type != 3 && i != j &&
                    arg0->player_standings[i].score <
                        arg0->player_standings[j].score)
                {
                    arg0->player_standings[i].is_big_loser += 1;
                }
            }
            if (max_loser < arg0->player_standings[i].is_big_loser) {
                max_loser = arg0->player_standings[i].is_big_loser;
            }
        }
    }
    ((struct fn_80165AC0_loser_bits*) &arg0->loser)->hi = max_loser;
    count = 0;
    for (j = 0; j < 6; j++) {
        if (arg0->player_standings[j].slot_type != 3 &&
            arg0->player_standings[j].is_big_loser == 0)
        {
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
        if (arg0->player_standings[i].slot_type != 3) {
            arg0->player_standings[i].is_small_loser =
                arg0->player_standings[i].is_big_loser;
            for (j = 0; j < 6; j++) {
                if (arg0->player_standings[j].slot_type != 3 && i != j &&
                    arg0->player_standings[i].is_big_loser ==
                        arg0->player_standings[j].is_big_loser &&
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
        if (arg0->player_standings[i].slot_type != 3) {
            u8 team = arg0->player_standings[i].team;

            if (gm_GetCurrentGameMode() == GM_STAMINA_VS ||
                arg0->match_kind == 1)
            {
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
    s32 i;
    s32 max_loser;
    s32 count;
    s32 j;

    max_loser = 0;
    for (i = 0; i < 5; i++) {
        if (arg0->team_standings[i].active != 0) {
            for (j = 0; j < 5; j++) {
                if (i != j && arg0->team_standings[j].active != 0 &&
                    (s32) arg0->team_standings[i].score <
                        (s32) arg0->team_standings[j].score)
                {
                    arg0->team_standings[i].is_big_loser += 1;
                }
            }
            if (max_loser < (s32) arg0->team_standings[i].is_big_loser) {
                max_loser = arg0->team_standings[i].is_big_loser;
            }
        }
    }
    ((struct fn_80165AC0_loser_bits*) &arg0->loser)->lo = max_loser;
    count = 0;
    for (j = 0; j < 5; j++) {
        if (arg0->team_standings[j].active != 0 &&
            arg0->team_standings[j].is_big_loser == 0)
        {
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
        if (arg0->team_standings[i].active != 0) {
            arg0->team_standings[i].is_small_loser =
                arg0->team_standings[i].is_big_loser;
            for (j = 0; j < 5; j++) {
                if (arg0->team_standings[j].active != 0 && i != j &&
                    arg0->team_standings[i].is_big_loser ==
                        arg0->team_standings[j].is_big_loser &&
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
    s32 i;
    MatchEnd* arg0 = (MatchEnd*) arg0_raw;
    u64 stack_padding;
    f32 sp48_y;
    f32 sp48_x;
    s32 j;
    u32 cnt;
    f32 d, c, b, a;

    PAD_STACK(60);

    memzero(arg0->player_standings, sizeof(arg0->player_standings));
    memzero(arg0->team_standings, sizeof(arg0->team_standings));
    memzero(arg0->_x448, sizeof(arg0->_x448));
    arg0->frame_count = gm_8016AEDC();
    arg0->x7 = fn_8016B728();
    for (i = 0; i < 6; i++) {
        arg0->player_standings[i].slot_type = Player_GetPlayerSlotType(i);
        if (arg0->player_standings[i].slot_type != 3) {
            arg0->player_standings[i].ckind = Player_GetPlayerCharacter(i);
            arg0->player_standings[i].ftkind = Player_80036394(i);
            arg0->player_standings[i].stocks = Player_GetStocks(i);
            arg0->player_standings[i].x3 = Player_GetCostumeId(i);
            arg0->player_standings[i].x4 = Player_GetNametagSlotID(i);
            arg0->player_standings[i].x1C = Player_GetCoins(i);
            arg0->player_standings[i].x28 = Player_GetMatchFrameCount(i);
            if (arg0->player_standings[i].x28 == -1U) {
                arg0->player_standings[i].x28 = gm_8016AEDC();
            }
            arg0->player_standings[i].self_destructs =
                Player_GetSuicideCount(i);
            arg0->player_standings[i].x24 = Player_GetFalls(i);
            arg0->player_standings[i].team = Player_GetTeam(i);
            arg0->player_standings[i].percent = Player_GetDamage(i);
            arg0->player_standings[i].x3_6 = Player_800353BC(i);
            arg0->player_standings[i].x3_7 = Player_GetMoreFlagsBit2(i);
            arg0->player_standings[i].x9 = (s8) Player_GetRemainingHP(i);
            cnt = Player_GetJoystickCountByIndex(i, 0);
            sp48_y = (a = 0.031f) * ((f32) cnt * fn_8016B5B0());
            fn_80166A8C((Vec3*) &sp48_y, (Vec3*) &sp48_x);
            arg0->player_standings[i].xE = *(u16*) &sp48_x;
            arg0->player_standings[i].x34 =
                (s8) ((b = 100.0f) * pl_80040948(i));
            arg0->player_standings[i].x38 = pl_80040900(i);
            arg0->player_standings[i].x3C = pl_80040924(i);
            arg0->player_standings[i].x40 = pl_80040B3C(i);
            arg0->player_standings[i].x44 = pl_80040B64(i);
            arg0->player_standings[i].x48 = pl_80040BD8(i);
            arg0->player_standings[i].x4C = pl_80040BFC(i);
            arg0->player_standings[i].x50 = (u32) pl_80040C24(i) * 0xA;
            arg0->player_standings[i].x54 = (u32) pl_80040C48(i) * 0xA;
            arg0->player_standings[i].x58 = (u32) pl_80040C6C(i) * 0xA;
            arg0->player_standings[i].x5C = (u32) pl_80040C90(i) * 0xA;
            arg0->player_standings[i].x60 = Player_GetTotalCoins(i);
            arg0->player_standings[i].x64 = Player_GetUnk98(i);
            arg0->player_standings[i].x68 = Player_GetUnk9C(i);
            arg0->player_standings[i].x6C = (u32) pl_80040CB4(i) / 60U;
            arg0->player_standings[i].x70 = (u32) pl_80040CD8(i) / 60U;
            arg0->player_standings[i].x74 = pl_80040A04(i);
            arg0->player_standings[i].x78 = pl_80040A30(i);
            arg0->player_standings[i].x7C = pl_80040A54(i);
            arg0->player_standings[i].x80 = pl_80040B18(i);
            arg0->player_standings[i].x84 = pl_80040A78(i);
            arg0->player_standings[i].x88 = pl_80040A9C(i);
            arg0->player_standings[i].x8C = pl_80040AF0(i);
            arg0->player_standings[i].x90 = pl_8003E39C(i);
            arg0->player_standings[i].x94 =
                (u32) ((void) (c = 60.0f),
                       (c * ((d = 10.0f) * pl_80040D44(i))));
            arg0->player_standings[i].x98 = (u32) (c * (d * pl_80040D68(i)));
            arg0->player_standings[i].x9C = (u32) pl_80040CFC(i) / 60U;
            arg0->player_standings[i].xA0 = (u32) pl_80040D20(i) / 60U;
            arg0->player_standings[i].xA4 = pl_80040DB8(i);
            for (j = 0; j < 6; j++) {
                if (arg0->player_standings[j].slot_type != 3) {
                    arg0->player_standings[i].kills[j] =
                        Player_GetKOsByPlayerIndex(i, j);
                }
            }
        }
    }
    if (arg0->is_teams == 1) {
        for (i = 0; i < 6; i++) {
            if (arg0->player_standings[i].slot_type != 3) {
                s32 team_i = arg0->player_standings[i].team;
                for (j = 0; j < 6; j++) {
                    if (arg0->player_standings[j].slot_type != 3) {
                        if (arg0->player_standings[j].team != team_i) {
                            if (i != j) {
                                arg0->player_standings[i].x20 +=
                                    arg0->player_standings[i].kills[j];
                            }
                        } else {
                            arg0->player_standings[i].self_destructs +=
                                arg0->player_standings[i].kills[j];
                            arg0->player_standings[i].x24 +=
                                arg0->player_standings[i].kills[j];
                        }
                    }
                }
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            if (arg0->player_standings[i].slot_type != 3) {
                for (j = 0; j < 6; j++) {
                    if (arg0->player_standings[j].slot_type != 3) {
                        if (i != j) {
                            arg0->player_standings[i].x20 +=
                                arg0->player_standings[i].kills[j];
                        } else {
                            arg0->player_standings[i].self_destructs +=
                                arg0->player_standings[i].kills[j];
                            arg0->player_standings[i].x24 +=
                                arg0->player_standings[i].kills[j];
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 6; i++) {
        if (arg0->player_standings[i].slot_type != 3) {
            arg0->player_standings[i].score = fn_8016588C(arg0_raw, i);
            arg0->player_standings[i].x30 = fn_801656A8(arg0, i);
        }
    }
    fn_80165AC0(arg0);
    fn_80165D60(arg0);
    fn_80165E7C(arg0);
    fn_80165FA4(arg0);
    fn_801661E0(arg0);
}

float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
#ifdef MWERKS_GEKKO
    register float x = src->x;
    asm { psq_st x, Vec3.x(dst), 1, qr3 }
    return x;
#endif
}

// Probably some code to setup or end a 4 player match?
s32 gm_80166A98(MatchEnd* arg0, u8 arg1, s8 arg2, u8 arg3, s8 arg4, u8 arg5,
                s8 arg6, u8 arg7, u8 arg_sp8, u8 arg_spC)
{
    s32 score0;
    s32 score1;
    s32 score2;
    s32 score3;
    u32 i;

    memzero(arg0, sizeof(*arg0));

    arg0->result = OUTCOME_TIMEOUT;
    arg0->match_kind = 0;
    arg0->is_teams = 0;

    score0 = 0xA - arg3;
    arg0->player_standings[0].ckind = arg2;
    score1 = 0xA - arg5;
    arg0->player_standings[1].ckind = arg4;
    score2 = 0xA - arg7;
    arg0->player_standings[2].ckind = arg6;
    score3 = 0xA - arg_spC;
    arg0->player_standings[3].ckind = arg_sp8;

    // Apply player color to all 4 players?
    for (i = 0; i < 4; i++) {
        arg0->player_standings[i].x3 = arg1;
    }

    arg0->player_standings[0].score = score0;
    arg0->player_standings[1].score = score1;
    arg0->player_standings[2].score = score2;
    arg0->player_standings[3].score = score3;
    arg0->player_standings[0].x30 = score0;
    arg0->player_standings[1].x30 = score1;
    arg0->player_standings[2].x30 = score2;
    arg0->player_standings[3].x30 = score3;

    for (i = 0; i < 4; i++) {
        arg0->player_standings[i].x30 += 6 - i;
        if (arg0->player_standings[i].ckind == CHKIND_NONE) {
            arg0->player_standings[i].slot_type = 3;
        } else if (HSD_PadMasterStatus[(u8) i].err == 0) {
            arg0->player_standings[i].slot_type = 0;
        } else {
            arg0->player_standings[i].slot_type = 1;
        }

        if (arg0->player_standings[i].ckind == CKIND_SEAK) {
            arg0->player_standings[i].ckind = CKIND_ZELDA;
            arg0->player_standings[i].ftkind = FTKIND_SEAK;
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

u8 fn_80166CBC(MatchEnd* arg0, ssize_t index)
{
    return arg0->player_standings[index].is_small_loser;
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
    if (result == OUTCOME_NO_CONTEST || result == OUTCOME_RETRY) {
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
                arg0->player_standings[i].ftkind =
                    arg1->player_standings[i].ftkind;
                arg0->player_standings[i].xE += arg1->player_standings[i].xE;
                if (arg0->player_standings[i].is_big_loser == 0) {
                    if (arg1->player_standings[i].slot_type == 3) {
                        arg0->player_standings[i].is_big_loser += player_count;
                        arg0->player_standings[i].is_small_loser +=
                            player_count;
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

bool gm_MatchHasMultipleWinners(MatchEnd* end)
{
    s32 winners;

    if (end->result != OUTCOME_NO_CONTEST) {
        if (end->is_teams == 1) {
            winners = end->n_team_winners;
        } else {
            winners = fn_80167194(end);
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

struct fn_8016719C_xC_bits {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
};

void fn_8016719C(s32 slot, s32 subchar)
{
    Vec3 respawn_pos;
    Vec3 offset;
    lbl_8046B6A0_t* match_info;
    s32 var_r30;
    StKind stkind;
    struct fn_8016719C_xC_bits* temp_r4;

    match_info = gm_16AE_GetUnkData_1();
    stkind = gm_8016B004();
    if (Stage_80224DC8(stkind) != 0) {
        var_r30 = Ground_801C5774();
        Stage_80224E38(&respawn_pos, var_r30);
        offset.z = 0.0f;
        offset.y = 0.0f;
        offset.x = 0.0f;
        if ((stkind != 0x4C) && (subchar == 0)) {
            Ground_801C38BC(respawn_pos.x, respawn_pos.y);
            Camera_8002F3AC();
        }
    } else {
        var_r30 = fn_80167638(slot, &respawn_pos, &offset);
    }
    respawn_pos.x += offset.x;
    Player_SetSpawnPlatformPos(slot, &respawn_pos);

    if (!stage_info.unk8C.b5) {
        Player_80032FA4(slot, var_r30);
        Player_SetSomePos(slot, &offset);
    }

    respawn_pos.y = Stage_GetCamBoundsTopOffset();
    Player_80032768(slot, &respawn_pos);
    Player_SetFacingDirection(slot, respawn_pos.x >= 0.0f ? -1.0f : 1.0f);
    Player_SetHPByIndex(slot, subchar, match_info->FighterMatchInfo[slot].x6);
    Player_80032070(slot, subchar);
    if (subchar != 1) {
        ifStatus_802F6508(slot);
        temp_r4 =
            (struct fn_8016719C_xC_bits*) &match_info->FighterMatchInfo[slot]
                .xC;
        if (temp_r4->b0) {
            temp_r4->b0 = true;
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
    switch ((s32) gm_GetCurrentGameMode()) {
    case GM_STAMINA_VS:
        gm_801B97C4(arg0, arg1);
        break;
    }
}

void gm_801674C4(s8 arg0, u8 arg1, s8 arg2, s8 arg3, GmRouteCallback arg4)
{
    s8 temp_r31;
    struct lbl_8046B488_t* new_var;
    struct lbl_8046B488_t* new_var2;
    s64 new_var3;
    struct lbl_8046B488_t* temp_ptr;
    temp_ptr = gm_1601_GetUnkData();
    temp_ptr->x0 = arg0;
    temp_ptr->x1 = 0x21;
    new_var3 = arg1;
    temp_ptr->x2 = 0x21;
    temp_ptr->x7 = new_var3;
    temp_ptr->x8 = new_var3;
    temp_ptr->x9 = arg2;
    new_var2 = temp_ptr;
    new_var2->xA = arg3 & 0xFFFF;
    PAD_STACK(10);
    new_var = new_var2;
    new_var->unk_10_b2 = 1;
    fn_80169574(new_var->x7, new_var->x20);
    fn_80169900(new_var->xD, new_var, new_var2->xA2, new_var->x20);
    temp_r31 = Player_GetCostumeId(0);
    fn_8016989C((u8*) new_var, (s8) Player_GetPlayerCharacter(0), temp_r31,
                (u8*) new_var->xA2, new_var2->x20);
    fn_8016A09C();
    fn_80169434(arg4);
}

void fn_8016758C(void)
{
    lbl_8046B6A0_t* mi = gm_16AE_GetUnkData_1();
    int i;

    for (i = 0; i < ARRAY_SIZE(mi->FighterMatchInfo); i++) {
        if (mi->FighterMatchInfo[i].x8 != 0) {
            mi->FighterMatchInfo[i].x8--;
        }
    }
}

static inline int get_idx(void)
{
    lbl_8046B6A0_t* info = gm_16AE_GetUnkData_1();
    int i;
    for (i = 0; i < ARRAY_SIZE(info->FighterMatchInfo); i++) {
        if (info->FighterMatchInfo[i].x8 == 0) {
            return i;
        }
    }
    return 0;
}

s32 fn_80167638(s32 arg0, Vec3* arg1, Vec3* arg2)
{
    int idx = get_idx();
    s8 chr = Player_GetPlayerCharacter(arg0);
    s32 tmp;
    PAD_STACK(8);

    if (stage_info.unk8C.b4) {
        Stage_80224E38(arg1, tmp = arg0);
        arg2->z = 0.0f;
        arg2->y = 0.0f;
        arg2->x = 0.0f;
    } else {
        tmp = 0 & 0xFFFF;
        Stage_80224E38(arg1, tmp);
        {
            float sp[] = {
                0, 1, -1, 2, 0, 0,
            };
            arg2->x = 16.0f * sp[idx];
            arg2->z = 0.0f;
            arg2->y = 0.0f;
        }
        {
            lbl_8046B6A0_t* info = gm_16AE_GetUnkData_1();
            PAD_STACK(8);
            info->FighterMatchInfo[idx].x8 = 0x90;
            info->FighterMatchInfo[idx].x9 = chr;
        }
    }
    return tmp;
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

bool gm_RumbleEnabledForPlayer(int port, int nametag)
{
    bool result = false;
    if (nametag == GM_NAMETAG_NONE) {
        if (GetRumbleSettingOfPort(port)) {
            result = true;
        }
    } else if (GetPersistentNameData(nametag)->rumble_enabled) {
        result = true;
    }
    return result;
}

void gm_80167858(int port, int nametag, int arg2, int arg3)
{
    if (gm_RumbleEnabledForPlayer(port, nametag)) {
        lb_80014574(port, 3, arg2, arg3);
    }
}

void gm_801678F8(int port, int arg1, int arg2)
{
    gm_80167858(port, 120, arg1, arg2);
}

void gm_SetupPlayerDefaults(struct PlayerInitData* player)
{
    memzero(player, sizeof(*player));
    player->ckind = CHKIND_NONE;
    player->slot_type = Gm_PKind_NA;
    player->stocks = 0;
    player->color = 0;
    player->slot = 0;
    player->x5 = -1;
    player->spawn_dir = 0;
    player->xB = 0;
    player->sub_color = 0;
    player->handicap = 9;
    player->team = 0;
    player->rumble_enabled = false;
    player->nametag = GM_NAMETAG_NONE;
    player->xC_b1 = true;
    player->xE = 4;
    player->cpu_level = 0;
    player->x12 = 0;
    player->hp = 0;
    player->x18 = 1.0F;
    player->x1C = 1.0F;
    player->x20 = 1.0F;
}

void gm_80167A14(struct PlayerInitData* arg0)
{
    int i;
    for (i = 0; i < 6; i++) {
        gm_SetupPlayerDefaults(&arg0[i]);
    }
}

void gm_SetupRulesDefaults(struct StartMeleeRules* rules)
{
    memzero(rules, sizeof(*rules));
    rules->x0_3 = 4;

    rules->xC = 0;
    rules->xB = 2;

    rules->x20 = -1;
    rules->x28 = 0;

    rules->x3_1 = true;

    rules->x3_5 = true;
    rules->x3_4 = true;
    rules->x4_0 = true;

    rules->timer_shows_hours = false;
    rules->x2_5 = true;
    rules->x2_6 = true;

    rules->x2C = 1.0f;
    rules->x30 = 1.0f;
    rules->x34 = 1.0f;

    rules->x4_6 = true;
    rules->x4_7 = true;
    rules->xD = 110;
    rules->xA = 0;
}

void gm_80167B50(VsModeData* arg0)
{
    gm_SetupRulesDefaults(&arg0->start.rules);
    gm_80167A14(arg0->start.players);
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
    PAD_STACK(72);

    rules = gmMainLib_GetGameRules();
    prefs = gmMainLib_8015CC58();
    vs_data->start.rules.x0_6 = 0;

    switch (rules->mode) {
    case 0:
        vs_data->start.rules.match_kind = 0;
        if (rules->time_limit != 0) {
            vs_data->start.rules.x0_6 = 1;
            vs_data->start.rules.time_limit = rules->time_limit * 60;
        }
        break;
    case 1:
        vs_data->start.rules.match_kind = 1;
        if (rules->stock_time_limit != 0) {
            vs_data->start.rules.x0_6 = 1;
            vs_data->start.rules.time_limit = rules->stock_time_limit * 60;
            break;
        }
        break;
    case 2:
        vs_data->start.rules.match_kind = 2;
        if (rules->time_limit != 0) {
            vs_data->start.rules.x0_6 = 1;
            vs_data->start.rules.time_limit = rules->time_limit * 60;
        }
        break;
    case 3:
        vs_data->start.rules.match_kind = 3;
        if (rules->time_limit != 0) {
            vs_data->start.rules.x0_6 = 1;
            vs_data->start.rules.time_limit = rules->time_limit * 60;
        }
        break;
    }

    i = 0;
    for (i = 0; i < 6; i++) {
        vs_data->start.players[i].stocks = (s8) rules->stock_count;
        switch (rules->handicap) {
        case 0:
            vs_data->start.players[i].x18 = 1.0f;
            vs_data->start.players[i].x1C = 1.0f;
            break;
        case 1:
            handicap =
                gmMainLib_8015CE44(i, (s32) vs_data->start.players[i].nametag);
            if (handicap != NULL) {
                vs_data->start.players[i].handicap = *handicap;
                vs_data->start.players[i].x18 =
                    lbl_803B7930[(u8) *handicap - 1].x;
                vs_data->start.players[i].x1C =
                    lbl_803B7930[(u8) *handicap - 1].y;
            } else {
                vs_data->start.players[i].handicap = 5;
                vs_data->start.players[i].x18 = lbl_803B7930[4].x;
                vs_data->start.players[i].x1C = lbl_803B7930[4].y;
            }
            break;
        case 2:
            vs_data->start.players[i].x18 =
                lbl_803B7930[(u8) vs_data->start.players[i].handicap - 1].x;
            vs_data->start.players[i].x1C =
                lbl_803B7930[(u8) vs_data->start.players[i].handicap - 1].y;
            break;
        }
    }

    vs_data->start.rules.friendly_fire = (rules->friendly_fire & 1);
    vs_data->start.rules.x30 = 0.1f * rules->damage_ratio;
    vs_data->start.rules.xB = (s8) prefs->item_freq;
    prefs = gmMainLib_8015CC58();
    i = 0;
    do {
        u8 item = lbl_803B7844[(u8) i];
        if ((s32) item != 0x23) {
            if (prefs->item_mask & (1LL << i)) {
                vs_data->start.rules.x20 |= 1LL << item;
            } else {
                vs_data->start.rules.x20 &= ~(1LL << item);
            }
        }
        i++;
    } while (i < 0x20);

    switch (gmMainLib_8015ED30()) {
    case 1:
        vs_data->start.rules.xC = 0;
        break;
    case 0:
        vs_data->start.rules.xC = -1;
        break;
    case 2:
        vs_data->start.rules.xC = -2;
        break;
    }

    if (rules->pause != 0) {
        vs_data->start.rules.disable_pausing = 0;
    } else {
        vs_data->start.rules.disable_pausing = 1;
    }
    if ((rules->score_display != 0) && (rules->mode == 0)) {
        vs_data->start.rules.x3_0 = 1;
        return;
    }
    vs_data->start.rules.x3_0 = 0;
}

static inline int pad_inline(SSSData* arg0, int base)
{
    int i;
    for (i = 0; i < 5; i++) {
        int j = (base + i) % 4;
        if (HSD_PadMasterStatus[(u8) j].err == 0 &&
            arg0->vs.start.players[j].slot_type == Gm_PKind_Human)
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

void gm_80167FC4(SSSData* arg0)
{
    int temp_r30;
    GameRules* temp_r3;
    int i;

    u16* temp_r25;
    s32 temp_r28;
    u8 temp_r3_2;

    PAD_STACK(8);

    temp_r3 = gmMainLib_GetGameRules();
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
            temp_r28 = arg0->vs.ordered_stage_index + i;
            temp_r28 = (temp_r28 + 1) % 29;
            temp_r30 = mnStageSel_8025BC08(temp_r28);
            temp_r25 = gmMainLib_8015EDA4();

            if (is_character_unlocked(get_flag_unk(temp_r30), temp_r25)) {
                arg0->force_stage_id = temp_r30;
                arg0->vs.ordered_stage_index = temp_r28;
                return;
            }
        }
        break;
    case 3:
        arg0->vs.loser = pad_inline(arg0, arg0->vs.loser + 1);
        if (arg0->vs.loser < 0) {
            arg0->vs.loser = 0;
            arg0->unk_stage = 0;
        } else {
            arg0->unk_stage = arg0->vs.loser + 1;
        }
        break;
    case 4:
        if (arg0->vs.winner == -1) {
            arg0->unk_stage = pad_inline(arg0, HSD_Randi(4)) + 1;
        } else {
            arg0->unk_stage = pad_inline(arg0, arg0->vs.winner) + 1;
        }
        break;
    }
}

s8 gm_801685D4(u8 arg0, u8 arg1)
{
    s8* temp_r3;

    if (gmMainLib_GetGameRules()->handicap == 1) {
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
    if (gmMainLib_GetGameRules()->handicap == 1) {
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
            if (arg0->player_standings[i].slot_type != 3) {
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
    memzero(buf, sizeof(buf));
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
            (s32) arg0->player_standings[j].is_big_loser == best)
        {
            buf[count++] = j;
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
    for (i = 0; i < GM_MAX_PLAYERS; i++) {
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
void gm_LoadAnnouncer(void)
{
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void fn_80169000(MatchEnd* arg0, u8* arg1)
{
    u8 operand_pad[4];
    u8 handicaps[4];
    u8 positions[4];
    MatchEnd* p = arg0;
    u8* hb = arg1;
    s32 count;
    s32 i;
    UNUSED u8 pad[8];

    count = 0;
    for (i = 0; i < 4; i++) {
        if (p->player_standings[i].slot_type != 3) {
            count += 1;
            positions[p->player_standings[i].is_small_loser] = i;
        }
        /// @todo Matching tactic: indexing both arrays (rather than
        /// walking `*hp++ = *sp++` through named locals) makes both copy
        /// pointers compiler-created webs, which outrank the standings
        /// induction variable and let the source pointer take r3.
        handicaps[i] = arg1[i];
    }

    /// @todo Matching tactic: this dead read manufactures one extra
    /// interference edge on the long-lived `&handicaps[positions[0]]` web.
    /// That pushes its degree at simplify-stack visit time from 28 to 29
    /// (== K), so it is deferred a pass, coloured earlier, and takes r3
    /// instead of r6 -- which is the whole tail register assignment.
    (void) handicaps[positions[0]];
    if (handicaps[positions[0]] >= 2 && handicaps[positions[count - 1]] <= 8) {
        handicaps[positions[0]] -= 1;
        handicaps[positions[count - 1]] += 1;
    } else if (handicaps[positions[0]] == 1 &&
               handicaps[positions[count - 1]] <= 7)
    {
        handicaps[positions[count - 1]] = handicaps[positions[count - 1]] + 2;
    } else if (handicaps[positions[0]] >= 3 &&
               handicaps[positions[count - 1]] == 9)
    {
        handicaps[positions[0]] -= 2;
    } else if (count >= 3) {
        if (handicaps[positions[0]] == 1 &&
            handicaps[positions[count - 1]] == 8)
        {
            handicaps[positions[count - 1]] += 1;
            if (handicaps[positions[1]] >= 2) {
                handicaps[positions[1]] -= 1;
            }
        } else if (handicaps[positions[0]] == 2 &&
                   handicaps[positions[count - 1]] == 9)
        {
            handicaps[positions[0]] -= 1;
            if (handicaps[positions[1]] >= 2) {
                handicaps[positions[1]] -= 1;
            }
        }
    }
    hb[0] = handicaps[0];
    hb[1] = handicaps[1];
    hb[2] = handicaps[2];
    hb[3] = handicaps[3];
}

u8 gm_80169238(u8 ckind)
{
    /// @todo Matching tactic: pad the pre-inline statement count so MWCC
    /// keeps direct calls to this accessor instead of auto-inlining them.
    if (0) {
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
        HSD_Randi(0);
    }
    if (ckind >= ARRAY_SIZE(lbl_803D51A0)) {
        return 0;
    }
    return lbl_803D51A0[ckind].ncolors;
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
