#include "crowdsfx.h"

#include "ft/ftlib.h"
#include "lb/lbaudio_ax.h"
#include "pl/player.h"
#include "pl/plbonuslib.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>

extern char mpLib_80458868[];

CrowdSFX_UnkStruct un_804A2F08;

static CrowdSFX_UnkStruct* un_804D7050;

void un_80321900(void)
{
    HSD_GObj* gobj = GObj_Create(0x16, 0x17, 0);
    HSD_GObj_SetupProc(gobj, fn_803219AC, 0x13);
    un_804D7050 = &un_804A2F08;
    un_80321950(un_804D7050);
}

void un_80321950(CrowdSFX_UnkStruct* s)
{
    s->x0 = 0;
    s->x4 = 0x10000;
    s->x8 = 0.0f;
    s->xC = 0;
    s->x10 = gCrowdConfig->cheer_limit;
    s->x14 = 0x83D60;
    s->x18 = gCrowdConfig->max_gasp_count;
    s->x1C = 0;
    s->x20 = 0;
    s->x24 = 0;
    s->x2C = -1;
    s->x28 = -1;
}

void fn_803219AC(HSD_GObj* gobj)
{
    CrowdSFX_UnkStruct* data = un_804D7050;
    if (data->x4 < 0x10000) {
        data->x4 = data->x4 + 1;
    }
    un_80321A00(gobj);
    un_80321AF4(gobj);
}

void un_80321A00(HSD_GObj* gobj)
{
    s32 zero;
    CrowdSFX_UnkStruct* data = un_804D7050;
    CrowdConfig* vdata = gCrowdConfig;

    if (data->x18 >= vdata->max_gasp_count) {
        if (data->x10 < vdata->cheer_limit) {
            data->x10 = data->x10 + 1;
        }
        return;
    }

    if (lbAudioAx_80023710(data->x2C) != 0) {
        return;
    }
    data->x18 = data->x18 + 1;

    if (data->x18 < gCrowdConfig->max_gasp_count) {
        if (data->x1C != 0) {
            zero = 0;
            data->x1C = zero;
            data->x10 = zero;
            data->x18 = gCrowdConfig->max_gasp_count;
            un_80321C28();
            if (data->x20 != 0) {
                un_80321CA4(0x144);
                data->x20 = zero;
            }
        } else {
            un_80321BF8(data->x14);
        }
    } else {
        data->x10 = 0;
        un_80321C28();
        un_80321CA4(0x140);
    }
}

void un_80321AF4(HSD_GObj* gobj)
{
    char* mpLib = mpLib_80458868;
    HSD_GObj* cur;
    CrowdSFX_UnkStruct* data = un_804D7050;
    s32 old_x24 = data->x24;
    s32 flag = 0;
    Vec3 pos;
    char pad[12];

    data->x24 = 0;
    cur = HSD_GObj_Entities->fighters;

    while (cur != NULL) {
        if (ftLib_8008732C(cur) == 0) {
            if (ftLib_8008731C(cur) == 0) {
                ftLib_80086644(cur, &pos);

                if (pos.y <
                    gCrowdConfig->blastzone_y_offset + *(f32*) (mpLib + 0x14))
                {
                    data->x24 = data->x24 + 1;
                } else {
                    if (data->xC == ftLib_80087460(cur)) {
                        flag = 1;
                    }
                }
            }
        }
        cur = cur->next;
    }

    if (old_x24 < gCrowdConfig->fighters_near_blastzone) {
        if (data->x24 >= gCrowdConfig->fighters_near_blastzone) {
            if (flag != 0) {
                un_8032201C(data->xC, 3);
            } else {
                un_80322178(3);
            }
        }
    }
}

void un_80321BF8(int arg0)
{
    CrowdSFX_UnkStruct* data = un_804D7050;
    data->x2C = lbAudioAx_800240B4(arg0);
}

void un_80321C28(void)
{
    CrowdSFX_UnkStruct* data = un_804D7050;
    if (lbAudioAx_80023710(data->x2C) != 0) {
        lbAudioAx_800236B8(data->x2C);
    }
    data->x2C = -1;
}

