#include <placeholder.h>

#include <cstring.h>
#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSTime.h>

#define EXI_FREQ_1M 0
#define REG(chan, idx) (__EXIRegs[(chan)][(idx)])
#define EXI_0CR(tstart, dma, rw, tlen)                                        \
    ((((u32) (tstart)) << 0) | (((u32) (dma)) << 1) | (((u32) (rw)) << 2) |   \
     (((u32) (tlen)) << 4))
#define CPR_CLK(x) ((x) << 4)
#define CPR_CS(x) ((1u << (x)) << 7)

extern s32 __EXIProbeStartTime[2] AT_ADDRESS(0x800030C0);

EXIControl Ecb[EXI_MAX_CHAN];

void SetExiInterruptMask(EXIChannel chan, volatile EXIControl* exi)
{
    volatile EXIControl* exi2 = &Ecb[EXI_CHAN_2];

    switch (chan) {
    case EXI_CHAN_0:
        if ((exi->exiCallback == NULL && exi2->exiCallback == NULL) ||
            exi->state & EXI_STATE_LOCKED)
        {
            __OSMaskInterrupts(OS_INTRMASK_EXI_0_EXI | OS_INTRMASK_EXI_2_EXI);
        } else {
            __OSUnmaskInterrupts(OS_INTRMASK_EXI_0_EXI |
                                 OS_INTRMASK_EXI_2_EXI);
        }
        break;
    case EXI_CHAN_1:
        if (exi->exiCallback == NULL || exi->state & EXI_STATE_LOCKED) {
            __OSMaskInterrupts(OS_INTRMASK_EXI_1_EXI);
        } else {
            __OSUnmaskInterrupts(OS_INTRMASK_EXI_1_EXI);
        }
        break;
    case EXI_CHAN_2:
        if (__OSGetInterruptHandler(OS_INTR_PI_DEBUG) == NULL ||
            exi->state & EXI_STATE_LOCKED)
        {
            __OSMaskInterrupts(OS_INTRMASK_PI_DEBUG);
        } else {
            __OSUnmaskInterrupts(OS_INTRMASK_PI_DEBUG);
        }
    }
}

static void CompleteTransfer(EXIChannel chan)
{
    EXIControl* exi = &Ecb[chan];
    u8* buf;
    u32 data;
    int i;
    int len;

    if (exi->state & EXI_STATE_BUSY) {
        if ((exi->state & EXI_STATE_IMM_ACCESS) && (len = exi->immLen)) {
            buf = exi->immBuf;
            data = REG(chan, 4);
            for (i = 0; i < len; i++) {
                *buf++ = (u8) ((data >> ((3 - i) * 8)) & 0xff);
            }
        }
        exi->state &= ~EXI_STATE_BUSY;
    }
}

bool EXIImm(EXIChannel chan, void* buf, s32 len, u32 type,
            EXICallback callback)
{
    EXIControl* exi = &Ecb[chan];
    bool enabled = OSDisableInterrupts();

    if ((exi->state & EXI_STATE_BUSY) || !(exi->state & EXI_STATE_SELECTED)) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->tcCallback = callback;
    if (exi->tcCallback) {
        EXIClearInterrupts(chan, false, true, false);
        __OSUnmaskInterrupts(OS_INTRMASK_EXI_0_TC >> (3 * chan));
    }

    exi->state |= EXI_STATE_IMM_ACCESS;

    if (type != EXI_READ) {
        u32 data;
        int i;

        data = 0;
        for (i = 0; i < len; i++) {
            data |= ((u8*) buf)[i] << ((3 - i) * 8);
        }
        REG(chan, 4) = data;
    }

    exi->immBuf = buf;
    exi->immLen = (type != EXI_WRITE) ? len : 0;

    REG(chan, 3) = EXI_0CR(1, 0, type, len - 1);

    OSRestoreInterrupts(enabled);

    return true;
}

bool EXIImmEx(EXIChannel chan, void* buf, s32 len, u32 mode)
{
    while (len) {
        s32 xLen = (len < 4) ? len : 4;

        if (!EXIImm(chan, buf, xLen, mode, NULL)) {
            return false;
        }

        if (!EXISync(chan)) {
            return false;
        }

        buf = (u8*) buf + xLen;

        len -= xLen;
    }

    return true;
}

