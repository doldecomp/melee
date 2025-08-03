#include "axdriver.static.h"

#include "axdriver.h"

#include <math_ppc.h>
#include <dolphin/axfx.h>
#include <sysdolphin/baselib/axdriver.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/synth.h>

// Forward declarations for functions not yet decompiled
static void fn_8038CC1C(void);
static void fn_8038CEA4(s32);
static void fn_8038CF48(s32);
static void AXFXSetHooks(void* (*) (size_t), void (*)(void*));

// External AX function declarations
void AXRegisterAuxACallback(void (*)(void*, void*), void*);
void AXRegisterAuxBCallback(void (*)(void*, void*), void*);
void* memcpy(void*, const void*, size_t);

void* AXDriverAlloc(size_t size)
{
    void* ptr = &AXDriver_804D77D4[axfxallocsize];

    // increment the size by the amount we will be indexing to.
    axfxallocsize += size;

    // size exceeds the max allowed; the pointer that we return would be
    // outside the heap. Raise an assert.
    if (axfxallocsize >= axfxmaxsize) {
        __assert("axdriver.c", 78, "axfxallocsize < axfxmaxsize");
    }
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
        if (*head == v) {
            __assert("axdriver.c", 113, "*head != v");
        }
    }
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
        return 0;
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
        return 0;
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
                float left_vol = (v->x26 * v->x24) / 65535.0F;
                float right_vol = (v->x27 * v->x25) / 65535.0F;
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
                        v->flags &= 0xFFFBFFFF;
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
                float left_vol = (v->x26 * v->x24) / 65535.0F;
                float right_vol = (v->x27 * v->x25) / 65535.0F;
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
    u32 temp_r27;
    s32 temp_r3_2;
    u32 temp_r3;
    int var_r28;

    while (v->x30 == (s32) AXDriver_804D778C) {
        temp_r3 = *(u32*) v->cmd_stream;
        temp_r27 = temp_r3 >> 0x18U;

        var_r28 = AXDriver_8038C678(temp_r27, temp_r3);
        if (var_r28 != 0) {
            AXDriver_8038BF6C(v);
        }
        v->x30 += var_r28;
        switch (temp_r27) {
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
                v->x24 = *v->cmd_stream;
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
                v->x24 = CLAMP(0, v->x24 + (s8) (u8) *v->cmd_stream, 0xFF);
            }
            break;
        case 18:
            if (!(((u32) AXDriver_804D603C >> 1U) & 1)) {
                v->flags |= 0x80;
                v->x25 = *v->cmd_stream;
            }
            break;
        case 19:
            if (!(AXDriver_804D603C >> 1 & 1)) {
                v->flags |= 0x80;
                v->x25 = CLAMP(0, v->x25 + (s8) (u8) *v->cmd_stream, 0xFF);
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

void fn_8038CC1C(void)
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
    AXDriver_804D778C += 1;
    while (v != NULL) {
        next = v->next;
        if (v->x30 == -1) {
            v->x30 = AXDriver_804D778C;
        } else if (v->flags & 0x20000000) {
            v->x30++;
        }
        switch (v->flags & 0xC0000000) {
        case 0x40000000:
            if (v->x30 == AXDriver_804D778C) {
                AXDriver_8038C6C0(v);
            }
            break;
        case 0:
            AXDriverUnlink(v, &AXDriver_804D7794);
            if (v != NULL) {
                if (AXDriver_804D7790 == v) {
                    __assert("axdriver.c", 0x7A, "*head != v");
                }
                v->prev = NULL;
                if (AXDriver_804D7790 != NULL) {
                    AXDriver_804D7790->prev = v;
                }
                v->next = AXDriver_804D7790;
                AXDriver_804D7790 = v;
            }
            AXDriver_804D77D0 -= 1;
            break;
        case 0x80000000:
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

void fn_8038CEA4(s32 vID)
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

void fn_8038CF48(s32 vID)
{
    HSD_SM* v;
    int idx;
    idx = vID & 0x3F;

    HSD_ASSERT(0x288, vID > 0);

    v = AXDriver_804C5920[idx];
    HSD_ASSERT(0x28A, v && v->vID == vID);

    v->flags |= 0x20000000;
}

HSD_SM* AXDriver_8038CFF4_inline(void)
{
    HSD_SM* v;
    if (AXDriver_804D7790 == NULL) {
        v = NULL;
    } else {
        bool enabled = OSDisableInterrupts();
        v = AXDriver_804D7790;
        AXDriverUnlink(v, &AXDriver_804D7790);
        OSRestoreInterrupts(enabled);
        v->vID = -1;
        v->x30 = -1;
        v->flags = 0;
        v->flags &= 0x3FFFFFFF;
    }
    return v;
}

int AXDriver_8038CFF4(int sound_id, u8 volume, u8 pan, int track, int channel,
                      float pitch)
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
    v->x24 = AXDriver_804C5A20[channel];
    v->x25 = AXDriver_804C5A30[channel];
    v->x26 = 0xFF;
    v->x27 = 0xFF;
    v->pri = 5;
    v->track = track;
    v->itdflag = channel;
    v->flags |= 0x30000;

    if (AXDriver_804D7788 & 0xFE000000) {
        OSReport("vidhigh exceeds the max value\n");
        __assert("axdriver.c", 0x2EA, "0");
    }

    v->unk = (AXDriver_804D7788 << 7) |
             ((u8*) v - (u8*) AXDriver_804C45A0) / sizeof(HSD_SM);
    AXDriver_804D7788++;

    enabled = OSDisableInterrupts();
    v->flags = (v->flags & 0x3FFFFFFF) | 0x40000000;
    if (v != NULL) {
        if (AXDriver_804D7794 == v) {
            __assert("axdriver.c", 0x7A, "*head != v");
        }
        v->prev = NULL;
        if (AXDriver_804D7794 != NULL) {
            AXDriver_804D7794->prev = v;
        }
        v->next = AXDriver_804D7794;
        AXDriver_804D7794 = v;
    }
    AXDriver_804D77D0++;
    OSRestoreInterrupts(enabled);

    return v->unk;
}

bool AXDriver_8038D2B4(int arg0, u8 arg1)
{
    int idx;
    bool enabled;
    HSD_SM* v;
    u8 var_r0;

    idx = arg0 & 0x7F;
    if ((arg0 < 0) || (idx >= 0x60)) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != arg0 || !(v->flags & 0xC0000000)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    if (v->vID != -1) {
        int tmp = arg1 < 0xFF ? arg1 : 0xFF;
        HSD_SynthSFXSetUserVol(v->vID, tmp);
    } else {
        if ((v->flags & 0xC0000000) != 0x40000000) {
            __assert("axdriver.c", 0x30B,
                     "(v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE");
        }
        v->pan = arg1;
        v->flags |= 0x20000;
    }
    OSRestoreInterrupts(enabled);
    return true;
}

/// #AXDriver_8038D3B8

/// #AXDriver_8038D4E4

/// #AXDriver_8038D5B4

/// #AXDriver_8038D914

/// #AXDriver_8038D9D8

void fn_8038DA5C(int arg0)
{
    if (arg0 != -1) {
        AXDriver_804D77EC = 1;
    }
}

/// #AXDriver_8038DA70

/// #AXDriver_8038DCFC

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

/// #AXDriver_8038E034

s32 AXDriver_8038E30C(s32 arg0, s32 arg1, void* arg2, u8* arg3, u32 arg4)
{
    if ((arg0 < 0) || (arg0 > 1)) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 > 4) ||
        ((arg1 != AXDRIVER_AUX_OFF) && (arg2 == NULL)))
    {
        return 0;
    }
    AXDriver_804D77D4 = arg3;
    axfxallocsize = 0;
    axfxmaxsize = arg4;
    return AXDriverSetupAux(arg0, arg1, arg2);
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

void AXDriver_8038E498(int arg0, int arg1, int arg2, int arg3)
{
    HSD_SM* v;
    int i;

    v = AXDriver_804C45A0;
    for (i = 0; i < 0x60; i++) {
        v->flags &= ~SMSTATE_MASK;
        if (v != NULL) {
            if (AXDriver_804D7790 == v) {
                __assert("axdriver.c", 0x7A, "*head != v");
            }
            v->prev = NULL;
            if (AXDriver_804D7790 != NULL) {
                AXDriver_804D7790->prev = v;
            }
            v->next = AXDriver_804D7790;
            AXDriver_804D7790 = v;
        }
        v++;
    }

    HSD_SynthInit(arg0, arg1, arg2, arg3);
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

bool AXDriver_8038E5E4(int vid)
{
    int idx;
    bool enabled;
    HSD_SM* v;

    idx = vid & 0x7F;
    if (vid < 0 || idx >= 0x60) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & 0xC0000000)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    if (v->vID != -1) {
        HSD_SynthSFXPause(v->vID);
    } else {
        if ((v->flags & 0xC0000000) != 0x40000000) {
            __assert("axdriver.c", 0x5D6,
                     "(v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE");
        }
        v->flags |= 0x20000000;
    }
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038E6C0(int arg0)
{
    bool enabled;
    HSD_SM* v;

    if (arg0 < 0 || arg0 >= 0x10) {
        return false;
    }
    enabled = OSDisableInterrupts();
    v = AXDriver_804D7794;
    while (v != NULL) {
        if ((v->flags & 0xC0000000) && v->itdflag == arg0) {
            AXDriver_8038E5E4(v->unk);
        }
        v = v->next;
    }
    AXDriver_804D77CC |= 1 << arg0;
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038E768(int vid)
{
    int idx;
    bool enabled;
    HSD_SM* v;

    idx = vid & 0x7F;
    if ((vid < 0) || idx >= 0x60) {
        return false;
    }
    v = &AXDriver_804C45A0[idx];
    if (v->unk != vid || !(v->flags & 0xC0000000)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    if (v->vID != -1) {
        HSD_SynthSFXResume(v->vID);
    } else if ((v->flags & 0xC0000000) != 0x40000000) {
        __assert("axdriver.c", 0x619,
                 "(v->flags&SMSTATE_MASK) == SMSTATE_ACTIVE");
    }
    v->flags &= 0xDFFFFFFF;
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038E844(int arg0)
{
    bool enabled;
    HSD_SM* v;

    if ((arg0 < 0) || (arg0 >= 0x10)) {
        return false;
    }
    enabled = OSDisableInterrupts();
    v = AXDriver_804D7794;
    while (v != NULL) {
        if ((v->flags & 0xC0000000) && v->itdflag == arg0) {
            AXDriver_8038E768(v->unk);
        }
        v = v->next;
    }
    AXDriver_804D77CC &= ~(1 << arg0);
    OSRestoreInterrupts(enabled);
    return true;
}

bool AXDriver_8038E8EC(char* arg0, int arg1, int arg2)
{
    int entrynum = DVDConvertPathToEntrynum(arg0);
    if (AXDriver_804D6038 != -1) {
        HSD_SynthSFXKeyOff(AXDriver_804D6038);
    }
    AXDriver_804D6038 = HSD_Synth_8038B5AC(entrynum, -1, arg1, arg2);
    AXDriver_804D77E8 = AXDriver_804D778C;
    return true;
}

bool AXDriver_8038E968(void)
{
    if (AXDriver_804D6038 == -1) {
        return false;
    }
    HSD_SynthSFXKeyOff(AXDriver_804D6038);
    AXDriver_804D6038 = -1;
    return true;
}

bool AXDriver_8038E9A8(void)
{
    if (AXDriver_804D6038 == -1) {
        return false;
    }
    HSD_SynthSFXPause(AXDriver_804D6038);
    return true;
}

bool AXDriver_8038E9E0(void)
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
