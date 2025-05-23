#include <placeholder.h>

#include "gm_1601.static.h"

#include "gmmain_lib.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbtime.h"
#include "mp/mpcoll.h"

#include <m2c_macros.h>

/// #gm_801601C4

/// #gm_80160244

/// #gm_801602C0

/// #gm_801603B0

/// #fn_80160400

/// #gm_80160438

/// #gm_80160474

/// #gm_801604DC

/// #gm_80160564

/// #fn_801605EC

/// #gm_80160638

/// #fn_801606A8

/// #fn_80160710

/// #gm_8016075C

/// #fn_801607A8

/// #fn_801607F4

u8 fn_80160840(u8 arg0)
{
    if (arg0 >= 4) {
        return 4;
    }
    return arg0;
}

/// #gm_80160854

int gm_80160968(u8 arg0)
{
    return lbl_803B7864[arg0];
}

/// #gm_80160980

/// #fn_801609E0

/// #gm_80160A60

/// #gm_80160B40

/// #gm_80160C90

/// #fn_80160DE8

/// #fn_80160F58

/// #fn_80161004

/// #fn_80161154

/// #fn_80161C90

/// #fn_80162068

/// #fn_80162170

/// #gm_801623A4

/// #gm_801623D8

/// #gm_801623FC

/// #gm_8016247C

/// #gm_80162574

/// #gm_8016260C

/// #gm_8016279C

/// #gm_80162800

/// #gm_801628C4

/// #gm_80162968

/// #gm_801629B4

/// #gm_80162A00

/// #gm_80162A4C

/// #gm_80162A98

/// #gm_80162B4C

/// #gm_80162B98

/// #gm_80162BD8

/// #fn_80162BFC

/// #gm_80162C48

/// #fn_80162CCC

/// #gm_80162D1C

/// #gm_80162D6C

/// #gm_80162DD4

/// #fn_80162DF8

/// #gm_80162E44

/// #gm_80162EC8

/// #gm_80162F18

/// #gm_80162F68

/// #gm_80162FD0

/// #fn_80162FF4

/// #gm_80163040

/// #fn_801630C4

/// #gm_80163114

/// #gm_80163164

/// #gm_801631CC

/// #gm_801631F0

/// #gm_80163274

/// #gm_80163298

/// #gm_8016332C

/// #gm_80163374

/// #gm_801634D4

/// #gm_8016365C

/// #gm_80163690

/// #gm_801636D8

/// #gm_80163838

/// #gm_801639C0

/// #gm_801639F4

/// #gm_80163A3C

/// #gm_80163B9C

/// #fn_80163D24

/// #fn_80163D74

/// #gm_80163DC4

/// #gm_80163DE8

/// #gm_80163E3C

/// #gm_80163E60

/// #gm_80163EB4

/// #gm_80163ED8

/// #gm_80163F2C

/// #gm_80163F50

/// #fn_80163FA4

u8 gm_8016400C(u8 arg0)
{
    return lbl_803B7888[arg0];
}

u8 gm_80164024(u8 arg0)
{
    return lbl_803B78A4[arg0];
}

/// #gm_8016403C

/// #fn_801640B0

float fn_8016419C(u8 arg0)
{
    return lbl_803B7930[arg0 - 1].x;
}

float fn_801641B4(u8 arg0)
{
    return lbl_803B7930[arg0 - 1].y;
}

u16 gm_801641CC(u8 arg0)
{
    return lbl_803B7808[arg0];
}

/// #gm_801641E4

/// #gm_80164250

/// #fn_801642A0

/// #gm_80164330

/// #gm_80164430

/// #gm_80164504

/// #gm_80164600

/// #gm_8016468C

/// #gm_801647D0

/// #gm_801647F8

bool gm_80164840(u8 id)
{
    int i;
    u16* temp_r31;
    u8 var_r0 = 0;

    temp_r31 = gmMainLib_8015ED8C(&lbl_803B75F8);
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (lbl_803B75F8.id[id] == lbl_803B75F8.thing[i].unk1) {
            var_r0 = lbl_803B75F8.thing[i].unk0;
            break;
        }
    }
    if ((var_r0 == 11) || (*temp_r31 & (1LL << var_r0))) {
        return true;
    }
    return false;
}

/// #gm_80164910

/// #gm_80164A0C

