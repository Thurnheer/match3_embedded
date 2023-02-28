# Iar Toolchain

set(CMAKE_SYSTEM_NAME Generic)

# avoid running the compiler check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_SYSTEM_PROCESSOR arm)

set(IAR_INSTALL_DIR "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.4")

set(TOOLKIT_DIR "${IAR_INSTALL_DIR}/${CMAKE_SYSTEM_PROCESSOR}")

set(ENV{PATH} "${TOOLKIT_DIR}/bin;$ENV{PATH}")

set(CMAKE_C_COMPILER "icc${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_CXX_COMPILER "icc${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_ASM_COMPILER "iasm${CMAKE_SYSTEM_PROCESSOR}")

set(LINKER_SCRIPT "${PROJECT_SOURCE_DIR}/Application\.EZ/anterior/anterior/iar_linker_script.icf")
