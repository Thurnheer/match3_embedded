cmake_minimum_required(VERSION 3.18.4)

project(Match3_stm VERSION 1.0)
              
if(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_PROCESSOR MATCHES STM32H735)

add_executable(${PROJECT_NAME})

generate_elf(${PROJECT_NAME})

add_subdirectory(Drivers)
add_subdirectory(Middlewares)
add_subdirectory(TouchGFX)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/time.cpp
)

target_link_libraries_system(${PROJECT_NAME}
    PRIVATE
    match3::Drivers
    match3::Middlewares
    match3::Touchgfx
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    match3::Model
    match3::Controller
    match3::View
    project_options
    project_warnings
)

endif()

