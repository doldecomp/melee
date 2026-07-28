#include "ftCo_DownAttack.h"

#include "ftCo_HammerWait.h"
#include "ftCo_Passive.h"

#include <platform.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0DF1.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "it/types.h"

#include <baselib/gobj.h>

/** @details Summed with ::Item::xBEC in ::it_80271B60; seems to describe an
 * upward expansion along the Y-axis and a symmetrical contraction along the
 * X-axis, rather than its own bounding box.
 */
static itECB ecb_offset = { 14.0f, 0.0f, -3.0f, +3.0f };

static inline bool inlineA0(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_AB) {
        return true;
    }
    return false;
}

int ftCo_800984D4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (inlineA0(fp) || ftCo_800DF644(fp)) {
        bool msid = fp->motion_id == ftCo_MS_DownWaitU ? ftCo_MS_DownAttackU
                                                       : ftCo_MS_DownAttackD;
        ftCo_8009856C(gobj, msid);
        return true;
    }
    return false;
}

void ftCo_8009856C(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_DownAttack_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_DownAttack_IASA(Fighter_GObj* gobj) {}

void ftCo_DownAttack_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DownAttack_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

void ftCo_80098634(Item_FtTrack* track)
{
    Fighter_GObj* cur_gobj;
    int i;
    for (cur_gobj = HSD_GObj_Entities->fighters, i = 0; cur_gobj != NULL;
         cur_gobj = cur_gobj->next, i++)
    {
        Fighter* fp = cur_gobj->user_data;
        track->ecb_offset_arr[i].top = ecb_offset.top;
        track->ecb_offset_arr[i].bottom = ecb_offset.bottom;
        track->ecb_offset_arr[i].right = ecb_offset.right;
        track->ecb_offset_arr[i].left = ecb_offset.left;
        track->ft_pos_arr[i] = fp->cur_pos;
    }
    track->count = i;
}

bool ftCo_800986B0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftCo_800C5240(gobj) && fp->x680 < p_ftCommonData->x250 &&
        fp->x684 >= p_ftCommonData->x1C)
    {
        return true;
    }
    return false;
}

bool ftCo_8009872C(Fighter_GObj* gobj)
{
    PAD_STACK(4);
    if (ftCo_800986B0(gobj)) {
        ftCo_800987D0(gobj);
        return true;
    }
    return false;
}
