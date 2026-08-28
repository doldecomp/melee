#include "if/ifstock.h"

#include "if/ifstock.static.h"
#include <placeholder.h>

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/jobj.h"
#include "ef/efsync.h"

#include "gm/forward.h"

#include "gm/gm_unsplit.h"
#include "gm/gmregclear.h"
#include "gm/types.h"
#include "gr/ground.h"
#include "if/ifall.h"
#include "if/ifstatus.h"
#include "if/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbspdisplay.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include "sc/forward.h"

#include "sc/types.h"

#include <baselib/aobj.h>
#include <baselib/dobj.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/mobj.h>
#include <baselib/tobj.h>

struct IfStockStealAnim {
    Vec3 start;
    Vec3 mid;
    Vec3 end;
};

struct IfStockData {
    unsigned char x0[0xC];
    struct IfStockStealAnim anim[2];
};

struct IfStockDataOffset {
    unsigned char x0[0x204];
    struct IfStockData data;
};

static inline HSD_JObj* ifStock_802F7EFC_inline(int index, int player,
                                                struct ifStock_804A1378* stock)
{
    return stock->player[player].x4[index];
}

int ifStock_802F7EFC(int arg0, int arg1)
{
    Vec3 pos;
    struct ifStock_804A1378* stock;
    struct IfStockData* arg1_data;
    struct IfStockData* arg0_data;
    int slot;
    int i, j;
    stock = &ifStock_804A1378;
    arg0_data = (struct IfStockData*) stock;
    arg0_data += arg0;
    arg1_data = (struct IfStockData*) stock;
    arg1_data += arg1;
    arg0_data = &((struct IfStockDataOffset*) arg0_data)->data;
    arg1_data = &((struct IfStockDataOffset*) arg1_data)->data;
    if (Player_GetStocks(arg1) == 0) {
        return 1;
    }
    stock->player[arg1].stocks = Player_GetStocks(arg1);
    if (stock->player[arg1].stocks < 0) {
        stock->player[arg1].stocks = 1;
    }
    if (arg1_data->x0[10] == 0) {
        slot = 5;
    } else if (arg1_data->x0[11] == 0) {
        slot = 6;
    } else {
        return 2;
    }
    arg1_data->x0[slot + 5] = 1;
    arg0_data->x0[2] = 0;
    arg1_data->x0[slot - 2] = arg0;
    {
        int stocks = stock->player[arg1].stocks;
        if (stocks <= 5 && stocks > 0) {
            arg1_data->x0[stocks + 4] = 10;
        }
        i = 0;
        if (stocks <= 5 && stocks > 0) {
            i = 1;
        }
        j = i != 0 ? stocks : 1;
    }
    HSD_JObjGetTranslation(stock->player[arg1].x4[0], &pos);
    HSD_JObjReqAnimAll(stock->player[arg1].x4[j], 0.0f);
    HSD_JObjAnimAll(stock->player[arg1].x4[j]);
    HSD_JObjGetTranslation(ifStock_802F7EFC_inline(j, arg1, stock),
                           &arg1_data->anim[slot - 5].start);
    arg1_data->anim[slot - 5].start.x += pos.x;
    arg1_data->anim[slot - 5].start.y += pos.y;
    arg1_data->anim[slot - 5].start.z += pos.z;
    i = 0;
    if (Player_GetStocks(arg0) < 5 && Player_GetStocks(arg0) > 0) {
        i = 1;
    }
    j = i != 0 ? Player_GetStocks(arg0) : 0;
    HSD_JObjGetTranslation(stock->player[arg0].x4[0], &pos);
    HSD_JObjReqAnimAll(stock->player[arg0].x4[j], 0.0f);
    HSD_JObjAnimAll(stock->player[arg0].x4[j]);
    HSD_JObjGetTranslation(stock->player[arg0].x4[1],
                           &arg1_data->anim[slot - 5].end);
    arg1_data->anim[slot - 5].end.x += (2.4f * j) + pos.x;
    arg1_data->anim[slot - 5].end.y = arg1_data->anim[slot - 5].start.y;
    arg1_data->anim[slot - 5].end.z += pos.z;
    arg1_data->anim[slot - 5].mid.x =
        0.5f *
        (arg1_data->anim[slot - 5].end.x + arg1_data->anim[slot - 5].start.x);
    arg1_data->anim[slot - 5].mid.z =
        0.5f *
        (arg1_data->anim[slot - 5].end.z + arg1_data->anim[slot - 5].start.z);
    arg1_data->anim[slot - 5].mid.y =
        10.0f + arg1_data->anim[slot - 5].start.y;
    return 0;
}

static inline struct ifStock_804A1378_x204*
ifStock_802F8298_get_data(struct ifStock_804A1378* stock)
{
    return stock->x204;
}

