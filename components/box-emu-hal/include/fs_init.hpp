#pragma once

#include <filesystem>

#include <esp_err.h>
#include <sys/stat.h>
#include <errno.h>

#include "esp_littlefs.h"
#define MOUNT_POINT "/littlefs"

void fs_init();
