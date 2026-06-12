#include "if/ifstock.h"

#include "if/ifstock.static.h"
#include <placeholder.h>

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/jobj.h"
#include "ef/efsync.h"

#include "gm/forward.h"

#include "gm/gm_1601.h"
#include "gm/gm_16AE.h"
#include "gm/types.h"
#include "gr/ground.h"
#include "if/ifall.h"
#include "if/ifstatus.h"
#include "if/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
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

int ifStock_802F7EFC(int arg0, int arg1)
{
    Vec3 pos;
    struct ifStock_804A1378* stock;
    struct ifStock_804A1378_x204* arg0_data;
    struct ifStock_804A1378_x204* arg1_data;
    struct IfStockStealAnim* anim;
    int slot;
    int i, j;
    stock = &ifStock_804A1378;
    arg0_data = &stock->x204[arg0];
    arg1_data = &stock->x204[arg1];
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
    if (stock->player[arg1].stocks <= 5 && stock->player[arg1].stocks > 0) {
        arg1_data->x0[stock->player[arg1].stocks + 4] = 10;
    }
    i = 0;
    if (stock->player[arg1].stocks <= 5 && stock->player[arg1].stocks > 0) {
        i = 1;
    }
    if (i != 0) {
        j = stock->player[arg1].stocks;
    } else {
        j = 1;
    }
    HSD_JObjGetTranslation(stock->player[arg1].x4[0], &pos);
    HSD_JObjReqAnimAll(stock->player[arg1].x4[j], 0.0f);
    HSD_JObjAnimAll(stock->player[arg1].x4[j]);
    anim = (struct IfStockStealAnim*) &arg1_data->x0
        [0xC + (slot - 5) * sizeof(struct IfStockStealAnim)];
    HSD_JObjGetTranslation(stock->player[arg1].x4[j], &anim->start);
    anim->start.x += pos.x;
    anim->start.y += pos.y;
    anim->start.z += pos.z;
    i = 0;
    if (Player_GetStocks(arg0) < 5 && Player_GetStocks(arg0) > 0) {
        i = 1;
    }
    if (i != 0) {
        j = Player_GetStocks(arg0);
    } else {
        j = 0;
    }
    HSD_JObjGetTranslation(stock->player[arg0].x4[0], &pos);
    HSD_JObjReqAnimAll(stock->player[arg0].x4[j], 0.0f);
    HSD_JObjAnimAll(stock->player[arg0].x4[j]);
    HSD_JObjGetTranslation(stock->player[arg0].x4[1], &anim->end);
    anim->end.x += (2.4f * j) + pos.x;
    anim->end.y = anim->start.y;
    anim->end.z += pos.z;
    anim->mid.x = 0.5f * (anim->end.x + anim->start.x);
    anim->mid.z = 0.5f * (anim->end.z + anim->start.z);
    anim->mid.y = 10.0f + anim->start.y;
    return 0;
}

