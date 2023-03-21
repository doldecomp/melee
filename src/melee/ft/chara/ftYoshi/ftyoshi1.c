#include "it/forward.h"

#include "ftyoshi1.h"

#include "types.h"

#include "ef/efasync.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <placeholder.h>
#include <dolphin/os/os.h>

MotionState ftYoshi_MotionStateTable[] = {
    { 37, 0x00100000, 0x01000000, lbl_8012C030, lbl_8012C114, lbl_8012C194,
      lbl_8012C1B4, func_800761C8 },
    { -1, 0x00180000, 0x01000000, lbl_8012C2F4, lbl_8012C3EC, lbl_8012C45C,
      lbl_8012C47C, func_800761C8 },
    { 39, 0x00100000, 0x01000000, lbl_8012C54C, lbl_8012C59C, lbl_8012C5C0,
      lbl_8012C5E0, func_800761C8 },
    { 40, 0x00100000, 0x01000000, lbl_8012C7A4, lbl_8012C80C, lbl_8012C810,
      lbl_8012C830, func_800761C8 },
    { 37, 0x00101073, 0x01000000, lbl_8012CAD0, lbl_8012CBBC, lbl_8012CBDC,
      lbl_8012CBFC, func_800761C8 },
    { 295, 0x00340011, 0x12000000, lbl_8012D550, NULL, lbl_8012DC30,
      lbl_8012DD70, func_800761C8 },
    { 296, 0x00340011, 0x12000000, lbl_8012D658, NULL, lbl_8012DC90,
      lbl_8012DDE8, func_800761C8 },
    { 296, 0x00340011, 0x12000000, lbl_8012D5C8, NULL, lbl_8012DC70,
      lbl_8012DDC0, func_800761C8 },
    { 297, 0x00340011, 0x12000000, lbl_8012D948, NULL, lbl_8012DD10,
      lbl_8012DE88, func_800761C8 },
    { 297, 0x00340011, 0x12000000, lbl_8012D7D8, NULL, lbl_8012DCF0,
      lbl_8012DE60, func_800761C8 },
    { 298, 0x00340411, 0x12000000, lbl_8012D58C, NULL, lbl_8012DC50,
      lbl_8012DD98, func_800761C8 },
    { 299, 0x00340411, 0x12000000, lbl_8012D760, NULL, lbl_8012DCD0,
      lbl_8012DE38, func_800761C8 },
    { 299, 0x00340411, 0x12000000, lbl_8012D6D0, NULL, lbl_8012DCB0,
      lbl_8012DE10, func_800761C8 },
    { 300, 0x00340411, 0x12000000, lbl_8012DB74, NULL, lbl_8012DD50,
      lbl_8012DED8, func_800761C8 },
    { 300, 0x00340411, 0x12000000, lbl_8012DA04, NULL, lbl_8012DD30,
      lbl_8012DEB0, func_800761C8 },
    { 301, 0x00340212, 0x13000000, lbl_8012F654, lbl_80130DB8, lbl_801310C4,
      lbl_801317DC, func_800761C8 },
    { 302, 0x00340212, 0x13000000, lbl_8012F750, lbl_80130DBC, lbl_801310E8,
      lbl_8013187C, func_800761C8 },
    { 303, 0x00340212, 0x13000000, lbl_8012FAC4, lbl_80130F7C, lbl_801312EC,
      lbl_80131B60, func_800761C8 },
    { 304, 0x00340212, 0x13000000, lbl_8012FFF4, lbl_80130FD8, lbl_80131618,
      lbl_80131E74, func_800761C8 },
    { 305, 0x00340612, 0x13000000, lbl_80130368, lbl_80130FDC, lbl_80131654,
      lbl_80131ED4, func_800761C8 },
    { 306, 0x00340612, 0x13000000, lbl_80130428, lbl_80130FEC, lbl_8013168C,
      lbl_80131F80, func_800761C8 },
    { 307, 0x00340612, 0x13000000, lbl_801306A8, lbl_80131050, lbl_80131718,
      lbl_8013245C, func_800761C8 },
    { 308, 0x00340612, 0x13000000, lbl_80130A24, lbl_801310B4, lbl_801317A4,
      lbl_801328F0, func_800761C8 },
    { 309, 0x00340113, 0x14000000, lbl_8012E4DC, NULL, lbl_8012E594,
      lbl_8012E5D4, func_800761C8 },
    { 310, 0x00340513, 0x14000000, lbl_8012E538, NULL, lbl_8012E5B4,
      lbl_8012E5FC, func_800761C8 },
    { 311, 0x00340214, 0x15000000, lbl_8012E814, NULL, lbl_8012E88C,
      lbl_8012E924, func_800761C8 },
    { 312, 0x00340214, 0x15000000, lbl_8012EA40, NULL, lbl_8012EA7C,
      lbl_8012EA9C, func_800761C8 },
    { 313, 0x00340614, 0x15000000, lbl_8012E850, NULL, lbl_8012E8CC,
      func_8012E944, func_800761C8 },
};

