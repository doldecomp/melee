/* Native regression tests for synth's packed records and AX conversions.
 * Include the implementation to exercise its private loader and helpers. */
#include <stdlib.h>

#include "sysdolphin/baselib/rumble.c"
#include "sysdolphin/baselib/synth.c"

/* The project's MSL headers omit host allocation declarations. */
extern void* malloc(size_t);
extern void free(void*);

static size_t allocation_size;
void* OSAllocFromHeap(int heap, size_t size)
{
    allocation_size = size;
    return malloc(size);
}
void OSReport(char* format, ...) {}
void __assert(const char* file, u32 line, const char* message)
{
    printf("ASSERT: %s:%u: %s\n", file, line, message);
    exit(1);
    __builtin_unreachable();
}

bool OSDisableInterrupts(void)
{
    return true;
}
bool OSRestoreInterrupts(bool enabled)
{
    return enabled;
}
void OSFreeToHeap(int heap, void* ptr)
{
    free(ptr);
}
int HSD_DevComRequest(int file, uintptr_t src, uintptr_t dest, size_t size,
                      int type, int priority, HSD_DevComCallback callback,
                      uintptr_t args)
{
    return 0;
}

static void check(bool condition, const char* message)
{
    if (!condition) {
        printf("FAIL: %s\n", message);
        exit(1);
    }
}

static void testAxFields(void)
{
    u32 ratios[] = { 0, 0x10000, 0x12345678, 0xFFFFFFFF };
    unsigned int i;
    for (i = 0; i < ARRAY_SIZE(ratios); i++) {
        AXPBSRC* src;
        HSD_Synth_80407FD8.ratio = ratios[i];
        src = getSrc();
        check(src->ratioHi == ratios[i] >> 16 &&
                  src->ratioLo == (ratios[i] & 0xFFFF),
              "AX ratio halves");
        src = getSrc();
        check(getAxAddress(src->ratioHi, src->ratioLo) == ratios[i],
              "AX conversion is repeatable");
        check(src->currentAddressFrac == 0 && src->last_samples[3] == 0,
              "AX history remains initialized");
    }
    check(getAxAddress(0x1234, 0x5678) == 0x12345678,
          "AX current address halves");
}

static void testRumble(void)
{
    HSD_Rumble commands[] = { { 0x8002 }, { 0x2002 }, { 0xA000 }, { 0 } };
    HSD_PadRumbleListData list = { 0 };
    u8 status = 0;
    int i;
    list.headp = list.listp = commands;
    list.frame = -2;
    for (i = 0; i < 4; i++) {
        check(HSD_PadRumbleInterpret1(&list, &status) == 0 && status == 2,
              "rumble opcode, duration and loop");
    }
    check(HSD_PadRumbleInterpret1(&list, &status) == 1, "rumble terminates");
}

int main(void)
{
    /* Two different record sizes make incorrect cursor strides observable. */
    u32 file[52] = { 0 };
    SfxVoice voice = { 0 };
    SfxBankBlock* block;
    SfxGroup* first;
    SfxGroup* second;

    check(SfxGroupFileSize(0) == 8, "file header has no runtime padding");
    check(SfxGroupFileSize(1) == 0x48, "mono file record size");
    check(SfxGroupFileSize(2) == 0x88, "stereo file record size");
    file[0] = 2;
    file[1] = 32000;
    voice.addr.ax.loopFlag = 1;
    voice.addr.ax.loopAddressHi = 1;
    voice.addr.ax.loopAddressLo = 0xFFF0;
    voice.addr.ax.endAddressHi = 3;
    voice.addr.ax.endAddressLo = 0xFFE0;
    voice.addr.ax.currentAddressHi = 5;
    voice.addr.ax.currentAddressLo = 0xFFD0;
    memcpy(&file[2], &voice, sizeof(voice));
    memcpy(&file[18], &voice, sizeof(voice));
    voice.addr.ax.loopFlag = 0;
    memcpy(&file[36], &voice, sizeof(voice));
    file[34] = 1;
    file[35] = 16000;
    hsd_SynthSFXLoadBuf[0] = sizeof(file);
    hsd_SynthSFXLoadBuf[1] = 0;
    hsd_SynthSFXLoadBuf[2] = 2;
    hsd_SynthSFXLoadBuf[3] = 100;
    memcpy(&hsd_SynthSFXLoadBuf[4], file, 16);
    hsd_SynthSFXBank[0] = 0x20;
    hsd_SynthSFXBankHead[1] = 0x1000;
    HSD_Synth_804D772C = 1;
    HSD_Synth_804C2A60[0].bankID = 0;
    HSD_Synth_804C2A60[0].entrynum = 17;
    HSD_SynthSFXHeaderLoadCallback(0, 0, NULL, false);
    block = HSD_Synth_804D7730;
    check(block != NULL, "allocate bank");
    memcpy(block, file + 4, sizeof(file) - 16);
    HSD_SynthSFXSampleLoadCallback(0, 0, NULL, false);
    first = hsd_SynthSFXDataHash[100 & 31];
    second = hsd_SynthSFXDataHash[101 & 31];
    check(HSD_Synth_804C2AE0[0] == block, "bank ownership");
    check(block->bank.entrynum == 17 && block->bank.group_count == 2,
          "bank metadata");
    check(first->voice_count == 2 && first->sample_rate == 32000,
          "stereo record survives expansion");
    check(second->voice_count == 1 && second->sample_rate == 16000,
          "mono record follows stereo record");
    check((u8*) HSD_Synth_804D7730 <= (u8*) block + allocation_size,
          "expanded records fit allocation");
    check(getAxAddress(first->voices[0].addr.ax.loopAddressHi,
                       first->voices[0].addr.ax.loopAddressLo) == 0x20030,
          "load relocation carries across AX halfwords");
    HSD_SynthSFXGroupDataReaddress(block, 0x10);
    check(getAxAddress(first->voices[1].addr.ax.loopAddressHi,
                       first->voices[1].addr.ax.loopAddressLo) == 0x20010,
          "negative relocation updates every voice");
    check(getAxAddress(second->voices[0].addr.ax.currentAddressHi,
                       second->voices[0].addr.ax.currentAddressLo) == 0x5FFF0,
          "relocation walks variable-sized records");
    check(getAxAddress(second->voices[0].addr.ax.loopAddressHi,
                       second->voices[0].addr.ax.loopAddressLo) == 0x20030,
          "non-looping relocation preserves loop address");
    free(block);
    testAxFields();
    testRumble();
    printf("synth portability: OK\n");
    return 0;
}
