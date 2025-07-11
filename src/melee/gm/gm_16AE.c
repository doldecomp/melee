#include <placeholder.h>

#include "gm_16AE.static.h"
#include "gm_1601.h"

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
#include "pl/player.h"

#include <m2c_macros.h>

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

u32 gm_8016AEDC(void)
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

/// #gm_SetGameSpeed

/// #gm_ResetGameSpeed

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

int gm_8016B558(void)
{
    int i;
    int count;
    count = 0;
    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != 3) {
            count++;
        }
    }
    return count;
}

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

/// #gm_8016D32C_OnFrame

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

/// #gm_8016E934_OnEnter

/// #gm_8016E9C8

/// #gm_8016EBC0_OnEnter

/// #gm_8016EC28_OnEnter

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

/// #gmDecisionGetType

short fn_8016F1F0(int idx)
{
    return lbl_803D5A4C[idx].x0;
}

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

/// #gm_801737E8_OnLoad

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