void ifStock_802F8298(HSD_GObj* gobj)
{
    struct IfStockUserData* user_data = GET_IFSTOCK(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    struct ifStock_804A1378* stock = &ifStock_804A1378;
    HSD_JObj* jobj2;
    HSD_JObj* jobj_anim = jobj;
    int i;
    Vec3 vecA, vecB;
    PAD_STACK(24);
    stock->player[user_data->player].stocks =
        Player_GetStocks(user_data->player);
    if (stock->player[user_data->player].stocks > 99) {
        stock->player[user_data->player].stocks = 99;
    }
    if (stock->player[user_data->player].stocks < 0) {
        stock->player[user_data->player].stocks = 1;
    }
    if (stock->player[user_data->player].stocks <= 5) {
        HSD_JObjSetFlagsAll(stock->player[user_data->player].x3C,
                            JOBJ_HIDDEN);
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
                    HSD_JObjGetTranslation(jobj2, &vecB);
                    vecB.x += vecA.x;
                    vecB.y += vecA.y;
                    vecB.z += vecA.z;
                    efSync_Spawn(0x474, gobj, &vecB);
                }
                if (stock->x204[user_data->player].x0[i + 5] < 10) {
                    stock->x204[user_data->player].x0[i + 5] += 1;
                }
            }
            HSD_JObjReqAnimAll(
                jobj2, stock->x204[user_data->player].x0[i + 5]);
            HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj,
                               gm_80168BF8(user_data->player));
            HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
        }
    } else {
        HSD_JObjClearFlagsAll(stock->player[user_data->player].x3C,
                              JOBJ_HIDDEN);
        if (stock->player[user_data->player].stocks >= 10) {
            HSD_JObjReqAnimAll(
                stock->player[user_data->player].x44,
                (int) (stock->player[user_data->player].stocks /
                       10));
            HSD_JObjReqAnimAll(
                stock->player[user_data->player].x40,
                stock->player[user_data->player].stocks % 10);
        } else {
            HSD_JObjReqAnimAll(
                stock->player[user_data->player].x44,
                stock->player[user_data->player].stocks);
            HSD_JObjSetFlagsAll(stock->player[user_data->player].x40,
                                JOBJ_HIDDEN);
        }
        for (i = 0; i < 5; i++) {
            jobj2 = stock->player[user_data->player].x4[i + 1];
            if (i == 0) {
                stock->x204[user_data->player].x0[i + 5] = 0;
            } else {
                stock->x204[user_data->player].x0[i + 5] = 10;
            }
            HSD_JObjReqAnimAll(
                jobj2, stock->x204[user_data->player].x0[i + 5]);
            HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj,
                               gm_80168BF8(user_data->player));
            HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
        }
    }
    for (i = 5; i <= 6; i++) {
        jobj2 = stock->player[user_data->player].x4[i + 1];
        if (stock->x204[user_data->player].x0[i + 5] == 0) {
            HSD_JObjSetFlagsAll(jobj2, JOBJ_HIDDEN);
        } else {
            HSD_JObjClearFlagsAll(jobj2, JOBJ_HIDDEN);
            if (stock->x204[user_data->player].x0[i + 5] <= 10) {
                lbVector_8000DE38(
                    (float (*)[4]) &stock->x204[user_data->player].x0
                        [0xC + (i - 5) * sizeof(struct IfStockStealAnim)],
                    &vecA, 0.1f * stock->x204[user_data->player].x0[i + 5]);
                HSD_JObjGetTranslation(
                    stock->player[user_data->player].x4[0], &vecB);
                vecA.x -= vecB.x;
                vecA.y -= vecB.y;
                vecA.z -= vecB.z;
                HSD_JObjSetTranslate(jobj2, &vecA);
                if (stock->x204[user_data->player].x0[i + 5] == 1) {
                    struct IfStockStealAnim* anim =
                        (struct IfStockStealAnim*) &stock->x204
                            [user_data->player]
                                .x0[0xC +
                                    (i - 5) *
                                        sizeof(struct IfStockStealAnim)];
                    vecA.x = anim->start.x;
                    vecA.y = anim->start.y;
                    efSync_Spawn(0x475, gobj, &vecA);
                } else if (stock->x204[user_data->player].x0[i + 5] ==
                           10) {
                    struct IfStockStealAnim* anim =
                        (struct IfStockStealAnim*) &stock->x204
                            [user_data->player]
                                .x0[0xC +
                                    (i - 5) *
                                        sizeof(struct IfStockStealAnim)];
                    vecA.x = anim->end.x;
                    vecA.y = anim->end.y;
                    efSync_Spawn(0x476, gobj, &vecA);
                }
                stock->x204[user_data->player].x0[i + 5]++;
            } else {
                stock->x204[user_data->player].x0[i + 5] = 0;
                stock->x204[stock->x204[user_data->player].x0[i - 2]]
                    .x0[2] = 1;
            }
        }
        HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj,
                           gm_80168BF8(user_data->player));
        HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    }
    HSD_JObjAnimAll(jobj_anim);
}

