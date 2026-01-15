#ifndef MELEE_MN_VIBRATION_H
#define MELEE_MN_VIBRATION_H

#include <placeholder.h>

#include <sysdolphin/baselib/forward.h>
#include "mn/types.h"

/// Node structure for vibration data traversal
typedef struct VibNode {
    char x0[8];
    struct VibNode* x8;
    char xC[4];
    struct VibNode* x10;
} VibNode;

/// Container with node pointer at offset 0x50
typedef struct VibNodeContainer {
    char x0[0x50];
    VibNode* x50;
} VibNodeContainer;

/// Main vibration data structure
typedef struct VibData {
    char x0[0x2C];
    VibNodeContainer* x2C;
} VibData;

/// Data with jobj at offset 0x10
typedef struct VibJObjData {
    char x0[0x10];
    void* x10;
} VibJObjData;

/* 2474C4 */ void* mnVibration_802474C4(s32 arg0);
/* 247510 */ UNK_RET fn_80247510(UNK_PARAMS);
/* 248084 */ void fn_80248084(HSD_GObj* gobj);
/* 2480B4 */ UNK_RET mnVibration_802480B4(UNK_PARAMS);
/* 24829C */ UNK_RET mnVibration_8024829C(UNK_PARAMS);
/* 248444 */ UNK_RET mnVibration_80248444(UNK_PARAMS);
/* 248644 */ UNK_RET mnVibration_80248644(UNK_PARAMS);
/* 248748 */ void fn_80248748(HSD_GObj* gobj);
/* 2487A8 */ UNK_RET fn_802487A8(UNK_PARAMS);
/* 248A78 */ UNK_RET fn_80248A78(UNK_PARAMS);
/* 248ED4 */ UNK_RET mnVibration_80248ED4(UNK_PARAMS);
/* 249174 */ void mnVibration_80249174(int arg0);

/* 3EECEC */ extern AnimLoopSettings mnVibration_803EECEC;
/* 4D6C28 */ extern VibData* mnVibration_804D6C28;

#endif
