#include "toy.h"

#include "baselib/cobj.h"
#include "baselib/controller.h"
#include "baselib/displayfunc.h"
#include "baselib/fog.h"
#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "baselib/lobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"
#include "baselib/sobjlib.h"
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
#include "lb/lbvector.h"
#include "mn/mnsoundtest.h"
#include "sc/types.h"

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

extern s8 un_804D6E50;
extern void** un_804D6E68;
extern s8 un_804D6EA2;

extern void* un_804D6EBC;

extern s16* un_804D6E64;

extern char un_803FDD18[];
extern void* un_804D6ED8;

extern DevText* un_804D6E9C;
extern TrophyData* un_804D6EC4;

extern void* un_804D6ED4;
extern char un_803FE3B8[];
extern char un_803FE3DC[];
extern HSD_FogDesc un_803B8844;

typedef struct PosArray {
    s32 xy[2];
} PosArray;

typedef struct PosArrayFull {
    PosArray a[7];
} PosArrayFull;

extern PosArrayFull un_803B8864;
extern PosArrayFull un_803B889C;

extern s32 un_804D6E58;
extern f32 un_804D6E80;
extern f32 un_804D6E84;
extern f32 un_804D6E88;
extern f32 un_804D6E8C;
extern f32 un_804D6E90;
extern f32 un_804D6E94;

extern s32 un_804D6E70;
extern s32 un_804D6E74;
extern s32 un_804D6E78;
extern s32 un_804D6E7C;

/// #un_80305058

/* 97.5% match */
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

/* 94.9% match */
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

/* 98.7% match */
void un_80305918(s8 arg0, s32 arg1, s32 arg2) {
    s16* var_r22;
    s32 var_r27;
    u8* temp_r26;
    s32 var_r25;
    u16* base;
    s32 mask;
    u16* ptr;
    u8* var_r22_2;
    u8* var_r3;
    u16 temp_val;

    base = un_804A26B8;
    if ((s8)arg0 == 8) {
        return;
    }

    temp_r26 = (u8*)base + 0x19E;
    var_r25 = 0;
    var_r27 = 0;

    do {
        s32 skip;
        s16 temp_r0;

        var_r22 = un_804D6EB4;
        if (lbLang_IsSettingUS() != 0) {
            goto load_value;
        loop_top:
            if (temp_r0 == var_r25) {
                skip = 0;
                goto check_skip;
            }
            var_r22++;
        load_value:
            temp_r0 = *var_r22;
            if (temp_r0 != -1) {
                goto loop_top;
            }
        }
        skip = 1;

check_skip:
        if (skip == 0) {
            goto next_iter;
        }

        if ((f32)arg0 != un_803060BC(var_r25, 6)) {
            goto next_iter;
        }

        if (arg1 != 0) {
            if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
                var_r22_2 = temp_r26;
            } else {
                var_r22_2 = gmMainLib_8015CC78();
            }
            if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
                var_r3 = temp_r26;
            } else {
                var_r3 = gmMainLib_8015CC78();
            }
            if (*(u16*)(var_r3 + var_r27) & 0x4000) {
                u16* temp_ptr;
                u16 val;
                temp_ptr = (u16*)(var_r22_2 + var_r27);
                val = *temp_ptr;
                *temp_ptr = val ^ 0x4000;
            }
        } else {
            if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
                var_r3 = temp_r26;
            } else {
                var_r3 = gmMainLib_8015CC78();
            }
            *(u16*)(var_r3 + var_r27) |= 0x4000;
        }

next_iter:
        var_r25++;
        var_r27 += 2;
    } while (var_r25 < 0x125);

    if (arg1 != 0) {
        if (arg2 != 0) {
            u16* ptr5;
            u16 val4;
            s32 mask2;
            ptr5 = (u16*)((u8*)base + 0x19C);
            val4 = base[0xCE];
            mask2 = 1 << arg0;
            if (val4 & mask2) {
                *ptr5 = (u16)(val4 ^ mask2);
            }
        } else {
            if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
                ptr = (u16*)((u8*)base + 0x19A);
            } else {
                ptr = gmMainLib_8015CC84();
            }
            temp_val = *ptr;
            mask = 1 << arg0;
            if (temp_val & mask) {
                *ptr = temp_val ^ mask;
            }
        }
    } else {
        if (arg2 != 0) {
            u16* ptr19c = (u16*)((u8*)base + 0x19C);
            *ptr19c = (u16)(*ptr19c | (1 << arg0));
        } else {
            if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
                ptr = (u16*)((u8*)base + 0x19A);
            } else {
                ptr = gmMainLib_8015CC84();
            }
            *ptr |= 1 << arg0;
        }
    }
}

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

static inline float HSD_PadGetNmlSubStickX(u8 slot)
{
    return HSD_PadCopyStatus[slot].nml_subStickX;
}

float un_80305EB4(void)
{
    float ret = 0.0F;
    int i;

    for (i = 0; i < 4; i++) {
        ret = HSD_PadGetNmlSubStickX(i);

        if (ABS(ret) > 0.1F) {
            gm_801677E8(i);
            break;
        }
    }

    return ret;
}

float un_80305FB8(void)
{
    float ret = 0.0F;
    int i;

    for (i = 0; i < 4; i++) {
        ret = HSD_PadGetNmlSubStickY(i);

        if (ABS(ret) > 0.1F) {
            gm_801677E8(i);
            break;
        }
    }

    return ret;
}

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
// Decompilation of un_803062EC
// Unit: main/melee/ty/toy


void un_803062EC(s32 arg0, u32 arg1, f32 farg0)
{
    char sp14[80];
    TrophyData* td;
    s32 id;

    td = un_804D6EC4;
    while ((id = td->id) != -1) {
        if (id == arg0) {
            break;
        }
        td++;
    }

    switch (arg1) {
    case 0:
        td->x08 = farg0;
        break;
    case 1:
        td->x0C = farg0;
        break;
    case 2:
        td->x10 = farg0;
        break;
    case 3:
        td->x14 = farg0;
        break;
    case 4:
        td->x18 = farg0;
        break;
    case 5:
        td->x1C = farg0;
        break;
    case 6:
    case 7:
    default:
        break;
    }

    if (un_804D6E9C != NULL) {
        DevText_Erase(un_804D6E9C);
        DevText_SetCursorXY(un_804D6E9C, 0, 0);
        sprintf(sp14, "X   %3.2f\nY   %3.2f\nZ   %3.2f\nMS  %3.2f\nSS  %3.2f\nMD  %3.2f",
                td->x08, td->x0C, td->x10, td->x14, td->x18, td->x1C);
        DevText_Print(un_804D6E9C, sp14);
    }
}

// m2c decompilation of un_803063D4
// Unit: main/melee/ty/toy

s32 un_803063D4(s16 arg0, s32 arg1, s32 arg2)
{
    s32 result;
    s32 i;
    s16* ptr;

    result = arg0 + arg1 + 1;

    if (lbLang_IsSettingJP() && lbLang_IsSavedLanguageUS()) {
        ptr = un_804D6EB8;
        i = 0;
        while (*ptr != -1) {
            if (*ptr == arg0) {
                result = i + arg2 + 1;
                break;
            }
            ptr++;
            i++;
        }
    } else if (lbLang_IsSettingUS() && lbLang_IsSavedLanguageJP()) {
        ptr = un_804D6EB8;
        i = 0;
        while (*ptr != -1) {
            if (*ptr == arg0) {
                result = i + arg2 + 1;
                break;
            }
            ptr++;
            i++;
        }
    }

    return result;
}

// Decompilation of un_803064B8
// Unit: main/melee/ty/toy

int lbLang_IsSavedLanguageJP(void);
int lbLang_IsSavedLanguageUS(void);
int lbLang_IsSettingJP(void);

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
} ToyNameData;


