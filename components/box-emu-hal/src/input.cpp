#include "input.h"

#include "i2c.hpp"

#include "task.hpp"

#include "mcp23x17.hpp"

#include "touchpad_input.hpp"
#define USE_FT5X06 0
#if USE_FT5X06
#include "ft5x06.hpp"
#else
#include "tt21100.hpp"
#endif

using namespace std::chrono_literals;

static std::shared_ptr<espp::Mcp23x17> mcp23x17;

#if USE_FT5X06
static std::shared_ptr<Ft5x06> ft5x06;
#else
static std::shared_ptr<Tt21100> tt21100;
#endif
static std::shared_ptr<espp::TouchpadInput> touchpad;

/**
 * Touch Controller configuration
 */
#if USE_FT5X06
void ft5x06_write(uint8_t reg_addr, uint8_t value) {
  uint8_t write_buf[] = {reg_addr, value};
  i2c_write_internal_bus(Ft5x06::ADDRESS, write_buf, 2);
}

void ft5x06_read(uint8_t reg_addr, uint8_t *read_data, size_t read_len) {
  i2c_read_internal_bus(Ft5x06::ADDRESS, reg_addr, read_data, read_len);
}
#else
void tt21100_write(uint8_t reg_addr, uint8_t value) {
  uint8_t write_buf[] = {reg_addr, value};
  i2c_write_internal_bus(Tt21100::ADDRESS, write_buf, 2);
}

void tt21100_read(uint8_t *read_data, size_t read_len) {
  i2c_read_internal_bus(Tt21100::ADDRESS, read_data, read_len);
}
#endif

void touchpad_read(uint8_t* num_touch_points, uint16_t* x, uint16_t* y, uint8_t* btn_state) {
  // NOTE: ft5x06 does not have button support, so data->btn_val cannot be set
#if USE_FT5X06
  ft5x06->get_touch_point(num_touch_points, x, y);
  // TODO: how to handle quit condition if FT5x06?
#else
  // get the latest data from the device
  while (!tt21100->read())
    ;
  // now hand it off
  tt21100->get_touch_point(num_touch_points, x, y);
  *btn_state = tt21100->get_home_button_state();
#endif
}

static std::atomic<bool> initialized = false;
void init_input() {
  if (initialized) return;
  fmt::print("Initializing input drivers...\n");

#if USE_FT5X06
  fmt::print("Initializing ft5x06\n");
  ft5x06 = std::make_shared<Ft5x06>(Ft5x06::Config{
      .write = ft5x06_write,
      .read = ft5x06_read,
      .log_level = espp::Logger::Verbosity::WARN
    });
#else
  fmt::print("Initializing Tt21100\n");
  tt21100 = std::make_shared<Tt21100>(Tt21100::Config{
      .read = tt21100_read,
      .log_level = espp::Logger::Verbosity::WARN
    });
#endif

  fmt::print("Initializing touchpad\n");
  touchpad = std::make_shared<espp::TouchpadInput>(espp::TouchpadInput::Config{
      .touchpad_read = touchpad_read,
      .swap_xy = false,
      .invert_x = true,
      .invert_y = false,
      .log_level = espp::Logger::Verbosity::WARN
    });

  fmt::print("initializing MCP23X17\n");
  mcp23x17 = std::make_shared<espp::Mcp23x17>(espp::Mcp23x17::Config{
      .port_a_direction_mask = 0x03,   // Start on A0, Select on A1
      .port_a_interrupt_mask = 0x00,
      .port_b_direction_mask = 0xFF,   // D-pad B0-B3, ABXY B4-B7
      .port_b_interrupt_mask = 0x00,
      .write = i2c_write_external_bus,
      .read = i2c_read_external_bus,
      .log_level = espp::Logger::Verbosity::WARN
    });

  initialized = true;
}

extern "C" void get_input_state(struct InputState* state) {
  bool is_a_pressed = false;
  bool is_b_pressed = false;
  bool is_x_pressed = false;
  bool is_y_pressed = false;
  bool is_select_pressed = false;
  bool is_start_pressed = false;
  bool is_up_pressed = false;
  bool is_down_pressed = false;
  bool is_left_pressed = false;
  bool is_right_pressed = false;
  if (!mcp23x17) {
    fmt::print("cannot get input state: mcp23x17 not initialized properly!\n");
    return;
  }
  // pins are active low
  // start, select = A0, A1
  std::error_code ec;
  auto a_pins = mcp23x17->get_pins(espp::Mcp23x17::Port::A, ec);
  // d-pad, abxy = B0-B3, B4-B7
  auto b_pins = mcp23x17->get_pins(espp::Mcp23x17::Port::B, ec);
  is_a_pressed = !(b_pins & 1<<4);
  is_b_pressed = !(b_pins & 1<<5);
  is_x_pressed = !(b_pins & 1<<6);
  is_y_pressed = !(b_pins & 1<<7);
  is_start_pressed = !(a_pins & 1<<0);
  is_select_pressed = !(a_pins & 1<<1);
  is_up_pressed = !(b_pins & 1<<0);
  is_down_pressed = !(b_pins & 1<<1);
  is_left_pressed = !(b_pins & 1<<2);
  is_right_pressed = !(b_pins & 1<<3);
  state->a = is_a_pressed;
  state->b = is_b_pressed;
  state->x = is_x_pressed;
  state->y = is_y_pressed;
  state->start = is_start_pressed;
  state->select = is_select_pressed;
  state->up = is_up_pressed;
  state->down = is_down_pressed;
  state->left = is_left_pressed;
  state->right = is_right_pressed;
}
