#include <dolphin/exi.h>
#include <dolphin/os.h>
#include <macros.h>

// internal include
#include "__os.h"

static struct SramControl Scb ATTRIBUTE_ALIGN(32);

static int GetRTC(unsigned long * rtc);
static int ReadSram(void * buffer);
static void WriteSramCallback();
static int WriteSram(void * buffer, unsigned long offset, unsigned long size);
static void * LockSram(unsigned long offset);
static int UnlockSram(int commit, unsigned long offset);
static void __OSReadROMCallback(long chan);

static int GetRTC(unsigned long * rtc) {
    int err;
    unsigned long cmd;

    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0x20000000;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImm(0, &cmd, 4, 0, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    rtc[0] = cmd;
    return !err;
}

int __OSGetRTC(unsigned long * rtc) {
    int err;
    unsigned long t0;
    unsigned long t1;
    int i;

    for(i = 0; i < 16; i++) {
        err = 0;
        err |= !GetRTC(&t0);
        err |= !GetRTC(&t1);
        if (err) {
            break;
        }
        if (t0 == t1) {
            rtc[0] = t0;
            return 1;
        }
    }
    return 0;
}

int __OSSetRTC(unsigned long rtc) {
    int err;
    unsigned long cmd;

    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0xA0000000;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImm(0, &rtc, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

static int ReadSram(void * buffer) {
    int err;
    unsigned long cmd;

    DCInvalidateRange(buffer, 0x40);
    if (!EXILock(0, 1, NULL) ) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0x20000100;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, 0x40, 0, NULL);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

static void WriteSramCallback() {
    int unused;
    ASSERTLINE(0xF0, !Scb.locked);
    Scb.sync = WriteSram(&Scb.sram[Scb.offset], Scb.offset, 0x40 - Scb.offset);
    if (Scb.sync != 0) {
        Scb.offset = 0x40;
    }
    ASSERTLINE(0xF6, Scb.sync);
}

static int WriteSram(void * buffer, unsigned long offset, unsigned long size) {
    int err;
    unsigned long cmd;

    if (!EXILock(0, 1, WriteSramCallback)) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }
    offset <<= 6;
    cmd = ((offset + 0x100) | 0xA0000000);
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImmEx(0, buffer, size, 1);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

void __OSInitSram() {
    Scb.locked = Scb.enabled = 0;
    Scb.sync = ReadSram(&Scb);
    ASSERTLINE(0x12C, Scb.sync);
    Scb.offset = 0x40;
}

static void * LockSram(unsigned long offset) {
    int enabled;

    enabled = OSDisableInterrupts();
    ASSERTLINE(0x140, !Scb.locked);
    if (Scb.locked) {
        OSRestoreInterrupts(enabled);
        return NULL;
    }
    Scb.enabled = enabled;
    Scb.locked = 1;
    return &Scb.sram[offset];
}

struct OSSram * __OSLockSram() {
    return (struct OSSram *)LockSram(0);
}

struct OSSramEx * __OSLockSramEx(void) {
    return (struct OSSramEx *)LockSram(0x14);
}

static int UnlockSram(int commit, unsigned long offset) {
    unsigned short * p;

    ASSERTLINE(0x162, Scb.locked);
    if (commit != 0) {
        if (offset == 0) {
            struct OSSram * sram  = (struct OSSram *)&Scb.sram[0];
            sram->checkSum = sram->checkSumInv = 0;
            for(p = (unsigned short*)&sram->counterBias; p < ((u16*)&Scb.sram[sizeof (struct OSSram)]); p++) {
                sram->checkSum += *p;
                sram->checkSumInv += ~(*p);
            }
        }
        if (offset < Scb.offset) {
            Scb.offset = offset;
        }
        Scb.sync = WriteSram(&Scb.sram[Scb.offset], Scb.offset, 0x40 - Scb.offset);
        if (Scb.sync != 0) {
            Scb.offset = 0x40;
        }
    }
    Scb.locked = 0;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

int __OSUnlockSram(int commit) {
    UnlockSram(commit, 0);
}

int __OSUnlockSramEx(int commit) {
    UnlockSram(commit, 0x14);
}

int __OSSyncSram() {
    return Scb.sync;
}

int __OSCheckSram() {
    unsigned short * p;
    unsigned short checkSum;
    unsigned short checkSumInv;
    struct OSSram * sram;
    int unused;

    ASSERTLINE(0x1A9, Scb.locked);

    checkSum = checkSumInv = 0;

    sram = (struct OSSram *)&Scb.sram[0];

    for (p = (void*)&sram->counterBias; p < (u16*)&Scb.sram[0x14]; p++) {
        checkSum += *p;
        checkSumInv += ~(*p);
    }

    return (sram->checkSum == checkSum && sram->checkSumInv == checkSumInv);
}

int __OSReadROM(void * buffer, long length, long offset) {
    int err;
    unsigned long cmd;

    ASSERTLINE(0x1C8, length <= 1024);
    DCInvalidateRange(buffer, length);
    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = offset << 6;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, length, 0, NULL);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

static void __OSReadROMCallback(long chan) {
    void (* callback)();

    EXIDeselect(chan);
    EXIUnlock(chan);
    callback = Scb.callback;
    if (callback) {
        Scb.callback = NULL;
        callback();
    }
}

int __OSReadROMAsync(void * buffer, long length, long offset, void (* callback)()) {
    int err;
    unsigned long cmd;

    ASSERTLINE(0x203, length <= 1024);
    ASSERTLINE(0x204, callback);
    DCInvalidateRange(buffer, length);
    Scb.callback = callback;
    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = offset << 6;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, length, 0, (void*)__OSReadROMCallback);
    return !err;
}

unsigned long OSGetSoundMode() {
    struct OSSram * sram = __OSLockSram();
    unsigned long mode = (sram->flags & 4) ? 1 : 0;

    __OSUnlockSram(0);
    return mode;
}

void OSSetSoundMode(unsigned long mode) {
    struct OSSram * sram;
    int unused;

    ASSERTLINE(0x22A, mode == OS_SOUND_MODE_MONO || mode == OS_SOUND_MODE_STEREO);
    mode *= 4;
    mode &= 4;
    sram = __OSLockSram();
    if (mode == (sram->flags & 4)) {
        __OSUnlockSram(0);
        return;
    }
    sram->flags &= 0xFFFFFFFB;
    sram->flags |= mode;
    __OSUnlockSram(1);
}

unsigned long OSGetVideoMode() {
    struct OSSram * sram = __OSLockSram();
    unsigned long mode = sram->flags & 3;

    __OSUnlockSram(0);
    return mode;
}

void OSSetVideoMode(unsigned long mode) {
    struct OSSram * sram;
    int unused;

    ASSERTLINE(0x249, OS_VIDEO_MODE_NTSC <= mode && mode <= OS_VIDEO_MODE_MPAL);

    mode &= 3;
    sram = __OSLockSram();
    if (mode == (sram->flags & 3)) {
        __OSUnlockSram(0);
        return;
    }
    sram->flags &= 0xFFFFFFFC;
    sram->flags |= mode;
    __OSUnlockSram(1);
}

unsigned char OSGetLanguage() {
    struct OSSram * sram = __OSLockSram();
    unsigned char language = sram->language;

    __OSUnlockSram(0);
    return language;
}

void OSSetLanguage(unsigned char language) {
    struct OSSram * sram = __OSLockSram();
    int unused;

    if (language == sram->language) {
        __OSUnlockSram(0);
        return;
    }
    sram->language = language;
    __OSUnlockSram(1);
}

unsigned char __OSGetBootMode() {
    struct OSSram * sram = __OSLockSram();
    unsigned char ntd = sram->ntd;
    __OSUnlockSram(0);
    return ntd & 0x80;
}

void __OSSetBootMode(unsigned char ntd) {
    struct OSSram * sram;
    int unused;

    ntd &= 0x80;
    sram = __OSLockSram();
    if (ntd == (sram->ntd & 0x80U)) {
        __OSUnlockSram(0);
        return;
    }
    sram->ntd &= 0xFFFFFF7F;
    sram->ntd |= ntd;
    __OSUnlockSram(1);
}
