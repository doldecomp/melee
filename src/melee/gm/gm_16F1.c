#include "gm_16F1.h"

#include <Runtime/platform.h>

#include <melee/pl/forward.h>

#include "gm_1601.h"
#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmvs.h"
#include <melee/if/textlib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbtime.h>
#include <melee/mn/types.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonus.h>
#include <melee/pl/plbonuslib.h>
#include <melee/ty/toy.h>
#include <sysdolphin/baselib/sislib.h>

static struct {
    u8 x0;
    u8 x1;
    struct {
        u8 x0;
        u8 x1;
    } x2[6];
} lbl_8046DBC8;

static int lbl_803D5648[] = {
    ///< @todo this is the start of a data section
    0x000003E8, 0xFFFFFC18, 0x000007D0, 0xFFFFFA24, 0x00000BB8, 0x000005DC,
    0x000007D0, 0x000003E8, 0xFFFFFC18, 0xFFFFFE0C, 0xFFFFF830, 0xFFFFFC18,
    0x000001F4, 0xFFFFFE0C, 0xFFFFFE0C, 0x00000FA0, 0x000009C4, 0x000005DC,
    0x000007D0, 0x000009C4, 0x00001388, 0x00000320, 0x00000BB8, 0x00001F40,
    0xFFFFFE0C, 0x000007D0, 0x00000FA0, 0x00000FA0, 0x00002710, 0x00001770,
    0x00000FA0, 0x00002710, 0x00004E20, 0x00001B58, 0x00000DAC, 0x00000BB8,
    0x00000DAC, 0x000005DC, 0x00000898, 0x00000C1C, 0x00000708, 0x000001F4,
    0x000003E8, 0x00000BB8, 0x00001B58, 0x00002710, 0x00003A98, 0x00004E20,
    0x000007D0, 0x000007D0, 0x00002710, 0x00001770, 0xFFFFFE0C, 0xFFFFFA24,
    0x000007D0, 0x00000DAC, 0x0000012C, 0x000009C4, 0x000005DC, 0x000009C4,
    0x000007D0, 0xFFFFFC18, 0xFFFFF63C, 0x000001F4, 0x00001388, 0x0000012C,
    0x00001964, 0x000009C4, 0x000003E8, 0x000007D0, 0x000005DC, 0x000009C4,
    0x00000BB8, 0x00000FA0, 0x00000320, 0x000007D0, 0x00001388, 0x000009C4,
    0xFFFFFC18, 0xFFFFF830, 0x000001F4, 0x000003E8, 0x00000320, 0x000003E8,
    0x00000320, 0x000009C4, 0x000007D0, 0x00000320, 0x000007D0, 0x000001F4,
    0x000002BC, 0x00000320, 0x00000064, 0x000003E8, 0x000002BC, 0x00000FA0,
    0x00000BB8, 0x000005DC, 0x000005DC, 0x000009C4, 0x000005DC, 0x0000012C,
    0x000004B0, 0x0000012C, 0x00000064, 0xFFFFF830, 0x00000BB8, 0x000009C4,
    0x000009C4, 0x000007D0, 0x00000BB8, 0x000009C4, 0x00000BB8, 0x00001388,
    0x00000BB8, 0x00001B58, 0x00001388, 0x00002EE0, 0xFFFFFA24, 0x000007D0,
    0x00000320, 0xFFFFFC18, 0xFFFFF830, 0xFFFFFE0C, 0x000007D0, 0x00000BB8,
    0x000007D0, 0x00000BB8, 0x0000012C, 0x00001388, 0x00000FA0, 0x00000320,
    0x00001388, 0x000001F4, 0x00000BB8, 0x00000DAC, 0x00000320, 0x000007D0,
    0x00000280, 0x000004B0, 0x000005DC, 0x000009C4, 0x000007D0, 0x00000FA0,
    0x00001F40, 0x00003A98, 0x00000FA0, 0x000003E8, 0x000005DC, 0x000001F4,
    0xFFFFFC18, 0x000001F4, 0xFFFFFC18, 0xFFFFFA24, 0x000007D0, 0x000001F4,
    0x000003E8, 0x000007D0, 0x000003E8, 0x000001F4, 0x000007D0, 0x000005DC,
    0x00000BB8, 0x00001388, 0x00000D02, 0x00000456, 0x000007D0, 0x00000708,
    0x000007D0, 0x00000BB8, 0x00000BB8, 0x00000320, 0x00000320, 0x000005DC,
    0x000003E8, 0x000007D0, 0xFFFFFC18, 0x00000BB8, 0x00000064, 0x000005DC,
    0x00000FA0, 0x00000FA0, 0x00000BB8, 0x000007D0, 0x000005DC, 0x000005DC,
    0x000005DC, 0x000005DC, 0x000005DC, 0x00000640, 0x000007D0, 0x000006A4,
    0x000007D0, 0x000007D0, 0x000009C4, 0x000003E8, 0x000009C4, 0x00001F40,
    0x00000320, 0x000007D0, 0x000007D0, 0x00000BB8, 0x000005DC, 0x00000FA0,
    0x00000FA0, 0x00000258, 0x000009C4, 0x0000012C, 0x00000320, 0x000004B0,
    0x00000708, 0x00000AF0, 0x000004B0, 0x00000320, 0x00000320, 0x00000258,
    0x00000FA0, 0x00000640, 0x000005DC, 0x000009C4, 0x00000320, 0xFFFFFE0C,
    0x000009C4, 0x00000190, 0x00000320, 0x000003E8, 0x00002710, 0x00001F40,
    0x000493E0, 0x00002710, 0xFFFFB1E0, 0x00002710, 0x00004E20, 0x000186A0,
    0x0000C350, 0x0000C350, 0x0000C350, 0x00030D40, 0x00000064, 0x000000C8,
    0x0000012C, 0x0000012C, 0x000001F4, 0x00000096, 0x000000C8, 0x00000320,
    0x00000014, 0x00013880, 0x00000014, 0x00007530, 0x00002710, 0x00001F40,
    0x000186A0, 0x00007530, 0x000003E8, 0x00007530, 0x00000320,
};

struct lbl_803D5A4C_t {
    /* +0 */ s16 kind;
    /* +2 */ u16 x2;
    /* +4 */ u8 x4;
    /* +5 */ u8 x5; ///< Gm_DecType
    /* +6 */ u8 x6;
};

