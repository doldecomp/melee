/** @file Storage and references for generated native readers. */
#include <limits.h>
#include <math.h>

#include <dat/reader-internal.h>

static uint32_t dat_reader_be32(const uint8_t* p);
static int dat_reader_command_length(const DatArchive* a, const DatScript* s,
                                     uint32_t at, uint64_t* out);
static int dat_reader_conditioned(const DatType* t);
static void dat_reader_counted_array(DatArchive* a, uint32_t offset,
                                     int32_t array, uint64_t count,
                                     DatBinding binding, DatScope* storage,
                                     DatParent parent, void* native);
static size_t dat_reader_extent_native_size(DatArchive* a, uint32_t offset,
                                            int32_t r);
static void dat_reader_finish(DatArchive* a);
static int dat_reader_lookup(const DatScope* env, int32_t name, uint64_t* out);
static void* dat_reader_native_array(DatArchive* a, uint32_t offset, int32_t e,
                                     uint64_t count);
static void dat_reader_object(DatArchive* a, uint32_t offset, int32_t type,
                              void* native, void** slot);
static int dat_reader_opaque(const DatArchive* a, int32_t type);
static void* dat_reader_plain_array(DatArchive* a, uint32_t offset,
                                    int32_t raw, int32_t r, uint64_t count);
static void dat_reader_reached(DatArchive* a, uint32_t offset, int32_t r);
static void dat_reader_script_at(DatArchive* a, uint32_t value, int32_t id,
                                 const DatScript* s);
static void dat_reader_set_native(DatArchive* a, uint32_t offset, int32_t r,
                                  void* native);
static void dat_reader_store_uint(void* dst, uint32_t size, uint64_t v);
static uint64_t dat_reader_terminated_count(const DatArchive* a,
                                            uint32_t offset, int32_t type,
                                            uint64_t term);
static int dat_reader_visit(DatArchive* a, uint32_t offset, int32_t r);
static void* dat_reader_walk(DatArchive* a, uint32_t offset,
                             const DatRoot* root, int32_t type, DatCount count,
                             uint64_t n);
static void* dat_reader_walk_root(DatArchive* a, uint32_t offset, int32_t type,
                                  const DatScope* env);
static void* dat_reader_walk_root_array(DatArchive* a, uint32_t offset,
                                        int32_t element, uint8_t bounded,
                                        uint64_t count, const DatScope* env);

