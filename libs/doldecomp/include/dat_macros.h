/** @file
 * Annotations describing how archive data is laid out, for the parts a C
 * declaration cannot express: how many elements a pointer refers to, and
 * which member of a union is valid.
 *
 * They expand to nothing for every compiler except clang with
 * @c DAT_ANNOTATIONS defined, where they become @c btf_decl_tag attributes
 * that clang emits into DWARF as @c DW_TAG_LLVM_annotation. The arguments are
 * kept as written, so constants are resolved by name through the DWARF macro
 * table.
 *
 * Union members are tested in declaration order; the first match is valid.
 * If every member has a condition and none holds, the union is unused.
 */
#ifndef DOLDECOMP_DAT_MACROS_H
#define DOLDECOMP_DAT_MACROS_H

#if defined(__clang__) && defined(DAT_ANNOTATIONS)
#define DAT_TAG(tag) __attribute__((btf_decl_tag("dat:" tag)))
#else
#define DAT_TAG(tag)
#endif

/// The pointer refers to @p count elements: a sibling field or a constant.
#define DAT_COUNT(count) DAT_TAG("count(" #count ")")

/// The pointer refers to elements up to and including a zeroed one.
#define DAT_NULLTERM DAT_TAG("nullterm")

/// The array holds as many elements as the data does: they continue until
/// the next symbol, the next address a pointer refers to, or an element that
/// no longer fits the element type.
/// Its declared size is ignored.
///
/// @todo This is a heuristic for arrays whose length only the code knows.
///       Replace each use with a #DAT_COUNT once counts can be read from the
///       code's own tables (e.g. the largest @c anim_id in an item kind's
///       @c ItemStateTable, for @c ItemStateArray), or from per-kind
///       @c *_Count enum values where those exist.
#define DAT_EXTENT DAT_TAG("extent")

/// The union member is valid when @p cond holds: a C expression over the
/// fields of the record containing the union, and macros.
#define DAT_IF(cond) DAT_TAG("if(" #cond ")")

/// @p name, conventionally @c Type::field for a value that belongs to @c Type
/// but is not stored in it, is @p value for everything reached through the
/// member: its own
/// layout and every pointer followed from within it. @p value is evaluated
/// in the record containing the member; for an array or a #DAT_COUNT
/// pointer, once per element, which it can refer to as @c _index. Inner
/// bindings shadow outer ones.
#define DAT_BIND(name, value) DAT_TAG("bind(" #name ", " #value ")")

/// The untyped pointer, or pointer-sized integer, refers to a @p type when it
/// is relocated.
#define DAT_TYPE(type) DAT_TAG("type(" #type ")")

/** @name Roots
 * Archive symbols the game looks up by name are the roots every other part of
 * an archive is reached from. Loaders taking @c (&dst, "name") pairs wrap
 * their calls in #DAT_ROOTS, which declares one static witness per pair:
 * its type is the type of @c &dst, and its @c dat:root annotation holds the
 * name argument as written, a string literal or an expression.
 * @{
 */
#if defined(__clang__) && defined(DAT_ANNOTATIONS)
#define DAT_ROOTS_ENABLED 1

/// Declares a witness for each @c (dst, name) pair of a null-terminated
/// argument list, as a statement.
#define DAT_ROOTS(...) __VA_OPT__(DAT_EXPAND(DAT_ROOTS_NEXT(__VA_ARGS__)))

#define DAT_ROOT(dst, name)                                                   \
    static __typeof__(dst) DAT_CAT(__dat_root_, __COUNTER__)                  \
        __attribute__((used)) DAT_TAG("root(" #name ")");

// A lone trailing argument is the terminator
#define DAT_ROOTS_NEXT(a, ...) __VA_OPT__(DAT_ROOTS_PAIR(a, __VA_ARGS__))
#define DAT_ROOTS_PAIR(dst, name, ...)                                        \
    DAT_ROOT(dst, name)                                                       \
    __VA_OPT__(DAT_ROOTS_AGAIN DAT_PARENS(__VA_ARGS__))
#define DAT_ROOTS_AGAIN() DAT_ROOTS_NEXT
#define DAT_PARENS ()

// Rescans enough times for 256 pairs
#define DAT_EXPAND(...) DAT_EXPAND4(DAT_EXPAND4(DAT_EXPAND4(__VA_ARGS__)))
#define DAT_EXPAND4(...) DAT_EXPAND3(DAT_EXPAND3(DAT_EXPAND3(__VA_ARGS__)))
#define DAT_EXPAND3(...) DAT_EXPAND2(DAT_EXPAND2(DAT_EXPAND2(__VA_ARGS__)))
#define DAT_EXPAND2(...) DAT_EXPAND1(DAT_EXPAND1(DAT_EXPAND1(__VA_ARGS__)))
#define DAT_EXPAND1(...) __VA_ARGS__

#define DAT_CAT(a, b) DAT_CAT_(a, b)
#define DAT_CAT_(a, b) a##b
#else
#define DAT_ROOTS(...)
#endif
/// @}

#endif
