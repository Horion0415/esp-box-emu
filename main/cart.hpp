#pragma once

#include <filesystem>
#include <memory>
#include <mutex>

#include "display.hpp"
#include "fs_init.hpp"
#include "spi_lcd.h"
#include "input.h"
#include "logger.hpp"
#include "mmap.hpp"
#include "rom_info.hpp"
#include "st7789.hpp"
#include "menu.hpp"

/// This class is the base class for all carts.
/// It provides the following functionality:
/// - menu
/// - save/load
/// - screenshot
/// - video setting
/// - romdata
class Cart {
public:

  /// Configuration for the Cart class
  struct Config {
    RomInfo info; ///< rom info
    std::shared_ptr<espp::Display> display; ///< display pointer for the menu
    espp::Logger::Verbosity verbosity = espp::Logger::Verbosity::WARN; ///< verbosity level for the logger
  };

  /// Constructor
  /// \param config configuration for the cart
  Cart(const Config& config)
    : info_(config.info),
      savedir_(FS_PREFIX + "/" + SAVE_DIR),
      display_(config.display),
      logger_({.tag = "Cart", .level = config.verbosity}) {
    logger_.info("ctor");
    menu_ = std::make_unique<Menu>(Menu::Config{
        .display = display_,
          .paused_image_path = get_paused_image_path(),
          .action_callback =
          std::bind(&Cart::on_menu_action, this, std::placeholders::_1),
          .slot_image_callback = [this]() -> std::string {
            return get_screenshot_path(false);
          },
          .log_level = espp::Logger::Verbosity::WARN
          });
    // create the save directory if it doesn't exist
    std::error_code ec;
    if (!std::filesystem::exists(savedir_, ec)) {
      std::filesystem::create_directory(savedir_, ec);
    }
  }

  ~Cart() {
    logger_.info("dtor");
    deinit();
  }

  std::string get_rom_filename() const {
    return FS_PREFIX + "/" + info_.rom_path;
  }

  virtual void reset() {
    logger_.info("reset");
    // the subclass should override this to reset the emulator
  }

  virtual void load() {
    logger_.info("loading...");
    // move the screenshot to the pause image
    auto screenshot_path = get_screenshot_path(true);
    auto paused_image_path = get_paused_image_path();
    logger_.debug("copy {} to {}", screenshot_path, paused_image_path);
    std::error_code ec;
    if (std::filesystem::exists(paused_image_path, ec)) {
      std::filesystem::remove(paused_image_path, ec);
    }
    // copy the screenshot to the paused image
    std::fstream screenshot(screenshot_path, std::ios::binary | std::ios::in);
    std::fstream paused_image(paused_image_path, std::ios::binary | std::ios::out);
    paused_image << screenshot.rdbuf();
    screenshot.close();
    paused_image.close();
  }

  virtual void save() {
    logger_.info("saving...");
    // move the pause image to the screenshot
    auto paused_image_path = get_paused_image_path();
    auto screenshot_path = get_screenshot_path(true);
    logger_.debug("copy {} to {}", paused_image_path, screenshot_path);
    std::error_code ec;
    if (std::filesystem::exists(paused_image_path, ec)) {
      if (std::filesystem::exists(screenshot_path, ec)) {
        std::filesystem::remove(screenshot_path, ec);
      }
      // copy the paused image to the screenshot
      std::fstream paused_image(paused_image_path, std::ios::binary | std::ios::in);
      std::fstream screenshot(screenshot_path, std::ios::binary | std::ios::out);
      screenshot << paused_image.rdbuf();
      paused_image.close();
      screenshot.close();
    } else {
      logger_.warn("paused image does not exist");
    }
  }

  /// Save the current screen to a file
  /// \param filename filename to save the screenshot to
  /// \return true if the screenshot was saved successfully
  virtual bool screenshot(std::string_view filename) {
    logger_.info("screenshot: {}", filename);
    // get the screen data from the display, size of the frame buffer is
    // (320*2)*240 formatted as RGB565
    auto size = get_video_size();
    uint16_t width = size.first;
    uint16_t height = size.second;
    logger_.debug("frame buffer size: {}x{}", width, height);
    std::vector<uint8_t> frame = get_video_buffer();

    // save it to the file
    std::ofstream file(filename.data(), std::ios::binary);
    if (!file.is_open()) {
      logger_.error("Failed to open file: {}", filename);
      return false;
    }

    uint8_t header[4] = {
      (uint8_t)(width >> 8),
      (uint8_t)(width & 0xFF),
      (uint8_t)(height >> 8),
      (uint8_t)(height & 0xFF)
    };
    // write the header
    file.write((char*)header, sizeof(header));

    // write the data
    file.write((char*)frame.data(), frame.size());
    // make sure to close the file
    file.close();

    return true;
  }

