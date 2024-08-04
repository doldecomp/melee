#include <dolphin.h>
#include <dolphin/ax.h>
#include <dolphin/axfx.h>
#include "fake_tgmath.h"

// functions
static void DLsetdelay(struct AXFX_REVSTD_DELAYLINE * dl, long lag);
static void DLcreate(struct AXFX_REVSTD_DELAYLINE * dl, long max_length);
static void DLdelete(struct AXFX_REVSTD_DELAYLINE * dl);
static int ReverbSTDCreate(struct AXFX_REVSTD_WORK * rv, float coloration, float time, float mix, float damping, float predelay);
static int ReverbSTDModify(struct AXFX_REVSTD_WORK * rv, float coloration, float time, float mix, float damping, float predelay);
static void HandleReverb(long * sptr, struct AXFX_REVSTD_WORK * rv);
static void ReverbSTDCallback(long * left, long * right, long * surround, struct AXFX_REVSTD_WORK * rv);
static void ReverbSTDFree(struct AXFX_REVSTD_WORK * rv);

static void DLsetdelay(struct AXFX_REVSTD_DELAYLINE * dl, long lag) {
    dl->outPoint = dl->inPoint - (lag * 4);
    while(dl->outPoint < 0) {
        dl->outPoint += dl->length;
    }
}

static void DLcreate(struct AXFX_REVSTD_DELAYLINE * dl, long max_length) {
    dl->length = (max_length * 4);
    dl->inputs = OSAllocFromHeap(__OSCurrHeap, max_length * 4);
    memset(dl->inputs, 0, max_length * 4);
    dl->lastOutput = 0.0f;
    DLsetdelay(dl, max_length >> 1);
    dl->inPoint = 0;
    dl->outPoint = 0;
}

static void DLdelete(struct AXFX_REVSTD_DELAYLINE * dl) {
    OSFreeToHeap(__OSCurrHeap, dl->inputs);
}

static int ReverbSTDCreate(struct AXFX_REVSTD_WORK * rv, float coloration, float time, float mix, float damping, float predelay) {
    u8 i;
    u8 k;
    static long lens[4] = {
        0x000006FD,
        0x000007CF,
        0x000001B1,
        0x00000095,
    };

    if ((coloration < 0.0f ) || (coloration > 1.0f ) 
     || (time       < 0.01f) || (time       > 10.0f) 
     || (mix        < 0.0f ) || (mix        > 1.0f ) 
     || (damping    < 0.0f ) || (damping    > 1.0f ) 
     || (predelay   < 0.0f ) || (predelay   > 0.1f )) {
        return 0;
    }

    memset(rv, 0, sizeof(struct AXFX_REVSTD_WORK));
    for(k = 0; k < 3; k++) {
        for(i = 0; i < 2; i++) {
            DLcreate(&rv->C[i + (k * 2)], lens[i] + 2);
            DLsetdelay(&rv->C[i + (k * 2)], lens[i]);
            rv->combCoef[i + (k * 2)] = powf(10.0f, (lens[i] * -3) / (32000.0f * time));
        }
        for(i = 0; i < 2; i++) {
            DLcreate(&rv->AP[i + (k * 2)], lens[i + 2] + 2);
            DLsetdelay(&rv->AP[i + (k * 2)], lens[i + 2]);
        }
        rv->lpLastout[k] = 0.0f;
    }
    rv->allPassCoeff = coloration;
    rv->level = mix;
    rv->damping = damping;
    if (rv->damping < 0.05f) {
        rv->damping = 0.05f;
    }
    rv->damping = (1.0f - (0.05f + (0.8f * rv->damping)));
    if (0.0f != predelay) {
        rv->preDelayTime = (32000.0f * predelay);
        for(i = 0; i < 3; i++) {
            rv->preDelayLine[i] = OSAllocFromHeap(__OSCurrHeap, rv->preDelayTime * 4);
            memset(rv->preDelayLine[i], 0, rv->preDelayTime * 4);
            rv->preDelayPtr[i] = rv->preDelayLine[i];
        }
    } else {
        rv->preDelayTime = 0;
        for(i = 0; i < 3; i++) {
            rv->preDelayPtr[i] = 0;
            rv->preDelayLine[i] = 0;
        }
    }
    return 1;
}

