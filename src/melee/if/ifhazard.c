#include "ifhazard.h"

#include "baselib/forward.h"

#include "gm/gm_unsplit.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

// .sbss
/* 4D6D80 */ static HSD_GObj* un_804D6D80;
/* 4D6D84 */ static int un_804D6D84;
/* 4D6D88 */ static s32 un_804D6D88;
/* 4D6D8C */ static s32 un_804D6D8C;

void un_802FD604(int arg)
{
    HSD_JObj* jobj = GET_JOBJ(un_804D6D80);
    HSD_JObjReqAnimAll(jobj, 0.0);
    HSD_JObjAnimAll(jobj);
    un_804D6D84 = arg;
    un_804D6D88 = 1;
}

void un_802FD65C(void)
{
    un_804D6D88 = 0;
}

void un_802FD668(void)
{
    un_804D6D8C = 1;
}

void un_802FD674(void)
{
    un_804D6D8C = 0;
}

void fn_802FD680(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (un_804D6D84) {
        un_804D6D84--;
        if (un_804D6D84 == 0) {
            un_804D6D88 = 0;
        }
    }
    HSD_JObjAnimAll(jobj);
}

void fn_802FD6CC(HSD_GObj* gobj, int pass)
{
    if (!un_804D6D8C && un_804D6D88) {
        HSD_GObj_JObjCallback(gobj, pass);
    }
}

void un_802FD704(void) {}

void un_802FD708(void* arg0, int arg1)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(*(HSD_Joint**) arg0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, fn_802FD6CC, 11, 0);
    gm_8016895C(jobj, arg0, 0);
    HSD_GObjProc_8038FD54(gobj, fn_802FD680, 17);
    un_804D6D88 = 0;
    un_804D6D8C = 0;
    un_804D6D80 = gobj;
    switch (arg1) {
        Vec3 v;
    case 0:
        HSD_JObjGetTranslation(jobj, &v);
        v.x += 18.0f;
        HSD_JObjSetTranslate(jobj, &v);
        break;
    case 1:
    case 2:
        break;
    }
}

void un_802FD8A0(void* arg0)
{
    un_802FD708(arg0, 0);
}

void un_802FD8C4(void* arg0)
{
    un_802FD708(arg0, 1);
}

void un_802FD8E8(void* arg0)
{
    un_802FD708(arg0, 2);
}

void un_802FD90C(void) {}
