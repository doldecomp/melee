#include <melee/ft/kinds/ftCrazyHand/ftcrazyhandtagcancel.h>

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <melee/ft/kinds/ftCrazyHand/ftcrazyhandwait10.h>
#include <melee/ft/kinds/ftCrazyHand/inlines.h>
#include <melee/ft/kinds/ftCrazyHand/types.h>
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/ft/types.h>

void ftCh_GrabUnk1_8015B8FC(HSD_GObj*);
void ftCh_GrabUnk1_8015B8FC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.mh.x2258 == ftMh_MS_Wait1_0 || fp->u.mh.x2258 == 0x184) {
        Fighter_ChangeMotionState(gobj, 0x184, Ft_MF_None, fp->cur_anim_frame, 1.0f,
                                  0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, 0x184, Ft_MF_None, 0, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
    fp->u.mh.x2258 = 0x184;
}

void ftCh_GrabUnk1_8015B998(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.mh.x2258 == ftMh_MS_Wait2_0 || fp->u.mh.x2258 == 0x185) {
        Fighter_ChangeMotionState(gobj, 0x185, Ft_MF_None, fp->cur_anim_frame, 1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, 0x185, Ft_MF_None, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
    fp->u.mh.x2258 = 0x185;
}

void ftCh_GrabUnk1_8015BA34(HSD_GObj* gobj, HSD_GObjEvent cb, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    if (fp->u.mh.x2258 == ftMh_MS_Wait2_0) {
        ftCh_GrabUnk1_8015B998(gobj);
    } else {
        ftCh_GrabUnk1_8015B8FC(gobj);
    }
    fp->mv.ch.unk0.x4 = cb;
    fp->mv.ch.unk0.xC = *pos;
}

void ftCh_TagCancel_Anim(HSD_GObj* gobj)
{
    u32 pad;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->u.mh.x2258 = ftMh_MS_TagCancel;
        Fighter_ChangeMotionState(gobj, ftMh_MS_TagCancel, Ft_MF_None, 0, 1.0f, 0.0f,
                                  NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_TagCancel_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ftCh_UpdateBossMotion(gobj, fp, da);
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
    Vec3 pos;
    u8 _[8];
    fp->mv.ch.unk0.x20 = 0;
    pos.x = da->x18;
    pos.y = da->x1C;
    pos.z = 0;
    fp->u.mh.x2258 = 0x184;
    ftCh_GrabUnk1_8015BA34(gobj, ftCh_Init_80156198, &pos);
}
