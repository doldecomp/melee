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
void it_3F14_Logic26_Spawned(Item_GObj*);
void it_802936E4(Item_GObj*);
bool itKinoko_UnkMotion0_Anim(Item_GObj*);
void itKinoko_UnkMotion0_Phys(Item_GObj*);
bool itKinoko_UnkMotion0_Coll(Item_GObj*);
void it_8029385C(Item_GObj*);
void it_80293884(Item_GObj*);
bool itKinoko_UnkMotion1_Anim(Item_GObj*);
void itKinoko_UnkMotion1_Phys(Item_GObj*);
bool itKinoko_UnkMotion1_Coll(Item_GObj*);
bool it_3F14_Logic26_DmgDealt(Item_GObj*);
void it_3F14_Logic26_EvtUnk(Item_GObj*, HSD_GObj*);

extern ItemStateTable it_803F6110[];

#endif
