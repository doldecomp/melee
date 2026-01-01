#include "mnname.h"

#include "mnmain.h"
#include "mnnamenew.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lblanguage.h>
#include <sysdolphin/baselib/jobj.h>

extern char mnName_StringTerminator;
extern char** NotAllowedNamesList;
extern char mnNameNew_NullCharacter;
extern char* mnNameNew_803EE724[];
extern char* mnNameNew_803EE720[];

void fn_80249A1C(HSD_GObj* arg0);

void* mnName_8023749C(s32 idx) {
    char** table;
    char* ptr;
    s32 i;
    s8 terminator;

    if (lbLang_IsSavedLanguageUS()) {
        table = mnNameNew_803EE724;
    } else {
        table = mnNameNew_803EE720;
    }

    terminator = mnName_StringTerminator;
    ptr = (char*)table;
    i = 0;

    goto loop_cond;
loop_body:
    ptr += 4;
    i++;
loop_cond:
    if (i != (u8)idx) {
        char* str = *(char**)ptr;
        if (terminator != str[0]) {
            goto loop_body;
        }
    }

    if ((s8)mnName_StringTerminator == table[i][0]) {
        return 0;
    }
    return table[i];
}

char* GetNameText(int slot)
{
    if (!IsNameValid(slot)) {
        return NULL;
    }
    return (char*)((u8*)GetPersistentNameData((u8)slot) + 0x198);
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
        if (IsNameValid((u8)i)) {
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

void fn_80238540(void) {
    switch (mn_804A04F0.x10) {
    case 0:
        mnName_MainInput();
        break;
    case 1:
        mnNameNew_MainInput();
        break;
    case 2:
        mnName_ConfirmNameDeleteInput();
        break;
    }
}
void mnName_802385A0(HSD_GObj* gobj)
{
    mnName_80238754(gobj);
    mnName_8023A058(gobj);
}
s32 mnName_GetPageCount(void) {
    s32 count;
    s32 i;
    s32 rem;
    
    count = 0;
    i = 0;
    
    for (; i < 0x78; i++) {
        char* data;
        char first_char;
        char term;
        BOOL valid;
        data = (char*)GetPersistentNameData((u8)i);
        first_char = data[0x198];
        term = mnName_StringTerminator;
        if (term == first_char) {
            valid = FALSE;
        } else {
            valid = TRUE;
        }
        if (valid) {
            count++;
        }
    }
    
    if (count % 24 != 0) {
        rem = 1;
    } else {
        rem = 0;
    }
    return count / 24 + rem;
}
/// #mnName_GetColumnCount

/// #mnName_80238754

s32 mnName_802388D4(void* arg0, u8 arg1) {
    int count;
    void* result;
    void* temp;

    if (arg1 < 0x18) {
        temp = *(void**)((u8*)arg0 + 0x30);
        if (temp == NULL) {
            result = NULL;
        } else {
            result = *(void**)((u8*)temp + 0x10);
        }
        for (count = (u8)arg1; count > 0; count--) {
            temp = result;
            if (temp == NULL) {
                result = NULL;
            } else {
                result = *(void**)((u8*)temp + 0x8);
            }
        }
        return (s32)result;
    }

    switch(arg1) {
        case 0x18:
            return *(s32*)((u8*)arg0 + 0x24);
        case 0x19:
            return *(s32*)((u8*)arg0 + 0x18);
        case 0x1a:
            return *(s32*)((u8*)arg0 + 0x1c);
    }

    return (s32)arg0;
}
/// #mnName_80238964

/// #mnName_80238A04

/// #mnName_80238AE0

/// #mnName_80238C34

/// #fn_80239574

/// #mnName_80239878

/// #mnName_80239A24

/// #mnName_80239EBC

/// #mnName_80239F5C

typedef struct {
    char unk[0x30];
    void* x30;
    char unk34[0x8];
    void* x3C;
} MnNameData;

s32 mnName_80239FFC(void* arg0) {
    MnNameData* data = (MnNameData*)arg0;
    void* obj;
    HSD_JObj* jobj;

    obj = data->x30;
    if (obj == NULL) {
        jobj = NULL;
    } else {
        jobj = *(HSD_JObj**)((u8*)obj + 0x10);
    }
    HSD_JObjRemoveAll(jobj);

    if (data->x3C != NULL) {
        HSD_SisLib_803A5CC4(data->x3C);
        data->x3C = NULL;
    }
}
void mnName_8023A058(HSD_GObj* gobj) {
    MnNameData* data = (MnNameData*)gobj;
    void* obj;
    HSD_JObj* jobj;

    obj = data->x30;
    if (obj == NULL) {
        jobj = NULL;
    } else {
        jobj = *(HSD_JObj**)((u8*)obj + 0x10);
    }
    HSD_JObjRemoveAll(jobj);

    if (data->x3C != NULL) {
        HSD_SisLib_803A5CC4(data->x3C);
        data->x3C = NULL;
    }
    
    mnName_80239A24(gobj);
}
/// #fn_8023A0BC

/// #mnName_8023A290

/// #mnName_8023A59C

/// #mnName_8023A9B4

/// #mnName_8023AC40

BOOL IsNameNotAllowed(char* name) {
    char** list = NotAllowedNamesList;
    for (;;) {
        char nullChar = mnNameNew_NullCharacter;
        char firstChar = **list;
        if ((s8)nullChar != (s8)firstChar) {
            if (CompareNameStrings(*list, name) == 0) {
                return TRUE;
            }
            list++;
        } else {
            return FALSE;
        }
    }
}