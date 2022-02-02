#include "sysdolphin/baselib/fobj.h"

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
    if (!fobj)
        return;

    HSD_FObjFree(fobj);
}

void HSD_FObjRemoveAll(HSD_FObj* fobj) 
{
    if (fobj == NULL)
        return;
    HSD_FObjRemoveAll(fobj->next);
    HSD_FObjRemove(fobj);
}

u8 HSD_FObjSetState(HSD_FObj* fobj, u8 state)
{
    if (fobj)
        fobj->flags = (state & 0xF) | (fobj->flags & 0xF0);
    return state;
}

u32 HSD_FObjGetState(HSD_FObj* fobj)
{
    if (!fobj)
        return 0;
    return fobj->flags & 0xF;
}

// Non-matching because the conversion to float currently
#ifdef NON_MATCHING
inline void HSD_FObjReqAnim(HSD_FObj* fobj, f32 startframe)
{
    if (fobj == NULL)
        return;
    
    fobj->ad = fobj->ad_head;
    fobj->time = (f32)fobj->startframe + startframe;
    fobj->op = 0;
    fobj->op_intrp = 0;
    fobj->flags &= ~0x40;
    fobj->nb_pack = 0;
    fobj->fterm = 0;
    fobj->p0 = 0.f;
    fobj->p1 = 0.f;
    fobj->d0 = 0.f;
    fobj->d1 = 0.f;
    if (fobj != NULL)
        fobj->flags = (1 & 0xF) | (fobj->flags & 0xF0);
}

void HSD_FObjReqAnimAll(HSD_FObj* fobj, f32 startframe)
{
    HSD_FObj* fp;

    if (fobj == NULL)
        return;

    for (fp = fobj; fp != NULL; fp = fp->next) {
        HSD_FObjReqAnim(fp, startframe);
    }
}
#else
extern const f32 lbl_804DE4D0;
extern const f64 lbl_804DE4D8;

asm void HSD_FObjReqAnimAll(HSD_FObj* fobj, f32 startframe)
{
    nofralloc
/* 8036AA80 00367660  28 03 00 00 */	cmplwi r3, 0
/* 8036AA84 00367664  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8036AA88 00367668  41 82 00 94 */	beq lbl_8036AB1C
/* 8036AA8C 0036766C  C8 62 EA F8 */	lfd f3, lbl_804DE4D8(r2)
/* 8036AA90 00367670  3C A0 43 30 */	lis r5, 0x4330
/* 8036AA94 00367674  C0 02 EA F0 */	lfs f0, lbl_804DE4D0(r2)
/* 8036AA98 00367678  48 00 00 7C */	b lbl_8036AB14
lbl_8036AA9C:
/* 8036AA9C 0036767C  28 03 00 00 */	cmplwi r3, 0
/* 8036AAA0 00367680  41 82 00 70 */	beq lbl_8036AB10
/* 8036AAA4 00367684  80 03 00 08 */	lwz r0, 8(r3)
/* 8036AAA8 00367688  38 80 00 00 */	li r4, 0
/* 8036AAAC 0036768C  90 03 00 04 */	stw r0, 4(r3)
/* 8036AAB0 00367690  A8 03 00 18 */	lha r0, 0x18(r3)
/* 8036AAB4 00367694  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8036AAB8 00367698  90 01 00 14 */	stw r0, 0x14(r1)
/* 8036AABC 0036769C  90 A1 00 10 */	stw r5, 0x10(r1)
/* 8036AAC0 003676A0  C8 41 00 10 */	lfd f2, 0x10(r1)
/* 8036AAC4 003676A4  EC 42 18 28 */	fsubs f2, f2, f3
/* 8036AAC8 003676A8  EC 42 08 2A */	fadds f2, f2, f1
/* 8036AACC 003676AC  D0 43 00 1C */	stfs f2, 0x1c(r3)
/* 8036AAD0 003676B0  98 83 00 11 */	stb r4, 0x11(r3)
/* 8036AAD4 003676B4  98 83 00 12 */	stb r4, 0x12(r3)
/* 8036AAD8 003676B8  88 03 00 10 */	lbz r0, 0x10(r3)
/* 8036AADC 003676BC  54 00 06 B0 */	rlwinm r0, r0, 0, 0x1a, 0x18
/* 8036AAE0 003676C0  98 03 00 10 */	stb r0, 0x10(r3)
/* 8036AAE4 003676C4  B0 83 00 16 */	sth r4, 0x16(r3)
/* 8036AAE8 003676C8  B0 83 00 1A */	sth r4, 0x1a(r3)
/* 8036AAEC 003676CC  D0 03 00 20 */	stfs f0, 0x20(r3)
/* 8036AAF0 003676D0  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 8036AAF4 003676D4  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 8036AAF8 003676D8  D0 03 00 2C */	stfs f0, 0x2c(r3)
/* 8036AAFC 003676DC  41 82 00 14 */	beq lbl_8036AB10
/* 8036AB00 003676E0  88 03 00 10 */	lbz r0, 0x10(r3)
/* 8036AB04 003676E4  54 00 06 36 */	rlwinm r0, r0, 0, 0x18, 0x1b
/* 8036AB08 003676E8  60 00 00 01 */	ori r0, r0, 1
/* 8036AB0C 003676EC  98 03 00 10 */	stb r0, 0x10(r3)
lbl_8036AB10:
/* 8036AB10 003676F0  80 63 00 00 */	lwz r3, 0(r3)
lbl_8036AB14:
/* 8036AB14 003676F4  28 03 00 00 */	cmplwi r3, 0
/* 8036AB18 003676F8  40 82 FF 84 */	bne lbl_8036AA9C
lbl_8036AB1C:
/* 8036AB1C 003676FC  38 21 00 18 */	addi r1, r1, 0x18
/* 8036AB20 00367700  4E 80 00 20 */	blr 
}
#endif

#pragma push
#pragma peephole on
void HSD_FObjStopAnim(HSD_FObj* fobj, void* obj, void (*update_func)(), f32 rate) {
    if (fobj == NULL)
        return;
    
    if (fobj->op_intrp == HSD_A_OP_KEY) {
        HSD_FObjInterpretAnim(fobj, obj, update_func, rate);
    }
    
    if (fobj != NULL)
        fobj->flags = (0 & 0xF) | (fobj->flags & 0xF0);
}

inline void FObj_FlushKeyData(HSD_FObj* fobj, void* obj, void (*obj_update)(), f32 rate)
{
    if (fobj->op_intrp == HSD_A_OP_KEY) {
        HSD_FObjInterpretAnim(fobj, obj, obj_update, rate);
    }
}

inline void HSD_FObjStopAnim_inline(HSD_FObj* fobj, void* obj, void (*obj_update)(), f32 rate) {
    if (fobj == NULL)
        return;
    
    FObj_FlushKeyData(fobj, obj, obj_update, rate);
    
    if (fobj)
        fobj->flags = (0 & 0xF) | (fobj->flags & 0xF0);
}

void HSD_FObjStopAnimAll(HSD_FObj* fobj, void* obj, void (*obj_update)(), f32 rate)
{
    for (; fobj != NULL; fobj = fobj->next) {
        HSD_FObjStopAnim_inline(fobj, obj, obj_update, rate);
    }
}
#pragma pop