s16 un_803064B8(s16 arg0, s8 arg1)
{
    ToyNameData* data;
    s16 result;

    result = arg0;
    switch (arg1) {
    case 0:
        data = (ToyNameData*)un_804D6EBC;
        result = data[arg0].x0;
        break;
    case 1:
        data = (ToyNameData*)un_804D6EBC;
        result = data[arg0].x2;
        break;
    case 2:
        if (lbLang_IsSettingJP() != 0) {
            if (lbLang_IsSavedLanguageJP() != 0) {
                data = (ToyNameData*)un_804D6EBC;
                result = data[arg0].x4;
                break;
            }
            data = (ToyNameData*)un_804D6EBC;
            result = data[arg0].x8;
            break;
        }
        if (lbLang_IsSavedLanguageUS() != 0) {
            data = (ToyNameData*)un_804D6EBC;
            result = data[arg0].x4;
            break;
        }
        data = (ToyNameData*)un_804D6EBC;
        result = data[arg0].x8;
        break;
    case 3:
        if (lbLang_IsSettingJP() != 0) {
            if (lbLang_IsSavedLanguageJP() != 0) {
                data = (ToyNameData*)un_804D6EBC;
                result = data[arg0].x6;
                break;
            }
            data = (ToyNameData*)un_804D6EBC;
            result = data[arg0].xA;
            break;
        }
        if (lbLang_IsSavedLanguageUS() != 0) {
            data = (ToyNameData*)un_804D6EBC;
            result = data[arg0].x6;
            break;
        }
        data = (ToyNameData*)un_804D6EBC;
        result = data[arg0].xA;
        break;
    }
    return result;
}

// Decompilation of un_8030663C
// Unit: main/melee/ty/toy


void un_8030663C(void)
{
    s32 var_r31;
    s32 var_r30;
    u16* var_r29;
    s16* var_r28;
    int var_r27;

    var_r29 = (u16*)((u8*)un_804A284C + 0xA);
    var_r27 = 0;
    var_r31 = 0;
    var_r30 = 0;
    var_r28 = un_804D6E64;
    do {
        u16* src;
        if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
            src = var_r29;
        } else {
            src = gmMainLib_8015CC78();
        }
        if ((u8)*(u16*)((u8*)src + var_r30) != 0) {
            *var_r28 = un_803064B8(var_r27, 0);
            var_r31 += 1;
            var_r28 += 3;
        }
        var_r27 += 1;
        var_r30 += 2;
    } while (var_r27 < 0x125);
    {
        s32 var2_r27;
        s16* var2_r28;
        s16* var2_r29;
        int var2_r30;

        var2_r29 = un_804D6E64;
        var2_r30 = 0;
        do {
            var2_r28 = un_804D6E64;
            var2_r27 = 0;
            goto loop_13_check;
    loop_13_body:
            if (*var2_r28 == un_803064B8(var2_r30, 1)) {
                var2_r29[1] = *var2_r28;
                var2_r29 += 3;
            } else {
                var2_r28 += 3;
                var2_r27 += 1;
    loop_13_check:
                if (var2_r27 < var_r31) {
                    goto loop_13_body;
                }
            }
            var2_r30 += 1;
        } while (var2_r30 < 0x125);
    }
    {
        s16* var3_r27;
        s32 var3_r28;
        s16* var3_r29;
        int var3_r30;
        s16* new_var;

        var3_r29 = un_804D6E64;
        var3_r30 = 0;
        do {
            var3_r27 = un_804D6E64;
            var3_r28 = 0;
            goto loop_23_check;
    loop_23_body:
            if (lbLang_IsSavedLanguageJP() != 0) {
                if (*var3_r27 == un_803064B8(var3_r30, 2)) {
                    var3_r29[2] = *var3_r27;
                    var3_r29 += 3;
                } else {
                    goto block_22;
                }
            } else {
                new_var = var3_r27;
                if (*new_var == un_803064B8(var3_r30, 3)) {
                    var3_r29[2] = *new_var;
                    var3_r29 += 3;
                } else {
    block_22:
                    var3_r27 += 3;
                    var3_r28 += 1;
    loop_23_check:
                    if (var3_r28 < var_r31) {
                        goto loop_23_body;
                    }
                }
            }
            var3_r30 += 1;
        } while (var3_r30 < 0x125);
    }
}

/// #un_803067BC

s32 un_803068E0(HSD_GObj* gobj)
{
    if (HSD_CObjSetCurrent(gobj->hsd_obj) != 0) {
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
        HSD_FogSet(NULL);
    }
}

void un_80306930(HSD_GObj* gobj, int unused)
{
    HSD_FogSet(gobj->hsd_obj);
}

// Decompilation of un_80306954
// Unit: main/melee/ty/toy


void un_80306954(HSD_GObj* gobj)
{
    void* state;
    char* tbl;
    char* entry;

    tbl = un_803FDD18;
    state = un_804D6ED4;
    if (HSD_CObjSetCurrent((HSD_CObj*)gobj->hsd_obj)) {
        if (un_804D6E50 == 0) {
            entry = tbl + *(s32*)((u8*)state + 0x10) * 0xC;
            if (*(s32*)(entry + 0x104) != 0) {
                HSD_SetEraseColor(
                    *(u8*)(entry + 0x100),
                    *(u8*)(entry + 0x101),
                    *(u8*)(entry + 0x102),
                    *(u8*)(entry + 0x103)
                );
                HSD_CObjEraseScreen((HSD_CObj*)gobj->hsd_obj, 1, 0, 0);
            }
        }
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(0);
        HSD_CObjEndCurrent();
    }
}

void un_80306A0C(void* arg0)
{
    HSD_Fog* fog = ((HSD_GObj*) arg0)->hsd_obj;

    if (un_804D6E54 == 0) {
        HSD_FogSet(NULL);
    } else {
        HSD_FogSet(fog);
    }
}
// Decompilation of un_80306A48
// Unit: main/melee/ty/toy

void un_80306A48(HSD_JObj* jobj, char* symbol1, char* symbol2, char* symbol3, HSD_Archive* archive, s32 frame) {
    void* new_var2;
    void* new_var;
    void* anim;
    void* matanim;
    int new_var3;
    void* shapeanim;

    new_var3 = symbol1 != NULL;
    if (new_var3) {
        anim = HSD_ArchiveGetPublicAddress(archive, symbol1);
    } else {
        anim = NULL;
    }
    new_var = (void*)(0 ^ 0);
    if (symbol2 != NULL) {
        matanim = HSD_ArchiveGetPublicAddress(archive, symbol2);
    } else {
        matanim = NULL;
    }
    if (symbol3 != new_var) {
        shapeanim = HSD_ArchiveGetPublicAddress(archive, symbol3);
    } else {
        new_var2 = NULL;
        shapeanim = new_var2;
    }
    HSD_JObjAddAnimAll(jobj, anim, matanim, shapeanim);
    HSD_JObjReqAnimAll(jobj, (f32)frame);
    HSD_JObjAnimAll(jobj);
}

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

/* 91.1% match */
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
// Attempt 7: Try struct-based array access


typedef struct {
    char pad[0xFC];
    s32 xFC_idx;
} TyLightEntry;

typedef struct {
    char pad[0xCC];
    char* xCC_name;
} TyLightSymbol;

void un_80306D70(s32 arg0)
{
    void* sp14;
    s32 spC;
    char* base;
    u8* data;
    TyLightEntry* entry;
    TyLightSymbol* sym;
    s32 idx;

    base = un_803FDD18;
    data = un_804D6ED4;

    if (*(HSD_Archive**)(data + 0xC) != NULL && *(HSD_GObj**)(data + 0x4) != NULL) {
        HSD_GObjProc_8038FED4(*(HSD_GObj**)(data + 0x4));
        HSD_GObjPLink_80390228(*(HSD_GObj**)(data + 0x4));
        *(HSD_GObj**)(data + 0x4) = NULL;
        entry = (TyLightEntry*)(base + arg0 * 0xC);
        idx = entry->xFC_idx;
        sym = (TyLightSymbol*)(base + idx * 8);
        sp14 = HSD_ArchiveGetPublicAddress(*(HSD_Archive**)(data + 0xC), sym->xCC_name);
    } else {
        entry = (TyLightEntry*)(base + arg0 * 0xC);
        idx = entry->xFC_idx;
        sym = (TyLightSymbol*)(base + idx * 8);
        *(HSD_Archive**)(data + 0xC) = lbArchive_80016DBC(base, &sp14, sym->xCC_name);
    }

    if (sp14 != NULL) {
        *(HSD_GObj**)(data + 0x4) = GObj_Create(2, 1, 0);
        HSD_GObjObject_80390A70(*(HSD_GObj**)(data + 0x4), HSD_GObj_804D784A, un_80306EEC(sp14, (s32)&spC));
        GObj_SetupGXLink(*(HSD_GObj**)(data + 0x4), HSD_GObj_LObjCallback, 0x37, 0);
        if (spC != 0) {
            HSD_GObjProc_8038FD54(*(HSD_GObj**)(data + 0x4), (HSD_GObjEvent)un_80306C5C, 0);
            HSD_GObj_80390CD4(*(HSD_GObj**)(data + 0x4));
        }
    } else {
        entry = (TyLightEntry*)(base + arg0 * 0xC);
        idx = entry->xFC_idx;
        sym = (TyLightSymbol*)(base + idx * 8);
        OSReport(base + 0x64C, sym->xCC_name);
        __assert("toy.c", 0x8CD, "0");
    }
}

