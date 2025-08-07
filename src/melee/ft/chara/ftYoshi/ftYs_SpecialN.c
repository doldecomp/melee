#include "ftYoshi/ftYs_SpecialN.static.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureYoshi.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftYoshi/ftYs_Init.h"
#include "it/items/it_2F2B.h"
#include "it/items/ityoshieggthrow.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>

/* 3B75C0 */ Vec3 const ftYs_Unk1_803B75C0 = { 0 };
f32 ftYs_Init_804D9A70 = 0.0f;

float ftYs_SpecialN_8012CD10(Fighter_GObj* gobj)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, f32*, 0x28);
}

float ftYs_SpecialN_8012CD28(void)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, f32*, 0x2C);
}

float ftYs_SpecialN_8012CD40(void)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, f32*, 0x30);
}

float ftYs_SpecialN_8012CD58(void)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, f32*, 0x34);
}

int ftYs_SpecialN_8012CD70(void)
{
    return M2C_FIELD(gFtDataList[0xE]->ext_attr, s32*, 0x38);
}

void ftYs_SpecialN_8012CD88(Vec3* arg0)
{
    Fighter* fp = gFtDataList[FTKIND_YOSHI]->ext_attr;
    arg0->x = fp->x34_scale.z; // x3C
    arg0->y = fp->x40;
    arg0->z = 0;
}

f32 ftYs_SpecialN_8012CDB4(Fighter_GObj* gobj)
{
    ftYoshiAttributes* ea = gFtDataList[FTKIND_YOSHI]->ext_attr;
    return ea->x44 / ea->x18;
}

HSD_Joint* ftYs_SpecialN_8012CDD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* ca = fp->ft_data;
    return ca->x48_items[3];
}

void ftYs_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN1, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 4, fn_8012CF7C, fn_8012CEE0, ftCo_800BBB8C);
    }
}

void ftYs_SpecialAirN_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState((Fighter_GObj*) gobj, 0x15F, 0U, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4((Fighter_GObj*) gobj);
    ftCommon_8007E2D0((Fighter*) gobj->user_data, 4,
                      (void (*)(Fighter_GObj*)) fn_8012D0A0,
                      (void (*)(Fighter_GObj*)) fn_8012D004, ftCo_800BBB8C);
}

void fn_8012CEE0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F2BFC(fp->x1A60, gobj);
    Fighter_ChangeMotionState(gobj, 348, 528530, fp->cur_anim_frame, 1, 0,
                              NULL);
    fp->x2222_b2 = true;
    fp->mv.ys.specialn.x0_b0 = true;
    ftYs_SpecialS_8012DF00(gobj);
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void fn_8012CF7C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 347, 528530, fp->cur_anim_frame, 1, 0,
                              NULL);
    fp->x2222_b2 = 1;
    fp->mv.ys.specialn.x0_b0 = false;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void fn_8012D004(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_802F2BFC(fp->x1A60, gobj);
    Fighter_ChangeMotionState((Fighter_GObj*) gobj, 0x161, 0x81092U,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);

    fp->x2222_b2 = 1;
    fp->mv.ys.specialn.x0_b0 = 1;
    ftYs_SpecialS_8012DF00(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC((Fighter_GObj*) gobj);
}

void fn_8012D0A0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    // 0x160 == 352 == ftYs_MS_SpecialAirN1_1
    // 0x81092U == (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) | (1 << 19)
    Fighter_ChangeMotionState(gobj, 0x160, 0x81092U, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);

    fp->x2222_b2 = 1;
    fp->mv.ys.specialn.x0_b0 = false;

    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
}

void fn_8012D128(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x15F, 0x0C4C509AU, fp->cur_anim_frame, 0,
                              1, NULL);
    ftCommon_8007E2D0((Fighter*) gobj->user_data, 4, fn_8012D0A0, fn_8012D004,
                      ftCo_800BBB8C);
}

void fn_8012D1AC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15A, 0x0C4C509AU, fp->cur_anim_frame,
                              0, 1, NULL);
    ftCommon_8007E2D0((Fighter*) gobj->user_data, 4, fn_8012CF7C, fn_8012CEE0,
                      ftCo_800BBB8C);
}

void fn_8012D230(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x161, 0x0C4C5092U, fp->cur_anim_frame, 0,
                              1, NULL);
    ftYs_SpecialS_8012DF00((HSD_GObj*) gobj);
}

extern f32 ftYs_Init_804D9A38;
// Just trying to replace ftYs_Init_804D9A38 with 0 seemed to prevent 100%
// matching
void fn_8012D298(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x160, 0x0C4C5092U, fp->cur_anim_frame, 0,
                              ftYs_Init_804D9A38, NULL);
}

void fn_8012D2F8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15C, 0x0C4C5092U, fp->cur_anim_frame, 0,
                              1, NULL);
    ftYs_SpecialS_8012DF00((HSD_GObj*) gobj);
}

