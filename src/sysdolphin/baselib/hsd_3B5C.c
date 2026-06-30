#include "hsd_3B34.h"

#include <placeholder.h>

#include <Gecko_setjmp.h>

#define HSD_COEFF(code) M2C_FIELD((hsd_804D2E70 + ((code) * 4)), s32*, 0x718)

extern u8 hsd_804D2E70[2084];
extern u8* hsd_804D79B8;
extern u8* hsd_804D79BC;
extern s32 hsd_804D79C0;
extern s32 hsd_804D79C4;
extern u8 hsd_804D79C8;

typedef struct HSD_JpegWork {
    u8 data[2084];
} HSD_JpegWork;

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
    u8* scratch_r3;

    do {
        if ((s32) hsd_804D79C4 == 0) {
            hsd_804D79C4 = 8;
            if ((u8*) hsd_804D79B8 >= &hsd_804D79BC[hsd_804D79C0]) {
                longjmp(jmp_buf, 1);
            }
            scratch_r3 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r3 + 1;
            hsd_804D79C8 = *scratch_r3;
            if ((u8) hsd_804D79C8 == 0xFF) {
                if ((u8) *hsd_804D79B8 != 0) {
                    longjmp(jmp_buf, 1);
                } else {
                    if ((u8*) hsd_804D79B8 >= &hsd_804D79BC[hsd_804D79C0]) {
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

s32 hsd_803B5C4C(s32 arg0)
{
    return hsd_803B5C4C_read(0, arg0);
}

#pragma dont_inline on
s32 hsd_803B5D70(s32 arg0, s32 arg1)
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
    if (arg0 == 0) {
        if (arg1 == 0) {
            code_table_tmp = lbl_80431678;
        } else {
            code_table_tmp = lbl_8043169C;
        }
        code_table = code_table_tmp;
        if (arg1 == 0) {
            length_table_tmp = lbl_80431690;
        } else {
            length_table_tmp = lbl_804316B4;
        }
        length_table_base = length_table_tmp;
        length_table_tmp = lbl_80431090 + 0x80;
        value_table = length_table_tmp;
    } else {
        if (arg1 == 0) {
            code_table_tmp = (u16*) (lbl_80431090 + 0x8C);
        } else {
            code_table_tmp = (u16*) (lbl_80431090 + 0x3BC);
        }
        code_table = code_table_tmp;
        if (arg1 == 0) {
            length_table_tmp = lbl_80431090 + 0x1D0;
        } else {
            length_table_tmp = lbl_80431090 + 0x318;
        }
        length_table_base = length_table_tmp;
        if (arg1 == 0) {
            length_table_tmp = lbl_80431090 + 0x274;
        } else {
            length_table_tmp = lbl_80431090 + 0x500;
        }
        value_table = length_table_tmp;
    }
    code_cursor = code_table;
    length_table = length_table_base;
    bit_len = 1;
loop_19:
    code = (code * 2) | hsd_803B5C4C(1);
    code_table_tmp = code_cursor;
    goto read_huffman_code;
loop_23:
    if (code == (s32) *code_table_tmp) {
        return value_table[value_idx];
    }
    code_table_tmp += 1;
    code_cursor += 1;
    value_idx += 1;
    length_table += 1;
read_huffman_code:
    if (bit_len == (s32) *length_table) {
        goto loop_23;
    }
    bit_len += 1;
    if (bit_len <= 0x10) {
        goto loop_19;
    }
    return 0U;
}
#pragma dont_inline off

#pragma dont_inline on
void hsd_803B5EA0(s32 arg0)
{
    u8* base;
    s32 scratch_r29;
    s32 scratch_r29_2;
    s32 scratch_r29_3;
    s32 scratch_r29_4;
    s32 scratch_r29_5;
    s32 scratch_r29_6;
    s32 scratch_r3_2;
    s32 work_r29;
    s32 work_r3;
    s32 work_r3_4;
    u32 scratch_r0_4;
    u32 scratch_r8;
    u32 work_ctr_3;
    u32 work_ctr_4;
    u32 work_r3_3;
    u8 scratch_r0_5;
    u8 scratch_r0_6;
    s32 scratch_r27;
    s32* scratch_r5;

    work_r29 = 1;
    base = hsd_804D2E70;
    scratch_r27 = hsd_803B5D70(0, arg0);
    if (scratch_r27 > 0) {
        work_r3 = hsd_803B5C4C(scratch_r27);
        if (!(work_r3 & (1 << (scratch_r27 - 1)))) {
            work_r3 -= (1 << scratch_r27) - 1;
        }
    } else {
        work_r3 = 0;
    }
    scratch_r5 = (s32*) (base + (arg0 * 4));
    scratch_r5[0x206] = (s32) (scratch_r5[0x206] + work_r3);
    HSD_COEFF(0) = (s32) scratch_r5[0x206];
    while (work_r29 < 0x40) {
        if ((scratch_r3_2 = hsd_803B5D70(1, arg0)) == 0) {
            while (work_r29 < 0x40) {
                HSD_COEFF(lbl_80431638[work_r29]) = 0;
                work_r29 += 1;
            }
            return;
        } else {
            scratch_r8 = hsd_803B5C4C(scratch_r3_2) - 1;
            work_r3_3 = scratch_r8;
            if (scratch_r8 != 0) {
                scratch_r0_4 = work_r3_3 >> 3U;
                work_ctr_3 = scratch_r0_4;
                if (scratch_r0_4 != 0) {
                    do {
                        scratch_r29 = work_r29 + 1;
                        HSD_COEFF(lbl_80431638[work_r29]) = 0;
                        scratch_r29_2 = scratch_r29 + 1;
                        HSD_COEFF(lbl_80431638[scratch_r29]) = 0;
                        scratch_r29_3 = scratch_r29_2 + 1;
                        scratch_r29_4 = scratch_r29_3 + 1;
                        HSD_COEFF(lbl_80431638[scratch_r29_2]) = 0;
                        scratch_r29_5 = scratch_r29_4 + 1;
                        HSD_COEFF(lbl_80431638[scratch_r29_3]) = 0;
                        scratch_r29_6 = scratch_r29_5 + 1;
                        HSD_COEFF(lbl_80431638[scratch_r29_4]) = 0;
                        HSD_COEFF(lbl_80431638[scratch_r29_5]) = 0;
                        work_r29 = scratch_r29_6 + 1;
                        HSD_COEFF(lbl_80431638[scratch_r29_6]) = 0;
                        HSD_COEFF(lbl_80431638[work_r29 - 1]) = 0;
                        work_ctr_3 -= 1;
                    } while (work_ctr_3 != 0);
                    work_r3_3 &= 7;
                    if (work_r3_3 != 0) {
                        goto emit_zero_tail;
                    }
                } else {
                emit_zero_tail:
                    work_ctr_4 = work_r3_3;
                    do {
                        scratch_r0_5 = lbl_80431638[work_r29];
                        work_r29 += 1;
                        HSD_COEFF(scratch_r0_5) = 0;
                        work_ctr_4 -= 1;
                    } while (work_ctr_4 != 0);
                }
            }
            scratch_r27 = hsd_803B5D70(1, arg0);
            work_r3_4 = hsd_803B5C4C(scratch_r27);
            if (!(work_r3_4 & (1 << (scratch_r27 - 1)))) {
                work_r3_4 -= (1 << scratch_r27) - 1;
            }
            scratch_r0_6 = lbl_80431638[work_r29];
            work_r29 += 1;
            HSD_COEFF(scratch_r0_6) = work_r3_4;
        }
    }
}
#pragma dont_inline off

static void fn_803B61B4(u8* arg0)
{
    f32 scratch_f10;
    f32 scratch_f10_2;
    f32 scratch_f10_3;
    f32 scratch_f11;
    f32 scratch_f11_2;
    f32 scratch_f12;
    f32 scratch_f12_2;
    f32 scratch_f12_3;
    f32 scratch_f13;
    f32 scratch_f13_2;
    f32 scratch_f13_3;
    f32 scratch_f13_4;
    f32 scratch_f13_5;
    f32 scratch_f22;
    f32 scratch_f22_2;
    f32 scratch_f23;
    f32 scratch_f23_2;
    f32 scratch_f23_3;
    f32 scratch_f24;
    f32 scratch_f24_2;
    f32 scratch_f24_3;
    f32 scratch_f24_4;
    f32 scratch_f25;
    f32 scratch_f25_2;
    f32 scratch_f25_3;
    f32 scratch_f25_4;
    f32 scratch_f26;
    f32 scratch_f26_2;
    f32 scratch_f27;
    f32 scratch_f27_2;
    f32 scratch_f29;
    f32 scratch_f30;
    f32 scratch_f31;
    f32 scratch_f9;
    f32 scratch_f9_2;
    f32 scratch_f9_3;
    s32 scratch_r0;
    s32 scratch_r0_2;
    s32 scratch_r0_3;
    s32 scratch_r0_4;
    s32 scratch_r10;
    s32 scratch_r10_2;
    s32 scratch_r11;
    s32 scratch_r11_2;
    s32 scratch_r5;
    s32 scratch_r5_2;
    s32 scratch_r5_3;
    s32 scratch_r5_4;
    s32 scratch_r5_5;
    s32 scratch_r5_6;
    s32 scratch_r6;
    s32 scratch_r6_2;
    s32 work_ctr;
    s32 work_ctr_2;
    s32 work_ctr_3;
    s32* work_r3;
    s32* work_r4;
    s32* work_r4_2;

    work_r4 = (s32*) arg0;
    for (work_ctr = 8; work_ctr != 0; work_ctr--) {
        scratch_r5 = work_r4[1];
        scratch_r0 = work_r4[3];
        scratch_r6 = work_r4[7];
        scratch_r5_2 = work_r4[5];
        scratch_r11 = work_r4[0];
        scratch_r10 = work_r4[4];
        scratch_f22 = (f32) ((0.980785f * (f64) scratch_r6) -
                             (0.19509f * (f64) scratch_r5));
        scratch_f31 = (f32) ((0.83147f * (f64) scratch_r5_2) -
                             (0.55557f * (f64) scratch_r0));
        scratch_f23 = (f32) ((0.55557f * (f64) scratch_r5_2) +
                             (0.83147f * (f64) scratch_r0));
        scratch_f24 = (f32) ((0.19509f * (f64) scratch_r6) +
                             (0.980785f * (f64) scratch_r5));
        scratch_f10 = (f32) (0.707107f * (f64) (scratch_r11 + scratch_r10));
        scratch_f11 = (f32) (0.707107f * (f64) (scratch_r11 - scratch_r10));
        scratch_r0_2 = work_r4[2];
        scratch_f12 = scratch_f22 + scratch_f31;
        scratch_r5_3 = work_r4[6];
        scratch_f13 = -scratch_f23 + scratch_f24;
        scratch_f13_2 = scratch_f23 + scratch_f24;
        scratch_f9 = (f32) (0.707107f * (f64) (-scratch_f12 + scratch_f13));
        scratch_f25 = (f32) ((-0.92388f * (f64) scratch_r5_3) +
                             (0.382683f * (f64) scratch_r0_2));
        scratch_f12_2 = (f32) ((0.382683f * (f64) scratch_r5_3) +
                               (0.92388f * (f64) scratch_r0_2));
        scratch_f23_2 = scratch_f10 + scratch_f12_2;
        scratch_f22_2 = (f32) (0.707107f * (f64) (scratch_f12 + scratch_f13));
        scratch_f24_2 = scratch_f11 + scratch_f25;
        scratch_f25_2 = scratch_f11 - scratch_f25;
        work_r4[0] = (s32) (scratch_f23_2 + scratch_f13_2);
        work_r4[1] = (s32) (scratch_f24_2 + scratch_f9);
        scratch_f13_3 = -scratch_f22 + scratch_f31;
        scratch_f10_2 = scratch_f10 - scratch_f12_2;
        work_r4[2] = (s32) (scratch_f25_2 + scratch_f22_2);
        work_r4[3] = (s32) (scratch_f10_2 + scratch_f13_3);
        work_r4[4] = (s32) (scratch_f10_2 - scratch_f13_3);
        work_r4[5] = (s32) (scratch_f25_2 - scratch_f22_2);
        work_r4[6] = (s32) (scratch_f24_2 - scratch_f9);
        work_r4[7] = (s32) (scratch_f23_2 - scratch_f13_2);
        work_r4 += 8;
    }
    work_r4_2 = (s32*) arg0;
    for (work_ctr_2 = 8; work_ctr_2 != 0; work_ctr_2--) {
        scratch_r5_4 = work_r4_2[8];
        scratch_r0_3 = work_r4_2[24];
        scratch_r6_2 = work_r4_2[56];
        scratch_r5_5 = work_r4_2[40];
        scratch_r11_2 = work_r4_2[0];
        scratch_r10_2 = work_r4_2[32];
        scratch_f26 = (f32) ((0.980785f * (f64) scratch_r6_2) -
                             (0.19509f * (f64) scratch_r5_4));
        scratch_f9_2 = (f32) ((0.83147f * (f64) scratch_r5_5) -
                              (0.55557f * (f64) scratch_r0_3));
        scratch_f27 = (f32) ((0.55557f * (f64) scratch_r5_5) +
                             (0.83147f * (f64) scratch_r0_3));
        scratch_f30 = (f32) ((0.19509f * (f64) scratch_r6_2) +
                             (0.980785f * (f64) scratch_r5_4));
        scratch_f10_3 =
            (f32) (0.707107f * (f64) (scratch_r11_2 + scratch_r10_2));
        scratch_f25_3 =
            (f32) (0.707107f * (f64) (scratch_r11_2 - scratch_r10_2));
        scratch_r0_4 = work_r4_2[16];
        scratch_f13_4 = scratch_f26 + scratch_f9_2;
        scratch_r5_6 = work_r4_2[48];
        scratch_f29 = -scratch_f27 + scratch_f30;
        scratch_f11_2 = scratch_f27 + scratch_f30;
        scratch_f12_3 =
            (f32) (0.707107f * (f64) (-scratch_f13_4 + scratch_f29));
        scratch_f13_5 = (f32) ((-0.92388f * (f64) scratch_r5_6) +
                               (0.382683f * (f64) scratch_r0_4));
        scratch_f26_2 = (f32) ((0.382683f * (f64) scratch_r5_6) +
                               (0.92388f * (f64) scratch_r0_4));
        scratch_f27_2 = scratch_f10_3 + scratch_f26_2;
        scratch_f23_3 =
            (f32) (0.707107f * (f64) (scratch_f13_4 + scratch_f29));
        scratch_f24_3 = scratch_f25_3 + scratch_f13_5;
        scratch_f25_4 = scratch_f25_3 - scratch_f13_5;
        work_r4_2[0] = (s32) (scratch_f27_2 + scratch_f11_2);
        work_r4_2[8] = (s32) (scratch_f24_3 + scratch_f12_3);
        scratch_f9_3 = -scratch_f26 + scratch_f9_2;
        scratch_f24_4 = scratch_f10_3 - scratch_f26_2;
        work_r4_2[16] = (s32) (scratch_f25_4 + scratch_f23_3);
        work_r4_2[24] = (s32) (scratch_f24_4 + scratch_f9_3);
        work_r4_2[32] = (s32) (scratch_f24_4 - scratch_f9_3);
        work_r4_2[40] = (s32) (scratch_f25_4 - scratch_f23_3);
        work_r4_2[48] = (s32) (scratch_f24_3 - scratch_f12_3);
        work_r4_2[56] = (s32) (scratch_f27_2 - scratch_f11_2);
        work_r4_2 += 1;
    }
    work_r3 = (s32*) arg0;
    work_ctr_3 = 4;
    do {
        work_r3[0] = work_r3[0] >> 2;
        work_r3[1] = work_r3[1] >> 2;
        work_r3[2] = work_r3[2] >> 2;
        work_r3[3] = work_r3[3] >> 2;
        work_r3[4] = work_r3[4] >> 2;
        work_r3[5] = work_r3[5] >> 2;
        work_r3[6] = work_r3[6] >> 2;
        work_r3[7] = work_r3[7] >> 2;
        work_r3[8] = work_r3[8] >> 2;
        work_r3[9] = work_r3[9] >> 2;
        work_r3[10] = work_r3[10] >> 2;
        work_r3[11] = work_r3[11] >> 2;
        work_r3[12] = work_r3[12] >> 2;
        work_r3[13] = work_r3[13] >> 2;
        work_r3[14] = work_r3[14] >> 2;
        work_r3[15] = work_r3[15] >> 2;
        work_r3 += 16;
        work_ctr_3 -= 1;
    } while (work_ctr_3 != 0);
}

static void fn_803B6820(u8* arg0, s32 arg1, s32 arg2, s32 arg3,
                        s32 unused_arg4)
{
    f32 scratch_f0;
    f32 scratch_f0_2;
    f32 scratch_f0_3;
    s32 scratch_r18;
    s32 scratch_r19;
    s32 scratch_r20;
    s32 scratch_r6;
    u8* base;
    s32 work_ctr;
    s32 work_ctr_2;
    s32 work_r10;
    s32 work_r12;
    s32 work_r21;
    s32 work_r22;
    s32 work_r23;
    s32 work_r24;
    s32 work_r25;
    s32 work_r31;
    s32 work_r4;
    s32 work_r5;
    s32 work_r6;
    s32 work_r7;
    s32 work_r8_2;
    u16* work_r9_2;
    u8 work_r16;
    u8 work_r16_2;
    u8 work_r17;
    u8* work_r27;
    u8* work_r8;
    u8* work_r9;
    u8* scratch_r16;

    PAD_STACK(0x30);
    base = hsd_804D2E70;
    work_r9 = &base[0x118];
    for (work_r10 = 0; work_r10 < 4; work_r10++) {
        work_r8 = work_r9;
        for (work_ctr = 4; work_ctr != 0; work_ctr--) {
            M2C_FIELD(work_r8, s32*, 0) =
                (s32) (M2C_FIELD(work_r8, s32*, 0) + 0x80);
            M2C_FIELD(work_r8, s32*, 4) =
                (s32) (M2C_FIELD(work_r8, s32*, 4) + 0x80);
            M2C_FIELD(work_r8, s32*, 8) =
                (s32) (M2C_FIELD(work_r8, s32*, 8) + 0x80);
            M2C_FIELD(work_r8, s32*, 0xC) =
                (s32) (M2C_FIELD(work_r8, s32*, 0xC) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x10) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x10) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x14) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x14) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x18) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x18) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x1C) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x1C) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x20) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x20) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x24) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x24) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x28) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x28) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x2C) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x2C) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x30) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x30) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x34) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x34) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x38) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x38) + 0x80);
            M2C_FIELD(work_r8, s32*, 0x3C) =
                (s32) (M2C_FIELD(work_r8, s32*, 0x3C) + 0x80);
            work_r8 += 0x40;
        }
        work_r9 += 0x100;
    }
    scratch_r6 = (s32) (arg3 + 0xF) / 16;
    work_r23 = arg2 / 4;
    work_r22 = 0;
    work_r21 = 0;
    for (work_r6 = 0; work_r6 < 2; work_r6++) {
        work_r25 = work_r22;
        work_r9_2 = (u16*) arg0 +
                    (((arg1 / 4) * 0x10) + ((scratch_r6 << 6) * work_r23));
        work_r24 = 0;
        for (work_r7 = 0; work_r7 < 2; work_r7++) {
            work_r12 = work_r21 * 8;
            for (work_r4 = 0; work_r4 < 4; work_r4++) {
                work_r31 = (work_r24 + work_r12) * 4;
                for (work_r5 = 0; work_r5 < 4; work_r5++) {
                    work_r8_2 = 0;
                    work_r27 = &base[work_r31] + 0x118;
                    for (work_ctr_2 = 4; work_ctr_2 != 0; work_ctr_2--) {
                        scratch_r19 = *work_r27;
                        scratch_r16 =
                            base + (((work_r5 >> 1) +
                                     (work_r25 + ((work_r4 * 4) & 8)) +
                                     (((work_r8_2 % 2) * 4) +
                                      ((work_r8_2 / 2) << 5))) *
                                    4);
                        scratch_r20 = M2C_FIELD(scratch_r16, s32*, 0x618);
                        scratch_r18 = M2C_FIELD(scratch_r16, s32*, 0x518);
                        scratch_f0 = (f32) ((1.402f * (f64) scratch_r20) +
                                            (f64) scratch_r19);
                        if (scratch_f0 < 0.0f) {
                            work_r16 = 0;
                        } else if (255.0f < scratch_f0) {
                            work_r16 = 0xFF;
                        } else {
                            work_r16 = (u8) (s32) scratch_f0;
                        }
                        scratch_f0_2 = ((f32) scratch_r19 -
                                        (0.3441f * (f32) scratch_r18)) -
                                       (0.7139f * (f32) scratch_r20);
                        if (scratch_f0_2 < 0.0f) {
                            work_r17 = 0;
                        } else if (255.0f < scratch_f0_2) {
                            work_r17 = 0xFF;
                        } else {
                            work_r17 = (u8) (s32) scratch_f0_2;
                        }
                        scratch_f0_3 =
                            (f32) ((f64) ((1.7718f * (f32) scratch_r18) +
                                          (f32) scratch_r19) -
                                   (0.0012f * (f64) scratch_r20));
                        if (scratch_f0_3 < 0.0f) {
                            work_r16_2 = 0;
                        } else if (255.0f < scratch_f0_3) {
                            work_r16_2 = 0xFF;
                        } else {
                            work_r16_2 = (u8) (s32) scratch_f0_3;
                        }
                        work_r9_2[((work_r8_2 & 1) << 5) +
                                  ((scratch_r6 << 4) *
                                   ((work_r8_2 << 2) & 8))] =
                            ((work_r16 << 8) & 0xF800) |
                            ((work_r17 << 3) & 0x7E0) | (work_r16_2 >> 3U);
                        work_r27 += 0x100;
                        work_r8_2 += 1;
                    }
                    work_r9_2 += 1;
                    work_r31 += 4;
                }
                work_r12 += 8;
            }
            work_r25 += 2;
            work_r24 += 4;
        }
        work_r23 += 1;
        work_r22 += 0x10;
        work_r21 += 4;
    }
}

