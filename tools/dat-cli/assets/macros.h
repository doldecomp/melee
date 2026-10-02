/** @file
 * Definitions for the C that `melee-dat samples codegen` generates, written
 * next to it by `melee-dat samples macros`, like dtk's `macros.inc` for
 * its assembly. Not for the decomp's own code.
 */
#ifndef DAT_SAMPLES_MACROS_H
#define DAT_SAMPLES_MACROS_H

/// Archive data that the archive doesn't name: local to its unit, like the
/// target object's symbol, and kept where nothing in the unit points to it.
#define LOCAL static __attribute__((used))

#endif
