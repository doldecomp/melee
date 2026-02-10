#include "ftCo_0A01.h"

#include "ftpickupitem.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/chara/ftPopo/ftPp_1211.h"
#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftcpuattack.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"
#include "ftDonkey/forward.h"
#include "ftKoopa/forward.h"
#include "ftMewtwo/forward.h"
#include "ftPopo/forward.h"
#include "ftSamus/forward.h"

#include "gm/gm_unsplit.h"
#include "gr/grbigblue.h"
#include "gr/grcorneria.h"
#include "gr/grinishie1.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/grvenom.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lb_00CE.h"
#include "lb/lbcollision.h"
#include "mp/mpisland.h"
#include "mp/mplib.h"
#include "mp/types.h"
#include "pl/player.h"

#include <math.h>
#include <math_ppc.h>
#include <dolphin/mtx.h>
#include <melee/ft/ftcmdscript.h>
#include <MetroTRK/intrinsics.h>

/**
 * Priority table, mapping ItemKind to priority number,
 * for which items the CPU should prefer to target.
 * Higher numbers are preferred.
 */
int ftCo_803C5A68[] = {
    1, 0, 0, 1, 0, 0, 0, 1, 7, 6, 5, 4, 4, 3, 1, 1, 2, 1,
    5, 2, 2, 2, 3, 3, 3, 4, 0, 0, 8, 4, 1, 4, 4, 5, 5,
};

typedef struct ftCo_803C6594_t {
    /* 00 */ Vec3 x0;
    /* 0C */ f32 xC;
    /* 10 */ f32 x10;
    /* 14 */ f32 x14;
    /* 18 */ f32 x18;
    /* 1C */ f32 x1C;
    /* 20 */ f32 x20;
    /* 24 */ f32 x24;
    /* 28 */ f32 x28;
    /* 2C */ f32 x2C;
    /* 30 */ f32 x30;
    /* 34 */ f32 x34;
    /* 38 */ f32 x38;
    /* 3C */ f32 x3C;
    /* 40 */ f32 x40;
    /* 44 */ u8 x44;
    /* 48 */ f32 x48;
    /* 4C */ f32 x4C;
    /* 50 */ struct ftCo_803C6594_t* next;
} ftCo_803C6594_t;

/* static */ extern ftCo_803C6594_t* ftCo_803C6594[];
/* 0A2638 */ static void ftCo_800B1DA0(Fighter* fp);

void ftCo_800A0148(Fighter* fp)
{
    struct Fighter_x1A88_t* x1A88 = &fp->x1A88;

    if (fp->cur_pos.y + x1A88->x558 > Stage_GetBlastZoneTopOffset()) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (ABS(x1A88->x54.x - fp->cur_pos.x) > 30.0) {
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickTowardDestination, 0x7F);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800A0384(Fighter* fp)
{
    if (fp->cur_pos.y + fp->x1A88.x558 > Stage_GetBlastZoneTopOffset()) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x7F);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800A0508(Fighter* fp)
{
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B463C(fp, CpuCmd_PressY);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);

    ftCo_800B463C(fp, CpuCmd_ReleaseY);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 30);

    ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x50);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
    ftCo_800B463C(fp, CpuCmd_PressR);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);

    ftCo_800B463C(fp, CpuCmd_ReleaseR);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B463C(fp, CpuCmd_Done);

    ftCo_800B463C(fp, CpuCmd_Done);
}

static inline void ftCo_800A0508_dontinline(Fighter* fp)
{
    ftCo_800A0508(fp);
}

void ftCo_800A05F4(Fighter* fp)
{
    if (fp->cur_pos.y + fp->x1A88.x558 > Stage_GetBlastZoneTopOffset()) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickTowardFighter, 0x7F);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800A0798(Fighter* fp)
{
    if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardFighter, 0x7F);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800A08F0(Fighter* fp)
{
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    if (fp->motion_id == ftCo_MS_SquatRv || fp->motion_id == ftCo_MS_Squat ||
        fp->motion_id == ftCo_MS_SquatWait)
    {
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (fp->kind == FTKIND_NANA) {
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, -0x7F);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    switch (fp->x1A88.level) {
    case 0:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 45);
        break;
    case 1:
    case 2:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 30);
        break;
    case 3:
    case 4:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 15);
        break;
    case 5:
    case 6:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
        break;
    case 7:
    case 8:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
        break;
    case 9:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        break;
    }
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, -0x7F);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
    ftCo_800B463C(fp, CpuCmd_Done);
}

void ftCo_800A0AF4(Fighter* fp)
{
    float rand = HSD_Randf();
    if (rand < 0.6f) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x50);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (rand < 0.8f) {
        ftCo_800B463C(fp, CpuCmd_ReleaseR);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressR);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseR);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (rand < 0.9f) {
        ftCo_800B463C(fp, CpuCmd_ReleaseA);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressA);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseA);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800A0C8C(Fighter* fp)
{
    ftCo_800B463C(fp, 127);
}

void ftCo_800A0CB0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->x1A88.x7C % 600 == 0) {
        float x = HSD_Randf();
        float rand;
        x = x * x * x;
        rand = 1.0F - x;
        switch (fp->kind) {
        case FTKIND_DONKEY:
        case FTKIND_KOOPA:
            data->x56C = 9.0 * rand;
            return;
        case FTKIND_GKOOPS:
            data->x56C = 18.0 * rand;
            return;
        case FTKIND_NANA:
            data->x56C = 1.0 * rand;
            return;
        default:
            data->x56C = 4.0 * rand;
            return;
        }
    }
}

void ftCo_800A0DA4(Fighter* fp)
{
    int i;
    FighterHurtCapsule* hurt;
    struct Fighter_x1A88_t* temp_r28;

    float scale;
    float dx;
    float var_f31;
    float var_f30;
    float var_f29;
    float dy;

    temp_r28 = &fp->x1A88;
    var_f30 = var_f31 = var_f29 = 0.0F;
    for (i = 0; i < fp->hurt_capsules_len; i++) {
        hurt = &fp->hurt_capsules[i];
        lbColl_800083C4(&hurt->capsule);

        dx = hurt->capsule.a_pos.x - fp->cur_pos.x;
        dy = hurt->capsule.a_pos.y - fp->cur_pos.y;

        scale = hurt->capsule.scale * fp->x34_scale.y;

        if (var_f31 > dx - scale) {
            var_f31 = dx - scale;
        }
        if (var_f30 < dx + scale) {
            var_f30 = dx + scale;
        }
        if (var_f29 < dy + scale) {
            var_f29 = dy + scale;
        }

        dx = hurt->capsule.b_pos.x - fp->cur_pos.x;
        dy = hurt->capsule.b_pos.y - fp->cur_pos.y;

        if (var_f31 > dx - scale) {
            var_f31 = dx - scale;
        }
        if (var_f30 < dx + scale) {
            var_f30 = dx + scale;
        }
        if (var_f29 < dy + scale) {
            var_f29 = dy + scale;
        }
    }
    if (fp->facing_dir > 0.0) {
        temp_r28->x55C = var_f30;
        temp_r28->x560 = -var_f31;
    } else {
        temp_r28->x55C = -var_f31;
        temp_r28->x560 = var_f30;
    }
    temp_r28->x564 = 0.5 * (temp_r28->x55C + temp_r28->x560);
    temp_r28->x568 = var_f29;
}

