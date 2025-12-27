add_executable(kernel.elf
    main.c
    boot.S
    entry.S
    driver.c
    irq.c
    memory.c
    log.c
    drivers/irq/arm/gicv3/gicv3.c
    drivers/tty/serial/arm/pl011/pl011.c
)

target_include_directories(kernel.elf PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(kernel.elf PRIVATE fdt libc)

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
