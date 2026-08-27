#include "cobj.h"
#include "gobj.h"
#include "gobjobject.h"
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
#include <dolphin/types.h>
#include <melee/lb/lbarchive.h> ///< @todo Circular include

static inline f32 HSD_SisLib_GlyphWidth(HSD_Text* text, f32 scale_x)
{
    return 32.0F * text->x80.x * scale_x;
}

void HSD_SisLib_803A7684(HSD_Text* text, const u8* cursor, u8 flags)
{
    switch (flags & 0x7F) {
    case 1: {
        u8* old_buf;
        u32 count;
        int idx;
        int new_x6E;
        int old_x6E;

        old_x6E = text->x6E;
        if (old_x6E < (s32) (text->x6C + 5)) {
            new_x6E = old_x6E + 0x10;
            old_buf = (u8*) text->string_buffer;
            text->string_buffer = HSD_SisLib_Alloc(new_x6E);
            text->x6E = (u16) new_x6E;
            count = old_x6E;
            for (idx = 0; (u32) idx < count; idx++) {
                text->string_buffer[idx] = old_buf[idx];
            }
            while (idx < (s32) text->x6E) {
                text->string_buffer[idx] = 0;
                idx += 1;
            }
            HSD_SisLib_Free(old_buf);
        }
        text->string_buffer[text->x6C++] =
            (u8) ((s32) (256.0F * text->x78.x) >> 8);
        text->string_buffer[text->x6C++] = (u8) (256.0F * text->x78.x);
        text->string_buffer[text->x6C++] =
            (u8) ((s32) (256.0F * text->x78.y) >> 8);
        text->string_buffer[text->x6C++] = (u8) (256.0F * text->x78.y);
        text->string_buffer[text->x6C++] = flags;
        return;
    }
    case 2: {
        int old_x6E;
        u32 count;
        int idx;
        u8* old_buf;
        int new_x6E;

        old_x6E = text->x6E;
        if (old_x6E < (s32) (text->x6C + 4)) {
            new_x6E = old_x6E + 0x10;
            old_buf = (u8*) text->string_buffer;
            text->string_buffer = HSD_SisLib_Alloc(new_x6E);
            text->x6E = (u16) new_x6E;
            count = old_x6E;
            for (idx = 0; (u32) idx < count; idx++) {
                text->string_buffer[idx] = old_buf[idx];
            }
            while (idx < (s32) text->x6E) {
                text->string_buffer[idx] = 0;
                idx += 1;
            }
            HSD_SisLib_Free(old_buf);
        }
        text->string_buffer[text->x6C++] = text->active_color.r;
        text->string_buffer[text->x6C++] = text->active_color.g;
        text->string_buffer[text->x6C++] = text->active_color.b;
        text->string_buffer[text->x6C++] = flags;
        return;
    }
    case 3: {
        int old_x6E;
        u32 count;
        int idx;
        u8* old_buf;
        int new_x6E;

        old_x6E = text->x6E;
        if (old_x6E < (s32) (text->x6C + 5)) {
            new_x6E = old_x6E + 0x10;
            old_buf = (u8*) text->string_buffer;
            text->string_buffer = HSD_SisLib_Alloc(new_x6E);
            text->x6E = (u16) new_x6E;
            count = old_x6E;
            for (idx = 0; (u32) idx < count; idx++) {
                text->string_buffer[idx] = old_buf[idx];
            }
            while (idx < (s32) text->x6E) {
                text->string_buffer[idx] = 0;
                idx += 1;
            }
            HSD_SisLib_Free(old_buf);
        }
        text->string_buffer[text->x6C++] =
            (u8) ((s32) (256.0F * text->x80.x) >> 8);
        text->string_buffer[text->x6C++] = (u8) (256.0F * text->x80.x);
        text->string_buffer[text->x6C++] =
            (u8) ((s32) (256.0F * text->x80.y) >> 8);
        text->string_buffer[text->x6C++] = (u8) (256.0F * text->x80.y);
        text->string_buffer[text->x6C++] = flags;
        return;
    }
    case 4: {
        int old_x6E;
        u32 count;
        int idx;
        u8* old_buf;
        int new_x6E;

        old_x6E = text->x6E;
        if (old_x6E < (s32) (text->x6C + 2)) {
            new_x6E = old_x6E + 0x10;
            old_buf = (u8*) text->string_buffer;
            text->string_buffer = HSD_SisLib_Alloc(new_x6E);
            text->x6E = (u16) new_x6E;
            count = old_x6E;
            for (idx = 0; (u32) idx < count; idx++) {
                text->string_buffer[idx] = old_buf[idx];
            }
            while (idx < (s32) text->x6E) {
                text->string_buffer[idx] = 0;
                idx += 1;
            }
            HSD_SisLib_Free(old_buf);
        }
        text->string_buffer[text->x6C++] = text->alignment;
        text->string_buffer[text->x6C++] = flags;
        return;
    }
    case 5: {
        int new_x6E;
        u32 count;
        int idx;
        u8* old_buf;
        int old_x6E;

        old_x6E = text->x6E;
        if (old_x6E < (s32) (text->x6C + 5)) {
            new_x6E = old_x6E + 0x10;
            old_buf = (u8*) text->string_buffer;
            text->string_buffer = HSD_SisLib_Alloc(new_x6E);
            text->x6E = (u16) new_x6E;
            count = old_x6E;
            for (idx = 0; (u32) idx < count; idx++) {
                text->string_buffer[idx] = old_buf[idx];
            }
            while (idx < (s32) text->x6E) {
                text->string_buffer[idx] = 0;
                idx += 1;
            }
            HSD_SisLib_Free(old_buf);
        }
        text->string_buffer[text->x6C++] = (u8) ((u32) cursor >> 0x18U);
        text->string_buffer[text->x6C++] =
            (u8) (((u32) cursor >> 0x10U) & 0xFFU);
        text->string_buffer[text->x6C++] = (u8) (((u32) cursor >> 8U) & 0xFFU);
        text->string_buffer[text->x6C++] = (u8) (u32) cursor;
        text->string_buffer[text->x6C++] = flags;
    }
    }
}