bool ftCo_800A0F00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (ft_80087A18(gobj)) {
        int result = ft_80087A80(gobj);
        if (result == 2) {
            return true;
        }
        if (result == 1) {
            if (data->x7C % 240 > 120) {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

bool ftCo_800A0FB0(Vec3* vec_out, int* line_id_out, u32* flags_out,
                   Vec3* normal_out, int arg4, int arg5, int arg6, float arg7,
                   float arg8, float arg9, float arg10, float arg11)
{
    *line_id_out = -1;
    {
        int ret =
            mpCheckFloor(arg7, arg8, arg9, arg10, arg11, vec_out, line_id_out,
                         flags_out, normal_out, arg4, arg5, arg6, NULL, NULL);
        if (ret && ftCo_800A1B38(*line_id_out)) {
            return false;
        }
        return ret;
    }
}

void ftCo_800A101C(Fighter* arg0, int arg1, int arg2, int arg3)
{
    Vec3 sp50;
    Vec3 sp44;

    s32 var_r31;
    struct Fighter_x1A88_t* temp_r30;
    Fighter* temp_r3_2;
    f32 temp_f0;
    f32 temp_f0_3;
    f32 temp_f1;
    f32 temp_f3_2;
    s32 temp_r6;
    s32 var_r0;
    int i;

    int sp34;
    u32 sp30;

    PAD_STACK(0xC);

    temp_r30 = &arg0->x1A88;
    if (arg0->kind == FTKIND_NANA) {
        temp_r30->xF9_b2 = true;
        temp_r30->xC = 6;
        temp_r30->x3C = 15.0f;
    } else {
        temp_r30->xC = arg1;
        temp_r30->x3C = 40.0f;
    }
    temp_r30->level = arg2;
    temp_r30->x14 = arg3;
    switch (temp_r30->xC) {
    case 1:
    case 25:
        temp_r30->x18 = 0xC;
        temp_r30->x1C = 0xC;
        temp_r30->x20 = 0;
        break;
    case 3:
        temp_r30->x18 = 1;
        temp_r30->x1C = 1;
        temp_r30->x20 = 0xB;
        break;
    case 15:
        temp_r30->x18 = 0;
        temp_r30->x1C = 0;
        temp_r30->x20 = 0;
        break;
    default:
        temp_r30->x18 = 1;
        temp_r30->x1C = 1;
        temp_r30->x20 = 0xA;
        break;
    }
    temp_r30->x24 = 0x12C;
    temp_r30->x28 = 0;
    temp_r30->x2C = 5;
    temp_r30->x30 = 0;
    temp_r30->xF9_b0 = false;
    temp_r30->x38 = 5.0f;
    temp_r30->x40 = 50.0f;
    temp_r30->x44 = NULL;
    temp_r30->x48 = 0;
    temp_r30->x50 = 0;
    temp_r30->x98 = arg0->cur_pos;
    if (ftCo_800A0FB0(&sp50, &sp34, &sp30, &sp44, -1, -1, -1, arg0->cur_pos.x,
                      10.0f + arg0->cur_pos.y, arg0->cur_pos.x,
                      arg0->cur_pos.y - 1000.0f, 0.0f))
    {
        temp_r30->x64.x = temp_r30->x54.x = sp50.x;
        temp_r30->x64.y = temp_r30->x54.y = sp50.y;
    } else {
        temp_r30->x64.x = temp_r30->x54.x = arg0->cur_pos.x;
        temp_r30->x64.y = temp_r30->x54.y = arg0->cur_pos.y;
    }
    temp_r30->x60 = 0;
    temp_r30->x74.y = 0.0f;
    temp_r30->x74.x = 0.0f;
    temp_r30->x6C.y = 0.0f;
    temp_r30->x6C.x = 0.0f;
    temp_r30->xF8_b0 = false;
    temp_r30->xF8_b12 = 0;
    temp_r6 = 10.0 * HSD_Randf();
    temp_r30->x7C = temp_r6;
    temp_r30->x80 = temp_r6;
    temp_r30->x84 = 0;
    temp_r30->x90 = 0;
    temp_r30->x88 = 0;
    temp_r30->x8C = 0;
    temp_r30->csP = NULL;
    temp_r30->command_duration = 0;
    temp_r30->write_pos = temp_r30->buffer;
    temp_r30->xA4 = 0;
    temp_r30->xC8 = 0;
    temp_r30->xEC = 0;
    temp_r30->xF8_b5 = false;
    temp_r30->xF8_b6 = false;
    temp_r30->xF8_b7 = false;
    temp_r30->xF9_b1 = false;
    temp_r30->x0 = 0;
    temp_r30->lstickX = 0;
    temp_r30->lstickY = 0;
    temp_r30->cstickX = 0;
    temp_r30->cstickY = 0;
    temp_r30->rtrigger = 0;
    temp_r30->ltrigger = 0;
    temp_r30->xF9_b2 = false;
    temp_r30->xF9_b3 = false;
    temp_r30->xF9_b4 = false;
    temp_r30->xF9_b6 = false;
    temp_r30->xF9_b5 = false;
    temp_r30->xF9_b7 = false;
    temp_r30->xFA_b7 = false;
    temp_r30->xFB_b0 = false;
    temp_r30->x94 = 0;
    temp_r30->xFA_b1 = false;
    temp_r30->xFA_b2 = false;
    temp_r30->xFA_b34 = 1;
    temp_r30->xFA_b5 = false;
    temp_r30->xFA_b6 = false;
    temp_r30->x55C = 1.0f;
    temp_r30->x560 = 1.0f;
    temp_r30->x564 = 0.5f * (temp_r30->x55C + temp_r30->x560);
    temp_r30->x568 = 2.0f;
    temp_r30->x444 = &temp_r30->xFC[5];
    temp_r30->x448 = temp_r30->xFC;
    if (arg0->kind == FTKIND_NANA) {
        temp_r3_2 = ftCo_800A589C(arg0);
        for (i = 0; i < 30; i++) {
            temp_r30->xFC[i].x0 = 0;
            temp_r30->xFC[i].lstickX = 0;
            temp_r30->xFC[i].lstickY = 0;
            temp_r30->xFC[i].x4 = 0;
            temp_r30->xFC[i].x5 = 0;
            temp_r30->xFC[i].cur_pos = temp_r3_2->cur_pos;
            temp_r30->xFC[i].facing_dir = temp_r3_2->facing_dir;
        }
    } else {
        for (i = 0; i < 30; i++) {
            temp_r30->xFC[i].x0 = 0;
            temp_r30->xFC[i].lstickX = 0;
            temp_r30->xFC[i].lstickY = 0;
            temp_r30->xFC[i].x4 = 0;
            temp_r30->xFC[i].x5 = 0;
            temp_r30->xFC[i].cur_pos.x = 0.0F;
            temp_r30->xFC[i].cur_pos.y = 0.0F;
            temp_r30->xFC[i].cur_pos.z = 0.0F;
            temp_r30->xFC[i].facing_dir = 1.0F;
        }
    }
    temp_f3_2 = arg0->co_attrs.grav;
    temp_f1 = arg0->co_attrs.jump_v_initial_velocity *
              arg0->co_attrs.air_jump_v_multiplier;
    if ((temp_f3_2 < 0.00001f) && (temp_f3_2 > -0.00001f)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        temp_r30->x558 = 10.0f;
    } else {
        temp_r30->x558 = temp_f1 * temp_f1 / (2.0 * temp_f3_2);
    }
    temp_r30->half_width = 10.0f;
    temp_r30->half_height = 10.0f;
    temp_r30->x570 = 1.0f;
    ftCo_800B9704(arg0);
    switch (arg0->kind) {
    case FTKIND_DONKEY:
    case FTKIND_KOOPA:
        temp_r30->x56C = 8.5f;
        break;
    case FTKIND_GKOOPS:
        temp_r30->x56C = 17.0f;
        break;
    case FTKIND_NANA:
        temp_r30->x56C = 1.0f;
        break;
    default:
        temp_r30->x56C = 3.5f;
        break;
    }
}

float ftCo_800A17E4(Fighter* fp)
{
    float result;
    if (fp->x1A88.lstickX > 0) {
        result = fp->x1A88.lstickX / 127.0F;
    } else {
        result = fp->x1A88.lstickX / 128.0F;
    }
    if (result > 1.0) {
        return 1.0;
    } else if (result < -1.0) {
        return -1.0;
    }
    return result;
}

static inline float inlineB0(s8 val, float a, float b)
{
    float ret = val > 0 ? val / a : val / b;
    return ret > +1.0 ? +1.0F : ret < -1.0 ? -1.0F : ret;
}

float ftCo_800A1874(Fighter* fp)
{
    return inlineB0(fp->x1A88.lstickY, 127.0f, 128.0F);
}

float ftCo_800A1904(Fighter* fp)
{
    float ret = fp->x1A88.ltrigger / 255.0;
    return ret > 1.0 ? 1.0F : ret;
}

float ftCo_800A1948(Fighter* fp)
{
    float ret = fp->x1A88.rtrigger / 255.0;
    return ret > 1.0 ? 1.0F : ret;
}

HSD_Pad ftCo_800A198C(Fighter* fp)
{
    return fp->x1A88.x0;
}

float ftCo_800A1994(Fighter* fp)
{
    return inlineB0(fp->x1A88.cstickX, 127.0F, 128.0F);
}

float ftCo_800A1A24(Fighter* fp)
{
    return inlineB0(fp->x1A88.cstickY, 127.0F, 128.0F);
}

/// Compute 2D distance between two fighters
f32 ftCo_800A1AB4(Fighter* fp0, Fighter* fp1)
{
    float dx = fp0->cur_pos.x - fp1->cur_pos.x;
    float dy = fp0->cur_pos.y - fp1->cur_pos.y;
    return sqrtf(SQ(dx) + SQ(dy));
}

bool ftCo_800A1B38(enum_t arg0)
{
    if (grBigBlue_801EF844(arg0) || grInishie1_801FCAAC(arg0) ||
        grCorneria_801E2D90(arg0) || grVenom_80206D10(arg0))
    {
        return true;
    }
    return false;
}

bool ftCo_800A1BA8(Fighter* fp)
{
    Fighter* other_fp = fp->x1A88.x44;
    if (other_fp == NULL) {
        return false;
    }
    {
        Vec3 coll_vec;
        Vec3 sp14;
        int sp10;
        u32 spC;
        if (fp->facing_dir > 0.0) {
            return mpCheckRightWall(fp->cur_pos.x, fp->cur_pos.y,
                                    other_fp->cur_pos.x, other_fp->cur_pos.y,
                                    &coll_vec, &sp10, &spC, &sp14, -1, -1);
        }
        return mpCheckLeftWall(fp->cur_pos.x, fp->cur_pos.y,
                               other_fp->cur_pos.x, other_fp->cur_pos.y,
                               &coll_vec, &sp10, &spC, &sp14, -1, -1);
    }
}

bool ftCo_800A1C44(Fighter* fp)
{
    if (fp->x2219_b1) {
        return true;
    }
    if (fp->x2164 != 0) {
        return true;
    }
    if (fp->x2168 != 0 && fp->x2338.x == 0) {
        return true;
    }
    if (fp->x221F_b3) {
        return true;
    }
    return false;
}

bool ftCo_800A1CA8(Fighter* fp)
{
    return fp->x2168 ? true : false;
}

static inline bool ftCo_800A1CC4_inline0(Fighter* fp, ftCo_803C6594_t* var_r29,
                                         mp_UnkStruct0* temp_r3)
{
    if (mpIsland_8005AC14(&var_r29->x0, -10.0F) == temp_r3) {
        if (var_r29->x44 != 0) {
            float temp_f1 = fp->cur_pos.x;
            if (temp_f1 > var_r29->x48 && temp_f1 < var_r29->x4C) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

static inline void ftCo_800A1CC4_inline1(Fighter* fp, float x, float y)
{
    fp->x1A88.x60 = 0x12C;
    fp->x1A88.x64.x = fp->x1A88.x54.x;
    fp->x1A88.x64.y = fp->x1A88.x54.y;
    fp->x1A88.x54.x = x;
    fp->x1A88.x54.y = y;
    fp->x1A88.x38 = 5.0F;
}

static void ftCo_800A1CC4(Fighter* fp, ftCo_803C6594_t* var_r29)
{
    struct Fighter_x1A88_t* data;

    PAD_STACK(0x10);

    data = &fp->x1A88;
    if (var_r29 != NULL && data->x60 == 0 && data->xC != 0 &&
        fp->ground_or_air != GA_Air && !ftCo_800A21FC(fp))
    {
        mp_UnkStruct0* temp_r3 = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (temp_r3 != NULL) {
            float dy = data->x54.y - fp->cur_pos.y;
            float angle = lb_8000D008(dy, ABS(data->x54.x - fp->cur_pos.x));
            for (; var_r29 != NULL; var_r29 = var_r29->next) {
                if (!ftCo_800A1CC4_inline0(fp, var_r29, temp_r3)) {
                    continue;
                }
                if (angle > var_r29->x3C) {
                    if (var_r29->x14 >= 0.0F) {
                        ftCo_800A1CC4_inline1(fp, var_r29->xC, var_r29->x10);
                        return;
                    }
                } else if (angle < var_r29->x40) {
                    if (var_r29->x20 >= 0.0F) {
                        ftCo_800A1CC4_inline1(fp, var_r29->x18, var_r29->x1C);
                        return;
                    }
                } else if (fp->facing_dir > 0.0F) {
                    if (var_r29->x2C >= 0.0F) {
                        ftCo_800A1CC4_inline1(fp, var_r29->x24, var_r29->x28);
                        return;
                    }
                } else {
                    if (var_r29->x38 >= 0.0F) {
                        ftCo_800A1CC4_inline1(fp, var_r29->x30, var_r29->x34);
                        return;
                    }
                }
            }
        }
    }
}

void ftCo_800A1F3C(Fighter* fp, float arg1, float arg2, float arg3)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->x1A88.x60 == 0) {
        data->x54.x = arg1;
        data->x54.y = arg2;
        data->x38 = arg3;
        ftCo_800A1CC4(fp, ftCo_803C6594[stage_info.internal_stage_id]);
    }
}

bool ftCo_800A1F98(int x, float y)
{
    float slope;
    float intercept;
    PAD_STACK(1 * 4);

    if (stage_info.internal_stage_id != ZEBES) {
        return false;
    }
    Ground_801C4368(&slope, &intercept);
    if (y < slope) {
        return true;
    }
    if (y < intercept * x + slope) {
        return true;
    }
    return false;
}

bool ftCo_800A2040(Fighter* fp)
{
    if (Player_8003248C(fp->player_id, fp->x221F_b4) != Gm_PKind_Cpu) {
        return false;
    }
    if (fp->x1A88.xC == 5) {
        return false;
    }
    return true;
}

void ftCo_800A20A0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(2 * 4);

    if (fp->x1A88.x44 != NULL && fp->ground_or_air == GA_Ground) {
        Fighter* other_fp = data->x44;

        if (ftCo_800A1AB4(fp, other_fp) <
            2.0f * M2C_FIELD(Fighter_804D64FC, float**, 0x20)[fp->kind])
        {
            data->xF8_b6 = true;
        } else {
            data->xF8_b6 = false;
        }
    } else {
        data->xF8_b6 = false;
    }
}

static inline void ftCo_800A20A0_dontinline(Fighter* fp)
{
    ftCo_800A20A0(fp);
}

bool ftCo_800A2170(Fighter* fp0, Fighter* fp1)
{
    mp_UnkStruct0* temp_r3;

    if (fp0->ground_or_air == GA_Air) {
        return false;
    }
    if (fp1->ground_or_air == GA_Air) {
        return false;
    }
    temp_r3 = mpIsland_8005AB54(fp0->coll_data.floor.index);
    if (temp_r3 == NULL) {
        return false;
    }
    if (mpIsland_8005AB54(fp1->coll_data.floor.index) == temp_r3) {
        return true;
    }
    return false;
}

bool ftCo_800A21FC(Fighter* fp)
{
    Vec3 vec;
    mp_UnkStruct0* data0;
    struct Fighter_x1A88_t* data1 = &fp->x1A88;
    PAD_STACK(9 * 4);

    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    data0 = mpIsland_8005AB54(fp->coll_data.floor.index);
    if (data0 == NULL) {
        return false;
    }
    vec.x = data1->x54.x;
    vec.y = 5.0 + data1->x54.y;
    vec.z = 0.0f;
    if (mpIsland_8005AC14(&vec, -10.0f) == data0) {
        return true;
    }
    return false;
}

/// #ftCo_800A229C

static inline bool inlineL0(mp_UnkStruct0* arg0)
{
    Item_GObj* cur;
    s32 temp_cr0_eq;
    s32 var_r0;
    Item* cur_ip;
    cur = HSD_GObj_Entities->items;
    goto loop_8;
block_3:
    cur_ip = GET_ITEM(cur);
    if (it_8026C1B4(cur) == 0) {
        goto block_7;
    }
    if (!ftCo_800A5944(cur_ip)) {
        goto block_7;
    }
    if (arg0 != mpIsland_8005AB54(cur_ip->x378_itemColl.floor.index)) {
        goto block_7;
    }
    return 1;
block_7:
    cur = cur->next;
loop_8:
    if (cur != NULL) {
        goto block_3;
    }
    if (stage_info.internal_stage_id == STORY) {
        goto block_15;
    }
    if (stage_info.internal_stage_id >= 0xA) {
        goto block_13;
    }
    if (stage_info.internal_stage_id == ZEBES) {
        goto block_16;
    }
    goto block_37;
block_13:
    temp_cr0_eq = stage_info.internal_stage_id == ONETT;
    if (temp_cr0_eq != 0) {
        goto block_21;
        goto block_37;
    block_15:
        return mpIsland_8005AC8C(arg0);
    block_16:
        if (ftCo_800A1F98(0x5A, arg0->x14.y) != 0) {
            return 1;
        }
        if (ftCo_800A1F98(0x5A, arg0->x8.y) != 0) {
            return 1;
        }
        return 0;
    }
block_21:
    if (temp_cr0_eq == 0) {
        return 0;
    }
    if (arg0->x14.y <= 5.0 || Ground_801C5794() == 0) {
        return 0;
    }
    return 1;
block_37:
    return 0;
}

static inline bool inlineL1(mp_UnkStruct0* arg0)
{
    if (stage_info.internal_stage_id != ONETT) {
        return false;
    }
    if (!(arg0->x8.y <= 5.0)) {
        if (Ground_801C5794() != 0) {
            return true;
        }
    }
    return false;
}

bool ftCo_800A2718(mp_UnkStruct0* arg0)
{
    PAD_STACK(4 * 4);
    if (arg0 == NULL) {
        return 0;
    }
    if (!inlineL0(arg0) && !inlineL1(arg0)) {
        return 0;
    }
    return 1;
}

bool ftCo_800A28D0(Fighter* fp, float arg1)
{
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (data == NULL) {
            return false;
        }
        {
            float x_offset;
            if (fp->facing_dir > 0.0) {
                x_offset = ABS(data->x14.x - fp->cur_pos.x);
            } else {
                x_offset = ABS(data->x8.x - fp->cur_pos.x);
            }
            if (x_offset < (5.0 * arg1)) {
                return true;
            }
        }
    }
    return false;
}

bool ftCo_800A2998(Fighter* fp, float arg1)
{
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (data == NULL) {
            return false;
        }
        {
            float diff_x8, diff_x14;
            diff_x14 = ABS(data->x14.x - fp->cur_pos.x);
            diff_x8 = ABS(data->x8.x - fp->cur_pos.x);
            if (diff_x14 < diff_x8) {
                if (diff_x14 < 5.0 * arg1) {
                    return true;
                }
                return false;
            }
            if (diff_x8 < 5.0 * arg1) {
                return true;
            }
        }
    }
    return false;
}

float ftCo_800A2A70(Fighter* fp, bool arg1)
{
    if (fp->ground_or_air == GA_Air) {
        return -1.0f;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (data == NULL) {
            return -1.0f;
        }
        {
            float r;
            if (arg1) {
                float x = data->x8.x - fp->cur_pos.x,
                      y = data->x8.y - fp->cur_pos.y;
                r = sqrtf(SQ(x) + SQ(y));
            } else {
                float x = data->x14.x - fp->cur_pos.x,
                      y = data->x14.y - fp->cur_pos.y;
                r = sqrtf(SQ(x) + SQ(y));
            }
            return r;
        }
    }
}

bool ftCo_800A2BD4(Fighter* fp)
{
    return fp->facing_dir * (fp->x1A88.x54.x - fp->cur_pos.x) >= 0.0 ? true
                                                                     : false;
}

bool ftCo_800A2C08(Fighter* fp)
{
    Fighter* other_fp = fp->x1A88.x44;
    if (other_fp == NULL) {
        return true;
    }
    {
        float pos_x_diff = other_fp->cur_pos.x - fp->cur_pos.x;
        if (ABS(pos_x_diff) < 1.0f) {
            return true;
        }
        if (pos_x_diff * fp->facing_dir >= 0.0) {
            return true;
        }
        return false;
    }
}

/// #ftCo_800A2C80

enum_t ftCo_800A3134(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_DownBoundD:
    case ftCo_MS_DownBoundU:
        return 1;
    case ftCo_MS_DownWaitD:
    case ftCo_MS_DownWaitU:
        return 2;
    default:
        return 0;
    }
}

bool ftCo_IsGrabbing(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_CatchWait) {
        return true;
    }
    if (fp->kind == FTKIND_DONKEY) {
        if (fp->motion_id >= ftDk_MS_ThrowFWait0 &&
            fp->motion_id <= ftDk_MS_ThrowFKneebend)
        {
            return true;
        }
    }
    if (fp->kind == FTKIND_KOOPA || fp->kind == FTKIND_GKOOPS) {
        if (fp->motion_id == ftKp_MS_SpecialSHit0_1) {
            return true;
        }
    }
    if (fp->kind == FTKIND_KIRBY) {
        if (fp->motion_id >= ftKb_MS_SpecialNCapture0 &&
            fp->motion_id <= ftKb_MS_EatTurnAir)
        {
            return true;
        }
    }
    return false;
}

bool ftCo_800A3200(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_CliffCatch:
        return 1;
    case ftCo_MS_CliffWait:
        return 2;
    default:
        return 0;
    }
}

bool ftCo_800A3234(Fighter* fp)
{
    Vec3 sp34;
    Vec3 sp28;

    bool var_r0;
    struct Fighter_x1A88_t* temp_r31;

    PAD_STACK(0xC);

    temp_r31 = &fp->x1A88;
    if (fp->x1A88.xFA_b6) {
        if (fp->pos_delta.y < 0.1f) {
            return true;
        }
        return false;
    }
    if (fp->ground_or_air != GA_Air) {
        return false;
    }
    if (fp->pos_delta.y > 0.0) {
        return false;
    }
    if (fp->motion_id == 0xF4) {
        return false;
    }
    if (fp->kind == FTKIND_YOSHI && fp->x34_scale.y > 1.0F &&
        temp_r31->x7C < 0x384)
    {
        return false;
    }
    if (lb_8000D008(temp_r31->x54.y - fp->cur_pos.y,
                    ABS(temp_r31->x54.x - fp->cur_pos.x)) < -1.3089969f)
    {
        return false;
    }
    if (fp->facing_dir > 0.0f) {
        if (fp->coll_data.env_flags & Collide_LeftWallMask) {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
    } else if (fp->coll_data.env_flags & Collide_RightWallMask) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        return true;
    }

    {
        int sp18;
        u32 sp14;
        float topn_x = fp->coll_data.last_pos.x;
        float topn_y = fp->coll_data.last_pos.y;
        float bottom_x = fp->coll_data.ecb.bottom.x;
        float bottom_y = fp->coll_data.ecb.bottom.y;
        float y = fp->coll_data.last_pos.y + bottom_y;
        if (ftCo_800A0FB0(&sp34, &sp18, &sp14, &sp28, -1, -1, -1,
                          topn_x + bottom_x, topn_y + bottom_y,
                          fp->coll_data.cur_pos.x + bottom_x,
                          fp->coll_data.cur_pos.y + bottom_y, 0.0f))
        {
            return false;
        }
        if (temp_r31->x54.y > y) {
            return true;
        }
    }
    return false;
}

static inline bool inlineC0(Fighter* fp)
{
    if (fp->coll_data.env_flags & Collide_WallMask) {
        return true;
    } else {
        return false;
    }
}

