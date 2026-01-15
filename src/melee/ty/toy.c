#include "toy.h"

#include "baselib/cobj.h"
#include "baselib/controller.h"
#include "baselib/displayfunc.h"
#include "baselib/fog.h"
#include "baselib/gobj.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "baselib/lobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"
#include "baselib/state.h"
#include "gm/gm_1601.h" // for gm_801677E8
#include "gm/gm_16AE.h"
#include "gm/gm_16F1.h" // for gm_80172C44
#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "gm/gmmain_lib.h"
#include "if/textdraw.h"
#include "if/textlib.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "mn/mnsoundtest.h"

#include "ty/forward.h"

#include "ty/tylist.h"
#include "ty/types.h"

#include <melee/if/textlib.h>
#include <MSL/math.h> // for ABS

typedef struct {
    u8 pad[4];
    s8 x4;
} TyViewData;

typedef struct {
    u8 pad[0x154];
    s16 selectedIdx;
} TyDisplayData;

typedef struct {
    u8 pad[4];
    HSD_GObj* gobj;
} TyLightData;

static u8 un_804D6EA1;

/// #un_80305058

void un_803053C4(s32 targetValue, s32 count, s32 flag)
{
    s16* list;
    u16* ptr;
    s32 trophyId;
    s32 i;
    s32 found;
    u16 val;

    if (flag != 0) {
        while (count != 0) {
            trophyId = 0;
            i = 0;

            while (trophyId < 0x125) {
                list = un_804D6EB4;

                if (lbLang_IsSettingUS()) {
                    while (*list != -1) {
                        if (*list == trophyId) {
                            found = 0;
                            goto check_found;
                        }
                        list++;
                    }
                }
                found = 1;

            check_found:
                if (found != 0) {
                    if ((f32) targetValue == un_803060BC(trophyId, 6)) {
                        if (HSD_Randi(2) == 0) {
                            if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
                                ptr = &un_804A284C[5];
                            } else {
                                ptr = gmMainLib_8015CC78();
                            }

                            if ((u8) * (u16*) ((u8*) ptr + i) == 0) {
                                Trophy_SetUnlockState((s16) trophyId,
                                                      HSD_Randi(0xFE) + 1);

                                if (gm_8016B498() || (u8) gm_801A4310() == 0xC)
                                {
                                    ptr = &un_804A284C[5];
                                } else {
                                    ptr = gmMainLib_8015CC78();
                                }

                                ptr = (u16*) ((u8*) ptr + i);
                                val = *ptr;
                                count = count - 1;
                                val ^= 0x8000;
                                *ptr = val;

                                if (count == 0) {
                                    goto done;
                                }
                            }
                        }
                    }
                }

                trophyId++;
                i += 2;
            }
        }
    } else {
        trophyId = 0;
        i = 0;

        while (trophyId < 0x125) {
            list = un_804D6EB4;

            if (lbLang_IsSettingUS()) {
                while (*list != -1) {
                    if (*list == trophyId) {
                        found = 0;
                        goto check_found2;
                    }
                    list++;
                }
            }
            found = 1;

        check_found2:
            if (found != 0) {
                if ((f32) targetValue == un_803060BC(trophyId, 6)) {
                    Trophy_SetUnlockState((s16) trophyId, HSD_Randi(0xFE) + 1);

                    if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
                        ptr = &un_804A284C[5];
                    } else {
                        ptr = gmMainLib_8015CC78();
                    }

                    ptr = (u16*) ((u8*) ptr + i);
                    val = *ptr;
                    count = count - 1;
                    val ^= 0x8000;
                    *ptr = val;

                    if (count == 0) {
                        goto done;
                    }
                }
            }

            trophyId++;
            i += 2;
        }
    }

done:
    return;
}