s32 HSD_SisLib_803A7F0C(HSD_Text* text, s32 flags)
{
    s8 entry;
    s32 flag_hi;
    s32 entry_flags;
    s32 target_type;
    s32 result;
    s32 remove_size;
    s32 pos;

    flag_hi = flags & 0x80;
    target_type = flags & 0x7F;
    pos = text->x6C;
    result = 0;
    remove_size = 0;
    while (pos >= 0) {
        entry = text->string_buffer[pos];
        entry_flags = entry & 0x80;
        switch ((u8) entry & 0x7F) { /* irregular */
        case 1:
            pos -= 4;
            if (target_type == 1) {
                text->x78.x =
                    (f32) * (s16*) (text->string_buffer + pos) / 256.0F;
                text->x78.y =
                    (f32) * (s16*) (text->string_buffer + pos + 2) / 256.0F;
                if (flag_hi == entry_flags) {
                    remove_size = 5;
                }
                goto done;
            }
            break;
        case 2:
            pos -= 3;
            if (target_type == 2) {
                text->active_color.r = text->string_buffer[pos];
                text->active_color.g = text->string_buffer[pos + 1];
                text->active_color.b = text->string_buffer[pos + 2];
                if (flag_hi == entry_flags) {
                    remove_size = 4;
                }
                goto done;
            }
            break;
        case 3:
            pos -= 4;
            if (target_type == 3) {
                text->x80.x =
                    (f32) * (u16*) (text->string_buffer + pos) / 256.0F;
                text->x80.y =
                    (f32) * (u16*) (text->string_buffer + pos + 2) / 256.0F;
                if (flag_hi == entry_flags) {
                    remove_size = 5;
                }
                goto done;
            }
            break;
        case 4:
            pos -= 1;
            if (target_type == 4) {
                text->alignment = text->string_buffer[pos];
                if (flag_hi == entry_flags) {
                    remove_size = 2;
                }
                goto done;
            }
            break;
        case 5:
            pos -= 4;
            if (target_type == 5) {
                result = *(s32*) (text->string_buffer + pos);
                if (flag_hi == entry_flags) {
                    remove_size = 5;
                }
                goto done;
            }
            break;
        }
        pos -= 1;
    }
done:
    if (remove_size != 0) {
        while ((pos + remove_size) < (s32) text->x6C) {
            text->string_buffer[pos] = text->string_buffer[pos + remove_size];
            pos += 1;
        }
        while (pos < (s32) text->x6C) {
            text->string_buffer[pos] = 0;
            pos += 1;
        }
        text->x6C -= remove_size;
    }
    return result;
}

void HSD_SisLib_803A8134(void* cursor, HSD_Text* text, f32* out_width,
                         f32* out_height)
{
    SIS* sis;
    TextGlyphTexture* glyph_tex;
    u8* default_kerning = HSD_SisLib_8040CB00;
    f32 line_height;
    f32 saved_scale_x;
    f32 saved_scale_y;
    f32 saved_spacing;
    u16 scale_val;
    u16 kern_enabled;
    u16 saved_x6C;
    u16 glyph_code;
    s32 kern_width;
    s32 clear_idx;
    u32 pop_result;
    TextKerning* kern_data_2;
    u8 opcode;
    TextKerning* kern_data;
    saved_scale_x = text->x80.x;
    saved_scale_y = text->x80.y;
    saved_spacing = text->x78.x;
    kern_enabled = text->kerning;
    sis = HSD_SisLib_804D1124[text->font_idx];
    saved_x6C = text->x6C;
    if (sis != NULL) {
        glyph_tex = sis->textures;
    }
    *out_width = 0.0F;
    *out_height = 32.0F * text->x80.y;
loop_3:
    opcode = *(u8*) cursor;
    switch (opcode) {
    case 0:
        pop_result = HSD_SisLib_803A7F0C(text, 0x85);
        if (pop_result != 0U) {
            cursor = (u8*) (pop_result + 4);
            goto block_33;
        }
        break;
    case 1:
    case 2:
    case 3:
    case 7:
        break;
    case 9:
        HSD_SisLib_803A7684(text, (u8*) cursor, 0x85U);
        /* fallthrough */
    case 8:
        cursor = (u8*) *(s32*) ((u8*) cursor + 1) - 1;
        goto block_33;
    case 14:
        HSD_SisLib_803A7684(text, (u8*) cursor, 0x83U);
        text->x80.x = (f32) * (u16*) ((u8*) cursor + 1) / 256.0F;
        scale_val = *(u16*) ((u8*) cursor + 3);
        cursor = (u8*) cursor + 4;
        text->x80.y = (f32) scale_val / 256.0F;
        goto block_33;
    case 15:
        HSD_SisLib_803A7F0C(text, 0x83);
        goto block_33;
    case 6:
        cursor = (u8*) cursor + 4;
        goto block_33;
    case 10:
        if ((text->alloc_data == NULL) || (kern_enabled == 0)) {
            HSD_SisLib_803A7684(text, (u8*) cursor, 0x81U);
            text->x78.x = (f32) * (s16*) ((u8*) cursor + 1) / 256.0F;
        }
        cursor = (u8*) cursor + 4;
        goto block_33;
    case 11:
        if ((text->alloc_data == NULL) || (kern_enabled == 0)) {
            HSD_SisLib_803A7F0C(text, 0x81);
        }
        goto block_33;
    case 12:
        cursor = (u8*) cursor + 3;
        goto block_33;
    case 5:
        cursor = (u8*) cursor + 2;
        goto block_33;
    case 22:
        kern_enabled = 1;
        goto block_33;
    case 23:
        kern_enabled = 0;
        goto block_33;
    case 26:
        *out_width += text->x80.x * (16.0F + text->x78.x);
        if (*out_height < (32.0F * text->x80.y)) {
            *out_height = 32.0F * text->x80.y;
        }
        goto block_33;
    default:
        if (opcode >= 0x20U) {
            *out_width += text->x80.x * (32.0F + text->x78.x);
            if (kern_enabled != 0) {
                glyph_code = *(u16*) cursor;
                if (glyph_code < 0x4000U) {
                    kern_width =
                        (s32) (default_kerning +
                               (((glyph_code - 0x2000) * 2) & 0x1FFFE));
                    kern_data = (TextKerning*) kern_width;
                    kern_width = kern_data->right - 2;
                    kern_data = (TextKerning*) (u32) kern_data->left;
                    kern_width = (s32) kern_data + kern_width;
                    *out_width =
                        -((text->x80.x * (f32) kern_width) - *out_width);
                } else {
                    kern_data_2 =
                        (TextKerning*) &glyph_tex
                            ->data[((glyph_code - 0x4000) * 2) & 0x1FFFE];
                    kern_width = kern_data_2->right - 2;
                    kern_data_2 = (TextKerning*) (u32) kern_data_2->left;
                    kern_width = (s32) kern_data_2 + kern_width;
                    *out_width =
                        -((text->x80.x * (f32) kern_width) - *out_width);
                }
            }
            if (*out_height < (32.0F * text->x80.y)) {
                *out_height = 32.0F * text->x80.y;
            }
            cursor = (u8*) cursor + 1;
        }
        goto block_33;
    }
    goto block_done;
block_33:
    cursor = (u8*) cursor + 1;
    goto loop_3;
block_done:
    *out_width -= text->x78.x;
    text->x80.x = saved_scale_x;
    text->x80.y = saved_scale_y;
    text->x78.x = saved_spacing;
    text->x6C = saved_x6C;
    opcode = 0;
    clear_idx = text->x6C;
    while (clear_idx < (s32) text->x6E) {
        text->string_buffer[clear_idx] = opcode;
        clear_idx += 1;
    }
}

