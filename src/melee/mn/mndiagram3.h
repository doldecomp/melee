#ifndef MNDIAGRAM3_H
#define MNDIAGRAM3_H

#include <placeholder.h>

#include <baselib/forward.h>

#include <baselib/gobj.h>
#include <melee/mn/types.h>

/* 245BA4 */ void mnDiagram3_PopulateRankings(HSD_GObj* gobj);
/* 246D40 */ void mnDiagram3_UpdateScrollArrows(HSD_GObj* gobj);
/* 246E04 */ void mnDiagram3_OnAnimComplete(HSD_GObj* gobj);
/* 246E64 */ void mnDiagram3_Think(HSD_GObj* gobj);
/* 246F0C */ void mnDiagram3_FreeUserData(void* arg0);
/* 246F2C */ void mnDiagram3_InitUserData(Diagram3* data, int arg1);
/* 247008 */ void mnDiagram3_Create(int arg0);
/* 24714C */ void mnDiagram3_Init(void* arg0);

#endif
