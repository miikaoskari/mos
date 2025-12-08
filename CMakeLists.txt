cmake_minimum_required(VERSION 3.30)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)

set(CMAKE_COLOR_DIAGNOSTICS ON)

include(FetchContent)

project(mos C ASM)

add_executable(kernel.elf
    src/main.c
    src/boot.S
    src/entry.S
    src/driver.c
    src/irq.c
    src/memory.c
    src/drivers/irq/arm/gicv3/gicv3.c
    src/drivers/tty/serial/arm/pl011/pl011.c
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
    ${libfdt_SOURCE_DIR}/libfdt/fdt_addresses.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_ro.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_wip.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_sw.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_rw.c
    ${libfdt_SOURCE_DIR}/libfdt/fdt_strerror.c
)

target_include_directories(fdt SYSTEM PUBLIC
    ${libfdt_SOURCE_DIR}/libfdt
)

add_library(libc STATIC
    libs/string/memchr.c
    libs/string/memcmp.c
    libs/string/memcpy.c
    libs/string/memmove.c
    libs/string/memrchr.c
    libs/string/memset.c
    libs/string/strcmp.c
    libs/string/strlen.c
    libs/string/strncmp.c
    libs/string/strnlen.c
    libs/string/strrchr.c
)

target_link_libraries(kernel.elf PRIVATE fdt libc)

# C compiler options
target_compile_options(kernel.elf PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-nostdlib>
    $<$<COMPILE_LANGUAGE:C>:-ffreestanding>
    $<$<COMPILE_LANGUAGE:C>:-O0>
    $<$<COMPILE_LANGUAGE:C>:-g3>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Wpedantic>
    $<$<COMPILE_LANGUAGE:C>:-Wunused>
    $<$<COMPILE_LANGUAGE:C>:-Wconversion>
    $<$<COMPILE_LANGUAGE:C>:-Wsign-conversion>
    $<$<COMPILE_LANGUAGE:C>:-Wuninitialized>
    $<$<COMPILE_LANGUAGE:C>:-Wshadow>
    $<$<COMPILE_LANGUAGE:C>:-Wpointer-arith>
    $<$<COMPILE_LANGUAGE:C>:-Wcast-align>
    $<$<COMPILE_LANGUAGE:C>:-Wwrite-strings>
    $<$<COMPILE_LANGUAGE:C>:-Wmissing-prototypes>
    $<$<COMPILE_LANGUAGE:C>:-Wstrict-prototypes>
    $<$<COMPILE_LANGUAGE:C>:-fno-omit-frame-pointer>
)

target_link_options(kernel.elf PRIVATE
    -T ${CMAKE_SOURCE_DIR}/linker.ld
    -nostdlib
    -g
)
