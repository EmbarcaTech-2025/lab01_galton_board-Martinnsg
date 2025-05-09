#include "machine.h"
#include "ball_sim.h"
#include "graphics.h"
#include "pico/stdlib.h"

static uint64_t last_emit_timestamp = 0;
static const uint64_t emit_interval_ms = 300;

void machine_initialize() {
    gfx_initialize();
    particle_system_init();
}

void machine_update() {
    uint64_t current_time = to_ms_since_boot(get_absolute_time());

    if (current_time - last_emit_timestamp > emit_interval_ms) {
        particle_emit();
        last_emit_timestamp = current_time;
    }

    particle_update_all();
}

void machine_render() {
    gfx_clear_screen();
    particle_render();
    gfx_draw_pin_field(MAX_BINS);
    gfx_draw_histogram(histogram_access(), MAX_BINS);
    gfx_draw_count_text(total_particles_counted());
    gfx_update_display();
}
