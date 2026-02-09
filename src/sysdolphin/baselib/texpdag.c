#include "texpdag.h"

#include "tobj.h"

int assign_reg(int num, u32* unused, HSD_TExpDag* list, int* order)
{
    u8 sp20[4] = { 0 };
    u8 sp1C[4] = { 0 };
    HSD_TETev* var_r29;
    HSD_TExpDag* temp_r27;
    int idx;
    int i;
    int var_r24 = 4;
    int var_r23 = 4;
    int temp_r5;
    PAD_STACK(4);

    for (idx = num - 1; idx >= 0; idx--) {
        temp_r27 = &list[order[idx]];
        var_r29 = temp_r27->tev;

        for (i = 0; i < 4; i++) {
            if (HSD_TExpGetType(var_r29->c_in[i].exp) == HSD_TE_TEV) {
                if (var_r29->c_in[i].sel == 1) {
                    sp20[var_r29->c_in[i].exp->tev.c_dst] -= 1;
                } else {
                    sp1C[var_r29->c_in[i].exp->tev.a_dst] -= 1;
                }
            }
            if (HSD_TExpGetType(var_r29->a_in[i].exp) == HSD_TE_TEV) {
                sp1C[var_r29->a_in[i].exp->tev.a_dst] -= 1;
            }
        }

        var_r29 = temp_r27->tev;
        if (var_r29->c_ref > 0) {
            for (i = 3; i >= 0; i--) {
                if (sp20[i] == 0) {
                    sp20[i] = var_r29->c_ref;
                    var_r29->c_dst = i;
                    if (var_r24 > i) {
                        var_r24 = i;
                    }
                    break;
                }
            }
        }
        temp_r5 = var_r29->a_ref;
        if (temp_r5 > 0) {
            for (i = 3; i >= 0; i--) {
                if (sp1C[i] == 0) {
                    sp1C[i] = temp_r5;
                    var_r29->a_dst = i;
                    if (var_r23 > i) {
                        var_r23 = i;
                    }
                    break;
                }
            }
        }
    }
    return (4 - var_r24) + (4 - var_r23);
}

void order_dag(int num, int* dep, int* full_dep, HSD_TExpDag* list, int depth,
               int node, int scheduled, int available, int* order,
               int* best_score, int* best_order)
{
    HSD_TExpDag* dag;
    int new_scheduled;
    int new_available;
    int blocked;
    int dep_bits;
    int score;
    int i;
    int n;
    int rem;

    new_scheduled = scheduled | (1 << node);
    new_available = available & ~(1 << node);
    order[depth] = (u8) node;

    if (depth + 1 == num) {
        score = assign_reg(num, (u32*) dep, list, order);
        if (score < *best_score) {
            *best_score = score;
            i = 0;
            if (num > 0) {
                rem = num - 8;
                if (num <= 8) {
                    goto remainder;
                }
                n = (u32) (rem + 7) >> 3;
                if (rem <= 0) {
                    goto remainder;
                }
                {
                    int* src = order;
                    int* dst = best_order;

                    do {
                        i += 8;
                        dst[0] = src[0];
                        dst[1] = src[1];
                        dst[2] = src[2];
                        dst[3] = src[3];
                        dst[4] = src[4];
                        dst[5] = src[5];
                        dst[6] = src[6];
                        dst[7] = src[7];
                        src += 8;
                        dst += 8;
                    } while (--n > 0);
                }
            remainder: {
                    int* src2 = order + i;
                    int* dst2 = best_order + i;

                    n = num - i;
                    if (i < num) {
                        do {
                            *dst2 = *src2;
                            src2++;
                            dst2++;
                        } while (--n > 0);
                    }
                }
            }
        }
    } else {
        dep_bits = dep[node];
        blocked = new_available | dep_bits;
        {
            int* fp = full_dep;

            dep_bits = 0;
            n = 0;
            for (i = 0; i < num; i++) {
                if (blocked & (1 << n)) {
                    dep_bits |= *fp;
                }
                fp++;
                n++;
            }
        }
        dag = &list[node];
        new_available = blocked & ~dep_bits;
        if (dag->nb_dep == 1 && (new_available & dep[node])) {
            order_dag(num, dep, full_dep, list, depth + 1,
                      dag->depend[0]->idx, new_scheduled, new_available,
                      order, best_score, best_order);
        } else {
            for (i = 0; i < num; i++) {
                if (new_available & (1 << i)) {
                    order_dag(num, dep, full_dep, list, depth + 1, i,
                              new_scheduled, new_available, order,
                              best_score, best_order);
                }
            }
        }
    }
}

