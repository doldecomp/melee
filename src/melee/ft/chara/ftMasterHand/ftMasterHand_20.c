#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80153D28(HSD_GObj* fighter_gobj)
{
    return;
}

static inline HSD_JObj* get_jobj(HSD_GObj* fighter_gobj)
{
    return fighter_gobj->hsd_obj;
}

void ftMasterHand_80153D2C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_JObj* jobj = get_jobj(fighter_gobj);
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x173, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    {
        Vec3 pos;
        ftbosslib_8015C208(fighter_gobj, &pos);
        fp->xB0_pos.x = pos.x;
        fp->xB0_pos.y = ext_attr->x70;
    }

    {
        fp->x80_self_vel.z = 0.0F;
        fp->x80_self_vel.y = 0.0F;
        fp->x80_self_vel.x = 0.0F;

        fp->x2340_f32 = ext_attr->x74;
        fp->x23B0 = ext_attr->x7C;
    }

    {
        Vec3 scale;
        u32 unused;

        HSD_JObjGetScale(jobj, &scale);
        fp->x23A4.x = scale.x;
        fp->x23A4.y = scale.y;
        fp->x23A4.z = scale.z;

        fp->x2398.x = scale.x - ext_attr->x78;
        fp->x2398.y = scale.y - ext_attr->x78;
        fp->x2398.z = scale.z - ext_attr->x78;

        fp->x2398.x /= ext_attr->x7C;
        fp->x2398.y /= ext_attr->x7C;
        fp->x2398.z /= ext_attr->x7C;

        scale.x = ext_attr->x78;
        scale.y = ext_attr->x78;
        scale.z = ext_attr->x78;
        HSD_JObjSetScale(jobj, &scale);
    }

    fp->x2200_ftcmd_var0 = 1;
}

static inline void stop_x_vel(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ((Fighter*) fighter_gobj->user_data)->x80_self_vel.x = 0.0F;
        ftMasterHand_80151018(fighter_gobj);
    }
}

void ftMasterHand_80153F8C(HSD_GObj* fighter_gobj)
{
    HSD_GObj* temp_gobj = fighter_gobj;

    /* todo: very likely an inline */ {
        Fighter* fp = temp_gobj->user_data;
        u32 unused0;

        if (fp->x2200_ftcmd_var0 != 0) {
            /* also an inline? */ {
                Vec3 scale;
                u32 unused1[3];
                HSD_JObj* jobj = get_jobj(temp_gobj);
                if (--fp->x23B0 < 0) {
                    fp->x2200_ftcmd_var0 = 0;
                    scale.x = fp->x23A4.x;
                    scale.y = fp->x23A4.y;
                    scale.z = fp->x23A4.z;
                } else {
                    HSD_JObjGetScale(jobj, &scale);
                    scale.x += fp->x2398.x;
                    scale.y += fp->x2398.y;
                    scale.z += fp->x2398.z;
                }
                HSD_JObjSetScale(jobj, &scale);
            }
        }
    }

    stop_x_vel(temp_gobj);
}

void ftMasterHand_80154114(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80154158(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (--fp->x2340_f32 > 0.0F) {
        u32 unused[2];

        MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
        ftbosslib_8015BF74(fighter_gobj, ext_attr->x58);
    } else {
        fp->x80_self_vel.x = 0.0F;
    }

    ftbosslib_8015C190(fighter_gobj);
}
