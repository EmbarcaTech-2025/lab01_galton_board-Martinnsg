#include <stdio.h>
#include "pico/stdlib.h"
#include "machine.h"
#include "ball_sim.h"
#include "graphics.h"

int main() {
    stdio_init_all();
    gfx_initialize();
    particle_system_init();

    while (true) {
        machine_update();
        machine_render();
        sleep_ms(100); 
    }

    return 0;
}
