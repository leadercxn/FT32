if(CMAKE_HOST_WIN32)
    set(DEFAULT_KEIL_PATH "C:/Keil_v5/ARM/ARMCC/bin")
elseif(CMAKE_HOST_UNIX)
    set(DEFAULT_KEIL_PATH "/usr/local/DS-5_v5.26.0/sw/ARMCompiler5.06u4/bin")
endif()

find_program(ARMCC_C_COMPILER armcc
    PATHS "${DEFAULT_KEIL_PATH}" ENV PATH NO_DEFAULT_PATH)
find_program(ARMCC_ASM_COMPILER armasm
    PATHS "${DEFAULT_KEIL_PATH}" ENV PATH NO_DEFAULT_PATH)
find_program(ARMCC_LINKER armlink
    PATHS "${DEFAULT_KEIL_PATH}" ENV PATH NO_DEFAULT_PATH)
find_program(ARMCC_FROMELF fromelf
    PATHS "${DEFAULT_KEIL_PATH}" ENV PATH NO_DEFAULT_PATH)

if(NOT(ARMCC_C_COMPILER AND ARMCC_ASM_COMPILER AND ARMCC_LINKER))
    message(FATAL_ERROR "Could not find ARMCC toolchain")
endif()

set(cortex-m0_FLAGS --cpu=Cortex-M0)
set(cortex-m4_FLAGS --cpu=Cortex-M4)
set(cortex-m4f_FLAGS --cpu=Cortex-M4.fp)

option(ARMCC_ENABLE_MICROLIB "Enable the ARM microlib?" ON)

set(CMAKE_C_COMPILER ${ARMCC_C_COMPILER})
set(CMAKE_ASM_COMPILER ${ARMCC_ASM_COMPILER})
set(CMAKE_LINKER ${ARMCC_LINKER})
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_FLAGS_INIT              "${${CPU}_FLAGS} -c --c99 --gnu --apcs=interwork --split_sections")
set(CMAKE_C_FLAGS_RELEASE           "-g -O3 --no_debug" CACHE STRING "")
set(CMAKE_C_FLAGS_DEBUG             "-O1 --debug" CACHE STRING "")
set(CMAKE_C_FLAGS_MINSIZEREL        "-Ospace --debug" CACHE STRING "")
set(CMAKE_C_FLAGS_RELWITHDEBINFO    "-O3 --debug" CACHE STRING "")

set(CMAKE_ASM_FLAGS "${${CPU}_FLAGS} --cpreproc --apcs=interwork --pd \"__HEAP_SIZE SETA 2048\" --pd \"__STACK_SIZE SETA 5120\"")

set(CMAKE_EXE_LINKER_FLAGS
    "${${CPU}_FLAGS} --strict --map --xref --summary_stderr --info summarysizes --info stack --callgraph --symbols --info sizes --info totals --info unused --info veneers")

# 6304: Suppress the "duplicate input" warning caused by circular linking by CMake
# 6330: Supress undefined symbol warning
# string(APPEND CMAKE_EXE_LINKER_FLAGS " --diag_suppress 6304,6330")

if(ARMCC_ENABLE_MICROLIB)
    add_compile_definitions(__MICROLIB)
    string(APPEND CMAKE_EXE_LINKER_FLAGS " --library_type=microlib")
    string(APPEND CMAKE_ASM_FLAGS " --pd \"__MICROLIB SETA 1\"")
endif()

function (set_target_link_options target_name linker_file)
    set_target_properties(${target_name} PROPERTIES LINK_FLAGS
        "--scatter \"${linker_file}.sct\"")
endfunction (set_target_link_options)

function (create_hex executable)
    add_custom_command(
        TARGET ${executable}
        POST_BUILD
        COMMAND ${ARMCC_FROMELF} --i32combined -o ${CMAKE_CURRENT_BINARY_DIR}/${executable}.hex ${CMAKE_CURRENT_BINARY_DIR}/${executable}.elf
        COMMAND ${ARMCC_FROMELF} --bin -o ${CMAKE_CURRENT_BINARY_DIR}/${executable}.bin ${CMAKE_CURRENT_BINARY_DIR}/${executable}.elf
        COMMAND ${CMAKE_SOURCE_DIR}/scripts/max_stack_usage.sh ${CMAKE_CURRENT_BINARY_DIR}/${executable}.elf.map
        BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/${executable}.hex)
endfunction(create_hex)

# We have to cache the variable before the enable_language() call.
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}" CACHE STRING "")