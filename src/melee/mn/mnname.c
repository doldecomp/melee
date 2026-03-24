#include "mnname.h"

#include "mnmain.h"
#include "mnnamenew.h"

#include "lb/lblanguage.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/gm/gmmain_lib.h>

extern AnimLoopSettings mnName_803ED538[];

extern char mnName_StringTerminator;
extern u8 mnName_804D4BF0;

extern f32 mnName_804D4BD0[2];
extern f32 mnName_804D4BD8[2];
extern s32 mnName_804D4BE0;
extern s32 mnName_804D4BE4;

extern char* mnNameNew_803EE720[];
extern char* mnNameNew_803EE724[];

void fn_80249A1C(HSD_GObj* arg0);

#pragma push
#pragma opt_common_subs off
char* mnName_8023749C(int slot)
{
    int j;
    s8 terminator;
    unsigned short new_var;
    char** array;
    s8 term;
    char* str;

    if (lbLang_IsSavedLanguageUS()) {
        array = mnNameNew_803EE724;
    } else {
        array = mnNameNew_803EE720;
    }

    term = (s8) mnName_StringTerminator;
    new_var = (u8) slot;
    for (j = 0; (j != new_var) && (term != ((s8) array[j][0])); j++) {
    }

    str = array[j];
    terminator = (s8) mnName_StringTerminator;
    if (terminator == str[0]) {
        str = NULL;
    }
    return str;
}
#pragma pop

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
s32 CompareNameStrings(char* str, s32 slot)
{
    char* p2 = (char*) slot;
    char* p1 = str;
    s32 i = 0;

    while (true) {
        char* cur = &str[i];

        if ((s8) mnName_StringTerminator == (s8)(u8) *cur) {
            char* rem = (char*) (slot + i);
            s32 result = 1;
            while ((s8) mnName_StringTerminator != (s8)(u8) *rem) {
                if ((s8) mnName_804D4BF0 != (s8)(u8) *rem ||
                    (s8) (&mnName_804D4BF0)[1] != (s8) rem[1])
                {
                    result = 0;
                    break;
                }
                rem += 2;
            }
            if (result != 0) {
                return 0;
            }
            return 2;
        }

        {
            u8 ch2 = (u8) *p2;
            if ((s8) mnName_StringTerminator == (s8) ch2) {
                s32 result = 1;
                while ((s8) mnName_StringTerminator != (s8)(u8) *cur) {
                    if ((s8) mnName_804D4BF0 != (s8)(u8) *cur ||
                        (s8) (&mnName_804D4BF0)[1] != (s8) cur[1])
                    {
                        result = 0;
                        break;
                    }
                    cur += 2;
                }
                if (result != 0) {
                    return 0;
                }
                return 1;
            }

            {
                u8 c1 = (u8) *p1;
                if (c1 > ch2) {
                    return 1;
                }
                if (c1 < ch2) {
                    return 2;
                }
            }
        }

        i++;
        p1++;
        p2++;
    }
}

void fn_802377A4(void) {}

bool IsNameUnique(s32 slot)
{
    int i;
    char* namedata;
    for (i = 0; i < 0x78; i++) {
        namedata = !IsNameValid(i & 0xFF)
                       ? (char*) NULL
                       : GetPersistentNameData((u8) i)->namedata;
        if (namedata == NULL) {
            break;
        }
        if (CompareNameStrings(namedata, slot) == 0) {
            return true;
        }
    }
    return false;
}

s32 DeleteName(u8 arg0)
{
    struct NameTagData temp;
    s32 i;
    u8 pos;
    s32 j;
    s32 k;
    u16* p;

    pos = arg0;
    i = 0;
    do {
        if (IsNameValid((s32) (u8) i) != 0) {
            p = (u16*) ((u8*) GetPersistentNameData(i) + pos * 2);
            for (k = pos; k < 0x78; k++) {
                if (k == 0x77) {
                    *p = 0;
                } else {
                    *p = *(p + 1);
                }
                p++;
            }
        }
        i++;
    } while (i < 0x78);

    while ((s32) pos < 0x78) {
        u8 pos_u8 = (u8) pos;
        j = pos + 1;
        while (j < 0x78) {
            if (IsNameValid((s32) (u8) pos) == 0) {
                if (IsNameValid((s32) (u8) j) != 0) {
                    temp = *GetPersistentNameData((s32) pos_u8);
                    *GetPersistentNameData((s32) pos_u8) =
                        *GetPersistentNameData((s32) (u8) j);
                    *GetPersistentNameData((s32) (u8) j) = temp;
                }
            }
            j++;
        }
        pos++;
    }
}

