#include "ftbosslib.h"

#include "ft_0877.h"
#include "ftlib.h"
#include "math.h"

#include "cm/camera.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftMasterHand/types.h"
#include "it/it_26B1.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include "pl/forward.h"

#include "pl/player.h"

#include <math_ppc.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <MetroTRK/intrinsics.h>

/// @todo Float reorder hack
static float get_zero(void)
{
    return 0.0f;
}

void ftBossLib_8015BD20(HSD_GObj* gobj)
{
    return;
}

void ftBossLib_8015BD24(s32 arg0, float* arg1, float arg2, s32 arg3, s32 arg4,
                        s32 arg5)
{
    *arg1 = ((s32) (arg3 / arg0) + HSD_Randi(arg4 - arg5) + arg5) / arg2;
}

void ftBossLib_8015BDB4(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    Gm_PKind kind = Player_GetPlayerSlotType(fp->player_id);
    HSD_ASSERTREPORT(103,
                     kind == Gm_PKind_Human || kind == Gm_PKind_Boss ||
                         kind == Gm_PKind_Cpu,
                     "boss is human or boss!\n");
}

static inline float my_lbvector_Len(Vec3* vec)
{
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftBossLib_8015BE40(HSD_GObj* gobj, Vec3* arg1, float* arg2, float arg3,
                        float arg4)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 diff;

    lbVector_Diff(arg1, &fp->cur_pos, &diff);

    {
        float distance = my_lbvector_Len(&diff);
        if (distance < arg3) {
            *arg2 = 0.0f;
        } else {
            *arg2 = distance;
            lbVector_Normalize(&diff);
            diff.x *= distance * arg4;
            diff.y *= distance * arg4;
            diff.z *= distance * arg4;
        }
    }

    fp->self_vel.x = diff.x;
    fp->self_vel.y = diff.y;
}

void ftBossLib_8015BF74(HSD_GObj* gobj, float x_diff_max)
{
    Fighter* fp = gobj->user_data;
    Vec3 vec;

    ftBossLib_8015C208(gobj, &vec);

    {
        float x_diff = vec.x - fp->cur_pos.x;
        float abs_x_diff = ABS(x_diff);
        if (abs_x_diff > x_diff_max) {
            fp->self_vel.x += x_diff > 0 ? x_diff_max : -x_diff_max;
        } else {
            fp->self_vel.x += x_diff;
        }
    }
}

void ftBossLib_8015C010(HSD_GObj* gobj, float x_diff_max)
{
    Vec3 vec;
    Fighter* fp = gobj->user_data;
    ftBossLib_8015C208(gobj, &vec);

    {
        float x_diff = vec.x - fp->cur_pos.x;
        float abs_x_diff = ABS(x_diff);
        if (abs_x_diff > x_diff_max) {
            fp->self_vel.x = x_diff > 0 ? x_diff_max : -x_diff_max;
        } else {
            fp->self_vel.x = x_diff;
        }
    }
}

void ftBossLib_8015C09C(HSD_GObj* gobj, float facing_dir)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    Quaternion quat = { 0 };

    fp->facing_dir = facing_dir;
    quat.y = M_PI_2 * fp->facing_dir;
    HSD_JObjSetRotation(jobj, &quat);
}

void ftBossLib_8015C190(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    Vec3 vec;

    mpFloorGetRight(0, &vec);
    if (fp->cur_pos.x > vec.x) {
        fp->cur_pos.x = vec.x;
        fp->self_vel.x = 0;
    }

    mpFloorGetLeft(0, &vec);
    if (fp->cur_pos.x < vec.x) {
        fp->cur_pos.x = vec.x;
        fp->self_vel.x = 0;
    }
}

void ftBossLib_8015C208(HSD_GObj* arg0, Vec3* arg1)
{
    Fighter* fp = GET_FIGHTER(arg0);
    HSD_GObj* gobj = ftBossLib_8015C244(arg0, &fp->cur_pos);
    ftLib_80086644(gobj, arg1);
}

HSD_GObj* ftBossLib_8015C244(HSD_GObj* arg0, Vec3* arg1)
{
    return ftLib_8008627C(arg1, arg0);
}

bool ftBossLib_8015C270(void)
{
    /// @todo Get msid
    if (ftBossLib_8015C44C(FTKIND_MASTERH) == 0x157) {
        return 1;
    }

    return 0;
}

bool ftBossLib_8015C2A8(void)
{
    /// @todo Get msid
    if (ftBossLib_8015C44C(FTKIND_CREZYH) == 0x183) {
        return true;
    }

    return false;
}

bool ftBossLib_8015C2E0(void)
{
    /// @todo Get ASIDs
    enum_t msid = ftBossLib_8015C44C(FTKIND_MASTERH);
    if (msid == 0x158 || msid == 0x159) {
        return true;
    }

    return false;
}

bool ftBossLib_8015C31C(void)
{
    /// @todo Get ASIDs
    enum_t msid = ftBossLib_8015C44C(FTKIND_CREZYH);
    if (msid == 0x181 || msid == 0x182) {
        return true;
    }

    return false;
}

bool ftBossLib_8015C358(void)
{
    HSD_GObj* gobj = ftBossLib_8015C3E8(FTKIND_MASTERH);
    if (gobj && GET_FIGHTER(gobj)->x221F_b3) {
        return true;
    }

    return false;
}

bool ftBossLib_8015C3A0(void)
{
    HSD_GObj* gobj = ftBossLib_8015C3E8(FTKIND_CREZYH);
    if (gobj && GET_FIGHTER(gobj)->x221F_b3) {
        return true;
    }

    return false;
}

