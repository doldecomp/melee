#include "synth.h"

#include "synth.static.h"

#include <dolphin/ai.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>

/* 389334 */ static int HSD_Synth_80389334(int arg0, u8 arg1, u8 arg2, u8 arg3,
                                           int arg4, u8 arg5, float arg6,
                                           float arg7, float arg8, float arg9,
                                           float argA);

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

extern void* HSD_Synth_804D7730;

static void HSD_SynthSFXHeaderLoadCallback(void* arg0, int arg1, void* arg2,
                                           int arg3)
{
    AXVPB** temp_r3_2;
    s32 temp_r26;
    void* temp_r3_3;
    size_t tmp;

    if (HSD_Synth_804D7738 == 0) {
        int bankID = HSD_Synth_804C2A60[0].bankID;

        HSD_ASSERTREPORT(0xCD,
                         hsd_SynthSFXBankHead[bankID + 1] -
                                 hsd_SynthSFXBank[bankID] >=
                             hsd_SynthSFXLoadBuf[1],
                         "Can't load SFX file; bank(id=%d) buffer overflow.\n",
                         HSD_Synth_804C2A60[0].bankID);

        tmp = hsd_SynthSFXLoadBuf[2] * 8 + 0x18;
        temp_r26 = hsd_SynthSFXLoadBuf[0];
        temp_r3_3 =
            OSAllocFromHeap(HSD_Synth_804D6018, OSRoundUp32B(tmp + temp_r26));
        if (temp_r3_3 == NULL) {
            OSReport("audio heap overflow.\n");
            __assert("synth.c", 0x29U, "p");
        }
        HSD_Synth_804D7730 = temp_r3_3;
        HSD_Synth_804D6028[1] = HSD_DevComRequest(
            HSD_Synth_804C2A60[0].entrynum, 0x20, (u32) HSD_Synth_804D7730,
            OSRoundUp32B(temp_r26 - 0x10), 0x21, 1, NULL, NULL);
        HSD_Synth_804D6028[0] = HSD_DevComRequest(
            HSD_Synth_804C2A60[0].entrynum, OSRoundUp32B(temp_r26 + 0x10),
            hsd_SynthSFXBank[HSD_Synth_804C2A60[0].bankID],
            hsd_SynthSFXLoadBuf[1], 0x23, 1, HSD_SynthSFXSampleLoadCallback,
            NULL);
        return;
    }
    HSD_Synth_804D7730 = NULL;
    HSD_SynthSFXSampleLoadCallback(NULL, 0, NULL, 0);
}

void HSD_SynthSFXLoadNewProc(void)
{
    if (HSD_Synth_804D772C != 0) {
        bool enabled = OSDisableInterrupts();
        HSD_Synth_804D6028[0] = HSD_DevComRequest(
            HSD_Synth_804C2A60[0].entrynum, 0, (size_t) hsd_SynthSFXLoadBuf,
            0x20, 0x21, 1, HSD_SynthSFXHeaderLoadCallback, NULL);
        OSRestoreInterrupts(enabled);
    }
}

int HSD_SynthSFXLoad(const char* filename, int bankID, int arg2, int arg3)
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

void HSD_SynthSFXWaitForLoadCompletion(void (*arg0)(void))
{
    while (HSD_Synth_804D772C != 0) {
        arg0();
    }
}

int HSD_SynthSFXGetPendingLoadCount(void)
{
    return HSD_Synth_804D772C - HSD_Synth_804D7738;
}

int HSD_SynthSFXCancelLoad(int entrynum)
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

void HSD_SynthSFXAllocateBank(int arg0)
{
    int temp_r0 = hsd_SynthSFXBankHead[hsd_SynthSFXBankNum];

    hsd_SynthSFXBank[hsd_SynthSFXBankNum] = temp_r0;
    hsd_SynthSFXBankHead[hsd_SynthSFXBankNum + 1] = arg0 + temp_r0;

    HSD_ASSERTREPORT(0x158,
                     hsd_SynthSFXBankHead[hsd_SynthSFXBankNum + 1] <=
                         hsd_SynthSFXBankAREnd,
                     "bank overflow\n");
    hsd_SynthSFXBankNum += 1;
}

static inline void HSD_SynthSFXUnloadBank_inline(AXVPB* temp_r29)
{
    int i;
    for (i = 0; i < temp_r29->priority; i++) {
        HSD_Synth_80388DC8((u8*) temp_r29->next1 + i);
    }
}

