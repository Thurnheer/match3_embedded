function(generate_elf project_name)


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

	add_custom_command(TARGET ${project_name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${project_name} ${project_name}.elf)

    add_custom_command(TARGET ${project_name} POST_BUILD COMMAND arm-none-eabi-size ${project_name}.elf)
	
    add_custom_command(TARGET ${project_name} POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${project_name} ${project_name}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${project_name} ${project_name}.bin
    )

endif()

endfunction()

