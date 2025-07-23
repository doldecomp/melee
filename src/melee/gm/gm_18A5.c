#include "gm_18A5.h"

#include <melee/gm/types.h>

/* 4D4190 */ static s32 lbl_804D4190 = 0xFFFFFFFF;

static TmData gm_804771C4;

struct lbl_803D9D20_t {
    /*  +0 */ char pad_0[0xB0];
    /* +B0 */ HSD_CObj* cobj;
    /* +B4 */ char pad_B4[0xD8 - 0xB4];
    /* +D8 */ Vec3 eye_position;
    /* +E4 */ char pad_E4[0xEC - 0xE4];
    /* +EC */ Vec3 interest;
};

static struct lbl_803D9D20_t lbl_803D9D20 = { 0 };

/// #fn_8018A514

/// #fn_8018A970

/// #fn_8018AA74

/// #fn_8018B090

/// #fn_8018C8D4

/// #fn_8018D50C

/// #fn_8018DC18

/// #fn_8018DF68

/// #fn_8018E46C

/// #fn_8018E618

/// #fn_8018E85C

/// #fn_8018EC48

/// #fn_8018EC7C

/// #fn_8018ECA8

/// #fn_8018F00C

/// #gm_8018F1B0

/// #fn_8018F310

u8 fn_8018F3BC(s32 arg0)
{
    return M2C_FIELD(&lbl_803D9D20.pad_0[arg0], u8*, 0x59);
}

/// #fn_8018F3D0

/// #fn_8018F410

/// #fn_8018F4A0

/// #fn_8018F508

/// #fn_8018F5F0

s32 fn_8018F62C(HSD_GObj* arg0)
{
    return M2C_FIELD(arg0, s32*, 0x2C);
}

TmData* gm_8018F634(void)
{
    return &gm_804771C4;
}

/// #fn_8018F640

/// #fn_8018F674

/// #fn_8018F6A8

/// #fn_8018F6DC

/// #fn_8018F6FC

/// #fn_8018F71C

/// #fn_8018F74C

/// #fn_8018F808

/// #fn_8018F888

/// #fn_8018FA24

void fn_8018FBD8(void* arg0, s32 arg1)
{
    M2C_FIELD(arg0, s32*, 0x2C) = arg1;
}

/// #fn_8018FBE0

/// #fn_8018FDC4

/// #fn_8018FF9C

/// #fn_80190174

/// #fn_801901F8

/// #fn_8019027C

/// #fn_801902F0

/// #fn_8019035C

/// #fn_8019044C

/// #fn_80190480

void fn_801904D0(void)
{
    HSD_CObjSetInterest(lbl_803D9D20.cobj, &lbl_803D9D20.interest);
    HSD_CObjSetEyePosition(lbl_803D9D20.cobj, &lbl_803D9D20.eye_position);
}

/// #fn_80190520

/// #gm_801905F0

/// #fn_80190ABC

/// #gm_80190EA4

/// #gm_80190FE4

/// #fn_801910E0

/// #fn_80191154

/// #fn_80191240

/// #fn_801913BC

/// #fn_80191678

/// #fn_8019175C

/// #fn_801918F0

/// #fn_80191A54

/// #fn_80191B5C

/// #fn_80191CA4

/// #fn_80191D38

/// #fn_80191E9C

/// #fn_80191FD4

/// #fn_8019237C

/// #fn_8019249C

/// #fn_80192690

/// #fn_80192758

/// #fn_80192938

/// #fn_80192BB0

/// #fn_80192E6C

/// #fn_80193230

/// #fn_80193308

/// #fn_801935B8

/// #fn_801937C4

/// #fn_80193B58

/// #fn_80193FCC

/// #fn_80194658

/// #fn_801949B4

/// #fn_80194BC4

/// #fn_80194D84

/// #fn_80194F30

/// #fn_801953C8

/// #fn_80195AF0

/// #fn_80195CCC

/// #fn_8019610C

/// #gm_8019628C_OnFrame

/// #gm_801963B4_OnEnter

/// #gm_801964A4_OnLeave

/// #fn_80196510

s32 fn_8019655C(void)
{
    return lbl_804D4190;
}

/// #fn_80196564

/// #fn_80196594

/// #fn_801965C4

/// #fn_80196684

/// #fn_801967E0

/// #fn_80196CF8

/// #fn_80196DBC

/// #fn_80196E30

/// #fn_80196EEC

/// #fn_80196FFC

/// #fn_801973F8

/// #fn_801975C8

/// #fn_801976D4

/// #fn_801977AC

/// #fn_80197AF0

/// #fn_80197D4C

/// #fn_80197E18

/// #fn_80197FD8

/// #fn_801981A0

/// #fn_801983E4

/// #fn_80198584

/// #fn_801985D4

/// #fn_80198824

/// #fn_80198BA0

/// #fn_80198C60

/// #fn_80198D18

/// #fn_80198EBC

/// #fn_80199AF0

/// #fn_8019A158

/// #fn_8019A71C

/// #gm_8019A828

/// #fn_8019A86C

/// #fn_8019AF50

/// #gm_8019B2DC_OnFrame

/// #fn_8019B458

/// #fn_8019B81C

/// #fn_8019B860
