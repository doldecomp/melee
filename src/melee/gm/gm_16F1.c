#include "gm_16F1.h"

#include "gm_16F1.static.h"

#include "gm_unsplit.h"

#include "un/un_3028.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lblanguage.h>
#include <melee/pl/plbonus.h>
#include <melee/ty/toy.h>
#include <melee/un/un_2FC9.h>

struct lbl_803D6300_t {
    u32 x0;
    bool (*x4)(void);
};

struct lbl_803D6300_t lbl_803D6300[] = {
    {0x0016FFFF, fn_801735F0},
	{0x00170001, fn_80173644},
	{0x0018FFFF, fn_80173510},
	{0x0019FFFF, NULL},
	{0x001AFFFF, NULL},
	{0x001BFFFF, fn_8017367C},
	{0x001CFFFF, gm_80164ABC},
	{0x001DFFFF, gm_80164600},
	{0x001E0040, fn_80162CCC},
	{0x001F0040, gm_80162EC8},
	{0x00200040, fn_801630C4},
	{0x00210040, gm_80162D1C},
	{0x00220040, gm_80162F18},
	{0x00230040, gm_80163114},
	{0x00240010, fn_801722BC},
	{0x00250010, fn_801722F4},
	{0x00260080, gmMainLib_8015D508},
	{0x00270020, fn_80163D24},
	{0x00280020, fn_80163D74},
	{0x00290040, fn_8017232C},
	{0x002A0040, fn_80172428},
	{0x002B0040, fn_80172380},
	{0x002C0040, fn_80172478},
	{0x002D0040, fn_801723D4},
	{0x002E0040, fn_801724C8},
	{0x002F0001, fn_801724D0},
	{0x00300001, fn_80172504},
	{0x00310001, fn_80172538},
	{0x00320001, fn_8017256C},
	{0x00330001, fn_801725A8},
	{0x00340001, fn_801725E4},
	{0x00350001, fn_80172624},
	{0x00360001, fn_80172664},
	{0x0037FFFF, fn_80172698},
	{0x0038FFFF, fn_801726CC},
	{0x0039FFFF, fn_80172700},
	{0x003AFFFF, fn_80172734},
	{0x003BFFFF, fn_80172768},
	{0x003CFFFF, un_80304470},
	{0x003DFFFF, un_80304510},
	{0x00410010, gmMainLib_8015CF94},
	{0x00420000, NULL},
};

int fn_8016F180(int arg0)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->x0 != arg0) {
        if (curr->x0 == 0x29A) {
            return 0;
        }
        curr++;
    }
    return curr->x4;
}

int gmDecisionGetType(int kind)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->x0 != kind) {
        if (curr->x0 == 0x29A) {
            return 0;
        }
        curr++;
    }
    return curr->x5;
}

short fn_8016F1F0(int idx)
{
    return lbl_803D5A4C[idx].x0;
}

int gm_8016F208(int arg0)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->x0 != arg0) {
        if (curr->x0 == 0x29A) {
            return 0;
        }
        curr++;
    }
    if (curr->x2 == 0xDE && lbLang_IsSettingUS()) {
        return 0x102;
    }
    return curr->x2;
}

int fn_8016F280(int arg0)
{
    return gm_8016F208(arg0) - 2;
}

int gm_8016F2F8(int arg0, u8 arg1)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->x0 != arg0) {
        if (curr->x0 == 0x29A) {
            return -1;
        }
        curr++;
    }
    return lbl_803D5648[curr->x2 - 2];
}

void fn_8016F344(struct lbl_8046B6A0_24C_t* arg0)
{
    struct lbl_8046B6A0_24C_58_t* curr = arg0->x58;
    int i;
    for (i = 0; i < 4; i++) {
        if (curr->x0 != 3) {
            pl_80039450(i);
        }
        curr++;
    }
}

/// #fn_8016F39C

/// #fn_8016F548

/// #fn_8016F740

/// #fn_8016F870

/// #fn_8016F9A8

void fn_80171AD4(void)
{
    memzero(&lbl_8046DBC8, 0xE);
}

/// #fn_8016FFD4

/// #fn_80170110

void gm_801701A0(void)
{
    lbl_804D65A0 = 1;
}

void fn_801701AC(void)
{
    lbl_804D65A0 = 0;
}

u8 fn_801701B8(void)
{
    return lbl_804D65A0;
}

/// #fn_801701C0

/// #fn_80171A88

/// #fn_80171AD4

/// #fn_80171B00

/// #fn_80171B2C

/// #fn_80171B64

/// #fn_80171BA4

