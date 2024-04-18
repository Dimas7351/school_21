# SmartCalc
* [Description](#description)
* [Build](#build)
* [Tests](#tests)
* [Documentation](#documentation)
* [Test Coverage](#test-coverage)
* [Archive](#archive)

## Description
An application for calculating complex mathematical expressions, for plotting various functions with a graph.

## Build
To build, you need to have `cmake` on your device.

    $ git clone https://github.com/ksilisk/SmartCalc.git
    $ cd SmartCalc
    $ make install

## Tests
Unit tests with `check.h` C library.

    $ cd SmartCalc
    $ make test

## Documentation
Documentation is generated using `Doxygen`. Before use, you need to change the `INPUT` value in the Doxygen file.
    
    $ cd SmartCalc
    $ make dvi
    
## Test Coverage
Test coverage is estimated using `lcov`.

    $ cd SmartCalc
    $ make gcov_report
    
## Archive
The archive is built using `tar`.

    $ cd SmartCalc
    $ make dist
