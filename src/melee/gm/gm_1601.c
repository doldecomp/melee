#include "gm_1601.h"

#include "gm_1601.static.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "runtime.h"
#include "stddef.h"

#include "baselib/gobjplink.h"
#include "baselib/particle.h"
#include "cm/camera.h"
#include "db/db.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "if/ifstatus.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lb_0192.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbtime.h"
#include "mn/mnstagesel.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "ty/toy.h"

#include <m2c_macros.h>
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

void gm_801602C0(s8 arg0)
{
    int a = gm_80160244(arg0);
    int b = gm_801601C4(arg0);

    PAD_STACK(8);

    lbAudioAx_80024614(b);
    lbAudioAx_800245F4(a);
}

#pragma push
#pragma dont_inline on
void gm_801603B0(void)
{
    int temp_r31;
    s8 temp_r3;

    temp_r3 = gmMainLib_8015ED74();
    temp_r31 = gm_80160244(temp_r3);

    lbAudioAx_80024614(gm_801601C4(temp_r3));
    lbAudioAx_800245F4(temp_r31);
}
#pragma pop

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

bool gm_80160474(CharacterKind ckind, MajorSceneKind scene)
{
    switch (scene) {
    case MJ_CLASSIC_GOVER:
    case MJ_CLASSIC:
        return lbl_803B7978[ckind];
    case MJ_ADVENTURE_GOVER:
    case MJ_ADVENTURE:
        return lbl_803B79BC[ckind];
    default:
        return lbl_803B7A00[ckind];
    }
}

char* gm_801604DC(CharacterKind ckind, MajorSceneKind scene)
{
    s16 var_r3;

    switch (scene) {
    case MJ_CLASSIC_GOVER:
    case MJ_CLASSIC:
        var_r3 = lbl_803B7978[ckind];
        break;
    case MJ_ADVENTURE_GOVER:
    case MJ_ADVENTURE:
        var_r3 = lbl_803B79BC[ckind];
        break;
    default:
        var_r3 = lbl_803B7A00[ckind];
        break;
    }
    return un_8030813C(var_r3, scene) + 4;
}

