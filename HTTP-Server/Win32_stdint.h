#ifndef WIN32_STDINT_H
#define WIN32_STDINT_H

#include <Windows.h>

/* Exact-width integer types */
typedef INT8    int8;
typedef UINT8   uint8;

typedef INT16   int16;
typedef UINT16  uint16;

typedef INT32   int32;
typedef UINT32  uint32;

typedef INT64   int64;
typedef UINT64  uint64;

/* Minimum-width integer types */
typedef INT8    int_least8_t;
typedef UINT8   uint_least8_t;

typedef INT16   int_least16_t;
typedef UINT16  uint_least16_t;

typedef INT32   int_least32_t;
typedef UINT32  uint_least32_t;

typedef INT64   int_least64_t;
typedef UINT64  uint_least64_t;

/* Fastest minimum-width integer types */
typedef INT8    int_fast8_t;
typedef UINT8   uint_fast8_t;

typedef INT16   int_fast16_t;
typedef UINT16  uint_fast16_t;

typedef INT32   int_fast32_t;
typedef UINT32  uint_fast32_t;

typedef INT64   int_fast64_t;
typedef UINT64  uint_fast64_t;

/* Pointer-sized integer types */
typedef INT_PTR   intptr_t;
typedef UINT_PTR  uintptr_t;

/* Greatest-width integer types */
typedef INT64   intmax_t;
typedef UINT64  uintmax_t;

/* Limits for exact-width integer types */
#define INT8_MIN    (-128)
#define INT8_MAX    127
#define UINT8_MAX   0xFF

#define INT16_MIN   (-32768)
#define INT16_MAX   32767
#define UINT16_MAX  0xFFFF

#define INT32_MIN   (-2147483647 - 1)
#define INT32_MAX   2147483647
#define UINT32_MAX  0xFFFFFFFF

#define INT64_MIN   (-9223372036854775807LL - 1)
#define INT64_MAX   9223372036854775807LL
#define UINT64_MAX  0xFFFFFFFFFFFFFFFFULL

/* Limits for pointer-sized integer types */
#ifdef _WIN64
#define INTPTR_MIN  INT64_MIN
#define INTPTR_MAX  INT64_MAX
#define UINTPTR_MAX UINT64_MAX
#else
#define INTPTR_MIN  INT32_MIN
#define INTPTR_MAX  INT32_MAX
#define UINTPTR_MAX UINT32_MAX
#endif

#endif /* WIN32_STDINT_H */
