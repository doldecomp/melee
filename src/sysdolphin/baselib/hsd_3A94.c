#include "hsd_3A94.h"

#include "hsd_3AA7.h"
#include "hsd_3B2B.h"
#include "hsd_3B2E.h"

#include <string.h>
#include <dolphin/card.h>

extern volatile s32 hsd_804D7980;
extern s32 hsd_804D7988;
extern s32 hsd_804D799C;

typedef struct CardBufEntry {
    s32 x0, x4, x8, xC;
    s32 x10;
    s32 x14, x18, x1C, x20;
} CardBufEntry;

typedef struct CardCmd {
    /* 0x00 */ s32 type;
    /* 0x04 */ CardState* state;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ void* x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
} CardCmd;

typedef struct CardBlock {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ u8 x10;
    /* 0x11 */ u8 x11;
    /* 0x12 */ u8 x12;
    /* 0x13 */ u8 pad_13[0x0D];
    /* 0x20 */ u8 x20[1];
} CardBlock;

#define CMD ((CardCmd*) &((CardBufEntry*) hsd_804D1138)[hsd_804D7980].x10)

static inline s32 hsd_803A949C_Close(CardState* state)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDClose(&state->file_info);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}

static inline s32 hsd_803A949C_IconSize(CardState* state)
{
    switch (state->x3B0) {
    case 2:
        return 0x1800;
    case 1:
        return 0xE00;
    default:
        return 0;
    }
}

static inline s32 hsd_803A949C_FileId(CardBlock* block)
{
    return (block->x10 << 8) | block->x11;
}

