#include <string.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXTev.h>
#include <baselib/texp.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/texpdag.h>
#include <sysdolphin/baselib/tobj.h>

#define HSD_ASSERT3(file, line, cond)                                         \
    ((cond) ? ((void) 0) : __assert((file), (line), #cond))

#define HSD_ASSERT4(file, line, msg, cond)                                    \
    ((cond) ? (void) 0 : __assert(file, line, msg))

static char HSD_TExp_804D5FC8[7] = "texp.c\0";
static char HSD_TExp_80407738[11] = "texp_list\0";

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
    HSD_ASSERT3(HSD_TExp_804D5FC8, 62, texp);
    return texp;
}

static HSD_TExp* CnstAlloc()
{
    HSD_TExp* texp = hsdAllocMemPiece(sizeof(HSD_TECnst));
    HSD_ASSERT3(HSD_TExp_804D5FC8, 70, texp);
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
                    HSD_ASSERT3(HSD_TExp_804D5FC8, 219, 0);
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
                    HSD_ASSERT3(HSD_TExp_804D5FC8, 267, 0);
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

    HSD_ASSERT4(HSD_TExp_804D5FC8, 294, HSD_TExp_80407738, texp_list);
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

    HSD_ASSERT4(HSD_TExp_804D5FC8, 361, HSD_TExp_80407738, texp_list);

    texp = *texp_list;
    do {
        while (texp) {
            if (texp->type == HSD_TE_CNST && texp->cnst.val == val &&
                texp->cnst.comp == comp)
            {
                HSD_ASSERT3(HSD_TExp_804D5FC8, 368, texp->cnst.ctype == type);
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
    HSD_ASSERT3(HSD_TExp_804D5FC8, 408, texp);
    HSD_ASSERT3(HSD_TExp_804D5FC8, 409, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.c_op = op;
    texp->tev.c_clamp = (clamp ? GX_ENABLE : GX_DISABLE);
    if ((u32) op <= GX_TEV_SUB) {
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
    HSD_ASSERT3(HSD_TExp_804D5FC8, 434, texp);
    HSD_ASSERT3(HSD_TExp_804D5FC8, 435, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.a_op = op;
    texp->tev.a_clamp = (clamp ? GX_ENABLE : GX_DISABLE);
    if ((u32) op <= GX_TEV_SUB) {
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
        break;
    case HSD_TE_1:
        tev->c_in[idx].arg = GX_CC_ONE;
        tev->c_in[idx].type = HSD_TE_IMM;
        tev->c_in[idx].exp = NULL;
        break;
    case HSD_TE_4_8:
        tev->c_in[idx].arg = GX_CC_HALF;
        tev->c_in[idx].type = HSD_TE_IMM;
        tev->c_in[idx].exp = NULL;
        break;
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
            HSD_ASSERT3(HSD_TExp_804D5FC8, 498, 0);
            break;
        }

        if (tev->kcsel == HSD_TE_UNDEF) {
            tev->kcsel = ksel;
        } else if (tev->kcsel == ksel) {
            HSD_Panic(HSD_TExp_804D5FC8, 503,
                      "tev can't select multiple konst input.\n");
        }
        tev->c_in[idx].type = HSD_TE_KONST;
        break;

    default: {
        switch (tev->c_in[idx].type) {
        case HSD_TE_ZERO:
            tev->c_in[idx].type = HSD_TE_ZERO;
            tev->c_in[idx].sel = HSD_TE_0;
            tev->c_in[idx].arg = GX_CC_ZERO;
            break;
        case HSD_TE_TEV: {
            u8 swap;
            HSD_ASSERT3(HSD_TExp_804D5FC8, 519,
                        sel == HSD_TE_RGB || sel == HSD_TE_A);
            HSD_ASSERT3(HSD_TExp_804D5FC8, 521,
                        idx == 3 || sel != HSD_TE_RGB || exp->tev.c_clamp);
            HSD_ASSERT3(HSD_TExp_804D5FC8, 522,
                        idx == 3 || sel != HSD_TE_A || exp->tev.a_clamp);
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
                HSD_ASSERT3(HSD_TExp_804D5FC8, 557, 0);
                break;
            }
            if (tev->tex_swap == HSD_TE_UNDEF) {
                tev->tex_swap = swap;
            } else {
                HSD_ASSERT3(HSD_TExp_804D5FC8, 562,
                            swap == HSD_TE_UNDEF || tev->tex_swap == swap);
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
                HSD_ASSERT3(HSD_TExp_804D5FC8, 605, 0);
                break;
            }
            if (tev->ras_swap == HSD_TE_UNDEF) {
                tev->ras_swap = swap;
            } else {
                HSD_ASSERT3(HSD_TExp_804D5FC8, 610,
                            swap == HSD_TE_UNDEF || tev->ras_swap == swap);
            }
        } break;
        default:
            HSD_ASSERT3(HSD_TExp_804D5FC8, 628, 0);
            break;
        }
    }
    }
    HSD_TExpUnref(prev.exp, prev.sel);
}

void HSD_TExpColorIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    HSD_ASSERT3(HSD_TExp_804D5FC8, 691, texp);
    HSD_ASSERT3(HSD_TExp_804D5FC8, 692, HSD_TExpGetType(texp) == HSD_TE_TEV);

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

    prev = tev->a_in[idx];
    tev->a_in[idx].sel = sel;
    tev->a_in[idx].exp = exp;
    tev->a_in[idx].type = HSD_TExpGetType(exp);
    tev->a_in[idx].arg = 0xFF;

    switch (sel) {
    case HSD_TE_0:
        tev->a_in[idx].type = HSD_TE_ZERO;
        tev->a_in[idx].arg = GX_CA_ZERO;
        tev->a_in[idx].exp = NULL;
        break;

    case HSD_TE_1:
    case HSD_TE_1_8:
    case HSD_TE_2_8:
    case HSD_TE_3_8:
    case HSD_TE_4_8:
    case HSD_TE_5_8:
    case HSD_TE_6_8:
    case HSD_TE_7_8:
        tev->a_in[idx].exp = NULL;
        tev->a_in[idx].arg = GX_CA_KONST;
        switch (sel) {
        case HSD_TE_1_8:
            ksel = GX_TEV_KASEL_1_8;
            break;
        case HSD_TE_2_8:
            ksel = GX_TEV_KASEL_1_4;
            break;
        case HSD_TE_3_8:
            ksel = GX_TEV_KASEL_3_8;
            break;
        case HSD_TE_4_8:
            ksel = GX_TEV_KASEL_1_2;
            break;
        case HSD_TE_5_8:
            ksel = GX_TEV_KASEL_5_8;
            break;
        case HSD_TE_6_8:
            ksel = GX_TEV_KASEL_3_4;
            break;
        case HSD_TE_7_8:
            ksel = GX_TEV_KASEL_7_8;
            break;
        default:
            ksel = GX_TEV_KASEL_1;
            break;
        }

        if (tev->kasel == HSD_TE_UNDEF) {
            tev->kasel = ksel;
        } else {
            HSD_ASSERT3(HSD_TExp_804D5FC8, 748, tev->kasel == ksel);
        }
        tev->a_in[idx].type = HSD_TE_KONST;
        break;

    default: {
        switch (tev->a_in[idx].type) {
        case HSD_TE_ZERO:
            tev->a_in[idx].exp = NULL;
            tev->a_in[idx].type = HSD_TE_ZERO;
            tev->a_in[idx].sel = HSD_TE_0;
            tev->a_in[idx].arg = GX_CA_ZERO;
            break;
        case HSD_TE_TEV:
            HSD_ASSERT3(HSD_TExp_804D5FC8, 771, sel == HSD_TE_A);
            HSD_ASSERT3(HSD_TExp_804D5FC8, 772, idx == 3 || exp->tev.a_clamp);
            HSD_TExpRef(tev->a_in[idx].exp, tev->a_in[idx].sel);
            break;
        case HSD_TE_CNST:
            HSD_ASSERT3(HSD_TExp_804D5FC8, 776,
                        sel == HSD_TE_A || sel == HSD_TE_X);
            HSD_ASSERT3(HSD_TExp_804D5FC8, 777, exp->cnst.comp == HSD_TE_X);
            tev->a_in[idx].sel = HSD_TE_X;
            HSD_TExpRef(tev->a_in[idx].exp, tev->a_in[idx].sel);
            break;
        case HSD_TE_TEX:
            HSD_ASSERT3(HSD_TExp_804D5FC8, 782, sel == HSD_TE_A);
            tev->a_in[idx].arg = GX_CA_TEXA;
            break;
        case HSD_TE_RAS:
            HSD_ASSERT3(HSD_TExp_804D5FC8, 786, sel == HSD_TE_A);
            tev->a_in[idx].arg = GX_CA_RASA;
            break;
        default:
            HSD_ASSERT3(HSD_TExp_804D5FC8, 790, 0);
            break;
        }
    }
    }
    HSD_TExpUnref(prev.exp, prev.sel);
}

void HSD_TExpAlphaIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    HSD_ASSERT3(HSD_TExp_804D5FC8, 821, texp);
    HSD_ASSERT3(HSD_TExp_804D5FC8, 822, HSD_TExpGetType(texp) == HSD_TE_TEV);

    tev = &texp->tev;
    HSD_TExpAlphaInSub(tev, sel_a, exp_a, 0);
    HSD_TExpAlphaInSub(tev, sel_b, exp_b, 1);
    HSD_TExpAlphaInSub(tev, sel_c, exp_c, 2);
    HSD_TExpAlphaInSub(tev, sel_d, exp_d, 3);
}

void HSD_TExpOrder(HSD_TExp* texp, HSD_TObj* tex, GXChannelID chan)
{
    HSD_ASSERT3(HSD_TExp_804D5FC8, 837, texp);
    HSD_ASSERT3(HSD_TExp_804D5FC8, 838, HSD_TExpGetType(texp) == HSD_TE_TEV);

    texp->tev.tex = tex;
    if (chan == GX_COLOR_NULL) {
        texp->tev.chan = GX_COLOR_NULL;
        return;
    }
    texp->tev.chan = chan;
}

static int AssignColorReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevColorArg a_in[4] = { GX_CC_A0, GX_CC_A1, GX_CC_A2,
                                     GX_CC_APREV };
    static GXTevColorArg c_in[4] = { GX_CC_C0, GX_CC_C1, GX_CC_C2,
                                     GX_CC_CPREV };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->c_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg < 4) {
            return -1;
        }
        tev->c_in[idx].type = HSD_TE_IMM;
        if (cnst->comp == HSD_TE_X) {
            tev->c_in[idx].arg = a_in[cnst->reg - 4];
        } else {
            tev->c_in[idx].arg = c_in[cnst->reg - 4];
        }
        return 0;
    } else {
        if (cnst->comp == HSD_TE_X) {
            for (j = 4; j < 8; ++j) {
                if (res->reg[j].alpha == 0) {
                    res->reg[j].alpha = 1;
                    cnst->reg = j;
                    cnst->idx = 3;
                    tev->c_in[idx].type = HSD_TE_IMM;
                    tev->c_in[idx].arg = a_in[j - 4];
                    return 0;
                }
            }
        } else {
            for (j = 4; j < 8; ++j) {
                if (res->reg[j].color == 0) {
                    res->reg[j].color = 3;
                    cnst->reg = j;
                    cnst->idx = 0;
                    tev->c_in[idx].type = HSD_TE_IMM;
                    tev->c_in[idx].arg = c_in[j - 4];
                    return 0;
                }
            }
        }
    }
    return -1;
}

