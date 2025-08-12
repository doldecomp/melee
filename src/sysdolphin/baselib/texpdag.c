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

/// #order_dag

/// #CalcDistance

/// #HSD_TExpMakeDag

/// #make_full_dependancy_mtx

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
    HSD_TExpDag* temp_r3;
    int var_r27;
    int var_r7;
    u8 temp_r0;
    u8 temp_r0_2;
    int idx;
    int i;
    HSD_TETev* tev;

    int sp1AC[32];
    UNK_T sp12C[0x80 / 4];
    UNK_T spAC[0x80 / 4];
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
                    tev = &(*var_r28)->tev;
                    if (tev->c_in[i].sel == 1) {
                        tev->c_in[i].arg =
                            HSD_TExpDag_80407AA0_44[tev->c_in[i]
                                                        .exp->tev.c_dst];
                    } else {
                        tev->c_in[i].arg =
                            HSD_TExpDag_80407AA0_54[tev->c_in[i]
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
                    tev = &(*var_r28)->tev;
                    tev->a_in[i].arg =
                        HSD_TExpDag_80407AA0_64[tev->a_in[i].exp->tev.a_dst];
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

/// #HSD_TExpSimplify2
