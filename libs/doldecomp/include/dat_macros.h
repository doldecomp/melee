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
 * A condition that can't be evaluated stops the search, so a last member
 * marked @c DAT_IF(true) is a catch-all for the others. If every member has a
 * condition and none holds, the union is unused.
 */
#ifndef DOLDECOMP_DAT_MACROS_H
#define DOLDECOMP_DAT_MACROS_H

#if defined(__clang__) && defined(DAT_ANNOTATIONS)
#define DAT_TAG(tag) __attribute__((btf_decl_tag("dat:" tag)))
#else
#define DAT_TAG(tag)
#endif

/// The array holds, or the pointer refers to, @p count elements: an expression
/// of sibling fields (or their members, @c x0.count) and constants, which may
/// call the functions the tool ports, e.g. @c GXGetTexBufferSize. On a pointer
/// typedef, for lists of counted lists, names resolve to bindings (#DAT_BIND).
/// A pointer field whose own #DAT_COUNT or #DAT_TERMINATED gives its length
/// is the bytes it points to, which calls and bindings take: the tool-side
/// @c GXMaxIndex(dl, descs, attr) is the largest index the display list
/// @c dl gives the attribute @c attr of the vertex descriptors @c descs.
#define DAT_COUNT(count) DAT_TAG("count(" #count ")")

/// The pointer refers to elements up to and including a terminator: the
/// first element whose first word is @p value and not a relocated pointer,
/// e.g. @c DAT_TERMINATED(GX_VA_NULL) for a vertex descriptor list. An
/// optional second argument, a number, is how many elements the terminator
/// takes, for lists that end in it more than once:
/// @c DAT_TERMINATED(0x83D60, 2).
#define DAT_TERMINATED(...) DAT_TAG("terminated(" #__VA_ARGS__ ")")

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

