/**
 * @file
 * What the library knows of the archives' types and roots: a schema of
 * descriptors, one per type, which `melee-dat native codegen` writes from
 * the DWARF (or tests write by hand).
 *
 * Each type is a DatType, referred to by its index in DatSchema::types; a
 * struct or union lists its members, each a DatMember saying where it is in
 * the archive's record and natively. The `dat_macros.h` annotations on the
 * game's types become the members' expressions (DatExpr), scripts and
 * bindings.
 *
 * Every field's zero is its default, so descriptors are written with
 * designated initializers, naming only what they have: index 0 is no type
 * and no name (`DAT_NONE`), and no expression or script is `NULL`.
 */

#ifndef DAT_SCHEMA_H
#define DAT_SCHEMA_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// No type and no name: index 0 of DatSchema::types and DatSchema::names.
#define DAT_NONE 0

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

typedef enum DatOp {
    /// `value`.
    DAT_OP_INT,
    /// `name`: resolved as the walker does where the expression is, else as
    /// its macro, the expression `b`, if it has one.
    DAT_OP_NAME,
    /// `function` of the `nargs` expressions `args`.
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
    /// Always fails: a call to a function the library doesn't port.
    DAT_OP_FAIL,
} DatOp;

typedef enum DatFunction {
    DAT_FN_IT_COMMAND_LENGTH,
    DAT_FN_GX_GET_TEX_BUFFER_SIZE,
} DatFunction;

/// An expression node. Arithmetic is unsigned 64-bit, as `melee-dat`
/// evaluates it.
typedef struct DatExpr {
    uint8_t op;
    /// DAT_OP_NAME: an index into DatSchema::names.
    int32_t name;
    /// DAT_OP_CALL.
    uint8_t function;
    uint8_t nargs;
    const struct DatExpr* const* args;
    /// Operands; for DAT_OP_NAME, `b` is the name's macro.
    const struct DatExpr* a;
    const struct DatExpr* b;
    uint64_t value;
} DatExpr;

/// `DAT_BIND(name, value)`.
typedef struct DatBind {
    int32_t name;
    const DatExpr* value;
} DatBind;

/// `DAT_SCRIPT`: the lengths of a script's own commands, from opcode 10,
/// as a table of words or an expression in `_command`.
typedef struct DatScript {
    const uint8_t* table;
    uint32_t table_size;
    const DatExpr* length;
} DatScript;

typedef struct DatMember {
    /// Its name, an index into DatSchema::names, or `DAT_NONE`.
    int32_t name;
    int32_t type;
    /// Where it is in the archive's record, in bytes, if `has_offset`.
    /// Bitfields have `bit_size` bits from bit `bit_offset` of the record,
    /// counted from the most significant bit of its first byte.
    uint32_t offset;
    uint8_t has_offset;
    uint32_t bit_offset;
    uint8_t bit_size;
    /// `DAT_EXTENT`.
    uint8_t extent;
    /// Where it is natively, in bytes; for bitfields, see `set_bits`.
    uint32_t native_offset;
    /// Its native size; 0 for bitfields.
    uint32_t native_size;
    /// A bitfield's accessors, given its native record.
    void (*set_bits)(void* record, uint64_t value);
    uint64_t (*get_bits)(const void* record);
    /// `DAT_COUNT`, `DAT_TERMINATED` and `DAT_IF`.
    const DatExpr* count;
    const DatExpr* terminator;
    const DatExpr* cond;
    /// `DAT_TYPE`.
    int32_t type_tag;
    /// `DAT_SCRIPT`.
    const DatScript* script;
    /// `DAT_BIND`s.
    const DatBind* binds;
    uint32_t nbinds;
} DatMember;

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
    /// Structs and unions.
    const DatMember* members;
    uint32_t nmembers;
    /// Typedefs: `DAT_TERMINATED`'s value.
    const DatExpr* terminator;
    /// Typedefs: `DAT_TYPE`'s type.
    int32_t type_tag;
} DatType;

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
    const DatRootBind* binds;
    uint32_t nbinds;
} DatRoot;

