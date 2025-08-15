#include "gm_1832.h"

#include "gm_unsplit.h"

#include <math_ppc.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/util.h>
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftdemo.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>

static struct {
    int x0;
    HSD_JObj* x4[0xF];
} lbl_804735A8;
static struct {
    HSD_ImageDesc x40[3];
    HSD_ImageDesc x88[3];
    u8 pad[0xE0 - 0x88 - 3 * 0x18];
    u8 xE0;
    u8 xE1;
    u8 xE2;
    u8 xE3;
    int xE4;
    int xE8;
    u8 xEC;
    u8 xED;
    u8 xEE;
    u8 xEF;
    u8 xF0;
    u8 xF1;
} lbl_804735E8;

static struct {
    u8 pad[0x6A8];
    Vec3 x630[4];
    Vec3 x650[4];
    Vec3 x6A8[1];
}* lbl_804D6604;

/// #fn_8018325C

/// #fn_80184138

void fn_801849E0(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 0);
}

void fn_80184A04(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 1);
}

void fn_80184A28(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 2);
}

void fn_80184A4C(HSD_GObj* gobj)
{
    fn_80184138(gobj, 0);
}

void fn_80184A70(HSD_GObj* gobj)
{
    fn_80184138(gobj, 1);
}

void fn_80184A94(HSD_GObj* gobj)
{
    fn_80184138(gobj, 2);
}

/// #fn_80184AB8

/// #fn_8018504C

/// #fn_801851C0

void fn_801852FC(HSD_GObj* gobj)
{
    int i;
    int j;

    PAD_STACK(0x18);

    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < lbl_804735E8.xE0; i++) {
            for (j = 0; j < lbl_804735E8.xE0 + 1; j++) {
                if (j == 0 || i + 1 != j) {
                    Player_800366DC(j, 0);
                } else {
                    Player_800366DC(j, 1);
                }
            }
            Camera_800313E0(gobj, 1);
            HSD_StateInvalidate(-1);
            HSD_ImageDescCopyFromEFB(&lbl_804735E8.x40[i], 0x82, 0, 0, 0);
            HSD_ImageDescCopyFromEFB(&lbl_804735E8.x88[i], 0x82, 0, 1, 1);
        }
        HSD_CObjEndCurrent();
    }
    lbl_804735E8.xE1 = 1;
}

void fn_80185408(int x, float arg8, float arg9, float argA, float argB)
{
    u8 _[0x30];
    Mtx sp1C;
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE,
                  GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                  GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(0);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXLoadPosMtxImm(HSD_identityMtx, 0);
    GXSetCurrentMtx(0);
    MTXOrtho(sp1C, 0.0F, 480.0F, 0.0F, 640.0F, 0.0F, 5000.0F);
    GXSetProjection(sp1C, GX_ORTHOGRAPHIC);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = argA;
    GXWGFifo.f32 = arg8;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argB;
    GXWGFifo.f32 = arg8;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argB;
    GXWGFifo.f32 = arg9;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argA;
    GXWGFifo.f32 = arg9;
    GXWGFifo.f32 = -4932.0F;
    GXSetColorUpdate(1);
    HSD_StateInvalidate(-1);
}

extern float MSL_TrigF_80400770[];
extern float MSL_TrigF_80400774[];
double fn_801855BC(double arg8)
{
    f64 temp_f2;
    f64 temp_f2_2;
    f64 temp_f2_3;
    f64 temp_f2_4;

    if (arg8 > 0.0) {
        temp_f2_2 = __frsqrte(arg8);
        temp_f2_3 =
            0.5 * temp_f2_2 * -(((f64) arg8 * (temp_f2_2 * temp_f2_2)) - 3.0);
        temp_f2_4 =
            0.5 * temp_f2_3 * -(((f64) arg8 * (temp_f2_3 * temp_f2_3)) - 3.0);
        temp_f2 =
            0.5 * temp_f2_4 * -(((f64) arg8 * (temp_f2_4 * temp_f2_4)) - 3.0);
        return arg8 *
               (0.5 * temp_f2 * -(((f64) arg8 * (temp_f2 * temp_f2)) - 3.0));
    }
    if (0.0 == arg8) {
        return 0.0;
    }
    if (arg8) {
        return MSL_TrigF_80400770[0];
    }
    return MSL_TrigF_80400774[0];
}

void fn_8018564C(HSD_GObj* gobj)
{
    fn_80185408(0xFC8000, 0.0F, 480.0F, 200.0F, 640.0F);
    HSD_SObjLib_803A54EC(gobj, 7);
}

