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
    /* 0x00 */ u8 quick[32];
    /* 0x20 */ u8 increment[32];
    /* 0x40 */ u8* Vij;
    /* 0x44 */ s32 maxCode[18];
    /* 0x8C */ s32 valPtr[18];
    /* 0xD4 */ u8 Vij1;
    /* 0xD5 */ u8 padD5[0xD8 - 0xD5];
    /* 0xD8 */ u8* bits;
    /* 0xDC */ s8* sizeTab;
    /* 0xE0 */ u32* codeTab;
    /* 0xE4 */ u32 numCodes;
    /* 0xE8 */ u16 numVij;
    /* 0xEA */ u16 padEA;
} THPHuffmanTab; // size = 0xEC

typedef struct _THPComponent {
    /* 0x00 */ u8 componentID;
    /* 0x01 */ u8 samplingH;
    /* 0x02 */ u8 samplingV;
    /* 0x03 */ u8 quantizationTableSelector;
    /* 0x04 */ u8 DCTableSelector;
    /* 0x05 */ u8 ACTableSelector;
    /* 0x06 */ THPCoeff predDC;
    /* 0x08 */ u32 x08;
    /* 0x0C */ u32 x0C;
    /* 0x10 */ u32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ s32 x28;
} THPComponent; // size = 0x2C

/**
 * The decode work area, sized by ::THPDec_8032FD40 and filled in by
 * ::THPVideoDecode: the bit stream being read, the tables read out of the
 * frame's headers, and the per-component decode state.
 */
typedef struct _THPFileInfo {
    /* 0x000 */ u8* file;
    /* 0x004 */ u32 currByte;
    /* 0x008 */ u32 cnt;
    /* 0x00C */ u8* dataStart;
    /* 0x010 */ THPCoeff* mcuBuffer[16];
    /* 0x050 */ u16 xSize;
    /* 0x052 */ u16 ySize;
    /* 0x054 */ u8 pad54[0x6C - 0x54];
    /* 0x06C */ u8* scanStart;
    /* 0x070 */ u16 xPixelSize;
    /* 0x072 */ u16 yPixelSize;
    /* 0x074 */ u16 x74;
    /* 0x076 */ u16 decompressedY;
    /* 0x078 */ u8 validHuffmanTabs;
    /* 0x079 */ u8 validQuantTabs;
    /* 0x07A */ u8 samplingHMax;
    /* 0x07B */ u8 samplingVMax;
    /* 0x07C */ u8 nComponents;
    /* 0x07D */ u8 x7D;
    /* 0x07E */ u8 pad7E[0x88 - 0x7E];
    /* 0x088 */ THPHuffmanTab huffmanTabs[4];
    /* 0x438 */ THPQuantTab quantTabs[3];
    /* 0x738 */ u8 pad738[0x838 - 0x738];
    /* 0x838 */ THPComponent components[3];
    /* 0x8BC */ u8 x8BC[0x8CC - 0x8BC];
    /* 0x8CC */ u16 MCUsPerRow;
    /* 0x8CE */ u16 x8CE;
    /* 0x8D0 */ u16 x8D0;
    /* 0x8D2 */ u16 x8D2;
    /* 0x8D4 */ u16 x8D4;
    /* 0x8D6 */ u8 pad8D6[0x8E8 - 0x8D6];
    /* 0x8E8 */ u16 x8E8;
    /* 0x8EA */ u16 x8EA;
    /* 0x8EC */ u16 x8EC;
    /* 0x8EE */ u16 x8EE;
    /* 0x8F0 */ u8* tileY;
    /* 0x8F4 */ u8* tileU;
    /* 0x8F8 */ u8* tileV;
    /* 0x8FC */ u16 nMCU;
    /* 0x8FE */ u16 currMCU;
    /* 0x900 */ u8 RST;
    /* 0x901 */ u8 pad901[0x904 - 0x901];
    /* 0x904 */ u8* scratch;
} THPFileInfo; // size = 0x908

typedef struct {
    s32 val0;
    u16 val1;
    u16 _pad;
    u8 val2;
} THPDec_8032FD40_Data;

static u8 __THPReadFrameHeader(THPFileInfo*);
static u8 __THPReadScaneHeader(THPFileInfo*);
static u8 __THPReadQuantizationTable(THPFileInfo*);
static u8 __THPReadHuffmanTableSpecification(THPFileInfo*);
static u8 __THPReadScaneHeader(THPFileInfo*);
static u8 __THPHuffGenerateSizeTable(THPFileInfo*, u8, int);
static u8 __THPHuffGenerateCodeTable(THPFileInfo*, u8 tab_index);
static int __THPHuffGenerateDecoderTables(THPFileInfo*, u8 tab_index);
static u8 __THPRestartDefinition(THPFileInfo*);
static void __THPPrepBitStream(THPFileInfo*);
static void __THPDecompressiMCURow640x480(THPFileInfo*);
static void __THPDecompressiMCURowNxN(THPFileInfo*, u32);
static void __THPInverseDCTNoYPos(THPCoeff*, u32);
static void __THPHuffDecodeDCTCompY(THPFileInfo*, THPCoeff*);
static void __THPHuffDecodeDCTCompU(THPFileInfo*, THPCoeff*);
static void __THPHuffDecodeDCTCompV(THPFileInfo*, THPCoeff*);

THPFileInfo* THPVideoDecode(void* header, void* status_out, THPFileInfo* work,
                            void* data, THPDec_8032FD40_Data* desc);
s32 THPDec_803302EC(u8** data);
s32 THPDec_8032FD40(THPDec_8032FD40_Data* arg0, u16 arg1);
s32 THPDec_8032F8D4(u8* data, THPDec_8032FD40_Data* out);
u8 THPDec_80330158(THPFileInfo* info);
void THPDec_80331340(THPFileInfo*, void*, void*, void*);
void THPDec_803313D0(THPFileInfo*, void*, void*, void*, u32);
void THPDec_803300E0(THPFileInfo* info);
void THPInit(void);

#ifdef __cplusplus
}
#endif

#endif // THP_H
