/**
 * @file
 * The library on tables written by hand, over an archive built here: each
 * kind of field converted, pointers followed and shared, unions chosen by
 * `DAT_IF`, and malformed archives refused.
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

/* --- The native types -----------------------------------------------------
 */

typedef struct Leaf {
    int8_t a;
    int16_t b;
    int32_t c;
    float f;
} Leaf;

union Choice {
    Leaf* leaf;
    struct Node* node;
};

typedef struct Node {
    struct Node* next;
    Leaf* leaf;
    Leaf* many;
    uint32_t n;
    uint8_t* raw;
    int32_t kind;
    union Choice u;
    unsigned flag : 3;
    unsigned other : 5;
} Node;

static void set_flag(void* o, uint64_t v)
{
    ((Node*) o)->flag = (unsigned) v & 7;
}

static uint64_t get_flag(const void* o)
{
    return ((const Node*) o)->flag;
}

static void set_other(void* o, uint64_t v)
{
    ((Node*) o)->other = (unsigned) v & 31;
}

static uint64_t get_other(const void* o)
{
    return ((const Node*) o)->other;
}

/* --- Their tables, as the archive lays them out ---------------------------
 */

enum {
    T_S8 = 1,
    T_S16,
    T_S32,
    T_F32,
    T_LEAF,
    T_LEAF_P,
    T_NODE,
    T_NODE_P,
    T_U32,
    T_U8,
    T_U8_P,
    T_CHOICE,
    T_UINT,
    T_INLINE_LEAVES,
    T_INLINE_POINTERS,
    T_FIXED_POINTERS,
    T_LEAF_ARRAY,
    T_POINTER_ARRAY,
    T_FIXED_ARRAY,
    T_COUNT,
};

enum {
    DAT_NAME_n = 1,
    DAT_NAME_kind,
    DAT_NAME_COUNT,
};

static const char* const names[DAT_NAME_COUNT] = {
    [DAT_NAME_n] = "n",
    [DAT_NAME_kind] = "kind",
};

#define SCALAR(self, type_name, type_kind, sign, bytes, native)               \
    static const DatType type_##self = {                                      \
        .name = type_name,                                                    \
        .id = self,                                                           \
        .kind = type_kind,                                                    \
        .is_signed = sign,                                                    \
        .raw = self == T_U8,                                                  \
        .size = bytes,                                                        \
        .native_size = native,                                                \
        .resolved = self,                                                     \
    }
#define POINTER(self, type_name, to)                                          \
    static const DatType type_##self = {                                      \
        .name = type_name,                                                    \
        .id = self,                                                           \
        .kind = DAT_KIND_POINTER,                                             \
        .has_pointers = 1,                                                    \
        .size = 4,                                                            \
        .native_size = sizeof(void*),                                         \
        .target = to,                                                         \
        .resolved = self,                                                     \
    }

SCALAR(T_S8, "s8", DAT_KIND_INT, 1, 1, 1);
SCALAR(T_S16, "s16", DAT_KIND_INT, 1, 2, 2);
SCALAR(T_S32, "s32", DAT_KIND_INT, 1, 4, 4);
SCALAR(T_F32, "f32", DAT_KIND_FLOAT, 0, 4, 4);
SCALAR(T_U32, "u32", DAT_KIND_INT, 0, 4, 4);
SCALAR(T_U8, "u8", DAT_KIND_INT, 0, 1, 1);
SCALAR(T_UINT, "unsigned int", DAT_KIND_INT, 0, 4, sizeof(unsigned));
POINTER(T_LEAF_P, "Leaf*", T_LEAF);
POINTER(T_NODE_P, "Node*", T_NODE);
POINTER(T_U8_P, "u8*", T_U8);

