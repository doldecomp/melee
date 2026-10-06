/**
 * @file
 * References to array elements share the array's native storage, including
 * when an element is reached before its container and host strides differ.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dat/archive.h>

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
    T_TYPES,
};

enum {
    DAT_NAME_n = 1,
    DAT_NAME_value,
    DAT_NAME_next,
    DAT_NAME_items,
    DAT_NAME_array,
    DAT_NAME_COUNT
};
static const char* const names[DAT_NAME_COUNT] = {
    [DAT_NAME_n] = "n",         [DAT_NAME_value] = "value",
    [DAT_NAME_next] = "next",   [DAT_NAME_items] = "items",
    [DAT_NAME_array] = "array",
};

#define POINTER(self, to)                                                     \
    static const DatType type_##self = {                                      \
        .name = #self,                                                        \
        .id = self,                                                           \
        .kind = DAT_KIND_POINTER,                                             \
        .has_pointers = 1,                                                    \
        .size = 4,                                                            \
        .native_size = sizeof(void*),                                         \
        .target = to,                                                         \
        .resolved = self,                                                     \
    }

static const DatType type_T_INT = {
    .name = "int",
    .id = T_INT,
    .kind = DAT_KIND_INT,
    .is_signed = 1,
    .size = 4,
    .native_size = sizeof(int64_t),
    .resolved = T_INT,
};
static const DatType type_T_COUNT = {
    .name = "count",
    .id = T_COUNT,
    .kind = DAT_KIND_INT,
    .size = 4,
    .native_size = sizeof(uint32_t),
    .resolved = T_COUNT,
};
POINTER(T_ITEM_P, T_ITEM);
POINTER(T_MATRIX_P, T_MATRIX);
POINTER(T_INLINE_P, T_INLINE);
POINTER(T_COUNTED_P, T_COUNTED);

static const DatMember item_members[] = {
    { DAT_MEMBER(Item, value, 0, T_INT) },
    { DAT_MEMBER(Item, next, 4, T_ITEM_P) },
};
static const DatType type_T_ITEM = {
    .name = "Item",
    .id = T_ITEM,
    .kind = DAT_KIND_STRUCT,
    .has_pointers = 1,
    .size = 8,
    .native_size = sizeof(Item),
    .resolved = T_ITEM,
    DAT_MEMBERS(item_members),
};
static const DatType type_T_ROW = {
    .name = "Item[3]",
    .id = T_ROW,
    .kind = DAT_KIND_ARRAY,
    .has_pointers = 1,
    .size = 24,
    .native_size = sizeof(Item[3]),
    .target = T_ITEM,
    .resolved = T_ROW,
    .count = 3,
};
static const DatType type_T_MATRIX = {
    .name = "Item[2][3]",
    .id = T_MATRIX,
    .kind = DAT_KIND_ARRAY,
    .has_pointers = 1,
    .size = 48,
    .native_size = sizeof(Item[2][3]),
    .target = T_ROW,
    .resolved = T_MATRIX,
    .count = 2,
};
static const DatType type_T_INLINE_ARRAY = {
    .name = "Item[]",
    .id = T_INLINE_ARRAY,
    .kind = DAT_KIND_ARRAY,
    .has_pointers = 1,
    .unbounded = 1,
    .native_size = sizeof(Item),
    .target = T_ITEM,
    .resolved = T_INLINE_ARRAY,
    .count = 1,
};
static const DatMember inline_members[] = {
    { DAT_MEMBER(Inline, n, 0, T_COUNT) },
    { .type = T_INLINE_ARRAY,
      DAT_AT(4),
      .native_offset = offsetof(Inline, items),
      .count = DAT_NAME(n) },
};
static const DatType type_T_INLINE = {
    .name = "Inline",
    .id = T_INLINE,
    .kind = DAT_KIND_STRUCT,
    .has_pointers = 1,
    .size = 4,
    .native_size = sizeof(Inline),
    .resolved = T_INLINE,
    DAT_MEMBERS(inline_members),
};
static const DatMember counted_members[] = {
    { DAT_MEMBER(Counted, n, 0, T_COUNT) },
    { DAT_MEMBER(Counted, items, 4, T_ITEM_P), .count = DAT_NAME(n) },
};
static const DatType type_T_COUNTED = {
    .name = "Counted",
    .id = T_COUNTED,
    .kind = DAT_KIND_STRUCT,
    .has_pointers = 1,
    .size = 8,
    .native_size = sizeof(Counted),
    .resolved = T_COUNTED,
    DAT_MEMBERS(counted_members),
};

static const DatType* const types[T_TYPES] = {
    [T_INT] = &type_T_INT,           [T_COUNT] = &type_T_COUNT,
    [T_ITEM] = &type_T_ITEM,         [T_ITEM_P] = &type_T_ITEM_P,
    [T_ROW] = &type_T_ROW,           [T_MATRIX] = &type_T_MATRIX,
    [T_MATRIX_P] = &type_T_MATRIX_P, [T_INLINE_ARRAY] = &type_T_INLINE_ARRAY,
    [T_INLINE] = &type_T_INLINE,     [T_INLINE_P] = &type_T_INLINE_P,
    [T_COUNTED] = &type_T_COUNTED,   [T_COUNTED_P] = &type_T_COUNTED_P,
};

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
    DatMember members[4] = {
        { DAT_MEMBER(Root, array, 0, kind) },
        { .type = T_ITEM_P,
          DAT_AT(4),
          .native_offset = offsetof(Root, refs[0]) },
        { .type = T_ITEM_P,
          DAT_AT(8),
          .native_offset = offsetof(Root, refs[1]) },
        { .type = T_ITEM_P,
          DAT_AT(12),
          .native_offset = offsetof(Root, refs[2]) },
    };
    if (reverse) {
        DatMember swap = members[0];
        members[0] = members[3];
        members[3] = swap;
    }
    const DatType root_type = {
        .name = "Root",
        .id = T_ROOT,
        .kind = DAT_KIND_STRUCT,
        .has_pointers = 1,
        .size = 16,
        .native_size = sizeof(Root),
        .resolved = T_ROOT,
        DAT_MEMBERS(members),
    };
    const DatType* all[T_TYPES];
    memcpy(all, types, sizeof all);
    all[T_ROOT] = &root_type;
    DatType pointer_type = type_T_ITEM_P;
    if (plain) {
        pointer_type.target = T_INT;
        all[T_ITEM_P] = &pointer_type;
    }
    const DatSchema schema = {
        .types = all,
        .ntypes = T_TYPES,
        .names = names,
        .nnames = DAT_NAME_COUNT,
    };
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

int main(void)
{
    for (int reverse = 0; reverse < 2; reverse++) {
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