void CalcDistance(HSD_TExp** tevs, int* dist, HSD_TExp* tev, int num,
                  int depth)
{
    int idx;
    int i;

    idx = 0;
    for (i = 0; i < num; i++) {
        if (tevs[i] == tev) {
            if (dist[idx] < depth) {
                dist[idx] = depth;
                for (i = 0; i < 4; i++) {
                    if (tev->tev.c_in[i].type == 1) {
                        CalcDistance(tevs, dist, tev->tev.c_in[i].exp, num,
                                    depth + 1);
                    }
                    if (tev->tev.a_in[i].type == 1) {
                        CalcDistance(tevs, dist, tev->tev.a_in[i].exp, num,
                                    depth + 1);
                    }
                }
            }
            return;
        }
        idx++;
    }
}

/// #HSD_TExpMakeDag

void make_full_dependancy_mtx(int num, int* dep, int* full)
{
    int* src;
    int* dst;
    int* row;
    int changed;
    int rem;
    int i;
    int j;
    int old;
    int n;

    i = 0;
    if (num > 0) {
        rem = num - 8;
        if (num <= 8) {
            goto remainder;
        }
        n = (u32) (rem + 7) >> 3;
        if (rem <= 0) {
            goto remainder;
        }
        src = dep;
        dst = full;
        do {
            i += 8;
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
            dst[5] = src[5];
            dst[6] = src[6];
            dst[7] = src[7];
            src += 8;
            dst += 8;
        } while (--n > 0);
    remainder:
        n = num - i;
        src = dep + i;
        dst = full + i;
        if (i < num) {
            do {
                *dst = *src;
                src++;
                dst++;
            } while (--n > 0);
        }
    }
    do {
        row = full;
        changed = 0;
        j = 0;
        while (j < num) {
            n = *row;
            for (i = 0; i < num; i++) {
                if ((1 << j) & full[i]) {
                    old = full[i];
                    full[i] = old | n;
                    if (old != full[i]) {
                        changed = 1;
                    }
                }
            }
            row++;
            j++;
        }
    } while (changed != 0);
}

void fn_80386230(void) {}

static u8 pad[0x44] = { 0 };
static int HSD_TExpDag_80407AA0_44[4] = {
    2,
    4,
    6,
    0,
};
static int HSD_TExpDag_80407AA0_54[4] = {
    3,
    5,
    7,
    1,
};
static int HSD_TExpDag_80407AA0_64[8] = {
    1,
    2,
    3,
    0,
};

void HSD_TExpSchedule(int num, HSD_TExpDag* list, HSD_TExp** result,
                      HSD_TExpRes* resource)
{
    int* var_r29;
    HSD_TExp** var_r28;
    int var_r27;
    u8 temp_r0;
    u8 temp_r0_2;
    int var_r7;
    int idx;
    int i;

    int sp1AC[32];
    int sp12C[32];
    int spAC[32];
    int sp2C[32];
    int sp28;

    sp28 = 5;
    memset(sp2C, 0, sizeof(sp2C));

    for (idx = 0; idx < num; idx++) {
        sp1AC[idx] = 0;
        for (var_r7 = 0; var_r7 < list[idx].nb_dep; var_r7++) {
            sp1AC[idx] |= 1 << list[idx].depend[var_r7]->idx;
        }
    }

    make_full_dependancy_mtx(num, sp1AC, sp12C);
    // sp8 = &spAC;
    var_r29 = sp2C;
    // spC = &sp28;
    // sp10 = var_r29;
    order_dag(num, sp1AC, sp12C, list, 0, 0, 0, 0, spAC, &sp28, var_r29);
    var_r28 = result;
    var_r27 = 0;
    while (var_r27 < num) {
        *var_r28 = (HSD_TExp*) list[*var_r29].tev;
        temp_r0 = (*var_r28)->tev.c_dst;
        if (temp_r0 != 0xFF) {
            resource->reg[temp_r0 + 4].color = 3;

            for (i = 0; i < 4; i++) {
                if (HSD_TExpGetType((*var_r28)->tev.c_in[i].exp) == HSD_TE_TEV)
                {
                    if ((*var_r28)->tev.c_in[i].sel == 1) {
                        (*var_r28)->tev.c_in[i].arg =
                            HSD_TExpDag_80407AA0_44[(*var_r28)->tev.c_in[i]
                                                        .exp->tev.c_dst];
                    } else {
                        (*var_r28)->tev.c_in[i].arg =
                            HSD_TExpDag_80407AA0_54[(*var_r28)->tev.c_in[i]
                                                        .exp->tev.c_dst];
                    }
                }
            }
        }
        temp_r0_2 = (*var_r28)->tev.a_dst;
        if (temp_r0_2 != 0xFF) {
            resource->reg[temp_r0_2 + 4].alpha = 1;

            for (i = 0; i < 4; i++) {
                if (HSD_TExpGetType((*var_r28)->tev.a_in[i].exp) == HSD_TE_TEV)
                {
                    (*var_r28)->tev.a_in[i].arg =
                        HSD_TExpDag_80407AA0_64[(*var_r28)->tev.a_in[i]
                                                    .exp->tev.a_dst];
                }
            }
        }
        var_r29 += 1;
        var_r28 += 1;
        var_r27 += 1;
    }
}

