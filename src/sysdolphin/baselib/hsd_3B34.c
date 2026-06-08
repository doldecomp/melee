#include "hsd_3B34.h"

#include "hsd_3B33.h"

#include <placeholder.h>

#include <Gecko_setjmp.h>
#include <string.h>

extern __jmp_buf hsd_804D2648;
extern u8 hsd_804D2E70[2084];
extern u8* hsd_804D79A0;
extern u8* hsd_804D79A4;
extern s32 hsd_804D79A8;
extern s32 hsd_804D79AC;
extern u8 hsd_804D79B0;
extern u8* hsd_804D79B8;
extern u8* hsd_804D79BC;
extern s32 hsd_804D79C0;
extern s32 hsd_804D79C4;
extern u8 hsd_804D79C8;

#define HSD_804D2648_BUF ((u8*) &hsd_804D2648)

static const u8 lbl_803B9670[0x1B6] = {
    0x48, 0x41, 0x4C, 0x20, 0x4C, 0x61, 0x62, 0x6F, 0x72, 0x61, 0x74, 0x6F,
    0x72, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x00, 0x02, 0x01, 0x03,
    0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7D,
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06,
    0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08,
    0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0, 0x24, 0x33, 0x62, 0x72,
    0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75,
    0x76, 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3,
    0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,
    0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9,
    0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2,
    0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4,
    0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0x00, 0x00, 0x00, 0x02, 0x01, 0x02,
    0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77,
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41,
    0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
    0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0, 0x15, 0x62, 0x72, 0xD1,
    0x0A, 0x16, 0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26,
    0x27, 0x28, 0x29, 0x2A, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44,
    0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
    0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x73, 0x74,
    0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A,
    0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4,
    0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
    0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA,
    0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4,
    0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA,
};
static u8 lbl_80430C40[0x40] = {
    0x10, 0x0B, 0x0A, 0x10, 0x18, 0x28, 0x33, 0x3D, 0x0C, 0x0C, 0x0E,
    0x13, 0x1A, 0x3A, 0x3C, 0x37, 0x0E, 0x0D, 0x10, 0x18, 0x28, 0x39,
    0x45, 0x38, 0x0E, 0x11, 0x16, 0x1D, 0x33, 0x57, 0x50, 0x3E, 0x12,
    0x16, 0x25, 0x38, 0x44, 0x6D, 0x67, 0x4D, 0x18, 0x23, 0x37, 0x40,
    0x51, 0x68, 0x71, 0x5C, 0x31, 0x40, 0x4E, 0x57, 0x67, 0x79, 0x78,
    0x65, 0x48, 0x5C, 0x5F, 0x62, 0x70, 0x64, 0x67, 0x63,
};
static u8 lbl_80430C80[0x410] = {
    0x11, 0x12, 0x18, 0x2F, 0x63, 0x63, 0x63, 0x63, 0x12, 0x15, 0x1A, 0x42,
    0x63, 0x63, 0x63, 0x63, 0x18, 0x1A, 0x38, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x2F, 0x42, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04,
    0x00, 0x0B, 0x00, 0x1A, 0x00, 0x78, 0x00, 0xF8, 0x03, 0xF6, 0xFF, 0x82,
    0xFF, 0x83, 0x00, 0x0C, 0x00, 0x1B, 0x00, 0x79, 0x01, 0xF6, 0x07, 0xF6,
    0xFF, 0x84, 0xFF, 0x85, 0xFF, 0x86, 0xFF, 0x87, 0xFF, 0x88, 0x00, 0x1C,
    0x00, 0xF9, 0x03, 0xF7, 0x0F, 0xF4, 0xFF, 0x89, 0xFF, 0x8A, 0xFF, 0x8B,
    0xFF, 0x8C, 0xFF, 0x8D, 0xFF, 0x8E, 0x00, 0x3A, 0x01, 0xF7, 0x0F, 0xF5,
    0xFF, 0x8F, 0xFF, 0x90, 0xFF, 0x91, 0xFF, 0x92, 0xFF, 0x93, 0xFF, 0x94,
    0xFF, 0x95, 0x00, 0x3B, 0x03, 0xF8, 0xFF, 0x96, 0xFF, 0x97, 0xFF, 0x98,
    0xFF, 0x99, 0xFF, 0x9A, 0xFF, 0x9B, 0xFF, 0x9C, 0xFF, 0x9D, 0x00, 0x7A,
    0x07, 0xF7, 0xFF, 0x9E, 0xFF, 0x9F, 0xFF, 0xA0, 0xFF, 0xA1, 0xFF, 0xA2,
    0xFF, 0xA3, 0xFF, 0xA4, 0xFF, 0xA5, 0x00, 0x7B, 0x0F, 0xF6, 0xFF, 0xA6,
    0xFF, 0xA7, 0xFF, 0xA8, 0xFF, 0xA9, 0xFF, 0xAA, 0xFF, 0xAB, 0xFF, 0xAC,
    0xFF, 0xAD, 0x00, 0xFA, 0x0F, 0xF7, 0xFF, 0xAE, 0xFF, 0xAF, 0xFF, 0xB0,
    0xFF, 0xB1, 0xFF, 0xB2, 0xFF, 0xB3, 0xFF, 0xB4, 0xFF, 0xB5, 0x01, 0xF8,
    0x7F, 0xC0, 0xFF, 0xB6, 0xFF, 0xB7, 0xFF, 0xB8, 0xFF, 0xB9, 0xFF, 0xBA,
    0xFF, 0xBB, 0xFF, 0xBC, 0xFF, 0xBD, 0x01, 0xF9, 0xFF, 0xBE, 0xFF, 0xBF,
    0xFF, 0xC0, 0xFF, 0xC1, 0xFF, 0xC2, 0xFF, 0xC3, 0xFF, 0xC4, 0xFF, 0xC5,
    0xFF, 0xC6, 0x01, 0xFA, 0xFF, 0xC7, 0xFF, 0xC8, 0xFF, 0xC9, 0xFF, 0xCA,
    0xFF, 0xCB, 0xFF, 0xCC, 0xFF, 0xCD, 0xFF, 0xCE, 0xFF, 0xCF, 0x03, 0xF9,
    0xFF, 0xD0, 0xFF, 0xD1, 0xFF, 0xD2, 0xFF, 0xD3, 0xFF, 0xD4, 0xFF, 0xD5,
    0xFF, 0xD6, 0xFF, 0xD7, 0xFF, 0xD8, 0x03, 0xFA, 0xFF, 0xD9, 0xFF, 0xDA,
    0xFF, 0xDB, 0xFF, 0xDC, 0xFF, 0xDD, 0xFF, 0xDE, 0xFF, 0xDF, 0xFF, 0xE0,
    0xFF, 0xE1, 0x07, 0xF8, 0xFF, 0xE2, 0xFF, 0xE3, 0xFF, 0xE4, 0xFF, 0xE5,
    0xFF, 0xE6, 0xFF, 0xE7, 0xFF, 0xE8, 0xFF, 0xE9, 0xFF, 0xEA, 0xFF, 0xEB,
    0xFF, 0xEC, 0xFF, 0xED, 0xFF, 0xEE, 0xFF, 0xEF, 0xFF, 0xF0, 0xFF, 0xF1,
    0xFF, 0xF2, 0xFF, 0xF3, 0xFF, 0xF4, 0x07, 0xF9, 0xFF, 0xF5, 0xFF, 0xF6,
    0xFF, 0xF7, 0xFF, 0xF8, 0xFF, 0xF9, 0xFF, 0xFA, 0xFF, 0xFB, 0xFF, 0xFC,
    0xFF, 0xFD, 0xFF, 0xFE, 0x04, 0x02, 0x02, 0x03, 0x04, 0x05, 0x07, 0x08,
    0x0A, 0x10, 0x10, 0x04, 0x05, 0x07, 0x09, 0x0B, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x05, 0x08, 0x0A, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x06,
    0x09, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x06, 0x0A, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x07, 0x0B, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x07, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x08, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x09, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x09,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x09, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0A, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x0A, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x0B, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0B,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x0A, 0x00, 0x18, 0x00, 0x19,
    0x00, 0x38, 0x00, 0x78, 0x01, 0xF4, 0x03, 0xF6, 0x0F, 0xF4, 0x00, 0x0B,
    0x00, 0x39, 0x00, 0xF6, 0x01, 0xF5, 0x07, 0xF6, 0x0F, 0xF5, 0xFF, 0x88,
    0xFF, 0x89, 0xFF, 0x8A, 0xFF, 0x8B, 0x00, 0x1A, 0x00, 0xF7, 0x03, 0xF7,
    0x0F, 0xF6, 0x7F, 0xC2, 0xFF, 0x8C, 0xFF, 0x8D, 0xFF, 0x8E, 0xFF, 0x8F,
    0xFF, 0x90, 0x00, 0x1B, 0x00, 0xF8, 0x03, 0xF8, 0x0F, 0xF7, 0xFF, 0x91,
    0xFF, 0x92, 0xFF, 0x93, 0xFF, 0x94, 0xFF, 0x95, 0xFF, 0x96, 0x00, 0x3A,
    0x01, 0xF6, 0xFF, 0x97, 0xFF, 0x98, 0xFF, 0x99, 0xFF, 0x9A, 0xFF, 0x9B,
    0xFF, 0x9C, 0xFF, 0x9D, 0xFF, 0x9E, 0x00, 0x3B, 0x03, 0xF9, 0xFF, 0x9F,
    0xFF, 0xA0, 0xFF, 0xA1, 0xFF, 0xA2, 0xFF, 0xA3, 0xFF, 0xA4, 0xFF, 0xA5,
    0xFF, 0xA6, 0x00, 0x79, 0x07, 0xF7, 0xFF, 0xA7, 0xFF, 0xA8, 0xFF, 0xA9,
    0xFF, 0xAA, 0xFF, 0xAB, 0xFF, 0xAC, 0xFF, 0xAD, 0xFF, 0xAE, 0x00, 0x7A,
    0x07, 0xF8, 0xFF, 0xAF, 0xFF, 0xB0, 0xFF, 0xB1, 0xFF, 0xB2, 0xFF, 0xB3,
    0xFF, 0xB4, 0xFF, 0xB5, 0xFF, 0xB6, 0x00, 0xF9, 0xFF, 0xB7, 0xFF, 0xB8,
    0xFF, 0xB9, 0xFF, 0xBA, 0xFF, 0xBB, 0xFF, 0xBC, 0xFF, 0xBD, 0xFF, 0xBE,
    0xFF, 0xBF, 0x01, 0xF7, 0xFF, 0xC0, 0xFF, 0xC1, 0xFF, 0xC2, 0xFF, 0xC3,
    0xFF, 0xC4, 0xFF, 0xC5, 0xFF, 0xC6, 0xFF, 0xC7, 0xFF, 0xC8, 0x01, 0xF8,
    0xFF, 0xC9, 0xFF, 0xCA, 0xFF, 0xCB, 0xFF, 0xCC, 0xFF, 0xCD, 0xFF, 0xCE,
    0xFF, 0xCF, 0xFF, 0xD0, 0xFF, 0xD1, 0x01, 0xF9, 0xFF, 0xD2, 0xFF, 0xD3,
    0xFF, 0xD4, 0xFF, 0xD5, 0xFF, 0xD6, 0xFF, 0xD7, 0xFF, 0xD8, 0xFF, 0xD9,
    0xFF, 0xDA, 0x01, 0xFA, 0xFF, 0xDB, 0xFF, 0xDC, 0xFF, 0xDD, 0xFF, 0xDE,
    0xFF, 0xDF, 0xFF, 0xE0, 0xFF, 0xE1, 0xFF, 0xE2, 0xFF, 0xE3, 0x07, 0xF9,
    0xFF, 0xE4, 0xFF, 0xE5, 0xFF, 0xE6, 0xFF, 0xE7, 0xFF, 0xE8, 0xFF, 0xE9,
    0xFF, 0xEA, 0xFF, 0xEB, 0xFF, 0xEC, 0x3F, 0xE0, 0xFF, 0xED, 0xFF, 0xEE,
    0xFF, 0xEF, 0xFF, 0xF0, 0xFF, 0xF1, 0xFF, 0xF2, 0xFF, 0xF3, 0xFF, 0xF4,
    0xFF, 0xF5, 0x03, 0xFA, 0x7F, 0xC3, 0xFF, 0xF6, 0xFF, 0xF7, 0xFF, 0xF8,
    0xFF, 0xF9, 0xFF, 0xFA, 0xFF, 0xFB, 0xFF, 0xFC, 0xFF, 0xFD, 0xFF, 0xFE,
    0x02, 0x02, 0x03, 0x04, 0x05, 0x05, 0x06, 0x07, 0x09, 0x0A, 0x0C, 0x04,
    0x06, 0x08, 0x09, 0x0B, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x05, 0x08, 0x0A,
    0x0C, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x05, 0x08, 0x0A, 0x0C, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x06, 0x09, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x06, 0x0A, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x07, 0x0B, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x07,
    0x0B, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x09, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x09, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x09, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x09, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0B,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0E, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0A, 0x0F, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
};
extern u8 lbl_80431638[0x40];
extern u16 lbl_80431678[0xC];
extern u8 lbl_80431690[0xC];
extern u16 lbl_8043169C[0xC];
extern u8 lbl_804316B4[0xC];
static s32 lbl_804D6398 = 3;

