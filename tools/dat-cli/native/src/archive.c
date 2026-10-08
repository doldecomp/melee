/**
 * @file
 * The walk of `melee-dat`'s `walk.rs`, in C, converting as it goes.
 *
 * The walk is ported step for step, in the same order, so that it reaches
 * exactly what `melee-dat` does: dat_trace() prints what it reached for
 * comparing with `melee-dat native expect`. Where the walk lays a type over
 * the data, this also writes the native object it describes.
 */

#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <dat/archive.h>

/* --- Memory ---------------------------------------------------------------
 */

typedef struct Chunk {
    struct Chunk* next;
    size_t used, size;
    /* Aligned for any object the tables describe */
    _Alignas(16) unsigned char bytes[];
} Chunk;

typedef struct Arena {
    Chunk* chunks;
} Arena;

/// Zeroed memory that lives as long as the arena.
static void* arena_alloc(Arena* arena, size_t size)
{
    size = (size + 15) & ~(size_t) 15;
    if (size == 0) {
        size = 16;
    }
    Chunk* chunk = arena->chunks;
    if (chunk == NULL || chunk->size - chunk->used < size) {
        size_t want = size > (1 << 20) ? size : (1 << 20);
        chunk = calloc(1, sizeof(Chunk) + want);
        if (chunk == NULL) {
            abort();
        }
        chunk->size = want;
        chunk->next = arena->chunks;
        arena->chunks = chunk;
    }
    void* p = chunk->bytes + chunk->used;
    chunk->used += size;
    return p;
}

static void arena_free(Arena* arena)
{
    for (Chunk* c = arena->chunks; c != NULL;) {
        Chunk* next = c->next;
        free(c);
        c = next;
    }
    arena->chunks = NULL;
}

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

/// A set of offsets in the data.
typedef struct Bits {
    uint32_t* words;
} Bits;

static void bits_init(Bits* b, uint32_t size)
{
    b->words = calloc(size / 32 + 2, sizeof(uint32_t));
    if (b->words == NULL) {
        abort();
    }
}

static bool bits_has(const Bits* b, uint64_t at, uint32_t size)
{
    return at < size && (b->words[at / 32] >> (at % 32) & 1);
}

/// Insert; whether it was new.
static bool bits_set(Bits* b, uint64_t at, uint32_t size)
{
    if (at >= size || bits_has(b, at, size)) {
        return false;
    }
    b->words[at / 32] |= 1u << (at % 32);
    return true;
}

/// A hash map from 64-bit keys to 64-bit values; key `UINT64_MAX` is free.
typedef struct Map {
    uint64_t* keys;
    uint64_t* values;
    size_t len, cap;
} Map;

static uint64_t mix(uint64_t x)
{
    x ^= x >> 33;
    x *= 0xFF51AFD7ED558CCDull;
    x ^= x >> 33;
    x *= 0xC4CEB9FE1A85EC53ull;
    x ^= x >> 33;
    return x;
}

static void map_grow(Map* m);

static uint64_t* map_slot(Map* m, uint64_t key, bool insert)
{
    if (insert && (m->len + 1) * 2 > m->cap) {
        map_grow(m);
    }
    if (m->cap == 0) {
        return NULL;
    }
    size_t mask = m->cap - 1;
    for (size_t i = mix(key) & mask;; i = (i + 1) & mask) {
        if (m->keys[i] == key) {
            return &m->values[i];
        }
        if (m->keys[i] == UINT64_MAX) {
            if (!insert) {
                return NULL;
            }
            m->keys[i] = key;
            m->values[i] = 0;
            m->len++;
            return &m->values[i];
        }
    }
}

static void map_grow(Map* m)
{
    Map old = *m;
    m->cap = old.cap ? old.cap * 2 : 64;
    m->len = 0;
    m->keys = malloc(m->cap * sizeof(uint64_t));
    m->values = malloc(m->cap * sizeof(uint64_t));
    if (m->keys == NULL || m->values == NULL) {
        abort();
    }
    memset(m->keys, 0xFF, m->cap * sizeof(uint64_t));
    for (size_t i = 0; i < old.cap; i++) {
        if (old.keys[i] != UINT64_MAX) {
            *map_slot(m, old.keys[i], true) = old.values[i];
        }
    }
    free(old.keys);
    free(old.values);
}

static bool map_get(const Map* m, uint64_t key, uint64_t* value)
{
    uint64_t* slot = map_slot((Map*) m, key, false);
    if (slot != NULL && value != NULL) {
        *value = *slot;
    }
    return slot != NULL;
}

static void map_free(Map* m)
{
    free(m->keys);
    free(m->values);
}

static uint64_t key2(uint32_t offset, uint32_t id)
{
    return (uint64_t) offset << 32 | id;
}

/* --- The archive ----------------------------------------------------------
 */

typedef enum IssueKind {
    ISSUE_UNRELOCATED_POINTER,
    ISSUE_RELOCATED_SCALAR,
    ISSUE_OUT_OF_BOUNDS,
    ISSUE_AMBIGUOUS_UNION,
    ISSUE_UNKNOWN_COMMAND,
} IssueKind;

static const char* const issue_names[] = {
    "unrelocated-pointer", "relocated-scalar", "out-of-bounds",
    "ambiguous-union",     "unknown-command",
};

typedef struct Issue {
    uint8_t kind;
    uint32_t at;
    uint32_t value;
} Issue;

/// An expression value. If `bytes` is NULL, `i` is an integer.
/// Otherwise, `bytes` and `len` describe data for calls and bindings.
typedef struct Value {
    uint64_t i;
    const uint8_t* bytes;
    uint64_t len;
} Value;

/// Names bound by a root or `DAT_BIND`.
typedef struct Scope {
    int32_t name;
    Value value;
    const struct Scope* outer;
} Scope;

/// An object to walk: at `offset`, of `type`, with the bindings `env`.
/// Either its native object is already allocated (`native`, an element of
/// an array), or it is allocated when walked and stored to `slot`.
typedef struct Task {
    uint32_t offset;
    int32_t type;
    const Scope* env;
    void* native;
    void** slot;
} Task;

/// A native object to copy once every pointer has been stored: an element
/// already walked as another object.
typedef struct Copy {
    void* dst;
    const void* src;
    size_t size;
} Copy;

typedef struct Choice {
    uint32_t offset, id, index;
} Choice;

typedef struct Reached {
    uint32_t offset, id;
} Reached;

struct DatArchive {
    const DatSchema* s;
    uint8_t* data;
    uint32_t size;
    uint32_t* relocs;
    uint32_t nrelocs;
    struct {
        uint32_t offset;
        const char* name;
    } *publics, *externs;
    uint32_t npublics, nexterns;
    const char* names;
    uint32_t names_size;

    Bits reloc, extern_slot, public, target, object, script, pointer;
    /// (offset, type id) visited, as the walk's `visited`.
    Map visited;
    /// (offset, type id) → native object.
    Map natives;
    /// Native arrays' allocated element counts.
    Map native_counts;
    /// Native pointer slots → (target offset, type id), for array aliases.
    Map references;
    /// Native object → offset, for dat_verify().
    Map offsets;
    /// offset → furthest end.
    Map extents;
    Map choices;
    /// Counted inline arrays' lengths, for verification after leaving scope.
    Map array_counts;
    VEC(Reached) reached;
    VEC(Choice) chosen;
    VEC(Issue) issues;
    VEC(Task) queue;
    VEC(Copy) copies;
    bool native_moved;
    size_t untyped_pointers, sentinels;
    const Scope* env;
    /// Names the walk treats specially.
    int32_t name_index, name_command;
    Arena arena;
};

