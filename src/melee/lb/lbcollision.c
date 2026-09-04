#include "lbcollision.h"

#include "lb_00B0.h"
#include "lbaudio_ax.h"
#include "lbvector.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/types.h"

#include "lb/forward.h"

#include "lb/types.h"

#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>
#include <baselib/state.h>
#include <baselib/tev.h>

/* 006E58 */ static bool
lbColl_80006E58(Vec3* hit_start, Vec3* hit_end, Vec3* hurt_start,
                Vec3* hurt_end, Vec3* hit_closest, Vec3* hurt_closest,
                MtxPtr hurt_mtx, Vec3* out_contact_pos, float* out_overlap,
                float hit_radius, float hurt_radius, float broadphase_scale);

/// .sdata
static GXColor lbColl_804D36A0 = { 0xFF, 0x00, 0x00, 0x80 };
static GXColor lbColl_804D36A4 = { 0xFF, 0x00, 0xFF, 0x80 };
static GXColor lbColl_804D36A8 = { 0x80, 0x00, 0x00, 0x80 };
static GXColor lbColl_804D36AC = { 0xFF, 0xFF, 0x00, 0x80 };
static GXColor lbColl_804D36B0 = { 0x80, 0x80, 0x00, 0x80 };
static GXColor lbColl_804D36B4 = { 0x00, 0xFF, 0x00, 0x80 };
static GXColor lbColl_804D36B8 = { 0x00, 0x80, 0x00, 0x80 };
static GXColor lbColl_804D36BC = { 0x00, 0x00, 0xFF, 0x80 };
static GXColor lbColl_804D36C0 = { 0x00, 0x00, 0x80, 0x80 };
static GXColor lbColl_804D36C4 = { 0x00, 0xFF, 0xFF, 0x80 };
static GXColor lbColl_804D36C8 = { 0x00, 0x80, 0x80, 0x80 };
static GXColor lbColl_804D36CC = { 0x00, 0xFF, 0x80, 0x80 };
static GXColor lbColl_804D36D0 = { 0x00, 0x80, 0x40, 0x80 };
static GXColor lbColl_804D36D4 = { 0x00, 0x80, 0xFF, 0x80 };
static GXColor lbColl_804D36D8 = { 0x00, 0x40, 0x80, 0x80 };
static GXColor lbColl_804D36DC = { 0xFF, 0xFF, 0xFF, 0x80 };
static GXColor lbColl_804D36E0 = { 0xFF, 0x80, 0x00, 0x80 };
static GXColor lbColl_804D36E4 = { 0x80, 0x40, 0x00, 0x80 };
static GXColor lbColl_804D36E8 = { 0xFF, 0xFF, 0xFF, 0x80 };
static GXColor lbColl_804D36EC = { 0x80, 0x80, 0x80, 0x80 };
static GXColor lbColl_804D36F0 = { 0xFF, 0xFF, 0x00, 0x80 };

/// .data
int lbColl_803B9880[] = {
    0x00083D60, 0x00083D60, 0x00083D60, 0x0000005B, 0x0000005A, 0x00000059,
    0x00000058, 0x00000057, 0x00000056, 0x0000006F, 0x00000070, 0x00000071,
    0x00000054, 0x00000054, 0x00000054, 0x0000005A, 0x00000059, 0x000000DF,
    0x000000E1, 0x000000E1, 0x000000E1, 0x00000062, 0x00000063, 0x00000064,
    0x00000065, 0x00000066, 0x00000067, 0x0004461B, 0x0004461B, 0x0004461B,
    0x000000F1, 0x000000F1, 0x000000F1, 0x0000005E, 0x0000005D, 0x0000005C,
    0x00035BAF, 0x00035BB2, 0x00035BB5, 0x00083D60, 0x00083D60, 0x0000020D,
};

static GXColor lbColl_804D36F4 = { 0x80, 0x80, 0x00, 0x80 };
static GXColor lbColl_804D36F8 = { 0xFF, 0x00, 0x00, 0x80 };
static GXColor lbColl_804D36FC = { 0x80, 0x00, 0x00, 0x80 };

struct unk {
    GXColor* pad;
    GXColor* pad_x;
} lbColl_803B9928[] = {
    &lbColl_804D36AC, &lbColl_804D36B0, &lbColl_804D36B4,
    &lbColl_804D36B8, &lbColl_804D36BC, &lbColl_804D36C0,
};