static uint32_t dat_reader_be32(const uint8_t* p)
{
    return (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
           (uint32_t) p[2] << 8 | p[3];
}

/// The word at `offset`, or 0 past the data.
uint32_t dat_reader_word(const DatArchive* a, uint64_t offset)
{
    return offset + 4 <= a->archive->size
               ? dat_reader_be32(a->archive->data + offset)
               : 0;
}

/// `size` bytes from `offset`, big-endian, as an integer: the low 64 bits
/// of a larger one.
uint64_t dat_reader_bytes_at(const DatArchive* a, uint64_t offset,
                             uint32_t size)
{
    uint64_t v = 0;
    for (uint32_t i = 0; i < size; i++) {
        v = v << 8 | a->archive->data[offset + i];
    }
    return v;
}

static DatArchive* dat_wrap(const DatSchema* schema, DatArchiveData* archive)
{
    if (archive == NULL) {
        return NULL;
    }
    DatArchive* a = calloc(1, sizeof(*a));
    if (a == NULL) {
        abort();
    }
    a->archive = archive;
    a->s = schema;
    bits_init(&a->object, archive->size);
    bits_init(&a->script, archive->size);
    dat_test_init(a);
    for (uint32_t i = 1; i < schema->nnames; i++) {
        if (strcmp(schema->names[i], "_index") == 0) {
            a->name_index = i;
        }
        if (strcmp(schema->names[i], "_command") == 0) {
            a->name_command = i;
        }
    }
    return a;
}

DatArchive* dat_open(const DatSchema* schema, const void* bytes, size_t size,
                     const char** error)
{
    return dat_wrap(schema, dat_archive_open(bytes, size, error));
}

int dat_open_packed(const DatSchema* schema, const void* bytes, size_t size,
                    DatArchive** out, size_t* offsets, int max,
                    const char** error)
{
    if (max < 0) {
        return -1;
    }
    DatArchiveData** raw = calloc((size_t) max + 1, sizeof(*raw));
    if (raw == NULL) {
        abort();
    }
    int n = dat_archive_open_packed(bytes, size, raw, offsets, max, error);
    for (int i = 0; i < n; i++) {
        out[i] = dat_wrap(schema, raw[i]);
    }
    free(raw);
    return n;
}

void dat_close(DatArchive* a)
{
    if (a == NULL) {
        return;
    }
    dat_archive_close(a->archive);
    free(a->object.words);
    free(a->script.words);
    map_free(&a->visited);
    map_free(&a->natives);
    map_free(&a->native_counts);
    map_free(&a->references);
    map_free(&a->extern_values);
    dat_test_close(a);
    while (a->allocations != NULL) {
        DatAllocation* allocation = a->allocations;
        a->allocations = allocation->next;
        free(allocation->data);
        free(allocation);
    }
    free(a);
}

const uint8_t* dat_raw(const DatArchive* a, uint32_t offset)
{
    return a->archive->data + offset;
}

uint32_t dat_size(const DatArchive* a)
{
    return a->archive->size;
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

const DatType* dat_reader_T(const DatArchive* a, int32_t type)
{
    return a->s->types[type];
}

int32_t dat_reader_resolve(const DatArchive* a, int32_t type)
{
    return type == DAT_NONE ? DAT_NONE : dat_reader_T(a, type)->resolved;
}

/// What a pointer points to, if it can be followed: not `void`, functions
/// or undefined types.
int32_t dat_reader_pointee(const DatArchive* a, int32_t target)
{
    int32_t r = dat_reader_resolve(a, target);
    if (r == DAT_NONE || dat_reader_T(a, r)->kind == DAT_KIND_VOID) {
        return DAT_NONE;
    }
    return r;
}

/// Data with no conversion: raw bytes, or a `DAT_BLOB` format, which
/// natively stay as they are in the data.
static int dat_reader_opaque(const DatArchive* a, int32_t type)
{
    return type != DAT_NONE && dat_reader_T(a, type)->opaque;
}

uint32_t dat_reader_native_size(const DatArchive* a, int32_t type)
{
    int32_t r = dat_reader_resolve(a, type);
    return r == DAT_NONE ? 0 : dat_reader_T(a, r)->native_size;
}

/* --- Native values --------------------------------------------------------
 */

static void dat_reader_store_uint(void* dst, uint32_t size, uint64_t v)
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

/// An integer of `size` bytes as a value of `bits`, sign-extended if
/// `is_signed`.
uint64_t dat_reader_extend(uint64_t v, uint32_t bits, uint8_t is_signed)
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

void dat_reader_integer(const DatArchive* a, uint32_t offset,
                        uint32_t source_size, uint32_t native_size,
                        uint8_t is_signed, void* native)
{
    if (!native || (uint64_t) offset + source_size > a->archive->size) {
        return;
    }
    uint64_t value = dat_reader_bytes_at(a, offset, source_size);
    dat_reader_store_uint(
        native, native_size,
        dat_reader_extend(value, 8 * source_size, is_signed));
}

void dat_reader_float(const DatArchive* a, uint32_t offset,
                      uint32_t source_size, uint32_t native_size, void* native)
{
    if (!native || (uint64_t) offset + source_size > a->archive->size) {
        return;
    }
    uint64_t v = dat_reader_bytes_at(a, offset, source_size);
    if (source_size == 4 && native_size == sizeof(float)) {
        uint32_t bits = (uint32_t) v;
        float f;
        memcpy(&f, &bits, 4);
        memcpy(native, &f, sizeof f);
    } else if (source_size == 8 && native_size == sizeof(double)) {
        double d;
        memcpy(&d, &v, 8);
        memcpy(native, &d, sizeof d);
    } else if (source_size == 4 && native_size == sizeof(double)) {
        uint32_t bits = (uint32_t) v;
        float f;
        memcpy(&f, &bits, 4);
        double d = f;
        memcpy(native, &d, sizeof d);
    }
}

/// Bits `start` to `start + bits` of the data from `offset`, counted from
/// the most significant bit of its first byte.
uint64_t dat_reader_bits_at(const DatArchive* a, uint64_t offset,
                            uint64_t start, uint32_t bits)
{
    uint64_t v = 0;
    for (uint64_t bit = start; bit < start + bits; bit++) {
        uint64_t at = offset + bit / 8;
        uint8_t byte = at < a->archive->size ? a->archive->data[at] : 0;
        v = v << 1 | (byte >> (7 - bit % 8) & 1);
    }
    return v;
}

void dat_reader_store_pointer(void* slot, const void* p)
{
    if (slot != NULL) {
        memcpy(slot, &p, sizeof p);
    }
}

/// A pointer the data doesn't relocate, natively: null for null and
/// externs (which the loader leaves null), -1 kept as -1, and anything else
/// as its value.
void* dat_reader_unrelocated_value(const DatArchive* a, uint32_t offset,
                                   uint32_t value)
{
    if (bits_has(&a->archive->extern_slot, offset, a->archive->size)) {
        uint64_t address = 0;
        map_get(&a->extern_values, offset, &address);
        return (void*) (uintptr_t) address;
    }
    if (value == 0) {
        return NULL;
    }
    if (value == UINT32_MAX) {
        return (void*) (intptr_t) -1;
    }
    return (void*) (uintptr_t) value;
}

/// Convert plain data, which has no pointers to follow.
void dat_reader_convert(DatArchive* a, uint32_t offset, int32_t type,
                        void* native)
{
    int32_t r = dat_reader_resolve(a, type);
    if (native != NULL && r != DAT_NONE) {
        dat_reader_T(a, r)->convert(a, offset, native);
    }
}

void dat_reader_store_unrelocated(DatArchive* a, uint32_t offset,
                                  uint32_t value, void* slot)
{
    dat_reader_unrelocated(a, offset, value);
    dat_reader_store_pointer(slot,
                             dat_reader_unrelocated_value(a, offset, value));
    if (slot && bits_has(&a->archive->extern_slot, offset, a->archive->size)) {
        *map_slot(&a->references, (uintptr_t) slot, true) =
            key2(offset, UINT32_MAX);
    }
}

void dat_link_extern(DatArchive* a, const char* name, void* address)
{
    for (uint32_t i = 0; i < a->archive->nexterns; i++) {
        const DatSymbol* symbol = &a->archive->externs[i];
        if (strcmp(symbol->name, name)) {
            continue;
        }
        uint32_t offset = symbol->offset;
        for (uint32_t n = 0; n < a->archive->size / 4 &&
                             (uint64_t) offset + 4 <= a->archive->size;
             n++)
        {
            *map_slot(&a->extern_values, offset, true) = (uintptr_t) address;
            offset = dat_reader_word(a, offset);
        }
        break;
    }
    for (size_t i = 0; i < a->references.cap; i++) {
        if (a->references.keys[i] != UINT64_MAX &&
            (uint32_t) a->references.values[i] == UINT32_MAX)
        {
            uint32_t offset = (uint32_t) (a->references.values[i] >> 32);
            dat_reader_store_pointer(
                (void*) (uintptr_t) a->references.keys[i],
                dat_reader_unrelocated_value(a, offset, 0));
        }
    }
}

/* --- Expressions ----------------------------------------------------------
 */

static int dat_reader_lookup(const DatScope* env, int32_t name, uint64_t* out)
{
    for (; env != NULL; env = env->outer) {
        if (env->name == name) {
            *out = env->value;
            return true;
        }
    }
    return false;
}

/// The value of a scalar field of the record at `base`, by name, as the
/// walk reads it: big-endian, floats as the integers C converts them to.
int dat_reader_field_value(const DatArchive* a, int32_t record, uint32_t base,
                           int32_t name, uint64_t* out)
{
    return record != DAT_NONE &&
           dat_reader_T(a, record)->field(a, base, name, out);
}

int dat_reader_resolve_name(const DatArchive* a, const DatContext* c,
                            int32_t name, uint64_t* out)
{
    switch (c->mode) {
    case MODE_COUNT:
        return dat_reader_field_value(a, c->record, c->base, name, out) ||
               dat_reader_lookup(c->env, name, out);
    case MODE_IF: {
        if (dat_reader_field_value(a, c->record, c->base, name, out)) {
            return true;
        }
        if (c->onion != DAT_NONE &&
            dat_reader_T(a, c->onion)
                ->union_field(a, c->union_base, name, out))
        {
            return true;
        }
        return dat_reader_lookup(c->env, name, out);
    }
    case MODE_BIND:
        if (name == a->name_index) {
            *out = c->index;
            return true;
        }
        return dat_reader_field_value(a, c->record, c->base, name, out) ||
               dat_reader_lookup(c->env, name, out);
    case MODE_TERMINATOR:
        return dat_reader_lookup(c->env, name, out);
    case MODE_SCRIPT:
        if (name == a->name_command) {
            *out = c->command;
            return true;
        }
        return false;
    }
    return false;
}

/// See `col_anim_command_length` in `expr.rs`.
int dat_reader_col_anim_command_length(uint64_t command, uint64_t* out)
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
uint64_t dat_reader_cpu_command_length(uint64_t command)
{
    uint8_t c = (uint8_t) command;
    return c == 0x7F ? 0 : c >= 0xC0 ? 3 : c >= 0x80 ? 2 : 1;
}

int dat_reader_it_command_length(uint64_t command, uint64_t* out)
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
int dat_reader_gx_get_tex_buffer_size(uint16_t width, uint16_t height,
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

int dat_reader_eval_at(const DatArchive* a, const DatContext* c,
                       const DatExpr* e, unsigned depth, uint64_t* out)
{
    return e != NULL && e->evaluate(a, c, depth, out);
}

int dat_reader_eval(const DatArchive* a, const DatContext* c, const DatExpr* e,
                    uint64_t* out)
{
    return dat_reader_eval_at(a, c, e, 0, out);
}

/* --- The walk -------------------------------------------------------------
 */

static void dat_reader_reached(DatArchive* a, uint32_t offset, int32_t r)
{
    (void) r;
    bits_set(&a->object, offset, a->archive->size);
    dat_test_reached(a, offset, r);
}

/// Insert into the walk's `visited`; whether it was new.
static int dat_reader_visit(DatArchive* a, uint32_t offset, int32_t r)
{
    uint64_t* v =
        map_slot(&a->visited, key2(offset, dat_reader_T(a, r)->id), true);
    if (*v) {
        return false;
    }
    *v = 1;
    return true;
}

/// The native object for `offset` as type `r`, once it has one.
void* dat_reader_native_of(const DatArchive* a, uint32_t offset, int32_t r)
{
    uint64_t v;
    if (!map_get(&a->natives, key2(offset, dat_reader_T(a, r)->id), &v)) {
        return NULL;
    }
    return (void*) (uintptr_t) v;
}

static void dat_reader_set_native(DatArchive* a, uint32_t offset, int32_t r,
                                  void* native)
{
    if (native == NULL) {
        return;
    }
    uint64_t* v =
        map_slot(&a->natives, key2(offset, dat_reader_T(a, r)->id), true);
    if (*v == 0) {
        *v = (uint64_t) (uintptr_t) native;
    }
}

/// Move an object's views and pointer slots together with its completed bytes.
static void dat_reader_move(DatArchive* a, void* previous, void* native,
                            size_t size)
{
    uintptr_t begin = (uintptr_t) previous, end = begin + size;
    for (size_t i = 0; i < a->natives.cap; i++) {
        if (a->natives.keys[i] == UINT64_MAX) {
            continue;
        }
        uintptr_t value = (uintptr_t) a->natives.values[i];
        if (value >= begin && value < end) {
            a->natives.values[i] = (uintptr_t) native + value - begin;
        }
    }
    memmove(native, previous, size);
    DatMap references = { 0 };
    for (size_t i = 0; i < a->references.cap; i++) {
        if (a->references.keys[i] == UINT64_MAX) {
            continue;
        }
        uintptr_t slot = (uintptr_t) a->references.keys[i];
        if (slot >= begin && slot < end) {
            slot = (uintptr_t) native + slot - begin;
        }
        *map_slot(&references, slot, true) = a->references.values[i];
    }
    map_free(&a->references);
    a->references = references;
    a->native_moved = true;
}

/// Publish the address supplied by an enclosing native object or array.
void dat_reader_place_native(DatArchive* a, uint32_t offset, int32_t r,
                             void* native)
{
    if (native == NULL) {
        return;
    }
    void* previous = dat_reader_native_of(a, offset, r);
    if (previous != NULL && previous != native &&
        previous != a->archive->data + offset)
    {
        dat_reader_move(a, previous, native,
                        dat_reader_T(a, r)->allocation_size(a, offset));
    }
    *map_slot(&a->natives, key2(offset, dat_reader_T(a, r)->id), true) =
        (uintptr_t) native;
}

static void* dat_reader_allocate(DatArchive* a, size_t size)
{
    DatAllocation* allocation = calloc(1, sizeof(*allocation));
    if (allocation == NULL) {
        abort();
    }
    allocation->data = calloc(1, size ? size : 1);
    if (allocation->data == NULL) {
        abort();
    }
    allocation->next = a->allocations;
    a->allocations = allocation;
    return allocation->data;
}

/// Keep converted references so an array discovered later can supply their
/// final addresses. Raw, script and zero-count pointers are not registered.
void dat_reader_reference(DatArchive* a, void* slot, uint32_t offset,
                          int32_t r)
{
    if (slot != NULL && r != DAT_NONE && !dat_reader_opaque(a, r)) {
        r = dat_reader_resolve(a, r);
        if (r == DAT_NONE) {
            return;
        }
        *map_slot(&a->references, (uint64_t) (uintptr_t) slot, true) =
            key2(offset, dat_reader_T(a, r)->id);
    }
}

static void* dat_reader_native_array(DatArchive* a, uint32_t offset, int32_t e,
                                     uint64_t count)
{
    uint64_t key = key2(offset, dat_reader_T(a, e)->id), n;
    void* existing = dat_reader_native_of(a, offset, e);
    if (existing != NULL && map_get(&a->native_counts, key, &n) && n >= count)
    {
        return existing;
    }
    uint32_t ns = dat_reader_T(a, e)->native_size;
    char* block = dat_reader_allocate(a, (size_t) ns * (count ? count : 1));
    for (uint64_t i = 0; i < count; i++) {
        dat_reader_place_native(
            a, (uint32_t) (offset + i * dat_reader_T(a, e)->size), e,
            block + i * ns);
    }
    *map_slot(&a->native_counts, key, true) = count;
    return block;
}

/// Whether any member of a union has a `DAT_IF`.
static int dat_reader_conditioned(const DatType* t)
{
    return t->conditioned;
}

void dat_reader_unrelocated(DatArchive* a, uint32_t offset, uint32_t value)
{
    if (bits_has(&a->archive->extern_slot, offset, a->archive->size)) {
        dat_reader_mark_pointer(a, offset, a->archive->size);
        return;
    }
    if (value == 0) {
        return;
    }
    if (value == UINT32_MAX) {
        dat_test_sentinel(a);
        return;
    }
    dat_reader_issue(a, ISSUE_UNRELOCATED_POINTER, offset, value);
}

void dat_reader_read_object(DatArchive* a, uint32_t offset, int32_t type,
                            const DatScope* env, void* native, void** slot)
{
    const DatScope* outer = a->env;
    a->env = env;
    dat_reader_object(a, offset, type, native, slot);
    a->env = outer;
}

const DatScope* dat_reader_bind_scope(DatArchive* a, const DatScope* outer,
                                      DatBinding binding, DatParent parent,
                                      uint64_t index, DatScope* storage)
{
    return binding == NULL ? outer
                           : binding(a, outer, &parent, index, storage);
}

int dat_reader_fits(const DatArchive* a, uint32_t offset, int32_t type)
{
    int32_t r = dat_reader_resolve(a, type);
    return r == DAT_NONE || dat_reader_T(a, r)->fits(a, offset);
}

/// A native array of `count` of `r` for the data at `offset`; plain data
/// converted, raw data where it is.
static void* dat_reader_plain_array(DatArchive* a, uint32_t offset,
                                    int32_t raw, int32_t r, uint64_t count)
{
    if (dat_reader_opaque(a, raw)) {
        return a->archive->data + offset;
    }
    uint32_t ns = dat_reader_T(a, r)->native_size;
    char* block = dat_reader_native_array(a, offset, r, count);
    for (uint64_t i = 0; i < count; i++) {
        dat_reader_convert(a,
                           (uint32_t) (offset + i * dat_reader_T(a, r)->size),
                           r, block + i * ns);
    }
    return block;
}

/// Whether a counted inline array fits its declared bound and the data.
int dat_reader_array_count_fits(const DatArchive* a, uint32_t offset,
                                int32_t array, int32_t element, uint64_t count)
{
    uint64_t size = dat_reader_T(a, element)->size;
    uint64_t room = a->archive->size > offset ? a->archive->size - offset : 0;
    return count <= room / (size ? size : 1) &&
           (dat_reader_T(a, array)->unbounded ||
            count <= dat_reader_T(a, array)->count);
}

/// Walk an inline array: an explicit count ignores symbols and pointer
/// targets inside it, unlike `DAT_EXTENT`.
static void dat_reader_counted_array(DatArchive* a, uint32_t offset,
                                     int32_t array, uint64_t count,
                                     DatBinding binding, DatScope* storage,
                                     DatParent parent, void* native)
{
    int32_t raw = dat_reader_T(a, array)->target;
    int32_t e = dat_reader_resolve(a, raw);
    if (e == DAT_NONE) {
        return;
    }
    dat_test_count(a, offset, array, 0);
    if (!dat_reader_array_count_fits(a, offset, array, e, count)) {
        dat_reader_issue(a, ISSUE_OUT_OF_BOUNDS, offset, 0);
        return;
    }
    dat_test_count(a, offset, array, count);
    const DatScope* outer = a->env;
    for (uint64_t i = 0; i < count; i++) {
        uint32_t at = (uint32_t) (offset + i * dat_reader_T(a, e)->size);
        a->env = dat_reader_bind_scope(a, outer, binding, parent, i, storage);
        dat_reader_typed_extent(a, at, raw, 1);
        dat_reader_place_native(
            a, at, e,
            native ? (char*) native + i * dat_reader_T(a, e)->native_size
                   : NULL);
        dat_reader_layout(a, at, raw,
                          native ? (char*) native +
                                       i * dat_reader_T(a, e)->native_size
                                 : NULL,
                          parent);
    }
    a->env = outer;
}

/// Walk an inline array or follow a pointer to `count` consecutive elements.
void dat_reader_counted(DatArchive* a, uint32_t offset, int32_t pointer,
                        int32_t element, uint64_t count, DatBinding binding,
                        DatScope* storage, DatParent parent, void* slot)
{
    int32_t p = dat_reader_resolve(a, pointer);
    if (p == DAT_NONE) {
        return;
    }
    int32_t target = DAT_NONE;
    if (dat_reader_T(a, p)->kind == DAT_KIND_ARRAY) {
        dat_reader_counted_array(a, offset, p, count, binding, storage, parent,
                                 slot);
        return;
    } else if (dat_reader_T(a, p)->kind == DAT_KIND_POINTER) {
        target = dat_reader_T(a, p)->target;
    } else if (element == DAT_NONE) {
        DatParent none = { DAT_NONE, 0, false };
        dat_reader_layout(a, offset, pointer, slot, none);
        return;
    }
    uint32_t value = dat_reader_word(a, offset);
    if (!bits_has(&a->archive->reloc, offset, a->archive->size)) {
        dat_reader_store_unrelocated(a, offset, value, slot);
        return;
    }
    dat_reader_mark_pointer(a, offset, a->archive->size);
    int32_t raw = element != DAT_NONE ? element : target;
    int32_t e = element != DAT_NONE ? element : dat_reader_pointee(a, target);
    if (e == DAT_NONE) {
        dat_reader_untyped(a);
        dat_reader_store_pointer(slot, a->archive->data + value);
        return;
    }
    if (raw == DAT_NONE) {
        raw = e;
    }
    uint64_t size = dat_reader_T(a, e)->size;
    uint64_t room = a->archive->size > value ? a->archive->size - value : 0;
    if (count > room / (size ? size : 1) &&
        !(count == 1 && dat_reader_conditioned(dat_reader_T(a, e))))
    {
        dat_reader_issue(a, ISSUE_OUT_OF_BOUNDS, value, 0);
        return;
    }
    if (count > 0 && !dat_reader_opaque(a, raw)) {
        dat_reader_reference(a, slot, value, e);
    }
    if (count > 0 && !dat_reader_T(a, e)->has_pointers &&
        !dat_reader_conditioned(dat_reader_T(a, e)))
    {
        void* block = dat_reader_plain_array(a, value, raw, e, count);
        if (!dat_reader_visit(a, value, e)) {
            if (!dat_reader_opaque(a, raw)) {
                dat_reader_typed_extent(a, value, raw, count);
            }
            dat_reader_store_pointer(slot, block);
            return;
        }
        dat_reader_reached(a, value, e);
        dat_reader_typed_extent(a, value, raw, count);
        dat_reader_set_native(a, value, e, block);
        dat_reader_store_pointer(slot, block);
        dat_reader_relocated_words(a, value, value + count * size);
        return;
    }
    /* None: where it points, which nothing reads */
    if (count == 0) {
        dat_reader_store_pointer(slot, a->archive->data + value);
        return;
    }
    uint32_t ns = dat_reader_native_size(a, raw);
    char* block = dat_reader_native_array(a, value, e, count);
    dat_reader_store_pointer(slot, block);
    const DatScope* outer = a->env;
    for (uint64_t i = 0; i < count; i++) {
        const DatScope* env =
            dat_reader_bind_scope(a, outer, binding, parent, i, storage);
        dat_reader_read_object(a, (uint32_t) (value + i * size), raw, env,
                               block + i * ns, NULL);
    }
}

/// Follow a `DAT_TERMINATED` pointer: elements up to one whose first word
/// is the terminator value, which is walked too.
void dat_reader_terminated(DatArchive* a, uint32_t offset, int32_t pointer,
                           void* slot, const DatExpr* terminator,
                           uint32_t length)
{
    int32_t p = dat_reader_resolve(a, pointer);
    if (p == DAT_NONE) {
        return;
    }
    if (dat_reader_T(a, p)->kind != DAT_KIND_POINTER) {
        DatParent none = { DAT_NONE, 0, false };
        dat_reader_layout(a, offset, pointer, slot, none);
        return;
    }
    uint32_t value = dat_reader_word(a, offset);
    if (!bits_has(&a->archive->reloc, offset, a->archive->size)) {
        dat_reader_store_unrelocated(a, offset, value, slot);
        return;
    }
    dat_reader_mark_pointer(a, offset, a->archive->size);
    int32_t target = dat_reader_T(a, p)->target;
    int32_t e = dat_reader_pointee(a, target);
    if (e == DAT_NONE) {
        dat_reader_untyped(a);
        dat_reader_store_pointer(slot, a->archive->data + value);
        return;
    }
    uint32_t size = dat_reader_T(a, e)->size;
    if (size == 0) {
        return;
    }
    dat_reader_reached(a, value, e);
    DatContext c = { MODE_TERMINATOR, DAT_NONE, 0, DAT_NONE, 0, a->env, 0, 0 };
    uint64_t term;
    if (!dat_reader_eval(a, &c, terminator, &term)) {
        dat_reader_store_pointer(slot, a->archive->data + value);
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
        if (at + size > a->archive->size) {
            past = true;
            break;
        }
        n = i + 1;
        if (ended > 0 || (dat_reader_bytes_at(a, at, width) == (term & mask) &&
                          !bits_has(&a->archive->reloc, at, a->archive->size)))
        {
            ended++;
        }
        if (ended >= (length ? length : 1)) {
            break;
        }
    }
    int32_t ty = target != DAT_NONE ? target : e;
    char* block = NULL;
    uint32_t ns = dat_reader_T(a, e)->native_size;
    if (dat_reader_opaque(a, ty)) {
        dat_reader_store_pointer(slot, a->archive->data + value);
    } else {
        block = dat_reader_native_array(a, value, e, n);
        dat_reader_store_pointer(slot, block);
        dat_reader_reference(a, slot, value, e);
    }
    const DatScope* env = a->env;
    for (uint64_t i = 0; i < n; i++) {
        uint32_t at = (uint32_t) (value + i * size);
        char* native = block ? block + i * ns : NULL;
        if (dat_reader_visit(a, at, e)) {
            dat_reader_set_native(a, at, e, native);
            dat_reader_typed_extent(a, at, ty, 1);
            DatParent none = { DAT_NONE, 0, false };
            dat_reader_layout(a, at, ty, native, none);
        } else {
            dat_reader_place_native(a, at, e, native);
        }
        a->env = env;
    }
    if (past) {
        dat_reader_issue(a, ISSUE_OUT_OF_BOUNDS, value, 0);
    }
}

/// How many elements of `size` a `DAT_EXTENT` array at `offset` can have:
/// up to the next public symbol or pointer target, or the end of the data.
uint64_t dat_reader_extent_bound(const DatArchive* a, uint32_t offset,
                                 uint32_t size)
{
    if (size == 0) {
        return 0;
    }
    uint64_t n = 0;
    for (uint64_t at = offset; at + size <= a->archive->size; at += size, n++)
    {
        if (n > 0 && (bits_has(&a->archive->public, at, a->archive->size) ||
                      bits_has(&a->archive->target, at, a->archive->size)))
        {
            break;
        }
    }
    return n;
}

/// A `DAT_EXTENT` array or pointer: every element until the next public
/// symbol, object or pointer target, the end of the data, or one that
/// doesn't fit its type.
void dat_reader_extent(DatArchive* a, uint32_t offset, int32_t array,
                       DatBinding binding, DatScope* storage, DatParent parent,
                       void* native)
{
    const DatScope* outer = a->env;
    int32_t r = dat_reader_resolve(a, array);
    if (r == DAT_NONE) {
        return;
    }
    int32_t element;
    char* base;
    if (dat_reader_T(a, r)->kind == DAT_KIND_ARRAY) {
        element = dat_reader_T(a, r)->target;
        base = native;
    } else if (dat_reader_T(a, r)->kind == DAT_KIND_POINTER) {
        uint32_t value = dat_reader_word(a, offset);
        if (!bits_has(&a->archive->reloc, offset, a->archive->size)) {
            dat_reader_store_unrelocated(a, offset, value, native);
            return;
        }
        dat_reader_mark_pointer(a, offset, a->archive->size);
        int32_t raw = dat_reader_T(a, r)->target;
        int32_t target = dat_reader_pointee(a, raw);
        if (target == DAT_NONE) {
            dat_reader_untyped(a);
            dat_reader_store_pointer(native, a->archive->data + value);
            return;
        }
        if (!dat_reader_visit(a, value, target)) {
            dat_reader_store_pointer(native,
                                     dat_reader_native_of(a, value, target));
            return;
        }
        dat_reader_reached(a, value, target);
        uint32_t size = dat_reader_T(a, target)->size;
        if (dat_reader_opaque(a, raw != DAT_NONE ? raw : target)) {
            base = NULL;
            dat_reader_store_pointer(native, a->archive->data + value);
        } else {
            uint64_t n = dat_reader_extent_bound(a, value, size);
            base = dat_reader_native_array(a, value, target, n);
            dat_reader_store_pointer(native, base);
            dat_reader_reference(a, native, value, target);
        }
        dat_reader_set_native(a, value, target, base);
        offset = value;
        element = raw;
    } else {
        dat_reader_layout(a, offset, array, native, parent);
        return;
    }
    int32_t e = dat_reader_resolve(a, element);
    if (e == DAT_NONE) {
        return;
    }
    uint32_t size = dat_reader_T(a, e)->size;
    uint32_t ns = dat_reader_T(a, e)->native_size;
    uint64_t count = 0;
    for (;; count++) {
        uint64_t i = count;
        uint64_t at = offset + i * size;
        if (at + size > a->archive->size) {
            break;
        }
        bool boundary = bits_has(&a->archive->public, at, a->archive->size) ||
                        bits_has(&a->archive->target, at, a->archive->size) ||
                        bits_has(&a->object, at, a->archive->size);
        if (i > 0 && (boundary || !dat_reader_fits(a, (uint32_t) at, e))) {
            break;
        }
    }
    /* Bound entries retain the walker's last-entry priority when several
       contexts share one target. Resolve the extent before following them. */
    for (uint64_t step = 0; step < count; step++) {
        uint64_t i = binding ? count - 1 - step : step;
        uint64_t at = offset + i * size;
        a->env = dat_reader_bind_scope(a, outer, binding, parent, i, storage);
        int32_t ty = element != DAT_NONE ? element : e;
        dat_reader_typed_extent(a, (uint32_t) at, ty, 1);
        dat_reader_place_native(a, (uint32_t) at, e,
                                base ? base + i * ns : NULL);
        dat_reader_layout(a, (uint32_t) at, ty, base ? base + i * ns : NULL,
                          parent);
    }
    a->env = outer;
}

/// A `DAT_TYPE` field: followed as a pointer to `target` when relocated.
void dat_reader_typed(DatArchive* a, uint32_t offset, int32_t target,
                      void* native, uint32_t native_field)
{
    if (bits_has(&a->archive->reloc, offset, a->archive->size)) {
        dat_reader_mark_pointer(a, offset, a->archive->size);
        /* A field too small for a native pointer keeps the offset */
        if (native_field >= sizeof(void*)) {
            dat_reader_reference(a, native, dat_reader_word(a, offset),
                                 target);
            dat_reader_read_object(a, dat_reader_word(a, offset), target,
                                   a->env, NULL, native);
        } else {
            dat_reader_read_object(a, dat_reader_word(a, offset), target,
                                   a->env, NULL, NULL);
            if (native != NULL) {
                dat_reader_store_uint(native, native_field,
                                      dat_reader_word(a, offset));
            }
        }
    } else if (native != NULL && native_field != 0) {
        dat_reader_store_uint(native, native_field,
                              dat_reader_word(a, offset));
    }
}

/// Return the command length at `at`: bytes for byte scripts, words otherwise.
static int dat_reader_command_length(const DatArchive* a, const DatScript* s,
                                     uint32_t at, uint64_t* out)
{
    /* Byte scripts use the full first byte and their own length expression. */
    uint32_t command =
        s->bytes ? a->archive->data[at] : dat_reader_word(a, at);
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
    DatContext c = { MODE_SCRIPT, DAT_NONE, 0, DAT_NONE, 0, NULL, 0, command };
    return dat_reader_eval(a, &c, s->length, out);
}

/// Follow a script pointer and any scripts referenced by its commands.
/// Keep script bytes unchanged, including big-endian words and pointer
/// offsets in word scripts.
void dat_reader_script_at(DatArchive* a, uint32_t value, int32_t id,
                          const DatScript* s);

void dat_reader_script(DatArchive* a, uint32_t offset, int32_t pointer,
                       const DatScript* s, void* slot)
{
    int32_t p = dat_reader_resolve(a, pointer);
    if (p == DAT_NONE) {
        return;
    }
    if (dat_reader_T(a, p)->kind != DAT_KIND_POINTER) {
        DatParent none = { DAT_NONE, 0, false };
        dat_reader_layout(a, offset, pointer, slot, none);
        return;
    }
    uint32_t value = dat_reader_word(a, offset);
    if (!bits_has(&a->archive->reloc, offset, a->archive->size)) {
        dat_reader_store_unrelocated(a, offset, value, slot);
        return;
    }
    dat_reader_mark_pointer(a, offset, a->archive->size);
    dat_reader_store_pointer(slot, a->archive->data + value);
    dat_reader_script_at(a, value,
                         dat_reader_pointee(a, dat_reader_T(a, p)->target), s);
}

/// Walk the script at `value` and any scripts its commands reference.
static void dat_reader_script_at(DatArchive* a, uint32_t value, int32_t id,
                                 const DatScript* s)
{
    uint32_t start = value;
    if (!bits_set(&a->script, start, a->archive->size)) {
        return;
    }
    {
        if (id != DAT_NONE) {
            dat_reader_reached(a, start, id);
        }
        uint64_t at = start;
        bool ended = false;
        uint64_t end = 0;
        for (;;) {
            if (at >= a->archive->size) {
                dat_reader_issue(a, ISSUE_OUT_OF_BOUNDS, (uint32_t) at, 0);
                break;
            }
            uint8_t opcode =
                s->bytes ? a->archive->data[at] : a->archive->data[at] >> 2;
            uint64_t length;
            if (!dat_reader_command_length(a, s, (uint32_t) at, &length)) {
                dat_reader_issue(a, ISSUE_UNKNOWN_COMMAND, (uint32_t) at,
                                 opcode);
                break;
            }
            end = at + (length ? length : 1) * (s->bytes ? 1 : 4);
            if (end > a->archive->size) {
                dat_reader_issue(a, ISSUE_OUT_OF_BOUNDS, (uint32_t) at, 0);
                break;
            }
            /* Byte scripts hold no pointers */
            if (!s->bytes) {
                for (uint64_t w = at; w < end; w += 4) {
                    if (bits_has(&a->archive->reloc, w, a->archive->size)) {
                        dat_reader_mark_pointer(a, w, a->archive->size);
                        dat_reader_script_at(a, dat_reader_word(a, w), id, s);
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
            dat_reader_record_extent(a, start, end);
        }
    }
}

void dat_reader_layout(DatArchive* a, uint32_t offset, int32_t type,
                       void* native, DatParent parent)
{
    if (type != DAT_NONE) {
        dat_reader_T(a, type)->read(a, offset, native, &parent);
        int32_t r = dat_reader_resolve(a, type);
        void* final = dat_reader_native_of(a, offset, r);
        if (native != NULL && final != NULL && final != native &&
            final != a->archive->data + offset)
        {
            dat_reader_move(a, native, final,
                            dat_reader_T(a, r)->allocation_size(a, offset));
        }
    }
}

/// The native size of a struct ending in a counted or extent array.
static size_t dat_reader_extent_native_size(DatArchive* a, uint32_t offset,
                                            int32_t r)
{
    return dat_reader_T(a, r)->allocation_size(a, offset);
}

/// Walk one object; see `Walker::object`.
static void dat_reader_object(DatArchive* a, uint32_t offset, int32_t type,
                              void* native_arg, void** slot)
{
    int32_t r = dat_reader_resolve(a, type);
    if (r == DAT_NONE || dat_reader_T(a, r)->kind == DAT_KIND_VOID) {
        return;
    }
    if (!dat_reader_visit(a, offset, r)) {
        void* existing = dat_reader_native_of(a, offset, r);
        if (slot != NULL) {
            dat_reader_store_pointer(slot, existing);
        }
        dat_reader_place_native(a, offset, r, native_arg);
        return;
    }
    /* Every object is made natively, even one reached through a field that
       can't point to it (DAT_TYPE on a narrow integer), so that pointers
       reaching it later can */
    void* native =
        native_arg != NULL ? native_arg : dat_reader_native_of(a, offset, r);
    if (native == NULL) {
        if (dat_reader_opaque(a, type)) {
            native = a->archive->data + offset;
        } else if (dat_reader_T(a, r)->kind == DAT_KIND_ARRAY) {
            int32_t element =
                dat_reader_resolve(a, dat_reader_T(a, r)->target);
            if (element == DAT_NONE) {
                return;
            }
            native = dat_reader_native_array(a, offset, element,
                                             dat_reader_T(a, r)->count);
        } else {
            native = dat_reader_allocate(
                a, dat_reader_extent_native_size(a, offset, r));
        }
    }
    dat_reader_store_pointer(slot, native);
    /* Opaque objects also need an identity for subsequent references. They
       remain archive bytes: layout and verification must not convert them. */
    dat_reader_set_native(a, offset, r, native);
    dat_reader_typed_extent(a, offset, type, 1);
    dat_reader_reached(a, offset, r);
    DatParent none = { DAT_NONE, 0, false };
    dat_reader_layout(a, offset, type,
                      native == a->archive->data + offset ? NULL : native,
                      none);
}

/// Refresh stored pointer fields after a larger array supplies their storage.
static void dat_reader_finish(DatArchive* a)
{
    if (!a->native_moved) {
        return;
    }
    a->native_moved = false;
    for (size_t i = 0; i < a->references.cap; i++) {
        uint64_t key = a->references.keys[i], native;
        if (key != UINT64_MAX &&
            (uint32_t) a->references.values[i] == UINT32_MAX)
        {
            uint32_t offset = (uint32_t) (a->references.values[i] >> 32);
            dat_reader_store_pointer(
                (void*) (uintptr_t) key,
                dat_reader_unrelocated_value(a, offset, 0));
        } else if (key != UINT64_MAX &&
                   map_get(&a->natives, a->references.values[i], &native))
        {
            dat_reader_store_pointer((void*) (uintptr_t) key,
                                     (void*) (uintptr_t) native);
        }
    }
}

/// Walk an object and everything it reaches; see `Walker::root`.
static void* dat_reader_walk_root(DatArchive* a, uint32_t offset, int32_t type,
                                  const DatScope* env)
{
    void* native = NULL;
    dat_reader_read_object(a, offset, type, env, NULL, &native);
    dat_reader_finish(a);
    return dat_reader_native_of(a, offset, dat_reader_resolve(a, type));
}

/// Walk `count` elements, or as many as fit before the next public symbol
/// or pointer target; see `Walker::root_array`.
static void* dat_reader_walk_root_array(DatArchive* a, uint32_t offset,
                                        int32_t element, uint8_t bounded,
                                        uint64_t count, const DatScope* env)
{
    a->env = env;
    int32_t raw = element;
    int32_t e = dat_reader_resolve(a, element);
    if (e == DAT_NONE || dat_reader_T(a, e)->kind == DAT_KIND_VOID) {
        return NULL;
    }
    if (bounded && count == 1 && dat_reader_conditioned(dat_reader_T(a, e))) {
        return dat_reader_walk_root(a, offset, raw, env);
    }
    uint64_t size = dat_reader_T(a, e)->size;
    if (size == 0 || !dat_reader_visit(a, offset, e)) {
        return dat_reader_native_of(a, offset, e);
    }
    dat_reader_reached(a, offset, e);
    uint64_t room = a->archive->size > offset ? a->archive->size - offset : 0;
    if (!bounded) {
        uint64_t end = room;
        for (uint64_t at = (uint64_t) offset + 1; at < a->archive->size; at++)
        {
            if (bits_has(&a->archive->public, at, a->archive->size) ||
                bits_has(&a->archive->target, at, a->archive->size))
            {
                end = at - offset;
                break;
            }
        }
        count = (end < room ? end : room) / size;
    }
    if (count * size > room) {
        dat_reader_issue(a, ISSUE_OUT_OF_BOUNDS, offset, 0);
    }
    if (count > room / size) {
        count = room / size;
    }
    dat_reader_typed_extent(a, offset, raw, count);
    if (!dat_reader_T(a, e)->has_pointers &&
        !dat_reader_conditioned(dat_reader_T(a, e)))
    {
        void* block = dat_reader_plain_array(a, offset, raw, e, count);
        dat_reader_set_native(a, offset, e, block);
        dat_reader_relocated_words(a, offset, offset + count * size);
        return block;
    }
    uint32_t ns = dat_reader_T(a, e)->native_size;
    char* block = dat_reader_native_array(a, offset, e, count);
    dat_reader_set_native(a, offset, e, block);
    for (uint64_t i = 0; i < count; i++) {
        /* Each element starts with the root's bindings */
        a->env = env;
        uint32_t at = (uint32_t) (offset + i * size);
        if (i > 0) {
            dat_reader_set_native(a, at, e, block + i * ns);
        }
        DatParent none = { DAT_NONE, 0, false };
        dat_reader_layout(a, at, e, block + i * ns, none);
    }
    dat_reader_finish(a);
    return dat_reader_native_of(a, offset, e);
}

/// How many elements of `type` a list at `offset` holds, up to and
/// including the first whose first word is `term` and not relocated.
static uint64_t dat_reader_terminated_count(const DatArchive* a,
                                            uint32_t offset, int32_t type,
                                            uint64_t term)
{
    int32_t e = dat_reader_resolve(a, type);
    if (e == DAT_NONE || dat_reader_T(a, e)->size == 0) {
        return 0;
    }
    uint32_t size = dat_reader_T(a, e)->size;
    uint32_t width = size < 4 ? size : 4;
    uint64_t mask = (1ull << (8 * width)) - 1;
    uint64_t n = 0;
    for (uint64_t at = offset; at + size <= a->archive->size; at += size) {
        n++;
        if (dat_reader_bytes_at(a, at, width) == (term & mask) &&
            !bits_has(&a->archive->reloc, at, a->archive->size))
        {
            break;
        }
    }
    return n;
}

static void* dat_reader_walk(DatArchive* a, uint32_t offset,
                             const DatRoot* root, int32_t type, DatCount count,
                             uint64_t n)
{
    const DatScope* env = root ? root->env : NULL;
    switch (count) {
    case DAT_COUNT_ONE:
        return dat_reader_walk_root(a, offset, type, env);
    case DAT_COUNT_EXACTLY:
        return dat_reader_walk_root_array(a, offset, type, true, n, env);
    case DAT_COUNT_EXTENT:
        return dat_reader_walk_root_array(a, offset, type, false, 0, env);
    case DAT_COUNT_TERMINATED:
        return dat_reader_walk_root_array(
            a, offset, type, true,
            dat_reader_terminated_count(a, offset, type, n), env);
    }
    return NULL;
}

void* dat_at(DatArchive* a, uint32_t offset, int32_t type, DatCount count,
             uint64_t n)
{
    if (type <= DAT_NONE || (uint32_t) type >= a->s->ntypes) {
        return NULL;
    }
    void* result = dat_reader_walk(a, offset, NULL, type, count, n);
    dat_reader_finish(a);
    return result;
}

void* dat_public(DatArchive* a, const char* name, int32_t type)
{
    if (type <= DAT_NONE || (uint32_t) type >= a->s->ntypes) {
        return NULL;
    }
    const DatSymbol* symbol = dat_archive_public(a->archive, name);
    if (!symbol) {
        return NULL;
    }
    /* Loader bindings are constants generated for this public symbol/type. */
    for (uint32_t i = 0; i < a->s->nmodules; i++) {
        const DatModule* module = &a->s->modules[i];
        for (uint32_t j = 0; j < module->nfiles; j++) {
            const DatFileRoots* file = &module->files[j];
            for (uint32_t k = 0; k < file->nroots; k++) {
                const DatRoot* root = &file->roots[k];
                if (!root->alias && !strcmp(root->name, name) &&
                    dat_reader_resolve(a, root->type) ==
                        dat_reader_resolve(a, type))
                {
                    return dat_reader_walk(a, symbol->offset, root, type,
                                           (DatCount) root->count_kind,
                                           root->count);
                }
            }
        }
    }
    return dat_at(a, symbol->offset, type, DAT_COUNT_ONE, 0);
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
    for (uint32_t i = 0; i < a->archive->npublics; i++) {
        for (uint32_t j = 0; j < f->nroots; j++) {
            const DatRoot* root = &f->roots[j];
            if (root->alias ||
                strcmp(root->name, a->archive->publics[i].name) != 0)
            {
                continue;
            }
            dat_reader_walk(a, a->archive->publics[i].offset, root, root->type,
                            (DatCount) root->count_kind, root->count);
            found++;
            break;
        }
    }
    for (uint32_t j = 0; j < f->nroots; j++) {
        const DatRoot* root = &f->roots[j];
        if (root->alias && root->script != NULL) {
            a->env = root->env;
            dat_reader_script_at(a, root->address,
                                 dat_reader_pointee(a, root->type),
                                 root->script);
            dat_reader_finish(a);
            found++;
        } else if (root->alias) {
            dat_reader_walk(a, root->address, root, root->type,
                            (DatCount) root->count_kind, root->count);
            found++;
        }
    }
    dat_reader_finish(a);
    return found;
}

int dat_reader_read_field(const DatArchive* a, uint64_t at, uint32_t size,
                          uint8_t floating, uint64_t* out)
{
    if (at + size > a->archive->size) {
        return 0;
    }
    uint64_t v = dat_reader_bytes_at(a, at, size);
    if (floating) {
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
    *out = v;
    return true;
}
