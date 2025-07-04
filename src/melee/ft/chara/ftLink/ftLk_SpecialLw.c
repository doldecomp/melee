#include <platform.h>

#include "ftLink/forward.h"
#include "it/forward.h"
#include <baselib/forward.h>

#include "ftLk_SpecialLw.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftpickupitem.h"
#include "it/it_26B1.h"
#include "it/items/it_27CF.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>

/* 0EB75C */ static bool updateBomb(HSD_GObj* gobj, FtMotionId msid);
/* 0EB7C8 */ static void spawnBomb(HSD_GObj* gobj);

static void doEnter(HSD_GObj* gobj, FtMotionId msid0, FtMotionId msid1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (updateBomb(gobj, msid0) != true) {
        fp->throw_flags = 0;
        Fighter_ChangeMotionState(gobj, msid1, Ft_MF_None, 0, 1, 0, NULL);
        ftAnim_8006EBA4(gobj);
        fp->accessory4_cb = spawnBomb;
    }
}

void ftLk_SpecialLw_Enter(HSD_GObj* gobj)
{
    doEnter(gobj, 108, ftLk_MS_SpecialLw);
}

void ftLk_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    doEnter(gobj, 112, ftLk_MS_SpecialAirLw);
}

static bool updateBomb(HSD_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL) {
        u32 bomb_kind = itGetKind(fp->item_gobj) - It_Kind_Link_Bomb;
        if (bomb_kind <= 1) {
            ftCo_800957F4(gobj, msid);
        }
        return true;
    }
    return false;
}

static void spawnBomb(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (ftCheckThrowB0(fp)) {
        Vec3 pos;
        u8 _[4];
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                    NULL, &pos);
        {
            Fighter_Part part = da->x48;
            float facing_dir = fp->facing_dir;
            HSD_GObj* igobj = it_8029DD58(gobj, &pos, fp->ft_data->x8->x10,
                                          part, facing_dir);
            fp->item_gobj = igobj;
            ftParts_80074A4C(gobj, 2, 1);
            if (igobj != NULL) {
                ftpickupitem_80094818(gobj, 1);
            }
        }
    }
}

static void doAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    u8 _[8] = { 0 };
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftLk_SpecialLw_Anim(HSD_GObj* gobj)
{
    doAnim(gobj, ft_8008A2BC);
}

void ftLk_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    doAnim(gobj, ftCo_800CC730);
}

void ftLk_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

static MotionFlags const coll_mf = Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
                                   Ft_MF_UpdateCmd | Ft_MF_SkipItemVis |
                                   Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
                                   Ft_MF_SkipModelFlags | Ft_MF_Unk27;

/// @todo Verify MSID.
void ftLk_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirLw, coll_mf,
                                  fp->cur_anim_frame, 1, 0, NULL);
        fp->accessory4_cb = spawnBomb;
    }
}

/// @todo Verify MSID.
void ftLk_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialLw, coll_mf,
                                  fp->cur_anim_frame, 1, 0, NULL);
        fp->accessory4_cb = spawnBomb;
    }
}