bool IsNameValid(int slot)
{
    if (mnName_StringTerminator ==
        (s8) GetPersistentNameData((u8) slot)->namedata[0])
    {
        return false;
    }
    return true;
}

void CreateNameAtIndex(s32 slot)
{
    s32 idx = slot & 0xFF;
    GetPersistentNameData(idx)->namedata[0] = mnName_StringTerminator;
    GetPersistentNameData(idx)->x1A1 = true;
    InitializePersistentNameData(slot);
}
/// #mnName_SortNames

/// #mnName_80237D94
extern HSD_GObj* mnName_804D6BF8;

s32 mnName_80237D94(s32 arg0, u8 arg1)
{
    HSD_GObj* gobj;

    gobj = mnName_804D6BF8->user_data;
    if (arg1 < 0x18U) {
        if (arg0 & 1) {
            if ((arg1 % 6) != 0) {
                return arg1 - 1;
            }
            return arg1 + 5;
        }
        if (arg0 & 2) {
            if ((s32) (arg1 % 6) != 5) {
                return arg1 + 1;
            }
            return arg1 - 5;
        }
        if (arg0 & 8) {
            if ((s32) (arg1 / 6) == 3) {
                if (mnName_GetColumnCount() > 4) {
                    lbAudioAx_80024030(2);
                    if ((s32) (mnName_GetColumnCount() - 1) >
                        (s32) gobj->gx_link)
                    {
                        gobj->gx_link = gobj->gx_link + 1;
                    } else {
                        gobj->gx_link = 0;
                    }
                    mnName_802385A0(gobj);
                }
                return arg1;
            }
            return arg1 + 6;
        }
        if (arg0 & 4) {
            if ((arg1 / 6) == 0) {
                if (mnName_GetColumnCount() > 4) {
                    lbAudioAx_80024030(2);
                    if (gobj->gx_link != 0) {
                        gobj->gx_link = gobj->gx_link - 1;
                    } else {
                        gobj->gx_link =
                            mnName_GetColumnCount() - 1;
                    }
                    mnName_802385A0(gobj);
                }
                return arg1;
            }
            return arg1 - 6;
        }
    } else {
        if (arg0 & 1) {
            if (arg1 == 0x18) {
                return 0x1A;
            }
            return arg1 - 1;
        }
        if (arg0 & 2) {
            if (arg1 == 0x1A) {
                return 0x18;
            }
            return arg1 + 1;
        }
    }
    return arg1;
}

/// #mnName_ConfirmNameDeleteInput

/// #mnName_MainInput

