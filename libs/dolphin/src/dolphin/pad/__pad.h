#ifndef _DOLPHIN_PAD_INTERNAL_H_
#define _DOLPHIN_PAD_INTERNAL_H_

typedef void (*PADCallback)(void);

static PADCallback PADSetSamplingCallback(PADCallback);
void SIRefreshSamplingRate(void);
int SIIsChanBusy(int);

#endif
