#include "ftCo_Attack100.h"

#include "ft/types.h"

bool ftCo_800D72A0(Fighter* fp)
{
    struct Fighter_x2D0_t* p = fp->x2D0;
    s32 i;

    for (i = 0; i < 2; i++) {
        if ((&p->x2C)[i] != -1) {
            if ((&p->x2C)[i] <= fp->motion_id &&
                fp->motion_id < (&p->x2C)[i] + p->x28)
            {
                return true;
            }
        }
    }
    return false;
}