  virtual void init() {
    logger_.info("init");
    espp::St7789::clear(0,0,320,240);
    // copy the romdata
    rom_size_bytes_ = copy_romdata_to_cart_partition(get_rom_filename());
    romdata_ = get_mmapped_romdata();
    handle_video_setting();
  }

  virtual void deinit() {
    logger_.info("deinit");
  }

  virtual bool run() {
    running_ = true;
    // handle touchpad so we can know if the user presses the menu
    uint8_t _num_touches, _btn_state;
    uint16_t _x,_y;
    touchpad_read(&_num_touches, &_x, &_y, &_btn_state);
    if (_btn_state) {
      logger_.warn("Menu pressed!");
      pre_menu();
      // take a screenshot before we show the menu
      screenshot(get_paused_image_path());
      // now resume the menu
      menu_->resume();
      display_->force_refresh();
      display_->resume();
      // wait here until the menu is no longer shown
      while (!menu_->is_paused()) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
      }
      display_->pause();
      // make sure to clear the screen before we resume the game
      espp::St7789::clear(0,0,320,240);
      // only run the post_menu if we are still running
      if (running_)
        post_menu();
    }
    return running_;
  }

protected:
  static constexpr std::string FS_PREFIX = MOUNT_POINT;
  static constexpr std::string SAVE_DIR = "/saves/";

  virtual void on_menu_action(Menu::Action action) {
    switch (action) {
    case Menu::Action::RESUME:
      menu_->pause();
      break;
    case Menu::Action::RESET:
      reset();
      menu_->pause();
      break;
    case Menu::Action::QUIT:
      running_ = false;
      menu_->pause();
      break;
    case Menu::Action::SAVE:
      save();
      break;
    case Menu::Action::LOAD:
      load();
      break;
    default:
      break;
    }
  }

  virtual std::string get_save_extension() const {
    return ".sav";
  }

  virtual std::string get_screenshot_extension() const {
    return ".bin";
  }

  virtual void pre_menu() {
    // subclass should override this function if they need to stop their tasks
    // or save screen state before the menu is shown
  }

  virtual void post_menu() {
    // subclass should override this function if they need to resume their tasks
    // or restore screen state before the menu is shown
    handle_video_setting();
  }

  virtual std::pair<size_t, size_t> get_video_size() const {
    // subclass should override this method to return the size of the video
    // in the framebuffer. This will be used when capturing screenshots.
    return std::make_pair(320, 240);
  }

  virtual std::vector<uint8_t> get_video_buffer() const {
    // subclass should override this method to return the frame buffer
    // as a vector of uint16_t
    return std::vector<uint8_t>();
  }

  // subclass should override these methods
  virtual void set_original_video_setting() = 0;
  virtual void set_fit_video_setting() = 0;
  virtual void set_fill_video_setting() = 0;

  virtual void handle_video_setting() {
    logger_.info("handling video setting...");
    switch (get_video_setting()) {
    case VideoSetting::ORIGINAL:
      set_original_video_setting();
      break;
    case VideoSetting::FIT:
      set_fit_video_setting();
      break;
    case VideoSetting::FILL:
      set_fill_video_setting();
      break;
    default:
      break;
    }
  }

  std::string get_save_path(bool bypass_exist_check=false) {
    namespace fs = std::filesystem;
    auto save_path =
      savedir_ + "/" +
      fs::path(get_rom_filename()).stem().string() +
      fmt::format("_{}", menu_->get_selected_slot()) +
      get_save_extension();
    if (bypass_exist_check || fs::exists(save_path)) {
      logger_.info("found: {}", save_path);
      return save_path;
    } else {
      logger_.warn("Could not find {}", save_path);
    }
    return "";
  }

  std::string get_paused_image_path() {
    namespace fs = std::filesystem;
    auto save_path =
      savedir_ + "/paused" +
      get_screenshot_extension();
    return save_path;
  }

  std::string get_screenshot_path(bool bypass_exist_check=false) {
    auto save_path = get_save_path(bypass_exist_check);
    if (!save_path.empty()) {
      return save_path + get_screenshot_extension();
    }
    return "";
  }

  std::atomic<bool> running_{false};
  size_t rom_size_bytes_{0};
  uint8_t* romdata_{nullptr};
  RomInfo info_;
  std::string savedir_;
  std::unique_ptr<Menu> menu_;
  std::shared_ptr<espp::Display> display_;
  espp::Logger logger_;
};