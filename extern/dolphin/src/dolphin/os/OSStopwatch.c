#include <dolphin.h>
#include <dolphin/os.h>

void OSInitStopwatch(struct OSStopwatch * sw, char * name) {
    sw->name = name;
    sw->total = 0;
    sw->hits = 0;
    sw->min = 0x00000000FFFFFFFF;
    sw->max = 0;
}

void OSStartStopwatch(struct OSStopwatch * sw) {
    sw->running = 1;
    sw->last = OSGetTime();
}

void OSStopStopwatch(struct OSStopwatch * sw) {
    long long interval;

    if (sw->running != 0) {
        interval = OSGetTime() - sw->last;
        sw->total += interval;
        sw->running = 0;
        sw->hits++;
        if (sw->max < interval) {
            sw->max = interval;
        }
        if (interval < sw->min) {
            sw->min = interval;
        }
    }
}

long long OSCheckStopwatch(struct OSStopwatch * sw) {
    long long currTotal;

    currTotal = sw->total;
    if (sw->running != 0) {
        currTotal += OSGetTime() - sw->last;
    }
    return currTotal;
}

void OSResetStopwatch(struct OSStopwatch * sw) {
    OSInitStopwatch(sw, sw->name);
}

void OSDumpStopwatch(struct OSStopwatch * sw) {
    OSReport("Stopwatch [%s]	:\n", sw->name);
    OSReport("\tTotal= %lld us\n",    OSTicksToMicroseconds(sw->total));
    OSReport("\tHits = %d \n",        sw->hits);
    OSReport("\tMin  = %lld us\n",    OSTicksToMicroseconds(sw->min));
    OSReport("\tMax  = %lld us\n",    OSTicksToMicroseconds(sw->max));
    OSReport("\tMean = %lld us\n",    OSTicksToMicroseconds(sw->total/sw->hits));
}