/* 3D5A4C */ static struct {
    struct lbl_803D5A4C_t entries[0x80C / sizeof(struct lbl_803D5A4C_t)];
    u8 pad[4];
} lbl_803D5A4C = {
    {
        { 0, 0x011, 0xFF, 0, 2 },
        { 1, 0x012, 0xFF, 0, 0 },
        { 2, 0x013, 0x7F, 1, 0 },
        { 3, 0x014, 0xFF, 0, 0 },
        { 4, 0x015, 0xFF, 0, 0 },
        { 5, 0x016, 0xFF, 0, 2 },
        { 6, 0x017, 0xFF, 1, 0 },
        { 7, 0x018, 0xFD, 1, 0 },
        { 8, 0x019, 0xFF, 0, 0 },
        { 9, 0x01A, 0xFF, 0, 0 },
        { 0xA, 0x01B, 0xFF, 1, 0 },
        { 0xB, 0x01C, 0xFF, 1, 0 },
        { 0xC, 0x01D, 0xFF, 0, 0 },
        { 0xD, 0x01E, 0xFF, 0, 0 },
        { 0xE, 0x01F, 0xFF, 0, 0 },
        { 0xF, 0x020, 0xFF, 0, 0 },
        { 0x10, 0x021, 0xFF, 0, 0 },
        { 0x11, 0x022, 0xFF, 0, 0 },
        { 0x12, 0x023, 0xFF, 0, 0 },
        { 0x13, 0x024, 0xFF, 1, 0 },
        { 0x14, 0x025, 0xFF, 0, 0 },
        { 0x15, 0x026, 0xFF, 0, 2 },
        { 0x16, 0x027, 0x9F, 0, 0 },
        { 0x17, 0x028, 0xFF, 0, 2 },
        { 0x18, 0x029, 0xFF, 0, 2 },
        { 0x19, 0x02A, 0xFF, 0, 0 },
        { 0x1A, 0x02B, 0xFF, 1, 0 },
        { 0x1B, 0x02C, 0xFF, 0, 0 },
        { 0x1C, 0x02D, 0xFF, 0, 0 },
        { 0x1D, 0x02E, 0xFF, 0, 0 },
        { 0x1E, 0x02F, 0xFF, 0, 0 },
        { 0x1F, 0x030, 0xFF, 0, 0 },
        { 0x20, 0x031, 0xFF, 0, 0 },
        { 0x21, 0x033, 0xFF, 0, 2 },
        { 0x22, 0x032, 0xFF, 0, 2 },
        { 0x23, 0x034, 0xFF, 0, 0 },
        { 0x24, 0x035, 0xFF, 0, 2 },
        { 0x25, 0x036, 0xFF, 0, 0 },
        { 0x26, 0x037, 0xFF, 0, 0 },
        { 0x27, 0x038, 0xFF, 0, 0 },
        { 0x28, 0x039, 0xFF, 0, 0 },
        { 0x29, 0x03A, 0xFF, 1, 0 },
        { 0x2A, 0x03B, 0xFD, 1, 0 },
        { 0x2B, 0x03C, 0xFF, 0, 0 },
        { 0x2C, 0x03D, 0xFF, 0, 0 },
        { 0x2D, 0x03E, 0xFF, 1, 0 },
        { 0x2E, 0x03F, 0x87, 0, 0 },
        { 0x2F, 0x040, 0x87, 0, 0 },
        { 0x30, 0x041, 0xFF, 0, 0 },
        { 0x31, 0x042, 0xFF, 0, 0 },
        { 0x32, 0x043, 0xFF, 0, 0 },
        { 0x33, 0x044, 0xFF, 0, 0 },
        { 0x34, 0x045, 0xFF, 0, 0 },
        { 0x35, 0x046, 0xFF, 0, 0 },
        { 0x36, 0x047, 0xFF, 0, 0 },
        { 0x37, 0x048, 0xFF, 0, 0 },
        { 0x38, 0x049, 0xFF, 0, 0 },
        { 0x39, 0x04A, 0xFF, 0, 0 },
        { 0x3A, 0x04B, 0xFF, 0, 0 },
        { 0x3B, 0x04C, 0xFF, 1, 0 },
        { 0x3C, 0x04D, 0xFF, 0, 0 },
        { 0x3D, 0x04E, 0xFF, 1, 0 },
        { 0x3E, 0x04F, 0xFF, 1, 0 },
        { 0x3F, 0x050, 0xFF, 1, 0 },
        { 0x40, 0x051, 0xFF, 1, 0 },
        { 0x41, 0x052, 0xFF, 1, 0 },
        { 0x42, 0x053, 0xFF, 0, 0 },
        { 0x43, 0x054, 0xFF, 1, 0 },
        { 0x44, 0x055, 0xFF, 1, 0 },
        { 0x45, 0x056, 0xFF, 1, 0 },
        { 0x46, 0x057, 0xFF, 1, 0 },
        { 0x47, 0x058, 0xFF, 0, 0 },
        { 0x48, 0x059, 0xFF, 1, 0 },
        { 0x49, 0x05A, 0xFF, 1, 0 },
        { 0x4A, 0x05B, 0xFF, 1, 0 },
        { 0x4B, 0x05C, 0xFF, 1, 0 },
        { 0x4C, 0x05D, 0xFF, 1, 0 },
        { 0x4D, 0x05E, 0xFF, 1, 0 },
        { 0x4E, 0x060, 0x02, 0, 0 },
        { 0x4F, 0x061, 0xFF, 0, 0 },
        { 0x50, 0x062, 0xDF, 0, 0 },
        { 0x51, 0x063, 0xFF, 0, 0 },
        { 0x52, 0x064, 0xFF, 0, 0 },
        { 0x53, 0x065, 0xFF, 0, 0 },
        { 0x54, 0x066, 0xFF, 1, 0 },
        { 0x55, 0x067, 0xDF, 0, 0 },
        { 0x56, 0x068, 0xFF, 1, 0 },
        { 0x57, 0x069, 0xFF, 0, 0 },
        { 0x58, 0x06A, 0xFF, 1, 0 },
        { 0x59, 0x06B, 0x1F, 0, 0 },
        { 0x5A, 0x06C, 0xFF, 0, 0 },
        { 0x5B, 0x06D, 0xFF, 1, 0 },
        { 0x5C, 0x06E, 0xFF, 1, 0 },
        { 0x5D, 0x06F, 0xFF, 0, 0 },
        { 0x5E, 0x070, 0xFF, 0, 0 },
        { 0x5F, 0x071, 0xFD, 1, 0 },
        { 0x60, 0x072, 0xFD, 0, 0 },
        { 0x61, 0x074, 0x02, 0, 0 },
        { 0x62, 0x075, 0xDF, 0, 0 },
        { 0x63, 0x076, 0xDF, 0, 0 },
        { 0x64, 0x077, 0xDF, 0, 0 },
        { 0x65, 0x078, 0x02, 0, 0 },
        { 0x66, 0x07A, 0xFF, 0, 0 },
        { 0x67, 0x07B, 0x02, 0, 0 },
        { 0x68, 0x07C, 0x02, 0, 0 },
        { 0x69, 0x07D, 0x87, 0, 0 },
        { 0x6A, 0x07E, 0x87, 0, 0 },
        { 0x6B, 0x07F, 0x1F, 0, 0 },
        { 0x6C, 0x080, 0x87, 0, 0 },
        { 0x6D, 0x082, 0xFF, 1, 1 },
        { 0x6E, 0x084, 0xFF, 1, 1 },
        { 0x6F, 0x085, 0xFF, 1, 1 },
        { 0x70, 0x086, 0xFF, 1, 1 },
        { 0x71, 0x087, 0xFF, 1, 1 },
        { 0x72, 0x088, 0xFF, 1, 1 },
        { 0x73, 0x089, 0x02, 1, 1 },
        { 0x74, 0x08A, 0xFF, 1, 1 },
        { 0x75, 0x08B, 0xFF, 1, 1 },
        { 0x76, 0x08C, 0xFF, 1, 1 },
        { 0x77, 0x08D, 0xFF, 1, 1 },
        { 0x78, 0x08E, 0xFF, 1, 1 },
        { 0x79, 0x08F, 0xFF, 1, 1 },
        { 0x7A, 0x090, 0xFF, 1, 1 },
        { 0x7B, 0x091, 0xFF, 1, 1 },
        { 0x7C, 0x092, 0xFF, 1, 1 },
        { 0x7D, 0x093, 0xFF, 1, 1 },
        { 0x7E, 0x094, 0xFF, 1, 1 },
        { 0x7F, 0x095, 0xFF, 1, 1 },
        { 0x80, 0x096, 0xFF, 1, 1 },
        { 0x81, 0x097, 0xFF, 1, 0 },
        { 0x82, 0x098, 0x02, 1, 0 },
        { 0x83, 0x099, 0x02, 1, 0 },
        { 0x84, 0x09A, 0x02, 1, 0 },
        { 0x85, 0x09B, 0x02, 1, 0 },
        { 0x86, 0x09C, 0x02, 0, 0 },
        { 0x87, 0x09D, 0x02, 1, 0 },
        { 0x88, 0x09E, 0x02, 1, 0 },
        { 0x89, 0x09F, 0xFF, 0, 0 },
        { 0x8A, 0x0A0, 0xFF, 0, 0 },
        { 0x8B, 0x0A1, 0xFF, 0, 0 },
        { 0x8C, 0x0A2, 0xFF, 0, 0 },
        { 0x8D, 0x0A3, 0xFF, 0, 0 },
        { 0x8E, 0x0A4, 0xFD, 0, 0 },
        { 0x8F, 0x0A5, 0xFD, 0, 0 },
        { 0x90, 0x0A6, 0xFD, 0, 0 },
        { 0x91, 0x0A7, 0xFF, 0, 0 },
        { 0x92, 0x0A8, 0xDF, 0, 0 },
        { 0x93, 0x0A9, 0x1F, 0, 0 },
        { 0x94, 0x0AA, 0xFF, 0, 2 },
        { 0x95, 0x0AB, 0xFF, 0, 2 },
        { 0x96, 0x0AC, 0xFF, 0, 2 },
        { 0x97, 0x0AD, 0xFF, 1, 1 },
        { 0x98, 0x0AE, 0xFF, 1, 1 },
        { 0x99, 0x0AF, 0x02, 1, 0 },
        { 0x9A, 0x0B0, 0xFF, 1, 0 },
        { 0x9B, 0x0B1, 0xFF, 1, 0 },
        { 0x9C, 0x0B2, 0xFF, 1, 0 },
        { 0x9D, 0x0B3, 0xFF, 1, 0 },
        { 0x9E, 0x0B6, 0x02, 0, 0 },
        { 0x9F, 0x0B7, 0xFF, 0, 0 },
        { 0xA0, 0x0B8, 0xFF, 0, 0 },
        { 0xA1, 0x0B9, 0xFF, 0, 0 },
        { 0xA2, 0x0BA, 0xFF, 0, 0 },
        { 0xA3, 0x0BB, 0xFF, 0, 0 },
        { 0xA4, 0x0BC, 0xFF, 0, 0 },
        { 0xA5, 0x0BD, 0xFF, 0, 0 },
        { 0xA6, 0x0BE, 0xFF, 0, 0 },
        { 0xA7, 0x0BF, 0xFF, 0, 0 },
        { 0xA8, 0x0C0, 0xFF, 0, 0 },
        { 0xA9, 0x0C1, 0xFF, 0, 0 },
        { 0xAA, 0x0C2, 0xFF, 0, 0 },
        { 0xAB, 0x0C3, 0xFF, 0, 0 },
        { 0xAC, 0x0C4, 0xFF, 1, 1 },
        { 0xAD, 0x0C5, 0xFF, 1, 1 },
        { 0xAE, 0x0C6, 0xFF, 0, 0 },
        { 0xAF, 0x0C7, 0xFF, 0, 0 },
        { 0xB0, 0x0C8, 0xFF, 1, 1 },
        { 0xB1, 0x0C9, 0xFF, 1, 1 },
        { 0xB2, 0x0CA, 0xFF, 1, 1 },
        { 0xB3, 0x0CB, 0xFF, 0, 0 },
        { 0xB4, 0x0CC, 0xFF, 0, 0 },
        { 0xB5, 0x0CD, 0xFF, 0, 0 },
        { 0xB6, 0x0CE, 0xFF, 1, 0 },
        { 0xB7, 0x0CF, 0xFF, 1, 1 },
        { 0xB8, 0x0D0, 0xFF, 1, 1 },
        { 0xB9, 0x0D1, 0xFF, 1, 1 },
        { 0xBA, 0x0D2, 0xFF, 1, 1 },
        { 0xBB, 0x0D3, 0xFF, 1, 1 },
        { 0xBC, 0x0D4, 0xFF, 0, 0 },
        { 0xBD, 0x0D5, 0xFF, 0, 0 },
        { 0xBE, 0x0D6, 0xFF, 0, 0 },
        { 0xBF, 0x0D7, 0xFF, 1, 1 },
        { 0xC0, 0x0D8, 0xFF, 1, 1 },
        { 0xC1, 0x0D9, 0xFF, 1, 1 },
        { 0xC2, 0x0DA, 0xFF, 1, 0 },
        { 0xC3, 0x0DB, 0xFF, 1, 0 },
        { 0xC4, 0x0DC, 0xFF, 1, 0 },
        { 0xC5, 0x0DD, 0xFF, 1, 0 },
        { 0xC6, 0x0DE, 0xFF, 1, 1 },
        { 0xC7, 0x0DF, 0xFF, 1, 0 },
        { 0xC8, 0x0E0, 0xFF, 1, 0 },
        { 0xC9, 0x0E1, 0xFF, 1, 0 },
        { 0xCA, 0x0E2, 0xFF, 1, 0 },
        { 0xCB, 0x0E3, 0xFF, 1, 1 },
        { 0xCC, 0x0E4, 0xFF, 0, 0 },
        { 0xCD, 0x0E5, 0xFF, 0, 0 },
        { 0xCE, 0x0F0, 0xFF, 1, 0 },
        { 0xCF, 0x0F1, 0xFF, 1, 0 },
        { 0xD0, 0x0F2, 0xFF, 1, 0 },
        { 0xD1, 0x0F3, 0xFF, 1, 0 },
        { 0xD2, 0x0F4, 0xFF, 1, 0 },
        { 0xD3, 0x0F5, 0xFF, 1, 0 },
        { 0xD4, 0x0F6, 0xFF, 1, 0 },
        { 0xD5, 0x0F7, 0xFF, 1, 0 },
        { 0xD6, 0x0F8, 0xFF, 1, 0 },
        { 0xD7, 0x002, 0x02, 0, 0 },
        { 0xD8, 0x003, 0x02, 0, 0 },
        { 0xD9, 0x004, 0x02, 0, 0 },
        { 0xDA, 0x005, 0x02, 0, 0 },
        { 0xDB, 0x006, 0x02, 0, 0 },
        { 0xDC, 0x007, 0x02, 0, 0 },
        { 0xDD, 0x008, 0x02, 0, 0 },
        { 0xDE, 0x009, 0x02, 0, 0 },
        { 0xDF, 0x00A, 0x02, 0, 0 },
        { 0xE0, 0x00B, 0x02, 0, 0 },
        { 0xE1, 0x00C, 0x02, 0, 0 },
        { 0xE2, 0x00D, 0x02, 0, 0 },
        { 0xE3, 0x00E, 0x02, 1, 0 },
        { 0xE4, 0x00F, 0x02, 1, 0 },
        { 0xE5, 0x010, 0x02, 1, 0 },
        { 0xE6, 0x0E6, 0xFD, 0, 0 },
        { 0xE7, 0x0E7, 0xFD, 0, 0 },
        { 0xE8, 0x0E8, 0xFD, 0, 0 },
        { 0xE9, 0x0E9, 0xFD, 0, 0 },
        { 0xEA, 0x0EA, 0xFD, 0, 0 },
        { 0xEB, 0x0EB, 0xFD, 0, 0 },
        { 0xEC, 0x0EC, 0xFD, 0, 0 },
        { 0xED, 0x0ED, 0xFD, 0, 0 },
        { 0xEE, 0x0EE, 0xFD, 0, 0 },
        { 0xEF, 0x0EF, 0xFD, 0, 0 },
        { 0xF0, 0x0F9, 0xFD, 0, 0 },
        { 0xF1, 0x0FA, 0xFD, 0, 0 },
        { 0xF2, 0x0FB, 0xFD, 0, 0 },
        { 0xF3, 0x0FC, 0xFD, 0, 0 },
        { 0xF4, 0x0FD, 0xFD, 0, 0 },
        { 0xF5, 0x0FE, 0xFD, 0, 0 },
        { 0xF6, 0x0FF, 0xFD, 0, 0 },
        { 0xF7, 0x100, 0xFD, 0, 0 },
        { 0xF8, 0x101, 0xFD, 0, 0 },
        { 0xF9, 0x05F, 0x02, 0, 0 },
        { 0xFA, 0x073, 0x02, 0, 0 },
        { 0xFB, 0x079, 0x02, 0, 0 },
        { 0xFC, 0x081, 0x87, 0, 0 },
        { 0xFD, 0x083, 0x14, 0, 0 },
        { 0xFE, 0x0B4, 0x87, 0, 0 },
        { 0xFF, 0x0B5, 0x87, 0, 0 },
        { 0x29A },
    },
};

