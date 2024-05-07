#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "event_manager.hpp"
#include "display.hpp"
#include "jpeg.hpp"
#include "task.hpp"
#include "logger.hpp"

#include "hal_events.hpp"
#include "i2s_audio.h"
#include "video_setting.hpp"
#include "lvgl.h"

class Gui {
public:
  struct Config {
    std::shared_ptr<espp::Display> display;
    espp::Logger::Verbosity log_level{espp::Logger::Verbosity::WARN};
  };

  Gui(const Config& config)
    :  display_(config.display),
       logger_({.tag="Gui", .level=config.log_level}) {
      init_ui();
    update_shared_state();
    //now start the gui updater task
    using namespace std::placeholders;
    task_ = espp::Task::make_unique({
        .name = "Gui Task",
        .callback = std::bind(&Gui::update, this, _1, _2),
        .stack_size_bytes = 6 * 1024
      });
    task_->start();
    //register events
    espp::EventManager::get().add_subscriber(mute_button_topic,
                                              "gui",
                                              std::bind(&Gui::on_mute_button_pressed_adapter, this, _1));
  }

  ~Gui() {
    task_->stop();
    deinit_ui();
    espp::EventManager::get().remove_subscriber(mute_button_topic, "gui");
  }

  void ready_to_play(bool new_state) {
    ready_to_play_ = new_state;
  }

  bool ready_to_play() {
    return ready_to_play_;
  }

  void set_mute(bool muted);

  void toggle_mute() {
    set_mute(!is_muted());
  }

  void set_audio_level(int new_audio_level);

  int get_audio_level();

  void set_video_setting(VideoSetting setting);

  void add_rom(const std::string& name, const std::string& image_path);

  size_t get_selected_rom_index() {
    return focused_rom_;
  }

  void next() {
    // protect since this function is called from another thread context
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    if (roms_.size() == 0) {
      return;
    }
    // focus the next rom
    focused_rom_++;
    if (focused_rom_ >= roms_.size()) focused_rom_ = 0;
    auto rom = roms_[focused_rom_];
    focus_rom(rom);
  }

  void previous() {
    // protect since this function is called from another thread context
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    if (roms_.size() == 0) {
      return;
    }
    // focus the previous rom
    focused_rom_--;
    if (focused_rom_ < 0) focused_rom_ = roms_.size() - 1;
    auto rom = roms_[focused_rom_];
    focus_rom(rom);
  }

  void focus_rom(lv_obj_t *new_focus, bool scroll_to_view=true);

protected:
  void init_ui();
  void deinit_ui();

  void load_rom_screen();

  void update_shared_state() {
    set_mute(is_muted());
    set_audio_level(get_audio_volume());
    set_video_setting(::get_video_setting());
  }

  VideoSetting get_video_setting();

  void on_mute_button_pressed(const std::string& data) {
    set_mute(is_muted());
  }

  void on_mute_button_pressed_adapter(const std::vector<unsigned char>& data) {
    std::string str_data(data.begin(), data.end());
    on_mute_button_pressed(str_data);
  }

  lv_img_dsc_t make_boxart(const std::string& path) {
    // load the file
    // auto start = std::chrono::high_resolution_clock::now();
    decoder_.decode(path.c_str());
    // auto end = std::chrono::high_resolution_clock::now();
    // auto elapsed = std::chrono::duration<float>(end-start).count();
    // fmt::print("Decoding took {:.3f}s\n", elapsed);
    // make the descriptor
    lv_img_dsc_t img_desc = {
      .header = {
        .cf = LV_IMG_CF_TRUE_COLOR,
        .always_zero = 0,
        .reserved = 0,
        .w = (uint32_t)decoder_.get_width(),
        .h = (uint32_t)decoder_.get_height(),
      },
      .data_size = (uint32_t)decoder_.get_size(),
      .data = decoder_.get_decoded_data(),
    };
    // and return it
    return img_desc;
  }

  bool update(std::mutex& m, std::condition_variable& cv) {
    using namespace std::chrono_literals;
    std::unique_lock<std::mutex> lk(m);
    cv.wait_for(lk, 16ms);

    // don't want to stop the task
    return false;
  }

  static void event_callback(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    auto user_data = lv_event_get_user_data(e);
    auto gui = static_cast<Gui*>(user_data);
    if (!gui) {
      return;
    }
    switch (event_code) {
    case LV_EVENT_SHORT_CLICKED:
      break;
    case LV_EVENT_PRESSED:
      gui->on_pressed(e);
      break;
    case LV_EVENT_VALUE_CHANGED:
      gui->on_value_changed(e);
      break;
    case LV_EVENT_LONG_PRESSED:
      break;
    case LV_EVENT_KEY:
      break;
    default:
      break;
    }
  }

  void on_pressed(lv_event_t *e);
  void on_value_changed(lv_event_t *e);

  // LVLG gui objects
  std::vector<std::string> boxart_paths_;
  std::vector<lv_obj_t*> roms_;
  std::atomic<int> focused_rom_{-1};
  lv_img_dsc_t focused_boxart_;

  lv_anim_t rom_label_animation_template_;
  lv_style_t rom_label_style_;

  Jpeg decoder_;

  std::atomic<bool> ready_to_play_{false};
  std::shared_ptr<espp::Display> display_;
  std::unique_ptr<espp::Task> task_;
  espp::Logger logger_;
  std::recursive_mutex mutex_;
};
