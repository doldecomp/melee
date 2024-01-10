#include <stdio.h>
#include <MSL/wchar_io.h>

int fwide(FILE* stream, int mode)
{
    int orientation;
    int result;

    if (stream->file_mode.file_kind == __closed_file) {
        return 0;
    }
    orientation = stream->file_mode.file_orientation;
    switch (orientation) {
    case UNORIENTED:
        if (mode > 0) {
            stream->file_mode.file_orientation = WIDE_ORIENTED;
        } else if (mode < 0) {
            stream->file_mode.file_orientation = CHAR_ORIENTED;
        }
        result = mode;
        break;

    case WIDE_ORIENTED:
        result = 1;
        break;

    case CHAR_ORIENTED:
        result = -1;
        break;
    }
    return result;
}
