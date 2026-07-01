#include "m2c_macros.h"
#include "math.h"
#include "math_ppc.h" // IWYU pragma: keep
#include "placeholder.h"
#include "platform.h"
#include "stddef.h"

#include "toy.static.h"

#include "trigf.h" // IWYU pragma: keep
#include "tylist.h"
#include "types.h"

#include <placeholder.h>

#include "db/db.h"
#include "gm/gm_1601.h"
#include "gm/gm_16AE.h"
#include "gm/gm_16F1.h"
#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "gm/gmmain_lib.h"
#include "if/textdraw.h"
#include "if/textlib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00CE.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbspdisplay.h"
#include "lb/lbvector.h"
#include "melee/if/textlib.h"
#include "mn/mnmain.h"
#include "mn/mnsoundtest.h"
#include "MSL/math.h"
#include "MSL/math_ppc.h"
#include "sc/types.h"
#include "ty/types.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/controller.h>
#include <baselib/debug.h>
#include <baselib/displayfunc.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/mobj.h>
#include <baselib/random.h>
#include <baselib/sislib.h>
#include <baselib/sobjlib.h>
#include <baselib/state.h>
#include <baselib/tobj.h>
#include <baselib/wobj.h>

int Toy_GetTrophyTotal(void);
s32 Toy_803048C0(int);
bool Toy_80304924(int);
void Toy_80304988(int);
bool Toy_803049F4(int);
void Toy_80304A58(int);
bool Toy_80304B0C(int);
int Toy_80304B94(int);
bool Toy_80304CC8(int);
int _Toy_80304D30(void);
s32 Toy_80305058(s32, s32, s32, f32);
void Toy_SetUnlockState(enum_t, bool);
void Toy_80305918(signed char, long, long);
s32 Toy_80305B88(void);
s32 Toy_80305C44(void);
float Toy_80305D00(void);
float Toy_80305DB0(void);
float Toy_80305EB4(void);
float Toy_80305FB8(void);
float Toy_803060BC(int, int);
s16 Toy_803062BC(s32 trophyId);
s32 Toy_803063D4(s32, s32, s32);
void Toy_803067BC(s32, s32);
void Toy_803068E0(HSD_GObj* gobj, int);
void Toy_80306930(HSD_GObj*, int);
void Toy_80306954(HSD_GObj* gobj, int);
void Toy_80306A48(HSD_JObj*, char*, char*, char*, HSD_Archive*, long);
HSD_GObjProc* Toy_80306B18(HSD_GObj* gobj, s32 anim_frame, s32 val1, s32 val2);
void Toy_80306BB8(HSD_GObj* gobj);
void Toy_RemoveUserData(void* ptr);
void Toy_80306D14(void);
void Toy_80306D70(s32 arg0);
HSD_LObj* Toy_LoadLObjList(LightList**, s32*);
void Toy_80307470(s32);
void Toy_80307E84(HSD_GObj* gobj);
char* Toy_8030813C(s16 arg0, enum_t unused);
void Toy_80308250(u8* arg0, s32 arg1, s32 arg2);
s32 Toy_803082F8(s16 idx);
void Toy_80308328(s32 arg0);
s32 Toy_80308354(s16 idx);
void Toy_803083D8(HSD_JObj* jobj, s32 arg1);
HSD_GObj* Toy_803087F4(UNK_T);
void Toy_803102D0(void);
void Toy_80310324(void);
void Toy_80310660(s32 arg0);
void Toy_80311680(void);
void Toy_80311960(void);
void Toy_OnEnter_80311AB0(UNK_T);
void Toy_OnFrame_80312018(void);
void Toy_OnInit_803122D0(void);
void Toy_8031234C(s32);
void Toy_803124BC(void);
void Toy_8031263C(void);
void Toy_803127D4(void);

int Toy_GetTrophyTotal(void)
{
    if (gm_8016B498() || gm_801A4310() == GM_TOY_LOTTERY) {
        return (short) Toy_804A284C[0x258 / 2];
    } else {
        return *gmMainLib_8015CC90();
    }
}

inline static u16* idk(void)
{
    if (gm_8016B498() || gm_801A4310() == GM_TOY_LOTTERY) {
        return &Toy_804A284C[5];
    } else {
        return gmMainLib_8015CC78();
    }
}

s32 Toy_803048C0(int arg0)
{
    return idk()[arg0] & 0xFF;
}

bool Toy_80304924(int arg0)
{
    return idk()[arg0] & 0x8000;
}

void Toy_80304988(int arg0)
{
    unsigned short* v = idk();
    v[arg0] = v[arg0] ^ 0x8000;
}

bool Toy_803049F4(int arg0)
{
    return idk()[arg0] & 0x4000;
}

void Toy_80304A58(int arg0)
{
    unsigned short* v = idk();
    if (Toy_803049F4(arg0)) {
        v[arg0] = v[arg0] ^ 0x4000;
    }
}

bool Toy_80304B0C(int arg0)
{
    unsigned short* v;
    unsigned short s;
    if (gm_8016B498() || gm_801A4310() == GM_TOY_LOTTERY) {
        s = Toy_804A284C[3] | Toy_804A284C[4];
        v = &s;
    } else {
        v = gmMainLib_8015CC84();
    }
    if (*v & (1 << arg0)) {
        return 1;
    } else {
        return 0;
    }
}

int Toy_80304B94(int option)
{
    int res;
    switch (option) {
    case 7:
        if (lbLang_IsSettingJP()) {
            res = 0x4;
        } else {
            res = 0x4;
        }
        break;
    case 6:
        if (lbLang_IsSettingJP()) {
            res = 0xA;
        } else {
            res = 0xA;
        }
        break;
    case 5:
        if (lbLang_IsSettingJP()) {
            res = 0x11;
        } else {
            res = 0x10;
        }
        break;
    case 4:
        if (lbLang_IsSettingJP()) {
            res = 0x17;
        } else {
            res = 0x17;
        }
        break;
    case 3:
        if (lbLang_IsSettingJP()) {
            res = 0xC;
        } else {
            res = 0xC;
        }
        break;
    case 2:
        if (lbLang_IsSettingJP()) {
            res = 0x48;
        } else {
            res = 0x48;
        }
        break;
    case 0:
        if (lbLang_IsSettingJP()) {
            res = 0x1B;
        } else {
            res = 0x1B;
        }
        break;
    case 1:
        if (lbLang_IsSettingJP()) {
            res = 0x7E;
        } else {
            res = 0x7E;
        }
        break;
    case 8:
        if (lbLang_IsSettingJP()) {
            res = 0x2;
        } else {
            res = 0x2;
        }
        break;
    }
    return res;
}

bool Toy_80304CC8(int arg0)
{
    short* v = _Toy_sbss_804D6EB4;
    if (lbLang_IsSettingUS()) {
        for (; *v != -1; v++) {
            if (*v == arg0) {
                return 0;
            }
        }
    }
    return 1;
}

bool _Toy_80304CC8_noinline(int arg0)
{
    return Toy_80304CC8(arg0);
}

inline static unsigned short* Toy_80304D30_idk(void)
{
    if (gm_8016B498() || gm_801A4310() == GM_TOY_LOTTERY) {
        return M2C_FIELD(&_Toy_804A26B8, unsigned short**, 0xCF);
    } else {
        return gmMainLib_8015CC78();
    }
}

inline static int Toy_80304D30_48C0(int arg0)
{
    return Toy_80304D30_idk()[arg0] & 0xFF;
}

inline static bool Toy_80304D30_4B0C(int arg0)
{
    unsigned short* v;
    unsigned short s;
    if (gm_8016B498() || gm_801A4310() == GM_TOY_LOTTERY) {
        s = M2C_FIELD(&_Toy_804A26B8, unsigned short*, 0xCD) |
            M2C_FIELD(&_Toy_804A26B8, unsigned short*, 0xCE);
        v = &s;
    } else {
        v = gmMainLib_8015CC84();
    }
    if (*v & (1 << arg0)) {
        return 1;
    } else {
        return 0;
    }
}

int _Toy_80304D30(void)
{
    int i;
    int x;
    int count;
    int count2;
    int idk;
    int* qwe;
    int sp14[36 / 4];
    PAD_STACK(4);
    if (un_80304470()) {
        return 0;
    }
    memzero(sp14, 36);
    count = 0;
    for (i = 0; i < 0x125; i++) {
        if (Toy_80304CC8(i)) {
            if (Toy_80304D30_48C0(i)) {
                x = Toy_803060BC(i, 6);
                sp14[x]++;
                if (x != 8 && x != 1) {
                    count++;
                }
            }
        }
    }

    idk = 6;
    qwe = &sp14[6];
    while (idk != 0) {
        if (idk > (unsigned int) 2 && *qwe != 0 && *qwe == Toy_80304B94(idk)) {
            for (i = 0; i < idk; i++) {
                if (1 < (unsigned int) i && i != 3) {
                    if (!Toy_80304D30_4B0C(i)) {
                        M2C_FIELD(&_Toy_804A26B8, unsigned char*, 0x194) = 2;
                        Toy_80305918(i, 0, 0);
                    }
                }
            }
            i = idk + 1;
            while (Toy_80304B94(i) == 0) {
                i++;
            }
            if (4 <= i && i <= 6) {
                if (!Toy_80304D30_4B0C(i)) {
                    M2C_FIELD(&_Toy_804A26B8, unsigned char*, 0x194) = 2;
                    Toy_80305918(i, 0, 0);
                    break;
                }
            }
            break;
        }
        idk--;
        qwe--;
    }

    count2 = 0;
    for (i = 0; i < 8; i++) {
        if (x != 8 && x != 1) {
            if (Toy_80304D30_4B0C(i)) {
                count2 += Toy_80304B94(i);
            }
        }
    }
    return count2 - count;
}

s32 Toy_80305058(s32 arg0, s32 arg1, s32 arg2, f32 farg0)
{
    s32 obtained_arr[293];
    s32 new_arr[293];
    s32 total;
    s32 byte_off;
    u16* default_flags;
    s32 trophy;
    s32 obtained_count;
    s32 new_count;
    s16* skip_list;
    u16* flags;
    s32 skip;

    PAD_STACK(20);

    default_flags = &Toy_804A284C[5];
    new_count = 0;
    obtained_count = 0;
    total = 0;
    trophy = 0;
    byte_off = 0;

    do {
        skip_list = _Toy_sbss_804D6EB4;
        if (lbLang_IsSettingUS() != 0) {
            s16 val;
            while ((val = *skip_list) != -1) {
                if (val == trophy) {
                    skip = 0;
                    goto check_skip;
                }
                skip_list++;
            }
        }
        skip = 1;

    check_skip:
        if (skip != 0) {
            if (arg0 == 0x63) {
                if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                    flags = default_flags;
                } else {
                    flags = gmMainLib_8015CC78();
                }
                if (!(M2C_FIELD(flags, u16*, byte_off) & 0x4000)) {
                    if (arg1 == 0x63) {
                        if (arg2 != 0) {
                            goto add_trophy;
                        }
                    } else if ((f32) arg1 == Toy_803060BC(trophy, 6)) {
                        if (arg2 != 0) {
                            if (gm_8016B498() != 0 ||
                                (u8) gm_801A4310() == 0xC)
                            {
                                flags = default_flags;
                            } else {
                                flags = gmMainLib_8015CC78();
                            }
                            if (M2C_FIELD(flags, u16*, byte_off) & 0x4000) {
                                goto add_obtained;
                            }
                        } else {
                            goto add_obtained;
                        }
                    }
                } else {
                    goto add_obtained;
                }
            } else if ((f32) arg0 != Toy_803060BC(trophy, 6)) {
                if (arg1 != 0x63 && (f32) arg1 == Toy_803060BC(trophy, 6)) {
                    if (arg2 != 0) {
                        if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                            flags = default_flags;
                        } else {
                            flags = gmMainLib_8015CC78();
                        }
                        if (M2C_FIELD(flags, u16*, byte_off) & 0x4000) {
                            goto add_obtained;
                        }
                    } else {
                        goto add_obtained;
                    }
                }
            } else if (arg2 != 0) {
                if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                    flags = default_flags;
                } else {
                    flags = gmMainLib_8015CC78();
                }
                if (M2C_FIELD(flags, u16*, byte_off) & 0x4000) {
                    goto add_obtained;
                }
            } else {
                if (arg2 == 0) {
                add_obtained:
                    if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                        flags = default_flags;
                    } else {
                        flags = gmMainLib_8015CC78();
                    }
                    if ((u8) * (u16*) ((u8*) flags + byte_off) != 0) {
                        obtained_arr[obtained_count++] = trophy;
                    } else {
                    add_trophy:
                        new_arr[new_count++] = trophy;
                    }
                    total++;
                }
            }
        }
        trophy++;
        byte_off += 2;
    } while (trophy < 0x125);

    if (total != 0) {
        s32 use_new;
        if (farg0 >= 100.0f || obtained_count == 0) {
            use_new = 1;
        } else {
            f32 rand = HSD_Randf();
            s32 rand_int = HSD_Randi(0x64);
            if ((f32) rand_int + rand < farg0) {
                use_new = 1;
            } else {
                use_new = 0;
            }
        }
        if (use_new != 0 && new_count != 0) {
            s32 idx = HSD_Randi(new_count);
            if (idx > new_count) {
                idx = 0;
            }
            return new_arr[idx];
        }
        {
            s32 idx = HSD_Randi(obtained_count);
            if (idx > obtained_count) {
                idx = 0;
            }
            return obtained_arr[idx];
        }
    }
    return -1;
}

void _Toy_803053C4(s32 targetValue, s32 count, s32 flag)
{
    s16* list;
    u16* ptr;
    s32 i;
    u16* default_flags;
    s32 trophyId;
    s32 found;

    if (flag != 0) {
        default_flags = &Toy_804A284C[5];
        while (count != 0) {
            trophyId = 0;
            i = 0;

            while (trophyId < 0x125) {
                list = _Toy_sbss_804D6EB4;

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
                    if ((f32) targetValue == Toy_803060BC(trophyId, 6)) {
                        if (HSD_Randi(2) == 0) {
                            if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
                                ptr = default_flags;
                            } else {
                                ptr = gmMainLib_8015CC78();
                            }

                            if ((u8) ptr[trophyId] == 0) {
                                Toy_SetUnlockState((s16) trophyId,
                                                   HSD_Randi(0xFE) + 1);

                                if (gm_8016B498() || (u8) gm_801A4310() == 0xC)
                                {
                                    ptr = default_flags;
                                } else {
                                    ptr = gmMainLib_8015CC78();
                                }

                                ptr += trophyId;
                                count = count - 1;
                                *ptr ^= 0x8000;
                            }
                        }
                    }
                    if (count == 0) {
                        break;
                    }
                }

                trophyId++;
                i += 2;
            }
        }
    } else {
        i = 0;
        default_flags = &Toy_804A284C[5];

        while (i < 0x125) {
            list = _Toy_sbss_804D6EB4;

            if (lbLang_IsSettingUS()) {
                while (*list != -1) {
                    if (*list == i) {
                        found = 0;
                        goto check_found2;
                    }
                    list++;
                }
            }
            found = 1;

        check_found2:
            if (found != 0) {
                if ((f32) targetValue == Toy_803060BC(i, 6)) {
                    Toy_SetUnlockState((s16) i, HSD_Randi(0xFE) + 1);

                    if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
                        ptr = default_flags;
                    } else {
                        ptr = gmMainLib_8015CC78();
                    }

                    ptr += i;
                    count = count - 1;
                    *ptr ^= 0x8000;

                    if (count == 0) {
                        goto done;
                    }
                }
            }

            i++;
        }
    }

done:
    return;
}

void Toy_SetUnlockState(enum_t trophyId, bool addValue)
{
    s32 newCount;
    s32 oldCount;
    s32 byteOffset;
    s16 idx;
    s32 count;
    s32 stateFlag;
    Toy* toy = (Toy*) &_Toy_804A26B8;
    u16* table;
    s32 newVal;
    u16* ptr;
    u16* statePtr;
    u16 temp;
    UNUSED u8 state_pad[8];
    u16 state[3];

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
            oldCount = toy->trophyCount;
        } else {
            oldCount = *gmMainLib_8015CC90();
        }
        newCount = oldCount + 1;
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
        state[2] = toy->x19A | toy->x19C;
        statePtr = &state[2];
    } else {
        statePtr = gmMainLib_8015CC84();
    }

    if (*statePtr & 0x80) {
        stateFlag = 1;
    } else {
        stateFlag = 0;
    }
    if (stateFlag == 0) {
        if (gm_8016B498() || (u8) gm_801A4310() == 0xC) {
            count = toy->trophyCount;
        } else {
            count = *gmMainLib_8015CC90();
        }
        if (count >= 0xFA) {
            *(u8*) &toy->x194 = 2;
            Toy_80305918(7, 0, 0);
        }
    }

    _Toy_80304D30();

    if ((s16) trophyId == 0xA5 && gm_80164430(0x14U) == 0) {
        gm_80164504(0x14U);
    }

    if ((s32) Toy_803060BC((s32) idx, 6) == 1) {
        gm_80172C44(idx);
    }
}

/** @note The inner loop with load_value/loop_top/check_skip labels is
 * logically: skip = !lbLang_IsSettingUS() || !IsInSkipList(var_r25,
 * _Toy_sbss_804D6EB4); Refactoring to an inline function breaks the match due
 * to control flow changes.
 */
void Toy_80305918(s8 arg0, s32 arg1, s32 arg2)
{
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

    base = (u16*) &_Toy_804A26B8.x0;
    if ((s8) arg0 == 8) {
        return;
    }

    temp_r26 = (u8*) base + 0x19E;

    for (var_r25 = 0, var_r27 = 0; var_r25 < 0x125; var_r25++, var_r27 += 2) {
        s32 skip;
        s16 temp_r0;

        /* Check if var_r25 is in skip list (only when US locale) */
        var_r22 = _Toy_sbss_804D6EB4;
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
            continue;
        }

        if ((f32) arg0 != Toy_803060BC(var_r25, 6)) {
            continue;
        }

        if (arg1 != 0) {
            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                var_r22_2 = temp_r26;
            } else {
                var_r22_2 = gmMainLib_8015CC78();
            }
            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                var_r3 = temp_r26;
            } else {
                var_r3 = gmMainLib_8015CC78();
            }
            if (*(u16*) (var_r3 + var_r27) & 0x4000) {
                u16* temp_ptr;
                u16 val;
                temp_ptr = (u16*) (var_r22_2 + var_r27);
                val = *temp_ptr;
                *temp_ptr = val ^ 0x4000;
            }
        } else {
            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                var_r3 = temp_r26;
            } else {
                var_r3 = gmMainLib_8015CC78();
            }
            *(u16*) (var_r3 + var_r27) |= 0x4000;
        }
    }

    if (arg1 != 0) {
        if (arg2 != 0) {
            u16 val4;
            s32 mask2;
            val4 = ((Toy26B8*) base)->x19C;
            mask2 = 1 << arg0;
            if (val4 & mask2) {
                ((Toy26B8*) base)->x19C = (u16) (val4 ^ mask2);
            }
        } else {
            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                ptr = (u16*) ((u8*) base + 0x19A);
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
            u16* ptr19c = (u16*) ((u8*) base + 0x19C);
            *ptr19c = (u16) (*ptr19c | (1 << arg0));
        } else {
            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                ptr = (u16*) ((u8*) base + 0x19A);
            } else {
                ptr = gmMainLib_8015CC84();
            }
            *ptr |= 1 << arg0;
        }
    }
}

s32 Toy_80305B88(void)
{
    int i;
    u32 button;
    PAD_STACK(8);

    for (i = 0; i < 4; i++) {
        if ((button = HSD_PadCopyStatus[(u8) i].trigger)) {
            gm_801677E8(i);
            break;
        }
    }
    return button;
}

s32 Toy_80305C44(void)
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

float Toy_80305D00(void)
{
    float ret;
    float val;
    int i;

    for (i = 0; i < 4; i++) {
        val = HSD_PadCopyStatus[(u8) i].nml_stickX;
        ret = val;
        if (val < 0.0F) {
            val = -val;
        }
        if (val > 0.1F) {
            break;
        }
    }

    return ret;
}

float Toy_80305DB0(void)
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

float Toy_80305EB4(void)
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

float Toy_80305FB8(void)
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

