#include "texpdag.h"

#include "texp.h"
#include "tobj.h"

#include "baselib/debug.h"

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
    u32 dep_bits;
    u32 blocked;
    u32 full_bits;
    int score;
    int i;
    int n;

    done_set |= 1 << idx;
    ready_set &= ~(1 << idx);
    order[depth++] = (u8) idx;

    if (depth == num) {
        score = assign_reg(num, dep, list, order);
        if (score < *min) {
            *min = score;
            for (i = 0; i < num; i++) {
                min_order[i] = order[i];
            }
        }
    } else {
        {
            u32* fp = full_dep;

            dep_bits = dep[idx];
            {
                u32 tmp = ready_set | dep_bits;
                blocked = tmp;
            }
            full_bits = 0;
            n = 0;
            for (i = 0; i < num; i++) {
                if (blocked & (1 << n)) {
                    full_bits |= *fp;
                }
                fp++;
                n++;
            }
        }
        dag = &list[idx];
        ready_set = blocked & ~full_bits;
        if (dag->nb_dep == 1 && (ready_set & dep_bits)) {
            sp8 = order;
            spC = min;
            sp10 = min_order;
            order_dag(num, dep, full_dep, list, depth, dag->depend[0]->idx,
                      done_set, ready_set, sp8, spC, sp10);
        } else {
            for (i = 0; i < num; i++) {
                if (ready_set & (1 << i)) {
                    sp8 = order;
                    spC = min;
                    sp10 = min_order;
                    order_dag(num, dep, full_dep, list, depth, i, done_set,
                              ready_set, sp8, spC, sp10);
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

#define HSD_TEXP_MAX_NUM 32

int HSD_TExpMakeDag(HSD_TExp* root, HSD_TExpDag* list)
{
    HSD_TExp* sp94[32];
    int sp14[32];
    HSD_TExp* tmp;
    HSD_TExp* cur;
    HSD_TExp* cur2;
    HSD_TExp** base;
    HSD_TExp** p;
    HSD_TExpDag* dep_entry;
    HSD_TExpDag* dep_entry2;
    HSD_TExpDag* dag;
    int count;
    int count2;
    int num;
    int j;
    int i;
    int k;
    int l;
    int last;
    int idx;
    int idx2;
    u32 loop_count3;
    int loop_count4;
    int dist;
    PAD_STACK(4);

    HSD_ASSERT(0xEEU, HSD_TExpGetType(root) == HSD_TE_TEV);

    base = &sp94[0];
    num = 0;
    base[num++] = root;
    p = base;
    j = 0;
    while (j < num) {
        HSD_ASSERT(0xF6U, j<HSD_TEXP_MAX_NUM);
        cur = *p;
        tmp = cur;
        for (i = 0; i < 4; i++) {
            if ((u8) cur->tev.c_in[0].type == HSD_TE_TEV) {
                HSD_TExp** q = base;
                for (k = 0; k < num; k++) {
                    if (*q == cur->tev.c_in[0].exp) {
                        break;
                    }
                    q++;
                }
                if (k >= num) {
                    base[num++] = cur->tev.c_in[0].exp;
                }
            }
            cur = (HSD_TExp*) ((u8*) cur + sizeof(HSD_TEArg));
        }

        cur2 = tmp;
        for (i = 0; i < 4; i++) {
            if ((u8) cur2->tev.a_in[0].type == HSD_TE_TEV) {
                HSD_TExp** r = base;
                for (k = 0; k < num; k++) {
                    if (*r == cur2->tev.a_in[0].exp) {
                        break;
                    }
                    r++;
                }
                if (k >= num) {
                    base[num++] = cur2->tev.a_in[0].exp;
                }
            }
            cur2 = (HSD_TExp*) ((u8*) cur2 + sizeof(HSD_TEArg));
        }

        p++;
        j++;
    }

    j = 0;
    if (num > 0) {
        count = num - 8;
        if (num > 8) {
            loop_count3 = (u32) (count + 7) >> 3;
            {
                int* distp = &sp14[0];

                if (count > 0) {
                    do {
                        distp[0] = -1;
                        j += 8;
                        distp[1] = -1;
                        distp[2] = -1;
                        distp[3] = -1;
                        distp[4] = -1;
                        distp[5] = -1;
                        distp[6] = -1;
                        distp[7] = -1;
                        distp += 8;
                        loop_count3--;
                    } while (loop_count3 != 0);
                }
            }
        }
        {
            int* distp = &sp14[j];

            loop_count4 = num - j;
            if (j < num) {
                do {
                    *distp = -1;
                    distp++;
                    loop_count4--;
                } while (loop_count4 != 0);
            }
        }
    }

    CalcDistance(&sp94[0], &sp14[0], sp94[0], num, 0);
    for (idx = 0; idx < num; idx++) {
        count2 = idx + 1;
        {
            HSD_TExp** r3;
            int* distp = &sp14[count2];

            r3 = &sp94[count2];
            for (; count2 < num; count2++) {
                if (distp[-1] > distp[0]) {
                    HSD_TExp* tmp2;

                    tmp2 = r3[-1];
                    r3[-1] = r3[0];
                    r3[0] = tmp2;
                    dist = distp[-1];
                    distp[-1] = distp[0];
                    distp[0] = dist;
                }
                distp++;
                r3++;
            }
        }
    }

    last = num - 1;
    dag = &list[last];
    p = &sp94[last];
loop_65:
    if (last >= 0) {
        tmp = *p;
        idx = 0;
        dag->idx = (u8) last;
        cur = tmp;
        dag->nb_ref = 0;
        dag->nb_dep = 0;
        dag->tev = &tmp->tev;
        do {
            if ((u8) cur->tev.c_in[0].type == HSD_TE_TEV) {
                HSD_TExp** q = &sp94[last];
                for (l = last; l < num; l++) {
                    if (cur->tev.c_in[0].exp == *q) {
                        HSD_TExpDag** deps;
                        u8 dep_count;

                        dep_count = dag->nb_dep;
                        deps = dag->depend;
                        dep_entry = &list[l];
                        for (l = 0; l < (int) dep_count; l++) {
                            if (*deps == dep_entry) {
                                break;
                            }
                            deps++;
                        }
                        if (l >= (int) dag->nb_dep) {
                            dag->depend[dag->nb_dep] = dep_entry;
                            dag->nb_dep++;
                            dep_entry->nb_ref++;
                        }
                        break;
                    }
                    q++;
                }
                HSD_ASSERT(0x145, l < num);
            }
            idx++;
            cur = (HSD_TExp*) ((u8*) cur + sizeof(HSD_TEArg));
        } while (idx < 4);

        idx2 = 0;
        cur2 = tmp;
        do {
            if ((u8) cur2->tev.a_in[0].type == HSD_TE_TEV) {
                HSD_TExp** r2 = &sp94[last];
                for (l = last; l < num; l++) {
                    if (cur2->tev.a_in[0].exp == *r2) {
                        HSD_TExpDag** deps2;
                        u8 dep_count2;

                        dep_count2 = dag->nb_dep;
                        deps2 = dag->depend;
                        dep_entry2 = &list[l];
                        for (l = 0; l < (int) dep_count2; l++) {
                            if (*deps2 == dep_entry2) {
                                break;
                            }
                            deps2++;
                        }
                        if (l >= (int) dag->nb_dep) {
                            dag->depend[dag->nb_dep] = dep_entry2;
                            dag->nb_dep++;
                            dep_entry2->nb_ref++;
                        }
                        break;
                    }
                    r2++;
                }
                HSD_ASSERT(0x15B, l < num);
            }
            idx2++;
            cur2 = (HSD_TExp*) ((u8*) cur2 + sizeof(HSD_TEArg));
        } while (idx2 < 4);

        dag--;
        p--;
        last--;
        goto loop_65;
    }
    return num;
}

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
            flag = 1 << j;
            old = full[j];
            bits = old;
            for (k = 0; k < num; k++) {
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
    u32 clear_arg;
    HSD_TExp* clear_exp;
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
                    clear_exp = HSD_TExpDag_804D5FFC;
                    clear_arg = HSD_TExpDag_804D5FF8;
                    *(u32*) c_arg = clear_arg;
                    c_arg->exp = clear_exp;
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
                    clear_exp = HSD_TExpDag_804D5FFC;
                    clear_arg = HSD_TExpDag_804D5FF8;
                    *(u32*) c_arg = clear_arg;
                    c_arg->exp = clear_exp;
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
                clear_exp = HSD_TExpDag_804D5FFC;
                clear_arg = HSD_TExpDag_804D5FF8;
                *(u32*) a_arg = clear_arg;
                a_arg->exp = clear_exp;
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

#define CLEAR_ARG(arg)                                                        \
    do {                                                                      \
        clear_arg = HSD_TExpDag_804D5FF8;                                     \
        clear_exp = HSD_TExpDag_804D5FFC;                                     \
        *(u32*) &(arg) = clear_arg;                                           \
        (arg).exp = clear_exp;                                                \
    } while (0)

#define BIAS_TO_INT(bias) ((bias) == 1 ? 1 : ((bias) == 2 ? -1 : 0))
#define INT_TO_BIAS(v) ((v) == 1 ? 1 : ((v) == -1 ? 2 : 0))
#define RESOURCE_CONFLICT(tex_obj, chan_id, src_exp)                          \
    ((((tex_obj) != NULL) && ((src_exp)->tev.tex != NULL) &&                  \
      ((tex_obj) != (src_exp)->tev.tex)) ||                                   \
     (((chan_id) != 0xFF) && ((src_exp)->tev.chan != 0xFF) &&                 \
      ((chan_id) != (src_exp)->tev.chan)))

int SimplifyThis(HSD_TExp* arg0)
{
    HSD_TExp* cur;
    u32 clear_arg;
    HSD_TExp* clear_exp;
    int color_tex;
    int alpha_tex;
    int color_ras;
    int alpha_ras;
    int result;
    int changed;
    int op;
    int i;

    result = 0;
    do {
        color_tex = -1;
        alpha_tex = -1;
        color_ras = -1;
        alpha_ras = -1;

        cur = arg0;
        for (i = 0; i < 4; i++) {
            switch (cur->tev.c_in[0].type) {
            case HSD_TE_TEX:
                color_tex = i;
                break;
            case HSD_TE_RAS:
                color_ras = i;
                break;
            }
            switch (cur->tev.a_in[0].type) {
            case HSD_TE_TEX:
                alpha_tex = i;
                break;
            case HSD_TE_RAS:
                alpha_ras = i;
                break;
            }
            cur = (HSD_TExp*) ((u8*) cur + sizeof(HSD_TEArg));
        }

        if (color_tex == -1 && alpha_tex == -1) {
            arg0->tev.tex = NULL;
            arg0->tev.tex_swap = 0xFF;
        }
        if (color_ras == -1 && alpha_ras == -1) {
            arg0->tev.chan = 0xFF;
            arg0->tev.ras_swap = 0xFF;
        }

        changed = 0;
        if (arg0->tev.a_op == 0xFF || ((u8) (arg0->tev.a_op - 0xE) <= 1U) ||
            arg0->tev.a_op <= 1)
        {
            if (arg0->tev.c_op != 0xFF && arg0->tev.c_ref == 0) {
                arg0->tev.c_op = 0xFF;
                cur = arg0;
                for (i = 0; i < 4; i++) {
                    HSD_TExpUnref(cur->tev.c_in[0].exp, cur->tev.c_in[0].sel);
                    CLEAR_ARG(cur->tev.c_in[0]);
                    cur = (HSD_TExp*) ((u8*) cur + sizeof(HSD_TEArg));
                }
                changed = 1;
            }

            switch (arg0->tev.c_op) {
            case 0:
            case 1:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    if (arg0->tev.c_in[1].sel != HSD_TE_0) {
                        HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                      arg0->tev.c_in[1].sel);
                        changed = 1;
                        CLEAR_ARG(arg0->tev.c_in[1]);
                    }
                    if (arg0->tev.c_op == 0 &&
                        arg0->tev.c_in[3].sel == HSD_TE_0)
                    {
                        changed = 1;
                        arg0->tev.c_in[3] = arg0->tev.c_in[0];
                        CLEAR_ARG(arg0->tev.c_in[0]);
                        arg0->tev.c_clamp = 1;
                    }
                }
                if (arg0->tev.c_in[2].sel == HSD_TE_1) {
                    if (arg0->tev.c_in[0].sel != HSD_TE_0) {
                        HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                      arg0->tev.c_in[0].sel);
                        changed = 1;
                        CLEAR_ARG(arg0->tev.c_in[0]);
                    }
                    if (arg0->tev.c_op == 0 &&
                        arg0->tev.c_in[3].sel == HSD_TE_0)
                    {
                        changed = 1;
                        arg0->tev.c_in[3] = arg0->tev.c_in[1];
                        CLEAR_ARG(arg0->tev.c_in[1]);
                        CLEAR_ARG(arg0->tev.c_in[2]);
                    }
                }
                if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                    arg0->tev.c_in[1].sel == HSD_TE_0 &&
                    arg0->tev.c_in[3].sel == HSD_TE_0 && arg0->tev.c_bias == 0)
                {
                    arg0->tev.c_op = 0xFF;
                    HSD_TExpUnref(arg0->tev.c_in[2].exp,
                                  arg0->tev.c_in[2].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            case 8:
            case 10:
            case 12:
            case 14:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                  arg0->tev.c_in[0].sel);
                    CLEAR_ARG(arg0->tev.c_in[0]);
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[1]);
                } else if (arg0->tev.c_in[0].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    CLEAR_ARG(arg0->tev.c_in[1]);
                    HSD_TExpUnref(arg0->tev.c_in[2].exp,
                                  arg0->tev.c_in[2].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            case 9:
            case 11:
            case 13:
            case 15:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                  arg0->tev.c_in[0].sel);
                    CLEAR_ARG(arg0->tev.c_in[0]);
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[1]);
                } else if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                           arg0->tev.c_in[1].sel == HSD_TE_0)
                {
                    arg0->tev.c_op = 0;
                    changed = 1;
                    arg0->tev.c_in[0] = arg0->tev.c_in[2];
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            }
        }

        if (arg0->tev.a_op != 0xFF && arg0->tev.a_ref == 0) {
            arg0->tev.a_op = 0xFF;
            cur = arg0;
            for (i = 0; i < 4; i++) {
                HSD_TExpUnref(cur->tev.a_in[0].exp, cur->tev.a_in[0].sel);
                CLEAR_ARG(cur->tev.a_in[0]);
                cur = (HSD_TExp*) ((u8*) cur + sizeof(HSD_TEArg));
            }
            changed = 1;
        }

        op = arg0->tev.a_op;
        if (op != 0xE) {
            if (op < 0xE) {
                if (op < 2) {
                    if (op >= 0) {
                        if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                            if (arg0->tev.a_in[1].sel != HSD_TE_0) {
                                HSD_TExpUnref(arg0->tev.a_in[1].exp,
                                              arg0->tev.a_in[1].sel);
                                changed = 1;
                                CLEAR_ARG(arg0->tev.a_in[1]);
                            }
                            if (arg0->tev.a_op == 0 &&
                                arg0->tev.a_in[3].sel == HSD_TE_0)
                            {
                                changed = 1;
                                arg0->tev.a_in[3] = arg0->tev.a_in[0];
                                CLEAR_ARG(arg0->tev.a_in[0]);
                            }
                        }
                        if (arg0->tev.a_in[2].sel == HSD_TE_1) {
                            if (arg0->tev.a_in[0].sel != HSD_TE_0) {
                                HSD_TExpUnref(arg0->tev.a_in[0].exp,
                                              arg0->tev.a_in[0].sel);
                                changed = 1;
                                CLEAR_ARG(arg0->tev.a_in[0]);
                            }
                            if (arg0->tev.a_op == 0 &&
                                arg0->tev.a_in[3].sel == HSD_TE_0)
                            {
                                changed = 1;
                                arg0->tev.a_in[3] = arg0->tev.a_in[1];
                                CLEAR_ARG(arg0->tev.a_in[1]);
                                CLEAR_ARG(arg0->tev.a_in[2]);
                            }
                        }
                        if (arg0->tev.a_in[0].sel == HSD_TE_0 &&
                            arg0->tev.a_in[1].sel == HSD_TE_0 &&
                            arg0->tev.a_in[3].sel == HSD_TE_0)
                        {
                            arg0->tev.a_op = 0xFF;
                            changed = 1;
                        }
                    }
                } else if (op >= 8) {
                    if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                        arg0->tev.a_op = 0;
                        HSD_TExpUnref(arg0->tev.a_in[0].exp,
                                      arg0->tev.a_in[0].sel);
                        CLEAR_ARG(arg0->tev.a_in[0]);
                        HSD_TExpUnref(arg0->tev.a_in[1].exp,
                                      arg0->tev.a_in[1].sel);
                        changed = 1;
                        CLEAR_ARG(arg0->tev.a_in[1]);
                    }
                }
            } else if (op < 0x10) {
                if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                    arg0->tev.a_op = 0;
                    HSD_TExpUnref(arg0->tev.a_in[0].exp,
                                  arg0->tev.a_in[0].sel);
                    CLEAR_ARG(arg0->tev.a_in[0]);
                    HSD_TExpUnref(arg0->tev.a_in[1].exp,
                                  arg0->tev.a_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.a_in[1]);
                } else if (arg0->tev.a_in[0].sel == HSD_TE_0 &&
                           arg0->tev.a_in[1].sel == HSD_TE_0)
                {
                    arg0->tev.a_op = 0;
                    changed = 1;
                    arg0->tev.a_in[0] = arg0->tev.a_in[2];
                    CLEAR_ARG(arg0->tev.a_in[2]);
                }
            }
        } else if (arg0->tev.a_in[2].sel == HSD_TE_0) {
            arg0->tev.a_op = 0;
            HSD_TExpUnref(arg0->tev.a_in[0].exp, arg0->tev.a_in[0].sel);
            CLEAR_ARG(arg0->tev.a_in[0]);
            HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
            changed = 1;
            CLEAR_ARG(arg0->tev.a_in[1]);
        } else if (arg0->tev.a_in[0].sel == HSD_TE_0) {
            arg0->tev.a_op = 0;
            HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
            CLEAR_ARG(arg0->tev.a_in[1]);
            HSD_TExpUnref(arg0->tev.a_in[2].exp, arg0->tev.a_in[2].sel);
            changed = 1;
            CLEAR_ARG(arg0->tev.a_in[2]);
        }

        if (changed != 0) {
            result = 1;
        }
    } while (changed != 0);

    return result;
}

