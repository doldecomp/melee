/** @file Bookkeeping used only by the native validation build. */
#ifndef DAT_TEST_INTERNAL_H
#define DAT_TEST_INTERNAL_H
#include <dat/test.h>
/// A growable array of `T`.
#define VEC(T)                                                                \
    struct {                                                                  \
        T* items;                                                             \
        size_t len, cap;                                                      \
    }

#define VEC_PUSH(v, item)                                                     \
    do {                                                                      \
        if ((v).len == (v).cap) {                                             \
            (v).cap = (v).cap ? (v).cap * 2 : 16;                             \
            (v).items = realloc((v).items, (v).cap * sizeof(*(v).items));     \
            if ((v).items == NULL) {                                          \
                abort();                                                      \
            }                                                                 \
        }                                                                     \
        (v).items[(v).len++] = (item);                                        \
    } while (0)

typedef struct DatIssue {
    uint8_t kind;
    uint32_t at;
    uint32_t value;
} DatIssue;

typedef struct DatChoice {
    uint32_t offset, id, index;
} DatChoice;

typedef struct DatReached {
    uint32_t offset, id;
} DatReached;

typedef struct DatValidation {
    Bits pointer;
    DatMap extents, choices, array_counts, reached_seen;
    VEC(DatReached) reached;
    VEC(DatChoice) chosen;
    VEC(DatIssue) issues;
    size_t untyped_pointers, sentinels;
} DatValidation;
/// Readback state shared by the generated verification callbacks.
typedef struct DatVerify {
    const DatArchive* a;
    FILE* out;
    size_t mismatches;
    DatMap checked, offsets;
} DatVerify;

uint64_t dat_reader_load_uint(const void* src, uint32_t size);
void dat_test_init(DatArchive* a);
void dat_test_close(DatArchive* a);
void dat_test_reached(DatArchive* a, uint32_t offset, int32_t r);
void dat_test_count(DatArchive* a, uint32_t offset, int32_t type,
                    uint64_t count);
void dat_test_sentinel(DatArchive* a);
void dat_reader_mark_pointer(DatArchive* a, uint32_t offset, uint32_t size);
void dat_reader_issue(DatArchive* a, DatIssueKind kind, uint32_t at,
                      uint32_t value);
void dat_reader_record_extent(DatArchive* a, uint32_t offset, uint64_t end);
void dat_reader_typed_extent(DatArchive* a, uint32_t offset, int32_t type,
                             uint64_t count);
void dat_reader_untyped(DatArchive* a);
void dat_reader_relocated_words(DatArchive* a, uint32_t start, uint64_t end);
void dat_reader_record_choice(DatArchive* a, uint32_t offset, int32_t type,
                              uint32_t index);
const char* dat_reader_type_name(const DatArchive* a, uint32_t id);
void dat_reader_mismatch(DatVerify* v, uint32_t at, const char* what,
                         uint64_t want, uint64_t got);
void dat_reader_verify(DatVerify* v, uint32_t offset, int32_t type,
                       const void* native, int depth);
#endif
