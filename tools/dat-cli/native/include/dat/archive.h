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
 * What it knows of the types comes from tables `melee-dat native codegen`
 * generates from the DWARF, which describe each type as the archive lays it
 * out and say where its members go natively (`offsetof`, `sizeof`), so the
 * host compiler decides the native layout.
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

#ifdef __cplusplus
extern "C" {
#endif

/// No index: no type, expression, script or member.
#define DAT_NONE (-1)

typedef enum DatKind {
    /// `void`, functions, and types without a definition: nothing to read.
    DAT_KIND_VOID,
    /// Integers, characters, booleans and enumerations.
    DAT_KIND_INT,
    DAT_KIND_FLOAT,
    DAT_KIND_POINTER,
    DAT_KIND_STRUCT,
    DAT_KIND_UNION,
    DAT_KIND_ARRAY,
    /// A typedef, which may carry `DAT_TERMINATED`, `DAT_TYPE` or
    /// `DAT_BLOB`.
    DAT_KIND_TYPEDEF,
    /// `const`, `volatile` or `restrict`: transparent, but the end of a
    /// search for a typedef's annotations.
    DAT_KIND_QUALIFIER,
} DatKind;

typedef struct DatType {
    /// The type's name, for traces.
    const char* name;
    /// The generator's id for it, which traces print.
    uint32_t id;
    uint8_t kind;
    /// `DAT_KIND_INT`: whether it is signed, which widening follows.
    uint8_t is_signed;
    /// Raw bytes: `u8`, or arrays of it, not named by a `DAT_BLOB` typedef.
    uint8_t raw;
    /// A `DAT_BLOB` typedef.
    uint8_t blob;
    /// Whether any part of it is a pointer, not looking through pointers.
    uint8_t has_pointers;
    /// A struct whose last member is a `DAT_EXTENT` array.
    uint8_t has_extent;
    /// Its size in the archive.
    uint32_t size;
    /// Its size natively; 0 where the generator couldn't spell it.
    uint32_t native_size;
    /// Pointers: the type pointed to, `DAT_NONE` for `void`. Typedefs and
    /// qualifiers: the type named. Arrays: the element type.
    int32_t target;
    /// Through typedefs and qualifiers: the type it is.
    int32_t resolved;
    /// Arrays: the number of elements, every dimension's together; a
    /// dimension without a bound counts as one.
    uint32_t count;
    /// Structs and unions: their members, a range of DatSchema::members.
    uint32_t members, nmembers;
    /// Typedefs: `DAT_TERMINATED`'s value, an expression.
    int32_t terminator;
    /// Typedefs: `DAT_TYPE`'s type.
    int32_t type_tag;
} DatType;

typedef struct DatMember {
    /// Its name, an index into DatSchema::names, or `DAT_NONE`.
    int32_t name;
    int32_t type;
    /// Where it is in the archive's record, in bytes. Bitfields have
    /// `bit_size` bits from bit `bit_offset` of the record, counted from the
    /// most significant bit of its first byte.
    uint32_t offset;
    uint32_t bit_offset;
    uint8_t bit_size;
    uint8_t has_offset;
    /// `DAT_EXTENT`.
    uint8_t extent;
    /// Where it is natively, in bytes; for bitfields, see `set_bits`.
    uint32_t native_offset;
    /// Its native size; 0 for bitfields.
    uint32_t native_size;
    /// A bitfield's accessors, given its native record.
    void (*set_bits)(void* record, uint64_t value);
    uint64_t (*get_bits)(const void* record);
    /// Expressions: `DAT_COUNT`, `DAT_TERMINATED` and `DAT_IF`.
    int32_t count;
    int32_t terminator;
    int32_t cond;
    /// `DAT_TYPE`.
    int32_t type_tag;
    /// `DAT_SCRIPT`, an index into DatSchema::scripts.
    int32_t script;
    /// `DAT_BIND`s, a range of DatSchema::binds.
    uint32_t binds, nbinds;
} DatMember;

typedef enum DatOp {
    /// `value`.
    DAT_OP_INT,
    /// A name, `a` (an index into DatSchema::names): resolved as the walker
    /// does where the expression is, else as its macro, the expression `b`.
    DAT_OP_NAME,
    /// Function `a` (DatFunction) of `value` arguments, the expressions
    /// listed from DatSchema::args[b].
    DAT_OP_CALL,
    DAT_OP_NOT,
    DAT_OP_BITNOT,
    DAT_OP_NEG,
    DAT_OP_OR,
    DAT_OP_AND,
    DAT_OP_BITOR,
    DAT_OP_BITXOR,
    DAT_OP_BITAND,
    DAT_OP_EQ,
    DAT_OP_NE,
    DAT_OP_LT,
    DAT_OP_GT,
    DAT_OP_LE,
    DAT_OP_GE,
    DAT_OP_SHL,
    DAT_OP_SHR,
    DAT_OP_ADD,
    DAT_OP_SUB,
    DAT_OP_MUL,
    DAT_OP_DIV,
    DAT_OP_REM,
    /// Always fails: a macro nested too deeply.
    DAT_OP_FAIL,
} DatOp;

typedef enum DatFunction {
    DAT_FN_IT_COMMAND_LENGTH,
    DAT_FN_GX_GET_TEX_BUFFER_SIZE,
} DatFunction;

/// An expression node: operands `a` and `b` are other nodes' indices.
/// Arithmetic is unsigned 64-bit, as `melee-dat` evaluates it.
typedef struct DatExpr {
    uint8_t op;
    int32_t a, b;
    uint64_t value;
} DatExpr;

/// `DAT_BIND(name, value)`.
typedef struct DatBind {
    int32_t name;
    int32_t value;
} DatBind;

/// `DAT_SCRIPT`: the lengths of a script's own commands, from opcode 10,
/// as a table of words or an expression in `_command`.
typedef struct DatScript {
    const uint8_t* table;
    uint32_t table_size;
    int32_t length;
} DatScript;

typedef enum DatCount {
    DAT_COUNT_ONE,
    DAT_COUNT_EXACTLY,
    /// As many as fit before the next public symbol or pointer target.
    DAT_COUNT_EXTENT,
} DatCount;

/// A value a root's loader binds, for `DAT_IF` and `DAT_BIND` names.
typedef struct DatRootBind {
    int32_t name;
    uint64_t value;
} DatRootBind;

/// A root of an archive: a public symbol by name, or an alias at an
/// address.
typedef struct DatRoot {
    const char* name;
    /// For an alias: where it is in the first archive of the file.
    uint8_t alias;
    uint32_t address;
    int32_t type;
    uint8_t count_kind;
    uint64_t count;
    /// A range of DatSchema::root_binds.
    uint32_t binds, nbinds;
} DatRoot;

/// The roots of one archive of a file, as `melee-dat` types them.
typedef struct DatFileRoots {
    /// The file, relative to the game's files, e.g. `PlCo.dat`.
    const char* file;
    /// Which archive of the file, for files that pack several.
    uint32_t archive;
    /// A range of DatSchema::roots: public symbols, then aliases.
    uint32_t roots, nroots;
} DatFileRoots;

typedef struct DatSchema {
    const DatType* types;
    uint32_t ntypes;
    const DatMember* members;
    const DatExpr* exprs;
    const int32_t* args;
    const DatBind* binds;
    const DatScript* scripts;
    const char* const* names;
    uint32_t nnames;
    const DatRoot* roots;
    const DatRootBind* root_binds;
    const DatFileRoots* files;
    uint32_t nfiles;
} DatSchema;

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
