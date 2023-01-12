#include <sysdolphin/baselib/perf.h>

#include <dolphin/os/OSTime.h>
#include <sysdolphin/baselib/debug.h>

s64 start_time;

HSD_PerfStat HSD_PerfLastStat = { 0 };
HSD_PerfStat HSD_PerfCurrentStat = { 0 };

void HSD_PerfInitStat(void)
{
    HSD_PerfLastStat = HSD_PerfCurrentStat;
    memset(&HSD_PerfCurrentStat, 0, sizeof(HSD_PerfStat));
}

void HSD_PerfSetStartTime(void)
{
    start_time = OSGetTime();
}

void HSD_PerfSetCPUTime(void)
{
    HSD_PerfCurrentStat.cpu_time =
        (OSGetTime() - start_time) / (f32) (*(u32*) 0x800000F8 / 4 / 60);
}

void HSD_PerfSetDrawTime(void)
{
    HSD_PerfCurrentStat.draw_time =
        (OSGetTime() - start_time) / (f32) (*(u32*) 0x800000F8 / 4 / 60);
}

void HSD_PerfSetTotalTime(void)
{
    HSD_PerfCurrentStat.total_time =
        (OSGetTime() - start_time) / (f32) (*(u32*) 0x800000F8 / 4 / 60);
}

void HSD_PerfCountEnvelopeBlending(s32 n)
{
    HSD_ASSERT(0xA4, n < 32);
    HSD_PerfCurrentStat.count[n]++;
}
