#include <string.h>
#include <baselib/texp.h>
#include <sysdolphin/baselib/class.h>

HSD_TExpType HSD_TExpGetType(HSD_TExp* texp)
{
    if (texp == NULL) {
        return HSD_TE_ZERO;
    }
    if ((uintptr_t) texp == -1U) {
        return HSD_TE_TEX;
    }
    if ((uintptr_t) texp == -2U) {
        return HSD_TE_RAS;
    }
    return texp->type;
}

void HSD_TExpRef(HSD_TExp* texp, u8 sel)
{
    HSD_TExpType type = HSD_TExpGetType(texp);
    switch (type) {
    case HSD_TE_TEV:
        if (sel == true) {
            texp->tev.c_ref += 1;
            return;
        } else {
            texp->tev.a_ref += 1;
            return;
        }
        break;
    case HSD_TE_CNST:
        texp->cnst.ref += 1;
        break;
    }
}

void HSD_TExpUnref(HSD_TExp* texp, u8 sel)
{
    s32 i;
    HSD_TExpType type = HSD_TExpGetType(texp);

    if (type != HSD_TE_CNST) {
        if (type >= HSD_TE_CNST || type != HSD_TE_TEV) {
            return;
        }
        if (sel == true) {
            if (texp->tev.c_ref != 0) {
                texp->tev.c_ref -= 1;
            }
        } else if (texp->tev.a_ref != 0) {
            texp->tev.a_ref -= 1;
        }

        if (texp->tev.c_ref == 0 && texp->tev.a_ref == 0) {
            for (i = 0; i < 4; i++) {
                HSD_TExpUnref(texp->tev.c_in[i].exp, texp->tev.c_in[i].sel);
                HSD_TExpUnref(texp->tev.a_in[i].exp, texp->tev.a_in[i].sel);
            }
        }
        return;
    }

    if (texp->cnst.ref != 0) {
        texp->cnst.ref -= 1;
        return;
    }
}

static HSD_TExp* TevAlloc()
{
    HSD_TExp* texp = hsdAllocMemPiece(sizeof(HSD_TETev));
    HSD_ASSERT(62, texp);
    return texp;
}

static HSD_TExp* CnstAlloc()
{
    HSD_TExp* texp = hsdAllocMemPiece(sizeof(HSD_TECnst));
    HSD_ASSERT(70, texp);
    return texp;
}

void HSD_TExpFree(HSD_TExp* texp)
{
    switch (HSD_TExpGetType(texp)) {
    case HSD_TE_TEV:
        hsdFreeMemPiece(texp, sizeof(HSD_TETev));
        break;
    case HSD_TE_CNST:
        hsdFreeMemPiece(texp, sizeof(HSD_TECnst));
        break;
    }
}

HSD_TExp* HSD_TExpFreeList(HSD_TExp* texp_list, HSD_TExpType type, s32 all)
{
    HSD_TExp** handle;
    HSD_TExp* ptr;
    HSD_TExp* next;

    handle = &texp_list;

    if (all != 0) {
        while (*handle != NULL) {
            if (type == HSD_TE_ALL || type == (*handle)->type) {
                switch ((*handle)->type) {
                case HSD_TE_TEV:
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                case HSD_TE_CNST:
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                default:
                    __assert(__FILE__, 219, "0");
                }
            }
            handle = &(*handle)->tev.next;
        }
    } else {
        if (type == HSD_TE_ALL || type == HSD_TE_TEV) {
            for (ptr = texp_list; ptr != NULL; ptr = ptr->tev.next) {
                switch (ptr->type) {
                case HSD_TE_TEV:
                    if (ptr->tev.c_ref == 0 && ptr->tev.c_ref == 0) {
                        HSD_TExpUnref(ptr, 1);
                        HSD_TExpUnref(ptr, 5);
                    }
                    break;
                }
            }
        }

        while (*handle != NULL) {
            if (type == HSD_TE_ALL || type == (*handle)->type) {
                switch ((*handle)->type) {
                case HSD_TE_TEV:
                    if ((*handle)->tev.c_ref != 0 || (*handle)->tev.a_ref != 0)
                    {
                        break;
                    }
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                case HSD_TE_CNST:
                    if ((*handle)->cnst.ref != 0) {
                        break;
                    }
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                default:
                    __assert(__FILE__, 267, "0");
                }
            }
            handle = &(*handle)->tev.next;
        }
    }

    return texp_list;
}

