set(target "ft32f0")

version_target(${target})
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config/version.h)

file(GLOB SDK_SOURCE_FILES
    ${LIB_DIR}/src/*.c

    ${DEV_DIR}/ft_lib/gpio/ft_gpio.c
    ${DEV_DIR}/ft_lib/i2c/ft_i2c.c
    ${DEV_DIR}/ft_lib/deprecated/ft_delay.c
    ${DEV_DIR}/ft_lib/timer/ft_timer.c

    ${DEV_DIR}/middle_api/mid_bk953x/mid_bk953x.c
    ${DEV_DIR}/middle_api/tft_8080/tft_8080.c
    ${DEV_DIR}/hardware/st7789/st7789.c
)


set(SDK_INCLUDE_DIRS
    ${FT_SDK_ROOT}/components/device
    ${FT_SDK_ROOT}/components/toolchain
    ${FT_SDK_ROOT}/components/toolchain/CMSIS
    ${FT_SDK_ROOT}/components/toolchain/CMSIS/Include

    ${LIB_DIR}/inc

    ${DEV_DIR}
    ${DEV_DIR}/ft_lib
    ${DEV_DIR}/ft_lib/gpio
    ${DEV_DIR}/ft_lib/i2c
    ${DEV_DIR}/ft_lib/deprecated
    ${DEV_DIR}/ft_lib/timer

    ${DEV_DIR}/hardware 
    ${DEV_DIR}/hardware/st7789
    ${DEV_DIR}/middle_api 
    ${DEV_DIR}/middle_api/mid_bk953x
    ${DEV_DIR}/middle_api/queue
    ${DEV_DIR}/middle_api/tft_8080

)


# file(GLOB APP_SOURCE_FILES
#     ${EXAMPLE_DIR}/USART/USART_Printf/main.c
#     ${EXAMPLE_DIR}/USART/USART_Printf/ft32f0XX_it.c
# )

# set(APP_INCLUDE_DIRS
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_CURRENT_SOURCE_DIR}/config
#     ${EXAMPLE_DIR}/USART/USART_Printf
    
# )

file(GLOB APP_SOURCE_FILES
    ${EXAMPLE_DIR}/USART/USART_HyperTerminalInterrupt/main.c
    ${EXAMPLE_DIR}/USART/USART_HyperTerminalInterrupt/ft32f0XX_it.c
)

set(APP_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${EXAMPLE_DIR}/USART/USART_HyperTerminalInterrupt
    
)

set(USER_DEFINITIONS
    -DPROJECT_NAME="${PROJECT_NAME}"
    -DTARGET_NAME="${target}"
    -DDEVICE_TYPE="ft32f0"
    -D${CONFIG_BUILD_TYPE}
    -DVERSION_BUILD_HASH="${${target}_VERSION}_${BUILD_HASH}"
    -DFACTORY_MODE=1
    ${FT32_DEFINES}
    -DFT32
    -DUSE_STDPERIPH_DRIVER
    -DUSE_DEFAULT_TIMEOUT_CALLBACK
    
)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/debug/debug_config_custom.h)
   set(USER_DEFINITIONS ${USER_DEFINITIONS} -DDEBUG_CONFIG_CUSTOM)
endif()

if(CONFIG_TRACE_ENABLE)
    set(USER_DEFINITIONS ${USER_DEFINITIONS}
        -DTRACE_ENABLE
        -DTRACE_LEVEL_DEFAULT=TRACE_LEVEL_${CONFIG_TRACE_LEVEL}
        -DNRF_LOG_USES_${CONFIG_TRACE_BACKEND}=1
        -DSHELL_UART_TX_BUF_SIZE=1024
    )
endif()

add_executable(${target}
    ${FT32_SOURCE_FILES}
    ${APP_SOURCE_FILES}
    ${SDK_SOURCE_FILES}
    ${BOARD_SOURCE_FILES}
)



target_include_directories(${target} PUBLIC
    ${FT32_INCLUDE_DIRS}
    ${APP_INCLUDE_DIRS}
    ${SDK_INCLUDE_DIRS}
)

get_property(PROJECT_LIBS_PROPERTY GLOBAL PROPERTY PROJECT_LIBS)

target_link_libraries(${target} ${PROJECT_LIBS_PROPERTY})

set_target_link_options(${target}
    ${CMAKE_CURRENT_SOURCE_DIR}/linker/ft32f0)

target_compile_definitions(${target} PUBLIC
    ${USER_DEFINITIONS}
)

create_hex(${target})
add_flash_target(${target})

# set(IMAGE_OUT_DIR ${target}_${${target}_VERSION}_${BUILD_HASH})
# add_fw_target(${target} FALSE FALSE ${IMAGE_OUT_DIR})