bool ftCo_800A3498(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r4 = &fp->x1A88;
    if (fp->x1A88.xFA_b5) {
        return false;
    }
    if (fp->ground_or_air != GA_Air) {
        return false;
    }
    if (fp->pos_delta.y > 0.0) {
        return false;
    }
    if (inlineC0(fp)) {
        return true;
    }
    if (fp->kind == FTKIND_LUIGI) {
        if (fp->pos_delta.y < 0.0) {
            return true;
        }
    } else if (temp_r4->x54.y > temp_r4->x568 + (fp->coll_data.cur_pos.y +
                                                 fp->coll_data.ecb.bottom.y))
    {
        return true;
    }
    return false;
}

bool ftCo_800A3554(Fighter* fp, float arg1)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    if (!ftCo_800A21FC(fp)) {
        return false;
    }
    {
        float x = data->x54.x - fp->cur_pos.x, y = data->x54.y - fp->cur_pos.y;
        if (sqrtf(SQ(x) + SQ(y)) < data->x38 + arg1) {
            if (data->x60 != 0) {
                data->x60 = 0;
                data->x54.x = data->x64.x;
                data->x54.y = data->x64.y;
                ftCo_800A1CC4(fp, ftCo_803C6594[stage_info.internal_stage_id]);
                return false;
            }
            return true;
        }
        return false;
    }
}

/**
 * This appears to be similar to ftCo_800A2170, but for fighter/item args.
 */
static inline bool ftCo_800A2170_it(Fighter* fp, Item* ip)
{
    mp_UnkStruct0* data;
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    if (ip->ground_or_air == GA_Air) {
        return false;
    }
    data = mpIsland_8005AB54(fp->coll_data.floor.index);
    if (data == NULL) {
        return false;
    }
    if (mpIsland_8005AB54(ip->x378_itemColl.floor.index) == data) {
        return true;
    }
    return false;
}

bool ftCo_800A3710(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Item* ip = data->x4C;
    if (!data->xF9_b7) {
        return false;
    }
    if (ip == NULL) {
        return false;
    }
    if (!Item_IsGrabbable(ip->entity)) {
        data->x4C = NULL;
        return false;
    }
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    if (fp->item_gobj != NULL) {
        return false;
    }
    if (!ftCo_800A2170_it(fp, ip)) {
        return false;
    }
    if (ftpickupitem_80094150(fp->gobj, ip->entity)) {
        return true;
    }
    return false;
}

bool ftCo_IsAlly(Fighter* fp0, Fighter* fp1)
{
    if (fp0 == NULL) {
        return false;
    }
    if (fp1 == NULL) {
        return false;
    }
    if (fp0->player_id == fp1->player_id) {
        return true;
    }
    if (gm_8016B168()) {
        if (fp0->team == fp1->team) {
            return true;
        }
        return false;
    }
    if (gm_8016B14C()) {
        return false;
    }
    if (fp0->team == fp1->team) {
        return true;
    }
    return false;
}

static inline bool ftCo_IsAlly_dontinline(Fighter* fp0, Fighter* fp1)
{
    return ftCo_IsAlly(fp0, fp1);
}

/// #ftCo_800A3908

/// #ftCo_800A4038

/// #ftCo_800A4768

void ftCo_800A49B4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    f32 dx = fp->cur_pos.x - data->x54.x;
    f32 dy = fp->cur_pos.y - data->x54.y;
    data->x5C = sqrtf(dx * dx + dy * dy);
}

static inline bool inlineD0(Fighter* fp, Fighter* fp1)
{
    float y, x;
    struct Fighter_x1A88_t* data = &fp->x1A88;

    y = fp1->cur_pos.y;
    x = fp1->cur_pos.x;
    if (x < Stage_GetBlastZoneLeftOffset() + data->half_width ||
        x > Stage_GetBlastZoneRightOffset() - data->half_width ||
        y < Stage_GetBlastZoneBottomOffset() + data->half_height ||
        y > Stage_GetBlastZoneTopOffset() - data->half_height)
    {
        return true;
    }
    return false;
}

static inline bool inlineD0_it(Fighter* fp, Item* it)
{
    float y, x;
    struct Fighter_x1A88_t* data = &fp->x1A88;

    y = it->pos.y;
    x = it->pos.x;
    if (x < Stage_GetBlastZoneLeftOffset() + data->half_width ||
        x > Stage_GetBlastZoneRightOffset() - data->half_width ||
        y < Stage_GetBlastZoneBottomOffset() + data->half_height ||
        y > Stage_GetBlastZoneTopOffset() - data->half_height)
    {
        return true;
    }
    return false;
}

static inline bool inlineD1(Fighter* fp)
{
    Fighter_GObj* gobj = fp->gobj;
    if (fp->x221F_b3 || fp->x2224_b2 || ftCo_800A0F00(gobj) ||
        ftLib_8008732C(gobj))
    {
        return true;
    } else {
        return false;
    }
}

Fighter* ftCo_800A4A40(Fighter* fp)
{
    Fighter* fp1;
    Fighter* cur_fp;
    Fighter_GObj* cur;
    float closest;
    float distance;

    PAD_STACK(8);

    if (fp == NULL) {
        return NULL;
    }
    cur_fp = NULL;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        if (fp->gobj == cur) {
            continue;
        }
        fp1 = GET_FIGHTER(cur);
        if (inlineD0(fp, fp1)) {
            continue;
        }
        if (inlineD1(fp1)) {
            continue;
        }
        if (cur_fp == NULL) {
            cur_fp = fp1;
            closest = ftCo_800A1AB4(fp, fp1);
            continue;
        }
        fp1 = GET_FIGHTER(cur);
        distance = ftCo_800A1AB4(fp, fp1);
        if (closest > distance) {
            closest = distance;
            cur_fp = fp1;
        }
    }
    return cur_fp;
}

/// #ftCo_800A4BEC

/// #ftCo_800A4E8C

/// Returns the closest enemy fighter
Fighter* ftCo_800A50D4(Fighter* fp)
{
    Fighter* cur_fp;
    Fighter* closest_fp;
    HSD_GObj* cur;

    f32 closest;
    f32 distance;

    PAD_STACK(4);

    if (fp == NULL) {
        return NULL;
    }
    closest_fp = NULL;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        // Ignore self
        if (fp->gobj == cur) {
            continue;
        }

        cur_fp = GET_FIGHTER(cur);

        // Ignore fighters outside the blast zones
        if (inlineD0(fp, cur_fp)) {
            continue;
        }

        // Ignore allies
        if (!ftCo_IsAlly_dontinline(fp, cur_fp)) {
            continue;
        }
        if (inlineD1(cur_fp)) {
            continue;
        }

        if (closest_fp == NULL) {
            closest_fp = cur_fp;
            closest = ftCo_800A1AB4(fp, cur_fp);
        } else {
            cur_fp = GET_FIGHTER(cur);
            distance = ftCo_800A1AB4(fp, cur_fp);
            if (closest > distance) {
                closest = distance;
                closest_fp = cur_fp;
            }
        }
    }
    return closest_fp;
}

Fighter* ftCo_800A5294(Fighter* fp, int player_id)
{
    PAD_STACK(2 * 4);
    if (fp == NULL) {
        return NULL;
    }
    {
        Fighter* cur_fp;
        HSD_GObj* cur;
        for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
            if (fp->gobj != cur) {
                cur_fp = GET_FIGHTER(cur);
                if (!inlineD0(fp, cur_fp)) {
                    if (!inlineD1(cur_fp) && cur_fp->player_id == player_id) {
                        return cur_fp;
                    }
                }
            }
        }
    }
    return NULL;
}

static inline Fighter* ftCo_800A5294_dontinline(Fighter* fp, int player_id)
{
    return ftCo_800A5294(fp, player_id);
}

Fighter* ftCo_800A53DC(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31;
    HSD_GObj* var_r30;
    HSD_GObj* var_r30_2;
    Fighter* temp_r29;
    Fighter* temp_r29_3;
    Fighter* var_r28;
    int var_r27;
    Fighter_GObj* temp_r25;
    Fighter* temp_r25_2;
    Fighter_GObj* temp_r25_3;
    Fighter* temp_r25_4;

    f32 temp_f1_3;
    f32 temp_f1_6;
    f32 var_f31;

    temp_r31 = &fp->x1A88;
    if (fp == NULL) {
        return 0;
    }
    var_r28 = NULL;
    if (temp_r31->xFA_b34) {
        for (var_r30 = HSD_GObj_Entities->fighters; var_r30 != NULL;
             var_r30 = var_r30->next)
        {
            if (fp->gobj == var_r30) {
                continue;
            }
            temp_r29 = GET_FIGHTER(var_r30);
            if (inlineD0(fp, temp_r29)) {
                continue;
            }
            if (ftCo_IsAlly_dontinline(fp, temp_r29)) {
                continue;
            }
            if (ftCo_800A1C44(temp_r29)) {
                continue;
            }
            temp_r25 = temp_r29->gobj;
            if (inlineD1(temp_r29)) {
                continue;
            }
            if (ftCo_800A2040(temp_r29)) {
                continue;
            }

            if (var_r28 == NULL) {
                var_r28 = temp_r29;
                var_r27 = gm_8016C6C0(var_r30);
                var_f31 = ftCo_800A1AB4(fp, temp_r29);
            } else {
                int temp_r29_2;
                temp_r25_2 = GET_FIGHTER(var_r30);
                temp_r29_2 = gm_8016C6C0(var_r30);
                temp_f1_3 = ftCo_800A1AB4(fp, temp_r25_2);
                if (var_r27 > temp_r29_2) {
                    var_f31 = temp_f1_3;
                    var_r27 = temp_r29_2;
                    var_r28 = temp_r25_2;
                } else if (var_r27 == temp_r29_2 && var_f31 > temp_f1_3) {
                    var_f31 = temp_f1_3;
                    var_r28 = temp_r25_2;
                }
            }
        }
        if (var_r28 != NULL) {
            return var_r28;
        }
    }
    for (var_r30_2 = HSD_GObj_Entities->fighters; var_r30_2 != NULL;
         var_r30_2 = var_r30_2->next)
    {
        if (fp->gobj == var_r30_2) {
            continue;
        }
        temp_r29_3 = GET_FIGHTER(var_r30_2);
        if (inlineD0(fp, temp_r29_3)) {
            continue;
        }
        if (ftCo_IsAlly_dontinline(fp, temp_r29_3)) {
            continue;
        }
        if (ftCo_800A1C44(temp_r29_3)) {
            continue;
        }
        temp_r25_3 = temp_r29_3->gobj;
        if (inlineD1(temp_r29_3)) {
            continue;
        }
        if (var_r28 == NULL) {
            var_r28 = temp_r29_3;
            var_r27 = gm_8016C6C0(var_r30_2);
            var_f31 = ftCo_800A1AB4(fp, temp_r29_3);
        } else {
            int temp_r29_4;
            temp_r25_4 = GET_FIGHTER(var_r30_2);
            temp_r29_4 = gm_8016C6C0(var_r30_2);
            temp_f1_6 = ftCo_800A1AB4(fp, temp_r25_4);
            if (var_r27 > temp_r29_4) {
                var_f31 = temp_f1_6;
                var_r27 = temp_r29_4;
                var_r28 = temp_r25_4;
            } else if (var_r27 == temp_r29_4 && var_f31 > temp_f1_6) {
                var_f31 = temp_f1_6;
                var_r28 = temp_r25_4;
            }
        }
    }
    return var_r28;
}

Fighter* ftCo_800A589C(Fighter* fp)
{
    if (fp == NULL) {
        return NULL;
    }
    {
        Fighter_GObj* cur;
        for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
            if (fp->gobj != cur) {
                Fighter* cur_fp = GET_FIGHTER(cur);
                if (fp->player_id == cur_fp->player_id) {
                    if (cur_fp->x221F_b3) {
                        return NULL;
                    }
                    return cur_fp;
                }
            }
        }
    }
    return NULL;
}

bool ftCo_800A5908(Item* ip)
{
    if (ip->kind == It_Kind_Heart) {
        return true;
    }
    if (ip->kind == It_Kind_Tomato) {
        return true;
    }
    if (ip->kind == It_Kind_Foods) {
        return true;
    }
    return false;
}

bool ftCo_800A5944(Item* ip)
{
    if (ip->kind == It_Kind_BombHei) {
        return true;
    }
    if (ip->kind == It_Kind_G_Shell) {
        return true;
    }
    if (ip->kind == It_Kind_R_Shell) {
        return true;
    }
    return false;
}

bool ftCo_800A5980(Fighter* fp)
{
    if (fp->motion_id >= ftCo_MS_LandingFallSpecial &&
        fp->motion_id < ftCo_MS_Attack100Start)
    {
        return true;
    }
    if (fp->motion_id == ftCo_MS_Furafura || fp->motion_id == ftCo_MS_Catch ||
        fp->motion_id == ftCo_MS_CatchPull ||
        fp->motion_id == ftCo_MS_CatchAttack)
    {
        return true;
    }
    return false;
}

bool ftCo_800A59C0(Item* ip)
{
    if (ip->xCC_item_attr->x0_78 == 3) {
        return true;
    }
    return false;
}

bool ftCo_800A59E4(Item* ip)
{
    if (ip == NULL) {
        return false;
    }
    if (ip->kind == It_Kind_Harisen || ip->kind == It_Kind_StarRod ||
        ip->kind == It_Kind_LipStick || ip->kind == It_Kind_Bat ||
        ip->kind == It_Kind_Sword || ip->kind == It_Kind_Parasol)
    {
        return true;
    }
    return false;
}

bool ftCo_800A5A28(Item* ip)
{
    switch (ip->kind) {
    case It_Kind_Capsule:
    case It_Kind_BombHei:
    case It_Kind_Dosei:
    case It_Kind_G_Shell:
    case It_Kind_R_Shell:
    case It_Kind_Freeze:
    case It_Kind_MSBomb:
    case It_Kind_Flipper:
    case It_Kind_M_Ball:
        return true;
    default:
        return false;
    }
}

bool ftCo_800A5A5C(Item* ip)
{
    switch (ip->kind) {
    case It_Kind_Box:
    case It_Kind_Taru:
    case It_Kind_Kusudama:
    case It_Kind_TaruCann:
        return true;
    default:
        return false;
    }
}

bool ftCo_800A5A90(Fighter* fp)
{
    if (fp->motion_id >= ftCo_MS_SwordSwing1 &&
        fp->motion_id <= ftCo_MS_StarRodSwingDash)
    {
        return true;
    }
    if (fp->motion_id >= ftCo_MS_LGunShoot &&
        fp->motion_id <= ftCo_MS_ItemScopeAirEndEmpty)
    {
        return true;
    }
    return false;
}

bool ftCo_800A5ACC(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (!data->xF9_b6) {
        return false;
    }
    switch (data->level) {
    case 0:
    case 1:
        return false;
    case 2:
        if (data->x7C % 120 > 0x64) {
            return true;
        }
        return false;
    case 3:
        if (data->x7C % 120 > 0x50) {
            return true;
        }
        return false;
    case 4:
        if (data->x7C % 120 > 0x3C) {
            return true;
        }
        return false;
    case 5:
        if (data->x7C % 120 > 0x28) {
            return true;
        }
        return false;
    case 6:
        if (data->x7C % 120 > 0x1E) {
            return true;
        }
        return false;
    case 7:
        if (data->x7C % 120 > 0x14) {
            return true;
        }
        return false;
    case 8:
        if (data->x7C % 120 > 0xA) {
            return true;
        }
        return false;
    case 9:
        return true;
    }
    return false;
}