bool EXIDma(EXIChannel chan, void* buf, s32 len, u32 type,
            EXICallback callback)
{
    EXIControl* exi = &Ecb[chan];
    bool enabled = OSDisableInterrupts();
    if ((exi->state & EXI_STATE_BUSY) || !(exi->state & EXI_STATE_SELECTED)) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->tcCallback = callback;
    if (exi->tcCallback) {
        EXIClearInterrupts(chan, false, true, false);
        __OSUnmaskInterrupts(OS_INTRMASK_EXI_0_TC >> (3 * chan));
    }

    exi->state |= EXI_STATE_DMA_ACCESS;

    REG(chan, 1) = (u32) buf & 0x3ffffe0;
    REG(chan, 2) = (u32) len;
    REG(chan, 3) = EXI_0CR(1, 1, type, 0);

    OSRestoreInterrupts(enabled);

    return true;
}

extern u32 __OSGetDIConfig(void);

#ifdef MWERKS_GEKKO

#pragma push
asm bool EXISync(EXIChannel)
{ // clang-format off
    nofralloc
/* 80345F4C 00342B2C  7C 08 02 A6 */	mflr r0
/* 80345F50 00342B30  3C A0 80 4A */	lis r5, Ecb@ha
/* 80345F54 00342B34  90 01 00 04 */	stw r0, 4(r1)
/* 80345F58 00342B38  3C 80 CC 00 */	lis r4, 0xCC006800@ha
/* 80345F5C 00342B3C  38 05 7C 80 */	addi r0, r5, Ecb@l
/* 80345F60 00342B40  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80345F64 00342B44  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 80345F68 00342B48  1F C3 00 14 */	mulli r30, r3, 0x14
/* 80345F6C 00342B4C  3B A4 68 00 */	addi r29, r4, 0xCC006800@l
/* 80345F70 00342B50  54 63 30 32 */	slwi r3, r3, 6
/* 80345F74 00342B54  7F E0 1A 14 */	add r31, r0, r3
/* 80345F78 00342B58  7F BD F2 14 */	add r29, r29, r30
/* 80345F7C 00342B5C  3B 80 00 00 */	li r28, 0
/* 80345F80 00342B60  48 00 01 B0 */	b lbl_80346130
lbl_80345F84:
/* 80345F84 00342B64  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80345F88 00342B68  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80345F8C 00342B6C  40 82 01 A4 */	bne lbl_80346130
/* 80345F90 00342B70  48 00 13 D5 */	bl OSDisableInterrupts
/* 80345F94 00342B74  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345F98 00342B78  3B 63 00 00 */	addi r27, r3, 0
/* 80345F9C 00342B7C  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 80345FA0 00342B80  41 82 01 84 */	beq lbl_80346124
/* 80345FA4 00342B84  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345FA8 00342B88  54 00 07 BF */	clrlwi. r0, r0, 0x1e
/* 80345FAC 00342B8C  41 82 01 34 */	beq lbl_803460E0
/* 80345FB0 00342B90  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345FB4 00342B94  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 80345FB8 00342B98  41 82 01 1C */	beq lbl_803460D4
/* 80345FBC 00342B9C  80 9F 00 10 */	lwz r4, 0x10(r31)
/* 80345FC0 00342BA0  2C 04 00 00 */	cmpwi r4, 0
/* 80345FC4 00342BA4  41 82 01 10 */	beq lbl_803460D4
/* 80345FC8 00342BA8  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 80345FCC 00342BAC  80 FF 00 14 */	lwz r7, 0x14(r31)
/* 80345FD0 00342BB0  38 03 68 00 */	addi r0, r3, 0xCC006800@l
/* 80345FD4 00342BB4  7C 60 F2 14 */	add r3, r0, r30
/* 80345FD8 00342BB8  80 C3 00 10 */	lwz r6, 0x10(r3)
/* 80345FDC 00342BBC  38 A0 00 00 */	li r5, 0
/* 80345FE0 00342BC0  40 81 00 F4 */	ble lbl_803460D4
/* 80345FE4 00342BC4  2C 04 00 08 */	cmpwi r4, 8
/* 80345FE8 00342BC8  38 64 FF F8 */	addi r3, r4, -8
/* 80345FEC 00342BCC  40 81 00 BC */	ble lbl_803460A8
/* 80345FF0 00342BD0  38 03 00 07 */	addi r0, r3, 7
/* 80345FF4 00342BD4  54 00 E8 FE */	srwi r0, r0, 3
/* 80345FF8 00342BD8  2C 03 00 00 */	cmpwi r3, 0
/* 80345FFC 00342BDC  7C 09 03 A6 */	mtctr r0
/* 80346000 00342BE0  40 81 00 A8 */	ble lbl_803460A8
lbl_80346004:
/* 80346004 00342BE4  20 05 00 03 */	subfic r0, r5, 3
/* 80346008 00342BE8  54 03 18 38 */	slwi r3, r0, 3
/* 8034600C 00342BEC  38 05 00 01 */	addi r0, r5, 1
/* 80346010 00342BF0  7C C8 1C 30 */	srw r8, r6, r3
/* 80346014 00342BF4  20 00 00 03 */	subfic r0, r0, 3
/* 80346018 00342BF8  99 07 00 00 */	stb r8, 0(r7)
/* 8034601C 00342BFC  54 03 18 38 */	slwi r3, r0, 3
/* 80346020 00342C00  38 05 00 02 */	addi r0, r5, 2
/* 80346024 00342C04  7C C3 1C 30 */	srw r3, r6, r3
/* 80346028 00342C08  20 00 00 03 */	subfic r0, r0, 3
/* 8034602C 00342C0C  98 67 00 01 */	stb r3, 1(r7)
/* 80346030 00342C10  54 00 18 38 */	slwi r0, r0, 3
/* 80346034 00342C14  7C C0 04 30 */	srw r0, r6, r0
/* 80346038 00342C18  7D 05 00 D0 */	neg r8, r5
/* 8034603C 00342C1C  98 07 00 02 */	stb r0, 2(r7)
/* 80346040 00342C20  55 09 18 38 */	slwi r9, r8, 3
/* 80346044 00342C24  39 05 00 04 */	addi r8, r5, 4
/* 80346048 00342C28  7C CC 4C 30 */	srw r12, r6, r9
/* 8034604C 00342C2C  21 08 00 03 */	subfic r8, r8, 3
/* 80346050 00342C30  99 87 00 03 */	stb r12, 3(r7)
/* 80346054 00342C34  55 09 18 38 */	slwi r9, r8, 3
/* 80346058 00342C38  39 05 00 05 */	addi r8, r5, 5
/* 8034605C 00342C3C  7C CB 4C 30 */	srw r11, r6, r9
/* 80346060 00342C40  21 08 00 03 */	subfic r8, r8, 3
/* 80346064 00342C44  99 67 00 04 */	stb r11, 4(r7)
/* 80346068 00342C48  55 09 18 38 */	slwi r9, r8, 3
/* 8034606C 00342C4C  7C CA 4C 30 */	srw r10, r6, r9
/* 80346070 00342C50  39 05 00 06 */	addi r8, r5, 6
/* 80346074 00342C54  99 47 00 05 */	stb r10, 5(r7)
/* 80346078 00342C58  21 28 00 03 */	subfic r9, r8, 3
/* 8034607C 00342C5C  39 05 00 07 */	addi r8, r5, 7
/* 80346080 00342C60  55 29 18 38 */	slwi r9, r9, 3
/* 80346084 00342C64  7C C9 4C 30 */	srw r9, r6, r9
/* 80346088 00342C68  21 08 00 03 */	subfic r8, r8, 3
/* 8034608C 00342C6C  99 27 00 06 */	stb r9, 6(r7)
/* 80346090 00342C70  55 08 18 38 */	slwi r8, r8, 3
/* 80346094 00342C74  7C C8 44 30 */	srw r8, r6, r8
/* 80346098 00342C78  99 07 00 07 */	stb r8, 7(r7)
/* 8034609C 00342C7C  38 E7 00 08 */	addi r7, r7, 8
/* 803460A0 00342C80  38 A5 00 08 */	addi r5, r5, 8
/* 803460A4 00342C84  42 00 FF 60 */	bdnz lbl_80346004
lbl_803460A8:
/* 803460A8 00342C88  7C 05 20 50 */	subf r0, r5, r4
/* 803460AC 00342C8C  7C 05 20 00 */	cmpw r5, r4
/* 803460B0 00342C90  7C 09 03 A6 */	mtctr r0
/* 803460B4 00342C94  40 80 00 20 */	bge lbl_803460D4
lbl_803460B8:
/* 803460B8 00342C98  20 05 00 03 */	subfic r0, r5, 3
/* 803460BC 00342C9C  54 00 18 38 */	slwi r0, r0, 3
/* 803460C0 00342CA0  7C C0 04 30 */	srw r0, r6, r0
/* 803460C4 00342CA4  98 07 00 00 */	stb r0, 0(r7)
/* 803460C8 00342CA8  38 E7 00 01 */	addi r7, r7, 1
/* 803460CC 00342CAC  38 A5 00 01 */	addi r5, r5, 1
/* 803460D0 00342CB0  42 00 FF E8 */	bdnz lbl_803460B8
lbl_803460D4:
/* 803460D4 00342CB4  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 803460D8 00342CB8  54 00 00 3A */	rlwinm r0, r0, 0, 0, 0x1d
/* 803460DC 00342CBC  90 1F 00 0C */	stw r0, 0xc(r31)
lbl_803460E0:
/* 803460E0 00342CC0  4B FF D6 2D */	bl __OSGetDIConfig
/* 803460E4 00342CC4  28 03 00 FF */	cmplwi r3, 0xff
/* 803460E8 00342CC8  40 82 00 38 */	bne lbl_80346120
/* 803460EC 00342CCC  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 803460F0 00342CD0  2C 00 00 04 */	cmpwi r0, 4
/* 803460F4 00342CD4  40 82 00 2C */	bne lbl_80346120
/* 803460F8 00342CD8  80 1D 00 00 */	lwz r0, 0(r29)
/* 803460FC 00342CDC  54 00 06 77 */	rlwinm. r0, r0, 0, 0x19, 0x1b
/* 80346100 00342CE0  40 82 00 20 */	bne lbl_80346120
/* 80346104 00342CE4  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 80346108 00342CE8  38 03 68 00 */	addi r0, r3, 0xCC006800@l
/* 8034610C 00342CEC  7C 60 F2 14 */	add r3, r0, r30
/* 80346110 00342CF0  80 63 00 10 */	lwz r3, 0x10(r3)
/* 80346114 00342CF4  3C 03 FE FF */	addis r0, r3, 0xfeff
/* 80346118 00342CF8  28 00 00 00 */	cmplwi r0, 0
/* 8034611C 00342CFC  41 82 00 08 */	beq lbl_80346124
lbl_80346120:
/* 80346120 00342D00  3B 80 00 01 */	li r28, 1
lbl_80346124:
/* 80346124 00342D04  7F 63 DB 78 */	mr r3, r27
/* 80346128 00342D08  48 00 12 65 */	bl OSRestoreInterrupts
/* 8034612C 00342D0C  48 00 00 10 */	b lbl_8034613C
lbl_80346130:
/* 80346130 00342D10  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346134 00342D14  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 80346138 00342D18  40 82 FE 4C */	bne lbl_80345F84
lbl_8034613C:
/* 8034613C 00342D1C  7F 83 E3 78 */	mr r3, r28
/* 80346140 00342D20  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 80346144 00342D24  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80346148 00342D28  38 21 00 30 */	addi r1, r1, 0x30
/* 8034614C 00342D2C  7C 08 03 A6 */	mtlr r0
/* 80346150 00342D30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

bool EXISync(EXIChannel _)
{
    NOT_IMPLEMENTED;
    return false;
}

#endif

u32 EXIClearInterrupts(EXIChannel chan, bool exi, bool tc, bool ext)
{
    u32 cpr = REG(chan, 0);
    u32 prev = cpr;
    cpr &= 0x7F5;
    if (exi) {
        cpr |= 2;
    }
    if (tc) {
        cpr |= 8;
    }
    if (ext) {
        cpr |= 0x800;
    }
    REG(chan, 0) = cpr;
    return prev;
}

EXICallback EXISetExiCallback(EXIChannel chan, EXICallback exiCallback)
{
    EXIControl* exi = &Ecb[chan];
    EXICallback prev;
    bool enabled = OSDisableInterrupts();

    prev = exi->exiCallback;
    exi->exiCallback = exiCallback;

    if (chan != 2) {
        SetExiInterruptMask(chan, exi);
    } else {
        SetExiInterruptMask(0, &Ecb[0]);
    }

    OSRestoreInterrupts(enabled);
    return prev;
}

static bool __EXIProbe(EXIChannel chan)
{
    EXIControl* exi = &Ecb[chan];
    bool enabled;
    bool rc;
    u32 cpr;
    s32 t;

    if (chan == 2) {
        return true;
    }

    rc = true;
    enabled = OSDisableInterrupts();
    cpr = REG(chan, 0);
    if (!(exi->state & EXI_STATE_ATTACHED)) {
        if (cpr & 0x800) {
            EXIClearInterrupts(chan, false, false, true);
            __EXIProbeStartTime[chan] = exi->idTime = 0;
        }

        if (cpr & 0x1000) {
            t = (s32) (OSTicksToMilliseconds(OSGetTime()) / 100) + 1;
            if (__EXIProbeStartTime[chan] == 0) {
                __EXIProbeStartTime[chan] = t;
            }
            if (t - __EXIProbeStartTime[chan] < 300 / 100) {
                rc = false;
            }
        } else {
            __EXIProbeStartTime[chan] = exi->idTime = 0;
            rc = false;
        }
    } else if (!(cpr & 0x1000) || (cpr & 0x800)) {
        __EXIProbeStartTime[chan] = exi->idTime = 0;
        rc = false;
    }
    OSRestoreInterrupts(enabled);

    return rc;
}

bool EXIProbe(EXIChannel chan)
{
    EXIControl* exi = &Ecb[chan];
    bool rc;
    u32 id;

    rc = __EXIProbe(chan);
    if (rc && exi->idTime == 0) {
        rc = EXIGetID(chan, 0, &id) ? true : false;
    }
    return rc;
}

s32 EXIProbeEx(EXIChannel chan)
{
    if (EXIProbe(chan)) {
        return 1;
    } else if (__EXIProbeStartTime[chan] != 0) {
        return 0;
    } else {
        return -1;
    }
}

static bool __EXIAttach(EXIChannel chan, EXICallback extCallback)
{
    EXIControl* exi = &Ecb[chan];
    bool enabled = OSDisableInterrupts();
    if ((exi->state & EXI_STATE_ATTACHED) || __EXIProbe(chan) == false) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    EXIClearInterrupts(chan, true, false, false);

    exi->extCallback = extCallback;
    __OSUnmaskInterrupts(OS_INTRMASK_EXI_0_EXT >> (3 * chan));
    exi->state |= EXI_STATE_ATTACHED;
    OSRestoreInterrupts(enabled);

    return true;
}

bool EXIAttach(EXIChannel chan, EXICallback extCallback)
{
    EXIControl* exi = &Ecb[chan];
    bool enabled;

    EXIProbe(chan);

    enabled = OSDisableInterrupts();
    if (exi->idTime == 0) {
        OSRestoreInterrupts(enabled);
        return false;
    } else {
        bool rc = __EXIAttach(chan, extCallback);
        OSRestoreInterrupts(enabled);
        return rc;
    }
}

bool EXIDetach(EXIChannel chan)
{
    EXIControl* exi = &Ecb[chan];
    bool enabled = OSDisableInterrupts();

    if (!(exi->state & EXI_STATE_ATTACHED)) {
        OSRestoreInterrupts(enabled);
        return true;
    }
    if ((exi->state & EXI_STATE_LOCKED) && exi->dev == 0) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->state &= ~EXI_STATE_ATTACHED;
    __OSMaskInterrupts((OS_INTRMASK_EXI_0_EXT | OS_INTRMASK_EXI_0_TC |
                        OS_INTRMASK_EXI_0_EXI) >>
                       (3 * chan));
    OSRestoreInterrupts(enabled);
    return true;
}

bool EXISelect(s32 chan, u32 dev, u32 freq)
{
    EXIControl* exi = &Ecb[chan];
    u32 cpr;
    bool enabled = OSDisableInterrupts();

    if ((exi->state & EXI_STATE_SELECTED) ||
        (chan != 2 && ((dev == 0 && !(exi->state & EXI_STATE_ATTACHED) &&
                        !__EXIProbe(chan)) ||
                       !(exi->state & EXI_STATE_LOCKED) || exi->dev != dev)))
    {
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->state |= EXI_STATE_SELECTED;
    cpr = REG(chan, 0);
    cpr &= 0x405;
    cpr |= CPR_CS(dev) | CPR_CLK(freq);
    REG(chan, 0) = cpr;

    if (exi->state & EXI_STATE_ATTACHED) {
        switch (chan) {
        case 0:
            __OSMaskInterrupts(OS_INTRMASK_EXI_0_EXT);
            break;
        case 1:
            __OSMaskInterrupts(OS_INTRMASK_EXI_1_EXT);
            break;
        }
    }

    OSRestoreInterrupts(enabled);
    return true;
}

bool EXIDeselect(EXIChannel chan)
{
    EXIControl* exi = &Ecb[chan];
    u32 cpr;
    bool enabled = OSDisableInterrupts();

    if (!(exi->state & EXI_STATE_SELECTED)) {
        OSRestoreInterrupts(enabled);
        return false;
    }
    exi->state &= ~EXI_STATE_SELECTED;
    cpr = REG(chan, 0);
    REG(chan, 0) = cpr & 0x405;

    if (exi->state & EXI_STATE_ATTACHED) {
        switch (chan) {
        case 0:
            __OSUnmaskInterrupts(OS_INTRMASK_EXI_0_EXT);
            break;
        case 1:
            __OSUnmaskInterrupts(OS_INTRMASK_EXI_1_EXT);
            break;
        }
    }

    OSRestoreInterrupts(enabled);

    if (chan != 2 && (cpr & CPR_CS(0))) {
        return __EXIProbe(chan) ? true : false;
    }

    return true;
}

static void EXIIntrruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    EXIChannel chan;
    EXIControl* exi;
    EXICallback callback;

    chan = (interrupt - OS_INTR_EXI_0_EXI) / 3;
    exi = &Ecb[chan];
    EXIClearInterrupts(chan, true, false, false);
    callback = exi->exiCallback;

    if (exi->exiCallback) {
        OSContext exceptionContext;

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        callback(chan, context);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

static void TCIntrruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    OSContext exceptionContext;
    EXIChannel chan;
    EXIControl* exi;
    EXICallback callback;

    chan = (interrupt - OS_INTR_EXI_0_TC) / 3;
    exi = &Ecb[chan];
    __OSMaskInterrupts(0x80000000U >> interrupt);
    EXIClearInterrupts(chan, false, true, false);
    callback = exi->tcCallback;
    if (callback) {
        exi->tcCallback = 0;
        CompleteTransfer(chan);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        callback(chan, context);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

#ifdef MWERKS_GEKKO

#pragma push
static asm void EXTIntrruptHandler(__OSInterrupt, OSContext*)
{ // clang-format off
    nofralloc
/* 80346BA4 00343784  7C 08 02 A6 */	mflr r0
/* 80346BA8 00343788  7C 65 07 34 */	extsh r5, r3
/* 80346BAC 0034378C  90 01 00 04 */	stw r0, 4(r1)
/* 80346BB0 00343790  3C 60 55 55 */	lis r3, 0x55555556@ha
/* 80346BB4 00343794  38 05 FF F5 */	addi r0, r5, -11
/* 80346BB8 00343798  38 63 55 56 */	addi r3, r3, 0x55555556@l
/* 80346BBC 0034379C  94 21 FD 10 */	stwu r1, -0x2f0(r1)
/* 80346BC0 003437A0  7C 63 00 96 */	mulhw r3, r3, r0
/* 80346BC4 003437A4  BF 61 02 DC */	stmw r27, 0x2dc(r1)
/* 80346BC8 003437A8  54 60 0F FE */	srwi r0, r3, 0x1f
/* 80346BCC 003437AC  7F C3 02 14 */	add r30, r3, r0
/* 80346BD0 003437B0  1C 1E 00 03 */	mulli r0, r30, 3
/* 80346BD4 003437B4  3C 60 00 70 */	lis r3, 0x70
/* 80346BD8 003437B8  3B 64 00 00 */	addi r27, r4, 0
/* 80346BDC 003437BC  7C 63 04 30 */	srw r3, r3, r0
/* 80346BE0 003437C0  48 00 0B 4D */	bl __OSMaskInterrupts
/* 80346BE4 003437C4  1C 1E 00 14 */	mulli r0, r30, 0x14
/* 80346BE8 003437C8  3C 80 CC 00 */	lis r4, 0xCC006800@ha
/* 80346BEC 003437CC  3C 60 80 4A */	lis r3, Ecb@ha
/* 80346BF0 003437D0  38 84 68 00 */	addi r4, r4, 0xCC006800@l
/* 80346BF4 003437D4  3B E0 00 00 */	li r31, 0
/* 80346BF8 003437D8  7F E4 01 2E */	stwx r31, r4, r0
/* 80346BFC 003437DC  57 C4 30 32 */	slwi r4, r30, 6
/* 80346C00 003437E0  38 03 7C 80 */	addi r0, r3, Ecb@l
/* 80346C04 003437E4  7F A0 22 14 */	add r29, r0, r4
/* 80346C08 003437E8  83 9D 00 08 */	lwz r28, 8(r29)
/* 80346C0C 003437EC  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80346C10 003437F0  28 1C 00 00 */	cmplwi r28, 0
/* 80346C14 003437F4  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 80346C18 003437F8  90 1D 00 0C */	stw r0, 0xc(r29)
/* 80346C1C 003437FC  41 82 00 3C */	beq lbl_80346C58
/* 80346C20 00343800  38 61 00 10 */	addi r3, r1, 0x10
/* 80346C24 00343804  4B FF E6 31 */	bl OSClearContext
/* 80346C28 00343808  38 61 00 10 */	addi r3, r1, 0x10
/* 80346C2C 0034380C  4B FF E4 61 */	bl OSSetCurrentContext
/* 80346C30 00343810  7F 8C E3 78 */	mr r12, r28
/* 80346C34 00343814  93 FD 00 08 */	stw r31, 8(r29)
/* 80346C38 00343818  7D 88 03 A6 */	mtlr r12
/* 80346C3C 0034381C  38 7E 00 00 */	addi r3, r30, 0
/* 80346C40 00343820  38 9B 00 00 */	addi r4, r27, 0
/* 80346C44 00343824  4E 80 00 21 */	blrl
/* 80346C48 00343828  38 61 00 10 */	addi r3, r1, 0x10
/* 80346C4C 0034382C  4B FF E6 09 */	bl OSClearContext
/* 80346C50 00343830  7F 63 DB 78 */	mr r3, r27
/* 80346C54 00343834  4B FF E4 39 */	bl OSSetCurrentContext
lbl_80346C58:
/* 80346C58 00343838  BB 61 02 DC */	lmw r27, 0x2dc(r1)
/* 80346C5C 0034383C  80 01 02 F4 */	lwz r0, 0x2f4(r1)
/* 80346C60 00343840  38 21 02 F0 */	addi r1, r1, 0x2f0
/* 80346C64 00343844  7C 08 03 A6 */	mtlr r0
/* 80346C68 00343848  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

static void EXTIntrruptHandler(__OSInterrupt unused0, OSContext* unused1)
{
    NOT_IMPLEMENTED;
}

#endif

void EXIInit(void)
{
    __OSMaskInterrupts(OS_INTRMASK_EXI_0_EXI | OS_INTRMASK_EXI_0_TC |
                       OS_INTRMASK_EXI_0_EXT | OS_INTRMASK_EXI_1_EXI |
                       OS_INTRMASK_EXI_1_TC | OS_INTRMASK_EXI_1_EXT |
                       OS_INTRMASK_EXI_2_EXI | OS_INTRMASK_EXI_2_TC);

    REG(0, 0) = 0;
    REG(1, 0) = 0;
    REG(2, 0) = 0;

    REG(0, 0) = 0x00002000;

    __OSSetInterruptHandler(OS_INTR_EXI_0_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(OS_INTR_EXI_0_TC, TCIntrruptHandler);
    __OSSetInterruptHandler(OS_INTR_EXI_0_EXT, EXTIntrruptHandler);
    __OSSetInterruptHandler(OS_INTR_EXI_1_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(OS_INTR_EXI_1_TC, TCIntrruptHandler);
    __OSSetInterruptHandler(OS_INTR_EXI_1_EXT, EXTIntrruptHandler);
    __OSSetInterruptHandler(OS_INTR_EXI_2_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(OS_INTR_EXI_2_TC, TCIntrruptHandler);

    if (OSGetConsoleType() & 0x10000000) {
        __EXIProbeStartTime[0] = __EXIProbeStartTime[1] = 0;
        Ecb[0].idTime = Ecb[1].idTime = 0;
        __EXIProbe(0);
        __EXIProbe(1);
    }
}

bool EXILock(s32 chan, u32 dev, EXICallback unlockedCallback)
{
    EXIControl* exi = &Ecb[chan];
    bool enabled = OSDisableInterrupts();
    if (exi->state & EXI_STATE_LOCKED) {
        if (unlockedCallback) {
            int i;
            for (i = 0; i < exi->items; i++) {
                if (exi->queue[i].dev == dev) {
                    OSRestoreInterrupts(enabled);
                    return false;
                }
            }
            exi->queue[exi->items].callback = unlockedCallback;
            exi->queue[exi->items].dev = dev;
            exi->items++;
        }
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->state |= EXI_STATE_LOCKED;
    exi->dev = dev;
    SetExiInterruptMask(chan, exi);

    OSRestoreInterrupts(enabled);
    return true;
}

bool EXIUnlock(EXIChannel chan)
{
    EXIControl* exi = &Ecb[chan];
    bool enabled;
    EXICallback unlockedCallback;

    enabled = OSDisableInterrupts();
    if (!(exi->state & EXI_STATE_LOCKED)) {
        OSRestoreInterrupts(enabled);
        return false;
    }
    exi->state &= ~EXI_STATE_LOCKED;
    SetExiInterruptMask(chan, exi);

    if (0 < exi->items) {
        unlockedCallback = exi->queue[0].callback;
        if (0 < --exi->items) {
            memmove(&exi->queue[0], &exi->queue[1],
                    sizeof(exi->queue[0]) * exi->items);
        }
        unlockedCallback(chan, 0);
    }

    OSRestoreInterrupts(enabled);
    return true;
}

u32 EXIGetState(EXIChannel chan)
{
    EXIControl* exi = &Ecb[chan];
    return exi->state;
}

static void UnlockedHandler(s32 chan, OSContext* context)
{
    u32 id;
    EXIGetID(chan, 0, &id);
}

s32 EXIGetID(EXIChannel chan, u32 dev, u32* id)
{
    EXIControl* exi = &Ecb[chan];
    bool err;
    u32 cmd;
    s32 startTime;

    if (chan < 2 && dev == 0) {
        if (!__EXIProbe(chan)) {
            return 0;
        }

        if (exi->idTime == __EXIProbeStartTime[chan]) {
            *id = exi->id;
            return exi->idTime;
        }

        if (!__EXIAttach(chan, NULL)) {
            return 0;
        }

        startTime = __EXIProbeStartTime[chan];
    }

    err = !EXILock(chan, dev, (chan < 2 && dev == 0) ? UnlockedHandler : NULL);
    if (!err) {
        err = !EXISelect(chan, dev, EXI_FREQ_1M);
        if (!err) {
            cmd = 0;
            err |= !EXIImm(chan, &cmd, 2, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, id, 4, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }

    if (chan < 2 && dev == 0) {
        bool enabled;
        EXIDetach(chan);
        enabled = OSDisableInterrupts();
        err |= (startTime != __EXIProbeStartTime[chan]);
        if (!err) {
            exi->id = *id;
            exi->idTime = startTime;
        }
        OSRestoreInterrupts(enabled);

        return err ? 0 : exi->idTime;
    }

    return err ? 0 : !0;
}
