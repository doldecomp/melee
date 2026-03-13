#ifndef MELEE_EF_TYPES_H
#define MELEE_EF_TYPES_H

#include <placeholder.h>

#include "baselib/objalloc.h"
#include "dolphin/mtx.h"

#include "ef/forward.h" // IWYU pragma: export

#include "dolphin/types.h"
#include "sc/types.h"

#include <baselib/forward.h>

struct ef_UnkStruct2 {
    /* +0 */ HSD_JObj* x0;
    /* +0 */ HSD_GObj* x4;
}; /* size = 0x8 */

struct Effect {
    /*  +0 */ ef_UnkStruct2* x0; // Should this really be ef_UnkStruct2*?
    /*  +4 */ HSD_GObj* gobj;
    /*  +8 */ HSD_GObj* parent_gobj;
    /*  +C */ HSD_JObj* xC;
    /* +10 */ efLib_UnkCallback x10;
    /* +14 */ void* x14;
    /* +18 */ Vec3 translate;
    /* +24 */ u16 x24;
    /* +26 */ s8 x26;
    /* +27 */ u8 x27; // specifically a singular bit flag ?
    /* +28 */ u8 x28; // Effect update control (?) in fn_8005BC50
    /* +29 */ u8 x29;
    /* +2A */ s8 x2A;
    /* +2B */ s8 x2B;
}; /* size = 0x2C */

struct EffectDesc {
    /* +0 */ float x0;
    /* +4 */ StaticModelDesc model_desc;
}; /* size = 0x14 */

struct ef_UnkStruct1 {
    /* +0 */ int x0;
    /* +4 */ int x4;
    /* +8 */ int x8;
    /* +C */ int xC;
}; /* size = 0x10 */

/// Same as efAsync_80067980_objalloc_t ??
/// Same size as __va_list struct?
struct ef_UnkStruct3 {
    /* +0 */ ef_UnkStruct3* next; // actually next?
    /* +4 */ u8 eff_type;
    /* +8 */ s32 gfx_id;
    /* +C */ HSD_JObj* xC;
    /* +10 */ Vec3 x10;
    /* +1C */ f32 x1C;
    /* +20 */ f32 x20;
}; /* size = 0x24 */

typedef struct ef_Symbols {
    /* 0x0 */ char* ef_DAT_file;
    /* 0x4 */ char* effDataTable_name;
    /* 0x8 */ void* unk8;
} ef_Symbols; /* size = 0xC */
STATIC_ASSERT(sizeof(ef_Symbols) == 0xC);

struct efAsync_80067980_objalloc_t {
    char pad_0[0x24];
};
STATIC_ASSERT(sizeof(struct efAsync_80067980_objalloc_t) == 0x24);

#endif