void hsd_803B3408(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 unused_arg4)
{
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f5;
    f32 temp_f7;
    s32 temp_r22;
    s32 temp_r22_2;
    s32 temp_r22_5;
    s32 temp_r23;
    s32 temp_r26;
    s32 temp_r31;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r10;
    s32 var_r11;
    s32 var_r12;
    u16* var_r24;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 var_r6;
    s32 var_r6_2;
    s32 var_r7;
    s32 var_r7_2;
    s32 var_r8;
    s32 var_r9;
    u16 temp_r21;
    u16 temp_r22_4;
    u16 temp_r22_6;
    u16 temp_r30;
    u16* temp_r5;
    u8* temp_r22_3;
    u8* var_r5;

    var_r10 = 0;
    temp_r31 = ((s32) (arg3 + 0xF) / 16) << 6;
    var_r11 = 0;
    var_r12 = 0;
    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        var_r8 = var_r11;
        var_r24 = (u16*) arg0 +
                  (((arg1 / 4) * 0x10) + ((arg2 / 4) * temp_r31) + var_r10);
        var_r9 = 0;
        for (var_r27 = 0; var_r27 < 2; var_r27++) {
            for (var_r7 = 0; var_r7 < 4; var_r7++) {
                var_r6 = 0;
                for (var_ctr = 4; var_ctr != 0; var_ctr--) {
                    temp_r22 = (var_r6 * 4) & 8;
                    temp_r5 =
                        var_r24 + (((var_r6 * 2) & 2) +
                                   (temp_r22 + (((var_r7 << 5) & 0x20) +
                                                ((var_r7 & 2) * temp_r31))));
                    temp_r30 = *temp_r5;
                    temp_r22_2 = (temp_r30 >> 8U) & 0xF8;
                    temp_r23 = (temp_r30 * 8) & 0xF8;
                    temp_f3 = (f32) ((temp_r30 >> 3U) & 0xFC);
                    temp_r22_3 = HSD_804D2648_BUF +
                                 (((var_r6 & 1) + temp_r22 +
                                   (var_r8 + (((var_r7 * 4) & 4) +
                                              ((var_r7 * 0x10) & 0x20)))) *
                                  4);
                    var_r6 += 1;
                    M2C_FIELD(temp_r22_3, s32*, 0x518) =
                        (s32) ((0.5f * (f32) temp_r23) +
                               ((-0.1687f * (f32) temp_r22_2) -
                                (0.3313f * temp_f3)));
                    temp_r21 = *temp_r5;
                    M2C_FIELD(temp_r22_3, s32*, 0x618) =
                        (s32) (((0.5f * (f32) ((temp_r21 >> 8U) & 0xF8)) -
                                (0.4187f * (f32) ((temp_r21 >> 3U) & 0xFC))) -
                               (0.0813f * (f32) ((temp_r21 * 8) & 0xF8)));
                }
            }
            var_r7_2 = var_r12;
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                var_r6_2 = var_r7_2 * 8;
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    var_r26 = 0;
                    var_r5 =
                        HSD_804D2648_BUF + ((var_r9 + var_r6_2) * 4) + 0x118;
                    for (var_ctr_2 = 2; var_ctr_2 != 0; var_ctr_2--) {
                        temp_r22_4 = var_r24[((var_r26 << 5) & 0x20) +
                                             ((var_r26 & 2) * temp_r31)];
                        temp_r26 = var_r26 + 1;
                        temp_f5 = (f32) ((temp_r22_4 >> 8U) & 0xF8);
                        temp_f3_2 = 0.587f * (f32) ((temp_r22_4 >> 3U) & 0xFC);
                        temp_r22_5 = ((temp_r26 << 5) & 0x20) +
                                     ((temp_r26 & 2) * temp_r31);
                        temp_f7 = (f32) ((temp_r22_4 * 8) & 0xF8);
                        var_r26 = temp_r26 + 1;
                        M2C_FIELD(var_r5, s32*, 0) =
                            (s32) ((s32) ((0.114f * temp_f7) +
                                          ((0.299f * temp_f5) + temp_f3_2)) -
                                   0x80);
                        temp_r22_6 = var_r24[temp_r22_5];
                        M2C_FIELD(var_r5, s32*, 0x100) =
                            (s32) ((s32) ((0.114f *
                                           (f32) ((temp_r22_6 * 8) & 0xF8)) +
                                          ((0.299f *
                                            (f32) ((temp_r22_6 >> 8U) &
                                                   0xF8)) +
                                           (0.587f *
                                            (f32) ((temp_r22_6 >> 3U) &
                                                   0xFC)))) -
                                   0x80);
                        var_r5 += 0x200;
                    }
                    var_r24 += 1;
                    var_r6_2 += 1;
                }
                var_r7_2 += 1;
            }
            var_r8 += 2;
            var_r9 += 4;
        }
        var_r10 += temp_r31;
        var_r11 += 0x10;
        var_r12 += 4;
    }
}

