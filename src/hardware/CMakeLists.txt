add_library(interrupts OBJECT interrupts.c)
target_include_directories(interrupts PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(interrupts PUBLIC soc)

add_subdirectory(bsp)
add_subdirectory(drivers)
add_subdirectory(mcu_hal)
add_subdirectory(system)