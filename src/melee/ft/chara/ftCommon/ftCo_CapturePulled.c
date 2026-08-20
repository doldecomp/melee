#include "ftCo_Attack100.h"
#include "ftCo_Lift.h"
#include "ftCo_Throw.h"

#include "ft/chara/ftCommon/inlines.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "lb/lb_00B0.h"
#include "pl/player.h"

static void fn_800DAECC(Fighter_GObj* gobj);
static void fn_800DAEEC(Fighter_GObj* gobj);
static void fn_800DB230(Fighter_GObj* gobj);

float ftCo_800DA824(Fighter* fp)
{
    ftCommonData* co = p_ftCommonData;
    s32 slot;
    s32 handicap;
    f32 temp;
    f32 value;

    slot = Player_80033BB8(fp->player_id) + 1;
    temp = (f32) slot;
    value = co->x364 - temp;
    value = co->x360 * value;
    handicap = Player_GetHandicap(fp->player_id);
    temp = (f32) handicap;
    temp = co->x35C - temp;
    temp = co->x358 * temp + co->x354;
    temp += value;
    return fp->dmg.x1830_percent * co->x368 + temp;
}

void fn_800DA8E4(Fighter_GObj* gobj, Fighter_GObj* victim_gobj, s32 arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim = GET_FIGHTER(victim_gobj);
    ftCommonData* cd;
    f32 v;
    float* cd2;

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = victim_gobj;
    fp->victim_gobj = victim_gobj;
    fp->x221B_b5 = 0;
    fp->x221B_b7 = 0;
    fp->facing_dir = -victim->facing_dir;
    cd = p_ftCommonData;
    cd2 = &cd->x360;
    v = (*cd2) * (cd->x364 - ((f32) (Player_80033BB8(fp->player_id) + 1)));
    {
        f32 s3 = (cd->x35C - (f32) Player_GetHandicap(fp->player_id));
        s3 = cd->x358 * s3 + cd->x354;
        s3 = s3 + v;
        ftCommon_InitGrab(fp, 0, (fp->dmg.x1830_percent * cd->x368) + s3);
    }
    fp->mv.ca.specials.grav = 0.0f;
    fp->mv._[0xC] = 0;
    fp->mv.ca.speciallw.friction = 0.0f;
    fp->mv.ca.speciallw.x4 = 0;
    Fighter_ChangeMotionState(gobj, arg2, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800DAA40(Fighter_GObj* arg0, Fighter_GObj* arg1)
{
    Vec3 sp18;
    Fighter* temp_r31 = GET_FIGHTER(arg0);
    Fighter* temp_r30 = GET_FIGHTER(arg1);
    fn_800DAC78(arg0, &sp18);
    if (temp_r31->ground_or_air == GA_Ground) {
        temp_r30->x2170 = sp18.y + temp_r31->cur_pos.y - temp_r30->cur_pos.y;
    } else {
        temp_r30->x2170 = 0.0f;
        temp_r31->cur_pos.x += sp18.x;
        temp_r31->cur_pos.y += sp18.y;
        temp_r31->cur_pos.z += sp18.z;
    }
}

static inline void fn_800DAADC_applyMotion(s32 msid, Fighter_GObj* arg1,
                                           Fighter_GObj* arg0, Vec3* sp24)
{
    Fighter* temp_r30;
    Fighter* temp_r31;
    fn_800DA8E4(arg0, arg1, msid);
    temp_r30 = GET_FIGHTER(arg0);
    temp_r31 = GET_FIGHTER(arg1);
    fn_800DAC78(arg0, sp24);
    if (temp_r30->ground_or_air == GA_Ground) {
        temp_r31->x2170 = sp24->y + temp_r30->cur_pos.y - temp_r31->cur_pos.y;
    } else {
        temp_r31->x2170 = 0.0F;
        temp_r30->cur_pos.x += sp24->x;
        temp_r30->cur_pos.y += sp24->y;
        temp_r30->cur_pos.z += sp24->z;
    }
}

void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1)
{
    u8 _pad[4];
    Fighter* fp = GET_FIGHTER(arg0);
    Vec3 sp24;
    FtMotionId msid;
    PAD_STACK(4);

    if (fp->ground_or_air == GA_Ground) {
        msid = ftCo_MS_CapturePulledLw;
    } else {
        msid = ftCo_MS_CapturePulledHi;
    }
    fn_800DAADC_applyMotion(msid, arg1, arg0, &sp24);

    fp->coll_cb(arg0);
    HSD_JObjSetTranslate(GET_JOBJ(arg0), &fp->cur_pos);
}

void ftCo_CapturePulledHi_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledHi_IASA(Fighter_GObj* gobj) {}

void fn_800DAC78(Fighter_GObj* gobj, Vec3* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 sp2C;
    Vec3 sp20;

    PAD_STACK(4);

    lb_8000B1CC(GET_FIGHTER(fp->victim_gobj)->mv.co.capturedamage.x18, NULL,
                &sp2C);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &sp20);

    arg1->x = sp2C.x - sp20.x;
    arg1->y = sp2C.y - sp20.y;
    arg1->z = sp2C.z - sp20.z;
}

