#ifndef SYSCALL_H
#define SYSCALL_H

#include "int.h"

s64 read(u32 fd, u8 *buf, u64 count);
s64 write(u32 fd, u8 *buffer, u64 count);
s32 open(const u8 *path, s32 flags, u64 mode);
s32 close(s32 fd);
void *mmap(void *addr, u64 len, s32 prot, s32 flags, s32 fd, s64 offset);
void *mremap(void *old_addr, u64 old_len, u64 new_len, u64 flags, ...);
s32 munmap(void *addr, u64 len);
void exit(s32 error_code)__attribute__ ((noreturn));

#endif /* SYSCALL_H */
