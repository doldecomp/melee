#ifndef MELEE_EF_TYPES_H
#define MELEE_EF_TYPES_H

#include <placeholder.h>

#include "dolphin/mtx.h"
#include "dolphin/types.h"

#include "ef/forward.h" // IWYU pragma: export

#include "sc/types.h"

#include <baselib/forward.h>

// How efAsync_Spawn resolves position and forwards args to efSync_Spawn.
// ATTACH = passes jobj directly (effect tracks the joint).
// POS    = converts jobj to world coords via lb_8000B1CC (effect at fixed pos).
// OFFSET = Vec3 offset applied during world-pos calculation.
// PARAM  = extra float(s) forwarded to efSync_Spawn after the position arg.
typedef enum EF_SpawnKind {
    EF_SPAWN_ATTACH             = 0, // (jobj)                 -> efSync(gfx_id, gobj, jobj)
    EF_SPAWN_POS                = 1, // (jobj)                 -> worldpos(jobj)                   -> efSync(gfx_id, gobj, &pos)
    EF_SPAWN_POS_OFFSET         = 2, // (jobj, &ofs)           -> worldpos(jobj, &ofs)             -> efSync(gfx_id, gobj, &pos)
    EF_SPAWN_ATTACH_PARAM       = 3, // (jobj, &f)             -> efSync(gfx_id, gobj, jobj, &f)
    EF_SPAWN_POS_PARAM          = 4, // (jobj, &f)             -> worldpos(jobj)                   -> efSync(gfx_id, gobj, &pos, &f)
    EF_SPAWN_POS_OFFSET_PARAM   = 5, // (jobj, &ofs, &f)       -> worldpos(jobj, &ofs)             -> efSync(..., &pos, &f)
    EF_SPAWN_POS_OFFSET_PARAM2  = 6, // (jobj, &ofs, &f1, &f2) -> worldpos(jobj, &ofs)             -> efSync(..., &f1, &f2)
    EF_SPAWN_ATTACH_OFFSET      = 7, // (jobj, &vec)           -> efSync(gfx_id, gobj, jobj, &vec)
    EF_SPAWN_CAMERA_SHAKE       = 8, // (jobj, &ofs)           -> worldpos(jobj, &ofs)             -> Camera_80030E44(gfx_id, &pos)
} EF_SpawnKind;

// 0 = async load (default)
// 1 = sync load
#define EF_LOADKIND_ASYNC 0
#define EF_LOADKIND_SYNC  1

// EF_Effect: scale_flags
#define EF_SCALE_NO_INHERIT 0x00
#define EF_SCALE_INHERIT    0x01

// EF_Effect: expire_flags
#define EF_DOES_NOT_EXPIRE 0x00
#define EF_DOES_EXPIRE     0x01

// EF_Effect: state_flags
#define EF_STATE_ACTIVE         0x00
#define EF_STATE_ENTERING_PAUSE 0x01
#define EF_STATE_PAUSED         0x02
#define EF_STATE_ASYNC          0x80

struct EF_Effect {
    /*  +0 */ EF_Effect* next;
    /*  +4 */ HSD_GObj* gobj;
    /*  +8 */ HSD_GObj* parent_gobj;
    /*  +C */ HSD_JObj* attach_jobj;
    /* +10 */ EF_UpdateFn update;
    /* +14 */ void* user_data;
    /* +18 */ Vec3 params; // callback parameters, usage depends per-callback
    /* +24 */ u16 lifetime;
    /* +26 */ s8 expire_flags;
    /* +27 */ u8 scale_flags;
    /* +28 */ u8 state_flags;
    /* +29 */ u8 is_async;
    /* +2A */ s8 x2A;
    /* +2B */ s8 x2B;
}; /* size = 0x2C */

struct EF_EffectDesc {
    /* +0 */ float lifetime;
    /* +4 */ StaticModelDesc model_desc;
}; /* size = 0x14 */

struct EF_QueuedEffect {
    /* +0 */ EF_QueuedEffect* next;
    /* +4 */ u8 spawn_kind; // EF_SpawnKind
    /* +8 */ s32 gfx_id;
    /* +C */ HSD_JObj* jobj;
    /* +10 */ Vec3 params; // parameters depending on spawn_kind
    /* +1C */ f32 extra1;  // forwarded to efSync_Spawn depending on spawn_kind
    /* +20 */ f32 extra2;  // second extra float used depending on spawn_kind
}; /* size = 0x24 */

typedef struct EF_DAT_Entry {
    /* 0x0 */ char* ef_DAT_file;  // ex. "EfCoData.dat"
    /* 0x4 */ char* effDataTable_name;   // ex. "effCommonDataTable"
    /* 0x8 */ void* data;          // loaded data pointer
} EF_DAT_Entry; /* size = 0xC */
STATIC_ASSERT(sizeof(EF_DAT_Entry) == 0xC);

struct EF_QueuedEffect_ObjAlloc {
    char pad_0[0x24];
};
STATIC_ASSERT(sizeof(struct EF_QueuedEffect_ObjAlloc) == 0x24);

#endif
