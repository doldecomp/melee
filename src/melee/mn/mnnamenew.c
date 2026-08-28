#include "mnnamenew.h"

#include "baselib/debug.h"
#include "dolphin/gx/GXStruct.h"
#include "gm/gm_1A3F.h"
#include "gm/gmmain_lib.h"
#include "gm/gmtoulib.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "lb/lbspdisplay.h"
#include "mn/inlines.h"
#include "mn/mncharsel.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "mn/types.h"
#include "sc/types.h"
#include "sysdolphin/baselib/gobj.h"
#include "sysdolphin/baselib/gobjgxlink.h"
#include "sysdolphin/baselib/gobjobject.h"
#include "sysdolphin/baselib/gobjplink.h"
#include "sysdolphin/baselib/gobjproc.h"
#include "sysdolphin/baselib/gobjuserdata.h"
#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/memory.h"
#include "sysdolphin/baselib/random.h"
#include "sysdolphin/baselib/sislib.h"

typedef char* GlyphRow[4];

/// Glyph strings in the keyboard tables are read through
/// mnNameNew_NullCharacter, which this translation unit declares
/// volatile, so the tables store pointers to volatile characters.
typedef volatile char GlyphChar;

/* 4D6C0C */ u8 mnNameNew_PortInUse;

/// Maps keyboard cursor positions to jobj indices and glyph strings.
/// Mirrors the key_jobj_ids/x34/xFC/character_bytes fields of
/// MnNameNewDataLayout (data object at 0x803EDA7C).
typedef struct MnNameNewKeyMap {
    u16 key_jobj_ids[8];
    GlyphChar* x34[50];
    GlyphChar* xFC[50];
    GlyphChar* character_bytes[50];
} MnNameNewKeyMap;

/// Lowercase/uppercase glyph variant rows for each key. Mirrors the
/// lower_glyphs/upper_glyphs/x8CC fields of MnNameNewDataLayout (data
/// object at 0x803EDCE4).
typedef struct MnNameNewGlyphTable {
    GlyphChar* lower_glyphs[50][4];
    GlyphChar* upper_glyphs[50][4];
} MnNameNewGlyphTable;

typedef struct MnNameNewDataLayout {
    AnimLoopSettings anim[3];
    u16 key_jobj_ids[8];
    char* x34[50];
    char* xFC[50];
    char* character_bytes[50];
    GlyphRow lower_glyphs[50];
    GlyphRow upper_glyphs[50];
    Vec3 x8CC;
    Vec3 x8D8;
    u8 assert_pad[0x20];
    char assert_msg[0x18];
    char assert_file[0xC];
    char assert_cond[0xC];
} MnNameNewDataLayout;

extern void* mnNameNew_804A06F0[4];
extern void* mnNameNew_804A0700[4];
extern void* mnNameNew_804A0710[4];
extern void* mnNameNew_804A0720[8];
extern char mnNameNew_CurrentNameText[0x10];
extern u8 mnNameNew_804D4F7C[8];
HSD_GObj* mnNameNew_804D6C08;

static AnimLoopSettings mnNameNew_803EDA58[3] = {
    { 0.0f, 19.0f, -0.1f },
    { 20.0f, 39.0f, -0.1f },
    { 0.0f, 10.0f, -0.1f },
};

static f32 mnNameNew_804D4C10 = 10.0f;

static MnNameNewKeyMap mnNameNew_KeyMap = {
    { 3, 10, 11, 7, 9, 8, 5, 5 },
    { "あ", "い", "う", "え", "お", "か", "き", "く", "け", "こ",
      "さ", "し", "す", "せ", "そ", "た", "ち", "つ", "て", "と",
      "な", "に", "ぬ", "ね", "の", "は", "ひ", "ふ", "へ", "ほ",
      "ま", "み", "む", "め", "も", "や", "ゆ", "よ", "　", "　",
      "ら", "り", "る", "れ", "ろ", "わ", "を", "ん", "ー", "。" },
    { "ア", "イ", "ウ", "エ", "オ", "カ", "キ", "ク", "ケ", "コ",
      "サ", "シ", "ス", "セ", "ソ", "タ", "チ", "ツ", "テ", "ト",
      "ナ", "ニ", "ヌ", "ネ", "ノ", "ハ", "ヒ", "フ", "ヘ", "ホ",
      "マ", "ミ", "ム", "メ", "モ", "ヤ", "ユ", "ヨ", "　", "　",
      "ラ", "リ", "ル", "レ", "ロ", "ワ", "ヲ", "ン", "ー", "。" },
    { "Ｊ", "Ｔ", "　", "９", "．", "Ｉ", "Ｓ", "　", "８", "＄",
      "Ｈ", "Ｒ", "　", "７", "＆", "Ｇ", "Ｑ", "　", "６", "％",
      "Ｆ", "Ｐ", "Ｚ", "５", "＠", "Ｅ", "Ｏ", "Ｙ", "４", "？",
      "Ｄ", "Ｎ", "Ｘ", "３", "！", "Ｃ", "Ｍ", "Ｗ", "２", "＝",
      "Ｂ", "Ｌ", "Ｖ", "１", "＋", "Ａ", "Ｋ", "Ｕ", "０", "－" },
};

/** @remarks The original defines mnNameNew_NullCharacter between the first
 * two glyph literals of the table below, which C cannot express; the seed
 * restores that literal-pool order.
 */
#ifdef MUST_MATCH
static void order_sdata(void)
{
    (void) "ぁ";
}
#endif

char mnNameNew_NullCharacter[1] = "";

