#include "ftPk_SpecialN.h"

#include "types.h"

#include <platform.h>

#include "ef/efsync.h"

#include "forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/inlines.h"
#include "it/kinds/itpikachutjoltground.h"

#include <dolphin/mtx.h>

static void doEnter(Fighter_GObj* gobj, ftPikachu_MotionState msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[ftPk_SpecialN_Cmd0] = fp->cmd_vars[ftPk_SpecialN_Cmd1] =
        fp->cmd_vars[ftPk_SpecialN_Cmd2] = fp->cmd_vars[ftPk_SpecialN_Cmd3] =
            0;
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialN_Enter(Fighter_GObj* gobj)
{
    doEnter(gobj, ftPk_MS_SpecialN);
}

void ftPk_SpecialAirN_Enter(Fighter_GObj* gobj)
{
    doEnter(gobj, ftPk_MS_SpecialAirN);
}

void ftPk_SpecialN_Anim(Fighter_GObj* gobj)
{
    Vec3 pos;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    PAD_STACK(4);

    if (fp->cmd_vars[ftPk_SpecialN_Cmd0] == true) {
        fp->cmd_vars[ftPk_SpecialN_Cmd0] = false;

        if (!fp->cmd_vars[ftPk_SpecialN_Cmd1]) {
            fp->cmd_vars[ftPk_SpecialN_Cmd1] = true;
            pos.x = (fp->x34_scale.y *
                     (pika_attr->specialn_spawn_offset.x * fp->facing_dir)) +
                    fp->cur_pos.x;
            pos.y = (pika_attr->specialn_spawn_offset.y * fp->x34_scale.y) +
                    fp->cur_pos.y;
            pos.z = 0.0f;
            itPikachuThunderJolt_Spawn(gobj, &pos, fp->facing_dir,
                                       pika_attr->specialn_itkind);
            switch (ftLib_GetKind(gobj)) {
            case FTKIND_PIKACHU:
                ft_PlaySFX(fp, 240076, 127, 64);
                break;
            case FTKIND_PICHU:
                ft_PlaySFX(fp, 230067, 127, 64);
                break;
            default:
                break;
            }
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// @todo Shared code with ::ftPk_SpecialAirN_Anim using different attrs
void ftPk_SpecialAirN_Anim(HSD_GObj* gobj)
{
    Vec3 it_pos;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;
    PAD_STACK(4);

    if (fp->cmd_vars[ftPk_SpecialN_Cmd0] == 1) {
        fp->cmd_vars[ftPk_SpecialN_Cmd0] = 0;

        if (!fp->cmd_vars[ftPk_SpecialN_Cmd1]) {
            fp->cmd_vars[ftPk_SpecialN_Cmd1] = 1;
            it_pos.x =
                (fp->x34_scale.y *
                 (pika_attr->specialairn_spawn_offset.x * fp->facing_dir)) +
                fp->cur_pos.x;
            it_pos.y =
                (pika_attr->specialairn_spawn_offset.y * fp->x34_scale.y) +
                fp->cur_pos.y;
            it_pos.z = 0.0f;
            itPikachuThunderJolt_Spawn(gobj, &it_pos, fp->facing_dir,
                                       pika_attr->specialn_itkind);
            switch (ftLib_GetKind(gobj)) {
            case FTKIND_PIKACHU:
                ft_PlaySFX(fp, 240076, 127, 64);
                break;
            case FTKIND_PICHU:
                ft_PlaySFX(fp, 230067, 127, 64);
                break;
            default:
                break;
            }
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (pika_attr->specialairn_landing_lag == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0f,
                          pika_attr->specialairn_landing_lag);
        }
    }
}

void ftPk_SpecialN_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialAirN_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftPk_SpecialN_Coll(HSD_GObj* gobj)
{
    Fighter* fp;
    if (!ft_80082708(gobj)) {
        fp = GET_FIGHTER(gobj);
        ftCommon_GroundToAirStateChange(gobj, fp, ftPk_MS_SpecialAirN,
                                        ftPk_MF_SpecialN_Coll);
    }
}

void ftPk_SpecialAirN_Coll(HSD_GObj* gobj)
{
    Fighter* fp;
    if (ft_80081D0C(gobj) == GA_Air) {
        fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        fp->self_vel.y = 0.0f;
        Fighter_ChangeMotionState(gobj, ftPk_MS_SpecialN,
                                  ftPk_MF_SpecialN_Coll, fp->cur_anim_frame,
                                  1.0f, 0.0f, 0);
    }
}

void ftPk_SpecialN_SpawnEffect0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_GObj* tempObj;
    HSD_GObj* tempObj2;

    if (!fp->x2219_b0) {
        Fighter_Part part = ftParts_GetBoneIndex(fp, FtPart_HipN);
        tempObj = gobj;
        efSync_Spawn(1214, tempObj2 = tempObj, fp->parts[part].joint);
        fp->x2219_b0 = true;
    }
    Fighter_SetEffectHitlagCallbacks(fp);
    fp->accessory4_cb = NULL;
}

/// @todo Shared code with ::ftPk_SpecialN_SpawnEffect0
void ftPk_SpecialN_SpawnEffect1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_GObj* tempObj;
    HSD_GObj* tempObj2;

    if (!fp->x2219_b0) {
        Fighter_Part part = ftParts_GetBoneIndex(fp, FtPart_HipN);
        tempObj = gobj;
        efSync_Spawn(1215, tempObj2 = tempObj, fp->parts[part].joint);
        fp->x2219_b0 = true;
    }
    Fighter_SetEffectHitlagCallbacks(fp);
    fp->accessory4_cb = NULL;
}

void ftPk_SpecialN_80124DC8(HSD_GObj* gobj)
{
    u8 fp_x673;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;
    float pika_attr_1C;

    fp->cmd_vars[ftPk_SpecialN_Cmd0] = 0;
    fp_x673 = fp->x673;

    pika_attr_1C = pika_attr->x1C;
    if (fp_x673 < pika_attr_1C) {
        fp->mv.pk.unk2.x0 = pika_attr->x20;
        fp->x2070.count_thrown_items = 1;
    } else {
        fp->mv.pk.unk2.x0 = 0;
    }
}