static inline void
ifStock_802F8298_init(HSD_GObj* gobj, struct IfStockUserData** user_data,
                      HSD_JObj** jobj, struct ifStock_804A1378** stock)
{
    *user_data = GET_IFSTOCK(gobj);
    *jobj = gobj->hsd_obj;
    *stock = &ifStock_804A1378;
}

void ifStock_802F8298(HSD_GObj* gobj)
{
    struct IfStockUserData* user_data;
    HSD_JObj* jobj;
    struct ifStock_804A1378* stock;
    HSD_JObj* jobj_anim;
    Vec3 vecA, vecB, vecC, vecD;
    HSD_JObj* jobj2;
    int i;
    ifStock_802F8298_init(gobj, &user_data, &jobj, &stock);
    jobj_anim = jobj;
    stock->player[user_data->player].stocks =
        Player_GetStocks(user_data->player);
    if (stock->player[user_data->player].stocks > 99) {
        stock->player[user_data->player].stocks = 99;
    }
    if (stock->player[user_data->player].stocks < 0) {
        stock->player[user_data->player].stocks = 1;
    }
    if (stock->player[user_data->player].stocks <= 5) {
        HSD_JObjSetFlagsAll(stock->player[user_data->player].x3C, JOBJ_HIDDEN);
        for (i = 0; i < 5; i++) {
            jobj2 = stock->player[user_data->player].x4[i + 1];
            if (i < stock->player[user_data->player].stocks) {
                HSD_JObjClearFlagsAll(jobj2, JOBJ_HIDDEN);
                if (stock->x204[user_data->player].x0[2] != 0) {
                    stock->x204[user_data->player].x0[i + 5] = 0;
                } else {
                    stock->x204[user_data->player].x0[i + 5] = 10;
                }
            } else {
                if (stock->x204[user_data->player].x0[2] == 0) {
                    stock->x204[user_data->player].x0[i + 5] = 10;
                }
                if (stock->x204[user_data->player].x0[i + 5] == 0) {
                    HSD_JObjGetTranslation(jobj, &vecA);
                    HSD_JObjGetTranslation(
                        stock->player[user_data->player].x4[i + 1], &vecB);
                    vecB.x += vecA.x;
                    vecB.y += vecA.y;
                    vecB.z += vecA.z;
                    efSync_Spawn(0x474, gobj, &vecB);
                }
                if (stock->x204[user_data->player].x0[i + 5] < 10) {
                    stock->x204[user_data->player].x0[i + 5] += 1;
                }
            }
            HSD_JObjReqAnimAll(jobj2,
                               stock->x204[user_data->player].x0[i + 5]);
            HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj,
                               gm_80168BF8(user_data->player));
            HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
        }
    } else {
        HSD_JObjClearFlagsAll(stock->player[user_data->player].x3C,
                              JOBJ_HIDDEN);
        if (stock->player[user_data->player].stocks >= 10) {
            HSD_JObjReqAnimAll(stock->player[user_data->player].x44,
                               (stock->player[user_data->player].stocks / 10));
            HSD_JObjReqAnimAll(stock->player[user_data->player].x40,
                               stock->player[user_data->player].stocks % 10);
        } else {
            HSD_JObjReqAnimAll(stock->player[user_data->player].x44,
                               stock->player[user_data->player].stocks);
            HSD_JObjSetFlagsAll(stock->player[user_data->player].x40,
                                JOBJ_HIDDEN);
        }
        for (i = 0; i < 5; i++) {
            jobj2 = stock->player[user_data->player].x4[i + 1];
            if (i == 0) {
                ifStock_802F8298_get_data(stock)[user_data->player]
                    .x0[i + 5] = 0;
            } else {
                ifStock_802F8298_get_data(stock)[user_data->player]
                    .x0[i + 5] = 10;
            }
            HSD_JObjReqAnimAll(jobj2,
                               stock->x204[user_data->player].x0[i + 5]);
            HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj,
                               gm_80168BF8(user_data->player));
            HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
        }
    }
    for (i = 5; i <= 6; i++) {
        jobj2 = stock->player[user_data->player].x4[i + 1];
        if (ifStock_802F8298_get_data(stock)[user_data->player].x0[i + 5] ==
            0) {
            HSD_JObjSetFlagsAll(jobj2, JOBJ_HIDDEN);
        } else {
            HSD_JObjClearFlagsAll(jobj2, JOBJ_HIDDEN);
            if (stock->x204[user_data->player].x0[i + 5] <= 10) {
                {
                    unsigned char* data = stock->x204[user_data->player].x0;
                    u32 anim_offset =
                        0xC + (i - 5) * sizeof(struct IfStockStealAnim);
                    lbVector_8000DE38(
                        (float (*)[4]) &
                            stock->x204[user_data->player].x0[anim_offset],
                        &vecC, 0.1f * data[i + 5]);
                }
                HSD_JObjGetTranslation(stock->player[user_data->player].x4[0],
                                       &vecD);
                vecC.x -= vecD.x;
                vecC.y -= vecD.y;
                vecC.z -= vecD.z;
                HSD_JObjSetTranslate(jobj2, &vecC);
                if (stock->x204[user_data->player].x0[i + 5] == 1) {
                    vecC.x =
                        ((struct IfStockStealAnim*) &stock
                             ->x204[user_data->player]
                             .x0[0xC + i * sizeof(struct IfStockStealAnim) -
                                 5 * sizeof(struct IfStockStealAnim)])
                            ->start.x;
                    vecC.y =
                        ((struct IfStockStealAnim*) &stock
                             ->x204[user_data->player]
                             .x0[0xC + i * sizeof(struct IfStockStealAnim) -
                                 5 * sizeof(struct IfStockStealAnim)])
                            ->start.y;
                    efSync_Spawn(0x475, gobj, &vecC);
                } else if (stock->x204[user_data->player].x0[i + 5] == 10) {
                    {
                        struct ifStock_804A1378_x204* data =
                            ifStock_802F8298_get_data(stock);
                        vecC.x =
                            ((struct IfStockStealAnim*)
                                 &data[user_data->player]
                                      .x0[0xC +
                                          i * sizeof(struct IfStockStealAnim) -
                                          5 * sizeof(
                                                  struct IfStockStealAnim)])
                                ->end.x;
                    }
                    vecC.y =
                        ((struct IfStockStealAnim*)
                             &ifStock_802F8298_get_data(stock)
                                  [user_data->player]
                                      .x0[0xC +
                                          i * sizeof(struct IfStockStealAnim) -
                                          5 * sizeof(
                                                  struct IfStockStealAnim)])
                            ->end.y;
                    efSync_Spawn(0x476, gobj, &vecC);
                }
                ifStock_802F8298_get_data(stock)[user_data->player]
                    .x0[i + 5]++;
            } else {
                int count_index = i + 5;
                stock->x204[user_data->player].x0[count_index] = 0;
                stock->x204[ifStock_802F8298_get_data(stock)
                                [user_data->player]
                                    .x0[i - 2]]
                    .x0[2] = 1;
            }
        }
        HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj,
                           gm_80168BF8(user_data->player));
        HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    }
    HSD_JObjAnimAll(jobj_anim);
}