void Trophy_SetUnlockState(enum_t trophyId, bool addValue)
{
    s32 newCount;
    s32 byteOffset;
    s16 idx;
    s16 count;
    Toy* toy = (Toy*) &un_804A26B8;
    u16* table;
    s32 newVal;
    u16* ptr;
    u16* statePtr;
    u16 temp;

    if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
        table = toy->trophyTable;
    } else {
        table = gmMainLib_8015CC78();
    }

    idx = (s16) trophyId;
    byteOffset = idx * 2;

    if ((u8) * (u16*) ((u8*) table + byteOffset) == 0) {
        if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
            table = toy->trophyTable;
        } else {
            table = gmMainLib_8015CC78();
        }
        table = (u16*) ((u8*) table + byteOffset);
        temp = *table;
        temp ^= 0x8000;
        *table = temp;

        if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
            newCount = toy->trophyCount + 1;
        } else {
            newCount = *gmMainLib_8015CC90() + 1;
        }
        if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
            toy->trophyCount = (s16) newCount;
        } else {
            *gmMainLib_8015CC90() = (s16) newCount;
        }
    }

    if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
        table = toy->trophyTable;
    } else {
        table = gmMainLib_8015CC78();
    }

    if ((s32) (addValue + (u8) * (u16*) ((u8*) table + byteOffset)) <= 0xFF) {
        if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
            table = toy->trophyTable;
        } else {
            table = gmMainLib_8015CC78();
        }
        newVal = addValue + (u8) * (u16*) ((u8*) table + byteOffset);
        if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
            table = toy->trophyTable;
        } else {
            table = gmMainLib_8015CC78();
        }
        ptr = (u16*) ((u8*) table + byteOffset);
        *ptr = newVal + (*ptr & 0xFF00);
    } else {
        if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
            table = toy->trophyTable;
        } else {
            table = gmMainLib_8015CC78();
        }
        ptr = (u16*) ((u8*) table + byteOffset);
        *ptr = (*ptr & 0xFF00) + 0xFF;
    }

    if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
        statePtr = &toy->x19A;
        *statePtr = toy->x19A | toy->x19C;
    } else {
        statePtr = gmMainLib_8015CC84();
    }

    if (!(*statePtr & 0x80)) {
        if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
            count = toy->trophyCount;
        } else {
            count = *gmMainLib_8015CC90();
        }
        if (count >= 0xFA) {
            toy->x194 = 2;
            un_80305918(7, 0, 0);
        }
    }

    un_80304D30();

    if ((s16) trophyId == 0xA5 && gm_80164430(0x14U) == 0) {
        gm_80164504(0x14U);
    }

    if ((s32) un_803060BC((s32) (s16) trophyId, 6) == 1) {
        gm_80172C44((s16) trophyId);
    }
}

/// #un_80305918

s32 un_80305B88(void)
{
    int i;
    u32 button;
    PAD_STACK(4);

    for (i = 0; i < 4; i++) {
        if ((button = HSD_PadCopyStatus[(u8) i].trigger)) {
            gm_801677E8(i);
            break;
        }
    }
    return button;
}

s32 un_80305C44(void)
{
    int i = 0;
    u32 button;
    PAD_STACK(4);

    for (i = 0; i < 4; i++) {
        if ((button = HSD_PadCopyStatus[(u8) i].button)) {
            gm_801677E8(i);
            break;
        }
    }
    return button;
}

/// #un_80305D00

float un_80305DB0(void)
{
    float ret = 0.0F;
    int i;

    for (i = 0; i < 4; i++) {
        ret = HSD_PadGetNmlStickY(i);

        if (ABS(ret) > 0.1F) {
            gm_801677E8(i);
            break;
        }
    }

    return ret;
}

/// #un_80305EB4

/// #un_80305FB8

