#include "cobj.h"
#include "gobj.h"
#include "gobjgxlink.h"
#include "gobjobject.h"
#include "gobjplink.h"
#include "gobjuserdata.h"
#include "memory.h"
#include "sislib.h"

#include "sislib.static.h"

#include "sislib_font.h"
#include "state.h"
#include "tev.h"
#include "wobj.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include <m2c_macros.h>
#include <printf.h> // IWYU pragma: keep
#include <stdarg.h>
#include <stdio.h>
#include <dolphin/os.h>
#include <dolphin/types.h>
#include <melee/lb/lbarchive.h> ///< @todo Circular include

u8* HSD_SisLib_803A6478(u8* dst, u8* src)
{
    while (*src != 0) {
        if (*src >= 0x20) {
            *dst++ = *src++;
            *dst++ = *src++;
        } else {
            switch (*dst++ = *src++) {
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 14:
                *dst++ = *src++;
            case 12:
                *dst++ = *src++;
            case 5:
                *dst++ = *src++;
                *dst++ = *src++;
            }
        }
    }
    *dst = 0;
    return dst;
}

u8* HSD_SisLib_803A6530(s32 font_idx, s32 dst_idx, s32 src_idx)
{
    u8** sis_table = (u8**) HSD_SisLib_804D1124[font_idx];
    return HSD_SisLib_803A6478(sis_table[dst_idx], sis_table[src_idx]);
}

void HSD_SisLib_803A660C(s32 font_idx, s32 dst_idx, s32 src_idx)
{
    u8** sis_table = (u8**) HSD_SisLib_804D1124[font_idx];
    u8* dst = sis_table[dst_idx];
    u8* src = sis_table[src_idx];

    while (*dst != 0) {
        if (*dst >= 0x20) {
            dst += 2;
        } else {
            switch (*dst) {
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 14:
                dst += 5;
                break;
            case 12:
                dst += 4;
                break;
            case 5:
                dst += 3;
                break;
            default:
                dst += 1;
            }
        }
    }
    HSD_SisLib_803A6478(dst, src);
}

HSD_Text* HSD_SisLib_803A6754(int font_idx, int context_id)
{
    SisBlock* alloc;
    HSD_Text* text;
    HSD_Text* buffer;

    text = HSD_SisLib_803A5ACC(font_idx, context_id, 0.0F, 0.0F, 0.0F, 640.0F,
                               480.0F);
    alloc = HSD_SisLib_Alloc(0x10);
    text->alloc_data = alloc;
    buffer = HSD_SisLib_Alloc(0x80);
    alloc->data = buffer;
    alloc->next = (SisBlock*) buffer;
    alloc->size = 0x80; ///< @todo This being a byte store means one of my
                        ///< assumptions is wrong;
    // maybe this is a different struct.
    *(u8*) &alloc->next->next =
        0; ///< @todo Do any other Data struct usages have a 0xC member?
    *(&alloc->size + 1) = 0;
    HSD_SisLib_803A6368(text, 0);
    text->sis_buffer = (SIS*) alloc->data;
    return text;
}

