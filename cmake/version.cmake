
macro(version_target target)
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION ver)

    string(REGEX MATCH "VERSION_MAJOR = ([0-9]*)" _ ${ver})
    set(VERSION_MAJOR ${CMAKE_MATCH_1})

    string(REGEX MATCH "VERSION_MINOR = ([0-9]*)" _ ${ver})
    set(VERSION_MINOR ${CMAKE_MATCH_1})

    string(REGEX MATCH "EXTRAVERSION = ([a-z0-9]*)" _ ${ver})
    set(VERSION_EXTRA ${CMAKE_MATCH_1})

    if((VERSION_MAJOR GREATER 9) OR (VERSION_MINOR GREATER 9) OR (VERSION_EXTRA GREATER 9))
        message(FATAL_ERROR "Version number cannot be greater than 9")
    endif()

    set(${target}_VERSION "v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_EXTRA}" CACHE STRING "" FORCE)

    message(STATUS "${target} version: ${${target}_VERSION}_${BUILD_HASH}")

    math(EXPR VERSION "${VERSION_MAJOR} * 16 * 16 * 16 + ${VERSION_MINOR} * 16 * 16 + ${VERSION_EXTRA}" OUTPUT_FORMAT HEXADECIMAL)
    math(EXPR VERSION_BYTE "${VERSION_MAJOR} * 16 + ${VERSION_MINOR}" OUTPUT_FORMAT HEXADECIMAL)
    set(VERSION_STRING "\"${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_EXTRA}\"")
    math(EXPR VERSION_DEC "${VERSION_MAJOR} * 100 + ${VERSION_MINOR} * 10 + ${VERSION_EXTRA}" OUTPUT_FORMAT DECIMAL)


endmacro(version_target)
