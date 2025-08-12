#include "ftCo_HammerWait.h"

#include "ftCo_0C60.h"
#include "ftCo_HammerFall.h"
#include "ftCo_HammerJump.h"
#include "ftCo_HammerTurn.h"
#include "ftCo_HammerWalk.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdevice.h"
#include "ft/types.h"

#include "it/forward.h"

#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/ithammer.h"
#include "pl/plbonuslib.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 0C5408 */ static void ftCo_800C5408(Fighter* fp);
/* 0C5588 */ static void ftCo_800C5588(Fighter* fp);

bool ftCo_800C4E4C(Fighter_GObj* gobj)
{
    if (ft_8008A1FC(gobj)) {
        ftCo_800C4ED8(gobj);
        return true;
    }
    return false;
}

void ftCo_800C4E94(Fighter* fp)
{
    ftCo_800C5408(fp);
    ftCo_800C5588(fp);
    ftCommon_8007EBAC(fp, 1, 0);
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 flags = ftCo_800C54C4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_HammerWait, flags,
                              ftCo_800C548C(fp), 1, 0, NULL);
    ftCo_800C4E94(fp);
}

void ftCo_800C4ED8(Fighter_GObj* gobj)
{
    inlineA0(gobj);
}

static inline void inlineB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2338.x != 0) {
        ftColl_8007AFF8(gobj);
    } else if (fp->cur_anim_frame >= 0 &&
               fp->cur_anim_frame < fp->frame_speed_mul)
    {
        ft_800892A0(gobj);
        ft_80089824(gobj);
        it_8027B070(fp->item_gobj, gobj);
    }
}

void ftCo_800C4F64(Fighter_GObj* gobj)
{
    inlineB0(gobj);
}

void ftCo_HammerWait_Anim(Fighter_GObj* gobj)
{
    inlineB0(gobj);
}

void ftCo_HammerWait_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_800C5A50(gobj));
    RETURN_IF(ftCo_800C60C8(gobj));
    RETURN_IF(ftCo_800C576C(gobj));
    RETURN_IF(ftCo_800C55CC(gobj));
}

void ftCo_HammerWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_HammerWait_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_800C5D34);
}

void ftCo_800C511C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id != ftCo_MS_LightGet) {
        if (fp->x2330.x != 0) {
            --fp->x2330.x;
        }
        if (fp->x2330.y != 0 && ftCo_800C53E4(fp)) {
            --fp->x2330.y;
            if (fp->x2330.y == 0) {
                fp->x2338.x = 1;
                it_80293E34(fp->item_gobj);
                ftCommon_8007ECD4(fp, true);
            }
        }
        if (fp->x2330.x == 0) {
            bool b = false;
            Item_8026A8EC(fp->item_gobj);
            ft_80088110(fp);
            if (ftCo_800C0694(fp) == 106) {
                b = true;
            }
            if (ftCo_800C53E4(fp)) {
                ftCommon_8007D92C(gobj);
            }
            if (b) {
                ftCo_800C0200(fp, 106);
            }
        }
        if (fp->x2338.y != 0) {
            --fp->x2338.y;
        }
    }
}

bool ftCo_800C5240(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL && itGetKind(fp->item_gobj) == It_Kind_Hammer) {
        return true;
    }
    return false;
}

void ftCo_800C5284(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2330.x = p_ftCommonData->x6AC;
    fp->x2330.y = it_80293DCC(fp->item_gobj);
    fp->x2338.x = 0;
    fp->x2338.y = 0;
    if (fp->x2330.y != 0) {
        pl_800403C0(fp->player_id, fp->x221F_b4);
    }
    ft_800880AC(fp);
}

void ftCo_800C52F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800C5284(gobj);
    if (fp->ground_or_air == GA_Ground) {
        inlineA0(gobj);
    } else {
        ftCo_800C5D34(gobj);
    }
}

bool ftCo_800C53E4(Fighter* fp)
{
    if (fp->motion_id >= ftCo_MS_HammerWait &&
        fp->motion_id <= ftCo_MS_HammerLanding)
    {
        return true;
    }
    return false;
}

void ftCo_800C5408(Fighter* fp)
{
    if (ftCo_800C0694(fp) != 106) {
        ftCo_800BFFD0(fp, 106, false);
    }
}

void ftCo_800C544C(Fighter* fp)
{
    if (ftCo_800C0694(fp) == 106) {
        ftCo_800C0200(fp, 106);
    }
}

float ftCo_800C548C(Fighter* fp)
{
    return ftCo_800C53E4(fp) ? fp->cur_anim_frame : 0;
}

u32 ftCo_800C54C4(Fighter* fp)
{
    return ftCo_800C53E4(fp)
               ? Ft_MF_SkipHit | Ft_MF_SkipModel | Ft_MF_SkipMatAnim |
                     Ft_MF_SkipRumble | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
                     Ft_MF_Unk19
               : Ft_MF_None;
}

void ftCo_800C5500(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800C544C(fp);
    ft_80088110(fp);
}

void ftCo_800C554C(Fighter* fp)
{
    fp->x2338.y = p_ftCommonData->x6B8;
}

void ftCo_800C555C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_8026C16C(fp->item_gobj, 0);
}

void ftCo_800C5588(Fighter* fp)
{
    it_8026C16C(fp->item_gobj, true);
    fp->x2219_b4 = true;
}
