#include <dolphin/exi.h>
#include <dolphin/os.h>

static unsigned long serEnabled;

// None of the functions in this file were ever used or made public
int InitializeUART();
int ReadUARTN();
int WriteUARTN(void *buf, u32 len);

int InitializeUART() {
    if (!(OSGetConsoleType() & 0x10000000)) {
        serEnabled = 0;
        return 2;
    }
    serEnabled = 0xA5FF005A;
    return 0;
}

int ReadUARTN() {
    return 4;
}

static int QueueLength(void) {
    unsigned long cmd;

    if (EXISelect(0, 1, 3) == 0) {
        return -1;
    }
    cmd = 0x20010000;
    EXIImm(0, &cmd, 4, 1, 0);
    EXISync(0);
    EXIImm(0, &cmd, 1, 0, 0);
    EXISync(0);
    EXIDeselect(0);
    return 0x10 - (cmd >> 0x18);
}

int WriteUARTN(void *buf, u32 len) {
    unsigned long cmd;
    long xLen;
    int qLen;
    char* ptr;
    int locked;
    int error;

    if ((serEnabled + 0x5A010000) != 0x5A) {
        return 2;
    }

    locked = EXILock(0, 1, 0);
    if (locked == 0) {
        return 0;
    }
    else {
        ptr = (char*)buf;
    }

    while ((u32)ptr - (u32)buf < len) {
        if (*(s8*)ptr == 0xA) {
            *ptr = 0xD;
        }
        ptr++;
    }
    error = 0;
    cmd = 0xA0010000;

    while (len != 0) {
        qLen = QueueLength();
        if (qLen < 0) {
            error = -1;
            break;
        }
        
        if ((qLen >= 0xC) || (qLen >= len)) {
            if (EXISelect(0, 1, 3) == 0) {
                error = -1;
                break;
            }
            
            EXIImm(0, &cmd, 4, 1, 0);
            EXISync(0);

            while((qLen != 0) && (len != 0)) {
                if ((qLen < 4) && (qLen < len)) {
                    break;
                }

                xLen = len < 4 ? (long)len : 4;
                
                EXIImm(0, buf, xLen, 1, 0);
                (char*)buf += xLen;
                len -= xLen;
                qLen -= xLen;
                EXISync(0);
            }
            EXIDeselect(0);
        }
    }
    EXIUnlock(0);
    return error;
}
