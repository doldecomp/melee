#include "ftGw_AttackLw3.h"

#include "ftGw_Init.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Dash.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Squat.h"
#include "ftCommon/ftCo_SquatWait.h"
#include "ftCommon/ftCo_Turn.h"
#include "ftCommon/ftCo_Walk.h"
#include "ftCommon/ftpickupitem.h"
#include "ftGameWatch/types.h"
#include "it/it_26B1.h"
#include "it/items/it_27CF.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>

static void ftGw_AttackLw3_ItemManholeExitHitlag(HSD_GObj*);
static void ftGw_AttackLw3_ItemManholeEnterHitlag(HSD_GObj*);

/// 0x8014AB48
/// https://decomp.me/scratch/x73Hx // Create Manhole Item
void ftGw_AttackLw3_ItemManholeSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    HSD_GObj* manholeGObj;

    u8 _[4];

    Fighter* fp = getFighter(gobj);

    if (fp->fv.gw.x2250_manholeGObj2 == NULL) {
        lb_8000B1CC(fp->parts[FtPart_LHandNb].joint, NULL, &sp10);
        manholeGObj = fp->item_gobj;
        if (manholeGObj != NULL) {
            fp->fv.gw.x2248_manholeGObj = manholeGObj;
            it_8026BB44(fp->item_gobj);
            it_8026B724(fp->item_gobj);
            ftCommon_8007E6DC(gobj, fp->item_gobj, 1);
        }
        fp->fv.gw.x2250_manholeGObj2 =
            it_802C65E4(gobj, &sp10, FtPart_LHandNb, fp->facing_dir);
    }
    if (fp->fv.gw.x2250_manholeGObj2 != NULL) {
        if (fp->death2_cb == NULL) {
            fp->death2_cb = ftGw_Init_OnDamage;
        }
        if (fp->take_dmg_cb == NULL) {
            fp->take_dmg_cb = ftGw_Init_OnDamage;
        }
    }
    fp->pre_hitlag_cb = ftGw_AttackLw3_ItemManholeEnterHitlag;
    fp->post_hitlag_cb = ftGw_AttackLw3_ItemManholeExitHitlag;
    fp->accessory4_cb = NULL;
}

/// 0x8014AC40
/// https://decomp.me/scratch/JEvaL // Swap item GObj pointers
void ftGw_AttackLw3_ItemManholeRemove(HSD_GObj* gobj)
{
    HSD_GObj* manholeGObj;
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_AttackLw3_ItemManholeExitHitlag(gobj);
    fp->fv.gw.x2250_manholeGObj2 = NULL;
    manholeGObj = fp->fv.gw.x2248_manholeGObj;
    if (manholeGObj != NULL) {
        fp->item_gobj = manholeGObj;
        fp->fv.gw.x2248_manholeGObj = NULL;
        it_8026BB20(fp->item_gobj);
        it_8026B73C(fp->item_gobj);
        ftpickupitem_80094818(gobj, 1);
    }
}

/// 0x8014ACB0
/// https://decomp.me/scratch/09CUB // Remove Manhole on damage
void ftGw_AttackLw3_ItemManholeOnDamage(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = getFighter(gobj);

    if (fp->fv.gw.x2250_manholeGObj2 != NULL) {
        it_802C6718(fp->fv.gw.x2250_manholeGObj2);
        ftGw_AttackLw3_ItemManholeRemove(gobj);
    }
}

/// 0x8014AD38
/// https://decomp.me/scratch/Kw1d3 // Apply hitlag to Manhole item
static void ftGw_AttackLw3_ItemManholeEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x2250_manholeGObj2 != NULL) {
        it_802C6764(fp->fv.gw.x2250_manholeGObj2);
    }
}

/// 0x8014AD68 - Remove hitlag from Manhole item
static void ftGw_AttackLw3_ItemManholeExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x2250_manholeGObj2 != NULL) {
        it_802C6784(fp->fv.gw.x2250_manholeGObj2);
    }
}

/// 0x8014AD98
/// https://decomp.me/scratch/IERdX // Check if Mr. Game & Watch is performing
/// Down Tilt - remove if returns true
bool ftGw_AttackLw3_ItemCheckManholeRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id == ftGw_MS_AttackLw3) {
        return false;
    }
    return true;
}

/// 0x8014ADB8
/// https://decomp.me/scratch/rGgyM // Mr. Game & Watch's Down Tilt Motion State
/// Handler
void ftGw_AttackLw3_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftpickupitem_80094790(gobj) == false) {
        fp->allow_interrupt = 0;
        Fighter_ChangeMotionState(gobj, ftGw_MS_AttackLw3, 0, 0.0f, 1.0f, 0.0f,
                                  NULL);
        ftAnim_8006EBA4(gobj);
        fp->accessory4_cb = ftGw_AttackLw3_ItemManholeSetup;
    }
}

/// 0x8014AE3C
/// https://decomp.me/scratch/h03Ja // Mr. Game & Watch's Down Tilt Animation
/// callback
void ftGw_AttackLw3_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800D638C(gobj);
    }
}

/// Mr. Game & Watch's Down Tilt IASA callback
void ftGw_AttackLw3_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt) {
        RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
        RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
        RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
        RETURN_IF(ftCo_Attack1_CheckInput(gobj));
        RETURN_IF(ftCo_Jump_CheckInput(gobj));
        RETURN_IF(ftCo_Dash_CheckInput(gobj));
        RETURN_IF(ftCo_Squat_CheckInput(gobj));
        RETURN_IF(ftCo_Turn_CheckInput(gobj));
        RETURN_IF(ftCo_Walk_CheckInput(gobj));
    }
}

/// 0x8014AF6C
/// https://decomp.me/scratch/Xp4C5 // Mr. Game & Watch's Down Tilt Physics
/// callback
void ftGw_AttackLw3_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// 0x8014AF8C
/// https://decomp.me/scratch/0stMN // Mr. Game & Watch's Down Tilt Collision
/// callback
void ftGw_AttackLw3_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
    ftGw_Init_8014A538(gobj);
}
