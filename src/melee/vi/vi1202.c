#include "vi/vi1202.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

#include "ft/fighter.h"
#include "gm/gm_unsplit.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "vi.h"

typedef struct {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ void* x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ s32 x28;
    /* 0x2C */ s32 x2C;
} vi1202_UnkStruct;

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

void un_80321900(void)
{
    HSD_GObj* gobj = GObj_Create(0x16, 0x17, 0);
    HSD_GObjProc_8038FD54(gobj, fn_803219AC, 0x13);
    un_804D7050 = (vi1202_UnkStruct*)un_804A2F08;
    un_80321950(un_804D7050);
}

void un_80321950(void* s)
{
    ((vi1202_UnkStruct*)s)->x0 = 0;
    ((vi1202_UnkStruct*)s)->x4 = 0x10000;
    ((vi1202_UnkStruct*)s)->x8 = 1.0F;
    ((vi1202_UnkStruct*)s)->xC = 0;
    ((vi1202_UnkStruct*)s)->x10 = *(void**)((char*)Fighter_804D6500 + 0x20);
    ((vi1202_UnkStruct*)s)->x14 = 0x83D60;
    ((vi1202_UnkStruct*)s)->x18 = *(s32*)((char*)Fighter_804D6500 + 0x28);
    ((vi1202_UnkStruct*)s)->x1C = 0;
    ((vi1202_UnkStruct*)s)->x20 = 0;
    ((vi1202_UnkStruct*)s)->x24 = 0;
    ((vi1202_UnkStruct*)s)->x2C = -1;
    ((vi1202_UnkStruct*)s)->x28 = -1;
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

void un_80321BF8(void)
{
    vi1202_UnkStruct* data;
    char pad[8];
    data = un_804D7050;
    data->x2C = lbAudioAx_800240B4();
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
    void* fighter = Fighter_804D6500;
    s32 x18 = data->x18;
    if (x18 >= *(s32*)((char*)fighter + 0x28)) {
        return;
    }
    if (x18 >= *(s32*)((char*)fighter + 0x24)) {
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

extern char mpLib_80458868[];

bool un_80322258(float arg)
{
    f32 val2c = *(f32*)((char*)Fighter_804D6500 + 0x2c);
    f32 val18 = *(f32*)(mpLib_80458868 + 0x18);
    f32 val1c;
    if (arg >= val2c + val18) {
        val1c = *(f32*)(mpLib_80458868 + 0x1c);
        if (arg > val1c - val2c) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

s32 un_80322298(float arg)
{
    void* fighter = Fighter_804D6500;
    if (arg >= *(f32*)((char*)fighter + 0x8)) {
        return 3;
    }
    if (arg >= *(f32*)((char*)fighter + 0x4)) {
        return 2;
    }
    if (arg >= *(f32*)((char*)fighter + 0x0)) {
        return 1;
    }
    return 0;
}

f32 un_803222EC(f32 arg1, f32 arg2)
{
    void* fighter = Fighter_804D6500;
    if (!(arg2 > *(f32*)((char*)fighter + 0xc))) {
        return arg1;
    }
    if (!(arg2 < *(f32*)((char*)fighter + 0x10))) {
        return arg1;
    }
    return arg1 * *(f32*)((char*)fighter + 0x14);
}

void un_80322314(void)
{
    vi1202_UnkStruct* data = un_804D7050;
    void* fighter = Fighter_804D6500;
    if (data->x18 >= *(s32*)((char*)fighter + 0x28)) {
        return;
    }
    data->x1C = 1;
    data->x20 = 1;
}

int un_80322598(int arg0, float arg1)
{
    f32 val14 = *(f32*)(mpLib_80458868 + 0x14);
    s32 cat;
    void* fighter;
    if (arg1 >= val14) {
        goto ret_zero;
    }
    fighter = Fighter_804D6500;
    if (arg1 < *(f32*)((char*)fighter + 0x38) + val14) {
ret_zero:
        return 0;
    }
    if (arg1 > *(f32*)((char*)fighter + 0x30) + val14) {
        cat = 3;
    } else if (arg1 > *(f32*)((char*)fighter + 0x34) + val14) {
        cat = 2;
    } else {
        cat = 1;
    }
    un_8032201C(arg0, cat);
}
