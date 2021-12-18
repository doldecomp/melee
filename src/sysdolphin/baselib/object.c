#include "sysdolphin/baselib/object.h"

extern HSD_ClassInfo lbl_804072A8; // hsdObj
extern const char lbl_804072E4[24]; // "sysdolphin_base_library\0"
extern HSD_ClassInfo hsdClass; // hsdClass

void ObjInfoInit(void)
{
    hsdInitClassInfo(&lbl_804072A8, &hsdClass, lbl_804072E4, "hsd_obj", sizeof(HSD_ObjInfo), sizeof(HSD_Obj));
}