void fn_8012D360(Fighter_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15B, 0x0C4C5092U, fp->cur_anim_frame, 0,
                              ftYs_Init_804D9A38, NULL);
}

void fn_8012D3C0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x163, 0x0C4C5092U, fp->cur_anim_frame, 0,
                              1, NULL);
    ftYs_SpecialS_8012DF00((HSD_GObj*) gobj);
}

void fn_8012D428(Fighter_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x162, 0x0C4C5092U, fp->cur_anim_frame, 0,
                              ftYs_Init_804D9A38, NULL);
}

void fn_8012D488(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15E, 0x0C4C5092U, fp->cur_anim_frame, 0,
                              1, NULL);
    ftYs_SpecialS_8012DF00((HSD_GObj*) gobj);
}

void fn_8012D4F0(Fighter_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15D, 0x0C4C5092U, fp->cur_anim_frame, 0,
                              ftYs_Init_804D9A38, NULL);
}

void ftYs_SpecialN1_Anim(Fighter_GObj* gobj)
{
    u8 _[8]; // brought to full match

    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ft_8008A2BC((Fighter_GObj*) gobj);
    }
}

void ftYs_SpecialAirN1_0_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ftCo_Fall_Enter((Fighter_GObj*) gobj);
    }
}

static void inlineA1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
}

static void inlineA0(Fighter_GObj* gobj, enum_t msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x1A60 != NULL) {
        inlineA1(gobj);
        Fighter_ChangeMotionState(gobj, msid, 0x80012U, 0.0f, 1.0f, 0.0f,
                                  NULL);
        ftYs_SpecialS_8012DF00(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftYs_SpecialN1_1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] != 0) {
        inlineA0(gobj, 0x15E);
    }
}

inline void* Fighter_GetVictimGobj(Fighter* fp)
{
    return fp->victim_gobj;
}

static void ftYs_SpecialN1_0_Anim_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->cmd_vars[0]) && (Fighter_GetVictimGobj(fp) != NULL)) {
        fp->cmd_vars[0] = 0;
        fp->cmd_vars[1] = 0;
        Fighter_ChangeMotionState(gobj, 0x15D, 0x80012U, ftYs_Init_804D9A38,
                                  1, ftYs_Init_804D9A38,
                                  NULL);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftYs_SpecialN1_0_Anim(Fighter_GObj* gobj)
{
    ftYs_SpecialN1_0_Anim_inline(gobj);
}

void ftYs_SpecialAirN1_2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] != 0) {
        inlineA0(gobj, 0x163);
    }
}

/// #ftYs_SpecialAirN1_1_Anim

/// #ftYs_SpecialN2_1_Anim

/// #ftYs_SpecialN2_0_Anim

/// #ftYs_SpecialAirN2_1_Anim

/// #ftYs_SpecialAirN2_0_Anim

void ftYs_SpecialN1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

void ftYs_SpecialAirN1_0_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC((Fighter_GObj*) gobj);
}

void ftYs_SpecialN1_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

void ftYs_SpecialN1_0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

void ftYs_SpecialAirN1_2_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC((Fighter_GObj*) gobj);
}

void ftYs_SpecialAirN1_1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC((Fighter_GObj*) gobj);
}

void ftYs_SpecialN2_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

void ftYs_SpecialN2_0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

void ftYs_SpecialAirN2_1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC((Fighter_GObj*) gobj);
}

void ftYs_SpecialAirN2_0_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC((Fighter_GObj*) gobj);
}

void ftYs_SpecialN1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C((Fighter_GObj*) gobj, fn_8012D128);
}

void ftYs_SpecialAirN1_0_Coll(Fighter_GObj* gobj)
{
    ft_80082C74((Fighter_GObj*) gobj, fn_8012D1AC);
}

void ftYs_SpecialN1_1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C((Fighter_GObj*) gobj, fn_8012D230);
}

void ftYs_SpecialN1_0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C((Fighter_GObj*) gobj, fn_8012D298);
}

void ftYs_SpecialAirN1_2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74((Fighter_GObj*) gobj, fn_8012D2F8);
}

void ftYs_SpecialAirN1_1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74((Fighter_GObj*) gobj, fn_8012D360);
}

void ftYs_SpecialN2_1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C((Fighter_GObj*) gobj, fn_8012D3C0);
}

void ftYs_SpecialN2_0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C((Fighter_GObj*) gobj, fn_8012D428);
}

void ftYs_SpecialAirN2_1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74((Fighter_GObj*) gobj, fn_8012D488);
}

void ftYs_SpecialAirN2_0_Coll(Fighter_GObj* gobj)
{
    ft_80082C74((Fighter_GObj*) gobj, fn_8012D4F0);
}

