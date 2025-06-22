# trielext
unoptimized TRIE word search

## Requirements
- CMake >= 3.14
- C++17 compiler

- ## Configuration

Edit `src/config.hpp.in` to modify install paths and data locations.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Install

Local install (default):
```bash
make install
```

System install:
```bash
sudo make install
```

Clean:
```bash
make clean
```


