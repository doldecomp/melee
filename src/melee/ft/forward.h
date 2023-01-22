#ifndef MELEE_FT_FORWARD_H
#define MELEE_FT_FORWARD_H

#include <dolphin/mtx/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

typedef struct UnkFloat6_Camera UnkFloat6_Camera;
typedef struct Fighter Fighter;
typedef struct ActionState ActionState;
typedef struct Fighter_CostumeStrings Fighter_CostumeStrings;
typedef struct Fighter_DemoStrings Fighter_DemoStrings;

typedef void (*Fighter_ItemEvent)(HSD_GObj* this, bool arg1);
typedef void (*Fighter_UnkMtxEvent)(HSD_GObj* this, int arg1, Mtx vmtx);
typedef void (*Fighter_ModelEvent)(Fighter* fp, int arg1, bool arg2);

#endif