static uint32_t be32(const uint8_t* p)
{
    return (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
           (uint32_t) p[2] << 8 | p[3];
}

/// The word at `offset`, or 0 past the data.
static uint32_t word(const DatArchive* a, uint64_t offset)
{
    return offset + 4 <= a->size ? be32(a->data + offset) : 0;
}

/// `size` bytes from `offset`, big-endian, as an integer: the low 64 bits
/// of a larger one.
static uint64_t bytes_at(const DatArchive* a, uint64_t offset, uint32_t size)
{
    uint64_t v = 0;
    for (uint32_t i = 0; i < size; i++) {
        v = v << 8 | a->data[offset + i];
    }
    return v;
}

static const char* symbol_at(const uint8_t* table, uint32_t size,
                             uint32_t offset)
{
    if (offset >= size) {
        return NULL;
    }
    if (memchr(table + offset, 0, size - offset) == NULL) {
        return NULL;
    }
    return (const char*) table + offset;
}

DatArchive* dat_open(const DatSchema* schema, const void* bytes, size_t size,
                     const char** error)
{
    const uint8_t* b = bytes;
    const char* why = NULL;
    if (size < 0x20) {
        why = "shorter than its header";
        goto fail;
    }
    uint32_t file_size = be32(b), data_size = be32(b + 4),
             nrelocs = be32(b + 8), npublics = be32(b + 12),
             nexterns = be32(b + 16);
    /* HSD_ArchiveParse's byte-order check */
    if (file_size != size) {
        why = "its size isn't the file's";
        goto fail;
    }
    uint64_t tables = 0x20 + (uint64_t) data_size + 4ull * nrelocs +
                      8ull * npublics + 8ull * nexterns;
    if (tables > size) {
        why = "its tables extend past the file";
        goto fail;
    }
    DatArchive* a = calloc(1, sizeof(DatArchive));
    if (a == NULL) {
        abort();
    }
    a->s = schema;
    a->size = data_size;
    a->data = malloc(data_size + 1);
    memcpy(a->data, b + 0x20, data_size);
    const uint8_t* at = b + 0x20 + data_size;
    a->relocs = malloc((nrelocs + 1) * sizeof(uint32_t));
    a->nrelocs = nrelocs;
    for (uint32_t i = 0; i < nrelocs; i++, at += 4) {
        a->relocs[i] = be32(at);
    }
    const uint8_t* publics = at;
    const uint8_t* externs = publics + 8 * npublics;
    const uint8_t* names = externs + 8 * nexterns;
    uint32_t names_size = (uint32_t) (b + size - names);
    a->names = malloc(names_size + 1);
    memcpy((char*) a->names, names, names_size);
    a->names_size = names_size;
    a->publics = malloc((npublics + 1) * sizeof(*a->publics));
    a->externs = malloc((nexterns + 1) * sizeof(*a->externs));
    a->npublics = npublics;
    a->nexterns = nexterns;
    for (uint32_t i = 0; i < npublics; i++) {
        a->publics[i].offset = be32(publics + 8 * i);
        a->publics[i].name = symbol_at((const uint8_t*) a->names, names_size,
                                       be32(publics + 8 * i + 4));
    }
    for (uint32_t i = 0; i < nexterns; i++) {
        a->externs[i].offset = be32(externs + 8 * i);
        a->externs[i].name = symbol_at((const uint8_t*) a->names, names_size,
                                       be32(externs + 8 * i + 4));
    }
    /* What Archive::parse refuses */
    for (uint32_t i = 0; i < nrelocs && why == NULL; i++) {
        if (a->relocs[i] > UINT32_MAX - 4 || a->relocs[i] + 4 > data_size) {
            why = "a relocation is outside the data";
        }
    }
    for (uint32_t i = 0; i < npublics && why == NULL; i++) {
        if (a->publics[i].name == NULL) {
            why = "a public symbol's name is outside the symbol table";
        } else if (a->publics[i].offset > data_size) {
            why = "a public symbol is outside the data";
        }
    }
    for (uint32_t i = 0; i < nexterns && why == NULL; i++) {
        if (a->externs[i].name == NULL) {
            why = "an extern's name is outside the symbol table";
        }
    }
    if (why != NULL) {
        dat_close(a);
        goto fail;
    }

    bits_init(&a->reloc, data_size);
    bits_init(&a->extern_slot, data_size);
    bits_init(&a->public, data_size);
    bits_init(&a->target, data_size);
    bits_init(&a->object, data_size);
    bits_init(&a->script, data_size);
    bits_init(&a->pointer, data_size);
    for (uint32_t i = 0; i < nrelocs; i++) {
        bits_set(&a->reloc, a->relocs[i], data_size);
        bits_set(&a->target, word(a, a->relocs[i]), data_size);
    }
    for (uint32_t i = 0; i < npublics; i++) {
        bits_set(&a->public, a->publics[i].offset, data_size);
    }
    /* HSD_ArchiveLocateExtern: a chain through the words, each holding the
       next offset, until -1 or the end of the data */
    for (uint32_t i = 0; i < nexterns; i++) {
        uint32_t offset = a->externs[i].offset;
        while (offset != UINT32_MAX && (uint64_t) offset + 4 <= data_size &&
               bits_set(&a->extern_slot, offset, data_size))
        {
            offset = word(a, offset);
        }
    }
    a->name_index = a->name_command = DAT_NONE;
    for (uint32_t i = 1; i < schema->nnames; i++) {
        if (strcmp(schema->names[i], "_index") == 0) {
            a->name_index = (int32_t) i;
        } else if (strcmp(schema->names[i], "_command") == 0) {
            a->name_command = (int32_t) i;
        }
    }
    return a;

fail:
    if (error != NULL) {
        *error = why;
    }
    return NULL;
}

int dat_open_packed(const DatSchema* schema, const void* bytes, size_t size,
                    DatArchive** out, size_t* offsets, int max,
                    const char** error)
{
    const uint8_t* b = bytes;
    size_t offset = 0;
    int n = 0;
    while (offset < size) {
        if (size - offset < 0x20) {
            if (error != NULL) {
                *error = "an archive is shorter than its header";
            }
            goto fail;
        }
        size_t file_size = be32(b + offset);
        if (file_size == 0 || file_size > size - offset) {
            if (error != NULL) {
                *error = "an archive's size is outside the file";
            }
            goto fail;
        }
        if (n == max) {
            break;
        }
        if (offsets != NULL) {
            offsets[n] = offset;
        }
        out[n] = dat_open(schema, b + offset, file_size, error);
        if (out[n] == NULL) {
            goto fail;
        }
        n++;
        offset += (file_size + 31) & ~(size_t) 31;
    }
    return n;

fail:
    while (n > 0) {
        dat_close(out[--n]);
    }
    return -1;
}

void dat_close(DatArchive* a)
{
    if (a == NULL) {
        return;
    }
    free(a->data);
    free(a->relocs);
    free(a->publics);
    free(a->externs);
    free((char*) a->names);
    free(a->reloc.words);
    free(a->extern_slot.words);
    free(a->public.words);
    free(a->target.words);
    free(a->object.words);
    free(a->script.words);
    free(a->pointer.words);
    map_free(&a->visited);
    map_free(&a->natives);
    map_free(&a->native_counts);
    map_free(&a->references);
    map_free(&a->offsets);
    map_free(&a->extents);
    map_free(&a->choices);
    map_free(&a->array_counts);
    free(a->reached.items);
    free(a->chosen.items);
    free(a->issues.items);
    free(a->queue.items);
    free(a->copies.items);
    arena_free(&a->arena);
    free(a);
}

const uint8_t* dat_raw(const DatArchive* a, uint32_t offset)
{
    return a->data + offset;
}

uint32_t dat_size(const DatArchive* a)
{
    return a->size;
}

int32_t dat_type_by_id(const DatSchema* s, uint32_t id)
{
    for (uint32_t i = 1; i < s->ntypes; i++) {
        if (s->types[i]->id == id) {
            return (int32_t) i;
        }
    }
    return DAT_NONE;
}

/* --- Types ----------------------------------------------------------------
 */

static const DatType* T(const DatArchive* a, int32_t type)
{
    return a->s->types[type];
}

static int32_t resolve(const DatArchive* a, int32_t type)
{
    return type == DAT_NONE ? DAT_NONE : T(a, type)->resolved;
}

/// What a pointer points to, if it can be followed: not `void`, functions
/// or undefined types.
static int32_t pointee(const DatArchive* a, int32_t target)
{
    int32_t r = resolve(a, target);
    if (r == DAT_NONE || T(a, r)->kind == DAT_KIND_VOID) {
        return DAT_NONE;
    }
    return r;
}

/// A `DAT_TERMINATED` value on a typedef, or one it names, and its length.
static const DatExpr* typedef_terminator(const DatArchive* a, int32_t type,
                                         uint32_t* length)
{
    while (type != DAT_NONE && T(a, type)->kind == DAT_KIND_TYPEDEF) {
        if (T(a, type)->terminator != NULL) {
            *length = T(a, type)->terminator_length;
            return T(a, type)->terminator;
        }
        type = T(a, type)->target;
    }
    return NULL;
}

/// A `DAT_COUNT` on a pointer typedef, or one it names.
static const DatExpr* typedef_count(const DatArchive* a, int32_t type)
{
    while (type != DAT_NONE && T(a, type)->kind == DAT_KIND_TYPEDEF) {
        if (T(a, type)->count_tag != NULL) {
            return T(a, type)->count_tag;
        }
        type = T(a, type)->target;
    }
    return NULL;
}

/// Find a script annotation on a pointer typedef, following typedef aliases.
static const DatScript* typedef_script(const DatArchive* a, int32_t type)
{
    while (type != DAT_NONE && T(a, type)->kind == DAT_KIND_TYPEDEF) {
        if (T(a, type)->script != NULL) {
            return T(a, type)->script;
        }
        type = T(a, type)->target;
    }
    return NULL;
}

/// The type a `DAT_TYPE` typedef on the way to the type refers to.
static int32_t typedef_type(const DatArchive* a, int32_t type)
{
    while (type != DAT_NONE && T(a, type)->kind == DAT_KIND_TYPEDEF) {
        if (T(a, type)->type_tag != DAT_NONE) {
            return T(a, type)->type_tag;
        }
        type = T(a, type)->target;
    }
    return DAT_NONE;
}

/// Data with no conversion: raw bytes, or a `DAT_BLOB` format, which
/// natively stay as they are in the data.
static bool opaque(const DatArchive* a, int32_t type)
{
    for (; type != DAT_NONE; type = T(a, type)->target) {
        const DatType* t = T(a, type);
        if (t->raw || t->blob) {
            return true;
        }
        if (t->kind != DAT_KIND_TYPEDEF && t->kind != DAT_KIND_QUALIFIER) {
            return false;
        }
    }
    return false;
}

static uint32_t native_size(const DatArchive* a, int32_t type)
{
    int32_t r = resolve(a, type);
    return r == DAT_NONE ? 0 : T(a, r)->native_size;
}

/* --- Native values --------------------------------------------------------
 */

static void store_uint(void* dst, uint32_t size, uint64_t v)
{
    switch (size) {
    case 1: {
        uint8_t x = (uint8_t) v;
        memcpy(dst, &x, 1);
        break;
    }
    case 2: {
        uint16_t x = (uint16_t) v;
        memcpy(dst, &x, 2);
        break;
    }
    case 4: {
        uint32_t x = (uint32_t) v;
        memcpy(dst, &x, 4);
        break;
    }
    case 8:
        memcpy(dst, &v, 8);
        break;
    default:
        break;
    }
}

static uint64_t load_uint(const void* src, uint32_t size)
{
    switch (size) {
    case 1: {
        uint8_t x;
        memcpy(&x, src, 1);
        return x;
    }
    case 2: {
        uint16_t x;
        memcpy(&x, src, 2);
        return x;
    }
    case 4: {
        uint32_t x;
        memcpy(&x, src, 4);
        return x;
    }
    case 8: {
        uint64_t x;
        memcpy(&x, src, 8);
        return x;
    }
    default:
        return 0;
    }
}

/// An integer of `size` bytes as a value of `bits`, sign-extended if
/// `is_signed`.
static uint64_t extend(uint64_t v, uint32_t bits, bool is_signed)
{
    if (bits >= 64) {
        return v;
    }
    v &= (1ull << bits) - 1;
    if (is_signed && bits > 0 && (v >> (bits - 1) & 1)) {
        v |= ~0ull << bits;
    }
    return v;
}

/// The scalar of type `r` (resolved) at `offset`, written natively.
static void convert_scalar(const DatArchive* a, uint32_t offset, int32_t r,
                           void* native)
{
    const DatType* t = T(a, r);
    if (native == NULL || (uint64_t) offset + t->size > a->size) {
        return;
    }
    uint32_t nsize = t->native_size ? t->native_size : t->size;
    uint64_t v = bytes_at(a, offset, t->size);
    if (t->kind == DAT_KIND_FLOAT) {
        if (t->size == 4 && nsize == sizeof(float)) {
            uint32_t bits = (uint32_t) v;
            float f;
            memcpy(&f, &bits, 4);
            memcpy(native, &f, sizeof f);
        } else if (t->size == 8 && nsize == sizeof(double)) {
            double d;
            memcpy(&d, &v, 8);
            memcpy(native, &d, sizeof d);
        } else if (t->size == 4 && nsize == sizeof(double)) {
            uint32_t bits = (uint32_t) v;
            float f;
            memcpy(&f, &bits, 4);
            double d = f;
            memcpy(native, &d, sizeof d);
        }
        return;
    }
    store_uint(native, nsize, extend(v, 8 * t->size, t->is_signed));
}

/// Bits `start` to `start + bits` of the data from `offset`, counted from
/// the most significant bit of its first byte.
static uint64_t bits_at(const DatArchive* a, uint64_t offset, uint64_t start,
                        uint32_t bits)
{
    uint64_t v = 0;
    for (uint64_t bit = start; bit < start + bits; bit++) {
        uint64_t at = offset + bit / 8;
        uint8_t byte = at < a->size ? a->data[at] : 0;
        v = v << 1 | (byte >> (7 - bit % 8) & 1);
    }
    return v;
}

static void convert_bitfield(const DatArchive* a, uint32_t offset,
                             const DatMember* m, void* native)
{
    if (native == NULL || m->set_bits == NULL) {
        return;
    }
    int32_t r = resolve(a, m->type);
    bool is_signed = r != DAT_NONE && T(a, r)->is_signed;
    uint64_t v = bits_at(a, offset, m->bit_offset, m->bit_size);
    m->set_bits(native, extend(v, m->bit_size, is_signed));
}

static void store_pointer(void* slot, const void* p)
{
    if (slot != NULL) {
        memcpy(slot, &p, sizeof p);
    }
}

/// A pointer the data doesn't relocate, natively: null for null and
/// externs (which the loader leaves null), -1 kept as -1, and anything else
/// as its value.
static void* unrelocated_value(const DatArchive* a, uint32_t offset,
                               uint32_t value)
{
    if (bits_has(&a->extern_slot, offset, a->size) || value == 0) {
        return NULL;
    }
    if (value == UINT32_MAX) {
        return (void*) (intptr_t) -1;
    }
    return (void*) (uintptr_t) value;
}

/// The member of a union to convert when nothing chooses one: the
/// largest, which holds every byte.
static const DatMember* largest(const DatArchive* a, const DatType* u)
{
    const DatMember* best = NULL;
    uint32_t size = 0;
    for (uint32_t i = 0; i < u->nmembers; i++) {
        const DatMember* m = &u->members[i];
        int32_t r = resolve(a, m->type);
        uint32_t ms = r == DAT_NONE ? 0 : T(a, r)->size;
        if (best == NULL || ms > size) {
            best = m;
            size = ms;
        }
    }
    return best;
}

/// Convert plain data, which has no pointers to follow.
static void convert(DatArchive* a, uint32_t offset, int32_t type, void* native)
{
    int32_t r = resolve(a, type);
    if (native == NULL || r == DAT_NONE) {
        return;
    }
    const DatType* t = T(a, r);
    switch (t->kind) {
    case DAT_KIND_INT:
    case DAT_KIND_FLOAT:
        convert_scalar(a, offset, r, native);
        break;
    case DAT_KIND_STRUCT:
        for (uint32_t i = 0; i < t->nmembers; i++) {
            const DatMember* m = &t->members[i];
            if (m->bit_size) {
                convert_bitfield(a, offset, m, native);
            } else if (m->has_offset && m->type != DAT_NONE) {
                convert(a, offset + m->offset, m->type,
                        (char*) native + m->native_offset);
            }
        }
        break;
    case DAT_KIND_UNION: {
        const DatMember* m = largest(a, t);
        if (m != NULL && m->type != DAT_NONE) {
            convert(a, offset, m->type, native);
        }
        break;
    }
    case DAT_KIND_ARRAY: {
        int32_t e = resolve(a, t->target);
        if (e == DAT_NONE) {
            break;
        }
        for (uint32_t i = 0; i < t->count; i++) {
            convert(a, offset + i * T(a, e)->size, e,
                    (char*) native + (size_t) i * T(a, e)->native_size);
        }
        break;
    }
    default:
        break;
    }
}

/* --- Expressions ----------------------------------------------------------
 */

typedef enum Mode {
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
} Mode;

typedef struct Context {
    Mode mode;
    /// The record the fields are of, and where it is.
    int32_t record;
    uint32_t base;
    /// MODE_IF: the union.
    int32_t onion;
    uint32_t union_base;
    const Scope* env;
    uint64_t index, command;
} Context;

static bool lookup(const Scope* env, int32_t name, Value* out)
{
    for (; env != NULL; env = env->outer) {
        if (env->name == name) {
            *out = env->value;
            return true;
        }
    }
    return false;
}

static bool eval(const DatArchive* a, const Context* c, const DatExpr* e,
                 uint64_t* out);
static uint64_t terminated_count(const DatArchive* a, uint32_t offset,
                                 int32_t type, uint64_t term);

/// Return the bytes referenced by relocated pointer member `m` at `at`.
/// Its `DAT_COUNT` or `DAT_TERMINATED` gives the length, as in the walk.
static bool pointed_bytes(const DatArchive* a, const DatMember* m,
                          int32_t record, uint32_t base, uint64_t at,
                          Value* out)
{
    int32_t p = resolve(a, m->type);
    if (p == DAT_NONE || T(a, p)->kind != DAT_KIND_POINTER ||
        at + 4 > a->size || !bits_has(&a->reloc, at, a->size))
    {
        return false;
    }
    uint32_t value = word(a, at);
    if (value > a->size) {
        return false;
    }
    int32_t e = pointee(a, T(a, p)->target);
    if (e == DAT_NONE) {
        return false;
    }
    uint64_t size = T(a, e)->size;
    uint64_t count;
    if (m->terminator != NULL) {
        Context c = {
            MODE_TERMINATOR, DAT_NONE, 0, DAT_NONE, 0, a->env, 0, 0
        };
        uint64_t term;
        if (size == 0 || !eval(a, &c, m->terminator, &term)) {
            return false;
        }
        uint64_t room = a->size > value ? (a->size - value) / size : 0;
        uint32_t length = m->terminator_length ? m->terminator_length : 1;
        count = terminated_count(a, value, e, term) + length - 1;
        count = count < room ? count : room;
    } else {
        Context c = { MODE_COUNT, record, base, DAT_NONE, 0, a->env, 0, 0 };
        if (m->count == NULL || !eval(a, &c, m->count, &count)) {
            return false;
        }
    }
    if (size != 0 && count > (a->size - value) / size) {
        return false;
    }
    out->i = 0;
    out->bytes = a->data + value;
    out->len = count * size;
    return true;
}

/// Read a field by name from the record at `base`.
/// Scalars are big-endian; floats convert to integers as C would.
/// Annotated pointers can resolve to the bytes they reference.
static bool field_value(const DatArchive* a, int32_t record, uint32_t base,
                        int32_t name, Value* out)
{
    if (record == DAT_NONE) {
        return false;
    }
    const DatType* t = T(a, record);
    if (t->kind != DAT_KIND_STRUCT && t->kind != DAT_KIND_UNION) {
        return false;
    }
    const DatMember* m = NULL;
    /* A member of a nested record, `x0.count`: by the name's text */
    const char* full = a->s->names[name];
    const char* dot = strchr(full, '.');
    if (dot != NULL) {
        size_t len = (size_t) (dot - full);
        for (uint32_t i = 0; i < t->nmembers; i++) {
            const DatMember* c = &t->members[i];
            if (c->name != DAT_NONE &&
                strncmp(a->s->names[c->name], full, len) == 0 &&
                a->s->names[c->name][len] == '\0')
            {
                m = c;
                break;
            }
        }
        if (m == NULL || !m->has_offset || m->type == DAT_NONE) {
            return false;
        }
        for (uint32_t i = 1; i < a->s->nnames; i++) {
            if (strcmp(a->s->names[i], dot + 1) == 0) {
                return field_value(a, resolve(a, m->type), base + m->offset,
                                   (int32_t) i, out);
            }
        }
        return false;
    }
    for (uint32_t i = 0; i < t->nmembers; i++) {
        if (t->members[i].name == name) {
            m = &t->members[i];
            break;
        }
    }
    if (m == NULL || !m->has_offset || m->type == DAT_NONE) {
        return false;
    }
    uint64_t at = (uint64_t) base + m->offset;
    if (pointed_bytes(a, m, record, base, at, out)) {
        return true;
    }
    int32_t r = resolve(a, m->type);
    if (r == DAT_NONE) {
        return false;
    }
    uint32_t size = T(a, m->type)->size;
    if (at + size > a->size) {
        return false;
    }
    uint64_t v = bytes_at(a, at, size);
    if (T(a, r)->kind == DAT_KIND_FLOAT) {
        /* Rust's `as`: toward zero, saturating, NaN to zero */
        double d;
        if (size == 4) {
            uint32_t bits = (uint32_t) v;
            float f;
            memcpy(&f, &bits, 4);
            d = f;
        } else if (size == 8) {
            memcpy(&d, &v, 8);
        } else {
            return false;
        }
        int64_t i;
        if (isnan(d)) {
            i = 0;
        } else if (d >= 9223372036854775808.0) {
            i = INT64_MAX;
        } else if (d < -9223372036854775808.0) {
            i = INT64_MIN;
        } else {
            i = (int64_t) d;
        }
        v = (uint64_t) i;
    }
    *out = (Value){ v, NULL, 0 };
    return true;
}

static bool resolve_name(const DatArchive* a, const Context* c, int32_t name,
                         Value* out)
{
    switch (c->mode) {
    case MODE_COUNT:
        return field_value(a, c->record, c->base, name, out) ||
               lookup(c->env, name, out);
    case MODE_IF: {
        if (field_value(a, c->record, c->base, name, out)) {
            return true;
        }
        const DatType* u = T(a, c->onion);
        for (uint32_t i = 0; i < u->nmembers; i++) {
            const DatMember* m = &u->members[i];
            if (field_value(a, resolve(a, m->type), c->union_base, name, out))
            {
                return true;
            }
        }
        return lookup(c->env, name, out);
    }
    case MODE_BIND:
        if (name == a->name_index) {
            *out = (Value){ c->index, NULL, 0 };
            return true;
        }
        return field_value(a, c->record, c->base, name, out) ||
               lookup(c->env, name, out);
    case MODE_TERMINATOR:
        return lookup(c->env, name, out);
    case MODE_SCRIPT:
        if (name == a->name_command) {
            *out = (Value){ c->command, NULL, 0 };
            return true;
        }
        return false;
    }
    return false;
}

/// See `col_anim_command_length` in `expr.rs`.
static bool col_anim_command_length(uint64_t command, uint64_t* out)
{
    static const uint8_t own[11] = { 0, 1, 1, 2, 2, 2, 1, 1, 2, 2, 1 };
    uint64_t opcode = (command >> 26) & 0x3F;
    if (opcode >= 10 && opcode <= 20) {
        *out = own[opcode - 10];
        return true;
    }
    switch (opcode) {
    case 21:
        *out = 5;
        return true;
    case 22:
        *out = 3;
        return true;
    case 23:
        *out = 1;
        return true;
    default:
        return false;
    }
}

/// See `cpu_command_length` in `expr.rs`.
static uint64_t cpu_command_length(uint64_t command)
{
    uint8_t c = (uint8_t) command;
    return c == 0x7F ? 0 : c >= 0xC0 ? 3 : c >= 0x80 ? 2 : 1;
}

static bool it_command_length(uint64_t command, uint64_t* out)
{
    uint64_t opcode = (command >> 26) & 0x3F;
    uint64_t sub = (command >> 18) & 0xFF;
    switch (opcode) {
    case 10:
        *out = 5;
        return true;
    case 11:
        *out = 6;
        return true;
    case 16:
        *out = (sub <= 2 || sub == 10 || sub == 11) ? 3 : 2;
        return true;
    default:
        if (opcode >= 12 && opcode <= 25) {
            *out = 1;
            return true;
        }
        return false;
    }
}

/// `GXGetTexBufferSize`, as `melee-dat` ports it.
static bool gx_get_tex_buffer_size(uint16_t width, uint16_t height,
                                   uint32_t format, uint8_t mipmap,
                                   uint8_t max_lod, uint64_t* out)
{
    uint32_t sx, sy;
    switch (format) {
    case 0x0:
    case 0x8:
    case 0xE:
    case 0x20:
    case 0x30:
        sx = 3, sy = 3;
        break;
    case 0x1:
    case 0x2:
    case 0x9:
    case 0x11:
    case 0x22:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x39:
    case 0x3A:
        sx = 3, sy = 2;
        break;
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0xA:
    case 0x13:
    case 0x16:
    case 0x23:
    case 0x2B:
    case 0x2C:
    case 0x3C:
        sx = 2, sy = 2;
        break;
    default:
        return false;
    }
    uint32_t tile = (format == 0x6 || format == 0x16) ? 64 : 32;
#define TILES(w, h)                                                           \
    (tile * (((uint32_t) (w) + (1u << sx) - 1) >> sx) *                       \
     (((uint32_t) (h) + (1u << sy) - 1) >> sy))
    if (mipmap != 1) {
        *out = TILES(width, height);
        return true;
    }
    uint32_t size = 0;
    for (uint32_t i = 0; i < max_lod; i++) {
        size += TILES(width, height);
        if (width == 1 && height == 1) {
            break;
        }
        width = width >> 1 ? width >> 1 : 1;
        height = height >> 1 ? height >> 1 : 1;
    }
#undef TILES
    *out = size;
    return true;
}

/// The bytes a direct attribute takes in a vertex, by its `GXCompCnt` and
/// `GXCompType`; 0 for one not known.
static uint32_t gx_direct_size(uint32_t attr, uint32_t cnt, uint32_t comp)
{
    static const uint8_t colors[6] = { 2, 3, 4, 2, 3, 4 };
    uint32_t scalar = comp <= 1 ? 1 : comp <= 3 ? 2 : comp == 4 ? 4 : 0;
    if (attr <= 8) {
        return 1;
    }
    switch (attr) {
    case 9:
        return scalar * (cnt == 0 ? 2 : 3);
    case 10:
    case 25:
        return scalar * (cnt == 0 ? 3 : 9);
    case 11:
    case 12:
        return comp < 6 ? colors[comp] : 0;
    default:
        return attr >= 13 && attr <= 20 ? scalar * (cnt == 0 ? 1 : 2) : 0;
    }
}

/// See `gx_max_index` in `expr.rs`.
static bool gx_max_index(const uint8_t* dl, uint64_t dl_len,
                         const uint8_t* descs, uint64_t descs_len,
                         uint64_t attr, uint64_t* out)
{
    enum {
        DESC_SIZE = 0x18,
        MAX_ATTRS = 32
    };
    /* Each attribute present: its place in a vertex, its bytes in a vertex,
       and its indices' width and number, if indexed */
    struct {
        uint32_t order, width, count;
        bool target;
    } attrs[MAX_ATTRS];
    uint32_t n = 0;
    for (uint64_t at = 0; at + DESC_SIZE <= descs_len; at += DESC_SIZE) {
        uint32_t at_ = be32(descs + at), ty = be32(descs + at + 4),
                 cnt = be32(descs + at + 8), comp = be32(descs + at + 12);
        if (at_ == 0xFF) {
            break;
        }
        uint32_t indices = (at_ == 10 || at_ == 25) && cnt == 2 ? 3 : 1;
        uint32_t width, count;
        switch (ty) {
        case 0:
            continue;
        case 1:
            width = gx_direct_size(at_, cnt, comp);
            count = 0;
            if (width == 0) {
                return false;
            }
            break;
        case 2:
        case 3:
            width = ty - 1;
            count = indices;
            break;
        default:
            return false;
        }
        if (n == MAX_ATTRS) {
            return false;
        }
        /* Stable, as Rust's sort */
        uint32_t order = at_ == 25 ? 10 : at_;
        uint32_t i = n++;
        for (; i > 0 && attrs[i - 1].order > order; i--) {
            attrs[i] = attrs[i - 1];
        }
        attrs[i].order = order;
        attrs[i].width = width;
        attrs[i].count = count;
        attrs[i].target = at_ == attr;
    }
    bool found = false;
    uint64_t max = 0;
    uint64_t at = 0;
    while (at < dl_len) {
        uint8_t opcode = dl[at];
        if (opcode == 0) {
            break;
        }
        switch (opcode & 0xF8) {
        case 0x80:
        case 0x90:
        case 0x98:
        case 0xA0:
        case 0xA8:
        case 0xB0:
        case 0xB8:
            break;
        default:
            return false;
        }
        if (at + 3 > dl_len) {
            return false;
        }
        uint32_t vertices = (uint32_t) dl[at + 1] << 8 | dl[at + 2];
        at += 3;
        for (uint32_t v = 0; v < vertices; v++) {
            for (uint32_t i = 0; i < n; i++) {
                uint64_t size = (uint64_t) attrs[i].width *
                                (attrs[i].count > 0 ? attrs[i].count : 1);
                if (at + size > dl_len) {
                    return false;
                }
                for (uint32_t k = 0; attrs[i].target && k < attrs[i].count;
                     k++)
                {
                    const uint8_t* p = dl + at + k * attrs[i].width;
                    uint64_t index = attrs[i].width == 2
                                         ? (uint64_t) p[0] << 8 | p[1]
                                         : p[0];
                    if (!found || index > max) {
                        max = index;
                    }
                    found = true;
                }
                at += size;
            }
        }
    }
    *out = max;
    return found;
}

/// How deep a name's macro is expanded within macros, as `melee-dat`
/// expands them.
#define MACRO_DEPTH 16

static bool eval_at(const DatArchive* a, const Context* c, const DatExpr* e,
                    unsigned depth, Value* out);

/// An operand, which must be an integer.
static bool eval_int(const DatArchive* a, const Context* c, const DatExpr* e,
                     unsigned depth, uint64_t* out)
{
    Value v;
    if (!eval_at(a, c, e, depth, &v) || v.bytes != NULL) {
        return false;
    }
    *out = v.i;
    return true;
}

static bool eval_at(const DatArchive* a, const Context* c, const DatExpr* e,
                    unsigned depth, Value* out)
{
    if (e == NULL) {
        return false;
    }
    *out = (Value){ 0, NULL, 0 };
    uint64_t x, y;
    switch (e->op) {
    case DAT_OP_INT:
        out->i = e->value;
        return true;
    case DAT_OP_NAME:
        return resolve_name(a, c, e->name, out) ||
               (depth < MACRO_DEPTH && eval_at(a, c, e->b, depth + 1, out));
    case DAT_OP_FAIL:
        return false;
    case DAT_OP_CALL: {
        Value args[8];
        if (e->nargs > 8) {
            return false;
        }
        for (uint8_t i = 0; i < e->nargs; i++) {
            if (!eval_at(a, c, e->args[i], depth, &args[i])) {
                return false;
            }
        }
        /* Which arguments are bytes, a bit each */
        unsigned bytes = 0;
        for (uint8_t i = 0; i < e->nargs; i++) {
            bytes |= (args[i].bytes != NULL) << i;
        }
        switch (e->function) {
        case DAT_FN_IT_COMMAND_LENGTH:
            return e->nargs == 1 && bytes == 0 &&
                   it_command_length(args[0].i, &out->i);
        case DAT_FN_COL_ANIM_COMMAND_LENGTH:
            return e->nargs == 1 && bytes == 0 &&
                   col_anim_command_length(args[0].i, &out->i);
        case DAT_FN_CPU_COMMAND_LENGTH:
            if (e->nargs != 1 || bytes != 0) {
                return false;
            }
            out->i = cpu_command_length(args[0].i);
            return true;
        case DAT_FN_GX_GET_TEX_BUFFER_SIZE:
            return e->nargs == 5 && bytes == 0 &&
                   gx_get_tex_buffer_size(
                       (uint16_t) args[0].i, (uint16_t) args[1].i,
                       (uint32_t) args[2].i, (uint8_t) args[3].i,
                       (uint8_t) args[4].i, &out->i);
        case DAT_FN_GX_MAX_INDEX:
            return e->nargs == 3 && bytes == 3 &&
                   gx_max_index(args[0].bytes, args[0].len, args[1].bytes,
                                args[1].len, args[2].i, &out->i);
        default:
            return false;
        }
    }
    case DAT_OP_NOT:
    case DAT_OP_BITNOT:
    case DAT_OP_NEG:
        if (!eval_int(a, c, e->a, depth, &x)) {
            return false;
        }
        out->i = e->op == DAT_OP_NOT      ? (x == 0)
                 : e->op == DAT_OP_BITNOT ? ~x
                                          : (uint64_t) 0 - x;
        return true;
    case DAT_OP_COND:
        if (!eval_int(a, c, e->cond, depth, &x)) {
            return false;
        }
        return eval_at(a, c, x != 0 ? e->a : e->b, depth, out);
    default:
        break;
    }
    if (!eval_int(a, c, e->a, depth, &x)) {
        return false;
    }
    /* Short-circuit like C, so the other side may be unresolved */
    if (e->op == DAT_OP_OR && x != 0) {
        out->i = 1;
        return true;
    }
    if (e->op == DAT_OP_AND && x == 0) {
        out->i = 0;
        return true;
    }
    if (!eval_int(a, c, e->b, depth, &y)) {
        return false;
    }
    switch (e->op) {
    case DAT_OP_OR:
    case DAT_OP_AND:
        out->i = y != 0;
        return true;
    case DAT_OP_BITOR:
        out->i = x | y;
        return true;
    case DAT_OP_BITXOR:
        out->i = x ^ y;
        return true;
    case DAT_OP_BITAND:
        out->i = x & y;
        return true;
    case DAT_OP_EQ:
        out->i = x == y;
        return true;
    case DAT_OP_NE:
        out->i = x != y;
        return true;
    case DAT_OP_LT:
        out->i = x < y;
        return true;
    case DAT_OP_GT:
        out->i = x > y;
        return true;
    case DAT_OP_LE:
        out->i = x <= y;
        return true;
    case DAT_OP_GE:
        out->i = x >= y;
        return true;
    case DAT_OP_SHL:
        if (y >= 64) {
            return false;
        }
        out->i = x << y;
        return true;
    case DAT_OP_SHR:
        if (y >= 64) {
            return false;
        }
        out->i = x >> y;
        return true;
    case DAT_OP_ADD:
        out->i = x + y;
        return true;
    case DAT_OP_SUB:
        out->i = x - y;
        return true;
    case DAT_OP_MUL:
        out->i = x * y;
        return true;
    case DAT_OP_DIV:
        if (y == 0) {
            return false;
        }
        out->i = x / y;
        return true;
    case DAT_OP_REM:
        if (y == 0) {
            return false;
        }
        out->i = x % y;
        return true;
    default:
        return false;
    }
}

/// An expression whose value must be an integer.
static bool eval(const DatArchive* a, const Context* c, const DatExpr* e,
                 uint64_t* out)
{
    return eval_int(a, c, e, 0, out);
}

/* --- The walk -------------------------------------------------------------
 */

static void issue(DatArchive* a, IssueKind kind, uint32_t at, uint32_t value)
{
    Issue i = { (uint8_t) kind, at, value };
    VEC_PUSH(a->issues, i);
}

static void reached(DatArchive* a, uint32_t offset, int32_t r)
{
    uint64_t* seen = map_slot(
        &a->visited, key2(offset, T(a, r)->id) ^ 0x8000000000000000ull, true);
    if (*seen == 0) {
        *seen = 1;
        Reached x = { offset, T(a, r)->id };
        VEC_PUSH(a->reached, x);
    }
    bits_set(&a->object, offset, a->size);
}

/// Insert into the walk's `visited`; whether it was new.
static bool visit(DatArchive* a, uint32_t offset, int32_t r)
{
    uint64_t* v = map_slot(&a->visited, key2(offset, T(a, r)->id), true);
    if (*v) {
        return false;
    }
    *v = 1;
    return true;
}

/// The native object for `offset` as type `r`, once it has one.
static void* native_of(const DatArchive* a, uint32_t offset, int32_t r)
{
    uint64_t v;
    if (!map_get(&a->natives, key2(offset, T(a, r)->id), &v)) {
        return NULL;
    }
    return (void*) (uintptr_t) v;
}

static void set_native(DatArchive* a, uint32_t offset, int32_t r, void* native)
{
    if (native == NULL) {
        return;
    }
    uint64_t* v = map_slot(&a->natives, key2(offset, T(a, r)->id), true);
    if (*v == 0) {
        *v = (uint64_t) (uintptr_t) native;
    }
    *map_slot(&a->offsets, (uint64_t) (uintptr_t) native, true) =
        key2(offset, T(a, r)->id);
}

/// An element already walked as another object: a copy of it, made once
/// every pointer is stored, which is the same object at `offset`.
static void copy_of(DatArchive* a, uint32_t offset, int32_t r, void* native)
{
    void* existing = native_of(a, offset, r);
    if (native == NULL || existing == NULL) {
        return;
    }
    Copy copy = { native, existing, T(a, r)->native_size };
    VEC_PUSH(a->copies, copy);
    *map_slot(&a->offsets, (uint64_t) (uintptr_t) native, true) =
        key2(offset, T(a, r)->id);
}

/// An array element or inline record owns this storage. References to a
/// separately converted view must use it too, once its pointers are filled.
static void place_native(DatArchive* a, uint32_t offset, int32_t r,
                         void* native)
{
    if (native == NULL) {
        return;
    }
    void* existing = native_of(a, offset, r);
    if (existing != NULL && existing != native && existing != a->data + offset)
    {
        copy_of(a, offset, r, native);
        a->native_moved = true;
    }
    *map_slot(&a->natives, key2(offset, T(a, r)->id), true) =
        (uint64_t) (uintptr_t) native;
    *map_slot(&a->offsets, (uint64_t) (uintptr_t) native, true) =
        key2(offset, T(a, r)->id);
}

/// Keep converted references so an array discovered later can supply their
/// final addresses. Raw, script and zero-count pointers are not registered.
static void reference(DatArchive* a, void* slot, uint32_t offset, int32_t r)
{
    if (slot != NULL && r != DAT_NONE && !opaque(a, r)) {
        r = resolve(a, r);
        if (r == DAT_NONE) {
            return;
        }
        *map_slot(&a->references, (uint64_t) (uintptr_t) slot, true) =
            key2(offset, T(a, r)->id);
    }
}

static void* native_array(DatArchive* a, uint32_t offset, int32_t e,
                          uint64_t count)
{
    uint64_t key = key2(offset, T(a, e)->id), n;
    void* existing = native_of(a, offset, e);
    if (existing != NULL && map_get(&a->native_counts, key, &n) && n >= count)
    {
        return existing;
    }
    uint32_t ns = T(a, e)->native_size;
    char* block = arena_alloc(&a->arena, (size_t) ns * (count ? count : 1));
    for (uint64_t i = 0; i < count; i++) {
        place_native(a, (uint32_t) (offset + i * T(a, e)->size), e,
                     block + i * ns);
    }
    *map_slot(&a->native_counts, key, true) = count;
    return block;
}

/// Whether any member of a union has a `DAT_IF`.
static bool conditioned(const DatType* u)
{
    if (u->kind != DAT_KIND_UNION) {
        return false;
    }
    for (uint32_t i = 0; i < u->nmembers; i++) {
        if (u->members[i].cond != NULL) {
            return true;
        }
    }
    return false;
}

static void record_extent(DatArchive* a, uint32_t offset, uint64_t end)
{
    uint64_t* e = map_slot(&a->extents, offset, true);
    if (end > *e) {
        *e = end;
    }
}

static void typed_extent(DatArchive* a, uint32_t offset, int32_t type,
                         uint64_t count)
{
    if (T(a, type)->raw) {
        return;
    }
    int32_t r = resolve(a, type);
    if (r == DAT_NONE) {
        return;
    }
    if (count == 1 && conditioned(T(a, r))) {
        return;
    }
    uint64_t end = offset + (uint64_t) T(a, r)->size * count;
    record_extent(a, offset, end);
}

static void untyped(DatArchive* a)
{
    a->untyped_pointers++;
}

static void unrelocated(DatArchive* a, uint32_t offset, uint32_t value)
{
    if (bits_has(&a->extern_slot, offset, a->size)) {
        bits_set(&a->pointer, offset, a->size);
        return;
    }
    if (value == 0) {
        return;
    }
    if (value == UINT32_MAX) {
        a->sentinels++;
        return;
    }
    issue(a, ISSUE_UNRELOCATED_POINTER, offset, value);
}

static void push(DatArchive* a, uint32_t offset, int32_t type,
                 const Scope* env, void* native, void** slot)
{
    Task t = { offset, type, env, native, slot };
    VEC_PUSH(a->queue, t);
}

static const Scope* bound(DatArchive* a, const Scope* outer,
                          const DatMember* m, int32_t record, uint32_t base,
                          bool has_record, uint64_t index)
{
    const Scope* env = outer;
    for (uint32_t i = 0; i < m->nbinds; i++) {
        const DatBind* b = &m->binds[i];
        Context c = { MODE_BIND, has_record ? record : DAT_NONE,
                      base,      DAT_NONE,
                      0,         outer,
                      index,     0 };
        Value value;
        if (eval_at(a, &c, b->value, 0, &value)) {
            Scope* s = arena_alloc(&a->arena, sizeof(Scope));
            s->name = b->name;
            s->value = value;
            s->outer = env;
            env = s;
        }
    }
    return env;
}

/// The record a union is in, which its conditions refer to.
typedef struct Parent {
    int32_t record;
    uint32_t base;
    bool some;
} Parent;

static void layout(DatArchive* a, uint32_t offset, int32_t type, void* native,
                   Parent parent);
static void extent(DatArchive* a, uint32_t offset, int32_t array,
                   const DatMember* m, Parent parent, void* native);

static bool fits(const DatArchive* a, uint32_t offset, int32_t type)
{
    int32_t r = resolve(a, type);
    if (r == DAT_NONE) {
        return true;
    }
    const DatType* t = T(a, r);
    switch (t->kind) {
    case DAT_KIND_POINTER: {
        uint32_t w = word(a, offset);
        return bits_has(&a->reloc, offset, a->size) ||
               bits_has(&a->extern_slot, offset, a->size) || w == 0 ||
               w == UINT32_MAX;
    }
    case DAT_KIND_INT:
    case DAT_KIND_FLOAT:
        return !bits_has(&a->reloc, offset, a->size);
    case DAT_KIND_STRUCT:
        for (uint32_t i = 0; i < t->nmembers; i++) {
            const DatMember* m = &t->members[i];
            if (m->bit_size || !m->has_offset || m->type == DAT_NONE) {
                continue;
            }
            if (!fits(a, offset + m->offset, m->type)) {
                return false;
            }
        }
        return true;
    case DAT_KIND_ARRAY: {
        int32_t e = resolve(a, t->target);
        if (e == DAT_NONE) {
            return true;
        }
        for (uint32_t i = 0; i < t->count; i++) {
            if (!fits(a, offset + i * T(a, e)->size, e)) {
                return false;
            }
        }
        return true;
    }
    default:
        return true;
    }
}

/// Report any relocated word within plain data.
static void relocated_words(DatArchive* a, uint32_t start, uint64_t end)
{
    for (uint32_t i = 0; i < a->nrelocs; i++) {
        uint32_t at = a->relocs[i];
        if (at >= start && at < end) {
            issue(a, ISSUE_RELOCATED_SCALAR, at, 0);
        }
    }
}

/// A native array of `count` of `r` for the data at `offset`; plain data
/// converted, raw data where it is.
static void* plain_array(DatArchive* a, uint32_t offset, int32_t raw,
                         int32_t r, uint64_t count)
{
    if (opaque(a, raw)) {
        return a->data + offset;
    }
    uint32_t ns = T(a, r)->native_size;
    char* block = native_array(a, offset, r, count);
    for (uint64_t i = 0; i < count; i++) {
        convert(a, (uint32_t) (offset + i * T(a, r)->size), r, block + i * ns);
    }
    return block;
}

/// Whether a counted inline array fits its declared bound and the data.
static bool array_count_fits(const DatArchive* a, uint32_t offset,
                             int32_t array, int32_t element, uint64_t count)
{
    uint64_t size = T(a, element)->size;
    uint64_t room = a->size > offset ? a->size - offset : 0;
    return count <= room / (size ? size : 1) &&
           (T(a, array)->unbounded || count <= T(a, array)->count);
}

/// Walk an inline array: an explicit count ignores symbols and pointer
/// targets inside it, unlike `DAT_EXTENT`.
static void counted_array(DatArchive* a, uint32_t offset, int32_t array,
                          uint64_t count, const DatMember* m, Parent parent,
                          void* native)
{
    int32_t raw = T(a, array)->target;
    int32_t e = resolve(a, raw);
    if (e == DAT_NONE) {
        return;
    }
    uint64_t* walked =
        map_slot(&a->array_counts, key2(offset, T(a, array)->id), true);
    *walked = 0;
    if (!array_count_fits(a, offset, array, e, count)) {
        issue(a, ISSUE_OUT_OF_BOUNDS, offset, 0);
        return;
    }
    *walked = count;
    const Scope* outer = a->env;
    for (uint64_t i = 0; i < count; i++) {
        uint32_t at = (uint32_t) (offset + i * T(a, e)->size);
        a->env =
            m ? bound(a, outer, m, parent.record, parent.base, parent.some, i)
              : outer;
        typed_extent(a, at, raw, 1);
        place_native(a, at, e,
                     native ? (char*) native + i * T(a, e)->native_size
                            : NULL);
        layout(a, at, raw,
               native ? (char*) native + i * T(a, e)->native_size : NULL,
               parent);
    }
    a->env = outer;
}

/// Walk an inline array or follow a pointer to `count` consecutive elements.
static void counted(DatArchive* a, uint32_t offset, int32_t pointer,
                    int32_t element, uint64_t count, const DatMember* m,
                    Parent parent, void* slot)
{
    int32_t p = resolve(a, pointer);
    if (p == DAT_NONE) {
        return;
    }
    int32_t target = DAT_NONE;
    if (T(a, p)->kind == DAT_KIND_ARRAY) {
        counted_array(a, offset, p, count, m, parent, slot);
        return;
    } else if (T(a, p)->kind == DAT_KIND_POINTER) {
        target = T(a, p)->target;
    } else if (element == DAT_NONE) {
        Parent none = { DAT_NONE, 0, false };
        layout(a, offset, pointer, slot, none);
        return;
    }
    uint32_t value = word(a, offset);
    if (!bits_has(&a->reloc, offset, a->size)) {
        unrelocated(a, offset, value);
        store_pointer(slot, unrelocated_value(a, offset, value));
        return;
    }
    bits_set(&a->pointer, offset, a->size);
    int32_t raw = element != DAT_NONE ? element : target;
    int32_t e = element != DAT_NONE ? element : pointee(a, target);
    if (e == DAT_NONE) {
        untyped(a);
        store_pointer(slot, a->data + value);
        return;
    }
    if (raw == DAT_NONE) {
        raw = e;
    }
    uint64_t size = T(a, e)->size;
    uint64_t room = a->size > value ? a->size - value : 0;
    if (count > room / (size ? size : 1) &&
        !(count == 1 && conditioned(T(a, e))))
    {
        issue(a, ISSUE_OUT_OF_BOUNDS, value, 0);
        return;
    }
    if (count > 0 && !opaque(a, raw)) {
        reference(a, slot, value, e);
    }
    /* As long as the longest count, for data several pointers count */
    if (count > 0 && !T(a, e)->has_pointers && !conditioned(T(a, e))) {
        typed_extent(a, value, raw, count);
        void* block = plain_array(a, value, raw, e, count);
        if (!visit(a, value, e)) {
            store_pointer(slot, block);
            return;
        }
        reached(a, value, e);
        set_native(a, value, e, block);
        store_pointer(slot, block);
        relocated_words(a, value, value + count * size);
        return;
    }
    /* None: where it points, which nothing reads */
    if (count == 0) {
        store_pointer(slot, a->data + value);
        return;
    }
    uint32_t ns = native_size(a, raw);
    char* block = native_array(a, value, e, count);
    store_pointer(slot, block);
    const Scope* outer = a->env;
    for (uint64_t i = 0; i < count; i++) {
        const Scope* env =
            m ? bound(a, outer, m, parent.record, parent.base, parent.some, i)
              : outer;
        push(a, (uint32_t) (value + i * size), raw, env, block + i * ns, NULL);
    }
}

/// Recheck plain pointer fields when bindings change on a visited record.
/// Shared vertex descriptors can supply a longer count or an extent fallback.
static void recount(DatArchive* a, uint32_t offset, int32_t type)
{
    int32_t r = resolve(a, type);
    if (r == DAT_NONE || T(a, r)->kind != DAT_KIND_STRUCT) {
        return;
    }
    const DatType* t = T(a, r);
    for (uint32_t i = 0; i < t->nmembers; i++) {
        const DatMember* m = &t->members[i];
        if (m->bit_size || m->type == DAT_NONE || !m->has_offset ||
            (m->count == NULL && !m->extent))
        {
            continue;
        }
        uint32_t at = offset + m->offset;
        int32_t p = resolve(a, m->type);
        if (p == DAT_NONE || T(a, p)->kind != DAT_KIND_POINTER ||
            !bits_has(&a->reloc, at, a->size))
        {
            continue;
        }
        int32_t e = m->type_tag != DAT_NONE ? m->type_tag
                                            : pointee(a, T(a, p)->target);
        if (e == DAT_NONE || T(a, e)->has_pointers) {
            continue;
        }
        Parent here = { r, offset, true };
        const Scope* outer = a->env;
        a->env = bound(a, outer, m, r, offset, true, 0);
        uint64_t count;
        Context c = { MODE_COUNT, r, offset, DAT_NONE, 0, a->env, 0, 0 };
        if (m->count != NULL && eval(a, &c, m->count, &count)) {
            counted(a, at, m->type, m->type_tag, count, m, here, NULL);
        } else if (m->extent) {
            extent(a, at, m->type, m, here, NULL);
        }
        a->env = outer;
    }
}

/// Follow a `DAT_TERMINATED` pointer: elements up to one whose first word
/// is the terminator value, which is walked too.
static void terminated(DatArchive* a, uint32_t offset, int32_t pointer,
                       void* slot, const DatExpr* terminator, uint32_t length)
{
    int32_t p = resolve(a, pointer);
    if (p == DAT_NONE) {
        return;
    }
    if (T(a, p)->kind != DAT_KIND_POINTER) {
        Parent none = { DAT_NONE, 0, false };
        layout(a, offset, pointer, slot, none);
        return;
    }
    uint32_t value = word(a, offset);
    if (!bits_has(&a->reloc, offset, a->size)) {
        unrelocated(a, offset, value);
        store_pointer(slot, unrelocated_value(a, offset, value));
        return;
    }
    bits_set(&a->pointer, offset, a->size);
    int32_t target = T(a, p)->target;
    int32_t e = pointee(a, target);
    if (e == DAT_NONE) {
        untyped(a);
        store_pointer(slot, a->data + value);
        return;
    }
    uint32_t size = T(a, e)->size;
    if (size == 0) {
        return;
    }
    reached(a, value, e);
    Context c = { MODE_TERMINATOR, DAT_NONE, 0, DAT_NONE, 0, a->env, 0, 0 };
    uint64_t term;
    if (!eval(a, &c, terminator, &term)) {
        store_pointer(slot, a->data + value);
        return;
    }
    /* How many there are, the terminator included */
    uint32_t width = size < 4 ? size : 4;
    uint64_t mask = width >= 8 ? ~0ull : (1ull << (8 * width)) - 1;
    uint64_t n = 0;
    uint32_t ended = 0;
    bool past = false;
    for (uint64_t i = 0;; i++) {
        uint64_t at = value + i * size;
        if (at + size > a->size) {
            past = true;
            break;
        }
        n = i + 1;
        if (ended > 0 || (bytes_at(a, at, width) == (term & mask) &&
                          !bits_has(&a->reloc, at, a->size)))
        {
            ended++;
        }
        if (ended >= (length ? length : 1)) {
            break;
        }
    }
    int32_t ty = target != DAT_NONE ? target : e;
    char* block = NULL;
    uint32_t ns = T(a, e)->native_size;
    if (opaque(a, ty)) {
        store_pointer(slot, a->data + value);
    } else {
        block = native_array(a, value, e, n);
        store_pointer(slot, block);
        reference(a, slot, value, e);
    }
    const Scope* env = a->env;
    for (uint64_t i = 0; i < n; i++) {
        uint32_t at = (uint32_t) (value + i * size);
        char* native = block ? block + i * ns : NULL;
        if (visit(a, at, e)) {
            set_native(a, at, e, native);
            typed_extent(a, at, ty, 1);
            Parent none = { DAT_NONE, 0, false };
            layout(a, at, ty, native, none);
        } else {
            copy_of(a, at, e, native);
            recount(a, at, ty);
        }
        a->env = env;
    }
    if (past) {
        issue(a, ISSUE_OUT_OF_BOUNDS, value, 0);
    }
}

/// How many elements of `size` a `DAT_EXTENT` array at `offset` can have:
/// up to the next public symbol or pointer target, or the end of the data.
static uint64_t extent_bound(const DatArchive* a, uint32_t offset,
                             uint32_t size)
{
    if (size == 0) {
        return 0;
    }
    uint64_t n = 0;
    for (uint64_t at = offset; at + size <= a->size; at += size, n++) {
        if (n > 0 && (bits_has(&a->public, at, a->size) ||
                      bits_has(&a->target, at, a->size)))
        {
            break;
        }
    }
    return n;
}

/// A `DAT_EXTENT` array or pointer: every element until the next public
/// symbol, object or pointer target, the end of the data, or one that
/// doesn't fit its type.
static void extent(DatArchive* a, uint32_t offset, int32_t array,
                   const DatMember* m, Parent parent, void* native)
{
    const Scope* outer = a->env;
    int32_t r = resolve(a, array);
    if (r == DAT_NONE) {
        return;
    }
    int32_t element;
    char* base;
    if (T(a, r)->kind == DAT_KIND_ARRAY) {
        element = T(a, r)->target;
        base = native;
    } else if (T(a, r)->kind == DAT_KIND_POINTER) {
        uint32_t value = word(a, offset);
        if (!bits_has(&a->reloc, offset, a->size)) {
            unrelocated(a, offset, value);
            store_pointer(native, unrelocated_value(a, offset, value));
            return;
        }
        bits_set(&a->pointer, offset, a->size);
        int32_t raw = T(a, r)->target;
        int32_t target = pointee(a, raw);
        if (target == DAT_NONE) {
            untyped(a);
            store_pointer(native, a->data + value);
            return;
        }
        if (opaque(a, raw != DAT_NONE ? raw : target)) {
            uint32_t size = T(a, target)->size;
            uint64_t count = extent_bound(a, value, size);
            for (uint64_t i = 1; i < count; i++) {
                uint32_t at = (uint32_t) (value + i * size);
                if (bits_has(&a->object, at, a->size) || !fits(a, at, target))
                {
                    count = i;
                    break;
                }
            }
            counted(a, offset, array, DAT_NONE, count, m, parent, native);
            return;
        }
        if (!visit(a, value, target)) {
            store_pointer(native, native_of(a, value, target));
            return;
        }
        reached(a, value, target);
        uint32_t size = T(a, target)->size;
        uint64_t n = extent_bound(a, value, size);
        base = native_array(a, value, target, n);
        store_pointer(native, base);
        reference(a, native, value, target);
        set_native(a, value, target, base);
        offset = value;
        element = raw;
    } else {
        layout(a, offset, array, native, parent);
        return;
    }
    int32_t e = resolve(a, element);
    if (e == DAT_NONE) {
        return;
    }
    uint32_t size = T(a, e)->size;
    uint32_t ns = T(a, e)->native_size;
    for (uint64_t i = 0;; i++) {
        uint64_t at = offset + i * size;
        if (at + size > a->size) {
            break;
        }
        bool boundary = bits_has(&a->public, at, a->size) ||
                        bits_has(&a->target, at, a->size) ||
                        bits_has(&a->object, at, a->size);
        if (i > 0 && (boundary || !fits(a, (uint32_t) at, e))) {
            break;
        }
        a->env =
            m ? bound(a, outer, m, parent.record, parent.base, parent.some, i)
              : outer;
        int32_t ty = element != DAT_NONE ? element : e;
        typed_extent(a, (uint32_t) at, ty, 1);
        place_native(a, (uint32_t) at, e, base ? base + i * ns : NULL);
        layout(a, (uint32_t) at, ty, base ? base + i * ns : NULL, parent);
    }
    a->env = outer;
}

/// A `DAT_TYPE` field: followed as a pointer to `target` when relocated.
static void typed(DatArchive* a, uint32_t offset, int32_t target, void* native,
                  uint32_t native_field)
{
    if (bits_has(&a->reloc, offset, a->size)) {
        bits_set(&a->pointer, offset, a->size);
        /* A field too small for a native pointer keeps the offset */
        if (native_field >= sizeof(void*)) {
            reference(a, native, word(a, offset), target);
            push(a, word(a, offset), target, a->env, NULL, native);
        } else {
            push(a, word(a, offset), target, a->env, NULL, NULL);
            if (native != NULL) {
                store_uint(native, native_field, word(a, offset));
            }
        }
    } else if (native != NULL && native_field != 0) {
        store_uint(native, native_field, word(a, offset));
    }
}

/// Return the command length at `at`: bytes for byte scripts, words otherwise.
static bool command_length(const DatArchive* a, const DatScript* s,
                           uint32_t at, uint64_t* out)
{
    /* Byte scripts use the full first byte and their own length expression. */
    uint32_t command = s->bytes ? a->data[at] : word(a, at);
    uint64_t opcode = command >> 26;
    if (!s->bytes && (opcode == 5 || opcode == 7)) {
        *out = 2;
        return true;
    }
    if (!s->bytes && opcode < 10) {
        *out = 1;
        return true;
    }
    if (s->table != NULL) {
        uint64_t index = opcode - 10;
        if (index >= s->table_size) {
            return false;
        }
        *out = s->table[index];
        return true;
    }
    Context c = { MODE_SCRIPT, DAT_NONE, 0, DAT_NONE, 0, NULL, 0, command };
    return eval(a, &c, s->length, out);
}

/// Follow a script pointer and any scripts referenced by its commands.
/// Keep script bytes unchanged, including big-endian words and pointer
/// offsets in word scripts.
static void script_at(DatArchive* a, uint32_t value, int32_t id,
                      const DatScript* s);

static void script(DatArchive* a, uint32_t offset, int32_t pointer,
                   const DatScript* s, void* slot)
{
    int32_t p = resolve(a, pointer);
    if (p == DAT_NONE) {
        return;
    }
    if (T(a, p)->kind != DAT_KIND_POINTER) {
        Parent none = { DAT_NONE, 0, false };
        layout(a, offset, pointer, slot, none);
        return;
    }
    uint32_t value = word(a, offset);
    if (!bits_has(&a->reloc, offset, a->size)) {
        unrelocated(a, offset, value);
        store_pointer(slot, unrelocated_value(a, offset, value));
        return;
    }
    bits_set(&a->pointer, offset, a->size);
    store_pointer(slot, a->data + value);
    script_at(a, value, pointee(a, T(a, p)->target), s);
}

/// Walk the script at `value` and any scripts its commands reference.
static void script_at(DatArchive* a, uint32_t value, int32_t id,
                      const DatScript* s)
{
    VEC(uint32_t) queue = { 0 };
    VEC_PUSH(queue, value);
    while (queue.len > 0) {
        uint32_t start = queue.items[--queue.len];
        if (!bits_set(&a->script, start, a->size)) {
            continue;
        }
        if (id != DAT_NONE) {
            reached(a, start, id);
        }
        uint64_t at = start;
        bool ended = false;
        uint64_t end = 0;
        for (;;) {
            if (at >= a->size) {
                issue(a, ISSUE_OUT_OF_BOUNDS, (uint32_t) at, 0);
                break;
            }
            uint8_t opcode = s->bytes ? a->data[at] : a->data[at] >> 2;
            uint64_t length;
            if (!command_length(a, s, (uint32_t) at, &length)) {
                issue(a, ISSUE_UNKNOWN_COMMAND, (uint32_t) at, opcode);
                break;
            }
            end = at + (length ? length : 1) * (s->bytes ? 1 : 4);
            if (end > a->size) {
                issue(a, ISSUE_OUT_OF_BOUNDS, (uint32_t) at, 0);
                break;
            }
            /* Byte scripts hold no pointers */
            if (!s->bytes) {
                for (uint64_t w = at; w < end; w += 4) {
                    if (bits_has(&a->reloc, w, a->size)) {
                        bits_set(&a->pointer, w, a->size);
                        VEC_PUSH(queue, word(a, w));
                    }
                }
            }
            /* Word scripts end at opcode 0. A zero length also ends scripts
             * sized by expressions. */
            if ((opcode == 0 && !s->bytes) ||
                (length == 0 && s->table == NULL))
            {
                ended = true;
                break;
            }
            at = end;
        }
        if (ended) {
            uint64_t* e = map_slot(&a->extents, start, true);
            if (end > *e) {
                *e = end;
            }
        }
    }
    free(queue.items);
}

typedef enum ChoiceKind {
    CHOICE_MEMBER,
    CHOICE_UNUSED,
    CHOICE_AMBIGUOUS,
} ChoiceKind;

/// The first union member whose `DAT_IF` holds; see `Walker::choose`.
static ChoiceKind choose(const DatArchive* a, int32_t u, uint32_t base,
                         Parent parent, uint32_t* index)
{
    const DatType* t = T(a, u);
    if (t->nmembers == 1) {
        *index = 0;
        return CHOICE_MEMBER;
    }
    bool decided = true;
    for (uint32_t i = 0; i < t->nmembers; i++) {
        const DatMember* m = &t->members[i];
        bool conditioned = m->cond != NULL;
        Context c = { MODE_IF,     parent.some ? parent.record : DAT_NONE,
                      parent.base, u,
                      base,        a->env,
                      0,           0 };
        uint64_t holds;
        bool known = conditioned && eval(a, &c, m->cond, &holds);
        if (known && holds == 0) {
            continue;
        }
        if (known) {
            *index = i;
            return CHOICE_MEMBER;
        }
        if (conditioned) {
            return CHOICE_AMBIGUOUS;
        }
        decided = false;
    }
    return decided ? CHOICE_UNUSED : CHOICE_AMBIGUOUS;
}

static void layout(DatArchive* a, uint32_t offset, int32_t type, void* native,
                   Parent parent)
{
    if (type == DAT_NONE) {
        return;
    }
    uint32_t term_length = 0;
    const DatExpr* term = typedef_terminator(a, type, &term_length);
    if (term != NULL) {
        terminated(a, offset, type, native, term, term_length);
        return;
    }
    const DatExpr* count_tag = typedef_count(a, type);
    if (count_tag != NULL) {
        Context c = {
            MODE_TERMINATOR, DAT_NONE, 0, DAT_NONE, 0, a->env, 0, 0
        };
        uint64_t count;
        if (eval(a, &c, count_tag, &count)) {
            Parent none = { DAT_NONE, 0, false };
            counted(a, offset, type, DAT_NONE, count, NULL, none, native);
            return;
        }
    }
    int32_t declared = typedef_type(a, type);
    if (declared != DAT_NONE) {
        typed(a, offset, declared, native, native_size(a, type));
        return;
    }
    const DatScript* s = typedef_script(a, type);
    if (s != NULL) {
        script(a, offset, type, s, native);
        return;
    }
    int32_t r = resolve(a, type);
    if (r == DAT_NONE) {
        return;
    }
    const DatType* t = T(a, r);
    if (t->kind == DAT_KIND_VOID) {
        return;
    }
    if (!conditioned(t) && !t->has_extent &&
        (uint64_t) offset + t->size > a->size)
    {
        issue(a, ISSUE_OUT_OF_BOUNDS, offset, 0);
        return;
    }
    if (t->kind == DAT_KIND_STRUCT || t->kind == DAT_KIND_UNION ||
        t->kind == DAT_KIND_ARRAY)
    {
        place_native(a, offset, r, native);
    }
    switch (t->kind) {
    case DAT_KIND_STRUCT:
        for (uint32_t i = 0; i < t->nmembers; i++) {
            const DatMember* m = &t->members[i];
            if (m->bit_size) {
                convert_bitfield(a, offset, m, native);
                continue;
            }
            if (m->type == DAT_NONE || !m->has_offset) {
                continue;
            }
            uint32_t at = offset + m->offset;
            char* mnative = native ? (char*) native + m->native_offset : NULL;
            Parent here = { r, offset, true };
            const Scope* outer = a->env;
            a->env = bound(a, outer, m, r, offset, true, 0);
            uint64_t count;
            Context c = { MODE_COUNT, r, offset, DAT_NONE, 0, a->env, 0, 0 };
            if (m->count != NULL && eval(a, &c, m->count, &count)) {
                counted(a, at, m->type, m->type_tag, count, m, here, mnative);
            } else if (m->type_tag != DAT_NONE) {
                typed(a, at, m->type_tag, mnative, m->native_size);
            } else if (m->script != NULL) {
                script(a, at, m->type, m->script, mnative);
            } else if (m->extent) {
                extent(a, at, m->type, m, here, mnative);
            } else if (m->terminator != NULL) {
                terminated(a, at, m->type, mnative, m->terminator,
                           m->terminator_length);
            } else if (m->nbinds > 0 &&
                       T(a, resolve(a, m->type))->kind == DAT_KIND_ARRAY)
            {
                const DatType* arr = T(a, resolve(a, m->type));
                int32_t e = resolve(a, arr->target);
                if (e != DAT_NONE) {
                    for (uint32_t j = 0; j < arr->count; j++) {
                        a->env = bound(a, outer, m, r, offset, true, j);
                        place_native(a, at + j * T(a, e)->size, e,
                                     mnative
                                         ? mnative + (size_t) j *
                                                         T(a, e)->native_size
                                         : NULL);
                        layout(a, at + j * T(a, e)->size, arr->target,
                               mnative ? mnative +
                                             (size_t) j * T(a, e)->native_size
                                       : NULL,
                               here);
                    }
                }
            } else {
                layout(a, at, m->type, mnative, here);
            }
            a->env = outer;
        }
        break;
    case DAT_KIND_UNION: {
        /* Views of plain data need no condition: nothing to follow.
         * Conditions still choose among layouts of different sizes. */
        bool plain = !t->has_pointers;
        if (plain && !conditioned(t)) {
            relocated_words(a, offset, (uint64_t) offset + t->size);
            convert(a, offset, r, native);
            break;
        }
        uint32_t index;
        ChoiceKind choice = choose(a, r, offset, parent, &index);
        if (choice == CHOICE_AMBIGUOUS && plain) {
            if ((uint64_t) offset + t->size > a->size) {
                issue(a, ISSUE_OUT_OF_BOUNDS, offset, 0);
                break;
            }
            record_extent(a, offset, (uint64_t) offset + t->size);
            relocated_words(a, offset, (uint64_t) offset + t->size);
            convert(a, offset, r, native);
            break;
        }
        switch (choice) {
        case CHOICE_MEMBER: {
            Choice ch = { offset, t->id, index };
            uint64_t* seen = map_slot(&a->choices, key2(offset, t->id), true);
            if (*seen == 0) {
                VEC_PUSH(a->chosen, ch);
            }
            *seen = index + 1;
            const DatMember* m = &t->members[index];
            if (m->type == DAT_NONE) {
                break;
            }
            typed_extent(a, offset, m->type, 1);
            const Scope* outer = a->env;
            a->env =
                bound(a, outer, m, parent.record, parent.base, parent.some, 0);
            if (m->script != NULL) {
                script(a, offset, m->type, m->script, native);
            } else if (m->terminator != NULL) {
                terminated(a, offset, m->type, native, m->terminator,
                           m->terminator_length);
            } else {
                layout(a, offset, m->type, native, parent);
            }
            a->env = outer;
            break;
        }
        case CHOICE_UNUSED:
            break;
        case CHOICE_AMBIGUOUS:
            /* Following a guess could misread everything behind it */
            issue(a, ISSUE_AMBIGUOUS_UNION, offset, 0);
            break;
        }
        break;
    }
    case DAT_KIND_ARRAY: {
        int32_t e = resolve(a, t->target);
        if (e == DAT_NONE) {
            break;
        }
        for (uint32_t i = 0; i < t->count; i++) {
            /* Keep typedef tags, e.g. a counted list in each slot. */
            place_native(a, offset + i * T(a, e)->size, e,
                         native ? (char*) native +
                                      (size_t) i * T(a, e)->native_size
                                : NULL);
            layout(a, offset + i * T(a, e)->size, t->target,
                   native ? (char*) native + (size_t) i * T(a, e)->native_size
                          : NULL,
                   parent);
        }
        break;
    }
    case DAT_KIND_POINTER: {
        uint32_t value = word(a, offset);
        if (bits_has(&a->reloc, offset, a->size)) {
            bits_set(&a->pointer, offset, a->size);
            if (pointee(a, t->target) != DAT_NONE) {
                reference(a, native, value, t->target);
                push(a, value, t->target, a->env, NULL, native);
            } else {
                untyped(a);
                store_pointer(native, a->data + value);
            }
        } else {
            unrelocated(a, offset, value);
            store_pointer(native, unrelocated_value(a, offset, value));
        }
        break;
    }
    case DAT_KIND_INT:
    case DAT_KIND_FLOAT:
        if (bits_has(&a->reloc, offset, a->size)) {
            issue(a, ISSUE_RELOCATED_SCALAR, offset, 0);
        }
        convert_scalar(a, offset, r, native);
        break;
    default:
        break;
    }
}

/// The native size of a struct ending in a counted or extent array.
static size_t extent_native_size(DatArchive* a, uint32_t offset, int32_t r)
{
    const DatType* t = T(a, r);
    size_t size = t->native_size;
    if (t->nmembers == 0) {
        return size;
    }
    const DatMember* m = &t->members[t->nmembers - 1];
    if (!m->extent && m->count == NULL) {
        return size;
    }
    int32_t arr = resolve(a, m->type);
    if (arr == DAT_NONE || T(a, arr)->kind != DAT_KIND_ARRAY) {
        return size;
    }
    int32_t e = resolve(a, T(a, arr)->target);
    if (e == DAT_NONE) {
        return size;
    }
    uint64_t n;
    if (m->count != NULL) {
        const Scope* env = bound(a, a->env, m, r, offset, true, 0);
        Context c = { MODE_COUNT, r, offset, DAT_NONE, 0, env, 0, 0 };
        if (!eval(a, &c, m->count, &n)) {
            n = T(a, arr)->count;
        }
        if (!array_count_fits(a, offset + m->offset, arr, e, n)) {
            return size;
        }
    } else {
        n = extent_bound(a, offset + m->offset, T(a, e)->size);
    }
    size_t end = m->native_offset + (size_t) n * T(a, e)->native_size;
    return end > size ? end : size;
}

/// Walk one object; see `Walker::object`.
static void object(DatArchive* a, Task task)
{
    int32_t r = resolve(a, task.type);
    if (r == DAT_NONE || T(a, r)->kind == DAT_KIND_VOID) {
        return;
    }
    if (!visit(a, task.offset, r)) {
        void* existing = native_of(a, task.offset, r);
        if (task.slot != NULL) {
            store_pointer(task.slot, existing);
        }
        copy_of(a, task.offset, r, task.native);
        recount(a, task.offset, task.type);
        return;
    }
    /* Every object is made natively, even one reached through a field that
       can't point to it (DAT_TYPE on a narrow integer), so that pointers
       reaching it later can */
    void* native =
        task.native != NULL ? task.native : native_of(a, task.offset, r);
    if (native == NULL) {
        if (opaque(a, task.type)) {
            native = a->data + task.offset;
        } else {
            native =
                arena_alloc(&a->arena, extent_native_size(a, task.offset, r));
        }
    }
    store_pointer(task.slot, native);
    /* Opaque objects also need an identity for subsequent references. They
       remain archive bytes: layout and verification must not convert them. */
    set_native(a, task.offset, r, native);
    typed_extent(a, task.offset, task.type, 1);
    reached(a, task.offset, r);
    Parent none = { DAT_NONE, 0, false };
    layout(a, task.offset, task.type,
           native == a->data + task.offset ? NULL : native, none);
}

static void drain(DatArchive* a)
{
    while (a->queue.len > 0) {
        Task t = a->queue.items[--a->queue.len];
        a->env = t.env;
        object(a, t);
    }
}

/// Copy every element walked as another object, once every pointer is
/// stored.
static void finish(DatArchive* a)
{
    /* Later copies may read earlier ones */
    for (size_t i = 0; i < a->copies.len; i++) {
        Copy* c = &a->copies.items[i];
        if (c->src != NULL && c->dst != c->src) {
            memcpy(c->dst, c->src, c->size);
            /* A copied record's pointer fields need the same fixups. Slots
               may be unaligned, so do not assume a native pointer stride. */
            for (size_t j = 0; j < c->size; j++) {
                uint64_t target;
                if (map_get(&a->references, (uint64_t) (uintptr_t) c->src + j,
                            &target))
                {
                    *map_slot(&a->references,
                              (uint64_t) (uintptr_t) c->dst + j, true) =
                        target;
                }
            }
        }
    }
    a->copies.len = 0;
    if (!a->native_moved) {
        return;
    }
    a->native_moved = false;
    for (size_t i = 0; i < a->references.cap; i++) {
        uint64_t key = a->references.keys[i], native;
        if (key != UINT64_MAX &&
            map_get(&a->natives, a->references.values[i], &native))
        {
            store_pointer((void*) (uintptr_t) key, (void*) (uintptr_t) native);
        }
    }
}

static const Scope* root_env(DatArchive* a, const DatRoot* root)
{
    const Scope* env = NULL;
    if (root == NULL) {
        return NULL;
    }
    for (uint32_t i = 0; i < root->nbinds; i++) {
        const DatRootBind* b = &root->binds[i];
        Scope* s = arena_alloc(&a->arena, sizeof(Scope));
        s->name = b->name;
        s->value = (Value){ b->value, NULL, 0 };
        s->outer = env;
        env = s;
    }
    return env;
}

/// Walk an object and everything it reaches; see `Walker::root`.
static void* walk_root(DatArchive* a, uint32_t offset, int32_t type,
                       const Scope* env)
{
    void* native = NULL;
    push(a, offset, type, env, NULL, &native);
    drain(a);
    finish(a);
    return native;
}

/// Walk `count` elements, or as many as fit before the next public symbol
/// or pointer target; see `Walker::root_array`.
static void* walk_root_array(DatArchive* a, uint32_t offset, int32_t element,
                             bool bounded, uint64_t count, const Scope* env)
{
    a->env = env;
    int32_t raw = element;
    int32_t e = resolve(a, element);
    if (e == DAT_NONE || T(a, e)->kind == DAT_KIND_VOID) {
        return NULL;
    }
    if (bounded && count == 1 && conditioned(T(a, e))) {
        return walk_root(a, offset, raw, env);
    }
    uint64_t size = T(a, e)->size;
    if (size == 0 || !visit(a, offset, e)) {
        return native_of(a, offset, e);
    }
    reached(a, offset, e);
    uint64_t room = a->size > offset ? a->size - offset : 0;
    if (!bounded) {
        uint64_t end = room;
        for (uint64_t at = (uint64_t) offset + 1; at < a->size; at++) {
            if (bits_has(&a->public, at, a->size) ||
                bits_has(&a->target, at, a->size))
            {
                end = at - offset;
                break;
            }
        }
        count = (end < room ? end : room) / size;
    }
    if (count * size > room) {
        issue(a, ISSUE_OUT_OF_BOUNDS, offset, 0);
    }
    if (count > room / size) {
        count = room / size;
    }
    typed_extent(a, offset, raw, count);
    if (!T(a, e)->has_pointers && !conditioned(T(a, e))) {
        void* block = plain_array(a, offset, raw, e, count);
        set_native(a, offset, e, block);
        relocated_words(a, offset, offset + count * size);
        return block;
    }
    uint32_t ns = T(a, e)->native_size;
    char* block = native_array(a, offset, e, count);
    set_native(a, offset, e, block);
    for (uint64_t i = 0; i < count; i++) {
        /* Each element starts with the root's bindings */
        a->env = env;
        uint32_t at = (uint32_t) (offset + i * size);
        if (i > 0) {
            set_native(a, at, e, block + i * ns);
        }
        Parent none = { DAT_NONE, 0, false };
        layout(a, at, e, block + i * ns, none);
        drain(a);
    }
    finish(a);
    return block;
}

/// How many elements of `type` a list at `offset` holds, up to and
/// including the first whose first word is `term` and not relocated.
static uint64_t terminated_count(const DatArchive* a, uint32_t offset,
                                 int32_t type, uint64_t term)
{
    int32_t e = resolve(a, type);
    if (e == DAT_NONE || T(a, e)->size == 0) {
        return 0;
    }
    uint32_t size = T(a, e)->size;
    uint32_t width = size < 4 ? size : 4;
    uint64_t mask = (1ull << (8 * width)) - 1;
    uint64_t n = 0;
    for (uint64_t at = offset; at + size <= a->size; at += size) {
        n++;
        if (bytes_at(a, at, width) == (term & mask) &&
            !bits_has(&a->reloc, at, a->size))
        {
            break;
        }
    }
    return n;
}

static void* walk(DatArchive* a, uint32_t offset, const DatRoot* root,
                  int32_t type, DatCount count, uint64_t n)
{
    const Scope* env = root_env(a, root);
    switch (count) {
    case DAT_COUNT_ONE:
        return walk_root(a, offset, type, env);
    case DAT_COUNT_EXACTLY:
        return walk_root_array(a, offset, type, true, n, env);
    case DAT_COUNT_EXTENT:
        return walk_root_array(a, offset, type, false, 0, env);
    case DAT_COUNT_TERMINATED:
        return walk_root_array(a, offset, type, true,
                               terminated_count(a, offset, type, n), env);
    }
    return NULL;
}

void* dat_at(DatArchive* a, uint32_t offset, int32_t type, DatCount count,
             uint64_t n)
{
    if (type <= DAT_NONE || (uint32_t) type >= a->s->ntypes) {
        return NULL;
    }
    return walk(a, offset, NULL, type, count, n);
}

void* dat_public(DatArchive* a, const char* name, int32_t type)
{
    for (uint32_t i = 0; i < a->npublics; i++) {
        if (strcmp(a->publics[i].name, name) == 0) {
            return dat_at(a, a->publics[i].offset, type, DAT_COUNT_ONE, 0);
        }
    }
    return NULL;
}

int dat_load_roots(DatArchive* a, const char* file, uint32_t index)
{
    const DatFileRoots* f = NULL;
    for (uint32_t i = 0; i < a->s->nmodules && f == NULL; i++) {
        const DatModule* mod = &a->s->modules[i];
        for (uint32_t j = 0; j < mod->nfiles; j++) {
            if (mod->files[j].archive == index &&
                strcmp(mod->files[j].file, file) == 0)
            {
                f = &mod->files[j];
                break;
            }
        }
    }
    if (f == NULL) {
        return 0;
    }
    int found = 0;
    /* Public symbols in the archive's order, then aliases */
    for (uint32_t i = 0; i < a->npublics; i++) {
        for (uint32_t j = 0; j < f->nroots; j++) {
            const DatRoot* root = &f->roots[j];
            if (root->alias || strcmp(root->name, a->publics[i].name) != 0) {
                continue;
            }
            walk(a, a->publics[i].offset, root, root->type,
                 (DatCount) root->count_kind, root->count);
            found++;
            break;
        }
    }
    for (uint32_t j = 0; j < f->nroots; j++) {
        const DatRoot* root = &f->roots[j];
        if (root->alias && root->script != NULL) {
            a->env = root_env(a, root);
            script_at(a, root->address, pointee(a, root->type), root->script);
            finish(a);
            found++;
        } else if (root->alias) {
            walk(a, root->address, root, root->type,
                 (DatCount) root->count_kind, root->count);
            found++;
        }
    }
    return found;
}

/* --- Traces ---------------------------------------------------------------
 */

static int compare_pair(const void* x, const void* y)
{
    const uint32_t* a = x;
    const uint32_t* b = y;
    for (int i = 0; i < 2; i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : 1;
        }
    }
    return 0;
}

