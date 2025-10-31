#ifndef SYSDOLPHIN_SYNTH_H
#define SYSDOLPHIN_SYNTH_H

#include <placeholder.h>

#include <dolphin/ax.h>

struct HSD_SynthSFXNode;

/* 388330 */ void* HSD_AudioMalloc(size_t);
/* 38838C */ void HSD_AudioFree(void*);
/* 3883B4 */ void HSD_SynthSFXSampleLoadCallback(int, int, void*,
                                                 int cancelflag);
/* 38893C */ void HSD_SynthSFXLoadNewProc(void);
/* 3889B8 */ int HSD_SynthSFXLoad(const char* filename, int, int, int);
/* 388B0C */ void HSD_SynthSFXWaitForLoadCompletion(void (*)(void));
/* 388B50 */ int HSD_SynthSFXGetPendingLoadCount(void);
/* 388B60 */ int HSD_SynthSFXCancelLoad(int);
/* 388CB0 */ void HSD_SynthSFXAllocateBank(int);
/* 388D30 */ void HSD_SynthSFXUnloadBank(int);
/* 388DC8 */ void HSD_Synth_80388DC8(u8*);
/* 388E08 */ void HSD_Synth_80388E08(int);
/* 388EFC */ void HSD_SynthSFXGroupDataReaddress(AXVPB*, void* callback);
/* 388FF0 */ void HSD_SynthSFXBankDeflag(int);
/* 389084 */ void HSD_SynthSFXBankDeflagSync(void);
/* 389094 */ u32 HSD_SynthGetSoundMode(void);
/* 3890B4 */ void HSD_SynthSetSoundMode(int); // set sound mode
/* 38912C */ void HSD_SynthSFXStopNode(struct HSD_SynthSFXNode*);
/* 3891D0 */ void dropcallback(void*);
/* 389334 */ // s32 HSD_Synth_80389334(u16, u8, u8, u8, u8, u8, f32, f32, f32,
             //                       f32, f32);
/* 3896F0 */ bool HSD_SynthSFXPlayWithGroup(int, u8, u8, u8, int, u8, int, f32,
                                            f32, f32, f32, f32);
void HSD_SynthSFXKeyOff(int);
/* 3899B0 */ void HSD_SynthSFXStopRange(int);
/* 389A50 */ void HSD_SynthSFXPause(int);
/* 389AD0 */ void HSD_SynthSFXResume(int);
/* 389B50 */ int HSD_SynthSFXCheck(int);
/* 389BD8 */ void HSD_SynthSFXSetVolumeFade(int, u8, int);
/* 389CC4 */ void HSD_SynthSFXSetUserVol(int, u8);
/* 389D24 */ void HSD_SynthSFXSetMix(int, float, float, float);
/* 389D8C */ void HSD_SynthSFXUpdatePitch(struct HSD_SynthSFXNode*);
/* 389E2C */ void HSD_SynthSFXSetPitchRatio(int, int, float);
/* 389F4C */ void HSD_SynthSFXSetPriority(int id, int prio);
/* 38A000 */ UNK_RET HSD_Synth_8038A000(UNK_PARAMS);
/* 38A5A4 */ void HSD_SynthSFXUpdateVolume(struct HSD_SynthSFXNode*);
/* 38A600 */ void HSD_SynthSFXUpdateMix(struct HSD_SynthSFXNode*, int);
/* 38AAB0 */ void HSD_SynthSFXUpdateAllVolume(int, u16, int);
/* 38ABBC */ void HSD_SynthSFXSetDriverInactivatedCallback(UNK_T);
/* 38ABC4 */ void HSD_SynthSFXSetDriverMasterClockCallback(UNK_T);
/* 38ABCC */ void HSD_SynthSFXSetDriverPauseCallback(UNK_T);
/* 38ABD4 */ void HSD_SynthCallback(void);
/* 38AD60 */ void HSD_SynthResetStreamCounters(int, int, void*, bool);
/* 38AD74 */ UNK_RET HSD_Synth_8038AD74(u32);
/* 38ADD0 */ UNK_RET HSD_Synth_8038ADD0(UNK_PARAMS);
/* 38B120 */ UNK_RET HSD_Synth_8038B120(UNK_PARAMS);
/* 38B380 */ UNK_RET HSD_SynthPStreamFirstHakoHeaderCallback(UNK_PARAMS);
/* 38B3E0 */ void HSD_SynthPStreamHeaderCallback(int, int, void*,
                                                 bool cancelflag);
/* 38B5AC */ int HSD_Synth_8038B5AC(int, u8, u8, int);
/* 38B81C */ void HSD_SynthStreamSetVolume(float);
/* 38B938 */ void HSD_SynthInit(int, int, int, int);

#endif
