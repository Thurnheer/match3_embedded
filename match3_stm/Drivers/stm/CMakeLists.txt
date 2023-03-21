cmake_minimum_required(VERSION 3.18.4)

project(Stm VERSION 1.0 LANGUAGES ASM C CXX)
              
add_library(${PROJECT_NAME} OBJECT) # object keyword needed for the interrupt functions
add_library(match3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    match3::Drivers
    project_options
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc/nema_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc/nema_hal_threadx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32h7xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/system_stm32h7xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32h7xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32h7xx_hal_timebase_tim.c
    "$<$<CXX_COMPILER_ID:GNU>:${CMAKE_CURRENT_SOURCE_DIR}/Src/startup_stm32h735igkx.s>"
)

