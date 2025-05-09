#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>

void gfx_initialize();
void gfx_clear_screen();
void gfx_draw_dot(int x, int y, bool state);
void gfx_draw_particle(int x, int y);
void gfx_draw_histogram(int *data_bins, int num_bins);
void gfx_draw_count_text(int value);
void gfx_draw_pin_field(int pin_layers);
void gfx_update_display();

#endif
