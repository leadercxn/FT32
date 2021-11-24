set(target "FT32F0XX")

version_target(${target})
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config/version.h)

file(GLOB SDK_SOURCE_FILES
    ${LIB_DIR}/src/*.c

    ${DEV_DIR}/ft_lib/adc/*.c
    ${DEV_DIR}/ft_lib/common/*.c
    ${DEV_DIR}/ft_lib/exit/*.c
    ${DEV_DIR}/ft_lib/gpio/*.c
    ${DEV_DIR}/ft_lib/i2c/*.c
    ${DEV_DIR}/ft_lib/spi/*.c
    ${DEV_DIR}/ft_lib/timer/*.c
    ${DEV_DIR}/ft_lib/timer_pwm/*.c
    ${DEV_DIR}/ft_lib/flash/*.c

    ${DEV_DIR}/middle_api/adc/*.c
    ${DEV_DIR}/middle_api/delay/*.c
    ${DEV_DIR}/middle_api/ir/*.c

    ${DEV_DIR}/middle_api/mid_bk953x/*.c
    ${DEV_DIR}/middle_api/mid_flash/*.c
    ${DEV_DIR}/middle_api/mid_gpio/*.c
    ${DEV_DIR}/middle_api/mid_timer/*.c

    # ${DEV_DIR}/middle_api/pwm/*.c
    ${DEV_DIR}/middle_api/queue/*.c
    ${DEV_DIR}/middle_api/tft_8080/*.c

    ${DEV_DIR}/hardware/bk953x/*.c
    ${DEV_DIR}/hardware/st7789/*.c

    ${DEV_DIR}/third_lib/app_timer/*.c
    # ${DEV_DIR}/third_lib/app_error/*.c
    ${DEV_DIR}/third_lib/app_scheduler/*.c
)


set(SDK_INCLUDE_DIRS
    ${FT_SDK_ROOT}/components/device
    ${FT_SDK_ROOT}/components/toolchain
    ${FT_SDK_ROOT}/components/toolchain/CMSIS
    ${FT_SDK_ROOT}/components/toolchain/CMSIS/Include

    ${LIB_DIR}/inc

    ${DEV_DIR}
    ${DEV_DIR}/ft_lib
    ${DEV_DIR}/ft_lib/adc
    ${DEV_DIR}/ft_lib/common
    ${DEV_DIR}/ft_lib/exit
    ${DEV_DIR}/ft_lib/gpio
    ${DEV_DIR}/ft_lib/i2c
    ${DEV_DIR}/ft_lib/spi
    ${DEV_DIR}/ft_lib/timer
    ${DEV_DIR}/ft_lib/timer_pwm
    ${DEV_DIR}/ft_lib/flash

    ${DEV_DIR}/middle_api
    ${DEV_DIR}/middle_api/adc
    ${DEV_DIR}/middle_api/delay
    ${DEV_DIR}/middle_api/ir
    ${DEV_DIR}/middle_api/mid_bk953x
    ${DEV_DIR}/middle_api/mid_flash
    ${DEV_DIR}/middle_api/mid_gpio
    ${DEV_DIR}/middle_api/mid_timer

    ${DEV_DIR}/middle_api/pwm
    ${DEV_DIR}/middle_api/queue
    ${DEV_DIR}/middle_api/tft_8080

    ${DEV_DIR}/hardware 
    ${DEV_DIR}/hardware/bk953x
    ${DEV_DIR}/hardware/st7789

    ${DEV_DIR}/third_lib/
    ${DEV_DIR}/third_lib/app_scheduler
    ${DEV_DIR}/third_lib/app_timer
    ${DEV_DIR}/third_lib/app_error
)


file(GLOB APP_SOURCE_FILES

    # ${CMAKE_CURRENT_SOURCE_DIR}/gpio/main.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/gpio/ft32f0xx_it.c

    ${TEST_DIR}/main.c
    ${TEST_DIR}/ft32f0XX_it.c
    ${TEST_DIR}/app/*.c
    ${CMAKE_SOURCE_DIR}/apps/app_common/trace/*.c
    ${CMAKE_SOURCE_DIR}/apps/app_common/usart/*.c
    ${CMAKE_SOURCE_DIR}/apps/app_common/LetterShell/*.c

)

set(APP_INCLUDE_DIRS
    ${TEST_DIR}
    ${TEST_DIR}/app

    ${CMAKE_CURRENT_SOURCE_DIR}
    # ${CMAKE_CURRENT_SOURCE_DIR}/config
    # ${CMAKE_CURRENT_SOURCE_DIR}/gpio

    ${CMAKE_SOURCE_DIR}/apps/app_common
    ${CMAKE_SOURCE_DIR}/apps/app_common/trace
    ${CMAKE_SOURCE_DIR}/apps/app_common/usart
    ${CMAKE_SOURCE_DIR}/apps/app_common/LetterShell
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




