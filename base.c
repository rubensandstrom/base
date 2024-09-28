#include "int.h"
#include "base.h"
#include "amd64_posix_syscall.h"

#define MAIN_NOARGS
#include "startup.c"

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
(da)->count += sizeof(*(da)->items);                                            

void __sb_append__(string_builder *sb, u8 *string, u64 len) {
    if (sb->count + len >= sb->capacity) {
        sb->items = mremap(sb->items, sb->capacity, sb->capacity * 2, 1);
        sb->capacity *= 2;
    }
    for (int i = 0; i < len; i++) {
        sb->items[sb->count] = string[i];
        sb->count += 1;
    }
}

#define sb_append(sb, string) __sb_append__(sb, string, sizeof(string) - 1)

typedef enum {
    INFO,
    WARN,
    ERROR,
    FATAL,
    TRACE,
    DEBUG,
} log_level;

void __sb_log__(string_builder *sb, log_level level, u8 *string, u64 len) {
    switch (level) {
        case INFO:
            sb_append(sb, "\e[34mINFO: \e[0m");
            break;
        case WARN:
            sb_append(sb, "\e[33mWARNING: \e[0m");
            break;
        case ERROR:
            sb_append(sb, "\e[31mERROR: \e[0m");
            break;
        default:
            return;
    }
    __sb_append__(sb, string, len);
}

#define sb_log(sb, level, string) __sb_log__(sb, level, string, sizeof(string) - 1)


void print(string_builder sb) {
    write(1, sb.items, sb.count);
}

s64 main(void) {

    string_builder sb = da_init(string_builder);

    sb_append(&sb, "b\n");
    sb_append(&sb, "next thing\n");
    sb_append(&sb, "and another\n");

    sb_log(&sb, ERROR, "What\n");
    sb_log(&sb, WARN, "Lol\n");

    

    print(sb);
    return 0;
}

