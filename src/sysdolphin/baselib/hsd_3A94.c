#include "hsd_3A94.h"

#include "hsd_3AA7.h"
#include "hsd_3B2B.h"
#include "hsd_3B2E.h"

#include <dolphin/card.h>
#include <string.h>

extern s32 hsd_804D7980;
extern s32 hsd_804D7988;
extern s32 hsd_804D799C;

typedef struct CardStateExt {
    /* 0x00 */ u8* x0;
    /* 0x04 */ u8 pad_04[0x4];
    /* 0x08 */ u32 x8;
    /* 0x0C */ CARDFileInfo xC;
    /* 0x20 */ s32 x20;
    /* 0x24 */ u32 x24;
    /* 0x28 */ u8 pad_28[0x148];
    /* 0x170 */ s32 x170[0x40];
    /* 0x270 */ s32 x270[0x40];
    /* 0x370 */ u8 x370[0x40];
    /* 0x3B0 */ u8 x3B0;
    /* 0x3B1 */ u8 pad_3B1[0x7F];
    /* 0x430 */ u8 x430[0x30];
    /* 0x460 */ s32 x460;
} CardStateExt;

typedef struct CardCmdEntry {
    /* 0x00 */ s32 x0;
    /* 0x04 */ CardStateExt* state;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
} CardCmdEntry;

typedef struct CardBlock {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ u8 x10;
    /* 0x11 */ u8 x11;
    /* 0x12 */ u8 x12;
    /* 0x13 */ u8 pad_13[0x0D];
    /* 0x20 */ u8 x20[1];
} CardBlock;

static CardCmdEntry* hsd_803A949C_GetEntry(void)
{
    return &((CardCmdEntry*) hsd_804D1148)[hsd_804D7980];
}

static s32 hsd_803A949C_Close(CardStateExt* state)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDClose(&state->xC);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}

static s32 hsd_803A949C_IconSize(CardStateExt* state)
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

static s32 hsd_803A949C_FileId(CardBlock* block)
{
    return (block->x10 << 8) | block->x11;
}

