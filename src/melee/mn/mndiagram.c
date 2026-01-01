#include "mndiagram.static.h"

#include "mnmain.h"
#include "mnname.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lblanguage.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/sislib.h>

void HSD_Free(void*);

bool mn_8022E950(int);

u8 mnDiagram_8023EA2C(s32 arg0)
{
    return mnDiagram_804A0750.pad_0[arg0];
}

u8 mnDiagram_8023EA40(s32 arg0)
{
    return mnDiagram_804A076C.pad_0[arg0];
}

s32 mnDiagram_8023EA54(u32 arg0) {
    if (lbLang_IsSavedLanguageUS() != 0) {
        if (arg0 >= 0x274A6) {
            return 1;
        }
        return 0;
    } else {
        if (arg0 >= 0x186A0) {
            return 1;
        }
        return 0;
    }
}
/// #mnDiagram_8023EAC4

/// #GetHitPercentage

/// #GetPlayPercentage

/// #GetAveragePlayerCount

char* GetNameText_u8(u8);
#define GetNameText GetNameText_u8

s32 GetNameTotalKOs(u8 field_index) {
    u8 idx = (u8)(field_index & 0xFF);
    s32 total = 0;
    s32 i = 0;
    for (; i < 0x78; i++) {
        if (GetNameText(i) != 0) {
            void* data = GetPersistentNameData(idx);
            total += *(u16*)((u8*)data + ((u8)i * 2));
        }
    }
    return total;
}

#undef GetNameText

s32 GetNameTotalFalls(u8 field_index) {
    s32 i;
    s32 total = 0;
    s32 offset = (u8)(field_index & 0xFF) * 2;
    s32 dummy[4];
    (void)dummy;
    for (i = 0; i < 0x78; i++) {
        if (GetNameText(i) != 0) {
            void* data = GetPersistentNameData(i);
            total += *(u16*)(offset + (u8*)data);
        }
    }
    if (total > 999999) {
        total = 999999;
    }
    return total;
}

s32 GetFighterTotalKOs(u8 field_index) {
    u8 idx = (u8)(field_index & 0xFF);
    s32 total = 0;
    s32 i = 0;
    void* data;
    for (; i < 0x19; i++) {
        if (mn_8022E950(i) != 0) {
            data = GetPersistentFighterData(idx);
            total += *(u16*)((u8*)data + ((u8)i * 2));
        }
    }
    return total;
}

s32 GetFighterTotalFalls(u8 field_index) {
    s32 i;
    s32 total = 0;
    s32 offset = field_index * 2;
    s32 dummy[4];
    void* data;
    (void)dummy;
    for (i = 0; i < 0x19; i++) {
        if (mn_8022E950(i) != 0) {
            data = GetPersistentFighterData(i);
            total += *(u16*)((u8*)data + offset);
        }
    }
    return total;
}

/// #mnDiagram_8023F14C

/// #mnDiagram_8023F238

extern char mnDiagram_804D4FA4;
s32 mn_8022EB78(s32);
s32 mn_8022EB24(s32, s32);

void mnDiagram_8023F334(s32 arg0, s32 arg1) {
    s32 digit_count;
    char* ptr;
    s32 last;
    s32 i;

    digit_count = mn_8022EB78(arg1);
    ptr = (char*)arg0;
    last = digit_count - 1;
    i = 0;
    for (; i < digit_count; i++) {
        *ptr = mn_8022EB24(arg1, last - i) + 0x30;
        ptr++;
    }
    ((char*)arg0)[digit_count] = mnDiagram_804D4FA4;
}

u8 mnDiagram_8023F3A8(u8 arg0) {
    s32 i, original;
    
    original = i = (int)arg0;
    
    do {
        if (--i < 0) {
            return original;
        }
    } while ((u32)GetNameText(i) == 0);
    
    return i;
}
/// #mnDiagram_8023F400

