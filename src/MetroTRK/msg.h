#ifndef _METROTRK_MSG_H
#define _METROTRK_MSG_H

#include <platform.h>

#include "MetroTRK/dserror.h"
#include "MetroTRK/msgbuf.h"

typedef struct TRKPacketSeq {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u8 unk02[6];
} TRKPacketSeq; // size = 0x08

DSError TRKMessageSend(MessageBuffer* buf);

#endif