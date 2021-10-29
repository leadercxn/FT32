
########################################################
# 2. Kconfig-aware extensions
########################################################
#
# Kconfig is a configuration language developed for the Linux
# kernel. The below functions integrate CMake with Kconfig.
#
# 2.1 *_if_kconfig
#
# Functions for conditionally including directories and source files
# that have matching KConfig values.
#
# zephyr_library_sources_if_kconfig(fft.c)
# is the same as
# zephyr_library_sources_ifdef(CONFIG_FFT fft.c)
#
# add_subdirectory_if_kconfig(serial)
# is the same as
# add_subdirectory_ifdef(CONFIG_SERIAL serial)
function(add_subdirectory_if_kconfig dir)
  string(TOUPPER config_${dir} UPPER_CASE_CONFIG)
  add_subdirectory_ifdef(${UPPER_CASE_CONFIG} ${dir})
endfunction()

function(target_sources_if_kconfig target scope item)
  get_filename_component(item_basename ${item} NAME_WE)
  string(TOUPPER CONFIG_${item_basename} UPPER_CASE_CONFIG)
  target_sources_ifdef(${UPPER_CASE_CONFIG} ${target} ${scope} ${item})
endfunction()


# 2.2 Misc
#
# Parse a KConfig fragment (typically with extension .config) and
# introduce all the symbols that are prefixed with 'prefix' into the
# CMake namespace
function(import_kconfig prefix kconfig_fragment)
  # Parse the lines prefixed with 'prefix' in ${kconfig_fragment}
  file(
    STRINGS
    ${kconfig_fragment}
    DOT_CONFIG_LIST
    REGEX "^${prefix}"
    ENCODING "UTF-8"
  )

  foreach (CONFIG ${DOT_CONFIG_LIST})
    # CONFIG could look like: CONFIG_NET_BUF=y

    # Match the first part, the variable name
    string(REGEX MATCH "[^=]+" CONF_VARIABLE_NAME ${CONFIG})

    # Match the second part, variable value
    string(REGEX MATCH "=(.+$)" CONF_VARIABLE_VALUE ${CONFIG})

    # The variable name match we just did included the '=' symbol. To just get the
    # part on the RHS we use match group 1
    set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})

    if("${CONF_VARIABLE_VALUE}" MATCHES "^\"(.*)\"$") # Is surrounded by quotes
      set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})
    endif()

    set("${CONF_VARIABLE_NAME}" "${CONF_VARIABLE_VALUE}" PARENT_SCOPE)
  endforeach()
endfunction()

########################################################
# 3. CMake-generic extensions
########################################################
#
# These functions extend the CMake API in a way that is not particular
# to Zephyr. Primarily they work around limitations in the CMake
# language to allow cleaner build scripts.

# 3.1. *_ifdef
#
# Functions for conditionally executing CMake functions with oneliners
# e.g.
#
# if(CONFIG_FFT)
#   zephyr_library_source(
#     fft_32.c
#     fft_utils.c
#     )
# endif()
#
# Becomes
#
# zephyr_source_ifdef(
#   CONFIG_FFT
#   fft_32.c
#   fft_utils.c
#   )
#
# More Generally
# "<function-name>_ifdef(CONDITION args)"
# Becomes
# """
# if(CONDITION)
#   <function-name>(args)
# endif()
# """
#
# ifdef functions are added on an as-need basis. See
# https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html for
# a list of available functions.
function(add_subdirectory_ifdef feature_toggle dir)
  if(${${feature_toggle}})
    add_subdirectory(${dir})
  endif()
endfunction()

function(target_sources_ifdef feature_toggle target scope item)
  if(${${feature_toggle}})
    target_sources(${target} ${scope} ${item} ${ARGN})
  endif()
endfunction()

function(target_compile_definitions_ifdef feature_toggle target scope item)
  if(${${feature_toggle}})
    target_compile_definitions(${target} ${scope} ${item} ${ARGN})
  endif()
endfunction()

function(target_include_directories_ifdef feature_toggle target scope item)
  if(${${feature_toggle}})
    target_include_directories(${target} ${scope} ${item} ${ARGN})
  endif()
endfunction()

function(target_link_libraries_ifdef feature_toggle target item)
  if(${${feature_toggle}})
    target_link_libraries(${target} ${item} ${ARGN})
  endif()
endfunction()

function(add_compile_option_ifdef feature_toggle option)
  if(${${feature_toggle}})
    add_compile_options(${option})
  endif()
endfunction()

function(target_compile_option_ifdef feature_toggle target scope option)
  if(${feature_toggle})
    target_compile_options(${target} ${scope} ${option})
  endif()
