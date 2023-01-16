#ifndef SYSDOLPHIN_BASELIB_FORWARD_H
#define SYSDOLPHIN_BASELIB_FORWARD_H

#include <Runtime/platform.h>

typedef struct _HSD_Obj HSD_Obj;
typedef struct _HSD_Fog HSD_Fog;
typedef union _HSD_ObjData HSD_ObjData;

typedef void (*HSD_AObjUpdateFunc)(any_t obj, enum_t type, HSD_ObjData* fval);

#endif
