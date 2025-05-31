add_library(bsp OBJECT bsp.c)
target_include_directories(bsp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(bsp PUBLIC soc uart system_clock)