void ftYs_SpecialS_8012DF00(HSD_GObj* arg0)
{
    void* temp_r3;

    temp_r3 = arg0->user_data;
    M2C_FIELD(temp_r3, void (**)(HSD_GObj*), 0x21DC) = ftYs_Init_8012BA8C;
    M2C_FIELD(temp_r3, void (**)(HSD_GObj*), 0x21E4) = ftYs_Init_8012BA8C;
}

void ftYs_SpecialS_8012DF18(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x1A60 != NULL) {
        ftYoshi_MotionState motion_id = fp->motion_id;
        bool clear_destroy_type = false;
        if (motion_id == ftYs_MS_SpecialN1_1 ||
            motion_id == ftYs_MS_SpecialN2_1 ||
            motion_id == ftYs_MS_SpecialAirN1_2 ||
            motion_id == ftYs_MS_SpecialAirN2_1)
        {
            clear_destroy_type = true;
        }
        it_802F2CE0(fp->x1A60, clear_destroy_type);
        fp->x1A64 = NULL;
        fp->x1A60 = NULL;
    }
}

/// #ftYs_SpecialS_8012DF8C

/// #fn_8012E110

void ftYs_SpecialS_8012E270(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ys.x2238 != NULL && fp->mv.ys.specials.x0 == 0) {
        it_802B2890(fp->fv.ys.x2238);
    }
    fp->fv.ys.x2238 = NULL;
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

/// #ftYs_SpecialHi_Enter

/// #ftYs_SpecialAirHi_Enter

inline void qwe(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8012E110;
}
inline void fn_8012E3B4_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.ys.x2238 != NULL) {
        fp->take_dmg_cb = ftYs_Init_8012BA8C;
        fp->death2_cb = ftYs_Init_8012BA8C;
    }
}
void fn_8012E3B4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16D, 0x0C4C5082U, fp->cur_anim_frame, 0,
                              1, NULL);

    fn_8012E3B4_inline(gobj);
    qwe(gobj);

    ftCommon_8007D468(fp);
}

/// #fn_8012E44C

void ftYs_SpecialHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->input.held_inputs & 0x200) {
        fp->mv.ys.specialhi.x4 += 1;
    }
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ft_8008A2BC((Fighter_GObj*) gobj);
    }
}

void ftYs_SpecialAirHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->input.held_inputs & 0x200) {
        fp->mv.ys.specialhi.x4 += 1;
    }
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ftCo_Fall_Enter((Fighter_GObj*) gobj);
    }
}

void ftYs_SpecialHi_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialAirHi_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC((Fighter_GObj*) gobj);
}

void ftYs_SpecialHi_Coll(Fighter_GObj* gobj)
{
    ft_8008403C((Fighter_GObj*) gobj, (void (*)(Fighter_GObj*)) fn_8012E3B4);
}

void ftYs_SpecialAirHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ys.specialhi.x0 != 0) {
        // ft_80083A48(NULL, fn_8012E44C);
        ft_80083A48(gobj, fn_8012E44C);
        // return;
    } else {
        ft_80082C74(gobj, fn_8012E44C);
    }
}

/// #fn_8012E644

inline void ftYoshi_SpecialLw_SetVars(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    fp->cmd_vars[0] = fp->cmd_vars[1] = 0;
    fp->throw_flags_b0 = false;
    fp->self_vel.x = fp->self_vel.y = 0;
    fp->x6A4_transNOffset.y = 0;
    fp->x2223_b4 = true;
}

void ftYs_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 4);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialLw, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftYoshi_SpecialLw_SetVars(gobj);
}

/// #ftYs_SpecialAirLw_Enter

void ftYs_SpecialLw_Anim(Fighter_GObj* gobj)
{
    u8 _[8];

    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ftYs_SpecialS_8012EA04(gobj);
    }
}

void ftYs_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        fp->cmd_vars[1] = 1;
    }
}

void ftYs_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085134(gobj);
    if (fp->self_vel.y < 0) {
        fp->self_vel.y = 0;
    }
}

void ftYs_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    u8 _[8];

    ft_80085134((Fighter_GObj*) gobj);
    if ((fp->self_vel.y < attributes->x114) || ((u32) fp->cmd_vars[1] != 0U)) {
        fp->self_vel.y = attributes->x114;
    }
}
void ftYs_SpecialLw_Coll(HSD_GObj* gobj)
{
    ftYs_SpecialAirLw_Coll(gobj);
}