static void un_80321C70_inline(void)
{
    CrowdSFX_UnkStruct* data;

    data = un_804D7050;

    if (data->x18 >= gCrowdConfig->max_gasp_count ||
        data->x18 < gCrowdConfig->x24)
    {
        return;
    }
    data->x1C = 1;
}

#pragma push
#pragma dont_inline on
void un_80321C70(void)
{
    CrowdSFX_UnkStruct* data;

    data = un_804D7050;

    if (data->x18 >= gCrowdConfig->max_gasp_count ||
        data->x18 < gCrowdConfig->x24)
    {
        return;
    }
    data->x1C = 1;
}

void un_80321CA4(s32 arg)
{
    CrowdSFX_UnkStruct* data = un_804D7050;
    un_80321CE8();
    data->x28 = lbAudioAx_8002411C(arg);
}
#pragma pop

void un_80321CE8(void)
{
    CrowdSFX_UnkStruct* data = un_804D7050;
    if (lbAudioAx_80023710(data->x28) != 0) {
        lbAudioAx_800236B8(data->x28);
    }
    data->x28 = -1;
}

static void un_80321CE8_caller(u32 arg0)
{
    CrowdSFX_UnkStruct* data = un_804D7050;
    if (lbAudioAx_80023710(data->x28) != 0) {
        lbAudioAx_800236B8(data->x28);
    }
    data->x28 = -1;
    data->x28 = lbAudioAx_8002411C(arg0);
}

void un_80321D30(u32 arg0, f32 arg1)
{
    s32 cat;
    CrowdSFX_UnkStruct* data;

    data = un_804D7050;
    cat = un_80322298(arg1);
    if (cat >= 2) {
        if (un_80321EBC(arg0, arg1) != 0) {
            un_80321CE8();
            return;
        }
    }

    switch (cat) {
    case 3: {
        un_80321CE8_caller(0x140);
        break;
    }
    case 2: {
        un_80321CE8_caller(0x141);
        break;
    }
    case 1: {
        un_80321CE8_caller(0x142);
        break;
    }
    }

    if (arg0 != 0) {
        if (data->xC == arg0) {
            un_80321C70_inline();
        }
    }
}

bool un_80321EBC(u32 arg0, f32 arg1)
{
    s32 port;
    CrowdSFX_UnkStruct* data;
    HSD_GObj* gobj;
    u32 arg0_copy = arg0;

    data = un_804D7050;
    gobj = ftLib_8008741C(arg0_copy);
    if (gobj == NULL) {
        goto skip;
    }

    port = ftLib_800874BC(gobj);
    if (Player_8003248C(ftLib_80086BE0(gobj), port) == 1) {
        goto skip;
    }

    if (ftLib_80087120(gobj) < gCrowdConfig->x1C) {
        goto skip;
    }
    if (data->x10 < gCrowdConfig->cheer_limit) {
        goto skip;
    }
    if (data->xC == arg0) {
    skip:
        return 0;
    }

    data->x14 = ftLib_8008746C(gobj);
    if (data->x14 == 0x83D60) {
        return 0;
    }

    {
        CrowdSFX_UnkStruct* data2 = un_804D7050;
        s32 sfx;
        if (lbAudioAx_80023710(data2->x2C) != 0) {
            lbAudioAx_800236B8(data2->x2C);
        }
        data2->x2C = -1;
        if (un_80322298(arg1) == 3) {
            sfx = 0x140;
        } else {
            sfx = 0x141;
        }
        data2 = un_804D7050;
        data2->x2C = lbAudioAx_800240B4(sfx);
    }

    data->xC = arg0;
    data->x18 = 0;

    port = ftLib_800874BC(gobj);
    pl_8003FDA0(ftLib_80086BE0(gobj), port);

    return 1;
}

bool un_8032201C(u32 arg0, s32 cat)
{
    CrowdSFX_UnkStruct* data = un_804D7050;
    HSD_GObj* gobj;
    char pad[16];

    switch (cat) {
    case 3:
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13d);
        break;
    case 2:
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13e);
        break;
    case 1:
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13f);
        break;
    case 0:
        return false;
    }

    if (arg0 != 0) {
        if (data->xC == arg0) {
            un_80321C70_inline();
        }

        gobj = ftLib_8008741C(arg0);
        pl_8003FDC8(ftLib_80086BE0(gobj), ftLib_800874BC(gobj));
    }
    return true;
}