/* 78.7% match */
static char un_804D5A54[] = "lobj.h";
static char un_804D5A5C[] = "lobj";

HSD_LObj* un_80306EEC(void* list_arg, s32 hasAnim_arg)
{
    LightList** list = list_arg;
    s32* hasAnim = (s32*)hasAnim_arg;
    HSD_LObj* prev;
    HSD_LObj* lobj;
    HSD_LObj* first;
    HSD_LightAnim** anims;
    u8* base;
    u8* posTable;
    u8* animFlag;
    s32 idx;

    prev = NULL;
    idx = 0;
    base = un_804D6ED4;

    if (hasAnim != NULL) {
        *hasAnim = 0;
    }

    posTable = base + idx * 0xC;

    while (*list != NULL) {
        lobj = HSD_LObjLoadDesc((*list)->desc);
        if (lobj != NULL) {
            animFlag = base + idx + 0xDC;
            anims = (*list)->anims;
            *animFlag = 0;
            if (anims != NULL && *anims != NULL) {
                if (hasAnim != NULL) {
                    *hasAnim = 1;
                }
                HSD_LObjAddAnimAll(lobj, *anims);
                HSD_LObjReqAnimAll(lobj, 0.0F);
                if ((*anims)->next != NULL) {
                    *animFlag = 1;
                }
            }
            HSD_LObjGetPosition(lobj, (Vec3*)(posTable + 0x1C));
            HSD_LObjGetInterest(lobj, (Vec3*)(posTable + 0x7C));
            posTable += 0xC;
            idx += 1;
        }
        if (prev != NULL) {
            if (prev == NULL) {
                __assert(un_804D5A54, 0x136, un_804D5A5C);
            }
            prev->next = lobj;
        } else {
            first = lobj;
        }
        prev = lobj;
        list++;
    }
    return first;
}

// Decompilation of un_80307018
// Unit: main/melee/ty/toy




typedef struct {
    /* 0x00 */ HSD_GObj* x0;
    /* 0x04 */ void* x4;
    /* 0x08 */ HSD_GObj* x8;
} tyUnkStruct;

typedef struct {
    /* 0x00 */ u8 pad[0x50];
    /* 0x50 */ HSD_Archive* x50;
} tyUnkStruct2;

void un_80307018(void)
{
    u8 _pad[16];
    HSD_Fog* fog;
    HSD_JObj* jobj;
    void* obj;
    u8 kind;
    tyUnkStruct2* ptr1;
    tyUnkStruct* ptr2;
    HSD_FogDesc fog_desc;

    (void)_pad;
    ptr1 = un_804D6ED8;
    ptr2 = un_804D6ED4;

    if (ptr1->x50 == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        __assert("toy.c", 0x912, "0");
    }

    jobj = HSD_ArchiveGetPublicAddress(ptr1->x50, un_803FE3DC);
    if (jobj != NULL) {
        ptr2->x0 = GObj_Create(2, 3, 0);
        obj = un_80306EEC(jobj, 0);
        kind = HSD_GObj_804D784A;
        HSD_GObjObject_80390A70(ptr2->x0, kind, obj);
        GObj_SetupGXLink(ptr2->x0, HSD_GObj_LObjCallback, 0x36, 0);

        if (un_804D6E50 != 0) {
            fog_desc = un_803B8844;
            fog = HSD_FogLoadDesc(&fog_desc);
            ptr2->x8 = GObj_Create(3, 4, 0);
            kind = HSD_GObj_804D7848;
            HSD_GObjObject_80390A70(ptr2->x8, kind, fog);
            GObj_SetupGXLink(ptr2->x8, (GObj_RenderFunc)un_80306A0C, 0x35, 0);
        }
    }
}

/* 78.7% match */
typedef struct TyGObjX8_ {
    u8 pad[0x28];
    HSD_CObj* x28;
} TyGObjX8_;

typedef struct TyCameraData_ {
    void* x0;
    void* x4;
    TyGObjX8_* x8;
    u8 padC[0x18 - 0x0C];
    f32 x18;
    f32 x1C;
    f32 x20;
} TyCameraData_;

typedef struct TyLightGObj_ {
    u8 pad[0x28];
    HSD_LObj* x28;
} TyLightGObj_;

typedef struct TyLightArray_ {
    void* x0;
    TyLightGObj_* x4;
    u8 pad08[0x14 - 0x08];
    f32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    u8 pad28[0x7C - 0x28];
    s32 x7C;
    s32 x80;
    s32 x84;
} TyLightArray_;

void un_8030715C(f32 cstick_x, f32 cstick_y)
{
    Vec3 interest;
    Vec3 new_interest;
    Mtx mtx;
    Vec3 up_vec;
    Vec3 left_vec;
    Vec3 euler;
    Vec3 angles;
    TyCameraData_* data;
    TyLightArray_* data2;
    HSD_CObj* cobj;
    HSD_LObj* lobj;
    TyLightArray_* cur;
    s32 i;
    s8* flag_ptr;

    data = (void*)un_804D6E68;
    data2 = un_804D6ED4;
    cobj = data->x8->x28;

    HSD_CObjGetInterest(cobj, &interest);
    HSD_CObjGetInterest(cobj, &new_interest);
    HSD_CObjGetUpVector(cobj, &up_vec);
    PSVECScale(&up_vec, &up_vec, -cstick_y);
    PSVECAdd(&up_vec, &new_interest, &new_interest);
    HSD_CObjGetLeftVector(cobj, &left_vec);
    PSVECScale(&left_vec, &left_vec, cstick_x);
    PSVECAdd(&left_vec, &new_interest, &new_interest);

    if (new_interest.x <= -3000.0F ||
        new_interest.y <= -3000.0F ||
        new_interest.z <= -3000.0F ||
        new_interest.x >= 3000.0F ||
        new_interest.y >= 3000.0F ||
        new_interest.z >= 3000.0F)
    {
        return;
    }

    HSD_CObjSetInterest(cobj, &new_interest);

    euler.x = 0.0F;
    euler.y = 0.0F;
    euler.z = data->x20;

    MTXRotRad(mtx, 'x', 0.017453292F * data->x18);
    PSMTXMultVecSR(mtx, &euler, &euler);
    MTXRotRad(mtx, 'y', 0.017453292F * -data->x1C);
    PSMTXMultVecSR(mtx, &euler, &euler);

    euler.x += new_interest.x;
    euler.y += new_interest.y;
    euler.z += new_interest.z;

    HSD_CObjSetEyePosition(cobj, &euler);

    cur = data2;
    i = 0;
    lobj = data2->x4->x28;

    while (lobj != NULL) {
        flag_ptr = (s8*)data2 + i + 0xDC;

        angles.x = 0.017453292F * data2->x14;
        angles.y = 0.017453292F * -data2->x18;
        angles.z = 0.0F;

        if (*flag_ptr != 0) {
            HSD_LObjGetPosition(lobj, &interest);
        } else {
            *(s32*)&interest.x = cur->x1C;
            *(s32*)&interest.y = cur->x20;
            *(s32*)&interest.z = cur->x24;
        }

        if (*flag_ptr != 0) {
            cur->x1C = *(s32*)&interest.x;
            cur->x20 = *(s32*)&interest.y;
            cur->x24 = *(s32*)&interest.z;
        }

        lbVector_ApplyEulerRotation(&interest, &angles);
        HSD_LObjSetPosition(lobj, &interest);

        if (HSD_LObjGetInterest(lobj, &interest) != 0) {
            if (*flag_ptr != 0) {
                cur->x7C = *(s32*)&interest.x;
                cur->x80 = *(s32*)&interest.y;
                cur->x84 = *(s32*)&interest.z;
            } else {
                *(s32*)&interest.x = cur->x7C;
                *(s32*)&interest.y = cur->x80;
                *(s32*)&interest.z = cur->x84;
            }
            lbVector_ApplyEulerRotation(&interest, &angles);
            HSD_LObjSetInterest(lobj, &interest);
        }

        cur = (TyLightArray_*)((u8*)cur + 0xC);
        i += 1;

        if (lobj != NULL) {
            lobj = lobj->next;
        }
    }
}

