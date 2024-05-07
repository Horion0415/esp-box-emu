#include "nes.hpp"
#include "gameboy.hpp"

#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include <chrono>
#include <memory>
#include <thread>
#include <vector>
#include <stdio.h>

#include "input.h"
#include "i2s_audio.h"
#include "spi_lcd.h"
#include "format.hpp"

#include "gbc_cart.hpp"
#include "nes_cart.hpp"
#include "string_utils.hpp"
#include "fs_init.hpp"
#include "gui.hpp"
#include "mmap.hpp"
#include "rom_info.hpp"

#include "joybutton.h"

#include <math.h>
#include "esp_log.h"
#include "esp_check.h"

#include "bsp_board.h"
#include "bsp/esp-bsp.h"
#include "audio_player.h"
#include "spi_lcd.h"

#include <time.h>
#include <sys/time.h>

_lv_disp_drv_t * disp_drv = NULL;
// from spi_lcd.cpp
extern std::shared_ptr<espp::Display> display;
TaskHandle_t nes_handle_task;
std::vector<RomInfo> roms;

using namespace std::chrono_literals;

bool operator==(const InputState& lhs, const InputState& rhs) {
  return
    lhs.a == rhs.a &&
    lhs.b == rhs.b &&
    lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.select == rhs.select &&
    lhs.start == rhs.start &&
    lhs.up == rhs.up &&
    lhs.down == rhs.down &&
    lhs.left == rhs.left &&
    lhs.right == rhs.right &&
    lhs.joystick_select == rhs.joystick_select;
}

std::unique_ptr<Cart> make_cart(const RomInfo& info) {
    switch (info.platform) {
    case Emulator::GAMEBOY:
    case Emulator::GAMEBOY_COLOR:
        return std::make_unique<GbcCart>(Cart::Config{
            .info = info,
            .display = display,
            .verbosity = espp::Logger::Verbosity::WARN
        });
        break;
    case Emulator::NES:
        return std::make_unique<NesCart>(Cart::Config{
            .info = info,
            .display = display,
            .verbosity = espp::Logger::Verbosity::WARN
        });
    default:
        return nullptr;
    }
}

extern "C" void app_main(void) {
  init_memory();

  fs_init();

  bsp_i2c_init();

  bsp_display_cfg_t cfg = {
      .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG()
  };
  cfg.lvgl_port_cfg.task_affinity = 1;
  lv_disp_t * s_disp = bsp_display_start_with_config(&cfg);
  disp_drv = s_disp->driver;
  display_init();

  audio_init();

  box_rc_button_init();
  rocker_adc_init();

  bsp_display_backlight_on();

  bsp_display_lock(0);

  Gui gui({
      .display = display,
      .log_level = espp::Logger::Verbosity::WARN
    });

  bsp_display_unlock();

  //the prefix for the filesystem (either littlefs or sdcard)
  std::string fs_prefix = MOUNT_POINT;

  //load the metadata.csv file, parse it, and add roms from it
  roms = parse_metadata(fs_prefix + "/metadata.csv");
  std::string boxart_prefix = fs_prefix + "/";

  for (auto& rom : roms) {
      gui.add_rom(rom.name, boxart_prefix + rom.boxart_path);
  }

    while (true) {
        // reset gui ready to play and user_quit
        gui.ready_to_play(false);

        struct InputState prev_state;
        struct InputState curr_state;
        get_input_state(&prev_state);
        get_input_state(&curr_state);
        while (!gui.ready_to_play()) {
        // TODO: would be better to make this an actual LVGL input device instead
        // of this..
        get_input_state(&curr_state);
        bsp_display_lock(0);
        if (curr_state != prev_state) {
            prev_state = curr_state;
            if (curr_state.left) {
            gui.previous();
            } else if (curr_state.right) {
            gui.next();
            } else if (curr_state.start) {
            // same as play button was pressed, just exit the loop!
            break;
            }
        }
        bsp_display_unlock();
        std::this_thread::sleep_for(50ms);
        }

        // Now pause the LVGL gui
        display->pause();

        // ensure the display has been paused
        std::this_thread::sleep_for(100ms);

        fmt::print("Before emulation, minimum free heap: {}\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));

        auto selected_rom_index = gui.get_selected_rom_index();
        if (selected_rom_index < roms.size()) {
        fmt::print("Selected rom:\n");
        fmt::print("  index: {}\n", selected_rom_index);
        auto selected_rom_info = roms[selected_rom_index];
        fmt::print("  name:  {}\n", selected_rom_info.name);
        fmt::print("  path:  {}\n", selected_rom_info.rom_path);

        // Cart handles platform specific code, state management, etc.
        {
            std::unique_ptr<Cart> cart = std::move(make_cart(selected_rom_info));
            if (cart) {
            fmt::print("Running cart...\n");
            while (cart->run());
            } else {
            fmt::print("Failed to create cart!\n");
            }
        }
        } else {
        fmt::print("Invalid rom selected!\n");
        }

        std::this_thread::sleep_for(100ms);

        fmt::print("Resuming your regularly scheduled programming...\n");

        fmt::print("During emulation, minimum free heap: {}\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));

        // need to reset to control the whole screen
        lcd_clear(0,0,320,240);

        display->force_refresh();
        display->resume();
    }
}
