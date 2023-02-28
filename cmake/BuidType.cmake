function(setBuildType)
    
    set(default_build_type "Debug")

    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
        set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose build type" FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel"
            "RelWithDebInfo")
    endif()

    # Modify compile flags to change optimization level from O3 to O2
    string(REGEX REPLACE "([\\/\\-]O)3" "\\12" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE "([\\/\\-]O)3" "\\12" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    # string(REGEX REPLACE "([\\/\\-]O)3" "\\1s" CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}")
#    string(REGEX REPLACE "([\\/\\-]O)3" "\\1s" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

endfunction()