Fighter* ftCo_800A5CE0(Fighter* fp)
{
    Fighter* cur_fp;
    Fighter* closest_enemy;
    HSD_GObj* cur;
    bool var_r0_3;

    f32 distance;
    f32 closest;

    PAD_STACK(8);

    if (fp == NULL) {
        return NULL;
    }
    if (ftCo_800A1C44(fp)) {
        return NULL;
    }
    closest_enemy = NULL;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        if (fp->gobj == cur) {
            continue;
        }
        cur_fp = GET_FIGHTER(cur);
        if (inlineD1(cur_fp)) {
            continue;
        }
        if (cur_fp->x221D_b6) {
            var_r0_3 = true;
        } else if (cur_fp->x2168 != 0 && cur_fp->x2338.x == 0) {
            var_r0_3 = true;
        } else {
            var_r0_3 = false;
        }
        if (!var_r0_3) {
            continue;
        }
        if (ftCo_IsAlly_dontinline(fp, cur_fp)) {
            continue;
        }
        if (inlineD0(fp, cur_fp)) {
            continue;
        }
        if (closest_enemy == NULL) {
            closest_enemy = cur_fp;
            closest = ftCo_800A1AB4(fp, cur_fp);
        } else {
            distance = ftCo_800A1AB4(fp, cur_fp);
            if (closest > distance) {
                closest = distance;
                closest_enemy = cur_fp;
            }
        }
    }
    return closest_enemy;
}

static inline float itemDist(Fighter* fp, Item* ip)
{
    float dx, dy;
    if (ip == NULL) {
        return 10000.0F;
    }
    dx = fp->cur_pos.x - ip->pos.x;
    dy = fp->cur_pos.y - ip->pos.y;
    return sqrtf(dx * dx + dy * dy);
}

/// Decide which common item to target
Item* ftCo_800A5F4C(Fighter* fp, ItemKind arg1)
{
    Item* cur_ip;
    Item* closest_ip;
    Item_GObj* cur;
    struct Fighter_x1A88_t* data;

    f32 closest;
    f32 distance;

    data = &fp->x1A88;
    if (fp == NULL) {
        return NULL;
    }
    closest_ip = NULL;
    for (cur = HSD_GObj_Entities->items; cur != NULL; cur = cur->next) {
        /// @todo stupid stack padding hack
        cur_ip = GET_ITEM(cur);
        cur_ip = GET_ITEM(cur);
        cur_ip = GET_ITEM(cur);

        if (!Item_IsGrabbable(cur)) {
            continue;
        }

        /// Passing It_Kind_L_Gun_Ray means to target any common item
        if (arg1 != It_Kind_L_Gun_Ray && cur_ip->kind != arg1) {
            continue;
        }
        if (inlineD0_it(fp, cur_ip)) {
            continue;
        }
        if (cur_ip->kind >= It_Kind_L_Gun_Ray) {
            continue;
        }
        if (ftCo_803C5A68[cur_ip->kind] < data->x2C) {
            continue;
        }

        /// If we don't have a target yet, just pick the first item,
        /// and remember its distance.
        if (closest_ip == NULL) {
            closest_ip = cur_ip;
            closest = itemDist(fp, cur_ip);
            continue;
        }

        /// Skip items with lower priority than the current one
        if (ftCo_803C5A68[cur_ip->kind] < ftCo_803C5A68[closest_ip->kind]) {
            continue;
        }

        distance = itemDist(fp, cur_ip);
        if (closest > distance) {
            closest = distance;
            closest_ip = cur_ip;
        }
    }
    return closest_ip;
}

/// #ftCo_800A61D8

/// #ftCo_800A648C

/// #ftCo_800A6700

/// #ftCo_800A6A98

/// #ftCo_800A6D2C

/// #ftCo_800A6FC4

/// #ftCo_800A75DC

/// #ftCo_800A7AAC

void ftCo_800A80E4(Fighter* fp)
{
    Fighter* other_fp = fp->x1A88.x44;
    if (other_fp != NULL && fp->ground_or_air != GA_Air) {
        f32 dx = fp->cur_pos.x - other_fp->cur_pos.x;
        f32 dy = fp->cur_pos.y - other_fp->cur_pos.y;
        Vec3 vec;
        if (!(sqrtf(dx * dx + dy * dy) > 50.0) &&
            ftCo_800A6700(fp, &other_fp->cur_pos, &vec))
        {
            ftCo_800A1F3C(fp, vec.x, vec.y, 5.0F);
        }
    }
}

static inline void ftCo_800A80E4_dontinline(Fighter* fp)
{
    ftCo_800A80E4(fp);
}

/// #ftCo_800A8210

/// #ftCo_800A866C

/// #ftCo_800A8940

void ftCo_800A8DE4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(0x20);
    if (!fp->x1A88.xFA_b2) {
        data->xFA_b2 = true;
        data->x5C = 10000.0f;
        if (fp->facing_dir > 0.0) {
            if (!ftCo_800A4038(fp, true) && !ftCo_800A3908(fp, true)) {
                ftCo_800A4038(fp, false);
            }
        } else if (!ftCo_800A3908(fp, true) && !ftCo_800A4038(fp, true)) {
            ftCo_800A3908(fp, false);
        }
    }
}

static inline int angle_x_units(float angle)
{
    return 127.0F * cosf(angle);
}

static inline int angle_y_units(float angle)
{
    return 127.0F * sinf(angle);
}

/**
 * Ness recovery PK thunder logic
 */
void ftCo_800A8EB0(Fighter* fp)
{
    float angle;

    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (fp->x1A88.level < 9) {
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_PressBFor, 1);
    ftCo_800B463C(fp, CpuCmd_ReleaseB);
    if (data->x54.x - fp->cur_pos.x > 0.0) {
        angle = M_PI;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, angle_x_units(angle));
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, angle_y_units(angle));
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 20);

        angle = -M_PI_2;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, angle_x_units(angle));
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, angle_y_units(angle));
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 35);

        angle = 0.0F;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, angle_x_units(angle));
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, angle_y_units(angle));
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 20);

        angle = M_PI_2;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, angle_x_units(angle));
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, angle_y_units(angle));
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 20);
    } else {
        angle = 0.0F;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, angle_x_units(angle));
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, angle_y_units(angle));
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 20);

        angle = -M_PI_2;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, angle_x_units(angle));
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, angle_y_units(angle));
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 35);

        angle = M_PI;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, angle_x_units(angle));
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, angle_y_units(angle));
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 20);

        angle = M_PI_2;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, angle_x_units(angle));
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, angle_y_units(angle));
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 20);
    }
    ftCo_800B463C(fp, CpuCmd_Done);
}

/**
 * Pikachu/Pichu recovery logic
 */
void ftCo_800A92CC(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (ABS(fp->cur_pos.x - data->x54.x) > 60.0) {
        // If we're far in the horizontal direction, up-B diagonally, then to
        // the side.

        // Start the up-B
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_PressBFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);

        // Go diagonally upward
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x58);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x58);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 15);

        // Go horizontally toward the stage
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 15);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        // Otherwise, go straight up, then randomly horizontal or diagonal.

        // Start the up-B
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_PressBFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 15);

        if (HSD_Randf() > 0.5) {
            // Go diagonally upward
            ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x58);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x58);
        } else {
            // Go horizontally toward the stage
            ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        }
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 15);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

/**
 * Zelda recovery logic
 *
 * If we're far from the stage horizontally, up-B diagonally,
 * otherwise go straight up.
 */
static void ftCo_800A949C(Fighter* fp, bool unused)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (ABS(data->x54.x - fp->cur_pos.x) > 30.0) {
        // Wait a frame with the stick neutral?
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);

        // Up-B diagonally toward the stage
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_PressBFor, 40);

        // Release the B button and put the stick back to neutral
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
    } else {
        // Wait a frame with the stick neutral?
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);

        // Up-B straight up
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_PressBFor, 40);

        // Release the B button and put the stick back to neutral
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
    }
    ftCo_800B463C(fp, CpuCmd_Done);
}

/**
 * Samus recovery logic
 */
static void ftCo_800A963C(Fighter* fp, bool unused)
{
    PAD_STACK(4 * 14);

    // Up-B
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x58);
    ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x58);
    ftCo_800B46B8(fp, CpuCmd_PressBFor, 1);

    // Full drift toward the stage
    ftCo_800B463C(fp, CpuCmd_ReleaseB);
    ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
    ftCo_800B463C(fp, CpuCmd_Done);
}

#pragma push
#pragma dont_inline on
/**
 * Handles CPU recovery / up-B logic for each character
 */
void ftCo_800A96B8(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    float sum = fp->coll_data.cur_pos.y + fp->coll_data.ecb.bottom.y;
    bool tmp = fp->x1A88.x54.y > sum ? true : false;

    PAD_STACK(0x10);

    switch (fp->kind) {
    case FTKIND_MARIO:
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x58);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x58);
        ftCo_800B46B8(fp, CpuCmd_PressBFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
        ftCo_800B463C(fp, CpuCmd_Done);
        break;
    case FTKIND_PIKACHU:
    case FTKIND_PICHU:
        ftCo_800A92CC(fp);
        break;
    case FTKIND_FOX:
    case FTKIND_FALCO:
        // Diagonally up-B toward the stage
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x58);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x58);
        ftCo_800B46B8(fp, CpuCmd_PressBFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 40);
        ftCo_800B463C(fp, CpuCmd_Done);
        break;
    case FTKIND_YOSHI:
        // Yoshi's up-B isn't a recovery move, so don't try it
        ftCo_800B463C(fp, CpuCmd_Done);
        break;
    case FTKIND_NESS:
        // Don't try to up-B until Ness is under the stage
        if (fp->cur_pos.y > data->x54.y - 10.0) {
            ftCo_800B463C(fp, CpuCmd_Done);
        } else {
            ftCo_800A8EB0(fp);
        }
        break;
    case FTKIND_LUIGI:
        // Side-B toward the stage
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_PressBFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 40);
        ftCo_800B463C(fp, CpuCmd_Done);
        break;
    case FTKIND_ZELDA:
        ftCo_800A949C(fp, tmp);
        break;
    case FTKIND_SAMUS:
        ftCo_800A963C(fp, tmp);
        break;
    default:
        // For all other characters, diagonally up-B toward the stage,
        // with full inward drift
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x58);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x58);
        ftCo_800B46B8(fp, CpuCmd_PressBFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
        ftCo_800B463C(fp, CpuCmd_Done);
        break;
    }
}
#pragma pop

static inline bool is_small(float x)
{
    if (x < 0.00001F && x > -0.00001F) {
        return true;
    }
    return false;
}

void ftCo_800A9904(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;

    f32 var_f0;
    f32 temp_f3;
    f32 var_f4;
    f32 var_f5;

    f32* temp_r3;

    Vec3 sp4C;
    Vec3 sp40;
    int sp3C;
    u32 sp38;

    PAD_STACK(0x24);

    if (ftCo_800A3498(fp) != 0) {
        if (fp->co_attrs.max_jumps > fp->x1968_jumpsUsed) {
            ftCo_800B46B8(fp, CpuCmd_LstickTowardDestination, 0x7F);
            ftCo_800B463C(fp, CpuCmd_PressY);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseY);
            ftCo_800B463C(fp, CpuCmd_Done);
        } else {
            ftCo_800A96B8(fp);
        }
    } else if (temp_r31->xFA_b5) {
        f32 dx = temp_r31->x54.x - fp->cur_pos.x;
        if (is_small(fp->pos_delta.x)) {
            var_f0 = 1000.0F;
        } else {
            var_f0 = dx / fp->pos_delta.x;
        }
        temp_r3 = &fp->co_attrs.grav;
        if (is_small(fp->co_attrs.grav)) {
            var_f5 = 1000.0F;
        } else {
            var_f5 = -(-fp->co_attrs.terminal_vel - fp->pos_delta.y) /
                     fp->co_attrs.grav;
        }
        if (var_f5 <= 0.0F) {
            var_f4 = (fp->pos_delta.y * var_f0) + fp->cur_pos.y;
        } else if (var_f0 < var_f5) {
            var_f4 = fp->cur_pos.y + (fp->pos_delta.y * var_f0 -
                                      0.5 * (*temp_r3 * sqrtf(var_f0)));
        } else {
            var_f4 =
                fp->cur_pos.y +
                (fp->pos_delta.y * var_f5 - 0.5 * (*temp_r3 * sqrtf(var_f5)) -
                 ((var_f0 - var_f5) * fp->co_attrs.terminal_vel));
        }
        {
            int stick = 4.7000003F * (temp_r31->level + 1) + 80.0f;
            if (var_f0 < 0.0 || var_f4 < temp_r31->x54.y) {
                ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, stick);
            } else {
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            }
        }
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (mpCheckCeiling(fp->cur_pos.x, fp->cur_pos.y, temp_r31->x54.x,
                              temp_r31->x54.y, &sp4C, &sp3C, &sp38, &sp40, -1,
                              -1))
    {
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x81);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

static inline enum_t ftCo_800A9CB4_inline0(Fighter* fp)
{
    if (stage_info.internal_stage_id == SHRINE) {
        if (fp->cur_pos.x > -150.0f && fp->cur_pos.x < -90.0f) {
            return 1;
        }
    } else if (stage_info.internal_stage_id == FOURSIDE) {
        return 2;
    }
    return 0;
}

static inline bool ftCo_800A9CB4_inline1(Fighter* fp)
{
    Vec3 sp3C;
    if (fp->x1A88.xFA_b6) {
        return false;
    }
    if (fp->x34_scale.y < 1.0f) {
        return true;
    }
    if (stage_info.internal_stage_id == ICEMTN) {
        grLib_801C9E60(&sp3C);
        if (sp3C.y < 0.0) {
            return true;
        }
    } else if (stage_info.internal_stage_id == RCRUISE) {
        return true;
    }
    return false;
}

void ftCo_800A9CB4(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;

    f32 temp_f1;
    f32 dx;
    f32 var_f0;
    f32 var_f1_2;
    f32 var_f2;
    f32 var_f5;

    f32* temp_r3;
    enum_t var_r0_2;
    int var_r0_6;

    PAD_STACK(0x58);

    if (ftCo_800A1CA8(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (ftCo_800A3234(fp)) {
        if (fp->co_attrs.max_jumps > fp->x1968_jumpsUsed) {
            if (temp_r31->xFA_b6) {
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x7F);
                ftCo_800B463C(fp, CpuCmd_PressY);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseY);
                ftCo_800B463C(fp, CpuCmd_Done);
            } else if (fp->kind == FTKIND_YOSHI && fp->x34_scale.y < 1.0 &&
                       ABS(temp_r31->x54.x - fp->cur_pos.x) < 20.0f)
            {
                ftCo_800A0508_dontinline(fp);
            } else {
                ftCo_800B46B8(fp, CpuCmd_LstickTowardDestination, 0x7F);
                ftCo_800B463C(fp, CpuCmd_PressY);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseY);
                ftCo_800B463C(fp, CpuCmd_Done);
            }
            return;
        }
        if ((var_r0_2 = ftCo_800A9CB4_inline0(fp))) {
            if (var_r0_2 == 1) {
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
                ftCo_800B463C(fp, CpuCmd_PressR);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseR);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B463C(fp, CpuCmd_Done);
            } else {
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x50);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
                ftCo_800B463C(fp, CpuCmd_PressR);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseR);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B463C(fp, CpuCmd_Done);
            }
            return;
        }
        if (ftCo_800A9CB4_inline1(fp)) {
            ftCo_800A96B8(fp);
            return;
        }
    }
    if (temp_r31->xFA_b6) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x81);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    dx = temp_r31->x54.x - fp->cur_pos.x;
    var_f1_2 = ABS(dx);
    if (!is_small(fp->pos_delta.x)) {
        var_f0 = dx / fp->pos_delta.x;
    } else if (var_f1_2 > 0.0) {
        var_f0 = -1.0F;
    } else {
        var_f0 = 0.0F;
    }
    temp_r3 = &fp->co_attrs.grav;
    if (is_small(fp->co_attrs.grav)) {
        var_f5 = 1000.0F;
    } else {
        var_f5 = -(-fp->co_attrs.terminal_vel - fp->pos_delta.y) /
                 fp->co_attrs.grav;
    }
    if (var_f5 <= 0.0F) {
        var_f2 = (fp->pos_delta.y * var_f0) + fp->cur_pos.y;
    } else if (var_f0 < var_f5) {
        var_f2 = fp->cur_pos.y +
                 (fp->pos_delta.y * var_f0 - 0.5 * (*temp_r3 * sqrtf(var_f0)));
    } else {
        var_f2 = fp->cur_pos.y +
                 (fp->pos_delta.y * var_f5 - 0.5 * (*temp_r3 * sqrtf(var_f5)) -
                  ((var_f0 - var_f5) * fp->co_attrs.terminal_vel));
    }
    if (var_f0 < 0.0) {
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
    } else {
        if (var_f2 < temp_r31->x54.y) {
            var_r0_6 = (int) (temp_r31->x54.y - var_f2) * 2;
            if (var_r0_6 > 0x20) {
                var_r0_6 = 0x20;
            }
            ftCo_800B4778(fp, CpuCmd_LstickXTowardDestinationClamped, var_r0_6,
                          0x7F);
        } else {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        }
    }
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B463C(fp, CpuCmd_Done);
}

