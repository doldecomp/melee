#include "hsd_3B27.h"

#include <string.h>

#include "hsd_3A94.h"

/// The request queue as a pointer value: MWCC then keeps the array offset in
/// the load/store displacement, as retail does.
#define CARD_REQUESTS(ctx) ((CardRequest*) (ctx)->requests)

int hsd_803B27F4(CardState* state, void* comment, void* banner, void* icons,
                 CardCallback callback)
{
    s32 read_idx = hsd_804D7990;
    CardContext* ctx = (CardContext*) &hsd_804D1138;
    s32 write_idx = hsd_804D7994;
    CardRequest* entry;

    if (read_idx == write_idx) {
        if (CARD_REQUESTS(ctx)[read_idx].type != 0) {
            return -265;
        }
    }

    entry = &CARD_REQUESTS(ctx)[write_idx];
    {
        s32 next = write_idx + 1;
        entry->type = CARD_REQ_READ_HEADER;
        entry->state = state;
        entry->header.comment = comment;
        entry->header.banner = banner;
        entry->header.icons = icons;
        entry->callback = callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B286C(CardState* state, const char* filename, const char* comment,
                 void* banner, void* icons, CardCallback callback)
{
    CardContext* ctx = (CardContext*) &hsd_804D1138;

    memcpy(state->comment, comment, 64);

    {
        s32 write_idx;
        s32 read_idx = hsd_804D7990;

        if (read_idx == (write_idx = hsd_804D7994)) {
            if (CARD_REQUESTS(ctx)[read_idx].type != 0) {
                return -265;
            }
        }

        CARD_REQUESTS(ctx)[write_idx].type = CARD_REQ_CREATE_FILE;
        CARD_REQUESTS(ctx)[write_idx].state = state;
        CARD_REQUESTS(ctx)[write_idx].create.filename = filename;
        CARD_REQUESTS(ctx)[write_idx].create.banner = banner;
        CARD_REQUESTS(ctx)[write_idx].create.icons = icons;
        CARD_REQUESTS(ctx)[write_idx].callback = callback;
        hsd_804D7994 = (write_idx + 1) % 32;
    }

    return 0;
}

int hsd_803B2928(CardState* state, const char* comment, void* banner,
                 void* icons, CardCallback callback)
{
    CardContext* ctx = (CardContext*) &hsd_804D1138;

    memcpy(state->comment, comment, 64);

    {
        s32 write_idx;
        s32 read_idx = hsd_804D7990;

        if (read_idx == (write_idx = hsd_804D7994)) {
            if (CARD_REQUESTS(ctx)[read_idx].type != 0) {
                return -265;
            }
        }

        CARD_REQUESTS(ctx)[write_idx].type = CARD_REQ_SET_STATUS;
        CARD_REQUESTS(ctx)[write_idx].state = state;
        CARD_REQUESTS(ctx)[write_idx].status.banner = banner;
        CARD_REQUESTS(ctx)[write_idx].status.icons = icons;
        CARD_REQUESTS(ctx)[write_idx].callback = callback;
        hsd_804D7994 = (write_idx + 1) % 32;
    }

    return 0;
}

int hsd_803B29D8(CardState* state, int file_idx, u8* buf,
                 CardCallback callback)
{
    s32 read_idx = hsd_804D7990;
    CardContext* ctx = (CardContext*) &hsd_804D1138;
    s32 write_idx = hsd_804D7994;
    CardRequest* entry;

    if (read_idx == write_idx) {
        if (CARD_REQUESTS(ctx)[read_idx].type != 0) {
            return -265;
        }
    }

    entry = &CARD_REQUESTS(ctx)[write_idx];
    {
        s32 next = write_idx + 1;
        entry->type = CARD_REQ_READ_FILE;
        entry->state = state;
        entry->file.file_idx = file_idx;
        entry->file.buf = buf;
        entry->callback = callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B2A4C(CardState* state, int file_idx, u8* buf,
                 CardCallback callback)
{
    CardContext* ctx = (CardContext*) &hsd_804D1138;
    s32 read_idx;
    s32 write_idx;
    CardRequest* entry;

    if (state->file_sizes[file_idx] <= 0) {
        return -257;
    }

    read_idx = hsd_804D7990;
    write_idx = hsd_804D7994;

    if (read_idx == write_idx) {
        if (CARD_REQUESTS(ctx)[read_idx].type != 0) {
            return -265;
        }
    }

    entry = &CARD_REQUESTS(ctx)[write_idx];
    {
        s32 next = write_idx + 1;
        entry->type = CARD_REQ_WRITE_FILE;
        entry->state = state;
        entry->file.file_idx = file_idx;
        entry->file.buf = buf;
        entry->callback = callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B2ADC(CardState* state, UNK_T data)
{
    memcpy(&state->banner_format, data, 18);
    state->header_size = hsd_803AC340(&state->banner_format);
    return 0;
}
