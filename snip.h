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
 *   github.com/ralfholly/snip
 */

#ifndef SAFE_NUMERIC_INTEGER_PRIMITIVES
#define SAFE_NUMERIC_INTEGER_PRIMITIVES

#ifdef SNIP_INT_TYPES_H
#include SNIP_INT_TYPES_H
#else
#include <stdint.h>
#endif

#ifndef SNIP_INLINE
#define SNIP_INLINE
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Add two unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @param[out] error. Set to 1 iff the result of the operation overflows the valid integer range.
 * @return Result of the operation, iff no overflow condition occurred.
 */
SNIP_INLINE uint8_t snip_add_uint8(uint8_t a, uint8_t b, uint8_t* error);
SNIP_INLINE uint16_t snip_add_uint16(uint16_t a, uint16_t b, uint8_t* error);
SNIP_INLINE uint32_t snip_add_uint32(uint32_t a, uint32_t b, uint8_t* error);
SNIP_INLINE uint64_t snip_add_uint64(uint64_t a, uint64_t b, uint8_t* error);

/**
 * Add two signed integers.
 * @param a First operand.
 * @param b Second operand.
 * @param[out] error. Set to 1 iff the result of the operation overflows the valid integer range.
 * @return Result of the operation, iff no overflow condition occurred.
 */
SNIP_INLINE int8_t snip_add_int8(int8_t a, int8_t b, uint8_t* error);
SNIP_INLINE int16_t snip_add_int16(int16_t a, int16_t b, uint8_t* error);
SNIP_INLINE int32_t snip_add_int32(int32_t a, int32_t b, uint8_t* error);
SNIP_INLINE int64_t snip_add_int64(int64_t a, int64_t b, uint8_t* error);

/**
 * Subtract an unsigned integer from another unsigned integer.
 * @param a Operand, from which operand 'b' is to be subtracted.
 * @param b Operand, which is to be subtracted from operand 'a'.
 * @param[out] error. Set to 1 iff the result of the operation overflows the valid integer range.
 * @return Result of the operation, iff no overflow condition occurred.
 */
SNIP_INLINE uint8_t snip_sub_uint8(uint8_t a, uint8_t b, uint8_t* error);
SNIP_INLINE uint16_t snip_sub_uint16(uint16_t a, uint16_t b, uint8_t* error);
SNIP_INLINE uint32_t snip_sub_uint32(uint32_t a, uint32_t b, uint8_t* error);
SNIP_INLINE uint64_t snip_sub_uint64(uint64_t a, uint64_t b, uint8_t* error);

/**
 * Subtract a signed integer from another signed integer.
 * @param a Operand, from which operand 'b' is to be subtracted.
 * @param b Operand, which is to be subtracted from operand 'a'.
 * @param[out] error. Set to 1 iff the result of the operation overflows the valid integer range.
 * @return Result of the operation, iff no overflow condition occurred.
 */
SNIP_INLINE int8_t snip_sub_int8(int8_t a, int8_t b, uint8_t* error);
SNIP_INLINE int16_t snip_sub_int16(int16_t a, int16_t b, uint8_t* error);
SNIP_INLINE int32_t snip_sub_int32(int32_t a, int32_t b, uint8_t* error);
SNIP_INLINE int64_t snip_sub_int64(int64_t a, int64_t b, uint8_t* error);

/**
 * Multiply two unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @param[out] error. Set to 1 iff the result of the operation overflows the valid integer range.
 * @return Result of the operation, iff no overflow condition occurred.
 */
SNIP_INLINE uint8_t snip_mul_uint8(uint8_t a, uint8_t b, uint8_t* error);
SNIP_INLINE uint16_t snip_mul_uint16(uint16_t a, uint16_t b, uint8_t* error);
SNIP_INLINE uint32_t snip_mul_uint32(uint32_t a, uint32_t b, uint8_t* error);
SNIP_INLINE uint64_t snip_mul_uint64(uint64_t a, uint64_t b, uint8_t* error);

/**
 * Multiply two signed integers.
 * @param a First operand.
 * @param b Second operand.
 * @param[out] error. Set to 1 iff the result of the operation overflows the valid integer range.
 * @return Result of the operation, iff no overflow condition occurred.
 */
SNIP_INLINE int8_t snip_mul_int8(int8_t a, int8_t b, uint8_t* error);
SNIP_INLINE int16_t snip_mul_int16(int16_t a, int16_t b, uint8_t* error);
SNIP_INLINE int32_t snip_mul_int32(int32_t a, int32_t b, uint8_t* error);
SNIP_INLINE int64_t snip_mul_int64(int64_t a, int64_t b, uint8_t* error);

/**
 * Divide an unsigned integer by another unsigned integer.
 * @param a Dividend.
 * @param b Divisor.
 * @param[out] error. Set to 1 iff the result of the operation overflows the valid integer range.
 * @return Result of the operation, iff no overflow condition occurred.
 */
SNIP_INLINE uint8_t snip_div_uint8(uint8_t a, uint8_t b, uint8_t* error);
SNIP_INLINE uint16_t snip_div_uint16(uint16_t a, uint16_t b, uint8_t* error);
SNIP_INLINE uint32_t snip_div_uint32(uint32_t a, uint32_t b, uint8_t* error);
SNIP_INLINE uint64_t snip_div_uint64(uint64_t a, uint64_t b, uint8_t* error);

/**
 * Divide a signed integer by another signed integer.
 * @param a Dividend.
 * @param b Divisor.
 * @param[out] error. Set to 1 iff the result of the operation overflows the valid integer range.
 * @return Result of the operation, iff no overflow condition occurred.
 */
SNIP_INLINE int8_t snip_div_int8(int8_t a, int8_t b, uint8_t* error);
SNIP_INLINE int16_t snip_div_int16(int16_t a, int16_t b, uint8_t* error);
SNIP_INLINE int32_t snip_div_int32(int32_t a, int32_t b, uint8_t* error);
SNIP_INLINE int64_t snip_div_int64(int64_t a, int64_t b, uint8_t* error);

/* Minimum and maximum values for integer types. */
#define SNIP_UINT_MAX(bits) ((2U * (((uint##bits##_t)1U << (bits - 1)) - 1U)) + 1U)
#define SNIP_UINT_MIN(bits) (0U)
#define SNIP_INT_MAX(bits)  ((int##bits##_t)(((uint##bits##_t)1U << (bits##U - 1U)) - 1U))
#define SNIP_INT_MIN(bits)  (-SNIP_INT_MAX(bits) - 1)

#ifdef __cplusplus
}
#endif

#endif /* SAFE_NUMERIC_INTEGER_PRIMITIVES */
