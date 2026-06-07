#include "ftkirbyspecialdonkey.h"

#include "ftKb_Init.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Escape.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include <common_structs.h>
#include <stddef.h>
#include <trigf.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/// @todo This is some kind of inline within #ftKb_DkSpecialN_Anim that's
///       shared by #ftKb_DkSpecialAirN_Anim
static double sdata2_order0(void)
{
    return S32_TO_F32;
}

void ftKb_SpecialNDk_800FF8EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->fv.kb.xBC == da->specialn_dk_swings_to_full_charge) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNFull, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 1;
        fp->mv.dk.specialn.xC = fp->fv.kb.xBC;
        fp->fv.kb.xBC = 0;
    } else {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNStart, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 0;
        fp->mv.dk.specialn.xC = 0;
    }
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.dk.specialn.x0 = 0;
    fp->mv.dk.specialn.x4 = 0;
    fp->mv.dk.specialn.x14 = -1;
    fp->mv.dk.specialn.x10 = -1;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0;
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        fp2->pre_hitlag_cb = efLib_PauseAll;
        fp2->post_hitlag_cb = efLib_ResumeAll;
    }
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNDk_800FFA10(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->fv.kb.xBC == da->specialn_dk_swings_to_full_charge) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNFull, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 1;
        fp->mv.dk.specialn.xC = fp->fv.kb.xBC;
        fp->fv.kb.xBC = 0;
    } else {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNStart, 0, 0, 1, 0,
                                  NULL);
        fp->mv.dk.specialn.x8 = 0;
        fp->mv.dk.specialn.xC = 0;
    }
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.dk.specialn.x0 = 0;
    fp->mv.dk.specialn.x4 = 0;
    fp->mv.dk.specialn.x14 = -1;
    fp->mv.dk.specialn.x10 = -1;
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        fp2->pre_hitlag_cb = efLib_PauseAll;
        fp2->post_hitlag_cb = efLib_ResumeAll;
    }
    ftAnim_8006EBA4(gobj);
}

static inline void ftKb_DkSpecialNStart_Coll_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftKb_DkSpecialNStart_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNLoop, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    volatile unsigned short pad;
    if (fp->cur_anim_frame == 0.0F) {
        fp->fv.kb.xBC += 1;
        if (fp->fv.kb.xBC >= da->specialn_dk_swings_to_full_charge) {
            Fighter* fighter2 = fp;
            ftCo_800BFFD0(fighter2, 58, 0);
            fp->fv.kb.xBC = da->specialn_dk_swings_to_full_charge;
            {
                Fighter* fp2 = gobj->user_data;
                fp2->pre_hitlag_cb = NULL;
                fp2->post_hitlag_cb = NULL;
            }
            ft_8008A2BC(gobj);
        }
    }
}

void ftKb_DkSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
        ft_8008A2BC(gobj);
    }
}

void ftKb_DkSpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(24);
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1194, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1193, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->mv.dk.specialn.x4 == 0) {
            fp->mv.dk.specialn.x4 = 1;
        }
        if (fp->mv.dk.specialn.x10 == -1) {
            fp->mv.dk.specialn.x10 = (s32) fp->x914[0].damage;
        }
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.dk.specialn.x10 +
                            (fp->mv.dk.specialn.xC *
                             da->specialn_dk_damage_increase_per_swing),
                        gobj);
        if (fp->mv.dk.specialn.x14 == -1) {
            fp->mv.dk.specialn.x14 = (s32) fp->x914[1].damage;
        }
        ftColl_8007ABD0(&fp->x914[1],
                        fp->mv.dk.specialn.x14 +
                            (fp->mv.dk.specialn.xC *
                             da->specialn_dk_damage_increase_per_swing),
                        gobj);
    }
    if (fp->mv.dk.specialn.x4 == 1) {
        fp->mv.dk.specialn.x4 = 2;
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            ftKb_DatAttrs* da2 = fp2->dat_attrs;
            fp2->gr_vel =
                fp2->facing_dir *
                (da2->specialn_dk_grounded_punch_horizontal_velocity *
                 fp2->mv.dk.specialn.xC);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        {
            Fighter* fp2 = gobj->user_data;
            fp2->pre_hitlag_cb = NULL;
            fp2->post_hitlag_cb = NULL;
        }
        ft_8008A2BC(gobj);
    }
}

void ftKb_DkSpecialNFull_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[32];
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1194, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1193, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled &&
        (fp->mv.dk.specialn.x4 == 0))
    {
        fp->mv.dk.specialn.x4 = 1;
    }
    if (fp->mv.dk.specialn.x4 == 1) {
        fp->mv.dk.specialn.x4 = 2;
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            ftKb_DatAttrs* da2 = fp2->dat_attrs;
            fp2->gr_vel =
                fp2->facing_dir *
                (da2->specialn_dk_grounded_punch_horizontal_velocity *
                 fp2->mv.dk.specialn.xC);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        {
            Fighter* fp2 = gobj->user_data;
            fp2->pre_hitlag_cb = NULL;
            fp2->post_hitlag_cb = NULL;
        }
        ft_8008A2BC(gobj);
    }
}

