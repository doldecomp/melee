typedef void (*PADCallback)(void);

static void SamplingHandler(int, OSContext* arg1);
static PADCallback PADSetSamplingCallback(PADCallback);
void SIRefreshSamplingRate(void);
int SIIsChanBusy(int);

void SIRegisterPollingHandler(void (*)(int, OSContext*));
void SIUnregisterPollingHandler(void (*)(int, OSContext*));
