cmake_minimum_required(VERSION 3.28)

project(lpc2292-sdk2
    LANGUAGES ASM C)

include(cmake/lpc2292.cmake)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_definitions(${mcu_def} ${board_def})
add_compile_options(${mcu_options} ${compiler_options})
add_link_options(${mcu_options})

add_subdirectory(src)