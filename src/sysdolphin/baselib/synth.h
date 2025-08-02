#ifndef SYSDOLPHIN_SYNTH_H
#define SYSDOLPHIN_SYNTH_H

#include <placeholder.h>

#include <dolphin/ax.h>

struct HSD_SynthSFXNode;

/* 388330 */ void* HSD_AudioMalloc(size_t);
/* 38838C */ void HSD_AudioFree(void*);
/* 3883B4 */ void HSD_SynthSFXSampleLoadCallback(void*, s32, void*,
                                                 s32 cancelflag);
/* 3887DC */ void HSD_SynthSFXHeaderLoadCallback(void*, int, void*, int);
/* 38893C */ void HSD_SynthSFXLoadNewProc(void);
/* 3889B8 */ int HSD_SynthSFXLoad(char* filename, int, int, int);
/* 388B0C */ void HSD_Synth_80388B0C(void (*)(void));
/* 388B50 */ int HSD_Synth_80388B50(void);
/* 388B60 */ int HSD_Synth_80388B60(int);
/* 388CB0 */ void HSD_Synth_80388CB0(int);
/* 388D30 */ void HSD_Synth_80388D30(int);
/* 388DC8 */ void HSD_Synth_80388DC8(UNK_T);
/* 388E08 */ void HSD_Synth_80388E08(int);
/* 388EFC */ void HSD_SynthSFXGroupDataReaddress(AXVPB*, void* callback);
/* 388FF0 */ void HSD_SynthSFXBankDeflag(int);
/* 389084 */ void HSD_SynthSFXBankDeflagSync(void);
/* 389094 */ u32 HSD_Synth_80389094(void);
/* 3890B4 */ void HSD_Synth_803890B4(int); // set sound mode
/* 38912C */ void HSD_Synth_8038912C(struct HSD_SynthSFXNode*);
/* 3891D0 */ UNK_RET dropcallback(UNK_PARAMS);
/* 389334 */ UNK_RET HSD_Synth_80389334(UNK_PARAMS);
/* 3896F0 */ s32 HSD_Synth_803896F0(u16, u8, u8, u8, u8, u8, u8, f32, f32, f32,
                                    f32, f32);
/* 38987C */ void HSD_SynthSFXKeyOff(int);
/* 3899B0 */ void HSD_SynthSFXStopRange(int);
/* 389A50 */ void HSD_SynthSFXPause(int);
/* 389AD0 */ void HSD_SynthSFXResume(int);
/* 389B50 */ int HSD_SynthSFXCheck(int);
/* 389BD8 */ void HSD_SynthSFXSetVolumeFade(int, u8, int);
/* 389CC4 */ void HSD_Synth_80389CC4(int, u8);
/* 389D24 */ void HSD_SynthSFXSetMix(int, float, float, float);
/* 389D8C */ void HSD_SynthSFXUpdatePitch(struct HSD_SynthSFXNode*);
/* 389E2C */ void HSD_Synth_80389E2C(s32, s32, float);
/* 389F4C */ void HSD_Synth_80389F4C(s32, u8);
/* 38A000 */ UNK_RET HSD_Synth_8038A000(UNK_PARAMS);
/* 38A5A4 */ void HSD_SynthSFXUpdateVolume(struct HSD_SynthSFXNode*);
/* 38A600 */ void HSD_SynthSFXUpdateMix(struct HSD_SynthSFXNode*, int);
/* 38AAB0 */ void HSD_SynthSFXUpdateAllVolume(int, u16, int);
/* 38ABBC */ void HSD_SynthSFXSetDriverInactivatedCallback(UNK_T);
/* 38ABC4 */ void HSD_SynthSFXSetDriverMasterClockCallback(UNK_T);
/* 38ABCC */ void HSD_SynthSFXSetDriverPauseCallback(UNK_T);
/* 38ABD4 */ void HSD_SynthCallback(void);
/* 38AD60 */ void fn_8038AD60(void);
/* 38AD74 */ UNK_RET HSD_Synth_8038AD74(UNK_PARAMS);
/* 38ADD0 */ UNK_RET HSD_Synth_8038ADD0(UNK_PARAMS);
/* 38B120 */ UNK_RET HSD_Synth_8038B120(UNK_PARAMS);
/* 38B380 */ UNK_RET HSD_SynthPStreamFirstHakoHeaderCallback(UNK_PARAMS);
/* 38B3E0 */ void HSD_SynthPStreamHeaderCallback(void*, s32, void*,
                                                 s32 cancelflag);
/* 38B5AC */ int HSD_Synth_8038B5AC(int, u8, int, int);
/* 38B81C */ void HSD_SynthStreamSetVolume(float);
/* 38B938 */ void HSD_SynthInit(int, int, int, int);

#endif
