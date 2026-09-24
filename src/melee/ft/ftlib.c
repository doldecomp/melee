#include "ftlib.h"

#include <melee/it/forward.h>

#include "fighter.h"
#include "forward.h"
#include "ft_081B.h"
#include "ft_0877.h"
#include "ft_0D4D.h"
#include "ftanim.h"
#include "ftchangeparam.h"
#include "ftcommon.h"
#include "ftdata.h"
#include "ftmetal.h"
#include "ftparts.h"
#include "kinds/ftCommon/forward.h"
#include "kinds/ftGameWatch/ftgamewatch.h"
#include "kinds/ftKirby/ftkirby.h"
#include <melee/cm/camera.h>
#include <melee/cm/types.h>
#include <melee/ef/efasync.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/it/it_26B1.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_013B.h>
#include <melee/mn/types.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/rumble.h>

s32 ftLib_CountFighters(void)
{
    s32 ret = 0;
    HSD_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        ret++;
    }
    return ret;
}

bool ftLib_IsMasterHandPresent(void)
{
    u8 _[8];

    HSD_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        if (ftLib_GetKind(cur) == Ft_Kind_MasterH) {
            return true;
        }
    }

    return false;
}

bool ftLib_IsCrazyHandPresent(void)
{
    u8 _[8];

    HSD_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        if (ftLib_GetKind(cur) == Ft_Kind_CrezyH) {
            return true;
        }
    }

    return false;
}

HSD_GObj* ftLib_FindLowestPercentOpponent(HSD_GObj* gobj)
{
    /// @todo Figure out how these are really declared
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;
    int min_percent = 999;

    u8 _[8];

    if (gobj != NULL) {
        fp = GET_FIGHTER(gobj);
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        if (!ftLib_IsSamePlayer(gobj, cur)) {
            // If not same player
            Fighter* cur_fp = GET_FIGHTER(cur);
            if (cur_fp->is_sleeping) {
                continue;
            }

            // Skip if same team
            if (gm_8016B168() && fp != NULL && cur_fp->team == fp->team) {
                continue;
            }

            if (cur_fp->dmg.x1830_percent < min_percent) {
                min_percent = cur_fp->dmg.x1830_percent;
                result = cur;
            }
        }
    }

    return result;
}

/// Closest opponent to @p pos (squared x/y distance), skipping teammates.
HSD_GObj* ftLib_FindNearestOpponent(Vec3* pos, HSD_GObj* gobj)
{
    Vec3 cur_v;
    float dist;
    float dx;
    float dy;
    Fighter* cur_fp;
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;

    u8 _[16];

    float min_dist = F32_MAX;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        // skip if same player
        if (ftLib_IsSamePlayer(gobj, cur)) {
            continue;
        }

        cur_fp = cur->user_data;
        // skip if same team
        if (cur_fp->is_sleeping ||
            (gm_8016B168() && fp != NULL && cur_fp->team == fp->team))
        {
            continue;
        }

        ftLib_GetCameraBonePos(cur, &cur_v);
        dx = pos->x - cur_v.x;
        dy = pos->y - cur_v.y;
        dist = (dx * dx) + (dy * dy);

        if (dist < min_dist) {
            min_dist = dist;
            result = cur;
        }
    }
    return result;
}

/// Like #ftLib_FindNearestOpponent, but only opponents on the @p facing_dir
/// side of @p v.
Fighter_GObj* ftLib_FindNearestOpponentInDir(Vec3* v, Fighter_GObj* gobj,
                                             float facing_dir)
{
    Vec3 sp24;
    float dx, dy, diff;
    Fighter* cur_fp;
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;

    u8 _[16];

    float min_diff = F32_MAX;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        if (ftLib_IsSamePlayer(gobj, cur)) {
            continue;
        }

        cur_fp = cur->user_data;
        if (cur_fp->is_sleeping ||
            (gm_8016B168() && fp != NULL && cur_fp->team == fp->team))
        {
            continue;
        }
        ftLib_GetCameraBonePos(cur, &sp24);

        if ((facing_dir == -1 && sp24.x > v->x) ||
            (facing_dir == +1 && sp24.x < v->x))
        {
            continue;
        }

        dx = v->x - sp24.x;
        dy = v->y - sp24.y;
        diff = dx * dx + dy * dy;

        if (diff < min_diff) {
            min_diff = diff;
            result = cur;
        }
    }
    return result;
}

static inline s32 sgn(float x)
{
    if (x < 0.0f) {
        return -1;
    } else {
        return +1;
    }
}

