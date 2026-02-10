#ifndef MNDIAGRAM3_H
#define MNDIAGRAM3_H

#include <platform.h>

#include <baselib/forward.h>

#include <melee/mn/types.h>

struct Diagram3Data;

typedef struct {
    HSD_Joint* joint;
    HSD_AnimJoint* animjoint;
    HSD_MatAnimJoint* matanimjoint;
    HSD_ShapeAnimJoint* shapeanimjoint;
} StaticModelDesc3;

extern AnimLoopSettings mnDiagram3_803EEC1C;
extern StaticModelDesc3 mnDiagram_804A0844;
extern StaticModelDesc3 mnDiagram_804A0854;
extern char mnDiagram3_803EEC10[];
extern u16 mnDiagram3_803EEC4C[];
extern Vec3 mnDiagram3_803EEC28;
extern SDATA char mnDiagram3_804D4FD8[];
extern SDATA char mnDiagram3_804D4FE0[];
extern f32 mnDiagram3_804DC00C;
extern f32 mnDiagram3_804DC008;
extern f32 mnDiagram3_804DC010;
extern f32 mnDiagram3_804DC014;
extern f64 mnDiagram3_804DC000;
extern f32 mnDiagram3_804DBFF8;
extern f32 mnDiagram3_804DBFFC;
extern s32 mn_804D4B64;

extern HSD_GObj* mnDiagram3_804D6C20;

void mnDiagram3_80246D40(HSD_GObj* gobj);
void fn_80246F0C(void* arg0);
void mnDiagram3_80246F2C(struct Diagram3Data* data, void* arg1);
void mnDiagram3_80247008(void* arg0);
void mnDiagram3_8024714C(void* arg0);
void mnDiagram3_80245BA4(HSD_GObj* gobj);

#endif