HSD_TExp* HSD_TExpTev(HSD_TExp** texp_list)
{
    int i;
    HSD_TExp* texp;

    HSD_ASSERT(294, texp_list);
    texp = TevAlloc();
    memset(texp, 0xFF, sizeof(HSD_TETev));
    texp->type = HSD_TE_TEV;
    texp->tev.next = *texp_list;
    *texp_list = texp;
    texp->tev.c_ref = 0;
    texp->tev.a_ref = 0;
    texp->tev.tex = NULL;
    for (i = 0; i < 4; i++) {
        texp->tev.c_in[i].exp = NULL;
        texp->tev.a_in[i].exp = NULL;
    }
    return texp;
}

HSD_TExp* HSD_TExpCnst(void* val, HSD_TEInput comp, HSD_TEType type,
                       HSD_TExp** texp_list)
{
    HSD_TExp* texp;

    HSD_ASSERT(361, texp_list);

    texp = *texp_list;
    do {
        while (texp) {
            if (texp->type == HSD_TE_CNST && texp->cnst.val == val &&
                texp->cnst.comp == comp)
            {
                HSD_ASSERT(368, texp->cnst.ctype == type);
                return texp;
            }
            texp = texp->cnst.next;
        }

        if (comp == HSD_TE_0) {
            return NULL;
        }
        texp = CnstAlloc();
        texp->cnst.type = HSD_TE_CNST;
        texp->cnst.next = (*texp_list);
        *texp_list = texp;
        texp->cnst.ref = 0;
        texp->cnst.val = val;
        texp->cnst.comp = comp;
        texp->cnst.ctype = type;
        texp->cnst.reg = 0xFF;
        texp->cnst.idx = 0xFF;
        return texp;
    } while (true);

    return texp;
}

