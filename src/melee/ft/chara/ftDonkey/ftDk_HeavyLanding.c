#include <platform.h>

#include "ftDk_HeavyLanding.h"

#include "ftDk_HeavyTurn.h"
#include "ftDk_HeavyWait0.h"

#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Damage.h"
#include "ftDonkey/types.h"
#include "it/item.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

void ftDk_HeavyLanding_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_HeavyLanding_Coll(HSD_GObj* gobj)
{
    ftDk_HeavyWait0_Coll(gobj);
}

static bool checkSomething(HSD_GObj* gobj);
static void doSomething(HSD_GObj* gobj);

void ftDk_MS_349_800E06D8(HSD_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp = GET_FIGHTER(gobj);
    if (checkSomething(gobj)) {
        doSomething(gobj);
    } else {
        vec.x = vec.y = vec.z = 0;
        Item_8026ABD8(fp->item_gobj, &vec, 1);
        ftCo_8008E908(gobj, 0);
    }
}

bool checkSomething(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCo_8008E984(fp)) {
        return true;
    }
    if (ftCo_8008D8E8(ftCo_ScaleBy154(fp->dmg.kb_applied)) < 3) {
        return true;
    }
    return false;
}

void doSomething(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2CC;
    ftCo_8008DCE0(gobj, donkey_attr->motion_state + 9, 0);
}

void ftDk_HeavyWait2_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_8008F744(gobj);
    if (!fp->x221C_b6) {
        if (fp->ground_or_air == GA_Air) {
            ftDk_MS_345_800E0294(gobj);
        } else {
            ftDk_MS_341_800DF980(gobj);
        }
    }
}

void ftDk_HeavyWait2_Phys(HSD_GObj* gobj)
{
    ftCo_Damage_Phys(gobj);
}

void ftDk_HeavyWait2_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        if (!ft_80082708(gobj)) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
    }
}
