/** @file Traces and readback; excluded from the production archive library. */
#include <dat/reader-internal.h>
uint64_t dat_reader_load_uint(const void* src, uint32_t size)
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

static const char* const issue_names[] = {
    "unrelocated-pointer", "relocated-scalar", "out-of-bounds",
    "ambiguous-union",     "unknown-command",
};
void dat_test_init(DatArchive* a)
{
    a->validation = calloc(1, sizeof(*a->validation));
    if (!a->validation) {
        abort();
    }
    bits_init(&a->validation->pointer, a->archive->size);
}
void dat_test_close(DatArchive* a)
{
    DatValidation* d = a->validation;
    free(d->pointer.words);
    map_free(&d->extents);
    map_free(&d->choices);
    map_free(&d->array_counts);
    map_free(&d->reached_seen);
    free(d->reached.items);
    free(d->chosen.items);
    free(d->issues.items);
    free(d);
}
void dat_test_reached(DatArchive* a, uint32_t offset, int32_t r)
{
    uint32_t id = dat_reader_T(a, r)->id;
    uint64_t* seen =
        map_slot(&a->validation->reached_seen, key2(offset, id), true);
    if (*seen == 0) {
        *seen = 1;
        DatReached x = { offset, id };
        VEC_PUSH(a->validation->reached, x);
    }
}
void dat_test_count(DatArchive* a, uint32_t offset, int32_t type,
                    uint64_t count)
{
    *map_slot(&a->validation->array_counts,
              key2(offset, dat_reader_T(a, type)->id), true) = count;
}
void dat_test_sentinel(DatArchive* a)
{
    a->validation->sentinels++;
}

void dat_reader_mark_pointer(DatArchive* a, uint32_t offset, uint32_t size)
{
    bits_set(&a->validation->pointer, offset, size);
}

void dat_reader_issue(DatArchive* a, DatIssueKind kind, uint32_t at,
                      uint32_t value)
{
    DatIssue i = { (uint8_t) kind, at, value };
    VEC_PUSH(a->validation->issues, i);
}

void dat_reader_record_extent(DatArchive* a, uint32_t offset, uint64_t end)
{
    uint64_t* e = map_slot(&a->validation->extents, offset, true);
    if (end > *e) {
        *e = end;
    }
}

void dat_reader_typed_extent(DatArchive* a, uint32_t offset, int32_t type,
                             uint64_t count)
{
    if (dat_reader_T(a, type)->raw) {
        return;
    }
    int32_t r = dat_reader_resolve(a, type);
    if (r == DAT_NONE) {
        return;
    }
    if (count == 1 && dat_reader_T(a, r)->conditioned) {
        return;
    }
    uint64_t end = offset + (uint64_t) dat_reader_T(a, r)->size * count;
    dat_reader_record_extent(a, offset, end);
}

void dat_reader_untyped(DatArchive* a)
{
    a->validation->untyped_pointers++;
}

void dat_reader_relocated_words(DatArchive* a, uint32_t start, uint64_t end)
{
    for (uint32_t i = 0; i < a->archive->nrelocs; i++) {
        uint32_t at = a->archive->relocs[i];
        if (at >= start && at < end) {
            dat_reader_issue(a, ISSUE_RELOCATED_SCALAR, at, 0);
        }
    }
}

static int dat_reader_compare_pair(const void* x, const void* y)
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

static int dat_reader_compare_triple(const void* x, const void* y)
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

const char* dat_reader_type_name(const DatArchive* a, uint32_t id)
{
    int32_t t = dat_type_by_id(a->s, id);
    return t == DAT_NONE ? "?" : a->s->types[t]->name;
}

