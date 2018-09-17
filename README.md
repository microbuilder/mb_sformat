# String Format Package for Mynewt

> **NOTE**: This package developed against Apache Mynewt release 1.4.1.

This package allows you to display **binary data** or **`os_mbuf` chains** in
well-formatted tables, and can help with debugging or data analysis.

Individual bytes can be displayed in the following formats:

* `SF_TABLE_DSPL_FMT_HEX`: Hexadecimal values (ex. `FE`)
* `SF_TABLE_DSPL_FMT_DEC`: Decimal values (ex. `127`)
* `SF_TABLE_DSPL_FMT_ASC`: ASCII character codes (ex. `M`)

The following struct is used to indicate how the data should be rendered:

```
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
```

The start address, and whether or not to show an ASCII equivalents of values
can be set in the struct above using the appropriate fields.

The two key functions to call, depending on the source of data, are:

* `void sf_bytes_tbl_16(struct sf_tbl_cfg *cfg, unsigned char *data,
   unsigned int len);`
* `void sf_mbuf_tbl_16(struct sf_tbl_cfg *cfg, struct os_mbuf *om,
   bool verbose);`

## Example

```
int i;
struct sf_tbl_cfg cfg;
uint8_t test_data[256];

memset(&cfg, 0, sizeof cfg);
cfg.format = SF_TABLE_DSPL_FMT_HEX;
cfg.show_ascii = true;
cfg.show_addr = true;
cfg.start_addr = 0x20004000;

/* Populate test_data. */
for (i=0; i<256; i++) {
    test_data[i] = i;
};

/* Render the first 64 bytes of flash memory. */
sf_bytes_tbl_16(&cfg, &test_data[48], 80);
```

would generate the following output:

```
         0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
20004000 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 0123456789:;<=>?
20004010 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F @ABCDEFGHIJKLMNO
20004020 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F PQRSTUVWXYZ[\]^_
20004030 60 61 62 63 64 65 66 67 68 69 6A 6B 6C 6D 6E 6F `abcdefghijklmno
20004040 70 71 72 73 74 75 76 77 78 79 7A 7B 7C 7D 7E 7F pqrstuvwxyz{|}~.
```

## Package Structure

- **Unit tests** are provided in the `test` folder, which can also
serve as an example of how the various functions and structs in this package
can be used.

- Reasonably complete **documentation** is available in the `docs` folder. The
doxygen style documentation can be built via `doxygen Doxyfile`.

### Note on unit tests

For the moment, unit tests in this package **intentionally** fail. They are
used to test the output of the functions during local development since
testing the output this way is quicker than running the code on actual hardware.

These tests will be changed before final release to perform checks against an
internal memory buffer.