static inline struct IfStockUserData* ifStock_802F89F8_get_data(HSD_GObj* gobj)
{
    struct IfStockUserData* user_data = GET_IFSTOCK(gobj);

    return user_data;
}

static inline int ifStock_802F89F8_count(int coins)
{
    int i;

    for (i = 0; i < 32; i++) {
        if (coins == 0) {
            return i;
        }
        coins /= 10;
    }
    return 0;
}

static inline int ifStock_802F89F8_divisor(int position)
{
    int i;
    int divisor = 1;

    if (position != 0) {
        for (i = 0; i < position; i++) {
            divisor *= 10;
        }
    }
    return divisor;
}

static inline int ifStock_802F89F8_digit(int coins, int position)
{
    int i;
    int divisor = 1;

    if (position - 1 == 0) {
        coins %= 10;
        return coins;
    }
    for (i = 0; i < position - 1; i++) {
        divisor *= 10;
    }
    return (coins / divisor) % 10;
}

void ifStock_802F89F8(HSD_GObj* gobj)
{
    struct IfStockUserData* user_data = ifStock_802F89F8_get_data(gobj);
    int i;
    int player = user_data->player;
    HSD_JObj* jobj2 = ifStock_804A1378.player[player].x4[1];
    HSD_JObj* jobj = gobj->hsd_obj;
    int coins;
    int count;
    int digit;
    int divisor;
    Player_GetCoins(player);
    PAD_STACK(16);
    coins = ifStock_804A1378.player[user_data->player].coins =
        Player_GetCoins(user_data->player);
    if ((u32) coins > 99999U) {
        coins = 99999;
    }
    count = ifStock_802F89F8_count(coins);
    if (count > 5) {
        count = 5;
    }
    HSD_JObjReqAnimAll(jobj2, 0.0f);
    HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj,
                       gm_80168BF8(user_data->player));
    HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    for (i = 0; i < 5; i++) {
        if (i < count) {
            divisor = ifStock_802F89F8_divisor(i);
            HSD_JObjClearFlagsAll(
                ifStock_804A1378.player[user_data->player].x4[13 - i],
                JOBJ_HIDDEN);
            digit = ifStock_802F89F8_digit(coins, count - i);
            HSD_JObjReqAnimAll(
                ifStock_804A1378.player[user_data->player].x4[13 - i], digit);
        } else {
            HSD_JObjSetFlagsAll(
                ifStock_804A1378.player[user_data->player].x4[13 - i],
                JOBJ_HIDDEN);
            if (count == 0 && i == 0) {
                HSD_JObjReqAnimAll(
                    ifStock_804A1378.player[user_data->player].x38, 0.0f);
                HSD_JObjClearFlagsAll(
                    ifStock_804A1378.player[user_data->player].x38,
                    JOBJ_HIDDEN);
            }
        }
    }
    HSD_JObjAnimAll(jobj);
}

