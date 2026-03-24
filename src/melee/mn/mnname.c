#include "mnname.h"

#include "mnmain.h"
#include "mnmainrule.h"
#include "mnnamenew.h"

#include "lb/lblanguage.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <melee/gm/gmmain_lib.h>

extern AnimLoopSettings mnName_803ED538[];
extern f32 mnName_803ED600[];

extern char mnName_StringTerminator;
extern u8 mnName_804D4BF0;

static u8 mnName_NameDisplayOrder[0x78];

extern f32 mnName_804D4BD0[2];
extern f32 mnName_804D4BD8[2];
extern s32 mnName_804D4BE0;
extern s32 mnName_804D4BE4;
extern s32 mnName_804D4BE8[];

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

void mnName_ConfirmNameDeleteInput(HSD_GObj* arg0)
{
    HSD_GObj* gobj2 = (HSD_GObj*) mnName_804D6BF8->user_data;
    u32 buttons = mn_80229624(4U);
    mn_804A04F0.buttons = buttons;

    if (buttons & 0x10) {
        if ((u8) mn_804A04F0.confirmed_selection == 0) {
            lbAudioAx_80024030(0);
            mn_804D6BC8.cooldown = 5;
            mn_804A04F0.x10 = 0;
            return;
        }
        {
            u8 sel = (u8) mn_804A04F0.hovered_selection;
            s32 col = gobj2->gx_link +
                      (mn_804A04F0.hovered_selection / 6);
            s32 colCount = mnName_GetColumnCount();
            u8 nameIdx;
            if (colCount > 4 && col >= colCount) {
                col -= colCount;
            }
            nameIdx = mnName_NameDisplayOrder[col * 6 + (sel % 6)];
            lbAudioAx_80024030(1);
            {
                u8 term = mnName_StringTerminator;
                mn_804D6BC8.cooldown = 5;
                GetPersistentNameData((s32) nameIdx)->namedata[0] =
                    term;
            }
            GetPersistentNameData((s32) nameIdx)->x1A1 = 1;
            InitializePersistentNameData((s32) nameIdx);
            if ((s32) gobj2->gx_link >
                (s32) (mnName_GetColumnCount() - 1))
            {
                gobj2->gx_link = 0;
            }
            DeleteName(nameIdx);
            mnName_SortNames(mnName_804D6BF8);
            if (mnName_GetColumnCount() <= 4) {
                gobj2->gx_link = 0;
            }
            mnName_802385A0(gobj2);
            gmMainLib_8015DBF4(nameIdx);
            mn_804A04F0.x10 = 0;
        }
        return;
    }
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.x10 = 0;
        return;
    }
    if ((buttons & 8) || (buttons & 4)) {
        lbAudioAx_80024030(2);
        if ((u8) mn_804A04F0.confirmed_selection == 0) {
            mn_804A04F0.confirmed_selection = 1;
            return;
        }
        mn_804A04F0.confirmed_selection = 0;
    }
}

