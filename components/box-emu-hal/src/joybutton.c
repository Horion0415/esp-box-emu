#include "joybutton.h"

#define EXAMPLE_ADC_ATTEN           ADC_ATTEN_DB_11

#define LEFT_HOTAS1_ADC_CHAN        ADC_CHANNEL_0
#define LEFT_HOTAS2_ADC_CHAN        ADC_CHANNEL_1
#define RIGHT_HOTAS1_ADC_CHAN       ADC_CHANNEL_2
#define RIGHT_HOTAS2_ADC_CHAN       ADC_CHANNEL_3

extern bool is_a_pressed;
extern bool is_b_pressed;
extern bool is_x_pressed;
extern bool is_y_pressed;
extern bool is_select_pressed;
extern bool is_start_pressed;
extern bool is_up_pressed;
extern bool is_down_pressed;
extern bool is_left_pressed;
extern bool is_right_pressed;

int g_left_hotas1_adc_raw[2][10];
int g_left_hotas1_voltage[2][10];

int g_left_hotas2_adc_raw[2][10];
int g_left_hotas2_voltage[2][10];

int g_right_hotas1_adc_raw[2][10];
int g_right_hotas1_voltage[2][10];

int g_right_hotas2_adc_raw[2][10];
int g_right_hotas2_voltage[2][10];

uint16_t left_rocker_x_adc_value[3] = { 565, 1623, 2655 };
uint16_t left_rocker_y_adc_value[3] = { 560, 1623, 2850 };
uint16_t right_rocker_x_adc_value[3] = { 423, 1610, 2500 };
uint16_t right_rocker_y_adc_value[3] = { 491, 1590, 2715 };

adc_oneshot_unit_handle_t game_mode_adc_handle = NULL;

adc_cali_handle_t left_hotas1_adc_chan_handle = NULL;
bool do_left_hotas1_adc_chan = false;

adc_cali_handle_t left_hotas2_adc_chan_handle = NULL;
bool do_left_hotas2_adc_chan = false;

adc_cali_handle_t right_hotas1_adc_chan_handle = NULL;
bool do_right_hotas1_adc_chan = false;

adc_cali_handle_t right_hotas2_adc_chan_handle = NULL;
bool do_right_hotas2_adc_chan = false;

static void up_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "up_button_down OK");
    is_up_pressed = true;
}

static void up_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "up_button_up OK");
    is_up_pressed = false;
}

static void left_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "left_button_down OK");
    is_left_pressed = true;
}

static void left_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "left_button_up OK");
    is_left_pressed = false;
}

static void down_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "down_button_down OK");
    is_down_pressed = true;
}

static void down_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "down_button_up OK");
    is_down_pressed = false;
}

static void right_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "right_button_down OK");
    is_right_pressed = true;
}

static void right_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "right_button_up OK");
    is_right_pressed = false;
}

static void lb_button_press_down_cb(void *arg, void *data)
{

}

static void lb_button_press_up_cb(void *arg, void *data)
{

}

static void lt_button_press_down_cb(void *arg, void *data)
{

}

static void lt_button_press_up_cb(void *arg, void *data)
{

}

static void select_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "select_button_down OK");
    is_select_pressed = true;
}

static void select_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "select_button_up OK");
    is_select_pressed = false;
}

static void x_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "x_button_down OK");
    is_x_pressed = true;
}

static void x_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "x_button_up OK");
    is_x_pressed = false;
}

static void y_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "y_button_down OK");
    is_y_pressed = true;
}

static void y_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "y_button_up OK");
    is_y_pressed = false;
}

static void a_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "a_button_down OK");
    is_a_pressed = true;
}

static void a_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "a_button_up OK");
    is_a_pressed = false;
}

static void b_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "b_button_down OK");
    is_b_pressed = true;
}

static void b_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "b_button_up OK");
    is_b_pressed = false;
}

static void rb_button_press_down_cb(void *arg, void *data)
{

}

static void rb_button_press_up_cb(void *arg, void *data)
{

}

static void rt_button_press_down_cb(void *arg, void *data)
{

}

static void rt_button_press_up_cb(void *arg, void *data)
{

}

static void start_button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "start_button_down OK");
    is_start_pressed = true;
}

static void start_button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI("joybutton", "start_button_up OK");
    is_start_pressed = false;
}

static void left_rocker_button_press_down_cb(void *arg, void *data)
{

}

static void left_rocker_button_press_up_cb(void *arg, void *data)
{

}

static void right_rocker_button_press_down_cb(void *arg, void *data)
{

}

static void right_rocker_button_press_up_cb(void *arg, void *data)
{

}

button_cb_t button_press_down_cb[16] = {
    up_button_press_down_cb,
    left_button_press_down_cb,
    down_button_press_down_cb,
    right_button_press_down_cb,
    lb_button_press_down_cb,
    lt_button_press_down_cb,
    select_button_press_down_cb,
    left_rocker_button_press_down_cb,
    y_button_press_down_cb,
    x_button_press_down_cb,
    a_button_press_down_cb,
    b_button_press_down_cb,
    rb_button_press_down_cb,
    rt_button_press_down_cb,
    start_button_press_down_cb,
    right_rocker_button_press_down_cb,
};

