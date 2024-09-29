#include "int.h"
#include "base.h"
#include "amd64_posix_syscall.h"

#define MAIN_NOARGS
#include "startup.c"

void __stack_chk_fail(void) {
    *(s64 *){0} = 0;
}

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

void __sb_log__(string_builder *sb, log_level level, u8 *string, u64 len) {
    switch (level) {
        case INFO:
            sb_append(sb, "\e[34mINFO: \e[0m");
            break;
        case WARN:
            sb_append(sb, "\e[33mWARN: \e[0m");
            break;
        case ERROR:
            sb_append(sb, "\e[31mERROR: \e[0m");
            break;
        default:
            return;
    }
    __sb_append__(sb, string, len);
}

void print(string_builder sb) {
    write(1, sb.items, sb.count);
}

void read_file(string_builder *sb, u8 *path) {
    u32 fd = open(path, OPEN_READ_WRITE, 0);
    u64 bytes_read;

    while (1){
        bytes_read = read(fd, sb->items + sb->count, sb->capacity - sb->count);
        if (bytes_read == sb->capacity - sb->count) {
            sb->items = mremap(sb->items, sb->capacity, sb->capacity * 2, MREMAP_MAYMOVE);
            sb->capacity *= 2;
        } else break;
        sb->count += bytes_read;
    }
    sb->count += bytes_read;

    close(fd);
}