static void sisFitLineToBox(HSD_Text* text, f32 measured_width)
{
    if ((text->fitting == 1) && (text->box_size_x < measured_width)) {
        text->current_width = 0.0F;
        text->x88 = (text->box_size_x / measured_width);
    } else {
        text->x88 = 1.0F;
        switch ((s32) text->alignment) {
        case 1:
            text->current_width =
                (f32) (0.5F * (text->box_size_x - measured_width));
            break;
        case 2:
            text->current_width = (text->box_size_x - measured_width);
            break;
        default:
            text->current_width = 0.0F;
            break;
        }
    }
}

void HSD_SisLib_803A84BC(HSD_GObj* gobj, int pass)
{
    // clang-format off
    HSD_Text *text;
    GXTexObj tex_obj;
    Mtx m;
    f32 line_width_out;
    f32 line_height_out;
    TextKerning *kerning = NULL;
    TextGlyphTexture *textures = NULL;

    f32 min_x;
    f32 min_y;
    f32 max_x;
    f32 max_y;

    u8 saved_color_r;
    u8 saved_color_g;
    u8 saved_color_b;
    u8 saved_fitting;
    u8 saved_alignment;
    f32 saved_font_size_x;
    f32 saved_font_size_y;
    f32 saved_scale_x;
    f32 saved_scale_y;
    u16 line_delay;
    u16 char_delay;
    u32 skip_count;
    u16 saved_x6C;
    u8 saved_kerning;

    u8 *data = M2C_BITWISE(u8*, HSD_SisLib_FontAtlas);
    u8 *default_kerning = HSD_SisLib_8040CB00;

    if (gobj != NULL) {
        if (pass != 2U) {
            return;
        }
        text = HSD_GObjGetUserData(gobj);
    } else {
        text = (HSD_Text*) pass;
    }
    if (text->hidden == 0 && text->sis_buffer != NULL) {
        u8 *sis_cursor = (u8 *)text->sis_buffer;
        if (gobj != NULL) {
            SIS *sis = HSD_SisLib_804D1124[text->font_idx];
            if (sis != NULL) {
                kerning = sis->kerning;
                textures = sis->textures;
            }
        }
        if (gobj != NULL) {
            if (text->x4C != 0) {
                HSD_StateSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            } else {
                HSD_StateSetZMode(GX_FALSE, GX_NEVER, GX_FALSE);
            }
            HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), (MtxPtr)&m);
        } else {
            Mtx projection_m;

            GXSetZMode(0U, 0U, 0U);
            GXSetViewport(0.0F, 0.0F, 640.0F, 480.0F, 0.0F, 1.0F);
            GXSetScissor(0, 0, 0x280, 0x1E0);
#ifdef MUST_MATCH
            MTXOrtho((MtxPtr) ((u8*) &projection_m[0][0] - 0x14), 0.0F,
                     -480.0F, 0.0F, 640.0F, 0.0F, 2.0F);
            GXSetProjection((MtxPtr) ((u8*) &projection_m[2][3] - 0x40), 0);
#else
            MTXOrtho((MtxPtr)&projection_m, 0.0F, -480.0F, 0.0F, 640.0F,
                     0.0F, 2.0F);
            GXSetProjection((MtxPtr)&projection_m, 0);
#endif
            m[0][0] = 1.0F;
            m[0][1] = 0.0F;
            m[0][2] = 0.0F;
            m[0][3] = 0.0F;
            m[1][0] = 0.0F;
            m[1][1] = 1.0F;
            m[1][2] = 0.0F;
            m[1][3] = 0.0F;
            m[2][0] = 0.0F;
            m[2][1] = 0.0F;
            m[2][2] = 1.0F;
            m[2][3] = -1.0F;
        }
        GXSetCurrentMtx(0);
        GXLoadPosMtxImm((MtxPtr)&m, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_DISABLE, GX_PTIDENTITY);
        if (gobj != NULL) {
            HSD_StateSetNumChans(0);
        } else {
            GXSetNumChans(0U);
        }
        GXClearVtxDesc();
        GXSetCullMode(GX_CULL_NONE);
        GXSetNumTexGens(1U);
        GXSetNumTevStages(1U);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_RGBA6, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER, GX_NEVER);
        GXSetColorUpdate(GX_ENABLE);
        GXSetAlphaUpdate(GX_DISABLE);
        if (gobj != NULL) {
            if (text->render_callback != NULL) {
                text->render_callback(gobj);
            }
        }
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        // first quad is the background
        if (text->bg_color.a != 0) {
            min_x = text->pos_x;
            min_y = text->pos_y;
            max_x =
                (text->box_size_x * text->font_size.x) + text->pos_x;
            max_y =
                (text->box_size_y * text->font_size.y) + text->pos_y;
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
            GXSetTevColor(GX_TEVREG0, *(&text->bg_color));
            GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
            // @note: could be inlined
            {
                f32 depth = text->pos_z;
                f32 neg_min_y = -min_y;
                f32 neg_max_y = -max_y;
                GXPosition3f32(min_x, neg_min_y, depth);
                GXTexCoord2f32(0.0F, 0.0F);
                GXPosition3f32(max_x, neg_min_y, depth);
                GXTexCoord2f32(1.0F, 0.0F);
                GXPosition3f32(max_x, neg_max_y, depth);
                GXTexCoord2f32(1.0F, 1.0F);
                GXPosition3f32(min_x, neg_max_y, depth);
                GXTexCoord2f32(0.0F, 1.0F);
            }
            GXEnd();
        }
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
        if (text->x4E != 0) {
            min_x = (text->x14.z * text->font_size.x) + text->pos_x;
            max_x = (text->font_size.x * (text->box_size_x - text->x14.w)) + text->pos_x;
            min_y = (text->x14.x * text->font_size.y) + text->pos_y;
            max_y = (text->font_size.y * (text->box_size_y - text->x14.y)) + text->pos_y;
        }
        if (text->alloc_data != NULL) {
            text->x78.x = text->x3C.x;
            text->x78.y = text->x3C.y;
            // interesting pattern... is there a U8Vec3?
            text->alignment = text->default_alignment;
            text->kerning = text->default_kerning;
            text->fitting = text->default_fitting;
        }
        {
            f64 half_glyph = 16.0;

            u32 line_started;

        restart:
            text->current_height = 0.0F;
            line_started = 0U;
            saved_font_size_x = text->x80.x;
            saved_font_size_y = text->x80.y;
            saved_color_r = text->active_color.r;
            saved_color_g = text->active_color.g;
            saved_color_b = text->active_color.b;
            saved_scale_x = text->x78.x;
            saved_scale_y = text->x78.y;
            saved_alignment = text->alignment;
            saved_fitting = text->fitting;
            saved_kerning = text->kerning;
            line_delay = text->x90;
            char_delay = text->x92;
            skip_count = text->x98;
            saved_x6C = text->x6C;
            for (;;) {
                if ((sis_cursor == text->x60) && (text->x4B != 0)) {
                    break;
                }
                if ((sis_cursor == text->x60) && text->x94) {
                    text->x94--;
                    break;
                } else {
                    u32 pop_result;
                    s32 clear_idx;
                    f32 x_origin;
                    s16 y_offset;
                    u8 opcode = *sis_cursor;
                    switch (*sis_cursor) {
                        case 0:
                            pop_result = HSD_SisLib_803A7F0C(text, 5);
                            if (pop_result != 0U) {
                                sis_cursor = (u8*) (pop_result + 4);
                                break;
                            }
                            goto render_done;
                        case 1:
                            text->x60 = NULL;
                            clear_idx = 0;
                            text->active_color = text->text_color;
                            text->x80.x = text->x34.x;
                            text->x80.y = text->x34.y;
                            text->x78.x = text->x3C.x;
                            text->x78.y = text->x3C.y;
                            text->x90 = text->x44;
                            text->x92 = text->x46;
                            text->alignment = text->default_alignment;
                            text->kerning = text->default_kerning;
                            text->fitting = text->default_fitting;
                            text->x94 = 0U;
                            text->x4B = 0U;
                            while (clear_idx < (s32) text->x6E) {
                                text->string_buffer[clear_idx] = 0;
                                clear_idx += 1;
                            }
                            text->x6C = 0;
                            /* fallthrough */
                        case 2:
                            text->x98 = 0;
                            sis_cursor += 1;
                            text->sis_buffer = (SIS *)sis_cursor;
                            goto restart;
                        case 3:
                            if (line_started == 0U) {
                                line_height_out = 32.0F * text->x80.y;
                            }
                            line_started = 0U;
                            text->current_height = ((text->font_size.y * ((text->x80.y * text->x78.y) + line_height_out)) + text->current_height);
                            if (skip_count != 0U) {
                                skip_count -= 1;
                            } else {
                                text->x98 = (u32) (text->x98 + 1);
                                text->x94 = (u32) char_delay;
                                text->x60 = (void *) (sis_cursor + 1);
                            }
                            break;
                        case 4:
                            if (skip_count != 0U) {
                                skip_count -= 1;
                            } else {
                                text->x98 = (u32) (text->x98 + 1);
                                text->x4B = 1U;
                                text->x60 = (void *) (sis_cursor + 1);
                            }
                            break;
                        case 5:
                            if (skip_count != 0U) {
                                skip_count -= 1;
                            } else {
                                text->x98 = (u32) (text->x98 + 1);
                                text->x94 = *(u16*) (sis_cursor + 1);
                                text->x60 = (void *) (sis_cursor + 3);
                            }
                            sis_cursor += 2;
                            break;
                        case 6:
                            line_delay = *(u16*) (sis_cursor + 1);
                            char_delay = *(u16*) (sis_cursor + 3);
                            sis_cursor += 4;
                            break;
                        case 7:
                            line_started = 1U;
                            HSD_SisLib_803A8134((void*) (sis_cursor + 5), text, &line_width_out, &line_height_out);
                            x_origin = (f32) *(s16*) (sis_cursor + 1);
                            if (( text->fitting == 1) && (text->box_size_x < line_width_out)) {
                                text->x88 = (text->box_size_x / line_width_out);
                            } else {
                                text->x88 = 1.0F;
                            }
                            switch ((s32) text->alignment) {
                            case 1:
                                text->current_width = (f32) -((0.5F * (line_width_out * text->x88)) - x_origin);
                                break;
                            case 2:
                                text->current_width = (-((line_width_out * text->x88) - x_origin));
                                break;
                            default:
                                text->current_width = x_origin;
                                break;
                            }
                            y_offset = *(s16*) (sis_cursor + 3);
                            sis_cursor += 4;
                            text->current_height = ((f32) y_offset * text->font_size.y);
                            break;
                        case 9:
                            HSD_SisLib_803A7684(text, sis_cursor, 5U);
                            /* fallthrough */
                        case 8:
                            sis_cursor = (u8*) *(s32*) (sis_cursor + 1) - 1;
                            break;
                        case 10:
                            if (((u32) text->alloc_data == 0U) || (saved_kerning == 0)) {
                                HSD_SisLib_803A7684(text, sis_cursor, 1U);
                                text->x78.x = (f32) *(s16*) (sis_cursor + 1) / 256.0F;
                                text->x78.y = (f32) *(s16*) (sis_cursor + 3) / 256.0F;
                            }
                            sis_cursor += 4;
                            break;
                        case 11:
                            if (((u32) text->alloc_data == 0U) || (saved_kerning == 0)) {
                                HSD_SisLib_803A7F0C(text, 1);
                            }
                            break;
                        case 12:
                            HSD_SisLib_803A7684(text, sis_cursor, 2U);
                            text->active_color.r = sis_cursor[1];
                            text->active_color.g = sis_cursor[2];
                            text->active_color.b = sis_cursor[3];
                            sis_cursor += 3;
                            break;
                        case 13:
                            HSD_SisLib_803A7F0C(text, 2);
                            break;
                        case 14:
                            HSD_SisLib_803A7684(text, sis_cursor, 3U);
                            text->x80.x = (f32) *(u16*) (sis_cursor + 1) / 256.0F;
                            text->x80.y = (f32) *(u16*) (sis_cursor + 3) / 256.0F;
                            sis_cursor += 4;
                            break;
                        case 15:
                            HSD_SisLib_803A7F0C(text, 3);
                            break;
                        case 16:
                            HSD_SisLib_803A7684(text, sis_cursor, 4U);
                            text->alignment = 1U;
                            break;
                        case 18:
                            HSD_SisLib_803A7684(text, sis_cursor, 4U);
                            text->alignment = 0U;
                            break;
                        case 20:
                            HSD_SisLib_803A7684(text, sis_cursor, 4U);
                            text->alignment = 2U;
                            break;
                        case 17:
                        case 19:
                        case 21:
                            HSD_SisLib_803A7F0C(text, 4);
                            break;
                        case 22:
                            text->kerning = 1U;
                            break;
                        case 23:
                            text->kerning = 0U;
                            break;
                        case 24:
                            text->fitting = 1U;
                            break;
                        case 25:
                            text->fitting = 0U;
                            break;
                        case 26:
                            if (line_started == 0U) {
                                f32 measured_width;

                                line_started += 1;
                                HSD_SisLib_803A8134(sis_cursor, text, &line_width_out, &line_height_out);
                                measured_width = line_width_out;
                                sisFitLineToBox(text, measured_width);
                            }
                            text->current_width = (f32) (((f64) text->x88 * ((f64) text->x80.x *
                                            (half_glyph + (f64) text->x78.x))) + (f64) text->current_width);
                            if (skip_count != 0U) {
                                skip_count -= 1;
                            } else {
                                text->x98 = (u32) (text->x98 + 1);
                                text->x94 = (u32) line_delay;
                                text->x60 = (void *) (sis_cursor + 1);
                            }
                            break;
                        default:
                            if (opcode >= 0x20U) {
                                u16 glyph_idx;
                                s32 tex_offset;
                                f32 glyph_x;
                                f32 scale_x;
                                if (line_started == 0U) {
                                    f32 measured_width;

                                    line_started += 1;
                                    HSD_SisLib_803A8134(sis_cursor, text, &line_width_out, &line_height_out);
                                    measured_width = line_width_out;
                                    sisFitLineToBox(text, measured_width);
                                }
                                glyph_idx = *(u16 *)sis_cursor;
                                if (glyph_idx < 0x4000U) {
                                    tex_offset = glyph_idx - 0x2000;
                                } else {
                                    tex_offset = glyph_idx - 0x4000;
                                }
                                glyph_x = (text->current_width * text->font_size.x) + text->pos_x;
                                scale_x = text->font_size.x;
                                if ( text->kerning != 0) {
                                    if (glyph_idx < 0x4000U) {
                                        glyph_x = -((scale_x * (text->x80.x * (f32) (default_kerning[(tex_offset * 2) & 0x1FFFE] - 1))) - glyph_x);
                                    } else {
                                        glyph_x = -((scale_x * (text->x80.x * (f32) (textures->data[(tex_offset * 2) & 0x1FFFE] - 1))) - glyph_x);
                                    }
                                }
                                {
                                    f32 scale_y = text->font_size.y;
                                    f32 glyph_size = 32.0F * text->x80.y;
                                    f32 uv_top = 0.0F;
                                    f32 glyph_w = HSD_SisLib_GlyphWidth(text, scale_x);
                                    f32 quad_right = (text->x88 * glyph_w) + glyph_x;
                                    f32 glyph_y = (scale_y * (line_height_out - glyph_size)) + (text->pos_y + text->current_height);
                                    f32 glyph_h = glyph_size * scale_y;
                                    f32 uv_bottom = 1.0F;
                                    f32 uv_left = 0.0F;
                                    f32 quad_top;
                                    f32 uv_right;
                                    f32 quad_bottom;

                                    quad_top = glyph_y;
                                    uv_right = 1.0F;
                                    quad_bottom = glyph_y + glyph_h;
#ifdef MUST_MATCH
                                    (void) (glyph_y = glyph_y);
#endif
                                    if ( text->x4E != 0) {
                                        if ((min_x > quad_right) || (max_x < glyph_x) || (min_y > quad_bottom) || (max_y < quad_top)) {
                                            goto glyph_draw_done;
                                        }
                                        if (min_x > glyph_x) {
                                            f32 clip_left = min_x - glyph_x;
                                            uv_left = clip_left / glyph_w;
                                            glyph_x += clip_left;
                                        }
                                        if (max_x < quad_right) {
                                            f32 clip_right = quad_right - max_x;
                                            uv_right = 1.0F - (clip_right / glyph_w);
                                            quad_right -= clip_right;
                                        }
                                        if (min_y > quad_top) {
                                            f32 clip_top = min_y - quad_top;
                                            uv_top = clip_top / glyph_h;
                                            quad_top += clip_top;
                                        }
                                        if (max_y < quad_bottom) {
                                            f32 clip_bottom = quad_bottom - max_y;
                                            uv_bottom = 1.0F - (clip_bottom / glyph_h);
                                            quad_bottom -= clip_bottom;
                                        }
                                    }
                                    {
                                        if (glyph_idx < 0x4000U) {
                                            GXInitTexObj(&tex_obj, data + ((tex_offset << 9) & 0x01FFFE00), 0x20U, 0x20U, GX_TF_I4, GX_CLAMP, GX_CLAMP, 0U);
                                        } else {
                                            GXInitTexObj(&tex_obj, HSD_SisLib_BytePtr(kerning) + ((tex_offset << 9) & 0x01FFFE00), 0x20U, 0x20U, GX_TF_I4, GX_CLAMP, GX_CLAMP, 0U);
                                        }
                                        GXLoadTexObj(&tex_obj, GX_TEXMAP0);
                                        GXSetTevColor(GX_TEVREG0, *(&text->active_color));
                                        GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
                                        {
                                            f32 glyph_depth = text->pos_z;
                                            f32 neg_quad_top = -quad_top;
                                            f32 neg_quad_bottom = -quad_bottom;
                                            GXPosition3f32(glyph_x, neg_quad_top, glyph_depth);
                                            GXTexCoord2f32(uv_left, uv_top);
                                            GXPosition3f32(quad_right, neg_quad_top, glyph_depth);
                                            GXTexCoord2f32(uv_right, uv_top);
                                            GXPosition3f32(quad_right, neg_quad_bottom, glyph_depth);
                                            GXTexCoord2f32(uv_right, uv_bottom);
                                            GXPosition3f32(glyph_x, neg_quad_bottom, glyph_depth);
                                            GXTexCoord2f32(uv_left, uv_bottom);
                                        }
                                        GXEnd();
                                    }
                                glyph_draw_done:
                                    text->current_width = (f32) ((text->x88 * (text->x80.x * (32.0F + text->x78.x))) + text->current_width);
                                    if ( text->kerning != 0) {
                                        if (glyph_idx < 0x4000U) {
                                            u8 *kern_pair = &default_kerning[(tex_offset * 2) & 0x1FFFE];
                                            tex_offset = (clear_idx = kern_pair[1] - 2);
                                            text->current_width = (-((text->x88 * (text->x80.x * (f32) (kern_pair[0] + tex_offset))) - text->current_width));
                                        } else {
                                            u8 *kern_pair = &textures->data[(tex_offset * 2) & 0x1FFFE];
                                            tex_offset = (clear_idx = kern_pair[1] - 2);
                                            text->current_width = (-((text->x88 * (text->x80.x * (f32) (kern_pair[0] + tex_offset))) - text->current_width));
                                        }
                                    }
                                    if (skip_count != 0U) {
                                        skip_count -= 1;
                                    } else {
                                        text->x98 = (u32) (text->x98 + 1);
                                        text->x94 = (u32) line_delay;
                                        text->x60 = (void *) (sis_cursor + 2);
                                    }
                                    sis_cursor += 1;
                            }
                        }
                    }
                }
                sis_cursor++;
            }
        render_done:
            HSD_StateInvalidate(-1);
            text->active_color.r = saved_color_r;
            text->active_color.g = saved_color_g;
            text->active_color.b = saved_color_b;
            text->x80.x = saved_font_size_x;
            text->x80.y = saved_font_size_y;
            text->x78.x = saved_scale_x;
            text->x78.y = saved_scale_y;
            text->alignment = saved_alignment;
            text->kerning = saved_kerning;
            text->fitting = saved_fitting;
            text->x6C = saved_x6C;
            {
                s32 clear_i = text->x6C;
                while ( clear_i < (s32) text->x6E) {
                    *(text->string_buffer + clear_i) = 0;
                    clear_i += 1;
                }
            }
        }
    }
    // clang-format on
}