u8 lbColl_SpherePositions[0x1A0] = {
    0x29, 0xCF, 0x2D, 0x41, 0x11, 0x51, 0x20, 0x00, 0x2D, 0x41, 0x1F, 0xFF,
    0x29, 0xCF, 0xE7, 0x83, 0x29, 0xCF, 0x00, 0x00, 0xC4, 0xE0, 0x18, 0x7D,
    0x11, 0x51, 0x3B, 0x20, 0x11, 0x51, 0x11, 0x51, 0xD2, 0xBF, 0x29, 0xCF,
    0x00, 0x00, 0xD2, 0xBF, 0x2D, 0x41, 0x16, 0xA0, 0x18, 0x7D, 0x36, 0xA0,
    0x00, 0x00, 0x18, 0x7D, 0x3B, 0x20, 0x09, 0x5F, 0xC4, 0xE0, 0x16, 0xA0,
    0x00, 0x00, 0x3B, 0x20, 0x18, 0x7D, 0x09, 0x5F, 0x3B, 0x20, 0x16, 0xA0,
    0x11, 0x51, 0x2D, 0x41, 0x29, 0xCF, 0x00, 0x00, 0x2D, 0x41, 0x2D, 0x41,
    0x29, 0xCF, 0x18, 0x7D, 0x29, 0xCF, 0x36, 0xA0, 0x18, 0x7D, 0x16, 0xA0,
    0x2D, 0x41, 0x00, 0x00, 0x2D, 0x41, 0x3B, 0x20, 0x00, 0x00, 0x18, 0x7D,
    0x36, 0xA0, 0xE7, 0x83, 0x16, 0xA0, 0x16, 0xA0, 0x3B, 0x20, 0x09, 0x5F,
    0x20, 0x00, 0xD2, 0xBF, 0x1F, 0xFF, 0x29, 0xCF, 0xD2, 0xBF, 0x11, 0x51,
    0x16, 0xA0, 0xC4, 0xE0, 0x09, 0x5F, 0x11, 0x51, 0xC4, 0xE0, 0x11, 0x51,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x18, 0x7D, 0x00, 0x00, 0x3B, 0x20,
    0x16, 0xA0, 0xE7, 0x83, 0x36, 0xA0, 0x00, 0x00, 0xE7, 0x83, 0x3B, 0x20,
    0x00, 0x00, 0x3B, 0x20, 0xE7, 0x83, 0x00, 0x00, 0x2D, 0x41, 0xD2, 0xBF,
    0x00, 0x00, 0x18, 0x7D, 0xC4, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01,
    0x00, 0x00, 0xE7, 0x83, 0xC4, 0xE0, 0x00, 0x00, 0xD2, 0xBF, 0xD2, 0xBF,
    0x00, 0x00, 0xC4, 0xE0, 0xE7, 0x83, 0x09, 0x5F, 0x3B, 0x20, 0xE9, 0x60,
    0x11, 0x51, 0x2D, 0x41, 0xD6, 0x31, 0x16, 0xA0, 0x18, 0x7D, 0xC9, 0x60,
    0x18, 0x7D, 0x00, 0x00, 0xC4, 0xE0, 0x16, 0xA0, 0xE7, 0x83, 0xC9, 0x60,
    0x11, 0x51, 0xD2, 0xBF, 0xD6, 0x31, 0x09, 0x5F, 0xC4, 0xE0, 0xE9, 0x60,
    0x11, 0x51, 0x3B, 0x20, 0xEE, 0xAF, 0x1F, 0xFF, 0x2D, 0x41, 0xE0, 0x00,
    0x29, 0xCF, 0x18, 0x7D, 0xD6, 0x31, 0x2D, 0x41, 0x00, 0x00, 0xD2, 0xBF,
    0x29, 0xCF, 0xE7, 0x83, 0xD6, 0x31, 0x1F, 0xFF, 0xD2, 0xBF, 0xE0, 0x00,
    0x11, 0x51, 0xC4, 0xE0, 0xEE, 0xAF, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x18, 0x7D, 0x3B, 0x20, 0x00, 0x00, 0x16, 0xA0, 0x3B, 0x20, 0xF6, 0xA1,
    0x2D, 0x41, 0x2D, 0x41, 0x00, 0x00, 0x29, 0xCF, 0x2D, 0x41, 0xEE, 0xAF,
    0x3B, 0x20, 0x18, 0x7D, 0x00, 0x00, 0x36, 0xA0, 0x18, 0x7D, 0xE9, 0x60,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x20, 0x00, 0x00, 0xE7, 0x83,
    0x3B, 0x20, 0xE7, 0x83, 0x00, 0x00, 0x36, 0xA0, 0xE7, 0x83, 0xE9, 0x60,
    0x2D, 0x41, 0xD2, 0xBF, 0x00, 0x00, 0x29, 0xCF, 0xD2, 0xBF, 0xEE, 0xAF,
    0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x18, 0x7D, 0xC4, 0xE0, 0x00, 0x00,
    0x16, 0xA0, 0xC4, 0xE0, 0xF6, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 lbColl_SphereNormals[0x1A0] = {
    0x29, 0xC7, 0x2D, 0x49, 0x11, 0x4E, 0x1F, 0xF9, 0x2D, 0x49, 0x1F, 0xF9,
    0x29, 0xCD, 0xE7, 0x7B, 0x29, 0xCD, 0x00, 0x00, 0xC4, 0xDC, 0x18, 0x75,
    0x11, 0x4B, 0x3B, 0x24, 0x11, 0x4B, 0x11, 0x4E, 0xD2, 0xB7, 0x29, 0xC7,
    0x00, 0x00, 0xD2, 0xB7, 0x2D, 0x38, 0x16, 0x9F, 0x18, 0x85, 0x36, 0x9D,
    0x00, 0x00, 0x18, 0x85, 0x3B, 0x1D, 0x09, 0x5C, 0xC4, 0xDC, 0x16, 0x99,
    0x00, 0x00, 0x3B, 0x24, 0x18, 0x75, 0x09, 0x5C, 0x3B, 0x24, 0x16, 0x99,
    0x11, 0x4E, 0x2D, 0x49, 0x29, 0xC7, 0x00, 0x00, 0x2D, 0x49, 0x2D, 0x38,
    0x29, 0xCD, 0x18, 0x85, 0x29, 0xCD, 0x36, 0x9D, 0x18, 0x85, 0x16, 0x9F,
    0x2D, 0x41, 0x00, 0x00, 0x2D, 0x41, 0x3B, 0x20, 0x00, 0x00, 0x18, 0x7D,
    0x36, 0x9D, 0xE7, 0x7B, 0x16, 0x9F, 0x16, 0x99, 0x3B, 0x24, 0x09, 0x5C,
    0x1F, 0xF9, 0xD2, 0xB7, 0x1F, 0xF9, 0x29, 0xC7, 0xD2, 0xB7, 0x11, 0x4E,
    0x16, 0x99, 0xC4, 0xDC, 0x09, 0x5C, 0x11, 0x4B, 0xC4, 0xDC, 0x11, 0x4B,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x18, 0x7D, 0x00, 0x00, 0x3B, 0x20,
    0x16, 0x9F, 0xE7, 0x7B, 0x36, 0x9D, 0x00, 0x00, 0xE7, 0x7B, 0x3B, 0x1D,
    0x00, 0x00, 0x3B, 0x24, 0xE7, 0x8B, 0x00, 0x00, 0x2D, 0x49, 0xD2, 0xC8,
    0x00, 0x00, 0x18, 0x85, 0xC4, 0xE3, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00,
    0x00, 0x00, 0xE7, 0x7B, 0xC4, 0xE3, 0x00, 0x00, 0xD2, 0xB7, 0xD2, 0xC8,
    0x00, 0x00, 0xC4, 0xDC, 0xE7, 0x8B, 0x09, 0x5C, 0x3B, 0x24, 0xE9, 0x67,
    0x11, 0x4E, 0x2D, 0x49, 0xD6, 0x39, 0x16, 0x9F, 0x18, 0x85, 0xC9, 0x63,
    0x18, 0x7D, 0x00, 0x00, 0xC4, 0xE0, 0x16, 0x9F, 0xE7, 0x7B, 0xC9, 0x63,
    0x11, 0x4E, 0xD2, 0xB7, 0xD6, 0x39, 0x09, 0x5C, 0xC4, 0xDC, 0xE9, 0x67,
    0x11, 0x4B, 0x3B, 0x24, 0xEE, 0xB5, 0x1F, 0xF9, 0x2D, 0x49, 0xE0, 0x07,
    0x29, 0xCD, 0x18, 0x85, 0xD6, 0x33, 0x2D, 0x41, 0x00, 0x00, 0xD2, 0xBF,
    0x29, 0xCD, 0xE7, 0x7B, 0xD6, 0x33, 0x1F, 0xF9, 0xD2, 0xB7, 0xE0, 0x07,
    0x11, 0x4B, 0xC4, 0xDC, 0xEE, 0xB5, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x18, 0x75, 0x3B, 0x24, 0x00, 0x00, 0x16, 0x99, 0x3B, 0x24, 0xF6, 0xA4,
    0x2D, 0x38, 0x2D, 0x49, 0x00, 0x00, 0x29, 0xC7, 0x2D, 0x49, 0xEE, 0xB2,
    0x3B, 0x1D, 0x18, 0x85, 0x00, 0x00, 0x36, 0x9D, 0x18, 0x85, 0xE9, 0x61,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x20, 0x00, 0x00, 0xE7, 0x83,
    0x3B, 0x1D, 0xE7, 0x7B, 0x00, 0x00, 0x36, 0x9D, 0xE7, 0x7B, 0xE9, 0x61,
    0x2D, 0x38, 0xD2, 0xB7, 0x00, 0x00, 0x29, 0xC7, 0xD2, 0xB7, 0xEE, 0xB2,
    0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x18, 0x75, 0xC4, 0xDC, 0x00, 0x00,
    0x16, 0x99, 0xC4, 0xDC, 0xF6, 0xA4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 lbColl_SphereDisplayList[0x120] = {
    0x98, 0x00, 0x75, 0x0B, 0x0B, 0x04, 0x04, 0x0C, 0x0C, 0x01, 0x01, 0x07,
    0x07, 0x0E, 0x0E, 0x19, 0x19, 0x10, 0x10, 0x1A, 0x1A, 0x02, 0x02, 0x05,
    0x05, 0x14, 0x14, 0x09, 0x09, 0x14, 0x14, 0x17, 0x17, 0x15, 0x15, 0x17,
    0x17, 0x16, 0x16, 0x17, 0x17, 0x3E, 0x3E, 0x09, 0x09, 0x03, 0x03, 0x05,
    0x05, 0x06, 0x06, 0x1A, 0x1A, 0x1B, 0x1B, 0x19, 0x19, 0x18, 0x18, 0x07,
    0x07, 0x08, 0x08, 0x0C, 0x0C, 0x0D, 0x0D, 0x0B, 0x0B, 0x0A, 0x0A, 0x0B,
    0x0B, 0x31, 0x31, 0x04, 0x04, 0x31, 0x31, 0x13, 0x13, 0x32, 0x32, 0x00,
    0x00, 0x34, 0x34, 0x0F, 0x0F, 0x36, 0x36, 0x11, 0x11, 0x38, 0x38, 0x12,
    0x12, 0x3A, 0x3A, 0x15, 0x15, 0x3C, 0x3C, 0x16, 0x16, 0x3F, 0x3F, 0x3E,
    0x3E, 0x3F, 0x3F, 0x40, 0x40, 0x3F, 0x3F, 0x3D, 0x3D, 0x3C, 0x3C, 0x3B,
    0x3B, 0x3A, 0x3A, 0x39, 0x39, 0x38, 0x38, 0x37, 0x37, 0x36, 0x36, 0x35,
    0x35, 0x34, 0x34, 0x33, 0x33, 0x32, 0x32, 0x33, 0x33, 0x31, 0x31, 0x33,
    0x33, 0x2A, 0x2A, 0x35, 0x35, 0x2B, 0x2B, 0x37, 0x37, 0x2C, 0x2C, 0x39,
    0x39, 0x2D, 0x2D, 0x3B, 0x3B, 0x2E, 0x2E, 0x3D, 0x3D, 0x2F, 0x2F, 0x40,
    0x40, 0x30, 0x30, 0x3E, 0x3E, 0x30, 0x30, 0x29, 0x29, 0x30, 0x30, 0x28,
    0x28, 0x2F, 0x2F, 0x27, 0x27, 0x2E, 0x2E, 0x26, 0x26, 0x2D, 0x2D, 0x25,
    0x25, 0x2C, 0x2C, 0x24, 0x24, 0x2B, 0x2B, 0x23, 0x23, 0x2A, 0x2A, 0x23,
    0x23, 0x31, 0x31, 0x23, 0x23, 0x1C, 0x1C, 0x24, 0x24, 0x1D, 0x1D, 0x25,
    0x25, 0x1E, 0x1E, 0x26, 0x26, 0x1F, 0x1F, 0x27, 0x27, 0x20, 0x20, 0x28,
    0x28, 0x21, 0x21, 0x29, 0x29, 0x22, 0x22, 0x3E, 0x3E, 0x98, 0x00, 0x0C,
    0x15, 0x15, 0x14, 0x14, 0x12, 0x12, 0x02, 0x02, 0x11, 0x11, 0x10, 0x10,
    0x0F, 0x0F, 0x0E, 0x0E, 0x00, 0x00, 0x01, 0x01, 0x13, 0x13, 0x04, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 lbColl_CylinderPositions[0x80] = {
    0xE0, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x01, 0xE7, 0x83, 0x3B, 0x20,
    0xE0, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01,
    0x20, 0x00, 0x00, 0x00, 0xC0, 0x01, 0xE0, 0x01, 0xC4, 0xE0, 0xE7, 0x83,
    0xE0, 0x01, 0xE7, 0x83, 0xC4, 0xE0, 0xE0, 0x01, 0xD2, 0xBF, 0xD2, 0xBF,
    0xE0, 0x00, 0x18, 0x7D, 0xC4, 0xE0, 0x00, 0x00, 0x18, 0x7D, 0xC4, 0xE0,
    0x1F, 0xFF, 0x18, 0x7D, 0xC4, 0xE0, 0x1F, 0xFF, 0x18, 0x7D, 0x3B, 0x20,
    0xE0, 0x00, 0x18, 0x7D, 0x3B, 0x20, 0xE0, 0x00, 0x2D, 0x41, 0x2D, 0x41,
    0x00, 0x00, 0x18, 0x7D, 0x3B, 0x20, 0xE0, 0x01, 0xC0, 0x01, 0x00, 0x00,
    0x00, 0x00, 0xE7, 0x83, 0xC4, 0xE0, 0x00, 0x00, 0xD2, 0xBF, 0xD2, 0xBF,
    0x20, 0x00, 0xD2, 0xBF, 0xD2, 0xBF, 0x20, 0x00, 0xE7, 0x83, 0xC4, 0xE0,
    0xE0, 0x00, 0x2D, 0x41, 0xD2, 0xBF, 0x00, 0x00,
};
u8 lbColl_UnknownData[0xA0] = {
    0x2D, 0x41, 0xD2, 0xBF, 0x1F, 0xFF, 0x2D, 0x41, 0xD2, 0xBF, 0x00, 0x00,
    0xC4, 0xE0, 0xE7, 0x83, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x20, 0x00,
    0xC0, 0x01, 0x00, 0x00, 0x20, 0x00, 0xC4, 0xE0, 0xE7, 0x83, 0x00, 0x00,
    0x2D, 0x41, 0x2D, 0x41, 0x1F, 0xFF, 0x3B, 0x20, 0x18, 0x7D, 0x1F, 0xFF,
    0x2D, 0x41, 0x2D, 0x41, 0x00, 0x00, 0xE7, 0x83, 0x3B, 0x20, 0x00, 0x00,
    0x00, 0x00, 0x3F, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x20, 0x00,
    0xE7, 0x83, 0x3B, 0x20, 0x20, 0x00, 0xD2, 0xBF, 0x2D, 0x41, 0x20, 0x00,
    0xC4, 0xE0, 0x18, 0x7D, 0xE0, 0x00, 0x3B, 0x20, 0xE7, 0x83, 0x00, 0x00,
    0x3B, 0x20, 0xE7, 0x83, 0x1F, 0xFF, 0x3B, 0x20, 0xE7, 0x83, 0x1F, 0xFF,
    0x40, 0x00, 0x00, 0x00, 0xE0, 0x01, 0xC4, 0xE0, 0x18, 0x7D, 0xE0, 0x01,
    0xD2, 0xBF, 0x2D, 0x41, 0x00, 0x00, 0xD2, 0xBF, 0x2D, 0x41, 0x00, 0x00,
    0xC4, 0xE0, 0x18, 0x7D, 0xE0, 0x00, 0x3B, 0x20, 0x18, 0x7D, 0xE0, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3B, 0x20, 0x18, 0x7D,
};
u8 lbColl_CylinderNormals[0x60] = {
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x18, 0xFF, 0xC5,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x3B, 0x00, 0x00, 0xFF, 0xD3, 0xFF, 0xD3,
    0x00, 0x00, 0xFF, 0xE8, 0xFF, 0xC5, 0x00, 0x00, 0x00, 0x2D, 0xFF, 0xD3,
    0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC5, 0xFF, 0xE8,
    0x00, 0x00, 0x00, 0x2D, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    0x00, 0x00, 0xFF, 0xE8, 0x00, 0x3B, 0x00, 0x00, 0x00, 0x3B, 0xFF, 0xE8,
    0x00, 0x00, 0xFF, 0xD3, 0x00, 0x2D, 0x00, 0x00, 0xFF, 0xC5, 0x00, 0x18,
    0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x18,
};
u8 lbColl_CylinderDisplayList[0xA0] = {
    0x98, 0x00, 0x45, 0x2C, 0x0F, 0x2D, 0x0E, 0x2F, 0x0F, 0x2D, 0x0E, 0x2E,
    0x0E, 0x24, 0x0B, 0x25, 0x0B, 0x14, 0x05, 0x15, 0x05, 0x08, 0x01, 0x09,
    0x01, 0x02, 0x00, 0x03, 0x00, 0x06, 0x04, 0x10, 0x04, 0x07, 0x03, 0x11,
    0x03, 0x05, 0x07, 0x17, 0x07, 0x0F, 0x06, 0x18, 0x06, 0x28, 0x0D, 0x2B,
    0x0D, 0x29, 0x0C, 0x2A, 0x0C, 0x01, 0x0A, 0x1E, 0x0A, 0x00, 0x09, 0x1F,
    0x09, 0x0C, 0x02, 0x0E, 0x02, 0x0D, 0x08, 0x1B, 0x08, 0x2C, 0x0F, 0x1B,
    0x08, 0x2F, 0x0F, 0x1D, 0x08, 0x2F, 0x0F, 0x1C, 0x0F, 0x2E, 0x0E, 0x27,
    0x0E, 0x25, 0x0B, 0x26, 0x0B, 0x15, 0x05, 0x16, 0x05, 0x09, 0x01, 0x0A,
    0x01, 0x03, 0x00, 0x04, 0x00, 0x10, 0x04, 0x13, 0x04, 0x11, 0x03, 0x12,
    0x03, 0x17, 0x07, 0x1A, 0x07, 0x18, 0x06, 0x19, 0x06, 0x2B, 0x0D, 0x23,
    0x0D, 0x2A, 0x0C, 0x22, 0x0C, 0x1E, 0x0A, 0x21, 0x0A, 0x1F, 0x09, 0x20,
    0x09, 0x0E, 0x02, 0x0B, 0x02, 0x1B, 0x08, 0x1D, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

/// .text

int lbColl_80005BB0(HitCapsule* arg0, int arg1)
{
    u32 temp_r0;
    u32 temp_r6;

    temp_r0 = arg0->sfx_kind;
    if (temp_r0 == 0xD) {
        temp_r6 = arg0->sfx_severity;
        if (temp_r6 == 2) {
            return lbAudioAx_80024184(
                *(lbColl_803B9880 + (temp_r0 * 3) + temp_r6), 127, 64, arg1);
        }
    }

    return lbAudioAx_80024184(
        *(lbColl_803B9880 + (temp_r0 * 3) + (arg0->sfx_severity)), 127, 64,
        -1);
}

static inline bool nearzero(float x)
{
    if (x < 1e-5F && x > -1e-5F) {
        return true;
    } else {
        return false;
    }
}

bool lbColl_80005C44(const Vec3* arg0, const Vec3* arg1, const Vec3* arg2,
                     Vec3* arg3, float arg8, float arg9)
{
    float temp_f2;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 d1;
    float d2_x, d2_y, d2_z;

    temp_f2 = arg8 + arg9;
    sp38 = *arg0;
    sp2C = *arg2;

    if (sp38.x > arg1->x) {
        if (sp38.x + temp_f2 < sp2C.x) {
            return 0;
        }
        if (arg1->x - temp_f2 > sp2C.x) {
            return 0;
        }
    } else {
        if (sp38.x - temp_f2 > sp2C.x) {
            return 0;
        }
        if (arg1->x + temp_f2 < sp2C.x) {
            return 0;
        }
    }
    if (sp38.y > arg1->y) {
        if (sp38.y + temp_f2 < sp2C.y) {
            return 0;
        }
        if (arg1->y - temp_f2 > sp2C.y) {
            return 0;
        }
    } else {
        if (sp38.y - temp_f2 > sp2C.y) {
            return 0;
        }
        if (arg1->y + temp_f2 < sp2C.y) {
            return 0;
        }
    }
    if (sp38.z > arg1->z) {
        if (sp38.z + temp_f2 < sp2C.z) {
            return 0;
        }
        if (arg1->z - temp_f2 > sp2C.z) {
            return 0;
        }
    } else {
        if (sp38.z - temp_f2 > sp2C.z) {
            return 0;
        }
        if (arg1->z + temp_f2 < sp2C.z) {
            return 0;
        }
    }

    d1.x = arg1->x - sp38.x;
    d1.y = arg1->y - sp38.y;
    d1.z = arg1->z - sp38.z;

    d2_x = sp38.x - sp2C.x;
    d2_y = sp38.y - sp2C.y;
    d2_z = sp38.z - sp2C.z;

    {
        float d1_dot_d1 = d1.x * d1.x + d1.y * d1.y + d1.z * d1.z;
        float d1_dot_d2 = d1.x * d2_x + d1.y * d2_y + d1.z * d2_z;
        float scale;

        if (nearzero(d1_dot_d1)) {
            scale = 0.0f;
        } else {
            scale = -d1_dot_d2 / d1_dot_d1;
            if (scale > 1.0) {
                scale = 1.0f;
            } else if (scale < 0.0) {
                scale = 0.0f;
            }
        }

        arg3->x = d1.x * scale + sp38.x;
        arg3->y = d1.y * scale + sp38.y;
        arg3->z = d1.z * scale + sp38.z;
    }

    d2_x = arg3->x - sp2C.x;
    d2_y = arg3->y - sp2C.y;
    d2_z = arg3->z - sp2C.z;

    if (SQ(temp_f2) < SQ(d2_x) + SQ(d2_y) + SQ(d2_z)) {
        return false;
    } else {
        return true;
    }
}

float lbColl_80005EBC(const Vec3* arg0, const Vec3* arg1, const Vec3* arg2,
                      float* arg3)
{
    Vec3 sp50;
    Vec3 d1;
    Vec3 sp38;
    Vec3 d2;
    float scale;
    float d1_dot_d1;
    float d1_dot_d2;
    float x;
    float y;
    float z;

    sp50 = *arg0;
    d1.x = arg1->x - arg0->x;
    d1.y = arg1->y - arg0->y;
    d1.z = arg1->z - arg0->z;

    sp38 = *arg2;
    d2.x = sp50.x - sp38.x;
    d2.y = sp50.y - sp38.y;
    d2.z = sp50.z - sp38.z;

    d1_dot_d1 = d1.x * d1.x + d1.y * d1.y + d1.z * d1.z;
    d1_dot_d2 = d1.x * d2.x + d1.y * d2.y + d1.z * d2.z;

    scale = -d1_dot_d2 / d1_dot_d1;
    if (scale > 1.0) {
        scale = 1.0F;
    } else if (scale < 0.0) {
        scale = 0.0F;
    }

    x = d1.x * scale + sp50.x - arg2->x;
    y = d1.y * scale + sp50.y - arg2->y;
    z = d1.z * scale + sp50.z - arg2->z;

    *arg3 = scale;
    return x * x + y * y + z * z;
}

float lbColl_80005FC0(Vec3* arg0, Vec3* arg1, Vec3* arg2, float* arg3)
{
    Vec3 sp50;
    Vec3 d1;
    Vec3 sp38;
    Vec3 d2;
    float scale;
    float d1_dot_d1;
    float d1_dot_d2;
    float x;
    float y;
    float z;

    sp50 = *arg0;
    d1.x = arg1->x - arg0->x;
    d1.y = arg1->y - arg0->y;

    sp38 = *arg2;
    d2.x = sp50.x - sp38.x;
    d2.y = sp50.y - sp38.y;

    d1_dot_d1 = d1.x * d1.x + d1.y * d1.y;
    d1_dot_d2 = d1.x * d2.x + d1.y * d2.y;

    scale = -d1_dot_d2 / d1_dot_d1;
    if (scale > 1.0) {
        scale = 1.0F;
    } else if (scale < 0.0) {
        scale = 0.0F;
    }

    x = d1.x * scale + sp50.x - arg2->x;
    y = d1.y * scale + sp50.y - arg2->y;

    *arg3 = scale;
    return x * x + y * y;
}

static inline bool end(Vec3* a, Vec3* b, float unk_sum)
{
    float x = a->x - b->x;
    float y = a->y - b->y;
    float z = a->z - b->z;

    if (unk_sum * unk_sum < z * z + (x * x + y * y)) {
        return false;
    }

    return true;
}

bool lbColl_80006094(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3,
                     Vec3* arg4, Vec3* arg5, float arg6, float arg7)
{
    {
        Vec3 arg4_offset;
        Vec3 arg5_offset;
        float arg1_y;
        float unk_sum = arg6 + arg7;

        PAD_STACK(60);
        {
            float candidate0_arg5_scl;
            float candidate1_arg4_scl;
            float arg3_z;
            float dot0;
            float dot1;
            Vec3 a2;
            Vec3 d1;
            Vec3 c3;
            Vec3 mid;
            Vec3 b0;
            Vec3 d2;
            Vec3 c2;
            Vec3 arg2_copy;
            Vec3 vec4 = *arg0;

            (void) vec4;
            arg4_offset = vec4;
            arg2_copy = *arg2;
            (void) arg2_copy;
            arg5_offset = arg2_copy;

            {
                float arg1_x = arg1->x;
                if (arg4_offset.x > arg1_x) {
                    {
                        float x = arg4_offset.x + unk_sum;
                        if (x < arg5_offset.x && x < arg3->x) {
                            return false;
                        }
                    }

                    {
                        float x = arg1_x - unk_sum;
                        if (x > arg5_offset.x && x > arg3->x) {
                            return false;
                        }
                    }

                } else {
                    {
                        float x = arg4_offset.x - unk_sum;
                        if (x > arg5_offset.x && x > arg3->x) {
                            return false;
                        }
                    }

                    {
                        float x = arg1_x + unk_sum;
                        if (x < arg5_offset.x && x < arg3->x) {
                            return false;
                        }
                    }
                }

                {
                    if (arg4_offset.y > (arg1_y = arg1->y)) {
                        {
                            float upper_bound = arg4_offset.y + unk_sum;

                            if (upper_bound < arg5_offset.y &&
                                upper_bound < arg3->y)
                            {
                                return false;
                            }
                        }

                        {
                            float lower_bound = arg1_y - unk_sum;

                            if (lower_bound > arg5_offset.y &&
                                lower_bound > arg3->y)
                            {
                                return false;
                            }
                        }

                    } else {
                        {
                            float y = arg4_offset.y - unk_sum;
                            if (y > arg5_offset.y && y > arg3->y) {
                                return false;
                            }
                        }

                        {
                            float y = arg1_y + unk_sum;
                            if (y < arg5_offset.y && y < arg3->y) {
                                return false;
                            }
                        }
                    }
                }
                {
                    float arg1_z;
                    if (arg4_offset.z > (arg1_z = arg1->z)) {
                        {
                            float upper_bound = arg4_offset.z + unk_sum;
                            if ((upper_bound < arg5_offset.z) &&
                                (upper_bound < arg3->z))
                            {
                                return false;
                            }
                        }
                        {
                            float lower_bound = arg1_z - unk_sum;
                            if ((lower_bound > arg5_offset.z) &&
                                (lower_bound > arg3->z))
                            {
                                return false;
                            }
                        }
                    } else {
                        {
                            float lower_bound = arg4_offset.z - unk_sum;
                            if ((lower_bound > arg5_offset.z) &&
                                (lower_bound > arg3->z))
                            {
                                return false;
                            }
                        }
                        {
                            float upper_bound = arg1_z + unk_sum;
                            if ((upper_bound < arg5_offset.z) &&
                                (upper_bound < arg3->z))
                            {
                                return false;
                            }
                        }
                    }
                    {
                        float arg4_scl;
                        float d1_x;
                        float d1_y;
                        float d1_z;
                        float d2_x;
                        float d2_y;
                        float d2_z;
                        float offset_delta_y;
                        float offset_delta_z;
                        float offset_delta_x;
                        float d1_len_sq;
                        float d2_len_sq;
                        float d1_dot_d2;
                        float d2_dot_offset_delta;
                        float d1_dot_offset_delta;
                        float denom;

                        d1_y = arg1->y - arg4_offset.y;
                        d1_z = arg1->z - arg4_offset.z;
                        d2_y = arg3->y - arg5_offset.y;
                        offset_delta_y = arg4_offset.y - arg5_offset.y;
                        d1_x = arg1_x - arg4_offset.x;
                        d2_x = arg3->x - arg5_offset.x;
                        {
                            f32 z = arg3->z;
                            arg3_z = z;
                        }
                        d2_z = arg3_z - arg5_offset.z;
                        offset_delta_x = arg4_offset.x - arg5_offset.x;
                        d1_len_sq =
                            (d1_z * d1_z) + ((d1_x * d1_x) + (d1_y * d1_y));
                        d2_len_sq =
                            (d2_z * d2_z) + ((d2_x * d2_x) + (d2_y * d2_y));
                        d1_dot_d2 =
                            (d1_z * d2_z) + ((d1_x * d2_x) + (d1_y * d2_y));
                        offset_delta_z = arg4_offset.z - arg5_offset.z;
                        d2_dot_offset_delta = (d2_z * offset_delta_z) +
                                              ((d2_x * offset_delta_x) +
                                               (d2_y * offset_delta_y));
                        d1_dot_offset_delta = (d1_z * offset_delta_z) +
                                              ((d1_x * offset_delta_x) +
                                               (d1_y * offset_delta_y));
                        denom =
                            (d1_len_sq * d2_len_sq) - (d1_dot_d2 * d1_dot_d2);

                        {
                            float arg5_scl;
                            if (approximatelyZero(d2_len_sq)) {
                                if (approximatelyZero(d1_len_sq)) {
                                    arg4_scl = 0.0f;
                                    arg5_scl = 0.0f;
                                } else {
                                    arg5_scl = 0.0f;
                                    {
                                        arg4_scl =
                                            -d1_dot_offset_delta / d1_len_sq;

                                        if (arg4_scl > 1.0) {
                                            arg4_scl = 1.0F;
                                        } else if (arg4_scl < 0.0) {
                                            arg4_scl = 0.0F;
                                        }
                                    }
                                }
                            } else {
                                if (approximatelyZero(denom)) {
                                    float arg4_mid_y;
                                    float arg4_mid_x;
                                    float arg4_offset_z;
                                    float arg1_mid_z;
                                    float arg1_mid_x;
                                    float arg1_mid_y;

                                    mid.y = 0.5 * d2_y + arg5_offset.y;
                                    mid.x = 0.5 * d2_x + arg5_offset.x;
                                    arg4_mid_y = arg4_offset.y - mid.y;
                                    arg1_mid_y = arg1->y - mid.y;
                                    mid.z = 0.5 * d2_z + arg5_offset.z;
                                    arg4_mid_x = arg4_offset.x - mid.x;
                                    arg1_mid_x = arg1_x - mid.x;
                                    arg4_offset_z = arg4_offset.z - mid.z;
                                    arg1_mid_z = arg1->z - mid.z;

                                    // lhs and rhs each the same inline
                                    if ((arg4_offset_z * arg4_offset_z +
                                         ((arg4_mid_x * arg4_mid_x) +
                                          (arg4_mid_y * arg4_mid_y))) <
                                        ((arg1_mid_z * arg1_mid_z) +
                                         ((arg1_mid_x * arg1_mid_x) +
                                          (arg1_mid_y * arg1_mid_y))))
                                    {
                                        float scale;

                                        c3 = arg5_offset;
                                        arg4_scl = 0.0f;
                                        d1.x = arg3->x - arg2->x;
                                        d1.y = arg3->y - arg2->y;
                                        d1.z = arg3_z - arg2->z;
                                        {
                                            a2 = vec4;
                                            dot0 = (d1.z * (c3.z - a2.z)) +
                                                   ((d1.x * (c3.x - a2.x)) +
                                                    (d1.y * (c3.y - a2.y)));
                                            scale = -dot0 / ((d1.z * d1.z) +
                                                             ((d1.x * d1.x) +
                                                              (d1.y * d1.y)));
                                        }
                                        if (scale > 1.0) {
                                            scale = 1.0F;
                                        } else if (scale < 0.0) {
                                            scale = 0.0F;
                                        }
                                        arg5_scl = scale;
                                    } else {
                                        c2 = arg5_offset;
                                        arg4_scl = 1.0f;
                                        d2.x = arg3->x - arg2->x;
                                        d2.y = arg3->y - arg2->y;
                                        d2.z = arg3_z - arg2->z;
                                        {
                                            float scale;

                                            b0 = *arg1;
                                            dot1 = (d2.z * (c2.z - b0.z)) +
                                                   ((d2.x * (c2.x - b0.x)) +
                                                    (d2.y * (c2.y - b0.y)));
                                            scale = -dot1 / ((d2.z * d2.z) +
                                                             ((d2.x * d2.x) +
                                                              (d2.y * d2.y)));

                                            if (scale > 1.0) {
                                                scale = 1.0F;
                                            } else if (scale < 0.0) {
                                                scale = 0.0F;
                                            }

                                            arg5_scl = scale;
                                        }
                                    }
                                } else {
                                    arg4_scl =
                                        ((d1_dot_d2 * d2_dot_offset_delta) -
                                         (d2_len_sq * d1_dot_offset_delta)) /
                                        denom;
                                    arg5_scl =
                                        ((d1_len_sq * d2_dot_offset_delta) -
                                         (d1_dot_d2 * d1_dot_offset_delta)) /
                                        denom;
                                    if (arg4_scl > 1.0 || arg4_scl < 0.0 ||
                                        arg5_scl > 1.0 || arg5_scl < 0.0)
                                    {
                                        float candidate0_dist_sq;
                                        float candidate0_scale;
                                        float candidate1_dist_sq;

                                        if (arg4_scl < 0.0) {
                                            candidate0_scale = 0.0F;
                                            {
                                                float result = lbColl_80005EBC(
                                                    arg2, arg3, arg0,
                                                    &candidate0_arg5_scl);
                                                candidate0_dist_sq = result;
                                            }
                                        } else {
                                            candidate0_scale = 1.0F;
                                            candidate0_dist_sq =
                                                lbColl_80005EBC(
                                                    arg2, arg3, arg1,
                                                    &candidate0_arg5_scl);
                                        }

                                        {
                                            if (arg5_scl < 0.0) {
                                                arg5_scl = 0.0F;
                                                candidate1_dist_sq =
                                                    lbColl_80005EBC(
                                                        arg0, arg1, arg2,
                                                        &candidate1_arg4_scl);
                                            } else {
                                                arg5_scl = 1.0F;
                                                candidate1_dist_sq =
                                                    lbColl_80005EBC(
                                                        arg0, arg1, arg3,
                                                        &candidate1_arg4_scl);
                                            }

                                            if (candidate0_dist_sq <
                                                candidate1_dist_sq)
                                            {
                                                arg4_scl = candidate0_scale;
                                                arg5_scl = candidate0_arg5_scl;
                                            } else {
                                                arg4_scl = candidate1_arg4_scl;
                                            }
                                        }
                                    }
                                }
                            }

                            arg4->x = d1_x * arg4_scl + arg4_offset.x;
                            arg4->y = d1_y * arg4_scl + arg4_offset.y;
                            arg4->z = d1_z * arg4_scl + arg4_offset.z;

                            arg5->x = d2_x * arg5_scl + arg5_offset.x;
                            arg5->y = d2_y * arg5_scl + arg5_offset.y;
                            arg5->z = d2_z * arg5_scl + arg5_offset.z;
                        }
                    }
                    return end(arg4, arg5, unk_sum);
                }
            }
        }
    }
}

static inline float lbColl_GetY(Vec3* v)
{
    return v->y;
}

static inline float lbColl_DifferenceY(Vec3* a, Vec3* b)
{
    return a->y - b->y;
}

bool lbColl_800067F8(Vec3* a, Vec3* b, Vec3* c, Vec3* d, Vec3* e, Vec3* f,
                     float p, float q)
{
    Vec3 a1;
    Vec3 c1;
    float diff_ac_x;
    float d_y;
    float sqdist2_dc;
    float dot2_diff_ba_dc;
    float d_x;
    float sqdist2_ba;
    float dot2_diff_dc_ac;
    float dot2_diff_ba_ac;
    float determinant;
    float c1_y;
    float sum_pq = p + q;

    float distance_sq;
    Vec2 diff_ba;
    Vec2 diff_dc;
    PAD_STACK(28);

    {
        float dot0;
        float dot1;
        float out0;
        float out1;
        float dot_squared;
        float y_product;
        float diff_ac_y;
        Vec3 a2;
        Vec3 d1;
        Vec3 c3;
        Vec3 mid;
        Vec3 b0;
        Vec3 d2;
        Vec3 c2;
        Vec3 c0;
        Vec3 a0 = *a;

        (void) a0;
        a1 = a0;

        c0 = *c;
        (void) c0;

        {
            c1 = c0;
            {
                float b_x = b->x;
                if (a1.x > b_x) {
                    {
                        float x = a1.x + sum_pq;
                        if (x < c1.x && x < d->x) {
                            return false;
                        }
                    }

                    {
                        float x = b_x - sum_pq;
                        if ((x > c1.x) && (x > d->x)) {
                            return false;
                        }
                    }

                } else {
                    {
                        float x = a1.x - sum_pq;
                        if (x > c1.x && x > d->x) {
                            return false;
                        }
                    }

                    {
                        float temp_f2_4 = b_x + sum_pq;
                        if (temp_f2_4 < c1.x && temp_f2_4 < d->x) {
                            return false;
                        }
                    }
                }

                {
                    float a1_y = a1.y;
                    float b_y = b->y;
                    if (a1_y > b_y) {
                        {
                            float y = a1_y + sum_pq;
                            if (y < c1.y && y < d->y) {
                                return false;
                            }
                        }
                        {
                            float y = b_y - sum_pq;
                            if (y > c1.y && y > d->y) {
                                return false;
                            }
                        }

                    } else {
                        {
                            float y = a1_y - sum_pq;
                            if (y > c1.y && y > d->y) {
                                return false;
                            }
                        }
                        {
                            float y = b_y + sum_pq;
                            if (y < c1.y && y < d->y) {
                                return false;
                            }
                        }
                    }

                    {
                        c1_y = c1.y;
                        d_y = lbColl_GetY(d);
                        diff_ac_y = lbColl_DifferenceY(&a1, &c1);
                        d_x = d->x;

                        diff_ba.x = b_x - a1.x;
                        diff_ba.y = b_y - a1_y;
                        diff_dc.x = d_x - c1.x;
                        diff_dc.y = d_y - c1_y;

                        sqdist2_ba =
                            diff_ba.x * diff_ba.x + diff_ba.y * diff_ba.y;
                        sqdist2_dc =
                            diff_dc.x * diff_dc.x + diff_dc.y * diff_dc.y;
                        dot2_diff_ba_dc =
                            diff_ba.x * diff_dc.x + diff_ba.y * diff_dc.y;
                        diff_ac_x = a1.x - c1.x;

                        dot2_diff_dc_ac =
                            diff_dc.x * diff_ac_x + diff_dc.y * diff_ac_y;

                        {
                            y_product = diff_ba.y * diff_ac_y;
                            dot2_diff_ba_ac =
                                diff_ba.x * diff_ac_x + y_product;
                        }

                        {
                            dot_squared = dot2_diff_ba_dc * dot2_diff_ba_dc;
                            determinant =
                                sqdist2_ba * sqdist2_dc - dot_squared;
                        }

                        {
                            float scl_e;
                            float scl_f;
                            if (approximatelyZero(sqdist2_dc)) {
                                if (approximatelyZero(sqdist2_ba)) {
                                    scl_e = 0.0f;
                                    scl_f = 0.0f;
                                } else {
                                    scl_f = 0.0f;
                                    scl_e = -dot2_diff_ba_ac / sqdist2_ba;
                                    if (scl_e > 1.0) {
                                        scl_e = 1.0F;
                                    } else if (scl_e < 0.0) {
                                        scl_e = 0.0F;
                                    }
                                }
                            } else if (approximatelyZero(determinant)) {
                                float a_mid_y;
                                float b_mid_y;

                                mid.y = 0.5 * diff_dc.y + c1_y;
                                mid.x = 0.5 * diff_dc.x + c1.x;
                                a_mid_y = a1_y - mid.y;
                                b_mid_y = b_y - mid.y;
                                {
                                    float a_mid_x = a1.x - mid.x;
                                    float b_mid_x = b_x - mid.x;
                                    if ((a_mid_x * a_mid_x +
                                         a_mid_y * a_mid_y) <
                                        (b_mid_x * b_mid_x +
                                         b_mid_y * b_mid_y))
                                    {
                                        float scale;

                                        c3 = c0;
                                        scl_e = 0.0f;
                                        d1.x = d_x - c->x;
                                        d1.y = d_y - c->y;
                                        d1.z = d->z - c->z;
                                        {
                                            a2 = a0;
                                            dot0 = d1.z * (c3.z - a2.z) +
                                                   ((d1.x * (c3.x - a2.x)) +
                                                    (d1.y * (c3.y - a2.y)));
                                            scale = -dot0 / ((d1.z * d1.z) +
                                                             ((d1.x * d1.x) +
                                                              (d1.y * d1.y)));
                                        }
                                        if (scale > 1.0) {
                                            scale = 1.0F;
                                        } else if (scale < 0.0) {
                                            scale = 0.0F;
                                        }
                                        scl_f = scale;
                                    } else {
                                        c2 = c0;
                                        scl_e = 1.0f;
                                        d2.x = d_x - c->x;
                                        d2.y = d_y - c->y;
                                        d2.z = d->z - c->z;
                                        {
                                            float scale;

                                            b0 = *b;
                                            dot1 = d2.z * (c2.z - b0.z) +
                                                   ((d2.x * (c2.x - b0.x)) +
                                                    (d2.y * (c2.y - b0.y)));
                                            scale = -dot1 / ((d2.z * d2.z) +
                                                             ((d2.x * d2.x) +
                                                              (d2.y * d2.y)));
                                            if (scale > 1.0) {
                                                scale = 1.0F;
                                            } else if (scale < 0.0) {
                                                scale = 0.0F;
                                            }
                                            scl_f = scale;
                                        }
                                    }
                                }
                            } else {
                                scl_e = ((dot2_diff_ba_dc * dot2_diff_dc_ac) -
                                         (sqdist2_dc * dot2_diff_ba_ac)) /
                                        determinant;
                                scl_f = ((sqdist2_ba * dot2_diff_dc_ac) -
                                         (dot2_diff_ba_dc * dot2_diff_ba_ac)) /
                                        determinant;
                                if ((scl_e > 1.0) || (scl_e < 0.0) ||
                                    (scl_f > 1.0) || (scl_f < 0.0))
                                {
                                    float result0;
                                    float temp_scl_e;
                                    {
                                        if (scl_e < 0.0) {
                                            temp_scl_e = 0.0F;
                                            result0 = lbColl_80005FC0(c, d, a,
                                                                      &out0);
                                        } else {
                                            temp_scl_e = 1.0F;
                                            result0 = lbColl_80005FC0(c, d, b,
                                                                      &out0);
                                        }
                                    }
                                    {
                                        float result1;
                                        if (scl_f < 0.0) {
                                            scl_f = 0.0F;
                                            result1 = lbColl_80005FC0(a, b, c,
                                                                      &out1);
                                        } else {
                                            scl_f = 1.0F;
                                            result1 = lbColl_80005FC0(a, b, d,
                                                                      &out1);
                                        }

                                        if (result0 < result1) {
                                            scl_e = temp_scl_e;
                                            scl_f = out0;
                                        } else {
                                            scl_e = out1;
                                        }
                                    }
                                }
                            }

                            e->x = diff_ba.x * scl_e + a1.x;
                            e->y = diff_ba.y * scl_e + a1_y;
                            e->z = 0.0f;

                            f->x = diff_dc.x * scl_f + c1.x;
                            f->y = diff_dc.y * scl_f + c1_y;
                            f->z = 0.0f;
                        }
                    }
                }
            }
        }
    }
    {
        float x = e->x - f->x;
        float y = e->y - f->y;
        distance_sq = x * x + y * y;
        if (sum_pq * sum_pq < distance_sq) {
            return false;
        }
        return true;
    }
}

/// @brief Tests a hit capsule segment against a hurt or shield capsule
/// segment.
/// @param[in] hit_start First endpoint of the hit capsule axis.
/// @param[in] hit_end Second endpoint of the hit capsule axis.
/// @param[in] hurt_start First endpoint of the hurt/shield capsule axis.
/// @param[in] hurt_end Second endpoint of the hurt/shield capsule axis.
/// @param[out] hit_closest Closest point on the hit capsule axis.
/// @param[out] hurt_closest Closest point on the hurt/shield capsule axis.
/// @param[in] hurt_mtx Matrix used to measure hurt radius along contact
/// normal.
/// @param[out] out_contact_pos Contact point on the hurt/shield surface.
/// @param[out] out_overlap Effective radius margin minus closest distance.
/// @param[in] hit_radius Hit capsule radius.
/// @param[in] hurt_radius Hurt/shield capsule radius.
/// @param[in] broadphase_scale Scale applied to hurt_radius for AABB
/// rejection.
/// @return true if the capsule axes overlap within their effective radii.
bool lbColl_80006E58(Vec3* hit_start, Vec3* hit_end, Vec3* hurt_start,
                     Vec3* hurt_end, Vec3* hit_closest, Vec3* hurt_closest,
                     MtxPtr hurt_mtx, Vec3* out_contact_pos,
                     float* out_overlap, float hit_radius, float hurt_radius,
                     float broadphase_scale)
{
    float hit_end_min_z;
    float closest_delta_y;
    float hit_start_mid_x;
    float local_delta_x;
    float hurt_mid_z;
    Vec3 hit_start_copy;
    Vec3 hurt_start_copy;
    Vec3 hit_delta;
    u8 operand_pad[4];
    u8 frame_pad[32];
    float scaled_hurt_radius;
    float hit_start_dot;
    float hurt_mid_x;
    float hurt_mid_y;
    float hit_end_mid_y;
    float start_delta_y;
    float closest_denom;
    float projected_hit_param;
    float local_dist_sq;
    float allowed_distance;
    float hurt_closest_x;
    float hurt_closest_y;
    float hurt_end_x;
    float hit_start_mid_y;
    float hit_param_candidate;
    float closest_delta_x;
    float closest_dist_sq;
    float local_delta_y;
    float hurt_param_from_hit_start;
    float start_delta_x;
    float hurt_delta_z;
    float x_work;
    float start_delta_z;
    float hit_end_min_x;
    float hit_start_min_x;
    float hit_end_max_x;
    float hit_start_mid_z;
    float closest_delta_z;
    float local_delta_z;
    float hurt_start_dot;
    float contact_lerp;
    float broadphase_radius;
    float hit_end_mid_z;
    float y_work;
    float hit_end_min_y;
    float hit_start_min_y;
    float hit_end_max_y;
    float hurt_len_sq;
    float hit_end_max_z;
    float hit_end_x;
    float hit_len_sq;
    float hit_end_mid_x;
    float hit_start_y;
    float hit_start_max_z;
    float hit_start_min_z;
    float hurt_closest_z;
    float hit_start_z;
    float segment_dot;
    float hurt_end_y;
    float hit_param;
    float local_dist;
    float hurt_param;
    float hurt_param_from_hit_end;
    float hurt_end_z;
    f64 local_rsqrt_estimate;
    f64 local_rsqrt_step1;
    f64 local_rsqrt_step2;
    f64 closest_rsqrt_estimate;
    f64 closest_rsqrt_step1;
    f64 closest_rsqrt_step2;
    float candidate_hurt_param;
    float candidate_hit_param;
    Mtx inv_hurt_mtx;
    s32 is_hurt_segment_degenerate;
    s32 is_hit_segment_degenerate;
    s32 is_parallel;
    s32 is_zero_distance;
    float hurt_start_y;
    float hurt_start_z;
    PAD_STACK(4);

    // Fast reject when the expanded hit segment AABB misses both hurt
    // endpoints.
    broadphase_radius = (hurt_radius * broadphase_scale) + hit_radius;
    hit_start_copy = *hit_start;
    hurt_start_copy = *hurt_start;
    hit_end_x = hit_end->x;
    if (hit_start_copy.x > hit_end_x) {
        x_work = hit_start_copy.x + broadphase_radius;
        if ((x_work < hurt_start_copy.x) && (x_work < hurt_end->x)) {
            return 0;
        }
        hit_end_min_x = hit_end_x - broadphase_radius;
        if ((hit_end_min_x > hurt_start_copy.x) &&
            (hit_end_min_x > hurt_end->x))
        {
            return 0;
        }
        goto block_13;
    }
    hit_start_min_x = hit_start_copy.x - broadphase_radius;
    if ((hit_start_min_x > hurt_start_copy.x) &&
        (hit_start_min_x > hurt_end->x))
    {
        return 0;
    }
    hit_end_max_x = hit_end_x + broadphase_radius;
    if ((hit_end_max_x < hurt_start_copy.x) && (hit_end_max_x < hurt_end->x)) {
        return 0;
    }
block_13:
    hit_start_y = hit_start_copy.y;
    if (hit_start_y > hit_end->y) {
        y_work = hit_start_y + broadphase_radius;
        if ((y_work < hurt_start_copy.y) && (y_work < hurt_end->y)) {
            return 0;
        }
        hit_end_min_y = hit_end->y - broadphase_radius;
        if ((hit_end_min_y > hurt_start_copy.y) &&
            (hit_end_min_y > hurt_end->y))
        {
            return 0;
        }
        goto block_26;
    }
    hit_start_min_y = hit_start_y - broadphase_radius;
    if ((hit_start_min_y > hurt_start_copy.y) &&
        (hit_start_min_y > hurt_end->y))
    {
        return 0;
    }
    hit_end_max_y = hit_end->y + broadphase_radius;
    if ((hit_end_max_y < hurt_start_copy.y) && (hit_end_max_y < hurt_end->y)) {
        return 0;
    }
block_26:
    hit_start_z = hit_start_copy.z;
    if (hit_start_z > hit_end->z) {
        hit_start_max_z = hit_start_z + broadphase_radius;
        if ((hit_start_max_z < hurt_start_copy.z) &&
            (hit_start_max_z < hurt_end->z))
        {
            return 0;
        }
        hit_end_min_z = hit_end->z - broadphase_radius;
        if ((hit_end_min_z > hurt_start_copy.z) &&
            (hit_end_min_z > hurt_end->z))
        {
            return 0;
        }
        goto block_39;
    }
    hit_start_min_z = hit_start_z - broadphase_radius;
    if ((hit_start_min_z > hurt_start_copy.z) &&
        (hit_start_min_z > hurt_end->z))
    {
        return 0;
    }
    hit_end_max_z = hit_end->z;
    hit_end_max_z += broadphase_radius;
    if ((hit_end_max_z < hurt_start_copy.z) && (hit_end_max_z < hurt_end->z)) {
        return 0;
    }
block_39:
    // Solve closest points between the two segment axes.
    hit_delta.x = hit_end_x - hit_start_copy.x;
    hit_delta.y = hit_end->y - hit_start_copy.y;
    hit_delta.z = hit_end->z - hit_start_copy.z;
    hurt_end_y = hurt_end->y;
    start_delta_y = hurt_start_y = hurt_start_copy.y;
    hit_start_mid_y = hit_delta.y * hit_delta.y;
    y_work = hurt_end_y - hurt_start_y;
    hit_start_mid_x = hit_delta.x * hit_delta.x;
    {
        float hit_delta_z_sq = hit_delta.z * hit_delta.z;
        PAD_STACK(4);
        hit_start_mid_z = hit_delta_z_sq;
    }
    hurt_end_z = hurt_end->z;
    hurt_delta_z = hurt_end_z - (hurt_start_z = hurt_start_copy.z);
    hit_len_sq = hit_start_mid_z + (hit_start_mid_x + hit_start_mid_y);
    hurt_end_x = hurt_end->x;
    hurt_len_sq = y_work * y_work;
    x_work = hurt_end_x - (start_delta_x = hurt_start_copy.x);
    start_delta_y = hit_start_copy.y - hurt_start_y;
    hurt_len_sq = (x_work * x_work) + hurt_len_sq;
    start_delta_x = hit_start_copy.x - start_delta_x;
    (void) hurt_end_z;
    start_delta_z = hit_start_copy.z - hurt_start_z;
    (void) hurt_end_y;
    hurt_start_dot = hurt_delta_z * start_delta_z +
                     (x_work * start_delta_x + y_work * start_delta_y);
    hit_start_min_z = 1.0F;
    (void) hurt_end_x;
    segment_dot = hit_delta.z * hurt_delta_z +
                  (hit_delta.x * x_work + hit_delta.y * y_work);
    {
        PAD_STACK(4);
        hit_start_dot =
            hit_delta.z * start_delta_z +
            (hit_delta.x * start_delta_x + hit_delta.y * start_delta_y);
    }
    hurt_len_sq = (hurt_delta_z * hurt_delta_z) + hurt_len_sq;
    closest_denom = (hit_len_sq * hurt_len_sq) - (segment_dot * segment_dot);
    if ((hurt_len_sq < 1e-5F) && (hurt_len_sq > -1e-5F)) {
        is_hurt_segment_degenerate = 1;
    } else {
        is_hurt_segment_degenerate = 0;
    }
    if (is_hurt_segment_degenerate != 0) {
        if ((hit_len_sq < 1e-5F) && (hit_len_sq > -1e-5F)) {
            is_hit_segment_degenerate = 1;
        } else {
            is_hit_segment_degenerate = 0;
        }
        if (is_hit_segment_degenerate != 0) {
            hit_param = 0.0F;
            hurt_param = hit_param;
        } else {
            hurt_param = 0.0F;
            projected_hit_param = -hit_start_dot / hit_len_sq;
            hit_param = projected_hit_param;
            if (projected_hit_param > 1.0) {
                hit_param = hit_start_min_z;
            } else if (hit_param < 0.0) {
                hit_param = hurt_param;
            }
        }
    } else {
        if ((closest_denom < 1e-5F) && (closest_denom > -1e-5F)) {
            is_parallel = 1;
        } else {
            is_parallel = 0;
        }
        if (is_parallel != 0) {
            // For parallel axes, project the hit endpoint nearer the hurt
            // midpoint.
            hurt_mid_y = (float) ((0.5 * (f64) y_work) + (f64) hurt_start_y);
            hurt_mid_x =
                (float) ((0.5 * (f64) x_work) + (f64) hurt_start_copy.x);
            hit_start_mid_y = hit_start_copy.y - hurt_mid_y;
            hurt_mid_z =
                (float) ((0.5 * (f64) hurt_delta_z) + (f64) hurt_start_z);
            hit_end_mid_y = hit_end->y - hurt_mid_y;
            hit_start_mid_x = hit_start_copy.x - hurt_mid_x;
            hit_end_mid_x = hit_end->x - hurt_mid_x;
            hit_start_mid_z = hit_start_copy.z - hurt_mid_z;
            hit_end_mid_z = hit_end->z - hurt_mid_z;
            if (((hit_start_mid_z * hit_start_mid_z) +
                 ((hit_start_mid_x * hit_start_mid_x) +
                  (hit_start_mid_y * hit_start_mid_y))) <
                ((hit_end_mid_z * hit_end_mid_z) +
                 ((hit_end_mid_x * hit_end_mid_x) +
                  (hit_end_mid_y * hit_end_mid_y))))
            {
                Vec3 a2;
                Vec3 d1;
                Vec3 c3;
                PAD_STACK(4);
                c3 = *hurt_start;
                hit_param = 0.0F;
                d1.x = hurt_end_x - hurt_start->x;
                d1.y = hurt_end_y - hurt_start->y;
                d1.z = hurt_end_z - hurt_start->z;
                {
                    float dot;

                    a2 = *hit_start;
                    dot = (d1.z * (c3.z - a2.z)) +
                          ((d1.x * (c3.x - a2.x)) + (d1.y * (c3.y - a2.y)));
                    hurt_param_from_hit_start =
                        -dot /
                        ((d1.z * d1.z) + ((d1.x * d1.x) + (d1.y * d1.y)));
                }
                if (hurt_param_from_hit_start > 1.0) {
                    hurt_param_from_hit_start = hit_start_min_z;
                } else if (hurt_param_from_hit_start < 0.0) {
                    hurt_param_from_hit_start = hit_param;
                }
                hurt_param = hurt_param_from_hit_start;
            } else {
                float dot;
                Vec3 b0;
                Vec3 d1;
                Vec3 c2;
                c2 = *hurt_start;
                hit_param = hit_start_min_z;
                d1.x = hurt_end_x - hurt_start->x;
                d1.y = hurt_end_y - hurt_start->y;
                d1.z = hurt_end_z - hurt_start->z;
                {
                    b0 = *hit_end;
                    dot = (d1.z * (c2.z - b0.z)) +
                          ((d1.x * (c2.x - b0.x)) + (d1.y * (c2.y - b0.y)));
                    hurt_param_from_hit_end =
                        -dot /
                        ((d1.z * d1.z) + ((d1.x * d1.x) + (d1.y * d1.y)));
                }
                if (hurt_param_from_hit_end > 1.0) {
                    hurt_param_from_hit_end = hit_param;
                } else if (hurt_param_from_hit_end < 0.0) {
                    hurt_param_from_hit_end = 0.0F;
                }
                hurt_param = hurt_param_from_hit_end;
            }
        } else {
            hit_param =
                (hit_param_candidate = ((segment_dot * hurt_start_dot) -
                                        (hurt_len_sq * hit_start_dot)) /
                                       closest_denom);
            hurt_param = ((hurt_start_dot * hit_len_sq) -
                          (segment_dot * hit_start_dot)) /
                         closest_denom;
            if ((hit_param_candidate > 1.0) || (hit_param < 0.0) ||
                (hurt_param > 1.0) || (hurt_param < 0.0))
            {
                float hit_endpoint_dist_sq;
                float hit_endpoint_param;
                float hurt_endpoint_param;
                float hurt_endpoint_dist_sq;

                // If the unconstrained solution leaves either segment, compare
                // the nearest endpoint projection from each axis.
                if (hit_param < 0.0) {
                    hit_endpoint_param = 0.0F;
                    hit_endpoint_dist_sq =
                        lbColl_80005EBC(hurt_start, hurt_end, hit_start,
                                        &candidate_hurt_param);
                } else {
                    hit_endpoint_param = hit_start_min_z;
                    hit_endpoint_dist_sq = lbColl_80005EBC(
                        hurt_start, hurt_end, hit_end, &candidate_hurt_param);
                }
                if (hurt_param < 0.0) {
                    hurt_endpoint_param = 0.0F;
                    hurt_endpoint_dist_sq = lbColl_80005EBC(
                        hit_start, hit_end, hurt_start, &candidate_hit_param);
                } else {
                    hurt_endpoint_param = hit_start_min_z;
                    hurt_endpoint_dist_sq = lbColl_80005EBC(
                        hit_start, hit_end, hurt_end, &candidate_hit_param);
                }
                if (hit_endpoint_dist_sq < hurt_endpoint_dist_sq) {
                    hit_param = hit_endpoint_param;
                    hurt_param = candidate_hurt_param;
                } else {
                    hit_param = candidate_hit_param;
                    hurt_param = hurt_endpoint_param;
                }
            }
        }
    }
    hit_closest->x = (hit_delta.x * hit_param) + hit_start_copy.x;
    hit_closest->y = (hit_delta.y * hit_param) + hit_start_copy.y;
    hit_closest->z = (hit_delta.z * hit_param) + hit_start_copy.z;
    hurt_closest->x = (x_work * hurt_param) + hurt_start_copy.x;
    hurt_closest->y = (y_work * hurt_param) + hurt_start_y;
    hurt_closest->z = (hurt_delta_z * hurt_param) + hurt_start_z;
    closest_delta_x = hit_closest->x - hurt_closest->x;
    closest_delta_y = hit_closest->y - hurt_closest->y;
    closest_delta_z = hit_closest->z - hurt_closest->z;
    closest_dist_sq = (closest_delta_z * closest_delta_z) +
                      ((closest_delta_x * closest_delta_x) +
                       (closest_delta_y * closest_delta_y));
    if (closest_dist_sq > 0.0F) {
        volatile float sp38;

        closest_rsqrt_estimate = __frsqrte(closest_dist_sq);
        closest_rsqrt_step1 =
            0.5 * closest_rsqrt_estimate *
            -(((f64) closest_dist_sq *
               (closest_rsqrt_estimate * closest_rsqrt_estimate)) -
              3.0);
        closest_rsqrt_step2 = 0.5 * closest_rsqrt_step1 *
                              -(((f64) closest_dist_sq *
                                 (closest_rsqrt_step1 * closest_rsqrt_step1)) -
                                3.0);
        sp38 = (float) ((f64) closest_dist_sq *
                        (0.5 * closest_rsqrt_step2 *
                         -(((f64) closest_dist_sq *
                            (closest_rsqrt_step2 * closest_rsqrt_step2)) -
                           3.0)));
        x_work = sp38;
    } else {
        x_work = closest_dist_sq;
    }
    if ((x_work < 1e-5F) && (x_work > -1e-5F)) {
        is_zero_distance = 1;
    } else {
        is_zero_distance = 0;
    }
    if (is_zero_distance != 0) {
        *out_overlap = (hit_radius + hurt_radius) - x_work;
        *out_contact_pos = *hit_closest;
        return 1;
    }

    // Measure the hurt radius in the matrix's local space for scaled bones.
    HSD_MtxInverse(hurt_mtx, inv_hurt_mtx);
    PSMTXMultVec(inv_hurt_mtx, hit_closest, &hit_start_copy);
    PSMTXMultVec(inv_hurt_mtx, hurt_closest, &hit_delta);
    local_delta_x = hit_start_copy.x - hit_delta.x;
    local_delta_y = hit_start_copy.y - hit_delta.y;
    local_delta_z = hit_start_copy.z - hit_delta.z;
    local_dist_sq =
        (local_delta_z * local_delta_z) +
        ((local_delta_x * local_delta_x) + (local_delta_y * local_delta_y));
    if (local_dist_sq > 0.0F) {
        volatile float sp34;

        local_rsqrt_estimate = __frsqrte(local_dist_sq);
        {
            f64 local_rsqrt_first_step =
                0.5 * local_rsqrt_estimate *
                -(((f64) local_dist_sq *
                   (local_rsqrt_estimate * local_rsqrt_estimate)) -
                  3.0);
            local_rsqrt_step1 = local_rsqrt_first_step;
        }
        local_rsqrt_step2 =
            0.5 * local_rsqrt_step1 *
            -(((f64) local_dist_sq * (local_rsqrt_step1 * local_rsqrt_step1)) -
              3.0);
        sp34 = (float) ((f64) local_dist_sq *
                        (0.5 * local_rsqrt_step2 *
                         -(((f64) local_dist_sq *
                            (local_rsqrt_step2 * local_rsqrt_step2)) -
                           3.0)));
        local_dist = sp34;
    } else {
        local_dist = local_dist_sq;
    }
    scaled_hurt_radius = (hurt_radius * x_work) / local_dist;
    contact_lerp = scaled_hurt_radius / x_work;
    allowed_distance = hit_radius + scaled_hurt_radius;
    *out_overlap = allowed_distance - x_work;
    hurt_closest_x = hurt_closest->x;
    out_contact_pos->x =
        (contact_lerp * (hit_closest->x - hurt_closest_x)) + hurt_closest_x;
    hurt_closest_y = hurt_closest->y;
    out_contact_pos->y =
        (contact_lerp * (hit_closest->y - hurt_closest_y)) + hurt_closest_y;
    hurt_closest_z = hurt_closest->z;
    out_contact_pos->z =
        (contact_lerp * (hit_closest->z - hurt_closest_z)) + hurt_closest_z;
    if (allowed_distance < x_work) {
        return 0;
    }
    return 1;
}

static inline float sqrDistance(Vec3* a, Vec3* b)
{
    float x = a->x - b->x;
    float y = a->y - b->y;
    float z = a->z - b->z;
    return x * x + y * y + z * z;
}

static inline float sqrtf_store(float x, volatile float* y)
{
    if (x > 0.0f) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = (float) (x * guess);
        return *y;
    }
    return x;
}

void lbColl_800077A0(Vec3* a, MtxPtr arg1, Vec3* b, Vec3* c, Vec3* d, Vec3* e,
                     float* angle, float x, float dist_offset)
{
    float dot_diff_cb;
    float offset_dist;
    float scl;
    float n0;
    float ba_dot;
    float dist;
    Vec3 diff_cb;
    float n1;
    Vec3 diff_ba;
    Vec3 normalize_e;
    Vec3 normal_x;
    Vec3 multi_mtx;
    volatile float sqrt_tmp[2];

    diff_cb.x = c->x - b->x;
    diff_cb.y = c->y - b->y;
    diff_cb.z = c->z - b->z;

    if (diff_cb.x || diff_cb.y || diff_cb.z) {
        normal_x.x = x;
        normal_x.y = 0.0f;
        normal_x.z = 0.0f;
        PSMTXMultVec(arg1, &normal_x, &normal_x);

        multi_mtx.x = 0.0f;
        multi_mtx.y = 0.0f;
        multi_mtx.z = 0.0f;
        PSMTXMultVec(arg1, &multi_mtx, &multi_mtx);

        dist = sqrDistance(&normal_x, &multi_mtx);
        dist = sqrtf_store(dist, &sqrt_tmp[0]);

        offset_dist = dist + dist_offset;

        diff_ba.x = b->x - a->x;
        diff_ba.y = b->y - a->y;
        diff_ba.z = b->z - a->z;

        dot_diff_cb = diff_cb.x * diff_cb.x + diff_cb.y * diff_cb.y +
                      diff_cb.z * diff_cb.z;

        if (nearzero(dot_diff_cb)) {
            scl = 0.0f;
        } else {
            n0 = 2.0f * diff_cb.x * diff_ba.x + 2.0f * diff_cb.y * diff_ba.y +
                 2.0f * diff_cb.z * diff_ba.z;

            ba_dot = diff_ba.x * diff_ba.x + diff_ba.y * diff_ba.y +
                     diff_ba.z * diff_ba.z;

            n1 = n0 * n0 -
                 (4.0f * dot_diff_cb * -(offset_dist * offset_dist - ba_dot));

            if (n1 < 0.0f) {
                n1 = 0.0f;
            }

            // The second sqrtf spill is allocated just below the scratch
            // array.
            scl = (-n0 - sqrtf_store(n1, sqrt_tmp - 1)) / (2.0f * dot_diff_cb);
        }

        normalize_e.x = scl * diff_cb.x + b->x - a->x;
        normalize_e.y = scl * diff_cb.y + b->y - a->y;
        normalize_e.z = scl * diff_cb.z + b->z - a->z;

        PSVECNormalize(&normalize_e, e);

        *angle = lbVector_AngleXY(e, &diff_cb);
        d->x = dist * e->x + a->x;
        d->y = dist * e->y + a->y;
        d->z = dist * e->z + a->z;
    } else {
        *angle = M_PI;
        e->z = 0.0f;
        e->y = 0.0f;
        e->x = 0.0f;
    }
}

bool lbColl_80007AFC(HitCapsule* a, HitCapsule* b, float x, float y)
{
    float a_val, b_val;

    if (a->x43_b1) {
        a_val = a->scale;
    } else {
        a_val = a->scale * x;
    }

    if (b->x43_b1) {
        b_val = b->scale;
    } else {
        b_val = b->scale * y;
    }

    return lbColl_80006094(&b->x58, &b->x4C, &a->x58, &a->x4C,
                           &b->hurt_coll_pos, &a->hurt_coll_pos, b_val, a_val);
}

bool lbColl_80007B78(Mtx a, struct Fighter_x1614_t* b, float x, float y)
{
    /// @todo Eliminate casts.
    return lbColl_800067F8(&b->x14, &b->x8, (Vec3*) &a[1][1], (Vec3*) &a[0][2],
                           &b->x20, (Vec3*) &a[1][4], b->x0 * y, a[0][0] * x);
}

bool lbColl_80007BCC(HitCapsule* arg0, HitResult* shield_hit, void* arg2,
                     s32 arg3, float arg4, float arg5, float arg6)
{
    Vec3 sp74;
    Vec3 sp68;
    MtxPtr hurt_mtx;
    float hit_radius;
    Mtx sp38;

    if (!shield_hit->skip_update_pos) {
        lb_8000B1CC(shield_hit->bone, &shield_hit->offset, &shield_hit->pos);
        if (arg2 != NULL) {
            shield_hit->pos.z = arg6;
        }
        shield_hit->skip_update_pos = 1;
    }
    if (arg3 != 0) {
        arg0->hurt_coll_pos = shield_hit->pos;
        arg0->coll_distance = 0.0F;
        return 1;
    }
    if (arg2 != NULL) {
        PSMTXConcat(arg2, HSD_JObjGetMtxPtr(shield_hit->bone), sp38);
    }
    if (arg2 != NULL) {
        hurt_mtx = sp38;
    } else {
        hurt_mtx = HSD_JObjGetMtxPtr(shield_hit->bone);
    }
    if (arg0->x43_b1) {
        hit_radius = arg0->scale;
    } else {
        hit_radius = arg0->scale * arg4;
    }

    return lbColl_80006E58(&arg0->x58,           // hit_start
                           &arg0->x4C,           // hit_end
                           &shield_hit->pos,     // hurt_start
                           &shield_hit->pos,     // hurt_end
                           &sp74,                // hit_closest
                           &sp68,                // hurt_closest
                           hurt_mtx,             // hurt_mtx
                           &arg0->hurt_coll_pos, // out_contact_pos
                           &arg0->coll_distance, // out_overlap
                           hit_radius,           // hit_radius
                           shield_hit->size,     // hurt_radius
                           20.0F * arg5          // broadphase_scale
    );
}

void lbColl_80007DD8(HitCapsule* capsule, HitResult* hit, Mtx hit_transform,
                     Vec3* /*out*/ arg3, float* angle, float scale)
{
    float dist_offset;
    Vec3 unused_result;
    Mtx transformed_hit;

    if (hit_transform != NULL) {
        PSMTXConcat(hit_transform, HSD_JObjGetMtxPtr(hit->bone),
                    transformed_hit);
    }
    if (capsule->x43_b1) {
        dist_offset = capsule->scale;
    } else {
        dist_offset = capsule->scale * scale;
    }
    lbColl_800077A0(&hit->pos,
                    hit_transform != NULL ? transformed_hit
                                          : HSD_JObjGetMtxPtr(hit->bone),
                    &capsule->x58, &capsule->x4C, &unused_result, arg3, angle,
                    hit->size, dist_offset);
}

bool lbColl_80007ECC(HitCapsule* arg0, HurtCapsule* arg1, Mtx arg2,
                     float hit_scl_y, float hurt_scl_y, float hurt_pos_z)
{
    Vec3 sp70;
    Vec3 sp64;
    Mtx sp34;
    float hit_radius;
    MtxPtr hurt_mtx;

    if (arg1->state == HurtCapsule_Enabled) {
        if (!arg1->skip_update_pos) {
            lb_8000B1CC(arg1->bone, &arg1->a_offset, &arg1->a_pos);
            lb_8000B1CC(arg1->bone, &arg1->b_offset, &arg1->b_pos);
            if (arg2 != NULL) {
                arg1->b_pos.z = hurt_pos_z;
                arg1->a_pos.z = hurt_pos_z;
            }
            arg1->skip_update_pos = 1;
        }
        if (arg2 != NULL) {
            PSMTXConcat(arg2, HSD_JObjGetMtxPtr(arg1->bone), sp34);
        }
        if (arg2 != NULL) {
            hurt_mtx = sp34;
        } else {
            hurt_mtx = HSD_JObjGetMtxPtr(arg1->bone);
        }
        if (arg0->x43_b1) {
            hit_radius = arg0->scale;
        } else {
            hit_radius = arg0->scale * hit_scl_y;
        }
        return lbColl_80006E58(&arg0->x58, &arg0->x4C, &arg1->a_pos,
                               &arg1->b_pos, &sp70, &sp64, hurt_mtx,
                               &arg0->hurt_coll_pos, &arg0->coll_distance,
                               hit_radius, arg1->scale, 3.0F * hurt_scl_y);
    }
    return 0;
}

bool lbColl_8000805C(HitCapsule* arg0, HurtCapsule* arg1, Mtx arg2, s32 arg3,
                     float arg4, float arg5, float arg6)
{
    Vec3 sp74;
    Vec3 sp68;
    Mtx sp38;
    MtxPtr var_r9;
    float hit_radius;

    if (arg1->state != HurtCapsule_Intangible) {
        if (!arg1->skip_update_pos) {
            lb_8000B1CC(arg1->bone, &arg1->a_offset, &arg1->a_pos);
            lb_8000B1CC(arg1->bone, &arg1->b_offset, &arg1->b_pos);
            if (arg2 != NULL) {
                arg1->b_pos.z = arg6;
                arg1->a_pos.z = arg6;
            }
            arg1->skip_update_pos = 1;
        }
        if (arg3 != 0) {
            arg0->hurt_coll_pos.x = 0.5F * (arg1->a_pos.x + arg1->b_pos.x);
            arg0->hurt_coll_pos.y = 0.5F * (arg1->a_pos.y + arg1->b_pos.y);
            arg0->hurt_coll_pos.z = 0.5F * (arg1->a_pos.z + arg1->b_pos.z);
            arg0->coll_distance = 5.0f;
            return 1;
        }
        if (arg2 != NULL) {
            PSMTXConcat(arg2, HSD_JObjGetMtxPtr(arg1->bone), sp38);
        }
        if (arg2 != NULL) {
            var_r9 = sp38;
        } else {
            var_r9 = HSD_JObjGetMtxPtr(arg1->bone);
        }
        if (arg0->x43_b1) {
            hit_radius = arg0->scale;
        } else {
            hit_radius = arg0->scale * arg4;
        }

        return lbColl_80006E58(&arg0->x58, &arg0->x4C, &arg1->a_pos,
                               &arg1->b_pos, &sp74, &sp68, var_r9,
                               &arg0->hurt_coll_pos, &arg0->coll_distance,
                               hit_radius, arg1->scale, 3.0F * arg5);
    }
    return 0;
}

bool lbColl_80008248(HitCapsule* arg0, HurtCapsule* arg1, Mtx arg2, f32 arg3,
                     f32 arg4, f32 arg5)
{
    f32 var_f1;
    Vec3 sp70;
    Vec3 sp64;
    Mtx sp34;
    MtxPtr var_r9;

    if (!arg1->skip_update_pos) {
        lb_8000B1CC(arg1->bone, &arg1->a_offset, &arg1->a_pos);
        lb_8000B1CC(arg1->bone, &arg1->b_offset, &arg1->b_pos);
        if (arg2 != NULL) {
            arg1->b_pos.z = arg5;
            arg1->a_pos.z = arg5;
        }
        arg1->skip_update_pos = 1;
    }
    if (arg2 != NULL) {
        PSMTXConcat(arg2, HSD_JObjGetMtxPtr(arg1->bone), sp34);
    }
    if (arg2 != NULL) {
        var_r9 = sp34;
    } else {
        var_r9 = HSD_JObjGetMtxPtr(arg1->bone);
    }
    if (arg0->x43_b1) {
        var_f1 = arg0->scale;
    } else {
        var_f1 = arg0->scale * arg3;
    }
    return lbColl_80006E58(&arg0->x58, &arg0->x4C, &arg1->a_pos, &arg1->b_pos,
                           &sp70, &sp64, var_r9, &arg0->hurt_coll_pos,
                           &arg0->coll_distance, var_f1, arg1->scale,
                           3.0f * arg4);
}

void lbColl_800083C4(HurtCapsule* arg0)
{
    if (arg0->skip_update_pos) {
        return;
    }

    lb_8000B1CC(arg0->bone, &arg0->a_offset, &arg0->a_pos);
    lb_8000B1CC(arg0->bone, &arg0->b_offset, &arg0->b_pos);
    arg0->skip_update_pos = true;
}

void lbColl_80008428(HitCapsule* arg0)
{
    arg0->state = HitCapsule_Disabled;
}

void lbColl_80008434(HitCapsule* arg0)
{
    arg0->state = HitCapsule_Enabled;
}

void lbColl_80008440(HitCapsule* hit)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(hit->victims_1); i++) {
        hit->victims_1[i].victim = NULL;
    }
    hit->x44 = 0;
    for (i = 0; i < ARRAY_SIZE(hit->victims_2); i++) {
        hit->victims_2[i].victim = NULL;
    }
    hit->x45 = 0;
}

void lbColl_CopyHitCapsule(HitCapsule* src, HitCapsule* dst)
{
    HitVictim* sv1 = src->victims_1;
    HitVictim* dv1 = dst->victims_1;
    HitVictim* sv2 = src->victims_2;
    HitVictim* dv2 = dst->victims_2;
    size_t i;
    for (i = 0; i < ARRAY_SIZE(src->victims_1); i++) {
        dv1[i] = sv1[i];
        dv2[i] = sv2[i];
    }
    dst->x44 = src->x44;
    dst->x45 = src->x45;
}

bool lbColl_80008688(HitCapsule* capsule, int type, void* victim)
{
    int var_r0;
    int i;

    for (i = 0; i < ARRAY_SIZE(capsule->victims_1); i++) {
        if (capsule->victims_1[i].victim == victim) {
            switch (type) {
            case 2:
            case 4:
            case 5:
            case 7:
            case 8:
                capsule->victims_1[i].x4 = capsule->x40_b4;
            }
            return false;
        }
    }

    for (i = 0; i < ARRAY_SIZE(capsule->victims_1); i++) {
        if (capsule->victims_1[i].victim == NULL) {
            break;
        }
    }

    if (i == ARRAY_SIZE(capsule->victims_1)) {
        var_r0 = capsule->x44;
    } else {
        var_r0 = i;
    }

    capsule->victims_1[var_r0].victim = victim;

    switch (type) {
    case 2:
    case 4:
    case 5:
    case 7:
    case 8:
        capsule->victims_1[var_r0].x4 = capsule->x40_b4;
        break;
    default:
        capsule->victims_1[var_r0].x4 = 0;
        break;
    }

    if (i == ARRAY_SIZE(capsule->victims_1)) {
        capsule->x44 += 1;
        if (capsule->x44 >= 0xC) {
            capsule->x44 = 0;
        }
    }
    return true;
}

bool lbColl_80008820(HitCapsule* capsule, int type, void* victim)
{
    int var_r0;
    int i;

    for (i = 0; i < ARRAY_SIZE(capsule->victims_2); i++) {
        if (capsule->victims_2[i].victim == victim) {
            switch (type) {
            case 2:
            case 5:
            case 7:
            case 8:
                capsule->victims_2[i].x4 = capsule->x40_b4;
            }
            return false;
        }
    }

    for (i = 0; i < ARRAY_SIZE(capsule->victims_2); i++) {
        if (capsule->victims_2[i].victim == NULL) {
            break;
        }
    }

    if (i == ARRAY_SIZE(capsule->victims_2)) {
        var_r0 = capsule->x45;
    } else {
        var_r0 = i;
    }

    capsule->victims_2[var_r0].victim = victim;

    switch (type) {
    case 2:
    case 5:
    case 7:
    case 8:
        capsule->victims_2[var_r0].x4 = capsule->x40_b4;
        break;
    default:
        capsule->victims_2[var_r0].x4 = 0;
        break;
    }

    if (i == ARRAY_SIZE(capsule->victims_2)) {
        capsule->x45 += 1;
        if (capsule->x45 >= ARRAY_SIZE(capsule->victims_2)) {
            capsule->x45 = 0;
        }
    }
    return true;
}

void lbColl_800089B8(HitCapsule* hit, UNK_T arg1)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(hit->victims_1); i++) {
        if (hit->victims_1[i].victim == arg1) {
            hit->victims_1[i].victim = 0;
        }
    }
}