/* 4D65A0 */ static struct {
    /* 0x0 */ u8 x0;
    /* 0x1 */ u8 x1[7];
} lbl_804D65A0;
/* 4D65A8 */ static u8 lbl_804D65A8[6];
/* 4D65B0 */ static s32 lbl_804D65B0;

struct lbl_803B7A60_t {
    /* 0x00 */ s32 x0[4];
    /* 0x10 */ s32 x10[4];
    /* 0x20 */ s32 x20[4];
    /* 0x30 */ s32 x30[4];
    /* 0x40 */ f32 x40[4];
    /* 0x50 */ u32 x50[4];
    /* 0x60 */ u32 x60[4];
};

static const struct lbl_803B7A60_t lbl_803B7A60 = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF },
    { 0, 0, 0, 0 },
};

struct lbl_804D65A8_t {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
};

struct lbl_803D6300_t {
    u16 x0;
    u16 x2;
    bool (*x4)(void);
};

int fn_8016F180(int kind)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C.entries;
    while (curr->kind != kind) {
        if (curr->kind == 0x29A) {
            return 0;
        }
        curr++;
    }
    return curr->x4;
}

Gm_DecType gmDecisionGetType(int kind)
{
    struct lbl_803D5A4C_t* curr;
    for (curr = lbl_803D5A4C.entries; curr->kind != kind; curr++) {
        if (curr->kind == 0x29A) {
            return Gm_DecType_Flag;
        }
    }
    return curr->x5;
}

s32 fn_8016F1F0(int idx)
{
    return lbl_803D5A4C.entries[idx].kind;
}

int gm_8016F208(int kind)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C.entries;
    while (curr->kind != kind) {
        if (curr->kind == 0x29A) {
            return 0;
        }
        curr++;
    }
    if (curr->x2 == 0xDE && lbLang_IsSettingUS()) {
        return 0x102;
    }
    return curr->x2;
}

int fn_8016F280(int arg0)
{
    return gm_8016F208(arg0) - 2;
}

int gm_8016F2F8(int kind, u8 arg1)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C.entries;
    while (curr->kind != kind) {
        if (curr->kind == 0x29A) {
            return -1;
        }
        curr++;
    }
    return lbl_803D5648[curr->x2 - 2];
}

void fn_8016F344(MatchEnd* match_end)
{
    struct MatchPlayerData* curr = match_end->player_standings;
    int i;
    for (i = 0; i < 4; i++) {
        if (curr->pkind != 3) {
            pl_80039450(i);
        }
        curr++;
    }
}

/// Same table lookup as #gm_8016F208, but with a u16 result.
/// fn_8016F39C passes the looked-up id straight to HSD_SisLib_803A6368 and
/// the original code keeps it in a u16: the u16 -> int promotion is emitted
/// during argument setup (clrlwi after the arg0[count] load). Reusing the
/// int-returning gm_8016F208 (or changing its return type) instead moves or
/// drops that zero-extension and regresses gm_8016F208/fn_8016F280.
static inline u16 fn_8016F39C_GetSisTextId(int kind)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C.entries;
    while (curr->kind != kind) {
        if (curr->kind == 0x29A) {
            return 0;
        }
        curr++;
    }
    if (curr->x2 == 0xDE && lbLang_IsSettingUS()) {
        return 0x102;
    }
    return curr->x2;
}

int fn_8016F39C(HSD_Text** arg0, void* arg1, u8 arg2, u16 arg3, u8 arg4,
                u8 arg5)
{
    int idx;
    int count = 0;
    int matched;
    u8 flags;

    if (arg3 >= 0x101U) {
        return -1;
    }

    idx = arg3;
    while ((u32) idx < 0x101U) {
        matched = 0;
        if (lbl_803D5A4C.entries[idx].kind < 0xD7) {
            flags = fn_8016F180(idx);
            if (arg4 & flags) {
                if (pl_80039418(arg5, idx) != 0) {
                    matched = 1;
                }
            }
        } else {
            flags = fn_8016F180(idx);
            if (arg4 & flags) {
                if ((unsigned) fn_801701C0(arg1, arg5, idx) != 0) {
                    matched = 1;
                }
            }
        }

        if (matched != 0) {
            HSD_SisLib_803A6368(arg0[count], fn_8016F39C_GetSisTextId(idx));
            count++;
            if (count == (int) arg2) {
                break;
            }
        }
        idx++;
    }
    return count;
    PAD_STACK(8);
}

int fn_8016F548(void* arg0, u16 arg1, u8 mask, u8 player_id)
{
    int i;

    if (arg1 >= 0x101U) {
        return -1;
    }

    for (i = arg1; (u32) i < 0x101U; i++) {
        if (lbl_803D5A4C.entries[i].kind < 0xD7) {
            if (mask & (u8) fn_8016F180(i)) {
                if (pl_80039418(player_id, i) != 0) {
                    return i;
                }
            }
        } else {
            if (mask & (u8) fn_8016F180(i)) {
                if ((unsigned) fn_801701C0(arg0, player_id, i) != 0) {
                    return i;
                }
            }
        }
    }

    for (i = 0x100; i >= 0; i--) {
        if (lbl_803D5A4C.entries[i].kind < 0xD7) {
            if (mask & (u8) fn_8016F180(i)) {
                if (pl_80039418(player_id, i) != 0) {
                    return i;
                }
            }
        } else {
            if (mask & (u8) fn_8016F180(i)) {
                if ((unsigned) fn_801701C0(arg0, player_id, i) != 0) {
                    return i;
                }
            }
        }
    }

    return -1;
    PAD_STACK(24);
}

