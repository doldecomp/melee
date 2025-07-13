#include "gm_1B03.h"

#include <melee/db/db.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/gm/types.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbsnap.h>
#include <melee/mn/mngallery.h>
#include <melee/mn/types.h>
#include <sysdolphin/baselib/memory.h>

/* 49C178 */ static s8 gm_8049C178[16];
/* 49E548 */ static struct gm_8049E548_t gm_8049E548;

/// #gm_801B0348

/// #gm_801B0474

/// #gm_801B05F4

/// #gm_801B0620

/// #gm_801B0664

/// #gm_801B06B0

/// #gm_801B0730

/// #gm_801B07B4

/// #gm_801B07E8

/// #gm_801B087C

void gm_801B089C(MinorScene* scene)
{
    int* temp_r3 = gm_801A4284(scene);
    if (g_debugLevel >= 3) {
        if (*temp_r3 & 0x100) {
            gm_801A42E8(0xE);
        } else if (*temp_r3 & 0x1000) {
            gm_80173EEC();
            gm_80172898(0x100);
            if (gm_80173754(1, 0) == 0) {
                gm_801A42E8(1);
            }
        } else if (*temp_r3 & 0x400) {
            gm_801A42E8(7);
        } else if (*temp_r3 & 0x800) {
            gm_801A42E8(6);
        } else {
            gm_801BF708(1);
            gm_801A42E8(0x18);
        }
    } else if (*temp_r3 & 0x1000) {
        gm_80173EEC();
        gm_80172898(0x100);
        if (gm_80173754(1, 0) == 0) {
            gm_801A42E8(1);
        }
    } else {
        gm_801BF708(1);
        gm_801A42E8(0x18);
    }
    gm_801A42D4();
}

/// #gm_801B099C

/// #gm_801B09C0

/// #fn_801B09F8

/// #gm_801B0A34

/// #fn_801B0A8C

/// #gm_801B0AC8

/// #gm_801B0B00

/// #gm_801B0B24

/// #gm_801B0B48

/// #gm_801B0B8C

/// #gm_801B0BF0

/// #gm_801B0C18

/// #gm_801B0C50

/// #gm_801B0C74

/// #gm_801B0CF0

/// #gm_801B0DD0

/// #gm_801B0F1C

/// #gm_801B0F60

/// #gm_801B0F90

/// #gm_801B0FB8

