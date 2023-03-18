cmake_minimum_required(VERSION 3.18.4)

project(Drivers VERSION 1.0 LANGUAGES ASM C CXX)
              

add_library(${PROJECT_NAME} OBJECT)
add_library(match3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/stm/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32H7xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/STM32H735G-DK
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/common
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/s70kl1281
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/ft5336
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/mx25lm51245g
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/STM32H735G-DK
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    project_options
    match3::Core
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/stm/Inc/nema_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm/Inc/nema_hal_threadx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm/Src/stm32h7xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm/Src/system_stm32h7xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm/Src/stm32h7xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm/Src/freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm/Src/stm32h7xx_hal_timebase_tim.c
    "$<$<CXX_COMPILER_ID:GNU>:${CMAKE_CURRENT_SOURCE_DIR}/stm/Src/startup_stm32h735igkx.s>"
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/STM32H735G-DK/stm32h735g_discovery_ts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/STM32H735G-DK/stm32h735g_discovery_bus.c
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/STM32H735G-DK/stm32h735g_discovery.c
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/s70kl1281/s70kl1281.c
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/mx25lm51245g/mx25lm51245g.c
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/ft5336/ft5336_reg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/ft5336/ft5336.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ospi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma2d.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
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

endif()