/// get_fighter_gobj(FighterKind)
HSD_GObj* ftBossLib_8015C3E8(FighterKind kind)
{
    HSD_GObj* cur;

    u8 _[8];

    for (cur = HSD_GObj_Entities->fighters; cur; cur = cur->next) {
        if (kind == ftLib_800872A4(cur)) {
            return cur;
        }
    }

    return NULL;
}

enum_t ftBossLib_8015C44C(FighterKind kind)
{
    HSD_GObj* gobj = ftBossLib_8015C3E8(kind);

    u8 _[16];

    if (gobj != NULL) {
        // DataOffset_MotionStateLoad
        return ftLib_80086C0C(gobj);
    } else {
        return ftCo_MS_DeadDown;
    }
}

enum_t ftBossLib_8015C4C4(void)
{
    HSD_GObj* gobj = ftBossLib_8015C3E8(FTKIND_CREZYH);

    u8 _[24];

    if (gobj) {
        return GET_FIGHTER(gobj)->fv.mh.x2250;
    }

    return 0;
}

s32 ftBossLib_8015C530(int cpu_level)
{
    HSD_GObj* gobj = ftBossLib_8015C3E8(FTKIND_MASTERH);

    u8 _[16];

    if (gobj != NULL) {
        ftMasterHand_SpecialAttrs* ftCo_DatAttrs =
            GET_FIGHTER(gobj)->ft_data->ext_attr;
        switch (cpu_level) {
        case 0:
            return ftCo_DatAttrs->x0;
        case 1:
            return ftCo_DatAttrs->x4;
        case 2:
            return ftCo_DatAttrs->x8;
        case 3:
            return ftCo_DatAttrs->xC;
        case 4:
            return ftCo_DatAttrs->x10;
        case 6:
        default:
            return ftCo_DatAttrs->x14;
        }
    } else {
        return 0;
    }
}

void ftBossLib_8015C5F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (HSD_Randi(4)) {
    case 0:
        ft_PlaySFX(fp, 0x4E21A, 0x7F, 0x40);
        return;
    case 1:
        ft_PlaySFX(fp, 0x4E21B, 0x7F, 0x40);
        return;
    case 2:
        ft_PlaySFX(fp, 0x4E21C, 0x7F, 0x40);
        return;
    case 3:
        ft_PlaySFX(fp, 0x4E21D, 0x7F, 0x40);
        return;
    }
}

ftMasterHand_SpecialAttrs* ftBossLib_8015C6BC(void)
{
    u8 _[16];

    {
        HSD_GObj* gobj = ftBossLib_8015C3E8(FTKIND_MASTERH);
        if (gobj == NULL) {
            return NULL;
        }

        {
            /// @todo Can be #GET_FIGHTER when inlines are fixed.
            Fighter* fp = gobj->user_data;
            if (fp == NULL) {
                return NULL;
            }

            {
                ftMasterHand_SpecialAttrs* ftCo_DatAttrs =
                    fp->ft_data->ext_attr;
                if (ftCo_DatAttrs == NULL) {
                    return NULL;
                }

                return ftCo_DatAttrs;
            }
        }
    }
}

s32 ftBossLib_8015C74C(void)
{
    u8 _[24];

    ftMasterHand_SpecialAttrs* da = ftBossLib_8015C6BC();
    if (da == NULL) {
        return -1;
    }

    return da->x164;
}

s32 ftBossLib_8015C7EC(void)
{
    u8 _[24];

    ftMasterHand_SpecialAttrs* da = ftBossLib_8015C6BC();
    if (da == NULL) {
        return -1;
    }

    return da->x168;
}

s32 ftBossLib_8015C88C(void)
{
    u8 _[24];

    ftMasterHand_SpecialAttrs* da = ftBossLib_8015C6BC();
    if (da == NULL) {
        return -1;
    }

    return da->x16C;
}

s32 ftBossLib_8015C92C(void)
{
    u8 _[24];

    ftMasterHand_SpecialAttrs* da = ftBossLib_8015C6BC();
    if (da == NULL) {
        return -1;
    }

    return da->x170;
}

s32 ftBossLib_8015C9CC(void)
{
    u8 _[24];

    ftMasterHand_SpecialAttrs* da = ftBossLib_8015C6BC();
    if (da == NULL) {
        return -1;
    }

    return da->x174;
}

static void func_8015CA6C_inline(s32 arg0)
{
    HSD_GObj* ch_gobj = ftBossLib_8015C3E8(FTKIND_CREZYH);
    if (ch_gobj) {
        ftLib_80086A4C(ch_gobj, arg0);
    }
}

void ftBossLib_8015CA6C(s32 arg0)
{
    u8 _[32];

    Player_80036790(0, arg0);

    {
        HSD_GObj* mh_gobj = ftBossLib_8015C3E8(FTKIND_MASTERH);
        if (mh_gobj) {
            ftLib_80086A4C(mh_gobj, arg0);
        }
    }

    func_8015CA6C_inline(arg0);
    it_8026C3FC();
}

void ftBossLib_8015CB7C(void)
{
    it_8026C42C();
}

static void func_8015CB9C_inline(Vec3 spC)
{
    ftMasterHand_SpecialAttrs* da = ftBossLib_8015C6BC();
    spC.z += da == NULL ? -1 : da->x178;
    Camera_8002EA64(&spC);
    Camera_8002F0E4(0xA);
}

void ftBossLib_8015CB9C(s32 arg0)
{
    Vec3 vec;
    Player_LoadPlayerCoords(arg0, &vec);
    Camera_8002E818(&vec);
    func_8015CB9C_inline(vec);
}

void ftBossLib_8015CC14(void)
{
    Camera_8002F474();
}
