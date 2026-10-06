/* Synthetic archive regression: no game data or generated game schema. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dat/archive.h>

static unsigned failures;
#define CHECK(c)                                                              \
    do {                                                                      \
        if (!(c)) {                                                           \
            fprintf(stderr, "%s:%d: failed: %s\n", __FILE__, __LINE__, #c);   \
            failures++;                                                       \
        }                                                                     \
    } while (0)

typedef union Ambiguous {
    unsigned char* a;
    unsigned char* b;
} Ambiguous;
typedef struct Refs {
    unsigned char *zero_a, *nonzero_a, *zero_b, *nonzero_b;
    unsigned int *blob_a, *blob_b;
    void* unknown;
    unsigned char *empty, *external, *local_null;
    Ambiguous ambiguous;
} Refs;

enum {
    BYTE = 1,
    WORD,
    BLOB,
    BYTE_P,
    BLOB_P,
    VOID_P,
    AMBIGUOUS,
    REFS,
    REVERSED,
    N_TYPES
};
#define BASE(i, k, sz, ns)                                                    \
    .id = i, .resolved = i, .kind = k, .size = sz, .native_size = ns
static const DatType byte = {
    .name = "byte",
    BASE(BYTE, DAT_KIND_INT, 1, 1),
    .raw = 1,
};
static const DatType word = {
    .name = "word",
    BASE(WORD, DAT_KIND_INT, 4, sizeof(unsigned int)),
};
/* Opacity belongs to this typedef; the canonical word is not raw. */
static const DatType blob = {
    .name = "Blob",
    .id = BLOB,
    .resolved = WORD,
    .kind = DAT_KIND_TYPEDEF,
    .size = 4,
    .native_size = sizeof(unsigned int),
    .target = WORD,
    .blob = 1,
};
#define PTR(i, target_type)                                                   \
    static const DatType ptr_##i = { .name = #i,                              \
                                     BASE(i, DAT_KIND_POINTER, 4,             \
                                          sizeof(void*)),                     \
                                     .target = target_type,                   \
                                     .has_pointers = 1 }
PTR(BYTE_P, BYTE);
PTR(BLOB_P, BLOB);
PTR(VOID_P, DAT_NONE);
static const DatMember ambiguous_members[] = {
    { .type = BYTE_P, DAT_AT(0), .native_size = sizeof(void*) },
    { .type = BYTE_P, DAT_AT(0), .native_size = sizeof(void*) },
};
static const DatType ambiguous = {
    .name = "Ambiguous",
    BASE(AMBIGUOUS, DAT_KIND_UNION, 4, sizeof(Ambiguous)),
    .has_pointers = 1,
    DAT_MEMBERS(ambiguous_members),
};
#define REF(field, at, t) { .type = t, DAT_AT(at), DAT_FIELD(Refs, field) }
#define EMPTY                                                                 \
    { .type = BYTE_P,                                                         \
      DAT_AT(0x1C),                                                           \
      DAT_FIELD(Refs, empty),                                                 \
      .count = DAT_INT(0) }
static const DatMember members[] = {
    REF(zero_a, 0, BYTE_P),        REF(nonzero_a, 4, BYTE_P),
    REF(zero_b, 8, BYTE_P),        REF(nonzero_b, 0xC, BYTE_P),
    REF(blob_a, 0x10, BLOB_P),     REF(blob_b, 0x14, BLOB_P),
    REF(unknown, 0x18, VOID_P),    EMPTY,
    REF(external, 0x20, BYTE_P),   REF(ambiguous, 0x24, AMBIGUOUS),
    REF(local_null, 0x28, BYTE_P),
};
static const DatMember reversed_members[] = {
    REF(blob_b, 0x14, BLOB_P),     REF(blob_a, 0x10, BLOB_P),
    REF(nonzero_b, 0xC, BYTE_P),   REF(zero_b, 8, BYTE_P),
    REF(nonzero_a, 4, BYTE_P),     REF(zero_a, 0, BYTE_P),
    REF(unknown, 0x18, VOID_P),    EMPTY,
    REF(external, 0x20, BYTE_P),   REF(ambiguous, 0x24, AMBIGUOUS),
    REF(local_null, 0x28, BYTE_P),
};
#define RECORD(i, list)                                                       \
    static const DatType record_##i = { .name = #i,                           \
                                        BASE(i, DAT_KIND_STRUCT, 0x2C,        \
                                             sizeof(Refs)),                   \
                                        .has_pointers = 1,                    \
                                        DAT_MEMBERS(list) }
