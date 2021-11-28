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
