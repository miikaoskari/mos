cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER aarch64-none-elf-gcc)
set(CMAKE_ASM_COMPILER aarch64-none-elf-as)
set(CMAKE_OBJCOPY aarch64-none-elf-objcopy)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)

include(FetchContent)

project(mos C ASM)

add_executable(kernel.elf
    src/main.c
    src/boot.S
    libs/string/memchr.c
    libs/string/memcmp.c
    libs/string/memcpy.c
    libs/string/memmove.c
    libs/string/strlen.c
    libs/string/strnlen.c
)

include_directories(include)

FetchContent_Declare(
    libfdt
    GIT_REPOSITORY https://github.com/dgibson/dtc.git 
    GIT_TAG        v1.7.2
)

FetchContent_MakeAvailable(libfdt)

add_library(fdt STATIC
    ${libfdt_SOURCE_DIR}/libfdt/fdt.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_ro.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_wip.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_sw.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_rw.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_strerror.c
)

target_include_directories(fdt PUBLIC
    ${libfdt_SOURCE_DIR}/libfdt
)

target_link_libraries(kernel.elf PRIVATE fdt)

# C compiler options
target_compile_options(kernel.elf PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-nostdlib>
    $<$<COMPILE_LANGUAGE:C>:-ffreestanding>
    $<$<COMPILE_LANGUAGE:C>:-O0>
    $<$<COMPILE_LANGUAGE:C>:-g3>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-fno-omit-frame-pointer>
)

target_link_options(kernel.elf PRIVATE
    -T ${CMAKE_SOURCE_DIR}/linker.ld
    -nostdlib
    -g
)