#pragma push
#pragma dont_inline on
void mnName_MainInput(HSD_GObj* arg0)
{
    MnName_GObj* gobj2 = (MnName_GObj*) mnName_804D6BF8->user_data;
    u32 buttons = mn_80229624(4U);
    s32 isFull = 0;
    mn_804A04F0.buttons = buttons;

    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804D6BC8.cooldown = 5;
        if ((u16) mn_804A04F0.hovered_selection < 0x18U) {
            mn_804A04F0.hovered_selection = 0x1A;
            mnName_80238A04((HSD_GObj*) gobj2, 0x1AU, 0U);
            return;
        }
        mn_804A04F0.entering_menu = 0;
        HSD_SisLib_803A5D30();
        mn_80229894(2, 4U, 3);
        return;
    }
    if (buttons & 0x10) {
        mn_804D6BC8.cooldown = 5;
        switch ((s32) mn_804A04F0.hovered_selection) {
        case 24:
            if (GetNameCount() < 0x78) {
            } else {
                isFull = 1;
            }
            if (isFull == 0) {
                s32 isValid;
                u8 count = 0;
                u8 i = 0;
                lbAudioAx_80024030(1);
                mnName_80239878(1U, (HSD_GObj*) gobj2);
                mnName_80238A04((HSD_GObj*) gobj2, 0x18U, 1U);
                HSD_SisLib_803A5CC4(gobj2->text2);
                do {
                    if ((s8) mnName_StringTerminator ==
                        (s8) GetPersistentNameData((s32) i)
                                 ->namedata[0])
                    {
                        isValid = 0;
                    } else {
                        isValid = 1;
                    }
                    if (isValid != 0) {
                        count += 1;
                    }
                    i += 1;
                } while ((s32) i < 0x78);
                mnNameNew_EnterFromMnName((void*)(s32) count);
                return;
            }
            lbAudioAx_80024030(3);
            return;
        case 25:
            if (mnName_GetPageCount() != 0) {
                lbAudioAx_80024030(1);
                if ((u8) gobj2->gobj.p_priority == 0) {
                    isFull = 1;
                }
                gobj2->gobj.p_priority = (u8) isFull;
                mnName_SortNames(mnName_804D6BF8);
                gobj2->gobj.gx_link = 0U;
                mnName_802385A0((HSD_GObj*) gobj2);
                return;
            }
            lbAudioAx_80024030(3);
            return;
        case 26:
            if (mnName_GetPageCount() != 0) {
                lbAudioAx_80024030(1);
                mn_804A04F0.hovered_selection = 0;
                mnName_80238A04((HSD_GObj*) gobj2, 0x1AU, 1U);
                return;
            }
            lbAudioAx_80024030(3);
            return;
        default:
            if ((u16) mn_804A04F0.hovered_selection < 0x18U) {
                s32 isValid;
                u8 sel = (u8) mn_804A04F0.hovered_selection;
                s32 col = gobj2->gobj.gx_link +
                          (mn_804A04F0.hovered_selection / 6);
                s32 colCount = mnName_GetColumnCount();
                u8 nameIdx;
                if (colCount > 4 && col >= colCount) {
                    col -= colCount;
                }
                nameIdx = mnName_NameDisplayOrder[col * 6 + (sel % 6)];
                if ((s8) mnName_StringTerminator ==
                    (s8) GetPersistentNameData((s32) nameIdx)
                             ->namedata[0])
                {
                    isValid = 0;
                } else {
                    isValid = 1;
                }
                if (isValid != 0) {
                    lbAudioAx_80024030(1);
                    mn_804A04F0.x10 = 2;
                    mn_804A04F0.confirmed_selection = 0;
                    mnName_8023A290();
                    return;
                }
                lbAudioAx_80024030(3);
                return;
            }
            break;
        }
    } else {
        u32 isL = buttons & 0x40;
        if (isL != 0 || (buttons & 0x80)) {
            if (mnName_GetColumnCount() > 4) {
                lbAudioAx_80024030(2);
                if (isL != 0) {
                    u8 scroll = gobj2->gobj.gx_link;
                    if (scroll != 0) {
                        gobj2->gobj.gx_link = (u8) (scroll - 1);
                    } else {
                        gobj2->gobj.gx_link =
                            (u8) (mnName_GetColumnCount() - 1);
                    }
                } else {
                    u8 scroll = gobj2->gobj.gx_link;
                    if ((s32) (mnName_GetColumnCount() - 1) >
                        (s32) scroll)
                    {
                        gobj2->gobj.gx_link = (u8) (scroll + 1);
                    } else {
                        gobj2->gobj.gx_link = 0U;
                    }
                }
                mnName_802385A0((HSD_GObj*) gobj2);
            }
        } else if (buttons & 0xF) {
            u8 prev = (u8) mn_804A04F0.hovered_selection;
            mn_804A04F0.hovered_selection =
                (u16) mnName_80237D94((s32) buttons, prev);
            if ((s32) prev !=
                (s32) mn_804A04F0.hovered_selection)
            {
                lbAudioAx_80024030(2);
            }
        }
    }
}
#pragma pop

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

