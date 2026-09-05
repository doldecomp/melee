#include "ftcrazyhandcapturedamagecrazyhand.h"

#include "ftcrazyhandcapturewaitcrazyhand.h"
#include "ftcrazyhandfingerbeam.h"

#include <sysdolphin/baselib/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_Attack100.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

void ftCh_GrabUnk1_8015B670(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x151, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->invisible = true;
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x2220_b3 = true;
    ftAnim_8006EBA4(gobj);
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void ftCo_CaptureDamageCrazyHand_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_GrabMash(fp, p_ftCommonData->x3A8);
    if (fp->grab_timer <= 0) {
        ftCh_GrabUnk1_8015B778(gobj);
        ftCh_Init_80159098(fp->victim_gobj);
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

void ftCo_CaptureDamageCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureDamageCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureDamageCrazyHand_Coll(HSD_GObj* gobj) {}
