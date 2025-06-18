#include <platform.h>
#include <placeholder.h>

#include "plbonus.h"

#include "pl_040D.h"
#include "plattack.h"
#include "player.h"
#include "plbonusinline.h"
#include "plstale.h"
#include "types.h"

#include <baselib/debug.h>
#include <gm/gm_1601.h>

unsigned int pl_800386D8(pl_800386D8_t* arg0, ssize_t arg1)
{
    return arg0->x3E8[arg1];
}

int pl_800386E8(pl_800386E8_arg0_t* arg0)
{
    int temp = arg0->unk_190 + arg0->unk_5AC;
    return temp + arg0->unk_5B0;
}

/// #fn_80038700

void pl_80038788(int player, int kind, int arg2)
{
    pl_StaleMoveTableExt_t* temp_r31 =
        Player_GetStaleMoveTableIndexPtr2(player);

    HSD_ASSERTMSG(80, player != 6, "player != Gm_Player_Other");
    HSD_ASSERTMSG(81, gm_8016F1B8(kind) == 1,
                  "gmDecisionGetType(kind) == Gm_DecType_Point");
    temp_r31->x0_staleMoveTable.x904[kind] = arg2;
}

void pl_80038824(int arg0, int kind)
{
    pl_StaleMoveTableExt_t* temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);

    HSD_ASSERTMSG(92, gm_8016F1B8(kind) == 1,
                  "gmDecisionGetType(kind) == Gm_DecType_Point");
    temp_r31->x0_staleMoveTable.x904[kind] += 1;
}

void pl_80038898(int arg0, int kind)
{
    unsigned int temp_r3;
    pl_StaleMoveTableExt_t* temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    HSD_ASSERTMSG(103, gm_8016F1B8(kind) == 1,
                  "gmDecisionGetType(kind) == Gm_DecType_Point");
    temp_r3 = temp_r31->x0_staleMoveTable.x904[kind];
    RETURN_IF(temp_r3 == 0);
    temp_r31->x0_staleMoveTable.x904[kind] = temp_r3 - 1;
}

pl_804D6470_t* pl_80038914(void)
{
    return pl_804D6470;
}

