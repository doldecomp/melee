#include "ftCo_Attack100.h"

#include "ft/chara/ftCommon/inlines.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0CDD.h"
#include "ft/inlines.h"
#include "it/items/itsscope.h"

void fn_800D84D4(Fighter_GObj*, int);
FtMotionId fn_800D769C(Fighter* ft, FtMotionId msid);

void fn_800D7BDC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_GObj* temp_gobj;
    FtMotionId msid;
    f32 zero;

    msid = fn_800D769C(fp, ftCo_MS_ItemScopeRapid);
    zero = 0.0F;
    temp_gobj = gobj;
    Fighter_ChangeMotionState(temp_gobj, msid, 0x02000000, zero, 1.0F, zero,
                              NULL);
    fp->mv.co.common.x0 = (int) p_ftCommonData->x5BC;
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D7C60(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_GObj* temp_gobj;
    FtMotionId msid;

    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirRapid);
    {
        f32 zero = 0.0F;
        temp_gobj = gobj;
        Fighter_ChangeMotionState(temp_gobj, msid, 0x02000000, zero, 1.0F,
                                  zero, NULL);
    }
    ftCommon_ClampAirDrift(fp);
    fp->mv.co.common.x0 = (int) p_ftCommonData->x5BC;
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D7CEC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D7FC(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeRapid);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D7D70(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirRapid);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}

void ftCo_ItemScopeRapid_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PAD_STACK(8);

    if (fp->cur_anim_frame >= 0.0F && fp->cur_anim_frame < fp->frame_speed_mul)
    {
        ft_800892A0(gobj);
        ft_80089824(gobj);
        fp->mv.co.common.x0--;

        if (fp->mv.co.common.x0 == 0) {
            fn_800D86E0(gobj);
        } else if (fp->item_gobj != NULL && it_8026B594(fp->item_gobj) != 0) {
            fp = gobj->user_data;

            if (fp->ground_or_air == GA_Ground) {
                Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeRapidEmpty,
                                          0x0C4C5080, fp->cur_anim_frame,
                                          fp->frame_speed_mul, 0.0F, NULL);
            } else {
                Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeAirRapidEmpty,
                                          0x0C4C5080, fp->cur_anim_frame,
                                          fp->frame_speed_mul, 0.0F, NULL);
            }
            fp->accessory4_cb = fn_800D80F4;
            fp->take_dmg_cb = fn_800D8378;
        }
    }
}

void ftCo_ItemScopeAirRapid_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PAD_STACK(8);

    if (fp->cur_anim_frame >= 0.0F && fp->cur_anim_frame < fp->frame_speed_mul)
    {
        ft_800892A0(gobj);
        ft_80089824(gobj);
        fp->mv.co.common.x0--;

        if (fp->mv.co.common.x0 == 0) {
            fn_800D874C(gobj);
        } else if (fp->item_gobj != NULL && it_8026B594(fp->item_gobj) != 0) {
            fp = gobj->user_data;

            if (fp->ground_or_air == GA_Ground) {
                Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeRapidEmpty,
                                          0x0C4C5080, fp->cur_anim_frame,
                                          fp->frame_speed_mul, 0.0F, NULL);
            } else {
                Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeAirRapidEmpty,
                                          0x0C4C5080, fp->cur_anim_frame,
                                          fp->frame_speed_mul, 0.0F, NULL);
            }
            fp->accessory4_cb = fn_800D80F4;
            fp->take_dmg_cb = fn_800D8378;
        }
    }
}

void ftCo_ItemScopeRapid_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_PAD_A) {
        *(s32*) ((u8*) fp + 0x2340) = *(s32*) ((u8*) p_ftCommonData + 0x5BC);
    }
}

void ftCo_ItemScopeAirRapid_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = *(Fighter**) ((u8*) gobj + 0x2C);

    if (fp->input.x668 & HSD_PAD_A) {
        *(s32*) ((u8*) fp + 0x2340) = *(s32*) ((u8*) p_ftCommonData + 0x5BC);
    }
}

void ftCo_ItemScopeRapid_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirRapid_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

void ftCo_ItemScopeRapid_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D7D70);
}

void ftCo_ItemScopeAirRapid_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D7CEC);
}

void fn_800D80F4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->item_gobj != NULL) {
        fn_800D84D4(gobj, it_80291DAC(fp->item_gobj, 0));
    }
}