s32 hsd_803B6BE4(char* arg0, s32 arg1, void* arg2)
{
    s32* base_s32;
    u8* base;
    u8* quant_table;
    s32 work_r28;
    s32 work_r29;
    s32 scratch_r6_4;
    s32 scratch_r7;
    s32 scratch_r7_3;
    s32 work_r23;
    s32 work_r25;
    s32 work_r26;
    s32 work_r3;
    s32 work_r3_2;
    s32 work_r3_3;
    s32 work_r3_4;
    s32 work_r3_5;
    u8 scratch_r0;
    u8 scratch_r0_3;
    u8 scratch_r0_7;
    u8 scratch_r6_3;
    u8 scratch_r7_2;
    u8* scratch_r0_2;
    u8* scratch_r0_4;
    u8* scratch_r0_5;
    u8* scratch_r0_6;
    u8* scratch_r5;
    u8* scratch_r5_10;
    u8* scratch_r5_11;
    u8* scratch_r5_12;
    u8* scratch_r5_13;
    u8* scratch_r5_14;
    u8* scratch_r5_15;
    u8* scratch_r5_16;
    u8* scratch_r5_17;
    u8* scratch_r5_2;
    u8* scratch_r5_3;
    u8* scratch_r5_4;
    u8* scratch_r5_5;
    u8* scratch_r5_6;
    u8* scratch_r5_7;
    u8* scratch_r5_8;
    u8* scratch_r5_9;
    u8* scratch_r6;
    u8* scratch_r6_2;
    u8* work_r24;
    u8* work_r24_2;
    u8* work_r4;
    u8* work_r4_2;
    u8* work_r4_3;
    u8* work_r4_4;
    u8* work_r4_5;
    u8* work_r5;
    u8* work_r5_2;

    PAD_STACK(0x48);
    base_s32 = (s32*) hsd_804D2E70;
    hsd_804D79C0 = arg1;
    quant_table = lbl_80431090;
    hsd_804D79B8 = (u8*) arg0;
    hsd_804D79BC = (u8*) arg0;
    base = ((HSD_JpegWork*) base_s32)->data;
    base_s32[0x208] = 0;
    base_s32[0x207] = 0;
    base_s32[0x206] = 0;
    hsd_804D79C4 = 0;
    if (__setjmp((__jmp_buf*) base_s32) != 0) {
        return 0;
    }
    scratch_r5 = &hsd_804D79BC[hsd_804D79C0];
loop_3:
    if (*(u16*) hsd_804D79B8 == 0xFFDB) {
        work_r4 = lbl_80431638;
        hsd_804D79B8 += 5;
        for (work_r3 = 0; work_r3 < 0x40; work_r3 += 8) {
            scratch_r5 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5 + 1;
            *(quant_table + M2C_FIELD(work_r4, u8*, 0)) = *scratch_r5;
            scratch_r5_2 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_2 + 1;
            *(quant_table + work_r4[1]) = *scratch_r5_2;
            scratch_r5_3 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_3 + 1;
            *(quant_table + work_r4[2]) = *scratch_r5_3;
            scratch_r5_4 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_4 + 1;
            *(quant_table + work_r4[3]) = *scratch_r5_4;
            scratch_r5_5 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_5 + 1;
            *(quant_table + work_r4[4]) = *scratch_r5_5;
            scratch_r5_6 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_6 + 1;
            *(quant_table + work_r4[5]) = *scratch_r5_6;
            scratch_r5_7 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_7 + 1;
            *(quant_table + work_r4[6]) = *scratch_r5_7;
            scratch_r5_8 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_8 + 1;
            scratch_r0 = work_r4[7];
            work_r4 += 8;
            *(quant_table + scratch_r0) = *scratch_r5_8;
        }
    } else {
        scratch_r0_2 = hsd_804D79B8 + 1;
        hsd_804D79B8 = scratch_r0_2;
        if (scratch_r0_2 >= scratch_r5) {
            longjmp((__jmp_buf*) base, 1);
        } else {
            goto loop_3;
        }
    }
    scratch_r5 = &hsd_804D79BC[hsd_804D79C0];
loop_11:
    if (*(u16*) hsd_804D79B8 == 0xFFDB) {
        work_r4_2 = lbl_80431638;
        hsd_804D79B8 += 5;
        for (work_r3_2 = 0; work_r3_2 < 0x40; work_r3_2 += 8) {
            scratch_r5_9 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_9 + 1;
            M2C_FIELD((quant_table + M2C_FIELD(work_r4_2, u8*, 0)), u8*,
                      0x40) = (u8) *scratch_r5_9;
            scratch_r5_10 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_10 + 1;
            M2C_FIELD((quant_table + work_r4_2[1]), u8*, 0x40) =
                (u8) *scratch_r5_10;
            scratch_r5_11 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_11 + 1;
            M2C_FIELD((quant_table + work_r4_2[2]), u8*, 0x40) =
                (u8) *scratch_r5_11;
            scratch_r5_12 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_12 + 1;
            M2C_FIELD((quant_table + work_r4_2[3]), u8*, 0x40) =
                (u8) *scratch_r5_12;
            scratch_r5_13 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_13 + 1;
            M2C_FIELD((quant_table + work_r4_2[4]), u8*, 0x40) =
                (u8) *scratch_r5_13;
            scratch_r5_14 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_14 + 1;
            M2C_FIELD((quant_table + work_r4_2[5]), u8*, 0x40) =
                (u8) *scratch_r5_14;
            scratch_r5_15 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_15 + 1;
            M2C_FIELD((quant_table + work_r4_2[6]), u8*, 0x40) =
                (u8) *scratch_r5_15;
            scratch_r5_16 = hsd_804D79B8;
            hsd_804D79B8 = scratch_r5_16 + 1;
            scratch_r0_3 = work_r4_2[7];
            work_r4_2 += 8;
            M2C_FIELD((quant_table + scratch_r0_3), u8*, 0x40) =
                (u8) *scratch_r5_16;
        }
    } else {
        scratch_r0_4 = hsd_804D79B8 + 1;
        hsd_804D79B8 = scratch_r0_4;
        if (scratch_r0_4 >= scratch_r5) {
            longjmp((__jmp_buf*) base, 1);
        } else {
            goto loop_11;
        }
    }
    scratch_r5 = &hsd_804D79BC[hsd_804D79C0];
loop_19:
    if (*(u16*) hsd_804D79B8 == 0xFFC0) {
        hsd_804D79B8 += 5;
        work_r28 = *(u16*) hsd_804D79B8;
        hsd_804D79B8 += 2;
        work_r29 = *(u16*) hsd_804D79B8;
        hsd_804D79B8 += 0xC;
    } else {
        scratch_r0_5 = hsd_804D79B8 + 1;
        hsd_804D79B8 = scratch_r0_5;
        if (scratch_r0_5 >= scratch_r5) {
            longjmp((__jmp_buf*) base, 1);
        } else {
            goto loop_19;
        }
    }
    scratch_r5 = &hsd_804D79BC[hsd_804D79C0];
loop_24:
    if (*(u16*) hsd_804D79B8 == 0xFFDA) {
        hsd_804D79B8 += 2;
        hsd_804D79B8 += 0xC;
    } else {
        scratch_r0_6 = hsd_804D79B8 + 1;
        hsd_804D79B8 = scratch_r0_6;
        if (scratch_r0_6 >= scratch_r5) {
            longjmp((__jmp_buf*) base, 1);
        } else {
            goto loop_24;
        }
    }
    for (work_r25 = 0; work_r25 < (s32) work_r28; work_r25 += 0x10) {
        for (work_r26 = 0; work_r26 < (s32) work_r29; work_r26 += 0x10) {
            work_r24 = &base[0x118];
            for (work_r23 = 0; work_r23 < 4; work_r23++) {
                hsd_803B5EA0(0);
                work_r5 = work_r24;
                work_r4_3 = &base[0x718];
                for (work_r3_3 = 0; work_r3_3 < 0x40; work_r3_3 += 8) {
                    scratch_r6 = quant_table + work_r3_3;
                    scratch_r0_7 = M2C_FIELD(scratch_r6, u8*, 0);
                    M2C_FIELD(work_r5, s32*, 0) =
                        (s32) (M2C_FIELD(work_r4_3, s32*, 0) * scratch_r0_7);
                    M2C_FIELD(work_r5, s32*, 4) =
                        (s32) (M2C_FIELD(work_r4_3, s32*, 4) *
                               M2C_FIELD(scratch_r6, u8*, 1));
                    M2C_FIELD(work_r5, s32*, 8) =
                        (s32) (M2C_FIELD(work_r4_3, s32*, 8) *
                               M2C_FIELD(scratch_r6, u8*, 2));
                    M2C_FIELD(work_r5, s32*, 0xC) =
                        (s32) (M2C_FIELD(work_r4_3, s32*, 0xC) *
                               M2C_FIELD(scratch_r6, u8*, 3));
                    M2C_FIELD(work_r5, s32*, 0x10) =
                        (s32) (M2C_FIELD(work_r4_3, s32*, 0x10) *
                               M2C_FIELD(scratch_r6, u8*, 4));
                    M2C_FIELD(work_r5, s32*, 0x14) =
                        (s32) (M2C_FIELD(work_r4_3, s32*, 0x14) *
                               M2C_FIELD(scratch_r6, u8*, 5));
                    M2C_FIELD(work_r5, s32*, 0x18) =
                        (s32) (M2C_FIELD(work_r4_3, s32*, 0x18) *
                               M2C_FIELD(scratch_r6, u8*, 6));
                    scratch_r7 = M2C_FIELD(work_r4_3, s32*, 0x1C);
                    work_r4_3 += 0x20;
                    M2C_FIELD(work_r5, s32*, 0x1C) =
                        (s32) (scratch_r7 * M2C_FIELD(scratch_r6, u8*, 7));
                    work_r5 += 0x20;
                }
                fn_803B61B4(work_r24);
                work_r24 += 0x100;
            }
            hsd_803B5EA0(1);
            work_r24_2 = &base[0x718];
            work_r4_4 = work_r24_2;
            work_r5_2 = &base[0x518];
            for (work_r3_4 = 0; work_r3_4 < 0x40; work_r3_4 += 8) {
                scratch_r6_2 = quant_table + 0x40 + work_r3_4;
                scratch_r7_2 = M2C_FIELD(scratch_r6_2, u8*, 0);
                M2C_FIELD(work_r5_2, s32*, 0) =
                    (s32) (M2C_FIELD(work_r4_4, s32*, 0) * scratch_r7_2);
                M2C_FIELD(work_r5_2, s32*, 4) =
                    (s32) (M2C_FIELD(work_r4_4, s32*, 4) *
                           M2C_FIELD(scratch_r6_2, u8*, 1));
                M2C_FIELD(work_r5_2, s32*, 8) =
                    (s32) (M2C_FIELD(work_r4_4, s32*, 8) *
                           M2C_FIELD(scratch_r6_2, u8*, 2));
                M2C_FIELD(work_r5_2, s32*, 0xC) =
                    (s32) (M2C_FIELD(work_r4_4, s32*, 0xC) *
                           M2C_FIELD(scratch_r6_2, u8*, 3));
                M2C_FIELD(work_r5_2, s32*, 0x10) =
                    (s32) (M2C_FIELD(work_r4_4, s32*, 0x10) *
                           M2C_FIELD(scratch_r6_2, u8*, 4));
                M2C_FIELD(work_r5_2, s32*, 0x14) =
                    (s32) (M2C_FIELD(work_r4_4, s32*, 0x14) *
                           M2C_FIELD(scratch_r6_2, u8*, 5));
                M2C_FIELD(work_r5_2, s32*, 0x18) =
                    (s32) (M2C_FIELD(work_r4_4, s32*, 0x18) *
                           M2C_FIELD(scratch_r6_2, u8*, 6));
                scratch_r7_3 = M2C_FIELD(work_r4_4, s32*, 0x1C);
                work_r4_4 += 0x20;
                M2C_FIELD(work_r5_2, s32*, 0x1C) =
                    (s32) (scratch_r7_3 * M2C_FIELD(scratch_r6_2, u8*, 7));
                work_r5_2 += 0x20;
            }
            fn_803B61B4(&base[0x518]);
            hsd_803B5EA0(2);
            work_r4_5 = &base[0x618];
            for (work_r3_5 = 0; work_r3_5 < 0x40; work_r3_5 += 8) {
                scratch_r5_17 = quant_table + 0x40 + work_r3_5;
                scratch_r6_3 = M2C_FIELD(scratch_r5_17, u8*, 0);
                M2C_FIELD(work_r4_5, s32*, 0) =
                    (s32) (M2C_FIELD(work_r24_2, s32*, 0) * scratch_r6_3);
                M2C_FIELD(work_r4_5, s32*, 4) =
                    (s32) (M2C_FIELD(work_r24_2, s32*, 4) *
                           M2C_FIELD(scratch_r5_17, u8*, 1));
                M2C_FIELD(work_r4_5, s32*, 8) =
                    (s32) (M2C_FIELD(work_r24_2, s32*, 8) *
                           M2C_FIELD(scratch_r5_17, u8*, 2));
                M2C_FIELD(work_r4_5, s32*, 0xC) =
                    (s32) (M2C_FIELD(work_r24_2, s32*, 0xC) *
                           M2C_FIELD(scratch_r5_17, u8*, 3));
                M2C_FIELD(work_r4_5, s32*, 0x10) =
                    (s32) (M2C_FIELD(work_r24_2, s32*, 0x10) *
                           M2C_FIELD(scratch_r5_17, u8*, 4));
                M2C_FIELD(work_r4_5, s32*, 0x14) =
                    (s32) (M2C_FIELD(work_r24_2, s32*, 0x14) *
                           M2C_FIELD(scratch_r5_17, u8*, 5));
                M2C_FIELD(work_r4_5, s32*, 0x18) =
                    (s32) (M2C_FIELD(work_r24_2, s32*, 0x18) *
                           M2C_FIELD(scratch_r5_17, u8*, 6));
                scratch_r6_4 = M2C_FIELD(work_r24_2, s32*, 0x1C);
                work_r24_2 += 0x20;
                M2C_FIELD(work_r4_5, s32*, 0x1C) =
                    (s32) (scratch_r6_4 * M2C_FIELD(scratch_r5_17, u8*, 7));
                work_r4_5 += 0x20;
            }
            fn_803B61B4(&base[0x618]);
            fn_803B6820((u8*) arg2, work_r26, work_r25, (s32) work_r29,
                        (s32) work_r28);
        }
    }
    return work_r29 * work_r28 * 2;
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
