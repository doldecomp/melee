#include "ftCo_Attack100.h"
#include "ftCo_ItemScopeStart.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0CDD.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "it/kinds/itsscope.h"

void fn_800D8140(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    fp->throw_flags = 0;
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeFire);
    {
        HSD_GObj* gobj2 = gobj;
        float zero = 0.0F;
        Fighter_ChangeMotionState(gobj2, msid, Ft_MF_None, zero, 1.0F, zero,
                                  NULL);
    }
    fp->mv.co.common.x0 = arg1;
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D81D0(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    fp->throw_flags = 0;
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirFire);
    {
        HSD_GObj* gobj2 = gobj;
        float zero = 0.0F;
        Fighter_ChangeMotionState(gobj2, msid, Ft_MF_None, zero, 1.0F, zero,
                                  NULL);
    }
    ftCommon_ClampAirDrift(fp);
    fp->mv.co.common.x0 = arg1;
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D8268(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    ftCommon_8007D7FC(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeFire);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D82EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirFire);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D8378(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->item_gobj != NULL) {
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ftCo_ItemScopeFire_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ftCo_ItemScopeAirFire_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ftCo_ItemScopeFire_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirFire_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeFire_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirFire_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

void ftCo_ItemScopeFire_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D82EC);
}

void ftCo_ItemScopeAirFire_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D8268);
}

void fn_800D84D4(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = gobj->user_data;
    Vec3 sp20;
    Vec3 sp14;
    PAD_STACK(4);

    if (fp->item_gobj != NULL) {
        if (ftCheckThrowB0(fp)) {
            it_80291CCC(fp->item_gobj, &sp14);
            ftCo_800CDE94(fp, &sp14, &sp20);
            if (arg1 == 0) {
                it_80291FA8(fp->item_gobj, &sp20, arg1, fp->facing_dir);
                sp20.z = 0.0F;
                efSync_Spawn(0x430, fp->gobj, &sp20, &fp->facing_dir);
                ft_PlaySFX(fp, 0xFC, 0x7F, 0x40);
            } else if (arg1 >= 1 && arg1 <= 8) {
                it_80291FA8(fp->item_gobj, &sp20, arg1, fp->facing_dir);
                sp20.z = 0.0F;
                efSync_Spawn(0x430, fp->gobj, &sp20, &fp->facing_dir);
                if (arg1 <= 4) {
                    ft_PlaySFX(fp, 0xFF, 0x7F, 0x40);
                } else {
                    ft_PlaySFX(fp, 0x100, 0x7F, 0x40);
                }
            } else if (arg1 == 9) {
                it_80291FA8(fp->item_gobj, &sp20, arg1, fp->facing_dir);
                sp20.z = 0.0F;
                efSync_Spawn(0x430, fp->gobj, &sp20, &fp->facing_dir);
                ft_PlaySFX(fp, 0x100, 0x7F, 0x40);
            } else {
                efSync_Spawn(0x405, gobj, &sp20);
                ft_PlaySFX(fp, 0x101, 0x7F, 0x40);
            }
        }
    }
}

void fn_800D86B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D84D4(gobj, fp->mv.co.common.x0);
}
