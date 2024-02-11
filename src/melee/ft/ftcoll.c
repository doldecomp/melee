#include <platform.h>
#include "ft/forward.h"
#include "it/forward.h"
#include "lb/forward.h"

#include "ftcoll.h"

#include "fighter.h"
#include "ft_081B.h"
#include "ft_0877.h"
#include "ftcommon.h"
#include "ftlib.h"

#include "ft/types.h"
#include "ftCommon/types.h"
#include "gm/gm_1601.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "lb/lbcollision.h"
#include "lb/types.h"

#include <common_structs.h>
#include <math.h>
#include <placeholder.h>
#include <dolphin/mtx/types.h>
#include <baselib/gobj.h>

// .data
IntVec3 ftColl_803C0C40 = { 141, 142, 143 };
IntVec3 ftColl_803C0C4C = { 107, 108, 109 };

static char ftColl_803C0C58[] = "attack power over 500!! %f\n";
static char ftColl_803C0C74[] = "ftcoll.c";
static char ftColl_803C0C80[] = "damage log over %d!!\n";
static char assert_msg_0[] = "tip log over %d!!\n";
static int ftColl_803C0CAC[] = {
    1000, 1002, 1001, 1004, 1145, 1005, -1, -1, -1,
    1000, 1000, -1,   -1,   1046, -1,   -1, 0,
};
static char ftColl_803C0CF0[] = "in ftCollisionSetHitStatus illegal parts!\n";
static char assert_msg_1[] = "fighter hit num over!\n";
static char assert_msg_2[] = "fighter dynamics hit num over!\n";

struct UnkSize320_t {
    u8 x0[0x320];
};

// .bss
struct UnkSize320_t ftColl_80459278;
struct UnkSize320_t ftColl_80459598;

// .sdata
char* const ftColl_804D3A68;

// .sbss
UNK_T ftColl_804D6558;
UNK_T ftColl_804D655C;
bool* ftColl_804D6560;

// .sdata2
float const ftColl_804D82E0 = 0;
float const ftColl_804D82E4 = 500;
float const ftColl_804D82E8 = 0.5;
float const ftColl_804D82EC = +1;
float const ftColl_804D82F0 = -1;
double const ftColl_804D82F8 = S32_TO_F32;
float const ftColl_804D8300 = deg_to_rad;
double const ftColl_804D8308 = U32_TO_F32;
float const ftColl_804D8310 = F32_MAX;
float const ftColl_804D8314 = 0.01;
float const ftColl_804D8318 = 1e-5;
float const ftColl_804D831C = rad_to_deg;

/// Combo Count Logic
void ftColl_800763C0(Fighter_GObj* attacker, Fighter_GObj* victim,
                     enum_t attack_id)
{
    if (attacker != victim) {
        Fighter* fp = GET_FIGHTER(attacker);
        Fighter_GObj* fp_x2094 = fp->x2094;
        if (fp_x2094 == NULL) {
            fp->x208C = attack_id;
            fp->x2090 = 1;
            fp->x2094 = victim;
        } else if (fp_x2094 == victim) {
            if (attack_id != 1 && fp->x208C == attack_id) {
                ++fp->x2090;
                if (fp->x2090 >= p_ftCommonData->x4C4) {
                    fp->x2092 = p_ftCommonData->x4D8;
                }
            } else {
                fp->x2090 = 0;
                fp->x208C = attack_id;
            }
        }
    }
}

/// Combo Count Logic + Get Attack ID
void ftColl_80076444(Fighter_GObj* attacker, Fighter_GObj* victim)
{
    Fighter* fp = GET_FIGHTER(attacker);
    ftColl_800763C0(attacker, victim, fp->x2068_attackID);
}

/// Combo Count Logic w/ Item Owner
void ftColl_8007646C(Item_GObj* attackItem, Fighter_GObj* victim)
{
    Fighter_GObj* owner = it_8026BC78(attackItem);
    enum_t msid = it_8026BC84(attackItem);

    if (ftLib_80086960(owner)) {
        ftColl_800763C0(owner, victim, msid);
    }
}

/// Check to end combo for victim
void ftColl_800764DC(Fighter_GObj* gobj)
{
    /// @todo #GET_FIGHTER adds an instruction
    Fighter* fp = gobj->user_data;
    if (fp->x2098 != 0) {
        fp->x2098--;
    }
    if (fp->x2094 != NULL) {
        Fighter* fp1 = fp->x2094->user_data;
        if (!fp1->x221C_b6 && fp1->x2098 == 0) {
            fp->x2094 = NULL;
        }
    }
}

