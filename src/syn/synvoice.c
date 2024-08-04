#include <dolphin.h>
#include <dolphin/ax.h>
#include <dolphin/mix.h>
#include <dolphin/syn.h>
#include "fake_tgmath.h"

#include "__syn.h"

#define AX_MAX_VOICES 64

struct SYNVOICE __SYNVoice[64];

void __SYNClearVoiceReferences(void * p) {
    AXVPB * axvpb;
    struct SYNSYNTH * synth;
    struct SYNVOICE * voice;

    ASSERTLINE(0x21, p);
    axvpb = p;
    synth = (void*)axvpb->userContext;
    voice = &__SYNVoice[axvpb->index];
    ASSERTLINE(0x26, synth);
    ASSERTLINE(0x27, axvpb->index < AX_MAX_VOICES);
    MIXReleaseChannel(axvpb);
    if (voice->keyGroup) {
        synth->keyGroup[voice->midiChannel][voice->keyGroup] = 0;
    }
    if (synth->voice[voice->midiChannel][voice->keyNum] == voice) {
        synth->voice[voice->midiChannel][voice->keyNum] = 0;
    }
    voice->synth = 0;
    synth->notes--;
}

void __SYNSetVoiceToRelease(struct SYNVOICE * voice, unsigned long priority) {
    ASSERTLINE(0x3F, voice);
    voice->veState = 3;
    voice->peState = 3;
    AXSetVoicePriority(voice->axvpb, priority);
}

void __SYNServiceVoice(int i) {
    struct SYNVOICE * voice;
    struct SYNSYNTH * synth;

    voice = &__SYNVoice[i];
    synth = voice->synth;
    if(synth != NULL) {
        if ((voice->type == 0) && (voice->axvpb->pb.state == 0)) {
            if (voice->keyGroup != 0) {
                voice->synth->keyGroup[voice->midiChannel][voice->keyGroup] = 0;
            }
            if (synth->voice[voice->midiChannel][voice->keyNum] == voice) {
                synth->voice[voice->midiChannel][voice->keyNum] = 0;
            }
            voice->veState = 4;
        }
        __SYNRunVolumeEnvelope(voice);
        if (voice->veState == 4) {
            if (voice->keyGroup != 0) {
                voice->synth->keyGroup[voice->midiChannel][voice->keyGroup] = 0;
            }
            voice->synth = NULL;
            MIXReleaseChannel(voice->axvpb);
            AXFreeVoice(voice->axvpb);
            synth->notes--;
            return;
        }
        __SYNRunLfo(voice);
        __SYNRunPitchEnvelope(voice);
        __SYNUpdateMix(voice);
        __SYNUpdateSrc(voice);
    }
}