void HSD_SynthSFXUnloadBank(int arg0)
{
    AXVPB** temp_r27;
    HSD_SynthSFXStopRange(arg0);
    temp_r27 = &HSD_Synth_804C2AE0[arg0];
    while (*temp_r27 != NULL) {
        AXVPB* cur;
        HSD_SynthSFXUnloadBank_inline(*temp_r27);
        cur = *temp_r27;
        *temp_r27 = (*temp_r27)->next;
        HSD_AudioFree(cur);
    }
    hsd_SynthSFXBank[arg0] = hsd_SynthSFXBankHead[arg0];
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

u32 HSD_SynthGetSoundMode(void)
{
    return OSGetSoundMode();
}

void HSD_SynthSetSoundMode(int mode)
{
    int i;
    HSD_Synth_804D7754 = mode;
    for (i = 0; i < (int) ARRAY_SIZE(hsd_SynthSFXNodes); i++) {
        if (hsd_SynthSFXNodes[i].x0 > 0) {
            HSD_SynthSFXUpdateMix(&hsd_SynthSFXNodes[i], 1);
        }
    }
    OSSetSoundMode(mode);
}

void HSD_SynthSFXStopNode(struct HSD_SynthSFXNode* node)
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
        hsd_SynthSFXNodes[node->voice[i]->index].x0 = 0;
    }
}

/// #dropcallback

static AXPBSRC HSD_Synth_80407FD8 = { 1, 0, 0, { 0, 0, 0, 0 } };

int HSD_Synth_80389334(int arg0, u8 arg1, u8 arg2, u8 arg3, int arg4, u8 arg5,
                       float arg6, float arg7, float arg8, float arg9,
                       float argA)
{
    AXVPB* sp4C[2] = { NULL, NULL };
    AXPBVE sp40;
    float temp_f0;
    float temp_f1;
    int var_r20;
    u32 temp_r30;
    int var_r29;
    struct foo {
        void* next;
        int unk4; // sound ID
        int unk8; // voice count
        int unkC; // audio parameter
        AXPBADDR x10;
        AXPBADPCM x20;
        AXPBADPCMLOOP x48;
    }* var_r28;
    struct HSD_SynthSFXNode* temp_r27;
    int temp_r26;
    AXVPB** var_r21_2;
    struct foo* var_r23;

    PAD_STACK(0x1C);

    temp_r26 = OSDisableInterrupts();
    var_r28 = HSD_Synth_804C29E0[arg0 & 0x1F];

    while (var_r28 != NULL) {
        if (var_r28->unk4 == arg0) {
            var_r20 = 0;
            while (var_r20 < var_r28->unk8) {
                sp4C[var_r20] = AXAcquireVoice(arg4 + 1, dropcallback, 0U);
                if (sp4C[var_r20] == NULL) {
                    if (sp4C[0] != NULL) {
                        AXFreeVoice(sp4C[0]);
                    }
                    OSRestoreInterrupts(temp_r26);
                    return -1;
                }
                var_r20 += 1;
            }
            if ((var_r28->unk8 == 2) && (sp4C[0] == sp4C[1])) {
                AXFreeVoice(sp4C[0]);
                OSRestoreInterrupts(temp_r26);
                return -1;
            }
            if (var_r28->unk8 == 2) {
                hsd_SynthSFXNodes[sp4C[1]->index].x0 = -1;
                hsd_SynthSFXNodes[sp4C[1]->index].voice[0] = sp4C[0];
            }

            temp_r30 = sp4C[0]->index;

            temp_r27 = &hsd_SynthSFXNodes[temp_r30];
            temp_r27->x27 = 1;
            temp_r27->x0 = arg0;
            temp_r27->flags = 0;
            temp_r27->voice_count = var_r28->unk8;
            temp_r27->xB = arg5;
            temp_r27->voice[0] = sp4C[0];
            temp_r27->voice[1] = sp4C[1];
            temp_r27->x14 = 0.00003125f * var_r28->unkC;
            temp_r27->x18[0] = arg6;
            temp_r27->x18[1] = arg7;
            temp_f1 = 1 / 255.0F * arg1;
            temp_f0 = 1 / 255.0F * arg2;
            temp_r27->unk28 = temp_f1;
            temp_r27->user_vol[0].volume = temp_f1;
            temp_r27->user_vol[0].x4 = 0;
            temp_r27->user_vol[0].x8_float = temp_f0;
            temp_r27->user_vol[1].volume = temp_f0;
            temp_r27->user_vol[1].x4 = 0;
            temp_r27->user_vol[1].x8 = arg3;
            temp_r27->x44 = arg8;
            temp_r27->x48 = arg9;
            temp_r27->x4C = argA;
            HSD_SynthSFXUpdateVolume(temp_r27);
            HSD_SynthSFXUpdateMix(temp_r27, 0);
            sp40.currentVolume =
                (32767.0f * (temp_r27->user_vol[0].x8_float *
                             (temp_r27->unk28 *
                              (HSD_Synth_804D6030 *
                               HSD_Synth_804C28E0_1784[temp_r27->xB].x1784))));
            sp40.currentDelta = 0;
            temp_r27->x24 = sp40.currentVolume;

            var_r23 = (void*) ((u8*) var_r28 + 0x40 * arg1);
            var_r21_2 = &sp4C[arg1];
            var_r29 = 0;
            while (var_r29 < var_r28->unk8) {
                AXSetVoicePriority(*var_r21_2, arg4);
                AXSetVoiceVe(*var_r21_2, &sp40);
                *(u32*) &HSD_Synth_80407FD8.ratioHi =
                    (65536.0f *
                     (temp_r27->x18[1] * (temp_r27->x14 * temp_r27->x18[0])));
                AXSetVoiceSrc(*var_r21_2, &HSD_Synth_80407FD8);
                AXSetVoiceAddr(*var_r21_2, &var_r23->x10);
                AXSetVoiceAdpcm(*var_r21_2, &var_r23->x20);
                AXSetVoiceAdpcmLoop(*var_r21_2, &var_r23->x48);
                AXSetVoiceState(*var_r21_2, 1U);
                var_r21_2 += 1;
                var_r23 = (void*) ((u8*) var_r23 +
                                   0x40); ///< @todo what is going on here...
                var_r29 += 1;
            }
            HSD_Synth_804D7750 += 0x40;
            if (HSD_Synth_804D7750 < 0) {
                HSD_Synth_804D7750 = 0x40;
            }
            temp_r27->x0 = HSD_Synth_804D7750 + temp_r30;
            OSRestoreInterrupts(temp_r26);
            return temp_r27->x0;
        }
        var_r28 = var_r28->next;
    }

    OSRestoreInterrupts(temp_r26);
    return -1;
}

