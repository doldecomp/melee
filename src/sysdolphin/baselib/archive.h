#ifndef _archive_h_
#define _archive_h_

#include <global.h>

#include <dolphin/types.h>

#define HSD_ARCHIVE_DONT_FREE 1

typedef struct _HSD_ArchiveHeader {
    u32 file_size; /* 0x00 */
    u32 data_size; /* 0x04 */
    u32 nb_reloc; /* 0x08 */
    u32 nb_public; /* 0x0C */
    u32 nb_extern; /* 0x10 */
    u8 version[4]; /* 0x14 */
    u32 pad[2]; /* 0x18 */
} HSD_ArchiveHeader;

typedef struct _HSD_ArchiveRelocationInfo {
    u32 offset;
} HSD_ArchiveRelocationInfo;

typedef struct _HSD_ArchivePublicInfo {
    u32 offset; /* 0x00 */
    u32 symbol; /* 0x04 */
} HSD_ArchivePublicInfo;

typedef struct _HSD_ArchiveExternInfo {
    u32 offset; /* 0x00 */
    u32 symbol; /* 0x04 */
} HSD_ArchiveExternInfo;

typedef struct _HSD_Archive {
    struct _HSD_ArchiveHeader header; /* 0x00 */
    u8* data; /* 0x20 */
    struct _HSD_ArchiveRelocationInfo* reloc_info; /* 0x24 */
    struct _HSD_ArchivePublicInfo* public_info; /* 0x28 */
    struct _HSD_ArchiveExternInfo* extern_info; /* 0x2C */
    char* symbols; /* 0x30 */
    struct _HSD_Archive* next; /* 0x34 */
    char* name; /* 0x38 */
    u32 flags; /* 0x3C */
    void* top_ptr; /* 0x40 */
} HSD_Archive;

s32 HSD_ArchiveParse(HSD_Archive*, u8*, u32);
void* HSD_ArchiveGetPublicAddress(HSD_Archive*, char*);
char* HSD_ArchiveGetExtern(HSD_Archive*, s32);
void HSD_ArchiveLocateExtern(HSD_Archive*, char*, void*);

#endif
