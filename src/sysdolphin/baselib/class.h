/**
 * @file class.h
 * @brief Base class and virtual method table (VMT) system declarations.
 * @details Implements the object-oriented programming (OOP) foundation for the Sysdolphin engine,
 * providing single inheritance, dynamic polymorphism, virtual method dispatch (alloc, init,
 * release, destroy, amnesia), runtime type information (RTTI), class tree introspection,
 * and bucketed piece memory management.
 * Module prefix: HSD (Sysdolphin)
 */

#ifndef _class_h_
#define _class_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

/// Casts any pointer to an HSD_ClassInfo vtable pointer
#define HSD_CLASS_INFO(o) ((HSD_ClassInfo*) o)

/// Accesses the virtual method table (vtable) from an HSD_Class instance
#define HSD_CLASS_METHOD(o) (((HSD_Class*) o)->class_info)

/// Accesses the parent class vtable descriptor
#define HSD_PARENT_INFO(o) ((o)->parent.head.parent)

/// Safe list progression macro: returns p->next if p != NULL, else NULL
#define next_p(p) (p != NULL ? p->next : NULL)

/**
 * @brief Base instance structure for all polymorphic Sysdolphin objects.
 * @details Every HSD object begins with a pointer to its class descriptor (vtable).
 */
typedef struct _HSD_Class {
    struct _HSD_ClassInfo* class_info; ///< Pointer to the virtual method table and class metadata
} HSD_Class;

/**
 * @brief Header metadata describing a Sysdolphin class and its position in the class tree.
 */
typedef struct _HSD_ClassInfoHead {
    void (*info_init)(void);            ///< Lazy initialization callback for this class (offset 0x00)
    u32 flags;                          ///< Class status flags (bit 0 = initialized) (offset 0x04)
    char* library_name;                 ///< Library grouping string (e.g. "sysdolphin_base_library") (offset 0x08)
    char* class_name;                   ///< Name identifier for this class (e.g. "hsd_class") (offset 0x0C)
    s16 obj_size;                       ///< Size of an instance of this class in bytes (offset 0x10)
    s16 info_size;                      ///< Size of this class's ClassInfo descriptor in bytes (offset 0x12)
    struct _HSD_ClassInfo* parent;      ///< Pointer to superclass ClassInfo (offset 0x14)
    struct _HSD_ClassInfo* next;        ///< Sibling class in inheritance tree (offset 0x18)
    struct _HSD_ClassInfo* child;       ///< First subclass in inheritance tree (offset 0x1C)
    u32 nb_exist;                       ///< Currently active instance count (offset 0x20)
    u32 nb_peak;                        ///< Peak simultaneous instance count (offset 0x24)
} HSD_ClassInfoHead;

/**
 * @brief Full class descriptor and virtual method table for Sysdolphin objects.
 */
typedef struct _HSD_ClassInfo {
    struct _HSD_ClassInfoHead head;               ///< Class metadata and tree links (offset 0x00)
    HSD_Class* (*alloc)(struct _HSD_ClassInfo* c);///< Virtual allocator: allocates instance memory (offset 0x28)
    int (*init)(struct _HSD_Class* c);            ///< Virtual constructor: initializes instance fields (offset 0x2C)
    void (*release)(struct _HSD_Class* c);        ///< Virtual pre-destructor: releases child references (offset 0x30)
    void (*destroy)(struct _HSD_Class* c);        ///< Virtual destructor: deallocates instance memory (offset 0x34)
    void (*amnesia)(struct _HSD_ClassInfo* c);    ///< Virtual memory purge callback for class (offset 0x38)
} HSD_ClassInfo;

/**
 * @brief Free-list node for bucketed piece memory allocator.
 */
typedef struct _HSD_FreeList {
    struct _HSD_FreeList* next; ///< Pointer to next free memory block in bucket
} HSD_FreeList;

/**
 * @brief Memory bucket entry managing fixed-size allocations in 32-byte increments.
 */
typedef struct _HSD_MemoryEntry {
    u32 size;                       ///< Block size in bytes for this bucket (multiple of 32)
    u32 nb_alloc;                   ///< Total number of blocks allocated from this bucket
    u32 nb_free;                    ///< Number of currently available free blocks in bucket
    struct _HSD_FreeList* free_list;///< Head of free block singly-linked list
    struct _HSD_MemoryEntry* next;  ///< Next memory entry in linked bucket chain
} HSD_MemoryEntry;

/// Root class descriptor for the Sysdolphin class hierarchy
extern HSD_ClassInfo hsdClass;

/**
 * @brief Lazily ensures that a class descriptor is initialized.
 * @param info Pointer to HSD_ClassInfo descriptor
 */
void ClassInfoInit(HSD_ClassInfo* info);

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
                      s32 class_size);

/**
 * @brief Prints spaces for indented diagnostic hierarchy dumps.
 * @param count Number of space characters to emit
 */
void OSReport_PrintSpaces(s32 count);

/**
 * @brief Allocates a piece of memory from the bucketed memory allocator.
 * @details Finds or allocates a bucket matching size (rounded up to 32 bytes),
 * pulling from the free-list, carving from larger blocks, or growing the heap.
 * @param size Requested byte size
 * @return Pointer to allocated memory, or NULL on failure
 */