static int AssignAlphaReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevAlphaArg in[4] = { GX_CA_A0, GX_CA_A1, GX_CA_A2, GX_CA_APREV };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->a_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg < 4) {
            return -1;
        }
        tev->a_in[idx].type = HSD_TE_IMM;
        tev->a_in[idx].arg = in[cnst->reg - 4];
        return 0;
    } else {
        for (j = 4; j < 8; ++j) {
            if (res->reg[j].alpha == 0) {
                res->reg[j].alpha = 1;
                cnst->reg = j;
                cnst->idx = 3;
                tev->a_in[idx].type = HSD_TE_IMM;
                tev->a_in[idx].arg = in[j - 4];
                return 0;
            }
        }
    }
    return -1;
}

static int AssignColorKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevKColorSel xsel[4][4] = {
        { GX_TEV_KCSEL_K0_R, GX_TEV_KCSEL_K0_G, GX_TEV_KCSEL_K0_B,
          GX_TEV_KCSEL_K0_A },
        { GX_TEV_KCSEL_K1_R, GX_TEV_KCSEL_K1_G, GX_TEV_KCSEL_K1_B,
          GX_TEV_KCSEL_K1_A },
        { GX_TEV_KCSEL_K2_R, GX_TEV_KCSEL_K2_G, GX_TEV_KCSEL_K2_B,
          GX_TEV_KCSEL_K2_A },
        { GX_TEV_KCSEL_K3_R, GX_TEV_KCSEL_K3_G, GX_TEV_KCSEL_K3_B,
          GX_TEV_KCSEL_K3_A }
    };

    static GXTevKColorSel csel[4] = { GX_TEV_KCSEL_K0, GX_TEV_KCSEL_K1,
                                      GX_TEV_KCSEL_K2, GX_TEV_KCSEL_K3 };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->c_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg >= 4) {
            return -1;
        }
        if (cnst->comp == HSD_TE_X) {
            tev->kcsel = xsel[cnst->reg][cnst->idx];
            tev->c_in[idx].type = HSD_TE_KONST;
            tev->c_in[idx].arg = GX_CC_KONST;
        } else {
            tev->kcsel = csel[cnst->reg];
            tev->c_in[idx].type = HSD_TE_KONST;
            tev->c_in[idx].arg = GX_CC_KONST;
        }
        return 0;
    } else {
        if (cnst->comp == HSD_TE_X) {
            for (j = 1; j < 4; j++) {
                if (res->reg[j].alpha == 0) {
                    res->reg[j].alpha = 1;
                    cnst->reg = j;
                    cnst->idx = 3;
                    tev->kcsel = xsel[cnst->reg][cnst->idx];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }

            for (j = 0; j < 4; j++) {
                if (res->reg[j].color < 3) {
                    cnst->reg = j;
                    cnst->idx = res->reg[j].color++;
                    tev->kcsel = xsel[cnst->reg][cnst->idx];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }
        } else {
            for (j = 0; j < 4; j++) {
                if (res->reg[j].color == 0) {
                    res->reg[j].color = 3;
                    cnst->reg = j;
                    cnst->idx = 0;
                    tev->kcsel = csel[cnst->reg];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }
        }
    }
    return -1;
}

static int AssignAlphaKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevKAlphaSel sel[4][4] = {
        { GX_TEV_KASEL_K0_R, GX_TEV_KASEL_K0_G, GX_TEV_KASEL_K0_B,
          GX_TEV_KASEL_K0_A },
        { GX_TEV_KASEL_K1_R, GX_TEV_KASEL_K1_G, GX_TEV_KASEL_K1_B,
          GX_TEV_KASEL_K1_A },
        { GX_TEV_KASEL_K2_R, GX_TEV_KASEL_K2_G, GX_TEV_KASEL_K2_B,
          GX_TEV_KASEL_K2_A },
        { GX_TEV_KASEL_K3_R, GX_TEV_KASEL_K3_G, GX_TEV_KASEL_K3_B,
          GX_TEV_KASEL_K3_A }
    };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->a_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg >= 4) {
            return -1;
        }
        tev->kasel = sel[cnst->reg][cnst->idx];
        tev->a_in[idx].type = HSD_TE_KONST;
        tev->a_in[idx].arg = GX_CA_KONST;
        return 0;
    } else {
        for (j = 1; j < 4; j++) {
            if (res->reg[j].alpha == 0) {
                res->reg[j].alpha = 1;
                cnst->reg = j;
                cnst->idx = 3;
                tev->kasel = sel[cnst->reg][cnst->idx];
                tev->a_in[idx].type = HSD_TE_KONST;
                tev->a_in[idx].arg = GX_CA_KONST;
                return 0;
            }
        }

        for (j = 0; j < 4; j++) {
            if (res->reg[j].color < 3) {
                cnst->reg = j;
                cnst->idx = res->reg[j].color++;
                tev->kasel = sel[cnst->reg][cnst->idx];
                tev->a_in[idx].type = HSD_TE_KONST;
                tev->a_in[idx].arg = GX_CA_KONST;
                return 0;
            }
        }
    }
    return -1;
}

