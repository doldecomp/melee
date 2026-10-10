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

typedef struct CountedLists {
    uint32_t n;
    Leaf* (*rows)[2];
} CountedLists;

typedef struct InlineLists {
    uint32_t n;
    Leaf* rows[2];
} InlineLists;

/// A vertex descriptor, laid out as `GXMaxIndex` reads it, and a shape
/// whose display list indexes the vertex arrays its descriptors point to.
typedef struct Desc {
    uint32_t attr, attr_type, comp_cnt, comp_type, stride;
    uint8_t* vertex;
} Desc;

typedef struct Shape {
    Desc* descs;
    uint8_t* list;
    uint32_t n;
} Shape;

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
    T_COUNTED_LEAF_P,
    T_COUNTED_ROW,
    T_COUNTED_ROW_P,
    T_COUNTED_LISTS,
    T_INLINE_LISTS,
    T_SCRIPT,
    T_SCRIPT_ROW,
    T_BLOB,
    T_BLOB_P,
    T_DESC,
    T_DESC_P,
    T_SHAPE,
    T_COUNT,
};

enum {
    DAT_NAME_n = 1,
    DAT_NAME_kind,
    DAT_NAME_lists_count,
    DAT_NAME_rows,
    DAT_NAME__command,
    DAT_NAME_dl,
    DAT_NAME_descs,
    DAT_NAME_list,
    DAT_NAME_attr,
    DAT_NAME_stride,
    DAT_NAME_COUNT,
};

static const char* const names[DAT_NAME_COUNT] = {
    [DAT_NAME_n] = "n",
    [DAT_NAME_kind] = "kind",
    [DAT_NAME_lists_count] = "Lists::count",
    [DAT_NAME_rows] = "rows",
    [DAT_NAME__command] = "_command",
    [DAT_NAME_dl] = "dl",
    [DAT_NAME_descs] = "descs",
    [DAT_NAME_list] = "list",
    [DAT_NAME_attr] = "attr",
    [DAT_NAME_stride] = "stride",
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

static const DatType type_T_COUNTED_LEAF_P = {
    .name = "CountedLeafPtr",
    .id = T_COUNTED_LEAF_P,
    .kind = DAT_KIND_TYPEDEF,
    .has_pointers = 1,
    .size = 4,
    .native_size = sizeof(Leaf*),
    .target = T_LEAF_P,
    .resolved = T_LEAF_P,
    .count_tag = DAT_NAME(lists_count),
};

static const DatType type_T_COUNTED_ROW = {
    .name = "CountedLeafPtr[2]",
    .id = T_COUNTED_ROW,
    .kind = DAT_KIND_ARRAY,
    .has_pointers = 1,
    .size = 8,
    .native_size = 2 * sizeof(Leaf*),
    .target = T_COUNTED_LEAF_P,
    .resolved = T_COUNTED_ROW,
    .count = 2,
};

POINTER(T_COUNTED_ROW_P, "CountedLeafPtr(*)[2]", T_COUNTED_ROW);

static const DatMember counted_lists_members[] = {
    { DAT_MEMBER(CountedLists, n, 0, T_U32) },
    { DAT_MEMBER(CountedLists, rows, 4, T_COUNTED_ROW_P), .extent = 1,
      DAT_BINDS({ DAT_NAME_lists_count, DAT_NAME(n) }) },
};

static const DatMember inline_lists_members[] = {
    { DAT_MEMBER(InlineLists, n, 0, T_U32) },
    { DAT_MEMBER(InlineLists, rows, 4, T_COUNTED_ROW),
      DAT_BINDS({ DAT_NAME_lists_count, DAT_NAME(n) }) },
};

INLINE_TYPE(T_COUNTED_LISTS, CountedLists, 8, counted_lists_members);
INLINE_TYPE(T_INLINE_LISTS, InlineLists, 12, inline_lists_members);

/* An array of script pointers annotated with `DAT_BYTE_SCRIPT`. */
static const DatType type_T_SCRIPT = {
    .name = "Script",
    .id = T_SCRIPT,
    .kind = DAT_KIND_TYPEDEF,
    .has_pointers = 1,
    .size = 4,
    .native_size = sizeof(uint8_t*),
    .target = T_U8_P,
    .resolved = T_U8_P,
    .script =
        &(const DatScript){
            .length = DAT_CALL(CPU_COMMAND_LENGTH, DAT_NAME(_command)),
            .bytes = 1,
        },
};

static const DatType type_T_SCRIPT_ROW = {
    .name = "Script[3]",
    .id = T_SCRIPT_ROW,
    .kind = DAT_KIND_ARRAY,
    .has_pointers = 1,
    .size = 12,
    .native_size = 3 * sizeof(uint8_t*),
    .target = T_SCRIPT,
    .resolved = T_SCRIPT_ROW,
    .count = 3,
};

static const DatType type_T_BLOB = {
    .name = "Blob",
    .id = T_BLOB,
    .kind = DAT_KIND_TYPEDEF,
    .blob = 1,
    .size = 1,
    .native_size = 1,
    .target = T_U8,
    .resolved = T_U8,
};

POINTER(T_BLOB_P, "Blob*", T_BLOB);
POINTER(T_DESC_P, "Desc*", T_DESC);

static const DatMember desc_members[] = {
    { DAT_MEMBER(Desc, attr, 0, T_U32) },
    { .type = T_U32, DAT_AT(4), DAT_FIELD(Desc, attr_type) },
    { .type = T_U32, DAT_AT(8), DAT_FIELD(Desc, comp_cnt) },
    { .type = T_U32, DAT_AT(0xC), DAT_FIELD(Desc, comp_type) },
    { DAT_MEMBER(Desc, stride, 0x10, T_U32) },
    { .type = T_BLOB_P,
      DAT_AT(0x14),
      DAT_FIELD(Desc, vertex),
      .count = DAT_BINARY(MUL,
                          DAT_BINARY(ADD,
                                     DAT_CALL(GX_MAX_INDEX, DAT_NAME(dl),
                                              DAT_NAME(descs), DAT_NAME(attr)),
                                     DAT_INT(1)),
                          DAT_NAME(stride)) },
};

static const DatMember shape_members[] = {
    { DAT_MEMBER(Shape, descs, 0, T_DESC_P), .terminator = DAT_INT(0xFF),
      DAT_BINDS({ DAT_NAME_dl, DAT_NAME(list) },
                { DAT_NAME_descs, DAT_NAME(descs) }) },
    { DAT_MEMBER(Shape, list, 4, T_BLOB_P), .count = DAT_NAME(n) },
    { DAT_MEMBER(Shape, n, 8, T_U32) },
};

static const DatType type_T_DESC = {
    .name = "Desc",
    .id = T_DESC,
    .kind = DAT_KIND_STRUCT,
    .has_pointers = 1,
    .size = 0x18,
    .native_size = sizeof(Desc),
    .resolved = T_DESC,
    DAT_MEMBERS(desc_members),
};

INLINE_TYPE(T_SHAPE, Shape, 0xC, shape_members);

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
    [T_COUNTED_LEAF_P] = &type_T_COUNTED_LEAF_P,
    [T_COUNTED_ROW] = &type_T_COUNTED_ROW,
    [T_COUNTED_ROW_P] = &type_T_COUNTED_ROW_P,
    [T_COUNTED_LISTS] = &type_T_COUNTED_LISTS,
    [T_INLINE_LISTS] = &type_T_INLINE_LISTS,
    [T_SCRIPT] = &type_T_SCRIPT,
    [T_SCRIPT_ROW] = &type_T_SCRIPT_ROW,
    [T_BLOB] = &type_T_BLOB,
    [T_BLOB_P] = &type_T_BLOB_P,
    [T_DESC] = &type_T_DESC,
    [T_DESC_P] = &type_T_DESC_P,
    [T_SHAPE] = &type_T_SHAPE,
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
    CHECK(root->leaf == root->many);
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

static void test_array_typedef_counts(void)
{
    for (unsigned i = 0; i < 4; i++) {
        unsigned char file[0x200];
        uint32_t count = i < 2 ? 2 : 0;
        bool inline_row = i % 2 != 0;
        size_t size = build_inline(file, count, true);
        unsigned char* d = file + 0x20;
        /* Two lists of two leaves; the last leaf of each must be read. */
        memcpy(d + 0x58, d + 0x40, 24);
        put32(d + 0x5C, 111);
        put32(d + 0x68, 222);
        if (!inline_row) {
            put32(d + 4, 16);
            put32(d + 8, 0);
            put32(d + 12, 0);
            put32(d + 16, 0x40);
            put32(d + 20, 0x58);
            put32(d + DATA + 4, 16);
            put32(d + DATA + 8, 20);
        } else {
            put32(d + 8, 0x58);
        }
        DatArchive* a = dat_open(&schema, file, size, NULL);
        CHECK(a != NULL);
        Leaf** row = NULL;
        if (!inline_row) {
            CountedLists* lists = dat_public(a, "root", T_COUNTED_LISTS);
            CHECK(lists != NULL && lists->rows != NULL);
            if (lists != NULL && lists->rows != NULL) {
                row = lists->rows[0];
            }
        } else {
            InlineLists* lists = dat_public(a, "root", T_INLINE_LISTS);
            CHECK(lists != NULL);
            if (lists != NULL) {
                row = lists->rows;
            }
        }
        CHECK(row != NULL && row[0] != NULL && row[1] != NULL);
        char* text = trace(a);
        CHECK(!contains(text, "issue"));
        CHECK(contains(text, "extent 0x40 0x58") == (count > 0));
        CHECK(contains(text, "extent 0x58 0x70") == (count > 0));
        if (count > 0 && row != NULL && row[0] != NULL && row[1] != NULL) {
            /* An incomplete list should fail without an out-of-bounds
               access, so guard its last element with the traced extent. */
            if (contains(text, "extent 0x40 0x58") &&
                contains(text, "extent 0x58 0x70"))
            {
                CHECK(row[0][1].c == 456);
                CHECK(row[1][1].c == 222);
            }
        }
        CHECK(dat_verify(a, NULL) == 0);
        free(text);
        dat_close(a);
    }
}

/// Test a 0x7F argument, a two-argument command, and an unterminated script.
static void test_byte_scripts(void)
{
    static const unsigned char scripts[] = {
        0x80, 0x7F, 0x7F, 0, 0x01, 0xC0, 0x01, 0x02, 0x7F, 0, 0, 0, 0x01, 0x02,
    };
    unsigned char file[0x200];
    memset(file, 0, sizeof file);
    unsigned char* d = file + 0x20;
    put32(d, 12), put32(d + 4, 16), put32(d + 8, 24);
    memcpy(d + 12, scripts, sizeof scripts);
    uint32_t data = 12 + sizeof scripts;
    unsigned char* at = d + data;
    put32(at, 0), put32(at + 4, 4), put32(at + 8, 8), at += 12;
    put32(at, 0), put32(at + 4, 0), at += 8;
    memcpy(at, "root", 5);
    at += 5;
    size_t size = (size_t) (at - file);
    put32(file, (uint32_t) size);
    put32(file + 4, data);
    put32(file + 8, 3);
    put32(file + 12, 1);
    DatArchive* a = dat_open(&schema, file, size, NULL);
    CHECK(a != NULL);
    if (a == NULL) {
        return;
    }
    uint8_t** row = dat_public(a, "root", T_SCRIPT_ROW);
    CHECK(row != NULL);
    if (row != NULL) {
        /* Script pointers refer to unchanged archive bytes. */
        CHECK(row[0] == dat_raw(a, 12) && row[2] == dat_raw(a, 24));
    }
    char* text = trace(a);
    CHECK(contains(text, "extent 0xC 0xF\n"));
    CHECK(contains(text, "extent 0x10 0x15\n"));
    CHECK(!contains(text, "extent 0x18"));
    CHECK(contains(text, "issue out-of-bounds 0x1A"));
    CHECK(dat_verify(a, NULL) == 0);
    free(text);
    dat_close(a);
}

/// Three shapes at 0, 0x10 and 0xA0. The first and third share descriptors
/// at 0x20; the second uses 0x50. Both lists reference 4-byte positions at
/// 0xC0. Display lists at 0x80, 0x88 and 0x90 use indices up to 2, 5 and 7.
/// Export the first `publics` shapes as "a", "b" and "c".
static size_t build_shapes(unsigned char* f, size_t publics)
{
    static const uint32_t shape_relocs[] = { 0x00, 0x04, 0x10, 0x14,
                                             0x34, 0x64, 0xA0, 0xA4 };
    static const uint32_t shapes[3][3] = {
        { 0x00, 0x20, 0x80 },
        { 0x10, 0x50, 0x88 },
        { 0xA0, 0x20, 0x90 },
    };
    static const unsigned char lists[24] = {
        0x90, 0, 3, 0, 1,    2, 0, 0, 0x98, 0, 2, 5,
        1,    0, 0, 0, 0x98, 0, 1, 7, 0,    0, 0, 0,
    };
    memset(f, 0, 0x200);
    unsigned char* d = f + 0x20;
    for (size_t i = 0; i < 3; i++) {
        unsigned char* shape = d + shapes[i][0];
        put32(shape, shapes[i][1]);
        put32(shape + 4, shapes[i][2]);
        put32(shape + 8, 8);
    }
    for (uint32_t i = 0; i < 2; i++) {
        unsigned char* desc = d + 0x20 + i * 0x30;
        /* GX_VA_POS, GX_INDEX8, then GX_VA_NULL */
        put32(desc, 9);
        put32(desc + 4, 2);
        put32(desc + 0x10, 4);
        put32(desc + 0x14, 0xC0);
        put32(desc + 0x18, 0xFF);
    }
    memcpy(d + 0x80, lists, sizeof lists);
    enum {
        SHAPE_DATA = 0x100
    };
    unsigned char* at = d + SHAPE_DATA;
    for (size_t i = 0; i < 8; i++, at += 4) {
        put32(at, shape_relocs[i]);
    }
    for (uint32_t i = 0; i < publics; i++, at += 8) {
        put32(at, shapes[i][0]);
        put32(at + 4, i * 2);
    }
    memcpy(at, "a\0b\0c\0", 6);
    at += 6;
    size_t size = (size_t) (at - f);
    put32(f, (uint32_t) size);
    put32(f + 4, SHAPE_DATA);
    put32(f + 8, 8);
    put32(f + 12, (uint32_t) publics);
    return size;
}

static void test_vertex_arrays(void)
{
    /* Each shape's list reaches further than the last's; the third shares
       the first's descriptor list, walked already */
    static const struct {
        size_t publics;
        const char* extent;
    } cases[] = {
        { 1, "extent 0xC0 0xCC\n" },
        { 2, "extent 0xC0 0xD8\n" },
        { 3, "extent 0xC0 0xE0\n" },
    };
    for (size_t i = 0; i < 3; i++) {
        unsigned char file[0x200];
        size_t size = build_shapes(file, cases[i].publics);
        DatArchive* a = dat_open(&schema, file, size, NULL);
        CHECK(a != NULL);
        if (a == NULL) {
            continue;
        }
        for (size_t j = 0; j < cases[i].publics; j++) {
            Shape* shape =
                dat_public(a, (const char[]){ 'a' + j, 0 }, T_SHAPE);
            CHECK(shape != NULL);
            if (shape != NULL) {
                CHECK(shape->descs[0].vertex == dat_raw(a, 0xC0));
                CHECK(shape->descs[1].attr == 0xFF);
            }
        }
        char* text = trace(a);
        CHECK(!contains(text, "issue"));
        CHECK(contains(text, "pointer 0x34\n"));
        CHECK(contains(text, cases[i].extent));
        CHECK(dat_verify(a, NULL) == 0);
        free(text);
        dat_close(a);
    }
}

static void test_vertex_extent_fallback(void)
{
    DatMember members[sizeof desc_members / sizeof *desc_members];
    memcpy(members, desc_members, sizeof members);
    members[5].extent = true;
    DatType type = type_T_DESC;
    type.members = members;
    const DatType* local_types[T_COUNT];
    memcpy(local_types, types, sizeof types);
    local_types[T_DESC] = &type;
    DatSchema local_schema = schema;
    local_schema.types = local_types;
    for (unsigned order = 0; order < 3; order++) {
        unsigned char file[0x200];
        size_t size = build_shapes(file, 1);
        DatArchive* a = dat_open(&local_schema, file, size, NULL);
        CHECK(a != NULL);
        if (a == NULL) {
            continue;
        }
        if (order == 1) {
            CHECK(dat_public(a, "a", T_SHAPE) != NULL);
        }
        Desc* desc = dat_at(a, 0x20, T_DESC, DAT_COUNT_ONE, 0);
        CHECK(desc != NULL && desc->vertex == dat_raw(a, 0xC0));
        if (order == 2) {
            CHECK(dat_public(a, "a", T_SHAPE) != NULL);
        }
        char* text = trace(a);
        CHECK(!contains(text, "issue"));
        CHECK(contains(text, "extent 0xC0 0x100\n"));
        CHECK(dat_verify(a, NULL) == 0);
        free(text);
        dat_close(a);
    }
}

static void test_nbt3_indices(void)
{
    for (unsigned attr = 10; attr <= 25; attr += 15) {
        unsigned char file[0x200];
        size_t size = build_shapes(file, 1);
        unsigned char* d = file + 0x20;
        put32(d + 8, 16);
        put32(d + 0x20, attr);
        put32(d + 0x28, 2);
        static const unsigned char dl[16] = {
            0x90, 0, 2, 1, 2, 7, 3, 4, 5, 0,
        };
        memcpy(d + 0x80, dl, sizeof dl);
        DatArchive* a = dat_open(&schema, file, size, NULL);
        CHECK(a != NULL);
        CHECK(dat_public(a, "a", T_SHAPE) != NULL);
        char* text = trace(a);
        CHECK(!contains(text, "issue"));
        CHECK(contains(text, "extent 0xC0 0xE0\n"));
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

static void test_conditional_counts(void)
{
    /* An unresolved inactive branch must not stop a count from being read. */
    const DatExpr* counts[] = {
        DAT_COND(DAT_INT(1), DAT_NAME(n), DAT_FAIL),
        DAT_COND(DAT_INT(0), DAT_FAIL, DAT_NAME(n)),
        DAT_COND(DAT_NAME(n), DAT_COND(DAT_INT(0), DAT_FAIL, DAT_NAME(n)),
                 DAT_INT(0)),
    };
    for (size_t i = 0; i < sizeof counts / sizeof *counts; i++) {
        DatMember members[2];
        memcpy(members, inline_leaves_members, sizeof members);
        members[1].count = counts[i];
        DatType type = type_T_INLINE_LEAVES;
        type.members = members;
        const DatType* local_types[T_COUNT];
        memcpy(local_types, types, sizeof types);
        local_types[T_INLINE_LEAVES] = &type;
        DatSchema local_schema = schema;
        local_schema.types = local_types;
        for (uint32_t count = 0; count <= 2; count += 2) {
            unsigned char file[0x200];
            size_t size = build_inline(file, count, false);
            DatArchive* a = dat_open(&local_schema, file, size, NULL);
            CHECK(a != NULL);
            InlineLeaves* leaves = dat_public(a, "root", T_INLINE_LEAVES);
            CHECK(leaves != NULL && leaves->n == (int32_t) count);
            char* text = trace(a);
            CHECK(!contains(text, "issue"));
            CHECK(contains(text, "extent 0x10 0x1C") == (count == 2));
            if (count == 2 && leaves != NULL) {
                CHECK(leaves->entries[1].c == 456);
            }
            CHECK(dat_verify(a, NULL) == 0);
            free(text);
            dat_close(a);
        }
    }
}

static void test_union_member_binding(void)
{
    DatMember members[2];
    memcpy(members, choice_members, sizeof members);
    const DatBind binds[] = { { DAT_NAME_lists_count, DAT_NAME(n) } };
    members[0].type = T_COUNTED_LEAF_P;
    members[0].binds = binds;
    members[0].nbinds = 1;
    DatType type = type_T_CHOICE;
    type.members = members;
    const DatType* local_types[T_COUNT];
    memcpy(local_types, types, sizeof types);
    local_types[T_CHOICE] = &type;
    DatSchema local_schema = schema;
    local_schema.types = local_types;
    unsigned char file[0x200];
    size_t size = build(file);
    DatArchive* a = dat_open(&local_schema, file, size, NULL);
    CHECK(a != NULL);
    Node* root = dat_public(a, "root", T_NODE);
    CHECK(root != NULL && root->u.leaf != NULL);
    char* text = trace(a);
    CHECK(!contains(text, "issue"));
    CHECK(contains(text, "extent 0x40 0x58"));
    CHECK(dat_verify(a, NULL) == 0);
    free(text);
    dat_close(a);
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

static void test_tagged_plain_union_size(void)
{
    union PlainChoice {
        uint32_t small;
        Leaf large;
    };
    const DatMember members[] = {
        { .type = T_U32,
          DAT_AT(0),
          DAT_FIELD(union PlainChoice, small),
          .cond = DAT_BINARY(EQ, DAT_NAME(kind), DAT_INT(0)) },
        { .type = T_LEAF,
          DAT_AT(0),
          DAT_FIELD(union PlainChoice, large),
          .cond = DAT_BINARY(EQ, DAT_NAME(kind), DAT_INT(1)) },
    };
    DatType type = type_T_CHOICE;
    type.has_pointers = 0;
    type.size = 12;
    type.native_size = sizeof(union PlainChoice);
    type.members = members;
    const DatType* local_types[T_COUNT];
    memcpy(local_types, types, sizeof types);
    local_types[T_CHOICE] = &type;
    DatType pointer = type_T_LEAF_P;
    pointer.target = T_CHOICE;
    DatType counted_pointer = type_T_COUNTED_LEAF_P;
    counted_pointer.count_tag = DAT_INT(1);
    local_types[T_LEAF_P] = &pointer;
    local_types[T_COUNTED_LEAF_P] = &counted_pointer;
    for (unsigned i = 0; i < 9; i++) {
        uint32_t kind = i % 3 == 2;
        uint32_t offset = i >= 6 ? 4 : 0;
        uint32_t data = (i % 3 == 0 ? 4 : 12) + offset;
        bool foreign = i % 3 == 1;
        unsigned char file[0x200] = { 0 };
        unsigned char* d = file + 32;
        put32(d, 4);
        put32(d + offset, 123);
        if (data - offset > 4) {
            put32(d + offset + 4, 456);
            put32(d + offset + 8, 0x3FC00000);
        }
        unsigned char* at = d + data;
        if (offset) {
            put32(at, 0);
            at += 4;
        }
        if (foreign) {
            put32(at, offset + 4);
            at += 4;
        }
        put32(at, 0), put32(at + 4, 0), at += 8;
        memcpy(at, "root", 5);
        at += 5;
        size_t size = (size_t) (at - file);
        put32(file, (uint32_t) size);
        put32(file + 4, data);
        put32(file + 8, foreign + (offset != 0));
        put32(file + 12, 1);
        const DatRootBind bind = { DAT_NAME_kind, kind };
        const DatRoot root = { .name = "root",
                               .type = offset ? T_COUNTED_LEAF_P : T_CHOICE,
                               .count_kind = i >= 3 && i < 6
                                                 ? DAT_COUNT_EXACTLY
                                                 : DAT_COUNT_ONE,
                               .count = 1,
                               .binds = &bind,
                               .nbinds = 1 };
        const DatFileRoots roots = { .file = "fixture",
                                     .roots = &root,
                                     .nroots = 1 };
        const DatModule module = { .files = &roots, .nfiles = 1 };
        DatSchema local_schema = schema;
        local_schema.types = local_types;
        local_schema.modules = &module;
        local_schema.nmodules = 1;
        DatArchive* a = dat_open(&local_schema, file, size, NULL);
        CHECK(a != NULL);
        CHECK(dat_load_roots(a, "fixture", 0) == 1);
        void* loaded = dat_public(a, "root", root.type);
        CHECK(loaded != NULL);
        union PlainChoice* value =
            offset && loaded != NULL ? *(union PlainChoice**) loaded : loaded;
        CHECK(value != NULL);
        char* text = trace(a);
        CHECK(!contains(text, "issue"));
        CHECK(contains(
            text, offset ? (kind ? "extent 0x4 0x10\n" : "extent 0x4 0x8\n")
                         : (kind ? "extent 0x0 0xC\n" : "extent 0x0 0x4\n")));
        CHECK(dat_verify(a, NULL) == 0);
        if (value != NULL) {
            if (kind) {
                CHECK(value->large.c == 456);
                value->large.c++;
            } else {
                CHECK(value->small == 123);
                value->small++;
            }
            CHECK(dat_verify(a, NULL) == 1);
        }
        free(text);
        dat_close(a);
    }
}

int main(void)
{
    test_walk();
    test_inline_counts();
    test_array_typedef_counts();
    test_conditional_counts();
    test_union_member_binding();
    test_byte_scripts();
    test_tagged_plain_union_size();
    test_vertex_arrays();
    test_vertex_extent_fallback();
    test_nbt3_indices();
    test_refuses();
    test_packed();
    printf("%s (%zu-bit %s-endian)\n", failures ? "FAILED" : "ok",
           sizeof(void*) * 8,
           *(const unsigned char*) &(const uint16_t){ 1 } ? "little" : "big");
    return failures ? 1 : 0;
}