HSD_Archive* HSD_SisLib_803A945C(char* path)
{
    return lbArchive_LoadArchive(path);
}

void HSD_SisLib_803A947C(HSD_Archive* archive)
{
    lbArchive_80016EFC(archive);
}

u8 HSD_SisLib_8040C680[0x240] = {
    0x20, 0xE3, 0x20, 0xEC, 0x20, 0xF4, 0x21, 0x04, 0x21, 0x02, 0x21, 0x03,
    0x21, 0x05, 0x20, 0xF3, 0x20, 0xF5, 0x20, 0xF6, 0x21, 0x06, 0x20, 0xFB,
    0x20, 0xE6, 0x20, 0xFC, 0x20, 0xE7, 0x20, 0xF0, 0x20, 0x00, 0x20, 0x01,
    0x20, 0x02, 0x20, 0x03, 0x20, 0x04, 0x20, 0x05, 0x20, 0x06, 0x20, 0x07,
    0x20, 0x08, 0x20, 0x09, 0x20, 0xE9, 0x20, 0xEA, 0x20, 0xFF, 0x20, 0xFE,
    0x21, 0x00, 0x20, 0xEB, 0x21, 0x07, 0x20, 0x0A, 0x20, 0x0B, 0x20, 0x0C,
    0x20, 0x0D, 0x20, 0x0E, 0x20, 0x0F, 0x20, 0x10, 0x20, 0x11, 0x20, 0x12,
    0x20, 0x13, 0x20, 0x14, 0x20, 0x15, 0x20, 0x16, 0x20, 0x17, 0x20, 0x18,
    0x20, 0x19, 0x20, 0x1A, 0x20, 0x1B, 0x20, 0x1C, 0x20, 0x1D, 0x20, 0x1E,
    0x20, 0x1F, 0x20, 0x20, 0x20, 0x21, 0x20, 0x22, 0x20, 0x23, 0x20, 0xF7,
    0x21, 0x01, 0x20, 0xF8, 0x20, 0xED, 0x20, 0xEE, 0x20, 0x24, 0x20, 0x25,
    0x20, 0x26, 0x20, 0x27, 0x20, 0x28, 0x20, 0x29, 0x20, 0x2A, 0x20, 0x2B,
    0x20, 0x2C, 0x20, 0x2D, 0x20, 0x2E, 0x20, 0x2F, 0x20, 0x30, 0x20, 0x31,
    0x20, 0x32, 0x20, 0x33, 0x20, 0x34, 0x20, 0x35, 0x20, 0x36, 0x20, 0x37,
    0x20, 0x38, 0x20, 0x39, 0x20, 0x3A, 0x20, 0x3B, 0x20, 0x3C, 0x20, 0x3D,
    0x20, 0xF9, 0x20, 0xF2, 0x20, 0xFA, 0x20, 0xF1, 0x20, 0x3E, 0x20, 0x3F,
    0x20, 0x40, 0x20, 0x41, 0x20, 0x42, 0x20, 0x43, 0x20, 0x44, 0x20, 0x45,
    0x20, 0x46, 0x20, 0x47, 0x20, 0x48, 0x20, 0x49, 0x20, 0x4A, 0x20, 0x4B,
    0x20, 0x4C, 0x20, 0x4D, 0x20, 0x4E, 0x20, 0x4F, 0x20, 0x50, 0x20, 0x51,
    0x20, 0x52, 0x20, 0x53, 0x20, 0x54, 0x20, 0x55, 0x20, 0x56, 0x20, 0x57,
    0x20, 0x58, 0x20, 0x59, 0x20, 0x5A, 0x20, 0x5B, 0x20, 0x5C, 0x20, 0x5D,
    0x20, 0x5E, 0x20, 0x5F, 0x20, 0x60, 0x20, 0x61, 0x20, 0x62, 0x20, 0x63,
    0x20, 0x64, 0x20, 0x65, 0x20, 0x66, 0x20, 0x67, 0x20, 0x68, 0x20, 0x69,
    0x20, 0x6A, 0x20, 0x6B, 0x20, 0x6C, 0x20, 0x6D, 0x20, 0x6E, 0x20, 0x6F,
    0x20, 0x70, 0x20, 0x71, 0x20, 0x72, 0x20, 0x73, 0x20, 0x74, 0x20, 0x75,
    0x20, 0x76, 0x20, 0x77, 0x20, 0x78, 0x20, 0x79, 0x20, 0x7A, 0x20, 0x7B,
    0x20, 0x7C, 0x20, 0x7D, 0x20, 0x7E, 0x20, 0x7F, 0x20, 0x80, 0x20, 0x81,
    0x20, 0x82, 0x20, 0x83, 0x20, 0x84, 0x20, 0x85, 0x20, 0x86, 0x20, 0x87,
    0x20, 0x88, 0x20, 0x89, 0x20, 0x8A, 0x20, 0x8B, 0x20, 0x8C, 0x20, 0x8D,
    0x20, 0x8E, 0x20, 0x8F, 0x20, 0x90, 0x20, 0x91, 0x20, 0x92, 0x20, 0x93,
    0x20, 0x94, 0x20, 0x95, 0x20, 0x96, 0x20, 0x97, 0x20, 0x98, 0x20, 0x99,
    0x20, 0x9A, 0x20, 0x9B, 0x20, 0x9C, 0x20, 0x9D, 0x20, 0x9E, 0x20, 0x9F,
    0x20, 0xA0, 0x20, 0xA1, 0x20, 0xA2, 0x20, 0xA3, 0x20, 0xA4, 0x20, 0xA5,
    0x20, 0xA6, 0x20, 0xA7, 0x20, 0xA8, 0x20, 0xA9, 0x20, 0xAA, 0x20, 0xAB,
    0x20, 0xAC, 0x20, 0xAD, 0x20, 0xAE, 0x20, 0xAF, 0x20, 0xB0, 0x20, 0xB1,
    0x20, 0xB2, 0x20, 0xB3, 0x20, 0xB4, 0x20, 0xB5, 0x20, 0xB6, 0x20, 0xB7,
    0x20, 0xB8, 0x20, 0xB9, 0x20, 0xBA, 0x20, 0xBB, 0x20, 0xBC, 0x20, 0xBD,
    0x20, 0xBE, 0x20, 0xBF, 0x20, 0xC0, 0x20, 0xC1, 0x20, 0xC2, 0x20, 0xC3,
    0x20, 0xC4, 0x20, 0xC5, 0x20, 0xC6, 0x20, 0xC7, 0x20, 0xC8, 0x20, 0xC9,
    0x20, 0xCA, 0x20, 0xCB, 0x20, 0xCC, 0x20, 0xCD, 0x20, 0xCE, 0x20, 0xCF,
    0x20, 0xD0, 0x20, 0xD1, 0x20, 0xD2, 0x20, 0xD3, 0x20, 0xD4, 0x20, 0xD5,
    0x20, 0xD6, 0x20, 0xD7, 0x20, 0xD8, 0x20, 0xD9, 0x20, 0xDA, 0x20, 0xDB,
    0x20, 0xDC, 0x20, 0xDD, 0x20, 0xDE, 0x20, 0xDF, 0x20, 0xE0, 0x20, 0xE1,
    0x20, 0xE2, 0x20, 0xE4, 0x20, 0xE5, 0x20, 0xEF, 0x20, 0xE8, 0x20, 0xFD,
    0x21, 0x0A, 0x21, 0x17, 0x21, 0x13, 0x21, 0x1B, 0x21, 0x0C, 0x21, 0x1C,
    0x21, 0x19, 0x21, 0x1D, 0x21, 0x16, 0x21, 0x10, 0x21, 0x08, 0x21, 0x15,
    0x21, 0x1E, 0x21, 0x11, 0x21, 0x12, 0x21, 0x09, 0x21, 0x18, 0x21, 0x0B,
    0x21, 0x0E, 0x21, 0x0F, 0x21, 0x1A, 0x21, 0x14, 0x21, 0x0D, 0x00, 0x00,
};