extern char* lbl_804D3E58;
extern char* lbl_804D3E60;
extern char* lbl_804D3E68;
extern char* lbl_804D3E70;
extern char* lbl_804D3E78;

/// https://decomp.me/scratch/ufrFK
void func_8012B6E8(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    struct S_UNK_YOSHI1* unk_struct1;
    s32* ptr2EndIndex;
    ftYoshiAttributes* attr_r26;
    u8* index;
    s32 i;
    f32 zero_float;

    attr_r26 = fp->ft_data->ext_attr;
    index = (unk_struct1 = unk_struct_arg)->unk_struct->xC_start_index;
    ptr2EndIndex = (s32*) (&unk_struct1->unk_struct->x8_end_index);
    zero_float = 0.0f;

    for (i = 0; i < *ptr2EndIndex; i++) {
        HSD_DObj* dobj_r3 = fp->dobj_list.data[index[i]];
        HSD_MObj* mobj_r3;
        HSD_AObj* aobj_r24;

        if (dobj_r3) {
            mobj_r3 = dobj_r3->mobj;
        } else {
            mobj_r3 = 0;
        }

        aobj_r24 = mobj_r3->aobj;
        HSD_AObjSetRate(aobj_r24, 0.0f);

        if (zero_float == attr_r26->xC) {
            attr_r26->xC = HSD_AObjGetEndFrame(aobj_r24);
        } else {
            if (attr_r26->xC != HSD_AObjGetEndFrame(aobj_r24)) {
                OSReport("yoshi matanim frame not same\n");
                __assert("ftyoshi.c", 0x61, "0");
            }
        }
    }
}

void func_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg,
                   f32 start_frame)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (unk_struct_arg) {
        struct S_UNK_YOSHI2* unk_struct = unk_struct_arg->unk_struct;
        s32* ptr2EndIndex;
        u8* index;
        s32 i;

        index = unk_struct->xC_start_index;
        ptr2EndIndex = (s32*) &unk_struct->x8_end_index;

        for (i = 0; i < *ptr2EndIndex; i++) {
            HSD_DObj* dobj_r3 = fp->dobj_list.data[index[i]];
            HSD_MObj* mobj_r3;
            HSD_MObj* mobj;

            if (dobj_r3) {
                mobj_r3 = dobj_r3->mobj;
            } else {
                mobj_r3 = 0;
            }

            mobj = mobj_r3;
            HSD_MObjReqAnim(mobj, start_frame);
            HSD_MObjAnim(mobj);
        }
    }
}

void func_8012B8A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attr = fp->x2D4_specialAttributes;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    f32 tempf = attr->xC * (1.0f - (fp->x1998_shieldHealth /
                                    p_ftCommonData->x260_startShieldHealth));
    func_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5B8, tempf);
    func_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5BC, tempf);
}

void func_8012B918(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5B8, 0.0f);
    func_8012B804(fp, (struct S_UNK_YOSHI1*) fp->x5BC, 0.0f);
}

void ftYoshi_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_80074A4C(gobj, 0, 0);
    fp->fv.ys.x2238 = 0;
}

