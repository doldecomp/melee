#include <melee/ft/ftparts.h>

#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GX_unknown_001.h>
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftdata.h>
#include <melee/lb/lbrefract.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/perf.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/util.h>
#include <dolphin/os/os.h>

#define MAX_FT_PARTS 140

#define JOBJ_NEXT(jobj) ((jobj) == NULL ? NULL : (jobj)->next)
#define JOBJ_PARENT(jobj) ((jobj) == NULL ? NULL : (jobj)->parent)
#define JOBJ_CHILD(jobj) ((jobj) == NULL ? NULL : (jobj)->child)

extern HSD_GObj* lbl_804D7814;
extern HSD_PerfStat HSD_PerfCurrentStat;
extern HSD_MObjInfo ftMObj;
BOOL hsdIsDescendantOf(HSD_ClassInfo* info, HSD_ClassInfo* p);

unk_t func_80074ACC();
u32 func_8007506C(s32 ftkind, u32 part);

void Fighter_JObjInfoInit(void);
void Fighter_IntpJObjInfoInit(void);
void Fighter_PObjInfoInit(void);

HSD_JObjInfo ftJObj = { Fighter_JObjInfoInit };
HSD_JObjInfo ftIntpJObj = { Fighter_IntpJObjInfoInit };
HSD_PObjInfo ftPObj = { Fighter_PObjInfoInit };

// .data
static char lbl_803C09E0[] = "fighter_class_library";
static char lbl_803C09F8[] = "ft_intp_jobj";
static char lbl_803C0A08[] = "ftparts.c";
static char lbl_803C0A14[] = "envelope";
static char lbl_803C0A20[] = "envelope->jobj";
static char lbl_803C0A30[] = "jp->envelopemtx";
static char lbl_803C0A40[] = "fighter parts model dobj num over! player %d\n";
static char lbl_803C0A70[] = "fighter dobj num over! player %d\n";
static char lbl_803C0A94[] = "fighter parts num over! player %d\n";
static char lbl_803C0AB8[] = "fighter parts num not match! player %d\n";
static char lbl_803C0AE0[] = "fighter parts model num over!\n";
static char lbl_803C0B00[] = "can't find tobj!\n";
static char lbl_803C0B14[] = "fighter parts model dobj num over!\n";
static char lbl_803C0B38[] = "cant set fighter rot x!\n";
static char lbl_803C0B54[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static char lbl_803C0B7C[] = "cant set fighter rot y!\n";
static char lbl_803C0B98[] = "cant set fighter rot z!\n";
static char lbl_803C0BB4[] = "cant get fighter rot x!\n";
static char lbl_803C0BD0[] = "cant get fighter rot y!\n";
static char lbl_803C0BEC[] = "cant get fighter rot z!\n";

// .bss
struct {
    Mtx mtx;
    u8 has_z_scale : 1;
    char unk_31[7];
} ft_jobj_scale;

// .sdata
static char lbl_804D3A30[] = "jobj.h";
static char lbl_804D3A38[] = "jobj";
static char lbl_804D3A40[] = "ft_jobj";
static char lbl_804D3A48[] = "jp->mtx";
static char lbl_804D3A50[] = "ft_pobj";
static char lbl_804D3A58[] = "0";
static char lbl_804D3A5C[] = "rotate";

/// @todo Remove when strings can be reused
static inline f32 _HSD_JObjGetScaleX(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0) : __assert(lbl_804D3A30, 875, lbl_804D3A38));
    return jobj->scale.x;
}

/// @todo Remove when strings can be reused
static inline f32 _HSD_JObjGetScaleY(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0) : __assert(lbl_804D3A30, 888, lbl_804D3A38));
    return jobj->scale.y;
}

/// @todo Remove when strings can be reused
static inline f32 _HSD_JObjGetScaleZ(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0) : __assert(lbl_804D3A30, 901, lbl_804D3A38));
    return jobj->scale.z;
}

void Fighter_JObjMakePositionMtx(HSD_JObj* jobj, Mtx mtx, Mtx rmtx)
{
    Fighter* fighter = (Fighter*) lbl_804D7814->user_data;

    hsdJObj.make_pmtx(jobj, mtx, rmtx);

    if (fighter->x34_scale.z != 1.0F) {
        Mtx temp_mtx;
        f32 scale_z = _HSD_JObjGetScaleZ(jobj);
        f32 scale_y = _HSD_JObjGetScaleY(jobj);
        f32 scale_x = _HSD_JObjGetScaleX(jobj);
        PSMTXScale(temp_mtx, 1.0F / scale_x, 1.0F / scale_y, 1.0F / scale_z);
        PSMTXConcat(rmtx, temp_mtx, ft_jobj_scale.mtx);
        HSD_MtxInverse(rmtx, temp_mtx);
        PSMTXConcat(ft_jobj_scale.mtx, temp_mtx, ft_jobj_scale.mtx);
        ft_jobj_scale.has_z_scale = TRUE;
    } else {
        ft_jobj_scale.has_z_scale = FALSE;
    }
}

void Fighter_JObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftJObj), HSD_CLASS_INFO(&hsdJObj),
                     lbl_803C09E0, lbl_804D3A40, sizeof(HSD_JObjInfo),
                     sizeof(HSD_JObj));
    HSD_JOBJ_INFO(&ftJObj)->make_pmtx = Fighter_JObjMakePositionMtx;
}

