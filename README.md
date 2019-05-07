<!-- @file README.md -->
# Purpose

Illustrate various C++11/14/17 techniques with SystemC 2.3.2.

## How to run

If you get this as a single file, it needs to be split into its component pieces
using the `cxxsplit` script.

```sh
cxxsplit magnitude.cxx
```

Build and execute with the `build` script:

```sh
build -run -- -d
```

<!--///* The end *///-->
