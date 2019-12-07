#!/bin/bash
mkdir build
cd build
i686-w64-mingw32.static-qmake-qt5 CONFIG+=debug ..
make -j9
cd ..