void fn_802F8DB0(HSD_GObj* gobj)
{
    int x = gm_801694A0(gobj);
    if (x != ifStock_804A1774.x108) {
        ifStock_802FA2D0(x);
    }
    ifStock_804A1774.x108 = x;
}

void fn_802F8E08(HSD_GObj* _gobj)
{
    struct ifStock_804A1774* stock = &ifStock_804A1774;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;
    int counter = 0;
    float x = -21.0f;
    float y = 11.0f;
    signed char* thing = gm_80169520();
    for (i = 0; i < 130; i++, thing++) {
        gobj = stock->x10C[i + 1];
        if (gobj == NULL) {
            break;
        }
        jobj = gobj->hsd_obj;
        stock->x1[i] = *thing;
        if (stock->x1[i] == -1) {
            HSD_JObjSetTranslateZ(jobj, 10000.0f);
        } else if (stock->x1[i] == -2) {
            int j;
            for (j = i; j < 130; j++) {
                gobj = stock->x10C[i + 1];
                if (gobj != NULL) {
                    jobj = gobj->hsd_obj;
                    HSD_JObjSetTranslateZ(jobj, 10000.0f);
                }
            }
            return;
        } else {
            HSD_JObjSetTranslateZ(jobj, 0.0f);
            HSD_JObjSetTranslateX(jobj, x);
            HSD_JObjSetTranslateY(jobj, y);
            counter++;
            x += 2.45f;
            if (counter % 5 == 0) {
                x = -21.0f;
                y -= 2.45f;
            }
        }
    }
}

void fn_802F916C(HSD_GObj* _gobj)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 b, a;
    int i;
    int counter = 0;
    float x = -21.0f;
    float y = 11.0f;
    PAD_STACK(8);
    Ground_801C1DE4(&a, &b);
    for (i = 0; i < 16; i++) {
        if (i >= b) {
            break;
        } else {
            gobj = ifStock_804A1A8C[i];
            jobj = gobj->hsd_obj;
            if (i >= a) {
                HSD_JObjSetTranslateZ(jobj, 10000.0f);
            } else {
                HSD_JObjSetTranslateZ(jobj, 0.0f);
                HSD_JObjSetTranslateX(jobj, x);
                HSD_JObjSetTranslateY(jobj, y);
                counter++;
                x += 2.45f;
                if (counter % 5 == 0) {
                    x = -21.0f;
                    y -= 2.45f;
                }
            }
        }
    }
}

static inline void fn_802F9410_inline(HSD_GObj* gobj,
                                      struct IfStockUserData* p)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* jobj2 = ifStock_804A1378.player[p->player].x4[1];
    HSD_JObjReqAnimAll(jobj2, 0.0f);
    HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj, gm_80168BF8(p->player));
    HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    HSD_JObjAnimAll(jobj);
}

void fn_802F9410(HSD_GObj* gobj)
{
    struct IfStockUserData* p = GET_IFSTOCK(gobj);
    PAD_STACK(0x10);
    switch (p->mode) {
    case 0:
        ifStock_802F8298(gobj);
        break;
    case 1:
        fn_802F9410_inline(gobj, p);
        break;
    case 2:
        ifStock_802F89F8(gobj);
        break;
    }
}

void fn_802F94E0(HSD_GObj* gobj, int renderpass)
{
    struct IfStockUserData* p = GET_IFSTOCK(gobj);
    struct HudIndex* x = ifStatus_GetHUDInfo();
    if (!x->players[p->player].flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, renderpass);
    }
}

void fn_802F9548(HSD_GObj* gobj, int renderpass)
{
    struct HudIndex* x = ifStatus_GetHUDInfo();
    if (!x->players[0].flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, renderpass);
    }
}

void fn_802F9598(HSD_GObj* gobj, int renderpass)
{
    struct HudIndex* x = ifStatus_GetHUDInfo();
    if (!x->players[0].flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, renderpass);
    }
}

void fn_802F95E8(HSD_GObj* gobj, int renderpass)
{
    struct HudIndex* x = ifStatus_GetHUDInfo();
    if (gm_8016B184() && gm_8016A1F8() &&
        !(x->players[0].flags.hide_all_digits |
          x->players[1].flags.hide_all_digits |
          x->players[2].flags.hide_all_digits |
          x->players[3].flags.hide_all_digits))
    {
        HSD_GObj_JObjCallback(gobj, renderpass);
    }
}

void fn_802F9680(HSD_GObj* gobj, int renderpass)
{
    struct HudIndex* x = ifStatus_GetHUDInfo();
    if (!x->players[0].flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, renderpass);
    }
}

