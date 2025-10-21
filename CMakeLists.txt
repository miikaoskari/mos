cmake_minimum_required(VERSION 3.20)

project(mos C ASM)

set(CMAKE_C_COMPILER aarch64-none-elf-gcc)
set(CMAKE_ASM_COMPILER aarch64-none-elf-as)
set(CMAKE_OBJCOPY aarch64-none-elf-objcopy)

add_executable(kernel.elf
    main.c
    boot.S
)

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
