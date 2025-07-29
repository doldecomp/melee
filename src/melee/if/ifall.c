#include "ifall.h"

#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <melee/if/if_2F72.h>
#include <melee/if/ifmagnify.h>
#include <melee/if/ifstatus.h>
#include <melee/if/ifstock.h>
#include <melee/if/iftime.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/sc/types.h>
#include <melee/un/un_2FC9.h>

static struct ifAll_804A0FD8_t {
    /* 0x00 */ HSD_GObj* gobj;
    /* 0x04 */ HSD_GObj* gobj_2;
    /* 0x08 */ HSD_JObj* x8;
    /* 0x0C */ Vec3 xC;
    /* 0x18 */ Vec3 x18[6];
    /* 0x60 */ Vec3 x60[3];
    /* 0x84 */ Vec3 x84[2];
} ifAll_804A0FD8;

static u8 hidden; // HUD hidden bool

void ifAll_802F3394(void)
{
    ifStatus_802F6898();
    ifTime_802F405C();
    un_802FD450();
    ifMagnify_802FC8E8();
    un_802FD668();
    un_802FD910();
    un_802FF570();
}

void ifAll_802F33CC(void)
{
    ifStatus_802F68F0();
    ifTime_802F40B8();
    un_802FD45C();
    ifMagnify_802FC940();
    un_802FD674();
    un_802FD91C();
    un_802FF620();
}

HSD_GObj* ifAll_802F3404(void)
{
    return ifAll_804A0FD8.gobj;
}

Vec3* ifAll_802F3414(void)
{
    return &ifAll_804A0FD8.xC;
}

Vec3* ifAll_802F3424(int idx)
{
    return &ifAll_804A0FD8.x18[idx];
}

static inline void ifAll_802F343C_inline(int i)
{
    ifAll_804A0FD8.x18[i].x *= 0.65F;
}

void ifAll_802F343C(int arg0)
{
    HSD_JObj* jobj;
    int i;
    HSD_JObj* spC;

    jobj = ifAll_804A0FD8.x8;
    switch (arg0) {
    case 1:
        lb_80011E24(jobj, &spC, 9, -1);
        lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[0]);
        break;
    case 2:
        for (i = 0; i < arg0; i++) {
            lb_80011E24(jobj, &spC, i + 11, -1);
            lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[i]);
        }
        break;
    case 3:
        for (i = 0; i < arg0; i++) {
            lb_80011E24(jobj, &spC, i + 8, -1);
            lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[i]);
        }
        break;
    case 4:
        for (i = 0; i < arg0; i++) {
            lb_80011E24(jobj, &spC, i + 2, -1);
            lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[i]);
        }
        break;
    case 5:
    case 6:
        lb_80011E24(jobj, &spC, 6, -1);
        lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[0]);
        ifAll_802F343C_inline(0);

        lb_80011E24(jobj, &spC, 7, -1);
        lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[5]);
        ifAll_802F343C_inline(5);

        for (i = 1; i < 5; i++) {
            lb_80011E24(jobj, &spC, i + 1, -1);
            lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[i]);
            ifAll_802F343C_inline(i);
        }
        break;
    }
}

HSD_Archive** ifAll_802F3690(void)
{
    static HSD_Archive* archive;
    return &archive;
}

void ifAll_HideHUD(void)
{
    hidden = true;
}

void ifAll_ShowHUD(void)
{
    hidden = false;
}

bool ifAll_IsHUDHidden(void)
{
    return hidden;
}

static void fn_802F36B8(HSD_GObj* gobj, int unused)
{
    if (!ifAll_IsHUDHidden()) {
        if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
            HSD_GObj_80390ED0(gobj, 0x7);
            HSD_CObjEndCurrent();
        }
    }
}

static void ifAll_802F370C(SceneDesc* arg0)
{
    HSD_JObj* spC;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(arg0->models[0]->joint);
    ifAll_804A0FD8.x8 = jobj;
    lb_80011E24(jobj, &spC, 0xD, -1);
    lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.xC);

    lb_80011E24(jobj, &spC, 2, -1);
    lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[0]);
    lb_80011E24(jobj, &spC, 3, -1);
    lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[1]);
    lb_80011E24(jobj, &spC, 4, -1);
    lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[2]);
    lb_80011E24(jobj, &spC, 5, -1);
    lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[3]);
    lb_80011E24(jobj, &spC, 6, -1);
    lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[4]);
    lb_80011E24(jobj, &spC, 7, -1);
    lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x18[5]);

    for (i = 0; i < 3; i++) {
        lb_80011E24(jobj, &spC, i + 8, -1);
        lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x60[i]);
    }
    for (i = 0; i < 2; i++) {
        lb_80011E24(jobj, &spC, i + 11, -1);
        lb_8000B1CC(spC, NULL, &ifAll_804A0FD8.x84[i]);
    }
    HSD_GObjPLink_80390228(gobj);
}

void ifAll_802F390C(void)
{
    SceneDesc* sp14;

    HSD_LightDesc* lightdesc;
    HSD_Archive** parchive = ifAll_802F3690();

    PAD_STACK(0xC);

    ifAll_ShowHUD();
    lbArchive_80016F80(parchive, "IfAll");
    lbArchive_LoadSections(*parchive, (void**) &sp14, "ScInfDmg_scene_data",
                           0);
    ifAll_802F370C(sp14);

    {
        HSD_CObjDesc* desc = sp14->cameras[0].desc;
        HSD_GObj* gobj = GObj_Create(0x13, 0x14, 0);
        HSD_CObj* cobj = lb_80013B14((HSD_CameraDescPerspective*) desc);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_802F36B8, 8);
        gobj->gxlink_prios = 0xD00;
        ifAll_804A0FD8.gobj = gobj;
    }

    lightdesc = sp14->lights[0]->desc;
    {
        HSD_GObj* gobj = GObj_Create(0xE, 3, 0);
        HSD_LObj* lobj = HSD_LObjLoadDesc(lightdesc);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
        GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0xA, 0);
        ifAll_804A0FD8.gobj_2 = gobj;
    }

    ifStatus_802F7134();
    ifStatus_802F66A4();
    ifStock_802FAEC4();
    ifTime_802F480C();
    if_802F7E24();
    ifMagnify_802FC870();
    un_802FE260();
    un_802FD704();
    un_802FD4C8();
    un_802FF1B4();
    un_802FF498();
}

void ifAll_802F3A64(void)
{
    struct ifAll_804A0FD8_t* data;

    un_802FE390();
    ifStock_802FB390();
    ifStock_802FB41C();
    ifStock_802FB484();
    ifMagnify_802FC750();
    if_802F7E7C();
    ifTime_802F483C();
    ifStatus_802F6804();
    ifStatus_802F7220();

    data = &ifAll_804A0FD8;
    if (data->gobj != NULL) {
        HSD_GObjPLink_80390228(data->gobj);
    }

    if (data->gobj_2 != NULL) {
        HSD_GObjPLink_80390228(data->gobj_2);
    }

    un_802FD468();
    un_802FD90C();
    un_802FE390();
    un_802FF190();
    un_802FF4FC();
}
