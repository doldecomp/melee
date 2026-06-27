#include "ftkirbycaptureyoshi.h"

#include <placeholder.h>

#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 4D95A0 */ extern f64 ftKb_Init_804D95A0;

void fn_8010A930(Fighter_GObj* gobj, Fighter_GObj* attacker_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* attacker_fp = GET_FIGHTER(attacker_gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = attacker_gobj;
    fp->victim_gobj = attacker_gobj;
    fp->x221B_b5 = false;
    fp->x221B_b7 = false;
    fp->facing_dir = -attacker_fp->facing_dir;
    ftCo_800DB368(attacker_fp, fp);
    Fighter_ChangeMotionState(gobj, 0x14B, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
}

void ftCo_CaptureKirbyYoshi_Anim(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_Coll(Fighter_GObj* gobj) {}

void ftKb_SpecialNYs_8010AA2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->invisible = true;
    ftColl_8007B62C(gobj, 2);
}