static inline bool IsThroughColor(HSD_TExp* texp)
{
    bool r0, r1, r2, result;
    result = false, r2 = false, r1 = false, r0 = false;
    if (texp->tev.c_op == GX_TEV_ADD && texp->tev.c_in[0].sel == HSD_TE_0) {
        r0 = true;
    }
    if (r0 && texp->tev.c_in[1].sel == HSD_TE_0) {
        r1 = true;
    }
    if (r1 && texp->tev.c_bias == 0) {
        r2 = true;
    }
    if (r2 && texp->tev.c_scale == 0) {
        result = true;
    }
    return result;
}

static inline bool IsThroughAlpha(HSD_TExp* texp)
{
    bool r0, r1, r2, result;
    result = false, r2 = false, r1 = false, r0 = false;
    if (texp->tev.a_op == GX_TEV_ADD && texp->tev.a_in[0].sel == HSD_TE_0) {
        r0 = true;
    }
    if (r0 && texp->tev.a_in[1].sel == HSD_TE_0) {
        r1 = true;
    }
    if (r1 && texp->tev.a_bias == 0) {
        r2 = true;
    }
    if (r2 && texp->tev.a_scale == 0) {
        result = true;
    }
    return result;
}

static int TExpAssignReg(HSD_TExp* texp, HSD_TExpRes* res)
{
    HSD_TETev* tev;
    int i, val;

    tev = &texp->tev;
    if (tev->c_ref > 0) {
        if (tev->kcsel != HSD_TE_UNDEF) {
            for (i = 0; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST &&
                    (val = AssignColorReg(tev, i, res)) < 0)
                {
                    HSD_ASSERT3(HSD_TExp_804D5FC8, 0x47B, val >= 0);
                    return val;
                }
            }
        } else {
            if (IsThroughColor(texp) && tev->c_in[3].type == HSD_TE_CNST) {
                if (AssignColorKonst(tev, 3, res) < 0 &&
                    (val = AssignColorReg(tev, 3, res)) < 0)
                {
                    HSD_ASSERT3(HSD_TExp_804D5FC8, 0x488, val >= 0);
                    return val;
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (tev->c_in[i].type == HSD_TE_CNST) {
                        if (AssignColorKonst(tev, i, res) < 0 &&
                            (val = AssignColorReg(tev, i, res)) < 0)
                        {
                            HSD_ASSERT3(HSD_TExp_804D5FC8, 0x49D, val >= 0);
                            return val;
                        }
                    }
                }
                for (; i < 4; i++) {
                    if (tev->c_in[i].type == HSD_TE_CNST &&
                        (val = AssignColorReg(tev, i, res)) < 0)
                    {
                        HSD_ASSERT3(HSD_TExp_804D5FC8, 0x4A6, val >= 0);
                        return val;
                    }
                }
            }
        }
    }

    if (tev->a_ref > 0) {
        if (tev->kasel != HSD_TE_UNDEF) {
            for (i = 0; i < 4; i++) {
                if (tev->a_in[i].type == HSD_TE_CNST &&
                    (val = AssignAlphaReg(tev, i, res)) < 0)
                {
                    HSD_ASSERT3(HSD_TExp_804D5FC8, 0x4B6, val >= 0);
                    return val;
                }
            }
        } else {
            if (IsThroughAlpha(texp) && tev->a_in[3].type == HSD_TE_CNST) {
                if (AssignAlphaReg(tev, 3, res) < 0 &&
                    (val = AssignAlphaKonst(tev, 3, res)) < 0)
                {
                    HSD_ASSERT3(HSD_TExp_804D5FC8, 0x4C2, val >= 0);
                    return val;
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (tev->a_in[i].type == HSD_TE_CNST) {
                        if (AssignAlphaKonst(tev, i, res) < 0 &&
                            (val = AssignAlphaReg(tev, i, res)) < 0)
                        {
                            HSD_ASSERT3(HSD_TExp_804D5FC8, 0x4CF, val >= 0);
                            return val;
                        }
                    }
                }
                for (; i < 4; i++) {
                    if (tev->a_in[i].type == HSD_TE_CNST &&
                        (val = AssignAlphaReg(tev, i, res)) < 0)
                    {
                        HSD_ASSERT3(HSD_TExp_804D5FC8, 0x4D8, val >= 0);
                        return val;
                    }
                }
            }
        }
    }
    return 0;
}

