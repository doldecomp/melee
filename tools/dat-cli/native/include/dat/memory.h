#ifndef DAT_MEMORY_H
#define DAT_MEMORY_H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/// A set of offsets in the data.
typedef struct DatOffsets {
    uint32_t* words;
} Bits;

static inline void bits_init(Bits* b, uint32_t size)
{
    b->words = calloc(size / 32 + 2, sizeof(uint32_t));
    if (b->words == NULL) {
        abort();
    }
}

static inline bool bits_has(const Bits* b, uint64_t at, uint32_t size)
{
    return at < size && (b->words[at / 32] >> (at % 32) & 1);
}

/// Insert; whether it was new.
static inline bool bits_set(Bits* b, uint64_t at, uint32_t size)
{
    if (at >= size || bits_has(b, at, size)) {
        return false;
    }
    b->words[at / 32] |= 1u << (at % 32);
    return true;
}

/// A hash map from 64-bit keys to 64-bit values; key `UINT64_MAX` is free.
typedef struct DatMap {
    uint64_t* keys;
    uint64_t* values;
    size_t len, cap;
} DatMap;

static inline uint64_t mix(uint64_t x)
{
    x ^= x >> 33;
    x *= 0xFF51AFD7ED558CCDull;
    x ^= x >> 33;
    x *= 0xC4CEB9FE1A85EC53ull;
    x ^= x >> 33;
    return x;
}

static inline void map_grow(DatMap* m);

static inline uint64_t* map_slot(DatMap* m, uint64_t key, bool insert)
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

static inline void map_grow(DatMap* m)
{
    DatMap old = *m;
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

static inline bool map_get(const DatMap* m, uint64_t key, uint64_t* value)
{
    uint64_t* slot = map_slot((DatMap*) m, key, false);
    if (slot != NULL && value != NULL) {
        *value = *slot;
    }
    return slot != NULL;
}

static inline void map_free(DatMap* m)
{
    free(m->keys);
    free(m->values);
}

static inline uint64_t key2(uint32_t offset, uint32_t id)
{
    return (uint64_t) offset << 32 | id;
}

#endif
