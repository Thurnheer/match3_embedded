# emscripten Toolchain

set(CMAKE_SYSTEM_NAME Generic)

# avoid running the compiler check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER "emcc")
set(CMAKE_CXX_COMPILER "em++")
set(EMSCRIPTEN "emscripten")

set(CMAKE_SYSTEM_PROCESSOR web)

set(SHELL_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/data/template.html")
