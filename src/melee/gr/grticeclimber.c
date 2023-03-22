#include "gr/grticeclimber.h"

#include "cm/camera.h"
#include "ef/efsync.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <dolphin/os/os.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* static */ StageCallbacks lbl_803E8A98[4] = {
    {
        lbl_8022109C,
        lbl_802210C8,
        lbl_802210D0,
        lbl_802210D4,
        0,
    },
    {
        lbl_8022118C,
        lbl_802211DC,
        lbl_802211E4,
        lbl_80221204,
        0,
    },
    {
        lbl_802210D8,
        lbl_8022114C,
        lbl_80221154,
        lbl_80221188,
        (1 << 30) | (1 << 31),
    },
};

StageData lbl_803E8AF4 = {
    47,           lbl_803E8A98, "/GrTIc.dat", lbl_80220F14, func_80220F10,
    lbl_80220F84, lbl_80220F88, lbl_80220FAC, lbl_80221354, lbl_8022135C,
    (1 << 0),
};

void func_80220F10(bool arg0) {}

void lbl_80220F14(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    func_80220FB4(0);
    func_80220FB4(1);
    func_80220FB4(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void lbl_80220F84(void) {}

void lbl_80220F88(void)
{
    grZakoGenerator_801CAE04(0);
}

bool lbl_80220FAC(void)
{
    return false;
}

HSD_GObj* func_80220FB4(int id)
{
    /// @todo Cannot be moved below @c cb due to an inline
    HSD_GObj* gobj;

    StageCallbacks* cb = &lbl_803E8A98[id];
    gobj = Ground_801C14D0(id);

    if (gobj != NULL) {
        Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (cb->callback3 != NULL)
            gp->x1C_callback = cb->callback3;

        if (cb->callback0 != NULL)
            cb->callback0(gobj);

        if (cb->callback2 != NULL)
            func_8038FD54(gobj, cb->callback2, 4);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grticeclimber.c", 202,
                 id);
    }

    return gobj;
}

void lbl_8022109C(HSD_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool lbl_802210C8(HSD_GObj* arg0)
{
    return false;
}

void lbl_802210D0(HSD_GObj* arg0) {}

void lbl_802210D4(HSD_GObj* arg0) {}

void lbl_802210D8(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
    grAnime_801C7FF8(gobj, 69, 2, 1, 0.0F, 1.0F);
    func_80221288(gobj);
}

bool lbl_8022114C(HSD_GObj* arg0)
{
    return false;
}

void lbl_80221154(HSD_GObj* arg0)
{
    func_800115F4();
    Ground_801C2FE0(arg0);
}

void lbl_80221188(HSD_GObj* arg0) {}

void lbl_8022118C(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool lbl_802211DC(HSD_GObj* arg0)
{
    return false;
}

void lbl_802211E4(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void lbl_80221204(HSD_GObj* arg0) {}

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_80221208(void){
    // clang-format off
    nofralloc
/* 80221208 0021DDE8  7C 08 02 A6 */	mflr r0
/* 8022120C 0021DDEC  38 80 00 10 */	li r4, 0x10
/* 80221210 0021DDF0  90 01 00 04 */	stw r0, 4(r1)
/* 80221214 0021DDF4  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80221218 0021DDF8  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8022121C 0021DDFC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 80221220 0021DE00  7C 7E 1B 78 */	mr r30, r3
/* 80221224 0021DE04  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80221228 0021DE08  80 7F 0D D8 */	lwz r3, 0xdd8(r31)
/* 8022122C 0021DE0C  48 15 0B 71 */	bl HSD_JObjSetFlagsAll
/* 80221230 0021DE10  80 7F 0D D8 */	lwz r3, 0xdd8(r31)
/* 80221234 0021DE14  38 A1 00 20 */	addi r5, r1, 0x20
/* 80221238 0021DE18  38 80 00 00 */	li r4, 0
/* 8022123C 0021DE1C  4B DE 9F 91 */	bl func_8000B1CC
/* 80221240 0021DE20  38 9E 00 00 */	addi r4, r30, 0
/* 80221244 0021DE24  4C C6 31 82 */	crclr 6
/* 80221248 0021DE28  38 A1 00 20 */	addi r5, r1, 0x20
/* 8022124C 0021DE2C  38 60 04 45 */	li r3, 0x445
/* 80221250 0021DE30  4B E3 EB 8D */	bl ef_Spawn
/* 80221254 0021DE34  38 60 00 02 */	li r3, 2
/* 80221258 0021DE38  38 80 00 00 */	li r4, 0
/* 8022125C 0021DE3C  4B E0 FB E9 */	bl func_80030E44
/* 80221260 0021DE40  38 60 01 36 */	li r3, 0x136
/* 80221264 0021DE44  4B FA 41 89 */	bl Ground_801C53EC
/* 80221268 0021DE48  7F C3 F3 78 */	mr r3, r30
/* 8022126C 0021DE4C  4B FA 7A 71 */	bl grMaterial_801C8CDC
/* 80221270 0021DE50  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80221274 0021DE54  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80221278 0021DE58  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8022127C 0021DE5C  38 21 00 38 */	addi r1, r1, 0x38
/* 80221280 0021DE60  7C 08 03 A6 */	mtlr r0
/* 80221284 0021DE64  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

s16 lbl_803E8B5C[] = {
    0,  1,  2,  3,  4,  5,  6,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, 0,
};

void func_80221288(HSD_GObj* ground_gobj)
{
    Ground* gp = GET_GROUND(ground_gobj);
    int i;

    for (i = 0; lbl_803E8B5C[i] != -1; i++) {
        enum_t result_0 = Ground_801C33C0(2, lbl_803E8B5C[i]);
        if (result_0 != -1) {
            bool result_1 = grMaterial_801C8CFC(
                0, 0, gp, Ground_801C3FA4(ground_gobj, result_0), 0,
                lbl_80221208, 0);

            if (result_1) {
                grMaterial_801C8DE0(result_1, -1.0F, 0.0F, 0.0F, 1.0F, 0.0F,
                                    0.0F, 4.0F);
                grMaterial_801C8E08(result_1);
            }
        }
    }
}

bool lbl_80221354(int arg0)
{
    return false;
}

bool lbl_8022135C(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
