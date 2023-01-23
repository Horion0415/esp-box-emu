#pragma once

#include <string>
#include <string_view>

void init_nes(const std::string& rom_filename, uint8_t *romdata, size_t rom_data_size);
void load_nes(std::string_view save_path);
void save_nes(std::string_view save_path);
void run_nes_rom();
void deinit_nes();
void set_nes_video_original();
void set_nes_video_fit();
void set_nes_video_fill();
