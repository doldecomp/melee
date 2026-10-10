/**
 * @file
 * Reads HSD archives (`.dat`) into the game's own C types on any platform.
 *
 * An archive is big-endian data laid out for a 32-bit target, whose
 * pointers are offsets the loader relocates (`lbarchive.c`). This library
 * walks it the way `melee-dat`'s walker does, from the roots the game loads
 * by name, and writes what it reaches as native objects: scalars converted
 * to the host's byte order and sizes, pointers to the native objects they
 * refer to.
 *
 * Rust generates each type's reader and verifier from DWARF. The native
 * compiler supplies its field offsets and sizes through `offsetof` and
 * `sizeof`. Archive loading itself needs no schema; generated readers use
 * shared storage and reference helpers to build native objects.
 *
 * Data with no type to convert by is left as the archive has it, in its
 * original byte order: pointers to raw bytes (`u8`, `DAT_BLOB` formats such
 * as textures and display lists), command scripts and untyped pointers
 * (`void*`) point into a copy of the archive's data, whose own pointers are
 * still offsets (see dat_raw()).
 */

#ifndef DAT_ARCHIVE_H
#define DAT_ARCHIVE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <dat/schema.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DatArchive DatArchive;

/// What a trace prints: everything, for comparing with `melee-dat native
/// expect`.
typedef enum DatTrace {
    DAT_TRACE_OBJECTS = 1 << 0,
    DAT_TRACE_POINTERS = 1 << 1,
    DAT_TRACE_EXTENTS = 1 << 2,
    DAT_TRACE_CHOICES = 1 << 3,
    DAT_TRACE_ISSUES = 1 << 4,
    DAT_TRACE_COUNTS = 1 << 5,
    DAT_TRACE_ALL = (1 << 6) - 1,
} DatTrace;

/// Open one archive in `bytes`, which is copied. `NULL` if it is malformed
/// in a way the game would misread, with why in `error` if given.
DatArchive* dat_open(const DatSchema* schema, const void* bytes, size_t size,
                     const char** error);

/// Every archive in a file, which some (`Pl??AJ.dat`) pack several of,
/// each padded to 32 bytes, with where each starts in `offsets` if given.
/// Returns how many, up to `max`, or -1 if any is malformed.
int dat_open_packed(const DatSchema* schema, const void* bytes, size_t size,
                    DatArchive** out, size_t* offsets, int max,
                    const char** error);

void dat_close(DatArchive* archive);

/// Walk and convert the roots `melee-dat` gives the `index`th archive of
/// `file`. Returns how many roots it found.
int dat_load_roots(DatArchive* archive, const char* file, uint32_t index);

/// The public symbol `name` as an object of type `type`, converted with
/// everything it reaches; `NULL` if there is none.
void* dat_public(DatArchive* archive, const char* name, int32_t type);

/// The object at `offset` as `count` of type `type`.
void* dat_at(DatArchive* archive, uint32_t offset, int32_t type,
             DatCount count, uint64_t n);

/// The archive's data as it is in the file: big-endian, with offsets for
/// pointers. Raw data and untyped pointers point into it.
const uint8_t* dat_raw(const DatArchive* archive, uint32_t offset);

/// The data's size.
uint32_t dat_size(const DatArchive* archive);

/// Write what the walk reached, sorted, in the form `melee-dat native
/// expect` does.
void dat_trace(const DatArchive* archive, FILE* out, unsigned what);

/// Check every converted object against the data it came from, reading it
/// back natively. Returns the number of mismatches, writing each to `out`
/// if given.
size_t dat_verify(const DatArchive* archive, FILE* out);

/// The index of a type by its trace id, or `DAT_NONE`.
int32_t dat_type_by_id(const DatSchema* schema, uint32_t id);

#ifdef __cplusplus
}
#endif

#endif