float ftLib_GetOpponentsDir(Vec3* v, HSD_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp;
    HSD_GObj* cur;

    u8 _[12];

    int result = 0;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        if (ftLib_IsSamePlayer(gobj, cur)) {
            continue;
        }

        {
            Fighter* cur_fp = cur->user_data;
            if (cur_fp->is_sleeping ||
                (gm_8016B168() && fp != NULL && cur_fp->team == fp->team))
            {
                continue;
            }

            ftLib_GetCameraBonePos(cur, &vec);
            result += sgn(vec.x - v->x);
        }
    }

    if (result == 0) {
        result = HSD_Randi(2) != 0 ? +1 : -1;
    }

    if (result < 0) {
        return -1;
    } else {
        return +1;
    }
}

float ftLib_GetFacingDir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->facing_dir;
}

s32 ftLib_GetGroundAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->ground_or_air;
}

void ftLib_GetLStick(HSD_GObj* gobj, float* x, float* y)
{
    Fighter* fp = GET_FIGHTER(gobj);
    *x = fp->input.lstick[0].x;
    *y = fp->input.lstick[0].y;
}

HSD_JObj* ftLib_GetHipJObj(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].joint;
}

HSD_JObj* ftLib_GetPartJObj(HSD_GObj* gobj, Fighter_Part part)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->parts[part].joint;
}

void ftLib_GetPos(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    *pos = fp->cur_pos;
}

void ftLib_SetPos(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cur_pos = *pos;
}

void ftLib_GetPrevPos(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    *pos = fp->prev_pos;
}

void ftLib_SetScale(HSD_GObj* gobj, float val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x34_scale.y = val;
    Fighter_UpdateModelScale(gobj);
    ftCommon_80080174(fp);
}

void ftLib_GetCameraBonePos(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftCo_DatAttrs* r4 = &fp->co_attrs;
    s32 i = fp->ft_data->x0->camera_zoom_target_bone;
    lb_8000B1CC(ftLib_GetPartJObj(gobj, i), &r4->x170, v);
}

void ftLib_ReleaseItem(HSD_GObj* gobj, HSD_GObj* other)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL || fp->x1978 != NULL) {
        ftCommon_8007E6DC(gobj, other, 1);
    }
}

void ftLib_ClearHeldSpecialItem(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x1984_heldItemSpec != NULL) {
        ftCommon_8007E82C(gobj);
    }
}

HSD_GObj* ftLib_GetItem(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->item_gobj;
}

bool ftLib_IsHoldingItem(HSD_GObj* gobj, HSD_GObj* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftLib_GetItem(gobj) == arg1 || fp->x1978 == arg1) {
        return true;
    } else {
        return false;
    }
}

HSD_GObj* ftLib_GetHeldSpecialItem(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x1984_heldItemSpec;
}

bool ftLib_IsInputDisabled(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->input_disabled;
}

void ftLib_DisableInput(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ResetInputData_80068854(gobj);
    fp->input_disabled = true;
}

void ftLib_DisableAllInput(void)
{
    u8 _[16];

    HSD_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        ftLib_DisableInput(cur);
    }
}

void ftLib_EnableInput(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->input_disabled = false;
}

void ftLib_EnableAllInput(void)
{
    HSD_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        ftLib_EnableInput(cur);
    }
}

bool ftLib_IsItemVisible(HSD_GObj* gobj, HSD_GObj* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->item_gobj != arg1 && fp->x197C != arg1 && fp->x1980 != arg1) {
        return true;
    }

    if (fp->invisible || fp->x221E_b5 ||
        (!fp->x221E_b3 && fp->item_gobj == arg1) ||
        (!fp->x221E_b4 && (fp->x197C == arg1 || fp->x1980 == arg1)))
    {
        return false;
    } else {
        return true;
    }
}

/// Check if the HSD_GObj* class is a fighter
bool ftLib_IsFighter(HSD_GObj* arg)
{
    if (arg != NULL && arg->classifier == HSD_GOBJ_CLASS_FIGHTER) {
        return true;
    } else {
        return false;
    }
}

CollData* ftLib_GetCollData(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return Fighter_GetCollData(fp);
}

static inline void vector_add(Vec3* dst, Vec3* src, float x, float y, float z)
{
    dst->x = src->x + x;
    dst->y = src->y + y;
    dst->z = src->z + z;
}

void ftLib_GetECBCenter(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float tmp = 0.5f * (fp->coll_data.ecb.top.y + fp->coll_data.ecb.bottom.y);
    vector_add(v, &fp->cur_pos, 0, tmp, 0);
}

float ftLib_GetModelScale(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return ftCommon_GetModelScale(fp);
}

