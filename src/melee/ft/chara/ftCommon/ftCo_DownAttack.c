#include "ftCo_DownAttack.h"

#include "ftCo_HammerWait.h"
#include "ftCo_Passive.h"

#include <platform.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_AppealS.h"
#include "it/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <baselib/gobj.h>

static Vec4 unk_vec4 = { 14, 0, -3, +3 };

static inline bool inlineA0(Fighter* fp)
{
    if (fp->input.x668 & (HSD_PAD_A | HSD_PAD_B)) {
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
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
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

void ftCo_80098634(HSD_ObjAllocUnk2* arg0)
{
    Vec4* cur_vec4 = (Vec4*) arg0;
    Vec3* cur_pos = (Vec3*) arg0;
    Fighter_GObj* cur_gobj;
    int count = 0;
    for (cur_gobj = HSD_GObj_Entities->fighters; cur_gobj != NULL;
         cur_gobj = cur_gobj->next)
    {
        Fighter* fp = cur_gobj->user_data;
        ++count;
        cur_vec4->x = unk_vec4.x;
        cur_vec4->y = unk_vec4.y;
        cur_vec4->z = unk_vec4.z;
        cur_vec4->w = unk_vec4.w;
        ++cur_vec4;
        cur_pos[16] = fp->cur_pos;
        ++cur_pos;
    }
    arg0->x150 = count;
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

int ftCo_8009872C(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    if (ftCo_800986B0(gobj)) {
        ftCo_800987D0(gobj);
        return true;
    }
    return false;
}