void lbColl_80008A5C(HitCapsule* hit)
{
    if (hit->state != HitCapsule_Disabled) {
        size_t i;
        for (i = 0; i < ARRAY_SIZE(hit->victims_1); i++) {
            if (hit->victims_1[i].victim != NULL) {
                u32 temp_r4 = hit->victims_1[i].x4;
                if (temp_r4 != 0) {
                    hit->victims_1[i].x4 = temp_r4 - 1;
                    if (hit->victims_1[i].x4 == 0) {
                        hit->victims_1[i].victim = NULL;
                    }
                }
            }
        }
        for (i = 0; i < ARRAY_SIZE(hit->victims_2); i++) {
            if (hit->victims_2[i].victim != 0) {
                u32 temp_r4 = hit->victims_2[i].x4;
                if (temp_r4 != 0) {
                    hit->victims_2[i].x4 = temp_r4 - 1;
                    if (hit->victims_2[i].x4 == 0) {
                        hit->victims_2[i].victim = NULL;
                    }
                }
            }
        }
    }
}

void lbColl_80008D30(HitCapsule* arg0, lbColl_80008D30_arg1* arg1)
{
    arg0->state = arg1->state;
    arg0->damage = arg1->damage;
    arg0->kb_angle = arg1->kb_angle;
    arg0->x24 = arg1->unkC;
    arg0->x28 = arg1->unk10;
    arg0->x2C = arg1->unk14;
    arg0->element = arg1->element;
    arg0->sfx_severity = arg1->sfx_severity;
    arg0->sfx_kind = arg1->sfx_kind;
    arg0->unk_count = arg1->damage;
}

