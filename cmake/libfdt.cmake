include(FetchContent)

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
    ${CMAKE_SOURCE_DIR}/include
)
