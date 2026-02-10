#include "gm_18A5.h"

#include "gm_18A5.static.h"

#include "ft/forward.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/particle.h>
#include <sysdolphin/baselib/random.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmtou.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnmainrule.h>
#include <melee/mn/mnname.h>
#include <melee/mn/mnnamenew.h>
#include <melee/mn/mnstagesel.h>
#include <melee/pl/player.h>

extern char* lbl_804DA6C4;
extern char* lbl_804DA6C8;
extern char* lbl_804DA6CC;
extern char* lbl_804DA6D0;

typedef void (*lbl_803D9FD8_fn)(s32*, u32, u32);

lbl_803D9FD8_fn lbl_803D9FD8[] = {
    fn_801937C4, fn_80193B58, fn_80193FCC, fn_80194658, fn_801949B4,
    fn_80194BC4, fn_80194D84, fn_80194D84, fn_80194D84, NULL,
    fn_80194F30, fn_801953C8, fn_80194F30, fn_80195AF0, fn_80195AF0,
    fn_80195CCC, fn_80194F30, fn_8019610C, fn_8019610C,
};

/// #fn_8018A514

void fn_8018A970(int arg0)
{
    int i;
    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x0 != 0) {
            HSD_GObj* gobj = GObj_Create(0xE, 0x1B, 0);
            gobj->user_data = &lbl_80473AB8[i];
            if (i == 0) {
                HSD_GObjProc_8038FD54(gobj, fn_8018B090, 0);
            }
            GObj_SetupGXLink(gobj, fn_8018E46C, 4, 1);
        }
    }

    if (arg0 < 9) {
        if (arg0 == 1) {
            lbl_80473AB8[5].x5E = 1;
        } else if (arg0 == 3) {
            lbl_80473AB8[10].x32 = 1;
            lbl_80473AB8[11].x5E = 1;
        } else if (arg0 == 5) {
            lbl_80473AB8[23].x5E = 1;
        } else if (arg0 == 7) {
            lbl_80473AB8[46].x5E = 1;
            lbl_80473AB8[47].x5E = 1;
        }
    }
}

/// #fn_8018AA74

/// #fn_8018B090

/// #fn_8018C8D4

/// #fn_8018D50C

/// #fn_8018DC18

/// #fn_8018DF68

/// @TODO: Currently 98.8% match - permuter couldn't improve beyond score 140
void fn_8018E46C(HSD_GObj* gobj, int unused)
{
    void* data;
    s32 temp;
    s32 r30;
    u8* data_u8;
    s32* data_s32;
    f32* data_f32;

    data = gobj->user_data;
    data_u8 = (u8*) data;
    data_s32 = (s32*) data;
    data_f32 = (f32*) data;

    if (data_u8[2] != 0) {
        temp = -(data_s32[0x10 / 4] + data_s32[0x18 / 4]);
    } else {
        temp = -data_s32[0x10 / 4];
    }
    r30 = temp;
    HSD_FogSet(NULL);
    hsd_80391A04(1.0F, 1.0F, 1);
    switch (data_u8[3]) {
    case 0:
        fn_8018C8D4(data,
                    data_s32[0xC / 4] - (s32) (0.5F * data_f32[0x1C / 4]),
                    -data_s32[0x10 / 4], data_s32[0x14 / 4],
                    -data_s32[0x18 / 4], r30, data_s32[0xC / 4], 0.5F);
        break;
    case 1:
        fn_8018D50C(data,
                    data_s32[0xC / 4] - (s32) (0.5F * data_f32[0x1C / 4]),
                    -data_s32[0x10 / 4], data_s32[0x14 / 4],
                    -data_s32[0x18 / 4], r30, data_s32[0xC / 4], 0.5F);
        break;
    case 2:
        fn_8018DC18(data,
                    data_s32[0xC / 4] - (s32) (0.5F * data_f32[0x1C / 4]),
                    -data_s32[0x10 / 4], data_s32[0x14 / 4],
                    -data_s32[0x18 / 4], r30, data_s32[0xC / 4], 0.5F);
        break;
    case 3:
        fn_8018DF68(data,
                    data_s32[0xC / 4] - (s32) (0.5F * data_f32[0x1C / 4]),
                    -data_s32[0x10 / 4], data_s32[0x14 / 4],
                    -data_s32[0x18 / 4], r30, data_s32[0xC / 4], 0.5F);
        break;
    }
}

/// #fn_8018E618

/// #fn_8018E85C

void fn_8018EC48(void)
{
    mn_8022F138(0x19, 0x1C);
    mn_8022F138(0x12, 0x15);
}

void fn_8018EC7C(void)
{
    mn_8022F0F0(0x1B);
    mn_8022F0F0(0x14);
}

/// #fn_8018ECA8

/// Formats a tournament slot display name into a destination buffer.
void fn_8018F00C(char* dest, s32 slot_id)
{
    char* templates_800[2];
    char* templates_900[2];
    char* tmpl_800;
    char* tmpl_900;

    templates_800[0] = lbl_804DA6C4;
    templates_900[0] = lbl_804DA6CC;
    templates_800[1] = lbl_804DA6C8;
    templates_900[1] = lbl_804DA6D0;

    tmpl_800 = templates_800[!!lbLang_IsSavedLanguageUS()];
    tmpl_900 = templates_900[!!lbLang_IsSavedLanguageUS()];

    if (slot_id >= 0x320) {
        if (slot_id < 0x384) {
            /* Slot IDs 800-899: format as 2-digit number (00-99) */
            s32 diff = slot_id - 0x320;
            if (diff < 10) {
                /* Single digit: write digit + null terminator */
                tmpl_800[7] = (s8) (slot_id - 0x2F0);
                tmpl_800[8] = 0;
            } else {
                /* Double digit: write tens, ones, null terminator */
                tmpl_800[7] = (s8) (diff / 10 + 0x30);
                tmpl_800[8] = (s8) (diff % 10 + 0x30);
                tmpl_800[9] = 0;
            }
            strcpy(dest, tmpl_800);
        } else if (slot_id != 0x3E7) {
            /* Slot IDs 900-998: format as 2-digit number (00-98) */
            s32 diff = slot_id - 0x384;
            if (diff < 10) {
                /* Single digit: write digit + null terminator */
                tmpl_900[7] = (s8) (slot_id - 0x354);
                tmpl_900[8] = 0;
            } else {
                /* Double digit: write tens, ones, null terminator */
                tmpl_900[7] = (s8) (diff / 10 + 0x30);
                tmpl_900[8] = (s8) (diff % 10 + 0x30);
                tmpl_900[9] = 0;
            }
            strcpy(dest, tmpl_900);
        }
    } else {
        /* Slot IDs below 800: use player nametag text */
        strcpy(dest, GetNameText((u8) slot_id));
    }
}

s32 gm_8018F1B0(MatchEnd* me)
{
    TmData* tm;

    tm = gm_8018F634();

    switch (gm_804771C4.match_type) {
    case 0:
        return 1;

    case 1:
        switch (tm->hmn_cpu_count) {
        case 1:
            return 1;

        case 2:
            if (tm->x30 == 3) {
                if (me->n_winners == 3) {
                    return 1;
                }
            } else if (tm->x30 == 4) {
                if (me->n_winners >= 3) {
                    return 1;
                }
            }
            break;

        case 3:
            if (me->n_winners == 4) {
                return 1;
            }
            break;
        }
        break;

    case 2:
        switch (tm->hmn_cpu_count) {
        case 1:
            if (tm->x30 == me->n_winners) {
                return 1;
            }
            break;

        case 2:
            if (tm->x30 == 3) {
                return 1;
            } else if (tm->x30 == 4) {
                if (me->n_winners >= 3) {
                    return 1;
                }
            }
            break;

        case 3:
            return 1;
        }
        break;
    }

    return 0;
}

int fn_8018F310(int arg0)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(lbl_803D9D20.x59); i++) {
        if (lbl_803D9D20.x59[i] == arg0) {
            return i;
        }
    }
    return -1;
}

u8 fn_8018F3BC(s32 arg0)
{
    return lbl_803D9D20.x59[arg0];
}

int fn_8018F3D0(int arg0)
{
    if (arg0 == 0xE || (arg0 >= 0x10 && arg0 <= 0x13) || arg0 == 0xA) {
        return 1;
    }
    if (arg0 <= 0xD) {
        return 0;
    }
    return 2;
}