float Toy_803060BC(int trophyId, int field)
{
    TrophyData* jp_ptr;
    TrophyData* us_ptr;
    s32 lang_flag;
    s32 found_jp;

    lang_flag = 0;
    found_jp = 0;
    jp_ptr = _Toy_sbss_804D6EC0;

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
    us_ptr = _Toy_sbss_804D6EC4;
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

s16 Toy_803062BC(s32 trophyId)
{
    s16* table = Toy_sbss_804D6EDC;
    s32 i;

    for (i = 0; i < 0x125; i++) {
        if (trophyId == *table) {
            break;
        }
        table++;
    }

    return (s16) i;
}

void _Toy_803062EC(s32 arg0, u32 arg1, f32 farg0)
{
    char sp14[72];
    TrophyData* td;
    s32 id;

    td = _Toy_sbss_804D6EC4;
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

    if (_Toy_sbss_804D6E9C != NULL) {
        DevText_Erase(_Toy_sbss_804D6E9C);
        DevText_SetCursorXY(_Toy_sbss_804D6E9C, 0, 0);
        sprintf(sp14,
                "X   %3.2f\n"
                "Y   %3.2f\n"
                "Z   %3.2f\n"
                "MS  %3.2f\n"
                "SS  %3.2f\n"
                "MD  %3.2f",
                td->x08, td->x0C, td->x10, td->x14, td->x18, td->x1C);
        DevText_Print(_Toy_sbss_804D6E9C, sp14);
    }
}

static char* getViewDatFilename(void)
{
    if (lbLang_IsSavedLanguageJP()) {
        return "TyMnView.dat";
    } else {
        return "TyMnView.usd";
    }
}

static char* getDataiDatFilename(void)
{
    if (lbLang_IsSavedLanguageJP()) {
        return "TyDatai.dat";
    } else {
        return "TyDatai.usd";
    }
}

static char* getInfoDatFilename(void)
{
    if (lbLang_IsSavedLanguageJP()) {
        return "TyMnInfo.dat";
    } else {
        return "TyMnInfo.usd";
    }
}

static char* getBgDatFilename(void)
{
    return "TyMnBg.dat";
}

s32 Toy_803063D4(s32 arg0, s32 arg1, s32 arg2)
{
    s32 result;
    s32 i;
    s16* ptr;

    result = arg0 + arg1 + 1;

    if (lbLang_IsSettingJP() && lbLang_IsSavedLanguageUS()) {
        ptr = _Toy_sbss_804D6EB8;
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
        ptr = _Toy_sbss_804D6EB8;
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

s16 _Toy_803064B8(s16 arg0, s8 arg1)
{
    ToyNameData* data;
    s16 result;

    result = arg0;
    switch (arg1) {
    case 0:
        data = (ToyNameData*) _Toy_sbss_804D6EBC;
        result = data[arg0].x0;
        break;
    case 1:
        data = (ToyNameData*) _Toy_sbss_804D6EBC;
        result = data[arg0].x2;
        break;
    case 2:
        if (lbLang_IsSettingJP() != 0) {
            if (lbLang_IsSavedLanguageJP() != 0) {
                data = (ToyNameData*) _Toy_sbss_804D6EBC;
                result = data[arg0].x4;
                break;
            }
            data = (ToyNameData*) _Toy_sbss_804D6EBC;
            result = data[arg0].x8;
            break;
        }
        if (lbLang_IsSavedLanguageUS() != 0) {
            data = (ToyNameData*) _Toy_sbss_804D6EBC;
            result = data[arg0].x4;
            break;
        }
        data = (ToyNameData*) _Toy_sbss_804D6EBC;
        result = data[arg0].x8;
        break;
    case 3:
        if (lbLang_IsSettingJP() != 0) {
            if (lbLang_IsSavedLanguageJP() != 0) {
                data = (ToyNameData*) _Toy_sbss_804D6EBC;
                result = data[arg0].x6;
                break;
            }
            data = (ToyNameData*) _Toy_sbss_804D6EBC;
            result = data[arg0].xA;
            break;
        }
        if (lbLang_IsSavedLanguageUS() != 0) {
            data = (ToyNameData*) _Toy_sbss_804D6EBC;
            result = data[arg0].x6;
            break;
        }
        data = (ToyNameData*) _Toy_sbss_804D6EBC;
        result = data[arg0].xA;
        break;
    }
    return result;
}

void _Toy_8030663C(void)
{
    s32 var_r31;
    s32 var_r30;
    u16* var_r29;
    s16* var_r28;
    int var_r27;

    var_r29 = (u16*) ((u8*) Toy_804A284C + 0xA);
    var_r27 = 0;
    var_r31 = 0;
    var_r30 = 0;
    var_r28 = _Toy_sbss_804D6E64;
    do {
        u16* src;
        if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
            src = var_r29;
        } else {
            src = gmMainLib_8015CC78();
        }
        if ((u8) * (u16*) ((u8*) src + var_r30) != 0) {
            *var_r28 = _Toy_803064B8(var_r27, 0);
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

        var2_r29 = _Toy_sbss_804D6E64;
        var2_r30 = 0;
        do {
            var2_r28 = _Toy_sbss_804D6E64;
            var2_r27 = 0;
            goto loop_13_check;
        loop_13_body:
            if (*var2_r28 == _Toy_803064B8(var2_r30, 1)) {
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

        var3_r29 = _Toy_sbss_804D6E64;
        var3_r30 = 0;
        do {
            var3_r27 = _Toy_sbss_804D6E64;
            var3_r28 = 0;
            goto loop_23_check;
        loop_23_body:
            if (lbLang_IsSavedLanguageJP() != 0) {
                if (*var3_r27 == _Toy_803064B8(var3_r30, 2)) {
                    var3_r29[2] = *var3_r27;
                    var3_r29 += 3;
                } else {
                    goto block_22;
                }
            } else {
                new_var = var3_r27;
                if (*new_var == _Toy_803064B8(var3_r30, 3)) {
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

void Toy_803067BC(s32 arg0, s32 arg1)
{
    s16* src;
    s32 offset;
    s32 i;
    s16* dest;
    s32 count;
    s16* base;

    base = _Toy_sbss_804D6E64;

    if (arg1 == 0) {
        src = base + arg0;
        i = 0;
        offset = 0;
        while (i < *gmMainLib_8015CC90()) {
            M2C_FIELD(Toy_sbss_804D6EDC, s16*, offset) = *src;
            src += 3;
            i++;
            offset += 2;
        }
        return;
    }

    count = *gmMainLib_8015CC90();
    src = base + arg0;
    dest = Toy_sbss_804D6EDC + count;
    if (count != 0) {
        for (i = count; i != 0; i--) {
            *dest-- = *src;
            src += 3;
        }
    }
}

void Toy_803068E0(HSD_GObj* gobj, int unused)
{
    if (HSD_CObjSetCurrent(gobj->hsd_obj) != 0) {
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
        HSD_FogSet(NULL);
    }
}

void Toy_80306930(HSD_GObj* gobj, int unused)
{
    HSD_FogSet(gobj->hsd_obj);
}

void Toy_80306954(HSD_GObj* gobj, int unused)
{
    void* state;
    char* tbl;
    char* entry;

    tbl = _Toy_str_TyLight_dat;
    state = Toy_sbss_804D6ED4;
    if (HSD_CObjSetCurrent((HSD_CObj*) gobj->hsd_obj)) {
        if (_Toy_sbss_804D6E50 == 0) {
            entry = tbl + M2C_FIELD(state, s32*, 0x10) * 0xC;
            if (*(s32*) (entry + 0x104) != 0) {
                HSD_SetEraseColor(
                    *(u8*) (entry + 0x100), *(u8*) (entry + 0x101),
                    *(u8*) (entry + 0x102), *(u8*) (entry + 0x103));
                HSD_CObjEraseScreen((HSD_CObj*) gobj->hsd_obj, 1, 0, 0);
            }
        }
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(0);
        HSD_CObjEndCurrent();
    }
}

void _Toy_80306A0C(HSD_GObj* arg0, int unused)
{
    HSD_Fog* fog = GET_FOG(arg0);

    if (_Toy_sbss_804D6E54 == 0) {
        HSD_FogSet(NULL);
    } else {
        HSD_FogSet(fog);
    }
}

void Toy_80306A48(HSD_JObj* jobj, char* symbol1, char* symbol2, char* symbol3,
                  HSD_Archive* archive, s32 frame)
{
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
    new_var = (void*) (0 ^ 0);
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
    HSD_JObjReqAnimAll(jobj, (f32) frame);
    HSD_JObjAnimAll(jobj);
}

HSD_GObjProc* Toy_80306B18(HSD_GObj* gobj, s32 anim_frame, s32 val1, s32 val2)
{
    HSD_GObjProc* proc = NULL;
    Toy* tp = (Toy*) gobj->user_data;

    if (tp != NULL) {
        HSD_JObjClearFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
        HSD_JObjReqAnimAll(gobj->hsd_obj, anim_frame);

        tp->x8 = val1;
        tp->x4 = val2;

        proc = HSD_GObj_SetupProc(gobj, Toy_80306BB8, 0);
        HSD_GObj_80390CD4(gobj);
    }
    return proc;
}

void Toy_80306BB8(HSD_GObj* gobj)
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

void _Toy_80306C5C(HSD_GObj* arg0)
{
    s32 idx;
    s32 offset;
    TyLightData* base;
    HSD_GObj* data;
    u8* table;
    unsigned char new_var;
    HSD_LObj* lobj;
    HSD_LObj* next;

    PAD_STACK(16);

    idx = 0;
    offset = (new_var = idx) * 0xC;
    base = (TyLightData*) Toy_sbss_804D6ED4;
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
        data = base->gobj;
    }

    HSD_LObjAnimAll(((HSD_GObj*) arg0)->hsd_obj);
}

void Toy_RemoveUserData(void* ptr)
{
    HSD_Free(ptr);
}

void Toy_80306D14(void)
{
    TyModeState* state = (TyModeState*) Toy_804A284C;

    if (state->x0 == 1) {
        lbAudioAx_800237A8(0xAA, 0x7F, 0x40);
    } else if (state->x0 == 2) {
        lbAudioAx_800237A8(0xAB, 0x7F, 0x40);
    }
}

void Toy_80306D70(s32 arg0)
{
    UNUSED u8 framepad[8];

    {
        LightList** sp14;
        TyLightFile* base;
        TyLightData* data;
        char* sym;
        s32 idx;
        u8 kind;

        base = (TyLightFile*) _Toy_str_TyLight_dat;
        data = (TyLightData*) Toy_sbss_804D6ED4;

        if (data->archive != NULL && data->gobj != NULL) {
            HSD_GObjProc_8038FED4(data->gobj);
            HSD_GObjPLink_80390228(data->gobj);
            data->gobj = NULL;
            idx = base->entries[arg0].idx;
            sym = base->symbols[idx].name;
            sp14 = HSD_ArchiveGetPublicAddress(data->archive, sym);
        } else {
            idx = base->entries[arg0].idx;
            sym = base->symbols[idx].name;
            data->archive =
                lbArchive_80016DBC(_Toy_str_TyLight_dat, &sp14, sym, 0);
        }

        if (sp14 != NULL) {
            s32 spC;
            HSD_LObj* lobj;

            data->gobj = GObj_Create(2, 1, 0);
            lobj = Toy_LoadLObjList(sp14, &spC);
            kind = HSD_GObj_804D784A;
            HSD_GObjObject_80390A70(data->gobj, kind, lobj);
            GObj_SetupGXLink(data->gobj, HSD_GObj_LObjCallback, 0x37, 0);
            if (spC != 0) {
                HSD_GObj_SetupProc(data->gobj, _Toy_80306C5C, 0);
                HSD_GObj_80390CD4(data->gobj);
            }
        } else {
            idx = base->entries[arg0].idx;
            sym = base->symbols[idx].name;
            OSReport("*** Can not Load Light Label(%s)\n", sym);
            HSD_ASSERT(2253, 0);
        }
    }
}

HSD_LObj* Toy_LoadLObjList(LightList** list, s32* hasAnim)
{
    u8* base;
    HSD_LObj* lobj;
    HSD_LObj* prev;
    HSD_LObj* first;
    HSD_LightAnim** anims;
    s32 idx;
    u8* animFlag;

    PAD_STACK(4);

    prev = NULL;
    base = (u8*) Toy_sbss_804D6ED4;
    idx = 0;

    if (hasAnim != NULL) {
        *hasAnim = 0;
    }

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
                HSD_LObjReqAnimAll(lobj, 0.0f);
                if ((*anims)->position_anim != NULL) {
                    *animFlag = 1;
                }
            }
            HSD_LObjGetPosition(lobj, (Vec3*) (base + idx * 0xC + 0x1C));
            HSD_LObjGetInterest(lobj, (Vec3*) (base + idx * 0xC + 0x7C));
            idx += 1;
        }
        if (prev != NULL) {
            if (prev == NULL) {
                __assert("lobj.h", 0x136U, "lobj");
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

/// @todo .data order hack
static void order_data_670(void)
{
    /* +670 */ (void) "ScMenFigure_ambanim_light";
    /* +68C */ (void) "ScMenFigure_ambfog";
}

void _Toy_80307018(void)
{
    u8 _pad[16];
    HSD_Fog* fog;
    LightList** lights;
    void* obj;
    u8 kind;
    ToyED8Data* ptr1;
    tyUnkStruct* ptr2;
    HSD_FogDesc fog_desc;

    (void) _pad;
    ptr1 = (ToyED8Data*) Toy_sbss_804D6ED8;
    ptr2 = (tyUnkStruct*) Toy_sbss_804D6ED4;

    if (ptr1->archive == NULL) {
        HSD_ASSERTREPORT(2322, 0, "*** BG data aren't being loaded!\n");
    }

    lights =
        HSD_ArchiveGetPublicAddress(ptr1->archive, "ScMenFigure_scene_lights");
    if (lights != NULL) {
        ptr2->x0 = GObj_Create(2, 3, 0);
        obj = Toy_LoadLObjList(lights, 0);
        kind = HSD_GObj_804D784A;
        HSD_GObjObject_80390A70(ptr2->x0, kind, obj);
        GObj_SetupGXLink(ptr2->x0, HSD_GObj_LObjCallback, 0x36, 0);

        if (_Toy_sbss_804D6E50 != 0) {
            fog_desc = _Toy_803B8844;
            fog = HSD_FogLoadDesc(&fog_desc);
            ptr2->x8 = GObj_Create(3, 4, 0);
            kind = HSD_GObj_804D7848;
            HSD_GObjObject_80390A70(ptr2->x8, kind, fog);
            GObj_SetupGXLink(ptr2->x8, _Toy_80306A0C, 0x35, 0);
        }
    }
}

/// @todo .data order hack
static void order_data_6C4(void)
{
    /* +6C4 */ (void) "ScMenFigure_scene_lights";
}

void _Toy_8030715C(f32 cstick_x, f32 cstick_y)
{
    Vec3 euler;
    Vec3 light_pos;
    Vec3 interest;
    Vec3 new_interest;
    Mtx mtx;
    UNUSED u8 midpad[0x30];
    Vec3 up_vec;
    Vec3 left_vec;
    Vec3 angles;
    TyCameraData_* data;
    TyLightArray_* cur;
    TyLightArray_* data2;
    HSD_LObj* lobj;
    s32 i;
    s8* flag_ptr;
    HSD_CObj* cobj;
    PAD_STACK(36);

    data = (void*) _Toy_sbss_804D6E68;
    data2 = (TyLightArray_*) Toy_sbss_804D6ED4;
    (void) data2;
    cobj = data->x8->x28;

    HSD_CObjGetInterest(cobj, &interest);
    HSD_CObjGetInterest(cobj, &new_interest);
    HSD_CObjGetUpVector(cobj, &up_vec);
    PSVECScale(&up_vec, &up_vec, -cstick_y);
    PSVECAdd(&up_vec, &new_interest, &new_interest);
    HSD_CObjGetLeftVector(cobj, &left_vec);
    PSVECScale(&left_vec, &left_vec, cstick_x);
    PSVECAdd(&left_vec, &new_interest, &new_interest);

    if (new_interest.x <= -3000.0F || new_interest.y <= -3000.0F ||
        new_interest.z <= -3000.0F || new_interest.x >= 3000.0F ||
        new_interest.y >= 3000.0F || new_interest.z >= 3000.0F)
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
        flag_ptr = &data2->xDC[i];

        angles.x = 0.017453292F * data2->x14;
        angles.y = 0.017453292F * -data2->x18;
        angles.z = 0.0F;

        if (*flag_ptr != 0) {
            HSD_LObjGetPosition(lobj, &light_pos);
        } else {
            light_pos = *(Vec3*) &cur->x1C;
        }

        if (*flag_ptr != 0) {
            *(Vec3*) &cur->x1C = light_pos;
        }

        lbVector_ApplyEulerRotation(&light_pos, &angles);
        HSD_LObjSetPosition(lobj, &light_pos);

        if (HSD_LObjGetInterest(lobj, &light_pos) != 0) {
            if (*flag_ptr != 0) {
                *(Vec3*) &cur->x7C = light_pos;
            } else {
                light_pos = *(Vec3*) &cur->x7C;
            }
            lbVector_ApplyEulerRotation(&light_pos, &angles);
            HSD_LObjSetInterest(lobj, &light_pos);
        }

        cur = (TyLightArray_*) ((u8*) cur + 0xC);
        i += 1;

        lobj = HSD_LObjGetNext(lobj);
    }
}

/* 3FE3F8 */ static u16 _Toy_803FE3F8[9] = {
    1, 7, 22, 20, 18, 21, 19, 17, 23,
};

typedef union ToyPanelLabelData {
    char bytes[1];
    char* ptrs[1];
} ToyPanelLabelData;

void Toy_80307470(s32 arg0)
{
    HSD_AnimJoint* anim;
    HSD_JObj* loaded_jobj;
    HSD_Joint* joint;
    HSD_MatAnimJoint* matanim;
    ToyGlobalsS_* tg;
    ToyPanelLabelData* data;
    char** label;
    char** anim_label;
    HSD_ShapeAnimJoint* shapanim;
    u8 kind;

    PAD_STACK(24);

    data = (ToyPanelLabelData*) _Toy_str_TyLight_dat;
    tg = (ToyGlobalsS_*) Toy_sbss_804D6ED8;

    if (tg->x50 == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        __assert(__FILE__, 2481, "0");
    }

    if (tg->x0 != NULL) {
        HSD_GObjPLink_80390228(tg->x0);
        tg->x0 = NULL;
    }

    label = &data->ptrs[arg0];
    joint = HSD_ArchiveGetPublicAddress(tg->x50, *(label += 0x188 / 4));

    if (joint != NULL) {
        tg->x0 = GObj_Create(9, 9, 0);

        loaded_jobj = HSD_JObjLoadJoint(joint);
        anim_label = &data->ptrs[arg0 * 3];
        anim = HSD_ArchiveGetPublicAddress(tg->x50, anim_label[0x224 / 4]);
        matanim = HSD_ArchiveGetPublicAddress(tg->x50, anim_label[0x228 / 4]);
        shapanim = HSD_ArchiveGetPublicAddress(tg->x50, anim_label[0x22C / 4]);
        HSD_JObjAddAnimAll(loaded_jobj, anim, matanim, shapanim);
        HSD_JObjReqAnimAll(loaded_jobj, 0.0f);
        kind = HSD_GObj_804D7849;
        HSD_GObjObject_80390A70(tg->x0, kind, loaded_jobj);
        GObj_SetupGXLink(tg->x0, HSD_GObj_JObjCallback, 0x3C, 0);

        lb_8001204C(loaded_jobj, (HSD_JObj**) &tg->x10, _Toy_803FE3F8, 9);

        Toy_803083D8(tg->x30, 0x3E7);
        return;
    }

    OSReport("*** Can not Load Panel Label(%s)\n", *label);
    __assert(__FILE__, 2534, "0");
}

void _Toy_803075E8(s32 arg0)
{
    char* data;
    ToyED8Data* td;
    HSD_Joint* joint;
    char** ptr;
    HSD_JObj* jobj;
    HSD_AnimJoint* animjoint;
    HSD_MatAnimJoint* matanim;
    HSD_ShapeAnimJoint* shapanim;
    ToyDataJObj* tdjobj;
    u8 kind;

    PAD_STACK(88);

    data = _Toy_str_TyLight_dat;
    td = (ToyED8Data*) Toy_sbss_804D6ED8;

    if (td->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        __assert(__FILE__, 2625, "0");
    }

    if (td->gobj != NULL) {
        HSD_GObjProc_8038FED4(td->gobj);
        HSD_GObjPLink_80390228(td->gobj);
        td->gobj = NULL;
    }

    if (td->x54 != 0) {
        ((ToyED8Data*) Toy_sbss_804D6ED8)->x8->x28->x40 = 9;
        ((ToyED8Data*) Toy_sbss_804D6ED8)->x8->x28->x4->x40 = 9;
        ((ToyED8Data*) Toy_sbss_804D6ED8)->x8->x28->x4->x4->x40 = 9;
    }

    ptr = (char**) (data + arg0 * 4);
    if (*(ptr += 0x69) != NULL) {
        joint = HSD_ArchiveGetPublicAddress(td->archive, *ptr);
        if (joint != NULL) {
            td->gobj = GObj_Create(4, 7, 0);
            jobj = HSD_JObjLoadJoint(joint);
            kind = HSD_GObj_804D7849;
            HSD_GObjObject_80390A70(td->gobj, kind, jobj);
            GObj_SetupGXLink(td->gobj, HSD_GObj_JObjCallback, 0x33, 0);

            ptr = (char**) (data + arg0 * 0xC);
            animjoint =
                HSD_ArchiveGetPublicAddress(td->archive, ptr[0x290 / 4]);
            matanim = HSD_ArchiveGetPublicAddress(td->archive, ptr[0x294 / 4]);
            shapanim =
                HSD_ArchiveGetPublicAddress(td->archive, ptr[0x298 / 4]);

            if (animjoint != NULL || matanim != NULL || shapanim != NULL) {
                HSD_JObjAddAnimAll(jobj, animjoint, matanim, shapanim);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
                HSD_GObj_SetupProc(td->gobj, Toy_80306BB8, 0);
                HSD_GObj_80390CD4(td->gobj);
            }
        } else {
            OSReport("*** Can not Load Back Label(%s)\n", *ptr);
            __assert(__FILE__, 2677, "0");
        }
    } else if (td->x54 != 0) {
        tdjobj = ((ToyED8Data*) Toy_sbss_804D6ED8)->x8->x28;
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

void _Toy_80307828(int arg0)
{
    Vec3 interest;
    TyCameraData_* data;
    TyLightArray_* data2;
    HSD_CObj* cobj;

    data = (void*) _Toy_sbss_804D6E68;
    cobj = data->x8->x28;
    data2 = (TyLightArray_*) Toy_sbss_804D6ED4;
    interest = _Toy_803B8858;

    if (arg0 == 0) {
        data->x18 = data->x1C = (f32) (data->x58 = 0);
        data2->x18 = 0.0F;
        data2->x14 = 0.0F;
    } else {
        data->x18 = 0.0F;
        data2->x14 = 0.0F;
    }

    data->x20 = 38.0F;
    data->x2C = 0.0F;
    data->x28 = 0.0F;
    data->x24 = 0.0F;

    HSD_CObjSetInterest(cobj, &interest);

    PAD_STACK(12);
}

void _Toy_803078E4(void)
{
    struct tyLightData* data;
    UNK_T syms[7];
    PosArrayFull pos_en;
    PosArrayFull pos_jp;
    HSD_SObj* sobj;
    s32 i;

    data = (struct tyLightData*) Toy_sbss_804D6ED8;

    pos_en = _Toy_803B8864;
    pos_jp = _Toy_803B889C;

    if (data->x58 == NULL) {
        char* filename;

        if (lbLang_IsSavedLanguageJP() != 0) {
            filename = "TyMnInfo.dat";
        } else {
            filename = "TyMnInfo.usd";
        }

        data->x58 = lbArchive_LoadSymbols(
            filename, &syms[0], _Toy_803FE108[0], &syms[1], _Toy_803FE108[1],
            &syms[2], _Toy_803FE108[2], &syms[3], _Toy_803FE108[3], &syms[4],
            _Toy_803FE108[4], &syms[5], _Toy_803FE108[5], &syms[6],
            _Toy_803FE108[6], NULL);

        data->x0C = GObj_Create(5, 6, 0);
        GObj_SetupGXLink(data->x0C, HSD_SObjLib_803A49E0, 0x38, 0);

        i = 0;

        do {
            sobj = HSD_SObjLib_803A477C(data->x0C, syms[i], 0, 0, 0x80, 0);
            if (sobj != NULL) {
                if (lbLang_IsSavedLanguageJP() != 0) {
                    sobj->x10 = (f32) pos_jp.a[i].xy[0];
                    sobj->x14 = (f32) pos_jp.a[i].xy[1];
                } else {
                    sobj->x10 = (f32) pos_en.a[i].xy[0];
                    sobj->x14 = (f32) pos_en.a[i].xy[1];
                }
            }
            i += 1;
        } while (i < 7);
    }
}

HSD_JObj* _Toy_80307BA0(HSD_JObj* parent_jobj, s16 arg1)
{
    void* joint_data;
    HSD_JObj* jobj;
    ToyAnimState* state;
    f32 scale_val;

    state = &Toy_804A2AA8;

    if (Toy_sbss_804D6EC8 == NULL) {
        Toy_sbss_804D6EC8 = lbArchive_LoadSymbols(
            "TyStand.dat", &joint_data, "ToyStandModel_TopN_joint", NULL);
    } else {
        joint_data = HSD_ArchiveGetPublicAddress(Toy_sbss_804D6EC8,
                                                 "ToyStandModel_TopN_joint");
    }

    jobj = HSD_JObjLoadJoint(joint_data);
    HSD_JObjAddChild(parent_jobj, jobj);

    {
        s32 idx;
        if (state->jobj[0] != NULL) {
            idx = 1;
        } else {
            idx = 0;
        }
        state->x0E = (s8) idx;
        state->jobj[(s32) state->x0E] = jobj;
    }

    HSD_JObjAddTranslationY(jobj, 0.25F);

    state->x11 = 2;
    state->x10 = 2;
    state->x0F = 0;

    _Toy_80307F64(2, 0);

    scale_val = Toy_803060BC((int) arg1, 4);

    HSD_JObjSetScaleX(jobj, scale_val);
    HSD_JObjSetScaleY(jobj, scale_val);
    HSD_JObjSetScaleZ(jobj, scale_val);

    return jobj;
}

void Toy_80307E84(HSD_GObj* gobj)
{
    s32* base;
    ToyAnimState* state;
    s8 idx;
    s8 x0F_val;
    HSD_JObj* jobj0;
    HSD_JObj* jobj1;

    base = (s32*) &_Toy_804A26B8;
    state = (ToyAnimState*) ((u8*) base + 0x3F0);
    idx = M2C_FIELD(base, s8*, 0x3FE);
    x0F_val = M2C_FIELD(base, s8*, 0x3FF);
    jobj0 = (HSD_JObj*) base[idx + (0x3F4 / 4)];
    jobj1 = (HSD_JObj*) base[(idx ^ 1) + (0x3F4 / 4)];

    if (x0F_val <= 0) {
        if (state->x10 == 1) {
            HSD_JObjSetFlagsAll(jobj0, JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(jobj1, JOBJ_HIDDEN);
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

void _Toy_80307F64(s32 arg0, s32 arg1)
{
    s8 idx;
    char* strings;
    Toy26B8* base;
    ToyAnimState* state;
    HSD_JObj* jobj1;
    HSD_JObj* jobj2;

    strings = _Toy_str_TyLight_dat;
    base = (Toy26B8*) &_Toy_804A26B8;
    state = &base->anim;
    idx = base->anim.x0E;
    jobj1 = base->anim.jobj[(s32) idx];
    jobj2 = base->anim.jobj[(s32) (idx ^ 1)];

    if (base->anim.x0F == 0) {
        if (arg1 != 0) {
            if (arg0 != state->x11) {
                HSD_JObjRemoveAnimAll(jobj1);
                HSD_JObjRemoveAnimAll(jobj2);
                state->x11 = (s8) arg0;
                state->x10 = (s8) arg0;
                if (arg0 == 1) {
                    Toy_80306A48(jobj1, 0, strings + 0x438, 0,
                                 Toy_sbss_804D6EC8, 0);
                    Toy_80306A48(jobj2, 0, strings + 0x438, 0,
                                 Toy_sbss_804D6EC8, 0);
                } else {
                    Toy_80306A48(jobj1, 0, strings + 0x4C8, 0,
                                 Toy_sbss_804D6EC8, 0);
                    Toy_80306A48(jobj2, 0, strings + 0x4C8, 0,
                                 Toy_sbss_804D6EC8, 0);
                }
                state->x0F = 0xA;
                HSD_GObj_SetupProc(state->gobj, Toy_80307E84, 0);
                HSD_GObj_80390CD4(state->gobj);
            }
        } else {
            if (arg0 == 1) {
                Toy_80306A48(jobj1, 0, strings + 0x438, 0, Toy_sbss_804D6EC8,
                             10);
                Toy_80306A48(jobj2, 0, strings + 0x438, 0, Toy_sbss_804D6EC8,
                             10);
            } else {
                Toy_80306A48(jobj1, 0, strings + 0x4C8, 0, Toy_sbss_804D6EC8,
                             10);
                Toy_80306A48(jobj2, 0, strings + 0x4C8, 0, Toy_sbss_804D6EC8,
                             10);
            }
            HSD_JObjRemoveAnimAll(jobj1);
            HSD_JObjRemoveAnimAll(jobj2);
            state->x0F = 0;
        }
    }
}

char* Toy_8030813C(s16 arg0, enum_t unused)
{
    char* ptr;
    s32 i;
    s32 found;
    s32 cur;
    s32 id = arg0;

    found = 0;

    if (lbLang_IsSettingUS()) {
        cur = *(s32*) (ptr = _Toy_sbss_804D6EA4);
        if (cur == id) {
            found = 1;
        } else if (*(s32*) (ptr += 0x54) == id) {
            found = 1;
        } else if (*(s32*) (ptr += 0x54) == id) {
            found = 1;
        } else if (*(s32*) (ptr += 0x54) == id) {
            found = 1;
        } else if (*(s32*) (ptr += 0x54) == id) {
            found = 1;
        } else {
            ptr += 0x54;
        }
    }

    if (found == 0) {
        ptr = _Toy_sbss_804D6EA8;
        for (i = 0x125; i != 0; i--) {
            if (*(s32*) ptr == id) {
                found = 1;
                break;
            }
            ptr += 0x54;
        }
    }

    if (found == 0) {
        OSReport("**** Not Found Toy Model!(%d)\n", id);
        __assert("toy.c", 2979, "0");
    }

    return ptr;
}

void Toy_80308250(u8* arg0, s32 arg1, s32 arg2)
{
    void* sym;
    char* ptr;
    ptr = Toy_8030813C(arg1, arg1);

    if (*(HSD_Archive**) (arg0 + 0x14) != NULL) {
        lbArchive_80016EFC(*(HSD_Archive**) (arg0 + 0x14));
        *(HSD_Archive**) (arg0 + 0x14) = NULL;
    }

    *(char**) (arg0 + 0x8) = ptr + 4;
    *(char**) (arg0 + 0xC) = ptr + 0x24;
    *(u16*) (arg0 + 0x10) = arg1;

    if (arg2 == 0) {
        *(HSD_Archive**) (arg0 + 0x14) = lbArchive_LoadSymbols(
            *(char**) (arg0 + 0x8), &sym, *(char**) (arg0 + 0xC), 0);
    }
}

s32 Toy_803082F8(s16 idx)
{
    return Toy_803063D4((s16) Toy_80308354(idx), 2, 0x128);
}

void Toy_80308328(s32 arg0)
{
    Toy_803063D4((s16) arg0, 2, 0x128);
}

s32 Toy_80308354(s16 idx)
{
    s32 i;
    s32 target;
    TrophyData* entry;

    target = Toy_sbss_804D6EDC[idx];
    entry = _Toy_sbss_804D6EC4;

    for (i = 0; i < 0x125; entry++, i++) {
        if (target == entry->id) {
            break;
        }
    }

    if (i == 293) {
        HSD_ASSERTREPORT(3114, 0,
                         "*** Error : Not Found Model Name!(To Idx %d)\n",
                         target, entry);
    } else {
        return target;
    }
}

void Toy_803083D8(HSD_JObj* jobj, s32 arg1)
{
    s32 temp_r31;

    if (arg1 == 0x3E6) {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    if (arg1 == 0x3E7) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    temp_r31 = (s32) Toy_803060BC(arg1, 8);
    if (temp_r31 == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    if (temp_r31 == 1) {
        HSD_JObjReqAnim(jobj, 0.0F);
    } else {
        HSD_JObjReqAnim(jobj, 1.0F);
    }
    HSD_JObjAnim(jobj);
}

#pragma push
#pragma peephole on

void _Toy_803084A0(s32 arg0)
{
    volatile GXColor color;
    tyDispData* display;
    HSD_Text* text;
    s32 one;
    s32 id;

    PAD_STACK(72);

    id = arg0;
    display = (tyDispData*) Toy_sbss_804D6EE0;
    color = _Toy_color_FFBA00FF;

    if (display->x144 == NULL) {
        display->x144 = HSD_SisLib_803A5ACC(0, _Toy_sbss_804D6E70, 0.9F,
                                            -10.9F, 0.0F, 384.0F, 64.0F);
        one = 1;
        text = display->x144;
        text->default_fitting = one;
        text = display->x144;
        text->default_alignment = one;
        text = *(HSD_Text* volatile*) &display->x144;
        text->text_color = color;
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
    HSD_SisLib_803A6368(display->x144, Toy_803063D4(id, 2, 0x128));

    if (display->x148 == NULL) {
        if (lbLang_IsSavedLanguageJP()) {
            display->x148 = HSD_SisLib_803A5ACC(3, _Toy_sbss_804D6E74, 0.2F,
                                                -5.1F, 17.2F, 384.0F, 384.0F);
            text = display->x148;
            text->font_size.x = 0.035F;
            text->font_size.y = 0.034F;
        } else {
            display->x148 = HSD_SisLib_803A5ACC(3, _Toy_sbss_804D6E74, 0.2F,
                                                -5.0F, 17.2F, 384.0F, 384.0F);
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
    HSD_SisLib_803A6368(display->x148, Toy_803063D4(id, 2, 0x374));

    if (display->x14C == NULL) {
        if (lbLang_IsSavedLanguageJP()) {
            display->x14C = HSD_SisLib_803A5ACC(3, _Toy_sbss_804D6E78, 0.7F,
                                                7.9F, 17.2F, 384.0F, 64.0F);
            display->x150 = HSD_SisLib_803A5ACC(3, _Toy_sbss_804D6E7C, 0.7F,
                                                9.0F, 17.2F, 384.0F, 64.0F);
            text = display->x14C;
            text->font_size.x = 0.03F;
            text->font_size.y = 0.03F;
            text = display->x150;
            text->font_size.x = 0.03F;
            text->font_size.y = 0.03F;
        } else {
            display->x14C = HSD_SisLib_803A5ACC(3, _Toy_sbss_804D6E78, 0.7F,
                                                7.9F, 17.2F, 384.0F, 64.0F);
            display->x150 = HSD_SisLib_803A5ACC(3, _Toy_sbss_804D6E7C, 0.7F,
                                                9.0F, 17.2F, 384.0F, 64.0F);
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
    HSD_SisLib_803A6368(display->x14C, Toy_803063D4(id, 0x128, 0x37A));
    HSD_SisLib_803A6368(display->x150, Toy_803063D4(id, 0x24E, 0x380));
}

#pragma pop

HSD_GObj* Toy_803087F4(void* arg0)
{
    ToyEntryData* entry = arg0;
    ToyAnimState* anim;
    HSD_JObj* parent_jobj;
    HSD_JObj* trophy_jobj;
    HSD_Joint* joint;
    s16 trophy_id;
    char* model_name;
    f32 scale, rot;
    UNUSED u8 pad[0x10];
    char buf[0x48];
    void* spC;
    u8 kind;

    anim = &Toy_804A2AA8;

    if (entry->x14 == NULL) {
        trophy_id = entry->x10;
        model_name = Toy_8030813C(trophy_id, trophy_id);
        if (entry->x14 != NULL) {
            lbArchive_80016EFC(entry->x14);
            entry->x14 = NULL;
        }
        entry->x8 = model_name + 4;
        entry->xC = model_name + 0x24;
        entry->x10 = trophy_id;
        entry->x14 = lbArchive_LoadSymbols(entry->x8, &spC, entry->xC, 0);
    }

    joint = HSD_ArchiveGetPublicAddress(entry->x14, entry->xC);
    if (joint == NULL) {
        goto assert_fail;
    }

    if (anim->gobj != NULL) {
        HSD_GObjPLink_80390228(anim->gobj);
        anim->gobj = NULL;
        anim->jobj[1] = NULL;
        anim->jobj[0] = NULL;
    }

    anim->gobj = GObj_Create(6, 7, 0);
    anim->xC = entry->x10;

    parent_jobj = HSD_JObjAlloc();
    _Toy_80307BA0(parent_jobj, anim->xC);

    trophy_jobj = HSD_JObjLoadJoint(joint);
    HSD_JObjAddChild(parent_jobj, trophy_jobj);

    kind = HSD_GObj_804D7849;
    HSD_GObjObject_80390A70(anim->gobj, kind, parent_jobj);
    GObj_SetupGXLink(anim->gobj, HSD_GObj_JObjCallback, 0x39, 0);

    HSD_JObjSetTranslateX(trophy_jobj, Toy_803060BC((s32) anim->xC, 0));

    HSD_JObjSetTranslateY(trophy_jobj, Toy_803060BC((s32) anim->xC, 1));

    HSD_JObjSetTranslateZ(trophy_jobj, Toy_803060BC((s32) anim->xC, 2));

    scale = Toy_803060BC((s32) anim->xC, 3);
    HSD_JObjSetScaleX(trophy_jobj, scale);
    HSD_JObjSetScaleY(trophy_jobj, scale);
    HSD_JObjSetScaleZ(trophy_jobj, scale);

    rot = deg_to_rad * Toy_803060BC((s32) anim->xC, 5);
    HSD_JObjSetRotationY(trophy_jobj, rot);

    if (_Toy_sbss_804D6E9C != NULL) {
        DevText_Erase(_Toy_sbss_804D6E9C);
        DevText_SetCursorXY(_Toy_sbss_804D6E9C, 0, 0);

        sprintf(
            buf,
            "X   %3.2f\n"
            "Y   %3.2f\n"
            "Z   %3.2f\n"
            "MS  %3.2f\n"
            "SS  %3.2f\n"
            "MD  %3.2f",

            Toy_803060BC((s32) anim->xC, 0), Toy_803060BC((s32) anim->xC, 1),
            Toy_803060BC((s32) anim->xC, 2), Toy_803060BC((s32) anim->xC, 3),
            Toy_803060BC((s32) anim->xC, 4), Toy_803060BC((s32) anim->xC, 5));
        DevText_Print(_Toy_sbss_804D6E9C, buf);
    }

    {
        HSD_JObj* child = _Toy_80307BA0(parent_jobj, anim->xC);
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
        anim->x0E = 0;
    }

    goto done;

assert_fail:
    OSReport("*** Cann't Show Model!\n");
    __assert("toy.c", 3358, "0");

done:
    return anim->gobj;
}

/// @todo .data order hack
static void order_data_6F4(void)
{
    /* +7CC */ (void) "3DPos X = %f, Y = %f, Z = %f\n";
    /* +7EC */ (void) "2DPos X = %f, Y = %f\n\n";
    /* +804 */ (void) "Pos : %f, %f,%f\n";
    /* +818 */ (void) "WinSize = %f, %f\n";
    /* +82C */ (void) "WinScale = %f, %f\n";
    /* +840 */ (void) "FontSize = %f, %f\n";
    /* +854 */ (void) "RotY = %f\n";
    /* +860 */ (void) "*** Pad = %d\n";
    /* +870 */ (void) "top = %f, bottom = %f, right = %f, left = %f\n";
    /* +8A0 */ (void) "top = %f, bottom = %f\n";
    /* +8B8 */ (void) "right = %f, left = %f\n";
}

void _Toy_80308DC8(HSD_CObj* cobj)
{
    Vec3 interest;
    Vec3 eye_pos;
    un_804D6E68_t* temp_r30;
    ToyAnimState* temp_r31;
    f32 temp_f1;

    temp_r31 = &Toy_804A2AA8;
    temp_r30 = (un_804D6E68_t*) _Toy_sbss_804D6E68;

    HSD_CObjGetInterest(cobj, &interest);
    HSD_CObjGetEyePosition(cobj, &eye_pos);

    temp_f1 = temp_r30->x18;

    if (temp_f1 >= 25.0F ||
        (temp_f1 >= -3.0F && _Toy_80309338(&eye_pos, 0) <= 15.0F))
    {
        _Toy_80307F64(1, 1);
        return;
    }

    _Toy_80307F64(2, 1);

    if (temp_r30->x18 < 10.0F) {
        if (eye_pos.y < 0.0F) {
            temp_r31->x0E = 1;
            HSD_JObjClearFlagsAll(temp_r31->jobj[1], JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(temp_r31->jobj[0], JOBJ_HIDDEN);
        } else {
            temp_r31->x0E = 0;
            HSD_JObjClearFlagsAll(temp_r31->jobj[0], JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(temp_r31->jobj[1], JOBJ_HIDDEN);
        }
    } else {
        temp_r31->x0E = 1;
        HSD_JObjClearFlagsAll(temp_r31->jobj[1], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(temp_r31->jobj[0], JOBJ_HIDDEN);
    }
}

void _Toy_80308F04(HSD_CObj* cobj)
{
    UNUSED u8 interest_pad[16];
    Vec3 interest;
    Toy26B8* data;
    Toy6E68* state;
    void* jobj_ptr;
    f32 top;
    f32 bottom;
    f32 right;
    f32 left;
    ToyJObjNode* jobj;

    PAD_STACK(48);

    data = (void*) &_Toy_804A26B8;
    state = _Toy_sbss_804D6E68;
    jobj_ptr = ((Toy26B8_2*) data->x3F0)->x28;

    top = HSD_CObjGetTop(cobj);
    bottom = HSD_CObjGetBottom(cobj);
    right = HSD_CObjGetRight(cobj);
    left = HSD_CObjGetLeft(cobj);

    if (jobj_ptr == NULL) {
        __assert("jobj.h", 0x378, "jobj");
    }

    if (state->x61 == 1) {
        if ((f32) state->x5C < 10.0F) {
            _Toy_sbss_804D6E80 = _Toy_sbss_804D6E80 - 0.0013187003F;
            if (top != _Toy_sbss_804D6E80) {
                f32 val = _Toy_sbss_804D6E80;
                if (val < 0.036397F) {
                    val = 0.036397F;
                }
                HSD_CObjSetTop(cobj, val);
            }

            _Toy_sbss_804D6E84 = _Toy_sbss_804D6E84 - 0.00008119978F;
            if (bottom != _Toy_sbss_804D6E84) {
                f32 val = _Toy_sbss_804D6E84;
                if (val < -0.036397F) {
                    val = -0.036397F;
                }
                HSD_CObjSetBottom(cobj, val);
            }

            _Toy_sbss_804D6E88 = _Toy_sbss_804D6E88 - 0.0032531999F;
            if (right != _Toy_sbss_804D6E88) {
                f32 val = _Toy_sbss_804D6E88;
                if (val < 0.044307F) {
                    val = 0.044307F;
                }
                HSD_CObjSetRight(cobj, val);
            }

            _Toy_sbss_804D6E8C = _Toy_sbss_804D6E8C - 0.0017468001F;
            if (left != _Toy_sbss_804D6E8C) {
                HSD_CObjSetLeft(cobj, _Toy_sbss_804D6E8C);
            }

            state->x5C = state->x5C + 1;
        } else {
            HSD_CObjSetTop(cobj, 0.036397F);
            HSD_CObjSetBottom(cobj, -0.036397F);
            HSD_CObjSetRight(cobj, 0.044307F);
            HSD_CObjSetLeft(cobj, -0.044307F);

            if (_Toy_sbss_804D6E58 != 0) {
                jobj = Toy_sbss_804D6ED8->xC->x28;
                while (jobj != NULL) {
                    jobj->x40 = 9;
                    jobj = jobj->x4;
                }
            } else {
                jobj = Toy_sbss_804D6ED8->xC->x28;
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
        if ((f32) state->x5C < 10.0F) {
            state->x20 = state->x20 - _Toy_sbss_804D6E90;
            state->x18 = state->x18 - _Toy_sbss_804D6E94;

            HSD_CObjGetInterest(cobj, &interest);
            interest.x = interest.x + data->x0.x;
            interest.y = interest.y + data->x0.y;
            interest.z = interest.z + data->x0.z;
            HSD_CObjSetInterest(cobj, &interest);

            _Toy_80308DC8(cobj);

            _Toy_sbss_804D6E80 = _Toy_sbss_804D6E80 + 0.0013187003F;
            if (top != _Toy_sbss_804D6E80) {
                f32 val = _Toy_sbss_804D6E80;
                if (val > 0.049584F) {
                    val = 0.049584F;
                }
                HSD_CObjSetTop(cobj, val);
            }

            _Toy_sbss_804D6E84 = _Toy_sbss_804D6E84 + 0.00008119978F;
            if (bottom != _Toy_sbss_804D6E84) {
                f32 val = _Toy_sbss_804D6E84;
                if (val > -0.035585F) {
                    val = -0.035585F;
                }
                HSD_CObjSetBottom(cobj, val);
            }

            _Toy_sbss_804D6E88 = _Toy_sbss_804D6E88 + 0.0032531999F;
            if (right != _Toy_sbss_804D6E88) {
                f32 val = _Toy_sbss_804D6E88;
                if (val > 0.076839F) {
                    val = 0.076839F;
                }
                HSD_CObjSetRight(cobj, val);
            }

            _Toy_sbss_804D6E8C = _Toy_sbss_804D6E8C + 0.0017468001F;
            if (left != _Toy_sbss_804D6E8C) {
                HSD_CObjSetLeft(cobj, _Toy_sbss_804D6E8C);
            }

            state->x5C = state->x5C + 1;
        } else {
            state->x61 = 0;
            _Toy_80307828(1);

            HSD_CObjSetTop(cobj, 0.049584F);
            HSD_CObjSetBottom(cobj, -0.035585F);
            HSD_CObjSetRight(cobj, 0.076839F);
            HSD_CObjSetLeft(cobj, -0.026839F);

            _Toy_803102C4(1);

            state->x5C = 0;
            state->x58 = 0x95E;
            state->x60 = 4;
            HSD_PadRenewStatus();
        }
    }
}

f32 _Toy_80309338(Vec3* arg0, Vec3* arg1)
{
    f64 unused[2];
    Vec3 sp14;
    volatile f32 sp10;
    Vec3* var_r3;
    Vec3* var_r4;
    f32 temp_f4;
    f32 temp_f2;
    f32 var_f1;
    f64 guess;

    sp14 = _Toy_803B88D4;
    var_r3 = arg0;
    var_r4 = arg1;
    if (var_r3 == NULL) {
        var_r3 = &sp14;
    }
    if (var_r4 == NULL) {
        var_r4 = &sp14;
    }
    var_f1 = var_r3->y - var_r4->y;
    temp_f4 = var_r3->x - var_r4->x;
    temp_f2 = var_r3->z - var_r4->z;
    var_f1 = var_f1 * var_f1;
    var_f1 = temp_f4 * temp_f4 + var_f1;
    var_f1 = temp_f2 * temp_f2 + var_f1;
    if (var_f1 > 0.0f) {
        guess = __frsqrte((f64) var_f1);
        guess = 0.5 * guess * (3.0 - guess * guess * var_f1);
        guess = 0.5 * guess * (3.0 - guess * guess * var_f1);
        guess = 0.5 * guess * (3.0 - guess * guess * var_f1);
        sp10 = (f32) (var_f1 * guess);
        var_f1 = sp10;
    }
    return var_f1;
}

#pragma push
#pragma dont_inline off

void _Toy_80309404(HSD_GObj* gobj)
{
    struct {
        u8 pad[0x2C];
        Vec3 pos;
        u8 pad2[0x10];
    } eye_pad;
    Vec3 eye_pos;
    HSD_CObj* cobj;
    Vec3 transition_interest;
    Vec3 transition_eye;
    Toy26B8* base;
    ToyED8Data* ed8;
    Toy6E68* state;
    ToyCameraControl* ed4;
    ToyAnimState* anim;
    f32 dist;
    f32 tmp;
    f32 zoom_update;
    f32 movement_update;
    f32 rotate_update;
    u32 trigger;
    u32 button;
    s32 sign;
    s32 sp138;
    s32 sp134;
    s32 sp130;
    s32 sp12C;

    PAD_STACK(260);

    cobj = gobj->hsd_obj;
    base = (Toy26B8*) &_Toy_804A26B8;
    ed8 = Toy_sbss_804D6ED8;
    state = _Toy_sbss_804D6E68;
    anim = &base->anim;
    ed4 = (ToyCameraControl*) Toy_sbss_804D6ED4;
    rotate_update = 0.0f;
    movement_update = 0.0f;
    zoom_update = 0.0f;

    HSD_CObjGetEyePosition(cobj, &eye_pos);
    dist = _Toy_80309338(&eye_pos, NULL);

    {
        f32 val;
        f32 abs;
        s32 i;

        for (i = 0; i < 4; i++) {
            val = HSD_PadCopyStatus[(u8) i].nml_stickX;
            if (val < 0.0F) {
                abs = -val;
            } else {
                abs = val;
            }
            if (abs > 0.1F) {
                break;
            }
        }
        state->x30 = val;
    }

    state->x34 = Toy_80305DB0();

    state->x54 = 0.0f;
    state->x50 = 0.0f;

    tmp = state->x30;
    if ((tmp > -0.2f) && (tmp < 0.2f)) {
        state->x30 = 0.0f;
    } else {
        if (tmp > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        state->x30 = (f32) (-((0.2f * (f32) sign) - tmp) / 0.8f);
    }

    tmp = state->x34;
    if ((tmp > -0.2f) && (tmp < 0.2f)) {
        state->x34 = 0.0f;
    } else {
        if (tmp > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        state->x34 = (f32) (-((0.2f * (f32) sign) - tmp) / 0.8f);
    }

    state->x40 = Toy_80305EB4();

    state->x44 = Toy_80305FB8();

    tmp = state->x40;
    if ((tmp > -0.2f) && (tmp < 0.2f)) {
        state->x40 = 0.0f;
    } else {
        if (tmp > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        state->x40 = (f32) (-((0.2f * (f32) sign) - tmp) / 0.8f);
    }

    tmp = state->x44;
    if ((tmp > -0.2f) && (tmp < 0.2f)) {
        state->x44 = 0.0f;
    } else {
        if (tmp > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        state->x44 = (f32) (-((0.2f * (f32) sign) - tmp) / 0.8f);
    }

    {
        u8 cooldown = state->x60;
        if ((s8) cooldown != 0) {
            state->x60 = (s8) (cooldown - 1);
            _Toy_8030715C(0.0f, 0.0f);
            return;
        }
    }

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        Toy_80310660(1);
        HSD_GObj_80390CD4(gobj);
        mn_8022F268();
        base->x198 = 1;
        return;
    }

    switch ((s8) state->x61) {
    case 0: {
        trigger = Toy_80305B88();

        if (trigger & 0x200) {
            lbAudioAx_80024030(0);
            Toy_80310660(1);
            HSD_GObj_80390CD4(gobj);
            tyList_803147C4();
            return;
        }

        {
            s32 trophy_count;
            if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                trophy_count = base->trophy_count;
            } else {
                trophy_count = *gmMainLib_8015CC90();
            }
            if (trophy_count == 0) {
                return;
            }
        }

        if ((state->x40 + state->x44) != 0.0f) {
            goto reset_idle_timer;
        }
        trigger = Toy_80305B88();

        if (trigger & 0xF) {
        reset_idle_timer:
            state->x58 = 0;
        } else {
            if ((f32) state->x58 > 2400.0f) {
                state->x24 += 0.01f;
                if (state->x24 > 1.0f) {
                    state->x24 = 1.0f;
                }
                state->x1C = (f32) (state->x1C + state->x24);
                tmp = state->x1C;
                if (tmp < -360.0f) {
                    state->x1C += 360.0f;
                }
                tmp = state->x1C;
                if (tmp > 360.0f) {
                    state->x1C = (f32) (tmp - 360.0f);
                }
                ed4->x18 = (f32) state->x1C;
            }
            state->x58 = state->x58 + 1;
        }

        {
            s32 trophy_count;
            if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                trophy_count = base->trophy_count;
            } else {
                trophy_count = *gmMainLib_8015CC90();
            }
            if (trophy_count == 1) {
                if ((state->x30 + state->x34) != 0.0f) {
                    state->x34 = 0.0f;
                    state->x30 = 0.0f;
                }
            }
        }

        trigger = Toy_80305B88();
        if (trigger & 0xD00) {
            lbAudioAx_80024030(1);
            _Toy_sbss_804D6E80 = HSD_CObjGetTop(cobj);
            _Toy_sbss_804D6E84 = HSD_CObjGetBottom(cobj);
            _Toy_sbss_804D6E88 = HSD_CObjGetRight(cobj);
            _Toy_sbss_804D6E8C = HSD_CObjGetLeft(cobj);
            state->x5C = 0;
            {
                ToyTransitionObj* obj = state->x0;
                obj->x24 = 0;
                obj->x20 = 0x480000;
            }
            {
                ToyTransitionObj* obj = state->x4;
                obj->x24 = 0;
                obj->x20 = 0;
            }
            {
                ToyTransitionObj* obj = state->xC;
                obj->x24 = 0;
                obj->x20 = 0;
            }
            state->x61 = 1;
            _Toy_8030715C(0.0f, 0.0f);
            return;
        }
        rotate_update = 1.0f;
        break;
    }
    case 1:
    case 3:
        _Toy_80308F04(cobj);
        break;
    case 2:
        trigger = Toy_80305B88();
        if (trigger & 0x100) {
            ToyJObjNode* jobj_node;

            _Toy_sbss_804D6E58 ^= 1;
            jobj_node = (ToyJObjNode*) ed8->xC->x28;
            if (_Toy_sbss_804D6E58 != 0) {
                while (jobj_node != NULL) {
                    jobj_node->x40 = 9;
                    jobj_node = (ToyJObjNode*) jobj_node->x4;
                }
            } else {
                while (jobj_node != NULL) {
                    jobj_node->x40 = 8;
                    jobj_node = (ToyJObjNode*) jobj_node->x4;
                }
            }
        }

        trigger = Toy_80305B88();

        if ((trigger & 0x200) || ((f32) state->x5C > 7200.0f)) {
            ToyJObjNode* jobj_node;

            lbAudioAx_80024030(0);
            _Toy_sbss_804D6E80 = HSD_CObjGetTop(cobj);
            _Toy_sbss_804D6E84 = HSD_CObjGetBottom(cobj);
            _Toy_sbss_804D6E88 = HSD_CObjGetRight(cobj);
            _Toy_sbss_804D6E8C = HSD_CObjGetLeft(cobj);

            {
                ToyTransitionObj* obj = state->x0;
                obj->x24 = 0;
                obj->x20 = 0x50480000;
            }
            {
                ToyTransitionObj* obj = state->x4;
                obj->x24 = 0;
                obj->x20 = (s32) 0x80000000U;
            }
            {
                ToyTransitionObj* obj = state->xC;
                obj->x24 = 0;
                obj->x20 = 0x40000000;
            }
            jobj_node = (ToyJObjNode*) ed8->xC->x28;
            while (jobj_node != NULL) {
                jobj_node->x40 = 9;
                jobj_node = (ToyJObjNode*) jobj_node->x4;
            }

            state->x5C = 0;
            transition_eye = _Toy_803B88E0;
            transition_interest = _Toy_803B88EC;
            HSD_CObjGetEyePosition(cobj, &eye_pad.pos);
            transition_eye.y = 8.0f;
            HSD_CObjGetInterest(cobj, &transition_interest);
            base->x0.x = (transition_eye.x - transition_interest.x) / 10.0f;
            base->x0.y = (transition_eye.y - transition_interest.y) / 10.0f;
            base->x0.z = (transition_eye.z - transition_interest.z) / 10.0f;
            _Toy_sbss_804D6E90 = (state->x20 - 38.0f) / 10.0f;
            _Toy_sbss_804D6E94 = state->x18 / 10.0f;
            state->x61 = 3;
        }

        trigger = Toy_80305B88();

        tmp = state->x44 + (state->x40 + (state->x30 + state->x34));
        if ((tmp + (f32) trigger) == 0.0f) {
            state->x5C = state->x5C + 1;
        } else {
            state->x5C = 0;
        }

        button = Toy_80305C44();
        if (button & 1) {
            state->x50 = (f32) (-0.3f * (dist / 38.0f));
        }

        button = Toy_80305C44();
        if (button & 2) {
            state->x50 = (f32) (0.3f * (dist / 38.0f));
        }

        button = Toy_80305C44();
        if (button & 8) {
            state->x54 = (f32) (0.3f * (dist / 38.0f));
        }

        button = Toy_80305C44();
        if (button & 4) {
            state->x54 = (f32) (-0.3f * (dist / 38.0f));
        }

        button = Toy_80305C44();
        if (button & 0x100) {
            tmp = state->x30;
            if ((tmp != 0.0f) && (tmp < 0.0f)) {
                state->x50 = (f32) (0.3f * tmp * (dist / 38.0f));
            }
        }

        button = Toy_80305C44();
        if (button & 0x100) {
            tmp = state->x30;
            if ((tmp != 0.0f) && (tmp > 0.0f)) {
                state->x50 = (f32) (0.3f * tmp * (dist / 38.0f));
            }
        }

        button = Toy_80305C44();
        if (button & 0x100) {
            tmp = state->x34;
            if ((tmp != 0.0f) && (tmp > 0.0f)) {
                state->x54 = (f32) (0.3f * tmp * (dist / 38.0f));
            }
        }

        button = Toy_80305C44();
        if (button & 0x100) {
            tmp = state->x34;
            if ((tmp != 0.0f) && (tmp < 0.0f)) {
                state->x54 = (f32) (0.3f * tmp * (dist / 38.0f));
            }
        }

        if ((state->x50 == 0.0f) && (state->x54 == 0.0f)) {
            button = Toy_80305C44();
            if (button & 0x100) {
                _Toy_803102C4(0);
            } else {
                _Toy_803102C4(1);
            }
        } else {
            _Toy_803102C4(0);
            movement_update = 1.0f;
        }

        if (movement_update == 0.0f) {
            button = Toy_80305C44();
            if (button & 0x800) {
                state->x20 = (f32) - ((0.025f * dist) - state->x20);
                zoom_update = 1.0f;
            } else {
                button = Toy_80305C44();
                if (button & 0x400) {
                    state->x20 = (f32) - ((-0.025f * dist) - state->x20);
                    zoom_update = 1.0f;
                } else {
                    tmp = state->x34;
                    if (tmp != 0.0f) {
                        state->x20 =
                            (f32) - ((dist * (0.025f * tmp)) - state->x20);
                        zoom_update = 1.0f;
                    }
                }
            }
            if (state->x20 < 5.0f) {
                state->x20 = 5.0f;
            }
            if (state->x20 > 250.0f) {
                state->x20 = 250.0f;
            }
        }
        rotate_update = 1.0f;
        break;
    }

    if (rotate_update != 0.0f) {
        state->x1C = (f32) - ((3.0f * state->x40) - state->x1C);
        state->x18 = (f32) - ((3.0f * state->x44) - state->x18);
        if (state->x18 < -89.0f) {
            state->x18 = -89.0f;
        }
        if (state->x18 > 89.0f) {
            state->x18 = 89.0f;
        }
        tmp = state->x1C;
        if (tmp < -360.0f) {
            state->x1C = (f32) (tmp + 360.0f);
        }
        tmp = state->x1C;
        if (tmp > 360.0f) {
            state->x1C = (f32) (tmp - 360.0f);
        }
        ed4->x18 = (f32) state->x1C;
        ed4->x14 = (f32) state->x18;
        if ((state->x40 + state->x44) != 0.0f) {
            state->x24 = 0.0f;
        }

        if ((movement_update == 0.0f) && (zoom_update == 0.0f)) {
            s16 trophy_count;

            if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                trophy_count = base->trophy_count;
            } else {
                trophy_count = *gmMainLib_8015CC90();
            }
            if (trophy_count > 1) {
                tmp = state->x30;
                if (tmp < 0.0f) {
                    tmp = -tmp;
                }
                if (!(tmp > 0.9f)) {
                    trigger = Toy_80305B88();
                    if (!(trigger & 0x60)) {
                        goto skip_trophy_cycle;
                    }
                }
                {
                    TyDisplayData* display;
                    u32 trig2;

                    display = Toy_sbss_804D6EE0;
                    if (state->x30 < 0.0f) {
                        goto cycle_prev;
                    }
                    trig2 = Toy_80305B88();
                    if (trig2 & 0x441) {
                    cycle_prev: {
                        s16 new_idx;
                        s32 total;

                        lbAudioAx_80024030(2);
                        new_idx = display->selectedIdx - 1;
                        display->selectedIdx = new_idx;
                        if (new_idx < 0) {
                            if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC))
                            {
                                total = base->trophy_count;
                            } else {
                                total = *gmMainLib_8015CC90();
                            }
                            display->selectedIdx = (s16) (total - 1);
                        }
                        if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                            total = base->trophy_count;
                        } else {
                            total = *gmMainLib_8015CC90();
                        }
                        if (total > 3) {
                            s16 cur_idx = display->selectedIdx;
                            if ((cur_idx - 1) < 0) {
                                s32 cnt;
                                s32 lk;
                                ToyListEntry* entry;
                                HSD_Archive* oa;
                                char* md;

                                if ((gm_8016B498() != 0) ||
                                    (gm_801A4310() == 0xC))
                                {
                                    cnt = base->trophy_count;
                                } else {
                                    cnt = *gmMainLib_8015CC90();
                                }
                                lk = cnt + cur_idx;
                                entry = display->first_entry;
                                {
                                    s16 tid = Toy_sbss_804D6EDC[lk - 1];
                                    md = Toy_8030813C(tid, lk);
                                    oa = entry->archive;
                                    if (oa != NULL) {
                                        lbArchive_80016EFC(oa);
                                        entry->archive = NULL;
                                    }
                                    entry->archive_name = md + 4;
                                    entry->symbol_name = md + 0x24;
                                    entry->trophy_id = tid;
                                    entry->archive = lbArchive_LoadSymbols(
                                        entry->archive_name, &sp138,
                                        entry->symbol_name, 0);
                                }
                            } else {
                                ToyListEntry* entry;
                                HSD_Archive* oa;
                                char* md;
                                s16 tid;

                                entry = display->first_entry;
                                tid = Toy_sbss_804D6EDC[cur_idx - 1];
                                md = Toy_8030813C(
                                    tid, (enum_t) &Toy_sbss_804D6EDC[cur_idx]);
                                oa = entry->archive;
                                if (oa != NULL) {
                                    lbArchive_80016EFC(oa);
                                    entry->archive = NULL;
                                }
                                entry->archive_name = md + 4;
                                entry->symbol_name = md + 0x24;
                                entry->trophy_id = tid;
                                entry->archive = lbArchive_LoadSymbols(
                                    entry->archive_name, &sp134,
                                    entry->symbol_name, 0);
                            }
                            {
                                HSD_Archive* ma = display->last_entry->archive;
                                if (ma != NULL) {
                                    lbArchive_80016EFC(ma);
                                    display->last_entry->archive = NULL;
                                }
                            }
                            display->selected_entry =
                                display->selected_entry->prev;
                            display->first_entry = display->first_entry->prev;
                            display->last_entry = display->last_entry->prev;
                        } else {
                            display->selected_entry =
                                display->selected_entry->prev;
                        }
                    }
                    } else {
                        if (state->x30 > 0.0f) {
                            goto cycle_next;
                        }
                        trig2 = Toy_80305B88();
                        if (!(trig2 & 0x822)) {
                            goto after_cycle_direction;
                        }
                    cycle_next: {
                        s32 total;
                        s16 cur_idx;

                        lbAudioAx_80024030(2);
                        display->selectedIdx = display->selectedIdx + 1;
                        if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                            total = base->trophy_count;
                        } else {
                            total = *gmMainLib_8015CC90();
                        }
                        if (display->selectedIdx >= total) {
                            display->selectedIdx = 0;
                        }
                        if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                            total = base->trophy_count;
                        } else {
                            total = *gmMainLib_8015CC90();
                        }
                        if (total > 3) {
                            s32 cnt;

                            if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC))
                            {
                                cnt = base->trophy_count;
                            } else {
                                cnt = *gmMainLib_8015CC90();
                            }
                            cur_idx = display->selectedIdx;
                            if ((s32) (cur_idx + 1) >= cnt) {
                                s32 cnt2;
                                ToyListEntry* entry;
                                HSD_Archive* oa;
                                char* md;
                                s16 tid;
                                s32 lk;

                                if ((gm_8016B498() != 0) ||
                                    (gm_801A4310() == 0xC))
                                {
                                    cnt2 = base->trophy_count;
                                } else {
                                    cnt2 = *gmMainLib_8015CC90();
                                }
                                entry = display->last_entry->next;
                                lk = cur_idx - cnt2;
                                tid = Toy_sbss_804D6EDC[lk + 1];
                                md = Toy_8030813C(tid,
                                                  (enum_t) Toy_sbss_804D6EDC);
                                oa = entry->archive;
                                if (oa != NULL) {
                                    lbArchive_80016EFC(oa);
                                    entry->archive = NULL;
                                }
                                entry->archive_name = md + 4;
                                entry->symbol_name = md + 0x24;
                                entry->trophy_id = tid;
                                entry->archive = lbArchive_LoadSymbols(
                                    entry->archive_name, &sp130,
                                    entry->symbol_name, 0);
                            } else {
                                ToyListEntry* entry;
                                HSD_Archive* oa;
                                char* md;
                                s16 tid;

                                entry = display->last_entry->next;
                                tid = Toy_sbss_804D6EDC[cur_idx + 1];
                                md = Toy_8030813C(
                                    tid, (enum_t) &Toy_sbss_804D6EDC[cur_idx]);
                                oa = entry->archive;
                                if (oa != NULL) {
                                    lbArchive_80016EFC(oa);
                                    entry->archive = NULL;
                                }
                                entry->archive_name = md + 4;
                                entry->symbol_name = md + 0x24;
                                entry->trophy_id = tid;
                                entry->archive = lbArchive_LoadSymbols(
                                    entry->archive_name, &sp12C,
                                    entry->symbol_name, 0);
                            }
                            {
                                HSD_Archive* ma =
                                    display->first_entry->archive;
                                if (ma != NULL) {
                                    lbArchive_80016EFC(ma);
                                    display->first_entry->archive = NULL;
                                }
                            }
                            display->selected_entry =
                                display->selected_entry->next;
                            display->first_entry = display->first_entry->next;
                            display->last_entry = display->last_entry->next;
                        } else {
                            display->selected_entry =
                                display->selected_entry->next;
                        }
                    }
                    }

                after_cycle_direction:
                    _Toy_80307828(0);
                    _Toy_8030715C(0.0f, 0.0f);
                    state->x58 = 0x95E;
                    Toy_803087F4(display->selected_entry);
                    {
                        s16 idx = Toy_sbss_804D6EDC[display->selectedIdx];
                        u16* flags;

                        if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                            flags = base->trophy_flags;
                        } else {
                            flags = gmMainLib_8015CC78();
                        }

                        if (flags[idx] & 0x8000) {
                            idx = Toy_sbss_804D6EDC[display->selectedIdx];
                            if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC))
                            {
                                flags = base->trophy_flags;
                            } else {
                                flags = gmMainLib_8015CC78();
                            }
                            flags += idx;
                            *flags ^= 0x8000;
                        }
                    }
                    _Toy_803084A0(display->selected_entry->trophy_id);
                    Toy_803083D8(ed8->x30,
                                 (s32) display->selected_entry->trophy_id);
                    state->x60 = 0x14;
                }
            skip_trophy_cycle:;
            }
        }

        trigger = Toy_80305B88();
        if (trigger & 0x1000) {
            lbAudioAx_80024030(2);
            state->x58 = 0;
            ed4->x10 = (s32) (ed4->x10 + 1);
            if (ed4->x10 == 6) {
                ed4->x10 = 0;
            }
            Toy_80306D70(ed4->x10);
            _Toy_803075E8(ed4->x10);
        }

        trigger = Toy_80305B88();
        if (trigger & 0x10) {
            _Toy_80307828(0);
            ed4->x10 = 0;
            Toy_80306D70(ed4->x10);
            _Toy_803075E8(ed4->x10);
            anim->x11 = 2;
            anim->x10 = 2;
            anim->x0F = 0;
            anim->x0E = 0;
            _Toy_80307F64(2, 0);
        }
    }

    _Toy_80308DC8(cobj);
    _Toy_8030715C(state->x50, state->x54);
    state->x38 = state->x30;
    state->x3C = state->x34;
    state->x48 = state->x40;
    state->x4C = state->x44;
}

#pragma pop

/// trophy/lighting debug viewer
void _Toy_8030B530(HSD_GObj* arg0)
{
    HSD_GObj* gobj = arg0;
    Toy26B8* base = (Toy26B8*) &_Toy_804A26B8;
    HSD_CObj* cobj = gobj->hsd_obj;
    Toy6E68* state = (Toy6E68*) _Toy_sbss_804D6E68;
    void* ed8 = Toy_sbss_804D6ED8;
    void* ed4 = Toy_sbss_804D6ED4;
    ToyAnimState* anim = &base->anim;

    if (base->x3F0 != NULL) {
        HSD_JObj* jobj_child;
        HSD_JObj* jobj_next;
        f32 stick_x;
        f32 stick_y;
        f32 adj_x;
        f32 adj_y;
        f32 substick_x;
        f32 substick_y;
        f32 adj_sx;
        f32 adj_sy;
        u32 trigger;
        u32 button;
        f32 angle;
        s32 sp190;
        s32 sp18C;
        s32 sp188;
        s32 sp184;

        PAD_STACK(272);

        {
            void* anim_state_ptr = M2C_FIELD(anim, void**, 0x0);
            void* x28_ptr = M2C_FIELD(anim_state_ptr, void**, 0x28);
            jobj_child = M2C_FIELD(x28_ptr, HSD_JObj**, 0x10);
            jobj_next = jobj_child->next;
        }

        {
            f32 abs;
            s32 i;

            for (i = 0; i < 4; i++) {
                if ((stick_x = HSD_PadCopyStatus[(u8) i].nml_stickX) < 0.0F) {
                    abs = -stick_x;
                } else {
                    abs = stick_x;
                }
                if (abs > 0.1F) {
                    break;
                }
            }
        }
        stick_y = Toy_80305DB0();

        if ((stick_x > -0.2f) && (stick_x < 0.2f)) {
            adj_x = 0.0f;
        } else {
            s32 sign;
            if (stick_x > 0.0f) {
                sign = 1;
            } else {
                sign = -1;
            }
            adj_x = -((0.2f * (f32) sign) - stick_x) / 0.8f;
        }

        if ((stick_y > -0.2f) && (stick_y < 0.2f)) {
            adj_y = 0.0f;
        } else {
            s32 sign;
            if (stick_y > 0.0f) {
                sign = 1;
            } else {
                sign = -1;
            }
            adj_y = -((0.2f * (f32) sign) - stick_y) / 0.8f;
        }

        substick_x = Toy_80305EB4();
        substick_y = Toy_80305FB8();

        if ((substick_x > -0.2f) && (substick_x < 0.2f)) {
            adj_sx = 0.0f;
        } else {
            s32 sign;
            if (substick_x > 0.0f) {
                sign = 1;
            } else {
                sign = -1;
            }
            adj_sx = -((0.2f * (f32) sign) - substick_x) / 0.8f;
        }

        if ((substick_y > -0.2f) && (substick_y < 0.2f)) {
            adj_sy = 0.0f;
        } else {
            s32 sign;
            if (substick_y > 0.0f) {
                sign = 1;
            } else {
                sign = -1;
            }
            adj_sy = -((0.2f * (f32) sign) - substick_y) / 0.8f;
        }

        {
            u8 cooldown = state->x60;
            if ((s8) cooldown != 0) {
                state->x60 = (s8) (cooldown - 1);
                return;
            }
        }

        trigger = Toy_80305B88();

        if (trigger & 0x10) {
            lbAudioAx_80024030(0);
            if ((s8) state->x61 == 0) {
                Toy_80310660(1);
                HSD_GObj_80390CD4(arg0);
                tyList_803147C4();
                return;
            }
        }

        {
            u8 mode = state->x61;
            if ((s8) mode == 1) {
                _Toy_80308F04(cobj);
                return;
            }
            if ((s8) mode == 3) {
                _Toy_80308F04(cobj);
                return;
            }
        }

        trigger = Toy_80305B88();

        if (trigger & 0x400) {
            _Toy_sbss_804D6E80 = HSD_CObjGetTop(cobj);
            _Toy_sbss_804D6E84 = HSD_CObjGetBottom(cobj);
            _Toy_sbss_804D6E88 = HSD_CObjGetRight(cobj);
            _Toy_sbss_804D6E8C = HSD_CObjGetLeft(cobj);

            trigger = Toy_80305B88();
            OSReport("*** Pad = %d\n", trigger);
            state->x5C = 0;

            {
                u8 mode = state->x61;
                if ((s8) mode == 0) {
                    *(s32*) (M2C_FIELD(state, u8**, 0x00) + 0x24) = 0;
                    *(s32*) (M2C_FIELD(state, u8**, 0x00) + 0x20) = 0x480000;
                    *(s32*) (M2C_FIELD(state, u8**, 0x04) + 0x24) = 0;
                    *(s32*) (M2C_FIELD(state, u8**, 0x04) + 0x20) = 0;
                    *(s32*) (M2C_FIELD(state, u8**, 0x0C) + 0x24) = 0;
                    *(s32*) (M2C_FIELD(state, u8**, 0x0C) + 0x20) = 0;
                    state->x61 = 1;
                    state->x5C = 0;
                    return;
                }
                if ((s8) mode == 2) {
                    state->x5C = 0;
                    _Toy_80307828(0);
                    *(s32*) (M2C_FIELD(state, u8**, 0x00) + 0x24) = 0;
                    *(s32*) (M2C_FIELD(state, u8**, 0x00) + 0x20) = 0x50480000;
                    *(s32*) (M2C_FIELD(state, u8**, 0x04) + 0x24) = 0;
                    *(s32*) (M2C_FIELD(state, u8**, 0x04) + 0x20) =
                        (s32) 0x80000000U;
                    *(s32*) (M2C_FIELD(state, u8**, 0x0C) + 0x24) = 0;
                    *(s32*) (M2C_FIELD(state, u8**, 0x0C) + 0x20) = 0x40000000;
                    state->x5C = 0;
                    state->x61 = 3;
                    lbAudioAx_80024030(0);
                    return;
                }
            }
            goto check_buttons;
        }
    check_buttons:

        button = Toy_80305C44();

        if (button & 0x400) {
            u32 btn2;
            btn2 = Toy_80305C44();
            if (btn2 & 2) {
                adj_x = 0.01f;
                state->x60 = 8;
            }

            btn2 = Toy_80305C44();
            if (btn2 & 1) {
                adj_x = -0.01f;
                state->x60 = 8;
            }

            HSD_JObjAddRotationY(jobj_next, 0.017453292f * adj_x);
            _Toy_803062EC((s32) anim->xC, 5U,
                          57.29578f * HSD_JObjGetRotationY(jobj_next));

            {
                f32 abs_y = ABS(adj_y);
                if (abs_y > 0.8f) {
                    f32 dist = state->x20;
                    state->x20 = (f32) - ((dist * (0.025f * adj_y)) - dist);
                    if (state->x20 < 5.0f) {
                        state->x20 = 5.0f;
                    }
                    if (state->x20 > 250.0f) {
                        state->x20 = 250.0f;
                    }
                }
            }
        } else {
            u32 btn3;
            btn3 = Toy_80305C44();

            if (btn3 & 0x100) {
                u32 btn4;
                btn4 = Toy_80305C44();
                if (btn4 & 2) {
                    adj_x = 1.0f;
                    state->x60 = 8;
                }

                btn4 = Toy_80305C44();
                if (btn4 & 1) {
                    adj_x = -1.0f;
                    state->x60 = 8;
                }

                btn4 = Toy_80305C44();
                if (btn4 & 8) {
                    adj_y = 1.0f;
                    state->x60 = 8;
                }

                btn4 = Toy_80305C44();
                if (btn4 & 4) {
                    adj_y = -1.0f;
                    state->x60 = 8;
                }

                angle = lb_8000D008(adj_y, adj_x);

                if (state->x18 < -25.0f) {
                    f32 abs_x2 = ABS(adj_x);
                    if (abs_x2 > 0.8f) {
                        f32 dx = 0.01f * cosf(angle);
                        HSD_JObjAddTranslationX(jobj_next, dx);
                        _Toy_803062EC((s32) anim->xC, 0U,
                                      HSD_JObjGetTranslationX(jobj_next));
                    }
                    {
                        f32 abs_y2 = ABS(adj_y);
                        if (abs_y2 > 0.8f) {
                            f32 dz = 0.01f * -sinf(angle);
                            HSD_JObjAddTranslationZ(jobj_next, dz);
                            _Toy_803062EC((s32) anim->xC, 2U,
                                          HSD_JObjGetTranslationZ(jobj_next));
                        }
                    }
                } else {
                    f32 abs_x3 = ABS(adj_x);
                    if (abs_x3 > 0.8f) {
                        f32 dx = 0.01f * cosf(angle);
                        HSD_JObjAddTranslationX(jobj_next, dx);
                        _Toy_803062EC((s32) anim->xC, 0U,
                                      HSD_JObjGetTranslationX(jobj_next));
                    }
                    {
                        f32 abs_y3 = ABS(adj_y);
                        if (abs_y3 > 0.8f) {
                            f32 dy = 0.01f * sinf(angle);
                            HSD_JObjAddTranslationY(jobj_next, dy);
                            _Toy_803062EC((s32) anim->xC, 1U,
                                          HSD_JObjGetTranslationY(jobj_next));
                        }
                    }
                }
            } else {
                u32 btn5;
                btn5 = Toy_80305C44();

                if (btn5 & 0x200) {
                    if (!(adj_y > 0.8f)) {
                        u32 btn6;
                        btn6 = Toy_80305C44();
                        if (btn6 & 8) {
                            goto scale_up_all;
                        }

                        if (!(adj_y < -0.8f)) {
                            u32 btn7;
                            btn7 = Toy_80305C44();
                            if (btn7 & 4) {
                                goto scale_down_all;
                            }

                            if (!(adj_x > 0.8f)) {
                                u32 btn8;
                                btn8 = Toy_80305C44();
                                if (btn8 & 2) {
                                    goto scale_up_xz;
                                }

                                if (!(adj_x < -0.8f)) {
                                    u32 btn9;
                                    btn9 = Toy_80305C44();
                                    if (btn9 & 1) {
                                        goto scale_down_xz;
                                    }
                                } else {
                                    u32 btn10;
                                scale_down_xz:
                                    HSD_JObjAddScaleX(jobj_child, -0.01f);
                                    HSD_JObjAddScaleZ(jobj_child, -0.01f);
                                    {
                                        HSD_JObj* n2 = jobj_next->next;
                                        HSD_JObjAddScaleX(n2, -0.01f);
                                        HSD_JObjAddScaleZ(n2, -0.01f);
                                        _Toy_803062EC((s32) anim->xC, 4U,
                                                      HSD_JObjGetScaleX(n2));
                                    }
                                    btn10 = Toy_80305C44();
                                    if (btn10 & 1) {
                                        state->x60 = 8;
                                    }
                                }
                            } else {
                                u32 btn10;
                            scale_up_xz:
                                HSD_JObjAddScaleX(jobj_child, 0.01f);
                                HSD_JObjAddScaleZ(jobj_child, 0.01f);
                                {
                                    HSD_JObj* n2 = jobj_next->next;
                                    HSD_JObjAddScaleX(n2, 0.01f);
                                    HSD_JObjAddScaleZ(n2, 0.01f);
                                    _Toy_803062EC((s32) anim->xC, 4U,
                                                  HSD_JObjGetScaleX(n2));
                                }
                                btn10 = Toy_80305C44();
                                if (btn10 & 2) {
                                    state->x60 = 8;
                                }
                            }
                        } else {
                            u32 btn10;
                        scale_down_all:
                            HSD_JObjAddScaleX(jobj_next, -0.01f);
                            HSD_JObjAddScaleY(jobj_next, -0.01f);
                            HSD_JObjAddScaleZ(jobj_next, -0.01f);
                            _Toy_803062EC((s32) anim->xC, 3U,
                                          HSD_JObjGetScaleX(jobj_next));
                            btn10 = Toy_80305C44();
                            if (btn10 & 4) {
                                state->x60 = 8;
                            }
                        }
                    } else {
                        u32 btn10;
                    scale_up_all:
                        HSD_JObjAddScaleX(jobj_next, 0.01f);
                        HSD_JObjAddScaleY(jobj_next, 0.01f);
                        HSD_JObjAddScaleZ(jobj_next, 0.01f);
                        _Toy_803062EC((s32) anim->xC, 3U,
                                      HSD_JObjGetScaleX(jobj_next));
                        btn10 = Toy_80305C44();
                        if (btn10 & 8) {
                            state->x60 = 8;
                        }
                    }
                } else {
                    if ((s8) state->x61 == 0) {
                        u32 bm;
                        bm = Toy_80305C44();
                        if (bm != 8) {
                            u32 bm2;
                            bm2 = Toy_80305C44();
                            if (bm2 != 4) {
                                u32 bm3;
                                bm3 = Toy_80305C44();
                                if (bm3 != 1) {
                                    u32 bm4;
                                    bm4 = Toy_80305C44();
                                    if (bm4 == 2) {
                                        goto do_mode_switch;
                                    }
                                } else {
                                    goto do_mode_switch;
                                }
                            } else {
                                goto do_mode_switch;
                            }
                        } else {
                        do_mode_switch:
                            switch ((s32) _Toy_sbss_804D6E60) {
                            case 0:
                                lbLang_IsSavedLanguageJP();
                                break;
                            case 1:
                                lbLang_IsSavedLanguageJP();
                                break;
                            case 2:
                                lbLang_IsSavedLanguageJP();
                                break;
                            }
                        }
                    }
                    state->x1C = (f32) - ((3.0f * adj_x) - state->x1C);
                    state->x18 = (f32) - ((3.0f * adj_y) - state->x18);
                    if (state->x18 < -89.0f) {
                        state->x18 = -89.0f;
                    }
                    if (state->x18 > 89.0f) {
                        state->x18 = 89.0f;
                    }
                    {
                        f32 yaw = state->x1C;
                        if (yaw < -360.0f) {
                            state->x1C = (f32) (yaw + 360.0f);
                        }
                    }
                    {
                        f32 yaw = state->x1C;
                        if (yaw > 360.0f) {
                            state->x1C = (f32) (yaw - 360.0f);
                        }
                    }
                    M2C_FIELD(ed4, f32*, 0x18) = (f32) state->x1C;
                    M2C_FIELD(ed4, f32*, 0x14) = (f32) state->x18;
                }
            }
        }

        trigger = Toy_80305B88();
        if (trigger & 0x1000) {
            state->x58 = 0;
            M2C_FIELD(ed4, s32*, 0x10) = M2C_FIELD(ed4, s32*, 0x10) + 1;
            if (M2C_FIELD(ed4, s32*, 0x10) == 6) {
                M2C_FIELD(ed4, s32*, 0x10) = 0;
            }
            Toy_80306D70(M2C_FIELD(ed4, s32*, 0x10));
            _Toy_803075E8(M2C_FIELD(ed4, s32*, 0x10));
        }

        _Toy_80308DC8(cobj);

        trigger = Toy_80305B88();

        if (trigger & 0x60) {
            void* display;
            u32 trig2;
            display = Toy_sbss_804D6EE0;

            trig2 = Toy_80305B88();

            if (trig2 & 0x441) {
                s16 new_idx;
                s16 total;
                lbAudioAx_80024030(2);
                new_idx = M2C_FIELD(display, s16*, 0x154) - 1;
                M2C_FIELD(display, s16*, 0x154) = new_idx;
                if (new_idx < 0) {
                    if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                        total = M2C_FIELD(base, s16*, 0x3EC);
                    } else {
                        total = *gmMainLib_8015CC90();
                    }
                    M2C_FIELD(display, s16*, 0x154) = (s16) (total - 1);
                }
                if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                    total = M2C_FIELD(base, s16*, 0x3EC);
                } else {
                    total = *gmMainLib_8015CC90();
                }
                if (total > 3) {
                    s16 cur_idx = M2C_FIELD(display, s16*, 0x154);
                    if ((cur_idx - 1) < 0) {
                        s16 cnt;
                        s32 lk;
                        u8* entry;
                        HSD_Archive* oa;
                        char* md;
                        if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                            cnt = M2C_FIELD(base, s16*, 0x3EC);
                        } else {
                            cnt = *gmMainLib_8015CC90();
                        }
                        lk = cnt + cur_idx;
                        entry = M2C_FIELD(display, u8**, 0x138);
                        {
                            s16 tid = Toy_sbss_804D6EDC[lk - 1];
                            oa = *(HSD_Archive**) (entry + 0x14);
                            md = Toy_8030813C(tid, lk);
                            if (oa != NULL) {
                                lbArchive_80016EFC(oa);
                                *(HSD_Archive**) (entry + 0x14) = NULL;
                            }
                            *(char**) (entry + 0x8) = md + 4;
                            *(char**) (entry + 0xC) = md + 0x24;
                            *(s16*) (entry + 0x10) = tid;
                            *(HSD_Archive**) (entry + 0x14) =
                                lbArchive_LoadSymbols(
                                    *(char**) (entry + 0x08), &sp190,
                                    *(char**) (entry + 0x0C), 0);
                        }
                    } else {
                        u8* entry;
                        HSD_Archive* oa;
                        char* md;
                        s16 tid;
                        entry = M2C_FIELD(display, u8**, 0x138);
                        tid = Toy_sbss_804D6EDC[cur_idx - 1];
                        oa = *(HSD_Archive**) (entry + 0x14);
                        md = Toy_8030813C(
                            tid, (enum_t) &Toy_sbss_804D6EDC[cur_idx]);
                        if (oa != NULL) {
                            lbArchive_80016EFC(oa);
                            *(HSD_Archive**) (entry + 0x14) = NULL;
                        }
                        *(char**) (entry + 0x8) = md + 4;
                        *(char**) (entry + 0xC) = md + 0x24;
                        *(s16*) (entry + 0x10) = tid;
                        *(HSD_Archive**) (entry + 0x14) =
                            lbArchive_LoadSymbols(*(char**) (entry + 0x08),
                                                  &sp18C,
                                                  *(char**) (entry + 0x0C), 0);
                    }
                    {
                        HSD_Archive* ma =
                            *(HSD_Archive**) (M2C_FIELD(display, u8**, 0x13C) +
                                              0x14);
                        if (ma != NULL) {
                            lbArchive_80016EFC(ma);
                            *(HSD_Archive**) (M2C_FIELD(display, u8**, 0x13C) +
                                              0x14) = NULL;
                        }
                    }
                    M2C_FIELD(display, void**, 0x140) =
                        *(void**) M2C_FIELD(display, u8**, 0x140);
                    M2C_FIELD(display, void**, 0x138) =
                        *(void**) M2C_FIELD(display, u8**, 0x138);
                    M2C_FIELD(display, void**, 0x13C) =
                        *(void**) M2C_FIELD(display, u8**, 0x13C);
                } else {
                    M2C_FIELD(display, void**, 0x140) =
                        *(void**) M2C_FIELD(display, u8**, 0x140);
                }
            } else {
                s16 total;
                s16 cur_idx;
                lbAudioAx_80024030(2);
                M2C_FIELD(display, s16*, 0x154) =
                    M2C_FIELD(display, s16*, 0x154) + 1;
                if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                    total = M2C_FIELD(base, s16*, 0x3EC);
                } else {
                    total = *gmMainLib_8015CC90();
                }
                if (M2C_FIELD(display, s16*, 0x154) >= total) {
                    M2C_FIELD(display, s16*, 0x154) = 0;
                }
                if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                    total = M2C_FIELD(base, s16*, 0x3EC);
                } else {
                    total = *gmMainLib_8015CC90();
                }
                if (total > 3) {
                    s16 cnt;
                    if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                        cnt = M2C_FIELD(base, s16*, 0x3EC);
                    } else {
                        cnt = *gmMainLib_8015CC90();
                    }
                    cur_idx = M2C_FIELD(display, s16*, 0x154);
                    if ((s32) (cur_idx + 1) >= cnt) {
                        s16 cnt2;
                        u8* entry;
                        HSD_Archive* oa;
                        char* md;
                        s16 tid;
                        s32 lk;
                        if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                            cnt2 = M2C_FIELD(base, s16*, 0x3EC);
                        } else {
                            cnt2 = *gmMainLib_8015CC90();
                        }
                        entry =
                            *(u8**) (M2C_FIELD(display, u8**, 0x13C) + 0x04);
                        lk = cur_idx - cnt2;
                        tid = M2C_FIELD(Toy_sbss_804D6EDC, s16*, (lk * 2) + 2);
                        oa = *(HSD_Archive**) (entry + 0x14);
                        md = Toy_8030813C(tid, (enum_t) Toy_sbss_804D6EDC);
                        if (oa != NULL) {
                            lbArchive_80016EFC(oa);
                            *(HSD_Archive**) (entry + 0x14) = NULL;
                        }
                        *(char**) (entry + 0x8) = md + 4;
                        *(char**) (entry + 0xC) = md + 0x24;
                        *(s16*) (entry + 0x10) = tid;
                        *(HSD_Archive**) (entry + 0x14) =
                            lbArchive_LoadSymbols(*(char**) (entry + 0x08),
                                                  &sp188,
                                                  *(char**) (entry + 0x0C), 0);
                    } else {
                        u8* entry;
                        HSD_Archive* oa;
                        char* md;
                        s16 tid;
                        entry =
                            *(u8**) (M2C_FIELD(display, u8**, 0x13C) + 0x04);
                        tid = Toy_sbss_804D6EDC[cur_idx + 1];
                        oa = *(HSD_Archive**) (entry + 0x14);
                        md = Toy_8030813C(
                            tid, (enum_t) &Toy_sbss_804D6EDC[cur_idx]);
                        if (oa != NULL) {
                            lbArchive_80016EFC(oa);
                            *(HSD_Archive**) (entry + 0x14) = NULL;
                        }
                        *(char**) (entry + 0x8) = md + 4;
                        *(char**) (entry + 0xC) = md + 0x24;
                        *(s16*) (entry + 0x10) = tid;
                        *(HSD_Archive**) (entry + 0x14) =
                            lbArchive_LoadSymbols(*(char**) (entry + 0x08),
                                                  &sp184,
                                                  *(char**) (entry + 0x0C), 0);
                    }
                    {
                        HSD_Archive* ma =
                            *(HSD_Archive**) (M2C_FIELD(display, u8**, 0x138) +
                                              0x14);
                        if (ma != NULL) {
                            lbArchive_80016EFC(ma);
                            *(HSD_Archive**) (M2C_FIELD(display, u8**, 0x138) +
                                              0x14) = NULL;
                        }
                    }
                    M2C_FIELD(display, void**, 0x140) =
                        *(void**) (M2C_FIELD(display, u8**, 0x140) + 0x04);
                    M2C_FIELD(display, void**, 0x138) =
                        *(void**) (M2C_FIELD(display, u8**, 0x138) + 0x04);
                    M2C_FIELD(display, void**, 0x13C) =
                        *(void**) (M2C_FIELD(display, u8**, 0x13C) + 0x04);
                } else {
                    M2C_FIELD(display, void**, 0x140) =
                        *(void**) (M2C_FIELD(display, u8**, 0x140) + 0x04);
                }
            }

            _Toy_80307828(0);
            _Toy_8030715C(0.0f, 0.0f);
            state->x58 = 0x95E;
            Toy_803087F4(M2C_FIELD(display, void**, 0x140));
            _Toy_803084A0(*(s16*) (M2C_FIELD(display, u8**, 0x140) + 0x10));
            Toy_803083D8(M2C_FIELD(ed8, HSD_JObj**, 0x30),
                         (s32) *
                             (s16*) (M2C_FIELD(display, u8**, 0x140) + 0x10));
        }

        trigger = Toy_80305B88();
        if (trigger & 0x1000) {
            _Toy_80307828(0);
        }

        {
            f32 top = HSD_CObjGetTop(cobj);
            f32 bottom = HSD_CObjGetBottom(cobj);
            f32 right = HSD_CObjGetRight(cobj);
            f32 left = HSD_CObjGetLeft(cobj);
            f32 left_copy = left;
            if (HSD_PadCopyStatus[1].trigger & 0x1000) {
                OSReport("top = %f, bottom = %f, right = %f, left = %f\n",
                         (u32) (s32) left_copy, top, bottom, right, left_copy);
                return;
            }
            if (HSD_PadCopyStatus[1].button & 8) {
                f32 nt = top + 0.001f;
                f32 nb = bottom + 0.001f;
                HSD_CObjSetTop(cobj, nt);
                HSD_CObjSetBottom(cobj, nb);
                OSReport("top = %f, bottom = %f\n", nt, nb);
                return;
            }
            if (HSD_PadCopyStatus[1].button & 4) {
                f32 nt = top - 0.001f;
                f32 nb = bottom - 0.001f;
                HSD_CObjSetTop(cobj, nt);
                HSD_CObjSetBottom(cobj, nb);
                OSReport("top = %f, bottom = %f\n", nt, nb);
                return;
            }
            if (HSD_PadCopyStatus[1].button & 1) {
                f32 nr = HSD_CObjGetRight(cobj) - 0.001f;
                f32 nl = HSD_CObjGetLeft(cobj) - 0.001f;
                HSD_CObjSetRight(cobj, nr);
                HSD_CObjSetLeft(cobj, nl);
                OSReport("right = %f, left = %f\n", nr, nl);
                return;
            }
            if (HSD_PadCopyStatus[1].button & 2) {
                f32 nr = HSD_CObjGetRight(cobj) + 0.001f;
                f32 nl = HSD_CObjGetLeft(cobj) + 0.001f;
                HSD_CObjSetRight(cobj, nr);
                HSD_CObjSetLeft(cobj, nl);
                OSReport("right = %f, left = %f\n", nr, nl);
                return;
            }
            _Toy_8030715C(0.3f * adj_sx, 0.3f * adj_sy);
        }
    }
}

void _Toy_8030E110(HSD_GObj* arg0)
{
    Vec3 sp140;
    Vec3 sp134;
    Vec3 sp128;
    void* spD8;
    void* spD4;
    void* spCC;
    void* spC8;
    Toy26B8* base;
    void* ed4;
    HSD_CObj* cobj;
    Toy6E68* state;
    ToyAnimState* anim;
    f32 abs_val, tmp;
    s32 sign;
    f32 moved_x, moved_y;
    u32 trigger, button;
    TyDisplayData* display;
    ToyListEntry* entry;
    char* result;
    s16 trophy_id;
    HSD_Archive* archive;

    PAD_STACK(176);

    base = (Toy26B8*) &_Toy_804A26B8;
    anim = &base->anim;
    state = (Toy6E68*) _Toy_sbss_804D6E68;
    ed4 = Toy_sbss_804D6ED4;
    cobj = arg0->hsd_obj;
    moved_x = 0.0f;
    moved_y = 0.0f;
    {
        f32 val;
        f32 abs;
        s32 i;

        for (i = 0; i < 4; i++) {
            val = HSD_PadCopyStatus[(u8) i].nml_stickX;
            if (val < 0.0F) {
                abs = -val;
            } else {
                abs = val;
            }
            if (abs > 0.1F) {
                break;
            }
        }
        state->x30 = val;
    }

    state->x34 = Toy_80305DB0();
    state->x54 = 0.0f;
    state->x50 = 0.0f;

    tmp = state->x30;
    if ((tmp > -0.2f) && (tmp < 0.2f)) {
        state->x30 = 0.0f;
    } else {
        if (tmp > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        state->x30 = (f32) (-((0.2f * (f32) sign) - tmp) / 0.8f);
    }
    tmp = state->x34;
    if ((tmp > -0.2f) && (tmp < 0.2f)) {
        state->x34 = 0.0f;
    } else {
        if (tmp > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        state->x34 = (f32) (-((0.2f * (f32) sign) - tmp) / 0.8f);
    }

    state->x40 = Toy_80305EB4();

    state->x44 = Toy_80305FB8();

    tmp = state->x40;
    if ((tmp > -0.2f) && (tmp < 0.2f)) {
        state->x40 = 0.0f;
    } else {
        if (tmp > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        state->x40 = (f32) (-((0.2f * (f32) sign) - tmp) / 0.8f);
    }
    tmp = state->x44;
    if ((tmp > -0.2f) && (tmp < 0.2f)) {
        state->x44 = 0.0f;
    } else {
        if (tmp > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        state->x44 = (f32) (-((0.2f * (f32) sign) - tmp) / 0.8f);
    }

    {
        u8 cd = state->x60;
        if ((s8) cd != 0) {
            state->x60 = (s8) (cd - 1);
            _Toy_8030715C(0.0f, 0.0f);
            return;
        }
    }

    {
        u8 mode = state->x61;
        switch ((s8) mode) {
        case 0:
            trigger = Toy_80305B88();

            if (trigger & 0x200) {
                lbAudioAx_80024030(0);
                Toy_80310660(1);
                HSD_GObj_80390CD4(arg0);
                tyList_803147C4();
                return;
            }

            {
                s32 tc;
                if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                    tc = base->trophy_count;
                } else {
                    tc = *gmMainLib_8015CC90();
                }
                if (tc == 0) {
                    return;
                }
                trigger = Toy_80305B88();

                if (trigger & 0xD00) {
                    lbAudioAx_80024030(1);
                    _Toy_sbss_804D6E80 = HSD_CObjGetTop(cobj);
                    _Toy_sbss_804D6E84 = HSD_CObjGetBottom(cobj);
                    _Toy_sbss_804D6E88 = HSD_CObjGetRight(cobj);
                    _Toy_sbss_804D6E8C = HSD_CObjGetLeft(cobj);
                    state->x5C = 0;
                    state->x61 = 1;
                    _Toy_8030715C(0.0f, 0.0f);
                    return;
                }
            }
            goto case_default;

        case 1:
        case 3:
            _Toy_80308F04(cobj);
            goto case_default;

        case 2:
            trigger = Toy_80305B88();

            if ((trigger & 0x200) || ((f32) state->x5C > 7200.0f)) {
                ToyJObjNode* jobj_node;
                lbAudioAx_80024030(0);
                _Toy_sbss_804D6E80 = HSD_CObjGetTop(cobj);
                _Toy_sbss_804D6E84 = HSD_CObjGetBottom(cobj);
                _Toy_sbss_804D6E88 = HSD_CObjGetRight(cobj);
                _Toy_sbss_804D6E8C = HSD_CObjGetLeft(cobj);
                jobj_node =
                    (ToyJObjNode*) ((ToyED8Data*) Toy_sbss_804D6ED8)->xC->x28;
                while (jobj_node != NULL) {
                    jobj_node->x40 = 9;
                    jobj_node = (ToyJObjNode*) jobj_node->x4;
                }
                state->x5C = 0;
                sp134 = _Toy_803B88F8;
                sp128 = _Toy_803B8904;
                HSD_CObjGetEyePosition(cobj, &sp140);
                sp134.y = 8.0f;
                HSD_CObjGetInterest(cobj, &sp128);
                base->x0.x = (f32) ((sp134.x - sp128.x) / 10.0f);
                base->x0.y = (f32) ((sp134.y - sp128.y) / 10.0f);
                base->x0.z = (f32) ((sp134.z - sp128.z) / 10.0f);
                _Toy_sbss_804D6E90 = (state->x20 - 38.0f) / 10.0f;
                _Toy_sbss_804D6E94 = state->x18 / 10.0f;
                state->x61 = 3;
            }

            trigger = Toy_80305B88();

            tmp = state->x44 + (state->x40 + (state->x30 + state->x34));
            if ((tmp + (f32) trigger) == 0.0f) {
                state->x5C = state->x5C + 1;
            } else {
                state->x5C = 0;
            }

            button = Toy_80305C44();
            if (button & 0x100) {
                f32 sx = state->x30;
                if ((sx != 0.0f) && (sx < 0.0f)) {
                    state->x50 = (f32) (0.3f * sx * (state->x20 / 38.0f));
                }
            }

            button = Toy_80305C44();
            if (button & 0x100) {
                f32 sx = state->x30;
                if ((sx != 0.0f) && (sx > 0.0f)) {
                    state->x50 = (f32) (0.3f * sx * (state->x20 / 38.0f));
                }
            }

            button = Toy_80305C44();
            if (button & 0x100) {
                f32 sy = state->x34;
                if ((sy != 0.0f) && (sy > 0.0f)) {
                    state->x54 = (f32) (0.3f * sy * (state->x20 / 38.0f));
                }
            }

            button = Toy_80305C44();
            if (button & 0x100) {
                f32 sy = state->x34;
                if ((sy != 0.0f) && (sy < 0.0f)) {
                    state->x54 = (f32) (0.3f * sy * (state->x20 / 38.0f));
                }
            }

            if ((state->x50 == 0.0f) && (state->x54 == 0.0f)) {
                button = HSD_PadCopyStatus[0].button;
                if (button != 0) {
                    gm_801677E8(0);
                } else {
                    button = HSD_PadCopyStatus[1].button;
                    if (button != 0) {
                        gm_801677E8(1);
                    } else {
                        button = HSD_PadCopyStatus[2].button;
                        if (button != 0) {
                            gm_801677E8(2);
                        } else {
                            button = HSD_PadCopyStatus[3].button;
                            if (button != 0) {
                                gm_801677E8(3);
                            }
                        }
                    }
                }
                if (button & 0x100) {
                    goto pan_active;
                }
                _Toy_803102C4(1);
            } else {
            pan_active:
                _Toy_803102C4(0);
            }

            if ((state->x50 != 0.0f) || (state->x54 != 0.0f)) {
                moved_x = 1.0f;
            }

            if (moved_x == 0.0f) {
                f32 sy = state->x34;
                if (sy != 0.0f) {
                    f32 dist = state->x20;
                    state->x20 = (f32) - ((dist * (0.025f * sy)) - dist);
                    moved_y = 1.0f;
                }
                if (state->x20 < 5.0f) {
                    state->x20 = 5.0f;
                }
                if (state->x20 > 250.0f) {
                    state->x20 = 250.0f;
                }
            }
            goto case_default;

        default:
        case_default:
            trigger = Toy_80305B88();
            if (trigger & 0x800) {
                _Toy_sbss_804D6E54 ^= 1;
            }

            state->x1C = (f32) - ((3.0f * state->x40) - state->x1C);
            state->x18 = (f32) - ((3.0f * state->x44) - state->x18);
            if (state->x18 < -89.0f) {
                state->x18 = -89.0f;
            }
            if (state->x18 > 89.0f) {
                state->x18 = 89.0f;
            }
            tmp = state->x1C;
            if (tmp < -360.0f) {
                state->x1C = (f32) (tmp + 360.0f);
            }
            tmp = state->x1C;
            if (tmp > 360.0f) {
                state->x1C = (f32) (tmp - 360.0f);
            }
            M2C_FIELD(ed4, f32*, 0x18) = (f32) state->x1C;
            M2C_FIELD(ed4, f32*, 0x14) = (f32) state->x18;
            if ((state->x40 + state->x44) != 0.0f) {
                state->x24 = 0.0f;
            }

            if ((moved_x == 0.0f) && (moved_y == 0.0f)) {
                trigger = Toy_80305B88();
                if (trigger & 0x60) {
                    display = Toy_sbss_804D6EE0;
                    {
                        s32 tc;
                        if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC)) {
                            tc = base->trophy_count;
                        } else {
                            tc = *gmMainLib_8015CC90();
                        }
                        if (tc == 1) {
                            state->x58 = 0x961;
                            return;
                        }
                    }
                    if (!(state->x30 < 0.0f)) {
                        trigger = Toy_80305B88();
                        if (trigger & 0x441) {
                            goto cycle_prev;
                        }
                        if (!(state->x30 > 0.0f)) {
                            trigger = Toy_80305B88();
                            if (trigger & 0x822) {
                                goto cycle_next;
                            }
                        } else {
                        cycle_next:
                            lbAudioAx_80024030(2);
                            display->selectedIdx =
                                (s16) (display->selectedIdx + 1);
                            {
                                s32 tc2;
                                if ((gm_8016B498() != 0) ||
                                    (gm_801A4310() == 0xC))
                                {
                                    tc2 = base->trophy_count;
                                } else {
                                    tc2 = *gmMainLib_8015CC90();
                                }
                                if (display->selectedIdx >= tc2) {
                                    display->selectedIdx = 0;
                                }
                            }
                            {
                                s32 tc3;
                                if ((gm_8016B498() != 0) ||
                                    (gm_801A4310() == 0xC))
                                {
                                    tc3 = base->trophy_count;
                                } else {
                                    tc3 = *gmMainLib_8015CC90();
                                }
                                if (tc3 > 3) {
                                    s32 tc4;
                                    s16 cur_trophy;
                                    s32 next_idx;
                                    if ((gm_8016B498() != 0) ||
                                        (gm_801A4310() == 0xC))
                                    {
                                        tc4 = base->trophy_count;
                                    } else {
                                        tc4 = *gmMainLib_8015CC90();
                                    }
                                    cur_trophy = display->selectedIdx;
                                    next_idx = (s32) (cur_trophy + 1);
                                    if (next_idx >= tc4) {
                                        s32 tc5;
                                        if ((gm_8016B498() != 0) ||
                                            (gm_801A4310() == 0xC))
                                        {
                                            tc5 = base->trophy_count;
                                        } else {
                                            tc5 = *gmMainLib_8015CC90();
                                        }
                                        entry = display->last_entry->next;
                                        trophy_id = Toy_sbss_804D6EDC
                                            [display->selectedIdx - tc5];
                                        result = Toy_8030813C(
                                            trophy_id,
                                            (s32) Toy_sbss_804D6EDC);
                                        archive = entry->archive;
                                        if (archive != NULL) {
                                            lbArchive_80016EFC(archive);
                                            entry->archive = NULL;
                                        }
                                        entry->archive_name = result + 4;
                                        entry->symbol_name = result + 0x24;
                                        entry->trophy_id = trophy_id;
                                        entry->archive = lbArchive_LoadSymbols(
                                            entry->archive_name, &spCC,
                                            entry->symbol_name, 0);
                                    } else {
                                        entry = display->last_entry->next;
                                        trophy_id =
                                            Toy_sbss_804D6EDC[cur_trophy];
                                        result = Toy_8030813C(
                                            trophy_id, (s32) &Toy_sbss_804D6EDC
                                                           [cur_trophy]);
                                        archive = entry->archive;
                                        if (archive != NULL) {
                                            lbArchive_80016EFC(archive);
                                            entry->archive = NULL;
                                        }
                                        entry->archive_name = result + 4;
                                        entry->symbol_name = result + 0x24;
                                        entry->trophy_id = trophy_id;
                                        entry->archive = lbArchive_LoadSymbols(
                                            entry->archive_name, &spC8,
                                            entry->symbol_name, 0);
                                    }
                                    archive = display->first_entry->archive;
                                    if (archive != NULL) {
                                        lbArchive_80016EFC(archive);
                                        display->first_entry->archive = NULL;
                                    }
                                    display->selected_entry =
                                        display->selected_entry->next;
                                    display->first_entry =
                                        display->first_entry->next;
                                    display->last_entry =
                                        display->last_entry->next;
                                } else {
                                    display->selected_entry =
                                        display->selected_entry->next;
                                }
                            }
                        }
                    } else {
                    cycle_prev:
                        lbAudioAx_80024030(2);
                        display->selectedIdx =
                            (s16) (display->selectedIdx - 1);
                        if (display->selectedIdx < 0) {
                            s32 tc6;
                            if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC))
                            {
                                tc6 = base->trophy_count;
                            } else {
                                tc6 = *gmMainLib_8015CC90();
                            }
                            display->selectedIdx = (s16) (tc6 - 1);
                        }
                        {
                            s32 tc7;
                            if ((gm_8016B498() != 0) || (gm_801A4310() == 0xC))
                            {
                                tc7 = base->trophy_count;
                            } else {
                                tc7 = *gmMainLib_8015CC90();
                            }
                            if (tc7 > 3) {
                                s16 prev_trophy = display->selectedIdx;
                                if ((prev_trophy - 1) < 0) {
                                    s32 tc8;
                                    s32 calc_idx;
                                    if ((gm_8016B498() != 0) ||
                                        (gm_801A4310() == 0xC))
                                    {
                                        tc8 = base->trophy_count;
                                    } else {
                                        tc8 = *gmMainLib_8015CC90();
                                    }
                                    calc_idx = tc8 + display->selectedIdx;
                                    entry = display->first_entry->prev;
                                    trophy_id =
                                        Toy_sbss_804D6EDC[calc_idx - 1];
                                    result = Toy_8030813C(trophy_id, calc_idx);
                                    archive = entry->archive;
                                    if (archive != NULL) {
                                        lbArchive_80016EFC(archive);
                                        entry->archive = NULL;
                                    }
                                    entry->archive_name = result + 4;
                                    entry->symbol_name = result + 0x24;
                                    entry->trophy_id = trophy_id;
                                    entry->archive = lbArchive_LoadSymbols(
                                        entry->archive_name, &spD8,
                                        entry->symbol_name, 0);
                                } else {
                                    entry = display->first_entry->prev;
                                    trophy_id =
                                        Toy_sbss_804D6EDC[prev_trophy - 1];
                                    result = Toy_8030813C(
                                        trophy_id,
                                        (s32) &Toy_sbss_804D6EDC[prev_trophy]);
                                    archive = entry->archive;
                                    if (archive != NULL) {
                                        lbArchive_80016EFC(archive);
                                        entry->archive = NULL;
                                    }
                                    entry->archive_name = result + 4;
                                    entry->symbol_name = result + 0x24;
                                    entry->trophy_id = trophy_id;
                                    entry->archive = lbArchive_LoadSymbols(
                                        entry->archive_name, &spD4,
                                        entry->symbol_name, 0);
                                }
                                archive = display->last_entry->archive;
                                if (archive != NULL) {
                                    lbArchive_80016EFC(archive);
                                    display->last_entry->archive = NULL;
                                }
                                display->selected_entry =
                                    display->selected_entry->prev;
                                display->first_entry =
                                    display->first_entry->prev;
                                display->last_entry =
                                    display->last_entry->prev;
                            } else {
                                display->selected_entry =
                                    display->selected_entry->prev;
                            }
                        }
                    }
                    _Toy_80307828(0);
                    state->x58 = 0x95E;
                    Toy_803087F4(display->selected_entry);
                    state->x60 = 0x14;
                    goto after_trophy_cycle;
                }
                goto after_trophy_cycle;
            }

        after_trophy_cycle:
            trigger = Toy_80305B88();
            if (trigger & 0x1000) {
                lbAudioAx_80024030(2);
                state->x58 = 0;
                M2C_FIELD(ed4, s32*, 0x10) = M2C_FIELD(ed4, s32*, 0x10) + 1;
                if (M2C_FIELD(ed4, s32*, 0x10) == 6) {
                    M2C_FIELD(ed4, s32*, 0x10) = 0;
                }
                Toy_80306D70(M2C_FIELD(ed4, s32*, 0x10));
                _Toy_803075E8(M2C_FIELD(ed4, s32*, 0x10));
            }

            trigger = Toy_80305B88();
            if (trigger & 0x10) {
                void* ed4_2;
                _Toy_80307828(0);
                ed4_2 = Toy_sbss_804D6ED4;
                M2C_FIELD(ed4_2, s32*, 0x10) = 0;
                Toy_80306D70(M2C_FIELD(ed4_2, s32*, 0x10));
                _Toy_803075E8(M2C_FIELD(ed4_2, s32*, 0x10));
                anim->x11 = 0;
                anim->x10 = 0;
                anim->x0E = 1;
            }

            {
                HSD_JObjSetFlagsAll(anim->jobj[0], JOBJ_HIDDEN);
                HSD_JObjSetFlagsAll(anim->jobj[1], JOBJ_HIDDEN);
            }

            _Toy_8030715C(state->x50, state->x54);
            state->x38 = state->x30;
            state->x3C = state->x34;
            state->x48 = state->x40;
            state->x4C = state->x44;
            break;
        }
    }
}

/* 3FE5E8 */ char Toy_str_ScMenFigure_cam_int1_camera[] =
    "ScMenFigure_cam_int1_camera";

/* 3FE604 */ static HSD_WObjDesc _Toy_803FE604 = {
    NULL,
    { 0.0f, 0.0f, 38.0f },
    NULL,
};
/* 3FE618 */ static HSD_WObjDesc _Toy_803FE618 = {
    NULL,
    { 8.0f, 4.0f, 0.0f },
    NULL,
};
/* 3FE62C */ static HSD_CameraDescPerspective _Toy_803FE62C = {
    NULL,
    0,
    PROJ_PERSPECTIVE,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &_Toy_803FE604,
    &_Toy_803FE618,
    0.0f,
    NULL,
    0.1f,
    (float) 0x8000,
    40.0f,
    913.0f / 750.0f,
};

/* 3FE664 */ static HSD_WObjDesc _Toy_803FE664 = {
    NULL,
    { 0.0f, 0.0f, 50.0f },
    NULL,
};
/* 3FE678 */ static HSD_WObjDesc _Toy_803FE678 = {
    NULL,
    { 0.0f, 0.0f, 0.0f },
    NULL,
};
/* 3FE68C */ static HSD_CameraDescPerspective _Toy_803FE68C = {
    NULL,
    0,
    PROJ_PERSPECTIVE,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &_Toy_803FE664,
    &_Toy_803FE678,
    0.0f,
    NULL,
    0.1f,
    (float) 0x8000,
    40.0f,
    913.0f / 750.0f,
};

void _Toy_8030FA50(void)
{
    UNUSED u8 framepad[16];
    Vec3 eye;
    Mtx mtx;
    HSD_GObj* gobj;
    HSD_CameraDescPerspective* cam_desc;
    HSD_CObj* cobj;
    void** state;
    f32 frustum_top;
    f32 frustum_bottom;
    f32 frustum_far;
    f32 frustum_near;
    u8 kind;

    PAD_STACK(48);

    {
        /// @todo likely inline where #Toy_str_ScMenFigure_cam_int1_camera
        ///       is declared
        ToyED8Data* ed8 = Toy_sbss_804D6ED8;
        state = (void**) _Toy_sbss_804D6E68;
        cam_desc = HSD_ArchiveGetPublicAddress(
            ed8->archive, Toy_str_ScMenFigure_cam_int1_camera);
    }

    /* Screen camera (offset 0x14) */
    state[5] = GObj_Create(1U, 2U, 0U);
    HSD_SObjLib_803A55DC(state[5], 0x280, 0x1E0, 0);
    gobj = state[5];
    gobj->gxlink_prios = 0x0004000000000000ULL;

    /* Main CObj (offset 0x00) */
    state[0] = GObj_Create(1U, 2U, 0U);
    cobj = lb_80013B14(cam_desc);
    kind = HSD_GObj_804D784B;
    HSD_GObjObject_80390A70(state[0], kind, cobj);
    GObj_SetupGXLinkMax(state[0], Toy_80306954, 0U);
    gobj = state[0];
    gobj->gxlink_prios = 0x1048000000000000ULL;

    /* Screen2 (offset 0x10) */
    state[4] = GObj_Create(1U, 2U, 0U);
    HSD_SObjLib_803A55DC(state[4], 0x280, 0x1E0, 0);
    gobj = state[4];
    gobj->gxlink_prios = 0x0100000000000000ULL;

    /* Frustum camera (offset 0x08) */
    state[2] = GObj_Create(1U, 2U, 0U);
    cobj = lb_80013B14(&_Toy_803FE62C);
    frustum_top = 0.049584f;
    frustum_bottom = -0.035585f;
    frustum_far = 0.076839;
    frustum_near = -0.026839f;
    HSD_CObjSetFrustum(cobj, frustum_top, frustum_bottom, frustum_near,
                       frustum_far);
    kind = HSD_GObj_804D784B;
    HSD_GObjObject_80390A70(state[2], kind, cobj);
    GObj_SetupGXLinkMax(state[2], (GObj_RenderFunc) (Event) Toy_803068E0, 0U);
    gobj = state[2];
    gobj->gxlink_prios = 0x0E80000000000000ULL;

    if ((s8) _Toy_sbss_804D6EA2 != 0) {
        _Toy_sbss_804D6E60 = 0;
        DevText_SetXY(_Toy_sbss_804D6E9C, 0x21C, 0x82);
        HSD_GObj_SetupProc(state[2], _Toy_8030B530, 0U);
    } else if ((s8) _Toy_sbss_804D6E50 != 0) {
        HSD_GObj_SetupProc(state[2], _Toy_8030E110, 0U);
    } else {
        HSD_GObj_SetupProc(state[2], _Toy_80309404, 0U);
    }

    HSD_GObj_80390CD4(state[2]);
    ((Toy6E68*) state)->x61 = 0;
    ((Toy6E68*) state)->x60 = 4;
    _Toy_80307828(0);
    ((Toy6E68*) _Toy_sbss_804D6E68)->x58 = 0x95E;

    /* Camera2 (offset 0x04) */
    state[1] = GObj_Create(1U, 2U, 0U);
    cobj = lb_80013B14(&_Toy_803FE68C);
    kind = HSD_GObj_804D784B;
    HSD_GObjObject_80390A70(state[1], kind, cobj);
    GObj_SetupGXLinkMax(state[1], Toy_803068E0, 0U);
    gobj = state[1];
    gobj->gxlink_prios = 0x8000000000000000ULL;

    _Toy_sbss_804D6E70 =
        HSD_SisLib_803A611C(0, state[1], 0xBU, 0xCU, 0U, 0x3FU, 0U, 0U);

    HSD_CObjGetEyePosition(cobj, &eye);
    eye.y = 0.0f;
    eye.x = 0.0f;
    eye.z = HSD_CObjGetEyeDistance(cobj);
    MTXRotRad(mtx, 'y', 0.57595867f);
    PSMTXMultVecSR(mtx, &eye, &eye);
    HSD_CObjSetEyePosition(cobj, &eye);

    /* Light camera (offset 0x0C) */
    state[3] = GObj_Create(1U, 2U, 0U);
    cobj = lb_80013B14(cam_desc);
    kind = HSD_GObj_804D784B;
    HSD_GObjObject_80390A70(state[3], kind, cobj);
    GObj_SetupGXLinkMax(state[3], HSD_GObj_803910D8, 0U);
    gobj = state[3];
    gobj->gxlink_prios = 0x4000000000000000ULL;

    _Toy_sbss_804D6E74 =
        HSD_SisLib_803A611C(3, state[3], 0xCU, 0xBU, 0U, 0x3EU, 0U, 0U);
    _Toy_sbss_804D6E78 =
        HSD_SisLib_803A611C(3, state[3], 0xDU, 0xBU, 0U, 0x3EU, 0U, 0U);
    _Toy_sbss_804D6E7C =
        HSD_SisLib_803A611C(3, state[3], 0xEU, 0xBU, 0U, 0x3EU, 0U, 0U);

    if ((s8) _Toy_sbss_804D6E50 != 0) {
        gobj = state[0];
        gobj->gxlink_prios = 0;
        gobj = state[1];
        gobj->gxlink_prios = 0;
        gobj = state[3];
        gobj->gxlink_prios = 0;
        gobj = state[4];
        gobj->gxlink_prios = 0;
        gobj = state[5];
        gobj->gxlink_prios = 0;
        gobj = state[2];
        gobj->gxlink_prios = 0x02A0000000000000ULL;
    }
}

void _Toy_8030FE48(void* arg0, s32 arg1)
{
    u8* toy = (u8*) &_Toy_804A26B8;
    u8* data = arg0;
    u8* sel = toy + 0x3E8;
    s32 arg1_copy = arg1;
    s32 var_r26 = 0;
    s16* ptr;
    s32 count;
    char* result;
    s16 trophyIdx;
    void* sym;
    void* sym2;
    void* zero;
    s32 start;
    u8* zero_entry;
    s32 remaining;
    s32 var_r7;
    PAD_STACK(8);

    ptr = &_Toy_sbss_804D6E64[(s8) toy[0x195]];
    *(s16*) (data + 0x154) = *(s16*) sel;

    goto loop_check;

loop_body:
    if (*(s16*) (toy + 0x3EA) == *ptr) {
        *(s16*) (data + 0x154) = (s16) var_r26;
        *(s16*) sel = *(s16*) (data + 0x154);
        goto loop_done;
    }

    ptr = (s16*) ((u8*) ptr + 6);
    var_r26 += 1;

loop_check:
    if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
        count = *(s16*) (toy + 0x3EC);
    } else {
        count = *gmMainLib_8015CC90();
    }

    if (var_r26 < count) {
        goto loop_body;
    }

loop_done:
    if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
        count = *(s16*) (toy + 0x3EC);
    } else {
        count = *gmMainLib_8015CC90();
    }

    var_r7 = count;
    if (count > 3) {
        *(s8*) (data + 0x157) = 3;
        var_r7 = 0xD;
    } else {
        *(s8*) (data + 0x157) = (s8) count;
    }

    if (arg1_copy == 0) {
        s32 last = var_r7 - 1;
        u8* entry = data;
        s32 i;
        u8* last_entry = data + last * 0x18;
        for (i = 0; i < var_r7; i++) {
            if (i == 0) {
                *(void**) (entry + 0x00) = last_entry;
            } else {
                *(void**) (entry + 0x00) = (void*) (data + (i - 1) * 0x18);
            }
            if (i == last) {
                *(void**) (entry + 0x04) = (void*) data;
            } else {
                *(void**) (entry + 0x04) = (void*) (data + (i + 1) * 0x18);
            }
            entry += 0x18;
        }
    }

    zero = NULL;
    start = 8;
    *(void**) (data + 0x14) = zero;
    *(void**) (data + 0x2C) = zero;
    *(void**) (data + 0x44) = zero;
    *(void**) (data + 0x5C) = zero;
    *(void**) (data + 0x74) = zero;
    *(void**) (data + 0x8C) = zero;
    *(void**) (data + 0xA4) = zero;
    *(void**) (data + 0xBC) = zero;
    goto clear_archive_setup;

clear_archive_loop:
    remaining = 0xD - start;
    if (start < 0xD) {
        do {
            *(void**) (zero_entry + 0x14) = zero;
            zero_entry += 0x18;
            remaining -= 1;
        } while (remaining != 0);
    }

    if ((s8) * (u8*) (data + 0x157) == var_r7) {
        s32 j = 0;
        s32 offset = 0;
        u8* entry = data;

        for (; j < (s8) * (u8*) (data + 0x157);
             j += 1, offset += 2, entry += 0x18)
        {
            if (j == *(s16*) (data + 0x154)) {
                trophyIdx = M2C_FIELD(Toy_sbss_804D6EDC, s16*, offset);
                result = Toy_8030813C(trophyIdx, trophyIdx);
                if (*(HSD_Archive**) (entry + 0x14) != NULL) {
                    lbArchive_80016EFC(*(HSD_Archive**) (entry + 0x14));
                    *(HSD_Archive**) (entry + 0x14) = NULL;
                }

                *(char**) (entry + 0x08) = result + 4;
                *(char**) (entry + 0x0C) = result + 0x24;
                *(s16*) (entry + 0x10) = trophyIdx;
                *(HSD_Archive**) (entry + 0x14) =
                    lbArchive_LoadSymbols(*(char**) (entry + 0x08), &sym,
                                          *(char**) (entry + 0x0C), 0);
            } else {
                trophyIdx = M2C_FIELD(Toy_sbss_804D6EDC, s16*, offset);
                result = Toy_8030813C(trophyIdx, trophyIdx);
                if (*(HSD_Archive**) (entry + 0x14) != NULL) {
                    lbArchive_80016EFC(*(HSD_Archive**) (entry + 0x14));
                    *(HSD_Archive**) (entry + 0x14) = NULL;
                }

                *(char**) (entry + 0x08) = result + 4;
                *(char**) (entry + 0x0C) = result + 0x24;
                *(s16*) (entry + 0x10) = trophyIdx;
            }
        }

        *(void**) (data + 0x140) =
            (void*) (data + *(s16*) (data + 0x154) * 0x18);
        *(void**) (data + 0x138) = data;
        *(void**) (data + 0x13C) =
            (void*) (data + ((s8) * (u8*) (data + 0x157) - 1) * 0x18);
        return;
    }

    {
        s32 startIdx;
        s32 prevIdx;
        s32 loopCount;
        u8* cur;

        prevIdx = *(s16*) (data + 0x154) - 1;
        if (prevIdx < 0) {
            s32 tcount;
            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                tcount = *(s16*) (toy + 0x3EC);
            } else {
                tcount = *gmMainLib_8015CC90();
            }
            startIdx = tcount + *(s16*) (data + 0x154);
            startIdx -= 1;
        } else {
            startIdx = prevIdx;
        }

        *(void**) (data + 0x140) = data;
        loopCount = 0;
        *(void**) (data + 0x138) = *(void**) (*(u8**) (data + 0x140) + 0x00);
        *(void**) (data + 0x13C) = *(void**) (*(u8**) (data + 0x140) + 0x04);
        cur = *(u8**) (data + 0x138);

        while (loopCount < (s8) * (u8*) (data + 0x157)) {
            s32 tcount2;

            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                tcount2 = *(s16*) (toy + 0x3EC);
            } else {
                tcount2 = *gmMainLib_8015CC90();
            }

            if (startIdx >= tcount2) {
                startIdx = 0;
            }

            if (startIdx == *(s16*) (data + 0x154)) {
                trophyIdx = Toy_sbss_804D6EDC[startIdx];
                result = Toy_8030813C(trophyIdx, trophyIdx);
                if (*(HSD_Archive**) (cur + 0x14) != NULL) {
                    lbArchive_80016EFC(*(HSD_Archive**) (cur + 0x14));
                    *(HSD_Archive**) (cur + 0x14) = NULL;
                }

                *(char**) (cur + 0x08) = result + 4;
                *(char**) (cur + 0x0C) = result + 0x24;
                *(s16*) (cur + 0x10) = trophyIdx;
                *(HSD_Archive**) (cur + 0x14) = lbArchive_LoadSymbols(
                    *(char**) (cur + 0x08), &sym2, *(char**) (cur + 0x0C), 0);
            } else {
                trophyIdx = Toy_sbss_804D6EDC[startIdx];
                result = Toy_8030813C(trophyIdx, trophyIdx);
                if (*(HSD_Archive**) (cur + 0x14) != NULL) {
                    lbArchive_80016EFC(*(HSD_Archive**) (cur + 0x14));
                    *(HSD_Archive**) (cur + 0x14) = NULL;
                }

                *(char**) (cur + 0x08) = result + 4;
                *(char**) (cur + 0x0C) = result + 0x24;
                *(s16*) (cur + 0x10) = trophyIdx;
            }

            cur = *(u8**) (cur + 0x04);
            startIdx += 1;
            loopCount += 1;
        }
    }
    return;

clear_archive_setup:
    zero_entry = data + start * 0x18;
    goto clear_archive_loop;
}

void _Toy_803102C4(s8 arg0)
{
    _Toy_sbss_804D6E6C->x4 = arg0;
}

/// @todo .data order hack
static void order_data_9AC(void)
{
    /* +9AC */ (void) "*** Error : Didn't Add Ligth!(call otoguro)\n";
    /* +9DC */ (void) "tyInitModelTbl";
    /* +9EC */ (void) "tyInitModelDTbl";
    /* +9FC */ (void) "tyModelSortTbl";
    /* +A0C */ (void) "tyExpDifferentTbl";
    /* +A20 */ (void) "tyNoGetUsTbl";
    /* +A30 */ (void) "tyDisplayModelTbl";
    /* +A44 */ (void) "tyDisplayModelUsTbl";
}

// static void inlineA0(void)
// {
//     if (_Toy_sbss_804D6ED0 == NULL) {
//         _Toy_sbss_804D6ED0 = lbArchive_LoadSymbols(
//             getDataiDatFilename(), &_Toy_sbss_804D6EC4, "tyInitModelTbl",
//             &_Toy_sbss_804D6EC0, "tyModelSortTbl", &_Toy_sbss_804D6EBC,
//             "tyModelSortTbl", &_Toy_sbss_804D6EB8, "tyExpDifferentTbl",
//             &_Toy_sbss_804D6EB4, "tyNoGetUsTbl", &Toy_sbss_804D6EB0,
//             "tyDisplayModelTbl", &Toy_sbss_804D6EAC, "tyDisplayModelUsTbl",
//             NULL);
//     }
// }

void Toy_803102D0(void)
{
    if (_Toy_sbss_804D6ECC == NULL) {
        _Toy_sbss_804D6ECC = lbArchive_LoadSymbols(
            "TyDataf.dat", &_Toy_sbss_804D6EA8, "tyModelFileTbl",
            &_Toy_sbss_804D6EA4, "tyModelFileUsTbl", NULL);
    }
}

void Toy_80310324(void)
{
    s16 idx;
    ToyGlobalsS_* tg3;
    s32 i;
    Toy26B8* toy;
    ToyGlobalsS_* tg;
    ToyGlobalsS_* tg2;
    ToyGlobalsS_* tg4;
    ToyGlobalsS_* tg5;
    ToyGlobalsS_* tg6;
    ToySubStructS_* sub;
    UNK_T syms[6];
    s32 one;
    s32 var_r0;
    HSD_SObj* sobj;
    HSD_GObj* gobj;
    u16* flags;
    f32 two;

    toy = (void*) &_Toy_804A26B8;
    tg = (ToyGlobalsS_*) Toy_sbss_804D6ED8;

    _Toy_8030663C();
    Toy_803067BC(toy->x195, toy->x196);

    if (tg->x50 == NULL) {
        tg->x50 = lbArchive_LoadSymbols(
            lbLang_IsSavedLanguageJP() ? "TyMnView.dat" : "TyMnView.usd",
            &syms[5], _Toy_803FDEA0[0], NULL);
    }

    memzero(_Toy_sbss_804D6E68, 0x64);
    _Toy_8030FA50();
    memzero(Toy_sbss_804D6ED4, 0xE4);
    Toy_80306D70(0);
    _Toy_80307018();

    if ((tg2 = (ToyGlobalsS_*) Toy_sbss_804D6ED8)->x54 == NULL) {
        tg2->x54 = lbArchive_LoadSymbols(
            "TyMnBg.dat", &syms[2], _Toy_803FE038[0], &syms[3],
            _Toy_803FE038[1], &syms[4], _Toy_803FE038[2], 0);

        tg2->x8 = GObj_Create(4, 5, 0);
        GObj_SetupGXLink(tg2->x8, HSD_SObjLib_803A49E0, 0x32, 0);

        i = 0;
        two = 2.0f;
        one = 1;
        do {
            sobj = HSD_SObjLib_803A477C(tg2->x8, syms[i + 2], 0, 0, 0x80, 0);
            *(f32*) ((char*) sobj + 0x1C) = two;
            i += 1;
            *(f32*) ((char*) sobj + 0x20) = two;
            *(s32*) ((char*) sobj + 0x40) = one;
        } while (i < 3);
    }

    _Toy_803075E8(0);
    Toy_80307470(0);
    _Toy_803078E4();

    gobj = ((ToyGlobalsS_*) Toy_sbss_804D6ED8)->xC;
    gobj = *(HSD_GObj**) ((char*) gobj + 0x28);
    while (gobj != NULL) {
        *(s32*) ((char*) gobj + 0x40) = 9;
        gobj = *(HSD_GObj**) ((char*) gobj + 0x4);
    }

    if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
        var_r0 = toy->trophy_count;
    } else {
        var_r0 = *gmMainLib_8015CC90();
    }

    if (var_r0 != 0) {
        memzero(&toy->anim, 0x14);
        _Toy_8030FE48(Toy_sbss_804D6EE0, 0);
        tg6 = (ToyGlobalsS_*) Toy_sbss_804D6EE0;
        Toy_803087F4(tg6->x140);

        tg6 = (ToyGlobalsS_*) Toy_sbss_804D6EE0;
        idx = Toy_sbss_804D6EDC[tg6->x154];

        if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
            flags = toy->trophy_flags;
        } else {
            flags = gmMainLib_8015CC78();
        }

        if (flags[idx] & 0x8000) {
            tg6 = (ToyGlobalsS_*) Toy_sbss_804D6EE0;
            idx = Toy_sbss_804D6EDC[tg6->x154];

            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                flags = toy->trophy_flags;
            } else {
                flags = gmMainLib_8015CC78();
            }

            flags += idx;
            *flags ^= 0x8000;
        }

        tg6 = (ToyGlobalsS_*) Toy_sbss_804D6EE0;
        sub = tg6->x140;
        _Toy_803084A0(sub->x10);

        tg6 = (ToyGlobalsS_*) Toy_sbss_804D6EE0;
        sub = tg6->x140;
        Toy_803083D8(tg->x30, sub->x10);

        tg3 = (ToyGlobalsS_*) _Toy_sbss_804D6E6C;
        tg3->x0 = GObj_Create(6, 7, 0);
        GObj_SetupGXLink(tg3->x0, _Toy_80312050, 0x39, 0);
        tg3->x4 = 1;
    }

    _Toy_80307828(0);

    tg5 = (ToyGlobalsS_*) _Toy_sbss_804D6E68;
    tg5->x58 = 0x95E;

    _Toy_8030715C(0.0f, 0.0f);

    tg4 = (ToyGlobalsS_*) Toy_sbss_804D6ED4;
    tg4->x10 = 0;
    Toy_80306D70(tg4->x10);
    _Toy_803075E8(tg4->x10);
    HSD_PadRenewStatus();
}

void Toy_80310660(s32 arg0)
{
    s32 idx;
    s32 arg;
    u8* state;
    void** ty31;
    TyCleanupObj* ty28;
    u8* ty27;
    void* ty26;
    ToyGlobalsS_* ty25;
    struct tyLightData* ty30;

    state = (u8*) &_Toy_804A26B8;
    arg = arg0;
    ty27 = state + 0x3F0;
    ty31 = (void**) _Toy_sbss_804D6E68;
    ty28 = (TyCleanupObj*) Toy_sbss_804D6ED4;
    ty26 = _Toy_sbss_804D6E6C;
    ty25 = (ToyGlobalsS_*) Toy_sbss_804D6EE0;
    ty30 = (struct tyLightData*) Toy_sbss_804D6ED8;

    if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
        idx = *(s16*) (state + 0x3EC);
    } else {
        idx = *gmMainLib_8015CC90();
    }

    if (idx != 0) {
        u16* ptr;
        idx = Toy_sbss_804D6EDC[ty25->x154];

        if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
            ptr = (u16*) (state + 0x19E);
        } else {
            ptr = gmMainLib_8015CC78();
        }

        if (ptr[idx] & 0x8000) {
            idx = Toy_sbss_804D6EDC[ty25->x154];

            if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
                ptr = (u16*) (state + 0x19E);
            } else {
                ptr = gmMainLib_8015CC78();
            }
            ptr += idx;
            *ptr ^= 0x8000;
        }

        *(s16*) (state + 0x3E8) = ty25->x154;
        *(s16*) (state + 0x3EA) = ty25->x140->x10;
    }

    if (arg != 0) {
        Ty25Entry* loopPtr;
        s32 count;

        HSD_SisLib_803A5E70();
        ty25->x150 = NULL;
        ty25->x14C = NULL;
        ty25->x148 = NULL;
        ty25->x144 = NULL;

        if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
            idx = *(s16*) (state + 0x3EC);
        } else {
            idx = *gmMainLib_8015CC90();
        }

        if (idx != 0) {
            loopPtr = (Ty25Entry*) ty25;
            count = 0;
            arg = 0;
            do {
                if (loopPtr->x14 != NULL) {
                    lbArchive_80016EFC(loopPtr->x14);
                    loopPtr->x14 = (void*) arg;
                }
                count += 1;
                loopPtr += 1;
            } while (count < 0xD);
        }

        if (Toy_sbss_804D6EC8 != NULL) {
            lbArchive_80016EFC(Toy_sbss_804D6EC8);
            Toy_sbss_804D6EC8 = NULL;
        }

        if (ty28->xC != NULL) {
            lbArchive_80016EFC(ty28->xC);
            ty28->xC = NULL;
        }

        if (ty30->x58 != NULL) {
            lbArchive_80016EFC(ty30->x58);
            arg = 0;
            ty30->x58 = (void*) arg;
            if (ty30->x0C != NULL) {
                HSD_GObjPLink_80390228(ty30->x0C);
                ty30->x0C = (void*) arg;
            }
        }

        if (*(void**) ty27 != NULL) {
            HSD_GObjPLink_80390228(*(void**) ty27);
            *(void**) ty27 = NULL;
            *(void**) (ty27 + 0x8) = NULL;
            *(void**) (ty27 + 0x4) = NULL;
        }

        if (*(void**) ty26 != NULL) {
            HSD_GObjPLink_80390228(*(void**) ty26);
            *(void**) ty26 = NULL;
        }

        if (ty28->x0 != NULL) {
            HSD_GObjPLink_80390228(ty28->x0);
            ty28->x0 = NULL;
            ty28->x10 = NULL;
        }

        if (ty28->x4 != NULL) {
            HSD_GObjProc_8038FED4(ty28->x4);
            HSD_GObjPLink_80390228(ty28->x4);
            ty28->x4 = NULL;
        }

        if (ty28->x8 != NULL) {
            HSD_GObjPLink_80390228(ty28->x8);
            ty28->x8 = NULL;
            HSD_FogSet(NULL);
        }

        if (ty30->x0C != NULL) {
            HSD_GObjPLink_80390228(ty30->x0C);
            ty30->x0C = NULL;
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

void _Toy_803109A0(s32 arg0, s32 arg1, s32 arg2)
{
    ToyTable table;
    char buf[16];
    s32 idx;
    s32 target;

    target = arg0;

    /* Copy table from _Toy_803B8910 to stack */
    table = *(ToyTable*) _Toy_803B8910;

    /* Search for matching entry using pointer walk */
    {
        ToyEntry* p = table.entries;
        idx = 0;
        if (target == p->id) {
            goto found;
        }
        idx = 1;
        if (target == (++p)->id) {
            goto found;
        }
        idx = 2;
        if (target == (++p)->id) {
            goto found;
        }
        idx = 3;
        if (target == (++p)->id) {
            goto found;
        }
        idx = 4;
        if (target == (++p)->id) {
            goto found;
        }
        idx = 5;
        if (target == (++p)->id) {
            goto found;
        }
        idx = 6;
        if (target == (++p)->id) {
            goto found;
        }
        idx = 7;
        if (target == (++p)->id) {
            goto found;
        }
        idx = 8;
        if (target == (++p)->id) {
            goto found;
        }
        idx = 9;
    }

found:
    if (arg2 != 0) {
        DevText_StoreColorIndex(_Toy_sbss_804D6E98, 1);
    } else {
        DevText_StoreColorIndex(_Toy_sbss_804D6E98, 0);
    }

    if (target == 8) {
        s32 ret = Toy_80304B94(target);
        sprintf(buf, "Rea_%c %3d/%3d", table.entries[idx].value_byte, arg1,
                ret);
    } else {
        s32 ret = Toy_80304B94(target);
        sprintf(buf, "Rea_%c %3d/%3d\n", table.entries[idx].value_byte, arg1,
                ret);
    }
    DevText_Printf(_Toy_sbss_804D6E98, buf);
}

void _Toy_80310B48(HSD_GObj* gobj)
{
    ToyParamEditor* editor;
    f32 stickX;
    f32 stickY;
    f32 absVal;
    f32 dirX;
    f32 dirY;
    u32 buttons;
    s32 changed;
    s32 i;
    s16* valptr;

    PAD_STACK(88);

    changed = 0;
    editor = (ToyParamEditor*) _Toy_sbss_804D6E5C;

    for (i = 0; i < 4; i++) {
        if ((stickX = HSD_PadCopyStatus[(u8) i].nml_stickX) < 0.0F) {
            absVal = -stickX;
        } else {
            absVal = stickX;
        }
        if (absVal > 0.1F) {
            break;
        }
    }

    for (i = 0; i < 4; i++) {
        if ((stickY = HSD_PadCopyStatus[(u8) i].nml_stickY) < 0.0F) {
            absVal = -stickY;
        } else {
            absVal = stickY;
        }
        if (absVal > 0.1F) {
            gm_801677E8(i);
            break;
        }
    }

    if (stickX < -0.6f) {
        dirX = 1.0f;
        dirY = 0.0f;
    } else if (stickX > 0.6f) {
        dirX = -1.0f;
        dirY = 0.0f;
    } else if (stickY < -0.6f) {
        dirX = 0.0f;
        dirY = 1.0f;
    } else if (stickY > 0.6f) {
        dirX = 0.0f;
        dirY = -1.0f;
    } else {
        dirX = 0.0f;
        dirY = 0.0f;
        editor->repeat_delay = 0;
    }

    if ((s8) editor->repeat_delay != 0) {
        editor->repeat_delay = (u8) (editor->repeat_delay - 1);
        return;
    }

    buttons = Toy_80305B88();

    if (buttons & 0x200) {
        lbAudioAx_80024030(0);
        HSD_GObjPLink_80390228(gobj);
        editor->gobj = NULL;
        ((TyModeState*) Toy_804A284C)->x4 = 1;
        return;
    }

    buttons = Toy_80305B88();

    if (buttons & 0x1100) {
        lbAudioAx_80024030(1);
        Toy_80311960();
        valptr = (s16*) editor;
        {
            s32 slot;

            slot = 0;
            do {
                if (valptr[3] != 0) {
                    Toy_80305918(slot, 0, 0);
                    buttons = Toy_80305B88();
                    if (buttons & 0x1000) {
                        _Toy_803053C4(slot, (s32) valptr[3], 0);
                    } else {
                        _Toy_803053C4(slot, (s32) valptr[3], 1);
                    }
                } else if (slot == 2) {
                    Toy_80305918(slot, 0, 0);
                }
                slot += 1;
                valptr += 1;
            } while (slot < 9);
        }
        Toy_80305918(0, 1, 0);
        Toy_80305918(1, 1, 0);
        Toy_80305918(8, 1, 0);
        Toy_80305918(3, 1, 0);
        DevText_HideBackground(_Toy_sbss_804D6E98);
        DevText_HideText(_Toy_sbss_804D6E98);
        Toy_80310324();
        HSD_GObjPLink_80390228(gobj);
        editor->gobj = NULL;
        return;
    }

    if (!(dirX > 0.0f)) {
        buttons = Toy_80305C44();
        if (!(buttons & 0x800)) {
            buttons = Toy_80305B88();
            if (!(buttons & 1)) {
                goto skip_increment;
            }
        }
    }

    lbAudioAx_80024030(2);
    editor->values[(s8) editor->selected_slot] =
        (s16) (editor->values[(s8) editor->selected_slot] + 1);
    if ((s16) editor->values[(s8) editor->selected_slot] >
        Toy_80304B94((s32) (s8) editor->selected_slot))
    {
        editor->values[(s8) editor->selected_slot] =
            (s16) Toy_80304B94((s32) (s8) editor->selected_slot);
    }
    editor->repeat_delay = 4;
    changed = 1;

skip_increment:

    if (!(dirX < 0.0f)) {
        buttons = Toy_80305C44();
        if (!(buttons & 0x400)) {
            buttons = Toy_80305B88();
            if (!(buttons & 2)) {
                goto skip_decrement;
            }
        }
    }

    lbAudioAx_80024030(2);
    editor->values[(s8) editor->selected_slot] =
        (s16) (editor->values[(s8) editor->selected_slot] - 1);
    if ((s16) editor->values[(s8) editor->selected_slot] < 0) {
        editor->values[(s8) editor->selected_slot] = 0;
    }
    editor->repeat_delay = 4;
    changed = 1;

skip_decrement:

    if (dirX == 0.0f && dirY != 0.0f) {
        lbAudioAx_80024030(2);
        editor->selected_slot =
            (u8) (s32) ((f32) (s8) editor->selected_slot + dirY);
        if ((s8) editor->selected_slot < 0) {
            editor->selected_slot = 0;
        }
        if ((s8) editor->selected_slot > 9) {
            editor->selected_slot = 9;
        }
        editor->repeat_delay = 8;
        changed = 1;
    }

    if (changed != 0) {
        DevText_Erase(_Toy_sbss_804D6E98);
        DevText_SetCursorXY(_Toy_sbss_804D6E98, 0, 0);
        i = 0;
        do {
            if (i == (s8) editor->selected_slot) {
                _Toy_803109A0(i, (s32) editor->values[i], 1);
            } else {
                _Toy_803109A0(i, (s32) editor->values[i], 0);
            }
            i += 1;
        } while (i < 9);
    }
}

void _Toy_803114E8(void)
{
    GXColor color;
    s32 pad[0x20]; /* Force larger stack frame */
    void** data;
    s32 i;

    (void) pad;

    _Toy_sbss_804D6E5C = HSD_MemAlloc(0x18);
    data = _Toy_sbss_804D6E5C;

    _Toy_sbss_804D6E98 =
        DevText_Create(1, 0x28, 0x28, 0xE, 9, _Toy_devtext_buf_804A2750);

    if (_Toy_sbss_804D6E98 != NULL) {
        HSD_GObj* gobj = DevText_GetGObj();
        color = _Toy_color_4080D060_0;
        DevText_Show(gobj, _Toy_sbss_804D6E98);
        DevText_HideCursor(_Toy_sbss_804D6E98);
        DevText_80302AC0(_Toy_sbss_804D6E98);
        DevText_SetBGColor(_Toy_sbss_804D6E98, *(GXColor*) &color);
        DevText_SetScale(_Toy_sbss_804D6E98, 12.0f, 18.0f);
        DevText_Erase(_Toy_sbss_804D6E98);
        DevText_SetCursorXY(_Toy_sbss_804D6E98, 0, 0);
        DevText_StoreColorIndex(_Toy_sbss_804D6E98, 0);
        DevText_SetTextColor(_Toy_sbss_804D6E98,
                             *(GXColor*) &_Toy_color_E2E2E2FF);
        DevText_StoreColorIndex(_Toy_sbss_804D6E98, 1);
        DevText_SetTextColor(_Toy_sbss_804D6E98,
                             *(GXColor*) &_Toy_color_FF8020FF);

        i = 0;
        do {
            if (i == 0) {
                _Toy_803109A0(i, 0, 1);
            } else {
                _Toy_803109A0(i, 0, 0);
            }
            i++;
        } while (i < 9);

        memzero(data, 0x18);
        *data = GObj_Create(0, 0, 0);
        HSD_GObj_SetupProc(*data, (void (*)(HSD_GObj*)) _Toy_80310B48, 0);
        HSD_GObj_80390CD4(*data);
    } else {
        OSReport("*** Couldn't Open Debug Window2!\n");
    }
}

void Toy_80311680(void)
{
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
    Toy_80311960();
    var_r28 = 0;
    do {
        var_r30 = _Toy_sbss_804D6EB4;
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
            temp_r0_2 = (s32) Toy_803060BC(var_r28, 6);
            if ((u32) temp_r0_2 > 1U && temp_r0_2 != 8 && temp_r0_2 != 3) {
                *var_r29 |= 0x4000;
            }
        }
        var_r28++;
        var_r29++;
    } while (var_r28 < 0x125);
    *temp_r31 = 0xF4;
    _Toy_sbss_804D6EA1 = 1;
}