void gm_801B0FF8(struct gm_801B0FF8_arg0_t* arg0)
{
    GameRules* temp_r3;
    struct gm_801B0FF8_arg0_x10_t* temp_r31;
    u8 var_r0;
    Unk80433380_48* temp_r30;

    temp_r31 = arg0->x10;
    lb_8001C550();
    lb_8001D164(0);
    temp_r30 = HSD_MemAlloc(lbSnap_8001E210());
    lbSnap_8001E218(HSD_MemAlloc(lbSnap_8001E204()), temp_r30);
    {
        ssize_t i;
        for (i = 0; i < (signed) ARRAY_SIZE(mnGallery_804A0B90); i++) {
            mnGallery_804A0B90[i] =
                HSD_MemAlloc(sizeof(struct mnGallery_804A0B90_t));
        }
    }
    lbDvd_80018C6C();
    lbDvd_8001823C();
    lbDvd_80018254();
    mnGallery_80258940();
    temp_r3 = gmMainLib_8015CC34();
    if (temp_r3->unk_x0 != 0) {
        temp_r3->unk_x0 = 0;
        temp_r31->x0 = 0;
        temp_r31->x1 = 0;
        temp_r31->x2 = 1;
        return;
    }
    temp_r31->x2 = 1;
    var_r0 = gm_801A4320();
    if (var_r0 == 0x14) {
        var_r0 = gm_801737D8();
    }
    switch (var_r0) {
    case 3:
        temp_r31->x0 = 6;
        temp_r31->x1 = 0;
        return;
    case 4:
        temp_r31->x0 = 6;
        temp_r31->x1 = 1;
        return;
    case 5:
        temp_r31->x0 = 6;
        temp_r31->x1 = 2;
        return;
    case 21:
        temp_r31->x0 = 6;
        temp_r31->x1 = 0;
        return;
    case 22:
        temp_r31->x0 = 6;
        temp_r31->x1 = 1;
        return;
    case 23:
        temp_r31->x0 = 6;
        temp_r31->x1 = 2;
        return;
    case 43:
        temp_r31->x0 = 7;
        temp_r31->x1 = 0;
        return;
    case 15:
        temp_r31->x0 = 9;
        temp_r31->x1 = 0;
        return;
    case 33:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 0;
        return;
    case 34:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 1;
        return;
    case 35:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 2;
        return;
    case 36:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 3;
        return;
    case 37:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 4;
        return;
    case 38:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 5;
        return;
    case 32:
        temp_r31->x0 = 9;
        temp_r31->x1 = 1;
        return;
    case 28:
        temp_r31->x0 = 1;
        temp_r31->x1 = 4;
        return;
    case 2:
        temp_r31->x0 = 2;
        temp_r31->x1 = 0;
        return;
    case 27:
        temp_r31->x0 = 2;
        temp_r31->x1 = 1;
        return;
    case 10:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 0;
        return;
    case 31:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 1;
        return;
    case 16:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 2;
        return;
    case 30:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 3;
        return;
    case 29:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 4;
        return;
    case 17:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 5;
        return;
    case 18:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 9;
        return;
    case 19:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 8;
        return;
    case 42:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 6;
        return;
    case 44:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 7;
        return;
    case 11:
        temp_r31->x0 = 3;
        temp_r31->x1 = 0;
        return;
    case 12:
        temp_r31->x0 = 3;
        temp_r31->x1 = 1;
        return;
    case 13:
        temp_r31->x0 = 3;
        temp_r31->x1 = 3;
        return;
    case 1:
        temp_r31->x0 = 4;
        temp_r31->x1 = 4;
        return;
    default:
        temp_r31->x0 = 0;
        temp_r31->x1 = 0;
        return;
    }
}

/// #gm_801B138C

/// #gm_801B13B8

/// #gm_801B14A0

/// #gm_801B14DC

/// #gm_801B1514

/// #gm_801B154C

/// #gm_801B1588

/// #gm_801B15C8

/// #gm_801B1648

/// #gm_801B1688

/// #gm_801B16A8

/// #gm_801B16C8

/// #gm_801B1724

/// #gm_801B174C

/// #gm_801B1788

/// #gm_801B1810

/// #gm_801B1834

/// #gm_801B18D4

/// #gm_801B1A2C

/// #gm_801B1A84

/// #gm_801B1AD4

/// #gm_801B1B74

/// #gm_801B1C24

/// #gm_801B1EB8

/// #gm_801B1EEC

void fn_801B1F6C(void) {}

/// #gm_801B1F70

/// #gm_801B2204

/// #gm_801B2298_OnInit

/// #gm_801B23C4_OnLoad

/// #gm_801B23F0

/// #gm_801B24B4

/// #gm_801B2510

/// #gm_801B254C

/// #gm_801B25D4

/// #gm_801B26AC

/// #gm_801B2704

/// #gm_801B2790

/// #gm_801B2AF8

/// #gm_801B2B7C_OnInit

/// #gm_801B2BA4

/// #gm_801B2D54

/// #gm_801B2F78_OnLoad

void gm_801B34B8_OnInit(void)
{
    u8* temp_r3 = gmMainLib_8015CDC8();
    temp_r3[0] = 0x21;
    temp_r3[2] = 0;
    temp_r3[1] = 3;
    temp_r3[3] = 0;
    temp_r3[4] = 0x78;
    temp_r3[5] = 0;
}

/// #gm_801B3500

/// #gm_801B3A34

/// #gm_801B3B40

/// #gm_801B3D44

/// #gm_801B3D84

/// #gm_801B3DD8

/// #gm_801B3E44

/// #gm_801B3F18

/// #gm_801B3F40

