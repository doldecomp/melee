#include "mnnamenew.h"

#include "gm/gm_18A5.h"
#include "gm/gm_1A3F.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "mn/mncharsel.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "mn/types.h"
#include "sysdolphin/baselib/gobjplink.h"
#include "sysdolphin/baselib/memory.h"
#include "sysdolphin/baselib/sislib.h"

extern volatile char mnNameNew_NullCharacter;
extern u8 mnNameNew_PortInUse;
extern char mnNameNew_CurrentNameText[0x10];
extern u8** AutoNamesList;
extern u8 mn_804D6BB4;
extern u8 mnNameNew_804D4F7C[4];
extern void* mnNameNew_804D6C08;
extern u8 mnNameNew_SpaceCharacter[2];

static AnimLoopSettings mnNameNew_803EDA58[3] = {
    { 0.0f, 19.0f, -0.1f },
    { 20.0f, 39.0f, -0.1f },
    { 0.0f, 10.0f, -0.1f },
};

/// #mnNameNew_8023B0F8

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

/// #PickAutoName

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

/// #AddCharacterToName

/// #mnNameNew_GlyphVariantInput

/// #mnNameNew_MainInput

/// #mnNameNew_8023CE4C

/// #fn_8023CFC8

void fn_8023D0F8(void* arg0)
{
    HSD_SisLib_803A5CC4(*(HSD_Text**) ((u8*) arg0 + 0x20));
    HSD_Free(arg0);
}

/// #mnNameNew_8023D130

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
