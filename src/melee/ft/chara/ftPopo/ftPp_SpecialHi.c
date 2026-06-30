

#include "ft/chara/ftPopo/ftPp_SpecialHi.h"

#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Landing.h"
#include "ft/chara/ftPopo/ftPp_SpecialS.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftNana/ftNn_Init.h"
#include "ftPopo/ftPp_Init.h"
#include "it/items/itclimbersstring.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include <math.h>
#include <trigf.h>

static void sdata2_order(void)
{
    (void) 0.0f;
    (void) 0.5;
    (void) 3.0;
    (void) 3.0f;
    (void) 5.0f;
    (void) 1.0f;
    (void) -1.0f;
    (void) 1.5707963267948966;
}

static inline float my_sqrtf(float x, volatile float* y)
{
    if (x > 0) {
        double guess = __frsqrte(x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        *y = (x * guess);
        return *y;
    }
    return x;
}

void ftPp_SpecialS_80120E68(Fighter_GObj* gobj)
{
    u8 _pad[4];
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    Fighter_GObj* gobj2 = Player_GetEntityAtIndex(fp->player_id, 1);
    volatile float y;
    PAD_STACK(8);

    if (gobj2 != NULL) {
        Fighter* fp2 = GET_FIGHTER(gobj2);
        f32 dx, dy;
        f32 dist;
        fp->self_vel.x = fp2->cur_pos.x - fp->cur_pos.x;
        fp->self_vel.y = fp2->cur_pos.y - fp->cur_pos.y;
        fp->self_vel.z = 0.0F;
        fp->self_vel.x = -(3.0F * fp2->facing_dir - fp->self_vel.x);
        fp->self_vel.y += 5.0F;
        lbVector_Normalize(&fp->self_vel);
        dx = SQ(fp->cur_pos.x - fp2->cur_pos.x);
        dy = SQ(fp->cur_pos.y - fp2->cur_pos.y);
        dist = my_sqrtf(dx + dy, &y) / da->x98;
        fp->self_vel.x *= da->x94 + dist;
        fp->self_vel.y *= da->x94 + dist;
        if (fp->self_vel.x > 0.0F) {
            fp->facing_dir = +1.0F;
        } else {
            fp->facing_dir = -1.0F;
        }
    }
}

bool ftPp_SpecialS_80120FE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 cmd = fp->mv.pp.speciallw.x0;
    PAD_STACK(16);

    if (cmd > 8 && cmd <= 0x53) {
        Item_GObj* item_gobj;
        if ((item_gobj = fp->fv.pp.x2238) != NULL) {
            Item_GObj* gobj = item_gobj;
            Item* ip = item_gobj->user_data;
            itClimbersStringAttributes* sa =
                ip->xC4_article_data->x4_specialAttributes;
            s32 ev0 = sa->x18;
            s32 ev1 = sa->x1C;
            s32 ev2 = sa->x20;
            if (cmd == ev0) {
                it_802C3950(gobj);
            } else if (cmd == ev1) {
                it_802C3810(gobj);
            } else if (cmd == ev2) {
                it_802C3864(gobj);
            }
            if (fp->mv.pp.speciallw.x0 == 0x53) {
                it_802C2750(fp->fv.pp.x2238);
            }
        } else {
            goto end;
        }
    } else if (fp->mv.pp.speciallw.x0 == 8) {
        ftPp_SpecialS_801210C8(gobj);
        if (fp->fv.pp.x2238 == NULL) {
            ft_8008A2BC(gobj);
            return true;
        }
    }
    return false;
end: {
    // original code returns without a value
}
}

void ftPp_SpecialS_801210C8(Fighter_GObj* arg0)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(arg0);
    float dir;
    lb_8000B1CC(fp->parts[FtPart_L4thNb].joint, NULL, &sp10);
    dir = fp->facing_dir;
    fp->fv.pp.x2238 = it_802C27D4(arg0, &sp10, fp->motion_id, dir);
    fp->x1984_heldItemSpec = fp->fv.pp.x2238;
    if (fp->fv.pp.x2238 != NULL) {
        fp->death3_cb = ftPp_Init_8011F060;
        fp->take_dmg_cb = ftPp_Init_8011F060;
    }
}

void ftPp_SpecialS_8012114C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.pp.x2238 = NULL;
    fp->death3_cb = NULL;
    fp->take_dmg_cb = NULL;
}