/**
 * Determine how much to move the stick based on CPU level
 */
void ftCo_800AA320(Fighter* fp, int* stick, int* clamp)
{
    // Nana moves the stick more aggressively so she can follow more
    // effectively
    if (fp->kind == FTKIND_NANA) {
        *stick = 0x40;
        *clamp = 0x7F;
        return;
    }
    switch (fp->x1A88.level) {
    case 0:
        *stick = 1;
        *clamp = 0x43;
        break;
    case 1:
        *stick = 2;
        *clamp = 0x48;
        break;
    case 2:
        *stick = 2;
        *clamp = 0x4D;
        break;
    case 3:
        *stick = 2;
        *clamp = 0x52;
        break;
    case 4:
        *stick = 2;
        *clamp = 0x57;
        break;
    case 5:
        *stick = 2;
        *clamp = 0x5C;
        break;
    case 6:
        *stick = 4;
        *clamp = 0x61;
        break;
    case 7:
        *stick = 4;
        *clamp = 0x6B;
        break;
    case 8:
        *stick = 8;
        *clamp = 0x75;
        break;
    case 9:
        *stick = 8;
        *clamp = 0x7F;
        break;
    }
}

static inline bool isInTeeter(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_Ottotto ||
        fp->motion_id == ftCo_MS_OttottoWait)
    {
        return true;
    }
    return false;
}

static inline int ftCo_800AA42C_inline0(float clamp, float dist, float near,
                                        float far)
{
    float raw;

    if (dist > far) {
        return clamp;
    }
    if (dist < near) {
        return 0;
    }
    raw = 127.0F * p_ftCommonData->x0;
    if (raw > clamp) {
        raw = clamp;
    }
    if (raw < 80.0F) {
        raw = 80.0F;
    }
    {
        float scale = (dist - near) / (far - near);
        float tmp = raw + scale * (clamp - raw);
        int new_clamp = tmp;
        if (new_clamp > clamp) {
            new_clamp = clamp;
        }
        return new_clamp;
    }
}

static inline bool isFacingDestination(Fighter* fp)
{
    if (fp->facing_dir * (fp->x1A88.x54.x - fp->cur_pos.x) >= 0.0) {
        return true;
    } else {
        return false;
    }
}

void ftCo_800AA42C(Fighter* fp)
{
    struct Fighter_x1A88_t* data;
    f32 near;
    f32 dist;
    bool facing_dest;
    bool running;

    int stick;
    int clamp;

    PAD_STACK(0x8);

    data = &fp->x1A88;
    ftCo_800AA320(fp, &stick, &clamp);
    if (isInTeeter(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (fp->facing_dir * (fp->x1A88.x54.x - fp->cur_pos.x) >= 0.0) {
        facing_dest = true;
    } else {
        facing_dest = false;
    }
    if (!facing_dest) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0xB0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 0xA);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    {
        float dx = data->x54.x - fp->cur_pos.x;
        float dy = data->x54.y - fp->cur_pos.y;
        dist = sqrtf(dx * dx + dy * dy);
    }
    near = data->x38;
    if (dist - near > data->x3C) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        if (data->xF8_b0) {
            if (fp->motion_id == ftCo_MS_Dash ||
                fp->motion_id == ftCo_MS_Run ||
                fp->motion_id == ftCo_MS_TurnRun)
            {
                running = true;
            } else {
                running = false;
            }
            if (running) {
                ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
            } else {
                ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 2);
                ftCo_800B46B8(fp, CpuCmd_LstickXTowardDestination, 0x7F);
            }
        } else {
            ftCo_800B4778(fp, CpuCmd_LstickXTowardDestinationClamped, stick,
                          clamp);
        }
    } else if (dist > near) {
        int tmp;
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        tmp = ftCo_800AA42C_inline0(clamp, dist, data->x38, data->x3C);
        ftCo_800B4778(fp, CpuCmd_LstickXTowardDestinationClamped, stick, tmp);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    }
    ftCo_800B463C(fp, CpuCmd_Done);
}

void ftCo_800AA844(Fighter* fp)
{
    struct Fighter_x1A88_t* data;

    int sp38;
    int sp34;
    Vec3 sp28;
    Vec3 sp1C;
    int sp18;
    u32 sp14;

    data = &fp->x1A88;
    if (isInTeeter(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    ftCo_800AA320(fp, &sp38, &sp34);
    if (ftCo_800A28D0(fp, 1.0F)) {
        if (ftCo_800A1CA8(fp) && fp->coll_data.floor.index != -1 &&
            (mpLineGetFlags(fp->coll_data.floor.index) & LINE_FLAG_PLATFORM) &&
            ftCo_800A0FB0(&sp28, &sp18, &sp14, &sp1C, -1, -1, -1,
                          fp->cur_pos.x, fp->cur_pos.y - 10.0F, fp->cur_pos.x,
                          fp->cur_pos.y - 1000.0F, 0.0F))
        {
            ftCo_800A08F0(fp);
        } else if (data->x54.y > fp->cur_pos.y) {
            ftCo_800A0148(fp);
        } else if (ABS(data->x54.x - fp->cur_pos.x) > 40.0) {
            ftCo_800A0148(fp);
        } else if (inlineC0(fp)) {
            ftCo_800A0148(fp);
        } else {
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B4778(fp, CpuCmd_LstickForwardClamped, sp38, sp34);
            ftCo_800B463C(fp, CpuCmd_Done);
        }
        return;
    } else if (inlineC0(fp)) {
        ftCo_800A0148(fp);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B4778(fp, CpuCmd_LstickForwardClamped, sp38, sp34);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800AABC8(Fighter* fp)
{
    PAD_STACK(2 * 4);
    if (isInTeeter(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        int stick;
        int clamp;
        ftCo_800AA320(fp, &stick, &clamp);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B4778(fp, CpuCmd_LstickForwardClamped, stick, clamp);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

static inline void ftCo_800AABC8_dontinline(Fighter* fp)
{
    ftCo_800AABC8(fp);
}

void ftCo_800AACD0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    mp_UnkStruct0* temp_r3_2;

    u8 _[8];

    int stick;
    int clamp;
    Vec3 sp24;
    Vec3 sp18;

    PAD_STACK(0xC);

    if (isInTeeter(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    ftCo_800AA320(fp, &stick, &clamp);
    if (fp->coll_data.floor.index != -1 &&
        (mpLineGetFlags(fp->coll_data.floor.index) & LINE_FLAG_PLATFORM))
    {
        ftCo_800A08F0(fp);
        return;
    }
    temp_r3_2 = mpIsland_8005AB54(fp->coll_data.floor.index);
    if (temp_r3_2 != NULL) {
        mpIsland_8005ACE8(temp_r3_2, &sp24, &sp18);
        if ((data->x54.x < sp24.x || data->x54.x > sp18.x) &&
            !ftCo_800A2BD4(fp))
        {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0xB0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 0xA);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B463C(fp, CpuCmd_Done);
            return;
        }
    }
    if (stage_info.internal_stage_id != ICEMTN && inlineC0(fp)) {
        ftCo_800A0148(fp);
        return;
    }
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B4778(fp, CpuCmd_LstickForwardClamped, stick, clamp);
    ftCo_800B463C(fp, CpuCmd_Done);
}

bool ftCo_800AAF48(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r29 = &fp->x1A88;
    mp_UnkStruct0* cur;

    f32 dx;
    f32 dy;

    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp2C;
    int sp28;
    u32 sp24;
    PAD_STACK(0xC);

    if (temp_r29->x60 != 0) {
        return false;
    }
    if (stage_info.internal_stage_id != SHRINE) {
        return false;
    }
    if (fp->facing_dir > 0.0) {
        for (cur = mpIsland_80458E88.next; cur != NULL; cur = cur->next) {
            sp44 = cur->x8;
            dx = sp44.x - fp->cur_pos.x;
            dy = sp44.y - fp->cur_pos.y;
            if (dx < 0.0F) {
                continue;
            }
            if (dy < 0.0F) {
                continue;
            }
            if (mpCheckCeiling(fp->cur_pos.x, fp->cur_pos.y, sp44.x, sp44.y,
                               &sp38, &sp28, &sp24, &sp2C, -1, -1))
            {
                continue;
            }
            if (mpCheckRightWall(fp->cur_pos.x, fp->cur_pos.y, sp44.x, sp44.y,
                                 &sp38, &sp28, &sp24, &sp2C, -1, -1))
            {
                continue;
            }
            if (dy < 2.0F * temp_r29->x558 + temp_r29->x568 &&
                dx < 5.0F * temp_r29->x564)
            {
                fp->x1A88.x60 = 0x12C;
                fp->x1A88.x64.x = fp->x1A88.x54.x;
                fp->x1A88.x64.y = fp->x1A88.x54.y;
                fp->x1A88.x54.x = sp44.x;
                fp->x1A88.x54.y = sp44.y;
                fp->x1A88.x38 = 5.0F;
                return true;
            }
        }
    } else {
        for (cur = mpIsland_80458E88.next; cur != NULL; cur = cur->next) {
            Vec3 spC = cur->x14;
            dx = fp->cur_pos.x - spC.x;
            dy = fp->cur_pos.y - spC.y;
            if (dx < 0.0F) {
                continue;
            }
            if (dy < 0.0F) {
                continue;
            }
            if (mpCheckCeiling(fp->cur_pos.x, fp->cur_pos.y, spC.x, spC.y,
                               &sp38, &sp28, &sp24, &sp2C, -1, -1))
            {
                continue;
            }
            if (mpCheckLeftWall(fp->cur_pos.x, fp->cur_pos.y, spC.x, spC.y,
                                &sp38, &sp28, &sp24, &sp2C, -1, -1))
            {
                continue;
            }
            if (dy < 2.0F * temp_r29->x558 + temp_r29->x568 &&
                dx < 5.0F * temp_r29->x564)
            {
                fp->x1A88.x60 = 0x12C;
                fp->x1A88.x64.x = fp->x1A88.x54.x;
                fp->x1A88.x64.y = fp->x1A88.x54.y;
                fp->x1A88.x54.x = spC.x;
                fp->x1A88.x54.y = spC.y;
                fp->x1A88.x38 = 5.0f;
                return true;
            }
        }
    }
    return false;
}

static inline void ftCo_800AD54C_inline0(Fighter* fp)
{
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
    ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0xB0);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 10);
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B463C(fp, CpuCmd_Done);
}

void ftCo_800AB224(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31;

    f32 temp_f1;
    f32 var_f1_3;
    f32 var_f2;
    f32 var_f31;

    Fighter* temp_r0;
    s32 var_r0_5;
    s32 var_r0_6;

    u8 _[0x48];

    u32 sp40;
    int sp3C;
    Vec3 sp30;
    Vec3 sp24;

    PAD_STACK(0xC);

    temp_r31 = &fp->x1A88;
    if (temp_r31->xFA_b6) {
        if (fp->facing_dir > 0.0) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0xB0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 0xA);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B463C(fp, CpuCmd_Done);
            return;
        }
        if (!ftCo_800A28D0(fp, 1.0F)) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0xB0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_Done);
            return;
        }
        ftCo_800A0384(fp);
        return;
    }
    if (temp_r31->xF9_b1) {
        temp_r0 = temp_r31->x44;
        if (temp_r0 != NULL) {
            if (ftCo_800A2C08(fp)) {
                if (ftCo_800A2170(fp, temp_r0)) {
                    var_f1_3 = ABS(temp_r0->cur_pos.x - fp->cur_pos.x);
                    if (var_f1_3 < 37.5) {
                        ftCo_800A0148(fp);
                        return;
                    }
                }
            }
        }
        if (!temp_r31->xF8_b6 || fp->ground_or_air != GA_Ground ||
            !(HSD_Randf() < 0.05f * temp_r31->level) ||
            (temp_r31->xF8_b6 = false, ftCo_800BA2E8(fp, temp_r0) == 0))
        {
            goto block_49;
        }
    } else {
    block_49:
        if (ftCo_800A21FC(fp)) {
            ftCo_800AA42C(fp);
            return;
        }
        var_f2 = ABS(temp_r31->x54.x - fp->cur_pos.x);
        temp_f1 = temp_r31->x54.y - fp->cur_pos.y;
        if (var_f2 < 0.00001F && var_f2 > -0.00001F) {
            var_r0_5 = 1;
        } else {
            var_r0_5 = 0;
        }
        if (var_r0_5 != 0) {
            if (temp_f1 > 0.0) {
                var_f31 = +M_PI_2;
            } else {
                var_f31 = -M_PI_2;
            }
        } else {
            var_f31 = lb_8000D008(temp_f1, var_f2);
        }
        if (var_f31 > 0.6108652334660292) {
            if (mpCheckCeiling(fp->coll_data.cur_pos.x,
                               fp->coll_data.cur_pos.y,
                               fp->coll_data.cur_pos.x, fp->x1A88.x54.y, &sp24,
                               &sp3C, &sp40, &sp30, -1, -1))
            {
                var_r0_6 = 1;
            } else {
                var_r0_6 = 0;
            }
            if (var_r0_6 != 0) {
                if (ftCo_800A28D0(fp, 1.0F)) {
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0xB0);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 0xA);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                    ftCo_800B463C(fp, CpuCmd_Done);
                } else if (ftCo_800AAF48(fp) != 0) {
                    ftCo_800A0148(fp);
                } else {
                    ftCo_800AABC8_dontinline(fp);
                }
            } else if (stage_info.internal_stage_id == ICEMTN) {
                ftCo_800A0148(fp);
            } else if (!ftCo_800A2BD4(fp)) {
                if (var_f31 < 1.3089969288557768) {
                    ftCo_800AD54C_inline0(fp);
                } else {
                    ftCo_800AABC8_dontinline(fp);
                }
            } else {
                ftCo_800A0148(fp);
            }
        } else if (var_f31 > -0.7853981573134661) {
            if (!ftCo_800A2BD4(fp)) {
                ftCo_800AD54C_inline0(fp);
            } else {
                ftCo_800AA844(fp);
            }
        } else {
            ftCo_800AACD0(fp);
        }
    }
}

void ftCo_800ABA34(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (data->xC == 11) {
        if (fp->item_gobj == NULL) {
            ftCo_800B4880(fp, 38);
            return;
        }
    } else if (data->xC == 12) {
        if (data->x7C % 30 == 0) {
            ftCo_800B4880(fp, 38);
            return;
        }
    } else if (data->xC == 16 && fp->ground_or_air == GA_Ground &&
               data->x7C % 300 == 0)
    {
        ftCo_800A05F4(fp);
        return;
    }
    if ((fp->kind == FTKIND_ZELDA || fp->kind == FTKIND_SEAK) && data->xF8_b5)
    {
        ftCo_800B4880(fp, 38);
        data->xF8_b5 = false;
    } else if (ftCo_800A5CE0(fp) == NULL &&
               fp->motion_id == ftCo_MS_RebirthWait)
    {
        ftCo_800A08F0(fp);
    } else if (fp->ground_or_air == GA_Air) {
        ftCo_800A9CB4(fp);
    } else {
        ftCo_800AB224(fp);
    }
}

