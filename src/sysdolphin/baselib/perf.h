#ifndef _hsd_perf_h_
#define _hsd_perf_h_

#include <platform.h>

typedef struct _HSD_PerfStat {
    f32 cpu_time;
    f32 draw_time;
    f32 total_time;
    u32 nb_mtx_load;
    u32 env_blend[32];
} HSD_PerfStat;

extern HSD_PerfStat HSD_PerfCurrentStat;
extern HSD_PerfStat HSD_PerfLastStat;

void HSD_PerfInitStat(void);
void HSD_PerfSetStartTime(void);
void HSD_PerfSetCPUTime(void);
void HSD_PerfSetDrawTime(void);
void HSD_PerfSetTotalTime(void);
void HSD_PerfCountEnvelopeBlending(s32 n);

static inline void HSD_PerfCountMtxLoad(void)
{
    HSD_PerfCurrentStat.nb_mtx_load += 1;
}

#endif