float un_803060BC(int trophyId, int field)
{
    TrophyData* jp_ptr;
    TrophyData* us_ptr;
    s32 lang_flag;
    s32 found_jp;

    lang_flag = 0;
    found_jp = 0;
    jp_ptr = un_804D6EC0;

    // Search JP table
    while (jp_ptr->id != -1) {
        if (jp_ptr->id == trophyId) {
            found_jp = 1;
            break;
        }
        jp_ptr++;
    }

    // Check language settings
    if (lbLang_IsSettingJP()) {
        if (lbLang_IsSavedLanguageUS()) {
            goto set_lang_flag;
        }
    }
    if (lbLang_IsSettingUS()) {
        if (lbLang_IsSavedLanguageJP()) {
            goto set_lang_flag;
        }
    }
    goto after_lang_flag;

set_lang_flag:
    lang_flag = 1;

after_lang_flag:

    // Search US table
    us_ptr = un_804D6EC4;
    while (us_ptr->id != -1) {
        if (us_ptr->id == trophyId) {
            break;
        }
        us_ptr++;
    }

    // Switch on field index
    switch (field) {
    case 0:
        if (lang_flag && found_jp) {
            return jp_ptr->x08;
        }
        return us_ptr->x08;
    case 1:
        if (lang_flag && found_jp) {
            return jp_ptr->x0C;
        }
        return us_ptr->x0C;
    case 2:
        if (lang_flag && found_jp) {
            return jp_ptr->x10;
        }
        return us_ptr->x10;
    case 3:
        if (lang_flag && found_jp) {
            return jp_ptr->x14;
        }
        return us_ptr->x14;
    case 4:
        if (lang_flag && found_jp) {
            return jp_ptr->x18;
        }
        return us_ptr->x18;
    case 5:
        if (lang_flag && found_jp) {
            return jp_ptr->x1C;
        }
        return us_ptr->x1C;
    case 6:
        return (float) us_ptr->x20;
    case 7:
        return (float) us_ptr->x21;
    case 8:
        return (float) us_ptr->x04;
    }
}
s16 un_803062BC(s32 trophyId)
{
    s16* table = un_804D6EDC;
    s32 i;

    for (i = 0; i < 0x125; i++) {
        if (trophyId == *table) {
            break;
        }
        table++;
    }

    return (s16) i;
}
/// #un_803062EC

/// #un_803063D4

/// #un_803064B8

/// #un_8030663C

/// #un_803067BC

s32 un_803068E0(HSD_GObj* gobj)
{
    if (HSD_CObjSetCurrent(gobj->hsd_obj) != 0) {
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
        HSD_FogSet(NULL);
    }
}

void un_80306930(void* arg)
{
    HSD_FogSet(((HSD_GObj*) arg)->hsd_obj);
}

/// #un_80306954

void un_80306A0C(void* arg0)
{
    HSD_Fog* fog = ((HSD_GObj*) arg0)->hsd_obj;

    if (un_804D6E54 == 0) {
        HSD_FogSet(NULL);
    } else {
        HSD_FogSet(fog);
    }
}
/// #un_80306A48

HSD_GObjProc* un_80306B18(HSD_GObj* gobj, s32 anim_frame, s32 val1, s32 val2)
{
    HSD_GObjProc* proc = NULL;
    Toy* tp = (Toy*) gobj->user_data;

    if (tp != NULL) {
        HSD_JObjClearFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
        HSD_JObjReqAnimAll(gobj->hsd_obj, anim_frame);

        tp->x8 = val1;
        tp->x4 = val2;

        proc = HSD_GObjProc_8038FD54(gobj, un_80306BB8, 0);
        HSD_GObj_80390CD4(gobj);
    }
    return proc;
}

void un_80306BB8(HSD_GObj* gobj)
{
    Toy* tp = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;

    if (tp != NULL) {
        if (tp->x8--) {
            HSD_JObjAnimAll(jobj);
        } else {
            tp->x8 = 0;

            if (tp->x4 != 0) {
                HSD_JObjClearFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
            }

            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        }
    } else {
        if (!lb_8000B09C(jobj)) {
            HSD_JObjReqAnimAll(jobj, 0.0f);
        }
        HSD_JObjAnimAll(jobj);
    }
}