/// #fn_80171DC4

/// #gm_801720B4

/// #gm_801720F8

/// #gm_80172140

/// #gm_80172174

/// #gm_8017219C

static inline bool gm_801721EC_1(u32 i)
{
    if (gmMainLib_8015D94C(i) && gmMainLib_8015D8D8(i)) {
        return true;
    }
    return false;
}

static inline bool gm_801721EC_2(void)
{
    s32 i;
    for (i = 0; i < 0x42; i++) {
        if (gm_801721EC_1(i)) {
            return true;
        }
    }
    return false;
}

static inline bool gm_801721EC_3(u32 j)
{
    if (gmMainLib_8015DA1C(j)) {
        return true;
    }
    return false;
}

static inline bool gm_801721EC_4(void)
{
    s32 j;
    for (j = 0; j < 0x125; j++) {
        if (gm_801721EC_3(j)) {
            return true;
        }
    }
    return false;
}

bool gm_801721EC(void)
{
    if (gm_801721EC_2() || gm_801721EC_4()) {
        return true;
    }
    return false;
}

/// #fn_801722BC

/// #fn_801722F4

/// #fn_8017232C

/// #fn_80172380

/// #fn_801723D4

/// #fn_80172428

/// #fn_80172478

bool fn_801724C8(void)
{
    return false;
}

bool fn_801724D0(void)
{
    if (gm_8016279C() >= 0x64) {
        return true;
    }
    return false;
}

bool fn_80172504(void)
{
    if (gm_8016279C() >= 0x3E8) {
        return true;
    }
    return false;
}

bool fn_80172538(void)
{
    if (gm_8016279C() >= 0x2710) {
        return true;
    }
    return false;
}

bool fn_8017256C(void)
{
    if (gm_8016279C() >= 0x186A0) {
        return true;
    }
    return false;
}

bool fn_801725A8(void)
{
    if (gm_8016279C() >= 0xF4240) {
        return true;
    }
    return false;
}

enum {
    LANG_JP = 0,
    LANG_US = 1,
};

bool fn_801725E4(void)
{
    if (lbLang_GetLanguageSetting() == LANG_JP && gm_8016279C() >= 0x1A90) {
        return true;
    }
    return false;
}

bool fn_80172624(void)
{
    if (lbLang_GetLanguageSetting() == LANG_US && gm_8016279C() >= 0x1383) {
        return true;
    }
    return false;
}

bool fn_80172664(void)
{
    if (gm_8016279C() >= 0xC350) {
        return true;
    }
    return false;
}

bool fn_80172698(void)
{
    if (un_80304870() >= 0x32) {
        return true;
    }
    return false;
}

bool fn_801726CC(void)
{
    if (un_80304870() >= 0x64) {
        return true;
    }
    return false;
}

bool fn_80172700(void)
{
    if (un_80304870() >= 0x96) {
        return true;
    }
    return false;
}

bool fn_80172734(void)
{
    if (un_80304870() >= 0xC8) {
        return true;
    }
    return false;
}

bool fn_80172768(void)
{
    if (un_80304870() >= 0xFA) {
        return true;
    }
    return false;
}

/// #fn_8017279C

void fn_8017280C(void)
{
    if (gmMainLib_8015D94C(0x18) != 0) {
        gmMainLib_8015EE54();
    } else {
        gmMainLib_8015EE68();
    }
    if (gmMainLib_8015D94C(0x17) != 0) {
        gmMainLib_8015EE1C();
    } else {
        gmMainLib_8015EE30();
    }
    if (gmMainLib_8015D94C(0x16) != 0) {
        gmMainLib_8015EDE4();
    } else {
        gmMainLib_8015EDF8();
    }
    if (gmMainLib_8015D94C(0x1B) != 0) {
        gmMainLib_8015EEA0();
        return;
    }
    gmMainLib_8015EEB4();
}

/// #gm_80172898

/// #gm_8017297C

/// #gm_801729EC

bool gm_80172BC4(void)
{
    if (gmMainLib_8015D94C(0x19) == 0) {
        gmMainLib_8015D818(0x19);
        return true;
    }
    return false;
}

bool gm_80172C04(void)
{
    if (gmMainLib_8015D94C(0x1A) == 0) {
        gmMainLib_8015D818(0x1A);
        return true;
    }
    return false;
}

/// #gm_80172C44

#pragma push
#pragma dont_inline on
bool fn_80172C78(int arg0)
{
    if (gmMainLib_8015D984(arg0) != 0) {
        gmMainLib_8015DA68(arg0);
        return true;
    }
    return false;
}
#pragma pop

