#ifndef _JOYBUTTON_H
#define _JOYBUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "iot_button.h"

#define HC165D_PL    38
#define HC165D_CE    39
#define HC165D_SCL   40
#define HC165D_DATA  41

#ifdef __cplusplus
extern "C" {
#endif

void box_rc_button_init(void);
void rocker_adc_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif


#endif