/// Bind @p name to the result of matching the tuple @p values against the
/// remaining arguments: @c (pattern, ...): value cases, ending with
/// @c _: value. Cases are comma-separated.
/// Patterns are constants, @c | alternatives, or @c _ to ignore a tuple
/// component. The first matching case supplies the binding, with the same
/// scope as #DAT_BIND.
#define DAT_MATCH(name, values, ...)                                          \
    DAT_TAG("bind(" #name ", (match " #values " { " #__VA_ARGS__ " }))")

/// The pointer refers to a command script: commands of whole words, each
/// with its opcode in the top 6 bits of its first byte, up to one with opcode
/// 0. Relocated words within a command point to more script, such as a
/// goto's target. Opcodes 0 to 9 are the generic commands every script
/// shares (#Command_Execute). The script's own commands, from opcode 10,
/// are as many words long as either
/// - @c table, an array in the code of their lengths, from opcode 10:
///   @c DAT_SCRIPT(ftAction_803C0870); or
/// - an expression in @c _command, the command's first word, such as a call
///   to a tool-side helper: @c DAT_SCRIPT(itCommandLength(_command)). A
///   length of 0 ends the script there, for scripts that stop at a command
///   of their own (a color animation's opcode 10).
///
/// Apply to a pointer member or a pointer typedef used in an array of scripts.
#define DAT_SCRIPT(...) DAT_TAG("script(" #__VA_ARGS__ ")")

/// A pointer to a byte command script. @p length gives the command's size in
/// bytes, using its first byte as @c _command. For example:
/// @c DAT_BYTE_SCRIPT(cpuCommandLength(_command)).
///
/// A length of 0 marks the terminator. The terminator byte is included in the
/// script. Byte scripts have no generic commands or pointers.
/// Apply to a pointer member or a pointer typedef used in an array of scripts.
#define DAT_BYTE_SCRIPT(length) DAT_TAG("bytescript(" #length ")")

/// On a typedef of @c u8: the bytes are data of one format the archive
/// doesn't break down further, such as an animation's keyframe stream. Raw
/// @c u8 data is unknown; the size comes from the members that point to it,
/// e.g. @c DAT_COUNT(length).
#define DAT_BLOB DAT_TAG("blob")

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

#if defined(__clang__) && defined(DAT_ANNOTATIONS) && !defined(TARGET_PC)
/** @name Aurora console GX
 * The DWARF build compiles aurora's headers in their console layout, like
 * the game's. Their console branch of GXVert.h lacks most of the vertex
 * functions its TARGET_PC branch declares; these fill them in.
 *
 * @todo Upstream to aurora's GXVert.h and remove.
 * @{
 */
#include <dolphin/gx/GXVert.h>

static inline void GXPosition2u8(const u8 x, const u8 y)
{
    GXWGFifo.u8 = x;
    GXWGFifo.u8 = y;
}

static inline void GXPosition3u16(const u16 x, const u16 y, const u16 z)
{
    GXWGFifo.u16 = x;
    GXWGFifo.u16 = y;
    GXWGFifo.u16 = z;
}

static inline void GXPosition3u8(const u8 x, const u8 y, const u8 z)
{
    GXWGFifo.u8 = x;
    GXWGFifo.u8 = y;
    GXWGFifo.u8 = z;
}

static inline void GXPosition3s8(const s8 x, const s8 y, const s8 z)
{
    GXWGFifo.s8 = x;
    GXWGFifo.s8 = y;
    GXWGFifo.s8 = z;
}

static inline void GXPosition2u16(const u16 x, const u16 y)
{
    GXWGFifo.u16 = x;
    GXWGFifo.u16 = y;
}

static inline void GXPosition2s16(const s16 x, const s16 y)
{
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
}

static inline void GXPosition2s8(const s8 x, const s8 y)
{
    GXWGFifo.s8 = x;
    GXWGFifo.s8 = y;
}

static inline void GXPosition1x16(const u16 index)
{
    GXWGFifo.u16 = index;
}

static inline void GXPosition1x8(const u8 index)
{
    GXWGFifo.u8 = index;
}

static inline void GXNormal3s16(const s16 x, const s16 y, const s16 z)
{
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXWGFifo.s16 = z;
}

static inline void GXNormal3s8(const s8 x, const s8 y, const s8 z)
{
    GXWGFifo.s8 = x;
    GXWGFifo.s8 = y;
    GXWGFifo.s8 = z;
}

static inline void GXNormal1x16(const u16 index)
{
    GXWGFifo.u16 = index;
}

static inline void GXNormal1x8(const u8 index)
{
    GXWGFifo.u8 = index;
}

static inline void GXColor3u8(const u8 r, const u8 g, const u8 b)
{
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
}

static inline void GXColor1u32(const u32 clr)
{
    GXWGFifo.u32 = clr;
}

static inline void GXColor1u16(const u16 clr)
{
    GXWGFifo.u16 = clr;
}

static inline void GXColor1x16(const u16 index)
{
    GXWGFifo.u16 = index;
}

static inline void GXColor1x8(const u8 index)
{
    GXWGFifo.u8 = index;
}

static inline void GXTexCoord2u16(const u16 s, const u16 t)
{
    GXWGFifo.u16 = s;
    GXWGFifo.u16 = t;
}

static inline void GXTexCoord2u8(const u8 s, const u8 t)
{
    GXWGFifo.u8 = s;
    GXWGFifo.u8 = t;
}

static inline void GXTexCoord2s8(const s8 s, const s8 t)
{
    GXWGFifo.s8 = s;
    GXWGFifo.s8 = t;
}

static inline void GXTexCoord1f32(const f32 s)
{
    GXWGFifo.f32 = s;
}

static inline void GXTexCoord1u16(const u16 s)
{
    GXWGFifo.u16 = s;
}

static inline void GXTexCoord1s16(const s16 s)
{
    GXWGFifo.s16 = s;
}

static inline void GXTexCoord1u8(const u8 s)
{
    GXWGFifo.u8 = s;
}

static inline void GXTexCoord1s8(const s8 s)
{
    GXWGFifo.s8 = s;
}

static inline void GXTexCoord1x16(const u16 index)
{
    GXWGFifo.u16 = index;
}
/// @}
#endif

/** @name SDK types
 * The SDK's typedefs, declared again with annotations: its headers aren't
 * the decomp's to annotate, and C23 allows the same typedef twice. Only for
 * the DWARF build, whose clang reads them.
 * @{
 */
#if defined(__clang__) && defined(DAT_ANNOTATIONS)
/// Each points to its first row, but to a whole matrix.
typedef float (*MtxPtr)[4] DAT_TYPE(Mtx);
typedef float (*Mtx44Ptr)[4] DAT_TYPE(Mtx44);
typedef float (*ROMtxPtr)[3] DAT_TYPE(ROMtx);
#endif
/// @}

#endif