char* gm_80160564(CharacterKind ckind, MajorSceneKind scene)
{
    s16 var_r3;

    switch (scene) {
    case MJ_CLASSIC_GOVER:
    case MJ_CLASSIC:
        var_r3 = lbl_803B7978[ckind];
        break;
    case MJ_ADVENTURE_GOVER:
    case MJ_ADVENTURE:
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

void gm_80160B40(HSD_Text* text, u8 ckind, u8 arg2)
{
    f32 var_f31;
    const char* str;

    if (lbLang_IsSavedLanguageUS()) {
        text->default_kerning = 1;
    }
    str = arg2 ? fn_801609E0(ckind) : gm_80160980(ckind);
    if (lbLang_IsSavedLanguageUS()) {
        bool tmp = arg2 && lbl_803D50E4[ckind] != NULL;
        var_f31 = tmp ? lbl_803B7784[ckind] : lbl_803B767C[ckind];
    } else {
        bool tmp = arg2 && lbl_803D5060[ckind] != NULL;
        var_f31 = tmp ? lbl_803B7700[ckind] : lbl_803B75F8[ckind];
    }
    HSD_SisLib_803A6B98(text, 0.0F, 0.0F, str);
    text->font_size.x *= var_f31;
}

/// #gm_80160C90

/// #fn_80160DE8

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

/// #fn_80161004

/// #fn_80161154

/// #fn_80161C90

/// #fn_80162068

/// #fn_80162170

s32 gm_801623A4(MatchEnd* arg0)
{
    fn_80162068();
    return fn_80162170(arg0);
}

int gm_801623D8(void)
{
    return *(s32*) gmMainLib_8015CCF0();
}

void gm_801623FC(int arg0)
{
    s32* temp_r30;
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

/// #gm_8016247C

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
    ptr = (u16*) ((u8*) gmMainLib_8015EDBC() + gm_80164024(arg0) * 2 + 0x18);
    val = *ptr + 1;
    if (val > 0xFFFF) {
        val = 0xFFFF;
    }
    *ptr = val;
}

/// #gm_8016260C

u32 gm_8016279C(void)
{
    return *(u32*) gmMainLib_8015CD2C() + *(u32*) gmMainLib_8015CD38() +
           *(u32*) gmMainLib_8015CD44() + *(u32*) gmMainLib_8015CD50() +
           *(u32*) gmMainLib_8015CD5C();
}

/// #gm_80162800

/// #gm_801628C4

long gm_80162968(u32 seconds)
{
    u32* ptr;

    ptr = gmMainLib_8015CD74();
    *ptr = MAX(*ptr + seconds, (u32) -1);
}

long gm_801629B4(s32 amount)
{
    u32* ptr;

    ptr = gmMainLib_8015CD80();
    *ptr = MAX(*ptr + amount, (u32) -1);
}

long gm_80162A00(void)
{
    u32 a;
    u32 b;

    a = *(u32*) gmMainLib_8015CD14();
    b = *(u32*) gmMainLib_8015CD74();
    return MAX(a + b, (u32) -1);
}

long gm_80162A4C(s32 amount)
{
    u32* ptr;

    ptr = gmMainLib_8015CDA4();
    *ptr = MAX(*ptr + amount, (u32) -1);
}

/// #gm_80162A98

/// #gm_80162B4C

void gm_80162B98(void)
{
    u32* temp_r3;

    temp_r3 = gmMainLib_8015CD8C();
    *temp_r3 = MAX(*temp_r3 + 1, -1);
}

int gm_80162BD8(u8 arg0)
{
    return *gmMainLib_8015D0C0(arg0);
}

/// #fn_80162BFC

/// #gm_80162C48

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

/// #gm_80162D6C

int gm_80162DD4(u8 i)
{
    return *gmMainLib_8015D1E8(i);
}

/// #fn_80162DF8

/// #gm_80162E44

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

/// #gm_80162F68

int gm_80162FD0(u8 i)
{
    return *gmMainLib_8015D310(i);
}

/// #fn_80162FF4

/// #gm_80163040

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

/// #gm_80163164

u32 gm_801631CC(u8 i)
{
    return *gmMainLib_8015D06C(i);
}

/// #gm_801631F0

u16 gm_80163274(u8 i)
{
    return *gmMainLib_8015D7EC(i);
}

/// #gm_80163298

/// #gm_8016332C

/// #gm_80163374

/// #gm_801634D4

bool gm_8016365C(u8 arg0)
{
    if (!gmMainLib_8015D6BC(arg0)) {
        return true;
    }
    return false;
}

/// #gm_80163690

/// #gm_801636D8

/// #gm_80163838

bool gm_801639C0(u8 arg0)
{
    if (!gmMainLib_8015D710(arg0)) {
        return true;
    }
    return false;
}

/// #gm_801639F4

/// #gm_80163A3C

/// #gm_80163B9C

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

/// #gm_80164250

/// #fn_801642A0

/// #gm_80164330

/// #gm_80164430

/// #gm_80164504

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

/// #gm_8016468C

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

/// #gm_80164910

/// #gm_80164A0C

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

/// #fn_80164B48

/// #gm_80164F18

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

/// #fn_801652D8

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

/// #fn_80165548

/// #fn_801656A8

/// #fn_8016588C

/// #fn_80165AC0

/// #fn_80165D60

/// #fn_80165E7C

/// #fn_80165FA4

/// #fn_801661E0

/// #gm_80166378

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

/// #gm_80166A98

u8 fn_80166CBC(struct fn_80166CBC_arg0_t* arg0, ssize_t index)
{
    return arg0[index].x5E;
}

/// #gm_80166CCC

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

/// #gm_80167470

/// #gm_801674C4

/// #fn_8016758C

/// #fn_80167638

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
                vs_data->data.players[i].handicap = *handicap;
                // TODO :: fix these to actually get the offensive and
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
    prefs = gmMainLib_8015CC58();

    // TODO :: some weird item copy thing that needs to be fixed
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

/// #gm_80168638

/// #gm_80168710

/// #gm_801688AC

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

/// #fn_80168A6C

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

void fn_80168F2C(void)
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

// UnclePunch: Audio_LoadAnnouncer
void gm_80168FC4(void)
{
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

/// #fn_80169000

u8 gm_80169238(u8 ckind)
{
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

struct lbl_8046B488_t* fn_80169364(void)
{
    return &lbl_8046B488;
}

u8 gm_80169370(s32 arg0)
{
    return lbl_8046B488.pad_0[arg0];
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

void fn_80169434(s32 arg0)
{
    M2C_FIELD(&lbl_8046B488, s32*, 0x1B8) = arg0;
}

/// #fn_80169444

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
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0x20);
}

UNK_T gm_80169530(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0xA2);
}

UNK_T gm_80169540(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0x124);
}

/// #fn_80169550

/// #fn_80169574

/// #fn_801695BC

/// #fn_801697FC

/// #fn_8016989C

/// #fn_80169900

/// #fn_80169A84

/// #fn_80169C54

/// #fn_80169F50

/// #fn_8016A09C

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

/// #gm_8016A22C

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

/// #fn_8016A488

/// #fn_8016A4C8

void gm_8016A92C(StartMeleeRules* arg0)
{
    lbl_8046B668.unk_1C = -2;
    arg0->x58 = (int) &lbl_8046B668;
}

/// #gm_8016A944

UNK_T gm_8016A97C(void)
{
    return &M2C_FIELD(&lbl_8046B668, UNK_T*, 0x1C);
}

UNK_T gm_8016A98C(void)
{
    return &lbl_8046B668;
}

/// #gm_8016A998

/// #gm_8016A9E8

/// #gm_8016AC44