float ftLib_800869F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x34_scale.x * fp->co_attrs.model_scaling;
}

float ftLib_GetScale(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x34_scale.y;
}

bool ftLib_IsShielding(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool result = false;

    switch (fp->motion_id) {
    case ftCo_MS_GuardOn:
    case ftCo_MS_Guard:
    case ftCo_MS_GuardSetOff:
        result = true;
    }

    return result;
}

void ftLib_80086A4C(HSD_GObj* gobj, float val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->dmg.x1958 = val;
}

bool ftLib_GetScreenPos(HSD_GObj* gobj, S32Vec2* x)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2229_b3 && !fp->x2220_b7) {
        *x = fp->x2188;
    }

    return false;
}

bool ftLib_UpdateScreenVisibility(HSD_GObj* gobj)
{
    HSD_GObj* camera_gobj;

    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2229_b3 && !fp->x2220_b7) {
        camera_gobj = Camera_80030A50();
        if (camera_gobj != NULL) {
            HSD_CObj* temp_r30 = GET_COBJ(camera_gobj);
            if (temp_r30 == HSD_CObjGetCurrent()) {
                if (Camera_80030CD8(fp->x890_cameraBox, &fp->x2188)) {
                    fp->x221F_b0 = false;
                    return true;
                }
                fp->x221F_b0 = true;
                if (Camera_80030CFC(fp->x890_cameraBox, 15)) {
                    return true;
                }
                return false;
            }
        }
    }

    fp->x221F_b0 = false;
    return true;
}

bool ftLib_IsOffscreen(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221F_b0;
}

CmSubject* ftLib_GetCameraSubject(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x890_cameraBox;
}

float ftLib_80086B80(HSD_GObj* gobj)
{
    return ftLib_GetCameraSubject(gobj)->target_ext.v.z;
}

void ftLib_GetCameraSubjectBonePos(HSD_GObj* gobj, Vec3* v)
{
    CmSubject* cam = ftLib_GetCameraSubject(gobj);
    *v = cam->bone_pos;
}

bool ftLib_IsCameraSubjectInBounds(HSD_GObj* gobj)
{
    CmSubject* cam = ftLib_GetCameraSubject(gobj);
    return Camera_80031154(&cam->pos);
}

u8 ftLib_GetPlayerIndex(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->player_idx;
}

void ftLib_GetPosDelta(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    *v = fp->pos_delta;
}

enum_t ftLib_GetMotionId(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->motion_id;
}

static inline void helper(HSD_GObj* gobj, s32 arg1, s32 arg2, s32 val)
{
    Fighter* fp = gobj->user_data;

    if (!Player_8003544C(fp->player_idx, fp->is_sub_fighter)) {
        return;
    }

    if (!fp->is_sleeping && !fp->stamina_dead) {
        lb_80014574(fp->pad_port, val, arg1, arg2);
    }
}

void ftLib_StartRumble(HSD_GObj* gobj, s32 arg1, s32 arg2)
{
    helper(gobj, arg1, arg2, 0);
}

void ftLib_StartRumbleAll(s32 arg0, s32 arg1)
{
    u8 _[16];

    HSD_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        ftLib_StartRumble(cur, arg0, arg1);
    }
}

void ftLib_StartItemRumble(HSD_GObj* arg0, s32 arg1, s32 arg2)
{
    helper(arg0, arg1, arg2, 1);
}

void ftLib_StartItemRumbleAll(s32 arg0, s32 arg1)
{
    u8 _[16];

    HSD_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        ftLib_StartItemRumble(cur, arg0, arg1);
    }
}

void ftLib_StopItemRumble(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_8003544C(fp->player_idx, fp->is_sub_fighter)) {
        HSD_PadRumbleRemoveId(fp->pad_port, 1);
    }
}

/// Get fighter's team ID
s32 ftLib_GetTeam(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->team;
}

bool ftLib_IsInHitstun(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221C_b6;
}

bool ftLib_CanBeMagnified(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->invisible || fp->x221E_b2 ||
        Player_GetMoreFlagsBit4(fp->player_idx) || fp->is_sandbag ||
        fp->x2229_b3 || fp->x2220_b7)
    {
        return false;
    }

    return true;
}

bool ftLib_80086F4C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x221F_b2 && !fp->x221F_b1 && fp->x209A == 1) {
        return true;
    }

    return false;
}

float ftLib_GetNameTagHeight(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->invisible) {
        return fp->ft_data->x0->name_tag_height;
    }

    return fp->co_attrs.name_tag_height;
}