/// #un_80307470

/* 96.3% match */

typedef struct ToyDataJObj {
    /* 0x00 */ void* x0;
    /* 0x04 */ struct ToyDataJObj* x4;
    /* 0x08 */ u8 pad08[0x40 - 0x08];
    /* 0x40 */ s32 x40;
} ToyDataJObj;

typedef struct ToyDataX8 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ ToyDataJObj* x28;
} ToyDataX8;

typedef struct ToyData {
    /* 0x00 */ void* x0;
    /* 0x04 */ HSD_GObj* gobj;
    /* 0x08 */ ToyDataX8* x8;
    /* 0x0C */ u8 pad0C[0x50 - 0x0C];
    /* 0x50 */ HSD_Archive* archive;
    /* 0x54 */ u32 x54;
} ToyData;

void un_80306BB8(HSD_GObj*);

void un_803075E8(s32 arg0)
{
    char* data;
    ToyData* td;
    void* joint;
    char** ptr;
    HSD_JObj* jobj;
    void* animjoint;
    void* matanim;
    void* shapanim;
    ToyDataJObj* tdjobj;

    data = un_803FDD18;
    td = un_804D6ED8;

    if (td->archive == NULL) {
        OSReport(data + 0x6A0);
        __assert("toy.c", 0xA41, "0");
    }

    if (td->gobj != NULL) {
        HSD_GObjProc_8038FED4(td->gobj);
        HSD_GObjPLink_80390228(td->gobj);
        td->gobj = NULL;
    }

    if (td->x54 != 0) {
        ((ToyData*)un_804D6ED8)->x8->x28->x40 = 9;
        ((ToyData*)un_804D6ED8)->x8->x28->x4->x40 = 9;
        ((ToyData*)un_804D6ED8)->x8->x28->x4->x4->x40 = 9;
    }

    ptr = (char**)(data + arg0 * 4);
    if (*(ptr += 0x69) != NULL) {
        joint = HSD_ArchiveGetPublicAddress(td->archive, *ptr);
        if (joint != NULL) {
            td->gobj = GObj_Create(4, 7, 0);
            jobj = HSD_JObjLoadJoint(joint);
            HSD_GObjObject_80390A70(td->gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(td->gobj, HSD_GObj_JObjCallback, 0x33, 0);

            ptr = (char**)(data + arg0 * 0xC);
            animjoint = HSD_ArchiveGetPublicAddress(td->archive, ptr[0x290 / 4]);
            matanim = HSD_ArchiveGetPublicAddress(td->archive, ptr[0x294 / 4]);
            shapanim = HSD_ArchiveGetPublicAddress(td->archive, ptr[0x298 / 4]);

            if (animjoint != NULL || matanim != NULL || shapanim != NULL) {
                HSD_JObjAddAnimAll(jobj, animjoint, matanim, shapanim);
                HSD_JObjReqAnimAll(jobj, 0.0F);
                HSD_JObjAnimAll(jobj);
                HSD_GObjProc_8038FD54(td->gobj, un_80306BB8, 0);
                HSD_GObj_80390CD4(td->gobj);
            }
        } else {
            OSReport(data + 0x718, *ptr);
            __assert("toy.c", 0xA75, "0");
        }
    } else if (td->x54 != 0) {
        tdjobj = ((ToyData*)un_804D6ED8)->x8->x28;
        switch (arg0) {
        case 2:
            break;
        case 4:
            tdjobj = tdjobj->x4;
            break;
        case 5:
            tdjobj = tdjobj->x4->x4;
            break;
        }
        tdjobj->x40 = 8;
    }
}

/// #un_80307828

/* 96.8% match */

typedef struct tyLightData {
    /* 0x00 */ char _pad0[0x0C];
    /* 0x0C */ HSD_GObj* x0C;
    /* 0x10 */ char _pad1[0x48];
    /* 0x58 */ void* x58;
} tyLightData;


void un_803078E4(void)
{
    tyLightData* data;
    char* table;
    PosArrayFull pos_en;
    PosArrayFull pos_jp;
    void* syms[7];
    HSD_SObj_803A477C_t* sobj;
    void** sym_ptr;
    s32* jp_ptr;
    s32* en_ptr;
    s32 i;

    table = un_803FDD18;
    data = un_804D6ED8;

    pos_en = un_803B8864;
    pos_jp = un_803B889C;

    if (data->x58 == NULL) {
        char* filename;

        if (lbLang_IsSavedLanguageJP() != 0) {
            filename = table + 0x620;
        } else {
            filename = table + 0x630;
        }

        data->x58 = lbArchive_LoadSymbols(
            filename,
            &syms[0], *(s32*)(table + 0x3F0),
            &syms[1], *(s32*)(table + 0x3F4),
            &syms[2], *(s32*)(table + 0x3F8),
            &syms[3], *(s32*)(table + 0x3FC),
            &syms[4], *(s32*)(table + 0x400),
            &syms[5], *(s32*)(table + 0x404),
            &syms[6], *(s32*)(table + 0x408),
            NULL
        );

        data->x0C = GObj_Create(5, 6, 0);
        GObj_SetupGXLink(data->x0C, HSD_SObjLib_803A49E0, 0x38, 0);

        i = 0;
        sym_ptr = &syms[i];
        jp_ptr = pos_jp.a[0].xy;
        en_ptr = pos_en.a[0].xy;

        do {
            sobj = HSD_SObjLib_803A477C(data->x0C, (int)*sym_ptr, 0, 0, 0x80, 0);
            if (sobj != NULL) {
                if (lbLang_IsSavedLanguageJP() != 0) {
                    sobj->x10 = (f32)jp_ptr[0];
                    sobj->x14 = (f32)jp_ptr[1];
                } else {
                    sobj->x10 = (f32)en_ptr[0];
                    sobj->x14 = (f32)en_ptr[1];
                }
            }
            i += 1;
            sym_ptr += 1;
            jp_ptr += 2;
            en_ptr += 2;
        } while (i < 7);
    }
}

/* 99.945% match - remaining diff is add operand order (r3,r0,r29 vs r3,r29,r0) */
HSD_JObj* un_80307BA0(HSD_JObj* parent_jobj, s16 arg1)
{
    void* joint_data;
    HSD_JObj* jobj;
    u8* data_ptr;
    f32 scale_val;
    char* str = un_803FDD18;

    data_ptr = un_804A2AA8;

    if (un_804D6EC8 == NULL) {
        un_804D6EC8 = lbArchive_LoadSymbols(str + 0x144, &joint_data, str + 0x150, 0);
    } else {
        joint_data = HSD_ArchiveGetPublicAddress(un_804D6EC8, str + 0x150);
    }

    jobj = HSD_JObjLoadJoint(joint_data);
    HSD_JObjAddChild(parent_jobj, jobj);

    {
        s8 tmp;
        s32 idx;
        s32 offset;
        if (*(HSD_JObj**)(data_ptr + 0x4) != NULL) {
            idx = 1;
        } else {
            idx = 0;
        }
        *(s8*)(data_ptr + 0xE) = (s8)idx;
        tmp = data_ptr[0xE];
        offset = tmp;
        offset *= 4;
        offset += 4;
        *(HSD_JObj**)(data_ptr + offset) = jobj;
    }

    HSD_JObjAddTranslationY(jobj, 0.25F);

    *(u8*)(data_ptr + 0x11) = 2;
    *(u8*)(data_ptr + 0x10) = 2;
    *(u8*)(data_ptr + 0xF) = 0;

    un_80307F64(2, 0);

    scale_val = un_803060BC((int)arg1, 4);

    HSD_JObjSetScaleX(jobj, scale_val);
    HSD_JObjSetScaleY(jobj, scale_val);
    HSD_JObjSetScaleZ(jobj, scale_val);

    return jobj;
}

// Decompilation of fn_80307E84

void fn_80307E84(HSD_GObj* gobj)
{
    s32* base;
    ToyAnimState* state;
    s8 idx;
    s8 x0F_val;
    HSD_JObj* jobj0;
    HSD_JObj* jobj1;

    base = (s32*)un_804A26B8;
    state = (ToyAnimState*)((u8*)base + 0x3F0);
    idx = *(s8*)((u8*)base + 0x3FE);
    x0F_val = *(s8*)((u8*)base + 0x3FF);
    jobj0 = (HSD_JObj*)base[idx + (0x3F4 / 4)];
    jobj1 = (HSD_JObj*)base[(idx ^ 1) + (0x3F4 / 4)];

    if (x0F_val <= 0) {
        if (state->x10 == 1) {
            HSD_JObjSetFlagsAll(jobj0, 0x10);
            HSD_JObjSetFlagsAll(jobj1, 0x10);
        }
        state->x10 = 0;
        HSD_JObjRemoveAnimAll(jobj0);
        HSD_JObjRemoveAnimAll(jobj1);
        HSD_GObjProc_8038FED4(gobj);
    } else {
        state->x0F = state->x0F - 1;
        HSD_JObjAnimAll(jobj0);
        HSD_JObjAnimAll(jobj1);
    }
}

/* 98.4% match */
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
// Decompilation of un_8030813C
// Unit: main/melee/ty/toy

char* un_8030813C(s16 arg0, enum_t unused)
{
    char* ptr;
    s32 i;
    s32 found;

    found = 0;

    if (lbLang_IsSettingUS()) {
        if (*(s32*)(ptr = un_804D6EA4) == arg0) {
            found = 1;
        } else if (*(s32*)(ptr += 0x54) == arg0) {
            found = 1;
        } else if (*(s32*)(ptr += 0x54) == arg0) {
            found = 1;
        } else if (*(s32*)(ptr += 0x54) == arg0) {
            found = 1;
        } else if (*(s32*)(ptr += 0x54) == arg0) {
            found = 1;
        } else {
            ptr += 0x54;
        }
    }

    if (found == 0) {
        ptr = un_804D6EA8;
        for (i = 0x125; i != 0; i--) {
            if (*(s32*)ptr == arg0) {
                found = 1;
                break;
            }
            ptr += 0x54;
        }
    }

    if (found == 0) {
        OSReport("**** Not Found Toy Model!(%d)\n", arg0);
        __assert("toy.c", 0xBA3, "0");
    }

    return ptr;
}

/// #un_80308250

/* 91.2% match */
void un_803082F8(s16 idx)
{
    s32 trophyId = un_80308354(idx);
    un_803063D4((s16) trophyId, 2, 0x128);
}
void un_80308328(s32 arg0)
{
    un_803063D4((s16) arg0, 2, 0x128);
}
/* 68.1% match */
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
// Decompilation of un_803083D8
// Unit: main/melee/ty/toy

void un_803083D8(HSD_JObj* jobj, s32 arg1)
{
    s32 temp_r31;

    if (arg1 == 0x3E6) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
        return;
    }
    if (arg1 == 0x3E7) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    temp_r31 = (s32) un_803060BC(arg1, 8);
    if (temp_r31 == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, 0x10);
    if (temp_r31 == 1) {
        HSD_JObjReqAnim(jobj, 0.0F);
    } else {
        HSD_JObjReqAnim(jobj, 1.0F);
    }
    HSD_JObjAnim(jobj);
}