/// The roots of one archive of a file, as `melee-dat` types them.
typedef struct DatFileRoots {
    /// The file, relative to the game's files, e.g. `PlCo.dat`.
    const char* file;
    /// Which archive of the file, for files that pack several.
    uint32_t archive;
    /// Public symbols, then aliases.
    const DatRoot* roots;
    uint32_t nroots;
} DatFileRoots;

/// The files of a module, the first two letters of their names: `Pl`, `Gr`.
typedef struct DatModule {
    const DatFileRoots* files;
    uint32_t nfiles;
} DatModule;

typedef struct DatSchema {
    /// By index; the first, `DAT_NONE`, is `NULL`.
    const DatType* const* types;
    uint32_t ntypes;
    /// The names members and expressions refer to; the first, `DAT_NONE`,
    /// is `NULL`.
    const char* const* names;
    uint32_t nnames;
    const DatModule* modules;
    uint32_t nmodules;
} DatSchema;

/* --- Writing descriptors --------------------------------------------------
 */

#define DAT_COUNTOF(array) (sizeof(array) / sizeof *(array))

/// A struct or union's members.
#define DAT_MEMBERS(array) .members = (array), .nmembers = DAT_COUNTOF(array)

/// A member at `at` in the archive's record, and where `field` of the
/// native `record` is.
#define DAT_AT(at) .offset = (at), .has_offset = 1
#define DAT_FIELD(record, field)                                              \
    .native_offset = offsetof(record, field),                                 \
    .native_size = sizeof(((record*) 0)->field)

/// A member that is the native record's field of the same name, whose
/// name is `DAT_NAME_<field>`.
#define DAT_MEMBER(record, field, at, member_type)                            \
    .name = DAT_NAME_##field, .type = (member_type), DAT_AT(at),              \
    DAT_FIELD(record, field)

/// A member's `DAT_BIND`s.
#define DAT_BINDS(...)                                                        \
    .binds = (const DatBind[]) { __VA_ARGS__ },                               \
    .nbinds = DAT_COUNTOF(((const DatBind[]) { __VA_ARGS__ }))

/// A root's bindings, a file's roots and a module's files.
#define DAT_ROOT_BINDS(...)                                                   \
    .binds = (const DatRootBind[]) { __VA_ARGS__ },                           \
    .nbinds = DAT_COUNTOF(((const DatRootBind[]) { __VA_ARGS__ }))
#define DAT_FILE_ROOTS(array) .roots = (array), .nroots = DAT_COUNTOF(array)
#define DAT_MODULE(array) { .files = (array), .nfiles = DAT_COUNTOF(array) }

/// Expressions, as nodes with static storage.
#define DAT_EXPR(...) (&(const DatExpr) { __VA_ARGS__ })
#define DAT_INT(v) DAT_EXPR(.op = DAT_OP_INT, .value = (v))
/// A name, `DAT_NAME_<n>`.
#define DAT_NAME(n) DAT_EXPR(.op = DAT_OP_NAME, .name = DAT_NAME_##n)
/// A name that is a macro where the walk doesn't bind it, whose name is
/// `DAT_NAME_<n>` and whose body is `dat_macro_<n>`.
#define DAT_MACRO(n)                                                          \
    DAT_EXPR(.op = DAT_OP_NAME, .name = DAT_NAME_##n, .b = &dat_macro_##n)
#define DAT_UNARY(o, x) DAT_EXPR(.op = DAT_OP_##o, .a = (x))
#define DAT_BINARY(o, x, y) DAT_EXPR(.op = DAT_OP_##o, .a = (x), .b = (y))
#define DAT_CALL(f, ...)                                                      \
    DAT_EXPR(.op = DAT_OP_CALL, .function = DAT_FN_##f,                       \
             .args = (const DatExpr* const[]) { __VA_ARGS__ },                \
             .nargs =                                                         \
                 DAT_COUNTOF(((const DatExpr* const[]) { __VA_ARGS__ })))
#define DAT_FAIL DAT_EXPR(.op = DAT_OP_FAIL)

#ifdef __cplusplus
}
#endif

#endif
