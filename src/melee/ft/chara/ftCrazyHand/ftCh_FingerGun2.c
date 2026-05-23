#include "ftCh_FingerGun2.h"

#include "ftCh_Init.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_BackAirplane1.h"
#include "ftCrazyHand/ftCh_FingerBeam.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_GrabUnk1_8015ABD0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x16D, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.xC.x = da->xCC_pos.y;
    fp->mv.ch.unk0.xC.y = da->xD4;
    fp->mv.ch.unk0.xC.z = 0.0f;
}

void ftCh_GrabUnk1_8015AC50(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x16E, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.xC.x = da->x18;
    fp->mv.ch.unk0.xC.y = da->x1C;
    fp->mv.ch.unk0.xC.z = 0.0f;
}

static void ftCh_FingerGun2_Anim_inline(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.ch.unk0.x20 == 1) {
        ftCh_Init_801592D4(gobj);
    } else {
        ftCh_Init_80158F34(gobj);
    }
}

static void ftCh_FingerGun2_Anim_inline2(HSD_GObj* gobj)
{
    ftCh_FingerGun2_Anim_inline(gobj);
}

void ftCh_FingerGun2_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCh_FingerGun2_Anim_inline2(gobj);
    }
}

void ftCh_FingerGun2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerGun2_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_FingerGun2_Coll(HSD_GObj* gobj) {}
