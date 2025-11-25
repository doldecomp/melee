#include "ftcoll.h"

#include "fighter.h"
#include "ft_081B.h"
#include "ft_0877.h"
#include "ftcolanim.h"
#include "ftcommon.h"
#include "ftdevice.h"
#include "ftlib.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/efsync.h"

#include "ft/forward.h"

#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Bury.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/types.h"
#include "gm/gm_unsplit.h"

#include "gr/forward.h"
#include "it/forward.h"

#include "it/it_26B1.h"
#include "lb/lb_00B0.h"
#include "lb/lbcollision.h"
#include "lb/types.h"
#include "pl/plbonuslib.h"

#include <common_structs.h>
#include <math.h>
#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>

/* 07A06C */ static void ftColl_8007A06C(float facing_dir, DmgLogEntry** log,
                                         int idx, bool);
// /* 076808 */ static void ftColl_80076808(Fighter* fp, HitCapsule* hit, int,
//                                          Fighter* victim, bool);

// .data
int ftColl_803C0C40[] = { 141, 142, 143 };
int ftColl_803C0C4C[] = { 107, 108, 109 };

UNUSED static int ftColl_803C0CAC[] = {
    1000, 1002, 1001, 1004, 1145, 1005, -1, -1, -1,
    1000, 1000, -1,   -1,   1046, -1,   -1, 0,
};
UNUSED static char ftColl_803C0CF0[] =
    "in ftCollisionSetHitStatus illegal parts!\n";
UNUSED static char assert_msg_1[] = "fighter hit num over!\n";
UNUSED static char assert_msg_2[] = "fighter dynamics hit num over!\n";

struct UnkSize320_t {
    u8 x0[0x320];
};

// .bss
static DmgLogEntry dmg_log0[20];
struct DmgLogEntry dmg_log1[20];

// .sdata
char* const ftColl_804D3A68;

// .sbss
static size_t dmg_log0_idx;
static size_t dmg_log1_idx;
static s8 ftColl_804D6560[8];

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
    if ((int) fp->x2090 < (int) p_ftCommonData->x4C8) {
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
    dmg_log0_idx = 0;
    dmg_log1_idx = 0;
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

static int getEnvDmg(float dmg)
{
    if (dmg) {
        if ((int) dmg) {
            return dmg;
        }
        return 1;
    }
    return 0;
}

bool ftColl_80076640(Fighter* fp, float* dmg)
{
    int env_dmg = getEnvDmg(*dmg);
    PAD_STACK(4);
    if (fp->x221C_b4) {
        fp->dmg.x1834 -= *dmg;
        if (fp->dmg.x1834 < 0) {
            *dmg = -fp->dmg.x1834;
            fp->x221C_b4 = false;
        }
    }
    if (!fp->x221C_b4) {
        if (*dmg > 500) {
            OSReport("attack power over 500!! %f\n", *dmg);
            HSD_ASSERT(183, 0);
        }
        fp->dmg.x1838_percentTemp += *dmg;
        if (env_dmg > fp->dmg.x183C_applied) {
            fp->dmg.x183C_applied = env_dmg;
        }
        return true;
    }
    return false;
}

void ftColl_80076764(int arg0, enum_t arg1, Fighter_GObj* arg2,
                     DynamicsDesc* arg3, Fighter* fp, FighterHurtCapsule* hurt)
{
    if (dmg_log0_idx < ARRAY_SIZE(dmg_log0)) {
        DmgLogEntry* entry = &dmg_log0[dmg_log0_idx];
        entry->x0 = arg0;
        entry->kind = arg1;
        entry->gobj = arg2;
        entry->unk_anim0 = arg3;
        entry->hurt1 = hurt;
        entry->pos = fp->cur_pos;
        entry->size_of_xC = arg3->count;
        ++dmg_log0_idx;
    } else {
        OSReport("damage log over %d!!\n", ARRAY_SIZE(dmg_log0));
        HSD_ASSERT(249, 0);
    }
}

void ftColl_80076808(Fighter* fp, HitCapsule* hit, int arg2, void* victim,
                     bool arg4)
{
    s8 j;
    size_t i;
    for (i = 0, j = 0; i < ARRAY_SIZE(fp->x914); i++, j++) {
        HitCapsule* cur = &fp->x914[i];
        if (cur->state != HitCapsule_Disabled && cur->x4 == hit->x4 &&
            lbColl_80008688(cur, arg2, victim) && arg4)
        {
            ftColl_804D6560[j] = false;
        }
    }
}

static inline void ftColl_80076808_dontinline(Fighter* fp, HitCapsule* hit,
                                              int arg2, void* victim,
                                              bool arg4)
{
    ftColl_80076808(fp, hit, arg2, victim, arg4);
}

void ftColl_800768A0(Fighter* fp, HitCapsule* dst)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(fp->x914); i++) {
        HitCapsule* hitbox = &fp->x914[i];
        if (hitbox != dst && hitbox->state != HitCapsule_Disabled &&
            hitbox->x4 == dst->x4)
        {
            lbColl_CopyHitCapsule(hitbox, dst);
            return;
        }
    }
    lbColl_80008440(dst);
}