void hsd_803A949C(s32 chan, s32 arg1)
{
    CardState* state;
    CardBlock* block;
    s32 result;
    s32 icon_size;
    s32 offset;
    s32 remaining;
    s32 data_offset;
    s32 hdr_plus_icon;
    s32 slot;
    s32 i;

    if (hsd_804D799C != 1) {
        return;
    }

    state = CMD->state;

    switch (CMD->type) {
    case 2:
        if (arg1 != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }

        if (CMD->x10 < 0) {
            if (hsd_803A949C_Close(state) < 0) {
                hsd_804D7988 = arg1;
            }
            break;
        }

        if (CMD->x10 == 0) {
            offset = (state->x24 + 0x30) % state->x8;
            if (CMD->x20 > 0) {
                if (hsd_803B31CC(state->x0 + offset, state->x8 - offset) < 0) {
                    hsd_803A949C_Close(state);
                    hsd_804D7988 = -0x105;
                    break;
                }
                if (CMD->x18 != NULL) {
                    u8* src = state->x0 + offset;
                    memcpy(CMD->x18, src + 0x20, CMD->x20);
                }
            }
            result = hsd_803A949C_Close(state);
        } else {
            if (hsd_803B31CC(state->x0, state->x8) < 0) {
                hsd_803A949C_Close(state);
                hsd_804D7988 = -0x105;
                break;
            }
            if (CMD->x20 > 0 && CMD->x18 != NULL) {
                memcpy(CMD->x18, state->x0 + 0x20, CMD->x20);
            }
            result = hsd_803A949C_Close(state);
        }
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 15:
        if (arg1 != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
        } else if (hsd_803B31CC(state->x0, state->x8) < 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = -0x105;
        } else {
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
            }
        }
        break;

    case 5:
        if (arg1 != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }

        if (CMD->x10 == 0) {
            if (CMD->x20 <= 0) {
                result = hsd_803A949C_Close(state);
                if (result < 0) {
                    hsd_804D7988 = result;
                }
                break;
            }

            offset = (state->x24 + 0x30) % state->x8;
            if (hsd_803B31CC(state->x0 + offset, state->x8 - offset) < 0) {
                hsd_803A949C_Close(state);
                hsd_804D7988 = 2;
                break;
            }
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
                break;
            }
            block = (CardBlock*) (state->x0 + offset);
            if (hsd_803A949C_FileId(block) != CMD->x10) {
                hsd_804D7988 = 2;
            } else if ((s32) block->x12 != CMD->x14) {
                hsd_804D7988 = 2;
            } else if (CMD->x20 > 0 &&
                       memcmp(CMD->x18, block->x20, CMD->x20) != 0)
            {
                hsd_804D7988 = 2;
            }
        } else {
            if (hsd_803B31CC(state->x0, state->x8) < 0) {
                hsd_803A949C_Close(state);
                hsd_804D7988 = 2;
                break;
            }
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
                break;
            }
            block = (CardBlock*) state->x0;
            if (hsd_803A949C_FileId(block) != CMD->x10) {
                hsd_804D7988 = 2;
            } else if ((s32) block->x12 != CMD->x14) {
                hsd_804D7988 = 2;
            } else if (CMD->x20 > 0 &&
                       memcmp(CMD->x18, block->x20, CMD->x20) != 0)
            {
                hsd_804D7988 = 2;
            }
        }
        break;

    case 10:
        if (arg1 != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }

        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
            break;
        }

        icon_size = hsd_803A949C_IconSize(state);

        if (CMD->x8 == 0) {
            if (memcmp(state->x0, state->x370, 0x40) != 0) {
                hsd_804D7988 = 2;
                break;
            }
            if (icon_size > 0 &&
                memcmp(state->x0 + 0x40, (void*) CMD->xC, icon_size) != 0)
            {
                hsd_804D7988 = 2;
                break;
            }
            hdr_plus_icon = icon_size + 0x40;
            if (state->x24 > state->x8) {
                if (memcmp(state->x0 + hdr_plus_icon, (void*) CMD->x10,
                           state->x8 - hdr_plus_icon) != 0)
                {
                    hsd_804D7988 = 2;
                    break;
                }
                hsd_803B2B20(CMD->state->x0, CMD->state->x8,
                             &CMD->state->digest[CMD->x8 * 0x10]);
            } else if (memcmp(state->x0 + hdr_plus_icon, (void*) CMD->x10,
                              state->x24 - hdr_plus_icon) != 0)
            {
                hsd_804D7988 = 2;
            } else {
                hsd_803B2B20(CMD->state->x0, CMD->state->x24,
                             &CMD->state->digest[CMD->x8 * 0x10]);
                if (memcmp(state->x0 + state->x24, CMD->state->digest, 0x30) !=
                    0)
                {
                    hsd_804D7988 = 2;
                }
            }
        } else {
            remaining = state->x24 - state->x8 * CMD->x8;
            data_offset = (state->x8 * CMD->x8) - 0x40 - icon_size;
            if ((u32) remaining > state->x8) {
                if (memcmp(state->x0, (u8*) CMD->x10 + data_offset,
                           state->x8) != 0)
                {
                    hsd_804D7988 = 2;
                    break;
                }
                hsd_803B2B20(CMD->state->x0, CMD->state->x8,
                             &CMD->state->digest[CMD->x8 * 0x10]);
            } else if (memcmp(state->x0, (u8*) CMD->x10 + data_offset,
                              remaining) != 0)
            {
                hsd_804D7988 = 2;
            } else {
                hsd_803B2B20(CMD->state->x0, remaining,
                             &CMD->state->digest[CMD->x8 * 0x10]);
                if (memcmp(state->x0 + remaining, CMD->state->digest, 0x30) !=
                    0)
                {
                    hsd_804D7988 = 2;
                }
            }
        }
        break;

    case 11:
        if (arg1 != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }

        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
            break;
        }

        icon_size = hsd_803A949C_IconSize(state);

        if (CMD->x8 == 0) {
            if (((void*) CMD->xC) != NULL) {
                memcpy((void*) CMD->xC, state->x0, 0x40);
            }
            if (icon_size > 0 && ((void*) CMD->x10) != NULL) {
                memcpy((void*) CMD->x10, state->x0 + 0x40, icon_size);
            }
            hdr_plus_icon = icon_size + 0x40;
            if (state->x24 > state->x8) {
                if (((void*) CMD->x14) != NULL) {
                    memcpy((void*) CMD->x14, state->x0 + hdr_plus_icon,
                           state->x8 - hdr_plus_icon);
                }
                hsd_803B2B20(CMD->state->x0, CMD->state->x8,
                             &CMD->state->digest[CMD->x8 * 0x10]);
            } else {
                if (((void*) CMD->x14) != NULL) {
                    memcpy((void*) CMD->x14, state->x0 + hdr_plus_icon,
                           state->x24 - hdr_plus_icon);
                }
                hsd_803B2B20(CMD->state->x0, CMD->state->x24,
                             &CMD->state->digest[CMD->x8 * 0x10]);
                if (memcmp(state->x0 + state->x24, CMD->state->digest, 0x30) !=
                    0)
                {
                    hsd_804D7988 = -0x107;
                }
            }
        } else {
            remaining = state->x24 - state->x8 * CMD->x8;
            data_offset = (state->x8 * CMD->x8) - 0x40 - icon_size;
            if ((u32) remaining > state->x8) {
                if (((void*) CMD->x14) != NULL) {
                    memcpy((u8*) CMD->x14 + data_offset, state->x0, state->x8);
                }
                hsd_803B2B20(CMD->state->x0, CMD->state->x8,
                             &CMD->state->digest[CMD->x8 * 0x10]);
            } else {
                if (((void*) CMD->x14) != NULL) {
                    memcpy((u8*) CMD->x14 + data_offset, state->x0, remaining);
                }
                hsd_803B2B20(CMD->state->x0, remaining,
                             &CMD->state->digest[CMD->x8 * 0x10]);
                if (memcmp(state->x0 + remaining, CMD->state->digest, 0x30) !=
                    0)
                {
                    hsd_804D7988 = -0x107;
                }
            }
        }
        break;

    case 1:
        if (arg1 != 0) {
            state->x170[CMD->xC] = -0x7FFF;
            state->x270[CMD->xC] = 0;
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }
        if (CMD->x10 != 0xFFFF) {
            state->x170[CMD->xC] = CMD->x10;
            state->x270[CMD->xC] = CMD->x14;
        } else {
            state->x170[CMD->xC] = -0x7FFF;
            state->x270[CMD->xC] = 0;
        }
        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 16:
        if (arg1 != 0) {
            state->x170[CMD->xC] = -0x7FFF;
            state->x270[CMD->xC] = 0;
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }
        if (CMD->x10 != 0xFFFF) {
            state->x170[CMD->xC] = CMD->x10;
            state->x270[CMD->xC] = CMD->x14;
        } else {
            state->x170[CMD->xC] = -0x7FFF;
            state->x270[CMD->xC] = 0;
        }
        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 7:
        if (arg1 != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }
        result = state->file_info.fileNo;
        i = 0;
        do {
            if (result != -1) {
                break;
            }
            i++;
        } while (i < 10);
        state->x20 = result;
        if (state->x20 < 0) {
            hsd_804D7988 = state->x20;
        }
        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 8:
        if (arg1 != 0) {
            hsd_804D7988 = arg1;
        }
        break;

    case 9:
        if (arg1 != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
        } else {
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
            }
        }
        break;

    case 13:
        slot = CMD->x10;
        hsd_803A949C_Close(state);
        if (arg1 != 0) {
            state->x170[slot] = -0x7FFF;
            state->x270[slot] = 0;
            break;
        }

        if (slot == 0) {
            offset = (state->x24 + 0x30) % state->x8;
            if (hsd_803B31CC(state->x0 + offset, state->x8 - offset) < 0) {
                state->x170[0] = -0x7FFF;
                state->x270[0] = 0;
                break;
            }
            state->x170[slot] =
                state->x0[offset + 0x11] + (state->x0[offset + 0x10] << 8);
            if (state->x170[slot] != 0) {
                state->x170[slot] = -0x7FFF;
                state->x270[slot] = 0;
            } else {
                state->x270[slot] = state->x0[offset + 0x12];
                hsd_803AC558(state, state->x0 + offset + 0x13);
            }
        } else {
            if (hsd_803B31CC(state->x0, state->x8) < 0) {
                state->x170[slot] = -0x7FFF;
                state->x270[slot] = 0;
                break;
            }
            state->x170[slot] = state->x0[0x11] + (state->x0[0x10] << 8);
            if (state->x170[slot] < 0 || state->x170[slot] > state->x460) {
                state->x170[slot] = -0x7FFF;
                state->x270[slot] = 0;
            } else {
                state->x270[slot] = state->x0[0x12];
                hsd_803AC558(state, state->x0 + 0x13);
            }
        }
        break;
    }

    CMD->type = 0;
    hsd_804D799C = 0;
    hsd_804D7980 = (hsd_804D7980 + 1) % 128;
}
