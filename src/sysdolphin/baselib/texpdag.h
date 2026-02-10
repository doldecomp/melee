#ifndef SYSDOLPHIN_BASELIB_TEXPDAG_H
#define SYSDOLPHIN_BASELIB_TEXPDAG_H

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "baselib/texp.h"

typedef struct HSD_TExpDag {
    struct _HSD_TETev* tev;
    u8 idx;
    u8 nb_dep;
    u8 nb_ref;
    u8 dist;
    HSD_TExpDag* depend[8];
} HSD_TExpDag;

/* 385798 */ int assign_reg(int num, u32*, HSD_TExpDag* list, int* order);
/* 385944 */ void order_dag(int num, u32* dep, u32* full_dep,
                            HSD_TExpDag* list, int depth, int node,
                            int scheduled, int available, int* order,
                            int* best_score, int* best_order);
/* 385B8C */ void CalcDistance(HSD_TExp** tevs, int* dist, HSD_TExp* tev,
                               int num, int depth);
/* 385C60 */ int HSD_TExpMakeDag(HSD_TExp* root, HSD_TExpDag* list);
/* 386100 */ void make_full_dependancy_mtx(int num, u32* dep, u32* full);
/* 386230 */ UNK_RET fn_80386230(UNK_PARAMS);
/* 386234 */ void HSD_TExpSchedule(int num, HSD_TExpDag* list,
                                   HSD_TExp** result, HSD_TExpRes* resource);
/* 386470 */ int SimplifySrc(HSD_TExp*);
/* 38687C */ int SimplifyThis(HSD_TExp*);
/* 3870E4 */ int SimplifyByMerge(HSD_TExp*);
/* 387B1C */ int HSD_TExpSimplify(HSD_TExp* texp);
/* 387BA4 */ int HSD_TExpSimplify2(HSD_TExp* texp);

#endif
