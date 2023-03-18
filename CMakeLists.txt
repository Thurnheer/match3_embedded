#
# Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 3.20)

project(Match3)

add_library(project_warnings INTERFACE)


include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/StaticAnalyzers.cmake)
include(cmake/target_link_libraries_system.cmake)
include(cmake/target_include_directories_system.cmake)

option(ENABLE_TESTING "Enable Test Builds" OFF)
option(EXPORT_COMPILE_COMMANDS "Enable compile commands for clang refactoring tool" OFF)

add_library(project_options INTERFACE)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/BuidType.cmake)
setBuildType()

if(EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()


include(cmake/Dependencies.cmake)
fetch_dependencies()

if(CMAKE_CROSSCOMPILING)
    include(cmake/CrossCompiling.cmake)
    set_crosscompiling(project_options)
    include(cmake/GenerateElf.cmake)
endif()

if(ENABLE_TESTING)

    enable_testing()

    include(CTest)

    add_subdirectory(test)

endif()

add_subdirectory(config)
add_subdirectory(core)
add_subdirectory(model)

if(CMAKE_CROSSCOMPILING)
    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES STM32H735)
        add_subdirectory(controller_stm)
        add_subdirectory(view_stm)
        add_subdirectory(match3_stm)
    elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES web)
        add_subdirectory(match3_desktop)
        add_subdirectory(controller_desktop)
        add_subdirectory(view_desktop)
    endif()
else()
    add_subdirectory(match3_desktop)
    add_subdirectory(controller_desktop)
    add_subdirectory(view_desktop)
endif()