u8 lbl_8040C8C0[0x240] = {
    0x81, 0x40, 0x81, 0x49, 0x81, 0x68, 0x81, 0x94, 0x81, 0x90, 0x81, 0x93,
    0x81, 0x95, 0x81, 0x66, 0x81, 0x69, 0x81, 0x6A, 0x81, 0x96, 0x81, 0x7B,
    0x81, 0x43, 0x81, 0x7C, 0x81, 0x44, 0x81, 0x5E, 0x82, 0x4F, 0x82, 0x50,
    0x82, 0x51, 0x82, 0x52, 0x82, 0x53, 0x82, 0x54, 0x82, 0x55, 0x82, 0x56,
    0x82, 0x57, 0x82, 0x58, 0x81, 0x46, 0x81, 0x47, 0x81, 0x83, 0x81, 0x81,
    0x81, 0x84, 0x81, 0x48, 0x81, 0x97, 0x82, 0x60, 0x82, 0x61, 0x82, 0x62,
    0x82, 0x63, 0x82, 0x64, 0x82, 0x65, 0x82, 0x66, 0x82, 0x67, 0x82, 0x68,
    0x82, 0x69, 0x82, 0x6A, 0x82, 0x6B, 0x82, 0x6C, 0x82, 0x6D, 0x82, 0x6E,
    0x82, 0x6F, 0x82, 0x70, 0x82, 0x71, 0x82, 0x72, 0x82, 0x73, 0x82, 0x74,
    0x82, 0x75, 0x82, 0x76, 0x82, 0x77, 0x82, 0x78, 0x82, 0x79, 0x81, 0x6D,
    0x81, 0x8F, 0x81, 0x6E, 0x81, 0x4F, 0x81, 0x51, 0x82, 0x81, 0x82, 0x82,
    0x82, 0x83, 0x82, 0x84, 0x82, 0x85, 0x82, 0x86, 0x82, 0x87, 0x82, 0x88,
    0x82, 0x89, 0x82, 0x8A, 0x82, 0x8B, 0x82, 0x8C, 0x82, 0x8D, 0x82, 0x8E,
    0x82, 0x8F, 0x82, 0x90, 0x82, 0x91, 0x82, 0x92, 0x82, 0x93, 0x82, 0x94,
    0x82, 0x95, 0x82, 0x96, 0x82, 0x97, 0x82, 0x98, 0x82, 0x99, 0x82, 0x9A,
    0x81, 0x6F, 0x81, 0x62, 0x81, 0x70, 0x81, 0x60, 0x82, 0x9F, 0x82, 0xA0,
    0x82, 0xA1, 0x82, 0xA2, 0x82, 0xA3, 0x82, 0xA4, 0x82, 0xA5, 0x82, 0xA6,
    0x82, 0xA7, 0x82, 0xA8, 0x82, 0xA9, 0x82, 0xAA, 0x82, 0xAB, 0x82, 0xAC,
    0x82, 0xAD, 0x82, 0xAE, 0x82, 0xAF, 0x82, 0xB0, 0x82, 0xB1, 0x82, 0xB2,
    0x82, 0xB3, 0x82, 0xB4, 0x82, 0xB5, 0x82, 0xB6, 0x82, 0xB7, 0x82, 0xB8,
    0x82, 0xB9, 0x82, 0xBA, 0x82, 0xBB, 0x82, 0xBC, 0x82, 0xBD, 0x82, 0xBE,
    0x82, 0xBF, 0x82, 0xC0, 0x82, 0xC1, 0x82, 0xC2, 0x82, 0xC3, 0x82, 0xC4,
    0x82, 0xC5, 0x82, 0xC6, 0x82, 0xC7, 0x82, 0xC8, 0x82, 0xC9, 0x82, 0xCA,
    0x82, 0xCB, 0x82, 0xCC, 0x82, 0xCD, 0x82, 0xCE, 0x82, 0xCF, 0x82, 0xD0,
    0x82, 0xD1, 0x82, 0xD2, 0x82, 0xD3, 0x82, 0xD4, 0x82, 0xD5, 0x82, 0xD6,
    0x82, 0xD7, 0x82, 0xD8, 0x82, 0xD9, 0x82, 0xDA, 0x82, 0xDB, 0x82, 0xDC,
    0x82, 0xDD, 0x82, 0xDE, 0x82, 0xDF, 0x82, 0xE0, 0x82, 0xE1, 0x82, 0xE2,
    0x82, 0xE3, 0x82, 0xE4, 0x82, 0xE5, 0x82, 0xE6, 0x82, 0xE7, 0x82, 0xE8,
    0x82, 0xE9, 0x82, 0xEA, 0x82, 0xEB, 0x82, 0xEC, 0x82, 0xED, 0x82, 0xF0,
    0x82, 0xF1, 0x83, 0x40, 0x83, 0x41, 0x83, 0x42, 0x83, 0x43, 0x83, 0x44,
    0x83, 0x45, 0x83, 0x46, 0x83, 0x47, 0x83, 0x48, 0x83, 0x49, 0x83, 0x4A,
    0x83, 0x4B, 0x83, 0x4C, 0x83, 0x4D, 0x83, 0x4E, 0x83, 0x4F, 0x83, 0x50,
    0x83, 0x51, 0x83, 0x52, 0x83, 0x53, 0x83, 0x54, 0x83, 0x55, 0x83, 0x56,
    0x83, 0x57, 0x83, 0x58, 0x83, 0x59, 0x83, 0x5A, 0x83, 0x5B, 0x83, 0x5C,
    0x83, 0x5D, 0x83, 0x5E, 0x83, 0x5F, 0x83, 0x60, 0x83, 0x61, 0x83, 0x62,
    0x83, 0x63, 0x83, 0x64, 0x83, 0x65, 0x83, 0x66, 0x83, 0x67, 0x83, 0x68,
    0x83, 0x69, 0x83, 0x6A, 0x83, 0x6B, 0x83, 0x6C, 0x83, 0x6D, 0x83, 0x6E,
    0x83, 0x6F, 0x83, 0x70, 0x83, 0x71, 0x83, 0x72, 0x83, 0x73, 0x83, 0x74,
    0x83, 0x75, 0x83, 0x76, 0x83, 0x77, 0x83, 0x78, 0x83, 0x79, 0x83, 0x7A,
    0x83, 0x7B, 0x83, 0x7C, 0x83, 0x7D, 0x83, 0x7E, 0x83, 0x80, 0x83, 0x81,
    0x83, 0x82, 0x83, 0x83, 0x83, 0x84, 0x83, 0x85, 0x83, 0x86, 0x83, 0x87,
    0x83, 0x88, 0x83, 0x89, 0x83, 0x8A, 0x83, 0x8B, 0x83, 0x8C, 0x83, 0x8D,
    0x83, 0x8E, 0x83, 0x8F, 0x83, 0x92, 0x83, 0x93, 0x83, 0x94, 0x83, 0x95,
    0x83, 0x96, 0x81, 0x41, 0x81, 0x42, 0x81, 0x5B, 0x81, 0x45, 0x81, 0x7E,
    0x8C, 0x52, 0x92, 0x63, 0x90, 0x6C, 0x94, 0xB2, 0x8C, 0xC2, 0x95, 0xC2,
    0x93, 0xC7, 0x96, 0x7B, 0x91, 0xCC, 0x8E, 0xE6, 0x88, 0xB5, 0x90, 0xE0,
    0x96, 0xBE, 0x8F, 0x91, 0x8F, 0xDA, 0x89, 0x9F, 0x93, 0x64, 0x8C, 0xB9,
    0x8E, 0x77, 0x8E, 0xA6, 0x94, 0xAD, 0x90, 0xB6, 0x8D, 0x9E, 0x00, 0x00,
};