int fn_8016F740(void* arg0, u16 arg1, u8 mask, u8 player_id)
{
    struct lbl_803D5A4C_t* curr;
    u32 temp;
    int i;
    u8 flags;

    temp = arg1 + 1;
    if (temp >= 0x101U) {
        return -1;
    }

    i = temp;
    for (; (u32) i < 0x101U; i++) {
        if (lbl_803D5A4C.entries[i].kind < 0xD7) {
            flags = fn_8016F180(i);
            if (mask & flags) {
                if (pl_80039418(player_id, i) != 0) {
                    return i;
                }
            }
        } else {
            flags = fn_8016F180(i);
            if (mask & flags) {
                if ((unsigned) fn_801701C0(arg0, player_id, i) != 0) {
                    return i;
                }
            }
        }
    }

    return -1;
    PAD_STACK(8);
}

int fn_8016F870(void* arg0, u16 arg1, u8 mask, u8 player_id)
{
    struct lbl_803D5A4C_t* curr;
    int kind;
    u8 flags;
    int i;

    if (arg1 > 0x101 || arg1 == 0) {
        return -1;
    }

    for (i = arg1 - 1; i >= 0; i--) {
        kind = lbl_803D5A4C.entries[i].kind;

        if (kind < 0xD7) {
            flags = fn_8016F180(i);
            if (mask & flags) {
                if (pl_80039418(player_id, i) != 0) {
                    return i;
                }
            }
        } else {
            flags = fn_8016F180(i);
            if (mask & flags) {
                if ((unsigned) fn_801701C0(arg0, player_id, i) != 0) {
                    return i;
                }
            }
        }
    }

    return -1;
}

int fn_8016F9A8(void* arg0, u16 arg1, u8 mask, u8 player_id)
{
    int count = 0;
    int i;
    u8 flags;

    if (arg1 >= 0x101U) {
        return -1;
    }

    for (i = arg1; (u32) i < 0x101; i++) {
        if (lbl_803D5A4C.entries[i].kind < 0xD7) {
            flags = fn_8016F180(i);
            if (mask & flags) {
                if (pl_80039418(player_id, i) != 0) {
                    count++;
                }
            }
        } else {
            flags = fn_8016F180(i);
            if (mask & flags) {
                if ((unsigned) fn_801701C0(arg0, player_id, i) != 0) {
                    count++;
                }
            }
        }
    }

    return count;
    PAD_STACK(8);
}

int fn_8016FAD4(MatchEnd* rules, int kind, int flags, u8 player)
{
    struct lbl_803D5A4C_t* entry = lbl_803D5A4C.entries;
    struct MatchPlayerData* x58 = rules->player_standings;
    u8 rankings[7] = { 0 };
    s32 scores[6];
    int i;

    while (entry->kind != kind) {
        if (entry->kind == 0x29A) {
            return -1;
        }
        entry++;
    }

    for (i = 0; i < 6; i++) {
        if (x58[i].pkind != 3) {
            u16 sd = x58[i].self_destructs;
            scores[i] =
                x58[i].x20 - (x58[i].x24 - sd) + rules->sd_penalty * sd;
        }
    }

    for (i = 0; i < 6; i++) {
        if (x58[i].pkind != 3) {
            int j;
            for (j = 0; j < 6; j++) {
                if (x58[j].pkind != 3 && i != j && scores[i] < scores[j]) {
                    rankings[i]++;
                }
            }
            if (rankings[6] < rankings[i]) {
                rankings[6] = rankings[i];
            }
        }
    }

    if ((entry->x6 & 2) && (flags & 2)) {
        u8 pr = rankings[player];
        if (pr == 0) {
            return lbl_803D5648[entry->x2 - 2] * 2;
        }
        {
            int active_count = 0;
            for (i = 0; i < 4; i++) {
                if (x58[i].pkind != 3) {
                    active_count++;
                }
            }
            (void) active_count;
        }
        if (pr == rankings[6]) {
            return lbl_803D5648[entry->x2 - 2] / 2;
        }
    }

    if ((entry->x6 & 1) && (flags & 4)) {
        return (lbl_803D5648[entry->x2 - 2] / 10) * pl_80039418(player, kind);
    }

    if (entry->x5 == 1) {
        if (kind == 0xE3) {
            return lbl_803D5648[entry->x2 - 2] * x58[player].x20;
        } else if (kind == 0xE4) {
            return lbl_803D5648[entry->x2 - 2] *
                   (x58[player].x24 - x58[player].self_destructs);
        } else if (kind == 0xE5) {
            return lbl_803D5648[entry->x2 - 2] * x58[player].self_destructs;
        } else {
            return lbl_803D5648[entry->x2 - 2] * pl_80039418(player, kind);
        }
    }

    return lbl_803D5648[entry->x2 - 2];
}

int fn_8016FFD4(MatchEnd* arg0, int arg1, u8 arg2)
{
    int i;
    int count = 0;

    for (i = 0; (u32) i < 0x101U; i++) {
        if (lbl_803D5A4C.entries[i].kind < 0xD7) {
            if ((arg1 & 0xFF) & (u8) fn_8016F180(i) &&
                pl_80039418(arg2, i) != 0)
            {
                count += fn_8016FAD4(arg0, i, arg1, arg2);
            }
        } else {
            if ((arg1 & 0xFF) & (u8) fn_8016F180(i)) {
                if ((unsigned) fn_801701C0(arg0, arg2, i) != 0) {
                    count += fn_8016FAD4(arg0, i, arg1, arg2);
                }
            }
        }
    }
    return count;
    PAD_STACK(8);
}

int fn_80170110(void* arg0, int idx, int mask, u8 player_id)
{
    struct lbl_803D5A4C_t* curr = lbl_803D5A4C.entries;
    int kind = lbl_803D5A4C.entries[idx].kind;
    u8 flags;

    flags = (fn_8016F180(kind));
    if ((u8) mask & flags) {
        if (kind < 0xD7) {
            return pl_80039418(player_id, kind);
        }
        return fn_801701C0(arg0, player_id, kind);
    }
    return 0;
}

void gm_801701A0(void)
{
    lbl_804D65A0.x0 = 1;
}

void fn_801701AC(void)
{
    lbl_804D65A0.x0 = 0;
}

int fn_801701B8(void)
{
    return lbl_804D65A0.x0;
}

