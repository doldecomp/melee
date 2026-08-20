#include "ftCo_Attack100.h"

#include "ft/chara/ftCommon/inlines.h"
#include "ft/ft_081B.h"
#include "ft/ft_0CDD.h"
#include "ft/inlines.h"

FtMotionId fn_800D769C(Fighter* ft, FtMotionId msid);

void fn_800D86E0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, ftCo_MS_ItemScopeEnd), 0,
                              0.0F, 1.0F, 0.0F, NULL);
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D874C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_GObj* temp_gobj;
    FtMotionId msid;
    f32 zero;

    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirEnd);
    zero = 0.0F;
    temp_gobj = gobj;
    Fighter_ChangeMotionState(temp_gobj, msid, 0, 0.0F, 1.0F, zero, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D87C0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D7FC(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeEnd);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D8838(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirEnd);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->take_dmg_cb = fn_800D8378;
}

void ftCo_ItemScopeEnd_Anim(Fighter_GObj* gobj)
{
    ftCo_ItemScopeFire_Anim(gobj);
}

void ftCo_ItemScopeAirEnd_Anim(Fighter_GObj* gobj)
{
    ftCo_ItemScopeFire_Anim(gobj);
}

void ftCo_ItemScopeEnd_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirEnd_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeEnd_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirEnd_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

void ftCo_ItemScopeEnd_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D8838);
}

void ftCo_ItemScopeAirEnd_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D87C0);
}
