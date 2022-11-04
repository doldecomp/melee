#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/ft/ftanim.h>

#pragma push

// todo: proper inlines should fix this due to max inline depth.
#pragma dont_inline on

static void ftMasterHand_80150C8C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_341 || fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_389) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_389, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
    } else {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_389, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }

    fp->sa.masterhand.x2258 = AS_MASTERHAND_UNK_389;
}

static void ftMasterHand_80150D28(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_342 || fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_390) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_390, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
    } else {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_390, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }

    fp->sa.masterhand.x2258 = AS_MASTERHAND_UNK_390;
}

#pragma pop

void ftMasterHand_80150DC4(HSD_GObj* fighter_gobj, GObjCallback callback, Vec3* pos)
{
    u32 args_unused[4];

    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_342) {
        if ((fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_342) || (fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_390)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_390, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
        } else {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_390, 0, 0, 0.0F, 1.0F, 0.0F);
            func_8006EBA4(fighter_gobj);
        }
        fp->sa.masterhand.x2258 = AS_MASTERHAND_UNK_390;
    } else {
        if ((fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_341) || (fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_389)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_389, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
        } else {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_389, 0, 0, 0.0F, 1.0F, 0.0F);
            func_8006EBA4(fighter_gobj);
        }
        fp->sa.masterhand.x2258 = AS_MASTERHAND_UNK_389;
    }

    fp->x2344_callback = callback;
    fp->x234C_pos = *pos;
}

void ftMasterHand_80150F00(HSD_GObj* fighter_gobj)
{
    u32 arg_unused;

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;

        fp->sa.masterhand.x2258 = AS_MASTERHAND_UNK_389;
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MASTERHAND_UNK_389, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }
}

void lbl_80150F68(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    func_80085134(fighter_gobj);
    ftbosslib_8015BE40(fighter_gobj, &fp->x234C_pos, &fp->x2358_stateVar7, ext_attr->x2C, ext_attr->x28);
}

void ftMasterHand_80150FC8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2358_stateVar7 != 0.0F)
        return;

    fp->x80_self_vel.z = 0.0F;
    fp->x80_self_vel.y = 0.0F;
    fp->x80_self_vel.x = 0.0F;

    if (fp->x2344_stateVar2)
        ((GObjCallback) fp->x2344_stateVar2)(fighter_gobj);
}

static void set_callback_and_pos(HSD_GObj* fighter_gobj, Vec3* pos)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.masterhand.x2258 == AS_MASTERHAND_UNK_342)
        ftMasterHand_80150D28(fighter_gobj);
    else
        ftMasterHand_80150C8C(fighter_gobj);

    fp->x2344_callback = ftMasterHand_8014FFDC;
    fp->x234C_pos = *pos;
}

static void ftMasterHand_80150F00_impl(HSD_GObj* fighter_gobj, Vec3* pos)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
    fp->x2360 = FALSE;

    pos->x = ext_attr->x30_pos2.x;
    pos->y = ext_attr->x30_pos2.y;
    pos->z = 0.0F;

    fp->sa.masterhand.x2258 = AS_MASTERHAND_UNK_390;
    set_callback_and_pos(fighter_gobj, pos);
}

void ftMasterHand_80151018(HSD_GObj* fighter_gobj)
{
    Vec3 arg_pos;
    u32 arg_unused[4];
    ftMasterHand_80150F00_impl(fighter_gobj, &arg_pos);
}
