
set(BOARD ${CONFIG_BOARD})

string(TOUPPER ${BOARD} BOARD_UPPER)

add_compile_definitions(BOARD_${BOARD_UPPER})

include_directories(
    ${CMAKE_SOURCE_DIR}/boards
    ${CMAKE_SOURCE_DIR}/boards/${BOARD}
)

file(GLOB BOARD_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/boards/${BOARD}/*.c)