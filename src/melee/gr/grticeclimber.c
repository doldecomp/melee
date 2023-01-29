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

s16 lbl_803E8B5C[] = {
    0,  1,  2,  3,  4,  5,  6,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, 0,
};

extern f32 const lbl_804DBCC0;
extern f32 const lbl_804DBCC4;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80221288(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 80221288 0021DE68  7C 08 02 A6 */	mflr r0
/* 8022128C 0021DE6C  3C 80 80 3F */	lis r4, lbl_803E8B5C@ha
/* 80221290 0021DE70  90 01 00 04 */	stw r0, 4(r1)
/* 80221294 0021DE74  38 00 00 00 */	li r0, 0
/* 80221298 0021DE78  54 05 08 3C */	slwi r5, r0, 1
/* 8022129C 0021DE7C  94 21 FF D8 */	stwu r1, -40(r1)
/* 802212A0 0021DE80  38 04 8B 5C */	addi r0, r4, lbl_803E8B5C@l
/* 802212A4 0021DE84  BF 61 00 14 */	stmw r27, 20(r1)
/* 802212A8 0021DE88  3B 63 00 00 */	addi r27, r3, 0
/* 802212AC 0021DE8C  3C 60 80 22 */	lis r3, lbl_80221208@ha
/* 802212B0 0021DE90  7F C0 2A 14 */	add r30, r0, r5
/* 802212B4 0021DE94  3B E3 12 08 */	addi r31, r3, lbl_80221208@l
/* 802212B8 0021DE98  83 BB 00 2C */	lwz r29, 44(r27)
/* 802212BC 0021DE9C  48 00 00 78 */	b lbl_80221334
lbl_802212C0:
/* 802212C0 0021DEA0  38 60 00 02 */	li r3, 2
/* 802212C4 0021DEA4  4B FA 20 FD */	bl func_801C33C0
/* 802212C8 0021DEA8  38 83 00 00 */	addi r4, r3, 0
/* 802212CC 0021DEAC  2C 04 FF FF */	cmpwi r4, -1
/* 802212D0 0021DEB0  41 82 00 60 */	beq lbl_80221330
/* 802212D4 0021DEB4  7F 63 DB 78 */	mr r3, r27
/* 802212D8 0021DEB8  4B FA 2C CD */	bl func_801C3FA4
/* 802212DC 0021DEBC  38 C3 00 00 */	addi r6, r3, 0
/* 802212E0 0021DEC0  38 BD 00 00 */	addi r5, r29, 0
/* 802212E4 0021DEC4  39 1F 00 00 */	addi r8, r31, 0
/* 802212E8 0021DEC8  38 60 00 00 */	li r3, 0
/* 802212EC 0021DECC  38 80 00 00 */	li r4, 0
/* 802212F0 0021DED0  38 E0 00 00 */	li r7, 0
/* 802212F4 0021DED4  39 20 00 00 */	li r9, 0
/* 802212F8 0021DED8  4B FA 7A 05 */	bl func_801C8CFC
/* 802212FC 0021DEDC  7C 7C 1B 79 */	or. r28, r3, r3
/* 80221300 0021DEE0  41 82 00 30 */	beq lbl_80221330
/* 80221304 0021DEE4  C0 42 C2 D8 */	lfs f2, lbl_804DBCB8(r2)
/* 80221308 0021DEE8  7F 83 E3 78 */	mr r3, r28
/* 8022130C 0021DEEC  C0 22 C2 E0 */	lfs f1, lbl_804DBCC0(r2)
/* 80221310 0021DEF0  FC 60 10 90 */	fmr f3, f2
/* 80221314 0021DEF4  C0 82 C2 DC */	lfs f4, lbl_804DBCBC(r2)
/* 80221318 0021DEF8  FC A0 10 90 */	fmr f5, f2
/* 8022131C 0021DEFC  C0 E2 C2 E4 */	lfs f7, lbl_804DBCC4(r2)
/* 80221320 0021DF00  FC C0 10 90 */	fmr f6, f2
/* 80221324 0021DF04  4B FA 7A BD */	bl func_801C8DE0
/* 80221328 0021DF08  7F 83 E3 78 */	mr r3, r28
/* 8022132C 0021DF0C  4B FA 7A DD */	bl func_801C8E08
lbl_80221330:
/* 80221330 0021DF10  3B DE 00 02 */	addi r30, r30, 2
lbl_80221334:
/* 80221334 0021DF14  A8 9E 00 00 */	lha r4, 0(r30)
/* 80221338 0021DF18  2C 04 FF FF */	cmpwi r4, -1
/* 8022133C 0021DF1C  40 82 FF 84 */	bne lbl_802212C0
/* 80221340 0021DF20  BB 61 00 14 */	lmw r27, 20(r1)
/* 80221344 0021DF24  80 01 00 2C */	lwz r0, 44(r1)
/* 80221348 0021DF28  38 21 00 28 */	addi r1, r1, 40
/* 8022134C 0021DF2C  7C 08 03 A6 */	mtlr r0
/* 80221350 0021DF30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void func_80221288(HSD_GObj* ground_gobj)
{
    s16* cur = lbl_803E8B5C;
    Ground* gp = GET_GROUND(ground_gobj->user_data);
    s16 val = *cur;

    while (val != -1) {
        enum_t result_0 = func_801C33C0(2, val);
        if (result_0 != -1) {
            bool result_1 =
                func_801C8CFC(0, 0, gp, func_801C3FA4(ground_gobj, result_0), 0,
                              lbl_80221208, 0);

            if (result_1) {
                func_801C8DE0(result_1, lbl_804DBCC0, lbl_804DBCB8,
                              lbl_804DBCB8, lbl_804DBCBC, lbl_804DBCB8,
                              lbl_804DBCB8, lbl_804DBCC4);
                func_801C8E08(result_1);
            }
        }

        val = *cur;
        cur += 1;
    }
}

#endif

bool lbl_80221354(int arg0)
{
    return false;
}

bool lbl_8022135C(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
