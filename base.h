#include "int.h"

#define PAGESIZE 4*1024

typedef struct {
    u8 *items;
    u64 count;
    u64 capacity;
} string_builder;

typedef struct {
    u8 *items;
    u64 count;
} string_slice;
