# header-dump
[![GitHub](https://img.shields.io/github/license/alkurbatov/header-dump)](https://github.com/alkurbatov/header-dump/blob/main/LICENSE)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-green.svg)](https://isocpp.org/std/the-standard)

Tiny utility to dump info from WAVE header.

## Prerequisites
1. Download and install [CMake](https://cmake.org/download/).
2. A compiler with C++20 support.

## Build instructions
1. Generate build routine:
   ``` bash
   cmake -B build -DCMAKE_BUILD_TYPE=Release
   ```

2. Build the utility:
   ``` bash
   cmake --build build
   ```

## Run the utility
   ```bash
   ./build/bin/header-dump ~/work/testdata/audio-samples/alaw.wav
   ```

## License
Copyright (c) 2023-2024 Alexander Kurbatov

Licensed under the [GPLv3 license](LICENSE).