void pl_8003891C(int slot)
{
    int i;
    pl_StaleMoveTableExt_t* temp_r31;
    /// @todo: This aint it
    volatile int temp_zero;
    PAD_STACK(8);

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(slot);
    plStale_ResetStaleMoveTableForPlayer(slot);
    plAttack_8003759C(slot);
    pl_80040DDC(slot);
    pl_80041524(slot);
    pl_800418F4(slot);

    for (i = 0; i < 39; ++i) {
        temp_r31->x0_staleMoveTable.x674[i] = 0;
    }
    for (i = 0; i < 39; ++i) {
        temp_r31->x0_staleMoveTable.x710[i] = 0;
    }
    for (i = 0; i < 39; ++i) {
        temp_r31->x0_staleMoveTable.x7AC[i] = 0;
    }
    for (i = 0; i < 30; ++i) {
        temp_r31->x0_staleMoveTable.x848[i] = 0;
    }

    fn_80038FB8(slot);
    temp_r31->x0_staleMoveTable.xC60 = 0.0f;
    temp_r31->x0_staleMoveTable.xC64 = 0.0f;
    temp_r31->x0_staleMoveTable.xC68 = 0;
    temp_r31->x0_staleMoveTable.xC6C = 0.0f;
    temp_r31->x0_staleMoveTable.xC70 = 0.0f;
    temp_r31->x0_staleMoveTable.xC74 = 0.0f;
    temp_r31->x0_staleMoveTable.xC78 = 0.0f;
    temp_r31->x0_staleMoveTable.xC7C = 0.0f;
    temp_r31->x0_staleMoveTable.xC80 = 0.0f;
    temp_r31->x0_staleMoveTable.xC84 = 0.0f;
    temp_r31->x0_staleMoveTable.xC88 = 0.0f;
    temp_r31->x0_staleMoveTable.xC8C = 0.0f;
    temp_r31->x0_staleMoveTable.xC90 = 0;
    temp_r31->x0_staleMoveTable.xC94 = 0;
    temp_r31->x0_staleMoveTable.xC98 = 0.0f;
    temp_r31->x0_staleMoveTable.xC9C = 0.0f;
    temp_r31->x0_staleMoveTable.xCA0 = 0.0f;
    temp_r31->x0_staleMoveTable.xCA4 = 0;
    temp_r31->x0_staleMoveTable.xCAC = 6;
    temp_r31->x0_staleMoveTable.xCB4 = 0;

    /// @todo: What?
    {
        temp_zero = 0;
        temp_r31->x0_staleMoveTable.xCB8 = 6;
        temp_r31->x0_staleMoveTable.xCBC = temp_zero;
    }

    temp_r31->x0_staleMoveTable.xCC0 = 0;
    temp_r31->x0_staleMoveTable.xCC4 = 0;
    temp_r31->x0_staleMoveTable.xCC8 = 0.0f;
    temp_r31->x0_staleMoveTable.xCCC = 6;
    temp_r31->x0_staleMoveTable.xCD0.bit0 = 0;
    temp_r31->x0_staleMoveTable.xCD1.bit3 = 0;
    temp_r31->x0_staleMoveTable.xCD0.bit1 = 0;
    temp_r31->x0_staleMoveTable.xCD0.bit2 = 0;
    temp_r31->x0_staleMoveTable.xCD0.bit3 = 0;
    temp_r31->x0_staleMoveTable.xCD0.bit4 = 0;
    temp_r31->x0_staleMoveTable.xCD0.bit5 = 0;
    temp_r31->x0_staleMoveTable.xCD0.bit6 = 0;
    temp_r31->x0_staleMoveTable.xCD0.bit7 = 0;
    temp_r31->x0_staleMoveTable.xCD1.bit0 = 0;
    temp_r31->x0_staleMoveTable.xCD1.bit1 = 0;
    temp_r31->x0_staleMoveTable.xCD1.bit2 = 0;
    temp_r31->x0_staleMoveTable.xCD1.bit4 = 0;
    temp_r31->x0_staleMoveTable.xCD4 = 0;
    temp_r31->x0_staleMoveTable.xCD8 = 0;
    temp_r31->x0_staleMoveTable.xCE0 = 0.0f;
    temp_r31->x0_staleMoveTable.xCDC = 0.0f;
    temp_r31->x0_staleMoveTable.xCE4 = 0;
    temp_r31->x0_staleMoveTable.xCE8 = 0;
    temp_r31->x0_staleMoveTable.xCEC = 0;
    temp_r31->x0_staleMoveTable.xCF0 = 0;
    temp_r31->xCF4 = 0;
    temp_r31->xCF8 = 0.0f;
    temp_r31->x0_staleMoveTable.xCA8 = 0;
    temp_r31->xD04 = 0;
    temp_r31->xD08 = 0;
    temp_r31->xD0C = 0;
    temp_r31->xD10 = 0;
    temp_r31->xD14 = 0;
    temp_r31->xD18 = 0;
    temp_r31->xD1C = 0;
    temp_r31->xD20 = 0;
    temp_r31->xD24 = 0;
    temp_r31->xD28 = 0;
    temp_r31->xD2C = 0;
    temp_r31->xD30 = 0;
    temp_r31->xD34 = 0;
    temp_r31->xD38 = 0;
    temp_r31->xD3C = 0;
    temp_r31->xD40 = 0;
    temp_r31->xD44 = 0;
    temp_r31->xD48 = 0;
    temp_r31->xD4C = 0;
    temp_r31->xD50 = 0;
    temp_r31->xD54 = 0;
    temp_r31->xDC0 = 0.0f;
    temp_r31->xD58 = 0;
    temp_r31->xD5C = -1U;
    temp_r31->xD60 = 0;
    temp_r31->xD64 = 6;
    temp_r31->xD68 = 0;
    temp_r31->xD6C = 6;
    temp_r31->xCFC = 0;
    temp_r31->xD00 = 0;
    temp_r31->xD70 = 0;
    temp_r31->xD74 = 0.0f;
    temp_r31->xD78 = 0.0f;
    temp_r31->xD7C = 0.0f;
    temp_r31->xD80 = 0.0f;
    temp_r31->xD84 = 0.0f;
    temp_r31->xD88 = 0.0f;
    temp_r31->xD94 = 0.0f;
    temp_r31->xD98 = 0;
    temp_r31->xD8C = 0.0f;
    temp_r31->xD90 = 0;
    temp_r31->xD9C = 0;
    temp_r31->xDA0 = 0;
    temp_r31->xDA4 = 0;
    temp_r31->xDA8 = 0;
    temp_r31->xDAC = 0;
    temp_r31->xDB4 = 0;
    temp_r31->xDBC = 0;
    temp_r31->xDC4 = 0;
    temp_r31->xDC8 = 0;
    temp_r31->xDCC = 0;
    temp_r31->xDD0.bit0 = 0;
    temp_r31->xDD0.bit1 = 0;
    temp_r31->xDD0.bit2 = 0;
    temp_r31->xDD0.bit3 = 0;
    temp_r31->xDD0.bit4 = 0;
    temp_r31->xDD0.bit5 = 0;
    temp_r31->xDD0.bit6 = 0;
    temp_r31->xDD0.bit7 = 0;
    temp_r31->xDD1.bit0 = 0;
    temp_r31->xDD1.bit1 = 0;
    temp_r31->xDD1.bit2 = 0;
    temp_r31->xDD1.bit3 = 0;
    temp_r31->xDB8 = 0;
    temp_r31->xDD1.bit4 = 0;
    temp_r31->xDD1.bit5 = 0;
    temp_r31->xDD1.bit6 = 0;
    temp_r31->xDD1.bit7 = 0;
}

