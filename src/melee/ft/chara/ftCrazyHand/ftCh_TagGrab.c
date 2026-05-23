#include "ftCh_TagGrab.h"

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

inline void func_8015ADD0_inline(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    it_802F046C(fp->mv.ch.grab.x28);
    it_802F046C(fp->mv.ch.grab.x2C);
    it_802F046C(fp->mv.ch.grab.x30);
    it_802F046C(fp->mv.ch.grab.x34);
    fp->mv.ch.grab.x28 = NULL;
    fp->mv.ch.grab.x2C = NULL;
    fp->mv.ch.grab.x30 = NULL;
    fp->mv.ch.grab.x34 = NULL;
    lbAudioAx_800236B8(fp->mv.ch.unk0.x38);
    lbAudioAx_800236B8(fp->mv.ch.unk0.x3C);
    lbAudioAx_800236B8(fp->mv.ch.unk0.x40);
    if (fp->mv.ch.unk0.x20) {
        ftCh_GrabUnk1_8015B800(fp->victim_gobj);
    }
    fp->self_vel.y = da->x12C_pos.x;
    fp->self_vel.z = da->x134_pos.x;
    fp->mv.ch.unk0.x8 = (int) da->x13C_pos.x;
}

void ftCh_GrabUnk1_8015ADD0(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    func_8015ADD0_inline(gobj);
    Fighter_ChangeMotionState(gobj, 0x181, 0, 0, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ft_800881D8(fp, 0x4E217, 127, 64);
    ft_PlaySFX(fp, 0x4E219, 127, 64);
    fp->mv.ch.ch_dmg.x60 = 0;
    fp->mv.ch.ch_dmg.x64 = 0;
}

void ftCh_TagGrab_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
        if (++fp->mv.ch.ch_dmg.x60 <= da->x124) {
            lbAudioAx_8002438C(0x81652);
        } else {
            if (++fp->mv.ch.ch_dmg.x64 <= da->x128) {
                lbAudioAx_8002438C(0x81653);
            }
        }
        fp->cmd_vars[0] = 0;
    }
    if (fp->mv.ch.unk0.x8 > 0 && !ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x182, 0, 0, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
    if (--fp->mv.ch.unk0.x8 == 0) {
        ftCo_800D4F24(gobj, 0);
    }
}

void ftCh_TagSqueeze_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
        if (++fp->mv.ch.ch_dmg.x60 <= da->x124) {
            lbAudioAx_8002438C(0x81652);
        } else {
            if (++fp->mv.ch.ch_dmg.x64 <= da->x128) {
                lbAudioAx_8002438C(0x81653);
            }
        }
        fp->cmd_vars[0] = 0;
    }
    if (fp->mv.ch.unk0.x8 > 0 && !ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x182, 0, 0, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
    if (--fp->mv.ch.unk0.x8 == 0) {
        ftCo_800D4F24(gobj, 0);
    }
}

void ftCh_TagGrab_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagGrab_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    fp->self_vel.y += da->x12C_pos.y;
    fp->self_vel.z += da->x134_pos.y;
}

void ftCh_TagGrab_Coll(HSD_GObj* gobj) {}