GXColor const lbColl_804D7A50 = { 0 };

void lbColl_80008DA4(GXColor* arg0, GXColor* arg1)
{
    GXColor sp10;
    GXBlendMode var_r3;
    u8 var_r5;

    sp10 = lbColl_804D7A50;
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_DISABLE);
    GXSetFog(GX_FOG_NONE, 0.0F, 0.0F, 0.0F, 0.0F, sp10);
    if (arg0->a < 0xFF) {
        var_r3 = GX_BM_BLEND;
    } else {
        var_r3 = GX_BM_NONE;
    }
    GXSetBlendMode(var_r3, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    if (arg0->a < 0xFF) {
        var_r5 = 0;
    } else {
        var_r5 = 1;
    }
    GXSetZMode(1, GX_LEQUAL, var_r5);
    GXSetZCompLoc(0);
    GXSetNumTexGens(0);
    GXSetTevClampMode(0, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColor(GX_TEVREG0, *arg0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C0,
                    GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    GXSetNumChans(1);
    sp10 = *arg1;
    GXSetChanAmbColor(GX_COLOR0A0, sp10);
    sp10.r = 0xFF;
    sp10.g = 0xFF;
    sp10.b = 0xFF;
    sp10.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, sp10);
    if (arg0->a < 0xFF) {
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_NONE,
                      GX_AF_NONE);
    } else {
        GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP,
                      GX_AF_NONE);
    }
}

