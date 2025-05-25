add_executable(${PROJECT_NAME} main.c)

set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_DEPENDS "${LINKER_SCRIPT}")

target_link_options(${PROJECT_NAME} PRIVATE
 	-T${LINKER_SCRIPT}
	-specs=nano.specs
	-lm
	-lnosys
	-Wl,-Map=${PROJECT_NAME}.map,--cref
	-Wl,--gc-sections
    )

target_link_libraries(${PROJECT_NAME}
					PUBLIC
					system)

set(ELF_FILE $<TARGET_FILE:${PROJECT_NAME}>)
set(BIN_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin")
set(HEX_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary "${ELF_FILE}" "${BIN_FILE}"
    COMMAND ${CMAKE_OBJCOPY} -O ihex "${ELF_FILE}" "${HEX_FILE}"
    COMMAND ${CMAKE_SIZE_UTIL} -B "${ELF_FILE}"
    COMMENT "Generating .bin, .hex and displaying size after build"
)
