#include "ftMasterHand.h"

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
    Fighter* ft;

    
    ft = gobj->user_data;
    ftdata = ft->x10C_ftData;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(ft, MasterHandAttributes);
    
    func_8015BDB4(gobj);
    func_8026B3F8(items[0], 0x7D);
    func_8026B3F8(items[1], 0x7E);
    ft->x2229_b5_no_normal_motion = 1;
    ft->x2229_b6 = 1;
    ft->x2229_b7 = 1;
    ft->x222A_flag.bits.b0 = 1;
    ft->x222A_flag.bits.b1 = 1;
    ft->x2229_b3 = 1;
    ft->xB0_pos.x = ftData_attr->x30_pos2.x;
    ft->xB0_pos.y = ftData_attr->x30_pos2.y;
    ft->xB0_pos.z = 0.0f;
    ft->x2374 = 0;
    ft->x2378 = 0;
    ft->x237C = 0;
    ft->x2380 = 0;
    ft->x2368 = -1;
    ft->x236C = -1;
    ft->x2370 = -1;
    ft->x235C = 0.0f;
    ft->x2360 = 0;
    ft->sa.masterhand.x222C = func_8015C244(gobj, &ft->xB0_pos);
    ft->sa.masterhand.x2238 = 1.0f;
    ft->sa.masterhand.x224C = 0;
    ft->sa.masterhand.x2250 = 0x15B;
    ft->sa.masterhand.x2254 = 0;
    ft->x1A98 = 1;
    func_8015BD24(ft->x1A98, &ft->sa.masterhand.x223C, ft->sa.masterhand.x2238, ftData_attr->x18, ftData_attr->x20, ftData_attr->x1C);
}