static inline bool isSmall(float x)
{
    if (x < 0.00001F && x > -0.00001F) {
        return true;
    } else {
        return false;
    }
}

void lbColl_80008FC8(Vec3 arg0, Vec3 arg1, GXColor* arg2, GXColor* arg3,
                     f32 arg4)
{
    Mtx sp104;
    Mtx spD4;
    Mtx spA4;
    Mtx sp74;
    Mtx sp44;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;

    f32 var_f31;

    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    lbColl_80008DA4(arg2, arg3);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp104);
    PSMTXScale(spA4, arg4, arg4, arg4);
    sp38.x = arg0.x - arg1.x;
    sp38.y = arg0.y - arg1.y;
    sp38.z = arg0.z - arg1.z;
    var_f31 = sqrtf(SQ(sp38.x) + SQ(sp38.y) + SQ(sp38.z));
    if (isSmall(var_f31) ||
        (isSmall(sp38.x) && isSmall(sp38.y) && isSmall(sp38.z)))
    {
        PSMTXIdentity(sp44);
        sp44[0][0] = -1.0F;
        sp44[1][0] = 0.0F;
        sp44[2][0] = 0.0F;
        sp44[0][1] = 0.0F;
        sp44[1][1] = 1.0F;
        sp44[2][1] = 0.0F;
        sp44[0][2] = 0.0F;
        sp44[1][2] = 0.0F;
        sp44[2][2] = -1.0F;
        PSMTXConcat(sp44, spA4, spD4);
    } else {
        PSMTXScale(sp74, var_f31, arg4, arg4);
        if (isSmall(sp38.x) && isSmall(sp38.y)) {
            sp2C.x = sp38.z;
            sp2C.y = 0.0f;
            sp2C.z = 0.0f;
        } else {
            sp2C.x = sp38.y;
            sp2C.y = -sp38.x;
            sp2C.z = 0.0f;
        }
        PSVECNormalize(&sp38, &sp38);
        PSVECNormalize(&sp2C, &sp2C);
        PSVECCrossProduct(&sp38, &sp2C, &sp20);
        PSMTXIdentity(sp44);
        sp44[0][0] = sp38.x;
        sp44[1][0] = sp38.y;
        sp44[2][0] = sp38.z;
        sp44[0][1] = sp2C.x;
        sp44[1][1] = sp2C.y;
        sp44[2][1] = sp2C.z;
        sp44[0][2] = sp20.x;
        sp44[1][2] = sp20.y;
        sp44[2][2] = sp20.z;
        PSMTXConcat(sp44, spA4, spD4);
        PSMTXConcat(sp44, sp74, sp74);
        sp44[0][0] = -sp38.x;
        sp44[1][0] = -sp38.y;
        sp44[2][0] = -sp38.z;
        sp44[0][1] = sp2C.x;
        sp44[1][1] = sp2C.y;
        sp44[2][1] = sp2C.z;
        sp44[0][2] = -sp20.x;
        sp44[1][2] = -sp20.y;
        sp44[2][2] = -sp20.z;
        PSMTXConcat(sp44, spA4, spA4);
    }
    PSMTXTrans(sp44, arg0.x, arg0.y, arg0.z);
    PSMTXConcat(sp44, spD4, spD4);
    PSMTXTrans(sp44, arg1.x, arg1.y, arg1.z);
    PSMTXConcat(sp44, spA4, spA4);
    PSMTXTrans(sp44, 0.5 * (arg0.x + arg1.x), 0.5 * (arg0.y + arg1.y),
               0.5 * (arg0.z + arg1.z));
    PSMTXConcat(sp44, sp74, sp74);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetArray(GX_VA_POS, lbColl_SpherePositions, 6);
    GXSetArray(GX_VA_NRM, lbColl_SphereNormals, 6);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 0xE);
    PSMTXConcat(sp104, spD4, spD4);
    GXLoadPosMtxImm(spD4, 0);
    HSD_MtxInverse(spD4, spD4);
    PSMTXTranspose(spD4, spD4);
    GXLoadNrmMtxImm(spD4, 0);
    GXCallDisplayList(lbColl_SphereDisplayList, 0x120);
    GXClearVtxDesc();
    GXSetArray(GX_VA_POS, lbColl_SpherePositions, 6);
    GXSetArray(GX_VA_NRM, lbColl_SphereNormals, 6);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 0xE);
    PSMTXConcat(sp104, spA4, spA4);
    GXLoadPosMtxImm(spA4, 0);
    HSD_MtxInverse(spA4, spA4);
    PSMTXTranspose(spA4, spA4);
    GXLoadNrmMtxImm(spA4, 0);
    GXCallDisplayList(lbColl_SphereDisplayList, 0x120);
    if (!isSmall(var_f31)) {
        GXClearVtxDesc();
        GXSetArray(GX_VA_POS, lbColl_CylinderPositions, 6);
        GXSetArray(GX_VA_NRM, lbColl_CylinderNormals, 6);
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 6);
        PSMTXConcat(sp104, sp74, sp74);
        GXLoadPosMtxImm(sp74, 0);
        HSD_MtxInverse(sp74, sp74);
        PSMTXTranspose(sp74, sp74);
        GXLoadNrmMtxImm(sp74, 0);
        GXCallDisplayList(lbColl_CylinderDisplayList, 0xA0);
    }
    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
}

