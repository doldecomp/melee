/** @file Test-only archive tracing and readback. */
#ifndef DAT_TEST_H
#define DAT_TEST_H
#include <stdio.h>

#include <dat/archive.h>
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

/// Write what the walk reached, sorted, in the form `melee-dat native
/// expect` does.
void dat_trace(const DatArchive* archive, FILE* out, unsigned what);

/// Check every converted object against the data it came from, reading it
/// back natively. Returns the number of mismatches, writing each to `out`
/// if given.
size_t dat_verify(const DatArchive* archive, FILE* out);

#endif
