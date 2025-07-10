#include "texpdag.h"

/// #assign_reg

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