static void TExp2TevDesc(HSD_TExp* texp, HSD_TExpTevDesc* desc,
                         int* init_cprev, int* init_aprev)
{
    static GXTevRegID dst[4] = { GX_TEVREG0, GX_TEVREG1, GX_TEVREG2,
                                 GX_TEVPREV };

    HSD_TETev* tev;
    HSD_TevDesc* tevdesc;

    HSD_ASSERT3(HSD_TExp_804D5FC8, 1296, texp);
    HSD_ASSERT3(HSD_TExp_804D5FC8, 1297, desc);
    HSD_ASSERT3(HSD_TExp_804D5FC8, 1298, HSD_TExpGetType(texp) == HSD_TE_TEV);

    tev = &texp->tev;
    tevdesc = &desc->desc;

    tevdesc->next = NULL;
    tevdesc->flags = 1;
    desc->tobj = tev->tex;
    if (tev->tex == NULL) {
        tevdesc->coord = HSD_TE_UNDEF;
        tevdesc->map = HSD_TE_UNDEF;
    }
    tevdesc->color = tev->chan == HSD_TE_UNDEF ? HSD_TE_UNDEF : tev->chan;
    tevdesc->u.tevconf.ras_swap =
        tev->ras_swap == HSD_TE_UNDEF ? 0 : tev->ras_swap;
    tevdesc->u.tevconf.tex_swap =
        tev->tex_swap == HSD_TE_UNDEF ? 0 : tev->tex_swap;
    tevdesc->u.tevconf.kcsel = tev->kcsel == HSD_TE_UNDEF ? 0 : tev->kcsel;
    tevdesc->u.tevconf.kasel = tev->kasel == HSD_TE_UNDEF ? 0 : tev->kasel;

    if ((tev->c_op == HSD_TE_UNDEF) ||
        (tev->c_ref == 0 && tev->a_op != 8 && tev->a_op != 9 &&
         tev->a_op != 0xA && tev->a_op != 0xB && tev->a_op != 0xC &&
         tev->a_op != 0xD))
    {
        tevdesc->u.tevconf.clr_op = GX_TEV_ADD;
        tevdesc->u.tevconf.clr_a = GX_CC_ZERO;
        tevdesc->u.tevconf.clr_b = GX_CC_ZERO;
        tevdesc->u.tevconf.clr_c = GX_CC_ZERO;
        if (*init_cprev != 0) {
            *init_cprev = 0;
            tevdesc->u.tevconf.clr_d = GX_CC_ZERO;
        } else {
            tevdesc->u.tevconf.clr_d = GX_CC_CPREV;
        }
        tevdesc->u.tevconf.clr_scale = 0;
        tevdesc->u.tevconf.clr_bias = 0;
        tevdesc->u.tevconf.clr_clamp = 0;
        tevdesc->u.tevconf.clr_out_reg = 0;
    } else {
        tevdesc->u.tevconf.clr_op = tev->c_op;
        tevdesc->u.tevconf.clr_a =
            tev->c_in[0].arg == HSD_TE_UNDEF ? GX_CC_ZERO : tev->c_in[0].arg;
        tevdesc->u.tevconf.clr_b =
            tev->c_in[1].arg == HSD_TE_UNDEF ? GX_CC_ZERO : tev->c_in[1].arg;
        tevdesc->u.tevconf.clr_c =
            tev->c_in[2].arg == HSD_TE_UNDEF ? GX_CC_ZERO : tev->c_in[2].arg;
        tevdesc->u.tevconf.clr_d =
            tev->c_in[3].arg == HSD_TE_UNDEF ? GX_CC_ZERO : tev->c_in[3].arg;
        tevdesc->u.tevconf.clr_scale =
            tev->c_scale == HSD_TE_UNDEF ? 0 : tev->c_scale;
        tevdesc->u.tevconf.clr_bias =
            tev->c_bias == HSD_TE_UNDEF ? 0 : tev->c_bias;
        tevdesc->u.tevconf.clr_clamp = tev->c_clamp != 0 ? GX_TRUE : GX_FALSE;

        HSD_ASSERT3(HSD_TExp_804D5FC8, 1361, tev->c_dst != HSD_TE_UNDEF);
        tevdesc->u.tevconf.clr_out_reg = dst[tev->c_dst];
        if (tevdesc->u.tevconf.clr_out_reg == 0) {
            *init_cprev = 0;
        }
    }

    if (tev->a_op == HSD_TE_UNDEF || tev->a_ref == 0) {
        tevdesc->u.tevconf.alpha_op = GX_TEV_ADD;
        tevdesc->u.tevconf.alpha_a = GX_CA_ZERO;
        tevdesc->u.tevconf.alpha_b = GX_CA_ZERO;
        tevdesc->u.tevconf.alpha_c = GX_CA_ZERO;
        if (*init_aprev != 0) {
            *init_aprev = 0;
            tevdesc->u.tevconf.alpha_d = GX_CA_ZERO;
        } else {
            tevdesc->u.tevconf.alpha_d = GX_CA_APREV;
        }
        tevdesc->u.tevconf.alpha_scale = 0;
        tevdesc->u.tevconf.alpha_bias = 0;
        tevdesc->u.tevconf.alpha_clamp = 0;
        tevdesc->u.tevconf.alpha_out_reg = 0;
    } else {
        tevdesc->u.tevconf.alpha_op = tev->a_op;
        tevdesc->u.tevconf.alpha_a =
            tev->a_in[0].arg == HSD_TE_UNDEF ? GX_CA_ZERO : tev->a_in[0].arg;
        tevdesc->u.tevconf.alpha_b =
            tev->a_in[1].arg == HSD_TE_UNDEF ? GX_CA_ZERO : tev->a_in[1].arg;
        tevdesc->u.tevconf.alpha_c =
            tev->a_in[2].arg == HSD_TE_UNDEF ? GX_CA_ZERO : tev->a_in[2].arg;
        tevdesc->u.tevconf.alpha_d =
            tev->a_in[3].arg == HSD_TE_UNDEF ? GX_CA_ZERO : tev->a_in[3].arg;
        tevdesc->u.tevconf.alpha_scale =
            tev->a_scale == HSD_TE_UNDEF ? 0 : tev->a_scale;
        tevdesc->u.tevconf.alpha_bias =
            tev->a_bias == HSD_TE_UNDEF ? 0 : tev->a_bias;
        tevdesc->u.tevconf.alpha_clamp =
            tev->a_clamp != 0 ? GX_TRUE : GX_FALSE;

        HSD_ASSERT3(HSD_TExp_804D5FC8, 1397, tev->a_dst != HSD_TE_UNDEF);
        tevdesc->u.tevconf.alpha_out_reg = dst[tev->a_dst];
        if (tevdesc->u.tevconf.alpha_out_reg == 0) {
            *init_aprev = 0;
        }
    }
    tevdesc->u.tevconf.mode = GX_TC_LINEAR;
}

static GXTevRegID id[7] = { GX_TEVPREV, GX_TEVREG0, GX_TEVREG1, GX_TEVREG2,
                            GX_TEVREG0, GX_TEVREG1, GX_TEVREG2 };
static char list_type[27] = "clist->type == HSD_TE_CNST";
const float HSD_TExp_804DE7E0 = 255.0f;
const double HSD_TExp_804DE7D8 = 255.0;

