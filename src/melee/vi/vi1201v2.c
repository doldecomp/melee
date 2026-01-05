#include "vi/vi1201v2.h"

#include "vi.h"

#include "gm/gm_unsplit.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbshadow.h"
#include "mn/mnmain.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjplink.h>
#include <baselib/jobj.h>

extern HSD_GObj* un_804D7030;
extern HSD_GObj* un_804D7034;
extern u8 un_804D7028;

void un_803204C0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_803204E4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8032074C(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    char pad[24];
    HSD_JObjAnimAll(jobj);
    if (mn_8022F298(jobj) == 1.0F) {
        if (un_804D7030 != NULL) {
            HSD_GObjPLink_80390228(un_804D7030);
            un_804D7030 = NULL;
        }
        if (un_804D7034 != NULL) {
            HSD_GObjPLink_80390228(un_804D7034);
            un_804D7034 = NULL;
        }
        un_803205F4();
    }
}

void un_803208F0(HSD_GObj* gobj)
{
    u8* colors;
    char pad[8];
    lbShadow_8000F38C(0);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        colors = &un_804D7028;
        HSD_SetEraseColor(colors[0], colors[1], colors[2], colors[3]);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        *(s32*)((char*)gobj + 0x24) = 0x881;
        *(s32*)((char*)gobj + 0x20) = 0;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void un_80320984(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 1.0F || cobj->aobj->curr_frame == 30.0F) {
        vi_8031C9B4(0xd, 0);
    }
    if (cobj->aobj->curr_frame == 60.0F) {
        vi_8031C9B4(1, 0xdb);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_803210EC_OnFrame(void)
{
    vi_8031CAAC();
}