inline void comboCount_Push(Fighter* fp)
{
    Vec3* pos = &fp->coll_data.floor.normal;
    float temp_f2;
    float var_f2;
    if ((s32) fp->x2090 < (s32) p_ftCommonData->x4C8) {
        var_f2 = p_ftCommonData->x4D0;
    } else {
        var_f2 = p_ftCommonData->x4D4;
    }
    temp_f2 = fp->facing_dir * var_f2;
    fp->cur_pos.x = -(pos->y * temp_f2 - fp->cur_pos.x);
    fp->cur_pos.y = -(-pos->x * temp_f2 - fp->cur_pos.y);
}

/// Combo count something + adjust FtPart_TopN
void ftColl_80076528(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u16 fp_x2092 = fp->x2092;
    if (fp_x2092 != 0) {
        fp->x2092 = (u16) (fp_x2092 - 1);
        if (fp->victim_gobj == NULL && fp->ground_or_air == GA_Ground) {
            comboCount_Push(fp);
        }
    }
}

/// Clear victim pointer from attacker upon freeing memory?
void ftColl_800765AC(Fighter_GObj* victim)
{
    Fighter_GObj* cur = HSD_GObj_Entities->fighters;
    while (cur != NULL) {
        Fighter* fp = GET_FIGHTER(cur);
        if (victim == fp->x2094) {
            fp->x2094 = NULL;
        }
        cur = cur->next;
    }
}

/// Reset hitbox and phantom collision count?
void ftColl_800765E0(void)
{
    ftColl_804D6558 = NULL;
    ftColl_804D655C = NULL;
}

float ftColl_800765F0(Fighter* fp, Fighter_GObj* victim, float arg2)
{
    Fighter_GObj* cur = fp->victim_gobj;
    if (cur != NULL && !fp->x221B_b5 && cur != victim) {
        arg2 *= p_ftCommonData->x128;
    }
    if (fp->motion_id == ftCo_MS_DamageIce) {
        arg2 *= p_ftCommonData->x714;
    }
    return arg2 * fp->dmg.x182c_behavior;
}