void _Toy_80311788(void)
{
    GXColor color;
    char buf[0x48];
    f32 f31, f30, f29, f28, f27;

    _Toy_sbss_804D6E9C =
        DevText_Create(1, 0x21C, 0x82, 0xA, 7, _Toy_devtext_buf_804A26C4);

    if (_Toy_sbss_804D6E9C != NULL) {
        HSD_GObj* gobj = DevText_GetGObj();
        color = _Toy_color_40B0D060_1;
        DevText_Show(gobj, _Toy_sbss_804D6E9C);
        DevText_HideCursor(_Toy_sbss_804D6E9C);
        DevText_80302AC0(_Toy_sbss_804D6E9C);
        DevText_SetBGColor(_Toy_sbss_804D6E9C, *(GXColor*) &color);
        DevText_SetScale(_Toy_sbss_804D6E9C, 12.0f, 18.0f);
        DevText_Erase(_Toy_sbss_804D6E9C);
        DevText_SetCursorXY(_Toy_sbss_804D6E9C, 0, 0);

        f27 =
            Toy_803060BC(Toy_sbss_804D6EDC[Toy_sbss_804D6EE0->selectedIdx], 5);
        f28 =
            Toy_803060BC(Toy_sbss_804D6EDC[Toy_sbss_804D6EE0->selectedIdx], 4);
        f29 =
            Toy_803060BC(Toy_sbss_804D6EDC[Toy_sbss_804D6EE0->selectedIdx], 3);
        f30 =
            Toy_803060BC(Toy_sbss_804D6EDC[Toy_sbss_804D6EE0->selectedIdx], 2);
        f31 =
            Toy_803060BC(Toy_sbss_804D6EDC[Toy_sbss_804D6EE0->selectedIdx], 1);

        sprintf(
            buf,
            "X   %3.2f\nY   %3.2f\nZ   %3.2f\nMS  %3.2f\nSS  "
            "%3.2f\nMD  %3.2f",
            Toy_803060BC(Toy_sbss_804D6EDC[Toy_sbss_804D6EE0->selectedIdx], 0),
            f31, f30, f29, f28, f27);
        DevText_Print(_Toy_sbss_804D6E9C, buf);
    } else {
        OSReport("*** Couldn't Open Debug Window!\n");
    }
}