endfunction()

function(target_cc_option_ifdef feature_toggle target scope option)
  if(${feature_toggle})
    target_cc_option(${target} ${scope} ${option})
  endif()
endfunction()

macro(list_append_ifdef feature_toggle list)
  if(${${feature_toggle}})
    list(APPEND ${list} ${ARGN})
  endif()
endmacro()

# 3.2. *_ifndef
# See 3.1 *_ifdef
function(set_ifndef variable value)
  if(NOT ${variable})
    set(${variable} ${value} ${ARGN} PARENT_SCOPE)
  endif()
endfunction()

function(target_cc_option_ifndef feature_toggle target scope option)
  if(NOT ${feature_toggle})
    target_cc_option(${target} ${scope} ${option})
  endif()
endfunction()


# 3.2. *_option Compiler-compatibility checks
#
# Utility functions for silently omitting compiler flags when the
# compiler lacks support. *_cc_option was ported from KBuild, see
# cc-option in
# https://www.kernel.org/doc/Documentation/kbuild/makefiles.txt

# Writes 1 to the output variable 'ok' for the language 'lang' if
# the flag is supported, otherwise writes 0.
#
# lang must be C or CXX
#
# TODO: Support ASM
#
# Usage:
#
# check_compiler_flag(C "-Wall" my_check)
# print(my_check) # my_check is now 1
function(check_compiler_flag lang option ok)
  if(NOT DEFINED CMAKE_REQUIRED_QUIET)
    set(CMAKE_REQUIRED_QUIET 1)
  endif()

  string(MAKE_C_IDENTIFIER
    check${option}_${lang}_${CMAKE_REQUIRED_FLAGS}
    ${ok}
    )

  if(${lang} STREQUAL C)
    check_c_compiler_flag("${option}" ${${ok}})
  else()
    check_cxx_compiler_flag("${option}" ${${ok}})
  endif()

  if(${${${ok}}})
    set(ret 1)
  else()
    set(ret 0)
  endif()

  set(${ok} ${ret} PARENT_SCOPE)
endfunction()

function(target_cc_option target scope option)
  target_cc_option_fallback(${target} ${scope} ${option} "")
endfunction()


# 3.4. Debugging CMake

# Usage:
#   print(BOARD)
#
# will print: "BOARD: nrf52_pca10040"
function(print arg)
  message(STATUS "${arg}: ${${arg}}")
endfunction()

# Usage:
#   assert(ZEPHYR_TOOLCHAIN_VARIANT "ZEPHYR_TOOLCHAIN_VARIANT not set.")
#
# will cause a FATAL_ERROR and print an error message if the first
# expression is false
macro(assert test comment)
  if(NOT ${test})
    message(FATAL_ERROR "Assertion failed: ${comment}")
  endif()
endmacro()

# Usage:
#   assert_not(FLASH_SCRIPT "FLASH_SCRIPT has been removed; use BOARD_FLASH_RUNNER")
#
# will cause a FATAL_ERROR and print an errorm essage if the first
# espression is true
macro(assert_not test comment)
  if(${test})
    message(FATAL_ERROR "Assertion failed: ${comment}")
  endif()
endmacro()

# Usage:
#   assert_exists(CMAKE_READELF)
#
# will cause a FATAL_ERROR if there is no file or directory behind the
# variable
macro(assert_exists var)
  if(NOT EXISTS ${${var}})
    message(FATAL_ERROR "No such file or directory: ${var}: '${${var}}'")
  endif()
endmacro()

function(print_usage)
  message("see usage:")
  string(REPLACE ";" " " BOARD_ROOT_SPACE_SEPARATED "${BOARD_ROOT}")
  execute_process(
    COMMAND
    ${CMAKE_COMMAND}
    -DBOARD_ROOT_SPACE_SEPARATED=${BOARD_ROOT_SPACE_SEPARATED}
    -P ${ZEPHYR_BASE}/cmake/usage/usage.cmake
    )
endfunction()

# 3.5. File system management
function(check_if_directory_is_writeable dir ok)
  execute_process(
    COMMAND
    ${PYTHON_EXECUTABLE}
    ${ZEPHYR_BASE}/scripts/dir_is_writeable.py
    ${dir}
    RESULT_VARIABLE ret
    )

  if("${ret}" STREQUAL "0")
    # The directory is write-able
    set(${ok} 1 PARENT_SCOPE)
  else()
    set(${ok} 0 PARENT_SCOPE)
  endif()
endfunction()

