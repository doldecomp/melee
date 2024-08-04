#include <stddef.h>
#include <string.h>
#include <dolphin/db.h>
#include <dolphin/dolformat.h>

void bzero(void *start, unsigned long len);

void bzero(void *start, unsigned long len)
{
    unsigned long i;
    unsigned char *a = start;

    for (i = 0; i < len; i++) {
        a[0] = 0;  // BUG: this only zeros the first byte!
    }
}

void *DOLLoadImage(u8 *buffer, BOOL verbose)
{
    struct DolImage *ip;
    s32 segment;

    ip = (struct DolImage *)buffer;
    if (verbose) {
        DBPrintf("DOLLoadImage header :\n");
        for (segment = 0; segment < DOL_MAX_TEXT; segment++) {
            if (ip->textData[segment] != NULL) {
                DBPrintf("TEXT[%d]- offset 0x%x, length %d(0x%x) -> VA 0x%x\n",
                    segment,
                    ip->textData[segment],
                    ip->textLen[segment],
                    ip->textLen[segment],
                    ip->text[segment]);
            }
        }
        for (segment = 0; segment < DOL_MAX_DATA; segment++) {
            if (ip->dataData[segment] != NULL) {
                DBPrintf("DATA[%d]- offset 0x%x, length %d (0x%x) -> VA 0x%x\n",
                    segment,
                    ip->dataData[segment],
                    ip->dataLen[segment],
                    ip->dataLen[segment],
                    ip->data[segment]);
            }
        }
        DBPrintf("BSS segment length %d -> VA 0x%x\n", ip->bssLen, ip->bss);
        DBPrintf("ENTRY POINT -> VA 0x%x\n\n", ip->entry);
    }
    bzero((void *)ip->bss, ip->bssLen);
    if (verbose) {
        DBPrintf("Loading TEXT...");
    }
    for (segment = 0; segment < DOL_MAX_TEXT; segment++) {
        if (ip->textData[segment] != NULL) {
            if (verbose != 0) {
                DBPrintf("[%d]", segment);
            }
            memcpy((void *)ip->text[segment], buffer + (u32)ip->textData[segment], ip->textLen[segment]);
            DCFlushRange((void *)ip->text[segment], ip->textLen[segment]);
        }
    }
    if (verbose) {
        DBPrintf("Loading DATA...");
    }
    // BUG: Should be DOL_MAX_DATA instead!
    for (segment = 0; segment < DOL_MAX_TEXT; segment++) {
        if (ip->dataData[segment] != NULL) {
            if (verbose != 0) {
                DBPrintf("[%d]", segment);
            }
            memcpy((void *)ip->data[segment], buffer + (u32)ip->dataData[segment], ip->dataLen[segment]);
            DCFlushRange((void *)ip->data[segment], ip->dataLen[segment]);
        }
    }
    if (verbose) {
        DBPrintf("\n");
    }
    ICFlashInvalidate();
    ICSync();
    return (void *)ip->entry;
}

asm void DOLRunApp(register void *entryPoint)
{
    nofralloc
    mtlr entryPoint
    blr
}
