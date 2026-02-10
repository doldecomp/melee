#include "grmutecity.h"

#include "grmutecity.static.h"
#include <platform.h>

#include "forward.h"

#include "gr/grdatfiles.h"
#include "gr/grfzerocar.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "if/ifhazard.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/lobj.h>

extern s16 grMc_803E34A4[];

static struct {
    int x0;
}* grMc_804D69D0;

static f32 light_ref_br = 40000.0f;
static f32 light_ref_dist = 0.99f;
static s32 light_dist_func = 0x1;

void grMuteCity_801EFC68(bool arg) {}

void grMuteCity_801EFC6C(void)
{
    grMc_804D69D0 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 0;
    grMuteCity_801EFD0C(0);
    Ground_801C39C0();
    Ground_801C3BB4();
    grMuteCity_801EFD0C(0x1E);
    un_802FD8C4(grMuteCity_801F28A8());
    un_802FD65C();
}

void grMuteCity_801EFCDC(void) {}

void grMuteCity_801EFCE0(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grMuteCity_801EFD04(void)
{
    return false;
}

/// #grMuteCity_801EFD0C

/// #grMuteCity_801EFDF8

bool grMuteCity_801F0118(Ground_GObj* arg)
{
    return false;
}

void grMuteCity_801F0120(Ground_GObj* gobj)
{
    Ground* ground;
    HSD_LObj* lobj;

    ground = GET_GROUND(gobj);
    if (ground->gv.mutecity.x110 != NULL) {
        HSD_LObjSetDistAttn(ground->gv.mutecity.x110, light_ref_dist,
                            light_ref_br, light_dist_func);
    }
    grMuteCity_801F04B8(gobj);
    grMuteCity_801F0948(gobj);
    if (ground->gv.mutecity.xD0_flags.b0 != 0) {
        grMuteCity_801F0D20(gobj);
    }
    grMuteCity_801F1328();
    grMuteCity_801F1A34(ground->gv.mutecity.xCC, gobj);
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grMuteCity_801F01B0(Ground_GObj* arg) {}

void grMuteCity_801F01B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grMaterial_801C94D8(jobj);
    grAnime_801C8138(gobj, gp->map_id, false);
    grAnime_801C775C(gobj, 0, 7, 0.0f, 3600.0f);
    grAnime_801C7FF8(gobj, 6, 7, 1, 0.0f, 1.0f);
    gp->x10_flags.b5 = 1;
    gp->gv.mutecity2.xC8 = Ground_801C3FA4(gobj, 6);
    gp->gv.mutecity2.xCC = 0.0f;
    gp->gv.mutecity2.xD0 = 0.0f;
    gp->gv.mutecity2.xC4_flags.b0 = 0;
}

bool grMuteCity_801F0288(Ground_GObj* arg)
{
    return false;
}

/// #grMuteCity_801F0290

void grMuteCity_801F040C(Ground_GObj* arg) {}

void grMuteCity_801F0410(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grMuteCity_801F043C(Ground_GObj* arg)
{
    return false;
}

void grMuteCity_801F0444(Ground_GObj* arg) {}

void grMuteCity_801F0448(Ground_GObj* arg) {}

void grMuteCity_801F044C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grFZeroCar_801CAFBC(gobj, grMc_803E34A4, 0x1C, 0);
    grMuteCity_801F0F4C(gobj);
    gp->gv.mutecity.xC4 = 0;
}

bool grMuteCity_801F04A8(Ground_GObj* arg)
{
    return false;
}

void grMuteCity_801F04B0(Ground_GObj* arg) {}

void grMuteCity_801F04B4(Ground_GObj* arg) {}

/// #grMuteCity_801F04B8

void grMuteCity_801F0948(Ground_GObj* arg) {}

/// #grMuteCity_801F094C

/// #grMuteCity_801F0D20

/// #grMuteCity_801F0F4C

/// #grMuteCity_801F106C

/// #grMuteCity_801F1328

void grMuteCity_801F173C(float arg0)
{
    grMc_8049F4B8.x10 += arg0;
}

void grMuteCity_801F1754(float arg0)
{
    grMc_8049F4B8.x3C += arg0;
}

void grMuteCity_801F176C(float arg0)
{
    grMc_8049F4B8.x68 += arg0;
}

void grMuteCity_801F1784(f32 arg0)
{
    grMc_8049F4B8.x94 += arg0;
}

void grMuteCity_801F179C(f32 arg0)
{
    grMc_8049F4B8.xC0 += arg0;
}

void grMuteCity_801F17B4(f32 arg0)
{
    grMc_8049F4B8.xEC += arg0;
}

void grMuteCity_801F17CC(f32 arg0)
{
    grMc_8049F4B8.x118 += arg0;
}

void grMuteCity_801F17E4(f32 arg0)
{
    grMc_8049F4B8.x144 += arg0;
}

void grMuteCity_801F17FC(f32 arg0)
{
    grMc_8049F4B8.x170 += arg0;
}

void grMuteCity_801F1814(f32 arg0)
{
    grMc_8049F4B8.x19C += arg0;
}

void grMuteCity_801F182C(f32 arg0)
{
    grMc_8049F4B8.x1C8 += arg0;
}

void grMuteCity_801F1844(f32 arg0)
{
    grMc_8049F4B8.x1F4 += arg0;
}

void grMuteCity_801F185C(f32 arg0)
{
    grMc_8049F4B8.x220 += arg0;
}

void grMuteCity_801F1874(f32 arg0)
{
    grMc_8049F4B8.x24C += arg0;
}

void grMuteCity_801F188C(f32 arg0)
{
    grMc_8049F4B8.x278 += arg0;
}

void grMuteCity_801F18A4(f32 arg0)
{
    grMc_8049F4B8.x2A4 += arg0;
}

void grMuteCity_801F18BC(f32 arg0)
{
    grMc_8049F4B8.x2D0 += arg0;
}

void grMuteCity_801F18D4(f32 arg0)
{
    grMc_8049F4B8.x2FC += arg0;
}

void grMuteCity_801F18EC(f32 arg0)
{
    grMc_8049F4B8.x328 += arg0;
}

void grMuteCity_801F1904(f32 arg0)
{
    grMc_8049F4B8.x354 += arg0;
}

void grMuteCity_801F191C(f32 arg0)
{
    grMc_8049F4B8.x380 += arg0;
}

void grMuteCity_801F1934(f32 arg0)
{
    grMc_8049F4B8.x3AC += arg0;
}

void grMuteCity_801F194C(f32 arg0)
{
    grMc_8049F4B8.x3D8 += arg0;
}

void grMuteCity_801F1964(f32 arg0)
{
    grMc_8049F4B8.x404 += arg0;
}

void grMuteCity_801F197C(f32 arg0)
{
    grMc_8049F4B8.x430 += arg0;
}

void grMuteCity_801F1994(f32 arg0)
{
    grMc_8049F4B8.x45C += arg0;
}

void grMuteCity_801F19AC(f32 arg0)
{
    grMc_8049F4B8.x488 += arg0;
}

void grMuteCity_801F19C4(f32 arg0)
{
    grMc_8049F4B8.x4B4 += arg0;
}

void grMuteCity_801F19DC(f32 arg0)
{
    grMc_8049F4B8.x4E0 += arg0;
}

void grMuteCity_801F19F4(f32 arg0)
{
    grMc_8049F4B8.x50C += arg0;
}

void grMuteCity_801F1A0C(void)
{
    Ground_801C53EC(0x5CC60);
}

/// #grMuteCity_801F1A34

DynamicModelDesc* grMuteCity_801F28A8(void)
{
    UnkArchiveStruct* archive = grDatFiles_801C6330(0x26);
    UnkStageDat* dat;
    HSD_ASSERT(2135, archive);
    dat = archive->unk4;
    if (dat != NULL) {
        return (DynamicModelDesc*) ((char*) dat->unk8 + 0x7B8);
    }
    return NULL;
}

/// #grMuteCity_801F290C

/// #grMuteCity_801F2AB0

/// #fn_801F2B58

/// #grMuteCity_801F2BBC

/// #grMuteCity_801F2C10
