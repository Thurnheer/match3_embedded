cmake_minimum_required(VERSION 3.18.4)

project(Config VERSION 1.0)
              

add_library(${PROJECT_NAME} INTERFACE)
add_library(match3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