// m2c decompilation of un_803084A0
// Unit: main/melee/ty/toy

typedef struct tyDispData {
    u8 pad[0x144];
    HSD_Text* x144;
    HSD_Text* x148;
    HSD_Text* x14C;
    HSD_Text* x150;
} tyDispData;

static s32 un_804DDCFC = 0xFFBA00FF;


#pragma push
#pragma peephole on

void un_803084A0(s16 arg0)
{
    volatile s32 color;
    tyDispData* display;
    HSD_Text* text;
    s32 one;

    display = un_804D6EE0;
    color = un_804DDCFC;

    if (display->x144 == NULL) {
        display->x144 = HSD_SisLib_803A5ACC(0, un_804D6E70, 0.9F, -10.9F, 0.0F, 384.0F, 64.0F);
        one = 1;
        text = display->x144;
        text->default_fitting = one;
        text = display->x144;
        text->default_alignment = one;
        text = display->x144;
        *(s32*)&text->bg_color = color;
        if (lbLang_IsSavedLanguageJP()) {
            text = display->x144;
            text->font_size.x = 0.044F;
            text->font_size.y = 0.103F;
            text = display->x144;
            text->x34.x = 2.0F;
            text->x34.y = 1.0F;
        } else {
            text = display->x144;
            text->font_size.x = 0.044F;
            text->font_size.y = 0.103F;
            display->x144->default_kerning = one;
            text = display->x144;
            text->x34.x = 1.75F;
            text->x34.y = 1.0F;
        }
    }
    HSD_SisLib_803A6368(display->x144, un_803063D4(arg0, 2, 0x128));

    if (display->x148 == NULL) {
        if (lbLang_IsSavedLanguageJP()) {
            display->x148 = HSD_SisLib_803A5ACC(3, un_804D6E74, 0.2F, -5.1F, 17.2F, 384.0F, 384.0F);
            text = display->x148;
            text->font_size.x = 0.035F;
            text->font_size.y = 0.034F;
        } else {
            display->x148 = HSD_SisLib_803A5ACC(3, un_804D6E74, 0.2F, -5.0F, 17.2F, 384.0F, 384.0F);
            text = display->x148;
            text->font_size.x = 0.034F;
            text->font_size.y = 0.033F;
            text = display->x148;
            text->x34.x = 0.7F;
            text->x34.y = 0.7F;
        }
        text = display->x148;
        text->default_fitting = 1;
        text = display->x148;
        text->default_kerning = 1;
    }
    HSD_SisLib_803A6368(display->x148, un_803063D4(arg0, 2, 0x374));

    if (display->x14C == NULL) {
        if (lbLang_IsSavedLanguageJP()) {
            display->x14C = HSD_SisLib_803A5ACC(3, un_804D6E78, 0.7F, 7.9F, 17.2F, 384.0F, 64.0F);
            display->x150 = HSD_SisLib_803A5ACC(3, un_804D6E7C, 0.7F, 9.0F, 17.2F, 384.0F, 64.0F);
            text = display->x14C;
            text->font_size.x = 0.03F;
            text->font_size.y = 0.03F;
            text = display->x150;
            text->font_size.x = 0.03F;
            text->font_size.y = 0.03F;
        } else {
            display->x14C = HSD_SisLib_803A5ACC(3, un_804D6E78, 0.7F, 7.9F, 17.2F, 384.0F, 64.0F);
            display->x150 = HSD_SisLib_803A5ACC(3, un_804D6E7C, 0.7F, 9.0F, 17.2F, 384.0F, 64.0F);
            text = display->x14C;
            text->font_size.x = 0.03F;
            text->font_size.y = 0.03F;
            text = display->x150;
            text->font_size.x = 0.03F;
            text->font_size.y = 0.03F;
        }
        display->x14C->default_kerning = 1;
        display->x150->default_kerning = 1;
        text = display->x14C;
        text->x34.x = 1.0F;
        text->x34.y = 1.0F;
        text = display->x150;
        text->x34.x = 1.0F;
        text->x34.y = 1.0F;
        display->x14C->default_fitting = 1;
        display->x150->default_fitting = 1;
        display->x14C->default_alignment = 0;
        display->x150->default_alignment = 0;
    }
    HSD_SisLib_803A6368(display->x14C, un_803063D4(arg0, 0x128, 0x37A));
    HSD_SisLib_803A6368(display->x150, un_803063D4(arg0, 0x24E, 0x380));
}

