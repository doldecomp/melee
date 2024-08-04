#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/ax.h>
#include <dolphin/mix.h>
#include <dolphin/syn.h>
#include "fake_tgmath.h"

#include "__syn.h"

// .sbss
struct SYNSYNTH * __SYNSynthList;

// functions
static void __SYNAddSynthToList(struct SYNSYNTH * synth);
static void __SYNRemoveSynthFromList(struct SYNSYNTH * synth);

static void __SYNAddSynthToList(struct SYNSYNTH * synth) {
    int old = OSDisableInterrupts();

    if (__SYNSynthList) {
        synth->next = __SYNSynthList;
    } else {
        synth->next = NULL;
    }
    __SYNSynthList = synth;
    OSRestoreInterrupts(old);
}

static void __SYNRemoveSynthFromList(struct SYNSYNTH * synth) {
    struct SYNSYNTH * tempList;
    struct SYNSYNTH * tempSynth;
    int old;

    old = OSDisableInterrupts();
    tempList = NULL;
    
    for(tempSynth = __SYNSynthList; tempSynth; tempSynth = tempSynth->next) {
        if (tempSynth != synth) {
            if (tempList) {
                tempSynth->next = tempList;
            } else {
                tempSynth->next = NULL;
            }
            tempList = tempSynth;
        }
    }
    __SYNSynthList = tempList;
    OSRestoreInterrupts(old);
}

void SYNInit() {
    int i;

    for(i = 0; i < 64; i++) {
        __SYNVoice[i].synth = 0;
    }
    __SYNSynthList = NULL;
}

void SYNQuit() {
    SYNInit();
}

void SYNRunAudioFrame() {
    int i;
    struct SYNSYNTH * synth;

    for(i = 0; i < 64; i++) {
        __SYNServiceVoice(i);
    }
    for(synth = __SYNSynthList; synth; synth = synth->next) {
        __SYNRunInputBufferEvents(synth);
    }
}

void SYNInitSynth(struct SYNSYNTH * synth, void * wavetable, u32 aramBase, u32 priorityVoiceAlloc, u32 priorityNoteOn, u32 priorityNoteRelease) {
    u32 * p;
    u32 midiChannel;
    u32 noteNumber;

    ASSERTLINE(0x84, synth);
    ASSERTLINE(0x85, wavetable);
    ASSERTLINE(0x86, aramBase);
    p = wavetable;
    synth->percussiveInst = (void*)((u32)wavetable + *(p)); p += 1;
    synth->melodicInst = (void*)((u32)wavetable + *(p)); p += 1;
    synth->region = (void*)((u32)wavetable + *(p)); p += 1;
    synth->art = (void*)((u32)wavetable + *(p)); p += 1;
    synth->sample = (void*)((u32)wavetable + *(p)); p += 1;
    synth->adpcm = (void*)((u32)wavetable + *(p)); p += 1;
    synth->aramBaseWord = (aramBase >> 1);
    synth->aramBaseByte = aramBase;
    synth->aramBaseNibble = (aramBase << 1);
    synth->priorityVoiceAlloc = priorityVoiceAlloc;
    synth->priorityNoteOn = priorityNoteOn;
    synth->priorityNoteRelease = priorityNoteRelease;
    synth->masterVolume = 0;
    __SYNResetAllControllers(synth);
    synth->inputPosition = &synth->input[0][0];
    synth->inputCounter = 0;
    synth->notes = 0;
    for(midiChannel = 0; midiChannel < 16; midiChannel++) {
        for(noteNumber = 0; noteNumber < 16; noteNumber++) {
            synth->keyGroup[midiChannel][noteNumber] = 0;
        }
    }
    for(midiChannel = 0; midiChannel < 16; midiChannel++) {
        for(noteNumber = 0; noteNumber < 128; noteNumber++) {
            synth->voice[midiChannel][noteNumber] = 0;
        }
    }
    __SYNAddSynthToList(synth);
}

void SYNQuitSynth(struct SYNSYNTH * synth) {
    int i;
    int old;
    struct SYNVOICE * voice;

    old = OSDisableInterrupts();
    if (synth->notes) {
        for(i = 0; i < 64; i++) {
            voice = &__SYNVoice[i];
            if (voice->synth == synth) {
                MIXReleaseChannel(voice->axvpb);
                AXFreeVoice(voice->axvpb);
                voice->synth = 0;
            }
        }
    }
    __SYNRemoveSynthFromList(synth);
    OSRestoreInterrupts(old);
}

void SYNMidiInput(struct SYNSYNTH * synth, u8 * input) {
    u8 * src;

    ASSERTLINE(0xD7, synth);
    ASSERTLINE(0xD8, input);
    src = input;
    *(synth->inputPosition) = *(src); (synth->inputPosition)+=1; (src)+=1;
    *(synth->inputPosition) = *(src); (synth->inputPosition)+=1; (src)+=1;
    *(synth->inputPosition) = *(src); (synth->inputPosition)+=1; (src)+=1;
    synth->inputCounter++;

    if (synth->inputCounter >= SYN_INPUT_BUFFER_SIZE) {
        ASSERTMSGLINE(0xE5, FALSE, "synth input buffer exceeded, increase SYN_INPUT_BUFFER_SIZE");
    }
}

void SYNSetMasterVolume(struct SYNSYNTH * synth, long dB) {
    ASSERTLINE(0xEE, synth);
    synth->masterVolume = (dB << 0x10);
}

long SYNGetMasterVolume(struct SYNSYNTH * synth) {
    ASSERTLINE(0xF9, synth);
    return synth->masterVolume << 0x10;
}

u32 SYNGetActiveNotes(struct SYNSYNTH * synth) {
    ASSERTLINE(0x104, synth);
    return synth->notes;
}