/// #SimplifySrc

/// #SimplifyThis

/// #SimplifyByMerge

int HSD_TExpSimplify(HSD_TExp* texp_)
{
    HSD_TExp* texp = texp_;
    int res = false;
    if (HSD_TExpGetType(texp) != HSD_TE_TEV) {
        return false;
    }
    if (SimplifySrc(texp) != 0) {
        res = true;
    }
    if (SimplifyThis(texp) != 0) {
        res = true;
    }
    if (SimplifyByMerge(texp) != 0) {
        res = true;
    }
    return res;
}

int HSD_TExpSimplify2(HSD_TExp* texp)
{
    HSD_TExp* child;
    u8 sel;
    int i;
    int r3;
    int r4;
    int r5;
    int r6;

    for (i = 0; i < 4; i++) {
        child = texp->tev.c_in[i].exp;
        sel = texp->tev.c_in[i].sel;
        if (texp->tev.c_in[i].type == HSD_TE_TEV && sel == 1) {
            r3 = 0;
            r4 = 0;
            r5 = 0;
            r6 = 0;
            if (child->tev.c_op == 0 && child->tev.c_in[0].sel == HSD_TE_0) {
                r6 = 1;
            }
            if (r6 != 0 && child->tev.c_in[1].sel == HSD_TE_0) {
                r5 = 1;
            }
            if (r5 != 0 && child->tev.c_bias == 0) {
                r4 = 1;
            }
            if (r4 != 0 && child->tev.c_scale == 0) {
                r3 = 1;
            }
            if (r3 != 0) {
                switch (child->tev.c_in[3].type) {
                case HSD_TE_KONST:
                    if (texp->tev.kcsel == 0xFF) {
                        texp->tev.kcsel = child->tev.kcsel;
                    } else if (texp->tev.kcsel != child->tev.kcsel) {
                        break;
                    }
                    /* fallthrough */
                case HSD_TE_IMM:
                    texp->tev.c_in[i] = child->tev.c_in[3];
                    HSD_TExpRef(texp->tev.c_in[i].exp, texp->tev.c_in[i].sel);
                    HSD_TExpUnref(child, sel);
                    break;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        child = texp->tev.a_in[i].exp;
        sel = texp->tev.a_in[i].sel;
        if (texp->tev.a_in[i].type == HSD_TE_TEV) {
            r3 = 0;
            r4 = 0;
            r5 = 0;
            r6 = 0;
            if (child->tev.a_op == 0 && child->tev.a_in[0].sel == HSD_TE_0) {
                r6 = 1;
            }
            if (r6 != 0 && child->tev.a_in[1].sel == HSD_TE_0) {
                r5 = 1;
            }
            if (r5 != 0 && child->tev.a_bias == 0) {
                r4 = 1;
            }
            if (r4 != 0 && child->tev.a_scale == 0) {
                r3 = 1;
            }
            if (r3 != 0) {
                switch (child->tev.a_in[3].type) {
                case HSD_TE_KONST:
                    if (texp->tev.kasel == 0xFF) {
                        texp->tev.kasel = child->tev.kasel;
                    } else if (texp->tev.kasel != child->tev.kasel) {
                        break;
                    }
                    /* fallthrough */
                case HSD_TE_IMM:
                    texp->tev.a_in[i] = child->tev.a_in[3];
                    HSD_TExpRef(texp->tev.a_in[i].exp, texp->tev.a_in[i].sel);
                    HSD_TExpUnref(child, sel);
                    break;
                }
            }
        }
    }
    return 0;
}
