#include "gr/forward.h"
#include "lb/forward.h"

#include "grtmewtwo.h"

#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobjgxlink.h>

typedef struct grTMewtwo_UnkStruct {
    UNK_T x0;
} grTMewtwo_UnkStruct;

/* 2221D8 */ static void grTMewtwo_802221D8(int arg0);
/* 2221DC */ static void grTMewtwo_802221DC(void);
/* 222254 */ static void grTMewtwo_80222254(void);
/* 222258 */ static void grTMewtwo_80222258(void);
/* 22227C */ static bool grTMewtwo_8022227C(void);
/* 222284 */ static Ground_GObj* grTMewtwo_80222284(int index);
/* 22236C */ static void grTMewtwo_8022236C(Ground_GObj* gobj);
/* 222398 */ static bool grTMewtwo_80222398(Ground_GObj* gobj);
/* 2223A0 */ static void grTMewtwo_802223A0(Ground_GObj* gobj);
/* 2223A4 */ static void grTMewtwo_802223A4(Ground_GObj* gobj);
/* 2223A8 */ static void grTMewtwo_802223A8(Ground_GObj* gobj);
/* 2223F8 */ static bool grTMewtwo_802223F8(Ground_GObj* gobj);
/* 222400 */ static void grTMewtwo_80222400(Ground_GObj* gobj);
/* 222434 */ static void grTMewtwo_80222434(Ground_GObj* gobj);
/* 222438 */ static void grTMewtwo_80222438(Ground_GObj* gobj);
/* 222488 */ static bool grTMewtwo_80222488(Ground_GObj* gobj);
/* 222490 */ static void grTMewtwo_80222490(Ground_GObj* gobj);
/* 2224B0 */ static void grTMewtwo_802224B0(Ground_GObj* gobj);
/* 2224B4 */ static lb_UnkAnimStruct* grTMewtwo_802224B4(int arg0);
/* 2225C8 */ static bool grTMewtwo_802225C8(Vec3* arg0, int arg1,
                                            HSD_JObj* arg2);
/* 3E8FC0 */ static void grTMewtwo_803E8FC0(Ground_GObj* gobj);
/* 4D6B08 */ static grTMewtwo_UnkStruct* grTMewtwo_804D6B08;

