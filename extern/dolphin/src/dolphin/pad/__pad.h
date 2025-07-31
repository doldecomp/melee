typedef void (*PADCallback)(void);

static PADCallback PADSetSamplingCallback(PADCallback);
void SIRefreshSamplingRate(void);
int SIIsChanBusy(int);
