#include "mnnamenew.h"

#include "lb/lblanguage.h"
#include "mn/mnmain.h"
#include "sysdolphin/baselib/memory.h"
#include "sysdolphin/baselib/sislib.h"

#include <baselib/gobjplink.h>

extern volatile char mnNameNew_NullCharacter;
extern u8 mnNameNew_PortInUse;
extern char mnNameNew_CurrentNameText[0x10];
extern u8 mnNameNew_803EDA58[];

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

typedef struct fn_8023DAEC_data {
    /* 0x00 */ u8 pad_00[0x0C];
    /* 0x0C */ HSD_JObj* x0C;
    /* 0x10 */ u8 pad_10[4];
    /* 0x14 */ HSD_JObj* x14;
    /* 0x18 */ u8 pad_18[4];
    /* 0x1C */ HSD_JObj* x1C;
    /* 0x20 */ u8 pad_20[0x40];
    /* 0x60 */ HSD_Text* x60;
    /* 0x64 */ HSD_Text* x64;
    /* 0x68 */ HSD_Text* x68;
} fn_8023DAEC_data;

void fn_8023DAEC(HSD_GObj* gobj)
{
    fn_8023DAEC_data* data = gobj->user_data;
    u8* base = mnNameNew_803EDA58;
    int done;
    float* threshold;

    if (data->x60 != NULL) {
        HSD_SisLib_803A5CC4(data->x60);
        data->x60 = NULL;
    }
    if (data->x64 != NULL) {
        HSD_SisLib_803A5CC4(data->x64);
        data->x64 = NULL;
    }
    if (data->x68 != NULL) {
        HSD_SisLib_803A5CC4(data->x68);
        data->x68 = NULL;
    }

    done = 1;
    if (mn_8022EFD8(data->x14, (AnimLoopSettings*) (base + 0x0C)) <
        *(threshold = (float*) (base + 0x10)))
    {
        done = 0;
    }
    if (mn_8022EFD8(data->x0C, (AnimLoopSettings*) (base + 0x0C)) <
        *threshold)
    {
        done = 0;
    }
    if (mn_8022EFD8(data->x1C, (AnimLoopSettings*) (base + 0x0C)) <
        *threshold)
    {
        done = 0;
    }

    if (done || mn_804A04F0.x10 == 1) {
        HSD_GObjPLink_80390228(gobj);
    }
    PAD_STACK(8);
}

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
