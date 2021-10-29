if(BUILD_HOST)
else()
    set(PLATFORM "ft32f07x" CACHE STRING "Choose the target platform to build for.")
    set(PLATFORM_OPTIONS "ft32f07x" "ft32f03x" )
    check_in_list(PLATFORM PLATFORM_OPTIONS)
endif()

if(EXISTS ${CMAKE_CONFIG_DIR}/platform/${PLATFORM}.cmake)
    include(${CMAKE_CONFIG_DIR}/platform/${PLATFORM}.cmake)
else()
    message(FATAL_ERROR "Platform specific file for ${PLATFORM} not found")
endif()