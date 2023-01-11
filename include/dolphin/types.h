/** @file
 * @todo This can be removed when its macros are dealt with.
 */
#ifndef __TYPES_H__
#define __TYPES_H__

#include <Runtime/platform.h>

/// @todo This is @c HSD_ASSERT and belongs in @c baselib/debug.h.
/// @todo Take @c file as another arg, ignore it if @c !MUST_MATCH.
/// @todo Add another variant that takes a string for @c cond.
#ifdef MUST_MATCH
#define assert_line(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))
#else
#define assert_line(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#endif

/// @todo Remove.
#define STRUCT_PLACEHOLDER(module, number)                                     \
    extern struct _##module##_Unk##number;                                     \
    typedef struct _##module##_Unk##number module##_Unk##number;

/// @todo Remove.
#define CALLBACK_PLACEHOLDER(module, number)                                   \
    typedef void (*module##_UnkCallback##number)(void);

/// @todo Remove.
#define UNK_FUNC(name) unk_t name()

#endif