/// @todo Probably the same function as #inlineA1
static inline void inlineA0(Fighter* fp0, Fighter* fp1, HitCapsule* hit1,
                            Vec3* ef_pos, float dmg)
{
    int int_dmg;

    /// @todo <tt>int_dmg = getEnvDmg(dmg);</tt>
    if (dmg) {
        if ((int) dmg) {
            int_dmg = dmg;
        } else {
            int_dmg = 1;
        }
    } else {
        int_dmg = 0;
    }

    {
        /// @todo <tt>ftColl_80076808(fp1, hit1, 3, fp0, true);</tt>
        size_t i;
        s8 j;
        for (i = 0, j = 0; i < ARRAY_SIZE(fp1->x914); i++, j++) {
            HitCapsule* cur = &fp1->x914[i];
            if (cur->state != HitCapsule_Disabled && cur->x4 == hit1->x4 &&
                lbColl_80008688(cur, 3, fp0))
            {
                ftColl_804D6560[j] = 0;
            }
        }
    }

    if (int_dmg > fp1->dmg.int_value) {
        fp1->dmg.int_value = int_dmg;
        if (hit1->x40_b1 == true && fp1->ground_or_air == GA_Ground) {
            fp1->dmg.x191C =
                int_dmg * p_ftCommonData->x3D0 + p_ftCommonData->x3D4;
            {
                float facing_dir;
                if (fp1->cur_pos.x < fp0->cur_pos.x) {
                    facing_dir = +1;
                } else {
                    facing_dir = -1;
                }
                fp1->dmg.facing_dir = facing_dir;
            }
        }
    }

    efSync_Spawn(1052, NULL, ef_pos);
}

static inline bool inlineA1(Fighter* fp0, HitCapsule* hit0, Fighter* fp1,
                            HitCapsule* hit1, Vec3* ef_pos, float dmg)
{
    size_t i;
    int int_dmg;

    /// @todo <tt>int_dmg = getEnvDmg(dmg);</tt>
    if (dmg) {
        if ((int) dmg) {
            int_dmg = dmg;
        } else {
            int_dmg = 1;
        }
    } else {
        int_dmg = 0;
    }

    {
        /// @todo <tt>ftColl_80076808(fp1, hit1, 3, fp0, false);</tt>
        for (i = 0; i < ARRAY_SIZE(fp0->x914); i++) {
            HitCapsule* hit;
            hit = &fp0->x914[i];
            if (hit->state != HitCapsule_Disabled && hit->x4 == hit0->x4) {
                lbColl_80008688(hit, 3, fp1);
            }
        }
    }

    if (int_dmg > fp0->dmg.int_value) {
        fp0->dmg.int_value = int_dmg;
        if (hit0->x40_b1 == true && fp0->ground_or_air == GA_Ground) {
            fp0->dmg.x191C =
                int_dmg * p_ftCommonData->x3D0 + p_ftCommonData->x3D4;
            {
                float facing_dir;
                if (fp1->cur_pos.x > fp0->cur_pos.x) {
                    facing_dir = +1;
                } else {
                    facing_dir = -1;
                }
                fp0->dmg.facing_dir = facing_dir;
            }
        }
    }

    efSync_Spawn(1052, NULL, ef_pos);
    ftColl_800784B4(fp1, hit0, hit1);
    return true;
}

bool ftColl_8007699C(Fighter* fp0, HitCapsule* hit0, Fighter* fp1,
                     HitCapsule* hit1)
{
    Vec3 midpoint;
    PAD_STACK(24);

    midpoint.x = 0.5f * (hit0->hurt_coll_pos.x + hit1->hurt_coll_pos.x);
    midpoint.y = 0.5f * (hit0->hurt_coll_pos.y + hit1->hurt_coll_pos.y);
    midpoint.z = 0.5f * (hit0->hurt_coll_pos.z + hit1->hurt_coll_pos.z);

    {
        float dmg = hit1->damage;
        if ((int) dmg - p_ftCommonData->x3CC < (int) hit0->damage) {
            inlineA0(fp0, fp1, hit1, &midpoint, dmg);
        }
    }

    {
        float dmg = hit0->damage;
        if ((int) dmg - p_ftCommonData->x3CC < (int) hit1->damage) {
            return inlineA1(fp0, hit0, fp1, hit1, &midpoint, dmg);
        }
    }

    return false;
}

static inline bool ftColl_8007699C_dontinline(Fighter* fp0, HitCapsule* hit0,
                                              Fighter* fp1, HitCapsule* hit1)
{
    ftColl_8007699C(fp0, hit0, fp1, hit1);
}

