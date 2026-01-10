#include "mnname.h"

#include "mnmain.h"
#include "mnnamenew.h"

#include <sysdolphin/baselib/jobj.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lblanguage.h>

extern char mnName_StringTerminator;
extern char** NotAllowedNamesList;
extern char mnNameNew_NullCharacter;
extern char* mnNameNew_803EE724[];
extern char* mnNameNew_803EE720[];
extern char* mnName_804D4BF4;
extern char* mnName_804D4BFC;
extern f32 mnName_803ED538[];

void fn_80249A1C(HSD_GObj* arg0);

void* mnName_8023749C(s32 idx)
{
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
    ptr = (char*) table;
    i = 0;

    goto loop_cond;
loop_body:
    ptr += 4;
    i++;
loop_cond:
    if (i != (u8) idx) {
        char* str = *(char**) ptr;
        if (terminator != str[0]) {
            goto loop_body;
        }
    }

    if ((s8) mnName_StringTerminator == table[i][0]) {
        return 0;
    }
    return table[i];
}

char* GetNameText(int slot)
{
    if (!IsNameValid(slot)) {
        return NULL;
    }
    return GetPersistentNameData((u8) slot)->namedata;
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
    struct gmm_x2FF8_inner* data = GetPersistentNameData((u8) slot);
    char first_char = data->namedata[0];
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

void fn_80238540(void)
{
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
s32 mnName_GetPageCount(void)
{
    s32 count;
    s32 i;
    s32 rem;

    count = 0;
    i = 0;

    for (; i < 0x78; i++) {
        struct gmm_x2FF8_inner* data;
        char first_char;
        char term;
        s32 valid;
        data = GetPersistentNameData((u8) i);
        first_char = data->namedata[0];
        term = mnName_StringTerminator;
        if (term == first_char) {
            valid = 0;
        } else {
            valid = 1;
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
s32 mnName_GetColumnCount(void)
{
    s32 count;
    s32 i;
    s32 rem;
    s32 zero;

    count = 0;
    zero = count;
    i = zero;

    for (; i < 0x78; i++) {
        struct gmm_x2FF8_inner* data;
        char first_char;
        char term;
        s32 valid;
        data = GetPersistentNameData((u8) i);
        first_char = data->namedata[0];
        term = mnName_StringTerminator;
        if (term == first_char) {
            valid = 0;
        } else {
            valid = 1;
        }
        if (valid) {
            count++;
        }
    }

    if (count % 6 != 0) {
        rem = 1;
    } else {
        rem = 0;
    }
    return count / 6 + rem;
}
/// #mnName_80238754

typedef struct MnName88D4Data {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ char unk20[0x4];
    /* 0x24 */ s32 x24;
    /* 0x28 */ char unk28[0x8];
    /* 0x30 */ HSD_JObj* x30;
} MnName88D4Data;

s32 mnName_802388D4(void* arg0, u8 arg1)
{
    MnName88D4Data* data = arg0;
    int count;
    HSD_JObj* result;
    HSD_JObj* temp;

    if (arg1 < 0x18) {
        temp = data->x30;
        if (temp == NULL) {
            result = NULL;
        } else {
            result = temp->child;
        }
        for (count = (u8) arg1; count > 0; count--) {
            temp = result;
            if (temp == NULL) {
                result = NULL;
            } else {
                result = temp->next;
            }
        }
        return (s32) result;
    }

    switch (arg1) {
    case 0x18:
        return data->x24;
    case 0x19:
        return data->x18;
    case 0x1A:
        return data->x1C;
    }

    return (s32) arg0;
}
/// #mnName_80238964

void mnName_80238A04(s32 arg0, s32 arg1, s32 arg2)
{
    MnName88D4Data* data = (MnName88D4Data*) arg0;
    f32* table = mnName_803ED538;
    s32 i;
    s32 jobj;

    for (i = 0x18; i < 0x1B; i++) {
        jobj = mnName_802388D4((void*) arg0, (u8) i);
        HSD_JObjReqAnimAll((HSD_JObj*) jobj,
                           mnName_80238964((void*) i, arg1, arg2));
        HSD_JObjAnimAll((HSD_JObj*) jobj);
    }

    i = data->x14;

    if ((u8) arg1 == 0x18) {
        if ((u8) arg2 != 0) {
            HSD_JObjReqAnimAll((HSD_JObj*) i, table[15]);
        } else {
            HSD_JObjReqAnimAll((HSD_JObj*) i, table[12]);
        }
    } else {
        if ((u8) arg2 != 0) {
            HSD_JObjReqAnimAll((HSD_JObj*) i, table[24]);
        } else {
            HSD_JObjReqAnimAll((HSD_JObj*) i, table[18]);
        }
    }
    HSD_JObjAnimAll((HSD_JObj*) i);
}
/// #mnName_80238AE0

/// #mnName_80238C34

/// #fn_80239574

/// #mnName_80239878

/// #mnName_80239A24

void mnName_80239EBC(void* arg0, f32 arg1)
{
    HSD_JObj* jobj = arg0;

    if (jobj == NULL) {
        __assert(mnName_804D4BF4, 947, mnName_804D4BFC);
    }

    jobj->translate.z = arg1;

    if ((jobj->flags & 0x02000000) != 0) {
        return;
    }

    if (jobj == NULL) {
        return;
    }

    if (jobj == NULL) {
        __assert(mnName_804D4BF4, 564, mnName_804D4BFC);
    }

    {
        s32 cond;
        cond = false;
        if ((jobj->flags & 0x00800000) == 0) {
            if ((jobj->flags & 0x00000040) != 0) {
                cond = true;
            }
        }
        if (cond == false) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}
void mnName_80239F5C(void* arg0, f32 arg1)
{
    HSD_JObj* jobj = arg0;

    if (jobj == NULL) {
        __assert(mnName_804D4BF4, 932, mnName_804D4BFC);
    }

    jobj->translate.x = arg1;

    if ((jobj->flags & 0x02000000) != 0) {
        return;
    }

    if (jobj == NULL) {
        return;
    }

    if (jobj == NULL) {
        __assert(mnName_804D4BF4, 564, mnName_804D4BFC);
    }

    {
        s32 cond;
        cond = false;
        if ((jobj->flags & 0x00800000) == 0) {
            if ((jobj->flags & 0x00000040) != 0) {
                cond = true;
            }
        }
        if (cond == false) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}
typedef struct {
    char unk[0x30];
    HSD_JObj* x30;
    char unk34[0x8];
    void* x3C;
} MnNameData;

s32 mnName_80239FFC(void* arg0)
{
    MnNameData* data = (MnNameData*) arg0;
    HSD_JObj* obj;
    HSD_JObj* jobj;

    obj = data->x30;
    if (obj == NULL) {
        jobj = NULL;
    } else {
        jobj = obj->child;
    }
    HSD_JObjRemoveAll(jobj);

    if (data->x3C != NULL) {
        HSD_SisLib_803A5CC4(data->x3C);
        data->x3C = NULL;
    }
}
void mnName_8023A058(HSD_GObj* gobj)
{
    MnNameData* data = (MnNameData*) gobj;
    HSD_JObj* obj;
    HSD_JObj* jobj;

    obj = data->x30;
    if (obj == NULL) {
        jobj = NULL;
    } else {
        jobj = obj->child;
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

bool IsNameNotAllowed(char* name)
{
    char** list = NotAllowedNamesList;
    for (;;) {
        char nullChar = mnNameNew_NullCharacter;
        char firstChar = **list;
        if ((s8) nullChar != (s8) firstChar) {
            if (CompareNameStrings(*list, name) == 0) {
                return true;
            }
            list++;
        } else {
            return false;
        }
    }
}