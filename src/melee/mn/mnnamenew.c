#include "mnnamenew.h"

#include "lb/lblanguage.h"
#include "mn/mnmain.h"
#include "sysdolphin/baselib/memory.h"
#include "sysdolphin/baselib/sislib.h"

extern volatile char mnNameNew_NullCharacter;
extern u8 mnNameNew_PortInUse;
extern char mnNameNew_CurrentNameText[0x10];
extern u8** AutoNamesList;

/// #mnNameNew_8023B0F8

/// #mnNameNew_8023B224

/// #mnNameNew_8023B314

/// #mnNameNew_KeySetup

/// #mnNameNew_8023BAA8

/// #PickAutoName

/// #NameContainsOnlySpaces

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

/// #mnNameNew_8023DA08

/// #fn_8023DAEC

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
