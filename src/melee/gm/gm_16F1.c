#include "gm_1601.h"

#include "gm_16F1.static.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lblanguage.h>
#include <melee/pl/plbonus.h>
#include <melee/lb/lb_00B0.h>
#include <melee/un/un_2FC9.h>

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

/// #gm_801721EC

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

/// #fn_801724D0

/// #fn_80172504

/// #fn_80172538

/// #fn_8017256C

/// #fn_801725A8

/// #fn_801725E4

/// #fn_80172624

/// #fn_80172664

/// #fn_80172698

/// #fn_801726CC

/// #fn_80172700

/// #fn_80172734

/// #fn_80172768

/// #fn_8017279C

/// #fn_8017280C

/// #gm_80172898

/// #gm_8017297C

/// #gm_801729EC

/// #gm_80172BC4

/// #gm_80172C04

/// #gm_80172C44

/// #fn_80172C78

/// #gm_80172CC0

/// #gm_80172D78

/// #gm_80172DD4

/// #gm_80172E74

/// #gm_80172F00

/// #fn_80172FAC

/// #fn_80173098

/// #gm_80173224

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
        if (i != 0x29 && i - 0x42 > 1U && i != 0xB9 &&
            i - 0xC9 > 1U && i != 9 && gmMainLib_8015DADC(i) == 0) {
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

/// #gm_80174180

/// #gm_801741FC

/// #gm_80174238
