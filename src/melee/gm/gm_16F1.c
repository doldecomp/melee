#include "gm_16F1.h"

#include "gm_16F1.static.h"

#include "gm_unsplit.h"

#include "if/textlib.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbtime.h>
#include <melee/pl/plbonus.h>
#include <melee/ty/toy.h>

struct lbl_804D65A8_t {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
};

struct lbl_803D6300_t {
    u16 x0;
    u16 x2;
    bool (*x4)(void);
};

struct lbl_803D6300_t lbl_803D6300[] = {
    { 0x0016, 0xFFFF, fn_801735F0 },
    { 0x0017, 0x0001, fn_80173644 },
    { 0x0018, 0xFFFF, fn_80173510 },
    { 0x0019, 0xFFFF, NULL },
    { 0x001A, 0xFFFF, NULL },
    { 0x001B, 0xFFFF, fn_8017367C },
    { 0x001C, 0xFFFF, gm_80164ABC },
    { 0x001D, 0xFFFF, gm_80164600 },
    { 0x001E, 0x0040, fn_80162CCC },
    { 0x001F, 0x0040, gm_80162EC8 },
    { 0x0020, 0x0040, fn_801630C4 },
    { 0x0021, 0x0040, gm_80162D1C },
    { 0x0022, 0x0040, gm_80162F18 },
    { 0x0023, 0x0040, gm_80163114 },
    { 0x0024, 0x0010, fn_801722BC },
    { 0x0025, 0x0010, fn_801722F4 },
    { 0x0026, 0x0080, gmMainLib_8015D508 },
    { 0x0027, 0x0020, fn_80163D24 },
    { 0x0028, 0x0020, fn_80163D74 },
    { 0x0029, 0x0040, fn_8017232C },
    { 0x002A, 0x0040, fn_80172428 },
    { 0x002B, 0x0040, fn_80172380 },
    { 0x002C, 0x0040, fn_80172478 },
    { 0x002D, 0x0040, fn_801723D4 },
    { 0x002E, 0x0040, fn_801724C8 },
    { 0x002F, 0x0001, fn_801724D0 },
    { 0x0030, 0x0001, fn_80172504 },
    { 0x0031, 0x0001, fn_80172538 },
    { 0x0032, 0x0001, fn_8017256C },
    { 0x0033, 0x0001, fn_801725A8 },
    { 0x0034, 0x0001, fn_801725E4 },
    { 0x0035, 0x0001, fn_80172624 },
    { 0x0036, 0x0001, fn_80172664 },
    { 0x0037, 0xFFFF, fn_80172698 },
    { 0x0038, 0xFFFF, fn_801726CC },
    { 0x0039, 0xFFFF, fn_80172700 },
    { 0x003A, 0xFFFF, fn_80172734 },
    { 0x003B, 0xFFFF, fn_80172768 },
    { 0x003C, 0xFFFF, un_80304470 },
    { 0x003D, 0xFFFF, un_80304510 },
    { 0x0041, 0x0010, gmMainLib_8015CF94 },
    { 0x0042, 0x0000, NULL },
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

void fn_80171B64(struct lbl_804D65A8_t* arg0)
{
    arg0->x0 = lbl_804D65A8[0];
    arg0->x1 = lbl_804D65A8[1];
    arg0->x2 = lbl_804D65A8[2];
    arg0->x3 = lbl_804D65A8[3];
    arg0->x4 = lbl_804D65A8[4];
    arg0->x5 = lbl_804D65A8[5];
    arg0->x6 = (u8) lbl_804D65B0;
}

/// #fn_80171BA4

/// #fn_80171DC4

bool gm_801720B4(void)
{
    if (gm_8016B3D8()) {
        return fn_8017E160();
    }
    return gm_8016AE50()->is_teams == true;
}

bool gm_801720F8(void)
{
    if (gm_8016B3D8()) {
        return true;
    }
    return gm_8016AE50()->x0_0 == 1;
}

int gm_80172140(void)
{
    Unk1PData* temp_r3 = fn_8017DF28();
    if (temp_r3 != NULL) {
        return temp_r3->xC.x10;
    }
    return 0;
}

void gm_80172174(void)
{
    /// @todo create struct of size 0x4D8 returned by gmMainLib_8015CCE4
    memzero(gmMainLib_8015CCE4(), 0x4D8);
}

bool gm_8017219C(u32 arg0)
{
    if (gmMainLib_8015D94C(arg0) != 0 && gmMainLib_8015D8D8(arg0) != 0) {
        return true;
    }
    return false;
}

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

bool fn_8017232C(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (*gmMainLib_8015D194(i) == 4) {
            return true;
        }
    }
    return false;
}

