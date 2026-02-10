#include "texpdag.h"

#include "tobj.h"

int assign_reg(int num, u32* unused, HSD_TExpDag* list, int* order)
{
    u8 color_refs[4] = { 0 };
    u8 alpha_refs[4] = { 0 };
    HSD_TETev* tev;
    HSD_TExpDag* dag_entry;
    int idx;
    int i;
    int min_color_reg = 4;
    int min_alpha_reg = 4;
    int alpha_ref_count;
    PAD_STACK(4);

    for (idx = num - 1; idx >= 0; idx--) {
        dag_entry = &list[order[idx]];
        tev = dag_entry->tev;

        for (i = 0; i < 4; i++) {
            if (HSD_TExpGetType(tev->c_in[i].exp) == HSD_TE_TEV) {
                if (tev->c_in[i].sel == 1) {
                    color_refs[tev->c_in[i].exp->tev.c_dst] -= 1;
                } else {
                    alpha_refs[tev->c_in[i].exp->tev.a_dst] -= 1;
                }
            }
            if (HSD_TExpGetType(tev->a_in[i].exp) == HSD_TE_TEV) {
                alpha_refs[tev->a_in[i].exp->tev.a_dst] -= 1;
            }
        }

        tev = dag_entry->tev;
        if (tev->c_ref > 0) {
            for (i = 3; i >= 0; i--) {
                if (color_refs[i] == 0) {
                    color_refs[i] = tev->c_ref;
                    tev->c_dst = i;
                    if (min_color_reg > i) {
                        min_color_reg = i;
                    }
                    break;
                }
            }
        }
        alpha_ref_count = tev->a_ref;
        if (alpha_ref_count > 0) {
            for (i = 3; i >= 0; i--) {
                if (alpha_refs[i] == 0) {
                    alpha_refs[i] = alpha_ref_count;
                    tev->a_dst = i;
                    if (min_alpha_reg > i) {
                        min_alpha_reg = i;
                    }
                    break;
                }
            }
        }
    }
    return (4 - min_color_reg) + (4 - min_alpha_reg);
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
    HSD_TExp** p;
    int idx;
    int i;

    p = tevs;
    idx = 0;
    for (i = 0; i < num; i++) {
        if (*p == tev) {
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
        p++;
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
    int* order_ptr;
    HSD_TExp** result_ptr;
    int count;
    u8 c_dst_reg;
    u8 a_dst_reg;
    int j;
    int idx;
    int i;

    int dep_matrix[32];
    int full_dep_matrix[32];
    int work_order[32];
    int best_order[32];
    int best_score;

    best_score = 5;
    memset(best_order, 0, sizeof(best_order));

    for (idx = 0; idx < num; idx++) {
        HSD_TExpDag* dag = &list[idx];
        dep_matrix[idx] = 0;
        for (j = 0; j < dag->nb_dep; j++) {
            dep_matrix[idx] |= 1 << dag->depend[j]->idx;
        }
    }

    make_full_dependancy_mtx(num, dep_matrix, full_dep_matrix);
    // sp8 = &work_order;
    order_ptr = best_order;
    // spC = &best_score;
    // sp10 = order_ptr;
    order_dag(num, dep_matrix, full_dep_matrix, list, 0, 0, 0, 0, work_order,
              &best_score, order_ptr);
    result_ptr = result;
    count = 0;
    while (count < num) {
        *result_ptr = (HSD_TExp*) list[*order_ptr].tev;
        c_dst_reg = (*result_ptr)->tev.c_dst;
        if (c_dst_reg != 0xFF) {
            resource->reg[c_dst_reg + 4].color = 3;

            for (i = 0; i < 4; i++) {
                if (HSD_TExpGetType((*result_ptr)->tev.c_in[i].exp) ==
                    HSD_TE_TEV)
                {
                    if ((*result_ptr)->tev.c_in[i].sel == 1) {
                        (*result_ptr)->tev.c_in[i].arg =
                            HSD_TExpDag_80407AA0_44
                                [(*result_ptr)->tev.c_in[i].exp->tev.c_dst];
                    } else {
                        (*result_ptr)->tev.c_in[i].arg =
                            HSD_TExpDag_80407AA0_54
                                [(*result_ptr)->tev.c_in[i].exp->tev.c_dst];
                    }
                }
            }
        }
        a_dst_reg = (*result_ptr)->tev.a_dst;
        if (a_dst_reg != 0xFF) {
            resource->reg[a_dst_reg + 4].alpha = 1;

            for (i = 0; i < 4; i++) {
                if (HSD_TExpGetType((*result_ptr)->tev.a_in[i].exp) ==
                    HSD_TE_TEV)
                {
                    (*result_ptr)->tev.a_in[i].arg = HSD_TExpDag_80407AA0_64
                        [(*result_ptr)->tev.a_in[i].exp->tev.a_dst];
                }
            }
        }
        order_ptr += 1;
        result_ptr += 1;
        count += 1;
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
