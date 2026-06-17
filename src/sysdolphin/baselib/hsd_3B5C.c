#include "hsd_3B34.h"

#include <placeholder.h>

#include <Gecko_setjmp.h>

extern u8 hsd_804D2E70[2084];
extern u8* hsd_804D79B8;
extern u8* hsd_804D79BC;
extern s32 hsd_804D79C0;
extern s32 hsd_804D79C4;
extern u8 hsd_804D79C8;

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
    u8* temp_r3;

    do {
        if ((s32) hsd_804D79C4 == 0) {
            hsd_804D79C4 = 8;
            if ((u8*) hsd_804D79B8 >= &hsd_804D79BC[hsd_804D79C0]) {
                longjmp(jmp_buf, 1);
            }
            temp_r3 = hsd_804D79B8;
            hsd_804D79B8 = temp_r3 + 1;
            hsd_804D79C8 = *temp_r3;
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
    goto block_23;
loop_23:
    if (code == (s32) *code_table_tmp) {
        return value_table[value_idx];
    }
    code_table_tmp += 1;
    code_cursor += 1;
    value_idx += 1;
    length_table += 1;
block_23:
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
    s32 temp_r29;
    s32 temp_r29_2;
    s32 temp_r29_3;
    s32 temp_r29_4;
    s32 temp_r29_5;
    s32 temp_r29_6;
    s32 temp_r3_2;
    s32 var_r29;
    s32 var_r3;
    s32 var_r3_4;
    u32 temp_r0_4;
    u32 temp_r8;
    u32 var_ctr_3;
    u32 var_ctr_4;
    u32 var_r3_3;
    u8 temp_r0_5;
    u8 temp_r0_6;
    s32 temp_r27;
    s32* temp_r5;

    temp_r27 = hsd_803B5D70(0, arg0);
    if (temp_r27 > 0) {
        var_r3 = hsd_803B5C4C(temp_r27);
        if (!(var_r3 & (1 << (temp_r27 - 1)))) {
            var_r3 -= (1 << temp_r27) - 1;
        }
    } else {
        var_r3 = 0;
    }
    temp_r5 = (s32*) (hsd_804D2E70 + (arg0 * 4));
    temp_r5[0x206] = (s32) (temp_r5[0x206] + var_r3);
    var_r29 = 1;
    M2C_FIELD(hsd_804D2E70, s32*, 0x718) = (s32) temp_r5[0x206];
    while (var_r29 < 0x40) {
        if ((temp_r3_2 = hsd_803B5D70(1, arg0)) == 0) {
            while (var_r29 < 0x40) {
                M2C_FIELD((hsd_804D2E70 + (lbl_80431638[var_r29] * 4)), s32*,
                          0x718) = 0;
                var_r29 += 1;
            }
            return;
        } else {
            temp_r8 = hsd_803B5C4C(temp_r3_2) - 1;
            var_r3_3 = temp_r8;
            if (temp_r8 != 0) {
                temp_r0_4 = var_r3_3 >> 3U;
                var_ctr_3 = temp_r0_4;
                if (temp_r0_4 != 0) {
                    do {
                        temp_r29 = var_r29 + 1;
                        M2C_FIELD((hsd_804D2E70 + (lbl_80431638[var_r29] * 4)),
                                  s32*, 0x718) = 0;
                        temp_r29_2 = temp_r29 + 1;
                        M2C_FIELD(
                            (hsd_804D2E70 +
                             (M2C_FIELD(&lbl_80431638[var_r29], u8*, 1) * 4)),
                            s32*, 0x718) = 0;
                        temp_r29_3 = temp_r29_2 + 1;
                        temp_r29_4 = temp_r29_3 + 1;
                        M2C_FIELD(
                            (hsd_804D2E70 +
                             (M2C_FIELD(&lbl_80431638[temp_r29], u8*, 1) * 4)),
                            s32*, 0x718) = 0;
                        temp_r29_5 = temp_r29_4 + 1;
                        M2C_FIELD(
                            (hsd_804D2E70 +
                             (M2C_FIELD(&lbl_80431638[temp_r29_2], u8*, 1) *
                              4)),
                            s32*, 0x718) = 0;
                        temp_r29_6 = temp_r29_5 + 1;
                        M2C_FIELD(
                            (hsd_804D2E70 +
                             (M2C_FIELD(&lbl_80431638[temp_r29_3], u8*, 1) *
                              4)),
                            s32*, 0x718) = 0;
                        M2C_FIELD(
                            (hsd_804D2E70 +
                             (M2C_FIELD(&lbl_80431638[temp_r29_4], u8*, 1) *
                              4)),
                            s32*, 0x718) = 0;
                        var_r29 = temp_r29_6 + 1 + 1;
                        M2C_FIELD(
                            (hsd_804D2E70 +
                             (M2C_FIELD(&lbl_80431638[temp_r29_5], u8*, 1) *
                              4)),
                            s32*, 0x718) = 0;
                        M2C_FIELD(
                            (hsd_804D2E70 +
                             (M2C_FIELD(&lbl_80431638[temp_r29_6], u8*, 1) *
                              4)),
                            s32*, 0x718) = 0;
                        var_ctr_3 -= 1;
                    } while (var_ctr_3 != 0);
                    var_r3_3 &= 7;
                    if (var_r3_3 != 0) {
                        goto block_17;
                    }
                } else {
                block_17:
                    var_ctr_4 = var_r3_3;
                    do {
                        temp_r0_5 = lbl_80431638[var_r29];
                        var_r29 += 1;
                        M2C_FIELD((hsd_804D2E70 + (temp_r0_5 * 4)), s32*,
                                  0x718) = 0;
                        var_ctr_4 -= 1;
                    } while (var_ctr_4 != 0);
                }
            }
            temp_r27 = hsd_803B5D70(1, arg0);
            var_r3_4 = hsd_803B5C4C(temp_r27);
            if (!(var_r3_4 & (1 << (temp_r27 - 1)))) {
                var_r3_4 -= (1 << temp_r27) - 1;
            }
            temp_r0_6 = lbl_80431638[var_r29];
            var_r29 += 1;
            M2C_FIELD((hsd_804D2E70 + (temp_r0_6 * 4)), s32*, 0x718) =
                var_r3_4;
        }
    }
}
#pragma dont_inline off

static void fn_803B61B4(u8* arg0)
{
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f13_3;
    f32 temp_f13_4;
    f32 temp_f13_5;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f23;
    f32 temp_f23_2;
    f32 temp_f23_3;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f24_3;
    f32 temp_f24_4;
    f32 temp_f25;
    f32 temp_f25_2;
    f32 temp_f25_3;
    f32 temp_f25_4;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f9;
    f32 temp_f9_2;
    f32 temp_f9_3;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r5_5;
    s32 temp_r5_6;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32* var_r3;
    s32* var_r4;
    s32* var_r4_2;

    var_r4 = (s32*) arg0;
    for (var_ctr = 8; var_ctr != 0; var_ctr--) {
        temp_r5 = var_r4[1];
        temp_r0 = var_r4[3];
        temp_r6 = var_r4[7];
        temp_r5_2 = var_r4[5];
        temp_r11 = var_r4[0];
        temp_r10 = var_r4[4];
        temp_f22 =
            (f32) ((0.980785f * (f64) temp_r6) - (0.19509f * (f64) temp_r5));
        temp_f31 =
            (f32) ((0.83147f * (f64) temp_r5_2) - (0.55557f * (f64) temp_r0));
        temp_f23 =
            (f32) ((0.55557f * (f64) temp_r5_2) + (0.83147f * (f64) temp_r0));
        temp_f24 =
            (f32) ((0.19509f * (f64) temp_r6) + (0.980785f * (f64) temp_r5));
        temp_f10 = (f32) (0.707107f * (f64) (temp_r11 + temp_r10));
        temp_f11 = (f32) (0.707107f * (f64) (temp_r11 - temp_r10));
        temp_r0_2 = var_r4[2];
        temp_f12 = temp_f22 + temp_f31;
        temp_r5_3 = var_r4[6];
        temp_f13 = -temp_f23 + temp_f24;
        temp_f13_2 = temp_f23 + temp_f24;
        temp_f9 = (f32) (0.707107f * (f64) (-temp_f12 + temp_f13));
        temp_f25 = (f32) ((-0.92388f * (f64) temp_r5_3) +
                          (0.382683f * (f64) temp_r0_2));
        temp_f12_2 = (f32) ((0.382683f * (f64) temp_r5_3) +
                            (0.92388f * (f64) temp_r0_2));
        temp_f23_2 = temp_f10 + temp_f12_2;
        temp_f22_2 = (f32) (0.707107f * (f64) (temp_f12 + temp_f13));
        temp_f24_2 = temp_f11 + temp_f25;
        temp_f25_2 = temp_f11 - temp_f25;
        var_r4[0] = (s32) (temp_f23_2 + temp_f13_2);
        var_r4[1] = (s32) (temp_f24_2 + temp_f9);
        temp_f13_3 = -temp_f22 + temp_f31;
        temp_f10_2 = temp_f10 - temp_f12_2;
        var_r4[2] = (s32) (temp_f25_2 + temp_f22_2);
        var_r4[3] = (s32) (temp_f10_2 + temp_f13_3);
        var_r4[4] = (s32) (temp_f10_2 - temp_f13_3);
        var_r4[5] = (s32) (temp_f25_2 - temp_f22_2);
        var_r4[6] = (s32) (temp_f24_2 - temp_f9);
        var_r4[7] = (s32) (temp_f23_2 - temp_f13_2);
        var_r4 += 8;
    }
    var_r4_2 = (s32*) arg0;
    for (var_ctr_2 = 8; var_ctr_2 != 0; var_ctr_2--) {
        temp_r5_4 = var_r4_2[8];
        temp_r0_3 = var_r4_2[24];
        temp_r6_2 = var_r4_2[56];
        temp_r5_5 = var_r4_2[40];
        temp_r11_2 = var_r4_2[0];
        temp_r10_2 = var_r4_2[32];
        temp_f26 = (f32) ((0.980785f * (f64) temp_r6_2) -
                          (0.19509f * (f64) temp_r5_4));
        temp_f9_2 = (f32) ((0.83147f * (f64) temp_r5_5) -
                           (0.55557f * (f64) temp_r0_3));
        temp_f27 = (f32) ((0.55557f * (f64) temp_r5_5) +
                          (0.83147f * (f64) temp_r0_3));
        temp_f30 = (f32) ((0.19509f * (f64) temp_r6_2) +
                          (0.980785f * (f64) temp_r5_4));
        temp_f10_3 = (f32) (0.707107f * (f64) (temp_r11_2 + temp_r10_2));
        temp_f25_3 = (f32) (0.707107f * (f64) (temp_r11_2 - temp_r10_2));
        temp_r0_4 = var_r4_2[16];
        temp_f13_4 = temp_f26 + temp_f9_2;
        temp_r5_6 = var_r4_2[48];
        temp_f29 = -temp_f27 + temp_f30;
        temp_f11_2 = temp_f27 + temp_f30;
        temp_f12_3 = (f32) (0.707107f * (f64) (-temp_f13_4 + temp_f29));
        temp_f13_5 = (f32) ((-0.92388f * (f64) temp_r5_6) +
                            (0.382683f * (f64) temp_r0_4));
        temp_f26_2 = (f32) ((0.382683f * (f64) temp_r5_6) +
                            (0.92388f * (f64) temp_r0_4));
        temp_f27_2 = temp_f10_3 + temp_f26_2;
        temp_f23_3 = (f32) (0.707107f * (f64) (temp_f13_4 + temp_f29));
        temp_f24_3 = temp_f25_3 + temp_f13_5;
        temp_f25_4 = temp_f25_3 - temp_f13_5;
        var_r4_2[0] = (s32) (temp_f27_2 + temp_f11_2);
        var_r4_2[8] = (s32) (temp_f24_3 + temp_f12_3);
        temp_f9_3 = -temp_f26 + temp_f9_2;
        temp_f24_4 = temp_f10_3 - temp_f26_2;
        var_r4_2[16] = (s32) (temp_f25_4 + temp_f23_3);
        var_r4_2[24] = (s32) (temp_f24_4 + temp_f9_3);
        var_r4_2[32] = (s32) (temp_f24_4 - temp_f9_3);
        var_r4_2[40] = (s32) (temp_f25_4 - temp_f23_3);
        var_r4_2[48] = (s32) (temp_f24_3 - temp_f12_3);
        var_r4_2[56] = (s32) (temp_f27_2 - temp_f11_2);
        var_r4_2 += 1;
    }
    var_r3 = (s32*) arg0;
    var_ctr_3 = 4;
    do {
        var_r3[0] = var_r3[0] >> 2;
        var_r3[1] = var_r3[1] >> 2;
        var_r3[2] = var_r3[2] >> 2;
        var_r3[3] = var_r3[3] >> 2;
        var_r3[4] = var_r3[4] >> 2;
        var_r3[5] = var_r3[5] >> 2;
        var_r3[6] = var_r3[6] >> 2;
        var_r3[7] = var_r3[7] >> 2;
        var_r3[8] = var_r3[8] >> 2;
        var_r3[9] = var_r3[9] >> 2;
        var_r3[10] = var_r3[10] >> 2;
        var_r3[11] = var_r3[11] >> 2;
        var_r3[12] = var_r3[12] >> 2;
        var_r3[13] = var_r3[13] >> 2;
        var_r3[14] = var_r3[14] >> 2;
        var_r3[15] = var_r3[15] >> 2;
        var_r3 += 16;
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
}

static void fn_803B6820(u8* arg0, s32 arg1, s32 arg2, s32 arg3,
                        s32 unused_arg4)
{
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    s32 temp_r18;
    s32 temp_r19;
    s32 temp_r20;
    s32 temp_r6;
    u8* base;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r10;
    s32 var_r12;
    s32 var_r21;
    s32 var_r22;
    s32 var_r23;
    s32 var_r24;
    s32 var_r25;
    s32 var_r31;
    s32 var_r4;
    s32 var_r5;
    s32 var_r6;
    s32 var_r7;
    s32 var_r8_2;
    u16* var_r9_2;
    u8 var_r16;
    u8 var_r16_2;
    u8 var_r17;
    u8* var_r27;
    u8* var_r8;
    u8* var_r9;
    u8* temp_r16;

    PAD_STACK(0x30);
    base = hsd_804D2E70;
    var_r9 = &base[0x118];
    for (var_r10 = 0; var_r10 < 4; var_r10++) {
        var_r8 = var_r9;
        for (var_ctr = 4; var_ctr != 0; var_ctr--) {
            M2C_FIELD(var_r8, s32*, 0) =
                (s32) (M2C_FIELD(var_r8, s32*, 0) + 0x80);
            M2C_FIELD(var_r8, s32*, 4) =
                (s32) (M2C_FIELD(var_r8, s32*, 4) + 0x80);
            M2C_FIELD(var_r8, s32*, 8) =
                (s32) (M2C_FIELD(var_r8, s32*, 8) + 0x80);
            M2C_FIELD(var_r8, s32*, 0xC) =
                (s32) (M2C_FIELD(var_r8, s32*, 0xC) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x10) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x10) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x14) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x14) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x18) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x18) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x1C) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x1C) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x20) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x20) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x24) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x24) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x28) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x28) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x2C) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x2C) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x30) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x30) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x34) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x34) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x38) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x38) + 0x80);
            M2C_FIELD(var_r8, s32*, 0x3C) =
                (s32) (M2C_FIELD(var_r8, s32*, 0x3C) + 0x80);
            var_r8 += 0x40;
        }
        var_r9 += 0x100;
    }
    temp_r6 = (s32) (arg3 + 0xF) / 16;
    var_r23 = arg2 / 4;
    var_r22 = 0;
    var_r21 = 0;
    for (var_r6 = 0; var_r6 < 2; var_r6++) {
        var_r25 = var_r22;
        var_r9_2 =
            (u16*) arg0 + (((arg1 / 4) * 0x10) + ((temp_r6 << 6) * var_r23));
        var_r24 = 0;
        for (var_r7 = 0; var_r7 < 2; var_r7++) {
            var_r12 = var_r21 * 8;
            for (var_r4 = 0; var_r4 < 4; var_r4++) {
                var_r31 = (var_r24 + var_r12) * 4;
                for (var_r5 = 0; var_r5 < 4; var_r5++) {
                    var_r8_2 = 0;
                    var_r27 = &base[var_r31] + 0x118;
                    for (var_ctr_2 = 4; var_ctr_2 != 0; var_ctr_2--) {
                        temp_r19 = *var_r27;
                        temp_r16 =
                            base +
                            (((var_r5 >> 1) + (var_r25 + ((var_r4 * 4) & 8)) +
                              (((var_r8_2 % 2) * 4) + ((var_r8_2 / 2) << 5))) *
                             4);
                        temp_r20 = M2C_FIELD(temp_r16, s32*, 0x618);
                        temp_r18 = M2C_FIELD(temp_r16, s32*, 0x518);
                        temp_f0 =
                            (f32) ((1.402f * (f64) temp_r20) + (f64) temp_r19);
                        if (temp_f0 < 0.0f) {
                            var_r16 = 0;
                        } else if (255.0f < temp_f0) {
                            var_r16 = 0xFF;
                        } else {
                            var_r16 = (u8) (s32) temp_f0;
                        }
                        temp_f0_2 =
                            ((f32) temp_r19 - (0.3441f * (f32) temp_r18)) -
                            (0.7139f * (f32) temp_r20);
                        if (temp_f0_2 < 0.0f) {
                            var_r17 = 0;
                        } else if (255.0f < temp_f0_2) {
                            var_r17 = 0xFF;
                        } else {
                            var_r17 = (u8) (s32) temp_f0_2;
                        }
                        temp_f0_3 = (f32) ((f64) ((1.7718f * (f32) temp_r18) +
                                                  (f32) temp_r19) -
                                           (0.0012f * (f64) temp_r20));
                        if (temp_f0_3 < 0.0f) {
                            var_r16_2 = 0;
                        } else if (255.0f < temp_f0_3) {
                            var_r16_2 = 0xFF;
                        } else {
                            var_r16_2 = (u8) (s32) temp_f0_3;
                        }
                        var_r9_2[((var_r8_2 & 1) << 5) +
                                 ((temp_r6 << 4) * ((var_r8_2 << 2) & 8))] =
                            ((var_r16 << 8) & 0xF800) |
                            ((var_r17 << 3) & 0x7E0) | (var_r16_2 >> 3U);
                        var_r27 += 0x100;
                        var_r8_2 += 1;
                    }
                    var_r9_2 += 1;
                    var_r31 += 4;
                }
                var_r12 += 8;
            }
            var_r25 += 2;
            var_r24 += 4;
        }
        var_r23 += 1;
        var_r22 += 0x10;
        var_r21 += 4;
    }
}