#pragma push
#pragma dont_inline on
void fn_80239574(HSD_GObj* arg0)
{
    AnimLoopSettings* anim;
    AnimLoopSettings* base = mnName_803ED538;
    s32 doUpdate = 0;
    u8 doSel = 0;
    u8 doSelReset = 0;
    MnName_GObj* data = (MnName_GObj*) arg0->user_data;
    u8 state = data->gobj.p_link;

    if ((state == 0 || state == 1 || state == 3) &&
        *((u8*) data) != (u8) mn_804A04F0.cur_menu)
    {
        if (mn_804A04F0.buttons & 0x10) {
            data->gobj.p_link = 4U;
        } else if (mn_804A04F0.buttons & 0x20) {
            data->gobj.p_link = 2U;
        }
        state = data->gobj.p_link;
        switch ((s32) state) {
        case 1:
            anim = &base[0];
            break;
        case 2:
            anim = &base[2];
            break;
        case 3:
            anim = &base[1];
            break;
        case 4:
            anim = &base[3];
            break;
        }
        {
            HSD_JObj* jobj = (HSD_JObj*) data->gobj.next_gx;
            HSD_JObjReqAnim(jobj, anim->start_frame);
            HSD_JObjAnim(jobj);
        }
        state = data->gobj.p_link;
        if (state == 0 || state == 1 || state == 3) {
            doUpdate = 1;
            doSel = 1;
            doSelReset = 1;
        }
    }
    state = data->gobj.p_link;
    if (state != 0) {
        switch ((s32) state) {
        case 1:
            anim = &base[0];
            break;
        case 2:
            anim = &base[2];
            break;
        case 3:
            anim = &base[1];
            break;
        case 4:
            anim = &base[3];
            break;
        }
        {
            HSD_JObj* jobj = (HSD_JObj*) data->gobj.next_gx;
            if (mn_8022F298(jobj) >= anim->end_frame) {
                state = data->gobj.p_link;
                switch ((s32) state) {
                case 3:
                case 1:
                    data->gobj.p_link = 0U;
                    goto do_anim;
                case 4:
                    HSD_GObjPLink_80390228(arg0);
                    return;
                }
            } else {
            do_anim:
                HSD_JObjAnim(jobj);
                goto do_update;
            }
        }
    } else {
    do_update:
        if ((u8) mn_804A04F0.x10 != 1) {
            state = data->gobj.p_link;
            if ((state == 0 || state == 1 || state == 3) &&
                (s32) *((u8*) data + 1) !=
                    (s32) mn_804A04F0.hovered_selection)
            {
                doSel = 1;
            }
        }
        mnName_80238C34(arg0, doSel, doSelReset);
        if ((s32) doSel != 0 &&
            (u16) mn_804A04F0.hovered_selection >= 0x18U &&
            (u8) *((u8*) data + 1) >= 0x18U)
        {
            HSD_Text* text;
            s32 idx = mn_804A04F0.hovered_selection - 0x18;
            if (data->text2 != NULL) {
                HSD_SisLib_803A5CC4(data->text2);
            }
            text = HSD_SisLib_803A5ACC(0, 0, -9.5f, 9.1f, 17.0f,
                                       364.68332f, 38.38772f);
            data->text2 = text;
            text->font_size.x = 0.0521f;
            text->font_size.y = 0.0521f;
            HSD_SisLib_803A6368(text, mnName_804D4BE8[idx]);
        }
        if (doUpdate != 0) {
            *((u8*) data) = (u8) mn_804A04F0.cur_menu;
        }
        if ((s32) doSel != 0) {
            *((u8*) data + 1) = (u8) mn_804A04F0.hovered_selection;
        }
    }
}
#pragma pop

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
extern HSD_Text* mnName_804D6BFC;

void fn_8023A0BC(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    HSD_JObj* sp2C;
    HSD_JObj* sp28;
    HSD_JObj* sp18;
    HSD_JObj* sp14;
    f32 frame;
    f32 frame2;
    u8 sel;
    u8* base;
    HSD_Text* text;

    jobj = gobj->hsd_obj;
    base = (u8*) mnName_803ED538;
    lb_80011E24(jobj, &sp2C, 2, -1);

    if ((u8) mn_804A04F0.x10 != 2) {
        HSD_SisLib_803A5CC4(mnName_804D6BFC);
        mnName_804D6BFC = NULL;
        HSD_GObjPLink_80390228(gobj);
        return;
    }

    frame = mn_8022F298(sp2C);
    if (*(f32*) (base + 0xC8) <= frame &&
        frame < *(f32*) (base + 0xCC))
    {
        frame2 = mn_8022EFD8(sp2C,
                             (AnimLoopSettings*) (base + 0xC8));
        lb_80011E24(jobj, &sp28, 8, -1);
        mn_8022EFD8(sp28, (AnimLoopSettings*) (base + 0xC8));
        if (frame2 >= *(f32*) (base + 0xCC)) {
            if (mnName_804D6BFC != NULL) {
                HSD_SisLib_803A5CC4(mnName_804D6BFC);
            }
            text = HSD_SisLib_803A5ACC(
                0, 1,
                *(f32*) (base + 0xEC),
                *(f32*) (base + 0xF0),
                *(f32*) (base + 0xF4),
                416.6667f, 33.333336f);
            mnName_804D6BFC = text;
            text->font_size.x = 0.03f;
            text->font_size.y = 0.03f;
            HSD_SisLib_803A6368(text, 0x49);
        }
    } else {
        sel = mn_804A04F0.confirmed_selection;
        lb_80011E24(jobj, &sp14, 6, -1);
        lb_80011E24(jobj, &sp18, 7, -1);
        if ((s32) sel != 0) {
            HSD_JObjReqAnimAll(sp14, 1.0f);
            HSD_JObjReqAnimAll(sp18, 0.0f);
        } else {
            HSD_JObjReqAnimAll(sp14, 0.0f);
            HSD_JObjReqAnimAll(sp18, 1.0f);
        }
        HSD_JObjAnimAll(sp14);
        HSD_JObjAnimAll(sp18);
    }
}

