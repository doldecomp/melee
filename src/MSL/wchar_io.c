#include "stdio.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type"
int fwide(FILE* stream, int mode)
{
    int orientation;

    if (stream->mode.file_kind == __closed_file) {
        return 0;
    }

    orientation = stream->mode.file_orientation;
    switch (orientation) {
    case __unoriented:
        if (mode > 0) {
            stream->mode.file_orientation = __wide_oriented;
        } else if (mode < 0) {
            stream->mode.file_orientation = __char_oriented;
        }

        return mode;

    case __wide_oriented:
        return 1;

    case __char_oriented:
        return -1;
    }
}
#pragma clang diagnostic pop