button_cb_t button_press_up_cb[16] = {
    up_button_press_up_cb,
    left_button_press_up_cb,
    down_button_press_up_cb,
    right_button_press_up_cb,
    lb_button_press_up_cb,
    lt_button_press_up_cb,
    select_button_press_up_cb,
    left_rocker_button_press_up_cb,
    y_button_press_up_cb,
    x_button_press_up_cb,
    a_button_press_up_cb,
    b_button_press_up_cb,
    rb_button_press_up_cb,
    rt_button_press_up_cb,
    start_button_press_up_cb,
    right_rocker_button_press_up_cb,
};

static void configure_74hc165_pin(void)
{
    gpio_reset_pin(HC165D_PL);
    gpio_reset_pin(HC165D_CE);
    gpio_reset_pin(HC165D_SCL);
    gpio_reset_pin(HC165D_DATA);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(HC165D_PL, GPIO_MODE_OUTPUT);
    gpio_set_direction(HC165D_CE, GPIO_MODE_OUTPUT);
    gpio_set_direction(HC165D_SCL, GPIO_MODE_OUTPUT);
    gpio_set_direction(HC165D_DATA, GPIO_MODE_INPUT);
    gpio_set_level(HC165D_PL, 1);
    gpio_set_level(HC165D_CE, 0);
    gpio_set_level(HC165D_SCL, 1);
}

static uint16_t read_74hc165d_data(void)
{
    uint16_t data = 0;
    uint8_t i = 0;
    uint8_t q7_bit = 0;
    gpio_set_level(HC165D_PL, 0);
    gpio_set_level(HC165D_PL, 1);
    q7_bit = gpio_get_level(HC165D_DATA);
    if (q7_bit == 1) {
        data |= 0x01;
    }
    for (i = 0; i < 15; i++) {
        data = data << 1;
        gpio_set_level(HC165D_SCL, 0);
        gpio_set_level(HC165D_SCL, 1);
        q7_bit = gpio_get_level(HC165D_DATA);
        if (q7_bit == 1) {
            data |= 0x01;
        }
    }
    return data;
}

static uint8_t get_button_value(uint8_t button_index)
{
    uint16_t data = read_74hc165d_data();
    uint16_t mask = 1 << button_index;
    uint8_t button_value = (data & mask) >> button_index;
    return button_value;
}

void box_rc_button_init(void)
{
    configure_74hc165_pin();
    button_handle_t btns[16] = {0};
    button_config_t button_cfg = {
        .type = BUTTON_TYPE_CUSTOM,
        .long_press_time = 1000,
        .short_press_time = 180,
        .custom_button_config = {
            .button_custom_get_key_value = get_button_value,
        },
    };

    for (int i = 0; i < 16; i++) {
        if (btns[i] == NULL) {
            button_cfg.custom_button_config.priv = i;
            if (i == 7 || i == 15) {
                button_cfg.custom_button_config.active_level = 1;
            } else {
                button_cfg.custom_button_config.active_level = 0;
            }
            btns[i] = iot_button_create(&button_cfg);
            iot_button_register_cb(btns[i], BUTTON_PRESS_DOWN, button_press_down_cb[i], NULL);
            iot_button_register_cb(btns[i], BUTTON_PRESS_UP, button_press_up_cb[i], NULL);
        }
    }
}

static bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI("joybutton", "calibration scheme version is %s", "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .chan = channel,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI("joybutton", "calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

    *out_handle = handle;
    if (ret == ESP_OK) {
        ESP_LOGI("joybutton", "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        ESP_LOGW("joybutton", "eFuse not burnt, skip software calibration");
    } else {
        ESP_LOGE("joybutton", "Invalid arg or no memory");
    }

    return calibrated;
}

void rocker_adc_init(void)
{
    adc_oneshot_unit_init_cfg_t rocker_adc_init_config = {
        .unit_id = ADC_UNIT_2,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&rocker_adc_init_config, &game_mode_adc_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = EXAMPLE_ADC_ATTEN,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(game_mode_adc_handle, LEFT_HOTAS1_ADC_CHAN, &config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(game_mode_adc_handle, LEFT_HOTAS2_ADC_CHAN, &config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(game_mode_adc_handle, RIGHT_HOTAS1_ADC_CHAN, &config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(game_mode_adc_handle, RIGHT_HOTAS2_ADC_CHAN, &config));

    do_left_hotas1_adc_chan = example_adc_calibration_init(ADC_UNIT_2, LEFT_HOTAS1_ADC_CHAN, EXAMPLE_ADC_ATTEN, &left_hotas1_adc_chan_handle);
    do_left_hotas2_adc_chan = example_adc_calibration_init(ADC_UNIT_2, LEFT_HOTAS2_ADC_CHAN, EXAMPLE_ADC_ATTEN, &left_hotas2_adc_chan_handle);
    do_right_hotas1_adc_chan = example_adc_calibration_init(ADC_UNIT_2, RIGHT_HOTAS1_ADC_CHAN, EXAMPLE_ADC_ATTEN, &right_hotas1_adc_chan_handle);
    do_right_hotas2_adc_chan = example_adc_calibration_init(ADC_UNIT_2, RIGHT_HOTAS2_ADC_CHAN, EXAMPLE_ADC_ATTEN, &right_hotas2_adc_chan_handle);
    ESP_LOGI("joybutton", "rocker adc init OK.");
}