# Sample toolchain file for building for Windows from an Ubuntu Linux system.
#
# Typical usage:
#    *) install cross compiler: `sudo apt-get install mingw-w64`
#    *) cmake -H. -B_build_mingw -DCMAKE_TOOLCHAIN_FILE="${PWD}/toolchains/linux-mingw-w64.cmake"
#
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

# set compiler
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_RC_COMPILER  ${TOOLCHAIN_PREFIX}-windres)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -lpthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc -static-libstdc++ -static -lpthread")


# target environment on the build host system
#   set 1st to dir with the cross compiler's C/C++ headers/libs
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

# modify default behavior of FIND_XXX() commands to
# search for headers/libs in the target environment and
# search for programs in the build host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# use emulator for `try_run` calls
set(CMAKE_CROSSCOMPILING_EMULATOR wine64)

# set c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(Qt5_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5)
set(Qt5Core_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Core)
set(Qt5Gui_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Gui)
set(Qt5Widgets_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Widgets)
set(Qt5WebKit_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5WebKit)
set(Qt5WebKitWidgets_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5WebKitWidgets)
set(Qt5WebView_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5WebView)
set(Qt5PrintSupport_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5PrintSupport)
set(Qt5Network_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Network)
set(Qt5Concurrent_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Concurrent)
set(Qt5DBus_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5DBus)
set(Qt5Qml_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Qml)
set(Qt5Quick_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Quick)
set(Qt5QuickWidgets_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5QuickWidgets)
set(Qt5Xml_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Xml)
set(BOOST_ROOT /usr/lib/x86_64-linux-gnu/cmake/Boost)
