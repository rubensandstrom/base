#include "int.h"
#include "amd64_posix_syscall.h"

#ifdef MAIN_NOARGS
s64 main(void);
void _start(void) {

    void *stack_ptr;
    asm volatile (
        "movq %%rsp, %0\n\t" 
        : "=r"(stack_ptr)
    );

    if ((u64)stack_ptr % 16 != 0) {
        asm("sub $8, %%rsp" : : : "memory");
    }

    s64 exitcode = main();
    exit(exitcode);
}
#endif // MAIN_NOARGS


