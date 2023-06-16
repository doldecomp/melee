#include "forward.h"

#include "fobj.h"

#include "spline.h"

#include <string.h>

HSD_ObjAllocData fobj_alloc_data;

HSD_ObjAllocData* HSD_FObjGetAllocData(void)
{
    return &fobj_alloc_data;
}

void HSD_FObjInitAllocData(void)
{
    HSD_ObjAllocInit(&fobj_alloc_data, sizeof(HSD_FObj), 4);
}

void HSD_FObjRemove(HSD_FObj* fobj)
{
    if (!fobj) {
        return;
    }

    HSD_FObjFree(fobj);
}

void HSD_FObjRemoveAll(HSD_FObj* fobj)
{
    if (fobj == NULL) {
        return;
    }
    HSD_FObjRemoveAll(fobj->next);
    HSD_FObjRemove(fobj);
}

u8 HSD_FObjSetState(HSD_FObj* fobj, u8 state)
{
    if (fobj) {
        fobj->flags = (state & 0xF) | (fobj->flags & 0xF0);
    }
    return state;
}

u32 HSD_FObjGetState(HSD_FObj* fobj)
{
    if (!fobj) {
        return 0;
    }
    return fobj->flags & 0xF;
}

inline void HSD_FObjReqAnim(HSD_FObj* fobj, f32 startframe)
{
    if (fobj == NULL) {
        return;
    }

    fobj->ad = fobj->ad_head;
    fobj->time = (f32) fobj->startframe + startframe;
    fobj->op = 0;
    fobj->op_intrp = 0;
    fobj->flags &= ~0x40;
    fobj->nb_pack = 0;
    fobj->fterm = 0;
    fobj->p0 = 0.f;
    fobj->p1 = 0.f;
    fobj->d0 = 0.f;
    fobj->d1 = 0.f;
    HSD_FObjSetState(fobj, 1);
}

void HSD_FObjReqAnimAll(HSD_FObj* fobj, f32 startframe)
{
    HSD_FObj* fp;

    if (fobj == NULL) {
        return;
    }

    for (fp = fobj; fp != NULL; fp = fp->next) {
        HSD_FObjReqAnim(fp, startframe);
    }
}

inline void FObj_FlushKeyData(HSD_FObj* fobj, void* obj,
                              HSD_ObjUpdateFunc obj_update, f32 rate)
{
    if (fobj->op_intrp == HSD_A_OP_KEY) {
        HSD_FObjInterpretAnim(fobj, obj, obj_update, rate);
    }
}

void HSD_FObjStopAnim(HSD_FObj* fobj, void* obj, HSD_ObjUpdateFunc obj_update,
                      f32 rate)
{
    if (fobj == NULL) {
        return;
    }

    FObj_FlushKeyData(fobj, obj, obj_update, rate);
    HSD_FObjSetState(fobj, 0);
}

void HSD_FObjStopAnimAll(HSD_FObj* fobj, void* obj,
                         HSD_ObjUpdateFunc obj_update, f32 rate)
{
    for (; fobj != NULL; fobj = fobj->next) {
        HSD_FObjStopAnim(fobj, obj, obj_update, rate);
    }
}

/*static*/ f32 parseFloat(u8** pos, u8 frac)
{
    union {
        f32 f;
        u32 d;
    } u;
    f32 numer;
    s32 denom;

    if (frac == HSD_A_FRAC_FLOAT) {
        u.d = (s32) ((*pos)++)[0];
        u.d |= ((*pos)++)[0] << 8;
        u.d |= ((*pos)++)[0] << 16;
        u.d |= ((*pos)++)[0] << 24;
        return u.f;
    }

    denom = (1 << (frac & 0x1F));
    switch (frac & 0xE0) {
    case HSD_A_FRAC_S8:
        numer = (s8) (*pos)[0];
        *pos += 1;
        break;
    case HSD_A_FRAC_U8:
        numer = (*pos)[0];
        *pos += 1;
        break;
    case HSD_A_FRAC_S16:
        numer = ((s8) (*pos)[1] << 8) | (*pos)[0];
        *pos += 2;
        break;
    case HSD_A_FRAC_U16:
        numer = ((*pos)[1] << 8) | (*pos)[0];
        *pos += 2;
        break;
    default:
        return 0.0f;
    }
    return numer / denom;
}

/*static*/ s32 parsePackInfo(u8** pos)
{
    u8 val;
    s32 result;
    s32 i;

    val = *(*pos)++;
    result = ((val >> 4) & 7) + 1;
    i = 3;
    if (!(val & 0x80)) {
        return result;
    }
    do {
        val = *(*pos)++;
        result += (val & 0x7F) << i;
        i += 7;
    } while (val & 0x80);
    return result;
}

/*static*/ void FObjLaunchKeyData(HSD_FObj* fobj)
{
    if ((fobj->flags & 0x40) != 0) {
        fobj->op_intrp = fobj->op;
        fobj->flags &= ~0x40;
        fobj->flags |= 0x80;
        fobj->p0 = fobj->p1;
    }
}

