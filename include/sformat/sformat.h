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
#ifndef _MB_SFORMAT_H_
#define _MB_SFORMAT_H_

#include <stdint.h>
#include "os/mynewt.h"

#ifdef __cplusplus
extern "C" {
#endif

struct sf_hex_tbl_fmt {
    /** Whether or not to render ASCII equivalents. */
    bool show_ascii;
    /** Whether or not to add address labels to the output. */
    bool show_addr;
    /** The starting value for the address labels. */
    unsigned int start_addr;
} __attribute__((packed));


void sf_hex_tabulate_16(struct sf_hex_tbl_fmt *fmt, unsigned char *data,
    unsigned int len);

#ifdef __cplusplus
}
#endif

#endif /* _MB_SFORMAT_H_ */
