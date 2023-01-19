#include <melee/gr/grticeclimber.h>

#include <dolphin/os/os.h>
#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/grmaterial.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/types.h>
#include <melee/lb/lbunknown_001.h>
#include <melee/lb/lbunknown_003.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjproc.h>

/* static */ StageCallbacks lbl_803E8A98[4] = {
    {
        lbl_8022109C,
        lbl_802210C8,
        lbl_802210D0,
        lbl_802210D4,
        FLAGS_ZERO,
    },
    {
        lbl_8022118C,
        lbl_802211DC,
        lbl_802211E4,
        lbl_80221204,
        FLAGS_ZERO,
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
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

void lbl_80220F84(void) {}

void lbl_80220F88(void)
{
    func_801CAE04(0);
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
    gobj = func_801C14D0(id);

    if (gobj != NULL) {
        Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);

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
    func_801C8138(gobj, gp->map_id, 0);
}

bool lbl_802210C8(HSD_GObj* arg0)
{
    return false;
}

void lbl_802210D0(HSD_GObj* arg0) {}

void lbl_802210D4(HSD_GObj* arg0) {}

extern f32 const lbl_804DBCB8;
extern f32 const lbl_804DBCBC;

void lbl_802210D8(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
    func_801C7FF8(gobj, 69, 2, 1, lbl_804DBCB8, lbl_804DBCBC);
    func_80221288(gobj);
}

bool lbl_8022114C(HSD_GObj* arg0)
{
    return false;
}

void lbl_80221154(HSD_GObj* arg0)
{
    func_800115F4();
    func_801C2FE0(arg0);
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
    func_801C2FE0(gobj);
}

void lbl_80221204(HSD_GObj* arg0) {}

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_80221208(void)
{ // clang-format off
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
/* 80221264 0021DE44  4B FA 41 89 */	bl func_801C53EC
/* 80221268 0021DE48  7F C3 F3 78 */	mr r3, r30
/* 8022126C 0021DE4C  4B FA 7A 71 */	bl func_801C8CDC
/* 80221270 0021DE50  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80221274 0021DE54  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80221278 0021DE58  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8022127C 0021DE5C  38 21 00 38 */	addi r1, r1, 0x38
/* 80221280 0021DE60  7C 08 03 A6 */	mtlr r0
/* 80221284 0021DE64  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

/// @todo Unknown struct
u32 lbl_803E8B5C[] = {
    0x00000001, 0x00020003, 0x00040005, 0x00060008, 0x0009000A, 0x000B000C,
    0x000D000E, 0x000F0010, 0x00110012, 0x00130014, 0x00150016, 0x002C002D,
    0x002E002F, 0x00300031, 0x00320033, 0x00340035, 0x00360037, 0x00380039,
    0x003A003B, 0x003C003D, 0xFFFF0000,
};

extern f32 const lbl_804DBCC0;
extern f32 const lbl_804DBCC4;
