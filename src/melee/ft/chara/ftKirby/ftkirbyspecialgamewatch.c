#include "ftkirbyspecialgamewatch.h"

#include "types.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "ftKirby/ftkirby.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 10CE5C */ static void fn_8010CE5C(Fighter_GObj* gobj);
/* 10CFB0 */ static void fn_8010CFB0(Fighter_GObj* gobj);

void fn_8010CE5C(Fighter_GObj* gobj)
{
    Vec3 vec0;
    Vec3 vec1;

    {
        PAD_STACK(1 * 4);
        {
            int sausageCount[6];
            PAD_STACK(1 * 4);
            {
                Fighter* fp;
                {
                    Fighter* fp2 = GET_FIGHTER(gobj);
                    ftKb_DatAttrs* da = fp2->dat_attrs;
                    PAD_STACK(2 * 4);
                    if (fp2->cmd_vars[0] != 0) {
                        int var_r28;
                        fp2->cmd_vars[0] = var_r28 = 0;

                        if ((float) fp2->mv.kb.specialn_gw.maxSausage <
                            da->specialn_gw_max_sausages_per_use)
                        {
                            fp2->mv.kb.specialn_gw.maxSausage++;

                            vec1.x = 2.5f;
                            vec1.y = 6.5f;
                            vec1.z = 0.0f;

                            lb_8000B1CC(fp2->parts[ftParts_GetBoneIndex(
                                                       fp2, FtPart_LThumbNb)]
                                            .joint,
                                        &vec1, &vec0);

                            {
                                int i;
                                int* pSausage;
                                fp = gobj->user_data;
                                pSausage = sausageCount;
                                for (i = 5, i -= 5; i < 5; i++) {
                                    if (i != fp->fv.kb.xD4 &&
                                        i != fp->fv.kb.xD8)
                                    {
                                        *pSausage++ = i;
                                        var_r28++;
                                    }
                                }
                                {
                                    int temp_r5 =
                                        sausageCount[HSD_Randi(var_r28)];
                                    int var_r6;
                                    fp->fv.kb.xD8 = fp->fv.kb.xD4;
                                    var_r6 = temp_r5;
                                    fp->fv.kb.xD4 = temp_r5;
                                    it_802C837C(gobj, &vec0, 0x9B, var_r6,
                                                fp2->facing_dir);
                                }
                            }
                        }
                        fp2->accessory4_cb = NULL;
                    }
                }
            }
        }
    }
}

void fn_8010CFB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_LThumbNb)].joint,
                NULL, &pos);
    fp->fv.kb.xDC = it_802C74D8(
        gobj, &pos, ftParts_GetBoneIndex(fp, FtPart_LThumbNb), fp->facing_dir);
    if (fp->fv.kb.xDC != NULL) {
        fp->death2_cb = ftKb_Init_800EE74C;
        fp->take_dmg_cb = ftKb_Init_800EE7B8;
    }
    fp->pre_hitlag_cb = fn_8010D100;
    fp->post_hitlag_cb = ftKb_SpecialNGw_8010D130;
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D074(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialNGw_8010D130(gobj);
    fp->fv.kb.xDC = NULL;
}

void ftKb_SpecialNGw_8010D0A8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C760C(fp->fv.kb.xDC);
        ftKb_SpecialNGw_8010D074(gobj);
    }
}

void fn_8010D100(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C7658(fp->fv.kb.xDC);
    }
}

void ftKb_SpecialNGw_8010D130(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C7678(fp->fv.kb.xDC);
    }
}

bool ftKb_SpecialNGw_8010D160(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id >= ftKb_MS_GwSpecialN &&
        fp->motion_id <= ftKb_MS_GwSpecialAirN)
    {
        return false;
    }
    return true;
}

/// #ftGameWatch_SpecialN_SetVars with callback arg
inline void setGwVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.kb.specialn_gw.isChefLoopDisable = false;
    fp->mv.kb.specialn_gw.maxSausage = 0;
    fp->accessory4_cb = fn_8010CFB0;
}

void ftKb_SpecialNGw_8010D188(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0.0F;
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    setGwVars(gobj);
}

void ftKb_SpecialNGw_8010D204(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    setGwVars(gobj);
}

void ftKb_GwSpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x20);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (fp->mv.kb.specialn_gw.maxSausage <
                da->specialn_gw_max_sausages_per_use &&
            !fp->mv.kb.specialn_gw.isChefLoopDisable)
        {
            ftKb_SpecialNGw_8010D660(gobj, da->specialn_gw_frame_on_repeat);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_GwSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x20);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (!fp->mv.kb.specialn_gw.isChefLoopDisable &&
            fp->mv.kb.specialn_gw.maxSausage <
                da->specialn_gw_max_sausages_per_use)
        {
            ftKb_SpecialNGw_8010D6D0(gobj, da->specialn_gw_frame_on_repeat);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_GwSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialn_gw.isChefLoopDisable = true;
    }
    if (fp->cmd_vars[1] != 0 && (fp->input.x668 & HSD_PAD_B) &&
        fp->mv.kb.specialn_gw.maxSausage <
            da->specialn_gw_max_sausages_per_use)
    {
        ftKb_SpecialNGw_8010D660(gobj, da->specialn_gw_frame_on_repeat);
    }
}

void ftKb_GwSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialn_gw.isChefLoopDisable = true;
    }
    if (fp->cmd_vars[1] != 0 && (fp->input.x668 & HSD_PAD_B) &&
        fp->mv.kb.specialn_gw.maxSausage <
            da->specialn_gw_max_sausages_per_use)
    {
        ftKb_SpecialNGw_8010D6D0(gobj, da->specialn_gw_frame_on_repeat);
    }
}

void ftKb_GwSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_GwSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_GwSpecialN_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNGw_8010D580(gobj);
    }
}

void ftKb_GwSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNGw_8010D5F0(gobj);
    }
}

void ftKb_SpecialNGw_8010D580(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0x0C4C508C,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);

    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D5F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0x0C4C508C,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);

    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8010CE5C;
}

static inline void inline1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.kb.specialn_gw.isChefLoopDisable = false;
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D660(Fighter_GObj* gobj, f32 arg1)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0x0C4C508C,
                              arg1 - 1.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    inline1(gobj);
}

void ftKb_SpecialNGw_8010D6D0(Fighter_GObj* gobj, f32 arg1)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0x0C4C508C,
                              arg1 - 1.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    inline1(gobj);
}
