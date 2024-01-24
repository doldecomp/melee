#include <platform.h>
#include <baselib/forward.h>

#include "lb/lbarchive.h"
#include "sc/scene.h"

#include <common_structs.h>
#include <dolphin/mtx/types.h>
#include <baselib/aobj.h>
#include <baselib/controller.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/mobj.h>
#include <baselib/random.h>
#include <baselib/sislib.h>

//@todo: float order hack
static f32 force_float_order_0(u32 x)
{
    return (f32) x;
}
static f32 force_float_order_1(void)
{
    return -9.5F;
}
static f32 force_float_order_2(void)
{
    return 9.1F;
}
static f32 force_float_order_3(void)
{
    return 17.0F;
}
static f32 force_float_order_4(void)
{
    return 364.68332F;
}
static f32 force_float_order_5(void)
{
    return 38.38772F;
}
static f32 force_float_order_6(void)
{
    return 0.0521F;
}

void mnDeflicker_8024A168(HSD_GObj* gobj);
void mnDeflicker_8024A2E8(HSD_GObj* gobj);
void mnDeflicker_8024A344(HSD_GObj* gobj);
void mnDeflicker_8024A3E8(HSD_GObj* gobj);
void mnDeflicker_8024A4BC(HSD_GObj* arg0);
void mnDeflicker_8024A6C4(HSD_GObj* arg0);

typedef struct {
    unsigned char x0;
    void* x4;
} gobj_user_data;

struct sislib_idk {
    float idk[40];
};

extern struct {
    unsigned char x0;
    char x1;
    short x2;
    int x4;
    unsigned long long x8;
    char x10;
    char x11;
} mn_804A04F0;

extern struct {
    unsigned short x0;
    short x2;
    int x4;
} mn_804D6BC8;

struct ThreeFloats {
    float x0;
    float x4;
    float x8;
};

unsigned int mn_80229624(int);
void mn_80229894(int, int, int);
void mn_8022F3D8(void*, int, int);
void mn_8022ED6C(HSD_JObj*, struct ThreeFloats*);
float mn_8022EC18(HSD_JObj*, float*, int);
void gmMainLib_8015F4F4(u8);
void gmMainLib_8015F588(u8);
void lbAudioAx_80024030(int);
int lb_80011E24(HSD_JObj*, HSD_JObj**, ...);
void lb_8001CE00(void);
void HSD_SisLib_803A5CC4(void*);
void lb_8001CE00(void);
u8 gmMainLib_8015F4E8(void);

extern void* mn_804D6BB8;
unsigned char mnDeflicker_804D6C3C;
HSD_GObj* mnDeflicker_804D6C38;
StaticModelDesc mnDeflicker_804A08B8;

struct ThreeFloats mnDeflicker_803EEFD8 = { 0.0F, 19.0F, -0.1F };
struct ThreeFloats mnDeflicker_803EEFE4 = { 20.0F, 30.0F, -0.1F };
struct ThreeFloats mnDeflicker_803EEFF0 = { 50.0F, 350.0F, 50.0F };

void mnDeflicker_8024A168(HSD_GObj* gobj)
{
    unsigned long long ty_permuter;
    HSD_JObj* asd[3];
    int stack[9];
    gobj_user_data* unk = mnDeflicker_804D6C38->user_data;
    if (mn_804D6BC8.x0 != 0) {
        mn_804D6BC8.x0--;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    } else {
        ty_permuter = (mn_804A04F0.x8 = mn_80229624(4));
        if ((ty_permuter & 0x20)) {
            lbAudioAx_80024030(0);
            gmMainLib_8015F4F4(
                ((gobj_user_data*) mnDeflicker_804D6C38->user_data)
                    ->x0); // inline
            lb_8001CE00();
            mn_804A04F0.x11 = 0;
            mn_80229894(4, 2, 3);
        } else if (mnDeflicker_804D6C3C && (ty_permuter & 0x200)) {
            unsigned char x;
            lbAudioAx_80024030(2);
            unk->x0 = (unk->x0 == 0);
            x = unk->x0; // inline arg?
            lb_80011E24(mnDeflicker_804D6C38->hsd_obj, asd, 5, -1);
            HSD_JObjReqAnimAll(asd[0], (f32) x);
            mn_8022F3D8(asd[0], 0xFF, 0x20);
            HSD_JObjAnimAll(asd[0]);
            gmMainLib_8015F588(x);
            gmMainLib_8015F4F4(
                ((gobj_user_data*) mnDeflicker_804D6C38->user_data)
                    ->x0); // inline
        }
    }
}

void mnDeflicker_8024A2E8(HSD_GObj* gobj)
{
    int x[2];
    float f = mn_8022EC18(GET_JOBJ(gobj), &mnDeflicker_803EEFE4.x0, 0x400);
    if (f == mnDeflicker_803EEFE4.x4) {
        HSD_GObjPLink_80390228(gobj);
    }
}

