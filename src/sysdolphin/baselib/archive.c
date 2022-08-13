#include <string.h>

#include <sysdolphin/baselib/archive.h>

inline void Locate(HSD_Archive* archive)
{
    int i;
    u32* ptr;

    for (i = 0; i < archive->header.nb_reloc; i++) {
        ptr = (u32*)(archive->data + archive->reloc_info[i].offset);
        *ptr += (u32)archive->data;
    }
}

s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, u32 file_size)
{
    u32 offset;
    
    if (archive == NULL) {
        return -1;
    }

    memset(archive, 0, sizeof(HSD_Archive));
    archive->flags |= 1;
    memcpy(archive, src, sizeof(HSD_ArchiveHeader));

    if (archive->header.file_size != file_size) {
        OSReport("HSD_ArchiveParse: byte-order mismatch! Please check data format %x %x\n", archive->header.file_size, file_size);
        return -1;
    }

    offset = sizeof(HSD_ArchiveHeader);
    if (archive->header.data_size != 0) { // Body Size
        archive->data = src + 0x20;
        offset = archive->header.data_size + 0x20;
    }
    if (archive->header.nb_reloc != 0) { // Relocation Size
        archive->reloc_info = (HSD_ArchiveRelocationInfo*)((s32)src + offset);
        offset = offset + archive->header.nb_reloc * 4;
    }
    if (archive->header.nb_public != 0) { // Root Size
        archive->public_info = (HSD_ArchivePublicInfo*)((s32)src + offset);
        offset = offset + archive->header.nb_public * 8;
    }
    if (archive->header.nb_extern != 0) { // XRef Size
        archive->extern_info = (HSD_ArchiveExternInfo*)((s32)src + offset);
        offset = offset + archive->header.nb_extern * 8;
    }
    if (offset < archive->header.file_size) { // File Size
        archive->symbols = (char*)((s32)src + offset);
    }

    archive->top_ptr = (void*)src;
    Locate(archive);

    return 0;
}

void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, char* symbols) {
    int i;
    
    for (i = 0; i < archive->header.nb_public; i++) {
        if (strcmp(archive->symbols + archive->public_info[i].symbol, symbols) == 0) // If both strings are equal, we've found the node
            return archive->data + archive->public_info[i].offset;;
    }

    return NULL;
}

char* HSD_ArchiveGetExtern(HSD_Archive* archive, s32 offset)
{
    if (offset < 0 || archive->header.nb_extern <= offset) {
        return NULL;
    }
    return archive->symbols + archive->extern_info[offset].symbol;
}

void HSD_ArchiveLocateExtern(HSD_Archive* archive, char* symbols, void* addr)
{
    u32 next;
    u32 offset;
    int i;
    
    offset = -1;
    for (i = 0; i < archive->header.nb_extern; i++){
        if (strcmp(symbols, archive->symbols + archive->extern_info[i].symbol) == 0) {
            offset = archive->extern_info[i].offset;
            break;
        }
    }

    if (offset == -1){
        return;
    }

    while (offset != -1 && offset < archive->header.data_size) {
        next = *(u32*)((u32)archive->data + offset);
        *(u32*)((u32)archive->data + offset) = (u32)addr;
        offset = next;
    }
}