RECORD(REFS, members);
RECORD(REVERSED, reversed_members);
static const DatType* const types[N_TYPES] = {
    [BYTE] = &byte,
    [WORD] = &word,
    [BLOB] = &blob,
    [BYTE_P] = &ptr_BYTE_P,
    [BLOB_P] = &ptr_BLOB_P,
    [VOID_P] = &ptr_VOID_P,
    [AMBIGUOUS] = &ambiguous,
    [REFS] = &record_REFS,
    [REVERSED] = &record_REVERSED,
};
static const DatSchema schema = { .types = types, .ntypes = N_TYPES };

static void put32(unsigned char* p, unsigned int v)
{
    p[0] = v >> 24;
    p[1] = v >> 16;
    p[2] = v >> 8;
    p[3] = v;
}

/* Raw targets at body offsets 0, 8, 0x10; record at 0x20. The extern
   chain at 0x40 is unrelocated. The unselected union still has a relocation.
 */
static size_t build(unsigned char file[256])
{
    static const unsigned int relocs[] = {
        0x20, 0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C, 0x44,
    };
    memset(file, 0, 256);
    unsigned char* d = file + 0x20;
    memcpy(d, "ZERO", 4);
    put32(d + 8, 0x01234567);
    memcpy(d + 0x10, "DATA", 4);
    put32(d + 0x20, 0);
    put32(d + 0x24, 0x10);
    put32(d + 0x28, 0);
    put32(d + 0x2C, 0x10);
    put32(d + 0x30, 8);
    put32(d + 0x34, 8);
    put32(d + 0x38, 0x10);
    put32(d + 0x3C, 0x10);
    put32(d + 0x40, 0xFFFFFFFF);
    put32(d + 0x44, 0x10);
    unsigned char* at = d + 0x50;
    for (size_t i = 0; i < sizeof relocs / sizeof *relocs; i++, at += 4) {
        put32(at, relocs[i]);
    }
    put32(at, 0x20);
    put32(at + 4, 0);
    at += 8;
    put32(at, 0x40);
    put32(at + 4, 5);
    at += 8;
    memcpy(at, "root\0ext\0", 9);
    at += 9;
    size_t size = at - file;
    put32(file, size);
    put32(file + 4, 0x50);
    put32(file + 8, sizeof relocs / sizeof *relocs);
    put32(file + 12, 1);
    put32(file + 16, 1);
    return size;
}

static unsigned consume(const unsigned char* p)
{
    /* A bounded byte consumer rather than a dereference of a missing pointer.
     */
    if (p == NULL) {
        return 0;
    }
    return p[0] + p[1] + p[2] + p[3];
}

static void save_trace(DatArchive* a, const char* dir, unsigned mode)
{
    if (dir == NULL) {
        return;
    }
    char path[1024];
    int n = snprintf(path, sizeof path, "%s/trace-%u.txt", dir, mode);
    CHECK(n > 0 && (size_t) n < sizeof path);
    FILE* out = fopen(path, "w");
    CHECK(out != NULL);
    if (out != NULL) {
        dat_trace(a, out, DAT_TRACE_ALL);
        fclose(out);
    }
}

