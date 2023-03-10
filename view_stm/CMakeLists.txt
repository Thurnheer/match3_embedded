cmake_minimum_required(VERSION 3.18.4)

project(View VERSION 1.0)
              

add_library(${PROJECT_NAME} INTERFACE)
add_library(match3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(${PROJECT_NAME}
    SYSTEM
    INTERFACE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
    #project_warnings
    project_options
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
)

