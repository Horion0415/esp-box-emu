#pragma once

#include "lvgl.h"

#ifdef __cplusplus
extern "C"
{
#endif

  struct InputState {
    int a : 1;
    int b : 1;
    int x : 1;
    int y : 1;
    int select : 1;
    int start : 1;
    int up : 1;
    int down : 1;
    int left : 1;
    int right : 1;
    int joystick_select : 1;
  };

  void init_input();
  void get_input_state(struct InputState *state);
  lv_indev_t *get_keypad_input_device();
  void touchpad_read(unsigned char *num_touch_points, unsigned short* x, unsigned short* y, unsigned char* btn_state);

#ifdef __cplusplus
}
#endif
