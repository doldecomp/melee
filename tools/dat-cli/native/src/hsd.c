/** @file TARGET_PC adapter for the game's typed archive loader. */
#include "melee_dat.h"
#include <dat/reader-internal.h>
#include <sysdolphin/baselib/archive.h>

/* Only parsed wrappers have top_ptr. Plain relocation views leave it null. */
static HSD_ArchiveStorage* storage_of(HSD_Archive* archive)
{
    return archive != NULL && archive->top_ptr != NULL
               ? (HSD_ArchiveStorage*) archive
               : NULL;
}

static uint32_t be32(const u8* p)
{
    return (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
           (uint32_t) p[2] << 8 | p[3];
}

s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, size_t size)
{
    if (archive == NULL) {
        return -1;
    }
    HSD_ArchiveStorage* storage = (HSD_ArchiveStorage*) archive;
    memset(storage, 0, sizeof(*storage));
    DatArchive* native = dat_open(&melee_dat_schema, src, size, NULL);
    if (native == NULL) {
        return -1;
    }
    DatArchiveData* raw = native->archive;
    storage->native_data = native;
    archive->header.file_size = be32(src);
    archive->header.data_size = raw->size;
    archive->header.nb_reloc = raw->nrelocs;
    archive->header.nb_public = raw->npublics;
    archive->header.nb_extern = raw->nexterns;
    memcpy(archive->header.version, src + 0x14, 4);
    archive->header.pad[0] = be32(src + 0x18);
    archive->header.pad[1] = be32(src + 0x1C);
    /* The game frees its input allocation through this address. */
    archive->data = src + sizeof(HSD_ArchiveHeader);
    archive->top_ptr = src;
    archive->flags = HSD_ARCHIVE_DONT_FREE;
    archive->symbols = (char*) raw->names;
    archive->reloc_info = calloc(raw->nrelocs, sizeof(*archive->reloc_info));
    archive->public_info =
        calloc(raw->npublics, sizeof(*archive->public_info));
    archive->extern_info =
        calloc(raw->nexterns, sizeof(*archive->extern_info));
    if ((raw->nrelocs && !archive->reloc_info) ||
        (raw->npublics && !archive->public_info) ||
        (raw->nexterns && !archive->extern_info))
    {
        abort();
    }
    for (uint32_t i = 0; i < raw->nrelocs; i++) {
        archive->reloc_info[i].offset = raw->relocs[i];
    }
    for (uint32_t i = 0; i < raw->npublics; i++) {
        archive->public_info[i].offset = raw->publics[i].offset;
        archive->public_info[i].symbol = raw->publics[i].name - raw->names;
    }
    for (uint32_t i = 0; i < raw->nexterns; i++) {
        archive->extern_info[i].offset = raw->externs[i].offset;
        archive->extern_info[i].symbol = raw->externs[i].name - raw->names;
    }
    return 0;
}

void HSD_ArchiveReleaseNative(HSD_Archive* archive)
{
    HSD_ArchiveStorage* storage = storage_of(archive);
    if (storage == NULL || storage->native_data == NULL) {
        return;
    }
    dat_close(storage->native_data);
    storage->native_data = NULL;
    archive->top_ptr = NULL;
    free(archive->reloc_info);
    free(archive->public_info);
    free(archive->extern_info);
    archive->reloc_info = NULL;
    archive->public_info = NULL;
    archive->extern_info = NULL;
    archive->symbols = NULL;
}

void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* name)
{
    HSD_ArchiveStorage* storage = storage_of(archive);
    if (storage == NULL || storage->native_data == NULL) {
        return NULL;
    }
    const DatArchiveData* raw = storage->native_data->archive;
    const DatSymbol* symbol = dat_archive_public(raw, name);
    return symbol ? raw->data + symbol->offset : NULL;
}

void* HSD_ArchiveGetPublicTyped(HSD_Archive* archive, const char* name,
                                const char* type)
{
    HSD_ArchiveStorage* storage = storage_of(archive);
    if (storage == NULL || storage->native_data == NULL) {
        return NULL;
    }
    int32_t index = melee_dat_type(type);
    return index == DAT_NONE ? NULL
                             : dat_public(storage->native_data, name, index);
}

char* HSD_ArchiveGetExtern(HSD_Archive* archive, int index)
{
    HSD_ArchiveStorage* storage = storage_of(archive);
    if (storage == NULL || storage->native_data == NULL) {
        return NULL;
    }
    const DatArchiveData* raw = storage->native_data->archive;
    return index < 0 || (uint32_t) index >= raw->nexterns
               ? NULL
               : (char*) raw->externs[index].name;
}

void HSD_ArchiveLocateExtern(HSD_Archive* archive, const char* name,
                             void* address)
{
    HSD_ArchiveStorage* storage = storage_of(archive);
    if (storage != NULL && storage->native_data != NULL) {
        dat_link_extern(storage->native_data, name, address);
    }
}