static const DatMember leaf_members[] = {
    { .type = T_S8, DAT_AT(0), DAT_FIELD(Leaf, a) },
    { .type = T_S16, DAT_AT(2), DAT_FIELD(Leaf, b) },
    { .type = T_S32, DAT_AT(4), DAT_FIELD(Leaf, c) },
    { .type = T_F32, DAT_AT(8), DAT_FIELD(Leaf, f) },
};

static const DatType type_T_LEAF = {
    .name = "Leaf",
    .id = T_LEAF,
    .kind = DAT_KIND_STRUCT,
    .size = 12,
    .native_size = sizeof(Leaf),
    .resolved = T_LEAF,
    DAT_MEMBERS(leaf_members),
};

static const DatMember node_members[] = {
    { .type = T_NODE_P, DAT_AT(0), DAT_FIELD(Node, next) },
    { .type = T_LEAF_P, DAT_AT(4), DAT_FIELD(Node, leaf) },
    { .type = T_LEAF_P,
      DAT_AT(8),
      DAT_FIELD(Node, many),
      .count = DAT_NAME(n) },
    { DAT_MEMBER(Node, n, 0xC, T_U32) },
    { .type = T_U8_P, DAT_AT(0x10), DAT_FIELD(Node, raw) },
    { DAT_MEMBER(Node, kind, 0x14, T_S32) },
    { .type = T_CHOICE, DAT_AT(0x18), DAT_FIELD(Node, u) },
    { .type = T_UINT,
      .bit_offset = 0x1C * 8,
      .bit_size = 3,
      .set_bits = set_flag,
      .get_bits = get_flag },
    { .type = T_UINT,
      .bit_offset = 0x1C * 8 + 3,
      .bit_size = 5,
      .set_bits = set_other,
      .get_bits = get_other },
};

static const DatType type_T_NODE = {
    .name = "Node",
    .id = T_NODE,
    .kind = DAT_KIND_STRUCT,
    .has_pointers = 1,
    .size = 0x20,
    .native_size = sizeof(Node),
    .resolved = T_NODE,
    DAT_MEMBERS(node_members),
};

static const DatMember choice_members[] = {
    { .type = T_LEAF_P,
      DAT_AT(0),
      .native_size = sizeof(void*),
      .cond = DAT_BINARY(EQ, DAT_NAME(kind), DAT_INT(0)) },
    { .type = T_NODE_P,
      DAT_AT(0),
      .native_size = sizeof(void*),
      .cond = DAT_BINARY(EQ, DAT_NAME(kind), DAT_INT(1)) },
};

static const DatType type_T_CHOICE = {
    .name = "Choice",
    .id = T_CHOICE,
    .kind = DAT_KIND_UNION,
    .has_pointers = 1,
    .size = 4,
    .native_size = sizeof(union Choice),
    .resolved = T_CHOICE,
    DAT_MEMBERS(choice_members),
};

/* Counted inline arrays have no pointer slot. Flexible arrays need their
   count's native storage, including the host's larger pointer stride. */
typedef struct InlineLeaves {
    int32_t n;
    Leaf entries[];
} InlineLeaves;

typedef struct InlinePointers {
    int32_t n;
    Leaf* entries[];
} InlinePointers;

typedef struct FixedPointers {
    int32_t n;
    Leaf* entries[2];
} FixedPointers;

#define INLINE_MEMBERS(record, element_array)                                 \
    { DAT_MEMBER(record, n, 0, T_S32) },                                      \
    {                                                                         \
        .type = element_array, DAT_AT(4),                                     \
        .native_offset = offsetof(record, entries), .count = DAT_NAME(n)      \
    }

static const DatMember inline_leaves_members[] = {
    INLINE_MEMBERS(InlineLeaves, T_LEAF_ARRAY),
};
static const DatMember inline_pointers_members[] = {
    INLINE_MEMBERS(InlinePointers, T_POINTER_ARRAY),
};
static const DatMember fixed_pointers_members[] = {
    INLINE_MEMBERS(FixedPointers, T_FIXED_ARRAY),
};