/// Are all unlockable characters unlocked?
bool gm_80164ABC(struct gmMainLib_8015ED8C_arg0_t* arg0)
{
    u16* unlockable_character_bitfield = gmMainLib_8015ED8C(arg0);
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (!(*unlockable_character_bitfield & (1LL << i))) {
            /// @remarks Gekko codes which unlock all characters change this to
            ///          return @c true.
            return false;
        }
    }
    return true;
}

/// #fn_80164B48

/// #gm_80164F18

/// #gm_8016505C

/// #gm_80165084

/// #fn_801650E8

/// #fn_80165108

/// #fn_80165190

/// #fn_801651FC

/// #gm_80165268

/// #gm_80165290

/// #fn_801652B0

/// #fn_801652D8

/// #gm_80165388

/// #gm_801653C8

/// #fn_801653E8

/// #fn_80165418

/// #fn_801654A0

/// #fn_80165548

/// #fn_801656A8

/// #fn_8016588C

/// #fn_80165AC0

/// #fn_80165D60

/// #fn_80165E7C

/// #fn_80165FA4

/// #fn_801661E0

/// #gm_80166378

#ifdef MWERKS_GEKKO
float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
    register float x = src->x;
    asm { psq_st x, Vec3.x(dst), 1, qr3 }
    return x;
}
#else
float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
    NOT_IMPLEMENTED;
}
#endif

/// #gm_80166A98

u8 fn_80166CBC(struct fn_80166CBC_arg0_t* arg0, ssize_t index)
{
    return arg0[index].x5E;
}

/// #gm_80166CCC

/// #gm_80167140

u8 fn_80167194(void* arg0)
{
    return M2C_FIELD(arg0, u8*, 0xD);
}

/// #fn_8016719C

/// #gm_80167320

/// #gm_80167470

/// #gm_801674C4

/// #fn_8016758C

/// #fn_80167638

/// #gm_801677C0

void gm_801677E8(s8 arg0)
{
    lbl_804D6598 = arg0;
}

u8 gm_801677F0(void)
{
    return lbl_804D6598;
}

/// #gm_801677F8

/// #gm_80167858

/// #gm_801678F8

/// #gm_8016795C

/// #gm_80167A14

/// #gm_80167A64

/// #gm_80167B50

/// #gm_80167BC8

/// #gm_80167FC4

/// #gm_801685D4

/// #gm_80168638

/// #gm_80168710

/// #gm_801688AC

/// #gm_80168940

/// #gm_8016895C

/// #fn_801689E4

/// #fn_80168A6C

/// #gm_80168B34

/// #gm_80168BF8

/// #gm_80168C5C

/// #fn_80168E54

/// #fn_80168F2C

extern s16 lbl_804D659A;

void fn_80168F7C(void)
{
    lbl_804D659A = 0;
}

/// #gm_80168F88

/// #gm_80168FC4

/// #fn_80169000

/// #gm_80169238

/// #gm_80169264

/// #gm_80169290

/// #gm_801692BC

void gm_801692E8(uint ticks, struct datetime* datetime)
{
    OSCalendarTime tm;

    lbTime_8000B028(&tm, ticks);
    datetime->year = tm.year;
    datetime->month = tm.mon + 1;
    datetime->day = tm.mday;
    datetime->hour = tm.hour;
    datetime->minute = tm.min;
    if (tm.sec > 59) {
        datetime->second = 59;
    } else {
        datetime->second = tm.sec;
    }
}

UNK_T fn_80169364(void)
{
    return &lbl_8046B488;
}

u8 gm_80169370(s32 arg0)
{
    return lbl_8046B488.pad_0[arg0];
}

u8 gm_80169384(void)
{
    return M2C_FIELD(&lbl_8046B488, u8*, 7);
}

s32 gm_80169394(void)
{
    return lbl_8046B488.unk_10_b3;
}

s32 fn_801693A8(void)
{
    return lbl_8046B488.unk_10_b2;
}

/// #gm_801693BC

void fn_80169434(s32 arg0)
{
    M2C_FIELD(&lbl_8046B488, s32*, 0x1B8) = arg0;
}

/// #fn_80169444

/// #gm_801694A0

UNK_T gm_80169520(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0x20);
}

UNK_T gm_80169530(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0xA2);
}

UNK_T gm_80169540(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0x124);
}

/// #fn_80169550

/// #fn_80169574

/// #fn_801695BC

/// #fn_801697FC

/// #fn_8016989C

/// #fn_80169900

/// #fn_80169A84

/// #fn_80169C54

/// #fn_80169F50

/// #fn_8016A09C

/// #gm_8016A164

s32 fn_8016A1E4(void)
{
    return lbl_8046B488.unk_10_b0;
}

/// #gm_8016A1F8

void gm_8016A21C(UNK_T arg0)
{
    M2C_FIELD(arg0, struct lbl_8046B488_t**, 0x54) = &lbl_8046B488;
}

/// #gm_8016A22C

void gm_8016A404(s32 arg0)
{
    M2C_FIELD(&lbl_8046B488, s32*, 0x1BC) = arg0;
}

void gm_8016A414(f32 arg8)
{
    M2C_FIELD(&lbl_8046B488, f32*, 0x1C) = arg8;
}

void gm_8016A424(s8 arg0)
{
    M2C_FIELD(&lbl_8046B488, s8*, 0xF) = arg0;
}

/// #gm_8016A434

/// #fn_8016A450

/// #fn_8016A46C

/// #fn_8016A488

/// #fn_8016A4C8

void gm_8016A92C(gm_8016A92C_arg0_t* arg0)
{
    lbl_8046B668.unk_1C = -2;
    arg0->x58 = &lbl_8046B668;
}

/// #gm_8016A944

UNK_T gm_8016A97C(void)
{
    return &M2C_FIELD(&lbl_8046B668, UNK_T*, 0x1C);
}

UNK_T gm_8016A98C(void)
{
    return &lbl_8046B668;
}

/// #gm_8016A998

/// #gm_8016A9E8

/// #gm_8016AC44

lbl_8046B6A0_t* gm_8016AE38(void)
{
    return &lbl_8046B6A0;
}

lbl_8046B6A0_t* gm_8016AE44(void)
{
    return &lbl_8046B6A0;
}

Placeholder_8016AE38_flags_2* gm_8016AE50(void)
{
    return &lbl_8046B6A0.unk24C8;
}

/// #fn_8016AE60

bool gm_8016AE80(void)
{
    return lbl_8046B6A0.unk_24D3;
}

f32 gm_8016AE94(void)
{
    return lbl_8046B6A0.unk_34;
}

u64 gm_8016AEA4(void)
{
    return lbl_8046B6A0.unk_24E8;
}

s32 gm_8016AEB8(void)
{
    return lbl_8046B6A0.unk_24F0;
}

bool gm_8016AEC8(void)
{
    return lbl_8046B6A0.unk_24D4;
}

bool gm_8016AEDC(void)
{
    return lbl_8046B6A0.unk_24;
}

bool gm_8016AEEC(void)
{
    return lbl_8046B6A0.unk_28;
}

u16 gm_8016AEFC(void)
{
    return lbl_8046B6A0.unk_2C;
}

/// #gm_8016AF0C

/// #gm_8016AF88

u16 gm_8016B004(void)
{
    return lbl_8046B6A0.unk_24D6;
}

/// #gm_8016B014

/// #gm_8016B094

/// #gm_8016B0B4

bool gm_8016B0D4(void)
{
    return lbl_8046B6A0.unk24C8.x1_b7;
}

bool gm_8016B0E8(void)
{
    return lbl_8046B6A0.unk_24CC_b2;
}

bool gm_8016B0FC(void)
{
    return lbl_8046B6A0.unk24C8.x2_b3;
}

bool gm_8016B110(void)
{
    return lbl_8046B6A0.unk24C8.x0_b7;
}

bool gm_8016B124(void)
{
    return lbl_8046B6A0.unk24C8.x2_b1;
}

void fn_8016B138(void)
{
    lbl_8046B6A0.unk_24D0 = 0;
}

/// #gm_8016B14C

/// #gm_8016B168

/// #gm_8016B184

/// #gm_8016B1A8

bool gm_8016B1C4(void)
{
    return lbl_8046B6A0.unk_24CD_b2;
}

bool gm_8016B1D8(void)
{
    return lbl_8046B6A0.unk_24CD_b3;
}

bool gm_8016B1EC(void)
{
    return lbl_8046B6A0.unk_0 == 0;
}

/// #gm_8016B204

bool gm_8016B238(void)
{
    return lbl_8046B6A0.unk_24CE;
}

f32 gm_8016B248(void)
{
    return lbl_8046B6A0.unk_24F8;
}

/// #gm_8016B258

/// #gm_8016B274

/// #gm_8016B2C8

