#include "hal/spi_types.h"
#include "spi_host_cxx.hpp"

#include "display.hpp"
#include "st7789.hpp"

#include "spi_lcd.h"

static constexpr size_t display_width = 320;
static constexpr size_t display_height = 240;
static constexpr size_t pixel_buffer_size = display_width*50;
std::unique_ptr<idf::SPIMaster> master;
std::shared_ptr<idf::SPIDevice> lcd;
std::shared_ptr<espp::Display> display;

// create the lcd_write function
extern "C" void lcd_write(uint8_t *data, size_t length, uint16_t user_data) {
    if (length == 0) {
        // oddly the esp-idf-cxx spi driver asserts if we try to send 0 data...
        return;
    }
    // NOTE: we could simply provide user_data as context to the function
    // NOTE: if we don't call get() to block for the transaction, then the
    // transaction will go out scope and fail.
    lcd->transfer(data, data+length, nullptr,
                  [](void* ud) {
                      uint32_t flags = (uint32_t)ud;
                      if (flags & (uint32_t)espp::Display::Signal::FLUSH) {
                          lv_disp_t * disp = _lv_refr_get_disp_refreshing();
                          lv_disp_flush_ready(disp->driver);
                      }
                  },
                  (void*)user_data).get();
}

#define U16x2toU32(m,l) ((((uint32_t)(l>>8|(l&0xFF)<<8))<<16)|(m>>8|(m&0xFF)<<8))

extern "C" uint16_t make_color(uint8_t r, uint8_t g, uint8_t b) {
    return lv_color_make(r,g,b).full;
}

extern "C" void set_pixel(const uint16_t x, const uint16_t y, const uint16_t color) {
    uint32_t xv,yv;
    xv = U16x2toU32(x,x);
    yv = U16x2toU32(y,y);
    // Send command for column address set
    espp::St7789::send_command((uint8_t)espp::St7789::Command::caset);
    // send data for column address set
    espp::St7789::send_data((uint8_t*)&xv, 4);
    // send command for row address set
    espp::St7789::send_command((uint8_t)espp::St7789::Command::raset);
    // send data for row address set
    espp::St7789::send_data((uint8_t*)&yv, 4);
    // send command for ram write
    espp::St7789::send_command((uint8_t)espp::St7789::Command::ramwr);
    // now send the actual color data
    espp::St7789::send_data((uint8_t *)&color, 2);
}

extern "C" void lcd_write_frame(const uint16_t xs, const uint16_t ys, const uint16_t width, const uint16_t height, const uint8_t * data){
    if (data) {
        // have data, fill the area with the color data
        lv_area_t area {
            .x1 = (lv_coord_t)(xs),
            .y1 = (lv_coord_t)(ys),
            .x2 = (lv_coord_t)(xs+width-1),
            .y2 = (lv_coord_t)(ys+height-1)};
        espp::St7789::fill(nullptr, &area, (lv_color_t*)data);
    } else {
        // don't have data, so clear the area (set to 0)
        espp::St7789::clear(xs, ys, width, height);
    }
}

static bool initialized = false;
extern "C" void lcd_init() {
    if (initialized) {
        return;
    }
    master = std::make_unique<idf::SPIMaster>(idf::SPINum(SPI2_HOST),
                                              idf::MOSI(6),
                                              idf::MISO(18),
                                              idf::SCLK(7),
                                              idf::SPI_DMAConfig::AUTO(),
                                              idf::SPITransferSize(pixel_buffer_size * sizeof(lv_color_t)));
    lcd = master->create_dev(idf::CS(5), idf::Frequency::MHz(60));
    // initialize the controller
    espp::St7789::initialize({
            .lcd_write = lcd_write,
            .reset_pin = (gpio_num_t)48,
            .data_command_pin = (gpio_num_t)4,
            .backlight_pin = (gpio_num_t)45,
            .backlight_on_value = true,
            .invert_colors = true,
            .mirror_x = true,
            .mirror_y = true,
        });
    // initialize the display / lvgl
    display = std::make_shared<espp::Display>(espp::Display::Config{
            .width = display_width,
            .height = display_height,
            .pixel_buffer_size = pixel_buffer_size,
            .flush_callback = espp::St7789::flush,
            .rotation = espp::Display::Rotation::LANDSCAPE,
            .software_rotation_enabled = true
        });
    initialized = true;
}