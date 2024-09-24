#ifndef DOLPHIN_MCC_MCC_H
#define DOLPHIN_MCC_MCC_H

#include <placeholder.h>

/* 32C74C */ UNK_RET callbackEventStream(UNK_PARAMS);
/* 32C7D0 */ UNK_RET MCCStreamOpen(UNK_PARAMS);
/* 32C848 */ UNK_RET MCCStreamClose(UNK_PARAMS);
/* 32C880 */ UNK_RET MCCStreamWrite(UNK_PARAMS);
/* 32CA60 */ UNK_RET LoadChannelInfo(UNK_PARAMS);
/* 32CB7C */ UNK_RET FlushChannelInfo(UNK_PARAMS);
/* 32CC80 */ void SetChannelInfoDirty(bool dirty);
/* 32CC88 */ UNK_RET MakeMemoryMap(UNK_PARAMS);
/* 32CD40 */ UNK_RET SearchFreeBlocks(UNK_PARAMS);
/* 32CE40 */ UNK_RET NotifyCompulsorily(UNK_PARAMS);
/* 32CF48 */ UNK_RET WaitAMinute(UNK_PARAMS);
/* 32CFD8 */ UNK_RET MailboxCheck(UNK_PARAMS);
/* 32D260 */ UNK_RET MCCExiCallback(UNK_PARAMS);
/* 32D280 */ UNK_RET MCCTxCallback(UNK_PARAMS);
/* 32D29C */ UNK_RET MCCRxCallback(UNK_PARAMS);
/* 32D2B8 */ UNK_RET mccInitializeCheck(UNK_PARAMS);
/* 32D5E8 */ UNK_RET MCCInit(UNK_PARAMS);
/* 32D88C */ UNK_RET MCCExit(UNK_PARAMS);
/* 32D954 */ UNK_RET MCCEnumDevices(UNK_PARAMS);
/* 32D9AC */ UNK_RET MCCGetFreeBlocks(UNK_PARAMS);
/* 32DA3C */ u8 MCCGetLastError(void);
/* 32DA44 */ UNK_RET MCCGetChannelInfo(UNK_PARAMS);
/* 32DB14 */ UNK_RET MCCGetConnectionStatus(UNK_PARAMS);
/* 32DBD4 */ UNK_RET MCCNotify(UNK_PARAMS);
/* 32DCB0 */ UNK_RET MCCSetChannelEventMask(UNK_PARAMS);
/* 32DDC0 */ UNK_RET MCCOpen(UNK_PARAMS);
/* 32DFDC */ UNK_RET MCCClose(UNK_PARAMS);
/* 32E1B8 */ UNK_RET MCCRead(UNK_PARAMS);
/* 32E504 */ UNK_RET MCCWrite(UNK_PARAMS);
/* 32E868 */ UNK_RET MCCCheckAsyncDone(UNK_PARAMS);

#endif
