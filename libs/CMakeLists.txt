add_library(libc STATIC
    string/memchr.c
    string/memcmp.c
    string/memcpy.c
    string/memmove.c
    string/memrchr.c
    string/memset.c
    string/strcmp.c
    string/strlen.c
    string/strncmp.c
    string/strnlen.c
    string/strrchr.c
)

target_include_directories(libc SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