void ftKb_DkSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNLoop, 0, 0.0F,
                                  1.0F, 0.0F, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->cur_anim_frame == 0.0F) {
        new_var = da;
        fp->fv.kb.xBC += 1;
        if (fp->fv.kb.xBC >= new_var->specialn_dk_swings_to_full_charge) {
            Fighter* fighter2 = fp;
            ftCo_800BFFD0(fighter2, 58, 0);
            fp->fv.kb.xBC = new_var->specialn_dk_swings_to_full_charge;
            {
                Fighter* fp2 = gobj->user_data;
                fp2->pre_hitlag_cb = NULL;
                fp2->post_hitlag_cb = NULL;
            }
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftKb_DkSpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    u8 _[16];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_DkSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1194, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1193, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (fp->x914[0].state != HitCapsule_Disabled) {
        if (fp->mv.dk.specialn.x10 == -1) {
            fp->mv.dk.specialn.x10 = (s32) fp->x914[0].damage;
        }
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.dk.specialn.x10 +
                            (fp->mv.dk.specialn.xC *
                             da->specialn_dk_damage_increase_per_swing),
                        gobj);
        if (fp->mv.dk.specialn.x14 == -1) {
            fp->mv.dk.specialn.x14 = (s32) fp->x914[1].damage;
        }
        ftColl_8007ABD0(&fp->x914[1],
                        fp->mv.dk.specialn.x14 +
                            (fp->mv.dk.specialn.xC *
                             da->specialn_dk_damage_increase_per_swing),
                        gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        {
            Fighter* fp2 = gobj->user_data;
            fp2->pre_hitlag_cb = NULL;
            fp2->post_hitlag_cb = NULL;
        }
        if (da->specialn_dk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_dk_freefall_toggle);
        }
    }
}

void ftKb_DkSpecialAirNFull_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->cmd_vars[0]) {
        if (fp->mv.dk.specialn.x8 == 0) {
            fp->mv.dk.specialn.x8++;
        }
    }
    if (fp->mv.dk.specialn.x8 == 1) {
        fp->mv.dk.specialn.x8++;
        if (fp->ground_or_air == GA_Air) {
            efSync_Spawn(1194, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        } else {
            efSync_Spawn(1193, gobj, fp->parts[FtPart_TopN].joint,
                         &fp->facing_dir);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xBC = 0;
        {
            Fighter* fp2 = gobj->user_data;
            fp2->pre_hitlag_cb = NULL;
            fp2->post_hitlag_cb = NULL;
        }
        if (da->specialn_dk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_dk_freefall_toggle);
        }
    }
}

void ftKb_DkSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftCo_8009917C(gobj)) {
        if (fp->input.x668 & HSD_PAD_B) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialN, 0, 0.0F, 1.0F,
                                      0.0F, NULL);
            new_var = fp;
            new_var->mv.dk.specialn.xC = fp->fv.kb.xBC;
            fp->fv.kb.xBC = 0;
            ftKb_DkSpecialNStart_Coll_inline(gobj);
            ftAnim_8006EBA4(gobj);
        }
        if (fp->input.x668 & HSD_PAD_LR) {
            fp->mv.dk.specialn.x0 = 1;
        }
        if (fp->cur_anim_frame == 0.0F && fp->mv.dk.specialn.x0) {
            Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNCancel, 0, 0.0F,
                                      1.0F, 0.0F, NULL);
            ftKb_DkSpecialNStart_Coll_inline(gobj);
        }
    }
}

void ftKb_DkSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNFull_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    new_var = fp;
    if (fp->input.x668 & HSD_PAD_B) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirN, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
        fp->mv.dk.specialn.xC = fp->fv.kb.xBC;
        fp->fv.kb.xBC = 0;
        ftKb_DkSpecialNStart_Coll_inline(gobj);
        ftAnim_8006EBA4(gobj);
    }
    if (fp->input.x668 & HSD_PAD_LR) {
        fp->mv.dk.specialn.x0 = 1;
    }
    if (new_var->cur_anim_frame == 0.0F && fp->mv.dk.specialn.x0) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNCancel, 0, 0.0F,
                                  1.0F, 0.0F, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialAirNFull_IASA(Fighter_GObj* gobj) {}

void ftKb_DkSpecialNStart_Phys(Fighter_GObj* gobj)

{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialNFull_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_DkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialAirNFull_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_DkSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNStart,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNLoop, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNCancel,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_800827A0(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirN, 0x0C4D508EU,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_800827A0(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialAirNFull, 0x0C4D508EU,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNLoop, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNCancel, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialN, 0x0C4D508EU,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_DkSpecialAirNFull_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_DkSpecialNFull, 0x0C4D508EU,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_DkSpecialNStart_Coll_inline(gobj);
    }
}

void ftKb_SpecialNPr_80100DE0(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ft->fv.kb.xBC = 0;
    efLib_DestroyAll(gobj);
}
