#include "ftCo_0C60.h"

#include "ftCo_HammerWait.h"
#include "ftCo_Pass.h"

#include "ft/inlines.h"
#include "ft/types.h"

bool ftCo_800C60C8(Fighter_GObj* gobj)
{
    if (ftCo_80099F1C(gobj)) {
        ftCo_800C6110(gobj);
        return true;
    }
    return false;
}

void ftCo_800C6110(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_8009A184(gobj, ftCo_MS_HammerFall, Ft_MF_None, 0);
    ftCo_800C4E94(fp);
}
