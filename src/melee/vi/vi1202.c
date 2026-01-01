#include "vi/vi1202.h"

#include "vi.h"

#include "ft/fighter.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

struct vi1202_UnkStruct {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ s32 x28;
    /* 0x2C */ s32 x2C;
};

void un_8032110C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321130(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321154(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321294(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 1.0F) {
        vi_8031C9B4(0xe, 0);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_803218E0_OnFrame(void)
{
    vi_8031CAAC();
}

extern char un_804A2F08[];
extern vi1202_UnkStruct* un_804D7050;
extern char mpLib_80458868[];

void un_80321900(void)
{
    HSD_GObj* gobj = GObj_Create(0x16, 0x17, 0);
    HSD_GObjProc_8038FD54(gobj, fn_803219AC, 0x13);
    un_804D7050 = (vi1202_UnkStruct*) un_804A2F08;
    un_80321950(un_804D7050);
}

void un_80321950(vi1202_UnkStruct* s)
{
    s->x0 = 0;
    s->x4 = 0x10000;
    s->x8 = 1.0F;
    s->xC = 0;
    s->x10 = Fighter_804D6500->x20;
    s->x14 = 0x83D60;
    s->x18 = Fighter_804D6500->x28;
    s->x1C = 0;
    s->x20 = 0;
    s->x24 = 0;
    s->x2C = -1;
    s->x28 = -1;
}

void fn_803219AC(HSD_GObj* gobj)
{
    vi1202_UnkStruct* data = un_804D7050;
    if (data->x4 < 0x10000) {
        data->x4 = data->x4 + 1;
    }
    un_80321A00(gobj);
    un_80321AF4(gobj);
}

void un_80321A00(HSD_GObj* gobj)
{
    s32 zero;
    vi1202_UnkStruct* data = un_804D7050;
    vi1202_ViData* vdata = Fighter_804D6500;

    if (data->x18 >= vdata->x28) {
        if (data->x10 < vdata->x20) {
            data->x10 = data->x10 + 1;
        }
        return;
    }

    if (lbAudioAx_80023710(data->x2C) != 0) {
        return;
    }
    data->x18 = data->x18 + 1;

    if (data->x18 < Fighter_804D6500->x28) {
        if (data->x1C != 0) {
            zero = 0;
            data->x1C = zero;
            data->x10 = zero;
            data->x18 = Fighter_804D6500->x28;
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
    vi1202_UnkStruct* data = un_804D7050;
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

                if (pos.y < Fighter_804D6500->x40 + M2C_FIELD(mpLib, f32*, 0x14)) {
                    data->x24 = data->x24 + 1;
                } else {
                    if ((u32) data->xC == ftLib_80087460(cur)) {
                        flag = 1;
                    }
                }
            }
        }
        cur = cur->next;
    }

    if (old_x24 < Fighter_804D6500->x3C) {
        if (data->x24 >= Fighter_804D6500->x3C) {
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
    vi1202_UnkStruct* data;
    char pad[8];
    data = un_804D7050;
    data->x2C = lbAudioAx_800240B4(arg0);
}

void un_80321C28(void)
{
    vi1202_UnkStruct* data = un_804D7050;
    if (lbAudioAx_80023710(data->x2C) != 0) {
        lbAudioAx_800236B8(data->x2C);
    }
    data->x2C = -1;
}

void un_80321C70(void)
{
    vi1202_UnkStruct* data = un_804D7050;
    vi1202_ViData* vdata = Fighter_804D6500;
    s32 x18 = data->x18;
    if (x18 >= vdata->x28) {
        return;
    }
    if (x18 >= vdata->x24) {
        data->x1C = 1;
    }
}

void un_80321CA4(s32 arg)
{
    vi1202_UnkStruct* data = un_804D7050;
    un_80321CE8();
    data->x28 = lbAudioAx_8002411C(arg);
}

void un_80321CE8(void)
{
    vi1202_UnkStruct* data = un_804D7050;
    if (lbAudioAx_80023710(data->x28) != 0) {
        lbAudioAx_800236B8(data->x28);
    }
    data->x28 = -1;
}

void un_8032201C(int arg0, s32 cat)
{
    vi1202_UnkStruct* data = un_804D7050;
    char pad[16];

    switch (cat) {
    case 0:
        return;
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
    }

    if ((u32)arg0 != 0) {
        if ((u32)data->xC == (u32)arg0) {
            vi1202_ViData* vdata = Fighter_804D6500;
            vi1202_UnkStruct* data2 = un_804D7050;
            if (data2->x18 < vdata->x28) {
                if (data2->x18 >= vdata->x24) {
                    data2->x1C = 1;
                }
            }
        }
    }

    {
        HSD_GObj* gobj = ftLib_8008741C(arg0);
        s32 port = ftLib_800874BC(gobj);
        data->x10 = port;
    }
}

void un_80322178(int arg)
{
    vi1202_UnkStruct* data;
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
    f32 val2c = Fighter_804D6500->x2C;
    f32 val18 = M2C_FIELD(mpLib_80458868, f32*, 0x18);
    f32 val1c;
    if (arg >= val2c + val18) {
        val1c = M2C_FIELD(mpLib_80458868, f32*, 0x1c);
        if (arg > val1c - val2c) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

s32 un_80322298(float arg)
{
    vi1202_ViData* vdata = Fighter_804D6500;
    if (arg >= vdata->x8) {
        return 3;
    }
    if (arg >= vdata->x4) {
        return 2;
    }
    if (arg >= vdata->x0) {
        return 1;
    }
    return 0;
}

f32 un_803222EC(f32 arg1, f32 arg2)
{
    vi1202_ViData* vdata = Fighter_804D6500;
    if (!(arg2 > vdata->xC)) {
        return arg1;
    }
    if (!(arg2 < vdata->x10)) {
        return arg1;
    }
    return arg1 * vdata->x14;
}

void un_80322314(void)
{
    vi1202_UnkStruct* data = un_804D7050;
    vi1202_ViData* vdata = Fighter_804D6500;
    if (data->x18 >= vdata->x28) {
        return;
    }
    data->x1C = 1;
    data->x20 = 1;
}

bool un_803224DC(s32 spawn_id, f32 pos_x, f32 kb_mag)
{
    void* fighter = Fighter_804D6500;
    s32 cat;
    s32 out_of_bounds;

    if (kb_mag >= M2C_FIELD(fighter, f32*, 0x8)) {
        cat = 3;
    } else if (kb_mag >= M2C_FIELD(fighter, f32*, 0x4)) {
        cat = 2;
    } else if (kb_mag >= M2C_FIELD(fighter, f32*, 0x0)) {
        cat = 1;
    } else {
        cat = 0;
    }

    {
        f32 val2c = M2C_FIELD(fighter, f32*, 0x2c);
        f32 val18 = M2C_FIELD(mpLib_80458868, f32*, 0x18);
        f32 val1c;

        if (pos_x < val2c + val18) {
            out_of_bounds = 1;
        } else {
            val1c = M2C_FIELD(mpLib_80458868, f32*, 0x1c);
            if (pos_x > val1c - val2c) {
                out_of_bounds = 1;
            } else {
                out_of_bounds = 0;
            }
        }
    }

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
    vi1202_ViData* vdata;
    if (arg1 >= val14) {
        goto ret_zero;
    }
    vdata = Fighter_804D6500;
    if (arg1 < vdata->x38 + val14) {
ret_zero:
        return 0;
    }
    if (arg1 > vdata->x30 + val14) {
        cat = 3;
    } else if (arg1 > vdata->x34 + val14) {
        cat = 2;
    } else {
        cat = 1;
    }
    un_8032201C(arg0, cat);
}
