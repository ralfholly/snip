SNIP — Safe Numeric/Integer Primitives
======================================

Summary
-------

SNIP is a small, easy-to-use library for doing overflow-safe integer arithmethic. Currently, `add`, `sub`, `mul`, and `div` are supported. The main design goals have been simplicity and portability. SNIP was developed, because other safe integer libraries are either proprietary, cumbersome to use, part of bulky libraries (i. e. 'boost/safe_numerics'), or only support C++.

Example
-------

    int8_t x = ...;
    int8_t y = ...;
    uint8_t error = 0;

    int8_t sum = snip_add_int8(x, y, &error);
    if (error != 0) {
        fprintf(stderr, "Sum of %d and %d doesn't fit into an int8_t!", x, y);
    } else {
        fprintf(stdout, "Sum of %d and %d is %d.", x, y, sum);
    }


Prerequesites
-------------

SNIP uses portable integer types known from C11 ala `int8_t`, `uint8_t` (up to `int64_t`, `uint64_t`). Therefore, `snip.h` includes `stdint.h`, but if this header is not available on your system, you can define these portable integer types in your own header file and set the type include file name via the `SNIP_INT_TYPES_H` preprocessor variable. This is the code in `snip.h` that does the magic:

    #ifdef SNIP_INT_TYPES_H
    #include SNIP_INT_TYPES_H
    #else
    #include <stdint.h>
    #endif


Usage
-----

Just include `snip.h` in your module. `snip.c` contains the definitions of the SNIP API functions, so please add this file to your project and link it to your binary.


Error Saturation
----------------

If a SNIP operation doesn't overflow, the passed-in `error` value is not changed (ie. reset to 0). This allows to stack multiple SNIP operations and check for errors once, at the end:

    /* Start with a clean error value. */
    error = 0;
    sum1 = snip_add_int32(a, b, &error);
    sum2 = snip_add_int32(sum1, NUM_ROWS, &error);
    total = snip_mul_int32(sum2, NUM_COLS, &error);
    if (error) {
        /* Any of the previous operations overflowed. */
    }


Portability
-----------

SNIP supports C versions >= C89 and C++ versions >= C++98.


MISRA Compliance
----------------

The SNIP source code is compliant with the MISRA C 2012 guidelines.


Inlining
--------

If necessary (prove it first by profiling!), SNIP operations can be inlined. In this case, you don't compile/link `snip.c`, but rather include it in your module instead of `snip.h`:

    #define SNIP_INLINE inline
    #include "snip.c"

If your toolchain doesn't support inlining (not even via a proprietary keyword like `__inline`), you can still increase the likelihood of inlining by making the SNIP functions `static`:

    #define SNIP_INLINE static
    #include "snip.c"
