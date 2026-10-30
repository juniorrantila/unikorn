#pragma once
#include "./compat.h"

typedef __INT8_TYPE__   i8;
typedef __INT16_TYPE__ i16;
typedef __INT32_TYPE__ i32;
typedef __INT64_TYPE__ i64;

typedef __UINT8_TYPE__   u8;
typedef __UINT16_TYPE__ u16;
typedef __UINT32_TYPE__ u32;
typedef __UINT64_TYPE__ u64;

typedef __UINTPTR_TYPE__ uptr;
typedef __INTPTR_TYPE__  iptr;

typedef char const* c_string;

typedef enum Flat32   : u32 Flat32;
typedef enum Flat64   : u64 Flat64;
#if __SIZEOF_POINTER__ == 4
typedef Flat32 Flat_Ptr;
#elif __SIZEOF_POINTER__ == 8
typedef Flat64 Flat_Ptr;
#else
#error "unknown pointer size"
#endif
void* flat32_cast(Flat32);
void* flat64_cast(Flat64);
#define flat_cast(ptr) _Generic((ptr), Flat32: flat32_cast, Flat64: flat64_cast)(ptr)

typedef __builtin_va_list va_list;
#define va_start __builtin_va_start
#define va_end   __builtin_va_end
#define va_copy  __builtin_va_copy
#define va_arg   __builtin_va_arg

constexpr u64 Ki = 1024;
constexpr u64 Mi = 1024 * Ki;
constexpr u64 Gi = 1024 * Mi;
constexpr u64 Ti = 1024 * Gi;
constexpr u64 Pi = 1024 * Ti;
constexpr u64 Ei = 1024 * Pi;

constexpr u64 K = 1000;
constexpr u64 M = 1000 * K;
constexpr u64 G = 1000 * M;
constexpr u64 T = 1000 * G;
constexpr u64 P = 1000 * T;
constexpr u64 E = 1000 * P;

#define ARRAY_SSIZE(a) ((iptr)(sizeof(a) / sizeof((a)[0])))
#define ALIGN_UP __builtin_align_up
