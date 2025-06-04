#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft_0C31.h"

#include "ft_081B.h"
#include "ft_0852.h"
#include "ftcommon.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/types.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_DownBound.h"
#include "ftCommon/types.h"
#include "it/it_26B1.h"
#include "it/items/itgreatfoxlaser.h"
#include "it/items/itleadead.h"
#include "it/items/itlikelike.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <baselib/dobj.h>
#include <baselib/jobj.h>

void ftCo_800C61B0(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_Entry_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.entry.timer == 0) {
        ftCo_800C6408(gobj);
    }
    --fp->mv.co.entry.timer;
}

void ftCo_Entry_IASA(ftCo_GObj* gobj) {}

void ftCo_Entry_Phys(ftCo_GObj* gobj) {}

void fn_800C63BC(ftCo_GObj* gobj)
{
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
}

void fn_800C63E0(ftCo_GObj* gobj)
{
    ftCommon_8007D5D4(GET_FIGHTER(gobj));
}

void ftCo_Entry_Coll(ftCo_GObj* gobj) {}

void ftCo_800C6408(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_EntryStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    --fp->mv.co.entry.timer;
    if (fp->mv.co.entry.timer == 0) {
        ftCo_800C6B6C(gobj);
    }
}

void ftCo_EntryStart_IASA(ftCo_GObj* gobj) {}