void FObjUpdateAnim(HSD_FObj* fobj, void* obj, HSD_ObjUpdateFunc obj_update)
{
    f32 phi_f0;
    HSD_ObjData fobjdata;

    if (obj_update == NULL) {
        return;
    }
    switch (fobj->op_intrp) {
    case HSD_A_OP_KEY:
        if (fobj->flags & 0x80) {
            fobjdata.fv = fobj->p0;
            fobj->flags &= 0xFFFFFF7F;
        } else {
            return;
        }
        break;
    case HSD_A_OP_CON:
        if (fobj->time >= fobj->fterm) {
            phi_f0 = fobj->p1;
        } else {
            phi_f0 = fobj->p0;
        }
        fobjdata.fv = phi_f0;
        break;
    case HSD_A_OP_LIN:
        if (fobj->flags & 0x20) {
            fobj->flags = fobj->flags & 0xFFFFFFDF;
            if (fobj->fterm != 0) {
                fobj->d0 = (fobj->p1 - fobj->p0) / fobj->fterm;
            } else {
                fobj->d0 = 0;
                fobj->p0 = fobj->p1;
            }
        }
        fobjdata.fv = fobj->d0 * fobj->time + fobj->p0;
        break;
    case HSD_A_OP_SPL0:
    case HSD_A_OP_SPL:
    case HSD_A_OP_SLP:
        if (fobj->fterm != 0) {
            fobjdata.fv =
                splGetHelmite(1.0 / fobj->fterm, fobj->time, fobj->p0,
                              fobj->p1, fobj->d0, fobj->d1);
        } else {
            fobjdata.fv = fobj->p1;
        }
        break;
    default:
        break;
    }
    obj_update(obj, fobj->obj_type, &fobjdata);
}

#define fobj_c_sdata2_start (HSD_FObj_804DE4F0 - 0x20)
#define lbl_804DE4E0 (fobj_c_sdata2_start + 0x10)

extern void* HSD_FObj_80406350[];

static char HSD_FObj_804D5D58[8] = "fobj.c";
static char HSD_FObj_804D5D60[8] = "new";

static const f64 HSD_FObj_804DE4F0 = 0.0;