void un_80306C5C(void* arg0)
{
    s32 idx;
    s32 offset;
    TyLightData* base;
    HSD_GObj* data;
    u8* table;
    HSD_LObj* lobj;
    HSD_LObj* next;
    void* unused1;
    void* unused2;

    idx = 0;
    offset = idx * 0xC;
    base = un_804D6ED4;
    data = base->gobj;
    table = (u8*) base + offset;
    lobj = data->hsd_obj;

    while (lobj != NULL) {
        HSD_LObjSetPosition(lobj, (Vec3*) (table + 0x1C));
        HSD_LObjSetInterest(lobj, (Vec3*) (table + 0x7C));
        table += 0xC;
        if (lobj == NULL) {
            next = NULL;
        } else {
            next = lobj->next;
        }
        lobj = next;
    }

    HSD_LObjAnimAll(((HSD_GObj*) arg0)->hsd_obj);
}

void Toy_RemoveUserData(void* ptr)
{
    HSD_Free(ptr);
}

void un_80306D14(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x0 == 1) {
        lbAudioAx_800237A8(0xAA, 0x7F, 0x40);
    } else if (state->x0 == 2) {
        lbAudioAx_800237A8(0xAB, 0x7F, 0x40);
    }
}
/// #un_80306D70

/// #un_80306EEC

/// #un_80307018

/// #un_8030715C

/// #un_80307470

/// #un_803075E8

/// #un_80307828

/// #un_803078E4

/// #un_80307BA0

/// #fn_80307E84

void un_80307F64(s32 arg0, s32 arg1)
{
    s8 idx;
    char* data;
    ToyAnimState* state;
    HSD_JObj* jobj1;
    HSD_JObj* jobj2;

    state = (ToyAnimState*) ((u8*) un_804A26B8 + 0x3F0);
    data = un_803FDD18;
    idx = state->x0E;
    jobj1 = state->jobj[idx];
    jobj2 = state->jobj[idx ^ 1];

    if (state->x0F == 0) {
        if (arg1 != 0) {
            if (arg0 != state->x11) {
                HSD_JObjRemoveAnimAll(jobj1);
                HSD_JObjRemoveAnimAll(jobj2);
                state->x11 = arg0;
                state->x10 = arg0;
                if (arg0 == 1) {
                    un_80306A48(jobj1, 0, data + 0x438, 0, un_804D6EC8, 0);
                    un_80306A48(jobj2, 0, data + 0x438, 0, un_804D6EC8, 0);
                } else {
                    un_80306A48(jobj1, 0, data + 0x4C8, 0, un_804D6EC8, 0);
                    un_80306A48(jobj2, 0, data + 0x4C8, 0, un_804D6EC8, 0);
                }
                state->x0F = 0xA;
                HSD_GObjProc_8038FD54(state->gobj,
                                      (void (*)(HSD_GObj*)) fn_80307E84, 0);
                HSD_GObj_80390CD4(state->gobj);
            }
        } else {
            if (arg0 == 1) {
                un_80306A48(jobj1, 0, data + 0x438, 0, un_804D6EC8, 0xA);
                un_80306A48(jobj2, 0, data + 0x438, 0, un_804D6EC8, 0xA);
            } else {
                un_80306A48(jobj1, 0, data + 0x4C8, 0, un_804D6EC8, 0xA);
                un_80306A48(jobj2, 0, data + 0x4C8, 0, un_804D6EC8, 0xA);
            }
            HSD_JObjRemoveAnimAll(jobj1);
            HSD_JObjRemoveAnimAll(jobj2);
            state->x0F = 0;
        }
    }
}
/// #un_8030813C

/// #un_80308250

void un_803082F8(s16 idx)
{
    s32 trophyId = un_80308354(idx);
    un_803063D4((s16) trophyId, 2, 0x128);
}
void un_80308328(s32 arg0)
{
    un_803063D4((s16) arg0, 2, 0x128);
}
s16 un_80308354(s16 idx)
{
    s32 i;
    s16 target;
    TrophyData* entry;

    target = un_804D6EDC[idx];
    entry = un_804D6EC4;

    for (i = 0; i < 0x125; i++) {
        if (target == entry->id) {
            break;
        }
        entry++;
    }

    if (i == 0x125) {
        OSReport(un_803FE474);
        __assert(un_804D5A48, 0xC2A, un_804D5A50);
    }

    return target;
}
/// #un_803083D8