void ftColl_80076CBC(Fighter* fp0, HitCapsule* hit0, Fighter* fp1)
{
    ftColl_80076808(fp0, hit0, 1, fp1, false);

    {
        int int_dmg = getEnvDmg(hit0->damage);
        if (int_dmg > fp0->dmg.x1924) {
            fp0->dmg.x1924 = int_dmg;
            if (fp0->ground_or_air == GA_Ground) {
                fp0->dmg.x1928 = fp1->lightshield_amount * int_dmg;
                {
                    float facing_dir;
                    if (fp1->cur_pos.x > fp0->cur_pos.x) {
                        facing_dir = +1;
                    } else {
                        facing_dir = -1;
                    }
                    fp0->dmg.x192c = facing_dir;
                }
            }
        }

        if (int_dmg > fp1->x19A4) {
            fp1->x19A4 = int_dmg;
            {
                float facing_dir;
                if (fp1->cur_pos.x > fp0->cur_pos.x) {
                    facing_dir = -1;
                } else {
                    facing_dir = +1;
                }
                fp1->specialn_facing_dir = facing_dir;
            }
            fp1->x19B0 = hit0->element;
            fp1->x19A8 = fp0->gobj;
        }

        if (!fp1->x221C_b2) {
            int tmp_dmg = int_dmg + hit0->x34;
            PAD_STACK(4);
            fp1->x19A0_shieldDamageTaken += tmp_dmg < 0 ? 0 : tmp_dmg;
            fp1->x19BC_shieldDamageTaken3 = fp0->player_id;
            fp1->x221F_b6 = fp0->x221F_b4;
            efSync_Spawn(1052, NULL, &hit0->hurt_coll_pos);
        } else {
            ftCo_80094138(fp1);
            ftCo_800BFFD0(fp1, 118, 0);
            ft_PlaySFX(fp1, 104, 0x7F, 0x40);
            pl_8003E150(fp1->player_id, fp1->x221F_b4);
            efSync_Spawn(27, NULL, &hit0->hurt_coll_pos);
        }
    }

    {
        float tmp = fp1->shield_unk0;
        if (fp1->shield_unk0) {
            fp0->x1964 = tmp;
            fp1->x1964 = tmp;
        }
    }
}

struct ftCollSFX {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
};

struct ftCollSFX lbl_803C0C40 = {
    0x8D, 0x8E, 0x8C, 0x6B, 0x6C, 0x6D,
};

/// @todo #ftColl_80076808
inline void inlineB0(Fighter* fp0, HitCapsule* hitbox, Fighter* fp1, int arg3,
                     bool (*cb)(HitCapsule* hit, int arg1, void* fp))
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(fp0->x914); i++) {
        HitCapsule* cur = &fp0->x914[i];
        if (cur->state != HitCapsule_Disabled && cur->x4 == hitbox->x4) {
            cb(cur, arg3, fp1);
        }
    }
}

/// Loop through phantom hit victims
static inline HitCapsuleState checkTipLog(UNK_T victim, HitCapsule* hit)
{
    HitVictim* hit_victims = hit->victims_2;
    usize_t i;
    for (i = 0; i < ARRAY_SIZE(hit->victims_2); i++) {
        if (hit_victims[i].victim == victim) {
            break;
        }
    }

    return i == ARRAY_SIZE(hit->victims_2) ? HitCapsule_Disabled
                                           : HitCapsule_Enabled;
}

static inline bool inlineB1(HitCapsule* hit0)
{
    bool var_r0;
    if (hit0->coll_distance < p_ftCommonData->x7A8) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    return var_r0;
}

static inline bool inlineB2(Fighter* fp1, float dmg, int var_r24_3)
{
    int var_r0_3;
    if (fp1->x221C_b4 == 0) {
        if (dmg > 500.0f) {
            OSReport("attack power over 500!! %f", dmg);
            __assert("ftcoll.c", 183, "0");
        }
        fp1->dmg.x1838_percentTemp =
            (float) (fp1->dmg.x1838_percentTemp + dmg);
        if (var_r24_3 > (int) fp1->dmg.x183C_applied) {
            fp1->dmg.x183C_applied = var_r24_3;
        }
        var_r0_3 = 1;
    } else {
        var_r0_3 = 0;
    }
    return var_r0_3;
}

static inline float inlineB3(Fighter* fp0, HitCapsule* hit0, Fighter* fp1)
{
    HSD_GObj* victim_gobj = fp1->victim_gobj;
    HSD_GObj* gobj = fp0->gobj;
    float ret = hit0->damage;

    if (victim_gobj != NULL && !fp1->x221B_b5 && victim_gobj != gobj) {
        ret *= p_ftCommonData->x128;
    }

    if (fp1->motion_id == ftCo_MS_DamageIce) {
        ret *= p_ftCommonData->x714;
    }

    return ret * fp1->dmg.x182c_behavior;
}