int fn_8018F410(void)
{
    int temp_r3;
    int* temp_r30;
    int* temp_r29;

    temp_r30 = &lbl_803D9F0C.x8;
    temp_r29 = &lbl_803D9F0C.x4;
    do {
        temp_r3 = HSD_Randi(0x19);
    } while (lbl_803D9D20.x72[temp_r3] == 0 || lbl_803D9F0C.x0 == temp_r3 ||
             *temp_r29 == temp_r3 || *temp_r30 == temp_r3);
    *temp_r30 = *temp_r29;
    *temp_r29 = lbl_803D9F0C.x0;
    lbl_803D9F0C.x0 = temp_r3;
    return temp_r3;
}

/// #fn_8018F410

int fn_8018F4A0(void)
{
    int temp_r3 = mnStageSel_8025BBD4();
    if (!gm_80164430(temp_r3)) {
        printf("This is impossible stage num from mnSelStageRandom() -> stage "
               "%d \n",
               temp_r3);
        __assert("gmtoulib.c", 0x53D, "0");
    }
    return temp_r3;
}

/// Counts available tournament slots and returns the last found index.
s32 fn_8018F508(s32* out_index)
{
    s32 count;
    u8* base_ptr;
    u8* slot_ptr;
    s32 i;

    count = 0;
    base_ptr = (u8*) &lbl_80473AB8[fn_8018F74C()];
    slot_ptr = base_ptr;

    if (slot_ptr[0x0] == 0) {
        return -1;
    }

    for (i = 0; i < 4; i++) {
        if (slot_ptr[0x4E] != 3) {
            if (out_index != NULL) {
                *out_index = i;
            }
            count++;
        }
        slot_ptr += 0x2C;
    }

    return count;
}

#pragma push
#pragma dont_inline on
char* fn_8018F5F0(void)
{
    if (lbLang_IsSavedLanguageUS()) {
        return "SdTou.usd";
    } else {
        return "SdTou.dat";
    }
}
#pragma pop

/// ???
/// tournament uses the user data as just an int
/// it controls various menu jobj states ie animation state, visibility, etc
#pragma dont_inline on
u32 fn_8018F62C(HSD_GObj* gobj)
{
    return (u32) gobj->user_data;
}
#pragma dont_inline off

#pragma push
#pragma dont_inline on
TmData* gm_8018F634(void)
{
    return &gm_804771C4;
}
#pragma pop

#pragma dont_inline on
u32 fn_8018F640(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36A0(arg0);
}

u32 fn_8018F674(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36C0(arg0);
}
#pragma dont_inline off

u32 fn_8018F6A8(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A3680((u8) arg0);
}

int fn_8018F6DC(int arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 - 1;
    }
    return arg0;
}

CharacterKind fn_8018F6FC(CSSIconHud arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 + 1;
    }
    return (CharacterKind) arg0;
}

float fn_8018F71C(int arg0, int arg1)
{
    return arg0 + arg1 * 0x1E;
}

int fn_8018F74C(void)
{
    int i;

    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x1 != 0) {
            break;
        }
    }

    return i;
}

int fn_8018F808(void)
{
    int i;
    int noerrcount = 0;
    for (i = 0; i < 4; i++) {
        if (HSD_PadMasterStatus[(u8) i].err == 0) {
            noerrcount += 1;
        }
    }
    return noerrcount;
}

/// @TODO: Currently 78.75% match - needs register allocation fix
void fn_8018F888(void)
{
    s32 idx;
    u8* ptr;
    u8* base;
    s32 ctr;
    u8 val;
    s32 idx2;

    base = (u8*) lbl_80473AB8;
    ctr = 8;
    ptr = base;
    idx = 0;

loop1:
    if (*(ptr + 0x1) != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx += 1;
    if (val != 0) {
        goto done1;
    }
    ptr += 0xDC;
    idx += 1;
    ctr -= 1;
    if (ctr != 0) {
        goto loop1;
    }

done1:
    idx2 = 0;
    *(base + idx * 0xDC + 0x21) = 0;

    if (*(base + 0x373F) != 5) {
        return;
    }

    ctr = 8;
    ptr = base;

loop2:
    if (*(ptr + 0x1) != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    val = *(ptr + 0xDD);
    ptr += 0xDC;
    idx2 += 1;
    if (val != 0) {
        goto done2;
    }
    ptr += 0xDC;
    idx2 += 1;
    ctr -= 1;
    if (ctr != 0) {
        goto loop2;
    }

done2:
    *(base + idx2 * 0xDC + 0xFD) = 0;
}

/// @TODO: Currently 84.63% match - needs loop pattern fix

void fn_8018FA24(void)
{
    s32 player_count;
    s32 player_idx;
    u8* tmdata;
    u8* dst;
    u8* ptr;
    s32 slot;
    s32 char_kind;
    s32 ctr;

    ptr = (u8*) lbl_80473AB8;
    tmdata = ptr + 0x370C;
    slot = 0;

    ctr = 8;
    do {
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
        if (ptr[0x01] != 0) {
            goto found;
        }
        ptr += 0xDC;
        slot += 1;
    } while (--ctr != 0);

found:
    dst = tmdata;
    ptr = (u8*) lbl_80473AB8 + slot * 0xDC;
    player_count = 0;
    player_idx = 0;

    do {
        dst[0x4B6] = ptr[0x30];
        dst[0x4B7] = ptr[0x50];
        *(u16*) (dst + 0x4BE) = *(u16*) (tmdata + 0x40 + ptr[0x50] * 0x12);
        dst[0x4BC] = ptr[0x51];
        dst[0x4BD] = ptr[0x52];
        dst[0x4B9] = ptr[0x4D];
        char_kind = dst[0x4B9];
        if (char_kind >= 0x13) {
            if (char_kind == 0x1D) {
                char_kind = 5;
            } else {
                char_kind += 1;
            }
        }
        Player_SetPlayerCharacter(player_idx, char_kind);
        dst[0x4B8] = ptr[0x4E];
        char_kind = dst[0x4B8];
        if (char_kind != 3) {
            player_count += 1;
        }
        Player_SetSlottype(player_idx, char_kind);
        dst[0x4BB] = ptr[0x4F];
        Player_SetCostumeId(player_idx, dst[0x4BB]);
        dst[0x4BC] = ptr[0x51];
        player_idx += 1;
        ptr += 0x2C;
        dst += 0xA;
    } while (player_idx < 4);

    tmdata[0x30] = player_count;
}

void fn_8018FBD8(void* arg0, s32 arg1)
{
    M2C_FIELD(arg0, s32*, 0x2C) = arg1;
}

/// #fn_8018FBE0

void fn_8018FDC4(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetTranslateX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetTranslateY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetTranslateZ(jobj, z);
    }
}

void fn_8018FF9C(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetScaleX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetScaleY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetScaleZ(jobj, z);
    }
}

HSD_GObj* fn_80190174(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x12, 0);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 7;
    return gobj;
}

HSD_GObj* fn_801901F8(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x15, 2);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 2);
    gobj->gxlink_prios = 0xA;
    return gobj;
}

void fn_8019027C(UNK_T lights)
{
    HSD_GObj* gobj = GObj_Create(0xB, 0x1A, 0);
    HSD_LObj* lobj = lb_80011AC4(lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 1, 0);
}

static HSD_GObj* lbl_804D663C;

/// Initializes SIS library text rendering for tournament mode.
void fn_801902F0(int sis_param)
{
    s32 value;
    PAD_STACK(8);

    value = sis_param;
    HSD_SisLib_803A5E70();
    if (*(s32*) ((u8*) &gm_804771C4 + 0x1C) == 0) {
        value = 0;
    }
    lbl_804D663C = (HSD_GObj*) HSD_SisLib_803A611C(0, (HSD_GObj*) value, 9,
                                                   0x12, 0, 3, 0, 0x13);
}

