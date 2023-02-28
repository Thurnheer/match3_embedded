function(fetch_dependencies)

Include(FetchContent)

if(ENABLE_TESTING)
    set(CATCH_BUILD_STATIC_LIBRARY TRUE CACHE INTERNAL "enable Catch2WithMain target")

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY git@github.com:catchorg/Catch2.git
        GIT_TAG v2.13.7
    )

    FetchContent_MakeAvailable(Catch2)

    get_target_property(catch_ifc_incl Catch2::Catch2 INTERFACE_INCLUDE_DIRECTORIES)
    set_target_properties(Catch2WithMain PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
        "${catch_ifc_incl}")

# location of catch_discover_tests for ctest
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)

    include(Catch)

    FetchContent_Declare(
        Trompeloeil
        GIT_REPOSITORY git@github.com:rollbear/trompeloeil.git
        GIT_TAG v43
    )

    FetchContent_MakeAvailable(Trompeloeil)


endif()


option(SML_BUILD_BENCHMARKS OFF)
option(SML_BUILD_EXAMPLES OFF)
option(SML_BUILD_TESTS OFF)
option(SML_USE_EXCEPTIONS OFF)

FetchContent_Declare(
    sml
    GIT_REPOSITORY git@github.com:boost-ext/sml.git
    GIT_TAG v1.1.6
)

set(SML_BUILD_BENCHMARKS OFF)
set(SML_BUILD_EXAMPLES OFF)
set(SML_BUILD_TESTS OFF)
set(SML_USE_EXCEPTIONS OFF)

FetchContent_MakeAvailable(sml)

FetchContent_Declare(
    DI
    GIT_REPOSITORY git@github.com:boost-ext/di.git
    GIT_TAG v1.2.0
)

FetchContent_MakeAvailable(DI)

FetchContent_Declare(
    range_v3
    GIT_REPOSITORY git@github.com:ericniebler/range-v3.git
    GIT_TAG 0.12.0
)

FetchContent_MakeAvailable(range_v3)



# SDL only needed on desktops or web
# TODO get SDL or check for it on host

endfunction()