void dat_trace(const DatArchive* a, FILE* out, unsigned what)
{
    if (what & DAT_TRACE_OBJECTS) {
        size_t n = a->validation->reached.len;
        uint32_t* rows = malloc((n + 1) * 2 * sizeof(uint32_t));
        for (size_t i = 0; i < n; i++) {
            rows[2 * i] = a->validation->reached.items[i].offset;
            rows[2 * i + 1] = a->validation->reached.items[i].id;
        }
        qsort(rows, n, 2 * sizeof(uint32_t), dat_reader_compare_pair);
        for (size_t i = 0; i < n; i++) {
            fprintf(out, "object 0x%X %u %s\n", rows[2 * i], rows[2 * i + 1],
                    dat_reader_type_name(a, rows[2 * i + 1]));
        }
        free(rows);
    }
    if (what & DAT_TRACE_POINTERS) {
        for (uint32_t at = 0; at < a->archive->size; at++) {
            if (bits_has(&a->validation->pointer, at, a->archive->size)) {
                fprintf(out, "pointer 0x%X\n", at);
            }
        }
    }
    if (what & DAT_TRACE_EXTENTS) {
        uint32_t* rows =
            malloc((a->validation->extents.len + 1) * 2 * sizeof(uint32_t));
        size_t n = 0;
        for (size_t i = 0; i < a->validation->extents.cap; i++) {
            if (a->validation->extents.keys[i] != UINT64_MAX) {
                rows[2 * n] = (uint32_t) a->validation->extents.keys[i];
                rows[2 * n + 1] = (uint32_t) a->validation->extents.values[i];
                n++;
            }
        }
        qsort(rows, n, 2 * sizeof(uint32_t), dat_reader_compare_pair);
        for (size_t i = 0; i < n; i++) {
            fprintf(out, "extent 0x%X 0x%X\n", rows[2 * i], rows[2 * i + 1]);
        }
        free(rows);
    }
    if (what & DAT_TRACE_CHOICES) {
        size_t n = a->validation->chosen.len;
        uint32_t* rows = malloc((n + 1) * 3 * sizeof(uint32_t));
        for (size_t i = 0; i < n; i++) {
            const DatChoice* c = &a->validation->chosen.items[i];
            uint64_t index = 0;
            map_get(&a->validation->choices, key2(c->offset, c->id), &index);
            rows[3 * i] = c->offset;
            rows[3 * i + 1] = c->id;
            rows[3 * i + 2] = (uint32_t) index - 1;
        }
        qsort(rows, n, 3 * sizeof(uint32_t), dat_reader_compare_triple);
        for (size_t i = 0; i < n; i++) {
            fprintf(out, "choice 0x%X %u %u\n", rows[3 * i], rows[3 * i + 1],
                    rows[3 * i + 2]);
        }
        free(rows);
    }
    if (what & DAT_TRACE_ISSUES) {
        size_t n = a->validation->issues.len;
        uint32_t* rows = malloc((n + 1) * 3 * sizeof(uint32_t));
        for (size_t i = 0; i < n; i++) {
            rows[3 * i] = a->validation->issues.items[i].kind;
            rows[3 * i + 1] = a->validation->issues.items[i].at;
            rows[3 * i + 2] = a->validation->issues.items[i].value;
        }
        qsort(rows, n, 3 * sizeof(uint32_t), dat_reader_compare_triple);
        for (size_t i = 0; i < n; i++) {
            if (i > 0 && dat_reader_compare_triple(&rows[3 * i],
                                                   &rows[3 * (i - 1)]) == 0)
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
                a->validation->untyped_pointers, a->validation->sentinels);
    }
}

void dat_reader_mismatch(DatVerify* v, uint32_t at, const char* what,
                         uint64_t want, uint64_t got)
{
    v->mismatches++;
    if (v->out != NULL) {
        fprintf(v->out, "mismatch 0x%X %s: want 0x%llX, got 0x%llX\n", at,
                what, (unsigned long long) want, (unsigned long long) got);
    }
}

void dat_reader_verify(DatVerify* v, uint32_t offset, int32_t type,
                       const void* native, int depth)
{
    const DatArchive* a = v->a;
    int32_t r = dat_reader_resolve(a, type);
    if (r == DAT_NONE || native == NULL || depth > 64) {
        return;
    }
    const DatType* t = dat_reader_T(a, r);
    if (!t->conditioned && (uint64_t) offset + t->size > a->archive->size) {
        return;
    }
    uint64_t key = key2(offset, t->id), previous;
    if (map_get(&v->checked, key, &previous) &&
        previous == (uint64_t) (uintptr_t) native)
    {
        return;
    }
    *map_slot(&v->checked, key, true) = (uint64_t) (uintptr_t) native;
    t->verify(v, offset, native, depth);
}

size_t dat_verify(const DatArchive* a, FILE* out)
{
    DatVerify v = { .a = a, .out = out };
    for (size_t i = 0; i < a->natives.cap; i++) {
        if (a->natives.keys[i] != UINT64_MAX) {
            *map_slot(&v.offsets, a->natives.values[i], true) =
                a->natives.keys[i];
        }
    }
    for (size_t i = 0; i < a->natives.cap; i++) {
        if (a->natives.keys[i] == UINT64_MAX) {
            continue;
        }
        uint32_t offset = (uint32_t) (a->natives.keys[i] >> 32);
        uint32_t id = (uint32_t) a->natives.keys[i];
        const void* native = (const void*) (uintptr_t) a->natives.values[i];
        int32_t type = dat_type_by_id(a->s, id);
        if (type != DAT_NONE && native != a->archive->data + offset) {
            dat_reader_verify(&v, offset, type, native, 0);
        }
    }
    map_free(&v.checked);
    map_free(&v.offsets);
    return v.mismatches;
}

void dat_reader_record_choice(DatArchive* a, uint32_t offset, int32_t type,
                              uint32_t index)
{
    uint32_t id = dat_reader_T(a, type)->id;
    DatChoice choice = { offset, id, index };
    uint64_t* seen = map_slot(&a->validation->choices, key2(offset, id), true);
    if (*seen == 0) {
        VEC_PUSH(a->validation->chosen, choice);
    }
    *seen = index + 1;
}