void Toy_80311960(void)
{
    u8* base;
    u16* save_data;
    s16* save_data2;
    int i;

    base = (u8*) &_Toy_804A26B8;
    save_data = gmMainLib_8015CC78();
    save_data2 = gmMainLib_8015CC84();

    for (i = 0; i < 0x125; i++) {
        save_data[i] = 0;
        ((u16*) (base + 0x194))[i + 5] = 0;
    }

    *save_data2 = 0;
    ((u16*) base)[0xCE] = 0;
    ((u16*) base)[0xCD] = 0;
    ((u16*) base)[0x1F4] = 0;
    ((u16*) base)[0x1F5] = 0;
    ((Toy26B8*) base)->x197 = 0;
    *gmMainLib_8015CC90() = 0;
    ((u16*) base)[0x1F6] = 0;
}

void Toy_OnEnter_80311AB0(void* arg0)
{
    u8* base;
    s16* selp;
    u32 buttons;
    s32 count;

    PAD_STACK(40);

    base = (u8*) &_Toy_804A26B8;
    _Toy_sbss_804D6EA2 = 0;
    _Toy_sbss_804D6E50 = 0;
    _Toy_sbss_804D6EA1 = 0;

    if (DbLevel >= 3) {
        /* Check Z button */
        buttons = Toy_80305C44();

        _Toy_sbss_804D6E50 = (buttons & HSD_PAD_L) ? 1 : 0;

        /* Check Start button */
        buttons = Toy_80305C44();

        _Toy_sbss_804D6EA2 = (buttons & HSD_PAD_Z) ? 1 : 0;

        /* Check D-pad down */
        buttons = Toy_80305C44();

        if (buttons & HSD_PAD_START) {
            _Toy_sbss_804D6EA0 = 0;
        }
        if ((s8) _Toy_sbss_804D6EA0 != 0) {
            _Toy_sbss_804D6EA0 += 1;
        }

        /* Check D-pad left */
        buttons = Toy_80305C44();

        if (buttons & HSD_PAD_R) {
            _Toy_sbss_804D6EA0 = 1;
        }
    }

    _Toy_sbss_804D6E68 = HSD_MemAlloc(sizeof(*_Toy_sbss_804D6E68));
    Toy_sbss_804D6ED8 = HSD_MemAlloc(sizeof(*Toy_sbss_804D6ED8));
    Toy_sbss_804D6ED4 = HSD_MemAlloc(0xE4);
    Toy_sbss_804D6EDC = HSD_MemAlloc(0x24A);
    _Toy_sbss_804D6E64 = HSD_MemAlloc(0x6DE);
    Toy_sbss_804D6EE0 = HSD_MemAlloc(sizeof(*Toy_sbss_804D6EE0));
    _Toy_sbss_804D6E6C = HSD_MemAlloc(8);

    memzero(_Toy_sbss_804D6E68, sizeof(*_Toy_sbss_804D6E68));
    memzero(Toy_sbss_804D6ED8, sizeof(*Toy_sbss_804D6ED8));
    memzero(Toy_sbss_804D6ED4, 0xE4);
    memzero(Toy_sbss_804D6EDC, 0x24A);
    memzero(_Toy_sbss_804D6E64, 0x6DE);
    memzero(Toy_sbss_804D6EE0, sizeof(*Toy_sbss_804D6EE0));
    memzero(_Toy_sbss_804D6E6C, 8);

    Toy_8031263C();

    /* Validate saved selection index */
    selp = &((s16*) base)[0x1F4];
    if (*selp < 0) {
        goto reset_selection;
    }
    if (gm_8016B498() != 0 || (u8) gm_801A4310() == 0xC) {
        count = *(s16*) (base + 0x3EC);
    } else {
        count = *gmMainLib_8015CC90();
    }
    if (*selp > count) {
    reset_selection:
        *selp = 0;
    }

    ((Toy26B8*) base)->x195 = 0;
    ((Toy26B8*) base)->x196 = 0;

    /* Set up SIS font tables based on language */
    if (lbLang_IsSavedLanguageJP() != 0) {
        HSD_SisLib_803A62A0(0, "SdToy.dat", "SIS_ToyData");
        HSD_SisLib_803A62A0(3, "SdToyExp.dat", "SIS_ToyDataExp");
    } else {
        HSD_SisLib_803A62A0(0, "SdToy.usd", "SIS_ToyData_E");
        HSD_SisLib_803A62A0(3, "SdToyExp.usd", "SIS_ToyDataExp_E");
    }

    /* Enter debug or normal mode */
    if ((s8) _Toy_sbss_804D6EA2 != 0) {
        _Toy_80311788();
    }
    if ((s32) _Toy_sbss_804D6EA0 == 1) {
        _Toy_803114E8();
        return;
    }
    if (gmMainLib_8015ED5C() != -1) {
        lbAudioAx_80023F28(gmMainLib_8015ED5C());
    }
    Toy_80310324();
}