bool ftColl_80076ED8(Fighter* fp0, HitCapsule* hit0, Fighter* fp1,
                     HitCapsule* hit1)
{
    float dmg = inlineB3(fp0, hit0, fp1);
    if (inlineB1(hit0)) {
        if (dmg_log0_idx == 0 && !fp1->dmg.x189C_unk_num_frames) {
            HitCapsuleState state = checkTipLog(fp1, hit0);
            if (state == HitCapsule_Disabled) {
                float temp_dmg = 0.5f * dmg;
                if (!((int) temp_dmg) && dmg) {
                    temp_dmg = 1;
                }

                inlineB0(fp0, hit0, fp1, 0, lbColl_80008820);
                if (fp1->x1988 == 0 && fp1->x198C == 0 && !fp1->x221D_b6 &&
                    hit1->state == HitCapsule_Disabled)
                {
                    size_t count = hit0->unk_count;
                    Fighter* fp = fp0;
                    size_t len = count >> 1;
                    if (len == 0 && count != 0) {
                        len = 1;
                    }
                    if ((int) temp_dmg > fp1->dmg.x1840) {
                        fp1->dmg.x1840 = temp_dmg;
                    }
                    if (fp0->x1064_thrownHitbox.owner != NULL) {
                        fp = GET_FIGHTER(fp0->x1064_thrownHitbox.owner);
                    }
                    {
                        HSD_GObj* gobj = fp->gobj;
                        FighterKind kind = fp->kind;
                        if (dmg_log1_idx < ARRAY_SIZE(dmg_log1)) {
                            DmgLogEntry* entry = &dmg_log1[dmg_log1_idx];
                            entry->x0 = 1;
                            entry->kind = kind;
                            entry->gobj = gobj;
                            entry->hit0 = hit0;
                            entry->hit1 = hit1;
                            entry->pos = hit0->hurt_coll_pos;
                            entry->x20 = temp_dmg;
                            entry->size_of_xC = len;
                            ++dmg_log1_idx;
                        } else {
                            OSReport("tip log over %d!! ",
                                     ARRAY_SIZE(dmg_log1));
                            HSD_ASSERT(272, 0);
                        }
                    }
                }

                ftColl_80078488(fp1);
                return true;
            }
        }
    }

    {
        int int_dmg = getEnvDmg(dmg);

        dmg_log1_idx = 0;
        inlineB0(fp0, hit0, fp1, 0, lbColl_80008688);

        if (int_dmg > fp0->dmg.x1914) {
            fp0->dmg.x1914 = int_dmg;
        }
    }

    if (fp1->x1988 == 0 && fp1->x198C == 0 && !fp1->x221D_b6 &&
        hit1->state == HitCapsule_Disabled)
    {
        int int_dmg = getEnvDmg(dmg);
        if (fp1->x221C_b4) {
            fp1->dmg.x1834 = fp1->dmg.x1834 - dmg;
            if (fp1->dmg.x1834 < 0) {
                dmg = -fp1->dmg.x1834;
                fp1->x221C_b4 = false;
            }
        }
        {
            bool inner_ret;
#ifdef BUGFIX
            inner_ret = false;
#endif
            { /// @todo inline
                if (inlineB2(fp1, dmg, int_dmg)) {
                    Fighter* fp = fp0;
                    if (fp0->x1064_thrownHitbox.owner != NULL) {
                        fp = fp0->x1064_thrownHitbox.owner->user_data;
                    }
                    {
                        size_t len = hit0->unk_count;
                        HSD_GObj* gobj = fp->gobj;
                        FighterKind kind = fp->kind;
                        if (dmg_log0_idx < 20U) {
                            DmgLogEntry* damageLog2 = &dmg_log1[dmg_log1_idx];
                            damageLog2->x0 = 1;
                            damageLog2->kind = kind;
                            damageLog2->gobj = gobj;
                            damageLog2->hit0 = hit0;
                            damageLog2->hit1 = hit1;
                            damageLog2->pos = hit0->hurt_coll_pos;
                            damageLog2->x20 = hit0->damage;
                            damageLog2->size_of_xC = len;
                            dmg_log0_idx++;
                        } else {
                            OSReport("damage log over %d!! ",
                                     ARRAY_SIZE(dmg_log1));
                            HSD_ASSERT(227, 0);
                        }
                        inner_ret = true;
                    }
                }
                ftColl_8007891C(fp0->gobj, fp1->gobj, dmg);
            }

            if (!inner_ret) {
                efSync_Spawn(1052, NULL, &hit0->hurt_coll_pos);
            }
        }

        return true;
    }

    return false;
}

