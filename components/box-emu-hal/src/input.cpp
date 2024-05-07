#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functional>

#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "iot_button.h"
#include "input.h"
#include "task.hpp"

#include "bsp_board.h"
#include "bsp/esp-bsp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

using namespace std::chrono_literals;

#define LEFT_HOTAS1_ADC_CHAN        ADC_CHANNEL_0
#define LEFT_HOTAS2_ADC_CHAN        ADC_CHANNEL_1
#define RIGHT_HOTAS1_ADC_CHAN       ADC_CHANNEL_2
#define RIGHT_HOTAS2_ADC_CHAN       ADC_CHANNEL_3

#define ESP_LCD_TOUCH_IO_I2C_TT21100_ADDRESS        (0x24)

extern uint8_t TOUCH_ADDRESS;

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

extern int g_left_hotas1_adc_raw[2][10];
extern int g_left_hotas1_voltage[2][10];

extern int g_left_hotas2_adc_raw[2][10];
extern int g_left_hotas2_voltage[2][10];

extern int g_right_hotas1_adc_raw[2][10];
extern int g_right_hotas1_voltage[2][10];

extern int g_right_hotas2_adc_raw[2][10];
extern int g_right_hotas2_voltage[2][10];

extern uint16_t left_rocker_x_adc_value[3];
extern uint16_t left_rocker_y_adc_value[3];
extern uint16_t right_rocker_x_adc_value[3];
extern uint16_t right_rocker_y_adc_value[3];

extern adc_oneshot_unit_handle_t game_mode_adc_handle;

extern adc_cali_handle_t left_hotas1_adc_chan_handle;
extern bool do_left_hotas1_adc_chan;

extern adc_cali_handle_t left_hotas2_adc_chan_handle;
extern bool do_left_hotas2_adc_chan;

extern adc_cali_handle_t right_hotas1_adc_chan_handle;
extern bool do_right_hotas1_adc_chan;

extern adc_cali_handle_t right_hotas2_adc_chan_handle;
extern bool do_right_hotas2_adc_chan;

bool left_right_flag = false;
bool up_down_flag = false;
extern uint8_t home_button_status;

/**
 * Gamepad controller configuration
 */

void touchpad_read(uint8_t* num_touch_points, uint16_t* x, uint16_t* y, uint8_t* btn_state) {
  typedef struct {
      esp_lcd_touch_handle_t   handle;     /* LCD touch IO handle */
      lv_indev_drv_t           indev_drv;  /* LVGL input device driver */
  } lvgl_port_touch_ctx_t;
  
  lv_indev_t * disp_indev = bsp_display_get_input_dev();
  esp_lcd_touch_handle_t tp = ((lvgl_port_touch_ctx_t*)(disp_indev->driver->user_data))->handle;  esp_lcd_touch_read_data(tp);
  
  uint8_t home_btn_val = 0x00;
  esp_lcd_touch_get_button_state(tp, 0, &home_btn_val);
  if(home_btn_val == 0x00) {
    * btn_state = 0;
  } else {
    * btn_state = 1;
  }
}

extern "C" void get_input_state(struct InputState* state) {
  adc_oneshot_read(game_mode_adc_handle, LEFT_HOTAS1_ADC_CHAN, &g_left_hotas1_adc_raw[0][0]);
  adc_oneshot_read(game_mode_adc_handle, LEFT_HOTAS2_ADC_CHAN, &g_left_hotas2_adc_raw[0][0]);
  adc_oneshot_read(game_mode_adc_handle, RIGHT_HOTAS1_ADC_CHAN, &g_right_hotas1_adc_raw[0][0]);
  adc_oneshot_read(game_mode_adc_handle, RIGHT_HOTAS2_ADC_CHAN, &g_right_hotas2_adc_raw[0][0]);
  if (do_left_hotas1_adc_chan && do_left_hotas2_adc_chan && do_right_hotas1_adc_chan && do_right_hotas2_adc_chan) {
      ESP_ERROR_CHECK(adc_cali_raw_to_voltage(left_hotas1_adc_chan_handle, g_left_hotas1_adc_raw[0][0], &g_left_hotas1_voltage[0][0]));
      ESP_ERROR_CHECK(adc_cali_raw_to_voltage(left_hotas2_adc_chan_handle, g_left_hotas2_adc_raw[0][0], &g_left_hotas2_voltage[0][0]));
      ESP_ERROR_CHECK(adc_cali_raw_to_voltage(right_hotas1_adc_chan_handle, g_right_hotas1_adc_raw[0][0], &g_right_hotas1_voltage[0][0]));
      ESP_ERROR_CHECK(adc_cali_raw_to_voltage(right_hotas2_adc_chan_handle, g_right_hotas2_adc_raw[0][0], &g_right_hotas2_voltage[0][0]));

      if(g_left_hotas1_voltage[0][0] != left_rocker_x_adc_value[1]) {
        if(g_left_hotas1_voltage[0][0] > left_rocker_x_adc_value[1] + 280) {
              ESP_LOGI("joybutton", "right_button_down OK");
              is_left_pressed = false;
              is_right_pressed = true;
              left_right_flag = false;
        } else if(g_left_hotas1_voltage[0][0] < left_rocker_x_adc_value[1] - 280) {
              ESP_LOGI("joybutton", "left_button_down OK");
              is_left_pressed = true;
              is_right_pressed = false;
              left_right_flag = false;
        } else {
            if(left_right_flag == false) {
              ESP_LOGI("joybutton", "right_button_up OK");
              ESP_LOGI("joybutton", "left_button_up OK");
              is_left_pressed = false;
              is_right_pressed = false;
              left_right_flag = true;
            }
        }
      }

      if(g_left_hotas2_voltage[0][0] != left_rocker_y_adc_value[1]) {
        if(g_left_hotas2_voltage[0][0] > left_rocker_y_adc_value[1] + 280) {
              ESP_LOGI("joybutton", "up_button_down OK");
              is_down_pressed = false;
              is_up_pressed = true;
              up_down_flag = false;
        } else if(g_left_hotas2_voltage[0][0] < left_rocker_y_adc_value[1] - 280) {
              ESP_LOGI("joybutton", "down_button_down OK");
              is_down_pressed = true;
              is_up_pressed = false;
              up_down_flag = false;
        } else {
            if(up_down_flag == false) {
              ESP_LOGI("joybutton", "up_button_up OK");
              ESP_LOGI("joybutton", "down_button_up OK");
              is_up_pressed = false;
              is_down_pressed = false;
              up_down_flag = true;
            }
        }
      }
  }

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