HSD_GObj* ifStock_802F96D0(int a, int b, float x, float y)
{
    struct ifStock_804A1378* q = &ifStock_804A1378;
    HSD_GObj* gobj = GObj_Create(14, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint((*q->x0)->joint);
    HSD_JObj* jobj2;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, fn_802F9680, 11, 0);
    gm_8016895C(jobj, *q->x0, 0);
    lb_80011E24(jobj, &jobj2, 1, -1);
    HSD_JObjSetTranslateX(jobj, x);
    HSD_JObjSetTranslateY(jobj, y);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    HSD_JObjClearFlags(jobj2, JOBJ_HIDDEN);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj, gm_80168B34(a, 0, b));
    HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    return gobj;
}

static inline HSD_JObj*
ifStock_802F98E8_get_x3C(unsigned char player)
{
    return ifStock_804A1378.player[player].x3C;
}

void ifStock_802F98E8(unsigned char player, int b)
{
    struct ifStock_804A1378* stock = &ifStock_804A1378;
    HSD_JObj* jobj;
    struct ifStock_804A1378_x204* volatile user_data;
    int i;
    HSD_GObj* gobj;
    lbl_8046B6A0_t* ae44;
    if (stock->x0 != NULL) {
        user_data = &stock->x204[player];
        stock->x204[player].x0[0] = player;
        user_data->x0[1] = b;
        user_data->x0[2] = 1;
        if (stock->player[player].x0 != NULL) {
            HSD_GObjPLink_80390228(stock->player[player].x0);
        }
        gobj = GObj_Create(14, 15, 0);
        gobj->user_data = user_data;
        if (gobj != NULL) {
            jobj = HSD_JObjLoadJoint((*stock->x0)->joint);
            if (jobj != NULL) {
                unsigned char* data;

                HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
                GObj_SetupGXLink(gobj, fn_802F94E0, 11, 0);
                gm_8016895C(jobj, *stock->x0, 0);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_GObj_SetupProc(gobj, fn_802F9410, 17);
                HSD_JObjSetTranslate(jobj, ifAll_GetPlayerHUDPosition(player));
                lb_80011E24(jobj, ifStock_804A1378.player[player].x4, 0, 1, 2,
                            3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                            -1);
                stock->player[player].x0 = gobj;
                ifStock_804A1378.player[player].coins =
                    Player_GetCoins(player);
                ifStock_804A1378.player[player].stocks =
                    Player_GetStocks(player);
                if (ifStock_804A1378.player[player].stocks < 0) {
                    ifStock_804A1378.player[player].stocks = 1;
                }
                data = user_data->x0;
                switch ((unsigned char) b) {
                case 0:
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x24,
                                        JOBJ_HIDDEN);
                    if (ifStock_804A1378.player[player].stocks <= 5) {
                        HSD_JObjSetFlagsAll(
                            ifStock_804A1378.player[player].x3C, JOBJ_HIDDEN);
                        for (i = 0; i < 7; i++, data++) {
                            jobj = ifStock_804A1378.player[player].x4[i + 1];
                            if (i < ifStock_804A1378.player[player].stocks ||
                                i >= 5)
                            {
                                data[5] = 0;
                                if (i >= 5) {
                                    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                                }
                            } else {
                                data[5] = 10;
                                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                            }
                            HSD_JObjReqAnimAll(jobj, data[5]);
                            HSD_TObjReqAnimAll(jobj->u.dobj->mobj->tobj,
                                               gm_80168BF8(player));
                            HSD_AObjSetRate(jobj->u.dobj->mobj->tobj->aobj,
                                            0.0f);
                        }
                    }
                    break;
                case 1:
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x24,
                                        JOBJ_HIDDEN);
                    HSD_JObjSetFlagsAll(ifStock_802F98E8_get_x3C(player),
                                        JOBJ_HIDDEN);
                    for (i = 0; i < 7; i++, data++) {
                        jobj = ifStock_804A1378.player[player].x4[i + 1];
                        if (i == 0) {
                            data[5] = 0;
                        } else {
                            data[5] = 10;
                        }
                        if (i < 5) {
                            HSD_JObjReqAnimAll(jobj, data[5]);
                            HSD_TObjReqAnimAll(jobj->u.dobj->mobj->tobj,
                                               gm_80168BF8(player));
                            HSD_AObjSetRate(jobj->u.dobj->mobj->tobj->aobj,
                                            0.0f);
                            if (i != 0) {
                                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                            }
                        } else {
                            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                        }
                    }
                    break;
                case 2:
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x28,
                                        JOBJ_HIDDEN);
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x2C,
                                        JOBJ_HIDDEN);
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x30,
                                        JOBJ_HIDDEN);
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x34,
                                        JOBJ_HIDDEN);
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x3C,
                                        JOBJ_HIDDEN);
                    for (i = 0; i < 7; i++, data++) {
                        jobj = ifStock_804A1378.player[player].x4[i + 1];
                        if (i == 0) {
                            data[5] = 0;
                        } else {
                            data[5] = 10;
                        }
                        if (i < 5) {
                            HSD_JObjReqAnimAll(jobj, data[5]);
                            HSD_TObjReqAnimAll(jobj->u.dobj->mobj->tobj,
                                               gm_80168BF8(player));
                            HSD_AObjSetRate(jobj->u.dobj->mobj->tobj->aobj,
                                            0.0f);
                            if (i != 0) {
                                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                            }
                        } else {
                            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                        }
                    }
                    break;
                }
                HSD_JObjAnimAll(jobj);
                ae44 = gm_16AE_GetUnkData_1();
                if (ae44->FighterMatchInfo[player].x4_b1) {
                    GXColor c = { 0x08, 0x08, 0x08, 0x80 };
                    GXColor* color = &c;
                    ifStock_802FB4EC(player, color);
                } else if (ae44->FighterMatchInfo[player].x4_b0) {
                    GXColor c = { 0x3C, 0x3C, 0x46, 0x80 };
                    GXColor* color = &c;
                    ifStock_802FB4EC(player, color);
                }
                fn_802F9410(gobj); // inlined
            } else {
                HSD_GObjPLink_80390228(gobj);
            }
        }
    }
    PAD_STACK(16);
}

