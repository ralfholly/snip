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
 * PREREQUESITES:
 *   Ensure that the portable integer types uint#_t and int#_t are properly
 *   defined, for instance by including the C99 header 'stdint.h'.
 *
 * GITHUB:
 *   https://github.com/ralfholly/snip
 */

#ifndef SAFE_NUMERIC_INTEGER_PRIMITIVES
#define SAFE_NUMERIC_INTEGER_PRIMITIVES

/**
 * Add two unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @param[out] error. 0 if the result of the operation doesn't overflow the valid integer range; != 0 otherwise.
 * @return Result of the operation, if *error == 0; unspecified if *error != 0.
 */
static uint8_t snip_add_uint8(uint8_t a, uint8_t b, uint8_t* error);
static uint16_t snip_add_uint16(uint16_t a, uint16_t b, uint8_t* error);
static uint32_t snip_add_uint32(uint32_t a, uint32_t b, uint8_t* error);
static uint64_t snip_add_uint64(uint64_t a, uint64_t b, uint8_t* error);

/**
 * Add two signed integers.
 * @param a First operand.
 * @param b Second operand.
 * @param[out] error. 0 if the result of the operation doesn't overflow the valid integer range; != 0 otherwise.
 * @return Result of the operation, if *error == 0; unspecified if *error != 0.
 */
static int8_t snip_add_int8(int8_t a, int8_t b, uint8_t* error);
static int16_t snip_add_int16(int16_t a, int16_t b, uint8_t* error);
static int32_t snip_add_int32(int32_t a, int32_t b, uint8_t* error);
static int64_t snip_add_int64(int64_t a, int64_t b, uint8_t* error);

/**
 * Subtract an unsigned integer from another unsigned integer.
 * @param a Operand, from which operand 'b' is to be subtracted.
 * @param b Operand, which is to be subtracted from operand 'a'.
 * @param[out] error. 0 if the result of the operation doesn't overflow the valid integer range; != 0 otherwise.
 * @return Result of the operation, if *error == 0; unspecified if *error != 0.
 */
static uint8_t snip_sub_uint8(uint8_t a, uint8_t b, uint8_t* error);
static uint16_t snip_sub_uint16(uint16_t a, uint16_t b, uint8_t* error);
static uint32_t snip_sub_uint32(uint32_t a, uint32_t b, uint8_t* error);
static uint64_t snip_sub_uint64(uint64_t a, uint64_t b, uint8_t* error);

/**
 * Subtract a signed integer from another signed integer.
 * @param a Operand, from which operand 'b' is to be subtracted.
 * @param b Operand, which is to be subtracted from operand 'a'.
 * @param[out] error. 0 if the result of the operation doesn't overflow the valid integer range; != 0 otherwise.
 * @return Result of the operation, if *error == 0; unspecified if *error != 0.
 */
static int8_t snip_sub_int8(int8_t a, int8_t b, uint8_t* error);
static int16_t snip_sub_int16(int16_t a, int16_t b, uint8_t* error);
static int32_t snip_sub_int32(int32_t a, int32_t b, uint8_t* error);
static int64_t snip_sub_int64(int64_t a, int64_t b, uint8_t* error);

/**
 * Divide an unsigned integer by another unsigned integer.
 * @param a Dividend.
 * @param b Divisor.
 * @param[out] error. 0 if the result of the operation doesn't overflow the valid integer range; != 0 otherwise.
 * @return Result of the operation, if *error == 0; unspecified if *error != 0.
 */
static uint8_t snip_div_uint8(uint8_t a, uint8_t b, uint8_t* error);
static uint16_t snip_div_uint16(uint16_t a, uint16_t b, uint8_t* error);
static uint32_t snip_div_uint32(uint32_t a, uint32_t b, uint8_t* error);
static uint64_t snip_div_uint64(uint64_t a, uint64_t b, uint8_t* error);

/**
 * Divide a signed integer by another signed integer.
 * @param a Dividend.
 * @param b Divisor.
 * @param[out] error. 0 if the result of the operation doesn't overflow the valid integer range; != 0 otherwise.
 * @return Result of the operation, if *error == 0; unspecified if *error != 0.
 */
static int8_t snip_div_int8(int8_t a, int8_t b, uint8_t* error);
static int16_t snip_div_int16(int16_t a, int16_t b, uint8_t* error);
static int32_t snip_div_int32(int32_t a, int32_t b, uint8_t* error);
static int64_t snip_div_int64(int64_t a, int64_t b, uint8_t* error);

