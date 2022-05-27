#include "ftcrazyhand.h"

void ftCrazyhand_OnDeath(HSD_GObj* fighterObj) {

}

void ftCrazyhand_OnLoad(HSD_GObj* fighterObj) {
    ftData* ftdata;
    ftCrazyHandAttributes* ftData_attr;
    void** items;
    Fighter* ft;

    
    ft = fighterObj->user_data;
    ftdata = ft->x10C_ftData;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(ft, ftCrazyHandAttributes);
    
    func_8015BDB4(fighterObj);
    func_8026B3F8(items[0], 0x7F);
    func_8026B3F8(items[1], 0x80);
    func_8026B3F8(items[2], 0x81);
    ft->x2229_b5_no_normal_motion = 1;
    ft->x2229_b6 = 1;
    ft->x2229_b7 = 1;
    ft->x222A_flag.bits.b0 = 1;
    ft->x222A_flag.bits.b1 = 1;
    ft->x2229_b3 = 1;
    ft->xB0_pos.x = ftData_attr->x18;
    ft->xB0_pos.y = ftData_attr->x1C;
    ft->xB0_pos.z = 0.0f;
    ft->x2368 = 0;
    ft->x236C = 0; 
    ft->x2370 = 0;
    ft->x2374 = 0;
    ft->x2378 = -1;
    ft->x237C = -1;
    ft->x2380 = -1;
    ft->x235C = 0.0f;
    ft->x2360 = 0;
    ft->sa.masterhand.x222C = func_8015C244(fighterObj, &ft->xB0_pos);
    ft->sa.masterhand.x2238 = 1.0f;
    ft->sa.masterhand.x224C = 0;
    ft->sa.masterhand.x2250 = 0x159; 
    ft->sa.masterhand.x2254 = 0;
    ft->x1A98 = 1;
    func_8015BD24(ft->x1A98, &ft->sa.masterhand.x223C, ft->sa.crazyhand.x2238, ftData_attr->x0, ftData_attr->x8, ftData_attr->x4);
}