static int compare_triple(const void* x, const void* y)
{
    const uint32_t* a = x;
    const uint32_t* b = y;
    for (int i = 0; i < 3; i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : 1;
        }
    }
    return 0;
}

static const char* type_name(const DatArchive* a, uint32_t id)
{
    int32_t t = dat_type_by_id(a->s, id);
    return t == DAT_NONE ? "?" : a->s->types[t]->name;
}

void dat_trace(const DatArchive* a, FILE* out, unsigned what)
{
    if (what & DAT_TRACE_OBJECTS) {
        size_t n = a->reached.len;
        uint32_t* rows = malloc((n + 1) * 2 * sizeof(uint32_t));
        for (size_t i = 0; i < n; i++) {
            rows[2 * i] = a->reached.items[i].offset;
            rows[2 * i + 1] = a->reached.items[i].id;
        }
        qsort(rows, n, 2 * sizeof(uint32_t), compare_pair);
        for (size_t i = 0; i < n; i++) {
            fprintf(out, "object 0x%X %u %s\n", rows[2 * i], rows[2 * i + 1],
                    type_name(a, rows[2 * i + 1]));
        }
        free(rows);
    }
    if (what & DAT_TRACE_POINTERS) {
        for (uint32_t at = 0; at < a->size; at++) {
            if (bits_has(&a->pointer, at, a->size)) {
                fprintf(out, "pointer 0x%X\n", at);
            }
        }
    }
    if (what & DAT_TRACE_EXTENTS) {
        uint32_t* rows = malloc((a->extents.len + 1) * 2 * sizeof(uint32_t));
        size_t n = 0;
        for (size_t i = 0; i < a->extents.cap; i++) {
            if (a->extents.keys[i] != UINT64_MAX) {
                rows[2 * n] = (uint32_t) a->extents.keys[i];
                rows[2 * n + 1] = (uint32_t) a->extents.values[i];
                n++;
            }
        }
        qsort(rows, n, 2 * sizeof(uint32_t), compare_pair);
        for (size_t i = 0; i < n; i++) {
            fprintf(out, "extent 0x%X 0x%X\n", rows[2 * i], rows[2 * i + 1]);
        }
        free(rows);
    }
    if (what & DAT_TRACE_CHOICES) {
        size_t n = a->chosen.len;
        uint32_t* rows = malloc((n + 1) * 3 * sizeof(uint32_t));
        for (size_t i = 0; i < n; i++) {
            const Choice* c = &a->chosen.items[i];
            uint64_t index = 0;
            map_get(&a->choices, key2(c->offset, c->id), &index);
            rows[3 * i] = c->offset;
            rows[3 * i + 1] = c->id;
            rows[3 * i + 2] = (uint32_t) index - 1;
        }
        qsort(rows, n, 3 * sizeof(uint32_t), compare_triple);
        for (size_t i = 0; i < n; i++) {
            fprintf(out, "choice 0x%X %u %u\n", rows[3 * i], rows[3 * i + 1],
                    rows[3 * i + 2]);
        }
        free(rows);
    }
    if (what & DAT_TRACE_ISSUES) {
        size_t n = a->issues.len;
        uint32_t* rows = malloc((n + 1) * 3 * sizeof(uint32_t));
        for (size_t i = 0; i < n; i++) {
            rows[3 * i] = a->issues.items[i].kind;
            rows[3 * i + 1] = a->issues.items[i].at;
            rows[3 * i + 2] = a->issues.items[i].value;
        }
        qsort(rows, n, 3 * sizeof(uint32_t), compare_triple);
        for (size_t i = 0; i < n; i++) {
            if (i > 0 && compare_triple(&rows[3 * i], &rows[3 * (i - 1)]) == 0)
            {
                continue;
            }
            fprintf(out, "issue %s 0x%X 0x%X\n", issue_names[rows[3 * i]],
                    rows[3 * i + 1], rows[3 * i + 2]);
        }
        free(rows);
    }
    if (what & DAT_TRACE_COUNTS) {
        fprintf(out, "untyped-pointers %zu\nsentinels %zu\n",
                a->untyped_pointers, a->sentinels);
    }
}