void fn_8018569C(HSD_GObj* gobj)
{
    int i;
    PAD_STACK(8);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < lbl_804735E8.xE0 + 1; i++) {
            if (i == 0) {
                Player_800366DC(i, 1);
            } else {
                Player_800366DC(i, 0);
            }
        }
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x1001;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void fn_8018575C(HSD_GObj* gobj)
{
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x1001;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

/// #fn_801857C4

/// #fn_801859C8

/// #fn_80185A0C

/// #fn_80185D64

/// #fn_80185E34

/// #fn_80185F5C

/// #fn_80186080

/// #fn_801861B8

static SceneDesc* lbl_804D65FC;

void fn_80186400(void)
{
    HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(lbl_804D65FC->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObjProc_8038FD54(gobj, fn_80184AB8, 0);
    gm_8016895C(jobj, lbl_804D65FC->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (lbl_804735E8.xE4 != 3) {
        lb_80011E24(jobj, &lbl_804735A8.x4[0], 4, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[1], 5, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[2], 0x3A, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[3], 0x3B, -1);
        HSD_JObjSetTranslateZ(lbl_804735A8.x4[2], 10000.0F);
        HSD_JObjSetTranslateZ(lbl_804735A8.x4[3], 10000.0F);
    }
}

/// #fn_80186634

void gm_80186DFC_OnFrame(void)
{
    if (lbl_804735A8.x0 != 0) {
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

static struct enterdata {
    int x0, x4;
} lbl_804D6618;

static struct {
    int x0, x4;
    HSD_JObj* x8;
    HSD_JObj* xC;
} lbl_804736B0;

/// #gm_80186E30_OnEnter

void fn_80186EFC(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(8);
    HSD_JObjReqAnimAll(lbl_804736B0.xC, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (lbl_804736B0.x4 < 0x8C) {
        lbl_804736B0.x4++;
    } else {
        lbl_804736B0.x0 = 1;
    }
}

/// #fn_80186F6C

extern HSD_Archive* lbl_804D6610;

#pragma push
#pragma dont_inline on
HSD_GObjProc* fn_801873F0(void)
{
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(lbl_804D6618.x0, lbl_804D6610, 1);
    Player_SetPlayerCharacter(0, lbl_804D6618.x0);
    Player_SetCostumeId(0, lbl_804D6618.x4);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 0.0f);
    Player_SetModelScale(0, 1.0f);
    Player_80036F34(0, 6);
    return HSD_GObjProc_8038FD54(Player_GetEntity(0), fn_80186F6C, 0x16U);
}
#pragma pop

void fn_80187494(HSD_GObj* gobj, int arg1)
{
    int temp_ret = HSD_CObjSetCurrent(gobj->hsd_obj);
    PAD_STACK(4);
    if (temp_ret != 0) {
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x801;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

static SceneDesc* lbl_804D6614;

void fn_801874FC(void)
{
    HSD_JObj* sp8;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D6614->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObjProc_8038FD54(gobj, fn_80186EFC, 0);
    gm_8016895C(jobj, lbl_804D6614->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, &sp8, 0x3A, -1);
    HSD_JObjSetTranslateZ(sp8, 10000.0F);
    lb_80011E24(jobj, &sp8, 0x3B, -1);
    HSD_JObjSetTranslateZ(sp8, 10000.0F);
    lb_80011E24(jobj, &lbl_804736B0.x8, 5, -1);
    lb_80011E24(jobj, &lbl_804736B0.xC, 6, -1);
}

/// #fn_801874FC

#pragma push
#pragma dont_inline on
void fn_80187714(void)
{
    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(64);
    Stage_802251E8(0, NULL);
    Stage_8022524C();
    Item_80266FA8();
    Item_80266FCC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
}
#pragma pop

extern HSD_Archive* lbl_804D6610;

void gm_8018776C_OnFrame(void)
{
    if (lbl_804736B0.x0 != 0) {
        lbArchive_80016EFC(lbl_804D6610);
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

#pragma push
#pragma dont_inline on
void gm_801877A8_OnEnter(void* arg0_)
{
    struct enterdata* arg0 = arg0_;
    HSD_GObj* temp_r30;
    HSD_GObj* temp_r30_2;
    HSD_GObj* temp_r30_3;
    HSD_LObj* lobj;
    HSD_CObj* cobj;
    HSD_Fog* fog;
    PAD_STACK(8);

    lbl_804736B0.x0 = 0;
    lbl_804736B0.x4 = 0;

    lbl_804D6618 = *arg0;
    fn_80187714();
    lbl_804D6610 = lbArchive_80016DBC("IrAls", &lbl_804D6614,
                                      "ScItrAllstar_scene_data", 0);

    temp_r30 = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(lbl_804D6614->cameras[0].desc);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(temp_r30, fn_80187494, 8);
    temp_r30->gxlink_prios = 0x801;

    temp_r30_2 = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(lbl_804D6614->lights);
    HSD_GObjObject_80390A70(temp_r30_2, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(temp_r30_2, HSD_GObj_LObjCallback, 0, 0);
    fn_801874FC();

    temp_r30_3 = GObj_Create(0xE, 0xF, 0);
    fog = HSD_FogLoadDesc(lbl_804D6614->fogs[0].desc);
    HSD_GObjObject_80390A70(temp_r30_3, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(temp_r30_3, HSD_GObj_FogCallback, 0xB, 0);
    fn_801873F0();
    lbAudioAx_80023F28(0x2D);
}
#pragma pop

/// #fn_80187910

/// #fn_80187AB4

void fn_80187C9C(HSD_GObj* gobj, int arg1)
{
    GXSetZMode(0, GX_NEVER, 0);
    HSD_GObj_JObjCallback(gobj, arg1);
    HSD_StateInvalidate(0x40);
}

/// #fn_80187CF4

/// #gm_80187F48_OnEnter

/// #gm_80188364_OnLeave

/// #gm_8018838C_OnFrame

/// #gm_801883C0

bool gm_8018841C(void)
{
    if (gm_801A4310() == MJ_TRAINING) {
        return true;
    }
    return false;
}

static int lbl_80473700[69];

int gm_80188454(int idx)
{
    return lbl_80473700[idx + 2];
}

/// #fn_8018846C

/// #fn_801884F8

/// #fn_80188550

/// #fn_80188644

/// #fn_80188738

/// #fn_80188910

/// #fn_80188B3C

/// #fn_80188D3C

/// #fn_80188EE8

/// #fn_801891F4

/// #fn_80189B88

/// #gm_80189CDC

/// #fn_8018A000

/// #gm_8018A160

/// #gm_8018A188

/// #gm_8018A1D8

/// #gm_8018A228

/// #gm_8018A25C

/// #gm_8018A290

/// #gm_8018A2C4

/// #gm_8018A314

/// #fn_8018A364
