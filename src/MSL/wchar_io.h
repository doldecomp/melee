#ifndef _WCHAR_IO_H_
#define _WCHAR_IO_H_

#include <Runtime/platform.h>
#include <common_structs.h>

enum __file_kinds {
    __closed_file,
    __disk_file,
    __console_file,
    __unavailable_file
};

enum __file_orientation {
    __unoriented,
    __char_oriented,
    __wide_oriented
};

#endif