function(find_appropriate_cache_directory dir)
  set(env_suffix_LOCALAPPDATA   .cache)

  if(CMAKE_HOST_APPLE)
    # On macOS, ~/Library/Caches is the preferred cache directory.
    set(env_suffix_HOME Library/Caches)
  else()
    set(env_suffix_HOME .cache)
  endif()

  # Determine which env vars should be checked
  if(CMAKE_HOST_APPLE)
    set(dirs HOME)
  elseif(CMAKE_HOST_WIN32)
    set(dirs LOCALAPPDATA)
  else()
    # Assume Linux when we did not detect 'mac' or 'win'
    #
    # On Linux, freedesktop.org recommends using $XDG_CACHE_HOME if
    # that is defined and defaulting to $HOME/.cache otherwise.
    set(dirs
      XDG_CACHE_HOME
      HOME
      )
  endif()

  foreach(env_var ${dirs})
    if(DEFINED ENV{${env_var}})
      set(env_dir $ENV{${env_var}})

      check_if_directory_is_writeable(${env_dir} ok)
      if(${ok})
        # The directory is write-able
        set(user_dir ${env_dir}/${env_suffix_${env_var}})
        break()
      else()
        # The directory was not writeable, keep looking for a suitable
        # directory
      endif()
    endif()
  endforeach()

  # Populate local_dir with a suitable directory for caching
  # files. Prefer a directory outside of the git repository because it
  # is good practice to have clean git repositories.
  if(DEFINED user_dir)
    # Zephyr's cache files go in the "zephyr" subdirectory of the
    # user's cache directory.
    set(local_dir ${user_dir}/zephyr)
  else()
    set(local_dir ${ZEPHYR_BASE}/.cache)
  endif()

  set(${dir} ${local_dir} PARENT_SCOPE)
endfunction()

function(generate_unique_target_name_from_filename filename target_name)
  get_filename_component(basename ${filename} NAME)
  string(REPLACE "." "_" x ${basename})
  string(REPLACE "@" "_" x ${x})

  string(RANDOM LENGTH 8 random_chars)

  set(${target_name} gen_${x}_${random_chars} PARENT_SCOPE)
endfunction()

# custom
#
# check if item is in list.
# if not, unset the cached value
#
macro(check_in_list item list)
    set(arg ${item})
    set(arg_value ${${item}})

    if (NOT arg_value IN_LIST ${list})
        unset(${item} CACHE)
        message(FATAL_ERROR "Invalid ${arg}: ${arg_value}, Please select in ${${list}}")
    endif()
endmacro()


macro(project_library)
  project_library_get_current_dir_lib_name(${CMAKE_SOURCE_DIR} lib_name)
  project_library_named(${lib_name})
endmacro()

# Determines what the current directory's lib name would be according to the
# provided base and writes it to the argument "lib_name"
macro(project_library_get_current_dir_lib_name base lib_name)
  # Remove the prefix (/home/sebo/zephyr/driver/serial/CMakeLists.txt => driver/serial/CMakeLists.txt)
  file(RELATIVE_PATH name ${base} ${CMAKE_CURRENT_LIST_FILE})

  # Remove the filename (driver/serial/CMakeLists.txt => driver/serial)
  get_filename_component(name ${name} DIRECTORY)

  # Replace / with __ (driver/serial => driver__serial)
  string(REGEX REPLACE "/" "__" name ${name})

  set(${lib_name} ${name})
endmacro()

# Constructor with an explicitly given name.
macro(project_library_named name)
  # This is a macro because we need add_library() to be executed
  # within the scope of the caller.
  set(PROJECT_CURRENT_LIBRARY ${name})

  add_library(${name} STATIC "")

  project_append_cmake_library(${name})

  # target_link_libraries(${name} PUBLIC project_interface)
endmacro()

function(project_append_cmake_library library)
  set_property(GLOBAL APPEND PROPERTY PROJECT_LIBS ${library})
endfunction()

function(project_link_interface interface)
  target_link_libraries(${interface} INTERFACE project_interface)
endfunction()

#
# project_library versions of normal CMake target_<func> functions
#
function(project_library_sources scope source)
  target_sources(${PROJECT_CURRENT_LIBRARY} ${scope} ${source} ${ARGN})
endfunction()

function(project_library_include_directories scope)
  target_include_directories(${PROJECT_CURRENT_LIBRARY} ${scope} ${ARGN})
endfunction()

function(project_library_link_libraries item)
  target_link_libraries(${PROJECT_CURRENT_LIBRARY} PUBLIC ${item} ${ARGN})
endfunction()

function(project_library_compile_definitions scope item)
  target_compile_definitions(${PROJECT_CURRENT_LIBRARY} ${scope} ${item} ${ARGN})
endfunction()