#pragma pop

/// #un_803087F4

// Decompilation of un_80308DC8

void un_80307F64(s32 a, s32 b);
f32 un_80309338(Vec3* arg0, Vec3* arg1);

typedef struct un_804A2AA8_t {
    /* 0x00 */ u8 pad[0x4];
    /* 0x04 */ HSD_JObj* x4;
    /* 0x08 */ HSD_JObj* x8;
    /* 0x0C */ u8 padC[0x2];
    /* 0x0E */ u8 xE;
} un_804A2AA8_t;

typedef struct un_804D6E68_t {
    /* 0x00 */ u8 pad[0x18];
    /* 0x18 */ f32 x18;
} un_804D6E68_t;

void un_80308DC8(HSD_CObj* cobj)
{
    Vec3 interest;
    Vec3 eye_pos;
    un_804D6E68_t* temp_r30;
    un_804A2AA8_t* temp_r31;
    f32 temp_f1;

    temp_r31 = (un_804A2AA8_t*) un_804A2AA8;
    temp_r30 = (un_804D6E68_t*) un_804D6E68;

    HSD_CObjGetInterest(cobj, &interest);
    HSD_CObjGetEyePosition(cobj, &eye_pos);

    temp_f1 = temp_r30->x18;

    if (temp_f1 >= 25.0F ||
        (temp_f1 >= -3.0F && un_80309338(&eye_pos, 0) <= 15.0F))
    {
        un_80307F64(1, 1);
        return;
    }

    un_80307F64(2, 1);

    if (temp_r30->x18 < 10.0F) {
        if (eye_pos.y < 0.0F) {
            temp_r31->xE = 1;
            HSD_JObjClearFlagsAll(temp_r31->x8, 0x10);
            HSD_JObjSetFlagsAll(temp_r31->x4, 0x10);
        } else {
            temp_r31->xE = 0;
            HSD_JObjClearFlagsAll(temp_r31->x4, 0x10);
            HSD_JObjSetFlagsAll(temp_r31->x8, 0x10);
        }
    } else {
        temp_r31->xE = 1;
        HSD_JObjClearFlagsAll(temp_r31->x8, 0x10);
        HSD_JObjSetFlagsAll(temp_r31->x4, 0x10);
    }
}

// m2c decompilation of un_80308F04
// Unit: main/melee/ty/toy

typedef struct {
    Vec3 x0;
    u8 pad[0x3F0 - 0xC];
    void* x3F0;
} Toy26B8;

typedef struct {
    u8 x0[0x28];
    void* x28;
} Toy26B8_2;

typedef struct {
    u8 x0[0x4];
    void* x4;
    u8 x8[0x40 - 0x8];
    s32 x40;
} ToyJObjNode;

typedef struct {
    u8 x0[0xC];
    Toy26B8_2* xC;
} ToyED8Data;

typedef struct {
    u8 x0[0x18];
    f32 x18;
    u8 x1C[0x20 - 0x1C];
    f32 x20;
    u8 x24[0x58 - 0x24];
    s32 x58;
    s32 x5C;
    s8 x60;
    s8 x61;
} Toy6E68;


#define TOY_DATA ((Toy26B8*)un_804A26B8)
#define TOY_ED8 ((ToyED8Data*)un_804D6ED8)
#define TOY_STATE (*(Toy6E68**)&un_804D6E68)

void un_80308F04(HSD_CObj* cobj)
{
    Vec3 interest;
    Toy26B8* data;
    Toy6E68* state;
    void* jobj_ptr;
    f32 top;
    f32 bottom;
    f32 right;
    f32 left;
    ToyJObjNode* jobj;

    data = TOY_DATA;
    state = TOY_STATE;
    jobj_ptr = ((Toy26B8_2*)data->x3F0)->x28;

    top = HSD_CObjGetTop(cobj);
    bottom = HSD_CObjGetBottom(cobj);
    right = HSD_CObjGetRight(cobj);
    left = HSD_CObjGetLeft(cobj);

    if (jobj_ptr == NULL) {
        __assert("jobj.h", 0x378, "jobj");
    }

    if (state->x61 == 1) {
        if ((f32)state->x5C < 10.0F) {
            un_804D6E80 = un_804D6E80 - 0.0013187003F;
            if (top != un_804D6E80) {
                f32 val = un_804D6E80;
                if (val < 0.036397F) {
                    val = 0.036397F;
                }
                HSD_CObjSetTop(cobj, val);
            }

            un_804D6E84 = un_804D6E84 - 0.00008119978F;
            if (bottom != un_804D6E84) {
                f32 val = un_804D6E84;
                if (val < -0.036397F) {
                    val = -0.036397F;
                }
                HSD_CObjSetBottom(cobj, val);
            }

            un_804D6E88 = un_804D6E88 - 0.0032531999F;
            if (right != un_804D6E88) {
                f32 val = un_804D6E88;
                if (val < 0.044307F) {
                    val = 0.044307F;
                }
                HSD_CObjSetRight(cobj, val);
            }

            un_804D6E8C = un_804D6E8C - 0.0017468001F;
            if (left != un_804D6E8C) {
                HSD_CObjSetLeft(cobj, un_804D6E8C);
            }

            state->x5C = state->x5C + 1;
        } else {
            HSD_CObjSetTop(cobj, 0.036397F);
            HSD_CObjSetBottom(cobj, -0.036397F);
            HSD_CObjSetRight(cobj, 0.044307F);
            HSD_CObjSetLeft(cobj, -0.044307F);

            if (un_804D6E58 != 0) {
                jobj = TOY_ED8->xC->x28;
                while (jobj != NULL) {
                    jobj->x40 = 9;
                    jobj = jobj->x4;
                }
            } else {
                jobj = TOY_ED8->xC->x28;
                while (jobj != NULL) {
                    jobj->x40 = 8;
                    jobj = jobj->x4;
                }
            }

            state->x61 = 2;
            state->x5C = 0;
            state->x60 = 4;
            HSD_PadRenewStatus();
        }
    } else {
        if ((f32)state->x5C < 10.0F) {
            state->x20 = state->x20 - un_804D6E90;
            state->x18 = state->x18 - un_804D6E94;

            HSD_CObjGetInterest(cobj, &interest);
            interest.x = interest.x + data->x0.x;
            interest.y = interest.y + data->x0.y;
            interest.z = interest.z + data->x0.z;
            HSD_CObjSetInterest(cobj, &interest);

            un_80308DC8(cobj);

            un_804D6E80 = un_804D6E80 + 0.0013187003F;
            if (top != un_804D6E80) {
                f32 val = un_804D6E80;
                if (val > 0.049584F) {
                    val = 0.049584F;
                }
                HSD_CObjSetTop(cobj, val);
            }

            un_804D6E84 = un_804D6E84 + 0.00008119978F;
            if (bottom != un_804D6E84) {
                f32 val = un_804D6E84;
                if (val > -0.035585F) {
                    val = -0.035585F;
                }
                HSD_CObjSetBottom(cobj, val);
            }

            un_804D6E88 = un_804D6E88 + 0.0032531999F;
            if (right != un_804D6E88) {
                f32 val = un_804D6E88;
                if (val > 0.076839F) {
                    val = 0.076839F;
                }
                HSD_CObjSetRight(cobj, val);
            }

            un_804D6E8C = un_804D6E8C + 0.0017468001F;
            if (left != un_804D6E8C) {
                HSD_CObjSetLeft(cobj, un_804D6E8C);
            }

            state->x5C = state->x5C + 1;
        } else {
            state->x61 = 0;
            un_80307828(1);

            HSD_CObjSetTop(cobj, 0.049584F);
            HSD_CObjSetBottom(cobj, -0.035585F);
            HSD_CObjSetRight(cobj, 0.076839F);
            HSD_CObjSetLeft(cobj, -0.026839F);

            un_803102C4(1);

            state->x5C = 0;
            state->x58 = 0x95E;
            state->x60 = 4;
            HSD_PadRenewStatus();
        }
    }
}