/// #ftCo_800ABBA8

static inline bool inlineG0(Fighter* fp)
{
    enum_t temp_r0 = fp->motion_id;
    bool ret;
    if (temp_r0 == 224) {
        ret = true;
    } else if (temp_r0 == 227) {
        ret = true;
    } else if (temp_r0 >= 266 && temp_r0 <= 270) {
        ret = true;
    } else {
        ret = false;
    }
    return ret;
}

void ftCo_800AC30C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(4 * 4);
    if (!inlineG0(fp)) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (data->x7C % 3 == 0 && !(data->level * 0.1F < HSD_Randf())) {
        if (fp->x1A88.lstickX < 0) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, +0x7F);
        } else {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, -0x7F);
        }
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

static inline enum_t inlineH0(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_BarrelWait) {
        return 1;
    }
    if (fp->motion_id == ftCo_MS_Barrel) {
        return 2;
    }
    return 0;
}

static inline void inlineH1(Fighter* fp, struct Fighter_x1A88_t* data)
{
    if (data->x7C % ((10 - data->level) * 5) == 0 && HSD_Randf() < 0.5f) {
        ftCo_800B463C(fp, CpuCmd_PressA);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseA);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800AC434(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Vec3 vec;
    float f;
    enum_t barrel_state = inlineH0(fp);
    PAD_STACK(5 * 4);

    if (barrel_state == 0) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (barrel_state == 1) {
        PAD_STACK(1 * 4);
        Ground_801C4DA0(&vec, &f);
    } else {
        inlineH1(fp, data);
        return;
    }
    if (f >= -0.26179938577115536 && f <= 0.0) {
        ftCo_800B463C(fp, CpuCmd_PressA);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseA);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800AC5A0(Fighter* fp)
{
    struct Fighter_x1A88_t* data;
    bool var_r0;
    s8 stick_x;
    s8 stick_y;

    data = &fp->x1A88;
    if (!fp->x221A_b3) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, CpuCmd_ReleaseR);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (data->x7C % 120 > 120 - data->level * 12) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        float kb_x = fp->x8c_kb_vel.x;
        float kb_y = fp->x8c_kb_vel.y;
        float kb_mag = sqrtf(kb_x * kb_x + kb_y * kb_y);
        if (!is_small(kb_mag)) {
            float x = kb_x * (1.0F / kb_mag);
            float y = kb_y * (1.0F / kb_mag);
            if (kb_x > 0.0F) {
                stick_y = 127.0F * -y;
                stick_x = 127.0F * +x;
            } else {
                stick_y = 127.0F * +y;
                stick_x = 127.0F * -x;
            }
        }
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, stick_y);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, stick_x);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    }
    if (data->xFA_b1) {
        ftCo_800B463C(fp, CpuCmd_PressR);
    }
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
    ftCo_800B463C(fp, CpuCmd_Done);
}

void ftCo_800AC7D4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Fighter* temp_r3;
    int temp_r0_2;
    enum_t var_r0;

    PAD_STACK(8);

    var_r0 = ftCo_800A3134(fp);
    if (var_r0 == 0) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (var_r0 == 1) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    temp_r0_2 = data->xC;
    if ((temp_r0_2 == 0xF) || (temp_r0_2 == 0)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    temp_r3 = ftCo_800A4BEC(fp);
    if (temp_r3 == NULL) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (ftCo_800A1AB4(fp, temp_r3) < 15.0) {
        if (HSD_Randf() < 0.1F * data->level) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B463C(fp, CpuCmd_ReleaseA);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_PressA);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseA);
            ftCo_800B463C(fp, CpuCmd_Done);
        } else {
            if (temp_r3->cur_pos.x - fp->cur_pos.x < 0.0F) {
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x50);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 0xA);
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            } else {
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0xB0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 0xA);
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            }
            ftCo_800B463C(fp, CpuCmd_Done);
        }
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800ACB44(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Fighter* temp_r3;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    s32 temp_r0_2;
    s32 var_r0;

    var_r0 = ftCo_800A3200(fp);
    if (var_r0 == 1) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (var_r0 == 0) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (data->xC == 0xF || data->xC == 0) {
        ftCo_800A0AF4(fp);
        return;
    }
    temp_r3 = ftCo_800A4BEC(fp);
    if (temp_r3 == NULL) {
        ftCo_800A0AF4(fp);
        return;
    }
    temp_f1_2 = ftCo_800A1AB4(fp, temp_r3);
    if (data->xF9_b2 && temp_f1_2 < 30.0) {
        if (0.1F * data->level > HSD_Randf()) {
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B463C(fp, CpuCmd_Done);
        } else {
            ftCo_800B463C(fp, CpuCmd_ReleaseA);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_PressA);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseA);
            ftCo_800B463C(fp, CpuCmd_Done);
        }
    } else {
        ftCo_800A0AF4(fp);
    }
}

void ftCo_800ACD5C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;

    PAD_STACK(0x18);

    if (data->xF9_b1) {
        Fighter* enemy = data->x44;
        if (enemy != NULL && data->xF8_b6) {
            data->xF8_b6 = false;
            ftCo_800BA674(fp, enemy);
            return;
        }
    }
    if (data->x88 > 0 && gm_801A4310() != 0x1C) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressUp);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseUp);
        ftCo_800B463C(fp, CpuCmd_Done);
        data->x88 = 0;
        data->x8C = gm_8016C75C(fp->gobj);
        return;
    }
    if (data->xC == 0xB && fp->item_gobj == NULL) {
        ftCo_800B4880(fp, 0x26);
        return;
    }
    if (ftCo_800A3554(fp, 1.0f) == 0) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if ((fp->kind == FTKIND_ZELDA || fp->kind == FTKIND_SEAK) && data->xF8_b5)
    {
        ftCo_800B4880(fp, 0x26);
        data->xF8_b5 = false;
        return;
    }
    if (!ftCo_800A2C08(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0xB0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 0xA);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (data->level < 5) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }
    if (fp->kind == FTKIND_DONKEY) {
        if (fp->motion_id != ftDk_MS_SpecialNLoop && fp->fv.dk.x222C == 0) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B463C(fp, CpuCmd_PressB);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseB);
            ftCo_800B463C(fp, CpuCmd_Done);
            return;
        }
    } else if (fp->kind == FTKIND_SAMUS) {
        if (fp->motion_id != ftSs_MS_SpecialNHold && fp->fv.ss.x2230 == 0) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B463C(fp, CpuCmd_PressB);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseB);
            ftCo_800B463C(fp, CpuCmd_Done);
            return;
        }
    } else if (fp->kind == FTKIND_MEWTWO) {
        ftMewtwoAttributes* da = fp->dat_attrs;
        if (fp->fv.mt.x2234_shadowBallCharge ==
            da->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES)
        {
            if (fp->motion_id == ftMt_MS_SpecialNLoop ||
                fp->motion_id == ftMt_MS_SpecialNLoopFull)
            {
                ftCo_800B463C(fp, CpuCmd_PressR);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseR);
                ftCo_800B463C(fp, CpuCmd_Done);
                return;
            }
        } else if (fp->motion_id != ftMt_MS_SpecialNLoop &&
                   fp->fv.mt.x2234_shadowBallCharge == 0)
        {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B463C(fp, CpuCmd_PressB);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseB);
            ftCo_800B463C(fp, CpuCmd_Done);
            return;
        }
    } else if (fp->kind == FTKIND_KIRBY) {
        if (fp->fv.kb.hat.kind == FTKIND_DONKEY) {
            if (fp->motion_id != ftKb_MS_DkSpecialNLoop && fp->fv.kb.xBC == 0)
            {
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B463C(fp, CpuCmd_PressB);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseB);
                ftCo_800B463C(fp, CpuCmd_Done);
                return;
            }
        } else if (fp->fv.kb.hat.kind == FTKIND_SAMUS) {
            if (fp->motion_id != ftKb_MS_SsSpecialNHold && fp->fv.kb.xA8 == 0)
            {
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B463C(fp, CpuCmd_PressB);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseB);
                ftCo_800B463C(fp, CpuCmd_Done);
                return;
            }
        } else if (fp->fv.kb.hat.kind == FTKIND_MEWTWO) {
            struct ftKb_DatAttrs* da = fp->dat_attrs;
            if (fp->fv.kb.x9C == da->specialn_mt_charge_time) {
                if (fp->motion_id == ftKb_MS_MtSpecialNLoop ||
                    fp->motion_id == ftKb_MS_MtSpecialNLoopFull)
                {
                    ftCo_800B463C(fp, CpuCmd_PressR);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B463C(fp, CpuCmd_ReleaseR);
                    return;
                }
            } else if (fp->motion_id != ftKb_MS_MtSpecialNLoop &&
                       fp->fv.kb.x9C == 0)
            {
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B463C(fp, CpuCmd_PressB);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseB);
                ftCo_800B463C(fp, CpuCmd_Done);
                return;
            }
        }
    }
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B463C(fp, CpuCmd_Done);
}

void ftCo_800AD42C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (!ftCo_800A3554(fp, 1.0F)) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (fp->ground_or_air == GA_Air) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, p_ftCommonData->x74 + 1);
        ftCo_800B463C(fp, CpuCmd_ReleaseY);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800AD54C(Fighter* fp)
{
    u8 _[8];
    int stick;
    int clamp;
    PAD_STACK(8);

    ftCo_800AA320(fp, &stick, &clamp);
    if (fp->ground_or_air == GA_Air) {
        ftCo_800B4778(fp, CpuCmd_LstickForwardClamped, stick, clamp);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (ftCo_800A28D0(fp, 1.0F)) {
        ftCo_800AD54C_inline0(fp);
    } else if (inlineC0(fp)) {
        if (HSD_Randf() < 0.5f) {
            ftCo_800A0384(fp);
        } else {
            ftCo_800AD54C_inline0(fp);
        }
    } else if (mpIsland_8005AB54(fp->coll_data.floor.index) != NULL) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B4778(fp, CpuCmd_LstickForwardClamped, stick, clamp);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

static inline bool is_capsule_egg_ball(ItemKind kind)
{
    if (kind == It_Kind_Capsule || kind == It_Kind_Egg ||
        kind == It_Kind_M_Ball)
    {
        return true;
    }
    return false;
}

/**
 * CPU item throw behavior
 */
void ftCo_800AD7FC(Fighter* fp)
{
    Fighter* enemy;
    struct Fighter_x1A88_t* data;
    Item* item;
    f32 angle;

    PAD_STACK(0x10);

    data = &fp->x1A88;
    if (fp->item_gobj == NULL) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, CpuCmd_Done);
        return;
    }

    enemy = data->x44;
    item = GET_ITEM(fp->item_gobj);
    if (enemy != NULL && data->xC == 0x1D) {
        if (!ftCo_800A2C08(fp)) {
            ftCo_800AD54C_inline0(fp);
        } else {
            angle = lb_8000D008(enemy->cur_pos.y - fp->cur_pos.y,
                                ABS(enemy->cur_pos.x - fp->cur_pos.x));
            if (angle > 1.3089969288557768) {
                ftCo_800B4880(fp, 0x2B);
            } else if (angle < -1.3089969288557768) {
                ftCo_800B4880(fp, 0x2C);
            } else {
                ftCo_800B4880(fp, 0x2A);
            }
            data->x18 = data->x1C;
        }
    } else {
        if (enemy != NULL) {
            float unused = ftCo_800A1AB4(fp, enemy);
            angle = lb_8000D008(enemy->cur_pos.y - fp->cur_pos.y,
                                ABS(enemy->cur_pos.x - fp->cur_pos.x));
            if (angle > 1.3089969288557768) {
                ftCo_800B4880(fp, 0xD);
            } else if (angle < -1.3089969288557768) {
                ftCo_800B4880(fp, 0xE);
            } else {
                if (!ftCo_800A2C08(fp)) {
                    if (is_capsule_egg_ball(item->kind)) {
                        ftCo_800B4880(fp, 0xE);
                    } else {
                        ftCo_800B4880(fp, 0x28);
                    }
                } else if (angle < 0.26179938577115536 &&
                           angle > -0.26179938577115536)
                {
                    ftCo_800B4880(fp, 0xF);
                } else {
                    if (is_capsule_egg_ball(item->kind)) {
                        ftCo_800B4880(fp, 0xE);
                    } else {
                        ftCo_800B4880(fp, 0x28);
                    }
                }
            }
        } else {
            if (is_capsule_egg_ball(item->kind)) {
                ftCo_800B4880(fp, 0xE);
            } else {
                ftCo_800B4880(fp, 0x28);
            }
        }
        data->x18 = data->x1C;
    }
}

/// Handle charging neutral-B
void ftCo_800ADC28(Fighter* fp)
{
    if (fp->x1A88.x18 == 0xA) {
        return;
    }

    if (fp->kind == FTKIND_DONKEY) {
        if (fp->motion_id == ftDk_MS_SpecialNLoop) {
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
        }
    } else if (fp->kind == FTKIND_SAMUS) {
        if (fp->motion_id == ftSs_MS_SpecialNHold) {
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        }
    } else if (fp->kind == FTKIND_MEWTWO) {
        if (fp->motion_id == ftMt_MS_SpecialNLoop ||
            fp->motion_id == ftMt_MS_SpecialNLoopFull)
        {
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        }
    } else if (fp->kind == FTKIND_KIRBY) {
        FighterKind kind = fp->fv.kb.hat.kind;
        if (kind == FTKIND_DONKEY && fp->motion_id == ftKb_MS_DkSpecialNLoop) {
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        } else if (kind == FTKIND_SAMUS &&
                   fp->motion_id == ftKb_MS_SsSpecialNHold)
        {
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        } else if (kind == FTKIND_MEWTWO &&
                   (fp->motion_id == ftKb_MS_MtSpecialNLoop ||
                    fp->motion_id == ftKb_MS_MtSpecialNLoopFull))
        {
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        }
    }
}

/// #ftCo_800ADE48

/// #ftCo_800AE7AC

/// #ftCo_800AEA8C

/// #ftCo_800AECF0

/// #ftCo_800AEFB8

/// #ftCo_800AF290

static inline bool inlineI1(struct Fighter_x1A88_t* data)
{
    if (data->x18 != data->x20 && data->x18 != data->x1C) {
        data->x60 = 0;
    }
    if (data->x18 == 4) {
        return false;
    } else {
        data->xFA_b2 = false;
        return true;
    }
}

static inline bool inlineI1_alt(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (data->x18 != data->x20 && data->x18 != data->x1C) {
        data->x60 = 0;
    }
    if (data->x18 == 4) {
        return false;
    } else {
        data->xFA_b2 = false;
        return true;
    }
}

static inline void ftCo_800AF78C_inline0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    if (ftCo_800A1C44(fp)) {
        data->xF8_b6 = false;
    } else {
        if ((data->x44 != NULL) && (fp->ground_or_air == GA_Ground)) {
            if (ftCo_800A1AB4(fp, data->x44) <
                M2C_FIELD(Fighter_804D64FC, float**, 0x20)[fp->kind])
            {
                data->xF8_b6 = true;
            } else {
                data->xF8_b6 = false;
            }
        } else {
            data->xF8_b6 = false;
        }
    }
}