/// #gm_801B4064

/// #gm_801B4170

/// #gm_801B4254

/// #gm_801B4294

/// #gm_801B42E8

/// #gm_801B4350

/// #gm_801B4408

/// #gm_801B4430

/// #gm_801B44A0

/// #gm_801B45A4

/// #gm_801B461C

/// #gm_801B4684

/// #gm_801B4768

/// #gm_801B47FC

/// #gm_801B4860

/// #gm_801B4974

/// #gm_801B4B28

/// #gm_801B4C5C

/// #gm_801B4D34

/// #gm_801B4DAC

/// #gm_801B4E58

/// #gm_801B4EB8

/// #gm_801B4F44

/// #gm_801B4FCC

/// #gm_801B5078

/// #gm_801B50C4

/// #gm_801B518C

/// #gm_801B51CC_OnInit

/// #gm_801B5214_OnLoad

/// #gm_801B5324

/// #gm_801B5624

/// #gm_801B59AC

/// #fn_801B5AA8

/// #gm_801B5ACC

/// #gm_801B5E7C

/// #gm_801B5EB4

/// #gm_801B5EE4

/// #gm_801B5F50

/// #gm_801B5FB4

/// #gm_801B607C

/// #gm_801B60A4_OnLoad

/// #gm_801B62D8_OnInit

UNK_T gm_801B6320(void)
{
    return &gmMainLib_804D3EE0->unk_584;
}

/// #gm_801B632C

/// #gm_801B63C4

/// #gm_801B6428

/// #gm_801B65D4

/// #gm_801B67E8_OnInit

/// #gm_801B6808_OnLoad

/// #gm_801B6834

/// #gm_801B685C

/// #gm_801B688C

/// #gm_801B69C0

/// #gm_801B6AD8

/// #gm_801B6B70

/// #gm_801B6BE8

/// #gm_801B6F44

/// #gm_801B7044

/// #gm_801B70DC

/// #gm_801B7154

/// #gm_801B74F0

/// #gm_801B75F0

/// #gm_801B7688

/// #gm_801B7700

/// #gm_801B7AA0

/// #gm_801B7B74

/// #gm_801B7C0C

/// #gm_801B7C84

/// #gm_801B8024

/// #gm_801B8110

/// #gm_801B81A8

/// #gm_801B8220

/// #gm_801B8580

/// #gm_801B863C

/// #gm_801B86D4

/// #gm_801B874C

/// #gm_801B8AF8

/// #gm_801B8BB4

/// #gm_801B8BE0

/// #gm_801B8C08

/// #gm_801B8C30

void fn_801B8C5C(void* arg0)
{
    M2C_FIELD(arg0, s16*, 0x12) = 0x12C;
}

/// #gm_801B8C68

/// #gm_801B8C9C

/// #gm_801B8CC4

/// #gm_801B8CF4

/// #gm_801B8D14

/// #gm_801B8D34

/// #gm_801B8D60_OnInit

/// #gm_801B8D88_OnLoad

/// #gm_801B8DA8

/// #gm_801B8DD4

/// #gm_801B8DFC

/// #gm_801B8E24

/// #fn_801B8E50

/// #gm_801B8E74

/// #gm_801B8EA8

/// #gm_801B8ED0

/// #gm_801B8F04

/// #gm_801B8F24

/// #gm_801B8F44

/// #gm_801B8F70_OnInit

/// #gm_801B8F98_OnLoad

/// #gm_801B8FB8

/// #gm_801B8FE4

/// #gm_801B900C

/// #gm_801B9034

/// #fn_801B9060

/// #gm_801B9084

/// #gm_801B90B8

/// #gm_801B90E0

/// #gm_801B9114

/// #gm_801B9134

/// #gm_801B9154

/// #gm_801B9180_OnInit

/// #gm_801B91A8_OnLoad

/// #gm_801B91C8

/// #gm_801B922C

/// #gm_801B9254

/// #gm_801B927C

/// #gm_801B931C

/// #gm_801B9560

/// #gm_801B95B0_OnInit

