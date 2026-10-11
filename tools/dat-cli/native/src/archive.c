/** @file Native archive loading, relocation tables and symbol lookup. */
#include <dat/archive-data.h>

static uint32_t be32(const uint8_t* p)
{
    return (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
           (uint32_t) p[2] << 8 | p[3];
}

/// The word at `offset`, or 0 past the data.
static uint32_t word(const DatArchiveData* a, uint64_t offset)
{
    return offset + 4 <= a->size ? be32(a->data + offset) : 0;
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

DatArchiveData* dat_archive_open(const void* bytes, size_t size,
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
    DatArchiveData* a = calloc(1, sizeof(DatArchiveData));
    if (a == NULL) {
        abort();
    }
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
        dat_archive_close(a);
        goto fail;
    }

    bits_init(&a->reloc, data_size);
    bits_init(&a->extern_slot, data_size);
    bits_init(&a->public, data_size);
    bits_init(&a->target, data_size);
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
    return a;

fail:
    if (error != NULL) {
        *error = why;
    }
    return NULL;
}

void dat_archive_close(DatArchiveData* a)
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
    free(a);
}

const DatSymbol* dat_archive_public(const DatArchiveData* a, const char* name)
{
    for (uint32_t i = 0; i < a->npublics; i++) {
        if (strcmp(a->publics[i].name, name) == 0) {
            return &a->publics[i];
        }
    }
    return NULL;
}

int dat_archive_open_packed(const void* bytes, size_t size,
                            DatArchiveData** out, size_t* offsets, int max,
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
        out[n] = dat_archive_open(b + offset, file_size, error);
        if (out[n] == NULL) {
            goto fail;
        }
        n++;
        offset += (file_size + 31) & ~(size_t) 31;
    }
    return n;

fail:
    while (n > 0) {
        dat_archive_close(out[--n]);
    }
    return -1;
}
