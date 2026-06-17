#include "synth.h"

#include "synth.static.h"

#include <math_ppc.h>
#include <dolphin/ai.h>
#include <dolphin/ar.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>

/* 389334 */ static int HSD_Synth_80389334(int sfx_id, u8 vol, u8 vol2, u8 pan,
                                           int priority, u8 itd_flag,
                                           float pitch1, float pitch2,
                                           float mix_main, float mix_auxA,
                                           float mix_auxB);

void* HSD_AudioMalloc(size_t size)
{
    void* p = OSAllocFromHeap(HSD_Synth_804D6018, size);
    HSD_ASSERTREPORT(0x29U, p, "audio heap overflow.\n");
    return p;
}

void HSD_AudioFree(void* ptr)
{
    OSFreeToHeap(HSD_Synth_804D6018, ptr);
}

extern void* HSD_Synth_804D7730;
extern u32* HSD_Synth_804D7734;

struct SfxLoadStreamNode {
    /* 0x00 */ struct SfxLoadStreamNode* x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
};

void HSD_SynthSFXSampleLoadCallback(int result, int length, void* addr,
                                    int cancelflag)
{
    BOOL intr;
    s32 i;

    if (HSD_Synth_804D7738 == 0) {
        int bankID = HSD_Synth_804C2A60[0].bankID;
        u32* buf = (u32*) HSD_Synth_804D7730;
        u32 data_bytes = hsd_SynthSFXLoadBuf[0] - 0x10;
        s32 src_idx = (data_bytes >> 2) - 1;
        u32 total =
            (hsd_SynthSFXLoadBuf[2] * 8 + hsd_SynthSFXLoadBuf[0] + 0x37) &
            ~0x1F;
        u32 shift = (total - data_bytes) >> 2;
        u32 dnw;
        AXVPB** pp;
        struct SfxLoadStreamNode* node;
        u8* cur;
        s32 count;
        s32 base;
        s32 bank2;

        for (i = src_idx; i >= 0; i--) {
            buf[i + shift] = buf[i];
        }
        dnw = (total - hsd_SynthSFXLoadBuf[0]) >> 2;
        buf[dnw] = hsd_SynthSFXLoadBuf[4];
        buf[dnw + 1] = hsd_SynthSFXLoadBuf[5];
        buf[dnw + 2] = hsd_SynthSFXLoadBuf[6];
        buf[dnw + 3] = hsd_SynthSFXLoadBuf[7];
        HSD_Synth_804D7734 = &buf[dnw];

        pp = &HSD_Synth_804C2AE0[bankID];
        while (*pp != NULL) {
            pp = &(*pp)->next;
        }
        *pp = (AXVPB*) buf;

        node = (struct SfxLoadStreamNode*) buf;
        node->x0 = NULL;
        node->x4 = HSD_Synth_804C2A60[0].entrynum;
        node->x10 = hsd_SynthSFXBank[bankID];
        node->x14 = hsd_SynthSFXLoadBuf[1];
        count = hsd_SynthSFXLoadBuf[2];
        base = hsd_SynthSFXLoadBuf[3];
        node->x8 = base;
        node->xC = count;
        bank2 = hsd_SynthSFXBank[bankID] * 2;

        cur = (u8*) buf + 0x18;
        for (i = 0; i < count; i++) {
            s32 n = *HSD_Synth_804D7734;
            s32 nbytes = (n << 6) + 8;
            s32 k;
            s32 id;
            struct SfxLoadStreamNode* nn;
            void** bucket;

            memcpy(cur + 8, HSD_Synth_804D7734, nbytes);
            for (k = 0; k < n; k++) {
                u8* e = cur + k * 0x40;
                if (*(u32*) (e + 0x10) != 0) {
                    *(u32*) (e + 0x14) += bank2;
                } else {
                    *(u32*) (e + 0x14) = HSD_Synth_804D7784;
                }
                *(u32*) (e + 0x18) += bank2;
                *(u32*) (e + 0x1C) += bank2;
            }
            nn = (struct SfxLoadStreamNode*) cur;
            id = base + i;
            nn->x4 = id;
            bucket = &HSD_Synth_804C29E0[id & 0x1F];
            nn->x0 = (struct SfxLoadStreamNode*) *bucket;
            *bucket = nn;
            HSD_Synth_804D7734 += ((u32) nbytes & ~3) >> 2;
            cur += ((n << 6) + 0x10) & ~3;
        }
        if (HSD_Synth_804C2A60[0].x8 != 0) {
            ((void (*)(s32, s32)) HSD_Synth_804C2A60[0].x8)(
                HSD_Synth_804C2A60[0].entrynum, HSD_Synth_804C2A60[0].xC);
        }
        hsd_SynthSFXBank[bankID] += hsd_SynthSFXLoadBuf[1];
    } else {
        if (HSD_Synth_804D7730 != NULL) {
            OSFreeToHeap(HSD_Synth_804D6018, HSD_Synth_804D7730);
        }
        HSD_Synth_804D7738 = 0;
    }
    intr = OSDisableInterrupts();
    HSD_Synth_804D772C -= 1;
    for (i = 0; i < HSD_Synth_804D772C; i++) {
        HSD_Synth_804C2A60[i] = HSD_Synth_804C2A60[i + 1];
    }
    HSD_SynthSFXLoadNewProc();
    OSRestoreInterrupts(intr);
}

