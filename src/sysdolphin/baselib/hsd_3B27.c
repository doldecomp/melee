#include "hsd_3B27.h"

#include <stddef.h>
#include <string.h>

#include "hsd_3A94.h"

typedef enum {
    cmd_type_0,
    cmd_type_1,
    cmd_type_2,
    cmd_type_3,
    cmd_type_4,
    cmd_type_5,
    cmd_type_6,
} cmd_type;

typedef struct {
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} cmd0;

typedef struct {
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} cmd2;

typedef struct {
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} cmd3;

typedef struct {
    s32 type;
    union {
        cmd2 c2;
        cmd3 c3;
        cmd0 c6;
    };
} HsdCmdEntry;

#define CMD_QUEUE(base) ((HsdCmdEntry*) ((base) + 0x1210))

int hsd_803B27F4(const CardState* arg0, const char* arg1, int arg2, int arg3,
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
        entry->type = cmd_type_6;
        entry->c6.f1 = (s32) arg0;
        entry->c6.f2 = (s32) arg1;
        entry->c6.f3 = arg2;
        entry->c6.f4 = arg3;
        entry->c6.f5 = (s32) arg4;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B286C(CardState* state, const char* filename, const char* comment,
                 int arg3, int arg4, void (*cb)(int, int))
{
    u8* base = hsd_804D1138;

    memcpy(state->comment, comment, 64);

    {
        s32 write_idx;
        s32 read_idx = hsd_804D7990;

        if (read_idx == (write_idx = hsd_804D7994)) {
            if (CMD_QUEUE(base)[read_idx].type != 0) {
                return -265;
            }
        }

        CMD_QUEUE(base)[write_idx].type = cmd_type_3;
        CMD_QUEUE(base)[write_idx].c3.f1 = (s32) state;
        CMD_QUEUE(base)[write_idx].c3.f2 = (s32) filename;
        CMD_QUEUE(base)[write_idx].c3.f3 = arg3;
        CMD_QUEUE(base)[write_idx].c3.f4 = arg4;
        CMD_QUEUE(base)[write_idx].c3.f5 = (s32) cb;
        hsd_804D7994 = (write_idx + 1) % 32;
    }

    return 0;
}

int hsd_803B2928(const CardState* arg0, const char* arg1, int arg2, int arg3,
                 void (*arg4)(int, int))
{
    u8* base = hsd_804D1138;

    memcpy((u8*) &arg0->comment, arg1, 64);

    {
        s32 write_idx;
        s32 read_idx = hsd_804D7990;

        if (read_idx == (write_idx = hsd_804D7994)) {
            if (CMD_QUEUE(base)[read_idx].type != 0) {
                return -265;
            }
        }

        CMD_QUEUE(base)[write_idx].type = 4;
        CMD_QUEUE(base)[write_idx].c6.f1 = (s32) arg0;
        CMD_QUEUE(base)[write_idx].c6.f3 = arg2;
        CMD_QUEUE(base)[write_idx].c6.f4 = arg3;
        CMD_QUEUE(base)[write_idx].c6.f5 = (s32) arg4;
        hsd_804D7994 = (write_idx + 1) % 32;
    }

    return 0;
}

int hsd_803B29D8(const CardState* ctx, int channel, const u8* data,
                 UNK_T callback)
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
        entry->c2.f1 = (s32) ctx;
        entry->c2.f2 = channel;
        entry->c2.f3 = (s32) data;
        entry->c2.f5 = (s32) callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B2A4C(const s32* arg0, int arg1, const u8* arg2,
                 void (*arg3)(int, int))
{
    u8* base = hsd_804D1138;
    s32 read_idx;
    s32 write_idx;
    HsdCmdEntry* entry;

    if (arg0[arg1 + offsetof(CardState, file_sizes) / sizeof(s32)] <= 0) {
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
        entry->type = cmd_type_2;
        entry->c2.f1 = (s32) arg0;
        entry->c2.f2 = arg1;
        entry->c2.f3 = (s32) arg2;
        entry->c2.f5 = (s32) arg3;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_SetCardIconInfo(CardState* ctx, CardIconInfo* icon_info)
{
    memcpy(&ctx->icon_info, icon_info, 18);
    ctx->header_size = hsd_803AC340(&ctx->icon_info);
    return 0;
}