u8 HSD_SisLib_8040CB00[0x240] = {
    0x09, 0x08, 0x09, 0x0C, 0x09, 0x08, 0x08, 0x08, 0x09, 0x08, 0x09, 0x08,
    0x09, 0x08, 0x09, 0x08, 0x09, 0x08, 0x09, 0x08, 0x04, 0x03, 0x06, 0x05,
    0x04, 0x04, 0x05, 0x03, 0x08, 0x06, 0x08, 0x06, 0x04, 0x03, 0x05, 0x03,
    0x0D, 0x0B, 0x07, 0x06, 0x06, 0x04, 0x08, 0x06, 0x03, 0x01, 0x04, 0x03,
    0x04, 0x03, 0x06, 0x04, 0x04, 0x02, 0x06, 0x04, 0x05, 0x04, 0x06, 0x05,
    0x05, 0x03, 0x04, 0x03, 0x01, 0x00, 0x05, 0x04, 0x04, 0x03, 0x05, 0x04,
    0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x08, 0x09,
    0x07, 0x06, 0x08, 0x07, 0x0A, 0x0A, 0x09, 0x0C, 0x08, 0x06, 0x0C, 0x0C,
    0x01, 0x00, 0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x0A, 0x09,
    0x08, 0x07, 0x08, 0x09, 0x07, 0x05, 0x07, 0x06, 0x02, 0x01, 0x07, 0x06,
    0x06, 0x06, 0x07, 0x06, 0x05, 0x05, 0x03, 0x02, 0x05, 0x05, 0x03, 0x02,
    0x06, 0x06, 0x04, 0x04, 0x06, 0x05, 0x03, 0x02, 0x05, 0x03, 0x02, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x00, 0x04, 0x05, 0x04, 0x03,
    0x02, 0x02, 0x02, 0x00, 0x04, 0x04, 0x03, 0x00, 0x04, 0x03, 0x03, 0x00,
    0x05, 0x03, 0x05, 0x03, 0x02, 0x02, 0x02, 0x00, 0x02, 0x02, 0x01, 0x00,
    0x02, 0x02, 0x01, 0x00, 0x02, 0x02, 0x02, 0x00, 0x03, 0x03, 0x03, 0x00,
    0x04, 0x05, 0x01, 0x02, 0x01, 0x00, 0x02, 0x02, 0x02, 0x00, 0x04, 0x04,
    0x03, 0x00, 0x01, 0x01, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x02, 0x01, 0x02, 0x00, 0x02, 0x00, 0x02, 0x01, 0x02, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x02, 0x01, 0x01, 0x00, 0x01, 0x00, 0x03, 0x03, 0x01, 0x01, 0x02, 0x01,
    0x02, 0x02, 0x03, 0x02, 0x04, 0x04, 0x01, 0x01, 0x05, 0x05, 0x02, 0x02,
    0x05, 0x05, 0x02, 0x02, 0x03, 0x03, 0x05, 0x05, 0x02, 0x02, 0x01, 0x00,
    0x02, 0x03, 0x04, 0x04, 0x01, 0x01, 0x02, 0x03, 0x01, 0x01, 0x05, 0x04,
    0x03, 0x01, 0x04, 0x06, 0x01, 0x03, 0x06, 0x05, 0x03, 0x02, 0x05, 0x04,
    0x02, 0x02, 0x04, 0x05, 0x02, 0x01, 0x02, 0x02, 0x02, 0x00, 0x02, 0x02,
    0x01, 0x00, 0x03, 0x02, 0x02, 0x00, 0x01, 0x01, 0x01, 0x00, 0x03, 0x04,
    0x02, 0x00, 0x02, 0x02, 0x01, 0x00, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01,
    0x02, 0x00, 0x02, 0x02, 0x02, 0x00, 0x02, 0x03, 0x01, 0x00, 0x03, 0x02,
    0x02, 0x00, 0x02, 0x02, 0x02, 0x00, 0x05, 0x05, 0x02, 0x02, 0x01, 0x00,
    0x02, 0x02, 0x01, 0x00, 0x09, 0x03, 0x09, 0x02, 0x02, 0x02, 0x01, 0x01,
    0x02, 0x02, 0x03, 0x02, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x04, 0x00, 0x04, 0x02, 0x04, 0x03, 0x03, 0x00, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x02, 0x02, 0x04, 0x04, 0x01, 0x01, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04,
    0x02, 0x01, 0x05, 0x05, 0x02, 0x02, 0x06, 0x06, 0x03, 0x04, 0x03, 0x03,
    0x05, 0x05, 0x01, 0x01, 0x05, 0x03, 0x03, 0x03, 0x06, 0x06, 0x03, 0x03,
    0x04, 0x03, 0x02, 0x02, 0x03, 0x00, 0x04, 0x05, 0x04, 0x00, 0x08, 0x08,
    0x02, 0x12, 0x02, 0x13, 0x0C, 0x0D, 0x0C, 0x0D, 0x0B, 0x0A, 0x0D, 0x0C,
    0x0D, 0x0C, 0x07, 0x06, 0x0D, 0x0C, 0x0A, 0x08, 0x00, 0x00, 0x02, 0x01,
    0x01, 0x00, 0x01, 0x01, 0x0F, 0x0F, 0x02, 0x17, 0x01, 0x10, 0x15, 0x00,
    0x01, 0x14, 0x15, 0x00, 0x01, 0x13, 0x13, 0x00, 0x01, 0x12, 0x04, 0x03,
    0x04, 0x03, 0x05, 0x04, 0x04, 0x03, 0x01, 0x01, 0x01, 0x00, 0x04, 0x02,
    0x05, 0x05, 0x01, 0x00, 0x04, 0x03, 0x03, 0x02, 0x08, 0x06, 0x03, 0x02,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,
};