/// #gm_80172CC0

/// #gm_80172D78

/// #gm_80172DD4

u8 gm_80172E74(void)
{
    int i;
    int count = 0;

    for (i = 0; i < 0x19; i++) {
        if (fn_801605EC(i) == 0xB && gmMainLib_8015CFCC(i)) {
            count += 1;
        }
    }
    if (count >= 0xE && !gm_80164840(9)) {
        return 9;
    }
    return 0x21;
}

u16 gm_80172F00(u32 arg0)
{
    if (arg0 >= 0x32 && !gm_80164430(0xF)) {
        return 0xF;
    }
    if (arg0 >= 0x64 && !gm_80164430(0x12)) {
        return 0x12;
    }
    if (arg0 >= 0x96 && !gm_80164430(0x18)) {
        return 0x18;
    }
    if (arg0 >= 0xC8 && !gm_80164430(0x17)) {
        return 0x17;
    }
    return 0x148;
}

/// #fn_80172FAC

/// #fn_80173098

u8 gm_80173224(int arg0, int arg1)
{
    u8 var_r4 = 0x21;
    if (arg1 != 0) {
        var_r4 = fn_80173098(arg0);
    }
    if (var_r4 == 0x21) {
        var_r4 = gm_80172E74();
    }
    return var_r4;
}

/// #gm_801732D8

/// #gm_8017335C

/// #gm_801733D8

/// #gm_8017341C

/// #gm_80173460

/// #gm_80173498

/// #gm_801734D0

/// #fn_80173510

/// #fn_801735F0

/// #fn_80173644

/// #fn_8017367C

UNK_T gm_801736DC(void)
{
    return &lbl_8046DBD8;
}

/// #gm_801736E8

/// #gm_80173754

u8 gm_801737D8(void)
{
    return M2C_FIELD(&lbl_8046DBD8, u8*, 6);
}

/// #gm_801737E8_OnLoad

/// #fn_80173834

/// #gm_8017390C

/// #gm_80173AA4

/// #gm_80173B30

/// #gm_80173BC4

/// #gm_80173C70

/// #gm_80173D3C

/// #gm_80173DE4

static inline bool gm_80173EEC_inline(void)
{
    int i;
    bool result = true;

    for (i = 0; i < 0x100; i++) {
        if (i != 0x29 && i - 0x42 > 1U && i != 0xB9 && i - 0xC9 > 1U &&
            i != 9 && gmMainLib_8015DADC(i) == 0)
        {
            result = false;
            break;
        }
    }
    return result;
}

void gm_80173EEC(void)
{
    int i;
    u8 temp_r3;
    u16* temp_r29;

    for (i = 0; i < 0x19; i++) {
        temp_r29 = &gmMainLib_8015EDBC()->x18[i];
        if (*temp_r29 >= 0x64) {
            temp_r3 = gm_8016400C(i);
            fn_80172C78(gm_80160474(temp_r3, 3));
            if (temp_r3 == 0x12) {
                fn_80172C78(gm_80160474(0x13, 3));
            }
            if (temp_r3 == 0x13) {
                fn_80172C78(gm_80160474(0x12, 3));
            }
        }
        if (*temp_r29 >= 0xC8) {
            temp_r3 = gm_8016400C(i);
            fn_80172C78(gm_80160474(temp_r3, 4));
            if (temp_r3 == 0x12) {
                fn_80172C78(gm_80160474(0x13, 4));
            }
            if (temp_r3 == 0x13) {
                fn_80172C78(gm_80160474(0x12, 4));
            }
        }
        if (*temp_r29 >= 0x12C) {
            temp_r3 = gm_8016400C(i);
            fn_80172C78(gm_80160474(temp_r3, 5));
            if (temp_r3 == 0x12) {
                fn_80172C78(gm_80160474(0x13, 5));
            }
            if (temp_r3 == 0x13) {
                fn_80172C78(gm_80160474(0x12, 5));
            }
        }
    }

    if (fn_80164B48() != 0) {
        fn_80172C78(0xA0);
    }
    if (gm_80164ABC() != 0) {
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

    if (gm_80173EEC_inline()) {
        fn_80172C78(0x123);
    }
}

void gm_80174180(void)
{
    if (fn_80162CCC() != 0 && gm_80162EC8() != 0) {
        un_80305918(4, 0, 0);
    }
    if (gm_8016279C() >= 0xC8) {
        un_80305918(5, 0, 0);
    }
    if (gm_80164ABC() != 0) {
        un_80305918(6, 0, 0);
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
