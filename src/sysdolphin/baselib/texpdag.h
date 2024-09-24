#ifndef SYSDOLPHIN_BASELIB_TEXPDAG_H
#define SYSDOLPHIN_BASELIB_TEXPDAG_H

#include <platform.h>
#include "baselib/forward.h"

#include "baselib/texp.h"

#include <placeholder.h>

typedef struct HSD_TExpDag {
    struct _HSD_TETev* tev;
    u8 idx;
    u8 nb_dep;
    u8 nb_ref;
    u8 dist;
    HSD_TExpDag* depend[8];
} HSD_TExpDag;

/* 385798 */ UNK_RET assign_reg(UNK_PARAMS);
/* 385944 */ UNK_RET order_dag(UNK_PARAMS);
/* 385B8C */ UNK_RET CalcDistance(UNK_PARAMS);
/* 385C60 */ int HSD_TExpMakeDag(HSD_TExp* root, HSD_TExpDag* list);
/* 386100 */ UNK_RET make_full_dependancy_mtx(UNK_PARAMS);
/* 386230 */ UNK_RET fn_80386230(UNK_PARAMS);
/* 386234 */ void HSD_TExpSchedule(int num, HSD_TExpDag* list,
                                   HSD_TExp** result, HSD_TExpRes* resource);
/* 386470 */ UNK_RET SimplifySrc(UNK_PARAMS);
/* 38687C */ UNK_RET SimplifyThis(UNK_PARAMS);
/* 3870E4 */ UNK_RET SimplifyByMerge(UNK_PARAMS);
/* 387B1C */ int HSD_TExpSimplify(HSD_TExp* texp);
/* 387BA4 */ int HSD_TExpSimplify2(HSD_TExp* texp);

#endif