void un_80322178(int arg)
{
    CrowdSFX_UnkStruct* data;
    char pad[8];

    switch (arg) {
    case 0:
        break;
    case 3:
        data = un_804D7050;
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13d);
        break;
    case 2:
        data = un_804D7050;
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13e);
        break;
    case 1:
        data = un_804D7050;
        if (lbAudioAx_80023710(data->x28) != 0) {
            lbAudioAx_800236B8(data->x28);
        }
        data->x28 = -1;
        data->x28 = lbAudioAx_8002411C(0x13f);
        break;
    }
}

bool un_80322258(float arg)
{
    f32 val2c = gCrowdConfig->horiz_margin;

    if (arg < val2c + M2C_FIELD(mpLib_80458868, f32*, 0x18)) {
        goto ret_true;
    }
    if (!(arg > M2C_FIELD(mpLib_80458868, f32*, 0x1C) - val2c)) {
        goto ret_false;
    }
ret_true:
    return 1;
ret_false:
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
    CrowdSFX_UnkStruct* data = un_804D7050;
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
    CrowdSFX_UnkStruct* data = un_804D7050;
    HSD_GObj* gobj;
    f32 kb_mag;
    PAD_STACK(8);

    gobj = ftLib_8008741C(arg0);
    kb_mag = ftLib_80087454(ftLib_8008741C(arg1));

    if (kb_mag >= gCrowdConfig->kb_threshold_high) {
        cat = 3;
    } else if (kb_mag >= gCrowdConfig->kb_threshold_mid) {
        cat = 2;
    } else if (kb_mag >= gCrowdConfig->kb_threshold_low) {
        cat = 1;
    } else {
        cat = 0;
    }

    if (cat == 0) {
        return;
    }

    if (gobj != NULL) {
        if (ftLib_80087454(gobj) >= 3.0f) {
            un_80321D30(arg0, kb_mag);
            goto end;
        }
    }

    if (data->x0 == arg0) {
        if ((f32) data->x4 < gCrowdConfig->x18) {
            un_80321D30(arg0, kb_mag > data->x8 ? kb_mag : data->x8);
            goto end;
        }
    }

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
end:
    data->x4 = 0;
    data->x0 = arg0;
    data->x8 = kb_mag;
}

bool un_803224DC(s32 spawn_id, f32 pos_x, f32 kb_mag)
{
    CrowdConfig* vdata = gCrowdConfig;
    s32 cat;
    s32 out_of_bounds;
    s32 tmp_cat;

    if (kb_mag >= vdata->kb_threshold_high) {
        tmp_cat = 3;
    } else if (kb_mag >= vdata->kb_threshold_mid) {
        tmp_cat = 2;
    } else if (kb_mag >= vdata->kb_threshold_low) {
        tmp_cat = 1;
    } else {
        tmp_cat = 0;
    }

    {
        f32 val2c = vdata->horiz_margin;
        f32 val18 = M2C_FIELD(mpLib_80458868, f32*, 0x18);
        f32 val1c;

        cat = tmp_cat;

        if (pos_x < val2c + val18) {
            goto oob;
        }
        val1c = M2C_FIELD(mpLib_80458868, f32*, 0x1C);
        if (!(pos_x > val1c - val2c)) {
            goto inb;
        }
    oob:
        out_of_bounds = 1;
        goto check;
    inb:
        out_of_bounds = 0;
    }
check:
    if (out_of_bounds != 0) {
        un_8032201C(spawn_id, cat);
    } else {
        return 0;
    }
}

int un_80322598(int arg0, float arg1)
{
    f32 val14 = M2C_FIELD(mpLib_80458868, f32*, 0x14);
    s32 cat;
    CrowdConfig* vdata;
    if (arg1 >= val14) {
        goto ret_zero;
    }
    vdata = gCrowdConfig;
    if (arg1 < vdata->recovery_y_low + val14) {
    ret_zero:
        return 0;
    }
    if (arg1 > vdata->recovery_y_high + val14) {
        cat = 3;
    } else if (arg1 > vdata->recovery_y_mid + val14) {
        cat = 2;
    } else {
        cat = 1;
    }
    un_8032201C(arg0, cat);
}
