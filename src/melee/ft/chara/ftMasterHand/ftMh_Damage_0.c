#include "ftMh_Damage_0.h"

#include "ftMh_ThrownMasterHand.h"

#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"

bool ftMh_MS_343_80151428(Vec3* vec)
{
    HSD_GObj* gobj = ftBossLib_8015C3E8(27);
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        lb_8000B1CC(fp->parts[FtPart_WaistN].joint, 0, vec);
        return true;
    }
    return false;
}

inline void func_80151484_inline1(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    it_802F046C(fp->mv.mh.unk0.x34);
    it_802F046C(fp->mv.mh.unk0.x38);
    it_802F046C(fp->mv.mh.unk0.x3C);
    it_802F046C(fp->mv.mh.unk0.x40);
    fp->mv.mh.unk0.x34 = 0;
    fp->mv.mh.unk0.x38 = 0;
    fp->mv.mh.unk0.x3C = 0;
    fp->mv.mh.unk0.x40 = 0;
    lbAudioAx_800236B8(fp->mv.mh.unk0.x28);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x2C);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x30);
    if (fp->mv.mh.unk0.x20) {
        ftMh_CaptureWaitMasterHand_80155D1C(fp->victim_gobj);
    }
    fp->self_vel.y = da->x14C;
    fp->self_vel.z = da->x154;
    fp->mv.mh.unk0.x8 = da->x15C;
}

void ftMh_MS_343_80151484(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    func_80151484_inline1(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Damage, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    ft_800881D8(fp, 320023, 127, 64);
    ft_80088148(fp, 320024, 127, 64);
    fp->mv.mh.unk0.x74 = 0;
    fp->mv.mh.unk0.x78 = 0;
}

void ftMh_Damage_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
        if (++fp->mv.mh.unk0.x74 <= da->x144) {
            lbAudioAx_8002438C(530002);
        } else {
            if (++fp->mv.mh.unk0.x78 <= da->x148) {
                lbAudioAx_8002438C(530003);
            }
        }
        fp->cmd_vars[0] = 0;
    }
    if (fp->mv.mh.unk0.x8 > 0 && !ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Damage2, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
    if (--fp->mv.mh.unk0.x8 == 0) {
        ftCo_800D4F24(gobj, 0);
    }
}

void ftMh_MS_345_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] != 0) {
        ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
        if (++fp->mv.mh.unk0.x74 <= da->x144) {
            lbAudioAx_8002438C(530002);
        } else if (++fp->mv.mh.unk0.x78 <= da->x148) {
            lbAudioAx_8002438C(530003);
        }
        fp->cmd_vars[0] = 0;
    }
    if (fp->mv.mh.unk0.x8 > 0 && !ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Damage2, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
    if (--fp->mv.mh.unk0.x8 == 0) {
        ftCo_800D4F24(gobj, 0);
    }
}