// https://decomp.me/scratch/5TPxg
void ftYoshi_OnLoad(HSD_GObj* gobj)
{
    void** item_list;
    ftYoshiAttributes* other_attr;
    struct S_UNK_YOSHI1* temp_r28;
    struct S_UNK_YOSHI1* temp;
    ftData* ft;
    struct S_UNK_YOSHI1* temp_r27;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    temp = temp_r27 = (struct S_UNK_YOSHI1*) fp->x5B8;
    ft = fp->ft_data;
    temp_r28 = (struct S_UNK_YOSHI1*) fp->x5BC;
    item_list = ft->x48_items;
    other_attr = ft->ext_attr;

    if (!temp) {
        OSReport("yoshi parts_model NULL!!\n");
        __assert("ftyoshi.c", 0x71U, "0");
    }

    other_attr->xC = 0.0f;
    func_8012B6E8(fp, temp_r27);
    func_8012B6E8(fp, temp_r28);
    PUSH_ATTRS(fp, ftYoshiAttributes);
    func_8026B3F8(item_list[0], It_Kind_Yoshi_EggThrow);
    func_8026B3F8(item_list[1], It_Kind_Yoshi_Star);
    func_8026B3F8(item_list[2], It_Kind_Yoshi_EggLay);
    fp->x2226_flag.bits.b1 = 1;
}

/* static */ void func_8012E270(HSD_GObj* gobj);
/* static */ void func_8012DF18(HSD_GObj* gobj);

void ftYoshi_8012BA8C(HSD_GObj* gobj)
{
    func_8012E270(gobj);
    func_8012DF18(gobj);
}

f32 ftYoshi_8012BAC0(Fighter* fp)
{
    ftYoshiAttributes* attr = fp->x2D4_specialAttributes;
    return attr->x120;
}

void ftYoshi_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftYoshi_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftYoshi_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftYoshi_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftYoshi_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftYoshiAttributes);
}

void ftYoshi_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftYoshi_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}

/* static */ extern f32 const lbl_804D9A28;
/* static */ extern u8 lbl_803B75C0[];

#ifdef MWERKS_GEKKO

#pragma push
asm unk_t func_8012BDA0(void)
{ // clang-format off
    nofralloc
/* 8012BDA0 00128980  7C 08 02 A6 */	mflr r0
/* 8012BDA4 00128984  38 80 00 02 */	li r4, 2
/* 8012BDA8 00128988  90 01 00 04 */	stw r0, 4(r1)
/* 8012BDAC 0012898C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8012BDB0 00128990  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8012BDB4 00128994  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012BDB8 00128998  4B F4 F3 09 */	bl func_8007B0C0
/* 8012BDBC 0012899C  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 8012BDC0 001289A0  3C 60 80 3B */	lis r3, lbl_803B75C0@ha
/* 8012BDC4 001289A4  38 00 00 01 */	li r0, 1
/* 8012BDC8 001289A8  C0 02 A0 48 */	lfs f0, lbl_804D9A28
/* 8012BDCC 001289AC  80 84 00 08 */	lwz r4, 8(r4)
/* 8012BDD0 001289B0  38 E3 75 C0 */	addi r7, r3, lbl_803B75C0@l
/* 8012BDD4 001289B4  88 A4 00 11 */	lbz r5, 0x11(r4)
/* 8012BDD8 001289B8  38 7F 00 00 */	addi r3, r31, 0
/* 8012BDDC 001289BC  38 9F 11 A0 */	addi r4, r31, 0x11a0
/* 8012BDE0 001289C0  90 A1 00 20 */	stw r5, 0x20(r1)
/* 8012BDE4 001289C4  38 A1 00 20 */	addi r5, r1, 0x20
/* 8012BDE8 001289C8  90 01 00 24 */	stw r0, 0x24(r1)
/* 8012BDEC 001289CC  90 01 00 28 */	stw r0, 0x28(r1)
/* 8012BDF0 001289D0  80 C7 00 00 */	lwz r6, 0(r7)
/* 8012BDF4 001289D4  80 07 00 04 */	lwz r0, 4(r7)
/* 8012BDF8 001289D8  90 C1 00 38 */	stw r6, 0x38(r1)
/* 8012BDFC 001289DC  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8012BE00 001289E0  80 07 00 08 */	lwz r0, 8(r7)
/* 8012BE04 001289E4  90 01 00 40 */	stw r0, 0x40(r1)
/* 8012BE08 001289E8  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8012BE0C 001289EC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8012BE10 001289F0  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 8012BE14 001289F4  90 01 00 30 */	stw r0, 0x30(r1)
/* 8012BE18 001289F8  80 01 00 40 */	lwz r0, 0x40(r1)
/* 8012BE1C 001289FC  90 01 00 34 */	stw r0, 0x34(r1)
/* 8012BE20 00128A00  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8012BE24 00128A04  4B F4 F7 89 */	bl func_8007B5AC
/* 8012BE28 00128A08  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8012BE2C 00128A0C  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 8012BE30 00128A10  38 21 00 58 */	addi r1, r1, 0x58
/* 8012BE34 00128A14  7C 08 03 A6 */	mtlr r0
/* 8012BE38 00128A18  4E 80 00 20 */	blr
}
#pragma pop