/// #un_803084A0

/// #un_803087F4

/// #un_80308DC8

/// #un_80308F04

/// #un_80309338

/// #fn_80309404

/// #fn_8030B530

/// #fn_8030E110

/// #un_8030FA50

/// #un_8030FE48

void un_803102C4(s8 arg0)
{
    ((TyViewData*) un_804D6E6C)->x4 = arg0;
}

void un_803102D0(void)
{
    if (un_804D6ECC == NULL) {
        un_804D6ECC = lbArchive_LoadSymbols(str_TyDataf_dat, &un_804D6EA8,
                                            str_tyModelFileTbl, &un_804D6EA4,
                                            str_tyModelFileUsTbl, NULL);
    }
}

/// #un_80310324

/// #un_80310660

void un_803109A0(s32 arg0, s32 arg1, s32 arg2)
{
    ToyEntry table[9];
    char buf[16];
    s32 idx;
    s32* src;
    s32* dst;
    s32 i;

    /* Copy table from un_803B8910 to stack */
    src = un_803B8910 - 2;
    dst = (s32*) table - 2;
    i = 9;
    do {
        s32 a, b;
        a = *++src;
        ++src;
        b = *src;
        *++dst = a;
        ++dst;
        *dst = b;
    } while (--i > 0);

    /* Search for matching entry using pointer walk */
    {
        ToyEntry* p = table - 1;
        idx = 0;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 1;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 2;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 3;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 4;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 5;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 6;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 7;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 8;
        if (arg0 == (++p)->id) {
            goto found;
        }
        idx = 9;
    }

found:
    if (arg2 != 0) {
        DevText_StoreColorIndex(un_804D6E98, 1);
    } else {
        DevText_StoreColorIndex(un_804D6E98, 0);
    }

    if (arg0 == 8) {
        s32 ret = un_80304B94(arg0);
        sprintf(buf, un_803FE7A0, table[idx].value_byte, arg1, ret);
    } else {
        s32 ret = un_80304B94(arg0);
        sprintf(buf, un_803FE7B0, table[idx].value_byte, arg1, ret);
    }
    DevText_Printf(un_804D6E98, buf);
}
/// #un_80310B48

void un_803114E8(void)
{
    s32 color;
    s32 pad[0x20]; /* Force larger stack frame */
    void** data;
    s32 i;

    (void) pad;

    un_804D6E5C = HSD_MemAlloc(0x18);
    data = un_804D6E5C;

    un_804D6E98 = DevText_Create(1, 0x28, 0x28, 0xE, 9, un_804A2750);

    if (un_804D6E98 != NULL) {
        HSD_GObj* gobj = DevText_GetGObj();
        color = un_804DDE0C;
        DevText_Show(gobj, un_804D6E98);
        DevText_HideCursor(un_804D6E98);
        DevText_80302AC0(un_804D6E98);
        DevText_SetBGColor(un_804D6E98, *(GXColor*) &color);
        DevText_SetScale(un_804D6E98, un_804DDE10, un_804DDE14);
        DevText_Erase(un_804D6E98);
        DevText_SetCursorXY(un_804D6E98, 0, 0);
        DevText_StoreColorIndex(un_804D6E98, 0);
        DevText_SetTextColor(un_804D6E98, *(GXColor*) &un_804D5A40);
        DevText_StoreColorIndex(un_804D6E98, 1);
        DevText_SetTextColor(un_804D6E98, *(GXColor*) &un_804D5A44);

        i = 0;
        do {
            if (i == 0) {
                un_803109A0(i, 0, 1);
            } else {
                un_803109A0(i, 0, 0);
            }
            i++;
        } while (i < 9);

        memzero(data, 0x18);
        *data = GObj_Create(0, 0, 0);
        HSD_GObjProc_8038FD54(*data, (void (*)(HSD_GObj*)) un_80310B48, 0);
        HSD_GObj_80390CD4(*data);
    } else {
        OSReport(un_803FE7C0);
    }
}
/// #un_80311680