// Decompilation of un_80309338
// Unit: main/melee/ty/toy

static Vec3 un_803B88D4;

f32 un_80309338(Vec3* arg0, Vec3* arg1)
{
    f64 unused[2];
    Vec3 sp14;
    volatile f32 sp10;
    Vec3* var_r3;
    Vec3* var_r4;
    f32 dy;
    f32 dx;
    f32 dz;
    f32 var_f1;
    f64 guess;

    sp14 = un_803B88D4;
    var_r3 = arg0;
    var_r4 = arg1;
    if (var_r3 == NULL) {
        var_r3 = &sp14;
    }
    if (var_r4 == NULL) {
        var_r4 = &sp14;
    }
    dy = var_r3->y - var_r4->y;
    dx = var_r3->x - var_r4->x;
    dz = var_r3->z - var_r4->z;
    var_f1 = dy * dy + dx * dx + dz * dz;
    if (var_f1 > 0.0F) {
        guess = __frsqrte((f64)var_f1);
        guess = 0.5 * guess * (3.0 - guess * guess * var_f1);
        guess = 0.5 * guess * (3.0 - guess * guess * var_f1);
        guess = 0.5 * guess * (3.0 - guess * guess * var_f1);
        sp10 = (f32)(var_f1 * guess);
        var_f1 = sp10;
    }
    return var_f1;
}

/// #fn_80309404

/// #fn_8030B530

/// #fn_8030E110

/// #un_8030FA50

/// #un_8030FE48

void un_803102C4(s8 arg0)
{
    ((TyViewData*) un_804D6E6C)->x4 = arg0;
}

/* 72.4% match */
void un_803102D0(void)
{
    if (un_804D6ECC == NULL) {
        un_804D6ECC = lbArchive_LoadSymbols(str_TyDataf_dat, &un_804D6EA8,
                                            str_tyModelFileTbl, &un_804D6EA4,
                                            str_tyModelFileUsTbl, NULL);
    }
}

/* 69.1% match */
extern f32 un_804DDCD8;
extern f32 un_804DDCF0;

typedef struct ToyGlobalsS_ {
    u8 pad0[0x8];
    HSD_GObj* x8;
    HSD_GObj* xC;
    u8 pad10[0x20];
    void* x30;
    u8 pad34[0x1C];
    void* x50;
    void* x54;
} ToyGlobalsS_;

typedef struct ToyGlobals2S_ {
    HSD_GObj* x0;
    u8 x4;
} ToyGlobals2S_;

typedef struct ToyGlobals3S_ {
    u8 pad0[0x10];
    s32 x10;
} ToyGlobals3S_;

typedef struct ToyGlobals4S_ {
    u8 pad0[0x58];
    s32 x58;
} ToyGlobals4S_;

typedef struct ToyGlobals5S_ {
    u8 pad0[0x140];
    void* x140;
    u8 pad144[0x10];
    s16 x154;
} ToyGlobals5S_;

typedef struct ToySubStructS_ {
    u8 pad0[0x10];
    s16 x10;
} ToySubStructS_;

void un_80310324(void)
{
    char* toy;
    char* data;
    ToyGlobalsS_* tg;
    ToyGlobalsS_* tg2;
    ToyGlobals2S_* tg3;
    ToyGlobals3S_* tg4;
    ToyGlobals4S_* tg5;
    ToyGlobals5S_* tg6;
    ToySubStructS_* sub;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32* ptr;
    s32 i;
    s32 one;
    s16 idx;
    s16 var_r0;
    char* str;
    HSD_SObj_803A477C_t* sobj;
    HSD_GObj* gobj;
    u16* flags;
    f32 two;

    data = un_803FDD18;
    toy = (char*) un_804A26B8;
    tg = un_804D6ED8;

    un_8030663C();
    un_803067BC((s8) toy[0x195], (s8) toy[0x196]);

    if (tg->x50 == NULL) {
        if (lbLang_IsSavedLanguageJP() != 0) {
            str = data + 0x5E8;
        } else {
            str = data + 0x5F8;
        }
        tg->x50 = lbArchive_LoadSymbols(str, &sp24, *(void**)(data + 0x188), NULL);
    }

    memzero(un_804D6E68, 0x64);
    un_8030FA50();
    memzero(un_804D6ED4, 0xE4);
    un_80306D70(0);
    un_80307018();

    tg2 = un_804D6ED8;
    if (tg2->x54 == NULL) {
        tg2->x54 = lbArchive_LoadSymbols(
            data + 0x640, &sp18,
            *(void**)(data + 0x320), &sp1C,
            *(void**)(data + 0x324), &sp20,
            *(void**)(data + 0x328), 0);

        tg2->x8 = GObj_Create(4, 5, 0);
        GObj_SetupGXLink(tg2->x8, HSD_SObjLib_803A49E0, 0x32, 0);

        i = 0;
        ptr = &sp18;
        two = un_804DDCF0;
        one = 1;
        do {
            sobj = HSD_SObjLib_803A477C(tg2->x8, *ptr, 0, 0, 0x80, 0);
            *(f32*)((char*)sobj + 0x1C) = two;
            i += 1;
            *(f32*)((char*)sobj + 0x20) = two;
            ptr += 1;
            *(s32*)((char*)sobj + 0x40) = one;
        } while (i < 3);
    }

    un_803075E8(0);
    un_80307470(0);
    un_803078E4();

    gobj = ((ToyGlobalsS_*)un_804D6ED8)->xC;
    gobj = *(HSD_GObj**)((char*)gobj + 0x28);
    while (gobj != NULL) {
        *(s32*)((char*)gobj + 0x40) = 9;
        gobj = *(HSD_GObj**)((char*)gobj + 0x4);
    }

    if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
        var_r0 = *(s16*)(toy + 0x3EC);
    } else {
        var_r0 = *gmMainLib_8015CC90();
    }

    if (var_r0 != 0) {
        memzero(toy + 0x3F0, 0x14);
        un_8030FE48(un_804D6EE0, 0);
        tg6 = un_804D6EE0;
        un_803087F4(tg6->x140);

        tg6 = un_804D6EE0;
        idx = un_804D6EDC[tg6->x154];

        if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
            flags = (u16*)(toy + 0x19E);
        } else {
            flags = gmMainLib_8015CC78();
        }

        if (flags[idx] & 0x8000) {
            tg6 = un_804D6EE0;
            idx = un_804D6EDC[tg6->x154];

            if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
                flags = (u16*)(toy + 0x19E);
            } else {
                flags = gmMainLib_8015CC78();
            }

            flags[idx] ^= 0x8000;
        }

        tg6 = un_804D6EE0;
        sub = tg6->x140;
        un_803084A0(sub->x10);

        tg6 = un_804D6EE0;
        sub = tg6->x140;
        un_803083D8(tg->x30, sub->x10);

        tg3 = un_804D6E6C;
        tg3->x0 = GObj_Create(6, 7, 0);
        GObj_SetupGXLink(tg3->x0, (void (*)(HSD_GObj*, int))un_80312050, 0x39, 0);
        tg3->x4 = 1;
    }

    un_80307828(0);

    tg5 = (ToyGlobals4S_*)un_804D6E68;
    tg5->x58 = 0x95E;

    un_8030715C(un_804DDCD8, un_804DDCD8);

    tg4 = un_804D6ED4;
    tg4->x10 = 0;
    un_80306D70(tg4->x10);
    un_803075E8(tg4->x10);
    HSD_PadRenewStatus();
}

// Decompilation of un_80310660
// Unit: main/melee/ty/toy

typedef struct TyUnk25 {
    u8 pad[0x140];
    void* x140;
    u8 pad2[0x10];
    s16 x154;
} TyUnk25;

