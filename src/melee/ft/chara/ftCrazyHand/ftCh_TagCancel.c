#include "ftCh_TagCancel.h"

#include "ftCh_Init.h"

#include "math.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ft/chara/ftCommon/ftCo_Attack100.h"
#include "ft/chara/ftCommon/ftCo_CaptureCut.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Thrown.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0D4D.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCrazyHand/forward.h"

#include "ftMasterHand/types.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/items/itcrazyhandbomb.h"
#include "it/items/itmasterhandlaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_GrabUnk1_8015B8FC(HSD_GObj*);
#pragma push
#pragma dont_inline on
void ftCh_GrabUnk1_8015B8FC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->fv.mh.x2258 == ftMh_MS_Wait1_0 || fp->fv.mh.x2258 == 0x184) {
        Fighter_ChangeMotionState(gobj, 0x184, 0, fp->cur_anim_frame, 1.0f,
                                  0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, 0x184, 0, 0, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
    fp->fv.mh.x2258 = 0x184;
}

void ftCh_GrabUnk1_8015B998(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->fv.mh.x2258 == ftMh_MS_Wait2_0 || fp->fv.mh.x2258 == 0x185) {
        Fighter_ChangeMotionState(gobj, 0x185, 0, fp->cur_anim_frame, 1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, 0x185, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
    fp->fv.mh.x2258 = 0x185;
}
#pragma pop

void ftCh_GrabUnk1_8015BA34(HSD_GObj*, HSD_GObjEvent, Vec3*);
void ftCh_GrabUnk1_8015BA34(HSD_GObj* gobj, HSD_GObjEvent cb, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[16];
    if (fp->fv.mh.x2258 == ftMh_MS_Wait2_0) {
        if ((fp->fv.mh.x2258 == ftMh_MS_Wait2_0) || (fp->fv.mh.x2258 == 0x185))
        {
            Fighter_ChangeMotionState(gobj, 0x185, 0, fp->cur_anim_frame, 1.0f,
                                      0.0f, NULL);
        } else {
            Fighter_ChangeMotionState(gobj, 0x185, 0, 0, 1.0f, 0.0f, NULL);
            ftAnim_8006EBA4(gobj);
        }
        fp->fv.mh.x2258 = 0x185;
    } else {
        if (fp->fv.mh.x2258 == ftMh_MS_Wait1_0 || fp->fv.mh.x2258 == 0x184) {
            Fighter_ChangeMotionState(gobj, 0x184, 0, fp->cur_anim_frame, 1.0f,
                                      0.0f, NULL);
        } else {
            Fighter_ChangeMotionState(gobj, 0x184, 0, 0, 1.0f, 0.0f, NULL);
            ftAnim_8006EBA4(gobj);
        }
        fp->fv.mh.x2258 = 0x184;
    }
    fp->mv.ch.unk0.x4 = cb;
    fp->mv.ch.unk0.xC = *pos;
}

void ftCh_TagCancel_Anim(HSD_GObj* gobj)
{
    u8 _[4];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->fv.mh.x2258 = ftMh_MS_TagCancel;
        Fighter_ChangeMotionState(gobj, ftMh_MS_TagCancel, 0, 0, 1.0f, 0.0f,
                                  NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_TagCancel_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_TagCancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ch.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
        if (fp->mv.ch.unk0.x4) {
            fp->mv.ch.unk0.x4(gobj);
        }
    }
}

void ftCh_GrabUnk1_8015BC88(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    fp->mv.ch.unk0.x20 = 0;
    {
        Vec3 pos;
        u8 _[8];
        pos.x = da->x18;
        pos.y = da->x1C;
        pos.z = 0;
        fp->fv.mh.x2258 = 0x184;
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.mh.x2258 == 0x156) {
                ftCh_GrabUnk1_8015B998(gobj);
            } else {
                ftCh_GrabUnk1_8015B8FC(gobj);
            }
            fp->mv.ch.unk0.x4 = ftCh_Init_80156198;
            fp->mv.ch.unk0.xC = pos;
        }
    }
}

