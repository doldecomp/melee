/** @file
 * @todo This can be removed when its macros are dealt with.
 */
#ifndef __TYPES_H__
#define __TYPES_H__

#include <Runtime/platform.h>

/// @todo This is @c HSD_ASSERT and belongs in @c baselib/debug.h.
#define assert_line(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))

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