void ftPp_SpecialS_80121164(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pp.x2238 != NULL) {
        it_802C2750(fp->fv.pp.x2238);
        ftPp_SpecialS_8012114C(gobj);
    }
}

void ftPp_SpecialHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;

    fp->gr_vel /= da->x84;

    ftPp_SpecialHi_801218AC(gobj);

    fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp = GET_FIGHTER(gobj);
    fp->mv.pp.unk_80123954.x0 = 1;
    fp->fv.pp.x223C = 0;
    fp->fv.pp.x2240.z = 0.0f;
    fp->fv.pp.x2240.y = 0.0f;
    fp->fv.pp.x2240.x = 0.0f;
}
void ftPp_SpecialAirHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(16);

    fp->self_vel.x /= da->x84;
    fp->self_vel.y /= da->x88;

    ftPp_SpecialHi_801218F8(gobj);

    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;

    fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp = GET_FIGHTER(gobj);
    fp->mv.pp.unk_80123954.x0 = 1;
    fp->fv.pp.x223C = 0;
    fp->fv.pp.x2240.z = 0.0f;
    fp->fv.pp.x2240.y = 0.0f;
    fp->fv.pp.x2240.x = 0.0f;
}

static inline bool checkNanaInRange(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    Fighter_GObj* nana_gobj = Player_GetEntityAtIndex(fp->player_id, 1);
    if (nana_gobj != NULL) {
        Vec3* nana_pos = &GET_FIGHTER(nana_gobj)->cur_pos;
        f32 dx = SQ(fp->cur_pos.x - nana_pos->x);
        f32 dy = SQ(fp->cur_pos.y - nana_pos->y);
        if (sqrtf__Ff(dx + dy) < da->x7C &&
            ftNn_Init_8012300C(nana_gobj) == true)
        {
            return true;
        }
    }
    return false;
}

static inline void incrementMvAndCheck(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pp.unk_80123954.x0++;
    ftPp_SpecialS_80120FE0(gobj);
}

void ftPp_SpecialHiStart_0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(24);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (!checkNanaInRange(gobj)) {
            ftPp_SpecialHi_80122098(gobj);
            return;
        }
        fp->x2222_b2 = true;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPp_SpecialHi_80121DA0(gobj);
    } else {
        incrementMvAndCheck(gobj);
    }
}

void ftPp_SpecialAirHiStart_0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(24);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (!checkNanaInRange(gobj)) {
            ftPp_SpecialHi_801220D4(gobj);
            return;
        }
        fp->x2222_b2 = true;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPp_SpecialHi_80121DD8(gobj);
        return;
    }
    incrementMvAndCheck(gobj);
}

void ftPp_SpecialHiStart_0_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        if (ABS(fp->input.lstick.x) > da->x80) {
            ftCommon_UpdateFacing(fp);
            ftPartSetRotY(fp, 0, (float) (M_PI_2 * fp->facing_dir));
        }
    }
}

void ftPp_SpecialAirHiStart_0_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        if (ABS(fp->input.lstick.x) > da->x80) {
            ftCommon_UpdateFacing(fp);
            ftPartSetRotY(fp, 0, (float) (M_PI_2 * fp->facing_dir));
        }
    }
}

void ftPp_SpecialHiStart_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    Vec3 sp;
    PAD_STACK(8);

    ft_80084F3C(gobj);
    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_id, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->fv.pp.x2240 = sp;
}

void ftPp_SpecialAirHiStart_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    Vec3 sp;
    PAD_STACK(16);

    ftCommon_Fall(fp, da->x8C, da->x90);
    ftCommon_8007CEF4(fp);

    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_id, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->fv.pp.x2240 = sp;
}

void ftPp_SpecialHiStart_0_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftPp_SpecialHi_801217EC(gobj);
    }
}
void ftPp_SpecialAirHiStart_0_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facingDir;
    if (fp->facing_dir < 0.0f) {
        facingDir = -1;
    } else {
        facingDir = 1;
    }
    if (ft_CheckGroundAndLedge(gobj, facingDir)) {
        ftPp_SpecialHi_8012184C(gobj);
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

void ftPp_SpecialHi_801217EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x160, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_8012184C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15B, 0x0C4C508AU, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_801218AC(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x15B, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftPp_SpecialHi_801218F8(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x160, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftPp_SpecialHiThrow_0_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(40);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }

    {
        Fighter* fp = gobj->user_data;
        if (fp->cmd_vars[1] != 0) {
            fp->cmd_vars[1] = 0;
            {
                int found;
                Fighter_GObj* nn_gobj =
                    Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_id, 1);
                if (nn_gobj != NULL && ftNn_Init_8012309C(nn_gobj) == 1) {
                    found = 1;
                } else {
                    found = 0;
                }
                if (found == 1) {
                    ftPp_SpecialHi_8012280C(gobj);
                    return;
                }
            }
        }
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        ++fp->mv.pp.unk_80123954.x0;
        ftPp_SpecialS_80120FE0(gobj);
    }
}