bool fn_800DAD18(Fighter_GObj* gobj)
{
    Fighter* temp_r31;
    bool var_r3;

    Vec3 tmp;
    Vec3 sp2C;
    Vec3 sp20;

    PAD_STACK(0x8);

    temp_r31 = GET_FIGHTER(gobj);
    lb_8000B1CC(GET_FIGHTER(temp_r31->victim_gobj)->mv.co.capturedamage.x18,
                NULL, &sp20);
    lb_8000B1CC(
        temp_r31->parts[ftParts_GetBoneIndex(temp_r31, FtPart_XRotN)].joint,
        NULL, &sp2C);

    tmp.x = sp20.x - sp2C.x;
    tmp.y = sp20.y - sp2C.y;
    tmp.z = sp20.z - sp2C.z;

    if (tmp.y > p_ftCommonData->x3C4 * temp_r31->x34_scale.y) {
        var_r3 = true;
    } else {
        var_r3 = false;
    }
    temp_r31->cur_pos.x += tmp.x;
    temp_r31->cur_pos.y += tmp.y;
    temp_r31->cur_pos.z += tmp.z;
    return var_r3;
}

void ftCo_CapturePulledHi_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 tmp;
    Vec3 sp2C;
    Vec3 sp20;
    f32 new_var;

    PAD_STACK(8);

    lb_8000B1CC(GET_FIGHTER(fp->victim_gobj)->mv.co.capturedamage.x18, NULL,
                &sp20);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &sp2C);
    tmp.x = sp20.x;
    tmp.x = (new_var = tmp.x - sp2C.x);
    tmp.y = sp20.y - sp2C.y;
    tmp.z = sp20.z - sp2C.z;
    fp->cur_pos.x += tmp.x;
    fp->cur_pos.y += tmp.y;
    fp->cur_pos.z += tmp.z;
}

void ftCo_CapturePulledHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_80083C00(gobj, fn_800DAECC);
    }
}

static void fn_800DAECC(Fighter_GObj* gobj)
{
    fn_800DAEEC(gobj);
}

void fn_800DAEEC(Fighter_GObj* gobj)
{
    register Fighter* temp_r31;
    register Fighter_GObj* temp_r30;
    Fighter* fp;
    Fighter* victim_fp;
    f32 dz;
    f32 dy;
    f32 dx;
    volatile u8 pad10[0x10];
    Vec3 sp34;
    Vec3 sp28;

    temp_r30 = gobj;
    temp_r31 = GET_FIGHTER(temp_r30);

    ftCommon_AirToGroundStateChange(temp_r30, temp_r31,
                                    ftCo_MS_CapturePulledLw, Ft_MF_UpdateCmd);

    fp = GET_FIGHTER(temp_r30);
    victim_fp = GET_FIGHTER(temp_r31->victim_gobj);

    lb_8000B1CC(GET_FIGHTER(fp->victim_gobj)->mv.co.capturedamage.x18, NULL,
                &sp28);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &sp34);

    dx = sp28.x - sp34.x;
    dy = sp28.y - sp34.y;
    dz = sp28.z - sp34.z;

    if (fp->ground_or_air == GA_Ground) {
        victim_fp->x2170 = dy + fp->cur_pos.y - victim_fp->cur_pos.y;
    } else {
        victim_fp->x2170 = 0.0F;
        fp->cur_pos.x += dx;
        fp->cur_pos.y += dy;
        fp->cur_pos.z += dz;
    }
}

