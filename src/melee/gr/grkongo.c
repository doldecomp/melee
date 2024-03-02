#include "grmaterial.h"
#include "types.h"

#include <baselib/gobj.h>

void grKongo_801D828C(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    if (gp->gv.kongo.xC6 != 1) {
        return;
    }
    HSD_ASSERT(1719, gp->gv.kongo.u.taru.keep);
    if (((u8*) gp->gv.kongo.u.taru.keep)[2] == 8) {
        gp->gv.kongo.xC6 = 0;
        gp->gv.kongo.u.taru.keep = NULL;
        grMaterial_801C95C4(gobj);
    }
}
