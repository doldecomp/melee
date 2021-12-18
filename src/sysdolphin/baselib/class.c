#include "sysdolphin/baselib/class.h"

extern char lbl_804075CC[];
extern char lbl_80407604[];

extern char lbl_804D5FA8[8]; // "class.c\0";
extern char lbl_804D5FB0[2];


void ClassInfoInit(HSD_ClassInfo* info)
{
    if ((info->head.flags & 1) == 0) {
        (*info->head.info_init)();
    }
}

void hsdInitClassInfo(HSD_ClassInfo* class_info, HSD_ClassInfo* parent_info, char* base_class_library, char* type, s32 info_size, s32 class_size)
{
    class_info->head.flags = 1;
    class_info->head.library_name = base_class_library;
    class_info->head.class_name = type;
    class_info->head.obj_size = (s16)class_size;
    class_info->head.info_size = (s16)info_size;
    class_info->head.parent = parent_info;
    class_info->head.child = NULL;
    class_info->head.next = NULL;
    class_info->head.nb_exist = 0;
    class_info->head.nb_peak = 0;

    if (parent_info != NULL) {
        if ((parent_info->head.flags & 1) == 0) {
            (*parent_info->head.info_init)();
        }
        if (class_info->head.obj_size < parent_info->head.obj_size) {
            __assert(lbl_804D5FA8, 94, lbl_804075CC);
        }
        if (class_info->head.info_size < parent_info->head.info_size) {
            __assert(lbl_804D5FA8, 95, lbl_80407604);
        }
        memcpy(&class_info->alloc, &parent_info->alloc, parent_info->head.info_size - 0x28);
        class_info->head.next = parent_info->head.child;
        parent_info->head.child = class_info;
    }
}

void OSReport_PrintSpaces(s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        OSReport(lbl_804D5FB0);
    }
}