HSD_GObj* fn_8019035C(bool arg0, DynamicModelDesc* model, int arg2, int arg3,
                      int arg4, bool arg5, void (*arg6)(HSD_GObj*), f32 arg8)
{
    HSD_GObj* gobj = GObj_Create(0xE, arg3, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, arg4, 0);
    if (arg6 != NULL) {
        HSD_GObjProc_8038FD54(gobj, arg6, 0);
    }
    if (arg5) {
        gm_8016895C(jobj, model, arg2);
        HSD_JObjReqAnimAll(jobj, arg8);
        HSD_JObjAnimAll(jobj);
        if (arg0) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
    return gobj;
}

#pragma dont_inline on
void fn_8019044C(HSD_JObj* jobj, float arg1)
{
    HSD_JObjReqAnimAll(jobj, arg1);
    HSD_JObjAnimAll(jobj);
}
#pragma dont_inline off

void fn_80190480(float arg8)
{
    if ((int) arg8 == 0) {
        HSD_CObjSetFov(lbl_803D9DD0.cobj, lbl_803D9DD0.xD0);
        return;
    }
    HSD_CObjSetFov(lbl_803D9DD0.cobj, arg8);
}

void fn_801904D0(void)
{
    struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
    HSD_CObjSetInterest(tmp->cobj, &lbl_803D9DD0.interest);
    HSD_CObjSetEyePosition(tmp->cobj, &lbl_803D9DD0.eye_position);
}

void fn_80190520(f32 x, f32 y, f32 z)
{
    Vec3 sp14;

    if (((s32) x == 0) && ((s32) y == 0) && ((s32) z == 0)) {
        struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
        HSD_CObjSetInterest(tmp->cobj, &lbl_803D9DD0.interest);
        HSD_CObjSetEyePosition(tmp->cobj, &lbl_803D9DD0.eye_position);
        return;
    } else {
        struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
        sp14.x = x;
        sp14.y = y;
        sp14.z = z;
        HSD_CObjSetInterest(tmp->cobj, &sp14);
        sp14.z = 415.6922f + z;
        HSD_CObjSetEyePosition(tmp->cobj, &sp14);
    }
}

/// #fn_80190520

static inline int gm_801905F0_inline0(int c_kind)
{
    if (c_kind < CKIND_SEAK) {
        return c_kind;
    }
    if (c_kind == CKIND_GKOOPS) {
        return CKIND_KOOPA;
    }
    return c_kind + 1;
}

void gm_801905F0(StartMeleeData* arg0)
{
    GameRules* temp_r31 = gmMainLib_8015CC34();
    int i;
    TmVsData sp18;

    gm_80168FC4();
    gm_80167A64(&arg0->rules);
    arg0->rules.is_teams = false;
    arg0->rules.xE = gm_804771C4.x28;
    fn_801640B0(&arg0->rules.x20);
    arg0->rules.x0_0 = temp_r31->mode;
    if (temp_r31->mode != 1) {
        arg0->rules.x0_6 = true;
    } else if (temp_r31->stock_time_limit != 0) {
        arg0->rules.x0_6 = true;
    } else {
        arg0->rules.x0_6 = false;
    }
    if (arg0->rules.x0_6) {
        if (temp_r31->mode != 1) {
            if (temp_r31->time_limit == 0) {
                arg0->rules.x10 = 99 * 60;
            } else {
                arg0->rules.x10 = temp_r31->time_limit * 60;
            }
        } else {
            if (temp_r31->stock_time_limit == 0) {
                arg0->rules.x10 = 99 * 60;
            } else {
                arg0->rules.x10 = temp_r31->stock_time_limit * 60;
            }
        }
    }
    if (arg0->rules.x0_0 == 1) {
        arg0->rules.x2_0 = true;
    }
    arg0->rules.x0_7 = false;
    arg0->rules.x4_2 = false;
    arg0->rules.x4_4 = false;
    arg0->rules.xB = gmMainLib_8015CC58()->item_freq;
    arg0->rules.x2_2 = false;
    arg0->rules.x18 = 0;
    arg0->rules.x34 = 1.0f;
    arg0->rules.x30 = fn_801653E8(temp_r31->damage_ratio);
    arg0->rules.x3_4 = false;
    arg0->rules.x3_5 = false;
    arg0->rules.x3_2 = false;
    arg0->rules.x3_3 = false;
    switch (gmMainLib_8015ED30()) {
    case 1:
        arg0->rules.xC = 0;
        break;
    case 0:
        arg0->rules.xC = -1;
        break;
    case 2:
        arg0->rules.xC = -2;
        break;
    }
    if (temp_r31->pause != 0) {
        arg0->rules.x2_4 = false;
    } else {
        arg0->rules.x2_4 = true;
    }
    if (temp_r31->score_display != 0 && !arg0->rules.x0_3) {
        arg0->rules.x3_0 = true;
    } else {
        arg0->rules.x3_0 = false;
    }
    gm_80167A14(arg0->players);

    for (i = 0; i < 4; i++) {
        if (i < gm_804771C4.x30) {
            arg0->players[i].x20 = 1.0f;
            arg0->players[i].xA = (u8) MIN(gm_804771C4.x4B8[i].x6, 0x78);
            if (gm_804771C4.x4B8[i].x2 != 0) {
                arg0->players[i].c_kind = gm_801905F0_inline0(fn_8018F410());
                arg0->players[i].color =
                    HSD_Randi(gm_80169238(arg0->players[i].c_kind));
            } else {
                arg0->players[i].c_kind =
                    gm_801905F0_inline0(gm_804771C4.x4B8[i].x1);
                arg0->players[i].color = gm_804771C4.x4B8[i].x3;
            }
            arg0->players[i].slot_type = gm_804771C4.x4B8[i].x0;
            arg0->players[i].stocks = temp_r31->stock_count;
            arg0->players[i].sub_color = 0;
            arg0->players[i].team = 0xFF;
            arg0->players[i].xC_b0 = gm_801677F8(i, arg0->players[i].xA);
            if (gm_804771C4.x4B8[i].x0 == 1) {
                arg0->players[i].xC_b0 = false;
            }
            arg0->players[i].xE = 4;
            arg0->players[i].cpu_level = gm_804771C4.x4B8[i].x4;
            arg0->players[i].x12 = 0;
            if (gmMainLib_8015CC34()->handicap != 0) {
                arg0->players[i].x18 = fn_8016419C(gm_804771C4.x4B8[i].x5);
                arg0->players[i].x1C = fn_801641B4(gm_804771C4.x4B8[i].x5);
            } else {
                arg0->players[i].x18 = arg0->players[i].x1C = 1.0F;
            }
        } else {
            arg0->players[i].slot_type = Gm_PKind_NA;
        }
    }

    sp18.stage_id = arg0->rules.xE;
    for (i = 0; i < 4; i++) {
        sp18.slot_type[i] = arg0->players[i].slot_type;
        sp18.char_id[i] = arg0->players[i].c_kind;
        sp18.color[i] = arg0->players[i].color;
    }

    fn_8019EF08(&sp18);
}

/// #fn_80190ABC

#pragma push
#pragma dont_inline on
void gm_80190EA4(void)
{
    int i;
    TmData* tmdata = gm_8018F634();

    fn_80190174(lbl_804D664C->cameras->desc);
    fn_801902F0(0);
    fn_80193308();
    fn_8019027C(lbl_804D664C->lights);
    fn_80193230();
    tmdata->cur_option = 0;

    while (tmdata->cur_option < 7) {
        fn_80190ABC(0);
        fn_80190ABC(2);
        fn_80190ABC(3);
        fn_80190ABC(1);
        tmdata->cur_option += 1;
    }
    if (gm_804771C4.match_type == 0) {
        TmData* tmdata = gm_8018F634();
        fn_8018EC7C();
        fn_8018E618(tmdata->entrants, 1, 4.5f);
        fn_80190480(130.0f);
        fn_80190520(-278.0f, 255.0f, 0.0f);
    }
    tmdata->x20 = 0;

    for (i = 0; i < 64; i++) {
        if (gmMainLib_8015CC34()->handicap == 1) {
            tmdata->x37[i].x1 = 5;
        } else {
            tmdata->x37[i].x1 = 9;
        }
    }
}
#pragma pop

static struct {
    u8 pad[0xC];
    u16 xC_counter;
    u8 xE;
    u8 xF;
    u8 pad2[0x10];
} lbl_804799B8;

/// Initializes the time menu state when entering the time selection screen.
/// #gm_80190FE4

void fn_801910E0(HSD_GObj* gobj)
{
    u16* counter = &lbl_804799B8.xC_counter;
    HSD_JObj* jobj = gobj->hsd_obj;

    if (*counter > 0x320U) {
        *counter = 0;
    }
    fn_8019044C(jobj, (f32) *counter);
    *counter = *counter + 1;
}

/// @TODO: Currently 83.05% match - compiler generates different register usage
void fn_80191154(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;
    u8* xE_ptr;

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tm->cur_option < 9) {
        xE_ptr = &lbl_804799B8.xE;
        if (*xE_ptr > 0x27U) {
            *xE_ptr = 0xA;
        }
    } else {
        xE_ptr = &lbl_804799B8.xE;
        if (lbl_804799B8.xE == 0x31) {
            fn_80190ABC(6);
            fn_80190ABC(5);
            tm->cur_option = 0xA;
        }
        if (*xE_ptr > 0x4EU) {
            *xE_ptr = 0x32;
        }
    }
    xE_ptr = &lbl_804799B8.xE;
    fn_8019044C(jobj, (float) lbl_804799B8.xE);
    (*xE_ptr)++;
}

