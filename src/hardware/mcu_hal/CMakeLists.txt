add_library(uart STATIC uart.c)
target_include_directories(uart PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(uart PUBLIC soc)

add_library(system_clock STATIC system_clock.c)
target_include_directories(system_clock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(system_clock PUBLIC soc)