/// @brief Converts ASCII to "SIS" format
/// @details - Maps ASCII characters to SIS characters by using byte pair
/// lookup tables
/// @param data output buffer for the converted string
/// @param string ASCII string to be converted
/// @return length of encoded string
s32 HSD_SisLib_803A67EC(u8* data, u8* string)
{
    u8* lut_ptr;
    s32 state;
    s32 state_dot;
    s32 out_idx_digit;
    u8* str_cursor;
    s32 state_digit;
    s32 lut_idx;
    s32 in_idx;
    s32 out_idx;
    u8* char_ptr;
    s32 state_colon;
    s32 has_kerning[1];
    u8* out_ptr;
    u8 cur_char;
    u8 sjis_hi;
    u8 sjis_lo;

    has_kerning[0] = 0;
    str_cursor = string;
    lut_ptr = lbl_8040C8C0;
    out_ptr = HSD_SisLib_8040C680;
    out_idx = 0;
    for (in_idx = 0; in_idx < 0x80; in_idx++, str_cursor++) {
        char_ptr = &string[in_idx];
        cur_char = *char_ptr;
        if (cur_char == '\0') {
            if (has_kerning[0] != 0) {
                data[out_idx++] = 0xB;
            }
            break;
        }
        if (cur_char == ' ') {
            state = has_kerning[0];
            if (state == 0) {
                data[out_idx++] = 0xA;
                data[out_idx++] = 0xF4;
                data[out_idx++] = 0x0;
                state += 1;
                data[out_idx++] = 0x0;
                data[out_idx++] = 0x0;
            }
            has_kerning[0] = state;
            sjis_hi = 0x81;
            sjis_lo = 0x40;
        } else if (cur_char == '"') {
            data[out_idx++] = 0xB;
            has_kerning[0] = 0;
            sjis_hi = 0x81;
            sjis_lo = 0x68;
        } else if (cur_char == '\'') {
            data[out_idx++] = 0xB;
            has_kerning[0] = 0;
            sjis_hi = 0x81;
            sjis_lo = 0x66;
        } else if (cur_char == ',') {
            data[out_idx++] = 0xB;
            has_kerning[0] = 0;
            sjis_hi = 0x81;
            sjis_lo = 0x43;
        } else if (cur_char == '-') {
            data[out_idx++] = 0xB;
            has_kerning[0] = 0;
            sjis_hi = 0x81;
            sjis_lo = 0x7C;
        } else if (cur_char == '.') {
            state_dot = has_kerning[0];
            if (state_dot == 0) {
                data[out_idx++] = 0xA;
                data[out_idx++] = 0xF4;
                data[out_idx++] = 0x0;
                state_dot += 1;
                data[out_idx++] = 0x0;
                data[out_idx++] = 0x0;
            }
            has_kerning[0] = state_dot;
            sjis_hi = 0x81;
            sjis_lo = 0x44;
        } else if ((cur_char >= '0') && (cur_char <= '9')) {
            state_digit = has_kerning[0];
            out_idx_digit = out_idx;
            if (state_digit == 0) {
                data[out_idx_digit++] = 0xA;
                data[out_idx_digit++] = 0xF4;
                data[out_idx_digit++] = 0x0;
                state_digit += 1;
                data[out_idx_digit++] = 0x0;
                data[out_idx_digit++] = 0x0;
            }
            has_kerning[0] = state_digit;
            out_idx = out_idx_digit;
            sjis_hi = 0x82;
            sjis_lo = (*char_ptr) + 0x1F;
        } else if (cur_char == ':') {
            state_colon = has_kerning[0];
            if (state_colon == 0) {
                data[out_idx++] = 0xA;
                data[out_idx++] = 0xF4;
                data[out_idx++] = 0x0;
                state_colon += 1;
                data[out_idx++] = 0x0;
                data[out_idx++] = 0x0;
            }
            has_kerning[0] = state_colon;
            sjis_hi = 0x81;
            sjis_lo = 0x46;
        } else if ((cur_char >= 'A') && (cur_char <= 'Z')) {
            data[out_idx++] = 0xB;
            has_kerning[0] = 0;
            sjis_hi = 0x82;
            sjis_lo = (*char_ptr) + 0x1F;
        } else if ((cur_char >= 'a') && (cur_char <= 'z')) {
            data[out_idx++] = 0xB;
            has_kerning[0] = 0;
            sjis_hi = 0x82;
            sjis_lo = (*char_ptr) + 0x20;
        } else {
            data[out_idx++] = 0xB;
            has_kerning[0] = 0;
            sjis_hi = string[in_idx];
            in_idx += 1;
            sjis_lo = str_cursor[1];
            str_cursor += 1;
        }
        for (lut_idx = 0; lut_idx < ARRAY_SIZE(HSD_SisLib_FontAtlas);
             lut_idx++)
        {
            if ((sjis_hi == lut_ptr[lut_idx * 2]) &&
                (sjis_lo == lut_ptr[lut_idx * 2 + 1]))
            {
                s32 write_idx;

                write_idx = out_idx;
                out_idx += 1;
                data[write_idx] = out_ptr[lut_idx * 2];
                write_idx = out_idx;
                out_idx += 1;
                data[write_idx] = out_ptr[lut_idx * 2 + 1];
                break;
            }
        }
    }
    data[out_idx] = 0;
    return out_idx;
}