#endif

void func_8012BE3C(HSD_GObj* gobj) {
    s32* x1CC;
    Fighter* fp = GET_FIGHTER(gobj);
    s32 bone_idx;
    Fighter* fp2;
    HSD_JObj* jobj;
    func_80074B0C(gobj, 0, 0);
    func_8007B0C0(gobj, 0);

    x1CC = &fp->x110_attr.x1CC;
    bone_idx = func_8007500C(fp, 4);
    fp2 = GET_FIGHTER(gobj);
    jobj = fp->ft_bones[bone_idx].x0_jobj;
    efAsync_Spawn(gobj, &fp2->x60C, 4U, 0x4CF, jobj, x1CC);
}

#ifdef MWERKS_GEKKO

/* static */ extern f32 const lbl_804D9A2C;
/* static */ extern f32 const lbl_804D9A28;

#pragma push
asm unk_t func_8012BECC(void)
{ // clang-format off
    nofralloc
func_8012BECC:
/* 8012BECC 00128AAC  7C 08 02 A6 */	mflr r0
/* 8012BED0 00128AB0  38 80 01 55 */	li r4, 0x155
/* 8012BED4 00128AB4  90 01 00 04 */	stw r0, 4(r1)
/* 8012BED8 00128AB8  38 A0 00 00 */	li r5, 0
/* 8012BEDC 00128ABC  38 C0 00 00 */	li r6, 0
/* 8012BEE0 00128AC0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8012BEE4 00128AC4  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8012BEE8 00128AC8  7C 7F 1B 78 */	mr r31, r3
/* 8012BEEC 00128ACC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8012BEF0 00128AD0  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8012BEF4 00128AD4  C0 22 A0 4C */	lfs f1, lbl_804D9A2C(r2)
/* 8012BEF8 00128AD8  C0 42 A0 48 */	lfs f2, lbl_804D9A28(r2)
/* 8012BEFC 00128ADC  FC 60 08 90 */	fmr f3, f1
/* 8012BF00 00128AE0  4B F3 D4 AD */	bl Fighter_ChangeMotionState
/* 8012BF04 00128AE4  7F E3 FB 78 */	mr r3, r31
/* 8012BF08 00128AE8  4B F4 2C 9D */	bl func_8006EBA4
/* 8012BF0C 00128AEC  7F E3 FB 78 */	mr r3, r31
/* 8012BF10 00128AF0  4B F6 65 41 */	bl func_80092450
/* 8012BF14 00128AF4  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 8012BF18 00128AF8  38 7F 00 00 */	addi r3, r31, 0
/* 8012BF1C 00128AFC  38 80 00 01 */	li r4, 1
/* 8012BF20 00128B00  4B F4 F1 A1 */	bl func_8007B0C0
/* 8012BF24 00128B04  38 00 00 00 */	li r0, 0
/* 8012BF28 00128B08  90 1E 23 4C */	stw r0, 0x234c(r30)
/* 8012BF2C 00128B0C  C0 22 A0 4C */	lfs f1, lbl_804D9A2C(r2)
/* 8012BF30 00128B10  D0 3E 23 40 */	stfs f1, 0x2340(r30)
/* 8012BF34 00128B14  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8012BF38 00128B18  C0 03 02 68 */	lfs f0, 0x268(r3)
/* 8012BF3C 00128B1C  D0 1E 23 50 */	stfs f0, 0x2350(r30)
/* 8012BF40 00128B20  90 1E 23 64 */	stw r0, 0x2364(r30)
/* 8012BF44 00128B24  90 1E 23 60 */	stw r0, 0x2360(r30)
/* 8012BF48 00128B28  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8012BF4C 00128B2C  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 8012BF50 00128B30  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 8012BF54 00128B34  80 7E 01 0C */	lwz r3, 0x10c(r30)
/* 8012BF58 00128B38  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8012BF5C 00128B3C  80 63 00 08 */	lwz r3, 8(r3)
/* 8012BF60 00128B40  88 03 00 11 */	lbz r0, 0x11(r3)
/* 8012BF64 00128B44  54 00 20 36 */	slwi r0, r0, 4
/* 8012BF68 00128B48  7F A4 00 2E */	lwzx r29, r4, r0
/* 8012BF6C 00128B4C  28 1D 00 00 */	cmplwi r29, 0
/* 8012BF70 00128B50  40 82 00 14 */	bne lbl_8012BF84
/* 8012BF74 00128B54  38 6D 87 B8 */	addi r3, r13, lbl_804D3E58
/* 8012BF78 00128B58  38 80 03 94 */	li r4, 0x394
/* 8012BF7C 00128B5C  38 AD 87 C0 */	addi r5, r13, lbl_804D3E60
/* 8012BF80 00128B60  48 25 C2 A1 */	bl __assert
lbl_8012BF84:
/* 8012BF84 00128B64  80 61 00 14 */	lwz r3, 0x14(r1)
/* 8012BF88 00128B68  80 01 00 18 */	lwz r0, 0x18(r1)
/* 8012BF8C 00128B6C  90 7D 00 38 */	stw r3, 0x38(r29)
/* 8012BF90 00128B70  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 8012BF94 00128B74  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012BF98 00128B78  90 1D 00 40 */	stw r0, 0x40(r29)
/* 8012BF9C 00128B7C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8012BFA0 00128B80  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8012BFA4 00128B84  40 82 00 4C */	bne lbl_8012BFF0
/* 8012BFA8 00128B88  28 1D 00 00 */	cmplwi r29, 0
/* 8012BFAC 00128B8C  41 82 00 44 */	beq lbl_8012BFF0
/* 8012BFB0 00128B90  40 82 00 14 */	bne lbl_8012BFC4
/* 8012BFB4 00128B94  38 6D 87 B8 */	addi r3, r13, lbl_804D3E58
/* 8012BFB8 00128B98  38 80 02 34 */	li r4, 0x234
/* 8012BFBC 00128B9C  38 AD 87 C0 */	addi r5, r13, lbl_804D3E60
/* 8012BFC0 00128BA0  48 25 C2 61 */	bl __assert
lbl_8012BFC4:
/* 8012BFC4 00128BA4  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8012BFC8 00128BA8  38 60 00 00 */	li r3, 0
/* 8012BFCC 00128BAC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8012BFD0 00128BB0  40 82 00 10 */	bne lbl_8012BFE0
/* 8012BFD4 00128BB4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8012BFD8 00128BB8  41 82 00 08 */	beq lbl_8012BFE0
/* 8012BFDC 00128BBC  38 60 00 01 */	li r3, 1
lbl_8012BFE0:
/* 8012BFE0 00128BC0  2C 03 00 00 */	cmpwi r3, 0
/* 8012BFE4 00128BC4  40 82 00 0C */	bne lbl_8012BFF0
/* 8012BFE8 00128BC8  7F A3 EB 78 */	mr r3, r29
/* 8012BFEC 00128BCC  48 24 72 FD */	bl HSD_JObjSetMtxDirtySub
lbl_8012BFF0:
/* 8012BFF0 00128BD0  7F E3 FB 78 */	mr r3, r31
/* 8012BFF4 00128BD4  4B FF F8 B1 */	bl func_8012B8A4
/* 8012BFF8 00128BD8  7F C3 F3 78 */	mr r3, r30
/* 8012BFFC 00128BDC  4B F6 5D 5D */	bl func_80091D58
/* 8012C000 00128BE0  38 7E 00 00 */	addi r3, r30, 0
/* 8012C004 00128BE4  38 80 00 6E */	li r4, 0x6e
/* 8012C008 00128BE8  38 A0 00 7F */	li r5, 0x7f
/* 8012C00C 00128BEC  38 C0 00 40 */	li r6, 0x40
/* 8012C010 00128BF0  4B F5 C1 39 */	bl func_80088148
/* 8012C014 00128BF4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8012C018 00128BF8  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8012C01C 00128BFC  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8012C020 00128C00  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8012C024 00128C04  38 21 00 38 */	addi r1, r1, 0x38
/* 8012C028 00128C08  7C 08 03 A6 */	mtlr r0
/* 8012C02C 00128C0C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
