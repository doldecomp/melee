#include <platform.h>

#include <baselib/forward.h>

#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"
#include "mn/types.h"
#include "sc/types.h"

#include <dolphin/os.h>
#include <baselib/controller.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/object.h>
#include <baselib/sislib.h>

void mnDeflicker_8024A168(HSD_GObj* gobj);
void mnDeflicker_8024A2E8(HSD_GObj* gobj);
void mnDeflicker_8024A344(HSD_GObj* gobj);
void mnDeflicker_8024A3E8(HSD_GObj* gobj);
void mnDeflicker_8024A4BC(HSD_GObj* arg0);
void mnDeflicker_8024A6C4(HSD_GObj* arg0);

void gmMainLib_8015F4F4(u8);
void gmMainLib_8015F588(u8);
u8 gmMainLib_8015F4E8(void);
void lb_8001CE00(void);

unsigned char mnDeflicker_804D6C3C;
HSD_GObj* mnDeflicker_804D6C38;
StaticModelDesc mnDeflicker_804A08B8;

Vec3 mnDeflicker_803EEFD8 = { 0.0F, 19.0F, -0.1F };
Vec3 mnDeflicker_803EEFE4 = { 20.0F, 30.0F, -0.1F };
Vec3 mnDeflicker_803EEFF0 = { 50.0F, 350.0F, 50.0F };

void mnDeflicker_8024A168(HSD_GObj* gobj)
{
    u64 events;
    HSD_JObj* asd[2];
    int stack[5];
    Menu* menu = GET_MENU(mnDeflicker_804D6C38);
    if (mn_804D6BC8.x0 != 0) {
        Menu_DecrementAnimTimer();
        return;
    }
    events = Menu_GetAllEvents();
    if ((events & MenuEvent_Back)) {
        sfxBack();
        gmMainLib_8015F4F4(
            ((Menu*) mnDeflicker_804D6C38->user_data)->cursor); // inline
        lb_8001CE00();
        mn_804A04F0.x11 = 0;
        mn_80229894(4, 2, 3);
    } else if (mnDeflicker_804D6C3C && (events & MenuEvent_unk4)) {
        unsigned char x;
        PAD_STACK(4);
        sfxMove();
        menu->cursor = (menu->cursor == 0);
        x = menu->cursor; // inline arg?
        lb_80011E24(mnDeflicker_804D6C38->hsd_obj, asd, 5, -1);
        HSD_JObjReqAnimAll(asd[0], (f32) x);
        mn_8022F3D8(asd[0], 0xFF, 0x20);
        HSD_JObjAnimAll(asd[0]);
        gmMainLib_8015F588(x);
        gmMainLib_8015F4F4(
            ((Menu*) mnDeflicker_804D6C38->user_data)->cursor); // inline
    }
}

void mnDeflicker_8024A2E8(HSD_GObj* gobj)
{
    int x[2];
    float f = mn_8022EC18(GET_JOBJ(gobj), &mnDeflicker_803EEFE4.x, 0x400);
    if (f == mnDeflicker_803EEFE4.y) {
        HSD_GObjPLink_80390228(gobj);
    }
}

void mnDeflicker_8024A344(HSD_GObj* gobj)
{
    Menu* menu = GET_MENU(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (mn_804A04F0.x0 != 0x15) {
        HSD_GObjProc* p;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        p = HSD_GObjProc_8038FD54(gobj, &mnDeflicker_8024A2E8, 0);
        p->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
    } else {
        HSD_JObj* asd;
        lb_80011E24(jobj, &asd, 6, -1);
        mn_8022ED6C(asd, &mnDeflicker_803EEFF0);
    }
}

void mnDeflicker_8024A3E8(HSD_GObj* gobj)
{
    Menu* menu = GET_MENU(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_GObjProc* p;
    if (mn_804A04F0.x0 != 0x15) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        p = HSD_GObjProc_8038FD54(gobj, &mnDeflicker_8024A2E8, 0);
        p->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
    } else {
        float f = mn_8022EC18(jobj, &mnDeflicker_803EEFD8.x, 0x400);
        if (f == mnDeflicker_803EEFD8.y) {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            p = HSD_GObjProc_8038FD54(gobj, &mnDeflicker_8024A344, 0);
            p->flags_3 = HSD_GObj_804D783C;
            mnDeflicker_804D6C3C = 1;
        }
    }
}

static void mnDeflicker_8024A4BC_inline(void)
{
    Menu* menu = GET_MENU(mnDeflicker_804D6C38);
    if (menu->text) {
        HSD_SisLib_803A5CC4(menu->text);
    }
    Menu_InitCenterText(menu, 0xBD);
}

void mnDeflicker_8024A4BC(HSD_GObj* arg0)
{
    int fake1[3];
    HSD_JObj* sp1C;
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    u8 temp_r29;
    Menu* menu;
    PAD_STACK(4);

    gobj = GObj_Create(HSD_GOBJ_CLASS_ITEM, 7U, 0x80);
    mnDeflicker_804D6C38 = gobj;
    jobj = HSD_JObjLoadJoint(mnDeflicker_804A08B8.joint);
    temp_r29 = HSD_GObj_804D7849; // ty permuter, why does this fix everything?
    HSD_GObjObject_80390A70(gobj, temp_r29, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, mnDeflicker_804A08B8.animjoint,
                       mnDeflicker_804A08B8.matanim_joint,
                       mnDeflicker_804A08B8.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    menu = HSD_MemAlloc(8);
    if (menu == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mndeflicker.c", 344, "user_data");
    }
    menu->cursor = gmMainLib_8015F4E8();
    menu->text = NULL;
    GObj_InitUserData(gobj, 0, HSD_Free, menu);
    proc = HSD_GObjProc_8038FD54(gobj, mnDeflicker_8024A3E8, 0U);
    proc->flags_3 = HSD_GObj_804D783C;
    temp_r29 = menu->cursor;
    lb_80011E24(GET_JOBJ(gobj), &sp1C, 5, -1);
    HSD_JObjReqAnimAll(sp1C, (f32) temp_r29);
    mn_8022F3D8(sp1C, 0xFF, 0x20);
    HSD_JObjAnimAll(sp1C);
    gmMainLib_8015F588(temp_r29);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    mn_8022F3D8(jobj, 0xFF, 0x400);
    HSD_JObjAnimAll(jobj);
    mnDeflicker_8024A4BC_inline();
}

void mnDeflicker_8024A6C4(HSD_GObj* arg0)
{
    HSD_GObjProc* temp_r3;
    HSD_Archive* archive;

    mn_804D6BC8.x0 = 5;
    mn_804A04F0.x1 = mn_804A04F0.x0;
    mn_804A04F0.x0 = 0x15;
    mn_804A04F0.x2 = 0;
    mnDeflicker_804D6C3C = 0;
    archive = mn_804D6BB8;
    lbArchive_LoadSections(
        archive, (void**) &mnDeflicker_804A08B8.joint,
        "MenMainConDf_Top_joint", &mnDeflicker_804A08B8.animjoint,
        "MenMainConDf_Top_animjoint", &mnDeflicker_804A08B8.matanim_joint,
        "MenMainConDf_Top_matanim_joint",
        &mnDeflicker_804A08B8.shapeanim_joint,
        "MenMainConDf_Top_shapeanim_joint", 0);
    mnDeflicker_8024A4BC(arg0);
    temp_r3 = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                    mnDeflicker_8024A168, 0);
    temp_r3->flags_3 = HSD_GObj_804D783C;
}
