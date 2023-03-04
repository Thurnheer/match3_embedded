cmake_minimum_required(VERSION 3.18.4)

project(Controller VERSION 1.0)
              

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
    project_warnings
    project_options
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    match3::Config
    match3::Model
    match3::View
)
target_include_directories_system(${PROJECT_NAME}
    INTERFACE
    sml
    Boost.DI
    range-v3 
)

if(ENABLE_TESTING)

    add_executable(${PROJECT_NAME}_unittest)

    target_sources(${PROJECT_NAME}_unittest
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libcontroller/actions/find_matches.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcontroller/actions/generate_new.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcontroller/actions/scroll_board.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcontroller/actions/destroy_matches.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcontroller/actions/swap_items.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcontroller/actions/drop_item.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcontroller/actions/clear_selected.cpp
    )

    target_link_libraries(${PROJECT_NAME}_unittest PRIVATE
        ${PROJECT_NAME}
        trompeloeil::trompeloeil
        test_common
    )

    target_link_libraries_system(${PROJECT_NAME}_unittest PRIVATE Catch2::Catch2WithMain)

    catch_discover_tests(${PROJECT_NAME}_unittest
        TEST_PREFIX
        "unittests.${PROJECT_NAME}."
        -s
        --reporter=xml
        --out=tests.xml
    )

#add_subdirectory(tests)

endif()

