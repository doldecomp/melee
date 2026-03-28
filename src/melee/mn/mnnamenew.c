#include "mnnamenew.h"

#include "gm/gm_18A5.h"
#include "gm/gm_1A3F.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "mn/mncharsel.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "mn/types.h"
#include "sysdolphin/baselib/gobjplink.h"
#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/memory.h"
#include "sysdolphin/baselib/random.h"
#include "sysdolphin/baselib/sislib.h"

extern volatile char mnNameNew_NullCharacter;
extern u8 mnNameNew_PortInUse;
extern char mnNameNew_CurrentNameText[0x10];
extern u8** AutoNamesList;
extern u8 mn_804D6BB4;
extern u8 mn_804D6BB5;
extern u8 mnNameNew_804D4F7C[4];
extern void* mnNameNew_804D6C08;
extern u8 mnNameNew_SpaceCharacter[2];
extern char* mnNameNew_803EDCE4[];

static AnimLoopSettings mnNameNew_803EDA58[3] = {
    { 0.0f, 19.0f, -0.1f },
    { 20.0f, 39.0f, -0.1f },
    { 0.0f, 10.0f, -0.1f },
};

static Vec3 mnNameNew_803EE330 = { -0.7f, 0.7f, 0.0f };

/// #mnNameNew_8023B0F8

void mnNameNew_8023B0F8(HSD_GObj* arg0, u8 arg1)
{
    HSD_JObj* jobj;
    u8* data;

    PAD_STACK(8);

    data = arg0->user_data;
    jobj = *(HSD_JObj**)(data + 0x2C);
    if (arg1 == 0x33) {
        HSD_JObjReqAnimAll(jobj, 1.0f);
    } else if (*(u8*)(data + 0x50) == 0) {
        HSD_JObjReqAnimAll(jobj, 2.0f);
    } else {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    }
    HSD_JObjAnimAll(jobj);
    jobj = *(HSD_JObj**)(data + 0x30);
    if (arg1 == 0x34) {
        HSD_JObjReqAnimAll(jobj, 1.0f);
    } else if (*(u8*)(data + 0x50) == 1) {
        HSD_JObjReqAnimAll(jobj, 2.0f);
    } else {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    }
    HSD_JObjAnimAll(jobj);
    jobj = *(HSD_JObj**)(data + 0x20);
    if (arg1 == 0x35) {
        HSD_JObjReqAnimAll(jobj, 1.0f);
    } else if (*(u8*)(data + 0x50) == 2) {
        HSD_JObjReqAnimAll(jobj, 2.0f);
    } else {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    }
    HSD_JObjAnimAll(jobj);
}

void mnNameNew_8023B224(u8 arg0)
{
    u8* temp_r31;
    u8 temp_r30;

    PAD_STACK(8);

    temp_r31 = *(u8**)((u8*) mnNameNew_804D6C08 + 0x2C);
    temp_r30 = temp_r31[0x59];
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
            mnName_8023A9B4((u8)(temp_r31[0x59] / 6));
            return;
        }
        mnName_8023A9B4(0U);
        return;
    }
    HSD_SisLib_803A5E70();
    mn_8022EBDC();
    mnCharSel_802640A0();
}

