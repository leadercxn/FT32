set(ARCH arm)
set(CPU  cortex-m0)

set(FT32_SOURCE_FILES
    # "${CMSIS_DIR}/Device/FT/FT32F0xx/Source/Templates/system_ft32f030x8.c"
    "${CMSIS_DIR}/Device/FT/FT32F0xx/Source/Templates/system_ft32f0xx.c"
    "${CMSIS_DIR}/Device/FT/FT32F0xx/Source/Templates/arm/startup_ft32f030x8.s"

    # "${UTIL_DIR}/FT32_EVAL/Common/*.c"   
    "${UTIL_DIR}/FT32_EVAL/FT32F030XX_EVAL/FT32F030XX_eval.c" 
)

set(FT32_INCLUDE_DIRS
    "${CMSIS_DIR}/Include"
    "${CMSIS_DIR}/Device/FT/FT32F0xx/Include"
    "${UTIL_DIR}/FT32_EVAL/Common"
    "${UTIL_DIR}/FT32_EVAL/FT32F030XX_EVAL"
)

set(FT32_DEFINES
    -DUSE_FT32F030XX_EVAL
    -DFT32F030x8
)

set(ft32f03x_FAMILY "FT32F0")
