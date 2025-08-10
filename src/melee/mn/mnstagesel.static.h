#ifndef __GALE01_2599EC
#define __GALE01_2599EC

#include "platform.h"

#include <placeholder.h>

#include <melee/mn/forward.h>
#include <melee/sc/types.h>

struct stagelistinfo {
    HSD_JObj* x0;
    int x4;
    u8 x8, x9, xA, xB;
    f32 xC, x10, x14, x18;
} mnStageSel_803F06D0[30] = {
    { 0, 0, 0x2, 0x00, 0x00, 0x04, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x01, 0x0C, 0x0B, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x02, 0x01, 0x05, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x03, 0x0D, 0x0C, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x04, 0x02, 0x0D, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x05, 0x0E, 0x0E, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x08, 0x04, 0x08, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x09, 0x10, 0x10, 2.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0A, 0x05, 0x02, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0B, 0x11, 0x11, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0C, 0x06, 0x07, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0D, 0x12, 0x16, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x06, 0x03, 0x06, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x07, 0x0F, 0x0F, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x12, 0x09, 0x09, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x13, 0x15, 0x12, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x10, 0x08, 0x0A, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x11, 0x14, 0x18, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0E, 0x07, 0x03, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0F, 0x13, 0x17, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x14, 0x0B, 0x13, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x15, 0x16, 0x14, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x16, 0x0A, 0x19, 3.1F, 2.9F, 1.0F, 1.1F },
    { 0, 0, 0x2, 0x17, 0x17, 0x1B, 3.1F, 2.9F, 1.0F, 1.1F },
    { 0, 0, 0x2, 0x18, 0x18, 0x1F, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x19, 0x19, 0x20, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1A, 0x1A, 0x1C, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1B, 0x1B, 0x1D, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1C, 0x1C, 0x1E, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1D, 0x00, 0x00, 3.6F, 2.7F, 1.2F, 1.0F },
};
static s8 mnStageSel_804D50A0 = -1;

static SSSData* mnStageSel_804D6C90;
static HSD_Archive* mnStageSel_804D6C94;
static struct mnStageSel_804D6C98_t {
    StaticModelDesc x0;
    StaticModelDesc x10;
    StaticModelDesc x20;
    StaticModelDesc x30;
    StaticModelDesc x40;
    StaticModelDesc x50;
    StaticModelDesc x60;
    StaticModelDesc x70;
    StaticModelDesc x80;
    StaticModelDesc x90;
    StaticModelDesc xA0;
    HSD_Joint* xB0;
    HSD_AnimJoint* xB4;
    HSD_MatAnimJoint* xB8;
    HSD_ShapeAnimJoint* xBC;
}* mnStageSel_804D6C98;
static HSD_GObj* mnStageSel_804D6C9C;
static u32 mnStageSel_804D6CA0;
static u32 mnStageSel_804D6CA4;
static s32 mnStageSel_804D6CA8;
static s8 mnStageSel_804D6CAC;
static s8 mnStageSel_804D6CAD;
static u8 mnStageSel_804D6CAE;
static u8 mnStageSel_804D6CAF;

#ifndef M2CTX
STATIC_ASSERT(sizeof(mnStageSel_803F06D0[0]) == 0x1C);
#endif

struct StageSelUserData {
    u16 x0;
    u16 x2;
    int x4;
};

#define MAX_ITER 100000
#define NUM_STAGES 29

#endif
