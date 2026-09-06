#include <melee/ft/fighter.h>
#include <melee/ft/types.h>

bool ftCo_800D67C4(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_B) {
        if (ABS(fp->input.lstick.x) < p_ftCommonData->x218 &&
            ABS(fp->input.lstick.y) < p_ftCommonData->x21C)
        {
            return true;
        }
    }
    return false;
}