void _Toy_80311F5C(void)
{
    void** p1 = (void**) Toy_sbss_804D6ED8;
    void** p2 = (void**) _Toy_sbss_804D6E68;

    if (p1[0x14] != NULL) {
        p1[0x14] = NULL;
    }
    if (p1[0] != NULL) {
        p1[0] = NULL;
    }
    if (p2[0] != NULL) {
        p2[0] = NULL;
    }
    if (_Toy_sbss_804D6EA2 != 0 && _Toy_sbss_804D6E9C != NULL) {
        DevText_Remove(&_Toy_sbss_804D6E9C);
        _Toy_sbss_804D6E9C = NULL;
    }
    if (_Toy_sbss_804D6E98 != NULL) {
        DevText_Remove(&_Toy_sbss_804D6E98);
        _Toy_sbss_804D6E98 = NULL;
    }
    if (_Toy_sbss_804D6E5C != NULL) {
        HSD_Free(_Toy_sbss_804D6E5C);
        _Toy_sbss_804D6E5C = NULL;
    }
}

void Toy_OnFrame_80312018(void)
{
    TyModeState* state = (TyModeState*) Toy_804A284C;

    if (state->x4 != 0) {
        _Toy_80311F5C();
        gm_801A4B60();
    }
}

void _Toy_80312050(HSD_GObj* gobj, int code)
{
    HSD_CObj* cobj;
    TyViewData* data;
    u8 color_ff;
    u8 color_00;

    data = _Toy_sbss_804D6E6C;
    cobj = HSD_CObjGetCurrent();

    if (data->x4 == 0) {
        Vec3 interest;
        Vec3 endpoint;
        UNUSED u8 pad[16];
        Mtx viewMtx;
        Vec3 up;
        Vec3 left;
        Vec3 eye;
        Vec3 scaled;

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

        PSVECScale(&left, &scaled, -3.25f);
        PSVECAdd(&scaled, &interest, &endpoint);

        color_ff = 0xFF;
        color_00 = 0;

        GXPosition3f32(endpoint.x, endpoint.y, endpoint.z);
        GXColor4u8(color_ff, color_00, color_00, color_ff);

        PSVECScale(&left, &scaled, +3.25f);
        PSVECAdd(&scaled, &interest, &endpoint);
        GXPosition3f32(endpoint.x, endpoint.y, endpoint.z);
        GXColor4u8(color_ff, color_00, color_00, color_ff);

        PSVECScale(&up, &scaled, -3.25f);
        PSVECAdd(&scaled, &interest, &endpoint);
        GXPosition3f32(endpoint.x, endpoint.y, endpoint.z);
        GXColor4u8(color_00, color_ff, color_00, color_ff);

        PSVECScale(&up, &scaled, +3.25f);
        PSVECAdd(&scaled, &interest, &endpoint);
        GXPosition3f32(endpoint.x, endpoint.y, endpoint.z);
        GXColor4u8(color_00, color_ff, color_00, color_ff);

        PSVECScale(&eye, &scaled, -3.25f);
        PSVECAdd(&scaled, &interest, &endpoint);
        GXPosition3f32(endpoint.x, endpoint.y, endpoint.z);
        GXColor4u8(color_00, color_00, color_ff, color_ff);

        PSVECScale(&eye, &scaled, +3.25f);
        PSVECAdd(&scaled, &interest, &endpoint);
        GXPosition3f32(endpoint.x, endpoint.y, endpoint.z);
        GXColor4u8(color_00, color_00, color_ff, color_ff);
    }
}

