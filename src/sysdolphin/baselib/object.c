#include <sysdolphin/baselib/object.h>

HSD_ClassInfo hsdObj = { ObjInfoInit };
extern HSD_ClassInfo hsdClass;

void ObjInfoInit(void)
{
    hsdInitClassInfo(&hsdObj, &hsdClass, "sysdolphin_base_library", "hsd_obj", sizeof(HSD_ObjInfo), sizeof(HSD_Obj));
}