static void test_refs(unsigned mode, const char* dir)
{
    unsigned char file[256];
    size_t size = build(file);
    const char* error = NULL;
    DatArchive* a = dat_open(&schema, file, size, &error);
    CHECK(a != NULL);
    if (a == NULL) {
        return;
    }
    /* The library owns its copy of the bytes. */
    memset(file, 0xCC, sizeof file);
    if (mode == 2) {
        CHECK(dat_at(a, 0, BYTE, DAT_COUNT_ONE, 0) == dat_raw(a, 0));
        CHECK(dat_at(a, 8, BLOB, DAT_COUNT_ONE, 0) == dat_raw(a, 8));
    } else if (mode == 3) {
        CHECK(dat_at(a, 0, BYTE, DAT_COUNT_EXACTLY, 4) == dat_raw(a, 0));
        CHECK(dat_at(a, 8, BLOB, DAT_COUNT_EXACTLY, 1) == dat_raw(a, 8));
    }
    Refs* r = dat_public(a, "root", mode == 1 ? REVERSED : REFS);
    CHECK(r != NULL);
    if (r == NULL) {
        dat_close(a);
        return;
    }
    unsigned present = !!r->zero_a + !!r->zero_b + !!r->nonzero_a +
                       !!r->nonzero_b + !!r->blob_a + !!r->blob_b;
    size_t before = dat_verify(a, NULL);
    unsigned sum = consume(r->zero_a) + consume(r->zero_b) +
                   consume(r->nonzero_a) + consume(r->nonzero_b);
    printf("case %u present=%u verify=%zu consumer=%u\n", mode, present,
           before, sum);
    save_trace(a, dir, mode);
    CHECK(r->zero_a == dat_raw(a, 0) && r->zero_b == r->zero_a);
    CHECK(r->nonzero_a == dat_raw(a, 0x10) && r->nonzero_b == r->nonzero_a);
    CHECK((const void*) r->blob_a == dat_raw(a, 8) && r->blob_b == r->blob_a);
    CHECK(sum == 2 * (consume(dat_raw(a, 0)) + consume(dat_raw(a, 0x10))));
    /* Registering opaque objects must not make verify decode guest bytes. */
    CHECK(memcmp(dat_raw(a, 8), "\x01\x23\x45\x67", 4) == 0);
    CHECK(before == 0);
    CHECK(r->unknown == dat_raw(a, 0x10));
    CHECK(r->empty == dat_raw(a, 0x10));
    CHECK(r->external == NULL && r->local_null == NULL &&
          r->ambiguous.a == NULL);
    CHECK(dat_public(a, "root", mode == 1 ? REVERSED : REFS) == r);
    /* A scalar-first visit must also remain usable through root-array API. */
    CHECK(dat_at(a, 0, BYTE, DAT_COUNT_EXACTLY, 4) == dat_raw(a, 0));
    CHECK(dat_at(a, 8, BLOB, DAT_COUNT_EXACTLY, 1) == dat_raw(a, 8));
    unsigned char* saved = r->zero_a;
    r->zero_a = NULL;
    FILE* diagnostics = tmpfile();
    CHECK(diagnostics != NULL);
    size_t missing_zero = dat_verify(a, diagnostics);
    if (diagnostics != NULL) {
        rewind(diagnostics);
        char text[2048] = { 0 };
        fread(text, 1, sizeof text - 1, diagnostics);
        CHECK(strstr(text, "missing relocated pointer") != NULL);
        fclose(diagnostics);
    }
    r->zero_a = saved;
    saved = r->nonzero_a;
    r->nonzero_a = NULL;
    size_t missing_nonzero = dat_verify(a, NULL);
    r->nonzero_a = saved;
    void* unknown = r->unknown;
    r->unknown = NULL;
    size_t missing_unknown = dat_verify(a, NULL);
    r->unknown = unknown;
    printf("corruption %u zero=%zu nonzero=%zu untyped=%zu\n", mode,
           missing_zero, missing_nonzero, missing_unknown);
    CHECK(missing_zero > 0 && missing_nonzero > 0 && missing_unknown > 0);
    CHECK(dat_verify(a, NULL) == before);
    if (mode == 0) {
        size = build(file);
        DatArchive* other = dat_open(&schema, file, size, NULL);
        CHECK(other != NULL);
        if (other != NULL) {
            CHECK(dat_raw(other, 0) != dat_raw(a, 0));
            dat_close(other);
            CHECK(consume(r->zero_a) == consume(dat_raw(a, 0)));
        }
    }
    dat_close(a);
}

int main(int argc, char** argv)
{
    for (unsigned i = 0; i < 4; i++) {
        test_refs(i, argc > 1 ? argv[1] : NULL);
    }
    printf("%s failures=%u pointer_bytes=%zu\n", failures ? "FAILED" : "ok",
           failures, sizeof(void*));
    return failures ? 1 : 0;
}