int SimplifyByMerge(HSD_TExp* arg0)
{
    HSD_TExp* child;
    HSD_TEArg tmp_arg;
    int bias;
    int result;
    int merged;
    int i;
    int conflict;
    u8 type;
    u8 child_sel;
    u8 new_op;

    result = 0;
    do {
        merged = 0;

        if (arg0->tev.a_op == 0xFF || ((u8) (arg0->tev.a_op - 0xE) <= 1U) ||
            arg0->tev.a_op <= 1)
        {
            if ((arg0->tev.c_op == 0 || arg0->tev.c_op == 1) &&
                arg0->tev.c_in[1].sel == HSD_TE_0 &&
                arg0->tev.c_in[2].sel == HSD_TE_0 &&
                HSD_TExpGetType(arg0->tev.c_in[0].exp) != HSD_TE_CNST &&
                HSD_TExpGetType(arg0->tev.c_in[3].exp) != HSD_TE_CNST)
            {
                if (arg0->tev.c_op == 0 &&
                    arg0->tev.c_in[3].type == HSD_TE_TEV &&
                    ((arg0->tev.c_in[3].sel == HSD_TE_RGB &&
                      arg0->tev.c_in[3].exp->tev.c_clamp != 0) ||
                     (arg0->tev.c_in[3].sel == HSD_TE_A &&
                      arg0->tev.c_in[3].exp->tev.a_clamp != 0)))
                {
                    type = arg0->tev.c_in[0].type;
                    switch ((s32) type) {
                    case HSD_TE_TEX:
                    case HSD_TE_RAS:
                        tmp_arg = arg0->tev.c_in[0];
                        arg0->tev.c_in[0] = arg0->tev.c_in[3];
                        arg0->tev.c_in[3] = tmp_arg;
                        break;
                    }
                }

                switch (arg0->tev.c_in[0].type) {
                case HSD_TE_TEV:
                    if (arg0->tev.c_in[0].sel == HSD_TE_RGB) {
                        child = arg0->tev.c_in[0].exp;
                        child_sel = arg0->tev.c_in[0].sel;
                        if ((child->tev.c_op == 0 || child->tev.c_op == 1) &&
                            child->tev.c_in[3].sel == HSD_TE_0 &&
                            child->tev.c_scale == 0)
                        {
                            if (arg0->tev.tex != NULL &&
                                child->tev.tex != NULL &&
                                arg0->tev.tex != child->tev.tex)
                            {
                                conflict = 1;
                            } else if (arg0->tev.chan != 0xFF &&
                                       child->tev.chan != 0xFF &&
                                       arg0->tev.chan != child->tev.chan)
                            {
                                conflict = 1;
                            } else {
                                conflict = 0;
                            }
                            if (conflict == 0) {
                                switch ((s32) child->tev.c_bias) {
                                case 1:
                                    bias = 1;
                                    break;
                                case 2:
                                    bias = -1;
                                    break;
                                default:
                                    bias = 0;
                                    break;
                                }
                                if (child->tev.c_op == 1) {
                                    bias = -bias;
                                }
                                switch ((s32) arg0->tev.c_bias) {
                                case 1:
                                    bias += 1;
                                    break;
                                case 2:
                                    bias -= 1;
                                    break;
                                }
                                switch (bias) {
                                case 0:
                                    arg0->tev.c_bias = 0;
                                    merged = 1;
                                    break;
                                case 1:
                                    arg0->tev.c_bias = 1;
                                    merged = 1;
                                    break;
                                case -1:
                                    arg0->tev.c_bias = 2;
                                    merged = 1;
                                    break;
                                default:
                                    merged = 0;
                                    break;
                                }
                                if (merged != 0) {
                                    if (child->tev.c_op == 1) {
                                        if (arg0->tev.c_op == 0) {
                                            new_op = 1;
                                        } else {
                                            new_op = 0;
                                        }
                                        arg0->tev.c_op = new_op;
                                    }
                                    for (i = 0; i < 3; i++) {
                                        arg0->tev.c_in[i] = child->tev.c_in[i];
                                        HSD_TExpRef(arg0->tev.c_in[i].exp,
                                                    arg0->tev.c_in[i].sel);
                                    }
                                    if (arg0->tev.tex == NULL) {
                                        arg0->tev.tex = child->tev.tex;
                                    }
                                    if (arg0->tev.chan == 0xFF) {
                                        arg0->tev.chan = child->tev.chan;
                                    }
                                    if (arg0->tev.tex_swap == 0xFF) {
                                        arg0->tev.tex_swap =
                                            child->tev.tex_swap;
                                    }
                                    if (arg0->tev.ras_swap == 0xFF) {
                                        arg0->tev.ras_swap =
                                            child->tev.ras_swap;
                                    }
                                    HSD_TExpUnref(child, child_sel);
                                }
                            }
                        }
                    }
                    break;
                case HSD_TE_ZERO:
                    if (arg0->tev.c_in[3].type == HSD_TE_TEV) {
                        child_sel = arg0->tev.c_in[3].sel;
                        if (child_sel == HSD_TE_RGB) {
                            child = arg0->tev.c_in[3].exp;
                            if (child->tev.c_scale == 0 &&
                                (arg0->tev.c_bias == 0 ||
                                 arg0->tev.c_bias != child->tev.c_bias))
                            {
                                if (arg0->tev.tex != NULL &&
                                    child->tev.tex != NULL &&
                                    arg0->tev.tex != child->tev.tex)
                                {
                                    conflict = 1;
                                } else if (arg0->tev.chan != 0xFF &&
                                           child->tev.chan != 0xFF &&
                                           arg0->tev.chan != child->tev.chan)
                                {
                                    conflict = 1;
                                } else {
                                    conflict = 0;
                                }
                                if (conflict == 0) {
                                    merged = 1;
                                    for (i = 0; i < 4; i++) {
                                        arg0->tev.c_in[i] = child->tev.c_in[i];
                                        HSD_TExpRef(arg0->tev.c_in[i].exp,
                                                    arg0->tev.c_in[i].sel);
                                    }
                                    arg0->tev.c_op = child->tev.c_op;
                                    switch ((s32) child->tev.c_bias) {
                                    case 1:
                                        bias = 1;
                                        break;
                                    case 2:
                                        bias = -1;
                                        break;
                                    default:
                                        bias = 0;
                                        break;
                                    }
                                    if (child->tev.c_op == 1) {
                                        bias = -bias;
                                    }
                                    switch ((s32) arg0->tev.c_bias) {
                                    case 1:
                                        bias += 1;
                                        break;
                                    case 2:
                                        bias -= 1;
                                        break;
                                    }
                                    switch (bias) {
                                    case 1:
                                        arg0->tev.c_bias = 1;
                                        break;
                                    case -1:
                                        arg0->tev.c_bias = 2;
                                        break;
                                    default:
                                    case 0:
                                        arg0->tev.c_bias = 0;
                                        break;
                                    }
                                    if (arg0->tev.c_clamp == 0xFF ||
                                        arg0->tev.c_clamp == 0)
                                    {
                                        arg0->tev.c_clamp = child->tev.c_clamp;
                                    }
                                    if (arg0->tev.tex == NULL) {
                                        arg0->tev.tex = child->tev.tex;
                                    }
                                    if (arg0->tev.chan == 0xFF) {
                                        arg0->tev.chan = child->tev.chan;
                                    }
                                    if (arg0->tev.tex_swap == 0xFF) {
                                        arg0->tev.tex_swap =
                                            child->tev.tex_swap;
                                    }
                                    if (arg0->tev.ras_swap == 0xFF) {
                                        arg0->tev.ras_swap =
                                            child->tev.ras_swap;
                                    }
                                    HSD_TExpUnref(child, child_sel);
                                }
                            }
                        }
                    }
                    break;
                }
            }

            if ((arg0->tev.a_op == 0 || arg0->tev.a_op == 1) &&
                arg0->tev.a_in[1].sel == HSD_TE_0 &&
                arg0->tev.a_in[2].sel == HSD_TE_0 &&
                HSD_TExpGetType(arg0->tev.a_in[0].exp) != HSD_TE_CNST &&
                HSD_TExpGetType(arg0->tev.a_in[3].exp) != HSD_TE_CNST)
            {
                if (arg0->tev.a_op == 0 &&
                    arg0->tev.a_in[3].type == HSD_TE_TEV &&
                    arg0->tev.a_in[3].exp->tev.a_clamp != 0)
                {
                    type = arg0->tev.a_in[0].type;
                    switch ((s32) type) {
                    case HSD_TE_TEX:
                    case HSD_TE_RAS:
                        tmp_arg = arg0->tev.a_in[0];
                        arg0->tev.a_in[0] = arg0->tev.a_in[3];
                        arg0->tev.a_in[3] = tmp_arg;
                        break;
                    }
                }

                switch (arg0->tev.a_in[0].type) {
                case HSD_TE_TEV:
                    child = arg0->tev.a_in[0].exp;
                    child_sel = arg0->tev.a_in[0].sel;
                    if ((child->tev.a_op == 0 || child->tev.a_op == 1) &&
                        child->tev.a_in[3].sel == HSD_TE_0 &&
                        child->tev.a_scale == 0)
                    {
                        if (arg0->tev.tex != NULL && child->tev.tex != NULL &&
                            arg0->tev.tex != child->tev.tex)
                        {
                            conflict = 1;
                        } else if (arg0->tev.chan != 0xFF &&
                                   child->tev.chan != 0xFF &&
                                   arg0->tev.chan != child->tev.chan)
                        {
                            conflict = 1;
                        } else {
                            conflict = 0;
                        }
                        if (conflict == 0) {
                            switch ((s32) child->tev.a_bias) {
                            case 1:
                                bias = 1;
                                break;
                            case 2:
                                bias = -1;
                                break;
                            default:
                                bias = 0;
                                break;
                            }
                            if (child->tev.a_op == 1) {
                                bias = -bias;
                            }
                            switch ((s32) arg0->tev.a_bias) {
                            case 1:
                                bias += 1;
                                break;
                            case 2:
                                bias -= 1;
                                break;
                            }
                            switch (bias) {
                            case 0:
                                arg0->tev.a_bias = 0;
                                merged = 1;
                                break;
                            case 1:
                                arg0->tev.a_bias = 1;
                                merged = 1;
                                break;
                            case -1:
                                arg0->tev.a_bias = 2;
                                merged = 1;
                                break;
                            default:
                                merged = 0;
                                break;
                            }
                            if (merged != 0) {
                                if (child->tev.a_op == 1) {
                                    if (arg0->tev.a_op == 0) {
                                        new_op = 1;
                                    } else {
                                        new_op = 0;
                                    }
                                    arg0->tev.a_op = new_op;
                                }
                                for (i = 0; i < 3; i++) {
                                    arg0->tev.a_in[i] = child->tev.a_in[i];
                                    HSD_TExpRef(arg0->tev.a_in[i].exp,
                                                arg0->tev.a_in[i].sel);
                                }
                                if (arg0->tev.tex == NULL) {
                                    arg0->tev.tex = child->tev.tex;
                                }
                                if (arg0->tev.chan == 0xFF) {
                                    arg0->tev.chan = child->tev.chan;
                                }
                                HSD_TExpUnref(child, child_sel);
                            }
                        }
                    }
                    break;
                case HSD_TE_ZERO:
                    if (arg0->tev.a_in[3].type == HSD_TE_TEV) {
                        child = arg0->tev.a_in[3].exp;
                        child_sel = arg0->tev.a_in[3].sel;
                        if (child->tev.a_scale == 0 &&
                            (arg0->tev.a_bias == 0 ||
                             arg0->tev.a_bias != child->tev.a_bias))
                        {
                            if (arg0->tev.tex != NULL &&
                                child->tev.tex != NULL &&
                                arg0->tev.tex != child->tev.tex)
                            {
                                conflict = 1;
                            } else if (arg0->tev.chan != 0xFF &&
                                       child->tev.chan != 0xFF &&
                                       arg0->tev.chan != child->tev.chan)
                            {
                                conflict = 1;
                            } else {
                                conflict = 0;
                            }
                            if (conflict == 0) {
                                merged = 1;
                                for (i = 0; i < 4; i++) {
                                    arg0->tev.a_in[i] = child->tev.a_in[i];
                                    HSD_TExpRef(arg0->tev.a_in[i].exp,
                                                arg0->tev.a_in[i].sel);
                                }
                                arg0->tev.a_op = child->tev.a_op;
                                switch ((s32) child->tev.a_bias) {
                                case 1:
                                    bias = 1;
                                    break;
                                case 2:
                                    bias = -1;
                                    break;
                                default:
                                    bias = 0;
                                    break;
                                }
                                if (child->tev.a_op == 1) {
                                    bias = -bias;
                                }
                                switch ((s32) arg0->tev.a_bias) {
                                case 1:
                                    bias += 1;
                                    break;
                                case 2:
                                    bias -= 1;
                                    break;
                                }
                                switch (bias) {
                                case 1:
                                    arg0->tev.a_bias = 1;
                                    break;
                                case -1:
                                    arg0->tev.a_bias = 2;
                                    break;
                                default:
                                case 0:
                                    arg0->tev.a_bias = 0;
                                    break;
                                }
                                if (arg0->tev.a_clamp == 0xFF ||
                                    arg0->tev.a_clamp == 0)
                                {
                                    arg0->tev.a_clamp = child->tev.a_clamp;
                                }
                                if (arg0->tev.tex == NULL) {
                                    arg0->tev.tex = child->tev.tex;
                                }
                                if (arg0->tev.chan == 0xFF) {
                                    arg0->tev.chan = child->tev.chan;
                                }
                                HSD_TExpUnref(child, child_sel);
                            }
                        }
                    }
                    break;
                }
            }
        }

        if (merged != 0) {
            result = 1;
        }
    } while (merged != 0);

    return result;
}

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

int HSD_TExpSimplify2(HSD_TExp* texp_)
{
    HSD_TExp* texp = (HSD_TExp*) texp_;
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