void gm_8016B328(void)
{
    M2C_FIELD(&lbl_8046B6A0, s8*, 6) = 1;
}

void gm_8016B33C(s32 arg0)
{
    M2C_FIELD(&lbl_8046B6A0, s8*, 0xB) = arg0 + 1;
}

void gm_8016B350(s32 arg0)
{
    lbl_8046B6A0.unk_10 = arg0 + 1;
}

void gm_8016B364(s32 arg0)
{
    lbl_8046B6A0.unk_14 = arg0 + 1;
}

void gm_8016B378(s8 arg0)
{
    M2C_FIELD(&lbl_8046B6A0, s8*, 0x18) = arg0;
}

void fn_8016B388(ssize_t arg0, s16 arg1)
{
    M2C_FIELD((&lbl_8046B6A0 + (arg0 * 0xE)), s16*, 0x3E) = arg1;
}

/// #gm_8016B3A0

/// #gm_8016B3D8

/// #gm_8016B41C

/// #gm_8016B498

/// #fn_8016B4BC

/// #fn_8016B510

/// #gm_8016B558

/// #fn_8016B5B0

/// #gm_8016B6E8

u8 fn_8016B728(void)
{
    return M2C_FIELD(&lbl_8046B6A0, u8*, 0xC);
}

/// #fn_8016B738

UNK_T gm_8016B774(void)
{
    return &M2C_FIELD(&lbl_8046B6A0, UNK_T*, 0x24C);
}

/// #fn_8016B784

/// #fn_8016B7B4

/// #fn_8016B7F8

/// #fn_8016B88C

/// #gm_8016B8D4

/// #fn_8016B918

/// #fn_8016BAF4

/// #fn_8016BBB4

/// #fn_8016BC74

/// #gm_8016BE80

/// #fn_8016BF74

/// #fn_8016C0C8

/// #fn_8016C35C

/// #fn_8016C46C

/// #fn_8016C4F4

/// #gm_8016C5C0

/// #gm_8016C658

/// #gm_8016C6C0

/// #gm_8016C75C

/// #fn_8016C7D0

/// #fn_8016C7F0

/// #fn_8016CA68

/// #fn_8016CBE8

/// #fn_8016CD98

/// #fn_8016CF4C

/// #fn_8016CFE0

/// #gm_8016D32C

/// #fn_8016D538

/// #fn_8016D634

/// #gm_8016D800

/// #fn_8016D8AC

/// #fn_8016DCC0

/// #fn_8016DEEC

/// #fn_8016E124

/// #fn_8016E2BC

/// #fn_8016E5C0

/// #fn_8016E730

/// #gm_8016E934

/// #gm_8016E9C8

/// #gm_8016EBC0

/// #gm_8016EC28

/// #gm_8016ECE8

/// #gm_8016EDDC

/// #fn_8016EF98

/// #gm_8016F00C

/// #fn_8016F030

/// #gm_8016F088

/// #gm_8016F120

/// #fn_8016F140

/// #fn_8016F160

/// #fn_8016F180

/// #gm_8016F1B8

/// #fn_8016F1F0

/// #gm_8016F208

/// #fn_8016F280

/// #gm_8016F2F8

/// #fn_8016F344

/// #fn_8016F39C

/// #fn_8016F548

/// #fn_8016F740

/// #fn_8016F870

/// #fn_8016F9A8

/// #fn_8016FAD4

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

/// #gm_801737E8

/// #fn_80173834

/// #gm_8017390C

/// #gm_80173AA4

/// #gm_80173B30

/// #gm_80173BC4

/// #gm_80173C70

/// #gm_80173D3C

/// #gm_80173DE4

/// #gm_80173EEC

/// #gm_80174180

/// #gm_801741FC

/// #gm_80174238

int fn_80174274(void)
{
    return lbl_8046DBE8.x94;
}

/// #fn_80174284

/// #fn_80174338

/// #fn_8017435C

/// #fn_80174380

/// #gm_801743A4

/// #fn_801743C4

/// #fn_80174468

/// #fn_801748EC

/// #fn_80174920

/// #fn_801749B8

/// #fn_80174A60

/// #fn_80174B4C

/// #fn_80174FD0

/// #fn_80175038

/// #fn_8017507C

/// #fn_80175240

/// #fn_8017556C

/// #fn_801756E0

/// #fn_80175880

/// #fn_80175A94

/// #fn_80175C5C

