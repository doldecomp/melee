#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "baselib/jobj.h"
#include "mp/types.h"

#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_CargoWait.h>
#include <melee/ft/chara/ftCommon/ftCo_Damage.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_Fall.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/chara/ftCommon/ftCo_Throw.h>
#include <melee/ft/chara/ftCommon/ftCo_Thrown.h>
#include <melee/ft/chara/ftFox/ftFx_SpecialN.h>
#include <melee/ft/chara/ftMewtwo/ftMt_SpecialN.h>
#include <melee/ft/chara/ftSamus/ftSs_Init.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ft_0DF1.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbcollision.h>
#include <melee/mp/mpcoll.h>
#include <melee/mp/mplib.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

void fn_800DD568(Fighter_GObj* gobj);
void fn_800DD5EC(Fighter_GObj* gobj);
void fn_800DD684(Fighter_GObj* gobj);
bool fn_800DD6E4(Fighter_GObj* gobj, int arg);

void ftCo_800DD100(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;
    if (victim != NULL) {
        if (fp->x221B_b5) {
            ftCo_800DC920(gobj, victim);
        } else {
            ftCo_800DC920(victim, gobj);
        }
        ftCommon_8007D92C(victim);
    }
}

void ftCo_800DD168(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;
    if (victim != NULL) {
        if (fp->x221B_b5) {
            ftCo_800DCFD4(victim);
            ftCo_800DC920(gobj, victim);
        } else {
            ftCo_800DC920(victim, gobj);
            ftCommon_8007D92C(victim);
        }
    }
}

static inline bool ftCo_800DD1E4_inline1(Fighter* fp);
static inline bool ftCo_800DD1E4_inline1(Fighter* fp)
{
    float thresh = p_ftCommonData->x98;
    if ((fp->input.lstick1.x < thresh && fp->input.lstick.x >= thresh) ||
        (fp->input.lstick1.x > -thresh && fp->input.lstick.x <= -thresh))
    {
        return true;
    }
    return false;
}

static inline bool ftCo_800DD1E4_inline2(Fighter* fp);
static inline bool ftCo_800DD1E4_inline2(Fighter* fp)
{
    float thresh = p_ftCommonData->attackhi3_stick_threshold_y;
    if (fp->input.lstick1.y < thresh && fp->input.lstick.y >= thresh) {
        return true;
    }
    return false;
}

static inline bool ftCo_800DD1E4_inline3(Fighter* fp);
static inline bool ftCo_800DD1E4_inline3(Fighter* fp)
{
    float thresh = p_ftCommonData->xB0;
    if (fp->input.lstick1.y > thresh && fp->input.lstick.y <= thresh) {
        return true;
    }
    return false;
}

bool ftCo_800DD1E4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = fp->motion_id;
    if (ftCo_800DD1E4_inline1(fp)) {
        if (fp->input.lstick.x * fp->facing_dir > 0.0f) {
            msid = 219;
        } else {
            msid = 220;
        }
    } else if (ftCo_800DF7F4(fp)) {
        if (fp->input.cstick.x * fp->facing_dir > 0.0f) {
            msid = 219;
        } else {
            msid = 220;
        }
    } else if (ftCo_800DD1E4_inline2(fp) || ftCo_800DF844(fp)) {
        msid = 221;
    } else if (ftCo_800DD1E4_inline3(fp) || ftCo_800DF878(fp)) {
        msid = 222;
    }
    if (msid != fp->motion_id) {
        ftCo_800DD4B0(gobj, msid);
        return true;
    }
    return false;
}

void ftCo_800DD398(Fighter_GObj* gobj, FtMotionId msid, FtMotionId victim_msid,
                   float anim_speed)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(0x10);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp->mv.co.throw.x4 = 0;
    fp->mv.co.throw.x8 = 0;
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, anim_speed, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCo_800DE3FC(fp->victim_gobj, victim_msid, anim_speed);
    switch (fp->kind) {
    case FTKIND_KIRBY:
        if (msid == 221) {
            Fighter* victim = GET_FIGHTER(fp->victim_gobj);
            fp->x2219_b2 = victim->x2219_b2 = 1;
        }
        break;
    case FTKIND_SAMUS:
        ftSs_Init_CreateThrowGrappleBeam(gobj, msid, anim_speed);
        break;
    default:
        break;
    }
    ftColl_8007B7A4(gobj, p_ftCommonData->x348);
}

