#include <global_destructor_chain.h>

typedef void (*Destructor)(void*, int);
typedef struct DestructorChain {
    struct DestructorChain* next;
    Destructor destructor;
    void* object;
} DestructorChain;
DestructorChain* __global_destructor_chain;

void __destroy_global_chain(void)
{
    while (__global_destructor_chain) {
        DestructorChain* cur = __global_destructor_chain;
        __global_destructor_chain = cur->next;
        cur->destructor(cur->object, -1);
    }
}