void ftCo_800AF78C(Fighter* fp)
{
    Vec3 sp4C;

    Fighter** temp_r31;
    struct Fighter_x1A88_t* temp_r30;
    struct Fighter_x1A88_t* temp_r27;

    Fighter* temp_r3_2;
    Fighter* temp_r4_2;
    f32 temp_f2_2;
    f32 temp_f3;
    f32 var_f4;
    s32 temp_r3;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;

    PAD_STACK(8);

    temp_r30 = &fp->x1A88;
    temp_r3 = ftCo_800A229C(fp, &sp4C);
    if (temp_r3 != 0) {
        ftCo_800AE7AC(fp, &sp4C, temp_r3);
        return;
    }
    temp_r3_2 = ftCo_800A5CE0(fp);
    temp_r30->x44 = temp_r3_2;
    if (temp_r3_2 != NULL) {
        temp_r30->xF8_b0 = true;
        temp_r30->xF9_b2 = false;
        temp_r30->xF9_b4 = false;
        temp_r30->xF9_b3 = false;
        temp_r30->xF9_b5 = false;
        temp_r30->xF9_b6 = false;
        temp_r30->xF9_b7 = false;
        temp_r30->xF9_b1 = true;
        ftCo_800A20A0_dontinline(fp);
        if (temp_r30->x18 != temp_r30->x20 && temp_r30->x18 != temp_r30->x1C) {
            temp_r30->x60 = 0;
        }
        if (temp_r30->x18 == 4) {
            var_r0 = false;
        } else {
            temp_r30->xFA_b2 = false;
            var_r0 = true;
        }
        if (var_r0) {
            ftCo_800A80E4_dontinline(fp);
        }
        ftCo_800ADE48(fp);
        return;
    }
    if (fp->x221D_b6) {
        var_r0_2 = 1;
    } else if (fp->x2168 != 0 && fp->x2338.x == 0) {
        var_r0_2 = 1;
    } else {
        var_r0_2 = 0;
    }
    if (var_r0_2 != 0) {
        ftCo_800AECF0(fp);
        return;
    }
    temp_r30->xF8_b0 = true;
    temp_r30->xF9_b2 = true;
    temp_r30->xF9_b4 = true;
    temp_r30->xF9_b3 = false;
    temp_r30->xF9_b5 = true;
    temp_r30->xF9_b6 = true;
    temp_r30->xF9_b7 = true;
    temp_r30->xF9_b1 = false;

    fp->x1A88.x44 = ftCo_800A4BEC(fp);
    temp_r31 = &fp->x1A88.x44;

    temp_r27 = &fp->x1A88;
    if (fp->item_gobj != NULL && !ftCo_800A5908(GET_ITEM(fp->item_gobj))) {
        temp_r27->x4C = NULL;
    } else if (fp->x2168 != 0) {
        temp_r27->x4C = NULL;
    } else {
        temp_r27->x4C = ftCo_800A5F4C(fp, It_Kind_L_Gun_Ray);
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);

    ftCo_800AF78C_inline0(fp);
    if (inlineI1_alt(fp)) {
        if (temp_r30->x4C != NULL) {
            ftCo_800A866C(fp);
        } else {
            ftCo_800A80E4(fp);
        }
    }
    ftCo_800ADE48(fp);
}

void ftCo_800AFC40(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31;
    struct Fighter_x1A88_t* temp_r28;

    Fighter* temp_r3_3;
    s32 var_r0;
    struct Fighter_x1A88_t* temp_r4;

    PAD_STACK(0x10);

    temp_r31 = &fp->x1A88;
    if (fp->x221D_b6) {
        var_r0 = 1;
    } else if (fp->x2168 != 0 && fp->x2338.x == 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        ftCo_800AECF0(fp);
        return;
    }
    temp_r31->xF8_b0 = true;
    temp_r31->xF9_b2 = true;
    temp_r31->xF9_b4 = true;
    temp_r31->xF9_b3 = true;
    temp_r31->xF9_b5 = true;
    temp_r31->xF9_b6 = true;
    temp_r31->xF9_b7 = false;
    temp_r31->xF9_b1 = false;
    fp->x1A88.x44 = ftCo_800A4BEC(fp);
    temp_r28 = &fp->x1A88;
    if (fp->item_gobj != NULL && !ftCo_800A5908(GET_ITEM(fp->item_gobj))) {
        temp_r28->x4C = NULL;
    } else {
        if (fp->x2168 != 0) {
            temp_r28->x4C = NULL;
        } else {
            temp_r28->x4C = ftCo_800A5F4C(fp, It_Kind_L_Gun_Ray);
        }
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);
    temp_r4 = &fp->x1A88;
    if (inlineI1(temp_r4)) {
        temp_r3_3 = ftCo_800A50D4(fp);
        if (temp_r3_3 != NULL) {
            ftCo_800A75DC(fp, temp_r3_3);
        } else {
            ftCo_800A75DC(fp, temp_r31->x44);
        }
    }
    ftCo_800ADE48(fp);
}

void ftCo_800AFE3C(Fighter* fp, int arg1)
{
    struct Fighter_x1A88_t* temp_r31;

    Vec3 sp2C;

    Fighter* temp_r3_2;
    Fighter* temp_r3_6;
    s32 temp_r3;

    PAD_STACK(0x14);

    temp_r31 = &fp->x1A88;
    temp_r3 = ftCo_800A229C(fp, &sp2C);
    if (temp_r3 != 0) {
        ftCo_800AE7AC(fp, &sp2C, temp_r3);
        return;
    }
    temp_r3_2 = ftCo_800A5CE0(fp);
    temp_r31->x44 = temp_r3_2;
    if (temp_r3_2 != NULL) {
        temp_r31->xF8_b0 = true;
        temp_r31->xF9_b2 = false;
        temp_r31->xF9_b4 = false;
        temp_r31->xF9_b3 = false;
        temp_r31->xF9_b5 = false;
        temp_r31->xF9_b6 = false;
        temp_r31->xF9_b7 = false;
        temp_r31->xF9_b1 = true;
        ftCo_800A20A0_dontinline(fp);
        if (inlineI1_alt(fp)) {
            ftCo_800A80E4_dontinline(fp);
        }
        ftCo_800ADE48(fp);
        return;
    }
    temp_r31->xF8_b0 = false;
    temp_r31->xF9_b2 = true;
    temp_r31->xF9_b4 = true;
    temp_r31->xF9_b3 = true;
    temp_r31->xF9_b5 = true;
    temp_r31->xF9_b6 = true;
    temp_r31->xF9_b7 = true;
    temp_r31->xF9_b1 = false;
    fp->x1A88.x44 = ftCo_800A4BEC(fp);
    if (fp->item_gobj != NULL && !ftCo_800A5908(GET_ITEM(fp->item_gobj))) {
        temp_r31->x4C = NULL;
    } else {
        if (fp->x2168 != 0) {
            temp_r31->x4C = NULL;
        } else {
            temp_r31->x4C = ftCo_800A5F4C(fp, It_Kind_L_Gun_Ray);
        }
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);
    if (inlineI1_alt(fp)) {
        if ((temp_r3_6 = ftCo_800A5294_dontinline(fp, arg1))) {
            ftCo_800A75DC(fp, temp_r3_6);
        } else {
            ftCo_800A75DC(fp, temp_r31->x44);
        }
    }
    ftCo_800ADE48(fp);
}

void ftCo_800B00F8(Fighter* fp)
{
    Vec3 sp28;
    Fighter* temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_4;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    int var_r0_10;
    int var_r0_4;
    int var_r0_5;
    int var_r0_6;
    int var_r0_7;
    int var_r0_8;
    int var_r0_9;
    struct Fighter_x1A88_t* temp_r31;
    struct Fighter_x1A88_t* temp_r4;
    int tmp;

    PAD_STACK(0x10);

    temp_r31 = &fp->x1A88;
    tmp = ftCo_800A229C(fp, &sp28);
    if (tmp) {
        ftCo_800AE7AC(fp, &sp28, tmp);
        return;
    }
    temp_r3 = ftCo_800A5CE0(fp);
    temp_r31->x44 = temp_r3;
    if (temp_r3 != NULL) {
        temp_r31->xF8_b0 = true;
        temp_r31->xF9_b2 = false;
        temp_r31->xF9_b4 = false;
        temp_r31->xF9_b3 = false;
        temp_r31->xF9_b5 = false;
        temp_r31->xF9_b6 = false;
        temp_r31->xF9_b7 = false;
        temp_r31->xF9_b1 = true;
        ftCo_800A20A0_dontinline(fp);
        temp_r3_2 = temp_r31->x18;
        if ((temp_r3_2 != temp_r31->x20) && (temp_r3_2 != temp_r31->x1C)) {
            temp_r31->x60 = 0;
        }
        if (temp_r31->x18 == 4) {
            var_r0 = 0;
        } else {
            temp_r31->xFA_b2 = false;
            var_r0 = 1;
        }
        if (var_r0 != 0) {
            ftCo_800A80E4_dontinline(fp);
        }
        ftCo_800ADE48(fp);
        return;
    }
    fp->x1A88.x44 = ftCo_800A4BEC(fp);
    if (fp->item_gobj != NULL && !ftCo_800A5908(GET_ITEM(fp->item_gobj))) {
        temp_r31->x4C = NULL;
    } else {
        if (fp->x2168 != 0) {
            temp_r31->x4C = NULL;
        } else {
            temp_r31->x4C = ftCo_800A61D8(fp);
        }
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);
    temp_r4 = &fp->x1A88;
    temp_r3_4 = fp->x1A88.x18;
    if (temp_r3_4 != fp->x1A88.x20 && temp_r3_4 != temp_r4->x1C) {
        temp_r4->x60 = 0;
    }
    if (temp_r4->x18 == 4) {
        var_r0_3 = 0;
    } else {
        temp_r4->xFA_b2 = false;
        var_r0_3 = 1;
    }
    if (var_r0_3 != 0) {
        if (temp_r31->x4C != NULL) {
            ftCo_800A866C(fp);
        } else if (((temp_r31->x7C % 60) * 5) == 0) {
            if (HSD_Randf() < 0.5) {
                ftCo_800A8940(fp);
            }
            if (HSD_Randf() > 0.5) {
                var_r0_4 = 1;
            } else {
                var_r0_4 = 0;
            }
            temp_r31->xF8_b0 = var_r0_4;
            if (HSD_Randf() > 0.5) {
                var_r0_5 = 1;
            } else {
                var_r0_5 = 0;
            }
            temp_r31->xF9_b2 = var_r0_5;
            if (HSD_Randf() > 0.5) {
                var_r0_6 = 1;
            } else {
                var_r0_6 = 0;
            }
            temp_r31->xF9_b4 = var_r0_6;
            if (HSD_Randf() > 0.5) {
                var_r0_7 = 1;
            } else {
                var_r0_7 = 0;
            }
            temp_r31->xF9_b3 = var_r0_7;
            if (HSD_Randf() > 0.5) {
                var_r0_8 = 1;
            } else {
                var_r0_8 = 0;
            }
            temp_r31->xF9_b5 = var_r0_8;
            if (HSD_Randf() > 0.5) {
                var_r0_9 = 1;
            } else {
                var_r0_9 = 0;
            }
            temp_r31->xF9_b6 = var_r0_9;
            if (HSD_Randf() > 0.5) {
                var_r0_10 = 1;
            } else {
                var_r0_10 = 0;
            }
            temp_r31->xF9_b7 = var_r0_10;
            temp_r31->xF9_b1 = false;
        }
    }
    ftCo_800ADE48(fp);
}

/// #ftCo_800B04DC

static inline void inlineI0(Fighter* fp, struct Fighter_x1A88_t* data)
{
    data->xF8_b0 = false;
    data->xF9_b2 = true;
    data->xF9_b4 = true;
    data->xF9_b3 = false;
    data->xF9_b5 = false;
    data->xF9_b6 = false;
    data->xF9_b7 = false;
    data->xF9_b1 = false;
    fp->x1A88.x44 = ftCo_800A4BEC(fp);
}

static inline void inlineI3(Fighter* fp, struct Fighter_x1A88_t* data)
{
    struct Fighter_x1A88_t* fp_data = &fp->x1A88;
    if (inlineI1(fp_data)) {
        if (data->xFB_b0) {
            ftCo_800A8DE4(fp);
        } else {
            ftCo_800A7AAC(fp);
        }
    }
}

void ftCo_800B0760(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(4 * 4);

    data->xF8_b0 = true;
    data->xF9_b2 = true;
    data->xF9_b4 = true;
    data->xF9_b3 = false;
    data->xF9_b5 = false;
    data->xF9_b6 = false;
    data->xF9_b7 = false;
    data->xF9_b1 = false;

    fp->x1A88.x44 = ftCo_800A4BEC(fp);

    if (fp->item_gobj != NULL && !ftCo_800A5908(GET_ITEM(fp->item_gobj))) {
        data->x4C = NULL;
    } else if (fp->x2168 != 0) {
        data->x4C = NULL;
    } else {
        data->x4C = ftCo_800A5F4C(fp, It_Kind_L_Gun_Ray);
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);
    inlineI3(fp, data);
    ftCo_800ADE48(fp);
}

static inline void ftCo_800B0760_dontinline(Fighter* fp)
{
    ftCo_800B0760(fp);
}

/// @todo Maybe a macro?
static inline u8 inlineM0(float x)
{
    if (x >= 0) {
        return 127.0F * x;
    } else {
        return 128.0F * x;
    }
}

void ftCo_800B0918(Fighter* fp0, Fighter* fp1)
{
    struct Fighter_x1A88_t* data;

    data = &fp1->x1A88;
    data->x444++;
    data->x448++;
    if (data->x444 == data->xFC + ARRAY_SIZE(data->xFC)) {
        data->x444 = data->xFC;
    }
    if (data->x448 == data->xFC + ARRAY_SIZE(data->xFC)) {
        data->x448 = data->xFC;
    }
    data->x444->lstickX = inlineM0(fp0->input.lstick.x);
    data->x444->lstickY = inlineM0(fp0->input.lstick.y);
    data->x444->cstickX = inlineM0(fp0->input.cstick.x);
    data->x444->cstickY = inlineM0(fp0->input.cstick.y);
    data->x444->x4 = fp0->input.x650;
    data->x444->x5 = fp0->input.x650;
    data->x444->x0 = fp0->input.held_inputs;
    data->x444->cur_pos = fp0->cur_pos;
    data->x444->facing_dir = fp0->facing_dir;
}

static inline bool inlineJ0(Fighter* fp, Fighter* nana_fp)
{
    if (fp->motion_id == ftCo_MS_FireFlowerShoot ||
        fp->motion_id == ftCo_MS_FireFlowerShootAir)
    {
        return false;
    }
    if (nana_fp->motion_id == ftPp_MS_SpecialLw &&
        fp->motion_id < ftCo_MS_Count)
    {
        return true;
    } else {
        return false;
    }
}

void ftCo_800B0AF4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    Fighter* nana_fp = ftCo_800A589C(fp);
    if (nana_fp != NULL && data->xFA_b7) {
        if (inlineJ0(fp, nana_fp)) {
            fp->facing_dir = -nana_fp->facing_dir;
            ftPp_SpecialLw_Enter(fp->gobj);
            return;
        }
        data->lstickX = data->x448->lstickX;
        data->lstickY = data->x448->lstickY;
        data->cstickX = data->x448->cstickX;
        data->cstickY = data->x448->cstickY;
        data->x0 = data->x448->x0;
        data->ltrigger = data->x448->x4;
        data->rtrigger = data->x448->x5;
        if (fp->x2225_b3) {
            fp->cur_pos.x =
                0.95 * fp->cur_pos.x + 0.05 * data->x448->cur_pos.x;
            fp->cur_pos.y =
                0.95 * fp->cur_pos.y + 0.05 * data->x448->cur_pos.y;
            if (fp->motion_id != ftPp_MS_SpecialLw &&
                fp->motion_id != ftPp_MS_SpecialAirLw)
            {
                fp->facing_dir = data->x448->facing_dir;
            }
        }
    }
}

