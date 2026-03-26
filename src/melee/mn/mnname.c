#include "mnname.h"

#include "mnmain.h"
#include "mnmainrule.h"
#include "mnnamenew.h"
#include "placeholder.h"

#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"

#include <dolphin/os.h>
#include <baselib/debug.h>
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
extern char mnName_804D4BF0;

static u8 mnName_NameDisplayOrder[0x78];

extern f32 mnName_804D4BD0[2];
extern f32 mnName_804D4BD8[2];
extern s32 mnName_804D4BE0;
extern s32 mnName_804D4BE4;
extern u8 mnName_804D4BE8[3];

extern char* mnNameNew_803EE720[];
extern char* mnNameNew_803EE724[];

extern AnimLoopSettings* mnName_803B8510[];
extern char mnName_804D4C04[8];

typedef struct {
    HSD_Joint* joint;
    HSD_AnimJoint* anim_joint;
    HSD_MatAnimJoint* matanim_joint;
    HSD_ShapeAnimJoint* shapeanim_joint;
} MnNameArchive;

extern MnNameArchive mnName_804A06C0;
extern MnNameArchive mnName_804A06D0;
extern MnNameArchive mnName_804A06E0;
extern Vec3 mnName_803ED618[];

void fn_80249A1C(HSD_GObj* arg0);

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

    new_var = (u8) slot;
    for (j = 0;
         (j != new_var) && (mnName_StringTerminator != ((s8) array[j][0]));
         j++)
    {
    }

    str = array[j];
    terminator = (s8) mnName_StringTerminator;
    if (terminator == str[0]) {
        str = NULL;
    }
    return str;
}

char* GetNameText(int slot)
{
    if (!IsNameValid(slot)) {
        return NULL;
    }
    return GetPersistentNameData((u8) slot)->namedata;
}

static int GetNameCount_noinline(void)
{
    return GetNameCount();
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

inline int GetNumNameList()
{
    int i;
    int count = 0;
    for (i = 0; i < 0x78; i++) {
        if (IsNameValid((u8) i)) {
            count++;
        }
    }
    return count;
}

bool IsNameListFull(void)
{
    if (GetNumNameList() < 0x78) {
        return false;
    }
    return true;
}

inline bool checkStringRest(char* ptr)
{
    char* cmp = &mnName_804D4BF0;
    char c = cmp[0];
    while (mnName_StringTerminator != *ptr) {
        if (c != *ptr || cmp[1] != ptr[1]) {
            return false;
        }
        ptr += 2;
    }
    return true;
}

s32 CompareNameStrings(char* str1, char* str2)
{
    char* p1;
    char* p2;
    s32 i;
    for (i = 0, p2 = str2, p1 = str1;; i++, p1++, p2++) {
        char* ch1 = &str1[i];

        if (mnName_StringTerminator == *ch1) {
            if (checkStringRest(&str2[i & 0xFFFFFFFFFFFFFFFF])) {
                return 0;
            }
            return 2;
        }

        if (mnName_StringTerminator == str2[i]) {
            if (checkStringRest(&str1[i])) {
                return 0;
            }
            return 1;
        }

        if ((u8) *p1 > (u8) str2[i]) {
            return 1;
        }
        if ((u8) *p1 < (u8) str2[i]) {
            return 2;
        }
    }
}

void fn_802377A4(void) {}

bool IsNameUnique(char* name)
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
        if (CompareNameStrings(namedata, name) == 0) {
            return true;
        }
    }
    return false;
}

