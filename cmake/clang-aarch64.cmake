set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_FLAGS "-target aarch64-none-elf ${CMAKE_C_FLAGS}")
set(CMAKE_ASM_FLAGS "-target aarch64-none-elf ${CMAKE_ASM_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-target aarch64-none-elf -fuse-ld=lld ${CMAKE_EXE_LINKER_FLAGS}")
