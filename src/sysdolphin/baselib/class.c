/**
 * @file class.c
 * @brief Base class and virtual method table (VMT) system implementation.
 * @details Implements runtime type information (RTTI), dynamic class mutation,
 * virtual method dispatching, class hierarchy management, and bucketed piece memory
 * allocation for the Sysdolphin scene graph engine.
 * Module prefix: HSD (Sysdolphin)
 */

#include "class.h"

#include <string.h>

#include "debug.h"
#include "hash.h"
#include "memory.h"
#include "object.h" // IWYU pragma: keep
#include <dolphin/os.h>

void _hsdClassInfoInit(void);

/// Global root class descriptor for all Sysdolphin classes
HSD_ClassInfo hsdClass = { _hsdClassInfoInit };

/// Dynamic array of memory bucket entries indexed by allocation size
static HSD_MemoryEntry** memory_list;

/// Current capacity of the memory_list bucket array
static s32 nb_memory_list;

/// Hash table for dynamic class lookup by string name
static HSD_Hash* current_hash;

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
/**
 * @brief Lazily ensures that a class descriptor is initialized.
 * @param info Pointer to HSD_ClassInfo descriptor
 */
void ClassInfoInit(HSD_ClassInfo* info)
{
    if ((info->head.flags & 1) == 0) {
        (*info->head.info_init)();
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

/**
 * @brief Registers and initializes a new class descriptor in the inheritance tree.
 * @details Configures metadata, links class into parent's child list, copies parent vtable
 * methods into the new descriptor, and asserts size invariants.
 * @param class_info Descriptor of the new subclass to initialize
 * @param parent_info Descriptor of the base superclass (NULL for root hsdClass)
 * @param base_class_library Library grouping name string
 * @param type Unique class type name string
 * @param info_size Size of the class descriptor struct in bytes
 * @param class_size Size of an object instance in bytes
 */
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
               parent_info->head.info_size - sizeof(HSD_ClassInfoHead));
        class_info->head.next = parent_info->head.child;
        parent_info->head.child = class_info;
    }
}

/**
 * @brief Prints spaces for indented diagnostic hierarchy dumps.
 * @param count Number of space characters to emit
 */
