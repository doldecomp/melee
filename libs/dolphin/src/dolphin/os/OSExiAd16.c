#include <dolphin/exi.h>
#include <dolphin/os.h>

static int Initialized;

int AD16Init(void);
int AD16WriteReg(unsigned long word);
int AD16ReadReg(unsigned long *word);

int AD16Init(void) {
    int err;
    unsigned long cmd;
    unsigned long id;

    if (Initialized != 0) {
        return 1;
    }
    if (EXILock(2, 0, 0) == 0) {
        return 0;
    }
    if (EXISelect(2, 0, 0) == 0) {
        EXIUnlock(2);
        return 0;
    }
    cmd = 0;
    err = 0;
    err |= !EXIImm(2, &cmd, 2, 1, 0);
    err |= !EXISync(2);
    err |= !EXIImm(2, &id, 4, 0, 0);
    err |= !EXISync(2);
    err |= !EXIDeselect(2);
    EXIUnlock(2);
    if (err != 0 || id != 0x4120000) {
        return 0;
    }
    Initialized = 1;
    return 1;
}

int AD16WriteReg(unsigned long word) {
    int err;
    unsigned long cmd;

    if (Initialized == 0 || EXILock(2, 0, 0) == 0) {
        return 0;
    }
    if (EXISelect(2, 0, 3) == 0) {
        EXIUnlock(2);
        return 0;
    }
    cmd = 0xA0000000;
    err = 0;
    err |= !EXIImm(2, &cmd, 1, 1, 0);
    err |= !EXISync(2);
    err |= !EXIImm(2, &word, 4, 1, 0);
    err |= !EXISync(2);
    err |= !EXIDeselect(2);
    EXIUnlock(2);
    if (err) {
        return 0;
    }
    return 1;
}

int AD16ReadReg(unsigned long * word) {
    int err;
    unsigned long cmd;

    if (Initialized == 0 || EXILock(2, 0, 0) == 0) {
        return 0;
    }
    if (EXISelect(2, 0, 3) == 0) {
        EXIUnlock(2);
        return 0;
    }
    cmd = 0xA2000000;
    err = 0;
    err |= !EXIImm(2, &cmd, 1, 1, 0);
    err |= !EXISync(2);
    err |= !EXIImm(2, word, 4, 0, 0);
    err |= !EXISync(2);
    err |= !EXIDeselect(2);
    EXIUnlock(2);
    if (err) {
        return 0;
    }
    return 1;
}
