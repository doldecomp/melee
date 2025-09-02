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
    u16 x0;
    u16 x2;
    bool (*x4)(void);
};

struct lbl_803D6300_t lbl_803D6300[] = {
    {0x0016, 0xFFFF, fn_801735F0},
    {0x0017, 0x0001, fn_80173644},
    {0x0018, 0xFFFF, fn_80173510},
    {0x0019, 0xFFFF, NULL},
    {0x001A, 0xFFFF, NULL},
    {0x001B, 0xFFFF, fn_8017367C},
    {0x001C, 0xFFFF, gm_80164ABC},
    {0x001D, 0xFFFF, gm_80164600},
    {0x001E, 0x0040, fn_80162CCC},
    {0x001F, 0x0040, gm_80162EC8},
    {0x0020, 0x0040, fn_801630C4},
    {0x0021, 0x0040, gm_80162D1C},
    {0x0022, 0x0040, gm_80162F18},
    {0x0023, 0x0040, gm_80163114},
    {0x0024, 0x0010, fn_801722BC},
    {0x0025, 0x0010, fn_801722F4},
    {0x0026, 0x0080, gmMainLib_8015D508},
    {0x0027, 0x0020, fn_80163D24},
    {0x0028, 0x0020, fn_80163D74},
    {0x0029, 0x0040, fn_8017232C},
    {0x002A, 0x0040, fn_80172428},
    {0x002B, 0x0040, fn_80172380},
    {0x002C, 0x0040, fn_80172478},
    {0x002D, 0x0040, fn_801723D4},
    {0x002E, 0x0040, fn_801724C8},
    {0x002F, 0x0001, fn_801724D0},
    {0x0030, 0x0001, fn_80172504},
    {0x0031, 0x0001, fn_80172538},
    {0x0032, 0x0001, fn_8017256C},
    {0x0033, 0x0001, fn_801725A8},
    {0x0034, 0x0001, fn_801725E4},
    {0x0035, 0x0001, fn_80172624},
    {0x0036, 0x0001, fn_80172664},
    {0x0037, 0xFFFF, fn_80172698},
    {0x0038, 0xFFFF, fn_801726CC},
    {0x0039, 0xFFFF, fn_80172700},
    {0x003A, 0xFFFF, fn_80172734},
    {0x003B, 0xFFFF, fn_80172768},
    {0x003C, 0xFFFF, un_80304470},
    {0x003D, 0xFFFF, un_80304510},
    {0x0041, 0x0010, gmMainLib_8015CF94},
    {0x0042, 0x0000, NULL},
};

int fn_8016F180(int kind)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->kind != kind) {
        if (curr->kind == 0x29A) {
            return 0;
        }
        curr++;
    }
    return curr->x4;
}

Gm_DecType gmDecisionGetType(int kind)
{
    struct lbl_803D5A4C_t* curr;
    for (curr = lbl_803D5A4C; curr->kind != kind; curr++) {
        if (curr->kind == 0x29A) {
            return Gm_DecType_Flag;
        }
    }
    return curr->x5;
}

short fn_8016F1F0(int idx)
{
    return lbl_803D5A4C[idx].kind;
}

int gm_8016F208(int kind)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->kind != kind) {
        if (curr->kind == 0x29A) {
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

int gm_8016F2F8(int kind, u8 arg1)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C;
    while (curr->kind != kind) {
        if (curr->kind == 0x29A) {
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
    memzero(&lbl_8046DBC8, sizeof(lbl_8046DBC8));
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

int fn_801701B8(void)
{
    return lbl_804D65A0;
}

/// #fn_801701C0

int fn_80171A88(void)
{
    int result = 0;
    if (gm_8016B41C()) {
        result = fn_8017E0E4();
        if (result == -1) {
            result = 1;
        }
    }
    return result;
}

/// #fn_80171AD4

bool fn_80171B00(int arg0)
{
    if (lbl_8046DBC8.x2[arg0].x0 != 0) {
        return true;
    }
    return false;
}

bool fn_80171B2C(int arg0)
{
    if (lbl_8046DBC8.x1 != 0 && lbl_8046DBC8.x2[arg0].x1 != 0) {
        return true;
    }
    return false;
}

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

bool fn_801722BC(void)
{
    if (fn_80163FA4(0x1E) == 0x1E) {
        return true;
    }
    return false;
}

bool fn_801722F4(void)
{
    if (fn_80163FA4(0x33) == 0x33) {
        return true;
    }
    return false;
}

/// #fn_8017232C

/// #fn_80172380

/// #fn_801723D4

bool fn_80172428(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D1AC(i) == 1) {
            return true;
        }
    }
    return false;
}

bool fn_80172478(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D2D4(i) == 1) {
            return true;
        }
    }
    return false;
}

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

bool fn_8017279C(int arg0, u16 arg1)
{
    struct lbl_803D6300_t* cur = lbl_803D6300;
    while (cur->x0 != 0x42) {
        if (cur->x0 == arg0 && cur->x2 & arg1) {
            if (cur->x4 != NULL) {
                return cur->x4();
            }
        }
        cur++;
    }
    return false;
}

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
    if (count >= 0xE && !gm_80164840(CKIND_MARS)) {
        return CKIND_MARS;
    }
    return CHKIND_NONE;
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

/// check for event character unlocks?
CharacterKind gm_801732D8(u8 arg0)
{
    if (!gm_80164840(CKIND_GANON) && gm_801BEBC0(arg0) == 0x1C) {
        return CKIND_GANON;
    }
    if (!gm_80164840(CKIND_PICHU) && gm_801BEBC0(arg0) == 0xE) {
        return CKIND_PICHU;
    }
    return CHKIND_NONE;
}

int gm_8017335C(void)
{
    int var_r31 = 1;
    int i;
    for (i = 0; i < 0x33; i++) {
        if (!gmMainLib_8015CEFC(i)) {
            var_r31 = 0;
            break;
        }
    }
    if (var_r31 == 1 && !gm_80164430(0x20)) {
        return 0x20;
    }
    return 0x148;
}

int gm_801733D8(void)
{
    if (!gm_80164840(CKIND_GAMEWATCH) && fn_80172FAC()) {
        return CKIND_GAMEWATCH;
    }
    return CHKIND_NONE;
}

int gm_8017341C(void)
{
    if (gmMainLib_8015D5DC() && !gm_80164430(0x1C)) {
        return 0x1C;
    }
    return 0x148;
}

u8 gm_80173460(s8 arg0)
{
    if (!gm_80164840(CKIND_FALCO)) {
        return CKIND_FALCO;
    }
    return CHKIND_NONE;
}

u16 gm_80173498(void)
{
    if (!gm_80164430(0x1E)) {
        return 0x1E;
    }
    return 0x148U;
}

u16 gm_801734D0(u32 arg0)
{
    if (arg0 >= 0x9C40 && !gm_80164430(0x1D)) {
        return 0x1D;
    }
    return 0x148;
}

/// #fn_80173510

bool fn_801735F0(void)
{
    if (!gmMainLib_8015EDC8()->x4 && gm_80164ABC()) {
        gmMainLib_8015EDC8()->x4 = true;
    }
    return gmMainLib_8015EDC8()->x4;
}

bool fn_80173644(void)
{
    if (gmMainLib_8015EDC8()->x0 >= 0x1388) {
        return true;
    }
    return false;
}

bool fn_8017367C(void)
{
    if (!gmMainLib_8015EDC8()->x6 && gm_80164ABC() && gm_80164600()) {
        gmMainLib_8015EDC8()->x6 = true;
    }
    return gmMainLib_8015EDC8()->x6;
}

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
