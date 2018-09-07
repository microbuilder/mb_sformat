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

static void
sf_hex_render_ascii(unsigned char *data, unsigned int len, unsigned char nonvis)
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
sf_hex_tabulate_16(struct sf_hex_tbl_fmt *fmt, unsigned char *data,
    unsigned int len)
{
    unsigned int idx;
    unsigned int cur_pos;
    unsigned int cur_addr;
    unsigned int end_addr;

    if (!len) {
      return;
    }

    /* Set the end address (since we modify len in the write loop). */
    end_addr = fmt->start_addr + len;

    /* Check if we need to render the top address bar. */
    if (fmt->show_addr) {
        /* Render the top address bar. */
        printf("          0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
        printf("%08X ", fmt->start_addr - (fmt->start_addr % 16));
    }

    /* Insert offset padding for first row if necessary. */
    if (fmt->show_addr) {
      cur_pos = fmt->start_addr % 16;
      if (cur_pos != 0) {
          for(idx = 0; idx < cur_pos; idx++) {
              printf("   ");
          }
      }
    } else {
      cur_pos = 0;
    }

    /* Print data row by row. */
    idx = 0;
    cur_addr = fmt->start_addr;
    while(len) {
        /* Print the current value. */
        printf("%02X ", data[idx++]);
        cur_pos++;
        cur_addr++;

        /* Wrap around to the next line if necessary. */
        if (cur_pos == 16 || cur_addr == end_addr) {
            /* Render ASCII equivalents at end of row if requested. */
            if (fmt->show_ascii) {
                if (cur_addr == end_addr) {
                    /* Handle last/single row. */
                    if (cur_addr % 16) {
                        /* PARTIAL row (< 16 values). */
                        printf("%.*s", (16 - cur_addr % 16) * 3,
                        "                                                ");
                        sf_hex_render_ascii(&data[idx - (cur_addr % 16)],
                            cur_addr - fmt->start_addr < 16 ? idx % 16 : cur_addr % 16, '.');
                    } else {
                        /* FULL row. */
                        sf_hex_render_ascii(&data[idx-16], 16, '.');
                    }
                } else if (cur_addr < fmt->start_addr + 15) {
                    /* Handle first row. */
                    printf("%.*s", fmt->start_addr % 16, "                ");
                    sf_hex_render_ascii(data, 16 - fmt->start_addr % 16, '.');
                } else {
                    /* Full row. */
                    sf_hex_render_ascii(&data[idx-16], 16, '.');
                }
            }

            /* Wrap around if this isn't the last row. */
            printf("\n");
            if (cur_addr != end_addr) {
                /* Render the next base row address if required. */
                if (fmt->show_addr) {
                    printf("%08X ", cur_addr);
                }
            }
            cur_pos = 0;
        }
        len--;
    }
}
