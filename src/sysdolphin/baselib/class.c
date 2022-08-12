#include <sysdolphin/baselib/class.h>

#include <dolphin/os/os.h>
#include <sysdolphin/baselib/memory.h>

extern void func_803822C0();

HSD_ClassInfo hsdClass = { func_803822C0 };

extern char lbl_80407698[]; // "idx >= 0"

extern char lbl_804D5FA8[8]; // "class.c\0";
extern char lbl_804D5FB0[2];

extern HSD_MemoryEntry** memory_list;
extern s32 nb_memory_list;

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
            __assert(lbl_804D5FA8, 94, "class_info->head.obj_size >= parent_info->head.obj_size");
        }
        if (class_info->head.info_size < parent_info->head.info_size) {
            __assert(lbl_804D5FA8, 95, "class_info->head.info_size >= parent_info->head.info_size");
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

HSD_MemoryEntry* GetMemoryEntry(s32 idx)
{
    if (idx < 0) {
        __assert(lbl_804D5FA8, 171, lbl_80407698);
    }

    if (idx >= nb_memory_list) {
        if (nb_memory_list == 0) { //In this case, it's uninitialized and allocs the array
            s32 new_nb;

            for (new_nb = 32; idx >= new_nb; new_nb *= 2) {
            }
            memory_list = (HSD_MemoryEntry**)HSD_MemAlloc(new_nb * 4);
            if (memory_list == NULL) {
                return NULL;
            }
            memset(memory_list, 0, new_nb*4);
            nb_memory_list = new_nb;
        } else { //Resizes the array
            HSD_MemoryEntry** old_list;
            HSD_MemoryEntry** new_list;
            s32 old_nb, new_nb;

            new_nb = nb_memory_list * 2;
            while (idx >= new_nb) {
                new_nb *= 2;
            }
            
            new_list = HSD_MemAlloc(4 * new_nb);
            if (new_list == NULL) {
                return NULL;
            }

            memcpy(new_list, memory_list, 4 * nb_memory_list);
            memset(&new_list[nb_memory_list], 0, 4 * (new_nb - nb_memory_list)); //You start *after* existing ptrs and make sure memory is zero'd
    
            old_list = memory_list;
            old_nb = OSRoundDown32B(nb_memory_list * 4);
            memory_list = new_list;
            nb_memory_list = new_nb;

            hsdFreeMemPiece(old_list, old_nb);
            memory_list[OSRoundUp32B(old_nb)/32 - 1]->nb_alloc += 1;
        }
    }

    {
        s32 i;
        u32 size;
        BOOL found;
        HSD_MemoryEntry* entry;

        size = idx * 4;
        if (memory_list[idx] == NULL) {
            entry = HSD_MemAlloc(sizeof(HSD_MemoryEntry));
            if (entry == NULL) {
                return NULL;
            }
            memset(entry, 0, sizeof(HSD_MemoryEntry));
            entry->size = (idx + 1) * 32;
            memory_list[idx] = entry;
            
            found = FALSE;
            for (i = idx - 1; i >= 0; --i) {
                if (memory_list[i] != NULL) {
                    found = TRUE;
                    entry->next = memory_list[i]->next;
                    memory_list[i]->next = entry;
                    break;
                }
            }
            if (found == FALSE) {
                for (i = idx + 1; i < nb_memory_list; i++) {
                    if (memory_list[i] != NULL) {
                        entry->next = memory_list[i];
                        break;
                    }
                }
            }
        }
        return memory_list[idx];
    }
}