static void HSD_SynthSFXHeaderLoadCallback(int result, int length, void* addr,
                                           int cancelflag)
{
    AXVPB** unused;
    s32 header_size;
    void* p;
    size_t alloc_size;

    if (HSD_Synth_804D7738 == 0) {
        int bankID = HSD_Synth_804C2A60[0].bankID;

        HSD_ASSERTREPORT(0xCD,
                         hsd_SynthSFXBankHead[bankID + 1] -
                                 hsd_SynthSFXBank[bankID] >=
                             hsd_SynthSFXLoadBuf[1],
                         "Can't load SFX file; bank(id=%d) buffer overflow.\n",
                         HSD_Synth_804C2A60[0].bankID);

        alloc_size = hsd_SynthSFXLoadBuf[2] * 8 + 0x18;
        header_size = hsd_SynthSFXLoadBuf[0];
        p = OSAllocFromHeap(HSD_Synth_804D6018,
                            OSRoundUp32B(alloc_size + header_size));
        HSD_ASSERTREPORT(0x29U, p, "audio heap overflow.\n");
        HSD_Synth_804D7730 = p;
        HSD_Synth_804D6028[1] = HSD_DevComRequest(
            HSD_Synth_804C2A60[0].entrynum, 0x20, (u32) HSD_Synth_804D7730,
            OSRoundUp32B(header_size - 0x10), 0x21, 1, NULL, NULL);
        HSD_Synth_804D6028[0] = HSD_DevComRequest(
            HSD_Synth_804C2A60[0].entrynum, OSRoundUp32B(header_size + 0x10),
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

int HSD_SynthSFXLoad(const char* filename, int bankID, int flags, int mode)
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
    HSD_Synth_804C2A60[HSD_Synth_804D772C].x8 = flags;
    HSD_Synth_804C2A60[HSD_Synth_804D772C].xC = mode;
    HSD_Synth_804D772C += 1;

    if (HSD_Synth_804D772C == 1) {
        HSD_SynthSFXLoadNewProc();
    }

    OSRestoreInterrupts(enabled);
    return entrynum;
}

void HSD_SynthSFXWaitForLoadCompletion(void (*callback)(void))
{
    while (HSD_Synth_804D772C != 0) {
        callback();
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

void HSD_SynthSFXAllocateBank(int size)
{
    int base = hsd_SynthSFXBankHead[hsd_SynthSFXBankNum];

    hsd_SynthSFXBank[hsd_SynthSFXBankNum] = base;
    hsd_SynthSFXBankHead[hsd_SynthSFXBankNum + 1] = size + base;

    HSD_ASSERTREPORT(0x158,
                     hsd_SynthSFXBankHead[hsd_SynthSFXBankNum + 1] <=
                         hsd_SynthSFXBankAREnd,
                     "bank overflow\n");
    hsd_SynthSFXBankNum += 1;
}

u8 data_pad[0x2C] = { 0 };

static inline void HSD_SynthSFXUnloadBank_inline(AXVPB* vpb)
{
    int i;
    for (i = 0; i < vpb->priority; i++) {
        HSD_Synth_80388DC8((int) vpb->next1 + i);
    }
}

void HSD_SynthSFXUnloadBank(int bank_id)
{
    AXVPB** head;
    HSD_SynthSFXStopRange(bank_id);
    head = &HSD_Synth_804C2AE0[bank_id];
    while (*head != NULL) {
        AXVPB* cur;
        HSD_SynthSFXUnloadBank_inline(*head);
        cur = *head;
        *head = (*head)->next;
        HSD_AudioFree(cur);
    }
    hsd_SynthSFXBank[bank_id] = hsd_SynthSFXBankHead[bank_id];
}

void HSD_Synth_80388DC8(int sfx_id)
{
    void* cur;
    void** pcur = &HSD_Synth_804C29E0[sfx_id & 0x1F];

    while ((cur = *pcur) != NULL) {
        if (((int*) cur)[1] == sfx_id) {
            *pcur = *(void**) cur;
            return;
        }
        pcur = (void**) cur;
    }
}

void HSD_Synth_80388E08(int sfx_id)
{
    AXVPB* cur;
    AXVPB** pcur;
    int i;

    for (i = 0; i < 0x20; i++) {
        pcur = &HSD_Synth_804C2AE0[i];
        while (*pcur != NULL) {
            cur = *pcur;
            /// @todo AXVPB prev must be a signed int type, not a pointer
            if ((int) cur->prev == sfx_id) {
                HSD_SynthSFXUnloadBank_inline(cur);
                *pcur = cur->next;
                OSFreeToHeap(HSD_Synth_804D6018, cur);
                return;
            }
            pcur = &cur->next;
        }
    }
}

static void HSD_SynthSFXGroupDataReaddressCallback(void* result, int length,
                                                   void* addr, int cancelflag)
{
    HSD_ASSERT(0x182, sfxGroupDataReaddressCounter > 0);
    sfxGroupDataReaddressCounter--;
}

u8 data_pad_2[0x84] = { 0 };

void HSD_SynthSFXGroupDataReaddress(AXVPB* arg0, void* callback)
{
    u8* q;
    int i;
    int count;
    int delta;
    u8* p;
    int j;

    p = (u8*) arg0 + 0x18;
    sfxGroupDataReaddressCounter += 1;
    HSD_DevComRequest(
        0, (uintptr_t) arg0->callback, (uintptr_t) callback, arg0->userContext,
        0x1B, 0,
        (HSD_DevComCallback) (Event) HSD_SynthSFXGroupDataReaddressCallback,
        NULL);
    i = 0;
    delta = ((u8*) callback - (u8*) arg0->callback) * 2;
    while (i < arg0->priority) {
        count = *(int*) (p + 8);
        q = p;
        for (j = 0; j < count; j++) {
            if (*(u16*) (q + 0x10) != 0) {
                *(u32*) (q + 0x14) += delta;
            }
            *(u32*) (q + 0x18) += delta;
            *(u32*) (q + 0x1C) += delta;
            q += 0x40;
        }
        p = (u8*) ((count << 6) + (uintptr_t) p);
        p += 0x10;
        i++;
    }
    arg0->callback = (void (*)(void*)) callback;
}

void HSD_SynthSFXBankDeflag(int bank_id)
{
    AXVPB* vpb;
    intptr_t offset;

    HSD_SynthSFXStopRange(bank_id);
    vpb = HSD_Synth_804C2AE0[bank_id];
    offset = hsd_SynthSFXBankHead[bank_id];
    while (vpb != NULL) {
        if ((intptr_t) vpb->callback != offset) {
            HSD_SynthSFXGroupDataReaddress(vpb, (void*) offset);
        }
        offset += vpb->userContext;
        vpb = vpb->next;
    }
    HSD_Synth_804C2AE0[bank_id + 0x80 / 4] = (void*) offset;
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

/// @todo Currently ~90% match - second loop uses pointer arithmetic instead of
/// indexed store (stwx). Stack frame is 8 bytes too large.
void dropcallback(void* dropped)
{
    AXVPB* voice = dropped;
    struct HSD_SynthSFXNode* node;
    bool enabled;
    int i;

    PAD_STACK(0x10);

    enabled = OSDisableInterrupts();

    node = &hsd_SynthSFXNodes[voice->index];

    /// Search HSD_Synth_804C28E0 queue for this voice and remove it
    for (i = 0; i < HSD_Synth_804D7720; i++) {
        if (HSD_Synth_804C28E0[i] == voice) {
            HSD_Synth_804C28E0[i] = NULL;
            break;
        }
    }

    if (node->x0 == 0) {
        OSRestoreInterrupts(enabled);
        return;
    }

    if (node->x0 == -1) {
        /// Secondary voice - follow to primary node
        node = &hsd_SynthSFXNodes[node->voice[0]->index];
    }

    if (!(node->flags & 1) && node->x27 == 1 &&
        driverInactivatedCallback != NULL)
    {
        driverInactivatedCallback(node->x0);
    }

    {
        struct HSD_SynthSFXNode* walk = node;
        int j;
        for (j = 0; j < node->voice_count; j++) {
            AXVPB* v = walk->voice[0];
            if (v != voice) {
                int idx = HSD_Synth_804D7720;
                HSD_Synth_804D7720 = idx + 1;
                HSD_Synth_804C28E0[idx] = v;
            }
            hsd_SynthSFXNodes[walk->voice[0]->index].x0 = 0;
            walk = (void*) ((u8*) walk + 4);
        }
    }

    OSRestoreInterrupts(enabled);
}

static AXPBMIX lbl_80407FB4 = { 0 };

static AXPBSRC HSD_Synth_80407FD8 = { 1, 0, 0, { 0, 0, 0, 0 } };

/// @todo Currently 95.4% match - register allocation shifted by 1
/// (r29 reuse for loop counter and computation missing)
int HSD_Synth_80389334(int sfx_id, u8 vol, u8 vol2, u8 pan, int priority,
                       u8 itd_flag, float pitch1, float pitch2, float mix_main,
                       float mix_auxA, float mix_auxB)
{
    AXVPB* voices[2] = { NULL, NULL };
    AXPBVE ve;
    float vol_norm;
    float vol2_norm;
    int voice_idx;
    u32 node_idx;
    int loop_idx;
    struct foo {
        void* next;
        int unk4; // sound ID
        int unk8; // voice count
        int unkC; // audio parameter
        AXPBADDR x10;
        AXPBADPCM x20;
        AXPBADPCMLOOP x48;
    }* sfx_entry;
    struct HSD_SynthSFXNode* sfx_node;
    int saved_interrupts;
    AXVPB** voice_ptr;
    struct foo* sample_data;

    PAD_STACK(0x1C);

    saved_interrupts = OSDisableInterrupts();
    sfx_entry = HSD_Synth_804C29E0[sfx_id & 0x1F];

    while (sfx_entry != NULL) {
        if (sfx_entry->unk4 == sfx_id) {
            voice_idx = 0;
            while (voice_idx < sfx_entry->unk8) {
                voices[voice_idx] =
                    AXAcquireVoice(priority + 1, dropcallback, 0U);
                if (voices[voice_idx] == NULL) {
                    if (voices[0] != NULL) {
                        AXFreeVoice(voices[0]);
                    }
                    OSRestoreInterrupts(saved_interrupts);
                    return -1;
                }
                voice_idx += 1;
            }
            if ((sfx_entry->unk8 == 2) && (voices[0] == voices[1])) {
                AXFreeVoice(voices[0]);
                OSRestoreInterrupts(saved_interrupts);
                return -1;
            }
            if (sfx_entry->unk8 == 2) {
                hsd_SynthSFXNodes[voices[1]->index].x0 = -1;
                hsd_SynthSFXNodes[voices[1]->index].voice[0] = voices[0];
            }

            node_idx = voices[0]->index;

            sfx_node = &hsd_SynthSFXNodes[node_idx];
            sfx_node->x27 = 1;
            sfx_node->x0 = sfx_id;
            sfx_node->flags = 0;
            sfx_node->voice_count = sfx_entry->unk8;
            sfx_node->xB = itd_flag;
            sfx_node->voice[0] = voices[0];
            sfx_node->voice[1] = voices[1];
            sfx_node->x14 = 0.00003125F * sfx_entry->unkC;
            sfx_node->x18[0] = pitch1;
            sfx_node->x18[1] = pitch2;
            vol_norm = 1 / 255.0F * vol;
            vol2_norm = 1 / 255.0F * vol2;
            sfx_node->unk28 = vol_norm;
            sfx_node->user_vol[0].volume = vol_norm;
            sfx_node->user_vol[0].x4 = 0;
            sfx_node->user_vol[0].x8_float = vol2_norm;
            sfx_node->user_vol[1].volume = vol2_norm;
            sfx_node->user_vol[1].x4 = 0;
            sfx_node->user_vol[1].x8 = pan;
            sfx_node->x44 = mix_main;
            sfx_node->x48 = mix_auxA;
            sfx_node->x4C = mix_auxB;
            HSD_SynthSFXUpdateVolume(sfx_node);
            HSD_SynthSFXUpdateMix(sfx_node, 0);
            ve.currentVolume =
                (32767.0F * (sfx_node->user_vol[0].x8_float *
                             (sfx_node->unk28 *
                              (HSD_Synth_804D6030 *
                               HSD_Synth_804C28E0_1784[sfx_node->xB].x1784))));
            ve.currentDelta = 0;
            sfx_node->x24 = ve.currentVolume;

            sample_data = (void*) ((u8*) sfx_entry + 0x40 * vol);
            voice_ptr = &voices[vol];
            loop_idx = 0;
            while (loop_idx < sfx_entry->unk8) {
                AXSetVoicePriority(*voice_ptr, priority);
                AXSetVoiceVe(*voice_ptr, &ve);
                /// @todo Type pun writes ratioHi+ratioLo as u32; no union in
                /// AXPBSRC. Needed for match - AXPBSRC lacks a u32 ratio
                /// field.
                *(u32*) &HSD_Synth_80407FD8.ratioHi =
                    (65536.0F *
                     (sfx_node->x18[1] * (sfx_node->x14 * sfx_node->x18[0])));
                AXSetVoiceSrc(*voice_ptr, &HSD_Synth_80407FD8);
                AXSetVoiceAddr(*voice_ptr, &sample_data->x10);
                AXSetVoiceAdpcm(*voice_ptr, &sample_data->x20);
                AXSetVoiceAdpcmLoop(*voice_ptr, &sample_data->x48);
                AXSetVoiceState(*voice_ptr, 1U);
                voice_ptr += 1;
                sample_data =
                    (void*) ((u8*) sample_data +
                             0x40); ///< @todo what is going on here...
                loop_idx += 1;
            }
            HSD_Synth_804D7750 += 0x40;
            if (HSD_Synth_804D7750 < 0) {
                HSD_Synth_804D7750 = 0x40;
            }
            sfx_node->x0 = HSD_Synth_804D7750 + node_idx;
            OSRestoreInterrupts(saved_interrupts);
            return sfx_node->x0;
        }
        sfx_entry = sfx_entry->next;
    }

    OSRestoreInterrupts(saved_interrupts);
    return -1;
}

static inline struct HSD_SynthSFXNode* getNode(int sfx_id)
{
    struct HSD_SynthSFXNode* node = &hsd_SynthSFXNodes[sfx_id & 0x3F];
    if (sfx_id > 0 && node->x0 == sfx_id) {
        return node;
    } else {
        return NULL;
    }
}

bool HSD_SynthSFXPlayWithGroup(int sfx_id, u8 vol, u8 vol2, u8 pan,
                               int priority, u8 itd_flag, int group,
                               f32 pitch1, f32 pitch2, f32 mix_main,
                               f32 mix_auxA, f32 mix_auxB)
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

    result = HSD_Synth_80389334(sfx_id, vol, vol2, pan, priority, itd_flag,
                                pitch1, pitch2, mix_main, mix_auxA, mix_auxB);
    HSD_Synth_804C28E0_1844[group] = result;
    return result;
}

static inline void freeVoices(struct HSD_SynthSFXNode* node)
{
    int j;
    for (j = 0; j < node->voice_count; j++) {
        AXFreeVoice(node->voice[j]);
        hsd_SynthSFXNodes[node->voice[j]->index].x0 = 0;
    }
}

void HSD_SynthSFXKeyOff(int id)
{
    struct HSD_SynthSFXNode* node;
    int i;

    PAD_STACK(0x10);

    if ((node = getNode(id))) {
        if (node->flags & 8) {
            if (!(node->flags & 1) && node->x27 == 1 &&
                driverInactivatedCallback != NULL)
            {
                driverInactivatedCallback(node->x0);
            }
            freeVoices(node);
        } else if (!(node->flags & 1)) {
            node->flags |= 1;
            HSD_SynthSFXUpdateVolume(node);
            for (i = 0; i < node->voice_count; i++) {
                AXSetVoicePriority(node->voice[i], 1U);
            }
        }
    }
}

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

void HSD_SynthSFXStopRange(int bank_id)
{
    stopRange(hsd_SynthSFXBankHead[bank_id + 0] * 2,
              hsd_SynthSFXBankHead[bank_id + 1] * 2);
}

void HSD_SynthSFXPause(int sfx_id)
{
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(sfx_id))) {
        node->flags |= 2;
        HSD_SynthSFXUpdateVolume(node);
        if (node->flags & 8) {
            node->flags |= 6;
        }
    }
}

void HSD_SynthSFXResume(int sfx_id)
{
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(sfx_id))) {
        if (node->flags & 2) {
            node->flags &= ~6;
            HSD_SynthSFXUpdatePitch(node);
            HSD_SynthSFXUpdateVolume(node);
        }
    }
}