/// #fn_80175D34

/// #fn_80175DC8

/// #fn_80176A6C

/// #fn_80176BCC

/// #fn_80176BF0

/// #fn_80176D18

/// #fn_80176D3C

/// #fn_80176F60

/// #fn_801771C0

/// #gm_80177368

/// #gm_80177704

/// #gm_80177724

/// #fn_80177748

/// #fn_80177920

/// #fn_80177B7C

/// #fn_80177DD0

/// #fn_80178050

/// #fn_801785B0

/// #fn_80178BB4

/// #fn_801791E4

/// #fn_80179350

/// #fn_801795D4

/// #fn_801796F0

/// #fn_80179854

/// #fn_80179990

/// #fn_80179D3C

/// #fn_80179D60

/// #fn_80179D84

/// #fn_80179DA8

/// #fn_80179DCC

/// #fn_80179E34

/// #fn_80179E9C

/// #fn_80179F04

/// #fn_80179F6C

/// #fn_80179F84

/// #fn_8017A004

/// #fn_8017A078

/// #fn_8017A318

/// #fn_8017A67C

/// #fn_8017A9B4

/// #fn_8017AA78

/// #fn_8017AD04

/// #fn_8017AD28

/// #fn_8017AD48

/// #fn_8017AD78

/// #fn_8017ADA8

/// #fn_8017AE0C

/// #fn_8017AE70

/// #fn_8017AED8

/// #fn_8017AF40

/// #fn_8017AFA8

/// #fn_8017B010

/// #fn_8017B07C

/// #fn_8017B0E4

/// #fn_8017B14C

/// #fn_8017B1B4

/// #fn_8017B21C

/// #fn_8017B280

/// #fn_8017B2E4

/// #fn_8017B348

/// #fn_8017B3AC

/// #fn_8017B410

/// #fn_8017B4D0

/// #fn_8017B534

/// #fn_8017B598

/// #fn_8017B5FC

/// #fn_8017B660

/// #fn_8017B6C4

/// #fn_8017B728

/// #fn_8017B78C

/// #fn_8017B7F0

/// #fn_8017B854

/// #fn_8017B8B8

/// #fn_8017B91C

/// #fn_8017B9F4

/// #fn_8017BACC

/// #fn_8017BB30

/// #fn_8017BB94

/// #fn_8017BC50

/// #fn_8017BD0C

/// #fn_8017BDC8

s32 gm_8017BE84(u32 arg0)
{
    return (arg0 >> 3) & 0x1F;
}

/// #gm_8017BE8C

/// #gm_8017BEC8

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

/// #gm_80186DFC

/// #gm_80186E30

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

/// #gm_8018776C

/// #gm_801877A8

/// #fn_80187910

/// #fn_80187AB4

/// #fn_80187C9C

/// #fn_80187CF4

/// #gm_80187F48

/// #gm_80188364

/// #gm_8018838C

/// #gm_801883C0

/// #gm_8018841C

/// #gm_80188454

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

/// #gm_8019628C

/// #gm_801963B4

/// #gm_801964A4

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

/// #gm_8019B2DC

/// #fn_8019B458

/// #fn_8019B81C

/// #fn_8019B860

/// #gm_8019B8C4

/// #gm_8019B9C8

void fn_8019BA04(void) {}

/// #fn_8019BA08

/// #fn_8019BF18

/// #fn_8019BF8C

/// #fn_8019C048

/// #fn_8019C3EC

/// #fn_8019C570

/// #fn_8019C6AC

/// #fn_8019C744

/// #fn_8019CA38

/// #fn_8019CBFC

/// #fn_8019CC74

/// #fn_8019CDBC

/// #fn_8019CFA4

/// #fn_8019D074

/// #fn_8019D1BC

/// #fn_8019DD60

/// #gm_8019DF8C

/// #gm_8019E634

/// #gm_8019ECAC

/// #gm_8019EE54

/// #fn_8019EE80

/// #fn_8019EF08

/// #fn_8019EFC4

/// #fn_8019F1D0

/// #fn_8019F2D4

/// #fn_8019F6EC

/// #fn_8019F810

/// #fn_8019F9C4

/// #gm_801A0A10

/// #gm_801A0B18

/// #fn_801A0B60

/// #gm_801A0C6C

/// #gm_801A0E0C

/// #fn_801A0E34

/// #gm_801A0FEC

/// #gm_801A10FC

/// #fn_801A1134
