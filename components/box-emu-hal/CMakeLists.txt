idf_component_register(
  INCLUDE_DIRS "include"
  SRC_DIRS "src"
  REQUIRES "driver" "joltwallet__littlefs" "heap" "fatfs" "esp_lcd" "esp_psram" "spi_flash" "nvs_flash" "codec" "display" "event_manager" "button" "bsp" "espressif__esp_lcd_touch" "esp-box-3" "esp_lvgl_port" 
  )
