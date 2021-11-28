#include "texp.h"

HSD_TExpType HSD_TExpGetType(HSD_TExp* texp) {
    if (texp == NULL) {
        return HSD_TE_ZERO;
    }
    if ((u32)texp == -1) {
        return HSD_TE_TEX;
    }
    if ((u32)texp == -2) {
        return HSD_TE_RAS;
    }
    return texp->type;
}

inline HSD_TExpType HSD_TExpGetType_inline(HSD_TExp* texp) {
    if (texp == NULL) {
        return HSD_TE_ZERO;
    }
    if ((u32)texp == -1) {
        return HSD_TE_TEX;
    }
    if ((u32)texp == -2) {
        return HSD_TE_RAS;
    }
    return texp->type;
}

void HSD_TExpRef(HSD_TExp* texp, u8 sel)
{
    HSD_TExpType type = HSD_TExpGetType_inline(texp);
    if (type != HSD_TE_CNST) {
        if (type >= HSD_TE_CNST){
            return;
        }
        if (type != HSD_TE_TEV)
        {
            return;
        }
        if (sel == TRUE) {
            texp->tev.c_ref += 1;
            return;
        } else {
            texp->tev.a_ref += 1;
            return;
        }
    }
    
    texp->cnst.ref += 1;
}
