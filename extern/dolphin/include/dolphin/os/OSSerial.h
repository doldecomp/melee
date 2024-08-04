#ifndef _DOLPHIN_OSSERIAL_H
#define _DOLPHIN_OSSERIAL_H

#include <dolphin/hw_regs.h>

#define CHAN_NONE -1

#define SI_MAX_CHAN 4

#define SI_COMCSR_IDX 13
#define SI_STATUS_IDX 14

#define SI_COMCSR_TCINT_MASK       (1 << 31)
#define SI_COMCSR_TCINTMSK_MASK    (1 << 30)
#define SI_COMCSR_COMERR_MASK      (1 << 29)
#define SI_COMCSR_RDSTINT_MASK     (1 << 28)
#define SI_COMCSR_RDSTINTMSK_MASK  (1 << 27)
// 4 bits of padding
#define SI_COMCSR_OUTLNGTH_MASK    (1 << 22) \
                                 | (1 << 21) \
                                 | (1 << 20) \
                                 | (1 << 19) \
                                 | (1 << 18) \
                                 | (1 << 17) \
                                 | (1 << 16)
// 1 bit of padding
#define SI_COMCSR_INLNGTH_MASK     (1 << 14) \
                                 | (1 << 13) \
                                 | (1 << 12) \
                                 | (1 << 11) \
                                 | (1 << 10) \
                                 | (1 << 9)  \
                                 | (1 << 8)
// 5 bits of padding
#define SI_COMCSR_CHANNEL_MASK     (1 << 2) \
                                 | (1 << 1)
#define SI_COMCSR_TSTART_MASK      (1 << 0)

#define ROUND(n, a) (((u32)(n) + (a)-1) & ~((a)-1))

struct SIControl {
    long chan;
    unsigned long poll;
    unsigned long inputBytes;
    void * input;
    void (* callback)(long, unsigned long, struct OSContext *);
};

struct SIPacket {
    long chan;
    void * output;
    unsigned long outputBytes;
    void * input;
    unsigned long inputBytes;
    void (* callback)(long, unsigned long, struct OSContext *);
    long long time;
};

int SIBusy();
void SIInit();
unsigned long SISync();
unsigned long SIGetStatus();
void SISetCommand(long chan, unsigned long command);
unsigned long SIGetCommand(long chan);
void SITransferCommands();
unsigned long SISetXY(unsigned long x, unsigned long y);
unsigned long SIEnablePolling(unsigned long poll);
unsigned long SIDisablePolling(unsigned long poll);
void SIGetResponse(long chan, void * data);
int SITransfer(long chan, void * output, unsigned long outputBytes, void * input, unsigned long inputBytes, 
                void (* callback)(long, unsigned long, struct OSContext *), long long time);

#endif // _DOLPHIN_OSSERIAL_H