void HSD_TExpColorOp(HSD_TExp* texp, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, u8 clamp)
{
    s32 unused[2];

    HSD_ASSERT(408, texp);
    HSD_ASSERT(409, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.c_op = op;
    texp->tev.c_clamp = (clamp ? GX_ENABLE : GX_DISABLE);
    if (op <= GX_TEV_SUB) {
        texp->tev.c_bias = bias;
        texp->tev.c_scale = scale;
    } else {
        texp->tev.c_bias = 0;
        texp->tev.c_scale = 0;
    }
}

void HSD_TExpAlphaOp(HSD_TExp* texp, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, u8 clamp)
{
    s32 unused[2];

    HSD_ASSERT(434, texp);
    HSD_ASSERT(435, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.a_op = op;
    texp->tev.a_clamp = (clamp ? GX_ENABLE : GX_DISABLE);
    if (op <= GX_TEV_SUB) {
        texp->tev.a_bias = bias;
        texp->tev.a_scale = scale;
    } else {
        texp->tev.a_bias = 0;
        texp->tev.a_scale = 0;
    }
}

static void HSD_TExpColorInSub(HSD_TETev* tev, HSD_TEInput sel, HSD_TExp* exp,
                               s32 idx)
{
    HSD_TEArg prev;
    u8 ksel;

    prev = tev->c_in[idx];
    tev->c_in[idx].type = HSD_TExpGetType(exp);
    tev->c_in[idx].sel = sel;
    tev->c_in[idx].exp = exp;
    tev->c_in[idx].arg = 0xFF;

    switch (sel) {
    case HSD_TE_0:
        tev->c_in[idx].arg = GX_CC_ZERO;
        tev->c_in[idx].type = HSD_TE_ZERO;
        tev->c_in[idx].exp = NULL;
        goto UNREF;
    case HSD_TE_1:
        tev->c_in[idx].arg = GX_CC_ONE;
        tev->c_in[idx].type = HSD_TE_IMM;
        tev->c_in[idx].exp = NULL;
        goto UNREF;
    case HSD_TE_4_8:
        tev->c_in[idx].arg = GX_CC_HALF;
        tev->c_in[idx].type = HSD_TE_IMM;
        tev->c_in[idx].exp = NULL;
        goto UNREF;
    case HSD_TE_1_8:
    case HSD_TE_2_8:
    case HSD_TE_3_8:
    case HSD_TE_5_8:
    case HSD_TE_6_8:
    case HSD_TE_7_8:
        tev->c_in[idx].arg = GX_CC_KONST;
        switch (sel) {
        case HSD_TE_1_8:
            ksel = GX_TEV_KCSEL_1_8;
            break;
        case HSD_TE_2_8:
            ksel = GX_TEV_KCSEL_1_4;
            break;
        case HSD_TE_3_8:
            ksel = GX_TEV_KCSEL_3_8;
            break;
        case HSD_TE_5_8:
            ksel = GX_TEV_KCSEL_5_8;
            break;
        case HSD_TE_6_8:
            ksel = GX_TEV_KCSEL_3_4;
            break;
        case HSD_TE_7_8:
            ksel = GX_TEV_KCSEL_7_8;
            break;
        default:
            HSD_ASSERT(0x1F2, 0);
            break;
        }

        if (tev->kcsel == HSD_TE_UNDEF) {
            tev->kcsel = ksel;
        } else if (tev->kcsel == ksel) {
            HSD_Panic(__FILE__, 0x1F7,
                      "tev can't select multiple konst input.\n");
        }
        tev->c_in[idx].type = HSD_TE_KONST;
        goto UNREF;
    }

    switch (tev->c_in[idx].type) {
    case HSD_TE_ZERO:
        tev->c_in[idx].type = HSD_TE_ZERO;
        tev->c_in[idx].sel = HSD_TE_0;
        tev->c_in[idx].arg = GX_CC_ZERO;
        break;
    case HSD_TE_TEV: {
        u8 swap;
        HSD_ASSERT(0x207, sel == HSD_TE_RGB || sel == HSD_TE_A);
        HSD_ASSERT(0x209, idx == 3 || sel != HSD_TE_RGB || exp->tev.c_clamp);
        HSD_ASSERT(0x20A, idx == 3 || sel != HSD_TE_A || exp->tev.a_clamp);
        swap = tev->c_in[idx].sel;
        switch (HSD_TExpGetType(tev->c_in[idx].exp)) {
        case HSD_TE_TEV:
            if (swap == 1) {
                tev->c_in[idx].exp->tev.c_ref += 1;
            } else {
                tev->c_in[idx].exp->tev.a_ref += 1;
            }
            break;
        case HSD_TE_CNST: /* switch 2 */
            tev->c_in[idx].exp->cnst.ref += 1;
            break;
        }
    } break;
    case HSD_TE_CNST: {
        u8 swap;
        tev->c_in[idx].sel = exp->cnst.comp;
        swap = tev->c_in[idx].sel;
        switch (HSD_TExpGetType(tev->c_in[idx].exp)) {
        case HSD_TE_TEV:
            if (swap == 1) {
                tev->c_in[idx].exp->tev.c_ref += 1;
            } else {
                tev->c_in[idx].exp->tev.a_ref += 1;
            }
            break;
        case HSD_TE_CNST:
            tev->c_in[idx].exp->cnst.ref += 1;
            break;
        }
    } break;
    case HSD_TE_TEX: {
        u8 swap = HSD_TE_UNDEF;
        switch (sel) {
        case HSD_TE_RGB:
            tev->c_in[idx].arg = GX_CC_TEXC;
            swap = GX_TEV_SWAP0;
            break;
        case HSD_TE_R:
            tev->c_in[idx].arg = GX_CC_TEXC;
            swap = GX_TEV_SWAP1;
            break;
        case HSD_TE_G:
            tev->c_in[idx].arg = GX_CC_TEXC;
            swap = GX_TEV_SWAP2;
            break;
        case HSD_TE_B:
            tev->c_in[idx].arg = GX_CC_TEXC;
            swap = GX_TEV_SWAP3;
            break;
        case HSD_TE_A:
            tev->c_in[idx].arg = GX_CC_TEXA;
            break;
        default:
            HSD_ASSERT(0x22D, 0);
            break;
        }
        if (tev->tex_swap == HSD_TE_UNDEF) {
            tev->tex_swap = swap;
        } else {
            HSD_ASSERT(0x232, swap == HSD_TE_UNDEF || tev->tex_swap == swap);
        }
    } break;
    case HSD_TE_RAS: {
        u8 swap = HSD_TE_UNDEF;
        switch (sel) {
        case HSD_TE_RGB:
            tev->c_in[idx].arg = GX_CC_RASC;
            swap = GX_TEV_SWAP0;
            break;
        case HSD_TE_R:
            tev->c_in[idx].arg = GX_CC_RASC;
            swap = GX_TEV_SWAP1;
            break;
        case HSD_TE_G:
            tev->c_in[idx].arg = GX_CC_RASC;
            swap = GX_TEV_SWAP2;
            break;
        case HSD_TE_B:
            tev->c_in[idx].arg = GX_CC_RASC;
            swap = GX_TEV_SWAP3;
            break;
        case HSD_TE_A:
            tev->c_in[idx].arg = GX_CC_RASA;
            break;
        default:
            HSD_ASSERT(0x25D, 0);
            break;
        }
        if (tev->ras_swap == HSD_TE_UNDEF) {
            tev->ras_swap = swap;
        } else {
            HSD_ASSERT(0x262, swap == HSD_TE_UNDEF || tev->ras_swap == swap);
        }
    } break;
    default:
        HSD_ASSERT(0x274, 0);
        break;
    }
UNREF:
    HSD_TExpUnref(prev.exp, prev.sel);
}

void HSD_TExpColorIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    HSD_ASSERT(0x2B3, texp);
    HSD_ASSERT(0x2B4, HSD_TExpGetType(texp) == HSD_TE_TEV);

    tev = &texp->tev;
    HSD_TExpColorInSub(tev, sel_a, exp_a, 0);
    HSD_TExpColorInSub(tev, sel_b, exp_b, 1);
    HSD_TExpColorInSub(tev, sel_c, exp_c, 2);
    HSD_TExpColorInSub(tev, sel_d, exp_d, 3);
}

static void HSD_TExpAlphaInSub(HSD_TETev* tev, HSD_TEInput sel, HSD_TExp* exp,
                               s32 idx)
{
    HSD_TEArg prev;
    u8 ksel;
}

void HSD_TExpAlphaIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    HSD_ASSERT(0x335, texp);
    HSD_ASSERT(0x336, HSD_TExpGetType(texp) == HSD_TE_TEV);

    tev = &texp->tev;
    HSD_TExpAlphaInSub(tev, sel_a, exp_a, 0);
    HSD_TExpAlphaInSub(tev, sel_b, exp_b, 1);
    HSD_TExpAlphaInSub(tev, sel_c, exp_c, 2);
    HSD_TExpAlphaInSub(tev, sel_d, exp_d, 3);
}

void HSD_TExpOrder(HSD_TExp* texp, HSD_TObj* tex, GXChannelID chan)
{
    HSD_ASSERT(0x345, texp);
    HSD_ASSERT(0x346, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.tex = tex;
    if (chan == GX_COLOR_NULL) {
        texp->tev.chan = GX_COLOR_NULL;
        return;
    }
    texp->tev.chan = chan;
}

static int AssignColorReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    HSD_TECnst* cnst;
    int j;
}
