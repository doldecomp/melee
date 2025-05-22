#include "buffer_io.h"
#include "stdio.h"
#include "string.h"
#include "wchar.h"

extern void __stdio_atexit(void);

size_t fwrite(const void* buffer, size_t memb_size, size_t num_memb,
              FILE* file)
{
    unsigned char* cur_ptr;
    size_t num_bytes, rem_bytes, bytes_written;
    int res, buff;

    if (fwide(file, 0) == 0) {
        fwide(file, -1);
    }

    rem_bytes = memb_size * num_memb;

    if (rem_bytes == 0 || file->state.error ||
        file->mode.file_kind == __closed_file)
    {
        return 0;
    }

    if ((int) file->mode.file_kind == __console_file) {
        __stdio_atexit();
    }

    buff = (!file->mode.binary_io ||
            (int) file->mode.file_kind == __unavailable_file ||
            file->mode.buffer_mode == 2 || file->mode.buffer_mode == 1);

    if (file->state.io_state == __neutral && file->mode.io_mode & 2) {
        file->state.io_state = __writing;
        __prep_buffer(file);
    }

    if (file->state.io_state != __writing) {
        file->state.error = 1;
        file->buffer_len = 0;
        return 0;
    }

    cur_ptr = (u8*) buffer;
    bytes_written = 0;

    if (rem_bytes && (file->buffer_ptr != file->buffer || buff)) {
        file->buffer_len =
            file->buffer_size - (file->buffer_ptr - file->buffer);

        do {
            u8* nw = 0;
            num_bytes = file->buffer_len;

            if (num_bytes > rem_bytes) {
                num_bytes = rem_bytes;
            }

            if (num_bytes != 0) {
                memcpy(file->buffer_ptr, cur_ptr, num_bytes);
                cur_ptr += num_bytes;
                bytes_written += num_bytes;
                rem_bytes -= num_bytes;
                file->buffer_ptr += num_bytes;
                file->buffer_len -= num_bytes;
            }

            if (file->buffer_len == 0 &&
                (int) file->mode.file_kind == __unavailable_file)
            {
                bytes_written += rem_bytes;
                break;
            }
            if (file->buffer_len == 0 || (int) file->mode.buffer_mode == 0) {
                res = __flush_buffer(file, 0);

                if (res != 0) {
                    file->state.error = 1;
                    file->buffer_len = 0;
                    rem_bytes = 0;
                    break;
                }
            }

        } while (rem_bytes && buff);
    }

    if (rem_bytes && buff == 0) {
        u8* save_buf = (u8*) file->buffer;
        size_t save_size = file->buffer_size;

        file->buffer = cur_ptr;
        file->buffer_size = rem_bytes;
        file->buffer_ptr = cur_ptr + rem_bytes;

        if (__flush_buffer(file, &num_bytes) != 0) {
            file->state.error = 1;
            file->buffer_len = 0;
        }

        bytes_written += num_bytes;

        file->buffer = save_buf;
        file->buffer_size = save_size;
        __prep_buffer(file);
        file->buffer_len = 0;
    }

    if (file->mode.buffer_mode != 2) {
        file->buffer_len = 0;
    }

    return (bytes_written + memb_size - 1) / memb_size;
}
