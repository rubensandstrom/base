#ifndef INT_H
#define INT_H

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef float               f32;
typedef double              f64;

typedef union {
    f32 f;
    struct {
        u32 mantissa: 24;
        u32 exponent: 8;
        u32 sign:     1;
    };
} f32_bits;

typedef union {
    f64 f;
    struct {
        u64 mantissa: 52;
        u64 exponent: 11;
        u64 sign:     1;
    };
} f64_bits;
#endif // INT_H