static inline struct HSD_SynthSFXNode* getNode(int arg0)
{
    struct HSD_SynthSFXNode* var_r5 = &hsd_SynthSFXNodes[arg0 & 0x3F];
    if (arg0 > 0 && var_r5->x0 == arg0) {
        return var_r5;
    } else {
        return NULL;
    }
}

bool HSD_SynthSFXPlayWithGroup(int arg0, u8 arg1, u8 arg2, u8 arg3, int arg4,
                               u8 arg5, int group, f32 arg7, f32 arg8,
                               f32 arg9, f32 argA, f32 argB)
{
    bool result;
    int nodeID;
    struct HSD_SynthSFXNode* node;

    PAD_STACK(0x8);

    HSD_ASSERTREPORT(0x30B, group >= 0 && group < HSD_SYNTHSFXGROUP_MAX,
                     "sfx group ID %d out of range.", group);

    if (group != 0) {
        nodeID = HSD_Synth_804C28E0_1844[group];
        if (nodeID > 0) {
            node = getNode(nodeID);
            if (node != NULL && node->flags != 1) {
                if (node->x27 == 1 && driverInactivatedCallback != NULL) {
                    driverInactivatedCallback(node->x0);
                }
                HSD_SynthSFXKeyOff(HSD_Synth_804C28E0_1844[group]);
            }
        }
    }

    result = HSD_Synth_80389334(arg0, arg1, arg2, arg3, arg4, arg5, arg7, arg8,
                                arg9, argA, argB);
    HSD_Synth_804C28E0_1844[group] = result;
    return result;
}

/// #HSD_SynthSFXKeyOff