/// @TODO: Currently 78.85% match - needs register allocation fix
void fn_80191240(HSD_GObj* gobj)
{
    TmData* tm;
    s32 val;
    HSD_JObj* jobj;
    HSD_JObj* child;

    tm = gm_8018F634();
    val = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;
    if (tm->cur_option >= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, 0x10);
    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    if (child == NULL) {
        child = NULL;
    } else {
        child = child->next;
    }
    if (val == tm->cur_option) {
        if (lbl_804799B8.pad[7] != 0) {
            fn_8019044C(jobj, 1.0F);
            lbl_804799B8.pad[7] = lbl_804799B8.pad[7] - 1;
        } else {
            fn_8019044C(jobj, 0.0F);
        }
        if (lbl_804799B8.pad[8] != 0) {
            fn_8019044C(child, 1.0F);
            lbl_804799B8.pad[8] = lbl_804799B8.pad[8] - 1;
            return;
        }
        fn_8019044C(child, 0.0F);
        return;
    }
    if (val > tm->cur_option) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    if (val == 5 && gm_804771C4.match_type != 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }
    fn_8019044C(jobj, 0.0F);
}

/// #fn_801913BC

/// Updates the visibility and animation state of a Tournament Mode menu
/// option.
void fn_80191678(HSD_GObj* gobj)
{
    TmData* tmdata;
    s32 idx;
    HSD_JObj* jobj;
    u8* ptr;

    tmdata = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (tmdata->cur_option >= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (idx == tmdata->cur_option) {
        ptr = &lbl_804799B8.pad[idx];
        if (*(ptr += 0x16) > 0x64) {
            *ptr = 0;
        }
        fn_8019044C(jobj, (f32) *ptr);
        *ptr = *ptr + 1;
        return;
    }

    HSD_JObjSetFlagsAll(jobj, 0x10);
}

/// @TODO: Currently 89.68% match - permuter couldn't improve
/// Updates menu option selection animation.
void fn_8019175C(void* gobj)
{
    HSD_JObj* first_child;
    HSD_JObj* option_jobj_a;
    HSD_JObj* option_jobj_b;
    u8* counter;
    s32 i;
    TmData* tm;
    HSD_JObj* jobj;
    HSD_JObj* root_jobj;
    HSD_JObj* child;
    HSD_JObj** base;

    tm = gm_8018F634();
    fn_8018F62C(gobj);
    root_jobj = *(HSD_JObj**) ((u8*) gobj + 0x28);
    jobj = root_jobj;

    if (tm->cur_option >= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (root_jobj == NULL) {
        first_child = NULL;
    } else {
        first_child = root_jobj->child;
    }

    if (first_child == NULL) {
        child = NULL;
    } else {
        child = first_child->next;
    }

    if (child == NULL) {
        child = NULL;
    } else {
        child = child->next;
    }

    if (child == NULL) {
        option_jobj_a = NULL;
    } else {
        option_jobj_a = child->next;
    }

    if (option_jobj_a == NULL) {
        option_jobj_b = NULL;
    } else {
        option_jobj_b = option_jobj_a->next;
    }

    if (tm->cur_option >= 6) {
        counter = &lbl_804799B8.xF;
        if (*counter >= 0x14U) {
            *counter = 0;
        }
        i = 0;
        base = &option_jobj_a;
        do {
            if (i != tm->cur_option - 6) {
                fn_8019044C(base[i], 0.0F);
            } else {
                fn_8019044C(base[i], (f32) *counter);
            }
            i += 1;
        } while (i <= 2);
        *counter = *counter + 1;
        return;
    }

    HSD_JObjSetFlagsAll(jobj, 0x10);
}

/// Updates visibility and animation frame of a Training Mode HUD element.
void fn_801918F0(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;
    u8* counter;

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    switch (tm->cur_option) {
    case 0xB:
        counter = &lbl_804799B8.pad2[0xC];
        if (*counter > 5) {
            *counter = 0;
        }
        fn_8019044C(jobj, (float) *counter);
        if (*counter < 5) {
            *counter = *counter + 1;
        }
        break;
    case 0xD:
    case 0xE:
        counter = &lbl_804799B8.pad2[0xC];
        if (*counter < 10) {
            *counter = 10;
        }
        fn_8019044C(jobj, (float) *counter);
        if (*counter < 15) {
            *counter = *counter + 1;
        }
        break;
    case 0xF:
        fn_8019044C(jobj, 16.0F);
        break;
    default:
        fn_8019044C(jobj, 0.0F);
        break;
    }
}

/// Updates the tournament bracket display visibility and animation.
void fn_80191A54(HSD_GObj* gobj)
{
    TmData* td;
    HSD_JObj* jobj;
    HSD_JObj* jobj_copy;
    HSD_JObj* child;
    int cur_option;

    td = gm_8018F634();
    jobj = gobj->hsd_obj;
    jobj_copy = jobj;

    if (td->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj_copy, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj_copy, 0x10);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    cur_option = td->cur_option;
    if (cur_option == 0xA || cur_option == 0xC || cur_option == 0x10) {
        fn_8019044C(child, (f32) lbl_804799B8.pad[2]);
        HSD_MObjReqAnim(child->u.dobj->mobj, (f32) lbl_804799B8.pad[0xa]);
    } else {
        HSD_MObjReqAnim(child->u.dobj->mobj, 6.0F);
    }
    HSD_MObjAnim(child->u.dobj->mobj);
}

static u8 lbl_804799B8_data[0x40];

/// Updates button highlight animation based on current menu option.
void fn_80191B5C(void* gobj)
{
    u8* timers;
    TmData* tm;
    HSD_JObj* jobj;

    timers = lbl_804799B8_data;
    tm = gm_8018F634();
    jobj = *(HSD_JObj**) ((u8*) gobj + 0x28);

    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjClearFlagsAll(jobj, 0x10);
        switch (tm->cur_option) {
        case 10:
            fn_8019044C(jobj, (f32) timers[0xA]);
            break;
        case 11:
            fn_8019044C(jobj, 5.0F);
            break;
        case 12:
            fn_8019044C(jobj, (f32) (s32) (timers[0xA] + 0x14));
            break;
        case 13:
        case 14:
        case 15:
            fn_8019044C(jobj, 25.0F);
            break;
        case 16:
            fn_8019044C(jobj, (f32) (s32) (timers[0xA] + 0x28));
            break;
        }
    }
}

static s32 lbl_804D6658;

/// Updates JObj visibility based on current menu option selection.
void fn_80191CA4(HSD_GObj* gobj)
{
    TmData* tm;
    HSD_JObj* jobj;

    tm = gm_8018F634();
    jobj = gobj->hsd_obj;
    if (tm->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    if (lbl_804D6658 < 10) {
        lbl_804D6658 += 1;
    }
    HSD_JObjClearFlagsAll(jobj, 0x10);
    fn_8019044C(jobj, (f32) lbl_804D6658);
}

/// GObj callback for tournament bracket slot UI elements.
/// #fn_80191D38

/// Updates visibility and position of a tournament bracket player entry JObj.
/// #fn_80191E9C

/// #fn_80191FD4

/// Updates tournament menu cursor JObj visibility and position.
/// #fn_8019237C

/// @TODO: Currently 92.46% match - permuter couldn't improve
void fn_8019249C(HSD_GObj* gobj)
{
    TmData* tmdata;
    HSD_JObj* jobj;
    HSD_JObj* child;
    int cur_option;

    tmdata = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tmdata->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    cur_option = tmdata->cur_option;
    if (cur_option != 0xD && cur_option != 0xE) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    child = HSD_JObjGetChild(jobj);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);
    child = HSD_JObjGetNext(child);

    if (cur_option == 0xD) {
        fn_8019044C(child, 0.0F);
        fn_8019044C(child, (f32) (lbl_804799B8.pad[0xA] + 10));
    } else {
        fn_8019044C(child, (f32) (lbl_804799B8.pad[0xA] + 10));
        fn_8019044C(child, 0.0F);
    }
}

#pragma push
#pragma dont_inline on
void fn_80192690(HSD_GObj* gobj)
{
    TmData* tmdata = gm_8018F634();
    HSD_JObj* jobj = gobj->hsd_obj;

    if (tmdata->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    if (tmdata->cur_option < 0x11 || tmdata->cur_option > 0x12) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    fn_8018FDC4(jobj, 666.0F, 666.0F, 0.3F);
    fn_8019044C(jobj, tmdata->cur_option - 0x11);
}
#pragma pop

/// @TODO: Currently 96.8% match - permuter couldn't improve
void fn_80192758(HSD_GObj* gobj)
{
    TmData* tmdata;
    HSD_JObj* jobj;
    u8* data;
    u8* data2;
    u8* data3;
    HSD_JObj* child;
    u8 val;

    data = (u8*) &lbl_804799B8;
    tmdata = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (tmdata->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if (data[0] == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    data2 = data + 2;
    data3 = data + 3;
    fn_8019044C(jobj, (float) tmdata->x37[data2[0] + data3[0]].x2);

    if (data[1] != 0) {
        child = (jobj == NULL) ? NULL : jobj->child;
        HSD_JObjClearFlags(child, JOBJ_HIDDEN);

        child = (jobj == NULL) ? NULL : jobj->child;
        child = (child == NULL) ? NULL : child->next;
        HSD_JObjClearFlags(child, JOBJ_HIDDEN);

        val = tmdata->x37[data2[0] + data3[0]].x2;
        if (val == 9) {
            child = (jobj == NULL) ? NULL : jobj->child;
            HSD_JObjSetFlags(child, JOBJ_HIDDEN);
            return;
        }
        if (val == 1) {
            child = (jobj == NULL) ? NULL : jobj->child;
            child = (child == NULL) ? NULL : child->next;
            HSD_JObjSetFlags(child, JOBJ_HIDDEN);
            return;
        }
    } else {
        child = (jobj == NULL) ? NULL : jobj->child;
        HSD_JObjSetFlags(child, JOBJ_HIDDEN);

        child = (jobj == NULL) ? NULL : jobj->child;
        child = (child == NULL) ? NULL : child->next;
        HSD_JObjSetFlags(child, JOBJ_HIDDEN);
    }
}

/// #fn_80192938

/// #fn_80192BB0

/// #fn_80192E6C

#pragma push
#pragma dont_inline on
void fn_80193230(void)
{
    HSD_GObj* gobj;
    HSD_Fog* fog;
    PAD_STACK(4);

    fn_8019035C(0, lbl_804D664C->models[5], 0, 0x1A, 2, 1, fn_801910E0, 0.0F);
    fn_8019035C(0, lbl_804D664C->models[4], 0, 0x1A, 2, 1, fn_80191154, 0.0F);
    fn_80192BB0();
    fn_80192E6C();
    gobj = GObj_Create(0xE, 0x1A, 0);
    fog = HSD_FogLoadDesc(lbl_804D664C->fogs[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
}
#pragma pop

/// #fn_80193308

/// #fn_801935B8

/// #fn_801937C4

/// #fn_80193B58

/// #fn_80193FCC

/// #fn_80194658

extern u8 lbl_803D9F80[];

/// @TODO: Currently 87.58% match - permuter couldn't improve
void fn_801949B4(s32* arg0, u32 arg1, u32 arg2)
{
    u8* table;
    s32 idx;
    s32* ptr;
    s32 val;
    u8* entry;

    if (arg1 & 0x40001) {
        lbAudioAx_80024030(2);
        ((u8*) &lbl_804799B8)[7] = 5;
        table = lbl_803D9F80;

        idx = *arg0;
        ptr = arg0 + idx;
        entry = table + (idx << 1) + (gm_804771C4.match_type != 0);
        val = *++ptr;

        if (val > (s32) entry[0x40]) {
            *ptr = val - 1;
        } else {
            *ptr = (s32) entry[0x4C];
        }
    } else if (arg1 & 0x80002) {
        lbAudioAx_80024030(2);
        ((u8*) &lbl_804799B8)[8] = 5;
        table = lbl_803D9F80;

        idx = *arg0;
        ptr = arg0 + idx;
        entry = table + (idx << 1) + (gm_804771C4.match_type != 0);
        val = *++ptr;

        if (val < (s32) entry[0x4C]) {
            *ptr = val + 1;
        } else {
            *ptr = (s32) entry[0x40];
        }
    }

    if (arg1 != 0) {
        if ((arg1 | arg2) & 0x300) {
            fn_80190ABC(0);
            fn_80190ABC(2);
            fn_80190ABC(1);
        }
        fn_80190ABC(3);
    }

    if (arg2 & 0x100) {
        lbAudioAx_80024030(1);
        if (gm_804771C4.match_type == 0) {
            *arg0 = *arg0 + 1;
        } else {
            *arg0 = 6;
        }
    } else if (arg2 & 0x200) {
        lbAudioAx_80024030(0);
        *arg0 = *arg0 - 1;
    }

    if (arg2 != 0) {
        if ((arg1 | arg2) & 0x300) {
            fn_80190ABC(0);
            fn_80190ABC(2);
            fn_80190ABC(1);
        }
        fn_80190ABC(3);
    }
}

/// @TODO: Currently 84.75% match - needs register allocation fix
void fn_80194BC4(s32* arg0, u32 arg1, u32 arg2)
{
    int* match_type_ptr;
    s16* data_ptr;
    s32 option;
    s32 value;
    s32* arr_ptr;
    s16* opt_ptr;
    u8* lookup_ptr;
    int match_type;
    s32 opt_x4, opt_x2;

    data_ptr = (s16*) lbl_803D9F80;
    match_type_ptr = &gm_804771C4.match_type;

    if (*match_type_ptr != 0) {
        return;
    }

    if (arg1 & 0x40001) {
        lbAudioAx_80024030(2);
        ((u8*) &lbl_804799B8)[7] = 5;
        match_type = *match_type_ptr;
        option = *arg0;
        opt_x4 = option << 2;
        opt_x2 = option << 1;
        arr_ptr = (s32*) ((u8*) arg0 + opt_x4);
        opt_ptr = (s16*) ((u8*) data_ptr + opt_x2);
        value = *(++arr_ptr);
        lookup_ptr = (u8*) opt_ptr + !!match_type;
        if (value > lookup_ptr[0x40]) {
            *arr_ptr = value - 1;
        } else {
            *arr_ptr = lookup_ptr[0x4C];
        }
    } else if (arg1 & 0x80002) {
        lbAudioAx_80024030(2);
        ((u8*) &lbl_804799B8)[8] = 5;
        match_type = *match_type_ptr;
        option = *arg0;
        opt_x4 = option << 2;
        opt_x2 = option << 1;
        arr_ptr = (s32*) ((u8*) arg0 + opt_x4);
        opt_ptr = (s16*) ((u8*) data_ptr + opt_x2);
        value = *(++arr_ptr);
        lookup_ptr = (u8*) opt_ptr + !!match_type;
        if (value < lookup_ptr[0x4C]) {
            *arr_ptr = value + 1;
        } else {
            *arr_ptr = lookup_ptr[0x40];
        }
    }

    if (arg1 != 0) {
        if ((arg1 | arg2) & 0x300) {
            fn_80190ABC(0);
        }
        fn_80190ABC(3);
    }

    if (arg2 & 0x100) {
        lbAudioAx_80024030(1);
        *arg0 = *arg0 + 1;
    } else if (arg2 & 0x200) {
        lbAudioAx_80024030(0);
        *arg0 = *arg0 - 1;
    }

    if (arg2 != 0) {
        if ((arg1 | arg2) & 0x300) {
            fn_80190ABC(0);
        }
        fn_80190ABC(3);
    }
}

/// @TODO: Currently 97.2% match - permuter couldn't improve
/// Handles button input for tournament mode menu navigation.
void fn_80194D84(s32* state, u32 buttons, u32 trigger)
{
    s32 cur_state;
    TmData* tm;

    if (buttons & 0x40001) {
        if (*state > 6) {
            lbAudioAx_80024030(2);
            *state -= 1;
        }
    } else if ((buttons & 0x80002) && (*state < 8)) {
        lbAudioAx_80024030(2);
        *state += 1;
    }

    if ((buttons != 0) && ((buttons | trigger) & 0x300)) {
        fn_80190ABC(0);
    }

    if (trigger & 0x1100) {
        lbAudioAx_80024030(1);
        fn_8018EC7C();
        cur_state = *state;
        if (cur_state == 6) {
            fn_80192938();
        } else if (cur_state == 7) {
            tm = gm_8018F634();
            tm->x20 = 1;
            HSD_SisLib_803A5E70();
            mn_8022F138(0x19, 0x1C);
            mn_8022F138(0x12, 0x15);
            if (gm_804771C4.match_type == 0) {
                mn_802317E4(lbl_804D6648, 0);
            } else {
                mn_802317E4(lbl_804D6648, 1);
            }
            return;
        } else {
            *state = 0;
        }
    } else if (trigger & 0x200) {
        lbAudioAx_80024030(0);
        if (gm_804771C4.match_type == 0) {
            *state = 5;
        } else {
            *state = 4;
        }
    }

    if ((trigger != 0) && ((buttons | trigger) & 0x300)) {
        fn_80190ABC(0);
    }
}

/// #fn_80194F30

/// #fn_801953C8

static s32 lbl_804D6654;

/// @TODO: Currently 93.5% match - permuter couldn't improve
/// Handles name entry/selection input for tournament mode.
void fn_80195AF0(s32* state_ptr, u32 buttons, u32 trigger)
{
    u8* ptr;
    u8* page_ptr;
    u8* row_ptr;
    u8* col_ptr;
    s32 cur_state;

    ptr = (u8*) &lbl_804799B8;

    if (trigger & 0x1000) {
        lbl_804D6654 = *state_ptr;
        *state_ptr = 0x11;
        return;
    }

    if (buttons & 0x40001) {
        if (*state_ptr == 0xE) {
            lbAudioAx_80024030(2);
            *state_ptr = 0xD;
        }
    } else if ((buttons & 0x80002) && (*state_ptr == 0xD)) {
        lbAudioAx_80024030(2);
        *state_ptr = 0xE;
    }

    if (trigger & 0x100) {
        u16* arr;

        lbAudioAx_80024030(1);
        col_ptr = &ptr[2];
        row_ptr = &ptr[3];
        arr = (u16*) ((u8*) state_ptr + (ptr[2] + ptr[3]) * 0x12);
        arr[0x21] = arr[0x20];
        cur_state = *state_ptr;
        switch (cur_state) {
        case 0xD:
            if (IsNameListFull() == 0) {
                TmData* tm = gm_8018F634();
                tm->x20 = 1;
                HSD_SisLib_803A5E70();
                mn_8022F138(0x19, 0x1C);
                mn_8022F138(0x12, 0x15);
                mnNameNew_8023EA08((UNK_T) lbl_804D6648);
            }
            return;
        case 0xE:
            page_ptr = &ptr[6];
            if (GetNameText(ptr[5] + (ptr[6] * 4)) != NULL) {
                s32 idx = (*col_ptr + *row_ptr) * 0x12;
                s16 val = ptr[5] + (*page_ptr * 4);
                ((u16*) ((u8*) state_ptr + idx))[0x20] = val;
            }
            *state_ptr = 0xF;
            fn_80190ABC(4);
            return;
        }
        return;
    }

    if (trigger & 0x200) {
        u16* arr;

        lbAudioAx_80024030(0);
        arr = (u16*) ((u8*) state_ptr + (ptr[2] + ptr[3]) * 0x12);
        arr[0x20] = arr[0x21];
        fn_80190ABC(5);
        fn_80190ABC(6);
        *state_ptr = 0xC;
    }
}

/// #fn_80195CCC

/// @TODO: Currently 96.88% match - needs minor register allocation fix
/// Handles confirm/cancel input for tournament start.
/// Type casts used to match target sth instruction patterns.
void fn_8019610C(s32* state, u32 buttons, u32 trigger)
{
    TmData* td;
    s32 i;
    u8* src_ptr;
    u8* dst_ptr;
    s32 base_val;

    i = 1;

    if (buttons & 0x10008) {
        if (*state == 0x12) {
            lbAudioAx_80024030(2);
            *state = 0x11;
        }
    } else if ((buttons & 0x20004) != 0) {
        if (*state == 0x11) {
            lbAudioAx_80024030(2);
            *state = 0x12;
        }
    }

    if ((trigger & 0x1100) != 0) {
        if (*state == 0x11) {
            lbAudioAx_80024030(i);
            if (gm_804771C4.match_type == 0) {
                gm_SetScenePendingMinor(1);
            } else {
                td = gm_8018F634();
                i = 0;
                src_ptr = (u8*) td;
                dst_ptr = (u8*) td;
                base_val = i;
                while (i < td->x2E) {
                    src_ptr[0x45] = src_ptr[0x44];
                    src_ptr[0x46] = base_val;
                    if (i < td->x30) {
                        *(u16*) &dst_ptr[0x4BE] = *(u16*) &src_ptr[0x40];
                        dst_ptr[0x4BD] = src_ptr[0x39];
                        dst_ptr[0x4B9] = src_ptr[0x3A];
                        dst_ptr[0x4B8] = src_ptr[0x37];
                        dst_ptr[0x4BB] = src_ptr[0x3E];
                        dst_ptr[0x4BA] = src_ptr[0x3C];
                    }
                    src_ptr += 0x12;
                    dst_ptr += 0xA;
                    i++;
                }
                gm_SetScenePendingMinor(2);
            }
            gm_801A4B60();
        } else {
            lbAudioAx_80024030(0);
            *state = lbl_804D6654;
        }
    } else if ((trigger & 0x200) != 0) {
        lbAudioAx_80024030(0);
        *state = lbl_804D6654;
    }
}

/// Tournament Mode per-frame update handler.
void gm_8019628C_OnFrame(void)
{
    TmData* tm;
    u32 r30;
    u32 r29;
    s32 cur_option;

    tm = gm_8018F634();
    r30 = fn_8018F674(4);
    r29 = fn_8018F640(4);

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        HSD_SisLib_803A5E70();
        mn_8022F138(1, 8);
        mn_8022F138(0x19, 0x1C);
        mn_8022F138(0x12, 0x15);
        mn_8022F268();
        gm_801A4B60();
        gm_801A42F8(1);
        return;
    }

    if (tm->x20 != 0) {
        return;
    }

    lbl_804799B8.pad[0xA] = (u8) ((lbl_804799B8.pad[0xA] + 1) % 11);

    cur_option = tm->cur_option;
    if (cur_option >= 9 && cur_option <= 9) {
        return;
    }
    if (cur_option >= 0x13) {
        return;
    }
    lbl_803D9FD8[cur_option]((s32*) tm, r30, r29);
}

extern struct {
    UNK_T x0;
    UNK_T x4;
    UNK_T x8;
} lbl_804771B8;

void gm_801963B4_OnEnter(void* arg0)
{
    const char* filename;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 8);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    lbl_804D6640 = lbArchive_80016DBC("GmTou1p", &lbl_804D664C,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6644 = lbArchive_80016DBC("GmTou2p", &lbl_804D6650,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6648 = lbArchive_LoadArchive("MnExtAll");
    filename = "TmBox.dat";
    lbl_804D6638 = lbArchive_80016DBC(
        filename, &lbl_804771B8.x0, "tournament_box2_array", &lbl_804771B8.x4,
        "tournament_box3_array", &lbl_804771B8.x8, "tournament_box4_array", 0);
    HSD_SisLib_803A62A0(0, fn_8018F5F0(), "SIS_TournamentData");
    fn_801935B8();
    lbAudioAx_800237A8(0x7539, 0x7F, 0x40);
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

/// Scene OnLeave callback for gm_18A5. Frees archive resources.
void gm_801964A4_OnLeave(UNK_T arg)
{
    (void) arg;
    lbArchive_80016EFC(lbl_804D6640);
    lbArchive_80016EFC(lbl_804D6644);
    lbArchive_80016EFC(lbl_804D6648);
    lbArchive_80016EFC(lbl_804D6638);
    gm_8018F634()->cur_option = 0x13;
    gm_8018F634()->x2C = 1;
    gm_8018F634()->x31 = lbl_804799B8.pad[0];
}

static s32 lbl_804D4194 = -1;

/// #fn_80196510

s32 fn_8019655C(void)
{
    return lbl_804D4190;
}

bool fn_80196564(TmData* arg0)
{
    if ((arg0->stage_selection_type == 0 && arg0->x32 == 0) ||
        arg0->stage_selection_type == 1)
    {
        return true;
    }
    return false;
}

bool fn_80196594(TmData* arg0)
{
    if ((arg0->stage_selection_type == 2 && arg0->x32 == 0) ||
        arg0->stage_selection_type == 3)
    {
        return true;
    }
    return false;
}

void fn_801965C4(void)
{
    TmData* temp_r3;
    int temp_r4;

    temp_r3 = gm_8018F634();
    temp_r3->x2D = 1;
    temp_r4 = temp_r3->stage_selection_type;

    if (fn_80196594(temp_r3)) {
        temp_r3->x32 = 1;
        gm_SetScenePendingMinor(3);
        gm_801A4B60();
        return;
    }
    if (fn_80196564(temp_r3)) {
        temp_r3->x32 = 1;
        temp_r3->x28 = lbl_804D4190;
    }
    gm_SetScenePendingMinor(4);
    gm_801A4B60();
}

/// @TODO: Currently 83.98% match - needs register allocation fix
/// Randomly assigns bracket positions for tournament seeding.
void fn_80196684(s32 bracket_idx)
{
    s32 rand_val;
    u8* weight_c;
    u8* weight_b;
    u8* weight_a;
    u8* bracket;
    u8 weight_a_val;

    weight_c = (u8*) &lbl_80473AB8[bracket_idx];
    weight_b = (u8*) &lbl_80473AB8[bracket_idx];
    weight_c = &weight_c[0xA9];
    weight_a = (u8*) &lbl_80473AB8[bracket_idx];
    weight_b = &weight_b[0x7D];
    weight_a = &weight_a[0x51];
    rand_val = HSD_Randi(*weight_a + *weight_b + *weight_c);
    weight_a_val = *weight_a;
    if (rand_val < (s32) weight_a_val) {
        bracket = (u8*) &lbl_80473AB8[bracket_idx];
        bracket[0x4C] = 0;
        if (HSD_Randi(*weight_b + *weight_c) < (s32) *weight_b) {
            bracket[0x78] = 1;
            bracket[0xA4] = 2;
            return;
        }
        bracket[0x78] = 2;
        bracket[0xA4] = 1;
        return;
    }
    if (rand_val < (s32) (weight_a_val + *weight_b)) {
        bracket = (u8*) &lbl_80473AB8[bracket_idx];
        bracket[0x78] = 0;
        if (HSD_Randi(*weight_a + *weight_c) < (s32) *weight_a) {
            bracket[0x4C] = 1;
            bracket[0xA4] = 2;
            return;
        }
        bracket[0x4C] = 2;
        bracket[0xA4] = 1;
        return;
    }
    bracket = (u8*) &lbl_80473AB8[bracket_idx];
    bracket[0xA4] = 0;
    if (HSD_Randi(*weight_a + *weight_b) < (s32) *weight_a) {
        bracket[0x4C] = 1;
        bracket[0x78] = 2;
        return;
    }
    bracket[0x4C] = 2;
    bracket[0x78] = 1;
}

/// #fn_801967E0

extern u8 lbl_803DA0D0[];

/// @TODO: Currently 95.92% match - needs minor register allocation fix
s32 fn_80196CF8(void)
{
    TmData* tmdata;
    s32 offset;
    u8* ptr;
    s32 x24;
    s32 result;

    tmdata = gm_8018F634();
    offset = tmdata->entrants * 6;
    ptr = lbl_803DA0D0;
    x24 = tmdata->x24;
    ptr += offset;

    result = 0;
    if (x24 > (s32) ptr[0x23]) {
        return 6;
    }

    ptr += 5;

    if (x24 <= (s32) ptr[0x1E]) {
        result = 5;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 4;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 3;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 2;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 1;
    }

    if (x24 <= (s32) (--ptr)[0x1E]) {
        result = 0;
    }

    return result;
}

static union {
    u8 x0[0x80];
    struct {
        u8 _pad1[0x10];
        u16 x10;
        u8 _pad2[0x8];
        u8 x1A;
        u8 x1B;
        u8 x1C;
    };
} lbl_804799D8;

/// Cycles animation frame counter and updates JObj animation.
void fn_80196DBC(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u16* counter = &lbl_804799D8.x10;

    jobj = gobj->hsd_obj;
    if (*counter > 0x320U) {
        *counter = 0;
    }
    fn_8019044C(jobj, (f32) *counter);
    *counter = *counter + 1;
}

/// Updates the tournament UI animation frame counter.
void fn_80196E30(HSD_GObj* gobj)
{
    u8* base_ptr;
    s32 cur_option;
    HSD_JObj* jobj;
    u8* x1A_ptr;
    u8 val;

    base_ptr = lbl_804799D8.x0;
    cur_option = gm_8018F634()->cur_option;
    jobj = gobj->hsd_obj;

    if (cur_option <= 0x1A || cur_option >= 0x1F) {
        if ((u8) * (x1A_ptr = base_ptr + 0x1A) > 0x77U) {
            *x1A_ptr = 0x5A;
        }
    } else if (cur_option <= 0x1E) {
        if ((u8) * (x1A_ptr = base_ptr + 0x1A) > 0x9FU) {
            *x1A_ptr = 0x82;
        }
    }

    val = *(base_ptr += 0x1A);
    fn_8019044C(jobj, (f32) val);
    *base_ptr = *base_ptr + 1;
}

/// Tournament mode JObj visibility/animation callback.
void fn_80196EEC(HSD_GObj* gobj)
{
    TmData* tmdata;
    HSD_JObj* jobj;
    u8* counter;
    int in_range;

    tmdata = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x13 && gm_8018F634()->cur_option <= 0x1A)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    counter = &lbl_804799D8.x1B;

    if (*counter != 0) {
        *counter = *counter - 1;
        HSD_JObjAnimAll(jobj);
        if (tmdata->x33 == tmdata->pad_x34[0]) {
            if (*counter > 2) {
                *counter = 2;
            }
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        if (tmdata->cur_option == 0x14) {
            tmdata->cur_option = 0x15;
        }
    }
}

/// #fn_80196FFC

/// Updates visibility and position of a tournament menu JObj.
/// #fn_801973F8

/// Updates visibility of a tournament menu JObj based on current menu state.
void fn_801975C8(HSD_GObj* gobj)
{
    TmData* tmdata;
    u32 idx;
    HSD_JObj* jobj;
    s32 in_range;

    tmdata = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if (HSD_PadMasterStatus[(u8) idx].err != 0 && tmdata->x4B8[idx].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    if (lbl_804799D8.x0[0x2D + idx * 6] == 4) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

/// Updates visibility and animation of tournament menu JObj.
void fn_801976D4(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u8* counter;
    s32 is_in_range;
    PAD_STACK(8);

    gm_8018F634();
    jobj = gobj->hsd_obj;
    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        is_in_range = 1;
    } else {
        is_in_range = 0;
    }
    if (is_in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjClearFlagsAll(jobj, 0x10);
        counter = &lbl_804799D8.x1C;
        if (*counter > 0x3C) {
            *counter = 0x3C;
        }
        fn_8019044C(jobj, (f32) *counter);
        *counter = *counter + 1;
    }
}

/// #fn_801977AC

/// #fn_80197AF0

/// Updates visibility of a menu JObj based on current menu option.
void fn_80197D4C(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u8* counter;
    int cond;
    PAD_STACK(8);

    gm_8018F634();
    jobj = gobj->hsd_obj;
    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    counter = &lbl_804799D8.x0[0x29];
    fn_8019044C(jobj, (float) lbl_804799D8.x0[0x29]);
    if (*counter < 10U) {
        *counter = *counter + 1;
    }
}

/// @TODO: Currently 69.71% match - needs register allocation fix
/// Updates player HUD element visibility and position.
void fn_80197E18(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    TmData* data;
    s32 pnum;
    s32 in_range;
    f32 x_pos;

    data = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (HSD_PadMasterStatus[(u8) pnum].err != 0 && data->x4B8[pnum].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    if (data->x4B8[pnum].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }

    if ((s32) data->x30 == 4) {
        x_pos = (13.0F * pnum) + (-19.5F);
    } else if ((s32) data->x30 == 3) {
        x_pos = 6.5F + ((13.0F * pnum) - 19.5F);
    } else {
        x_pos = 6.5F + ((13.0F * (2.0F * pnum)) - 19.5F);
    }
    fn_8018FDC4(jobj, x_pos, 666.0F, 666.0F);
}

/// @TODO: Currently 70.24% match - needs register allocation fix
/// Updates JObj visibility based on menu option and player state.
void fn_80197FD8(HSD_GObj* gobj)
{
    TmData* tm_data;
    s32 port;
    HSD_JObj* jobj;
    s32 option_in_range;
    u8 port_u8;

    tm_data = gm_8018F634();
    port = fn_8018F62C(gobj);
    jobj = *(HSD_JObj**) ((u8*) gobj + 0x28);

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        option_in_range = 1;
    } else {
        option_in_range = 0;
    }

    if (option_in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    port_u8 = (u8) port;
    if ((s8) HSD_PadMasterStatus[port_u8].err != 0) {
        if (tm_data->x4B8[port].x0 != 1) {
            HSD_JObjSetFlagsAll(jobj, 0x10);
            return;
        }
    } else {
        if (lbl_804799D8.x0[port * 6 + 0x2D] == 4) {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
    }

    {
        f32 x_position;
        u8 num_players = tm_data->x30;

        if ((s32) num_players == 4) {
            x_position = (13.0F * (f32) port) + -19.5F;
        } else if ((s32) num_players == 3) {
            x_position = 6.5F + ((13.0F * (f32) port) - 19.5F);
        } else {
            x_position = 6.5F + ((13.0F * (2.0F * (f32) port)) - 19.5F);
        }

        fn_8018FDC4(jobj, x_position, 666.0F, 666.0F);
    }
}

/// @TODO: Currently 55.88% match - needs significant rework
/// Updates player cursor animation and position.
void fn_801981A0(HSD_GObj* gobj)
{
    TmData* data;
    u8* player_ptr;
    s32 pnum;
    HSD_JObj* jobj;
    u8* state_ptr;
    f32 x_pos;
    s32 in_range;
    u8 counter;

    data = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, 0x10);

    if (HSD_PadMasterStatus[(u8) pnum].err != 0 &&
        ((u8*) &lbl_804799D8)[pnum * 6 + 0x2D] != 4)
    {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }

    state_ptr = &((u8*) &lbl_804799D8)[pnum + 0x44];
    if (*state_ptr == 6) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }

    if ((s32) data->x30 == 4) {
        x_pos = (13.0F * (f32) pnum) + (-19.5F);
    } else if ((s32) data->x30 == 3) {
        x_pos = 6.5F + ((13.0F * (f32) pnum) - 19.5F);
    } else {
        x_pos = 6.5F + ((13.0F * (2.0F * (f32) pnum)) - 19.5F);
    }

    fn_8018FDC4(jobj, x_pos, 666.0F, 0.01F);

    player_ptr = (u8*) &lbl_804799D8 + pnum;
    counter = player_ptr[0x21];
    counter = (counter + 1) % 11;
    player_ptr[0x21] = counter;

    if (*state_ptr == 7) {
        fn_8019044C(jobj, (f32) player_ptr[0x21]);
        return;
    }

    fn_8019044C(jobj, (f32) (player_ptr[0x21] + 0x14));
}

/// Updates the visibility and position of a player's controller indicator.
/// #fn_801983E4

void fn_80198584(ResultsData* results)
{
    HSD_JObj* jobj;
    int cur_option;

    cur_option = gm_8018F634()->cur_option;
    jobj = results->x28;
    if (cur_option == 0x1D) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }
}

/// #fn_801985D4

/// #fn_80198824

/// Initializes tournament mode match data.
/// Initializes tournament mode match data structures.
/// Type casts used to match target instruction patterns (stw/sth vs stb).
void fn_80198BA0(void)
{
    TmData* td;
    u8* ptr;
    u8* ptr7;
    u8* ptr8;
    s32 i;

    ptr = lbl_804799D8.x0;
    td = gm_8018F634();

    /* Clear first 4 bytes as word (stw instruction) */
    *(u32*) &ptr[0x00] = 0;
    if (td && td) {
        /* FAKE MATCH: Empty block affects register allocation */
    }
    /* Clear 2 bytes at offset 0x10 as halfword (sth instruction) */
    *(u16*) &ptr[0x10] = 0;

    if (td->x2C != 0) {
        ptr[0x1A] = 0x50;
    } else {
        ptr[0x1A] = 0x5A;
    }

    ptr[0x1C] = 0;
    ptr7 = ptr;
    ptr8 = ptr;

    for (i = 0; i < td->x30; i++) {
        ptr[0x25] = 0;
        /* Clear 2 bytes as halfword (sth instruction) */
        *(u16*) &ptr7[0x12] = 0;
        ptr7 += 2;
        ptr[0x1D] = 0;
        ptr8[0x2A] = 0;
        ptr8[0x2B] = 0;
        ptr8[0x2C] = 0x1E;
        ptr8[0x2E] = 0;
        ptr8[0x2F] = 0;
        ptr8[0x2D] = 0;
        ptr8 += 6;
        ptr[0x44] = 6;
        ptr++;
    }
}

/// @TODO: Currently 99.63% match - permuter couldn't improve (instruction
/// scheduling)
/// Initializes tournament mode text displays.
void fn_80198C60(void)
{
    TmData* td;
    HSD_Text* text;
    HSD_Text** arr;

    td = gm_8018F634();
    arr = (HSD_Text**) ((u8*) td + 0x524);
    arr[2] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    text = arr[2];
    text->font_size.x = 0.054945F;
    text->font_size.y = 0.08F;
    arr[2]->default_alignment = 1;
    arr[2]->default_kerning = 1;

    arr[3] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    arr[3]->default_alignment = 1;
    arr[3]->default_kerning = 1;
    HSD_SisLib_803A6B98(arr[3], 320.0F, 250.0F, "    ");
    HSD_SisLib_803A7548(arr[3], 0, 1.5F, 1.5F);
}

extern SceneDesc* lbl_804D666C;

/// Initializes the scene rendering components for the gm_18A5 game mode.
/// #fn_80198D18

/// #fn_80198EBC

/// #fn_80199AF0

/// #fn_8019A158

/// @TODO: Currently 98.36% match - needs branch pattern fix (beq+b vs bne)
#pragma dont_inline on
void fn_8019A71C(s32* state)
{
    u32* counter = (u32*) &lbl_804799D8;
    PAD_STACK(8);

    if (*state == 0x13) {
        fn_8019B458(state);
    }

    if (*state > 0x14) {
        *counter = *counter + 1;
    }

    if (*counter >= 0x14U) {
        *state = 0x15;
    }

    if (*counter == 0x1EU) {
        *state = 0x16;
    }

    if (*counter > 0x1EU) {
        *state = 0x17;
    }

    if (*counter >= 0x3CU) {
        *state = 0x18;
    }

    if (*counter >= 0x46U) {
        *state = 0x19;
    }

    if (*counter >= 0x5AU) {
        fn_8018EC48();
        *state = 0x1A;
        fn_8018EC7C();
        if (fn_8018F508(0) == 1) {
            *state = 0x1F;
            return;
        }
        *state = 0x1B;
    }
}
#pragma dont_inline reset

s32 lbl_804D6678;

void gm_8019A828(void)
{
    gm_8018F634()->x32 = 0;
    lbl_804D6678 = 1;
    gm_8018F634()->cur_option = 0x1B;
}

/// #fn_8019A86C

/// #fn_8019AF50

/// @TODO: Currently 89.97% match - permuter couldn't improve
/// Per-frame update for tournament mode menu.
void gm_8019B2DC_OnFrame(void)
{
    s32 sp[13];
    u32 arg1;
    TmData* data;
    u32 arg2;
    s32 cond;
    s32 val;
    s32 i;
    s32* dest;
    TmData* ptr;
    s32 stage;

    data = gm_8018F634();
    arg1 = fn_8018F674(4);
    arg2 = fn_8018F640(4);

    if (gm_8018F634()->cur_option >= 0x13 && gm_8018F634()->cur_option <= 0x1A)
    {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        fn_8019A71C((s32*) data);
    } else {
        if (gm_8018F634()->cur_option >= 0x1B &&
            gm_8018F634()->cur_option <= 0x1E)
        {
            cond = 1;
        } else {
            cond = 0;
        }
        if (cond != 0) {
            fn_8019A86C((s32*) data, arg1, arg2);
        } else {
            fn_8019AF50((s32*) data, arg1, arg2);
        }
    }

    val = data->stage_selection_type;
    if ((val == 0 && data->x32 == 0) || val == 1) {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        stage = lbl_804D4190;
    } else {
        stage = data->x28;
    }
    sp[0] = stage;

    ptr = data;
    dest = sp;
    i = 0;
    do {
        dest[1] = ptr->x4B8[0].x0;
        dest[5] = fn_8018F6FC(ptr->x4B8[0].x1);
        i += 1;
        dest[9] = ptr->x4B8[0].x3;
        ptr = (TmData*) ((u8*) ptr + 0xA);
        dest += 1;
    } while (i < 4);

    fn_8019BA04(sp);
}

/// #fn_8019B458

/// Initializes match data and transitions to next state.
/// Type cast used to match target stw instruction pattern.
void fn_8019B81C(s32* state)
{
    fn_80198BA0();
    fn_80198EBC();
    *state = 0x1C;
    *(u32*) &lbl_804799D8 = 0;
}

extern SceneDesc* lbl_804D6670;

/// @TODO: Currently 92% match - instruction scheduling issue (lfs/lbz order)
/// Sets up tournament bracket display with entrant data.
void fn_8019B860(TmData* tm)
{
    fn_8019A158();
    fn_80199AF0();
    fn_80198BA0();
    fn_8018F888();
    fn_8018E618(tm->entrants, tm->x2C, 4.5F);
    fn_8018E85C(*(int*) ((char*) lbl_804D6670->models + 0x10), tm->x2C);
    tm->cur_option = 0x20;
}
