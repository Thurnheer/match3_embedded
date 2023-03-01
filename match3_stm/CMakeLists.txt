cmake_minimum_required(VERSION 3.18.4)

project(View VERSION 1.0)
              

add_library(${PROJECT_NAME} INTERFACE)
add_library(match3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
)

if(ENABLE_TESTING)

    # compile with the unit test define which enables test functions (bad practice)
    # for the normal lib

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _UNITTEST
    ) 

    add_executable(${PROJECT_NAME}_unittest)

    target_sources(${PROJECT_NAME}_unittest
        PRIVATE
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

