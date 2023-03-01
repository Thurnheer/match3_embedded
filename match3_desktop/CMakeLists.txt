cmake_minimum_required(VERSION 3.18.4)

project(Desktop VERSION 1.0)
              
add_executable(${PROJECT_NAME})

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
  include(FindPkgConfig)
  PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
  PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
  PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    match3::View
    match3::Model
    match3::Controller
    match3::Config
)

target_include_directories_system(${PROJECT_NAME}
    PRIVATE
    Boost.DI
)

target_sources(${PROJECT_NAME}
    PRIVATE
    desktop/main.cpp
)

target_include_directories(${PROJECT_NAME}
    SYSTEM
    PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    project_warnings
    project_options
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)


