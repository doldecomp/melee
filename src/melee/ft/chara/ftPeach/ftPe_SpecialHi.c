#include "ftPe_SpecialHi.h"

#include "ftPe_Init.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_ItemParasolOpen.h"
#include "ftCommon/ftpickupitem.h"
#include "ftPeach/types.h"

#include "it/forward.h"

#include "it/it_26B1.h"
#include "lb/lb_00B0.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <math.h>
#include <dolphin/mtx.h>
#include <melee/it/items/itpeachparasol.h>

/* 11D424 */ static void ftPe_SpecialHi_8011D424(HSD_GObj* gobj);
/* 11D598 */ static void ftPe_SpecialHi_8011DD8C(HSD_GObj* gobj);
/* 11D620 */ static void ftPe_SpecialHi_8011D620(HSD_GObj* gobj);
/* 11D650 */ static void ftPe_SpecialHi_8011D650(HSD_GObj* gobj);
/* 11E064 */ static void ftPe_SpecialHi_8011E064(HSD_GObj* gobj);

void ftPe_SpecialHi_8011D424(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.pe.specialhi.kind == It_Kind_Capsule) {
        fp->mv.pe.specialhi.kind = It_Kind_Peach_Parasol;
        if (fp->fv.pe.parasol_gobj_0 == NULL) {
            Vec3 pos;
            lb_8000B1CC(fp->parts[FtPart_109].joint, NULL, &pos);
            {
                HSD_GObj* igobj = fp->item_gobj;
                if (igobj != NULL) {
                    fp->fv.pe.parasol_gobj_1 = igobj;
                    it_8026BB44(fp->item_gobj);
                    it_8026B724(fp->item_gobj);
                    ftCommon_8007E6DC(gobj, fp->item_gobj, true);
                }
            }
            fp->fv.pe.parasol_gobj_0 =
                it_802BDA64(gobj, &pos, FtPart_109, fp->facing_dir);
            fp->item_gobj = fp->fv.pe.parasol_gobj_0;
            if (fp->fv.pe.parasol_gobj_0 != NULL) {
                fp->death3_cb = ftPe_Init_OnDeath2;
                fp->take_dmg_cb = ftPe_Init_OnDeath2;
            }
        }
    }
    fp->accessory4_cb = NULL;
    fp->pre_hitlag_cb = ftPe_SpecialHi_8011D620;
    fp->post_hitlag_cb = ftPe_SpecialHi_8011D650;
}

bool ftPe_8011D518(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.pe.parasol_gobj_0 = NULL;
    fp->death3_cb = NULL;
    fp->take_dmg_cb = NULL;
    {
        HSD_GObj* parasol_gobj = fp->fv.pe.parasol_gobj_1;
        if (parasol_gobj != NULL) {
            fp->item_gobj = parasol_gobj;
            fp->fv.pe.parasol_gobj_1 = NULL;
            it_8026BB20(fp->item_gobj);
            it_8026B73C(fp->item_gobj);
            ftpickupitem_80094818(gobj, true);
            return true;
        }
    }
    return false;
}

static void setupParasol(HSD_GObj* gobj)
{
    ftPe_8011D518(gobj);
}

/// @todo Can maybe use #ensureUnkItem?
void ftPe_8011D598(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pe.parasol_gobj_0 != NULL) {
        it_802BDB94(fp->fv.pe.parasol_gobj_0);
        ftPe_8011D518(gobj);
    }
}

static void ensureUnkItem(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pe.parasol_gobj_0 != NULL) {
        cb(fp->fv.pe.parasol_gobj_0);
    }
}

void ftPe_SpecialHi_8011D620(HSD_GObj* gobj)
{
    ensureUnkItem(gobj, it_802BDBF8);
}

void ftPe_SpecialHi_8011D650(HSD_GObj* gobj)
{
    ensureUnkItem(gobj, it_802BDC18);
}

static bool notUsingParasol(Fighter* fp)
{
    FtMotionId msid = fp->motion_id;
    if (msid >= ftPe_MS_ItemParasolOpen && msid <= ftPe_MS_ItemParasolFall) {
        return false;
    }
    if (msid >= ftCo_MS_ItemParasolOpen &&
        msid <= ftCo_MS_ItemParasolFallSpecial)
    {
        return false;
    }
    if (msid >= ftCo_MS_FallSpecial && msid <= ftCo_MS_FallSpecialB) {
        return false;
    }
    if (msid == ftCo_MS_LandingFallSpecial && !it_802BDC38(fp->item_gobj)) {
        return false;
    }
    return true;
}

bool ftPe_SpecialHi_NotActive(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = fp->motion_id;
    if (msid >= ftPe_MS_SpecialHiStart && msid <= ftPe_MS_SpecialAirHiEnd) {
        return false;
    }
    return notUsingParasol(fp);
}

static void doEnter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = 0;
    fp->throw_flags = 0;
    fp->mv.pe.specialhi.kind = It_Kind_Capsule;
    fp->x2222_b2 = true;
    {
        HSD_GObj* igobj = fp->item_gobj;
        if (igobj != NULL) {
            if (itGetKind(igobj) == It_Kind_Parasol) {
                fp->mv.pe.specialhi.kind = It_Kind_Parasol;
                return;
            }
            if (itGetKind(fp->item_gobj) == It_Kind_Peach_Parasol) {
                fp->mv.pe.specialhi.kind = It_Kind_Peach_Parasol;
                return;
            }
        }
    }
    fp->accessory4_cb = ftPe_SpecialHi_8011D424;
}