bool ftLib_IsSwordSwing(HSD_GObj* gobj)
{
    switch (ftLib_GetMotionId(gobj)) {
    case ftCo_MS_SwordSwing1:
    case ftCo_MS_SwordSwing3:
    case ftCo_MS_SwordSwing4:
    case ftCo_MS_SwordSwingDash:
        return true;
    }

    return false;
}

bool ftLib_IsSamePlayer(HSD_GObj* gobj0, HSD_GObj* gobj1)
{
    if (gobj0 != NULL && gobj1 != NULL) {
        if (gobj0 == gobj1) {
            return true;
        }

        {
            Fighter* fp0 = GET_FIGHTER(gobj0);
            Fighter* fp1 = GET_FIGHTER(gobj1);
            if (fp0->player_idx == fp1->player_idx) {
                return true;
            }
        }
    }

    return false;
}

bool ftLib_IsSleeping(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->is_sleeping;
}

void ftLib_IncFighterRefCount(s32 arg0)
{
    ftData_80085560(arg0, 1);
}

void ftLib_DecFighterRefCount(s32 arg0)
{
    ftData_80085560(arg0, -1);
}

bool ftLib_GetShakeOffset(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x18B8 || fp->dmg.x18BC) {
        v->x = fp->dmg.x18B8;
        v->y = fp->dmg.x18BC;
        v->z = 0.0f;
        return true;
    }
    return false;
}

bool ftLib_GetSubColor(HSD_GObj* gobj, GXColor* val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->sub_color) {
        *val = p_ftCommonData->sub_colors[fp->sub_color - 1];
        return true;
    }
    return false;
}

void ftLib_SetPercent(HSD_GObj* gobj, s32 x)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->dmg.x1830_percent = x;
}

s32 ftLib_GetPercent(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 result = fp->dmg.x1830_percent;
    return result;
}

void ftLib_80087140(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->is_sleeping) {
        ftCo_800D4F24(gobj, 1);
        ftCommon_8007ED2C(fp);
        Fighter_Spawn(gobj);
        ftCommon_8007D92C(gobj);
    }
}

void ftLib_ApplyMetalBox(Fighter_GObj* gobj, Item_GObj* item_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_ASSERT(1117, itGetKind(item_gobj) == It_Kind_MetalB);
    ftCo_800C8348(gobj, it_8026B560(item_gobj), it_8026B574(item_gobj));
    ftCo_800D105C(gobj);
    ft_80081C88(gobj, fp->x34_scale.y);
    ftCommon_8007EBAC(fp, 0xC, 0);
    Camera_RequestQuake(QuakeKind_Small, &fp->cur_pos);
    ft_PlaySFX(fp, 0x121, 0x7F, 0x40);
}

bool ftLib_IsSmashThrow(HSD_GObj* gobj)
{
    if (ftLib_GetMotionId(gobj) >= ftCo_MS_LightThrowF4) {
        return true;
    }

    return false;
}

FighterKind ftLib_GetKind(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->kind;
}

LbShadow* ftLib_GetShadow(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return &fp->x20A4;
}

bool ftLib_CastsShadow(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return !fp->x221E_b1 && !fp->x2226_b4 && !fp->is_sub_fighter;
}

s32 ftLib_GetLastAttackerSlot(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->dmg.x18c4_source_ply;
}

s32 ftLib_IsLastAttackerSubFighter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221F_b5;
}

s32 ftLib_IsSleeping_8008731C(HSD_GObj* gobj)
{
    return ftLib_IsSleeping(gobj);
}

bool ftLib_IsDead(HSD_GObj* gobj)
{
    FtMotionId msid = ftLib_GetMotionId(gobj);
    if (msid >= ftCo_MS_DeadDown && msid <= ftCo_MS_DeadUpFallHitCameraIce) {
        return true;
    }

    return false;
}

bool ftLib_IsDeadUp(HSD_GObj* gobj)
{
    FtMotionId msid = ftLib_GetMotionId(gobj);
    if (msid >= ftCo_MS_DeadUp && msid <= ftCo_MS_DeadUpFallHitCameraIce) {
        return true;
    }

    return false;
}

bool ftLib_IsDeadUpStar(HSD_GObj* gobj)
{
    FtMotionId msid = ftLib_GetMotionId(gobj);
    if (msid >= ftCo_MS_DeadUpStar && msid <= ftCo_MS_DeadUpStarIce) {
        return true;
    }

    return false;
}

bool ftLib_IsDeadUpFall(HSD_GObj* gobj)
{
    FtMotionId msid = ftLib_GetMotionId(gobj);
    if (msid >= ftCo_MS_DeadUpFall && msid <= ftCo_MS_DeadUpFallHitCameraIce) {
        return true;
    }

    return false;
}

