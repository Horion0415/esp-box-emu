#include "hal/spi_types.h"
#include "driver/spi_master.h"

#include "display.hpp"

#include "spi_lcd.h"
#include "esp_lcd_panel_ops.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static constexpr size_t display_width = 320;
static constexpr size_t display_height = 240;
static constexpr size_t pixel_buffer_size = display_width*NUM_ROWS_IN_FRAME_BUFFER;
std::shared_ptr<espp::Display> display;

static constexpr size_t frame_buffer_size = (((320) * 2) * 240);
static uint8_t *frame_buffer0;
static uint8_t *frame_buffer1;

SemaphoreHandle_t sem_count_free_trans = NULL;
bool flushing_flag = false;
extern _lv_disp_drv_t * disp_drv;


extern "C" uint16_t make_color(uint8_t r, uint8_t g, uint8_t b) {
    return lv_color_make(r,g,b).full;
}

extern "C" uint16_t* get_vram0() {
    return display->vram0();
}

extern "C" uint16_t* get_vram1() {
    return display->vram1();
}

extern "C" uint8_t* get_frame_buffer0() {
    return frame_buffer0;
}

extern "C" uint8_t* get_frame_buffer1() {
    return frame_buffer1;
}


static void lcd_fill(const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel = ((lvgl_port_display_cfg_t *)disp_drv->user_data)->panel_handle;

    if(area->x1 < area->x2 && area->y1 < area->y2) {
        if(esp_lcd_panel_draw_bitmap(panel, area->x1, area->y1, area->x2, area->y2, color_map) == ESP_OK){
            flushing_flag = true;
            xSemaphoreTake(sem_count_free_trans, portMAX_DELAY);
        }
    }
}

void lcd_clear(const uint16_t xs, const uint16_t ys, const uint16_t width, const uint16_t height) {
    esp_lcd_panel_handle_t panel = ((lvgl_port_display_cfg_t *)disp_drv->user_data)->panel_handle;

    uint16_t chunk_height = 25;

    uint16_t* line_buffer =  (uint16_t*)get_vram0();
    memset(line_buffer, 0, pixel_buffer_size * sizeof(uint16_t));

    for (uint16_t y_start = ys; y_start < ys + height; y_start += chunk_height) {
        uint16_t this_chunk_height = chunk_height;
        if (y_start + this_chunk_height > ys + height) {
            this_chunk_height = (ys + height) - y_start;
        }
        if(esp_lcd_panel_draw_bitmap(panel, xs, y_start, xs + width, y_start + this_chunk_height, line_buffer) == ESP_OK) {
            flushing_flag = true;
            xSemaphoreTake(sem_count_free_trans, portMAX_DELAY);
        }
    }
}

extern "C" void lcd_write_frame(const uint16_t xs, const uint16_t ys, const uint16_t width, const uint16_t height, const uint8_t * data){
    lv_area_t area {
        .x1 = (lv_coord_t)(xs),
        .y1 = (lv_coord_t)(ys),
        .x2 = (lv_coord_t)(xs+width),
        .y2 = (lv_coord_t)(ys+height)};
    lcd_fill(&area, (lv_color_t*)data);
}

static bool lvgl_port_flush_ready_callback(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_drv = (lv_disp_drv_t *)user_ctx;
    assert(disp_drv != NULL);
    BaseType_t taskAwake = pdFALSE;
    lv_disp_flush_ready(disp_drv);
    if (flushing_flag && sem_count_free_trans) {
        xSemaphoreGiveFromISR(sem_count_free_trans, &taskAwake);
    }
    return taskAwake == pdTRUE;
}

static bool initialized = false;
extern "C" void display_init() {
    if (initialized) {
        return;
    }
    // initialize the display / lvgl
    using namespace std::chrono_literals;
    display = std::make_shared<espp::Display>(espp::Display::AllocatingConfig{
            .width = display_width,
            .height = display_height,
            .pixel_buffer_size = pixel_buffer_size,
            .update_period = 5ms,
            .double_buffered = true,
            .allocation_flags = MALLOC_CAP_8BIT | MALLOC_CAP_DMA,
        });

    if (NULL == sem_count_free_trans) {
        sem_count_free_trans = xSemaphoreCreateCounting(1, 0);
        assert(sem_count_free_trans);
    }
    esp_lcd_panel_io_handle_t io_panel = ((lvgl_port_display_cfg_t *)disp_drv->user_data)->io_handle;
    const esp_lcd_panel_io_callbacks_t cbs = {
        .on_color_trans_done = lvgl_port_flush_ready_callback,
    };
    esp_lcd_panel_io_register_event_callbacks(io_panel, &cbs, disp_drv);

    frame_buffer0 = (uint8_t*)heap_caps_malloc(frame_buffer_size, MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
    frame_buffer1 = (uint8_t*)heap_caps_malloc(frame_buffer_size, MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
    initialized = true;
}
