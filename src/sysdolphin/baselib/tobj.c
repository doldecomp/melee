#include "tobj.h"

inline void HSD_TObjRemoveAnim_inline(HSD_TObj* tobj)
{
    if (tobj == NULL){
        return;
    }

    HSD_AObjRemove(tobj->aobj);
    tobj->aobj = NULL;
}

void HSD_TObjRemoveAnimAll(HSD_TObj* tobj)
{
    HSD_TObj* tp;

    if (tobj != NULL){
        for (tp = tobj; tp != NULL; tp = tp->next) {
            HSD_TObjRemoveAnim_inline(tp);
        }
    }
}