#pragma push
asm void func_80073758()
{ // clang-format off
    nofralloc
/* 80073758 00070338  7C 08 02 A6 */	mflr r0
/* 8007375C 0007033C  3C 80 80 3C */	lis r4, ftJObj@ha
/* 80073760 00070340  90 01 00 04 */	stw r0, 4(r1)
/* 80073764 00070344  38 84 08 F8 */	addi r4, r4, ftJObj@l
/* 80073768 00070348  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007376C 0007034C  48 30 EC 95 */	bl hsdChangeClass
/* 80073770 00070350  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80073774 00070354  38 21 00 08 */	addi r1, r1, 8
/* 80073778 00070358  7C 08 03 A6 */	mtlr r0
/* 8007377C 0007035C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm s32 Fighter_IntpJObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent)
{ // clang-format off
    nofralloc
/* 80073780 00070360  7C 08 02 A6 */	mflr r0
/* 80073784 00070364  90 01 00 04 */	stw r0, 4(r1)
/* 80073788 00070368  38 00 00 00 */	li r0, 0
/* 8007378C 0007036C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80073790 00070370  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80073794 00070374  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80073798 00070378  7C 9E 23 78 */	mr r30, r4
/* 8007379C 0007037C  83 E4 00 10 */	lwz r31, 0x10(r4)
/* 800737A0 00070380  3C 80 80 40 */	lis r4, hsdJObj@ha
/* 800737A4 00070384  38 84 67 08 */	addi r4, r4, hsdJObj@l
/* 800737A8 00070388  90 1E 00 10 */	stw r0, 0x10(r30)
/* 800737AC 0007038C  81 84 00 3C */	lwz r12, 0x3c(r4)
/* 800737B0 00070390  38 9E 00 00 */	addi r4, r30, 0
/* 800737B4 00070394  7D 88 03 A6 */	mtlr r12
/* 800737B8 00070398  4E 80 00 21 */	blrl
/* 800737BC 0007039C  93 FE 00 10 */	stw r31, 0x10(r30)
/* 800737C0 000703A0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800737C4 000703A4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800737C8 000703A8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800737CC 000703AC  38 21 00 20 */	addi r1, r1, 0x20
/* 800737D0 000703B0  7C 08 03 A6 */	mtlr r0
/* 800737D4 000703B4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

void Fighter_IntpJObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftIntpJObj), HSD_CLASS_INFO(&hsdJObj),
                     lbl_803C09E0, lbl_803C09F8, sizeof(HSD_JObjInfo),
                     sizeof(HSD_JObj));
    HSD_JOBJ_INFO(&ftIntpJObj)->load = Fighter_IntpJObjLoad;
}

#pragma push
asm unk_t func_80073830()
{ // clang-format off
    nofralloc
/* 80073830 00070410  7C 08 02 A6 */	mflr r0
/* 80073834 00070414  90 01 00 04 */	stw r0, 4(r1)
/* 80073838 00070418  94 21 FF 68 */	stwu r1, -0x98(r1)
/* 8007383C 0007041C  93 E1 00 94 */	stw r31, 0x94(r1)
/* 80073840 00070420  93 C1 00 90 */	stw r30, 0x90(r1)
/* 80073844 00070424  93 A1 00 8C */	stw r29, 0x8c(r1)
/* 80073848 00070428  3B A5 00 00 */	addi r29, r5, 0
/* 8007384C 0007042C  93 81 00 88 */	stw r28, 0x88(r1)
/* 80073850 00070430  3B 86 00 00 */	addi r28, r6, 0
/* 80073854 00070434  48 2F EA C1 */	bl HSD_JObjGetCurrent
/* 80073858 00070438  3B C3 00 00 */	addi r30, r3, 0
/* 8007385C 0007043C  38 81 00 50 */	addi r4, r1, 0x50
/* 80073860 00070440  38 A1 00 4C */	addi r5, r1, 0x4c
/* 80073864 00070444  38 60 00 00 */	li r3, 0
/* 80073868 00070448  48 2F A8 19 */	bl HSD_PObjGetMtxMark
/* 8007386C 0007044C  80 01 00 50 */	lwz r0, 0x50(r1)
/* 80073870 00070450  7C 00 F0 40 */	cmplw r0, r30
/* 80073874 00070454  40 82 00 10 */	bne lbl_80073884
/* 80073878 00070458  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8007387C 0007045C  28 00 00 01 */	cmplwi r0, 1
/* 80073880 00070460  41 82 01 18 */	beq lbl_80073998
lbl_80073884:
/* 80073884 00070464  38 9E 00 00 */	addi r4, r30, 0
/* 80073888 00070468  38 60 00 00 */	li r3, 0
/* 8007388C 0007046C  38 A0 00 01 */	li r5, 1
/* 80073890 00070470  48 2F A7 BD */	bl HSD_PObjSetMtxMark
/* 80073894 00070474  38 60 00 00 */	li r3, 0
/* 80073898 00070478  48 2C DC 79 */	bl GXSetCurrentMtx
/* 8007389C 0007047C  38 7D 00 00 */	addi r3, r29, 0
/* 800738A0 00070480  38 80 00 00 */	li r4, 0
/* 800738A4 00070484  48 2C DB F1 */	bl GXLoadPosMtxImm
/* 800738A8 00070488  3C 60 80 40 */	lis r3, HSD_PerfCurrentStat@ha
/* 800738AC 0007048C  38 63 72 18 */	addi r3, r3, HSD_PerfCurrentStat@l
/* 800738B0 00070490  3B E3 00 0C */	addi r31, r3, 0xc
/* 800738B4 00070494  80 63 00 0C */	lwz r3, 0xc(r3)
/* 800738B8 00070498  57 80 01 4B */	rlwinm. r0, r28, 0, 5, 5
/* 800738BC 0007049C  38 03 00 01 */	addi r0, r3, 1
/* 800738C0 000704A0  3B 80 00 00 */	li r28, 0
/* 800738C4 000704A4  90 1F 00 00 */	stw r0, 0(r31)
/* 800738C8 000704A8  40 82 00 44 */	bne lbl_8007390C
/* 800738CC 000704AC  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 800738D0 000704B0  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 800738D4 000704B4  41 82 00 08 */	beq lbl_800738DC
/* 800738D8 000704B8  63 9C 00 01 */	ori r28, r28, 1
lbl_800738DC:
/* 800738DC 000704BC  38 60 00 00 */	li r3, 0
/* 800738E0 000704C0  38 80 00 01 */	li r4, 1
/* 800738E4 000704C4  48 2E B5 85 */	bl _HSD_TObjGetCurrentByType
/* 800738E8 000704C8  28 03 00 00 */	cmplwi r3, 0
/* 800738EC 000704CC  41 82 00 08 */	beq lbl_800738F4
/* 800738F0 000704D0  63 9C 00 03 */	ori r28, r28, 3
lbl_800738F4:
/* 800738F4 000704D4  38 60 00 00 */	li r3, 0
/* 800738F8 000704D8  38 80 00 02 */	li r4, 2
/* 800738FC 000704DC  48 2E B5 6D */	bl _HSD_TObjGetCurrentByType
/* 80073900 000704E0  28 03 00 00 */	cmplwi r3, 0
/* 80073904 000704E4  41 82 00 08 */	beq lbl_8007390C
/* 80073908 000704E8  63 9C 00 05 */	ori r28, r28, 5
lbl_8007390C:
/* 8007390C 000704EC  57 80 07 FF */	clrlwi. r0, r28, 0x1f
/* 80073910 000704F0  41 82 00 88 */	beq lbl_80073998
/* 80073914 000704F4  3C 60 80 46 */	lis r3, ft_jobj_scale@ha
/* 80073918 000704F8  38 63 92 40 */	addi r3, r3, ft_jobj_scale@l
/* 8007391C 000704FC  88 03 00 30 */	lbz r0, 0x30(r3)
/* 80073920 00070500  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80073924 00070504  41 82 00 20 */	beq lbl_80073944
/* 80073928 00070508  38 9D 00 00 */	addi r4, r29, 0
/* 8007392C 0007050C  38 A1 00 18 */	addi r5, r1, 0x18
/* 80073930 00070510  48 2C E8 D5 */	bl PSMTXConcat
/* 80073934 00070514  38 61 00 18 */	addi r3, r1, 0x18
/* 80073938 00070518  38 81 00 54 */	addi r4, r1, 0x54
/* 8007393C 0007051C  48 30 60 E5 */	bl HSD_MtxInverseTranspose
/* 80073940 00070520  48 00 00 10 */	b lbl_80073950
lbl_80073944:
/* 80073944 00070524  38 7D 00 00 */	addi r3, r29, 0
/* 80073948 00070528  38 81 00 54 */	addi r4, r1, 0x54
/* 8007394C 0007052C  48 30 60 D5 */	bl HSD_MtxInverseTranspose
lbl_80073950:
/* 80073950 00070530  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 80073954 00070534  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 80073958 00070538  41 82 00 1C */	beq lbl_80073974
/* 8007395C 0007053C  38 61 00 54 */	addi r3, r1, 0x54
/* 80073960 00070540  38 80 00 00 */	li r4, 0
/* 80073964 00070544  48 2C DB 6D */	bl GXLoadNrmMtxImm
/* 80073968 00070548  80 7F 00 00 */	lwz r3, 0(r31)
/* 8007396C 0007054C  38 03 00 01 */	addi r0, r3, 1
/* 80073970 00070550  90 1F 00 00 */	stw r0, 0(r31)
lbl_80073974:
/* 80073974 00070554  57 80 07 7D */	rlwinm. r0, r28, 0, 0x1d, 0x1e
/* 80073978 00070558  41 82 00 20 */	beq lbl_80073998
/* 8007397C 0007055C  38 61 00 54 */	addi r3, r1, 0x54
/* 80073980 00070560  38 80 00 1E */	li r4, 0x1e
/* 80073984 00070564  38 A0 00 00 */	li r5, 0
/* 80073988 00070568  48 2C DB C5 */	bl GXLoadTexMtxImm
/* 8007398C 0007056C  80 7F 00 00 */	lwz r3, 0(r31)
/* 80073990 00070570  38 03 00 01 */	addi r0, r3, 1
/* 80073994 00070574  90 1F 00 00 */	stw r0, 0(r31)
lbl_80073998:
/* 80073998 00070578  80 01 00 9C */	lwz r0, 0x9c(r1)
/* 8007399C 0007057C  83 E1 00 94 */	lwz r31, 0x94(r1)
/* 800739A0 00070580  83 C1 00 90 */	lwz r30, 0x90(r1)
/* 800739A4 00070584  83 A1 00 8C */	lwz r29, 0x8c(r1)
/* 800739A8 00070588  83 81 00 88 */	lwz r28, 0x88(r1)
/* 800739AC 0007058C  38 21 00 98 */	addi r1, r1, 0x98
/* 800739B0 00070590  7C 08 03 A6 */	mtlr r0
/* 800739B4 00070594  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800739B8()
{ // clang-format off
    nofralloc
/* 800739B8 00070598  7C 08 02 A6 */	mflr r0
/* 800739BC 0007059C  3C E0 80 46 */	lis r7, ft_jobj_scale@ha
/* 800739C0 000705A0  90 01 00 04 */	stw r0, 4(r1)
/* 800739C4 000705A4  94 21 FE C8 */	stwu r1, -0x138(r1)
/* 800739C8 000705A8  BF 21 01 1C */	stmw r25, 0x11c(r1)
/* 800739CC 000705AC  3B E7 92 40 */	addi r31, r7, ft_jobj_scale@l
/* 800739D0 000705B0  3B 23 00 00 */	addi r25, r3, 0
/* 800739D4 000705B4  3B 44 00 00 */	addi r26, r4, 0
/* 800739D8 000705B8  3B 65 00 00 */	addi r27, r5, 0
/* 800739DC 000705BC  3B C6 00 00 */	addi r30, r6, 0
/* 800739E0 000705C0  3B 80 00 00 */	li r28, 0
/* 800739E4 000705C4  48 2F E9 31 */	bl HSD_JObjGetCurrent
/* 800739E8 000705C8  3B A3 00 00 */	addi r29, r3, 0
/* 800739EC 000705CC  38 81 00 80 */	addi r4, r1, 0x80
/* 800739F0 000705D0  38 A1 00 7C */	addi r5, r1, 0x7c
/* 800739F4 000705D4  38 60 00 00 */	li r3, 0
/* 800739F8 000705D8  48 2F A6 89 */	bl HSD_PObjGetMtxMark
/* 800739FC 000705DC  80 01 00 80 */	lwz r0, 0x80(r1)
/* 80073A00 000705E0  7C 00 E8 40 */	cmplw r0, r29
/* 80073A04 000705E4  41 82 00 14 */	beq lbl_80073A18
/* 80073A08 000705E8  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80073A0C 000705EC  28 00 00 01 */	cmplwi r0, 1
/* 80073A10 000705F0  41 82 00 08 */	beq lbl_80073A18
/* 80073A14 000705F4  63 9C 00 01 */	ori r28, r28, 1
lbl_80073A18:
/* 80073A18 000705F8  38 9D 00 00 */	addi r4, r29, 0
/* 80073A1C 000705FC  38 60 00 00 */	li r3, 0
/* 80073A20 00070600  38 A0 00 01 */	li r5, 1
/* 80073A24 00070604  48 2F A6 29 */	bl HSD_PObjSetMtxMark
/* 80073A28 00070608  38 81 00 80 */	addi r4, r1, 0x80
/* 80073A2C 0007060C  38 A1 00 7C */	addi r5, r1, 0x7c
/* 80073A30 00070610  38 60 00 01 */	li r3, 1
/* 80073A34 00070614  48 2F A6 4D */	bl HSD_PObjGetMtxMark
/* 80073A38 00070618  80 01 00 80 */	lwz r0, 0x80(r1)
/* 80073A3C 0007061C  80 99 00 14 */	lwz r4, 0x14(r25)
/* 80073A40 00070620  7C 00 20 40 */	cmplw r0, r4
/* 80073A44 00070624  41 82 00 14 */	beq lbl_80073A58
/* 80073A48 00070628  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80073A4C 0007062C  28 00 00 01 */	cmplwi r0, 1
/* 80073A50 00070630  41 82 00 08 */	beq lbl_80073A58
/* 80073A54 00070634  63 9C 00 02 */	ori r28, r28, 2
lbl_80073A58:
/* 80073A58 00070638  38 60 00 01 */	li r3, 1
/* 80073A5C 0007063C  38 A0 00 01 */	li r5, 1
/* 80073A60 00070640  48 2F A5 ED */	bl HSD_PObjSetMtxMark
/* 80073A64 00070644  2C 1C 00 00 */	cmpwi r28, 0
/* 80073A68 00070648  41 82 02 2C */	beq lbl_80073C94
/* 80073A6C 0007064C  57 C0 01 4B */	rlwinm. r0, r30, 0, 5, 5
/* 80073A70 00070650  3B C0 00 00 */	li r30, 0
/* 80073A74 00070654  40 82 00 44 */	bne lbl_80073AB8
/* 80073A78 00070658  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80073A7C 0007065C  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 80073A80 00070660  41 82 00 08 */	beq lbl_80073A88
/* 80073A84 00070664  63 DE 00 01 */	ori r30, r30, 1
lbl_80073A88:
/* 80073A88 00070668  38 60 00 00 */	li r3, 0
/* 80073A8C 0007066C  38 80 00 01 */	li r4, 1
/* 80073A90 00070670  48 2E B3 D9 */	bl _HSD_TObjGetCurrentByType
/* 80073A94 00070674  28 03 00 00 */	cmplwi r3, 0
/* 80073A98 00070678  41 82 00 08 */	beq lbl_80073AA0
/* 80073A9C 0007067C  63 DE 00 03 */	ori r30, r30, 3
lbl_80073AA0:
/* 80073AA0 00070680  38 60 00 00 */	li r3, 0
/* 80073AA4 00070684  38 80 00 02 */	li r4, 2
/* 80073AA8 00070688  48 2E B3 C1 */	bl _HSD_TObjGetCurrentByType
/* 80073AAC 0007068C  28 03 00 00 */	cmplwi r3, 0
/* 80073AB0 00070690  41 82 00 08 */	beq lbl_80073AB8
/* 80073AB4 00070694  63 DE 00 05 */	ori r30, r30, 5
lbl_80073AB8:
/* 80073AB8 00070698  7F 9C F3 78 */	or r28, r28, r30
/* 80073ABC 0007069C  63 80 00 01 */	ori r0, r28, 1
/* 80073AC0 000706A0  2C 00 00 00 */	cmpwi r0, 0
/* 80073AC4 000706A4  41 82 00 B8 */	beq lbl_80073B7C
/* 80073AC8 000706A8  38 60 00 00 */	li r3, 0
/* 80073ACC 000706AC  48 2C DA 45 */	bl GXSetCurrentMtx
/* 80073AD0 000706B0  38 7B 00 00 */	addi r3, r27, 0
/* 80073AD4 000706B4  38 80 00 00 */	li r4, 0
/* 80073AD8 000706B8  48 2C D9 BD */	bl GXLoadPosMtxImm
/* 80073ADC 000706BC  3C 60 80 40 */	lis r3, HSD_PerfCurrentStat@ha
/* 80073AE0 000706C0  38 63 72 18 */	addi r3, r3, HSD_PerfCurrentStat@l
/* 80073AE4 000706C4  3B C3 00 0C */	addi r30, r3, 0xc
/* 80073AE8 000706C8  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80073AEC 000706CC  57 80 07 FF */	clrlwi. r0, r28, 0x1f
/* 80073AF0 000706D0  38 03 00 01 */	addi r0, r3, 1
/* 80073AF4 000706D4  90 1E 00 00 */	stw r0, 0(r30)
/* 80073AF8 000706D8  41 82 00 84 */	beq lbl_80073B7C
/* 80073AFC 000706DC  88 1F 00 30 */	lbz r0, 0x30(r31)
/* 80073B00 000706E0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80073B04 000706E4  41 82 00 24 */	beq lbl_80073B28
/* 80073B08 000706E8  38 7F 00 00 */	addi r3, r31, 0
/* 80073B0C 000706EC  38 9B 00 00 */	addi r4, r27, 0
/* 80073B10 000706F0  38 A1 00 48 */	addi r5, r1, 0x48
/* 80073B14 000706F4  48 2C E6 F1 */	bl PSMTXConcat
/* 80073B18 000706F8  38 61 00 48 */	addi r3, r1, 0x48
/* 80073B1C 000706FC  38 81 00 E4 */	addi r4, r1, 0xe4
/* 80073B20 00070700  48 30 5F 01 */	bl HSD_MtxInverseTranspose
/* 80073B24 00070704  48 00 00 10 */	b lbl_80073B34
lbl_80073B28:
/* 80073B28 00070708  38 7B 00 00 */	addi r3, r27, 0
/* 80073B2C 0007070C  38 81 00 E4 */	addi r4, r1, 0xe4
/* 80073B30 00070710  48 30 5E F1 */	bl HSD_MtxInverseTranspose
lbl_80073B34:
/* 80073B34 00070714  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80073B38 00070718  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 80073B3C 0007071C  41 82 00 1C */	beq lbl_80073B58
/* 80073B40 00070720  38 61 00 E4 */	addi r3, r1, 0xe4
/* 80073B44 00070724  38 80 00 00 */	li r4, 0
/* 80073B48 00070728  48 2C D9 89 */	bl GXLoadNrmMtxImm
/* 80073B4C 0007072C  80 7E 00 00 */	lwz r3, 0(r30)
/* 80073B50 00070730  38 03 00 01 */	addi r0, r3, 1
/* 80073B54 00070734  90 1E 00 00 */	stw r0, 0(r30)
lbl_80073B58:
/* 80073B58 00070738  57 80 07 7D */	rlwinm. r0, r28, 0, 0x1d, 0x1e
/* 80073B5C 0007073C  41 82 00 20 */	beq lbl_80073B7C
/* 80073B60 00070740  38 61 00 E4 */	addi r3, r1, 0xe4
/* 80073B64 00070744  38 80 00 1E */	li r4, 0x1e
/* 80073B68 00070748  38 A0 00 00 */	li r5, 0
/* 80073B6C 0007074C  48 2C D9 E1 */	bl GXLoadTexMtxImm
/* 80073B70 00070750  80 7E 00 00 */	lwz r3, 0(r30)
/* 80073B74 00070754  38 03 00 01 */	addi r0, r3, 1
/* 80073B78 00070758  90 1E 00 00 */	stw r0, 0(r30)
lbl_80073B7C:
/* 80073B7C 0007075C  63 80 00 02 */	ori r0, r28, 2
/* 80073B80 00070760  2C 00 00 00 */	cmpwi r0, 0
/* 80073B84 00070764  41 82 01 10 */	beq lbl_80073C94
/* 80073B88 00070768  83 79 00 14 */	lwz r27, 0x14(r25)
/* 80073B8C 0007076C  28 1B 00 00 */	cmplwi r27, 0
/* 80073B90 00070770  41 82 00 44 */	beq lbl_80073BD4
/* 80073B94 00070774  40 82 00 14 */	bne lbl_80073BA8
/* 80073B98 00070778  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80073B9C 0007077C  38 80 02 34 */	li r4, 0x234
/* 80073BA0 00070780  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80073BA4 00070784  48 31 46 7D */	bl __assert
lbl_80073BA8:
/* 80073BA8 00070788  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 80073BAC 0007078C  38 60 00 00 */	li r3, 0
/* 80073BB0 00070790  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80073BB4 00070794  40 82 00 10 */	bne lbl_80073BC4
/* 80073BB8 00070798  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80073BBC 0007079C  41 82 00 08 */	beq lbl_80073BC4
/* 80073BC0 000707A0  38 60 00 01 */	li r3, 1
lbl_80073BC4:
/* 80073BC4 000707A4  2C 03 00 00 */	cmpwi r3, 0
/* 80073BC8 000707A8  41 82 00 0C */	beq lbl_80073BD4
/* 80073BCC 000707AC  7F 63 DB 78 */	mr r3, r27
/* 80073BD0 000707B0  48 2F F4 A9 */	bl HSD_JObjSetupMatrixSub
lbl_80073BD4:
/* 80073BD4 000707B4  80 99 00 14 */	lwz r4, 0x14(r25)
/* 80073BD8 000707B8  38 7A 00 00 */	addi r3, r26, 0
/* 80073BDC 000707BC  38 A1 00 84 */	addi r5, r1, 0x84
/* 80073BE0 000707C0  38 84 00 44 */	addi r4, r4, 0x44
/* 80073BE4 000707C4  48 2C E6 21 */	bl PSMTXConcat
/* 80073BE8 000707C8  38 61 00 84 */	addi r3, r1, 0x84
/* 80073BEC 000707CC  38 80 00 03 */	li r4, 3
/* 80073BF0 000707D0  48 2C D8 A5 */	bl GXLoadPosMtxImm
/* 80073BF4 000707D4  3C 60 80 40 */	lis r3, HSD_PerfCurrentStat@ha
/* 80073BF8 000707D8  38 63 72 18 */	addi r3, r3, HSD_PerfCurrentStat@l
/* 80073BFC 000707DC  3B 23 00 0C */	addi r25, r3, 0xc
/* 80073C00 000707E0  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80073C04 000707E4  57 80 07 FF */	clrlwi. r0, r28, 0x1f
/* 80073C08 000707E8  38 03 00 01 */	addi r0, r3, 1
/* 80073C0C 000707EC  90 19 00 00 */	stw r0, 0(r25)
/* 80073C10 000707F0  41 82 00 84 */	beq lbl_80073C94
/* 80073C14 000707F4  88 1F 00 30 */	lbz r0, 0x30(r31)
/* 80073C18 000707F8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80073C1C 000707FC  41 82 00 24 */	beq lbl_80073C40
/* 80073C20 00070800  38 7F 00 00 */	addi r3, r31, 0
/* 80073C24 00070804  38 81 00 84 */	addi r4, r1, 0x84
/* 80073C28 00070808  38 A1 00 18 */	addi r5, r1, 0x18
/* 80073C2C 0007080C  48 2C E5 D9 */	bl PSMTXConcat
/* 80073C30 00070810  38 61 00 18 */	addi r3, r1, 0x18
/* 80073C34 00070814  38 81 00 B4 */	addi r4, r1, 0xb4
/* 80073C38 00070818  48 30 5D E9 */	bl HSD_MtxInverseTranspose
/* 80073C3C 0007081C  48 00 00 10 */	b lbl_80073C4C
lbl_80073C40:
/* 80073C40 00070820  38 61 00 84 */	addi r3, r1, 0x84
/* 80073C44 00070824  38 81 00 B4 */	addi r4, r1, 0xb4
/* 80073C48 00070828  48 30 5D D9 */	bl HSD_MtxInverseTranspose
lbl_80073C4C:
/* 80073C4C 0007082C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80073C50 00070830  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 80073C54 00070834  41 82 00 1C */	beq lbl_80073C70
/* 80073C58 00070838  38 61 00 B4 */	addi r3, r1, 0xb4
/* 80073C5C 0007083C  38 80 00 03 */	li r4, 3
/* 80073C60 00070840  48 2C D8 71 */	bl GXLoadNrmMtxImm
/* 80073C64 00070844  80 79 00 00 */	lwz r3, 0(r25)
/* 80073C68 00070848  38 03 00 01 */	addi r0, r3, 1
/* 80073C6C 0007084C  90 19 00 00 */	stw r0, 0(r25)
lbl_80073C70:
/* 80073C70 00070850  57 80 07 7D */	rlwinm. r0, r28, 0, 0x1d, 0x1e
/* 80073C74 00070854  41 82 00 20 */	beq lbl_80073C94
/* 80073C78 00070858  38 61 00 B4 */	addi r3, r1, 0xb4
/* 80073C7C 0007085C  38 80 00 21 */	li r4, 0x21
/* 80073C80 00070860  38 A0 00 00 */	li r5, 0
/* 80073C84 00070864  48 2C D8 C9 */	bl GXLoadTexMtxImm
/* 80073C88 00070868  80 79 00 00 */	lwz r3, 0(r25)
/* 80073C8C 0007086C  38 03 00 01 */	addi r0, r3, 1
/* 80073C90 00070870  90 19 00 00 */	stw r0, 0(r25)
lbl_80073C94:
/* 80073C94 00070874  BB 21 01 1C */	lmw r25, 0x11c(r1)
/* 80073C98 00070878  80 01 01 3C */	lwz r0, 0x13c(r1)
/* 80073C9C 0007087C  38 21 01 38 */	addi r1, r1, 0x138
/* 80073CA0 00070880  7C 08 03 A6 */	mtlr r0
/* 80073CA4 00070884  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80073CA8()
{ // clang-format off
    nofralloc
/* 80073CA8 00070888  7C 08 02 A6 */	mflr r0
/* 80073CAC 0007088C  3C A0 80 3C */	lis r5, ftJObj@ha
/* 80073CB0 00070890  90 01 00 04 */	stw r0, 4(r1)
/* 80073CB4 00070894  94 21 FE D0 */	stwu r1, -0x130(r1)
/* 80073CB8 00070898  DB E1 01 28 */	stfd f31, 0x128(r1)
/* 80073CBC 0007089C  DB C1 01 20 */	stfd f30, 0x120(r1)
/* 80073CC0 000708A0  BE 21 00 E4 */	stmw r17, 0xe4(r1)
/* 80073CC4 000708A4  3A 43 00 00 */	addi r18, r3, 0
/* 80073CC8 000708A8  3B E4 00 00 */	addi r31, r4, 0
/* 80073CCC 000708AC  3A 26 00 00 */	addi r17, r6, 0
/* 80073CD0 000708B0  3B A5 08 F8 */	addi r29, r5, ftJObj@l
/* 80073CD4 000708B4  48 2F E6 41 */	bl HSD_JObjGetCurrent
/* 80073CD8 000708B8  3A E3 00 00 */	addi r23, r3, 0
/* 80073CDC 000708BC  38 60 00 00 */	li r3, 0
/* 80073CE0 000708C0  38 80 00 02 */	li r4, 2
/* 80073CE4 000708C4  48 2F A3 51 */	bl HSD_PObjClearMtxMark
/* 80073CE8 000708C8  56 20 01 4B */	rlwinm. r0, r17, 0, 5, 5
/* 80073CEC 000708CC  3A 20 00 00 */	li r17, 0
/* 80073CF0 000708D0  40 82 00 44 */	bne lbl_80073D34
/* 80073CF4 000708D4  80 17 00 14 */	lwz r0, 0x14(r23)
/* 80073CF8 000708D8  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 80073CFC 000708DC  41 82 00 08 */	beq lbl_80073D04
/* 80073D00 000708E0  62 31 00 01 */	ori r17, r17, 1
lbl_80073D04:
/* 80073D04 000708E4  38 60 00 00 */	li r3, 0
/* 80073D08 000708E8  38 80 00 01 */	li r4, 1
/* 80073D0C 000708EC  48 2E B1 5D */	bl _HSD_TObjGetCurrentByType
/* 80073D10 000708F0  28 03 00 00 */	cmplwi r3, 0
/* 80073D14 000708F4  41 82 00 08 */	beq lbl_80073D1C
/* 80073D18 000708F8  62 31 00 03 */	ori r17, r17, 3
lbl_80073D1C:
/* 80073D1C 000708FC  38 60 00 00 */	li r3, 0
/* 80073D20 00070900  38 80 00 02 */	li r4, 2
/* 80073D24 00070904  48 2E B1 45 */	bl _HSD_TObjGetCurrentByType
/* 80073D28 00070908  28 03 00 00 */	cmplwi r3, 0
/* 80073D2C 0007090C  41 82 00 08 */	beq lbl_80073D34
/* 80073D30 00070910  62 31 00 05 */	ori r17, r17, 5
lbl_80073D34:
/* 80073D34 00070914  38 77 00 00 */	addi r3, r23, 0
/* 80073D38 00070918  38 81 00 AC */	addi r4, r1, 0xac
/* 80073D3C 0007091C  48 30 05 71 */	bl _HSD_mkEnvelopeModelNodeMtx
/* 80073D40 00070920  3C 80 80 46 */	lis r4, ft_jobj_scale@ha
/* 80073D44 00070924  82 D2 00 14 */	lwz r22, 0x14(r18)
/* 80073D48 00070928  3B C4 92 40 */	addi r30, r4, ft_jobj_scale@l
/* 80073D4C 0007092C  C3 E2 88 EC */	lfs f31, 0.0F
/* 80073D50 00070930  3C 80 80 40 */	lis r4, HSD_PerfCurrentStat@ha
/* 80073D54 00070934  C3 C2 88 E8 */	lfs f30, 1.0F
/* 80073D58 00070938  38 84 72 18 */	addi r4, r4, HSD_PerfCurrentStat@l
/* 80073D5C 0007093C  3A 83 00 00 */	addi r20, r3, 0
/* 80073D60 00070940  56 3C 07 FE */	clrlwi r28, r17, 0x1f
/* 80073D64 00070944  3B 7E 00 30 */	addi r27, r30, 0x30
/* 80073D68 00070948  56 3A 07 7C */	rlwinm r26, r17, 0, 0x1d, 0x1e
/* 80073D6C 0007094C  3B 04 00 0C */	addi r24, r4, 0xc
/* 80073D70 00070950  3A A0 00 00 */	li r21, 0
/* 80073D74 00070954  48 00 02 A8 */	b lbl_8007401C
lbl_80073D78:
/* 80073D78 00070958  82 76 00 04 */	lwz r19, 4(r22)
/* 80073D7C 0007095C  7E A3 AB 78 */	mr r3, r21
/* 80073D80 00070960  48 30 6B 2D */	bl HSD_Index2PosNrmMtx
/* 80073D84 00070964  28 13 00 00 */	cmplwi r19, 0
/* 80073D88 00070968  3A 43 00 00 */	addi r18, r3, 0
/* 80073D8C 0007096C  3A 20 00 00 */	li r17, 0
/* 80073D90 00070970  40 82 00 14 */	bne lbl_80073DA4
/* 80073D94 00070974  38 7D 01 10 */	addi r3, r29, 0x110
/* 80073D98 00070978  38 BD 01 1C */	addi r5, r29, 0x11c
/* 80073D9C 0007097C  38 80 01 48 */	li r4, 0x148
/* 80073DA0 00070980  48 31 44 81 */	bl __assert
lbl_80073DA4:
/* 80073DA4 00070984  C0 13 00 08 */	lfs f0, 8(r19)
/* 80073DA8 00070988  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 80073DAC 0007098C  4C 41 13 82 */	cror 2, 1, 2
/* 80073DB0 00070990  40 82 00 80 */	bne lbl_80073E30
/* 80073DB4 00070994  83 33 00 04 */	lwz r25, 4(r19)
/* 80073DB8 00070998  28 19 00 00 */	cmplwi r25, 0
/* 80073DBC 0007099C  41 82 00 44 */	beq lbl_80073E00
/* 80073DC0 000709A0  40 82 00 14 */	bne lbl_80073DD4
/* 80073DC4 000709A4  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80073DC8 000709A8  38 80 02 34 */	li r4, 0x234
/* 80073DCC 000709AC  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80073DD0 000709B0  48 31 44 51 */	bl __assert
lbl_80073DD4:
/* 80073DD4 000709B4  80 99 00 14 */	lwz r4, 0x14(r25)
/* 80073DD8 000709B8  38 60 00 00 */	li r3, 0
/* 80073DDC 000709BC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80073DE0 000709C0  40 82 00 10 */	bne lbl_80073DF0
/* 80073DE4 000709C4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80073DE8 000709C8  41 82 00 08 */	beq lbl_80073DF0
/* 80073DEC 000709CC  38 60 00 01 */	li r3, 1
lbl_80073DF0:
/* 80073DF0 000709D0  2C 03 00 00 */	cmpwi r3, 0
/* 80073DF4 000709D4  41 82 00 0C */	beq lbl_80073E00
/* 80073DF8 000709D8  7F 23 CB 78 */	mr r3, r25
/* 80073DFC 000709DC  48 2F F2 7D */	bl HSD_JObjSetupMatrixSub
lbl_80073E00:
/* 80073E00 000709E0  28 14 00 00 */	cmplwi r20, 0
/* 80073E04 000709E4  41 82 00 20 */	beq lbl_80073E24
/* 80073E08 000709E8  80 73 00 04 */	lwz r3, 4(r19)
/* 80073E0C 000709EC  38 A1 00 7C */	addi r5, r1, 0x7c
/* 80073E10 000709F0  80 83 00 78 */	lwz r4, 0x78(r3)
/* 80073E14 000709F4  38 63 00 44 */	addi r3, r3, 0x44
/* 80073E18 000709F8  48 2C E3 ED */	bl PSMTXConcat
/* 80073E1C 000709FC  3A 61 00 7C */	addi r19, r1, 0x7c
/* 80073E20 00070A00  48 00 01 1C */	b lbl_80073F3C
lbl_80073E24:
/* 80073E24 00070A04  80 73 00 04 */	lwz r3, 4(r19)
/* 80073E28 00070A08  3A 63 00 44 */	addi r19, r3, 0x44
/* 80073E2C 00070A0C  48 00 01 10 */	b lbl_80073F3C
lbl_80073E30:
/* 80073E30 00070A10  D3 E1 00 A8 */	stfs f31, 0xa8(r1)
/* 80073E34 00070A14  D3 E1 00 A4 */	stfs f31, 0xa4(r1)
/* 80073E38 00070A18  D3 E1 00 A0 */	stfs f31, 0xa0(r1)
/* 80073E3C 00070A1C  D3 E1 00 9C */	stfs f31, 0x9c(r1)
/* 80073E40 00070A20  D3 E1 00 98 */	stfs f31, 0x98(r1)
/* 80073E44 00070A24  D3 E1 00 94 */	stfs f31, 0x94(r1)
/* 80073E48 00070A28  D3 E1 00 90 */	stfs f31, 0x90(r1)
/* 80073E4C 00070A2C  D3 E1 00 8C */	stfs f31, 0x8c(r1)
/* 80073E50 00070A30  D3 E1 00 88 */	stfs f31, 0x88(r1)
/* 80073E54 00070A34  D3 E1 00 84 */	stfs f31, 0x84(r1)
/* 80073E58 00070A38  D3 E1 00 80 */	stfs f31, 0x80(r1)
/* 80073E5C 00070A3C  D3 E1 00 7C */	stfs f31, 0x7c(r1)
/* 80073E60 00070A40  48 00 00 D0 */	b lbl_80073F30
lbl_80073E64:
/* 80073E64 00070A44  80 13 00 04 */	lwz r0, 4(r19)
/* 80073E68 00070A48  28 00 00 00 */	cmplwi r0, 0
/* 80073E6C 00070A4C  40 82 00 14 */	bne lbl_80073E80
/* 80073E70 00070A50  38 7D 01 10 */	addi r3, r29, 0x110
/* 80073E74 00070A54  38 BD 01 28 */	addi r5, r29, 0x128
/* 80073E78 00070A58  38 80 01 5C */	li r4, 0x15c
/* 80073E7C 00070A5C  48 31 43 A5 */	bl __assert
lbl_80073E80:
/* 80073E80 00070A60  80 13 00 04 */	lwz r0, 4(r19)
/* 80073E84 00070A64  28 00 00 00 */	cmplwi r0, 0
/* 80073E88 00070A68  7C 19 03 78 */	mr r25, r0
/* 80073E8C 00070A6C  41 82 00 44 */	beq lbl_80073ED0
/* 80073E90 00070A70  40 82 00 14 */	bne lbl_80073EA4
/* 80073E94 00070A74  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80073E98 00070A78  38 80 02 34 */	li r4, 0x234
/* 80073E9C 00070A7C  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80073EA0 00070A80  48 31 43 81 */	bl __assert
lbl_80073EA4:
/* 80073EA4 00070A84  80 99 00 14 */	lwz r4, 0x14(r25)
/* 80073EA8 00070A88  38 60 00 00 */	li r3, 0
/* 80073EAC 00070A8C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80073EB0 00070A90  40 82 00 10 */	bne lbl_80073EC0
/* 80073EB4 00070A94  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80073EB8 00070A98  41 82 00 08 */	beq lbl_80073EC0
/* 80073EBC 00070A9C  38 60 00 01 */	li r3, 1
lbl_80073EC0:
/* 80073EC0 00070AA0  2C 03 00 00 */	cmpwi r3, 0
/* 80073EC4 00070AA4  41 82 00 0C */	beq lbl_80073ED0
/* 80073EC8 00070AA8  7F 23 CB 78 */	mr r3, r25
/* 80073ECC 00070AAC  48 2F F1 AD */	bl HSD_JObjSetupMatrixSub
lbl_80073ED0:
/* 80073ED0 00070AB0  34 19 00 44 */	addic. r0, r25, 0x44
/* 80073ED4 00070AB4  40 82 00 14 */	bne lbl_80073EE8
/* 80073ED8 00070AB8  38 7D 01 10 */	addi r3, r29, 0x110
/* 80073EDC 00070ABC  38 80 01 5F */	li r4, 0x15f
/* 80073EE0 00070AC0  38 AD 83 A8 */	addi r5, r13, lbl_804D3A48
/* 80073EE4 00070AC4  48 31 43 3D */	bl __assert
lbl_80073EE8:
/* 80073EE8 00070AC8  80 19 00 78 */	lwz r0, 0x78(r25)
/* 80073EEC 00070ACC  28 00 00 00 */	cmplwi r0, 0
/* 80073EF0 00070AD0  40 82 00 14 */	bne lbl_80073F04
/* 80073EF4 00070AD4  38 7D 01 10 */	addi r3, r29, 0x110
/* 80073EF8 00070AD8  38 BD 01 38 */	addi r5, r29, 0x138
/* 80073EFC 00070ADC  38 80 01 60 */	li r4, 0x160
/* 80073F00 00070AE0  48 31 43 21 */	bl __assert
lbl_80073F04:
/* 80073F04 00070AE4  80 99 00 78 */	lwz r4, 0x78(r25)
/* 80073F08 00070AE8  38 79 00 44 */	addi r3, r25, 0x44
/* 80073F0C 00070AEC  38 A1 00 4C */	addi r5, r1, 0x4c
/* 80073F10 00070AF0  48 2C E2 F5 */	bl PSMTXConcat
/* 80073F14 00070AF4  38 81 00 7C */	addi r4, r1, 0x7c
/* 80073F18 00070AF8  C0 33 00 08 */	lfs f1, 8(r19)
/* 80073F1C 00070AFC  38 A4 00 00 */	addi r5, r4, 0
/* 80073F20 00070B00  38 61 00 4C */	addi r3, r1, 0x4c
/* 80073F24 00070B04  48 30 66 29 */	bl HSD_MtxScaledAdd
/* 80073F28 00070B08  82 73 00 00 */	lwz r19, 0(r19)
/* 80073F2C 00070B0C  3A 31 00 01 */	addi r17, r17, 1
lbl_80073F30:
/* 80073F30 00070B10  28 13 00 00 */	cmplwi r19, 0
/* 80073F34 00070B14  40 82 FF 30 */	bne lbl_80073E64
/* 80073F38 00070B18  3A 61 00 7C */	addi r19, r1, 0x7c
lbl_80073F3C:
/* 80073F3C 00070B1C  7E 23 8B 78 */	mr r3, r17
/* 80073F40 00070B20  48 30 A4 61 */	bl HSD_PerfCountEnvelopeBlending
/* 80073F44 00070B24  28 14 00 00 */	cmplwi r20, 0
/* 80073F48 00070B28  41 82 00 14 */	beq lbl_80073F5C
/* 80073F4C 00070B2C  38 73 00 00 */	addi r3, r19, 0
/* 80073F50 00070B30  38 94 00 00 */	addi r4, r20, 0
/* 80073F54 00070B34  38 A1 00 7C */	addi r5, r1, 0x7c
/* 80073F58 00070B38  48 2C E2 AD */	bl PSMTXConcat
lbl_80073F5C:
/* 80073F5C 00070B3C  38 7F 00 00 */	addi r3, r31, 0
/* 80073F60 00070B40  38 93 00 00 */	addi r4, r19, 0
/* 80073F64 00070B44  38 A1 00 4C */	addi r5, r1, 0x4c
/* 80073F68 00070B48  48 2C E2 9D */	bl PSMTXConcat
/* 80073F6C 00070B4C  38 61 00 4C */	addi r3, r1, 0x4c
/* 80073F70 00070B50  38 92 00 00 */	addi r4, r18, 0
/* 80073F74 00070B54  48 2C D5 21 */	bl GXLoadPosMtxImm
/* 80073F78 00070B58  80 78 00 00 */	lwz r3, 0(r24)
/* 80073F7C 00070B5C  2C 1C 00 00 */	cmpwi r28, 0
/* 80073F80 00070B60  38 03 00 01 */	addi r0, r3, 1
/* 80073F84 00070B64  90 18 00 00 */	stw r0, 0(r24)
/* 80073F88 00070B68  41 82 00 8C */	beq lbl_80074014
/* 80073F8C 00070B6C  88 1B 00 00 */	lbz r0, 0(r27)
/* 80073F90 00070B70  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80073F94 00070B74  41 82 00 24 */	beq lbl_80073FB8
/* 80073F98 00070B78  38 7E 00 00 */	addi r3, r30, 0
/* 80073F9C 00070B7C  38 81 00 4C */	addi r4, r1, 0x4c
/* 80073FA0 00070B80  38 A1 00 18 */	addi r5, r1, 0x18
/* 80073FA4 00070B84  48 2C E2 61 */	bl PSMTXConcat
/* 80073FA8 00070B88  38 61 00 18 */	addi r3, r1, 0x18
/* 80073FAC 00070B8C  38 81 00 7C */	addi r4, r1, 0x7c
/* 80073FB0 00070B90  48 30 5A 71 */	bl HSD_MtxInverseTranspose
/* 80073FB4 00070B94  48 00 00 10 */	b lbl_80073FC4
lbl_80073FB8:
/* 80073FB8 00070B98  38 61 00 4C */	addi r3, r1, 0x4c
/* 80073FBC 00070B9C  38 81 00 7C */	addi r4, r1, 0x7c
/* 80073FC0 00070BA0  48 30 5A 61 */	bl HSD_MtxInverseTranspose
lbl_80073FC4:
/* 80073FC4 00070BA4  80 17 00 14 */	lwz r0, 0x14(r23)
/* 80073FC8 00070BA8  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 80073FCC 00070BAC  41 82 00 1C */	beq lbl_80073FE8
/* 80073FD0 00070BB0  38 61 00 7C */	addi r3, r1, 0x7c
/* 80073FD4 00070BB4  38 92 00 00 */	addi r4, r18, 0
/* 80073FD8 00070BB8  48 2C D4 F9 */	bl GXLoadNrmMtxImm
/* 80073FDC 00070BBC  80 78 00 00 */	lwz r3, 0(r24)
/* 80073FE0 00070BC0  38 03 00 01 */	addi r0, r3, 1
/* 80073FE4 00070BC4  90 18 00 00 */	stw r0, 0(r24)
lbl_80073FE8:
/* 80073FE8 00070BC8  2C 1A 00 00 */	cmpwi r26, 0
/* 80073FEC 00070BCC  41 82 00 28 */	beq lbl_80074014
/* 80073FF0 00070BD0  7E A3 AB 78 */	mr r3, r21
/* 80073FF4 00070BD4  48 2E CF 31 */	bl HSD_Index2TexMtx
/* 80073FF8 00070BD8  38 83 00 00 */	addi r4, r3, 0
/* 80073FFC 00070BDC  38 61 00 7C */	addi r3, r1, 0x7c
/* 80074000 00070BE0  38 A0 00 00 */	li r5, 0
/* 80074004 00070BE4  48 2C D5 49 */	bl GXLoadTexMtxImm
/* 80074008 00070BE8  80 78 00 00 */	lwz r3, 0(r24)
/* 8007400C 00070BEC  38 03 00 01 */	addi r0, r3, 1
/* 80074010 00070BF0  90 18 00 00 */	stw r0, 0(r24)
lbl_80074014:
/* 80074014 00070BF4  82 D6 00 00 */	lwz r22, 0(r22)
/* 80074018 00070BF8  3A B5 00 01 */	addi r21, r21, 1
lbl_8007401C:
/* 8007401C 00070BFC  2C 15 00 0A */	cmpwi r21, 0xa
/* 80074020 00070C00  40 80 00 0C */	bge lbl_8007402C
/* 80074024 00070C04  28 16 00 00 */	cmplwi r22, 0
/* 80074028 00070C08  40 82 FD 50 */	bne lbl_80073D78
lbl_8007402C:
/* 8007402C 00070C0C  BA 21 00 E4 */	lmw r17, 0xe4(r1)
/* 80074030 00070C10  80 01 01 34 */	lwz r0, 0x134(r1)
/* 80074034 00070C14  CB E1 01 28 */	lfd f31, 0x128(r1)
/* 80074038 00070C18  CB C1 01 20 */	lfd f30, 0x120(r1)
/* 8007403C 00070C1C  38 21 01 30 */	addi r1, r1, 0x130
/* 80074040 00070C20  7C 08 03 A6 */	mtlr r0
/* 80074044 00070C24  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void Fighter_PObjSetupMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                              u32 rendermode)
{ // clang-format off
    nofralloc
/* 80074048 00070C28  7C 08 02 A6 */	mflr r0
/* 8007404C 00070C2C  3C E0 80 46 */	lis r7, ft_jobj_scale@ha
/* 80074050 00070C30  90 01 00 04 */	stw r0, 4(r1)
/* 80074054 00070C34  38 E7 92 40 */	addi r7, r7, ft_jobj_scale@l
/* 80074058 00070C38  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007405C 00070C3C  88 07 00 30 */	lbz r0, 0x30(r7)
/* 80074060 00070C40  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80074064 00070C44  40 82 00 1C */	bne lbl_80074080
/* 80074068 00070C48  3C E0 80 40 */	lis r7, hsdPObj@ha
/* 8007406C 00070C4C  38 E7 63 98 */	addi r7, r7, hsdPObj@l
/* 80074070 00070C50  81 87 00 40 */	lwz r12, 0x40(r7)
/* 80074074 00070C54  7D 88 03 A6 */	mtlr r12
/* 80074078 00070C58  4E 80 00 21 */	blrl
/* 8007407C 00070C5C  48 00 00 58 */	b lbl_800740D4
lbl_80074080:
/* 80074080 00070C60  A0 03 00 0C */	lhz r0, 0xc(r3)
/* 80074084 00070C64  54 00 04 A6 */	rlwinm r0, r0, 0, 0x12, 0x13
/* 80074088 00070C68  2C 00 10 00 */	cmpwi r0, 0x1000
/* 8007408C 00070C6C  41 82 00 3C */	beq lbl_800740C8
/* 80074090 00070C70  40 80 00 10 */	bge lbl_800740A0
/* 80074094 00070C74  2C 00 00 00 */	cmpwi r0, 0
/* 80074098 00070C78  41 82 00 14 */	beq lbl_800740AC
/* 8007409C 00070C7C  48 00 00 38 */	b lbl_800740D4
lbl_800740A0:
/* 800740A0 00070C80  2C 00 20 00 */	cmpwi r0, 0x2000
/* 800740A4 00070C84  41 82 00 2C */	beq lbl_800740D0
/* 800740A8 00070C88  48 00 00 2C */	b lbl_800740D4
lbl_800740AC:
/* 800740AC 00070C8C  80 03 00 14 */	lwz r0, 0x14(r3)
/* 800740B0 00070C90  28 00 00 00 */	cmplwi r0, 0
/* 800740B4 00070C94  40 82 00 0C */	bne lbl_800740C0
/* 800740B8 00070C98  4B FF F7 79 */	bl func_80073830
/* 800740BC 00070C9C  48 00 00 18 */	b lbl_800740D4
lbl_800740C0:
/* 800740C0 00070CA0  4B FF F8 F9 */	bl func_800739B8
/* 800740C4 00070CA4  48 00 00 10 */	b lbl_800740D4
lbl_800740C8:
/* 800740C8 00070CA8  4B FF F7 69 */	bl func_80073830
/* 800740CC 00070CAC  48 00 00 08 */	b lbl_800740D4
lbl_800740D0:
/* 800740D0 00070CB0  4B FF FB D9 */	bl func_80073CA8
lbl_800740D4:
/* 800740D4 00070CB4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800740D8 00070CB8  38 21 00 08 */	addi r1, r1, 8
/* 800740DC 00070CBC  7C 08 03 A6 */	mtlr r0
/* 800740E0 00070CC0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

void Fighter_PObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftPObj), HSD_CLASS_INFO(&hsdPObj),
                     lbl_803C09E0, lbl_804D3A50, sizeof(HSD_PObjInfo),
                     sizeof(HSD_PObj));
    HSD_POBJ_INFO(&ftPObj)->load = lbRefract_PObjLoad;
    HSD_POBJ_INFO(&ftPObj)->setup_mtx = Fighter_PObjSetupMtx;
}

#pragma push
asm void func_80074148()
{ // clang-format off
    nofralloc
/* 80074148 00070D28  7C 08 02 A6 */	mflr r0
/* 8007414C 00070D2C  3C 60 80 3C */	lis r3, ftPObj@ha
/* 80074150 00070D30  90 01 00 04 */	stw r0, 4(r1)
/* 80074154 00070D34  38 63 09 98 */	addi r3, r3, ftPObj@l
/* 80074158 00070D38  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007415C 00070D3C  48 2F 7E 15 */	bl HSD_PObjSetDefaultClass
/* 80074160 00070D40  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80074164 00070D44  38 21 00 08 */	addi r1, r1, 8
/* 80074168 00070D48  7C 08 03 A6 */	mtlr r0
/* 8007416C 00070D4C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80074170()
{ // clang-format off
    nofralloc
/* 80074170 00070D50  7C 08 02 A6 */	mflr r0
/* 80074174 00070D54  38 60 00 00 */	li r3, 0
/* 80074178 00070D58  90 01 00 04 */	stw r0, 4(r1)
/* 8007417C 00070D5C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80074180 00070D60  48 2F 7D F1 */	bl HSD_PObjSetDefaultClass
/* 80074184 00070D64  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80074188 00070D68  38 21 00 08 */	addi r1, r1, 8
/* 8007418C 00070D6C  7C 08 03 A6 */	mtlr r0
/* 80074190 00070D70  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#include <dolphin/os/os.h>

#pragma push
asm void func_80074194(Fighter* fighter, FighterBone* bone, HSD_JObj* jobj,
                       u32* dobj_index, u32 tree_depth)
{ // clang-format off
    nofralloc
/* 80074194 00070D74  7C 08 02 A6 */	mflr r0
/* 80074198 00070D78  3D 00 80 3C */	lis r8, ftJObj@ha
/* 8007419C 00070D7C  90 01 00 04 */	stw r0, 4(r1)
/* 800741A0 00070D80  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 800741A4 00070D84  BF 21 00 2C */	stmw r25, 0x2c(r1)
/* 800741A8 00070D88  3B A5 00 00 */	addi r29, r5, 0
/* 800741AC 00070D8C  3B 23 00 00 */	addi r25, r3, 0
/* 800741B0 00070D90  3B 44 00 00 */	addi r26, r4, 0
/* 800741B4 00070D94  3B 66 00 00 */	addi r27, r6, 0
/* 800741B8 00070D98  3B 87 00 00 */	addi r28, r7, 0
/* 800741BC 00070D9C  38 7D 00 00 */	addi r3, r29, 0
/* 800741C0 00070DA0  3B E8 08 F8 */	addi r31, r8, ftJObj@l
/* 800741C4 00070DA4  48 2F DA 29 */	bl HSD_JObjGetDObj
/* 800741C8 00070DA8  3B C3 00 00 */	addi r30, r3, 0
/* 800741CC 00070DAC  38 7D 00 00 */	addi r3, r29, 0
/* 800741D0 00070DB0  48 2F DB 19 */	bl HSD_JObjGetFlags
/* 800741D4 00070DB4  93 BA 00 00 */	stw r29, 0(r26)
/* 800741D8 00070DB8  38 A0 00 01 */	li r5, 1
/* 800741DC 00070DBC  54 60 06 31 */	rlwinm. r0, r3, 0, 0x18, 0x18
/* 800741E0 00070DC0  88 9A 00 08 */	lbz r4, 8(r26)
/* 800741E4 00070DC4  50 A4 36 72 */	rlwimi r4, r5, 6, 0x19, 0x19
/* 800741E8 00070DC8  3B A0 00 00 */	li r29, 0
/* 800741EC 00070DCC  98 9A 00 08 */	stb r4, 8(r26)
/* 800741F0 00070DD0  41 82 00 08 */	beq lbl_800741F8
/* 800741F4 00070DD4  48 00 00 08 */	b lbl_800741FC
lbl_800741F8:
/* 800741F8 00070DD8  38 A0 00 00 */	li r5, 0
lbl_800741FC:
/* 800741FC 00070DDC  88 9A 00 08 */	lbz r4, 8(r26)
/* 80074200 00070DE0  50 A4 07 FE */	rlwimi r4, r5, 0, 0x1f, 0x1f
/* 80074204 00070DE4  54 60 05 EF */	rlwinm. r0, r3, 0, 0x17, 0x17
/* 80074208 00070DE8  98 9A 00 08 */	stb r4, 8(r26)
/* 8007420C 00070DEC  41 82 00 0C */	beq lbl_80074218
/* 80074210 00070DF0  38 A0 00 01 */	li r5, 1
/* 80074214 00070DF4  48 00 00 08 */	b lbl_8007421C
lbl_80074218:
/* 80074218 00070DF8  38 A0 00 00 */	li r5, 0
lbl_8007421C:
/* 8007421C 00070DFC  88 9A 00 09 */	lbz r4, 9(r26)
/* 80074220 00070E00  50 A4 3E 30 */	rlwimi r4, r5, 7, 0x18, 0x18
/* 80074224 00070E04  54 60 03 DF */	rlwinm. r0, r3, 0, 0xf, 0xf
/* 80074228 00070E08  98 9A 00 09 */	stb r4, 9(r26)
/* 8007422C 00070E0C  41 82 00 0C */	beq lbl_80074238
/* 80074230 00070E10  38 A0 00 01 */	li r5, 1
/* 80074234 00070E14  48 00 00 08 */	b lbl_8007423C
lbl_80074238:
/* 80074238 00070E18  38 A0 00 00 */	li r5, 0
lbl_8007423C:
/* 8007423C 00070E1C  88 9A 00 09 */	lbz r4, 9(r26)
/* 80074240 00070E20  50 A4 36 72 */	rlwimi r4, r5, 6, 0x19, 0x19
/* 80074244 00070E24  54 60 03 5B */	rlwinm. r0, r3, 0, 0xd, 0xd
/* 80074248 00070E28  98 9A 00 09 */	stb r4, 9(r26)
/* 8007424C 00070E2C  41 82 00 0C */	beq lbl_80074258
/* 80074250 00070E30  38 A0 00 01 */	li r5, 1
/* 80074254 00070E34  48 00 00 08 */	b lbl_8007425C
lbl_80074258:
/* 80074258 00070E38  38 A0 00 00 */	li r5, 0
lbl_8007425C:
/* 8007425C 00070E3C  88 9A 00 09 */	lbz r4, 9(r26)
/* 80074260 00070E40  50 A4 2E B4 */	rlwimi r4, r5, 5, 0x1a, 0x1a
/* 80074264 00070E44  54 60 02 D7 */	rlwinm. r0, r3, 0, 0xb, 0xb
/* 80074268 00070E48  98 9A 00 09 */	stb r4, 9(r26)
/* 8007426C 00070E4C  41 82 00 0C */	beq lbl_80074278
/* 80074270 00070E50  38 80 00 01 */	li r4, 1
/* 80074274 00070E54  48 00 00 08 */	b lbl_8007427C
lbl_80074278:
/* 80074278 00070E58  38 80 00 00 */	li r4, 0
lbl_8007427C:
/* 8007427C 00070E5C  54 60 03 19 */	rlwinm. r0, r3, 0, 0xc, 0xc
/* 80074280 00070E60  88 7A 00 09 */	lbz r3, 9(r26)
/* 80074284 00070E64  50 83 26 F6 */	rlwimi r3, r4, 4, 0x1b, 0x1b
/* 80074288 00070E68  98 7A 00 09 */	stb r3, 9(r26)
/* 8007428C 00070E6C  41 82 00 0C */	beq lbl_80074298
/* 80074290 00070E70  38 00 00 01 */	li r0, 1
/* 80074294 00070E74  48 00 00 08 */	b lbl_8007429C
lbl_80074298:
/* 80074298 00070E78  38 00 00 00 */	li r0, 0
lbl_8007429C:
/* 8007429C 00070E7C  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 800742A0 00070E80  88 1A 00 09 */	lbz r0, 9(r26)
/* 800742A4 00070E84  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 800742A8 00070E88  98 1A 00 09 */	stb r0, 9(r26)
/* 800742AC 00070E8C  3C 60 80 3C */	lis r3, ftMObj@ha
/* 800742B0 00070E90  9B 9A 00 0C */	stb r28, 0xc(r26)
/* 800742B4 00070E94  3B 83 69 80 */	addi r28, r3, ftMObj@l
lbl_800742B8:
/* 800742B8 00070E98  28 1E 00 00 */	cmplwi r30, 0
/* 800742BC 00070E9C  41 82 00 94 */	beq lbl_80074350
/* 800742C0 00070EA0  80 1B 00 00 */	lwz r0, 0(r27)
/* 800742C4 00070EA4  2C 00 00 7C */	cmpwi r0, 0x7c
/* 800742C8 00070EA8  41 80 00 24 */	blt lbl_800742EC
/* 800742CC 00070EAC  88 99 00 0C */	lbz r4, 0xc(r25)
/* 800742D0 00070EB0  38 7F 01 48 */	addi r3, r31, 0x148
/* 800742D4 00070EB4  4C C6 31 82 */	crclr 6
/* 800742D8 00070EB8  48 2D 13 D1 */	bl OSReport
/* 800742DC 00070EBC  38 7F 01 10 */	addi r3, r31, 0x110
/* 800742E0 00070EC0  38 80 01 D2 */	li r4, 0x1d2
/* 800742E4 00070EC4  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 800742E8 00070EC8  48 31 3F 39 */	bl __assert
lbl_800742EC:
/* 800742EC 00070ECC  80 1B 00 00 */	lwz r0, 0(r27)
/* 800742F0 00070ED0  28 1E 00 00 */	cmplwi r30, 0
/* 800742F4 00070ED4  80 79 05 F0 */	lwz r3, 0x5f0(r25)
/* 800742F8 00070ED8  54 00 10 3A */	slwi r0, r0, 2
/* 800742FC 00070EDC  7F C3 01 2E */	stwx r30, r3, r0
/* 80074300 00070EE0  41 82 00 0C */	beq lbl_8007430C
/* 80074304 00070EE4  80 1E 00 08 */	lwz r0, 8(r30)
/* 80074308 00070EE8  48 00 00 08 */	b lbl_80074310
lbl_8007430C:
/* 8007430C 00070EEC  38 00 00 00 */	li r0, 0
lbl_80074310:
/* 80074310 00070EF0  28 00 00 00 */	cmplwi r0, 0
/* 80074314 00070EF4  7C 03 03 78 */	mr r3, r0
/* 80074318 00070EF8  41 82 00 0C */	beq lbl_80074324
/* 8007431C 00070EFC  7F 84 E3 78 */	mr r4, r28
/* 80074320 00070F00  48 30 E0 E1 */	bl hsdChangeClass
lbl_80074324:
/* 80074324 00070F04  28 1E 00 00 */	cmplwi r30, 0
/* 80074328 00070F08  41 82 00 0C */	beq lbl_80074334
/* 8007432C 00070F0C  80 1E 00 04 */	lwz r0, 4(r30)
/* 80074330 00070F10  48 00 00 08 */	b lbl_80074338
lbl_80074334:
/* 80074334 00070F14  38 00 00 00 */	li r0, 0
lbl_80074338:
/* 80074338 00070F18  80 7B 00 00 */	lwz r3, 0(r27)
/* 8007433C 00070F1C  7C 1E 03 78 */	mr r30, r0
/* 80074340 00070F20  3B BD 00 01 */	addi r29, r29, 1
/* 80074344 00070F24  38 03 00 01 */	addi r0, r3, 1
/* 80074348 00070F28  90 1B 00 00 */	stw r0, 0(r27)
/* 8007434C 00070F2C  4B FF FF 6C */	b lbl_800742B8
lbl_80074350:
/* 80074350 00070F30  2C 1D 00 80 */	cmpwi r29, 0x80
/* 80074354 00070F34  41 80 00 24 */	blt lbl_80074378
/* 80074358 00070F38  88 99 00 0C */	lbz r4, 0xc(r25)
/* 8007435C 00070F3C  38 7F 01 78 */	addi r3, r31, 0x178
/* 80074360 00070F40  4C C6 31 82 */	crclr 6
/* 80074364 00070F44  48 2D 13 45 */	bl OSReport
/* 80074368 00070F48  38 7F 01 10 */	addi r3, r31, 0x110
/* 8007436C 00070F4C  38 80 01 E0 */	li r4, 0x1e0
/* 80074370 00070F50  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 80074374 00070F54  48 31 3E AD */	bl __assert
lbl_80074378:
/* 80074378 00070F58  80 7B 00 00 */	lwz r3, 0(r27)
/* 8007437C 00070F5C  2C 03 00 00 */	cmpwi r3, 0
/* 80074380 00070F60  41 82 00 18 */	beq lbl_80074398
/* 80074384 00070F64  38 63 FF FF */	addi r3, r3, -1
/* 80074388 00070F68  88 1A 00 0D */	lbz r0, 0xd(r26)
/* 8007438C 00070F6C  50 60 0E 3C */	rlwimi r0, r3, 1, 0x18, 0x1e
/* 80074390 00070F70  98 1A 00 0D */	stb r0, 0xd(r26)
/* 80074394 00070F74  48 00 00 14 */	b lbl_800743A8
lbl_80074398:
/* 80074398 00070F78  88 1A 00 0D */	lbz r0, 0xd(r26)
/* 8007439C 00070F7C  38 60 00 00 */	li r3, 0
/* 800743A0 00070F80  50 60 0E 3C */	rlwimi r0, r3, 1, 0x18, 0x1e
/* 800743A4 00070F84  98 1A 00 0D */	stb r0, 0xd(r26)
lbl_800743A8:
/* 800743A8 00070F88  2C 1D 00 00 */	cmpwi r29, 0
/* 800743AC 00070F8C  41 82 00 0C */	beq lbl_800743B8
/* 800743B0 00070F90  38 00 00 01 */	li r0, 1
/* 800743B4 00070F94  48 00 00 08 */	b lbl_800743BC
lbl_800743B8:
/* 800743B8 00070F98  38 00 00 00 */	li r0, 0
lbl_800743BC:
/* 800743BC 00070F9C  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 800743C0 00070FA0  88 1A 00 09 */	lbz r0, 9(r26)
/* 800743C4 00070FA4  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 800743C8 00070FA8  98 1A 00 09 */	stb r0, 9(r26)
/* 800743CC 00070FAC  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800743D0 00070FB0  BB 21 00 2C */	lmw r25, 0x2c(r1)
/* 800743D4 00070FB4  38 21 00 48 */	addi r1, r1, 0x48
/* 800743D8 00070FB8  7C 08 03 A6 */	mtlr r0
/* 800743DC 00070FBC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

void Fighter_SetupParts(HSD_GObj* fighter_obj)
{
    HSD_JObj* jobj = fighter_obj->hsd_obj;
    Fighter* fighter = (Fighter*) fighter_obj->user_data;
    u32 part = 0;
    u32 tree_depth = 0;
    u32 dobj_count = 0;

    if (ftPartsTable[fighter->x4_fighterKind]->parts_num > MAX_FT_PARTS) {
        OSReport(lbl_803C0A94, fighter->xC_playerID);
        __assert(lbl_803C0A08, 503, lbl_804D3A58);
    }

    while (jobj != NULL) {
        if (func_8007506C(fighter->x4_fighterKind, part) != 0) {
            fighter->x5E8_fighterBones[part].x0_jobj = NULL;
            part++;
            continue;
        }

        func_80074194(fighter, &fighter->x5E8_fighterBones[part], jobj,
                      &dobj_count, tree_depth);
        part++;

        if (!(HSD_JObjGetFlags(jobj) & JOBJ_INSTANCE) &&
            JOBJ_CHILD(jobj) != NULL)
        {
            // Descend the left side of the tree
            jobj = JOBJ_CHILD(jobj);
            tree_depth++;
            continue;
        }

        if (JOBJ_NEXT(jobj) != NULL) {
            // Visit bottom nodes from left to right
            jobj = JOBJ_NEXT(jobj);
            continue;
        }

        while (TRUE) {
            if (JOBJ_PARENT(jobj) == NULL) {
                // Finished
                jobj = NULL;
                break;
            } else {
                // Go back up the tree until we can continue to the right
                HSD_JObj* parent = JOBJ_PARENT(jobj);
                HSD_JObj* parent_next = JOBJ_NEXT(parent);

                if (parent_next != NULL) {
                    jobj = JOBJ_PARENT(jobj);
                    jobj = JOBJ_NEXT(jobj);
                    tree_depth--;
                    break;
                }

                jobj = JOBJ_PARENT(jobj);
                tree_depth--;
            }
        }
    }

    fighter->x5EC_dobj_list.count = dobj_count;

    if (part != ftPartsTable[fighter->x4_fighterKind]->parts_num) {
        OSReport(lbl_803C0AB8, fighter->xC_playerID);
        __assert(lbl_803C0A08, 546, lbl_804D3A58);
    }
}

#pragma push
asm unk_t func_8007462C()
{ // clang-format off
    nofralloc
/* 8007462C 0007120C  7C 08 02 A6 */	mflr r0
/* 80074630 00071210  90 01 00 04 */	stw r0, 4(r1)
/* 80074634 00071214  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80074638 00071218  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007463C 0007121C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80074640 00071220  3B C0 00 00 */	li r30, 0
/* 80074644 00071224  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80074648 00071228  3B A0 00 00 */	li r29, 0
/* 8007464C 0007122C  93 81 00 10 */	stw r28, 0x10(r1)
/* 80074650 00071230  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80074654 00071234  83 9F 08 AC */	lwz r28, 0x8ac(r31)
/* 80074658 00071238  48 00 01 68 */	b lbl_800747C0
lbl_8007465C:
/* 8007465C 0007123C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80074660 00071240  7F C4 F3 78 */	mr r4, r30
/* 80074664 00071244  48 00 0A 09 */	bl func_8007506C
/* 80074668 00071248  28 03 00 00 */	cmplwi r3, 0
/* 8007466C 0007124C  41 82 00 20 */	beq lbl_8007468C
/* 80074670 00071250  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 80074674 00071254  38 1D 00 04 */	addi r0, r29, 4
/* 80074678 00071258  38 80 00 00 */	li r4, 0
/* 8007467C 0007125C  7C 83 01 2E */	stwx r4, r3, r0
/* 80074680 00071260  3B DE 00 01 */	addi r30, r30, 1
/* 80074684 00071264  3B BD 00 10 */	addi r29, r29, 0x10
/* 80074688 00071268  48 00 01 38 */	b lbl_800747C0
lbl_8007468C:
/* 8007468C 0007126C  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80074690 00071270  38 1D 00 04 */	addi r0, r29, 4
/* 80074694 00071274  38 7C 00 00 */	addi r3, r28, 0
/* 80074698 00071278  7F 84 01 2E */	stwx r28, r4, r0
/* 8007469C 0007127C  3B DE 00 01 */	addi r30, r30, 1
/* 800746A0 00071280  3B BD 00 10 */	addi r29, r29, 0x10
/* 800746A4 00071284  48 2F D6 45 */	bl HSD_JObjGetFlags
/* 800746A8 00071288  54 60 04 E7 */	rlwinm. r0, r3, 0, 0x13, 0x13
/* 800746AC 0007128C  40 82 00 3C */	bne lbl_800746E8
/* 800746B0 00071290  28 1C 00 00 */	cmplwi r28, 0
/* 800746B4 00071294  40 82 00 0C */	bne lbl_800746C0
/* 800746B8 00071298  38 00 00 00 */	li r0, 0
/* 800746BC 0007129C  48 00 00 08 */	b lbl_800746C4
lbl_800746C0:
/* 800746C0 000712A0  80 1C 00 10 */	lwz r0, 0x10(r28)
lbl_800746C4:
/* 800746C4 000712A4  28 00 00 00 */	cmplwi r0, 0
/* 800746C8 000712A8  41 82 00 20 */	beq lbl_800746E8
/* 800746CC 000712AC  28 1C 00 00 */	cmplwi r28, 0
/* 800746D0 000712B0  40 82 00 0C */	bne lbl_800746DC
/* 800746D4 000712B4  38 00 00 00 */	li r0, 0
/* 800746D8 000712B8  48 00 00 08 */	b lbl_800746E0
lbl_800746DC:
/* 800746DC 000712BC  80 1C 00 10 */	lwz r0, 0x10(r28)
lbl_800746E0:
/* 800746E0 000712C0  7C 1C 03 78 */	mr r28, r0
/* 800746E4 000712C4  48 00 00 DC */	b lbl_800747C0
lbl_800746E8:
/* 800746E8 000712C8  28 1C 00 00 */	cmplwi r28, 0
/* 800746EC 000712CC  40 82 00 0C */	bne lbl_800746F8
/* 800746F0 000712D0  38 00 00 00 */	li r0, 0
/* 800746F4 000712D4  48 00 00 08 */	b lbl_800746FC
lbl_800746F8:
/* 800746F8 000712D8  80 1C 00 08 */	lwz r0, 8(r28)
lbl_800746FC:
/* 800746FC 000712DC  28 00 00 00 */	cmplwi r0, 0
/* 80074700 000712E0  41 82 00 20 */	beq lbl_80074720
/* 80074704 000712E4  28 1C 00 00 */	cmplwi r28, 0
/* 80074708 000712E8  40 82 00 0C */	bne lbl_80074714
/* 8007470C 000712EC  38 00 00 00 */	li r0, 0
/* 80074710 000712F0  48 00 00 08 */	b lbl_80074718
lbl_80074714:
/* 80074714 000712F4  80 1C 00 08 */	lwz r0, 8(r28)
lbl_80074718:
/* 80074718 000712F8  7C 1C 03 78 */	mr r28, r0
/* 8007471C 000712FC  48 00 00 A4 */	b lbl_800747C0
lbl_80074720:
/* 80074720 00071300  28 1C 00 00 */	cmplwi r28, 0
/* 80074724 00071304  40 82 00 0C */	bne lbl_80074730
/* 80074728 00071308  38 00 00 00 */	li r0, 0
/* 8007472C 0007130C  48 00 00 08 */	b lbl_80074734
lbl_80074730:
/* 80074730 00071310  80 1C 00 0C */	lwz r0, 0xc(r28)
lbl_80074734:
/* 80074734 00071314  28 00 00 00 */	cmplwi r0, 0
/* 80074738 00071318  40 82 00 0C */	bne lbl_80074744
/* 8007473C 0007131C  3B 80 00 00 */	li r28, 0
/* 80074740 00071320  48 00 00 80 */	b lbl_800747C0
lbl_80074744:
/* 80074744 00071324  28 1C 00 00 */	cmplwi r28, 0
/* 80074748 00071328  40 82 00 0C */	bne lbl_80074754
/* 8007474C 0007132C  38 60 00 00 */	li r3, 0
/* 80074750 00071330  48 00 00 08 */	b lbl_80074758
lbl_80074754:
/* 80074754 00071334  80 7C 00 0C */	lwz r3, 0xc(r28)
lbl_80074758:
/* 80074758 00071338  28 03 00 00 */	cmplwi r3, 0
/* 8007475C 0007133C  40 82 00 0C */	bne lbl_80074768
/* 80074760 00071340  38 00 00 00 */	li r0, 0
/* 80074764 00071344  48 00 00 08 */	b lbl_8007476C
lbl_80074768:
/* 80074768 00071348  80 03 00 08 */	lwz r0, 8(r3)
lbl_8007476C:
/* 8007476C 0007134C  28 00 00 00 */	cmplwi r0, 0
/* 80074770 00071350  41 82 00 34 */	beq lbl_800747A4
/* 80074774 00071354  28 1C 00 00 */	cmplwi r28, 0
/* 80074778 00071358  40 82 00 0C */	bne lbl_80074784
/* 8007477C 0007135C  38 60 00 00 */	li r3, 0
/* 80074780 00071360  48 00 00 08 */	b lbl_80074788
lbl_80074784:
/* 80074784 00071364  80 7C 00 0C */	lwz r3, 0xc(r28)
lbl_80074788:
/* 80074788 00071368  28 03 00 00 */	cmplwi r3, 0
/* 8007478C 0007136C  40 82 00 0C */	bne lbl_80074798
/* 80074790 00071370  38 00 00 00 */	li r0, 0
/* 80074794 00071374  48 00 00 08 */	b lbl_8007479C
lbl_80074798:
/* 80074798 00071378  80 03 00 08 */	lwz r0, 8(r3)
lbl_8007479C:
/* 8007479C 0007137C  7C 1C 03 78 */	mr r28, r0
/* 800747A0 00071380  48 00 00 20 */	b lbl_800747C0
lbl_800747A4:
/* 800747A4 00071384  28 1C 00 00 */	cmplwi r28, 0
/* 800747A8 00071388  40 82 00 0C */	bne lbl_800747B4
/* 800747AC 0007138C  38 00 00 00 */	li r0, 0
/* 800747B0 00071390  48 00 00 08 */	b lbl_800747B8
lbl_800747B4:
/* 800747B4 00071394  80 1C 00 0C */	lwz r0, 0xc(r28)
lbl_800747B8:
/* 800747B8 00071398  7C 1C 03 78 */	mr r28, r0
/* 800747BC 0007139C  4B FF FF 64 */	b lbl_80074720
lbl_800747C0:
/* 800747C0 000713A0  28 1C 00 00 */	cmplwi r28, 0
/* 800747C4 000713A4  40 82 FE 98 */	bne lbl_8007465C
/* 800747C8 000713A8  80 1F 00 04 */	lwz r0, 4(r31)
/* 800747CC 000713AC  80 6D AE A4 */	lwz r3, ftPartsTable(r13)
/* 800747D0 000713B0  54 00 10 3A */	slwi r0, r0, 2
/* 800747D4 000713B4  7C 63 00 2E */	lwzx r3, r3, r0
/* 800747D8 000713B8  80 03 00 08 */	lwz r0, 8(r3)
/* 800747DC 000713BC  7C 1E 00 40 */	cmplw r30, r0
/* 800747E0 000713C0  41 82 00 2C */	beq lbl_8007480C
/* 800747E4 000713C4  3C 60 80 3C */	lis r3, lbl_803C0AB8@ha
/* 800747E8 000713C8  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 800747EC 000713CC  38 63 0A B8 */	addi r3, r3, lbl_803C0AB8@l
/* 800747F0 000713D0  4C C6 31 82 */	crclr 6
/* 800747F4 000713D4  48 2D 0E B5 */	bl OSReport
/* 800747F8 000713D8  3C 60 80 3C */	lis r3, lbl_803C0A08@ha
/* 800747FC 000713DC  38 63 0A 08 */	addi r3, r3, lbl_803C0A08@l
/* 80074800 000713E0  38 80 02 51 */	li r4, 0x251
/* 80074804 000713E4  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 80074808 000713E8  48 31 3A 19 */	bl __assert
lbl_8007480C:
/* 8007480C 000713EC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80074810 000713F0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80074814 000713F4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80074818 000713F8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8007481C 000713FC  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80074820 00071400  38 21 00 20 */	addi r1, r1, 0x20
/* 80074824 00071404  7C 08 03 A6 */	mtlr r0
/* 80074828 00071408  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8007482C()
{ // clang-format off
    nofralloc
/* 8007482C 0007140C  7C 08 02 A6 */	mflr r0
/* 80074830 00071410  3C 80 80 3C */	lis r4, ftIntpJObj@ha
/* 80074834 00071414  90 01 00 04 */	stw r0, 4(r1)
/* 80074838 00071418  38 04 09 48 */	addi r0, r4, ftIntpJObj@l
/* 8007483C 0007141C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80074840 00071420  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80074844 00071424  3B E3 00 00 */	addi r31, r3, 0
/* 80074848 00071428  7C 03 03 78 */	mr r3, r0
/* 8007484C 0007142C  48 2F C3 45 */	bl HSD_JObjSetDefaultClass
/* 80074850 00071430  7F E3 FB 78 */	mr r3, r31
/* 80074854 00071434  48 2F C5 F1 */	bl HSD_JObjLoadJoint
/* 80074858 00071438  3B E3 00 00 */	addi r31, r3, 0
/* 8007485C 0007143C  38 60 00 00 */	li r3, 0
/* 80074860 00071440  48 2F C3 31 */	bl HSD_JObjSetDefaultClass
/* 80074864 00071444  7F E3 FB 78 */	mr r3, r31
/* 80074868 00071448  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007486C 0007144C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80074870 00071450  38 21 00 18 */	addi r1, r1, 0x18
/* 80074874 00071454  7C 08 03 A6 */	mtlr r0
/* 80074878 00071458  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_8007487C(unk_t item, u32*, u8 costume_id, u32*, u32*)
{ // clang-format off
    nofralloc
/* 8007487C 0007145C  7C 08 02 A6 */	mflr r0
/* 80074880 00071460  90 01 00 04 */	stw r0, 4(r1)
/* 80074884 00071464  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80074888 00071468  BF 61 00 2C */	stmw r27, 0x2c(r1)
/* 8007488C 0007146C  7C 9C 23 78 */	mr r28, r4
/* 80074890 00071470  3B 65 00 00 */	addi r27, r5, 0
/* 80074894 00071474  3B A6 00 00 */	addi r29, r6, 0
/* 80074898 00071478  7C FE 3B 78 */	mr r30, r7
/* 8007489C 0007147C  83 E3 00 04 */	lwz r31, 4(r3)
/* 800748A0 00071480  80 03 00 00 */	lwz r0, 0(r3)
/* 800748A4 00071484  90 04 00 00 */	stw r0, 0(r4)
/* 800748A8 00071488  80 04 00 00 */	lwz r0, 0(r4)
/* 800748AC 0007148C  28 00 00 0B */	cmplwi r0, 0xb
/* 800748B0 00071490  40 81 00 28 */	ble lbl_800748D8
/* 800748B4 00071494  3C 60 80 3C */	lis r3, lbl_803C0AE0@ha
/* 800748B8 00071498  4C C6 31 82 */	crclr 6
/* 800748BC 0007149C  38 63 0A E0 */	addi r3, r3, lbl_803C0AE0@l
/* 800748C0 000714A0  48 2D 0D E9 */	bl OSReport
/* 800748C4 000714A4  3C 60 80 3C */	lis r3, lbl_803C0A08@ha
/* 800748C8 000714A8  38 63 0A 08 */	addi r3, r3, lbl_803C0A08@l
/* 800748CC 000714AC  38 80 02 73 */	li r4, 0x273
/* 800748D0 000714B0  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 800748D4 000714B4  48 31 39 4D */	bl __assert
lbl_800748D8:
/* 800748D8 000714B8  57 64 20 36 */	slwi r4, r27, 4
/* 800748DC 000714BC  7C 1F 20 2E */	lwzx r0, r31, r4
/* 800748E0 000714C0  28 00 00 00 */	cmplwi r0, 0
/* 800748E4 000714C4  41 82 00 08 */	beq lbl_800748EC
/* 800748E8 000714C8  48 00 00 08 */	b lbl_800748F0
lbl_800748EC:
/* 800748EC 000714CC  80 1F 00 00 */	lwz r0, 0(r31)
lbl_800748F0:
/* 800748F0 000714D0  90 1C 00 0C */	stw r0, 0xc(r28)
/* 800748F4 000714D4  7C 7F 22 14 */	add r3, r31, r4
/* 800748F8 000714D8  80 03 00 04 */	lwz r0, 4(r3)
/* 800748FC 000714DC  28 00 00 00 */	cmplwi r0, 0
/* 80074900 000714E0  41 82 00 08 */	beq lbl_80074908
/* 80074904 000714E4  48 00 00 08 */	b lbl_8007490C
lbl_80074908:
/* 80074908 000714E8  80 1F 00 04 */	lwz r0, 4(r31)
lbl_8007490C:
/* 8007490C 000714EC  90 1C 00 10 */	stw r0, 0x10(r28)
/* 80074910 000714F0  7C 7F 22 14 */	add r3, r31, r4
/* 80074914 000714F4  80 03 00 08 */	lwz r0, 8(r3)
/* 80074918 000714F8  28 00 00 00 */	cmplwi r0, 0
/* 8007491C 000714FC  41 82 00 08 */	beq lbl_80074924
/* 80074920 00071500  48 00 00 08 */	b lbl_80074928
lbl_80074924:
/* 80074924 00071504  80 1F 00 08 */	lwz r0, 8(r31)
lbl_80074928:
/* 80074928 00071508  90 1C 00 14 */	stw r0, 0x14(r28)
/* 8007492C 0007150C  7C 7F 22 14 */	add r3, r31, r4
/* 80074930 00071510  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80074934 00071514  28 00 00 00 */	cmplwi r0, 0
/* 80074938 00071518  41 82 00 08 */	beq lbl_80074940
/* 8007493C 0007151C  48 00 00 08 */	b lbl_80074944
lbl_80074940:
/* 80074940 00071520  80 1F 00 0C */	lwz r0, 0xc(r31)
lbl_80074944:
/* 80074944 00071524  90 1C 00 18 */	stw r0, 0x18(r28)
/* 80074948 00071528  38 60 00 00 */	li r3, 0
/* 8007494C 0007152C  38 00 00 01 */	li r0, 1
/* 80074950 00071530  90 7C 00 1C */	stw r3, 0x1c(r28)
/* 80074954 00071534  38 7C 00 00 */	addi r3, r28, 0
/* 80074958 00071538  38 BD 00 00 */	addi r5, r29, 0
/* 8007495C 0007153C  98 1C 00 04 */	stb r0, 4(r28)
/* 80074960 00071540  38 80 00 00 */	li r4, 0
/* 80074964 00071544  98 1C 00 05 */	stb r0, 5(r28)
/* 80074968 00071548  98 1C 00 06 */	stb r0, 6(r28)
/* 8007496C 0007154C  98 1C 00 07 */	stb r0, 7(r28)
/* 80074970 00071550  98 1C 00 08 */	stb r0, 8(r28)
/* 80074974 00071554  48 00 04 09 */	bl func_80074D7C
/* 80074978 00071558  38 7C 00 00 */	addi r3, r28, 0
/* 8007497C 0007155C  38 BD 00 00 */	addi r5, r29, 0
/* 80074980 00071560  38 80 00 01 */	li r4, 1
/* 80074984 00071564  48 00 03 F9 */	bl func_80074D7C
/* 80074988 00071568  38 7C 00 00 */	addi r3, r28, 0
/* 8007498C 0007156C  38 BE 00 00 */	addi r5, r30, 0
/* 80074990 00071570  38 80 00 02 */	li r4, 2
/* 80074994 00071574  48 00 03 E9 */	bl func_80074D7C
/* 80074998 00071578  38 7C 00 00 */	addi r3, r28, 0
/* 8007499C 0007157C  38 BD 00 00 */	addi r5, r29, 0
/* 800749A0 00071580  38 80 00 03 */	li r4, 3
/* 800749A4 00071584  48 00 03 D9 */	bl func_80074D7C
/* 800749A8 00071588  38 7C 00 00 */	addi r3, r28, 0
/* 800749AC 0007158C  38 BD 00 00 */	addi r5, r29, 0
/* 800749B0 00071590  38 80 00 04 */	li r4, 4
/* 800749B4 00071594  48 00 03 C9 */	bl func_80074D7C
/* 800749B8 00071598  BB 61 00 2C */	lmw r27, 0x2c(r1)
/* 800749BC 0007159C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800749C0 000715A0  38 21 00 40 */	addi r1, r1, 0x40
/* 800749C4 000715A4  7C 08 03 A6 */	mtlr r0
/* 800749C8 000715A8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_800749CC()
{ // clang-format off
    nofralloc
/* 800749CC 000715AC  7C 08 02 A6 */	mflr r0
/* 800749D0 000715B0  90 01 00 04 */	stw r0, 4(r1)
/* 800749D4 000715B4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800749D8 000715B8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800749DC 000715BC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800749E0 000715C0  7C 7E 1B 78 */	mr r30, r3
/* 800749E4 000715C4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800749E8 000715C8  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 800749EC 000715CC  38 9F 05 AC */	addi r4, r31, 0x5ac
/* 800749F0 000715D0  88 BF 06 19 */	lbz r5, 0x619(r31)
/* 800749F4 000715D4  38 DF 05 EC */	addi r6, r31, 0x5ec
/* 800749F8 000715D8  80 63 00 08 */	lwz r3, 8(r3)
/* 800749FC 000715DC  38 FF 20 3C */	addi r7, r31, 0x203c
/* 80074A00 000715E0  4B FF FE 7D */	bl func_8007487C
/* 80074A04 000715E4  38 9F 00 00 */	addi r4, r31, 0
/* 80074A08 000715E8  38 A0 00 00 */	li r5, 0
/* 80074A0C 000715EC  38 60 FF FF */	li r3, -1
/* 80074A10 000715F0  48 00 00 10 */	b lbl_80074A20
lbl_80074A14:
/* 80074A14 000715F4  98 64 05 F4 */	stb r3, 0x5f4(r4)
/* 80074A18 000715F8  38 84 00 02 */	addi r4, r4, 2
/* 80074A1C 000715FC  38 A5 00 01 */	addi r5, r5, 1
lbl_80074A20:
/* 80074A20 00071600  80 1F 05 AC */	lwz r0, 0x5ac(r31)
/* 80074A24 00071604  7C 05 00 40 */	cmplw r5, r0
/* 80074A28 00071608  41 80 FF EC */	blt lbl_80074A14
/* 80074A2C 0007160C  7F C3 F3 78 */	mr r3, r30
/* 80074A30 00071610  48 00 00 9D */	bl func_80074ACC
/* 80074A34 00071614  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80074A38 00071618  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80074A3C 0007161C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80074A40 00071620  38 21 00 18 */	addi r1, r1, 0x18
/* 80074A44 00071624  7C 08 03 A6 */	mtlr r0
/* 80074A48 00071628  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80074A4C(struct _HSD_GObj*, u32, s32)
{ // clang-format off
    nofralloc
/* 80074A4C 0007162C  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80074A50 00071630  54 80 08 3C */	slwi r0, r4, 1
/* 80074A54 00071634  7C A4 07 74 */	extsb r4, r5
/* 80074A58 00071638  7C 66 02 14 */	add r3, r6, r0
/* 80074A5C 0007163C  98 83 05 F4 */	stb r4, 0x5f4(r3)
/* 80074A60 00071640  38 60 00 01 */	li r3, 1
/* 80074A64 00071644  88 06 22 1D */	lbz r0, 0x221d(r6)
/* 80074A68 00071648  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80074A6C 0007164C  98 06 22 1D */	stb r0, 0x221d(r6)
/* 80074A70 00071650  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm s32 func_80074A74(HSD_GObj*, s32)
{ // clang-format off
    nofralloc
/* 80074A74 00071654  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80074A78 00071658  54 80 08 3C */	slwi r0, r4, 1
/* 80074A7C 0007165C  7C 63 02 14 */	add r3, r3, r0
/* 80074A80 00071660  88 63 05 F4 */	lbz r3, 0x5f4(r3)
/* 80074A84 00071664  7C 63 07 74 */	extsb r3, r3
/* 80074A88 00071668  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80074A8C()
{ // clang-format off
    nofralloc
/* 80074A8C 0007166C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80074A90 00071670  38 A0 00 00 */	li r5, 0
/* 80074A94 00071674  38 64 00 00 */	addi r3, r4, 0
/* 80074A98 00071678  48 00 00 14 */	b lbl_80074AAC
lbl_80074A9C:
/* 80074A9C 0007167C  88 03 05 F4 */	lbz r0, 0x5f4(r3)
/* 80074AA0 00071680  38 A5 00 01 */	addi r5, r5, 1
/* 80074AA4 00071684  98 03 05 F5 */	stb r0, 0x5f5(r3)
/* 80074AA8 00071688  38 63 00 02 */	addi r3, r3, 2
lbl_80074AAC:
/* 80074AAC 0007168C  80 04 05 AC */	lwz r0, 0x5ac(r4)
/* 80074AB0 00071690  7C 05 00 40 */	cmplw r5, r0
/* 80074AB4 00071694  41 80 FF E8 */	blt lbl_80074A9C
/* 80074AB8 00071698  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 80074ABC 0007169C  38 60 00 00 */	li r3, 0
/* 80074AC0 000716A0  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80074AC4 000716A4  98 04 22 1D */	stb r0, 0x221d(r4)
/* 80074AC8 000716A8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80074ACC()
{ // clang-format off
    nofralloc
/* 80074ACC 000716AC  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 80074AD0 000716B0  38 C0 00 00 */	li r6, 0
/* 80074AD4 000716B4  38 60 FF FF */	li r3, -1
/* 80074AD8 000716B8  38 85 00 00 */	addi r4, r5, 0
/* 80074ADC 000716BC  48 00 00 10 */	b lbl_80074AEC
lbl_80074AE0:
/* 80074AE0 000716C0  98 64 05 F5 */	stb r3, 0x5f5(r4)
/* 80074AE4 000716C4  38 84 00 02 */	addi r4, r4, 2
/* 80074AE8 000716C8  38 C6 00 01 */	addi r6, r6, 1
lbl_80074AEC:
/* 80074AEC 000716CC  80 05 05 AC */	lwz r0, 0x5ac(r5)
/* 80074AF0 000716D0  7C 06 00 40 */	cmplw r6, r0
/* 80074AF4 000716D4  41 80 FF EC */	blt lbl_80074AE0
/* 80074AF8 000716D8  88 05 22 1D */	lbz r0, 0x221d(r5)
/* 80074AFC 000716DC  38 60 00 00 */	li r3, 0
/* 80074B00 000716E0  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80074B04 000716E4  98 05 22 1D */	stb r0, 0x221d(r5)
/* 80074B08 000716E8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80074B0C(HSD_GObj*, s32, s32)
{ // clang-format off
    nofralloc
/* 80074B0C 000716EC  7C 08 02 A6 */	mflr r0
/* 80074B10 000716F0  90 01 00 04 */	stw r0, 4(r1)
/* 80074B14 000716F4  54 80 08 3C */	slwi r0, r4, 1
/* 80074B18 000716F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80074B1C 000716FC  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80074B20 00071700  7C 66 02 14 */	add r3, r6, r0
/* 80074B24 00071704  88 03 05 F5 */	lbz r0, 0x5f5(r3)
/* 80074B28 00071708  7C 00 07 74 */	extsb r0, r0
/* 80074B2C 0007170C  7C 05 00 00 */	cmpw r5, r0
/* 80074B30 00071710  41 82 00 2C */	beq lbl_80074B5C
/* 80074B34 00071714  7C A0 07 74 */	extsb r0, r5
/* 80074B38 00071718  98 03 05 F5 */	stb r0, 0x5f5(r3)
/* 80074B3C 0007171C  38 80 00 01 */	li r4, 1
/* 80074B40 00071720  38 66 05 AC */	addi r3, r6, 0x5ac
/* 80074B44 00071724  88 06 22 1D */	lbz r0, 0x221d(r6)
/* 80074B48 00071728  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 80074B4C 0007172C  38 A6 05 EC */	addi r5, r6, 0x5ec
/* 80074B50 00071730  98 06 22 1D */	stb r0, 0x221d(r6)
/* 80074B54 00071734  38 80 00 00 */	li r4, 0
/* 80074B58 00071738  48 00 02 25 */	bl func_80074D7C
lbl_80074B5C:
/* 80074B5C 0007173C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80074B60 00071740  38 21 00 08 */	addi r1, r1, 8
/* 80074B64 00071744  7C 08 03 A6 */	mtlr r0
/* 80074B68 00071748  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80074B6C()
{ // clang-format off
    nofralloc
/* 80074B6C 0007174C  7C 08 02 A6 */	mflr r0
/* 80074B70 00071750  90 01 00 04 */	stw r0, 4(r1)
/* 80074B74 00071754  54 A0 10 3A */	slwi r0, r5, 2
/* 80074B78 00071758  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80074B7C 0007175C  BE 81 00 18 */	stmw r20, 0x18(r1)
/* 80074B80 00071760  3A C4 00 00 */	addi r22, r4, 0
/* 80074B84 00071764  7C 96 02 14 */	add r4, r22, r0
/* 80074B88 00071768  3A E6 00 00 */	addi r23, r6, 0
/* 80074B8C 0007176C  80 04 00 0C */	lwz r0, 0xc(r4)
/* 80074B90 00071770  28 00 00 00 */	cmplwi r0, 0
/* 80074B94 00071774  7C 04 03 78 */	mr r4, r0
/* 80074B98 00071778  41 82 00 F4 */	beq lbl_80074C8C
/* 80074B9C 0007177C  7F F6 2A 14 */	add r31, r22, r5
/* 80074BA0 00071780  88 1F 00 04 */	lbz r0, 4(r31)
/* 80074BA4 00071784  28 00 00 00 */	cmplwi r0, 0
/* 80074BA8 00071788  40 82 00 E4 */	bne lbl_80074C8C
/* 80074BAC 0007178C  3B A3 00 00 */	addi r29, r3, 0
/* 80074BB0 00071790  3B 84 00 00 */	addi r28, r4, 0
/* 80074BB4 00071794  3B 40 00 00 */	li r26, 0
/* 80074BB8 00071798  48 00 00 C8 */	b lbl_80074C80
lbl_80074BBC:
/* 80074BBC 0007179C  8B 3D 05 F5 */	lbz r25, 0x5f5(r29)
/* 80074BC0 000717A0  3B 00 00 00 */	li r24, 0
/* 80074BC4 000717A4  3B C0 00 00 */	li r30, 0
/* 80074BC8 000717A8  7F 39 07 74 */	extsb r25, r25
/* 80074BCC 000717AC  48 00 00 94 */	b lbl_80074C60
lbl_80074BD0:
/* 80074BD0 000717B0  80 1C 00 04 */	lwz r0, 4(r28)
/* 80074BD4 000717B4  7C 18 C8 00 */	cmpw r24, r25
/* 80074BD8 000717B8  7F 60 F2 14 */	add r27, r0, r30
/* 80074BDC 000717BC  80 1B 00 04 */	lwz r0, 4(r27)
/* 80074BE0 000717C0  40 82 00 40 */	bne lbl_80074C20
/* 80074BE4 000717C4  7C 15 03 78 */	mr r21, r0
/* 80074BE8 000717C8  3A 80 00 00 */	li r20, 0
/* 80074BEC 000717CC  48 00 00 24 */	b lbl_80074C10
lbl_80074BF0:
/* 80074BF0 000717D0  88 15 00 00 */	lbz r0, 0(r21)
/* 80074BF4 000717D4  38 80 00 01 */	li r4, 1
/* 80074BF8 000717D8  80 77 00 04 */	lwz r3, 4(r23)
/* 80074BFC 000717DC  54 00 10 3A */	slwi r0, r0, 2
/* 80074C00 000717E0  7C 63 00 2E */	lwzx r3, r3, r0
/* 80074C04 000717E4  48 2E 91 CD */	bl HSD_DObjClearFlags
/* 80074C08 000717E8  3A 94 00 01 */	addi r20, r20, 1
/* 80074C0C 000717EC  3A B5 00 01 */	addi r21, r21, 1
lbl_80074C10:
/* 80074C10 000717F0  80 1B 00 00 */	lwz r0, 0(r27)
/* 80074C14 000717F4  7C 14 00 00 */	cmpw r20, r0
/* 80074C18 000717F8  41 80 FF D8 */	blt lbl_80074BF0
/* 80074C1C 000717FC  48 00 00 3C */	b lbl_80074C58
lbl_80074C20:
/* 80074C20 00071800  7C 15 03 78 */	mr r21, r0
/* 80074C24 00071804  3A 80 00 00 */	li r20, 0
/* 80074C28 00071808  48 00 00 24 */	b lbl_80074C4C
lbl_80074C2C:
/* 80074C2C 0007180C  88 15 00 00 */	lbz r0, 0(r21)
/* 80074C30 00071810  38 80 00 01 */	li r4, 1
/* 80074C34 00071814  80 77 00 04 */	lwz r3, 4(r23)
/* 80074C38 00071818  54 00 10 3A */	slwi r0, r0, 2
/* 80074C3C 0007181C  7C 63 00 2E */	lwzx r3, r3, r0
/* 80074C40 00071820  48 2E 91 79 */	bl HSD_DObjSetFlags
/* 80074C44 00071824  3A 94 00 01 */	addi r20, r20, 1
/* 80074C48 00071828  3A B5 00 01 */	addi r21, r21, 1
lbl_80074C4C:
/* 80074C4C 0007182C  80 1B 00 00 */	lwz r0, 0(r27)
/* 80074C50 00071830  7C 14 00 00 */	cmpw r20, r0
/* 80074C54 00071834  41 80 FF D8 */	blt lbl_80074C2C
lbl_80074C58:
/* 80074C58 00071838  3B DE 00 08 */	addi r30, r30, 8
/* 80074C5C 0007183C  3B 18 00 01 */	addi r24, r24, 1
lbl_80074C60:
/* 80074C60 00071840  80 1C 00 00 */	lwz r0, 0(r28)
/* 80074C64 00071844  7C 18 00 00 */	cmpw r24, r0
/* 80074C68 00071848  41 80 FF 68 */	blt lbl_80074BD0
/* 80074C6C 0007184C  38 00 00 01 */	li r0, 1
/* 80074C70 00071850  98 1F 00 04 */	stb r0, 4(r31)
/* 80074C74 00071854  3B BD 00 02 */	addi r29, r29, 2
/* 80074C78 00071858  3B 9C 00 08 */	addi r28, r28, 8
/* 80074C7C 0007185C  3B 5A 00 01 */	addi r26, r26, 1
lbl_80074C80:
/* 80074C80 00071860  80 16 00 00 */	lwz r0, 0(r22)
/* 80074C84 00071864  7C 1A 00 40 */	cmplw r26, r0
/* 80074C88 00071868  41 80 FF 34 */	blt lbl_80074BBC
lbl_80074C8C:
/* 80074C8C 0007186C  BA 81 00 18 */	lmw r20, 0x18(r1)
/* 80074C90 00071870  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80074C94 00071874  38 21 00 48 */	addi r1, r1, 0x48
/* 80074C98 00071878  7C 08 03 A6 */	mtlr r0
/* 80074C9C 0007187C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80074CA0(u32*, s32, u32*)
{ // clang-format off
    nofralloc
/* 80074CA0 00071880  7C 08 02 A6 */	mflr r0
/* 80074CA4 00071884  90 01 00 04 */	stw r0, 4(r1)
/* 80074CA8 00071888  54 80 10 3A */	slwi r0, r4, 2
/* 80074CAC 0007188C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80074CB0 00071890  BE C1 00 18 */	stmw r22, 0x18(r1)
/* 80074CB4 00071894  3B C3 00 00 */	addi r30, r3, 0
/* 80074CB8 00071898  7C 7E 02 14 */	add r3, r30, r0
/* 80074CBC 0007189C  3B E5 00 00 */	addi r31, r5, 0
/* 80074CC0 000718A0  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80074CC4 000718A4  28 00 00 00 */	cmplwi r0, 0
/* 80074CC8 000718A8  7C 03 03 78 */	mr r3, r0
/* 80074CCC 000718AC  41 82 00 9C */	beq lbl_80074D68
/* 80074CD0 000718B0  7F 3E 22 14 */	add r25, r30, r4
/* 80074CD4 000718B4  8C 19 00 04 */	lbzu r0, 4(r25)
/* 80074CD8 000718B8  28 00 00 00 */	cmplwi r0, 0
/* 80074CDC 000718BC  40 82 00 8C */	bne lbl_80074D68
/* 80074CE0 000718C0  3B 63 00 00 */	addi r27, r3, 0
/* 80074CE4 000718C4  3B 00 00 00 */	li r24, 0
/* 80074CE8 000718C8  48 00 00 6C */	b lbl_80074D54
lbl_80074CEC:
/* 80074CEC 000718CC  3A E0 00 00 */	li r23, 0
/* 80074CF0 000718D0  3B 80 00 00 */	li r28, 0
/* 80074CF4 000718D4  48 00 00 4C */	b lbl_80074D40
lbl_80074CF8:
/* 80074CF8 000718D8  80 1B 00 04 */	lwz r0, 4(r27)
/* 80074CFC 000718DC  3A C0 00 00 */	li r22, 0
/* 80074D00 000718E0  7F 40 E2 14 */	add r26, r0, r28
/* 80074D04 000718E4  83 BA 00 04 */	lwz r29, 4(r26)
/* 80074D08 000718E8  48 00 00 24 */	b lbl_80074D2C
lbl_80074D0C:
/* 80074D0C 000718EC  88 1D 00 00 */	lbz r0, 0(r29)
/* 80074D10 000718F0  38 80 00 01 */	li r4, 1
/* 80074D14 000718F4  80 7F 00 04 */	lwz r3, 4(r31)
/* 80074D18 000718F8  54 00 10 3A */	slwi r0, r0, 2
/* 80074D1C 000718FC  7C 63 00 2E */	lwzx r3, r3, r0
/* 80074D20 00071900  48 2E 90 B1 */	bl HSD_DObjClearFlags
/* 80074D24 00071904  3A D6 00 01 */	addi r22, r22, 1
/* 80074D28 00071908  3B BD 00 01 */	addi r29, r29, 1
lbl_80074D2C:
/* 80074D2C 0007190C  80 1A 00 00 */	lwz r0, 0(r26)
/* 80074D30 00071910  7C 16 00 00 */	cmpw r22, r0
/* 80074D34 00071914  41 80 FF D8 */	blt lbl_80074D0C
/* 80074D38 00071918  3B 9C 00 08 */	addi r28, r28, 8
/* 80074D3C 0007191C  3A F7 00 01 */	addi r23, r23, 1
lbl_80074D40:
/* 80074D40 00071920  80 1B 00 00 */	lwz r0, 0(r27)
/* 80074D44 00071924  7C 17 00 00 */	cmpw r23, r0
/* 80074D48 00071928  41 80 FF B0 */	blt lbl_80074CF8
/* 80074D4C 0007192C  3B 7B 00 08 */	addi r27, r27, 8
/* 80074D50 00071930  3B 18 00 01 */	addi r24, r24, 1
lbl_80074D54:
/* 80074D54 00071934  80 1E 00 00 */	lwz r0, 0(r30)
/* 80074D58 00071938  7C 18 00 40 */	cmplw r24, r0
/* 80074D5C 0007193C  41 80 FF 90 */	blt lbl_80074CEC
/* 80074D60 00071940  38 00 00 01 */	li r0, 1
/* 80074D64 00071944  98 19 00 00 */	stb r0, 0(r25)
lbl_80074D68:
/* 80074D68 00071948  BA C1 00 18 */	lmw r22, 0x18(r1)
/* 80074D6C 0007194C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80074D70 00071950  38 21 00 40 */	addi r1, r1, 0x40
/* 80074D74 00071954  7C 08 03 A6 */	mtlr r0
/* 80074D78 00071958  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80074D7C(u32*, s32, u32*)
{ // clang-format off
    nofralloc
/* 80074D7C 0007195C  7C 08 02 A6 */	mflr r0
/* 80074D80 00071960  90 01 00 04 */	stw r0, 4(r1)
/* 80074D84 00071964  54 80 10 3A */	slwi r0, r4, 2
/* 80074D88 00071968  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80074D8C 0007196C  BE C1 00 18 */	stmw r22, 0x18(r1)
/* 80074D90 00071970  3B C3 00 00 */	addi r30, r3, 0
/* 80074D94 00071974  7C 7E 02 14 */	add r3, r30, r0
/* 80074D98 00071978  3B E5 00 00 */	addi r31, r5, 0
/* 80074D9C 0007197C  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80074DA0 00071980  28 00 00 00 */	cmplwi r0, 0
/* 80074DA4 00071984  7C 03 03 78 */	mr r3, r0
/* 80074DA8 00071988  41 82 00 9C */	beq lbl_80074E44
/* 80074DAC 0007198C  7F 3E 22 14 */	add r25, r30, r4
/* 80074DB0 00071990  8C 19 00 04 */	lbzu r0, 4(r25)
/* 80074DB4 00071994  28 00 00 00 */	cmplwi r0, 0
/* 80074DB8 00071998  41 82 00 8C */	beq lbl_80074E44
/* 80074DBC 0007199C  3B 63 00 00 */	addi r27, r3, 0
/* 80074DC0 000719A0  3B 00 00 00 */	li r24, 0
/* 80074DC4 000719A4  48 00 00 6C */	b lbl_80074E30
lbl_80074DC8:
/* 80074DC8 000719A8  3A E0 00 00 */	li r23, 0
/* 80074DCC 000719AC  3B 80 00 00 */	li r28, 0
/* 80074DD0 000719B0  48 00 00 4C */	b lbl_80074E1C
lbl_80074DD4:
/* 80074DD4 000719B4  80 1B 00 04 */	lwz r0, 4(r27)
/* 80074DD8 000719B8  3A C0 00 00 */	li r22, 0
/* 80074DDC 000719BC  7F 40 E2 14 */	add r26, r0, r28
/* 80074DE0 000719C0  83 BA 00 04 */	lwz r29, 4(r26)
/* 80074DE4 000719C4  48 00 00 24 */	b lbl_80074E08
lbl_80074DE8:
/* 80074DE8 000719C8  88 1D 00 00 */	lbz r0, 0(r29)
/* 80074DEC 000719CC  38 80 00 01 */	li r4, 1
/* 80074DF0 000719D0  80 7F 00 04 */	lwz r3, 4(r31)
/* 80074DF4 000719D4  54 00 10 3A */	slwi r0, r0, 2
/* 80074DF8 000719D8  7C 63 00 2E */	lwzx r3, r3, r0
/* 80074DFC 000719DC  48 2E 8F BD */	bl HSD_DObjSetFlags
/* 80074E00 000719E0  3A D6 00 01 */	addi r22, r22, 1
/* 80074E04 000719E4  3B BD 00 01 */	addi r29, r29, 1
lbl_80074E08:
/* 80074E08 000719E8  80 1A 00 00 */	lwz r0, 0(r26)
/* 80074E0C 000719EC  7C 16 00 00 */	cmpw r22, r0
/* 80074E10 000719F0  41 80 FF D8 */	blt lbl_80074DE8
/* 80074E14 000719F4  3B 9C 00 08 */	addi r28, r28, 8
/* 80074E18 000719F8  3A F7 00 01 */	addi r23, r23, 1
lbl_80074E1C:
/* 80074E1C 000719FC  80 1B 00 00 */	lwz r0, 0(r27)
/* 80074E20 00071A00  7C 17 00 00 */	cmpw r23, r0
/* 80074E24 00071A04  41 80 FF B0 */	blt lbl_80074DD4
/* 80074E28 00071A08  3B 7B 00 08 */	addi r27, r27, 8
/* 80074E2C 00071A0C  3B 18 00 01 */	addi r24, r24, 1
lbl_80074E30:
/* 80074E30 00071A10  80 1E 00 00 */	lwz r0, 0(r30)
/* 80074E34 00071A14  7C 18 00 40 */	cmplw r24, r0
/* 80074E38 00071A18  41 80 FF 90 */	blt lbl_80074DC8
/* 80074E3C 00071A1C  38 00 00 00 */	li r0, 0
/* 80074E40 00071A20  98 19 00 00 */	stb r0, 0(r25)
lbl_80074E44:
/* 80074E44 00071A24  BA C1 00 18 */	lmw r22, 0x18(r1)
/* 80074E48 00071A28  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80074E4C 00071A2C  38 21 00 40 */	addi r1, r1, 0x40
/* 80074E50 00071A30  7C 08 03 A6 */	mtlr r0
/* 80074E54 00071A34  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80074E58()
{ // clang-format off
    nofralloc
/* 80074E58 00071A38  7C 08 02 A6 */	mflr r0
/* 80074E5C 00071A3C  3C 80 80 46 */	lis r4, fighter_bones_alloc_data@ha
/* 80074E60 00071A40  90 01 00 04 */	stw r0, 4(r1)
/* 80074E64 00071A44  38 04 90 28 */	addi r0, r4, fighter_bones_alloc_data@l
/* 80074E68 00071A48  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80074E6C 00071A4C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80074E70 00071A50  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80074E74 00071A54  3B C3 00 00 */	addi r30, r3, 0
/* 80074E78 00071A58  7C 03 03 78 */	mr r3, r0
/* 80074E7C 00071A5C  48 30 5D 4D */	bl HSD_ObjAlloc
/* 80074E80 00071A60  3C 80 80 46 */	lis r4, lbl_80459054@ha
/* 80074E84 00071A64  90 7E 05 E8 */	stw r3, 0x5e8(r30)
/* 80074E88 00071A68  38 64 90 54 */	addi r3, r4, lbl_80459054@l
/* 80074E8C 00071A6C  48 30 5D 3D */	bl HSD_ObjAlloc
/* 80074E90 00071A70  38 E0 00 00 */	li r7, 0
/* 80074E94 00071A74  90 7E 05 F0 */	stw r3, 0x5f0(r30)
/* 80074E98 00071A78  38 C7 00 00 */	addi r6, r7, 0
/* 80074E9C 00071A7C  38 87 00 00 */	addi r4, r7, 0
/* 80074EA0 00071A80  39 00 00 00 */	li r8, 0
/* 80074EA4 00071A84  48 00 00 24 */	b lbl_80074EC8
lbl_80074EA8:
/* 80074EA8 00071A88  80 BE 05 E8 */	lwz r5, 0x5e8(r30)
/* 80074EAC 00071A8C  38 67 00 08 */	addi r3, r7, 8
/* 80074EB0 00071A90  38 07 00 0C */	addi r0, r7, 0xc
/* 80074EB4 00071A94  7C C5 1B 2E */	sthx r6, r5, r3
/* 80074EB8 00071A98  38 E7 00 10 */	addi r7, r7, 0x10
/* 80074EBC 00071A9C  39 08 00 01 */	addi r8, r8, 1
/* 80074EC0 00071AA0  80 7E 05 E8 */	lwz r3, 0x5e8(r30)
/* 80074EC4 00071AA4  7C 83 01 2E */	stwx r4, r3, r0
lbl_80074EC8:
/* 80074EC8 00071AA8  80 1E 00 04 */	lwz r0, 4(r30)
/* 80074ECC 00071AAC  80 6D AE A4 */	lwz r3, ftPartsTable(r13)
/* 80074ED0 00071AB0  54 00 10 3A */	slwi r0, r0, 2
/* 80074ED4 00071AB4  7C 63 00 2E */	lwzx r3, r3, r0
/* 80074ED8 00071AB8  80 03 00 08 */	lwz r0, 8(r3)
/* 80074EDC 00071ABC  7C 08 00 40 */	cmplw r8, r0
/* 80074EE0 00071AC0  41 80 FF C8 */	blt lbl_80074EA8
/* 80074EE4 00071AC4  80 BE 05 E8 */	lwz r5, 0x5e8(r30)
/* 80074EE8 00071AC8  3B E0 00 01 */	li r31, 1
/* 80074EEC 00071ACC  38 7E 00 00 */	addi r3, r30, 0
/* 80074EF0 00071AD0  88 05 00 08 */	lbz r0, 8(r5)
/* 80074EF4 00071AD4  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 80074EF8 00071AD8  38 80 00 01 */	li r4, 1
/* 80074EFC 00071ADC  98 05 00 08 */	stb r0, 8(r5)
/* 80074F00 00071AE0  48 00 01 0D */	bl func_8007500C
/* 80074F04 00071AE4  54 63 20 36 */	slwi r3, r3, 4
/* 80074F08 00071AE8  80 BE 05 E8 */	lwz r5, 0x5e8(r30)
/* 80074F0C 00071AEC  38 83 00 08 */	addi r4, r3, 8
/* 80074F10 00071AF0  7C 05 20 AE */	lbzx r0, r5, r4
/* 80074F14 00071AF4  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 80074F18 00071AF8  38 7E 00 00 */	addi r3, r30, 0
/* 80074F1C 00071AFC  7C 05 21 AE */	stbx r0, r5, r4
/* 80074F20 00071B00  38 80 00 02 */	li r4, 2
/* 80074F24 00071B04  48 00 00 E9 */	bl func_8007500C
/* 80074F28 00071B08  54 63 20 36 */	slwi r3, r3, 4
/* 80074F2C 00071B0C  80 BE 05 E8 */	lwz r5, 0x5e8(r30)
/* 80074F30 00071B10  38 83 00 08 */	addi r4, r3, 8
/* 80074F34 00071B14  7C 05 20 AE */	lbzx r0, r5, r4
/* 80074F38 00071B18  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 80074F3C 00071B1C  38 7E 00 00 */	addi r3, r30, 0
/* 80074F40 00071B20  7C 05 21 AE */	stbx r0, r5, r4
/* 80074F44 00071B24  38 80 00 03 */	li r4, 3
/* 80074F48 00071B28  48 00 00 C5 */	bl func_8007500C
/* 80074F4C 00071B2C  54 63 20 36 */	slwi r3, r3, 4
/* 80074F50 00071B30  80 BE 05 E8 */	lwz r5, 0x5e8(r30)
/* 80074F54 00071B34  38 83 00 08 */	addi r4, r3, 8
/* 80074F58 00071B38  7C 05 20 AE */	lbzx r0, r5, r4
/* 80074F5C 00071B3C  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 80074F60 00071B40  38 7E 00 00 */	addi r3, r30, 0
/* 80074F64 00071B44  7C 05 21 AE */	stbx r0, r5, r4
/* 80074F68 00071B48  38 80 00 04 */	li r4, 4
/* 80074F6C 00071B4C  48 00 00 A1 */	bl func_8007500C
/* 80074F70 00071B50  54 63 20 36 */	slwi r3, r3, 4
/* 80074F74 00071B54  80 BE 05 E8 */	lwz r5, 0x5e8(r30)
/* 80074F78 00071B58  38 83 00 08 */	addi r4, r3, 8
/* 80074F7C 00071B5C  7C 05 20 AE */	lbzx r0, r5, r4
/* 80074F80 00071B60  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 80074F84 00071B64  38 7E 00 00 */	addi r3, r30, 0
/* 80074F88 00071B68  7C 05 21 AE */	stbx r0, r5, r4
/* 80074F8C 00071B6C  38 80 00 34 */	li r4, 0x34
/* 80074F90 00071B70  48 00 00 7D */	bl func_8007500C
/* 80074F94 00071B74  54 63 20 36 */	slwi r3, r3, 4
/* 80074F98 00071B78  80 BE 05 E8 */	lwz r5, 0x5e8(r30)
/* 80074F9C 00071B7C  38 83 00 08 */	addi r4, r3, 8
/* 80074FA0 00071B80  7C 05 20 AE */	lbzx r0, r5, r4
/* 80074FA4 00071B84  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 80074FA8 00071B88  38 7E 00 00 */	addi r3, r30, 0
/* 80074FAC 00071B8C  7C 05 21 AE */	stbx r0, r5, r4
/* 80074FB0 00071B90  38 80 00 01 */	li r4, 1
/* 80074FB4 00071B94  48 00 00 59 */	bl func_8007500C
/* 80074FB8 00071B98  54 63 20 36 */	slwi r3, r3, 4
/* 80074FBC 00071B9C  80 BE 05 E8 */	lwz r5, 0x5e8(r30)
/* 80074FC0 00071BA0  38 83 00 08 */	addi r4, r3, 8
/* 80074FC4 00071BA4  7C 05 20 AE */	lbzx r0, r5, r4
/* 80074FC8 00071BA8  53 E0 1F 38 */	rlwimi r0, r31, 3, 0x1c, 0x1c
/* 80074FCC 00071BAC  38 7E 00 00 */	addi r3, r30, 0
/* 80074FD0 00071BB0  7C 05 21 AE */	stbx r0, r5, r4
/* 80074FD4 00071BB4  38 80 00 35 */	li r4, 0x35
/* 80074FD8 00071BB8  48 00 00 35 */	bl func_8007500C
/* 80074FDC 00071BBC  54 63 20 36 */	slwi r3, r3, 4
/* 80074FE0 00071BC0  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 80074FE4 00071BC4  38 63 00 08 */	addi r3, r3, 8
/* 80074FE8 00071BC8  7C 04 18 AE */	lbzx r0, r4, r3
/* 80074FEC 00071BCC  53 E0 1F 38 */	rlwimi r0, r31, 3, 0x1c, 0x1c
/* 80074FF0 00071BD0  7C 04 19 AE */	stbx r0, r4, r3
/* 80074FF4 00071BD4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80074FF8 00071BD8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80074FFC 00071BDC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80075000 00071BE0  38 21 00 18 */	addi r1, r1, 0x18
/* 80075004 00071BE4  7C 08 03 A6 */	mtlr r0
/* 80075008 00071BE8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm s32 func_8007500C(Fighter*, s32)
{ // clang-format off
    nofralloc
/* 8007500C 00071BEC  80 03 00 04 */	lwz r0, 4(r3)
/* 80075010 00071BF0  80 6D AE A4 */	lwz r3, ftPartsTable(r13)
/* 80075014 00071BF4  54 00 10 3A */	slwi r0, r0, 2
/* 80075018 00071BF8  7C 63 00 2E */	lwzx r3, r3, r0
/* 8007501C 00071BFC  80 63 00 04 */	lwz r3, 4(r3)
/* 80075020 00071C00  7C 63 20 AE */	lbzx r3, r3, r4
/* 80075024 00071C04  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80075028()
{ // clang-format off
    nofralloc
/* 80075028 00071C08  80 CD AE A4 */	lwz r6, ftPartsTable(r13)
/* 8007502C 00071C0C  54 80 10 3A */	slwi r0, r4, 2
/* 80075030 00071C10  7C 86 00 2E */	lwzx r4, r6, r0
/* 80075034 00071C14  80 04 00 08 */	lwz r0, 8(r4)
/* 80075038 00071C18  7C 05 00 40 */	cmplw r5, r0
/* 8007503C 00071C1C  40 80 00 28 */	bge lbl_80075064
/* 80075040 00071C20  80 84 00 00 */	lwz r4, 0(r4)
/* 80075044 00071C24  7C 84 28 AE */	lbzx r4, r4, r5
/* 80075048 00071C28  28 04 00 FF */	cmplwi r4, 0xff
/* 8007504C 00071C2C  41 82 00 18 */	beq lbl_80075064
/* 80075050 00071C30  54 60 10 3A */	slwi r0, r3, 2
/* 80075054 00071C34  7C 66 00 2E */	lwzx r3, r6, r0
/* 80075058 00071C38  80 63 00 04 */	lwz r3, 4(r3)
/* 8007505C 00071C3C  7C 63 20 AE */	lbzx r3, r3, r4
/* 80075060 00071C40  4E 80 00 20 */	blr
lbl_80075064:
/* 80075064 00071C44  38 60 00 FF */	li r3, 0xff
/* 80075068 00071C48  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm u32 func_8007506C(s32 ftkind, u32 part)
{ // clang-format off
    nofralloc
/* 8007506C 00071C4C  80 AD AE A0 */	lwz r5, lbl_804D6540(r13)
/* 80075070 00071C50  54 60 10 3A */	slwi r0, r3, 2
/* 80075074 00071C54  7C 65 00 2E */	lwzx r3, r5, r0
/* 80075078 00071C58  28 03 00 00 */	cmplwi r3, 0
/* 8007507C 00071C5C  41 82 00 44 */	beq lbl_800750C0
/* 80075080 00071C60  80 03 00 04 */	lwz r0, 4(r3)
/* 80075084 00071C64  2C 00 00 00 */	cmpwi r0, 0
/* 80075088 00071C68  41 82 00 38 */	beq lbl_800750C0
/* 8007508C 00071C6C  7C 09 03 A6 */	mtctr r0
/* 80075090 00071C70  80 63 00 00 */	lwz r3, 0(r3)
/* 80075094 00071C74  38 A0 00 00 */	li r5, 0
/* 80075098 00071C78  40 81 00 28 */	ble lbl_800750C0
lbl_8007509C:
/* 8007509C 00071C7C  88 03 00 00 */	lbz r0, 0(r3)
/* 800750A0 00071C80  7C 00 20 00 */	cmpw r0, r4
/* 800750A4 00071C84  40 82 00 10 */	bne lbl_800750B4
/* 800750A8 00071C88  38 00 00 01 */	li r0, 1
/* 800750AC 00071C8C  7C 03 28 30 */	slw r3, r0, r5
/* 800750B0 00071C90  4E 80 00 20 */	blr
lbl_800750B4:
/* 800750B4 00071C94  38 A5 00 01 */	addi r5, r5, 1
/* 800750B8 00071C98  38 63 00 04 */	addi r3, r3, 4
/* 800750BC 00071C9C  42 00 FF E0 */	bdnz lbl_8007509C
lbl_800750C0:
/* 800750C0 00071CA0  38 60 00 00 */	li r3, 0
/* 800750C4 00071CA4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800750C8()
{ // clang-format off
    nofralloc
/* 800750C8 00071CA8  7C 08 02 A6 */	mflr r0
/* 800750CC 00071CAC  90 01 00 04 */	stw r0, 4(r1)
/* 800750D0 00071CB0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800750D4 00071CB4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800750D8 00071CB8  3B E5 00 00 */	addi r31, r5, 0
/* 800750DC 00071CBC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800750E0 00071CC0  3B C3 00 00 */	addi r30, r3, 0
/* 800750E4 00071CC4  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800750E8 00071CC8  3B A4 00 00 */	addi r29, r4, 0
/* 800750EC 00071CCC  2C 1D 00 02 */	cmpwi r29, 2
/* 800750F0 00071CD0  40 82 00 D0 */	bne lbl_800751C0
/* 800750F4 00071CD4  2C 1F 00 00 */	cmpwi r31, 0
/* 800750F8 00071CD8  41 82 00 1C */	beq lbl_80075114
/* 800750FC 00071CDC  38 7E 00 00 */	addi r3, r30, 0
/* 80075100 00071CE0  38 9E 05 AC */	addi r4, r30, 0x5ac
/* 80075104 00071CE4  38 DE 20 3C */	addi r6, r30, 0x203c
/* 80075108 00071CE8  38 A0 00 02 */	li r5, 2
/* 8007510C 00071CEC  4B FF FA 61 */	bl func_80074B6C
/* 80075110 00071CF0  48 00 00 14 */	b lbl_80075124
lbl_80075114:
/* 80075114 00071CF4  38 7E 05 AC */	addi r3, r30, 0x5ac
/* 80075118 00071CF8  38 BE 20 3C */	addi r5, r30, 0x203c
/* 8007511C 00071CFC  38 80 00 02 */	li r4, 2
/* 80075120 00071D00  4B FF FC 5D */	bl func_80074D7C
lbl_80075124:
/* 80075124 00071D04  80 9E 00 04 */	lwz r4, 4(r30)
/* 80075128 00071D08  3C 60 80 3C */	lis r3, lbl_803C2150@ha
/* 8007512C 00071D0C  38 03 21 50 */	addi r0, r3, lbl_803C2150@l
/* 80075130 00071D10  54 83 10 3A */	slwi r3, r4, 2
/* 80075134 00071D14  7C 60 1A 14 */	add r3, r0, r3
/* 80075138 00071D18  81 83 00 00 */	lwz r12, 0(r3)
/* 8007513C 00071D1C  28 0C 00 00 */	cmplwi r12, 0
/* 80075140 00071D20  41 82 00 18 */	beq lbl_80075158
/* 80075144 00071D24  7D 88 03 A6 */	mtlr r12
/* 80075148 00071D28  38 7E 00 00 */	addi r3, r30, 0
/* 8007514C 00071D2C  38 BF 00 00 */	addi r5, r31, 0
/* 80075150 00071D30  38 80 00 02 */	li r4, 2
/* 80075154 00071D34  4E 80 00 21 */	blrl
lbl_80075158:
/* 80075158 00071D38  2C 1F 00 00 */	cmpwi r31, 0
/* 8007515C 00071D3C  41 82 00 1C */	beq lbl_80075178
/* 80075160 00071D40  38 7E 00 00 */	addi r3, r30, 0
/* 80075164 00071D44  38 9E 05 AC */	addi r4, r30, 0x5ac
/* 80075168 00071D48  38 DE 05 EC */	addi r6, r30, 0x5ec
/* 8007516C 00071D4C  38 A0 00 03 */	li r5, 3
/* 80075170 00071D50  4B FF F9 FD */	bl func_80074B6C
/* 80075174 00071D54  48 00 00 14 */	b lbl_80075188
lbl_80075178:
/* 80075178 00071D58  38 7E 05 AC */	addi r3, r30, 0x5ac
/* 8007517C 00071D5C  38 BE 05 EC */	addi r5, r30, 0x5ec
/* 80075180 00071D60  38 80 00 03 */	li r4, 3
/* 80075184 00071D64  4B FF FB F9 */	bl func_80074D7C
lbl_80075188:
/* 80075188 00071D68  80 9E 00 04 */	lwz r4, 4(r30)
/* 8007518C 00071D6C  3C 60 80 3C */	lis r3, lbl_803C2150@ha
/* 80075190 00071D70  38 03 21 50 */	addi r0, r3, lbl_803C2150@l
/* 80075194 00071D74  54 83 10 3A */	slwi r3, r4, 2
/* 80075198 00071D78  7C 60 1A 14 */	add r3, r0, r3
/* 8007519C 00071D7C  81 83 00 00 */	lwz r12, 0(r3)
/* 800751A0 00071D80  28 0C 00 00 */	cmplwi r12, 0
/* 800751A4 00071D84  41 82 00 80 */	beq lbl_80075224
/* 800751A8 00071D88  7D 88 03 A6 */	mtlr r12
/* 800751AC 00071D8C  38 7E 00 00 */	addi r3, r30, 0
/* 800751B0 00071D90  38 BF 00 00 */	addi r5, r31, 0
/* 800751B4 00071D94  38 80 00 03 */	li r4, 3
/* 800751B8 00071D98  4E 80 00 21 */	blrl
/* 800751BC 00071D9C  48 00 00 68 */	b lbl_80075224
lbl_800751C0:
/* 800751C0 00071DA0  2C 1F 00 00 */	cmpwi r31, 0
/* 800751C4 00071DA4  41 82 00 1C */	beq lbl_800751E0
/* 800751C8 00071DA8  38 7E 00 00 */	addi r3, r30, 0
/* 800751CC 00071DAC  38 BD 00 00 */	addi r5, r29, 0
/* 800751D0 00071DB0  38 9E 05 AC */	addi r4, r30, 0x5ac
/* 800751D4 00071DB4  38 DE 05 EC */	addi r6, r30, 0x5ec
/* 800751D8 00071DB8  4B FF F9 95 */	bl func_80074B6C
/* 800751DC 00071DBC  48 00 00 14 */	b lbl_800751F0
lbl_800751E0:
/* 800751E0 00071DC0  38 9D 00 00 */	addi r4, r29, 0
/* 800751E4 00071DC4  38 7E 05 AC */	addi r3, r30, 0x5ac
/* 800751E8 00071DC8  38 BE 05 EC */	addi r5, r30, 0x5ec
/* 800751EC 00071DCC  4B FF FB 91 */	bl func_80074D7C
lbl_800751F0:
/* 800751F0 00071DD0  80 9E 00 04 */	lwz r4, 4(r30)
/* 800751F4 00071DD4  3C 60 80 3C */	lis r3, lbl_803C2150@ha
/* 800751F8 00071DD8  38 03 21 50 */	addi r0, r3, lbl_803C2150@l
/* 800751FC 00071DDC  54 83 10 3A */	slwi r3, r4, 2
/* 80075200 00071DE0  7C 60 1A 14 */	add r3, r0, r3
/* 80075204 00071DE4  81 83 00 00 */	lwz r12, 0(r3)
/* 80075208 00071DE8  28 0C 00 00 */	cmplwi r12, 0
/* 8007520C 00071DEC  41 82 00 18 */	beq lbl_80075224
/* 80075210 00071DF0  7D 88 03 A6 */	mtlr r12
/* 80075214 00071DF4  38 7E 00 00 */	addi r3, r30, 0
/* 80075218 00071DF8  38 9D 00 00 */	addi r4, r29, 0
/* 8007521C 00071DFC  38 BF 00 00 */	addi r5, r31, 0
/* 80075220 00071E00  4E 80 00 21 */	blrl
lbl_80075224:
/* 80075224 00071E04  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80075228 00071E08  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8007522C 00071E0C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80075230 00071E10  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80075234 00071E14  38 21 00 28 */	addi r1, r1, 0x28
/* 80075238 00071E18  7C 08 03 A6 */	mtlr r0
/* 8007523C 00071E1C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80075240()
{ // clang-format off
    nofralloc
/* 80075240 00071E20  7C 08 02 A6 */	mflr r0
/* 80075244 00071E24  90 01 00 04 */	stw r0, 4(r1)
/* 80075248 00071E28  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8007524C 00071E2C  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 80075250 00071E30  3B 63 00 00 */	addi r27, r3, 0
/* 80075254 00071E34  3B 84 00 00 */	addi r28, r4, 0
/* 80075258 00071E38  3B C0 00 00 */	li r30, 0
/* 8007525C 00071E3C  3B A0 00 00 */	li r29, 0
/* 80075260 00071E40  3B E0 00 00 */	li r31, 0
/* 80075264 00071E44  48 00 00 5C */	b lbl_800752C0
lbl_80075268:
/* 80075268 00071E48  80 7B 00 04 */	lwz r3, 4(r27)
/* 8007526C 00071E4C  7C 63 F8 2E */	lwzx r3, r3, r31
/* 80075270 00071E50  28 03 00 00 */	cmplwi r3, 0
/* 80075274 00071E54  41 82 00 44 */	beq lbl_800752B8
/* 80075278 00071E58  41 82 00 0C */	beq lbl_80075284
/* 8007527C 00071E5C  80 03 00 08 */	lwz r0, 8(r3)
/* 80075280 00071E60  48 00 00 08 */	b lbl_80075288
lbl_80075284:
/* 80075284 00071E64  38 00 00 00 */	li r0, 0
lbl_80075288:
/* 80075288 00071E68  28 00 00 00 */	cmplwi r0, 0
/* 8007528C 00071E6C  7C 03 03 78 */	mr r3, r0
/* 80075290 00071E70  41 82 00 28 */	beq lbl_800752B8
/* 80075294 00071E74  48 2E E9 A5 */	bl HSD_MObjGetTObj
lbl_80075298:
/* 80075298 00071E78  28 03 00 00 */	cmplwi r3, 0
/* 8007529C 00071E7C  41 82 00 1C */	beq lbl_800752B8
/* 800752A0 00071E80  7C 1E E0 00 */	cmpw r30, r28
/* 800752A4 00071E84  40 82 00 08 */	bne lbl_800752AC
/* 800752A8 00071E88  48 00 00 48 */	b lbl_800752F0
lbl_800752AC:
/* 800752AC 00071E8C  3B DE 00 01 */	addi r30, r30, 1
/* 800752B0 00071E90  48 2E BE C5 */	bl HSD_TObjGetNext
/* 800752B4 00071E94  4B FF FF E4 */	b lbl_80075298
lbl_800752B8:
/* 800752B8 00071E98  3B FF 00 04 */	addi r31, r31, 4
/* 800752BC 00071E9C  3B BD 00 01 */	addi r29, r29, 1
lbl_800752C0:
/* 800752C0 00071EA0  80 1B 00 00 */	lwz r0, 0(r27)
/* 800752C4 00071EA4  7C 1D 00 00 */	cmpw r29, r0
/* 800752C8 00071EA8  41 80 FF A0 */	blt lbl_80075268
/* 800752CC 00071EAC  3C 60 80 3C */	lis r3, lbl_803C0B00@ha
/* 800752D0 00071EB0  4C C6 31 82 */	crclr 6
/* 800752D4 00071EB4  38 63 0B 00 */	addi r3, r3, lbl_803C0B00@l
/* 800752D8 00071EB8  48 2D 03 D1 */	bl OSReport
/* 800752DC 00071EBC  3C 60 80 3C */	lis r3, lbl_803C0A08@ha
/* 800752E0 00071EC0  38 63 0A 08 */	addi r3, r3, lbl_803C0A08@l
/* 800752E4 00071EC4  38 80 03 B4 */	li r4, 0x3b4
/* 800752E8 00071EC8  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 800752EC 00071ECC  48 31 2F 35 */	bl __assert
lbl_800752F0:
/* 800752F0 00071ED0  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 800752F4 00071ED4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800752F8 00071ED8  38 21 00 30 */	addi r1, r1, 0x30
/* 800752FC 00071EDC  7C 08 03 A6 */	mtlr r0
/* 80075300 00071EE0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80075304()
{ // clang-format off
    nofralloc
/* 80075304 00071EE4  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 80075308 00071EE8  2C 00 00 02 */	cmpwi r0, 2
/* 8007530C 00071EEC  41 82 00 78 */	beq lbl_80075384
/* 80075310 00071EF0  40 80 00 14 */	bge lbl_80075324
/* 80075314 00071EF4  2C 00 00 00 */	cmpwi r0, 0
/* 80075318 00071EF8  41 82 00 18 */	beq lbl_80075330
/* 8007531C 00071EFC  40 80 00 44 */	bge lbl_80075360
/* 80075320 00071F00  4E 80 00 20 */	blr
lbl_80075324:
/* 80075324 00071F04  2C 00 00 04 */	cmpwi r0, 4
/* 80075328 00071F08  4C 80 00 20 */	bgelr
/* 8007532C 00071F0C  48 00 00 80 */	b lbl_800753AC
lbl_80075330:
/* 80075330 00071F10  28 04 00 00 */	cmplwi r4, 0
/* 80075334 00071F14  40 82 00 0C */	bne lbl_80075340
/* 80075338 00071F18  38 60 00 00 */	li r3, 0
/* 8007533C 00071F1C  48 00 00 08 */	b lbl_80075344
lbl_80075340:
/* 80075340 00071F20  80 64 00 10 */	lwz r3, 0x10(r4)
lbl_80075344:
/* 80075344 00071F24  90 65 00 10 */	stw r3, 0x10(r5)
/* 80075348 00071F28  28 03 00 00 */	cmplwi r3, 0
/* 8007534C 00071F2C  90 85 00 0C */	stw r4, 0xc(r5)
/* 80075350 00071F30  90 A4 00 10 */	stw r5, 0x10(r4)
/* 80075354 00071F34  4D 82 00 20 */	beqlr
/* 80075358 00071F38  90 A3 00 0C */	stw r5, 0xc(r3)
/* 8007535C 00071F3C  4E 80 00 20 */	blr
lbl_80075360:
/* 80075360 00071F40  28 04 00 00 */	cmplwi r4, 0
/* 80075364 00071F44  40 82 00 0C */	bne lbl_80075370
/* 80075368 00071F48  38 00 00 00 */	li r0, 0
/* 8007536C 00071F4C  48 00 00 08 */	b lbl_80075374
lbl_80075370:
/* 80075370 00071F50  80 04 00 10 */	lwz r0, 0x10(r4)
lbl_80075374:
/* 80075374 00071F54  90 05 00 08 */	stw r0, 8(r5)
/* 80075378 00071F58  90 85 00 0C */	stw r4, 0xc(r5)
/* 8007537C 00071F5C  90 A4 00 10 */	stw r5, 0x10(r4)
/* 80075380 00071F60  4E 80 00 20 */	blr
lbl_80075384:
/* 80075384 00071F64  28 04 00 00 */	cmplwi r4, 0
/* 80075388 00071F68  40 82 00 0C */	bne lbl_80075394
/* 8007538C 00071F6C  38 00 00 00 */	li r0, 0
/* 80075390 00071F70  48 00 00 08 */	b lbl_80075398
lbl_80075394:
/* 80075394 00071F74  80 04 00 08 */	lwz r0, 8(r4)
lbl_80075398:
/* 80075398 00071F78  90 05 00 10 */	stw r0, 0x10(r5)
/* 8007539C 00071F7C  80 04 00 0C */	lwz r0, 0xc(r4)
/* 800753A0 00071F80  90 05 00 0C */	stw r0, 0xc(r5)
/* 800753A4 00071F84  90 A4 00 08 */	stw r5, 8(r4)
/* 800753A8 00071F88  4E 80 00 20 */	blr
lbl_800753AC:
/* 800753AC 00071F8C  28 04 00 00 */	cmplwi r4, 0
/* 800753B0 00071F90  40 82 00 0C */	bne lbl_800753BC
/* 800753B4 00071F94  38 00 00 00 */	li r0, 0
/* 800753B8 00071F98  48 00 00 08 */	b lbl_800753C0
lbl_800753BC:
/* 800753BC 00071F9C  80 04 00 08 */	lwz r0, 8(r4)
lbl_800753C0:
/* 800753C0 00071FA0  90 05 00 08 */	stw r0, 8(r5)
/* 800753C4 00071FA4  80 04 00 0C */	lwz r0, 0xc(r4)
/* 800753C8 00071FA8  90 05 00 0C */	stw r0, 0xc(r5)
/* 800753CC 00071FAC  90 A4 00 08 */	stw r5, 8(r4)
/* 800753D0 00071FB0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_800753D4(struct _Fighter*, s32, unk_t)
{ // clang-format off
    nofralloc
/* 800753D4 00071FB4  7C 08 02 A6 */	mflr r0
/* 800753D8 00071FB8  90 01 00 04 */	stw r0, 4(r1)
/* 800753DC 00071FBC  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 800753E0 00071FC0  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 800753E4 00071FC4  93 C1 00 78 */	stw r30, 0x78(r1)
/* 800753E8 00071FC8  93 A1 00 74 */	stw r29, 0x74(r1)
/* 800753EC 00071FCC  3B A4 00 00 */	addi r29, r4, 0
/* 800753F0 00071FD0  93 81 00 70 */	stw r28, 0x70(r1)
/* 800753F4 00071FD4  3B 83 00 00 */	addi r28, r3, 0
/* 800753F8 00071FD8  90 A1 00 6C */	stw r5, 0x6c(r1)
/* 800753FC 00071FDC  88 04 00 03 */	lbz r0, 3(r4)
/* 80075400 00071FE0  28 00 00 FF */	cmplwi r0, 0xff
/* 80075404 00071FE4  41 82 00 30 */	beq lbl_80075434
/* 80075408 00071FE8  38 00 00 00 */	li r0, 0
/* 8007540C 00071FEC  90 01 00 24 */	stw r0, 0x24(r1)
/* 80075410 00071FF0  3B C0 00 00 */	li r30, 0
/* 80075414 00071FF4  48 00 00 14 */	b lbl_80075428
lbl_80075418:
/* 80075418 00071FF8  38 61 00 6C */	addi r3, r1, 0x6c
/* 8007541C 00071FFC  38 81 00 24 */	addi r4, r1, 0x24
/* 80075420 00072000  4B FF 89 E1 */	bl Fighter_GetNextJointInTree
/* 80075424 00072004  3B DE 00 01 */	addi r30, r30, 1
lbl_80075428:
/* 80075428 00072008  88 1D 00 03 */	lbz r0, 3(r29)
/* 8007542C 0007200C  7C 1E 00 00 */	cmpw r30, r0
/* 80075430 00072010  41 80 FF E8 */	blt lbl_80075418
lbl_80075434:
/* 80075434 00072014  80 C1 00 6C */	lwz r6, 0x6c(r1)
/* 80075438 00072018  3C 60 80 3C */	lis r3, ftIntpJObj@ha
/* 8007543C 0007201C  3B E3 09 48 */	addi r31, r3, ftIntpJObj@l
/* 80075440 00072020  80 A6 00 00 */	lwz r5, 0(r6)
/* 80075444 00072024  38 00 00 00 */	li r0, 0
/* 80075448 00072028  80 86 00 04 */	lwz r4, 4(r6)
/* 8007544C 0007202C  7F E3 FB 78 */	mr r3, r31
/* 80075450 00072030  90 A1 00 2C */	stw r5, 0x2c(r1)
/* 80075454 00072034  90 81 00 30 */	stw r4, 0x30(r1)
/* 80075458 00072038  80 A6 00 08 */	lwz r5, 8(r6)
/* 8007545C 0007203C  80 86 00 0C */	lwz r4, 0xc(r6)
/* 80075460 00072040  90 A1 00 34 */	stw r5, 0x34(r1)
/* 80075464 00072044  90 81 00 38 */	stw r4, 0x38(r1)
/* 80075468 00072048  80 A6 00 10 */	lwz r5, 0x10(r6)
/* 8007546C 0007204C  80 86 00 14 */	lwz r4, 0x14(r6)
/* 80075470 00072050  90 A1 00 3C */	stw r5, 0x3c(r1)
/* 80075474 00072054  90 81 00 40 */	stw r4, 0x40(r1)
/* 80075478 00072058  80 A6 00 18 */	lwz r5, 0x18(r6)
/* 8007547C 0007205C  80 86 00 1C */	lwz r4, 0x1c(r6)
/* 80075480 00072060  90 A1 00 44 */	stw r5, 0x44(r1)
/* 80075484 00072064  90 81 00 48 */	stw r4, 0x48(r1)
/* 80075488 00072068  80 A6 00 20 */	lwz r5, 0x20(r6)
/* 8007548C 0007206C  80 86 00 24 */	lwz r4, 0x24(r6)
/* 80075490 00072070  90 A1 00 4C */	stw r5, 0x4c(r1)
/* 80075494 00072074  90 81 00 50 */	stw r4, 0x50(r1)
/* 80075498 00072078  80 A6 00 28 */	lwz r5, 0x28(r6)
/* 8007549C 0007207C  80 86 00 2C */	lwz r4, 0x2c(r6)
/* 800754A0 00072080  90 A1 00 54 */	stw r5, 0x54(r1)
/* 800754A4 00072084  90 81 00 58 */	stw r4, 0x58(r1)
/* 800754A8 00072088  80 A6 00 30 */	lwz r5, 0x30(r6)
/* 800754AC 0007208C  80 86 00 34 */	lwz r4, 0x34(r6)
/* 800754B0 00072090  90 A1 00 5C */	stw r5, 0x5c(r1)
/* 800754B4 00072094  90 81 00 60 */	stw r4, 0x60(r1)
/* 800754B8 00072098  80 A6 00 38 */	lwz r5, 0x38(r6)
/* 800754BC 0007209C  80 86 00 3C */	lwz r4, 0x3c(r6)
/* 800754C0 000720A0  90 A1 00 64 */	stw r5, 0x64(r1)
/* 800754C4 000720A4  90 81 00 68 */	stw r4, 0x68(r1)
/* 800754C8 000720A8  90 01 00 38 */	stw r0, 0x38(r1)
/* 800754CC 000720AC  90 01 00 34 */	stw r0, 0x34(r1)
/* 800754D0 000720B0  48 2F B6 C1 */	bl HSD_JObjSetDefaultClass
/* 800754D4 000720B4  38 61 00 2C */	addi r3, r1, 0x2c
/* 800754D8 000720B8  48 2F B9 6D */	bl HSD_JObjLoadJoint
/* 800754DC 000720BC  3B C3 00 00 */	addi r30, r3, 0
/* 800754E0 000720C0  38 60 00 00 */	li r3, 0
/* 800754E4 000720C4  48 2F B6 AD */	bl HSD_JObjSetDefaultClass
/* 800754E8 000720C8  7F E3 FB 78 */	mr r3, r31
/* 800754EC 000720CC  48 2F B6 A5 */	bl HSD_JObjSetDefaultClass
/* 800754F0 000720D0  38 61 00 2C */	addi r3, r1, 0x2c
/* 800754F4 000720D4  48 2F B9 51 */	bl HSD_JObjLoadJoint
/* 800754F8 000720D8  3B E3 00 00 */	addi r31, r3, 0
/* 800754FC 000720DC  38 60 00 00 */	li r3, 0
/* 80075500 000720E0  48 2F B6 91 */	bl HSD_JObjSetDefaultClass
/* 80075504 000720E4  88 1D 00 01 */	lbz r0, 1(r29)
/* 80075508 000720E8  38 BE 00 00 */	addi r5, r30, 0
/* 8007550C 000720EC  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 80075510 000720F0  54 00 20 36 */	slwi r0, r0, 4
/* 80075514 000720F4  88 7D 00 02 */	lbz r3, 2(r29)
/* 80075518 000720F8  7C 84 00 2E */	lwzx r4, r4, r0
/* 8007551C 000720FC  4B FF FD E9 */	bl func_80075304
/* 80075520 00072100  88 1D 00 01 */	lbz r0, 1(r29)
/* 80075524 00072104  7F E5 FB 78 */	mr r5, r31
/* 80075528 00072108  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 8007552C 0007210C  54 00 20 36 */	slwi r0, r0, 4
/* 80075530 00072110  88 7D 00 02 */	lbz r3, 2(r29)
/* 80075534 00072114  7C 84 02 14 */	add r4, r4, r0
/* 80075538 00072118  80 84 00 04 */	lwz r4, 4(r4)
/* 8007553C 0007211C  4B FF FD C9 */	bl func_80075304
/* 80075540 00072120  88 1D 00 01 */	lbz r0, 1(r29)
/* 80075544 00072124  88 9D 00 02 */	lbz r4, 2(r29)
/* 80075548 00072128  80 7C 05 E8 */	lwz r3, 0x5e8(r28)
/* 8007554C 0007212C  54 00 20 36 */	slwi r0, r0, 4
/* 80075550 00072130  28 04 00 00 */	cmplwi r4, 0
/* 80075554 00072134  7C 63 02 14 */	add r3, r3, r0
/* 80075558 00072138  88 E3 00 0C */	lbz r7, 0xc(r3)
/* 8007555C 0007213C  41 82 00 0C */	beq lbl_80075568
/* 80075560 00072140  28 04 00 01 */	cmplwi r4, 1
/* 80075564 00072144  40 82 00 08 */	bne lbl_8007556C
lbl_80075568:
/* 80075568 00072148  38 E7 00 01 */	addi r7, r7, 1
lbl_8007556C:
/* 8007556C 0007214C  38 00 00 00 */	li r0, 0
/* 80075570 00072150  90 01 00 28 */	stw r0, 0x28(r1)
/* 80075574 00072154  38 7C 00 00 */	addi r3, r28, 0
/* 80075578 00072158  38 BE 00 00 */	addi r5, r30, 0
/* 8007557C 0007215C  88 1D 00 00 */	lbz r0, 0(r29)
/* 80075580 00072160  38 C1 00 28 */	addi r6, r1, 0x28
/* 80075584 00072164  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 80075588 00072168  54 00 20 36 */	slwi r0, r0, 4
/* 8007558C 0007216C  7C 84 02 14 */	add r4, r4, r0
/* 80075590 00072170  4B FF EC 05 */	bl func_80074194
/* 80075594 00072174  88 1D 00 00 */	lbz r0, 0(r29)
/* 80075598 00072178  38 A0 00 01 */	li r5, 1
/* 8007559C 0007217C  80 7C 05 E8 */	lwz r3, 0x5e8(r28)
/* 800755A0 00072180  54 00 20 36 */	slwi r0, r0, 4
/* 800755A4 00072184  7C 63 02 14 */	add r3, r3, r0
/* 800755A8 00072188  93 E3 00 04 */	stw r31, 4(r3)
/* 800755AC 0007218C  88 1D 00 00 */	lbz r0, 0(r29)
/* 800755B0 00072190  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 800755B4 00072194  54 03 20 36 */	slwi r3, r0, 4
/* 800755B8 00072198  38 63 00 08 */	addi r3, r3, 8
/* 800755BC 0007219C  7C 04 18 AE */	lbzx r0, r4, r3
/* 800755C0 000721A0  50 A0 2E B4 */	rlwimi r0, r5, 5, 0x1a, 0x1a
/* 800755C4 000721A4  7C 04 19 AE */	stbx r0, r4, r3
/* 800755C8 000721A8  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800755CC 000721AC  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 800755D0 000721B0  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 800755D4 000721B4  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 800755D8 000721B8  83 81 00 70 */	lwz r28, 0x70(r1)
/* 800755DC 000721BC  38 21 00 80 */	addi r1, r1, 0x80
/* 800755E0 000721C0  7C 08 03 A6 */	mtlr r0
/* 800755E4 000721C4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800755E8()
{ // clang-format off
    nofralloc
/* 800755E8 000721C8  7C 08 02 A6 */	mflr r0
/* 800755EC 000721CC  90 01 00 04 */	stw r0, 4(r1)
/* 800755F0 000721D0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800755F4 000721D4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800755F8 000721D8  88 04 00 00 */	lbz r0, 0(r4)
/* 800755FC 000721DC  80 63 05 E8 */	lwz r3, 0x5e8(r3)
/* 80075600 000721E0  54 00 20 36 */	slwi r0, r0, 4
/* 80075604 000721E4  7F E3 02 14 */	add r31, r3, r0
/* 80075608 000721E8  80 7F 00 00 */	lwz r3, 0(r31)
/* 8007560C 000721EC  48 2F BD 65 */	bl HSD_JObjRemove
/* 80075610 000721F0  80 7F 00 04 */	lwz r3, 4(r31)
/* 80075614 000721F4  48 2F BD 5D */	bl HSD_JObjRemove
/* 80075618 000721F8  38 60 00 00 */	li r3, 0
/* 8007561C 000721FC  90 7F 00 00 */	stw r3, 0(r31)
/* 80075620 00072200  90 7F 00 04 */	stw r3, 4(r31)
/* 80075624 00072204  88 1F 00 08 */	lbz r0, 8(r31)
/* 80075628 00072208  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8007562C 0007220C  98 1F 00 08 */	stb r0, 8(r31)
/* 80075630 00072210  88 1F 00 08 */	lbz r0, 8(r31)
/* 80075634 00072214  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80075638 00072218  98 1F 00 08 */	stb r0, 8(r31)
/* 8007563C 0007221C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80075640 00072220  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80075644 00072224  38 21 00 18 */	addi r1, r1, 0x18
/* 80075648 00072228  7C 08 03 A6 */	mtlr r0
/* 8007564C 0007222C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80075650(HSD_GObj* fighter_gobj, HSD_JObj*, u32*)
{ // clang-format off
    nofralloc
/* 80075650 00072230  7C 08 02 A6 */	mflr r0
/* 80075654 00072234  3C 60 80 3C */	lis r3, ftMObj@ha
/* 80075658 00072238  90 01 00 04 */	stw r0, 4(r1)
/* 8007565C 0007223C  3C E0 80 3C */	lis r7, lbl_803C0B14@ha
/* 80075660 00072240  3C C0 80 3C */	lis r6, lbl_803C0A08@ha
/* 80075664 00072244  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80075668 00072248  BE E1 00 24 */	stmw r23, 0x24(r1)
/* 8007566C 0007224C  3B 84 00 00 */	addi r28, r4, 0
/* 80075670 00072250  3B A5 00 00 */	addi r29, r5, 0
/* 80075674 00072254  3B 63 69 80 */	addi r27, r3, ftMObj@l
/* 80075678 00072258  3B 27 0B 14 */	addi r25, r7, lbl_803C0B14@l
/* 8007567C 0007225C  3B 46 0A 08 */	addi r26, r6, lbl_803C0A08@l
/* 80075680 00072260  3B C0 00 00 */	li r30, 0
/* 80075684 00072264  3B E0 00 00 */	li r31, 0
/* 80075688 00072268  48 00 01 A8 */	b lbl_80075830
lbl_8007568C:
/* 8007568C 0007226C  7F 83 E3 78 */	mr r3, r28
/* 80075690 00072270  48 2F C5 5D */	bl HSD_JObjGetDObj
/* 80075694 00072274  3A E3 00 00 */	addi r23, r3, 0
/* 80075698 00072278  3B 1F 00 00 */	addi r24, r31, 0
lbl_8007569C:
/* 8007569C 0007227C  28 17 00 00 */	cmplwi r23, 0
/* 800756A0 00072280  41 82 00 70 */	beq lbl_80075710
/* 800756A4 00072284  2C 1E 00 20 */	cmpwi r30, 0x20
/* 800756A8 00072288  41 80 00 20 */	blt lbl_800756C8
/* 800756AC 0007228C  38 79 00 00 */	addi r3, r25, 0
/* 800756B0 00072290  4C C6 31 82 */	crclr 6
/* 800756B4 00072294  48 2C FF F5 */	bl OSReport
/* 800756B8 00072298  38 7A 00 00 */	addi r3, r26, 0
/* 800756BC 0007229C  38 80 04 27 */	li r4, 0x427
/* 800756C0 000722A0  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 800756C4 000722A4  48 31 2B 5D */	bl __assert
lbl_800756C8:
/* 800756C8 000722A8  80 7D 00 04 */	lwz r3, 4(r29)
/* 800756CC 000722AC  7E E3 C1 2E */	stwx r23, r3, r24
/* 800756D0 000722B0  80 17 00 08 */	lwz r0, 8(r23)
/* 800756D4 000722B4  28 00 00 00 */	cmplwi r0, 0
/* 800756D8 000722B8  7C 03 03 78 */	mr r3, r0
/* 800756DC 000722BC  41 82 00 0C */	beq lbl_800756E8
/* 800756E0 000722C0  7F 64 DB 78 */	mr r4, r27
/* 800756E4 000722C4  48 30 CD 1D */	bl hsdChangeClass
lbl_800756E8:
/* 800756E8 000722C8  28 17 00 00 */	cmplwi r23, 0
/* 800756EC 000722CC  41 82 00 0C */	beq lbl_800756F8
/* 800756F0 000722D0  80 17 00 04 */	lwz r0, 4(r23)
/* 800756F4 000722D4  48 00 00 08 */	b lbl_800756FC
lbl_800756F8:
/* 800756F8 000722D8  38 00 00 00 */	li r0, 0
lbl_800756FC:
/* 800756FC 000722DC  7C 17 03 78 */	mr r23, r0
/* 80075700 000722E0  3B 18 00 04 */	addi r24, r24, 4
/* 80075704 000722E4  3B FF 00 04 */	addi r31, r31, 4
/* 80075708 000722E8  3B DE 00 01 */	addi r30, r30, 1
/* 8007570C 000722EC  4B FF FF 90 */	b lbl_8007569C
lbl_80075710:
/* 80075710 000722F0  7F 83 E3 78 */	mr r3, r28
/* 80075714 000722F4  48 2F C5 D5 */	bl HSD_JObjGetFlags
/* 80075718 000722F8  54 60 04 E7 */	rlwinm. r0, r3, 0, 0x13, 0x13
/* 8007571C 000722FC  40 82 00 3C */	bne lbl_80075758
/* 80075720 00072300  28 1C 00 00 */	cmplwi r28, 0
/* 80075724 00072304  40 82 00 0C */	bne lbl_80075730
/* 80075728 00072308  38 00 00 00 */	li r0, 0
/* 8007572C 0007230C  48 00 00 08 */	b lbl_80075734
lbl_80075730:
/* 80075730 00072310  80 1C 00 10 */	lwz r0, 0x10(r28)
lbl_80075734:
/* 80075734 00072314  28 00 00 00 */	cmplwi r0, 0
/* 80075738 00072318  41 82 00 20 */	beq lbl_80075758
/* 8007573C 0007231C  28 1C 00 00 */	cmplwi r28, 0
/* 80075740 00072320  40 82 00 0C */	bne lbl_8007574C
/* 80075744 00072324  38 00 00 00 */	li r0, 0
/* 80075748 00072328  48 00 00 08 */	b lbl_80075750
lbl_8007574C:
/* 8007574C 0007232C  80 1C 00 10 */	lwz r0, 0x10(r28)
lbl_80075750:
/* 80075750 00072330  7C 1C 03 78 */	mr r28, r0
/* 80075754 00072334  48 00 00 DC */	b lbl_80075830
lbl_80075758:
/* 80075758 00072338  28 1C 00 00 */	cmplwi r28, 0
/* 8007575C 0007233C  40 82 00 0C */	bne lbl_80075768
/* 80075760 00072340  38 00 00 00 */	li r0, 0
/* 80075764 00072344  48 00 00 08 */	b lbl_8007576C
lbl_80075768:
/* 80075768 00072348  80 1C 00 08 */	lwz r0, 8(r28)
lbl_8007576C:
/* 8007576C 0007234C  28 00 00 00 */	cmplwi r0, 0
/* 80075770 00072350  41 82 00 20 */	beq lbl_80075790
/* 80075774 00072354  28 1C 00 00 */	cmplwi r28, 0
/* 80075778 00072358  40 82 00 0C */	bne lbl_80075784
/* 8007577C 0007235C  38 00 00 00 */	li r0, 0
/* 80075780 00072360  48 00 00 08 */	b lbl_80075788
lbl_80075784:
/* 80075784 00072364  80 1C 00 08 */	lwz r0, 8(r28)
lbl_80075788:
/* 80075788 00072368  7C 1C 03 78 */	mr r28, r0
/* 8007578C 0007236C  48 00 00 A4 */	b lbl_80075830
lbl_80075790:
/* 80075790 00072370  28 1C 00 00 */	cmplwi r28, 0
/* 80075794 00072374  40 82 00 0C */	bne lbl_800757A0
/* 80075798 00072378  38 00 00 00 */	li r0, 0
/* 8007579C 0007237C  48 00 00 08 */	b lbl_800757A4
lbl_800757A0:
/* 800757A0 00072380  80 1C 00 0C */	lwz r0, 0xc(r28)
lbl_800757A4:
/* 800757A4 00072384  28 00 00 00 */	cmplwi r0, 0
/* 800757A8 00072388  40 82 00 0C */	bne lbl_800757B4
/* 800757AC 0007238C  3B 80 00 00 */	li r28, 0
/* 800757B0 00072390  48 00 00 80 */	b lbl_80075830
lbl_800757B4:
/* 800757B4 00072394  28 1C 00 00 */	cmplwi r28, 0
/* 800757B8 00072398  40 82 00 0C */	bne lbl_800757C4
/* 800757BC 0007239C  38 60 00 00 */	li r3, 0
/* 800757C0 000723A0  48 00 00 08 */	b lbl_800757C8
lbl_800757C4:
/* 800757C4 000723A4  80 7C 00 0C */	lwz r3, 0xc(r28)
lbl_800757C8:
/* 800757C8 000723A8  28 03 00 00 */	cmplwi r3, 0
/* 800757CC 000723AC  40 82 00 0C */	bne lbl_800757D8
/* 800757D0 000723B0  38 00 00 00 */	li r0, 0
/* 800757D4 000723B4  48 00 00 08 */	b lbl_800757DC
lbl_800757D8:
/* 800757D8 000723B8  80 03 00 08 */	lwz r0, 8(r3)
lbl_800757DC:
/* 800757DC 000723BC  28 00 00 00 */	cmplwi r0, 0
/* 800757E0 000723C0  41 82 00 34 */	beq lbl_80075814
/* 800757E4 000723C4  28 1C 00 00 */	cmplwi r28, 0
/* 800757E8 000723C8  40 82 00 0C */	bne lbl_800757F4
/* 800757EC 000723CC  38 60 00 00 */	li r3, 0
/* 800757F0 000723D0  48 00 00 08 */	b lbl_800757F8
lbl_800757F4:
/* 800757F4 000723D4  80 7C 00 0C */	lwz r3, 0xc(r28)
lbl_800757F8:
/* 800757F8 000723D8  28 03 00 00 */	cmplwi r3, 0
/* 800757FC 000723DC  40 82 00 0C */	bne lbl_80075808
/* 80075800 000723E0  38 00 00 00 */	li r0, 0
/* 80075804 000723E4  48 00 00 08 */	b lbl_8007580C
lbl_80075808:
/* 80075808 000723E8  80 03 00 08 */	lwz r0, 8(r3)
lbl_8007580C:
/* 8007580C 000723EC  7C 1C 03 78 */	mr r28, r0
/* 80075810 000723F0  48 00 00 20 */	b lbl_80075830
lbl_80075814:
/* 80075814 000723F4  28 1C 00 00 */	cmplwi r28, 0
/* 80075818 000723F8  40 82 00 0C */	bne lbl_80075824
/* 8007581C 000723FC  38 00 00 00 */	li r0, 0
/* 80075820 00072400  48 00 00 08 */	b lbl_80075828
lbl_80075824:
/* 80075824 00072404  80 1C 00 0C */	lwz r0, 0xc(r28)
lbl_80075828:
/* 80075828 00072408  7C 1C 03 78 */	mr r28, r0
/* 8007582C 0007240C  4B FF FF 64 */	b lbl_80075790
lbl_80075830:
/* 80075830 00072410  28 1C 00 00 */	cmplwi r28, 0
/* 80075834 00072414  40 82 FE 58 */	bne lbl_8007568C
/* 80075838 00072418  BA E1 00 24 */	lmw r23, 0x24(r1)
/* 8007583C 0007241C  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80075840 00072420  38 21 00 48 */	addi r1, r1, 0x48
/* 80075844 00072424  7C 08 03 A6 */	mtlr r0
/* 80075848 00072428  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void Fighter_JObjSetRotation(HSD_JObj* jobj, Quaternion* quat)
{ // clang-format off
    nofralloc
/* 8007584C 0007242C  7C 08 02 A6 */	mflr r0
/* 80075850 00072430  90 01 00 04 */	stw r0, 4(r1)
/* 80075854 00072434  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80075858 00072438  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8007585C 0007243C  3B E4 00 00 */	addi r31, r4, 0
/* 80075860 00072440  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80075864 00072444  7C 7E 1B 79 */	or. r30, r3, r3
/* 80075868 00072448  40 82 00 14 */	bne lbl_8007587C
/* 8007586C 0007244C  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075870 00072450  38 80 02 6A */	li r4, 0x26a
/* 80075874 00072454  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075878 00072458  48 31 29 A9 */	bl __assert
lbl_8007587C:
/* 8007587C 0007245C  28 1F 00 00 */	cmplwi r31, 0
/* 80075880 00072460  40 82 00 14 */	bne lbl_80075894
/* 80075884 00072464  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075888 00072468  38 80 02 6B */	li r4, 0x26b
/* 8007588C 0007246C  38 AD 83 BC */	addi r5, r13, lbl_804D3A5C
/* 80075890 00072470  48 31 29 91 */	bl __assert
lbl_80075894:
/* 80075894 00072474  80 7F 00 00 */	lwz r3, 0(r31)
/* 80075898 00072478  80 1F 00 04 */	lwz r0, 4(r31)
/* 8007589C 0007247C  90 7E 00 1C */	stw r3, 0x1c(r30)
/* 800758A0 00072480  90 1E 00 20 */	stw r0, 0x20(r30)
/* 800758A4 00072484  80 7F 00 08 */	lwz r3, 8(r31)
/* 800758A8 00072488  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 800758AC 0007248C  90 7E 00 24 */	stw r3, 0x24(r30)
/* 800758B0 00072490  90 1E 00 28 */	stw r0, 0x28(r30)
/* 800758B4 00072494  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 800758B8 00072498  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800758BC 0007249C  40 82 00 4C */	bne lbl_80075908
/* 800758C0 000724A0  28 1E 00 00 */	cmplwi r30, 0
/* 800758C4 000724A4  41 82 00 44 */	beq lbl_80075908
/* 800758C8 000724A8  40 82 00 14 */	bne lbl_800758DC
/* 800758CC 000724AC  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 800758D0 000724B0  38 80 02 34 */	li r4, 0x234
/* 800758D4 000724B4  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 800758D8 000724B8  48 31 29 49 */	bl __assert
lbl_800758DC:
/* 800758DC 000724BC  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 800758E0 000724C0  38 60 00 00 */	li r3, 0
/* 800758E4 000724C4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800758E8 000724C8  40 82 00 10 */	bne lbl_800758F8
/* 800758EC 000724CC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800758F0 000724D0  41 82 00 08 */	beq lbl_800758F8
/* 800758F4 000724D4  38 60 00 01 */	li r3, 1
lbl_800758F8:
/* 800758F8 000724D8  2C 03 00 00 */	cmpwi r3, 0
/* 800758FC 000724DC  40 82 00 0C */	bne lbl_80075908
/* 80075900 000724E0  7F C3 F3 78 */	mr r3, r30
/* 80075904 000724E4  48 2F D9 E5 */	bl HSD_JObjSetMtxDirtySub
lbl_80075908:
/* 80075908 000724E8  38 7E 00 00 */	addi r3, r30, 0
/* 8007590C 000724EC  3C 80 00 02 */	lis r4, 2
/* 80075910 000724F0  48 2F C5 F1 */	bl HSD_JObjClearFlags
/* 80075914 000724F4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80075918 000724F8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8007591C 000724FC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80075920 00072500  38 21 00 18 */	addi r1, r1, 0x18
/* 80075924 00072504  7C 08 03 A6 */	mtlr r0
/* 80075928 00072508  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_8007592C(Fighter*, s32, f32)
{ // clang-format off
    nofralloc
/* 8007592C 0007250C  7C 08 02 A6 */	mflr r0
/* 80075930 00072510  90 01 00 04 */	stw r0, 4(r1)
/* 80075934 00072514  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80075938 00072518  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8007593C 0007251C  FF E0 08 90 */	fmr f31, f1
/* 80075940 00072520  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80075944 00072524  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80075948 00072528  54 9E 20 36 */	slwi r30, r4, 4
/* 8007594C 0007252C  3C 80 80 3C */	lis r4, ftJObj@ha
/* 80075950 00072530  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80075954 00072534  3B E4 08 F8 */	addi r31, r4, ftJObj@l
/* 80075958 00072538  93 81 00 18 */	stw r28, 0x18(r1)
/* 8007595C 0007253C  7C 7C 1B 78 */	mr r28, r3
/* 80075960 00072540  80 63 05 E8 */	lwz r3, 0x5e8(r3)
/* 80075964 00072544  7F A3 F0 2E */	lwzx r29, r3, r30
/* 80075968 00072548  38 7D 00 00 */	addi r3, r29, 0
/* 8007596C 0007254C  48 2F C3 7D */	bl HSD_JObjGetFlags
/* 80075970 00072550  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075974 00072554  41 82 00 CC */	beq lbl_80075A40
/* 80075978 00072558  80 1C 05 E8 */	lwz r0, 0x5e8(r28)
/* 8007597C 0007255C  7C 60 F2 14 */	add r3, r0, r30
/* 80075980 00072560  83 A3 00 04 */	lwz r29, 4(r3)
/* 80075984 00072564  7F A3 EB 78 */	mr r3, r29
/* 80075988 00072568  48 2F C3 61 */	bl HSD_JObjGetFlags
/* 8007598C 0007256C  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075990 00072570  41 82 00 20 */	beq lbl_800759B0
/* 80075994 00072574  38 7F 02 40 */	addi r3, r31, 0x240
/* 80075998 00072578  4C C6 31 82 */	crclr 6
/* 8007599C 0007257C  48 2C FD 0D */	bl OSReport
/* 800759A0 00072580  38 7F 01 10 */	addi r3, r31, 0x110
/* 800759A4 00072584  38 80 04 60 */	li r4, 0x460
/* 800759A8 00072588  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 800759AC 0007258C  48 31 28 75 */	bl __assert
lbl_800759B0:
/* 800759B0 00072590  28 1D 00 00 */	cmplwi r29, 0
/* 800759B4 00072594  40 82 00 14 */	bne lbl_800759C8
/* 800759B8 00072598  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 800759BC 0007259C  38 80 02 7F */	li r4, 0x27f
/* 800759C0 000725A0  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 800759C4 000725A4  48 31 28 5D */	bl __assert
lbl_800759C8:
/* 800759C8 000725A8  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 800759CC 000725AC  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 800759D0 000725B0  41 82 00 14 */	beq lbl_800759E4
/* 800759D4 000725B4  38 BF 02 5C */	addi r5, r31, 0x25c
/* 800759D8 000725B8  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 800759DC 000725BC  38 80 02 80 */	li r4, 0x280
/* 800759E0 000725C0  48 31 28 41 */	bl __assert
lbl_800759E4:
/* 800759E4 000725C4  D3 FD 00 1C */	stfs f31, 0x1c(r29)
/* 800759E8 000725C8  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 800759EC 000725CC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800759F0 000725D0  40 82 00 DC */	bne lbl_80075ACC
/* 800759F4 000725D4  28 1D 00 00 */	cmplwi r29, 0
/* 800759F8 000725D8  41 82 00 D4 */	beq lbl_80075ACC
/* 800759FC 000725DC  40 82 00 14 */	bne lbl_80075A10
/* 80075A00 000725E0  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075A04 000725E4  38 80 02 34 */	li r4, 0x234
/* 80075A08 000725E8  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075A0C 000725EC  48 31 28 15 */	bl __assert
lbl_80075A10:
/* 80075A10 000725F0  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80075A14 000725F4  38 60 00 00 */	li r3, 0
/* 80075A18 000725F8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80075A1C 000725FC  40 82 00 10 */	bne lbl_80075A2C
/* 80075A20 00072600  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80075A24 00072604  41 82 00 08 */	beq lbl_80075A2C
/* 80075A28 00072608  38 60 00 01 */	li r3, 1
lbl_80075A2C:
/* 80075A2C 0007260C  2C 03 00 00 */	cmpwi r3, 0
/* 80075A30 00072610  40 82 00 9C */	bne lbl_80075ACC
/* 80075A34 00072614  7F A3 EB 78 */	mr r3, r29
/* 80075A38 00072618  48 2F D8 B1 */	bl HSD_JObjSetMtxDirtySub
/* 80075A3C 0007261C  48 00 00 90 */	b lbl_80075ACC
lbl_80075A40:
/* 80075A40 00072620  28 1D 00 00 */	cmplwi r29, 0
/* 80075A44 00072624  40 82 00 14 */	bne lbl_80075A58
/* 80075A48 00072628  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075A4C 0007262C  38 80 02 7F */	li r4, 0x27f
/* 80075A50 00072630  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075A54 00072634  48 31 27 CD */	bl __assert
lbl_80075A58:
/* 80075A58 00072638  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075A5C 0007263C  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 80075A60 00072640  41 82 00 14 */	beq lbl_80075A74
/* 80075A64 00072644  38 BF 02 5C */	addi r5, r31, 0x25c
/* 80075A68 00072648  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075A6C 0007264C  38 80 02 80 */	li r4, 0x280
/* 80075A70 00072650  48 31 27 B1 */	bl __assert
lbl_80075A74:
/* 80075A74 00072654  D3 FD 00 1C */	stfs f31, 0x1c(r29)
/* 80075A78 00072658  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075A7C 0007265C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80075A80 00072660  40 82 00 4C */	bne lbl_80075ACC
/* 80075A84 00072664  28 1D 00 00 */	cmplwi r29, 0
/* 80075A88 00072668  41 82 00 44 */	beq lbl_80075ACC
/* 80075A8C 0007266C  40 82 00 14 */	bne lbl_80075AA0
/* 80075A90 00072670  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075A94 00072674  38 80 02 34 */	li r4, 0x234
/* 80075A98 00072678  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075A9C 0007267C  48 31 27 85 */	bl __assert
lbl_80075AA0:
/* 80075AA0 00072680  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80075AA4 00072684  38 60 00 00 */	li r3, 0
/* 80075AA8 00072688  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80075AAC 0007268C  40 82 00 10 */	bne lbl_80075ABC
/* 80075AB0 00072690  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80075AB4 00072694  41 82 00 08 */	beq lbl_80075ABC
/* 80075AB8 00072698  38 60 00 01 */	li r3, 1
lbl_80075ABC:
/* 80075ABC 0007269C  2C 03 00 00 */	cmpwi r3, 0
/* 80075AC0 000726A0  40 82 00 0C */	bne lbl_80075ACC
/* 80075AC4 000726A4  7F A3 EB 78 */	mr r3, r29
/* 80075AC8 000726A8  48 2F D8 21 */	bl HSD_JObjSetMtxDirtySub
lbl_80075ACC:
/* 80075ACC 000726AC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80075AD0 000726B0  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 80075AD4 000726B4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80075AD8 000726B8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80075ADC 000726BC  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80075AE0 000726C0  83 81 00 18 */	lwz r28, 0x18(r1)
/* 80075AE4 000726C4  38 21 00 30 */	addi r1, r1, 0x30
/* 80075AE8 000726C8  7C 08 03 A6 */	mtlr r0
/* 80075AEC 000726CC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80075AF0(Fighter*, s32, f32)
{ // clang-format off
    nofralloc
/* 80075AF0 000726D0  7C 08 02 A6 */	mflr r0
/* 80075AF4 000726D4  90 01 00 04 */	stw r0, 4(r1)
/* 80075AF8 000726D8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80075AFC 000726DC  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 80075B00 000726E0  FF E0 08 90 */	fmr f31, f1
/* 80075B04 000726E4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80075B08 000726E8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80075B0C 000726EC  54 9E 20 36 */	slwi r30, r4, 4
/* 80075B10 000726F0  3C 80 80 3C */	lis r4, ftJObj@ha
/* 80075B14 000726F4  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80075B18 000726F8  3B E4 08 F8 */	addi r31, r4, ftJObj@l
/* 80075B1C 000726FC  93 81 00 18 */	stw r28, 0x18(r1)
/* 80075B20 00072700  7C 7C 1B 78 */	mr r28, r3
/* 80075B24 00072704  80 63 05 E8 */	lwz r3, 0x5e8(r3)
/* 80075B28 00072708  7F A3 F0 2E */	lwzx r29, r3, r30
/* 80075B2C 0007270C  38 7D 00 00 */	addi r3, r29, 0
/* 80075B30 00072710  48 2F C1 B9 */	bl HSD_JObjGetFlags
/* 80075B34 00072714  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075B38 00072718  41 82 00 CC */	beq lbl_80075C04
/* 80075B3C 0007271C  80 1C 05 E8 */	lwz r0, 0x5e8(r28)
/* 80075B40 00072720  7C 60 F2 14 */	add r3, r0, r30
/* 80075B44 00072724  83 A3 00 04 */	lwz r29, 4(r3)
/* 80075B48 00072728  7F A3 EB 78 */	mr r3, r29
/* 80075B4C 0007272C  48 2F C1 9D */	bl HSD_JObjGetFlags
/* 80075B50 00072730  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075B54 00072734  41 82 00 20 */	beq lbl_80075B74
/* 80075B58 00072738  38 7F 02 84 */	addi r3, r31, 0x284
/* 80075B5C 0007273C  4C C6 31 82 */	crclr 6
/* 80075B60 00072740  48 2C FB 49 */	bl OSReport
/* 80075B64 00072744  38 7F 01 10 */	addi r3, r31, 0x110
/* 80075B68 00072748  38 80 04 73 */	li r4, 0x473
/* 80075B6C 0007274C  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 80075B70 00072750  48 31 26 B1 */	bl __assert
lbl_80075B74:
/* 80075B74 00072754  28 1D 00 00 */	cmplwi r29, 0
/* 80075B78 00072758  40 82 00 14 */	bne lbl_80075B8C
/* 80075B7C 0007275C  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075B80 00072760  38 80 02 94 */	li r4, 0x294
/* 80075B84 00072764  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075B88 00072768  48 31 26 99 */	bl __assert
lbl_80075B8C:
/* 80075B8C 0007276C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075B90 00072770  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 80075B94 00072774  41 82 00 14 */	beq lbl_80075BA8
/* 80075B98 00072778  38 BF 02 5C */	addi r5, r31, 0x25c
/* 80075B9C 0007277C  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075BA0 00072780  38 80 02 95 */	li r4, 0x295
/* 80075BA4 00072784  48 31 26 7D */	bl __assert
lbl_80075BA8:
/* 80075BA8 00072788  D3 FD 00 20 */	stfs f31, 0x20(r29)
/* 80075BAC 0007278C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075BB0 00072790  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80075BB4 00072794  40 82 00 DC */	bne lbl_80075C90
/* 80075BB8 00072798  28 1D 00 00 */	cmplwi r29, 0
/* 80075BBC 0007279C  41 82 00 D4 */	beq lbl_80075C90
/* 80075BC0 000727A0  40 82 00 14 */	bne lbl_80075BD4
/* 80075BC4 000727A4  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075BC8 000727A8  38 80 02 34 */	li r4, 0x234
/* 80075BCC 000727AC  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075BD0 000727B0  48 31 26 51 */	bl __assert
lbl_80075BD4:
/* 80075BD4 000727B4  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80075BD8 000727B8  38 60 00 00 */	li r3, 0
/* 80075BDC 000727BC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80075BE0 000727C0  40 82 00 10 */	bne lbl_80075BF0
/* 80075BE4 000727C4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80075BE8 000727C8  41 82 00 08 */	beq lbl_80075BF0
/* 80075BEC 000727CC  38 60 00 01 */	li r3, 1
lbl_80075BF0:
/* 80075BF0 000727D0  2C 03 00 00 */	cmpwi r3, 0
/* 80075BF4 000727D4  40 82 00 9C */	bne lbl_80075C90
/* 80075BF8 000727D8  7F A3 EB 78 */	mr r3, r29
/* 80075BFC 000727DC  48 2F D6 ED */	bl HSD_JObjSetMtxDirtySub
/* 80075C00 000727E0  48 00 00 90 */	b lbl_80075C90
lbl_80075C04:
/* 80075C04 000727E4  28 1D 00 00 */	cmplwi r29, 0
/* 80075C08 000727E8  40 82 00 14 */	bne lbl_80075C1C
/* 80075C0C 000727EC  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075C10 000727F0  38 80 02 94 */	li r4, 0x294
/* 80075C14 000727F4  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075C18 000727F8  48 31 26 09 */	bl __assert
lbl_80075C1C:
/* 80075C1C 000727FC  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075C20 00072800  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 80075C24 00072804  41 82 00 14 */	beq lbl_80075C38
/* 80075C28 00072808  38 BF 02 5C */	addi r5, r31, 0x25c
/* 80075C2C 0007280C  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075C30 00072810  38 80 02 95 */	li r4, 0x295
/* 80075C34 00072814  48 31 25 ED */	bl __assert
lbl_80075C38:
/* 80075C38 00072818  D3 FD 00 20 */	stfs f31, 0x20(r29)
/* 80075C3C 0007281C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075C40 00072820  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80075C44 00072824  40 82 00 4C */	bne lbl_80075C90
/* 80075C48 00072828  28 1D 00 00 */	cmplwi r29, 0
/* 80075C4C 0007282C  41 82 00 44 */	beq lbl_80075C90
/* 80075C50 00072830  40 82 00 14 */	bne lbl_80075C64
/* 80075C54 00072834  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075C58 00072838  38 80 02 34 */	li r4, 0x234
/* 80075C5C 0007283C  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075C60 00072840  48 31 25 C1 */	bl __assert
lbl_80075C64:
/* 80075C64 00072844  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80075C68 00072848  38 60 00 00 */	li r3, 0
/* 80075C6C 0007284C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80075C70 00072850  40 82 00 10 */	bne lbl_80075C80
/* 80075C74 00072854  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80075C78 00072858  41 82 00 08 */	beq lbl_80075C80
/* 80075C7C 0007285C  38 60 00 01 */	li r3, 1
lbl_80075C80:
/* 80075C80 00072860  2C 03 00 00 */	cmpwi r3, 0
/* 80075C84 00072864  40 82 00 0C */	bne lbl_80075C90
/* 80075C88 00072868  7F A3 EB 78 */	mr r3, r29
/* 80075C8C 0007286C  48 2F D6 5D */	bl HSD_JObjSetMtxDirtySub
lbl_80075C90:
/* 80075C90 00072870  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80075C94 00072874  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 80075C98 00072878  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80075C9C 0007287C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80075CA0 00072880  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80075CA4 00072884  83 81 00 18 */	lwz r28, 0x18(r1)
/* 80075CA8 00072888  38 21 00 30 */	addi r1, r1, 0x30
/* 80075CAC 0007288C  7C 08 03 A6 */	mtlr r0
/* 80075CB0 00072890  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm void func_80075CB4(Fighter*, s32, f32)
{ // clang-format off
    nofralloc
/* 80075CB4 00072894  7C 08 02 A6 */	mflr r0
/* 80075CB8 00072898  90 01 00 04 */	stw r0, 4(r1)
/* 80075CBC 0007289C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80075CC0 000728A0  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 80075CC4 000728A4  FF E0 08 90 */	fmr f31, f1
/* 80075CC8 000728A8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80075CCC 000728AC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80075CD0 000728B0  54 9E 20 36 */	slwi r30, r4, 4
/* 80075CD4 000728B4  3C 80 80 3C */	lis r4, ftJObj@ha
/* 80075CD8 000728B8  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80075CDC 000728BC  3B E4 08 F8 */	addi r31, r4, ftJObj@l
/* 80075CE0 000728C0  93 81 00 18 */	stw r28, 0x18(r1)
/* 80075CE4 000728C4  7C 7C 1B 78 */	mr r28, r3
/* 80075CE8 000728C8  80 63 05 E8 */	lwz r3, 0x5e8(r3)
/* 80075CEC 000728CC  7F A3 F0 2E */	lwzx r29, r3, r30
/* 80075CF0 000728D0  38 7D 00 00 */	addi r3, r29, 0
/* 80075CF4 000728D4  48 2F BF F5 */	bl HSD_JObjGetFlags
/* 80075CF8 000728D8  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075CFC 000728DC  41 82 00 CC */	beq lbl_80075DC8
/* 80075D00 000728E0  80 1C 05 E8 */	lwz r0, 0x5e8(r28)
/* 80075D04 000728E4  7C 60 F2 14 */	add r3, r0, r30
/* 80075D08 000728E8  83 A3 00 04 */	lwz r29, 4(r3)
/* 80075D0C 000728EC  7F A3 EB 78 */	mr r3, r29
/* 80075D10 000728F0  48 2F BF D9 */	bl HSD_JObjGetFlags
/* 80075D14 000728F4  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075D18 000728F8  41 82 00 20 */	beq lbl_80075D38
/* 80075D1C 000728FC  38 7F 02 A0 */	addi r3, r31, 0x2a0
/* 80075D20 00072900  4C C6 31 82 */	crclr 6
/* 80075D24 00072904  48 2C F9 85 */	bl OSReport
/* 80075D28 00072908  38 7F 01 10 */	addi r3, r31, 0x110
/* 80075D2C 0007290C  38 80 04 86 */	li r4, 0x486
/* 80075D30 00072910  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 80075D34 00072914  48 31 24 ED */	bl __assert
lbl_80075D38:
/* 80075D38 00072918  28 1D 00 00 */	cmplwi r29, 0
/* 80075D3C 0007291C  40 82 00 14 */	bne lbl_80075D50
/* 80075D40 00072920  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075D44 00072924  38 80 02 A9 */	li r4, 0x2a9
/* 80075D48 00072928  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075D4C 0007292C  48 31 24 D5 */	bl __assert
lbl_80075D50:
/* 80075D50 00072930  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075D54 00072934  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 80075D58 00072938  41 82 00 14 */	beq lbl_80075D6C
/* 80075D5C 0007293C  38 BF 02 5C */	addi r5, r31, 0x25c
/* 80075D60 00072940  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075D64 00072944  38 80 02 AA */	li r4, 0x2aa
/* 80075D68 00072948  48 31 24 B9 */	bl __assert
lbl_80075D6C:
/* 80075D6C 0007294C  D3 FD 00 24 */	stfs f31, 0x24(r29)
/* 80075D70 00072950  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075D74 00072954  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80075D78 00072958  40 82 00 DC */	bne lbl_80075E54
/* 80075D7C 0007295C  28 1D 00 00 */	cmplwi r29, 0
/* 80075D80 00072960  41 82 00 D4 */	beq lbl_80075E54
/* 80075D84 00072964  40 82 00 14 */	bne lbl_80075D98
/* 80075D88 00072968  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075D8C 0007296C  38 80 02 34 */	li r4, 0x234
/* 80075D90 00072970  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075D94 00072974  48 31 24 8D */	bl __assert
lbl_80075D98:
/* 80075D98 00072978  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80075D9C 0007297C  38 60 00 00 */	li r3, 0
/* 80075DA0 00072980  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80075DA4 00072984  40 82 00 10 */	bne lbl_80075DB4
/* 80075DA8 00072988  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80075DAC 0007298C  41 82 00 08 */	beq lbl_80075DB4
/* 80075DB0 00072990  38 60 00 01 */	li r3, 1
lbl_80075DB4:
/* 80075DB4 00072994  2C 03 00 00 */	cmpwi r3, 0
/* 80075DB8 00072998  40 82 00 9C */	bne lbl_80075E54
/* 80075DBC 0007299C  7F A3 EB 78 */	mr r3, r29
/* 80075DC0 000729A0  48 2F D5 29 */	bl HSD_JObjSetMtxDirtySub
/* 80075DC4 000729A4  48 00 00 90 */	b lbl_80075E54
lbl_80075DC8:
/* 80075DC8 000729A8  28 1D 00 00 */	cmplwi r29, 0
/* 80075DCC 000729AC  40 82 00 14 */	bne lbl_80075DE0
/* 80075DD0 000729B0  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075DD4 000729B4  38 80 02 A9 */	li r4, 0x2a9
/* 80075DD8 000729B8  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075DDC 000729BC  48 31 24 45 */	bl __assert
lbl_80075DE0:
/* 80075DE0 000729C0  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075DE4 000729C4  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 80075DE8 000729C8  41 82 00 14 */	beq lbl_80075DFC
/* 80075DEC 000729CC  38 BF 02 5C */	addi r5, r31, 0x25c
/* 80075DF0 000729D0  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075DF4 000729D4  38 80 02 AA */	li r4, 0x2aa
/* 80075DF8 000729D8  48 31 24 29 */	bl __assert
lbl_80075DFC:
/* 80075DFC 000729DC  D3 FD 00 24 */	stfs f31, 0x24(r29)
/* 80075E00 000729E0  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80075E04 000729E4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80075E08 000729E8  40 82 00 4C */	bne lbl_80075E54
/* 80075E0C 000729EC  28 1D 00 00 */	cmplwi r29, 0
/* 80075E10 000729F0  41 82 00 44 */	beq lbl_80075E54
/* 80075E14 000729F4  40 82 00 14 */	bne lbl_80075E28
/* 80075E18 000729F8  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075E1C 000729FC  38 80 02 34 */	li r4, 0x234
/* 80075E20 00072A00  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075E24 00072A04  48 31 23 FD */	bl __assert
lbl_80075E28:
/* 80075E28 00072A08  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80075E2C 00072A0C  38 60 00 00 */	li r3, 0
/* 80075E30 00072A10  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80075E34 00072A14  40 82 00 10 */	bne lbl_80075E44
/* 80075E38 00072A18  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80075E3C 00072A1C  41 82 00 08 */	beq lbl_80075E44
/* 80075E40 00072A20  38 60 00 01 */	li r3, 1
lbl_80075E44:
/* 80075E44 00072A24  2C 03 00 00 */	cmpwi r3, 0
/* 80075E48 00072A28  40 82 00 0C */	bne lbl_80075E54
/* 80075E4C 00072A2C  7F A3 EB 78 */	mr r3, r29
/* 80075E50 00072A30  48 2F D4 99 */	bl HSD_JObjSetMtxDirtySub
lbl_80075E54:
/* 80075E54 00072A34  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80075E58 00072A38  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 80075E5C 00072A3C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80075E60 00072A40  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80075E64 00072A44  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80075E68 00072A48  83 81 00 18 */	lwz r28, 0x18(r1)
/* 80075E6C 00072A4C  38 21 00 30 */	addi r1, r1, 0x30
/* 80075E70 00072A50  7C 08 03 A6 */	mtlr r0
/* 80075E74 00072A54  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm f32 func_80075E78(Fighter*, BOOL)
{ // clang-format off
    nofralloc
/* 80075E78 00072A58  7C 08 02 A6 */	mflr r0
/* 80075E7C 00072A5C  90 01 00 04 */	stw r0, 4(r1)
/* 80075E80 00072A60  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80075E84 00072A64  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80075E88 00072A68  54 9F 20 36 */	slwi r31, r4, 4
/* 80075E8C 00072A6C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80075E90 00072A70  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80075E94 00072A74  7C 7D 1B 78 */	mr r29, r3
/* 80075E98 00072A78  80 63 05 E8 */	lwz r3, 0x5e8(r3)
/* 80075E9C 00072A7C  7F C3 F8 2E */	lwzx r30, r3, r31
/* 80075EA0 00072A80  7F C3 F3 78 */	mr r3, r30
/* 80075EA4 00072A84  48 2F BE 45 */	bl HSD_JObjGetFlags
/* 80075EA8 00072A88  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075EAC 00072A8C  41 82 00 64 */	beq lbl_80075F10
/* 80075EB0 00072A90  80 1D 05 E8 */	lwz r0, 0x5e8(r29)
/* 80075EB4 00072A94  7C 60 FA 14 */	add r3, r0, r31
/* 80075EB8 00072A98  83 C3 00 04 */	lwz r30, 4(r3)
/* 80075EBC 00072A9C  7F C3 F3 78 */	mr r3, r30
/* 80075EC0 00072AA0  48 2F BE 29 */	bl HSD_JObjGetFlags
/* 80075EC4 00072AA4  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075EC8 00072AA8  41 82 00 28 */	beq lbl_80075EF0
/* 80075ECC 00072AAC  3C 60 80 3C */	lis r3, lbl_803C0BB4@ha
/* 80075ED0 00072AB0  4C C6 31 82 */	crclr 6
/* 80075ED4 00072AB4  38 63 0B B4 */	addi r3, r3, lbl_803C0BB4@l
/* 80075ED8 00072AB8  48 2C F7 D1 */	bl OSReport
/* 80075EDC 00072ABC  3C 60 80 3C */	lis r3, lbl_803C0A08@ha
/* 80075EE0 00072AC0  38 63 0A 08 */	addi r3, r3, lbl_803C0A08@l
/* 80075EE4 00072AC4  38 80 04 99 */	li r4, 0x499
/* 80075EE8 00072AC8  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 80075EEC 00072ACC  48 31 23 35 */	bl __assert
lbl_80075EF0:
/* 80075EF0 00072AD0  28 1E 00 00 */	cmplwi r30, 0
/* 80075EF4 00072AD4  40 82 00 14 */	bne lbl_80075F08
/* 80075EF8 00072AD8  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075EFC 00072ADC  38 80 02 CB */	li r4, 0x2cb
/* 80075F00 00072AE0  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075F04 00072AE4  48 31 23 1D */	bl __assert
lbl_80075F08:
/* 80075F08 00072AE8  C0 3E 00 1C */	lfs f1, 0x1c(r30)
/* 80075F0C 00072AEC  48 00 00 20 */	b lbl_80075F2C
lbl_80075F10:
/* 80075F10 00072AF0  28 1E 00 00 */	cmplwi r30, 0
/* 80075F14 00072AF4  40 82 00 14 */	bne lbl_80075F28
/* 80075F18 00072AF8  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075F1C 00072AFC  38 80 02 CB */	li r4, 0x2cb
/* 80075F20 00072B00  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075F24 00072B04  48 31 22 FD */	bl __assert
lbl_80075F28:
/* 80075F28 00072B08  C0 3E 00 1C */	lfs f1, 0x1c(r30)
lbl_80075F2C:
/* 80075F2C 00072B0C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80075F30 00072B10  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80075F34 00072B14  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80075F38 00072B18  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80075F3C 00072B1C  38 21 00 20 */	addi r1, r1, 0x20
/* 80075F40 00072B20  7C 08 03 A6 */	mtlr r0
/* 80075F44 00072B24  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#pragma push
asm f32 func_80075F48(Fighter*, s32)
{ // clang-format off
    nofralloc
/* 80075F48 00072B28  7C 08 02 A6 */	mflr r0
/* 80075F4C 00072B2C  90 01 00 04 */	stw r0, 4(r1)
/* 80075F50 00072B30  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80075F54 00072B34  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80075F58 00072B38  54 9F 20 36 */	slwi r31, r4, 4
/* 80075F5C 00072B3C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80075F60 00072B40  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80075F64 00072B44  7C 7D 1B 78 */	mr r29, r3
/* 80075F68 00072B48  80 63 05 E8 */	lwz r3, 0x5e8(r3)
/* 80075F6C 00072B4C  7F C3 F8 2E */	lwzx r30, r3, r31
/* 80075F70 00072B50  7F C3 F3 78 */	mr r3, r30
/* 80075F74 00072B54  48 2F BD 75 */	bl HSD_JObjGetFlags
/* 80075F78 00072B58  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075F7C 00072B5C  41 82 00 64 */	beq lbl_80075FE0
/* 80075F80 00072B60  80 1D 05 E8 */	lwz r0, 0x5e8(r29)
/* 80075F84 00072B64  7C 60 FA 14 */	add r3, r0, r31
/* 80075F88 00072B68  83 C3 00 04 */	lwz r30, 4(r3)
/* 80075F8C 00072B6C  7F C3 F3 78 */	mr r3, r30
/* 80075F90 00072B70  48 2F BD 59 */	bl HSD_JObjGetFlags
/* 80075F94 00072B74  54 60 03 9D */	rlwinm. r0, r3, 0, 0xe, 0xe
/* 80075F98 00072B78  41 82 00 28 */	beq lbl_80075FC0
/* 80075F9C 00072B7C  3C 60 80 3C */	lis r3, lbl_803C0BD0@ha
/* 80075FA0 00072B80  4C C6 31 82 */	crclr 6
/* 80075FA4 00072B84  38 63 0B D0 */	addi r3, r3, lbl_803C0BD0@l
/* 80075FA8 00072B88  48 2C F7 01 */	bl OSReport
/* 80075FAC 00072B8C  3C 60 80 3C */	lis r3, lbl_803C0A08@ha
/* 80075FB0 00072B90  38 63 0A 08 */	addi r3, r3, lbl_803C0A08@l
/* 80075FB4 00072B94  38 80 04 AC */	li r4, 0x4ac
/* 80075FB8 00072B98  38 AD 83 B8 */	addi r5, r13, lbl_804D3A58
/* 80075FBC 00072B9C  48 31 22 65 */	bl __assert
lbl_80075FC0:
/* 80075FC0 00072BA0  28 1E 00 00 */	cmplwi r30, 0
/* 80075FC4 00072BA4  40 82 00 14 */	bne lbl_80075FD8
/* 80075FC8 00072BA8  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075FCC 00072BAC  38 80 02 DA */	li r4, 0x2da
/* 80075FD0 00072BB0  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075FD4 00072BB4  48 31 22 4D */	bl __assert
lbl_80075FD8:
/* 80075FD8 00072BB8  C0 3E 00 20 */	lfs f1, 0x20(r30)
/* 80075FDC 00072BBC  48 00 00 20 */	b lbl_80075FFC
lbl_80075FE0:
/* 80075FE0 00072BC0  28 1E 00 00 */	cmplwi r30, 0
/* 80075FE4 00072BC4  40 82 00 14 */	bne lbl_80075FF8
/* 80075FE8 00072BC8  38 6D 83 90 */	addi r3, r13, lbl_804D3A30
/* 80075FEC 00072BCC  38 80 02 DA */	li r4, 0x2da
/* 80075FF0 00072BD0  38 AD 83 98 */	addi r5, r13, lbl_804D3A38
/* 80075FF4 00072BD4  48 31 22 2D */	bl __assert
lbl_80075FF8:
/* 80075FF8 00072BD8  C0 3E 00 20 */	lfs f1, 0x20(r30)
lbl_80075FFC:
/* 80075FFC 00072BDC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80076000 00072BE0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80076004 00072BE4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80076008 00072BE8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8007600C 00072BEC  38 21 00 20 */	addi r1, r1, 0x20
/* 80076010 00072BF0  7C 08 03 A6 */	mtlr r0
/* 80076014 00072BF4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
