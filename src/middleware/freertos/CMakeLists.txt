add_library(freertos_config INTERFACE)

target_compile_definitions(freertos_config INTERFACE ${mcu_def} ${board_def})
target_compile_options(freertos_config INTERFACE ${mcu_options} ${compiler_options})

target_link_libraries(freertos_config INTERFACE soc)

target_include_directories(freertos_config
    SYSTEM
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)

set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
if (CMAKE_CROSSCOMPILING)
  set(FREERTOS_PORT "GCC_ARM7_LPC2000" CACHE STRING "" FORCE)
endif()

add_library(freertos_hooks STATIC freertos_hooks.c)
target_link_libraries(freertos_hooks PRIVATE freertos_kernel)
target_include_directories(freertos_hooks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(FreeRTOS-Kernel)