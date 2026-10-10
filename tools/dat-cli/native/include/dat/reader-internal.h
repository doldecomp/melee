/** @file Shared storage and reference operations for generated readers. */
#ifndef DAT_READER_INTERNAL_H
#define DAT_READER_INTERNAL_H
#include <limits.h>
#include <math.h>

#include <dat/archive-data.h>
#include <dat/archive.h>
/// Maximum macro expansion depth, matching the Rust evaluator.
#define MACRO_DEPTH 16
typedef enum DatIssueKind {
    ISSUE_UNRELOCATED_POINTER,
    ISSUE_RELOCATED_SCALAR,
    ISSUE_OUT_OF_BOUNDS,
    ISSUE_AMBIGUOUS_UNION,
    ISSUE_UNKNOWN_COMMAND,
} DatIssueKind;

typedef struct DatIssue {
    uint8_t kind;
    uint32_t at;
    uint32_t value;
} DatIssue;

/// Names bound by a root or `DAT_BIND`.
typedef struct DatScope {
    int32_t name;
    uint64_t value;
    const struct DatScope* outer;
} DatScope;

/// An object to walk: at `offset`, of `type`, with the bindings `env`.
/// Either its native object is already allocated (`native`, an element of
/// an array), or it is allocated when walked and stored to `slot`.
typedef struct DatTask {
    uint32_t offset;
    int32_t type;
    const DatScope* env;
    void* native;
    void** slot;
} DatTask;

/// A native object to copy once every pointer has been stored: an element
/// already walked as another object.
typedef struct DatCopy {
    void* dst;
    const void* src;
    size_t size;
} DatCopy;

typedef struct DatChoice {
    uint32_t offset, id, index;
} DatChoice;

typedef struct DatReached {
    uint32_t offset, id;
} DatReached;

struct DatArchive {
    const DatSchema* s;
    DatArchiveData* archive;
    Bits object, script, pointer;
    /// (offset, type id) visited, as the walk's `visited`.
    DatMap visited;
    /// (offset, type id) → native object.
    DatMap natives;
    /// Native arrays' allocated element counts.
    DatMap native_counts;
    /// Native pointer slots → (target offset, type id), for array aliases.
    DatMap references;
    /// Native object → offset, for dat_verify().
    DatMap offsets;
    /// offset → furthest end.
    DatMap extents;
    DatMap choices;
    /// Counted inline arrays' lengths, for verification after leaving scope.
    DatMap array_counts;
    VEC(DatReached) reached;
    VEC(DatChoice) chosen;
    VEC(DatIssue) issues;
    VEC(DatTask) queue;
    VEC(DatCopy) copies;
    uint8_t native_moved;
    size_t untyped_pointers, sentinels;
    const DatScope* env;
    /// Names the walk treats specially.
    int32_t name_index, name_command;
    DatArena arena;
};

typedef enum DatMode {
    /// `DAT_COUNT`: the record's fields, then bindings.
    MODE_COUNT,
    /// `DAT_IF`: the parent record's fields, then those of the union's
    /// record members, then bindings.
    MODE_IF,
    /// `DAT_BIND`: `_index`, the record's fields, then the bindings outside.
    MODE_BIND,
    /// `DAT_TERMINATED`: bindings.
    MODE_TERMINATOR,
    /// A script's command length: `_command`.
    MODE_SCRIPT,
} DatMode;

typedef struct DatContext {
    DatMode mode;
    /// The record the fields are of, and where it is.
    int32_t record;
    uint32_t base;
    /// MODE_IF: the union.
    int32_t onion;
    uint32_t union_base;
    const DatScope* env;
    uint64_t index, command;
} DatContext;

typedef struct DatParent {
    int32_t record;
    uint32_t base;
    uint8_t some;
} DatParent;

typedef enum DatChoiceKind {
    CHOICE_MEMBER,
    CHOICE_UNUSED,
    CHOICE_AMBIGUOUS,
} DatChoiceKind;

/// Readback state shared by the generated verification callbacks.
typedef struct DatVerify {
    const DatArchive* a;
    FILE* out;
    size_t mismatches;
    DatMap checked;
} DatVerify;

uint32_t dat_reader_word(const DatArchive* a, uint64_t offset);
uint64_t dat_reader_bytes_at(const DatArchive* a, uint64_t offset,
                             uint32_t size);
const DatType* dat_reader_T(const DatArchive* a, int32_t type);
int32_t dat_reader_resolve(const DatArchive* a, int32_t type);
int32_t dat_reader_pointee(const DatArchive* a, int32_t target);
uint32_t dat_reader_native_size(const DatArchive* a, int32_t type);
uint64_t dat_reader_load_uint(const void* src, uint32_t size);
uint64_t dat_reader_extend(uint64_t v, uint32_t bits, uint8_t is_signed);
/// The scalar of type `r` (resolved) at `offset`, written natively.
void dat_reader_convert_scalar(const DatArchive* a, uint32_t offset, int32_t r,
                               void* native);
