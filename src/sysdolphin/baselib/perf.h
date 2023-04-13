#ifndef _hsd_perf_h_
#define _hsd_perf_h_

#include <platform.h>

typedef struct _HSD_PerfStat {
    f32 cpu_time;
    f32 draw_time;
    f32 total_time;
    u32 _;
    u32 count[32];
} HSD_PerfStat;

void HSD_PerfInitStat(void);
void HSD_PerfSetStartTime(void);
void HSD_PerfSetCPUTime(void);
void HSD_PerfSetDrawTime(void);
void HSD_PerfSetTotalTime(void);
void HSD_PerfCountEnvelopeBlending(s32 n);

#endif
