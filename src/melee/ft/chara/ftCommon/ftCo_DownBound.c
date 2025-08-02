#include <platform.h>
#include <placeholder.h>

#include "ftCommon/forward.h"

#include "ftCo_DownBound.h"

#include "ftCo_09F7.h"
#include "ftCo_Down.h"
#include "ftCo_DownAttack.h"
#include "ftCo_DownStand.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/types.h"
#include "ftSandbag/ftSb_Init.h"
#include "lb/lbrefract.h"

#include <common_structs.h>
#include <math.h>
#include <math_ppc.h>
#include <dolphin/mtx.h>
#include <baselib/jobj.h>

/* 097040 */ static void ftCo_800976A4(Fighter_GObj* gobj);
/* 0972E8 */ static void ftCo_8009794C(Fighter_GObj* gobj);
/* 097490 */ static void ftCo_80097AF4(Fighter_GObj* gobj);

bool ftCo_80097570(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_JObj* jobj = fp->parts[ftParts_8007500C(fp, FtPart_HipN)].joint;
    HSD_JObjSetupMatrix(jobj);
    {
        float f = fp->x2226_b0 ? jobj->mtx[1][2] : jobj->mtx[1][1];
        if (f > 0) {
            return true;
        }
        return false;
    }
}

void ftCo_80097630(Fighter* fp, enum_t* sfx_ids, float threshold)
{
    ft_80088148(fp,
                threshold >= p_ftCommonData->x1F0   ? sfx_ids[0]
                : threshold >= p_ftCommonData->x1F4 ? sfx_ids[1]
                : threshold >= p_ftCommonData->x1F4 ? sfx_ids[2]
                                                    : sfx_ids[3],
                127, 64);
}

void ftCo_800976A4(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = gobj->user_data;
    float vel_x = fp->self_vel.x + fp->x8c_kb_vel.x;
    float vel_y = fp->self_vel.y + fp->x8c_kb_vel.y;
    float dist = sqrtf(SQ(vel_x) + SQ(vel_y)) * fp->co_attrs.weight;
    enum_t ef_id = 1031;
    IntVec3 ivec;
    Vec3 vec1;
    Vec3 vec0;
    ivec.y = 1;
    if (ft_80084C74(gobj, &ivec.z, &ivec.y, &ivec.x)) {
        if (ivec.z != -1) {
            ftCo_80097630(fp, ftCo_DownBound_SfxIds, dist);
        }
        if (ivec.x != -1) {
            ef_id = ivec.x;
        }
    }
    vec0.x = vec1.x = 0;
    vec0.y = vec1.y = 0;
    vec0.z = vec1.z = 0;
    ftCo_8009F834(gobj, ef_id, 0, 0, 0, &vec1, &vec0, 0);
    if (ivec.y != 0) {
        ftCo_80097630(fp, ftCo_DownBound_SfxIds, dist);
    }
    Camera_80030E44(4, &fp->cur_pos);
    ftCommon_8007EBAC(fp, 9, 0);
}

/// @todo This is a common inline. Needs to be solved and placed in a header.
///       Could also be a real library function.
static inline void inlineA0(Fighter_GObj* gobj, enum_t arg1, enum_t arg2,
                            Fighter_Part part, float* param)
{
    Fighter* fp = gobj->user_data;
    void* fp_x60C = &fp->x60C;
    HSD_JObj* jobj = fp->parts[part].joint;
    efAsync_Spawn(gobj, fp_x60C, arg1, arg2, jobj, &param);
}

void ftCo_800978D4(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    float param =
        atan2f(-fp->coll_data.floor.normal.x, fp->coll_data.floor.normal.y);
    inlineA0(gobj, 4, 1030, FtPart_TopN, &param);
    ftCo_800976A4(gobj);
}

void ftCo_8009794C(Fighter_GObj* gobj)
{
    u8 _[12] = { 0 };
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    {
        bool b = ftCo_80097570(gobj);
        if (fp->x2226_b1) {
            b = !b;
        }
        Fighter_ChangeMotionState(
            gobj, b ? ftCo_MS_DownBoundU : ftCo_MS_DownBoundD,
            Ft_MF_SkipNametagVis | Ft_MF_KeepColAnimPartHitStatus, 0, 1, 0,
            NULL);
        ftCo_800978D4(gobj);
        ftCo_800976A4(gobj);
        fp->x67C = 255;
        fp->x67D = 255;
        ftCommon_8007E2F4(fp, 511);
        ftCommon_8007CCE8(fp);
    }
}

