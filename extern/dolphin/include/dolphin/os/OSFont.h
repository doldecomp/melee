#ifndef _DOLPHIN_OSFONT_H_
#define _DOLPHIN_OSFONT_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_FONT_ENCODE_ANSI 0u
#define OS_FONT_ENCODE_SJIS 1u
#define OS_FONT_SIZE_ANSI (288 + 131072)    // 9 sheets
#define OS_FONT_SIZE_SJIS (3840 + 1179648)  // 1 sheet
#define OS_FONT_ROM_SIZE_ANSI 0x03000
#define OS_FONT_ROM_SIZE_SJIS 0x4D000

typedef struct OSFontHeader
{
    /*0x00*/ u16 fontType;
             u16 firstChar;
             u16 lastChar;
             u16 invalChar;
    /*0x08*/ u16 ascent;
             u16 descent;
             u16 width;
             u16 leading;
    /*0x10*/ u16 cellWidth;
             u16 cellHeight;
    /*0x14*/ u32 sheetSize;
    /*0x18*/ u16 sheetFormat;
             u16 sheetColumn;
             u16 sheetRow;
             u16 sheetWidth;
    /*0x20*/ u16 sheetHeight;
             u16 widthTable;
             u32 sheetImage;
             u32 sheetFullSize;
             u8 c0;
             u8 c1;
             u8 c2;
             u8 c3;
} OSFontHeader;

u16 OSGetFontEncode(void);
BOOL OSInitFont(OSFontHeader *fontData);
u32 OSLoadFont(OSFontHeader *fontData, void *temp);
char *OSGetFontTexture(char *string, void **image, s32 *x, s32 *y, s32 *width);
char *OSGetFontWidth(char *string, s32 *width);
char *OSGetFontTexel(char *string, void *image, s32 pos, s32 stride, s32 *width);

#ifdef __cplusplus
}
#endif

#endif
