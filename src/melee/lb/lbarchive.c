#include <melee/lb/lbarchive.h>

extern char lbl_803BA588[]; //"HSD_ArchiveParse error!\n"
extern char lbl_803BA5A4[]; //"lbarchive.c"

extern char lbl_804D37C0[2]; //"0"

void lbArchive_InitializeDAT(HSD_Archive* archive, u8* data, u32 length)
{
    char* symbol;
    s32 i = 0;

    if (HSD_ArchiveParse(archive, data, length) == -1) {
        OSReport(lbl_803BA588);
        __assert(lbl_803BA5A4, 73, lbl_804D37C0);
    }
    while (1){
        symbol = HSD_ArchiveGetExtern(archive, i++);
        if (symbol != NULL)
            HSD_ArchiveLocateExtern(archive, symbol, NULL);
        if (symbol == NULL)
            return;
    }
}