int HSD_SisLib_803A6B98(HSD_Text* text, float x, float y, const char* fmt, ...)
{
    u8 buffer[128];
    u8 encoded[128];
    s32 x_coord;
    s32 y_coord;
    HSD_Text* old_buf;
    SisBlock* alloc;
    s32 encoded_len;
    s32 copied_bytes;
    u8* new_buf;
    u8* copy_src;
    s32 copy_idx;
    u32 required_size;
    u32 old_size;
    u8** cur;
    va_list args;

    encoded_len = 0;
    alloc = text->alloc_data;
    encoded[0] = 0;
    if (fmt) {
        va_start(args, fmt);
        vsnprintf((char*) buffer, -1, fmt, args);
        va_end(args);
        encoded_len = HSD_SisLib_803A67EC(encoded, buffer);
    }

    old_size = alloc->size;
    required_size = ((u8*) alloc->next - (u8*) (old_buf = alloc->data)) + 0x11;
    required_size = encoded_len + required_size;
    if (old_size < required_size) {
        alloc->size =
            old_size + ((((required_size - old_size) >> 7U) + 1) << 7);
        new_buf = HSD_SisLib_Alloc((s32) alloc->size);
        copy_src = (u8*) old_buf;
        copy_idx = 0;
        while (copy_idx < (s32) (((u8*) alloc->next - (u8*) alloc->data) + 1))
        {
            new_buf[copy_idx] = copy_src[copy_idx];
            copy_idx += 1;
        }
        alloc->data = (HSD_Text*) new_buf;
        text->sis_buffer = (SIS*) new_buf;
        alloc->next = (SisBlock*) (new_buf + ((u8*) alloc->next -
                                              HSD_SisLib_BytePtr(old_buf)));
        HSD_SisLib_Free(old_buf);
    }

    cur = (u8**) &alloc->next;
    *(*cur)++ = 7;
    copied_bytes = 0;
    x_coord = (s16) x;
    *(*cur)++ = (u8) (x_coord >> 8);
    *(*cur)++ = (u8) x_coord;
    y_coord = (s16) y;
    *(*cur)++ = (u8) (y_coord >> 8);
    *(*cur)++ = (u8) y_coord;
    *(*cur)++ = 0xC;
    *(*cur)++ = text->text_color.r;
    *(*cur)++ = text->text_color.g;
    *(*cur)++ = text->text_color.b;
    *(*cur)++ = 0xE;
    *(*cur)++ = (u8) (s32) text->x34.x;
    *(*cur)++ = (u8) (s32) (256.0F * text->x34.x);
    *(*cur)++ = (u8) (s32) text->x34.y;
    *(*cur)++ = (u8) (s32) (256.0F * text->x34.y);
    for (; copied_bytes < encoded_len; copied_bytes++) {
        *(*cur)++ = encoded[copied_bytes];
    }
    *(*cur)++ = 0xF;
    *(*cur)++ = 0xD;
    **cur = 0;
    return ((sisLib_803A7664_t*) alloc)->xC++;
}

/// @todo there seems to be a file boundary before this function,
/// because its data section is 8-byte aligned after the previous C strings
u8* fn_803A6FEC(u8* sis_data, s32 entry_idx, s32* out_size)
{
    s32 unused_r4;
    u8 char_size;
    u8* unused_r3;
    u8* scan_ptr;
    u8 unused_r0;
    u8 unused_r0_2;

    for (;;) {
        switch (*sis_data) {
        case 0:
            return NULL;
        case 12:
            sis_data += 3;
        case 11:
        case 13:
        case 15:
            break;
        case 7:
            entry_idx -= 1;
            if (entry_idx < 0) {
                goto end;
            }
        /* fallthrough */
        case 10:
        case 14:
            sis_data += 4;
            break;
        default:
            sis_data += 1;
            break;
        }
        sis_data += 1;
    }
end:
    if (out_size != NULL) {
        *out_size = 0;
        scan_ptr = sis_data + 0xE;
        do {
            char_size = 0;
            if (*scan_ptr >= 32) {
                char_size = 2;
            } else if (*scan_ptr == 10) {
                char_size = 5;
            } else if (*scan_ptr == 11) {
                char_size = 1;
            }
            *out_size += char_size;
            scan_ptr += char_size;
        } while (char_size != 0);
    }
    return sis_data;
}