void DeleteName(u8 arg0)
{
    u8 _2[8];
    struct NameTagData temp;
    s32 i;
    unsigned long long longpos;
    s32 pos;
    s32 j;
    u16* p;
    s32 k;
    u8 pos_u8;
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

    while (pos < 0x78) {
        j = pos + 1;
        while (j < 0x78) {
            longpos = pos;
            if (IsNameValid((s32) ((u8) longpos)) == 0) {
                if (IsNameValid((u8) j) != 0) {
                    temp = *GetPersistentNameData((s32) (u8) pos);
                    *GetPersistentNameData((s32) (u8) pos) =
                        *GetPersistentNameData((s32) ((u8) j));
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

s32 mnName_SortNames(HSD_GObj* arg0)
{
    u8* order = mnName_NameDisplayOrder;
    MnName_GObj* data = (MnName_GObj*) arg0->user_data;
    s32 result;

    if ((u8) data->gobj.p_priority == 0) {
        s32 i;
        for (i = 0; i < 0x78; i++) {
            order[i] = (u8) i;
        }
        return i;
    }

    {
        s32 i;
        u8* pi = mnName_NameDisplayOrder;

        i = 0;
        do {
            s32 j = i + 1;
            u8* pj = &mnName_NameDisplayOrder[i] + 1;

            while (j < 0x78) {
                u8 idx1 = *pi;
                u8 idx2 = *pj;
                char* name1 =
                    (char*) GetPersistentNameData((s32) idx1) + 0x198;
                char* name2 =
                    (char*) GetPersistentNameData((s32) idx2) + 0x198;
                s32 e1, e2;

                if ((s8) mnName_StringTerminator ==
                    (s8) GetPersistentNameData((s32) idx1)->namedata[0])
                {
                    e1 = 0;
                } else {
                    e1 = 1;
                }
                if (e1 != 0) {
                    if ((s8) mnName_StringTerminator ==
                        (s8) GetPersistentNameData((s32) idx2)
                            ->namedata[0])
                    {
                        e2 = 0;
                    } else {
                        e2 = 1;
                    }
                    if (e2 != 0) {
                        result = CompareNameStrings(name1, name2);
                    } else {
                        goto block_15;
                    }
                } else {
                block_15:
                    if ((s8) mnName_StringTerminator ==
                        (s8) GetPersistentNameData((s32) idx1)
                            ->namedata[0])
                    {
                        e1 = 0;
                    } else {
                        e1 = 1;
                    }
                    if (e1 == 0) {
                        if ((s8) mnName_StringTerminator ==
                            (s8) GetPersistentNameData((s32) idx2)
                                ->namedata[0])
                        {
                            e2 = 0;
                        } else {
                            e2 = 1;
                        }
                        if (e2 == 0) {
                            result = 0;
                        } else {
                            goto block_24;
                        }
                    } else {
                    block_24:
                        if ((s8) mnName_StringTerminator ==
                            (s8) GetPersistentNameData((s32) idx1)
                                ->namedata[0])
                        {
                            e1 = 0;
                        } else {
                            e1 = 1;
                        }
                        if (e1 == 0) {
                            result = 1;
                        } else {
                            result = 2;
                        }
                    }
                }
                if (result == 1) {
                    u8 tmp = *pi;
                    *pi = *pj;
                    *pj = tmp;
                }
                pj++;
                j++;
            }
            i++;
            pi++;
        } while (i < 0x78);
    }
    return result;
}

extern HSD_GObj* mnName_804D6BF8;

u8 mnName_80237D94(s32 arg0, u8 arg1)
{
    HSD_GObj* gobj;
    PAD_STACK(8);

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
    PAD_STACK(0x20);
    if (buttons & 0x10) {
        if ((u8) mn_804A04F0.confirmed_selection == 0) {
            lbAudioAx_80024030(0);
            mn_804D6BC8.cooldown = 5;
            mn_804A04F0.x10 = 0;
            return;
        }
        {
            u8 sel = (u8) mn_804A04F0.hovered_selection;
            s32 col = ((HSD_GObj*) mnName_804D6BF8->user_data)->gx_link +
                      ((mn_804A04F0.hovered_selection & 0xFF) / 6);
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

void mnName_MainInput(HSD_GObj* arg0)
{
    MnName_GObj* gobj2 = (MnName_GObj*) mnName_804D6BF8->user_data;
    u32 buttons = mn_80229624(4U);
    s32 isFull = 0;
    PAD_STACK(0x20);
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
            if (GetNameCount_noinline() < 0x78) {
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
    count = GetNumNameList();
    if (count % 6 != 0) {
        extra = 1;
    } else {
        extra = 0;
    }
    PAD_STACK(8);
    return count / 6 + extra;
}

void mnName_80238754(HSD_GObj* gobj)
{
    s32 extra;
    HSD_JObj* jobj = gobj->hsd_obj;
    s32 count = GetNameCount_noinline();
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
        f32 scroll_pos;

        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        scroll_pos = (f32) (u32) gobj->gx_link *
                     (14.0f / (f_col - 1.0f));
        HSD_JObjSetTranslateX(gobj->user_data, scroll_pos);
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

static void mnName_80238754_noinline(HSD_GObj* gobj)
{
    mnName_80238754(gobj);
}

static HSD_JObj* mnName_802388D4_noinline(HSD_GObj* gobj, u8 index)
{
    return mnName_802388D4(gobj, index);
}

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

static f32 mnName_80238964_noinline(u8 index, u8 target, u8 flag)
{
    return mnName_80238964(index, target, flag);
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

void mnName_80238A04(HSD_GObj* gobj, u8 target, u8 flag)
{
    AnimLoopSettings* base = mnName_803ED538;
    HSD_JObj* jobj2;
    int i;
    HSD_JObj* jobj;

    for (i = 0x18; i < 0x1B; i++) {
        jobj = mnName_802388D4_noinline(gobj, i);
        HSD_JObjReqAnimAll(jobj, mnName_80238964_noinline(i, target, flag));
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

void mnName_80238AE0(HSD_GObj* gobj, u8 index, u8 arg2)
{
    s32 color;
    HSD_JObj* jobj;
    s32* colorptr;

    if ((u8) index < 0x18) {
        jobj = mnName_802388D4_noinline(gobj, index);
        HSD_JObjReqAnimAll(jobj, (f32) arg2);
        HSD_JObjAnimAll(jobj);
        if (arg2 != 0) {
            colorptr = &mnName_804D4BE0;
        } else {
            colorptr = &mnName_804D4BE4;
        }
        color = *colorptr;
        HSD_SisLib_803A74F0(((MnName_GObj*) gobj)->text, (s32) index,
                            (0, (u8*) (&color)));
        return;
    }

    jobj = mnName_802388D4_noinline(gobj, index);
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

static inline AnimLoopSettings*
mnName_FindAnimLoop(AnimLoopSettings** tableBase, f32 frame)
{
    AnimLoopSettings* table[6];
    char* msg;
    s32 i;

    table[0] = tableBase[0];
    table[1] = tableBase[1];
    table[2] = tableBase[2];
    table[3] = tableBase[3];
    table[4] = tableBase[4];
    table[5] = tableBase[5];

    for (i = 0; i < 6; i++) {
        if (table[i]->start_frame <= frame && frame <= table[i]->end_frame) {
            return table[i];
        }
    }

    msg = "But AnimFrame!!!\n";
    HSD_ASSERTREPORT(0x3DC, NULL, msg);
}

void mnName_80238C34(HSD_GObj* arg0, u8 arg1, u8 arg2)
{
    AnimLoopSettings** tableBase = mnName_803B8510;
    AnimLoopSettings* base = mnName_803ED538;
    MnName_GObj* data = (MnName_GObj*) arg0->user_data;
    AnimLoopSettings* found;

    if (arg1 != 0) {
        u8 prev = *((u8*) data + 1);
        if (prev != 0x1A || (u16) mn_804A04F0.hovered_selection >= 0x18U) {
            mnName_80238AE0((HSD_GObj*) data, prev, 0);
        }
        mnName_80238AE0((HSD_GObj*) data,
                        (u8) mn_804A04F0.hovered_selection, 1);
    }

    {
        HSD_JObj* jobj = mnName_802388D4((HSD_GObj*) data, 0x18U);
        found = mnName_FindAnimLoop(tableBase, mn_8022F298(jobj));
        mn_8022ED6C(jobj, found);
    }

    {
        HSD_JObj* jobj = mnName_802388D4((HSD_GObj*) data, 0x19U);
        found = mnName_FindAnimLoop(tableBase, mn_8022F298(jobj));
        mn_8022ED6C(jobj, found);
    }

    {
        HSD_JObj* jobj = mnName_802388D4((HSD_GObj*) data, 0x1AU);
        found = mnName_FindAnimLoop(tableBase, mn_8022F298(jobj));
        mn_8022ED6C(jobj, found);
    }

    {
        HSD_JObj* jobj = (HSD_JObj*) data->gobj.prev_gx;
        f32 result;

        found = mnName_FindAnimLoop(tableBase, mn_8022F298(jobj));
        result = mn_8022ED6C(jobj, found);

        found = mnName_FindAnimLoop(tableBase, result);
        if (found == base + 5) {
            if (result >= base[5].end_frame) {
                HSD_GObjPLink_80390228(arg0);
            }
        }
    }
}

void fn_80239574(HSD_GObj* arg0)
{
    AnimLoopSettings* anim;
    HSD_JObj* new_var;
    AnimLoopSettings* base = (0, mnName_803ED538);
    s32 doUpdate = 0;
    int doSel = 0;
    unsigned int doSelReset = 0;
    MnName_GObj* data = (MnName_GObj*) arg0->user_data;
    s32 new_var2;
    u8 state = data->gobj.p_link;
    PAD_STACK(0x8);

    if ((((state == 0) || (data->gobj.p_link == 1)) ||
         (data->gobj.p_link == 3)) &&
        ((*((u8*) data)) != ((u8) mn_804A04F0.cur_menu)))
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
            new_var = jobj;
            if (mn_8022F298(new_var) >= anim->end_frame) {
                state = data->gobj.p_link;
                switch ((s32) state) {
                case 3:
                case 1:
                    data->gobj.p_link = 0U;
                    goto do_anim;
                case 2:
                case 4:
                    HSD_GObjPLink_80390228(arg0);
                    return;
                default:
                    goto do_anim;
                }
            } else {
            do_anim:
                HSD_JObjAnim(new_var);
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
            new_var2 = idx;
            if (data->text2 != NULL) {
                HSD_SisLib_803A5CC4(data->text2);
            }
            text = HSD_SisLib_803A5ACC(0, 0, -9.5f, 9.1f, 17.0f,
                                       364.68332f, 38.38772f);
            data->text2 = text;
            text->font_size.x = 0.0521f;
            text->font_size.y = 0.0521f;
            HSD_SisLib_803A6368(text, mnName_804D4BE8[new_var2]);
        }
        if (doUpdate != 0) {
            *((u8*) data) = (u8) mn_804A04F0.cur_menu;
        }
        if ((s32) doSel != 0) {
            *((u8*) data + 1) = (u8) mn_804A04F0.hovered_selection;
        }
    }
}

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
    count = GetNameCount_noinline();
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
        scroll_pos = (f32) gobj->gx_link *
                     (14.0f / (f_col - 1.0f));
        HSD_JObjSetTranslateX(gobj->user_data, scroll_pos);
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

void mnName_80239A24(HSD_GObj* gobj)
{
    Vec3 sp6C;
    s32 sp60;
    MnName_GObj* data = (MnName_GObj*) gobj;
    HSD_JObj* jobj;
    HSD_JObj* ref_jobj;
    HSD_JObj* ref_jobj2;
    HSD_JObj* ref_jobj3;
    HSD_JObj* text_jobj0;
    HSD_JObj* text_jobj6;
    HSD_JObj* text_jobj1;
    HSD_Text* text;
    f32 col_width;
    f32 row_height;
    f32 text_col_width;
    f32 text_row_height;
    u8 i;
    s32 row;
    s32 count;
    s32 extra;
    s32 total_rows;
    u8 name_idx;

    for (i = 0; i < 0x18; i++) {
        jobj = HSD_JObjLoadJoint(mnName_804A06C0.joint);
        HSD_JObjAddAnimAll(jobj, mnName_804A06C0.anim_joint,
                           mnName_804A06C0.matanim_joint,
                           mnName_804A06C0.shapeanim_joint);
        HSD_JObjReqAnimAll(jobj, (f32) (mn_804A04F0.hovered_selection == i));
        HSD_JObjAnimAll(jobj);
        col_width = HSD_JObjGetTranslationX(
            (HSD_JObj*) data->gobj.user_data_remove_func);
        col_width = HSD_JObjGetTranslationX((HSD_JObj*) data->gobj.x34_unk) -
                    col_width;
        row_height = HSD_JObjGetTranslationY(
            (HSD_JObj*) data->gobj.user_data_remove_func);
        row_height =
            HSD_JObjGetTranslationY((HSD_JObj*) data->x38) - row_height;
        mnName_80239F5C(jobj, col_width * (f32) (i / 6));
        mnName_80239EBC(jobj, row_height * (f32) (i % 6));
        HSD_JObjAddChild((HSD_JObj*) data->gobj.user_data_remove_func, jobj);
    }

    text = HSD_SisLib_803A6754(0, 0);
    data->text = text;
    text_jobj0 = mnName_802388D4_noinline(gobj, 0U);
    lb_8000B1CC(text_jobj0, mnName_803ED618, &sp6C);
    text->pos_x = sp6C.x;
    text->pos_y = -sp6C.y;
    text->pos_z = sp6C.z;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.03f;
    text->text_color = *(GXColor*) &mnName_804D4BE4;

    text_jobj6 = mnName_802388D4_noinline(gobj, 6U);
    text_col_width = HSD_JObjGetTranslationX(text_jobj0);
    text_col_width = HSD_JObjGetTranslationX(text_jobj6) - text_col_width;
    text_jobj1 = mnName_802388D4_noinline(gobj, 1U);
    text_row_height = HSD_JObjGetTranslationY(text_jobj0);
    text_row_height = -(HSD_JObjGetTranslationY(text_jobj1) - text_row_height);

    for (i = 0; i < 0x18; i++) {
        MnName_GObj* global_data =
            (MnName_GObj*) ((HSD_GObj*) mnName_804D6BF8)->user_data;
        row = global_data->gobj.gx_link + (i / 6);
        count = GetNameCount_noinline();
        if ((count % 6) != 0) {
            extra = 1;
        } else {
            extra = 0;
        }
        total_rows = (count / 6) + extra;
        if ((total_rows > 4) && (row >= total_rows)) {
            row -= total_rows;
        }
        name_idx =
            mnName_NameDisplayOrder[(i % 6) + (row * 6)];
        {
            s32 is_valid;
            if ((s8)(u8) mnName_StringTerminator ==
                (s8) GetPersistentNameData((s32) name_idx)->namedata[0])
            {
                is_valid = 0;
            } else {
                is_valid = 1;
            }
            if (is_valid != 0) {
                char* namedata;
                s32 is_valid2;
                if ((s8)(u8) mnName_StringTerminator ==
                    (s8) GetPersistentNameData((s32) name_idx)
                        ->namedata[0])
                {
                    is_valid2 = 0;
                } else {
                    is_valid2 = 1;
                }
                if (is_valid2 == 0) {
                    namedata = NULL;
                } else {
                    namedata = (char*) GetPersistentNameData(
                                   (s32) name_idx) +
                               0x198;
                }
                {
                    f32 font_x = text->font_size.x;
                    f32 x = (f32) (i / 6) * text_col_width;
                    HSD_SisLib_803A6B98(
                        text, x / font_x,
                        ((f32) (i % 6) * text_row_height) /
                            text->font_size.y,
                        namedata);
                }
                {
                    s32* color;
                    if ((s32) i ==
                        (s32) mn_804A04F0.hovered_selection)
                    {
                        color = &mnName_804D4BE0;
                    } else {
                        color = &mnName_804D4BE4;
                    }
                    sp60 = *color;
                    HSD_SisLib_803A74F0(text, (s32) i,
                                        (u8*) &sp60);
                }
            } else {
                HSD_SisLib_803A6B98(text, 0.0f, 0.0f,
                                    &mnName_StringTerminator);
            }
        }
    }
}

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

extern HSD_Text* mnName_804D6BFC;
void fn_8023A0BC(HSD_GObj* gobj)
{
    f32* end_frame;
    HSD_JObj* jobj;
    HSD_JObj* sp2C;
    HSD_JObj* sp28;
    u32 pad1;
    u32 pad2;
    u32 pad3;
    HSD_JObj* sp18;
    HSD_JObj* sp14;
    f32 frame;
    f32 frame2;
    f32* new_var;
    u8 sel;
    u8* base;
    u32 pad4;
    u32 pad5;
    HSD_Text* text;

    jobj = gobj->hsd_obj;
    base = (u8*) mnName_803ED538;
    lb_80011E24(jobj, &sp2C, 2, -1);

    if (((u8) (sel = mn_804A04F0.x10)) != 2) {
        HSD_SisLib_803A5CC4(mnName_804D6BFC);
        mnName_804D6BFC = NULL;
        HSD_GObjPLink_80390228(gobj);
        return;
    }

    frame = mn_8022F298(sp2C);
    if (*(f32*) (base + 0xC8) <= frame) {
        end_frame = (f32*) (base + 0xCC);
        if (frame < (*(new_var = (f32*) (base + 0xCC)))) {
            frame2 = mn_8022EFD8(sp2C, (AnimLoopSettings*) (base + 0xC8));
            lb_80011E24(jobj, &sp28, 8, -1);
            mn_8022EFD8(sp28, (AnimLoopSettings*) (base + 0xC8));
            if (frame2 >= *end_frame) {
                if (mnName_804D6BFC != NULL) {
                    HSD_SisLib_803A5CC4(mnName_804D6BFC);
                }
                text = HSD_SisLib_803A5ACC(
                    0, 1, *(f32*) (base + 0xEC), *(f32*) (base + 0xF0),
                    *(f32*) (base + 0xF4), 416.6667f, 33.333336f);
                mnName_804D6BFC = text;
                text->font_size.x = 0.03f;
                text->font_size.y = 0.03f;
                HSD_SisLib_803A6368(text, 0x49);
            }
        } else {
            goto else_block;
        }
    } else {
    else_block:
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

/// @todo Strings at base offsets are in rodata near mnName_803ED538

HSD_GObj* mnName_8023A59C(u8 arg0)
{
    char* base = (char*) &mnName_803ED538;
    HSD_GObj* gobj;
    HSD_JObj* root_jobj;
    MnName_GObj* user_data;
    HSD_JObj* jobj5;
    MnNameArchive* archive = &mnName_804A06E0;
    s32 i;
    HSD_JObj* jobj7;
    HSD_JObj* jobj4;
    HSD_JObj* scrollbar_container;
    HSD_JObj* slider;
    s32 count;
    s32 extra;
    f32 rows;
    f32 pos;
    HSD_Text* txt;
    PAD_STACK(0x18);

    gobj = GObj_Create(6U, 7U, 0x80U);
    mnName_804D6BF8 = gobj;
    root_jobj = HSD_JObjLoadJoint(archive->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root_jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4U, 0x80U);
    HSD_GObj_SetupProc(gobj, fn_80239574, 0U);
    HSD_JObjAddAnimAll(root_jobj, archive->anim_joint,
                       archive->matanim_joint,
                       archive->shapeanim_joint);
    HSD_JObjReqAnimAll(root_jobj, 0.0f);
    HSD_JObjAnimAll(root_jobj);
    user_data = (MnName_GObj*) HSD_MemAlloc(0x44);
    HSD_ASSERTREPORT(0x67CU, user_data, "Can't get user_data.\n");
    GObj_InitUserData(gobj, 0U, HSD_Free, user_data);
    *(u8*) &user_data->gobj.classifier = (u8) mn_804A04F0.cur_menu;
    *((u8*) &user_data->gobj.classifier + 1) =
        (u8) mn_804A04F0.hovered_selection;
    user_data->gobj.gx_link = 0;
    user_data->gobj.p_priority = 0;
    user_data->gobj.p_link = arg0;
    user_data->text = NULL;
    user_data->text2 = NULL;
    for (i = 0; i < 0xD; i++) {
        lb_80011E24(root_jobj, (HSD_JObj**) ((u8*) user_data + (i << 2) + 8),
                    i, -1);
    }
    if ((u8) mn_804A04F0.x10 == 1) {
        struct mn_80231634_t* p =
            (struct mn_80231634_t*) user_data->gobj.user_data_remove_func;
        HSD_JObj* j;
        if (p == NULL) {
            j = NULL;
        } else {
            j = (HSD_JObj*) p->x10;
        }
        HSD_JObjRemoveAll(j);
        if (user_data->text != NULL) {
            HSD_SisLib_803A5CC4(user_data->text);
            user_data->text = NULL;
        }
        HSD_JObjSetFlagsAll((HSD_JObj*) user_data->gobj.hsd_obj, 0x10U);
    } else {
        HSD_JObjRemoveAll((HSD_JObj*) mn_80231634(
            (struct mn_80231634_t*) user_data->gobj.user_data_remove_func));
        if (user_data->text != NULL) {
            HSD_SisLib_803A5CC4(user_data->text);
            user_data->text = NULL;
        }
        mnName_80239A24((HSD_GObj*) user_data);
        mnName_80238754_noinline((HSD_GObj*) user_data);
    }
    jobj7 = ((HSD_JObj**) user_data)[9];
    HSD_JObjReqAnimAll(jobj7,
                       mnName_804D4BD0[mn_804A04F0.hovered_selection == 0x18]);
    HSD_JObjAnimAll(jobj7);
    jobj4 = (HSD_JObj*) user_data->gobj.proc;
    HSD_JObjReqAnimAll(jobj4,
                       mnName_804D4BD8[mn_804A04F0.hovered_selection == 0x19]);
    HSD_JObjAnimAll(jobj4);
    jobj5 = (HSD_JObj*) user_data->gobj.render_cb;
    HSD_JObjReqAnimAll(jobj5,
                       mnName_804D4BD8[mn_804A04F0.hovered_selection == 0x1A]);
    HSD_JObjAnimAll(jobj5);
    scrollbar_container = (HSD_JObj*) user_data->gobj.hsd_obj;
    count = GetNameCount_noinline();
    if ((count % 6) != 0) {
        extra = 1;
    } else {
        extra = 0;
    }
    rows = (count / 6) + extra;
    if (rows > 4.0f) {
        HSD_JObjClearFlagsAll(scrollbar_container, JOBJ_HIDDEN);
        pos = ((f32) user_data->gobj.gx_link) * (14.0f / (rows - 1.0f));
        HSD_JObjSetTranslateX((HSD_JObj*) user_data->gobj.user_data, pos);
    } else {
        HSD_JObjSetFlagsAll(scrollbar_container, JOBJ_HIDDEN);
    }
    {
        s32 sel = mn_804A04F0.hovered_selection - 0x18;
        if (user_data->text2 != NULL) {
            HSD_SisLib_803A5CC4(user_data->text2);
        }
        txt = HSD_SisLib_803A5ACC(0, 0, -9.5f, 9.1f, 17.0f, 364.68332f,
                                  38.38772f);
        user_data->text2 = txt;
        txt->font_size.x = 0.0521f;
        txt->font_size.y = 0.0521f;
        HSD_SisLib_803A6368(txt, mnName_804D4BE8[sel]);
    }
    return gobj;
}

void mnName_8023A9B4(u8 arg0)
{
    u32 i;
    MnName_GObj* gobj2;
    HSD_JObj* jobj;
    mn_804A04F0.hovered_selection = 0x18;
    mn_804A04F0.x10 = (i = 0);
    PAD_STACK(0x8);

    for (i = 0; i < 0x78; i++) {
        mnName_NameDisplayOrder[i] = (u8) i;
    }
    HSD_GObj_80390CD4(mnName_8023A59C(3));
    gobj2 = (0, (MnName_GObj*) ((HSD_GObj*) mnName_804D6BF8)->user_data);
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
        mnName_80238754_noinline((HSD_GObj*) gobj2);
    }
    mnName_80238A04((HSD_GObj*) gobj2, 0x18U, (0, 0U));
    gobj2->gobj.gx_link = arg0;
    mnName_80238754_noinline((HSD_GObj*) gobj2);
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

extern char** AutoNamesList;
extern char** NotAllowedNamesList;
extern HSD_Text* mnName_804D6BFC;

s32 mnName_8023AC40(void)
{
    HSD_Archive* archive = mn_804D6BB8;
    u8* ptr = mnName_NameDisplayOrder;
    s32 ctr;
    s32 val;
    HSD_GObjProc* proc;

    lbArchive_LoadSections(
        archive,
        (void**) ((char*) mnName_NameDisplayOrder + 0x98),
        (char*) mnName_803ED538 + 0x13C,
        (void**) ((char*) mnName_NameDisplayOrder + 0x9C),
        (char*) mnName_803ED538 + 0x158,
        (void**) ((char*) mnName_NameDisplayOrder + 0xA0),
        (char*) mnName_803ED538 + 0x178,
        (void**) ((char*) mnName_NameDisplayOrder + 0xA4),
        (char*) mnName_803ED538 + 0x19C,
        (void**) ((char*) mnName_NameDisplayOrder + 0x78),
        (char*) mnName_803ED538 + 0x1C0,
        (void**) ((char*) mnName_NameDisplayOrder + 0x7C),
        (char*) mnName_803ED538 + 0x1DC,
        (void**) ((char*) mnName_NameDisplayOrder + 0x80),
        (char*) mnName_803ED538 + 0x1FC,
        (void**) ((char*) mnName_NameDisplayOrder + 0x84),
        (char*) mnName_803ED538 + 0x220,
        (void**) ((char*) mnName_NameDisplayOrder + 0x88),
        (char*) mnName_803ED538 + 0x244,
        (void**) ((char*) mnName_NameDisplayOrder + 0x8C),
        (char*) mnName_803ED538 + 0x25C,
        (void**) ((char*) mnName_NameDisplayOrder + 0x90),
        (char*) mnName_803ED538 + 0x278,
        (void**) ((char*) mnName_NameDisplayOrder + 0x94),
        (char*) mnName_803ED538 + 0x298,
        (void**) ((char*) mnName_NameDisplayOrder + 0xA8),
        (char*) mnName_803ED538 + 0x2BC,
        (void**) ((char*) mnName_NameDisplayOrder + 0xAC),
        (char*) mnName_803ED538 + 0x2D8,
        (void**) ((char*) mnName_NameDisplayOrder + 0xB0),
        (char*) mnName_803ED538 + 0x2F8,
        (void**) ((char*) mnName_NameDisplayOrder + 0xB4),
        (char*) mnName_803ED538 + 0x31C,
        (void**) ((char*) mnName_NameDisplayOrder + 0xB8),
        (char*) mnName_803ED538 + 0x340,
        (void**) ((char*) mnName_NameDisplayOrder + 0xBC),
        (char*) mnName_803ED538 + 0x35C,
        (void**) ((char*) mnName_NameDisplayOrder + 0xC0),
        (char*) mnName_803ED538 + 0x37C,
        (void**) ((char*) mnName_NameDisplayOrder + 0xC4),
        (char*) mnName_803ED538 + 0x3A0,
        (void**) ((char*) mnName_NameDisplayOrder + 0xC8),
        (char*) mnName_803ED538 + 0x3C4,
        (void**) ((char*) mnName_NameDisplayOrder + 0xCC),
        (char*) mnName_803ED538 + 0x3E0,
        (void**) ((char*) mnName_NameDisplayOrder + 0xD0),
        (char*) mnName_803ED538 + 0x400,
        (void**) ((char*) mnName_NameDisplayOrder + 0xD4),
        (char*) mnName_803ED538 + 0x424,
        (void**) ((char*) mnName_NameDisplayOrder + 0xD8),
        (char*) mnName_803ED538 + 0x448,
        (void**) ((char*) mnName_NameDisplayOrder + 0xDC),
        (char*) mnName_803ED538 + 0x464,
        (void**) ((char*) mnName_NameDisplayOrder + 0xE0),
        (char*) mnName_803ED538 + 0x484,
        (void**) ((char*) mnName_NameDisplayOrder + 0xE4),
        (char*) mnName_803ED538 + 0x4A8,
        0);

    if (lbLang_IsSavedLanguageUS()) {
        lbArchive_LoadSections(archive, (void**) &AutoNamesList,
            (char*) mnName_803ED538 + 0x4D0,
            (void**) &NotAllowedNamesList,
            (char*) mnName_803ED538 + 0x4E4,
            0);
    } else {
        lbArchive_LoadSections(archive, (void**) &AutoNamesList,
            (char*) mnName_803ED538 + 0x4F8,
            (void**) &NotAllowedNamesList,
            (char*) mnName_803ED538 + 0x508,
            0);
    }

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x12;
    val = 0;
    mn_804A04F0.hovered_selection = 0x18;
    mnName_804D6BFC = NULL;
    ctr = 3;
    do {
        ptr[0] = val;
        ptr[1] = val + 1;
        ptr[2] = val + 2;
        ptr[3] = val + 3;
        ptr[4] = val + 4;
        ptr[5] = val + 5;
        ptr[6] = val + 6;
        ptr[7] = val + 7;
        ptr[8] = val + 8;
        ptr[9] = val + 9;
        ptr[10] = val + 10;
        ptr[11] = val + 11;
        ptr[12] = val + 12;
        ptr[13] = val + 13;
        ptr[14] = val + 14;
        ptr[15] = val + 15;
        ptr[16] = val + 16;
        ptr[17] = val + 17;
        ptr[18] = val + 18;
        ptr[19] = val + 19;
        ptr[20] = val + 20;
        ptr[21] = val + 21;
        ptr[22] = val + 22;
        ptr[23] = val + 23;
        ptr[24] = val + 24;
        ptr[25] = val + 25;
        ptr[26] = val + 26;
        ptr[27] = val + 27;
        ptr[28] = val + 28;
        ptr[29] = val + 29;
        ptr[30] = val + 30;
        ptr[31] = val + 31;
        ptr[32] = val + 32;
        ptr[33] = val + 33;
        ptr[34] = val + 34;
        ptr[35] = val + 35;
        ptr[36] = val + 36;
        ptr[37] = val + 37;
        ptr[38] = val + 38;
        ptr[39] = val + 39;
        val += 40;
        ptr += 40;
        ctr--;
    } while (ctr != 0);

    mn_804A04F0.x10 = 0;
    HSD_GObj_80390CD4(mnName_8023A59C(1U));
    proc = HSD_GObj_SetupProc(GObj_Create(0U, 1U, 0x80U), fn_80238540, 0U);
    proc->flags_3 = HSD_GObj_804D783C;
    return (s32) proc;
}

extern char** NotAllowedNamesList;
extern char mnNameNew_NullCharacter;

bool IsNameNotAllowed(char* name)
{
    char** list = NotAllowedNamesList;
    while (true) {
        if (mnNameNew_NullCharacter == **list) {
            break;
        }
        if (!CompareNameStrings(*list, name)) {
            return true;
        }
        list++;
    }
    return false;
}