void ftColl_80077464(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_80077688(Item* item, HitCapsule* hurt, Fighter* fp, Vec3* pos,
                     f32 val)
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

static inline int getUnkVal(Fighter* fp, int i)
{
    return i + fp->player_id * 2 + fp->x221F_b4;
}

void ftColl_80078384(Fighter* fp, FighterHurtCapsule* arg1, HitCapsule* arg2)
{
    bool var_r0;
    if (fp->x1988 != 0 || fp->x198C != 0 || fp->x221D_b6 ||
        arg1->capsule.state != HurtCapsule_Enabled)
    {
        ft_PlaySFX(fp, ftColl_803C0C40[arg2->sfx_severity], 0x7F, 0x40);
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (!var_r0) {
        if (arg2->sfx_kind == 0xDU && arg2->sfx_severity == 2U) {
            fp->x215C = lbColl_80005BB0(arg2, getUnkVal(fp, 0x72));
        } else {
            fp->x2160 = lbColl_80005BB0(arg2, getUnkVal(fp, 0x7E));
        }
    }
}

void ftColl_80078488(Fighter* fp)
{
    ft_PlaySFX(fp, 85, 0x7F, 0x40);
}

void ftColl_800784B4(Fighter* arg0, HitCapsule* arg1, HitCapsule* arg2)
{
    if (arg1->element == 3 && arg2->element == 3) {
        ft_PlaySFX(arg0, ftColl_803C0C4C[HSD_Randi(3)], 0x7F, 0x40);
    } else {
        ft_PlaySFX(arg0, 0x6A, 0x7F, 0x40);
    }
}

void ftColl_80078538(void)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007861C(Fighter_GObj* arg0, Fighter_GObj* gobj, int arg2,
                     int arg3, int arg4, UNK_T arg5, int arg6, UNK_T arg7,
                     int arg8);

void ftColl_80078710(Fighter_GObj* arg0, Fighter_GObj* arg1, UNK_T arg2)
{
    Fighter* fp = GET_FIGHTER(arg0);
    PAD_STACK(8);
    ftColl_8007861C(arg0, arg1, 1, fp->kind, fp->x2070.x2070_int, &fp->x2074,
                    fp->x2074.x2088, arg2, 0);
}

void ftColl_80078754(Fighter_GObj* arg0, Fighter_GObj* arg1, bool arg2)
{
    NOT_IMPLEMENTED;
}

void ftColl_800787B4(Item_GObj* arg0, Fighter_GObj* arg1, int arg2)
{
    NOT_IMPLEMENTED;
}

void ftColl_800788D4(Fighter_GObj* gobj)
{
    ftColl_8007861C(0, gobj, 0, -10, 0, 0, 0, 0, 0);
}

void ftColl_8007891C(Fighter_GObj* arg0, Fighter_GObj* arg1, float arg2)
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
    if (grab_dist < 0) {
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
    u32 i;
    HitCapsule* this_hit;
    u32 j;
    PAD_STACK(16);
    this_fp = this_gobj->user_data;
    this_fp->victim_gobj = NULL;
    this_fp->unk_grab_val = F32_MAX;
    victim_gobj = HSD_GObj_Entities->fighters;
    while (victim_gobj != NULL) {
        if (!ftLib_80086FD4(this_gobj, victim_gobj)) {
            victim_fp = victim_gobj->user_data;
            if ((!victim_fp->x2219_b1 &&
                 (!victim_fp->x222A_b0 &&
                  (!gm_8016B168() || gm_8016B0D4() ||
                   victim_fp->team != this_fp->team) &&
                  victim_fp->x1988 == 0 && victim_fp->x198C == 0 &&
                  !victim_fp->x221D_b6 &&
                  !(victim_fp->x1A6A & this_fp->x1A68) &&
                  !victim_fp->x2224_b2)))
            {
                for (i = 0; i < 4; i++) {
                    this_hit = HitCapsuleGetPtr(this_fp, i);
                    if (this_hit->state != HitCapsule_Disabled &&
                        this_hit->element == HitElement_Catch &&
                        ((this_hit->x40_b2 &&
                          victim_fp->ground_or_air == GA_Air) ||
                         (this_hit->x40_b3 &&
                          victim_fp->ground_or_air == GA_Ground)))
                    {
                        if (!lbColl_8000ACFC(victim_fp, this_hit)) {
                            for (j = 0; j < victim_fp->hurt_capsules_len; j++)
                            {
                                if (victim_fp->hurt_capsules[j].is_grabbable) {
                                    if (lbColl_80007ECC(
                                            this_hit,
                                            &victim_fp->hurt_capsules[j]
                                                 .capsule,
                                            ftCommon_8007F804(victim_fp),
                                            this_fp->x34_scale.y,
                                            victim_fp->x34_scale.y,
                                            victim_fp->cur_pos.z) != 0)
                                    {
                                        if (ft_80084CE4(this_fp, victim_fp) ==
                                            false)
                                        {
                                            ftColl_80076808_dontinline(
                                                this_fp, this_hit, 0,
                                                victim_fp, 0);
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
    int var_unk;
    Fighter* victim_fp;
    u32 i;
    HitCapsule* temp_r23;
    u32 n;
    u32 m;
    u32 j;
    int var_r0_2;
    int var_r22;
    int var_r17;
    HitCapsule* temp_r16;
    HitCapsule* this_hit;
    int var_r4;
    int var_r3;
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
                if ((gm_8016B168()) && !gm_8016B0D4() && !(((u8) victim_fp->x2225_b4))) {
                    var_r0 = (victim_fp->x1064_thrownHitbox.owner != NULL) ? victim_fp->x119C_teamUnk : victim_fp->team;
                    if ((u8) this_fp->team != var_r0) {
                        goto block_16;
                    }
                } else {
                block_16:
                    if (victim_fp->x1064_thrownHitbox.owner != this_gobj) {
                        if (is_same_gobj && !this_fp->x221B_b5) {
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
                            if ((temp_r23->state != HitCapsule_Disabled) && ((u32) temp_r23->element != (u32) HitElement_Catch) && ((u32) (((u8) temp_r23->x42_b5)) == true) && (((((u8) temp_r23->x40_b2)) && (this_fp->ground_or_air == GA_Air)) || ((((u8) temp_r23->x40_b3)) && ((int) this_fp->ground_or_air == 0))) && (!(((u8) (temp_r23 ->hit_grabbed_victim_only))) || (((victim_fp->victim_gobj == NULL) != 0)) || !(((u8) victim_fp->x221B_b5)) || (victim_fp->victim_gobj == this_gobj)) && (lbColl_8000ACFC(this_fp, temp_r23) == false)) {
                                var_r22 = var_r0_2 = ((u8) temp_r23->x43_b2 != false) ? true : false;
                                if ((is_same_gobj != false) && (var_r0_2 == false) && (this_gobj != victim_fp->victim_gobj) && ((int) this_fp->ground_or_air == GA_Ground) && ((int) victim_fp->ground_or_air == GA_Ground) && !((u8) this_fp->x221B_b5) && ((u32) temp_r23->element != (u32) HitElement_Inert) && ((u32) (((u8) temp_r23->x40_b0)) == true) && (var_unk != 0)) {
                                    var_r17 = 0;
                                    for (m = 0; m < (sizeof(this_fp->x914) / sizeof(HitCapsule)); m++) {
                                        if ((u8) ftColl_804D6560[m] != 0) {
                                            temp_r16 = (HitCapsule*) HitCapsuleGetPtr( this_fp, m);
                                            if (((lbColl_80007AFC( temp_r23, temp_r16, victim_fp ->x34_scale .y, this_fp ->x34_scale .y) != false) && (ftColl_8007699C_dontinline( victim_fp, temp_r23, this_fp, temp_r16) != false))) {
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
                                        if (((int) this_fp->x1988 != 2) && ((int) this_fp->x198C != 2)) {
                                            for ( n = 0; n < this_fp ->hurt_capsules_len; n++) {
                                                if (lbColl_8000805C( temp_r23, &this_fp ->hurt_capsules [n].capsule, ftCommon_8007F804( this_fp), var_r22, victim_fp ->x34_scale .y, this_fp ->x34_scale .y, this_fp ->cur_pos .z) != false) {
                                                    if ((u32) temp_r23->element != (u32) HitElement_Inert) {
                                      if (ftColl_80076ED8((Fighter*) victim_fp, temp_r23, this_fp, (HitCapsule*)&this_fp ->hurt_capsules [n]) != false) {
                                                            if (((int) this_fp ->x1988 != 0) || ((int) this_fp ->x198C != 0) || this_fp ->x221D_b6 || ((&this_fp->hurt_capsules[n].capsule)->state != 0)) {
                                                                ft_PlaySFX(this_fp, hit_sfx [temp_r23 ->sfx_severity], 0x7FU, 0x40U);
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

float ftColl_80079AB0(Fighter* fp, HitCapsule* hit, int unk_count, float arg3,
                      float attack, float defense, float weight)
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

#pragma push
#pragma dont_inline on
void ftColl_8007A06C(float facing_dir, DmgLogEntry** log, int idx, bool arg3)
{
    NOT_IMPLEMENTED;
}
#pragma pop

void ftColl_8007AB48(Fighter_GObj* gobj)
{
    ftColl_8007A06C(GET_FIGHTER(gobj)->dmg.facing_dir_1,
                    (DmgLogEntry**) &dmg_log0, dmg_log0_idx, true);
}

void ftColl_8007AB80(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007ABD0(HitCapsule* arg0, u32 arg1, Fighter_GObj* arg2)
{
    NOT_IMPLEMENTED;
}

bool ftColl_8007AC68(u32 kb_angle)
{
    if (kb_angle != 361 && p_ftCommonData->unk_kb_angle_min <= kb_angle &&
        kb_angle <= p_ftCommonData->unk_kb_angle_max)
    {
        return true;
    }
    return false;
}

void ftColl_8007AC9C(HitCapsule* arg0, int arg1, Fighter_GObj* arg2)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007AD18(Fighter* fp, HitCapsule* arg1)
{
    Vec3 sp10;
    f32 temp_f1;

    switch (arg1->state) {
    case HitCapsule_Enabled:
        if (arg1->x43_b1) {
            temp_f1 = 1.0f / fp->x34_scale.y;
            sp10.x = arg1->b_offset.x * temp_f1;
            sp10.y = arg1->b_offset.y * temp_f1;
            sp10.z = arg1->b_offset.z * temp_f1;
        } else {
            sp10 = arg1->b_offset;
        }
        lb_8000B1CC(arg1->jobj, &sp10, &arg1->x4C);
        arg1->x58 = arg1->x4C;
        arg1->state = HitCapsule_Unk2;
        break;
    case HitCapsule_Unk2:
        arg1->state = HitCapsule_Max;
    case HitCapsule_Max:
        arg1->x58 = arg1->x4C;
        if (arg1->x43_b1) {
            temp_f1 = 1.0f / fp->x34_scale.y;
            sp10.x = arg1->b_offset.x * temp_f1;
            sp10.y = arg1->b_offset.y * temp_f1;
            sp10.z = arg1->b_offset.z * temp_f1;
        } else {
            sp10 = arg1->b_offset;
        }
        lb_8000B1CC(arg1->jobj, &sp10, &arg1->x4C);
        break;
    case HitCapsule_Disabled:
        break;
    }
}

void ftColl_8007AE80(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;
    for (i = 0; i < ARRAY_SIZE(fp->x914); i++) {
        ftColl_8007AD18(fp, &fp->x914[i]);
    }
}

void ftColl_8007AEE0(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->shield_hit.skip_update_pos = false;
}

void ftColl_8007AEF8(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->reflect_hit.skip_update_pos = false;
}

void ftColl_8007AF10(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->absorb_hit.skip_update_pos = false;
}

void ftColl_8007AF28(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    size_t i;
    for (i = 0; i < fp->hurt_capsules_len; i++) {
        fp->hurt_capsules[i].capsule.skip_update_pos = false;
    }
}

void ftColl_8007AF60(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < (unsigned) fp->x166C; i++) {
        Fighter_x1670_t* temp_r4 = &fp->x1670[i];
        lb_8000B1CC(temp_r4->jobj, &temp_r4->v1, &temp_r4->x18);
    }
}

void ftColl_8007AFC8(Fighter_GObj* gobj, int hit_idx)
{
    lbColl_80008428(&GET_FIGHTER(gobj)->x914[hit_idx]);
}

void ftColl_8007AFF8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;
    for (i = 0; i < ARRAY_SIZE(fp->x914); i++) {
        lbColl_80008428(&fp->x914[i]);
    }
    fp->x2219_b3 = false;
}

void ftColl_8007B064(Fighter_GObj* gobj, int arg1)
{
    HitCapsule* capsule;
    Fighter* fp = GET_FIGHTER(gobj);
    capsule = &fp->x914[arg1];
    lbColl_80008434(capsule);
    lbColl_80008440(capsule);
    fp->x2219_b3 = true;
}

void ftColl_8007B0C0(Fighter_GObj* gobj, HurtCapsuleState arg1)
{
    Fighter* fp = gobj->user_data;
    u32 i;
    for (i = 0; i < fp->hurt_capsules_len; i++) {
        fp->hurt_capsules[i].capsule.state = arg1;
        fp->hurt_capsules[i].capsule.skip_update_pos = false;
    }
    if (arg1 == HurtCapsule_Enabled) {
        fp->x221A_b5 = false;
    } else {
        fp->x221A_b5 = true;
    }
}

/// Set hurt capsule state
void ftColl_8007B128(Fighter_GObj* fighter_gobj, int bone_id,
                     HurtCapsuleState state)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    int i;
    for (i = 0; i < fp->hurt_capsules_len; i++) {
        FighterHurtCapsule* hurt = &fp->hurt_capsules[i];
        int bone_idx = hurt->capsule.bone_idx;
        if (bone_idx == bone_id) {
            hurt->capsule.state = state;
            if (state != HurtCapsule_Enabled) {
                fp->x221A_b5 = 1;
            }
            return;
        }
    }

    OSReport("in ftCollisionSetHitStatus illegal parts!\n");
    HSD_ASSERT(2184, 0);
}

/// @todo @p shield is #AbsorbDesc, and #AbsorbDesc is part of #ShieldDesc
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
    fp->reflecting = true;
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

void ftColl_HurtboxInit(Fighter* fp, FighterHurtCapsule* hurt,
                        ftHurtboxInit* init)
{
    hurt->capsule.bone_idx = init->bone_idx;
    hurt->height = init->height;
    hurt->is_grabbable = init->is_grabbable;
    hurt->capsule.state = HurtCapsule_Enabled;
    hurt->capsule.bone = fp->parts[hurt->capsule.bone_idx].joint;
    hurt->capsule.a_offset = init->a_offset;
    hurt->capsule.b_offset = init->b_offset;
    hurt->capsule.scale = init->scale;
    fp->x221A_b6 = true;
}

void ftColl_8007B62C(Fighter_GObj* gobj, enum_t arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x1988 = arg1;
    switch (arg1) {
    case 0:
        ftCo_800BFFD0(fp, 1, false);
        return;
    case 1:
        ftCo_800BFFD0(fp, 3, false);
        return;
    case 2:
        ftCo_800BFFD0(fp, 2, false);
        return;
    }
}

void ftColl_8007B6A0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2221_b0 = true;
    fp->x1990 = 0;
    fp->x198C = 2;
    ftCo_800BFFD0(fp, 9, false);
}

inline enum_t inlineC0(Fighter* fp)
{
    return ftCo_800C0694(fp);
}

void ftColl_8007B6EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2221_b0 = false;
    {
        s32 x1990 = fp->x1990;
        if (x1990 == 0) {
            x1990 = 0;
            if (fp->x1994) {
                x1990 = 1;
            }
            fp->x198C = x1990;
            if (inlineC0(fp) == 9) {
                ftCo_800C0200(fp, 9);
            }
        }
    }
}

void ftColl_8007B760(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (arg1 > fp->x1990) {
        fp->x1990 = arg1;
    }
    fp->x198C = 2;
    ftCo_800BFFD0(fp, 9, 0);
}

void ftColl_8007B7A4(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (arg1 > fp->x1994) {
        fp->x1994 = arg1;
    }
    fp->x198C = fp->x1990 ? 2 : 1;
    ftCo_800BFFD0(fp, 9, 0);
}

void ftColl_8007B7FC(Fighter* fp, int arg1)
{
    fp->x221D_b6 = true;
    fp->x2004 = arg1;
    ftCo_800BFFD0(fp, 107, 0);
    if (arg1 > it_8026B588()) {
        ft_80088080(fp);
    }
}

s32 ftColl_8007B868(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ret = fp->x221D_b6 ? 1 : 0;
    if (fp->x1988 > ret) {
        ret = fp->x1988;
    }
    if (fp->x198C > ret) {
        ret = fp->x198C;
    }
    return ret;
}

void ftColl_8007B8A8(HitCapsule* hit, Vec3* vec)
{
    hit->jobj = NULL;
    hit->b_offset = *vec;
}

void ftColl_8007B8CC(Fighter* fp, Fighter_GObj* grabber_gobj)
{
    Fighter* grabber_fp = GET_FIGHTER(grabber_gobj);
    fp->x1064_thrownHitbox.owner = grabber_gobj;
    fp->x119C_teamUnk = grabber_fp->team;
    fp->grabber_unk1 = grabber_fp->player_id;
}

void ftColl_8007B8E8(Fighter_GObj* gobj)
{
    Fighter_GObj* curr;
    for (curr = HSD_GObj_Entities->fighters; curr != NULL; curr = curr->next) {
        if (gobj != curr) {
            Fighter* fp = GET_FIGHTER(curr);
            if (fp->x1064_thrownHitbox.owner == gobj) {
                fp->x1064_thrownHitbox.owner = NULL;
            }
        }
    }
}

s32 func_800C0A28(HSD_GObj*, u32, s32); /* extern */

void ftColl_GetWindOffsetVec(HSD_GObj* fgp, Vec3* out_wind)
{
    Fighter* fp = GET_FIGHTER(fgp);
    Vec3 wind;
    out_wind->x = out_wind->y = out_wind->z = 0;
    if (!fp->x2224_b4) {
        int i;
        for (i = 0; i < ft_804D6578.x0; i++) {
            Ground_GObj* grp = ft_80459A68[i].ground;
            if (ft_80459A68[i].ground) {
                if (ftCo_800C0A28(fgp, grp, ft_80459A68[i].type) &&
                    ft_80459A68[i].active_cb(grp, fgp, &wind))
                {
                    out_wind->x += wind.x;
                    out_wind->y += wind.y;
                    out_wind->z += wind.z;
                }
            }
        }
    }
}

void ftColl_8007BA0C(Fighter_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x2219_b1) {
        int i;
        for (i = 0; i < ftDevice_BuryThingCount; i++) {
            struct ftDeviceUnk5* cur = &ftDevice_BuryThings[i];
            UNK_T x0 = cur->x0;
            if (x0 != NULL) {
                ftCommon_BuryType x4 = cur->x4;
                if (ftCo_800C0A28(gobj, x0, x4) && cur->cb(x0, gobj)) {
                    ftCo_800C0874(gobj, x0, x4);
                }
            }
        }
    }
}

void ftColl_8007BAC0(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

float ftColl_8007BBCC(UNUSED Fighter_GObj* gobj)
{
    float dmg = 0;
    size_t i;
    PAD_STACK(2 * 4);
    if (dmg_log0_idx != 0) {
        for (i = 0; i < dmg_log0_idx; i++) {
            DmgLogEntry* entry = &dmg_log0[i];
            switch (entry->kind) {
            case EntityKind_Fighter: {
                HitCapsule* hit = entry->hit0;
                if (hit->element == HitElement_Lipstick) {
                    dmg += hit->damage;
                }
                break;
            }
            case EntityKind_Item: {
                HitCapsule* hit = entry->hit0;
                if (hit->element == HitElement_Lipstick) {
                    dmg += it_8026B1D4(entry->gobj, hit);
                }
                break;
            }
            }
        }
    }
    return dmg;
}

void ftColl_8007BC90(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftColl_8007BE3C(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}
