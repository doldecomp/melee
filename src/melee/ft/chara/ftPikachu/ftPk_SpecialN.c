#include <platform.h>

#include "ftPk_SpecialN.h"

#include "types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "it/items/itpikachutjoltground.h"

#include <dolphin/mtx/types.h>

void ftPk_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 341, 0, 0.0f, 1.0f, 0.0f, 0);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 342, 0, 0.0f, 1.0f, 0.0f, 0);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialN_Anim(HSD_GObj* gobj)
{
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    u8 _[4];

    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 0;

        if (!fp->cmd_vars[1]) {
            fp->cmd_vars[1] = 1;
            sp14.x = (fp->x34_scale.y * (pika_attr->x0 * fp->facing_dir)) +
                     fp->cur_pos.x;
            sp14.y = (pika_attr->x4 * fp->x34_scale.y) + fp->cur_pos.y;
            sp14.z = 0.0f;
            it_802B338C(gobj, &sp14, fp->facing_dir, pika_attr->x14);
            switch (ftLib_800872A4(gobj)) {
            case 12:
                ft_80088148(fp, 240076, 127, 64);
                break;
            case 23:
                ft_80088148(fp, 230067, 127, 64);
                break;
            }
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPk_SpecialAirN_Anim(HSD_GObj* gobj)
{
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    u8 _[4];

    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 0;

        if (!fp->cmd_vars[1]) {
            fp->cmd_vars[1] = 1;
            sp14.x = (fp->x34_scale.y * (pika_attr->x8 * fp->facing_dir)) +
                     fp->cur_pos.x;
            sp14.y = (pika_attr->xC * fp->x34_scale.y) + fp->cur_pos.y;
            sp14.z = 0.0f;
            it_802B338C(gobj, &sp14, fp->facing_dir, pika_attr->x14);
            switch (ftLib_800872A4(gobj)) {
            case 12:
                ft_80088148(fp, 240076, 127, 64);
                break;
            case 23:
                ft_80088148(fp, 230067, 127, 64);
                break;
            }
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (0.0f == pika_attr->x10) {
            ftCo_800CC730(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0f, pika_attr->x10);
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
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 342, 206327938, fp->cur_anim_frame,
                                  1.0f, 0.0f, 0);
    }
}

void ftPk_SpecialAirN_Coll(HSD_GObj* gobj)
{
    Fighter* fp;
    if (ft_80081D0C(gobj) == 1) {
        fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        fp->self_vel.y = 0.0f;
        Fighter_ChangeMotionState(gobj, 341, 206327938, fp->cur_anim_frame,
                                  1.0f, 0.0f, 0);
    }
}

void ftPk_SpecialN_SpawnEffect0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_GObj* tempObj;
    HSD_GObj* tempObj2;

    if (!fp->x2219_b0) {
        Fighter_Part part = ftParts_8007500C(fp, FtPart_HipN);
        tempObj = gobj;
        efSync_Spawn(1214, tempObj2 = tempObj, fp->parts[part].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftPk_SpecialN_SpawnEffect1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_GObj* tempObj;
    HSD_GObj* tempObj2;

    if (!fp->x2219_b0) {
        Fighter_Part part = ftParts_8007500C(fp, FtPart_HipN);
        tempObj = gobj;
        efSync_Spawn(1215, tempObj2 = tempObj, fp->parts[part].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftPk_SpecialN_80124DC8(HSD_GObj* gobj)
{
    u8 fighter_x673_byte;
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;
    float pika_attr_1C;

    fp->cmd_vars[0] = 0;
    fighter_x673_byte = fp->x673;

    pika_attr_1C = pika_attr->x1C;
    if (fighter_x673_byte < pika_attr_1C) {
        fp->mv.pk.unk2.x0 = pika_attr->x20;
        fp->x2070.x2072_b4 = 1;
    } else {
        fp->mv.pk.unk2.x0 = 0;
    }
}