void lbColl_800096B4(MtxPtr arg0, Vec3 arg1, Vec3 arg2, GXColor* arg3,
                     GXColor* arg4, f32 arg5)
{
    Mtx sp108;
    Mtx spD8;
    Mtx spA8;
    Mtx sp78;
    Mtx sp48;
    Vec3 sp3C;
    Vec3 sp30;
    Vec3 sp24;
    f32 var_f31;

    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    lbColl_80008DA4(arg3, arg4);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp108);
    PSMTXScale(spA8, arg5, arg5, arg5);
    sp3C.x = arg1.x - arg2.x;
    sp3C.y = arg1.y - arg2.y;
    sp3C.z = arg1.z - arg2.z;
    var_f31 = sqrtf(SQ(sp3C.x) + SQ(sp3C.y) + SQ(sp3C.z));
    if (isSmall(var_f31) ||
        (isSmall(sp3C.x) && isSmall(sp3C.y) && isSmall(sp3C.z)))
    {
        PSMTXIdentity(sp48);
        sp48[0][0] = -1.0F;
        sp48[1][0] = 0.0F;
        sp48[2][0] = 0.0F;
        sp48[0][1] = 0.0F;
        sp48[1][1] = 1.0F;
        sp48[2][1] = 0.0F;
        sp48[0][2] = 0.0F;
        sp48[1][2] = 0.0F;
        sp48[2][2] = -1.0F;
        PSMTXConcat(sp48, spA8, spD8);
    } else {
        PSMTXScale(sp78, var_f31, arg5, arg5);
        if (isSmall(sp3C.x) && isSmall(sp3C.y)) {
            sp30.x = sp3C.z;
            sp30.y = 0.0F;
            sp30.z = 0.0F;
        } else {
            sp30.x = sp3C.y;
            sp30.y = -sp3C.x;
            sp30.z = 0.0F;
        }
        PSVECNormalize(&sp3C, &sp3C);
        PSVECNormalize(&sp30, &sp30);
        PSVECCrossProduct(&sp3C, &sp30, &sp24);
        PSMTXIdentity(sp48);
        sp48[0][0] = sp3C.x;
        sp48[1][0] = sp3C.y;
        sp48[2][0] = sp3C.z;
        sp48[0][1] = sp30.x;
        sp48[1][1] = sp30.y;
        sp48[2][1] = sp30.z;
        sp48[0][2] = sp24.x;
        sp48[1][2] = sp24.y;
        sp48[2][2] = sp24.z;
        PSMTXConcat(sp48, spA8, spD8);
        PSMTXConcat(sp48, sp78, sp78);
        sp48[0][0] = -sp3C.x;
        sp48[1][0] = -sp3C.y;
        sp48[2][0] = -sp3C.z;
        sp48[0][1] = sp30.x;
        sp48[1][1] = sp30.y;
        sp48[2][1] = sp30.z;
        sp48[0][2] = -sp24.x;
        sp48[1][2] = -sp24.y;
        sp48[2][2] = -sp24.z;
        PSMTXConcat(sp48, spA8, spA8);
    }
    PSMTXTrans(sp48, arg1.x, arg1.y, arg1.z);
    PSMTXConcat(sp48, spD8, spD8);
    PSMTXTrans(sp48, arg2.x, arg2.y, arg2.z);
    PSMTXConcat(sp48, spA8, spA8);
    PSMTXTrans(sp48, 0.5 * (arg1.x + arg2.x), 0.5 * (arg1.y + arg2.y),
               0.5 * (arg1.z + arg2.z));
    PSMTXConcat(sp48, sp78, sp78);
    PSMTXConcat(arg0, spD8, spD8);
    PSMTXConcat(arg0, spA8, spA8);
    PSMTXConcat(arg0, sp78, sp78);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetArray(GX_VA_POS, lbColl_SpherePositions, 6);
    GXSetArray(GX_VA_NRM, lbColl_SphereNormals, 6);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 0xE);
    PSMTXConcat(sp108, spD8, spD8);
    GXLoadPosMtxImm(spD8, 0);
    HSD_MtxInverse(spD8, spD8);
    PSMTXTranspose(spD8, spD8);
    GXLoadNrmMtxImm(spD8, 0);
    GXCallDisplayList(lbColl_SphereDisplayList, 0x120);
    GXClearVtxDesc();
    GXSetArray(GX_VA_POS, lbColl_SpherePositions, 6);
    GXSetArray(GX_VA_NRM, lbColl_SphereNormals, 6);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 0xE);
    PSMTXConcat(sp108, spA8, spA8);
    GXLoadPosMtxImm(spA8, 0);
    HSD_MtxInverse(spA8, spA8);
    PSMTXTranspose(spA8, spA8);
    GXLoadNrmMtxImm(spA8, 0);
    GXCallDisplayList(lbColl_SphereDisplayList, 0x120);
    if (!isSmall(var_f31)) {
        GXClearVtxDesc();
        GXSetArray(GX_VA_POS, lbColl_CylinderPositions, 6);
        GXSetArray(GX_VA_NRM, lbColl_CylinderNormals, 6);
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 6);
        PSMTXConcat(sp108, sp78, sp78);
        GXLoadPosMtxImm(sp78, 0);
        HSD_MtxInverse(sp78, sp78);
        PSMTXTranspose(sp78, sp78);
        GXLoadNrmMtxImm(sp78, 0);
        GXCallDisplayList(lbColl_CylinderDisplayList, 0xA0);
    }
    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
}