/// #gm_801B95D8_OnLoad

/// #gm_801B9600

/// #fn_801B96E8

/// #gm_801B97C4

/// #fn_801B9850

/// #gm_801B98E8

/// #gm_801B999C

/// #gm_801B9A3C

/// #gm_801B9DD8

/// #gm_801B9EB8_OnInit

/// #gm_801B9EE4_OnLoad

/// #gm_801B9F10

/// #gm_801B9F3C

/// #gm_801B9F64

/// #gm_801B9F8C

void fn_801B9FB8(void* arg0)
{
    M2C_FIELD(arg0, UNK_RET(**)(UNK_PARAMS), 0x38) = gm_80165290;
}

/// #gm_801B9FC8

/// #gm_801B9FFC

/// #gm_801BA024

/// #gm_801BA058

/// #gm_801BA078

/// #gm_801BA098

/// #gm_801BA0C4_OnInit

/// #gm_801BA0EC_OnLoad

/// #gm_801BA10C

/// #gm_801BA138

/// #gm_801BA160

/// #gm_801BA188

void fn_801BA1B4(struct fn_801BA1B4_arg0_t* arg0)
{
    arg0->x2_b3 = true;
}

/// #gm_801BA1C8

/// #gm_801BA1FC

/// #gm_801BA224

/// #gm_801BA258

/// #gm_801BA278

/// #gm_801BA298

/// #gm_801BA2C4_OnInit

/// #gm_801BA2EC_OnLoad

/// #gm_801BA30C

/// #gm_801BA338

/// #gm_801BA360

/// #gm_801BA388

void fn_801BA3B4(struct fn_801BA3B4_arg0_t* arg0)
{
    arg0->xC_b4 = true;
}

/// #gm_801BA3C8

/// #gm_801BA3FC

/// #gm_801BA424

/// #gm_801BA458

/// #gm_801BA478

/// #gm_801BA498

/// #gm_801BA4C4_OnInit

/// #gm_801BA4EC_OnLoad

/// #gm_801BA50C

/// #gm_801BA538

/// #gm_801BA560

/// #gm_801BA588

void fn_801BA5B4(void* arg0)
{
    M2C_FIELD(arg0, f32*, 0x34) = 0.5f;
}

/// #gm_801BA5C0

/// #gm_801BA5F4

/// #gm_801BA61C

/// #gm_801BA650

/// #gm_801BA670

/// #gm_801BA690

/// #gm_801BA6BC_OnInit

/// #gm_801BA6E4_OnLoad

/// #gm_801BA704

/// #gm_801BA730

/// #gm_801BA758

/// #gm_801BA780

void fn_801BA7AC(void* arg0)
{
    M2C_FIELD(arg0, f32*, 0x34) = 1.25f;
}

/// #gm_801BA7B8

/// #gm_801BA7EC

/// #gm_801BA814

/// #gm_801BA848

/// #gm_801BA868

/// #gm_801BA888

/// #gm_801BA8B4_OnInit

/// #gm_801BA8DC_OnLoad

/// #gm_801BA8FC

/// #gm_801BA938

/// #gm_801BAA60

/// #gm_801BAAD0

/// #gm_801BAB40

/// #gm_801BAC9C

/// #gm_801BAD70

/// #gm_801BB758

/// #gm_801BBA60_OnInit

/// #gm_801BBB64

/// #gm_801BBEA8_OnLoad

void gm_801BBFE4_OnUnload(void) {}

/// #fn_801BBFE8

/// #gm_801BC00C

/// #gm_801BC488

/// #gm_801BC4F4

/// #gm_801BC670

/// #gm_801BC754

/// #gm_801BC9E8

/// #gm_801BCAF0

/// #gm_801BCC9C

/// #gm_801BCF20

/// #gm_801BCF40

/// #gm_801BD028

/// #gm_801BD164

/// #gm_801BD30C

/// #gm_801BD44C

/// #gm_801BD46C

/// #gm_801BD658

/// #gm_801BD7FC

/// #gm_801BD93C

