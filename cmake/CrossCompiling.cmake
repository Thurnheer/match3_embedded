function(set_crosscompiling project_name)

if(EMSCRIPTEN)

    target_compile_options(${project_name}
        INTERFACE
        "-sUSE_SDL=2"
        "-sUSE_SDL_IMAGE=2"
        "-sUSE_SDL_TTF=2"
    )

    target_link_options(${project_name}
        INTERFACE
        "--emrun"
        "-sUSE_SDL=2"
        "-sUSE_SDL_IMAGE=2"
        "-sUSE_SDL_TTF=2"
        "--preload-file ${CMAKE_BINARY_DIR}/data"
        "--use-preload-plugins"
        "--shell-file ${SHELL_FILE}"
        "-sSINGLE_FILE"
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")

    target_compile_options(${project_name}
        INTERFACE
        "--target=armv7m-none-eabi"
        "--sysroot=/usr/arm-none-eabi"
        "--gcc-toolchain=/usr/arm-none-eabi/bin"
        "-c"
        "-MMD"
        "-MP"
        "-MF"
        "-MT"
        "-ffunction-sections"
        "-fdata-sections"
        "-I/usr/arm-none-eabi/include/c++/12.2.0"
        "-I/usr/arm-none-eabi/include/c++/12.2.0/arm-none-eabi/thumb/v7e-m+fp/softfp"
        "-mfloat-abi=hard"
        "-pipe"
        "-fmessage-length=0"
        "-mcpu=cortex-m4"
        "-mfpu=fpv4-sp-d16"
        "-mthumb"
        "-gdwarf-2"
        "-fno-exceptions"
        "-O0"
        "$<$<CXX_COMPILER_ID:Clang>:-fno-rtti>"
        "$<$<CXX_COMPILER_ID:Clang>:-nostdlib>"
        "-fuse-ld=${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-ld"
        "--verbose"
        "--rtlib=libgcc"
        "--stdlib=libstdc++"
        "-fsized-deallocation"
    )

    target_link_options(${project_name}
        INTERFACE
        "-T${LINKER_SCRIPT}"
        "-nostartfiles"
        "-Xlinker"
        "--gc-sections"
        "--specs=nano.specs"
        "--specs=nosys.specs"
        "-Wl,-Map,${PROJECT_NAME}.map"
        "-mfloat-abi=softfp"
        "-mcpu=cortex-m4"
        "-mfpu=fpv4-sp-d16"
        "-mthumb"
        "-gdwarf-2"
        "-lm"
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    target_compile_options(${project_name}
        INTERFACE
        "$<$<COMPILE_LANGUAGE:ASM>:-c>"
        "$<$<COMPILE_LANGUAGE:ASM>:-x>"
        "$<$<COMPILE_LANGUAGE:ASM>:assembler-with-cpp>"
        "$<$<COMPILE_LANGUAGE:ASM>:-Wa,-adhlns=${PROJECT_NAME}.lst>"
        "--specs=nano.specs"
        "-ffunction-sections"
        "-fdata-sections"
        "-mcpu=cortex-m7"
        "-mfloat-abi=hard"
        "-mfpu=fpv5-d16"
        "-mthumb"
        #"$<$<CXX_COMPILER_ID:GNU>:-fno-exceptions>" TODO reenable this -> ranges v3 depends on it
        "$<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>"
        "$<$<COMPILE_LANGUAGE:CXX>:-fcheck-new>"
        "$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>"
        "--specs=nano.specs"
        "-fno-unwind-tables"
        "$<$<CONFIG:Debug>:-O0>"
        "$<$<CONFIG:MinSizeRel>:-Oz>" # when gcc version >= 11.2
    )

    target_link_options(${project_name}
        INTERFACE
        "-T${LINKER_SCRIPT}"
        "-Wl,--gc-sections"
        "-Wl,-static"
        "--specs=nano.specs"
        "--specs=nosys.specs"
        "-Wl,-Map,${PROJECT_NAME}.map"
        "-mfloat-abi=hard"
        "-mcpu=cortex-m7"
        "-mfpu=fpv5-d16"
        "-mthumb"
        "-Wl,--no-warn-rwx-segment"
        "-lc"
        "-lm"
        "-lstdc++"
        "-lsupc++"
    )

else()
    message(AUTHOR_WARNING "No compiler options set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

endfunction()
