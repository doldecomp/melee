#include "ft/forward.h"

#include "ftDk_MS_345_0.h"

#include "ft/ft_0C88.h"
#include "ft/inlines.h"
#include "ftDonkey/types.h"

static void ifSomething(HSD_GObj* gobj);

bool ftDk_MS_345_800E0134(HSD_GObj* gobj)
{
    if (ftCo_800C97A8(gobj)) {
        ifSomething(gobj);
        return true;
    }
    return false;
}

static void ifSomething(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftCo_Turn_Enter(gobj, donkey_attr->motion_state + 4, 0, 0,
                  donkey_attr->cargo_hold.x20_TURN_SPEED, 0);
}
