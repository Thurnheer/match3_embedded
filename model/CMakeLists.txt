cmake_minimum_required(VERSION 3.18.4)

project(Model VERSION 1.0)
              

add_library(${PROJECT_NAME} INTERFACE)
add_library(match3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} INTERFACE
    match3::Config
    match3::Core
)

target_include_directories_system(${PROJECT_NAME}
    INTERFACE
    sml
    Boost.DI
    range-v3 
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

if(ENABLE_TESTING)

    add_executable(${PROJECT_NAME}_unittest)

    target_sources(${PROJECT_NAME}_unittest
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libmodel/board.cpp
    )

    target_link_libraries(${PROJECT_NAME}_unittest PRIVATE
        ${PROJECT_NAME}
        trompeloeil::trompeloeil
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

