<!-- @file README.md -->
<!-- For doxygen --> \mainpage
# Purpose

Illustrate various C++11/14/17 techniques with SystemC 2.3.2.

## Block diagram

```
.---------------------------------------------------------------.
|                                                               |
|  Stimulus                                                     |
|  _module                                                      |
|  .------.                                                     |
|  | stim |                                                     |
|  '------'                                                     |
|    [ ]                                                        |
|     |                                                         |
|     o                                                         |
|  .------.                                                     |
|  | raw  | sc_fifo                                             |
|  '-fifo-'                                                     |
|     o                                                         |
|     |                                                         |
|     |                                                         |
|     |             Processing                       Checker    |
|     |             _module           sc_buffer      _module    |
|     |             .-----------.      .------.      .-------.  |
|     |       .---[]|> process >|[]---o|result|o---[]|>      |  |
|    [ ]      |     '-----^-----'      '------'      |       |  |
|  .------.   |           |                          |       |  |
|  |     1|o--'  .-----.  |                          |       |  |
|  | dupl |      |clock|--'                          | check |  |
|  |     2|o--.  '-----'                             |       |  |
|  '------'   |                                      |       |  |
|  Duplicator |                             raw_in   |       |  |
|  _module    '------------------------------------[]|>      |  |
|                                                    '-------'  |
|                                                               |
'---------------------------------------------------------------'
```

## How to run

Build and execute with the `build` script:

```sh
build -run -- -d
```

Alternately, do it by hand:

```sh
mkdir -p build
pushd build
rm -f *.log
cmake .. 2>&1 | tee build.log
make docs 2>&1 | tee -a build.log
make modern 2>&1 | tee -a build.log
env LD_LIBRARY_PATH=$SYSTEMC/lib* ./modern 2>&1 | grep -v ^$ | tee run.log
popd
```

<!--///* The end *///-->
