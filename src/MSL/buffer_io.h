#ifndef _BUFFER_IO
#define _BUFFER_IO

#include "stdio.h"

enum {
    __align_buffer,
    __dont_align_buffer
};

void __convert_from_newlines(unsigned char* p, size_t* n);
void __convert_to_newlines(unsigned char* p, size_t* n);
void __prep_buffer(FILE*);
int __load_buffer(FILE*, size_t* bytes_loaded, int alignment);
int __flush_buffer(FILE*, size_t* bytes_flushed);

#endif // _BUFFER_IO