int fn_801701C0(MatchEnd* rules, int arg1, int arg2)
{
    u8* tmp;
    const struct lbl_803B7A60_t* zeroes = &lbl_803B7A60;
    u8* flags = (u8*) &rules->player_standings[6];
    struct MatchPlayerData* x58 = rules->player_standings;
    s32 player_net;
    s32 scores[4];
    u8 rankings[7] = { 0 };

    if (lbl_804D65A0.x0 != 0) {
        return 0;
    }
    if (rules == NULL || x58 == NULL) {
        return 0;
    }

    if (rules->match_kind == 3) {
        fn_80171B64((struct lbl_804D65A8_t*) rankings);
    } else {
        int k;

        for (k = 0; k < 6; k++) {
            if (x58[k].pkind != 3) {
                u16 xA = x58[k].self_destructs;
                scores[k] =
                    (x58[k].x20 - (x58[k].x24 - xA)) + rules->sd_penalty * xA;
            }
        }

        {
            int idx;
            for (idx = 0; idx < 6; idx++) {
                if (x58[idx].pkind != 3) {
                    int j;

                    for (j = 0; j < 6; j++) {
                        if (x58[j].pkind != 3 && idx != j &&
                            scores[idx] < scores[j])
                        {
                            rankings[idx]++;
                        }
                    }

                    if (rankings[6] < rankings[idx]) {
                        rankings[6] = rankings[idx];
                    }
                }
            }
        }
    }

    switch (arg2) {
    case 0xD7:
        if ((unsigned) fn_801701C0(rules, arg1, 0xD9) != 0) {
            return 0;
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                if (x58[i].pkind != 3 && i != arg1 && rankings[i] == 0) {
                    return 0;
                }
            }
        }
        if (rankings[arg1] == 0) {
            return 1;
        }
        return 0;

    case 0xD8:
        if ((unsigned) fn_801701C0(rules, arg1, 0xDA) != 0) {
            return 0;
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                if (x58[i].pkind != Gm_PKind_NA && i != arg1 &&
                    rankings[i] == rankings[6])
                {
                    return 0;
                }
            }
        }
        if (rankings[arg1] == rankings[6]) {
            return 1;
        }
        return 0;

    case 0xD9: {
        int k;
        for (k = 0; k < 4; k++) {
            if (x58[k].pkind != Gm_PKind_NA && k != arg1 &&
                fn_80171B00(k) != 0)
            {
                return 0;
            }
        }
        if (fn_80171B00(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    case 0xDA: {
        int k;
        for (k = 0; k < 4; k++) {
            if (x58[k].pkind != Gm_PKind_NA && k != arg1 &&
                fn_80171B2C(k) != 0)
            {
                return 0;
            }
        }
        if (fn_80171B2C(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    case 0xDB: {
        s32 vals[6];
        int i, j;
        if (x58[arg1].x20 >= 3) {
            {
                typedef struct {
                    s32 a, b, c, d;
                } copy_t;
                *(copy_t*) vals = *(copy_t*) zeroes->x0;
            }
            for (i = 0; i < 4; i++) {
                if (x58[i].pkind != 3) {
                    vals[i] = x58[i].x20;
                }
            }
            for (j = 3; j >= 1; j--) {
                for (i = 0; i < j; i++) {
                    if (vals[i] < vals[i + 1]) {
                        s32 tmp = vals[i + 1];
                        vals[i + 1] = vals[i];
                        vals[i] = tmp;
                    }
                }
            }
            if (vals[0] == x58[arg1].x20 && vals[0] >= vals[1] * 2) {
                return 1;
            }
        }
        return 0;
    }

    case 0xDC: {
        if ((unsigned) fn_801701C0(rules, arg1, 0xDB) == 0) {
            {
                int i;
                for (i = 0; i < 4; i++) {
                    if (x58[i].pkind != 3 && i != arg1 &&
                        x58[i].x20 >= x58[arg1].x20)
                    {
                        return 0;
                    }
                }
            }
            if (x58[arg1].x20 != 0) {
                return 1;
            }
        }
        return 0;
    }

    case 0xDD: {
        s32 vals[4];
        int i, j;
        if (x58[arg1].x40 >= 3) {
            {
                typedef struct {
                    s32 a, b, c, d;
                } copy_t;
                *(copy_t*) vals = *(copy_t*) zeroes->x10;
            }
            for (i = 0; i < 4; i++) {
                if (x58[i].pkind != 3) {
                    vals[i] = x58[i].x40;
                }
            }
            for (j = 3; j >= 1; j--) {
                for (i = 0; i < j; i++) {
                    if (vals[i] < vals[i + 1]) {
                        s32 tmp = vals[i + 1];
                        vals[i + 1] = vals[i];
                        vals[i] = tmp;
                    }
                }
            }
            if (vals[0] == x58[arg1].x40 && vals[0] >= vals[1] * 2) {
                return 1;
            }
        }
        return 0;
    }

    case 0xDE: {
        if ((unsigned) fn_801701C0(rules, arg1, 0xDD) == 0) {
            {
                int i;
                for (i = 0; i < 4; i++) {
                    if (x58[i].pkind != 3 && i != arg1 &&
                        x58[i].x40 >= x58[arg1].x40)
                    {
                        return 0;
                    }
                }
            }
            if (x58[arg1].x40 != 0) {
                return 1;
            }
        }
        return 0;
    }

    case 0xDF: {
        s32 vals[4];
        int i, j;
        player_net = x58[arg1].x24 - x58[arg1].self_destructs;
        if ((u32) player_net >= 3) {
            {
                typedef struct {
                    s32 a, b, c, d;
                } copy_t;
                *(copy_t*) vals = *(copy_t*) zeroes->x20;
            }
            for (i = 0; i < 4; i++) {
                if (x58[i].pkind != 3) {
                    vals[i] = x58[i].x24 - x58[i].self_destructs;
                }
            }
            for (j = 3; j >= 1; j--) {
                for (i = 0; i < j; i++) {
                    if (vals[i] < vals[i + 1]) {
                        s32 tmp = vals[i + 1];
                        vals[i + 1] = vals[i];
                        vals[i] = tmp;
                    }
                }
            }
            if ((u32) vals[0] ==
                    (u32) (x58[arg1].x24 - x58[arg1].self_destructs) &&
                vals[0] >= vals[1] * 2)
            {
                return 1;
            }
        }
        return 0;
    }

    case 0xE0: {
        if ((unsigned) fn_801701C0(rules, arg1, 0xDF) == 0) {
            {
                int i;
                for (i = 0; i < 4; i++) {
                    if (x58[i].pkind != 3 && i != arg1 &&
                        (u32) (x58[i].x24 - x58[i].self_destructs) >=
                            (u32) (x58[arg1].x24 - x58[arg1].self_destructs))
                    {
                        return 0;
                    }
                }
            }
            if ((x58[arg1].x24 - x58[arg1].self_destructs) != 0) {
                return 1;
            }
        }
        return 0;
    }

    case 0xE1: {
        s32 vals[4];
        int i, j;
        if (x58[arg1].self_destructs >= 3) {
            {
                typedef struct {
                    s32 a, b, c, d;
                } copy_t;
                *(copy_t*) vals = *(copy_t*) zeroes->x30;
            }
            for (i = 0; i < 4; i++) {
                if (x58[i].pkind != 3) {
                    vals[i] = x58[i].self_destructs;
                }
            }
            for (j = 3; j >= 1; j--) {
                for (i = 0; i < j; i++) {
                    if (vals[i] < vals[i + 1]) {
                        s32 tmp = vals[i + 1];
                        vals[i + 1] = vals[i];
                        vals[i] = tmp;
                    }
                }
            }
            if (vals[0] == x58[arg1].self_destructs && vals[0] >= vals[1] * 2)
            {
                return 1;
            }
        }
        return 0;
    }

    case 0xE2: {
        if ((unsigned) fn_801701C0(rules, arg1, 0xE1) == 0) {
            {
                int i;
                for (i = 0; i < 4; i++) {
                    if (x58[i].pkind != 3 && i != arg1 &&
                        x58[i].self_destructs >= x58[arg1].self_destructs)
                    {
                        return 0;
                    }
                }
            }
            if (x58[arg1].self_destructs != 0) {
                return 1;
            }
        }
        return 0;
    }

    case 0xE3:
        if (x58[arg1].x20 != 0) {
            return 1;
        }
        return 0;

    case 0xE4: {
        if ((x58[arg1].x24 - x58[arg1].self_destructs) != 0) {
            return 1;
        }
        return 0;
    }

    case 0xE5:
        if (x58[arg1].self_destructs != 0) {
            return 1;
        }
        return 0;

    case 0xE6:
        if ((flags[1] >> 1) & 1) {
            return 1;
        }
        return 0;

    case 0xE7:
        if ((flags[1] >> 2) & 1) {
            return 1;
        }
        return 0;

    case 0xE8:
        if (flags[1] & 1) {
            return 1;
        }
        return 0;

    case 0xE9:
        if ((flags[2] >> 7) & 1) {
            return 1;
        }
        return 0;

    case 0xEA:
        if ((flags[2] >> 6) & 1) {
            return 1;
        }
        return 0;

    case 0xEB: {
        u8 f0 = flags[0];
        if (((f0 >> 1) & 1) && ((f0 >> 5) & 1)) {
            return 1;
        }
        return 0;
    }

    case 0xEC:
        if ((flags[0] >> 7) & 1) {
            return 1;
        }
        return 0;

    case 0xED:
        if ((flags[0] >> 6) & 1) {
            return 1;
        }
        return 0;

    case 0xEE:
        if ((flags[0] >> 5) & 1) {
            return 1;
        }
        return 0;

    case 0xEF: {
        u8 f0 = flags[0];
        if (((f0 >> 4) & 1) || ((f0 >> 3) & 1) || ((f0 >> 2) & 1)) {
            return 1;
        }
        return 0;
    }

    case 0xF6:
        if (((flags[2] >> 5) & 1) && ((flags[0] >> 7) & 1)) {
            return 1;
        }
        return 0;

    case 0xF7:
        if ((flags[2] >> 3) & 1) {
            return 1;
        }
        return 0;

    case 0xF8:
        if ((flags[2] >> 4) & 1) {
            return 1;
        }
        return 0;

    case 0xF0:
        if (flags[0] & 1) {
            return 1;
        }
        return 0;

    case 0xF1:
        if ((flags[1] >> 7) & 1) {
            return 1;
        }
        return 0;

    case 0xF2:
        if ((flags[1] >> 6) & 1) {
            return 1;
        }
        return 0;

    case 0xF3:
        if ((flags[1] >> 5) & 1) {
            return 1;
        }
        return 0;

    case 0xF4:
        if ((flags[1] >> 4) & 1) {
            return 1;
        }
        return 0;

    case 0xF5:
        if ((flags[1] >> 3) & 1) {
            return 1;
        }
        return 0;

    case 0xF9: {
        f32 vals[4];
        int i, j;
        {
            typedef struct {
                s32 a, b, c, d;
            } copy_t;
            *(copy_t*) vals = *(copy_t*) zeroes->x40;
        }
        for (i = 0; i < 4; i++) {
            if (x58[i].pkind != 3) {
                vals[i] = pl_800407C8(i);
            }
        }
        for (j = 3; j >= 1; j--) {
            for (i = 0; i < j; i++) {
                if (vals[i] < vals[i + 1]) {
                    f32 tmp = vals[i + 1];
                    vals[i + 1] = vals[i];
                    vals[i] = tmp;
                }
            }
        }
        if (vals[0] == pl_800407C8(arg1) && vals[0] > 2.0f * vals[1]) {
            return 1;
        }
        return 0;
    }

    case 0xFA:
        if ((unsigned) fn_8016F160(arg1, 0x60) != 0 &&
            rankings[arg1] != rankings[6])
        {
            return 1;
        }
        return 0;

    case 0xFB: {
        f32 min_dmg = 0.0f;
        int i;
        for (i = 0; i < 4; i++) {
            if (x58[i].pkind != 3 && min_dmg > pl_80040870(i)) {
                min_dmg = pl_80040870(i);
            }
        }
        if (min_dmg < 0.0f && min_dmg == pl_80040870(arg1)) {
            return 1;
        }
        return 0;
    }

    case 0xFC: {
        {
            int i;
            for (i = 0; i < 4; i++) {
                if (x58[i].pkind != Gm_PKind_NA && i != arg1 &&
                    (x58[i].x3 & 1))
                {
                    return 0;
                }
            }
        }
        if (rules->match_kind == 3) {
            {
                int i;
                for (i = 0; i < 4; i++) {
                    if (x58[i].pkind != Gm_PKind_NA && i != arg1 &&
                        rankings[i] == 0)
                    {
                        return 0;
                    }
                }
            }
            if (!(x58[arg1].x3_b7 & 1) && rankings[arg1] == 0 &&
                x58[arg1].x20 == 0)
            {
                return 1;
            }
        } else {
            int mode;
            if (fn_80171A88() == 0) {
                mode = 0;
            } else {
                mode = 6;
            }
            if (mode == 0) {
                {
                    int i;
                    for (i = 0; i < 4; i++) {
                        if (x58[i].pkind != Gm_PKind_NA && i != arg1 &&
                            x58[i].is_big_loser == 0)
                        {
                            return 0;
                        }
                    }
                }
                if (!(x58[arg1].x3_b7 & 1) && x58[arg1].is_big_loser == 0 &&
                    x58[arg1].x20 == 0)
                {
                    return 1;
                }
            } else {
                if (!(x58[arg1].x3_b7 & 1) && x58[arg1].x20 == 0) {
                    return 1;
                }
            }
        }
        return 0;
    }

    case 0xFD:
        if ((unsigned) pl_800408DC(arg1) != 0 &&
            rules->x7 == (unsigned) pl_800408DC(arg1))
        {
            return 1;
        }
        return 0;

    case 0xFE: {
        u32 tmp, k;
        u32 vals[4];
        int i, j;
        unsigned int threshold;
        if (pl_800408B8(arg1) == 0) {
            return 0;
        }
        threshold = pl_80038914()->x13C;
        if (pl_800408B8(arg1) < threshold) {
            int mode;
            if (fn_80171A88() == 0) {
                mode = 0;
            } else {
                mode = 6;
            }
            if (mode == 0) {
                {
                    typedef struct {
                        u32 a, b, c, d;
                    } copy_t;
                    *(copy_t*) vals = *(copy_t*) zeroes->x50;
                }
                for (i = 0; i < 4; i++) {
                    if (x58[i].pkind != 3 && pl_800408B8(i) != 0) {
                        vals[i] = pl_800408B8(i);
                    }
                }
                for (j = 3; j >= 1; j--) {
                    for (k = 0; k < j; k++) {
                        if (vals[k] > vals[k + 1]) {
                            tmp = vals[k + 1];
                            vals[k + 1] = vals[k];
                            vals[k] = tmp;
                        }
                    }
                }
                if (vals[0] == pl_800408B8(arg1) && vals[0] <= vals[1] / 2) {
                    return 1;
                }
            } else {
                return 1;
            }
        }
        return 0;
    }

    case 0xFF: {
        u32 tmp, k;
        u32 vals[4];
        int i, j;
        unsigned int threshold;
        threshold = pl_80038914()->x140;
        if (pl_80040894(arg1) > threshold) {
            int mode;
            if (fn_80171A88() == 0) {
                mode = 0;
            } else {
                mode = 6;
            }
            if (mode == 0) {
                {
                    typedef struct {
                        u32 a, b, c, d;
                    } copy_t;
                    *(copy_t*) vals = *(copy_t*) zeroes->x60;
                }
                for (i = 0; i < 4; i++) {
                    if (x58[i].pkind != 3) {
                        vals[i] = pl_80040894(i);
                    }
                }
                for (j = 3; j >= 1; j--) {
                    for (k = 0; k < j; k++) {
                        if (vals[k] < vals[k + 1]) {
                            tmp = vals[k + 1];
                            vals[k + 1] = vals[k];
                            vals[k] = tmp;
                        }
                    }
                }
                if (vals[0] == pl_80040894(arg1) && vals[0] >= vals[1] * 2) {
                    return 1;
                }
            } else {
                return 1;
            }
        }
        return 0;
    }

    default:
        return 0;
    }
}

int fn_80171A88(void)
{
    int result = 0;
    if (gm_IsCurrently1PMode_inline()) {
        result = fn_8017E0E4();
        if (result == -1) {
            result = 1;
        }
    }
    return result;
}

void fn_80171AD4(void)
{
    memzero(&lbl_8046DBC8, sizeof(lbl_8046DBC8));
}

bool fn_80171B00(int arg0)
{
    if (lbl_8046DBC8.x2[arg0].x0 != 0) {
        return true;
    }
    return false;
}

bool fn_80171B2C(int arg0)
{
    if (lbl_8046DBC8.x1 != 0 && lbl_8046DBC8.x2[arg0].x1 != 0) {
        return true;
    }
    return false;
}

void fn_80171B64(struct lbl_804D65A8_t* arg0)
{
    arg0->x0 = lbl_804D65A8[0];
    arg0->x1 = lbl_804D65A8[1];
    arg0->x2 = lbl_804D65A8[2];
    arg0->x3 = lbl_804D65A8[3];
    arg0->x4 = lbl_804D65A8[4];
    arg0->x5 = lbl_804D65A8[5];
    arg0->x6 = (u8) lbl_804D65B0;
}

int fn_80171BA4(void* arg0)
{
    int player;
    int j;
    int ko_count;
    int falls;
    u32 self_destructs;
    int team;
    int result;
    u8* rules;
    int scores[6];

    rules = arg0;
    memzero(scores, sizeof(scores));
    memzero(lbl_804D65A8, sizeof(lbl_804D65A8));
    lbl_804D65B0 = Gm_PKind_Human;

    for (player = 0; player < 6; player++) {
        if (Player_GetPlayerSlotType(player) != Gm_PKind_NA) {
            ko_count = 0;
            falls = Player_GetFalls(player);
            self_destructs = Player_GetSelfDestructs(player);
            if (rules[6] == 1) {
                team = Player_GetTeam(player);
                for (j = 0; j < 6; j++) {
                    if (Player_GetPlayerSlotType(j) != Gm_PKind_NA) {
                        if (team != Player_GetTeam(j)) {
                            if (player != j) {
                                ko_count +=
                                    Player_GetKOsByPlayerIndex(player, j);
                            }
                        } else {
                            self_destructs +=
                                Player_GetKOsByPlayerIndex(player, j);
                            falls += Player_GetKOsByPlayerIndex(player, j);
                        }
                    }
                }
            } else {
                for (j = 0; j < 6; j++) {
                    if (Player_GetPlayerSlotType(j) != Gm_PKind_NA) {
                        if (player != j) {
                            ko_count += Player_GetKOsByPlayerIndex(player, j);
                        } else {
                            self_destructs +=
                                Player_GetKOsByPlayerIndex(player, j);
                            falls += Player_GetKOsByPlayerIndex(player, j);
                        }
                    }
                }
            }
            scores[player] = (ko_count - (falls -= (int) self_destructs)) +
                             ((int) self_destructs * (s8) rules[0xC]);
        }
    }

    for (player = 0; player < 6; player++) {
        result = Player_GetPlayerSlotType(player);
        if (result != Gm_PKind_NA) {
            for (j = 0; j < 6; j++) {
                if (Player_GetPlayerSlotType(j) != Gm_PKind_NA &&
                    player != j && scores[player] < scores[j])
                {
                    lbl_804D65A8[player] += 1;
                }
            }
            if (lbl_804D65B0 < (result = lbl_804D65A8[player])) {
                lbl_804D65B0 = result;
            }
        }
    }
    return result;
}

void fn_80171DC4(void)
{
    int i;
    MatchEnd* rules = gm_8016B774();

    fn_80171BA4(rules);

    if ((lbl_8046DBC8.x0 == 0) && (0 < lbl_804D65B0)) {
        lbl_8046DBC8.x0 = 1;
        lbl_8046DBC8.x1 = 1;
        for (i = 0; i < 6; i++) {
            if (rules->player_standings[i].pkind != 3) {
                if (lbl_804D65A8[i] == 0) {
                    lbl_8046DBC8.x2[i].x0 = 1;
                } else if ((s32) lbl_804D65A8[i] == lbl_804D65B0) {
                    lbl_8046DBC8.x2[i].x1 = 1;
                }
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            if (rules->player_standings[i].pkind != 3) {
                if (lbl_8046DBC8.x2[i].x0 == 1 && lbl_804D65A8[i] != 0) {
                    lbl_8046DBC8.x2[i].x0 = 0;
                }
                if (lbl_8046DBC8.x2[i].x1 == 1 &&
                    (lbl_804D65A8[i] == 0 ||
                     (s32) lbl_804D65A8[i] != lbl_804D65B0))
                {
                    lbl_8046DBC8.x2[i].x1 = 0;
                }
            }
        }
    }
}

bool gm_801720B4(void)
{
    if (gm_8016B3D8()) {
        return fn_8017E160();
    }
    return gm_GetStartMeleeRules()->is_teams == true;
}

bool gm_801720F8(void)
{
    if (gm_8016B3D8()) {
        return true;
    }
    return gm_GetStartMeleeRules()->match_kind == 1;
}

int gm_80172140(void)
{
    Unk1PData* temp_r3 = fn_8017DF28();
    if (temp_r3 != NULL) {
        return temp_r3->xC.x10;
    }
    return 0;
}

void gm_80172174(void)
{
    memzero(gmMainLib_8015CCE4(), sizeof(struct gmm_x0_44_t));
}

bool gm_8017219C(u32 arg0)
{
    if (gmMainLib_8015D94C(arg0) != 0 && gmMainLib_8015D8D8(arg0) != 0) {
        return true;
    }
    return false;
}

static inline bool gm_801721EC_1(u32 i)
{
    if (gmMainLib_8015D94C(i) && gmMainLib_8015D8D8(i)) {
        return true;
    }
    return false;
}

static inline bool gm_801721EC_2(void)
{
    s32 i;
    for (i = 0; i < 0x42; i++) {
        if (gm_801721EC_1(i)) {
            return true;
        }
    }
    return false;
}

static inline bool gm_801721EC_3(u32 j)
{
    if (gmMainLib_8015DA1C(j)) {
        return true;
    }
    return false;
}

static inline bool gm_801721EC_4(void)
{
    s32 j;
    for (j = 0; j < TY_TROPHY_COUNT; j++) {
        if (gm_801721EC_3(j)) {
            return true;
        }
    }
    return false;
}

bool gm_801721EC(void)
{
    if (gm_801721EC_2() || gm_801721EC_4()) {
        return true;
    }
    return false;
}

bool fn_801722BC(void)
{
    if (fn_80163FA4(0x1E) == 0x1E) {
        return true;
    }
    return false;
}

bool fn_801722F4(void)
{
    if (fn_80163FA4(0x33) == 0x33) {
        return true;
    }
    return false;
}

bool fn_8017232C(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (*gmMainLib_8015D194(i) == 4) {
            return true;
        }
    }
    return false;
}

bool fn_80172380(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (*gmMainLib_8015D2BC(i) == 4) {
            return true;
        }
    }
    return false;
}

bool fn_801723D4(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (*gmMainLib_8015D3E4(i) == 4) {
            return true;
        }
    }
    return false;
}

bool fn_80172428(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D1AC(i) == 1) {
            return true;
        }
    }
    return false;
}

