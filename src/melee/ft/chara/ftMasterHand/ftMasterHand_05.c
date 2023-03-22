#include "ftMasterHand_05.h"

#include "ftMasterHand_34.h"

#include "ft/ft_877.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "it/code_8027CF30.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbunknown_001.h"

u32 ftMasterHand_80151428(Vec3* vec)
{
    HSD_GObj* fetched_gobj = func_8015C3E8(0x1B);

    if (fetched_gobj) {
        func_8000B1CC(
            ((Fighter*) fetched_gobj->user_data)->ft_bones[5].x0_jobj, 0, vec);
        return 1;
    }
    return 0;
}

// 80151484 14E064
// https://decomp.me/scratch/0vIXi
inline void func_80151484_inline1(HSD_GObj* gobj)
{
    Fighter* r29_fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* temp_r30 = r29_fp->ft_data->ext_attr;
    r29_fp->x80_self_vel.z = 0.0f;
    r29_fp->x80_self_vel.y = 0.0f;
    r29_fp->x80_self_vel.x = 0.0f;
    func_802F046C(r29_fp->mv.mh.unk0.x34);
    func_802F046C(r29_fp->mv.mh.unk0.x38);
    func_802F046C(r29_fp->mv.mh.unk0.x3C);
    func_802F046C(r29_fp->mv.mh.unk0.x40);
    r29_fp->mv.mh.unk0.x34 = 0;
    r29_fp->mv.mh.unk0.x38 = 0;
    r29_fp->mv.mh.unk0.x3C = 0;
    r29_fp->mv.mh.unk0.x40 = 0;
    func_800236B8(r29_fp->mv.mh.unk0.x28);
    func_800236B8(r29_fp->mv.mh.unk0.x2C);
    func_800236B8(r29_fp->mv.mh.unk0.x30);
    if (r29_fp->mv.mh.unk0.x20) {
        ftMasterHand_80155D1C(r29_fp->x1A58_interactedFighter);
    }
    r29_fp->x80_self_vel.y = temp_r30->x14C;
    r29_fp->x80_self_vel.z = temp_r30->x154;
    r29_fp->mv.mh.unk0.x8 = temp_r30->x15C;
}

void ftMasterHand_80151484(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* r3_fp = GET_FIGHTER(gobj);
    r3_fp->x2200_ftcmd_var0 = 0;

    func_80151484_inline1(gobj);

    Fighter_ChangeMotionState(gobj, 0x158, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);

    // r3_fp now stored in r28
    ft_800881D8(r3_fp, 0x4E217, 0x7F, 0x40);
    ft_80088148(r3_fp, 0x4E218, 0x7F, 0x40);
    r3_fp->mv.mh.unk0.x74 = 0;
    r3_fp->mv.mh.unk0.x78 = 0;
}

// 801515B8 14E198
// https://decomp.me/scratch/I5KfO
void ftMasterHand_801515B8(HSD_GObj* gobj)
{
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;
    Fighter* r31_fp;
    ftMasterHand_SpecialAttrs* r4_attributes;

    r31_fp = gobj->user_data;
    if (r31_fp->x2200_ftcmd_var0) {
        r4_attributes = r31_fp->ft_data->ext_attr;
        temp_r3 = r31_fp->mv.mh.unk0.x74 + 1;
        r31_fp->mv.mh.unk0.x74 = temp_r3;
        if (temp_r3 <= r4_attributes->x144) {
            func_8002438C(0x81652);
        } else {
            temp_r3_2 = r31_fp->mv.mh.unk0.x78 + 1;
            r31_fp->mv.mh.unk0.x78 = temp_r3_2;
            if (temp_r3_2 <= r4_attributes->x148) {
                func_8002438C(0x81653);
            }
        }
        r31_fp->x2200_ftcmd_var0 = 0U;
    }

    // mv.mh.unk0.x8 does that make sense if its u32?
    if (r31_fp->mv.mh.unk0.x8 > 0 && !ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x159, 0, 0, 0.0f, 1.0f, 0.0f);
        ftAnim_8006EBA4(gobj);
    }
    temp_r0 = r31_fp->mv.mh.unk0.x8 - 1;

    r31_fp->mv.mh.unk0.x8 = temp_r0;
    if (temp_r0) {
        return;
    }
    ft_800D4F24(gobj, 0);
}

// 801516B4 14E294
// https://decomp.me/scratch/AmIVW
void ftMasterHand_801516B4(HSD_GObj* gobj)
{
    f32 temp_f1;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;
    ftMasterHand_SpecialAttrs* r4_attributes;
    Fighter* r31_fp = GET_FIGHTER(gobj);

    if ((u32) r31_fp->x2200_ftcmd_var0 != 0U) {
        r4_attributes = r31_fp->ft_data->ext_attr;
        temp_r3 = r31_fp->mv.mh.unk0.x74 + 1;
        r31_fp->mv.mh.unk0.x74 = temp_r3;
        if (temp_r3 <= r4_attributes->x144) {
            func_8002438C(0x81652);
        } else {
            temp_r3_2 = r31_fp->mv.mh.unk0.x78 + 1;
            r31_fp->mv.mh.unk0.x78 = temp_r3_2;
            if (temp_r3_2 <= r4_attributes->x148) {
                func_8002438C(0x81653);
            }
        }
        r31_fp->x2200_ftcmd_var0 = 0U;
    }
    if (r31_fp->mv.mh.unk0.x8 > 0 && !ftAnim_IsFramesRemaining(gobj)) {
        temp_f1 = 0.0f;
        Fighter_ChangeMotionState(gobj, 0x159, 0, 0, temp_f1, 1.0f, temp_f1);
        ftAnim_8006EBA4(gobj);
    }
    temp_r0 = r31_fp->mv.mh.unk0.x8 - 1;
    // temp_cr0_eq = ;
    r31_fp->mv.mh.unk0.x8 = temp_r0;
    if (temp_r0 == 0) {
        ft_800D4F24(gobj, 0);
    }
}
