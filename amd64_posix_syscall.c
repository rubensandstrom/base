#include "int.h"
#include "amd64_posix_syscall.h"

s64 read(u32 fd, u8 *buf, u64 count) { 
    register s64 rv;
    asm volatile (
        "syscall" 
        : "=a"(rv) 
        : "a"(0)
        : "rcx", "r11"
    );
    return rv;
}

s64 write(u32 fd, u8 *buf, u64 count) {
    register s64 rv;
    asm volatile (
        "syscall" 
        : "=a"(rv) 
        : "a"(1)
        : "rcx", "r11"
    );
    return rv;
}

s32 open(const u8 *path, open_flags flags, u32 permissions) {
    register s32 rv;
    asm volatile (
        "syscall" 
        : "=a"(rv) 
        : "a"(2)
        : "rcx", "r11"
    );
    return rv;
}

s32 close(s32 file_descriptor) {
    register s32 rv;
    asm volatile (
        "syscall" 
        : "=a"(rv) 
        : "a"(3)
        : "rcx", "r11"
    );
    return rv;
}

void *mmap(void *addr, u64 len, s32 prot, mmap_flags flags, s32 file_descriptor, s64 offset)  {
    register void *rv;
    register s32 r10 asm ("r10") = flags;    // 4th argument: flags (32-bit)
    register s32 r8 asm ("r8") = file_descriptor;  // 5th argument: fd (32-bit)
    register s64 r9 asm ("r9") = offset;     // 6th argument: offset (64-bit)
    asm volatile (
        "syscall\n\t" 
        : "=a"(rv) 
        : "a"(9), "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11"
    );
    return rv;
}

s32 munmap(void *addr, u64 len) {
    register s32 rv;
    asm volatile (
        "syscall" 
        : "=a"(rv) 
        : "a"(11)
        : "rcx", "r11"
    );
    return rv;
}

void *mremap(void *old_addr, u64 old_len, u64 new_len, mremap_flags flags, ...) {
    register void *rv;
    register u64 r10 asm("r10") = flags;
    asm volatile (
        "syscall" 
        : "=a"(rv) 
        : "a"(25), "r"(r10)
        : "rcx", "r11"
    );
    return rv;
}

void exit(s32 error_code) {
    asm volatile ("syscall" : : "a"(60));
end: goto end;
}