void un_80311788(void)
{
    s32 color;
    char buf[0x48];
    f32 f31, f30, f29, f28, f27;

    un_804D6E9C = DevText_Create(1, 0x21C, 0x82, 0xA, 7, un_804A26C4);

    if (un_804D6E9C == NULL) {
        OSReport(un_803FE7E4, un_804D6E9C, un_804D6E9C);
    } else {
        HSD_GObj* gobj = DevText_GetGObj();
        color = un_804DDE18;
        DevText_Show(gobj, un_804D6E9C);
        DevText_HideCursor(un_804D6E9C);
        DevText_80302AC0(un_804D6E9C);
        DevText_SetBGColor(un_804D6E9C, *(GXColor*) &color);
        DevText_SetScale(un_804D6E9C, un_804DDE10, un_804DDE14);
        DevText_Erase(un_804D6E9C);
        DevText_SetCursorXY(un_804D6E9C, 0, 0);

        {
            TyDisplayData* display = un_804D6EE0;
            f27 = un_803060BC(un_804D6EDC[display->selectedIdx], 5);
            f28 = un_803060BC(un_804D6EDC[display->selectedIdx], 4);
            f29 = un_803060BC(un_804D6EDC[display->selectedIdx], 3);
            f30 = un_803060BC(un_804D6EDC[display->selectedIdx], 2);
            f31 = un_803060BC(un_804D6EDC[display->selectedIdx], 1);

            sprintf(buf, un_803FE2A4,
                    un_803060BC(un_804D6EDC[display->selectedIdx], 0), f31,
                    f30, f29, f28, f27);
        }
        DevText_Print(un_804D6E9C, buf);
    }
}
/// #un_80311960

/// #un_80311AB0_OnEnter

/// #un_80311F5C

