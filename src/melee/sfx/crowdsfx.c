#include "crowdsfx.h"

#include <melee/mp/forward.h>

#include <melee/ft/ftlib.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/mp/mplib.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

/* 4A2F08 */ CrowdSFX_UnkStruct crowdsfx;
/* 4D7050 */ CrowdSFX_UnkStruct* crowdsfx_ptr;

void fn_803219AC(HSD_GObj* gobj)
{
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    if (data->x4 < 0x10000) {
        data->x4 = data->x4 + 1;
    }
    un_80321A00(gobj);
    un_80321AF4(gobj);
}

void un_80321A00(HSD_GObj* gobj)
{
    s32 zero;
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
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
    mpCollisionBox* box = mpLib_80458868;
    HSD_GObj* cur;
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    s32 old_x24 = data->x24;
    s32 flag = 0;
    Vec3 pos;
    PAD_STACK(12);

    data->x24 = 0;
    cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER];

    while (cur != NULL) {
        if (ftLib_8008732C(cur) == 0) {
            if (ftLib_8008731C(cur) == 0) {
                ftLib_80086644(cur, &pos);

                if (pos.y < gCrowdConfig->blastzone_y_offset + box[1].bottom) {
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
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    data->x2C = lbAudioAx_800240B4(arg0);
}

void un_80321C28(void)
{
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    if (lbAudioAx_80023710(data->x2C) != 0) {
        lbAudioAx_800236B8(data->x2C);
    }
    data->x2C = -1;
}

void un_80321C70(void)
{
    CrowdSFX_UnkStruct* data;

    data = crowdsfx_ptr;

    if (data->x18 >= gCrowdConfig->max_gasp_count ||
        data->x18 < gCrowdConfig->x24)
    {
        return;
    }
    data->x1C = 1;
}

void un_80321CA4(s32 arg)
{
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    un_80321CE8();
    data->x28 = lbAudioAx_8002411C(arg);
}

void un_80321CE8(void)
{
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    if (lbAudioAx_80023710(data->x28) != 0) {
        lbAudioAx_800236B8(data->x28);
    }
    data->x28 = -1;
}

void un_80321D30(u32 arg0, f32 arg1)
{
    s32 cat;
    CrowdSFX_UnkStruct* data;

    data = crowdsfx_ptr;
    cat = un_80322298(arg1);
    if (cat >= 2) {
        if (un_80321EBC(arg0, arg1) != 0) {
            un_80321CE8();
            return;
        }
    }

    switch (cat) {
    case 3: {
        un_80321CA4(0x140);
        break;
    }
    case 2: {
        un_80321CA4(0x141);
        break;
    }
    case 1: {
        un_80321CA4(0x142);
        break;
    }
    }

    if (arg0 != 0) {
        if (data->xC == arg0) {
            un_80321C70();
        }
    }
}

bool un_80321EBC(u32 arg0, f32 arg1)
{
    s32 port;
    CrowdSFX_UnkStruct* data;
    HSD_GObj* gobj;
    u32 arg0_copy = arg0;

    data = crowdsfx_ptr;
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
        CrowdSFX_UnkStruct* data2 = crowdsfx_ptr;
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
        data2 = crowdsfx_ptr;
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
    CrowdSFX_UnkStruct* data = crowdsfx_ptr;
    HSD_GObj* gobj;

    switch (cat) {
    case 3:
        un_80321CA4(0x13d);
        break;
    case 2:
        un_80321CA4(0x13e);
        break;
    case 1:
        un_80321CA4(0x13f);
        break;
    case 0:
        return false;
    }

    if (arg0 != 0) {
        if (data->xC == arg0) {
            un_80321C70();
        }

        gobj = ftLib_8008741C(arg0);
        pl_8003FDC8(ftLib_80086BE0(gobj), ftLib_800874BC(gobj));
    }
    return true;
}

void un_80322178(int arg)
{
    PAD_STACK(8);

    switch (arg) {
    case 0:
        break;
    case 3:
        un_80321CA4(0x13d);
        break;
    case 2:
        un_80321CA4(0x13e);
        break;
    case 1:
        un_80321CA4(0x13f);
        break;
    }
}