static void fn_803B376C(u8* arg0)
{
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f11_3;
    f32 temp_f11_4;
    f32 temp_f11_5;
    f32 temp_f11_6;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f27_3;
    f32 temp_f27_4;
    f32 temp_f27_5;
    f32 temp_f27_6;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f28_3;
    f32 temp_f28_4;
    f32 temp_f28_5;
    f32 temp_f28_6;
    f32 temp_f28_7;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f29_3;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 temp_f8_4;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r12;
    s32 temp_r12_2;
    s32 temp_r29;
    s32 temp_r29_2;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    s32 temp_r31_2;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32* var_r3;
    s32* var_r4;
    s32* var_r4_2;

    var_r4 = (s32*) arg0;
    for (var_ctr = 8; var_ctr != 0; var_ctr--) {
        temp_r29 = var_r4[0];
        temp_r30 = var_r4[7];
        temp_r31 = var_r4[1];
        temp_r12 = var_r4[6];
        temp_r11 = var_r4[2];
        temp_r10 = var_r4[5];
        temp_r9 = var_r4[3];
        temp_r7 = var_r4[4];
        temp_f11 = (f32) (temp_r29 + temp_r30);
        temp_f27 = (f32) (temp_r31 + temp_r12);
        temp_f28 = (f32) (temp_r11 + temp_r10);
        temp_f4 = (f32) (temp_r9 + temp_r7);
        temp_f30 = temp_f27 + temp_f28;
        temp_f6 = temp_f11 + temp_f4;
        temp_f26 = temp_f11 - temp_f4;
        temp_f27_2 = temp_f27 - temp_f28;
        temp_f27_3 = (f32) (temp_r9 - temp_r7);
        temp_f8 = (f32) (temp_r11 - temp_r10);
        temp_f11_2 = (f32) (temp_r31 - temp_r12);
        var_r4[0] = (s32) (0.707107f * (f64) (temp_f6 + temp_f30));
        temp_f28_2 = (f32) (temp_r29 - temp_r30);
        var_r4[4] = (s32) (0.707107f * (f64) (temp_f6 - temp_f30));
        var_r4[6] = (s32) ((-0.92388f * (f64) temp_f27_2) +
                           (0.382683f * (f64) temp_f26));
        var_r4[2] = (s32) ((0.382683f * (f64) temp_f27_2) +
                           (0.92388f * (f64) temp_f26));
        temp_f11_3 = (f32) (0.707107f * (f64) (temp_f8 + temp_f11_2));
        temp_f8_2 = (f32) (0.707107f * (f64) (temp_f8 - temp_f11_2));
        temp_f30_2 = temp_f11_3 + temp_f28_2;
        temp_f26_2 = -temp_f27_3 + temp_f8_2;
        temp_f28_3 = -temp_f11_3 + temp_f28_2;
        temp_f27_4 = temp_f27_3 + temp_f8_2;
        var_r4[7] = (s32) ((0.980785f * (f64) temp_f26_2) +
                           (0.19509f * (f64) temp_f30_2));
        var_r4[5] = (s32) ((0.83147f * (f64) temp_f27_4) +
                           (0.55557f * (f64) temp_f28_3));
        var_r4[3] = (s32) ((-0.55557f * (f64) temp_f27_4) +
                           (0.83147f * (f64) temp_f28_3));
        var_r4[1] = (s32) ((-0.19509f * (f64) temp_f26_2) +
                           (0.980785f * (f64) temp_f30_2));
        var_r4 += 8;
    }
    var_r4_2 = (s32*) arg0;
    for (var_ctr_2 = 8; var_ctr_2 != 0; var_ctr_2--) {
        temp_r31_2 = var_r4_2[0];
        temp_r30_2 = var_r4_2[56];
        temp_r29_2 = var_r4_2[8];
        temp_r12_2 = var_r4_2[48];
        temp_r11_2 = var_r4_2[16];
        temp_r10_2 = var_r4_2[40];
        temp_r9_2 = var_r4_2[24];
        temp_r7_2 = var_r4_2[32];
        temp_f11_4 = (f32) (temp_r31_2 + temp_r30_2);
        temp_f30_3 = (f32) (temp_r29_2 + temp_r12_2);
        temp_f28_4 = (f32) (temp_r11_2 + temp_r10_2);
        temp_f4_2 = (f32) (temp_r9_2 + temp_r7_2);
        temp_f29 = temp_f30_3 + temp_f28_4;
        temp_f6_2 = temp_f11_4 + temp_f4_2;
        temp_f27_5 = temp_f11_4 - temp_f4_2;
        temp_f28_5 = temp_f30_3 - temp_f28_4;
        temp_f28_6 = (f32) (temp_r9_2 - temp_r7_2);
        temp_f8_3 = (f32) (temp_r11_2 - temp_r10_2);
        temp_f11_5 = (f32) (temp_r29_2 - temp_r12_2);
        var_r4_2[0] = (s32) (0.707107f * (f64) (temp_f6_2 + temp_f29));
        temp_f29_2 = (f32) (temp_r31_2 - temp_r30_2);
        var_r4_2[32] = (s32) (0.707107f * (f64) (temp_f6_2 - temp_f29));
        var_r4_2[48] = (s32) ((-0.92388f * (f64) temp_f28_5) +
                              (0.382683f * (f64) temp_f27_5));
        var_r4_2[16] = (s32) ((0.382683f * (f64) temp_f28_5) +
                              (0.92388f * (f64) temp_f27_5));
        temp_f11_6 = (f32) (0.707107f * (f64) (temp_f8_3 + temp_f11_5));
        temp_f8_4 = (f32) (0.707107f * (f64) (temp_f8_3 - temp_f11_5));
        temp_f30_4 = temp_f11_6 + temp_f29_2;
        temp_f27_6 = -temp_f28_6 + temp_f8_4;
        temp_f29_3 = -temp_f11_6 + temp_f29_2;
        temp_f28_7 = temp_f28_6 + temp_f8_4;
        var_r4_2[56] = (s32) ((0.980785f * (f64) temp_f27_6) +
                              (0.19509f * (f64) temp_f30_4));
        var_r4_2[40] = (s32) ((0.83147f * (f64) temp_f28_7) +
                              (0.55557f * (f64) temp_f29_3));
        var_r4_2[24] = (s32) ((-0.55557f * (f64) temp_f28_7) +
                              (0.83147f * (f64) temp_f29_3));
        var_r4_2[8] = (s32) ((-0.19509f * (f64) temp_f27_6) +
                             (0.980785f * (f64) temp_f30_4));
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

void hsd_803B3CD8(s32 arg0)
{
    __jmp_buf* jmp_buf;
    s32 var_r31;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r4_12;
    s32 temp_r4_17;
    s32 temp_r4_18;
    s32 temp_r4_19;
    s32 temp_r4_20;
    s32 temp_r4_21;
    s32 temp_r4_22;
    s32 temp_r4_23;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 temp_r4_4;
    s32 temp_r4_5;
    s32 temp_r4_6;
    s32 temp_r4_7;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r5_5;
    s32 temp_r5_6;
    s32 temp_r5_7;
    s32 temp_r5_8;
    s32 temp_r5_9;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_r22;
    s32 var_r23;
    s32 var_r24;
    s32 var_r25;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r28_3;
    s32 var_r28_4;
    s32 var_r28_5;
    s32 var_r28_6;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r5;
    u16 temp_r28;
    u16 temp_r29;
    u16 temp_r31;
    u16 temp_r31_2;
    u16* var_r27;
    u16* var_r6;
    u8* temp_r4_10;
    u8* temp_r4_11;
    u8* temp_r4_13;
    u8* temp_r4_14;
    u8* temp_r4_15;
    u8* temp_r4_16;
    u8* temp_r4_24;
    u8* temp_r4_25;
    u8* temp_r4_26;
    u8* temp_r4_27;
    u8* temp_r4_28;
    u8* temp_r4_29;
    u8* temp_r4_8;
    u8* temp_r4_9;
    u8* var_r25_2;
    u8* var_r26;
    u8* var_r7;
    u8* temp_r8;

    jmp_buf = &hsd_804D2648;
    if (arg0 == 0) {
        var_r6 = lbl_80431678;
    } else {
        var_r6 = lbl_8043169C;
    }
    if (arg0 == 0) {
        var_r7 = lbl_80431690;
    } else {
        var_r7 = lbl_804316B4;
    }
    if (arg0 == 0) {
        var_r27 = (u16*) (lbl_80430C40 + 0x80);
    } else {
        var_r27 = (u16*) (lbl_80430C40 + 0x268);
    }
    if (arg0 == 0) {
        var_r26 = lbl_80430C40 + 0x1C4;
    } else {
        var_r26 = lbl_80430C40 + 0x3AC;
    }
    temp_r8 = (u8*) jmp_buf + (arg0 * 4);
    var_r25 = M2C_FIELD((u8*) jmp_buf, s32*, 0x718) -
              M2C_FIELD(temp_r8, s32*, 0x818);
    var_ctr = 4;
    temp_r0 = var_r25 >> 0x1F;
    var_r24 = 0;
    temp_r5 = (temp_r0 ^ var_r25) - temp_r0;
    var_r4 = 0x1F;
loop_13:
    if (temp_r5 & (1 << var_r4)) {
        var_r31 = var_r4 + 1;
    } else {
        temp_r4 = var_r4 - 1;
        if (temp_r5 & (1 << temp_r4)) {
            var_r31 = temp_r4 + 1;
        } else {
            temp_r4_2 = temp_r4 - 1;
            if (temp_r5 & (1 << temp_r4_2)) {
                var_r31 = temp_r4_2 + 1;
            } else {
                temp_r4_3 = temp_r4_2 - 1;
                if (temp_r5 & (1 << temp_r4_3)) {
                    var_r31 = temp_r4_3 + 1;
                } else {
                    temp_r4_4 = temp_r4_3 - 1;
                    if (temp_r5 & (1 << temp_r4_4)) {
                        var_r31 = temp_r4_4 + 1;
                    } else {
                        temp_r4_5 = temp_r4_4 - 1;
                        if (temp_r5 & (1 << temp_r4_5)) {
                            var_r31 = temp_r4_5 + 1;
                        } else {
                            temp_r4_6 = temp_r4_5 - 1;
                            if (temp_r5 & (1 << temp_r4_6)) {
                                var_r31 = temp_r4_6 + 1;
                            } else {
                                temp_r4_7 = temp_r4_6 - 1;
                                if (temp_r5 & (1 << temp_r4_7)) {
                                    var_r31 = temp_r4_7 + 1;
                                } else {
                                    var_r4 = temp_r4_7 - 1;
                                    var_ctr -= 1;
                                    if (var_ctr == 0) {
                                        var_r31 = 0;
                                    } else {
                                        goto loop_13;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    M2C_FIELD(temp_r8, s32*, 0x818) =
        (s32) M2C_FIELD((u8*) jmp_buf, s32*, 0x718);
    temp_r28 = var_r6[var_r31];
    var_r29 = var_r7[var_r31] - 1;
loop_44:
    if (var_r29 >= 0) {
        hsd_804D79AC += 1;
        hsd_804D79B0 *= 2;
        if (temp_r28 & (1 << var_r29)) {
            hsd_804D79B0 |= 1;
        }
        if ((s32) hsd_804D79AC == 8) {
            temp_r4_8 = hsd_804D79A0;
            if (temp_r4_8 < &hsd_804D79A4[hsd_804D79A8]) {
                hsd_804D79A0 = temp_r4_8 + 1;
                *temp_r4_8 = hsd_804D79B0;
            } else {
                longjmp(jmp_buf, 1);
            }
            if ((u8) hsd_804D79B0 == 0xFF) {
                temp_r4_9 = hsd_804D79A0;
                if (temp_r4_9 < &hsd_804D79A4[hsd_804D79A8]) {
                    hsd_804D79A0 = temp_r4_9 + 1;
                    *temp_r4_9 = 0;
                } else {
                    longjmp(jmp_buf, 1);
                }
            }
            hsd_804D79AC = 0;
            hsd_804D79B0 = 0;
        }
        var_r29 -= 1;
        goto loop_44;
    }
    if (var_r31 != 0) {
        if (var_r25 < 0) {
            var_r25 -= 1;
        }
        var_r28 = var_r31 - 1;
    loop_61:
        if (var_r28 >= 0) {
            hsd_804D79AC += 1;
            hsd_804D79B0 *= 2;
            if (var_r25 & (1 << var_r28)) {
                hsd_804D79B0 |= 1;
            }
            if ((s32) hsd_804D79AC == 8) {
                temp_r4_10 = hsd_804D79A0;
                if (temp_r4_10 < &hsd_804D79A4[hsd_804D79A8]) {
                    hsd_804D79A0 = temp_r4_10 + 1;
                    *temp_r4_10 = hsd_804D79B0;
                } else {
                    longjmp(jmp_buf, 1);
                }
                if ((u8) hsd_804D79B0 == 0xFF) {
                    temp_r4_11 = hsd_804D79A0;
                    if (temp_r4_11 < &hsd_804D79A4[hsd_804D79A8]) {
                        hsd_804D79A0 = temp_r4_11 + 1;
                        *temp_r4_11 = 0;
                    } else {
                        longjmp(jmp_buf, 1);
                    }
                }
                hsd_804D79AC = 0;
                hsd_804D79B0 = 0;
            }
            var_r28 -= 1;
            goto loop_61;
        }
    }
    var_r25_2 = &lbl_80431638[1];
    var_r23 = 1;
    do {
        temp_r0_2 = M2C_FIELD(((u8*) jmp_buf + (*var_r25_2 * 4)), s32*, 0x718);
        var_r22 = temp_r0_2;
        if (temp_r0_2 != 0) {
            var_ctr_2 = 4;
            temp_r4_12 = var_r24 + 1;
            var_r5 = 0x1F;
        loop_65:
            if (temp_r4_12 & (1 << var_r5)) {
                var_r28_2 = var_r5 + 1;
            } else {
                temp_r5_2 = var_r5 - 1;
                if (temp_r4_12 & (1 << temp_r5_2)) {
                    var_r28_2 = temp_r5_2 + 1;
                } else {
                    temp_r5_3 = temp_r5_2 - 1;
                    if (temp_r4_12 & (1 << temp_r5_3)) {
                        var_r28_2 = temp_r5_3 + 1;
                    } else {
                        temp_r5_4 = temp_r5_3 - 1;
                        if (temp_r4_12 & (1 << temp_r5_4)) {
                            var_r28_2 = temp_r5_4 + 1;
                        } else {
                            temp_r5_5 = temp_r5_4 - 1;
                            if (temp_r4_12 & (1 << temp_r5_5)) {
                                var_r28_2 = temp_r5_5 + 1;
                            } else {
                                temp_r5_6 = temp_r5_5 - 1;
                                if (temp_r4_12 & (1 << temp_r5_6)) {
                                    var_r28_2 = temp_r5_6 + 1;
                                } else {
                                    temp_r5_7 = temp_r5_6 - 1;
                                    if (temp_r4_12 & (1 << temp_r5_7)) {
                                        var_r28_2 = temp_r5_7 + 1;
                                    } else {
                                        temp_r5_8 = temp_r5_7 - 1;
                                        if (temp_r4_12 & (1 << temp_r5_8)) {
                                            var_r28_2 = temp_r5_8 + 1;
                                        } else {
                                            var_r5 = temp_r5_8 - 1;
                                            var_ctr_2 -= 1;
                                            if (var_ctr_2 == 0) {
                                                var_r28_2 = 0;
                                            } else {
                                                goto loop_65;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            temp_r31 = *(var_r27 + (var_r28_2 * 2));
            var_r29_2 = *(var_r26 + var_r28_2) - 1;
        loop_96:
            if (var_r29_2 >= 0) {
                hsd_804D79AC += 1;
                hsd_804D79B0 *= 2;
                if (temp_r31 & (1 << var_r29_2)) {
                    hsd_804D79B0 |= 1;
                }
                if ((s32) hsd_804D79AC == 8) {
                    temp_r4_13 = hsd_804D79A0;
                    if (temp_r4_13 < &hsd_804D79A4[hsd_804D79A8]) {
                        hsd_804D79A0 = temp_r4_13 + 1;
                        *temp_r4_13 = hsd_804D79B0;
                    } else {
                        longjmp(jmp_buf, 1);
                    }
                    if ((u8) hsd_804D79B0 == 0xFF) {
                        temp_r4_14 = hsd_804D79A0;
                        if (temp_r4_14 < &hsd_804D79A4[hsd_804D79A8]) {
                            hsd_804D79A0 = temp_r4_14 + 1;
                            *temp_r4_14 = 0;
                        } else {
                            longjmp(jmp_buf, 1);
                        }
                    }
                    hsd_804D79AC = 0;
                    hsd_804D79B0 = 0;
                }
                var_r29_2 -= 1;
                goto loop_96;
            }
            var_r28_3 = var_r28_2 - 1;
        loop_110:
            if (var_r28_3 >= 0) {
                hsd_804D79AC += 1;
                hsd_804D79B0 *= 2;
                if ((var_r24 + 1) & (1 << var_r28_3)) {
                    hsd_804D79B0 |= 1;
                }
                if ((s32) hsd_804D79AC == 8) {
                    temp_r4_15 = hsd_804D79A0;
                    if (temp_r4_15 < &hsd_804D79A4[hsd_804D79A8]) {
                        hsd_804D79A0 = temp_r4_15 + 1;
                        *temp_r4_15 = hsd_804D79B0;
                    } else {
                        longjmp(jmp_buf, 1);
                    }
                    if ((u8) hsd_804D79B0 == 0xFF) {
                        temp_r4_16 = hsd_804D79A0;
                        if (temp_r4_16 < &hsd_804D79A4[hsd_804D79A8]) {
                            hsd_804D79A0 = temp_r4_16 + 1;
                            *temp_r4_16 = 0;
                        } else {
                            longjmp(jmp_buf, 1);
                        }
                    }
                    hsd_804D79AC = 0;
                    hsd_804D79B0 = 0;
                }
                var_r28_3 -= 1;
                goto loop_110;
            }
            temp_r3 = var_r22 >> 0x1F;
            var_ctr_3 = 4;
            temp_r5_9 = (temp_r3 ^ var_r22) - temp_r3;
            var_r4_2 = 0x1F;
        loop_112:
            if (temp_r5_9 & (1 << var_r4_2)) {
                var_r28_4 = var_r4_2 + 1;
            } else {
                temp_r4_17 = var_r4_2 - 1;
                if (temp_r5_9 & (1 << temp_r4_17)) {
                    var_r28_4 = temp_r4_17 + 1;
                } else {
                    temp_r4_18 = temp_r4_17 - 1;
                    if (temp_r5_9 & (1 << temp_r4_18)) {
                        var_r28_4 = temp_r4_18 + 1;
                    } else {
                        temp_r4_19 = temp_r4_18 - 1;
                        if (temp_r5_9 & (1 << temp_r4_19)) {
                            var_r28_4 = temp_r4_19 + 1;
                        } else {
                            temp_r4_20 = temp_r4_19 - 1;
                            if (temp_r5_9 & (1 << temp_r4_20)) {
                                var_r28_4 = temp_r4_20 + 1;
                            } else {
                                temp_r4_21 = temp_r4_20 - 1;
                                if (temp_r5_9 & (1 << temp_r4_21)) {
                                    var_r28_4 = temp_r4_21 + 1;
                                } else {
                                    temp_r4_22 = temp_r4_21 - 1;
                                    if (temp_r5_9 & (1 << temp_r4_22)) {
                                        var_r28_4 = temp_r4_22 + 1;
                                    } else {
                                        temp_r4_23 = temp_r4_22 - 1;
                                        if (temp_r5_9 & (1 << temp_r4_23)) {
                                            var_r28_4 = temp_r4_23 + 1;
                                        } else {
                                            var_r4_2 = temp_r4_23 - 1;
                                            var_ctr_3 -= 1;
                                            if (var_ctr_3 == 0) {
                                                var_r28_4 = 0;
                                            } else {
                                                goto loop_112;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            temp_r31_2 = *(var_r27 + (var_r28_4 * 2));
            var_r29_3 = *(var_r26 + var_r28_4) - 1;
        loop_143:
            if (var_r29_3 >= 0) {
                hsd_804D79AC += 1;
                hsd_804D79B0 *= 2;
                if (temp_r31_2 & (1 << var_r29_3)) {
                    hsd_804D79B0 |= 1;
                }
                if ((s32) hsd_804D79AC == 8) {
                    temp_r4_24 = hsd_804D79A0;
                    if (temp_r4_24 < &hsd_804D79A4[hsd_804D79A8]) {
                        hsd_804D79A0 = temp_r4_24 + 1;
                        *temp_r4_24 = hsd_804D79B0;
                    } else {
                        longjmp(jmp_buf, 1);
                    }
                    if ((u8) hsd_804D79B0 == 0xFF) {
                        temp_r4_25 = hsd_804D79A0;
                        if (temp_r4_25 < &hsd_804D79A4[hsd_804D79A8]) {
                            hsd_804D79A0 = temp_r4_25 + 1;
                            *temp_r4_25 = 0;
                        } else {
                            longjmp(jmp_buf, 1);
                        }
                    }
                    hsd_804D79AC = 0;
                    hsd_804D79B0 = 0;
                }
                var_r29_3 -= 1;
                goto loop_143;
            }
            if (var_r22 < 0) {
                var_r22 -= 1;
            }
            var_r28_5 = var_r28_4 - 1;
        loop_159:
            if (var_r28_5 >= 0) {
                hsd_804D79AC += 1;
                hsd_804D79B0 *= 2;
                if (var_r22 & (1 << var_r28_5)) {
                    hsd_804D79B0 |= 1;
                }
                if ((s32) hsd_804D79AC == 8) {
                    temp_r4_26 = hsd_804D79A0;
                    if (temp_r4_26 < &hsd_804D79A4[hsd_804D79A8]) {
                        hsd_804D79A0 = temp_r4_26 + 1;
                        *temp_r4_26 = hsd_804D79B0;
                    } else {
                        longjmp(jmp_buf, 1);
                    }
                    if ((u8) hsd_804D79B0 == 0xFF) {
                        temp_r4_27 = hsd_804D79A0;
                        if (temp_r4_27 < &hsd_804D79A4[hsd_804D79A8]) {
                            hsd_804D79A0 = temp_r4_27 + 1;
                            *temp_r4_27 = 0;
                        } else {
                            longjmp(jmp_buf, 1);
                        }
                    }
                    hsd_804D79AC = 0;
                    hsd_804D79B0 = 0;
                }
                var_r28_5 -= 1;
                goto loop_159;
            }
            var_r24 = 0;
        } else {
            var_r24 += 1;
        }
        var_r23 += 1;
        var_r25_2 += 1;
    } while (var_r23 < 0x40);
    if (var_r24 != 0) {
        temp_r29 = *var_r27;
        var_r28_6 = *var_r26 - 1;
    loop_177:
        if (var_r28_6 >= 0) {
            hsd_804D79AC += 1;
            hsd_804D79B0 *= 2;
            if (temp_r29 & (1 << var_r28_6)) {
                hsd_804D79B0 |= 1;
            }
            if ((s32) hsd_804D79AC == 8) {
                temp_r4_28 = hsd_804D79A0;
                if (temp_r4_28 < &hsd_804D79A4[hsd_804D79A8]) {
                    hsd_804D79A0 = temp_r4_28 + 1;
                    *temp_r4_28 = hsd_804D79B0;
                } else {
                    longjmp(jmp_buf, 1);
                }
                if ((u8) hsd_804D79B0 == 0xFF) {
                    temp_r4_29 = hsd_804D79A0;
                    if (temp_r4_29 < &hsd_804D79A4[hsd_804D79A8]) {
                        hsd_804D79A0 = temp_r4_29 + 1;
                        *temp_r4_29 = 0;
                    } else {
                        longjmp(jmp_buf, 1);
                    }
                }
                hsd_804D79AC = 0;
                hsd_804D79B0 = 0;
            }
            var_r28_6 -= 1;
            goto loop_177;
        }
    }
}

static const u8 lbl_804DEB88[8] = "JFIF";

void hsd_803B46D4(void)
{
    __jmp_buf* jmp_buf;
    u8 spC;
    s32 sp8;
    u8* temp_r4;
    u8* temp_r4_10;
    u8* temp_r4_11;
    u8* temp_r4_12;
    u8* temp_r4_13;
    u8* temp_r4_2;
    u8* temp_r4_3;
    u8* temp_r4_4;
    u8* temp_r4_5;
    u8* temp_r4_6;
    u8* temp_r4_7;
    u8* temp_r4_8;
    u8* temp_r4_9;

    sp8 = *(s32*) lbl_804DEB88;
    spC = lbl_804DEB88[4];
    jmp_buf = &hsd_804D2648;
    temp_r4 = hsd_804D79A0;
    if (temp_r4 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4 + 1;
        *temp_r4 = 0xFF;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_2 = hsd_804D79A0;
    if (temp_r4_2 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_2 + 1;
        *temp_r4_2 = 0xE0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_3 = hsd_804D79A0;
    if (temp_r4_3 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_3 + 1;
        *temp_r4_3 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_4 = hsd_804D79A0;
    if (temp_r4_4 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_4 + 1;
        *temp_r4_4 = 0x10;
    } else {
        longjmp(jmp_buf, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8 - 5]) {
        memcpy(hsd_804D79A0, &sp8, 5U);
        hsd_804D79A0 += 5;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_5 = hsd_804D79A0;
    if (temp_r4_5 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_5 + 1;
        *temp_r4_5 = 1;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_6 = hsd_804D79A0;
    if (temp_r4_6 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_6 + 1;
        *temp_r4_6 = 2;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_7 = hsd_804D79A0;
    if (temp_r4_7 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_7 + 1;
        *temp_r4_7 = 1;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_8 = hsd_804D79A0;
    if (temp_r4_8 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_8 + 1;
        *temp_r4_8 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_9 = hsd_804D79A0;
    if (temp_r4_9 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_9 + 1;
        *temp_r4_9 = 0x48;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_10 = hsd_804D79A0;
    if (temp_r4_10 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_10 + 1;
        *temp_r4_10 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_11 = hsd_804D79A0;
    if (temp_r4_11 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_11 + 1;
        *temp_r4_11 = 0x48;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_12 = hsd_804D79A0;
    if (temp_r4_12 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_12 + 1;
        *temp_r4_12 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_13 = hsd_804D79A0;
    if (temp_r4_13 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_13 + 1;
        *temp_r4_13 = 0;
        return;
    }
    longjmp(jmp_buf, 1);
}

void hsd_803B4A2C(void)
{
    __jmp_buf* jmp_buf;
    s32 var_r28_2;
    u8* var_r28;
    s32 var_r27;
    u8* var_r30;
    s32 var_r5;
    u8 var_r3;
    u8* temp_r4;
    u8* temp_r4_10;
    u8* temp_r4_11;
    u8* temp_r4_12;
    u8* temp_r4_2;
    u8* temp_r4_3;
    u8* temp_r4_4;
    u8* temp_r4_5;
    u8* temp_r4_6;
    u8* temp_r4_7;
    u8* temp_r4_8;
    u8* temp_r4_9;

    jmp_buf = &hsd_804D2648;
    temp_r4 = hsd_804D79A0;
    if (temp_r4 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4 + 1;
        *temp_r4 = 0xFF;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_2 = hsd_804D79A0;
    if (temp_r4_2 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_2 + 1;
        *temp_r4_2 = 0xDB;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_3 = hsd_804D79A0;
    if (temp_r4_3 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_3 + 1;
        *temp_r4_3 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_4 = hsd_804D79A0;
    if (temp_r4_4 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_4 + 1;
        *temp_r4_4 = 0x43;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_5 = hsd_804D79A0;
    if (temp_r4_5 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_5 + 1;
        *temp_r4_5 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    var_r30 = lbl_80431638;
    var_r28 = lbl_80431638;
    var_r27 = 0;
    do {
        var_r5 = (s32) * (lbl_80430C40 + *var_r28) / (s32) lbl_804D6398;
        var_r3 = (u8) var_r5;
        temp_r4_6 = hsd_804D79A0;
        if (temp_r4_6 < &hsd_804D79A4[hsd_804D79A8]) {
            hsd_804D79A0 = temp_r4_6 + 1;
            *temp_r4_6 = var_r3;
        } else {
            longjmp(jmp_buf, 1);
        }
        var_r27 += 1;
        var_r28 += 1;
    } while (var_r27 < 0x40);
    temp_r4_7 = hsd_804D79A0;
    if (temp_r4_7 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_7 + 1;
        *temp_r4_7 = 0xFF;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_8 = hsd_804D79A0;
    if (temp_r4_8 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_8 + 1;
        *temp_r4_8 = 0xDB;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_9 = hsd_804D79A0;
    if (temp_r4_9 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_9 + 1;
        *temp_r4_9 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_10 = hsd_804D79A0;
    if (temp_r4_10 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_10 + 1;
        *temp_r4_10 = 0x43;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_11 = hsd_804D79A0;
    if (temp_r4_11 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_11 + 1;
        *temp_r4_11 = 1;
    } else {
        longjmp(jmp_buf, 1);
    }
    var_r28_2 = 0;
    do {
        var_r5 = (s32) * (lbl_80430C80 + *var_r30) / (s32) lbl_804D6398;
        var_r3 = (u8) var_r5;
        temp_r4_12 = hsd_804D79A0;
        if (temp_r4_12 < &hsd_804D79A4[hsd_804D79A8]) {
            hsd_804D79A0 = temp_r4_12 + 1;
            *temp_r4_12 = var_r3;
        } else {
            longjmp(jmp_buf, 1);
        }
        var_r28_2 += 1;
        var_r30 += 1;
    } while (var_r28_2 < 0x40);
}

void hsd_803B4D64(u32 arg0, u32 arg1)
{
    __jmp_buf* jmp_buf = &hsd_804D2648;
    u8* temp_r4;
    u8* temp_r4_10;
    u8* temp_r4_11;
    u8* temp_r4_12;
    u8* temp_r4_13;
    u8* temp_r4_14;
    u8* temp_r4_15;
    u8* temp_r4_16;
    u8* temp_r4_17;
    u8* temp_r4_18;
    u8* temp_r4_2;
    u8* temp_r4_3;
    u8* temp_r4_4;
    u8* temp_r4_5;
    u8* temp_r4_6;
    u8* temp_r4_7;
    u8* temp_r4_8;
    u8* temp_r4_9;
    u8* temp_r6;

    temp_r6 = hsd_804D79A0;
    if (temp_r6 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r6 + 1;
        *temp_r6 = 0xFF;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4 = hsd_804D79A0;
    if (temp_r4 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4 + 1;
        *temp_r4 = 0xC0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_2 = hsd_804D79A0;
    if (temp_r4_2 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_2 + 1;
        *temp_r4_2 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_3 = hsd_804D79A0;
    if (temp_r4_3 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_3 + 1;
        *temp_r4_3 = 0x11;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_4 = hsd_804D79A0;
    if (temp_r4_4 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_4 + 1;
        *temp_r4_4 = 8;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_5 = hsd_804D79A0;
    if (temp_r4_5 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_5 + 1;
        *temp_r4_5 = (u8) (arg1 >> 8U);
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_6 = hsd_804D79A0;
    if (temp_r4_6 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_6 + 1;
        *temp_r4_6 = arg1;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_7 = hsd_804D79A0;
    if (temp_r4_7 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_7 + 1;
        *temp_r4_7 = (u8) (arg0 >> 8U);
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_8 = hsd_804D79A0;
    if (temp_r4_8 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_8 + 1;
        *temp_r4_8 = arg0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_9 = hsd_804D79A0;
    if (temp_r4_9 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_9 + 1;
        *temp_r4_9 = 3;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_10 = hsd_804D79A0;
    if (temp_r4_10 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_10 + 1;
        *temp_r4_10 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_11 = hsd_804D79A0;
    if (temp_r4_11 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_11 + 1;
        *temp_r4_11 = 0x22;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_12 = hsd_804D79A0;
    if (temp_r4_12 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_12 + 1;
        *temp_r4_12 = 0;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_13 = hsd_804D79A0;
    if (temp_r4_13 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_13 + 1;
        *temp_r4_13 = 1;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_14 = hsd_804D79A0;
    if (temp_r4_14 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_14 + 1;
        *temp_r4_14 = 0x11;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_15 = hsd_804D79A0;
    if (temp_r4_15 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_15 + 1;
        *temp_r4_15 = 1;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_16 = hsd_804D79A0;
    if (temp_r4_16 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_16 + 1;
        *temp_r4_16 = 2;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_17 = hsd_804D79A0;
    if (temp_r4_17 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_17 + 1;
        *temp_r4_17 = 0x11;
    } else {
        longjmp(jmp_buf, 1);
    }
    temp_r4_18 = hsd_804D79A0;
    if (temp_r4_18 < &hsd_804D79A4[hsd_804D79A8]) {
        hsd_804D79A0 = temp_r4_18 + 1;
        *temp_r4_18 = 1;
        return;
    }
    longjmp(jmp_buf, 1);
}

s32 hsd_803B51C8(s32 arg0, s32 arg1, s32 arg2, char* arg3, s32 arg4)
{
    u8 sp1EC[0x15];
    u8 sp1D0[0x1C];
    u8 sp1B4[0x1C];
    u8 sp100[0xB2];
    u8 sp4C[0xB2];
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r6_4;
    s32 temp_r6_5;
    s32 temp_r7_2;
    s32 temp_r7_4;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r24;
    s32 var_r25;
    s32 var_r26;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    u16 temp_r0;
    u32 temp_r23;
    u8 temp_r6_3;
    u8 temp_r7;
    u8 temp_r7_3;
    u8* temp_r3;
    u8* temp_r3_10;
    u8* temp_r3_11;
    u8* temp_r3_12;
    u8* temp_r3_13;
    u8* temp_r3_14;
    u8* temp_r3_15;
    u8* temp_r3_16;
    u8* temp_r3_17;
    u8* temp_r3_18;
    u8* temp_r3_19;
    u8* temp_r3_20;
    u8* temp_r3_21;
    u8* temp_r3_2;
    u8* temp_r3_5;
    u8* temp_r3_6;
    u8* temp_r3_7;
    u8* temp_r3_8;
    u8* temp_r3_9;
    u8* temp_r5;
    u8* temp_r6;
    u8* temp_r6_2;
    u8* quant_table;
    u8* base;
    u8* var_r23;
    u8* var_r26_2;
    u8* var_r4;
    u8* var_r4_2;
    u8* var_r4_3;
    u8* var_r4_4;
    u8* var_r4_5;
    u8* var_r5;
    u8* var_r5_2;
    u8* var_r5_3;
    u8* var_r5_4;

    quant_table = lbl_80430C40;
    base = HSD_804D2648_BUF;
    hsd_804D79A8 = arg4;
    hsd_804D79AC = 0;
    hsd_804D79A0 = (u8*) arg3;
    hsd_804D79A4 = (u8*) arg3;
    M2C_FIELD(base, s32*, 0x820) = 0;
    M2C_FIELD(base, s32*, 0x81C) = 0;
    M2C_FIELD(base, s32*, 0x818) = 0;
    if (__setjmp((__jmp_buf*) base) != 0) {
        return 0;
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3 + 1;
        *temp_r3 = 0xFF;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_2 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_2 + 1;
        *temp_r3_2 = 0xD8;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    hsd_803B46D4();
    M2C_FIELD(sp1EC, s32*, 0) = M2C_FIELD(lbl_803B9670, s32*, 0);
    M2C_FIELD(sp1EC, s32*, 4) = M2C_FIELD(lbl_803B9670, s32*, 4);
    M2C_FIELD(sp1EC, s32*, 8) = M2C_FIELD(lbl_803B9670, s32*, 8);
    M2C_FIELD(sp1EC, s32*, 0xC) = M2C_FIELD(lbl_803B9670, s32*, 0xC);
    M2C_FIELD(sp1EC, s32*, 0x10) = M2C_FIELD(lbl_803B9670, s32*, 0x10);
    M2C_FIELD(sp1EC, u8*, 0x14) = M2C_FIELD(lbl_803B9670, u8*, 0x14);
    temp_r23 = strlen((char*) sp1EC) + 1;
    hsd_803B3344(0xFFU);
    hsd_803B3344(0xFEU);
    temp_r0 = temp_r23 + 2;
    hsd_803B3344((u8) (temp_r0 >> 8U));
    hsd_803B3344((u8) temp_r0);
    hsd_803B3398(sp1EC, temp_r23);
    hsd_803B4A2C();
    M2C_FIELD(sp1D0, s32*, 0) = M2C_FIELD(lbl_803B9670, s32*, 0x18);
    M2C_FIELD(sp1D0, s32*, 4) = M2C_FIELD(lbl_803B9670, s32*, 0x1C);
    M2C_FIELD(sp1D0, s32*, 8) = M2C_FIELD(lbl_803B9670, s32*, 0x20);
    M2C_FIELD(sp1D0, s32*, 0xC) = M2C_FIELD(lbl_803B9670, s32*, 0x24);
    M2C_FIELD(sp1D0, s32*, 0x10) = M2C_FIELD(lbl_803B9670, s32*, 0x28);
    M2C_FIELD(sp1D0, s32*, 0x14) = M2C_FIELD(lbl_803B9670, s32*, 0x2C);
    M2C_FIELD(sp1D0, s32*, 0x18) = M2C_FIELD(lbl_803B9670, s32*, 0x30);
    hsd_803B3344(0xFFU);
    hsd_803B3344(0xC4U);
    hsd_803B3344(0U);
    hsd_803B3344(0x1FU);
    hsd_803B3344(0U);
    hsd_803B3398(sp1D0, 0x1CU);
    M2C_FIELD(sp1B4, s32*, 0) = M2C_FIELD(lbl_803B9670, s32*, 0x34);
    M2C_FIELD(sp1B4, s32*, 4) = M2C_FIELD(lbl_803B9670, s32*, 0x38);
    M2C_FIELD(sp1B4, s32*, 8) = M2C_FIELD(lbl_803B9670, s32*, 0x3C);
    M2C_FIELD(sp1B4, s32*, 0xC) = M2C_FIELD(lbl_803B9670, s32*, 0x40);
    M2C_FIELD(sp1B4, s32*, 0x10) = M2C_FIELD(lbl_803B9670, s32*, 0x44);
    M2C_FIELD(sp1B4, s32*, 0x14) = M2C_FIELD(lbl_803B9670, s32*, 0x48);
    M2C_FIELD(sp1B4, s32*, 0x18) = M2C_FIELD(lbl_803B9670, s32*, 0x4C);
    hsd_803B3344(0xFFU);
    hsd_803B3344(0xC4U);
    hsd_803B3344(0U);
    hsd_803B3344(0x1FU);
    hsd_803B3344(1U);
    hsd_803B3398(sp1B4, 0x1CU);
    var_r5 = sp100 - 8;
    var_r4 = (u8*) (lbl_803B9670 + 0x48);
    for (var_ctr = 0x16; var_ctr != 0; var_ctr--) {
        var_r4 += 8;
        var_r5 += 8;
        M2C_FIELD(var_r5, s32*, 0) = M2C_FIELD(var_r4, s32*, 0);
        M2C_FIELD(var_r5, s32*, 4) = M2C_FIELD(var_r4, s32*, 4);
    }
    M2C_FIELD(var_r5, u16*, 8) = (u16) M2C_FIELD(var_r4, u16*, 8);
    hsd_803B3344(0xFFU);
    hsd_803B3344(0xC4U);
    hsd_803B3344(0U);
    hsd_803B3344(0xB5U);
    hsd_803B3344(0x10U);
    hsd_803B3398(sp100, 0xB2U);
    var_r5_2 = sp4C - 8;
    var_r4_2 = (u8*) (lbl_803B9670 + 0xFC);
    for (var_ctr_2 = 0x16; var_ctr_2 != 0; var_ctr_2--) {
        var_r4_2 += 8;
        var_r5_2 += 8;
        M2C_FIELD(var_r5_2, s32*, 0) = M2C_FIELD(var_r4_2, s32*, 0);
        M2C_FIELD(var_r5_2, s32*, 4) = M2C_FIELD(var_r4_2, s32*, 4);
    }
    M2C_FIELD(var_r5_2, u16*, 8) = (u16) M2C_FIELD(var_r4_2, u16*, 8);
    hsd_803B3344(0xFFU);
    hsd_803B3344(0xC4U);
    hsd_803B3344(0U);
    hsd_803B3344(0xB5U);
    hsd_803B3344(0x11U);
    hsd_803B3398(sp4C, 0xB2U);
    hsd_803B4D64(arg1, arg2);
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_5 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_5 + 1;
        *temp_r3_5 = 0xFF;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_6 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_6 + 1;
        *temp_r3_6 = 0xDA;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_7 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_7 + 1;
        *temp_r3_7 = 0;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_8 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_8 + 1;
        *temp_r3_8 = 0xC;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_9 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_9 + 1;
        *temp_r3_9 = 3;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_10 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_10 + 1;
        *temp_r3_10 = 0;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_11 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_11 + 1;
        *temp_r3_11 = 0;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_12 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_12 + 1;
        *temp_r3_12 = 1;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_13 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_13 + 1;
        *temp_r3_13 = 0x11;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_14 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_14 + 1;
        *temp_r3_14 = 2;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_15 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_15 + 1;
        *temp_r3_15 = 0x11;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_16 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_16 + 1;
        *temp_r3_16 = 0;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_17 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_17 + 1;
        *temp_r3_17 = 0x3F;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_18 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_18 + 1;
        *temp_r3_18 = 0;
    } else {
        longjmp(&hsd_804D2648, 1);
    }
    for (var_r24 = 0; var_r24 < arg2; var_r24 += 0x10) {
        for (var_r25 = 0; var_r25 < arg1; var_r25 += 0x10) {
            hsd_803B3408((u8*) arg0, var_r25, var_r24, arg1, arg2);
            var_r26 = 0;
            var_r23 = base + 0x118;
        loop_61:
            if (var_r26 < 4) {
                fn_803B376C(var_r23);
                var_r4_3 = var_r23;
                var_r5_3 = base + 0x718;
                for (var_r3 = 0; var_r3 < 0x40; var_r3 += 8) {
                    temp_r6 = quant_table + var_r3;
                    temp_r7 = M2C_FIELD(temp_r6, u8*, 0);
                    M2C_FIELD(var_r5_3, s32*, 0) =
                        (s32) ((s32) M2C_FIELD(var_r4_3, s32*, 0) /
                               (s32) ((s32) temp_r7 / (s32) lbl_804D6398));
                    M2C_FIELD(var_r5_3, s32*, 4) =
                        (s32) ((s32) M2C_FIELD(var_r4_3, s32*, 4) /
                               (s32) ((s32) M2C_FIELD(temp_r6, u8*, 1) /
                                      (s32) lbl_804D6398));
                    M2C_FIELD(var_r5_3, s32*, 8) =
                        (s32) ((s32) M2C_FIELD(var_r4_3, s32*, 8) /
                               (s32) ((s32) M2C_FIELD(temp_r6, u8*, 2) /
                                      (s32) lbl_804D6398));
                    M2C_FIELD(var_r5_3, s32*, 0xC) =
                        (s32) ((s32) M2C_FIELD(var_r4_3, s32*, 0xC) /
                               (s32) ((s32) M2C_FIELD(temp_r6, u8*, 3) /
                                      (s32) lbl_804D6398));
                    M2C_FIELD(var_r5_3, s32*, 0x10) =
                        (s32) ((s32) M2C_FIELD(var_r4_3, s32*, 0x10) /
                               (s32) ((s32) M2C_FIELD(temp_r6, u8*, 4) /
                                      (s32) lbl_804D6398));
                    M2C_FIELD(var_r5_3, s32*, 0x14) =
                        (s32) ((s32) M2C_FIELD(var_r4_3, s32*, 0x14) /
                               (s32) ((s32) M2C_FIELD(temp_r6, u8*, 5) /
                                      (s32) lbl_804D6398));
                    M2C_FIELD(var_r5_3, s32*, 0x18) =
                        (s32) ((s32) M2C_FIELD(var_r4_3, s32*, 0x18) /
                               (s32) ((s32) M2C_FIELD(temp_r6, u8*, 6) /
                                      (s32) lbl_804D6398));
                    temp_r7_2 = M2C_FIELD(var_r4_3, s32*, 0x1C);
                    var_r4_3 += 0x20;
                    M2C_FIELD(var_r5_3, s32*, 0x1C) =
                        (s32) (temp_r7_2 /
                               (s32) ((s32) M2C_FIELD(temp_r6, u8*, 7) /
                                      (s32) lbl_804D6398));
                    var_r5_3 += 0x20;
                }
                hsd_803B3CD8(0);
                var_r23 += 0x100;
                var_r26 += 1;
                goto loop_61;
            }
            fn_803B376C(base + 0x518);
            var_r26_2 = base + 0x718;
            var_r5_4 = var_r26_2;
            var_r4_4 = base + 0x518;
            for (var_r3_2 = 0; var_r3_2 < 0x40; var_r3_2 += 8) {
                temp_r6_2 = quant_table + 0x40 + var_r3_2;
                temp_r7_3 = M2C_FIELD(temp_r6_2, u8*, 0);
                M2C_FIELD(var_r5_4, s32*, 0) =
                    (s32) ((s32) M2C_FIELD(var_r4_4, s32*, 0) /
                           (s32) ((s32) temp_r7_3 / (s32) lbl_804D6398));
                M2C_FIELD(var_r5_4, s32*, 4) =
                    (s32) ((s32) M2C_FIELD(var_r4_4, s32*, 4) /
                           (s32) ((s32) M2C_FIELD(temp_r6_2, u8*, 1) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r5_4, s32*, 8) =
                    (s32) ((s32) M2C_FIELD(var_r4_4, s32*, 8) /
                           (s32) ((s32) M2C_FIELD(temp_r6_2, u8*, 2) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r5_4, s32*, 0xC) =
                    (s32) ((s32) M2C_FIELD(var_r4_4, s32*, 0xC) /
                           (s32) ((s32) M2C_FIELD(temp_r6_2, u8*, 3) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r5_4, s32*, 0x10) =
                    (s32) ((s32) M2C_FIELD(var_r4_4, s32*, 0x10) /
                           (s32) ((s32) M2C_FIELD(temp_r6_2, u8*, 4) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r5_4, s32*, 0x14) =
                    (s32) ((s32) M2C_FIELD(var_r4_4, s32*, 0x14) /
                           (s32) ((s32) M2C_FIELD(temp_r6_2, u8*, 5) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r5_4, s32*, 0x18) =
                    (s32) ((s32) M2C_FIELD(var_r4_4, s32*, 0x18) /
                           (s32) ((s32) M2C_FIELD(temp_r6_2, u8*, 6) /
                                  (s32) lbl_804D6398));
                temp_r7_4 = M2C_FIELD(var_r4_4, s32*, 0x1C);
                var_r4_4 += 0x20;
                M2C_FIELD(var_r5_4, s32*, 0x1C) =
                    (s32) (temp_r7_4 /
                           (s32) ((s32) M2C_FIELD(temp_r6_2, u8*, 7) /
                                  (s32) lbl_804D6398));
                var_r5_4 += 0x20;
            }
            hsd_803B3CD8(1);
            fn_803B376C(base + 0x618);
            var_r4_5 = base + 0x618;
            for (var_r3_3 = 0; var_r3_3 < 0x40; var_r3_3 += 8) {
                temp_r5 = quant_table + 0x40 + var_r3_3;
                temp_r6_3 = M2C_FIELD(temp_r5, u8*, 0);
                M2C_FIELD(var_r26_2, s32*, 0) =
                    (s32) ((s32) M2C_FIELD(var_r4_5, s32*, 0) /
                           (s32) ((s32) temp_r6_3 / (s32) lbl_804D6398));
                M2C_FIELD(var_r26_2, s32*, 4) =
                    (s32) ((s32) M2C_FIELD(var_r4_5, s32*, 4) /
                           (s32) ((s32) M2C_FIELD(temp_r5, u8*, 1) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r26_2, s32*, 8) =
                    (s32) ((s32) M2C_FIELD(var_r4_5, s32*, 8) /
                           (s32) ((s32) M2C_FIELD(temp_r5, u8*, 2) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r26_2, s32*, 0xC) =
                    (s32) ((s32) M2C_FIELD(var_r4_5, s32*, 0xC) /
                           (s32) ((s32) M2C_FIELD(temp_r5, u8*, 3) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r26_2, s32*, 0x10) =
                    (s32) ((s32) M2C_FIELD(var_r4_5, s32*, 0x10) /
                           (s32) ((s32) M2C_FIELD(temp_r5, u8*, 4) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r26_2, s32*, 0x14) =
                    (s32) ((s32) M2C_FIELD(var_r4_5, s32*, 0x14) /
                           (s32) ((s32) M2C_FIELD(temp_r5, u8*, 5) /
                                  (s32) lbl_804D6398));
                M2C_FIELD(var_r26_2, s32*, 0x18) =
                    (s32) ((s32) M2C_FIELD(var_r4_5, s32*, 0x18) /
                           (s32) ((s32) M2C_FIELD(temp_r5, u8*, 6) /
                                  (s32) lbl_804D6398));
                temp_r6_4 = M2C_FIELD(var_r4_5, s32*, 0x1C);
                var_r4_5 += 0x20;
                M2C_FIELD(var_r26_2, s32*, 0x1C) =
                    (s32) (temp_r6_4 /
                           (s32) ((s32) M2C_FIELD(temp_r5, u8*, 7) /
                                  (s32) lbl_804D6398));
                var_r26_2 += 0x20;
            }
            hsd_803B3CD8(2);
        }
    }
    if ((s32) hsd_804D79AC != 0) {
        temp_r6_5 = 8 - hsd_804D79AC;
        hsd_804D79B0 <<= temp_r6_5;
        hsd_804D79B0 |= (1 << temp_r6_5) - 1;
        if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
            temp_r3_19 = hsd_804D79A0;
            hsd_804D79A0 = temp_r3_19 + 1;
            *temp_r3_19 = hsd_804D79B0;
        } else {
            longjmp((__jmp_buf*) base, 1);
        }
        hsd_804D79B0 = 0;
        hsd_804D79AC = 0;
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_20 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_20 + 1;
        *temp_r3_20 = 0xFF;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    if ((u8*) hsd_804D79A0 < &hsd_804D79A4[hsd_804D79A8]) {
        temp_r3_21 = hsd_804D79A0;
        hsd_804D79A0 = temp_r3_21 + 1;
        *temp_r3_21 = 0xD9;
    } else {
        longjmp((__jmp_buf*) base, 1);
    }
    return hsd_804D79A0 - hsd_804D79A4;
}

void hsd_803B5C2C(s32 arg0)
{
    lbl_804D6398 = arg0;
    if ((arg0 < 1) || (arg0 > 0xA)) {
        lbl_804D6398 = 3;
    }
}
