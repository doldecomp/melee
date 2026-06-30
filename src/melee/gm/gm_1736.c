#include "gm_1601.h"
#include "gm_16F1.h"
#include "gm_1A3F.h"
#include "gm_1BA8.h"
#include "gmmain_lib.h"
#include "gmregclear.h"
#include "types.h"

#include <melee/if/textlib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbtime.h>
#include <melee/ty/toy.h>

static lbl_8046DBD8_t lbl_8046DBD8;

lbl_8046DBD8_t* gm_801736DC(void)
{
    return &lbl_8046DBD8;
}

void gm_801736E8(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5)
{
    lbl_8046DBD8_t* tmp = &lbl_8046DBD8;
    memzero(tmp, sizeof(lbl_8046DBD8));
    tmp->x0 = arg0;
    tmp->x1 = arg1;
    tmp->x2 = arg2;
    tmp->x3 = arg3;
    tmp->x4 = arg4;
    tmp->x5 = arg5;
}

#pragma push
#pragma dont_inline on
bool gm_80173754(s8 arg0, u8 arg1)
{
    if (gm_801721EC()) {
        memzero(&lbl_8046DBD8, sizeof(lbl_8046DBD8));
        lbl_8046DBD8.x0 = CHKIND_NONE;
        lbl_8046DBD8.x2 = arg1;
        lbl_8046DBD8.x5 = arg0;
        gm_801A42E8(GM_CHALLENGER_APPROACH);
        gm_801A42D4();
        return true;
    }
    return false;
}
#pragma pop

u8 gm_801737D8(void)
{
    return lbl_8046DBD8.x6;
}

void gm_801737E8_OnLoad(void)
{
    lbl_8046DBD8.x6 = gm_801A4320();
    if (lbl_8046DBD8.x0 == CHKIND_NONE) {
        gm_SetScene(2);
    } else {
        gm_SetScene(0);
    }
}

void fn_80173834(u8 ckind, u8 major, int arg2)
{
    bool temp_r31;
    bool temp_r30 = gm_80160474(ckind, major);

    if (arg2) {
        gmMainLib_8015DA68(temp_r30);
    }
    fn_80172C78(temp_r30);
    if (ckind == CKIND_ZELDA) {
        temp_r31 = gm_80160474(CKIND_SEAK, major);
        if (arg2) {
            gmMainLib_8015DA68(temp_r31);
        }
        fn_80172C78(temp_r31);
    }
    if (ckind == CKIND_SEAK) {
        temp_r31 = gm_80160474(CKIND_ZELDA, major);
        if (arg2) {
            gmMainLib_8015DA68(temp_r31);
        }
        fn_80172C78(temp_r31);
    }
}

#pragma push
#pragma dont_inline on
void gm_8017390C(int arg0, int arg1)
{
    Unk1PData* temp_r3_2;
    Unk1PData* temp_r3_3;
    UnkAdventureData* temp_r3;

    switch (arg0) { /* irregular */
    case 0:
        temp_r3 = gm_8017E424();
        if (temp_r3->x76 != 0) {
            fn_80172C78(0xE7);
        }
        if (arg1 != 0) {
            fn_80173834(temp_r3->x0.ckind, 4, 1);
            if (temp_r3->x0.xC.xD == 0 && temp_r3->x77 != 0) {
                fn_80172C78(0x51);
            }
            if (temp_r3->x0.xC.xD == 0 && temp_r3->x0.cpu_level >= 3) {
                fn_80172C78(0x53);
            }
            if (temp_r3->x0.xC.x20 < 0x101D0) {
                fn_80172C78(0xE3);
            }
        }
        break;
    case 1:
        if (arg1 != 0) {
            temp_r3_2 = fn_8017DEC8(1);
            fn_80173834(temp_r3_2->ckind, 3, 1);
            if (temp_r3_2->xC.xD == 0 && temp_r3_2->cpu_level >= 3) {
                fn_80172C78(0x52);
            }
            if (temp_r3_2->xC.x20 < 0x4650) {
                fn_80172C78(0x11A);
            }
        }
        break;
    case 2:
        if (arg1 != 0) {
            temp_r3_3 = fn_8017DEC8(2);
            fn_80173834(temp_r3_3->ckind, 5, 1);
            fn_80172C78(0xBE);
            if (temp_r3_3->xC.xD == 0) {
                fn_80172C78(0xCC);
            }
            if (temp_r3_3->cpu_level >= 3) {
                fn_80172C78(0x86);
            }
        }
        break;
    }
}
#pragma pop