asm void HSD_TExpSetReg(HSD_TExp* texp)
{ // clang-format off
#ifdef MUST_MATCH
    nofralloc
/* 80384F28 00381B08  7C 08 02 A6 */	mflr r0
/* 80384F2C 00381B0C  3C 80 80 40 */	lis r4, HSD_TExp_80407738@ha
/* 80384F30 00381B10  90 01 00 04 */	stw r0, 4(r1)
/* 80384F34 00381B14  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80384F38 00381B18  DB E1 00 78 */	stfd f31, 0x78(r1)
/* 80384F3C 00381B1C  DB C1 00 70 */	stfd f30, 0x70(r1)
/* 80384F40 00381B20  BF 21 00 54 */	stmw r25, 0x54(r1)
/* 80384F44 00381B24  3B A3 00 00 */	addi r29, r3, 0
/* 80384F48 00381B28  3B 84 77 38 */	addi r28, r4, HSD_TExp_80407738@l
/* 80384F4C 00381B2C  3B E1 00 18 */	addi r31, r1, 0x18
/* 80384F50 00381B30  3B C0 00 00 */	li r30, 0
/* 80384F54 00381B34  CB E2 EE 00 */	lfd f31, HSD_TExp_804DE7E0(r2)
/* 80384F58 00381B38  C3 C2 ED F8 */	lfs f30, HSD_TExp_804DE7D8(r2)
/* 80384F5C 00381B3C  48 00 04 10 */	b L_8038536C
L_80384F60:
/* 80384F60 00381B40  80 1D 00 00 */	lwz r0, 0(r29)
/* 80384F64 00381B44  2C 00 00 04 */	cmpwi r0, 4
/* 80384F68 00381B48  41 82 00 14 */	beq L_80384F7C
/* 80384F6C 00381B4C  38 BC 03 4C */	addi r5, r28, 0x34c
/* 80384F70 00381B50  38 6D A9 28 */	addi r3, r13, HSD_TExp_804D5FC8
/* 80384F74 00381B54  38 80 05 91 */	li r4, 0x591
/* 80384F78 00381B58  48 00 32 A9 */	bl __assert
L_80384F7C:
/* 80384F7C 00381B5C  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 80384F80 00381B60  28 00 00 08 */	cmplwi r0, 8
/* 80384F84 00381B64  40 80 03 E4 */	bge L_80385368
/* 80384F88 00381B68  80 7D 00 0C */	lwz r3, 0xc(r29)
/* 80384F8C 00381B6C  38 80 00 01 */	li r4, 1
/* 80384F90 00381B70  7C 84 00 30 */	slw r4, r4, r0
/* 80384F94 00381B74  2C 03 00 01 */	cmpwi r3, 1
/* 80384F98 00381B78  7F DE 23 78 */	or r30, r30, r4
/* 80384F9C 00381B7C  40 82 02 08 */	bne L_803851A4
/* 80384FA0 00381B80  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 80384FA4 00381B84  2C 03 00 01 */	cmpwi r3, 1
/* 80384FA8 00381B88  41 82 00 B8 */	beq L_80385060
/* 80384FAC 00381B8C  40 80 00 10 */	bge L_80384FBC
/* 80384FB0 00381B90  2C 03 00 00 */	cmpwi r3, 0
/* 80384FB4 00381B94  40 80 00 14 */	bge L_80384FC8
/* 80384FB8 00381B98  48 00 00 A8 */	b L_80385060
L_80384FBC:
/* 80384FBC 00381B9C  2C 03 00 03 */	cmpwi r3, 3
/* 80384FC0 00381BA0  40 80 00 A0 */	bge L_80385060
/* 80384FC4 00381BA4  48 00 00 30 */	b L_80384FF4
L_80384FC8:
/* 80384FC8 00381BA8  80 7D 00 08 */	lwz r3, 8(r29)
/* 80384FCC 00381BAC  54 00 10 3A */	slwi r0, r0, 2
/* 80384FD0 00381BB0  38 81 00 18 */	addi r4, r1, 0x18
/* 80384FD4 00381BB4  80 63 00 00 */	lwz r3, 0(r3)
/* 80384FD8 00381BB8  7C 84 02 14 */	add r4, r4, r0
/* 80384FDC 00381BBC  90 61 00 14 */	stw r3, 0x14(r1)
/* 80384FE0 00381BC0  88 04 00 03 */	lbz r0, 3(r4)
/* 80384FE4 00381BC4  98 01 00 17 */	stb r0, 0x17(r1)
/* 80384FE8 00381BC8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80384FEC 00381BCC  90 04 00 00 */	stw r0, 0(r4)
/* 80384FF0 00381BD0  48 00 03 78 */	b L_80385368
L_80384FF4:
/* 80384FF4 00381BD4  80 9D 00 08 */	lwz r4, 8(r29)
/* 80384FF8 00381BD8  80 64 00 00 */	lwz r3, 0(r4)
/* 80384FFC 00381BDC  28 03 01 00 */	cmplwi r3, 0x100
/* 80385000 00381BE0  40 80 00 08 */	bge L_80385008
/* 80385004 00381BE4  48 00 00 08 */	b L_8038500C
L_80385008:
/* 80385008 00381BE8  38 60 00 FF */	li r3, 0xff
L_8038500C:
/* 8038500C 00381BEC  54 00 10 3A */	slwi r0, r0, 2
/* 80385010 00381BF0  7C 7F 01 AE */	stbx r3, r31, r0
/* 80385014 00381BF4  80 A4 00 04 */	lwz r5, 4(r4)
/* 80385018 00381BF8  28 05 01 00 */	cmplwi r5, 0x100
/* 8038501C 00381BFC  40 80 00 08 */	bge L_80385024
/* 80385020 00381C00  48 00 00 08 */	b L_80385028
L_80385024:
/* 80385024 00381C04  38 A0 00 FF */	li r5, 0xff
L_80385028:
/* 80385028 00381C08  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 8038502C 00381C0C  54 03 10 3A */	slwi r3, r0, 2
/* 80385030 00381C10  38 03 00 01 */	addi r0, r3, 1
/* 80385034 00381C14  7C BF 01 AE */	stbx r5, r31, r0
/* 80385038 00381C18  80 84 00 08 */	lwz r4, 8(r4)
/* 8038503C 00381C1C  28 04 01 00 */	cmplwi r4, 0x100
/* 80385040 00381C20  40 80 00 08 */	bge L_80385048
/* 80385044 00381C24  48 00 00 08 */	b L_8038504C
L_80385048:
/* 80385048 00381C28  38 80 00 FF */	li r4, 0xff
L_8038504C:
/* 8038504C 00381C2C  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 80385050 00381C30  54 03 10 3A */	slwi r3, r0, 2
/* 80385054 00381C34  38 03 00 02 */	addi r0, r3, 2
/* 80385058 00381C38  7C 9F 01 AE */	stbx r4, r31, r0
/* 8038505C 00381C3C  48 00 03 0C */	b L_80385368
L_80385060:
/* 80385060 00381C40  2C 03 00 02 */	cmpwi r3, 2
/* 80385064 00381C44  41 82 00 78 */	beq L_803850DC
/* 80385068 00381C48  40 80 00 10 */	bge L_80385078
/* 8038506C 00381C4C  2C 03 00 01 */	cmpwi r3, 1
/* 80385070 00381C50  40 80 00 14 */	bge L_80385084
/* 80385074 00381C54  48 00 00 68 */	b L_803850DC
L_80385078:
/* 80385078 00381C58  2C 03 00 04 */	cmpwi r3, 4
/* 8038507C 00381C5C  40 80 00 60 */	bge L_803850DC
/* 80385080 00381C60  48 00 00 18 */	b L_80385098
L_80385084:
/* 80385084 00381C64  80 BD 00 08 */	lwz r5, 8(r29)
/* 80385088 00381C68  A0 65 00 00 */	lhz r3, 0(r5)
/* 8038508C 00381C6C  A0 85 00 02 */	lhz r4, 2(r5)
/* 80385090 00381C70  A0 A5 00 04 */	lhz r5, 4(r5)
/* 80385094 00381C74  48 00 00 88 */	b L_8038511C
L_80385098:
/* 80385098 00381C78  80 7D 00 08 */	lwz r3, 8(r29)
/* 8038509C 00381C7C  C0 43 00 00 */	lfs f2, 0(r3)
/* 803850A0 00381C80  C0 23 00 04 */	lfs f1, 4(r3)
/* 803850A4 00381C84  C0 03 00 08 */	lfs f0, 8(r3)
/* 803850A8 00381C88  EC 5E 00 B2 */	fmuls f2, f30, f2
/* 803850AC 00381C8C  EC 3E 00 72 */	fmuls f1, f30, f1
/* 803850B0 00381C90  EC 1E 00 32 */	fmuls f0, f30, f0
/* 803850B4 00381C94  FC 40 10 1E */	fctiwz f2, f2
/* 803850B8 00381C98  FC 20 08 1E */	fctiwz f1, f1
/* 803850BC 00381C9C  FC 00 00 1E */	fctiwz f0, f0
/* 803850C0 00381CA0  D8 41 00 48 */	stfd f2, 0x48(r1)
/* 803850C4 00381CA4  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 803850C8 00381CA8  80 61 00 4C */	lwz r3, 0x4c(r1)
/* 803850CC 00381CAC  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 803850D0 00381CB0  80 81 00 44 */	lwz r4, 0x44(r1)
/* 803850D4 00381CB4  80 A1 00 3C */	lwz r5, 0x3c(r1)
/* 803850D8 00381CB8  48 00 00 44 */	b L_8038511C
L_803850DC:
/* 803850DC 00381CBC  80 7D 00 08 */	lwz r3, 8(r29)
/* 803850E0 00381CC0  C8 43 00 00 */	lfd f2, 0(r3)
/* 803850E4 00381CC4  C8 23 00 08 */	lfd f1, 8(r3)
/* 803850E8 00381CC8  C8 03 00 10 */	lfd f0, 0x10(r3)
/* 803850EC 00381CCC  FC 5F 00 B2 */	fmul f2, f31, f2
/* 803850F0 00381CD0  FC 3F 00 72 */	fmul f1, f31, f1
/* 803850F4 00381CD4  FC 1F 00 32 */	fmul f0, f31, f0
/* 803850F8 00381CD8  FC 40 10 1E */	fctiwz f2, f2
/* 803850FC 00381CDC  FC 20 08 1E */	fctiwz f1, f1
/* 80385100 00381CE0  FC 00 00 1E */	fctiwz f0, f0
/* 80385104 00381CE4  D8 41 00 38 */	stfd f2, 0x38(r1)
/* 80385108 00381CE8  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 8038510C 00381CEC  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 80385110 00381CF0  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 80385114 00381CF4  80 81 00 44 */	lwz r4, 0x44(r1)
/* 80385118 00381CF8  80 A1 00 4C */	lwz r5, 0x4c(r1)
L_8038511C:
/* 8038511C 00381CFC  2C 03 00 FF */	cmpwi r3, 0xff
/* 80385120 00381D00  40 81 00 0C */	ble L_8038512C
/* 80385124 00381D04  38 60 00 FF */	li r3, 0xff
/* 80385128 00381D08  48 00 00 10 */	b L_80385138
L_8038512C:
/* 8038512C 00381D0C  2C 03 00 00 */	cmpwi r3, 0
/* 80385130 00381D10  40 80 00 08 */	bge L_80385138
/* 80385134 00381D14  38 60 00 00 */	li r3, 0
L_80385138:
/* 80385138 00381D18  54 00 10 3A */	slwi r0, r0, 2
/* 8038513C 00381D1C  2C 04 00 FF */	cmpwi r4, 0xff
/* 80385140 00381D20  7C 7F 01 AE */	stbx r3, r31, r0
/* 80385144 00381D24  40 81 00 0C */	ble L_80385150
/* 80385148 00381D28  38 80 00 FF */	li r4, 0xff
/* 8038514C 00381D2C  48 00 00 10 */	b L_8038515C
L_80385150:
/* 80385150 00381D30  2C 04 00 00 */	cmpwi r4, 0
/* 80385154 00381D34  40 80 00 08 */	bge L_8038515C
/* 80385158 00381D38  38 80 00 00 */	li r4, 0
L_8038515C:
/* 8038515C 00381D3C  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 80385160 00381D40  2C 05 00 FF */	cmpwi r5, 0xff
/* 80385164 00381D44  54 03 10 3A */	slwi r3, r0, 2
/* 80385168 00381D48  38 03 00 01 */	addi r0, r3, 1
/* 8038516C 00381D4C  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385170 00381D50  40 81 00 0C */	ble L_8038517C
/* 80385174 00381D54  38 80 00 FF */	li r4, 0xff
/* 80385178 00381D58  48 00 00 18 */	b L_80385190
L_8038517C:
/* 8038517C 00381D5C  2C 05 00 00 */	cmpwi r5, 0
/* 80385180 00381D60  40 80 00 0C */	bge L_8038518C
/* 80385184 00381D64  38 80 00 00 */	li r4, 0
/* 80385188 00381D68  48 00 00 08 */	b L_80385190
L_8038518C:
/* 8038518C 00381D6C  7C A4 2B 78 */	mr r4, r5
L_80385190:
/* 80385190 00381D70  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 80385194 00381D74  54 03 10 3A */	slwi r3, r0, 2
/* 80385198 00381D78  38 03 00 02 */	addi r0, r3, 2
/* 8038519C 00381D7C  7C 9F 01 AE */	stbx r4, r31, r0
/* 803851A0 00381D80  48 00 01 C8 */	b L_80385368
L_803851A4:
/* 803851A4 00381D84  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 803851A8 00381D88  2C 03 00 02 */	cmpwi r3, 2
/* 803851AC 00381D8C  41 82 00 5C */	beq L_80385208
/* 803851B0 00381D90  40 80 00 14 */	bge L_803851C4
/* 803851B4 00381D94  2C 03 00 00 */	cmpwi r3, 0
/* 803851B8 00381D98  41 82 00 18 */	beq L_803851D0
/* 803851BC 00381D9C  40 80 00 20 */	bge L_803851DC
/* 803851C0 00381DA0  48 00 00 B8 */	b L_80385278
L_803851C4:
/* 803851C4 00381DA4  2C 03 00 04 */	cmpwi r3, 4
/* 803851C8 00381DA8  40 80 00 B0 */	bge L_80385278
/* 803851CC 00381DAC  48 00 00 68 */	b L_80385234
L_803851D0:
/* 803851D0 00381DB0  80 7D 00 08 */	lwz r3, 8(r29)
/* 803851D4 00381DB4  88 83 00 00 */	lbz r4, 0(r3)
/* 803851D8 00381DB8  48 00 00 E0 */	b L_803852B8
L_803851DC:
/* 803851DC 00381DBC  80 7D 00 08 */	lwz r3, 8(r29)
/* 803851E0 00381DC0  A0 63 00 00 */	lhz r3, 0(r3)
/* 803851E4 00381DC4  2C 03 00 FF */	cmpwi r3, 0xff
/* 803851E8 00381DC8  40 81 00 0C */	ble L_803851F4
/* 803851EC 00381DCC  38 60 00 FF */	li r3, 0xff
/* 803851F0 00381DD0  48 00 00 10 */	b L_80385200
L_803851F4:
/* 803851F4 00381DD4  2C 03 00 00 */	cmpwi r3, 0
/* 803851F8 00381DD8  40 80 00 08 */	bge L_80385200
/* 803851FC 00381DDC  38 60 00 00 */	li r3, 0
L_80385200:
/* 80385200 00381DE0  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 80385204 00381DE4  48 00 00 B4 */	b L_803852B8
L_80385208:
/* 80385208 00381DE8  80 7D 00 08 */	lwz r3, 8(r29)
/* 8038520C 00381DEC  80 63 00 00 */	lwz r3, 0(r3)
/* 80385210 00381DF0  2C 03 00 FF */	cmpwi r3, 0xff
/* 80385214 00381DF4  40 81 00 0C */	ble L_80385220
/* 80385218 00381DF8  38 60 00 FF */	li r3, 0xff
/* 8038521C 00381DFC  48 00 00 10 */	b L_8038522C
L_80385220:
/* 80385220 00381E00  2C 03 00 00 */	cmpwi r3, 0
/* 80385224 00381E04  40 80 00 08 */	bge L_8038522C
/* 80385228 00381E08  38 60 00 00 */	li r3, 0
L_8038522C:
/* 8038522C 00381E0C  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 80385230 00381E10  48 00 00 88 */	b L_803852B8
L_80385234:
/* 80385234 00381E14  80 7D 00 08 */	lwz r3, 8(r29)
/* 80385238 00381E18  C0 03 00 00 */	lfs f0, 0(r3)
/* 8038523C 00381E1C  EC 1E 00 32 */	fmuls f0, f30, f0
/* 80385240 00381E20  FC 00 00 1E */	fctiwz f0, f0
/* 80385244 00381E24  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 80385248 00381E28  80 61 00 44 */	lwz r3, 0x44(r1)
/* 8038524C 00381E2C  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80385250 00381E30  2C 03 00 FF */	cmpwi r3, 0xff
/* 80385254 00381E34  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 80385258 00381E38  40 81 00 0C */	ble L_80385264
/* 8038525C 00381E3C  38 60 00 FF */	li r3, 0xff
/* 80385260 00381E40  48 00 00 10 */	b L_80385270
L_80385264:
/* 80385264 00381E44  2C 03 00 00 */	cmpwi r3, 0
/* 80385268 00381E48  40 80 00 08 */	bge L_80385270
/* 8038526C 00381E4C  38 60 00 00 */	li r3, 0
L_80385270:
/* 80385270 00381E50  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 80385274 00381E54  48 00 00 44 */	b L_803852B8
L_80385278:
/* 80385278 00381E58  80 7D 00 08 */	lwz r3, 8(r29)
/* 8038527C 00381E5C  C8 03 00 00 */	lfd f0, 0(r3)
/* 80385280 00381E60  FC 1F 00 32 */	fmul f0, f31, f0
/* 80385284 00381E64  FC 00 00 1E */	fctiwz f0, f0
/* 80385288 00381E68  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 8038528C 00381E6C  80 61 00 44 */	lwz r3, 0x44(r1)
/* 80385290 00381E70  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80385294 00381E74  2C 03 00 FF */	cmpwi r3, 0xff
/* 80385298 00381E78  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 8038529C 00381E7C  40 81 00 0C */	ble L_803852A8
/* 803852A0 00381E80  38 60 00 FF */	li r3, 0xff
/* 803852A4 00381E84  48 00 00 10 */	b L_803852B4
L_803852A8:
/* 803852A8 00381E88  2C 03 00 00 */	cmpwi r3, 0
/* 803852AC 00381E8C  40 80 00 08 */	bge L_803852B4
/* 803852B0 00381E90  38 60 00 00 */	li r3, 0
L_803852B4:
/* 803852B4 00381E94  54 64 06 3E */	clrlwi r4, r3, 0x18
L_803852B8:
/* 803852B8 00381E98  28 00 00 04 */	cmplwi r0, 4
/* 803852BC 00381E9C  40 80 00 68 */	bge L_80385324
/* 803852C0 00381EA0  88 7D 00 15 */	lbz r3, 0x15(r29)
/* 803852C4 00381EA4  2C 03 00 01 */	cmpwi r3, 1
/* 803852C8 00381EA8  41 82 00 2C */	beq L_803852F4
/* 803852CC 00381EAC  40 80 00 10 */	bge L_803852DC
/* 803852D0 00381EB0  2C 03 00 00 */	cmpwi r3, 0
/* 803852D4 00381EB4  40 80 00 14 */	bge L_803852E8
/* 803852D8 00381EB8  48 00 00 3C */	b L_80385314
L_803852DC:
/* 803852DC 00381EBC  2C 03 00 03 */	cmpwi r3, 3
/* 803852E0 00381EC0  40 80 00 34 */	bge L_80385314
/* 803852E4 00381EC4  48 00 00 20 */	b L_80385304
L_803852E8:
/* 803852E8 00381EC8  54 00 10 3A */	slwi r0, r0, 2
/* 803852EC 00381ECC  7C 9F 01 AE */	stbx r4, r31, r0
/* 803852F0 00381ED0  48 00 00 78 */	b L_80385368
L_803852F4:
/* 803852F4 00381ED4  54 03 10 3A */	slwi r3, r0, 2
/* 803852F8 00381ED8  38 03 00 01 */	addi r0, r3, 1
/* 803852FC 00381EDC  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385300 00381EE0  48 00 00 68 */	b L_80385368
L_80385304:
/* 80385304 00381EE4  54 03 10 3A */	slwi r3, r0, 2
/* 80385308 00381EE8  38 03 00 02 */	addi r0, r3, 2
/* 8038530C 00381EEC  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385310 00381EF0  48 00 00 58 */	b L_80385368
L_80385314:
/* 80385314 00381EF4  54 03 10 3A */	slwi r3, r0, 2
/* 80385318 00381EF8  38 03 00 03 */	addi r0, r3, 3
/* 8038531C 00381EFC  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385320 00381F00  48 00 00 48 */	b L_80385368
L_80385324:
/* 80385324 00381F04  88 7D 00 15 */	lbz r3, 0x15(r29)
/* 80385328 00381F08  28 03 00 03 */	cmplwi r3, 3
/* 8038532C 00381F0C  40 82 00 14 */	bne L_80385340
/* 80385330 00381F10  54 03 10 3A */	slwi r3, r0, 2
/* 80385334 00381F14  38 03 00 03 */	addi r0, r3, 3
/* 80385338 00381F18  7C 9F 01 AE */	stbx r4, r31, r0
/* 8038533C 00381F1C  48 00 00 2C */	b L_80385368
L_80385340:
/* 80385340 00381F20  54 00 10 3A */	slwi r0, r0, 2
/* 80385344 00381F24  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385348 00381F28  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 8038534C 00381F2C  54 03 10 3A */	slwi r3, r0, 2
/* 80385350 00381F30  38 03 00 01 */	addi r0, r3, 1
/* 80385354 00381F34  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385358 00381F38  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 8038535C 00381F3C  54 03 10 3A */	slwi r3, r0, 2
/* 80385360 00381F40  38 03 00 02 */	addi r0, r3, 2
/* 80385364 00381F44  7C 9F 01 AE */	stbx r4, r31, r0
L_80385368:
/* 80385368 00381F48  83 BD 00 04 */	lwz r29, 4(r29)
L_8038536C:
/* 8038536C 00381F4C  28 1D 00 00 */	cmplwi r29, 0
/* 80385370 00381F50  40 82 FB F0 */	bne L_80384F60
/* 80385374 00381F54  28 1E 00 00 */	cmplwi r30, 0
/* 80385378 00381F58  41 82 00 B4 */	beq L_8038542C
/* 8038537C 00381F5C  4B FB 79 A1 */	bl GXPixModeSync
/* 80385380 00381F60  3B 20 00 00 */	li r25, 0
/* 80385384 00381F64  57 20 10 3A */	slwi r0, r25, 2
/* 80385388 00381F68  7F 5C 02 14 */	add r26, r28, r0
/* 8038538C 00381F6C  3B 61 00 18 */	addi r27, r1, 0x18
/* 80385390 00381F70  3B E1 00 10 */	addi r31, r1, 0x10
/* 80385394 00381F74  3B A0 00 01 */	li r29, 1
/* 80385398 00381F78  3B 5A 03 30 */	addi r26, r26, 0x330
L_8038539C:
/* 8038539C 00381F7C  7F A0 C8 30 */	slw r0, r29, r25
/* 803853A0 00381F80  7F C0 00 39 */	and. r0, r30, r0
/* 803853A4 00381F84  41 82 00 18 */	beq L_803853BC
/* 803853A8 00381F88  80 1B 00 00 */	lwz r0, 0(r27)
/* 803853AC 00381F8C  7F E4 FB 78 */	mr r4, r31
/* 803853B0 00381F90  90 01 00 10 */	stw r0, 0x10(r1)
/* 803853B4 00381F94  80 7A 00 00 */	lwz r3, 0(r26)
/* 803853B8 00381F98  4B FB AF 1D */	bl GXSetTevKColor
L_803853BC:
/* 803853BC 00381F9C  3B 39 00 01 */	addi r25, r25, 1
/* 803853C0 00381FA0  2C 19 00 04 */	cmpwi r25, 4
/* 803853C4 00381FA4  3B 7B 00 04 */	addi r27, r27, 4
/* 803853C8 00381FA8  3B 5A 00 04 */	addi r26, r26, 4
/* 803853CC 00381FAC  41 80 FF D0 */	blt L_8038539C
/* 803853D0 00381FB0  3B E0 00 04 */	li r31, 4
/* 803853D4 00381FB4  57 E0 10 3A */	slwi r0, r31, 2
/* 803853D8 00381FB8  7F 7C 02 14 */	add r27, r28, r0
/* 803853DC 00381FBC  3B 41 00 28 */	addi r26, r1, 0x28
/* 803853E0 00381FC0  3B A1 00 0C */	addi r29, r1, 0xc
/* 803853E4 00381FC4  3B 80 00 01 */	li r28, 1
/* 803853E8 00381FC8  3B 7B 03 40 */	addi r27, r27, 0x340
L_803853EC:
/* 803853EC 00381FCC  7F 80 F8 30 */	slw r0, r28, r31
/* 803853F0 00381FD0  7F C0 00 39 */	and. r0, r30, r0
/* 803853F4 00381FD4  41 82 00 18 */	beq L_8038540C
/* 803853F8 00381FD8  80 1A 00 00 */	lwz r0, 0(r26)
/* 803853FC 00381FDC  7F A4 EB 78 */	mr r4, r29
/* 80385400 00381FE0  90 01 00 0C */	stw r0, 0xc(r1)
/* 80385404 00381FE4  80 7B FF F0 */	lwz r3, -0x10(r27)
/* 80385408 00381FE8  4B FB AD E5 */	bl GXSetTevColor
L_8038540C:
/* 8038540C 00381FEC  3B FF 00 01 */	addi r31, r31, 1
/* 80385410 00381FF0  2C 1F 00 07 */	cmpwi r31, 7
/* 80385414 00381FF4  3B 5A 00 04 */	addi r26, r26, 4
/* 80385418 00381FF8  3B 7B 00 04 */	addi r27, r27, 4
/* 8038541C 00381FFC  41 80 FF D0 */	blt L_803853EC
/* 80385420 00382000  38 60 00 10 */	li r3, 0x10
/* 80385424 00382004  4B FD CB A1 */	bl HSD_StateInvalidate
/* 80385428 00382008  4B FB 78 F5 */	bl GXPixModeSync
L_8038542C:
/* 8038542C 0038200C  BB 21 00 54 */	lmw r25, 0x54(r1)
/* 80385430 00382010  80 01 00 84 */	lwz r0, 0x84(r1)
/* 80385434 00382014  CB E1 00 78 */	lfd f31, 0x78(r1)
/* 80385438 00382018  CB C1 00 70 */	lfd f30, 0x70(r1)
/* 8038543C 0038201C  38 21 00 80 */	addi r1, r1, 0x80
/* 80385440 00382020  7C 08 03 A6 */	mtlr r0
/* 80385444 00382024  4E 80 00 20 */	blr
}
#pragma peephole on
#endif

