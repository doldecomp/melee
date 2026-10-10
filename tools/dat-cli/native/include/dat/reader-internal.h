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

/// Individual native allocations, released with the archive.
typedef struct DatAllocation {
    struct DatAllocation* next;
    void* data;
} DatAllocation;

struct DatArchive {
    const DatSchema* s;
    DatArchiveData* archive;
    Bits object, script;
    /// (offset, type id) visited, as the walk's `visited`.
    DatMap visited;
    /// (offset, type id) → native object.
    DatMap natives;
    /// Native arrays' allocated element counts.
    DatMap native_counts;
    /// Native pointer slots → (target offset, type id), for array aliases.
    DatMap references;
    /// Serialized extern slot → native address supplied by the game.
    DatMap extern_values;
    uint8_t native_moved;
#ifdef DAT_NATIVE_TESTING
    struct DatValidation* validation;
#endif
    const DatScope* env;
    /// Names the walk treats specially.
    int32_t name_index, name_command;
    DatAllocation* allocations;
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

uint32_t dat_reader_word(const DatArchive* a, uint64_t offset);
uint64_t dat_reader_bytes_at(const DatArchive* a, uint64_t offset,
                             uint32_t size);
const DatType* dat_reader_T(const DatArchive* a, int32_t type);
int32_t dat_reader_resolve(const DatArchive* a, int32_t type);
int32_t dat_reader_pointee(const DatArchive* a, int32_t target);
uint32_t dat_reader_native_size(const DatArchive* a, int32_t type);
uint64_t dat_reader_extend(uint64_t v, uint32_t bits, uint8_t is_signed);
/// Primitive source widths and signedness are literals emitted by Rust.
void dat_reader_integer(const DatArchive* a, uint32_t offset,
                        uint32_t source_size, uint32_t native_size,
                        uint8_t is_signed, void* native);
void dat_reader_float(const DatArchive* a, uint32_t offset,
                      uint32_t source_size, uint32_t native_size,
                      void* native);
uint64_t dat_reader_bits_at(const DatArchive* a, uint64_t offset,
                            uint64_t start, uint32_t bits);
void dat_reader_store_pointer(void* slot, const void* p);
/// externs (which the loader leaves null), -1 kept as -1, and anything else
/// as its value.
void dat_reader_store_unrelocated(DatArchive* a, uint32_t offset,
                                  uint32_t value, void* slot);
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
void* dat_reader_native_of(const DatArchive* a, uint32_t offset, int32_t r);
void dat_reader_place_native(DatArchive* a, uint32_t offset, int32_t r,
                             void* native);
void dat_reader_reference(DatArchive* a, void* slot, uint32_t offset,
                          int32_t r);
void dat_reader_unrelocated(DatArchive* a, uint32_t offset, uint32_t value);
void dat_reader_read_object(DatArchive* a, uint32_t offset, int32_t type,
                            const DatScope* env, void* native, void** slot);
const DatScope* dat_reader_bind_scope(DatArchive* a, const DatScope* outer,
                                      DatBinding binding, DatParent parent,
                                      uint64_t index, DatScope* storage);
int dat_reader_fits(const DatArchive* a, uint32_t offset, int32_t type);
int dat_reader_array_count_fits(const DatArchive* a, uint32_t offset,
                                int32_t array, int32_t element,
                                uint64_t count);
void dat_reader_counted(DatArchive* a, uint32_t offset, int32_t pointer,
                        int32_t element, uint64_t count, DatBinding binding,
                        DatScope* storage, DatParent parent, void* slot);
void dat_reader_terminated(DatArchive* a, uint32_t offset, int32_t pointer,
                           void* slot, const DatExpr* terminator,
                           uint32_t length);
uint64_t dat_reader_extent_bound(const DatArchive* a, uint32_t offset,
                                 uint32_t size);
void dat_reader_extent(DatArchive* a, uint32_t offset, int32_t array,
                       DatBinding binding, DatScope* storage, DatParent parent,
                       void* native);
void dat_reader_typed(DatArchive* a, uint32_t offset, int32_t target,
                      void* native, uint32_t native_field);
void dat_reader_script(DatArchive* a, uint32_t offset, int32_t pointer,
                       const DatScript* s, void* slot);
void dat_reader_layout(DatArchive* a, uint32_t offset, int32_t type,
                       void* native, DatParent parent);
int dat_reader_read_field(const DatArchive* a, uint64_t at, uint32_t size,
                          uint8_t floating, uint64_t* out);
#ifdef DAT_NATIVE_TESTING
#include <dat/test-internal.h>
#else
#define dat_test_init(...) ((void) 0)
#define dat_test_close(...) ((void) 0)
#define dat_test_reached(...) ((void) 0)
#define dat_test_count(...) ((void) 0)
#define dat_test_sentinel(...) ((void) 0)
#define dat_reader_mark_pointer(...) ((void) 0)
#define dat_reader_issue(...) ((void) 0)
#define dat_reader_record_extent(...) ((void) 0)
#define dat_reader_typed_extent(...) ((void) 0)
#define dat_reader_untyped(...) ((void) 0)
#define dat_reader_relocated_words(...) ((void) 0)
#define dat_reader_record_choice(...) ((void) 0)
#endif
#endif