bool ftLib_IsRebirth(HSD_GObj* gobj)
{
    FtMotionId msid = ftLib_GetMotionId(gobj);
    if (msid >= ftCo_MS_Rebirth && msid <= ftCo_MS_RebirthWait) {
        return true;
    }

    return false;
}

bool ftLib_IsEntry(HSD_GObj* gobj)
{
    FtMotionId msid = ftLib_GetMotionId(gobj);
    if (msid >= ftCo_MS_Entry && msid <= ftCo_MS_EntryEnd) {
        return true;
    }

    return false;
}

HSD_GObj* ftLib_FindBySpawnNum(u32 i)
{
    HSD_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        Fighter* fp = GET_FIGHTER(cur);

        /// @todo Is @c i really #u32?
        if ((unsigned) fp->x8_spawnNum == i) {
            return cur;
        }
    }
    return NULL;
}

float ftLib_GetKnockbackMagnitude(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->dmg.x18A4_knockbackMagnitude;
}

u32 ftLib_GetSpawnNum(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x8_spawnNum;
}

s32 ftLib_8008746C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCommon_80080144(fp)) {
        return 0x1FBD1;
    }

    return fp->ft_data->x4C_sfx->x34;
}

s32 ftLib_IsSubFighter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->is_sub_fighter;
}

void ftLib_800874CC(HSD_GObj* gobj, void* arg1, s32 arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    pl_8003E4A4(fp->player_idx, fp->is_sub_fighter, arg1, arg2);
}

void ftLib_LoadFighterCostume(s8 ft_kind, u8 arg1)
/// void ftLib_LoadFighterCostume(FighterKind ft_kind, u8 arg1)
{
    ftData_8008572C(ft_kind);
    efAsync_LoadSync(ftData_UnkBytePerCharacter[ft_kind]);
    ftData_80085820(ft_kind, arg1);
    ftData_80085A14(ft_kind);
    ftData_800857E0(ft_kind);
}

void ftLib_LoadFighterAllCostumes(s8 ft_kind)
/// void ftLib_LoadFighterAllCostumes(FighterKind ft_kind)
{
    u8 i;
    ftData_8008572C(ft_kind);
    efAsync_LoadSync(ftData_UnkBytePerCharacter[ft_kind]);

    for (i = 0; i < CostumeListsForeachCharacter[ft_kind].numCostumes; i++) {
        ftData_80085820(ft_kind, i);
    }

    ftData_80085A14(ft_kind);
    ftData_800857E0(ft_kind);
}

void ftLib_LoadKirbyHats(u8 arg0)
{
    u8 i;
    for (i = 0; i <= SELKIND_COUNT; i++) {
        if (gm_IsCKindUnlocked(i)) {
            ftKb_SpecialN_800EED50(Player_800325C8(i, 0), arg0);
            if (i == CKind_Zelda || i == CKind_Seak) {
                ftKb_SpecialN_800EED50(Player_800325C8(i, 1), arg0);
            }
        }
    }
}

void ftLib_IsFramesRemaining(HSD_GObj* gobj)
{
    ftAnim_IsFramesRemaining(gobj);
}

bool ftLib_IsChargingSmash(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->smash_attrs.state == SmashState_Charging) {
        return true;
    } else {
        return false;
    }
}

s32 ftLib_GetLastHitSourceType(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->dmg.x18CC;
}

s32 ftLib_GetLastHitSourceKind(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->dmg.x18D0;
}

void ftLib_GetGameWatchColor(HSD_GObj* gobj, void* dst)
{
    if (ftLib_GetKind(gobj) == Ft_Kind_GameWatch) {
        ftGw_Init_8014A7F4(gobj, dst);
    } else {
        ftKb_Init_800EEB00(gobj, dst);
    }
}

void ftLib_GetGameWatchOutlineColor(HSD_GObj* gobj, void* dst)
{
    if (ftLib_GetKind(gobj) == Ft_Kind_GameWatch) {
        ftGw_Init_8014A814(gobj, dst);
    } else {
        ftKb_Init_800EEB1C(gobj, dst);
    }
}

float ftLib_GetGroundSlopeAngle(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_ASSERT(1517, fp->ground_or_air == GA_Ground);

    {
        CollData* cd = Fighter_GetCollData(fp);
        return atan2f(-cd->floor.normal.x, cd->floor.normal.y);
    }
}

bool ftLib_IsBeingNudged(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->xF8_playerNudgeVel.x != 0) {
        return true;
    } else {
        return false;
    }
}
