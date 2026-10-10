/**
 * @file
 * References to array elements share the array's native storage, including
 * when an element is reached before its container and host strides differ.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dat/test.h>

static int failures;

#define CHECK(cond)                                                           \
    do {                                                                      \
        if (!(cond)) {                                                        \
            printf("%s:%d: failed: %s\n", __FILE__, __LINE__, #cond);         \
            failures++;                                                       \
        }                                                                     \
    } while (0)

typedef struct Item {
    int64_t value;
    struct Item* next;
} Item;

typedef struct Root {
    void* array;
    Item* refs[3];
} Root;

typedef struct Counted {
    uint32_t n;
    Item* items;
} Counted;

typedef struct Inline {
    uint32_t n;
    Item items[];
} Inline;

typedef struct Recursive {
    int64_t value;
    struct Recursive* array;
    struct Recursive* next;
} Recursive;

enum {
    T_INT = 1,
    T_COUNT,
    T_ITEM,
    T_ITEM_P,
    T_ROW,
    T_MATRIX,
    T_MATRIX_P,
    T_INLINE_ARRAY,
    T_INLINE,
    T_INLINE_P,
    T_COUNTED,
    T_COUNTED_P,
    T_ROOT,
    T_RECURSIVE,
    T_RECURSIVE_P,
    T_RECURSIVE_ARRAY,
    T_RECURSIVE_ARRAY_P,
    T_TYPES,
};

#include "array_refs.h"

static void put32(unsigned char* p, uint32_t value)
{
    p[0] = (unsigned char) (value >> 24);
    p[1] = (unsigned char) (value >> 16);
    p[2] = (unsigned char) (value >> 8);
    p[3] = (unsigned char) value;
}

enum {
    DATA = 0xE0,
    ROOT = 0x80,
    CONTAINER = 0xA0,
    N = 6
};

static size_t build(unsigned char* file, int kind, uint32_t base, bool plain)
{
    memset(file, 0, 0x200);
    unsigned char* d = file + 0x20;
    uint32_t relocs[16];
    size_t nrelocs = 0;
    uint32_t stride = plain ? 4 : 8;
    for (uint32_t i = 0; i < N; i++) {
        put32(d + base + i * stride, i + 1);
        if (!plain) {
            put32(d + base + i * 8 + 4, base + ((i + 1) % N) * 8);
            relocs[nrelocs++] = base + i * 8 + 4;
        }
    }
    put32(d + ROOT, kind == T_MATRIX_P ? base : CONTAINER);
    for (uint32_t i = 0; i < 3; i++) {
        uint32_t index = i == 0 ? 0 : i == 1 ? 2 : N - 1;
        put32(d + ROOT + 4 + i * 4, base + index * stride);
    }
    for (uint32_t i = 0; i < 4; i++) {
        relocs[nrelocs++] = ROOT + i * 4;
    }
    if (kind != T_MATRIX_P) {
        put32(d + CONTAINER, N);
        if (kind == T_COUNTED_P) {
            put32(d + CONTAINER + 4, base);
            relocs[nrelocs++] = CONTAINER + 4;
        }
    }
    unsigned char* at = d + DATA;
    for (size_t i = 0; i < nrelocs; i++, at += 4) {
        put32(at, relocs[i]);
    }
    size_t size = (size_t) (at - file);
    put32(file, (uint32_t) size);
    put32(file + 4, DATA);
    put32(file + 8, (uint32_t) nrelocs);
    return size;
}

static void test(int kind, bool reverse, bool zero, bool plain)
{
    const DatSchema* variants[4][2] = {
        { &fixture_matrix_0_0_schema, &fixture_matrix_1_0_schema },
        { &fixture_counted_0_0_schema, &fixture_counted_1_0_schema },
        { &fixture_inline_0_0_schema, &fixture_inline_1_0_schema },
        { &fixture_counted_0_1_schema, &fixture_counted_1_1_schema },
    };
    unsigned variant = plain                 ? 3
                       : kind == T_MATRIX_P  ? 0
                       : kind == T_COUNTED_P ? 1
                                             : 2;
    const DatSchema schema = *variants[variant][reverse];
    unsigned char file[0x200];
    uint32_t base = kind == T_INLINE_P ? CONTAINER + 4 : zero ? 0 : 0x40;
    size_t size = build(file, kind, base, plain);
    const char* error = NULL;
    DatArchive* a = dat_open(&schema, file, size, &error);
    CHECK(a != NULL);
    if (a == NULL) {
        printf("open: %s\n", error);
        return;
    }
    Root* root = dat_at(a, ROOT, T_ROOT, DAT_COUNT_ONE, 0);
    CHECK(root != NULL && root->array != NULL);
    if (root == NULL || root->array == NULL) {
        dat_close(a);
        return;
    }
    Item* items = kind == T_COUNTED_P  ? ((Counted*) root->array)->items
                  : kind == T_INLINE_P ? ((Inline*) root->array)->items
                                       : root->array;
    if (plain) {
        int64_t* values = (void*) items;
        CHECK((void*) root->refs[0] == &values[0]);
        CHECK((void*) root->refs[1] == &values[2]);
        CHECK((void*) root->refs[2] == &values[N - 1]);
        for (uint32_t i = 0; i < N; i++) {
            CHECK(values[i] == (int64_t) i + 1);
            CHECK(dat_at(a, base + i * 4, T_INT, DAT_COUNT_ONE, 0) ==
                  &values[i]);
        }
        CHECK(dat_verify(a, stdout) == 0);
        values[2] = 123;
        CHECK(*(int64_t*) root->refs[1] == 123);
        values[2] = 3;
        CHECK(dat_verify(a, stdout) == 0);
        dat_close(a);
        return;
    }
    CHECK(root->refs[0] == &items[0]);
    CHECK(root->refs[1] == &items[2]);
    CHECK(root->refs[2] == &items[N - 1]);
    for (uint32_t i = 0; i < N; i++) {
        CHECK(items[i].value == (int64_t) i + 1);
        CHECK(items[i].next == &items[(i + 1) % N]);
        CHECK(dat_at(a, base + i * 8, T_ITEM, DAT_COUNT_ONE, 0) == &items[i]);
    }
    CHECK(dat_verify(a, stdout) == 0);
    items[2].value = 123;
    CHECK(root->refs[1]->value == 123);
    items[2].value = 3;
    root->refs[2]->value = 456;
    CHECK(items[N - 1].value == 456);
    root->refs[2]->value = N;
    CHECK(dat_verify(a, stdout) == 0);
    dat_close(a);
}

static void test_root_array(bool nested, bool zero)
{
    const DatSchema schema = {
        .types = types,
        .ntypes = T_TYPES,
        .names = names,
        .nnames = DAT_NAME_COUNT,
    };
    unsigned char file[0x200];
    uint32_t base = zero ? 0 : 0x40;
    size_t size = build(file, T_MATRIX_P, base, false);
    DatArchive* a = dat_open(&schema, file, size, NULL);
    CHECK(a != NULL);
    if (a == NULL) {
        return;
    }
    Item* items = nested ? dat_at(a, base, T_MATRIX, DAT_COUNT_ONE, 0)
                         : dat_at(a, base, T_ITEM, DAT_COUNT_EXACTLY, N);
    CHECK(items != NULL);
    if (items != NULL) {
        for (uint32_t i = 0; i < N; i++) {
            CHECK(items[i].value == (int64_t) i + 1);
            CHECK(items[i].next == &items[(i + 1) % N]);
            CHECK(dat_at(a, base + i * 8, T_ITEM, DAT_COUNT_ONE, 0) ==
                  &items[i]);
        }
        CHECK(dat_verify(a, stdout) == 0);
    }
    dat_close(a);
}

/// The array is discovered while an element's recursive reader is active.
static void test_recursive_move(bool reverse, uint32_t root_count)
{
    unsigned char bytes[0x20 + 24 + 4 * 4] = { 0 };
    put32(bytes, sizeof bytes);
    put32(bytes + 4, 24);
    unsigned char* data = bytes + 0x20;
    put32(data, 11);
    put32(data + 8, 12);
    put32(data + 12, 22);
    const uint32_t relocs[] = { 4, 8, 16, 20 };
    put32(bytes + 8, DAT_COUNTOF(relocs));
    for (size_t i = 0; i < DAT_COUNTOF(relocs); i++) {
        put32(data + 24 + 4 * i, relocs[i]);
    }
    put32(bytes, 0x20 + 24 + sizeof relocs);
    const DatSchema* selected =
        reverse ? &fixture_recursive_reverse_schema : &schema;
    DatArchive* archive =
        dat_open(selected, bytes, 0x20 + 24 + sizeof relocs, NULL);
    CHECK(archive != NULL);
    if (!archive) {
        return;
    }
    Recursive* root =
        dat_at(archive, 0, T_RECURSIVE,
               root_count ? DAT_COUNT_EXACTLY : DAT_COUNT_ONE, root_count);
    CHECK(root != NULL);
    if (root) {
        CHECK(root->array == root);
        CHECK(root->next == &root->array[1]);
        CHECK(root->value == 11 && root->next->value == 22);
        CHECK(root->next->array == root && root->next->next == root);
        CHECK(dat_at(archive, 12, T_RECURSIVE, DAT_COUNT_ONE, 0) ==
              root->next);
        CHECK(dat_verify(archive, stdout) == 0);
        root->next->value = 33;
        CHECK(root->array[1].value == 33);
    }
    dat_close(archive);
}

int main(void)
{
    for (int reverse = 0; reverse < 2; reverse++) {
        for (uint32_t root_count = 0; root_count <= 2; root_count++) {
            test_recursive_move(reverse, root_count);
        }
        test(T_MATRIX_P, reverse, false, false);
        test(T_MATRIX_P, reverse, true, false);
        test(T_COUNTED_P, reverse, false, false);
        test(T_COUNTED_P, reverse, true, false);
        test(T_INLINE_P, reverse, false, false);
        test(T_COUNTED_P, reverse, false, true);
        test(T_COUNTED_P, reverse, true, true);
        test_root_array(false, reverse);
        test_root_array(true, reverse);
    }
    if (failures != 0) {
        printf("%d failures\n", failures);
        return 1;
    }
    puts("ok: array references share native storage");
    return 0;
}
