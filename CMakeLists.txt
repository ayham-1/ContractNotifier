cmake_minimum_required(VERSION 3.10)
project("ContractNotifier")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(CMAKE_CXX_FLAGS -pthread)

include(InstallRequiredSystemLibraries)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Set Compiler Specific Commands, Cross-Platform
if(MSVC)
	# Microsoft visual studio
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4 /EHsc")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /SUBSYSTEM:WINDOWS /W4 /EHsc")
	endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	# GNU compilers
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wno-long-long -lstdc++fs")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-long-long -lstdc++fs")
endif()

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
if (WIN32)
	add_definitions(-D__WIN32__)
endif(WIN32)
if (UNIX)
	add_definitions(-D__LINUX__)
endif(UNIX)
# Libraries

# Qt5
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Boost stuff
find_package(Boost COMPONENTS serialization REQUIRED)

# curl
if (WIN32)
	find_package(CURL CONFIG REQUIRED)
elseif(UNIX)
find_package(CURL REQUIRED)
endif()
include_directories(${CURL_INCLUDE_DIR})

file(GLOB_RECURSE hdrs "src/*.h")
file(GLOB_RECURSE srcs "src/*.cpp")
file(GLOB_RECURSE ui "src/*.ui")
include_directories("." "src/")

add_executable(contractNotifier ${ui} ${hdrs} ${srcs})
target_link_libraries(contractNotifier Qt5::Core Qt5::Widgets Boost::serialization ${CMAKE_THREAD_LIBS_INIT} ${CURL_LIBRARIES})
if (WIN32)
	if (CMAKE_BUILD_TYPE STREQUAL "Release")
		set_target_properties(contractNotifier PROPERTIES WIN32_EXECUTABLE TRUE)
	endif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_link_libraries(contractNotifier Qt5::Core Qt5::Widgets Boost::serialization ${CMAKE_THREAD_LIBS_INIT} CURL::libcurl)
endif(WIN32)

# examples
add_executable(dataBenchmark "examples/dataBenchmark.cpp")
target_link_libraries(dataBenchmark Qt5::Core Qt5::Widgets Boost::serialization ${CMAKE_THREAD_LIBS_INIT} ${CURL_LIBRARIES})
if (WIN32)
	target_link_libraries(dataBenchmark Qt5::Core Qt5::Widgets Boost::serialization ${CMAKE_THREAD_LIBS_INIT} CURL::libcurl)
endif(WIN32)

add_executable(searchBenchmark "examples/searchBenchmark.cpp")
target_link_libraries(searchBenchmark Qt5::Core Qt5::Widgets Boost::serialization ${CMAKE_THREAD_LIBS_INIT} ${CURL_LIBRARIES})
if (WIN32)
	target_link_libraries(searchBenchmark Qt5::Core Qt5::Widgets Boost::serialization ${CMAKE_THREAD_LIBS_INIT} CURL::libcurl)
endif(WIN32)

# res files:
add_custom_command(
	TARGET contractNotifier POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/res/icon.png
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/icon.png)
add_custom_command(
	TARGET contractNotifier POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/vendor/notifu.exe
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/notifu.exe)

# Install stuff
install(TARGETS contractNotifier
	RUNTIME DESTINATION "bin"
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib")
install(DIRECTORY "res" DESTINATION bin)
install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION bin COMPONENT Libraries)

# Package Generator
set(CPACK_PACKAGE_DESCRIPTION "A Contract notifier application")
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_VENDOR "altffour")
set(CPACK_PACKAGE_CONTACT "ayhamaboualfadl@gmail.com")
set(CPACK_PACKAGE_FILE_NAME contractNotifier)
set(CPACK_NSIS_CREATE_ICONS_EXTRA
	"CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\ContractNotifier.lnk' '$INSTDIR\\\\contractNotifier.exe'")
include(CPack)
