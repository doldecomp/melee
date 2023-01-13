/// @file
/// @todo Assumes @c GEKKO.
#ifndef STDBOOL_H
#define STDBOOL_H

/// A signed integer used to contain boolean values
/// @todo Rename to @c bool.
/// @todo Maybe some versions of MetroWerks support @c _Bool?
typedef int BOOL;

/// #BOOL true
#define TRUE 1

/// #BOOL false
#define FALSE 0

#endif
