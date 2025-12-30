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