s32 HSD_SisLib_803A70A0(HSD_Text* text, s32 entry_idx, char* fmt, ...)
{
    u8 buffer[128];
    u8 encoded[128];
    HSD_Text* old_buf;
    u8* playhead;
    SisBlock* alloc;
    s32 new_size;
    s32 tail_len;
    s32 result;
    s32 old_size;
    u8* entry;
    u8* copy_src;
    u8* new_buf;
    s32 copy_idx;
    va_list args;
    s32 i;

    result = 0;

    entry = fn_803A6FEC((u8*) text->sis_buffer, entry_idx, &old_size);
    if (entry != NULL) {
        alloc = text->alloc_data;
        playhead = entry + 0xE;
        if (fmt != NULL) {
            va_start(args, fmt);
            vsnprintf((char*) buffer, -1, fmt, args);
            va_end(args);
            new_size = HSD_SisLib_803A67EC(encoded, buffer);
        } else {
            new_size = 0;
        }
        if (old_size < new_size) {
            u32 required_size;

            result = new_size - old_size;
            tail_len = (u8*) alloc->next - playhead;
            required_size =
                new_size +
                ((u8*) alloc->next - (u8*) (old_buf = alloc->data)) + 1;
            if (alloc->size < required_size) {
                alloc->size +=
                    ((((required_size - alloc->size) >> 7U) + 1) << 7);
                new_buf = HSD_SisLib_Alloc((s32) alloc->size);
                copy_src = (u8*) old_buf;
                copy_idx = 0;
                while (copy_idx <
                       (s32) (((u8*) alloc->next - (u8*) alloc->data) + 1))
                {
                    new_buf[copy_idx] = copy_src[copy_idx];
                    copy_idx += 1;
                }
                alloc->data = (HSD_Text*) new_buf;
                text->sis_buffer = (SIS*) new_buf;
                alloc->next =
                    (SisBlock*) (new_buf + ((u8*) alloc->next -
                                            HSD_SisLib_BytePtr(old_buf)));
                HSD_SisLib_Free(old_buf);
                playhead = (u8*) alloc->next - tail_len;
            }
            for (i = tail_len; i > 0; i--) {
                playhead[result + i] = playhead[i];
            }
            alloc->next = (SisBlock*) ((u8*) alloc->next + result);
        } else if (old_size > new_size) {
            s32 shrink_size = old_size - new_size;
            s32 tail_len = (u8*) alloc->next - playhead;

            for (i = 0; i < tail_len; i++) {
                playhead[i] = playhead[shrink_size + i];
            }
            alloc->next = (SisBlock*) ((u8*) alloc->next - shrink_size);
        }
        for (i = 0; i < new_size; i++) {
            *playhead++ = encoded[i];
        }
        *playhead = 0xF;
        result = 1;
    }
    return result;
}

void HSD_SisLib_803A746C(HSD_Text* text, s32 entry_idx, f32 new_x, f32 new_y)
{
    s32 x;
    s32 y;
    u8* entry;

    entry = fn_803A6FEC((u8*) text->sis_buffer, entry_idx, NULL);
    if (entry != NULL) {
        u8* p = entry + 1;
        x = (s16) new_x;
        p[0] = (u8) (x >> 8);
        y = (s16) new_y;
        p[1] = (u8) x;
        p[2] = (u8) (y >> 8);
        p[3] = (u8) y;
    }
}

void HSD_SisLib_803A74F0(HSD_Text* text, s32 entry_idx, GXColor* color_rgb)
{
    u8* entry;
    u8* color_ptr;
    void* unused_r31;

    entry = fn_803A6FEC((u8*) text->sis_buffer, entry_idx, NULL);
    if (entry != NULL) {
        color_ptr = entry + 5;
        color_ptr[1] = color_rgb->r;
        color_ptr[2] = color_rgb->g;
        color_ptr[3] = color_rgb->b;
    }
}

void HSD_SisLib_803A7548(HSD_Text* text, int entry_idx, float scale_x,
                         float scale_y)
{
    u8* entry = fn_803A6FEC((u8*) text->sis_buffer, entry_idx, NULL);
    u8* scale_ptr;
    if (entry != NULL) {
        scale_ptr = entry + 9;
        *++scale_ptr = (u8) scale_x;
        scale_ptr[1] = (u8) (256.0F * scale_x);
        scale_ptr[2] = (u8) scale_y;
        scale_ptr[3] = (u8) (256.0F * scale_y);
    }
}

void HSD_SisLib_803A75E0(HSD_Text* text, s32 entry_idx)
{
    GXColor color;
    u8* entry;
    u8* p;

    if (HSD_SisLib_803A70A0(text, entry_idx, 0) != 0) {
        color = text->text_color;
        entry = fn_803A6FEC((u8*) text->sis_buffer, entry_idx, NULL);
        if (entry != NULL) {
            p = entry + 5;
            p[1] = color.r;
            p[2] = color.g;
            p[3] = color.b;
        }
    }
}

void HSD_SisLib_803A7664(HSD_Text* text)
{
    sisLib_803A7664_t* data;

    data = (sisLib_803A7664_t*) text->alloc_data;
    data->x0 = data->x4;
    *(u8*) data->x0 = 0;
    data->xC = 0;
}
