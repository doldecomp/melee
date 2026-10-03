/**
 * @file
 * @copydoc melee/mp/mplib.h
 */

#include "mplib.h"

#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <math.h>
#include <placeholder.h>
#include <stdbool.h>
#include <stddef.h>

#include "forward.h"
#include "mpcoll.h"
#include "mpisland.h"
#include "types.h"
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>
#include <melee/cm/camera.h>
#include <melee/cm/types.h>
#include <melee/db/db.h>
#include <melee/ft/ftlib.h>
#include <melee/gr/grdynamicattr.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/itCharItems.h>
#include <melee/lb/types.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/texp.h>

#define LINEID_CHECK(line, line_id)                                           \
    do {                                                                      \
        if ((line_id) == -1 || (line_id) >= mpLib_804D64B4->line_count)       \
            HSD_ASSERTREPORT(line, 0, "%s:%d:not found lineID=%d\n",          \
                             __FILE__, line, line_id);                                   \
    } while (0)

struct mpLib_803BF248_t_x4 {
    float x0;
    int x4[4];
    int x14[3];
    int x20[4];
    int x30[3];
    int x3C[4];
    int x4C[3];
};

struct mpLib_803BF248_t {
    GrKind id;
    struct mpLib_803BF248_t_x4* (*x4)[20];
};

/* 458868 */ mpCollisionBox mpLib_80458868[2];

/* 04E97C */ static bool mpLineIntersection(float a0x, float a0y, float a1x,
                                            float a1y, float b0x, float b0y,
                                            float b1x, float b1y, float* int_x,
                                            float* int_y);
/* 4D64B0 */ static bool didCheckBounding;
/* 4D64B4 */ static MapCollData* mpLib_804D64B4;

static size_t const groundCollVtx_count = 2048;
static size_t const groundCollLine_count = 1536;
static size_t const groundCollJoint_count = 256;

/* 4D64B8 */ static CollVtx* groundCollVtx;
/* 4D64BC */ static CollLine* groundCollLine;
/* 4D64C0 */ static CollJoint* groundCollJoint;
/* 4D64C4 */ static CollJoint* jointListStart;
/* 4D64C8 */ static CollJoint* jointListEnd;
/* 4D64CC */ static s32 mpLib_804D64CC;
/* 4D64D0 */ static s32 mpLib_804D64D0;
/* 4D64D4 */ static s32 mpLib_804D64D4;
/* 4D64D8 */ static s32 mpLib_804D64D8;
/* 4D64DC */ static s32 mpLib_804D64DC;
/* 4D64E0 */ static s32 mpLib_804D64E0;
/* 4D64E4 */ static s32 mpLib_804D64E4;
/* 458888 */ Vec3 mpLib_80458888[0x80];