void mnNameNew_8023B314(u8* arg0, s32 arg1)
{
    HSD_Text* text;
    u8 idx;
    s32 var_r4;

    var_r4 = arg1;
    if (var_r4 < 0x32) {
        switch (arg0[0x50]) {
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
    text = *(HSD_Text**)(arg0 + 0x68);
    idx = mnNameNew_804D4F7C[var_r4 - 0x32];
    if (text != NULL) {
        if (text->sis_buffer == ((SIS**) HSD_SisLib_804D1124[0])[idx]) {
            return;
        }
        HSD_SisLib_803A5CC4(text);
    }
    text = HSD_SisLib_803A5ACC(0, (s32) mn_804D6BB4, -9.5f, 9.1f, 17.0f,
                               364.68332f, 38.38772f);
    *(HSD_Text**)(arg0 + 0x68) = text;
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(text, (s32) idx);
}

/// #mnNameNew_KeySetup

/// #mnNameNew_8023BAA8

s32 mnNameNew_8023BAA8(u8* arg0, s32 arg1, u8 arg2)
{
    u8 mode;

    if (arg2 >= 0x32U && arg2 < 0x3AU) {
        if (arg1 & 1) {
            if (arg2 == 0x39) {
                return ((arg0[0x51] / 5) * 5) + 4;
            }
            if (arg2 > 0x32U) {
                return arg2 - 1;
            }
            return 0x38;
        }
        if (arg1 & 2) {
            if (arg2 == 0x39) {
                return (arg0[0x51] / 5) * 5;
            }
            if (arg2 == 0x38) {
                return 0x32;
            }
            return arg2 + 1;
        }
        if (arg1 & 4) {
            if (arg2 != 0x38 && arg2 != 0x39) {
                return arg0[0x51] % 5;
            }
        } else if ((arg1 & 8) && arg2 != 0x38 && arg2 != 0x39) {
            return (arg0[0x51] % 5) + 0x2D;
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
            mode = arg0[0x50];
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
            mode = arg0[0x50];
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

/// #PickAutoName

s32 PickAutoName(HSD_GObj* arg0)
{
    u8* data;
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
        } while (IsNameUnique((s32) AutoNamesList[pick]) != 0);

        if (pick == (s32) data[0x5A]) {
            dup = 1;
        } else if (pick == (s32) data[0x5B]) {
            dup = 1;
        } else if (pick == (s32) data[0x5C]) {
            dup = 1;
        } else if (pick == (s32) data[0x5D]) {
            dup = 1;
        } else if (pick == (s32) data[0x5E]) {
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

    tmp = data[0x5A];
    data[0x5A] = (u8) pick;
    ch = data[0x5B];
    data[0x5B] = tmp;
    tmp = data[0x5C];
    data[0x5C] = ch;
    ch = data[0x5D];
    data[0x5D] = tmp;
    data[0x5E] = ch;

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

/// #WriteCharactersForNameAtIndex

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

/// #AddCharacterToName

s32 AddCharacterToName(u8* arg0, s32 arg1, u8 arg2, u8 arg3)
{
    s32 idx;
    u8 ch;
    u8* var_r4;
    u8** table;
    u8* base;
    u8* entry;

    base = (u8*) mnNameNew_803EDA58;

    if ((s32) arg3 != 2) {
        if ((s32) arg3 < 2 && (s32) arg3 >= 0) {
            if ((u8) (arg1 - 0x30) <= 1U) {
                if ((arg2 % 2) != 0) {
                    table = (u8**) (base + ((arg1 * 0x10) & 0xFF0) + 0x5AC);
                } else {
                    table = (u8**) (base + ((arg1 * 0x10) & 0xFF0) + 0x28C);
                }
            } else if ((arg3 == 0 && (arg2 % 2) == 0) ||
                       (arg3 == 1 && (arg2 % 2) != 0))
            {
                table = (u8**) (base + ((arg1 * 0x10) & 0xFF0) + 0x28C);
            } else {
                table = (u8**) (base + ((arg1 * 0x10) & 0xFF0) + 0x5AC);
            }
            var_r4 = arg0;
            idx = 0;
            while ((s8) mnNameNew_NullCharacter !=
                   (s8) (ch = *(table[arg2 / 2] + idx)))
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
    entry = base + ((arg1 * 4) & 0x3FC);
    arg0[0] = (*(u8**) (entry + 0x1C4))[0];
    arg0[1] = (*(u8**) (entry + 0x1C4))[1];
    arg0[2] = (*(u8**) (entry + 0x1C4))[2];
    return (s32) arg0;
}

/// #mnNameNew_GlyphVariantInput

void mnNameNew_GlyphVariantInput(void)
{
    u8* data;
    u32 buttons;
    s32 count;
    u16 old_hover;
    u8 old_sel;
    u8 cur_pos;
    char** table;
    s32 total;
    s8 null_ch;

    PAD_STACK(24);

    data = ((HSD_GObj*) mnNameNew_804D6C08)->user_data;
    buttons = mn_80229624((u32) mnNameNew_PortInUse);
    *(u32*)((u8*)&mn_804A04F0 + 0xC) = buttons;
    count = 0;
    *(u32*)((u8*)&mn_804A04F0 + 0x8) = 0;
    if (buttons & 0x200) {
        HSD_GObjPLink_80390228(*(HSD_GObj**)(data + 0x54));
        *(HSD_GObj**)(data + 0x54) = NULL;
        AddCharacterToName((u8*) &mnNameNew_CurrentNameText[*(u8*)(data + 0x58) * 3],
                           (s32)(u8) mn_804A04F0.hovered_selection,
                           mn_804A04F0.confirmed_selection,
                           *(u8*)(data + 0x50));
        lbAudioAx_80024030(1);
        cur_pos = *(u8*)(data + 0x58);
        old_hover = mn_804A04F0.hovered_selection;
        if (cur_pos < 3U) {
            *(u8*)(data + 0x58) = (u8)(cur_pos + 1);
        } else {
            mn_804A04F0.hovered_selection = 0x39;
        }
        mnNameNew_8023CE4C();
        if (((s32) old_hover != 0x30) && ((s32) old_hover != 0x31) &&
            ((mn_804A04F0.confirmed_selection % 2) != 0))
        {
            if (*(u8*)(data + 0x50) == 0) {
                *(u8*)(data + 0x50) = 1;
            } else {
                *(u8*)(data + 0x50) = 0;
            }
            mnNameNew_KeySetup(data, *(u8*)(data + 0x50));
            mnNameNew_8023B0F8((HSD_GObj*) mnNameNew_804D6C08,
                               (u8) mn_804A04F0.hovered_selection);
            mnNameNew_8023B314(data, (s32) mn_804A04F0.hovered_selection);
        }
    } else {
        if (buttons & 0x20) {
            HSD_GObjPLink_80390228(*(HSD_GObj**)(data + 0x54));
            *(HSD_GObj**)(data + 0x54) = NULL;
            mnNameNew_8023CE4C();
            return;
        }
        null_ch = (s8) mnNameNew_NullCharacter;
        table = &mnNameNew_803EDCE4[*(u8*)(data + 1) * 4];
        while (null_ch != (s8) **table) {
            table++;
            count++;
        }
        total = count * 2;
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

/// #mnNameNew_MainInput

static s32 mnNameNew_804D4F6C = (s32) 0xA6813DFF;
static s32 mnNameNew_804D4F70 = 0xFF;
static s32 mnNameNew_804D4F74 = 0x744F0BFF;
static s32 mnNameNew_804D4F78 = 0xFF;

/// #mnNameNew_8023CE4C

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
    u8* data;
    u8* name_ptr;
    u8* sp20_ptr;
    s32 i;

    PAD_STACK(8);

    data = *(u8**)((u8*) mnNameNew_804D6C08 + 0x2C);
    jobj_a = *(HSD_JObj**)(data + 0x3C);
    jobj_b = *(HSD_JObj**)(data + 0x40);
    first_x = HSD_JObjGetTranslationX(jobj_a);
    char_spacing = HSD_JObjGetTranslationX(jobj_b) - first_x;
    old_text = *(HSD_Text**)(data + 0x64);
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
    *(s32*) &text->text_color = mnNameNew_804D4F6C;
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
    *(HSD_Text**)(data + 0x64) = text;
}

/// #fn_8023CFC8

void fn_8023CFC8(HSD_GObj* arg0)
{
    s32 sp30;
    s32 sp2C;
    HSD_JObj* jobj;
    HSD_JObj* root;
    u8 old_sel;
    s32 count;
    u8* data;

    PAD_STACK(40);

    data = arg0->user_data;
    old_sel = data[0];
    if (old_sel != (u8) mn_804A04F0.confirmed_selection) {
        root = *(HSD_JObj**)(data + 0x14);
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
        HSD_SisLib_803A74F0(*(HSD_Text**)(data + 0x20), (s32) data[0],
                            (u8*) &sp30);
        root = *(HSD_JObj**)(data + 0x14);
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
        HSD_SisLib_803A74F0(*(HSD_Text**)(data + 0x20),
                            (s32) mn_804A04F0.confirmed_selection,
                            (u8*) &sp2C);
        data[0] = (u8) mn_804A04F0.confirmed_selection;
    }
}

void fn_8023D0F8(void* arg0)
{
    HSD_SisLib_803A5CC4(*(HSD_Text**) ((u8*) arg0 + 0x20));
    HSD_Free(arg0);
}

/// #mnNameNew_8023D130

s32 mnNameNew_8023D130(u8* arg0, u8 arg1, u8 arg2, s32 arg3)
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
    u8* table_b;
    u8* table_a;
    u8* base;
    u8* sp2C_ptr;

    PAD_STACK(8);

    base = (u8*) mnNameNew_803EDA58;
    jobj14 = *(HSD_JObj**)(arg0 + 0x14);
    text = HSD_SisLib_803A6754(0, (s32) mn_804D6BB4);
    jobj18 = *(HSD_JObj**)(arg0 + 0x18);
    jobj1C = *(HSD_JObj**)(arg0 + 0x1C);
    lb_8000B1CC(jobj14, (Vec3*)(base + 0x8CC), &sp30);
    text->pos_x = sp30.x;
    text->pos_y = -sp30.y;
    text->pos_z = sp30.z;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.04f;
    *(s32*) &text->text_color = mnNameNew_804D4F6C;
    x_range = HSD_JObjGetTranslationX(jobj18) - HSD_JObjGetTranslationX(jobj14);
    y_range = -(HSD_JObjGetTranslationY(jobj1C) - HSD_JObjGetTranslationY(jobj14));
    temp = (arg3 * 0x10) & 0xFF0;
    table_b = base + temp + 0x5AC;
    table_a = base + temp + 0x28C;
    sp2C_ptr = (u8*) &sp2C;
    for (i = 0; i < (s32) arg1; i++) {
        if ((u8)(arg3 - 0x30) <= 1U) {
            if ((i % 2) != 0) {
                str = *(char**)(table_b + (i / 2) * 4);
            } else {
                str = *(char**)(table_a + (i / 2) * 4);
            }
        } else if ((arg2 == 0 && (i % 2) == 0) ||
                   (arg2 == 1 && (i % 2) != 0))
        {
            str = *(char**)(table_a + (i / 2) * 4);
        } else {
            str = *(char**)(table_b + (i / 2) * 4);
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
    *(HSD_Text**)(arg0 + 0x20) = text;
    return (s32) text;
}

/// #mnNameNew_GlyphVariantSetup

s32 mnNameNew_8023DA08(u8* arg0)
{
    s32 var_r29 = 1;

    if (mn_8022ED6C(*(HSD_JObj**)(arg0 + 0x34), &mnNameNew_803EDA58[2]) <
        mnNameNew_803EDA58[2].end_frame)
    {
        var_r29 = 0;
    }
    if (mn_8022ED6C(*(HSD_JObj**)(arg0 + 0x38), &mnNameNew_803EDA58[2]) <
        mnNameNew_803EDA58[2].end_frame)
    {
        var_r29 = 0;
    }
    if (mn_8022EFD8(*(HSD_JObj**)(arg0 + 0x14), mnNameNew_803EDA58) <
        mnNameNew_803EDA58->end_frame)
    {
        var_r29 = 0;
    }
    if (mn_8022EFD8(*(HSD_JObj**)(arg0 + 0x0C), mnNameNew_803EDA58) <
        mnNameNew_803EDA58->end_frame)
    {
        var_r29 = 0;
    }
    if (mn_8022EFD8(*(HSD_JObj**)(arg0 + 0x1C), mnNameNew_803EDA58) <
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
    u8* data;

    PAD_STACK(8);

    data = arg0->user_data;
    text = *(HSD_Text**)(data + 0x60);
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
        *(HSD_Text**)(data + 0x60) = NULL;
    }
    text = *(HSD_Text**)(data + 0x64);
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
        *(HSD_Text**)(data + 0x64) = NULL;
    }
    text = *(HSD_Text**)(data + 0x68);
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
        *(HSD_Text**)(data + 0x68) = NULL;
    }
    var_r30 = 1;
    if (mn_8022EFD8(*(HSD_JObj**)(data + 0x14), &mnNameNew_803EDA58[1]) <
        mnNameNew_803EDA58[1].end_frame)
    {
        var_r30 = 0;
    }
    if (mn_8022EFD8(*(HSD_JObj**)(data + 0x0C), &mnNameNew_803EDA58[1]) <
        mnNameNew_803EDA58[1].end_frame)
    {
        var_r30 = 0;
    }
    if (mn_8022EFD8(*(HSD_JObj**)(data + 0x1C), &mnNameNew_803EDA58[1]) <
        mnNameNew_803EDA58[1].end_frame)
    {
        var_r30 = 0;
    }
    if (var_r30 != 0 || (u8) mn_804A04F0.x10 == 1) {
        HSD_GObjPLink_80390228(arg0);
    }
}

/// #fn_8023DBE8

/// #mnNameNew_8023E0D8

void mnNameNew_8023E0D8(u8* arg0)
{
    HSD_JObj* jobj;
    s32 i;
    u16* table;

    jobj = *(HSD_JObj**)(arg0 + 0x34);
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[2].start_frame);
    HSD_JObjAnim(jobj);

    jobj = *(HSD_JObj**)(arg0 + 0x38);
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[2].start_frame);
    HSD_JObjAnim(jobj);

    jobj = *(HSD_JObj**)(arg0 + 0x14);
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[0].start_frame);
    HSD_JObjAnim(jobj);

    jobj = *(HSD_JObj**)(arg0 + 0x18);
    HSD_JObjReqAnimAll(jobj, (f32)(arg0[1] == 0x38));
    HSD_JObjAnimAll(jobj);

    jobj = *(HSD_JObj**)(arg0 + 0x0C);
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[0].start_frame);
    HSD_JObjAnim(jobj);

    jobj = *(HSD_JObj**)(arg0 + 0x18);
    HSD_JObjReqAnimAll(jobj, (f32)(arg0[1] == 0x32));
    HSD_JObjAnimAll(jobj);

    jobj = *(HSD_JObj**)(arg0 + 0x1C);
    HSD_JObjReqAnim(jobj, mnNameNew_803EDA58[0].start_frame);
    HSD_JObjAnim(jobj);

    table = (u16*)((u8*) mnNameNew_803EDA58 + 0x24);
    for (i = 0x32; i < 0x3A; i++) {
        jobj = *(HSD_JObj**)(arg0 + table[i - 0x32] * 4 + 4);
        HSD_JObjReqAnimAll(jobj, (f32)(i == arg0[1]));
        HSD_JObjAnimAll(jobj);
    }
}

/// #InitNameEntryUIState

s32 InitNameEntryUIState(u8* arg0, s8 arg1)
{
    s32 result;
    s8 count;
    u8** names;
    s8 null_char;

    PAD_STACK(0x20);

    arg0[1] = (u8) mn_804A04F0.hovered_selection;
    result = lbLang_IsSavedLanguageUS();
    if (result) {
        arg0[0x50] = 2;
    } else {
        arg0[0x50] = 0;
    }
    count = 0;
    arg0[0x58] = 0;
    arg0[0x51] = arg0[1];
    *(s32*)(arg0 + 0x54) = 0;
    arg0[0x59] = arg1;
    *(s32*)(arg0 + 0x60) = 0;
    *(s32*)(arg0 + 0x64) = 0;
    *(s32*)(arg0 + 0x68) = 0;
    null_char = (s8) mnNameNew_NullCharacter;
    names = AutoNamesList;
    while (null_char != (s8) **names) {
        names++;
        count++;
    }
    arg0[0x5A] = count;
    arg0[0x5B] = count;
    arg0[0x5C] = count;
    arg0[0x5D] = count;
    arg0[0x5E] = count;
    return result;
}

/// #mnNameNew_8023E32C

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
    mnNameNew_8023E32C(arg0);
}

/// #mnNameNew_EnterFromMnCharSel

void mnNameNew_8023EA08(UNK_T arg0)
{
    mnNameNew_EnterFromMnCharSel(arg0, 4);
}