void ftCo_CapturePulledLw_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledLw_IASA(Fighter_GObj* gobj) {}

static inline void fn_800DB230_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    Vec3* pos;

    ftCommon_8007D5D4(temp_r31);
    ftCommon_UnlockECB(temp_r31);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CapturePulledHi, Ft_MF_UpdateCmd,
                              temp_r31->cur_anim_frame, 1.0F, 0.0F, NULL);
    fn_800DAA40(gobj, temp_r31->victim_gobj);
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083C00(gobj, fn_800DAECC);
    }
    pos = &temp_r31->cur_pos;
    HSD_JObjSetTranslate(GET_JOBJ(gobj), pos);
}

void ftCo_CapturePulledLw_Phys(Fighter_GObj* gobj)
{
    Fighter_GObj* temp_r30;
    Fighter* temp_r31;
    bool var_r0;
    f32 dz;
    f32 dy;
    f32 dx;
    volatile u8 pad10[0x10];
    Vec3 sp2C;
    Vec3 sp20;
    volatile u8 pad8[8];

    temp_r30 = gobj;
    temp_r31 = GET_FIGHTER(temp_r30);

    lb_8000B1CC(GET_FIGHTER(temp_r31->victim_gobj)->mv.co.capturedamage.x18,
                NULL, &sp20);
    lb_8000B1CC(
        temp_r31->parts[ftParts_GetBoneIndex(temp_r31, FtPart_XRotN)].joint,
        NULL, &sp2C);

    dy = sp20.y - sp2C.y;
    dx = sp20.x - sp2C.x;
    dz = sp20.z - sp2C.z;

    if (dy > p_ftCommonData->x3C4 * temp_r31->x34_scale.y) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }

    temp_r31->cur_pos.x += dx;
    temp_r31->cur_pos.y += dy;
    temp_r31->cur_pos.z += dz;

    if (var_r0) {
        fn_800DB230_inline(temp_r30);
    }
}

void ftCo_CapturePulledLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_8008403C(gobj, fn_800DB230);
    }
}

static void fn_800DB230(Fighter_GObj* gobj)
{
    PAD_STACK(4);
    fn_800DB230_inline(gobj);
}

void ftCo_800DB368(Fighter* attacker_fp, Fighter* fp)
{
    register HSD_JObj* jobj;
    register HSD_JObj* constraint;

    constraint =
        attacker_fp->parts[ftParts_GetBoneIndex(attacker_fp, FtPart_TransN2)]
            .joint;

    if (!fp->x2226_b2) {
        Quaternion rotate;

        jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
        PAD_STACK(0x4);

        rotate.x = rotate.y = rotate.z = rotate.w = 0.0F;
        ftParts_JObjSetRotation(jobj, &rotate);
        HSD_JObjGetTranslation(jobj, &fp->x2174);
        lb_8000C1C0(jobj, constraint);
        fp->x2226_b2 = true;
    }
}

void ftCo_800DB464(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &pos);
    pos.x = (fp->facing_dir * (fp->x1A70.z * fp->x34_scale.y)) + pos.x;
    pos.y += fp->x1A70.y * fp->x34_scale.y;
    pos.z = 0.0f;
    fp->cur_pos = pos;
}

void ftCo_800DB500(Fighter_GObj* gobj)
{
    HSD_JObj* jobj;
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2226_b2) {
        if (ftAnim_8006F368(fp, ftParts_GetBoneIndex(fp, FtPart_XRotN))) {
            jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
            HSD_JObjGetTranslation(jobj, &fp->x2174);
        }
    }

    if (fp->x2226_b2) {
        ftAnim_8006DF0C(fp);
    }
}