static inline void stopRange(size_t lo, size_t hi)
{
    size_t addr;
    int i;
    for (i = 0; i < 0x40; i++) {
        struct HSD_SynthSFXNode* node = &hsd_SynthSFXNodes[i];
        if (hsd_SynthSFXNodes[i].x0 > 0) {
            addr = *(size_t*) &hsd_SynthSFXNodes[i]
                        .voice[0]
                        ->pb.addr.currentAddressHi;
            if (addr >= lo && addr < hi) {
                HSD_SynthSFXStopNode(&hsd_SynthSFXNodes[i]);
            }
        }
    }
}

void HSD_SynthSFXStopRange(int arg0)
{
    stopRange(hsd_SynthSFXBankHead[arg0 + 0] * 2,
              hsd_SynthSFXBankHead[arg0 + 1] * 2);
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
        node->user_vol[flag].volume = 1 / 255.0 * arg1;
        node->user_vol[flag].x4 = 1;
        HSD_SynthSFXUpdateVolume(node);
    }
}

void HSD_SynthSFXSetUserVol(int arg0, u8 arg1)
{
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(arg0))) {
        node->user_vol[1].x8 = arg1;
        HSD_SynthSFXUpdateMix(node, 1);
    }
}

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
        ratio = arg0->x14 * arg0->x18[0] * arg0->x18[1];
    }
    if (!(arg0->flags & 8)) {
        int i;
        for (i = 0; i < arg0->voice_count; i++) {
            AXSetVoiceSrcRatio(arg0->voice[i], ratio);
        }
    }
}

void HSD_SynthSFXSetPitchRatio(int arg0, int flag, float arg2)
{
    struct HSD_SynthSFXNode* node = getNode(arg0);

    if (node != NULL && !(node->flags & 1)) {
        HSD_ASSERT(0x3A7, flag == 0 || flag == 1);

        node->x18[flag] = arg2;

        HSD_SynthSFXUpdatePitch(node);
    }
}

void HSD_SynthSFXSetPriority(int id, int prio)
{
    struct HSD_SynthSFXNode* node = getNode(id);
    int i;

    if (node != NULL && !(node->flags & 1)) {
        for (i = 0; i < node->voice_count; i++) {
            AXSetVoicePriority(node->voice[i], prio);
        }
    }
}

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

static inline void updateAllVolume(u32 mask)
{
    int i;
    HSD_Synth_804D7758 |= mask;
    for (i = 0; i < 0x40; i++) {
        struct HSD_SynthSFXNode* node = &hsd_SynthSFXNodes[i];
        if (node->x0 > 0 && ((1 << node->xB) & mask)) {
            HSD_SynthSFXUpdateVolume(node);
        }
    }
}

void HSD_SynthSFXUpdateAllVolume(int arg0, u16 arg1, int arg2)
{
    HSD_Synth_804C28E0_1784[arg2].x1788 = 1 / 255.0F * arg0;
    if (HSD_Synth_804C28E0_1784[arg2].x1784 !=
        HSD_Synth_804C28E0_1784[arg2].x1788)
    {
        HSD_Synth_804C28E0_1784[arg2].x178C = arg1;
        updateAllVolume(1 << arg2);
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
        hsd_SynthSFXNodes[node->voice[j]->index].x0 = 0;
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
        struct HSD_SynthSFXNode* node = &hsd_SynthSFXNodes[base + i];
        if (node->x0 > 0) {
            if (!(node->flags & 8) && node->voice[0]->pb.state == 0 &&
                (node->voice_count == 1 || node->voice[1]->pb.state == 0))
            {
                HSD_SynthSFXStopNode(node);
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

void HSD_SynthResetStreamCounters(void)
{
    HSD_Synth_804D776C = HSD_Synth_804D7768;
    HSD_Synth_804D7778 = 0;
}

/// #HSD_Synth_8038AD74

/// #HSD_Synth_8038ADD0(void)

/// #HSD_Synth_8038B120

/// #HSD_SynthPStreamFirstHakoHeaderCallback

/// #HSD_SynthPStreamHeaderCallback

/// #HSD_Synth_8038B5AC

void HSD_SynthStreamSetVolume(f32 arg0)
{
    HSD_Synth_804D6030 = arg0;
    AISetStreamVolLeft(HSD_Synth_804D6030 * (f32) HSD_Synth_804D777C);
    AISetStreamVolRight(HSD_Synth_804D6030 * (f32) HSD_Synth_804D777C);
    updateAllVolume(0xFFFF);
} /// #HSD_SynthInit