static MnNameNewGlyphTable mnNameNew_GlyphTable = {
    {
        { "あ", "ぁ", mnNameNew_NullCharacter },
        { "い", "ぃ", mnNameNew_NullCharacter },
        { "う", "ぅ", mnNameNew_NullCharacter },
        { "え", "ぇ", mnNameNew_NullCharacter },
        { "お", "ぉ", mnNameNew_NullCharacter },
        { "か", "が", mnNameNew_NullCharacter },
        { "き", "ぎ", mnNameNew_NullCharacter },
        { "く", "ぐ", mnNameNew_NullCharacter },
        { "け", "げ", mnNameNew_NullCharacter },
        { "こ", "ご", mnNameNew_NullCharacter },
        { "さ", "ざ", mnNameNew_NullCharacter },
        { "し", "じ", mnNameNew_NullCharacter },
        { "す", "ず", mnNameNew_NullCharacter },
        { "せ", "ぜ", mnNameNew_NullCharacter },
        { "そ", "ぞ", mnNameNew_NullCharacter },
        { "た", "だ", mnNameNew_NullCharacter },
        { "ち", "ぢ", mnNameNew_NullCharacter },
        { "つ", "づ", "っ", mnNameNew_NullCharacter },
        { "て", "で", mnNameNew_NullCharacter },
        { "と", "ど", mnNameNew_NullCharacter },
        { "な", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "に", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ぬ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ね", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "の", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "は", "ば", "ぱ", mnNameNew_NullCharacter },
        { "ひ", "び", "ぴ", mnNameNew_NullCharacter },
        { "ふ", "ぶ", "ぷ", mnNameNew_NullCharacter },
        { "へ", "べ", "ぺ", mnNameNew_NullCharacter },
        { "ほ", "ぼ", "ぽ", mnNameNew_NullCharacter },
        { "ま", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "み", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "む", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "め", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "も", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "や", "ゃ", mnNameNew_NullCharacter },
        { "ゆ", "ゅ", mnNameNew_NullCharacter },
        { "よ", "ょ", mnNameNew_NullCharacter },
        { "　", " ", mnNameNew_NullCharacter },
        { "　", " ", mnNameNew_NullCharacter },
        { "ら", mnNameNew_NullCharacter },
        { "り", mnNameNew_NullCharacter },
        { "る", mnNameNew_NullCharacter },
        { "れ", mnNameNew_NullCharacter },
        { "ろ", mnNameNew_NullCharacter },
        { "わ", mnNameNew_NullCharacter },
        { "を", mnNameNew_NullCharacter },
        { "ん", mnNameNew_NullCharacter },
        { "ー", mnNameNew_NullCharacter },
        { "。", mnNameNew_NullCharacter },
    },
    {
        { "ア", "ァ", mnNameNew_NullCharacter },
        { "イ", "ィ", mnNameNew_NullCharacter },
        { "ウ", "ゥ", mnNameNew_NullCharacter },
        { "エ", "ェ", mnNameNew_NullCharacter },
        { "オ", "ォ", mnNameNew_NullCharacter },
        { "カ", "ガ", mnNameNew_NullCharacter },
        { "キ", "ギ", mnNameNew_NullCharacter },
        { "ク", "グ", mnNameNew_NullCharacter },
        { "ケ", "ゲ", mnNameNew_NullCharacter },
        { "コ", "ゴ", mnNameNew_NullCharacter },
        { "サ", "ザ", mnNameNew_NullCharacter },
        { "シ", "ジ", mnNameNew_NullCharacter },
        { "ス", "ズ", mnNameNew_NullCharacter },
        { "セ", "ゼ", mnNameNew_NullCharacter },
        { "ソ", "ゾ", mnNameNew_NullCharacter },
        { "タ", "ダ", mnNameNew_NullCharacter },
        { "チ", "ヂ", mnNameNew_NullCharacter },
        { "ツ", "ヅ", "ッ", mnNameNew_NullCharacter },
        { "テ", "デ", mnNameNew_NullCharacter },
        { "ト", "ド", mnNameNew_NullCharacter },
        { "ナ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ニ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ヌ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ネ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ノ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ハ", "バ", "パ", mnNameNew_NullCharacter },
        { "ヒ", "ビ", "ピ", mnNameNew_NullCharacter },
        { "フ", "ブ", "プ", mnNameNew_NullCharacter },
        { "ヘ", "ベ", "ペ", mnNameNew_NullCharacter },
        { "ホ", "ボ", "ポ", mnNameNew_NullCharacter },
        { "マ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ミ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ム", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "メ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "モ", mnNameNew_NullCharacter, mnNameNew_NullCharacter },
        { "ヤ", "ャ", mnNameNew_NullCharacter },
        { "ユ", "ュ", mnNameNew_NullCharacter },
        { "ヨ", "ョ", mnNameNew_NullCharacter },
        { "　", " ", mnNameNew_NullCharacter },
        { "　", " ", mnNameNew_NullCharacter },
        { "ラ", mnNameNew_NullCharacter },
        { "リ", mnNameNew_NullCharacter },
        { "ル", mnNameNew_NullCharacter },
        { "レ", mnNameNew_NullCharacter },
        { "ロ", mnNameNew_NullCharacter },
        { "ワ", mnNameNew_NullCharacter },
        { "ヲ", mnNameNew_NullCharacter },
        { "ン", mnNameNew_NullCharacter },
        { "～", mnNameNew_NullCharacter },
        { "、", mnNameNew_NullCharacter },
    },
};

Vec3 unk_vec = { -0.8f, 0.4f, 0.0f };
static Vec3 mnNameNew_803EE330 = { -0.7f, 0.7f, 0.0f };

void mnNameNew_8023B0F8(HSD_GObj* arg0, u8 arg1)
{
    HSD_JObj* jobj;
    NameNewEntry* data;

    PAD_STACK(8);

    data = arg0->user_data;
    jobj = data->jobjs[10];
    if (arg1 == 0x33) {
        HSD_JObjReqAnimAll(jobj, 1.0f);
    } else if (data->mode == 0) {
        HSD_JObjReqAnimAll(jobj, 2.0f);
    } else {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    }
    HSD_JObjAnimAll(jobj);
    jobj = data->jobjs[11];
    if (arg1 == 0x34) {
        HSD_JObjReqAnimAll(jobj, 1.0f);
    } else if (data->mode == 1) {
        HSD_JObjReqAnimAll(jobj, 2.0f);
    } else {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    }
    HSD_JObjAnimAll(jobj);
    jobj = data->jobjs[7];
    if (arg1 == 0x35) {
        HSD_JObjReqAnimAll(jobj, 1.0f);
    } else if (data->mode == 2) {
        HSD_JObjReqAnimAll(jobj, 2.0f);
    } else {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    }
    HSD_JObjAnimAll(jobj);
}

void mnNameNew_8023B224(u8 arg0)
{
    NameNewEntry* temp_r31;
    u8 temp_r30;

    PAD_STACK(8);

    temp_r31 = mnNameNew_804D6C08->user_data;
    temp_r30 = temp_r31->name_index;
    if (arg0 != 0) {
        lb_8001CE00();
    }
    if (gm_GetCurrentGameMode() == GM_TOURNAMENT) {
        HSD_SisLib_803A5E70();
        mn_8022EBDC();
        if (arg0 != 0) {
            gm_80190FE4((s32) temp_r30);
            return;
        }
        gm_80190FE4(0x78);
        return;
    }
    if (gm_GetCurrentGameMode() == GM_MENU) {
        mn_804D6BC8.cooldown = 5;
        if (arg0 != 0 && GetNameCount() > 0x18) {
            mnName_8023A9B4((u8) (temp_r31->name_index / 6));
            return;
        }
        mnName_8023A9B4(0U);
        return;
    }
    HSD_SisLib_803A5E70();
    mn_8022EBDC();
    mnCharSel_802640A0();
}

void mnNameNew_8023B314(NameNewEntry* arg0, s32 arg1)
{
    HSD_Text* text;
    u8 idx;
    s32 var_r4;

    var_r4 = arg1;
    if (var_r4 < 0x32) {
        switch (arg0->mode) {
        case 0:
            var_r4 = 0x33;
            break;
        case 1:
            var_r4 = 0x34;
            break;
        case 2:
            var_r4 = 0x35;
            break;
        }
    }
    text = arg0->desc_text;
    idx = mnNameNew_804D4F7C[var_r4 - 0x32];
    if (text != NULL) {
        if (text->sis_buffer == ((SIS**) HSD_SisLib_804D1124[0])[idx]) {
            return;
        }
        HSD_SisLib_803A5CC4(arg0->desc_text);
    }
    text = HSD_SisLib_803A5ACC(0, (s32) mn_804D6BB4, -9.5f, 9.1f, 17.0f,
                               364.68332f, 38.38772f);
    arg0->desc_text = text;
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(text, (s32) idx);
}

static GXColor mnNameNew_804D4F68 = { 0, 0, 0, 0xFF };
static GXColor mnNameNew_804D4F6C = { 0xA6, 0x81, 0x3D, 0xFF };
static GXColor mnNameNew_804D4F70 = { 0, 0, 0, 0xFF };
static GXColor mnNameNew_804D4F74 = { 0x74, 0x4F, 0x0B, 0xFF };
static GXColor mnNameNew_804D4F78 = { 0, 0, 0, 0xFF };

u8 mnNameNew_804D4F7C[8] = { 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'H' };

GXColor const mnNameNew_804DBF44 = { 0xA6, 0x81, 0x3D, 0xFF };
GXColor const mnNameNew_804DBF48 = { 0x00, 0x00, 0x00, 0xFF };

s32 mnNameNew_KeySetup(NameNewEntry* arg0, u8 arg1)
{
    Vec3 sp50;
    GXColor sp4C;
    GXColor sp48;
    GXColor color;
    MnNameNewDataLayout* layout;
    s32 j;
    HSD_Text* text;
    HSD_JObj* ref1;
    HSD_JObj* ref2;
    char** str_table;
    f32 x_range;
    f32 y_range;
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    f32 base_x;
    f32 base_y;
    f32 font_x;
    f32 col_x;
    s32 i;
    HSD_JObj* key_jobj;
    GXColor* color_ptr;

    FORCE_PAD_STACK(16);

    layout = (MnNameNewDataLayout*) mnNameNew_803EDA58;
    sp4C = mnNameNew_804DBF44;
    sp48 = mnNameNew_804DBF48;

    switch ((s32) arg1) {
    case 0:
        arg0->mode = 0;
        str_table = layout->x34;
        break;
    case 1:
        arg0->mode = 1;
        str_table = layout->xFC;
        break;
    case 2:
        arg0->mode = 2;
        str_table = layout->character_bytes;
        break;
    }

    if (arg0->key_text != NULL) {
        HSD_SisLib_803A5CC4(arg0->key_text);
    }
    text = HSD_SisLib_803A6754(0, (s32) mn_804D6BB5);
    arg0->key_text = text;

    key_jobj = arg0->jobjs[16];
    if (key_jobj == NULL) {
        key_jobj = NULL;
    } else {
        key_jobj = key_jobj->child;
    }
    for (i = 0; i < 50; i++) {
        if (i == 0x2D) {
            break;
        }
        if (key_jobj == NULL) {
            key_jobj = NULL;
        } else {
            key_jobj = key_jobj->next;
        }
    }

    lb_8000B1CC(key_jobj, &layout->x8CC, &sp50);
    pos_x = sp50.x;
    pos_y = -sp50.y;
    pos_z = sp50.z;
    text->pos_x = pos_x;
    text->pos_y = pos_y;
    text->pos_z = pos_z;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.04f;
    text->text_color = mnNameNew_804D4F6C;

    ref1 = arg0->jobjs[16];
    if (ref1 == NULL) {
        ref1 = NULL;
    } else {
        ref1 = ref1->child;
    }
    for (i = 0; i < 50; i++) {
        if (i == 0x28) {
            break;
        }
        if (ref1 == NULL) {
            ref1 = NULL;
        } else {
            ref1 = ref1->next;
        }
    }

    base_x = HSD_JObjGetTranslationX(key_jobj);
    x_range = HSD_JObjGetTranslationX(ref1) - base_x;

    ref2 = arg0->jobjs[16];
    if (ref2 == NULL) {
        ref2 = NULL;
    } else {
        ref2 = ref2->child;
    }
    for (i = 0; i < 50; i++) {
        if (i == 0x2E) {
            break;
        }
        if (ref2 == NULL) {
            ref2 = NULL;
        } else {
            ref2 = ref2->next;
        }
    }

    base_y = HSD_JObjGetTranslationY(key_jobj);
    y_range = -(HSD_JObjGetTranslationY(ref2) - base_y);

    j = 0;
    for (; j < 0x32; j++) {
        font_x = text->font_size.x;
        col_x = (f32) (9 - (j / 5)) * x_range;
        HSD_SisLib_803A6B98(text, col_x / font_x,
                            ((f32) (j % 5) * y_range) / text->font_size.y,
                            str_table[j], font_x, col_x);
        if (j == (s32) mn_804A04F0.hovered_selection) {
            color_ptr = &sp48;
        } else {
            color_ptr = &sp4C;
        }
        color = *color_ptr;
        color_ptr = &color;
        HSD_SisLib_803A74F0(text, j, color_ptr);
    }

    return (s32) text;
}

s32 mnNameNew_8023BAA8(NameNewEntry* arg0, s32 arg1, u8 arg2)
{
    u8 mode;

    if (arg2 >= 0x32U && arg2 < 0x3AU) {
        if (arg1 & 1) {
            if (arg2 == 0x39) {
                return ((arg0->last_key_sel / 5) * 5) + 4;
            }
            if (arg2 > 0x32U) {
                return arg2 - 1;
            }
            return 0x38;
        }
        if (arg1 & 2) {
            if (arg2 == 0x39) {
                return (arg0->last_key_sel / 5) * 5;
            }
            if (arg2 == 0x38) {
                return 0x32;
            }
            return arg2 + 1;
        }
        if (arg1 & 4) {
            if (arg2 != 0x38 && arg2 != 0x39) {
                return arg0->last_key_sel % 5;
            }
        } else if ((arg1 & 8) && arg2 != 0x38 && arg2 != 0x39) {
            return (arg0->last_key_sel % 5) + 0x2D;
        }
    } else {
        if (arg1 & 1) {
            if ((arg2 % 5) != 0) {
                return arg2 - 1;
            }
            return 0x39;
        }
        if (arg1 & 2) {
            if ((s32) (arg2 % 5) == 4) {
                return 0x39;
            }
            return arg2 + 1;
        }
        if (arg1 & 4) {
            if ((s32) (arg2 / 5) < 9) {
                return arg2 + 5;
            }
            mode = arg0->mode;
            switch ((s32) mode) {
            case 0:
                return 0x33;
            case 1:
                return 0x34;
            case 2:
                return 0x35;
            }
        } else if (arg1 & 8) {
            if ((arg2 / 5) != 0) {
                return arg2 - 5;
            }
            mode = arg0->mode;
            switch ((s32) mode) {
            case 0:
                return 0x33;
            case 1:
                return 0x34;
            case 2:
                return 0x35;
            }
        }
    }
    return (s32) arg2;
}

static inline s8 CopyAutoNameText(char* output, s32 pick)
{
    s32 name_idx;
    u8 ch;
    u8** name_ptr;
    char* text;
    s32 char_idx;
    s8 null_ch;

    name_idx = 0;
    char_idx = name_idx;
    output[0] = *mnNameNew_NullCharacter;
    text = output;
    output[3] = *mnNameNew_NullCharacter;
    output[6] = *mnNameNew_NullCharacter;
    output[9] = *mnNameNew_NullCharacter;

    name_ptr = &AutoNamesList[pick];
    while ((null_ch = (s8) *mnNameNew_NullCharacter) !=
           (s8) (ch = (*name_ptr)[char_idx]))
    {
        text[0] = ch;
        text[1] = (*name_ptr)[char_idx + 1];
        text[2] = *mnNameNew_NullCharacter;
        char_idx += 2;
        name_idx++;
        text += 3;
    }

    output[name_idx * 3] = null_ch;
    return null_ch;
}

static inline void UpdateAutoNameHistory(NameNewEntry* data, s32 pick)
{
    u8 tmp;
    s32 i;

    tmp = data->auto_history[0];
    data->auto_history[0] = (u8) pick;
    for (i = 1; i < 5; i++) {
        u8 next = data->auto_history[i];
        data->auto_history[i] = tmp;
        tmp = next;
    }
}

s32 PickAutoName(HSD_GObj* arg0)
{
    NameNewEntry* data;
    char* cur_text;
    u8** names;
    s32 count;
    s32 pick;
    s32 dup;
    s8 null_ch;

    PAD_STACK(32);

    data = arg0->user_data;
    cur_text = mnNameNew_CurrentNameText;

    do {
        dup = 0;
        do {
            null_ch = (s8) *mnNameNew_NullCharacter;
            count = 0;
            names = AutoNamesList;
            while (null_ch != (s8) * *names) {
                names++;
                count++;
            }
            pick = HSD_Randi(count);
        } while (IsNameUnique((char*) AutoNamesList[pick]) != 0);

        if (pick == (s32) data->auto_history[0]) {
            dup = 1;
        } else if (pick == (s32) data->auto_history[1]) {
            dup = 1;
        } else if (pick == (s32) data->auto_history[2]) {
            dup = 1;
        } else if (pick == (s32) data->auto_history[3]) {
            dup = 1;
        } else if (pick == (s32) data->auto_history[4]) {
            dup = 1;
        }
    } while (dup != 0);

    null_ch = CopyAutoNameText(cur_text, pick);
    UpdateAutoNameHistory(data, pick);

    return (s32) null_ch;
}

#line 779 "mnnamenew.c"
bool NameContainsOnlySpaces(void)
{
    s16 null_char;
    char* text = mnNameNew_CurrentNameText;
    s32 i;

    for (i = 0; i < 4; i++) {
        null_char = (s8) *mnNameNew_NullCharacter;
        if (null_char != (s8) text[0]) {
            if ((s8) * (char*) "　" != (s8) text[0] ||
                ((GlyphChar*) "　")[1] != text[1])
            {
                return false;
            }
        }
        text += 3;
    }
    return true;
}

static inline void CopyCurrentNameToNametag(struct NameTagData* nametag)
{
    s32 idx;
    u8* text;
    u8 ch;
    s8 null_ch;

    text = (u8*) mnNameNew_CurrentNameText;
    null_ch = (s8) *mnNameNew_NullCharacter;
    idx = 0;
    if (null_ch != (s8) *text) {
        u8* ptr;
        ptr = text;
        while ((null_ch = (s8) *mnNameNew_NullCharacter) != (s8) (ch = *ptr)) {
            nametag->namedata[idx] = (s8) ch;
            idx += 1;
            ptr += 1;
        }
        if (null_ch != (s8) * (text += 3)) {
            ptr = text;
            while ((null_ch = (s8) *mnNameNew_NullCharacter) !=
                   (s8) (ch = *ptr))
            {
                nametag->namedata[idx] = (s8) ch;
                idx += 1;
                ptr += 1;
            }
            if (null_ch != (s8) * (text += 3)) {
                ptr = text;
                while ((null_ch = (s8) *mnNameNew_NullCharacter) !=
                       (s8) (ch = *ptr))
                {
                    nametag->namedata[idx] = (s8) ch;
                    idx += 1;
                    ptr += 1;
                }
                if (null_ch != (s8) * (text += 3)) {
                    ptr = text;
                    while ((null_ch = (s8) *mnNameNew_NullCharacter) !=
                           (s8) (ch = *ptr))
                    {
                        nametag->namedata[idx] = (s8) ch;
                        idx += 1;
                        ptr += 1;
                    }
                }
            }
        }
    }
    nametag->namedata[idx] = (s8) *mnNameNew_NullCharacter;
}

s32 WriteCharactersForNameAtIndex(u8 arg0, s32 arg1)
{
    struct NameTagData* nametag;
    s32 ret;

    nametag = GetPersistentNameData((s32) arg0);
    CopyCurrentNameToNametag(nametag);
    ret = GetRumbleSettingOfPort(arg1);
    nametag->rumble_toggle = ret;
    return ret;
}

static inline char** AddCharacterToName_getGlyphs(GlyphRow* arg0, u8 arg1)
{
    return (char**) &arg0[arg1];
}

char* AddCharacterToName(char* arg0, u8 arg1, u8 arg2, u8 arg3)
{
    char ch;
    char* var_r4;
    char** table;
    MnNameNewDataLayout* layout;
    u32 temp;

    layout = (MnNameNewDataLayout*) mnNameNew_803EDA58;
    if ((s32) arg3 != 2) {
        if (((((s32) (temp = arg3)) < ((u16) 2)) & 0xFFFFFFFF) &&
            (((s32) ((u32) arg3)) >= 0))
        {
            char null;
            s32 idx;

            if ((u8) (arg1 - 0x30) <= 1U) {
                if ((arg2 % 2) != 0) {
                    table = AddCharacterToName_getGlyphs(layout->upper_glyphs,
                                                         arg1);
                } else {
                    table = AddCharacterToName_getGlyphs(layout->lower_glyphs,
                                                         arg1);
                }
            } else if ((arg3 == 0 && (arg2 % 2) == 0) ||
                       (arg3 == 1 && (arg2 % 2) != 0))
            {
                table =
                    AddCharacterToName_getGlyphs(layout->lower_glyphs, arg1);
            } else {
                table =
                    AddCharacterToName_getGlyphs(layout->upper_glyphs, arg1);
            }
            var_r4 = arg0;

            for (idx = layout->character_bytes[arg1][1] * 0;
                 (null = (*mnNameNew_NullCharacter & 0xFFFF) & 0xFFFF) !=
                 (ch = table[arg2 / 2][idx] & (0xFF & 0xFFu));
                 idx++)
            {
                var_r4[idx] = ch;
            }
            arg0[idx] = null;
        }
        return arg0;
    }
    arg0[0] = layout->character_bytes[arg1][0];
    arg0[1] = layout->character_bytes[arg1][1];
    arg0[2] = layout->character_bytes[arg1][2];
    return arg0;
}

void mnNameNew_GlyphVariantInput(void)
{
    NameNewEntry* data;
    u32 buttons;
    s32 count;
    u16 old_hover;
    u8 old_sel;
    u8 cur_pos;
    GlyphChar** table;
    s32 total;
    s8 null_ch;

    PAD_STACK(16);

    data = mnNameNew_804D6C08->user_data;
    buttons = mn_80229624((u32) mnNameNew_PortInUse);
    mn_804A04F0.buttons = buttons;
    count = 0;
    if (buttons & 0x200) {
        HSD_GObjPLink_80390228(data->variant_gobj);
        data->variant_gobj = NULL;
        AddCharacterToName(&mnNameNew_CurrentNameText[data->cursor_pos * 3],
                           mn_804A04F0.hovered_selection,
                           mn_804A04F0.confirmed_selection, data->mode);
        sfxForward();
        cur_pos = data->cursor_pos;
        old_hover = mn_804A04F0.hovered_selection;
        count = (s32) old_hover;
        if (cur_pos < 3U) {
            data->cursor_pos = (u8) (cur_pos + 1);
        } else {
            mn_804A04F0.hovered_selection = 0x39;
        }
        mnNameNew_8023CE4C();
        if (((count != 0x30) && (count != 0x31)) &&
            ((mn_804A04F0.confirmed_selection % 2) != 0))
        {
            if (data->mode == 0) {
                data->mode = 1;
            } else {
                data->mode = 0;
            }
            mnNameNew_KeySetup(data, data->mode);
            mnNameNew_8023B0F8(mnNameNew_804D6C08,
                               (u8) mn_804A04F0.hovered_selection);
            mnNameNew_8023B314(data, (s32) mn_804A04F0.hovered_selection);
        }
    } else {
        if (buttons & 0x20) {
            HSD_GObjPLink_80390228(data->variant_gobj);
            data->variant_gobj = NULL;
            mnNameNew_8023CE4C();
            return;
        }
        null_ch = (s8) *mnNameNew_NullCharacter;
        table = mnNameNew_GlyphTable.lower_glyphs[data->x1];
        while (null_ch != (s8) * *table) {
            table++;
            count++;
        }
        total = (0, count * 2);
        old_sel = mn_804A04F0.confirmed_selection;
        if (buttons & 1) {
            if ((mn_804A04F0.confirmed_selection % 2) != 0) {
                mn_804A04F0.confirmed_selection -= 1;
            } else {
                mn_804A04F0.confirmed_selection += 1;
            }
        } else if (buttons & 2) {
            if ((mn_804A04F0.confirmed_selection % 2) != 0) {
                mn_804A04F0.confirmed_selection -= 1;
            } else {
                mn_804A04F0.confirmed_selection += 1;
            }
        } else if (buttons & 4) {
            if ((mn_804A04F0.confirmed_selection / 2) == 0) {
                mn_804A04F0.confirmed_selection =
                    (mn_804A04F0.confirmed_selection % 2) +
                    ((total / 2 - 1) * 2);
            } else {
                mn_804A04F0.confirmed_selection -= 2;
            }
        } else if (buttons & 8) {
            if ((mn_804A04F0.confirmed_selection / 2) == (total / 2 - 1)) {
                mn_804A04F0.confirmed_selection =
                    mn_804A04F0.confirmed_selection % 2;
            } else {
                mn_804A04F0.confirmed_selection += 2;
            }
        }
        if (old_sel != mn_804A04F0.confirmed_selection) {
            sfxMove();
        }
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void mnNameNew_MainInput(HSD_GObj* arg0)
{
    char name_buffer[16];
    NameNewEntry* data;
    MnNameNewDataLayout* layout;
    u32 buttons;
    char* name_text;
    char* key_char;
    s8 null_char;
    s32 n;
    char* dest;
    s32 len;
    u8 cursor;
    char* src;

    name_text = mnNameNew_CurrentNameText;
    {
        NameNewEntry* entry = mnNameNew_804D6C08->user_data;
        data = entry;
    }
    layout = (MnNameNewDataLayout*) mnNameNew_803EDA58;

    if (data->variant_gobj != NULL) {
        mnNameNew_GlyphVariantInput();
        return;
    }

    buttons = (mn_804A04F0.buttons = mn_80229624((u32) mnNameNew_PortInUse));
    n = 0;

    if (buttons & 0x200) {
        u16 sel = mn_804A04F0.hovered_selection;
        if (sel < 0x32U) {
            if (data->mode != 2 && sel < 0x32U) {
                key_char = layout->lower_glyphs[(u8) sel][0];
                if ("　"[0] == (s8) key_char[0] &&
                    (s8) "　"[1] == (s8) key_char[1])
                {
                    n = 1;
                } else {
                    n = 0;
                }
                if (n == 0) {
                    lbAudioAx_80024030(1);
                    mn_804A04F0.confirmed_selection = 0;
                    n = 0;
                    {
                        u16 sel2 = mn_804A04F0.hovered_selection;
                        GlyphRow* glyphs = layout->lower_glyphs;
                        char** ptrs = glyphs[(u8) sel2];
                        null_char =
                            (s8) * ((GlyphChar*) mnNameNew_NullCharacter);
                        while (null_char != (s8) *ptrs[0]) {
                            ptrs++;
                            n++;
                        }
                    }
                    {
                        s32 variant_count = (n * 2) & 0xFE;
                        data->variant_gobj =
                            (HSD_GObj*) mnNameNew_GlyphVariantSetup(
                                data, variant_count,
                                mn_804A04F0.hovered_selection);
                    }
                    return;
                }
                cursor = data->cursor_pos;
                name_text[cursor * 3] = "　"[0];
                name_text[cursor * 3 + 1] = "　"[1];
                name_text[cursor * 3 + 2] =
                    *((GlyphChar*) mnNameNew_NullCharacter);
                lbAudioAx_80024030(1);
                if (data->cursor_pos < 3) {
                    data->cursor_pos = (u8) (data->cursor_pos + 1);
                } else {
                    mn_804A04F0.hovered_selection = 0x39;
                }
                mnNameNew_8023CE4C();
                return;
            }
            AddCharacterToName(&name_text[data->cursor_pos * 3],
                               mn_804A04F0.hovered_selection, 0U, data->mode);
            lbAudioAx_80024030(1);
            if (data->cursor_pos < 3) {
                data->cursor_pos = (u8) (data->cursor_pos + 1);
            } else {
                mn_804A04F0.hovered_selection = 0x39;
            }
            mnNameNew_8023CE4C();
            return;
        } else {
            switch (sel) {
            case 0x32:
                lbAudioAx_80024030(0);
                mnNameNew_8023B224(0U);
                return;

            case 0x33:
                if (data->mode != 0) {
                    lbAudioAx_80024030(1);
                    data->mode = 0;
                    mnNameNew_KeySetup(data, 0);
                    mnNameNew_8023B0F8(mnNameNew_804D6C08,
                                       (u8) mn_804A04F0.hovered_selection);
                    return;
                }
                break;

            case 0x34:
                if (data->mode != 1) {
                    lbAudioAx_80024030(1);
                    data->mode = 1;
                    mnNameNew_KeySetup(data, 1);
                    mnNameNew_8023B0F8(mnNameNew_804D6C08,
                                       (u8) mn_804A04F0.hovered_selection);
                    return;
                }
                break;

            case 0x35:
                if (data->mode != 2) {
                    lbAudioAx_80024030(1);
                    data->mode = 2;
                    mnNameNew_KeySetup(data, 2);
                    mnNameNew_8023B0F8(mnNameNew_804D6C08,
                                       (u8) mn_804A04F0.hovered_selection);
                    return;
                }
                break;

            case 0x36:
                lbAudioAx_80024030(0);
                cursor = data->cursor_pos;
                (void) cursor;
                {
                    char* slot = &name_text[cursor * 3];
                    if ((s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                        (s8) slot[0])
                    {
                        n = 1;
                    }
                    if (n != 0) {
                        slot[0] = *((GlyphChar*) mnNameNew_NullCharacter);
                        mnNameNew_8023CE4C();
                        return;
                    }
                }
                if (cursor != 0) {
                    name_text[(u8) (cursor - 1) * 3] =
                        *((GlyphChar*) mnNameNew_NullCharacter);
                    data->cursor_pos = (u8) (data->cursor_pos - 1);
                    mnNameNew_8023CE4C();
                    return;
                }
                lbAudioAx_80024030(3);
                return;

            case 0x37:
                lbAudioAx_80024030(1);
                PickAutoName(mnNameNew_804D6C08);
                null_char = (s8) * ((GlyphChar*) mnNameNew_NullCharacter);
                {
                    char* p = name_text;
                    if (null_char != (s8) *p) {
                        n = 1;
                        p += 3;
                        if (null_char != (s8) *p) {
                            n = 2;
                            p += 3;
                            if (null_char != (s8) *p) {
                                n = 3;
                                p += 3;
                                if (null_char != (s8) *p) {
                                    n = 4;
                                }
                            }
                        }
                    }
                }
                if (n == 4) {
                    data->cursor_pos = 3;
                } else {
                    data->cursor_pos = (u8) n;
                }
                mnNameNew_8023CE4C();
                return;

            case 0x38:
            case 0x39:
                dest = name_buffer;
                len = 0;

                {
                    char* src_iter;
                    char* dest_iter;

                    src = name_text;
                    src_iter = src;
                    dest_iter = dest;
                    for (; (s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                           (s8) *src_iter;
                         dest_iter++, dest++, len++, src_iter++)
                    {
                        *dest_iter = *src_iter;
                    }

                    src += 3;
                    src_iter = src;
                    dest_iter = dest;
                    for (; (s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                           (s8) *src_iter;
                         dest_iter++, dest++, len++, src_iter++)
                    {
                        *dest_iter = *src_iter;
                    }

                    src += 3;
                    src_iter = src;
                    dest_iter = dest;
                    for (; (s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                           (s8) *src_iter;
                         dest_iter++, dest++, len++, src_iter++)
                    {
                        *dest_iter = *src_iter;
                    }

                    src += 3;
                    src_iter = src;
                    dest_iter = dest;
                    for (; (s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                           (s8) *src_iter;
                         dest_iter++, dest++, len++, src_iter++)
                    {
                        *dest_iter = *src_iter;
                    }
                }

                name_buffer[len] = *((GlyphChar*) mnNameNew_NullCharacter);

                if ((s8) name_text[0] ==
                    (s8) * ((GlyphChar*) mnNameNew_NullCharacter))
                {
                    n = 1;
                } else {
                    n = 0;
                }
                if (n == 0 && NameContainsOnlySpaces() == 0 &&
                    IsNameUnique(name_buffer) == 0 &&
                    IsNameNotAllowed(name_buffer) == 0)
                {
                    n = 1;
                } else {
                    n = 0;
                }
                if (n != 0) {
                    lbAudioAx_80024030(1);
                    {
                        u8 name_index = data->name_index;
                        CreateNameAtIndex((s32) name_index);
                    }
                    WriteCharactersForNameAtIndex(data->name_index,
                                                  (s32) mn_802295AC());
                    mnNameNew_8023B224(1U);
                    return;
                }
                lbAudioAx_80024030(3);
                return;
            }
        }
        return;
    }
    if (buttons & 0x100) {
        if (mn_804A04F0.hovered_selection == 0x38 ||
            mn_804A04F0.hovered_selection == 0x39)
        {
            dest = name_buffer;
            len = 0;

            {
                char* src_iter;
                char* dest_iter;

                src = name_text;
                src_iter = src;
                dest_iter = dest;
                for (; (s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                       (s8) *src_iter;
                     dest_iter++, dest++, len++, src_iter++)
                {
                    *dest_iter = *src_iter;
                }

                src += 3;
                src_iter = src;
                dest_iter = dest;
                for (; (s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                       (s8) *src_iter;
                     dest_iter++, dest++, len++, src_iter++)
                {
                    *dest_iter = *src_iter;
                }

                src += 3;
                src_iter = src;
                dest_iter = dest;
                for (; (s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                       (s8) *src_iter;
                     dest_iter++, dest++, len++, src_iter++)
                {
                    *dest_iter = *src_iter;
                }

                src += 3;
                src_iter = src;
                dest_iter = dest;
                for (; (s8) * ((GlyphChar*) mnNameNew_NullCharacter) !=
                       (s8) *src_iter;
                     dest_iter++, dest++, len++, src_iter++)
                {
                    *dest_iter = *src_iter;
                }
            }

            name_buffer[len] = *((GlyphChar*) mnNameNew_NullCharacter);

            if ((s8) name_text[0] ==
                (s8) * ((GlyphChar*) mnNameNew_NullCharacter))
            {
                n = 1;
            } else {
                n = 0;
            }
            if (n == 0 && NameContainsOnlySpaces() == 0 &&
                IsNameUnique(name_buffer) == 0 &&
                IsNameNotAllowed(name_buffer) == 0)
            {
                n = 1;
            } else {
                n = 0;
            }
            if (n != 0) {
                lbAudioAx_80024030(1);
                CreateNameAtIndex((s32) data->name_index);
                WriteCharactersForNameAtIndex(data->name_index,
                                              (s32) mn_802295AC());
                mnNameNew_8023B224(1U);
                return;
            }
            lbAudioAx_80024030(3);
            return;
        }
        mn_804A04F0.hovered_selection = 0x39;
        return;
    }
    if (buttons & 0xC0) {
        lbAudioAx_80024030(1);
        if (buttons & 0x40) {
            s32 mode = data->mode;

            if (mode != 0) {
                data->mode = (u8) (data->mode - 1);
            } else {
                data->mode = 2;
            }
        } else {
            if (data->mode < 2) {
                data->mode = (u8) (data->mode + 1);
            } else {
                data->mode = 0;
            }
        }
        mnNameNew_KeySetup(data, data->mode);
        mnNameNew_8023B0F8(mnNameNew_804D6C08,
                           (u8) mn_804A04F0.hovered_selection);
        mnNameNew_8023B314(data, (s32) mn_804A04F0.hovered_selection);
        return;
    }
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        null_char = (s8) * ((GlyphChar*) mnNameNew_NullCharacter);
        if (null_char == (s8) name_text[0]) {
            n = 1;
        }
        if (n != 0) {
            mnNameNew_8023B224(0U);
            return;
        }
        {
            u8 cursor_pos = data->cursor_pos;
            cursor = cursor_pos;
        }
        if (null_char != (s8) name_text[cursor * 3]) {
            n = 1;
        } else {
            n = 0;
        }
        if (n != 0) {
            name_text[cursor * 3] = *((GlyphChar*) mnNameNew_NullCharacter);
            mnNameNew_8023CE4C();
            return;
        }
        if (cursor != 0) {
            name_text[(u8) (cursor - 1) * 3] =
                *((GlyphChar*) mnNameNew_NullCharacter);
            data->cursor_pos = (u8) (data->cursor_pos - 1);
            mnNameNew_8023CE4C();
            return;
        }
        lbAudioAx_80024030(3);
        return;
    }
    {
        u8 new_sel = mnNameNew_8023BAA8(data, (s32) buttons,
                                        (u8) mn_804A04F0.hovered_selection);
        if ((s32) new_sel != (s32) mn_804A04F0.hovered_selection) {
            lbAudioAx_80024030(2);
            mn_804A04F0.hovered_selection = (u16) new_sel;
            if (new_sel < 0x32) {
                data->last_key_sel = new_sel;
            }
        }
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

static inline NameNewEntry* mnNameNew_GetEntryData(void)
{
    return mnNameNew_804D6C08->user_data;
}

void mnNameNew_8023CE4C(void)
{
    Vec3 sp24;
    GXColor name_char_color;
    GXColor* name_char_color_ptr[1];
    NameNewEntry* data;
    HSD_JObj* jobj_a;
    HSD_JObj* jobj_b;
    HSD_Text* old_text;
    float y_minus;
    f32 char_spacing;
    f32 first_x;
    s32 i;
    HSD_Text* text;
    f32 z;

    data = mnNameNew_GetEntryData();
    jobj_a = data->jobjs[14];
    jobj_b = data->jobjs[15];
    first_x = HSD_JObjGetTranslationX(jobj_a);
    char_spacing = HSD_JObjGetTranslationX(jobj_b) - first_x;
    if (data->name_disp_text != 0L) {
        HSD_SisLib_803A5CC4(data->name_disp_text);
    }
    text = HSD_SisLib_803A6754(0, mn_804D6BB5);
    lb_8000B1CC(jobj_a, &mnNameNew_803EE330, &sp24);
    y_minus = -sp24.y;
    z = sp24.z;
    name_char_color_ptr[0] = &name_char_color;
    text->pos_x = sp24.x;
    i = 0;
    text->pos_y = y_minus;
    text->pos_z = z;
    text->font_size.x = 0.04f;
    text->font_size.y = 0.05f;
    text->text_color = mnNameNew_804D4F6C;
    for (; i < 4; i++) {
        if ((s8) *mnNameNew_NullCharacter ==
            (s8) mnNameNew_CurrentNameText[i * 3])
        {
            break;
        }
        HSD_SisLib_803A6B98(text, (char_spacing * (f32) i) / text->font_size.x,
                            0.0f, &mnNameNew_CurrentNameText[i * 3]);
        name_char_color = mnNameNew_804D4F78;
        HSD_SisLib_803A74F0(text, i, name_char_color_ptr[0]);
    }
    data->name_disp_text = text;
}

void fn_8023CFC8(HSD_GObj* arg0)
{
    HSD_JObj* jobj;
    HSD_JObj* root;
    u8 new_var;
    u8 old_sel;
    float one;
    s32 count;
    GlyphVariantEntry* data;
    u32 pad1;
    u32 pad2;
    GXColor sp30;
    GXColor sp2C;

    PAD_STACK(0x20);

    data = arg0->user_data;
    new_var = data->selection;
    old_sel = new_var;
    if (old_sel != mn_804A04F0.confirmed_selection) {
        root = data->jobjs[4];
        if (root == NULL) {
            jobj = NULL;
        } else {
            jobj = root->child;
        }
        for (count = old_sel; count > 0; count--) {
            if (jobj == NULL) {
                jobj = NULL;
            } else {
                jobj = jobj->next;
            }
        }
        root = jobj;
        HSD_JObjReqAnimAll(root, 0.0f);
        HSD_JObjAnimAll(root);
        sp30 = mnNameNew_804D4F74;
        HSD_SisLib_803A74F0(data->text, (s32) data->selection, &sp30);
        root = data->jobjs[4];
        new_var = mn_804A04F0.confirmed_selection;
        if (root == NULL) {
            jobj = NULL;
        } else {
            jobj = root->child;
        }
        for (count = (s32) new_var; count > 0; count--) {
            if (jobj == NULL) {
                jobj = NULL;
            } else {
                jobj = jobj->next;
            }
        }
        one = 1.0f;
        HSD_JObjReqAnimAll(jobj, one);
        HSD_JObjAnimAll(jobj);
        sp2C = mnNameNew_804D4F70;
        HSD_SisLib_803A74F0(data->text, (s32) mn_804A04F0.confirmed_selection,
                            &sp2C);
        data->selection = mn_804A04F0.confirmed_selection;
    }
}

void fn_8023D0F8(void* arg0)
{
    GlyphVariantEntry* entry = arg0;
    HSD_SisLib_803A5CC4(entry->text);
    HSD_Free(arg0);
}

s32 mnNameNew_8023D130(GlyphVariantEntry* arg0, u8 arg1, u8 arg2, s32 arg3)
{
    GXColor* glyph_color_ptr;
    char* str;
    f32 pos_z;
    f32 y_range;
    s32 i;
    MnNameNewDataLayout* layout;
    GXColor* color_ptr;
    f32 col_x;
    f32 pos_x;
    HSD_JObj* jobj14;
    HSD_JObj* jobj18;
    HSD_Text* text;
    HSD_JObj* jobj1C;
    f32 font_x;
    f32 x_range;
    char** table_upper;
    f32 pos_y;
    char** table_lower;
    Vec3 text_pos;
    GXColor glyph_color;

    layout = (MnNameNewDataLayout*) mnNameNew_803EDA58;
    text = HSD_SisLib_803A6754(0, (s32) mn_804D6BB4);
    jobj14 = arg0->jobjs[4];
    jobj18 = arg0->jobjs[5];
    jobj1C = arg0->jobjs[6];
    lb_8000B1CC(jobj14, &layout->x8CC, &text_pos);
    pos_x = text_pos.x;
    pos_y = -text_pos.y;
    pos_z = text_pos.z;
    text->pos_x = pos_x;
    text->pos_y = pos_y;
    text->pos_z = pos_z;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.04f;
    text->text_color = mnNameNew_804D4F6C;
    x_range =
        HSD_JObjGetTranslationX(jobj18) - HSD_JObjGetTranslationX(jobj14);
    y_range =
        -(HSD_JObjGetTranslationY(jobj1C) - HSD_JObjGetTranslationY(jobj14));
    table_upper =
        AddCharacterToName_getGlyphs(layout->upper_glyphs, (u8) arg3);
    table_lower =
        AddCharacterToName_getGlyphs(layout->lower_glyphs, (u8) arg3);
    (void) table_lower;
    for (i = 0; i < (u16) arg1; i++) {
        if ((u8) (arg3 - 0x30) <= 1U) {
            if ((i % 2) != 0) {
                str = table_upper[i / 2];
            } else {
                str = table_lower[i / 2];
            }
        } else if ((arg2 == 0 && (i % 2) == 0) || (arg2 == 1 && (i % 2) != 0))
        {
            str = table_lower[i / 2];
        } else {
            str = table_upper[i / 2];
        }
        font_x = text->font_size.x;
        col_x = (f32) (i / 2) * x_range;
        HSD_SisLib_803A6B98(text, col_x / font_x,
                            ((f32) (i % 2) * y_range) / text->font_size.y, str,
                            font_x, col_x);
        if (i == (s32) mn_804A04F0.confirmed_selection) {
            color_ptr = &mnNameNew_804D4F70;
        } else {
            color_ptr = &mnNameNew_804D4F74;
        }
        glyph_color = *color_ptr;
        glyph_color_ptr = &glyph_color;
        HSD_SisLib_803A74F0(text, i, glyph_color_ptr);
    }
    arg0->text = text;
    return (s32) text;
}

static const Vec3 mnNameNew_803B8528 = { -0.5f, 0.7f, 0.0f };

static inline void
mnNameNew_GlyphVariantSetup_InitJobjs(GlyphVariantEntry* user_data,
                                      HSD_JObj* jobj)
{
    s32 i;

    for (i = 0; i < 7; i++) {
        lb_80011E24(jobj, &user_data->jobjs[i], i, -1);
    }
}

s32 mnNameNew_GlyphVariantSetup(NameNewEntry* arg0, u16 arg1, u8 arg2)
{
    f32 base_y;
    MnNameNewDataLayout* layout;
    HSD_JObj* variant;
    HSD_JObj* key_jobj;
    HSD_JObj* ref_jobj;
    s32 i;
    HSD_JObj* ref3;
    GlyphVariantEntry* user_data;
    Vec3 sp38;
    Vec3 sp2C;
    f32 dx;
    f32 dy;
    f32 base_x;
    void** setup_desc;
    HSD_JObj* ref2;
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    void** variant_desc;

    layout = (MnNameNewDataLayout*) mnNameNew_803EDA58;
    setup_desc = mnNameNew_804A0710;
    gobj = GObj_Create(6U, 7U, 0x80U);
    jobj = HSD_JObjLoadJoint(setup_desc[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6U, 0x80U);
    HSD_GObj_SetupProc(gobj, fn_8023CFC8, 0U);
    HSD_JObjAddAnimAll(jobj, setup_desc[1], setup_desc[2], setup_desc[3]);
    HSD_JObjReqAnimAll(jobj, ((f32) (u8) arg1) / 2.0f);
    HSD_JObjAnimAll(jobj);

    user_data = HSD_MemAlloc(sizeof(GlyphVariantEntry));
    HSD_ASSERTREPORT(0x5B4, user_data, "Can't get user_data.\n");
    GObj_InitUserData(gobj, 0U, fn_8023D0F8, user_data);

    user_data->selection = mn_804A04F0.confirmed_selection;
    mnNameNew_GlyphVariantSetup_InitJobjs(user_data, jobj);

    sp2C = mnNameNew_803B8528;

    if (arg2 >= 0x32U && arg2 < 0x3AU) {
        key_jobj = (arg0->jobjs[layout->key_jobj_ids[arg2 - 0x32]]);
    } else {
        key_jobj = HSD_JObjGetChild(arg0->jobjs[16]);
        for (i = 0; i < 50; i++) {
            if (i == (s32) arg2) {
                break;
            }
            if (key_jobj == NULL) {
                key_jobj = NULL;
            } else {
                key_jobj = key_jobj->next;
            }
        }
    }

    lb_8000B1CC(key_jobj, &sp2C, &sp38);
    HSD_JObjSetTranslate(jobj, &sp38);

    ref_jobj = user_data->jobjs[4];
    ref2 = user_data->jobjs[5];
    ref3 = user_data->jobjs[6];

    base_x = HSD_JObjGetTranslationX(ref_jobj);
    dx = HSD_JObjGetTranslationX(ref2) - base_x;
    base_y = HSD_JObjGetTranslationY(ref_jobj);
    dy = HSD_JObjGetTranslationY(ref3) - base_y;

    variant_desc = mnNameNew_804A0720;
    i = 0;
    for (; i < (s32) (u8) arg1; i++) {
        variant = HSD_JObjLoadJoint(variant_desc[0]);
        HSD_JObjAddAnimAll(variant, variant_desc[1], variant_desc[2],
                           variant_desc[3]);
        HSD_JObjReqAnimAll(variant, (f32) (user_data->selection == i));
        HSD_JObjAnimAll(variant);
        HSD_JObjSetTranslateX(variant, dx * (f32) (i / 2));
        HSD_JObjSetTranslateY(variant, dy * (f32) (i % 2));
        HSD_JObjAddChild(ref_jobj, variant);
    }

    mnNameNew_8023D130(user_data, arg1, arg0->mode, arg2);
    return (s32) gobj;
}

s32 mnNameNew_8023DA08(NameNewEntry* arg0)
{
    AnimLoopSettings* anim;
    f32* end_frame;
    f32 frame;
    s32 all_anims_done;
    anim = mnNameNew_803EDA58;
    all_anims_done = 1;
    frame = mn_8022ED6C(arg0->jobjs[12], &anim[2]);
    end_frame = &anim[2].end_frame;
    if (frame < mnNameNew_803EDA58[2].end_frame) {
        all_anims_done = 0;
    }
    if (mn_8022ED6C(arg0->jobjs[13], &anim[2]) < *end_frame) {
        all_anims_done = 0;
    }
    frame = mn_8022EFD8(arg0->jobjs[4], anim);
    end_frame = &mnNameNew_803EDA58->end_frame;
    if (frame < mnNameNew_803EDA58->end_frame) {
        all_anims_done = 0;
    }
    if (mn_8022EFD8(arg0->jobjs[2], anim) < *end_frame) {
        all_anims_done = 0;
    }
    if (mn_8022EFD8(arg0->jobjs[6], anim) < *end_frame) {
        all_anims_done = 0;
    }
    return all_anims_done;
}

void fn_8023DAEC(HSD_GObj* arg0)
{
    s32 var_r30;
    NameNewEntry* data;
    MnNameNewDataLayout* layout;
    f32* end_frame;

    PAD_STACK(8);

    layout = (MnNameNewDataLayout*) mnNameNew_803EDA58;
    if ((data = arg0->user_data)->key_text != NULL) {
        HSD_SisLib_803A5CC4(data->key_text);
        data->key_text = NULL;
    }
    if (data->name_disp_text != NULL) {
        HSD_SisLib_803A5CC4(data->name_disp_text);
        data->name_disp_text = NULL;
    }
    if (data->desc_text != NULL) {
        HSD_SisLib_803A5CC4(data->desc_text);
        data->desc_text = NULL;
    }
    var_r30 = 1;
    if (mn_8022EFD8(data->jobjs[4], &layout->anim[1]) <
        *(end_frame = &layout->anim[1].end_frame))
    {
        var_r30 = 0;
    }
    if (mn_8022EFD8(data->jobjs[2], &layout->anim[1]) < *end_frame) {
        var_r30 = 0;
    }
    if (mn_8022EFD8(data->jobjs[6], &layout->anim[1]) < *end_frame) {
        var_r30 = 0;
    }
    if (var_r30 != 0 || mn_804A04F0.x10 == 1) {
        HSD_GObjPLink_80390228(arg0);
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void fn_8023DBE8(HSD_GObj* arg0)
{
    MenuFlow* flow;
    HSD_GObj* gobj;
    NameNewEntry* data;
    u16* hovered;
    u16 hovered_value;
    HSD_JObj* jobj;
    HSD_JObj* parent;
    HSD_GObjProc* proc;
    char unused[4];
    f32 frame;
    GXColor normal_key_color;
    GXColor highlighted_key_color;
    u8 cursor;
    u8 sel;
    s32 i;

    PAD_STACK(28);

    flow = &mn_804A04F0;
    gobj = arg0;
    data = gobj->user_data;

    if (flow->x10 != 1) {
        HSD_JObjSetFlagsAll(data->jobjs[16], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->jobjs[12], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->jobjs[13], JOBJ_HIDDEN);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8023DAEC, 0U);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }

    mnNameNew_8023DA08(data);
    cursor = data->x1;

    if ((s32) cursor != (s32) * (hovered = &flow->hovered_selection)) {
        if (cursor >= 0x32U && cursor < 0x3AU) {
            jobj = data->jobjs[mnNameNew_KeyMap.key_jobj_ids[cursor - 0x32]];
        } else {
            parent = data->jobjs[16];
            if (parent == NULL) {
                jobj = NULL;
            } else {
                jobj = parent->child;
            }
            for (i = 0; i < 50; i++) {
                if (i == (s32) cursor) {
                    break;
                }
                if (jobj == NULL) {
                    jobj = NULL;
                } else {
                    jobj = jobj->next;
                }
            }
        }
        frame = 0.0f;
        HSD_JObjReqAnimAll(jobj, frame);
        HSD_JObjAnimAll(jobj);
        if (data->x1 < 0x32U) {
            normal_key_color = mnNameNew_804D4F6C;
            HSD_SisLib_803A74F0(data->key_text, (s32) data->x1,
                                &normal_key_color);
        }

        sel = (u8) *hovered;
        if (sel >= 0x32U && sel < 0x3AU) {
            jobj = data->jobjs[mnNameNew_KeyMap.key_jobj_ids[sel - 0x32]];
        } else {
            parent = data->jobjs[16];
            if (parent == NULL) {
                jobj = NULL;
            } else {
                jobj = parent->child;
            }
            for (i = 0; i < 50; i++) {
                if (i == (s32) sel) {
                    break;
                }
                if (jobj == NULL) {
                    jobj = NULL;
                } else {
                    jobj = jobj->next;
                }
            }
        }
        frame = 1.0f;
        HSD_JObjReqAnimAll(jobj, frame);
        HSD_JObjAnimAll(jobj);
        hovered_value = *hovered;
        if (hovered_value < 0x32U) {
            highlighted_key_color = mnNameNew_804D4F68;
            HSD_SisLib_803A74F0(data->key_text, (s32) hovered_value,
                                &highlighted_key_color);
        }
        mnNameNew_8023B314(data, (s32) *hovered);
        data->x1 = (u8) *hovered;
        mnNameNew_8023B0F8(gobj, data->x1);
    }

    if ((mnNameNew_804D4C10 + (f32) data->cursor_pos) !=
        mn_8022F298(data->jobjs[13]))
    {
        cursor = data->cursor_pos;
        jobj = ((NameNewEntry*) gobj->user_data)->jobjs[13];
        HSD_JObjReqAnimAll(jobj, mnNameNew_804D4C10 + (f32) cursor);
        HSD_JObjAnimAll(jobj);
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

void mnNameNew_8023E0D8(NameNewEntry* arg0)
{
    MnNameNewDataLayout* layout;
    AnimLoopSettings* anim;
    HSD_JObj* jobj;
    u16* jobj_ids;
    s32 i;

    layout = (MnNameNewDataLayout*) mnNameNew_803EDA58;
    anim = layout->anim;
    jobj = arg0->jobjs[12];
    HSD_JObjReqAnim(jobj, anim[2].start_frame);
    HSD_JObjAnim(jobj);

    jobj = arg0->jobjs[13];
    HSD_JObjReqAnim(jobj, anim[2].start_frame);
    HSD_JObjAnim(jobj);

    jobj = arg0->jobjs[4];
    HSD_JObjReqAnim(jobj, anim[0].start_frame);
    HSD_JObjAnim(jobj);

    jobj = arg0->jobjs[5];
    HSD_JObjReqAnimAll(jobj, (f32) (arg0->x1 == 0x38));
    HSD_JObjAnimAll(jobj);

    jobj = arg0->jobjs[2];
    HSD_JObjReqAnim(jobj, anim[0].start_frame);
    HSD_JObjAnim(jobj);

    jobj = arg0->jobjs[5];
    HSD_JObjReqAnimAll(jobj, (f32) (arg0->x1 == 0x32));
    HSD_JObjAnimAll(jobj);

    jobj = arg0->jobjs[6];
    HSD_JObjReqAnim(jobj, anim[0].start_frame);
    HSD_JObjAnim(jobj);

    jobj_ids = layout->key_jobj_ids;
    for (i = 0x32; i < 0x3A; i++) {
        jobj = arg0->jobjs[jobj_ids[i - 0x32]];
        HSD_JObjReqAnimAll(jobj, (f32) (arg0->x1 == i));
        HSD_JObjAnimAll(jobj);
    }
}

s32 InitNameEntryUIState(NameNewEntry* arg0, s32 arg1)
{
    s32 result;
    s8 count;
    u8** names;
    s8 null_char;

    PAD_STACK(0x20);

    arg0->x1 = (count = (u8) mn_804A04F0.hovered_selection);
    result = lbLang_IsSavedLanguageUS();
    if (result) {
        arg0->mode = 2;
    } else {
        arg0->mode = 0;
    }
    count = 0;
    arg0->cursor_pos = 0;
    arg0->last_key_sel = arg0->x1;
    arg0->variant_gobj = 0;
    arg0->name_index = arg1;
    arg0->key_text = 0;
    arg0->name_disp_text = 0;
    arg0->desc_text = 0;
    null_char = (s8) *mnNameNew_NullCharacter;
    names = AutoNamesList;
    while (null_char != (s8) * *names) {
        names++;
        count++;
    }
    arg0->auto_history[0] = count;
    arg0->auto_history[1] = count;
    arg0->auto_history[2] = count;
    arg0->auto_history[3] = count;
    arg0->auto_history[4] = count;
    return result;
}

static inline void mnNameNew_InitKeyJobjs(NameNewEntry* user_data,
                                          HSD_JObj** child_out)
{
    s32 k;
    HSD_JObj* key_jobj;
    f32 x_range;
    f32 y_range;

    for (k = 0; k < 0x32; k++) {
        key_jobj = HSD_JObjLoadJoint(mnNameNew_804A0700[0]);
        HSD_JObjAddAnimAll(key_jobj, mnNameNew_804A0700[1],
                           mnNameNew_804A0700[2], mnNameNew_804A0700[3]);
        HSD_JObjReqAnimAll(key_jobj, (f32) ((u8) k == user_data->x1));
        HSD_JObjAnimAll(key_jobj);
        x_range = HSD_JObjGetTranslationX(user_data->jobjs[17]) -
                  HSD_JObjGetTranslationX(user_data->jobjs[16]);
        y_range = HSD_JObjGetTranslationY(user_data->jobjs[18]) -
                  HSD_JObjGetTranslationY(user_data->jobjs[16]);
        mnName_80239F5C(key_jobj, x_range * (f32) ((u8) k / 5));
        mnName_80239EBC(key_jobj, y_range * (f32) ((u8) k % 5));
        *child_out = key_jobj;
        HSD_JObjAddChild(user_data->jobjs[16], *child_out);
    }
}

void mnNameNew_8023E32C(s32 arg0)
{
    HSD_GObj* gobj;
    HSD_JObj* root_jobj;
    NameNewEntry* user_data;
    s32 i;
    void** setup_desc;

    PAD_STACK(8);

    setup_desc = mnNameNew_804A06F0;
    gobj = GObj_Create(6U, 7U, 0x80U);
    mnNameNew_804D6C08 = gobj;
    root_jobj = HSD_JObjLoadJoint(setup_desc[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, root_jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4U, 0x80U);
    HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_8023DBE8, 0U);
    HSD_JObjAddAnimAll(root_jobj, setup_desc[1], setup_desc[2], setup_desc[3]);
    HSD_JObjReqAnimAll(root_jobj, 0.0f);
    HSD_JObjAnimAll(root_jobj);
    user_data = HSD_MemAlloc(sizeof(*user_data));
    HSD_ASSERTREPORT(0x717U, user_data, "Can't get user_data.\n");
    GObj_InitUserData(gobj, 0U, HSD_Free, user_data);
    InitNameEntryUIState(user_data, arg0);
    for (i = 0; i < 0x13; i++) {
        lb_80011E24(root_jobj, &user_data->jobjs[i], i, -1);
    }
    mnNameNew_8023E0D8(user_data);
    {
        HSD_JObj* child;
        mnNameNew_InitKeyJobjs(user_data, &child);
    }
    user_data->key_text =
        (HSD_Text*) mnNameNew_KeySetup(user_data, user_data->mode);
    mnNameNew_8023B314(user_data, (s32) user_data->x1);
    mnNameNew_8023B0F8(gobj, user_data->x1);
}

void mnNameNew_EnterFromMnName(UNK_T arg0)
{
    char unused[8];
    char* text = mnNameNew_CurrentNameText;

    mn_804A04F0.x10 = 1;
    if (lbLang_IsSavedLanguageUS()) {
        mn_804A04F0.hovered_selection = 0x2d;
    } else {
        mn_804A04F0.hovered_selection = 0;
    }
    mnNameNew_PortInUse = 4;
    text[0] = *mnNameNew_NullCharacter;
    text[3] = *mnNameNew_NullCharacter;
    text[6] = *mnNameNew_NullCharacter;
    text[9] = *mnNameNew_NullCharacter;
    mnNameNew_8023E32C((s32) arg0);
}

void mnNameNew_EnterFromMnCharSel(HSD_Archive* arg0, s32 arg1)
{
    u8 name_count;
    HSD_GObjProc* proc;
    char* text;
    s32 is_us;

    PAD_STACK(16);

    text = mnNameNew_CurrentNameText;

    mn_804D6BC8.cooldown = 0x14;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
    mn_804A04F0.buttons = 0;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x12;

    if (lbLang_IsSavedLanguageUS()) {
        mn_804A04F0.hovered_selection = 0x2D;
    } else {
        mn_804A04F0.hovered_selection = 0;
    }

    mn_804A04F0.x10 = 1;
    HSD_SisLib_803A5E70();
    mnNameNew_PortInUse = arg1;

    lbArchive_LoadSections(
        arg0,

        // Background
        (void**) &MenMainBack_Top.joint, "MenMainBack_Top_joint",
        &MenMainBack_Top.animjoint, "MenMainBack_Top_animjoint",
        &MenMainBack_Top.matanim_joint, "MenMainBack_Top_matanim_joint",
        &MenMainBack_Top.shapeanim_joint, "MenMainBack_Top_shapeanim_joint",

        // Scene
        &MenMain_cam, "ScMenMain_cam_int1_camera", &MenMain_lights,
        "ScMenMain_scene_lights", &MenMain_fog, "ScMenMain_fog",

        // Panel
        &MenMainPanel_Top.joint, "MenMainPanel_Top_joint",
        &MenMainPanel_Top.animjoint, "MenMainPanel_Top_animjoint",
        &MenMainPanel_Top.matanim_joint, "MenMainPanel_Top_matanim_joint",
        &MenMainPanel_Top.shapeanim_joint, "MenMainPanel_Top_shapeanim_joint",

        // Row 1
        &mnNameNew_804A06F0[0], "MenMainConEtNw_Top_joint",
        &mnNameNew_804A06F0[1], "MenMainConEtNw_Top_animjoint",
        &mnNameNew_804A06F0[2], "MenMainConEtNw_Top_matanim_joint",
        &mnNameNew_804A06F0[3], "MenMainConEtNw_Top_shapeanim_joint",

        // Row 2
        &mnNameNew_804A0700[0], "MenMainBaseEtNw_Top_joint",
        &mnNameNew_804A0700[1], "MenMainBaseEtNw_Top_animjoint",
        &mnNameNew_804A0700[2], "MenMainBaseEtNw_Top_matanim_joint",
        &mnNameNew_804A0700[3], "MenMainBaseEtNw_Top_shapeanim_joint",

        // Row 3
        &mnNameNew_804A0710[0], "MenMainSubEtNw_Top_joint",
        &mnNameNew_804A0710[1], "MenMainSubEtNw_Top_animjoint",
        &mnNameNew_804A0710[2], "MenMainSubEtNw_Top_matanim_joint",
        &mnNameNew_804A0710[3], "MenMainSubEtNw_Top_shapeanim_joint",

        // Row 4
        &mnNameNew_804A0720[0], "MenMainSbaseEtNw_Top_joint",
        &mnNameNew_804A0720[1], "MenMainSbaseEtNw_Top_animjoint",
        &mnNameNew_804A0720[2], "MenMainSbaseEtNw_Top_matanim_joint",
        &mnNameNew_804A0720[3], "MenMainSbaseEtNw_Top_shapeanim_joint",

        NULL);

    is_us = lbLang_IsSavedLanguageUS();

    if (is_us) {
        lbArchive_LoadSections(arg0, (void**) &AutoNamesList,
                               "mnNameAutoNameUs", &NotAllowedNamesList,
                               "mnNameRefuseNameUs", NULL);
    } else {
        lbArchive_LoadSections(arg0, (void**) &AutoNamesList, "mnNameAutoName",
                               &NotAllowedNamesList, "mnNameRefuseName", NULL);
    }

    mn_8022C304();
    mn_8022BCF8();
    mn_8022BEDC(mn_8022BE34());
    mn_80229B2C();
    mn_80229DC0();

    name_count = (u8) GetNameCount();

    proc = HSD_GObj_SetupProc(GObj_Create(0U, 1U, 0x80U),
                              (HSD_GObjEvent) mnNameNew_MainInput, 0U);
    proc->flags_3 = HSD_GObj_804D783C;

    text[0] = *mnNameNew_NullCharacter;
    text[3] = *mnNameNew_NullCharacter;
    text[6] = *mnNameNew_NullCharacter;
    text[9] = *mnNameNew_NullCharacter;

    mnNameNew_8023E32C((s32) name_count);
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

void mnNameNew_8023EA08(UNK_T arg0)
{
    mnNameNew_EnterFromMnCharSel((HSD_Archive*) arg0, 4);
}

char mnNameNew_CurrentNameText[0x10];
void* mnNameNew_804A0720[8];
void* mnNameNew_804A0710[4];
void* mnNameNew_804A0700[4];
void* mnNameNew_804A06F0[4];

static u8 mnNameNew_804D4F98[8] = { 0 };

char* mnNameNew_803EE720[] = { (char*) mnNameNew_804D4F98 };
char* mnNameNew_803EE724[] = { (char*) mnNameNew_804D4F98 };
