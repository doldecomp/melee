#ifndef _DOLPHIN_SYN_H_
#define _DOLPHIN_SYN_H_

#include <dolphin/ax.h>

#define SYN_INPUT_BUFFER_SIZE 0x100

struct WTINST {
    /* 0x00 */ u16 keyRegion[128];
};

struct WTREGION {
    /* 0x00 */ u8 unityNote;
    /* 0x01 */ u8 keyGroup;
    /* 0x02 */ s16 fineTune;
    /* 0x04 */ long attn;
    /* 0x08 */ u32 loopStart;
    /* 0x0C */ u32 loopLength;
    /* 0x10 */ u32 articulationIndex;
    /* 0x14 */ u32 sampleIndex;
};

struct WTART {
    /* 0x00 */ long lfoFreq;
    /* 0x04 */ long lfoDelay;
    /* 0x08 */ long lfoAtten;
    /* 0x0C */ long lfoPitch;
    /* 0x10 */ long lfoMod2Atten;
    /* 0x14 */ long lfoMod2Pitch;
    /* 0x18 */ long eg1Attack;
    /* 0x1C */ long eg1Decay;
    /* 0x20 */ long eg1Sustain;
    /* 0x24 */ long eg1Release;
    /* 0x28 */ long eg1Vel2Attack;
    /* 0x2C */ long eg1Key2Decay;
    /* 0x30 */ long eg2Attack;
    /* 0x34 */ long eg2Decay;
    /* 0x38 */ long eg2Sustain;
    /* 0x3C */ long eg2Release;
    /* 0x40 */ long eg2Vel2Attack;
    /* 0x44 */ long eg2Key2Decay;
    /* 0x48 */ long eg2Pitch;
    /* 0x4C */ long pan;
};

struct WTSAMPLE {
    /* 0x00 */ u16 format;
    /* 0x02 */ u16 sampleRate;
    /* 0x04 */ u32 offset;
    /* 0x08 */ u32 length;
    /* 0x0C */ u16 adpcmIndex;
};

struct WTADPCM {
    /* 0x00 */ u16 a[8][2];
    /* 0x20 */ u16 gain;
    /* 0x22 */ u16 pred_scale;
    /* 0x24 */ u16 yn1;
    /* 0x26 */ u16 yn2;
    /* 0x28 */ u16 loop_pred_scale;
    /* 0x2A */ u16 loop_yn1;
    /* 0x2C */ u16 loop_yn2;
};

struct SYNSYNTH {
    /* 0x0000 */ void * next;
    /* 0x0004 */ struct WTINST * percussiveInst;
    /* 0x0008 */ struct WTINST * melodicInst;
    /* 0x000C */ struct WTREGION * region;
    /* 0x0010 */ struct WTART * art;
    /* 0x0014 */ struct WTSAMPLE * sample;
    /* 0x0018 */ struct WTADPCM * adpcm;
    /* 0x001C */ u32 aramBaseWord;
    /* 0x0020 */ u32 aramBaseByte;
    /* 0x0024 */ u32 aramBaseNibble;
    /* 0x0028 */ u32 priorityVoiceAlloc;
    /* 0x002C */ u32 priorityNoteOn;
    /* 0x0030 */ u32 priorityNoteRelease;
    /* 0x0034 */ struct WTINST * inst[16];
    /* 0x0074 */ long masterVolume;
    /* 0x0078 */ u8 controller[16][128];
    /* 0x0878 */ u8 rpn[16];
    /* 0x0888 */ s16 dataEntry[16];
    /* 0x08A8 */ long pwMaxCents[16];
    /* 0x08E8 */ long pwCents[16];
    /* 0x0928 */ long volAttn[16];
    /* 0x0968 */ long expAttn[16];
    /* 0x09A8 */ long auxAAttn[16];
    /* 0x09E8 */ long auxBAttn[16];
    /* 0x0A28 */ u8 input[SYN_INPUT_BUFFER_SIZE][3];
    /* 0x0D28 */ u8 * inputPosition;
    /* 0x0D2C */ u32 inputCounter;
    /* 0x0D30 */ u32 notes;
    /* 0x0D34 */ void * keyGroup[16][16];
    /* 0x1134 */ void * voice[16][128];
};

struct SYNVOICE {
    /* 0x00 */ void * next;
    /* 0x04 */ AXVPB * axvpb;
    /* 0x08 */ struct SYNSYNTH * synth;
    /* 0x0C */ u8 midiChannel;
    /* 0x0D */ u8 keyNum;
    /* 0x0E */ u8 keyVel;
    /* 0x0F */ u8 pan;
    /* 0x10 */ u8 keyGroup;
    /* 0x14 */ struct WTREGION * region;
    /* 0x18 */ struct WTART * art;
    /* 0x1C */ struct WTSAMPLE * sample;
    /* 0x20 */ struct WTADPCM * adpcm;
    /* 0x24 */ u32 hold;
    /* 0x28 */ u32 type;
    /* 0x2C */ f32 srcRatio;
    /* 0x30 */ long cents;
    /* 0x34 */ long attn;
    /* 0x38 */ long lfoState;
    /* 0x3C */ long lfoAttn;
    /* 0x40 */ long lfoCents;
    /* 0x44 */ long lfoFreq;
    /* 0x48 */ long lfoDelay;
    /* 0x4C */ long lfoAttn_;
    /* 0x50 */ long lfoCents_;
    /* 0x54 */ long lfoModAttn;
    /* 0x58 */ long lfoModCents;
    /* 0x5C */ u32 veState;
    /* 0x60 */ long veAttn;
    /* 0x64 */ long veAttack;
    /* 0x68 */ long veAttackDelta;
    /* 0x6C */ long veDecay;
    /* 0x70 */ long veSustain;
    /* 0x74 */ long veRelease;
    /* 0x78 */ u32 peState;
    /* 0x7C */ long peCents;
    /* 0x80 */ long peAttack;
    /* 0x84 */ long peDecay;
    /* 0x88 */ long peSustain;
    /* 0x8C */ long peRelease;
    /* 0x90 */ long pePitch;
};

// sample formats
#define SYN_SAMPLE_FORMAT_ADPCM 0
#define SYN_SAMPLE_FORMAT_PCM16 1
#define SYN_SAMPLE_FORMAT_PCM8  2

// syn.c
void SYNInit();
void SYNQuit();
void SYNRunAudioFrame();
void SYNInitSynth(struct SYNSYNTH * synth, void * wavetable, u32 aramBase, u32 priorityVoiceAlloc, u32 priorityNoteOn, u32 priorityNoteRelease);
void SYNQuitSynth(struct SYNSYNTH * synth);
void SYNMidiInput(struct SYNSYNTH * synth, u8 * input);
void SYNSetMasterVolume(struct SYNSYNTH * synth, long dB);
long SYNGetMasterVolume(struct SYNSYNTH * synth);
u32 SYNGetActiveNotes(struct SYNSYNTH * synth);

// synctrl.c
u8 SYNGetMidiController(struct SYNSYNTH * synth, u8 midiChannel, u8 function);

#endif // _DOLPHIN_SYN_H_
