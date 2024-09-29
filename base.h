#ifndef BASE_H
#define BASE_H

#include "amd64_posix_syscall.h"
#include "int.h"

#define PAGESIZE (4*1024)

typedef struct {
    u8 *items;
    u64 count;
    u64 capacity;
} string_builder;

typedef struct {
    u8 *items;
    u64 count;
} string_slice;

typedef enum {
    INFO,
    WARN,
    ERROR,
    FATAL,
    TRACE,
    DEBUG,
} log_level;

static void __sb_append__(string_builder *sb, u8 *string, u64 len);
#define sb_append(sb, string) __sb_append__(sb, string, sizeof(string) - 1)

static void __sb_log__(string_builder *sb, log_level level, u8 *string, u64 len);
#define sb_log(sb, level, string) __sb_log__(sb, level, string, sizeof(string) - 1)

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
(da)->count += sizeof(*(da)->items);                                            


void read_file(string_builder *sb, u8 *path);
#endif
