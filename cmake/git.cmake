find_package(Git QUIET)

set(SDK_URL "git@gitlab.sensoro.com:EndDevice/sdk.git" CACHE STRING "")
set(SDK_BRANCH "eb997b69" CACHE STRING "" FORCE)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/sdk")
    message(STATUS "Download remote SDK repo")
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} clone ${SDK_URL} ${CMAKE_SOURCE_DIR}/sdk
        )
        execute_process(
            COMMAND ${GIT_EXECUTABLE} -C ${CMAKE_SOURCE_DIR}/sdk checkout ${SDK_BRANCH}
        )
        execute_process(
            COMMAND ${GIT_EXECUTABLE} -C ${CMAKE_SOURCE_DIR}/sdk submodule update --init --recursive
        )
    endif()
else()
    message(STATUS "Find sdk repo")
endif()

# https://cmake.org/cmake/help/latest/module/FindGit.html
find_package(Git QUIET)
if(NOT BUILD_HASH AND GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
    WORKING_DIRECTORY                ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE                  BUILD_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    ERROR_VARIABLE                   stderr
    RESULT_VARIABLE                  return_code
  )
  if(return_code)
    message(STATUS "git describe failed: ${stderr};
   BUILD_HASH is left undefined")
  elseif(CMAKE_VERBOSE_MAKEFILE)
    message(STATUS "git describe stderr: ${stderr}")
  endif()
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/sdk/ft32f0_sdk")
    set(SDK_ROOT "${CMAKE_SOURCE_DIR}/sdk" CACHE STRING "")
    set(FT_SDK_ROOT "${CMAKE_SOURCE_DIR}/sdk/ft32f0_sdk" CACHE STRING "")
endif()