void fn_80238540(HSD_GObj* gobj)
{
    switch ((s32) mn_804A04F0.x10) {
    case 0:
        mnName_MainInput(gobj);
        break;
    case 1:
        mnNameNew_MainInput(gobj);
        break;
    case 2:
        mnName_ConfirmNameDeleteInput(gobj);
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
    s32 count = 0;
    s32 i;
    s32 extra;
    for (i = 0; i < 0x78; i++) {
        if (IsNameValid((u8) i)) {
            count++;
        }
    }
    if (count % 24 != 0) {
        extra = 1;
    } else {
        extra = 0;
    }
    return count / 24 + extra;
}

s32 mnName_GetColumnCount(void)
{
    s32 count;
    s32 extra;
    s32 i;
    count = 0;
    for (i = count; i < 0x78; i++) {
        if (IsNameValid((u8) i)) {
            count++;
        }
    }
    if (count % 6 != 0) {
        extra = 1;
    } else {
        extra = 0;
    }
    PAD_STACK(16);
    return count / 6 + extra;
}

#pragma push
#pragma dont_inline on
void mnName_80238754(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    s32 count = GetNameCount();
    s32 extra;
    s32 col_count;
    f32 f_col;

    if (count % 6 != 0) {
        extra = 1;
    } else {
        extra = 0;
    }
    col_count = count / 6 + extra;
    f_col = (f32) col_count;

    if (f_col > 4.0f) {
        HSD_JObj* scroll_jobj;
        f32 scroll_pos;

        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        scroll_pos = (f32) (u32) gobj->gx_link *
                     (14.0f / (f_col - 1.0f));
        scroll_jobj = gobj->user_data;
        if (scroll_jobj == NULL) {
            __assert("jobj.h", 0x3A4, "jobj");
        }
        scroll_jobj->translate.x = scroll_pos;
        if (!(scroll_jobj->flags & JOBJ_MTX_INDEP_SRT) && scroll_jobj) {
            if (scroll_jobj == NULL) {
                __assert("jobj.h", 0x234, "jobj");
            }
            if ((!(scroll_jobj->flags & 0x800000) &&
                 (scroll_jobj->flags & 0x40)) == 0)
            {
                HSD_JObjSetMtxDirtySub(scroll_jobj);
            }
        }
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}
#pragma pop

HSD_JObj* mnName_802388D4(HSD_GObj* gobj, u8 index)
{
    u8* p = (u8*) gobj;
    HSD_JObj* result;

    if ((u8) index < 0x18) {
        HSD_JObj* jobj = *(HSD_JObj**) (p + 0x30);
        s32 i;

        result = (jobj == NULL) ? NULL : jobj->child;

        for (i = 0; i < (u8) index; i++) {
            result = (result == NULL) ? NULL : result->next;
        }

        return result;
    }

    switch ((u8) index) {
    case 0x18:
        return *(HSD_JObj**) (p + 0x24);
    case 0x19:
        return *(HSD_JObj**) (p + 0x18);
    case 0x1A:
        return *(HSD_JObj**) (p + 0x1C);
    }

    return (HSD_JObj*) gobj;
}

f32 mnName_80238964(u8 index, u8 target, u8 flag)
{
    s32 idx;
    AnimLoopSettings* base = mnName_803ED538;

    if ((u8) target == 0x18) {
        if ((u8) flag) {
            return base[5].start_frame;
        }
        return base[4].start_frame;
    }

    idx = (u8) index;
    switch (idx) {
    case 0x18:
        if ((u8) flag) {
            return base[8].start_frame;
        }
        return base[6].start_frame;
    case 0x19:
    case 0x1A:
        if ((u8) flag) {
            return base[8 + ((u8) index == (u8) target)].start_frame;
        }
        return base[6 + ((u8) index == (u8) target)].start_frame;
    }
}

#pragma push
#pragma dont_inline on
void mnName_80238A04(HSD_GObj* gobj, u8 target, u8 flag)
{
    AnimLoopSettings* base = mnName_803ED538;
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    int i;

    for (i = 0x18; i < 0x1B; i++) {
        jobj = mnName_802388D4(gobj, i);
        HSD_JObjReqAnimAll(jobj, mnName_80238964(i, target, flag));
        HSD_JObjAnimAll(jobj);
    }

    jobj2 = (HSD_JObj*) gobj->prev_gx;

    if ((u8) target == 0x18) {
        if ((u8) flag) {
            HSD_JObjReqAnimAll(jobj2, base[5].start_frame);
        } else {
            HSD_JObjReqAnimAll(jobj2, base[4].start_frame);
        }
    } else {
        if ((u8) flag) {
            HSD_JObjReqAnimAll(jobj2, base[8].start_frame);
        } else {
            HSD_JObjReqAnimAll(jobj2, base[6].start_frame);
        }
    }
    HSD_JObjAnimAll(jobj2);
}
#pragma pop

#pragma push
#pragma dont_inline on
void mnName_80238AE0(HSD_GObj* gobj, u8 index, u8 arg2)
{
    s32 color;
    HSD_JObj* jobj;
    s32* colorptr;

    if ((u8) index < 0x18) {
        jobj = mnName_802388D4(gobj, index);
        HSD_JObjReqAnimAll(jobj, (f32) arg2);
        HSD_JObjAnimAll(jobj);
        if (arg2 != 0) {
            colorptr = &mnName_804D4BE0;
        } else {
            colorptr = &mnName_804D4BE4;
        }
        color = *colorptr;
        HSD_SisLib_803A74F0(((MnName_GObj*) gobj)->text, (s32) index,
                            (u8*) &color);
        return;
    }

    jobj = mnName_802388D4(gobj, index);
    if ((u8) index < 0x18) {
        HSD_JObjReqAnimAll(jobj, (f32) arg2);
    } else {
        switch ((u8) index) {
        case 24:
            HSD_JObjReqAnimAll(jobj, mnName_804D4BD0[arg2]);
            break;
        case 25:
            HSD_JObjReqAnimAll(jobj, mnName_804D4BD8[arg2]);
            break;
        case 26:
            HSD_JObjReqAnimAll(jobj, mnName_804D4BD8[arg2]);
            break;
        }
    }
    HSD_JObjAnimAll(jobj);
}
#pragma pop

/// #mnName_80238C34

/// #fn_80239574

/// #mnName_80239878
#pragma push
#pragma dont_inline on
void mnName_80239878(u8 arg0, HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    s32 count;
    s32 extra;
    s32 col_count;
    f32 f_col;

    if (arg0 == 1) {
        mnName_80239FFC(gobj);
        HSD_JObjSetFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
        return;
    }

    mnName_8023A058(gobj);
    jobj = gobj->hsd_obj;
    count = GetNameCount();
    if (count % 6 != 0) {
        extra = 1;
    } else {
        extra = 0;
    }
    col_count = count / 6 + extra;
    f_col = (f32) col_count;

    if (f_col > 4.0f) {
        HSD_JObj* scroll_jobj;
        f32 scroll_pos;

        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        scroll_jobj = gobj->user_data;
        scroll_pos = (f32) gobj->gx_link *
                     (14.0f / (f_col - 1.0f));
        if (scroll_jobj == NULL) {
            __assert("jobj.h", 0x3A4, "jobj");
        }
        scroll_jobj->translate.x = scroll_pos;
        if (!(scroll_jobj->flags & JOBJ_MTX_INDEP_SRT) && scroll_jobj) {
            if (scroll_jobj == NULL) {
                __assert("jobj.h", 0x234, "jobj");
            }
            if ((!(scroll_jobj->flags & 0x800000) &&
                 (scroll_jobj->flags & 0x40)) == 0)
            {
                HSD_JObjSetMtxDirtySub(scroll_jobj);
            }
        }
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}
#pragma pop

/// #mnName_80239A24

void mnName_80239EBC(HSD_JObj* jobj, f32 y)
{
    HSD_JObjSetTranslateY(jobj, y);
}

void mnName_80239F5C(HSD_JObj* jobj, f32 x)
{
    HSD_JObjSetTranslateX(jobj, x);
}

void mnName_80239FFC(HSD_GObj* gobj)
{
    MnName_GObj* mn = (MnName_GObj*) gobj;
    HSD_JObj* jobj = (HSD_JObj*) mn->gobj.user_data_remove_func;
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    HSD_JObjRemoveAll(child);

    if (mn->text != NULL) {
        HSD_SisLib_803A5CC4(mn->text);
        mn->text = NULL;
    }
}

void mnName_8023A058(HSD_GObj* gobj)
{
    u8* p = (u8*) gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;

    jobj = *(HSD_JObj**) (p + 0x30);
    if (jobj == NULL) {
        child = NULL;
    } else {
        child = *(HSD_JObj**) ((u8*) jobj + 0x10);
    }
    HSD_JObjRemoveAll(child);

    if (*(void**) (p + 0x3C) != NULL) {
        HSD_SisLib_803A5CC4(*(void**) (p + 0x3C));
        *(void**) (p + 0x3C) = NULL;
    }

    mnName_80239A24(gobj);
}

/// #fn_8023A0BC

/// #mnName_8023A290

/// #mnName_8023A59C

/// #mnName_8023A9B4

/// #mnName_8023AC40

extern char** NotAllowedNamesList;
extern char mnNameNew_NullCharacter;

bool IsNameNotAllowed(s32 name_idx)
{
    char** list = NotAllowedNamesList;
    while (true) {
        if (mnNameNew_NullCharacter == **list) {
            break;
        }
        if (!CompareNameStrings(*list, name_idx)) {
            return true;
        }
        list++;
    }
    return false;
}