bool ftCo_800B0CA8(Fighter* fp0, Fighter* fp1)
{
    Item_GObj* temp_r5_2;
    enum ItemKind temp_r0;
    s32 temp_r0_2;
    s32 temp_r5;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;

    temp_r5 = fp1->motion_id;
    if (ftCo_800A3200(fp1) != 0) {
        goto jmp_9c;
    } else {
        if (temp_r5 == ftCo_MS_CaptureWaitHi) {
            var_r0_2 = 1;
        } else if (temp_r5 == ftCo_MS_CaptureWaitLw) {
            var_r0_2 = 1;
        } else if (temp_r5 >= ftCo_MS_ShoulderedWait &&
                   temp_r5 <= ftCo_MS_ShoulderedTurn)
        {
            var_r0_2 = 1;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 != 0) {
            goto jmp_9c;
        } else {
            if (temp_r5 == ftCo_MS_Ottotto || temp_r5 == ftCo_MS_OttottoWait) {
                var_r0_3 = 1;
            } else {
                var_r0_3 = 0;
            }
            if (var_r0_3 != 0) {
                /// @todo fakematched control flow
            jmp_9c:
                return false;
            }
            if (temp_r5 >= ftCo_MS_CaptureKirby &&
                temp_r5 <= ftCo_MS_CaptureWaitKirby)
            {
                return false;
            }
            if (temp_r5 >= ftCo_MS_Rebirth && temp_r5 <= ftCo_MS_RebirthWait) {
                return false;
            }
            if (temp_r5 >= ftCo_MS_WarpStarJump &&
                temp_r5 <= ftCo_MS_WarpStarFall)
            {
                return false;
            }
            if (temp_r5 >= ftCo_MS_ItemParasolFall &&
                temp_r5 <= ftCo_MS_ItemParasolDamageFall)
            {
                return false;
            }
            temp_r5_2 = fp0->item_gobj;
            if (temp_r5_2 != NULL) {
                temp_r0 = GET_ITEM(temp_r5_2)->kind;
                switch (temp_r0) {
                case It_Kind_Box:
                case It_Kind_Taru:
                case It_Kind_Kusudama:
                case It_Kind_TaruCann:
                    var_r0_4 = true;
                    break;
                default:
                    var_r0_4 = false;
                }
                if (var_r0_4 != 0) {
                    return false;
                }
            }
            if (fp1->ground_or_air == GA_Ground &&
                fp0->ground_or_air == GA_Air &&
                fp1->cur_pos.y > fp0->cur_pos.y && fp0->pos_delta.y < 0.0f)
            {
                return false;
            }
            if (fp0->x2225_b3) {
                return true;
            }
            switch (fp0->motion_id) {
            case ftCo_MS_Squat:
            case ftCo_MS_SquatWait:
            case ftCo_MS_Landing:
            case ftCo_MS_LandingFallSpecial:
            case ftCo_MS_LandingAirN:
            case ftCo_MS_LandingAirF:
            case ftCo_MS_LandingAirB:
            case ftCo_MS_LandingAirHi:
            case ftCo_MS_LandingAirLw:
                return true;
            }
        }
    }
    return false;
}

static inline bool inlineK0(Fighter* fp0)
{
    if (fp0->motion_id >= 361 && fp0->motion_id <= 366) {
        return true;
    } else {
        return false;
    }
}

bool ftCo_800B0E98(Fighter* fp0, Fighter* fp1)
{
    s32 temp_r0;

    if (ftCo_800B0CA8(fp0, fp1) != 0) {
        struct Fighter_x1A88_t* data = &fp0->x1A88;
        if (fp1->ground_or_air == GA_Air) {
            return false;
        }
        if (fp0->ground_or_air == GA_Air) {
            return false;
        }
        if (!data->xFB_b0) {
            if (inlineK0(fp0)) {
                if (!inlineI1_alt(fp0) && fp0->motion_id != ftCo_MS_Wait) {
                    return false;
                }
                {
                    float x = fp0->pos_delta.x - fp1->pos_delta.x,
                          y = fp0->pos_delta.y - fp1->pos_delta.y,
                          r = fp0->co_attrs.mid_walk_point;
                    if (SQ(x) + SQ(y) > SQ(r)) {
                        return false;
                    }
                }
                {
                    float x = fp0->cur_pos.x - fp1->cur_pos.x,
                          y = fp1->cur_pos.y - fp0->cur_pos.y;
                    if (SQ(x) + SQ(y) < SQ(25.0)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

static inline bool isPopoUpB(Fighter* fp)
{
    if (fp->motion_id >= ftPp_MS_SpecialHi_0 &&
        fp->motion_id <= ftPp_MS_SpecialHi_5)
    {
        return true;
    }
    return false;
}

static inline bool ftCo_800B101C_inline0(Fighter* fp, Fighter* other)
{
    struct Fighter_x1A88_t* temp_r4 = &fp->x1A88;
    if (isPopoUpB(fp)) {
        temp_r4->xFB_b0 = true;
        return true;
    } else {
        float dx = fp->cur_pos.x - other->cur_pos.x;
        float dy = other->cur_pos.y - fp->cur_pos.y;
        if (SQ(dx) + SQ(dy) > SQ(25.0)) {
            return true;
        } else if (ftCo_800B0CA8(fp, other)) {
            return false;
        } else {
            return true;
        }
    }
}

void ftCo_800B101C(Fighter* fp)
{
    HSD_GObj* var_r4;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f3;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r3;
    struct Fighter_x1A88_t* temp_r31;
    Fighter* var_r29;

    PAD_STACK(8);

    temp_r31 = &fp->x1A88;
    temp_r31->xF9_b2 = true;
    temp_r31->xF9_b4 = true;
    var_r29 = ftCo_800A589C(fp);
    if (var_r29 == NULL) {
        ftCo_800AEFB8(fp);
        return;
    }
    ftCo_800B0918(var_r29, fp);

    // Set Nana's AI level based on percent
    temp_f0 = var_r29->dmg.x1830_percent / 20.0F;
    var_r0 = temp_f0;
    if ((int) temp_f0 > 9) {
        var_r0 = 9;
    }
    temp_r31->level = var_r0;

    if (temp_r31->xFA_b7) {
        ftCo_800A7AAC(fp);
        if (ftCo_800B101C_inline0(fp, var_r29)) {
            temp_r31->xFA_b7 = false;
            temp_r31->x18 = temp_r31->x1C;
            fp->x1A88.lstickX = 0;
            fp->x1A88.lstickY = 0;
            fp->x1A88.x0 = 0;
            fp->x1A88.ltrigger = 0;
            fp->x1A88.rtrigger = 0;
        }
    } else {
        ftCo_800B0760_dontinline(fp);
        if (ftCo_800B0E98(fp, var_r29)) {
            temp_r31->x18 = 0;
            temp_r31->xFA_b7 = true;
            temp_r31->xF9_b2 = false;
            temp_r31->xF9_b4 = false;
        }
    }
    if (fp->ground_or_air == GA_Ground) {
        temp_r31->xFB_b0 = false;
    }
}

void ftCo_800B126C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;

    data->xF8_b0 = true;
    data->xF9_b2 = false;
    data->xF9_b4 = false;
    data->xF9_b3 = false;
    data->xF9_b5 = true;
    data->xF9_b6 = true;
    data->xF9_b7 = true;
    data->x2C = 1;
    data->xF9_b1 = false;

    PAD_STACK(0x10);

    fp->x1A88.x44 = ftCo_800A4BEC(fp);
    if (fp->item_gobj != NULL && !ftCo_800A5908(GET_ITEM(fp->item_gobj))) {
        data->x4C = NULL;
    } else {
        if (fp->x2168 != 0) {
            data->x4C = NULL;
        } else {
            data->x4C = ftCo_800A5F4C(fp, It_Kind_L_Gun_Ray);
        }
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);

    if (inlineI1_alt(fp)) {
        if (data->x4C != NULL && fp->item_gobj == NULL) {
            ftCo_800A866C(fp);
        } else if ((data->x7C % 60) * 5 == 0 && HSD_Randf() < 0.5) {
            ftCo_800A8940(fp);
        }
    }
    ftCo_800ADE48(fp);
}

void ftCo_800B1478(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31;
    Fighter** temp_r27;
    Fighter* temp_r3;
    Fighter* var_r4;

    PAD_STACK(0x18);

    temp_r31 = &fp->x1A88;
    temp_r3 = ftCo_800A5CE0(fp);
    temp_r27 = &fp->x1A88.x44;

    fp->x1A88.x44 = temp_r3;

    if (temp_r3 != NULL) {
        temp_r31->xF8_b0 = true;
        temp_r31->xF9_b2 = false;
        temp_r31->xF9_b4 = false;
        temp_r31->xF9_b3 = false;
        temp_r31->xF9_b5 = false;
        temp_r31->xF9_b6 = false;
        temp_r31->xF9_b7 = false;
        temp_r31->xF9_b1 = true;
        ftCo_800A20A0_dontinline(fp);
        if (inlineI1_alt(fp)) {
            ftCo_800A80E4_dontinline(fp);
        }
        ftCo_800ADE48(fp);
        return;
    }

    temp_r31->xF8_b0 = true;
    temp_r31->xF9_b2 = true;
    temp_r31->xF9_b4 = true;
    temp_r31->xF9_b3 = true;
    temp_r31->xF9_b5 = true;
    temp_r31->xF9_b6 = true;
    temp_r31->xF9_b7 = true;
    temp_r31->xF9_b1 = false;

    *temp_r27 = ftCo_800A4BEC(fp);
    if (fp->item_gobj != NULL && !ftCo_800A5908(GET_ITEM(fp->item_gobj))) {
        temp_r31->x4C = NULL;
    } else {
        if (fp->x2168 != 0) {
            temp_r31->x4C = NULL;
        } else {
            temp_r31->x4C = ftCo_800A5F4C(fp, It_Kind_L_Gun_Ray);
        }
    }
    fp->x1A88.x50 = ftCo_800A648C(fp);

    ftCo_800AF78C_inline0(fp);

    if (inlineI1_alt(fp)) {
        if (temp_r31->x4C != NULL) {
            ftCo_800A866C(fp);
        } else {
            var_r4 = ftCo_800A53DC(fp);
            if (var_r4 == NULL) {
                var_r4 = temp_r31->x44;
            }
            ftCo_800A75DC(fp, var_r4);
        }
    }
    ftCo_800ADE48(fp);
}

/// #ftCo_800B17D0

/// #ftCo_800B1AB8

void ftCo_800B1DA0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88;
    PAD_STACK(6 * 4);
    inlineI0(fp, data);
    if (inlineI1(data) && data->x7C % 60 * 5 == 0 && HSD_Randf() < 0.5) {
        ftCo_800A8940(fp);
    }
    ftCo_800ADE48(fp);
}

/// #ftCo_800B1EF0

/// #ftCo_800B21C8

/// #ftCo_800B24B8

/// #ftCo_800B2790

void ftCo_800B1DA0(Fighter*); /* static */

/// #ftCo_800B2AFC

/// #ftCo_800B33B0

void ftCo_800B3900(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);

    ftCo_800B33B0(fp);
    ftCo_800B2AFC(fp);
    ftCo_800B2790(fp);
    ftCo_800B3E04(fp);
    ftCo_800B0AF4(fp);
    fp->x1A88.x7C += 1;
}

bool ftCo_800B395C(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp;
    int temp_r0_2;
    struct Fighter_x1A88_t* temp_r30;

    GXColor sp84;
    GXColor sp80;
    Mtx sp50;
    Vec3 sp44;
    Vec3 sp38;

    fp = GET_FIGHTER(gobj);
    temp_r30 = &fp->x1A88;
    if (Player_8003248C(fp->player_id, fp->x221F_b4) == Gm_PKind_Cpu) {
        switch (temp_r30->x18) {
        case 2:
        case 3:
            sp84.r = 0xFF;
            sp80.r = 0xFF;
            sp84.g = 0;
            sp80.g = 0;
            sp84.b = 0;
            sp80.b = 0;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        case 7:
            sp84.r = 0;
            sp80.r = 0;
            sp84.g = 0;
            sp80.g = 0;
            sp84.b = 0xFF;
            sp80.b = 0xFF;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        case 4:
            sp84.r = 0xFF;
            sp80.r = 0xFF;
            sp84.g = 0xFF;
            sp80.g = 0xFF;
            sp84.b = 0xFF;
            sp80.b = 0xFF;
            sp84.a = 0xFF;
            sp80.a = 0xFF;
            break;
        case 10:
            sp84.r = 0xFF;
            sp80.r = 0xFF;
            sp84.g = 0;
            sp80.g = 0;
            sp84.b = 0xFF;
            sp80.b = 0xFF;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        case 1:
            sp84.r = 0;
            sp80.r = 0;
            sp84.g = 0xFF;
            sp80.g = 0xFF;
            sp84.b = 0;
            sp80.b = 0;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        case 18:
            sp84.r = 0;
            sp80.r = 0;
            sp84.g = 0;
            sp80.g = 0;
            sp84.b = 0;
            sp80.b = 0;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        default:
            sp84.r = 0xFF;
            sp80.r = 0xFF;
            sp84.g = 0xFF;
            sp80.g = 0xFF;
            sp84.b = 0;
            sp80.b = 0;
            sp84.a = 0x60;
            sp80.a = 0x60;
            break;
        }
        sp44.x = temp_r30->x54.x;
        sp44.y = temp_r30->x54.y;
        sp44.z = 0.0f;
        PSMTXIdentity(sp50);
        lbColl_800096B4(sp50, sp44, sp44, &sp84, &sp80, 5.0f);
        sp84.r = 0xFF;
        sp84.g = 0xFF;
        sp84.b = 0;
        sp84.a = 0x60;
        if (fp->facing_dir > 0.0) {
            sp44.x = fp->cur_pos.x - temp_r30->x560;
            sp44.y = fp->cur_pos.y + temp_r30->x568;
            sp44.z = fp->cur_pos.z;
            sp38.x = fp->cur_pos.x + temp_r30->x55C;
            sp38.y = fp->cur_pos.y;
            sp38.z = fp->cur_pos.z;
        } else {
            sp44.x = fp->cur_pos.x - temp_r30->x55C;
            sp44.y = fp->cur_pos.y + temp_r30->x568;
            sp44.z = fp->cur_pos.z;
            sp38.x = fp->cur_pos.x + temp_r30->x560;
            sp38.y = fp->cur_pos.y;
            sp38.z = fp->cur_pos.z;
        }
        if (temp_r30->xF8_b7) {
            temp_r0_2 = temp_r30->x7C % 3;
            if (temp_r0_2 == 1) {
                sp84.r = 0xFF;
                sp84.g = 0xFF;
                sp84.b = 0;
                sp84.a = 0xFF;
                lbColl_80009DD4(&sp44, &sp38, &sp84);
            } else if (temp_r0_2 == 2) {
                sp84.r = 0;
                sp84.g = 0;
                sp84.b = 0;
                sp84.a = 0;
                lbColl_80009DD4(&sp44, &sp38, &sp84);
            } else {
                sp84.r = 0xFF;
                sp84.g = 0xFF;
                sp84.b = 0xFF;
                sp84.a = 0xFF;
                lbColl_80009DD4(&sp44, &sp38, &sp84);
            }
        } else {
            lbColl_80009DD4(&sp44, &sp38, &sp84);
        }
        if (temp_r30->x18 == 2) {
            sp84.r = 0xFF;
            sp84.g = 0;
            sp84.b = 0;
            sp84.a = 0x60;
            if (fp->facing_dir > 0.0) {
                sp44.x = fp->cur_pos.x + temp_r30->x6C.x;
                sp44.y = fp->cur_pos.y + temp_r30->x74.y;
                sp44.z = fp->cur_pos.z;
                sp38.x = fp->cur_pos.x + temp_r30->x74.x;
                sp38.y = fp->cur_pos.y + temp_r30->x6C.y;
                sp38.z = fp->cur_pos.z;
            } else {
                sp44.x = fp->cur_pos.x - temp_r30->x74.x;
                sp44.y = fp->cur_pos.y + temp_r30->x74.y;
                sp44.z = fp->cur_pos.z;
                sp38.x = fp->cur_pos.x - temp_r30->x6C.x;
                sp38.y = fp->cur_pos.y + temp_r30->x6C.y;
                sp38.z = fp->cur_pos.z;
            }
            lbColl_80009DD4(&sp44, &sp38, &sp84);
        }
        return true;
    }
    return false;
}