void OSReport_PrintSpaces(s32 count)
{
    s32 i;

    for (i = 0; i < count; i++) {
        OSReport(" ");
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static char unused1[] = "entry %d <null>\n";
static char unused2[] = "entry %d - %d <null>\n";
static char unused3[] = "entry %d(%d)";
static char unused4[] = "  nb_alloc %d nb_free %d\n";
#pragma pop
#endif

/**
 * @brief Retrieves or allocates a memory bucket entry for index idx (representing (idx+1)*32 bytes).
 * @param idx Bucket index
 * @return Pointer to HSD_MemoryEntry, or NULL on allocation failure
 */
HSD_MemoryEntry* GetMemoryEntry(s32 idx)
{
    HSD_ASSERT(171, idx >= 0);

    if (idx >= nb_memory_list) {
        if (nb_memory_list ==
            0) { // In this case, it's uninitialized and allocs the array
            s32 new_nb;

            for (new_nb = 32; idx >= new_nb; new_nb *= 2) {
            }
            memory_list = HSD_MemAlloc(new_nb * sizeof(*memory_list));
            if (memory_list == NULL) {
                return NULL;
            }
            memset(memory_list, 0, new_nb * sizeof(*memory_list));
            nb_memory_list = new_nb;
        } else { // Resizes the array
            HSD_MemoryEntry** old_list;
            HSD_MemoryEntry** new_list;
            s32 old_nb, new_nb;

            new_nb = nb_memory_list * 2;
            while (idx >= new_nb) {
                new_nb *= 2;
            }

            new_list = HSD_MemAlloc(sizeof(*memory_list) * new_nb);
            if (new_list == NULL) {
                return NULL;
            }

            memcpy(new_list, memory_list,
                   sizeof(*memory_list) * nb_memory_list);
            memset(&new_list[nb_memory_list], 0,
               4 * (new_nb -
                    nb_memory_list)); // You start *after* existing ptrs
                                      // and make sure memory is zero'd

            old_list = memory_list;
            old_nb = OSRoundDown32B(nb_memory_list * sizeof(*memory_list));
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
        size_t size = idx * 4;
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

/**
 * @brief Allocates a piece of memory from the bucketed memory allocator.
 * @details Finds or allocates a bucket matching size (rounded up to 32 bytes),
 * pulling from the free-list, carving from larger blocks, or growing the heap.
 * @param size Requested byte size
 * @return Pointer to allocated memory, or NULL on failure
 */
void* hsdAllocMemPiece(s32 size)
{
    HSD_FreeList* free_node;
    HSD_FreeList* split_tail;
    HSD_FreeList* split_block;
    HSD_FreeList* block;
    HSD_MemoryEntry* entry;
    HSD_MemoryEntry* remainder_entry;
    HSD_MemoryEntry* larger_entry;
    HSD_MemoryEntry* tail_entry;
    s32 split_idx;
    s32 bucket_idx;
    void* new_block;

    bucket_idx = (size + 0x1F) / 32 - 1;
    entry = GetMemoryEntry((size + 0x1F) / 32 - 1);
    if (entry == NULL) {
        return NULL;
    }
    /* Case 1: An exact-sized block is already available on the free list */
    if ((free_node = entry->free_list)) {
        entry->free_list = free_node->next;
        entry->nb_free -= 1;
        return free_node;
    }
    /* Case 2: Carve requested size from a larger available block */
    larger_entry = entry->next;
    while (larger_entry != NULL) {
        if (larger_entry->free_list != NULL) {
            remainder_entry = GetMemoryEntry(
                (s32) (larger_entry->size - entry->size + 0x1F) / 32 - 1);
            if (remainder_entry == NULL) {
                return NULL;
            }
            block = larger_entry->free_list;
            larger_entry->free_list = larger_entry->free_list->next;
            larger_entry->nb_free -= 1;
            larger_entry->nb_alloc -= 1;
            split_block = (void*) ((char*) block + entry->size);
            split_block->next = remainder_entry->free_list;
            remainder_entry->free_list = split_block;
            remainder_entry->nb_alloc += 1;
            remainder_entry->nb_free += 1;
            entry->nb_alloc += 1;
            return block;
        }
        larger_entry = larger_entry->next;
    }
    /* Case 3: Allocate a new chunk from the heap and store remaining tail */
    split_idx = (nb_memory_list - bucket_idx) - 2;
    bucket_idx = split_idx;
    if (bucket_idx >= 0) {
        tail_entry = GetMemoryEntry(bucket_idx);
        if (tail_entry == NULL) {
            return NULL;
        }
    }
    new_block = HSD_MemAlloc(nb_memory_list * 32);
    if (new_block == NULL) {
        return NULL;
    }
    if (split_idx >= 0) {
        split_tail = (void*) ((char*) new_block + entry->size);
        split_tail->next = tail_entry->free_list;
        tail_entry->free_list = split_tail;
        tail_entry->nb_alloc += 1;
        tail_entry->nb_free += 1;
    }
    entry->nb_alloc += 1;
    return new_block;
}

/**
 * @brief Returns an allocated memory piece back to its bucket free-list.
 * @param mem Pointer to memory block to free
 * @param size Size in bytes of the block being freed
 */
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

/**
 * @brief Default class allocator method allocating memory for an instance.
 * @param info Pointer to HSD_ClassInfo descriptor
 * @return Pointer to allocated HSD_Class instance
 */
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

/**
 * @brief Default class constructor method.
 * @param arg0 Pointer to HSD_Class instance
 * @return 0 on success
 */
int _hsdClassInit(HSD_Class* arg0)
{
    return 0;
}

/**
 * @brief Default class pre-destructor method (no-op).
 * @param cls Pointer to HSD_Class instance
 */
void _hsdClassRelease(HSD_Class* cls) {}

/**
 * @brief Default class destructor method freeing instance memory.
 * @param cls Pointer to HSD_Class instance
 */
void _hsdClassDestroy(HSD_Class* cls)
{
    HSD_ClassInfo* info = cls->class_info;
    info->head.nb_exist -= 1;
    hsdFreeMemPiece(cls, info->head.obj_size);
}

/**
 * @brief Default class memory reset callback resetting instance counts.
 * @param info Pointer to HSD_ClassInfo descriptor
 */
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

/**
 * @brief Initializes the root HSD_Class descriptor.
 */
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

/**
 * @brief Instantiates and constructs a new object of the given class.
 * @details Allocates memory via info->alloc, zeroes the instance, binds the vtable,
 * and executes constructor info->init.
 * @param i Pointer to HSD_ClassInfo descriptor
 * @return Pointer to newly instantiated object, or NULL on allocation/init failure
 */
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

/**
 * @brief Internal helper to retrieve the class descriptor of an HSD_Obj.
 * @param object Pointer to HSD_Obj
 * @return Pointer to HSD_ClassInfo
 */
static inline HSD_ClassInfo* HSD_GetClassInfo(HSD_Obj* object)
{
    return object->parent.class_info;
}

/**
 * @brief Internal helper to return class descriptor pointer.
 * @param class_info Pointer to HSD_ClassInfo
 * @return Pointer to HSD_ClassInfo
 */
static inline HSD_ClassInfo* HSD_PushClassInfo(HSD_ClassInfo* class_info)
{
    HSD_ClassInfo* ret;
    return ret = class_info;
}

/**
 * @brief Inlined implementation of dynamic class mutation.
 * @param object Pointer to object to reclassify
 * @param class_info Target HSD_ClassInfo to assign
 * @return true if successful, false if sizes or root ancestors mismatch
 */
static inline bool hsdChangeClass_inline(HSD_Obj* object,
                                         HSD_ClassInfo* class_info)
{
    HSD_ClassInfo* src_class;
    HSD_ClassInfo* dst_class;

    HSD_ASSERT(0x249, object);
    HSD_ASSERT(0x24A, class_info);
    src_class = HSD_GetClassInfo(object);
    !src_class;
    dst_class = HSD_PushClassInfo(class_info);
    if (!(dst_class->head.flags & 1)) {
        dst_class->head.info_init();
    }
    if (src_class->head.obj_size != dst_class->head.obj_size) {
        return false;
    }
    while (src_class->head.parent != NULL &&
           src_class->head.parent->head.obj_size == src_class->head.obj_size)
    {
        src_class = src_class->head.parent;
    }
    while (dst_class->head.parent != NULL &&
           dst_class->head.parent->head.obj_size == dst_class->head.obj_size)
    {
        dst_class = dst_class->head.parent;
    }
    if (src_class == dst_class) {
        src_class->head.nb_exist--;
        class_info->head.nb_exist++;
        if (class_info->head.nb_exist > class_info->head.nb_peak) {
            class_info->head.nb_peak = class_info->head.nb_exist;
        }
        object->parent.class_info = class_info;
        return true;
    }
    return false;
}

/**
 * @brief Mutates an existing object's class to another compatible class.
 * @details Verifies that both classes share the exact same instance size and common
 * root ancestor with identical size, updates tracking statistics, and rebinds class_info.
 * @param object Pointer to object to reclassify
 * @param class_info Target HSD_ClassInfo to assign
 * @return true if class was successfully changed, false if incompatible
 */
bool hsdChangeClass(void* object, void* class_info)
{
    return hsdChangeClass_inline(object, class_info);
}

/**
 * @brief RTTI check: determines whether class @p info inherits from class @p p.
 * @param info Subclass descriptor to test
 * @param p Superclass descriptor to test against
 * @return true if info is a descendant of p or equal to p, false otherwise
 */
bool hsdIsDescendantOf(void* info, void* p)
{
    HSD_ClassInfo* curr;
    HSD_ClassInfo* cls = (HSD_ClassInfo*) p;

    if (info == NULL || p == NULL) {
        return false;
    }

    curr =
#ifdef MUST_MATCH
        curr =
#endif
            info;

    if (!(HSD_CLASS_INFO(info)->head.flags & 1)) {
        curr->head.info_init();
    }
    if (!(cls->head.flags & 1)) {
        cls->head.info_init();
    }
    while (curr != NULL) {
        if (curr == cls) {
            return true;
        }
        curr = curr->head.parent;
    }
    return false;
}

/**
 * @brief RTTI check: determines whether object @p o is an instance of class @p p.
 * @param o Object instance to test
 * @param p Superclass descriptor to test against
 * @return true if object's class descends from p, false otherwise
 */
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

/**
 * @brief Updates status flags on a class descriptor.
 * @param class_info Pointer to HSD_ClassInfo
 * @param set Bitmask of flags to set
 * @param reset Bitmask of flags to clear
 */
void class_set_flags(HSD_ClassInfo* class_info, s32 set, s32 reset)
{
    class_info->head.flags = (class_info->head.flags & ~reset) | set;
}

/**
 * @brief Recursively purges a class and all its subclasses from memory.
 * @param class_info Root class descriptor to purge
 */
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

/**
 * @brief Purges child classes matching a library name.
 * @param library_name Name of library to forget
 * @param class_info Parent class descriptor whose children are searched
 */
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

/**
 * @brief Unregisters and purges all classes belonging to a specified library.
 * @param library_name Library grouping name string (defaults to "sysdolphin_base_library" if NULL)
 */
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

/**
 * @brief Searches for a registered class descriptor by its string name.
 * @param class_name ASCII class name string
 * @return Pointer to matching HSD_ClassInfo, or NULL if not found
 */
HSD_ClassInfo* hsdSearchClassInfo(const char* class_name)
{
    if (current_hash != NULL) {
        return HSD_HashSearch(current_hash, (void*) class_name, 0);
    }
    return NULL;
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static char unused5[] = "info_hash";
#pragma pop
#endif

/**
 * @brief Emits formatted diagnostic statistics for a single class.
 * @param info Pointer to HSD_ClassInfo
 * @param level Indentation level
 */
void DumpClassStat(HSD_ClassInfo* info, s32 level)
{
    OSReport_PrintSpaces(level);
    OSReport("<class %s>\n", info->head.class_name);
    OSReport_PrintSpaces(level);
    OSReport("    info %d object %d nb_exist %d nb_peak %d\n",
             info->head.info_size, info->head.obj_size, info->head.nb_exist,
             info->head.nb_peak);
}

/**
 * @brief Emits diagnostic hierarchy statistics for a class and optionally its subclasses.
 * @param info Pointer to HSD_ClassInfo (or NULL to dump from root hsdClass)
 * @param recursive Whether to recursively traverse child subclasses
 * @param level Indentation level
 */
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
