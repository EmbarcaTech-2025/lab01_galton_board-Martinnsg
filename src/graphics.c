#include "graphics.h"
#include "ssd1306.h"
#include "string.h"
#include "stdio.h"

#define I2C_SDA 14
#define I2C_SCL 15

static uint8_t gfx_buffer[ssd1306_buffer_length];
static struct render_area screen_region = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

void gfx_initialize() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();

    calculate_render_area_buffer_length(&screen_region);
    gfx_clear_screen();
    gfx_update_display();
}

void gfx_clear_screen() {
    memset(gfx_buffer, 0, sizeof(gfx_buffer));
}

void gfx_update_display() {
    render_on_display(gfx_buffer, &screen_region);
}

void gfx_draw_dot(int x, int y, bool state) {
    if (x < 0 || x >= ssd1306_width || y < 0 || y >= ssd1306_height)
        return;

    uint8_t page = y / 8;
    uint8_t bit_mask = 1 << (y % 8);

    if (state)
        gfx_buffer[page * ssd1306_width + x] |= bit_mask;
    else
        gfx_buffer[page * ssd1306_width + x] &= ~bit_mask;
}

void gfx_draw_particle(int x, int y) {
    gfx_draw_dot(x, y, true);
    gfx_draw_dot(x - 1, y, true);
    gfx_draw_dot(x + 1, y, true);
}

void gfx_draw_histogram(int *data_bins, int num_bins) {
    int max_bar_height = 20;
    int bar_width = 4;

    if (num_bins * bar_width > ssd1306_width) return;

    int max_val = 1;
    for (int i = 0; i < num_bins; i++) {
        if (data_bins[i] > max_val) max_val = data_bins[i];
    }

    int plot_width = num_bins * bar_width;
    int x_offset = (ssd1306_width - plot_width) / 2;

    for (int i = 0; i < num_bins; i++) {
        int height = (data_bins[i] * max_bar_height) / max_val;

        int x0 = x_offset + (i * bar_width);
        for (int x = x0; x < x0 + bar_width; x++) {
            for (int y = ssd1306_height - 1; y > (ssd1306_height - 1 - height); y--) {
                gfx_draw_dot(x, y, true);
            }
        }
    }
}

void gfx_draw_count_text(int value) {
    char text[20];
    snprintf(text, sizeof(text), "%d", value);
    ssd1306_draw_string(gfx_buffer, 0, 0, text);
}

void gfx_draw_pin_field(int pin_layers) {
    int center_x = 64;
    int top_y = 10;
    int total_rows = 7;

    for (int row = 0; row < total_rows; row++) {
        int pins_in_row = row + 1;
        int y_pos = top_y + row * 8;
        int spacing = 8;

        for (int i = 0; i < pins_in_row; i++) {
            int x = center_x + i * spacing - row * spacing / 2;
            gfx_draw_dot(x, y_pos, true);
        }
    }
}