#define INLINE_TYPE(self, record, bytes, members_array)                       \
    static const DatType type_##self = {                                      \
        .name = #record,                                                      \
        .id = self,                                                           \
        .kind = DAT_KIND_STRUCT,                                              \
        .has_pointers = self != T_INLINE_LEAVES,                              \
        .size = bytes,                                                        \
        .native_size = sizeof(record),                                        \
        .resolved = self,                                                     \
        DAT_MEMBERS(members_array),                                           \
    }

INLINE_TYPE(T_INLINE_LEAVES, InlineLeaves, 4, inline_leaves_members);
INLINE_TYPE(T_INLINE_POINTERS, InlinePointers, 4, inline_pointers_members);
INLINE_TYPE(T_FIXED_POINTERS, FixedPointers, 12, fixed_pointers_members);

static const DatType type_T_LEAF_ARRAY = {
    .name = "Leaf[]",
    .id = T_LEAF_ARRAY,
    .kind = DAT_KIND_ARRAY,
    .unbounded = 1,
    .native_size = sizeof(Leaf),
    .target = T_LEAF,
    .resolved = T_LEAF_ARRAY,
    .count = 1,
};
static const DatType type_T_POINTER_ARRAY = {
    .name = "Leaf*[]",
    .id = T_POINTER_ARRAY,
    .kind = DAT_KIND_ARRAY,
    .has_pointers = 1,
    .unbounded = 1,
    .native_size = sizeof(Leaf*),
    .target = T_LEAF_P,
    .resolved = T_POINTER_ARRAY,
    .count = 1,
};
static const DatType type_T_FIXED_ARRAY = {
    .name = "Leaf*[2]",
    .id = T_FIXED_ARRAY,
    .kind = DAT_KIND_ARRAY,
    .has_pointers = 1,
    .size = 8,
    .native_size = 2 * sizeof(Leaf*),
    .target = T_LEAF_P,
    .resolved = T_FIXED_ARRAY,
    .count = 2,
};

static const DatType* const types[T_COUNT] = {
    [T_S8] = &type_T_S8,
    [T_S16] = &type_T_S16,
    [T_S32] = &type_T_S32,
    [T_F32] = &type_T_F32,
    [T_LEAF] = &type_T_LEAF,
    [T_LEAF_P] = &type_T_LEAF_P,
    [T_NODE] = &type_T_NODE,
    [T_NODE_P] = &type_T_NODE_P,
    [T_U32] = &type_T_U32,
    [T_U8] = &type_T_U8,
    [T_U8_P] = &type_T_U8_P,
    [T_CHOICE] = &type_T_CHOICE,
    [T_UINT] = &type_T_UINT,
    [T_INLINE_LEAVES] = &type_T_INLINE_LEAVES,
    [T_INLINE_POINTERS] = &type_T_INLINE_POINTERS,
    [T_FIXED_POINTERS] = &type_T_FIXED_POINTERS,
    [T_LEAF_ARRAY] = &type_T_LEAF_ARRAY,
    [T_POINTER_ARRAY] = &type_T_POINTER_ARRAY,
    [T_FIXED_ARRAY] = &type_T_FIXED_ARRAY,
};

static const DatSchema schema = {
    .types = types,
    .ntypes = T_COUNT,
    .names = names,
    .nnames = DAT_NAME_COUNT,
};

/* --- An archive -----------------------------------------------------------
 */

static void put32(unsigned char* p, uint32_t v)
{
    p[0] = (unsigned char) (v >> 24);
    p[1] = (unsigned char) (v >> 16);
    p[2] = (unsigned char) (v >> 8);
    p[3] = (unsigned char) v;
}

static void put16(unsigned char* p, uint16_t v)
{
    p[0] = (unsigned char) (v >> 8);
    p[1] = (unsigned char) v;
}

enum {
    DATA = 0x80
};

static const uint32_t relocs[] = { 0x00, 0x04, 0x08, 0x10, 0x18, 0x20, 0x38 };