void ftPe_SpecialHi_Enter(HSD_GObj* gobj)
{
    u8 _[16];
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialHiStart, FtMoveId_None, 0,
                              1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    doEnter(gobj);
}

void ftPe_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->self_vel.y = 0;
    fp->self_vel.x *= da->x84;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirHiStart, FtMoveId_None,
                              0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    doEnter(gobj);
}

static bool checkCmdVar2(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[2] == 0) {
        return false;
    }
    fp->cmd_vars[2] = 0;
    return false;
}

void ftPe_SpecialHiStart_Anim(HSD_GObj* gobj)
{
    u8 _[16];
    if (!checkCmdVar2(gobj) && !ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftPe_DatAttrs* da = fp->dat_attrs;
        if (fp->mv.pe.specialhi.kind == It_Kind_Parasol) {
            fp->motion_id = ftCo_MS_FallSpecial;
            ftCo_800CEFE0(gobj, p_ftCommonData->x59C);
        } else {
            fp->motion_id = ftCo_MS_FallSpecial;
            ftCo_800CEFE0(gobj, da->x90);
        }
    }
}

void ftPe_SpecialAirHiStart_Anim(HSD_GObj* gobj)
{
    u8 _[16];
    ftPe_SpecialHiStart_Anim(gobj);
}

void ftPe_SpecialHiStart_IASA(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftPe_DatAttrs* da = fp->dat_attrs;
    float abs_lstick_x = ABS(fp->input.lstick.x);
    if (!fp->cmd_vars[0] && abs_lstick_x > da->x7C) {
        float deg = da->x80 * ((abs_lstick_x - da->x7C) / (1.0 - da->x7C));
        float rad =
            fp->input.lstick.x > 0 ? -(deg * deg_to_rad) : +(deg * deg_to_rad);
        float abs_lstick_angle = ABS(fp->lstick_angle);
        if (ABS(rad) > abs_lstick_angle) {
            fp->lstick_angle = rad;
        }
    }
    if (ftCheckThrowB3(fp) && ABS(fp->input.lstick.x) > da->x78) {
        ftCommon_8007D9FC(fp);
        ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
    }
}

void ftPe_SpecialAirHiStart_IASA(HSD_GObj* gobj)
{
    u8 _[8];
    ftPe_SpecialHiStart_IASA(gobj);
}

void ftPe_SpecialHiStart_Phys(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->ground_or_air == GA_Air) {
        ft_80085154(gobj);
    } else {
        ft_80084FA8(gobj);
    }
}

void ftPe_SpecialAirHiStart_Phys(HSD_GObj* gobj)
{
    u8 _[4];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca = &fp->co_attrs;
    if (fp->cmd_vars[0]) {
        ft_80085154(gobj);
        fp->self_vel.x = fp->self_vel.x * da->x8C;
        fp->self_vel.y = fp->self_vel.y * da->x8C;
        fp->self_vel.z = fp->self_vel.z * da->x8C;
    } else {
        ftCommon_8007D494(fp, da->x88, ca->terminal_vel);
        ftCommon_8007CF58(fp);
    }
}

static void ftPe_SpecialHi_8011DD8C(HSD_GObj* gobj)
{
    ftPe_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    ftCo_LandingFallSpecial_Enter(gobj, false, da->x74);
}

static void doColl(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (!fp->cmd_vars[0] || fp->self_vel.y >= 0) {
            ft_80083B68(gobj);
            return;
        }
        ft_800831CC(gobj, ftCo_80096CC8, cb);
        return;
    }
    ft_80084104(gobj);
}

void ftPe_SpecialHiStart_Coll(HSD_GObj* gobj)
{
    doColl(gobj, ftPe_SpecialHi_8011DD8C);
}

void ftPe_SpecialAirHiStart_Coll(HSD_GObj* gobj)
{
    doColl(gobj, ftPe_SpecialHi_8011DD8C);
}

void ftPe_SpecialHiEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, 0, da->x70, da->x74);
    }
}

void ftPe_SpecialAirHiEnd_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    ftPe_SpecialHiEnd_Anim(gobj);
}

void ftPe_SpecialHiEnd_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialAirHiEnd_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialHiEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* ca = &fp->co_attrs;
    if (fp->ground_or_air == GA_Air) {
        float vel_y = fp->self_vel.y;
        ft_80085154(gobj);
        fp->self_vel.y = vel_y;
        ftCommon_8007D494(fp, ca->grav, ca->terminal_vel);
    } else {
        ft_80084FA8(gobj);
    }
}

void ftPe_SpecialAirHiEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* ca = &fp->co_attrs;
    ftPe_DatAttrs* da = fp->dat_attrs;
    float vel_y = fp->self_vel.y;
    ft_80085154(gobj);
    fp->self_vel.x *= da->x8C;
    fp->self_vel.y *= da->x8C;
    fp->self_vel.z *= da->x8C;
    fp->self_vel.y = vel_y;
    ftCommon_8007D494(fp, ca->grav, ca->terminal_vel);
}

void ftPe_SpecialHi_8011E064(HSD_GObj* gobj)
{
    ftPe_SpecialHi_8011DD8C(gobj);
}

void ftPe_SpecialHiEnd_Coll(HSD_GObj* gobj)
{
    doColl(gobj, ftPe_SpecialHi_8011E064);
}

void ftPe_SpecialAirHiEnd_Coll(HSD_GObj* gobj)
{
    doColl(gobj, ftPe_SpecialHi_8011E064);
}