typedef struct {
    HSD_Joint* joint;
    HSD_AnimJoint* anim_joint;
    HSD_MatAnimJoint* matanim_joint;
    HSD_ShapeAnimJoint* shapeanim_joint;
} MnNameArchive;

extern MnNameArchive mnName_804A06D0;

void mnName_8023A290(void)
{
    HSD_JObj* sp28;
    HSD_JObj* sp24;
    HSD_JObj* sp20;
    HSD_JObj* sp18;
    HSD_JObj* sp14;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    u8 sel;

    gobj = GObj_Create(6U, 7U, 0x80U);
    jobj = HSD_JObjLoadJoint(mnName_804A06D0.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6U, 0x80U);
    HSD_GObj_SetupProc(gobj, fn_8023A0BC, 0U);
    HSD_JObjAddAnimAll(jobj, mnName_804A06D0.anim_joint,
                       mnName_804A06D0.matanim_joint,
                       mnName_804A06D0.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, mnName_803ED600[0]);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, &sp28, 0xA, -1);
    HSD_JObjSetFlagsAll(sp28, 0x10U);
    lb_80011E24(jobj, &sp28, 0xB, -1);
    HSD_JObjSetFlagsAll(sp28, 0x10U);
    sel = mn_804A04F0.confirmed_selection;
    lb_80011E24(jobj, &sp14, 6, -1);
    lb_80011E24(jobj, &sp18, 7, -1);
    if ((s32) sel != 0) {
        HSD_JObjReqAnimAll(sp14, 1.0f);
        HSD_JObjReqAnimAll(sp18, 0.0f);
    } else {
        HSD_JObjReqAnimAll(sp14, 0.0f);
        HSD_JObjReqAnimAll(sp18, 1.0f);
    }
    HSD_JObjAnimAll(sp14);
    HSD_JObjAnimAll(sp18);
    if (lbLang_IsSavedLanguageUS()) {
        lb_80011E24(jobj, &sp24, 6, -1);
        lb_80011E24(jobj, &sp20, 7, -1);
        {
            f32 x1 = HSD_JObjGetTranslationX(sp24);
            f32 x2 = HSD_JObjGetTranslationX(sp20);
            HSD_JObjSetTranslateX(sp24, x2);
            HSD_JObjSetTranslateX(sp20, x1);
        }
    }
}

/// #mnName_8023A59C

#pragma push
#pragma dont_inline on
void mnName_8023A9B4(u8 arg0)
{
    s32 i;
    MnName_GObj* gobj2;
    HSD_JObj* jobj;

    mn_804A04F0.hovered_selection = 0x18;
    mn_804A04F0.x10 = 0;
    for (i = 0; i < 0x78; i++) {
        mnName_NameDisplayOrder[i] = (u8) i;
    }
    HSD_GObj_80390CD4(mnName_8023A59C(3));
    gobj2 = (MnName_GObj*) ((HSD_GObj*) mnName_804D6BF8)->user_data;
    if ((u8) mn_804A04F0.x10 == 1) {
        struct mn_80231634_t* p =
            (struct mn_80231634_t*) gobj2->gobj.user_data_remove_func;
        if (p == NULL) {
            jobj = NULL;
        } else {
            jobj = (HSD_JObj*) p->x10;
        }
        HSD_JObjRemoveAll(jobj);
        if (gobj2->text != NULL) {
            HSD_SisLib_803A5CC4(gobj2->text);
            gobj2->text = NULL;
        }
        HSD_JObjSetFlagsAll((HSD_JObj*) gobj2->gobj.hsd_obj, 0x10U);
    } else {
        HSD_JObjRemoveAll(
            (HSD_JObj*) mn_80231634(
                (struct mn_80231634_t*) gobj2->gobj
                    .user_data_remove_func));
        if (gobj2->text != NULL) {
            HSD_SisLib_803A5CC4(gobj2->text);
            gobj2->text = NULL;
        }
        mnName_80239A24((HSD_GObj*) gobj2);
        mnName_80238754((HSD_GObj*) gobj2);
    }
    mnName_80238A04((HSD_GObj*) gobj2, 0x18U, 0U);
    gobj2->gobj.gx_link = arg0;
    mnName_80238754((HSD_GObj*) gobj2);
    HSD_JObjRemoveAll(
        (HSD_JObj*) mn_80231634(
            (struct mn_80231634_t*) gobj2->gobj
                .user_data_remove_func));
    if (gobj2->text != NULL) {
        HSD_SisLib_803A5CC4(gobj2->text);
        gobj2->text = NULL;
    }
    mnName_80239A24((HSD_GObj*) gobj2);
}
#pragma pop

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
