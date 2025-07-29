#include "synth.h"

#include "synth.static.h"

#include <dolphin/os.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>

void* HSD_AudioMalloc(size_t arg0)
{
    void* temp_r3 = OSAllocFromHeap(HSD_Synth_804D6018, arg0);
    if (temp_r3 == NULL) {
        OSReport("audio heap overflow.\n");
        __assert("synth.c", 0x29U, "p");
    }
    return temp_r3;
}

void HSD_AudioFree(void* arg0)
{
    OSFreeToHeap(HSD_Synth_804D6018, arg0);
}

/// #HSD_SynthSFXSampleLoadCallback

/// #HSD_SynthSFXHeaderLoadCallback

void HSD_SynthSFXLoadNewProc(void)
{
    if (HSD_Synth_804D772C != 0) {
        bool enabled = OSDisableInterrupts();
        HSD_Synth_804D6028[0] = HSD_DevComRequest(
            HSD_Synth_804C2A60[0].entrynum, 0, (u32) HSD_Synth_804C2AC0, 0x20U,
            0x21, 1, HSD_SynthSFXHeaderLoadCallback, NULL);
        OSRestoreInterrupts(enabled);
    }
}

int HSD_SynthSFXLoad(char* filename, int bankID, int arg2, int arg3)
{
    int entrynum;
    bool enabled;

    HSD_ASSERTREPORT(0x103, (bankID >= 0 && bankID < hsd_SynthSFXBankNum),
                     "invalid bankID = %d; filename = %s\n", bankID, filename);

    entrynum = DVDConvertPathToEntrynum(filename);

    while (HSD_Synth_804D772C >= 6) {
    }

    enabled = OSDisableInterrupts();
    HSD_Synth_804C2A60[HSD_Synth_804D772C].entrynum = entrynum;
    HSD_Synth_804C2A60[HSD_Synth_804D772C].bankID = bankID;
    HSD_Synth_804C2A60[HSD_Synth_804D772C].x8 = arg2;
    HSD_Synth_804C2A60[HSD_Synth_804D772C].xC = arg3;
    HSD_Synth_804D772C += 1;

    if (HSD_Synth_804D772C == 1) {
        HSD_SynthSFXLoadNewProc();
    }

    OSRestoreInterrupts(enabled);
    return entrynum;
}

void HSD_Synth_80388B0C(void (*arg0)(void))
{
    while (HSD_Synth_804D772C != 0) {
        arg0();
    }
}

int HSD_Synth_80388B50(void)
{
    return HSD_Synth_804D772C - HSD_Synth_804D7738;
}

