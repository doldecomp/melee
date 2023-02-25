/// @file
/// @todo Assumes @c __PPCGEKKO__.
#ifndef STDBOOL_H
#define STDBOOL_H

/// A signed integer used to contain boolean values
/// @todo Maybe some versions of MetroWerks support @c _Bool?
typedef int bool;

/// #bool true
#define true 1

/// #bool false
#define false 0

#endif