static inline HSD_GObj* ifStock_802F9F48_inline(int arg)
{
    struct ifStock_804A1378* q = &ifStock_804A1378;
    HSD_GObj* gobj = GObj_Create(14, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint((*q->x0)->joint);
    HSD_JObj* jobj2;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, fn_802F95E8, 11, 0);
    gm_8016895C(jobj, *q->x0, 0);
    lb_80011E24(jobj, &jobj2, 1, -1);
    if (!arg) {
        HSD_GObj_SetupProc(gobj, fn_802F8E08, 17);
    }
    HSD_JObjSetTranslateZ(jobj, 10000.0f);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    HSD_JObjClearFlags(jobj2, JOBJ_HIDDEN);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_TObjReqAnimAll(
        jobj2->u.dobj->mobj->tobj,
        gm_80168B34(ifStock_804A1774.x83[arg], 0, ifStock_804A1774.x1[arg]));
    HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    return gobj;
}
HSD_GObj* ifStock_802F9F48(int arg)
{
    return ifStock_802F9F48_inline(arg);
}

HSD_GObj* ifStock_802FA118(int arg)
{
    struct ifStock_804A1378* q = &ifStock_804A1378;
    HSD_GObj* gobj = GObj_Create(14, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint((*q->x0)->joint);
    HSD_JObj* jobj2;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, fn_802F9548, 11, 0);
    gm_8016895C(jobj, *q->x0, 0);
    lb_80011E24(jobj, &jobj2, 1, -1);
    if (arg == 0) {
        HSD_GObj_SetupProc(gobj, fn_802F916C, 17);
    }
    HSD_JObjSetTranslateZ(jobj, 10000.0f);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    HSD_JObjClearFlags(jobj2, JOBJ_HIDDEN);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj, 57.0f);
    HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    return gobj;
}

void ifStock_802FA2D0(int arg)
{
    HSD_JObj* jobj = ifStock_804A1378.jobj;
    if (arg > 9999) {
        arg = 9999;
    } else if (arg < 0) {
        arg = 0;
    }
    HSD_JObjReqAnimAll(jobj, 10.0f);
    if (arg >= 1000) {
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_a, arg % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_b, (arg / 10) % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_c, (arg / 100) % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_d, (arg / 1000));
    } else if (arg >= 100) {
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_b, arg % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_c, (arg / 10) % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_d, (arg / 100));
    } else if (arg >= 10) {
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_c, arg % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_d, (arg / 10));
    } else {
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_d, arg);
    }
    HSD_JObjAnimAll(jobj);
}

