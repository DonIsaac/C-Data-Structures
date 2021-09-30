# C Data Structures

[![C/C++ CI](https://github.com/DonIsaac/C-Data-Structures/actions/workflows/check.yml/badge.svg)](https://github.com/DonIsaac/C-Data-Structures/actions/workflows/check.yml)
[![codecov](https://codecov.io/gh/DonIsaac/C-Data-Structures/branch/main/graph/badge.svg?token=Z3K6B6177K)](https://codecov.io/gh/DonIsaac/C-Data-Structures)

A library of data structures in C. [Documentation is available here.](https://www.donisaac.dev/C-Data-Structures/)

## Maps

Stores key/value pairs. Keys are null-terminated strings, while values may be
any type of any size. Maps may store heterogenous data.

The map implementations that are currently available are:

- Binary Search Tree (`bintree.h`)
- Linked List (`linkedlist.h`) _(note: incomplete)_

## Lists

_TODO: Currently no list implementations are available_

## Building
> TL;DR: `make`

To build the source code, run `make`. For production use, run `make PROD=1`.
This enables compiler optimizations and removes `assert` macros. For development
and testing, run `make DEBUG=1`.

## Testing
> TL;DR: `make check DEBUG=1`

Tests are located in the `test` folder. They use a modified version of
[MinUnit](https://jera.com/techinfo/jtns/jtn002), located in `test/minunit.h`.
Running `make check DEBUG=1` will run all test suites while checking for memory
leaks. It then generates code coverage reports using `gcov`.

Note that `DEBUG=1` is recommended but not required for running tests. However,
it is required for generating coverage reports.  Running tests without setting
`DEBUG=1` will remove debugging symbols, making Valgrind unable to show
source-code lines.

## Other Commands

- `make clean`: Removes binaries, object files, coverage reports, etc.
- `make docs`: Builds documentation webpages using [Doxygen](https://www.doxygen.nl/index.html)
- `make install`: Installs packages used by other commands using `apt-get`. The
  installed packages include:
    - [Valgrind](https://www.valgrind.org/)
    - [Doxygen](https://man7.org/linux/man-pages/man1/gcov.1.html)
    - [`gcov`](https://man7.org/linux/man-pages/man1/gcov.1.html)
    - [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html)

## License

This code is made available under the MIT License. A copy of it is available in
`LICENSE`.
