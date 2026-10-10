/** @file Archive bytes, relocation slots, and public/extern tables. */
#ifndef DAT_ARCHIVE_DATA_H
#define DAT_ARCHIVE_DATA_H
#include <stddef.h>
#include <stdint.h>

#include <dat/memory.h>
typedef struct DatSymbol {
    uint32_t offset;
    const char* name;
} DatSymbol;
typedef struct DatArchiveData {
    uint8_t* data;
    uint32_t size;
    uint32_t* relocs;
    uint32_t nrelocs;
    DatSymbol *publics, *externs;
    uint32_t npublics, nexterns;
    const char* names;
    uint32_t names_size;

    Bits reloc, extern_slot, public, target;
} DatArchiveData;
DatArchiveData* dat_archive_open(const void* bytes, size_t size,
                                 const char** error);
int dat_archive_open_packed(const void* bytes, size_t size,
                            DatArchiveData** out, size_t* offsets, int max,
                            const char** error);
void dat_archive_close(DatArchiveData* archive);
const DatSymbol* dat_archive_public(const DatArchiveData* archive,
                                    const char* name);
#endif
