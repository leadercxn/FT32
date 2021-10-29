set(ARCH arm)
set(CPU  cortex-m0)

set(FT32_SOURCE_FILES
    # "${CMSIS_DIR}/Device/FT/FT32F0xx/Source/Templates/system_ft32f072x8.c"
    "${CMSIS_DIR}/Device/FT/FT32F0xx/Source/Templates/system_ft32f0xx.c"
    "${CMSIS_DIR}/Device/FT/FT32F0xx/Source/Templates/arm/startup_ft32f072xb.s"

    # "${UTIL_DIR}/FT32_EVAL/Common/*.c"   
    "${UTIL_DIR}/FT32_EVAL/FT32f072X8_EVAL/FT32F072X8_eval.C" 
    ${CMAKE_SOURCE_DIR}/Utilities/FT32_EVAL/FT32f072X8_EVAL/FT32F072X8_eval.c
)

set(FT32_INCLUDE_DIRS
    "${CMSIS_DIR}/Include"
    "${CMSIS_DIR}/Device/FT/FT32F0xx/Include"

    ${CMAKE_SOURCE_DIR}/Utilities/FT32_EVAL/Common
    ${CMAKE_SOURCE_DIR}/Utilities/FT32_EVAL/FT32f072X8_EVAL
)

set(FT32_DEFINES
    -DFT32F072x8
)

set(ft32f03x_FAMILY "FT32F0")
