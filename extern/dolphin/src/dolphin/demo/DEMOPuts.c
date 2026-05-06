#include <dolphin.h>
#include <dolphin/gx.h>
#include <dolphin/demo.h>
#include <dolphin/mtx.h>

#include "__demo.h"

extern unsigned long DEMOFontBitmap[]; // size: 0x0, address: 0x0

// .bss
static struct _GXTexObj fontTexObj; // size: 0x20, address: 0x0

// .sbss
static long fontShift; // size: 0x4, address: 0x0
static struct OSFontHeader * FontData; // size: 0x4, address: 0x4
static void * LastSheet; // size: 0x4, address: 0x8
static s16 FontSize; // size: 0x2, address: 0xC
static s16 FontSpace; // size: 0x2, address: 0xE

// functions
static void DrawFontChar(int x, int y, int z, int xChar, int yChar);
static void LoadSheet(void * image, enum _GXTexMapID texMapID);

void DEMOSetFontType(DMFontType attr) {
    switch(attr) {
        case DM_FT_RVS:
            GXSetBlendMode(2, 0, 0, 0xC);
            break;
        case DM_FT_XLU:
            GXSetBlendMode(1, 1, 1, 0);
            break;
        case DM_FT_OPQ:
        default:
            GXSetBlendMode(1, 1, 0, 0);
            break;
    }
}

