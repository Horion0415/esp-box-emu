set(requires "driver" "fatfs" "esp-box-3")

idf_component_register(
    SRCS "src/boards/esp32_bsp_board.c"
    INCLUDE_DIRS "src/boards" "include"
    REQUIRES ${requires})