u8 mnDiagram_8023F45C(u8 arg0) {
    s32 i;
    u8 original;
    u8* ptr;

    ptr = (u8*)&mnDiagram_804A0750 + arg0;
    i = arg0;
    original = arg0;
    do {
        i--;
        ptr--;
        if (i < 0) {
            return original;
        }
    } while (mn_8022E950(*ptr) == 0);
    return (u8)i;
}
u8 mnDiagram_8023F4CC(u8 arg0) {
    s32 i;
    u8 original;
    u8* ptr;

    ptr = (u8*)&mnDiagram_804A0750 + arg0;
    i = arg0;
    original = arg0;
    do {
        i++;
        ptr++;
        if (i >= 0x19) {
            return original;
        }
    } while (mn_8022E950(*ptr) == 0);
    return (u8)i;
}
/// #mnDiagram_8023F540

/// #mnDiagram_8023F578

/// #mnDiagram_8023F8CC

/// #mnDiagram_8023FA6C

/// #mnDiagram_8023FC28

s32 mnDiagram_8023FDD8(void) {
    s32 i;
    s32 count;
    i = 0;
    count = 0;
    for (; i < 0x19; i++) {
        if (mn_8022E950(i) != 0) {
            count++;
        }
    }
    return count;
}
/// #fn_8023FE30

/// #fn_8023FED4

void fn_80240B18(void* arg0) {
    if (*(void**)((u8*)arg0 + 0x38) != NULL) {
        HSD_SisLib_803A5CC4(*(void**)((u8*)arg0 + 0x38));
    }
    if (*(void**)((u8*)arg0 + 0x3C) != NULL) {
        HSD_SisLib_803A5CC4(*(void**)((u8*)arg0 + 0x3C));
    }
    if (*(void**)((u8*)arg0 + 0x40) != NULL) {
        HSD_SisLib_803A5CC4(*(void**)((u8*)arg0 + 0x40));
    }
    if (*(void**)((u8*)arg0 + 0x44) != NULL) {
        HSD_SisLib_803A5CC4(*(void**)((u8*)arg0 + 0x44));
    }
    if (*(void**)((u8*)arg0 + 0x48) != NULL) {
        HSD_SisLib_803A5CC4(*(void**)((u8*)arg0 + 0x48));
    }
    HSD_Free(arg0);
}

/// #fn_80240B98

/// #mnDiagram_80240D94

/// #mnDiagram_80241310

/// #mnDiagram_80241668

/// #mnDiagram_80241730

/// #mnDiagram_802417D0

void fn_80241AE8(HSD_GObj* gobj) {
    void* data;
    void* jobj;
    AnimLoopSettings* table;

    data = *(void**)((u8*)gobj + 0x2C);
    mnDiagram_802417D0(gobj);
    jobj = *(void**)((u8*)data + 0x0C);
    table = (AnimLoopSettings*)mnDiagram_803EE774;
    if (mn_8022ED6C(jobj, table) >= table->end_frame) {
        HSD_GObjPLink_80390228(gobj);
    }
}
/// #mnDiagram_80241B4C

/// #fn_80241BF8

/// #mnDiagram_80241E78

/// #mnDiagram_8024227C

/// #mnDiagram_802427B4

/// #mnDiagram_80242B38

/// #mnDiagram_80242C0C

/// #fn_80243038

extern void* mnDiagram_804A0814;
extern u8 HSD_GObj_804D7849;
void fn_80243038(HSD_GObj*);
HSD_JObj* HSD_JObjLoadJoint(void*);
void HSD_GObjObject_80390A70(HSD_GObj*, u8, HSD_JObj*);
void GObj_SetupGXLink(HSD_GObj*, void*, s32, s32);

void mnDiagram_802433AC(void) {
    void** joint_data;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 dummy[8];
    (void)dummy;

    joint_data = &mnDiagram_804A0814;
    gobj = GObj_Create(6, 7, 0x80);
    jobj = HSD_JObjLoadJoint(*joint_data);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObjProc_8038FD54(gobj, fn_80243038, 0);
}

/// #mnDiagram_80243434

/// #mnDiagram_802437E8
