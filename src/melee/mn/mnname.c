#include "mnname.h"

#include <melee/gm/gmmain_lib.h>

extern char mnName_StringTerminator;

void fn_80249A1C(HSD_GObj* arg0);

/// #mnName_8023749C

char* GetNameText(int slot)
{
    if (!IsNameValid(slot)) {
        return NULL;
    }
    return (char*) ((u8*) GetPersistentNameData((u8) slot) + 0x198);
}
int GetNameCount(void)
{
    int i = 0;
    int count = 0;
    for (; i < 0x78; i++) {
        if (IsNameValid((u8) i)) {
            count++;
        }
    }
    return count;
}

bool IsNameListFull(void)
{
    int result;
    int count = 0;
    int i;
    for (i = count; i < 0x78; i++) {
        if (IsNameValid((u8) i)) {
            count++;
        }
    }
    if (count < 0x78) {
        return false;
    }
    return true;
}
/// #CompareNameStrings

void fn_802377A4(void) {}

/// #IsNameUnique

/// #DeleteName

bool IsNameValid(int slot)
{
    char* data = (char*) GetPersistentNameData((u8) slot);
    char first_char = data[0x198];
    char term = mnName_StringTerminator;
    if (term == first_char) {
        return false;
    }
    return true;
}

/// #CreateNameAtIndex

/// #mnName_SortNames

/// #mnName_80237D94

/// #mnName_ConfirmNameDeleteInput

/// #mnName_MainInput

/// #fn_80238540

void mnName_802385A0(HSD_GObj* gobj)
{
    mnName_80238754(gobj);
    mnName_8023A058(gobj);
}
/// #mnName_GetPageCount

/// #mnName_GetColumnCount

/// #mnName_80238754

/// #mnName_802388D4

/// #mnName_80238964

/// #mnName_80238A04

/// #mnName_80238AE0

/// #mnName_80238C34

/// #fn_80239574

/// #mnName_80239878

/// #mnName_80239A24

/// #mnName_80239EBC

/// #mnName_80239F5C

/// #mnName_80239FFC

/// #mnName_8023A058

/// #fn_8023A0BC

/// #mnName_8023A290

/// #mnName_8023A59C

/// #mnName_8023A9B4

/// #mnName_8023AC40

/// #IsNameNotAllowed