void ftPp_SpecialAirHiThrow_0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(48);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, false, da->x74, da->x78);
    }

    {
        Fighter* fp = gobj->user_data;
        if (fp->cmd_vars[1] != 0) {
            fp->cmd_vars[1] = 0;
            {
                int found;
                Fighter_GObj* nn_gobj =
                    Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_id, 1);
                if (nn_gobj != NULL && ftNn_Init_8012309C(nn_gobj) == 1) {
                    found = 1;
                } else {
                    found = 0;
                }
                if (found == 1) {
                    ftPp_SpecialHi_8012280C(gobj);
                    return;
                }
            }
        }
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        ++fp->mv.pp.unk_80123954.x0;
        ftPp_SpecialS_80120FE0(gobj);
    }
}

void ftPp_SpecialHiThrow_0_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiThrow_0_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialHiThrow_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    Vec3 sp;
    PAD_STACK(8);

    ft_80084F3C(gobj);
    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_id, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->fv.pp.x2240 = sp;
}

static inline void doFallPhys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    ftCommon_Fall(fp, da->x8C, da->x90);
    ftCommon_8007CEF4(fp);
}

void ftPp_SpecialAirHiThrow_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    Vec3 sp;
    PAD_STACK(12);

    doFallPhys(gobj);
    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_id, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->fv.pp.x2240 = sp;
}

void ftPp_SpecialHiThrow_0_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftPp_SpecialHi_80121CE0(gobj);
    }
}
void ftPp_SpecialAirHiThrow_0_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facingDir;

    if (fp->facing_dir < 0.0f) {
        facingDir = -1;
    } else {
        facingDir = 1;
    }

    if (ft_CheckGroundAndLedge(gobj, facingDir)) {
        ftPp_SpecialHi_80121D40(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

void ftPp_SpecialHi_80121CE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x161, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_80121D40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15C, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_80121DA0(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x15C, 0, 0.0f, 1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_80121DD8(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x161, 0, 0.0f, 1.0f, 0.0f, NULL);
}

void ftPp_SpecialHiStart_1_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPp_SpecialHi_80122348(gobj);
    }
}

void ftPp_SpecialAirHiStart_1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        fp->self_vel.y = da->xA4;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPp_SpecialHi_80122380(gobj);
    }
}

void ftPp_SpecialHiStart_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiStart_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialHiStart_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPp_SpecialAirHiStart_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    ftCommon_Fall(fp, da->xA8, da->xAC);
    if (fp->self_vel.y < 0.0f) {
        ftCommon_8007CEF4(fp);
    }
}

void ftPp_SpecialHiStart_1_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPp_SpecialHi_80121FD8(gobj);
    }
}

void ftPp_SpecialAirHiStart_1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facingDir;

    if (fp->facing_dir < 0.0f) {
        facingDir = -1;
    } else {
        facingDir = 1;
    }

    if (ft_CheckGroundAndLedge(gobj, facingDir)) {
        ftPp_SpecialHi_80122038(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

void ftPp_SpecialHi_80121FD8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x163, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_80122038(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15E, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_80122098(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x15E, 0, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
}

void ftPp_SpecialHi_801220D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x163, 0, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
}

void ftPp_SpecialHiThrow_1_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}
void ftPp_SpecialAirHiThrow_1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, false, da->x74, da->x78);
    }
}

void ftPp_SpecialHiThrow_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiThrow_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialHiThrow_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPp_SpecialAirHiThrow_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    ftCommon_Fall(fp, da->xA8, da->xAC);
    if (fp->self_vel.y < 0.0f) {
        ftCommon_8007CEF4(fp);
    }
}

void ftPp_SpecialHiThrow_1_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPp_SpecialHi_801222E8(gobj);
    }
}