void Toy_OnInit_803122D0(void)
{
    Toy* userData = (Toy*) &_Toy_804A26B8;
    void* targetPtr;

    memzero(&userData->x194, 0x25A);

    _Toy_sbss_804D6EA1 = 0;

    if (gm_8016B498() || gm_801A4310() == GM_TOY_LOTTERY) {
        targetPtr = &userData->x19A;
    } else {
        targetPtr = gmMainLib_8015CC84();
    }

    *(u16*) targetPtr |= 4;

    *(u8*) &userData->x194 = 1;
}

void Toy_8031234C(s32 arg0)
{
    u16* saveData;
    u16* stateData;
    char* toy = (char*) &_Toy_804A26B8;
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
                    f32 result = Toy_803060BC(j, 6);
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

void Toy_803124BC(void)
{
    u16* table1;
    s16* list;
    u16* table2;
    s32 i;

    table1 = gmMainLib_8015CC78();
    table2 = gmMainLib_8015CC84();

    if (_Toy_sbss_804D6ED0 == NULL) {
        _Toy_sbss_804D6ED0 = lbArchive_LoadSymbols(
            getDataiDatFilename(), &_Toy_sbss_804D6EC4, "tyInitModelTbl",
            &_Toy_sbss_804D6EC0, "tyInitModelDTbl", &_Toy_sbss_804D6EBC,
            "tyModelSortTbl", &_Toy_sbss_804D6EB8, "tyExpDifferentTbl",
            &_Toy_sbss_804D6EB4, "tyNoGetUsTbl", &Toy_sbss_804D6EB0,
            "tyDisplayModelTbl", &Toy_sbss_804D6EAC, "tyDisplayModelUsTbl",
            NULL);
    }

    i = 0;
loop: {
    s32 skip;
    s16 val;

    list = _Toy_sbss_804D6EB4;
    if (lbLang_IsSettingUS()) {
        while ((val = *list) != -1) {
            if (val == i) {
                skip = 0;
                goto check;
            }
            list++;
        }
    }
    skip = 1;
check:
    if (skip != 0 && (s32) Toy_803060BC(i, 6) == 2) {
        *table1 |= 0x4000;
    }
}
    i++;
    table1++;
    if (i < 0x125) {
        goto loop;
    }

    *table2 |= 4;
    Toy_804A284C[3] |= 4;
}

void Toy_8031263C(void)
{
    s32 i;
    u16* table1;
    u16* table2;

    ((TyModeState*) Toy_804A284C)->x4 = 0;
    table1 = gmMainLib_8015CC78();
    table2 = gmMainLib_8015CC84();

    if (_Toy_sbss_804D6ED0 == NULL) {
        _Toy_sbss_804D6ED0 = lbArchive_LoadSymbols(
            getDataiDatFilename(), &_Toy_sbss_804D6EC4, "tyInitModelTbl",
            &_Toy_sbss_804D6EC0, "tyInitModelDTbl", &_Toy_sbss_804D6EBC,
            "tyModelSortTbl", &_Toy_sbss_804D6EB8, "tyExpDifferentTbl",
            &_Toy_sbss_804D6EB4, "tyNoGetUsTbl", &Toy_sbss_804D6EB0,
            "tyDisplayModelTbl", &Toy_sbss_804D6EAC, "tyDisplayModelUsTbl",
            NULL);
    }

    i = 0;
    do {
        if (_Toy_80304CC8_noinline(i) != 0) {
            if ((s32) Toy_803060BC(i, 6) == 2) {
                *table1 |= 0x4000;
            }
        }
        i++;
        table1++;
    } while (i < 0x125);

    *table2 |= 4;
    Toy_804A284C[3] |= 4;
    Toy_803102D0();
    Toy_8031234C(0);
}

void Toy_803127D4(void)
{
    _Toy_sbss_804D6ED0 = NULL;
    _Toy_sbss_804D6EC4 = NULL;
    _Toy_sbss_804D6EC0 = NULL;
    _Toy_sbss_804D6EBC = NULL;
    _Toy_sbss_804D6EB8 = NULL;
    _Toy_sbss_804D6EB4 = NULL;
    Toy_sbss_804D6EB0 = NULL;
    Toy_sbss_804D6EAC = NULL;
    _Toy_sbss_804D6ECC = NULL;
    _Toy_sbss_804D6EA8 = NULL;
    _Toy_sbss_804D6EA4 = NULL;
    Toy_sbss_804D6EC8 = NULL;
    memzero(&Toy_804A2AA8, sizeof(Toy_804A2AA8));
}