/// Node A at 0 (kind 0, its union a leaf), node B at 0x20 (kind 1, its
/// union node A), two leaves at 0x40, raw bytes at 0x70. B's raw pointer is
/// an extern.
static size_t build(unsigned char* f)
{
    unsigned char* d = f + 0x20;
    memset(f, 0, 0x200);
    /* A */
    put32(d + 0x00, 0x20);
    put32(d + 0x04, 0x40);
    put32(d + 0x08, 0x40);
    put32(d + 0x0C, 2);
    put32(d + 0x10, 0x70);
    put32(d + 0x14, 0);
    put32(d + 0x18, 0x40);
    d[0x1C] = 5 << 5 | 17;
    /* B */
    put32(d + 0x20, 0x00);
    put32(d + 0x24, 0xFFFFFFFF);
    put32(d + 0x30, 0xFFFFFFFF);
    put32(d + 0x34, 1);
    put32(d + 0x38, 0x00);
    /* Leaves */
    d[0x40] = 0xFD;
    put16(d + 0x42, 0xFFFE);
    put32(d + 0x44, 0x12345678);
    put32(d + 0x48, 0x3FC00000);
    d[0x4C] = 7;
    put16(d + 0x4E, 300);
    put32(d + 0x50, 0xFFFFFFFF);
    put32(d + 0x54, 0xC0000000);
    memcpy(d + 0x70, "HELLO", 6);
    /* Tables */
    unsigned char* at = d + DATA;
    for (size_t i = 0; i < sizeof relocs / sizeof *relocs; i++, at += 4) {
        put32(at, relocs[i]);
    }
    /* One public, "root" at 0; one extern, "ext" at 0x30 */
    put32(at, 0), put32(at + 4, 0), at += 8;
    put32(at, 0x30), put32(at + 4, 5), at += 8;
    memcpy(at, "root\0ext\0", 9);
    at += 9;
    size_t size = (size_t) (at - f);
    put32(f, (uint32_t) size);
    put32(f + 4, DATA);
    put32(f + 8, sizeof relocs / sizeof *relocs);
    put32(f + 12, 1);
    put32(f + 16, 1);
    return size;
}

static bool contains(const char* text, const char* line)
{
    return strstr(text, line) != NULL;
}

static void test_walk(void)
{
    unsigned char file[0x200];
    size_t size = build(file);
    const char* error = NULL;
    DatArchive* a = dat_open(&schema, file, size, &error);
    CHECK(a != NULL);
    if (a == NULL) {
        printf("dat_open: %s\n", error);
        return;
    }
    Node* root = dat_public(a, "root", T_NODE);
    CHECK(root != NULL);
    if (root == NULL) {
        return;
    }
    Node* b = root->next;
    CHECK(b != NULL && b->next == root);
    CHECK(root->kind == 0 && b->kind == 1);
    /* A union chosen by its record's field */
    CHECK(root->u.leaf == root->leaf);
    CHECK(b->u.node == root);
    /* Scalars sign-extended, floats by their bits */
    CHECK(root->leaf->a == -3);
    CHECK(root->leaf->b == -2);
    CHECK(root->leaf->c == 0x12345678);
    CHECK(root->leaf->f == 1.5f);
    /* A counted array, its first element also an object of its own */
    CHECK(root->n == 2);
    CHECK(root->many != NULL);
    if (root->many != NULL) {
        CHECK(root->many[0].c == 0x12345678 && root->many[0].b == -2);
        CHECK(root->many[1].a == 7 && root->many[1].b == 300);
        CHECK(root->many[1].c == -1 && root->many[1].f == -2.0f);
    }
    /* Raw bytes stay where they are */
    CHECK(root->raw == dat_raw(a, 0x70));
    CHECK(root->raw != NULL && memcmp(root->raw, "HELLO", 6) == 0);
    /* -1 stays -1; externs are null until linked */
    CHECK(b->leaf == (Leaf*) (intptr_t) -1);
    CHECK(b->raw == NULL);
    CHECK(b->many == NULL && b->n == 0);
    /* Bitfields, counted from the most significant bit */
    CHECK(root->flag == 5 && root->other == 17);
    CHECK(b->flag == 0 && b->other == 0);
    CHECK(dat_verify(a, stdout) == 0);
    /* A relocated pointer to a converted object cannot become NULL. */
    Leaf* saved_leaf = root->leaf;
    root->leaf = NULL;
    CHECK(dat_verify(a, NULL) == 1);
    root->leaf = saved_leaf;
    CHECK(dat_verify(a, NULL) == 0);

    FILE* out = tmpfile();
    dat_trace(a, out, DAT_TRACE_ALL);
    long n = ftell(out);
    rewind(out);
    char* text = calloc(1, (size_t) n + 1);
    if (fread(text, 1, (size_t) n, out) != (size_t) n) {
        CHECK(false);
    }
    fclose(out);
    CHECK(contains(text, "object 0x0 7 Node\n"));
    CHECK(contains(text, "object 0x20 7 Node\n"));
    CHECK(contains(text, "object 0x40 5 Leaf\n"));
    CHECK(contains(text, "object 0x70 10 u8\n"));
    CHECK(contains(text, "choice 0x18 12 0\n"));
    CHECK(contains(text, "choice 0x38 12 1\n"));
    CHECK(contains(text, "pointer 0x30\n"));
    CHECK(contains(text, "extent 0x40 0x58\n"));
    CHECK(contains(text, "sentinels 1\n"));
    CHECK(!contains(text, "issue"));
    free(text);
    dat_close(a);
}

