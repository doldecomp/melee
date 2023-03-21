#ifndef _STDIO_H_
#define _STDIO_H_

#include <platform.h>
#include <stdarg.h>

typedef struct {
    uint open_mode : 2;
    uint io_mode : 3;
    uint buffer_mode : 2;
    uint file_kind : 3;
    uint file_orientation : 2;
    uint binary_io : 1;
} __file_modes;

typedef struct FILE FILE;

struct FILE {
    int handle;
    __file_modes mode;
    int state;
    unsigned char is_dynamically_allocated;
    unsigned char char_buffer;
    unsigned char char_buffer_overflow;
    unsigned char ungetc_buffer[2];
    wchar_t ungetwc_buffer[2];
    unsigned long position;
    unsigned char* buffer;
    unsigned long buffer_size;
    unsigned char* buffer_ptr;
    unsigned long buffer_len;
    unsigned long buffer_alignment;
    unsigned long saved_buffer_len;
    unsigned long buffer_pos;
    int position_proc;
    int read_proc;
    int write_proc;
    int close_proc;
    int idle_proc;
    FILE* next_file_struct;
};

int puts(const char* s);
int printf(const char*, ...);
int sprintf(char* s, const char* format, ...);
int vprintf(const char* format, va_list arg);
int vsprintf(char* s, const char* format, va_list arg);

#endif