void ftCo_80097AF4(Fighter_GObj* gobj)
{
    // ftCo_80097570
    Fighter* fp = gobj->user_data;
    HSD_JObj* jobj = fp->parts[ftParts_8007500C(fp, FtPart_HipN)].joint;
    float rot0, rot1;
    HSD_JObjSetupMatrix(jobj);
    if (fp->x2226_b0) {
        rot0 = jobj->mtx[0][2];
        rot1 = jobj->mtx[1][2];
    } else {
        rot0 = jobj->mtx[0][1];
        rot1 = jobj->mtx[1][1];
    }
    if (ABS(rot0) < ABS(rot1)) {
        ftCo_8009794C(gobj);
    } else {
        // ftCo_800978D4
        Fighter* fp = gobj->user_data;
        float param = atan2f(-fp->self_vel.y, fp->self_vel.x);
        HSD_JObj* jobj = fp->parts[FtPart_TopN].joint;
        {
            Fighter* fp = gobj->user_data;
            efAsync_Spawn(gobj, &fp->x60C, 4, 1030, jobj, &param);
            ftCo_800976A4(gobj);
        }
        Camera_80030E44(4, &fp->cur_pos);
        if (fp->facing_dir * rot0 > 0) {
            ft_8008A2BC(gobj);
        } else {
            ftSb_Init_8014FBA4(gobj);
        }
        ftCommon_8007CCE8(fp);
    }
}

#define SOLUTION 1
void ftCo_80097D40(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
#if SOLUTION == 0
    ftCo_80097D88(gobj);
#else
    u8 _[8] = { 0 };
    if (fp->x2228_b2) {
        ftCo_80097AF4(gobj);
    } else {
        ftCo_8009794C(gobj);
    }
#endif
    M2C_FIELD(fp, s8*, 0x2344) = 0;
}
#undef SOLUTION

void ftCo_80097D88(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x2228_b2) {
        ftCo_80097AF4(gobj);
    } else {
        ftCo_8009794C(gobj);
    }
}

void ftCo_DownBound_Anim(Fighter_GObj* gobj)
{
    RETURN_IF(ftAnim_IsFramesRemaining(gobj));
    RETURN_IF(ftCo_80098400(gobj));
    RETURN_IF(ftCo_Down_CheckInput(gobj));
    ftCo_80097E8C(gobj);
}

void ftCo_DownBound_IASA(Fighter_GObj* gobj) {}

void ftCo_DownBound_Phys(Fighter_GObj* arg0)
{
    ft_80084F3C(arg0);
}

void ftCo_DownBound_Coll(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    if (ft_80082708(gobj) == GA_Ground) {
        ftCo_Fall_Enter(gobj);
    } else {
        RETURN_IF(ftCo_800C7CA0(gobj));
    }
}

void ftCo_80097E8C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    {
        FtMotionId msid;
        if (fp->motion_id == ftCo_MS_DownBoundU ||
            fp->motion_id == ftCo_MS_DownSpotU)
        {
            msid = ftCo_MS_DownWaitU;
        } else {
            msid = ftCo_MS_DownWaitD;
        }
        fp->mv.co.downwait.x0 = p_ftCommonData->x424;
        Fighter_ChangeMotionState(gobj, msid,
                                  Ft_MF_SkipModel | Ft_MF_SkipMatAnim |
                                      Ft_MF_SkipNametagVis |
                                      Ft_MF_KeepColAnimPartHitStatus,
                                  0, 1, 0, NULL);
    }
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, true);
}

void ftCo_80097F38(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(
        gobj,
        fp->motion_id == ftCo_MS_DownDamageU ? ftCo_MS_DownWaitU
                                             : ftCo_MS_DownWaitD,
        Ft_MF_SkipModel | Ft_MF_SkipMatAnim | Ft_MF_SkipNametagVis |
            Ft_MF_KeepColAnimPartHitStatus,
        0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 1);
}

void ftCo_DownWait_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!fp->x2224_b2) {
        fp->mv.co.downwait.x0 -= 1;
    }
    if (fp->mv.co.downwait.x0 <= 0) {
        ftCo_80098160(gobj, fp->motion_id == ftCo_MS_DownWaitU
                                ? ftCo_MS_DownStandU
                                : ftCo_MS_DownStandD);
    }
}

void ftCo_DownWait_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_800984D4(gobj));
    RETURN_IF(ftCo_Down_CheckInput(gobj));
    RETURN_IF(ftCo_800980BC(gobj));
}

void ftCo_DownWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DownWait_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