void DEMOLoadFont(enum _GXTexMapID texMap, enum _GXTexMtx texMtx, DMTexFlt texFlt) {
    float fontTMtx[3][4];
    unsigned short width;
    unsigned short height;

    width = 64;
    height = 0x1800 / width;
    GXInitTexObj(&fontTexObj,(void*)DEMOFontBitmap, width, (u16)height, 0, 0, 0, 0);
    fontShift = 1;
    if (texFlt == 0) {
        GXInitTexObjLOD(&fontTexObj, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
        fontShift = 0;
    }
    GXLoadTexObj(&fontTexObj, texMap);
    MTXScale(fontTMtx, 1.0f / (width - !fontShift), 1.0f / ((u16)height - !fontShift), 1.0f);
    GXLoadTexMtxImm(fontTMtx, texMtx, 1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(0, 1, 4, texMtx);
}

void DEMOSetupScrnSpc(long width, long height, float depth) {
    float pMtx[4][4];
    float mMtx[3][4];

    MTXOrtho(pMtx, 0.0f, height, 0.0f, width, 0.0f, -depth);
    GXSetProjection(pMtx, 1);
    MTXIdentity(mMtx);
    GXLoadPosMtxImm(mMtx, 0);
    GXSetCurrentMtx(0);
}

void DEMOInitCaption(long font_type, long width, long height) {
    DEMOSetupScrnSpc(width, height, 100.0f);
    GXSetZMode(1, 7, 1);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetTevOp(0, 3);
    GXSetTevOrder(0, 0, 0, 0xFF);
    DEMOLoadFont(0, 0x1E, 0);
    DEMOSetFontType(font_type);
}

void DEMOPuts(s16 x, s16 y, s16 z, char * string) {
    char * str;
    long s;
    long t;
    long c;
    long w;
    long len;
    long i;

    str = string;
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 3, 1);

    // calc len
    len = 0;
    while(1) {
        c = *(str++);
        if ((c >= 0x20) && (c <= 0x7F)) {
            len++;
            continue;
        }

        if (len > 0) {
            GXBegin(0x80, 0, len * 4);
            for(i = 0; i < len; i++) {
                w = string[i] - 0x20;
                s = fontShift + ((w % 8) * 0x10);
                t = fontShift + ((w / 8) * 0x10);
                GXPosition3s16(x + (i * 8), y, z);
                GXTexCoord2s16(s, t);
                GXPosition3s16(x + (i * 8) + 8, y, z);
                GXTexCoord2s16(s + 0x10, t);
                GXPosition3s16(x + (i * 8) + 8, y + 8, z);
                GXTexCoord2s16(s + 0x10, t + 0x10);
                GXPosition3s16(x + (i * 8), y + 8, z);
                GXTexCoord2s16(s, t + 0x10);
            }
            GXEnd();
            len = 0;
        }

        string = str;
        if (c == 0xA) {
            y += 0x8;
        } else {
            break;
        }
    }
}

void DEMOPrintf(s16 x, s16 y, s16 z, char * fmt, ...) {
    va_list vlist;
    char buf[256];

    va_start(vlist, fmt);
    vsprintf(buf, fmt, vlist);
    DEMOPuts(x, y, z, buf);
    va_end(vlist);
}

struct OSFontHeader * DEMOInitROMFont() {
    if (OSGetFontEncode() == 1) {
        FontData = OSAllocFromHeap(__OSCurrHeap, 0x120F00);
    } else {
        FontData = OSAllocFromHeap(__OSCurrHeap, 0x20120);
    }
    if (!FontData) {
        OSPanic(__FILE__, 0x19D, "Ins. memory to load ROM font.");
    }
    if (OSInitFont(FontData) == 0) {
        OSPanic(__FILE__, 0x1A1, "ROM font is available in boot ROM ver 0.8 or later.");
    }
    FontSize = FontData->cellWidth * 0x10;
    FontSpace = -0x10;
    return FontData;
}

void DEMOSetROMFontSize(s16 size, s16 space) {
    FontSize = size * 0x10;
    FontSpace = space * 0x10;
}

static void DrawFontChar(int x, int y, int z, int xChar, int yChar) {
    s16 posLeft = x;
    s16 posRight = posLeft + ((FontSize * FontData->cellWidth) / FontData->cellWidth);
    s16 posBottom = y;
    s16 posTop = y - ((FontData->cellHeight * ((FontData->cellHeight * FontSize) / FontData->cellWidth)) / FontData->cellHeight);
    s16 texLeft = xChar;
    s16 texTop = yChar;
    s16 texRight = (xChar + FontData->cellWidth);
    s16 texBottom = (yChar + FontData->cellHeight);

    GXBegin(0x80, 0, 4);
    GXPosition3s16(posLeft, posTop, z);
    GXTexCoord2s16(texLeft, texTop);
    GXPosition3s16(posRight, posTop, z);
    GXTexCoord2s16(texRight, texTop);
    GXPosition3s16(posRight, posBottom, z);
    GXTexCoord2s16(texRight, texBottom);
    GXPosition3s16(posLeft, posBottom, z);
    GXTexCoord2s16(texLeft, texBottom);
    GXEnd();
}

static void LoadSheet(void * image, enum _GXTexMapID texMapID) {
    float mtx[3][4];
    struct _GXTexObj texObj;

    if (LastSheet != image) {
        LastSheet = image;
        GXInitTexObj(&texObj, image, FontData->sheetWidth, FontData->sheetHeight, FontData->sheetFormat, 0, 0, 0);
        GXInitTexObjLOD(&texObj, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
        GXLoadTexObj(&texObj, texMapID);
        MTXScale(mtx, 1.0f / FontData->sheetWidth, 1.0f / FontData->sheetHeight, 1.0f);
        GXLoadTexMtxImm(mtx, 0x1E, 1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen(0, 1, 4, 0x1E);
    }
}

int DEMORFPuts(s16 x, s16 y, s16 z, char * string) {
    long cx;
    void * image;
    long xChar;
    long yChar;
    long width;

    ASSERTLINE(0x210, FontData);
    LastSheet = NULL;
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 3, 4);
    GXSetVtxAttrFmt(0, 0xD, 1, 3, 0);

    x *= 0x10;
    y *= 0x10;
    z *= 0x10;

    width = 0;
    while(*string != 0) {
        if (*string == 0xA) {
            width = 0;
            y += FontData->leading * 0x10;
            string++;
        } else {
            string = OSGetFontTexture(string, &image, &xChar, &yChar, &cx);
            LoadSheet(image, 0);
            DrawFontChar(x + width, y, z, xChar, yChar);
            width = FontSpace + ((FontSize * cx) / FontData->cellWidth) + width;
        }
    }
    return (width + 0xF) / 16;
}

int DEMORFPutsEx(s16 x, s16 y, s16 z, char * string, s16 maxWidth, int length) {
    long cx;
    void * image;
    long xChar;
    long yChar;
    long width;
    char * end;

    ASSERTLINE(0x23D, FontData);
    LastSheet = NULL;
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 3, 4);
    GXSetVtxAttrFmt(0, 0xD, 1, 3, 0);

    x *= 0x10;
    y *= 0x10;
    z *= 0x10;
    maxWidth *= 0x10;

    end = (char*)&string[length];
    width = 0;
    while(*string && string < end) {
        if (*string == 0xA) {
            width = 0;
            y += FontData->leading * 0x10;
            string++;
        } else {
            string = OSGetFontTexture(string, &image, &xChar, &yChar, &cx);
            if (maxWidth < width + (FontSize * cx / FontData->cellWidth) + FontSpace) {
                width = 0;
                y += FontData->leading * 0x10;
            }
            LoadSheet(image, 0);
            DrawFontChar(x + width, y, z, xChar, yChar);
            width = FontSpace + (FontSize * cx / FontData->cellWidth) + width;
        }
    }
    return (width + 0xF) / 16;
}

int DEMORFPrintf(s16 x, s16 y, s16 z, char * fmt, ...) {
    va_list vlist;
    char buf[256];

    va_start(vlist, fmt);
    vsprintf(buf, fmt, vlist);
    DEMORFPuts(x, y, z, buf);
}

char * DEMODumpROMFont(char * string) {
    unsigned long image[288];
    void * temp;
    int i;
    int j;
    long width;

    ASSERTLINE(0x295, FontData);

    if (OSGetFontEncode() == 1) {
        temp = (void*)((u32)FontData + 0xD3F00);
    } else {
        temp = (void*)((u32)FontData + 0x1D120);
    }
    temp = (void*)((u32)temp & 0xFFFFFFE0);
    OSLoadFont(FontData, temp);
    string = OSGetFontTexel(string, &image[0], 0, 0xC, &width);
    for(i = 0; i < 0x30; i++) {
        j = (i % 8) + ((i / 8) * 0x30);
        OSReport("%08x%08x%08x%08x%08x%08x\n", image[j], image[j+8], image[j+0x10], image[j+0x18], image[j+0x20], image[j+0x28]);
    }
    OSReport("\nwidth %d\n", width);
    OSInitFont(FontData);
    return string;
}

int DEMOGetRFTextWidth(char * string) {
    long cx;
    long width;

    ASSERTLINE(0x2C3, FontData);
    width = 0;
    while(*string != 0) {
        string = OSGetFontWidth(string, &cx);
        width = FontSpace + ((FontSize * cx) / FontData->cellWidth) + width;
    }
    return (width + 0xF) / 16;
}