bool fn_80172478(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D2D4(i) == 1) {
            return true;
        }
    }
    return false;
}

bool fn_801724C8(void)
{
    return false;
}

bool fn_801724D0(void)
{
    if (gm_GetVsPlayMatchTotal() >= 0x64) {
        return true;
    }
    return false;
}

bool fn_80172504(void)
{
    if (gm_GetVsPlayMatchTotal() >= 0x3E8) {
        return true;
    }
    return false;
}

bool fn_80172538(void)
{
    if (gm_GetVsPlayMatchTotal() >= 0x2710) {
        return true;
    }
    return false;
}

bool fn_8017256C(void)
{
    if (gm_GetVsPlayMatchTotal() >= 0x186A0) {
        return true;
    }
    return false;
}

bool fn_801725A8(void)
{
    if (gm_GetVsPlayMatchTotal() >= 0xF4240) {
        return true;
    }
    return false;
}

bool fn_801725E4(void)
{
    if (lbLang_GetLanguageSetting() == LANG_JP &&
        gm_GetVsPlayMatchTotal() >= 0x1A90)
    {
        return true;
    }
    return false;
}

bool fn_80172624(void)
{
    if (lbLang_GetLanguageSetting() == LANG_US &&
        gm_GetVsPlayMatchTotal() >= 0x1383)
    {
        return true;
    }
    return false;
}

