#include "int.h"
#include "base.h"
#include "amd64_posix_syscall.h"

void __stack_chk_fail(void) {
    *(s64 *){0} = 0;
}

#define da_init(type)                                       \
(type){                                                     \
        .items = mmap(0, PAGESIZE, 1|2, 0x02|0x20, -1, 0),  \
        .count = 0,                                         \
        .capacity = PAGESIZE,                               \
}

#define da_append(da, item)                                                     \
if ((da)->count + sizeof(*(da)->items) >= (da)->capacity) {                     \
    (da)->items = mremap((da)->items, (da)->capacity, (da)->capacity * 2, 1);   \
    (da)->capacity *= 2;                                                        \
}                                                                               \
(da)->items[(da)->count] = item;                                                \
(da)->count += sizeof(*(da)->items);                                            \

void print(string_builder sb) {
    write(1, sb.items, sb.count);
}

int main(void) {

    string_builder sb = da_init(string_builder);

    da_append(&sb, 'a');
    da_append(&sb, 'a');
    da_append(&sb, 'a');
    da_append(&sb, 'a');
    da_append(&sb, '\n');
    

    print(sb);
    return 0;
}

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