void ftCo_800DD4B0(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim = GET_FIGHTER(fp->victim_gobj);
    int throw_index = msid - 219;
    FtMotionId victim_msid = throw_index + 239;
    float anim_speed;
    if (fp->ft_data->x0->weight_independent_throws_mask & (1 << throw_index)) {
        anim_speed = 1.0f;
    } else {
        anim_speed =
            1.0f / (victim->ft_data->x0->weight * p_ftCommonData->x37C);
    }
    switch (msid) {
    case 222:
        switch (fp->kind) {
        case FTKIND_GKOOPS:
        case FTKIND_KOOPA:
            if (victim->kind == FTKIND_PEACH || victim->kind == FTKIND_ZELDA) {
                victim_msid = 243;
            }
        default:
            break;
        }
    default:
        break;
    }
    ftCo_800DD398(gobj, msid, victim_msid, anim_speed);
}

void fn_800DD568(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftAnim_SetAnimRate(gobj, 1.0f);
    ftAnim_8006EBA4(gobj);
    if (fp->anim_cb != NULL) {
        fp->anim_cb(gobj);
    }
    fp->mv.co.throw.x4 = 0;
    fp->mv.co.throw.x8 = 1;
    if (fp->victim_gobj != NULL) {
        ftCo_800DE974(fp->victim_gobj);
    }
    ftCommon_8007D7FC(fp);
}

void fn_800DD5EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    while (fp->cmd_vars[0] == 0) {
        ftAnim_8006EBA4(gobj);
    }
    if (fp->anim_cb != NULL) {
        fp->anim_cb(gobj);
    }
    ftAnim_SetAnimRate(gobj, 1.0f);
    fp->mv.co.throw.x4 = 0;
    fp->mv.co.throw.x8 = 1;
    if (fp->victim_gobj != NULL) {
        ftCo_800DE974(fp->victim_gobj);
    }
    ftCommon_8007D7FC(fp);
}

void fn_800DD684(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;
    if (victim != NULL) {
        ftCo_800DC920(gobj, victim);
        ftCo_Fall_Enter(victim);
    }
    ftCo_Fall_Enter(gobj);
}

bool fn_800DD6E4(Fighter_GObj* gobj, int arg)
{
    if (arg != -1 && (mpLineGetFlags(arg) & LINE_FLAG_PLATFORM) == 0) {
        return true;
    }
    return false;
}

inline static bool ftCo_800DD724_inline1(Fighter* fp)
{
    if (fp->throw_flags_b4) {
        fp->throw_flags_b4 = 0;
        return true;
    }
    return false;
}

inline static bool ftCo_800DD724_inline2(Fighter* fp)
{
    if (fp->throw_flags_b3) {
        fp->throw_flags_b3 = 0;
        return true;
    }
    return false;
}

void ftCo_800DD724(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ftCo_800DD724_inline1(fp)) {
        fp->facing_dir = -(fp->facing_dir);
    }
    if (ftCo_800DD724_inline2(fp)) {
        Fighter_GObj* victim = fp->victim_gobj;
        ftCommon_8007E2F4(fp, 0);
        if (victim != NULL) {
            pl_80040614(fp->player_id, fp->x221F_b4,
                        GET_FIGHTER(victim)->grab_timer);
            ftCo_800DE2A8(gobj, victim);
            ftCo_800DE7C0(victim, gobj, fp->motion_id == 222);
        }
    }
    if (fp->cmd_vars[0] != 0 && fp->mv.co.throw.x4 == 0) {
        fp->mv.co.throw.x4 = 1;
        fp->cmd_vars[0] = 0;
        fp->mv.co.throw.xC = fp->x6A4_transNOffset;
        ftAnim_SetAnimRate(gobj, 0.0f);
        if (fp->victim_gobj != NULL) {
            ftCo_800DE920(fp->victim_gobj, fp->cur_anim_frame);
        }
        if (fp->kind == FTKIND_KIRBY && fp->motion_id == 221) {
            fp->x2219_b2 = 0;
            if (fp->victim_gobj != NULL) {
                GET_FIGHTER(fp->victim_gobj)->x2219_b2 = 0;
            }
        }
    }
}

void ftCo_ThrowF_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    ftMt_SpecialN_Shoot(gobj);
    ftCo_800DD724(gobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if (GET_FIGHTER(gobj)->x2222_b0) {
            ftCo_8009B56C(gobj);
        } else {
            ftCommon_8007D92C(gobj);
        }
    }
}

