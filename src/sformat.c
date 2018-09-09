/**
 * Depending on the type of package, there are different
 * compilation rules for this directory.  This comment applies
 * to packages of type "pkg."  For other types of packages,
 * please view the documentation at http://mynewt.apache.org/.
 *
 * Put source files in this directory.  All files that have a *.c
 * ending are recursively compiled in the src/ directory and its
 * descendants.  The exception here is the arch/ directory, which
 * is ignored in the default compilation.
 *
 * The arch/<your-arch>/ directories are manually added and
 * recursively compiled for all files that end with either *.c
 * or *.a.  Any directories in arch/ that don't match the
 * architecture being compiled are not compiled.
 *
 * Architecture is set by the BSP/MCU combination.
 */

#include <ctype.h>
#include "sformat/sformat.h"

/**
 * Renders the ASCII equivalents for a row of values, with non-printable
 * characters represented by the char assigned to the 'ninvis' parameter.
 *
 * @param Pointer to the array of data to render as ASCII values.
 * @param The number of characters to attempt to render.
 * @param The single character to use to represent non-printable characters
 *        outside of the standard ASCII range.
 */
static void
sf_bytes_rndr_ascii(unsigned char *data, unsigned int len, unsigned char nonvis)
{
    unsigned int idx;

    /* Render printable characters. */
    idx = 0;
    while (len) {
        printf("%c", isprint(data[idx]) ? data[idx] : nonvis);
        idx++;
        len--;
    }
}

void
sf_bytes_tbl_16(struct sf_tbl_cfg *cfg, unsigned char *data, unsigned int len)
{
    unsigned int idx;
    unsigned int cur_pos;
    unsigned int cur_addr;
    unsigned int end_addr;

    if (!len) {
      return;
    }

    /* Set the end address (since we modify len in the write loop). */
    end_addr = cfg->start_addr + len;

    /* Check if we need to render the top address bar. */
    if (cfg->show_addr) {
        /* Render the top address bar. */
        switch (cfg->format) {
            case SF_TABLE_DSPL_FMT_DEC:
                /* 3 chars plus a space. */
                printf("           "
                  "0   1   2   3   4   5   6   7   8   9   "
                  "A   B   C   D   E   F\n");
                break;
            case SF_TABLE_DSPL_FMT_ASC:
                /* 1 char plus a space. */
                printf("         "
                  "0 1 2 3 4 5 6 7 8 9 A B C D E F\n");
                break;
            case SF_TABLE_DSPL_FMT_HEX:
            default:
                /* 2 chars plus a space. */
                printf("          "
                  "0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
                break;
        }
        printf("%08X ", cfg->start_addr - (cfg->start_addr % 16));
    }

    /* Insert offset padding for first row if necessary. */
    if (cfg->show_addr) {
      cur_pos = cfg->start_addr % 16;
      if (cur_pos != 0) {
          for(idx = 0; idx < cur_pos; idx++) {

              switch (cfg->format) {
                  case SF_TABLE_DSPL_FMT_DEC:
                      printf("    ");
                      break;
                  case SF_TABLE_DSPL_FMT_ASC:
                      printf("  ");
                      break;
                  case SF_TABLE_DSPL_FMT_HEX:
                  default:
                      printf("   ");
                      break;
              }
          }
      }
    } else {
      cur_pos = 0;
    }

    /* Print data row by row. */
    idx = 0;
    cur_addr = cfg->start_addr;
    while(len) {
        /* Print the current value. */
        switch (cfg->format) {
            case SF_TABLE_DSPL_FMT_DEC:
            printf("%03u ", (uint8_t)data[idx++]);
                break;
            case SF_TABLE_DSPL_FMT_ASC:
                printf("%c ", isprint(data[idx++]) ? data[idx] : '.');
                break;
            case SF_TABLE_DSPL_FMT_HEX:
            default:
                printf("%02X ", data[idx++]);
                break;
        }

        /* Increment position counters. */
        cur_pos++;
        cur_addr++;

        /* Wrap around to the next line if necessary. */
        if (cur_pos == 16 || cur_addr == end_addr) {
            /* Render ASCII equivalents at end of row if requested. */
            if ((cfg->show_ascii) && !(cfg->format ==
                SF_TABLE_DSPL_FMT_ASC)) {
                if (cur_addr == end_addr) {
                    /* Handle last/single row. */
                    if (cur_addr % 16) {
                        /* PARTIAL row (< 16 values). */
                        printf("%.*s", (16 - cur_addr % 16) * 3,
                        "                                                ");
                        sf_bytes_rndr_ascii(&data[idx - (cur_addr % 16)],
                            cur_addr - cfg->start_addr < 16 ? idx % 16 : cur_addr % 16, '.');
                    } else {
                        /* FULL row. */
                        sf_bytes_rndr_ascii(&data[idx-16], 16, '.');
                    }
                } else if (cur_addr < cfg->start_addr + 15) {
                    /* Handle first row. */
                    printf("%.*s", cfg->start_addr % 16, "                ");
                    sf_bytes_rndr_ascii(data, 16 - cfg->start_addr % 16, '.');
                } else {
                    /* Full row. */
                    sf_bytes_rndr_ascii(&data[idx-16], 16, '.');
                }
            }

            /* Wrap around if this isn't the last row. */
            printf("\n");
            if (cur_addr != end_addr) {
                /* Render the next base row address if required. */
                if (cfg->show_addr) {
                    printf("%08X ", cur_addr);
                }
            }
            cur_pos = 0;
        }
        len--;
    }
}

void sf_mbuf_tbl_16(struct sf_tbl_cfg *cfg, struct os_mbuf *om)
{
    const struct os_mbuf *cur;
    unsigned int count;

    for (cur = om; cur != NULL; cur = SLIST_NEXT(cur, om_next)) {
        printf("os_mbuf record #%u [len=%u]:\n\n", count++, cur->om_len);
        sf_bytes_tbl_16(cfg, OS_MBUF_DATA(om, uint8_t *), cur->om_len);
        printf("\n");
        /* Offset the starting address an appropriate number of bytes. */
        cfg->start_addr += cur->om_len;
    }
}
