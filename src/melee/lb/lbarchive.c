#include "lbarchive.h"

#include "lbfile.h"
#include "lbheap.h"

#include <stdarg.h>
#include <dolphin/os.h>
#include <baselib/archive.h>
#include <baselib/debug.h>

#pragma push
#pragma dont_inline on
void lbArchive_InitializeDAT(HSD_Archive* archive, u8* data, u32 length)
{
    char* symbol;
    int i = 0;

    if (HSD_ArchiveParse(archive, data, length) == -1) {
        OSReport("HSD_ArchiveParse error!\n");
        HSD_ASSERT(73, 0);
    }

    while (true) {
        symbol = HSD_ArchiveGetExtern(archive, i++);
        if (symbol != NULL) {
            HSD_ArchiveLocateExtern(archive, symbol, NULL);
        }
        if (symbol == NULL) {
            return;
        }
    }
}
#pragma pop

void lbArchive_LoadSections(HSD_Archive* archive, void** file, ...)
{
    char* symbols;
    va_list sections;

    va_start(sections, file);
    for (; file != NULL; file = va_arg(sections, void**)) {
        symbols = va_arg(sections, char*);
        *file = NULL;
        *file = HSD_ArchiveGetPublicAddress(archive, symbols);
        if (*file == NULL) {
            OSReport("Cannot find symbol %s.\n", symbols);
        }
    }
    va_end(sections);
}

HSD_Archive* lbArchive_LoadArchive(char* filename)
{
    s32 length;
    u8* data;
    HSD_Archive* archive;

    data = lbHeap_80015BD0(0, lbFile_800163D8(filename) + 0x1F & 0xFFFFFFE0);
    archive = lbHeap_80015BD0(0, sizeof(HSD_Archive));
    lbFile_8001668C(filename, data, &length);
    lbArchive_InitializeDAT(archive, data, (u32) length);
    return archive;
}

HSD_Archive* lbArchive_80016C64(char* filename, void** file, ...)
{
    va_list sections;
    char* symbols;
    HSD_Archive* archive;

    va_start(sections, file);
    archive = lbArchive_LoadArchive(filename);
    for (; file != NULL; file = va_arg(sections, void**)) {
        symbols = va_arg(sections, char*);
        *file = NULL;
        *file = HSD_ArchiveGetPublicAddress(archive, symbols);
        if (*file == NULL) {
            OSReport("Cannot find symbol %s.\n", symbols);
            HSD_ASSERT(112, 0);
        }
    }
    va_end(sections);
    return archive;
}
