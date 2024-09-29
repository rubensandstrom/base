#ifndef SYSCALL_H
#define SYSCALL_H

#include "int.h"

s64 read(u32 fd, u8 *buf, u64 count);
s64 write(u32 fd, u8 *buffer, u64 count);

typedef enum {
    OPEN_READ_ONLY  = 00,
    OPEN_WRITE_ONLY = 01,
    OPEN_READ_WRITE = 02,
    // TODO: the rest of the flags.
} open_flags;
s32 open(const u8 *path, open_flags flags, u32 permissions);

s32 close(s32 fd);

typedef enum {
    MMAP_FILE            = 0x0,
    MMAP_SHARED          = 0x1,
    MMAP_PRIVATE         = 0x2,
    // TODO: the rest of the flags.
    MMAP_FIXED           = 0x10,
    MMAP_ANONYMOUS       = 0x20,
    // TODO: the rest of the flags.
} mmap_flags;
void *mmap(void *addr, u64 len, s32 prot, mmap_flags flags, s32 fd, s64 offset);

typedef enum {
    MREMAP_MAYMOVE      = 1,
    MREMAP_FIXED        = 2,
    MREMAP_DONTUNMAP    = 4,
} mremap_flags;
void *mremap(void *old_addr, u64 old_len, u64 new_len, mremap_flags flags, ...);

s32 munmap(void *addr, u64 len);
void exit(s32 error_code)__attribute__ ((noreturn));

// TODO: the rest of syscalls, but really these will go a long way.
#endif /* SYSCALL_H */
