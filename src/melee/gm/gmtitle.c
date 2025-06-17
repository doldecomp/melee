#include "baselib/forward.h"

#include "gmtitle.h"

#include "lb/lb_00F9.h"
#include "mn/mn_2295.h"

#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>

Vec3 gmTitle_803DA4F0 = { 0, 1600.0f, 400.0f };
Vec3 gmTitle_803DA4FC = { 0, 1330.0f, 130.0f };

static HSD_CameraDescPerspective* gmTitle_804D6708;
static HSD_LightDesc** gmTitle_804D670C;
static HSD_FogDesc* gmTitle_804D6710;

static void gmTitle_801A146C(HSD_GObj* gobj)
{
    mn_8022ED6C(GET_JOBJ(gobj), &gmTitle_803DA4FC);
}

static void gmTitle_801A1630(HSD_GObj* gobj)
{
    mn_8022ED6C(GET_JOBJ(gobj), &gmTitle_803DA4F0);
}

static void gmTitle_801A1814(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_GObj_80390ED0(gobj, 0x7);
        HSD_CObjEndCurrent();
    }
}

void gmTitle_801A185C(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj = lb_80013B14(gmTitle_804D6708);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, gmTitle_801A1814, 0xC);
    gobj->gxlink_prios = 0x209;
}

static void gmTitle_801A18D4(HSD_GObj* gobj, int unused)
{
    GXColor erase_color;

    erase_color = gmTitle_804D6710->color;

    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_SetEraseColor(erase_color.r, erase_color.g, erase_color.b,
                          erase_color.a);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        HSD_CObjEndCurrent();
    }
}

void gmTitle_801A1944(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj = lb_80013B14(gmTitle_804D6708);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, gmTitle_801A18D4, 0);
}

void gmTitle_801A19AC(void)
{
    HSD_GObj* gobj;
    HSD_LObj* lobj;
    PAD_STACK(8);

    gobj = GObj_Create(0xB, 0x3, 0x80);
    lobj = lb_80011AC4(gmTitle_804D670C);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

static void gmTitle_801A1A18(HSD_GObj* gobj)
{
    HSD_FogInterpretAnim(GET_FOG(gobj));
}

HSD_GObj* gmTitle_801A1A3C(void)
{
    HSD_GObj* gobj;
    HSD_Fog* fog;

    gobj = GObj_Create(0xA, 0x3, 0);
    fog = HSD_FogLoadDesc(gmTitle_804D6710);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    HSD_GObjProc_8038FD54(gobj, gmTitle_801A1A18, 0);

    return gobj;
}