void un_80310660(s32 arg0)
{
    s32 idx;
    s32 arg;
    u8* state;
    void** ty31;
    void* ty28;
    u8* ty27;
    void* ty26;
    TyUnk25* ty25;
    void* ty30;

    state = (u8*) un_804A26B8;
    arg = arg0;
    ty27 = state + 0x3F0;
    ty31 = un_804D6E68;
    ty28 = un_804D6ED4;
    ty26 = un_804D6E6C;
    ty25 = un_804D6EE0;
    ty30 = un_804D6ED8;

    if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
        idx = *(s16*)(state + 0x3EC);
    } else {
        idx = *gmMainLib_8015CC90();
    }

    if (idx != 0) {
        u16* ptr;
        idx = un_804D6EDC[ty25->x154];

        if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
            ptr = (u16*)(state + 0x19E);
        } else {
            ptr = gmMainLib_8015CC78();
        }

        if (ptr[idx] & 0x8000) {
            idx = un_804D6EDC[ty25->x154];

            if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
                ptr = (u16*)(state + 0x19E);
            } else {
                ptr = gmMainLib_8015CC78();
            }
            ptr[idx] ^= 0x8000;
        }

        *(s16*)(state + 0x3E8) = ty25->x154;
        *(s16*)(state + 0x3EA) = *(s16*)((u8*)ty25->x140 + 0x10);
    }

    if (arg != 0) {
        void* loopPtr;
        s32 count;

        HSD_SisLib_803A5E70();
        *(s32*)((u8*)ty25 + 0x150) = 0;
        *(s32*)((u8*)ty25 + 0x14C) = 0;
        *(s32*)((u8*)ty25 + 0x148) = 0;
        *(s32*)((u8*)ty25 + 0x144) = 0;

        if (gm_8016B498() != 0 || (u8)gm_801A4310() == 0xC) {
            idx = *(s16*)(state + 0x3EC);
        } else {
            idx = *gmMainLib_8015CC90();
        }

        if (idx != 0) {
            loopPtr = ty25;
            count = 0;
            arg = 0;
            do {
                if (*(void**)((u8*)loopPtr + 0x14) != NULL) {
                    lbArchive_80016EFC(*(void**)((u8*)loopPtr + 0x14));
                    *(void**)((u8*)loopPtr + 0x14) = (void*)arg;
                }
                count += 1;
                loopPtr = (u8*)loopPtr + 0x18;
            } while (count < 0xD);
        }

        if (un_804D6EC8 != NULL) {
            lbArchive_80016EFC(un_804D6EC8);
            un_804D6EC8 = NULL;
        }

        if (*(void**)((u8*)ty28 + 0xC) != NULL) {
            lbArchive_80016EFC(*(void**)((u8*)ty28 + 0xC));
            *(void**)((u8*)ty28 + 0xC) = NULL;
        }

        if (*(void**)((u8*)ty30 + 0x58) != NULL) {
            lbArchive_80016EFC(*(void**)((u8*)ty30 + 0x58));
            arg = 0;
            *(void**)((u8*)ty30 + 0x58) = (void*)arg;
            if (*(void**)((u8*)ty30 + 0xC) != NULL) {
                HSD_GObjPLink_80390228(*(void**)((u8*)ty30 + 0xC));
                *(void**)((u8*)ty30 + 0xC) = (void*)arg;
            }
        }

        if (*(void**)ty27 != NULL) {
            HSD_GObjPLink_80390228(*(void**)ty27);
            *(void**)ty27 = NULL;
            *(void**)(ty27 + 0x8) = NULL;
            *(void**)(ty27 + 0x4) = NULL;
        }

        if (*(void**)ty26 != NULL) {
            HSD_GObjPLink_80390228(*(void**)ty26);
            *(void**)ty26 = NULL;
        }

        if (*(void**)ty28 != NULL) {
            HSD_GObjPLink_80390228(*(void**)ty28);
            *(void**)ty28 = NULL;
            *(void**)((u8*)ty28 + 0x10) = NULL;
        }

        if (*(void**)((u8*)ty28 + 0x4) != NULL) {
            HSD_GObjProc_8038FED4(*(void**)((u8*)ty28 + 0x4));
            HSD_GObjPLink_80390228(*(void**)((u8*)ty28 + 0x4));
            *(void**)((u8*)ty28 + 0x4) = NULL;
        }

        if (*(void**)((u8*)ty28 + 0x8) != NULL) {
            HSD_GObjPLink_80390228(*(void**)((u8*)ty28 + 0x8));
            *(void**)((u8*)ty28 + 0x8) = NULL;
            HSD_FogSet(NULL);
        }

        if (*(void**)((u8*)ty30 + 0xC) != NULL) {
            HSD_GObjPLink_80390228(*(void**)((u8*)ty30 + 0xC));
            *(void**)((u8*)ty30 + 0xC) = NULL;
        }

        if (ty31[0] != NULL) {
            HSD_GObjPLink_80390228(ty31[0]);
            ty31[0] = NULL;
        }

        if (ty31[1] != NULL) {
            HSD_GObjPLink_80390228(ty31[1]);
            ty31[1] = NULL;
        }

        if (ty31[2] != NULL) {
            HSD_GObjPLink_80390228(ty31[2]);
            ty31[2] = NULL;
        }

        if (ty31[3] != NULL) {
            HSD_GObjPLink_80390228(ty31[3]);
            ty31[3] = NULL;
        }

        if (ty31[4] != NULL) {
            HSD_GObjPLink_80390228(ty31[4]);
            ty31[4] = NULL;
        }

        if (ty31[5] != NULL) {
            HSD_GObjPLink_80390228(ty31[5]);
            ty31[5] = NULL;
        }
    }
}

/* 87.7% match */
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
// m2c decompilation of un_80311680
// Unit: main/melee/ty/toy


void un_80311680(void) {
    s16* temp_r31;
    s16* var_r30;
    u16* var_r29;
    s32 var_r28;
    s16 temp_r0;
    s32 var_r0;
    s16* temp_r3;
    s16 temp_r5;
    s32 temp_r0_2;

    var_r29 = gmMainLib_8015CC78();
    temp_r31 = gmMainLib_8015CC84();
    un_80311960();
    var_r28 = 0;
    do {
        var_r30 = un_804D6EB4;
        if (lbLang_IsSettingUS() != 0) {
            while ((temp_r0 = *var_r30) != -1) {
                if (temp_r0 == var_r28) {
                    var_r0 = 0;
                    goto check_var;
                }
                var_r30++;
            }
        }
        var_r0 = 1;
check_var:
        if (var_r0 != 0) {
            temp_r3 = gmMainLib_8015CC90();
            temp_r5 = *temp_r3;
            temp_r5 = temp_r5 + 1;
            *temp_r3 = temp_r5;
            *var_r29 = 1;
            temp_r0_2 = (s32)un_803060BC(var_r28, 6);
            if ((u32)temp_r0_2 > 1U && temp_r0_2 != 8 && temp_r0_2 != 3) {
                *var_r29 |= 0x4000;
            }
        }
        var_r28++;
        var_r29++;
    } while (var_r28 < 0x125);
    *temp_r31 = 0xF4;
    un_804D6EA1 = 1;
}

/* 81.3% match */
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

// Decompilation of un_80311F5C
// Unit: main/melee/ty/toy

#include <platform.h>

void DevText_Remove(DevText** ptext);
void HSD_Free(void* ptr);


void un_80311F5C(void)
{
    void** p1 = un_804D6ED8;
    void** p2 = un_804D6E68;

    if (p1[0x14] != NULL) {
        p1[0x14] = NULL;
    }
    if (p1[0] != NULL) {
        p1[0] = NULL;
    }
    if (p2[0] != NULL) {
        p2[0] = NULL;
    }
    if (un_804D6EA2 != 0 && un_804D6E9C != NULL) {
        DevText_Remove(&un_804D6E9C);
        un_804D6E9C = NULL;
    }
    if (un_804D6E98 != NULL) {
        DevText_Remove(&un_804D6E98);
        un_804D6E98 = NULL;
    }
    if (un_804D6E5C != NULL) {
        HSD_Free(un_804D6E5C);
        un_804D6E5C = NULL;
    }
}

void un_80312018_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_80311F5C();
        gm_801A4B60();
    }
}
/* 91.8% match */
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