void un_80312018_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_80311F5C();
        gm_801A4B60();
    }
}
void un_80312050(void)
{
    Point3d interest;
    Point3d sp98;
    Mtx viewMtx;
    Vec3 up;
    Vec3 left;
    Vec3 eye;
    Vec3 scaled;
    HSD_CObj* cobj;
    TyViewData* data;
    volatile f32* wgpipe_f32;
    u8 color_ff;
    u8 color_00;
    f32 fz, fy, fx;

    data = un_804D6E6C;
    cobj = HSD_CObjGetCurrent();

    if (data->x4 == 0) {
        HSD_CObjGetInterest(cobj, &interest);
        HSD_CObjGetLeftVector(cobj, &left);
        HSD_CObjGetUpVector(cobj, &up);
        HSD_CObjGetEyeVector(cobj, &eye);

        HSD_StateInitDirect(0, 2);
        HSD_SetupRenderMode(2);

        HSD_CObjGetViewingMtx(cobj, viewMtx);
        GXLoadPosMtxImm(viewMtx, 0);

        HSD_StateSetLineWidth(6, 5);
        GXBegin(GX_LINES, GX_VTXFMT0, 6);

        PSVECScale(&left, &scaled, un_804DDE1C);
        PSVECAdd(&scaled, &interest, &sp98);

        fz = sp98.z;
        wgpipe_f32 = (volatile f32*) 0xCC008000;
        fy = sp98.y;
        color_ff = 0xFF;
        fx = sp98.x;
        color_00 = 0;

        *wgpipe_f32 = fx;
        *wgpipe_f32 = fy;
        *wgpipe_f32 = fz;
        *(volatile u8*) wgpipe_f32 = color_ff;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_ff;

        PSVECScale(&left, &scaled, un_804DDE20);
        PSVECAdd(&scaled, &interest, &sp98);
        fz = sp98.z;
        fy = sp98.y;
        fx = sp98.x;
        *wgpipe_f32 = fx;
        *wgpipe_f32 = fy;
        *wgpipe_f32 = fz;
        *(volatile u8*) wgpipe_f32 = color_ff;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_ff;

        PSVECScale(&up, &scaled, un_804DDE1C);
        PSVECAdd(&scaled, &interest, &sp98);
        fz = sp98.z;
        fy = sp98.y;
        fx = sp98.x;
        *wgpipe_f32 = fx;
        *wgpipe_f32 = fy;
        *wgpipe_f32 = fz;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_ff;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_ff;

        PSVECScale(&up, &scaled, un_804DDE20);
        PSVECAdd(&scaled, &interest, &sp98);
        fz = sp98.z;
        fy = sp98.y;
        fx = sp98.x;
        *wgpipe_f32 = fx;
        *wgpipe_f32 = fy;
        *wgpipe_f32 = fz;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_ff;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_ff;

        PSVECScale(&eye, &scaled, un_804DDE1C);
        PSVECAdd(&scaled, &interest, &sp98);
        fz = sp98.z;
        fy = sp98.y;
        fx = sp98.x;
        *wgpipe_f32 = fx;
        *wgpipe_f32 = fy;
        *wgpipe_f32 = fz;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_ff;
        *(volatile u8*) wgpipe_f32 = color_ff;

        PSVECScale(&eye, &scaled, un_804DDE20);
        PSVECAdd(&scaled, &interest, &sp98);
        fz = sp98.z;
        fy = sp98.y;
        fx = sp98.x;
        *wgpipe_f32 = fx;
        *wgpipe_f32 = fy;
        *wgpipe_f32 = fz;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_00;
        *(volatile u8*) wgpipe_f32 = color_ff;
        *(volatile u8*) wgpipe_f32 = color_ff;
    }
}
void un_803122D0_OnInit(void)
{
    Toy* userData = (Toy*) &un_804A26B8;
    void* targetPtr;

    memzero(&userData->x194, 0x25A);

    un_804D6EA1 = 0;

    if (gm_8016B498() || gm_801A4310() == MJ_TOY_LOTTERY) {
        targetPtr = &userData->x19A;
    } else {
        targetPtr = gmMainLib_8015CC84();
    }

    *(u16*) targetPtr |= 4;

    *(u8*) &userData->x194 = 1;
}

void un_8031234C(s32 arg0)
{
    u16* saveData;
    u16* stateData;
    char* toy = (char*) un_804A26B8;
    u16* srcPtr;
    u16* dstPtr;
    s32 i;
    u16* ptr;
    s32 j;

    saveData = gmMainLib_8015CC78();
    stateData = gmMainLib_8015CC84();

    if (arg0 != 0) {
        s32 category;
        dstPtr = saveData;
        srcPtr = (u16*) (toy + 0x194);
        for (i = 0x125; i != 0; i--) {
            u16 flags = srcPtr[5];
            if (flags & 0x8000) {
                *dstPtr |= 0x8000;
            }
            *dstPtr = (u8) srcPtr[5] + (*dstPtr & 0xFF00);
            srcPtr++;
            dstPtr++;
        }

        *stateData = *(u16*) (toy + 0x19A);

        for (category = 0; category < 9; category++) {
            if ((u32) category > 1U && category != 8 && category != 3 &&
                (*stateData & (1 << category)))
            {
                ptr = saveData;
                for (j = 0; j < 0x125; j++) {
                    f32 result = un_803060BC(j, 6);
                    if ((f32) category == result) {
                        *ptr |= 0x4000;
                    }
                    ptr++;
                }
            }
        }

        *gmMainLib_8015CC90() = *(s16*) (toy + 0x3EC);
    } else {
        *(u16*) (toy + 0x19A) = *stateData;
        *(u16*) (toy + 0x19C) = 0;
        memcpy(toy + 0x19E, saveData, 0x24A);
        *(s16*) (toy + 0x3EC) = *gmMainLib_8015CC90();
    }
}
