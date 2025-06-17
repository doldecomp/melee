#ifndef THP_H
#define THP_H

#include <dolphin/os.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 THPSample;
typedef s16 THPCoeff;
typedef f32 THPQuantTab[64];

typedef struct _THPHuffmanTab {
    u8 quick[32];
    u8 increment[32];
    u8* Vij;
    s32 maxCode[18];
    s32 valPtr[18];
    u8 Vij1;
    u8* bits;
    u32 pad3;
    u32* codetab;
    u32 pad2[2];
} THPHuffmanTab;

typedef struct _THPComponent {
    THPCoeff predDC;
    u8 pad;
    u8 quantizationTableSelector;
    u8 DCTableSelector;
    u8 ACTableSelector;
    u32 pad2[9];
} THPComponent;

typedef struct _THPFileInfo {
    u8* file;
    u32 currByte;
    u32 cnt;
    u8 pad[0x78 - 12];
    u8 validHuffmanTabs;
    u8 x78;
    u8 pad3[0xb];
    THPHuffmanTab huffmanTabs[4];
    THPQuantTab quantTabs[3];
    u16 xPixelSize;
    u16 yPixelSize;
    u16 MCUsPerRow;
    u16 decompressedY;
    u8 RST;
    u16 nMCU;
    u16 currMCU;
    u8* dLC[3];
    u32 pad2[(0x83d - 0x756) / 4];
    THPComponent components[3];
} THPFileInfo;

static u8 __THPSetupBuffers(THPFileInfo*);
static u8 __THPReadFrameHeader(void);
static u8 __THPReadScaneHeader(THPFileInfo*);
static u8 __THPReadQuantizationTable(THPFileInfo*);
static u8 __THPReadHuffmanTableSpecification(THPFileInfo*);
static u8 __THPReadScaneHeader(THPFileInfo*);
static u8 __THPHuffGenerateSizeTable(THPFileInfo*, u8, int);
static u8 __THPHuffGenerateCodeTable(THPFileInfo*, u8 tab_index);
static int __THPHuffGenerateDecoderTables(THPFileInfo*, u8 tab_index);
static u8 __THPRestartDefinition(THPFileInfo*);
static void __THPPrepBitStream(THPFileInfo*);
static void __THPDecompressYUV(void*, void*, void*);
static void __THPGQRRestore(void);
static void __THPDecompressiMCURow512x448(void);
static void __THPDecompressiMCURow640x480(void);
static void __THPDecompressiMCURowNxN(void);
static void __THPInverseDCTNoYPos(THPCoeff*, u32);
static void __THPHuffDecodeDCTCompY(THPFileInfo*, THPCoeff*);
static void __THPHuffDecodeDCTCompU(THPFileInfo*, THPCoeff*);
static void __THPHuffDecodeDCTCompV(THPFileInfo*, THPCoeff*);

s32 THPVideoDecode(void* file, void* tileY, void* tileU, void* tileV, void* work);

BOOL THPInit(void);

#ifdef __cplusplus
}
#endif

#endif // THP_H
