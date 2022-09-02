#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 8014FC68 0014C848
void ftMasterhand_OnDeath(HSD_GObj* gobj) {
    return;
}

// 8014FC6C 0014C84C
// https://decomp.me/scratch/Tbp9G
void ftMasterhand_OnLoad(HSD_GObj* gobj) {

    ftData* ftdata;
    MasterHandAttributes* ftData_attr;
    void** items;
    Fighter* fp;

    
    fp = gobj->user_data;
    ftdata = fp->x10C_ftData;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(fp, MasterHandAttributes);
    
    func_8015BDB4(gobj);
    func_8026B3F8(items[0], 0x7D);
    func_8026B3F8(items[1], 0x7E);
    fp->x2229_b5_no_normal_motion = 1;
    fp->x2229_b6 = 1;
    fp->x2229_b7 = 1;
    fp->x222A_flag.bits.b0 = 1;
    fp->x222A_flag.bits.b1 = 1;
    fp->x2229_b3 = 1;
    fp->xB0_pos.x = ftData_attr->x30_pos2.x;
    fp->xB0_pos.y = ftData_attr->x30_pos2.y;
    fp->xB0_pos.z = 0.0f;
    fp->x2374 = 0;
    fp->x2378 = 0;
    fp->x237C = 0;
    fp->x2380 = 0;
    fp->x2368 = -1;
    fp->x236C = -1;
    fp->x2370 = -1;
    fp->x235C = 0.0f;
    fp->x2360 = 0;
    fp->sa.masterhand.x222C = func_8015C244(gobj, &fp->xB0_pos);
    fp->sa.masterhand.x2238 = 1.0f;
    fp->sa.masterhand.x224C = 0;
    fp->sa.masterhand.x2250 = 0x15B;
    fp->sa.masterhand.x2254 = 0;
    fp->x1A98 = 1;
    func_8015BD24(fp->x1A98, &fp->sa.masterhand.x223C, fp->sa.masterhand.x2238, ftData_attr->x18, ftData_attr->x20, ftData_attr->x1C);
}