void ftCo_ThrowF_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftCo_ThrowF_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.throw.x4 != 0) {
            fp->self_vel.x = fp->mv.co.throw.xC.z * fp->facing_dir;
            fp->self_vel.y = fp->mv.co.throw.xC.y;
        } else {
            ft_80085134(gobj);
        }
    } else {
        ft_80085004(gobj);
    }
}

void ftCo_ThrowF_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.throw.x4 != 0) {
            ft_80083C00(gobj, fn_800DD568);
        } else if (fp->mv.co.throw.x8 == 0) {
            ft_80083CE4(gobj, fn_800DD6E4, fn_800DD5EC);
        } else {
            ft_80083B68(gobj);
        }
    } else {
        ft_800841B8(gobj, fn_800DD684);
    }
}

void ftCo_ThrowB_Anim(Fighter_GObj* gobj)
{
    ftFx_Throw_Anim(gobj);
    ftCo_800DD724(gobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_ThrowB_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftCo_ThrowB_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.fighterthrow.x4 != 0) {
            fp->self_vel.x =
                fp->mv.co.fighterthrow.self_vel_x * fp->facing_dir;
            fp->self_vel.y = fp->mv.co.fighterthrow.self_vel_y;
        } else {
            ft_80085134(gobj);
        }
    } else {
        ft_80085004(gobj);
    }
}

void ftCo_ThrowB_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.throw.x4 != 0) {
            ft_80083C00(gobj, fn_800DD568);
        } else if (fp->mv.co.throw.x8 == 0) {
            ft_80083CE4(gobj, fn_800DD6E4, fn_800DD5EC);
        } else {
            ft_80083B68(gobj);
        }
    } else {
        ft_800841B8(gobj, fn_800DD684);
    }
}

void ftCo_ThrowHi_Anim(Fighter_GObj* gobj)
{
    ftFx_Throw_Anim(gobj);
    ftCo_800DD724(gobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_ThrowHi_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftCo_ThrowHi_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.fighterthrow.x4 != 0) {
            fp->self_vel.x =
                fp->mv.co.fighterthrow.self_vel_x * fp->facing_dir;
            fp->self_vel.y = fp->mv.co.fighterthrow.self_vel_y;
        } else {
            ft_80085134(gobj);
        }
    } else {
        ft_80085004(gobj);
    }
}

void ftCo_ThrowHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.throw.x4 != 0) {
            ft_80083C00(gobj, fn_800DD568);
        } else if (fp->mv.co.throw.x8 == 0) {
            ft_80083CE4(gobj, fn_800DD6E4, fn_800DD5EC);
        } else {
            ft_80083B68(gobj);
        }
    } else {
        ft_800841B8(gobj, fn_800DD684);
    }
}

void ftCo_ThrowHi_Cam(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == FTKIND_KIRBY && fp->motion_id == 221) {
        ftCamera_800762F4(gobj);
    } else {
        ftCamera_UpdateCameraBox(gobj);
    }
}

void ftCo_ThrowLw_Anim(Fighter_GObj* gobj)
{
    ftFx_Throw_Anim(gobj);
    ftCo_800DD724(gobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_ThrowLw_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftCo_ThrowLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.fighterthrow.x4 != 0) {
            fp->self_vel.x =
                fp->mv.co.fighterthrow.self_vel_x * fp->facing_dir;
            fp->self_vel.y = fp->mv.co.fighterthrow.self_vel_y;
        } else {
            ft_80085134(gobj);
        }
    } else {
        ft_80085004(gobj);
    }
}

void ftCo_ThrowLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.throw.x4 != 0) {
            ft_80083C00(gobj, fn_800DD568);
        } else if (fp->mv.co.throw.x8 == 0) {
            ft_80083CE4(gobj, fn_800DD6E4, fn_800DD5EC);
        } else {
            ft_80083B68(gobj);
        }
    } else {
        ft_800841B8(gobj, fn_800DD684);
    }
}

static inline float ftCo_800DDDE4_inline3(Fighter* fp3)
{
    return 0.0f;
}

static inline float ftCo_800DDDE4_inline2(Fighter* fp3)
{
    return 0.5f * (fp3->coll_data.ecb.top.y + fp3->coll_data.ecb.bottom.y);
}

