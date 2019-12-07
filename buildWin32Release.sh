#!/bin/bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=CMake/Toolchain-mingw64.cmake ..
make -j9
cd ..