#define SNIP_DEFINE_ADD_UINT(bits) \
static uint##bits##_t snip_add_uint##bits(uint##bits##_t a, uint##bits##_t b, uint8_t* error) { \
    uint##bits##_t result = (uint##bits##_t)((uint##bits##_t)a + (uint##bits##_t)b); \
    if (result < a) { \
        *error = 1U; \
    } \
    return result; \
}

#define SNIP_DEFINE_ADD_INT(bits) \
static int##bits##_t snip_add_int##bits(int##bits##_t a, int##bits##_t b, uint8_t* error) { \
    static const int##bits##_t max_val = (int##bits##_t)(((uint##bits##_t)1U << (bits##U - 1U)) - 1U); \
    static const int##bits##_t min_val = -max_val - 1; \
    int##bits##_t result = 0; \
    if (   ((b > 0) && (a > max_val - b)) \
        || ((b < 0) && (a < min_val - b))) { \
        *error = 1U; \
    } else { \
        result = (int##bits##_t)(a + b); \
    } \
    return result; \
}

#define SNIP_DEFINE_SUB_UINT(bits) \
static uint##bits##_t snip_sub_uint##bits(uint##bits##_t a, uint##bits##_t b, uint8_t* error) { \
    uint##bits##_t result = 0U; \
    if (a < b) { \
        *error = 1U; \
    } else { \
        result = (uint##bits##_t)(a - b); \
    } \
    return result; \
}

#define SNIP_DEFINE_SUB_INT(bits) \
static int##bits##_t snip_sub_int##bits(int##bits##_t a, int##bits##_t b, uint8_t* error) { \
    static const int##bits##_t max_val = (int##bits##_t)(((uint##bits##_t)1U << (bits##U - 1U)) - 1U); \
    static const int##bits##_t min_val = -max_val - 1; \
    int##bits##_t result = 0; \
    if (((uint##bits##_t)a ^ (uint##bits##_t)b) & (((uint##bits##_t)a - (uint##bits##_t)b) ^ (uint##bits##_t)a) & (uint##bits##_t)min_val) { \
        *error = 1U; \
    } else { \
        result = (int##bits##_t)(a - b); \
    } \
    return result; \
}

#define SNIP_DEFINE_DIV_UINT(bits) \
static uint##bits##_t snip_div_uint##bits(uint##bits##_t a, uint##bits##_t b, uint8_t* error) { \
    uint##bits##_t result = 0U; \
    if (b == 0U) { \
        *error = 1U; \
    } else { \
        result = (uint##bits##_t)(a / b); \
    } \
    return result; \
}

#define SNIP_DEFINE_DIV_INT(bits) \
static int##bits##_t snip_div_int##bits(int##bits##_t a, int##bits##_t b, uint8_t* error) { \
    static const int##bits##_t max_val = (int##bits##_t)(((uint##bits##_t)1U << (bits##U - 1U)) - 1U); \
    static const int##bits##_t min_val = -max_val - 1; \
    int##bits##_t result = 0; \
    if (((a == min_val) && (b == -1)) || (b == 0)) { \
        *error = 1U; \
    } else { \
        result = (int##bits##_t)(a / b); \
    } \
    return result; \
}

SNIP_DEFINE_ADD_UINT(8)
SNIP_DEFINE_ADD_INT(8)
SNIP_DEFINE_SUB_UINT(8)
SNIP_DEFINE_SUB_INT(8)
SNIP_DEFINE_DIV_UINT(8)
SNIP_DEFINE_DIV_INT(8)

SNIP_DEFINE_ADD_UINT(16)
SNIP_DEFINE_ADD_INT(16)
SNIP_DEFINE_SUB_UINT(16)
SNIP_DEFINE_SUB_INT(16)
SNIP_DEFINE_DIV_UINT(16)
SNIP_DEFINE_DIV_INT(16)

SNIP_DEFINE_ADD_UINT(32)
SNIP_DEFINE_ADD_INT(32)
SNIP_DEFINE_SUB_UINT(32)
SNIP_DEFINE_SUB_INT(32)
SNIP_DEFINE_DIV_UINT(32)
SNIP_DEFINE_DIV_INT(32)

SNIP_DEFINE_ADD_UINT(64)
SNIP_DEFINE_ADD_INT(64)
SNIP_DEFINE_SUB_UINT(64)
SNIP_DEFINE_SUB_INT(64)
SNIP_DEFINE_DIV_UINT(64)
SNIP_DEFINE_DIV_INT(64)

#endif /* SAFE_NUMERIC_INTEGER_PRIMITIVES */
