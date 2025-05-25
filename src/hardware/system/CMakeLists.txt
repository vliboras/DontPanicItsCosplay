add_library(system OBJECT startup.s)
target_include_directories(system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/lpc2292.ld" CACHE FILEPATH "Linker script file")