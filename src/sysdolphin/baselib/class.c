#include "class.h"

#include "debug.h"
#include "hash.h"
#include "memory.h"
#include "object.h" // IWYU pragma: keep

#include <__mem.h>
#include <string.h>
#include <dolphin/os.h>

void _hsdClassInfoInit(void);
HSD_ClassInfo hsdClass = { _hsdClassInfoInit };

static HSD_MemoryEntry** memory_list;
static s32 nb_memory_list;
static HSD_Hash* current_hash;

#pragma push
#pragma dont_inline on
void ClassInfoInit(HSD_ClassInfo* info)
{
    if ((info->head.flags & 1) == 0) {
        (*info->head.info_init)();
    }
}
#pragma pop

void hsdInitClassInfo(HSD_ClassInfo* class_info, HSD_ClassInfo* parent_info,
                      char* base_class_library, char* type, s32 info_size,
                      s32 class_size)
{
    class_info->head.flags = 1;
    class_info->head.library_name = base_class_library;
    class_info->head.class_name = type;
    class_info->head.obj_size = (s16) class_size;
    class_info->head.info_size = (s16) info_size;
    class_info->head.parent = parent_info;
    class_info->head.child = NULL;
    class_info->head.next = NULL;
    class_info->head.nb_exist = 0;
    class_info->head.nb_peak = 0;

    if (parent_info != NULL) {
        if ((parent_info->head.flags & 1) == 0) {
            (*parent_info->head.info_init)();
        }
        HSD_ASSERT(94, class_info->head.obj_size >= parent_info->head.obj_size);
        HSD_ASSERT(95, class_info->head.info_size >= parent_info->head.info_size);
        memcpy(&class_info->alloc, &parent_info->alloc,
               parent_info->head.info_size - 0x28);
        class_info->head.next = parent_info->head.child;
        parent_info->head.child = class_info;
    }
}

void OSReport_PrintSpaces(s32 count)
{
    s32 i;

    for (i = 0; i < count; i++) {
        OSReport(" ");
    }
}

#ifndef BUGFIX
#pragma push
#pragma force_active on
static char unused1[] = "entry %d <null>\n";
static char unused2[] = "entry %d - %d <null>\n";
static char unused3[] = "entry %d(%d)";
static char unused4[] = "  nb_alloc %d nb_free %d\n";
#pragma pop
#endif

