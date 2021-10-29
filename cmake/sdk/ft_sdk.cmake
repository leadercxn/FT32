set(SDK_ROOT "${CMAKE_SOURCE_DIR}/sdk" CACHE STRING "")
set(FT_SDK_ROOT "${CMAKE_SOURCE_DIR}/sdk/ft32f0_sdk" CACHE STRING "")

set(SOFTDEVICE s130)
set(${SOFTDEVICE}_HEX_FILE "${FT_SDK_ROOT}/components/softdevice/s130/hex/${SOFTDEVICE}_nrf51_2.0.0_softdevice.hex")