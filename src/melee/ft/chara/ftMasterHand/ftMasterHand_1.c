#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterhand_OnDeath(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterhand_OnLoad(HSD_GObj* fighter_gobj)
{
    ftData* ft_data;
    MasterHandAttributes* ext_attr;
    void** items;
    Fighter* fp;

    fp = fighter_gobj->user_data;
    ft_data = fp->x10C_ftData;
    ext_attr = ft_data->ext_attr;
    items = ft_data->x48_items;

    PUSH_ATTRS(fp, MasterHandAttributes);

    ftbosslib_8015BDB4(fighter_gobj);
    func_8026B3F8(items[0], 0x7D);
    func_8026B3F8(items[1], 0x7E);
    fp->x2229_b5_no_normal_motion = TRUE;
    fp->x2229_b6 = TRUE;
    fp->x2229_b7 = TRUE;
    fp->x222A_flag.bits.b0 = TRUE;
    fp->x222A_flag.bits.b1 = TRUE;
    fp->x2229_b3 = TRUE;
    fp->xB0_pos.x = ext_attr->x30_pos2.x;
    fp->xB0_pos.y = ext_attr->x30_pos2.y;
    fp->xB0_pos.z = 0.0F;
    fp->x2374 = 0;
    fp->x2378 = 0;
    fp->x237C = 0;
    fp->x2380 = 0;
    fp->x2368 = -1;
    fp->x236C = -1;
    fp->x2370 = -1;
    fp->x235C = 0.0f;
    fp->x2360 = FALSE;
    fp->sa.masterhand.x222C = func_8015C244(fighter_gobj, &fp->xB0_pos);
    fp->sa.masterhand.x2238 = 1.0F;
    fp->sa.masterhand.x224C = 0;
    fp->sa.masterhand.x2250 = 0x15B;
    fp->sa.masterhand.x2254 = 0;
    fp->x1A98 = 1;
    ftbosslib_8015BD24(fp->x1A98, &fp->sa.masterhand.x223C, fp->sa.masterhand.x2238, ext_attr->x18, ext_attr->x20, ext_attr->x1C);
}