static size_t build_inline(unsigned char* f, uint32_t count, bool pointers)
{
    memset(f, 0, 0x200);
    unsigned char* d = f + 0x20;
    put32(d, count);
    if (pointers) {
        put32(d + 4, 0x40);
        put32(d + 8, 0x4C);
        /* Relocated data past the count must stay unwalked. */
        put32(d + 12, 0x40);
    }
    unsigned char* leaves = d + (pointers ? 0x40 : 4);
    leaves[0] = (unsigned char) -3;
    put16(leaves + 2, (uint16_t) -2);
    put32(leaves + 4, 123);
    put32(leaves + 8, 0x3FC00000);
    leaves[12] = 7;
    put16(leaves + 14, 300);
    put32(leaves + 16, 456);
    put32(leaves + 20, 0xC0000000);
    unsigned char* at = d + DATA;
    if (pointers) {
        put32(at, 4), put32(at + 4, 8), put32(at + 8, 12), at += 12;
    }
    put32(at, 0), put32(at + 4, 0), at += 8;
    /* A public inside the array must not shorten its count. */
    put32(at, pointers ? 8 : 16), put32(at + 4, 5), at += 8;
    memcpy(at, "root\0interior\0", 14);
    at += 14;
    size_t size = (size_t) (at - f);
    put32(f, (uint32_t) size);
    put32(f + 4, DATA);
    put32(f + 8, pointers ? 3 : 0);
    put32(f + 12, 2);
    return size;
}

static char* trace(DatArchive* a)
{
    FILE* out = tmpfile();
    dat_trace(a, out, DAT_TRACE_ALL);
    long n = ftell(out);
    rewind(out);
    char* text = calloc(1, (size_t) n + 1);
    CHECK(fread(text, 1, (size_t) n, out) == (size_t) n);
    fclose(out);
    return text;
}