int HSD_SynthSFXCheck(int sfx_id)
{
    struct HSD_SynthSFXNode* node = getNode(sfx_id);
    int i;

    if (node != NULL) {
        if (node->flags & 1) {
            return -1;
        }
        for (i = 0; i < node->voice_count; i++) {
            if (node->voice[i]->pb.state == 0) {
                return -1;
            }
        }
        return sfx_id;
    }
    return -1;
}

void HSD_SynthSFXSetVolumeFade(int sfx_id, u8 vol, int flag)
{
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(sfx_id))) {
        HSD_ASSERT(0x376, flag >= 0 && flag < USERVOL_NUM);
        node->user_vol[flag].volume = 1 / 255.0 * vol;
        node->user_vol[flag].x4 = 1;
        HSD_SynthSFXUpdateVolume(node);
    }
}

void HSD_SynthSFXSetUserVol(int sfx_id, u8 vol)
{
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(sfx_id))) {
        node->user_vol[1].x8 = vol;
        HSD_SynthSFXUpdateMix(node, 1);
    }
}

void HSD_SynthSFXSetMix(int sfx_id, float mix_main, float mix_auxA,
                        float mix_auxB)
{
    int* unused;
    struct HSD_SynthSFXNode* node;

    if ((node = getNode(sfx_id))) {
        node->x44 = mix_main;
        node->x48 = mix_auxA;
        node->x4C = mix_auxB;
        HSD_SynthSFXUpdateMix(node, 1);
    }
}

