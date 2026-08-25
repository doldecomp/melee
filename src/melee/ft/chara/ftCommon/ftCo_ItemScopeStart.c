#include "ftCo_Attack100.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0CDD.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "it/items/itsscope.h"

typedef struct {
    u8 pad_1A4C[0x1A4C];
    f32 x1A4C; // 0x1A4C
    u8 pad_1A58[0x1A58 - 0x1A50];
    void* x1A58; // 0x1A58
    u8 pad_2340[0x2340 - 0x1A5C];
    f32 x2340; // 0x2340
    f32 x2344; // 0x2344
    s32 x2348; // 0x2348
    u8 x234C;  // 0x234C
} FighterOverlay;

FtMotionId fn_800D769C(Fighter* ft, FtMotionId msid)
{
    if (ft->motion_id >= ftCo_MS_ItemScopeStartEmpty) {
        return msid + 8;
    }
    return msid;
}

void ft_800D76B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (it_8026B594(fp->item_gobj) == false) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeStart, Ft_MF_None,
                                  0.0F, 1.0F, 0.0F, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeStartEmpty,
                                  Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    }

    {
        typedef struct {
            u8 x0[0x2340];
            f32 x2340;
            s32 x2344;
        } ItemScopeVars;
        ItemScopeVars* vars = (ItemScopeVars*) fp;

        ftAnim_8006EBA4(gobj);
        vars->x2340 = 0.0F;
        vars->x2344 = 0;
    }

    ftCommon_8007E79C(fp->gobj, 1);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_800D7938;
}

void ft_800D7770(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (it_8026B594(fp->item_gobj) == false) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeAirStart, Ft_MF_None,
                                  0.0F, 1.0F, 0.0F, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeAirStartEmpty,
                                  Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    }

    {
        typedef struct {
            u8 x0[0x2340];
            f32 x2340;
            s32 x2344;
        } ItemScopeVars;
        ItemScopeVars* vars = (ItemScopeVars*) fp;

        ftAnim_8006EBA4(gobj);
        ftCommon_ClampAirDrift(fp);
        vars->x2340 = 0.0F;
        vars->x2344 = 0;
    }

    ftCommon_8007E79C(fp->gobj, 1);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_800D7938;
}

void fn_800D7830(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    ftCommon_8007D7FC(fp);
    if (fp->motion_id >= ftCo_MS_ItemScopeStartEmpty) {
        msid = ftCo_MS_ItemScopeStartEmpty;
    } else {
        msid = ftCo_MS_ItemScopeStart;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5280, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_800D7938;
}

void fn_800D78B0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    if (fp->motion_id >= ftCo_MS_ItemScopeStartEmpty) {
        msid = ftCo_MS_ItemScopeAirStartEmpty;
    } else {
        msid = ftCo_MS_ItemScopeAirStart;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5280, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_800D7938;
}

void fn_800D7938(Fighter_GObj* gobj)
{
    Fighter_GObj* temp_r30;
    Fighter* temp_r31;
    s32 temp_r4;

    temp_r30 = gobj;
    temp_r31 = GET_FIGHTER(temp_r30);
    if (temp_r31->item_gobj != NULL) {
        temp_r4 = it_80291DAC(temp_r31->item_gobj,
                              (s32) ((FighterOverlay*) temp_r31)->x2340);
        if (temp_r4 != -1) {
            it_80291F14(temp_r31->item_gobj, temp_r4);
        }
        ftCommon_8007E7E4(temp_r30, 1);
    }
}

void ftCo_ItemScopeStart_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirStart_Anim(Fighter_GObj* gobj) {}

void fn_800D79B4(HSD_GObj* gobj, void (*cb_ground)(HSD_GObj*),
                 void (*cb_air)(HSD_GObj*, int))
{
    Fighter* fp = GET_FIGHTER(gobj);
    int item_val;
    s32 stack_var;

    // Define an overlay struct to force direct offset access (prevents address
    // caching in r26/r27)
    typedef struct {
        u8 pad[0x2340];
        f32 timer; // 0x2340
        s32 flag;  // 0x2344
    } FighterOverlay;
    FighterOverlay* fp_ovl = (FighterOverlay*) fp;

    // Use this specific cast to generate the correct 'lfs' instruction for the
    // global int

    if (fp->item_gobj == NULL) {
        return;
    }

    // Access 0x2344 (Flag) via overlay
    if (fp_ovl->flag == 0) {
        if (fp->input.held_inputs & HSD_PAD_A) {
            // Access 0x2340 (Timer) via overlay
            fp_ovl->timer += 1.0F;
        }
    }

    if (!(fp->input.held_inputs & HSD_PAD_A)) {
        fp_ovl->flag = 1;
    }

    // Timer to int conversion
    stack_var = (s32) fp_ovl->timer;

    item_val = it_80291DAC(fp->item_gobj, stack_var);

    // Threshold check (Float vs Float)
    if (fp_ovl->timer >= p_ftCommonData->x5B8) {
        if (!ftAnim_IsFramesRemaining(gobj)) {
            cb_air(gobj, item_val);
        }
    }

    if (fp_ovl->flag == 0) {
        return;
    }

    if (ftAnim_IsFramesRemaining(gobj)) {
        return;
    }

    stack_var = (s32) fp_ovl->timer;

    if (it_80291CF4(fp->item_gobj, stack_var) == 0) {
        cb_ground(gobj);
    } else {
        cb_air(gobj, item_val);
    }
}

void ftCo_ItemScopeStart_IASA(Fighter_GObj* gobj)
{
    fn_800D79B4(gobj, fn_800D7BDC, fn_800D8140);
}

void ftCo_ItemScopeAirStart_IASA(Fighter_GObj* gobj)
{
    fn_800D79B4(gobj, fn_800D7C60, fn_800D81D0);
}

void ftCo_ItemScopeStart_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirStart_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

void ftCo_ItemScopeStart_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D78B0);
}

void ftCo_ItemScopeAirStart_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D7830);
}