bool ftColl_80076640(Fighter* fp, float* arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_80076764(int arg0, enum_t arg1, enum_t arg2, UNK_T arg3,
                     ftCo_Fighter* arg4, HurtCapsule* arg5)

{
    NOT_IMPLEMENTED;
}

void ftColl_80076808(Fighter* attacker, HitCapsule* arg1, int arg2,
                     Fighter* victim, int arg3)

{
    NOT_IMPLEMENTED;
}

void ftColl_800768A0(void)

{
    NOT_IMPLEMENTED;
}

bool ftColl_8007699C(Fighter* arg1, HitCapsule* hit0, Fighter* arg2,
                     HitCapsule* hit1)
{
    NOT_IMPLEMENTED;
}

bool ftColl_80076CBC(Fighter* arg0, HitCapsule* arg1, Fighter* arg2)
{
    NOT_IMPLEMENTED;
}

bool ftColl_80076ED8(Fighter* arg0, HitCapsule* arg1, Fighter* arg2,
                     HurtCapsule* arg3)
{
    NOT_IMPLEMENTED;
}

void ftColl_80077464(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_80077688(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_80077970(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_80077C60(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_80078384(Fighter* fp, HurtCapsule* hurt, HitCapsule* hit)
{
    NOT_IMPLEMENTED;
}

void ftColl_80078488(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_800784B4(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_80078538(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007861C(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_80078710(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_80078754(Fighter_GObj* arg0, Fighter_GObj* arg1, bool arg2)
{
    NOT_IMPLEMENTED;
}

void ftColl_800787B4(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_800788D4(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007891C(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_80078998(void)
{
    NOT_IMPLEMENTED;
}

extern float const ftColl_804D8310;

inline HitCapsule* HitCapsuleGetPtr(Fighter* fp, u32 i)
{
    return &fp->x914[i];
}

inline void ftGrabDist(Fighter* this_fp, Fighter* victim_fp)
{
    float grab_dist = victim_fp->cur_pos.x - this_fp->cur_pos.x;
    if (grab_dist < F32_MAX) {
        grab_dist = -grab_dist;
    }
    if (grab_dist < this_fp->unk_grab_val) {
        Fighter_GObj* grabbed_fighter = victim_fp->gobj;
        this_fp->x1A5C = grabbed_fighter;
        this_fp->victim_gobj = grabbed_fighter;
        this_fp->x221B_b5 = true;
        this_fp->unk_grab_val = grab_dist;
    }
}

/// Checks for grabbable targets
void ftColl_80078A2C(Fighter_GObj* this_gobj)
{
    Fighter* this_fp;
    Fighter_GObj* victim_gobj;
    Fighter* victim_fp;
    u8 _[16];
    u32 i;
    HitCapsule* this_hit;
    u32 j;
    this_fp = this_gobj->user_data;
    this_fp->victim_gobj = NULL;
    this_fp->unk_grab_val = F32_MAX;
    victim_gobj = HSD_GObj_Entities->fighters;
    while (victim_gobj != NULL) {
        if (ftLib_80086FD4(this_gobj, victim_gobj) == false) {
            victim_fp = victim_gobj->user_data;
            if (((!(victim_fp->x2219_b1)) &&
                 ((!victim_fp->x222A_flag.bits.b0) &&
                  ((gm_8016B168() == false) || (gm_8016B0D4() != false) ||
                   ((u8) victim_fp->x61B_team != (u8) this_fp->x61B_team)) &&
                  ((s32) victim_fp->x1988 == 0) &&
                  ((s32) victim_fp->x198C == 0) &&
                  (!(victim_fp->x221D_b6) &&
                   !(victim_fp->x1A6A & this_fp->x1A68) &&
                   !((victim_fp->x2224_b2))))))
            {
                for (i = 0; i < 4; i++) {
                    this_hit = HitCapsuleGetPtr(this_fp, i);
                    if ((this_hit->state != HitCapsule_Disabled) &&
                        (this_hit->element == (u32) HitElement_Catch) &&
                        ((((this_hit->x40_b2) &&
                           (victim_fp->ground_or_air == GA_Air)) ||
                          ((((u8) this_hit->x40_b3) &&
                            ((s32) victim_fp->ground_or_air == GA_Ground))))))
                    {
                        if (lbColl_8000ACFC(victim_fp, this_hit) == false) {
                            for (j = 0; j < victim_fp->x119E_hurtboxNum; j++) {
                                if ((s32) victim_fp->x11A0_fighterHurtbox[j]
                                        .is_grabbable != false)
                                {
                                    if (lbColl_80007ECC(
                                            this_hit,
                                            &victim_fp
                                                 ->x11A0_fighterHurtbox[j],
                                            ftCommon_8007F804(victim_fp),
                                            this_fp->x34_scale.y,
                                            victim_fp->x34_scale.y,
                                            victim_fp->cur_pos.z) != 0)
                                    {
                                        if (ft_80084CE4(this_fp, victim_fp) ==
                                            false)
                                        {
                                            ftColl_80076808(this_fp, this_hit,
                                                            0, victim_fp, 0);
                                            ftGrabDist(this_fp, victim_fp);
                                        }
                                        goto next_gobj;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    next_gobj:
        victim_gobj = victim_gobj->next;
    }
}

void ftColl_80078C70(Fighter_GObj* this_gobj)
{ // clang-format off
    const static u32 hit_sfx[20];
    Fighter* this_fp;
    HSD_GObj* victim_gobj;
    bool is_same_gobj;
    s32 var_unk;
    Fighter* victim_fp;
    u32 i;
    HitCapsule* temp_r23;
    u32 n;
    u32 m;
    u32 j;
    s32 var_r0_2;
    s32 var_r22;
    s32 var_r17;
    HitCapsule* temp_r16;
    HitCapsule* this_hit;
    s32 var_r4;
    s32 var_r3;
    u8 var_r0;

    this_fp = this_gobj->user_data;

    if (gm_8016B1C4() == 0) {
        victim_gobj = HSD_GObj_Entities->fighters;
        is_same_gobj = false;
        while (victim_gobj != NULL) {
            if (this_gobj == victim_gobj) {
                is_same_gobj = true;
            } else {
                victim_fp = victim_gobj->user_data;
                var_r4 = false;
                if ((victim_fp->x1064_thrownHitbox.owner != NULL)) {
                    if ((u8) this_fp->player_id != (u8) victim_fp->grabber_unk1) {
                        var_r4 = true;
                    } else {
                        goto next_gobj;
                    }
                }
            if ((var_r4 != 0) || ((u8) this_fp->player_id != (u8) victim_fp->player_id)) {
                if ((gm_8016B168() != false) && (gm_8016B0D4() == false) && !(((u8) victim_fp->x2225_b4))) {
                    var_r0 = (victim_fp->x1064_thrownHitbox.owner != NULL) ? victim_fp->x119C_teamUnk : victim_fp->x61B_team;
                    if ((u8) this_fp->x61B_team != var_r0) {
                        goto block_16;
                    }
                } else {
                block_16:
                    if (victim_fp->x1064_thrownHitbox.owner != this_gobj) {
                        if ((is_same_gobj != false) && !(((u8) this_fp->x221B >> 2U) & 1)) {
                            for (var_unk = 0, i = 0; i < (sizeof(this_fp->x914) / sizeof(HitCapsule)); i++) {
                                this_hit = (HitCapsule*) HitCapsuleGetPtr( this_fp, i);
                                if ((this_hit->state != HitCapsule_Disabled) && (!((u8) this_hit->x43_b2) && ((((u32) this_hit->element == (u8) HitElement_Catch) == 0)) && ((u32) this_hit->element != (u8) HitElement_Inert) && ((((this_hit->x40_b0) == 1) != 0)) && ((u32) (((u8) this_hit->x42_b5) == 1) && (((this_hit->x40_b2) && (victim_fp->ground_or_air == GA_Air)) || (((u8) this_hit->x40_b3) && (victim_fp->ground_or_air == GA_Ground))) && (lbColl_8000ACFC(victim_fp, this_hit) == 0)))) { ftColl_804D6560[i] = 1; var_unk++;
                                } else {
                                    ftColl_804D6560[i] = 0;
                                }
                            }
                        }
                        for (j = 0; j < (sizeof(victim_fp->x914) / sizeof(HitCapsule)); j++) {
                            temp_r23 = (HitCapsule*) HitCapsuleGetPtr( victim_fp, j);
                            if ((temp_r23->state != HitCapsule_Disabled) && ((u32) temp_r23->element != (u32) HitElement_Catch) && ((u32) (((u8) temp_r23->x42_b5)) == true) && (((((u8) temp_r23->x40_b2)) && (this_fp->ground_or_air == GA_Air)) || ((((u8) temp_r23->x40_b3)) && ((s32) this_fp->ground_or_air == 0))) && (!(((u8) (temp_r23 ->hit_grabbed_victim_only))) || (((victim_fp->victim_gobj == NULL) != 0)) || !(((u8) victim_fp->x221B_b5)) || (victim_fp->victim_gobj == this_gobj)) && (lbColl_8000ACFC(this_fp, temp_r23) == false)) {
                                var_r22 = var_r0_2 = ((u8) temp_r23->x43_b2 != false) ? true : false;
                                if ((is_same_gobj != false) && (var_r0_2 == false) && (this_gobj != victim_fp->victim_gobj) && ((s32) this_fp->ground_or_air == GA_Ground) && ((s32) victim_fp->ground_or_air == GA_Ground) && !((u8) this_fp->x221B_b5) && ((u32) temp_r23->element != (u32) HitElement_Inert) && ((u32) (((u8) temp_r23->x40_b0)) == true) && (var_unk != 0)) {
                                    var_r17 = 0;
                                    for (m = 0; m < (sizeof(this_fp->x914) / sizeof(HitCapsule)); m++) {
                                        if ((u8) ftColl_804D6560[m] != 0) {
                                            temp_r16 = (HitCapsule*) HitCapsuleGetPtr( this_fp, m);
                                            if (((lbColl_80007AFC( temp_r23, temp_r16, victim_fp ->x34_scale .y, this_fp ->x34_scale .y) != false) && (ftColl_8007699C( victim_fp, temp_r23, this_fp, temp_r16) != false))) {
                                                var_r17 = true;
                                                break;
                                            } else {
                                                continue;
                                            }
                                        }
                                    }
                                    if (var_r17 == false) {
                                        goto block_66;
                                    }
                                } else {
                                block_66:
                                    if (this_fp->x221B_b0) {
                                        var_r3 = true;
                                        if (this_fp->x221B_b3) {
                                            if (1.0F == this_fp->facing_dir) {
                                                if (this_fp->cur_pos .x < victim_fp->cur_pos .x) {
                                                    var_r3 = false;
                                                }
                                            } else if (this_fp->cur_pos .x > victim_fp ->cur_pos.x) {
                                                var_r3 = false;
                                            }
                                        }
                                        if ((((u8) this_fp ->x221B_b4)) && !(((u8) temp_r23->x42_b4))) {
                                            var_r3 = false;
                                        }
                                        if ((var_r3 != false) && (lbColl_80007BCC( temp_r23, &this_fp->shield_hit, ftCommon_8007F804( this_fp), var_r22, victim_fp->x34_scale .y, this_fp->x34_scale.y, this_fp->cur_pos.z) != false)) {
                                            if ((u32) temp_r23 ->element != (u32) HitElement_Inert) {
                                                ftColl_80076CBC( (Fighter*) victim_fp, temp_r23, this_fp);
                                            } else {
                                                victim_fp->x221C_b5 = true;
                                                victim_fp->unk_gobj = this_gobj;
                                                goto block_81;
                                            }
                                        } else {
                                            goto block_81;
                                        }
                                    } else {
                                    block_81:
                                        if (((s32) this_fp->x1988 != 2) && ((s32) this_fp->x198C != 2)) {
                                            for ( n = 0; n < this_fp ->x119E_hurtboxNum; n++) {
                                                if (lbColl_8000805C( temp_r23, &this_fp ->x11A0_fighterHurtbox [n], ftCommon_8007F804( this_fp), var_r22, victim_fp ->x34_scale .y, this_fp ->x34_scale .y, this_fp ->cur_pos .z) != false) {
                                                    if ((u32) temp_r23->element != (u32) HitElement_Inert) {
                                                        if (ftColl_80076ED8((Fighter*) victim_fp, temp_r23, this_fp, &this_fp ->x11A0_fighterHurtbox [n]) != false) {
                                                            if (((s32) this_fp ->x1988 != 0) || ((s32) this_fp ->x198C != 0) || (((u8) this_fp ->x221D >> 1U) & 1) || ((&this_fp->x11A0_fighterHurtbox[n])->tangibility != 0)) {
                                                                ft_80088148(this_fp, hit_sfx [temp_r23 ->sfx_severity], 0x7FU, 0x40U);
                                                                var_r0_2 = true;
                                                            } else {
                                                                var_r0_2 = false;
                                                            }
                                                            if (var_r0_2 == 0) {
                                                                if (((u32) temp_r23 ->sfx_kind == 0xDU) && ((u32) temp_r23 ->sfx_severity == 2)) {
                                                                    this_fp->x215C = lbColl_80005BB0(temp_r23, (0x72 + (this_fp->player_id * 2) + (u8) this_fp->x221F_b4));
                                                                } else {
                                                                    this_fp->x2160 = lbColl_80005BB0(temp_r23, (0x7E + (this_fp ->player_id * 2) + (u8) this_fp ->x221F_b4));
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        victim_fp ->unk_gobj = this_gobj;
                                                    }

                                                    /* if(temp_r23->x70_coll_distance
                                                         * >=
                                                         * p_ftCommonData->x7A8)
                                                         */
                                                    break;

                                                    // else continue;

                                                    // This fix continues to advance the loop if a phantom hit
                                                    // occurs. Done to prevent astronomical edge case where the game exits
                                                    // the code due to hurtbox priority even if the hitbox is making contact with
                                                    // subsequent, lower priority hurtboxes.
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        next_gobj:
            victim_gobj = victim_gobj->next;
        }
    }
} // clang-format on

void ftColl_8007925C(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

extern double const ftColl_804D8308;
extern float const ftColl_804D8314;

void ftColl_80079AB0(void)
{
    NOT_IMPLEMENTED;
}

float ftColl_80079C70(Fighter* arg0, Fighter* arg1, UNK_T arg2, int arg3)
{
    NOT_IMPLEMENTED;
}

float ftColl_80079EA8(Fighter* arg0, HitCapsule* arg1, int arg2)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007A06C(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AB48(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AB80(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007ABD0(HitCapsule* arg0, u32 arg1, Fighter_GObj* arg2)
{
    NOT_IMPLEMENTED;
}

bool ftColl_8007AC68(int arg0)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AC9C(HitCapsule* arg0, int arg1, Fighter_GObj* arg2)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AD18(ftCo_Fighter* fp, HitCapsule* arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AE80(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AEE0(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AEF8(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AF10(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AF28(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AF60(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AFC8(Fighter_GObj* gobj, int arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AFF8(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B064(Fighter_GObj* gobj, enum_t arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B0C0(Fighter_GObj* gobj, Tangibility arg1)
{
    Fighter* fp;
    HurtCapsule* fp1;
    u32 var_r7;

    fp = gobj->user_data;
    var_r7 = 0U;
    fp1 = &fp->x11A0_fighterHurtbox[0];
    while (var_r7 < (u8) fp->x119E_hurtboxNum) {
        fp1->tangibility = arg1;
        var_r7 += 1;
        fp1->x24_b7 = false;
        ++fp1;
    }
    if (arg1 == Vulnerable) {
        M2C_FIELD(fp, u8*, 0x221A) = (u8) (M2C_FIELD(fp, u8*, 0x221A) & ~4);
        return;
    }
    M2C_FIELD(fp, u8*, 0x221A) = (u8) (M2C_FIELD(fp, u8*, 0x221A) | 4);
}

void ftColl_8007B128(s8 arg0, int arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B1B8(Fighter_GObj* gobj, ShieldDesc* shield, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221B_b0 = true;
    fp->x221B_b1 = false;
    fp->x221B_b2 = false;
    fp->x221B_b3 = false;
    fp->x221B_b4 = false;
    fp->shield_hit_cb = cb;
    fp->shield_hit.bone = fp->parts[shield->bone].joint;
    fp->shield_hit.size = shield->radius;
    fp->shield_hit.offset = shield->pos;
}

void ftColl_CreateReflectHit(Fighter_GObj* gobj, ReflectDesc* reflect,
                             HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2218_b3 = true;
    fp->x2218_b4 = false;
    fp->reflect_hit_cb = cb;
    fp->ReflectAttr.x1A30_maxDamage = reflect->x4_max_damage;
    fp->ReflectAttr.x1A34_damageMul = reflect->x18_damage_mul;
    fp->ReflectAttr.x1A38_speedMul = reflect->x1C_speed_mul;
    fp->x2218_b5 = reflect->x20_behavior;
    fp->reflect_hit.bone = fp->parts[reflect->x0_bone_id].joint;
    fp->reflect_hit.size = reflect->x14_size;
    fp->reflect_hit.offset = reflect->x8_offset;
}

void ftColl_CreateAbsorbHit(Fighter_GObj* gobj, AbsorbDesc* absorb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2218_b6 = true;
    fp->x2218_b7 = false;
    fp->absorb_hit.bone = fp->parts[absorb->x0_bone_id].joint;
    fp->absorb_hit.size = absorb->x10_size;
    fp->absorb_hit.offset = absorb->x4_offset;
}

void ftColl_8007B320(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B4E0(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B5AC(Fighter* fp, HurtCapsule* arg1, struct UNK_SAMUS_S2* arg2)
{
    arg1->bone_idx = arg2->parts[0];
    arg1->kind = arg2->parts[1];
    arg1->is_grabbable = arg2->parts[2];
    arg1->tangibility = Vulnerable;
    arg1->bone = fp->parts[arg1->bone_idx].joint;
    arg1->a_offset.x = arg2->vec1.x;
    arg1->a_offset.y = arg2->vec1.y;
    arg1->a_offset.z = arg2->vec1.z;
    arg1->b_offset.x = arg2->vec2.x;
    arg1->b_offset.y = arg2->vec2.y;
    arg1->b_offset.z = arg2->vec2.z;
    arg1->scl = arg2->single_float;
    M2C_FIELD(fp, u8*, 0x221A) = (u8) (M2C_FIELD(fp, u8*, 0x221A) | 2);
}

void ftColl_8007B62C(Fighter_GObj* gobj, int arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B6A0(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B6EC(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B760(Fighter_GObj* gobj, int arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B7A4(Fighter_GObj* gobj, int arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B7FC(Fighter* fp, int arg1)
{
    NOT_IMPLEMENTED;
}

bool ftColl_8007B868(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B8A8(HitCapsule* arg0, Vec3* arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B8CC(Fighter* arg0, Fighter_GObj* arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007B8E8(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_GetWindOffsetVec(Fighter_GObj* gobj, Vec3* arg1)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007BA0C(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007BAC0(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

float ftColl_8007BBCC(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007BC90(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007BE3C(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}
