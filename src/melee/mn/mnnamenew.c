#include "mnnamenew.h"

#include "gm/gm_18A5.h"
#include "gm/gm_1A3F.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "mn/mncharsel.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "sysdolphin/baselib/memory.h"
#include "sysdolphin/baselib/sislib.h"

extern volatile char mnNameNew_NullCharacter;
extern u8 mnNameNew_PortInUse;
extern char mnNameNew_CurrentNameText[0x10];
extern HSD_GObj* mnNameNew_804D6C08;

/// #mnNameNew_8023B0F8

void mnNameNew_8023B224(u8 arg0)
{
    HSD_GObj* gobj = mnNameNew_804D6C08;
    u8* user_data = gobj->user_data;
    u8 port = user_data[0x59];

    if (arg0 != 0) {
        lb_8001CE00();
    }

    if (gm_801A4310() == 0x1B) {
        HSD_SisLib_803A5E70();
        mn_8022EBDC();
        if (arg0 != 0) {
            gm_80190FE4(port);
        } else {
            gm_80190FE4(0x78);
        }
    } else if (gm_801A4310() == 0x01) {
        mn_804D6BC8.cooldown = 5;
        if (arg0 != 0 && GetNameCount() > 0x18) {
            mnName_8023A9B4((u8)(user_data[0x59] / 6));
        } else {
            mnName_8023A9B4(0);
        }
    } else {
        HSD_SisLib_803A5E70();
        mn_8022EBDC();
        mnCharSel_802640A0();
    }
    PAD_STACK(8);
}

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

/// #InitNameEntryUIState

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