HSD_MemoryEntry* GetMemoryEntry(s32 idx)
{
    HSD_ASSERT(171, idx >= 0);

    if (idx >= nb_memory_list) {
        if (nb_memory_list == 0)
        { // In this case, it's uninitialized and allocs the array
            s32 new_nb;

            for (new_nb = 32; idx >= new_nb; new_nb *= 2) {
            }
            memory_list = (HSD_MemoryEntry**) HSD_MemAlloc(new_nb * 4);
            if (memory_list == NULL) {
                return NULL;
            }
            memset(memory_list, 0, new_nb * 4);
            nb_memory_list = new_nb;
        } else { // Resizes the array
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
            memset(&new_list[nb_memory_list], 0,
                   4 * (new_nb -
                        nb_memory_list)); // You start *after* existing ptrs
                                          // and make sure memory is zero'd

            old_list = memory_list;
            old_nb = OSRoundDown32B(nb_memory_list * 4);
            memory_list = new_list;
            nb_memory_list = new_nb;

            hsdFreeMemPiece(old_list, old_nb);
            memory_list[OSRoundUp32B(old_nb) / 32 - 1]->nb_alloc += 1;
        }
    }

    {
        ssize_t i;
        bool found;
        HSD_MemoryEntry* entry;
        usize_t size = idx * 4;
        if (memory_list[idx] == NULL) {
            entry = HSD_MemAlloc(sizeof(HSD_MemoryEntry));
            if (entry == NULL) {
                return NULL;
            }
            memset(entry, 0, sizeof(HSD_MemoryEntry));
            entry->size = (idx + 1) * 32;
            memory_list[idx] = entry;

            found = false;
            for (i = idx - 1; i >= 0; --i) {
                if (memory_list[i] != NULL) {
                    found = true;
                    entry->next = memory_list[i]->next;
                    memory_list[i]->next = entry;
                    break;
                }
            }
            if (found == false) {
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

void* hsdAllocMemPiece(s32 size)
{
    HSD_FreeList* temp_r3_2;
    HSD_FreeList* temp_r4;
    HSD_FreeList* temp_r4_2;
    HSD_FreeList* temp_r5;
    HSD_MemoryEntry* temp_r3_3;
    HSD_MemoryEntry* temp_r3_4;
    HSD_MemoryEntry* var_r28;
    HSD_MemoryEntry* var_r30;
    s32 temp_r28;
    s32 temp_r29;
    void* temp_r3;

    temp_r29 = (size + 0x1F) / 32 - 1;
    temp_r3_3 = GetMemoryEntry((size + 0x1F) / 32 - 1);
    if (temp_r3_3 == NULL) {
        return NULL;
    }
    if ((temp_r3_2 = temp_r3_3->free_list)) {
        temp_r3_3->free_list = temp_r3_2->next;
        temp_r3_3->nb_free -= 1;
        return temp_r3_2;
    }
    var_r28 = temp_r3_3->next;
    while (var_r28 != NULL) {
        if (var_r28->free_list != NULL) {
            temp_r3_4 = GetMemoryEntry(
                (s32) (var_r28->size - temp_r3_3->size + 0x1F) / 32 - 1);
            if (temp_r3_4 == NULL) {
                return NULL;
            }
            temp_r5 = var_r28->free_list;
            var_r28->free_list = var_r28->free_list->next;
            var_r28->nb_free -= 1;
            var_r28->nb_alloc -= 1;
            temp_r4_2 = (void*) ((char*) temp_r5 + temp_r3_3->size);
            temp_r4_2->next = temp_r3_4->free_list;
            temp_r3_4->free_list = temp_r4_2;
            temp_r3_4->nb_alloc += 1;
            temp_r3_4->nb_free += 1;
            temp_r3_3->nb_alloc += 1;
            return temp_r5;
        }
        var_r28 = var_r28->next;
    }
    temp_r28 = (nb_memory_list - temp_r29) - 2;
    temp_r29 = temp_r28;
    if (temp_r29 >= 0) {
        var_r30 = GetMemoryEntry(temp_r29);
        if (var_r30 == NULL) {
            return NULL;
        }
    }
    temp_r3 = HSD_MemAlloc(nb_memory_list * 32);
    if (temp_r3 == NULL) {
        return NULL;
    }
    if (temp_r28 >= 0) {
        temp_r4 = (void*) ((char*) temp_r3 + temp_r3_3->size);
        temp_r4->next = var_r30->free_list;
        var_r30->free_list = temp_r4;
        var_r30->nb_alloc += 1;
        var_r30->nb_free += 1;
    }
    temp_r3_3->nb_alloc += 1;
    return temp_r3;
}

void hsdFreeMemPiece(void* mem, s32 size)
{
    HSD_MemoryEntry* entry;
    HSD_FreeList* piece = (HSD_FreeList*) mem;

    if (mem != NULL) {
        entry = GetMemoryEntry((size + 31) / 32 - 1);
        piece->next = entry->free_list;
        entry->free_list = piece;
        entry->nb_free += 1;
    }
}

/// _hsdClassAlloc
HSD_Class* _hsdClassAlloc(HSD_ClassInfo* info)
{
    HSD_Class* mem_piece = hsdAllocMemPiece(info->head.obj_size);
    if (mem_piece != NULL) {
        info->head.nb_exist += 1;
        if (info->head.nb_exist > info->head.nb_peak) {
            info->head.nb_peak = info->head.nb_exist;
        }
    }
    return mem_piece;
}

int _hsdClassInit(HSD_Class* arg0)
{
    return 0;
}

void _hsdClassRelease(HSD_Class* cls) {}

void _hsdClassDestroy(HSD_Class* cls)
{
    HSD_ClassInfo* info = cls->class_info;
    info->head.nb_exist -= 1;
    hsdFreeMemPiece(cls, info->head.obj_size);
}

void _hsdClassAmnesia(HSD_ClassInfo* info)
{
    info->head.nb_exist = 0;
    info->head.nb_peak = 0;
    if (info == &hsdClass) {
        nb_memory_list = 0;
        memory_list = NULL;
        current_hash = NULL;
    }
}

void _hsdClassInfoInit(void)
{
    hsdInitClassInfo(&hsdClass, NULL, "sysdolphin_base_library", "hsd_class",
                     sizeof(HSD_ClassInfo), sizeof(HSD_Class));
    hsdClass.alloc = _hsdClassAlloc;
    hsdClass.init = _hsdClassInit;
    hsdClass.release = _hsdClassRelease;
    hsdClass.destroy = _hsdClassDestroy;
    hsdClass.amnesia = _hsdClassAmnesia;
}

void* hsdNew(HSD_ClassInfo* i)
{
    HSD_ClassInfo* info = i;
    HSD_ClassInfo* info2 = info;
    HSD_Class* cls;
    if (!(info2->head.flags & 1)) {
        info2->head.info_init();
    }
    cls = info->alloc(info2);
    if (cls == NULL) {
        return NULL;
    }
    ClassInfoInit(info);
    memset(cls, 0, info->head.obj_size);
    cls->class_info = info;
    if (info->init(cls) < 0) {
        info->destroy(cls);
        return NULL;
    }
    return cls;
}

inline HSD_ClassInfo* HSD_GetClassInfo(HSD_Obj* object)
{
    return object->parent.class_info;
}

inline HSD_ClassInfo* HSD_PushClassInfo(HSD_ClassInfo* class_info)
{
    HSD_ClassInfo* ret;
    return ret = class_info;
}

inline bool hsdChangeClass_inline(HSD_Obj* object, HSD_ClassInfo* class_info)
{
    HSD_ClassInfo* var_r29;
    HSD_ClassInfo* var_r28;

    HSD_ASSERT(0x249, object);
    HSD_ASSERT(0x24A, class_info);
    var_r29 = HSD_GetClassInfo(object);
    !var_r29;
    var_r28 = HSD_PushClassInfo(class_info);
    if (!(var_r28->head.flags & 1)) {
        var_r28->head.info_init();
    }
    if (var_r29->head.obj_size != var_r28->head.obj_size) {
        return false;
    }
    while (var_r29->head.parent != NULL &&
           var_r29->head.parent->head.obj_size == var_r29->head.obj_size)
    {
        var_r29 = var_r29->head.parent;
    }
    while (var_r28->head.parent != NULL &&
           var_r28->head.parent->head.obj_size == var_r28->head.obj_size)
    {
        var_r28 = var_r28->head.parent;
    }
    if (var_r29 == var_r28) {
        var_r29->head.nb_exist--;
        class_info->head.nb_exist++;
        if (class_info->head.nb_exist > class_info->head.nb_peak) {
            class_info->head.nb_peak = class_info->head.nb_exist;
        }
        object->parent.class_info = class_info;
        return true;
    }
    return false;
}

bool hsdChangeClass(void* object, void* class_info)
{
    return hsdChangeClass_inline(object, class_info);
}

bool hsdIsDescendantOf(void* info, void* p)
{
    HSD_ClassInfo* var_r31;
    HSD_ClassInfo* cls = (HSD_ClassInfo*) p;

    if (info == NULL || p == NULL) {
        return false;
    }

    var_r31 = var_r31 = info;

    if (!(HSD_CLASS_INFO(info)->head.flags & 1)) {
        var_r31->head.info_init();
    }
    if (!(cls->head.flags & 1)) {
        cls->head.info_init();
    }
    while (var_r31 != NULL) {
        if (var_r31 == cls) {
            return true;
        }
        var_r31 = var_r31->head.parent;
    }
    return false;
}

bool hsdObjIsDescendantOf(HSD_Obj* o, HSD_ClassInfo* p)
{
    HSD_ClassInfo* info;

    if (o == NULL || p == NULL) {
        return false;
    }
    info = o->parent.class_info;
    if (!(p->head.flags & 1)) {
        p->head.info_init();
    }
    while (info != NULL) {
        if (info == p) {
            return true;
        }
        info = info->head.parent;
    }
    return false;
}

void class_set_flags(HSD_ClassInfo* class_info, s32 set, s32 reset)
{
    class_info->head.flags = (class_info->head.flags & ~reset) | set;
}

void ForgetClassLibraryReal(HSD_ClassInfo* class_info)
{
    HSD_ClassInfo* cur = class_info->head.child;
    HSD_ClassInfo* next;
    while (cur != NULL) {
        next = cur->head.next;
        cur->head.next = NULL;
        ForgetClassLibraryReal(cur);
        cur = next;
    }
    class_info->amnesia(class_info);
    class_info->head.child = NULL;
    class_info->head.parent = NULL;
    class_set_flags(class_info, 0, 1);
}

void ForgetClassLibraryChild(const char* library_name,
                             HSD_ClassInfo* class_info)
{
    HSD_ClassInfo** cur = &class_info->head.child;
    while (*cur != NULL) {
        if (strcmp(library_name, (*cur)->head.library_name) == 0) {
            ForgetClassLibraryReal(*cur);
            *cur = (*cur)->head.next;
        } else {
            cur = &(*cur)->head.next;
        }
    }
}

void hsdForgetClassLibrary(const char* library_name)
{
    if (library_name == NULL) {
        library_name = "sysdolphin_base_library";
    }
    if (!(hsdClass.head.flags & 1)) {
        return;
    }
    if (strcmp(library_name, hsdClass.head.library_name) == 0) {
        current_hash = NULL;
        ForgetClassLibraryReal(&hsdClass);
    } else {
        ForgetClassLibraryChild(library_name, &hsdClass);
    }
}

HSD_ClassInfo* hsdSearchClassInfo(const char* class_name)
{
    if (current_hash != NULL) {
        return (HSD_ClassInfo*) HSD_HashSearch(current_hash,
                                               (void*) class_name, 0);
    }
    return NULL;
}

#ifndef BUGFIX
#pragma push
#pragma force_active on
static char unused5[] = "info_hash";
#pragma pop
#endif

void DumpClassStat(HSD_ClassInfo* info, s32 level)
{
    OSReport_PrintSpaces(level);
    OSReport("<class %s>\n", info->head.class_name);
    OSReport_PrintSpaces(level);
    OSReport("    info %d object %d nb_exist %d nb_peak %d\n",
             info->head.info_size, info->head.obj_size, info->head.nb_exist,
             info->head.nb_peak);
}

void hsdDumpClassStat(HSD_ClassInfo* info, bool recursive, s32 level)
{
    if (info == NULL) {
        hsdDumpClassStat(&hsdClass, true, level);
    } else if (info->head.flags & 1) {
        DumpClassStat(info, level);
        if (recursive) {
            level += 2;
            info = info->head.child;
            while (info != NULL) {
                hsdDumpClassStat(info, true, level);
                info = info->head.next;
            }
        }
    }
}
