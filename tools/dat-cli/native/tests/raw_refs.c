/* Synthetic archive regression: no game data or generated game schema. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dat/test.h>

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
#include "raw_refs.h"

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