int HSD_Synth_80388B60(int entrynum)
{
    int result = 0;
    bool enabled = OSDisableInterrupts();

    if (HSD_Synth_804D772C != 0) {
        if (HSD_Synth_804C2A60[0].entrynum == entrynum &&
            HSD_Synth_804D7738 == 0)
        {
            int i;
            HSD_Synth_804D7738 = 1;
            for (i = 0; i < 2; i++) {
                HSD_DevComCancelEx(HSD_Synth_804D6028[i], 0, 0, 0);
            }
            result = 1;
        } else {
            int idx = 1;
            while (idx < HSD_Synth_804D772C) {
                if (HSD_Synth_804C2A60[idx].entrynum == entrynum) {
                    int j;
                    for (j = idx; j < HSD_Synth_804D772C - 1; j++) {
                        HSD_Synth_804C2A60[j] = HSD_Synth_804C2A60[j + 1];
                    }
                    HSD_Synth_804D772C--;
                    result = 1;
                    break;
                }
                idx++;
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return result;
}

void HSD_Synth_80388CB0(int arg0)
{
    int temp_r0 = hsd_SynthSFXBankHead[hsd_SynthSFXBankNum];

    HSD_Synth_804C2B60[hsd_SynthSFXBankNum] = temp_r0;
    hsd_SynthSFXBankHead[hsd_SynthSFXBankNum + 1] = arg0 + temp_r0;

    HSD_ASSERTREPORT(0x158,
                     hsd_SynthSFXBankHead[hsd_SynthSFXBankNum + 1] <=
                         hsd_SynthSFXBankAREnd,
                     "bank overflow\n");
    hsd_SynthSFXBankNum += 1;
}

void HSD_Synth_80388D30(int arg0)
{
    int i;
    AXVPB* temp_r29;
    AXVPB** temp_r27;

    HSD_SynthSFXStopRange(arg0);
    temp_r27 = &HSD_Synth_804C2AE0[arg0];
    while ((temp_r29 = *temp_r27)) {
        AXVPB* cur;
        for (i = 0; i < temp_r29->priority; i++) {
            HSD_Synth_80388DC8((u8*) temp_r29->next1 + i);
        }
        cur = *temp_r27;
        *temp_r27 = (*temp_r27)->next;
        HSD_AudioFree(cur);
    }
    HSD_Synth_804C2B60[arg0] = hsd_SynthSFXBankHead[arg0];
}

/// #HSD_Synth_80388DC8

/// #HSD_Synth_80388E08

static void HSD_SynthSFXGroupDataReaddressCallback(void* arg0, int arg1,
                                                   void* arg2, int cancelflag)
{
    HSD_ASSERT(0x182, sfxGroupDataReaddressCounter > 0);
    sfxGroupDataReaddressCounter--;
}

/// #HSD_SynthSFXGroupDataReaddress

void HSD_SynthSFXBankDeflag(int arg0)
{
    AXVPB* var_r29;
    intptr_t var_r28;

    HSD_SynthSFXStopRange(arg0);
    var_r29 = HSD_Synth_804C2AE0[arg0];
    var_r28 = hsd_SynthSFXBankHead[arg0];
    while (var_r29 != NULL) {
        if ((intptr_t) var_r29->callback != var_r28) {
            HSD_SynthSFXGroupDataReaddress(var_r29, (void*) var_r28);
        }
        var_r28 += var_r29->userContext;
        var_r29 = var_r29->next;
    }
    HSD_Synth_804C2AE0[arg0 + 0x80 / 4] = (void*) var_r28;
}

void HSD_SynthSFXBankDeflagSync(void)
{
    while (sfxGroupDataReaddressCounter) {
        continue;
    }
}

u32 HSD_Synth_80389094(void)
{
    return OSGetSoundMode();
}

void HSD_Synth_803890B4(int mode)
{
    int i;
    HSD_Synth_804D7754 = mode;
    for (i = 0; i < (int) ARRAY_SIZE(HSD_SynthSFXNodes); i++) {
        if (HSD_SynthSFXNodes[i].x0 > 0) {
            HSD_SynthSFXUpdateMix(&HSD_SynthSFXNodes[i], 1);
        }
    }
    OSSetSoundMode(mode);
}

void HSD_Synth_8038912C(struct HSD_SynthSFXNode* node)
{
    int i;
    PAD_STACK(0x10);

    if (!(node->flags & 1) && node->x27 == 1 &&
        driverInactivatedCallback != NULL)
    {
        driverInactivatedCallback(node->x0);
    }
    for (i = 0; i < node->voice_count; i++) {
        AXFreeVoice(node->voice[i]);
        HSD_SynthSFXNodes[node->voice[i]->index].x0 = 0;
    }
}

/// #dropcallback

/// #HSD_Synth_80389334

/// #HSD_Synth_803896F0

/// #HSD_SynthSFXKeyOff

static inline void stopRange(u32 temp_r30, u32 temp_r29)
{
    u32 temp_r0;
    int i;
    for (i = 0; i < 0x40; i++) {
        struct HSD_SynthSFXNode* node = &HSD_SynthSFXNodes[i];
        if (HSD_SynthSFXNodes[i].x0 > 0) {
            temp_r0 = *(u32*) &HSD_SynthSFXNodes[i]
                           .voice[0]
                           ->pb.addr.currentAddressHi;
            if (temp_r0 >= temp_r30 && temp_r0 < temp_r29) {
                HSD_Synth_8038912C(&HSD_SynthSFXNodes[i]);
            }
        }
    }
}

void HSD_SynthSFXStopRange(int arg0)
{
    stopRange(hsd_SynthSFXBankHead[arg0 + 0] * 2,
              hsd_SynthSFXBankHead[arg0 + 1] * 2);
}

static inline struct HSD_SynthSFXNode* getNode(int arg0)
{
    struct HSD_SynthSFXNode* var_r5 = &HSD_SynthSFXNodes[arg0 & 0x3F];
    if (arg0 > 0 && var_r5->x0 == arg0) {
        return var_r5;
    } else {
        return NULL;
    }
}

void HSD_SynthSFXPause(int arg0)
{
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(arg0))) {
        node->flags |= 2;
        HSD_SynthSFXUpdateVolume(node);
        if (node->flags & 8) {
            node->flags |= 6;
        }
    }
}

void HSD_SynthSFXResume(int arg0)
{
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(arg0))) {
        if (node->flags & 2) {
            node->flags &= ~6;
            HSD_SynthSFXUpdatePitch(node);
            HSD_SynthSFXUpdateVolume(node);
        }
    }
}

int HSD_SynthSFXCheck(int arg0)
{
    struct HSD_SynthSFXNode* var_r4 = getNode(arg0);
    int i;

    if (var_r4 != NULL) {
        if (var_r4->flags & 1) {
            return -1;
        }
        for (i = 0; i < var_r4->voice_count; i++) {
            if (var_r4->voice[i]->pb.state == 0) {
                return -1;
            }
        }
        return arg0;
    }
    return -1;
}

void HSD_SynthSFXSetVolumeFade(int arg0, u8 arg1, int flag)
{
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(arg0))) {
        HSD_ASSERT(0x376, flag >= 0 && flag < USERVOL_NUM);
        node->x2C[flag].x0 = 1 / 255.0 * arg1;
        node->x2C[flag].x4 = 1;
        HSD_SynthSFXUpdateVolume(node);
    }
}

