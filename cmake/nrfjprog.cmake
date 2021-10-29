find_program(NRFJPROG nrfjprog)
find_program(MERGEHEX mergehex)
find_program(MKDIR mkdir)

# As here I used a 3rd party tools
if(CMAKE_HOST_WIN32)
    find_program(NRFUTIL adafruit-nrfutil)
elseif(CMAKE_HOST_UNIX)
    find_program(NRFUTIL nrfutil)
endif()

if(NOT NRFJPROG)
    message(STATUS "Tool nrfjprog: not set")
endif()

if(NOT MERGEHEX)
    message(STATUS "Tool mergehex: not set")
endif()

if(NOT NRFUTIL)
    message(STATUS "Tool nrfutil: not set")
endif()

if(NRFJPROG AND MERGEHEX AND NRFUTIL)

    add_custom_target(erase
        COMMAND ${NRFJPROG} -e)

    add_custom_target(flash_sd
        COMMAND ${NRFJPROG} --program ${${SOFTDEVICE}_HEX_FILE} -f ${${PLATFORM}_FAMILY} --chiperase)

    function(add_flash_target target)

        string(TOUPPER ${target} ${target}_upper)

        # Flash target command
        add_custom_target(flash_${target}
            COMMAND ${NRFJPROG} --program ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex -f ${${PLATFORM}_FAMILY} --sectorerase --reset
            DEPENDS ${target})
 
        add_custom_target(flash_sd_${target}
            COMMAND ${NRFJPROG} --program ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex -f ${${PLATFORM}_FAMILY} --sectorerase --reset
            DEPENDS flash_sd ${target})

    endfunction(add_flash_target)

    function(add_dfu_target target out_dir)
        string(TOUPPER ${target} ${target}_upper)

        set(image_dir ${PROJECT_IMAGE_DIR}/${out_dir})

        # set(app_file ${image_dir}/SENSORO_${PROJECT_NAME_UPPER}_${CONFIG_NETWORK_TYPE}_${CONFIG_FIRMWARE_TYPE}_APP_${${target}_VERSION}_${BUILD_HASH}_${BUILD_DATE}.hex)
        # set(dfu_out_file ${image_dir}/SENSORO_${PROJECT_NAME_UPPER}_${CONFIG_NETWORK_TYPE}_${CONFIG_FIRMWARE_TYPE}_DFU_${${target}_VERSION}_${BUILD_HASH}_${BUILD_DATE}.zip)
        # set(swddfu_out_file ${image_dir}/SENSORO_${PROJECT_NAME_UPPER}_${CONFIG_NETWORK_TYPE}_${CONFIG_FIRMWARE_TYPE}_SWDDFU_${${target}_VERSION}_${BUILD_HASH}_${BUILD_DATE}.zip)

        add_custom_target(dfu_${target}
            COMMAND ${MKDIR} -p ${image_dir}
            COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex ${app_file}
            COMMAND ${NRFUTIL} dfu genpkg --application ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex --application-version 0xff
            --dev-revision 0xffff --dev-type 0xffff --sd-req 0x80 ${dfu_out_file}
            COMMAND ${CMAKE_SOURCE_DIR}/scripts/genSwdDfuPkg ${app_file} ${swddfu_out_file}
            DEPENDS ${target})

    endfunction(add_dfu_target)

    function(add_fw_target target with_sd with_bl out_dir)

        string(TOUPPER ${target} ${target}_upper)

        if(with_sd)
            set(sd ${${SOFTDEVICE}_HEX_FILE})
        endif()

        if(with_bl)
            set(bl ${CMAKE_SOURCE_DIR}/images/SENSORO_11A_TM100_BOOTLOADER_v1.1.2_20170420.hex)
            #set(bl ${CMAKE_BINARY_DIR}/apps/bootloader/bootloader.hex)
        endif()

        set(image_dir ${PROJECT_IMAGE_DIR}/${out_dir})

        # set(out_file ${image_dir}/SENSORO_${PROJECT_NAME_UPPER}_${CONFIG_NETWORK_TYPE}_${CONFIG_FIRMWARE_TYPE}_FW_${${target}_VERSION}_${BUILD_HASH}_${BUILD_DATE}.hex)

        if(with_sd OR with_bl)
            add_custom_target(fw_${target}
                COMMAND ${MKDIR} -p ${image_dir}
                COMMAND ${MERGEHEX} -m ${sd} ${bl} ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex -o ${out_file}
                DEPENDS ${target})
        else()
            add_custom_target(fw_${target}
                COMMAND ${MKDIR} -p ${image_dir}
                COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/${target}.hex ${out_file}
                DEPENDS ${target})
        endif()

        add_custom_target(flash_fw_${target}
            COMMAND ${NRFJPROG} --program ${out_file} -f ${${PLATFORM}_FAMILY} --chiperase -r
            DEPENDS fw_${target})


        add_custom_target(pub_${target}
            COMMAND zip -j -r ${PROJECT_IMAGE_DIR}/SENSORO_${PROJECT_NAME_UPPER}_${${target}_upper}_${${target}_VERSION}_${BUILD_HASH}_${BUILD_DATE}.zip ${image_dir}/* ${CMAKE_SOURCE_DIR}/CHANGELOG.md ${PROJECT_IMAGE_DIR}/external/*
            DEPENDS fw_${target} dfu_${target})

    endfunction(add_fw_target)

else()
    message(STATUS "Could not find nRFx command line tools")
    function(add_flash_target target)
        # Not supported
    endfunction()

    function(add_dfu_target target)
    endfunction()

    function(add_fw_target target)
    endfunction()
endif()