void HSD_SynthSFXUpdatePitch(struct HSD_SynthSFXNode* node)
{
    float ratio;

    if (node->flags & 4) {
        ratio = 0.0F;
    } else {
        ratio = node->x14 * node->x18[0] * node->x18[1];
    }
    if (!(node->flags & 8)) {
        int i;
        for (i = 0; i < node->voice_count; i++) {
            AXSetVoiceSrcRatio(node->voice[i], ratio);
        }
    }
}

void HSD_SynthSFXSetPitchRatio(int sfx_id, int flag, float ratio)
{
    struct HSD_SynthSFXNode* node = getNode(sfx_id);

    if (node != NULL && !(node->flags & 1)) {
        HSD_ASSERT(0x3A7, flag == 0 || flag == 1);

        node->x18[flag] = ratio;

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

s32 HSD_Synth_8038A000(void)
{
    BOOL intr;
    int i;
    struct HSD_SynthSFXNode* node;
    struct HSD_SynthSFXNode** pnode;

    intr = OSDisableInterrupts();
    if (HSD_Synth_804D7758 != 0) {
        int ch;
        for (ch = 0; ch < 16; ch++) {
            int mask = 1 << ch;
            if (HSD_Synth_804D7758 & mask) {
                int cnt = HSD_Synth_804C28E0_1784[ch].x178C;
                if (cnt != 0) {
                    HSD_Synth_804C28E0_1784[ch].x1784 =
                        (HSD_Synth_804C28E0_1784[ch].x1784 *
                         ((f32) cnt - 1.0f)) /
                            (f32) cnt +
                        HSD_Synth_804C28E0_1784[ch].x1788 / (f32) cnt;
                    HSD_Synth_804C28E0_1784[ch].x178C -= 1;
                }
                if (HSD_Synth_804C28E0_1784[ch].x178C == 0) {
                    HSD_Synth_804C28E0_1784[ch].x1784 =
                        HSD_Synth_804C28E0_1784[ch].x1788;
                    HSD_Synth_804D7758 &= ~mask;
                }
            }
        }
    }
    pnode = &HSD_Synth_804D774C;
    while ((node = *pnode) != NULL) {
        int active = 0;
        s16 vol;
        s32 delta;

        if (node->x0 <= 0) {
            node->volume_update_pending = 0;
            *pnode = node->x20;
            continue;
        }
        if (node->user_vol[0].x4 != 0) {
            int c = node->user_vol[0].x4;
            node->unk28 = (node->unk28 * ((f32) c - 1.0f)) / (f32) c +
                          node->user_vol[0].volume / (f32) c;
            node->user_vol[0].x4 -= 1;
            if (node->user_vol[0].x4 != 0) {
                active = 1;
            }
        }
        if (node->user_vol[1].x4 != 0) {
            int c = node->user_vol[1].x4;
            node->user_vol[0].x8_float =
                (node->user_vol[0].x8_float * ((f32) c - 1.0f)) / (f32) c +
                node->user_vol[1].volume / (f32) c;
            node->user_vol[1].x4 -= 1;
            if (node->user_vol[1].x4 != 0) {
                active = 1;
            }
        }
        if (HSD_Synth_804C28E0_1784[node->xB].x178C != 0) {
            active = 1;
        }
        if (!(node->flags & 3)) {
            vol = (s16) (32767.0f *
                         (node->user_vol[0].x8_float *
                          (node->unk28 *
                           (HSD_Synth_804D6030 *
                            HSD_Synth_804C28E0_1784[node->xB].x1784))));
        } else {
            vol = 0;
            active = 0;
        }
        delta = (vol - node->x24) / 160;
        if (delta > 0x14) {
            delta = 0x14;
        } else if (delta < -0x14) {
            delta = -0x14;
        }
        for (i = 0; i < node->voice_count; i++) {
            AXSetVoiceVeDelta(node->voice[i], (s16) delta);
        }
        node->x24 += delta * 0xA0;
        if (delta == 0 && (active == 0 || (f32) vol == 0.0f)) {
            AXPBVE ve;
            node->x24 = (u16) vol;
            ve.currentVolume = vol;
            ve.currentDelta = 0;
            for (i = 0; i < node->voice_count; i++) {
                node->voice[i]->sync &= 0xFFFFFBFF;
                AXSetVoiceVe(node->voice[i], &ve);
            }
            if (active == 0) {
                u8 flags;
                node->volume_update_pending = 0;
                *pnode = node->x20;
                flags = node->flags;
                if (flags & 1) {
                    for (i = 0; i < node->voice_count; i++) {
                        AXFreeVoice(node->voice[i]);
                        hsd_SynthSFXNodes[node->voice[i]->index].x0 = 0;
                    }
                } else if ((flags & 6) == 2) {
                    node->flags = flags | 6;
                    for (i = 0; i < node->voice_count; i++) {
                        f32 ratio;
                        u8 flags2 = node->flags;
                        if (flags2 & 4) {
                            ratio = 0.0f;
                        } else {
                            ratio = node->x18[1] * (node->x14 * node->x18[0]);
                        }
                        if (!(flags2 & 8)) {
                            int j;
                            for (j = 0; j < node->voice_count; j++) {
                                AXSetVoiceSrcRatio(node->voice[j], ratio);
                            }
                        }
                    }
                    if (driverPauseCallback != NULL && node->x27 == 1) {
                        driverPauseCallback(node->x0);
                    }
                }
                continue;
            }
        }
        pnode = &node->x20;
    }
    return OSRestoreInterrupts(intr);
}

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

static u8 lbl_8040806C[] = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04,
    0x05, 0x05, 0x06, 0x06, 0x07, 0x07, 0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A,
    0x0B, 0x0B, 0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0E, 0x0F, 0x0F, 0x10, 0x10,
    0x11, 0x11, 0x12, 0x12, 0x13, 0x13, 0x14, 0x14, 0x15, 0x15, 0x16, 0x16,
    0x16, 0x17, 0x17, 0x17, 0x17, 0x18, 0x18, 0x18, 0x18, 0x19, 0x19, 0x19,
    0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B,
    0x1B, 0x1B, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1D,
    0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1E, 0x1E, 0x1E, 0x1E,
    0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
};

static inline void my_memzero(void* dst_raw, size_t size)
{
    int i;
    int* dst = dst_raw;
    for (i = 0; i < size; i += 4) {
        *dst++ = 0;
    }
}

void HSD_SynthSFXUpdateMix(struct HSD_SynthSFXNode* node, int interpolate)
{
    int i;
    int shiftL;
    int shiftR;

    f32 l;
    f32 r;

    if (HSD_Synth_804D7754 != 0) {
        l = 32767.0F *
            sqrtf_accurate(0.003921569F * (0xFF - node->user_vol[1].x8));
        r = 32767.0F * sqrtf_accurate(0.003921569F * node->user_vol[1].x8);
    } else {
        l = 23169.768F;
        r = 23169.768F;
    }
    if (node->voice_count == 1) {
        lbl_80407FB4.vL = l * node->x44;
        lbl_80407FB4.vR = r * node->x44;
        lbl_80407FB4.vAuxAL = l * node->x48;
        lbl_80407FB4.vAuxAR = r * node->x48;
        lbl_80407FB4.vAuxBL = l * node->x4C;
        lbl_80407FB4.vAuxBR = r * node->x4C;
        AXSetVoiceMix(node->voice[0], &lbl_80407FB4);
    } else if (HSD_Synth_804D7754 != 0) {
        lbl_80407FB4.vL = l * node->x44;
        lbl_80407FB4.vAuxAL = l * node->x48;
        lbl_80407FB4.vAuxBL = l * node->x4C;
        AXSetVoiceMix(node->voice[0], &lbl_80407FB4);
        lbl_80407FB4.vAuxBL = 0;
        lbl_80407FB4.vAuxAL = 0;
        lbl_80407FB4.vL = 0;
        lbl_80407FB4.vR = r * node->x44;
        lbl_80407FB4.vAuxAR = r * node->x48;
        lbl_80407FB4.vAuxBR = r * node->x4C;
        AXSetVoiceMix(node->voice[1], &lbl_80407FB4);
    } else {
        l /= 2;
        lbl_80407FB4.vL = l * node->x44;
        lbl_80407FB4.vR = l * node->x44;
        lbl_80407FB4.vAuxAL = l * node->x48;
        lbl_80407FB4.vAuxAR = l * node->x48;
        lbl_80407FB4.vAuxBL = l * node->x4C;
        lbl_80407FB4.vAuxBR = l * node->x4C;
        AXSetVoiceMix(node->voice[0], &lbl_80407FB4);
        AXSetVoiceMix(node->voice[1], &lbl_80407FB4);
    }

    my_memzero(&lbl_80407FB4, sizeof(lbl_80407FB4));

    shiftL = 0;
    shiftR = 0;
    if (HSD_Synth_804D7754 != 0) {
        if (node->user_vol[1].x8 < 0x80) {
            shiftL = lbl_8040806C[0x7F - node->user_vol[1].x8];
        } else {
            shiftR = lbl_8040806C[node->user_vol[1].x8 - 0x80];
        }
    }
    for (i = 0; i < node->voice_count; i++) {
        if (shiftL != 0 || shiftR != 0 || node->voice[0]->pb.itd.flag == 1) {
            if (node->voice[i]->pb.itd.flag == 0 ||
                (node->voice[i]->sync & 0x20))
            {
                AXSetVoiceItdOn(node->voice[i]);
                if (interpolate == 0) {
                    node->voice[i]->pb.itd.shiftR = shiftR;
                    node->voice[i]->pb.itd.shiftL = shiftL;
                }
                node->voice[i]->pb.itd.targetShiftR = shiftR;
                node->voice[i]->pb.itd.targetShiftL = shiftL;
            } else {
                AXSetVoiceItdTarget(node->voice[i], shiftL, shiftR);
            }
        }
    }
}

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

void HSD_SynthSFXUpdateAllVolume(int vol, u16 fade_frames, int channel)
{
    HSD_Synth_804C28E0_1784[channel].x1788 = 1 / 255.0F * vol;
    if (HSD_Synth_804C28E0_1784[channel].x1784 !=
        HSD_Synth_804C28E0_1784[channel].x1788)
    {
        HSD_Synth_804C28E0_1784[channel].x178C = fade_frames;
        updateAllVolume(1 << channel);
    }
}

void HSD_SynthSFXSetDriverInactivatedCallback(UNK_T callback)
{
    driverInactivatedCallback = callback;
}

void HSD_SynthSFXSetDriverMasterClockCallback(UNK_T callback)
{
    driverMasterClockCallback = callback;
}

void HSD_SynthSFXSetDriverPauseCallback(void (*callback)(s32))
{
    driverPauseCallback = callback;
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

void HSD_SynthResetStreamCounters(int result, int length, void* buf, bool b)
{
    HSD_Synth_804D776C = HSD_Synth_804D7768;
    HSD_Synth_804D7778 = 0;
}

extern s32 HSD_Synth_804D7764;

void HSD_Synth_8038AD74(u32 offset, uintptr_t src)
{
    HSD_DevComRequest(HSD_Synth_804D7764, src,
                      HSD_Synth_804D7780 + ((u32) HSD_Synth_804D7768 << 16),
                      lbl_804C4540[HSD_Synth_804D7768].x0, 0x23, 0,
                      HSD_SynthResetStreamCounters, 0);
}

extern s32 HSD_Synth_804D7764;
extern u32 HSD_Synth_804D7770;
extern u32 HSD_Synth_804D7774;

void HSD_Synth_8038ADD0(void)
{
    struct HSD_SynthSFXNode* node = getNode(HSD_Synth_804D7760);
    u32 pos;
    s32 i;
    BOOL intr;
    s32 src;

    if (node == NULL) {
        return;
    }
    if (node->flags & 8) {
        return;
    }
    pos = (u32) (*(u32*) ((u8*) node->voice[0] + 0x1B2) -
                 HSD_Synth_804D7780 * 2) >>
          0x11;
    if (pos != HSD_Synth_804D7774) {
        HSD_Synth_804D7774 = pos;
        for (i = 0; i < node->voice_count; i++) {
            AXSetVoiceEndAddr(
                node->voice[i],
                (HSD_Synth_804D7780 + (HSD_Synth_804D7774 << 0x10)) * 2 +
                    (i * lbl_804C4540[HSD_Synth_804D7774].x0 +
                     lbl_804C4540[HSD_Synth_804D7774].x4));
        }
    }
    if (pos == HSD_Synth_804D7770 && pos != HSD_Synth_804D776C) {
        if (lbl_804C4540[HSD_Synth_804D7770].x8 == -0x10001) {
            HSD_Synth_804D7770 = (HSD_Synth_804D7770 + 1) % 3;
            for (i = 0; i < node->voice_count; i++) {
                AXSetVoiceLoop(node->voice[i], 0);
                AXSetVoiceLoopAddr(node->voice[i], HSD_Synth_804D7784);
            }
        } else {
            HSD_Synth_804D7770 = (HSD_Synth_804D7770 + 1) % 3;
            for (i = 0; i < node->voice_count; i++) {
                AXSetVoiceLoopAddr(
                    node->voice[i],
                    (HSD_Synth_804D7780 + (HSD_Synth_804D7770 << 0x10)) * 2 +
                        (i * lbl_804C4540[HSD_Synth_804D7770].x0 + 2));
                AXSetVoiceAdpcmLoop(
                    node->voice[i],
                    (AXPBADPCMLOOP*) ((u32*) &lbl_804C4540
                                          [HSD_Synth_804D7770] +
                                      (i * 2 + 3)));
            }
        }
    }
    if ((s32) ((HSD_Synth_804D776C + 1) % 3) != pos) {
        intr = OSDisableInterrupts();
        if (HSD_Synth_804D7778 != 0 ||
            HSD_Synth_804D7768 != HSD_Synth_804D776C)
        {
            OSRestoreInterrupts(intr);
            return;
        }
        if (getNode(HSD_Synth_804D7760) != NULL) {
            src = lbl_804C4540[HSD_Synth_804D776C].x8;
            if (src == -1) {
                HSD_Synth_804D776C = (HSD_Synth_804D776C + 1) % 3;
            } else {
                HSD_Synth_804D7768 = (HSD_Synth_804D776C + 1) % 3;
                HSD_Synth_804D7778 = 1;
                HSD_DevComRequest(
                    HSD_Synth_804D7764, src,
                    (uintptr_t) &lbl_804C4540[HSD_Synth_804D7768], 0x20, 0x21,
                    0, (HSD_DevComCallback) (Event) HSD_Synth_8038AD74,
                    (void*) (src + 0x20));
            }
        }
        OSRestoreInterrupts(intr);
    }
}

void HSD_Synth_8038B120(void)
{
    AXPBVE ve;
    int i;
    bool enabled;
    struct HSD_SynthSFXNode* node;

    PAD_STACK(0x10);

    node = getNode(HSD_Synth_804D7760);
    if (node != NULL) {
        if (!(node->flags & 2)) {
            ve.currentVolume =
                (32767.0F *
                 (node->user_vol[0].x8_float *
                  (node->unk28 * (HSD_Synth_804D6030 *
                                  HSD_Synth_804C28E0_1784[node->xB].x1784))));
        } else {
            ve.currentVolume = 0;
        }
        ve.currentDelta = 0;
        node->x24 = ve.currentVolume;
        for (i = 0; i < node->voice_count; i++) {
            AXSetVoiceVe(node->voice[i], &ve);
            if (node->flags & 4) {
                *(u32*) &HSD_Synth_80407FD8.ratioHi = 0;
            } else {
                *(u32*) &HSD_Synth_80407FD8.ratioHi =
                    (u32) (65536.0F *
                           (node->x14 * node->x18[0] * node->x18[1]));
            }
            AXSetVoiceSrc(node->voice[i], &HSD_Synth_80407FD8);
            AXSetVoiceCurrentAddr(
                node->voice[i],
                (HSD_Synth_804D7780 + ((u32) HSD_Synth_804D7768 << 16)) * 2 +
                    i * lbl_804C4540[HSD_Synth_804D7768].x0 + 2);
            AXSetVoiceEndAddr(
                node->voice[i],
                (HSD_Synth_804D7780 + ((u32) HSD_Synth_804D7768 << 16)) * 2 +
                    i * lbl_804C4540[HSD_Synth_804D7768].x0 +
                    lbl_804C4540[HSD_Synth_804D7768].x4);
            AXSetVoiceLoopAddr(
                node->voice[i],
                (HSD_Synth_804D7780 + ((u32) HSD_Synth_804D7768 << 16)) * 2 +
                    i * lbl_804C4540[HSD_Synth_804D7768].x0 + 2);
            AXSetVoiceState(node->voice[i], 1);
        }
        node->flags &= ~8;
        enabled = OSDisableInterrupts();
        if (!node->volume_update_pending && !(node->flags & 8)) {
            node->volume_update_pending = 1;
            node->x20 = HSD_Synth_804D774C;
            HSD_Synth_804D774C = node;
        }
        OSRestoreInterrupts(enabled);
        HSD_SynthSFXUpdateMix(node, 0);
        HSD_Synth_804D7778 = 0;
    } else {
        HSD_Synth_804D7778 = 0;
    }
}

void HSD_SynthPStreamFirstHakoHeaderCallback(void)
{
    HSD_DevComRequest(HSD_Synth_804D7764, 0xA0,
                      HSD_Synth_804D7780 + ((u32) HSD_Synth_804D7768 << 16),
                      lbl_804C4540[HSD_Synth_804D7768].x0, 0x23, 0,
                      (HSD_DevComCallback) HSD_Synth_8038B120, 0);
}

extern u32 HSD_Synth_804D7770;
extern u32 HSD_Synth_804D7774;

void HSD_SynthPStreamHeaderCallback(int arg0, int arg1, void* arg2,
                                    int cancelflag)
{
    u32* entry = arg2;
    struct HSD_SynthSFXNode* node;
    int i;

    node = getNode(HSD_Synth_804D7760);
    if (node != NULL) {
        node->voice_count = entry[3];
        if (node->voice_count == 2) {
            node->voice[1] = AXAcquireVoice(0x1D, dropcallback, 0);
            HSD_ASSERTMSG(0x5CF, node->voice[1], "entry->voice[1]");
        }
        node->x14 = 0.00003125f * (f32) entry[2];
        for (i = 0; i < node->voice_count; i++) {
            *(u32*) &HSD_Synth_80407FD8.ratioHi = (u32) (65536.0f * node->x14);
            AXSetVoiceAddr(node->voice[i], (AXPBADDR*) &entry[i * 14 + 4]);
            AXSetVoiceAdpcm(node->voice[i], (AXPBADPCM*) &entry[i * 14 + 8]);
        }
        HSD_Synth_804D7774 = (HSD_Synth_804D7774 + 2) % 3;
        HSD_Synth_804D776C = HSD_Synth_804D7770 = HSD_Synth_804D7768 =
            HSD_Synth_804D7774;
        HSD_DevComRequest(
            HSD_Synth_804D7764, 0x80,
            (uintptr_t) &lbl_804C4540[HSD_Synth_804D7768], 0x20, 0x21, 0,
            (HSD_DevComCallback) HSD_SynthPStreamFirstHakoHeaderCallback,
            NULL);
    } else {
        HSD_Synth_804D7778 = 0;
    }
}

static inline void HSD_Synth_8038B5AC_inline(void)
{
    struct HSD_SynthSFXNode* node = getNode(HSD_Synth_804D7760);
    int i;
    int saved_interrupts;

    if (!node) {
        return;
    }

    if (node->flags & 8) {
        HSD_SynthSFXStopNode(node);
    } else if (!(node->flags & 1)) {
        node->flags |= 1;
        saved_interrupts = OSDisableInterrupts();
        if (node->volume_update_pending == 0 && !(node->flags & 8)) {
            node->volume_update_pending = 1;
            node->x20 = HSD_Synth_804D774C;
            HSD_Synth_804D774C = node;
        }
        OSRestoreInterrupts(saved_interrupts);
        for (i = 0; i < node->voice_count; i++) {
            AXSetVoicePriority(node->voice[i], 1);
        }
    }
}

int HSD_Synth_8038B5AC(int entrynum, u8 vol, u8 vol2, int channel)
{
    bool enabled;

    struct HSD_SynthSFXNode* voice_node;
    int idx;
    AXVPB* voice;

    PAD_STACK(8);

    do {
    } while (HSD_Synth_804D7778 != 0);

    HSD_Synth_804D7778 = 1;
    enabled = OSDisableInterrupts();

    if (getNode(HSD_Synth_804D7760) != NULL) {
        HSD_Synth_8038B5AC_inline();
    }
    HSD_Synth_804D7764 = entrynum;
    voice = AXAcquireVoice(0x1D, dropcallback, 0);
    idx = voice->index;
    voice_node = &hsd_SynthSFXNodes[idx];
    HSD_Synth_804D7750 += 0x40;
    if (HSD_Synth_804D7750 < 0) {
        HSD_Synth_804D7750 = 0x40;
    }
    voice_node->x27 = 2;
    voice_node->x0 = HSD_Synth_804D7760 = HSD_Synth_804D7750 + idx;
    voice_node->next = NULL;
    voice_node->flags = 8;
    voice_node->voice_count = 1;
    voice_node->xB = (u8) channel;
    voice_node->voice[0] = voice;
    voice_node->x18[0] = 1.0F;
    voice_node->x18[1] = 1.0F;
    voice_node->unk28 = 0.003921569F * vol;
    voice_node->user_vol[0].volume = 0.003921569F * vol;
    voice_node->user_vol[0].x4 = 0;
    voice_node->user_vol[0].x8_float = 0.003921569F * vol2;
    voice_node->user_vol[1].volume = 0.003921569F * vol2;
    voice_node->user_vol[1].x4 = 0;
    voice_node->user_vol[1].x8 = 0x80;
    voice_node->x44 = 1.0F;
    voice_node->x48 = 0.0F;
    voice_node->x4C = 0.0F;
    HSD_DevComRequest(entrynum, 0, 0, 0x80, 0x22, 1,
                      HSD_SynthPStreamHeaderCallback, NULL);
    OSRestoreInterrupts(enabled);
    return HSD_Synth_804D7760;
}

void HSD_SynthStreamSetVolume(f32 volume)
{
    HSD_Synth_804D6030 = volume;
    AISetStreamVolLeft(HSD_Synth_804D6030 * (f32) HSD_Synth_804D777C);
    AISetStreamVolRight(HSD_Synth_804D6030 * (f32) HSD_Synth_804D777C);
    updateAllVolume(0xFFFF);
}

void HSD_SynthInit(int dsp_size, int voices, int stream_size, int bank_size)
{
    AXInit();
    AISetDSPSampleRate(0);
    HSD_Synth_804D7784 = ARAlloc(0x500);
    HSD_DevComRequest(0, 0, HSD_Synth_804D7784, 0x500, 3, 0, 0, 0);
    HSD_Synth_804D7784 *= 2;
    hsd_SynthSFXBankHead[0] = ARAlloc(bank_size);
    AXRegisterCallback(HSD_SynthCallback);
    HSD_Synth_804D777C = 0xFF;
    AISetStreamVolLeft(HSD_Synth_804D6030 * (f32) HSD_Synth_804D777C);
    AISetStreamVolRight(HSD_Synth_804D6030 * (f32) HSD_Synth_804D777C);
    /// Loop unrolled to match original binary (loop version adds 8 bytes
    /// to stack frame due to compiler allocating space for the counter)
    HSD_Synth_804C28E0_1784[0].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[0].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[0].x178C = 0;
    HSD_Synth_804C28E0_1784[1].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[1].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[1].x178C = 0;
    HSD_Synth_804C28E0_1784[2].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[2].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[2].x178C = 0;
    HSD_Synth_804C28E0_1784[3].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[3].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[3].x178C = 0;
    HSD_Synth_804C28E0_1784[4].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[4].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[4].x178C = 0;
    HSD_Synth_804C28E0_1784[5].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[5].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[5].x178C = 0;
    HSD_Synth_804C28E0_1784[6].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[6].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[6].x178C = 0;
    HSD_Synth_804C28E0_1784[7].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[7].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[7].x178C = 0;
    HSD_Synth_804C28E0_1784[8].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[8].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[8].x178C = 0;
    HSD_Synth_804C28E0_1784[9].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[9].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[9].x178C = 0;
    HSD_Synth_804C28E0_1784[10].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[10].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[10].x178C = 0;
    HSD_Synth_804C28E0_1784[11].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[11].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[11].x178C = 0;
    HSD_Synth_804C28E0_1784[12].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[12].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[12].x178C = 0;
    HSD_Synth_804C28E0_1784[13].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[13].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[13].x178C = 0;
    HSD_Synth_804C28E0_1784[14].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[14].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[14].x178C = 0;
    HSD_Synth_804C28E0_1784[15].x1784 = 1.0F;
    HSD_Synth_804C28E0_1784[15].x1788 = 1.0F;
    HSD_Synth_804C28E0_1784[15].x178C = 0;
    hsd_SynthSFXBankAREnd = hsd_SynthSFXBankHead[0] + bank_size;
    HSD_Synth_804D7780 = ARAlloc(0x30000);
    HSD_Synth_804D7754 = OSGetSoundMode();
}