static void test_inline_counts(void)
{
    unsigned char file[0x200];
    size_t size = build_inline(file, 2, false);
    DatArchive* a = dat_open(&schema, file, size, NULL);
    CHECK(a != NULL);
    InlineLeaves* leaves = dat_public(a, "root", T_INLINE_LEAVES);
    CHECK(leaves != NULL && leaves->n == 2);
    if (leaves != NULL) {
        CHECK(leaves->entries[0].b == -2 && leaves->entries[0].c == 123);
        CHECK(leaves->entries[1].b == 300 && leaves->entries[1].c == 456);
        CHECK(leaves->entries[1].f == -2.0f);
        /* Verification must include the flexible array's last element. */
        CHECK(dat_verify(a, NULL) == 0);
        leaves->entries[1].c++;
        CHECK(dat_verify(a, NULL) == 1);
        leaves->entries[1].c--;
    }
    dat_close(a);

    for (unsigned i = 0; i < 6; i++) {
        static const uint32_t counts[] = { 2, 0, 32, UINT32_MAX, 1, 3 };
        bool fixed = i >= 4;
        uint32_t count = counts[i];
        size = build_inline(file, count, true);
        a = dat_open(&schema, file, size, NULL);
        CHECK(a != NULL);
        InlinePointers* pointers = dat_public(
            a, "root", fixed ? T_FIXED_POINTERS : T_INLINE_POINTERS);
        CHECK(pointers != NULL && pointers->n == (int32_t) count);
        char* text = trace(a);
        bool invalid = i == 2 || i == 3 || i == 5;
        if (invalid) {
            CHECK(contains(text, "issue out-of-bounds 0x4"));
            CHECK(!contains(text, "pointer 0x4\n"));
        } else {
            CHECK(!contains(text, "issue"));
            if (count > 0 && pointers != NULL) {
                CHECK(pointers->entries[0]->c == 123);
                CHECK(contains(text, "pointer 0x4\n"));
                if (count == 2) {
                    CHECK(pointers->entries[1]->c == 456);
                    CHECK(contains(text, "pointer 0x8\n"));
                } else {
                    CHECK(!contains(text, "pointer 0x8\n"));
                }
            } else {
                CHECK(!contains(text, "pointer 0x"));
            }
        }
        CHECK(!contains(text, "pointer 0xC\n"));
        CHECK(dat_verify(a, NULL) == 0);
        free(text);
        dat_close(a);
    }
}

static void test_refuses(void)
{
    unsigned char file[0x200];
    size_t size = build(file);
    const char* error = NULL;
    /* The size in the header is the file's */
    CHECK(dat_open(&schema, file, size - 1, &error) == NULL && error != NULL);
    /* A relocation outside the data */
    unsigned char bad[0x200];
    memcpy(bad, file, size);
    put32(bad + 0x20 + DATA, DATA - 2);
    CHECK(dat_open(&schema, bad, size, &error) == NULL);
    /* A public symbol's name outside the symbol table */
    memcpy(bad, file, size);
    put32(bad + 0x20 + DATA + 4 * 7 + 4, 0x100);
    CHECK(dat_open(&schema, bad, size, &error) == NULL);
}

static void test_packed(void)
{
    unsigned char file[0x200];
    size_t size = build(file);
    size_t padded = (size + 31) & ~(size_t) 31;
    unsigned char* two = calloc(1, padded + size);
    memcpy(two, file, size);
    memcpy(two + padded, file, size);
    DatArchive* out[4];
    size_t offsets[4];
    int n =
        dat_open_packed(&schema, two, padded + size, out, offsets, 4, NULL);
    CHECK(n == 2);
    if (n == 2) {
        CHECK(offsets[0] == 0 && offsets[1] == padded);
        Node* a = dat_public(out[1], "root", T_NODE);
        CHECK(a != NULL && a->leaf != NULL && a->leaf->c == 0x12345678);
        dat_close(out[0]);
        dat_close(out[1]);
    }
    free(two);
}

int main(void)
{
    test_walk();
    test_inline_counts();
    test_refuses();
    test_packed();
    printf("%s (%zu-bit %s-endian)\n", failures ? "FAILED" : "ok",
           sizeof(void*) * 8,
           *(const unsigned char*) &(const uint16_t){ 1 } ? "little" : "big");
    return failures ? 1 : 0;
}
