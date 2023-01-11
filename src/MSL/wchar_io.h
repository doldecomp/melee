#ifndef _WCHAR_IO_H_
#define _WCHAR_IO_H_

#include <Runtime/platform.h>

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

typedef struct {
    unsigned int open_mode : 2;
    unsigned int io_mode : 3;
    unsigned int buffer_mode : 2;
    unsigned int file_kind : 3;
    unsigned int file_orientation : 2;
    unsigned int binary_io : 1;
} __file_modes;

typedef struct _FILE FILE;

typedef unsigned short wchar_t;

struct _FILE {
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
    struct _FILE* next_file_struct;
};

#endif