uint64_t dat_reader_bits_at(const DatArchive* a, uint64_t offset,
                            uint64_t start, uint32_t bits);
void dat_reader_store_pointer(void* slot, const void* p);
/// externs (which the loader leaves null), -1 kept as -1, and anything else
/// as its value.
void* dat_reader_unrelocated_value(const DatArchive* a, uint32_t offset,
                                   uint32_t value);
void dat_reader_convert(DatArchive* a, uint32_t offset, int32_t type,
                        void* native);
int dat_reader_field_value(const DatArchive* a, int32_t record, uint32_t base,
                           int32_t name, uint64_t* out);
int dat_reader_resolve_name(const DatArchive* a, const DatContext* c,
                            int32_t name, uint64_t* out);
int dat_reader_col_anim_command_length(uint64_t command, uint64_t* out);
uint64_t dat_reader_cpu_command_length(uint64_t command);
int dat_reader_it_command_length(uint64_t command, uint64_t* out);
int dat_reader_gx_get_tex_buffer_size(uint16_t width, uint16_t height,
                                      uint32_t format, uint8_t mipmap,
                                      uint8_t max_lod, uint64_t* out);
int dat_reader_eval_at(const DatArchive* a, const DatContext* c,
                       const DatExpr* e, unsigned depth, uint64_t* out);
int dat_reader_eval(const DatArchive* a, const DatContext* c, const DatExpr* e,
                    uint64_t* out);
void dat_reader_issue(DatArchive* a, DatIssueKind kind, uint32_t at,
                      uint32_t value);
void* dat_reader_native_of(const DatArchive* a, uint32_t offset, int32_t r);
void dat_reader_place_native(DatArchive* a, uint32_t offset, int32_t r,
                             void* native);
void dat_reader_reference(DatArchive* a, void* slot, uint32_t offset,
                          int32_t r);
void dat_reader_record_extent(DatArchive* a, uint32_t offset, uint64_t end);
void dat_reader_typed_extent(DatArchive* a, uint32_t offset, int32_t type,
                             uint64_t count);
void dat_reader_untyped(DatArchive* a);
void dat_reader_unrelocated(DatArchive* a, uint32_t offset, uint32_t value);
void dat_reader_push(DatArchive* a, uint32_t offset, int32_t type,
                     const DatScope* env, void* native, void** slot);
const DatScope* dat_reader_bind_scope(DatArchive* a, const DatScope* outer,
                                      DatBinding binding, DatParent parent,
                                      uint64_t index);
int dat_reader_fits(const DatArchive* a, uint32_t offset, int32_t type);
void dat_reader_relocated_words(DatArchive* a, uint32_t start, uint64_t end);
int dat_reader_array_count_fits(const DatArchive* a, uint32_t offset,
                                int32_t array, int32_t element,
                                uint64_t count);
void dat_reader_counted(DatArchive* a, uint32_t offset, int32_t pointer,
                        int32_t element, uint64_t count, DatBinding binding,
                        DatParent parent, void* slot);
void dat_reader_terminated(DatArchive* a, uint32_t offset, int32_t pointer,
                           void* slot, const DatExpr* terminator,
                           uint32_t length);
uint64_t dat_reader_extent_bound(const DatArchive* a, uint32_t offset,
                                 uint32_t size);
void dat_reader_extent(DatArchive* a, uint32_t offset, int32_t array,
                       DatBinding binding, DatParent parent, void* native);
void dat_reader_typed(DatArchive* a, uint32_t offset, int32_t target,
                      void* native, uint32_t native_field);
void dat_reader_script(DatArchive* a, uint32_t offset, int32_t pointer,
                       const DatScript* s, void* slot);
void dat_reader_layout(DatArchive* a, uint32_t offset, int32_t type,
                       void* native, DatParent parent);
const char* dat_reader_type_name(const DatArchive* a, uint32_t id);
void dat_reader_mismatch(DatVerify* v, uint32_t at, const char* what,
                         uint64_t want, uint64_t got);
void dat_reader_verify(DatVerify* v, uint32_t offset, int32_t type,
                       const void* native, int depth);
int dat_reader_read_field(const DatArchive* a, uint64_t at, uint32_t size,
                          uint8_t floating, uint64_t* out);
void dat_reader_record_choice(DatArchive* a, uint32_t offset, int32_t type,
                              uint32_t index);
#endif
