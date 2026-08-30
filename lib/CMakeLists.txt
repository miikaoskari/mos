add_library(libc STATIC
    string/memchr.c
    string/memcmp.c
    string/memmove.c
    string/memrchr.c
    string/strcmp.c
    string/strlen.c
    string/strncmp.c
    string/strnlen.c
    string/strrchr.c
    string/aarch64/memcpy.S
    string/aarch64/memset.S
)

target_include_directories(libc SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/include/miosb
)
