#
# Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#

cmake_minimum_required(VERSION 3.18.4)

project(Integrationtests VERSION 1.0)

if(ENABLE_TESTING)
    add_library(test_common INTERFACE)

    target_include_directories(test_common
        SYSTEM
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/common
    )

    add_executable(${PROJECT_NAME})

    target_sources(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/functional_tests/match3_matchl_no_moves_reset.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/functional_tests/match5_out_of_moves.cpp
    )

    target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/functional_tests
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
        test_common
        match3::Controller
        match3::View
        match3::Model
    )

    target_link_libraries_system(${PROJECT_NAME}
        PRIVATE
        Catch2::Catch2WithMain
        trompeloeil::trompeloeil
        Boost.DI
    )

    catch_discover_tests(${PROJECT_NAME}
        TEST_PREFIX
        "integration.${PROJECT_NAME}."
        -s
        --reporter=xml
        --out=tests.xml
    )

endif()

