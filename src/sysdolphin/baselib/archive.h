/**
 * @file archive.h
 * @brief Archive (DAT file) loading, relocation, and symbol resolution declarations.
 * @details Manages loading and runtime pointer relocation of Sysdolphin .dat archive files,
 * which contain 3D models, textures, animations, collision data, and stage geometry.
 * Implements public symbol lookup (root nodes) and external reference linking.
 * Module prefix: HSD (Sysdolphin)
 */

#ifndef _archive_h_
#define _archive_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <dat_macros.h> // IWYU pragma: keep

/// Flag indicating that this archive's memory should not be freed on release
#define HSD_ARCHIVE_DONT_FREE 1

/**
 * @brief 32-byte header stored at the beginning of every Melee DAT archive file.
 */
struct HSD_ArchiveHeader {
    u32 file_size;  ///< Total byte size of the archive file (offset 0x00)
    u32 data_size;  ///< Byte size of the binary data payload section (offset 0x04)
    u32 nb_reloc;   ///< Number of internal pointer relocation entries (offset 0x08)
    u32 nb_public;  ///< Number of public root symbol entries (offset 0x0C)
    u32 nb_extern;  ///< Number of external unresolved symbol references (offset 0x10)
    u8 version[4];  ///< Archive format version string (offset 0x14)
    u32 pad[2];     ///< Alignment padding bytes (offset 0x18)
};
ASSERT_SIZE(struct HSD_ArchiveHeader, 0x20);

/**
 * @brief Relocation entry specifying the offset of an internal pointer to be relocated.
 */
struct HSD_ArchiveRelocationInfo {
    u32 offset;     ///< Byte offset within data payload containing a 32-bit pointer (offset 0x00)
};

/**
 * @brief Public / exported root symbol descriptor within an archive.
 */
struct HSD_ArchivePublicInfo {
    u32 offset;     ///< Byte offset within data payload of the exported object (offset 0x00)
    u32 symbol;     ///< Byte offset within symbols string table of the root name (offset 0x04)
};

/**
 * @brief External reference descriptor linking symbols across multiple archives.
 */
struct HSD_ArchiveExternInfo {
    u32 offset;     ///< Byte offset within data payload of the first reference in chain (offset 0x00)
    u32 symbol;     ///< Byte offset within symbols string table of the extern symbol name (offset 0x04)
};

/**
 * @brief Runtime instance structure representing a parsed DAT archive.
 */
struct HSD_Archive {
    HSD_ArchiveHeader header;              ///< Copy of the 32-byte DAT header (offset 0x00)
    u8* data;                              ///< Pointer to binary data payload (offset 0x20)
    HSD_ArchiveRelocationInfo* reloc_info; ///< Pointer to relocation info table (offset 0x24)
    HSD_ArchivePublicInfo* public_info;    ///< Pointer to public roots table (offset 0x28)
    HSD_ArchiveExternInfo* extern_info;    ///< Pointer to external references table (offset 0x2C)
    char* symbols;                         ///< Pointer to null-terminated symbols string table (offset 0x30)
    HSD_Archive* next;                     ///< Next archive in global loaded archive list (offset 0x34)
    char* name;                            ///< Archive identifier / filename string (offset 0x38)
    u32 flags;                             ///< Archive state flags (e.g. HSD_ARCHIVE_DONT_FREE) (offset 0x3C)
    void* top_ptr;                         ///< Base memory allocation pointer for entire archive (offset 0x40)
};
ASSERT_SIZE(struct HSD_Archive, 0x44);

/**
 * @brief Parses raw DAT archive bytes, sets up section pointers, and relocates internal pointers.
 * @details Validates file size and byte-order header, partitions the buffer into data,
 * reloc_info, public_info, extern_info, and symbols sections, and resolves all internal
 * relative offsets into absolute memory pointers via Locate().
 * @param archive Pointer to HSD_Archive structure to populate
 * @param src Pointer to raw DAT file bytes loaded in memory
 * @param file_size Expected byte size of the loaded file
 * @return 0 on success, -1 on size/endian mismatch or error
 */
s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, size_t file_size);

/**
 * @brief Resolves a public root symbol by name and returns its absolute memory address.
 * @details Searches the public_info table for a matching symbol name in the string table
 * and returns data + public_info[i].offset.
 * @param archive Pointer to parsed HSD_Archive
 * @param symbols Null-terminated ASCII name of public root symbol
 * @return Absolute pointer to resolved object in memory, or NULL if not found
 */
void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* symbols);

/// The public symbol @p name of @p archive, as a pointer to @p type.
#ifdef DAT_ROOTS_ENABLED
// Also record the type the symbol is loaded as
#define HSD_ArchiveGetPublicAs(type, archive, name)                           \
    ({                                                                        \
        DAT_ROOT((type**) 0, name)                                            \
        (type*) HSD_ArchiveGetPublicAddress((archive), (name));               \
    })
#else
#define HSD_ArchiveGetPublicAs(type, archive, name)                           \
    ((type*) HSD_ArchiveGetPublicAddress((archive), (name)))
#endif

/**
 * @brief Retrieves the name of an external unresolved symbol by table index.
 * @param archive Pointer to parsed HSD_Archive
 * @param index Index into extern_info table
 * @return Pointer to symbol name string, or NULL if index is out of bounds
 */
char* HSD_ArchiveGetExtern(HSD_Archive* archive, int index);

/**
 * @brief Resolves an external symbol reference and patches its linked address chain.
 * @details Locates the external reference by symbol name and traverses the linked list
 * of pointer slots within the data payload, overwriting each slot with the resolved address.
 * @param archive Pointer to parsed HSD_Archive
 * @param symbols Null-terminated name of the external symbol to resolve
 * @param addr Resolved target address to link into the archive data
 */
void HSD_ArchiveLocateExtern(HSD_Archive* archive, const char* symbols, void* addr);

#endif
