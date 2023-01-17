#ifndef SYSDOLPHIN_BASELIB_FORWARD_H
#define SYSDOLPHIN_BASELIB_FORWARD_H

#include <Runtime/platform.h>

typedef struct HSD_AObj HSD_AObj;
typedef struct _HSD_DObj HSD_DObj;
typedef struct _HSD_Fog HSD_Fog;
typedef struct _HSD_LObj HSD_LObj;
typedef struct _HSD_Obj HSD_Obj;
typedef struct HSD_GObj HSD_GObj;
typedef union _HSD_ObjData HSD_ObjData;
typedef struct _TextKerning TextKerning;
typedef struct HSD_PadRumbleListData HSD_PadRumbleListData;
typedef struct Struct804C22E0 Struct804C22E0;
typedef struct RumbleCommand RumbleCommand;
typedef union HSD_Rumble HSD_Rumble;
typedef struct HSD_RumbleData HSD_RumbleData;
typedef struct HSD_PadData HSD_PadData;
typedef struct HSD_PadStatus HSD_PadStatus;
typedef struct PadLibData PadLibData;
typedef struct RumbleInfo RumbleInfo;
typedef struct HSD_TObj HSD_TObj;
typedef struct HSD_RObj HSD_RObj;
typedef struct HSD_PObj HSD_PObj;
typedef struct HSD_MObj HSD_MObj;
typedef struct HSD_JObj HSD_JObj;

typedef void (*HSD_ObjUpdateFunc)(any_t obj, enum_t type, HSD_ObjData* fval);
typedef void (*HSD_DevComCallback)(int, int, int, bool cancelflag);

#endif
