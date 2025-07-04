#include <platform.h>

#include "forward.h"

#include "ftDk_SpecialLw.h"

#include "ftDk_Init.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftDonkey/types.h"

void ftDk_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.dk.speciallw.x0 = 0;
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialLwStart, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
}

static void doAnim(HSD_GObj* gobj);

void ftDk_SpecialLwStart_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        doAnim(gobj);
    }
}

void ftDk_SpecialLwStart_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialLwStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLwStart_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftCo_800CC730(gobj);
    }
}

static void doTransition(HSD_GObj* gobj);

void ftDk_SpecialLwLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.dk.speciallw.x0) {
            fp->mv.dk.speciallw.x0 = 0;
            doAnim(gobj);
        } else {
            doTransition(gobj);
        }
    }
}

void ftDk_SpecialLwLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & 512) {
        fp->mv.dk.speciallw.x0 = 1;
    }
}

void ftDk_SpecialLwLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLwLoop_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftCo_800CC730(gobj);
    }
}

static void callback(HSD_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

static void ftDonkey_8010DE88_inner(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    if (!fp->x2219_b0) {
        efAsync_Spawn(gobj, &fp->x60C, 1, 1228, fp->parts[FtPart_TopN].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

static void callback(HSD_GObj* gobj);

static void doAnim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x21EC = callback;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialLwLoop, 0, 0, 1, 0, NULL);
    ftDonkey_8010DE88_inner(gobj);
    fp->accessory4_cb = ftDk_Init_8010DB3C;
}

void ftDk_SpecialLwEnd0_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialLwEnd0_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialLwEnd0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialLwEnd0_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftCo_800CC730(gobj);
    }
}

static void doTransition(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialLwEnd0, 0, 0, 1, 0, NULL);
}

void ftDk_SpecialLwEnd1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftDk_SpecialLwEnd1_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialLwEnd1_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftDk_SpecialLwEnd1_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialLw_8010E0CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(1222, gobj, fp->parts[FtPart_TransN].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftDk_SpecialLw_8010E148(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(1223, gobj, fp->parts[FtPart_TransN].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}
