#include "ball_sim.h"
#include "stdlib.h"
#include "ssd1306.h"
#include "graphics.h"

static Particle particles[MAX_BALLS];
static int bins[MAX_BINS] = {0};
static int count_total = 0;

void particle_system_init() {
    for (int i = 0; i < MAX_BALLS; i++) {
        particles[i].enabled = false;
    }
    for (int i = 0; i < MAX_BINS; i++) {
        bins[i] = 0;
    }
    count_total = 0;
}

void particle_emit() {
    for (int i = 0; i < MAX_BALLS; i++) {
        if (!particles[i].enabled) {
            particles[i].x = ssd1306_width / 2;
            particles[i].y = 10;
            particles[i].progress = 0;
            particles[i].enabled = true;
            break; // emite apenas uma partícula por vez
        }
    }
}

void particle_update_all() {
    for (int i = 0; i < MAX_BALLS; i++) {
        if (!particles[i].enabled) continue;

        if (particles[i].progress < MAX_STEPS) {
            int direction = (rand() % 2 == 0) ? -1 : 1;
            particles[i].x += direction * 2;
            particles[i].y += 5;
            particles[i].progress++;
        } else {
            int slot = particles[i].x * MAX_BINS / ssd1306_width;
            if (slot < 0) slot = 0;
            if (slot >= MAX_BINS) slot = MAX_BINS - 1;

            bins[slot]++;
            count_total++;
            particles[i].enabled = false;
        }
    }
}

void particle_render() {
    for (int i = 0; i < MAX_BALLS; i++) {
        if (particles[i].enabled) {
            gfx_draw_particle(particles[i].x, particles[i].y);
        }
    }
}

int *histogram_access() {
    return bins;
}

int total_particles_counted() {
    return count_total;
}
