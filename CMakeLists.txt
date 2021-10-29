cmake_minimum_required(VERSION 3.14)

option(BUILD_HOST "Build for host (unit test build)" OFF)

if(NOT BUILD_HOST)
    set(CMAKE_SYSTEM_NAME "Generic")
    set(CMAKE_SYSTEM_PROCESSOR "ARM")
endif()

project(ft32f0 LANGUAGES NONE)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

string(TIMESTAMP BUILD_DATE "%Y%m%d%H%M")

set(CMAKE_CONFIG_DIR ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR} CACHE STRING "" FORCE)
set(PROJECT_IMAGE_DIR ${CMAKE_SOURCE_DIR}/images)

set(DEV_DIR ${CMAKE_SOURCE_DIR}/develop_lib)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/Libraries/FT32F0xx_StdPeriph_Driver)
set(UTIL_DIR ${CMAKE_SOURCE_DIR}/Utilities)
set(CMSIS_DIR ${CMAKE_SOURCE_DIR}/Libraries/CMSIS)

set(AUTOCONF_H ${PROJECT_BINARY_DIR}/include/generated/autoconf.h)
# Re-configure (Re-execute all CMakeLists.txt code) when autoconf.h changes
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${AUTOCONF_H})

set_property(GLOBAL PROPERTY PROJECT_LIBS "")

include(${CMAKE_CONFIG_DIR}/extensions.cmake)
include(${CMAKE_CONFIG_DIR}/python.cmake)
# include(${CMAKE_CONFIG_DIR}/git.cmake)
include(${CMAKE_CONFIG_DIR}/kconfig.cmake)
include(${CMAKE_CONFIG_DIR}/platform.cmake)
include(${CMAKE_CONFIG_DIR}/toolchain.cmake)
include(${CMAKE_CONFIG_DIR}/board.cmake)
include(${CMAKE_CONFIG_DIR}/sdk/ft_sdk.cmake)
include(${CMAKE_CONFIG_DIR}/version.cmake)
include(${CMAKE_CONFIG_DIR}/openocd.cmake)
# include(${CMAKE_CONFIG_DIR}/nrfjprog.cmake)

if(EXISTS ${CMAKE_CONFIG_DIR}/custom.cmake)
   include(${CMAKE_CONFIG_DIR}/custom.cmake)
endif()

add_custom_target(pristine
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CONFIG_DIR}/pristine.cmake
# Equivalent to rm -rf build/*
)

message(STATUS "Platform: ${PLATFORM}")
message(STATUS "Arch: ${ARCH}")
message(STATUS "CPU: ${CPU}")
message(STATUS "Board: BOARD = ${BOARD}")
message(STATUS "Toolchain: TOOLCHAIN = ${TOOLCHAIN}")
message(STATUS "Build type: ${CONFIG_BUILD_TYPE}")
message(STATUS "Trace level: ${CONFIG_TRACE_LEVEL}")
message(STATUS "Trace backend: ${CONFIG_TRACE_BACKEND}")
message(STATUS "Firmware Type: ${CONFIG_FIRMWARE_TYPE}_MODE")

enable_language(C ASM)

if(NOT BUILD_HOST)
    set(CMAKE_EXECUTABLE_SUFFIX ".elf")
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
endif()

add_subdirectory(sdk)

if(NOT BUILD_HOST)
    add_subdirectory(apps/fct)
endif()


