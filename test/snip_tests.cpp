#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;

#include "gmock/gmock.h"
using namespace testing;

// TODO: Remove, once all families have been tested.
#pragma GCC diagnostic ignored "-Wunused-function"

#include "snip.h"

namespace testing {
namespace snip {

#pragma GCC diagnostic warning "-Wsign-conversion"

#define ASIZE(a) ( sizeof(a) / sizeof(a[0]) )

TEST(snip, simple_8_bits) {
    uint8_t error;
    uint8_t u8_result;
    int8_t i8_result;

    // Add unsigned.
    error = 0;
    u8_result = snip_add_uint8(42, 2, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(44, u8_result);

    error = 0;
    u8_result = snip_add_uint8(42, 255, &error);
    EXPECT_EQ(1, error);

    // Add signed.
    error = 0;
    i8_result = snip_add_int8(-2, 2, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(0, i8_result);

    error = 0;
    i8_result = snip_add_int8(-128, 1, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(-127, i8_result);

    // Sub unsigned.
    error = 0;
    u8_result = snip_sub_uint8(3, 2, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(1, u8_result);

    error = 0;
    u8_result = snip_sub_uint8(3, 255, &error);
    EXPECT_EQ(1, error);

    // Sub signed.
    error = 0;
    i8_result = snip_sub_int8(3, 10, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(-7, i8_result);

    error = 0;
    i8_result = snip_sub_int8(-3, 10, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(-13, i8_result);

    error = 0;
    i8_result = snip_sub_int8(-3, 10, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(-13, i8_result);
}

TEST(snip, add_uint8_no_overflow) {
    uint8_t error;
    static const uint8_t max_val = uint8_t(-1);
    typedef uint8_t (* PRIM)(uint8_t a, uint8_t b, uint8_t* error);
    static const PRIM prim = &snip_add_uint8;

    error = 0; EXPECT_EQ(0U, (*prim)(0, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1U, (*prim)(1, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1U, (*prim)(0, 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val - 1, (*prim)(max_val / 2, max_val / 2, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val, (*prim)(max_val / 2, max_val / 2 + 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val, (*prim)(max_val / 2 + 1, max_val / 2, &error)); EXPECT_EQ(0, error);
}

TEST(snip, add_uint16_no_overflow) {
    uint8_t error;
    static const uint16_t max_val = (uint16_t)(-1);
    typedef uint16_t (*PRIM)(uint16_t a, uint16_t b, uint8_t* error);
    static const PRIM prim = &snip_add_uint16;

    error = 0; EXPECT_EQ(0U, (*prim)(0, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1U, (*prim)(1, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1U, (*prim)(0, 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val - 1, (*prim)(max_val / 2, max_val / 2, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val, (*prim)(max_val / 2, max_val / 2 + 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val, (*prim)(max_val / 2 + 1, max_val / 2, &error)); EXPECT_EQ(0, error);
}

TEST(snip, add_uint32_no_overflow) {
    uint8_t error;
    static const uint32_t max_val = (uint32_t)(-1);
    typedef uint32_t (*PRIM)(uint32_t a, uint32_t b, uint8_t* error);
    static const PRIM prim = &snip_add_uint32;

    error = 0; EXPECT_EQ(0U, (*prim)(0, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1U, (*prim)(1, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1U, (*prim)(0, 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val - 1, (*prim)(max_val / 2, max_val / 2, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val, (*prim)(max_val / 2, max_val / 2 + 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val, (*prim)(max_val / 2 + 1, max_val / 2, &error)); EXPECT_EQ(0, error);
}

TEST(snip, add_uint64_no_overflow) {
    uint8_t error;
    static const uint64_t max_val = (uint64_t)(-1);
    typedef uint64_t (*PRIM)(uint64_t a, uint64_t b, uint8_t* error);
    static const PRIM prim = &snip_add_uint64;

    error = 0; EXPECT_EQ(0U, (*prim)(0, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1U, (*prim)(1, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1U, (*prim)(0, 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val - 1, (*prim)(max_val / 2, max_val / 2, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val, (*prim)(max_val / 2, max_val / 2 + 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(max_val, (*prim)(max_val / 2 + 1, max_val / 2, &error)); EXPECT_EQ(0, error);
}

TEST(snip, add_uint8_overflow) {
    uint8_t error;
    static const uint8_t max_val = uint8_t(-1);
    typedef uint8_t (* PRIM)(uint8_t a, uint8_t b, uint8_t* error);
    static const PRIM prim = &snip_add_uint8;

    error = 0; (*prim)(max_val, 1, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(1, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(1, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(max_val, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(max_val / 2, max_val, &error); EXPECT_EQ(1, error);
}

TEST(snip, add_uint16_overflow) {
    uint8_t error;
    static const uint16_t max_val = uint16_t(-1);
    typedef uint16_t (* PRIM)(uint16_t a, uint16_t b, uint8_t* error);
    static const PRIM prim = &snip_add_uint16;

    error = 0; (*prim)(max_val, 1, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(1, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(1, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(max_val, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(max_val / 2, max_val, &error); EXPECT_EQ(1, error);
}

TEST(snip, add_uint32_overflow) {
    uint8_t error;
    static const uint32_t max_val = uint32_t(-1);
    typedef uint32_t (* PRIM)(uint32_t a, uint32_t b, uint8_t* error);
    static const PRIM prim = &snip_add_uint32;

    error = 0; (*prim)(max_val, 1, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(1, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(1, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(max_val, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(max_val / 2, max_val, &error); EXPECT_EQ(1, error);
}

TEST(snip, add_uint64_overflow) {
    uint8_t error;
    static const uint64_t max_val = uint64_t(-1);
    typedef uint64_t (* PRIM)(uint64_t a, uint64_t b, uint8_t* error);
    static const PRIM prim = &snip_add_uint64;

    error = 0; (*prim)(max_val, 1, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(1, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(1, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(max_val, max_val, &error); EXPECT_EQ(1, error);
    error = 0; (*prim)(max_val / 2, max_val, &error); EXPECT_EQ(1, error);
}

TEST(snip, add_int8_no_overflow) {
    uint8_t error;
    static const int8_t max_val = (int8_t)((1 << (8 - 1)) - 1);
    static const int8_t min_val = -max_val - 1;
    typedef int8_t (* PRIM)(int8_t a, int8_t b, uint8_t* error);
    static const PRIM prim = &snip_add_int8;

    error = 0; EXPECT_EQ(0, (*prim)(0, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1, (*prim)(1, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1, (*prim)(0, 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(-2, (*prim)(-1, -1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(0, (*prim)(-100, 100, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(-1, (*prim)(min_val, max_val, &error)); EXPECT_EQ(0, error);
}

TEST(snip, add_int16_no_overflow) {
    uint8_t error;
    static const int16_t max_val = (int16_t)((1 << (16 - 1)) - 1);
    static const int16_t min_val = -max_val - 1;
    typedef int16_t (* PRIM)(int16_t a, int16_t b, uint8_t* error);
    static const PRIM prim = &snip_add_int16;

    error = 0; EXPECT_EQ(0, (*prim)(0, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1, (*prim)(1, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1, (*prim)(0, 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(-2, (*prim)(-1, -1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(0, (*prim)(-100, 100, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(-1, (*prim)(min_val, max_val, &error)); EXPECT_EQ(0, error);
}

TEST(snip, add_int32_no_overflow) {
    uint8_t error;
    static const int32_t max_val = (int32_t)(((uint32_t)1 << (32 - 1)) - 1);
    static const int32_t min_val = -max_val - 1;
    typedef int32_t (* PRIM)(int32_t a, int32_t b, uint8_t* error);
    static const PRIM prim = &snip_add_int32;

    error = 0; EXPECT_EQ(0, (*prim)(0, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1, (*prim)(1, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1, (*prim)(0, 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(-2, (*prim)(-1, -1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(0, (*prim)(-100, 100, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(-1, (*prim)(min_val, max_val, &error)); EXPECT_EQ(0, error);
}

TEST(snip, add_int64_no_overflow) {
    uint8_t error;
    static const int64_t max_val = (int64_t)(((uint64_t)1 << (64 - 1)) - 1);
    static const int64_t min_val = -max_val - 1;
    typedef int64_t (* PRIM)(int64_t a, int64_t b, uint8_t* error);
    static const PRIM prim = &snip_add_int64;

    error = 0; EXPECT_EQ(0, (*prim)(0, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1, (*prim)(1, 0, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(1, (*prim)(0, 1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(-2, (*prim)(-1, -1, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(0, (*prim)(-100, 100, &error)); EXPECT_EQ(0, error);
    error = 0; EXPECT_EQ(-1, (*prim)(min_val, max_val, &error)); EXPECT_EQ(0, error);
}








} // namespace snip
} // namespace testing