void ftPp_SpecialAirHiThrow_1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    s32 cliffCatchDir;
    PAD_STACK(4);
    if (fp->facing_dir < 0.0f) {
        cliffCatchDir = -1;
    } else {
        cliffCatchDir = 1;
    }
    if (ft_CheckGroundAndLedge(gobj, cliffCatchDir)) {
        ftCo_LandingFallSpecial_Enter(gobj, false, da->x78);
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

void ftPp_SpecialHi_801222E8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x164, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_80122348(Fighter_GObj* arg0)
{
    Fighter_ChangeMotionState(arg0, 0x15F, 0U, 0.0f, 1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_80122380(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x164, 0, 0.0f, 1.0f, 0.0f, NULL);
}

void ftPp_SpecialHiThrow2_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    } else {
        Fighter* fp = GET_FIGHTER(gobj);
        ++fp->mv.pp.unk_80123954.x0;
        ftPp_SpecialS_80120FE0(gobj);
    }
}

void ftPp_SpecialAirHiThrow2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp;
    ftIceClimberAttributes* da;

    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, 0, da->x74, da->x78);
    } else {
        Fighter* fp2 = GET_FIGHTER(gobj);
        ++fp2->mv.pp.unk_80123954.x0;
        ftPp_SpecialS_80120FE0(gobj);
    }
}

void ftPp_SpecialHiThrow2_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiThrow2_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialHiThrow2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    Vec3 sp;
    PAD_STACK(8);

    ft_80084F3C(gobj);
    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_id, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->fv.pp.x2240 = sp;
}

static inline void doFallPhys2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    ftCo_DatAttrs* co = &fp->co_attrs;
    ftCommon_Fall(fp, da->x9C, da->xA0);
    if (ABS(fp->input.lstick.x) > da->x80) {
        ftCommon_8007D344(fp, 0.0f, co->air_drift_stick_mul * da->xB0,
                          co->air_drift_max * da->xB4);
    } else if (fp->self_vel.y < 0.0f) {
        ftCommon_8007CEF4(fp);
    }
}

static inline void ftPp_SpecialAirHiThrow2_Phys_inline(Fighter_GObj* gobj,
                                                       Vec3* sp)
{
    Fighter_GObj* nn_gobj =
        Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_id, 1);
    if (nn_gobj != NULL) {
        Fighter* nn_fp = GET_FIGHTER(nn_gobj);
        if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
            nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
        {
            lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, sp);
        }
    }
}

void ftPp_SpecialAirHiThrow2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 sp;
    ftIceClimberAttributes* da = fp->dat_attrs;
    ftCo_DatAttrs* co = &fp->co_attrs;
    PAD_STACK(12);

    ftCommon_Fall(fp, da->x9C, da->xA0);
    if (ABS(fp->input.lstick.x) > da->x80) {
        ftCommon_8007D344(fp, 0.0f, co->air_drift_stick_mul * da->xB0,
                          co->air_drift_max * da->xB4);
    } else if (fp->self_vel.y < 0.0f) {
        ftCommon_8007CEF4(fp);
    }
    {
        fp = GET_FIGHTER(gobj);
        sp.x = sp.y = sp.z = 0.0f;
        ftPp_SpecialAirHiThrow2_Phys_inline(gobj, &sp);
        fp->fv.pp.x2240 = sp;
    }
}

void ftPp_SpecialHiThrow2_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPp_SpecialHi_801227AC(gobj);
    }
}

void ftPp_SpecialAirHiThrow2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    CollData* cd = &fp->coll_data;
    PAD_STACK(8);
    if (ft_CheckGroundAndLedge(gobj, (fp->facing_dir < 0) ? -1 : 1)) {
        ftCo_LandingFallSpecial_Enter(gobj, false, da->x78);
    } else if (!ftCliffCommon_80081298(gobj)) {
        if ((cd->env_flags & 0x3F) && fp->self_vel.x > 0.0f) {
            fp->self_vel.x = 0.0f;
        } else if ((cd->env_flags & 0xFC0) && fp->self_vel.x < 0.0f) {
            fp->self_vel.x = 0.0f;
        } else if (cd->env_flags & 0x6000) {
            fp->self_vel.y = 0.0f;
            ftCo_80096900(gobj, 0, 1, false, da->x74, da->x78);
        }
    }
}

void ftPp_SpecialHi_801227AC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x162, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

void ftPp_SpecialHi_8012280C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* co = &fp->co_attrs;
    PAD_STACK(8);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(fp);
    } else {
        fp->x1968_jumpsUsed = co->max_jumps;
    }
    ftPp_SpecialS_80120E68(gobj);
    Fighter_ChangeMotionState(gobj, 0x162, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->x21F8 = ftCommon_8007F76C;
}
