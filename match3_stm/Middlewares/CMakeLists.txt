cmake_minimum_required(VERSION 3.18.4)

project(Middlewares VERSION 1.0)
              
add_library(${PROJECT_NAME} STATIC)
add_library(match3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/lib/core/cortex_m7/gcc")
set(float-abi-hard "${LIB_PATH}/libtouchgfx-float-abi-hard.a")
#set(touchgfx "${LIB_PATH}/libtouchgfx.a")

message("${CMAKE_CURRENT_SOURCE_DIR}/${LIB_PATH}")
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    match3::Drivers
    project_options
    ${float-abi-hard}
    #${touchgfx}
    #project_warnings
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/os/OSWrappers_cmsis.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/os/OSWrappers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/clock/AnalogClock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/clock/DigitalClock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/clock/AbstractClock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/progress_indicators/CircleProgress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/progress_indicators/AbstractDirectionProgress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/progress_indicators/LineProgress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/progress_indicators/AbstractProgressIndicator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/progress_indicators/BoxProgress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/progress_indicators/TextProgress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/progress_indicators/ImageProgress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/SlideMenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/Slider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/ZoomAnimationImage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/ModalWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/SwipeContainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/CacheableContainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/ListLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/ScrollableContainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/Container.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/scrollers/ScrollWheelWithSelectionStyle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/scrollers/ScrollWheel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/scrollers/ScrollBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/scrollers/ScrollWheelBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/scrollers/ScrollList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/containers/scrollers/DrawableList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/AnimationTextureMapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/TiledImage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/Image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/ButtonWithIcon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/ToggleButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/TextureMapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/VideoWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/SnapshotWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/PixelDataWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGB888Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGBA2222Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterGRAY2Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterARGB8888.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/Circle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterABGR2222.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGB565L8Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/CanvasWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterARGB8888Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterARGB2222.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGB565LinearGradient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterXRGB8888L8Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/Canvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterGRAY2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterGRAY4Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/Line.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGB888L8Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterBWBitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterXRGB8888Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/AbstractShape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterXRGB8888.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGB565.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterBGRA2222Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterBGRA2222.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGB565Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterARGB2222Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterABGR2222Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGBA2222.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/CWRVectorRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGB888LinearGradient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterBW.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterGRAY4.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterARGB8888L8Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/canvas/PainterRGB888.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/AbstractButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/ScalableImage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/AnimatedImage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/BoxWithBorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/Button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/Keyboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/TextAreaWithWildcard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/TouchArea.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/SVGImage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/Box.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/Gauge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/TextArea.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/RadioButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/graph/Graph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/ButtonWithLabel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ST/touchgfx/framework/source/touchgfx/widgets/RepeatButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/stream_buffer.c
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