void gm_80173AA4(void)
{
    int i;
    u32 var_r30 = 0;

    if (gmMainLib_8015D640()) {
        fn_80172C78(0xBC);
        for (i = 0; i < 0x19; i++) {
            var_r30 += *gmMainLib_8015D450(i);
        }
        if (var_r30 < 0x15F90) {
            fn_80172C78(0x9B);
        }
        if (var_r30 < 0xAFC8) {
            fn_80172C78(0x122);
        }
    }
}

void gm_80173B30(u32 arg0)
{
    u32 var_r31 = 0;
    int i;

    if (arg0 >= 0x7530) {
        fn_80172C78(0xBD);
    }
    if (arg0 >= 0xAFC8) {
        fn_80172C78(0xCB);
    }
    for (i = 0; i < 0x19; i++) {
        var_r31 = lbTime_8000AEE4(var_r31, *gmMainLib_8015D084(i));
    }
    if (var_r31 >= 0x7A120) {
        fn_80172C78(0x8D);
    }
}

void gm_80173BC4(s8 arg0)
{
    u8 temp_r31;
    int i;
    int var_r29;
    int temp_r28;

    var_r29 = 0;
    temp_r28 = gmMainLib_8015EDBC()->x114[gm_80164024(arg0)];
    for (i = 0; i < 0x19; i++) {
        var_r29 += gmMainLib_8015EDBC()->x114[i];
    }
    if (temp_r28 >= 0xA) {
        fn_80172C78(0x6D);
    }
    if (temp_r28 >= 0x14) {
        fn_80172C78(0x5B);
    }
    if (var_r29 >= 0x7D) {
        fn_80172C78(0x6E);
    }
}

void gm_80173C70(s8 c_kind, u32 arg1, u32 arg2, int arg3)
{
    if (arg3 != 0) {
        if (gm_801A4310() == GM_15MIN_VS) {
            fn_80172C78(0x50);
        }
        if (gm_801A4310() == GM_100MAN_VS && arg2 <= 0x3840) {
            fn_80172C78(0x4E);
        }
        if (gm_801A4310() == GM_15MIN_VS) {
            fn_80172C78(0x50);
        }
    }
    if (gm_801A4310() == GM_ENDLESS_VS && arg1 >= 100) {
        fn_80172C78(0x4F);
    }
    if (gm_801A4310() == GM_CRUEL_VS && arg1 >= 5) {
        fn_80172C78(0x10E);
    }
}

static struct lbl_803D6450_t {
    u8 x0;
    u8 x1;
    u16 x2;
} lbl_803D6450[] = {
    { 0x02, 0x00, 0x0067 }, { 0x02, 0x01, 0x0067 }, { 0x0D, 0x02, 0x00C0 },
    { 0x19, 0x02, 0x0092 }, { 0x2C, 0x02, 0x00BB }, { 0x2E, 0x02, 0x00DD },
    { 0x32, 0x02, 0x00BF },
};

static inline int inline0(int arg0)
{
    struct lbl_803D6450_t* r30 = lbl_803D6450;
    int i;
    for (i = 0; i < ARRAY_SIZE(lbl_803D6450); i++) {
        if (r30[i].x1 == 2 || r30[i].x1 == lbLang_GetLanguageSetting()) {
            if (gm_801BEBC0(r30[i].x0) == gm_801BEBC0(arg0)) {
                return r30[i].x2;
            }
        }
    }
    return -1;
}

void gm_80173D3C(int arg0)
{
    int var_r0 = inline0(arg0);
    if (var_r0 != -1) {
        fn_80172C78(var_r0);
    }
}

static struct lbl_803D646C_t {
    u16 x0;
    u16 x2;
} lbl_803D646C[] = {
    { 0x032, 0xB5 }, { 0x064, 0xB9 }, { 0x096, 0xAE }, { 0x0C8, 0x8C },
    { 0x00A, 0x55 }, { 0x064, 0x56 }, { 0x3E8, 0x54 },
};

