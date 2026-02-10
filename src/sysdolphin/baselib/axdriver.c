#include "axdriver.h"

#include "axdriver.static.h"

#include <math_ppc.h>
#include <string.h>
#include <dolphin/axfx.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/axdriver.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/synth.h>

typedef struct {
    s32 v[8];
} RevHiDims;

void* AXDriverAlloc(size_t size)
{
    void* ptr = &AXDriver_804D77D4[axfxallocsize];

    // increment the size by the amount we will be indexing to.
    axfxallocsize += size;

    // size exceeds the max allowed; the pointer that we return would be
    // outside the heap. Raise an assert.
    HSD_ASSERT(78, axfxallocsize < axfxmaxsize);
    return ptr;
}

void AXDriverFree(void* ptr) {}

void AXDriverUnlink(HSD_SM* v, HSD_SM** head)
{
    HSD_SM* p;
    HSD_SM* n;

    if (v != NULL) {
        p = v->prev;
        n = v->next;
        v->next = NULL;
        v->prev = NULL;
        if (p != NULL) {
            p->next = n;
        }
        if (n != NULL) {
            n->prev = p;
        }
        if (*head == v) {
            *head = n;
        }
        HSD_ASSERT(113, *head != v);
    }
}

static void unk_inline(HSD_SM* v, HSD_SM** head)
{
    if (v == NULL) {
        return;
    }

    HSD_ASSERT(0x7A, *head != v);

    v->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = v;
    }
    v->next = *head;
    *head = v;
}