void* hsdAllocMemPiece(s32 size);

/**
 * @brief Returns an allocated memory piece back to its bucket free-list.
 * @param mem Pointer to memory block to free
 * @param size Size in bytes of the block being freed
 */
void hsdFreeMemPiece(void* mem, s32 size);

/**
 * @brief Instantiates and constructs a new object of the given class.
 * @details Allocates memory via info->alloc, zeroes the instance, binds the vtable,
 * and executes constructor info->init.
 * @param info Pointer to HSD_ClassInfo descriptor
 * @return Pointer to newly instantiated object, or NULL on allocation/init failure
 */
void* hsdNew(HSD_ClassInfo* info);

/**
 * @brief Mutates an existing object's class to another compatible class.
 * @details Verifies that both classes share the exact same instance size and common
 * root ancestor with identical size, updates tracking statistics, and rebinds class_info.
 * @param object Pointer to object to reclassify
 * @param class_info Target HSD_ClassInfo to assign
 * @return true if class was successfully changed, false if incompatible
 */
bool hsdChangeClass(void* object, void* class_info);

/**
 * @brief RTTI check: determines whether class @p info inherits from class @p p.
 * @param info Subclass descriptor to test
 * @param p Superclass descriptor to test against
 * @return true if info is a descendant of p or equal to p, false otherwise
 */
bool hsdIsDescendantOf(void* info, void* p);

/**
 * @brief RTTI check: determines whether object @p o is an instance of class @p p.
 * @param o Object instance to test
 * @param p Superclass descriptor to test against
 * @return true if object's class descends from p, false otherwise
 */
bool hsdObjIsDescendantOf(HSD_Obj* o, HSD_ClassInfo* p);

/**
 * @brief Searches for a registered class descriptor by its string name.
 * @param class_name ASCII class name string
 * @return Pointer to matching HSD_ClassInfo, or NULL if not found
 */
HSD_ClassInfo* hsdSearchClassInfo(const char* class_name);

/**
 * @brief Unregisters and purges all classes belonging to a specified library.
 * @param library_name Library grouping name string (defaults to "sysdolphin_base_library" if NULL)
 */
void hsdForgetClassLibrary(const char* library_name);

/**
 * @brief Retrieves or allocates a memory bucket entry for index idx (representing (idx+1)*32 bytes).
 * @param idx Bucket index
 * @return Pointer to HSD_MemoryEntry, or NULL on allocation failure
 */
HSD_MemoryEntry* GetMemoryEntry(s32 idx);

/**
 * @brief Default class allocator method allocating memory for an instance.
 * @param info Pointer to HSD_ClassInfo descriptor
 * @return Pointer to allocated HSD_Class instance
 */
HSD_Class* _hsdClassAlloc(HSD_ClassInfo* info);

/**
 * @brief Default class constructor method.
 * @param arg0 Pointer to HSD_Class instance
 * @return 0 on success
 */
int _hsdClassInit(HSD_Class* arg0);

/**
 * @brief Default class pre-destructor method (no-op).
 * @param cls Pointer to HSD_Class instance
 */
void _hsdClassRelease(HSD_Class* cls);

/**
 * @brief Default class destructor method freeing instance memory.
 * @param cls Pointer to HSD_Class instance
 */
void _hsdClassDestroy(HSD_Class* cls);

/**
 * @brief Default class memory reset callback resetting instance counts.
 * @param info Pointer to HSD_ClassInfo descriptor
 */
void _hsdClassAmnesia(HSD_ClassInfo* info);

/**
 * @brief Updates status flags on a class descriptor.
 * @param class_info Pointer to HSD_ClassInfo
 * @param set Bitmask of flags to set
 * @param reset Bitmask of flags to clear
 */
void class_set_flags(HSD_ClassInfo* class_info, s32 set, s32 reset);

/**
 * @brief Recursively purges a class and all its subclasses from memory.
 * @param class_info Root class descriptor to purge
 */
void ForgetClassLibraryReal(HSD_ClassInfo* class_info);

/**
 * @brief Emits formatted diagnostic statistics for a single class.
 * @param info Pointer to HSD_ClassInfo
 * @param level Indentation level
 */
void DumpClassStat(HSD_ClassInfo* info, s32 level);

/**
 * @brief Emits diagnostic hierarchy statistics for a class and optionally its subclasses.
 * @param info Pointer to HSD_ClassInfo (or NULL to dump from root hsdClass)
 * @param recursive Whether to recursively traverse child subclasses
 * @param level Indentation level
 */
void hsdDumpClassStat(HSD_ClassInfo* info, bool recursive, s32 level);

/**
 * @brief Purges child classes matching a library name.
 * @param library_name Name of library to forget
 * @param class_info Parent class descriptor whose children are searched
 */
void ForgetClassLibraryChild(const char* library_name,
                             HSD_ClassInfo* class_info);

/**
 * @brief Destroys an object instance by executing virtual release and destroy methods.
 * @param object Pointer to object instance to delete
 */
static inline void hsdDelete(void* object)
{
    if (object == NULL) {
        return;
    }

    HSD_CLASS_METHOD(object)->release((HSD_Class*) object);
    HSD_CLASS_METHOD(object)->destroy((HSD_Class*) object);
}

#endif