void gm_80173DE4(MatchEnd* arg0)
{
    u32 temp_r30;
    u32 var_r29_2;
    int i;

    temp_r30 = gmMainLib_8015EDBC()->x0;

    for (i = 0; i < ARRAY_SIZE(lbl_803D646C); i++) {
        if (temp_r30 >= lbl_803D646C[i].x0) {
            fn_80172C78(lbl_803D646C[i].x2);
        }
    }
    if (gmMainLib_8015EDBC()->x4 >= 100) {
        fn_80172C78(0x76);
    }
    if (gmMainLib_8015EDBC()->xC >= 1000) {
        fn_80172C78(0xE2);
    }
    var_r29_2 = 0;

    for (i = 0; i < 6; i++) {
        if (arg0->player_standings[i].slot_type == 0) {
            var_r29_2 =
                lbTime_8000AEC8(var_r29_2, arg0->player_standings[i].x50);
        }
    }
    if (lbTime_8000AEC8(var_r29_2, gmMainLib_8015EDBC()->x10) >= 0xF4240) {
        fn_80172C78(0xB0);
    }
}

static inline bool gm_80173EEC_inline(u8 arg0, int arg1)
{
    return gm_80160474(arg0, arg1);
}

void gm_80173EEC(void)
{
    int i;
    u8 ckind;
    u16* temp_r29;

    for (i = 0; i < 0x19; i++) {
        temp_r29 = &gmMainLib_8015EDBC()->x18[(u32) i];
        if (*temp_r29 >= 100) {
            ckind = gm_8016400C(i);
            fn_80172C78(gm_80173EEC_inline(ckind, GM_CLASSIC));
            if (ckind == CKIND_ZELDA) {
                fn_80172C78(gm_80173EEC_inline(CKIND_SEAK, GM_CLASSIC));
            }
            if (ckind == CKIND_SEAK) {
                fn_80172C78(gm_80173EEC_inline(CKIND_ZELDA, GM_CLASSIC));
            }
        }
        if (*temp_r29 >= 200) {
            ckind = gm_8016400C(i);
            fn_80172C78(gm_80173EEC_inline(ckind, GM_ADVENTURE));
            if (ckind == CKIND_ZELDA) {
                fn_80172C78(gm_80173EEC_inline(CKIND_SEAK, GM_ADVENTURE));
            }
            if (ckind == CKIND_SEAK) {
                fn_80172C78(gm_80173EEC_inline(CKIND_ZELDA, GM_ADVENTURE));
            }
        }
        if (*temp_r29 >= 300) {
            ckind = gm_8016400C(i);
            fn_80172C78(gm_80173EEC_inline(ckind, GM_ALLSTAR));
            if (ckind == CKIND_ZELDA) {
                fn_80172C78(gm_80173EEC_inline(CKIND_SEAK, GM_ALLSTAR));
            }
            if (ckind == CKIND_SEAK) {
                fn_80172C78(gm_80173EEC_inline(CKIND_ZELDA, GM_ALLSTAR));
            }
        }
    }

    if (fn_80164B48() != 0) {
        fn_80172C78(0xA0);
    }
    if (gm_80164ABC()) {
        fn_80172C78(0x9F);
    }
    if (gmMainLib_8015EE90() != 0) {
        fn_80172C78(0xDC);
    }
    if (gmMainLib_8015EDBC()->x14 >= 0x2710) {
        fn_80172C78(0x10C);
    }
    if (gmMainLib_8015D94C(0x1A) != 0) {
        fn_80172C78(0x96);
    }
    if (un_803045A0() != 0) {
        fn_80172C78(0x116);
    }
    if (un_80304690() != 0) {
        fn_80172C78(0xAF);
    }
    if (un_80304780() != 0) {
        fn_80172C78(0x100);
    }

    {
        int j;
        bool result = true;

        for (j = 0; j < 0x100; j++) {
            if (j == 0x29) {
                continue;
            }
            if (j == 0x42 || j == 0x43) {
                continue;
            }
            if (j == 0xB9) {
                continue;
            }
            if (j == 0xC9 || j == 0xCA) {
                continue;
            }
            if (j == 9) {
                continue;
            }
            if (!gmMainLib_8015DADC(j)) {
                result = false;
                break;
            }
        }
        if (result) {
            fn_80172C78(0x123);
        }
    }
}

void gm_80174180(void)
{
    if (fn_80162CCC() != 0 && gm_80162EC8() != 0) {
        Toy_80305918(4, 0, 0);
    }
    if (gm_GetVsPlayMatchTotal() >= 0xC8) {
        Toy_80305918(5, 0, 0);
    }
    if (gm_80164ABC() != 0) {
        Toy_80305918(6, 0, 0);
    }
}

void gm_801741FC(void)
{
    int i;
    for (i = 0; i < 0x12C; i++) {
        gmMainLib_8015DA40(i);
    }
}

void gm_80174238(void)
{
    int i;
    for (i = 0; i < 0x12C; i++) {
        gmMainLib_8015DA68(i);
    }
}
