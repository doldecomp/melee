#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/lb/lbunknown_001.h>

// probably isCrazyHandLoaded func
u32 ftMasterHand_80151428(Vec* vec)
{
    HSD_GObj* fetched_gobj;

    // probably attempt to find crazy hand func.
    fetched_gobj = ftbosslib_8015C3E8(0x1B);

    if (fetched_gobj != NULL) {
        func_8000B1CC(((Fighter*) fetched_gobj->user_data)->x5E8_fighterBones[5].x0_jobj, 0, vec);
        return 1;
    }
    return 0;
}

#include <melee/lb/lbaudio_ax.h>

inline void ftMasterHand_80151484_inline1(HSD_GObj* fighter_gobj)
{
    Fighter* r29_fp = fighter_gobj->user_data;
    MasterHandAttributes* temp_r30 = r29_fp->x10C_ftData->ext_attr;

    r29_fp->x80_self_vel.z = 0.0F;
    r29_fp->x80_self_vel.y = 0.0F;
    r29_fp->x80_self_vel.x = 0.0F;

    func_802F046C(r29_fp->x2374);
    func_802F046C(r29_fp->x2378);
    func_802F046C(r29_fp->x237C);
    func_802F046C(r29_fp->x2380);

    r29_fp->x2374 = 0;
    r29_fp->x2378 = 0;
    r29_fp->x237C = 0;
    r29_fp->x2380 = 0;

    func_800236B8(r29_fp->x2368);
    func_800236B8(r29_fp->x236C);
    func_800236B8(r29_fp->x2370);

    if (r29_fp->x2360)
        ftMasterHand_80155D1C(r29_fp->x1A58_interactedFighter);

    r29_fp->x80_self_vel.y = temp_r30->x14C;
    r29_fp->x80_self_vel.z = temp_r30->x154;
    r29_fp->x2348_stateVar3 = (s32) temp_r30->x15C;
}

#include <melee/ft/ftanim.h>

void ftMasterHand_80151484(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = fighter_gobj->user_data;
    fp->x2200_ftcmd_var0 = 0;

    ftMasterHand_80151484_inline1(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x158, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    func_800881D8(fp, 0x4E217, 0x7F, 0x40);
    func_80088148(fp, 0x4E218, 0x7F, 0x40);

    fp->x23B4 = 0;
    fp->x23B8 = 0;
}

#include <melee/ft/ftanim.h>

void ftMasterHand_801515B8(HSD_GObj* fighter_gobj)
{
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr;

    if (fp->x2200_ftcmd_var0) {
        ext_attr = fp->x10C_ftData->ext_attr;
        temp_r3 = fp->x23B4 + 1;
        fp->x23B4 = temp_r3;
        if (temp_r3 <= ext_attr->x144) {
            func_8002438C(0x81652);
        } else {
            temp_r3_2 = fp->x23B8 + 1;
            fp->x23B8 = temp_r3_2;
            if (temp_r3_2 <= ext_attr->x148) {
                func_8002438C(0x81653);
            }
        }
        fp->x2200_ftcmd_var0 = 0U;
    }

    if ((s32) fp->x2348_stateVar3 > 0 && !ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x159, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }

    temp_r0 = fp->x2348_stateVar3 - 1;

    fp->x2348_stateVar3 = temp_r0;

    if (temp_r0 == 0)
        func_800D4F24(fighter_gobj, 0);
}

void ftMasterHand_801516B4(HSD_GObj* fighter_gobj)
{
    f32 temp_f1;
    s32 temp_cr0_eq;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;
    Fighter* fp;
    MasterHandAttributes* ext_attr;

    fp = fighter_gobj->user_data;
    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        ext_attr = fp->x10C_ftData->ext_attr;
        temp_r3 = fp->x23B4 + 1;
        fp->x23B4 = temp_r3;
        if (temp_r3 <= (s32) ext_attr->x144) {
            func_8002438C(0x81652);
        } else {
            temp_r3_2 = fp->x23B8 + 1;
            fp->x23B8 = temp_r3_2;
            if (temp_r3_2 <= (s32) ext_attr->x148) {
                func_8002438C(0x81653);
            }
        }
        fp->x2200_ftcmd_var0 = 0U;
    }
    if (((s32) fp->x2348_stateVar3 > 0) && !ftAnim_IsFramesRemaining(fighter_gobj)) {
        temp_f1 = 0.0F;
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x159, 0, 0, temp_f1, 1.0F, temp_f1);
        func_8006EBA4(fighter_gobj);
    }
    temp_r0 = fp->x2348_stateVar3 - 1;

    fp->x2348_stateVar3 = temp_r0;

    if (temp_r0 == 0)
        func_800D4F24(fighter_gobj, 0);
}
