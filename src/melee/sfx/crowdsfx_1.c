#include <melee/mp/forward.h>

#include <placeholder.h>

#include "crowdsfx.h"
#include <melee/ft/ftlib.h>
#include <melee/mp/mplib.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

bool un_80322258(float arg)
{
    f32 val2c = gCrowdConfig->horiz_margin;

    if (arg < val2c + mpLib_80458868[1].left ||
        arg > mpLib_80458868[1].right - val2c)
    {
        return 1;
    }
    return 0;
}

s32 un_80322298(float arg)
{
    CrowdConfig* vdata = gCrowdConfig;
    if (arg >= vdata->kb_threshold_high) {
        return 3;
    }
    if (arg >= vdata->kb_threshold_mid) {
        return 2;
    }
    if (arg >= vdata->kb_threshold_low) {
        return 1;
    }
    return 0;
}

f32 un_803222EC(f32 arg1, f32 arg2)
{
    CrowdConfig* vdata = gCrowdConfig;
    if (!(arg2 > vdata->angle_min)) {
        return arg1;
    }
    if (!(arg2 < vdata->angle_max)) {
        return arg1;
    }
    return arg1 * vdata->angle_mult;
}

void un_80322314(void)
{
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    CrowdConfig* vdata = gCrowdConfig;
    if (data->x18 >= vdata->max_gasp_count) {
        return;
    }
    data->x1C = 1;
    data->x20 = 1;
}

void un_8032233C(u32 arg0, u32 arg1)
{
    s32 cat;
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    HSD_GObj* gobj;
    f32 kb_mag;
    PAD_STACK(8);

    gobj = ftLib_FindBySpawnNum(arg0);
    kb_mag = ftLib_GetCrowdKnockback(ftLib_FindBySpawnNum(arg1));

    cat = un_80322298(kb_mag);
    if (cat == 0) {
        return;
    }

    if (gobj != NULL && ftLib_GetCrowdKnockback(gobj) >= 3.0f) {
        un_80321D30(arg0, kb_mag);
    } else if (data->x0 == arg0 && (f32) data->x4 < gCrowdConfig->x18) {
        un_80321D30(arg0, kb_mag > data->x8 ? kb_mag : data->x8);
    } else {
        switch (cat) {
        case 3:
            un_80321CA4(0x144);
            break;
        case 2:
            un_80321CA4(0x145);
            break;
        case 1:
            un_80321CA4(0x146);
            break;
        }

        if (cat == 3 || (cat == 2 && data->xC == arg1)) {
            un_80321C70();
        }
    }
    data->x4 = 0;
    data->x0 = arg0;
    data->x8 = kb_mag;
}

bool un_803224DC(s32 spawn_id, f32 pos_x, f32 kb_mag)
{
    s32 cat = un_80322298(kb_mag);
    if (un_80322258(pos_x)) {
        return un_8032201C(spawn_id, cat);
    }
    return false;
}

int un_80322598(int arg0, float arg1)
{
    f32 val14 = mpLib_80458868[1].bottom;
    s32 cat;
    CrowdConfig* vdata;
    if (arg1 >= val14 || arg1 < gCrowdConfig->recovery_y_low + val14) {
        return 0;
    }
    vdata = gCrowdConfig;
    if (arg1 > vdata->recovery_y_high + val14) {
        cat = 3;
    } else if (arg1 > vdata->recovery_y_mid + val14) {
        cat = 2;
    } else {
        cat = 1;
    }
    un_8032201C(arg0, cat);
}
