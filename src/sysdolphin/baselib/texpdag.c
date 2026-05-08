#include "texpdag.h"

#include "texp.h"
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

void order_dag(int num, u32* dep, u32* full_dep, HSD_TExpDag* list, int depth,
               int idx, u32 done_set, u32 ready_set, int* order, int* min,
               int* min_order)
{
    int* sp8;
    int* spC;
    int* sp10;
    HSD_TExpDag* dag;
    int new_scheduled;
    u32 new_available;
    u32 blocked;
    u32 dep_bits;
    int score;
    int i;
    int n;
    int rem;
    PAD_STACK(8);

    new_scheduled = done_set | (1 << idx);
    new_available = ready_set & ~(1 << idx);
    order[depth] = (u8) idx;

    if (depth + 1 == num) {
        score = assign_reg(num, dep, list, order);
        if (score < *min) {
            *min = score;
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
                    int* dst = min_order;

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
                int* dst2 = min_order + i;

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
        dep_bits = dep[idx];
        blocked = new_available | dep_bits;
        {
            u32* fp = full_dep;

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
        dag = &list[idx];
        new_available = blocked & ~dep_bits;
        if (dag->nb_dep == 1 && (new_available & dep[idx])) {
            sp8 = order;
            spC = min;
            sp10 = min_order;
            order_dag(num, dep, full_dep, list, depth + 1, dag->depend[0]->idx,
                      new_scheduled, new_available, sp8, spC, sp10);
        } else {
            for (i = 0; i < num; i++) {
                if (new_available & (1 << i)) {
                    sp8 = order;
                    spC = min;
                    sp10 = min_order;
                    order_dag(num, dep, full_dep, list, depth + 1, i,
                              new_scheduled, new_available, sp8, spC, sp10);
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

static void make_dependancy_mtx(int num, HSD_TExpDag* list, u32* dep_mtx)
{
    HSD_TExpDag* dag;
    int i, j;

    for (i = 0; i < num; i++) {
        dep_mtx[i] = 0;
        dag = &list[i];
        for (j = 0; j < dag->nb_dep; j++) {
            dep_mtx[i] |= 1 << dag->depend[j]->idx;
        }
    }
}

void make_full_dependancy_mtx(int num, u32* dep, u32* full)
{
    int i, j, k;
    bool changed;
    u32 bits;
    u32 flag;
    u32 old;

    for (i = 0; i < num; i++) {
        full[i] = dep[i];
    }
    do {
        changed = false;
        for (j = 0; j < num; j++) {
            bits = full[j];
            for (k = 0; k < num; k++) {
                flag = (1 << j);
                if ((flag & full[k]) != 0) {
                    u32 old = full[k];
                    full[k] |= bits;
                    if (old != full[k]) {
                        changed = true;
                    }
                }
            }
        }
    } while (changed != false);
}

static u8 pad[0x44] = { 0 };

void HSD_TExpSchedule(int num, HSD_TExpDag* list, HSD_TExp** result,
                      HSD_TExpRes* resource)
{
    static int c_in[4] = { GX_CC_C0, GX_CC_C1, GX_CC_C2, GX_CC_CPREV };
    static int a_in[4] = { GX_CC_A0, GX_CC_A1, GX_CC_A2, GX_CC_APREV };
    static int args[8] = { GX_CA_A0, GX_CA_A1, GX_CA_A2, GX_CA_APREV };

    u32 dep_mtx[32];
    u32 full_dep_matrix[32];
    u32 order[32];
    u32 min_order[32];

    int i, j;
    int min;

    min = 5;
    memset(min_order, 0, sizeof(min_order));
    make_dependancy_mtx(num, list, dep_mtx);
    make_full_dependancy_mtx(num, dep_mtx, full_dep_matrix);
    order_dag(num, dep_mtx, full_dep_matrix, list, 0, 0, 0, 0, (int*) order,
              &min, (int*) min_order);

    for (i = 0; i < num; i++) {
        result[i] = (HSD_TExp*) list[min_order[i]].tev;
        if (result[i]->tev.c_dst != 0xFF) {
            resource->reg[result[i]->tev.c_dst + 4].color = 3;

            for (j = 0; j < 4; j++) {
                if (HSD_TExpGetType(result[i]->tev.c_in[j].exp) == HSD_TE_TEV)
                {
                    if (result[i]->tev.c_in[j].sel == 1) {
                        result[i]->tev.c_in[j].arg =
                            c_in[result[i]->tev.c_in[j].exp->tev.c_dst];
                    } else {
                        result[i]->tev.c_in[j].arg =
                            a_in[result[i]->tev.c_in[j].exp->tev.c_dst];
                    }
                }
            }
        }
        if (result[i]->tev.a_dst != 0xFF) {
            resource->reg[result[i]->tev.a_dst + 4].alpha = 1;

            for (j = 0; j < 4; j++) {
                if (HSD_TExpGetType(result[i]->tev.a_in[j].exp) == HSD_TE_TEV)
                {
                    result[i]->tev.a_in[j].arg =
                        args[result[i]->tev.a_in[j].exp->tev.a_dst];
                }
            }
        }
    }
}

static s32 HSD_TExpDag_804D5FF8 = 0x7FF00;
static HSD_TExp* HSD_TExpDag_804D5FFC = NULL;

int SimplifySrc(HSD_TExp* arg0)
{
    HSD_TEArg* c_arg;
    HSD_TEArg* a_arg;
    HSD_TExp* src;
    HSD_TObj* tobj;
    int result;
    int i;
    u8 sel;

    c_arg = arg0->tev.c_in;
    result = 0;
    for (i = 0; i < 4; i++) {
        if (c_arg->type == HSD_TE_TEV) {
            src = c_arg->exp;
            sel = c_arg->sel;
            if (HSD_TExpSimplify(src) != 0) {
                result = 1;
            }
            if (sel == HSD_TE_RGB) {
                switch (src->tev.c_op) {
                case 0xFF:
                    HSD_TExpUnref(src, sel);
                    result = 1;
                    *(u32*) c_arg = HSD_TExpDag_804D5FF8;
                    c_arg->exp = HSD_TExpDag_804D5FFC;
                    break;
                case GX_TEV_ADD:
                    if (src->tev.c_in[0].sel == HSD_TE_0 &&
                        src->tev.c_in[1].sel == HSD_TE_0 &&
                        src->tev.c_bias == 0 && src->tev.c_scale == 0)
                    {
                        switch (src->tev.c_in[3].type) {
                        case HSD_TE_TEV:
                            if (src->tev.c_in[3].exp->tev.c_clamp != 0 ||
                                src->tev.c_clamp == 0)
                            {
                                *c_arg = src->tev.c_in[3];
                                HSD_TExpRef(c_arg->exp, c_arg->sel);
                                HSD_TExpUnref(src, sel);
                                result = 1;
                            }
                            break;
                        case HSD_TE_TEX:
                            tobj = arg0->tev.tex;
                            if ((tobj == NULL || tobj == src->tev.tex) &&
                                (arg0->tev.tex_swap == 0xFF ||
                                 src->tev.tex_swap == 0xFF ||
                                 arg0->tev.tex_swap == src->tev.tex_swap))
                            {
                                *c_arg = src->tev.c_in[3];
                                arg0->tev.tex = src->tev.tex;
                                if (arg0->tev.tex_swap == 0xFF) {
                                    arg0->tev.tex_swap = src->tev.tex_swap;
                                }
                                HSD_TExpUnref(src, sel);
                                result = 1;
                            }
                            break;
                        case HSD_TE_RAS:
                            if ((arg0->tev.chan == 0xFF ||
                                 arg0->tev.chan == src->tev.chan) &&
                                (arg0->tev.ras_swap == 0xFF ||
                                 src->tev.ras_swap == 0xFF ||
                                 arg0->tev.ras_swap == src->tev.tex_swap))
                            {
                                *c_arg = src->tev.c_in[3];
                                arg0->tev.chan = src->tev.chan;
                                if (arg0->tev.tex_swap == 0xFF) {
                                    arg0->tev.tex_swap = src->tev.tex_swap;
                                }
                                HSD_TExpUnref(src, sel);
                                result = 1;
                            }
                            break;
                        }
                    }
                    break;
                }
            } else {
                switch (src->tev.a_op) {
                case GX_TEV_ADD:
                    break;
                case 0xFF:
                    HSD_TExpUnref(src, sel);
                    result = 1;
                    *(u32*) c_arg = HSD_TExpDag_804D5FF8;
                    c_arg->exp = HSD_TExpDag_804D5FFC;
                    break;
                }
            }
        }
        c_arg++;
    }

    a_arg = arg0->tev.a_in;
    for (i = 0; i < 4; i++) {
        if (a_arg->type == HSD_TE_TEV) {
            src = a_arg->exp;
            sel = a_arg->sel;
            HSD_TExpSimplify(src);
            switch (src->tev.a_op) {
            case 0xFF:
                HSD_TExpUnref(src, sel);
                result = 1;
                *(u32*) a_arg = HSD_TExpDag_804D5FF8;
                a_arg->exp = HSD_TExpDag_804D5FFC;
                break;
            case GX_TEV_ADD:
                if (src->tev.a_in[0].sel == HSD_TE_0 &&
                    src->tev.a_in[1].sel == HSD_TE_0 && src->tev.a_bias == 0 &&
                    src->tev.a_scale == 0)
                {
                    switch (src->tev.a_in[3].type) {
                    case HSD_TE_TEV:
                        *a_arg = src->tev.a_in[3];
                        HSD_TExpRef(a_arg->exp, a_arg->sel);
                        HSD_TExpUnref(src, sel);
                        result = 1;
                        break;
                    case HSD_TE_TEX:
                        tobj = arg0->tev.tex;
                        if (tobj == NULL || tobj == src->tev.tex) {
                            *a_arg = src->tev.a_in[3];
                            arg0->tev.tex = src->tev.tex;
                            HSD_TExpUnref(src, sel);
                            result = 1;
                        }
                        break;
                    case HSD_TE_RAS:
                        if (arg0->tev.chan == 0xFF ||
                            arg0->tev.chan == src->tev.chan)
                        {
                            *a_arg = src->tev.a_in[3];
                            arg0->tev.chan = src->tev.chan;
                            HSD_TExpUnref(src, sel);
                            result = 1;
                        }
                        break;
                    }
                }
                break;
            }
        }
        a_arg++;
    }
    return result;
}

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
    HSD_TExp* src_exp;
    u8 src_sel;
    int i;

    for (i = 0; i < 4; i++) {
        src_exp = texp->tev.c_in[i].exp;
        src_sel = texp->tev.c_in[i].sel;
        if (texp->tev.c_in[i].type == HSD_TE_TEV && src_sel == 1 &&
            IsThroughColor(src_exp))
        {
            switch (src_exp->tev.c_in[3].type) {
            case HSD_TE_KONST:
                if (texp->tev.kcsel == 0xFF) {
                    texp->tev.kcsel = src_exp->tev.kcsel;
                } else if (texp->tev.kcsel != src_exp->tev.kcsel) {
                    break;
                }
                /* fallthrough */
            case HSD_TE_IMM:
                texp->tev.c_in[i] = src_exp->tev.c_in[3];
                HSD_TExpRef(texp->tev.c_in[i].exp, texp->tev.c_in[i].sel);
                HSD_TExpUnref(src_exp, src_sel);
                break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        src_exp = texp->tev.a_in[i].exp;
        src_sel = texp->tev.a_in[i].sel;
        if (texp->tev.a_in[i].type == HSD_TE_TEV && IsThroughAlpha(src_exp)) {
            switch (src_exp->tev.a_in[3].type) {
            case HSD_TE_KONST:
                if (texp->tev.kasel == 0xFF) {
                    texp->tev.kasel = src_exp->tev.kasel;
                } else if (texp->tev.kasel != src_exp->tev.kasel) {
                    break;
                }
                /* fallthrough */
            case HSD_TE_IMM:
                texp->tev.a_in[i] = src_exp->tev.a_in[3];
                HSD_TExpRef(texp->tev.a_in[i].exp, texp->tev.a_in[i].sel);
                HSD_TExpUnref(src_exp, src_sel);
                break;
            }
        }
    }
    return 0;
}
