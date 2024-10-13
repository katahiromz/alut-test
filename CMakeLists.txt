# CMakeLists.txt --- CMake project settings
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 3.6)

# project name and languages
project(alut-test VERSION 0.0 LANGUAGES CXX)

# We don't want dependency of runtime libraries
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    set(CMAKE_C_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "-static")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "-static")
elseif (MSVC)
    # replace "/MD" with "/MT" (building without runtime DLLs)
    set(CompilerFlags
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    foreach(CompilerFlags ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlags} "${${CompilerFlags}}")
    endforeach()
endif()

# set output directory (build/)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# UTF-8
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

##############################################################################
# OpenAL - Audio library
# Please set OPENALDIR environment variable.

find_package(OpenAL)

set(MY_OPENAL_LIBRARY "")

if(OpenAL_FOUND)
    add_definitions(-DHAVE_OPENAL)
    include_directories("${OPENAL_INCLUDE_DIR}" "${OPENAL_INCLUDE_DIR}/..")
endif()

##############################################################################
# alut

if(OpenAL_FOUND)
    add_subdirectory(freealut)
endif()

##############################################################################
# Display current status

message(STATUS "OPENAL_INCLUDE_DIR: ${OPENAL_INCLUDE_DIR}")
message(STATUS "OPENAL_LIBRARY: ${MY_OPENAL_LIBRARY}")
message(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

##############################################################################
# alut-test.exe

add_executable(alut-test alut-test.cpp)
target_link_libraries(alut-test PRIVATE alut)