static StageCallbacks grTMewtwo_803E8F70[4] = {
    {
        grTMewtwo_8022236C,
        grTMewtwo_80222398,
        grTMewtwo_802223A0,
        grTMewtwo_802223A4,
        0,
    },
    {
        grTMewtwo_80222438,
        grTMewtwo_80222488,
        grTMewtwo_80222490,
        grTMewtwo_802224B0,
        0,
    },
    {
        grTMewtwo_802223A8,
        grTMewtwo_802223F8,
        grTMewtwo_80222400,
        grTMewtwo_80222434,
        (1 << 30) | (1 << 31),
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
};

StageData grTMewtwo_803E8FCC = {
    (1 << 0) | (1 << 2) | (1 << 4) | (1 << 5),
    grTMewtwo_803E8F70,
    "/GrTMt.dat",
    grTMewtwo_802221DC,
    grTMewtwo_802221D8,
    grTMewtwo_80222254,
    grTMewtwo_80222258,
    grTMewtwo_8022227C,
    grTMewtwo_802224B4,
    grTMewtwo_802225C8,
    (1 << 0),
    NULL,
};

void grTMewtwo_802221D8(int arg0) {}

void grTMewtwo_802221DC(void)
{
    grTMewtwo_804D6B08 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grTMewtwo_80222284(0);
    grTMewtwo_80222284(1);
    grTMewtwo_80222284(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTMewtwo_80222254(void) {}

void grTMewtwo_80222258(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTMewtwo_8022227C(void)
{
    return false;
}

Ground_GObj* grTMewtwo_80222284(int index)
{
    /// @todo Can't move below @c callbacks.
    HSD_GObj* gobj;

    StageCallbacks* callbacks = &grTMewtwo_803E8F70[index];
    gobj = Ground_801C14D0(index);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }

        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtmewtwo.c", 201,
                 index);
    }
    return gobj;
}

void grTMewtwo_8022236C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

ASM bool grTMewtwo_80222398(Ground_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 80222398 0021EF78  38 60 00 00 */	li r3, 0
/* 8022239C 0021EF7C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void grTMewtwo_802223A0(Ground_GObj* gobj) {}

void grTMewtwo_802223A4(Ground_GObj* gobj) {}

void grTMewtwo_802223A8(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

ASM bool grTMewtwo_802223F8(Ground_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 802223F8 0021EFD8  38 60 00 00 */	li r3, 0
/* 802223FC 0021EFDC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void grTMewtwo_80222400(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTMewtwo_80222434(Ground_GObj* gobj) {}

void grTMewtwo_80222438(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

ASM bool grTMewtwo_80222488(Ground_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 80222488 0021F068  38 60 00 00 */	li r3, 0
/* 8022248C 0021F06C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void grTMewtwo_80222490(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTMewtwo_802224B0(Ground_GObj* gobj) {}

ASM lb_UnkAnimStruct* grTMewtwo_802224B4(int arg0)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 802224B4 0021F094  7C 08 02 A6 */	mflr r0
/* 802224B8 0021F098  90 01 00 04 */	stw r0, 4(r1)
/* 802224BC 0021F09C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802224C0 0021F0A0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802224C4 0021F0A4  3B E3 00 00 */	addi r31, r3, 0
/* 802224C8 0021F0A8  2C 1F FF FF */	cmpwi r31, -1
/* 802224CC 0021F0AC  41 82 00 E4 */	beq lbl_802225B0
/* 802224D0 0021F0B0  7F E3 FB 78 */	mr r3, r31
/* 802224D4 0021F0B4  4B E3 46 99 */	bl mpLib_80056B6C
/* 802224D8 0021F0B8  2C 03 FF FF */	cmpwi r3, -1
/* 802224DC 0021F0BC  41 82 00 D4 */	beq lbl_802225B0
/* 802224E0 0021F0C0  2C 03 00 00 */	cmpwi r3, 0
/* 802224E4 0021F0C4  40 82 00 64 */	bne lbl_80222548
/* 802224E8 0021F0C8  7F E3 FB 78 */	mr r3, r31
/* 802224EC 0021F0CC  4B E3 27 81 */	bl mpLib_80054C6C
/* 802224F0 0021F0D0  2C 03 00 01 */	cmpwi r3, 1
/* 802224F4 0021F0D4  40 82 00 10 */	bne lbl_80222504
/* 802224F8 0021F0D8  80 6D B4 68 */	lwz r3, grTMewtwo_804D6B08
/* 802224FC 0021F0DC  80 63 00 00 */	lwz r3, 0(r3)
/* 80222500 0021F0E0  48 00 00 B4 */	b lbl_802225B4
lbl_80222504:
/* 80222504 0021F0E4  2C 03 00 02 */	cmpwi r3, 2
/* 80222508 0021F0E8  40 82 00 10 */	bne lbl_80222518
/* 8022250C 0021F0EC  80 6D B4 68 */	lwz r3, grTMewtwo_804D6B08
/* 80222510 0021F0F0  80 63 00 04 */	lwz r3, 4(r3)
/* 80222514 0021F0F4  48 00 00 A0 */	b lbl_802225B4
lbl_80222518:
/* 80222518 0021F0F8  2C 03 00 04 */	cmpwi r3, 4
/* 8022251C 0021F0FC  40 82 00 10 */	bne lbl_8022252C
/* 80222520 0021F100  80 6D B4 68 */	lwz r3, grTMewtwo_804D6B08
/* 80222524 0021F104  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80222528 0021F108  48 00 00 8C */	b lbl_802225B4
lbl_8022252C:
/* 8022252C 0021F10C  2C 03 00 08 */	cmpwi r3, 8
/* 80222530 0021F110  40 82 00 10 */	bne lbl_80222540
/* 80222534 0021F114  80 6D B4 68 */	lwz r3, grTMewtwo_804D6B08
/* 80222538 0021F118  80 63 00 08 */	lwz r3, 8(r3)
/* 8022253C 0021F11C  48 00 00 78 */	b lbl_802225B4
lbl_80222540:
/* 80222540 0021F120  38 60 00 00 */	li r3, 0
/* 80222544 0021F124  48 00 00 70 */	b lbl_802225B4
lbl_80222548:
/* 80222548 0021F128  2C 03 00 01 */	cmpwi r3, 1
/* 8022254C 0021F12C  40 82 00 64 */	bne lbl_802225B0
/* 80222550 0021F130  7F E3 FB 78 */	mr r3, r31
/* 80222554 0021F134  4B E3 27 19 */	bl mpLib_80054C6C
/* 80222558 0021F138  2C 03 00 01 */	cmpwi r3, 1
/* 8022255C 0021F13C  40 82 00 10 */	bne lbl_8022256C
/* 80222560 0021F140  80 6D B4 68 */	lwz r3, grTMewtwo_804D6B08
/* 80222564 0021F144  80 63 00 10 */	lwz r3, 0x10(r3)
/* 80222568 0021F148  48 00 00 4C */	b lbl_802225B4
lbl_8022256C:
/* 8022256C 0021F14C  2C 03 00 02 */	cmpwi r3, 2
/* 80222570 0021F150  40 82 00 10 */	bne lbl_80222580
/* 80222574 0021F154  80 6D B4 68 */	lwz r3, grTMewtwo_804D6B08
/* 80222578 0021F158  80 63 00 14 */	lwz r3, 0x14(r3)
/* 8022257C 0021F15C  48 00 00 38 */	b lbl_802225B4
lbl_80222580:
/* 80222580 0021F160  2C 03 00 04 */	cmpwi r3, 4
/* 80222584 0021F164  40 82 00 10 */	bne lbl_80222594
/* 80222588 0021F168  80 6D B4 68 */	lwz r3, grTMewtwo_804D6B08
/* 8022258C 0021F16C  80 63 00 1C */	lwz r3, 0x1c(r3)
/* 80222590 0021F170  48 00 00 24 */	b lbl_802225B4
lbl_80222594:
/* 80222594 0021F174  2C 03 00 08 */	cmpwi r3, 8
/* 80222598 0021F178  40 82 00 10 */	bne lbl_802225A8
/* 8022259C 0021F17C  80 6D B4 68 */	lwz r3, grTMewtwo_804D6B08
/* 802225A0 0021F180  80 63 00 18 */	lwz r3, 0x18(r3)
/* 802225A4 0021F184  48 00 00 10 */	b lbl_802225B4
lbl_802225A8:
/* 802225A8 0021F188  38 60 00 00 */	li r3, 0
/* 802225AC 0021F18C  48 00 00 08 */	b lbl_802225B4
lbl_802225B0:
/* 802225B0 0021F190  38 60 00 00 */	li r3, 0
lbl_802225B4:
/* 802225B4 0021F194  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802225B8 0021F198  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802225BC 0021F19C  38 21 00 18 */	addi r1, r1, 0x18
/* 802225C0 0021F1A0  7C 08 03 A6 */	mtlr r0
/* 802225C4 0021F1A4  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM bool grTMewtwo_802225C8(Vec3* arg0, int arg1, HSD_JObj* arg2)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 802225C8 0021F1A8  38 60 00 01 */	li r3, 1
/* 802225CC 0021F1AC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