void ifStock_802F89F8(HSD_GObj* gobj)
{
    struct IfStockUserData* user_data = GET_IFSTOCK(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    int player = user_data->player;
    HSD_JObj* jobj2 = ifStock_804A1378.player[player].x4[1];
    int coins;
    int i;
    int coins2;
    int count;
    int digit;
    int divisor;
    int j;
    Player_GetCoins(player);
    PAD_STACK(32);
    coins = Player_GetCoins(user_data->player);
    ifStock_804A1378.player[user_data->player].coins = coins;
    if ((u32) coins > 99999U) {
        coins = 99999;
    }
    count = 0;
    coins2 = coins;
    for (i = 0; i < 9; i++) {
        if (coins2 == 0) {
            break;
        }
        coins2 = coins2 / 10;
        count++;
    }
    if (count > 5) {
        count = 5;
    }
    HSD_JObjReqAnimAll(jobj2, 0.0f);
    HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj,
                       gm_80168BF8(user_data->player));
    HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    for (i = 0; i < 5; i++) {
        if (i < count) {
            HSD_JObjClearFlagsAll(
                ifStock_804A1378.player[user_data->player].x4[13 - i],
                JOBJ_HIDDEN);
            if (count - i == 1) {
                digit = coins % 10;
            } else {
                divisor = 1;
                for (j = 0; j < count - i - 1; j++) {
                    divisor *= 10;
                }
                digit = (coins / divisor) % 10;
            }
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
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;
    int counter = 0;
    signed char* thing = gm_80169520();
    float x = -21.0f;
    float y = 11.0f;
    for (i = 0; i < 130; i++) {
        HSD_GObj* x110 = ifStock_804A1774.x10C[i + 1];
        if (x110 == NULL) {
            break;
        }
        jobj = x110->hsd_obj;
        ifStock_804A1774.x1[i] = thing[i];
        if (thing[i] == -1) {
            HSD_JObjSetTranslateZ(jobj, 10000.0f);
        } else if (thing[i] == -2) {
            int j;
            for (j = i; j < 130; j++) {
                jobj = x110->hsd_obj;
                HSD_JObjSetTranslateZ(jobj, 10000.0f);
            }
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
    struct HudIndex* x = ifStatus_802F4910();
    if (!x->players[p->player].flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, renderpass);
    }
}

void fn_802F9548(HSD_GObj* gobj, int renderpass)
{
    struct HudIndex* x = ifStatus_802F4910();
    if (!x->players[0].flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, renderpass);
    }
}

void fn_802F9598(HSD_GObj* gobj, int renderpass)
{
    struct HudIndex* x = ifStatus_802F4910();
    if (!x->players[0].flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, renderpass);
    }
}

void fn_802F95E8(HSD_GObj* gobj, int renderpass)
{
    struct HudIndex* x = ifStatus_802F4910();
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
    struct HudIndex* x = ifStatus_802F4910();
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
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
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

void ifStock_802F98E8(unsigned char player, int b)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    struct ifStock_804A1378_x204* user_data;
    struct ifStock_804A1378_per_player* r26;
    int i;
    lbl_8046B6A0_t* ae44;
    PAD_STACK(8);
    if (ifStock_804A1378.x0 != NULL) {
        user_data = &ifStock_804A1378.x204[player];
        ifStock_804A1378.x204[player].x0[0] = player;
        ifStock_804A1378.x204[player].x0[1] = b;
        ifStock_804A1378.x204[player].x0[2] = 1;
        r26 = &ifStock_804A1378.player[player];
        if (ifStock_804A1378.player[player].x0 != NULL) {
            HSD_GObjPLink_80390228(ifStock_804A1378.player[player].x0);
        }
        gobj = GObj_Create(14, 15, 0);
        gobj->user_data = user_data;
        if (gobj != NULL) {
            jobj = HSD_JObjLoadJoint((*ifStock_804A1378.x0)->joint);
            if (jobj != NULL) {
                HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
                GObj_SetupGXLink(gobj, fn_802F94E0, 11, 0);
                gm_8016895C(jobj, *ifStock_804A1378.x0, 0);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_GObj_SetupProc(gobj, fn_802F9410, 17);
                HSD_JObjSetTranslate(jobj, ifAll_802F3424(player));
                lb_80011E24(jobj, ifStock_804A1378.player[player].x4, 0, 1, 2,
                            3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                            -1);
                r26->x0 = gobj;
                ifStock_804A1378.player[player].coins =
                    Player_GetCoins(player);
                ifStock_804A1378.player[player].stocks =
                    Player_GetStocks(player);
                if (ifStock_804A1378.player[player].stocks < 0) {
                    ifStock_804A1378.player[player].stocks = 1;
                }
                switch (b) {
                case 0:
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x24,
                                        JOBJ_HIDDEN);
                    if (ifStock_804A1378.player[player].stocks <= 5) {
                        HSD_JObjSetFlagsAll(
                            ifStock_804A1378.player[player].x3C, JOBJ_HIDDEN);
                        for (i = 0; i < 7; i++) {
                            jobj = ifStock_804A1378.player[player].x4[i + 1];
                            if (i < ifStock_804A1378.player[player].stocks ||
                                i >= 5)
                            {
                                user_data->x0[i + 5] = 0;
                                if (i >= 5) {
                                    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                                }
                            } else {
                                user_data->x0[i + 5] = 10;
                                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                            }
                            HSD_JObjReqAnimAll(jobj, user_data->x0[i + 5]);
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
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x3C,
                                        JOBJ_HIDDEN);
                    for (i = 0; i < 7; i++) {
                        jobj = ifStock_804A1378.player[player].x4[i + 1];
                        if (i == 0) {
                            user_data->x0[i + 5] = 0;
                        } else {
                            user_data->x0[i + 5] = 10;
                        }
                        if (i < 5) {
                            HSD_JObjReqAnimAll(jobj, user_data->x0[i + 5]);
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
                                        0x10);
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x2C,
                                        0x10);
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x30,
                                        0x10);
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x34,
                                        0x10);
                    HSD_JObjSetFlagsAll(ifStock_804A1378.player[player].x3C,
                                        0x10);
                    for (i = 0; i < 7; i++) {
                        jobj = ifStock_804A1378.player[player].x4[i + 1];
                        if (i == 0) {
                            user_data->x0[i + 5] = 0;
                        } else {
                            user_data->x0[i + 5] = 10;
                        }
                        if (i < 5) {
                            HSD_JObjReqAnimAll(jobj, user_data->x0[i + 5]);
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
                ae44 = gm_8016AE44();
                if (ae44->FighterMatchInfo[player].x4_b1) {
                    GXColor c = { 0x08, 0x08, 0x08, 0x80 };
                    ifStock_802FB4EC(player, &c);
                } else if (ae44->FighterMatchInfo[player].x4_b0) {
                    GXColor c = { 0x3C, 0x3C, 0x46, 0x80 };
                    ifStock_802FB4EC(player, &c);
                }
                fn_802F9410(gobj); // inlined
            } else {
                HSD_GObjPLink_80390228(gobj);
            }
        }
    }
}

HSD_GObj* ifStock_802F9F48(int arg)
{
    HSD_GObj* gobj = GObj_Create(14, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint((*ifStock_804A1378.x0)->joint);
    HSD_JObj* jobj2;
    float f;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, fn_802F95E8, 11, 0);
    gm_8016895C(jobj, *ifStock_804A1378.x0, 0);
    lb_80011E24(jobj, &jobj2, 1, -1);
    if (!arg) {
        HSD_GObj_SetupProc(gobj, fn_802F8E08, 17);
    }
    HSD_JObjSetTranslateZ(jobj, 10000.0f);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    HSD_JObjClearFlags(jobj2, JOBJ_HIDDEN);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    f = gm_80168B34(ifStock_804A1774.x83[arg], 0, ifStock_804A1774.x1[arg]);
    HSD_TObjReqAnimAll(jobj2->u.dobj->mobj->tobj, f);
    HSD_AObjSetRate(jobj2->u.dobj->mobj->tobj->aobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    return gobj;
}

HSD_GObj* ifStock_802FA118(int arg)
{
    struct ifStock_804A1378* q = &ifStock_804A1378;
    HSD_GObj* gobj = GObj_Create(14, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint((*q->x0)->joint);
    HSD_JObj* jobj2;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
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
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_d, (int) (arg / 1000));
    } else if (arg >= 100) {
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_b, arg % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_c, (arg / 10) % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_d, (int) (arg / 100));
    } else if (arg >= 10) {
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_c, arg % 10);
        HSD_JObjReqAnimAll(ifStock_804A1378.jobj_d, (int) (arg / 10));
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
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
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
                if (p[1] == -2) {
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
    HSD_JObj* jobj;
    int k = 0;
    int i;
    signed char* a97c = gm_8016A97C();
    signed char* a98c = (signed char*) gm_8016A98C();
    float x = -21.0f;
    float y = 11.0f;
    for (i = 0; i < 0x82; i++) {
        HSD_GObj* gobj = ifStock_804A1ACC.x10C[i];
        if (gobj == NULL) {
            return;
        }
        jobj = gobj->hsd_obj;
        ifStock_804A1ACC.x83[i] = a97c[i];
        ifStock_804A1ACC.x1[i] = a98c[i];
        if (ifStock_804A1ACC.x83[i] == -1) {
            HSD_JObjSetTranslateZ(jobj, 10000.0f);
        } else if (ifStock_804A1ACC.x83[i] == -2) {
            int j;
            for (j = i; j < 0x82; j++) {
                HSD_GObj* g = ifStock_804A1ACC.x10C[i];
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

void fn_802FAC34(HSD_GObj* arg)
{
    int i;
    char* q;
    char* w;
    if (gm_8016A944()) {
        if (ifStock_804A1ACC.x0 == 0) {
            ifStock_804A1ACC.x0 = 1;
            q = gm_8016A97C();
            w = (char*) gm_8016A98C();
            for (i = 0; i < 130; i++) {
                ifStock_804A1ACC.x10C[i + 1] = NULL;
                ifStock_804A1ACC.x1[i] = q[i];
                ifStock_804A1ACC.x83[i] = w[i];
            }
            for (i = 0; i < 130; i++) {
                if (ifStock_804A1ACC.x10C[i]) {
                    HSD_GObjPLink_80390228(ifStock_804A1ACC.x10C[i]);
                }
                if (ifStock_804A1ACC.x83[i] == -2) {
                    return;
                }
                if (ifStock_804A1ACC.x1[i] == -2) {
                    return;
                }
                ifStock_804A1ACC.x10C[1 + i] = ifStock_802F96D0(
                    ifStock_804A1ACC.x1[i], ifStock_804A1ACC.x83[i],
                    2.45f * (i % 5) + -21.0f,
                    -(2.45f * (int) (i / 5) - 11.0f));
                if (i == 0) {
                    HSD_GObj_SetupProc(ifStock_804A1ACC.x10C[i], fn_802FA8C0,
                                       17);
                }
            }
        }
    } else {
        if (ifStock_804A1ACC.x0 == 1) {
            for (i = 0; i < 130; i++) {
                if (ifStock_804A1ACC.x10C[1 + i]) {
                    HSD_GObjPLink_80390228(ifStock_804A1ACC.x10C[1 + i]);
                    ifStock_804A1ACC.x10C[1 + i] = NULL;
                }
            }
        }
        ifStock_804A1ACC.x0 = 0;
    }
}

#pragma push
#pragma dont_inline on
void ifStock_802FAEC4(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    DynamicModelDesc** sp18;
    int i;
    memzero(&ifStock_804A1378, sizeof(ifStock_804A1378));
    memzero(&ifStock_804A1ACC, sizeof(ifStock_804A1ACC));
    memzero(&ifStock_804A1A8C, sizeof(ifStock_804A1A8C));
    memzero(&ifStock_804A1774, sizeof(ifStock_804A1774));
    lbArchive_LoadSections(*ifAll_802F3690(), (void*) &sp18, "Stc_scemdls", 0);
    ifStock_804A1378.x0 = sp18;
    ifStock_804A1378.x4 = sp18[1];
    ifStock_804A1ACC.x108 = 0;
    ifStock_804A1ACC.x0 = 0;
    gobj = GObj_Create(14, 15, 0);
    HSD_GObj_SetupProc(gobj, fn_802FAC34, 17);
    ifStock_804A1ACC.x108 = (int) gobj;
    for (i = 0; i < 130; i++) {
        ifStock_804A1ACC.x10C[i] = NULL;
    }
    if (gm_80169394() == 0) {
        ifStock_804A1774.x10C[0] = NULL;
        ifStock_804A1774.x0 = 0;
        gobj = GObj_Create(14, 15, 0);
        HSD_GObj_SetupProc(gobj, fn_802FA6C4, 17);
        ifStock_804A1774.x10C[0] = gobj;
        for (i = 0; i < 130; i++) {
            ifStock_804A1774.x10C[i + 1] = NULL;
        }
    } else if (gm_8016A1F8()) {
        ifStock_804A1774.x108 = -1;
        ifStock_802FA5BC(1); // not inlined
    }
    for (i = 0; i < 16; i++) {
        ifStock_804A1A8C[i] = NULL;
        if (gm_8016B1A8()) {
            ifStock_804A1A8C[i] = ifStock_802FA118(i);
        }
    }
    if (gm_80182510()) {
        // ifStock_802FA5BC(0); // inlined
        gobj = GObj_Create(14, 15, 0);
        jobj = HSD_JObjLoadJoint(ifStock_804A1378.x4->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, fn_802F9598, 11, 0);
        gm_8016895C(jobj, ifStock_804A1378.x4, 0);
        HSD_JObjReqAnimAll(jobj, 10.0f);
        HSD_JObjAnimAll(jobj);
        ifStock_804A1378.gobj = gobj;
        lb_80011E24(jobj, &ifStock_804A1378.jobj, 0, 1, 2, 3, 4, 5, -1);
    }
}
#pragma pop

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