bool fn_80172380(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (*gmMainLib_8015D2BC(i) == 4) {
            return true;
        }
    }
    return false;
}

bool fn_801723D4(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (*gmMainLib_8015D3E4(i) == 4) {
            return true;
        }
    }
    return false;
}

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

#pragma push
#pragma dont_inline on
int gm_80172898(u16 arg0)
{
    s32 var_r3;
    int i;
    int count = 0;

    for (i = 0; i < 0x42; i++) {
        if (!gmMainLib_8015D94C(i) && fn_8017279C(i, arg0) != 0) {
            var_r3 = gmMainLib_8015D818(i);
        } else {
            var_r3 = 0;
        }
        if (var_r3 != 0) {
            count++;
        }
    }
    if (un_803048C0(0xE6) > 0 && gmMainLib_8015D94C(0x3F) == 0) {
        gmMainLib_8015D818(0x3F);
    }
    if (un_803048C0(0xC9) > 0 && gmMainLib_8015D94C(0x40) == 0) {
        gmMainLib_8015D818(0x40);
    }
    fn_8017280C();
    return count;
}
#pragma pop

void gm_8017297C(void)
{
    int i;
    for (i = 0; i < 0x42; i++) {
        if (gmMainLib_8015D94C(i) == 0) {
            u32* temp_r31 = gmMainLib_8015D804(i);
            *temp_r31 = lbTime_8000AFBC();
            gmMainLib_8015D8FC(i);
            gmMainLib_8015D8B0(i);
        }
    }
}

static inline bool inline3(int i)
{
    struct lbl_803D6300_t* cur;
    for (cur = lbl_803D6300; cur->x0 != 0x42; cur++) {
        if (cur->x0 == i && (int) cur->x2 != 0) {
            if (cur->x4 == NULL) {
                return false;
            } else {
                return !cur->x4();
            }
        }
    }
    return false;
}

void gm_801729EC(void)
{
    bool var_r0;
    int i;
    int j;
    u8 temp_r30;

    for (i = 0; i < 0x42; i++) {
        if (inline3(i)) {
            u32* tmp = gmMainLib_8015D804(i);
            *tmp = 0;
            gmMainLib_8015D8B0(i);
            gmMainLib_8015D924(i);
        }
    }

    for (i = 0; i < 11; i++) {
        if (gm_80164840(fn_801606A8(i)) == 0) {
            gmMainLib_8015D924(fn_80160710(i));
        }
    }

    for (i = 0; i < 11; i++) {
        u16* tmp;
        temp_r30 = fn_801607A8(i);
        tmp = gmMainLib_8015EDA4();
        if (!(*tmp & (1 << i))) {
            gmMainLib_8015D924((u32) fn_801607F4(temp_r30));
        }
    }

    if (un_803048C0(0xE6) == 0) {
        u32* tmp = gmMainLib_8015D804(0x3F);
        *tmp = 0;
        gmMainLib_8015D8B0(0x3FU);
        gmMainLib_8015D924(0x3FU);
    }
    if (un_803048C0(0xC9) == 0) {
        u32* tmp = gmMainLib_8015D804(0x40);
        *tmp = 0;
        gmMainLib_8015D8B0(0x40U);
        gmMainLib_8015D924(0x40U);
    }
    if (un_803048C0(0x96) == 0) {
        u32* tmp = gmMainLib_8015D804(0x1A);
        *tmp = 0;
        gmMainLib_8015D8B0(0x1AU);
        gmMainLib_8015D924(0x1AU);
    }
    fn_8017280C();
}

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

void gm_80172C44(u32 arg0)
{
    gmMainLib_8015DA68(arg0);
    gmMainLib_8015D984(arg0);
}

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