void HSD_TExpSetupTev(HSD_TExpTevDesc* tevdesc, HSD_TExp* texp)
{
    HSD_TExpSetReg(texp);
    for (; tevdesc != NULL; tevdesc = (HSD_TExpTevDesc*) tevdesc->desc.next) {
        if (tevdesc->tobj != NULL) {
            tevdesc->desc.map = tevdesc->tobj->id;
            tevdesc->desc.coord = tevdesc->tobj->coord;
        }
        HSD_StateAssignTev();
        HSD_SetupTevStage(&tevdesc->desc);
    }
}

int HSD_TExpCompile(HSD_TExp* texp, HSD_TExpTevDesc** tevdesc,
                    HSD_TExp** texp_list)
{
    int num, i, val;
    HSD_TExpRes res;
    HSD_TExp* order[32];
    HSD_TExpDag list[32];
    int init_cprev = 1;
    int init_aprev = 1;

    HSD_ASSERT3(HSD_TExp_804D5FC8, 1627, tevdesc);
    HSD_ASSERT4(HSD_TExp_804D5FC8, 1628, HSD_TExp_80407738, texp_list);

    memset(&res, 0, sizeof(HSD_TExpRes));

    HSD_TExpRef(texp, HSD_TE_RGB);
    HSD_TExpRef(texp, HSD_TE_A);
    HSD_TExpSimplify(texp);

    num = HSD_TExpMakeDag(texp, list);
    HSD_TExpSchedule(num, list, order, &res);
    for (i = 0; i < num; ++i) {
        val = TExpAssignReg(order[i], &res);
        HSD_ASSERT3(HSD_TExp_804D5FC8, 1660, val >= 0);
    }

    for (i = num - 1; i >= 0; --i) {
        HSD_TExpSimplify2(order[i]);
    }

    num = HSD_TExpMakeDag(texp, list);
    HSD_TExpSchedule(num, list, order, &res);
    *tevdesc = NULL;
    for (i = 0; i < num; ++i) {
        HSD_TExpTevDesc* tdesc = hsdAllocMemPiece(sizeof(HSD_TExpTevDesc));
        tdesc->desc.stage = HSD_Index2TevStage(i);
        TExp2TevDesc(order[(num - i) - 1], tdesc, &init_cprev, &init_aprev);
        tdesc->desc.next = &(*tevdesc)->desc;
        *tevdesc = tdesc;
    }

    *texp_list = HSD_TExpFreeList(*texp_list, HSD_TE_TEV, 1);
    *texp_list = HSD_TExpFreeList(*texp_list, HSD_TE_CNST, 0);
    return num;
}

void HSD_TExpFreeTevDesc(HSD_TExpTevDesc* tdesc)
{
    HSD_TExpTevDesc* next = tdesc;
    while (next != NULL) {
        HSD_TExpTevDesc* temp = (HSD_TExpTevDesc*) next->desc.next;
        hsdFreeMemPiece(next, sizeof(HSD_TExpTevDesc));
        next = temp;
    }
}
