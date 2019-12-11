cmake_minimum_required(VERSION 3.10)
project("ContractNotifier")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
SET(CMAKE_CXX_FLAGS -pthread)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Set C++ standard set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Set build type definitions.
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-D__DEBUG__)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
if (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions(-D__RELEASE__)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# Platform Definitions.
if (MINGW)
	add_definitions(-D__MINGW__)
else()
	add_definitions(-D__LINUX__)
endif(MINGW)

# Libraries

# Qt5
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Boost stuff
find_package(Boost COMPONENTS serialization REQUIRED)

# curl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

file(GLOB_RECURSE hdrs "src/*.h")
file(GLOB_RECURSE srcs "src/*.cpp")
file(GLOB_RECURSE ui "src/*.ui")
include_directories("." "src/")

add_executable(contractNotifier ${ui} ${hdrs} ${srcs})
target_link_libraries(contractNotifier Qt5::Core Qt5::Widgets Boost::serialization ${CMAKE_THREAD_LIBS_INIT} ${CURL_LIBRARIES})
