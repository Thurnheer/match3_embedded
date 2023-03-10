function(set_crosscompiling project_name)

if(CMAKE_CXX_COMPILER_ID MATCHES IAR)

    target_compile_definitions(${project_name} INTERFACE
    USE_ASM=1
    XMC4x00
    XMC4700_F144x2048
    XMC_ASSERT_ENABLE
    __IAR_SYSTEM_ICC__
    )

    target_compile_options(${project_name} INTERFACE
    $<$<COMPILE_LANGUAGE:ASM>:-s+>
    $<$<COMPILE_LANGUAGE:ASM>:-M<$<ANGLE-R>>
    $<$<COMPILE_LANGUAGE:ASM>:-w+>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_cse>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_unroll>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_inline>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_code_motion>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_tbaa>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_clustering>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_scheduling>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--endian=little>
    --cpu Cortex-M4
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_path_in_file_macros>
    #--diag_suppress Pe811
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--diag_suppress Pe186>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:-e>
    $<$<COMPILE_LANGUAGE:ASM>:--fpu VFPv4_sp>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--fpu=VFPv4_sp>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--dlib_config normal>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:-On>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--c++>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_exceptions>
    $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:--no_rtti>
    )

    target_link_libraries(${project_name} INTERFACE ${TOOLKIT_DIR}/lib/sh7Mx_l.a)
    
    list(APPEND LINK_OPTIONS
    --config ${LINKER_SCRIPT}
    "SHELL:--redirect malloc=_not_implemented"
    "SHELL:--redirect free=_not_implemented"
    "SHELL:--redirect realloc=_not_implemented"
    "SHELL:--redirect calloc=_not_implemented"
    --semihosting
    --entry __iar_program_start
    --place_holder __checksum,4,.checksum,1
    "SHELL:--define_symbol __checksum_begin=0x8020000"
    "SHELL:--define_symbol __checksum_end=0x81bffff"
    "SHELL:--redirect __iar_sh_stdout=__iar_sh_stdout_swo"
    --no_exceptions
    --vfe
    --text_out locale
    --no_free_heap
    )
    target_link_options(${project_name} INTERFACE
    ${LINK_OPTIONS}
    )

elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")

    target_compile_options(${project_name}
        INTERFACE
        "--target=armv7m-none-eabi"
        "--sysroot=/usr/arm-none-eabi"
        #"--gcc-install-dir=${CMAKE_GCC_TOOLCHAIN}"
        "--gcc-toolchain=/usr/arm-none-eabi/bin"
        "-c"
        "-MMD"
        "-MP"
        "-MF"
        "-MT"
        "-ffunction-sections"
        "-fdata-sections"
        #"-I/usr/arm-none-eabi/include"
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
        #"$<$<CXX_COMPILER_ID:Clang>:-nodefaultlibs>"
    )

    target_link_options(${project_name}
        INTERFACE
        "$<$<CXX_COMPILER_ID:Clang>:-T${LINKER_SCRIPT}>"
        #"--target=armv7m-none-eabi"
        #"--sysroot=/usr/arm-none-eabi"
        #"--gcc-toolchain=${CMAKE_GCC_TOOLCHAIN}"
        #"-L/usr/arm-none-eabi/lib/thumb/v7e-m+fp/hard /usr/lib/gcc/arm-none-eabi/12.2.0/thumb/v7e-m+fp/hard/libstdc++.a"
        #"-L/usr/arm-none-eabi/lib/thumb/v7e-m+fp/hard /usr/lib/gcc/arm-none-eabi/12.2.0/thumb/v7e-m+fp/hard/libc.a"
        "$<$<CXX_COMPILER_ID:Clang>:-nostartfiles>"
        "$<$<CXX_COMPILER_ID:Clang>:-Xlinker>"
        "$<$<CXX_COMPILER_ID:Clang>:--gc-sections>"
        "$<$<CXX_COMPILER_ID:Clang>:--specs=nano.specs>"
        "$<$<CXX_COMPILER_ID:Clang>:--specs=nosys.specs>"
        "$<$<CXX_COMPILER_ID:Clang>:-Wl,-Map,${PROJECT_NAME}.map>"
        "$<$<CXX_COMPILER_ID:Clang>:-mfloat-abi=softfp>"
        "$<$<CXX_COMPILER_ID:Clang>:-mcpu=cortex-m4>"
        "$<$<CXX_COMPILER_ID:Clang>:-mfpu=fpv4-sp-d16>"
        "$<$<CXX_COMPILER_ID:Clang>:-mthumb>"
        "$<$<CXX_COMPILER_ID:Clang>:-gdwarf-2>"
        "$<$<CXX_COMPILER_ID:Clang>:-lm>"
        #"$<$<CXX_COMPILER_ID:Clang>:-v>"
        #"-fuse-ld=ld"
        #"--rtlib=libgcc"
        #"$<$<CXX_COMPILER_ID:Clang>:-nodefaultlibs>"
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    target_compile_options(${project_name}
        INTERFACE
        "$<$<COMPILE_LANGUAGE:ASM>:-c>"
        "$<$<COMPILE_LANGUAGE:ASM>:-x>"
        "$<$<COMPILE_LANGUAGE:ASM>:assembler-with-cpp>"
        "$<$<CXX_COMPILER_ID:GNU>:--specs=nano.specs>"
        "$<$<COMPILE_LANGUAGE:ASM>:-Wa,-adhlns=${PROJECT_NAME}.lst>"
        #"$<$<CXX_COMPILER_ID:GNU>:-MMD>"
        #"$<$<CXX_COMPILER_ID:GNU>:-MP>"
        #"$<$<CXX_COMPILER_ID:GNU>:-MF>"
        #"$<$<CXX_COMPILER_ID:GNU>:-MT>"
        "$<$<CXX_COMPILER_ID:GNU>:-ffunction-sections>"
        #"$<$<CXX_COMPILER_ID:GNU>:-fdata-sections>"
        "$<$<CXX_COMPILER_ID:GNU>:-mfloat-abi=hard>"
        #"$<$<CXX_COMPILER_ID:GNU>:-pipe>"
        #"$<$<CXX_COMPILER_ID:GNU>:-fmessage-length=0>"
        "$<$<CXX_COMPILER_ID:GNU>:-mcpu=cortex-m7>"
        "$<$<CXX_COMPILER_ID:GNU>:-mfpu=fpv5-d16>"
        "$<$<CXX_COMPILER_ID:GNU>:-mthumb>"
        #"$<$<CXX_COMPILER_ID:GNU>:-gdwarf-2>"
        #"$<$<CXX_COMPILER_ID:GNU>:-fno-exceptions>" TODO reenable this -> ranges v3 depends on it
        "$<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>"
        "$<$<COMPILE_LANGUAGE:CXX>:-fcheck-new>"
        "$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>"
        "$<$<CXX_COMPILER_ID:GNU>:--specs=nano.specs>"
        #"$<$<COMPILE_LANGUAGE:CXX>:-ffreestanding>"
        "$<$<CXX_COMPILER_ID:GNU>:-fno-unwind-tables>"
        #"$<$<CXX_COMPILER_ID:GNU>:-nostdlib>"
        "$<$<CONFIG:Debug>:-Og>"
        "$<$<COMPILE_LANGUAGE:CXX>:-fcoroutines>"
        "$<$<CONFIG:MinSizeRel>:-Oz>" # when gcc version >= 11.2
    )

    target_link_options(${project_name}
        INTERFACE
        "$<$<CXX_COMPILER_ID:GNU>:-T${LINKER_SCRIPT}>"
        #"$<$<CXX_COMPILER_ID:GNU>:-Xlinker>"
        "$<$<CXX_COMPILER_ID:GNU>:-Wl,--gc-sections>"
        "$<$<CXX_COMPILER_ID:GNU>:-Wl,-static>"
        "$<$<CXX_COMPILER_ID:GNU>:--specs=nano.specs>"
        "$<$<CXX_COMPILER_ID:GNU>:--specs=nosys.specs>"
        "$<$<CXX_COMPILER_ID:GNU>:-Wl,-Map,${PROJECT_NAME}.map>"
        "$<$<CXX_COMPILER_ID:GNU>:-mfloat-abi=hard>"
        "$<$<CXX_COMPILER_ID:GNU>:-mcpu=cortex-m7>"
        "$<$<CXX_COMPILER_ID:GNU>:-mfpu=fpv5-d16>"
        "$<$<CXX_COMPILER_ID:GNU>:-mthumb>"
        #"$<$<CXX_COMPILER_ID:GNU>:-gdwarf-2>"
        "-Wl,--no-warn-rwx-segment"
        "$<$<CXX_COMPILER_ID:GNU>:-lc>"
        "$<$<CXX_COMPILER_ID:GNU>:-lm>"
        "$<$<CXX_COMPILER_ID:GNU>:-lstdc++>"
        "$<$<CXX_COMPILER_ID:GNU>:-lsupc++>"
    )

else()
    message(AUTHOR_WARNING "No compiler options set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

  #target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})

endfunction()
