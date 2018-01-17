#ifndef _TO_UNSIGNED_H
#define _TO_UNSIGNED_H 1

/* This C and C++ .h file defines the macro or function TO_UNSIGNED(x), which
 * converts an integer x to the equivalent unsigned type of the same size.
 * Thus TO_UNSIGNED((char)-3) == 253, and TO_UNSIGNED(((short)-3) == 65533
 * (typically).
 *
 * This is free software, Apache License 2.0. There is NO WARRANTY. Use at your
 * own risk.
 *
 * TO_UNSIGNED works for integer byte sizes 1, 2, 4, 8 in
 * gcc >= 4.4, g++ >= 4.4, clang >= 3.0, clang++ >= 3.0.
 *
 * TO_UNSIGNED works for integer byte size 16 in
 * gcc >= 4.6, g++ >= 4.6, clang >= 3.3, clang++ >= 3.3.
 *
 * It looks like there is no general solution which works for all sizes.
 * See https://stackoverflow.com/q/20870129/97248 for discussion.
 *
 * TO_UNSIGNED doesn't work with TCC (https://bellard.org/tcc/), TCC doesn't
 * have __builtin_choose_expr or _Generic.
 *
 * TO_UNSIGNED doesn't work with the Visual Studio C or C++ compiler. Maybe
 # it's possible to port it to the Visual Studio C++ compiler.
 *
 * TO_UNSIGNED works with any of (none), -ansi, -std=c99, -std=c++98,
 * -std=c++0x, -pedantic.
 *
 * __builtin_types_compatible_p is better than checking the sizeof, because
 * with sizeof an int could be converted to a long etc.
 *
 * C11 supports _Generic instead of __builtin_choose_expr, but gcc-4.8 doesn't
 * support generic even with gcc -std=c11.
 */

#ifdef __cplusplus
static __inline__ unsigned char TO_UNSIGNED(char v) { return v; }
static __inline__ unsigned char TO_UNSIGNED(unsigned char v) { return v; }
static __inline__ unsigned short TO_UNSIGNED(short v) { return v; }
static __inline__ unsigned short TO_UNSIGNED(unsigned short v) { return v; }
static __inline__ unsigned TO_UNSIGNED(int v) { return v; }
static __inline__ unsigned TO_UNSIGNED(unsigned v) { return v; }
static __inline__ unsigned long TO_UNSIGNED(long v) { return v; }
static __inline__ unsigned long TO_UNSIGNED(unsigned long v) { return v; }
#if defined __STRICT_ANSI__ && __cplusplus < 201103L  /* g++ -ansi, fails for long long and __int128 even with __extension__ */
#if __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_LONG__ < 8
typedef int __tou_int64_t __attribute__((mode(DI)));
typedef unsigned __tou_uint64_t __attribute__((mode(DI)));
static __inline__ __tou_uint64_t TO_UNSIGNED(__tou_int64_t v) { return v; }
static __inline__ __tou_uint64_t TO_UNSIGNED(__tou_uint64_t v) { return v; }
#endif
#if __SIZEOF_INT128__ > __SIZEOF_LONG_LONG__
typedef int __tou_int128_t __attribute__((mode(TI)));
typedef unsigned __tou_uint128_t __attribute__((mode(TI)));
static __inline__ __tou_uint128_t TO_UNSIGNED(__tou_int128_t v) { return v; }
static __inline__ __tou_uint128_t TO_UNSIGNED(__tou_uint128_t v) { return v; }
#endif
#else
static __inline__ unsigned long long TO_UNSIGNED(long long v) { return v; }
static __inline__ unsigned long long TO_UNSIGNED(unsigned long long v) { return v; }
#if __SIZEOF_INT128__ > __SIZEOF_LONG_LONG__
static __inline__ unsigned __int128 TO_UNSIGNED(__int128 v) { return v; }
static __inline__ unsigned __int128 TO_UNSIGNED(unsigned __int128 v) { return v; }
#endif
#endif
#else
#ifdef __SIZEOF_INT128__
#define TO_UNSIGNED(x) ( \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned char), (unsigned char)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), char), (unsigned char)(x), \
    __builtin_choose_expr(sizeof(x) == sizeof(char), (unsigned char)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned short), (unsigned short)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), short), (unsigned short)(x), \
    __builtin_choose_expr(sizeof(x) == sizeof(short), (unsigned short)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned), (unsigned)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), int), (unsigned)(x), \
    __builtin_choose_expr(sizeof(x) == sizeof(int), (unsigned)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned long), (unsigned long)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), long), (unsigned long)(x), \
    __builtin_choose_expr(sizeof(x) == sizeof(long), (unsigned long)(x), \
    __extension__ __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned long long), (unsigned long long)(x), \
    __extension__ __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), long long), (unsigned long long)(x), \
    __extension__ __builtin_choose_expr(sizeof(x) == sizeof(long long), (unsigned long)(x), \
    __extension__ __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned __int128), (unsigned __int128)(x), \
    __extension__ __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), __int128), (unsigned __int128)(x), \
    __extension__ __builtin_choose_expr(sizeof(x) == sizeof(__int128), (unsigned __int128)(x), \
    (void)0)))))))))))))))))))
#else
#define TO_UNSIGNED(x) ( \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned char), (unsigned char)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), char), (unsigned char)(x), \
    __builtin_choose_expr(sizeof(x) == sizeof(char), (unsigned char)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned short), (unsigned short)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), short), (unsigned short)(x), \
    __builtin_choose_expr(sizeof(x) == sizeof(short), (unsigned short)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned), (unsigned)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), int), (unsigned)(x), \
    __builtin_choose_expr(sizeof(x) == sizeof(int), (unsigned)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned long), (unsigned long)(x), \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), long), (unsigned long)(x), \
    __builtin_choose_expr(sizeof(x) == sizeof(long), (unsigned long)(x), \
    __extension__ __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), unsigned long long), (unsigned long long)(x), \
    __extension__ __builtin_choose_expr(__builtin_types_compatible_p(__typeof(x), long long), (unsigned long long)(x), \
    __extension__ __builtin_choose_expr(sizeof(x) == sizeof(long long), (unsigned long)(x), \
    (void)0))))))))))))))))
#endif
#endif

#endif  /* _TO_UNSIGNED_H */
