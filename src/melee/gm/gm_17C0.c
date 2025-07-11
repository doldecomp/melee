#include "gm_17C0.h"

#include "gm_1601.h"

#include "gm_1601.static.h"

#include <melee/cm/camera.h>
#include <melee/ef/eflib.h>
#include <melee/ef/efasync.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00F9.h>
#include <melee/mp/mpcoll.h>

struct lbl_803D9D20_t {
    /*  +0 */ char pad_0[0xB0];
    /* +B0 */ HSD_CObj* cobj;
    /* +B4 */ char pad_B4[0xD8 - 0xB4];
    /* +D8 */ Vec3 eye_position;
    /* +E4 */ char pad_E4[0xEC - 0xE4];
    /* +EC */ Vec3 interest;
};

static struct lbl_803D9D20_t lbl_803D9D20;
static UNK_T lbl_80472C30[32];
static UNK_T lbl_80472CB0[30];
static struct lbl_80472D28_t lbl_80472D28;
static struct lbl_80472E48_t lbl_80472E48;
static int lbl_80472EC8[4];
static u8 lbl_80473594[0x14];
static int lbl_80473700[69];
static UNK_T gm_804771C4[349];

/// #fn_8017C0C8

/// #fn_8017C1A4

/// #fn_8017C71C

/// #fn_8017C7A0

/// #fn_8017C7EC

/// #gm_8017C838

/// #gm_8017C984

/// #gm_8017C9A8

/// #gm_8017CA38

/// #gm_8017CBAC

/// #gm_8017CD94

/// #gm_8017CE34

/// #gm_8017D7AC

/// #fn_8017D9C0

void gm_8017DB58(void* arg0)
{
    M2C_FIELD(arg0, s8*, 0) = 0x21;
    M2C_FIELD(arg0, s8*, 0xC) = 0x21;
    M2C_FIELD(arg0, s8*, 0x18) = 0x21;
}

u8 gm_8017DB6C(gm_8017DB6C_arg0_t* arg0, ssize_t index)
{
    return arg0[index].x0;
}

u8 gm_8017DB78(gm_8017DB6C_arg0_t* arg0, ssize_t index)
{
    return arg0[index].x1;
}

/// #gm_8017DB88

/// #fn_8017DD7C

/// #fn_8017DE54

/// #fn_8017DEC8

/// #fn_8017DF28

/// #fn_8017DF90

/// #gm_8017DFF4

/// #gm_8017E068

/// #fn_8017E0E4

/// #fn_8017E160

/// #fn_8017E21C

/// #gm_8017E280

/// #fn_8017E318

/// #fn_8017E3C8

UNK_T gm_8017E424(void)
{
    return &lbl_80472C30;
}

u8 gm_8017E430(void)
{
    return M2C_FIELD(&lbl_80472C30, u8*, 3);
}

/// #gm_8017E440

/// #gm_8017E48C

/// #gm_8017E4C4

/// #gm_8017E500

/// #gm_8017E528

/// #gm_8017E578

/// #gm_8017E5C8

/// #gm_8017E5FC

/// #gm_8017E630

/// #gm_8017E664

/// #gm_8017E6B4

/// #gm_8017E704

/// #gm_8017E738

/// #gm_8017E76C

/// #gm_8017E7A0

/// #gm_8017E7E0

/// #gm_8017E7FC

/// #fn_8017E8A4

UNK_T gm_8017EB30(void)
{
    return &lbl_80472CB0;
}

/// #gm_8017EB3C

/// #gm_8017EB64

/// #gm_8017EB98

/// #gm_8017EBCC

/// #gm_8017EC00

/// #gm_8017EC50

/// #gm_8017ECA0

/// #gm_8017ECD4

/// #gm_8017ED08

/// #gm_8017ED3C

/// #gm_8017ED8C

/// #fn_8017EDDC

/// #fn_8017EE40

/// #fn_8017F008

/// #fn_8017F09C

/// #fn_8017F14C

/// #fn_8017F1B8