void ifStock_802FA5BC(int arg)
{
    struct ifStock_804A1378* q = &ifStock_804A1378;
    HSD_GObj* gobj = GObj_Create(14, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(q->x4->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, fn_802F9598, 11, 0);
    if (arg) {
        HSD_GObj_SetupProc(gobj, fn_802F8DB0, 17);
    }
    gm_8016895C(jobj, q->x4, 0);
    HSD_JObjReqAnimAll(jobj, 10.0f);
    HSD_JObjAnimAll(jobj);
    ifStock_804A1378.gobj = gobj;
    lb_80011E24(jobj, &ifStock_804A1378.jobj, 0, 1, 2, 3, 4, 5, -1);
}

void fn_802FA6C4(HSD_GObj* arg)
{
    int i;
    char* p;
    int j;
    int k;
    char* q;
    char* w;
    if (gm_8016B184() && gm_8016A1F8()) {
        if (ifStock_804A1774.x0 == 0) {
            ifStock_804A1774.x0 = 1;
            q = gm_80169520();
            w = gm_80169530();
            for (k = 0; k != 130; k++) {
                ifStock_804A1774.x10C[k + 1] = NULL;
                ifStock_804A1774.x1[k] = *q++;
                ifStock_804A1774.x83[k] = *w++;
            }
            i = 0;
            p = &ifStock_804A1774.x0 + i;
            for (; i < 130; i++, p++) {
                if (ifStock_804A1774.x10C[1 + i]) {
                    HSD_GObjPLink_80390228(ifStock_804A1774.x10C[1 + i]);
                }
                if (p[1] == (char) -2) {
                    return;
                }
                ifStock_804A1774.x10C[1 + i] = ifStock_802F9F48(i);
            }
        }
    } else {
        if (ifStock_804A1774.x0 == 1) {
            for (j = 129; j >= 0; j--) {
                if (ifStock_804A1774.x10C[1 + j]) {
                    HSD_GObjPLink_80390228(ifStock_804A1774.x10C[1 + j]);
                    ifStock_804A1774.x10C[1 + j] = NULL;
                }
            }
        }
        ifStock_804A1774.x0 = 0;
    }
}

void fn_802FA8C0(HSD_GObj* arg)
{
    struct ifStock_804A1ACC* stock = &ifStock_804A1ACC;
    HSD_GObj** cur;
    HSD_JObj* jobj;
    int i;
    int k = 0;
    float x = -21.0f;
    float y = 11.0f;
    signed char* a97c = gm_8016A97C();
    signed char* a98c = gm_8016A98C()->arr1;
    cur = stock->x10C - (0x10C / sizeof(*cur));
    for (i = 0; i < 0x82; i++, cur++, a97c++, a98c++) {
        HSD_GObj* gobj = cur[0x10C / sizeof(*cur)];
        if (gobj == NULL) {
            return;
        }
        jobj = gobj->hsd_obj;
        stock->x83[i] = *a97c;
        stock->x1[i] = *a98c;
        if (stock->x83[i] == -1) {
            HSD_JObjSetTranslateZ(jobj, 10000.0f);
        } else if (stock->x83[i] == -2) {
            int j;
            for (j = i; j < 0x82; j++) {
                HSD_GObj* g = stock->x10C[i];
                if (g != NULL) {
                    HSD_JObjSetTranslateZ(g->hsd_obj, 10000.0f);
                }
            }
            return;
        } else {
            HSD_JObjSetTranslateZ(jobj, 0.0f);
            HSD_JObjSetTranslateX(jobj, x);
            HSD_JObjSetTranslateY(jobj, y);
            k++;
            x += 2.45f;
            if (k % 5 == 0) {
                x = -21.0f;
                y -= 2.45f;
            }
        }
    }
}

static inline void ifStock_802FAEC4_call_802FA5BC(int arg)
{
    ifStock_802FA5BC(arg);
}

static inline void ifStock_802FAEC4_clear_acc(int count)
{
    int i;

    for (i = 0; i < count; i++) {
        ifStock_804A1ACC.x10C[i] = NULL;
    }
}

static inline void ifStock_802FAEC4_clear_1774(int count)
{
    int i;

    for (i = 0; i < count; i++) {
        ifStock_804A1774.x10C[i + 1] = NULL;
    }
}

static inline void ifStock_802FAEC4_init_1A8C(HSD_GObj** p)
{
    struct ifStock_804A1378* stock = &ifStock_804A1378;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;

    for (i = 0; i < 16; i++, p++) {
        *p = NULL;
        if (gm_8016B1A8()) {
            *p = ifStock_802FA118(i);
        }
    }
    if (gm_IsMultimanSmashMode()) {
        gobj = GObj_Create(14, 15, 0);
        jobj = HSD_JObjLoadJoint(stock->x4->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
        GObj_SetupGXLink(gobj, fn_802F9598, 11, 0);
        gm_8016895C(jobj, stock->x4, 0);
        HSD_JObjReqAnimAll(jobj, 10.0f);
        HSD_JObjAnimAll(jobj);
        stock->gobj = gobj;
        lb_80011E24(jobj, &stock->jobj, 0, 1, 2, 3, 4, 5, -1);
    }
}

void fn_802FAC34(HSD_GObj* arg)
{
    int i;
    int n[1];
    signed char* q;
    signed char* w;
    if (gm_8016A944()) {
        if (ifStock_804A1ACC.x0 == 0) {
            ifStock_804A1ACC.x0 = 1;
            q = gm_8016A97C();
            w = gm_8016A98C()->arr1;
            for (i = 0; i != 130; i++) {
                ifStock_804A1ACC.x10C[i] = NULL;
                ifStock_804A1ACC.x83[i] = *q++;
                ifStock_804A1ACC.x1[i] = *w++;
            }
            for (n[0] = 0; n[0] < 130; n[0]++) {
                if (ifStock_804A1ACC.x10C[n[0]]) {
                    HSD_GObjPLink_80390228(ifStock_804A1ACC.x10C[n[0]]);
                }
                if (ifStock_804A1ACC.x83[n[0]] == -2) {
                    return;
                }
                if (ifStock_804A1ACC.x1[n[0]] == -2) {
                    return;
                }
                ifStock_804A1ACC.x10C[n[0]] = ifStock_802F96D0(
                    ifStock_804A1ACC.x1[n[0]], ifStock_804A1ACC.x83[n[0]],
                    2.45f * (n[0] % 5) + -21.0f,
                    -(2.45f * (n[0] / 5) - 11.0f));
                if (n[0] == 0) {
                    HSD_GObj_SetupProc(ifStock_804A1ACC.x10C[n[0]],
                                       fn_802FA8C0, 17);
                }
            }
        }
    } else {
        if (ifStock_804A1ACC.x0 == 1) {
            for (i = 129; i >= 0; i--) {
                if (ifStock_804A1ACC.x10C[i]) {
                    HSD_GObjPLink_80390228(ifStock_804A1ACC.x10C[i]);
                    ifStock_804A1ACC.x10C[i] = NULL;
                }
            }
        }
        ifStock_804A1ACC.x0 = 0;
    }
}

void ifStock_802FAEC4(void)
{
    struct ifStock_804A1378* stock = &ifStock_804A1378;
    DynamicModelDesc** scene_models;
    memzero(stock, sizeof(*stock) - sizeof(stock->x204));
    memzero(&ifStock_804A1ACC, sizeof(ifStock_804A1ACC));
    memzero(&ifStock_804A1A8C, sizeof(ifStock_804A1A8C));
    memzero(&ifStock_804A1774, sizeof(ifStock_804A1774));
    lbArchive_LoadSections(*ifAll_GetArchive(), &scene_models, "Stc_scemdls",
                           0);
    {
        HSD_GObj** proc = (HSD_GObj**) &ifStock_804A1ACC.x108;
        HSD_GObj* gobj;

        stock->x0 = scene_models;
        stock->x4 = scene_models[1];
        *proc = NULL;
        ifStock_804A1ACC.x0 = 0;
        gobj = GObj_Create(14, 15, 0);
        HSD_GObj_SetupProc(gobj, fn_802FAC34, 17);
        *proc = gobj;
        ifStock_802FAEC4_clear_acc(130);
    }
    if (gm_80169394() == 0) {
        HSD_GObj** proc = &ifStock_804A1774.x10C[0];
        HSD_GObj* gobj;

        *proc = NULL;
        ifStock_804A1774.x0 = 0;
        gobj = GObj_Create(14, 15, 0);
        HSD_GObj_SetupProc(gobj, fn_802FA6C4, 17);
        *proc = gobj;
        ifStock_802FAEC4_clear_1774(130);
    } else if (gm_8016A1F8()) {
        ifStock_804A1774.x108 = -1;
        ifStock_802FAEC4_call_802FA5BC(1);
    }
    ifStock_802FAEC4_init_1A8C(ifStock_804A1A8C);
}

void ifStock_802FB390(void)
{
    int i;
    if (ifStock_804A1774.x10C[0] != NULL) {
        HSD_GObjPLink_80390228(ifStock_804A1774.x10C[0]);
        ifStock_804A1774.x10C[0] = NULL;
    }
    for (i = 129; i >= 0; i--) {
        if (ifStock_804A1774.x10C[i + 1] != NULL) {
            HSD_GObjPLink_80390228(ifStock_804A1774.x10C[i + 1]);
            ifStock_804A1774.x10C[i + 1] = NULL;
        }
    }
}

void ifStock_802FB41C(void)
{
    int i;
    for (i = 0; i < 16; i++) {
        if (ifStock_804A1A8C[i] != NULL) {
            HSD_GObjPLink_80390228(ifStock_804A1A8C[i]);
            ifStock_804A1A8C[i] = NULL;
        }
    }
}

void ifStock_802FB484(void)
{
    int i;
    for (i = 0; i < 16; i++) {
        if (ifStock_804A1ACC.x10C[i] != NULL) {
            HSD_GObjPLink_80390228(ifStock_804A1ACC.x10C[i]);
            ifStock_804A1ACC.x10C[i] = NULL;
        }
    }
}

static inline void copyColor(HSD_MObj* q, GXColor* arg)
{
    q->mat->diffuse.r = arg->r;
    q->mat->diffuse.g = arg->g;
    q->mat->diffuse.b = arg->b;
}

void ifStock_802FB4EC(int player, GXColor* arg)
{
    int i;
    for (i = 0; i < 7; i++) {
        copyColor(ifStock_804A1378.player[player].x4[i + 1]->u.dobj->mobj,
                  arg);
    }
}

void ifStock_802FB650(int player)
{
    struct ifStock_804A1378* x = &ifStock_804A1378;
    if (x->player[player].x0 != NULL) {
        HSD_GObjPLink_80390228(x->player[player].x0);
    }
    memzero(&x->player[player], sizeof(x->player[player]));
}

void ifStock_802FB6AC(int player)
{
    struct ifStock_804A1378* x = &ifStock_804A1378;
    if (x->player[player].x0 != NULL) {
        HSD_GObj_80390CAC(x->player[player].x0);
    }
}
