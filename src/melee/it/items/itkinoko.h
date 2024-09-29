#ifndef GALE01_293660
#define GALE01_293660

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

typedef struct KinokoAnim {
    HSD_AnimJoint* joint;
} KinokoAnim;

typedef struct KinokoAttrs {
    f32 x0;
    f32 x4;
    s32 x8;
} KinokoAttrs;

HSD_AnimJoint* it_80293660(int idx);
void it_8029367C(Item_GObj*);
void it_802936E4(Item_GObj*);
bool it_80293754(Item_GObj*);
void it_8029375C(Item_GObj*);
bool it_80293798(Item_GObj*);
void it_8029385C(Item_GObj*);
void it_80293884(Item_GObj*);
bool it_802938AC(Item_GObj*);
void it_802938B4(Item_GObj*);
bool it_80293964(Item_GObj*);
bool it_802939E0(Item_GObj*);
void it_802939E8(Item_GObj*, HSD_GObj*);

extern ItemStateTable it_803F6110[];

#endif
