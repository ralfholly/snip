/* SNIP -- Safe Numeric Integer Primitives.
 *
 * Copyright 2019 Ralf Holly.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The following safe integer primitives are defined in this header:
 *
 * uint#_t snip_add_uint#(uint#_t a, uint#_t b, int* error);
 * int#_t snip_add_int#(int#_t a, int#_t b, int* error);
 * uint#_t snip_sub_uint#(uint#_t a, uint#_t b, int* error);
 * int#_t snip_sub_int#(int#_t a, int#_t b, int* error);
 *
 * where # is the number of bits (8, 16, 32, 64).
 *
 * PREREQUESITES:
 *
 * Ensure that the portable integer types uint#_t and int#_t are properly
 * defined, for instance by including the C99 header 'stdint.h'.
 *
 */

#ifndef SAFE_NUMERIC_INTEGER_PRIMITIVES
#define SAFE_NUMERIC_INTEGER_PRIMITIVES


#define SNIP_DEFINE_ADD_UINT(bits) \
static uint##bits##_t snip_add_uint##bits(uint##bits##_t a, uint##bits##_t b, int* error) { \
    uint##bits##_t result = (uint##bits##_t)((uint##bits##_t)a + (uint##bits##_t)b); \
    if (result < a) { \
        *error |= 1; \
    } \
    return result; \
}

#define SNIP_DEFINE_ADD_INT(bits) \
static int##bits##_t snip_add_int##bits(int##bits##_t a, int##bits##_t b, int* error) { \
    static const int##bits##_t max_val = (int##bits##_t)(((uint##bits##_t)1U << (bits##U - 1U)) - 1U); \
    static const int##bits##_t min_val = -max_val - 1; \
    int##bits##_t result = 0; \
    if (   ((b > 0) && (a > max_val - b)) \
        || ((b < 0) && (a < min_val - b))) { \
        *error |= 1; \
    } else { \
        result = (int##bits##_t)(a + b); \
    } \
    return result; \
}

#define SNIP_DEFINE_SUB_UINT(bits) \
static uint##bits##_t snip_sub_uint##bits(uint##bits##_t a, uint##bits##_t b, int* error) { \
    uint##bits##_t result = 0U; \
    if (a < b) { \
        *error |= 1; \
    } else { \
        result = (uint##bits##_t)(a - b); \
    } \
    return result; \
}

#define SNIP_DEFINE_SUB_INT(bits) \
static int##bits##_t snip_sub_int##bits(int##bits##_t a, int##bits##_t b, int* error) { \
    static const int##bits##_t max_val = (int##bits##_t)(((uint##bits##_t)1U << (bits##U - 1U)) - 1U); \
    static const int##bits##_t min_val = -max_val - 1; \
    int##bits##_t result = 0; \
    if (((uint##bits##_t)a ^ (uint##bits##_t)b) & (((uint##bits##_t)a - (uint##bits##_t)b) ^ (uint##bits##_t)a) & (uint##bits##_t)min_val) { \
        *error |= 1; \
    } else { \
        result = (int##bits##_t)(a - b); \
    } \
    return result; \
}

SNIP_DEFINE_ADD_UINT(8)
SNIP_DEFINE_ADD_INT(8)
SNIP_DEFINE_SUB_UINT(8)
SNIP_DEFINE_SUB_INT(8)

SNIP_DEFINE_ADD_UINT(16)
SNIP_DEFINE_ADD_INT(16)
SNIP_DEFINE_SUB_UINT(16)
SNIP_DEFINE_SUB_INT(16)

SNIP_DEFINE_ADD_UINT(32)
SNIP_DEFINE_ADD_INT(32)
SNIP_DEFINE_SUB_UINT(32)
SNIP_DEFINE_SUB_INT(32)

SNIP_DEFINE_ADD_UINT(64)
SNIP_DEFINE_ADD_INT(64)
SNIP_DEFINE_SUB_UINT(64)
SNIP_DEFINE_SUB_INT(64)

#endif /* SAFE_NUMERIC_INTEGER_PRIMITIVES */
