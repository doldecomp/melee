/**
 * @file archive.c
 * @brief Archive (DAT file) loading, relocation, and symbol resolution implementation.
 * @details Implements the parser and runtime linker for Sysdolphin .dat archive files.
 * Performs in-place pointer relocation from relative offsets to absolute RAM addresses,
 * root symbol lookups (public symbols), and external reference patch chains.
 * Module prefix: HSD (Sysdolphin)
 */

#include "archive.h"

#include <string.h>

#include <dolphin/os.h>

/**
 * @brief Performs in-place runtime pointer relocation on the archive data payload.
 * @details Iterates through the relocation table (reloc_info). For each entry, reads
 * the 32-bit offset value stored at data + reloc_info[i].offset and adds the base address
 * of archive->data, converting file-relative offsets into absolute GameCube RAM pointers.
 * @param archive Pointer to HSD_Archive whose data payload is to be relocated
 */
static inline void Locate(HSD_Archive* archive)
{
    u32 reloc_idx;
    u32* target_ptr;

    for (reloc_idx = 0; reloc_idx < archive->header.nb_reloc; reloc_idx++) {
        target_ptr = (u32*) (archive->data + archive->reloc_info[reloc_idx].offset);
        *target_ptr += (uintptr_t) archive->data;
    }
}

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
s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, size_t file_size)
{
    u32 offset;

    if (archive == NULL) {
        return -1;
    }

    memset(archive, 0, sizeof(HSD_Archive));
    archive->flags |= 1;
    memcpy(archive, src, sizeof(HSD_ArchiveHeader));

    /* Verify file size matches header to detect truncation or endian mismatch */
    if (archive->header.file_size != file_size) {
        OSReport("HSD_ArchiveParse: byte-order mismatch! Please check data "
                 "format %x %x\n",
                 archive->header.file_size, file_size);
        return -1;
    }

    /* Partition DAT sections sequentially following the 32-byte header */
    offset = sizeof(HSD_ArchiveHeader);
    if (archive->header.data_size != 0) { // Binary data payload
        archive->data = src + sizeof(HSD_ArchiveHeader);
        offset = archive->header.data_size + sizeof(HSD_ArchiveHeader);
    }
    if (archive->header.nb_reloc != 0) { // Pointer relocation table
        archive->reloc_info = (HSD_ArchiveRelocationInfo*) (src + offset);
        offset = offset +
                 archive->header.nb_reloc * sizeof(HSD_ArchiveRelocationInfo);
    }
    if (archive->header.nb_public != 0) { // Public / root symbol table
        archive->public_info = (HSD_ArchivePublicInfo*) (src + offset);
        offset =
            offset + archive->header.nb_public * sizeof(HSD_ArchivePublicInfo);
    }
    if (archive->header.nb_extern != 0) { // External reference table
        archive->extern_info = (HSD_ArchiveExternInfo*) (src + offset);
        offset =
            offset + archive->header.nb_extern * sizeof(HSD_ArchiveExternInfo);
    }
    if (offset < archive->header.file_size) { // String table for symbol names
        archive->symbols = (char*) (src + offset);
    }

    archive->top_ptr = src;

    /* Convert all relative file offsets into absolute RAM pointers */
    Locate(archive);

    return 0;
}

/**
 * @brief Resolves a public root symbol by name and returns its absolute memory address.
 * @details Searches the public_info table for a matching symbol name in the string table
 * and returns data + public_info[i].offset.
 * @param archive Pointer to parsed HSD_Archive
 * @param symbols Null-terminated ASCII name of public root symbol
 * @return Absolute pointer to resolved object in memory, or NULL if not found
 */
void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* symbols)
{
    u32 pub_idx;

    for (pub_idx = 0; pub_idx < archive->header.nb_public; pub_idx++) {
        int comparison =
            strcmp(archive->symbols + archive->public_info[pub_idx].symbol, symbols);

        if (comparison == 0) {
            // If both strings are equal, we've found the node
            return archive->data + archive->public_info[pub_idx].offset;
        }
    }

    return NULL;
}

/**
 * @brief Retrieves the name of an external unresolved symbol by table index.
 * @param archive Pointer to parsed HSD_Archive
 * @param index Index into extern_info table
 * @return Pointer to symbol name string, or NULL if index is out of bounds
 */
char* HSD_ArchiveGetExtern(HSD_Archive* archive, int index)
{
    if (index < 0 || archive->header.nb_extern <= (u32) index) {
        return NULL;
    }

    return archive->symbols + archive->extern_info[index].symbol;
}

/**
 * @brief Resolves an external symbol reference and patches its linked address chain.
 * @details Locates the external reference by symbol name and traverses the linked list
 * of pointer slots within the data payload, overwriting each slot with the resolved address.
 * @param archive Pointer to parsed HSD_Archive
 * @param symbols Null-terminated name of the external symbol to resolve
 * @param addr Resolved target address to link into the archive data
 */
void HSD_ArchiveLocateExtern(HSD_Archive* archive, const char* symbols,
                             void* addr)
{
    u32 offset = -1U;
    u32 ext_idx;

    /* Find matching external symbol in the extern_info table */
    for (ext_idx = 0; ext_idx < archive->header.nb_extern; ext_idx++) {
        int comparison =
            strcmp(symbols, archive->symbols + archive->extern_info[ext_idx].symbol);

        if (comparison == 0) {
            offset = archive->extern_info[ext_idx].offset;
            break;
        }
    }

    if (offset == -1U) {
        return;
    }

    /* Traverse the linked reference chain in the data payload, patching each slot */
    while (offset != -1U && offset < archive->header.data_size) {
        u32* slot = (u32*) (archive->data + offset);
        u32 next_offset = *slot;
        *slot = (uintptr_t) addr;
        offset = next_offset;
    }
}