static int ReverbSTDModify(struct AXFX_REVSTD_WORK * rv, float coloration, float time, float mix, float damping, float predelay) {
    u8 i;

    if ((coloration < 0.0f ) || (coloration > 1.0f ) 
     || (time       < 0.01f) || (time       > 10.0f) 
     || (mix        < 0.0f ) || (mix        > 1.0f ) 
     || (damping    < 0.0f ) || (damping    > 1.0f ) 
     || (predelay   < 0.0f ) || (predelay   > 100.0f )) {
        return 0;
    }
    rv->allPassCoeff = coloration;
    rv->level = mix;
    rv->damping = damping;
    if (rv->damping < 0.05f) {
        rv->damping = 0.05f;
    }
    rv->damping = (1.0f - (0.05f + (0.8f * rv->damping)));
    for(i = 0; i < 6; i++) {
        DLdelete(&rv->AP[i]);
    }
    for(i = 0; i < 6; i++) {
        DLdelete(&rv->C[i]);
    }
    if (rv->preDelayTime) {
        for(i = 0; i < 3; i++) {
            OSFreeToHeap(__OSCurrHeap, rv->preDelayLine[i]);
        }
    }
    return ReverbSTDCreate(rv, coloration, time, mix, damping, predelay);
}

const static float value0_3 = 0.3f;
const static float value0_6 = 0.6f;
const static double i2fMagic = 4503601774854144.0;