#pragma push
asm void HSD_FObjInterpretAnim(HSD_FObj* fobj, void* obj,
                               HSD_ObjUpdateFunc obj_update, f32 rate)
{ // clang-format off
    nofralloc
/* 8036B030 00367C10  7C 08 02 A6 */	mflr r0
/* 8036B034 00367C14  90 01 00 04 */	stw r0, 4(r1)
/* 8036B038 00367C18  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 8036B03C 00367C1C  DB E1 00 A0 */	stfd f31, 0xa0(r1)
/* 8036B040 00367C20  DB C1 00 98 */	stfd f30, 0x98(r1)
/* 8036B044 00367C24  FF C0 08 90 */	fmr f30, f1
/* 8036B048 00367C28  DB A1 00 90 */	stfd f29, 0x90(r1)
/* 8036B04C 00367C2C  BF 41 00 78 */	stmw r26, 0x78(r1)
/* 8036B050 00367C30  7C 7F 1B 79 */	or. r31, r3, r3
/* 8036B054 00367C34  3C 60 80 40 */	lis r3, HSD_FObj_80406350@ha
/* 8036B058 00367C38  3B C3 63 50 */	addi r30, r3, HSD_FObj_80406350@l
/* 8036B05C 00367C3C  3B 84 00 00 */	addi r28, r4, 0
/* 8036B060 00367C40  3B 65 00 00 */	addi r27, r5, 0
/* 8036B064 00367C44  C3 A2 EA F0 */	lfs f29, 0.0f
/* 8036B068 00367C48  41 82 00 10 */	beq lbl_8036B078
/* 8036B06C 00367C4C  7F E3 FB 78 */	mr r3, r31
/* 8036B070 00367C50  4B FF F9 F5 */	bl HSD_FObjGetState
/* 8036B074 00367C54  48 00 00 08 */	b lbl_8036B07C
lbl_8036B078:
/* 8036B078 00367C58  38 60 00 00 */	li r3, 0
lbl_8036B07C:
/* 8036B07C 00367C5C  28 03 00 00 */	cmplwi r3, 0
/* 8036B080 00367C60  41 82 06 2C */	beq lbl_8036B6AC
/* 8036B084 00367C64  C0 1F 00 1C */	lfs f0, 0x1c(r31)
/* 8036B088 00367C68  EC 00 F0 2A */	fadds f0, f0, f30
/* 8036B08C 00367C6C  D0 1F 00 1C */	stfs f0, 0x1c(r31)
/* 8036B090 00367C70  C0 3F 00 1C */	lfs f1, 0x1c(r31)
/* 8036B094 00367C74  C8 02 EB 10 */	lfd f0, HSD_FObj_804DE4F0(r2)
/* 8036B098 00367C78  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8036B09C 00367C7C  41 80 06 10 */	blt lbl_8036B6AC
/* 8036B0A0 00367C80  CB E2 EB 00 */	lfd f31, lbl_804DE4E0(r2)
/* 8036B0A4 00367C84  3F A0 43 30 */	lis r29, 0x4330
/* 8036B0A8 00367C88  C3 C2 EA F0 */	lfs f30, 0.0f
lbl_8036B0AC:
/* 8036B0AC 00367C8C  2C 03 00 04 */	cmpwi r3, 4
/* 8036B0B0 00367C90  41 82 05 40 */	beq lbl_8036B5F0
/* 8036B0B4 00367C94  40 80 00 1C */	bge lbl_8036B0D0
/* 8036B0B8 00367C98  2C 03 00 00 */	cmpwi r3, 0
/* 8036B0BC 00367C9C  41 82 05 F0 */	beq lbl_8036B6AC
/* 8036B0C0 00367CA0  41 80 FF EC */	blt lbl_8036B0AC
/* 8036B0C4 00367CA4  2C 03 00 03 */	cmpwi r3, 3
/* 8036B0C8 00367CA8  40 80 04 5C */	bge lbl_8036B524
/* 8036B0CC 00367CAC  48 00 00 68 */	b lbl_8036B134
lbl_8036B0D0:
/* 8036B0D0 00367CB0  2C 03 00 06 */	cmpwi r3, 6
/* 8036B0D4 00367CB4  41 82 00 0C */	beq lbl_8036B0E0
/* 8036B0D8 00367CB8  40 80 FF D4 */	bge lbl_8036B0AC
/* 8036B0DC 00367CBC  48 00 05 B0 */	b lbl_8036B68C
lbl_8036B0E0:
/* 8036B0E0 00367CC0  C0 1F 00 1C */	lfs f0, 0x1c(r31)
/* 8036B0E4 00367CC4  EC 00 E8 2A */	fadds f0, f0, f29
/* 8036B0E8 00367CC8  D0 1F 00 1C */	stfs f0, 0x1c(r31)
/* 8036B0EC 00367CCC  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B0F0 00367CD0  54 00 06 73 */	rlwinm. r0, r0, 0, 0x19, 0x19
/* 8036B0F4 00367CD4  41 82 00 2C */	beq lbl_8036B120
/* 8036B0F8 00367CD8  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 8036B0FC 00367CDC  98 1F 00 12 */	stb r0, 0x12(r31)
/* 8036B100 00367CE0  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B104 00367CE4  54 00 06 B0 */	rlwinm r0, r0, 0, 0x1a, 0x18
/* 8036B108 00367CE8  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B10C 00367CEC  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B110 00367CF0  60 00 00 80 */	ori r0, r0, 0x80
/* 8036B114 00367CF4  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B118 00367CF8  C0 1F 00 24 */	lfs f0, 0x24(r31)
/* 8036B11C 00367CFC  D0 1F 00 20 */	stfs f0, 0x20(r31)
lbl_8036B120:
/* 8036B120 00367D00  38 7F 00 00 */	addi r3, r31, 0
/* 8036B124 00367D04  38 9C 00 00 */	addi r4, r28, 0
/* 8036B128 00367D08  38 BB 00 00 */	addi r5, r27, 0
/* 8036B12C 00367D0C  4B FF FD 45 */	bl FObjUpdateAnim
/* 8036B130 00367D10  48 00 05 7C */	b lbl_8036B6AC
lbl_8036B134:
/* 8036B134 00367D14  80 9F 00 08 */	lwz r4, 8(r31)
/* 8036B138 00367D18  80 7F 00 04 */	lwz r3, 4(r31)
/* 8036B13C 00367D1C  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 8036B140 00367D20  7C 64 18 50 */	subf r3, r4, r3
/* 8036B144 00367D24  7C 03 00 40 */	cmplw r3, r0
/* 8036B148 00367D28  41 80 00 0C */	blt lbl_8036B154
/* 8036B14C 00367D2C  38 60 00 06 */	li r3, 6
/* 8036B150 00367D30  4B FF FF 5C */	b lbl_8036B0AC
lbl_8036B154:
/* 8036B154 00367D34  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 8036B158 00367D38  98 1F 00 12 */	stb r0, 0x12(r31)
/* 8036B15C 00367D3C  A0 1F 00 16 */	lhz r0, 0x16(r31)
/* 8036B160 00367D40  28 00 00 00 */	cmplwi r0, 0
/* 8036B164 00367D44  40 82 00 20 */	bne lbl_8036B184
/* 8036B168 00367D48  80 9F 00 04 */	lwz r4, 4(r31)
/* 8036B16C 00367D4C  38 7F 00 04 */	addi r3, r31, 4
/* 8036B170 00367D50  88 04 00 00 */	lbz r0, 0(r4)
/* 8036B174 00367D54  54 00 07 3E */	clrlwi r0, r0, 0x1c
/* 8036B178 00367D58  98 1F 00 11 */	stb r0, 0x11(r31)
/* 8036B17C 00367D5C  4B FF FC 61 */	bl parsePackInfo
/* 8036B180 00367D60  B0 7F 00 16 */	sth r3, 0x16(r31)
lbl_8036B184:
/* 8036B184 00367D64  A0 7F 00 16 */	lhz r3, 0x16(r31)
/* 8036B188 00367D68  38 03 FF FF */	addi r0, r3, -1
/* 8036B18C 00367D6C  B0 1F 00 16 */	sth r0, 0x16(r31)
/* 8036B190 00367D70  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 8036B194 00367D74  2C 00 00 04 */	cmpwi r0, 4
/* 8036B198 00367D78  41 82 02 00 */	beq lbl_8036B398
/* 8036B19C 00367D7C  40 80 00 1C */	bge lbl_8036B1B8
/* 8036B1A0 00367D80  2C 00 00 02 */	cmpwi r0, 2
/* 8036B1A4 00367D84  41 82 00 C8 */	beq lbl_8036B26C
/* 8036B1A8 00367D88  40 80 01 68 */	bge lbl_8036B310
/* 8036B1AC 00367D8C  2C 00 00 01 */	cmpwi r0, 1
/* 8036B1B0 00367D90  40 80 00 18 */	bge lbl_8036B1C8
/* 8036B1B4 00367D94  48 00 03 68 */	b lbl_8036B51C
lbl_8036B1B8:
/* 8036B1B8 00367D98  2C 00 00 06 */	cmpwi r0, 6
/* 8036B1BC 00367D9C  41 82 02 D8 */	beq lbl_8036B494
/* 8036B1C0 00367DA0  40 80 03 5C */	bge lbl_8036B51C
/* 8036B1C4 00367DA4  48 00 02 68 */	b lbl_8036B42C
lbl_8036B1C8:
/* 8036B1C8 00367DA8  28 1F 00 00 */	cmplwi r31, 0
/* 8036B1CC 00367DAC  40 82 00 0C */	bne lbl_8036B1D8
/* 8036B1D0 00367DB0  3B 40 00 00 */	li r26, 0
/* 8036B1D4 00367DB4  48 00 00 0C */	b lbl_8036B1E0
lbl_8036B1D8:
/* 8036B1D8 00367DB8  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B1DC 00367DBC  54 1A 07 3E */	clrlwi r26, r0, 0x1c
lbl_8036B1E0:
/* 8036B1E0 00367DC0  38 1A FF FF */	addi r0, r26, -1
/* 8036B1E4 00367DC4  28 00 00 01 */	cmplwi r0, 1
/* 8036B1E8 00367DC8  38 00 00 01 */	li r0, 1
/* 8036B1EC 00367DCC  40 81 00 08 */	ble lbl_8036B1F4
/* 8036B1F0 00367DD0  38 00 00 00 */	li r0, 0
lbl_8036B1F4:
/* 8036B1F4 00367DD4  2C 00 00 00 */	cmpwi r0, 0
/* 8036B1F8 00367DD8  40 82 00 14 */	bne lbl_8036B20C
/* 8036B1FC 00367DDC  38 BE 00 18 */	addi r5, r30, 0x18
/* 8036B200 00367DE0  38 6D A6 B8 */	addi r3, r13, HSD_FObj_804D5D58
/* 8036B204 00367DE4  38 80 01 7F */	li r4, 0x17f
/* 8036B208 00367DE8  48 01 D0 19 */	bl __assert
lbl_8036B20C:
/* 8036B20C 00367DEC  C0 1F 00 24 */	lfs f0, 0x24(r31)
/* 8036B210 00367DF0  38 7F 00 04 */	addi r3, r31, 4
/* 8036B214 00367DF4  D0 1F 00 20 */	stfs f0, 0x20(r31)
/* 8036B218 00367DF8  88 9F 00 14 */	lbz r4, 0x14(r31)
/* 8036B21C 00367DFC  4B FF F9 F5 */	bl parseFloat
/* 8036B220 00367E00  D0 3F 00 24 */	stfs f1, 0x24(r31)
/* 8036B224 00367E04  88 1F 00 12 */	lbz r0, 0x12(r31)
/* 8036B228 00367E08  28 00 00 05 */	cmplwi r0, 5
/* 8036B22C 00367E0C  41 82 00 10 */	beq lbl_8036B23C
/* 8036B230 00367E10  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8036B234 00367E14  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 8036B238 00367E18  D3 DF 00 2C */	stfs f30, 0x2c(r31)
lbl_8036B23C:
/* 8036B23C 00367E1C  28 1A 00 01 */	cmplwi r26, 1
/* 8036B240 00367E20  40 82 00 0C */	bne lbl_8036B24C
/* 8036B244 00367E24  38 60 00 03 */	li r3, 3
/* 8036B248 00367E28  48 00 00 08 */	b lbl_8036B250
lbl_8036B24C:
/* 8036B24C 00367E2C  38 60 00 04 */	li r3, 4
lbl_8036B250:
/* 8036B250 00367E30  28 1F 00 00 */	cmplwi r31, 0
/* 8036B254 00367E34  41 82 FE 58 */	beq lbl_8036B0AC
/* 8036B258 00367E38  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B25C 00367E3C  54 00 06 36 */	rlwinm r0, r0, 0, 0x18, 0x1b
/* 8036B260 00367E40  50 60 07 3E */	rlwimi r0, r3, 0, 0x1c, 0x1f
/* 8036B264 00367E44  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B268 00367E48  4B FF FE 44 */	b lbl_8036B0AC
lbl_8036B26C:
/* 8036B26C 00367E4C  28 1F 00 00 */	cmplwi r31, 0
/* 8036B270 00367E50  40 82 00 0C */	bne lbl_8036B27C
/* 8036B274 00367E54  3B 40 00 00 */	li r26, 0
/* 8036B278 00367E58  48 00 00 0C */	b lbl_8036B284
lbl_8036B27C:
/* 8036B27C 00367E5C  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B280 00367E60  54 1A 07 3E */	clrlwi r26, r0, 0x1c
lbl_8036B284:
/* 8036B284 00367E64  38 1A FF FF */	addi r0, r26, -1
/* 8036B288 00367E68  28 00 00 01 */	cmplwi r0, 1
/* 8036B28C 00367E6C  38 00 00 01 */	li r0, 1
/* 8036B290 00367E70  40 81 00 08 */	ble lbl_8036B298
/* 8036B294 00367E74  38 00 00 00 */	li r0, 0
lbl_8036B298:
/* 8036B298 00367E78  2C 00 00 00 */	cmpwi r0, 0
/* 8036B29C 00367E7C  40 82 00 14 */	bne lbl_8036B2B0
/* 8036B2A0 00367E80  38 BE 00 18 */	addi r5, r30, 0x18
/* 8036B2A4 00367E84  38 6D A6 B8 */	addi r3, r13, HSD_FObj_804D5D58
/* 8036B2A8 00367E88  38 80 01 93 */	li r4, 0x193
/* 8036B2AC 00367E8C  48 01 CF 75 */	bl __assert
lbl_8036B2B0:
/* 8036B2B0 00367E90  C0 1F 00 24 */	lfs f0, 0x24(r31)
/* 8036B2B4 00367E94  38 7F 00 04 */	addi r3, r31, 4
/* 8036B2B8 00367E98  D0 1F 00 20 */	stfs f0, 0x20(r31)
/* 8036B2BC 00367E9C  88 9F 00 14 */	lbz r4, 0x14(r31)
/* 8036B2C0 00367EA0  4B FF F9 51 */	bl parseFloat
/* 8036B2C4 00367EA4  D0 3F 00 24 */	stfs f1, 0x24(r31)
/* 8036B2C8 00367EA8  88 1F 00 12 */	lbz r0, 0x12(r31)
/* 8036B2CC 00367EAC  28 00 00 05 */	cmplwi r0, 5
/* 8036B2D0 00367EB0  41 82 00 10 */	beq lbl_8036B2E0
/* 8036B2D4 00367EB4  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8036B2D8 00367EB8  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 8036B2DC 00367EBC  D3 DF 00 2C */	stfs f30, 0x2c(r31)
lbl_8036B2E0:
/* 8036B2E0 00367EC0  28 1A 00 01 */	cmplwi r26, 1
/* 8036B2E4 00367EC4  40 82 00 0C */	bne lbl_8036B2F0
/* 8036B2E8 00367EC8  38 60 00 03 */	li r3, 3
/* 8036B2EC 00367ECC  48 00 00 08 */	b lbl_8036B2F4
lbl_8036B2F0:
/* 8036B2F0 00367ED0  38 60 00 04 */	li r3, 4
lbl_8036B2F4:
/* 8036B2F4 00367ED4  28 1F 00 00 */	cmplwi r31, 0
/* 8036B2F8 00367ED8  41 82 FD B4 */	beq lbl_8036B0AC
/* 8036B2FC 00367EDC  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B300 00367EE0  54 00 06 36 */	rlwinm r0, r0, 0, 0x18, 0x1b
/* 8036B304 00367EE4  50 60 07 3E */	rlwimi r0, r3, 0, 0x1c, 0x1f
/* 8036B308 00367EE8  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B30C 00367EEC  4B FF FD A0 */	b lbl_8036B0AC
lbl_8036B310:
/* 8036B310 00367EF0  28 1F 00 00 */	cmplwi r31, 0
/* 8036B314 00367EF4  40 82 00 0C */	bne lbl_8036B320
/* 8036B318 00367EF8  3B 40 00 00 */	li r26, 0
/* 8036B31C 00367EFC  48 00 00 0C */	b lbl_8036B328
lbl_8036B320:
/* 8036B320 00367F00  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B324 00367F04  54 1A 07 3E */	clrlwi r26, r0, 0x1c
lbl_8036B328:
/* 8036B328 00367F08  38 1A FF FF */	addi r0, r26, -1
/* 8036B32C 00367F0C  28 00 00 01 */	cmplwi r0, 1
/* 8036B330 00367F10  38 00 00 01 */	li r0, 1
/* 8036B334 00367F14  40 81 00 08 */	ble lbl_8036B33C
/* 8036B338 00367F18  38 00 00 00 */	li r0, 0
lbl_8036B33C:
/* 8036B33C 00367F1C  2C 00 00 00 */	cmpwi r0, 0
/* 8036B340 00367F20  40 82 00 14 */	bne lbl_8036B354
/* 8036B344 00367F24  38 BE 00 18 */	addi r5, r30, 0x18
/* 8036B348 00367F28  38 6D A6 B8 */	addi r3, r13, HSD_FObj_804D5D58
/* 8036B34C 00367F2C  38 80 01 A7 */	li r4, 0x1a7
/* 8036B350 00367F30  48 01 CE D1 */	bl __assert
lbl_8036B354:
/* 8036B354 00367F34  C0 1F 00 24 */	lfs f0, 0x24(r31)
/* 8036B358 00367F38  38 7F 00 04 */	addi r3, r31, 4
/* 8036B35C 00367F3C  D0 1F 00 20 */	stfs f0, 0x20(r31)
/* 8036B360 00367F40  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8036B364 00367F44  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 8036B368 00367F48  88 9F 00 14 */	lbz r4, 0x14(r31)
/* 8036B36C 00367F4C  4B FF F8 A5 */	bl parseFloat
/* 8036B370 00367F50  D0 3F 00 24 */	stfs f1, 0x24(r31)
/* 8036B374 00367F54  28 1A 00 01 */	cmplwi r26, 1
/* 8036B378 00367F58  D3 DF 00 2C */	stfs f30, 0x2c(r31)
/* 8036B37C 00367F5C  40 82 00 0C */	bne lbl_8036B388
/* 8036B380 00367F60  38 80 00 03 */	li r4, 3
/* 8036B384 00367F64  48 00 00 08 */	b lbl_8036B38C
lbl_8036B388:
/* 8036B388 00367F68  38 80 00 04 */	li r4, 4
lbl_8036B38C:
/* 8036B38C 00367F6C  7F E3 FB 78 */	mr r3, r31
/* 8036B390 00367F70  4B FF F6 B5 */	bl HSD_FObjSetState
/* 8036B394 00367F74  4B FF FD 18 */	b lbl_8036B0AC
lbl_8036B398:
/* 8036B398 00367F78  28 1F 00 00 */	cmplwi r31, 0
/* 8036B39C 00367F7C  40 82 00 0C */	bne lbl_8036B3A8
/* 8036B3A0 00367F80  3B 40 00 00 */	li r26, 0
/* 8036B3A4 00367F84  48 00 00 0C */	b lbl_8036B3B0
lbl_8036B3A8:
/* 8036B3A8 00367F88  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B3AC 00367F8C  54 1A 07 3E */	clrlwi r26, r0, 0x1c
lbl_8036B3B0:
/* 8036B3B0 00367F90  38 1A FF FF */	addi r0, r26, -1
/* 8036B3B4 00367F94  28 00 00 01 */	cmplwi r0, 1
/* 8036B3B8 00367F98  38 00 00 01 */	li r0, 1
/* 8036B3BC 00367F9C  40 81 00 08 */	ble lbl_8036B3C4
/* 8036B3C0 00367FA0  38 00 00 00 */	li r0, 0
lbl_8036B3C4:
/* 8036B3C4 00367FA4  2C 00 00 00 */	cmpwi r0, 0
/* 8036B3C8 00367FA8  40 82 00 14 */	bne lbl_8036B3DC
/* 8036B3CC 00367FAC  38 BE 00 18 */	addi r5, r30, 0x18
/* 8036B3D0 00367FB0  38 6D A6 B8 */	addi r3, r13, HSD_FObj_804D5D58
/* 8036B3D4 00367FB4  38 80 01 B9 */	li r4, 0x1b9
/* 8036B3D8 00367FB8  48 01 CE 49 */	bl __assert
lbl_8036B3DC:
/* 8036B3DC 00367FBC  C0 1F 00 24 */	lfs f0, 0x24(r31)
/* 8036B3E0 00367FC0  38 7F 00 04 */	addi r3, r31, 4
/* 8036B3E4 00367FC4  D0 1F 00 20 */	stfs f0, 0x20(r31)
/* 8036B3E8 00367FC8  88 9F 00 14 */	lbz r4, 0x14(r31)
/* 8036B3EC 00367FCC  4B FF F8 25 */	bl parseFloat
/* 8036B3F0 00367FD0  D0 3F 00 24 */	stfs f1, 0x24(r31)
/* 8036B3F4 00367FD4  38 7F 00 04 */	addi r3, r31, 4
/* 8036B3F8 00367FD8  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8036B3FC 00367FDC  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 8036B400 00367FE0  88 9F 00 15 */	lbz r4, 0x15(r31)
/* 8036B404 00367FE4  4B FF F8 0D */	bl parseFloat
/* 8036B408 00367FE8  28 1A 00 01 */	cmplwi r26, 1
/* 8036B40C 00367FEC  D0 3F 00 2C */	stfs f1, 0x2c(r31)
/* 8036B410 00367FF0  40 82 00 0C */	bne lbl_8036B41C
/* 8036B414 00367FF4  38 80 00 03 */	li r4, 3
/* 8036B418 00367FF8  48 00 00 08 */	b lbl_8036B420
lbl_8036B41C:
/* 8036B41C 00367FFC  38 80 00 04 */	li r4, 4
lbl_8036B420:
/* 8036B420 00368000  7F E3 FB 78 */	mr r3, r31
/* 8036B424 00368004  4B FF F6 21 */	bl HSD_FObjSetState
/* 8036B428 00368008  4B FF FC 84 */	b lbl_8036B0AC
lbl_8036B42C:
/* 8036B42C 0036800C  28 1F 00 00 */	cmplwi r31, 0
/* 8036B430 00368010  40 82 00 0C */	bne lbl_8036B43C
/* 8036B434 00368014  38 60 00 00 */	li r3, 0
/* 8036B438 00368018  48 00 00 0C */	b lbl_8036B444
lbl_8036B43C:
/* 8036B43C 0036801C  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B440 00368020  54 03 07 3E */	clrlwi r3, r0, 0x1c
lbl_8036B444:
/* 8036B444 00368024  38 03 FF FF */	addi r0, r3, -1
/* 8036B448 00368028  28 00 00 01 */	cmplwi r0, 1
/* 8036B44C 0036802C  38 00 00 01 */	li r0, 1
/* 8036B450 00368030  40 81 00 08 */	ble lbl_8036B458
/* 8036B454 00368034  38 00 00 00 */	li r0, 0
lbl_8036B458:
/* 8036B458 00368038  2C 00 00 00 */	cmpwi r0, 0
/* 8036B45C 0036803C  40 82 00 14 */	bne lbl_8036B470
/* 8036B460 00368040  38 BE 00 18 */	addi r5, r30, 0x18
/* 8036B464 00368044  38 6D A6 B8 */	addi r3, r13, HSD_FObj_804D5D58
/* 8036B468 00368048  38 80 01 CC */	li r4, 0x1cc
/* 8036B46C 0036804C  48 01 CD B5 */	bl __assert
lbl_8036B470:
/* 8036B470 00368050  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8036B474 00368054  38 7F 00 04 */	addi r3, r31, 4
/* 8036B478 00368058  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 8036B47C 0036805C  88 9F 00 15 */	lbz r4, 0x15(r31)
/* 8036B480 00368060  4B FF F7 91 */	bl parseFloat
/* 8036B484 00368064  D0 3F 00 2C */	stfs f1, 0x2c(r31)
/* 8036B488 00368068  7F E3 FB 78 */	mr r3, r31
/* 8036B48C 0036806C  4B FF F5 D9 */	bl HSD_FObjGetState
/* 8036B490 00368070  4B FF FC 1C */	b lbl_8036B0AC
lbl_8036B494:
/* 8036B494 00368074  28 1F 00 00 */	cmplwi r31, 0
/* 8036B498 00368078  40 82 00 0C */	bne lbl_8036B4A4
/* 8036B49C 0036807C  3B 40 00 00 */	li r26, 0
/* 8036B4A0 00368080  48 00 00 0C */	b lbl_8036B4AC
lbl_8036B4A4:
/* 8036B4A4 00368084  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B4A8 00368088  54 1A 07 3E */	clrlwi r26, r0, 0x1c
lbl_8036B4AC:
/* 8036B4AC 0036808C  38 1A FF FF */	addi r0, r26, -1
/* 8036B4B0 00368090  28 00 00 01 */	cmplwi r0, 1
/* 8036B4B4 00368094  38 00 00 01 */	li r0, 1
/* 8036B4B8 00368098  40 81 00 08 */	ble lbl_8036B4C0
/* 8036B4BC 0036809C  38 00 00 00 */	li r0, 0
lbl_8036B4C0:
/* 8036B4C0 003680A0  2C 00 00 00 */	cmpwi r0, 0
/* 8036B4C4 003680A4  40 82 00 14 */	bne lbl_8036B4D8
/* 8036B4C8 003680A8  38 BE 00 18 */	addi r5, r30, 0x18
/* 8036B4CC 003680AC  38 6D A6 B8 */	addi r3, r13, HSD_FObj_804D5D58
/* 8036B4D0 003680B0  38 80 01 E9 */	li r4, 0x1e9
/* 8036B4D4 003680B4  48 01 CD 4D */	bl __assert
lbl_8036B4D8:
/* 8036B4D8 003680B8  7F E3 FB 78 */	mr r3, r31
/* 8036B4DC 003680BC  4B FF F9 5D */	bl FObjLaunchKeyData
/* 8036B4E0 003680C0  38 7F 00 04 */	addi r3, r31, 4
/* 8036B4E4 003680C4  88 9F 00 14 */	lbz r4, 0x14(r31)
/* 8036B4E8 003680C8  4B FF F7 29 */	bl parseFloat
/* 8036B4EC 003680CC  D0 3F 00 24 */	stfs f1, 0x24(r31)
/* 8036B4F0 003680D0  28 1A 00 01 */	cmplwi r26, 1
/* 8036B4F4 003680D4  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B4F8 003680D8  60 00 00 40 */	ori r0, r0, 0x40
/* 8036B4FC 003680DC  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B500 003680E0  40 82 00 0C */	bne lbl_8036B50C
/* 8036B504 003680E4  38 80 00 03 */	li r4, 3
/* 8036B508 003680E8  48 00 00 08 */	b lbl_8036B510
lbl_8036B50C:
/* 8036B50C 003680EC  38 80 00 04 */	li r4, 4
lbl_8036B510:
/* 8036B510 003680F0  7F E3 FB 78 */	mr r3, r31
/* 8036B514 003680F4  4B FF F5 31 */	bl HSD_FObjSetState
/* 8036B518 003680F8  4B FF FB 94 */	b lbl_8036B0AC
lbl_8036B51C:
/* 8036B51C 003680FC  38 60 00 00 */	li r3, 0
/* 8036B520 00368100  4B FF FB 8C */	b lbl_8036B0AC
lbl_8036B524:
/* 8036B524 00368104  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B528 00368108  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 8036B52C 0036810C  41 82 00 14 */	beq lbl_8036B540
/* 8036B530 00368110  38 7F 00 00 */	addi r3, r31, 0
/* 8036B534 00368114  38 9C 00 00 */	addi r4, r28, 0
/* 8036B538 00368118  38 BB 00 00 */	addi r5, r27, 0
/* 8036B53C 0036811C  4B FF F9 35 */	bl FObjUpdateAnim
lbl_8036B540:
/* 8036B540 00368120  28 1F 00 00 */	cmplwi r31, 0
/* 8036B544 00368124  40 82 00 0C */	bne lbl_8036B550
/* 8036B548 00368128  38 00 00 00 */	li r0, 0
/* 8036B54C 0036812C  48 00 00 0C */	b lbl_8036B558
lbl_8036B550:
/* 8036B550 00368130  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B554 00368134  54 00 07 3E */	clrlwi r0, r0, 0x1c
lbl_8036B558:
/* 8036B558 00368138  28 00 00 03 */	cmplwi r0, 3
/* 8036B55C 0036813C  41 82 00 14 */	beq lbl_8036B570
/* 8036B560 00368140  38 BE 00 00 */	addi r5, r30, 0
/* 8036B564 00368144  38 6D A6 B8 */	addi r3, r13, HSD_FObj_804D5D58
/* 8036B568 00368148  38 80 01 6C */	li r4, 0x16c
/* 8036B56C 0036814C  48 01 CC B5 */	bl __assert
lbl_8036B570:
/* 8036B570 00368150  80 9F 00 08 */	lwz r4, 8(r31)
/* 8036B574 00368154  80 7F 00 04 */	lwz r3, 4(r31)
/* 8036B578 00368158  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 8036B57C 0036815C  7C 64 18 50 */	subf r3, r4, r3
/* 8036B580 00368160  7C 03 00 40 */	cmplw r3, r0
/* 8036B584 00368164  41 80 00 0C */	blt lbl_8036B590
/* 8036B588 00368168  38 60 00 06 */	li r3, 6
/* 8036B58C 0036816C  4B FF FB 20 */	b lbl_8036B0AC
lbl_8036B590:
/* 8036B590 00368170  38 A0 00 00 */	li r5, 0
/* 8036B594 00368174  38 85 00 00 */	addi r4, r5, 0
lbl_8036B598:
/* 8036B598 00368178  80 7F 00 04 */	lwz r3, 4(r31)
/* 8036B59C 0036817C  38 03 00 01 */	addi r0, r3, 1
/* 8036B5A0 00368180  90 1F 00 04 */	stw r0, 4(r31)
/* 8036B5A4 00368184  88 63 00 00 */	lbz r3, 0(r3)
/* 8036B5A8 00368188  54 60 06 31 */	rlwinm. r0, r3, 0, 0x18, 0x18
/* 8036B5AC 0036818C  54 63 06 7E */	clrlwi r3, r3, 0x19
/* 8036B5B0 00368190  7C 63 20 30 */	slw r3, r3, r4
/* 8036B5B4 00368194  7C A5 1B 78 */	or r5, r5, r3
/* 8036B5B8 00368198  38 84 00 07 */	addi r4, r4, 7
/* 8036B5BC 0036819C  40 82 FF DC */	bne lbl_8036B598
/* 8036B5C0 003681A0  B0 BF 00 1A */	sth r5, 0x1a(r31)
/* 8036B5C4 003681A4  28 1F 00 00 */	cmplwi r31, 0
/* 8036B5C8 003681A8  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B5CC 003681AC  60 00 00 20 */	ori r0, r0, 0x20
/* 8036B5D0 003681B0  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B5D4 003681B4  41 82 00 14 */	beq lbl_8036B5E8
/* 8036B5D8 003681B8  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B5DC 003681BC  54 00 06 36 */	rlwinm r0, r0, 0, 0x18, 0x1b
/* 8036B5E0 003681C0  60 00 00 02 */	ori r0, r0, 2
/* 8036B5E4 003681C4  98 1F 00 10 */	stb r0, 0x10(r31)
lbl_8036B5E8:
/* 8036B5E8 003681C8  38 60 00 02 */	li r3, 2
/* 8036B5EC 003681CC  4B FF FA C0 */	b lbl_8036B0AC
lbl_8036B5F0:
/* 8036B5F0 003681D0  A0 1F 00 1A */	lhz r0, 0x1a(r31)
/* 8036B5F4 003681D4  C0 3F 00 1C */	lfs f1, 0x1c(r31)
/* 8036B5F8 003681D8  90 01 00 74 */	stw r0, 0x74(r1)
/* 8036B5FC 003681DC  93 A1 00 70 */	stw r29, 0x70(r1)
/* 8036B600 003681E0  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 8036B604 003681E4  EC 00 F8 28 */	fsubs f0, f0, f31
/* 8036B608 003681E8  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8036B60C 003681EC  4C 40 13 82 */	cror 2, 0, 2
/* 8036B610 003681F0  40 82 00 4C */	bne lbl_8036B65C
/* 8036B614 003681F4  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8036B618 003681F8  28 1F 00 00 */	cmplwi r31, 0
/* 8036B61C 003681FC  38 60 00 03 */	li r3, 3
/* 8036B620 00368200  93 A1 00 68 */	stw r29, 0x68(r1)
/* 8036B624 00368204  C8 01 00 68 */	lfd f0, 0x68(r1)
/* 8036B628 00368208  90 01 00 74 */	stw r0, 0x74(r1)
/* 8036B62C 0036820C  EC 00 F8 28 */	fsubs f0, f0, f31
/* 8036B630 00368210  93 A1 00 70 */	stw r29, 0x70(r1)
/* 8036B634 00368214  EC 01 00 28 */	fsubs f0, f1, f0
/* 8036B638 00368218  C8 21 00 70 */	lfd f1, 0x70(r1)
/* 8036B63C 0036821C  EF A1 F8 28 */	fsubs f29, f1, f31
/* 8036B640 00368220  D0 1F 00 1C */	stfs f0, 0x1c(r31)
/* 8036B644 00368224  41 82 FA 68 */	beq lbl_8036B0AC
/* 8036B648 00368228  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B64C 0036822C  54 00 06 36 */	rlwinm r0, r0, 0, 0x18, 0x1b
/* 8036B650 00368230  50 60 07 3E */	rlwimi r0, r3, 0, 0x1c, 0x1f
/* 8036B654 00368234  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B658 00368238  4B FF FA 54 */	b lbl_8036B0AC
lbl_8036B65C:
/* 8036B65C 0036823C  38 7F 00 00 */	addi r3, r31, 0
/* 8036B660 00368240  38 9C 00 00 */	addi r4, r28, 0
/* 8036B664 00368244  38 BB 00 00 */	addi r5, r27, 0
/* 8036B668 00368248  4B FF F8 09 */	bl FObjUpdateAnim
/* 8036B66C 0036824C  28 1F 00 00 */	cmplwi r31, 0
/* 8036B670 00368250  38 60 00 05 */	li r3, 5
/* 8036B674 00368254  41 82 00 38 */	beq lbl_8036B6AC
/* 8036B678 00368258  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B67C 0036825C  54 00 06 36 */	rlwinm r0, r0, 0, 0x18, 0x1b
/* 8036B680 00368260  50 60 07 3E */	rlwimi r0, r3, 0, 0x1c, 0x1f
/* 8036B684 00368264  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B688 00368268  48 00 00 24 */	b lbl_8036B6AC
lbl_8036B68C:
/* 8036B68C 0036826C  28 1F 00 00 */	cmplwi r31, 0
/* 8036B690 00368270  38 60 00 04 */	li r3, 4
/* 8036B694 00368274  41 82 FA 18 */	beq lbl_8036B0AC
/* 8036B698 00368278  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 8036B69C 0036827C  54 00 06 36 */	rlwinm r0, r0, 0, 0x18, 0x1b
/* 8036B6A0 00368280  50 60 07 3E */	rlwimi r0, r3, 0, 0x1c, 0x1f
/* 8036B6A4 00368284  98 1F 00 10 */	stb r0, 0x10(r31)
/* 8036B6A8 00368288  4B FF FA 04 */	b lbl_8036B0AC
lbl_8036B6AC:
/* 8036B6AC 0036828C  BB 41 00 78 */	lmw r26, 0x78(r1)
/* 8036B6B0 00368290  80 01 00 AC */	lwz r0, 0xac(r1)
/* 8036B6B4 00368294  CB E1 00 A0 */	lfd f31, 0xa0(r1)
/* 8036B6B8 00368298  CB C1 00 98 */	lfd f30, 0x98(r1)
/* 8036B6BC 0036829C  CB A1 00 90 */	lfd f29, 0x90(r1)
/* 8036B6C0 003682A0  38 21 00 A8 */	addi r1, r1, 0xa8
/* 8036B6C4 003682A4  7C 08 03 A6 */	mtlr r0
/* 8036B6C8 003682A8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

void HSD_FObjInterpretAnimAll(void* fobj, void* obj,
                              HSD_ObjUpdateFunc obj_update, f32 rate)
{
    HSD_FObj* fobjNew = (HSD_FObj*) fobj;
    while (fobjNew != NULL) {
        HSD_FObjInterpretAnim(fobjNew, obj, obj_update, rate);
        fobjNew = fobjNew->next;
    }
}

HSD_FObj* HSD_FObjLoadDesc(HSD_FObjDesc* desc)
{
    if (desc != NULL) {
        HSD_FObj* fobj = HSD_FObjAlloc();
        fobj->next = HSD_FObjLoadDesc(desc->next);
        fobj->startframe = desc->startframe;
        fobj->obj_type = desc->type;
        fobj->frac_value = desc->frac_value;
        fobj->frac_slope = desc->frac_slope;
        fobj->ad_head = desc->ad;
        fobj->length = desc->length;
        fobj->flags = 0;
        return fobj;
    }
    return NULL;
}

HSD_FObj* HSD_FObjAlloc(void)
{
    HSD_FObj* new = HSD_ObjAlloc(&fobj_alloc_data);
    if (new == NULL) {
        __assert(HSD_FObj_804D5D58, 0x2F3, HSD_FObj_804D5D60);
    }
    memset(new, 0, sizeof(HSD_FObj));
    return new;
}

void HSD_FObjFree(HSD_FObj* fobj)
{
    HSD_ObjFree(&fobj_alloc_data, fobj);
}