void ftYs_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int facing_dir;
    if (fp->facing_dir < 0) {
        facing_dir = -1;
    } else {
        facing_dir = +1;
    }
    if (ft_CheckGroundAndLedge(gobj, facing_dir)) {
        if (fp->cmd_vars[0] != 0 && fp->self_vel.y <= 0) {
            ftYs_SpecialS_8012EAD8(gobj);
        } else {
            ftCommon_8007D5D4(fp);
        }
    } else if (fp->cmd_vars[0] != 0 && ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

extern f32 ftYs_Init_804D9A5C;
extern f32 ftYs_Init_804D9A60;
extern f32 ftYs_Init_804D9A64;
void ftYs_SpecialS_8012EA04(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x170, 0x0C4C5088U, ftYs_Init_804D9A64,
                              ftYs_Init_804D9A5C, ftYs_Init_804D9A60, NULL);
}

void ftYs_SpecialLwLanding_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ft_8008A2BC((Fighter_GObj*) gobj);
    }
}

void ftYs_SpecialLwLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialLwLanding_Coll(Fighter_GObj* gobj)
{
    u8 _[8];

    if (ft_80082708((Fighter_GObj*) gobj) == GA_Ground) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftYs_SpecialS_8012EAD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = 0;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialLwLanding, Ft_MF_None, 0, 1,
                              0, NULL);
    fp->accessory4_cb = fn_8012E644;
}

/// #ftYs_SpecialS_8012EB48

/// #fn_8012EC7C

/// #fn_8012EDE8

void fn_8012EFC0(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

/// #fn_8012EFF4

/// #ftYs_SpecialS_8012F0DC

/// #ftYs_SpecialS_8012F35C

/// #ftYs_SpecialS_Enter

/// #ftYs_SpecialAirS_Enter

/// #ftYs_SpecialAirSStart_0_Anim

/// #ftYs_SpecialAirSLoop_0_Anim

/// #ftYs_SpecialAirSLoop_1_Anim

/// #ftYs_SpecialAirSEnd_Anim

/// #ftYs_SpecialAirSStart_1_Anim

/// #ftYs_SpecialAirSLoop_2_Anim

/// #ftYs_SpecialAirSLoop_3_Anim

/// #ftYs_SpecialAirSLanding_Anim

void ftYs_SpecialAirSStart_0_IASA(Fighter_GObj* gobj) {}

/// #ftYs_SpecialAirSLoop_0_IASA

void ftYs_SpecialAirSLoop_1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    s32 x48 = attributes->x48;
    s32 x4C = attributes->x4C;
    s32 difference = x48 - x4C;

    if ((fp->mv.ys.specials.x0 < difference) && (fp->input.x668 & HSD_PAD_B)) {
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x440012, ftYs_Init_804D9A70);
    }
}

void ftYs_SpecialAirSEnd_IASA(Fighter_GObj* gobj) {}

void ftYs_SpecialAirSStart_1_IASA(Fighter_GObj* gobj)
{
    M2C_FIELD(gobj->user_data, s32*, 0x2370) = 0;
}

void ftYs_SpecialAirSLoop_2_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    if ((fp->mv.ys.specials.x0 < attributes->x48 - attributes->x4C) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, ftYs_Init_804D9A70);
    }
}

void ftYs_SpecialAirSLoop_3_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.x30 = 0;

    if ((fp->mv.ys.specials.x0 < (attributes->x48 - attributes->x4C)) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, ftYs_Init_804D9A70);
    }
}

void ftYs_SpecialAirSLanding_IASA(Fighter_GObj* gobj)
{
    M2C_FIELD(gobj->user_data, s32*, 0x2370) = 0;
}

void ftYs_SpecialAirSStart_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 float_update = ftYs_Init_804D9A70;

    fp->xE4_ground_accel_1 = float_update;
    fp->gr_vel = float_update;
    fp->self_vel.y = float_update;
    fp->self_vel.x = float_update;
    fp->x74_anim_vel.y = float_update;
    fp->x74_anim_vel.x = float_update;
}

/// #ftYs_SpecialAirSLoop_0_Phys

/// #ftYs_SpecialAirSLoop_1_Phys

void ftYs_SpecialAirSEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007C930((Fighter*) fp, fp->co_attrs.gr_friction);
    ftCommon_8007CB74((Fighter_GObj*) gobj);
}

void ftYs_SpecialAirSStart_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_8007D494(fp, attributes->x6C, attributes->x70);
}

/// #ftYs_SpecialAirSLoop_2_Phys

/// #ftYs_SpecialAirSLoop_3_Phys

void ftYs_SpecialAirSLanding_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_8007D494(fp, attributes->x6C, attributes->x70);
}

/// #ftYs_SpecialAirSStart_0_Coll

/// #ftYs_SpecialAirSLoop_0_Coll

/// #ftYs_SpecialAirSLoop_1_Coll

void ftYs_SpecialAirSEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x4C4092, fp->cur_anim_frame);
    }
}

/// #ftYs_SpecialAirSStart_1_Coll

/// #ftYs_SpecialAirSLoop_2_Coll

/// #ftYs_SpecialAirSLoop_3_Coll

/// #ftYs_SpecialAirSLanding_Coll

/// #fn_8013295C
