#include "perf.h"

#include "debug.h"

#include <string.h>
#include <dolphin/os.h>

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
        (OSGetTime() - start_time) / (f32) (OSSecondsToTicks(1) / 60);
}

void HSD_PerfSetDrawTime(void)
{
    HSD_PerfCurrentStat.draw_time =
        (OSGetTime() - start_time) / (f32) (OSSecondsToTicks(1) / 60);
}

void HSD_PerfSetTotalTime(void)
{
    HSD_PerfCurrentStat.total_time =
        (OSGetTime() - start_time) / (f32) (OSSecondsToTicks(1) / 60);
}

void HSD_PerfCountEnvelopeBlending(s32 n)
{
    HSD_ASSERT(0xA4, n < 32);
    HSD_PerfCurrentStat.env_blend[n]++;
}
