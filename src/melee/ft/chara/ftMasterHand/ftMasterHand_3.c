#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#pragma push
#pragma dont_inline on

static void ftMasterHand_80150C8C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->sa.masterhand.x2258 == 0x155) || (fp->sa.masterhand.x2258 == 0x185)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x185, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
    } else {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x185, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }

    fp->sa.masterhand.x2258 = 0x185;
}

static void ftMasterHand_80150D28(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->sa.masterhand.x2258 == 0x156) || (fp->sa.masterhand.x2258 == 0x186)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x186, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
    } else {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x186, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }

    fp->sa.masterhand.x2258 = 0x186;
}

void ftMasterHand_80150DC4(HSD_GObj* fighter_gobj, GObjCallback callback, Vec3* arg2_pos)
{
    f32 temp_f1;
    Fighter* fp = fighter_gobj->user_data;
    s32 unk_filler[4];

    if (fp->sa.masterhand.x2258 == 0x156) {
        if ((fp->sa.masterhand.x2258 == 0x156) || (fp->sa.masterhand.x2258 == 0x186)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x186, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
        } else {
            temp_f1 = 0.0F;
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x186, 0, 0, temp_f1, 1.0F, temp_f1);
            func_8006EBA4(fighter_gobj);
        }
        fp->sa.masterhand.x2258 = 0x186;
    } else {
        if ((fp->sa.masterhand.x2258 == 0x155) || (fp->sa.masterhand.x2258 == 0x185)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x185, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
        } else {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x185, 0, 0, 0.0F, 1.0F, 0.0F);
            func_8006EBA4(fighter_gobj);
        }
        fp->sa.masterhand.x2258 = 0x185;
    }

    fp->x2344_callback = callback;
    fp->x234C_pos = *arg2_pos;
}

void lbl_80150F00(HSD_GObj* fighter_gobj)
{
    u32 unk[1];

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;
        fp->sa.masterhand.x2258 = 0x185;
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x185, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }
}

void lbl_80150F68(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    MasterHandAttributes* ext_attr;
    ftData* ftdata;

    ftdata = fp->x10C_ftData;
    ext_attr = ftdata->ext_attr;

    func_80085134(fighter_gobj);
    ftbosslib_8015BE40(fighter_gobj, &fp->x234C_pos, &fp->x2358_stateVar7, ext_attr->x2C, ext_attr->x28);
}

void ftMasterHand_80150FC8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (0.0F == fp->x2358_stateVar7) {
        fp->x80_self_vel.z = 0.0F;
        fp->x80_self_vel.y = 0.0F;
        fp->x80_self_vel.x = 0.0F;

        if (fp->x2344_stateVar2)
            ((void (*)(HSD_GObj*)) fp->x2344_stateVar2)(fighter_gobj);
    }
}

void ftMasterHand_80151018(HSD_GObj* fighter_gobj)
{
    Vec3 sp1C_pos;
    MasterHandAttributes* attr;
    Fighter* r6_fp;
    Fighter* fp;
    u32 unk[4];

    r6_fp = fighter_gobj->user_data;
    attr = r6_fp->x10C_ftData->ext_attr;
    r6_fp->x2360 = FALSE;
    sp1C_pos.x = attr->x30_pos2.x;
    sp1C_pos.y = attr->x30_pos2.y;
    sp1C_pos.z = 0.0F;
    r6_fp->sa.masterhand.x2258 = 0x186;
    fp = fighter_gobj->user_data;

    if (fp->sa.masterhand.x2258 == 0x156)
        ftMasterHand_80150D28(fighter_gobj);
    else
        ftMasterHand_80150C8C(fighter_gobj);

    fp->x2344_callback = ftMasterHand_8014FFDC;
    fp->x234C_pos = sp1C_pos;
}

#pragma pop
