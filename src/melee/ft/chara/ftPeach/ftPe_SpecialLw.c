#include "ftPe_SpecialLw.h"

#include "ftPe_Init.h"

#include <platform.h>

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftpickupitem.h"
#include "ftPeach/types.h"

#include "it/forward.h"

#include "it/it_26B1.h"
#include "it/items/itpeachturnip.h"
#include "lb/lb_00B0.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <baselib/random.h>

/* 11CE48 */ static ItemKind pickVeg(HSD_GObj* gobj);
/* 11D018 */ static void spawnVeg(HSD_GObj* gobj);
/* 11D214 */ static void handleAirColl(HSD_GObj* gobj);
/* 11D280 */ static void handleColl(HSD_GObj* gobj);

ItemKind pickVeg(HSD_GObj* gobj)
{
    ftPe_DatAttrs* a = GET_FIGHTER(gobj)->dat_attrs;
    u8 _[8];
    ssize_t randi, idx;
    {
        int odds;
        for (idx = 0, odds = 0; idx < a->speciallw_item_table_count; idx++) {
            odds += a->speciallw_item_table[idx].randi_max;
        }
        randi = HSD_Randi(odds);
    }
    {
        ssize_t randi_max, result;
        for (result = -1, idx = 0,
            randi_max = a->speciallw_item_table[0].randi_max;
             idx < a->speciallw_item_table_count && result == -1; idx++)
        {
            if (randi < randi_max) {
                result = idx;
            }
            randi_max += a->speciallw_item_table[idx + 1].randi_max;
        }
        return a->speciallw_item_table[result].kind;
    }
}

void ftPe_SpecialLw_UnsetVeg(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pe.veg_gobj != NULL) {
        fp->fv.pe.veg_gobj = NULL;
    }
}

void ftPe_SpecialLw_8011CFA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* veg_gobj = fp->fv.pe.veg_gobj;
    if (veg_gobj != NULL) {
        HSD_GObj* item_gobj = fp->item_gobj;
        if (veg_gobj == item_gobj &&
            itGetKind(item_gobj) == It_Kind_Peach_Turnip)
        {
            it_802BD45C(fp->fv.pe.veg_gobj);
            ftPe_SpecialLw_UnsetVeg(gobj);
        }
    }
}

static ItemKind getVeg(HSD_GObj* gobj)
{
    ftPe_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    int da_x14 = da->x14;

    ItemKind kind = It_Kind_Peach_Turnip;
    if (HSD_Randi(da_x14) == 0) {
        kind = pickVeg(gobj);
    }
    return kind;
}

static void setupVeg(ItemKind kind, HSD_GObj* gobj, Fighter* fp, Vec3* pos)
{
    HSD_GObj* veg_gobj =
        it_802BD4AC(gobj, pos, fp->ft_data->x8->x10, kind, fp->facing_dir);
    fp->item_gobj = veg_gobj;
    fp->fv.pe.veg_gobj = veg_gobj;
    if (veg_gobj != NULL) {
        ftpickupitem_80094818(gobj, false);
        efSync_Spawn(1234, gobj, &fp->cur_pos);
        fp->death2_cb = ftPe_Init_OnDeath2;
        fp->take_dmg_cb = ftPe_Init_OnDeath2;
    }
}

static void spawnVeg(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    Vec3 p1;
    Vec3 p2;

    if (ftCheckThrowB0(fp)) {
        ItemKind kind;

        lb_8000B1CC(fp->parts[FtPart_109].joint, NULL, &pos);
        kind = getVeg(gobj);
        setupVeg(kind, gobj, fp, &pos);
    }
}

static bool throwVegIfHeld(HSD_GObj* gobj, FtMotionId msid)
{
    HSD_GObj* igobj = GET_FIGHTER(gobj)->item_gobj;
    if (igobj != NULL) {
        if (itGetKind(igobj) == It_Kind_Peach_Turnip) {
            ftCo_800957F4(gobj, msid);
        }
        return true;
    } else {
        return false;
    }
}

void ftPe_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (throwVegIfHeld(gobj, ftCo_MS_LightThrowF4) != true) {
        fp->throw_flags = 0;
        Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialLw, Ft_MF_None, 0, 1, 0,
                                  NULL);
        ftAnim_8006EBA4(gobj);
        fp->accessory4_cb = spawnVeg;
    }
}

void ftPe_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    throwVegIfHeld(gobj, ftCo_MS_LightThrowAirF4);
}

static MotionFlags const coll_mf = Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
                                   Ft_MF_UpdateCmd | Ft_MF_SkipItemVis |
                                   Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
                                   Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static void handleAirColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirLw, coll_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    fp->accessory4_cb = spawnVeg;
}

static void handleColl(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialLw, coll_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    fp->accessory4_cb = spawnVeg;
}

static void doAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
        ftPe_SpecialLw_UnsetVeg(gobj);
    }
}

void ftPe_SpecialLw_Anim(HSD_GObj* gobj)
{
    u8 _[4];
    doAnim(gobj, ft_8008A2BC);
}

void ftPe_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    doAnim(gobj, ftCo_Fall_Enter);
}

void ftPe_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPe_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPe_SpecialLw_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, handleAirColl);
}

void ftPe_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, handleColl);
}