bool fn_80172664(void)
{
    if (gm_GetVsPlayMatchTotal() >= 0xC350) {
        return true;
    }
    return false;
}

bool fn_80172698(void)
{
    if (Toy_GetTrophyTotal() >= 0x32) {
        return true;
    }
    return false;
}

bool fn_801726CC(void)
{
    if (Toy_GetTrophyTotal() >= 0x64) {
        return true;
    }
    return false;
}

bool fn_80172700(void)
{
    if (Toy_GetTrophyTotal() >= 0x96) {
        return true;
    }
    return false;
}

bool fn_80172734(void)
{
    if (Toy_GetTrophyTotal() >= 0xC8) {
        return true;
    }
    return false;
}

bool fn_80172768(void)
{
    if (Toy_GetTrophyTotal() >= 0xFA) {
        return true;
    }
    return false;
}

struct lbl_803D6300_t lbl_803D6300[] ATTRIBUTE_ALIGN(8) = {
    { 0x0016, 0xFFFF, fn_801735F0 },
    { 0x0017, 0x0001, fn_80173644 },
    { 0x0018, 0xFFFF, fn_80173510 },
    { 0x0019, 0xFFFF, NULL },
    { 0x001A, 0xFFFF, NULL },
    { 0x001B, 0xFFFF, fn_8017367C },
    { 0x001C, 0xFFFF, gm_80164ABC },
    { 0x001D, 0xFFFF, gm_80164600 },
    { 0x001E, 0x0040, fn_80162CCC },
    { 0x001F, 0x0040, gm_80162EC8 },
    { 0x0020, 0x0040, fn_801630C4 },
    { 0x0021, 0x0040, gm_80162D1C },
    { 0x0022, 0x0040, gm_80162F18 },
    { 0x0023, 0x0040, gm_80163114 },
    { 0x0024, 0x0010, fn_801722BC },
    { 0x0025, 0x0010, fn_801722F4 },
    { 0x0026, 0x0080, gmMainLib_8015D508 },
    { 0x0027, 0x0020, fn_80163D24 },
    { 0x0028, 0x0020, fn_80163D74 },
    { 0x0029, 0x0040, fn_8017232C },
    { 0x002A, 0x0040, fn_80172428 },
    { 0x002B, 0x0040, fn_80172380 },
    { 0x002C, 0x0040, fn_80172478 },
    { 0x002D, 0x0040, fn_801723D4 },
    { 0x002E, 0x0040, fn_801724C8 },
    { 0x002F, 0x0001, fn_801724D0 },
    { 0x0030, 0x0001, fn_80172504 },
    { 0x0031, 0x0001, fn_80172538 },
    { 0x0032, 0x0001, fn_8017256C },
    { 0x0033, 0x0001, fn_801725A8 },
    { 0x0034, 0x0001, fn_801725E4 },
    { 0x0035, 0x0001, fn_80172624 },
    { 0x0036, 0x0001, fn_80172664 },
    { 0x0037, 0xFFFF, fn_80172698 },
    { 0x0038, 0xFFFF, fn_801726CC },
    { 0x0039, 0xFFFF, fn_80172700 },
    { 0x003A, 0xFFFF, fn_80172734 },
    { 0x003B, 0xFFFF, fn_80172768 },
    { 0x003C, 0xFFFF, un_80304470 },
    { 0x003D, 0xFFFF, un_80304510 },
    { 0x0041, 0x0010, gmMainLib_8015CF94 },
    { 0x0042, 0x0000, NULL },
};

bool fn_8017279C(int arg0, u16 arg1)
{
    struct lbl_803D6300_t* cur = lbl_803D6300;
    while (cur->x0 != 0x42) {
        if (cur->x0 == arg0 && cur->x2 & arg1) {
            if (cur->x4 != NULL) {
                return cur->x4();
            }
        }
        cur++;
    }
    return false;
}

void fn_8017280C(void)
{
    if (gmMainLib_8015D94C(0x18) != 0) {
        gmMainLib_8015EE54();
    } else {
        gmMainLib_8015EE68();
    }
    if (gmMainLib_8015D94C(0x17) != 0) {
        gmMainLib_8015EE1C();
    } else {
        gmMainLib_8015EE30();
    }
    if (gmMainLib_8015D94C(0x16) != 0) {
        gmMainLib_8015EDE4();
    } else {
        gmMainLib_8015EDF8();
    }
    if (gmMainLib_8015D94C(0x1B) != 0) {
        gmMainLib_8015EEA0();
        return;
    }
    gmMainLib_8015EEB4();
}

static inline s32 tryUnlock(int i, u16 mask)
{
    if (!gmMainLib_8015D94C(i) && fn_8017279C(i, mask) != 0) {
        return gmMainLib_8015D818(i);
    }
    return 0;
}

int gm_80172898(u16 arg0)
{
    int i;
    int count = 0;

    for (i = 0; i < 0x42; i++) {
        if (tryUnlock(i, arg0) != 0) {
            count++;
        }
    }
    if (Toy_803048C0(0xE6) > 0 && gmMainLib_8015D94C(0x3F) == 0) {
        gmMainLib_8015D818(0x3F);
    }
    if (Toy_803048C0(0xC9) > 0 && gmMainLib_8015D94C(0x40) == 0) {
        gmMainLib_8015D818(0x40);
    }
    fn_8017280C();
    return count;
}

void gm_8017297C(void)
{
    int i;
    for (i = 0; i < 0x42; i++) {
        if (gmMainLib_8015D94C(i) == 0) {
            u32* temp_r31 = gmMainLib_8015D804(i);
            *temp_r31 = lbTime_GetTimeInSeconds();
            gmMainLib_8015D8FC(i);
            gmMainLib_8015D8B0(i);
        }
    }
}

static inline bool inline3(int i)
{
    struct lbl_803D6300_t* cur;
    for (cur = lbl_803D6300; cur->x0 != 0x42; cur++) {
        if (cur->x0 == i && (int) cur->x2 != 0) {
            if (cur->x4 == NULL) {
                return false;
            } else {
                return !cur->x4();
            }
        }
    }
    return false;
}

void gm_801729EC(void)
{
    bool var_r0;
    int i;
    int j;
    u8 temp_r30;

    for (i = 0; i < 0x42; i++) {
        if (inline3(i)) {
            u32* tmp = gmMainLib_8015D804(i);
            *tmp = 0;
            gmMainLib_8015D8B0(i);
            gmMainLib_8015D924(i);
        }
    }

    for (i = 0; i < 11; i++) {
        if (gm_IsCKindUnlocked(gm_GetCKindByUnlockIndex(i)) == 0) {
            gmMainLib_8015D924(fn_80160710(i));
        }
    }

    for (i = 0; i < 11; i++) {
        u16* tmp;
        temp_r30 = fn_801607A8(i);
        tmp = gmMainLib_8015EDA4();
        if (!(*tmp & (1 << i))) {
            gmMainLib_8015D924((u32) fn_801607F4(temp_r30));
        }
    }

    if (Toy_803048C0(0xE6) == 0) {
        u32* tmp = gmMainLib_8015D804(0x3F);
        *tmp = 0;
        gmMainLib_8015D8B0(0x3FU);
        gmMainLib_8015D924(0x3FU);
    }
    if (Toy_803048C0(0xC9) == 0) {
        u32* tmp = gmMainLib_8015D804(0x40);
        *tmp = 0;
        gmMainLib_8015D8B0(0x40U);
        gmMainLib_8015D924(0x40U);
    }
    if (Toy_803048C0(0x96) == 0) {
        u32* tmp = gmMainLib_8015D804(0x1A);
        *tmp = 0;
        gmMainLib_8015D8B0(0x1AU);
        gmMainLib_8015D924(0x1AU);
    }
    fn_8017280C();
}

bool gm_80172BC4(void)
{
    if (gmMainLib_8015D94C(0x19) == 0) {
        gmMainLib_8015D818(0x19);
        return true;
    }
    return false;
}

bool gm_80172C04(void)
{
    if (gmMainLib_8015D94C(0x1A) == 0) {
        gmMainLib_8015D818(0x1A);
        return true;
    }
    return false;
}

void gm_80172C44(u32 arg0)
{
    gmMainLib_8015DA68(arg0);
    gmMainLib_8015D984(arg0);
}