/// #HSD_Synth_80389CC4

void HSD_SynthSFXSetMix(int arg0, float arg8, float arg9, float argA)
{
    int* var_r3;
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(arg0))) {
        node->x44 = arg8;
        node->x48 = arg9;
        node->x4C = argA;
        HSD_SynthSFXUpdateMix(node, 1);
    }
}

void HSD_SynthSFXUpdatePitch(struct HSD_SynthSFXNode* arg0)
{
    float ratio;

    if (arg0->flags & 4) {
        ratio = 0.0F;
    } else {
        ratio = arg0->x14 * arg0->x18 * arg0->x1C;
    }
    if (!(arg0->flags & 8)) {
        int i;
        for (i = 0; i < arg0->voice_count; i++) {
            AXSetVoiceSrcRatio(arg0->voice[i], ratio);
        }
    }
}

/// #HSD_Synth_80389E2C

/// #HSD_Synth_80389F4C

/// #HSD_Synth_8038A000

void HSD_SynthSFXUpdateVolume(struct HSD_SynthSFXNode* node)
{
    bool enabled = OSDisableInterrupts();
    if (!node->volume_update_pending && !(node->flags & 8)) {
        node->volume_update_pending = true;
        node->x20 = HSD_Synth_804D774C;
        HSD_Synth_804D774C = node;
    }
    OSRestoreInterrupts(enabled);
}

/// #HSD_SynthSFXUpdateMix

void HSD_SynthSFXUpdateAllVolume(int arg0, u16 arg1, int arg2)
{
    int i;
    u32 mask;

    PAD_STACK(4);

    HSD_Synth_804C28E0_1784[arg2].x1788 = 1 / 255.0F * arg0;
    if (HSD_Synth_804C28E0_1784[arg2].x1784 !=
        HSD_Synth_804C28E0_1784[arg2].x1788)
    {
        HSD_Synth_804C28E0_1784[arg2].x178C = arg1;
        mask = 1 << arg2;
        HSD_Synth_804D7758 |= mask;

        for (i = 0; i < 0x40; i++) {
            struct HSD_SynthSFXNode* node = &HSD_SynthSFXNodes[i];
            if (node->x0 > 0 && ((1 << node->xB) & mask)) {
                HSD_SynthSFXUpdateVolume(node);
            }
        }
    }
}

void HSD_SynthSFXSetDriverInactivatedCallback(UNK_T arg0)
{
    driverInactivatedCallback = arg0;
}

void HSD_SynthSFXSetDriverMasterClockCallback(UNK_T arg0)
{
    driverMasterClockCallback = arg0;
}

void HSD_SynthSFXSetDriverPauseCallback(UNK_T arg0)
{
    driverPauseCallback = arg0;
}

static inline void freeVoices(struct HSD_SynthSFXNode* node)
{
    int j;
    for (j = 0; j < node->voice_count; j++) {
        AXFreeVoice(node->voice[j]);
        HSD_SynthSFXNodes[node->voice[j]->index].x0 = 0;
    }
}

void HSD_SynthCallback(void)
{
    int i;
    int j;
    bool enabled;
    int base;
    PAD_STACK(0x8);

    base = HSD_Synth_804D775C % 8 * 8;

    enabled = OSDisableInterrupts();

    while (HSD_Synth_804D7720-- > 0) {
        if (HSD_Synth_804C28E0[HSD_Synth_804D7720] != 0) {
            AXFreeVoice(HSD_Synth_804C28E0[HSD_Synth_804D7720]);
        }
    }
    HSD_Synth_804D7720 = 0;

    for (i = 0; i < 8; i++) {
        struct HSD_SynthSFXNode* node = &HSD_SynthSFXNodes[base + i];
        if (node->x0 > 0) {
            if (!(node->flags & 8) && node->voice[0]->pb.state == 0 &&
                (node->voice_count == 1 || node->voice[1]->pb.state == 0))
            {
                HSD_Synth_8038912C(node);
            }
        }
    }

    HSD_Synth_8038A000();

    if (driverMasterClockCallback != NULL) {
        driverMasterClockCallback(HSD_Synth_804D775C);
    }

    HSD_Synth_8038ADD0();
    HSD_Synth_804D775C++;
    OSRestoreInterrupts(enabled);
}

void fn_8038AD60(void)
{
    HSD_Synth_804D776C = HSD_Synth_804D7768, HSD_Synth_804D7778 = 0;
}

/// #HSD_Synth_8038AD74

/// #HSD_Synth_8038ADD0(void)

/// #HSD_Synth_8038B120

/// #HSD_SynthPStreamFirstHakoHeaderCallback

/// #HSD_SynthPStreamHeaderCallback

/// #HSD_Synth_8038B5AC

/// #HSD_SynthStreamSetVolume

/// #HSD_SynthInit
