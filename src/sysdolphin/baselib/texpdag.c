#include "texpdag.h"

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

/// #HSD_TExpSchedule

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
