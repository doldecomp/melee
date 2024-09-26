#ifndef DOLPHIN_MCC_FIO_H
#define DOLPHIN_MCC_FIO_H

#include <placeholder.h>

/* 32EA84 */ UNK_RET fioMccChannelEvent(UNK_PARAMS);
/* 32EB44 */ UNK_RET FIOInit(UNK_PARAMS);
/* 32EC00 */ UNK_RET FIOExit(UNK_PARAMS);
/* 32EC6C */ UNK_RET FIOQuery(UNK_PARAMS);
/* 32ED8C */ UNK_RET FIOFopen(UNK_PARAMS);
/* 32EE94 */ UNK_RET FIOFclose(UNK_PARAMS);
/* 32EF48 */ UNK_RET FIOFwrite(UNK_PARAMS);
/* 32F020 */ UNK_RET fioPacketMakeHeader(UNK_PARAMS);
/* 32F0E4 */ UNK_RET fioPacketSendPacket(UNK_PARAMS);
/* 32F228 */ UNK_RET fioPacketReceiveResult(UNK_PARAMS);
/* 32F390 */ UNK_RET fioPacketReceiveDone(UNK_PARAMS);
/* 32F39C */ UNK_RET fioPacketWrite(UNK_PARAMS);
/* 32F468 */ UNK_RET fioPacketResultWrite(UNK_PARAMS);

#endif
