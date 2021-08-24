#include "object.h"

extern HSD_ClassInfo lbl_804072A8; // hsdObj
extern const char lbl_804072E4[24]; // "sysdolphin_base_library\0"
extern HSD_ClassInfo lbl_80407590; // hsdClass
extern char lbl_804D5F68[8]; // "hsd_obj\0"

void ObjInfoInit(void)
{
    hsdInitClassInfo(&lbl_804072A8, &lbl_80407590, lbl_804072E4, lbl_804D5F68, sizeof(HSD_ObjInfo), sizeof(HSD_Obj));
}