void mnDeflicker_8024A344(HSD_GObj* gobj)
{
    gobj_user_data* data = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (mn_804A04F0.x0 != 0x15) {
        HSD_GObjProc* p;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        p = HSD_GObjProc_8038FD54(gobj, &mnDeflicker_8024A2E8, 0);
        p->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(data->x4);
    } else {
        HSD_JObj* asd;
        int stack;
        lb_80011E24(jobj, &asd, 6, -1);
        mn_8022ED6C(asd, &mnDeflicker_803EEFF0);
    }
}

void mnDeflicker_8024A3E8(HSD_GObj* gobj)
{
    int stack[2];
    gobj_user_data* data = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_GObjProc* p;
    if (mn_804A04F0.x0 != 0x15) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        p = HSD_GObjProc_8038FD54(gobj, &mnDeflicker_8024A2E8, 0);
        p->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(data->x4);
    } else {
        float f = mn_8022EC18(jobj, &mnDeflicker_803EEFD8.x0, 0x400);
        if (f == mnDeflicker_803EEFD8.x4) {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            p = HSD_GObjProc_8038FD54(gobj, &mnDeflicker_8024A344, 0);
            p->flags_3 = HSD_GObj_804D783C;
            mnDeflicker_804D6C3C = 1;
        }
    }
}

// this feels off
#define GET_GOBJ_USER_DATA(gobj) ((gobj_user_data*) HSD_GObjGetUserData(gobj))
static inline void inline_test(void)
{
    struct sislib_idk* temp_r3_6;
    gobj_user_data* user_data = GET_GOBJ_USER_DATA(mnDeflicker_804D6C38);
    if (user_data->x4) {
        HSD_SisLib_803A5CC4(user_data->x4);
    }
    temp_r3_6 = (struct sislib_idk*) HSD_SisLib_803A5ACC(
        0, 1, -9.5F, 9.1F, 17.0F, 364.68332F, 38.38772F);
    user_data->x4 = temp_r3_6;
    temp_r3_6->idk[9] = 0.0521F;
    temp_r3_6->idk[10] = 0.0521F;
    HSD_SisLib_803A6368(temp_r3_6, 0xBD);
}

void mnDeflicker_8024A4BC(HSD_GObj* arg0)
{
    int fake1[3];
    HSD_JObj* sp1C;
    int fake2[1];
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    u8 temp_r29;
    struct sislib_idk* temp_r3_6;
    gobj_user_data* user_data;

    gobj = GObj_Create(HSD_GOBJ_CLASS_ITEM, 7U, 0x80);
    mnDeflicker_804D6C38 = gobj;
    jobj = HSD_JObjLoadJoint(mnDeflicker_804A08B8.joint);
    temp_r29 = HSD_GObj_804D7849; // ty permuter, why does this fix everything?
    HSD_GObjObjet_80390A70(gobj, temp_r29, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_80391070, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, mnDeflicker_804A08B8.animjoint,
                       mnDeflicker_804A08B8.matanim_joint,
                       mnDeflicker_804A08B8.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    user_data = HSD_MemAlloc(8);
    if (user_data == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mndeflicker.c", 344, "user_data");
    }
    user_data->x0 = gmMainLib_8015F4E8();
    user_data->x4 = 0;
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);
    proc = HSD_GObjProc_8038FD54(gobj, mnDeflicker_8024A3E8, 0U);
    proc->flags_3 = HSD_GObj_804D783C;
    temp_r29 = user_data->x0;
    lb_80011E24(GET_JOBJ(gobj), &sp1C, 5, -1);
    HSD_JObjReqAnimAll(sp1C, (f32) temp_r29);
    mn_8022F3D8(sp1C, 0xFF, 0x20);
    HSD_JObjAnimAll(sp1C);
    gmMainLib_8015F588(temp_r29);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    mn_8022F3D8(jobj, 0xFF, 0x400);
    HSD_JObjAnimAll(jobj);
    inline_test();
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
    lbArchive_80016AF0(
        archive, &mnDeflicker_804A08B8.joint, "MenMainConDf_Top_joint",
        &mnDeflicker_804A08B8.animjoint, "MenMainConDf_Top_animjoint",
        &mnDeflicker_804A08B8.matanim_joint, "MenMainConDf_Top_matanim_joint",
        &mnDeflicker_804A08B8.shapeanim_joint,
        "MenMainConDf_Top_shapeanim_joint", 0);
    mnDeflicker_8024A4BC(arg0);
    temp_r3 = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                    mnDeflicker_8024A168, 0);
    temp_r3->flags_3 = HSD_GObj_804D783C;
}
