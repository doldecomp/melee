#ifndef GALE01_293D94
#define GALE01_293D94

#include <platform.h>
#include "it/forward.h"
#include <baselib/forward.h>

#include "it/types.h"

typedef struct itHammerData {
    u32 x0;
    u32 x4;
    f32 x8;
} itHammerData;

void it_80293D94(Item_GObj* gobj);
int it_80293DCC(Item_GObj* gobj);
void it_80293E34(Item_GObj* gobj);
void it_80293F58(HSD_GObj* gobj);
void it_80293F84(Item_GObj* gobj);
static bool it_80293FF4(HSD_GObj* gobj);
static void it_80293FFC(HSD_GObj* gobj);
static bool it_80294000(HSD_GObj* gobj);
static void it_8029402C(HSD_GObj* gobj);
static int it_80294080(HSD_GObj* gobj);
static void it_80294088(HSD_GObj* gobj);
static int it_802940B8(HSD_GObj* gobj);
void it_802940FC(HSD_GObj* gobj);
static int it_80294170(HSD_GObj* gobj);
void it_802941F8(HSD_GObj* gobj);
static void it_802941A4(HSD_GObj* gobj);
static void it_8029424C(HSD_GObj* gobj);
static bool it_8029427C(HSD_GObj* gobj);
void it_802942B0(HSD_GObj* gobj);
static int it_80294304(HSD_GObj* gobj);
static void it_8029430C(HSD_GObj* gobj);
static int it_80294310(HSD_GObj* gobj);
void it_80294344(Item_GObj* gobj, HSD_GObj* gobj2);

extern ItemStateTable it_803F6150[];

#endif
