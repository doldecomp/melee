#include "buffer_io.h"

void __prep_buffer(FILE* file)
{
    file->buffer_ptr = file->buffer;
    file->buffer_len = file->buffer_size;
    file->buffer_len -= file->position & file->buffer_alignment;
    file->buffer_pos = file->position;
}

int __flush_buffer(FILE* file, size_t* bytes_flushed)
{
    size_t len;
    int res;

    len = file->buffer_ptr - file->buffer;
    if (len != 0) {
        file->buffer_len = len;
        if (file->mode.binary_io) {
            (void) (file->mode.binary_io != 0);
        }
        res = file->write_proc(file->handle, file->buffer, &file->buffer_len,
                               file->idle_proc);
        if (bytes_flushed != NULL) {
            *bytes_flushed = file->buffer_len;
        }
        if (res != 0) {
            return res;
        }
        file->position += file->buffer_len;
    }

    __prep_buffer(file);
    return 0;
}
