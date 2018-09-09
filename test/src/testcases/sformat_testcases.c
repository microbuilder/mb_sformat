/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <string.h>
#include "sformat_test_priv.h"

/** Checks if two float values are 'nearly' equal (diff < epsilon) */
static bool
f_is_equal(float a, float b, float epsilon)
{
    float c;

    c = a - b;

    return c < epsilon && -c < epsilon;
}

TEST_CASE(test_tbl_hex)
{
    int i;
    struct sf_bytes_tbl_fmt fmt;
    uint8_t test_data[256];

    memset(&fmt, 0, sizeof fmt);
    fmt.render_as = SF_BYTES_TBL_RNDR_HEX;
    fmt.show_ascii = true;
    fmt.show_addr = true;
    fmt.start_addr = 0x20004000;

    /* Populate test_data. */
    for (i=0; i<256; i++) {
        test_data[i] = i;
    };

    /* Render the first 64 bytes of flash memory. */
    sf_bytes_tbl_16(&fmt, &test_data[48], 80);

    /* Intentionally fail to see results for now. */
    TEST_ASSERT(f_is_equal(1.0f, 1.1f, 1E-5F));
}

TEST_CASE(test_tbl_dec)
{
    int i;
    struct sf_bytes_tbl_fmt fmt;
    uint8_t test_data[256];

    memset(&fmt, 0, sizeof fmt);
    fmt.render_as = SF_BYTES_TBL_RNDR_DEC;
    fmt.show_ascii = true;
    fmt.show_addr = true;
    fmt.start_addr = 0x20004000;

    /* Populate test_data. */
    for (i=0; i<256; i++) {
        test_data[i] = i;
    };

    /* Render the first 64 bytes of flash memory. */
    sf_bytes_tbl_16(&fmt, &test_data[48], 80);

    /* Intentionally fail to see results for now. */
    TEST_ASSERT(f_is_equal(1.0f, 1.1f, 1E-5F));
}

TEST_CASE(test_tbl_asc)
{
    int i;
    struct sf_bytes_tbl_fmt fmt;
    uint8_t test_data[256];

    memset(&fmt, 0, sizeof fmt);
    fmt.render_as = SF_BYTES_TBL_RNDR_ASC;
    fmt.show_ascii = true;
    fmt.show_addr = true;
    fmt.start_addr = 0x20004000;

    /* Populate test_data. */
    for (i=0; i<256; i++) {
        test_data[i] = i;
    };

    /* Render the first 64 bytes of flash memory. */
    sf_bytes_tbl_16(&fmt, &test_data[48], 80);

    /* Intentionally fail to see results for now. */
    TEST_ASSERT(f_is_equal(1.0f, 1.1f, 1E-5F));
}