static const struct lbl_803B7AD0_t {
    u8 x0;
    u8 x1;
    u8 x2;
    u16 x4;
} lbl_803B7AD0[0xB] = {
    { 0, 5, 2, 0x3E8 }, { 1, 5, 2, 0x320 },  { 2, 5, 2, 0x190 },
    { 3, 5, 2, 0x2BC }, { 4, 5, 2, 0x032 },  { 5, 5, 2, 0x12C },
    { 6, 5, 2, 0x1F4 }, { 7, 5, 2, 0x064 },  { 8, 5, 2, 0x384 },
    { 9, 5, 2, 0x0C8 }, { 10, 5, 2, 0x258 },
};

static inline const struct lbl_803B7AD0_t* inline2(u8 arg0)
{
    int i;
    u8 temp_r3 = gm_80160638(arg0);
    const struct lbl_803B7AD0_t* tmp = lbl_803B7AD0;
    for (i = 0; i < 0xB; i++) {
        if (temp_r3 == tmp[i].x0) {
            return &tmp[i];
        }
    }
    return NULL;
}

u8 gm_80172CC0(u8 arg0, u8 arg1)
{
    int var_r0;
    const struct lbl_803B7AD0_t* var_r31 = inline2(arg0);

    var_r0 = var_r31->x1 - var_r31->x2 * gmMainLib_8015DB6C(gm_80160638(arg0));
    if (var_r0 < 0) {
        var_r0 = 0;
    } else if (var_r0 > 9) {
        var_r0 = 9;
    }
    return var_r0;
}

u8 gm_80172D78(void)
{
    u32* temp_r31 = &gmMainLib_8015ED98()->x4;
    if (!gm_80164840(CKIND_MEWTWO) && *temp_r31 >= 0x11940) {
        return CKIND_MEWTWO;
    }
    return CHKIND_NONE;
}

static inline const struct lbl_803B7AD0_t* inline1(u32 arg0)
{
    const struct lbl_803B7AD0_t* var_r29 = NULL;
    u16 var_r30 = -1;
    int i;
    for (i = 0; i < 0xB; i++) {
        if (lbl_803B7AD0[i].x4 <= arg0 &&
            !gm_80164840(fn_801606A8(lbl_803B7AD0[i].x0)))
        {
            if (lbl_803B7AD0[i].x4 < var_r30) {
                var_r30 = lbl_803B7AD0[i].x4;
                var_r29 = &lbl_803B7AD0[i];
            }
        }
    }
    return var_r29;
}

u8 gm_80172DD4(u32 arg0)
{
    const struct lbl_803B7AD0_t* var_r29 = inline1(arg0);
    PAD_STACK(8);
    if (var_r29 != NULL) {
        return fn_801606A8(var_r29->x0);
    }
    return CHKIND_NONE;
}

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

bool fn_80172FAC(void)
{
    int j;
    bool var_r31 = true;
    int i;

    for (j = 0; j < 0x19; j++) {
        if (j != 3 && gmMainLib_8015D4A8(j) == 0) {
            var_r31 = false;
            break;
        }
    }
    if (var_r31) {
        return true;
    }

    var_r31 = true;
    for (i = 0; i < 0x19; i++) {
        if (i != 3 && gmMainLib_8015D0F4(i) == 0) {
            var_r31 = false;
            break;
        }
    }
    if (var_r31) {
        return true;
    }

    var_r31 = true;
    for (i = 0; i < 0x19; i++) {
        if (i != 3 && gmMainLib_8015D21C(i) == 0) {
            var_r31 = false;
            break;
        }
    }
    return var_r31;
}

u8 fn_80173098(int arg0)
{
    Unk1PData* temp_r3;
    UnkAdventureData* temp_r31;
    int var_r31;
    int i;

    temp_r3 = fn_8017DEC8(arg0);
    if (temp_r3->xC.xD == 0) {
        if (temp_r3->ckind == CKIND_MARS && !gm_80164840(CKIND_EMBLEM)) {
            return CKIND_EMBLEM;
        }
        if (temp_r3->ckind == CKIND_MARIO && !gm_80164840(CKIND_DRMARIO)) {
            return CKIND_DRMARIO;
        }
    }
    var_r31 = 0;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D0F4(i) != 0) {
            var_r31++;
        } else if (gmMainLib_8015D21C(i) != 0) {
            var_r31++;
        } else if (gmMainLib_8015D344(i) != 0) {
            var_r31++;
        }
    }
    if (var_r31 >= 10 && !gm_80164840(CKIND_CLINK)) {
        return CKIND_CLINK;
    }
    if (fn_80172FAC() && !gm_80164840(CKIND_GAMEWATCH)) {
        return CKIND_GAMEWATCH;
    }
    if (arg0 == 0) {
        temp_r31 = gm_8017E424();
        if (!gm_80164840(CKIND_LUIGI) && temp_r31->x74 != 0 &&
            temp_r31->x75 != 0)
        {
            return CKIND_LUIGI;
        }
    }
    if (!gm_80164840(CKIND_PURIN)) {
        return CKIND_PURIN;
    }
    return CHKIND_NONE;
}