void ftCo_EntryStart_Phys(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_EntryStart_Coll(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C6AFC(HSD_JObj* jobj)
{
    if (jobj == NULL || HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetMtxDirtySub(jobj);
}

void ftCo_800C6B6C(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_EntryEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    --fp->mv.co.entry.timer;
    if (fp->mv.co.entry.timer == 0) {
        if (Player_GetFlagsBit4(fp->player_id)) {
            ftColl_8007B760(gobj, p_ftCommonData->x6C8);
        }
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_EntryEnd_IASA(ftCo_GObj* gobj) {}

void ftCo_EntryEnd_Phys(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_EntryEnd_Coll(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

extern float ftCo_804D8DE8;

void ftCo_800C703C(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->xA4_unk_vel.x = fp->self_vel.x;
    fp->xA4_unk_vel.y = p_ftCommonData->x6D0;
    fp->xA4_unk_vel.z = 0;
    fp->dmg.x1948 = fp->dmg.x194C = p_ftCommonData->x6CC;
}

/// @todo #ftCo_800C6150
void ftCo_800C7070(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_RebirthWait, 0, 0, 1, 0, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}

void ftCo_800C70D0(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C7158(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}

void ftCo_800C7178(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C7200(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}

static inline void inlineB0(ftCo_GObj* gobj)
{
    ftCo_800C7070(gobj);
}

static inline void inlineB1(ftCo_GObj* gobj)
{
    inlineB0(gobj);
}

static inline void inlineB2(ftCo_GObj* gobj)
{
    inlineB1(gobj);
}

void ftCo_800C7220(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        ftCo_800C7070(gobj);
    }
}

void ftCo_800C7294(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        ftCo_800C7070(gobj);
    }
}

void ftCo_800C7308(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        ftCo_800C7070(gobj);
    }
}

void ftCo_800C737C(ftCo_GObj* gobj)
{
    ft_8008521C(gobj);
}

void ftCo_800C739C(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C7414(ftCo_GObj* gobj)
{
    ft_8008521C(gobj);
}

static inline void inlineC0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0xE, 0, 0, 1, 0, NULL);
    fp->x2219_b1 = true;
    fp->x2219_b2 = true;
}

static inline void inlineC1(ftCo_GObj* gobj)
{
    inlineC0(gobj);
}

static inline void inlineC2(ftCo_GObj* gobj)
{
    inlineC1(gobj);
}

void ftCo_800C7434(ftCo_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    if (temp_r31->kind == FTKIND_GKOOPS) {
        inlineC2(gobj);
    } else {
        inlineB2(gobj);
    }
}

void ftCo_800C74AC(ftCo_GObj* gobj)
{
    ft_8008521C(gobj);
}

void fn_800C74CC(ftCo_GObj* gobj)
{
    it_802EADD8(GET_FIGHTER(gobj)->mv.co.captureleadead.x0);
}

bool ftCo_800C74F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x1860_element == 16 && fp->capture_timer == 0 &&
        fp->motion_id != ftCo_MS_CaptureLeadead &&
        it_802EAF28(fp->dmg.x1868_source) == NULL)
    {
        ftCo_800C7590(gobj);
        return true;
    }
    return false;
}

void fn_800C7568(ftCo_GObj* gobj)
{
    it_802EADD8(GET_FIGHTER(gobj)->mv.co.captureleadead.x0);
}

void ftCo_800C7590(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_CaptureLeadead_Anim(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_CaptureLeadead_IASA(ftCo_GObj* gobj) {}

void ftCo_CaptureLeadead_Phys(ftCo_GObj* gobj) {}

static void fn_800C77E0(ftCo_GObj* arg0)
{
    ftCo_80090780(arg0);
}

void ftCo_CaptureLeadead_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800C77E0);
}

UNK_RET ftCo_800C7800(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void fn_800C7890(ftCo_GObj* gobj)
{
    ftCo_800C7A30(gobj);
}

UNK_RET ftCo_800C78B0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C7A30(ftCo_GObj* gobj)
{
    it_802DBA68(GET_FIGHTER(gobj)->mv.co.capturelikelike.x0);
}

void ftCo_CaptureLikelike_Anim(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_CaptureLikelike_IASA(ftCo_GObj* gobj) {}

void ftCo_CaptureLikelike_Phys(ftCo_GObj* gobj) {}

void ftCo_CaptureLikelike_Coll(ftCo_GObj* gobj) {}

void fn_800C7AE0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_8026B294(fp->mv.co.captureleadead.x0, &fp->cur_pos);
}

UNK_RET ftCo_800C7B0C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C7C60(ftCo_GObj* gobj, int damage_amount)
{
    Fighter_TakeDamage_8006CC7C(GET_FIGHTER(gobj), damage_amount);
}

bool ftCo_800C7CA0(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_DownReflect_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80090780(gobj);
    }
}

void ftCo_DownReflect_IASA(ftCo_GObj* gobj) {}

void ftCo_DownReflect_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_DownReflect_Coll(ftCo_GObj* gobj)
{
    if (ft_80081DD4(gobj)) {
        ftCo_80097D88(gobj);
    }
}

void ftCo_800C8064(void)
{
    HSD_DObj* temp_r3;
    HSD_MObj* var_r0;

    temp_r3 = HSD_JObjGetDObj(HSD_JObjLoadJoint(Fighter_804D6504));
    if (temp_r3 != NULL) {
        var_r0 = temp_r3->mobj;
    } else {
        var_r0 = NULL;
    }
    ft_804D6580 = var_r0;
}

void ft_800C80A4(Fighter* fp)
{
    size_t i;
    int idx;

    for (i = idx = 0; i < ftPartsTable[fp->kind]->parts_num; idx++, i++) {
        FighterBone* bone = &fp->parts[idx];
        if (bone->flags_b1) {
            HSD_JObj* jobj = bone->joint;
            HSD_DObj* dobj = HSD_JObjGetDObj(jobj);
            HSD_JObjSetFlags(jobj, JOBJ_LIGHTING | JOBJ_TEXGEN |
                                       JOBJ_SPECULAR | JOBJ_UNK_B18);
            HSD_JObjClearFlags(jobj, JOBJ_UNK_B19 | JOBJ_UNK_B20);
            while (dobj != NULL) {
                HSD_DObj* cur;
                HSD_DObjModifyFlags(dobj, 2, 0xE);
                if (dobj != NULL) {
                    cur = dobj->next;
                } else {
                    cur = NULL;
                }
                dobj = cur;
            }
        }
    }
}
