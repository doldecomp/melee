#include "hsd_3B34.h"

#include <placeholder.h>

#include <setjmp.h>

extern u8 hsd_804D2E70[2084];
extern u8* hsd_804D79B8;
extern u8* hsd_804D79BC;
extern s32 hsd_804D79C0;
extern s32 hsd_804D79C4;
extern u8 hsd_804D79C8;

typedef struct JpegWorkData {
    s32 luma[0x100];
    s32 cb[0x40];
    s32 cr[0x40];
    s32 coeff[0x40];
    s32 prev_dc[3];
} JpegWorkData;

typedef struct JpegState {
    __jmp_buf jmp;
    u8 unk_f8[0x20];
    JpegWorkData work;
} JpegState;

typedef struct JpegQuantTables {
    u8 luma[0x40];
    u8 chroma[0x40];
} JpegQuantTables;

u8 lbl_80431090[0x5A8] = {
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x04, 0x00, 0x0A, 0x00, 0x0B, 0x00, 0x0C, 0x00, 0x1A, 0x00, 0x1B,
    0x00, 0x1C, 0x00, 0x3A, 0x00, 0x3B, 0x00, 0x78, 0x00, 0x79, 0x00, 0x7A,
    0x00, 0x7B, 0x00, 0xF8, 0x00, 0xF9, 0x00, 0xFA, 0x01, 0xF6, 0x01, 0xF7,
    0x01, 0xF8, 0x01, 0xF9, 0x01, 0xFA, 0x03, 0xF6, 0x03, 0xF7, 0x03, 0xF8,
    0x03, 0xF9, 0x03, 0xFA, 0x07, 0xF6, 0x07, 0xF7, 0x07, 0xF8, 0x07, 0xF9,
    0x0F, 0xF4, 0x0F, 0xF5, 0x0F, 0xF6, 0x0F, 0xF7, 0x7F, 0xC0, 0xFF, 0x82,
    0xFF, 0x83, 0xFF, 0x84, 0xFF, 0x85, 0xFF, 0x86, 0xFF, 0x87, 0xFF, 0x88,
    0xFF, 0x89, 0xFF, 0x8A, 0xFF, 0x8B, 0xFF, 0x8C, 0xFF, 0x8D, 0xFF, 0x8E,
    0xFF, 0x8F, 0xFF, 0x90, 0xFF, 0x91, 0xFF, 0x92, 0xFF, 0x93, 0xFF, 0x94,
    0xFF, 0x95, 0xFF, 0x96, 0xFF, 0x97, 0xFF, 0x98, 0xFF, 0x99, 0xFF, 0x9A,
    0xFF, 0x9B, 0xFF, 0x9C, 0xFF, 0x9D, 0xFF, 0x9E, 0xFF, 0x9F, 0xFF, 0xA0,
    0xFF, 0xA1, 0xFF, 0xA2, 0xFF, 0xA3, 0xFF, 0xA4, 0xFF, 0xA5, 0xFF, 0xA6,
    0xFF, 0xA7, 0xFF, 0xA8, 0xFF, 0xA9, 0xFF, 0xAA, 0xFF, 0xAB, 0xFF, 0xAC,
    0xFF, 0xAD, 0xFF, 0xAE, 0xFF, 0xAF, 0xFF, 0xB0, 0xFF, 0xB1, 0xFF, 0xB2,
    0xFF, 0xB3, 0xFF, 0xB4, 0xFF, 0xB5, 0xFF, 0xB6, 0xFF, 0xB7, 0xFF, 0xB8,
    0xFF, 0xB9, 0xFF, 0xBA, 0xFF, 0xBB, 0xFF, 0xBC, 0xFF, 0xBD, 0xFF, 0xBE,
    0xFF, 0xBF, 0xFF, 0xC0, 0xFF, 0xC1, 0xFF, 0xC2, 0xFF, 0xC3, 0xFF, 0xC4,
    0xFF, 0xC5, 0xFF, 0xC6, 0xFF, 0xC7, 0xFF, 0xC8, 0xFF, 0xC9, 0xFF, 0xCA,
    0xFF, 0xCB, 0xFF, 0xCC, 0xFF, 0xCD, 0xFF, 0xCE, 0xFF, 0xCF, 0xFF, 0xD0,
    0xFF, 0xD1, 0xFF, 0xD2, 0xFF, 0xD3, 0xFF, 0xD4, 0xFF, 0xD5, 0xFF, 0xD6,
    0xFF, 0xD7, 0xFF, 0xD8, 0xFF, 0xD9, 0xFF, 0xDA, 0xFF, 0xDB, 0xFF, 0xDC,
    0xFF, 0xDD, 0xFF, 0xDE, 0xFF, 0xDF, 0xFF, 0xE0, 0xFF, 0xE1, 0xFF, 0xE2,
    0xFF, 0xE3, 0xFF, 0xE4, 0xFF, 0xE5, 0xFF, 0xE6, 0xFF, 0xE7, 0xFF, 0xE8,
    0xFF, 0xE9, 0xFF, 0xEA, 0xFF, 0xEB, 0xFF, 0xEC, 0xFF, 0xED, 0xFF, 0xEE,
    0xFF, 0xEF, 0xFF, 0xF0, 0xFF, 0xF1, 0xFF, 0xF2, 0xFF, 0xF3, 0xFF, 0xF4,
    0xFF, 0xF5, 0xFF, 0xF6, 0xFF, 0xF7, 0xFF, 0xF8, 0xFF, 0xF9, 0xFF, 0xFA,
    0xFF, 0xFB, 0xFF, 0xFC, 0xFF, 0xFD, 0xFF, 0xFE, 0x02, 0x02, 0x03, 0x04,
    0x04, 0x04, 0x05, 0x05, 0x05, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x08,
    0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
    0x0B, 0x0B, 0x0B, 0x0B, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
    0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32,
    0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0,
    0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A,
    0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55,
    0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85,
    0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
    0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2,
    0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5,
    0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8,
    0xD9, 0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA,
    0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0x00, 0x00,
    0x02, 0x02, 0x03, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06,
    0x06, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B,
    0x0C, 0x0C, 0x0C, 0x0C, 0x0E, 0x0F, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x04, 0x00, 0x0A, 0x00, 0x0B, 0x00, 0x18, 0x00, 0x19, 0x00, 0x1A,
    0x00, 0x1B, 0x00, 0x38, 0x00, 0x39, 0x00, 0x3A, 0x00, 0x3B, 0x00, 0x78,
    0x00, 0x79, 0x00, 0x7A, 0x00, 0xF6, 0x00, 0xF7, 0x00, 0xF8, 0x00, 0xF9,
    0x01, 0xF4, 0x01, 0xF5, 0x01, 0xF6, 0x01, 0xF7, 0x01, 0xF8, 0x01, 0xF9,
    0x01, 0xFA, 0x03, 0xF6, 0x03, 0xF7, 0x03, 0xF8, 0x03, 0xF9, 0x03, 0xFA,
    0x07, 0xF6, 0x07, 0xF7, 0x07, 0xF8, 0x07, 0xF9, 0x0F, 0xF4, 0x0F, 0xF5,
    0x0F, 0xF6, 0x0F, 0xF7, 0x3F, 0xE0, 0x7F, 0xC2, 0x7F, 0xC3, 0xFF, 0x88,
    0xFF, 0x89, 0xFF, 0x8A, 0xFF, 0x8B, 0xFF, 0x8C, 0xFF, 0x8D, 0xFF, 0x8E,
    0xFF, 0x8F, 0xFF, 0x90, 0xFF, 0x91, 0xFF, 0x92, 0xFF, 0x93, 0xFF, 0x94,
    0xFF, 0x95, 0xFF, 0x96, 0xFF, 0x97, 0xFF, 0x98, 0xFF, 0x99, 0xFF, 0x9A,
    0xFF, 0x9B, 0xFF, 0x9C, 0xFF, 0x9D, 0xFF, 0x9E, 0xFF, 0x9F, 0xFF, 0xA0,
    0xFF, 0xA1, 0xFF, 0xA2, 0xFF, 0xA3, 0xFF, 0xA4, 0xFF, 0xA5, 0xFF, 0xA6,
    0xFF, 0xA7, 0xFF, 0xA8, 0xFF, 0xA9, 0xFF, 0xAA, 0xFF, 0xAB, 0xFF, 0xAC,
    0xFF, 0xAD, 0xFF, 0xAE, 0xFF, 0xAF, 0xFF, 0xB0, 0xFF, 0xB1, 0xFF, 0xB2,
    0xFF, 0xB3, 0xFF, 0xB4, 0xFF, 0xB5, 0xFF, 0xB6, 0xFF, 0xB7, 0xFF, 0xB8,
    0xFF, 0xB9, 0xFF, 0xBA, 0xFF, 0xBB, 0xFF, 0xBC, 0xFF, 0xBD, 0xFF, 0xBE,
    0xFF, 0xBF, 0xFF, 0xC0, 0xFF, 0xC1, 0xFF, 0xC2, 0xFF, 0xC3, 0xFF, 0xC4,
    0xFF, 0xC5, 0xFF, 0xC6, 0xFF, 0xC7, 0xFF, 0xC8, 0xFF, 0xC9, 0xFF, 0xCA,
    0xFF, 0xCB, 0xFF, 0xCC, 0xFF, 0xCD, 0xFF, 0xCE, 0xFF, 0xCF, 0xFF, 0xD0,
    0xFF, 0xD1, 0xFF, 0xD2, 0xFF, 0xD3, 0xFF, 0xD4, 0xFF, 0xD5, 0xFF, 0xD6,
    0xFF, 0xD7, 0xFF, 0xD8, 0xFF, 0xD9, 0xFF, 0xDA, 0xFF, 0xDB, 0xFF, 0xDC,
    0xFF, 0xDD, 0xFF, 0xDE, 0xFF, 0xDF, 0xFF, 0xE0, 0xFF, 0xE1, 0xFF, 0xE2,
    0xFF, 0xE3, 0xFF, 0xE4, 0xFF, 0xE5, 0xFF, 0xE6, 0xFF, 0xE7, 0xFF, 0xE8,
    0xFF, 0xE9, 0xFF, 0xEA, 0xFF, 0xEB, 0xFF, 0xEC, 0xFF, 0xED, 0xFF, 0xEE,
    0xFF, 0xEF, 0xFF, 0xF0, 0xFF, 0xF1, 0xFF, 0xF2, 0xFF, 0xF3, 0xFF, 0xF4,
    0xFF, 0xF5, 0xFF, 0xF6, 0xFF, 0xF7, 0xFF, 0xF8, 0xFF, 0xF9, 0xFF, 0xFA,
    0xFF, 0xFB, 0xFF, 0xFC, 0xFF, 0xFD, 0xFF, 0xFE, 0x00, 0x01, 0x02, 0x03,
    0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
    0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1, 0x09,
    0x23, 0x33, 0x52, 0xF0, 0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16, 0x24, 0x34,
    0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26, 0x27, 0x28, 0x29, 0x2A,
    0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64,
    0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x92,
    0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5,
    0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
    0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2,
    0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE2, 0xE3, 0xE4, 0xE5,
    0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
    0xF9, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
extern u8 lbl_80431638[0x40];
extern u16 lbl_80431678[0xC];
extern u8 lbl_80431690[0xC];
extern u16 lbl_8043169C[0xC];
extern u8 lbl_804316B4[0xC];

static inline s32 hsd_803B5C4C_read(s32 bits, s32 bit_count)
{
    __jmp_buf* jmp_buf = (__jmp_buf*) hsd_804D2E70;
    u8* next_byte;

    do {
        if (hsd_804D79C4 == 0) {
            hsd_804D79C4 = 8;
            if (hsd_804D79B8 >= &hsd_804D79BC[hsd_804D79C0]) {
                longjmp(jmp_buf, 1);
            }
            next_byte = hsd_804D79B8;
            hsd_804D79B8 = next_byte + 1;
            hsd_804D79C8 = *next_byte;
            if (hsd_804D79C8 == 0xFF) {
                if ((*hsd_804D79B8) != 0) {
                    longjmp(jmp_buf, 1);
                } else {
                    if (hsd_804D79B8 >= &hsd_804D79BC[hsd_804D79C0]) {
                        longjmp(jmp_buf, 1);
                    }
                    hsd_804D79B8 += 1;
                }
            }
        }
        bits *= 2;
        if (hsd_804D79C8 & (1 << (hsd_804D79C4 - 1))) {
            bits |= 1;
        }
        bit_count -= 1;
        hsd_804D79C4 -= 1;
    } while (bit_count != 0);
    return bits;
}

s32 hsd_803B5C4C(s32 bit_count)
{
    return hsd_803B5C4C_read(0, bit_count);
}

#ifdef MUST_MATCH
#pragma dont_inline on
#endif
s32 hsd_803B5D70(s32 ac, s32 component)
{
    s32 value_idx;
    s32 code;
    u16* code_table_tmp;
    u16* code_table;
    u8* length_table_tmp;
    u8* length_table_base;
    u8* length_table;
    u16* code_cursor;
    u8* value_table;
    s32 bit_len;

    value_idx = 0;
    code = 0;
    if (ac == 0) {
        if (component == 0) {
            code_table_tmp = lbl_80431678;
        } else {
            code_table_tmp = lbl_8043169C;
        }
        code_table = code_table_tmp;
        if (component == 0) {
            length_table_tmp = lbl_80431690;
        } else {
            length_table_tmp = lbl_804316B4;
        }
        length_table_base = length_table_tmp;
        length_table_tmp = lbl_80431090 + 0x80;
        value_table = length_table_tmp;
    } else {
        if (component == 0) {
            code_table_tmp = (u16*) (lbl_80431090 + 0x8C);
        } else {
            code_table_tmp = (u16*) (lbl_80431090 + 0x3BC);
        }
        code_table = code_table_tmp;
        if (component == 0) {
            length_table_tmp = lbl_80431090 + 0x1D0;
        } else {
            length_table_tmp = lbl_80431090 + 0x318;
        }
        length_table_base = length_table_tmp;
        if (component == 0) {
            length_table_tmp = lbl_80431090 + 0x274;
        } else {
            length_table_tmp = lbl_80431090 + 0x500;
        }
        value_table = length_table_tmp;
    }
    code_cursor = code_table;
    length_table = length_table_base;
    bit_len = 1;
read_bit:
    code = (code * 2) | hsd_803B5C4C(1);
    code_table_tmp = code_cursor;
    goto read_huffman_code;
check_code:
    if (code == (s32) *code_table_tmp) {
        return value_table[value_idx];
    }
    code_table_tmp += 1;
    code_cursor += 1;
    value_idx += 1;
    length_table += 1;
read_huffman_code:
    if (bit_len == (s32) *length_table) {
        goto check_code;
    }
    bit_len += 1;
    if (bit_len <= 0x10) {
        goto read_bit;
    }
    return 0U;
}
#ifdef MUST_MATCH
#pragma dont_inline off
#endif

#ifdef MUST_MATCH
#pragma dont_inline on
#endif
void hsd_803B5EA0(s32 component)
{
    u8* base;
    s32 run_bits;
    s32 coefficient;
    s32 dc;
    s32 ac;
    u32 zeros;
    u8 zigzag_index;
    s32 value_bits;

    base = hsd_804D2E70;
    value_bits = hsd_803B5D70(0, component);
    if (value_bits > 0) {
        dc = hsd_803B5C4C(value_bits);
        if (!(dc & (1 << (value_bits - 1)))) {
            dc -= (1 << value_bits) - 1;
        }
    } else {
        dc = 0;
    }
    ((s32*) &base[0x818])[component] += dc;
    coefficient = 1;
    ((JpegWorkData*) &base[0x118])->coeff[0] =
        ((s32*) &base[0x818])[component];
    while (coefficient < 0x40) {
        if ((run_bits = hsd_803B5D70(1, component)) == 0) {
            while (coefficient < 0x40) {
                ((JpegWorkData*) &base[0x118])
                    ->coeff[lbl_80431638[coefficient]] = 0;
                coefficient += 1;
            }
            return;
        } else {
            zeros = hsd_803B5C4C(run_bits) - 1;
            while (zeros--) {
                ((JpegWorkData*) &base[0x118])
                    ->coeff[lbl_80431638[coefficient++]] = 0;
            }
            value_bits = hsd_803B5D70(1, component);
            ac = hsd_803B5C4C(value_bits);
            if (!(ac & (1 << (value_bits - 1)))) {
                ac -= (1 << value_bits) - 1;
            }
            zigzag_index = lbl_80431638[coefficient++];
            ((JpegWorkData*) &base[0x118])->coeff[zigzag_index] = ac;
        }
    }
}
#ifdef MUST_MATCH
#pragma dont_inline off
#endif

void fn_803B61B4(s32* block)
{
    f32 odd_rotation_diff;
    f32 odd_pair_sum;
    f32 odd_pair_diff;
    s32 col5;
    f32 odd3;
    f32 odd_diff;
    f32 even_sum;
    f32 even_diff;
    f32 even1;
    f32 even_rotation_diff;
    f32 even2;
    f32 even0;
    f32 even_rotation_sum;
    f32 odd2;
    s32 col7;
    f32 column_odd_sum;
    f32 even3;
    s32 row3;
    s32 row2;
    s32 col3;
    s32 col2;
    s32 row4;
    s32 col4;
    s32 row0;
    s32 col0;
    s32 row1;
    s32 row5;
    s32 row6;
    s32 col1;
    f32 odd_sum;
    f32 odd_rotation_sum;
    f32 odd0;
    f32 odd1;
    s32 col6;
    s32 rows;
    s32 columns;
    s32 i;
    s32* samples;
    s32* row;
    s32* column;

    row = block;
    for (rows = 8; rows != 0; rows--) {
        s32 row7;

        row1 = row[1];
        row3 = row[3];
        row7 = row[7];
        row5 = row[5];
        row0 = row[0];
        row4 = row[4];
        odd0 = (f32) ((0.980785 * (f64) row7) - (0.19509 * (f64) row1));
        odd1 = (f32) ((0.83147 * (f64) row5) - (0.55557 * (f64) row3));
        odd2 = (f32) ((0.55557 * (f64) row5) + (0.83147 * (f64) row3));
        odd3 = (f32) ((0.19509 * (f64) row7) + (0.980785 * (f64) row1));
        even_sum = (f32) (0.707107 * (f64) (row0 + row4));
        even_diff = (f32) (0.707107 * (f64) (row0 - row4));
        row2 = row[2];
        odd_pair_sum = odd0 + odd1;
        row6 = row[6];
        odd_pair_diff = -odd2 + odd3;
        odd_sum = odd2 + odd3;
        even_rotation_diff =
            (f32) ((-0.92388 * (f64) row6) + (0.382683 * (f64) row2));
        even_rotation_sum =
            (f32) ((0.382683 * (f64) row6) + (0.92388 * (f64) row2));
        odd_rotation_diff =
            (f32) (0.707107 * (f64) (-odd_pair_sum + odd_pair_diff));
        even0 = even_sum + even_rotation_sum;
        odd_diff = -odd0 + odd1;
        odd_rotation_sum =
            (f32) (0.707107 * (f64) (odd_pair_sum + odd_pair_diff));
        odd0 = odd_rotation_sum;
        even1 = even_diff + even_rotation_diff;
        even2 = even_diff - even_rotation_diff;
        row[0] = (s32) (even0 + odd_sum);
        row[1] = (s32) (even1 + odd_rotation_diff);
        even3 = even_sum - even_rotation_sum;
        row[2] = (s32) (even2 + odd0);
        row[3] = (s32) (even3 + odd_diff);
        row[4] = (s32) (even3 - odd_diff);
        row[5] = (s32) (even2 - odd0);
        row[6] = (s32) (even1 - odd_rotation_diff);
        row[7] = (s32) (even0 - odd_sum);
        row += 8;
    }
    column = block;
    for (columns = 8; columns != 0; columns--) {
        col1 = column[8];
        col3 = column[24];
        col7 = column[56];
        col5 = column[40];
        col0 = column[0];
        col4 = column[32];
        odd0 = (f32) ((0.980785 * (f64) col7) - (0.19509 * (f64) col1));
        odd1 = (f32) ((0.83147 * (f64) col5) - (0.55557 * (f64) col3));
        odd2 = (f32) ((0.55557 * (f64) col5) + (0.83147 * (f64) col3));
        odd3 = (f32) ((0.19509 * (f64) col7) + (0.980785 * (f64) col1));
        even_sum = (f32) (0.707107 * (f64) (col0 + col4));
        even_diff = (f32) (0.707107 * (f64) (col0 - col4));
        col2 = column[16];
        odd_pair_sum = odd0 + odd1;
        col6 = column[48];
        odd_pair_diff = -odd2 + odd3;
        odd_sum = odd2 + odd3;
        even_rotation_diff =
            (f32) ((-0.92388 * (f64) col6) + (0.382683 * (f64) col2));
        even_rotation_sum =
            (f32) ((0.382683 * (f64) col6) + (0.92388 * (f64) col2));
        {
            f32 odd_rotation_sum =
                (f32) (0.707107 * (f64) (-odd_pair_sum + odd_pair_diff));
            odd_rotation_diff = odd_rotation_sum;
        }
        even0 = even_sum + even_rotation_sum;
        odd_diff = -odd0 + odd1;
        column_odd_sum =
            (f32) (0.707107 * (f64) (odd_pair_sum + odd_pair_diff));
        even1 = even_diff + even_rotation_diff;
        even2 = even_diff - even_rotation_diff;
        column[0] = (s32) (even0 + odd_sum);
        column[8] = (s32) (even1 + odd_rotation_diff);
        even3 = even_sum;
        even3 -= even_rotation_sum;
        column[16] = (s32) (even2 + column_odd_sum);
        column[24] = (s32) (even3 + odd_diff);
        column[32] = (s32) (even3 - odd_diff);
        column[40] = (s32) (even2 - column_odd_sum);
        column[48] = (s32) (even1 - odd_rotation_diff);
        column[56] = (s32) (even0 - odd_sum);
        column += 1;
    }
    samples = block;
    for (i = 0; 0x40 > i; i++) {
        samples[i] >>= 2;
    }
}

static inline s32 jpeg_clamp(f32 value)
{
    if (value < 0.0f) {
        return 0;
    }
    if (255.0f < value) {
        return 255;
    }
    return (u8) (s32) value;
}

static void fn_803B6820(u8* dst, s32 x, s32 y, s32 width, s32 unused_height)
{
    s32 tile_y;
    s32 chroma_column;
    s32 cr;
    s32 block_columns;
    s32 tile_x;
    s32 group_y;
    s32 group_x;
    s32 block;
    s32* luma;
    u8* luma_block;
    u16* out;
    s32 luminance;
    f32 red_value;
    u32 luma_offset;
    s32 luma_x;
    s32 row;
    s32 aligned_width;
    u8 green;
    s32 channel;
    u8 blue;
    s32 chroma_row;
    s32 cb;
    f32 green_value;
    s32 bias_block;
    s32 out_offset;
    f32 blue_value;
    s32 group_row;
    s32 block_count;
    u8* base;
    s32 chroma_x_base;
    s32 luma_row_offset;
    u8* chroma;
    s32 group_chroma;
    s32 luma_groups;
    struct {
        s32* luma;
        u8 red;
    } pixel;
    PAD_STACK(24);
    pixel.red = 0;
    base = hsd_804D2E70;
    luma_block = (u8*) ((JpegState*) base)->work.luma;
    for (bias_block = 0; bias_block < 4; bias_block++) {
        luma = (s32*) luma_block;
        for (luma_groups = 16; luma_groups != 0; luma_groups--) {
            channel = luma[0];
            luma[0] = channel + 0x80;
            channel = luma[1];
            luma[1] = channel + 0x80;
            channel = luma[2];
            luma[2] = channel + 0x80;
            channel = luma[3];
            luma[3] = channel + 0x80;
            luma += 4;
        }
        luma_block += 0x100;
    }
    block_columns = (width + 0xF) / 16;
    aligned_width = block_columns << 4;
    for (group_y = 0; group_y < 2; group_y++) {
        out = (u16*) dst + (((x / 4) * 0x10) +
                            ((aligned_width << 2) * ((y / 4) + group_y)));
        group_chroma = group_y * 16;
        group_row = group_y * 4;
        for (group_x = 0; group_x < 2; group_x++) {
            row = group_row;
            chroma_x_base = group_chroma + group_x * 2;
            luma_x = group_x * 4;
            for (tile_y = 0, luma_row_offset = row * 8; tile_y < 4; tile_y++) {
                luma_offset = (luma_x + luma_row_offset) * 4;
                for (tile_x = 0; tile_x < 4; tile_x++) {
                    chroma_row = tile_x >> 1;
                    chroma_row += chroma_x_base + ((tile_y & 2) * 4);
                    block = 0;
                    pixel.luma =
                        &((JpegWorkData*) &base[0x118])->luma[luma_offset / 4];
                    for (block_count = 4; block_count != 0; block_count--) {
                        luminance = *pixel.luma;
                        {
                            chroma_column = (block % 2) * 4;
                            chroma = base + ((chroma_row + ((block / 2) << 5) +
                                              chroma_column) *
                                             4);
                        }
                        cr = ((JpegState*) chroma)->work.cr[0];
                        cb = ((JpegState*) chroma)->work.cb[0];
                        out_offset = ((block & 1) << 5) +
                                     (aligned_width * ((block & 2) << 2));
                        red_value =
                            (f32) ((1.402 * (f64) cr) + (f64) luminance);
                        pixel.red = jpeg_clamp(red_value);
                        green_value =
                            ((f32) luminance - (0.3441f * (f32) cb)) -
                            (0.7139f * (f32) cr);
                        green = jpeg_clamp(green_value);
                        blue_value = (f32) ((f64) ((1.7718f * (f32) cb) +
                                                   (f32) luminance) -
                                            (0.0012 * (f64) cr));
                        blue = jpeg_clamp(blue_value);
                        out[out_offset] = ((pixel.red << 8) & 0xF800) |
                                          ((green << 3) & 0x7E0) |
                                          (blue >> 3U);
                        pixel.luma += 0x40;
                        block += 1;
                    }
                    out += 1;
                    luma_offset += 4;
                }
                luma_row_offset += 8;
            }
            group_row = row;
        }
    }
}
static inline s32 hsd_803B6BE4_inline(char* src, s32 size, void* dst)
{
    s32 cr_coeff7;
    s32 luma_coeff7;
    s32 cb_coeff7;
    s32 y;
    s32 x;
    u8* zigzag;
    s32 i;
    u8 quant_byte;
    u8 quant0;
    u8 cr_quant0;
    u8 cb_quant0;
    u8* src_byte0;
    u8* src_byte9;
    u8* src_byte10;
    u8* src_byte11;
    u8* src_byte12;
    u8* src_byte13;
    u8* src_byte14;
    u8* src_byte15;
    u8* src_byte1;
    u8* src_byte2;
    u8* src_byte3;
    u8* src_byte4;
    u8* src_byte5;
    u8* src_byte6;
    u8* src_byte7;
    u8* src_byte8;
    s32 luma_block;
    s32* luma;
    s32* coefficients;
    struct {
        u8* base;
        JpegState* work;
        JpegQuantTables* quant_table;
        s32 width;
        s32 height;
    } state;

    state.base = hsd_804D2E70;
    state.work = (JpegState*) state.base;
    hsd_804D79C0 = size;
    state.quant_table = (JpegQuantTables*) lbl_80431090;
    hsd_804D79B8 = (u8*) src;
    hsd_804D79BC = (u8*) src;
    state.work->work.prev_dc[0] = state.work->work.prev_dc[1] =
        state.work->work.prev_dc[2] = 0;
    hsd_804D79C4 = 0;
    if (__setjmp(&state.work->jmp) != 0) {
        return 0;
    }
    src_byte0 = &hsd_804D79BC[hsd_804D79C0];
find_luma_quant:
    if (*(u16*) hsd_804D79B8 == 0xFFDB) {
        u8* zigzag;
        s32 i;

        hsd_804D79B8 += 5;
        zigzag = lbl_80431638;
        for (i = 0; i < 0x40; i += 8) {
            src_byte0 = hsd_804D79B8;
            hsd_804D79B8 = src_byte0 + 1;
            state.quant_table->luma[zigzag[0]] = *src_byte0;
            src_byte1 = hsd_804D79B8;
            hsd_804D79B8 = src_byte1 + 1;
            state.quant_table->luma[zigzag[1]] = *src_byte1;
            src_byte2 = hsd_804D79B8;
            hsd_804D79B8 = src_byte2 + 1;
            state.quant_table->luma[zigzag[2]] = *src_byte2;
            src_byte3 = hsd_804D79B8;
            hsd_804D79B8 = src_byte3 + 1;
            state.quant_table->luma[zigzag[3]] = *src_byte3;
            src_byte4 = hsd_804D79B8;
            hsd_804D79B8 = src_byte4 + 1;
            state.quant_table->luma[zigzag[4]] = *src_byte4;
            src_byte5 = hsd_804D79B8;
            hsd_804D79B8 = src_byte5 + 1;
            state.quant_table->luma[zigzag[5]] = *src_byte5;
            src_byte6 = hsd_804D79B8;
            hsd_804D79B8 = src_byte6 + 1;
            state.quant_table->luma[zigzag[6]] = *src_byte6;
            src_byte7 = hsd_804D79B8;
            hsd_804D79B8 = src_byte7 + 1;
            quant_byte = zigzag[7];
            zigzag += 8;
            state.quant_table->luma[quant_byte] = *src_byte7;
        }
    } else {
        if (++hsd_804D79B8 >= src_byte0) {
            longjmp(&state.work->jmp, 1);
        } else {
            goto find_luma_quant;
        }
    }
    src_byte0 = &hsd_804D79BC[hsd_804D79C0];
find_chroma_quant:
    if (*(u16*) hsd_804D79B8 == 0xFFDB) {
        u8 qbyte;
        u8* qptr;
        s32 zigzag_index;

        hsd_804D79B8 += 5;
        zigzag = lbl_80431638;
        for (i = 0; i < 0x40; i += 8) {
            src_byte8 = hsd_804D79B8;
            hsd_804D79B8 = src_byte8 + 1;
            zigzag_index = zigzag[0];
            qptr = state.quant_table->luma + zigzag_index;
            qptr[0x40] = qbyte = *src_byte8;
            src_byte9 = hsd_804D79B8;
            hsd_804D79B8 = src_byte9 + 1;
            zigzag_index = zigzag[1];
            qptr = state.quant_table->luma + zigzag_index;
            qptr[0x40] = qbyte = *src_byte9;
            src_byte10 = hsd_804D79B8;
            hsd_804D79B8 = src_byte10 + 1;
            zigzag_index = zigzag[2];
            qptr = state.quant_table->luma + zigzag_index;
            qptr[0x40] = qbyte = *src_byte10;
            src_byte11 = hsd_804D79B8;
            hsd_804D79B8 = src_byte11 + 1;
            zigzag_index = zigzag[3];
            qptr = state.quant_table->luma + zigzag_index;
            qptr[0x40] = qbyte = *src_byte11;
            src_byte12 = hsd_804D79B8;
            hsd_804D79B8 = src_byte12 + 1;
            zigzag_index = zigzag[4];
            qptr = state.quant_table->luma + zigzag_index;
            qptr[0x40] = qbyte = *src_byte12;
            src_byte13 = hsd_804D79B8;
            hsd_804D79B8 = src_byte13 + 1;
            zigzag_index = zigzag[5];
            qptr = state.quant_table->luma + zigzag_index;
            qbyte = quant_byte = *src_byte13;
            qptr[0x40] = qbyte;
            src_byte14 = hsd_804D79B8;
            hsd_804D79B8 = src_byte14 + 1;
            zigzag_index = zigzag[6];
            qptr = state.quant_table->luma + zigzag_index;
            qptr[0x40] = qbyte = *src_byte14;
            src_byte15 = hsd_804D79B8;
            hsd_804D79B8 = src_byte15 + 1;
            zigzag_index = zigzag[7];
            qptr = state.quant_table->luma + zigzag_index;
            zigzag += 8;
            qptr[0x40] = qbyte = *src_byte15;
        }
    } else {
        if (++hsd_804D79B8 >= src_byte0) {
            longjmp(&state.work->jmp, 1);
        } else {
            goto find_chroma_quant;
        }
    }
    src_byte0 = &hsd_804D79BC[hsd_804D79C0];
find_frame:
    if (*(u16*) hsd_804D79B8 == 0xFFC0) {
        hsd_804D79B8 += 5;
        state.height = *(u16*) hsd_804D79B8;
        hsd_804D79B8 += 2;
        state.width = *(u16*) hsd_804D79B8;
        hsd_804D79B8 += 0xC;
    } else {
        if (++hsd_804D79B8 >= src_byte0) {
            longjmp(&state.work->jmp, 1);
        } else {
            goto find_frame;
        }
    }
    src_byte0 = &hsd_804D79BC[hsd_804D79C0];
find_scan:
    if (*(u16*) hsd_804D79B8 == 0xFFDA) {
        hsd_804D79B8 += 2;
        hsd_804D79B8 += 0xC;
    } else {
        if (++hsd_804D79B8 >= src_byte0) {
            longjmp(&state.work->jmp, 1);
        } else {
            goto find_scan;
        }
    }
    for (y = 0; y < state.height; y += 0x10) {
        for (x = 0; x < state.width; x += 0x10) {
            luma = state.work->work.luma;
            for (luma_block = 0; luma_block < 4; luma_block++) {
                u8* luma_quant;
                s32* luma_out;
                s32* luma_coeff;
                s32 luma_index;

                hsd_803B5EA0(0);
                luma_out = luma;
                luma_coeff = state.work->work.coeff;
                for (luma_index = 0; luma_index < 0x40; luma_index += 8) {
                    luma_quant = state.quant_table->luma + luma_index;
                    quant0 = luma_quant[0];
                    luma_out[0] = (luma_coeff[0] * quant0);
                    luma_out[1] = (luma_coeff[1] * luma_quant[1]);
                    luma_out[2] = (luma_coeff[2] * luma_quant[2]);
                    luma_out[3] = (luma_coeff[3] * luma_quant[3]);
                    luma_out[4] = (luma_coeff[4] * luma_quant[4]);
                    luma_out[5] = (luma_coeff[5] * luma_quant[5]);
                    luma_out[6] = (luma_coeff[6] * luma_quant[6]);
                    luma_coeff7 = luma_coeff[7];
                    luma_coeff += 8;
                    luma_out[7] = (luma_coeff7 * luma_quant[7]);
                    luma_out += 8;
                }
                fn_803B61B4(luma);
                luma += 0x40;
            }
            hsd_803B5EA0(1);
            {
                u8* cb_quant;
                s32* cb_out;
                s32* cb_coeff;
                s32 cb_index;
                u8* quant_chroma = state.quant_table->chroma;

                cb_coeff = coefficients = state.work->work.coeff;
                cb_out = state.work->work.cb;
                for (cb_index = 0; cb_index < 0x40; cb_index += 8) {
                    cb_quant = quant_chroma + cb_index;
                    cb_quant0 = cb_quant[0];
                    cb_out[0] = (cb_coeff[0] * cb_quant0);
                    cb_out[1] = (cb_coeff[1] * cb_quant[1]);
                    cb_out[2] = (cb_coeff[2] * cb_quant[2]);
                    cb_out[3] = (cb_coeff[3] * cb_quant[3]);
                    cb_out[4] = (cb_coeff[4] * cb_quant[4]);
                    cb_out[5] = (cb_coeff[5] * cb_quant[5]);
                    cb_out[6] = (cb_coeff[6] * cb_quant[6]);
                    cb_coeff7 = cb_coeff[7];
                    cb_coeff += 8;
                    cb_out[7] = (cb_coeff7 * cb_quant[7]);
                    cb_out += 8;
                }
                fn_803B61B4(state.work->work.cb);
            }
            hsd_803B5EA0(2);
            {
                u8* quant_chroma = state.quant_table->chroma;
                u8* cr_quant;
                s32* cr_out;
                s32 cr_index;

                cr_out = state.work->work.cr;
                for (cr_index = 0; cr_index < 0x40; cr_index += 8) {
                    cr_quant = quant_chroma + cr_index;
                    cr_quant0 = cr_quant[0];
                    cr_out[0] = (coefficients[0] * cr_quant0);
                    cr_out[1] = (coefficients[1] * cr_quant[1]);
                    cr_out[2] = (coefficients[2] * cr_quant[2]);
                    cr_out[3] = (coefficients[3] * cr_quant[3]);
                    cr_out[4] = (coefficients[4] * cr_quant[4]);
                    cr_out[5] = (coefficients[5] * cr_quant[5]);
                    cr_out[6] = (coefficients[6] * cr_quant[6]);
                    cr_coeff7 = coefficients[7];
                    coefficients += 8;
                    cr_out[7] = (cr_coeff7 * cr_quant[7]);
                    cr_out += 8;
                }
                fn_803B61B4(state.work->work.cr);
            }
            fn_803B6820(dst, x, y, state.width, state.height);
        }
    }
    return state.width * state.height * 2;
}

s32 hsd_803B6BE4(char* src, s32 size, void* dst)
{
    PAD_STACK(0x30);

    return hsd_803B6BE4_inline(src, size, dst);
}

u8 lbl_80431638[0x40] = {
    0,    1,    8,    0x10, 9,    2,    3,    0xA,  0x11, 0x18, 0x20,
    0x19, 0x12, 0xB,  4,    5,    0xC,  0x13, 0x1A, 0x21, 0x28, 0x30,
    0x29, 0x22, 0x1B, 0x14, 0xD,  6,    7,    0xE,  0x15, 0x1C, 0x23,
    0x2A, 0x31, 0x38, 0x39, 0x32, 0x2B, 0x24, 0x1D, 0x16, 0xF,  0x17,
    0x1E, 0x25, 0x2C, 0x33, 0x3A, 0x3B, 0x34, 0x2D, 0x26, 0x1F, 0x27,
    0x2E, 0x35, 0x3C, 0x3D, 0x36, 0x2F, 0x37, 0x3E, 0x3F,
};
u16 lbl_80431678[0xC] = {
    0, 2, 3, 4, 5, 6, 0xE, 0x1E, 0x3E, 0x7E, 0xFE, 0x1FE
};
u8 lbl_80431690[0xC] = { 2, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9 };
u16 lbl_8043169C[0xC] = { 0,    1,    2,    6,     0xE,   0x1E,
                          0x3E, 0x7E, 0xFE, 0x1FE, 0x3FE, 0x7FE };
u8 lbl_804316B4[0xC] = { 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB };
