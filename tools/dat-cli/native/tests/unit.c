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
    T_S8,
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
};

#define SCALAR(name, kind, sign, raw, size, native, self)                     \
    { name,   self,     kind, sign, raw, 0, 0,        0,       size,          \
      native, DAT_NONE, self, 0,    0,   0, DAT_NONE, DAT_NONE }
#define POINTER(name, target, self)                                           \
    { name, self,     DAT_KIND_POINTER, 0,      0,    0, 1,                   \
      0,    4,        sizeof(void*),    target, self, 0, 0,                   \
      0,    DAT_NONE, DAT_NONE }

static const DatType types[] = {
    SCALAR("s8", DAT_KIND_INT, 1, 0, 1, 1, T_S8),
    SCALAR("s16", DAT_KIND_INT, 1, 0, 2, 2, T_S16),
    SCALAR("s32", DAT_KIND_INT, 1, 0, 4, 4, T_S32),
    SCALAR("f32", DAT_KIND_FLOAT, 0, 0, 4, 4, T_F32),
    { "Leaf", T_LEAF, DAT_KIND_STRUCT, 0, 0, 0, 0, 0, 12, sizeof(Leaf),
      DAT_NONE, T_LEAF, 0, 0, 4, DAT_NONE, DAT_NONE },
    POINTER("Leaf*", T_LEAF, T_LEAF_P),
    { "Node", T_NODE, DAT_KIND_STRUCT, 0, 0, 0, 1, 0, 0x20, sizeof(Node),
      DAT_NONE, T_NODE, 0, 4, 9, DAT_NONE, DAT_NONE },
    POINTER("Node*", T_NODE, T_NODE_P),
    SCALAR("u32", DAT_KIND_INT, 0, 0, 4, 4, T_U32),
    SCALAR("u8", DAT_KIND_INT, 0, 1, 1, 1, T_U8),
    POINTER("u8*", T_U8, T_U8_P),
    { "Choice", T_CHOICE, DAT_KIND_UNION, 0, 0, 0, 1, 0, 4,
      sizeof(union Choice), DAT_NONE, T_CHOICE, 0, 13, 2, DAT_NONE, DAT_NONE },
    SCALAR("unsigned int", DAT_KIND_INT, 0, 0, 4, sizeof(unsigned), T_UINT),
};

enum {
    N_N,
    N_KIND
};

static const char* const names[] = { "n", "kind", NULL };

static const DatExpr exprs[] = {
    /* 0: n */
    { DAT_OP_NAME, N_N, DAT_NONE, 0 },
    /* 1: kind, 2: 0, 3: kind == 0 */
    { DAT_OP_NAME, N_KIND, DAT_NONE, 0 },
    { DAT_OP_INT, DAT_NONE, DAT_NONE, 0 },
    { DAT_OP_EQ, 1, 2, 0 },
    /* 4: 1, 5: kind == 1 */
    { DAT_OP_INT, DAT_NONE, DAT_NONE, 1 },
    { DAT_OP_EQ, 1, 4, 0 },
};

#define FIELD(name, type, offset, native, nsize)                              \
    { name,     type,     offset,   0,        0,    1,                        \
      0,        native,   nsize,    NULL,     NULL, DAT_NONE,                 \
      DAT_NONE, DAT_NONE, DAT_NONE, DAT_NONE, 0,    0 }

static const DatMember members[] = {
    /* Leaf */
    FIELD(DAT_NONE, T_S8, 0, offsetof(Leaf, a), 1),
    FIELD(DAT_NONE, T_S16, 2, offsetof(Leaf, b), 2),
    FIELD(DAT_NONE, T_S32, 4, offsetof(Leaf, c), 4),
    FIELD(DAT_NONE, T_F32, 8, offsetof(Leaf, f), 4),
    /* Node */
    FIELD(DAT_NONE, T_NODE_P, 0, offsetof(Node, next), sizeof(void*)),
    FIELD(DAT_NONE, T_LEAF_P, 4, offsetof(Node, leaf), sizeof(void*)),
    /* DAT_COUNT(n) */
    { DAT_NONE, T_LEAF_P, 8, 0, 0, 1, 0, offsetof(Node, many), sizeof(void*),
      NULL, NULL, 0, DAT_NONE, DAT_NONE, DAT_NONE, DAT_NONE, 0, 0 },
    FIELD(N_N, T_U32, 0xC, offsetof(Node, n), 4),
    FIELD(DAT_NONE, T_U8_P, 0x10, offsetof(Node, raw), sizeof(void*)),
    FIELD(N_KIND, T_S32, 0x14, offsetof(Node, kind), 4),
    FIELD(DAT_NONE, T_CHOICE, 0x18, offsetof(Node, u), sizeof(union Choice)),
    { DAT_NONE, T_UINT, 0, 0x1C * 8, 3, 0, 0, 0, 0, set_flag, get_flag,
      DAT_NONE, DAT_NONE, DAT_NONE, DAT_NONE, DAT_NONE, 0, 0 },
    { DAT_NONE, T_UINT, 0, 0x1C * 8 + 3, 5, 0, 0, 0, 0, set_other, get_other,
      DAT_NONE, DAT_NONE, DAT_NONE, DAT_NONE, DAT_NONE, 0, 0 },
    /* Choice: DAT_IF(kind == 0), DAT_IF(kind == 1) */
    { DAT_NONE, T_LEAF_P, 0, 0, 0, 1, 0, 0, sizeof(void*), NULL, NULL,
      DAT_NONE, DAT_NONE, 3, DAT_NONE, DAT_NONE, 0, 0 },
    { DAT_NONE, T_NODE_P, 0, 0, 0, 1, 0, 0, sizeof(void*), NULL, NULL,
      DAT_NONE, DAT_NONE, 5, DAT_NONE, DAT_NONE, 0, 0 },
};

static const DatSchema schema = {
    types,   sizeof types / sizeof *types,
    members, exprs,
    NULL,    NULL,
    NULL,    names,
    2,       NULL,
    NULL,    NULL,
    0,
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

    FILE* out = tmpfile();
    dat_trace(a, out, DAT_TRACE_ALL);
    long n = ftell(out);
    rewind(out);
    char* text = calloc(1, (size_t) n + 1);
    if (fread(text, 1, (size_t) n, out) != (size_t) n) {
        CHECK(false);
    }
    fclose(out);
    CHECK(contains(text, "object 0x0 6 Node\n"));
    CHECK(contains(text, "object 0x20 6 Node\n"));
    CHECK(contains(text, "object 0x40 4 Leaf\n"));
    CHECK(contains(text, "object 0x70 9 u8\n"));
    CHECK(contains(text, "choice 0x18 11 0\n"));
    CHECK(contains(text, "choice 0x38 11 1\n"));
    CHECK(contains(text, "pointer 0x30\n"));
    CHECK(contains(text, "extent 0x40 0x58\n"));
    CHECK(contains(text, "sentinels 1\n"));
    CHECK(!contains(text, "issue"));
    free(text);
    dat_close(a);
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
    test_refuses();
    test_packed();
    printf("%s (%zu-bit %s-endian)\n", failures ? "FAILED" : "ok",
           sizeof(void*) * 8,
           *(const unsigned char*) &(const uint16_t){ 1 } ? "little" : "big");
    return failures ? 1 : 0;
}
