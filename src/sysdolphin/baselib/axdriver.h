/**
 * @file axdriver.h
 * @brief Audio Driver (AXDriver) subsystem for SysDolphin
 * @details The low-level sound engine interfacing with the GameCube DSP audio hardware.
 * Handles voice allocation, streaming, pitch/volume control, and sample playback 
 * for all sound effects and music in Melee.
 */
#ifndef _AXDRIVER_H_
#define _AXDRIVER_H_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#define SMSTATE_MASK 0xC0000000
#define SMSTATE_ACTIVE 0x40000000
#define SMSTATE_SLEEP 0x80000000

typedef enum {
    AXDRIVER_AUX_OFF = 0,
    AXDRIVER_AUX_REVERB_HI = 1,
    AXDRIVER_AUX_REVERB_STD = 2,
    AXDRIVER_AUX_CHORUS = 3,
    AXDRIVER_AUX_DELAY = 4
} AXDriverAuxType;

struct HSD_SM {
    /* 00 */ HSD_SM* prev;
    /* 04 */ HSD_SM* next;
    /* 08 */ u32 flags;
    /* 0C */ int unk;
    /* 10 */ int vID;
    /* 14 */ u16 fid;
    /* 16 */ u16 x16;
    /* 18 */ u8 track;
    /* 19 */ u8 pri;
    /* 1A */ u8 x1A;
    /* 1B */ u8 volume;
    /* 1C */ u8 x1C;
    /* 1D */ u8 pan;
    /* 1E */ u8 x1E;
    /* 20 */ s16 x20;
    /* 22 */ s16 fadetime;
    /* 24 */ u8 x24[2];
    /* 26 */ u8 x26;
    /* 27 */ u8 x27;
    /* 28 */ u8 dp12flag;
    /* 29 */ u8 itdflag;
    /* 2A */ u16 x2A;
    /* 2C */ u32* cmd_stream;
    /* 30 */ int x30;
};

/** @brief Allocates memory on the internal audio heap */
/* 38BB34 */ void* AXDriverAlloc(size_t size);
/** @brief Frees memory on the internal audio heap (stubbed) */
/* 38BB98 */ void AXDriverFree(void* ptr);

/** @brief Unlinks an audio state machine (voice) from a doubly-linked list */
/* 38BB9C */ void AXDriverUnlink(HSD_SM* voice_ptr, HSD_SM** head);

/** @brief Issues a key-off (stop) command to a specific sound effect ID */
/* 38BC20 */ bool HSD_AudioSFXKeyOff(int vid);
/** @brief Issues a key-off command to all currently active sound effects */
/* 38BD6C */ void HSD_AudioSFXKeyOffAll(void);
/** @brief Issues a key-off command to all sound effects on a specific track */
/* 38BE64 */ void HSD_AudioSFXKeyOffTrack(int track);

/** @brief Executes the current state block/commands for an audio voice */
/* 38BF6C */ void AXDriverExec(HSD_SM* voice_ptr);
/** @brief Parses a stream wait command payload */
/* 38C678 */ u32 parseWait(u32 param_type, u32 param_value);
/** @brief Evaluates an audio voice's bytecode command stream */
/* 38C6C0 */ void AXDriverInterp(HSD_SM* voice_ptr);

/** @brief Starts a sound effect with specific parameters (volume, pan, track, channel) */
/* 38CFF4 */ int HSD_AudioSFXStartParam(int sound_id, u8 volume, u8 pan,
                                        int track, int channel);
/** @brief Updates the pan setting for an active sound effect */
/* 38D2B4 */ bool HSD_AudioSFXSetPan(int vid, u8 pan);
/** @brief Updates the volume level for an active sound effect */
/* 38D3B8 */ bool HSD_AudioSFXSetVolumeEx(s32 vid, u8 volume);
/** @brief Updates the pitch setting for an active sound effect */
/* 38D4E4 */ bool HSD_AudioSFXSetPitchFid(s32 vid, s16 pitch);
/** @brief Adjusts the mix level for an auxiliary effect bus (reverb/delay) */
/* 38D5B4 */ bool HSD_AudioSFXSetMix(s32 vid, s32 aux_bus, u8 send_level);
/** @brief Adjusts the mix level for a specific mixer group */
/* 38D914 */ bool HSD_AudioSFXSetMixGroup(s32 channel, s32 aux_bus,
                                          s8 send_level);
/** @brief Checks if a sound effect is currently active */
/* 38D9D8 */ bool HSD_AudioSFXCheck(int vid);

/** @brief Asynchronously loads audio configuration and triggers a callback */
/* 38DA70 */ void AXDriver_8038DA70(const char* path, void (*callback)(void));
/** @brief Internal AX initialization function */
/* 38DCFC */ void AXDriver_8038DCFC(void);
/** @brief Configures an auxiliary effect bus (e.g. chorus, delay, reverb) */
/* 38DD30 */ int AXDriverSetupAux(int channel, AXDriverAuxType type,
                                  void* param);
/** @brief Calculates memory requirements for a specific auxiliary effect */
/* 38E034 */ s32 HSD_AudioGetAuxHeapSize(AXDriverAuxType type, void* param);
/** @brief Allocates and initializes an auxiliary effect bus */
/* 38E30C */ bool HSD_AudioSFXSetupAux(s32 channel, s32 type, void* param,
                                       u8* heap, size_t heap_size);
/** @brief Retrieves the default parameters for a given auxiliary effect type */
/* 38E37C */ bool HSD_AudioSFXGetDefaultAuxParam(AXDriverAuxType type,
                                                 void* param);

/** @brief Configures global settings for multi-channel streaming audio */
/* 38E498 */ void HSD_AudioInitMultiPStream(int voices, int priority,
                                            int sample_rate, int aram_size);
/** @brief Unknown internal setup function */
/* 38E5D4 */ int AXDriver_8038E5D4(void);
/** @brief Unknown internal driver utility */
/* 38E5DC */ int AXDriver_8038E5DC(void);

/** @brief Pauses audio streaming on a specific channel */
/* 38E6C0 */ bool HSD_AudioPStreamPauseCh(int channel);
/** @brief Resumes audio streaming on a specific channel */
/* 38E844 */ bool HSD_AudioPStreamResumeCh(int channel);
/** @brief Starts audio streaming on a channel with specified volume and track */
/* 38E8EC */ bool HSD_AudioPStreamStartChParam(const char* path, u8 volume,
                                               int track);

/** @brief Globally stops the AX hardware driver */
/* 38E968 */ bool AXDriverStop(void);
/** @brief Globally pauses the AX hardware driver */
/* 38E9A8 */ bool AXDriverPause(void);
/** @brief Globally resumes the AX hardware driver */
/* 38E9E0 */ bool AXDriverResume(void);
/** @brief Returns whether the AX hardware driver is currently active */
/* 38EA18 */ bool AXDriverCheck(void);

#endif
