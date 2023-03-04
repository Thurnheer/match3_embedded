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
add_library(project_options INTERFACE)


include(cmake/target_link_libraries_system.cmake)
include(cmake/target_include_directories_system.cmake)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/StaticAnalyzers.cmake)

option(ENABLE_TESTING "Enable Test Builds" OFF)
option(EXPORT_COMPILE_COMMANDS "Enable compile commands for clang refactoring tool" OFF)


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
else()
    #add_subdirectory()
    #target_link_libraries(${PROJECT_NAME} INTERFACE )
endif()

if(ENABLE_TESTING)

    enable_testing()

    include(CTest)

    add_subdirectory(test)

endif()
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])*")
  set(CMAKE_CXX_COMPILER_ID "Emscripten")
endif()

add_custom_target(app DEPENDS ${PROJECT_NAME} copy-data-files)
add_custom_target(style)
add_custom_target(copy-data-files ALL COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)
add_custom_command(TARGET style COMMAND find ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/test -iname "*.hpp" -or -iname "*.cpp" | xargs clang-format -i)

find_program(MEMORYCHECK_COMMAND valgrind)
if(MEMORYCHECK_COMMAND-NOTFOUND)
  message("[W] Valgrind not found")
else()
  set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --error-exitcode=1")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Emscripten")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --emrun")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s BINARYEN=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file data --use-preload-plugins")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --shell-file ${CMAKE_SOURCE_DIR}/data/template.html")

  set(WEB "index.html")
  add_custom_target(web DEPENDS ${WEB} copy-data-files)
  add_custom_target(emrun)
  add_custom_command(TARGET emrun COMMAND emrun --port 8080 index.html)
  add_executable(${WEB} src/main.cpp)
else()
    #include(FindPkgConfig)
    #PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    #PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    #PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
endif()

add_subdirectory(config)
add_subdirectory(controller)
add_subdirectory(core)
add_subdirectory(model)
add_subdirectory(view)

if(CMAKE_CROSSCOMPILING)
    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES STM32H735)
        add_subdirectory(match3_stm)
    elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES STM32)
    endif()
else()
    add_subdirectory(match3_desktop)
endif()