void lbColl_80009DD4(Vec3* v0, Vec3* v1, GXColor* clr)
{
    Mtx viewMtx;
    float x1, x0, y0, z0, y1;
    u8 r, g, b, a;

    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    PAD_STACK(32);
    lbColl_80008DA4(clr, clr);
    HSD_ClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetCurrentMtx(0);
    GXSetCullMode(GX_CULL_NONE);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), viewMtx);
    GXLoadPosMtxImm(viewMtx, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    z0 = v0->z;
    y0 = v0->y;
    x0 = v0->x;
    GXPosition3f32(x0, y0, z0);
    a = clr->a;
    b = clr->b;
    g = clr->g;
    r = clr->r;
    GXColor4u8(r, g, b, a);

    x1 = v1->x;
    GXPosition3f32(x1, y0, z0);
    GXColor4u8(r, g, b, a);

    y1 = v1->y;
    GXPosition3f32(x1, y1, z0);
    GXColor4u8(r, g, b, a);

    GXPosition3f32(x0, y1, z0);
    GXColor4u8(r, g, b, a);

    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
}

bool lbColl_80009F54(HitCapsule* hit, u32 arg1, float arg8)
{
    GXColor* var_r5;
    float var_f1;
    u32 var_r0;

    if (hit->state != HitCapsule_Disabled && !hit->x43_b2) {
        switch (hit->element) {
        case HitElement_Catch:
            var_r5 = &lbColl_804D36A4;
            break;
        case HitElement_Inert:
            var_r5 = &lbColl_804D36DC;
            break;
        default:
            var_r5 = &lbColl_804D36A0;
            break;
        }

        if (var_r5->a == 0xFF) {
            var_r0 = 0;
        } else {
            var_r0 = 2;
        }
        if (var_r0 == arg1) {
            if (hit->x43_b1) {
                var_f1 = hit->scale;
            } else {
                var_f1 = hit->scale * arg8;
            }
            lbColl_80008FC8(hit->x58, hit->x4C, var_r5, &lbColl_804D36A8,
                            var_f1);
            return 1;
        }
    }
    return 0;
}