int fn_8017F294(void)
{
    return lbl_80472D28.x104;
}

/// #fn_8017F2A4

/// #fn_8017F47C

/// #fn_8017F608

/// #fn_8017FA1C

/// #fn_8017FBA4

/// #fn_8017FE54

/// #fn_8017FF1C

/// #fn_801803FC

/// #fn_80180630

/// #fn_80180AC0

s32 gm_80180AE4(void)
{
    return lbl_80472EC8[0] * 0xA;
}

/// #gm_80180AF4

/// #gm_80180B18

/// #gm_80180BA0

/// #fn_80180C14

/// #fn_80180C60

/// #fn_80181598

/// #fn_80181708

/// #gm_80181998

void gm_80181A00(s32 arg0, s32 arg1)
{
    lbl_80472E48.unk_4 = arg0;
    lbl_80472E48.unk_8 = arg1;
}

u8 gm_80181A14(void)
{
    return *lbl_80473594;
}

u16 gm_80181A24(void)
{
    return M2C_FIELD(&lbl_80473594, u16*, 2);
}

s32 gm_80181A34(void)
{
    return M2C_FIELD(&lbl_80473594, s32*, 4);
}

/// #gm_80181A44

/// #gm_80181AC8

/// #gm_80181B64

/// #fn_80181BFC

/// #fn_80181C80

/// #fn_80181E18

/// #gm_80182174

/// #gm_80182510

/// #gm_80182554

/// #gm_80182578

/// #fn_80182B5C

/// #gm_80182DF0

/// #fn_80182F40

/// #gm_80183218

/// #fn_8018325C

/// #fn_80184138

/// #fn_801849E0

/// #fn_80184A04

/// #fn_80184A28

/// #fn_80184A4C

/// #fn_80184A70

/// #fn_80184A94

/// #fn_80184AB8

/// #fn_8018504C

/// #fn_801851C0

/// #fn_801852FC

/// #fn_80185408

/// #fn_801855BC

/// #fn_8018564C

/// #fn_8018569C

/// #fn_8018575C

/// #fn_801857C4

/// #fn_801859C8

/// #fn_80185A0C

/// #fn_80185D64

/// #fn_80185E34

/// #fn_80185F5C

/// #fn_80186080

/// #fn_801861B8

/// #fn_80186400

/// #fn_80186634

/// #gm_80186DFC_OnFrame

/// #gm_80186E30_OnEnter

/// #fn_80186EFC

/// #fn_80186F6C

/// #fn_801873F0

/// #fn_80187494

/// #fn_801874FC

void fn_80187714(void)
{
    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(64);
    Stage_802251E8(0, NULL);
    Stage_8022524C();
    Item_80266FA8();
    Item_80266FCC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
}

/// #gm_8018776C_OnFrame

/// #gm_801877A8_OnEnter

/// #fn_80187910

/// #fn_80187AB4

/// #fn_80187C9C

/// #fn_80187CF4

/// #gm_80187F48_OnEnter

/// #gm_80188364_OnLeave

/// #gm_8018838C_OnFrame

/// #gm_801883C0

/// #gm_8018841C

int gm_80188454(int idx)
{
    return lbl_80473700[idx + 2];
}

/// #fn_8018846C

/// #fn_801884F8

/// #fn_80188550

/// #fn_80188644

/// #fn_80188738

/// #fn_80188910

/// #fn_80188B3C

/// #fn_80188D3C

/// #fn_80188EE8

/// #fn_801891F4

/// #fn_80189B88

/// #gm_80189CDC

/// #fn_8018A000

/// #gm_8018A160

/// #gm_8018A188

/// #gm_8018A1D8

/// #gm_8018A228

/// #gm_8018A25C

/// #gm_8018A290

/// #gm_8018A2C4

/// #gm_8018A314

/// #fn_8018A364

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

s32 fn_8018F62C(void* arg0)
{
    return M2C_FIELD(arg0, s32*, 0x2C);
}

UNK_T gm_8018F634(void)
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
