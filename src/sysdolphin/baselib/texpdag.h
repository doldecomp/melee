#ifndef _texpdag_h_
#define _texpdag_h_

#include <platform.h>
#include <baselib/forward.h>

#include <baselib/texp.h>

typedef struct HSD_TExpDag {
    struct _HSD_TETev* tev;
    u8 idx;
    u8 nb_dep;
    u8 nb_ref;
    u8 dist;
    HSD_TExpDag* depend[8];
};

void HSD_TExpSchedule(int num, HSD_TExpDag* list, HSD_TExp** result,
                      HSD_TExpRes* resource);
int HSD_TExpSimplify(HSD_TExp* texp);
int HSD_TExpSimplify2(HSD_TExp* texp);
int HSD_TExpMakeDag(HSD_TExp* root, HSD_TExpDag* list);

#endif