static inline void lbColl_DrawHitResult(MtxPtr mtx, Vec3* a, Vec3* b,
                                        GXColor* c0, GXColor* c1, f32 size)
{
    Vec3 sp30;
    Vec3 sp24;
    Mtx sp3C;

    HSD_MtxInverse(mtx, sp3C);
    PSMTXMultVec(sp3C, a, &sp30);
    PSMTXMultVec(sp3C, b, &sp24);
    lbColl_800096B4(mtx, sp30, sp24, c0, c1, size);
}

bool lbColl_8000A044(HitCapsule* hit, u32 arg1, float arg8)
{
    float var_f1;
    u32 var_r0;

    if (hit->state != HitCapsule_Disabled && !hit->x43_b2) {
        if (lbColl_804D36E8.a == 0xFF) {
            var_r0 = 0;
        } else {
            var_r0 = 2;
        }
        if (var_r0 == arg1) {
            if (hit->x43_b1) {
                var_f1 = hit->scale;
            } else {
                var_f1 = hit->scale * arg8;
            }
            lbColl_80008FC8(hit->x58, hit->x4C, &lbColl_804D36E8,
                            &lbColl_804D36EC, var_f1);
            return 1;
        }
    }
    return 0;
}

bool lbColl_8000A244(HurtCapsule* hurt, u32 arg1, Mtx arg2, float arg3)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;
    float temp_f31;
    MtxPtr var_r28;
    GXColor* temp_r31_2;
    u32 var_r0;
    GXColor* temp_r3;

    temp_r3 = lbColl_803B9928[hurt->state].pad;
    if (temp_r3->a == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        if (!hurt->skip_update_pos) {
            lb_8000B1CC(hurt->bone, &hurt->a_offset, &hurt->a_pos);
            lb_8000B1CC(hurt->bone, &hurt->b_offset, &hurt->b_pos);
            if (arg2 != NULL) {
                hurt->b_pos.z = arg3;
                hurt->a_pos.z = arg3;
            }
            hurt->skip_update_pos = 1;
        }
        if (arg2 != NULL) {
            PSMTXConcat(arg2, HSD_JObjGetMtxPtr(hurt->bone), sp9C);
        }
        temp_f31 = hurt->scale;
        temp_r31_2 = lbColl_803B9928[hurt->state].pad_x;
        sp84 = hurt->b_pos;
        sp90 = hurt->a_pos;
        if (arg2 != NULL) {
            var_r28 = sp9C;
        } else {
            var_r28 = HSD_JObjGetMtxPtr(hurt->bone);
        }
        lbColl_DrawHitResult(var_r28, &sp90, &sp84, temp_r3, temp_r31_2,
                             temp_f31);
        return true;
    }
    return false;
}

bool lbColl_8000A10C(struct lbColl_8000A10C_arg0_t* arg0, u32 arg1, f32 arg2)
{
    GXColor* c = &lbColl_804D36F8;
    u32 var_r0;
    if (c->a == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        lbColl_80008FC8(arg0->x14, arg0->x8, c, &lbColl_804D36FC,
                        arg0->x0 * arg2);
        return true;
    }
    return false;
}

bool lbColl_8000A1A8(struct Fighter_x1614_t* arg0, int arg1, f32 scale_y)
{
    u32 var_r0;

    if (lbColl_804D36F0.a == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        lbColl_80008FC8(arg0->x14, arg0->x8, &lbColl_804D36F0,
                        &lbColl_804D36F4, arg0->x0 * scale_y);
        return true;
    }
    return false;
}

bool lbColl_8000A460(Fighter_x1670_t* hurt, u32 arg1)
{
    u32 var_r0;

    GXColor* r31 = &lbColl_804D36E0;
    GXColor* r30 = &lbColl_804D36E4;

    if (r31->a == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        HSD_JObjSetupMatrix(hurt->jobj);
        lbColl_800096B4(HSD_JObjGetMtxPtr(hurt->jobj), hurt->v1, hurt->v1, r31,
                        r30, hurt->v2);
        return true;
    }
    return false;
}

bool lbColl_8000A584(HurtCapsule* hurt, u32 arg1, u32 arg2, Mtx arg3, f32 arg8)
{
    PAD_STACK(4);
    {
        Mtx spA0;
        Vec3 sp94;
        Vec3 sp88;
        f32 temp_f31;
        GXColor* temp_r31_2;
        u32 var_r0;
        u32 var_r4;
        GXColor* temp_r3;

        var_r4 = arg1;
        if (hurt->state == HurtCapsule_Intangible) {
            var_r4 = 2;
        }
        temp_r3 = lbColl_803B9928[var_r4].pad;
        if (temp_r3->a == 0xFF) {
            var_r0 = 0;
        } else {
            var_r0 = 2;
        }
        if (var_r0 == arg2) {
            if (!hurt->skip_update_pos) {
                lb_8000B1CC(hurt->bone, &hurt->a_offset, &hurt->a_pos);
                lb_8000B1CC(hurt->bone, &hurt->b_offset, &hurt->b_pos);
                if (arg3 != NULL) {
                    hurt->b_pos.z = arg8;
                    hurt->a_pos.z = arg8;
                }
                hurt->skip_update_pos = 1;
            }
            if (arg3 != NULL) {
                PSMTXConcat(arg3, HSD_JObjGetMtxPtr(hurt->bone), spA0);
            }
            temp_f31 = hurt->scale;
            temp_r31_2 = lbColl_803B9928[var_r4].pad_x;
            sp88 = hurt->b_pos;
            sp94 = hurt->a_pos;
            if (arg3 != NULL) {
                hurt = (HurtCapsule*) spA0;
            } else {
                hurt = (HurtCapsule*) HSD_JObjGetMtxPtr(hurt->bone);
            }
            lbColl_DrawHitResult((MtxPtr) hurt, &sp94, &sp88, temp_r3,
                                 temp_r31_2, temp_f31);
            return true;
        }
        return false;
    }
}

static inline bool lbColl_DrawHit(HitResult* hit, u32 arg1, MtxPtr arg2,
                                  f32 pos_z, GXColor* color,
                                  GXColor* secondary_color, MtxPtr hit_mtx,
                                  Vec3* pos_a, Vec3* pos_b)
{
    f32 temp_f31;
    MtxPtr var_r31;
    u32 var_r0;

    if (color->a == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        if (!hit->skip_update_pos) {
            lb_8000B1CC(hit->bone, &hit->offset, &hit->pos);
            if (arg2 != NULL) {
                hit->pos.z = pos_z;
            }
            hit->skip_update_pos = true;
        }
        if (arg2 != NULL) {
            PSMTXConcat(arg2, HSD_JObjGetMtxPtr(hit->bone), hit_mtx);
        }
        temp_f31 = hit->size;
        *pos_b = hit->pos;
        *pos_a = hit->pos;
        if (arg2 != NULL) {
            var_r31 = hit_mtx;
        } else {
            var_r31 = HSD_JObjGetMtxPtr(hit->bone);
        }
        lbColl_DrawHitResult(var_r31, pos_a, pos_b, color, secondary_color,
                             temp_f31);
        return true;
    }
    return false;
}

bool lbColl_8000A78C(HitResult* hit, u32 arg1, Mtx arg2, f32 pos_z)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;

    return lbColl_DrawHit(hit, arg1, arg2, pos_z, &lbColl_804D36C4,
                          &lbColl_804D36C8, sp9C, &sp90, &sp84);
}

bool lbColl_8000A95C(HitResult* hit, u32 arg1, Mtx arg2, f32 pos_z)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;

    return lbColl_DrawHit(hit, arg1, arg2, pos_z, &lbColl_804D36CC,
                          &lbColl_804D36D0, sp9C, &sp90, &sp84);
}

bool lbColl_8000AB2C(HitResult* hit, u32 arg1, MtxPtr arg2, f32 pos_z)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;

    return lbColl_DrawHit(hit, arg1, arg2, pos_z, &lbColl_804D36D4,
                          &lbColl_804D36D8, sp9C, &sp90, &sp84);
}

bool lbColl_8000ACFC(UNK_T victim, HitCapsule* hitbox)
{
    HitVictim* victims = hitbox->victims_1;
    size_t const count = ARRAY_SIZE(hitbox->victims_1);
    size_t i;

    for (i = 0; i < count; i++) {
        if (victims[i].victim == victim) {
            break;
        }
    }

    return i == count ? false : true;
}