void ftCo_800DDDE4(Fighter_GObj* gobj, Fighter_GObj* gobj2, bool arg)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2 = GET_FIGHTER(gobj2);
    HitCapsule* hit = fp->xDF4;
    Fighter* fp3;
    Fighter* fp4;
    Vec vec;
    float damage;
    Vec vec2;
    CollData* cd;
    HSD_JObj* jobj;
    PAD_STACK(0x14);
    if (fp->x221B_b7) {
        fp3 = fp2;
        fp4 = fp;
    } else {
        fp3 = fp;
        fp4 = fp2;
    }
    fp->x1A5C = NULL;
    fp->victim_gobj = NULL;
    fp->x221B_b5 = 0;
    fp->x221B_b7 = 0;
    ftColl_8007891C(gobj, gobj2, hit[0].damage);
    if (fp2->x1988 != 0) {
        ftColl_8007B62C(gobj2, 0);
    }
    lb_8000B1CC(fp3->parts[ftParts_GetBoneIndex(fp3, FtPart_TransN2)].joint,
                NULL, &vec);
    if (ftColl_8007B868(gobj2) == 0) {
        damage = hit[0].damage;
    } else {
        damage = 0.0f;
    }
    ftColl_80076640(fp2, &damage);
    fp2->dmg.kb_applied = ftColl_80079AB0(
        fp2, &hit[0], hit[0].unk_count, gm_8016B248(),
        Player_GetAttackRatio(fp->player_id),
        Player_GetDefenseRatio(fp2->player_id), p_ftCommonData->x10C);
    fp2->dmg.x1848_kb_angle = hit[0].kb_angle;
    fp2->dmg.facing_dir_1 = -(fp->facing_dir);
    fp2->dmg.x184c_damaged_hurtbox = 1;
    fp2->dmg.x1854_collpos = vec;
    fp2->dmg.x1860_element = hit[0].element;
    ftColl_80078710(gobj, gobj2, &fp2->dmg.facing_dir_1);
    ftCommon_8007EE0C(fp, hit[0].damage);
    ftCo_Damage_CalcKnockback(fp2);
    ftCommon_8007D5D4(fp4);
    if (fp4->x2226_b2) {
        HSD_JObj* jobj2 =
            fp4->parts[ftParts_GetBoneIndex(fp4, FtPart_XRotN)].joint;
        lb_8000C390(jobj2);
        fp4->x2226_b2 = 0;
        HSD_JObjSetTranslate(jobj2, &fp4->x2174);
        if (arg) {
            vec.x += fp4->facing_dir * (fp4->x1A70.z * fp4->x34_scale.y);
            vec.y += fp4->x1A70.y * fp4->x34_scale.y;
            vec.z = 0.0f;
        }
        cd = &fp4->coll_data;
        jobj = GET_JOBJ(fp4->gobj);
        vec2.x = fp3->cur_pos.x + ftCo_800DDDE4_inline3(fp3);
        vec2.y = fp3->cur_pos.y + ftCo_800DDDE4_inline2(fp3);
        vec2.z = fp3->cur_pos.z + ftCo_800DDDE4_inline3(fp3);
        fp4->coll_data.last_pos = vec2;
        mpColl_80043670(cd);
        cd->cur_pos = vec;
        HSD_JObjSetTranslate(jobj, &vec);
        ftCommon_UnlockECB(fp4);
        mpColl_800471F8(cd);
        fp4->cur_pos = cd->cur_pos;
        HSD_JObjSetTranslate(jobj, &fp4->cur_pos);
    }
    fp2->x1A5C = NULL;
    fp2->victim_gobj = NULL;
    fp2->x221B_b7 = 0;
}

void ftCo_800DE2A8(Fighter_GObj* gobj, Fighter_GObj* other)
{
    ftCo_800DDDE4(gobj, other, true);
}

void ftCo_800DE2CC(Fighter_GObj* gobj, Fighter_GObj* other)
{
    ftCo_800DDDE4(gobj, other, false);
}

void ftCo_800DE2F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* attrs = &fp->co_attrs;
    HitCapsule hit;
    Vec vec;
    PAD_STACK(4);
    lbColl_80008D30(&hit, &p_ftCommonData->x380);
    ftColl_800788D4(gobj);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN2)].joint,
                NULL, &vec);
    fp->dmg.kb_applied =
        ftColl_80079AB0(fp, &hit, hit.unk_count, gm_8016B248(), 1.0f,
                        Player_GetDefenseRatio(fp->player_id), attrs->weight);
    fp->dmg.x1848_kb_angle = hit.kb_angle;
    fp->dmg.facing_dir_1 = fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 1;
    fp->dmg.x1854_collpos = vec;
    fp->dmg.x1860_element = hit.element;
    Fighter_UnkTakeDamage_8006CC30(fp, hit.damage);
    ftCo_Damage_CalcKnockback(fp);
    ftCo_8008E908(gobj, 0.0f);
}
