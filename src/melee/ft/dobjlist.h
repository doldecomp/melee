#ifndef MELEE_FT_DOBJLIST_H
#define MELEE_FT_DOBJLIST_H

#include <platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

/**
 * @todo This was split out of ft/types.h to break a circular dependency with
 * fighter-specific types.h headers. Figure out a better place for it.
 */

struct DObjList {
    u32 count;
    HSD_DObj** data;
};

struct CostumeTObjList {
    /*  fp+5CC */ u32 n_costume_tobjs;
    /*  fp+5D0 */ u16* x5D0;
    /*  fp+5D4 */ HSD_TObj* costume_tobjs[5];
};

#endif
