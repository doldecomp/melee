#ifndef _CHARPIPELINE_TEXPALETTE_H_
#define _CHARPIPELINE_TEXPALETTE_H_

#include <dolphin/gx/GXStruct.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* 0x00 */ u16 numEntries;
    /* 0x02 */ u8 unpacked;
    /* 0x03 */ u8 pad8;
    /* 0x04 */ GXTlutFmt format;
    /* 0x08 */ Ptr data;
} CLUTHeader, *CLUTHeaderPtr;

typedef struct {
    /* 0x00 */ u16 height;
    /* 0x02 */ u16 width;
    /* 0x04 */ u32 format;
    /* 0x08 */ Ptr data;
    /* 0x0C */ GXTexWrapMode wrapS;
    /* 0x10 */ GXTexWrapMode wrapT;
    /* 0x14 */ GXTexFilter minFilter;
    /* 0x18 */ GXTexFilter magFilter;
    /* 0x1C */ f32 LODBias;
    /* 0x20 */ u8 edgeLODEnable;
    /* 0x21 */ u8 minLOD;
    /* 0x22 */ u8 maxLOD;
    /* 0x23 */ u8 unpacked;
} TEXHeader, *TEXHeaderPtr;

typedef struct {
    /* 0x00 */ TEXHeaderPtr textureHeader;
    /* 0x04 */ CLUTHeaderPtr CLUTHeader;
} TEXDescriptor, *TEXDescriptorPtr;

typedef struct {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ u32 numDescriptors;
    /* 0x08 */ TEXDescriptorPtr descriptorArray;
} TEXPalette, *TEXPalettePtr;

void TEXGetPalette(TEXPalettePtr *pal, char *name);
TEXDescriptorPtr TEXGet(TEXPalettePtr pal, u32 id);
void TEXReleasePalette(TEXPalettePtr *pal);
void TEXGetGXTexObjFromPalette(TEXPalettePtr pal, GXTexObj *to, u32 id);
void TEXGetGXTexObjFromPaletteCI(TEXPalettePtr pal, GXTexObj *to, GXTlutObj *tlo, GXTlut tluts, u32 id);

#ifdef __cplusplus
}
#endif

#endif
