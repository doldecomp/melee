#include <platform.h>
#include <placeholder.h>

#include "plbonus.h"

#include "inlines.h"
#include "pl_040D.h"
#include "plattack.h"
#include "player.h"
#include "plstale.h"
#include "types.h"

#include <baselib/debug.h>
#include <gm/gm_unsplit.h>

static inline void setKindToOne_inline(int player, int kind)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(player);
    HSD_ASSERTMSG(56, player != 6, "player != Gm_Player_Other");
    HSD_ASSERTMSG(57, gmDecisionGetType(kind) == 0,
                  "gmDecisionGetType(kind) == Gm_DecType_Flag");
    table->x0_staleMoveTable.x904[kind] = 1U;
}

static inline void setKindToValue_inline(int player, int kind,
                                         unsigned int val)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(player);
    HSD_ASSERTMSG(80, player != 6, "player != Gm_Player_Other");
    HSD_ASSERTMSG(81, gmDecisionGetType(kind) == 1,
                  "gmDecisionGetType(kind) == Gm_DecType_Point");
    table->x0_staleMoveTable.x904[kind] = val;
}

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
    setKindToValue_inline(player, kind, arg2);
}

void pl_80038824(int arg0, int kind)
{
    pl_StaleMoveTableExt_t* temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);

    HSD_ASSERTMSG(92, gmDecisionGetType(kind) == 1,
                  "gmDecisionGetType(kind) == Gm_DecType_Point");
    temp_r31->x0_staleMoveTable.x904[kind] += 1;
}

void pl_80038898(int arg0, int kind)
{
    unsigned int currentValue;
    pl_StaleMoveTableExt_t* temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    HSD_ASSERTMSG(103, gmDecisionGetType(kind) == 1,
                  "gmDecisionGetType(kind) == Gm_DecType_Point");
    currentValue = temp_r31->x0_staleMoveTable.x904[kind];
    RETURN_IF(currentValue == 0);
    temp_r31->x0_staleMoveTable.x904[kind] = currentValue - 1;
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
    for (i = 0; i < 6; ++i) {
        temp_r31->x0_staleMoveTable.xC78[i] = 0.0f;
    }
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
        *(int*) (&temp_r31->x0_staleMoveTable.xCBC.x0) = temp_zero;
    }

    temp_r31->x0_staleMoveTable.xCC0.x0 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x4 = 0;
    temp_r31->x0_staleMoveTable.xCC0.kb_applied1 = 0.0f;
    temp_r31->x0_staleMoveTable.xCC0.xC = 6;
    temp_r31->x0_staleMoveTable.xCC0.x10_b0 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b3 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b1 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b2 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b3 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b4 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b5 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b6 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b7 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b0 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b1 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b2 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b4 = 0;
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

void fn_80038FB8(int arg0)
{
    int var_ctr;
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);

    for (var_ctr = 0; var_ctr < 215; ++var_ctr) {
        temp_r3->x0_staleMoveTable.x904[var_ctr] = 0;
    }
}

int pl_8003906C(int arg0, int arg1, unsigned int* arg2, unsigned int arg3,
                unsigned int arg4, unsigned int arg5, int* arg6)
{
    unsigned int var_r3;

    if (pl_Verify_gm_8016AEDC()) {
        if (gm_8016AEDC() <= arg3) {
            if (arg5 >= arg4) {
                if (arg1 != -1) {
                    setKindToValue_inline(arg0, arg1, 1U);
                } else {
                    *arg2 = 1U;
                }
            }

            if (arg3 == gm_8016AEDC()) {
                *arg6 = (int) arg5;
                return 1;
            }
        } else if ((gm_8016AEDC() % arg3) == 0) {
            if (arg1 != -1) {
                var_r3 = pl_80039418(arg0, arg1);
            } else {
                var_r3 = *arg2;
            }

            if (((int) var_r3 != 0) && (arg5 - (unsigned int) *arg6 < arg4)) {
                if (arg1 != -1) {
                    setKindToValue_inline(arg0, arg1, 0U);
                } else {
                    *arg2 = 0U;
                }
            }

            *arg6 = (int) arg5;
            return 1;
        }
    }
    return 0;
}

/// #pl_80039238

unsigned int pl_80039418(int arg0, int arg1)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(arg0);
    return table->x0_staleMoveTable.x904[arg1];
}

static inline void pl_80039450_inline(int slot)
{
    pl_StaleMoveTableExt_t* var_r26;
    int i;

    var_r26 = Player_GetStaleMoveTableIndexPtr2(slot);

    for (i = 0; i < 215; ++i) {
        if (gmDecisionGetType(i) == 0) {
            var_r26->x0_staleMoveTable.x904[0] = 0;
        }
        var_r26 = (pl_StaleMoveTableExt_t*) ((char*) var_r26 + 4);
    }
}

void pl_80039450(int arg0)
{
    pl_StaleMoveTableExt_t* temp_r29 = Player_GetStaleMoveTableIndexPtr2(arg0);

    pl_80039450_inline(arg0);

    fn_80039618(arg0);
    fn_8003B044(arg0);
    fn_8003B9A4(arg0);
    fn_8003BD60(arg0);
    fn_8003C340(arg0);
    fn_8003CC84(arg0);
    fn_8003D2EC(arg0);

    if (!temp_r29->xDD0.bit1) {
        setKindToOne_inline(arg0, 0x4F);
    }

    if (gm_8016B0FC() == 0 && !temp_r29->xDD0.bit2) {
        setKindToOne_inline(arg0, 0x55);
    }

    if (temp_r29->xDCC != 0U && temp_r29->xDD1.bit5) {
        setKindToOne_inline(arg0, 0x4E);
    }
}

/// #fn_80039618

/// #fn_8003B044

/// #fn_8003B9A4

/// #fn_8003BD60

/// #fn_8003C340

/// #fn_8003CC84

/// #fn_8003D2EC
