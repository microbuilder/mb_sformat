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

 /**
  * \defgroup SFORMAT String Formatter
  *
  * Helper functions to render 8-bit data in human-readable format.
  */

#ifndef _MB_SFORMAT_H_
#define _MB_SFORMAT_H_

#include <stdint.h>
#include "os/mynewt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup STRUCTS Structs and Enums
 *
 * Common rendering-related structs and enums.
 *
 * \ingroup SFORMAT
 *  @{ */

/** Indicates the display format used when rendering 8-bit data. */
enum sf_tbl_dspl_fmt {
    /** Render values in hexadecimal format (default). */
    SF_TABLE_DSPL_FMT_HEX = 0,

    /** Render values in unsigned decimal format. */
    SF_TABLE_DSPL_FMT_DEC = 1,

    /** Render values in ASCII format ('.' if value is out of range). */
    SF_TABLE_DSPL_FMT_ASC = 2
};

/** Configurable rendering options for 8-bit tabular data. */
struct sf_tbl_cfg {
    /** Indicates the display format for the data. */
    enum sf_tbl_dspl_fmt format;

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

/** @} */ /* End of STRUCTS group */

/**
 * @addtogroup FUNC Functions
 *
 * Helper functions to render 8-bit data.
 *
 * \ingroup SFORMAT
 *  @{ */

/**
 * Renders 8-bit values in a 16 column wide table, with optional address
 * labels and ASCII text equivalents.
 *
 * @param cfg   Pointer to the sf_tbl_cfg struct indicating which optional
 *              features should be enabled when rendering the table.
 * @param data  Pointer to the data to render.
 * @param len   Number of bytes to render.
 */
void sf_bytes_tbl_16(struct sf_tbl_cfg *cfg, unsigned char *data,
    unsigned int len);

/**
 * Renders an mbuf chain in 16 column wide tabular format, with optional
 * address labels and ASCII text equivalents.
 *
 * @param cfg   Pointer to the sf_tbl_cfg struct indicating which optional
 *              features should be enabled when rendering the table.
 * @param m     Pointer to the mbuf chain to render.
 */
void sf_mbuf_tbl_16(struct sf_tbl_cfg *cfg, struct os_mbuf *m);

/** @} */ /* End of FUNC group */

#ifdef __cplusplus
}
#endif

#endif /* _MB_SFORMAT_H_ */

/** @} */ /* End of colorimetry group */
