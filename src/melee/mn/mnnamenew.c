#include "mnnamenew.h"

#include "gm/gm_18A5.h"
#include "gm/gm_1A3F.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "mn/mncharsel.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "mn/types.h"

#include <dolphin/os.h>
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

extern volatile char mnNameNew_NullCharacter;
extern u8 mnNameNew_PortInUse;
extern char mnNameNew_CurrentNameText[0x10];
extern u8** AutoNamesList;
extern char** NotAllowedNamesList;
extern u8 mn_804D6BB4;
extern u8 mn_804D6BB5;
extern u8 mnNameNew_804D4F7C[4];
extern void* mnNameNew_804D6C08;
extern u8 mnNameNew_SpaceCharacter[2];
extern char* mnNameNew_803EDCE4[];
extern void* mnNameNew_804A06F0[];
extern void* mnNameNew_804A0700[];
extern void* mnNameNew_804A0710[];
extern void* mnNameNew_804A0720[];

extern u16 mnNameNew_803EDA7C[];
extern StaticModelDesc MenMainBack_Top;
extern StaticModelDesc MenMainPanel_Top;
extern HSD_CObjDesc* MenMain_cam;
extern UNK_T MenMain_lights;
extern HSD_FogDesc* MenMain_fog;

extern char** mnNameNew_803EDA8C[];
extern char** mnNameNew_803EDB54[];
extern char** mnNameNew_803EDC1C[];
extern Vec3 mnNameNew_803EE324;

/// Row of 4 glyph character pointers for a single key position.
typedef struct GlyphRow {
    char* glyphs[4];
} GlyphRow;

/// Large static data block starting at mnNameNew_803EDA58.
/// Contains animation settings, glyph lookup tables, etc.
typedef struct NameNewData {
    /* 0x000 */ AnimLoopSettings anim[3];
    /* 0x024 */ u16 key_counts[8];
    /* 0x034 */ char* glyph_set_a[50];
    /* 0x0FC */ char* glyph_set_b[50];
    /* 0x1C4 */ char* glyph_single[50];
    /* 0x28C */ GlyphRow glyph_lower[50];
    /* 0x5AC */ GlyphRow glyph_upper[50];
    /* 0x8CC */ Vec3 ref_pos;
} NameNewData;

