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

/** Indicates the display format used when rendering 8-bit data. */
enum sf_bytes_tbl_rndr {
    /** Render values in hexadecimal format (default). */
    SF_BYTES_TBL_RNDR_HEX = 0,

    /** Render values in unsigned decimal format. */
    SF_BYTES_TBL_RNDR_DEC = 1,

    /** Render values in ASCII format ('.' if value is out of range). */
    SF_BYTES_TBL_RNDR_ASC = 2
};

/** Configurable rendering options for 8-bit tabular data. */
struct sf_bytes_tbl_fmt {
    /** Indicates how the data should be rendered. */
    enum sf_bytes_tbl_rndr render_as;

    /** Whether or not to render ASCII equivalents in a right-hand column. */
    bool show_ascii;

    /** Whether or not address labels should be added to the output. */
    bool show_addr;

    /**
     * The starting value for the address labels, which will be correlated
     * with the first byte in the provided payload.
     */
    unsigned int start_addr;
} __attribute__((packed));

/**
 * Renders 8-bit values in a 16 column wide table, with optional address
 * labels and ASCII text equivalents.
 *
 * @param Pointer to the sf_hex_tbl_fmt struct indicating which optional
 *        features should be enabled when rendering the table.
 * @param Pointer to the data to render.
 * @param Number of bytes to render.
 */
void sf_bytes_tbl_16(struct sf_bytes_tbl_fmt *fmt, unsigned char *data,
    unsigned int len);

#ifdef __cplusplus
}
#endif

#endif /* _MB_SFORMAT_H_ */
