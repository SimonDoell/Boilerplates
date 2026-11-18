cmake_minimum_required(VERSION 3.16)

project(main LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main
    src/main.c
)

target_compile_options(main PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wformat=2
    -Wnull-dereference
    -Wdouble-promotion
    -Wstrict-prototypes
    -Wmissing-prototypes
    -Wold-style-definition
    -Wundef
    -Wcast-qual
    -Wwrite-strings
    -fanalyzer

    -Wno-unused
)

target_compile_options(main PRIVATE
    $<$<CONFIG:Debug>:
        -g3
        -O1
        -fno-omit-frame-pointer
        -fsanitize=address,undefined
        -fno-sanitize=leak
        -fno-sanitize-recover=all
    >
)

target_link_options(main PRIVATE
    $<$<CONFIG:Debug>:
        -fsanitize=address,undefined
        -fno-sanitize=leak
        -fno-sanitize-recover=all
    >
)

target_link_libraries(main PRIVATE m)