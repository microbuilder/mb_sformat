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
#include <assert.h>
#include <stddef.h>
#include "os/mynewt.h"
#include "testutil/testutil.h"
#include "sformat_test_priv.h"

TEST_CASE_DECL(test_bytes_tbl_hex)
TEST_CASE_DECL(test_bytes_tbl_dec)
TEST_CASE_DECL(test_bytes_tbl_asc)
TEST_CASE_DECL(test_mbuf_tbl_hex)

int
sf_test_all(void)
{
    sf_test_suite();
    return tu_case_failed;
}

TEST_SUITE(sf_test_suite)
{
    test_bytes_tbl_hex();
    test_bytes_tbl_dec();
    test_bytes_tbl_asc();
    test_mbuf_tbl_hex();
}

#if MYNEWT_VAL(SELFTEST)

int
main(int argc, char **argv)
{
    sysinit();

    sf_test_all();
    return tu_any_failed;
}

#endif