/// #gm_801BDAD4

/// #gm_801BDAF4

/// #gm_801BDC08

/// #gm_801BDD44

/// #gm_801BDE94

/// #gm_801BE37C

/// #gm_801BE39C

/// #gm_801BE618

/// #gm_801BE638

/// #gm_801BEA10

/// #gm_801BEA4C

/// #gm_801BEA88

/// #gm_801BEAF0

/// #gm_801BEB2C

void gm_801BEB68(s32 arg0)
{
    M2C_FIELD(gmMainLib_804D3EE0, s32*, 0x548) = arg0;
}

void gm_801BEB74(u8 arg0)
{
    gmMainLib_804D3EE0->unk_535 = arg0;
}

u8 gm_801BEB80(void)
{
    return gmMainLib_804D3EE0->unk_535;
}

/// #gm_801BEB8C

extern u8 gm_803DF918[];

u8 gm_801BEBA8(u8 arg0)
{
    return gm_803DF918[arg0];
}

/// #gm_801BEBC0

/// #gm_801BEBF8

/// #gm_801BEC54

/// #gm_801BEC80

/// #gm_801BECA8

/// #gm_801BECD0

/// #gm_801BED14

/// #gm_801BED3C

/// #gm_801BEDA8

/// #gm_801BEE58

/// #gm_801BEE9C

/// #gm_801BEF84

void gm_801BEFA4(s8 arg0)
{
    gm_8049C178[0] = arg0;
}

u8 gm_801BEFB0(void)
{
    return gm_8049C178[0];
}

void gm_801BEFC0(s8 arg0)
{
    gm_8049C178[1] = arg0;
}

u8 gm_801BEFD0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 1);
}

void gm_801BEFE0(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 0xA) = arg0;
}

u8 gm_801BEFF0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 0xA);
}

void gm_801BF000(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 9) = arg0;
}

u8 gm_801BF010(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 9);
}

void gm_801BF020(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 8) = arg0;
}

u8 gm_801BF030(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 8);
}

void gm_801BF040(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 2) = arg0;
}

u8 gm_801BF050(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 2);
}

/// #gm_801BF060

/// #gm_801BF128

/// #gm_801BF3F8

/// #gm_801BF4DC

void gm_801BF634(s32 arg0, s8 arg1)
{
    gm_8049E548.pad_0[arg0] = arg1;
}

u8 gm_801BF648(s32 arg0)
{
    return gm_8049E548.pad_0[arg0];
}

void gm_801BF65C(s32 arg0, s8 arg1)
{
    M2C_FIELD(&gm_8049E548.pad_0[arg0], s8*, 4) = arg1;
}

u8 gm_801BF670(s32 arg0)
{
    return M2C_FIELD(&gm_8049E548.pad_0[arg0], u8*, 4);
}

void gm_801BF684(s16 arg0)
{
    gm_8049E548.unk_C = arg0;
}

u8 gm_801BF694(void)
{
    return gm_8049E548.unk_C;
}

void gm_801BF6A8(s8 arg0)
{
    gm_8049E548.unk_A = arg0;
}

u8 gm_801BF6B8(void)
{
    return gm_8049E548.unk_A;
}

void gm_801BF6C8(s8 arg0)
{
    gm_8049E548.unk_8 = arg0;
}

u8 gm_801BF6D8(void)
{
    return gm_8049E548.unk_8;
}

void gm_801BF6E8(s8 arg0)
{
    M2C_FIELD(&gm_8049E548, s8*, 9) = arg0;
}

u8 gm_801BF6F8(void)
{
    return gm_8049E548.unk_9;
}

void gm_801BF708(s8 arg0)
{
    gm_8049E548.unk_E = arg0;
}

u8 gm_801BF718(void)
{
    return gm_8049E548.unk_E;
}

/// #gm_801BF728

/// #gm_801BF834

/// #gm_801BF85C

/// #gm_801BF898

/// #gm_801BF8B8

/// #gm_801BF8D8

/// #gm_801BF8F8

/// #gm_801BF920
