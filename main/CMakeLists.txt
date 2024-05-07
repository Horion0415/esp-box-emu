idf_component_register(SRC_DIRS "."
                       INCLUDE_DIRS ".")

littlefs_create_partition_image(littlefs ../flash_data FLASH_IN_PROJECT)