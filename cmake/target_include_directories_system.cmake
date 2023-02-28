function(target_include_directories_system target scope)
    set(libs ${ARGN})
    foreach(lib ${libs})
        get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
        target_include_directories(${target} SYSTEM ${scope} ${lib_include_dirs})
    endforeach(lib)
endfunction(target_include_directories_system)