asm static void HandleReverb(register long * sptr, register struct AXFX_REVSTD_WORK * rv) {
    nofralloc
	stwu r1, -144(r1)
	stmw r17, 8(r1)
	stfd f14, 88(r1)
	stfd f15, 96(r1)
	stfd f16, 104(r1)
	stfd f17, 112(r1)
	stfd f18, 120(r1)
	stfd f19, 128(r1)
	stfd f20, 136(r1)
	lis r31, value0_3@ha
	lfs f6, value0_3@l(r31)
	lis r31, value0_6@ha
	lfs f9, value0_6@l(r31)
	lis r31, i2fMagic@ha
	lfd f5, i2fMagic@l(r31)
	lfs f2, AXFX_REVSTD_WORK.allPassCoeff(rv)
	lfs f11, AXFX_REVSTD_WORK.damping(rv)
	lfs f8, AXFX_REVSTD_WORK.level(rv)
	fmuls f3, f8, f9
	fsubs f4, f9, f3
	lis r30, 0x4330 // 176.0f (0x43300000)
	stw r30, 80(r1)
	li r5, 0
L_00000638:
	slwi r31, r5, 3
	add r31, r31, rv
	lfs f19, AXFX_REVSTD_WORK.combCoef[0](r31)
	lfs f20, AXFX_REVSTD_WORK.combCoef[1](r31)
	slwi r31, r5, 2
	add r31, r31, rv
	lfs f7, AXFX_REVSTD_WORK.lpLastout[0](r31)
	lwz r27, AXFX_REVSTD_WORK.preDelayLine[0](r31)
	lwz r28, AXFX_REVSTD_WORK.preDelayPtr[0](r31)
	lwz r31, AXFX_REVSTD_WORK.preDelayTime(rv)
	subi r22, r31, 1
	slwi r22, r22, 2
	add r22, r22, r27
	cmpwi cr7, r31, 0
	mulli r31, r5, 0x28 // sizeof(struct AXFX_REVSTD_DELAYLINE * 2)
	addi r29, rv, AXFX_REVSTD_WORK.C
	add r29, r29, r31
	addi r30, rv, AXFX_REVSTD_WORK.AP
	add r30, r30, r31
	lwz r21, AXFX_REVSTD_DELAYLINE.inPoint    + 0x00(r29) // C array + 0
	lwz r20, AXFX_REVSTD_DELAYLINE.outPoint   + 0x00(r29) // C array + 0
	lwz r19, AXFX_REVSTD_DELAYLINE.inPoint    + 0x14(r29) // C array + 1
	lwz r18, AXFX_REVSTD_DELAYLINE.outPoint   + 0x14(r29) // C array + 1
	lfs f15, AXFX_REVSTD_DELAYLINE.lastOutput + 0x00(r29) // C array + 0
	lfs f16, AXFX_REVSTD_DELAYLINE.lastOutput + 0x14(r29) // C array + 1
	lwz r26, AXFX_REVSTD_DELAYLINE.length     + 0x00(r29) // C array + 0
	lwz r25, AXFX_REVSTD_DELAYLINE.length     + 0x14(r29) // C array + 1
	lwz r7,  AXFX_REVSTD_DELAYLINE.inputs     + 0x00(r29) // C array + 0
	lwz r8,  AXFX_REVSTD_DELAYLINE.inputs     + 0x14(r29) // C array + 1
	lwz r12, AXFX_REVSTD_DELAYLINE.inPoint    + 0x00(r30) // AP array + 0
	lwz r11, AXFX_REVSTD_DELAYLINE.outPoint   + 0x00(r30) // AP array + 0
	lwz r10, AXFX_REVSTD_DELAYLINE.inPoint    + 0x14(r30) // AP array + 1
	lwz r9,  AXFX_REVSTD_DELAYLINE.outPoint   + 0x14(r30) // AP array + 1
	lfs f17, AXFX_REVSTD_DELAYLINE.lastOutput + 0x00(r30) // AP array + 0
	lfs f18, AXFX_REVSTD_DELAYLINE.lastOutput + 0x14(r30) // AP array + 1
	lwz r24, AXFX_REVSTD_DELAYLINE.length     + 0x00(r30) // AP array + 0
	lwz r23, AXFX_REVSTD_DELAYLINE.length     + 0x14(r30) // AP array + 1
	lwz r17, AXFX_REVSTD_DELAYLINE.inputs     + 0x00(r30) // AP array + 0
	lwz r6,  AXFX_REVSTD_DELAYLINE.inputs     + 0x14(r30) // AP array + 1
	lwz r30, 0(sptr)
	xoris r30, r30, 0x8000
	stw r30, 84(r1)
	lfd f12, 80(r1)
	fsubs f12, f12, f5
	li r31, 159
	mtctr r31
L_000006F0:
	fmr f13, f12
	beq cr7, L_00000710
	lfs f13, 0(r28)
	addi r28, r28, 4
	cmpw r28, r22
	stfs f12, -4(r28)
	bne+ L_00000710
	mr r28, r27
L_00000710:
	fmadds f8, f19, f15, f13
	lwzu r29, 4(sptr)
	fmadds f9, f20, f16, f13
	stfsx f8, r7, r21
	addi r21, r21, 4
	stfsx f9, r8, r19
	lfsx f14, r7, r20
	addi r20, r20, 4
	lfsx f16, r8, r18
	cmpw r21, r26
	cmpw cr1, r20, r26
	addi r19, r19, 4
	addi r18, r18, 4
	fmr f15, f14
	cmpw cr5, r19, r25
	fadds f14, f14, f16
	cmpw cr6, r18, r25
	bne+ L_0000075C
	li r21, 0
L_0000075C:
	xoris r29, r29, 0x8000
	fmadds f9, f2, f17, f14
	bne+ cr1, L_0000076C
	li r20, 0
L_0000076C:
	stw r29, 84(r1)
	bne+ cr5, L_00000778
	li r19, 0
L_00000778:
	stfsx f9, r17, r12
	fnmsubs f14, f2, f9, f17
	addi r12, r12, 4
	bne+ cr6, L_0000078C
	li r18, 0
L_0000078C:
	lfsx f17, r17, r11
	cmpw cr5, r12, r24
	addi r11, r11, 4
	cmpw cr6, r11, r24
	bne+ cr5, L_000007A4
	li r12, 0
L_000007A4:
	bne+ cr6, L_000007AC
	li r11, 0
L_000007AC:
	fmuls f14, f14, f6
	lfd f10, 80(r1)
	fmadds f14, f11, f7, f14
	fmadds f9, f2, f18, f14
	fmr f7, f14
	stfsx f9, r6, r10
	fnmsubs f14, f2, f9, f18
	fmuls f8, f4, f12
	lfsx f18, r6, r9
	addi r10, r10, 4
	addi r9, r9, 4
	fmadds f14, f3, f14, f8
	cmpw cr5, r10, r23
	cmpw cr6, r9, r23
	fctiwz f14, f14
	bne+ cr5, L_000007F0
	li r10, 0
L_000007F0:
	bne+ cr6, L_000007F8
	li r9, 0
L_000007F8:
	li r31, -4
	fsubs f12, f10, f5
	stfiwx f14, sptr, r31
	bdnz L_000006F0
	fmr f13, f12
	beq cr7, L_00000828
	lfs f13, 0(r28)
	addi r28, r28, 4
	cmpw r28, r22
	stfs f12, -4(r28)
	bne+ L_00000828
	mr r28, r27
L_00000828:
	fmadds f8, f19, f15, f13
	fmadds f9, f20, f16, f13
	stfsx f8, r7, r21
	addi r21, r21, 4
	stfsx f9, r8, r19
	lfsx f14, r7, r20
	addi r20, r20, 4
	lfsx f16, r8, r18
	cmpw r21, r26
	cmpw cr1, r20, r26
	addi r19, r19, 4
	addi r18, r18, 4
	fmr f15, f14
	cmpw cr5, r19, r25
	fadds f14, f14, f16
	cmpw cr6, r18, r25
	bne+ L_00000870
	li r21, 0
L_00000870:
	fmadds f9, f2, f17, f14
	bne+ cr1, L_0000087C
	li r20, 0
L_0000087C:
	bne+ cr5, L_00000884
	li r19, 0
L_00000884:
	stfsx f9, r17, r12
	fnmsubs f14, f2, f9, f17
	addi r12, r12, 4
	bne+ cr6, L_00000898
	li r18, 0
L_00000898:
	lfsx f17, r17, r11
	cmpw cr5, r12, r24
	addi r11, r11, 4
	cmpw cr6, r11, r24
	bne+ cr5, L_000008B0
	li r12, 0
L_000008B0:
	bne+ cr6, L_000008B8
	li r11, 0
L_000008B8:
	fmuls f14, f14, f6
	fmadds f14, f11, f7, f14
	mulli r31, r5, 0x28 // sizeof(struct AXFX_REVSTD_DELAYLINE * 2)
	fmadds f9, f2, f18, f14
	fmr f7, f14
	addi r29, rv, AXFX_REVSTD_WORK.C
	add r29, r29, r31
	stfsx f9, r6, r10
	fnmsubs f14, f2, f9, f18
	fmuls f8, f4, f12
	lfsx f18, r6, r9
	addi r10, r10, 4
	addi r9, r9, 4
	fmadds f14, f3, f14, f8
	cmpw cr5, r10, r23
	cmpw cr6, r9, r23
	fctiwz f14, f14
	bne+ cr5, L_00000904
	li r10, 0
L_00000904:
	bne+ cr6, L_0000090C
	li r9, 0
L_0000090C:
	addi r30, rv, AXFX_REVSTD_WORK.AP
	add r30, r30, r31
	stfiwx f14, r0, sptr
	stw r21, AXFX_REVSTD_DELAYLINE.inPoint  + 0x00(r29) // C array + 0
	stw r20, AXFX_REVSTD_DELAYLINE.outPoint + 0x00(r29) // C array + 0
	stw r19, AXFX_REVSTD_DELAYLINE.inPoint  + 0x14(r29) // C array + 1
	stw r18, AXFX_REVSTD_DELAYLINE.outPoint + 0x14(r29) // C array + 1
	addi sptr, sptr, 4
	stfs f15, AXFX_REVSTD_DELAYLINE.lastOutput + 0x00(r29) // C array + 0
	stfs f16, AXFX_REVSTD_DELAYLINE.lastOutput + 0x14(r29) // C array + 1
	slwi r31, r5, 2
	add r31, r31, rv
	addi r5, r5, 1
	stw r12, AXFX_REVSTD_DELAYLINE.inPoint  + 0x00(r30) // AP array + 0
	stw r11, AXFX_REVSTD_DELAYLINE.outPoint + 0x00(r30) // AP array + 0
	stw r10, AXFX_REVSTD_DELAYLINE.inPoint  + 0x14(r30) // AP array + 1
	stw r9, AXFX_REVSTD_DELAYLINE.outPoint  + 0x14(r30) // AP array + 1
	cmpwi r5, 3
	stfs f17, AXFX_REVSTD_DELAYLINE.lastOutput + 0x00(r30) // AP array + 0
	stfs f18, AXFX_REVSTD_DELAYLINE.lastOutput + 0x14(r30) // AP array + 1
	stfs f7, AXFX_REVSTD_WORK.lpLastout(r31)
	stw r28, AXFX_REVSTD_WORK.preDelayPtr(r31)
	bne L_00000638
	lfd f14, 88(r1)
	lfd f15, 96(r1)
	lfd f16, 104(r1)
	lfd f17, 112(r1)
	lfd f18, 120(r1)
	lfd f19, 128(r1)
	lfd f20, 136(r1)
	lmw r17, 8(r1)
	addi r1, r1, 144
	blr
}