static bool tmp(HSD_SM* v)
{
    int idx;
    HSD_ASSERT(0x92, (v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE ||
                     (v->flags&SMSTATE_MASK) == SMSTATE_SLEEP);

    idx = v->vID;
    if (v->vID != -1) {
        AXDriver_804C5920[idx & 0x3F] = 0;
        v->vID = -1;
        HSD_SynthSFXKeyOff(idx);
        AXDriver_804D77C8--;
    }

    v->flags &= ~0x20000000;
    v->flags &= ~SMSTATE_MASK;
    return true;
}

bool AXDriverKeyOff(int vid)
{
    bool result;
    int idx;
    HSD_SM* v;
    bool enabled;
    PAD_STACK(8);

    idx = vid & 0x7F;
    if (vid < 0 || idx >= 0x60) {
        return false;
    }

    enabled = OSDisableInterrupts();
    v = &AXDriver_804C45A0[idx];

    if (v->unk != vid || !(v->flags & SMSTATE_MASK)) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    if (v == NULL) {
        result = false;
    } else {
        result = tmp(v);
    }

    OSRestoreInterrupts(enabled);
    return result;
}

void HSD_AudioSFXKeyOffAll(void)
{
    bool enabled = OSDisableInterrupts();
    HSD_SM* v = AXDriver_804D7794;
    PAD_STACK(8);

    while (v != NULL) {
        if (v->flags & SMSTATE_MASK) {
            if (v != NULL) {
                tmp(v);
            }
        }
        v = v->next;
    }
    OSRestoreInterrupts(enabled);
}

void HSD_AudioSFXKeyOffTrack(int track)
{
    bool enabled = OSDisableInterrupts();
    HSD_SM* v = AXDriver_804D7794;

    while (v != NULL) {
        if ((v->flags & SMSTATE_MASK) && v->track == track) {
            if (v != NULL) {
                tmp(v);
            }
        }
        v = v->next;
    }
    OSRestoreInterrupts(enabled);
}

/// unused function to force data ordering for this assert string
static void unused(HSD_SM* v)
{
    HSD_ASSERT(__LINE__, (v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE);
}

u32 AXDriver_8038C678(u32 param_type, u32 param_value)
{
    switch (param_type) {
    case 0:
        return param_value & 0xFFFFFF;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 14:
    case 15:
    case 20:
    case 21:
        return false;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 16:
    case 17:
    case 18:
    case 19:
        return param_value >> 8 & 0xFFFF;
    case 12:
    case 13:
        return param_value >> 16 & 0xFF;
    default:
        return false;
    }
}

void AXDriver_8038BF6C(HSD_SM* v)
{
    int flag;
    int i;

    for (i = 0; i <= 9; i++) {
        flag = 1 << i;

        if (v->flags & flag) {
            switch (flag) {
            case 0x1: {
                float left_vol = (v->x26 * v->x24[0]) / 65535.0F;
                float right_vol = (v->x27 * v->x24[1]) / 65535.0F;
                float left_sqrt = sqrtf(left_vol);
                float left_inv_sqrt = sqrtf(1.0F - left_vol);
                float right_sqrt = sqrtf(right_vol);
                float right_inv_sqrt = sqrtf(1.0F - right_vol);
                float tmp2 = left_inv_sqrt * right_sqrt;
                float pitch1 = powf(2.0F, v->x20 / 1200.0F);
                float pitch2 = powf(2.0F, v->fadetime / 1200.0F);

                v->vID = HSD_SynthSFXPlayWithGroup(
                    v->fid, v->x1A, v->volume,
                    (v->flags & 0x20000) ? v->pan : v->x1C, v->pri, v->itdflag,
                    v->track, pitch1, pitch2, left_inv_sqrt * tmp2, left_sqrt,
                    left_inv_sqrt * right_inv_sqrt);

                if (v->vID != -1) {
                    AXDriver_804C5920[v->vID & 0x3F] = v;
                    v->flags &= 0xFFF4FF99;
                    if (v->flags & 0x40000) {
                        v->flags &= ~0x40000;
                    }
                    AXDriver_804D77C8++;
                } else {
                    HSD_ASSERT(0x13B,
                             (v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE);
                    v->flags &= ~SMSTATE_MASK;
                    return;
                }
                break;
            }
            case 0x2:
                HSD_SynthSFXSetPriority(v->vID, v->pri);
                break;
            case 0x4:
                HSD_SynthSFXSetVolumeFade(v->vID, v->x1A, 0);
                break;
            case 0x8:
                HSD_SynthSFXSetUserVol(v->vID, v->x1C);
                break;
            case 0x10:
                break;
            case 0x20:
                HSD_SynthSFXSetPitchRatio(v->vID, 0,
                                          powf(2.0F, v->x20 / 1200.0F));
                break;
            case 0x40:
                HSD_SynthSFXSetPitchRatio(v->vID, 1,
                                          powf(2.0F, v->fadetime / 1200.0F));
                break;
            case 0x80: {
                float left_vol = (v->x26 * v->x24[0]) / 65535.0F;
                float right_vol = (v->x27 * v->x24[1]) / 65535.0F;
                float left_sqrt = sqrtf(left_vol);
                float left_inv_sqrt = sqrtf(1.0F - left_vol);
                float right_sqrt = sqrtf(right_vol);
                float right_inv_sqrt = sqrtf(1.0F - right_vol);

                HSD_SynthSFXSetMix(
                    v->vID, left_inv_sqrt * left_inv_sqrt * right_inv_sqrt,
                    left_sqrt, right_sqrt * left_inv_sqrt);
                break;
            }
            case 0x100:
                v->flags = (v->flags & ~SMSTATE_MASK) | SMSTATE_SLEEP;
                return;
            case 0x200:
                if (v != NULL) {
                    tmp(v);
                }
                return;
            }
        }

        v->flags &= ~flag;
    }
}

#define MIN2(x, y) ((x) < (y) ? (x) : (y))
#define MAX2(x, y) ((x) < (y) ? (y) : (x))
#define CLAMP(min, val, max) MAX2(MIN2(val, max), min)

void AXDriver_8038C6C0(HSD_SM* v)
{
    u32 cmd_type;
    u32 cmd_word;
    int cmd_size;
    PAD_STACK(8);

    while (v->x30 == (s32) AXDriver_804D778C) {
        cmd_word = *(u32*) v->cmd_stream;
        cmd_type = cmd_word >> 0x18U;

        cmd_size = AXDriver_8038C678(cmd_type, cmd_word);
        if (cmd_size != 0) {
            AXDriver_8038BF6C(v);
        }
        v->x30 += cmd_size;
        switch (cmd_type) {
        case 2:
            v->x2A = *(u32*) v->cmd_stream;
            if (v->x2A == 0) {
                v->flags |= 0x100000;
            }
            break;
        case 3:
            if ((v->flags & 0x100000) || v->x2A != 0) {
                v->cmd_stream -= *v->cmd_stream;
                v->x2A--;
            }
            break;
        case 1:
            v->flags |= 1;
            v->fid = *v->cmd_stream;
            break;
        case 4:
            v->flags |= 2;
            v->pri = *v->cmd_stream;
            break;
        case 5:
            v->flags |= 2;
            v->pri = CLAMP(5, v->pri + (s8) (u8) *v->cmd_stream, 0x1C);
            break;
        case 6:
            v->flags |= 4;
            v->x1A = *(u32*) v->cmd_stream;
            break;
        case 7:
            v->flags |= 4;
            v->x1A = CLAMP(0, v->x1A + (s8) (u8) *v->cmd_stream, 0xFF);
            break;
        case 8:
            v->flags |= 8;
            v->x1C = *(u32*) v->cmd_stream;
            break;
        case 9:
            v->flags |= 8;
            v->x1C = CLAMP(0, v->x1C + (s8) (u8) *v->cmd_stream, 0xFF);
            break;
        case 10:
            v->flags |= 0x10;
            v->x1E = *(u32*) v->cmd_stream;
            break;
        case 11:
            v->flags |= 0x10;
            v->x1E = CLAMP(0, v->x1E + (s8) (u8) *v->cmd_stream, 0xFF);
            break;
        case 12:
            v->flags |= 0x20;
            v->x20 = (s16) (u16) *v->cmd_stream;
            break;
        case 13:
            v->flags |= 0x20;
            v->x20 =
                CLAMP(-0x2A30, v->x20 + (s16) (u16) *v->cmd_stream, 0x960);
            break;
        case 16:
            if (!(AXDriver_804D603C & 1)) {
                v->flags |= 0x80;
                v->x24[0] = *v->cmd_stream;
            }
            break;
        case 20:
            if (!(AXDriver_804D603C & 1)) {
                v->x26 = *v->cmd_stream;
            }
            break;
        case 21:
            if (!((AXDriver_804D603C >> 1U) & 1)) {
                v->x27 = *v->cmd_stream;
            }
            break;
        case 17:
            if (!(AXDriver_804D603C & 1)) {
                v->flags |= 0x80;
                v->x24[0] =
                    CLAMP(0, v->x24[0] + (s8) (u8) *v->cmd_stream, 0xFF);
            }
            break;
        case 18:
            if (!(((u32) AXDriver_804D603C >> 1U) & 1)) {
                v->flags |= 0x80;
                v->x24[1] = *v->cmd_stream;
            }
            break;
        case 19:
            if (!(AXDriver_804D603C >> 1 & 1)) {
                v->flags |= 0x80;
                v->x24[1] =
                    CLAMP(0, v->x24[1] + (s8) (u8) *v->cmd_stream, 0xFF);
            }
            break;
        case 15:
            v->flags |= 0x200;
            AXDriver_8038BF6C(v);
            return;
        case 14:
            v->flags |= 0x100;
            AXDriver_8038BF6C(v);
            return;
        }
        v->cmd_stream++;
    }
}

static void fn_8038CC1C(void)
{
    HSD_SM* v;
    HSD_SM* next;
    PAD_STACK(4);

    if (AXDriver_804D77E0 != 0) {
        AXDriver_804D77E0 = 0;
        if (AXDriver_804D6038 != -1) {
            float x =
                powf(2.0F, CLAMP(-0x2A30, AXDriver_804D77E4, 0x960) / 1200.0F);
            HSD_SynthSFXSetPitchRatio(AXDriver_804D6038, 1, x);
        }
    }
    v = AXDriver_804D7794;
    AXDriver_804D778C++;
    while (v != NULL) {
        next = v->next;
        if (v->x30 == -1) {
            v->x30 = AXDriver_804D778C;
        } else if (v->flags & 0x20000000) {
            v->x30++;
        }
        switch (v->flags & SMSTATE_MASK) {
        case SMSTATE_ACTIVE:
            if (v->x30 == AXDriver_804D778C) {
                AXDriver_8038C6C0(v);
            }
            break;
        case 0:
            AXDriverUnlink(v, &AXDriver_804D7794);
            unk_inline(v, &AXDriver_804D7790);
            AXDriver_804D77D0--;
            break;
        case SMSTATE_SLEEP:
            if (v->flags & 0x40) {
                float x = powf(2.0F, v->fadetime / 1200.0F);
                HSD_SynthSFXSetPitchRatio(v->vID, 1, x);
                v->flags &= 0xFFFFFFBF;
            }
            break;
        default:
            HSD_ASSERT(0x25F, 0);
            break;
        }
        v = next;
    }
}

static void fn_8038CEA4(s32 vID)
{
    HSD_SM* v;
    int idx = vID & 0x3F;

    if (vID <= 0) {
        __assert("axdriver.c", 0x26D, "vID > 0");
    }

    v = AXDriver_804C5920[idx];
    if (v == NULL || v->vID != vID) {
        return;
    }

    AXDriver_804C5920[idx] = NULL;
    v->flags &= ~0x20000000;
    v->flags &= ~SMSTATE_MASK;
    AXDriver_804D77C8--;
}

static void fn_8038CF48(s32 vID)
{
    HSD_SM* v;
    int idx;
    idx = vID & 0x3F;

    HSD_ASSERT(0x288, vID > 0);

    v = AXDriver_804C5920[idx];
    HSD_ASSERT(0x28A, v && v->vID == vID);

    v->flags |= 0x20000000;
}

static inline HSD_SM* AXDriver_8038CFF4_inline(void)
{
    if (AXDriver_804D7790 == NULL) {
        return NULL;
    } else {
        HSD_SM* v;
        bool enabled = OSDisableInterrupts();
        v = AXDriver_804D7790;
        AXDriverUnlink(v, &AXDriver_804D7790);
        OSRestoreInterrupts(enabled);
        v->vID = -1;
        v->x30 = -1;
        v->flags = 0;
        v->flags &= ~SMSTATE_MASK;
        return v;
    }
}

int AXDriver_8038CFF4(int sound_id, u8 volume, u8 pan, int track, int channel)
{
    HSD_SM* v;
    int sample_idx;
    int bank_idx;
    int bank_mem;
    bool enabled;

    bank_idx = sound_id / 10000;
    bank_mem = sound_id % 10000;

    if (AXDriver_804D77B0 <= bank_idx) {
        return -1;
    }

    sample_idx = bank_mem + AXDriver_804D77B4[bank_idx];

    if (AXDriver_804D77B8 <= sample_idx) {
        return -1;
    }

    if (bank_idx < AXDriver_804D77B0 - 1 &&
        AXDriver_804D77B4[bank_idx + 1] <= sample_idx)
    {
        return -1;
    }

    if (track < 0 || track > 0xFF) {
        return -1;
    }

    if (channel < 0 || channel >= 0x10) {
        return -1;
    }

    if (AXDriver_804D77CC & (1 << channel)) {
        return -1;
    }

    v = AXDriver_8038CFF4_inline();

    if (v == NULL) {
        return -1;
    }

    v->x16 = sound_id;
    v->cmd_stream = AXDriver_804D77BC[sample_idx];
    v->x1A = 0xFF;
    v->volume = volume;
    v->x1C = 0x80;
    v->pan = pan;
    v->x20 = 0;
    v->fadetime = 0;
    v->x24[0] = AXDriver_804C5A20[0][channel];
    v->x24[1] = AXDriver_804C5A20[1][channel];
    v->x26 = 0xFF;
    v->x27 = 0xFF;
    v->pri = 5;
    v->track = track;
    v->itdflag = channel;
    v->flags |= 0x30000;

    if (vidhigh & 0xFE000000) {
        OSReport("vidhigh exceeds the max value\n");
        HSD_ASSERT(0x2EA, 0);
    }

    v->unk =
        (vidhigh << 7) | ((u8*) v - (u8*) AXDriver_804C45A0) / sizeof(HSD_SM);
    vidhigh++;

    enabled = OSDisableInterrupts();
    v->flags = (v->flags & ~SMSTATE_MASK) | SMSTATE_ACTIVE;
    unk_inline(v, &AXDriver_804D7790);
    AXDriver_804D77D0++;
    OSRestoreInterrupts(enabled);

    return v->unk;
}

bool AXDriver_8038D2B4(int vid, u8 pan)
{
    int idx;
    bool enabled;
    HSD_SM* v;
    u8 clamped;

    idx = vid & 0x7F;
    if (vid < 0 || idx >= 0x60) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & SMSTATE_MASK)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    if (v->vID != -1) {
        HSD_SynthSFXSetUserVol(v->vID, MIN(pan, 0xFF));
    } else {
        HSD_ASSERT(0x30B, (v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE);
        v->pan = pan;
        v->flags |= 0x20000;
    }
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038D3B8(s32 vid, u8 volume)
{
    HSD_SM* v;
    s32 idx;
    bool enabled;
    s32 voice_id;

    idx = vid & 0x7F;
    if (vid < 0 || idx >= 0x60) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & SMSTATE_MASK)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    voice_id = v->vID;
    if (voice_id != -1) {
        HSD_SynthSFXSetVolumeFade(voice_id, CLAMP(0, volume, 0xFF), 1);
    } else {
        HSD_ASSERT(0x34D, (v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE);
        v->volume = volume;
        v->flags |= 0x10000;
    }
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038D4E4(s32 vid, s16 pitch)
{
    HSD_SM* v;
    s32 idx;
    bool enabled;
    int clamped;

    idx = vid & 0x7F;
    if (vid < 0 || idx >= 0x60) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & SMSTATE_MASK)) {
        return false;
    }
    clamped = CLAMP(-0x2A30, pitch, 0x960);
    enabled = OSDisableInterrupts();
    v->fadetime = clamped;
    v->flags |= 0x40;
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038D5B4(s32 vid, s32 aux_bus, u8 send_level)
{
    HSD_SM* v;
    float right_vol;
    float left_vol;
    float left_inv_sqrt;
    float left_sqrt;
    float right_sqrt;
    float right_inv_sqrt;
    bool enabled;
    int idx;
    int lock_flag;
    int unused;
    int clamped;

    idx = vid & 0x7F;
    if (vid < 0 || idx >= 0x60) {
        return false;
    }
    if (aux_bus < 0 || aux_bus > 1) {
        return false;
    }
    if (aux_bus == 0) {
        lock_flag = AXDriver_804D603C & 1;
    } else {
        lock_flag = (AXDriver_804D603C >> 1) & 1;
    }
    if (lock_flag != 1) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & SMSTATE_MASK)) {
        return false;
    }
    clamped = CLAMP(0, send_level, 0xFF);
    enabled = OSDisableInterrupts();
    if (v->vID != -1) {
        v->x24[aux_bus] = clamped;
        left_vol = (f32) (v->x26 * v->x24[0]) / 65535.0F;
        right_vol = (f32) (v->x27 * v->x24[1]) / 65535.0F;
        left_sqrt = sqrtf(left_vol);
        left_inv_sqrt = sqrtf(1.0F - left_vol);
        right_sqrt = sqrtf(right_vol);
        right_inv_sqrt = sqrtf(1.0F - right_vol);
        HSD_SynthSFXSetMix(v->vID,
                           left_inv_sqrt * (left_inv_sqrt * right_inv_sqrt),
                           left_sqrt, right_sqrt * left_inv_sqrt);
    } else {
        HSD_ASSERT(0x3AB, (v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE);
        v->x24[aux_bus] = clamped;
        v->flags |= 0x80000;
    }
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038D914(s32 channel, s32 aux_bus, s8 send_level)
{
    bool enabled;
    HSD_SM* v;

    if (channel < 0 || channel >= 0x10) {
        return false;
    }
    if (aux_bus < 0 || aux_bus > 1) {
        return false;
    }
    enabled = OSDisableInterrupts();
    v = AXDriver_804D7794;
    while (v != NULL) {
        if ((v->flags & SMSTATE_MASK) && v->itdflag == channel) {
            AXDriver_8038D5B4(v->unk, aux_bus, (u8) send_level);
        }
        v = v->next;
    }
    AXDriver_804C5A20[aux_bus][channel] = send_level;
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038D9D8(int vid)
{
    HSD_SM* v;
    int idx;

    idx = vid & 0x7F;
    if (vid < 0 || idx >= 0x60) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & SMSTATE_MASK)) {
        return false;
    }
    if (HSD_SynthSFXCheck(v->vID) == -1) {
        return false;
    }
    return true;
}

static void fn_8038DA5C(s32 result, DVDFileInfo* fileInfo)
{
    if (result != -1) {
        AXDriver_804D77EC = 1;
    }
}

/// @@todo: Currently 97.58% match - register allocation in section 1 and 2
/// parsing blocks (r0/r3 swap for count/ptr, r4/r5 swap for base pointer)
void AXDriver_8038DA70(const char* path, void (*callback)(void))
{
    DVDFileInfo fileInfo;
    s32 entrynum;
    s32 alignedSize;
    void* ptr;
    s32 offset;
    s32 j;
    s32 i;

    entrynum = DVDConvertPathToEntrynum(path);
    if (entrynum == -1 || DVDFastOpen(entrynum, &fileInfo) == 0) {
        OSReport("can not open %s\n", path);
        return;
    }

    AXDriver_804D779C = fileInfo.length;
    if (AXDriver_804D779C == 0) {
        OSReport("file size of \"%s\" is 0\n", path);
        return;
    }

    alignedSize = (AXDriver_804D779C + 0x1F) & ~0x1F;
    AXDriver_804D7798 = HSD_AudioMalloc(alignedSize);
    AXDriver_804D77EC = 0;
    DVDReadAsyncPrio(&fileInfo, AXDriver_804D7798, alignedSize, 0,
                     fn_8038DA5C, 2);

    while (AXDriver_804D77EC == 0) {
        callback();
    }

    DVDClose(&fileInfo);

    AXDriver_804D77A0 = ((s32*)AXDriver_804D7798)[0];
    if (AXDriver_804D77A0 != 0) {
        ptr = (void*)((u8*)AXDriver_804D7798 + 4);
    } else {
        ptr = NULL;
    }
    offset = AXDriver_804D77A0 * 4 + 4;
    AXDriver_804D77A4 = ptr;

    AXDriver_804D77A8 = *(s32*)((u8*)AXDriver_804D7798 + offset);
    offset += 4;
    if (AXDriver_804D77A8 != 0) {
        ptr = (u8*)AXDriver_804D7798 + offset;
    } else {
        ptr = NULL;
    }
    AXDriver_804D77AC = ptr;

    j = 0;
    i = 0;
    while (i < AXDriver_804D77A8) {
        i++;
        *(u32*)((u8*)AXDriver_804D77AC + j) +=
            (u32)AXDriver_804D7798 & ~3u;
        j += 4;
    }

    offset += AXDriver_804D77A8 * 4;
    AXDriver_804D77B0 = *(s32*)((u8*)AXDriver_804D7798 + offset);
    offset += 4;
    if (AXDriver_804D77B0 != 0) {
        ptr = (u8*)AXDriver_804D7798 + offset;
    } else {
        ptr = NULL;
    }
    offset += AXDriver_804D77B0 * 4;
    AXDriver_804D77B4 = ptr;

    AXDriver_804D77B8 = *(s32*)((u8*)AXDriver_804D7798 + offset);
    offset += 4;
    if (AXDriver_804D77B8 != 0) {
        ptr = (u8*)AXDriver_804D7798 + offset;
    } else {
        ptr = NULL;
    }
    AXDriver_804D77BC = ptr;
    i = 0;
    j = i;
    while (i < AXDriver_804D77B8) {
        i++;
        *(u32*)((u8*)AXDriver_804D77BC + j) +=
            (u32)AXDriver_804D7798 & ~3u;
        j += 4;
    }

    offset += AXDriver_804D77B8 * 4;
    AXDriver_804D77C0 = *(s32*)((u8*)AXDriver_804D7798 + offset);
    offset += 4;
    if (AXDriver_804D77C0 != 0) {
        ptr = (u8*)AXDriver_804D7798 + offset;
    } else {
        ptr = NULL;
    }
    AXDriver_804D77C4 = ptr;
    i = 0;
    j = i;
    while (i < AXDriver_804D77C0) {
        i++;
        *(u32*)((u8*)AXDriver_804D77C4 + j) +=
            (u32)AXDriver_804D7798 & ~3u;
        j += 4;
    }
}

void AXDriver_8038DCFC(void)
{
    if (AXDriver_804D7798 != NULL) {
        HSD_AudioFree(AXDriver_804D7798);
    }
    AXDriver_804D7798 = NULL;
}

int AXDriverSetupAux(int channel, AXDriverAuxType type, void* param)
{
    struct AXFX_REVERBHI* aux_data_hi;
    struct AXFX_REVERBSTD* aux_data_std;
    struct AXFX_CHORUS* aux_data_chorus;
    struct AXFX_DELAY* aux_data_delay;

    int old_type;
    int result;
    void* callback;
    void* callback_data;

    aux_data_hi = &AXDriver_804C5A40[channel];
    aux_data_std = &AXDriver_804C5E00[channel];
    aux_data_chorus = &AXDriver_804C60A8[channel];
    aux_data_delay = &AXDriver_804C61E0[channel];

    result = 0;
    callback = NULL;
    callback_data = NULL;

    // Validate aux channel (0 or 1)
    HSD_ASSERT(0x49C, channel == 0 || channel == 1);

    // Validate effect type (0-4)
    HSD_ASSERT(0x49D, 0 <= type && type <= 4);

    // Validate param pointer when effect type is not 0 (off)
    HSD_ASSERT(0x49E, type == 0 || param != NULL);

    // Get old effect type and update with new type
    if (channel == 0) {
        old_type = AXDriver_804D603C >> 8 & 0xF;
        AXDriver_804D603C &= ~(old_type << 8);
        AXDriver_804D603C |= (type << 8);
        AXRegisterAuxACallback(NULL, NULL);
    } else {
        old_type = AXDriver_804D603C >> 12 & 0xF;
        AXDriver_804D603C &= ~(old_type << 12);
        AXDriver_804D603C |= (type << 12);
        AXRegisterAuxBCallback(NULL, NULL);
    }

    // Shutdown old effect
    switch (old_type) {
    case AXDRIVER_AUX_REVERB_HI:
        AXFXReverbHiShutdown(aux_data_hi);
        break;
    case AXDRIVER_AUX_REVERB_STD:
        AXFXReverbStdShutdown(aux_data_std);
        break;
    case AXDRIVER_AUX_CHORUS:
        AXFXChorusShutdown(aux_data_chorus);
        break;
    case AXDRIVER_AUX_DELAY:
        AXFXDelayShutdown(aux_data_delay);
        break;
    }

    // Initialize new effect
    switch (type) {
    case AXDRIVER_AUX_OFF:
        result = 1;
        break;
    case AXDRIVER_AUX_REVERB_HI:
        memcpy(aux_data_hi, param, sizeof(struct AXFX_REVERBHI));
        if (AXFXReverbHiInit(aux_data_hi) == 1) {
            callback = AXFXReverbHiCallback;
            callback_data = aux_data_hi;
            result = 1;
        }
        break;
    case AXDRIVER_AUX_REVERB_STD:
        memcpy(aux_data_std, param, sizeof(struct AXFX_REVERBSTD));
        if (AXFXReverbStdInit(aux_data_std) == 1) {
            callback = AXFXReverbStdCallback;
            callback_data = aux_data_std;
            result = 1;
        }
        break;
    case AXDRIVER_AUX_CHORUS:
        memcpy(aux_data_chorus, param, sizeof(struct AXFX_CHORUS));
        if (AXFXChorusInit(aux_data_chorus) == 1) {
            callback = AXFXChorusCallback;
            callback_data = aux_data_chorus;
            result = 1;
        }
        break;
    case AXDRIVER_AUX_DELAY:
        memcpy(aux_data_delay, param, sizeof(struct AXFX_DELAY));
        if (AXFXDelayInit(aux_data_delay) == 1) {
            callback = AXFXDelayCallback;
            callback_data = aux_data_delay;
            result = 1;
        }
        break;
    }

    // Register new effect callback
    if (channel == 0) {
        AXRegisterAuxACallback(callback, callback_data);
    } else {
        AXRegisterAuxBCallback(callback, callback_data);
    }

    return result;
}

static const RevHiDims revhi_dims = {
    { 0x6FD, 0x7CF, 0x91D, 0x1B1, 0x95, 0x2F, 0x49, 0x43 },
};

static const s32 revstd_dims[] = {
    0x6FD, 0x7CF, 0x1B1, 0x95,
};

/// @@todo: Currently 53.61% match - needs struct copy and computation order fixes
s32 AXDriver_8038E034(AXDriverAuxType type, void* param)
{
    s32 result;
    s32 d[8];
    s32 predelay;
    s32 s0, s1, s2, s3, s4, s5;

    result = 0;

    if (type < 0 || type > 4 || (type != 0 && param == NULL)) {
        return 0;
    }

    switch (type) {
    case AXDRIVER_AUX_OFF:
        break;

    case AXDRIVER_AUX_REVERB_HI:
    {
        RevHiDims tmp;

        tmp = revhi_dims;
        predelay = (s32)(32000.0F *
            ((struct AXFX_REVERBHI*)param)->preDelay);

        s0 = (tmp.v[0] + 2) * 4;
        s1 = (tmp.v[1] + 2) * 4;
        s2 = (tmp.v[2] + 2) * 4;
        s3 = (tmp.v[3] + 2) * 4;
        s4 = (tmp.v[4] + 2) * 4;
        s5 = (tmp.v[5] + 2) * 4;

        result += s0 + s3 + s1 + s4 + s2 + s5 +
                  (tmp.v[5] + 2) * 4 + predelay * 4;
        result += s0 + s3 + s1 + s4 + s2 + s5 +
                  (tmp.v[6] + 2) * 4 + predelay * 4;
        result += s0 + s3 + s1 + s4 + s2 + s5 +
                  (tmp.v[7] + 2) * 4 + predelay * 4;
        break;
    }

    case AXDRIVER_AUX_REVERB_STD:
    {
        s0 = (revstd_dims[0] + 2) * 4;
        s1 = (revstd_dims[1] + 2) * 4;
        s2 = (revstd_dims[2] + 2) * 4;
        s3 = (revstd_dims[3] + 2) * 4;

        predelay = (s32)(32000.0F *
            ((struct AXFX_REVERBSTD*)param)->preDelay);

        result = s0 + s2 + s1 + s3 + predelay * 4;
        result += s0 + s2 + s1 + s3 + predelay * 4;
        result += s0 + s2 + s1 + s3 + predelay * 4;
        break;
    }

    case AXDRIVER_AUX_CHORUS:
        result = 0x1680;
        break;

    case AXDRIVER_AUX_DELAY:
    {
        struct AXFX_DELAY* delay = (struct AXFX_DELAY*)param;
        s32 ch0, ch1, ch2;

        ch0 = ((delay->delay[0] - 5) * 32 + 159) / 160 * 640;
        ch1 = ((delay->delay[1] - 5) * 32 + 159) / 160 * 640;
        ch2 = ((delay->delay[2] - 5) * 32 + 159) / 160 * 640;
        result = ch0 + ch1 + ch2;
        break;
    }
    }

    return result;
}

bool AXDriver_8038E30C(s32 channel, s32 type, void* param, u8* heap,
                       u32 heap_size)
{
    if (channel < 0 || channel > 1) {
        return false;
    }
    if (type < 0 || type > 4 || (type != AXDRIVER_AUX_OFF && param == NULL)) {
        return false;
    }
    AXDriver_804D77D4 = heap;
    axfxallocsize = 0;
    axfxmaxsize = heap_size;
    return AXDriverSetupAux(channel, type, param);
}

bool AXDriver_8038E37C(AXDriverAuxType type, void* param)
{
    if (type < 0 || type > AXDRIVER_AUX_DELAY ||
        (type != AXDRIVER_AUX_OFF && param == NULL))
    {
        return false;
    }
    switch (type) {
    case AXDRIVER_AUX_OFF:
        break;
    case AXDRIVER_AUX_REVERB_HI:
        ((struct AXFX_REVERBHI*) param)->tempDisableFX = 0;
        ((struct AXFX_REVERBHI*) param)->time = 3.0F;
        ((struct AXFX_REVERBHI*) param)->preDelay = 0.1F;
        ((struct AXFX_REVERBHI*) param)->damping = 0.5F;
        ((struct AXFX_REVERBHI*) param)->coloration = 0.5F;
        ((struct AXFX_REVERBHI*) param)->crosstalk = 0.3F;
        ((struct AXFX_REVERBHI*) param)->mix = 0.5F;
        break;
    case AXDRIVER_AUX_REVERB_STD:
        ((struct AXFX_REVERBSTD*) param)->tempDisableFX = 0;
        ((struct AXFX_REVERBSTD*) param)->time = 1.48F;
        ((struct AXFX_REVERBSTD*) param)->preDelay = 0.002F;
        ((struct AXFX_REVERBSTD*) param)->damping = 0.64F;
        ((struct AXFX_REVERBSTD*) param)->coloration = 0.5F;
        ((struct AXFX_REVERBSTD*) param)->mix = 1.0F;
        break;
    case AXDRIVER_AUX_CHORUS:
        ((struct AXFX_CHORUS*) param)->baseDelay = 0xF;
        ((struct AXFX_CHORUS*) param)->variation = 0;
        ((struct AXFX_CHORUS*) param)->period = 0x1F4;
        break;
    case AXDRIVER_AUX_DELAY:
        ((struct AXFX_DELAY*) param)->delay[0] = 0x104;
        ((struct AXFX_DELAY*) param)->delay[1] = 0x136;
        ((struct AXFX_DELAY*) param)->delay[2] = 6;
        ((struct AXFX_DELAY*) param)->feedback[0] = 0x18;
        ((struct AXFX_DELAY*) param)->feedback[1] = 0x18;
        ((struct AXFX_DELAY*) param)->feedback[2] = 0;
        ((struct AXFX_DELAY*) param)->output[0] = 0x23;
        ((struct AXFX_DELAY*) param)->output[1] = 0x23;
        ((struct AXFX_DELAY*) param)->output[2] = 0;
        break;
    }
    return true;
}

void AXDriver_8038E498(int voices, int priority, int sample_rate,
                       int aram_size)
{
    HSD_SM* v;
    int i;

    v = AXDriver_804C45A0;
    for (i = 0; i < 0x60; i++) {
        v->flags &= ~SMSTATE_MASK;
        unk_inline(v, &AXDriver_804D7790);
        v++;
    }

    HSD_SynthInit(voices, priority, sample_rate, aram_size);
    HSD_SynthSFXSetDriverMasterClockCallback(fn_8038CC1C);
    HSD_SynthSFXSetDriverInactivatedCallback(fn_8038CEA4);
    HSD_SynthSFXSetDriverPauseCallback(fn_8038CF48);

    axfxallocsize = 0;
    AXDriver_804D77D4 = NULL;
    axfxmaxsize = 0;
    AXDriverSetupAux(0, AXDRIVER_AUX_OFF, NULL);

    axfxallocsize = 0;
    AXDriver_804D77D4 = NULL;
    axfxmaxsize = 0;
    AXDriverSetupAux(1, AXDRIVER_AUX_OFF, NULL);
    AXFXSetHooks(AXDriverAlloc, AXDriverFree);
}

int AXDriver_8038E5D4(void)
{
    return AXDriver_804D77C8;
}

int AXDriver_8038E5DC(void)
{
    return AXDriver_804D77D0;
}

static bool AXDriver_8038E5E4(int vid)
{
    int idx;
    bool enabled;
    HSD_SM* v;

    idx = vid & 0x7F;
    if (vid < 0 || idx >= 0x60) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & SMSTATE_MASK)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    if (v->vID != -1) {
        HSD_SynthSFXPause(v->vID);
    } else {
        HSD_ASSERT(0x5D6, (v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE);
        v->flags |= 0x20000000;
    }
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038E6C0(int channel)
{
    bool enabled;
    HSD_SM* v;

    if (channel < 0 || channel >= 0x10) {
        return false;
    }
    enabled = OSDisableInterrupts();
    v = AXDriver_804D7794;
    while (v != NULL) {
        if ((v->flags & SMSTATE_MASK) && v->itdflag == channel) {
            AXDriver_8038E5E4(v->unk);
        }
        v = v->next;
    }
    AXDriver_804D77CC |= 1 << channel;
    OSRestoreInterrupts(enabled);
    return true;
}

static bool AXDriver_8038E768(int vid)
{
    int idx;
    bool enabled;
    HSD_SM* v;

    idx = vid & 0x7F;
    if ((vid < 0) || idx >= 0x60) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & SMSTATE_MASK)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    if (v->vID != -1) {
        HSD_SynthSFXResume(v->vID);
    } else {
        HSD_ASSERT(0x619, (v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE);
    }
    v->flags &= 0xDFFFFFFF;
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038E844(int channel)
{
    bool enabled;
    HSD_SM* v;

    if ((channel < 0) || (channel >= 0x10)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    v = AXDriver_804D7794;
    while (v != NULL) {
        if ((v->flags & SMSTATE_MASK) && v->itdflag == channel) {
            AXDriver_8038E768(v->unk);
        }
        v = v->next;
    }
    AXDriver_804D77CC &= ~(1 << channel);
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038E8EC(const char* path, u8 volume, int track)
{
    int entrynum = DVDConvertPathToEntrynum(path);
    if (AXDriver_804D6038 != -1) {
        HSD_SynthSFXKeyOff(AXDriver_804D6038);
    }
    AXDriver_804D6038 = HSD_Synth_8038B5AC(entrynum, -1, volume, track);
    AXDriver_804D77E8 = AXDriver_804D778C;
    return true;
}

bool AXDriverStop(void)
{
    if (AXDriver_804D6038 == -1) {
        return false;
    }
    HSD_SynthSFXKeyOff(AXDriver_804D6038);
    AXDriver_804D6038 = -1;
    return true;
}

bool AXDriverPause(void)
{
    if (AXDriver_804D6038 == -1) {
        return false;
    }
    HSD_SynthSFXPause(AXDriver_804D6038);
    return true;
}

bool AXDriverResume(void)
{
    if (AXDriver_804D6038 == -1) {
        return false;
    }
    HSD_SynthSFXResume(AXDriver_804D6038);
    return true;
}

bool AXDriver_8038EA18(void)
{
    if (HSD_SynthSFXCheck(AXDriver_804D6038) == -1) {
        return false;
    }
    return true;
}
