cmake_minimum_required(VERSION 3.18.4)

project(Touchgfx VERSION 1.0 LANGUAGES ASM C CXX )
              

add_library(${PROJECT_NAME} STATIC)
add_library(match3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/App
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/gui_generated/include
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/include
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/include
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/texts/include
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/videos/include
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/include
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/target/generated
    ${CMAKE_CURRENT_SOURCE_DIR}/target
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/target/STM32TouchController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target/TouchGFXGPIO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target/generated/TouchGFXConfiguration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target/generated/TouchGFXGeneratedHAL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target/generated/OSWrappers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target/generated/STM32DMA.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target/CortexMMCUInstrumentation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target/TouchGFXHAL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App/app_touchgfx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/gui_generated/src/common/FrontendApplicationBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/gui_generated/src/screen1_screen/Screen1ViewBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/src/SVGDatabase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/src/BitmapDatabase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/src/image_img3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/src/image_img4.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/src/image_img2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/src/image_img1.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/src/image_img5.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/images/src/image_match.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/texts/src/LanguageGb.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/texts/src/Texts.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/texts/src/TypedTextDatabase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/Table_verdana_20_4bpp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/Kerning_verdana_40_4bpp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/GeneratedFont.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/Table_verdana_40_4bpp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/Kerning_verdana_20_4bpp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/FontCache.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/Table_verdana_10_4bpp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/ApplicationFontProvider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/CachedFont.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/UnmappedDataFont.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/fonts/src/Kerning_verdana_10_4bpp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/src/common/FrontendApplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/src/model/Model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/src/screen1_screen/Screen1View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/src/screen1_screen/Screen1Presenter.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    match3::Middlewares
    match3::Drivers
    project_options
    PRIVATE
    #project_warnings
)