static void ReverbSTDCallback(long * left, long * right, long * surround, struct AXFX_REVSTD_WORK * rv) {
    HandleReverb(left, rv);
}

static void ReverbSTDFree(struct AXFX_REVSTD_WORK * rv) {
    u8 i;

    for(i = 0; i < 6; i++) {
        DLdelete(&rv->AP[i]);
    }
    for(i = 0; i < 6; i++) {
        DLdelete(&rv->C[i]);
    }
    if (rv->preDelayTime) {
        for(i = 0; i < 3; i++) {
            OSFreeToHeap(__OSCurrHeap, rv->preDelayLine[i]);
        }
    }
}

int AXFXReverbStdInit(struct AXFX_REVERBSTD * rev) {
    int ret;
    int old;

    old = OSDisableInterrupts();
    rev->tempDisableFX = 0;
    ret = ReverbSTDCreate(&rev->rv, rev->coloration, rev->time, rev->mix, rev->damping, rev->preDelay);
    OSRestoreInterrupts(old);
    return ret;
}

int AXFXReverbStdShutdown(struct AXFX_REVERBSTD * rev) {
    int old;

    old = OSDisableInterrupts();
    ReverbSTDFree(&rev->rv);
    OSRestoreInterrupts(old);
    return 1;
}

int AXFXReverbStdSettings(struct AXFX_REVERBSTD * rev) {
    int old;

    old = OSDisableInterrupts();
    rev->tempDisableFX = 1;
    ReverbSTDModify(&rev->rv, rev->coloration, rev->time, rev->mix, rev->damping, rev->preDelay);
    rev->tempDisableFX = 0;
    OSRestoreInterrupts(old);
    return 1;
}

void AXFXReverbStdCallback(struct AXFX_BUFFERUPDATE * bufferUpdate, struct AXFX_REVERBSTD * reverb) {
    if (reverb->tempDisableFX == 0) {
        ReverbSTDCallback(bufferUpdate->left, bufferUpdate->right, bufferUpdate->surround, &reverb->rv);
    }
}