bool fn_80172C78(int arg0)
{
    if (gmMainLib_8015D984(arg0) != 0) {
        gmMainLib_8015DA68(arg0);
        return true;
    }
    return false;
}

static const struct lbl_803B7AD0_t {
    u8 x0;
    u8 x1;
    u8 x2;
    u16 x4;
} lbl_803B7AD0[0xB] = {
    { 0, 5, 2, 0x3E8 }, { 1, 5, 2, 0x320 },  { 2, 5, 2, 0x190 },
    { 3, 5, 2, 0x2BC }, { 4, 5, 2, 0x032 },  { 5, 5, 2, 0x12C },
    { 6, 5, 2, 0x1F4 }, { 7, 5, 2, 0x064 },  { 8, 5, 2, 0x384 },
    { 9, 5, 2, 0x0C8 }, { 10, 5, 2, 0x258 },
};

static inline const struct lbl_803B7AD0_t* inline2(u8 cpu_ckind)
{
    int i;
    u8 temp_r3 = gm_CKindToUnlockIndex(cpu_ckind);
    const struct lbl_803B7AD0_t* tmp = lbl_803B7AD0;
    for (i = 0; i < 0xB; i++) {
        if (temp_r3 == tmp[i].x0) {
            return &tmp[i];
        }
    }
    return NULL;
}

/// @returns CPU level (0-9)
u8 gm_DecideChallengerCpuLevel(u8 cpu_ckind, UNUSED u8 human_nametag)
{
    int var_r0;
    const struct lbl_803B7AD0_t* var_r31 = inline2(cpu_ckind);

    var_r0 = var_r31->x1 - var_r31->x2 * gmMainLib_8015DB6C(
                                             gm_CKindToUnlockIndex(cpu_ckind));
    if (var_r0 < 0) {
        var_r0 = 0;
    } else if (var_r0 > 9) {
        var_r0 = 9;
    }
    return var_r0;
}

u8 gm_80172D78(void)
{
    u32* temp_r31 = &gmMainLib_8015ED98()->x4;
    if (!gm_IsCKindUnlocked(CKind_Mewtwo) && *temp_r31 >= 0x11940) {
        return CKind_Mewtwo;
    }
    return ChKind_None;
}

static inline const struct lbl_803B7AD0_t* inline1(u32 arg0)
{
    const struct lbl_803B7AD0_t* var_r29 = NULL;
    u16 var_r30 = -1;
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (lbl_803B7AD0[i].x4 <= arg0 &&
            !gm_IsCKindUnlocked(gm_GetCKindByUnlockIndex(lbl_803B7AD0[i].x0)))
        {
            if (lbl_803B7AD0[i].x4 < var_r30) {
                var_r30 = lbl_803B7AD0[i].x4;
                var_r29 = &lbl_803B7AD0[i];
            }
        }
    }
    return var_r29;
}

u8 gm_80172DD4(u32 arg0)
{
    const struct lbl_803B7AD0_t* var_r29 = inline1(arg0);
    PAD_STACK(8);
    if (var_r29 != NULL) {
        return gm_GetCKindByUnlockIndex(var_r29->x0);
    }
    return ChKind_None;
}

u8 gm_80172E74(void)
{
    int i;
    int count = 0;

    for (i = 0; i < SELKIND_COUNT; i++) {
        if (gm_SelKindToUnlockIndex(i) == NUM_UNLOCKABLE_CHARACTERS &&
            gmMainLib_8015CFCC(i))
        {
            count += 1;
        }
    }
    if (count >= 0xE && !gm_IsCKindUnlocked(CKind_Mars)) {
        return CKind_Mars;
    }
    return ChKind_None;
}

u16 gm_80172F00(u32 arg0)
{
    if (arg0 >= 0x32 && !gm_80164430(0xF)) {
        return 0xF;
    }
    if (arg0 >= 0x64 && !gm_80164430(0x12)) {
        return 0x12;
    }
    if (arg0 >= 0x96 && !gm_80164430(0x18)) {
        return 0x18;
    }
    if (arg0 >= 0xC8 && !gm_80164430(0x17)) {
        return 0x17;
    }
    return 0x148;
}

bool fn_80172FAC(void)
{
    int j;
    bool var_r31 = true;
    int i;

    for (j = 0; j < 0x19; j++) {
        if (j != 3 && gmMainLib_8015D4A8(j) == 0) {
            var_r31 = false;
            break;
        }
    }
    if (var_r31) {
        return true;
    }

    var_r31 = true;
    for (i = 0; i < 0x19; i++) {
        if (i != 3 && gmMainLib_8015D0F4(i) == 0) {
            var_r31 = false;
            break;
        }
    }
    if (var_r31) {
        return true;
    }

    var_r31 = true;
    for (i = 0; i < 0x19; i++) {
        if (i != 3 && gmMainLib_8015D21C(i) == 0) {
            var_r31 = false;
            break;
        }
    }
    return var_r31;
}

static inline s32 fn_80173098_CountUnlocked(void)
{
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D0F4(i) != 0) {
            count++;
        } else if (gmMainLib_8015D21C(i) != 0) {
            count++;
        } else if (gmMainLib_8015D344(i) != 0) {
            count++;
        }
    }
    return count;
}

u8 fn_80173098(int arg0)
{
    Unk1PData* temp_r3;
    UnkAdventureData* temp_r31;
    int unlocked_chars_count;

    temp_r3 = fn_8017DEC8(arg0);
    if (temp_r3->xC.xD == 0) {
        if (temp_r3->x0.ckind == CKind_Mars &&
            !gm_IsCKindUnlocked(CKind_Emblem))
        {
            return CKind_Emblem;
        }
        if (temp_r3->x0.ckind == CKind_Mario &&
            !gm_IsCKindUnlocked(CKind_DrMario))
        {
            return CKind_DrMario;
        }
    }
    unlocked_chars_count = fn_80173098_CountUnlocked();
    (void) unlocked_chars_count;
    if (unlocked_chars_count >= 10 && !gm_IsCKindUnlocked(CKind_CLink)) {
        return CKind_CLink;
    }
    if (fn_80172FAC() && !gm_IsCKindUnlocked(CKind_GameWatch)) {
        return CKind_GameWatch;
    }
    if (arg0 == 0) {
        temp_r31 = gm_GetAdventureData();
        if (!gm_IsCKindUnlocked(CKind_Luigi) && temp_r31->x74 != 0 &&
            temp_r31->x75 != 0)
        {
            return CKind_Luigi;
        }
    }
    if (!gm_IsCKindUnlocked(CKind_Purin)) {
        return CKind_Purin;
    }
    return ChKind_None;
}

u8 gm_80173224(int arg0, int arg1)
{
    u8 ckind = ChKind_None;
    if (arg1 != 0) {
        ckind = fn_80173098(arg0);
    }
    if (ckind == ChKind_None) {
        ckind = gm_80172E74();
    }
    return ckind;
}

/// check for event character unlocks?
u8 gm_801732D8(u8 arg0)
{
    if (!gm_IsCKindUnlocked(CKind_Ganon) && gm_801BEBC0(arg0) == 0x1C) {
        return CKind_Ganon;
    }
    if (!gm_IsCKindUnlocked(CKind_Pichu) && gm_801BEBC0(arg0) == 0xE) {
        return CKind_Pichu;
    }
    return ChKind_None;
}

u16 gm_8017335C(void)
{
    int var_r31 = 1;
    int i;
    for (i = 0; i < 0x33; i++) {
        if (!gmMainLib_8015CEFC(i)) {
            var_r31 = 0;
            break;
        }
    }
    if (var_r31 == 1 && !gm_80164430(0x20)) {
        return 0x20;
    }
    return 0x148;
}

u8 gm_801733D8(void)
{
    if (!gm_IsCKindUnlocked(CKind_GameWatch) && fn_80172FAC()) {
        return CKind_GameWatch;
    }
    return ChKind_None;
}

u16 gm_8017341C(void)
{
    if (gmMainLib_8015D5DC() && !gm_80164430(0x1C)) {
        return 0x1C;
    }
    return 0x148;
}

u8 gm_80173460(s8 arg0)
{
    if (!gm_IsCKindUnlocked(CKind_Falco)) {
        return CKind_Falco;
    }
    return ChKind_None;
}

u16 gm_80173498(void)
{
    if (!gm_80164430(0x1E)) {
        return 0x1E;
    }
    return 0x148;
}

u16 gm_801734D0(u32 arg0)
{
    if (arg0 >= 0x9C40 && !gm_80164430(0x1D)) {
        return 0x1D;
    }
    return 0x148;
}

bool fn_80173510(void)
{
    u16* temp_r31 = gmMainLib_8015EDA4();
    bool var_r30 = true;
    int i;

    if (gmMainLib_8015EDC8()->x5 == 0) {
        for (i = 0; i < 11; i++) {
            if (i != 6 && i != 7 && i != 8 && i != 9 && i != 10 &&
                !(*temp_r31 & (1LL << i)))
            {
                var_r30 = false;
                break;
            }
        }
        if (var_r30 != 0) {
            gmMainLib_8015EDC8()->x5 = true;
        }
    }
    return gmMainLib_8015EDC8()->x5;
}

bool fn_801735F0(void)
{
    if (!gmMainLib_8015EDC8()->x4 && gm_80164ABC()) {
        gmMainLib_8015EDC8()->x4 = true;
    }
    return gmMainLib_8015EDC8()->x4;
}

bool fn_80173644(void)
{
    if (gmMainLib_8015EDC8()->x0 >= 0x1388) {
        return true;
    }
    return false;
}

bool fn_8017367C(void)
{
    if (!gmMainLib_8015EDC8()->x6 && gm_80164ABC() && gm_80164600()) {
        gmMainLib_8015EDC8()->x6 = true;
    }
    return gmMainLib_8015EDC8()->x6;
}
