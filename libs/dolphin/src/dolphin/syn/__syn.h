#ifndef _DOLPHIN_SYN_INTERNAL_H_
#define _DOLPHIN_SYN_INTERNAL_H_

#include <dolphin/syn.h>

// syn.c
extern struct SYNSYNTH * __SYNSynthList;

// synctrl.c
extern float __SYNn128[128];

void __SYNClearAllNotes(struct SYNSYNTH * synth);
void __SYNSetController(struct SYNSYNTH * synth, u8 midiChannel, u8 function, u8 value);
void __SYNResetController0(struct SYNSYNTH * synth, u8 midiChannel);
void __SYNResetController(struct SYNSYNTH * synth, u8 midiChannel);
void __SYNResetAllControllers(struct SYNSYNTH * synth);
void __SYNRunInputBufferEvents(struct SYNSYNTH * synth);

// synenv.c
s32 __SYNGetEnvelopeTime(s32 scale, s32 mod, u8 key);
void __SYNSetupVolumeEnvelope(struct SYNVOICE * voice);
void __SYNSetupPitchEnvelope(struct SYNVOICE * voice);
void __SYNRunVolumeEnvelope(struct SYNVOICE * voice);
void __SYNRunPitchEnvelope(struct SYNVOICE * voice);

// synlfo.c
void __SYNSetupLfo(struct SYNVOICE * voice);
void __SYNRunLfo(struct SYNVOICE * voice);

// synmix.c
extern long __SYNVolumeAttenuation[128];
extern long __SYNAttackAttnTable[100];

void __SYNSetupVolume(struct SYNVOICE * voice);
void __SYNSetupPan(struct SYNVOICE * voice);
long __SYNGetVoiceInput(struct SYNVOICE * voice);
long __SYNGetVoiceFader(struct SYNVOICE * voice);
void __SYNUpdateMix(struct SYNVOICE * voice);

// synpitch.c
float __SYNGetRelativePitch(struct SYNVOICE * voice);
void __SYNSetupPitch(struct SYNVOICE * voice);
void __SYNSetupSrc(struct SYNVOICE * voice);
void __SYNUpdateSrc(struct SYNVOICE * voice);

// synsample.c
void __SYNSetupSample(struct SYNVOICE * voice);

// synvoice.c
extern struct SYNVOICE __SYNVoice[64];

void __SYNClearVoiceReferences(void * p);
void __SYNSetVoiceToRelease(struct SYNVOICE * voice, unsigned long priority);
void __SYNServiceVoice(int i);

// synwt.c
int __SYNGetWavetableData(struct SYNVOICE * voice);

#endif // _DOLPHIN_SYN_INTERNAL_H_
