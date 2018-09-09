# String Formatting Library for Apache Mynewt

This package contains a number of functions to render numeric data in a
well-formatted, human readable manner, and is intended to help improve
debugging, bug reporting and data display.

It supports rendering 8-bit data in the following formats:

- Hexadecimal (default)
- Decimal (unsigned 8-bit decimal values)
- ASCII (or '.' for out of range values).

For both hexadecimal and decimal out, ASCII equivalents can also be rendered
alongside the raw numeric data for improved human readability.

This package is designed to work with the [Apache Mynewt](https://mynewt.apache.org/) operating system, and was
written using version 1.4.1.

## Dependencies

### Package Dependencies

This package has no package dependencies outside of
[mynewt-core](https://github.com/apache/mynewt-core).

### Libraries

This packages requires no additional libraries during the build process.

## Using this Package

The easiest way to make use of this package is to add it as a project
dependency. This will pull the latest version of the library from Github:

    $ newt TODO

## Development Status

See the dedicated ToDos page for details, or check the [issue
tracking](https://github.com/microbuilder/mb_colorimetry/issues) for the
project on Github.

## Sample Output

### Hexadecimal Renderer

#### Settings

```
fmt.render_as = SF_BYTES_TBL_RNDR_HEX;
fmt.show_ascii = true;
fmt.show_addr = true;
fmt.start_addr = 0x20004000;
```

#### Output

```
          0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
20004000 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 0123456789:;<=>?
20004010 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F @ABCDEFGHIJKLMNO
20004020 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F PQRSTUVWXYZ[\]^_
20004030 60 61 62 63 64 65 66 67 68 69 6A 6B 6C 6D 6E 6F `abcdefghijklmno
20004040 70 71 72 73 74 75 76 77 78 79 7A 7B 7C 7D 7E 7F pqrstuvwxyz{|}~.
```

### Decimal Renderer

#### Settings

```
fmt.render_as = SF_BYTES_TBL_RNDR_DEC;
fmt.show_ascii = true;
fmt.show_addr = true;
fmt.start_addr = 0x20004000;
```

> NOTE: Rendering decimal values in combination with the ASCII equivalents
  will cause output > 80 characters wide.

#### Output

```
           0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
20004000 048 049 050 051 052 053 054 055 056 057 058 059 060 061 062 063 0123456789:;<=>?
20004010 064 065 066 067 068 069 070 071 072 073 074 075 076 077 078 079 @ABCDEFGHIJKLMNO
20004020 080 081 082 083 084 085 086 087 088 089 090 091 092 093 094 095 PQRSTUVWXYZ[\]^_
20004030 096 097 098 099 100 101 102 103 104 105 106 107 108 109 110 111 `abcdefghijklmno
20004040 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 pqrstuvwxyz{|}~.
```

### ASCII Renderer

#### Settings

```
fmt.render_as = SF_BYTES_TBL_RNDR_ASC;
fmt.show_ascii = true;
fmt.show_addr = true;
fmt.start_addr = 0x20004000;
```

> NOTE: The `show_addr` field will be ignored in this case since it has
  no added-value compared to other `render_as` settings.

#### Output

```
         0 1 2 3 4 5 6 7 8 9 A B C D E F
20004000 1 2 3 4 5 6 7 8 9 : ; < = > ? @
20004010 A B C D E F G H I J K L M N O P
20004020 Q R S T U V W X Y Z [ \ ] ^ _ .
20004030 a b c d e f g h i j k l m n o p
20004040 q r s t u v w x y z { | } ~  .
```
