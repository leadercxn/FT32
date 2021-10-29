
find_program(OPENOCD openocd)
find_program(MERGEHEX mergehex)

if(NOT OPENOCD)
    message(STATUS "Tool openocd: not set")
endif()

set(DEBUGGER "jlink" CACHE STRING "")
set(DEBUGGER_OPTIONS "jlink" "stlink")
check_in_list(DEBUGGER DEBUGGER_OPTIONS)

if(OPENOCD)
    function(add_flash_target target)
        add_custom_target(flash_${target}
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'reset halt' -c 'flash write_image erase ${target}.hex' -c 'reset halt' -c 'verify_image ${target}.hex' -c 'reset run' -c shutdown
            DEPENDS ${target})
    endfunction(add_flash_target)

    function(add_dfu_target target)
        string(TOUPPER ${target} ${target}_upper)

        set(image_dir ${PROJECT_IMAGE_DIR}/${${target}_VERSION}_${BUILD_HASH})

        set(out_file ${image_dir}/SENSORO_${PROJECT_NAME_UPPER}_${${target}_upper}_DFU_${${target}_VERSION}_${BUILD_HASH}_${BUILD_DATE}.dfu)

        add_custom_target(dfu_${target}
            COMMAND mkdir -p ${image_dir}
            COMMAND ${CMAKE_SOURCE_DIR}/scripts/dfu_pkg_gen.py ${CMAKE_CURRENT_BINARY_DIR}/${target}.bin ${${target}_VERSION} ${out_file}
            DEPENDS ${target})
    endfunction(add_dfu_target)

    function(add_fw_target target)
        string(TOUPPER ${target} ${target}_upper)

        set(image_dir ${PROJECT_IMAGE_DIR}/${${target}_VERSION}_${BUILD_HASH})
        set(bl ${CMAKE_BINARY_DIR}/apps/bootloader/bl.hex)
        set(out_file ${image_dir}/SENSORO_${PROJECT_NAME_UPPER}_${${target}_upper}_FW_${${target}_VERSION}_${BUILD_HASH}_${BUILD_DATE}.hex)

        add_custom_target(fw_${target}
                COMMAND mkdir -p ${image_dir}
                COMMAND ${MERGEHEX} -m ${bl} ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex -o ${out_file}
                DEPENDS ${target})

        add_custom_target(flash_fw_${target}
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'reset halt' -c 'flash write_image erase ${out_file}' -c 'reset halt' -c 'verify_image ${out_file}' -c 'reset run' -c shutdown
            DEPENDS fw_${target})

        add_custom_target(pub_${target}
            COMMAND zip -j -r ${PROJECT_IMAGE_DIR}/SENSORO_${PROJECT_NAME_UPPER}_${${target}_VERSION}_${BUILD_HASH}_${BUILD_DATE}.zip ${image_dir}/* ${CMAKE_SOURCE_DIR}/CHANGELOG.md ${PROJECT_IMAGE_DIR}/external/*
            DEPENDS bl fw_${target} fw_fct dfu_${target})

    endfunction(add_fw_target)

    add_custom_target(reset
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'reset run' -c shutdown)

    add_custom_target(halt
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'halt' -c shutdown)

    add_custom_target(erase
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'halt' -c 'flash erase_address 0x08000000 0x80000' -c shutdown)

    add_custom_target(erase_sec3
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'halt' -c 'flash erase_address 0x0800C000 0x4000' -c shutdown)

    add_custom_target(erase_cfg
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'halt' -c 'flash erase_address 0x08004000 0xC000' -c shutdown)

    add_custom_target(readapp
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'halt' -c 'flash read_bank 0 app_readed.bin 0x20000 0x20000' -c shutdown)

    add_custom_target(read
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg -c init -c targets -c 'halt' -c 'flash read_bank 0 fw.bin 0x00000 0x80000' -c shutdown)

    add_custom_target(gdbs
            COMMAND ${OPENOCD} -f ${CMAKE_SOURCE_DIR}/support/alarm_host_${DEBUGGER}.cfg)

    add_custom_target(gdb
            COMMAND arm-none-eabi-gdb ${target}.elf -ex 'target remote localhost:3333' -ex 'monitor reset halt' -ex 'load')


else()
    function(add_flash_target target)
        # Not supported
    endfunction()
endif()