u8 gm_80173224(int arg0, int arg1)
{
    u8 var_r4 = CHKIND_NONE;
    if (arg1 != 0) {
        var_r4 = fn_80173098(arg0);
    }
    if (var_r4 == CHKIND_NONE) {
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

u8 gm_801733D8(void)
{
    if (!gm_80164840(CKIND_GAMEWATCH) && fn_80172FAC()) {
        return CKIND_GAMEWATCH;
    }
    return CHKIND_NONE;
}

u16 gm_8017341C(void)
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
    return 0x148;
}

u16 gm_801734D0(u32 arg0)
{
    if (arg0 >= 0x9C40 && !gm_80164430(0x1D)) {
        return 0x1D;
    }
    return 0x148;
}

bool fn_80173510(void)
{
    u16* temp_r31 = gmMainLib_8015EDA4();
    bool var_r30 = true;
    int i;

    if (gmMainLib_8015EDC8()->x5 == 0) {
        for (i = 0; i < 11; i++) {
            if (i != 6 && i != 7 && i != 8 && i != 9 && i != 10 &&
                !(*temp_r31 & (1LL << i)))
            {
                var_r30 = false;
                break;
            }
        }
        if (var_r30 != 0) {
            gmMainLib_8015EDC8()->x5 = true;
        }
    }
    return gmMainLib_8015EDC8()->x5;
}

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
        gm_801A42E8(MJ_CHALLENGER_APPROACH);
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
        gm_SetSceneMinor(2);
    } else {
        gm_SetSceneMinor(0);
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
        if (gm_801A4310() == MJ_15MIN_VS) {
            fn_80172C78(0x50);
        }
        if (gm_801A4310() == MJ_100MAN_VS && arg2 <= 0x3840) {
            fn_80172C78(0x4E);
        }
        if (gm_801A4310() == MJ_15MIN_VS) {
            fn_80172C78(0x50);
        }
    }
    if (gm_801A4310() == MJ_ENDLESS_VS && arg1 >= 100) {
        fn_80172C78(0x4F);
    }
    if (gm_801A4310() == MJ_CRUEL_VS && arg1 >= 5) {
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
    u8 ckind;
    u16* temp_r29;

    for (i = 0; i < 0x19; i++) {
        temp_r29 = &gmMainLib_8015EDBC()->x18[i];
        if (*temp_r29 >= 100) {
            ckind = gm_8016400C(i);
            fn_80172C78(gm_80160474(ckind, MJ_CLASSIC));
            if (ckind == CKIND_ZELDA) {
                fn_80172C78(gm_80160474(CKIND_SEAK, MJ_CLASSIC));
            }
            if (ckind == CKIND_SEAK) {
                fn_80172C78(gm_80160474(CKIND_ZELDA, MJ_CLASSIC));
            }
        }
        if (*temp_r29 >= 200) {
            ckind = gm_8016400C(i);
            fn_80172C78(gm_80160474(ckind, MJ_ADVENTURE));
            if (ckind == CKIND_ZELDA) {
                fn_80172C78(gm_80160474(CKIND_SEAK, MJ_ADVENTURE));
            }
            if (ckind == CKIND_SEAK) {
                fn_80172C78(gm_80160474(CKIND_ZELDA, MJ_ADVENTURE));
            }
        }
        if (*temp_r29 >= 300) {
            ckind = gm_8016400C(i);
            fn_80172C78(gm_80160474(ckind, MJ_ALLSTAR));
            if (ckind == CKIND_ZELDA) {
                fn_80172C78(gm_80160474(CKIND_SEAK, MJ_ALLSTAR));
            }
            if (ckind == CKIND_SEAK) {
                fn_80172C78(gm_80160474(CKIND_ZELDA, MJ_ALLSTAR));
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
