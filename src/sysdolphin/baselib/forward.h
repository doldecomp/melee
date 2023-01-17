#ifndef SYSDOLPHIN_BASELIB_FORWARD_H
#define SYSDOLPHIN_BASELIB_FORWARD_H

#include <Runtime/platform.h>

typedef struct _HSD_DObj HSD_DObj;
typedef struct _HSD_Fog HSD_Fog;
typedef struct _HSD_LObj HSD_LObj;
typedef struct _HSD_Obj HSD_Obj;
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

typedef void (*HSD_ObjUpdateFunc)(any_t obj, enum_t type, HSD_ObjData* fval);

#endif