void hsd_803A949C(s32 arg1)
{
    CardCmdEntry* entry;
    CardStateExt* state;
    CardBlock* block;
    s32 result;
    s32 icon_size;
    s32 offset;
    s32 remaining;
    s32 data_offset;
    s32 hdr_plus_icon;
    s32 slot;
    u32 sector_size;

    if (hsd_804D799C != 1) {
        return;
    }

    entry = hsd_803A949C_GetEntry();
    state = entry->state;

    switch (entry->x0) {
    case 2:
        if (arg1 != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }

        if (entry->x10 < 0) {
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
            }
            break;
        }

        if (entry->x10 == 0) {
            if (entry->x20 > 0) {
                offset = (state->x24 + 0x30) % state->x8;
                if (hsd_803B31CC(state->x0 + offset, state->x8 - offset) < 0) {
                    hsd_803A949C_Close(state);
                    hsd_804D7988 = -0x105;
                    break;
                }
                if (entry->x18 != 0) {
                    memcpy((void*) entry->x18, state->x0 + offset + 0x20,
                           entry->x20);
                }
            }
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
            }
            break;
        }

        if (hsd_803B31CC(state->x0, state->x8) < 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = -0x105;
            break;
        }
        if (entry->x20 > 0 && entry->x18 != 0) {
            memcpy((void*) entry->x18, state->x0 + 0x20, entry->x20);
        }
        result = hsd_803A949C_Close(state);
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

        if (entry->x10 == 0) {
            if (entry->x20 <= 0) {
                result = hsd_803A949C_Close(state);
                if (result < 0) {
                    hsd_804D7988 = result;
                }
                break;
            }

            offset = (state->x24 + 0x30) % state->x8;
            block = (CardBlock*) (state->x0 + offset);
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
        } else {
            block = (CardBlock*) state->x0;
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
        }

        if (hsd_803A949C_FileId(block) != entry->x10) {
            hsd_804D7988 = 2;
        } else if ((s32) block->x12 != entry->x14) {
            hsd_804D7988 = 2;
        } else if (entry->x20 > 0 &&
                   memcmp((void*) entry->x18, block->x20, entry->x20) != 0)
        {
            hsd_804D7988 = 2;
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
        hdr_plus_icon = icon_size + 0x40;
        sector_size = state->x8;

        if (entry->x8 == 0) {
            if (memcmp(state->x0, state->x370, 0x40) != 0) {
                hsd_804D7988 = 2;
                break;
            }
            if (icon_size > 0 &&
                memcmp(state->x0 + 0x40, (void*) entry->xC, icon_size) != 0)
            {
                hsd_804D7988 = 2;
                break;
            }
            if (state->x24 > sector_size) {
                if (memcmp(state->x0 + hdr_plus_icon, (void*) entry->x10,
                           sector_size - hdr_plus_icon) != 0)
                {
                    hsd_804D7988 = 2;
                    break;
                }
                hsd_803B2B20(state->x0, state->x8,
                             &state->x430[entry->x8 * 0x10]);
            } else if (memcmp(state->x0 + hdr_plus_icon, (void*) entry->x10,
                              state->x24 - hdr_plus_icon) != 0)
            {
                hsd_804D7988 = 2;
            } else {
                hsd_803B2B20(state->x0, state->x24,
                             &state->x430[entry->x8 * 0x10]);
                if (memcmp(state->x0 + state->x24, state->x430, 0x30) != 0) {
                    hsd_804D7988 = 2;
                }
            }
        } else {
            remaining = state->x24 - sector_size * entry->x8;
            data_offset = (sector_size * entry->x8) - 0x40 - icon_size;
            if ((u32) remaining > sector_size) {
                if (memcmp(state->x0, (u8*) entry->x10 + data_offset,
                           state->x8) != 0)
                {
                    hsd_804D7988 = 2;
                    break;
                }
                hsd_803B2B20(state->x0, state->x8,
                             &state->x430[entry->x8 * 0x10]);
            } else if (memcmp(state->x0, (u8*) entry->x10 + data_offset,
                              remaining) != 0)
            {
                hsd_804D7988 = 2;
            } else {
                hsd_803B2B20(state->x0, remaining,
                             &state->x430[entry->x8 * 0x10]);
                if (memcmp(state->x0 + remaining, state->x430, 0x30) != 0) {
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
        hdr_plus_icon = icon_size + 0x40;
        sector_size = state->x8;

        if (entry->x8 == 0) {
            if (entry->xC != 0) {
                memcpy((void*) entry->xC, state->x0, 0x40);
            }
            if (icon_size > 0 && entry->x10 != 0) {
                memcpy((void*) entry->x10, state->x0 + 0x40, icon_size);
            }
            if (state->x24 > sector_size) {
                if (entry->x14 != 0) {
                    memcpy((void*) entry->x14, state->x0 + hdr_plus_icon,
                           sector_size - hdr_plus_icon);
                }
                hsd_803B2B20(state->x0, state->x8,
                             &state->x430[entry->x8 * 0x10]);
            } else {
                if (entry->x14 != 0) {
                    memcpy((void*) entry->x14, state->x0 + hdr_plus_icon,
                           state->x24 - hdr_plus_icon);
                }
                hsd_803B2B20(state->x0, state->x24,
                             &state->x430[entry->x8 * 0x10]);
                if (memcmp(state->x0 + state->x24, state->x430, 0x30) != 0) {
                    hsd_804D7988 = -0x107;
                }
            }
        } else {
            remaining = state->x24 - sector_size * entry->x8;
            data_offset = (sector_size * entry->x8) - 0x40 - icon_size;
            if ((u32) remaining > sector_size) {
                if (entry->x14 != 0) {
                    memcpy((u8*) entry->x14 + data_offset, state->x0,
                           state->x8);
                }
                hsd_803B2B20(state->x0, state->x8,
                             &state->x430[entry->x8 * 0x10]);
            } else {
                if (entry->x14 != 0) {
                    memcpy((u8*) entry->x14 + data_offset, state->x0,
                           remaining);
                }
                hsd_803B2B20(state->x0, remaining,
                             &state->x430[entry->x8 * 0x10]);
                if (memcmp(state->x0 + remaining, state->x430, 0x30) != 0) {
                    hsd_804D7988 = -0x107;
                }
            }
        }
        break;

    case 1:
        slot = entry->xC;
        if (arg1 != 0) {
            state->x170[slot] = -0x7FFF;
            state->x270[slot] = 0;
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }
        if (entry->x10 != -1) {
            state->x170[slot] = entry->x10;
            state->x270[slot] = entry->x14;
        } else {
            state->x170[slot] = -0x7FFF;
            state->x270[slot] = 0;
        }
        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 16:
        slot = entry->xC;
        if (arg1 != 0) {
            state->x170[slot] = -0x7FFF;
            state->x270[slot] = 0;
            hsd_803A949C_Close(state);
            hsd_804D7988 = arg1;
            break;
        }
        if (entry->x10 != -1) {
            state->x170[slot] = entry->x10;
            state->x270[slot] = entry->x14;
        } else {
            state->x170[slot] = -0x7FFF;
            state->x270[slot] = 0;
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
        state->x20 = state->xC.fileNo;
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
        slot = entry->x10;
        hsd_803A949C_Close(state);
        if (arg1 != 0) {
            state->x170[slot] = -0x7FFF;
            state->x270[slot] = 0;
            break;
        }

        if (slot == 0) {
            offset = (state->x24 + 0x30) % state->x8;
            block = (CardBlock*) (state->x0 + offset);
            if (hsd_803B31CC(state->x0 + offset, state->x8 - offset) < 0) {
                state->x170[slot] = -0x7FFF;
                state->x270[slot] = 0;
                break;
            }
        } else {
            block = (CardBlock*) state->x0;
            if (hsd_803B31CC(state->x0, state->x8) < 0) {
                state->x170[slot] = -0x7FFF;
                state->x270[slot] = 0;
                break;
            }
        }

        state->x170[slot] = hsd_803A949C_FileId(block);
        if ((slot == 0 && state->x170[slot] != 0) ||
            (slot != 0 &&
             (state->x170[slot] < 0 || state->x170[slot] > state->x460)))
        {
            state->x170[slot] = -0x7FFF;
            state->x270[slot] = 0;
        } else {
            state->x270[slot] = block->x12;
            hsd_803AC558((struct hsd_803AC3E0_arg0_t*) state,
                         ((u8*) block) + 0x13);
        }
        break;
    }

    entry->x0 = 0;
    hsd_804D799C = 0;
    hsd_804D7980 = (hsd_804D7980 + 1) % 128;
}