struct mpLib_803BF248_t_x4 mpLib_803BD3D8 = {
    1.0F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD430 = {
    1.0F,         { 0x161, 0x161, 0x161, 0x161 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x036, 0x037, 0x038, 0x039 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD488 = {
    1.5F,         { 0x152, 0x152, 0x152, 0x152 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x01D, 0x01E, 0x01F, 0x020 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD4E0 = {
    1.0F,         { 0x155, 0x155, 0x155, 0x155 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x022, 0x023, 0x024, 0x025 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD538 = {
    1.0F,         { 0x16D, 0x16D, 0x16D, 0x16D },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x00E, 0x00F, 0x010, 0x011 },
    { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD590 = {
    1.0F,         { 0x15B, 0x15B, 0x15B, 0x15B },
    { 1, -1, 0 }, { 0x04B, 0x04B, 0x04C, 0x04C },
    { 1, -1, 0 }, { 0x02C, 0x02D, 0x02E, 0x02F },
    { 1, -1, 1 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD5E8 = {
    1.0F,         { 0x158, 0x158, 0x158, 0x158 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x027, 0x028, 0x029, 0x02A },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD640 = {
    1.0F,         { 0x16A, 0x16A, 0x16A, 0x16A },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x03B, 0x03C, 0x03D, 0x03E },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD698 = {
    1.0F,         { 0x15E, 0x15E, 0x15E, 0x15E },
    { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x031, 0x032, 0x033, 0x034 },
    { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD6F0 = {
    1.0F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD748 = {
    1.0F,         { 0x14F, 0x14F, 0x14F, 0x14F },
    { 1, -1, 0 }, { 0x20E, 0x20E, 0x20E, 0x20E },
    { 0, -1, 0 }, { 0x018, 0x019, 0x01A, 0x01B },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD7A0 = {
    1.0F,
    { 0x14F, 0x14F, 0x14F, 0x14F },
    { 1, 0x00007537, 0 },
    { 0x20E, 0x20E, 0x20E, 0x20E },
    { 0, 0x00007538, 0 },
    { 0x018, 0x019, 0x01A, 0x01B },
    { 1, 0x0000753B, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD7F8 = {
    1.0F,
    { 0x14F, 0x14F, 0x14F, 0x14F },
    { 1, 0x00007539, 0 },
    { 0x20E, 0x20E, 0x20E, 0x20E },
    { 0, 0x00007533, 0 },
    { 0x018, 0x019, 0x01A, 0x01B },
    { 1, 0x0000753A, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD850 = {
    1.0F,
    { 0x14F, 0x14F, 0x14F, 0x14F },
    { 1, 0x0000754A, 0 },
    { 0x20E, 0x20E, 0x20E, 0x20E },
    { 0, 0x00007539, 0 },
    { 0x018, 0x019, 0x01A, 0x01B },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD8A8 = {
    1.0F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD900 = {
    0.1F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD958 = {
    0.9F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD9B0 = {
    1.0F,         { 0x14C, 0x14C, 0x14C, 0x14C },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x013, 0x014, 0x015, 0x016 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDA08 = {
    1.0F,
    { 0x14C, 0x14C, 0x14C, 0x14C },
    { 1, 0x00007531, 0 },
    { -1, -1, -1, -1 },
    { 0, 0x00007532, 0 },
    { 0x013, 0x014, 0x015, 0x016 },
    { 1, 0x00007533, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDA60 = {
    0.2F,         { 0x164, 0x164, 0x164, 0x164 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x036, 0x037, 0x038, 0x039 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDAB8 = {
    1.0F,         { 0x170, 0x170, 0x170, 0x170 },
    { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x040, 0x041, 0x042, 0x043 },
    { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDB10 = {
    0.1F,         { 0x15E, 0x15E, 0x15E, 0x15E },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x031, 0x032, 0x033, 0x034 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDB68 = {
    1.0F,         { 0x167, 0x167, 0x167, 0x167 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x03B, 0x03C, 0x03D, 0x03E },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDBC0 = {
    1.0F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4* mpLib_803BDC18[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDC68[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDCB8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDD08[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDD58[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDDA8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDDF8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDE48[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDE98[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDEE8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDF38[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDF88[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDFD8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD7A0, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE028[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE078[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE0C8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE118[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD850, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE168[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE1B8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE208[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE258[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE2A8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE2F8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BDA08, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE348[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE398[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE3E8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE438[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE488[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE4D8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE528[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE578[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE5C8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE618[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD7F8, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE668[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE6B8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE708[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE758[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE7A8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE7F8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE848[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE898[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE8E8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE938[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE988[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE9D8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEA28[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEA78[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEAC8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEB18[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEB68[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEBB8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEC08[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEC58[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BECA8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BECF8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BED48[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BED98[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEDE8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEE38[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEE88[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEED8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEF28[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEF78[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEFC8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF018[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF068[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF0B8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF108[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF158[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF1A8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF1F8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};

static struct mpLib_803BF248_t mpLib_803BF248[0x47] = {
    { Gr_Kind_Unk00, &mpLib_803BDC18 },
    { Gr_Kind_Test, &mpLib_803BDC68 },
    { Gr_Kind_Castle, &mpLib_803BDCB8 },
    { Gr_Kind_RCruise, &mpLib_803BDD08 },
    { Gr_Kind_Kongo, &mpLib_803BDD58 },
    { Gr_Kind_Garden, &mpLib_803BDDA8 },
    { Gr_Kind_GreatBay, &mpLib_803BDDF8 },
    { Gr_Kind_Shrine, &mpLib_803BDE48 },
    { Gr_Kind_Zebes, &mpLib_803BDE98 },
    { Gr_Kind_Kraid, &mpLib_803BDEE8 },
    { Gr_Kind_Story, &mpLib_803BDF38 },
    { Gr_Kind_Yorster, &mpLib_803BDF88 },
    { Gr_Kind_Izumi, &mpLib_803BDFD8 },
    { Gr_Kind_Greens, &mpLib_803BE028 },
    { Gr_Kind_Corneria, &mpLib_803BE078 },
    { Gr_Kind_Venom, &mpLib_803BE0C8 },
    { Gr_Kind_PStadium, &mpLib_803BE118 },
    { Gr_Kind_Pura, &mpLib_803BE168 },
    { Gr_Kind_MuteCity, &mpLib_803BE1B8 },
    { Gr_Kind_BigBlue, &mpLib_803BE208 },
    { Gr_Kind_Onett, &mpLib_803BE258 },
    { Gr_Kind_Fourside, &mpLib_803BE2A8 },
    { Gr_Kind_Icemt, &mpLib_803BE2F8 },
    { Gr_Kind_Unk23, &mpLib_803BE348 },
    { Gr_Kind_Inishie1, &mpLib_803BE398 },
    { Gr_Kind_Inishie2, &mpLib_803BE3E8 },
    { Gr_Kind_Unk26, &mpLib_803BE438 },
    { Gr_Kind_Flatzone, &mpLib_803BE488 },
    { Gr_Kind_OldPupupu, &mpLib_803BE4D8 },
    { Gr_Kind_OldYoshi, &mpLib_803BE528 },
    { Gr_Kind_OldKongo, &mpLib_803BE578 },
    { Gr_Kind_KinokoRoute, &mpLib_803BE5C8 },
    { Gr_Kind_ShrineRoute, &mpLib_803BE618 },
    { Gr_Kind_ZebesRoute, &mpLib_803BE668 },
    { Gr_Kind_BigBlueRoute, &mpLib_803BE6B8 },
    { Gr_Kind_Unk35, &mpLib_803BE708 },
    { Gr_Kind_Battle, &mpLib_803BE758 },
    { Gr_Kind_Last, &mpLib_803BE7A8 },
    { Gr_Kind_FigureGet, &mpLib_803BE7F8 },
    { Gr_Kind_Pushon, &mpLib_803BE848 },
    { Gr_Kind_TMario, &mpLib_803BE898 },
    { Gr_Kind_TCaptain, &mpLib_803BE8E8 },
    { Gr_Kind_TClink, &mpLib_803BE938 },
    { Gr_Kind_TDonkey, &mpLib_803BE988 },
    { Gr_Kind_TDrmario, &mpLib_803BE9D8 },
    { Gr_Kind_TFalco, &mpLib_803BEA28 },
    { Gr_Kind_TFox, &mpLib_803BEA78 },
    { Gr_Kind_TIceclimber, &mpLib_803BEAC8 },
    { Gr_Kind_TKirby, &mpLib_803BEB18 },
    { Gr_Kind_TKoopa, &mpLib_803BEB68 },
    { Gr_Kind_TLink, &mpLib_803BEBB8 },
    { Gr_Kind_TLuigi, &mpLib_803BEC08 },
    { Gr_Kind_TMars, &mpLib_803BEC58 },
    { Gr_Kind_TMewtwo, &mpLib_803BECA8 },
    { Gr_Kind_TNess, &mpLib_803BECF8 },
    { Gr_Kind_TPeach, &mpLib_803BED48 },
    { Gr_Kind_TPichu, &mpLib_803BED98 },
    { Gr_Kind_TPikachu, &mpLib_803BEDE8 },
    { Gr_Kind_TPurin, &mpLib_803BEE38 },
    { Gr_Kind_TSamus, &mpLib_803BEE88 },
    { Gr_Kind_TSeak, &mpLib_803BEED8 },
    { Gr_Kind_TYoshi, &mpLib_803BEF28 },
    { Gr_Kind_TZelda, &mpLib_803BEF78 },
    { Gr_Kind_TGamewatch, &mpLib_803BEFC8 },
    { Gr_Kind_TEmblem, &mpLib_803BF018 },
    { Gr_Kind_TGanon, &mpLib_803BF068 },
    { Gr_Kind_Heal, &mpLib_803BF0B8 },
    { Gr_Kind_Homerun, &mpLib_803BF108 },
    { Gr_Kind_Figure1, &mpLib_803BF158 },
    { Gr_Kind_Figure2, &mpLib_803BF1A8 },
    { Gr_Kind_Figure3, &mpLib_803BF1F8 },
};

extern Vec2 mpLib_803BF718[2];
extern MapLine mpLib_803BF728;
extern MapJoint mpLib_803BF738;
extern MapCollData mpLib_803BF760;

MapCollData* mpLib_8004D164(void)
{
    return mpLib_804D64B4;
}

CollVtx* mpGetGroundCollVtx(void)
{
    return groundCollVtx;
}

CollLine* mpGetGroundCollLine(void)
{
    return groundCollLine;
}

CollJoint* mpGetGroundCollJoint(void)
{
    return groundCollJoint;
}

void mpPruneEmptyLines(MapCollData* coll_data)
{
    MapLine* line;
    Vec2* verts = coll_data->verts;
    int i;

    if (stage_info.grkind == Gr_Kind_Pura) {
        return;
    }

    line = coll_data->lines;
    for (i = 0; i < coll_data->line_count; i++, line++) {
        Vec2* v0 = &verts[line->v0_idx];
        Vec2* v1 = &verts[line->v1_idx];
        MapLine* other;
        int j;

        if (v0->x != v1->x || v0->y != v1->y) {
            continue;
        }

        other = coll_data->lines;
        for (j = 0; j < coll_data->line_count; j++, other++) {
            if (other->prev_id0 == i) {
                other->prev_id0 = line->prev_id0;
            }
            if (other->next_id0 == i) {
                other->next_id0 = line->next_id0;
            }
            if (other->prev_id1 == i) {
                other->prev_id1 = line->prev_id0;
            }
            if (other->next_id1 == i) {
                other->next_id1 = line->next_id0;
            }
        }

        line->hi_flags |= LINE_FLAG_EMPTY;
        line->prev_id0 = -1;
        line->next_id0 = -1;
        line->prev_id1 = -1;
        line->next_id1 = -1;
    }
}

static inline void mpLib_LoadLineGroup(MapCollData* coll_data, int group)
{
    int count = coll_data->ranges[group].count;
    int start = coll_data->ranges[group].start;
    for (; count > 0; count--) {
        groundCollLine[start].flags =
            coll_data->lines[start].hi_flags | LINE_FLAG_ENABLED;
        groundCollLine[start].inner = &coll_data->lines[start];
        start++;
    }
}

void mpLibLoad(MapCollData* coll_data)
{
    float raw_x, raw_y;
    float y;
    float x;
    float scale;
    CollJoint* joint_prev;
    CollJoint* joint;
    int i;

    joint_prev = NULL;
    groundCollVtx = HSD_MemAlloc(sizeof(*groundCollVtx) * groundCollVtx_count);
    HSD_ASSERT(412, groundCollVtx);
    groundCollLine =
        HSD_MemAlloc(sizeof(*groundCollLine) * groundCollLine_count);
    HSD_ASSERT(413, groundCollLine);
    groundCollJoint =
        HSD_MemAlloc(sizeof(*groundCollJoint) * groundCollJoint_count);
    HSD_ASSERT(414, groundCollJoint);
    grDynamicAttr_801CA0B4();
    if (coll_data == NULL) {
        coll_data = &mpLib_803BF760;
    }
    scale = Ground_801C0498();
    mpLib_80458868[0].right = F32_MAX;
    mpLib_80458868[0].top = F32_MAX;
    mpLib_80458868[0].left = -F32_MAX;
    mpLib_80458868[0].bottom = -F32_MAX;
    for (i = 0; i < coll_data->joint_count; i++) {
        joint = &groundCollJoint[i];
        joint->inner = &coll_data->joints[i];
        joint->flags = CollJoint_Enabled;
        joint->bounding_min.x = scale * coll_data->joints[i].left_bound;
        joint->bounding_min.y = scale * coll_data->joints[i].bottom_bound;
        joint->bounding_max.x = scale * coll_data->joints[i].right_bound;
        joint->bounding_max.y = scale * coll_data->joints[i].top_bound;
        joint->jobj = NULL;
        joint->cb_data_0 = NULL;
        joint->cb_0 = NULL;
        joint->cb_data_1 = NULL;
        joint->cb_1 = NULL;
        joint->xE = true;
        if (joint_prev == NULL) {
            jointListStart = joint;
        } else {
            joint_prev->next = joint;
        }
        joint_prev = joint;
    }
    joint->next = NULL;
    jointListEnd = joint;
    mpPruneEmptyLines(coll_data);

    mpLib_LoadLineGroup(coll_data, MapLineGroup_Floor);
    mpLib_LoadLineGroup(coll_data, MapLineGroup_Ceiling);
    mpLib_LoadLineGroup(coll_data, MapLineGroup_RightWall);
    mpLib_LoadLineGroup(coll_data, MapLineGroup_LeftWall);
    mpLib_LoadLineGroup(coll_data, MapLineGroup_Dynamic);

    for (i = 0; i < coll_data->vert_count; i++) {
        raw_x = coll_data->verts[i].x;
        x = scale * raw_x;
        groundCollVtx[i].base_pos.x = raw_x;
        groundCollVtx[i].pos.x = x;
        groundCollVtx[i].prev_pos.x = x;
        raw_y = coll_data->verts[i].y;
        y = scale * raw_y;
        groundCollVtx[i].base_pos.y = raw_y;
        groundCollVtx[i].pos.y = y;
        groundCollVtx[i].prev_pos.y = y;
        if (mpLib_80458868[0].top < y) {
            mpLib_80458868[0].top = y;
        }
        if (mpLib_80458868[0].bottom > y) {
            mpLib_80458868[0].bottom = y;
        }
        if (mpLib_80458868[0].right < x) {
            mpLib_80458868[0].right = x;
        }
        if (mpLib_80458868[0].left > x) {
            mpLib_80458868[0].left = x;
        }
    }
    mpLib_804D64B4 = coll_data;
    if (coll_data != NULL) {
        mpIsland_8005A728();
    } else {
        mpIsland_8005A6F8();
    }
    mpUncheckBounding();
}

int mpLineGetNext(int line_id)
{
    s16 result = groundCollLine[line_id].inner->next_id1;
    int ret = result;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v1 =
                &groundCollVtx[groundCollLine[line_id].inner->v1_idx];
            CollVtx* v0 = &groundCollVtx[groundCollLine[result].inner->v0_idx];

            if (SQ(v1->pos.x - v0->pos.x) + SQ(v1->pos.y - v0->pos.y) < 4.0) {
                return ret;
            }
        }
    }

    return groundCollLine[line_id].inner->next_id0;
}

int mpLineGetPrev(int line_id)
{
    s16 result = groundCollLine[line_id].inner->prev_id1;
    int ret = result;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v0 =
                &groundCollVtx[groundCollLine[line_id].inner->v0_idx];
            CollVtx* v1 = &groundCollVtx[groundCollLine[result].inner->v1_idx];

            if (SQ(v0->pos.x - v1->pos.x) + SQ(v0->pos.y - v1->pos.y) < 4.0) {
                return ret;
            }
        }
    }

    return groundCollLine[line_id].inner->prev_id0;
}

/// remap point p from line a to line b
static void mpRemap2d(float* x_out, float* y_out, float ax0, float ay0,
                      float ax1, float ay1, float bx0, float by0, float bx1,
                      float by1, float px, float py)
{
    double dx;
    double dy;
    double dist2;
    float apx;
    float apy;
    dx = ax1 - ax0;
    dy = ay1 - ay0;
    apx = px - ax0;
    apy = py - ay0;
    dist2 = (dy * dy) + (dx * dx);
    if (ABS(dist2) > 0.0001) {
        // how far along line a is point p
        double t = (dy * apy + dx * apx) / dist2;
        if (t > 1.0) {
            t = 1.0;
        } else if (t < 0.0) {
            t = 0.0;
        }

        *x_out = px + (1.0 - t) * (bx0 - ax0) + t * (bx1 - ax1);
        *y_out = py + (1.0 - t) * (by0 - ay0) + t * (by1 - ay1);
    } else {
        *x_out = px + (bx0 - ax0) + (bx1 - ax0);
        *y_out = py + (by0 - ay0) + (by1 - ay0);
    }
}

int mpLib_8004DD90_Floor(int line_id, Vec3* vec, float* y_out, u32* flags_out,
                         Vec3* normal_out)
{
    int dir = 0;
    float x0, y0;
    float x1, y1;
    float x, y;

    LINEID_CHECK(774, line_id);

    while (true) {
        CollLine* line = &groundCollLine[line_id];

        x0 = groundCollVtx[line->inner->v0_idx].pos.x;
        x1 = groundCollVtx[line->inner->v1_idx].pos.x;
        x = vec->x;
        y = vec->y;
        if (x < x0) {
            if (dir != 1) {
                int new_id = mpLineGetPrev(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_Floor))
                {
                    if (x - x0 < -0.1) {
                        return -1;
                    }
                    x = x0;
                    break;
                }
                line_id = new_id;
                dir = -1;
            } else {
                x = x0;
                break;
            }
        } else if (x > x1) {
            if (dir != -1) {
                int new_id = mpLineGetNext(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_Floor))
                {
                    if (x - x1 > 0.1) {
                        return -1;
                    }
                    x = x1;
                    break;
                }

                line_id = new_id;
            } else {
                x = x1;
                break;
            }
        } else {
            break;
        }
    }

    if (flags_out != NULL) {
        *flags_out = groundCollLine[line_id].inner->lo_flags;
    }

    y0 = groundCollVtx[groundCollLine[line_id].inner->v0_idx].pos.y;
    y1 = groundCollVtx[groundCollLine[line_id].inner->v1_idx].pos.y;
    if (y_out != NULL) {
        *y_out = (y1 - y0) * (x - x0) / (x1 - x0) + y0 - y + 0.0001;
    }

    if (normal_out != NULL) {
        normal_out->x = -(y1 - y0);
        normal_out->y = x1 - x0;
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }

    return line_id;
}

int mpLib_8004E090_Ceiling(int line_id, Vec3* vec, float* y_out,
                           u32* flags_out, Vec3* normal_out)
{
    int dir = 0;
    float x0, y0;
    float x1, y1;
    float x;

    LINEID_CHECK(893, line_id);

    x = vec->x;
    while (true) {
        CollLine* line = &groundCollLine[line_id];
        x0 = groundCollVtx[line->inner->v0_idx].pos.x;
        x1 = groundCollVtx[line->inner->v1_idx].pos.x;
        if (vec->x < x1) {
            if (dir != 1) {
                int new_id = mpLineGetNext(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_Ceiling))
                {
                    if (vec->x - x1 < -0.1) {
                        return -1;
                    }

                    x = x1;
                    break;
                }
                line_id = new_id;
                dir = -1;
                continue;
            }
            x = x1;
        } else if (vec->x > x0) {
            if (dir != -1) {
                int new_id = mpLineGetPrev(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_Ceiling))
                {
                    if (vec->x - x0 > 0.1) {
                        return -1;
                    }

                    x = x0;
                    break;
                }
                line_id = new_id;
                dir = 1;
                continue;
            }
            x = x0;
        }
        break;
    }

    if (flags_out != NULL) {
        *flags_out = groundCollLine[line_id].inner->lo_flags;
    }

    y0 = groundCollVtx[groundCollLine[line_id].inner->v0_idx].pos.y;
    y1 = groundCollVtx[groundCollLine[line_id].inner->v1_idx].pos.y;

    if (y_out != NULL) {
        *y_out = (y1 - y0) * (x - x0) / (x1 - x0) + y0 - vec->y - 0.0001;
    }

    if (normal_out != NULL) {
        normal_out->x = -(y1 - y0);
        normal_out->y = x1 - x0;
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }

    return line_id;
}

int mpLib_8004E398_LeftWall(int line_id, Vec3* vec, float* x_out,
                            u32* flags_out, Vec3* normal_out)
{
    int dir = 0;
    float x0, y0;
    float x1, y1;
    float y;

    LINEID_CHECK(1014, line_id);

    y = vec->y;
    while (true) {
        CollLine* line = &groundCollLine[line_id];
        y0 = groundCollVtx[line->inner->v0_idx].pos.y;
        y1 = groundCollVtx[line->inner->v1_idx].pos.y;
        if (vec->y < y0) {
            if (dir != 1) {
                int new_id = mpLineGetPrev(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_LeftWall))
                {
                    if (vec->y - y0 < -0.1) {
                        return -1;
                    }
                    y = y0;
                    break;
                }
                line_id = new_id;
                dir = -1;
                continue;
            }
        } else if (vec->y > y1) {
            if (dir != -1) {
                int new_id = mpLineGetNext(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_LeftWall))
                {
                    if (vec->y - y1 > 0.1) {
                        return -1;
                    }
                    y = y1;
                    break;
                }
                line_id = new_id;
                dir = 1;
                continue;
            }
        }
        break;
    }

    if (flags_out != NULL) {
        *flags_out = groundCollLine[line_id].inner->lo_flags;
    }

    x0 = groundCollVtx[groundCollLine[line_id].inner->v0_idx].pos.x;
    x1 = groundCollVtx[groundCollLine[line_id].inner->v1_idx].pos.x;

    if (x_out != NULL) {
        *x_out = x0 + (x1 - x0) * (y - y0) / (y1 - y0) - vec->x;
    }

    if (normal_out != NULL) {
        normal_out->x = -(y1 - y0);
        normal_out->y = x1 - x0;
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }

    return line_id;
}

int mpLib_8004E684_RightWall(int line_id, Vec3* vec, float* x_out,
                             u32* flags_out, Vec3* normal_out)
{
    int dir = 0;
    float x0, y0;
    float x1, y1;
    float y;

    LINEID_CHECK(1134, line_id);

    y = vec->y;
    while (true) {
        CollLine* line = &groundCollLine[line_id];
        y0 = groundCollVtx[line->inner->v0_idx].pos.y;
        y1 = groundCollVtx[line->inner->v1_idx].pos.y;
        if (vec->y > y0) {
            if (dir != -1) {
                int new_id = mpLineGetPrev(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_RightWall))
                {
                    if (vec->y - y0 > 0.1) {
                        return -1;
                    }
                    y = y0;
                    break;
                }
                line_id = new_id;
                dir = 1;
                continue;
            }
            y = y0;
        } else if (vec->y < y1) {
            if (dir != 1) {
                int next_id = mpLineGetNext(line_id);
                if (next_id == -1 ||
                    !(groundCollLine[next_id].flags & CollLine_RightWall))
                {
                    if (vec->y - y1 < -0.1) {
                        return -1;
                    }
                    y = y1;
                    break;
                }
                line_id = next_id;
                dir = -1;
                continue;
            }
            y = y1;
        }
        break;
    }

    if (flags_out != NULL) {
        *flags_out = groundCollLine[line_id].inner->lo_flags;
    }

    x0 = groundCollVtx[groundCollLine[line_id].inner->v0_idx].pos.x;
    x1 = groundCollVtx[groundCollLine[line_id].inner->v1_idx].pos.x;

    if (x_out != NULL) {
        *x_out = x0 + ((x1 - x0) * (y - y0)) / (y1 - y0) - vec->x;
    }

    if (normal_out != NULL) {
        normal_out->x = -(y1 - y0);
        normal_out->y = x1 - x0;
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }

    return line_id;
}

/// direction dependent line intersection
bool mpLineIntersection(float a0x, float a0y, float a1x, float a1y, float b0x,
                        float b0y, float b1x, float b1y, float* int_x,
                        float* int_y)
{
    bool b1_below_a = false;
    bool b2_above_a = false;

    // b entirely left/right of a
    if (a0x <= a1x) {
        if ((b0x < a0x && b1x < a0x) || (a1x < b0x && a1x < b1x)) {
            return false;
        }
    } else {
        if ((b0x < a1x && b1x < a1x) || (a0x < b0x && a0x < b1x)) {
            return false;
        }
    }

    // b entirely above/below a
    if (a0y <= a1y) {
        if ((b0y < a0y && b1y < a0y) || (a1y < b0y && a1y < b1y)) {
            return false;
        }
    } else {
        if ((b0y < a1y && b1y < a1y) || (a0y < b0y && a0y < b1y)) {
            return false;
        }
    }

    {
        double ah = a1y - a0y;
        double d0x = b0x - a0x;
        double aw = a1x - a0x;
        double d0y = b0y - a0y;
        double hs_b0_a = (aw * d0y) - (ah * d0x);
        double d1y;
        double d1x;
        double det;
        double hs_b1_a;
        double bh;
        double bw;

        if (hs_b0_a < 0.0) {
            if (hs_b0_a < -0.1) {
                return false;
            }
            b1_below_a = true;
        }

        d1x = b1x - a1x;
        d1y = b1y - a1y;

        hs_b1_a = (aw * d1y) - (ah * d1x);
        if (hs_b1_a > 0.0) {
            if (hs_b1_a > 0.1) {
                return false;
            }
            b2_above_a = true;
        }

        // check if a and b are colinear
        if (hs_b0_a == 0.0 && hs_b1_a == 0.0) {
            return false;
        }

        det = (d0x * d1y) - (d0y * d1x);
        if (det < hs_b0_a) {
            if (det < hs_b1_a) {
                return false;
            }
        } else if (det > hs_b0_a) {
            if (det > hs_b1_a) {
                return false;
            }
        }

        bw = b1x - b0x;
        bh = b1y - b0y;
        if (!((bw == 0.0 && bh == 0.0) || (b1_below_a && b2_above_a) ||
              (hs_b0_a >= 0.0 && b2_above_a)))
        {
            double area = (bw * ah) - (bh * aw);

            if (ABS(area) > 0.0001F) {
                double t =
                    ((bw * d0y) - (bh * d0x)) / area; // barycentric weight
                if (t > 0.0) {
                    if (t < 1.0) {
                        *int_x = (aw * t) + a0x;
                        *int_y = (ah * t) + a0y;
                    } else {
                        *int_x = a1x;
                        *int_y = a1y;
                    }
                } else {
                    *int_x = a0x;
                    *int_y = a0y;
                }

                goto tlabel;
            }
        }
        return false;
    tlabel:
        return true;
    }
}

/// line intersection between a and b, where a is a horizontal line
bool mpLineIntersectionH(float* int_x, float* int_y, float a0x, float a0y,
                         float a1x, float b0x, float b0y, float b1x, float b1y)
{
    float max_ax;
    float min_ax;
    double dbx;
    double dby;
    double new_x;
    double dx;

    if (a0x < a1x) {
        if ((b0x < a0x && b1x < a0x) || (a1x < b0x && a1x < b1x)) {
            return false;
        }
        if (b0y - a0y < -0.0001 || b1y - a0y > 0.0001) {
            return false;
        }
        min_ax = a0x;
        max_ax = a1x;
    } else {
        if ((b0x < a1x && b1x < a1x) || (a0x < b0x && a0x < b1x)) {
            return false;
        }
        if (b1y - a0y < -0.0001 || b0y - a0y > 0.0001) {
            return false;
        }
        min_ax = a1x;
        max_ax = a0x;
    }
    dby = b1y - b0y;
    dbx = b1x - b0x;
    if (ABS(dby) < 0.0001) {
        return false;
    }
    new_x = dbx / dby * (a0y - b0y) + b0x;
    dx = new_x - min_ax;
    if (dx < 0.0) {
        if (dx < -0.1) {
            return false;
        }
        new_x = min_ax;
    }
    if (new_x - max_ax > 0.0) {
        if (new_x - max_ax > 0.1) {
            return false;
        }
        new_x = max_ax;
    }
    *int_x = new_x;
    *int_y = a0y;
    return true;
}

static inline CollLine* mpLineGetCollLine(int line_id)
{
    return &groundCollLine[line_id];
}

void mpLib_8004ED5C(int line_id, float* x0_out, float* y0_out, float* x1_out,
                    float* y1_out)
{
    bool calculated_distance = false;
    CollLine* line = mpLineGetCollLine(line_id);

    int i0;
    int i1;
    float x0;
    float y0;
    float x1;
    float y1;
    float distance;

    i0 = line->inner->v0_idx;
    x0 = groundCollVtx[i0].pos.x;
    y0 = groundCollVtx[i0].pos.y;
    i1 = line->inner->v1_idx;
    x1 = groundCollVtx[i1].pos.x;
    y1 = groundCollVtx[i1].pos.y;

    if (mpLineGetPrev(line_id) != -1) {
        distance = sqrtf(SQ(x0 - x1) + SQ(y0 - y1));
        if (distance > 0.001F) {
            x0 += (x0 - x1) / distance;
            y0 += (y0 - y1) / distance;
        }
        calculated_distance = true;
    }

    if (mpLineGetNext(line_id) != -1) {
        if (!calculated_distance) {
            distance = sqrtf(SQ(x0 - x1) + SQ(y0 - y1));
        }
        if (distance > 0.001F) {
            x1 += (x1 - x0) / distance;
            y1 += (y1 - y0) / distance;
        }
    }

    *x0_out = x0;
    *y0_out = y0;
    *x1_out = x1;
    *y1_out = y1;
}

bool mpCheckFloor(float ax, float ay, float bx, float by, float y_offset,
                  Vec3* vec_out, int* line_id_out, u32* flags_out,
                  Vec3* normal_out, int line_id_skip, int joint_id_skip,
                  int joint_id_only, bool (*cb)(Fighter_GObj*, int),
                  Fighter_GObj* gobj)
{
    float min_dist2;
    CollJoint* joint;
    int i;
    bool result;
    bool already_checked;
    PAD_STACK(8);

    result = false;
    min_dist2 = F32_MAX;
    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck2(ax, ay, bx, by);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        MapJoint* j_inner;
        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == joint - groundCollJoint ||
            (joint_id_only != -1 && joint_id_only != joint - groundCollJoint))
        {
            continue;
        }

        j_inner = joint->inner;
        i = 0;
        count = j_inner->ranges[MapLineGroup_Floor].count;
        dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[j_inner->ranges[MapLineGroup_Floor].start];
        for (; i < count; i += 1, line += 1) {
            float px;
            float py;
            u8 pad[4];
            float x0;
            float y0;
            float x1;
            float y1;
            float dist2;
            ssize_t line_offset;
        block_8:
            if (cb != NULL && !cb(gobj, line - groundCollLine)) {
                continue;
            }

            if (line_id_skip ==
                (line_offset = (intptr_t) line - (intptr_t) groundCollLine) /
                    (ssize_t) sizeof(CollLine))
            {
                continue;
            }

            if (!(line->flags & CollLine_Floor) ||
                !(line->flags & LINE_FLAG_ENABLED) ||
                line->flags & LINE_FLAG_EMPTY)
            {
                continue;
            }

            mpLib_8004ED5C(line_offset / (ssize_t) sizeof(CollLine), &x0, &y0,
                           &x1, &y1);
            y0 += y_offset;
            y1 += y_offset;
            if (ABS(y0 - y1) > 0.0001) {
                if (mpLineIntersection(x0, y0, x1, y1, ax, ay, bx, by, &px,
                                       &py))
                {
                    dist2 = SQ(px - ax) + SQ(py - ay);
                    if (min_dist2 > dist2) {
                        min_dist2 = dist2;
                        if (vec_out != NULL) {
                            vec_out->x = px;
                            vec_out->y = py;
                            vec_out->z = 0.0F;
                        }
                        if (line_id_out != NULL) {
                            *line_id_out = line - groundCollLine;
                        }
                        if (flags_out != NULL) {
                            *flags_out = line->inner->lo_flags;
                        }
                        if (normal_out != NULL) {
                            normal_out->x = -(y1 - y0);
                            normal_out->y = x1 - x0;
                            normal_out->z = 0.0F;
                            PSVECNormalize(normal_out, normal_out);
                        }
                        result = true;
                    }
                }
            } else {
                if (ay >= by &&
                    mpLineIntersectionH(&px, &py, x0, y0, x1, ax, ay, bx, by))
                {
                    dist2 = SQ(px - ax) + SQ(py - ay);
                    if (min_dist2 > dist2) {
                        min_dist2 = dist2;
                        if (vec_out != NULL) {
                            vec_out->x = px;
                            vec_out->y = py;
                            vec_out->z = 0.0F;
                        }
                        if (line_id_out != NULL) {
                            *line_id_out = line - groundCollLine;
                        }
                        if (flags_out != NULL) {
                            *flags_out = line->inner->lo_flags;
                        }
                        if (normal_out != NULL) {
                            normal_out->x = 0.0F;
                            normal_out->y = 1.0F;
                            normal_out->z = 0.0F;
                        }
                        result = true;
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

bool mpCheckFloorRemap(float ax, float ay, float bx, float by, float y_offset,
                       Vec3* vec_out, int* line_id_out, u32* flags_out,
                       Vec3* normal_out, int line_id_skip, int joint_id_skip,
                       int joint_id_only, bool (*cb)(Fighter_GObj*, int),
                       Fighter_GObj* gobj)
{
    float min_dist2 = F32_MAX;
    float old_x = ax;
    float old_y = ay;
    CollJoint* joint;
    int i;
    bool result = false;
    bool already_checked;

    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck2(ax, ay, bx, by);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == joint - groundCollJoint ||
            (joint_id_only != -1 && joint_id_only != joint - groundCollJoint))
        {
            continue;
        }

        count = joint->inner->ranges[MapLineGroup_Floor].count;
        dynamic_count = joint->inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[joint->inner->ranges[MapLineGroup_Floor].start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (cb != NULL && !cb(gobj, line - groundCollLine)) {
                continue;
            }

            if (line_id_skip == line - groundCollLine) {
                continue;
            }

            if (!(line->flags & CollLine_Floor) ||
                !(line->flags & LINE_FLAG_ENABLED) ||
                line->flags & LINE_FLAG_EMPTY)
            {
                continue;
            }

            {
                CollVtx* v0 = &groundCollVtx[line->inner->v0_idx];
                CollVtx* v1 = &groundCollVtx[line->inner->v1_idx];
                float x0 = groundCollVtx[line->inner->v0_idx].pos.x;
                float y0 = y_offset + groundCollVtx[line->inner->v0_idx].pos.y;
                float x1 = groundCollVtx[line->inner->v1_idx].pos.x;
                float y1 = y_offset + groundCollVtx[line->inner->v1_idx].pos.y;
                float dx;
                float dy;
                float dx2;
                float dy2;
                float dist2;
                float int_x;
                float int_y;
                PAD_STACK(4);

                if (joint->flags &
                    (CollJoint_B10 | CollJoint_B9 | CollJoint_B8))
                {
                    mpRemap2d(&ax, &ay,
                              groundCollVtx[line->inner->v0_idx].prev_pos.x,
                              groundCollVtx[line->inner->v0_idx].prev_pos.y,
                              groundCollVtx[line->inner->v1_idx].prev_pos.x,
                              groundCollVtx[line->inner->v1_idx].prev_pos.y,
                              x0, y0, x1, y1, old_x, old_y);
                } else {
                    ax = old_x;
                    ay = old_y;
                }

                dx = bx - ax;
                dy = by - ay;

                if (ABS(y0 - y1) > 0.0001) {
                    if (mpLineIntersection(x0, y0, x1, y1, ax, ay, bx, by,
                                           &int_x, &int_y))
                    {
                        dx2 = SQ(int_x - old_x);
                        dy2 = SQ(int_y - old_y);
                        dist2 = dx2 + dy2;

                        if (dx * (int_x - old_x) + dy * (int_y - old_y) < 0.0F)
                        {
                            dist2 = -dist2;
                        }

                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;
                            if (vec_out) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out) {
                                *line_id_out = line - groundCollLine;
                            }
                            if (flags_out) {
                                *flags_out = line->inner->lo_flags;
                            }
                            if (normal_out) {
                                normal_out->x = -(y1 - y0);
                                normal_out->y = x1 - x0;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }
                            result = true;
                        }
                    }
                } else if (ay >= by &&
                           mpLineIntersectionH(&int_x, &int_y, x0, y0, x1, ax,
                                               ay, bx, by))
                {
                    dx2 = SQ(int_x - old_x);
                    dy2 = SQ(int_y - old_y);
                    dist2 = dx2 + dy2;

                    if (dx * (int_x - old_x) + dy * (int_y - old_y) < 0.0F) {
                        dist2 = -dist2;
                    }

                    if (min_dist2 > dist2) {
                        min_dist2 = dist2;
                        if (vec_out) {
                            vec_out->x = int_x;
                            vec_out->y = int_y;
                            vec_out->z = 0.0F;
                        }
                        if (line_id_out) {
                            *line_id_out = line - groundCollLine;
                        }
                        if (flags_out) {
                            *flags_out = line->inner->lo_flags;
                        }
                        if (normal_out) {
                            normal_out->x = 0.0F;
                            normal_out->y = 1.0F;
                            normal_out->z = 0.0F;
                        }
                        result = true;
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

bool mpCheckCeiling(float ax, float ay, float bx, float by, Vec3* vec_out,
                    int* line_id_out, u32* flags_out, Vec3* normal_out,
                    int joint_id_skip, int joint_id_only)
{
    float min_dist2 = F32_MAX;
    CollJoint* joint;
    int i;
    bool result = false;
    bool already_checked;
    PAD_STACK(8);

    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck2(ax, ay, bx, by);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        MapJoint* j_inner;
        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == joint - groundCollJoint ||
            (joint_id_only != -1 && joint_id_only != joint - groundCollJoint))
        {
            continue;
        }

        j_inner = joint->inner;
        i = 0;
        count = j_inner->ranges[MapLineGroup_Ceiling].count;
        dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[j_inner->ranges[MapLineGroup_Ceiling].start];
        for (; i < count; i += 1, line += 1) {
            float int_x;
            float int_y;
            u8 pad[4];
            float x0;
            float y0;
            float x1;
            float y1;
            float dist2;

        block_8:
            if (!(line->flags & CollLine_Ceiling) ||
                !(line->flags & LINE_FLAG_ENABLED) ||
                line->flags & LINE_FLAG_EMPTY)
            {
                continue;
            }

            mpLib_8004ED5C(line - groundCollLine, &x0, &y0, &x1, &y1);
            if (ABS(y0 - y1) > 0.0001) {
                if (mpLineIntersection(x0, y0, x1, y1, ax, ay, bx, by, &int_x,
                                       &int_y))
                {
                    dist2 = SQ(int_x - ax) + SQ(int_y - ay);
                    if (min_dist2 > dist2) {
                        min_dist2 = dist2;

                        if (vec_out != NULL) {
                            vec_out->x = int_x;
                            vec_out->y = int_y;
                            vec_out->z = 0.0F;
                        }

                        if (line_id_out != NULL) {
                            *line_id_out = line - groundCollLine;
                        }

                        if (flags_out != NULL) {
                            *flags_out = line->inner->lo_flags;
                        }

                        if (normal_out != NULL) {
                            normal_out->x = -(y1 - y0);
                            normal_out->y = x1 - x0;
                            normal_out->z = 0.0F;
                            PSVECNormalize(normal_out, normal_out);
                        }

                        result = true;
                    }
                }
            } else {
                if (ay <= by && mpLineIntersectionH(&int_x, &int_y, x0, y0, x1,
                                                    ax, ay, bx, by))
                {
                    dist2 = SQ(int_x - ax) + SQ(int_y - ay);
                    if (min_dist2 > dist2) {
                        min_dist2 = dist2;

                        if (vec_out != NULL) {
                            vec_out->x = int_x;
                            vec_out->y = int_y;
                            vec_out->z = 0.0F;
                        }

                        if (line_id_out != NULL) {
                            *line_id_out = line - groundCollLine;
                        }

                        if (flags_out != NULL) {
                            *flags_out = line->inner->lo_flags;
                        }

                        if (normal_out != NULL) {
                            normal_out->x = 0.0F;
                            normal_out->y = -1.0F;
                            normal_out->z = 0.0F;
                        }

                        result = true;
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

bool mpCheckCeilingRemap(float ax, float ay, float bx, float by, Vec3* vec_out,
                         int* line_id_out, u32* flags_out, Vec3* normal_out,
                         int joint_id_skip, int joint_id_only)
{
    float min_dist2 = F32_MAX;
    float old_x = ax;
    float old_y = ay;
    CollJoint* joint;
    int i;
    int result = false;
    bool already_checked = mpCheckedBounding();

    if (!already_checked) {
        mpBoundingCheck2(ax, ay, bx, by);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == (joint - groundCollJoint) ||
            !(joint_id_only == -1 ||
              joint_id_only == (joint - groundCollJoint)))
        {
            continue;
        }

        count = joint->inner->ranges[MapLineGroup_Ceiling].count;
        dynamic_count = joint->inner->ranges[MapLineGroup_Dynamic].count;
        line =
            &groundCollLine[joint->inner->ranges[MapLineGroup_Ceiling].start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_Ceiling &&
                line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                float dx2;
                float dy2;
                float dist2;
                float dx;
                float dy;
                float int_x;
                float int_y;
                u8 _[12];
                float x0;
                float y0;
                float x1;
                float y1;
                mpLib_8004ED5C(line - groundCollLine, &x0, &y0, &x1, &y1);

                if (joint->flags &
                    (CollJoint_B10 | CollJoint_B9 | CollJoint_B8))
                {
                    MapLine* map_line = line->inner;
                    CollVtx* v1 = &groundCollVtx[map_line->v1_idx];
                    CollVtx* v0 = &groundCollVtx[map_line->v0_idx];
                    mpRemap2d(&ax, &ay, v0->prev_pos.x, v0->prev_pos.y,
                              v1->prev_pos.x, v1->prev_pos.y, x0, y0, x1, y1,
                              old_x, old_y);
                } else {
                    ax = old_x;
                    ay = old_y;
                }

                dx = bx - ax;
                dy = by - ay;
                if (ABS(y0 - y1) > 0.0001) {
                    if (mpLineIntersection(x0, y0, x1, y1, ax, ay, bx, by,
                                           &int_x, &int_y))
                    {
                        dx2 = SQ(int_x - old_x);
                        dy2 = SQ(int_y - old_y);
                        dist2 = dx2 + dy2;
                        if ((dx * (int_x - old_x)) + (dy * (int_y - old_y)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = -(y1 - y0);
                                normal_out->y = x1 - x0;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }

                            result = true;
                        }
                    }
                } else {
                    if (ay <= by && mpLineIntersectionH(&int_x, &int_y, x0, y0,
                                                        x1, ax, ay, bx, by))
                    {
                        dx2 = SQ(int_x - old_x);
                        dy2 = SQ(int_y - old_y);
                        dist2 = dx2 + dy2;
                        if ((dx * (int_x - old_x)) + (dy * (int_y - old_y)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = 0.0F;
                                normal_out->y = -1.0F;
                                normal_out->z = 0.0F;
                            }

                            result = true;
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

/// line intersection between a and b, where a is a vertical line
bool mpLineIntersectionV(float* int_x, float* int_y, float a0x, float a0y,
                         float a1y, float b0x, float b0y, float b1x, float b1y)
{
    float min_ay;
    float max_ay;
    double dbx;
    double dby;
    double new_y;
    double dy;

    if (a0y < a1y) {
        if ((b0y < a0y && b1y < a0y) || (a1y < b0y && a1y < b1y)) {
            return false;
        }
        if (b1x - a0x < -0.0001 || b0x - a0x > 0.0001) {
            return false;
        }
        min_ay = a0y;
        max_ay = a1y;
    } else {
        if ((b0y < a1y && b1y < a1y) || (a0y < b0y && a0y < b1y)) {
            return false;
        }
        if (b0x - a0x < -0.0001 || b1x - a0x > 0.0001) {
            return false;
        }
        min_ay = a1y;
        max_ay = a0y;
    }
    dby = b1y - b0y;
    dbx = b1x - b0x;
    if (ABS(dbx) < 0.0001) {
        return false;
    }
    new_y = (dby / dbx * (a0x - b0x)) + b0y;
    dy = new_y - min_ay;
    if (dy < 0.0) {
        if (dy < -0.1) {
            return false;
        }
        new_y = min_ay;
    }
    dy = new_y - max_ay;
    if (dy > 0.0) {
        if (dy > 0.1) {
            return false;
        }
        new_y = max_ay;
    }
    *int_x = a0x;
    *int_y = new_y;
    return true;
}

bool mpCheckLeftWall(float ax, float ay, float bx, float by, Vec3* vec_out,
                     int* line_id_out, u32* flags_out, Vec3* normal_out,
                     int joint_id_skip, int joint_id_only)
{
    float min_dist2;
    CollJoint* joint;
    int i;
    bool result;
    CollLine* line;
    int count;
    int dynamic_count;
    MapJoint* j_inner;
    bool already_checked;
    PAD_STACK(4);

    result = false;
    min_dist2 = F32_MAX;
    already_checked = mpCheckedBounding();

    if (!already_checked) {
        mpBoundingCheck2(ax, ay, bx, by);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == (joint - groundCollJoint) ||
            !(joint_id_only == -1 ||
              joint_id_only == (joint - groundCollJoint)))
        {
            continue;
        }

        j_inner = joint->inner;

        count = j_inner->ranges[MapLineGroup_LeftWall].count;
        dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[j_inner->ranges[MapLineGroup_LeftWall].start];

        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_LeftWall &&
                line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                MapLine* inner = line->inner;
                CollVtx* v0 = &groundCollVtx[inner->v0_idx];
                CollVtx* v1 = &groundCollVtx[inner->v1_idx];
                float x0 = v0->pos.x;
                float y0 = v0->pos.y;
                float x1 = v1->pos.x;
                float y1 = v1->pos.y;
                float dx2;
                float dy2;
                float dist2;
                float int_x;
                float int_y;
                if (ABS(x0 - x1) > 0.0001) {
                    if (mpLineIntersection(x0, y0, x1, y1, ax, ay, bx, by,
                                           &int_x, &int_y))
                    {
                        dx2 = SQ(int_x - ax);
                        dy2 = SQ(int_y - ay);
                        dist2 = dx2 + dy2;
                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;
                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }
                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }
                            if (normal_out != NULL) {
                                normal_out->x = -(y1 - y0);
                                normal_out->y = x1 - x0;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }
                            result = true;
                        }
                    }
                } else {
                    if ((ax <= bx) &&
                        mpLineIntersectionV(&int_x, &int_y, x0, y0, y1, ax, ay,
                                            bx, by))
                    {
                        dx2 = SQ(int_x - ax);
                        dy2 = SQ(int_y - ay);
                        dist2 = dx2 + dy2;
                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;
                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }
                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }
                            if (normal_out != NULL) {
                                normal_out->x = -1.0F;
                                normal_out->y = 0.0F;
                                normal_out->z = 0.0F;
                            }
                            result = true;
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }
    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

bool mpCheckLeftWallRemap(float ax, float ay, float bx, float by,
                          Vec3* vec_out, int* line_id_out, u32* flags_out,
                          Vec3* normal_out, int joint_id_skip,
                          int joint_id_only)
{
    float min_dist2;
    float old_x = ax;
    float old_y = ay;
    CollJoint* joint;
    int i;
    bool result;
    CollLine* line;
    int count;
    int dynamic_count;
    MapJoint* j_inner;
    bool already_checked;
    PAD_STACK(8);

    result = false;
    min_dist2 = F32_MAX;

    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck2(ax, ay, bx, by);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == (joint - groundCollJoint) ||
            !(joint_id_only == -1 ||
              joint_id_only == (joint - groundCollJoint)))
        {
            continue;
        }

        j_inner = joint->inner;
        count = j_inner->ranges[MapLineGroup_LeftWall].count;
        dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[j_inner->ranges[MapLineGroup_LeftWall].start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_LeftWall &&
                line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                float x0 = groundCollVtx[line->inner->v0_idx].pos.x;
                float y0 = groundCollVtx[line->inner->v0_idx].pos.y;
                float x1 = groundCollVtx[line->inner->v1_idx].pos.x;
                float y1 = groundCollVtx[line->inner->v1_idx].pos.y;
                float dx;
                float dy;
                float dx2;
                float dy2;
                float dist2;
                float int_x;
                float int_y;

                if (joint->flags &
                    (CollJoint_B10 | CollJoint_B9 | CollJoint_B8))
                {
                    mpRemap2d(&ax, &ay,
                              groundCollVtx[line->inner->v0_idx].prev_pos.x,
                              groundCollVtx[line->inner->v0_idx].prev_pos.y,
                              groundCollVtx[line->inner->v1_idx].prev_pos.x,
                              groundCollVtx[line->inner->v1_idx].prev_pos.y,
                              x0, y0, x1, y1, old_x, old_y);
                } else {
                    ax = old_x;
                    ay = old_y;
                }

                dx = bx - ax;
                dy = by - ay;
                if (ABS(x0 - x1) > 0.0001) {
                    if (mpLineIntersection(x0, y0, x1, y1, ax, ay, bx, by,
                                           &int_x, &int_y))
                    {
                        dx2 = SQ(int_x - old_x);
                        dy2 = SQ(int_y - old_y);
                        dist2 = dx2 + dy2;
                        if ((dx * (int_x - old_x)) + (dy * (int_y - old_y)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }

                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = -(y1 - y0);
                                normal_out->y = x1 - x0;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }

                            result = true;
                        }
                    }
                } else {
                    if (ax <= bx && mpLineIntersectionV(&int_x, &int_y, x0, y0,
                                                        y1, ax, ay, bx, by))
                    {
                        dx2 = SQ(int_x - old_x);
                        dy2 = SQ(int_y - old_y);
                        dist2 = dx2 + dy2;
                        if ((dx * (int_x - old_x)) + (dy * (int_y - old_y)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }

                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = -1.0F;
                                normal_out->y = 0.0F;
                                normal_out->z = 0.0F;
                            }

                            result = true;
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

bool mpCheckRightWall(float ax, float ay, float bx, float by, Vec3* vec_out,
                      int* line_id_out, u32* flags_out, Vec3* normal_out,
                      int joint_id_skip, int joint_id_only)
{
    float min_dist2;
    CollJoint* joint;
    int i;
    bool result;
    CollLine* line;
    int count;
    int dynamic_count;
    MapJoint* j_inner;
    bool already_checked;
    PAD_STACK(4);

    result = false;
    min_dist2 = F32_MAX;
    already_checked = mpCheckedBounding();

    if (!already_checked) {
        mpBoundingCheck2(ax, ay, bx, by);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == (joint - groundCollJoint) ||
            !(joint_id_only == -1 ||
              joint_id_only == (joint - groundCollJoint)))
        {
            continue;
        }

        j_inner = joint->inner;

        count = j_inner->ranges[MapLineGroup_RightWall].count;
        dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[j_inner->ranges[MapLineGroup_RightWall].start];

        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_RightWall &&
                line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                MapLine* inner = line->inner;
                CollVtx* v0 = &groundCollVtx[inner->v0_idx];
                CollVtx* v1 = &groundCollVtx[inner->v1_idx];
                float x0 = v0->pos.x;
                float y0 = v0->pos.y;
                float x1 = v1->pos.x;
                float y1 = v1->pos.y;
                float dx2;
                float dy2;
                float dist2;
                float int_x;
                float int_y;
                if (ABS(x0 - x1) > 0.0001) {
                    if (mpLineIntersection(x0, y0, x1, y1, ax, ay, bx, by,
                                           &int_x, &int_y))
                    {
                        dx2 = SQ(int_x - ax);
                        dy2 = SQ(int_y - ay);
                        dist2 = dx2 + dy2;
                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;
                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }
                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }
                            if (normal_out != NULL) {
                                normal_out->x = -(y1 - y0);
                                normal_out->y = x1 - x0;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }
                            result = true;
                        }
                    }
                } else {
                    if (ax >= bx && mpLineIntersectionV(&int_x, &int_y, x0, y0,
                                                        y1, ax, ay, bx, by))
                    {
                        dx2 = SQ(int_x - ax);
                        dy2 = SQ(int_y - ay);
                        dist2 = dx2 + dy2;
                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;
                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }
                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }
                            if (normal_out != NULL) {
                                normal_out->x = 1.0F;
                                normal_out->y = 0.0F;
                                normal_out->z = 0.0F;
                            }
                            result = true;
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }
    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

bool mpCheckRightWallRemap(float ax, float ay, float bx, float by,
                           Vec3* vec_out, int* line_id_out, u32* flags_out,
                           Vec3* normal_out, int joint_id_skip,
                           int joint_id_only)
{
    float min_dist2;
    float old_x = ax;
    float old_y = ay;
    CollJoint* joint;
    int i;
    int result;
    bool already_checked;
    PAD_STACK(8);

    result = false;
    min_dist2 = F32_MAX;

    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck2(ax, ay, bx, by);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        MapJoint* j_inner;

        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == (joint - groundCollJoint) ||
            !(joint_id_only == -1 ||
              joint_id_only == (joint - groundCollJoint)))
        {
            continue;
        }

        j_inner = joint->inner;
        count = j_inner->ranges[MapLineGroup_RightWall].count;
        dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[j_inner->ranges[MapLineGroup_RightWall].start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_RightWall &&
                line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                float x0 = groundCollVtx[line->inner->v0_idx].pos.x;
                float y0 = groundCollVtx[line->inner->v0_idx].pos.y;
                float x1 = groundCollVtx[line->inner->v1_idx].pos.x;
                float y1 = groundCollVtx[line->inner->v1_idx].pos.y;
                float dx;
                float dy;
                float dx2;
                float dy2;
                float dist2;
                float int_x;
                float int_y;

                if (joint->flags &
                    (CollJoint_B10 | CollJoint_B9 | CollJoint_B8))
                {
                    mpRemap2d(&ax, &ay,
                              groundCollVtx[line->inner->v0_idx].prev_pos.x,
                              groundCollVtx[line->inner->v0_idx].prev_pos.y,
                              groundCollVtx[line->inner->v1_idx].prev_pos.x,
                              groundCollVtx[line->inner->v1_idx].prev_pos.y,
                              x0, y0, x1, y1, old_x, old_y);
                } else {
                    ax = old_x;
                    ay = old_y;
                }

                dx = bx - ax;
                dy = by - ay;
                if (ABS(x0 - x1) > 0.0001) {
                    if (mpLineIntersection(x0, y0, x1, y1, ax, ay, bx, by,
                                           &int_x, &int_y))
                    {
                        dx2 = SQ(int_x - old_x);
                        dy2 = SQ(int_y - old_y);
                        dist2 = dx2 + dy2;
                        if ((dx * (int_x - old_x)) + (dy * (int_y - old_y)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }

                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = -(y1 - y0);
                                normal_out->y = x1 - x0;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }

                            result = true;
                        }
                    }
                } else {
                    if (ax >= bx && mpLineIntersectionV(&int_x, &int_y, x0, y0,
                                                        y1, ax, ay, bx, by))
                    {
                        dx2 = SQ(int_x - old_x);
                        dy2 = SQ(int_y - old_y);
                        dist2 = dx2 + dy2;
                        if ((dx * (int_x - old_x)) + (dy * (int_y - old_y)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }

                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x;
                                vec_out->y = int_y;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = line - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = line->inner->lo_flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = 1.0F;
                                normal_out->y = 0.0F;
                                normal_out->z = 0.0F;
                            }

                            result = true;
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

bool mpLib_800511A4_RightWall(float ax, float ay, float bx, float by, float cx,
                              float cy, float dx, float dy, int* line_id_out,
                              int joint_id_skip, int joint_id_only)
{
    float min_dist2;
    CollJoint* joint;
    int i;
    int result;
    bool already_checked;
    PAD_STACK(8);

    result = false;
    min_dist2 = F32_MAX;
    already_checked = mpCheckedBounding();

    if (!already_checked) {
        mpBoundingCheck3(ax, ay, bx, by, cx, cy, dx, dy);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        MapJoint* j_inner;

        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == (joint - groundCollJoint) ||
            !(joint_id_only == -1 ||
              joint_id_only == (joint - groundCollJoint)))
        {
            continue;
        }

        j_inner = joint->inner;

        count = j_inner->ranges[MapLineGroup_RightWall].count;
        dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[j_inner->ranges[MapLineGroup_RightWall].start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_RightWall &&
                line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                CollVtx* vtx;
                float int_x;
                float int_y;
                float x;
                float y;
                float x0;
                float y0;
                float x1;
                float y1;
                float vdx;
                float vdy;
                float dist2;

                {
                    vtx = &groundCollVtx[line->inner->v0_idx];
                    x0 = vtx->pos.x;
                    y0 = vtx->pos.y;
                    x1 = vtx->prev_pos.x;
                    y1 = vtx->prev_pos.y;
                    mpRemap2d(&x, &y, ax, ay, bx, by, cx, cy, dx, dy, x1, y1);

                    vdx = x0 - x;
                    vdy = y0 - y;

                    if (SQ(vdx) + SQ(vdy) > 0.001F) {
                        if (mpLineIntersection(cx, cy, dx, dy, x, y, x0, y0,
                                               &int_x, &int_y))
                        {
                            dist2 = SQ(int_x - x1) + SQ(int_y - y1);
                            if ((vdx * (int_x - x1)) + (vdy * (int_y - y1)) <
                                0.0F)
                            {
                                dist2 = -dist2;
                            }
                            if (min_dist2 > dist2) {
                                min_dist2 = dist2;
                                if (line_id_out != NULL) {
                                    *line_id_out = line - groundCollLine;
                                }
                                result = true;
                            }
                        }
                    }
                }

                {
                    vtx = &groundCollVtx[line->inner->v1_idx];
                    x0 = vtx->pos.x;
                    y0 = vtx->pos.y;
                    x1 = vtx->prev_pos.x;
                    y1 = vtx->prev_pos.y;
                    mpRemap2d(&x, &y, ax, ay, bx, by, cx, cy, dx, dy, x1, y1);

                    vdx = x0 - x;
                    vdy = y0 - y;

                    if (SQ(vdx) + SQ(vdy) > 0.001F) {
                        if (mpLineIntersection(cx, cy, dx, dy, x, y, x0, y0,
                                               &int_x, &int_y))
                        {
                            dist2 = SQ(int_x - x1) + SQ(int_y - y1);
                            if ((vdx * (int_x - x1)) + (vdy * (int_y - y1)) <
                                0.0F)
                            {
                                dist2 = -dist2;
                            }
                            if (min_dist2 > dist2) {
                                min_dist2 = dist2;
                                if (line_id_out != NULL) {
                                    *line_id_out = line - groundCollLine;
                                }
                                result = true;
                            }
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

bool mpLib_800515A0_LeftWall(float a0x, float a0y, float a1x, float a1y,
                             float b0x, float b0y, float b1x, float b1y,
                             int* line_id_out, int joint_id_skip,
                             int joint_id_only)
{
    float min_dist2;
    CollJoint* joint;
    int i;
    int result;
    bool already_checked;
    PAD_STACK(8);

    result = false;
    min_dist2 = F32_MAX;
    already_checked = mpCheckedBounding();

    if (!already_checked) {
        mpBoundingCheck3(a0x, a0y, a1x, a1y, b0x, b0y, b1x, b1y);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        MapJoint* j_inner;

        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == (joint - groundCollJoint) ||
            !(joint_id_only == -1 ||
              joint_id_only == (joint - groundCollJoint)))
        {
            continue;
        }

        j_inner = joint->inner;

        count = j_inner->ranges[MapLineGroup_LeftWall].count;
        dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
        line = &groundCollLine[j_inner->ranges[MapLineGroup_LeftWall].start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_LeftWall &&
                line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                CollVtx* vtx;
                float int_x;
                float int_y;
                float x;
                float y;
                float x0;
                float y0;
                float x1;
                float y1;
                float vdx;
                float vdy;
                float dist2;

                {
                    vtx = &groundCollVtx[line->inner->v0_idx];
                    x0 = vtx->pos.x;
                    y0 = vtx->pos.y;
                    x1 = vtx->prev_pos.x;
                    y1 = vtx->prev_pos.y;
                    mpRemap2d(&x, &y, a0x, a0y, a1x, a1y, b0x, b0y, b1x, b1y,
                              x1, y1);

                    vdx = x0 - x;
                    vdy = y0 - y;

                    if (SQ(vdx) + SQ(vdy) > 0.001F) {
                        if (mpLineIntersection(b0x, b0y, b1x, b1y, x, y, x0,
                                               y0, &int_x, &int_y))
                        {
                            dist2 = SQ(int_x - x1) + SQ(int_y - y1);
                            if ((vdx * (int_x - x1)) + (vdy * (int_y - y1)) <
                                0.0F)
                            {
                                dist2 = -dist2;
                            }
                            if (min_dist2 > dist2) {
                                min_dist2 = dist2;
                                if (line_id_out != NULL) {
                                    *line_id_out = line - groundCollLine;
                                }
                                result = true;
                            }
                        }
                    }
                }

                {
                    vtx = &groundCollVtx[line->inner->v1_idx];
                    x0 = vtx->pos.x;
                    y0 = vtx->pos.y;
                    x1 = vtx->prev_pos.x;
                    y1 = vtx->prev_pos.y;
                    mpRemap2d(&x, &y, a0x, a0y, a1x, a1y, b0x, b0y, b1x, b1y,
                              x1, y1);

                    vdx = x0 - x;
                    vdy = y0 - y;

                    if (SQ(vdx) + SQ(vdy) > 0.001F) {
                        if (mpLineIntersection(b0x, b0y, b1x, b1y, x, y, x0,
                                               y0, &int_x, &int_y))
                        {
                            dist2 = SQ(int_x - x1) + SQ(int_y - y1);
                            if ((vdx * (int_x - x1)) + (vdy * (int_y - y1)) <
                                0.0F)
                            {
                                dist2 = -dist2;
                            }
                            if (min_dist2 > dist2) {
                                min_dist2 = dist2;
                                if (line_id_out != NULL) {
                                    *line_id_out = line - groundCollLine;
                                }
                                result = true;
                            }
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                       .start];
            goto block_8;
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return result;
}

int mpLib_8005199C_Floor(Vec3* vec, int joint_id_skip, int joint_id_only)
{
    int line_id = -1;
    float x = vec->x;
    float y = vec->y;
    bool already_checked = mpCheckedBounding();
    CollJoint* joint;
    PAD_STACK(0x8);

    if (!already_checked) {
        mpBoundingCheck2(x, y, x, y - 30000.0F);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        if (joint->flags & CollJoint_TooFar ||
            joint_id_skip == joint - groundCollJoint)
        {
            continue;
        }

        if (joint_id_only != -1 && joint_id_only != joint - groundCollJoint) {
            continue;
        }

        {
            MapJoint* j_inner = joint->inner;
            int i;
            CollLine* line =
                &groundCollLine[j_inner->ranges[MapLineGroup_Floor].start];
            int count = j_inner->ranges[MapLineGroup_Floor].count;
            int dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
            for (i = 0; i < count; i++, line++) {
            block8:
                if (line->flags & CollLine_Floor &&
                    line->flags & LINE_FLAG_ENABLED &&
                    !(line->flags & LINE_FLAG_EMPTY))
                {
                    float x0 = groundCollVtx[line->inner->v0_idx].pos.x;
                    float y0 = groundCollVtx[line->inner->v0_idx].pos.y;
                    float x1 = groundCollVtx[line->inner->v1_idx].pos.x;
                    float y1 = groundCollVtx[line->inner->v1_idx].pos.y;

                    if (x >= x0 && x <= x1) {
                        if (y >= y0 && y >= y1) {
                            line_id = line - groundCollLine;
                            goto end;
                        }

                        if (ABS(x1 - x0) > 0.0001) {
                            float dx = x1 - x0;
                            float dy = y1 - y0;
                            if (y >= dy / dx * (x - x0) + y0) {
                                line_id = line - groundCollLine;
                                goto end;
                            }
                        }
                    }
                }
            }

            if (dynamic_count != 0) {
                count = dynamic_count;
                i = 0;
                line = &groundCollLine[j_inner->ranges[MapLineGroup_Dynamic]
                                           .start];
                dynamic_count = 0;
                goto block8;
            }
        }
    }

end:
    if (!already_checked) {
        mpUncheckBounding();
    }

    return line_id;
}

int mpLib_80051BA8_Floor(Vec3* out_vec, int line_id_skip, int joint_id_skip,
                         int joint_id_only, int dir, float left, float bottom,
                         float right, float top)
{
    float min;
    float out_x;
    float out_y;

    int ledge_id = -1;

    bool already_checked;
    int new_id;
    CollJoint* joint;

    if (dir > 0) {
        min = +F32_MAX;
    } else if (dir < 0) {
        min = -F32_MAX;
    } else {
        HSD_ASSERT(3821, 0);
    }

    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck(left, bottom, right, top);
    }

    for (joint = jointListStart; joint != NULL; joint = joint->next) {
        if (joint->flags & CollJoint_TooFar) {
            continue;
        }

        if (joint_id_skip == joint - groundCollJoint) {
            continue;
        }

        if (joint_id_only == -1 || joint_id_only == joint - groundCollJoint) {
            int i;
            CollLine* line =
                &groundCollLine[joint->inner->ranges[MapLineGroup_Floor]
                                    .start];
            int count = joint->inner->ranges[MapLineGroup_Floor].count;
            int dynamic_cout =
                joint->inner->ranges[MapLineGroup_Dynamic].count;
            for (i = 0; i < count; i++, line++) {
            reset:
                new_id = line - groundCollLine;
                if (line_id_skip == new_id) {
                    continue;
                }

                if (line->flags & CollLine_Floor &&
                    line->flags & LINE_FLAG_ENABLED &&
                    !(line->flags & LINE_FLAG_EMPTY))
                {
                    MapLine* inner = line->inner;
                    if (inner->lo_flags & LINE_FLAG_LEDGE) {
                        float x0 = groundCollVtx[inner->v0_idx].pos.x;
                        float y0 = groundCollVtx[inner->v0_idx].pos.y;
                        float x1 = groundCollVtx[inner->v1_idx].pos.x;
                        float y1 = groundCollVtx[inner->v1_idx].pos.y;
                        float line_left;
                        float line_bottom;
                        float line_right;
                        float line_top;
                        float dist_h;

                        if (x0 > x1) {
                            line_right = x0;
                            line_left = x1;
                        } else {
                            line_left = x0;
                            line_right = x1;
                        }

                        if (y0 > y1) {
                            line_top = y0;
                            line_bottom = y1;
                        } else {
                            line_bottom = y0;
                            line_top = y1;
                        }
                        // distance between midpoints of two right/left
                        // pairs
                        dist_h =
                            ABS((line_right + line_left) - (right + left));
                        if (dist_h < (line_right - line_left) + (right - left))
                        {
                            float dist_v =
                                ABS((line_top + line_bottom) - (top + bottom));
                            if (dist_v <
                                (line_top - line_bottom) + (top - bottom))
                            {
                                // we interesect in both axes
                                if (dir > 0) {
                                    if (min > x0) {
                                        min = x0;
                                        ledge_id = new_id;
                                        if (out_vec != NULL) {
                                            out_x = x0;
                                            out_y = y0;
                                        }
                                    }
                                } else if (dir < 0) {
                                    if (min < x1) {
                                        min = x1;
                                        ledge_id = new_id;
                                        if (out_vec != NULL) {
                                            out_x = x1;
                                            out_y = y1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (dynamic_cout != 0) {
                count = dynamic_cout;
                i = 0;
                line =
                    &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic]
                                        .start];
                dynamic_cout = 0;
                goto reset;
            }
        }
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    if (ledge_id != -1 && out_vec != NULL) {
        if (out_x > right) {
            out_x = right;
        } else if (out_x < left) {
            out_x = left;
        }
        out_vec->x = out_x;
        out_vec->y = out_y;
        out_vec->z = 0.0F;
    }

    return ledge_id;
}

bool mpCheckMultiple(float x0, float y0, float x1, float y1, Vec3* pos_out,
                     int* line_id_out, u32* flags_out, Vec3* normal_out,
                     u32 checks, int joint_id_skip, int joint_id_only)
{
    float dx;
    float dy;

    float min_dist2;
    bool already_checked;

    int line_id;
    u32 flags;

    Vec3 temp_pos;
    Vec3 temp_normal;
    Vec3 pos;
    Vec3 normal;
    int temp_line_id;
    u32 temp_flags;

    min_dist2 = F32_MAX;
    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck2(x0, y0, x1, y1);
    }
    if (checks & 0x10) {
        if (checks & 1 &&
            mpCheckFloorRemap(x0, y0, x1, y1, 0.0F, &temp_pos, &temp_line_id,
                              &temp_flags, &temp_normal, -1, joint_id_skip,
                              joint_id_only, NULL, NULL))
        {
            dx = SQ(temp_pos.x - x0);
            dy = SQ(temp_pos.y - y0);
            pos = temp_pos;
            normal = temp_normal;
            min_dist2 = dx + dy;
            line_id = temp_line_id;
            flags = temp_flags;
        }
        if (checks & 2 &&
            mpCheckCeilingRemap(x0, y0, x1, y1, &temp_pos, &temp_line_id,
                                &temp_flags, &temp_normal, joint_id_skip,
                                joint_id_only))
        {
            dx = SQ(temp_pos.x - x0);
            dy = SQ(temp_pos.y - y0);
            if (min_dist2 > dx + dy) {
                min_dist2 = dx + dy;
                pos = temp_pos;
                normal = temp_normal;
                line_id = temp_line_id;
                flags = temp_flags;
            }
        }
        if (checks & 4 &&
            mpCheckLeftWallRemap(x0, y0, x1, y1, &temp_pos, &temp_line_id,
                                 &temp_flags, &temp_normal, joint_id_skip,
                                 joint_id_only))
        {
            dx = SQ(temp_pos.x - x0);
            dy = SQ(temp_pos.y - y0);
            if (min_dist2 > dx + dy) {
                min_dist2 = dx + dy;
                pos = temp_pos;
                normal = temp_normal;
                line_id = temp_line_id;
                flags = temp_flags;
            }
        }
        if (checks & 8 &&
            mpCheckRightWallRemap(x0, y0, x1, y1, &temp_pos, &temp_line_id,
                                  &temp_flags, &temp_normal, joint_id_skip,
                                  joint_id_only))
        {
            dx = SQ(temp_pos.x - x0);
            dy = SQ(temp_pos.y - y0);
            if (min_dist2 > dx + dy) {
                min_dist2 = dx + dy;
                pos = temp_pos;
                normal = temp_normal;
                line_id = temp_line_id;
                flags = temp_flags;
            }
        }
    } else {
        if (checks & 1 &&
            mpCheckFloor(x0, y0, x1, y1, 0.0F, &temp_pos, &temp_line_id,
                         &temp_flags, &temp_normal, -1, joint_id_skip,
                         joint_id_only, NULL, NULL))
        {
            dx = SQ(temp_pos.x - x0);
            dy = SQ(temp_pos.y - y0);
            pos = temp_pos;
            normal = temp_normal;
            min_dist2 = dx + dy;
            line_id = temp_line_id;
            flags = temp_flags;
        }
        if (checks & 2 &&
            mpCheckCeiling(x0, y0, x1, y1, &temp_pos, &temp_line_id,
                           &temp_flags, &temp_normal, joint_id_skip,
                           joint_id_only))
        {
            dx = SQ(temp_pos.x - x0);
            dy = SQ(temp_pos.y - y0);
            if (min_dist2 > dx + dy) {
                min_dist2 = dx + dy;
                pos = temp_pos;
                normal = temp_normal;
                line_id = temp_line_id;
                flags = temp_flags;
            }
        }
        if (checks & 4 &&
            mpCheckLeftWall(x0, y0, x1, y1, &temp_pos, &temp_line_id,
                            &temp_flags, &temp_normal, joint_id_skip,
                            joint_id_only))
        {
            dx = SQ(temp_pos.x - x0);
            dy = SQ(temp_pos.y - y0);
            if (min_dist2 > dx + dy) {
                min_dist2 = dx + dy;
                pos = temp_pos;
                normal = temp_normal;
                line_id = temp_line_id;
                flags = temp_flags;
            }
        }
        if (checks & 8 &&
            mpCheckRightWall(x0, y0, x1, y1, &temp_pos, &temp_line_id,
                             &temp_flags, &temp_normal, joint_id_skip,
                             joint_id_only))
        {
            dx = SQ(temp_pos.x - x0);
            dy = SQ(temp_pos.y - y0);
            if (min_dist2 > dx + dy) {
                min_dist2 = dx + dy;
                pos = temp_pos;
                normal = temp_normal;
                line_id = temp_line_id;
                flags = temp_flags;
            }
        }
    }
    if (!already_checked) {
        mpUncheckBounding();
    }
    if (min_dist2 < F32_MAX) {
        if (pos_out != NULL) {
            *pos_out = pos;
        }
        if (line_id_out != NULL) {
            *line_id_out = line_id;
        }
        if (flags_out != NULL) {
            *flags_out = flags;
        }
        if (normal_out != NULL) {
            *normal_out = normal;
        }
        return true;
    }
    return false;
}

bool mpCheckAllRemap(Vec3* pos_out, int* line_id_out, u32* flags_out,
                     Vec3* normal_out, int joint_id_skip, int joint_id_only,
                     float x0, float y0, float x1, float y1)
{
    return mpCheckMultiple(x0, y0, x1, y1, pos_out, line_id_out, flags_out,
                           normal_out, 0x1F, joint_id_skip, joint_id_only);
}

bool mpCheckAll(Vec3* pos_out, int* line_id_out, u32* flags_out,
                Vec3* normal_out, int joint_id_skip, int joint_id_only,
                float x0, float y0, float x1, float y1)
{
    return mpCheckMultiple(x0, y0, x1, y1, pos_out, line_id_out, flags_out,
                           normal_out, 0xF, joint_id_skip, joint_id_only);
}

static inline int mpLineGetNextCheckInline(MapLine* line, s16 result)
{
    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v1 = &groundCollVtx[line->v1_idx];
            CollVtx* v0 = &groundCollVtx[groundCollLine[result].inner->v0_idx];

            if (SQ(v1->pos.x - v0->pos.x) + SQ(v1->pos.y - v0->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return line->next_id0;
}

static inline int mpLineGetPrevCheckInline(MapLine* line, s16 result)
{
    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v0 = &groundCollVtx[line->v0_idx];
            CollVtx* v1 = &groundCollVtx[groundCollLine[result].inner->v1_idx];

            if (SQ(v0->pos.x - v1->pos.x) + SQ(v0->pos.y - v1->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return line->prev_id0;
}

static inline int mpLineGetPrevCheckInlineVtx(MapLine* line, s16 result,
                                              CollVtx* vtx)
{
    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v0 = &vtx[line->v0_idx];
            CollVtx* v1 = &vtx[groundCollLine[result].inner->v1_idx];

            if (SQ(v0->pos.x - v1->pos.x) + SQ(v0->pos.y - v1->pos.y) < 4.0) {
                return result;
            }
        }
    }

    result = line->prev_id0;
    return result;
}

static inline int mpLineGetNextCheckInlineVtx(MapLine* line, s16 result,
                                              CollVtx* vtx)
{
    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v1 = &vtx[line->v1_idx];
            CollVtx* v0 = &vtx[groundCollLine[result].inner->v0_idx];

            if (SQ(v1->pos.x - v0->pos.x) + SQ(v1->pos.y - v0->pos.y) < 4.0) {
                return result;
            }
        }
    }

    result = line->next_id0;
    return result;
}

/// Return @p new_id unless the line walk dead-ended or looped back.
static inline int mpLineIterNonResult(int new_id, int line_id)
{
    bool valid_id = false;
    if ((new_id != -1) && (new_id != line_id)) {
        valid_id = true;
    }
    if (valid_id) {
        return new_id;
    }
    return -1;
}

int mpLineNextNonFloor(int line_id)
{
    MapLine* first_line;
    MapLine* line;
    int new_id;
    LINEID_CHECK(4139, line_id);
    first_line = groundCollLine[line_id].inner;
    new_id = mpLineGetNextCheckInline(first_line, first_line->next_id1);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_Floor)
    {
        line = groundCollLine[new_id].inner;
        new_id = line->next_id1;
        new_id = mpLineGetNextCheckInlineVtx(line, new_id, groundCollVtx);
    }
    return mpLineIterNonResult(new_id, line_id);
}

int mpLinePrevNonFloor(int line_id)
{
    MapLine* first_line;
    MapLine* line;
    int new_id;
    LINEID_CHECK(4148, line_id);
    first_line = groundCollLine[line_id].inner;
    new_id = mpLineGetPrevCheckInline(first_line, first_line->prev_id1);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_Floor)
    {
        line = groundCollLine[new_id].inner;
        new_id = line->prev_id1;
        new_id = mpLineGetPrevCheckInlineVtx(line, new_id, groundCollVtx);
    }
    return mpLineIterNonResult(new_id, line_id);
}

int mpLinePrevNonCeiling(int line_id)
{
    MapLine* first_line;
    MapLine* line;
    int new_id;
    LINEID_CHECK(4157, line_id);
    first_line = groundCollLine[line_id].inner;
    new_id = mpLineGetPrevCheckInline(first_line, first_line->prev_id1);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_Ceiling)
    {
        line = groundCollLine[new_id].inner;
        new_id = line->prev_id1;
        new_id = mpLineGetPrevCheckInlineVtx(line, new_id, groundCollVtx);
    }
    return mpLineIterNonResult(new_id, line_id);
}

int mpLineNextNonCeiling(int line_id)
{
    MapLine* first_line;
    MapLine* line;
    int new_id;
    LINEID_CHECK(4166, line_id);
    first_line = groundCollLine[line_id].inner;
    new_id = mpLineGetNextCheckInline(first_line, first_line->next_id1);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_Ceiling)
    {
        line = groundCollLine[new_id].inner;
        new_id = line->next_id1;
        new_id = mpLineGetNextCheckInlineVtx(line, new_id, groundCollVtx);
    }
    return mpLineIterNonResult(new_id, line_id);
}

int mpLineNextNonLeftWall(int line_id)
{
    MapLine* first_line;
    MapLine* line;
    int new_id;
    LINEID_CHECK(4175, line_id);
    first_line = groundCollLine[line_id].inner;
    new_id = mpLineGetNextCheckInline(first_line, first_line->next_id1);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_LeftWall)
    {
        line = groundCollLine[new_id].inner;
        new_id = line->next_id1;
        new_id = mpLineGetNextCheckInlineVtx(line, new_id, groundCollVtx);
    }
    return mpLineIterNonResult(new_id, line_id);
}

int mpLinePrevNonLeftWall(int line_id)
{
    MapLine* first_line;
    MapLine* line;
    int new_id;
    LINEID_CHECK(4184, line_id);
    first_line = groundCollLine[line_id].inner;
    new_id = mpLineGetPrevCheckInline(first_line, first_line->prev_id1);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_LeftWall)
    {
        line = groundCollLine[new_id].inner;
        new_id = line->prev_id1;
        new_id = mpLineGetPrevCheckInlineVtx(line, new_id, groundCollVtx);
    }
    return mpLineIterNonResult(new_id, line_id);
}

int mpLinePrevNonRightWall(int line_id)
{
    MapLine* first_line;
    MapLine* line;
    int new_id;
    LINEID_CHECK(4193, line_id);
    first_line = groundCollLine[line_id].inner;
    new_id = mpLineGetPrevCheckInline(first_line, first_line->prev_id1);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_RightWall)
    {
        line = groundCollLine[new_id].inner;
        new_id = line->prev_id1;
        new_id = mpLineGetPrevCheckInlineVtx(line, new_id, groundCollVtx);
    }
    return mpLineIterNonResult(new_id, line_id);
}

int mpLineNextNonRightWall(int line_id)
{
    MapLine* first_line;
    MapLine* line;
    int new_id;
    LINEID_CHECK(4202, line_id);
    first_line = groundCollLine[line_id].inner;
    new_id = mpLineGetNextCheckInline(first_line, first_line->next_id1);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_RightWall)
    {
        line = groundCollLine[new_id].inner;
        new_id = line->next_id1;
        new_id = mpLineGetNextCheckInlineVtx(line, new_id, groundCollVtx);
    }
    return mpLineIterNonResult(new_id, line_id);
}

/// Walk the next/prev chain from @p line_id while lines still have @p kind
/// set; return the first line without it, or -1.
static inline int mpLineWalkNon(int line_id, int kind, bool next)
{
    int new_id;
    if (next) {
        new_id = groundCollLine[line_id].inner->next_id0;
        while (new_id != -1 && groundCollLine[new_id].flags & kind) {
            new_id = groundCollLine[new_id].inner->next_id0;
        }
    } else {
        new_id = groundCollLine[line_id].inner->prev_id0;
        while (new_id != -1 && groundCollLine[new_id].flags & kind) {
            new_id = groundCollLine[new_id].inner->prev_id0;
        }
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

int mpLib_80053394_Floor(int line_id)
{
    LINEID_CHECK(4252, line_id);
    return mpLineWalkNon(line_id, CollLine_Floor, true);
}

int mpLib_80053448_Floor(int line_id)
{
    LINEID_CHECK(4261, line_id);
    return mpLineWalkNon(line_id, CollLine_Floor, false);
}

static inline int mpLineGetNextInline(int line_id)
{
    s32 result = groundCollLine[line_id].inner->next_id1;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v1 =
                &groundCollVtx[groundCollLine[line_id].inner->v1_idx];
            CollVtx* v0 = &groundCollVtx[groundCollLine[result].inner->v0_idx];

            if (SQ(v1->pos.x - v0->pos.x) + SQ(v1->pos.y - v0->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return groundCollLine[line_id].inner->next_id0;
}

static inline int mpLineGetNextCachedInline(int line_id)
{
    MapLine* line;
    int result = (line = groundCollLine[line_id].inner)->next_id1;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v1 = &groundCollVtx[line->v1_idx];
            CollVtx* v0 = &groundCollVtx[groundCollLine[result].inner->v0_idx];

            if (SQ(v1->pos.x - v0->pos.x) + SQ(v1->pos.y - v0->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return line->next_id0;
}

static inline int mpLineGetNextChecked(MapLine* line)
{
    int result = line->next_id1;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v1 = &groundCollVtx[line->v1_idx];
            CollVtx* v0 = &groundCollVtx[groundCollLine[result].inner->v0_idx];

            if (SQ(v1->pos.x - v0->pos.x) + SQ(v1->pos.y - v0->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return line->next_id0;
}

int mpLib_800534FC_Floor(int line_id)
{
    MapLine* line;
    int result;
    int new_id;
    LINEID_CHECK(4272, line_id);
    new_id = mpLineGetNextCachedInline(line_id);
    while (new_id != -1) {
        if (!(groundCollLine[new_id].flags & CollLine_Floor)) {
            new_id = -1;
        } else if (new_id != groundCollLine[line_id].inner->next_id1) {
            line_id = new_id;
            new_id =
                mpLineGetNextChecked(line = groundCollLine[line_id].inner);
            continue;
        }
        break;
    }
    if (new_id != -1) {
        result = new_id;
    } else {
        result = -1;
    }
    return result;
}

static inline int mpLineGetPrevInline(int line_id)
{
    MapLine* line;
    int result = (line = groundCollLine[line_id].inner)->prev_id1;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v0 = &groundCollVtx[line->v0_idx];
            CollVtx* v1 = &groundCollVtx[groundCollLine[result].inner->v1_idx];

            if (SQ(v0->pos.x - v1->pos.x) + SQ(v0->pos.y - v1->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return line->prev_id0;
}

static inline int mpLineGetPrevChecked(MapLine* line)
{
    int result = line->prev_id1;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v0 = &groundCollVtx[line->v0_idx];
            CollVtx* v1 = &groundCollVtx[groundCollLine[result].inner->v1_idx];

            if (SQ(v0->pos.x - v1->pos.x) + SQ(v0->pos.y - v1->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return line->prev_id0;
}

int mpLib_800536CC_Floor(int line_id)
{
    MapLine* line;
    int new_id;
    int result;
    LINEID_CHECK(4293, line_id);
    new_id = mpLineGetPrevInline(line_id);
    while (new_id != -1) {
        if (!(groundCollLine[new_id].flags & CollLine_Floor)) {
            new_id = -1;
        } else if (new_id != groundCollLine[line_id].inner->prev_id1) {
            line_id = new_id;
            new_id =
                mpLineGetPrevChecked(line = groundCollLine[line_id].inner);
            continue;
        }
        break;
    }
    if (new_id != -1) {
        result = new_id;
    } else {
        result = -1;
    }
    return result;
}

int mpLib_8005389C_Ceiling(int line_id)
{
    LINEID_CHECK(4314, line_id);
    return mpLineWalkNon(line_id, CollLine_Ceiling, false);
}

int mpLib_80053950_Ceiling(int line_id)
{
    LINEID_CHECK(4323, line_id);
    return mpLineWalkNon(line_id, CollLine_Ceiling, true);
}

int mpLib_80053A04_Ceiling(int line_id)
{
    MapLine* line;
    int result;
    int new_id;
    LINEID_CHECK(4334, line_id);
    new_id = mpLineGetPrevInline(line_id);
    while (new_id != -1) {
        if (!(groundCollLine[new_id].flags & CollLine_Ceiling)) {
            new_id = -1;
        } else if (new_id != groundCollLine[line_id].inner->prev_id1) {
            line_id = new_id;
            new_id =
                mpLineGetPrevChecked(line = groundCollLine[line_id].inner);
            continue;
        }
        break;
    }
    if (new_id != -1) {
        result = new_id;
    } else {
        result = -1;
    }
    return result;
}

int mpLib_80053BD4_Ceiling(int line_id)
{
    int result;
    int new_id;
    LINEID_CHECK(4355, line_id);
    new_id = mpLineGetNextInline(line_id);
    while (new_id != -1) {
        if (!(groundCollLine[new_id].flags & CollLine_Ceiling)) {
            new_id = -1;
        } else if (new_id != groundCollLine[line_id].inner->next_id1) {
            line_id = new_id;
            new_id = mpLineGetNextInline(new_id);
            continue;
        }
        break;
    }
    if (new_id != -1) {
        result = new_id;
    } else {
        result = -1;
    }
    return result;
}

void mpLib_80053DA4_Floor(int line_id, Vec3* pos_out)
{
    s16 next_id;
    CollVtx* vtx;

    LINEID_CHECK(4428, line_id);

    goto skip;
loop:
    line_id = next_id;
skip:
    next_id = groundCollLine[line_id].inner->next_id0;
    if (next_id != -1 && (groundCollLine[next_id].flags & CollLine_Floor)) {
        goto loop;
    }

    LINEID_CHECK(4433, line_id);

    vtx = &groundCollVtx[groundCollLine[line_id].inner->v1_idx];
    pos_out->x = vtx->pos.x;
    pos_out->y = vtx->pos.y;
    pos_out->z = 0.0F;
}

void mpLib_80053ECC_Floor(int line_id, Vec* vec)
{
    s16 prev_id;
    CollVtx* vtx;

    LINEID_CHECK(4448, line_id);

    goto skip;
loop:
    line_id = prev_id;
skip:
    prev_id = groundCollLine[line_id].inner->prev_id0;
    if (prev_id != -1 && (groundCollLine[prev_id].flags & CollLine_Floor)) {
        goto loop;
    }

    LINEID_CHECK(4453, line_id);

    vtx = &groundCollVtx[groundCollLine[line_id].inner->v0_idx];
    vec->x = vtx->pos.x;
    vec->y = vtx->pos.y;
    vec->z = 0.0F;
}

static inline u32 mpLineGetKindInline(int line_id)
{
    return groundCollLine[line_id].flags & LINE_FLAG_KIND;
}

/// Single-member wrapper for the line being walked.
struct mpLineWalk {
    int id;
};

void mpFloorGetRight(int line_id, Vec3* pos_out)
{
    u32 kind;
    struct mpLineWalk w;

    LINEID_CHECK(4465, line_id);

    w.id = line_id;
    kind = mpLineGetKindInline(line_id);
    for (;;) {
        MapLine* line = groundCollLine[w.id].inner;
        int next = line->next_id1;

        line_id = mpLineGetNextCheckInline(line, next);
        if (line_id == -1 ||
            kind != (groundCollLine[line_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
        w.id = line_id;
    }
    {
        CollVtx* vtx = &groundCollVtx[groundCollLine[w.id].inner->v1_idx];
        pos_out->x = vtx->pos.x;
        pos_out->y = vtx->pos.y;
        pos_out->z = 0.0F;
    }
}

void mpFloorGetLeft(int line_id, Vec3* pos_out)
{
    u32 kind;
    struct mpLineWalk w;

    LINEID_CHECK(4474, line_id);

    w.id = line_id;
    kind = mpLineGetKindInline(line_id);
    for (;;) {
        MapLine* line = groundCollLine[w.id].inner;
        int next = line->prev_id1;

        line_id = mpLineGetPrevCheckInline(line, next);
        if (line_id == -1 ||
            kind != (groundCollLine[line_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
        w.id = line_id;
    }
    {
        CollVtx* vtx = &groundCollVtx[groundCollLine[w.id].inner->v0_idx];
        pos_out->x = vtx->pos.x;
        pos_out->y = vtx->pos.y;
        pos_out->z = 0.0F;
    }
}

void mpCeilingGetRight(int line_id, Vec3* pos_out)
{
    u32 kind;
    struct mpLineWalk w;

    LINEID_CHECK(4483, line_id);

    w.id = line_id;
    kind = mpLineGetKindInline(line_id);
    for (;;) {
        MapLine* line = groundCollLine[w.id].inner;
        int next = line->prev_id1;

        line_id = mpLineGetPrevCheckInline(line, next);
        if (line_id == -1 ||
            kind != (groundCollLine[line_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
        w.id = line_id;
    }
    {
        CollVtx* vtx = &groundCollVtx[groundCollLine[w.id].inner->v0_idx];
        pos_out->x = vtx->pos.x;
        pos_out->y = vtx->pos.y;
        pos_out->z = 0.0F;
    }
}

void mpCeilingGetLeft(int line_id, Vec3* pos_out)
{
    u32 kind;
    struct mpLineWalk w;

    LINEID_CHECK(4492, line_id);

    w.id = line_id;
    kind = mpLineGetKindInline(line_id);
    for (;;) {
        MapLine* line = groundCollLine[w.id].inner;
        int next = line->next_id1;

        line_id = mpLineGetNextCheckInline(line, next);
        if (line_id == -1 ||
            kind != (groundCollLine[line_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
        w.id = line_id;
    }
    {
        CollVtx* vtx = &groundCollVtx[groundCollLine[w.id].inner->v1_idx];
        pos_out->x = vtx->pos.x;
        pos_out->y = vtx->pos.y;
        pos_out->z = 0.0F;
    }
}

void mpLeftWallGetTop(int line_id, Vec3* pos_out)
{
    u32 kind;
    struct mpLineWalk w;

    LINEID_CHECK(4501, line_id);

    w.id = line_id;
    kind = mpLineGetKindInline(line_id);
    for (;;) {
        MapLine* line = groundCollLine[w.id].inner;
        int next = line->next_id1;

        line_id = mpLineGetNextCheckInline(line, next);
        if (line_id == -1 ||
            kind != (groundCollLine[line_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
        w.id = line_id;
    }
    {
        CollVtx* vtx = &groundCollVtx[groundCollLine[w.id].inner->v1_idx];
        pos_out->x = vtx->pos.x;
        pos_out->y = vtx->pos.y;
        pos_out->z = 0.0F;
    }
}

void mpLeftWallGetBottom(int line_id, Vec3* pos_out)
{
    u32 kind;
    struct mpLineWalk w;

    LINEID_CHECK(4510, line_id);

    w.id = line_id;
    kind = mpLineGetKindInline(line_id);
    for (;;) {
        MapLine* line = groundCollLine[w.id].inner;
        int next = line->prev_id1;

        line_id = mpLineGetPrevCheckInline(line, next);
        if (line_id == -1 ||
            kind != (groundCollLine[line_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
        w.id = line_id;
    }
    {
        CollVtx* vtx = &groundCollVtx[groundCollLine[w.id].inner->v0_idx];
        pos_out->x = vtx->pos.x;
        pos_out->y = vtx->pos.y;
        pos_out->z = 0.0F;
    }
}

void mpRightWallGetTop(int line_id, Vec3* pos_out)
{
    u32 kind;
    struct mpLineWalk w;

    LINEID_CHECK(4519, line_id);

    w.id = line_id;
    kind = mpLineGetKindInline(line_id);
    for (;;) {
        MapLine* line = groundCollLine[w.id].inner;
        int next = line->prev_id1;

        line_id = mpLineGetPrevCheckInline(line, next);
        if (line_id == -1 ||
            kind != (groundCollLine[line_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
        w.id = line_id;
    }
    {
        CollVtx* vtx = &groundCollVtx[groundCollLine[w.id].inner->v0_idx];
        pos_out->x = vtx->pos.x;
        pos_out->y = vtx->pos.y;
        pos_out->z = 0.0F;
    }
}

void mpRightWallGetBottom(int line_id, Vec3* pos_out)
{
    u32 kind;
    struct mpLineWalk w;

    LINEID_CHECK(4528, line_id);

    w.id = line_id;
    kind = mpLineGetKindInline(line_id);
    for (;;) {
        MapLine* line = groundCollLine[w.id].inner;
        int next = line->next_id1;

        line_id = mpLineGetNextCheckInline(line, next);
        if (line_id == -1 ||
            kind != (groundCollLine[line_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
        w.id = line_id;
    }
    {
        CollVtx* vtx = &groundCollVtx[groundCollLine[w.id].inner->v1_idx];
        pos_out->x = vtx->pos.x;
        pos_out->y = vtx->pos.y;
        pos_out->z = 0.0F;
    }
}

void mpLineGetV1Pos(int line_id, Vec3* pos_out)
{
    CollVtx* v1;

    LINEID_CHECK(4540, line_id);
    v1 = &groundCollVtx[groundCollLine[line_id].inner->v1_idx];
    pos_out->x = v1->pos.x;
    pos_out->y = v1->pos.y;
    pos_out->z = 0.0F;
}

void mpLineGetV0Pos(int line_id, Vec3* pos_out)
{
    CollVtx* v0;

    LINEID_CHECK(4555, line_id);
    v0 = &groundCollVtx[groundCollLine[line_id].inner->v0_idx];
    pos_out->x = v0->pos.x;
    pos_out->y = v0->pos.y;
    pos_out->z = 0.0F;
}

enum_t mpLineGetKind(int line_id)
{
    LINEID_CHECK(4573, line_id);
    return groundCollLine[line_id].flags & LINE_FLAG_KIND;
}

u32 mpLineGetFlags(int line_id)
{
    LINEID_CHECK(4583, line_id);
    return groundCollLine[line_id].inner->lo_flags;
}

void mpLib_80054D68(int line_id, u32 flags)
{
    LINEID_CHECK(4595, line_id);
    {
        MapLine* line = groundCollLine[line_id].inner;
        u16* old_flags = &line->lo_flags;
        *old_flags = (*old_flags & ~0xFF) | flags;
    }
}

Vec3* mpLineGetNormal(int line_id, Vec3* normal_out)
{
    MapLine* line;
    PAD_STACK(4);

    LINEID_CHECK(4609, line_id);
    line = groundCollLine[line_id].inner;
    {
        float y0 = groundCollVtx[line->v0_idx].pos.y;
        float y1 = groundCollVtx[line->v1_idx].pos.y;
        float x0 = groundCollVtx[line->v0_idx].pos.x;
        float x1 = groundCollVtx[line->v1_idx].pos.x;
        normal_out->x = -(y1 - y0);
        normal_out->y = +(x1 - x0);
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }
    return normal_out;
}

bool mpLib_80054ED8(int line_id)
{
    if (line_id == -1) {
        return false;
    }
    if (line_id < 0 || line_id >= mpLib_804D64B4->line_count) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 4636, line_id);
        while (true) {
        };
    }
    if (!(groundCollLine[line_id].flags & LINE_FLAG_ENABLED) ||
        groundCollLine[line_id].flags & LINE_FLAG_HIDDEN)
    {
        return false;
    }
    return true;
}

static inline int mpLineGetNextFrom(MapLine* line, const u32* flags_base)
{
    int result = line->next_id1;

    if (result != -1) {
        u32 flags = flags_base[result * 2];

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v1 = &groundCollVtx[line->v1_idx];
            CollVtx* v0 = &groundCollVtx[groundCollLine[result].inner->v0_idx];

            if (SQ(v1->pos.x - v0->pos.x) + SQ(v1->pos.y - v0->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return line->next_id0;
}

static inline int mpLineGetPrevFrom(MapLine* line, const u32* flags_base)
{
    int result = line->prev_id1;

    if (result != -1) {
        u32 flags = flags_base[result * 2];

        if ((flags & LINE_FLAG_ENABLED) && !(flags & LINE_FLAG_HIDDEN)) {
            CollVtx* v0 = &groundCollVtx[line->v0_idx];
            CollVtx* v1 = &groundCollVtx[groundCollLine[result].inner->v1_idx];

            if (SQ(v0->pos.x - v1->pos.x) + SQ(v0->pos.y - v1->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return line->prev_id0;
}

bool mpLinesConnected(int start_id, int target_id)
{
    int line_id;
    u32 kind;
    MapLine* start_line;
    u32* flags_base;

    LINEID_CHECK(4656, start_id);
    LINEID_CHECK(4657, target_id);
    if (start_id == target_id) {
        return true;
    }

    start_line = groundCollLine[start_id].inner;
    flags_base = &groundCollLine->flags;
    kind = flags_base[start_id * 2] & LINE_FLAG_KIND;
    line_id = mpLineGetNextFrom(start_line, flags_base);
    while (line_id != -1 &&
           kind == (groundCollLine[line_id].flags & LINE_FLAG_KIND))
    {
        if (line_id == target_id) {
            return true;
        }

        line_id = mpLineGetNext(line_id);
    }

    line_id = mpLineGetPrevFrom(start_line, flags_base);
    while (line_id != -1 &&
           kind == (groundCollLine[line_id].flags & LINE_FLAG_KIND))
    {
        if (line_id == target_id) {
            return true;
        }

        line_id = mpLineGetPrev(line_id);
    }

    return false;
}

/// what even is this lol
void mpLib_800552B0(int joint_id, HSD_JObj* jobj, int z)
{
    s32 i;
    HSD_JObj* cur;

    for (cur = HSD_JObjGetChild(jobj), i = 0; cur != NULL && i != z; i++) {
        if (!(cur->flags & CollJoint_TooFar)) {
            if (HSD_JObjGetChild(cur) != NULL) {
                cur = HSD_JObjGetChild(cur);
                continue;
            }
        }

        if (HSD_JObjGetNext(cur) != NULL) {
            cur = HSD_JObjGetNext(cur);
            continue;
        }

        while (true) {
            if (HSD_JObjGetParent(cur) == NULL) {
                cur = NULL;
            } else {
                if (HSD_JObjGetNext(HSD_JObjGetParent(cur)) != NULL) {
                    cur = HSD_JObjGetNext(HSD_JObjGetParent(cur));
                } else {
                    cur = HSD_JObjGetParent(cur);
                    continue;
                }
            }
            break;
        }
    }

    if (cur != NULL) {
        CollJoint* joint = &groundCollJoint[joint_id];
        joint->jobj = cur;
    }
}

void mpJointHide(int joint_id)
{
    CollJoint* joint;
    CollLine* line;
    int count;

    joint = &groundCollJoint[joint_id];
    joint->flags |= CollJoint_Hidden;

    count = joint->inner->ranges[MapLineGroup_Floor].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_Floor].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_HIDDEN;
        line++;
    }

    count = joint->inner->ranges[MapLineGroup_Ceiling].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_Ceiling].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_HIDDEN;
        line++;
    }

    count = joint->inner->ranges[MapLineGroup_LeftWall].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_LeftWall].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_HIDDEN;
        line++;
    }

    count = joint->inner->ranges[MapLineGroup_RightWall].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_RightWall].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_HIDDEN;
        line++;
    }

    count = joint->inner->ranges[MapLineGroup_Dynamic].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_HIDDEN;
        line++;
    }
}

void mpJointUnhide(int joint_id)
{
    CollJoint* joint;
    CollLine* line;
    CollVtx* vtx;
    int count;
    int i;

    joint = &groundCollJoint[joint_id];
    joint->flags &= ~CollJoint_Hidden;

    count = joint->inner->ranges[MapLineGroup_Floor].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_Floor].start];
    while (count-- > 0) {
        line->flags &= ~LINE_FLAG_HIDDEN;
        line++;
    }

    count = joint->inner->ranges[MapLineGroup_Ceiling].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_Ceiling].start];
    while (count-- > 0) {
        line->flags &= ~LINE_FLAG_HIDDEN;
        line++;
    }

    count = joint->inner->ranges[MapLineGroup_LeftWall].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_LeftWall].start];
    while (count-- > 0) {
        line->flags &= ~LINE_FLAG_HIDDEN;
        line++;
    }

    count = joint->inner->ranges[MapLineGroup_RightWall].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_RightWall].start];
    while (count-- > 0) {
        line->flags &= ~LINE_FLAG_HIDDEN;
        line++;
    }

    count = joint->inner->ranges[MapLineGroup_Dynamic].count;
    line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic].start];
    while (count-- > 0) {
        line->flags &= ~LINE_FLAG_HIDDEN;
        line++;
    }

    vtx = &groundCollVtx[joint->inner->vtx_start];
    for (i = joint->inner->vtx_count; i > 0; i--, vtx++) {
        vtx->prev_pos.x = vtx->pos.x;
        vtx->prev_pos.y = vtx->pos.y;
    }
}

void mpJointUpdateDynamics(int joint_id)
{
    const double TAN30 = 0.577350295784245;
    const double TAN60 = 1.7320508368950045;
    CollJoint* joint = &groundCollJoint[joint_id];
    CollLine* line;
    int i;
    s16 count = joint->inner->ranges[MapLineGroup_Dynamic].count;
    u32 kind;

    line = &groundCollLine[joint->inner->ranges[MapLineGroup_Dynamic].start];

    for (i = 0; i < count; i++, line++) {
        MapLine* temp = line->inner;
        CollVtx* v1 = &groundCollVtx[temp->v1_idx];
        CollVtx* v0 = &groundCollVtx[temp->v0_idx];
        float dx = v1->pos.x - v0->pos.x;
        float dy = v1->pos.y - v0->pos.y;
        if (dx > 0.0F) {
            if (dy / dx > TAN60) {
                kind = CollLine_LeftWall;
            } else if (dy / dx < -TAN60) {
                kind = CollLine_RightWall;
            } else {
                kind = CollLine_Floor;
            }
        } else if (dx < 0.0F) {
            if (dy / dx > TAN30) {
                kind = CollLine_RightWall;
            } else if (dy / dx < -TAN30) {
                kind = CollLine_LeftWall;
            } else {
                kind = CollLine_Ceiling;
            }
        } else if (dy > 0.0F) {
            kind = CollLine_LeftWall;
        } else if (dy < 0.0F) {
            kind = CollLine_RightWall;
        } else {
            HSD_ASSERT(4884, 0);
        }
        line->flags = (line->flags & ~LINE_FLAG_KIND) | kind;
        if (joint->flags & CollJoint_Enabled && line->inner->lo_flags & 0x400)
        {
            if (kind & CollLine_Floor) {
                line->flags |= LINE_FLAG_ENABLED | LINE_FLAG_PLATFORM;
                line->inner->lo_flags |= LINE_FLAG_PLATFORM;
            } else {
                line->flags &= ~LINE_FLAG_ENABLED;
            }
        }
    }
}

void mpLib_80055E24(int joint_id)
{
    bool flag;
    CollJoint* joint = &groundCollJoint[joint_id];

    mpJointUpdateDynamics(joint_id);
    flag = false;
    if (!(joint->flags & (CollJoint_Hidden | CollJoint_B11)) &&
        joint->flags & CollJoint_Enabled)
    {
        flag = true;
    }
    mpIsland_8005B334(joint_id, joint->inner->vtx_start,
                      joint->inner->vtx_count, flag);
}

void mpLib_80055E9C(int joint_id)
{
    float corner_y;
    float corner_x;
    float hi;
    float lo;
    float corner2_x;
    float corner2_y;
    u8 _[4];
    float m0_3;
    float m1_3;
    float m0_0;
    CollJoint* joint;
    HSD_JObj* jobj;
    int vtx_count;
    CollVtx* vtx;
    int unchanged;
    CollVtx* v;
    bool flag;
    MtxPtr mtx;
    int i;
    Vec3 pt;
    PAD_STACK(0x14);

    mpColl_804D64AC += 1;
    joint = &groundCollJoint[joint_id];
    vtx_count = joint->inner->vtx_count;
    v = &groundCollVtx[joint->inner->vtx_start];
    for (i = 0; i < vtx_count; i++, v++) {
        v->prev_pos.x = v->pos.x;
        v->prev_pos.y = v->pos.y;
    }
    jobj = joint->jobj;
    if (jobj == NULL) {
        return;
    }

    if (HSD_JObjGetFlags(jobj) & JOBJ_HIDDEN) {
        if (!(joint->flags & CollJoint_Hidden)) {
            mpJointHide(joint_id);
            flag = false;
            if (!(joint->flags & (CollJoint_Hidden | CollJoint_B11)) &&
                joint->flags & CollJoint_Enabled)
            {
                flag = true;
            }
            mpIsland_8005B334(joint_id, joint->inner->vtx_start,
                              joint->inner->vtx_count, flag);
        }
        return;
    }

    joint->xE = true;
    unchanged = 0;
    HSD_JObjSetupMatrix(jobj);
    mtx = HSD_JObjGetMtxPtr(jobj);
    m0_0 = ((volatile float*) mtx)[0];
    if (m0_0 == mtx[1][1] && m0_0 == mtx[2][2]) {
        m0_3 = mtx[0][3];
        m1_3 = mtx[1][3];
        v = &groundCollVtx[joint->inner->vtx_start];
        for (i = 0; i < vtx_count; i++, v++) {
            v->pos.x = v->base_pos.x * m0_0 + m0_3;
            v->pos.y = v->base_pos.y * m0_0 + m1_3;
        }
        joint->bounding_min.x =
            (joint->inner->left_bound * m0_0 + m0_3) - 30.0F;
        joint->bounding_min.y =
            (joint->inner->bottom_bound * m0_0 + m1_3) - 30.0F;
        joint->bounding_max.x =
            30.0F + (joint->inner->right_bound * m0_0 + m0_3);
        joint->bounding_max.y =
            30.0F + (joint->inner->top_bound * m0_0 + m1_3);
        joint->flags |= CollJoint_B8;
        goto after0;
    }

    i = 0;
    vtx = &groundCollVtx[joint->inner->vtx_start];
    corner_y = 0.0F;

    while (i < vtx_count) {
        pt.x = vtx->base_pos.x;
        pt.y = vtx->base_pos.y;
        pt.z = corner_y;
        PSMTXMultVec(jobj->mtx, &pt, &pt);
        vtx->pos.x = pt.x;
        vtx->pos.y = pt.y;
        if (mpLib_804D64CC == 0 || vtx->pos.x != vtx->prev_pos.x ||
            vtx->pos.y != vtx->prev_pos.y || (++unchanged <= 1))
        {
            i += 1;
            vtx += 1;
        } else {
            goto after1;
        }
    }
    {
        mtx = HSD_JObjGetMtxPtr(jobj);
        if (mtx[0][1] != 0.0F || mtx[0][2] != 0.0F || mtx[1][0] != 0.0F ||
            mtx[1][2] != 0.0F || mtx[2][0] != 0.0F || mtx[2][1] != 0.0F)
        {
            joint->flags |= CollJoint_B9;
        }
        joint->flags |= CollJoint_B8;
        if (!(joint->flags & CollJoint_B10)) {
            pt.x = joint->inner->left_bound;
            pt.y = joint->inner->bottom_bound;
            pt.z = 0.0F;
            PSMTXMultVec(jobj->mtx, &pt, &pt);
            joint->bounding_min.x = pt.x;
            joint->bounding_min.y = pt.y;
            pt.x = joint->inner->right_bound;
            pt.y = joint->inner->top_bound;
            pt.z = 0.0F;
            PSMTXMultVec(jobj->mtx, &pt, &pt);
            joint->bounding_max.x = pt.x;
            joint->bounding_max.y = pt.y;
            if (joint->flags & CollJoint_B9) {
                pt.x = joint->inner->right_bound;
                pt.y = joint->inner->bottom_bound;
                pt.z = 0.0F;
                PSMTXMultVec(jobj->mtx, &pt, &pt);
                corner_x = pt.x;
                corner_y = pt.y;
                pt.x = joint->inner->left_bound;
                pt.y = joint->inner->top_bound;
                pt.z = 0.0F;
                PSMTXMultVec(jobj->mtx, &pt, &pt);
                lo = joint->bounding_min.x;
                hi = joint->bounding_max.x;
                corner2_x = pt.x;
                corner2_y = pt.y;
                if (lo > hi) {
                    joint->bounding_min.x = hi;
                }
                if (joint->bounding_min.x > corner_x) {
                    joint->bounding_min.x = corner_x;
                }
                if (joint->bounding_min.x > corner2_x) {
                    joint->bounding_min.x = corner2_x;
                }
                if (joint->bounding_max.x < lo) {
                    joint->bounding_max.x = lo;
                }
                if (joint->bounding_max.x < corner_x) {
                    joint->bounding_max.x = corner_x;
                }
                if (joint->bounding_max.x < corner2_x) {
                    joint->bounding_max.x = corner2_x;
                }
                lo = joint->bounding_min.y;
                hi = joint->bounding_max.y;
                if (lo > hi) {
                    joint->bounding_min.y = hi;
                }
                if (joint->bounding_min.y > corner_y) {
                    joint->bounding_min.y = corner_y;
                }
                if (joint->bounding_min.y > corner2_y) {
                    joint->bounding_min.y = corner2_y;
                }
                if (joint->bounding_max.y < lo) {
                    joint->bounding_max.y = lo;
                }
                if (joint->bounding_max.y < corner_y) {
                    joint->bounding_max.y = corner_y;
                }
                if (joint->bounding_max.y < corner2_y) {
                    joint->bounding_max.y = corner2_y;
                }
            }
            joint->bounding_min.x -= 30.0F;
            joint->bounding_max.x += 30.0F;
            joint->bounding_min.y -= 30.0F;
            joint->bounding_max.y += 30.0F;
        }
    }

after0:
    mpJointUpdateDynamics(joint_id);

after1:
    if (joint->flags & CollJoint_Hidden) {
        mpJointUnhide(joint_id);
    }
    flag = false;
    if (!(joint->flags & (CollJoint_Hidden | CollJoint_B11)) &&
        joint->flags & CollJoint_Enabled)
    {
        flag = true;
    }
    mpIsland_8005B334(joint_id, joint->inner->vtx_start,
                      joint->inner->vtx_count, flag);
}

void mpJointUpdateBounding(int joint_id)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    CollVtx* vtx = &groundCollVtx[joint->inner->vtx_start];
    int count = joint->inner->vtx_count;

    int i;
    for (i = 0; i < count; i++) {
        if (joint->bounding_min.x > vtx->pos.x - 30.0F) {
            joint->bounding_min.x = vtx->pos.x - 30.0F;
        }
        if (joint->bounding_max.x < vtx->pos.x + 30.0F) {
            joint->bounding_max.x = vtx->pos.x + 30.0F;
        }
        if (joint->bounding_min.y > vtx->pos.y - 30.0F) {
            joint->bounding_min.y = vtx->pos.y - 30.0F;
        }
        if (joint->bounding_max.y < vtx->pos.y + 30.0F) {
            joint->bounding_max.y = vtx->pos.y + 30.0F;
        }
        vtx += 1;
    }
}

void mpLib_8005667C(int joint_id)
{
    bool flag = false;
    CollJoint* joint = &groundCollJoint[joint_id];

    if (!(joint->flags & (CollJoint_Hidden | CollJoint_B11)) &&
        joint->flags & CollJoint_Enabled)
    {
        flag = true;
    }
    mpIsland_8005B334(joint_id, joint->inner->vtx_start,
                      joint->inner->vtx_count, flag);
}

void mpVtxGetPos(int vtx_id, float* x_out, float* y_out)
{
    CollVtx* vtx = &groundCollVtx[vtx_id];
    *x_out = vtx->pos.x;
    *y_out = vtx->pos.y;
}

void mpVtxSetPos(int vtx_id, float x, float y)
{
    CollVtx* vtx = &groundCollVtx[vtx_id];
    vtx->pos.x = x;
    vtx->pos.y = y;
}

void mpLineSetPos(int line_id, float x0, float y0, float x1, float y1)
{
    CollLine* line = &groundCollLine[line_id];
    mpVtxSetPos(line->inner->v0_idx, x0, y0);
    mpVtxSetPos(line->inner->v1_idx, x1, y1);
}

void mpLib_80056758(int line_id, float x0, float y0, float x1, float y1)
{
    CollLine* line = &groundCollLine[line_id];

    CollVtx* vtx = &groundCollVtx[line->inner->v0_idx];
    vtx->pos.x = vtx->base_pos.x + x0;
    vtx->pos.y = vtx->base_pos.y + y0;

    vtx = &groundCollVtx[line->inner->v1_idx];
    vtx->pos.x = vtx->base_pos.x + x1;
    vtx->pos.y = vtx->base_pos.y + y1;
}

bool mpGetSpeed(int line_id, Vec3* pos, Vec3* speed)
{
    float new_x;
    float new_y;
    CollVtx* v0;
    CollVtx* v1;

    if (!mpLib_80054ED8(line_id)) {
        return false;
    }

    v0 = &groundCollVtx[groundCollLine[line_id].inner->v0_idx];
    v1 = &groundCollVtx[groundCollLine[line_id].inner->v1_idx];
    mpRemap2d(&new_x, &new_y, v0->prev_pos.x, v0->prev_pos.y, v1->prev_pos.x,
              v1->prev_pos.y, v0->pos.x, v0->pos.y, v1->pos.x, v1->pos.y,
              pos->x, pos->y);
    speed->x = new_x - pos->x;
    speed->y = new_y - pos->y;
    speed->z = 0.0F;
    if (DbLevel >= DbLKind_DebugRom) {
        if (ABS(speed->x) > 10000.0F || ABS(speed->y) > 10000.0F) {
            OSReport("%s:%d: Error: mpGetSpeed() x=%f y=%f\n", __FILE__, 5333,
                     speed->x, speed->y);
            HSD_ASSERT(5334,
             !(ABS(speed->x)>10000.0F||ABS(speed->y)>10000.0F));
            HSD_ASSERT(5335, 0);
        }
    }
    return true;
}

float mpLib_800569EC(u32 unk)
{
    return (*mpLib_803BF248[stage_info.grkind].x4)[(u8) unk]->x0;
}

int* mpLib_80056A1C(int id, int* out)
{
    struct mpLib_803BF248_t_x4* entry =
        (*mpLib_803BF248[stage_info.grkind].x4)[(u8) id];
    *out = entry->x14[0];
    return entry->x4;
}

int mpLib_80056A54(int id, int* out)
{
    struct mpLib_803BF248_t_x4* entry =
        (*mpLib_803BF248[stage_info.grkind].x4)[(u8) id];
    *out = entry->x14[2];
    return entry->x14[1];
}

int* mpLib_80056A8C(int id, int* out)
{
    struct mpLib_803BF248_t_x4* entry =
        (*mpLib_803BF248[stage_info.grkind].x4)[(u8) id];
    *out = entry->x30[0];
    return entry->x20;
}

int mpLib_80056AC4(int id, int* out)
{
    struct mpLib_803BF248_t_x4* entry =
        (*mpLib_803BF248[stage_info.grkind].x4)[(u8) id];
    *out = entry->x30[2];
    return entry->x30[1];
}

int* mpLib_80056AFC(int id, int* out)
{
    struct mpLib_803BF248_t_x4* entry =
        (*mpLib_803BF248[stage_info.grkind].x4)[(u8) id];
    *out = entry->x4C[0];
    return entry->x3C;
}

int mpLib_80056B34(int id, int* out)
{
    struct mpLib_803BF248_t_x4* entry =
        (*mpLib_803BF248[stage_info.grkind].x4)[(u8) id];
    *out = entry->x4C[2];
    return entry->x4C[1];
}

static inline float sqrtf_store(float x, volatile float* y)
{
    if (x > 0.0F) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = (float) (x * guess);
        return *y;
    }
    return x;
}

int mpJointFromLine(int line_id)
{
    if (line_id != -1) {
        int i;
        int v0_idx;
        CollJoint* joint;
        int count;
        LINEID_CHECK(5459, line_id);
        v0_idx = groundCollLine[line_id].inner->v0_idx;
        count = mpLib_804D64B4->joint_count;
        joint = groundCollJoint;
        for (i = 0; i < count; i++) {
            if (joint->inner->vtx_start <= v0_idx &&
                v0_idx < joint->inner->vtx_start + joint->inner->vtx_count)
            {
                return joint - groundCollJoint;
            }
            joint++;
        }
    }

    return -1;
}

bool mpLib_80056C54(int line_id, Vec3* pos, int* line_id_out, Vec3* vec_out,
                    u32* flags_out, Vec3* normal_out, f32 distance,
                    f32 wall_limit)
{
    u8 _padA[8];
    float y;
    Vec3 cur_pos;
    Vec3 vtx_pos;
    float sqrt_tmp[2];
    float dist;
    float total_dist;
    float dx2;
    float dy2;
    int result;
    int new_id;
    u32 flags;

    result = true;
    if (!mpLib_80054ED8(line_id)) {
        return false;
    }

    if (mpLib_8004DD90_Floor(line_id, pos, &y, NULL, NULL) == -1) {
        return false;
    }
    cur_pos = *pos;
    cur_pos.y += y;
    if (distance > 0.0F) {
        while (true) {
            mpLineGetV1Pos(line_id, &vtx_pos);
            dx2 = SQ(cur_pos.x - vtx_pos.x);
            dy2 = SQ(cur_pos.y - vtx_pos.y);
            dist = sqrtf_store(dx2 + dy2, sqrt_tmp - 4);
            flags = mpLineGetKind(line_id);
            if (flags & 0xC) {
                total_dist += dist;
                if (total_dist > wall_limit) {
                    result = false;
                } else {
                    goto block_30;
                }
            } else if (flags & 2) {
                result = false;
            } else {
                total_dist = 0.0F;
            block_30:
                if (!(dist > distance)) {
                    new_id = mpLineGetNext(line_id);
                    if (new_id == -1) {
                        result = false;
                    } else {
                        distance -= dist;
                        line_id = new_id;
                        cur_pos = vtx_pos;
                        continue;
                    }
                }
            }

            break;
        }
    } else {
        distance = -distance;
        while (true) {
            mpLineGetV0Pos(line_id, &vtx_pos);
            dx2 = SQ(cur_pos.x - vtx_pos.x);
            dy2 = SQ(cur_pos.y - vtx_pos.y);
            dist = sqrtf_store(dx2 + dy2, sqrt_tmp - 5);
            flags = mpLineGetKind(line_id);
            if (flags & 0xC) {
                total_dist += dist;
                if (total_dist > wall_limit) {
                    result = false;
                } else {
                    goto block_55;
                }
            } else if (flags & 2) {
                result = false;
            } else {
                total_dist = 0.0F;
            block_55:
                if (!(dist > distance)) {
                    new_id = mpLineGetPrev(line_id);
                    if (new_id == -1) {
                        result = false;
                    } else {
                        distance -= dist;
                        line_id = new_id;
                        cur_pos = vtx_pos;
                        continue;
                    }
                }
            }
            break;
        }
    }
    if (line_id != -1) {
        if (!(mpLineGetKind(line_id) & CollLine_Floor)) {
            line_id = -1;
        }
    }
    if (line_id_out != NULL) {
        *line_id_out = line_id;
    }
    if (line_id != -1) {
        if (flags_out != NULL) {
            *flags_out = mpLineGetFlags(line_id);
        }
        if (normal_out != NULL) {
            mpLineGetNormal(line_id, normal_out);
        }
    }
    if (vec_out != NULL) {
        if (result) {
            if (dist < 0.0001) {
                *vec_out = cur_pos;
            } else {
                float t = distance / dist;
                vec_out->x = (t * (vtx_pos.x - cur_pos.x)) + cur_pos.x;
                vec_out->y = (t * (vtx_pos.y - cur_pos.y)) + cur_pos.y;
                vec_out->z = (t * (vtx_pos.z - cur_pos.z)) + cur_pos.z;
            }
        } else {
            *vec_out = vtx_pos;
        }
    }
    return result;
}

void mpLib_80057424(int joint_id)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    MapJoint* j_inner = joint->inner;
    u32 count = j_inner->vtx_count;
    int new_var;
    CollVtx* vtx = &groundCollVtx[j_inner->vtx_start];
    for (joint_id = 0; joint_id < (new_var = count); joint_id++) {
        vtx->prev_pos.x = vtx->pos.x;
        vtx->prev_pos.y = vtx->pos.y;
        vtx++;
    }
}

void mpLib_80057528(int line_id)
{
    int joint_id = mpJointFromLine(line_id);
    if (joint_id != -1) {
        CollLine* line = &groundCollLine[line_id];
        CollJoint* joint = &groundCollJoint[joint_id];
        line->flags |= LINE_FLAG_ENABLED;
        mpIsland_8005B334(joint_id, joint->inner->vtx_start,
                          joint->inner->vtx_count,
                          !(joint->flags & CollJoint_B11));
        joint->xE = true;
    }
}

void mpLib_800575B0(int line_id)
{
    int joint_id = mpJointFromLine(line_id);
    if (joint_id != -1) {
        CollLine* line = &groundCollLine[line_id];
        CollJoint* joint = &groundCollJoint[joint_id];
        line->flags &= ~LINE_FLAG_ENABLED;
        mpIsland_8005B334(joint_id, joint->inner->vtx_start,
                          joint->inner->vtx_count,
                          !(joint->flags & CollJoint_B11));
        joint->xE = true;
    }
}

void mpJointListAdd(int joint_id)
{
    CollJoint* joint;
    MapJoint* j_inner;
    int count;
    CollLine* line;

    joint = &groundCollJoint[joint_id];
    if (joint->flags & CollJoint_Enabled) {
        return;
    }

    joint->flags |= CollJoint_Enabled;
    if (jointListStart == NULL) {
        jointListStart = joint;
    } else {
        jointListEnd->next = joint;
    }
    jointListEnd = joint;
    joint->next = NULL;

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_Floor].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_Floor].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_ENABLED;
        line++;
    }

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_Ceiling].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_Ceiling].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_ENABLED;
        line++;
    }

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_LeftWall].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_LeftWall].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_ENABLED;
        line++;
    }

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_RightWall].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_RightWall].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_ENABLED;
        line++;
    }

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_Dynamic].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_Dynamic].start];
    while (count-- > 0) {
        line->flags |= LINE_FLAG_ENABLED;
        line++;
    }

    mpLib_80057424(joint_id);
    j_inner = joint->inner;
    mpIsland_8005B334(joint_id, j_inner->vtx_start, j_inner->vtx_count,
                      !(joint->flags & CollJoint_B11));
    joint->xE = true;
}

void mpJointListUnlink(CollJoint* joint)
{
    CollJoint* cur;

    if (joint == jointListStart) {
        if (joint == jointListEnd) {
            jointListEnd = NULL;
            jointListStart = NULL;
        } else {
            jointListStart = jointListStart->next;
        }
        return;
    }

    for (cur = jointListStart; cur != NULL; cur = cur->next) {
        if (cur->next == joint) {
            if (joint == jointListEnd) {
                jointListEnd = cur;
            }
            cur->next = cur->next->next;
            return;
        }
    }
}

void mpLib_80057BC0(int joint_id)
{
    CollJoint* joint;
    MapJoint* j_inner;
    int count;
    CollLine* line;

    joint = &groundCollJoint[joint_id];
    if (!(joint->flags & CollJoint_Enabled)) {
        return;
    }

    joint->flags &= ~CollJoint_Enabled;
    mpJointListUnlink(joint);

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_Floor].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_Floor].start];
    for (; count > 0; count--) {
        line->flags &= ~LINE_FLAG_ENABLED;
        line++;
    }

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_Ceiling].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_Ceiling].start];
    for (; count > 0; count--) {
        line->flags &= ~LINE_FLAG_ENABLED;
        line++;
    }

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_LeftWall].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_LeftWall].start];
    for (; count > 0; count--) {
        line->flags &= ~LINE_FLAG_ENABLED;
        line++;
    }

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_RightWall].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_RightWall].start];
    for (; count > 0; count--) {
        line->flags &= ~LINE_FLAG_ENABLED;
        line++;
    }

    j_inner = joint->inner;
    count = j_inner->ranges[MapLineGroup_Dynamic].count;
    line = &groundCollLine[j_inner->ranges[MapLineGroup_Dynamic].start];
    for (; count > 0; count--) {
        line->flags &= ~LINE_FLAG_ENABLED;
        line++;
    }
    j_inner = joint->inner;
    mpIsland_8005B334(joint_id, j_inner->vtx_start, j_inner->vtx_count, false);
    joint->xE = true;
}

void mpLib_80057FDC(int joint_id)
{
    MapJoint* j_inner;
    bool flag = false;
    CollJoint* joint = &groundCollJoint[joint_id];

    joint->flags &= ~CollJoint_B11;
    if (!(joint->flags & (CollJoint_Hidden | CollJoint_B11)) &&
        joint->flags & CollJoint_Enabled)
    {
        flag = true;
    }
    j_inner = joint->inner;
    mpIsland_8005B334(joint_id, j_inner->vtx_start, j_inner->vtx_count, flag);
}

void mpLib_80058044(int joint_id)
{
    MapJoint* j_inner;
    bool flag = false;
    CollJoint* joint = &groundCollJoint[joint_id];

    joint->flags |= CollJoint_B11;
    if (!(joint->flags & (CollJoint_Hidden | CollJoint_B11)) &&
        joint->flags & CollJoint_Enabled)
    {
        flag = true;
    }
    j_inner = joint->inner;
    mpIsland_8005B334(joint_id, j_inner->vtx_start, j_inner->vtx_count, flag);
}

void mpJointSetB10(int joint_id)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    joint->flags |= CollJoint_B10;
}

void mpJointSetCb1(int joint_id, void* user_data,
                   mpLib_JointCollisionCallback cb)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    joint->cb_0 = cb;
    joint->cb_data_0 = user_data;
}

void mpJointClearCb1(int joint_id)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    joint->cb_0 = NULL;
    joint->cb_data_0 = NULL;
}

void mpJointGetCb1(int joint_id, mpLib_JointCollisionCallback* cb,
                   void** user_data)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    *cb = joint->cb_0;
    *user_data = joint->cb_data_0;
}

void mpLib_8005811C(CollData* coll, int ledge_id)
{
    if (ledge_id != -1) {
        int joint_id = mpJointFromLine(ledge_id);
        if (joint_id != -1) {
            mpLib_JointCollisionCallback cb = groundCollJoint[joint_id].cb_0;
            Ground* gp = groundCollJoint[joint_id].cb_data_0;
            if (cb != NULL) {
                cb(gp, joint_id, coll, coll->x50, 3, 0.0F);
            }
        }
    }
}

void mpJointSetCb2(int joint_id, void* gp, mpLib_JointCollisionCallback cb)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    joint->cb_1 = cb;
    joint->cb_data_1 = gp;
}

void mpJointGetCb2(int joint_id, mpLib_JointCollisionCallback* cb,
                   void** user_data)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    *cb = joint->cb_1;
    *user_data = joint->cb_data_1;
}

static inline void mpLib_GetJointVtxRange(CollJoint* joint, int* start,
                                          int* count)
{
    MapJoint* map_joint = joint->inner;
    *start = map_joint->vtx_start;
    *count = map_joint->vtx_count;
}

struct mpLib_800581DC_ln {
    CollLine* p;
};

void mpLib_800581DC(int joint_id0, int joint_id1)
{
    CollJoint* j0;
    CollJoint* j1;
    CollLine* line_base;
    int vi;
    int i;
    int vcount0;
    int vstart0;
    struct mpLib_800581DC_ln ln;

    j0 = &groundCollJoint[joint_id0];
    j1 = &groundCollJoint[joint_id1];
    line_base = groundCollLine;
    for (i = 0; i < MapLineGroup_Count; i++) {
        struct MapLineRange* pair;
        int count;
        int temp;
        {
            int j;
            int idx;
            pair = j0->inner->ranges + i;
            count = pair->count;
            (void) line_base[idx = pair->start];
            ln.p = &line_base[idx];
            for (j = 0; j < count; j++, idx++) {
                temp = ln.p[j].inner->prev_id1;
                if (temp != -1) {
                    temp = line_base[temp].inner->next_id1;
                    if (temp != -1 && idx != temp) {
                        ln.p[j].inner->prev_id1 = -1;
                    }
                }
                temp = ln.p[j].inner->next_id1;
                if (temp != -1) {
                    temp = line_base[temp].inner->prev_id1;
                    if (temp != -1 && idx != temp) {
                        ln.p[j].inner->next_id1 = -1;
                    }
                }
            }
        }
        {
            int j;
            int idx;
            pair = j1->inner->ranges + i;
            count = pair->count;
            (void) line_base[idx = pair->start];
            ln.p = &line_base[idx];
            for (j = 0; j < count; j++, idx++) {
                temp = ln.p[j].inner->prev_id1;
                if (temp != -1) {
                    temp = line_base[temp].inner->next_id1;
                    if (temp != -1 && idx != temp) {
                        ln.p[j].inner->prev_id1 = -1;
                    }
                }
                temp = ln.p[j].inner->next_id1;
                if (temp != -1) {
                    temp = line_base[temp].inner->prev_id1;
                    if (temp != -1 && idx != temp) {
                        ln.p[j].inner->next_id1 = -1;
                    }
                }
            }
        }
    }

    mpLib_GetJointVtxRange(j0, &vstart0, &vcount0);

    // for every pair of verts
    for (vi = 0; vi < vcount0; vi++, vstart0++) {
        CollVtx* vtx0;
        int v;
        int vcount1;
        int vid;
        vtx0 = &groundCollVtx[vstart0];
        vcount1 = j1->inner->vtx_count;
        vid = j1->inner->vtx_start;
        for (v = 0; v < vcount1; v++, vid++) {
            int group;
            CollVtx* v1 = &groundCollVtx[vid];

            // ensure they are nearby
            if (!(ABS(vtx0->pos.x - v1->pos.x) < 2.0) ||
                !(ABS(vtx0->pos.y - v1->pos.y) < 2.0))
            {
                continue;
            }

            // find every line with the first vert
            for (group = 0; group < MapLineGroup_Count; group++) {
                int line0;
                int n;
                int count0;
                count0 = j0->inner->ranges[group].count;
                (void) line_base[line0 = j0->inner->ranges[group].start];
                for (n = 0; n < count0; n++, line0++) {
                    if (vstart0 == line_base[line0].inner->v0_idx) {
                        int j;
                        int line1;
                        s16 count1;
                        // if the first vert is that line's v0
                        // find every line with the second vert as v1
                        for (j = 0; j < MapLineGroup_Count; j++) {
                            int k;
                            count1 = j1->inner->ranges[j].count;
                            (void)
                                line_base[line1 = j1->inner->ranges[j].start];
                            for (k = 0; k < count1; k++, line1++) {
                                if (vid == line_base[line1].inner->v1_idx) {
                                    line_base[line0].inner->prev_id1 = line1;
                                    line_base[line1].inner->next_id1 = line0;
                                }
                            }
                        }
                    } else if (vstart0 == line_base[line0].inner->v1_idx) {
                        int j;
                        int line1;
                        s16 count1;
                        // else if the first vert is that line's v1
                        // find every line with the second vert as v0
                        for (j = 0; j < MapLineGroup_Count; j++) {
                            int k;
                            count1 = j1->inner->ranges[j].count;
                            (void)
                                line_base[line1 = j1->inner->ranges[j].start];
                            for (k = 0; k < count1; k++, line1++) {
                                if (vid == line_base[line1].inner->v0_idx) {
                                    line_base[line0].inner->next_id1 = line1;
                                    line_base[line1].inner->prev_id1 = line0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void mpLib_80058560(void)
{
    MapCollData* coll_data = mpLib_804D64B4;
    int i;
    int j;
    CollJoint* cur_i;
    CollJoint* cur_j;

    for (i = 0; i < coll_data->joint_count - 1; i++) {
        for (j = i + 1; j < coll_data->joint_count; j++) {
            cur_i = &groundCollJoint[i];
            cur_j = &groundCollJoint[j];
            if (cur_i->flags & CollJoint_Enabled &&
                !(cur_i->flags & CollJoint_Hidden) &&
                cur_j->flags & CollJoint_Enabled &&
                !(cur_j->flags & CollJoint_Hidden))
            {
                mpLib_800581DC(i, j);
            }
        }
    }
}

void mpLib_80058614_Floor(void)
{
    CollJoint* jp;
    int joint_count;
    int idx;
    int i;
    int j;
    CollLine* linebase;
    CollLine* line;
    int count;
    int dynamic_count;
    MapJoint* j_inner;
    CollVtx* v0;
    CollVtx* v1;
    float* top_p;
    float* bottom_p;
    float* right_p;
    float* left_p;
    CollJoint* joint;
    PAD_STACK(8);

    jp = (joint = groundCollJoint);
    joint_count = mpLib_804D64B4->joint_count;
    for (idx = 0; idx < joint_count; idx++, jp++) {
        if (jp->xE) {
            break;
        }
    }

    if (idx == joint_count) {
        return;
    }

    *(right_p = &mpLib_80458868[1].right) = -F32_MAX;
    *(top_p = &mpLib_80458868[1].top) = -F32_MAX;
    *(left_p = &mpLib_80458868[1].left) = F32_MAX;
    *(bottom_p = &mpLib_80458868[1].bottom) = F32_MAX;

    for (i = 0; i < joint_count; i++, joint++) {
        joint->xE = false;
        if (!(joint->flags & CollJoint_Enabled) ||
            joint->flags & CollJoint_Hidden)
        {
            continue;
        }

        {
            j_inner = joint->inner;
            dynamic_count = j_inner->ranges[MapLineGroup_Dynamic].count;
            (void)
                groundCollVtx[count =
                                  j_inner->ranges[MapLineGroup_Floor].count];
            linebase = groundCollLine;
            line = &linebase[j_inner->ranges[MapLineGroup_Floor].start];

            for (j = 0; j < count; j++, line++) {
                float x0;
                float y0;
                float x1;
                float y1;
            block_8:

                if (!(line->flags & CollLine_Floor) ||
                    !(line->flags & LINE_FLAG_ENABLED))
                {
                    continue;
                }

                v0 = &groundCollVtx[line->inner->v0_idx];
                v1 = &groundCollVtx[line->inner->v1_idx];
                x0 = v0->pos.x;
                y0 = v0->pos.y;
                x1 = v1->pos.x;
                y1 = v1->pos.y;

                if (*top_p < y0) {
                    *top_p = y0;
                }
                if (*bottom_p > y0) {
                    *bottom_p = y0;
                }
                if (*right_p < x0) {
                    *right_p = x0;
                }
                if (*left_p > x0) {
                    *left_p = x0;
                }
                if (*top_p < y1) {
                    *top_p = y1;
                }
                if (*bottom_p > y1) {
                    *bottom_p = y1;
                }
                if (*right_p < x1) {
                    *right_p = x1;
                }
                if (*left_p > x1) {
                    *left_p = x1;
                }
            }
            if (dynamic_count != 0) {
                count = dynamic_count;
                j = 0;
                dynamic_count = 0;
                line = &linebase[joint->inner->ranges[MapLineGroup_Dynamic]
                                     .start];
                goto block_8;
            }
        }
    }
}

void mpLib_800587FC(HSD_GObj* gobj)
{
    mpLib_80058614_Floor();
    grDynamicAttr_801CA224();
}

void mpLib_80058820(void)
{
    mpCollisionBox* box = mpLib_80458868;
    HSD_GObj* gobj = GObj_Create(1, 6, 0);
    HSD_ASSERT(6314, gobj);
    HSD_GObj_SetupProc(gobj, mpLib_800587FC, 4);
    box[0].right = 10000.0F;
    box[0].top = 10000.0F;
    box[0].left = -10000.0F;
    box[0].bottom = -10000.0F;
    box[1] = box[0];
}

bool mpCheckedBounding(void)
{
    return didCheckBounding;
}

/// takes a bounding box and checks each joint to see if they're within range
/// if they are outside the bounding box, they are marked as too far
void mpBoundingCheck(float left, float bottom, float right, float top)
{
    CollJoint* curr = jointListStart;

    while (curr != NULL) {
        if (curr->flags & CollJoint_Enabled &&
            !(curr->flags & CollJoint_Hidden))
        {
            if (curr->flags & CollJoint_B10) {
                curr->flags &= ~CollJoint_TooFar;
            } else if (left > curr->bounding_max.x ||
                       right < curr->bounding_min.x ||
                       bottom > curr->bounding_max.y ||
                       top < curr->bounding_min.y)
            {
                curr->flags |= CollJoint_TooFar;
            } else {
                curr->flags &= ~CollJoint_TooFar;
            }
        } else {
            curr->flags |= CollJoint_TooFar;
        }

        curr = curr->next;
    }

    didCheckBounding = true;
}

void mpBoundingCheck2(float x1, float y1, float x2, float y2)
{
    float right;
    float left;
    float bottom;
    float top;

    if (x1 > x2) {
        left = x2;
        right = x1;
    } else {
        right = x2;
        left = x1;
    }
    if (y1 > y2) {
        bottom = y2;
        top = y1;
    } else {
        top = y2;
        bottom = y1;
    }
    mpBoundingCheck(left, bottom, right, top);
}

void mpBoundingCheck3(float x0, float y0, float x1, float y1, float x2,
                      float y2, float x3, float y3)
{
    float right;
    float left;
    float bottom;
    float top;

    left = x1;
    bottom = y1;
    if (x0 > left) {
        right = x0;
    } else {
        right = left;
        left = x0;
    }
    if (y0 > bottom) {
        top = y0;
    } else {
        top = bottom;
        bottom = y0;
    }
    if (right < x2) {
        right = x2;
    } else if (left > x2) {
        left = x2;
    }
    if (top < y2) {
        top = y2;
    } else if (bottom > y2) {
        bottom = y2;
    }
    if (right < x3) {
        right = x3;
    } else if (left > x3) {
        left = x3;
    }
    if (top < y3) {
        top = y3;
    } else if (bottom > y3) {
        bottom = y3;
    }
    mpBoundingCheck(left, bottom, right, top);
}

void mpUncheckBounding(void)
{
    CollJoint* curr = jointListStart;

    while (curr != NULL) {
        curr->flags &= ~CollJoint_TooFar;
        curr = curr->next;
    }

    didCheckBounding = false;
}

static char lbl_803BF526[0x18] = "";

static HSD_Chan mpLib_803BF540 = {
    NULL,
    GX_COLOR0A0,
    0,
    { 0, 0, 0, 0 },
    { 0xFF, 0xA0, 0x30, 0xFF },
    0,
    GX_SRC_REG,
    GX_SRC_REG,
    GX_LIGHT_NULL,
    GX_DF_CLAMP,
    GX_AF_NONE,
    NULL,
};

static char lbl_803BF570[] = "B(%d,%d)-(%d,%d)\n";

void mpLib_SetupDraw(GXColor color)
{
    HSD_TevDesc spC;
    HSD_StateInitTev();
    spC.flags = 0;
    spC.stage = HSD_StateAssignTev();
    spC.coord = 0xFF;
    spC.map = 0xFF;
    spC.color = 4;
    spC.u.tevop.tevmode = 4;
    HSD_SetupTevStage(&spC);
    HSD_SetupPEMode(1, NULL);
    HSD_SetTevRegAll();
    HSD_StateSetNumTevStages();
    HSD_StateSetNumTexGens();
    HSD_StateSetNumChans(1);
    mpLib_803BF540.mat_color = color;
    HSD_SetupChannel(&mpLib_803BF540);
}

void mpLib_DrawEcbs(CollData* cd)
{
    GXColor cur_ecb_color = { 0xFF, 0xA0, 0x30, 0xFF };
    GXColor cur_cross_color = { 0x80, 0x50, 0x18, 0xFF };
    GXColor prev_ecb_color = { 0xFF, 0x5A, 0x20, 0xFF };
    GXColor prev_cross_color = { 0x80, 0x2D, 0x10, 0xFF };
    GXColor last_ecb_color = { 0x20, 0x20, 0xFF, 0xFF };
    GXColor last_cross_color = { 0x10, 0x10, 0x80, 0xFF };
    GXColor x28_ecb_color = { 0xFF, 0xFF, 0xFF, 0x80 };
    GXColor x28_cross_color = { 0xFF, 0xFF, 0xFF, 0x80 };

    mpLib_SetupDraw(cur_ecb_color);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(cd->cur_pos.x + cd->ecb.top.x,
                   cd->cur_pos.y + cd->ecb.top.y, cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x + cd->ecb.right.x,
                   cd->cur_pos.y + cd->ecb.right.y, cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x + cd->ecb.bottom.x,
                   cd->cur_pos.y + cd->ecb.bottom.y, cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x + cd->ecb.left.x,
                   cd->cur_pos.y + cd->ecb.left.y, cd->cur_pos.z);

    GXEnd();

    mpLib_SetupDraw(cur_cross_color);
    GXBegin(GX_LINES, GX_VTXFMT0, 4);

    GXPosition3f32(cd->cur_pos.x - 1.0F, cd->cur_pos.y, cd->cur_pos.z);
    GXPosition3f32(1.0F + cd->cur_pos.x, cd->cur_pos.y, cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x, cd->cur_pos.y - 1.0F, cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x, 1.0F + cd->cur_pos.y, cd->cur_pos.z);

    GXEnd();

    mpLib_SetupDraw(prev_ecb_color);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(cd->prev_pos.x + cd->prev_ecb.top.x,
                   cd->prev_pos.y + cd->prev_ecb.top.y, cd->prev_pos.z - 0.5F);
    GXPosition3f32(cd->prev_pos.x + cd->prev_ecb.right.x,
                   cd->prev_pos.y + cd->prev_ecb.right.y,
                   cd->prev_pos.z - 0.5F);
    GXPosition3f32(cd->prev_pos.x + cd->prev_ecb.bottom.x,
                   cd->prev_pos.y + cd->prev_ecb.bottom.y,
                   cd->prev_pos.z - 0.5F);
    GXPosition3f32(cd->prev_pos.x + cd->prev_ecb.left.x,
                   cd->prev_pos.y + cd->prev_ecb.left.y,
                   cd->prev_pos.z - 0.5F);

    GXEnd();

    mpLib_SetupDraw(prev_cross_color);
    GXBegin(GX_LINES, GX_VTXFMT0, 4);

    GXPosition3f32(cd->prev_pos.x - 1.0F, cd->prev_pos.y,
                   cd->prev_pos.z - 0.5F);
    GXPosition3f32(1.0F + cd->prev_pos.x, cd->prev_pos.y,
                   cd->prev_pos.z - 0.5F);
    GXPosition3f32(cd->prev_pos.x, cd->prev_pos.y - 1.0F,
                   cd->prev_pos.z - 0.5F);
    GXPosition3f32(cd->prev_pos.x, 1.0F + cd->prev_pos.y,
                   cd->prev_pos.z - 0.5F);

    GXEnd();

    mpLib_SetupDraw(last_ecb_color);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(cd->last_pos.x + cd->xE4_ecb.top.x,
                   cd->last_pos.y + cd->xE4_ecb.top.y, cd->last_pos.z - 1.0F);
    GXPosition3f32(cd->last_pos.x + cd->xE4_ecb.right.x,
                   cd->last_pos.y + cd->xE4_ecb.right.y,
                   cd->last_pos.z - 1.0F);
    GXPosition3f32(cd->last_pos.x + cd->xE4_ecb.bottom.x,
                   cd->last_pos.y + cd->xE4_ecb.bottom.y,
                   cd->last_pos.z - 1.0F);
    GXPosition3f32(cd->last_pos.x + cd->xE4_ecb.left.x,
                   cd->last_pos.y + cd->xE4_ecb.left.y, cd->last_pos.z - 1.0F);

    GXEnd();

    mpLib_SetupDraw(last_cross_color);
    GXBegin(GX_LINES, GX_VTXFMT0, 4);

    GXPosition3f32(cd->last_pos.x - 1.0F, cd->last_pos.y,
                   cd->last_pos.z - 1.0F);
    GXPosition3f32(1.0F + cd->last_pos.x, cd->last_pos.y,
                   cd->last_pos.z - 1.0F);
    GXPosition3f32(cd->last_pos.x, cd->last_pos.y - 1.0F,
                   cd->last_pos.z - 1.0F);
    GXPosition3f32(cd->last_pos.x, 1.0F + cd->last_pos.y,
                   cd->last_pos.z - 1.0F);

    GXEnd();

    mpLib_SetupDraw(x28_ecb_color);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
    if (cd->x34_flags.b6) {
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.top.x,
                       cd->x28_vec.y + cd->x64_ecb.top.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.right.x,
                       cd->x28_vec.y + cd->x64_ecb.right.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.bottom.x,
                       cd->x28_vec.y + cd->x64_ecb.bottom.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.left.x,
                       cd->x28_vec.y + cd->x64_ecb.left.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.top.x,
                       cd->x28_vec.y + cd->x64_ecb.top.y,
                       0.5F + cd->x28_vec.z);
    } else {
        GXPosition3f32(cd->x28_vec.x + cd->ecb.top.x,
                       cd->x28_vec.y + cd->ecb.top.y, 0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->ecb.right.x,
                       cd->x28_vec.y + cd->ecb.right.y, 0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->ecb.bottom.x,
                       cd->x28_vec.y + cd->ecb.bottom.y, 0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->ecb.left.x,
                       cd->x28_vec.y + cd->ecb.left.y, 0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->ecb.top.x,
                       cd->x28_vec.y + cd->ecb.top.y, 0.5F + cd->x28_vec.z);
    }
    GXEnd();

    mpLib_SetupDraw(x28_cross_color);
    GXBegin(GX_LINES, GX_VTXFMT0, 4U);

    GXPosition3f32(cd->x28_vec.x - 1.0F, cd->x28_vec.y, 0.5 + cd->x28_vec.z);
    GXPosition3f32(1.0F + cd->x28_vec.x, cd->x28_vec.y, 0.5 + cd->x28_vec.z);
    GXPosition3f32(cd->x28_vec.x, cd->x28_vec.y - 1.0F, 0.5 + cd->x28_vec.z);
    GXPosition3f32(cd->x28_vec.x, 1.0F + cd->x28_vec.y, 0.5 + cd->x28_vec.z);

    GXEnd();
}

static inline GXColor mpLib_CopyColor(GXColor color)
{
    return color;
}

static const GXColor mpLib_804D80E0 = { 0xFF, 0x37, 0x37, 0x80 };
static const GXColor mpLib_804D80E4 = { 0x37, 0x37, 0xFF, 0x80 };

void mpLib_DrawSnapping(void)
{
    GXColor left_snap_color = mpLib_804D80E0;
    GXColor right_snap_color = mpLib_804D80E4;
    HSD_GObj* item;
    HSD_GObj* ft;
    bool set_up;

    set_up = false;
    ft = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER];
    if (ft != NULL) {
        Mtx mtx;
        PAD_STACK(0x30);
        HSD_StateSetCullMode(0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), mtx);
        GXSetCurrentMtx(0U);
        GXLoadPosMtxImm(mtx, 0);
        set_up = true;
        for (; ft != NULL; ft = ft->next) {
            CollData* cd = ftLib_GetCollData(ft);

            if (!cd->x35_flags.b0 || cd->x38 != mpColl_804D64AC) {
                continue;
            }

            mpLib_DrawEcbs(cd);

            if (cd->ledge_snap_x != 0.0 || cd->ledge_snap_y != 0.0) {
                float inner_x = cd->cur_pos.x + cd->ecb.right.x;
                float pos_y = cd->cur_pos.y;
                float half_height = 0.5F * cd->ledge_snap_height;

                mpLib_SetupDraw(right_snap_color);
                GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
                GXPosition3f32(inner_x + cd->ledge_snap_x,
                               half_height + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXPosition3f32(inner_x + cd->ledge_snap_x,
                               (pos_y + cd->ledge_snap_y) - half_height,
                               cd->cur_pos.z);
                GXPosition3f32(cd->cur_pos.x,
                               (pos_y + cd->ledge_snap_y) - half_height,
                               cd->cur_pos.z);
                GXPosition3f32(cd->cur_pos.x,
                               half_height + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXPosition3f32(inner_x + cd->ledge_snap_x,
                               half_height + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXEnd();

                pos_y = cd->cur_pos.y;
                inner_x = cd->cur_pos.x + cd->ecb.left.x;
                mpLib_SetupDraw(mpLib_CopyColor(left_snap_color));
                GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

                GXPosition3f32(inner_x - cd->ledge_snap_x,
                               half_height + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXPosition3f32(inner_x - cd->ledge_snap_x,
                               (pos_y + cd->ledge_snap_y) - half_height,
                               cd->cur_pos.z);
                GXPosition3f32(cd->cur_pos.x,
                               (pos_y + cd->ledge_snap_y) - half_height,
                               cd->cur_pos.z);
                GXPosition3f32(cd->cur_pos.x,
                               half_height + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXPosition3f32(inner_x - cd->ledge_snap_x,
                               half_height + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);

                GXEnd();
            }
        }
    }

    if ((item = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM]) != NULL) {
        if (!set_up) {
            Mtx view_mtx;
            PAD_STACK(0x34);
            GXSetCullMode(GX_CULL_NONE);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
            HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), view_mtx);
            GXSetCurrentMtx(0);
            GXLoadPosMtxImm(view_mtx, 0);
        }

        for (; item != NULL; item = item->next) {
            CollData* cd = &GET_ITEM(item)->x378_itemColl;
            if (!cd->x35_flags.b0) {
                continue;
            }

            if (cd->x38 == mpColl_804D64AC) {
                mpLib_DrawEcbs(cd);
            }

            if (itGetKind(item) == It_Kind_Link_HShot) {
                mpLib_DrawEcbs(
                    &GET_ITEM(item)->xDD4_itemVar.linkhookshot.x0->coll_data);
            }
        }
    }
}

#ifdef MUST_MATCH
#define UNINITIALIZED(x) x
#else
#define UNINITIALIZED(x) void
#endif

static UNINITIALIZED(int)
    mpLib_DrawMatchingLines(int value, int flag, const GXColor* color)
{
    CollLine* line;
    int count;
    int total;
    CollLine* scan;
    int i;

    count = 0;
    total = mpLib_804D64B4->line_count;
    scan = groundCollLine;
    for (i = 0; i < total; i++) {
        if (scan->flags & LINE_FLAG_ENABLED &&
            !(scan->flags & LINE_FLAG_HIDDEN) &&
            value == (scan->inner->lo_flags & flag))
        {
            count += 1;
        }
        scan += 1;
    }

    if (count == 0) {
        return;
    }

    line = groundCollLine;
    mpLib_SetupDraw(*color);
    GXBegin(GX_QUADS, GX_VTXFMT0, count * 4);
    for (i = 0; i < total; i++) {
        if (line->flags & LINE_FLAG_ENABLED &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            if (value == (line->inner->lo_flags & flag)) {
                PAD_STACK(8);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
        }
        line += 1;
    }
    GXEnd();
}

static const GXColor mpLib_804D80F0 = { 0xFF, 0x40, 0x40, 0xFF };
static const GXColor mpLib_804D80F4 = { 0x40, 0x40, 0xFF, 0xFF };
static const GXColor mpLib_804D80F8 = { 0xFF, 0x40, 0xFF, 0xFF };
static const GXColor mpLib_804D80FC = { 0x80, 0x80, 0x80, 0xFF };
static const GXColor mpLib_804D8100 = { 0x80, 0x80, 0x80, 0xFF };

static const GXColor mpLib_FloorColor = { 0xC0, 0xC0, 0xC0, 0xFF };
static const GXColor mpLib_CeilingColor = { 0xC0, 0x80, 0x80, 0xFF };
static const GXColor mpLib_RightWallColor = { 0x80, 0xC0, 0x80, 0xFF };
static const GXColor mpLib_LeftWallColor = { 0x80, 0x80, 0xC0, 0xFF };
static const GXColor mpLib_DynamicFloorColor = { 0x60, 0x60, 0x60, 0xFF };
static const GXColor mpLib_DynamicCeilingColor = { 0x60, 0x40, 0x40, 0xFF };
static const GXColor mpLib_DynamicRightWallColor = { 0x40, 0x60, 0x40, 0xFF };
static const GXColor mpLib_DynamicLeftWallColor = { 0x40, 0x40, 0x60, 0xFF };

void mpLib_80059554(void)
{
    CollLine* line;
    int total;
    int count;
    MapCollData* coll_data;
    int i;
    UNUSED u8 pad[16];
    GXColor floor_color;
    GXColor ceiling_color;
    GXColor right_wall_color;
    GXColor left_wall_color;

    coll_data = mpLib_804D64B4;

    total = 0;
    count = coll_data->ranges[MapLineGroup_Floor].count;
    line = &groundCollLine[coll_data->ranges[MapLineGroup_Floor].start];

    for (i = 0; i < count; i++) {
        if (line->flags & LINE_FLAG_ENABLED &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            total += 1;
        }
        line++;
    }

    if (total != 0) {
        mpLib_SetupDraw(mpLib_FloorColor);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total * 4) & 0xFFFC);
        line = &groundCollLine[coll_data->ranges[MapLineGroup_Floor].start];

        for (i = 0; i < count; i++) {
            if (line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_HIDDEN))
            {
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
            line++;
        }
        GXEnd();
    }

    total = 0;
    count = coll_data->ranges[MapLineGroup_Ceiling].count;
    line = &groundCollLine[coll_data->ranges[MapLineGroup_Ceiling].start];

    for (i = 0; i < count; i++) {
        if (line->flags & LINE_FLAG_ENABLED &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            total += 1;
        }
        line += 1;
    }

    if (total != 0) {
        mpLib_SetupDraw(mpLib_CeilingColor);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total * 4) & 0xFFFC);
        line = &groundCollLine[coll_data->ranges[MapLineGroup_Ceiling].start];

        for (i = 0; i < count; i++) {
            if (line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_HIDDEN))
            {
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
            line++;
        }
        GXEnd();
    }

    total = 0;
    count = coll_data->ranges[MapLineGroup_RightWall].count;
    line = &groundCollLine[coll_data->ranges[MapLineGroup_RightWall].start];

    for (i = 0; i < count; i++) {
        if (line->flags & LINE_FLAG_ENABLED &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            total += 1;
        }
        line += 1;
    }

    if (total != 0) {
        mpLib_SetupDraw(mpLib_RightWallColor);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total * 4) & 0xFFFC);
        line =
            &groundCollLine[coll_data->ranges[MapLineGroup_RightWall].start];

        for (i = 0; i < count; i++) {
            if (line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_HIDDEN))
            {
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
            line++;
        }
        GXEnd();
    }

    total = 0;
    count = coll_data->ranges[MapLineGroup_LeftWall].count;
    line = &groundCollLine[coll_data->ranges[MapLineGroup_LeftWall].start];

    for (i = 0; i < count; i++) {
        if (line->flags & LINE_FLAG_ENABLED &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            total += 1;
        }
        line += 1;
    }

    if (total != 0) {
        mpLib_SetupDraw(mpLib_LeftWallColor);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total * 4) & 0xFFFC);
        line = &groundCollLine[coll_data->ranges[MapLineGroup_LeftWall].start];

        for (i = 0; i < count; i++) {
            if (line->flags & LINE_FLAG_ENABLED &&
                !(line->flags & LINE_FLAG_HIDDEN))
            {
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
            line++;
        }
        GXEnd();
    }

    count = coll_data->ranges[MapLineGroup_Dynamic].count;
    total = 0;
    floor_color = mpLib_DynamicFloorColor;
    ceiling_color = mpLib_DynamicCeilingColor;
    right_wall_color = mpLib_DynamicRightWallColor;
    left_wall_color = mpLib_DynamicLeftWallColor;
    line = &groundCollLine[coll_data->ranges[MapLineGroup_Dynamic].start];

    for (i = 0; i < count; i++) {
        if (line->flags & LINE_FLAG_ENABLED && line->flags & CollLine_Floor &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            total += 1;
        }
        line += 1;
    }

    if (total != 0) {
        mpLib_SetupDraw(floor_color);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total * 4) & 0xFFFC);
        line = &groundCollLine[coll_data->ranges[MapLineGroup_Dynamic].start];

        for (i = 0; i < count; i++) {
            if (line->flags & LINE_FLAG_ENABLED &&
                line->flags & CollLine_Floor &&
                !(line->flags & LINE_FLAG_HIDDEN))
            {
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
            line++;
        }
        GXEnd();
    }
    line = &groundCollLine[coll_data->ranges[MapLineGroup_Dynamic].start];
    total = 0;

    for (i = 0; i < count; i++) {
        if (line->flags & LINE_FLAG_ENABLED &&
            line->flags & CollLine_Ceiling &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            total += 1;
        }
        line += 1;
    }

    if (total != 0) {
        mpLib_SetupDraw(ceiling_color);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total * 4) & 0xFFFC);
        line = &groundCollLine[coll_data->ranges[MapLineGroup_Dynamic].start];

        for (i = 0; i < count; i++) {
            if (line->flags & LINE_FLAG_ENABLED &&
                line->flags & CollLine_Ceiling &&
                !(line->flags & LINE_FLAG_HIDDEN))
            {
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
            line++;
        }
        GXEnd();
    }
    line = &groundCollLine[coll_data->ranges[MapLineGroup_Dynamic].start];
    total = 0;

    for (i = 0; i < count; i++) {
        if (line->flags & LINE_FLAG_ENABLED &&
            line->flags & CollLine_RightWall &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            total += 1;
        }
        line += 1;
    }
    if (total != 0) {
        mpLib_SetupDraw(right_wall_color);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total * 4) & 0xFFFC);
        line = &groundCollLine[coll_data->ranges[MapLineGroup_Dynamic].start];

        for (i = 0; i < count; i++) {
            if (line->flags & LINE_FLAG_ENABLED &&
                line->flags & CollLine_RightWall &&
                !(line->flags & LINE_FLAG_HIDDEN))
            {
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
            line++;
        }
        GXEnd();
    }
    line = &groundCollLine[coll_data->ranges[MapLineGroup_Dynamic].start];
    total = 0;

    for (i = 0; i < count; i++) {
        if (line->flags & LINE_FLAG_ENABLED &&
            line->flags & CollLine_LeftWall &&
            !(line->flags & LINE_FLAG_HIDDEN))
        {
            total += 1;
        }
        line += 1;
    }
    if (total != 0) {
        mpLib_SetupDraw(left_wall_color);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total * 4) & 0xFFFC);
        line = &groundCollLine[coll_data->ranges[MapLineGroup_Dynamic].start];

        for (i = 0; i < count; i++) {
            if (line->flags & LINE_FLAG_ENABLED &&
                line->flags & CollLine_LeftWall &&
                !(line->flags & LINE_FLAG_HIDDEN))
            {
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v1_idx].pos.x,
                               groundCollVtx[line->inner->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line->inner->v0_idx].pos.x,
                               groundCollVtx[line->inner->v0_idx].pos.y,
                               -25.0F);
            }
            line++;
        }
        GXEnd();
    }
}

void mpLib_80059E60(void)
{
    Mtx sp104;
    PAD_STACK(0x30);

    HSD_LObjSetupInit(HSD_CObjGetCurrent());
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp104);
    GXSetCurrentMtx(0U);
    GXLoadPosMtxImm(sp104, 0U);
    if (Camera_80030B50()) {
        // terrain draw
        GXColor basic_color;
        GXColor line_color;
        UNUSED u8 pad[4];
        mpIsland_Palette palette;
        GXColor* color;
        mpIsland_PaletteEntry* entry;
        palette = mpIsland_TerrainPalette;

        entry = palette.entries;
        color = &line_color;

        while (entry->kind != -1) {
            *color = entry->color;
            mpLib_DrawMatchingLines(entry->kind, 0xFF, color);
            entry++;
        }

        basic_color = mpLib_804D8100;
        mpLib_DrawMatchingLines(mp_Terrain_Basic, 0xFF, &basic_color);
    } else if (Camera_80030B7C()) {
        // platform/ledge draw
        GXColor none_color;
        GXColor ledge_platform_color;
        GXColor platform_color;
        GXColor ledge_color;
        PAD_STACK(0x10);
        ledge_color = mpLib_804D80F0;
        mpLib_DrawMatchingLines(LINE_FLAG_LEDGE, LINE_FLAG_LEDGE,
                                &ledge_color);
        platform_color = mpLib_804D80F4;
        mpLib_DrawMatchingLines(LINE_FLAG_PLATFORM, LINE_FLAG_PLATFORM,
                                &platform_color);
        ledge_platform_color = mpLib_804D80F8;
        mpLib_DrawMatchingLines(LINE_FLAG_LEDGE | LINE_FLAG_PLATFORM,
                                LINE_FLAG_LEDGE | LINE_FLAG_PLATFORM,
                                &ledge_platform_color);
        none_color = mpLib_804D80FC;
        mpLib_DrawMatchingLines(0, LINE_FLAG_LEDGE | LINE_FLAG_PLATFORM,
                                &none_color);
    } else {
        mpLib_80059554();
    }
}

void mpLib_DrawCrosses(s16* idx, int len, GXColor color)
{
    Vec3 pos;
    int i;
    UNUSED u8 pad[4];
    int idx_i;
    int out_count;

    for (idx_i = 0, out_count = 0;
         idx_i < len && out_count < (signed) ARRAY_SIZE(mpLib_80458888);
         idx_i++)
    {
        if (Ground_801C2D24(idx[idx_i], &pos)) {
            mpLib_80458888[out_count] = pos;
            out_count += 1;
        }
    }

    if (!out_count) {
        return;
    }

    mpLib_SetupDraw(color);
    GXBegin(GX_LINES, GX_VTXFMT0, out_count * 6);
    for (i = 0; i < out_count; i++) {
        GXPosition3f32(mpLib_80458888[i].x - 3.0F, mpLib_80458888[i].y,
                       mpLib_80458888[i].z);
        GXPosition3f32(3.0F + mpLib_80458888[i].x, mpLib_80458888[i].y,
                       mpLib_80458888[i].z);
        GXPosition3f32(mpLib_80458888[i].x, mpLib_80458888[i].y - 3.0F,
                       mpLib_80458888[i].z);
        GXPosition3f32(mpLib_80458888[i].x, 3.0F + mpLib_80458888[i].y,
                       mpLib_80458888[i].z);
        GXPosition3f32(mpLib_80458888[i].x, mpLib_80458888[i].y,
                       mpLib_80458888[i].z - 3.0F);
        GXPosition3f32(mpLib_80458888[i].x, mpLib_80458888[i].y,
                       3.0F + mpLib_80458888[i].z);
    }
    GXEnd();
}

static const GXColor mpLib_804D8128 = { 0x7D, 0x7D, 0xFF, 0xFF };
static const GXColor mpLib_804D812C = { 0x7D, 0xFF, 0x80, 0xFF };
static const GXColor mpLib_804D8130 = { 0xFF, 0xFF, 0x80, 0xFF };
static const GXColor mpLib_804D8134 = { 0xFF, 0x40, 0x40, 0xFF };
static const GXColor mpLib_804D8138 = { 0xFF, 0x40, 0xC0, 0xFF };
static const GXColor mpLib_804D813C = { 0xFF, 0xFF, 0xFF, 0xFF };

enum mpLib {
    mpLib_EnemySpawnVtxIds = 0x16,
    mpLib_TrophySpawnVtxIds = 0x66,
    mpLib_ExitVtxIds = 0x80,
};

static s16 mpLib_ItemSpawnVtxIds[] = {
    0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A,
    0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0,    0x20, 0x21,
    0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,
    0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
    0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D,
    0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1,
    0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED,
    0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0,    0x99, 0x9A, 0x9B, 0x9C,
    0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8,
    0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0,
    0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,
};

char mpLib_803BF6E0[] =
    "map coll under=%d upper=%d left=%d right=%d bbox=%d\n";

static s16 mpLib_SpawnVtxIds[4] = { 0, 1, 2, 3 };
SDATA s16 mpLib_RespawnVtxIds[6] = { 4, 5, 6, 7, 0, 0 };

void mpLib_DrawSpecialPoints(void)
{
    PAD_STACK(40);
    mpLib_DrawCrosses(mpLib_SpawnVtxIds, 0x04, mpLib_804D8128);
    mpLib_DrawCrosses(mpLib_RespawnVtxIds, 0x04, mpLib_804D812C);
    mpLib_DrawCrosses(mpLib_ItemSpawnVtxIds, 0x15, mpLib_804D8130);
    mpLib_DrawCrosses(&mpLib_ItemSpawnVtxIds[mpLib_EnemySpawnVtxIds], 0x50,
                      mpLib_804D8134);
    mpLib_DrawCrosses(&mpLib_ItemSpawnVtxIds[mpLib_TrophySpawnVtxIds], 0x19,
                      mpLib_804D8138);
    mpLib_DrawCrosses(&mpLib_ItemSpawnVtxIds[mpLib_ExitVtxIds], 0x2E,
                      mpLib_804D813C);
}

void mpLib_8005A2DC(void)
{
    mpLib_DrawSnapping();
    mpLib_80059E60();
    if (mpLib_804D64D0 == 0) {
        mpLib_804D64D0 = 1;
        OSReport(mpLib_803BF6E0, mpLib_804D64D4, mpLib_804D64D8,
                 mpLib_804D64DC, mpLib_804D64E0, mpLib_804D64E4);
    }
    HSD_StateInvalidate(-1);
}

Vec2 mpLib_803BF718[2] = { { -1.0F, -400.0F }, { 1.0F, -400.0F } };
MapLine mpLib_803BF728 = { 0, 1, -1, -1, -1, -1, 1, 0 };
MapJoint mpLib_803BF738 = {
    { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
    -9.0F,
    -408.0F,
    9.0F,
    -392.0F,
    0,
    2,
};
MapCollData mpLib_803BF760 = {
    /*  +0 */ mpLib_803BF718,
    /*  +4 */ 2,
    /*  +8 */ &mpLib_803BF728,
    /*  +C */ 0x00000001,
    /* +10 */ { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
    /* +24 */ &mpLib_803BF738,
    /* +28 */ 0x00000001,
    /* +2C */ 0x00000000,
};

static const GXColor mpLib_804D8140 = { 0xFF, 0xFF, 0xC0, 0xFF };
static const GXColor mpLib_804D8144 = { 0xFF, 0xFF, 0xFF, 0x80 };
static const GXColor mpLib_804D8148 = { 0x80, 0xC0, 0xC0, 0xFF };
static const GXColor mpLib_804D814C = { 0xC0, 0xFF, 0xFF, 0x80 };
static const GXColor mpLib_804D8150[2] = {
    { 0x40, 0x40, 0xFF, 0x00 },
    { 0, 0, 0, 0 },
};

/// blast zones, camera bounds, etc
void mpLib_DrawZones(void)
{
    Mtx mtx;
    u8 _2[0x38];
    GXColor blast_zone_color;
    u8 _5[0x8];
    GXColor cam_bounds_color;
    GXColor cam_bounds_color_copy;
    CmSubject* subject;

    f32 left;
    f32 right;
    f32 bottom;
    f32 top;

    HSD_LObjSetupInit(HSD_CObjGetCurrent());
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), mtx);
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(mtx, 0);

    left = Stage_GetBlastZoneLeftOffset();
    right = Stage_GetBlastZoneRightOffset();
    bottom = Stage_GetBlastZoneBottomOffset();
    top = Stage_GetBlastZoneTopOffset();

    blast_zone_color = mpLib_804D8144;
    mpLib_SetupDraw(mpLib_804D8140);
    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    GXPosition3f32(left, bottom, 0.0F);
    GXPosition3f32(right, bottom, 0.0F);
    GXPosition3f32(right, top, 0.0F);
    GXPosition3f32(left, top, 0.0F);
    GXPosition3f32(left, bottom, 0.0F);

    GXEnd();

    mpLib_SetupDraw(blast_zone_color);
    GXSetZMode(1, GX_GREATER, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    GXPosition3f32(left, bottom, 0.0F);
    GXPosition3f32(right, bottom, 0.0F);
    GXPosition3f32(right, top, 0.0F);
    GXPosition3f32(left, top, 0.0F);
    GXPosition3f32(left, bottom, 0.0F);

    GXEnd();

    left = Stage_GetCamBoundsLeftOffset();
    right = Stage_GetCamBoundsRightOffset();
    bottom = Stage_GetCamBoundsBottomOffset();
    top = Stage_GetCamBoundsTopOffset();

    cam_bounds_color = mpLib_804D814C;
    mpLib_SetupDraw(mpLib_804D8148);

    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    cam_bounds_color_copy = cam_bounds_color;

    GXPosition3f32(left, bottom, 0.0F);
    GXPosition3f32(right, bottom, 0.0F);
    GXPosition3f32(right, top, 0.0F);
    GXPosition3f32(left, top, 0.0F);
    GXPosition3f32(left, bottom, 0.0F);

    GXEnd();

    mpLib_SetupDraw(cam_bounds_color_copy);

    GXSetZMode(1, GX_GREATER, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    GXPosition3f32(left, bottom, 0.0F);
    GXPosition3f32(right, bottom, 0.0F);
    GXPosition3f32(right, top, 0.0F);
    GXPosition3f32(left, top, 0.0F);
    GXPosition3f32(left, bottom, 0.0F);

    GXEnd();

    mpLib_SetupDraw(mpLib_804D8150[0]);

    GXSetZMode(0, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    subject = cm_804D6468;
    while (subject != NULL) {
        if (Camera_8002928C(subject)) {
            GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

            GXPosition3f32(subject->pos.x + subject->ext.h.x,
                           subject->pos.y + subject->ext.v.x, 0.0F);
            GXPosition3f32(subject->pos.x + subject->ext.h.y,
                           subject->pos.y + subject->ext.v.x, 0.0F);
            GXPosition3f32(subject->pos.x + subject->ext.h.y,
                           subject->pos.y + subject->ext.v.y, 0.0F);
            GXPosition3f32(subject->pos.x + subject->ext.h.x,
                           subject->pos.y + subject->ext.v.y, 0.0F);
            GXPosition3f32(subject->pos.x + subject->ext.h.x,
                           subject->pos.y + subject->ext.v.x, 0.0F);

            GXEnd();
        }
        subject = subject->prev;
    }
    HSD_StateInvalidate(-1);
}
