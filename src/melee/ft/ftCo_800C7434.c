#include "ftCo_800C7434.h"

#include "ft_0852.h"
#include "ftCo_800C7070.h"
#include "ftCo_800C7434.h"
#include "ftCo_800C7590.h"
#include "ftcommon.h"

#include <placeholder.h>

#include "ft/fighter.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "it/items/itgreatfoxlaser.h"
#include "it/items/itleadead.h"

static inline void inlineB0(Fighter_GObj* gobj)
{
    ftCo_800C7070(gobj);
}

static inline void inlineB1(Fighter_GObj* gobj)
{
    inlineB0(gobj);
}

static inline void inlineB2(Fighter_GObj* gobj)
{
    inlineB1(gobj);
}

void ftCo_800C7434(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_MotionState ms;
    if (fp->kind == FTKIND_GKOOPS) {
        ms = 0xE;
    } else {
        inlineB2(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ms, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}

void ftCo_800C74AC(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}

void fn_800C74CC(Fighter_GObj* gobj)
{
    it_802EADD8(GET_FIGHTER(gobj)->mv.co.captureleadead.x0);
}

bool ftCo_800C74F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x1860_element == 16 && fp->capture_timer == 0 &&
        fp->motion_id != ftCo_MS_CaptureLeadead &&
        it_802EAF28(fp->dmg.x1868_source) == 0U)
    {
        ftCo_800C7590(gobj);
        return true;
    }
    return false;
}

void fn_800C7568(Fighter_GObj* gobj)
{
    it_802EADD8(GET_FIGHTER(gobj)->mv.co.captureleadead.x0);
}