s32 hsd_803B6BE4(char* arg0, s32 arg1, void* arg2)
{
    s32 temp_r6_4;
    s32 temp_r7;
    s32 temp_r7_3;
    s32 var_r23;
    s32 var_r25;
    s32 var_r26;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    u8 temp_r0;
    u8 temp_r0_3;
    u8 temp_r0_7;
    u8 temp_r6_3;
    u8 temp_r7_2;
    u8* temp_r0_2;
    u8* temp_r0_4;
    u8* temp_r0_5;
    u8* temp_r0_6;
    u8* temp_r5;
    u8* temp_r5_10;
    u8* temp_r5_11;
    u8* temp_r5_12;
    u8* temp_r5_13;
    u8* temp_r5_14;
    u8* temp_r5_15;
    u8* temp_r5_16;
    u8* temp_r5_17;
    u8* temp_r5_2;
    u8* temp_r5_3;
    u8* temp_r5_4;
    u8* temp_r5_5;
    u8* temp_r5_6;
    u8* temp_r5_7;
    u8* temp_r5_8;
    u8* temp_r5_9;
    u8* temp_r6;
    u8* temp_r6_2;
    u8* quant_table;
    u8* base;
    s32 var_r28;
    s32 var_r29;
    u8* var_r24;
    u8* var_r24_2;
    u8* var_r4;
    u8* var_r4_2;
    u8* var_r4_3;
    u8* var_r4_4;
    u8* var_r4_5;
    u8* var_r5;
    u8* var_r5_2;

    PAD_STACK(0x48);
    quant_table = lbl_80431090;
    base = hsd_804D2E70;
    hsd_804D79C0 = arg1;
    hsd_804D79B8 = (u8*) arg0;
    hsd_804D79BC = (u8*) arg0;
    M2C_FIELD(base, s32*, 0x820) = 0;
    M2C_FIELD(base, s32*, 0x81C) = 0;
    M2C_FIELD(base, s32*, 0x818) = 0;
    hsd_804D79C4 = 0;
    if (__setjmp((__jmp_buf*) base) != 0) {
        return 0;
    }
loop_3:
    if (*(u16*) hsd_804D79B8 == 0xFFDB) {
        var_r4 = lbl_80431638;
        hsd_804D79B8 += 5;
        for (var_r3 = 0; var_r3 < 0x40; var_r3 += 8) {
            temp_r5 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5 + 1;
            *(quant_table + M2C_FIELD(var_r4, u8*, 0)) = *temp_r5;
            temp_r5_2 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_2 + 1;
            *(quant_table + var_r4[1]) = *temp_r5_2;
            temp_r5_3 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_3 + 1;
            *(quant_table + var_r4[2]) = *temp_r5_3;
            temp_r5_4 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_4 + 1;
            *(quant_table + var_r4[3]) = *temp_r5_4;
            temp_r5_5 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_5 + 1;
            *(quant_table + var_r4[4]) = *temp_r5_5;
            temp_r5_6 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_6 + 1;
            *(quant_table + var_r4[5]) = *temp_r5_6;
            temp_r5_7 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_7 + 1;
            *(quant_table + var_r4[6]) = *temp_r5_7;
            temp_r5_8 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_8 + 1;
            temp_r0 = var_r4[7];
            var_r4 += 8;
            *(quant_table + temp_r0) = *temp_r5_8;
        }
    } else {
        temp_r0_2 = hsd_804D79B8 + 1;
        hsd_804D79B8 = temp_r0_2;
        if (temp_r0_2 >= &hsd_804D79BC[hsd_804D79C0]) {
            longjmp((__jmp_buf*) base, 1);
        } else {
            goto loop_3;
        }
    }
loop_11:
    if (*(u16*) hsd_804D79B8 == 0xFFDB) {
        var_r4_2 = lbl_80431638;
        hsd_804D79B8 += 5;
        for (var_r3_2 = 0; var_r3_2 < 0x40; var_r3_2 += 8) {
            temp_r5_9 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_9 + 1;
            M2C_FIELD((quant_table + M2C_FIELD(var_r4_2, u8*, 0)), u8*, 0x40) =
                (u8) *temp_r5_9;
            temp_r5_10 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_10 + 1;
            M2C_FIELD((quant_table + var_r4_2[1]), u8*, 0x40) =
                (u8) *temp_r5_10;
            temp_r5_11 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_11 + 1;
            M2C_FIELD((quant_table + var_r4_2[2]), u8*, 0x40) =
                (u8) *temp_r5_11;
            temp_r5_12 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_12 + 1;
            M2C_FIELD((quant_table + var_r4_2[3]), u8*, 0x40) =
                (u8) *temp_r5_12;
            temp_r5_13 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_13 + 1;
            M2C_FIELD((quant_table + var_r4_2[4]), u8*, 0x40) =
                (u8) *temp_r5_13;
            temp_r5_14 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_14 + 1;
            M2C_FIELD((quant_table + var_r4_2[5]), u8*, 0x40) =
                (u8) *temp_r5_14;
            temp_r5_15 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_15 + 1;
            M2C_FIELD((quant_table + var_r4_2[6]), u8*, 0x40) =
                (u8) *temp_r5_15;
            temp_r5_16 = hsd_804D79B8;
            hsd_804D79B8 = temp_r5_16 + 1;
            temp_r0_3 = var_r4_2[7];
            var_r4_2 += 8;
            M2C_FIELD((quant_table + temp_r0_3), u8*, 0x40) = (u8) *temp_r5_16;
        }
    } else {
        temp_r0_4 = hsd_804D79B8 + 1;
        hsd_804D79B8 = temp_r0_4;
        if (temp_r0_4 >= &hsd_804D79BC[hsd_804D79C0]) {
            longjmp((__jmp_buf*) base, 1);
        } else {
            goto loop_11;
        }
    }
loop_19:
    if (*(u16*) hsd_804D79B8 == 0xFFC0) {
        hsd_804D79B8 += 5;
        var_r28 = *(u16*) hsd_804D79B8;
        hsd_804D79B8 += 2;
        var_r29 = *(u16*) hsd_804D79B8;
        hsd_804D79B8 += 0xC;
    } else {
        temp_r0_5 = hsd_804D79B8 + 1;
        hsd_804D79B8 = temp_r0_5;
        if (temp_r0_5 >= &hsd_804D79BC[hsd_804D79C0]) {
            longjmp((__jmp_buf*) base, 1);
        } else {
            goto loop_19;
        }
    }
loop_24:
    if (*(u16*) hsd_804D79B8 == 0xFFDA) {
        hsd_804D79B8 += 2;
        hsd_804D79B8 += 0xC;
    } else {
        temp_r0_6 = hsd_804D79B8 + 1;
        hsd_804D79B8 = temp_r0_6;
        if (temp_r0_6 >= &hsd_804D79BC[hsd_804D79C0]) {
            longjmp((__jmp_buf*) base, 1);
        } else {
            goto loop_24;
        }
    }
    for (var_r25 = 0; var_r25 < (s32) var_r28; var_r25 += 0x10) {
        for (var_r26 = 0; var_r26 < (s32) var_r29; var_r26 += 0x10) {
            var_r24 = &base[0x118];
            for (var_r23 = 0; var_r23 < 4; var_r23++) {
                hsd_803B5EA0(0);
                var_r5 = var_r24;
                var_r4_3 = &base[0x718];
                for (var_r3_3 = 0; var_r3_3 < 0x40; var_r3_3 += 8) {
                    temp_r6 = quant_table + var_r3_3;
                    temp_r0_7 = M2C_FIELD(temp_r6, u8*, 0);
                    M2C_FIELD(var_r5, s32*, 0) =
                        (s32) (M2C_FIELD(var_r4_3, s32*, 0) * temp_r0_7);
                    M2C_FIELD(var_r5, s32*, 4) =
                        (s32) (M2C_FIELD(var_r4_3, s32*, 4) *
                               M2C_FIELD(temp_r6, u8*, 1));
                    M2C_FIELD(var_r5, s32*, 8) =
                        (s32) (M2C_FIELD(var_r4_3, s32*, 8) *
                               M2C_FIELD(temp_r6, u8*, 2));
                    M2C_FIELD(var_r5, s32*, 0xC) =
                        (s32) (M2C_FIELD(var_r4_3, s32*, 0xC) *
                               M2C_FIELD(temp_r6, u8*, 3));
                    M2C_FIELD(var_r5, s32*, 0x10) =
                        (s32) (M2C_FIELD(var_r4_3, s32*, 0x10) *
                               M2C_FIELD(temp_r6, u8*, 4));
                    M2C_FIELD(var_r5, s32*, 0x14) =
                        (s32) (M2C_FIELD(var_r4_3, s32*, 0x14) *
                               M2C_FIELD(temp_r6, u8*, 5));
                    M2C_FIELD(var_r5, s32*, 0x18) =
                        (s32) (M2C_FIELD(var_r4_3, s32*, 0x18) *
                               M2C_FIELD(temp_r6, u8*, 6));
                    temp_r7 = M2C_FIELD(var_r4_3, s32*, 0x1C);
                    var_r4_3 += 0x20;
                    M2C_FIELD(var_r5, s32*, 0x1C) =
                        (s32) (temp_r7 * M2C_FIELD(temp_r6, u8*, 7));
                    var_r5 += 0x20;
                }
                fn_803B61B4(var_r24);
                var_r24 += 0x100;
            }
            hsd_803B5EA0(1);
            var_r24_2 = &base[0x718];
            var_r4_4 = var_r24_2;
            var_r5_2 = &base[0x518];
            for (var_r3_4 = 0; var_r3_4 < 0x40; var_r3_4 += 8) {
                temp_r6_2 = quant_table + 0x40 + var_r3_4;
                temp_r7_2 = M2C_FIELD(temp_r6_2, u8*, 0);
                M2C_FIELD(var_r5_2, s32*, 0) =
                    (s32) (M2C_FIELD(var_r4_4, s32*, 0) * temp_r7_2);
                M2C_FIELD(var_r5_2, s32*, 4) =
                    (s32) (M2C_FIELD(var_r4_4, s32*, 4) *
                           M2C_FIELD(temp_r6_2, u8*, 1));
                M2C_FIELD(var_r5_2, s32*, 8) =
                    (s32) (M2C_FIELD(var_r4_4, s32*, 8) *
                           M2C_FIELD(temp_r6_2, u8*, 2));
                M2C_FIELD(var_r5_2, s32*, 0xC) =
                    (s32) (M2C_FIELD(var_r4_4, s32*, 0xC) *
                           M2C_FIELD(temp_r6_2, u8*, 3));
                M2C_FIELD(var_r5_2, s32*, 0x10) =
                    (s32) (M2C_FIELD(var_r4_4, s32*, 0x10) *
                           M2C_FIELD(temp_r6_2, u8*, 4));
                M2C_FIELD(var_r5_2, s32*, 0x14) =
                    (s32) (M2C_FIELD(var_r4_4, s32*, 0x14) *
                           M2C_FIELD(temp_r6_2, u8*, 5));
                M2C_FIELD(var_r5_2, s32*, 0x18) =
                    (s32) (M2C_FIELD(var_r4_4, s32*, 0x18) *
                           M2C_FIELD(temp_r6_2, u8*, 6));
                temp_r7_3 = M2C_FIELD(var_r4_4, s32*, 0x1C);
                var_r4_4 += 0x20;
                M2C_FIELD(var_r5_2, s32*, 0x1C) =
                    (s32) (temp_r7_3 * M2C_FIELD(temp_r6_2, u8*, 7));
                var_r5_2 += 0x20;
            }
            fn_803B61B4(&base[0x518]);
            hsd_803B5EA0(2);
            var_r4_5 = &base[0x618];
            for (var_r3_5 = 0; var_r3_5 < 0x40; var_r3_5 += 8) {
                temp_r5_17 = quant_table + 0x40 + var_r3_5;
                temp_r6_3 = M2C_FIELD(temp_r5_17, u8*, 0);
                M2C_FIELD(var_r4_5, s32*, 0) =
                    (s32) (M2C_FIELD(var_r24_2, s32*, 0) * temp_r6_3);
                M2C_FIELD(var_r4_5, s32*, 4) =
                    (s32) (M2C_FIELD(var_r24_2, s32*, 4) *
                           M2C_FIELD(temp_r5_17, u8*, 1));
                M2C_FIELD(var_r4_5, s32*, 8) =
                    (s32) (M2C_FIELD(var_r24_2, s32*, 8) *
                           M2C_FIELD(temp_r5_17, u8*, 2));
                M2C_FIELD(var_r4_5, s32*, 0xC) =
                    (s32) (M2C_FIELD(var_r24_2, s32*, 0xC) *
                           M2C_FIELD(temp_r5_17, u8*, 3));
                M2C_FIELD(var_r4_5, s32*, 0x10) =
                    (s32) (M2C_FIELD(var_r24_2, s32*, 0x10) *
                           M2C_FIELD(temp_r5_17, u8*, 4));
                M2C_FIELD(var_r4_5, s32*, 0x14) =
                    (s32) (M2C_FIELD(var_r24_2, s32*, 0x14) *
                           M2C_FIELD(temp_r5_17, u8*, 5));
                M2C_FIELD(var_r4_5, s32*, 0x18) =
                    (s32) (M2C_FIELD(var_r24_2, s32*, 0x18) *
                           M2C_FIELD(temp_r5_17, u8*, 6));
                temp_r6_4 = M2C_FIELD(var_r24_2, s32*, 0x1C);
                var_r24_2 += 0x20;
                M2C_FIELD(var_r4_5, s32*, 0x1C) =
                    (s32) (temp_r6_4 * M2C_FIELD(temp_r5_17, u8*, 7));
                var_r4_5 += 0x20;
            }
            fn_803B61B4(&base[0x618]);
            fn_803B6820((u8*) arg2, var_r26, var_r25, (s32) var_r29,
                        (s32) var_r28);
        }
    }
    return var_r29 * var_r28 * 2;
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
