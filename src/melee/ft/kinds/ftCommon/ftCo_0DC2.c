#include "ftCo_Attack100.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/inlines.h"

#include <baselib/jobj.h>

bool fn_800DAD18(Fighter_GObj*);

void fn_800DB5D8(HSD_GObj*);

void ftCo_800DC284(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageHi, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.capturedamage.x4 = 0.0F;
    fn_800DB5D8(gobj);
}

void ftCo_CaptureDamageHi_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DB790(gobj);
    }
}

void ftCo_CaptureDamageHi_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureDamageHi_Phys(Fighter_GObj* gobj)
{
    fn_800DAD18(gobj);
}

/// @todo Fix duplicate ::ft_80083C00 usages
void ftCo_CaptureDamageHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_80083C00(gobj, fn_800DC384);
    }
}

void fn_800DC384(Fighter_GObj* gobj)
{
    fn_800DC404(gobj);
}

void ftCo_800DC3A4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageLw, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.capturedamage.x4 = 0.0F;
    fn_800DB5D8(gobj);
}

void fn_800DC404(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageLw, Ft_MF_UpdateCmd,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);
    fn_800DB5D8(gobj);
    fn_800DAA40(gobj, fp->victim_gobj);
}

void ftCo_CaptureDamageLw_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DBAE4(gobj);
    }
}

void ftCo_CaptureDamageLw_IASA(Fighter_GObj* gobj) {}

static inline void ftCo_CaptureDamageLw_Phys_inline(Fighter_GObj* gobj)
{
    Fighter* fp2;
    Vec3* pos;

    if (fn_800DAD18(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageHi,
                                  Ft_MF_UpdateCmd, fp->cur_anim_frame, 1.0F,
                                  0.0F, NULL);
        fn_800DB5D8(gobj);
        fn_800DAA40(gobj, fp->victim_gobj);

        fp2 = GET_FIGHTER(gobj);
        if (!fp2->x2226_b2) {
            ft_80083C00(gobj, fn_800DC384);
        }

        pos = &fp->cur_pos;
        HSD_JObjSetTranslate(GET_JOBJ(gobj), pos);
    }
}

void ftCo_CaptureDamageLw_Phys(Fighter_GObj* gobj)
{
    ftCo_CaptureDamageLw_Phys_inline(gobj);
}

void ftCo_CaptureDamageLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_8008403C(gobj, fn_800DC624);
    }
}

static inline void fn_800DC624_inline(HSD_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageHi, Ft_MF_UpdateCmd,
                              temp_r31->cur_anim_frame, 1.0F, 0.0F, NULL);
    fn_800DB5D8(gobj);
    fn_800DAA40(gobj, temp_r31->victim_gobj);
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083C00(gobj, fn_800DC384);
    }
    HSD_JObjSetTranslate(GET_JOBJ(gobj), &temp_r31->cur_pos);
}

void fn_800DC624(HSD_GObj* gobj)
{
    PAD_STACK(4);
    fn_800DC624_inline(gobj);
}
