#include "hsd_3B27.h"

#include "hsd_3A94.h"
#include "hsd_3AA7.h"

#include <string.h>

typedef struct {
    s32 type;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} HsdCmdEntry;

#define CMD_QUEUE(base) ((HsdCmdEntry*)((base) + 0x1210))

int hsd_803B27F4(s32* arg0, const char* arg1, int arg2, int arg3,
                 void (*arg4)(int, int))
{
    s32 read_idx = hsd_804D7990;
    u8* base = hsd_804D1138;
    s32 write_idx = hsd_804D7994;
    HsdCmdEntry* entry;

    if (read_idx == write_idx) {
        if (CMD_QUEUE(base)[read_idx].type != 0) {
            return -265;
        }
    }

    entry = &CMD_QUEUE(base)[write_idx];
    {
        s32 next = write_idx + 1;
        entry->type = 6;
        entry->f1 = (s32)arg0;
        entry->f2 = (s32)arg1;
        entry->f3 = arg2;
        entry->f4 = arg3;
        entry->f5 = (s32)arg4;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B286C(s32* arg0, UNK_T arg1, const char* arg2, int arg3, int arg4,
                 void (*arg5)(int, int))
{
    u8* base = hsd_804D1138;

    memcpy((u8*)arg0 + 0x370, arg2, 64);

    {
        s32 write_idx;
        s32 read_idx = hsd_804D7990;

        if (read_idx == (write_idx = hsd_804D7994)) {
            if (CMD_QUEUE(base)[read_idx].type != 0) {
                return -265;
            }
        }

        CMD_QUEUE(base)[write_idx].type = 3;
        CMD_QUEUE(base)[write_idx].f1 = (s32)arg0;
        CMD_QUEUE(base)[write_idx].f2 = (s32)arg1;
        CMD_QUEUE(base)[write_idx].f3 = arg3;
        CMD_QUEUE(base)[write_idx].f4 = arg4;
        CMD_QUEUE(base)[write_idx].f5 = (s32)arg5;
        hsd_804D7994 = (write_idx + 1) % 32;
    }

    return 0;
}

int hsd_803B2928(s32* arg0, const char* arg1, int arg2, int arg3,
                 void (*arg4)(int, int))
{
    u8* base = hsd_804D1138;

    memcpy((u8*)arg0 + 0x370, arg1, 64);

    {
        s32 write_idx;
        s32 read_idx = hsd_804D7990;

        if (read_idx == (write_idx = hsd_804D7994)) {
            if (CMD_QUEUE(base)[read_idx].type != 0) {
                return -265;
            }
        }

        CMD_QUEUE(base)[write_idx].type = 4;
        CMD_QUEUE(base)[write_idx].f1 = (s32)arg0;
        CMD_QUEUE(base)[write_idx].f3 = arg2;
        CMD_QUEUE(base)[write_idx].f4 = arg3;
        CMD_QUEUE(base)[write_idx].f5 = (s32)arg4;
        hsd_804D7994 = (write_idx + 1) % 32;
    }

    return 0;
}

int hsd_803B29D8(s32* arg0, int arg1, int arg2, UNK_T arg3)
{
    s32 read_idx = hsd_804D7990;
    u8* base = hsd_804D1138;
    s32 write_idx = hsd_804D7994;
    HsdCmdEntry* entry;

    if (read_idx == write_idx) {
        if (CMD_QUEUE(base)[read_idx].type != 0) {
            return -265;
        }
    }

    entry = &CMD_QUEUE(base)[write_idx];
    {
        s32 next = write_idx + 1;
        entry->type = 1;
        entry->f1 = (s32)arg0;
        entry->f2 = arg1;
        entry->f3 = arg2;
        entry->f5 = (s32)arg3;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B2A4C(s32* arg0, int arg1, int arg2, void (*arg3)(int, int))
{
    u8* base = hsd_804D1138;
    s32 read_idx;
    s32 write_idx;
    HsdCmdEntry* entry;

    if (arg0[arg1 + 19] <= 0) {
        return -257;
    }

    read_idx = hsd_804D7990;
    write_idx = hsd_804D7994;

    if (read_idx == write_idx) {
        if (CMD_QUEUE(base)[read_idx].type != 0) {
            return -265;
        }
    }

    entry = &CMD_QUEUE(base)[write_idx];
    {
        s32 next = write_idx + 1;
        entry->type = 2;
        entry->f1 = (s32)arg0;
        entry->f2 = arg1;
        entry->f3 = arg2;
        entry->f5 = (s32)arg3;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B2ADC(s32* arg0, UNK_T arg1)
{
    memcpy(&arg0[236], arg1, 18);
    arg0[9] = hsd_803AC340(&arg0[236]);
    return 0;
}