void pl_80038F10(int slot)
{
    pl_StaleMoveTableExt_t* temp_r3_2;
    int i;

    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    temp_r3->xD50 = 0;
    temp_r3->xD54 = 0;
    temp_r3->xD60 = 0;
    temp_r3->xD64 = 6;

    for (i = 0; i < 6; ++i) {
        temp_r3_2 = Player_GetStaleMoveTableIndexPtr2(i);

        if (slot == temp_r3_2->xD64) {
            temp_r3_2->xD60 = 0;
            temp_r3_2->xD64 = 6;
        }

        if (slot == temp_r3_2->x0_staleMoveTable.xCAC) {
            temp_r3_2->x0_staleMoveTable.xCAC = 6;
        }

        if (slot == temp_r3_2->xD6C) {
            temp_r3_2->xD6C = 6;
        }
    }
}

/// #fn_80038FB8

/// #pl_8003906C

/// #pl_80039238

unsigned int pl_80039418(int arg0, int arg1)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(arg0);
    return table->x0_staleMoveTable.x904[arg1];
}

void pl_80039450(int arg0)
{
    pl_StaleMoveTableExt_t* temp_r30;
    pl_StaleMoveTableExt_t* temp_r30_2;
    pl_StaleMoveTableExt_t* temp_r31;

    pl_StaleMoveTableExt_t* temp_r29 = Player_GetStaleMoveTableIndexPtr2(arg0);

    pl_80039450_inline(arg0);

    fn_80039618(arg0);
    fn_8003B044(arg0);
    fn_8003B9A4(arg0);
    fn_8003BD60(arg0);
    fn_8003C340(arg0);
    fn_8003CC84(arg0);
    fn_8003D2EC(arg0);

    /// @todo: Replace these with their inlines

    if (!(temp_r29->xDD0.bit1)) {
        temp_r30 = Player_GetStaleMoveTableIndexPtr2(arg0);
        HSD_ASSERTMSG(56, arg0 != 6, "player != Gm_Player_Other");
        HSD_ASSERTMSG(57, gm_8016F1B8(0x4F) == 0,
                      "gmDecisionGetType(kind) == Gm_DecType_Flag");
        temp_r30->x0_staleMoveTable.xA40 = 1;
    }

    if ((gm_8016B0FC() == 0) && !(temp_r29->xDD0.bit2)) {
        temp_r30_2 = Player_GetStaleMoveTableIndexPtr2(arg0);
        HSD_ASSERTMSG(56, arg0 != 6, "player != Gm_Player_Other");
        HSD_ASSERTMSG(57, gm_8016F1B8(0x55) == 0,
                      "gmDecisionGetType(kind) == Gm_DecType_Flag");
        temp_r30_2->x0_staleMoveTable.xA58 = 1;
    }

    if ((temp_r29->xDCC != 0U) && temp_r29->xDD1.bit5) {
        temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
        HSD_ASSERTMSG(56, arg0 != 6, "player != Gm_Player_Other");
        HSD_ASSERTMSG(57, gm_8016F1B8(0x4E) == 0,
                      "gmDecisionGetType(kind) == Gm_DecType_Flag");
        temp_r31->x0_staleMoveTable.xA3C = 1;
    }
}

/// #fn_80039618

/// #fn_8003B044

/// #fn_8003B9A4

/// #fn_8003BD60

/// #fn_8003C340

/// #fn_8003CC84

/// #fn_8003D2EC