static AnimLoopSettings mnNameNew_803EDA58[3] = {
    { 0.0f, 19.0f, -0.1f },
    { 20.0f, 39.0f, -0.1f },
    { 0.0f, 10.0f, -0.1f },
};

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

    temp_r31 = ((HSD_GObj*) mnNameNew_804D6C08)->user_data;
    temp_r30 = temp_r31->name_index;
    if (arg0 != 0) {
        lb_8001CE00();
    }
    if (gm_801A4310() == 0x1B) {
        HSD_SisLib_803A5E70();
        mn_8022EBDC();
        if (arg0 != 0) {
            gm_80190FE4((s32) temp_r30);
            return;
        }
        gm_80190FE4(0x78);
        return;
    }
    if (gm_801A4310() == 1) {
        mn_804D6BC8.cooldown = 5;
        if (arg0 != 0 && GetNameCount() > 0x18) {
            mnName_8023A9B4((u8)(temp_r31->name_index / 6));
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


static GXColor mnNameNew_804D4F6C = { 0xA6, 0x81, 0x3D, 0xFF };
static s32 mnNameNew_804D4F70 = 0xFF;
static s32 mnNameNew_804D4F74 = 0x744F0BFF;
static s32 mnNameNew_804D4F78 = 0xFF;

extern const s32 mnNameNew_804DBF44;
extern const s32 mnNameNew_804DBF48;

s32 mnNameNew_KeySetup(NameNewEntry* arg0, u8 arg1)
{
    HSD_JObj* key_jobj;
    HSD_JObj* ref1;
    HSD_JObj* ref2;
    HSD_Text* text;
    Vec3 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    char** str_table;
    f32 x_range;
    f32 y_range;
    f32 base_x;
    f32 base_y;
    f32 font_x;
    f32 col_x;
    s32 i;
    s32* color_ptr;
    NameNewData* ndata;

    FORCE_PAD_STACK(20);

    sp4C = mnNameNew_804DBF44;
    sp48 = mnNameNew_804DBF48;
    ndata = (NameNewData*) mnNameNew_803EDA58;

    switch ((s32) arg1) {
    case 0:
        arg0->mode = 0;
        str_table = ndata->glyph_set_a;
        break;
    case 1:
        arg0->mode = 1;
        str_table = ndata->glyph_set_b;
        break;
    case 2:
        arg0->mode = 2;
        str_table = ndata->glyph_single;
        break;
    }

    text = arg0->key_text;
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
    }
    text = HSD_SisLib_803A6754(0, (s32) mn_804D6BB5);
    arg0->key_text = text;

    key_jobj = HSD_JObjGetChild(arg0->jobjs[16]);
    for (i = 0; i < 50; i++) {
        if (i == 0x2D) break;
        key_jobj = HSD_JObjGetNext(key_jobj);
    }

    lb_8000B1CC(key_jobj, &mnNameNew_803EE324, &sp50);
    text->pos_x = sp50.x;
    text->pos_y = -sp50.y;
    text->pos_z = sp50.z;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.04f;
    text->text_color = mnNameNew_804D4F6C;

    ref1 = HSD_JObjGetChild(arg0->jobjs[16]);
    for (i = 0; i < 50; i++) {
        if (i == 0x28) break;
        ref1 = HSD_JObjGetNext(ref1);
    }

    base_x = HSD_JObjGetTranslationX(key_jobj);
    x_range = HSD_JObjGetTranslationX(ref1) - base_x;

    ref2 = HSD_JObjGetChild(arg0->jobjs[16]);
    for (i = 0; i < 50; i++) {
        if (i == 0x2E) break;
        ref2 = HSD_JObjGetNext(ref2);
    }

    base_y = HSD_JObjGetTranslationY(key_jobj);
    y_range = -(HSD_JObjGetTranslationY(ref2) - base_y);

    {
        u8* sp44_addr = (u8*) &sp44;
        i = 0;
        for (; i < 0x32; i++) {
            font_x = text->font_size.x;
            col_x = (f32)(9 - (i / 5)) * x_range;
            HSD_SisLib_803A6B98(text, col_x / font_x,
                                ((f32)(i % 5) * y_range) / text->font_size.y,
                                str_table[i], font_x, col_x);
            if (i == (s32) mn_804A04F0.hovered_selection) {
                color_ptr = &sp48;
            } else {
                color_ptr = &sp4C;
            }
            sp44 = *color_ptr;
            HSD_SisLib_803A74F0(text, i, sp44_addr);
        }
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
            if ((s32)(arg2 % 5) == 4) {
                return 0x39;
            }
            return arg2 + 1;
        }
        if (arg1 & 4) {
            if ((s32)(arg2 / 5) < 9) {
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


s32 PickAutoName(HSD_GObj* arg0)
{
    NameNewEntry* data;
    u8* cur_text;
    u8* text;
    u8** names;
    u8** name_ptr;
    s32 count;
    s32 pick;
    s32 dup;
    s32 char_idx;
    s32 name_idx;
    u8 ch;
    u8 tmp;
    s8 null_ch;

    PAD_STACK(48);

    data = arg0->user_data;
    cur_text = (u8*) mnNameNew_CurrentNameText;

    do {
        dup = 0;
        do {
            null_ch = (s8) mnNameNew_NullCharacter;
            count = 0;
            names = AutoNamesList;
            while (null_ch != (s8) **names) {
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

    name_idx = 0;
    char_idx = name_idx;
    cur_text[0] = mnNameNew_NullCharacter;
    text = cur_text;
    cur_text[3] = mnNameNew_NullCharacter;
    cur_text[6] = mnNameNew_NullCharacter;
    cur_text[9] = mnNameNew_NullCharacter;

    name_ptr = &AutoNamesList[pick];
    while ((s8) mnNameNew_NullCharacter != (s8)(ch = (*name_ptr)[char_idx])) {
        text[0] = ch;
        text[1] = (*name_ptr)[char_idx + 1];
        text[2] = mnNameNew_NullCharacter;
        char_idx += 2;
        name_idx++;
        text += 3;
    }

    cur_text[name_idx * 3] = mnNameNew_NullCharacter;

    tmp = data->auto_history[0];
    data->auto_history[0] = (u8) pick;
    ch = data->auto_history[1];
    data->auto_history[1] = tmp;
    tmp = data->auto_history[2];
    data->auto_history[2] = ch;
    ch = data->auto_history[3];
    data->auto_history[3] = tmp;
    data->auto_history[4] = ch;

    return (s32)(s8) mnNameNew_NullCharacter;
}

s32 NameContainsOnlySpaces(void)
{
    u8* text = (u8*) mnNameNew_CurrentNameText;
    s8 null_char = (s8) mnNameNew_NullCharacter;
    s8 space0 = (s8) mnNameNew_SpaceCharacter[0];
    u8* sp = mnNameNew_SpaceCharacter;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (null_char != (s8) text[0]) {
            if (space0 != (s8) text[0] ||
                (s8) sp[1] != (s8) text[1])
            {
                return 0;
            }
        }
        text += 3;
    }
    return 1;
}


s32 WriteCharactersForNameAtIndex(u8 arg0, s32 arg1)
{
    s32 idx;
    struct NameTagData* nametag;
    u8 ch;
    u8* text;
    u8* ptr;
    s32 ret;

    nametag = GetPersistentNameData((s32) arg0);
    text = (u8*) mnNameNew_CurrentNameText;
    idx = 0;
    if ((s8) mnNameNew_NullCharacter != (s8) *text) {
        ptr = text;
        while ((s8) mnNameNew_NullCharacter != (s8) (ch = *ptr)) {
            nametag->namedata[idx] = (s8) ch;
            idx += 1;
            ptr += 1;
        }
        if ((s8) ch != (s8) *(text += 3)) {
            ptr = text;
            while ((s8) mnNameNew_NullCharacter != (s8) (ch = *ptr)) {
                nametag->namedata[idx] = (s8) ch;
                idx += 1;
                ptr += 1;
            }
            if ((s8) ch != (s8) *(text += 3)) {
                ptr = text;
                while ((s8) mnNameNew_NullCharacter != (s8) (ch = *ptr)) {
                    nametag->namedata[idx] = (s8) ch;
                    idx += 1;
                    ptr += 1;
                }
                if ((s8) ch != (s8) *(text += 3)) {
                    ptr = text;
                    while ((s8) mnNameNew_NullCharacter !=
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
    nametag->namedata[idx] = (s8) mnNameNew_NullCharacter;
    ret = GetRumbleSettingOfPort(arg1);
    nametag->x1A1 = ret;
    return ret;
}


s32 AddCharacterToName(u8* arg0, s32 arg1, u8 arg2, u8 arg3)
{
    s32 idx;
    u8 ch;
    u8* var_r4;
    char** table;
    NameNewData* data;

    data = (NameNewData*) mnNameNew_803EDA58;

    if ((s32) arg3 != 2) {
        if ((s32) arg3 < 2 && (s32) arg3 >= 0) {
            if ((u8) (arg1 - 0x30) <= 1U) {
                if ((arg2 % 2) != 0) {
                    table = data->glyph_upper[(u8) arg1].glyphs;
                } else {
                    table = data->glyph_lower[(u8) arg1].glyphs;
                }
            } else if ((arg3 == 0 && (arg2 % 2) == 0) ||
                       (arg3 == 1 && (arg2 % 2) != 0))
            {
                table = data->glyph_lower[(u8) arg1].glyphs;
            } else {
                table = data->glyph_upper[(u8) arg1].glyphs;
            }
            var_r4 = arg0;
            idx = 0;
            while ((s8) mnNameNew_NullCharacter !=
                   (s8) (ch = (u8) table[arg2 / 2][idx]))
            {
                *var_r4 = ch;
                idx += 1;
                var_r4 += 1;
            }
            arg0[idx] = mnNameNew_NullCharacter;
            return (s32) arg0;
        }
        return (s32) arg0;
    }
    arg0[0] = (u8) data->glyph_single[(u8) arg1][0];
    arg0[1] = (u8) data->glyph_single[(u8) arg1][1];
    arg0[2] = (u8) data->glyph_single[(u8) arg1][2];
    return (s32) arg0;
}


void mnNameNew_GlyphVariantInput(void)
{
    NameNewEntry* data;
    u32 buttons;
    s32 count;
    u16 old_hover;
    u8 old_sel;
    u8 cur_pos;
    char** table;
    s32 total;
    s8 null_ch;

    PAD_STACK(16);

    data = ((HSD_GObj*) mnNameNew_804D6C08)->user_data;
    buttons = mn_80229624((u32) mnNameNew_PortInUse);
    mn_804A04F0.buttons = buttons;
    count = 0;
    if (buttons & 0x200) {
        HSD_GObjPLink_80390228(data->variant_gobj);
        data->variant_gobj = NULL;
        AddCharacterToName((u8*) &mnNameNew_CurrentNameText[data->cursor_pos * 3],
                           (s32)(u8) mn_804A04F0.hovered_selection,
                           mn_804A04F0.confirmed_selection,
                           data->mode);
        lbAudioAx_80024030(1);
        cur_pos = data->cursor_pos;
        old_hover = mn_804A04F0.hovered_selection;
        count = (s32) old_hover;
        if (cur_pos < 3U) {
            data->cursor_pos = (u8)(cur_pos + 1);
        } else {
            mn_804A04F0.hovered_selection = 0x39;
        }
        mnNameNew_8023CE4C();
        if (((count != 0x30) && (count != 0x31)) && ((mn_804A04F0.confirmed_selection % 2) != 0))
        {
            if (data->mode == 0) {
                data->mode = 1;
            } else {
                data->mode = 0;
            }
            mnNameNew_KeySetup(data, data->mode);
            mnNameNew_8023B0F8((HSD_GObj*) mnNameNew_804D6C08,
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
        null_ch = (s8) mnNameNew_NullCharacter;
        table = &mnNameNew_803EDCE4[data->x1 * 4];
        while (null_ch != (s8) **table) {
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
                    (mn_804A04F0.confirmed_selection % 2) + ((total / 2 - 1) * 2);
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
        if (old_sel != (u8) mn_804A04F0.confirmed_selection) {
            lbAudioAx_80024030(2);
        }
    }
}


void mnNameNew_MainInput(HSD_GObj* arg0)
{
    u8 sp24[16];
    NameNewEntry* data;
    char* name_text;
    u32 buttons;
    s32 var_r29;
    s32 key_off;
    u8* key_char;
    s8 null_char;
    u8* src;
    u8* dest;
    s32 len;
    u8 cursor;
    s32 n;

    PAD_STACK(24);

    name_text = mnNameNew_CurrentNameText;
    data = ((HSD_GObj*) mnNameNew_804D6C08)->user_data;

    if (data->variant_gobj != NULL) {
        mnNameNew_GlyphVariantInput();
        return;
    }

    buttons = mn_80229624((u32) mnNameNew_PortInUse);
    *(u32*)((u8*)&mn_804A04F0 + 0xC) = buttons;
    var_r29 = 0;
    *(u32*)((u8*)&mn_804A04F0 + 0x8) = 0;

    if (buttons & 0x200) {
        u16 sel = mn_804A04F0.hovered_selection;
        if (sel < 0x32U) {
            if (data->mode != 2 && sel < 0x32U)
            {
                key_off = (((u8) sel) << 4) & 0xFF0;
                key_char = *(u8**)((u8*) mnNameNew_803EDCE4 + key_off);
                if ((s8) mnNameNew_SpaceCharacter[0] == (s8) key_char[0] &&
                    (s8) mnNameNew_SpaceCharacter[1] == (s8) key_char[1])
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
                        u8** ptrs = (u8**)((u8*) mnNameNew_803EDCE4 + ((((u8) sel2) << 4) & 0xFF0));
                        null_char = (s8) mnNameNew_NullCharacter;
                        while (null_char != (s8) *ptrs[0]) {
                            ptrs++;
                            n++;
                        }
                    }
                    data->variant_gobj = (HSD_GObj*) mnNameNew_GlyphVariantSetup(
                        (u8*) data, (u8)((n * 2) & 0xFE),
                        (u8) mn_804A04F0.hovered_selection);
                    return;
                }
                cursor = data->cursor_pos;
                name_text[cursor * 3] = (char) mnNameNew_SpaceCharacter[0];
                name_text[cursor * 3 + 1] = (char) mnNameNew_SpaceCharacter[1];
                name_text[cursor * 3 + 2] = (char) mnNameNew_NullCharacter;
                lbAudioAx_80024030(1);
                if (data->cursor_pos < 3) {
                    data->cursor_pos = (u8)(data->cursor_pos + 1);
                } else {
                    mn_804A04F0.hovered_selection = 0x39;
                }
                mnNameNew_8023CE4C();
                return;
            }
            AddCharacterToName(
                (u8*) &name_text[data->cursor_pos * 3],
                (s32)(u8) mn_804A04F0.hovered_selection,
                0U, data->mode);
            lbAudioAx_80024030(1);
            if (data->cursor_pos < 3) {
                data->cursor_pos = (u8)(data->cursor_pos + 1);
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
                    mnNameNew_8023B0F8((HSD_GObj*) mnNameNew_804D6C08,
                                       (u8) mn_804A04F0.hovered_selection);
                    return;
                }
                break;

            case 0x34:
                if (data->mode != 1) {
                    lbAudioAx_80024030(1);
                    data->mode = 1;
                    mnNameNew_KeySetup(data, 1);
                    mnNameNew_8023B0F8((HSD_GObj*) mnNameNew_804D6C08,
                                       (u8) mn_804A04F0.hovered_selection);
                    return;
                }
                break;

            case 0x35:
                if (data->mode != 2) {
                    lbAudioAx_80024030(1);
                    data->mode = 2;
                    mnNameNew_KeySetup(data, 2);
                    mnNameNew_8023B0F8((HSD_GObj*) mnNameNew_804D6C08,
                                       (u8) mn_804A04F0.hovered_selection);
                    return;
                }
                break;

            case 0x36:
                lbAudioAx_80024030(0);
                cursor = data->cursor_pos;
                {
                    char* slot = &name_text[cursor * 3];
                    if ((s8) mnNameNew_NullCharacter != (s8) slot[0]) {
                        var_r29 = 1;
                    }
                    if (var_r29 != 0) {
                        slot[0] = (char) mnNameNew_NullCharacter;
                        mnNameNew_8023CE4C();
                        return;
                    }
                }
                if (cursor != 0) {
                    name_text[(u8)(cursor - 1) * 3] =
                        (char) mnNameNew_NullCharacter;
                    data->cursor_pos = (u8)(data->cursor_pos - 1);
                    mnNameNew_8023CE4C();
                    return;
                }
                lbAudioAx_80024030(3);
                return;

            case 0x37:
                lbAudioAx_80024030(1);
                PickAutoName((HSD_GObj*) mnNameNew_804D6C08);
                null_char = (s8) mnNameNew_NullCharacter;
                {
                    char* p = name_text;
                    if (null_char != (s8) *p) {
                        var_r29 = 1;
                        p += 3;
                        if (null_char != (s8) *p) {
                            var_r29 = 2;
                            p += 3;
                            if (null_char != (s8) *p) {
                                var_r29 = 3;
                                p += 3;
                                if (null_char != (s8) *p) {
                                    var_r29 = 4;
                                }
                            }
                        }
                    }
                }
                if (var_r29 == 4) {
                    data->cursor_pos = 3;
                } else {
                    data->cursor_pos = (u8) var_r29;
                }
                mnNameNew_8023CE4C();
                return;

            case 0x38:
            case 0x39:
                dest = sp24;
                len = 0;

                for (src = (u8*) name_text;
                     (s8) mnNameNew_NullCharacter != (s8) *src;
                     src++, dest++, len++) {
                    *dest = *src;
                }

                for (src = (u8*) name_text + 3;
                     (s8) mnNameNew_NullCharacter != (s8) *src;
                     src++, dest++, len++) {
                    *dest = *src;
                }

                for (src = (u8*) name_text + 6;
                     (s8) mnNameNew_NullCharacter != (s8) *src;
                     src++, dest++, len++) {
                    *dest = *src;
                }

                for (src = (u8*) name_text + 9;
                     (s8) mnNameNew_NullCharacter != (s8) *src;
                     src++, dest++, len++) {
                    *dest = *src;
                }

                null_char = (s8) mnNameNew_NullCharacter;
                sp24[len] = (u8) null_char;

                if ((s8) name_text[0] == null_char) {
                    n = 1;
                } else {
                    n = 0;
                }
                if (n == 0 && NameContainsOnlySpaces() == 0 &&
                    IsNameUnique((char*) sp24) == 0 &&
                    IsNameNotAllowed((char*) sp24) == 0)
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
        }
    } else {
        if (buttons & 0x100) {
            if ((u16) mn_804A04F0.hovered_selection == 0x38 ||
                (u16) mn_804A04F0.hovered_selection == 0x39)
            {
                dest = sp24;
                len = 0;

                for (src = (u8*) name_text;
                     (s8) mnNameNew_NullCharacter != (s8) *src;
                     src++, dest++, len++) {
                    *dest = *src;
                }

                for (src = (u8*) name_text + 3;
                     (s8) mnNameNew_NullCharacter != (s8) *src;
                     src++, dest++, len++) {
                    *dest = *src;
                }

                for (src = (u8*) name_text + 6;
                     (s8) mnNameNew_NullCharacter != (s8) *src;
                     src++, dest++, len++) {
                    *dest = *src;
                }

                for (src = (u8*) name_text + 9;
                     (s8) mnNameNew_NullCharacter != (s8) *src;
                     src++, dest++, len++) {
                    *dest = *src;
                }

                null_char = (s8) mnNameNew_NullCharacter;
                sp24[len] = (u8) null_char;

                if ((s8) name_text[0] == null_char) {
                    n = 1;
                } else {
                    n = 0;
                }
                if (n == 0 && NameContainsOnlySpaces() == 0 &&
                    IsNameUnique((char*) sp24) == 0 &&
                    IsNameNotAllowed((char*) sp24) == 0)
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
                if (data->mode != 0) {
                    data->mode = (u8)(data->mode - 1);
                } else {
                    data->mode = 2;
                }
            } else {
                if (data->mode < 2) {
                    data->mode = (u8)(data->mode + 1);
                } else {
                    data->mode = 0;
                }
            }
            mnNameNew_KeySetup(data, data->mode);
            mnNameNew_8023B0F8((HSD_GObj*) mnNameNew_804D6C08,
                               (u8) mn_804A04F0.hovered_selection);
            mnNameNew_8023B314(data, (s32) mn_804A04F0.hovered_selection);
            return;
        }
        if (buttons & 0x20) {
            lbAudioAx_80024030(0);
            null_char = (s8) mnNameNew_NullCharacter;
            if ((s8) name_text[0] == null_char) {
                var_r29 = 1;
            }
            if (var_r29 != 0) {
                mnNameNew_8023B224(0U);
                return;
            }
            cursor = data->cursor_pos;
            if (null_char != (s8) name_text[cursor * 3]) {
                n = 1;
            } else {
                n = 0;
            }
            if (n != 0) {
                name_text[cursor * 3] = (char) mnNameNew_NullCharacter;
                mnNameNew_8023CE4C();
                return;
            }
            if (cursor != 0) {
                name_text[(u8)(cursor - 1) * 3] =
                    (char) mnNameNew_NullCharacter;
                data->cursor_pos = (u8)(data->cursor_pos - 1);
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
}


void mnNameNew_8023CE4C(void)
{
    Vec3 sp24;
    s32 sp20;
    HSD_JObj* jobj_a;
    HSD_JObj* jobj_b;
    HSD_Text* text;
    HSD_Text* old_text;
    f32 char_spacing;
    f32 first_x;
    NameNewEntry* data;
    u8* name_ptr;
    u8* sp20_ptr;
    s32 i;

    PAD_STACK(8);

    data = ((HSD_GObj*) mnNameNew_804D6C08)->user_data;
    jobj_a = data->jobjs[14];
    jobj_b = data->jobjs[15];
    first_x = HSD_JObjGetTranslationX(jobj_a);
    char_spacing = HSD_JObjGetTranslationX(jobj_b) - first_x;
    old_text = data->name_disp_text;
    if (old_text != NULL) {
        HSD_SisLib_803A5CC4(old_text);
    }
    text = HSD_SisLib_803A6754(0, (s32) mn_804D6BB5);
    lb_8000B1CC(jobj_a, &mnNameNew_803EE330, &sp24);
    name_ptr = (u8*) &mnNameNew_CurrentNameText;
    text->pos_x = sp24.x;
    text->pos_y = -sp24.y;
    text->pos_z = sp24.z;
    text->font_size.x = 0.04f;
    text->font_size.y = 0.05f;
    text->text_color = mnNameNew_804D4F6C;
    sp20_ptr = (u8*) &sp20;
    i = 0;
    for (; i < 4; i++) {
        if ((s8) mnNameNew_NullCharacter == (s8) *name_ptr) {
            break;
        }
        HSD_SisLib_803A6B98(text,
                            (char_spacing * (f32) i) / text->font_size.x,
                            0.0f, (const char*) name_ptr);
        sp20 = mnNameNew_804D4F78;
        HSD_SisLib_803A74F0(text, i, sp20_ptr);
        name_ptr += 3;
    }
    data->name_disp_text = text;
}


void fn_8023CFC8(HSD_GObj* arg0)
{
    s32 sp30;
    s32 sp2C;
    HSD_JObj* jobj;
    HSD_JObj* root;
    u8 old_sel;
    s32 count;
    GlyphVariantEntry* data;

    PAD_STACK(40);

    data = arg0->user_data;
    old_sel = data->selection;
    if (old_sel != (u8) mn_804A04F0.confirmed_selection) {
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
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        sp30 = mnNameNew_804D4F74;
        HSD_SisLib_803A74F0(data->text, (s32) data->selection,
                            (u8*) &sp30);
        root = data->jobjs[4];
        if (root == NULL) {
            jobj = NULL;
        } else {
            jobj = root->child;
        }
        for (count = (s32) mn_804A04F0.confirmed_selection; count > 0;
             count--)
        {
            if (jobj == NULL) {
                jobj = NULL;
            } else {
                jobj = jobj->next;
            }
        }
        HSD_JObjReqAnimAll(jobj, 1.0f);
        HSD_JObjAnimAll(jobj);
        sp2C = mnNameNew_804D4F70;
        HSD_SisLib_803A74F0(data->text,
                            (s32) mn_804A04F0.confirmed_selection,
                            (u8*) &sp2C);
        data->selection = (u8) mn_804A04F0.confirmed_selection;
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
    Vec3 sp30;
    s32 sp2C;
    HSD_JObj* jobj14;
    HSD_JObj* jobj18;
    HSD_JObj* jobj1C;
    HSD_Text* text;
    s32 i;
    char* str;
    s32* color_ptr;
    f32 x_range;
    f32 y_range;
    f32 font_x;
    f32 col_x;
    s32 temp;
    GlyphRow* table_upper;
    GlyphRow* table_lower;
    NameNewData* ndata;
    u8* sp2C_ptr;

    PAD_STACK(8);

    ndata = (NameNewData*) mnNameNew_803EDA58;
    jobj14 = arg0->jobjs[4];
    text = HSD_SisLib_803A6754(0, (s32) mn_804D6BB4);
    jobj18 = arg0->jobjs[5];
    jobj1C = arg0->jobjs[6];
    lb_8000B1CC(jobj14, &ndata->ref_pos, &sp30);
    text->pos_x = sp30.x;
    text->pos_y = -sp30.y;
    text->pos_z = sp30.z;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.04f;
    text->text_color = mnNameNew_804D4F6C;
    x_range = HSD_JObjGetTranslationX(jobj18) - HSD_JObjGetTranslationX(jobj14);
    y_range = -(HSD_JObjGetTranslationY(jobj1C) - HSD_JObjGetTranslationY(jobj14));
    temp = (arg3 * 0x10) & 0xFF0;
    table_upper = (GlyphRow*) ((u8*) ndata + temp + 0x5AC);
    table_lower = (GlyphRow*) ((u8*) ndata + temp + 0x28C);
    sp2C_ptr = (u8*) &sp2C;
    for (i = 0; i < (s32) arg1; i++) {
        if ((u8)(arg3 - 0x30) <= 1U) {
            if ((i % 2) != 0) {
                str = table_upper->glyphs[i / 2];
            } else {
                str = table_lower->glyphs[i / 2];
            }
        } else if ((arg2 == 0 && (i % 2) == 0) ||
                   (arg2 == 1 && (i % 2) != 0))
        {
            str = table_lower->glyphs[i / 2];
        } else {
            str = table_upper->glyphs[i / 2];
        }
        font_x = text->font_size.x;
        col_x = (f32)(i / 2) * x_range;
        HSD_SisLib_803A6B98(text, col_x / font_x,
                            ((f32)(i % 2) * y_range) / text->font_size.y,
                            str, font_x, col_x);
        if (i == (s32) mn_804A04F0.confirmed_selection) {
            color_ptr = &mnNameNew_804D4F70;
        } else {
            color_ptr = &mnNameNew_804D4F74;
        }
        sp2C = *color_ptr;
        HSD_SisLib_803A74F0(text, i, sp2C_ptr);
    }
    arg0->text = text;
    return (s32) text;
}


extern const Vec3 mnNameNew_803B8528;

s32 mnNameNew_GlyphVariantSetup(u8* arg0, u8 arg1, u8 arg2)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* variant;
    HSD_JObj* key_jobj;
    HSD_JObj* ref_jobj;
    HSD_JObj* ref2;
    HSD_JObj* ref3;
    GlyphVariantEntry* udata;
    NameNewData* ndata;
    Vec3 sp38;
    Vec3 sp2C;
    f32 dx;
    f32 dy;
    f32 base_x;
    f32 base_y;
    s32 i;

    ndata = (NameNewData*) mnNameNew_803EDA58;
    gobj = GObj_Create(6U, 7U, 0x80U);
    jobj = HSD_JObjLoadJoint(mnNameNew_804A0710[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6U, 0x80U);
    HSD_GObj_SetupProc(gobj, fn_8023CFC8, 0U);
    HSD_JObjAddAnimAll(jobj, mnNameNew_804A0710[1], mnNameNew_804A0710[2],
                       mnNameNew_804A0710[3]);
    HSD_JObjReqAnimAll(jobj, (f32) arg1 * 0.5f);
    HSD_JObjAnimAll(jobj);

    udata = HSD_MemAlloc(sizeof(GlyphVariantEntry));
    if (udata == NULL) {
        OSReport((char*) ((u8*) ndata + 0x904));
        __assert((char*) ((u8*) ndata + 0x91C), 0x5B4U,
                 (char*) ((u8*) ndata + 0x928));
    }
    GObj_InitUserData(gobj, 0U, fn_8023D0F8, udata);

    udata->selection = mn_804A04F0.confirmed_selection;
    i = 0;
    for (; i < 7; i++) {
        lb_80011E24(jobj, &udata->jobjs[i], i, -1);
    }

    sp2C = mnNameNew_803B8528;

    if (arg2 >= 0x32U && arg2 < 0x3AU) {
        key_jobj = *(HSD_JObj**)(arg0 +
                     ndata->key_counts[arg2 - 0x32] * 4 + 4);
    } else {
        key_jobj = HSD_JObjGetChild(*(HSD_JObj**)(arg0 + 0x44));
        for (i = 0; i < 50; i++) {
            if (i == (s32) arg2) break;
            key_jobj = HSD_JObjGetNext(key_jobj);
        }
    }

    lb_8000B1CC(key_jobj, &sp2C, &sp38);
    HSD_JObjSetTranslate(jobj, &sp38);

    ref_jobj = udata->jobjs[4];
    ref2 = udata->jobjs[5];
    ref3 = udata->jobjs[6];

    base_x = HSD_JObjGetTranslationX(ref_jobj);
    dx = HSD_JObjGetTranslationX(ref2) - base_x;
    base_y = HSD_JObjGetTranslationY(ref_jobj);
    dy = HSD_JObjGetTranslationY(ref3) - base_y;

    i = 0;
    for (; i < (s32) arg1; i++) {
        variant = HSD_JObjLoadJoint(mnNameNew_804A0720[0]);
        HSD_JObjAddAnimAll(variant, mnNameNew_804A0720[1],
                           mnNameNew_804A0720[2], mnNameNew_804A0720[3]);
        HSD_JObjReqAnimAll(variant, (f32)(i == udata->selection));
        HSD_JObjAnimAll(variant);
        HSD_JObjSetTranslateX(variant, dx * (f32)(i / 2));
        HSD_JObjSetTranslateY(variant, dy * (f32)(i % 2));
        HSD_JObjAddChild(ref_jobj, variant);
    }

    mnNameNew_8023D130(udata, arg1, arg0[0x50], arg2);
    return (s32) gobj;
}
s32 mnNameNew_8023DA08(NameNewEntry* arg0)
{
    s32 var_r29 = 1;

    if (mn_8022ED6C(arg0->jobjs[12], &mnNameNew_803EDA58[2]) <
        mnNameNew_803EDA58[2].end_frame)
    {
        var_r29 = 0;
    }
    if (mn_8022ED6C(arg0->jobjs[13], &mnNameNew_803EDA58[2]) <
        mnNameNew_803EDA58[2].end_frame)
    {
        var_r29 = 0;
    }
    if (mn_8022EFD8(arg0->jobjs[4], mnNameNew_803EDA58) <
        mnNameNew_803EDA58->end_frame)
    {
        var_r29 = 0;
    }
    if (mn_8022EFD8(arg0->jobjs[2], mnNameNew_803EDA58) <
        mnNameNew_803EDA58->end_frame)
    {
        var_r29 = 0;
    }
    if (mn_8022EFD8(arg0->jobjs[6], mnNameNew_803EDA58) <
        mnNameNew_803EDA58->end_frame)
    {
        var_r29 = 0;
    }
    return var_r29;
}

void fn_8023DAEC(HSD_GObj* arg0)
{
    HSD_Text* text;
    s32 var_r30;
    NameNewEntry* data;

    PAD_STACK(8);

    data = arg0->user_data;
    text = data->key_text;
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
        data->key_text = NULL;
    }
    text = data->name_disp_text;
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
        data->name_disp_text = NULL;
    }
    text = data->desc_text;
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
        data->desc_text = NULL;
    }
    var_r30 = 1;
    if (mn_8022EFD8(data->jobjs[4], &mnNameNew_803EDA58[1]) <
        mnNameNew_803EDA58[1].end_frame)
    {
        var_r30 = 0;
    }
    if (mn_8022EFD8(data->jobjs[2], &mnNameNew_803EDA58[1]) <
        mnNameNew_803EDA58[1].end_frame)
    {
        var_r30 = 0;
    }
    if (mn_8022EFD8(data->jobjs[6], &mnNameNew_803EDA58[1]) <
        mnNameNew_803EDA58[1].end_frame)
    {
        var_r30 = 0;
    }
    if (var_r30 != 0 || (u8) mn_804A04F0.x10 == 1) {
        HSD_GObjPLink_80390228(arg0);
    }
}


static f32 mnNameNew_804D4C10 = 10.0f;
static s32 mnNameNew_804D4F68 = 0xFF;

#pragma push
#pragma dont_inline on
void fn_8023DBE8(HSD_GObj* arg0)
{
    NameNewEntry* data;
    HSD_JObj* jobj;
    HSD_JObj* parent;
    HSD_GObjProc* proc;
    GXColor sp2C;
    s32 sp28;
    u8 cursor;
    u8 sel;
    s32 i;

    FORCE_PAD_STACK(32);

    data = arg0->user_data;

    if ((u8) mn_804A04F0.x10 != 1) {
        HSD_JObjSetFlagsAll(data->jobjs[16], 0x10U);
        HSD_JObjSetFlagsAll(data->jobjs[12], 0x10U);
        HSD_JObjSetFlagsAll(data->jobjs[13], 0x10U);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(arg0, fn_8023DAEC, 0U);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }

    mnNameNew_8023DA08(data);
    cursor = data->x1;

    if ((s32) cursor != (s32) mn_804A04F0.hovered_selection) {
        if (cursor >= 0x32U && cursor < 0x3AU) {
            jobj = data->jobjs[mnNameNew_803EDA7C[cursor - 0x32]];
        } else {
            parent = data->jobjs[16];
            if (parent == NULL) {
                jobj = NULL;
            } else {
                jobj = parent->child;
            }
            for (i = 0; i < 50; i++) {
                if (i == (s32) cursor) break;
                if (jobj == NULL) {
                    jobj = NULL;
                } else {
                    jobj = jobj->next;
                }
            }
        }
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        if ((u8) data->x1 < 0x32U) {
            sp2C = mnNameNew_804D4F6C;
            HSD_SisLib_803A74F0(data->key_text,
                                (s32) data->x1, (u8*) &sp2C);
        }

        sel = (u8) mn_804A04F0.hovered_selection;
        if (sel >= 0x32U && sel < 0x3AU) {
            jobj = data->jobjs[mnNameNew_803EDA7C[sel - 0x32]];
        } else {
            parent = data->jobjs[16];
            if (parent == NULL) {
                jobj = NULL;
            } else {
                jobj = parent->child;
            }
            for (i = 0; i < 50; i++) {
                if (i == (s32) sel) break;
                if (jobj == NULL) {
                    jobj = NULL;
                } else {
                    jobj = jobj->next;
                }
            }
        }
        HSD_JObjReqAnimAll(jobj, 1.0f);
        HSD_JObjAnimAll(jobj);
        if ((u16) mn_804A04F0.hovered_selection < 0x32U) {
            sp28 = mnNameNew_804D4F68;
            HSD_SisLib_803A74F0(data->key_text,
                                (s32) mn_804A04F0.hovered_selection,
                                (u8*) &sp28);
        }
        mnNameNew_8023B314(data, (s32) mn_804A04F0.hovered_selection);
        data->x1 = (u8) mn_804A04F0.hovered_selection;
        mnNameNew_8023B0F8(arg0, data->x1);
    }

    cursor = data->cursor_pos;
    if ((mnNameNew_804D4C10 + (f32) cursor) !=
        mn_8022F298(data->jobjs[13]))
    {
        jobj = ((NameNewEntry*) arg0->user_data)->jobjs[13];
        HSD_JObjReqAnimAll(jobj, mnNameNew_804D4C10 + (f32) cursor);
        HSD_JObjAnimAll(jobj);
    }
}
#pragma pop


void mnNameNew_8023E0D8(NameNewEntry* arg0)
{
    HSD_JObj* jobj;
    s32 i;

    jobj = arg0->jobjs[12];
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[2].start_frame);
    HSD_JObjAnim(jobj);

    jobj = arg0->jobjs[13];
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[2].start_frame);
    HSD_JObjAnim(jobj);

    jobj = arg0->jobjs[4];
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[0].start_frame);
    HSD_JObjAnim(jobj);

    jobj = arg0->jobjs[5];
    HSD_JObjReqAnimAll(jobj, (f32)(arg0->x1 == 0x38));
    HSD_JObjAnimAll(jobj);

    jobj = arg0->jobjs[2];
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[0].start_frame);
    HSD_JObjAnim(jobj);

    jobj = arg0->jobjs[5];
    HSD_JObjReqAnimAll(jobj, (f32)(arg0->x1 == 0x32));
    HSD_JObjAnimAll(jobj);

    jobj = arg0->jobjs[6];
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[0].start_frame);
    HSD_JObjAnim(jobj);

    for (i = 0x32; i < 0x3A; i++) {
        jobj = arg0->jobjs[mnNameNew_803EDA7C[i - 0x32]];
        HSD_JObjReqAnimAll(jobj, (f32)(i == arg0->x1));
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

    arg0->x1 = (u8) mn_804A04F0.hovered_selection;
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
    null_char = (s8) mnNameNew_NullCharacter;
    names = AutoNamesList;
    while (null_char != (s8) **names) {
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


void mnNameNew_8023E32C(s32 arg0)
{
    HSD_GObj* gobj;
    HSD_JObj* root_jobj;
    HSD_JObj* key_jobj;
    NameNewEntry* data;
    s32 i;
    s32 k;
    f32 x_range;
    f32 y_range;

    PAD_STACK(8);

    gobj = GObj_Create(6U, 7U, 0x80U);
    mnNameNew_804D6C08 = gobj;
    root_jobj = HSD_JObjLoadJoint(mnNameNew_804A06F0[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root_jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4U, 0x80U);
    HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_8023DBE8, 0U);
    HSD_JObjAddAnimAll(root_jobj, mnNameNew_804A06F0[1],
                       mnNameNew_804A06F0[2], mnNameNew_804A06F0[3]);
    HSD_JObjReqAnimAll(root_jobj, 0.0f);
    HSD_JObjAnimAll(root_jobj);
    data = HSD_MemAlloc(0x6C);
    if (data == NULL) {
        OSReport((char*)((u8*) mnNameNew_803EDA58 + 0x904));
        __assert((char*)((u8*) mnNameNew_803EDA58 + 0x91C), 0x717U,
                 (char*)((u8*) mnNameNew_803EDA58 + 0x928));
    }
    GObj_InitUserData(gobj, 0U, HSD_Free, data);
    InitNameEntryUIState(data, arg0);
    i = 0;
    do {
        lb_80011E24(root_jobj, &data->jobjs[i], i, -1);
        i++;
    } while (i < 0x13);
    mnNameNew_8023E0D8(data);
    k = 0;
    do {
        key_jobj = HSD_JObjLoadJoint(mnNameNew_804A0700[0]);
        HSD_JObjAddAnimAll(key_jobj, mnNameNew_804A0700[1],
                           mnNameNew_804A0700[2], mnNameNew_804A0700[3]);
        HSD_JObjReqAnimAll(key_jobj, (f32)(data->x1 == (u8) k));
        HSD_JObjAnimAll(key_jobj);
        x_range = HSD_JObjGetTranslationX(data->jobjs[17]) -
                  HSD_JObjGetTranslationX(data->jobjs[16]);
        y_range = HSD_JObjGetTranslationY(data->jobjs[18]) -
                  HSD_JObjGetTranslationY(data->jobjs[16]);
        mnName_80239F5C(key_jobj, x_range * (f32)(k / 5));
        mnName_80239EBC(key_jobj, y_range * (f32)(k % 5));
        HSD_JObjAddChild(data->jobjs[16], key_jobj);
        k++;
    } while (k < 0x32);
    data->key_text = (HSD_Text*) mnNameNew_KeySetup(data, data->mode);
    mnNameNew_8023B314(data, (s32) data->x1);
    mnNameNew_8023B0F8(gobj, data->x1);
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
    text[0] = mnNameNew_NullCharacter;
    text[3] = mnNameNew_NullCharacter;
    text[6] = mnNameNew_NullCharacter;
    text[9] = mnNameNew_NullCharacter;
    mnNameNew_8023E32C((s32) arg0);
}


void mnNameNew_EnterFromMnCharSel(HSD_Archive* arg0, s32 arg1)
{
    u8* base;
    u8 name_count;
    HSD_GObjProc* proc;
    char* text;
    s32 is_us;

    PAD_STACK(16);

    base = (u8*) mnNameNew_803EDA58;
    text = mnNameNew_CurrentNameText;

    mn_804D6BC8.cooldown = 0x14;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
    *(u32*)((u8*)&mn_804A04F0 + 0xC) = 0;
    *(u32*)((u8*)&mn_804A04F0 + 0x8) = 0;
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
        (void**) &MenMainBack_Top.joint, (char*)(base + 0x934),
        &MenMainBack_Top.animjoint, (char*)(base + 0x94C),
        &MenMainBack_Top.matanim_joint, (char*)(base + 0x968),
        &MenMainBack_Top.shapeanim_joint, (char*)(base + 0x988),
        &MenMain_cam, (char*)(base + 0x9A8),
        &MenMain_lights, (char*)(base + 0x9C4),
        &MenMain_fog, (char*)(base + 0x9DC),
        &MenMainPanel_Top.joint, (char*)(base + 0x9EC),
        &MenMainPanel_Top.animjoint, (char*)(base + 0xA04),
        &MenMainPanel_Top.matanim_joint, (char*)(base + 0xA20),
        &MenMainPanel_Top.shapeanim_joint, (char*)(base + 0xA40),
        &mnNameNew_804A06F0[0], (char*)(base + 0xA64),
        &mnNameNew_804A06F0[1], (char*)(base + 0xA80),
        &mnNameNew_804A06F0[2], (char*)(base + 0xAA0),
        &mnNameNew_804A06F0[3], (char*)(base + 0xAC4),
        &mnNameNew_804A0700[0], (char*)(base + 0xAE8),
        &mnNameNew_804A0700[1], (char*)(base + 0xB04),
        &mnNameNew_804A0700[2], (char*)(base + 0xB24),
        &mnNameNew_804A0700[3], (char*)(base + 0xB48),
        &mnNameNew_804A0710[0], (char*)(base + 0xB6C),
        &mnNameNew_804A0710[1], (char*)(base + 0xB88),
        &mnNameNew_804A0710[2], (char*)(base + 0xBA8),
        &mnNameNew_804A0710[3], (char*)(base + 0xBCC),
        &mnNameNew_804A0720[0], (char*)(base + 0xBF0),
        &mnNameNew_804A0720[1], (char*)(base + 0xC0C),
        &mnNameNew_804A0720[2], (char*)(base + 0xC2C),
        &mnNameNew_804A0720[3], (char*)(base + 0xC50),
        NULL);

    is_us = lbLang_IsSavedLanguageUS();
    if (is_us) {
        lbArchive_LoadSections(
            arg0,
            (void**) &AutoNamesList, (char*)(base + 0xC78),
            &NotAllowedNamesList, (char*)(base + 0xC8C),
            NULL);
    } else {
        lbArchive_LoadSections(
            arg0,
            (void**) &AutoNamesList, (char*)(base + 0xCA0),
            &NotAllowedNamesList, (char*)(base + 0xCB0),
            NULL);
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

    text[0] = mnNameNew_NullCharacter;
    text[3] = mnNameNew_NullCharacter;
    text[6] = mnNameNew_NullCharacter;
    text[9] = mnNameNew_NullCharacter;
    mnNameNew_8023E32C((s32) name_count);
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

void mnNameNew_8023EA08(UNK_T arg0)
{
    mnNameNew_EnterFromMnCharSel((HSD_Archive*) arg0, 4);
}