/* --- Verification ---------------------------------------------------------
 */

typedef struct Verify {
    const DatArchive* a;
    FILE* out;
    size_t mismatches;
    Map checked;
} Verify;

static void mismatch(Verify* v, uint32_t at, const char* what, uint64_t want,
                     uint64_t got)
{
    v->mismatches++;
    if (v->out != NULL) {
        fprintf(v->out, "mismatch 0x%X %s: want 0x%llX, got 0x%llX\n", at,
                what, (unsigned long long) want, (unsigned long long) got);
    }
}

/// Read a native object back and compare it with the data: every scalar
/// converted, every relocated pointer to something the walk converted or
/// to the raw data at its target, every other pointer as
/// unrelocated_value() makes it.
static void verify(Verify* v, uint32_t offset, int32_t type,
                   const void* native, int depth)
{
    const DatArchive* a = v->a;
    int32_t r = resolve(a, type);
    if (r == DAT_NONE || native == NULL || depth > 64) {
        return;
    }
    const DatType* t = T(a, r);
    if (!conditioned(t) && (uint64_t) offset + t->size > a->size) {
        return;
    }
    uint64_t key = key2(offset, t->id), previous;
    if (map_get(&v->checked, key, &previous) &&
        previous == (uint64_t) (uintptr_t) native)
    {
        return;
    }
    *map_slot(&v->checked, key, true) = (uint64_t) (uintptr_t) native;
    switch (t->kind) {
    case DAT_KIND_INT: {
        uint32_t ns = t->native_size ? t->native_size : t->size;
        uint64_t want =
            extend(bytes_at(a, offset, t->size), 8 * t->size, t->is_signed);
        if (ns < 8) {
            want &= (1ull << (8 * ns)) - 1;
        }
        uint64_t got = load_uint(native, ns);
        if (got != want) {
            mismatch(v, offset, t->name, want, got);
        }
        break;
    }
    case DAT_KIND_FLOAT:
        if (t->size == 4 && t->native_size == 4) {
            uint32_t want = (uint32_t) bytes_at(a, offset, 4);
            uint32_t got = (uint32_t) load_uint(native, 4);
            if (got != want) {
                mismatch(v, offset, t->name, want, got);
            }
        }
        break;
    case DAT_KIND_POINTER: {
        const void* p;
        memcpy(&p, native, sizeof p);
        uint32_t value = word(a, offset);
        if (bits_has(&a->reloc, offset, a->size)) {
            uint64_t key;
            bool ok = p == a->data + value ||
                      (map_get(&a->offsets, (uint64_t) (uintptr_t) p, &key) &&
                       (uint32_t) (key >> 32) == value);
            /* Elements of a native array */
            if (!ok && p != NULL) {
                int32_t e = pointee(a, t->target);
                ok = e != DAT_NONE && native_of(a, value, e) == p;
            }
            if (!ok) {
                int32_t pe = pointee(a, t->target);
                mismatch(v, offset,
                         p == NULL        ? "missing relocated pointer"
                         : pe != DAT_NONE ? T(a, pe)->name
                                          : "pointer",
                         value, (uint64_t) (uintptr_t) p);
                if (v->out != NULL &&
                    map_get(&a->offsets, (uint64_t) (uintptr_t) p, &key))
                {
                    int32_t e = pointee(a, t->target);
                    fprintf(v->out, "  (to %s, which is 0x%X as %s)\n",
                            e != DAT_NONE ? T(a, e)->name : "?",
                            (uint32_t) (key >> 32),
                            type_name(a, (uint32_t) key));
                }
            }
        } else if (p != unrelocated_value(a, offset, value)) {
            mismatch(v, offset, "unrelocated pointer", value,
                     (uint64_t) (uintptr_t) p);
        }
        break;
    }
    case DAT_KIND_STRUCT:
        for (uint32_t i = 0; i < t->nmembers; i++) {
            const DatMember* m = &t->members[i];
            if (m->bit_size) {
                if (m->get_bits != NULL) {
                    int32_t mr = resolve(a, m->type);
                    uint64_t want = extend(
                        bits_at(a, offset, m->bit_offset, m->bit_size),
                        m->bit_size, mr != DAT_NONE && T(a, mr)->is_signed);
                    uint64_t got =
                        extend(m->get_bits(native), m->bit_size,
                               mr != DAT_NONE && T(a, mr)->is_signed);
                    if (want != got) {
                        mismatch(v, offset, "bitfield", want, got);
                    }
                }
                continue;
            }
            /* Counted, typed and scripted members are checked as the
               objects they point to */
            if (!m->has_offset || m->type == DAT_NONE ||
                m->type_tag != DAT_NONE || m->script != NULL || m->extent)
            {
                continue;
            }
            int32_t arr = resolve(a, m->type);
            uint64_t count;
            if (m->count != NULL && arr != DAT_NONE &&
                T(a, arr)->kind == DAT_KIND_ARRAY &&
                map_get(&a->array_counts,
                        key2(offset + m->offset, T(a, arr)->id), &count))
            {
                int32_t e = resolve(a, T(a, arr)->target);
                if (e != DAT_NONE) {
                    for (uint64_t j = 0; j < count; j++) {
                        verify(v, offset + m->offset + j * T(a, e)->size, e,
                               (const char*) native + m->native_offset +
                                   j * T(a, e)->native_size,
                               depth + 1);
                    }
                }
                continue;
            }
            verify(v, offset + m->offset, m->type,
                   (const char*) native + m->native_offset, depth + 1);
        }
        break;
    case DAT_KIND_UNION: {
        uint64_t index;
        const DatMember* m = NULL;
        if (map_get(&a->choices, key2(offset, t->id), &index)) {
            m = &t->members[index - 1];
        } else if (!t->has_pointers) {
            m = largest(a, t);
        }
        if (m != NULL && m->script == NULL) {
            verify(v, offset, m->type, native, depth + 1);
        }
        break;
    }
    case DAT_KIND_ARRAY: {
        int32_t e = resolve(a, t->target);
        if (e == DAT_NONE) {
            break;
        }
        for (uint32_t i = 0; i < t->count; i++) {
            verify(v, offset + i * T(a, e)->size, e,
                   (const char*) native + (size_t) i * T(a, e)->native_size,
                   depth + 1);
        }
        break;
    }
    default:
        break;
    }
}

size_t dat_verify(const DatArchive* a, FILE* out)
{
    Verify v = { .a = a, .out = out };
    for (size_t i = 0; i < a->natives.cap; i++) {
        if (a->natives.keys[i] == UINT64_MAX) {
            continue;
        }
        uint32_t offset = (uint32_t) (a->natives.keys[i] >> 32);
        uint32_t id = (uint32_t) a->natives.keys[i];
        const void* native = (const void*) (uintptr_t) a->natives.values[i];
        int32_t type = dat_type_by_id(a->s, id);
        if (type != DAT_NONE && native != a->data + offset) {
            verify(&v, offset, type, native, 0);
        }
    }
    map_free(&v.checked);
    return v.mismatches;
}
