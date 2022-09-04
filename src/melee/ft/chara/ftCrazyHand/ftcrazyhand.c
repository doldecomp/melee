#include <melee/ft/chara/ftCrazyHand/ftcrazyhand.h>

void ftCrazyhand_OnDeath(HSD_GObj* fighter_gobj) {

}

void ftCrazyhand_OnLoad(HSD_GObj* fighter_gobj) {
    ftData* ftdata;
    ftCrazyHandAttributes* ftData_attr;
    void** items;
    Fighter* fp;

    
    fp = fighter_gobj->user_data;
    ftdata = fp->x10C_ftData;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(fp, ftCrazyHandAttributes);
    
    func_8015BDB4(fighter_gobj);
    func_8026B3F8(items[0], 0x7F);
    func_8026B3F8(items[1], 0x80);
    func_8026B3F8(items[2], 0x81);
    fp->x2229_b5_no_normal_motion = 1;
    fp->x2229_b6 = 1;
    fp->x2229_b7 = 1;
    fp->x222A_flag.bits.b0 = 1;
    fp->x222A_flag.bits.b1 = 1;
    fp->x2229_b3 = 1;
    fp->xB0_pos.x = ftData_attr->x18;
    fp->xB0_pos.y = ftData_attr->x1C;
    fp->xB0_pos.z = 0.0f;
    fp->x2368 = 0;
    fp->x236C = 0; 
    fp->x2370 = 0;
    fp->x2374 = 0;
    fp->x2378 = -1;
    fp->x237C = -1;
    fp->x2380 = -1;
    fp->x235C = 0.0f;
    fp->x2360 = 0;
    fp->sa.masterhand.x222C = func_8015C244(fighter_gobj, &fp->xB0_pos);
    fp->sa.masterhand.x2238 = 1.0f;
    fp->sa.masterhand.x224C = 0;
    fp->sa.masterhand.x2250 = 0x159; 
    fp->sa.masterhand.x2254 = 0;
    fp->x1A98 = 1;
    func_8015BD24(fp->x1A98, &fp->sa.masterhand.x223C, fp->sa.crazyhand.x2238, ftData_attr->x0, ftData_attr->x8, ftData_attr->x4);
}


void ftCrazyHand_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftCrazyHandAttributes);
}
