cmake_minimum_required(VERSION 3.30)
project(mos C ASM)

set(CMAKE_C_STANDARD 23)

include(cmake/libfdt.cmake)
add_subdirectory(libs)
add_subdirectory(src)
